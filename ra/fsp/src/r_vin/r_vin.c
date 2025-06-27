/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_vin.h"
#include "r_vin_device_types.h"
#include "r_capture_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define VIN_OPEN    (0x5256494E)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * vin_prv_ns_callback)(capture_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile vin_prv_ns_callback)(capture_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const capture_api_t g_capture_on_vin =
{
    .open         = R_VIN_Open,
    .close        = R_VIN_Close,
    .captureStart = R_VIN_CaptureStart,
    .statusGet    = R_VIN_StatusGet,
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void        vin_status_isr(void);
void        vin_error_isr(void);
static void vin_common_isr(vin_event_t event);

static fsp_err_t vin_stop(vin_instance_ctrl_t * const p_ctrl);
static void      vin_isr_enable(vin_irq_cfg_t const * irq_cfg, void * p_context);
static void      vin_isr_disable(vin_irq_cfg_t const * irq_cfg);

static void vin_call_callback(vin_instance_ctrl_t * p_ctrl, capture_callback_args_t * p_args);

/*******************************************************************************************************************//**
 * @addtogroup VIN
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Initialize the VIN peripheral.
 *
 * @retval FSP_SUCCESS                     The channel was successfully opened.
 * @retval FSP_ERR_ASSERTION               One or both of the parameters was NULL.
 * @retval FSP_ERR_ALREADY_OPEN            The instance is already opened.
 **********************************************************************************************************************/
fsp_err_t R_VIN_Open (capture_ctrl_t * const p_api_ctrl, capture_cfg_t const * const p_cfg)
{
    vin_instance_ctrl_t * p_ctrl = (vin_instance_ctrl_t *) p_api_ctrl;

#if VIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_cfg);
    FSP_ASSERT(p_cfg->p_extend);
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(VIN_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif
    p_ctrl->p_cfg = p_cfg;
    vin_extended_cfg_t const * p_extend = p_cfg->p_extend;

    /* Start clocks to the VIN peripheral */
    R_BSP_MODULE_START(FSP_IP_MIPI_CSI, 0);

    /* Ensure VIN Module is in a good state for configuration */
    R_VIN->FC_b.CC = 0;                                                                    // Ensure Continuous Capture and Startup are disabled before starting configuration
    R_VIN->MC      = p_extend->input_ctrl.cfg_mask & ~(R_VIN_MC_ST_Msk | R_VIN_MC_ME_Msk); // Main control register (Disable start bit and module enable)

    R_VIN->CSI_IFMD = p_extend->input_ctrl.csi_mode_mask;
    R_VIN->CSIFLD   = p_extend->input_ctrl.csi_detect_mask;
    R_VIN->DMR      = p_extend->conversion_ctrl.data_mode_mask;
    R_VIN->SLPRC    = p_extend->input_ctrl.preclip.line_start;
    R_VIN->ELPRC    = p_extend->input_ctrl.preclip.line_end;
    R_VIN->SPPRC    = p_extend->input_ctrl.preclip.pixel_start;
    R_VIN->EPPRC    = p_extend->input_ctrl.preclip.pixel_end;
    R_VIN->IS       = p_extend->input_ctrl.image_stride;
    R_VIN->MB1      = (uint32_t) p_extend->output_ctrl.image_buffer[0];
    R_VIN->MB2      = (uint32_t) p_extend->output_ctrl.image_buffer[1];
    R_VIN->MB3      = (uint32_t) p_extend->output_ctrl.image_buffer[2];
    R_VIN->UVAOF    = (uint32_t) p_extend->conversion_data.uv_address;

    R_VIN->MC_b.BPS = p_extend->input_ctrl.cfg_bits.color_space_convert_bypass; // Set color space bypass register after other settings, according to Figure 68.17 (R01UH1064EJ0110)

    R_VIN->CSCE1 = p_extend->conversion_data.yc_rgb_conversion_setting_1_mask;
    R_VIN->CSCE2 = p_extend->conversion_data.yc_rgb_conversion_setting_2_mask;
    R_VIN->CSCE3 = p_extend->conversion_data.yc_rgb_conversion_setting_3_mask;
    R_VIN->CSCE4 = p_extend->conversion_data.yc_rgb_conversion_setting_4_mask;

    R_VIN->YCCR1 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[0].setting_1_mask;
    R_VIN->YCCR2 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[0].setting_2_mask;
    R_VIN->YCCR3 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[0].setting_3_mask;

    R_VIN->CBCCR1 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[1].setting_1_mask;
    R_VIN->CBCCR2 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[1].setting_2_mask;
    R_VIN->CBCCR3 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[1].setting_3_mask;

    R_VIN->CRCCR1 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[2].setting_1_mask;
    R_VIN->CRCCR2 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[2].setting_2_mask;
    R_VIN->CRCCR3 = p_extend->conversion_data.rgb_to_yuv_conversion_settings[2].setting_3_mask;

    R_VIN->MC_b.YUV444 = p_extend->input_ctrl.cfg_bits.yuv444_conversion; // Set YUV444 conversion register after other settings, according to Figure 68.17 (R01UH1064EJ0110)
    R_VIN->MC_b.DC     = p_extend->input_ctrl.cfg_bits.dithering_mode;    // Set Dithering mode register after other settings, according to Figure 68.17 (R01UH1064EJ0110)

    R_VIN->UDS_PASS_BWIDTH = p_extend->conversion_data.uds_bwidth_mask;
    R_VIN->UDS_CLIP_SIZE   = p_extend->conversion_data.uds_clipping_mask;
    R_VIN->MC_b.SCLE       = p_extend->input_ctrl.cfg_bits.scaling_enable;
    R_VIN->UDS_CTRL        = p_extend->conversion_data.uds_ctrl_mask;

    R_VIN->IE = p_extend->interrupt_cfg.status_enable_mask;
    R_VIN->SI = p_extend->interrupt_cfg.scanline_compare_value;

    p_ctrl->p_callback_memory = NULL;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    vin_isr_enable(&p_extend->interrupt_cfg.status, (void *) p_ctrl);
    vin_isr_enable(&p_extend->interrupt_cfg.error, (void *) p_ctrl);

    /* Open MIPI CSI */
    mipi_csi_api_t const * p_csi_api  = p_extend->p_mipi_csi_instance->p_api;
    mipi_csi_cfg_t const * p_csi_cfg  = p_extend->p_mipi_csi_instance->p_cfg;
    mipi_csi_ctrl_t      * p_csi_ctrl = p_extend->p_mipi_csi_instance->p_ctrl;
    fsp_err_t              err        = p_csi_api->open(p_csi_ctrl, p_csi_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err)

    /* Mark control block as opened */
    p_ctrl->open = VIN_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Close VIN and display data instances, disable interrupts, and power-off the module.
 *  - NOTE: Application shall issue stop command to the peripheral and wait at least one full frame before calling
 *          CSI_Stop, after ensuring MIPI CSI reception is no longer active by checking data returned by MIPI_CSI GetStatus()
 *
 * @retval   FSP_SUCCESS           The channel is successfully closed.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Instance is not open.
 **********************************************************************************************************************/
fsp_err_t R_VIN_Close (capture_ctrl_t * const p_api_ctrl)
{
    vin_instance_ctrl_t * p_ctrl = (vin_instance_ctrl_t *) p_api_ctrl;

#if VIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_ctrl->p_cfg);
    FSP_ASSERT(p_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(VIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    capture_cfg_t const * const p_cfg    = p_ctrl->p_cfg;
    vin_extended_cfg_t const  * p_extend = p_cfg->p_extend;

    fsp_err_t err = vin_stop(p_ctrl);
    FSP_ERROR_LOG(err);
    FSP_PARAMETER_NOT_USED(err);       /* Suppress dead store when FSP_ERROR_LOG is not enabled */

    /* Close MIPI CSI */
    mipi_csi_api_t const * p_csi_api  = p_extend->p_mipi_csi_instance->p_api;
    mipi_csi_ctrl_t      * p_csi_ctrl = p_extend->p_mipi_csi_instance->p_ctrl;
    err = p_csi_api->close(p_csi_ctrl);
    FSP_ERROR_LOG(err);

    /* Set control block to closed */
    p_ctrl->open = 0U;

    vin_isr_disable(&p_extend->interrupt_cfg.status);
    vin_isr_disable(&p_extend->interrupt_cfg.error);

    /* Stop clocks to the MIPI CSI peripheral */
    R_BSP_MODULE_STOP(FSP_IP_MIPI_CSI, 0);

    return err;
}

/******************************************************************************************************************//**
 * Start video capture.
 *  - NOTE: For best results, camera should not be transmitting data until after VIN capture start has been called.
 *
 * @retval   FSP_SUCCESS                Data is successfully written to the D/A Converter.
 * @retval   FSP_ERR_ASSERTION          p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN           Instance is not open.
 * @retval   FSP_ERR_IN_USE             The physical interface is currently in use.
 * @retval   FSP_ERR_INVALID_STATE      VIN is already in video mode.
 * @retval   FSP_ERR_UNSUPPORTED        p_buffer parameter is not supported.
 **********************************************************************************************************************/
fsp_err_t R_VIN_CaptureStart (capture_ctrl_t * const p_api_ctrl, uint8_t * const p_buffer)
{
    vin_instance_ctrl_t * p_ctrl = (vin_instance_ctrl_t *) p_api_ctrl;
#if VIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_ctrl->p_cfg);
    FSP_ASSERT(p_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(VIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(!R_VIN->MC_b.ME, FSP_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(!R_VIN->FC_b.CC, FSP_ERR_INVALID_STATE);
 #if !defined(VIN_CFG_USE_RUNTIME_BUFFER)
    FSP_ERROR_RETURN(!p_buffer, FSP_ERR_UNSUPPORTED);
 #endif
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    capture_cfg_t const * const p_cfg    = p_ctrl->p_cfg;
    vin_extended_cfg_t const  * p_extend = p_cfg->p_extend;

    /*----------------------------------------------------------------------------------------------------
     * Set Capture buffers if not provided by configuration
     *  - Note: It is highly recommended to configure capture buffers via FSP configuration tool
     *----------------------------------------------------------------------------------------------------*/
#if defined(VIN_CFG_USE_RUNTIME_BUFFER)
    R_VIN->MB1 = (uint32_t) p_buffer;
    R_VIN->MB2 = (uint32_t) p_buffer;
    R_VIN->MB3 = (uint32_t) p_buffer;
#else
    FSP_PARAMETER_NOT_USED(p_buffer);
#endif

    /* Start VIN */
    R_VIN->MC_b.ST = 0x1;              // Initialize the internal state of VIN
    FSP_REGISTER_READ(R_VIN->MC_b.ST); // Wait at least 10 cycles of aclk (ICLK)
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);
    FSP_REGISTER_READ(R_VIN->MC_b.ST);

    R_VIN->UDS_SCALE = p_extend->conversion_data.uds_scale_mask;

    R_VIN->MC_b.ME = 1;                // Start VIN
    R_VIN->FC_b.CC = 1;                // Put VIN in continuous frame capture mode waiting for video input

    /* Start MIPI CSI */
    mipi_csi_api_t const * p_csi_api  = p_extend->p_mipi_csi_instance->p_api;
    mipi_csi_ctrl_t      * p_csi_ctrl = p_extend->p_mipi_csi_instance->p_ctrl;
    fsp_err_t              err        = p_csi_api->start(p_csi_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err)

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Provide information about current VIN status.
 *
 * @retval   FSP_SUCCESS               Information read successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 **********************************************************************************************************************/
fsp_err_t R_VIN_StatusGet (capture_ctrl_t * const p_api_ctrl, capture_status_t * p_status)
{
#if VIN_CFG_PARAM_CHECKING_ENABLE
    vin_instance_ctrl_t * p_ctrl = (vin_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(VIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif
    uint32_t ** buffer_pointer = (uint32_t **) (&R_VIN->MB1);

    p_status->data_size = R_VIN->LC;
    p_status->p_buffer  = (R_VIN->MS_b.FBS >= 0x3) ? NULL : *(buffer_pointer + R_VIN->MS_b.FBS); // Buffer currently in use
    p_status->state     = R_VIN->MC_b.ME ? CAPTURE_STATE_BUSY : CAPTURE_STATE_IDLE;              // Module enabled but no capture in progress
    p_status->state     = R_VIN->MS_b.CA ? CAPTURE_STATE_IN_PROGRESS : p_status->state;          // Module enabled and capture in progress

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup VIN)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Private helper functions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Capture Stop - Follow procedure outlined in Figure 68.18 (R01UH1064EJ0100)
 **********************************************************************************************************************/
static fsp_err_t vin_stop (vin_instance_ctrl_t * const p_ctrl)
{
    capture_cfg_t const * const p_cfg    = p_ctrl->p_cfg;
    vin_extended_cfg_t const  * p_extend = p_cfg->p_extend;

    fsp_err_t err = R_VIN->MC_b.ME ? FSP_SUCCESS : FSP_ERR_INVALID_STATE;
    FSP_ERROR_LOG(err);
    FSP_PARAMETER_NOT_USED(err);       /* Suppress dead store when FSP_ERROR_LOG is not enabled */

    R_VIN->MC_b.ME = 0;                // Stop VIN
    R_VIN->FC_b.CC = 0;                // Disable VIN continuous capture mode

    if (R_VIN->MS_b.CA || R_VIN->MTCSTOP_b.OUTSTAND)
    {
        FSP_ERROR_LOG(FSP_ERR_IN_USE);
    }

    /* Stop MIPI CSI */
    mipi_csi_api_t const * p_csi_api  = p_extend->p_mipi_csi_instance->p_api;
    mipi_csi_ctrl_t      * p_csi_ctrl = p_extend->p_mipi_csi_instance->p_ctrl;
    err = p_csi_api->stop(p_csi_ctrl);
    FSP_ERROR_LOG(err);

    R_VIN->MC_b.SCLE = 0;              // Disable UDS scaling

    return err;
}

/***********************************************************************************************************************
 * Enable the specified ISR and add the control structure to the ISR context lookup table.
 **********************************************************************************************************************/
static void vin_isr_enable (vin_irq_cfg_t const * irq_cfg, void * p_context)
{
    R_BSP_IrqCfgEnable(irq_cfg->irq, irq_cfg->ipl, p_context);
}

/***********************************************************************************************************************
 * Disable the specified ISR
 **********************************************************************************************************************/
static void vin_isr_disable (vin_irq_cfg_t const * irq_cfg)
{
    R_BSP_IrqDisable(irq_cfg->irq);
    R_FSP_IsrContextSet(irq_cfg->irq, NULL);
}

/***********************************************************************************************************************
 * Interrupt Service Routines
 **********************************************************************************************************************/

/*----------------------------------------------------------------------------------------------------
 * Status Interrupt Service Routine
 *--------------------------------------------------------------------------------------------------*/
void vin_status_isr (void)
{
    vin_common_isr(VIN_EVENT_NOTIFY);
}

/*----------------------------------------------------------------------------------------------------
 * Error Interrupt Service Routine
 *--------------------------------------------------------------------------------------------------*/
void vin_error_isr (void)
{
    vin_common_isr(VIN_EVENT_ERROR);
}

/*----------------------------------------------------------------------------------------------------
 * Common ISR Handler
 *--------------------------------------------------------------------------------------------------*/
void vin_common_isr (vin_event_t event)
{
    capture_callback_args_t args;
    IRQn_Type               irq              = R_FSP_CurrentIrqGet();
    vin_instance_ctrl_t   * p_ctrl           = (vin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    vin_module_status_t     module_status    = (vin_module_status_t) R_VIN->MS;
    vin_interrupt_status_t  interrupt_status = (vin_interrupt_status_t) R_VIN->INTS;
    args.event            = event;
    args.event_status     = module_status.mask;
    args.interrupt_status = interrupt_status.mask;
    args.p_buffer         = NULL;
    if (interrupt_status.bits.frame_complete)
    {
        uint32_t ** buffer_pointer = (uint32_t **) (&R_VIN->MB1);
        args.p_buffer = (uint8_t *) ((R_VIN->MS_b.FBS >= 0x3) ? NULL : *(buffer_pointer + R_VIN->MS_b.FMS)); // Buffer currently in use
    }

    args.p_context = p_ctrl->p_context;

    R_VIN->INTS = interrupt_status.mask | (R_VIN_INTS_FOS_Msk | R_VIN_INTS_ARES_Msk | R_VIN_INTS_FIS2_Msk); // FOS, ARES, FIS2 are cleared by writing '1'. Other bits are status/state, updated by the module.
    R_BSP_IrqStatusClear(irq);
    vin_call_callback(p_ctrl, &args);
}

/***********************************************************************************************************************
 * Calls user callback
 *
 * @param[in]     p_ctrl     Pointer to VIN instance control block
 * @param[in]     p_args     Pointer to arguments on stack
 **********************************************************************************************************************/
static void vin_call_callback (vin_instance_ctrl_t * p_ctrl, capture_callback_args_t * p_args)
{
    capture_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    capture_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = p_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args_memory;

        /* Copy the stacked args to callback memory */
        *p_args_memory = *p_args;
    }

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args_memory);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        vin_prv_ns_callback p_callback = (vin_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args_memory);
    }
#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args_memory);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}
