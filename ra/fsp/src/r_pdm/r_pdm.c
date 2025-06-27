/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_pdm.h"
#include "r_pdm_cfg.h"
#if PDM_CFG_DMAC_ENABLE
 #include "r_dmac.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define PDM_PRV_PDSCR_CLEAR_MASK            (R_PDM_CH_PDSCR_SDFC_Msk | R_PDM_CH_PDSCR_SCDFC_Msk |    \
                                             R_PDM_CH_PDSCR_OVLDFC_Msk | R_PDM_CH_PDSCR_OVUDFC_Msk | \
                                             R_PDM_CH_PDSCR_BFOWDFC_Msk)
#define PDM_PRV_PDSR_ERROR_MASK             (R_PDM_CH_PDSR_SCDF_Msk | R_PDM_CH_PDSR_OVLDF_Msk | \
                                             R_PDM_CH_PDSR_OVUDF_Msk |                          \
                                             R_PDM_CH_PDSR_BFOWDF_Msk)

#define PDM_PRV_FIFO_SAMPLE_SIZE            sizeof(uint32_t)
#define PDM_PRV_FIFO_DEPTH                  32
#define PDM_PRV_FIFO_INITIAL_READ_LENGTH    (PDM_PRV_FIFO_DEPTH - 2)

/* "PDM" in ASCII, used to determine if driver is open. */
#define PDM_PRV_OPEN                        (0x50444DU)

#define PDM_PRV_LOOP_MAX                    (1000)

#define PDM_PRV_UNITS                       (1)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * pdm_prv_ns_callback)(pdm_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile pdm_prv_ns_callback)(pdm_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* ISRs */
void pdm_sdet_isr(void);
void pdm_dat_isr(void);
void pdm_err_isr(void);

static void r_pdm_call_callback(pdm_instance_ctrl_t * p_ctrl, pdm_event_t event, pdm_error_t error);

/* FIFO subroutines */
static uint32_t r_pdm_fifo_read(pdm_instance_ctrl_t * p_instance_ctrl);

#if PDM_CFG_DMAC_ENABLE
static fsp_err_t r_pdm_dependent_drivers_configure(pdm_instance_ctrl_t * p_instance_ctrl);
void             pdm_rxi_dmac_isr(dmac_callback_args_t * args);

#endif

/* Subroutines */
static void r_pdm_stop_sub(pdm_instance_ctrl_t * const p_instance_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** PDM Implementation of PDM interface.  */
const pdm_api_t g_pdm_on_pdm =
{
    .open                  = R_PDM_Open,
    .start                 = R_PDM_Start,
    .stop                  = R_PDM_Stop,
    .soundDetectionEnable  = R_PDM_SoundDetectionEnable,
    .soundDetectionDisable = R_PDM_SoundDetectionDisable,
    .read                  = R_PDM_Read,
    .statusGet             = R_PDM_StatusGet,
    .close                 = R_PDM_Close,
    .callbackSet           = R_PDM_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup PDM
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the PDM. Implements @ref pdm_api_t::open.
 *
 * This function sets this clock divisor and the configurations specified in pdm_cfg_t.
 *
 * @retval FSP_SUCCESS                     Ready for PDM communication.
 * @retval FSP_ERR_ASSERTION               The pointer to p_ctrl or p_cfg is null.
 * @retval FSP_ERR_ALREADY_OPEN            The control block has already been opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Channel number is not available on this device.
 * @return                                 See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                         possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_PDM_Open (pdm_ctrl_t * const p_ctrl, pdm_cfg_t const * const p_cfg)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if PDM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);

    FSP_ERROR_RETURN(BSP_PERIPHERAL_PDM_CHANNEL_MASK & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN(PDM_PRV_UNITS > p_cfg->unit, FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    FSP_ERROR_RETURN(PDM_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Calculate base address for registers on this channel. */
    R_PDM_CH_Type      * p_reg    = (R_PDM_CH_Type *) &R_PDM->CH[p_cfg->channel];
    pdm_extended_cfg_t * p_extend = (pdm_extended_cfg_t *) p_cfg->p_extend;

    /* Enable PDM module */
    R_BSP_MODULE_START(FSP_IP_PDM, p_cfg->unit);

    /* Initialize PDM IP according to Figure 50.17 "PDM-IF Start Flow" in
     * section 50.4.1 "Start Flow" from the RA8P1 user manual. */

    /* Set PCM Width */
    uint32_t pdmdsr = (uint32_t) p_cfg->pcm_width << R_PDM_CH_PDMDSR_DBIS_Pos;

    /* Set sinc and moving average order */
    pdmdsr |= (uint32_t) p_extend->sinc_filter_mode << R_PDM_CH_PDMDSR_SFMD_Pos;
    pdmdsr |= (uint32_t) p_extend->moving_average_mode << R_PDM_CH_PDMDSR_SDMAMD_Pos;

    /* Set filter shifts */
    pdmdsr |= (uint32_t) p_extend->low_pass_filter_shift << R_PDM_CH_PDMDSR_LFIS_Pos;
    pdmdsr |= (uint32_t) p_extend->compensation_filter_shift << R_PDM_CH_PDMDSR_CFIS_Pos;
    pdmdsr |= (uint32_t) p_extend->high_pass_filter_shift << R_PDM_CH_PDMDSR_HFIS_Pos;

    /* Set edge detection */
    pdmdsr |= (uint32_t) p_cfg->pcm_edge << R_PDM_CH_PDMDSR_INPSEL_Pos;

    /* Write to PDMDSRCHn */
    p_reg->PDMDSR = pdmdsr;

    /* Set sinc output range */
    uint32_t pdsfcr = (uint32_t) p_extend->sincrng << R_PDM_CH_PDSFCR_SINCRNG_Pos;

    /* Set sinc decimation ratio */
    pdsfcr |= (uint32_t) p_extend->sincdec << R_PDM_CH_PDSFCR_SINCDEC_Pos;

    /* Set PDM_CLK divider */
    pdsfcr |= (uint32_t) p_extend->clock_div << R_PDM_CH_PDSFCR_CKDIV_Pos;

    /* Write to PDSFCRCHn */
    p_reg->PDSFCR = pdsfcr;

    uint8_t i;

    /* Set high pass filter coefficients */
    p_reg->PDHFCS0R = (uint32_t) p_extend->hpf_coefficient_s0;
    p_reg->PDHFCK1R = (uint32_t) p_extend->hpf_coefficient_k1;
    for (i = 0; i < PDM_NUM_HPF_COEFFICIENT_H; i++)
    {
        p_reg->PDHFCHR[i] = (uint32_t) p_extend->hpf_coefficient_h[i];
    }

    /* Set compensation filter coefficients */
    for (i = 0; i < PDM_NUM_COMPENSATION_FILTER_COEFFICIENT_H; i++)
    {
        p_reg->PDCFCHR[i] = (uint32_t) p_extend->compensation_filter_coefficient_h[i];
    }

    /* Set low pass filter coefficients */
    p_reg->PDLFCH010R = (uint32_t) p_extend->lpf_coefficient_h0;
    for (i = 0; i < PDM_NUM_LPF_FILTER_COEFFICIENT_H1; i++)
    {
        p_reg->PDLFCH1R[i] = (uint32_t) p_extend->lpf_coefficient_h1[i];
    }

    /* Set Channel's Data Buffer Control */
    p_reg->PDDBCR = (uint32_t) p_extend->interrupt_threshold;

    /* Set Channel's Error Detection Control */
    p_reg->PDSCTSR = (uint32_t) (p_extend->short_circuit_count_h << R_PDM_CH_PDSCTSR_SCDH_Pos) |
                     (uint32_t) (p_extend->short_circuit_count_l << R_PDM_CH_PDSCTSR_SCDL_Pos);
    p_reg->PDOVLTR = p_extend->overvoltage_detection_lower_limit;
    p_reg->PDOVUTR = p_extend->overvoltage_detection_upper_limit;

    /* Activate target channel's filtering */
    p_reg->PDSTRTR = R_PDM_CH_PDSTRTR_STRTRG_Msk;

    /* Clear Channel's Status */
    p_reg->PDSCR = PDM_PRV_PDSCR_CLEAR_MASK;

    /* Set Channel's Status Detection Control (for Error Detection) */
    uint32_t pdsdcr = p_extend->short_circuit_detection_enable;
    pdsdcr |= p_extend->over_voltage_lower_limit_detection_enable;
    pdsdcr |= p_extend->over_voltage_upper_limit_detection_enable;
    pdsdcr |= p_extend->buffer_overwrite_detection_enable;

    p_reg->PDSDCR = pdsdcr;

    /* Initialize the control structure. */
    p_instance_ctrl->p_reg = p_reg;
    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* Initialization complete. */
    p_instance_ctrl->open = PDM_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts PDM. Implements @ref pdm_api_t::start.
 *
 * This function enables reception, and enables any transfer instances used.
 *
 * The PDM will start on the next frame boundary.
 *
 * @retval FSP_SUCCESS               PDM communication stop request issued.
 * @retval FSP_ERR_ASSERTION         The pointer to p_ctrl was null.
 * @retval FSP_ERR_INVALID_SIZE      The size of buffer is not a multiple of pdm_interrupt_threshold_t.
 * @retval FSP_ERR_INVALID_ALIGNMENT The alignment of argument buffer_size is not matched with hardware specification.
 * @retval FSP_ERR_NOT_OPEN          The channel is not opened.
 * @return                       See @ref RENESAS_ERROR_CODES or lower level drivers for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_PDM_Start (pdm_ctrl_t * const p_ctrl,
                       void * const       p_buffer,
                       size_t const       buffer_size,
                       uint32_t const     number_of_data_to_callback)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if PDM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_buffer, FSP_ERR_ASSERTION);
    FSP_ERROR_RETURN(PDM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(buffer_size > 0U);
    FSP_ASSERT(number_of_data_to_callback > 0U);
#endif
    pdm_extended_cfg_t * p_extend = (pdm_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
#if PDM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extend);
#endif

    R_PDM_CH_Type         * p_reg                = p_instance_ctrl->p_reg;
    pdm_cfg_t const * const p_cfg                = p_instance_ctrl->p_cfg;
    uint32_t                stages_per_interrupt = 1U << p_extend->interrupt_threshold;

    /* Verify that the buffer is aligned to 4 bytes. */
    FSP_ERROR_RETURN((0 == ((uint32_t) p_buffer & 0x03U)), FSP_ERR_INVALID_ALIGNMENT);

    /* Verify that number_of_data_to_callback is a multiple of configured interrupt threshold which determines the
     * number of stages per interrupt */
    FSP_ERROR_RETURN((0 == (number_of_data_to_callback % stages_per_interrupt)), FSP_ERR_INVALID_SIZE);

    /* Verify that buffer size is a multiple of 4 bytes */
    FSP_ERROR_RETURN((0 == buffer_size % PDM_PRV_FIFO_SAMPLE_SIZE), FSP_ERR_INVALID_SIZE);

    /* Verify that number of samples in buffer is a multiple of the number of data to callback */
    uint32_t number_of_samples_in_buffer = buffer_size / PDM_PRV_FIFO_SAMPLE_SIZE;
    FSP_ERROR_RETURN((0 == (number_of_samples_in_buffer % number_of_data_to_callback)), FSP_ERR_INVALID_SIZE);

    p_instance_ctrl->p_rx_dest        = p_buffer;
    p_instance_ctrl->p_read           = p_buffer;
    p_instance_ctrl->rx_dest_samples  = number_of_samples_in_buffer;
    p_instance_ctrl->rx_int_count     = 0;
    p_instance_ctrl->rx_int_count_max = number_of_data_to_callback;

    /* Start communication according to Figure 50.19 "PDM-IF normal processing flow" in
     * section 50.4.3 "Normal Processing Flow" from the RA8P1 user manual. */

    /* Set Channel's Data Read Enable */
    p_reg->PDDRCR = R_PDM_CH_PDDRCR_DATRE_Msk;

    /* Read PDDRR x (P_FD - 2) before starting interrupts/DMA
     * P_FD: FIFO Depth
     * Note: this data discarded and not stored anywhere
     */
    for (int i = 0; i < PDM_PRV_FIFO_INITIAL_READ_LENGTH; i++)
    {
        FSP_REGISTER_READ(p_reg->PDDRR);
    }

#if PDM_CFG_DMAC_ENABLE

    /* Configure dependent timer and transfer drivers. */
    fsp_err_t err = r_pdm_dependent_drivers_configure(p_instance_ctrl);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);
#endif

    /* Enable error interrupt if allocated and not already enabled */
    if ((p_cfg->err_irq >= 0) && (0 == p_reg->PDICR_b.IEDE))
    {
        p_reg->PDICR_b.IEDE = 1;
        R_BSP_IrqCfgEnable(p_cfg->err_irq, p_cfg->err_ipl, p_instance_ctrl);
    }

    /* Enable data interrupt */
    p_reg->PDICR |= R_PDM_CH_PDICR_IDRE_Msk;

    if (p_cfg->dat_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->dat_irq, p_cfg->dat_ipl, p_instance_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops PDM. Implements @ref pdm_api_t::stop.
 *
 * This function disables reception, and disables any transfer instances used.
 *
 * The PDM will stop on the next frame boundary.
 *
 * @retval FSP_SUCCESS           PDM communication stop request issued.
 * @retval FSP_ERR_ASSERTION     The pointer to p_ctrl was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 * @return                       See @ref RENESAS_ERROR_CODES or lower level drivers for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_PDM_Stop (pdm_ctrl_t * const p_ctrl)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if PDM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(PDM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_pdm_stop_sub(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures and enables sound detection. Implements @ref pdm_api_t::soundDetectionEnable.
 *
 * This function configures sound detection based on the passed in settings. It then enables sound detection.
 *
 * @retval FSP_SUCCESS           Sound detection configured and enabled.
 * @retval FSP_ERR_ASSERTION     The pointer to p_ctrl was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 * @return                       See @ref RENESAS_ERROR_CODES or lower level drivers for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_PDM_SoundDetectionEnable (pdm_ctrl_t * const p_ctrl, pdm_sound_detection_setting_t sound_detection_setting)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if PDM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(PDM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    pdm_cfg_t const * const p_cfg = p_instance_ctrl->p_cfg;
    R_PDM_CH_Type         * p_reg = p_instance_ctrl->p_reg;

    /* Enable error interrupt if allocated and not already enabled */
    if ((p_cfg->err_irq >= 0) && (0 == p_reg->PDICR_b.IEDE))
    {
        p_reg->PDICR_b.IEDE = 1;
        R_BSP_IrqCfgEnable(p_cfg->err_irq, p_cfg->err_ipl, p_instance_ctrl);
    }

    /* Clear sound detection status */
    p_reg->PDSCR_b.SDFC = 1;

    /* Set Channel's Sound Detection Control */
    p_reg->PDSDLTR = sound_detection_setting.sound_detection_lower_limit;
    p_reg->PDSDUTR = sound_detection_setting.sound_detection_upper_limit;

    /* Set sound detection enable */
    p_reg->PDSDCR_b.SDE = 1;

    /* Enable sound detection interrupt if used */
    if (p_cfg->sdet_irq >= 0)
    {
        p_reg->PDICR_b.ISDE = 1;
        R_BSP_IrqCfgEnable(p_cfg->sdet_irq, p_cfg->sdet_ipl, p_instance_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables sound detection. Implements @ref pdm_api_t::soundDetectionDisable.
 *
 * This function disables sound detection.
 *
 * @retval FSP_SUCCESS           Sound detection disabled.
 * @retval FSP_ERR_ASSERTION     The pointer to p_ctrl was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 * @return                       See @ref RENESAS_ERROR_CODES or lower level drivers for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_PDM_SoundDetectionDisable (pdm_ctrl_t * const p_ctrl)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if PDM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(PDM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    pdm_cfg_t const * const p_cfg = p_instance_ctrl->p_cfg;
    R_PDM_CH_Type         * p_reg = p_instance_ctrl->p_reg;

    /* Clear sound detection enable */
    p_reg->PDSDCR_b.SDE = 0;

    /* Disable sound detection interrupt if used */
    if (p_cfg->sdet_irq >= 0)
    {
        p_reg->PDICR_b.ISDE = 0;
    }

    /* Clear sound detection status */
    p_reg->PDSCR_b.SDFC = 1;

    /* Disable error interrupt if allocated and if data read isn't enabled */
    if ((p_cfg->err_irq >= 0) && (0 == p_reg->PDDRCR))
    {
        p_reg->PDICR_b.IEDE = 0;
        R_BSP_IrqDisable(p_cfg->err_irq);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function is not supported. Implements @ref pdm_api_t::read.
 *
 * @retval FSP_ERR_UNSUPPORTED                 This function is not supported.
 **********************************************************************************************************************/
fsp_err_t R_PDM_Read (pdm_ctrl_t * const p_ctrl, void * const p_dest, uint32_t const bytes)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(bytes);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Gets PDM status and stores it in provided pointer p_status. Implements @ref pdm_api_t::statusGet.
 *
 * Calling this function will clear any set error flags in the hardware.
 *
 * @retval FSP_SUCCESS           Information stored successfully.
 * @retval FSP_ERR_ASSERTION     The p_ctrl or p_status parameter was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_PDM_StatusGet (pdm_ctrl_t * const p_ctrl, pdm_status_t * const p_status)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if PDM_CFG_PARAM_CHECKING_ENABLE

    /* Make sure parameters are valid. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(PDM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    R_PDM_CH_Type * p_reg = p_instance_ctrl->p_reg;

    /* Set state based on if data read is enabled */
    p_status->state = p_reg->PDDRCR ? PDM_STATE_IN_USE : PDM_STATE_STOPPED;

    /* Set sound detection state */
    p_status->sound_detection_enabled = (0 != p_reg->PDICR_b.ISDE);

    /* Get status, mask out non-error statuses */
    uint32_t pdsr = p_instance_ctrl->p_reg->PDSR & PDM_PRV_PDSR_ERROR_MASK;

    /* Set errors, shift so that error statuses match the error enum*/
    p_status->error = (pdm_error_t) (pdsr >> R_PDM_CH_PDSCR_SCDFC_Pos);

    /* Clear set error flags */
    p_instance_ctrl->p_reg->PDSCR = pdsr;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes PDM. Implements @ref pdm_api_t::close.
 *
 * This function powers down the PDM and closes the lower level timer and transfer drivers if they are used.
 *
 * @retval FSP_SUCCESS           Device closed successfully.
 * @retval FSP_ERR_ASSERTION     The pointer to p_ctrl was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_PDM_Close (pdm_ctrl_t * const p_ctrl)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if PDM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(PDM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    pdm_cfg_t const * const p_cfg = p_instance_ctrl->p_cfg;
    R_PDM_CH_Type         * p_reg = p_instance_ctrl->p_reg;

    r_pdm_stop_sub(p_instance_ctrl);

    /* Stop PDM according to Figure 50.18 "PDM-IF Stop Flow" in
     * section 50.4.2 "Stop Flow" from the RA8P1 user manual. */

    /* Stop target channel's filtering */
    p_reg->PDSTPTR = R_PDM_CH_PDSTPTR_STPTRG_Msk;

    /* Target channel is stopped? */
    for (uint32_t loop = 0; loop < PDM_PRV_LOOP_MAX; loop++)
    {
        if (!(p_reg->PDSR & R_PDM_CH_PDSR_STATE_Msk))
        {
            break;
        }
    }

    /* Disable Channel's Interrupt */
    p_reg->PDICR &= ~(R_PDM_CH_PDICR_ISDE_Msk | R_PDM_CH_PDICR_IEDE_Msk);

    /* Disable Channel's Status Detection */
    p_reg->PDSDCR = 0;

    /* Clear Channel's Status */
    p_reg->PDSCR = PDM_PRV_PDSCR_CLEAR_MASK;

    p_instance_ctrl->open = 0U;

    /* Disable interrupts. */
    if (p_cfg->dat_irq >= 0)
    {
        R_BSP_IrqDisable(p_cfg->dat_irq);
    }

    if (p_cfg->sdet_irq >= 0)
    {
        R_BSP_IrqDisable(p_cfg->sdet_irq);
    }

    if (p_cfg->err_irq >= 0)
    {
        R_BSP_IrqDisable(p_cfg->err_irq);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements pdm_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_PDM_CallbackSet (pdm_ctrl_t * const          p_ctrl,
                             void (                    * p_callback)(pdm_callback_args_t *),
                             void * const                p_context,
                             pdm_callback_args_t * const p_callback_memory)
{
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) p_ctrl;

#if (PDM_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(PDM_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if PDM_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    pdm_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(pdm_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup R_PDM)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if PDM_CFG_DMAC_ENABLE

/***********************************************************************************************************************
 * Configures any dependent drivers selected by the user, including transfer and timer drivers.
 *
 * @param[in] p_instance_ctrl               Pointer to the p_instance_ctrl structure.
 *
 * @retval FSP_SUCCESS                 Dependent drivers configured successfully.
 * @return                             See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                     possible return codes. This function calls:
 *                                         * @ref transfer_api_t::open
 **********************************************************************************************************************/
static fsp_err_t r_pdm_dependent_drivers_configure (pdm_instance_ctrl_t * p_instance_ctrl)
{
    /* Prepare transfer configuration. */
    fsp_err_t               err_transfer_rx = FSP_SUCCESS;
    pdm_cfg_t const * const p_cfg           = p_instance_ctrl->p_cfg;
    R_PDM_CH_Type         * p_reg           = p_instance_ctrl->p_reg;
    pdm_extended_cfg_t    * p_extend        = (pdm_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    transfer_instance_t   * p_transfer_rx   = (transfer_instance_t *) p_cfg->p_transfer_rx;

    /* If a transfer instance is provided for read, open the transfer instance. */
    if (NULL != p_transfer_rx)
    {
        transfer_info_t * p_transfer_info = p_transfer_rx->p_cfg->p_info;
        uint32_t        * p_data_end      = p_instance_ctrl->p_rx_dest;
        p_data_end += p_instance_ctrl->rx_dest_samples;

        /* Configure transfer src, dest, and length */
        p_transfer_info->p_src  = (void *) &p_reg->PDDRR;
        p_transfer_info->p_dest = p_instance_ctrl->p_rx_dest;
        p_transfer_info->transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE;
        p_transfer_info->transfer_settings_word_b.mode = TRANSFER_MODE_BLOCK;
        p_transfer_info->transfer_settings_word_b.irq  = TRANSFER_IRQ_END;
        p_transfer_info->length     = (uint16_t) (1U << p_extend->interrupt_threshold);
        p_transfer_info->num_blocks = (uint16_t) p_instance_ctrl->rx_int_count_max /
                                      (1U << p_extend->interrupt_threshold);

        /* Calculate next transfer destination, if the next transfer will go past
         * the end of the buffer then start the next transfer at the beginning of the buffer */
        p_instance_ctrl->p_read =
            (void *) ((uint32_t *) p_instance_ctrl->p_read + p_instance_ctrl->rx_int_count_max);

        if (p_instance_ctrl->p_read >= (void *) p_data_end)
        {
            p_instance_ctrl->p_read = p_instance_ctrl->p_rx_dest;
        }

        err_transfer_rx = p_transfer_rx->p_api->open(p_cfg->p_transfer_rx->p_ctrl, p_cfg->p_transfer_rx->p_cfg);
        FSP_ERROR_RETURN((FSP_SUCCESS == err_transfer_rx), err_transfer_rx);

        err_transfer_rx = p_transfer_rx->p_api->enable(p_cfg->p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN((FSP_SUCCESS == err_transfer_rx), err_transfer_rx);
    }

    return FSP_SUCCESS;
}

#endif

/***********************************************************************************************************************
 * Disables PDM reception.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 **********************************************************************************************************************/
static void r_pdm_stop_sub (pdm_instance_ctrl_t * const p_instance_ctrl)
{
    /* Stop communication according to Figure 50.19 "PDM-IF normal processing flow" in
     * section 50.4.3 "Normal Processing Flow" from the RA8P1 user manual. */
    R_PDM_CH_Type         * p_reg = p_instance_ctrl->p_reg;
    pdm_cfg_t const * const p_cfg = p_instance_ctrl->p_cfg;

    /* Only stop if data read is currently enabled */
    if (p_reg->PDDRCR)
    {
        /* Disable channel data interrupt. */
        p_reg->PDICR_b.IDRE = 0;

        /* Disable Channel's Data Read. */
        p_reg->PDDRCR = 0;

#if PDM_CFG_DMAC_ENABLE
        transfer_instance_t * p_transfer_rx = (transfer_instance_t *) p_instance_ctrl->p_cfg->p_transfer_rx;

        /* If transfer is used, disable transfer when stop is requested. */
        if (NULL != p_transfer_rx)
        {
            fsp_err_t err = p_transfer_rx->p_api->close(p_transfer_rx->p_ctrl);

            /* Return from close is only used for error log */
            FSP_PARAMETER_NOT_USED(err);
            FSP_ERROR_LOG(err);
        }
#endif

        /* Disable error interrupt if allocated and if sound detection isn't enabled */
        if ((p_cfg->err_irq >= 0) && (0 == p_reg->PDSDCR_b.SDE))
        {
            p_reg->PDICR_b.IEDE = 0;
            R_BSP_IrqDisable(p_cfg->err_irq);
        }
    }
}

/***********************************************************************************************************************
 *  Reads data from FIFO.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 * @return                             The number of received data.
 **********************************************************************************************************************/
static uint32_t r_pdm_fifo_read (pdm_instance_ctrl_t * p_instance_ctrl)
{
    /* Calculate the number of available bytes of data in receive FIFO. */
    uint32_t count;

    uint32_t * p_data_end = p_instance_ctrl->p_rx_dest;
    p_data_end += p_instance_ctrl->rx_dest_samples;
    uint32_t * p_data      = p_instance_ctrl->p_read;
    uint32_t   fifo_number = p_instance_ctrl->p_reg->PDDSR;
    for (count = 0; count < fifo_number; count++)
    {
        *p_data++ = p_instance_ctrl->p_reg->PDDRR;
        if (p_data >= p_data_end)
        {
            p_data = p_instance_ctrl->p_rx_dest;
            count++;
            break;
        }
    }

    p_instance_ctrl->p_read = p_data;

    return count;
}

/***********************************************************************************************************************
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to PDM instance control block
 * @param[in]     event      Event code
 * @param[in]     error      Error code
 **********************************************************************************************************************/
static void r_pdm_call_callback (pdm_instance_ctrl_t * p_ctrl, pdm_event_t event, pdm_error_t error)
{
    pdm_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    pdm_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->event     = event;
    p_args->p_context = p_ctrl->p_context;
    p_args->error     = error;

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        pdm_prv_ns_callback p_callback = (pdm_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif
    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/***********************************************************************************************************************
 * Sound detection ISR. Calls callback and disables Sound detection interrupt.
 **********************************************************************************************************************/
void pdm_sdet_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq             = R_FSP_CurrentIrqGet();
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disable Sound detection */
    p_instance_ctrl->p_reg->PDSDCR &= ~R_PDM_CH_PDSDCR_SDE_Msk;

    /* Clear Sound detection flag */
    p_instance_ctrl->p_reg->PDSCR = R_PDM_CH_PDSCR_SDFC_Msk;

    /* Call callback if provided with sound detection event */
    if (p_instance_ctrl->p_callback)
    {
        r_pdm_call_callback(p_instance_ctrl, PDM_EVENT_SOUND_DETECTION, PDM_ERROR_NONE);
    }

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    /* Enable Sound detection */
    p_instance_ctrl->p_reg->PDSDCR |= R_PDM_CH_PDSDCR_SDE_Msk;

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * Receive ISR.  Calls callback when reception is complete.  Empties FIFO if transfer interface is not used.
 **********************************************************************************************************************/
void pdm_dat_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq             = R_FSP_CurrentIrqGet();
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    if (NULL != p_instance_ctrl->p_rx_dest)
    {
        uint32_t received;

        /* If transfer is not used, read data into the destination buffer. */
        received = r_pdm_fifo_read(p_instance_ctrl);
        p_instance_ctrl->rx_int_count += received;
        while (p_instance_ctrl->rx_int_count >= p_instance_ctrl->rx_int_count_max)
        {
            p_instance_ctrl->rx_int_count -= p_instance_ctrl->rx_int_count_max;
            if (p_instance_ctrl->p_callback)
            {
                r_pdm_call_callback(p_instance_ctrl, PDM_EVENT_DATA, PDM_ERROR_NONE);
            }
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * Error ISR.
 *
 * Handles errors and calls callback.
 **********************************************************************************************************************/
void pdm_err_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq             = R_FSP_CurrentIrqGet();
    pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    pdm_error_t error = PDM_ERROR_NONE;

    /* Get status, mask out non-error statuses */
    uint32_t pdsr = p_instance_ctrl->p_reg->PDSR & PDM_PRV_PDSR_ERROR_MASK;

    /* Set error for callback, shift so that error statuses match the error enum*/
    error = (pdm_error_t) (pdsr >> R_PDM_CH_PDSCR_SCDFC_Pos);

    /* Clear set error flags */
    p_instance_ctrl->p_reg->PDSCR = pdsr;

    if (p_instance_ctrl->p_callback)
    {
        /* Call callback if provided. */
        r_pdm_call_callback(p_instance_ctrl, PDM_EVENT_ERROR, error);
    }

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if PDM_CFG_DMAC_ENABLE

/***********************************************************************************************************************
 * Dedicated function for DMAC linkage at the time of reception.
 **********************************************************************************************************************/
void pdm_rxi_dmac_isr (dmac_callback_args_t * args)
{
    if (NULL != args)
    {
        pdm_instance_ctrl_t * p_instance_ctrl = (pdm_instance_ctrl_t *) args->p_context;

        if ((NULL != p_instance_ctrl) && (p_instance_ctrl->p_callback))
        {
            pdm_extended_cfg_t  * p_extend      = (pdm_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
            transfer_instance_t * p_transfer_rx = (transfer_instance_t *) p_instance_ctrl->p_cfg->p_transfer_rx;

            /* Set new destination for next transfer, reset block count */
            p_transfer_rx->p_api->reset(p_transfer_rx->p_ctrl,
                                        (void *) &p_instance_ctrl->p_reg->PDDRR,
                                        p_instance_ctrl->p_read,
                                        (uint16_t) p_instance_ctrl->rx_int_count_max /
                                        (1U << p_extend->interrupt_threshold));

            /* Calculate the next destination */
            p_instance_ctrl->p_read =
                (void *) ((uint32_t *) p_instance_ctrl->p_read + p_instance_ctrl->rx_int_count_max);

            uint32_t * p_data_end = p_instance_ctrl->p_rx_dest;
            p_data_end += p_instance_ctrl->rx_dest_samples;

            if (p_instance_ctrl->p_read >= (void *) p_data_end)
            {
                p_instance_ctrl->p_read = p_instance_ctrl->p_rx_dest;
            }

            /* Call callback function */
            r_pdm_call_callback(p_instance_ctrl, PDM_EVENT_DATA, PDM_ERROR_NONE);
        }
    }
}

#endif
