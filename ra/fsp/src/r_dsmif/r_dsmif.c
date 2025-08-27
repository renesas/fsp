/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_dsmif_cfg.h"
#include "r_dsmif.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DSMIF_OPEN                 ((uint32_t) ('D' << 24U) | ('S' << 16U) | ('M' << 8U) | ('I' << 0U))

#define DSMIF_DATA_CHANNEL_MASK    (0x03U)
#define DSMIF_DATA_REGID_MASK      (0x0FU)
#define DSMIF_DATA_TYPE_MASK       (0x70U)
#define DSMIF_DATA_TYPE_SHIFT      (0x4U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* DSMIF data register */
typedef enum e_dsmif_current_data
{
    DSMIF_CURRENT_DATA                 = 0, // DSCDRCHn    : Current Data Register
    DSMIF_CURRENT_DATA_CAPTURE_A       = 1, // DSCCDRACHn  : Capture Current Data Register A
    DSMIF_CURRENT_DATA_CAPTURE_B       = 2, // DSCCDRBCHn  : Capture Current Data Register B
    DSMIF_OVERCURRENT_DATA             = 3, // DSOCDRCHn   : Overcurrent Data Register
    DSMIF_OVERCURRENT0_CAPTURE_DATA    = 4, // DSCOCDR0CHn : Overcurrent Capture Data Register 0
    DSMIF_OVERCURRENT1_CAPTURE_DATA    = 5, // DSCOCDR1CHn : Overcurrent Capture Data Register 1
    DSMIF_OVERCURRENT2_CAPTURE_DATA    = 6, // DSCOCDR2CHn : Overcurrent Capture Data Register 2
    DSMIF_OVERCURRENT_SUM_CAPTURE_DATA = 7, // DSSECDRn    : Overcurrent Sum Error Detect Capture Data Register n
} dsmif_current_data_t;

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#if DSMIF_CFG_PARAM_CHECKING_ENABLE

static fsp_err_t r_dsmif_open_param_check(dsmif_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg);

#endif

static void      r_dsmif_start(dsmif_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t r_dsmif_stop(dsmif_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t r_dsmif_read(dsmif_instance_ctrl_t * const p_instance_ctrl,
                              adc_channel_t const           reg_id,
                              uint16_t                    * p_data);
static void r_dsmif_irq_enable(dsmif_instance_ctrl_t * const       p_instance_ctrl,
                               dsmif_interrupt_cfg_t const * const p_irq_cfg);
static void r_dsmif_irq_disable(dsmif_interrupt_cfg_t const * const p_irq_cfg);

static void r_dsmif_call_callback(dsmif_instance_ctrl_t * p_instance_ctrl, adc_event_t event, adc_channel_t channel);

void dsmif_cdupdn_isr(void);
void dsmif_cdaupdn_isr(void);
void dsmif_cdbupdn_isr(void);
void dsmif_cdupd_com_isr(void);
void dsmif_cdaupd_com_isr(void);
void dsmif_cdbupd_com_isr(void);
void dsmif_err_isr(void);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** DSMIF Implementation of DSMIF interface. */
const adc_api_t g_adc_on_dsmif =
{
    .open           = R_DSMIF_Open,
    .scanCfg        = R_DSMIF_ScanCfg,
    .scanStart      = R_DSMIF_ScanStart,
    .scanGroupStart = R_DSMIF_ScanGroupStart,
    .scanStop       = R_DSMIF_ScanStop,
    .scanStatusGet  = R_DSMIF_ScanStatusGet,
    .read           = R_DSMIF_Read,
    .read32         = R_DSMIF_Read32,
    .calibrate      = R_DSMIF_Calibrate,
    .offsetSet      = R_DSMIF_OffsetSet,
    .callbackSet    = R_DSMIF_CallbackSet,
    .close          = R_DSMIF_Close,
    .infoGet        = R_DSMIF_InfoGet,
};

/*******************************************************************************************************************//**
 * @addtogroup DSMIF
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Applies power to the DSMIF and initializes the hardware based on the user configuration.
 * As part of this initialization, set interrupts, set DSMIF error interrupt registers, etc.
 *
 * @retval  FSP_SUCCESS                 Configuration successful.
 * @retval  FSP_ERR_ASSERTION           An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_ALREADY_OPEN        Control block is already open.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED    A required interrupt is disabled
 * @retval  FSP_ERR_IP_UNIT_NOT_PRESENT The Unit requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

#if DSMIF_CFG_PARAM_CHECKING_ENABLE
    err = r_dsmif_open_param_check(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set all p_instance_ctrl fields prior to using it in any functions. */
    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->p_context  = p_cfg->p_context;

    dsmif_extended_cfg_t const * p_extend = p_cfg->p_extend;

    /* Calculate the register base address. */
    uint32_t address_offset = ((uint32_t) R_DSMIF1 - (uint32_t) R_DSMIF0);
    p_instance_ctrl->p_reg = (R_DSMIF0_Type *) ((uint32_t) R_DSMIF0 + address_offset * p_cfg->unit);

    /* Release from the module-stop state */
    R_BSP_MODULE_START(FSP_IP_DSMIF, p_cfg->unit);

    /* Set the DSMIF core clock. */
    p_instance_ctrl->p_reg->DSCCSCR = (uint32_t) p_extend->clock_selection;

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT

    /* Set Overcurrent Sum Error Detection Lower Limit. */
    p_instance_ctrl->p_reg->DSSELTR = p_extend->overcurrent_sum_error_lower_limit;

    /* Set Overcurrent Sum Error Detection Upper Limit. */
    p_instance_ctrl->p_reg->DSSEHTR = p_extend->overcurrent_sum_error_upper_limit;

    /* Set Overcurrent Sum Error Channel(s).  */
    p_instance_ctrl->p_reg->DSSECSR = p_extend->overcurrent_sum_error_channel;

    /* Set the Overcurrent Sum Error Interrupt. */
    p_instance_ctrl->p_reg->DSSEICR = p_extend->overcurrent_sum_error_enable;
#endif

    /* Set data format for measurement results. */
    p_instance_ctrl->p_reg->DSCMSR = (uint32_t) !p_cfg->alignment |
                                     ((uint32_t) p_extend->synchronization_mode << R_DSMIF0_DSCMSR_CISM_Pos);

    /* Enable common interrupts. */
    p_instance_ctrl->p_reg->DSCICR = R_DSMIF0_DSCICR_IUCE_Msk | R_DSMIF0_DSCICR_IAUCE_Msk | R_DSMIF0_DSCICR_IBUCE_Msk;

    /* Register settings for each channel */
    for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
    {
        if (p_extend->p_channel_cfgs[ch] != NULL)
        {
            /* Get the channel register struct for this channel. */
            __IOM R_DSMIF0_CH_Type * p_channel_reg = &p_instance_ctrl->p_reg->CH[ch];

            /* Get the channel configuration for this channel. */
            dsmif_channel_cfg_t const   * p_channel_cfg = p_extend->p_channel_cfgs[ch];
            dsmif_clock_cfg_t const     * p_clock_cfg   = &p_channel_cfg->clock_cfg;
            dsmif_trigger_cfg_t const   * p_trigger_cfg = &p_channel_cfg->trigger_cfg;
            dsmif_filter_cfg_t const    * p_filter_cfg  = &p_channel_cfg->filter_cfg;
            dsmif_interrupt_cfg_t const * p_irq_cfg     = &p_channel_cfg->irq_cfg;

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
            dsmif_error_detection_cfg_t const * p_error_detection_cfg = &p_channel_cfg->error_detection_cfg;

            dsmif_filter_cfg_t const * p_overcurrent_filter_cfg =
                &p_error_detection_cfg->overcurrent_filter_cfg;
#endif

            /* Set interrupt settings. */
            uint32_t dsicr = R_DSMIF0_CH_DSICR_IUE_Msk |
                             R_DSMIF0_CH_DSICR_IAUE_Msk |
                             R_DSMIF0_CH_DSICR_IBUE_Msk;

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
            dsicr |= (uint32_t) p_error_detection_cfg->short_circuit_detection_enable << R_DSMIF0_CH_DSICR_ISE_Pos;
            dsicr |= (uint32_t) p_error_detection_cfg->overcurrent_detection_enable << R_DSMIF0_CH_DSICR_IOEL0_Pos;
            dsicr |= (uint32_t) p_error_detection_cfg->overcurrent_window_notification_enable <<
                     R_DSMIF0_CH_DSICR_OWNE0_Pos;
#endif

            p_channel_reg->DSICR = dsicr;

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT

            /* Set Overcurrent Threshold settings. */
            p_channel_reg->TR[0].DSOCL = p_error_detection_cfg->overcurrent_lower_limit[0];
            p_channel_reg->TR[1].DSOCL = p_error_detection_cfg->overcurrent_lower_limit[1];
            p_channel_reg->TR[2].DSOCL = p_error_detection_cfg->overcurrent_lower_limit[2];
            p_channel_reg->TR[0].DSOCH = p_error_detection_cfg->overcurrent_upper_limit[0];
            p_channel_reg->TR[1].DSOCH = p_error_detection_cfg->overcurrent_upper_limit[1];
            p_channel_reg->TR[2].DSOCH = p_error_detection_cfg->overcurrent_upper_limit[2];

            /* Set Overcurrent Window Notification mode. */
            p_channel_reg->DSODWCR = (uint32_t) p_error_detection_cfg->overcurrent_window_notification_mode;

            /* Set Short Circuit Detection settings. */
            p_channel_reg->DSSCTSR =
                ((p_error_detection_cfg->short_circuit_detection_low_count << R_DSMIF0_CH_DSSCTSR_SCNTL_Pos) |
                 (p_error_detection_cfg->short_circuit_detection_high_count << R_DSMIF0_CH_DSSCTSR_SCNTH_Pos));
            p_channel_reg->DSEDCR =
                ((uint32_t) p_error_detection_cfg->short_circuit_detection_enable << R_DSMIF0_CH_DSEDCR_SDE_Pos);
#endif

            /* Set Measurement Capture Trigger settings. */
            p_channel_reg->DSCMCTCR =
                (((uint32_t) p_trigger_cfg->capture_trigger_a << R_DSMIF0_CH_DSCMCTCR_CTSELA_Pos) |
                 ((uint32_t) p_trigger_cfg->capture_trigger_b << R_DSMIF0_CH_DSCMCTCR_CTSELB_Pos) |
                 ((uint32_t) p_trigger_cfg->filter_initialization_trigger << R_DSMIF0_CH_DSCMCTCR_DITSEL_Pos) |
                 ((uint32_t) p_trigger_cfg->filter_initialization_edge << R_DSMIF0_CH_DSCMCTCR_DEDGE_Pos));

            /* Set channel clock settings. */
            p_channel_reg->DSCMCCR = (((uint32_t) p_clock_cfg->direction << R_DSMIF0_CH_DSCMCCR_CKDIR_Pos) |
                                      ((uint32_t) p_clock_cfg->edge << R_DSMIF0_CH_DSCMCCR_SEDGE_Pos) |
                                      ((uint32_t) p_clock_cfg->divider << R_DSMIF0_CH_DSCMCCR_CKDIV_Pos));

            /* Set Current Measurement Filter settings. */
            p_channel_reg->DSCMFCR =
                (((uint32_t) p_filter_cfg->filter_order << R_DSMIF0_CH_DSCMFCR_CMSINC_Pos) |
                 ((uint32_t) p_filter_cfg->decimation_count << R_DSMIF0_CH_DSCMFCR_CMDEC_Pos) |
                 ((uint32_t) p_filter_cfg->data_shift << R_DSMIF0_CH_DSCMFCR_CMSH_Pos));

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT

            /* Set Overcurrent Measurement Filter settings. */
            p_channel_reg->DSOCFCR =
                (((uint32_t) p_overcurrent_filter_cfg->filter_order << R_DSMIF0_CH_DSOCFCR_OCSINC_Pos) |
                 ((uint32_t) p_overcurrent_filter_cfg->decimation_count << R_DSMIF0_CH_DSOCFCR_OCDEC_Pos) |
                 ((uint32_t) p_overcurrent_filter_cfg->data_shift << R_DSMIF0_CH_DSOCFCR_OCSH_Pos));
#endif

            /* Enable configured channel interrupts. */
            r_dsmif_irq_enable(p_instance_ctrl, p_irq_cfg);
        }
    }

    /* Enable the common capture data update interrupt request if it is provided. */
    if (p_extend->common_current_data_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->common_current_data_irq, p_extend->common_current_data_ipl, p_instance_ctrl);
    }

    /* Enable the common capture data a interrupt request if it is provided. */
    if (p_extend->common_capture_data_a_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->common_capture_data_a_irq, p_extend->common_capture_data_a_ipl, p_instance_ctrl);
    }

    /* Enable the common capture data b interrupt request if it is provided. */
    if (p_extend->common_capture_data_b_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->common_capture_data_b_irq, p_extend->common_capture_data_b_ipl, p_instance_ctrl);
    }

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT

    /* Enable the error interrupt request if it is provided. */
    if (p_extend->common_error_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->common_error_irq, p_extend->common_error_ipl, p_instance_ctrl);
    }
#endif

    /* Mark driver as open by initializing it to "DSMI" - its ASCII equivalent. */
    p_instance_ctrl->open = DSMIF_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanCfg is not supported on DSMIF.
 *
 * @retval  FSP_ERR_UNSUPPORTED        This function is not supported by the DSMIF instance.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ScanCfg (adc_ctrl_t * p_ctrl, void const * const p_extend)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_extend);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Starts all configured DSMIF channels
 *
 * @note After executing R_DSMIF_ScanStart, it is necessary to wait until the filter result is output stably.
 *
 * @retval  FSP_SUCCESS                Scan started or hardware triggers enabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ScanStart (adc_ctrl_t * p_ctrl)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

#if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_dsmif_start(p_instance_ctrl);

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanGroupStart is not supported on DSMIF.
 *
 * @retval  FSP_ERR_UNSUPPORTED        This function is not supported by the DSMIF instance.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ScanGroupStart (adc_ctrl_t * p_ctrl, adc_group_mask_t group_mask)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(group_mask);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stops any in-progress scan started by software.
 *
 * @retval  FSP_SUCCESS                Scan stopped or hardware triggers disabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_TIMEOUT            Timeout error.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ScanStop (adc_ctrl_t * p_ctrl)
{
    fsp_err_t               err;
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

#if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    err = r_dsmif_stop(p_instance_ctrl);

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * Returns the status of a scan started by software.
 *
 * @retval  FSP_SUCCESS                No software scan is in progress.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ScanStatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

#if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (0U == (p_instance_ctrl->p_reg->DSCSSR & (R_DSMIF0_DSCSSR_CHSTATE_Msk | \
                                                 (R_DSMIF0_DSCSSR_CHSTATE_Msk << 4) |
                                                 (R_DSMIF0_DSCSSR_CHSTATE_Msk << 8))))
    {
        p_status->state = ADC_STATE_IDLE;
    }
    else
    {
        p_status->state = ADC_STATE_SCAN_IN_PROGRESS;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the most recent result from a channel.
 *
 * @retval  FSP_SUCCESS                Result in p_data.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Read (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data)
{
#if DSMIF_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_data != NULL);
#endif

    return r_dsmif_read(p_ctrl, reg_id, p_data);
}

/*******************************************************************************************************************//**
 * Reads the most recent conversion result from a single channel into a 32-bit result.
 *
 * @retval  FSP_SUCCESS                Result in p_data.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Read32 (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data)
{
#if DSMIF_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_data != NULL);
#endif
    uint16_t  data16 = 0;
    fsp_err_t err    = r_dsmif_read(p_ctrl, reg_id, &data16);
    if (FSP_SUCCESS == err)
    {
        dsmif_instance_ctrl_t * const p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;
        if (ADC_ALIGNMENT_LEFT == p_instance_ctrl->p_cfg->alignment)
        {
            *p_data = (uint32_t) data16 << 16U;
        }
        else
        {
            *p_data = data16;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::calibrate is not supported on DSMIF.
 *
 * @retval  FSP_ERR_UNSUPPORTED        This function is not supported by the DSMIF instance.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Calibrate (adc_ctrl_t * p_ctrl, void const * p_extend)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_extend);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::offsetSet is not supported on DSMIF.
 *
 * @retval  FSP_ERR_UNSUPPORTED        This function is not supported by the DSMIF instance.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_OffsetSet (adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t const offset)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(reg_id);
    FSP_PARAMETER_NOT_USED(offset);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_CallbackSet (adc_ctrl_t * const          p_ctrl,
                               void (                    * p_callback)(adc_callback_args_t *),
                               void * const                p_context,
                               adc_callback_args_t * const p_callback_memory)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

#if DSMIF_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_instance_ctrl->p_callback        = p_callback;
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops any scan in progress, disables interrupts, and powers down the DSMIF peripheral.
 *
 * @note This function is delayed at least until the outage is complete, as required by the DSMIF outage procedure.
 *
 * @retval  FSP_SUCCESS                Instance control block closed successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_Close (adc_ctrl_t * p_ctrl)
{
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking*/
#if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark driver as closed   */
    p_instance_ctrl->open = 0U;

    dsmif_extended_cfg_t const * const p_extend = (dsmif_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
    {
        p_instance_ctrl->p_reg->CH[ch].DSICR = 0x00000000U;

        if (NULL != p_extend->p_channel_cfgs[ch])
        {
            /* Disable channel interrupts. */
            r_dsmif_irq_disable(&p_extend->p_channel_cfgs[ch]->irq_cfg);
        }
    }

    /* Disabled common interrupts. */
    if (p_extend->common_current_data_irq >= 0)
    {
        R_BSP_IrqDisable(p_extend->common_current_data_irq);
    }

    if (p_extend->common_capture_data_a_irq >= 0)
    {
        R_BSP_IrqDisable(p_extend->common_capture_data_a_irq);
    }

    if (p_extend->common_capture_data_b_irq >= 0)
    {
        R_BSP_IrqDisable(p_extend->common_capture_data_b_irq);
    }

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
    if (p_extend->common_error_irq >= 0)
    {
        R_BSP_IrqDisable(p_extend->common_error_irq);
    }
#endif

    /* Stop processing(No error is returned because it is forcibly terminated.) */
    r_dsmif_stop(p_instance_ctrl);

    R_BSP_MODULE_STOP(FSP_IP_DSMIF, p_instance_ctrl->p_cfg->unit);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::infoGet is not supported on DSMIF.
 *
 * @retval  FSP_ERR_UNSUPPORTED        This function is not supported by the DSMIF instance.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_InfoGet (adc_ctrl_t * const p_ctrl, adc_info_t * const p_adc_info)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_adc_info);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Enable error detection.
 *
 * @retval  FSP_SUCCESS                Configuration setting successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ErrorDetectionEnable (adc_ctrl_t * p_ctrl)
{
#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;
 #if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif
    adc_cfg_t const * const p_cfg = p_instance_ctrl->p_cfg;

    dsmif_extended_cfg_t const * p_cfg_extend = (dsmif_extended_cfg_t *) p_cfg->p_extend;

    /* Clear error flags after reading. */
    p_instance_ctrl->p_reg->DSCOCNSCR = p_instance_ctrl->p_reg->DSCOCNSR;
    p_instance_ctrl->p_reg->DSCOCESCR = p_instance_ctrl->p_reg->DSCOCESR;
    p_instance_ctrl->p_reg->DSCESCR   = p_instance_ctrl->p_reg->DSCESR;

    /* Enable Overcurrent Detection and Window Notification for each channel. */
    for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
    {
        if (NULL != p_cfg_extend->p_channel_cfgs[ch])
        {
            __IOM R_DSMIF0_CH_Type            * p_channel_reg         = &p_instance_ctrl->p_reg->CH[ch];
            dsmif_error_detection_cfg_t const * p_error_detection_cfg =
                &p_cfg_extend->p_channel_cfgs[ch]->error_detection_cfg;

            p_channel_reg->DSODCR =
                ((uint32_t) p_error_detection_cfg->overcurrent_detection_enable << R_DSMIF0_CH_DSODCR_ODEL_Pos) |
                ((uint32_t) p_error_detection_cfg->overcurrent_window_notification_enable <<
                    R_DSMIF0_CH_DSODCR_OWFE_Pos);
        }
    }

    /* Enable sum error detection. */
    p_instance_ctrl->p_reg->DSSECR =
        (uint32_t) ((p_cfg_extend->overcurrent_sum_error_enable_b.lower_limit_enable << R_DSMIF0_DSSECR_SEEL_Pos) |
                    (p_cfg_extend->overcurrent_sum_error_enable_b.upper_limit_enable <<
                     R_DSMIF0_DSSECR_SEEH_Pos));

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Returns the error status of a scan started by software.
 *
 * @retval  FSP_SUCCESS                No software scan is in progress.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_DSMIF_ErrorStatusGet (adc_ctrl_t * p_ctrl, dsmif_error_status_t * p_error_status)
{
#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) p_ctrl;

 #if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_error_status);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    uint32_t dscesr = p_instance_ctrl->p_reg->DSCESR;

    p_error_status->channel_overcurrent_window_status =
        (dsmif_overcurrent_window_notification_status_t) (p_instance_ctrl->p_reg->DSCOCNSR);
    p_error_status->channel_overcurrent_status =
        (dsmif_overcurrent_status_t) (p_instance_ctrl->p_reg->DSCOCESR);
    p_error_status->channel_short_circuit_status = (dsmif_short_circuit_status_t) (dscesr & UINT16_MAX);
    p_error_status->overcurrent_sum_status       = (dsmif_overcurrent_sum_status_t) (dscesr >> 16U);

    /* Clear error flags after reading. */
    p_instance_ctrl->p_reg->DSCOCNSCR = p_error_status->channel_overcurrent_window_status;
    p_instance_ctrl->p_reg->DSCOCESCR = p_error_status->channel_overcurrent_status;
    p_instance_ctrl->p_reg->DSCESCR   = dscesr;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_error_status);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DSMIF)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
#if DSMIF_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Validates the input parameters to open().
 *
 * @param[in]  p_instance_ctrl  Pointer to instance control block
 * @param[in]  p_cfg   Pointer to configuration structure
 *
 * @retval  FSP_SUCCESS                 No invalid configurations identified.
 * @retval  FSP_ERR_ALREADY_OPEN        Control block is already open.
 * @retval  FSP_ERR_ASSERTION           An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED    A callback is provided, but the interrupt is not enabled.
 * @retval  FSP_ERR_IP_UNIT_NOT_PRESENT The Unit requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
static fsp_err_t r_dsmif_open_param_check (dsmif_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg)
{
    /* Verify the pointers are not NULL. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(DSMIF_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Verify the unit exists on the MCU. */
    FSP_ERROR_RETURN(((1U << p_cfg->unit) & BSP_PERIPHERAL_DSMIF_CHANNEL_MASK), FSP_ERR_IP_UNIT_NOT_PRESENT);

    dsmif_extended_cfg_t const * const p_extend = (dsmif_extended_cfg_t *) p_cfg->p_extend;

    /* If a common interrupt is enabled, then a callback must be provided. */
    if (
 #if DSMIF_CFG_ERROR_DETECTION_SUPPORT
        (p_extend->common_error_irq >= 0) ||
 #endif
        (p_extend->common_current_data_irq >= 0) ||
        (p_extend->common_capture_data_a_irq >= 0) ||
        (p_extend->common_capture_data_b_irq >= 0))
    {
        FSP_ASSERT(p_cfg->p_callback != NULL);
    }

    /* If a channel interrupt is enabled, then a callback must be provided. */
    for (uint32_t i = 0; i < DSMIF_MAX_NUM_CHANNELS; i++)
    {
        if ((NULL != p_extend->p_channel_cfgs[i]) &&
            ((p_extend->p_channel_cfgs[i]->irq_cfg.capture_data_a_irq >= 0) ||
             (p_extend->p_channel_cfgs[i]->irq_cfg.capture_data_b_irq >= 0)))
        {
            FSP_ASSERT(p_cfg->p_callback != NULL);
            break;
        }
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Start DSMIF conversion on all configured channels.
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 *
 **********************************************************************************************************************/
static void r_dsmif_start (dsmif_instance_ctrl_t * const p_instance_ctrl)
{
    dsmif_extended_cfg_t const * p_extend = (dsmif_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;

    /* Write channel mask to DSCSTRTR to start all configured channels at the same time. */
    p_instance_ctrl->p_reg->DSCSTRTR = p_extend->channel_mask;
}

/*******************************************************************************************************************//**
 * Stop DMSIF conversion on all configured channels.
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 *
 * @retval  FSP_SUCCESS            Stop processing succeeded.
 * @retval  FSP_ERR_TIMEOUT        Timeout error.
 **********************************************************************************************************************/
static fsp_err_t r_dsmif_stop (dsmif_instance_ctrl_t * const p_instance_ctrl)
{
    dsmif_extended_cfg_t const * p_extend = (dsmif_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;

    /* Write channel mask to DSCSTPTR to stop all configured channels at the same time. */
    p_instance_ctrl->p_reg->DSCSTPTR = p_extend->channel_mask;

    /* Wait for all DSMIF channels to stop (Refer to "DSMIF / Stop Flow" section in the MCU user manaul). */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->DSCSSR, 0);

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT

    /* Disable overcurrent detection of all target channels */
    for (uint32_t ch = 0U; ch < DSMIF_MAX_NUM_CHANNELS; ch++)
    {
        p_instance_ctrl->p_reg->CH[ch].DSODCR = 0;
    }

    /* Disable sum error detection  */
    p_instance_ctrl->p_reg->DSSECR = 0;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures interrupts and ensures required interrupts are enabled.
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 * @param[in]  reg_id              Channel to read data from
 * @param[out] p_data              Pointer to store the conversion result
 **********************************************************************************************************************/
static fsp_err_t r_dsmif_read (dsmif_instance_ctrl_t * const p_instance_ctrl,
                               adc_channel_t const           reg_id,
                               uint16_t                    * p_data)
{
#if DSMIF_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the DSMIF unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(DSMIF_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    dsmif_extended_cfg_t const * p_extend = (dsmif_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    FSP_ASSERT(0U != ((1U << ((uint32_t) reg_id & DSMIF_DATA_REGID_MASK)) & p_extend->channel_mask));
#elif DSMIF_CFG_ERROR_DETECTION_SUPPORT
    dsmif_extended_cfg_t const * p_extend = (dsmif_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
#endif

    adc_channel_t        channel         = (adc_channel_t) ((uint32_t) reg_id & DSMIF_DATA_CHANNEL_MASK);
    dsmif_current_data_t dsmif_data_type =
        (dsmif_current_data_t) (((uint32_t) reg_id & DSMIF_DATA_TYPE_MASK) >> DSMIF_DATA_TYPE_SHIFT);
    if (DSMIF_CURRENT_DATA == dsmif_data_type)
    {
        *p_data = (uint16_t) (p_instance_ctrl->p_reg->CH[channel].DSCDR);
    }
    else if (DSMIF_CURRENT_DATA_CAPTURE_A == dsmif_data_type)
    {
        *p_data = (uint16_t) (p_instance_ctrl->p_reg->CH[channel].DSCCDRA);
    }
    else if (DSMIF_CURRENT_DATA_CAPTURE_B == dsmif_data_type)
    {
        *p_data = (uint16_t) (p_instance_ctrl->p_reg->CH[channel].DSCCDRB);
    }

#if DSMIF_CFG_ERROR_DETECTION_SUPPORT
    else if (DSMIF_OVERCURRENT_DATA == dsmif_data_type)
    {
        *p_data = (uint16_t) (p_instance_ctrl->p_reg->CH[channel].DSOCDR);
    }
    else if (DSMIF_OVERCURRENT2_CAPTURE_DATA >= dsmif_data_type)
    {
        /* There are three different overcurrent capture registers. Calculate the overcurrent capture register
         * from the dsmif_data_type field. */
        uint32_t overcurrent_index = dsmif_data_type - DSMIF_OVERCURRENT0_CAPTURE_DATA;
        *p_data = (uint16_t) (p_instance_ctrl->p_reg->CH[channel].DSCOCDR[overcurrent_index]);
    }
    else if (DSMIF_OVERCURRENT_SUM_CAPTURE_DATA == dsmif_data_type)
    {
        /* There is an overcurrent sum capture register for each channel.
         * In the following modes, the channel is used to index the associated overcurrent sum capture data.
         * - DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_0_2
         * - DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_0_1
         */
        uint32_t overcurrent_sum_index = (uint32_t) channel;

        /*
         * If the overcurrent sum data is configured to any of the following modes, the data will be stored in the
         * first overcurrent capture register.
         * - DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_0
         * - DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_1
         * - DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_2
         */
        if (DSMIF_OVERCURRENT_SUM_ERROR_CHANNEL_0 <= p_extend->overcurrent_sum_error_channel)
        {
            overcurrent_sum_index = 0;
        }

        *p_data = (uint16_t) (p_instance_ctrl->p_reg->DSSECDR[overcurrent_sum_index]);
    }
#endif
    else
    {
        return FSP_ERR_UNSUPPORTED;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures channel interrupts.
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 * @param[in]  p_irq_cfg           Pointer to interrupt configuration structure
 *
 **********************************************************************************************************************/
static void r_dsmif_irq_enable (dsmif_instance_ctrl_t * const       p_instance_ctrl,
                                dsmif_interrupt_cfg_t const * const p_irq_cfg)
{
    /* Set the interrupt priorities. */
    if (p_irq_cfg->current_data_update_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_irq_cfg->current_data_update_irq, p_irq_cfg->current_data_update_ipl, p_instance_ctrl);
    }

    if (p_irq_cfg->capture_data_a_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_irq_cfg->capture_data_a_irq, p_irq_cfg->capture_data_a_ipl, p_instance_ctrl);
    }

    if (p_irq_cfg->capture_data_b_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_irq_cfg->capture_data_b_irq, p_irq_cfg->capture_data_b_ipl, p_instance_ctrl);
    }
}

/*******************************************************************************************************************//**
 * Disables channel interrupts.
 *
 * @param[in]  p_irq_cfg           Pointer to interrupt configuration structure
 **********************************************************************************************************************/
static void r_dsmif_irq_disable (dsmif_interrupt_cfg_t const * const p_irq_cfg)
{
    if (p_irq_cfg->current_data_update_irq >= 0)
    {
        R_BSP_IrqDisable(p_irq_cfg->current_data_update_irq);
        R_FSP_IsrContextSet(p_irq_cfg->current_data_update_irq, NULL);
    }

    if (p_irq_cfg->capture_data_a_irq >= 0)
    {
        R_BSP_IrqDisable(p_irq_cfg->capture_data_a_irq);
        R_FSP_IsrContextSet(p_irq_cfg->capture_data_a_irq, NULL);
    }

    if (p_irq_cfg->capture_data_b_irq >= 0)
    {
        R_BSP_IrqDisable(p_irq_cfg->capture_data_b_irq);
        R_FSP_IsrContextSet(p_irq_cfg->capture_data_b_irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Fill in the adc_callback_args_t, then call the user callback.
 **********************************************************************************************************************/
static void r_dsmif_call_callback (dsmif_instance_ctrl_t * p_instance_ctrl, adc_event_t event, adc_channel_t channel)
{
    adc_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    adc_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
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

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_callback)
    {
        /* Store the event into the callback argument */
        p_args->event     = event;
        p_args->unit      = p_instance_ctrl->p_cfg->unit;
        p_args->channel   = channel;
        p_args->p_context = p_instance_ctrl->p_context;
        p_instance_ctrl->p_callback(p_args);
    }

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * DSMIFn Current data update interrupt handler.
 **********************************************************************************************************************/
void dsmif_cdupdn_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Determine the channel associated with this interrupt request. */
    uint32_t ielsr_offset = (uint32_t) ELC_EVENT_DSMIF0_CDUPD0 +
                            ((ELC_EVENT_DSMIF1_CDUPD0 - ELC_EVENT_DSMIF0_CDUPD0) * p_instance_ctrl->p_cfg->unit);
    uint32_t channel = R_ICU->IELSR_b[irq].IELS - ielsr_offset;

    /* Clear the channel status flag. */
    p_instance_ctrl->p_reg->DSCSCR = 1 << channel;

    r_dsmif_call_callback(p_instance_ctrl, ADC_EVENT_CONVERSION_COMPLETE, (adc_channel_t) channel);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * DSMIFn Capture Data A Update interrupt handler.
 **********************************************************************************************************************/
void dsmif_cdaupdn_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Determine the channel associated with this interrupt request. */
    uint32_t ielsr_offset = (uint32_t) ELC_EVENT_DSMIF0_CDAUPD0 +
                            ((ELC_EVENT_DSMIF1_CDAUPD0 - ELC_EVENT_DSMIF0_CDAUPD0) * p_instance_ctrl->p_cfg->unit);
    uint32_t channel = R_ICU->IELSR_b[irq].IELS - ielsr_offset;

    /* Clear the channel status flag. */
    p_instance_ctrl->p_reg->DSCSCR = 1U << (R_DSMIF0_DSCSCR_CLRCAUF_Pos + channel);

    r_dsmif_call_callback(p_instance_ctrl, ADC_EVENT_CAPTURE_A, (adc_channel_t) (ADC_CHANNEL_CAPTURE_A_MASK | channel));

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * DSMIFn Capture Data B Update interrupt handler.
 **********************************************************************************************************************/
void dsmif_cdbupdn_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Determine the channel associated with this interrupt request. */
    uint32_t ielsr_offset = (uint32_t) ELC_EVENT_DSMIF0_CDBUPD0 +
                            ((ELC_EVENT_DSMIF1_CDBUPD0 - ELC_EVENT_DSMIF0_CDBUPD0) * p_instance_ctrl->p_cfg->unit);
    uint32_t channel = R_ICU->IELSR_b[irq].IELS - ielsr_offset;

    /* Clear the channel status flag. */
    p_instance_ctrl->p_reg->DSCSCR = 1U << (R_DSMIF0_DSCSCR_CLRCBUF_Pos + channel);

    r_dsmif_call_callback(p_instance_ctrl, ADC_EVENT_CAPTURE_B, (adc_channel_t) (ADC_CHANNEL_CAPTURE_B_MASK | channel));

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * DSMIFn Common Current data update interrupt handler.
 **********************************************************************************************************************/
void dsmif_cdupd_com_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Clear all data update flags. */
    p_instance_ctrl->p_reg->DSCSCR = (R_DSMIF0_DSCSCR_CLRDUF_Msk << 0) |
                                     (R_DSMIF0_DSCSCR_CLRDUF_Msk << 1) |
                                     (R_DSMIF0_DSCSCR_CLRDUF_Msk << 2);

    r_dsmif_call_callback(p_instance_ctrl, ADC_EVENT_CONVERSION_COMPLETE, (adc_channel_t) 0);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * DSMIFn Common Capture Data A Update interrupt handler.
 **********************************************************************************************************************/
void dsmif_cdaupd_com_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Clear all capture a flags. */
    p_instance_ctrl->p_reg->DSCSCR = (R_DSMIF0_DSCSCR_CLRCAUF_Msk << 0) |
                                     (R_DSMIF0_DSCSCR_CLRCAUF_Msk << 1) |
                                     (R_DSMIF0_DSCSCR_CLRCAUF_Msk << 2);

    r_dsmif_call_callback(p_instance_ctrl, ADC_EVENT_CAPTURE_A, (adc_channel_t) 0);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * DSMIFn Common Capture Data B Update interrupt handler.
 **********************************************************************************************************************/
void dsmif_cdbupd_com_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Clear all capture b flags. */
    p_instance_ctrl->p_reg->DSCSCR = (R_DSMIF0_DSCSCR_CLRCBUF_Msk << 0) |
                                     (R_DSMIF0_DSCSCR_CLRCBUF_Msk << 1) |
                                     (R_DSMIF0_DSCSCR_CLRCBUF_Msk << 2);

    r_dsmif_call_callback(p_instance_ctrl, ADC_EVENT_CAPTURE_B, (adc_channel_t) 0);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * DSMIFn Common Error interrupt handler.
 **********************************************************************************************************************/
void dsmif_err_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    dsmif_instance_ctrl_t * p_instance_ctrl = (dsmif_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    r_dsmif_call_callback(p_instance_ctrl, ADC_EVENT_CONVERSION_ERROR, (adc_channel_t) 0);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
