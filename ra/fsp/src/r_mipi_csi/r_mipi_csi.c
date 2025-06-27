/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_mipi_csi.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MIPI_CSI_OPEN    (0x4D504943)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * mipi_csi_prv_ns_callback)(mipi_csi_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile mipi_csi_prv_ns_callback)(mipi_csi_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const mipi_csi_api_t g_mipi_csi =
{
    .open      = R_MIPI_CSI_Open,
    .close     = R_MIPI_CSI_Close,
    .start     = R_MIPI_CSI_Start,
    .stop      = R_MIPI_CSI_Stop,
    .read      = R_MIPI_CSI_Read,
    .statusGet = R_MIPI_CSI_StatusGet,
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void mipi_csi_rx_isr(void);
void mipi_csi_dl_isr(void);
void mipi_csi_vc_isr(void);
void mipi_csi_pm_isr(void);
void mipi_csi_gst_isr(void);

static void csi_isr_enable(mipi_csi_irq_cfg_t const * irq_cfg, void * p_context);
static void csi_isr_disable(mipi_csi_irq_cfg_t const * irq_cfg);

static void csi_call_callback(mipi_csi_instance_ctrl_t * p_ctrl, mipi_csi_callback_args_t * p_args);

/*******************************************************************************************************************//**
 * @addtogroup MIPI_CSI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Initialize the MIPI CSI peripheral.
 *
 * @retval FSP_SUCCESS                     The channel was successfully opened.
 * @retval FSP_ERR_ASSERTION               One or both of the parameters was NULL.
 * @retval FSP_ERR_ALREADY_OPEN            The instance is already opened.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_CSI_Open (mipi_csi_ctrl_t * const p_api_ctrl, mipi_csi_cfg_t const * const p_cfg)
{
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) p_api_ctrl;

#if MIPI_CSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MIPI_CSI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif
    p_ctrl->p_cfg = p_cfg;

    /* Start clocks to the MIPI CSI peripheral */
    R_BSP_MODULE_START(FSP_IP_MIPI_CSI, 0);

    /* Open MIPI Phy */
    mipi_phy_api_t const * p_phy_api  = p_cfg->p_mipi_phy_instance->p_api;
    mipi_phy_cfg_t const * p_phy_cfg  = p_cfg->p_mipi_phy_instance->p_cfg;
    mipi_phy_ctrl_t      * p_phy_ctrl = p_cfg->p_mipi_phy_instance->p_ctrl;
    fsp_err_t              err        = p_phy_api->open(p_phy_ctrl, p_phy_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /*  Open MIPI CSI */
    R_MIPI_CSI->MCT3_b.RXEN = 0;                                             // Ensure reception is disabled before configuration
    FSP_HARDWARE_REGISTER_WAIT(R_MIPI_CSI->RTST_b.VSRSTS, 0x0);              // Ensure reset not currently in progress - This covers re-opening after stopping reception

    R_MIPI_CSI->MCT0 = p_cfg->ctrl_data.control_0_mask;                      // Module Control Register 0
    R_MIPI_CSI->MCT2 = p_cfg->ctrl_data.control_2_mask;                      // Module Control Register 2
    R_MIPI_CSI->EPCT = p_cfg->option_data.epd_option_0_mask;                 // Efficient Packet Delimter (EPD) settings
    R_MIPI_CSI->EMCT = p_cfg->option_data.epd_option_1_mask;                 // EPD Option settings
    *((uint64_t *) &R_MIPI_CSI->DTEL) = p_cfg->option_data.data_type_enable; // Receive Data Type Enable
    R_MIPI_CSI->GSCT = p_cfg->ctrl_data.short_packet_control_mask;           // Short Data Packet Control

    R_MIPI_CSI->RXIE  = p_cfg->interrupt_cfg.receive_enable_mask;
    R_MIPI_CSI->DLIE0 = p_cfg->interrupt_cfg.data_lane_enable_mask[0];
    R_MIPI_CSI->DLIE1 = p_cfg->interrupt_cfg.data_lane_enable_mask[1];
    uint32_t volatile * base_addr = (uint32_t volatile *) &R_MIPI_CSI->VCIE0;
    for (uint32_t i = 0; i < 16; i++)
    {
        base_addr[0x10 / 4 * i] = (p_cfg->interrupt_cfg.virtual_channel_enable_mask)[i];
    }

    R_MIPI_CSI->PMIE = p_cfg->interrupt_cfg.power_management_enable_mask;
    R_MIPI_CSI->GSIE = p_cfg->interrupt_cfg.short_packet_enable_mask;

    p_ctrl->p_callback_memory = NULL;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    csi_isr_enable(&p_cfg->interrupt_cfg.receive_cfg, (void *) p_ctrl);
    csi_isr_enable(&p_cfg->interrupt_cfg.data_lane_cfg, (void *) p_ctrl);
    csi_isr_enable(&p_cfg->interrupt_cfg.virtual_channel_cfg, (void *) p_ctrl);
    csi_isr_enable(&p_cfg->interrupt_cfg.power_management_cfg, (void *) p_ctrl);
    csi_isr_enable(&p_cfg->interrupt_cfg.short_packet_cfg, (void *) p_ctrl);

    /* Mark control block as opened */
    p_ctrl->open = MIPI_CSI_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Close MIPI CSI and display data instances, disable interrupts, and power-off the module.
 *
 * @retval   FSP_SUCCESS           The channel is successfully closed.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Instance is not open.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_CSI_Close (mipi_csi_ctrl_t * const p_api_ctrl)
{
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) p_api_ctrl;

#if MIPI_CSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MIPI_CSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mipi_csi_cfg_t const * const p_cfg = p_ctrl->p_cfg;
    csi_isr_disable(&p_cfg->interrupt_cfg.receive_cfg);
    csi_isr_disable(&p_cfg->interrupt_cfg.data_lane_cfg);
    csi_isr_disable(&p_cfg->interrupt_cfg.virtual_channel_cfg);
    csi_isr_disable(&p_cfg->interrupt_cfg.power_management_cfg);
    csi_isr_disable(&p_cfg->interrupt_cfg.short_packet_cfg);

    /* Close MIPI Phy */
    mipi_phy_api_t const * p_phy_api  = p_cfg->p_mipi_phy_instance->p_api;
    mipi_phy_ctrl_t      * p_phy_ctrl = p_cfg->p_mipi_phy_instance->p_ctrl;
    fsp_err_t              err        = p_phy_api->close(p_phy_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set control block to closed */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Start video output.
 * Initialize Video Output Registers
 * Perform sequence steps 3 to 5 from section 58.3.6.1 in RA8D1 hardware manual R01UH0995EJ0060.
 *
 * @retval   FSP_SUCCESS                Data is successfully written to the D/A Converter.
 * @retval   FSP_ERR_ASSERTION          p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN           Instance is not open.
 * @retval   FSP_ERR_INVALID_STATE      CSI is already in video mode.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_CSI_Start (mipi_csi_ctrl_t * const p_api_ctrl)
{
#if MIPI_CSI_CFG_PARAM_CHECKING_ENABLE
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(MIPI_CSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(!R_MIPI_CSI->MCT3_b.RXEN, FSP_ERR_INVALID_STATE);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    /* Enable CSI Reception */
    R_MIPI_CSI->MCT3_b.RXEN = 1;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Stop video capture.
 *  - NOTE: Application shall issue stop command to the peripheral and wait at least one full frame before calling
 *          CSI_Stop, after ensuring MIPI CSI reception is no longer active by checking data returned by GetStatus()
 *
 * @retval   FSP_SUCCESS                Data is successfully written to the D/A Converter.
 * @retval   FSP_ERR_ASSERTION          p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN           Instance is not open.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_CSI_Stop (mipi_csi_ctrl_t * const p_api_ctrl)
{
#if MIPI_CSI_CFG_PARAM_CHECKING_ENABLE
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(MIPI_CSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    /*----------------------------------------------------------------------------------------------------
     * Follow procedure identified in Figure 67.2 (R01UH1064EJ0100)
     *  - NOTE: Application shal stop transmission fromperipheral before calling MIPI_CSI Stop function.
     *----------------------------------------------------------------------------------------------------*/
    FSP_ASSERT(R_MIPI_CSI->RXSC_b.RACTDETC); // Reception must not be active when calling Stop(). See note above.
    R_MIPI_CSI->MCT3_b.RXEN  = 0;
    R_MIPI_CSI->RTCT_b.VSRST = 1;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Provide information about current MIPI CSI status.
 *
 * @retval   FSP_SUCCESS               Information read successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_CSI_StatusGet (mipi_csi_ctrl_t * const p_api_ctrl, mipi_csi_status_t * p_status)
{
#if MIPI_CSI_CFG_PARAM_CHECKING_ENABLE
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_status);
    FSP_ERROR_RETURN(MIPI_CSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    p_status->state             = R_MIPI_CSI->RXST_b.RACTDET ? MIPI_CSI_STATE_RECEIVING : MIPI_CSI_STATE_IDLE;
    R_MIPI_CSI->RXSC_b.RACTDETC = 1;   // Clear RX active flag

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Read Short Packet Data From FIFO.
 *
 * @retval   FSP_SUCCESS               Information read successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 * @retval   FSP_ERR_UNDERFLOW         Packet FIFO empty.
 **********************************************************************************************************************/
fsp_err_t R_MIPI_CSI_Read (mipi_csi_ctrl_t * const p_api_ctrl, mipi_csi_short_packet_t * p_data)
{
#if MIPI_CSI_CFG_PARAM_CHECKING_ENABLE
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_data);
    FSP_ERROR_RETURN(MIPI_CSI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    fsp_err_t err = FSP_ERR_UNDERFLOW;
    if (R_MIPI_CSI->GSST_b.PNUM)
    {
        R_MIPI_CSI->GSIU_b.FINC = 1;
        p_data->mask            = R_MIPI_CSI->GSHT;
        err = FSP_SUCCESS;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MIPI_CSI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Calls user callback
 **********************************************************************************************************************/
static void csi_call_callback (mipi_csi_instance_ctrl_t * p_ctrl, mipi_csi_callback_args_t * p_args)
{
    mipi_csi_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    mipi_csi_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
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
        mipi_csi_prv_ns_callback p_callback = (mipi_csi_prv_ns_callback) (p_ctrl->p_callback);
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

/*******************************************************************************************************************//**
 * Private helper functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Enable the specified ISR and add the control structure to the ISR context lookup table.
 *
 * @param[in]     irq_cfg    Pointer to interrupt configuration structure
 * @param[in]     p_ctrl     Pointer to MIPI CSI instance control block
 **********************************************************************************************************************/
static void csi_isr_enable (mipi_csi_irq_cfg_t const * irq_cfg, void * p_context)
{
    R_BSP_IrqCfgEnable(irq_cfg->irq, irq_cfg->ipl, p_context);
}

/***********************************************************************************************************************
 * Disable the specified ISR
 *
 * @param[in]     irq_cfg    Pointer to interrupt configuration structure
 **********************************************************************************************************************/
static void csi_isr_disable (mipi_csi_irq_cfg_t const * irq_cfg)
{
    R_BSP_IrqDisable(irq_cfg->irq);
    R_FSP_IsrContextSet(irq_cfg->irq, NULL);
}

/***********************************************************************************************************************
 * Interrupt Service Routines
 **********************************************************************************************************************/

/*----------------------------------------------------------------------------------------------------
 * Receive Interrupt Service Routine
 *--------------------------------------------------------------------------------------------------*/
void mipi_csi_rx_isr (void)
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    mipi_csi_callback_args_t args;
    args.event     = MIPI_CSI_EVENT_FRAME_DATA;
    args.event_idx = 0xFF;
    args.event_data.receive_status.mask = R_MIPI_CSI->RXST;
    args.p_context = p_ctrl->p_context;

    R_MIPI_CSI->RXSC = (args.event_data.receive_status.mask & R_MIPI_CSI_RXSC_RACTDETC_Msk); // Only clear RACTDETC (receive active detect)
    R_BSP_IrqStatusClear(irq);

    csi_call_callback(p_ctrl, &args);
}

/*----------------------------------------------------------------------------------------------------
 * Data Lane Interrupt Service Routine
 *--------------------------------------------------------------------------------------------------*/
void mipi_csi_dl_isr (void)
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    mipi_csi_interrupt_status_t interrupt_status = {.mask = R_MIPI_CSI->MIST};
    uint32_t lane0_status = R_MIPI_CSI->DLST0;
    uint32_t lane1_status = R_MIPI_CSI->DLST1;
    R_MIPI_CSI->DLSC0 = (lane0_status & ~R_MIPI_CSI_DLST0_ULP_Msk); // ULPS Escape has no clear bit
    R_MIPI_CSI->DLSC1 = (lane1_status & ~R_MIPI_CSI_DLST0_ULP_Msk); // ULPS Escape has no clear bit
    R_BSP_IrqStatusClear(irq);

    mipi_csi_callback_args_t args;
    args.p_context = p_ctrl->p_context;
    args.event     = MIPI_CSI_EVENT_DATA_LANE;
    if (interrupt_status.bits.data_lane_0)
    {
        args.event_idx = 0;
        args.event_data.data_lane_status.mask = lane0_status;
        csi_call_callback(p_ctrl, &args);
    }

    if (interrupt_status.bits.data_lane_1)
    {
        args.event_idx = 1;
        args.event_data.data_lane_status.mask = lane1_status;
        csi_call_callback(p_ctrl, &args);
    }
}

/*----------------------------------------------------------------------------------------------------
 * Virtual Channel Interrupt Service Routine
 *--------------------------------------------------------------------------------------------------*/
void mipi_csi_vc_isr (void)
{
#define MIPI_CSI_VC_GENERIC_ERRORS    (R_MIPI_CSI_VCST0_MLF_Msk | R_MIPI_CSI_VCST0_ECD_Msk)

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    mipi_csi_interrupt_status_t interrupt_status = {.mask = R_MIPI_CSI->MIST};
    uint32_t                 generic_errors_u32  = 0;
    mipi_csi_callback_args_t args;
    args.event     = MIPI_CSI_EVENT_VIRTUAL_CHANNEL;
    args.p_context = p_ctrl->p_context;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (interrupt_status.bits.virtual_channel.mask & (1 << i))
        {
            uint32_t volatile * p_vc_status   = (uint32_t volatile *) ((&R_MIPI_CSI->VCST0) + 0x10 / 4 * i);
            uint32_t volatile * p_vc_clear    = (uint32_t volatile *) ((&R_MIPI_CSI->VCSC0) + 0x10 / 4 * i);
            uint32_t            vc_status_u32 = *p_vc_status;
            *p_vc_clear = vc_status_u32; // Clear error flags for this channel

            /* Malformed packet and 2-Bit ECC errors are applied to all virtual channels */
            generic_errors_u32 |= vc_status_u32 & MIPI_CSI_VC_GENERIC_ERRORS;
            vc_status_u32      &= ~MIPI_CSI_VC_GENERIC_ERRORS;

            args.event_idx = i;
            args.event_data.virtual_channel_status.mask = vc_status_u32;
            csi_call_callback(p_ctrl, &args);
        }
    }

    R_BSP_IrqStatusClear(irq);
    args.event_idx = 0xFF;
    args.event_data.virtual_channel_status.mask = generic_errors_u32;
    csi_call_callback(p_ctrl, &args);

#undef MIPI_CSI_VC_GENERIC_ERRORS
}

/*----------------------------------------------------------------------------------------------------
 * Power Management Interrupt Service Routine
 *--------------------------------------------------------------------------------------------------*/
void mipi_csi_pm_isr (void)
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    mipi_csi_callback_args_t args;
    args.event     = MIPI_CSI_EVENT_POWER;
    args.event_idx = 0xFF;
    args.event_data.power_status.mask = R_MIPI_CSI->PMST;
    args.p_context   = p_ctrl->p_context;
    R_MIPI_CSI->PMSC = args.event_data.power_status.mask & 0xFF; // Only lower 8 bits have status to clear

    R_BSP_IrqStatusClear(irq);

    csi_call_callback(p_ctrl, &args);
}

/*----------------------------------------------------------------------------------------------------
 * Generic Short Packet Interrupt Service Routine
 *--------------------------------------------------------------------------------------------------*/
void mipi_csi_gst_isr (void)
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    mipi_csi_instance_ctrl_t * p_ctrl = (mipi_csi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    mipi_csi_callback_args_t args;
    args.event     = MIPI_CSI_EVENT_SHORT_PACKET_FIFO;
    args.event_idx = 0xFF;
    args.event_data.fifo_status.mask = R_MIPI_CSI->GSST;
    args.p_context = p_ctrl->p_context;

    R_MIPI_CSI->GSSC = (args.event_data.fifo_status.mask & R_MIPI_CSI_GSST_GOV_Msk); // Only clear GOVC (overflow status)

    R_BSP_IrqStatusClear(irq);

    csi_call_callback(p_ctrl, &args);
}
