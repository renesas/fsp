/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_pdc_api.h"
#include "bsp_api.h"
#include "r_pdc_cfg.h"
#include "r_pdc.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "PDC" in ASCII, used to determine if driver is open. */
#define PDC_PRV_OPEN                      (0x00504443ULL)

/* Performs 8 32bit/4byte transfers per PDC data ready interrupt as described in hardware manual (see Section 44.3.4
 * 'Reception Operation' of the RA6M3 manual R01UH0886EJ0100).
 * */
#define PDC_PRV_TRANSFER_SIZE             4U                    /* 32 bit transfer size from PCDR register */
#define PDC_PRV_TRANSFERS_PER_BLOCK       8U

#define PDC_PRV_MAX_PIXEL_RESOLUTION      0x1000U               /* Max resolution: 4095 */

#define PDC_PRV_PCSR_MASK                 (R_PDC_PCSR_HERF_Msk | R_PDC_PCSR_VERF_Msk | R_PDC_PCSR_UDRF_Msk | \
                                           R_PDC_PCSR_OVRF_Msk | R_PDC_PCSR_FEF_Msk | R_PDC_PCSR_FEMPF_Msk | \
                                           R_PDC_PCSR_FBSY_Msk) // Mask of PCSR flag bits
#define PDC_PRV_INTERRUPT_DISABLE_MASK    (~(R_PDC_PCCR0_HERIE_Msk | R_PDC_PCCR0_VERIE_Msk | R_PDC_PCCR0_UDRIE_Msk | \
                                             R_PDC_PCCR0_OVIE_Msk | R_PDC_PCCR0_FEIE_Msk | R_PDC_PCCR0_DFIE_Msk))

#define PDC_PRV_TIMEOUT                   0xFFFFU

/* Worst case ratio of (ICLK/PCLKB) = 64 approximately.
 * 3 PCLKB cycles is the number of cycles to wait for IICn.
 * Refer "Table 3.2 Access cycles (1 of 2)" of the RA6M3 manual R01UH0886EJ0100)
 */
#define PDC_PERIPHERAL_REG_MAX_WAIT       (0x40U * 0x03U)

#define PDC_HARDWARE_REGISTER_WAIT(reg, required_value, timeout) \
    while ((timeout))                                            \
    {                                                            \
        if ((required_value) == (reg))                           \
        {                                                        \
            break;                                               \
        }                                                        \
        (timeout)--;                                             \
    }

void pdc_transfer_req_isr(void);
void pdc_int_isr(void);

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void        r_pdc_transfer_callback(pdc_instance_ctrl_t * p_ctrl);
static void r_pdc_error_handler(pdc_instance_ctrl_t * p_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* PDC API  */
const pdc_api_t g_pdc_on_pdc =
{
    .open         = R_PDC_Open,
    .close        = R_PDC_Close,
    .captureStart = R_PDC_CaptureStart,
};

/*******************************************************************************************************************//**
 * @addtogroup PDC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Powers on PDC, handles required initialization described in the hardware manual.
 *
 * Implements @ref pdc_api_t::open.
 *
 * The Open function provides initial configuration for the PDC module. It powers on the module and enables the PCLKO
 * output and the PIXCLK input. Further initialization requires the PIXCLK input to be running in order to be able to
 * reset the PDC as part of its initialization. This clock is input from a camera module and so the reset and further
 * initialization is performed in @ref pdc_api_t::captureStart. This function should be called once prior to calling any
 * other PDC API functions. After the PDC is opened the Open function should not be called again without first
 * calling the Close function.
 *
 * Example:
 * @snippet r_pdc_example.c R_PDC_Open
 *
 * @retval FSP_SUCCESS              Initialization was successful.
 * @retval FSP_ERR_ASSERTION        One or more of the following parameters is NULL
 *                                  1. p_cfg is NULL
 *                                  2. p_api_ctrl is NULL
 *                                  3. The pointer to the transfer interface in the p_cfg parameter is NULL
 *                                  4. Callback parameter is NULL.
 *                                  5. Invalid IRQ number assigned
 * @retval FSP_ERR_INVALID_ARGUMENT One or more of the following parameters is incorrect
 *                                  1. bytes_per_pixel is zero
 *                                  2. x_capture_pixels is zero
 *                                  3. y_capture_pixels is zero
 *                                  4. x_capture_start_pixel + x_capture_pixels is greater than 4095, OR
 *                                  5. y_capture_start_pixel + y_capture_pixels is greater than 4095
 * @retval  FSP_ERR_ALREADY_OPEN     Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_PDC_Open (pdc_ctrl_t * const p_api_ctrl, pdc_cfg_t const * const p_cfg)
{
    pdc_instance_ctrl_t * p_ctrl = (pdc_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err;

#if (PDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg->p_lower_lvl_transfer);
    FSP_ASSERT(p_cfg->p_callback != NULL);
    FSP_ASSERT(p_cfg->pdc_irq >= (IRQn_Type) 0);
    FSP_ERROR_RETURN((p_cfg->bytes_per_pixel != 0UL), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((p_cfg->x_capture_pixels != (uint16_t) 0UL), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((p_cfg->y_capture_pixels != (uint16_t) 0UL), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(
        ((p_cfg->y_capture_start_pixel + p_cfg->y_capture_pixels) < (uint16_t) PDC_PRV_MAX_PIXEL_RESOLUTION),
        FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(
        ((p_cfg->x_capture_start_pixel + p_cfg->x_capture_pixels) < (uint16_t) PDC_PRV_MAX_PIXEL_RESOLUTION),
        FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_ctrl->open != PDC_PRV_OPEN, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg = p_cfg;

    R_BSP_IrqCfgEnable(p_cfg->pdc_irq, p_cfg->pdc_ipl, p_ctrl);

    /* If DTC is used */
    if (p_cfg->transfer_req_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->transfer_req_irq, p_cfg->transfer_req_ipl, p_ctrl);
    }

    p_ctrl->p_current_buffer     = p_cfg->p_buffer;
    p_ctrl->transfer_in_progress = false;
    p_ctrl->p_callback           = p_cfg->p_callback;
    p_ctrl->p_context            = p_cfg->p_context;

    /** Disable module stop mode for PDC */
    R_BSP_MODULE_START(FSP_IP_PDC, 0);

    /* Performs PDC initialization as described in hardware manual (see Section 44.3.8
     * 'Initial Settings' of the RA6M3 manual R01UH0886EJ0100).
     * Disable PDC
     * Set PCLKB divider
     * Enable PCLKO output
     * Enable the PIXCLK input
     */
    R_PDC->PCCR1 = (uint32_t) 0UL;
    R_PDC->PCCR0 = ((uint32_t) (p_cfg->clock_division << R_PDC_PCCR0_PCKDIV_Pos) & R_PDC_PCCR0_PCKDIV_Msk) |
                   (1U << R_PDC_PCCR0_PCKOE_Pos) |
                   (1U << R_PDC_PCCR0_PCKE_Pos);

    /* Open the transfer driver. Clear the transfer length in case the transfer_info_t structure is reused and the
     * length was copied to the upper 8 bits for block mode. Configurations are updated before it is used. */

    transfer_info_t * p_info            = p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info;
    uint32_t          transfer_settings = (uint32_t) TRANSFER_MODE_BLOCK << TRANSFER_SETTINGS_MODE_BITS |
                                          (uint32_t) TRANSFER_ADDR_MODE_INCREMENTED <<
                                 TRANSFER_SETTINGS_DEST_ADDR_BITS |
                                          (uint32_t) TRANSFER_SIZE_4_BYTE << TRANSFER_SETTINGS_SIZE_BITS |
                                          (uint32_t) TRANSFER_REPEAT_AREA_SOURCE << TRANSFER_SETTINGS_REPEAT_AREA_BITS |
                                          (uint32_t) TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS;

    /** Set up transfer interface */
    p_info->length = PDC_PRV_TRANSFERS_PER_BLOCK;

    /** Configure the transfer interface  */

    p_info->p_src = (void const *) &R_PDC->PCDR;
    uint32_t num_blocks =
        (uint32_t) (p_ctrl->p_cfg->x_capture_pixels * p_ctrl->p_cfg->bytes_per_pixel *
                    p_ctrl->p_cfg->y_capture_pixels) /
        (uint32_t) (PDC_PRV_TRANSFER_SIZE * PDC_PRV_TRANSFERS_PER_BLOCK);
    p_info->num_blocks             = (uint16_t) num_blocks;
    p_ctrl->num_blocks             = p_info->num_blocks;
    p_info->transfer_settings_word = transfer_settings;

    err = p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->open(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl,
                                                           p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg);
    FSP_ERROR_RETURN((err == FSP_SUCCESS), err);

    p_ctrl->open = PDC_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Stops and closes the transfer interface, disables and powers off the PDC, clears internal driver data
 * and disables interrupts.
 *
 * Implements @ref pdc_api_t::close.
 *
 * @retval FSP_SUCCESS           Successful close.
 * @retval FSP_ERR_ASSERTION     p_api_ctrl is NULL
 * @retval FSP_ERR_NOT_OPEN      Open has not been successfully called.
 **********************************************************************************************************************/
fsp_err_t R_PDC_Close (pdc_ctrl_t * const p_api_ctrl)
{
    pdc_instance_ctrl_t * p_ctrl = (pdc_instance_ctrl_t *) p_api_ctrl;

#if (PDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((PDC_PRV_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    /* Disable all interrupts. */
    R_PDC->PCCR0 &= PDC_PRV_INTERRUPT_DISABLE_MASK;

    /* Close the transfer driver. */
    p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->close(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl);

    /* Disable PDC */
    R_PDC->PCCR1 = (uint32_t) 0UL;

    R_BSP_IrqDisable(p_ctrl->p_cfg->pdc_irq);

    if (p_ctrl->p_cfg->transfer_req_irq >= 0)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->transfer_req_irq);
    }

    R_BSP_MODULE_STOP(FSP_IP_PDC, 0);

    /* Mark driver as closed */
    p_ctrl->open = 0U;

    /* Mark transfer as not in progress */
    p_ctrl->transfer_in_progress = false;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Starts a capture. Enables interrupts.
 *
 * Implements @ref pdc_api_t::captureStart.
 *
 * Sets up the transfer interface to transfer data from the PDC into the specified buffer. Configures the PDC settings
 * as previously set by the @ref pdc_api_t::open API. These settings are configured here as the PIXCLK input must be active
 * for the PDC reset operation.
 * When a capture is complete the callback registered during @ref pdc_api_t::open API call will be called.
 *
 * Example:
 * @snippet r_pdc_example.c R_PDC_CaptureStart
 *
 * @retval FSP_SUCCESS           Capture start successful.
 * @retval FSP_ERR_ASSERTION     One or more of the following parameters is NULL
 *                               1. p_api_ctrl is NULL
 *                               2. p_buffer is NULL while p_buffer field of the control structure is NULL
 * @retval FSP_ERR_NOT_OPEN      Open has not been successfully called.
 * @retval FSP_ERR_IN_USE        PDC transfer is already in progress.
 * @retval FSP_ERR_TIMEOUT       Reset operation timed out.
 **********************************************************************************************************************/
fsp_err_t R_PDC_CaptureStart (pdc_ctrl_t * const p_api_ctrl, uint8_t * const p_buffer)
{
    pdc_instance_ctrl_t * p_ctrl = (pdc_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t             err    = FSP_SUCCESS;
#if (PDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_ctrl);

    if (NULL == p_buffer)
    {
        FSP_ASSERT(NULL != p_ctrl->p_current_buffer);
    }

    /* Check driver is open */
    FSP_ERROR_RETURN((PDC_PRV_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);

    /* Check if a transfer is already in progress */
    FSP_ERROR_RETURN((p_ctrl->transfer_in_progress == false), FSP_ERR_IN_USE);
#endif
    uint32_t pccr0_initial_setting =
        (uint32_t) ((uint32_t) (p_ctrl->p_cfg->clock_division << R_PDC_PCCR0_PCKDIV_Pos) & R_PDC_PCCR0_PCKDIV_Msk) |
        (1U << R_PDC_PCCR0_PCKOE_Pos) |
        (1U << R_PDC_PCCR0_PCKE_Pos);

    if (NULL != p_buffer)
    {
        p_ctrl->p_current_buffer = p_buffer;
    }

    /* Reset PDC */
    /* Retain old settings and apply reset */
    R_PDC->PCCR0 = pccr0_initial_setting | (1U << R_PDC_PCCR0_PRST_Pos);

    /* Wait for PDC reset bit (PRST) to clear as described in hardware manual (see Section 44.2.1
     * 'PDC Control Register 0 (PCCR0): PRST' of the RA6M3 manual R01UH0886EJ0100).
     */
    uint32_t timeout = PDC_PERIPHERAL_REG_MAX_WAIT;
    PDC_HARDWARE_REGISTER_WAIT(R_PDC->PCCR0, pccr0_initial_setting, timeout);
    if (!timeout)
    {
        return FSP_ERR_TIMEOUT;
    }

    /** Set horizontal capture range */
    R_PDC->HCR =
        (uint32_t) ((uint32_t) (p_ctrl->p_cfg->x_capture_start_pixel * p_ctrl->p_cfg->bytes_per_pixel) &
                    R_PDC_HCR_HST_Msk) |
        (uint32_t) ((uint32_t) ((p_ctrl->p_cfg->x_capture_pixels * p_ctrl->p_cfg->bytes_per_pixel) << 16) &
                    R_PDC_HCR_HSZ_Msk);

    /** Set vertical capture range */
    R_PDC->VCR = (uint32_t) ((p_ctrl->p_cfg->y_capture_start_pixel) & R_PDC_VCR_VST_Msk) |
                 (uint32_t) ((uint32_t) ((p_ctrl->p_cfg->y_capture_pixels) << 16) & R_PDC_VCR_VSZ_Msk);

    /**
     * Set VSYNC polarity
     * Set HSYNC polarity
     * Set endianess of capture data
     * Enable interrupts
     * Receive data ready interrupt,
     * Underrun interrupt,
     * Overrun interrupt,
     * Frame end interrupt,
     * Vertical line number setting error interrupt,
     * Horizontal byte number setting error interrupt */
    R_PDC->PCCR0 = pccr0_initial_setting |
                   (uint32_t) ((uint32_t) p_ctrl->p_cfg->vsync_polarity << R_PDC_PCCR0_VPS_Pos |
                               (uint32_t) p_ctrl->p_cfg->hsync_polarity << R_PDC_PCCR0_HPS_Pos |
                               (uint32_t) p_ctrl->p_cfg->endian << R_PDC_PCCR0_EDS_Pos |
                               (R_PDC_PCCR0_DFIE_Msk | R_PDC_PCCR0_UDRIE_Msk | R_PDC_PCCR0_OVIE_Msk |
                                R_PDC_PCCR0_FEIE_Msk | R_PDC_PCCR0_VERIE_Msk | R_PDC_PCCR0_HERIE_Msk));

    /* Set destination buffer and enable transfer */
    err = p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->reset(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl,
                                                            p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info->p_src,
                                                            p_ctrl->p_current_buffer,
                                                            p_ctrl->num_blocks);
    FSP_ERROR_RETURN((err == FSP_SUCCESS), err);

    /* Mark transfer as in progress */
    p_ctrl->transfer_in_progress = true;

    /* Set PCCR1.PCE as 1 */
    R_PDC->PCCR1 = 1;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup PDC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Internal transfer complete callback for PDC driver.
 *
 * This is invoked every time a frame has been captured and hence also performs PDC operation flow
 * as described in hardware manual (see Figure 44.19 'Example operation flow' of the RA6M3 manual R01UH0886EJ0100).
 * Thus eliminating the need of a separate frame end interrupt and its ISR.
 *
 *
 * @param[in]     p_ctrl         Pointer to the instance control block.
 **********************************************************************************************************************/
void r_pdc_transfer_callback (pdc_instance_ctrl_t * p_ctrl)
{
    pdc_callback_args_t pdc_args;
    uint16_t            timeout = PDC_PERIPHERAL_REG_MAX_WAIT;

    /* Performs PDC operation flow as described in hardware manual (see Figure 44.19
     * 'Example operation flow' of the RA6M3 manual R01UH0886EJ0100).
     * */
    while ((0UL == (R_PDC_PCSR_FEMPF_Msk & R_PDC->PCSR)) && (0UL != timeout) &&
           (0UL == (R_PDC_PCSR_UDRF_Msk & R_PDC->PCSR)))
    {
        /* Wait for FIFO empty flag to be set and DTC/DMAC to transfer last data block.*/
        timeout--;
    }

    /* As per the above hardware manual reference the sequence for PDC stop and
     * FEF flag clear is reversed for error case but has no impact on the functionality.
     */

    /* Stop the PDC */
    R_PDC->PCCR1 = (uint32_t) 0UL;

    /* Clear FEF frame end flag */
    R_PDC->PCSR &= ~R_PDC_PCSR_FEF_Msk;

    if (0UL != (R_PDC_PCSR_UDRF_Msk & R_PDC->PCSR))
    {
        /* Underrun error has occurred */

        /* Clear FEF frame end flag */
        R_PDC->PCSR &= ~R_PDC_PCSR_FEF_Msk;

        /* Call the error handler */
        r_pdc_error_handler(p_ctrl);
    }

    p_ctrl->transfer_in_progress = false;
    pdc_args.p_context           = p_ctrl;
    pdc_args.event               = PDC_EVENT_TRANSFER_COMPLETE;
    pdc_args.p_buffer            = p_ctrl->p_current_buffer;
    p_ctrl->p_callback(&pdc_args);
}

/*******************************************************************************************************************//**
 * Called when a DTC transfer completes.  Not used for DMAC.
 **********************************************************************************************************************/
void pdc_transfer_req_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    pdc_instance_ctrl_t * p_ctrl = (pdc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    r_pdc_transfer_callback(p_ctrl);

    /* Clear the IR flag in the ICU.
     * This must be after the callback because the next DTC transfer will begin when this bit is cleared. */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * @brief  PDC error ISR
 **********************************************************************************************************************/
void pdc_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    IRQn_Type irq = R_FSP_CurrentIrqGet();

    pdc_instance_ctrl_t * p_ctrl = (pdc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Call the error handler */
    r_pdc_error_handler(p_ctrl);

    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * @brief  PDC error handler
 * @param[in]   p_ctrl   Pointer to PDC Specific Control Structure
 **********************************************************************************************************************/
static void r_pdc_error_handler (pdc_instance_ctrl_t * p_ctrl)
{
    pdc_callback_args_t pdc_args;

    /* Performs PDC error processing flow as described in hardware manual (see Figure 44.20
     * 'Example error processing flow' of the RA6M3 manual R01UH0886EJ0100).
     * All the errors are consolidated and reported through the callback and the status register
     * is cleared in a single write.
     * *//* Stop the PDC */
    R_PDC->PCCR1 = (uint32_t) 0UL;

    /* Disable the transfer */
    p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->disable(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl);

    /* Report all the errors at once */
    uint32_t event = R_PDC->PCSR;
    R_PDC->PCSR        = ~event & PDC_PRV_PCSR_MASK;
    pdc_args.event     = (pdc_event_t) event;
    pdc_args.p_context = p_ctrl->p_context;
    p_ctrl->p_callback(&pdc_args);
}
