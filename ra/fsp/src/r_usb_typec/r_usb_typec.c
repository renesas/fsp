/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "r_usb_typec.h"
#include "r_usb_typec_api.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define USB_TYPEC_OPEN                           (('U' << 24U) | ('T' << 16U) | ('P' << 8U) | ('C' << 0U))

/* TCC (Type C Control) Register */
#define USB_TYPEC_TCC_ENB                        (0x00000001U) /* b0 : Connection State Machine Enable */
#define USB_TYPEC_TCC_RESET                      (0x80000000U) /* b31: Type C Software Reset */

/* MEC (Mode Setting and State Control) Register */
#define USB_TYPEC_MEC_MODE                       (0x00000001U) /* b0 : Connection State Machine Enable */
#define USB_TYPEC_MEC_PMODE_MASK                 (0x00000006U) /* b2-b1 : Source Current Detection Mode */
#define USB_TYPEC_MEC_PMODE_DEFAULT              (0x00000000U) /* Detect Default USB Source */
#define USB_TYPEC_MEC_PMODE_DEFAULT_1_5A         (0x00000002U) /* Detect Default USB Source and 1.5A Source */
#define USB_TYPEC_MEC_PMODE_DEFAULT_1_5A_3_0A    (0x00000004U) /* Detect Default USB Source, 15A and 3.0A Source */
#define USB_TYPEC_MEC_GD                         (0x00010000U) /* b16 : Direct Connection State to Disable State */
#define USB_TYPEC_MEC_GUS                        (0x00020000U) /* b17 : Direct Connection State to Unattached_SNK */

/* CCC (CC-PHY Control) Register */
#define USB_TYPEC_CCC_RD                         (0x00000001U) /* b0  : RD Control */
#define USB_TYPEC_CCC_ZOPEN                      (0x00000002U) /* b1  : zOpen Control */
#define USB_TYPEC_CCC_CCSEL                      (0x00000100U) /* b8  : Selection of CC */
#define USB_TYPEC_CCC_VRAEN                      (0x00010000U) /* b16 : vRa Detection Circuit Enable */
#define USB_TYPEC_CCC_VRD1_5EN                   (0x00020000U) /* b17 : vRd-1.5 Detection Circuit Enable */
#define USB_TYPEC_CCC_VRD3_0EN                   (0x00040000U) /* b18 : vRd-3.0 Detection Circuit Enable */
#define USB_TYPEC_CCC_PDOWN                      (0x80000000U) /* b31 : CC-PHY Power Down Control */

/* IES (Interrupt Enable Control and Status) Register */
#define USB_TYPEC_IES_ISCN                       (0x00000001U) /* b0  : Interrupt Status of Connection */
#define USB_TYPEC_IES_ISCC                       (0x00000010U) /* b4  : Interrupt Status of CC */
#define USB_TYPEC_IES_ISVBUS                     (0x00000020U) /* b5  : Interrupt Status of VBUS */
#define USB_TYPEC_IES_ISVRA                      (0x00008000U) /* b15 : Interrupt Status of VRA */
#define USB_TYPEC_IES_CIEN                       (0x00010000U) /* b16 : CC Interrupt Enable */
#define USB_TYPEC_IES_CCIEN                      (0x00100000U) /* b20 : CC Interrupt Enable */
#define USB_TYPEC_IES_VBUSIEN                    (0x00200000U) /* b21 : VBUS Interrupt Enable */
#define USB_TYPEC_IES_VRAIEN                     (0x80000000U) /* b31 : VRA Interrupt Enable */

/* TCS (Type-CC Connection State and Status) Register */
#define USB_TYPEC_TCS_SRCD                       (0x00000001U) /* b0   : Interrupt Status of Connection */
#define USB_TYPEC_TCS_VRD1_5D                    (0x00000002U) /* b1   : Interrupt Status of CC (Power1.5 Source is Detected) */
#define USB_TYPEC_TCS_VRD3_0D                    (0x00000004U) /* b2   : Interrupt Status of CC (Power3.0 Source is Detected) */
#define USB_TYPEC_TCS_PLUG                       (0x00000008U) /* b3   : Connection of Plug Orientation */
#define USB_TYPEC_TCS_CNS_MASK                   (0x000000F0U) /* b7-b4: CC Interrupt Enable */
#define USB_TYPEC_TCS_CNS_DEFAULT                (0x00000000U) /* Disabled */
#define USB_TYPEC_TCS_CNS_UNATTACHED             (0x00000010U) /* Unattached.SNK */
#define USB_TYPEC_TCS_CNS_ATTACHED_WAIT          (0x00000020U) /* AttachedWait.SNK */
#define USB_TYPEC_TCS_CNS_ATTACHED_DEFAULT       (0x00000040U) /* Attache.SNK (PowerDefault.SNK) */
#define USB_TYPEC_TCS_CNS_ATTACHED_1_5           (0x00000050U) /* Attache.SNK (Power1.5.SNK) */
#define USB_TYPEC_TCS_CNS_ATTACHED_3_0           (0x00000060U) /* Attache.SNK (Power3.0.SNK) */
#define USB_TYPEC_TCS_CC1S_MASK                  (0x00000300U) /* b9-b8: Status of CC1 */
#define USB_TYPEC_TCS_CC1S_OPEN                  (0x00000000U) /* SNK.Open */
#define USB_TYPEC_TCS_CC1S_DEFAULT               (0x00000100U) /* SNK.Default */
#define USB_TYPEC_TCS_CC1S_1_5                   (0x00000200U) /* SNK.Power1.5 */
#define USB_TYPEC_TCS_CC1S_3_0                   (0x00000300U) /* SNK.Power3.0 */
#define USB_TYPEC_TCS_CC2S_MASK                  (0x00000C00U) /* b11-b10: Status of CC2 */
#define USB_TYPEC_TCS_CC2S_OPEN                  (0x00000000U) /* b11-b10: Status of CC2 */
#define USB_TYPEC_TCS_CC2S_DEFAULT               (0x00000400U) /* SNK.Default */
#define USB_TYPEC_TCS_CC2S_1_5                   (0x00000800U) /* SNK.Power1.5 */
#define USB_TYPEC_TCS_CC2S_3_0                   (0x00000C00U) /* SNK.Power3.0 */
#define USB_TYPEC_TCS_VBUSS                      (0x00001000U) /* Status of VBUS */

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
void usb_typec_int_isr(void);
void usb_typec_ccs_int_isr(void);

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/
uint32_t g_usb_typec_reg_tcs;

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
const usb_typec_api_t g_typec_on_typec =
{
    .open            = R_USB_TYPEC_Open,
    .close           = R_USB_TYPEC_Close,
    .infoGet         = R_USB_TYPEC_InfoGet,
    .lowPowerModeSet = R_USB_TYPEC_LowPowerModeSet,
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t hw_usb_typec_module_init(usb_typec_cfg_t const * const p_cfg);
static void      hw_usb_typec_module_uninit(void);

/*******************************************************************************************************************//**
 * @addtogroup USB_TYPEC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * @brief Initialize USB Type-C module and USB Type-C driver. Implements @ref usb_typec_api_t::open.
 *
 * @retval  FSP_SUCCESS             Channel opened successfully.
 * @retval  FSP_ERR_NOT_OPEN        USB TYPEC module is not open.
 * @retval  FSP_ERR_ALREADY_OPEN    Control block has already been opened or channel is being used by another
 *                                  instance. Call close() then open() to reconfigure.
 ***********************************************************************************************************************/
fsp_err_t R_USB_TYPEC_Open (usb_typec_ctrl_t * const p_ctrl, usb_typec_cfg_t const * const p_cfg)
{
    fsp_err_t err;
    usb_typec_instance_ctrl_t * p_typec_ctrl = (usb_typec_instance_ctrl_t *) p_ctrl;

    /* Check argument */
#if (USB_TYPEC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);
#endif
    FSP_ERROR_RETURN((USB_TYPEC_OPEN != p_typec_ctrl->open), FSP_ERR_ALREADY_OPEN);

    if (p_cfg->irq_typec_cci >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->irq_typec_cci, p_cfg->ipl_typec_cci, (void *) p_typec_ctrl); /* USBCC CCI enable */
    }

    p_typec_ctrl->module_number = p_cfg->module_number;
    p_typec_ctrl->p_cfg         = (usb_typec_cfg_t *) p_cfg;
    p_typec_ctrl->p_callback    = p_cfg->p_callback;
    p_typec_ctrl->p_context     = p_cfg->p_context;
    p_typec_ctrl->irq_typec_cci = p_cfg->irq_typec_cci;
    p_typec_ctrl->irq_typec_ccs = p_cfg->irq_typec_ccs;
    p_typec_ctrl->ipl_typec_cci = p_cfg->ipl_typec_cci;
    p_typec_ctrl->ipl_typec_ccs = p_cfg->ipl_typec_ccs;

    err = hw_usb_typec_module_init(p_cfg);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, FSP_ERR_NOT_OPEN);

    p_typec_ctrl->open = USB_TYPEC_OPEN;

    return FSP_SUCCESS;
}                                      /* End of function R_USB_HCDC_ECM_Open() */

/********************************************************************************************************************//**
 * @brief Uninitialize USB Type-C module and disable interrupts. Implements @ref usb_typec_api_t::close.
 *
 * @retval  FSP_SUCCESS             Channel successfully closed.
 * @retval  FSP_ERR_NOT_OPEN        USB TYPEC module is not open.
 *
 ***********************************************************************************************************************/
fsp_err_t R_USB_TYPEC_Close (usb_typec_ctrl_t * const p_ctrl)
{
    usb_typec_instance_ctrl_t * p_typec_ctrl = (usb_typec_instance_ctrl_t *) p_ctrl;

    /* Check argument */
#if (USB_TYPEC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_typec_ctrl);
    FSP_ERROR_RETURN(USB_TYPEC_OPEN == p_typec_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable USB Type-C interrupt. */
    NVIC_DisableIRQ(p_typec_ctrl->p_cfg->irq_typec_cci);
    R_FSP_IsrContextSet(p_typec_ctrl->p_cfg->irq_typec_cci, NULL);
    NVIC_DisableIRQ(p_typec_ctrl->p_cfg->irq_typec_ccs);
    R_FSP_IsrContextSet(p_typec_ctrl->p_cfg->irq_typec_ccs, NULL);

    hw_usb_typec_module_uninit();

    p_typec_ctrl->open = 0;

    return FSP_SUCCESS;
}                                      /* End of function R_USB_TYPEC_Close() */

/**************************************************************************//**
 * @brief Get USB Type-C connect Information. Implements @ref usb_typec_api_t::infoGet.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_NOT_OPEN         USB TYPEC module is not open.
 ******************************************************************************/
fsp_err_t R_USB_TYPEC_InfoGet (usb_typec_ctrl_t * const p_ctrl, usb_typec_info_t * p_info)
{
    /* Check argument */
#if (USB_TYPEC_CFG_PARAM_CHECKING_ENABLE)
    usb_typec_instance_ctrl_t * p_typec_ctrl = (usb_typec_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_typec_ctrl);
    FSP_ASSERT(p_info);
    FSP_ERROR_RETURN(USB_TYPEC_OPEN == p_typec_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Set Connection State Mode */
    if (USB_TYPEC_MEC_MODE == (R_USBCC->MEC & USB_TYPEC_MEC_MODE))
    {
        p_info->operation_mode = USB_TYPEC_MODE_USB20_ONLY_SINK; /* USB 2.0 Only Sink Mode */
    }
    else
    {
        p_info->operation_mode = USB_TYPEC_MODE_SINK;            /* Sink Only Mode */
    }

    /* Set Connection of Plug Orientation */
    if (USB_TYPEC_TCS_PLUG == (R_USBCC->TCS & USB_TYPEC_TCS_PLUG))
    {
        p_info->plug = USB_TYPEC_PLUG_CC2_CONNECTED; /* CC2 connected */
    }
    else
    {
        p_info->plug = USB_TYPEC_PLUG_CC1_CONNECTED; /* CC1 connected */
    }

    /* Set Status of VBUS */
    if (USB_TYPEC_TCS_VBUSS == (R_USBCC->TCS & USB_TYPEC_TCS_VBUSS))
    {
        p_info->vbus_status = USB_TYPEC_VBUS_STATUS_ON;  /* VBUS On State */
    }
    else
    {
        p_info->vbus_status = USB_TYPEC_VBUS_STATUS_OFF; /* VBUS Off State */
    }

    /* Set Status of Connection State Machine */
    p_info->connection_status = (usb_typec_connection_status_t) ((R_USBCC->TCS & USB_TYPEC_TCS_CNS_MASK) >> 4);

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief Set IRQ Mode for USB Type-C module by Low Power Mode. Implements @ref usb_typec_api_t::lowPowerModeSet.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_NOT_OPEN         USB TYPEC module is not open.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_TYPEC_LowPowerModeSet (usb_typec_ctrl_t * const p_ctrl, usb_typec_ccs_status_t status)
{
    usb_typec_instance_ctrl_t * p_typec_ctrl = (usb_typec_instance_ctrl_t *) p_ctrl;

    /* Check argument */
#if (USB_TYPEC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_typec_ctrl);
    FSP_ERROR_RETURN(USB_TYPEC_OPEN == p_typec_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(!((USB_TYPEC_CCS_STATUS_ON != status) && (USB_TYPEC_CCS_STATUS_OFF != status)),
                     FSP_ERR_USB_PARAMETER)
#endif

    if (USB_TYPEC_CCS_STATUS_ON == status)
    {
        /* USBCC CCI disable */
        R_BSP_IrqDisable(p_typec_ctrl->irq_typec_cci);

        /* USBCC Status Change Interrupt Software Standby/Snooze */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
        R_ICU->WUPEN2_b.USBCCSWUPEN = 1;
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);

        /* USBCC CCS enable */
        if (p_typec_ctrl->irq_typec_ccs >= 0)
        {
            R_BSP_IrqCfgEnable(p_typec_ctrl->irq_typec_ccs, p_typec_ctrl->ipl_typec_ccs, (void *) p_typec_ctrl); /* USBCC CCS enable */
        }
    }
    else
    {
        /* USBCC CCS disable */
        R_BSP_IrqDisable(p_typec_ctrl->irq_typec_ccs);

        /* USBCC Status Change Interrupt Software Standby/Snooze */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
        R_ICU->WUPEN2_b.USBCCSWUPEN = 0;
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);

        /* USBCC CCI enable */
        if (p_typec_ctrl->irq_typec_cci >= 0)
        {
            R_BSP_IrqCfgEnable(p_typec_ctrl->irq_typec_cci, p_typec_ctrl->ipl_typec_cci, (void *) p_typec_ctrl); /* USBCC CCI enable */
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_TYPEC)
 **********************************************************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_typec_module_init
 * Description     : Initialization of USB TypeC module
 * Arguments       : USB Type-C configuration
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_BUSY      USB is in use.
 ******************************************************************************/
static fsp_err_t hw_usb_typec_module_init (usb_typec_cfg_t const * const p_cfg)
{
    FSP_ERROR_RETURN(0 != R_MSTP->MSTPCRB_b.MSTPB14, FSP_ERR_USB_BUSY)

    /* Enable module start for TypeC module */
    R_BSP_MODULE_START(FSP_IP_USBCC, 0);

    /* Type-C Reset Processing */
    R_USBCC->TCC |= USB_TYPEC_TCC_RESET;
    while (0 != (R_USBCC->TCC & USB_TYPEC_TCC_RESET))
    {
        ;
    }

    /* CC1 and CC2 pin setting */

    /* CCC-PHY not Power Down  */
    R_USBCC->CCC = (R_USBCC->CCC & (~USB_TYPEC_CCC_PDOWN));

    /* Connection State Mode  */
    if (USB_TYPEC_MODE_USB20_ONLY_SINK == p_cfg->usb_typec_mode)
    {
        /* USB 2.0 Only Sink Mode */
        R_USBCC->MEC |= USB_TYPEC_MEC_MODE;
    }

    /* Source Current Detection Mode  */
    if (USB_TYPEC_PMODE_DEFAULT_1_5A_3_0A != p_cfg->usb_typec_pmode)
    {
        /* Detect Default USB Source */
        R_USBCC->MEC &= (~USB_TYPEC_MEC_PMODE_MASK);

        if (USB_TYPEC_PMODE_DEFAULT_1_5A == p_cfg->usb_typec_pmode)
        {
            /* Detect Default USB and 1.5A Source */
            R_USBCC->MEC |= USB_TYPEC_MEC_PMODE_DEFAULT_1_5A;
        }
    }

    /* Read Init TCS */
    g_usb_typec_reg_tcs = R_USBCC->TCS;

    /* Interrupt Enable(CC Status Change, VBUS Status Change, Rp Detection) */
    R_USBCC->IES |= (USB_TYPEC_IES_CCIEN | USB_TYPEC_IES_VBUSIEN | USB_TYPEC_IES_VRAIEN);

    /* Change to Unattached_SNK */
    R_USBCC->MEC |= USB_TYPEC_MEC_GUS;

    return FSP_SUCCESS;
}                                      /* End of function hw_usb_typec_module_init() */

/******************************************************************************
 * Function Name   : hw_usb_typec_module_uninit
 * Description     : Uninitialization of USB TypeC module
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void hw_usb_typec_module_uninit (void)
{
    /* Change to Unattached_SNK */
    R_USBCC->MEC |= USB_TYPEC_MEC_GD;

    /* CCC-PHY Power Down  */
    R_USBCC->CCC |= USB_TYPEC_CCC_PDOWN;

    /* Disable module start for TypeC module */
    R_BSP_MODULE_STOP(FSP_IP_USBCC, 0);
}                                      /* End of function hw_usb_typec_module_uninit() */

/***********************************************************************************************************************
 * Function Name: usb_typec_int_isr
 * Description  : Interrupt handler for usb typec interrupt.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void usb_typec_int_isr (void)
{
    usb_typec_cfg_t         * p_usb_typec_cfg;
    volatile uint32_t         read_reg_typec_ies;
    usb_typec_callback_args_t typec_args;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    usb_typec_instance_ctrl_t * p_instance_ctrl = (usb_typec_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    R_BSP_IrqStatusClear(irq);

    /* Read USB Type-C Reg */
    g_usb_typec_reg_tcs = R_USBCC->TCS;
    read_reg_typec_ies  = R_USBCC->IES;

    /* Clear USB Type-C Interrupt Flag(writing: to set this bit to 0.) */
    R_USBCC->IES = read_reg_typec_ies;

    p_usb_typec_cfg = p_instance_ctrl->p_cfg;

    /* Set APL callback */
    if (NULL != p_usb_typec_cfg->p_callback)
    {
        typec_args.module_number = p_usb_typec_cfg->module_number;
        typec_args.p_context     = p_usb_typec_cfg->p_context;

        /* Set Connection of Plug Orientation */
        if (USB_TYPEC_TCS_PLUG == (g_usb_typec_reg_tcs & USB_TYPEC_TCS_PLUG))
        {
            typec_args.plug = USB_TYPEC_PLUG_CC2_CONNECTED; /* CC2 connected */
        }
        else
        {
            typec_args.plug = USB_TYPEC_PLUG_CC1_CONNECTED; /* CC1 connected */
        }

        /* Set Status of VBUS */
        if (USB_TYPEC_TCS_VBUSS == (g_usb_typec_reg_tcs & USB_TYPEC_TCS_VBUSS))
        {
            typec_args.vbus_status = USB_TYPEC_VBUS_STATUS_ON;  /* VBUS On State */
        }
        else
        {
            typec_args.vbus_status = USB_TYPEC_VBUS_STATUS_OFF; /* VBUS Off State */
        }

        /* Set Status of Connection State Machine */
        typec_args.connection_status =
            (usb_typec_connection_status_t) ((g_usb_typec_reg_tcs & USB_TYPEC_TCS_CNS_MASK) >> 4);

        if (USB_TYPEC_IES_ISCN == (read_reg_typec_ies & USB_TYPEC_IES_ISCN))
        {
            /* Set APL callback */
            typec_args.status = USB_TYPEC_STATUS_ISCN;
            (p_usb_typec_cfg->p_callback)(&typec_args);
        }

        if (USB_TYPEC_IES_ISCC == (read_reg_typec_ies & USB_TYPEC_IES_ISCC))
        {
            /* Set APL callback */
            typec_args.status = USB_TYPEC_STATUS_ISCC;
            (p_usb_typec_cfg->p_callback)(&typec_args);
        }

        if (USB_TYPEC_IES_ISVBUS == (read_reg_typec_ies & USB_TYPEC_IES_ISVBUS))
        {
            /* Set APL callback */
            typec_args.status = USB_TYPEC_STATUS_ISVBUS;
            (p_usb_typec_cfg->p_callback)(&typec_args);
        }

        if (USB_TYPEC_IES_ISVRA == (read_reg_typec_ies & USB_TYPEC_IES_ISVRA))
        {
            /* Set APL callback */
            typec_args.status = USB_TYPEC_STATUS_ISVRA;
            (p_usb_typec_cfg->p_callback)(&typec_args);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}                                      /* End of function usb_typec_int_isr() */

/***********************************************************************************************************************
 * Function Name: usb_typec_ccs_int_isr
 * Description  : Interrupt handler for usb typec status interrupt.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void usb_typec_ccs_int_isr (void)
{
    usb_typec_cfg_t         * p_usb_typec_cfg;
    volatile uint32_t         read_reg_typec_ies;
    usb_typec_callback_args_t typec_args;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    usb_typec_instance_ctrl_t * p_instance_ctrl = (usb_typec_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    R_BSP_IrqStatusClear(irq);

    /* Read USB Type-C Reg */
    g_usb_typec_reg_tcs = R_USBCC->TCS;
    read_reg_typec_ies  = R_USBCC->IES;

    /* Clear USB Type-C Interrupt Flag(writing: to set this bit to 0.) */
    R_USBCC->IES = read_reg_typec_ies & (~(USB_TYPEC_IES_ISCN | USB_TYPEC_IES_ISCC | USB_TYPEC_IES_ISVBUS));

    p_usb_typec_cfg = p_instance_ctrl->p_cfg;

    /* Set APL callback */
    if (NULL != p_usb_typec_cfg->p_callback)
    {
        typec_args.module_number = p_usb_typec_cfg->module_number;
        typec_args.p_context     = p_usb_typec_cfg->p_context;

        /* Set Connection of Plug Orientation */
        if (USB_TYPEC_TCS_PLUG == (g_usb_typec_reg_tcs & USB_TYPEC_TCS_PLUG))
        {
            typec_args.plug = USB_TYPEC_PLUG_CC2_CONNECTED; /* CC2 connected */
        }
        else
        {
            typec_args.plug = USB_TYPEC_PLUG_CC1_CONNECTED; /* CC1 connected */
        }

        /* Set Status of VBUS */
        if (USB_TYPEC_TCS_VBUSS == (g_usb_typec_reg_tcs & USB_TYPEC_TCS_VBUSS))
        {
            typec_args.vbus_status = USB_TYPEC_VBUS_STATUS_ON;  /* VBUS On State */
        }
        else
        {
            typec_args.vbus_status = USB_TYPEC_VBUS_STATUS_OFF; /* VBUS Off State */
        }

        /* Set Status of Connection State Machine */
        typec_args.connection_status =
            (usb_typec_connection_status_t) ((g_usb_typec_reg_tcs & USB_TYPEC_TCS_CNS_MASK) >> 4);

        if (USB_TYPEC_IES_ISVRA == (read_reg_typec_ies & USB_TYPEC_IES_ISVRA))
        {
            /* Set APL callback */
            typec_args.status = USB_TYPEC_STATUS_ISVRA_CCS;
            (p_usb_typec_cfg->p_callback)(&typec_args);
        }
    }
}                                      /* End of function usb_typec_ccs_int_isr() */
