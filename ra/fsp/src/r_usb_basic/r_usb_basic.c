/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_cfg.h"

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include <string.h>

#include "src/driver/inc/r_usb_typedef.h"
#include "src/driver/inc/r_usb_extern.h"
#include "src/hw/inc/r_usb_bitdefine.h"
#include "src/hw/inc/r_usb_reg_access.h"

#if (BSP_CFG_RTOS == 1)
 #include "../../../microsoft/azure-rtos/usbx/common/core/inc/ux_api.h"
 #include "../../../microsoft/azure-rtos/usbx/common/core/inc/ux_system.h"
 #if defined(USB_CFG_HCDC_USE)
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_cdc_acm.h"
 #endif                                /* defined(USB_CFG_HCDC_USE) */
 #if defined(USB_CFG_HMSC_USE)
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_storage.h"
 #endif                                /* defined(USB_CFG_HMSC_USE) */
 #if defined(USB_CFG_HHID_USE)
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_hid.h"
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_hid_keyboard.h"
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_hid_mouse.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */
 #if defined(USB_CFG_HPRN_USE)
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_printer.h"
 #endif                                /* defined(USB_CFG_HPRN_USE) */
 #if defined(USB_CFG_HUVC_USE)
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_video.h"
 #endif                                /* defined(USB_CFG_HUVC_USE) */
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
  #include "../../../microsoft/azure-rtos/usbx/common/usbx_host_classes/inc/ux_host_class_hub.h"
 #endif /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

#if (BSP_CFG_RTOS != 0)
 #include "src/driver/inc/r_usb_cstd_rtos.h"

#endif                                 /*(BSP_CFG_RTOS != 0)*/

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HCDC_USE)
  #include "r_usb_hcdc_api.h"
 #endif                                /* defined(USB_CFG_HCDC_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HHID_USE)
  #include "r_usb_hhid_api.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */
#endif  /* (BSP_CFG_RTOS != 1) */

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HMSC_USE)
  #include "r_usb_hmsc_api.h"
  #include "../r_usb_hmsc/src/inc/r_usb_hmsc_driver.h"
 #endif                                /* defined(USB_CFG_HMSC_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#if defined(USB_CFG_PHID_USE) && !defined(USB_CFG_OTG_USE)
 #include "r_usb_phid_api.h"
#endif                                 /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_PPRN_USE)
 #include "r_usb_pprn_api.h"
#endif                                 /* defined(USB_CFG_PPRN_USE) */

#if defined(USB_CFG_OTG_USE)
 #if defined(USB_CFG_PCDC_USE)
  #include "r_usb_pcdc_api.h"
  #include "r_usb_otg_cdc_cfg.h"
 #endif                                /* (defined(USB_CFG_HCDC_USE) | defined(USB_CFG_PCDC_USE)) */
#else                                  /* defined(USB_CFG_OTG_USE) */
 #if defined(USB_CFG_PCDC_USE)
  #include "r_usb_pcdc_api.h"
  #include "r_usb_pcdc_cfg.h"
 #endif                                /* defined(USB_CFG_PCDC_USE) */
#endif                                 /* defined(USB_CFG_OTG_USE) */

#if defined(USB_CFG_PMSC_USE)
 #if (BSP_CFG_RTOS != 1)
  #include "../r_usb_pmsc/src/inc/r_usb_pmsc_driver.h"
 #endif                                /* #if (BSP_CFG_RTOS != 1) */
#endif                                 /* defined(USB_CFG_PMSC_USE) */

#if (USB_CFG_DMA == USB_CFG_ENABLE)
 #include "r_dmac.h"
#endif

#if defined(USB_OTG_CFG_USE)
 #include "r_icu.h"
 #include "r_ioport.h"
#endif                                 /* defined(USB_OTG_CFG_USE) */

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define USB_VALUE_50             (50)
#define USB_VALUE_100            (100)
#define USB_VALUE_7FH            (0x7F)
#define USB_VALUE_80H            (0x80)
#define USB_VALUE_FFH            (0xFF)

#define USB_MASK_ALIGN_2_BYTE    (0x1U)
#define USB_MASK_ALIGN_4_BYTE    (0x3U)

#define USB_OTG_IRQ              (0x7)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if (BSP_CFG_RTOS == 0)
usb_event_t g_usb_cstd_event;
uint16_t    g_usb_change_device_state[USB_NUM_USBIP];
#else                                  /*(BSP_CFG_RTOS == 0)*/
usb_instance_ctrl_t g_usb_cstd_event[USB_EVENT_MAX];

#endif                                 /*(BSP_CFG_RTOS == 0)*/
usb_callback_t      * g_usb_apl_callback[USB_NUM_USBIP];
usb_callback_args_t * g_usb_apl_callback_memory[USB_NUM_USBIP] =
{
    NULL,
#if 2 == USB_NUM_USBIP
    NULL,
#endif                                 /* 2 == USB_NUM_USBIP */
};

#if defined(USB_CFG_OTG_USE)
usb_cfg_t * g_p_usb_otg_cfg;

#endif                                 /* defined (USB_CFG_OTG_USE) */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
usb_utr_t g_usb_hdata[USB_NUM_USBIP][USB_MAXPIPE_NUM + 1];
 #if (BSP_CFG_RTOS == 1)
extern UINT     usb_host_usbx_initialize(UX_HCD * hcd);
extern uint32_t usb_host_usbx_uninitialize(uint32_t dcd_io);

 #endif                                /* (BSP_CFG_RTOS == 1) */
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
usb_compliance_cb_t * g_usb_compliance_callback[USB_NUM_USBIP];
 #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
usb_utr_t g_usb_pdata[USB_MAXPIPE_NUM + 1];
 #if (BSP_CFG_RTOS == 1)
extern uint32_t usb_peri_usbx_initialize(uint32_t dcd_io);
extern uint32_t usb_peri_usbx_uninitialize(uint32_t dcd_io);

  #if defined(USB_CFG_PMSC_USE)
extern fsp_err_t usb_peri_usbx_pmsc_media_initialize(void const * p_context);
extern fsp_err_t usb_peri_usbx_media_close(void);

  #endif                               /* defined(USB_CFG_PMSC_USE) */

 #else                                 /* (BSP_CFG_RTOS == 1) */
  #if defined(USB_CFG_PMSC_USE)
extern usb_utr_t g_usb_pmsc_utr;
  #endif                               /* defined(USB_CFG_PMSC_USE) */
 #endif                                /* (BSP_CFG_RTOS == 1) */

#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

volatile uint16_t g_usb_usbmode[USB_NUM_USBIP] =
{
    0,
#if USB_NUM_USBIP == 2
    0
#endif
};

#if defined(USB_CFG_OTG_USE)
void (* g_p_otg_callback[USB_NUM_USBIP])(ULONG mode);
#endif                                 /* USB_CFG_OTG_USE */

volatile uint32_t g_usb_open_class[USB_NUM_USBIP];

#if defined(USB_CFG_PMSC_USE)
uint8_t g_usb_pmsc_usbip = USB_VALUE_FFH;
#endif                                 /* defined(USB_CFG_PMSC_USE) */

#if (USB_CFG_DMA == USB_CFG_ENABLE)
 #if (BSP_CFG_RTOS == 1)
const transfer_instance_t * g_p_usbx_transfer_tx;
const transfer_instance_t * g_p_usbx_transfer_rx;
 #endif                                /* (BSP_CFG_RTOS == 1) */
#endif                                 /* (USB_CFG_DMA == USB_CFG_ENABLE) */

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
static uint8_t is_init[USB_NUM_USBIP] =
{
    USB_NO,
#if USB_NUM_USBIP == 2
    USB_NO,
#endif
};

#if (BSP_CFG_RTOS != 0)
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint8_t gs_usb_suspend_ing[USB_NUM_USBIP] =
{
    USB_NO,
  #if USB_NUM_USBIP == 2
    USB_NO,
  #endif
};
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

uint8_t g_usb_resume_ing[USB_NUM_USBIP] =
{
    USB_NO,
 #if USB_NUM_USBIP == 2
    USB_NO,
 #endif
};
#endif                                 /*#if (BSP_CFG_RTOS != 0)*/

#if defined(USB_CFG_OTG_USE)
uint8_t g_is_usbx_otg_host_class_init[USB_NUM_USBIP] =
{
    USB_NO,
 #if USB_NUM_USBIP == 2
    USB_NO,
 #endif
};
#endif                                 /* #if defined(USB_CFG_OTG_USE) */

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const usb_api_t g_usb_on_usb =
{
    .open                 = R_USB_Open,
    .close                = R_USB_Close,
    .read                 = R_USB_Read,
    .write                = R_USB_Write,
    .stop                 = R_USB_Stop,
    .suspend              = R_USB_Suspend,
    .resume               = R_USB_Resume,
    .vbusSet              = R_USB_VbusSet,
    .infoGet              = R_USB_InfoGet,
    .pipeRead             = R_USB_PipeRead,
    .pipeWrite            = R_USB_PipeWrite,
    .pipeStop             = R_USB_PipeStop,
    .usedPipesGet         = R_USB_UsedPipesGet,
    .pipeInfoGet          = R_USB_PipeInfoGet,
    .eventGet             = R_USB_EventGet,
    .callback             = R_USB_Callback,
    .pullUp               = R_USB_PullUp,
    .hostControlTransfer  = R_USB_HostControlTransfer,
    .periControlDataGet   = R_USB_PeriControlDataGet,
    .periControlDataSet   = R_USB_PeriControlDataSet,
    .periControlStatusSet = R_USB_PeriControlStatusSet,
    .remoteWakeup         = R_USB_RemoteWakeup,
    .driverActivate       = R_USB_DriverActivate,
    .callbackMemorySet    = R_USB_CallbackMemorySet,
    .moduleNumberGet      = R_USB_ModuleNumberGet,
    .classTypeGet         = R_USB_ClassTypeGet,
    .deviceAddressGet     = R_USB_DeviceAddressGet,
    .pipeNumberGet        = R_USB_PipeNumberGet,
    .deviceStateGet       = R_USB_DeviceStateGet,
    .dataSizeGet          = R_USB_DataSizeGet,
    .setupGet             = R_USB_SetupGet,
    .otgCallbackSet       = R_USB_OtgCallbackSet,
    .otgSRP               = R_USB_OtgSRP,
    .typecInfoGet         = R_USB_TypeCInfoGet,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB USB
 * @{
 **********************************************************************************************************************/

/**************************************************************************//**
 * @brief Obtains completed USB related events. (OS-less Only)
 *
 * In USB host mode, the device address value of the USB device that completed
 * an event is specified in the usb_ctrl_t structure member (address) specified
 * by the event's argument.
 * In USB peripheral mode, USB_NULL is specified in member (address).
 * If this function is called in the RTOS execution environment, a failure is returned.
 *
 * @retval FSP_SUCCESS        Event Get Success.
 * @retval FSP_ERR_USB_FAILED If called in the RTOS environment, an error is returned.
 *
 * @note Do not use the same variable as the first argument of R_USB_Open for the first argument.
 * @note Do not call this API in the interrupt function.
 ******************************************************************************/
fsp_err_t R_USB_EventGet (usb_ctrl_t * const p_api_ctrl, usb_status_t * event)
{
    fsp_err_t result;
#if (BSP_CFG_RTOS == 0)
    result   = FSP_SUCCESS;
    (*event) = USB_STATUS_NONE;
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_cstd_usb_task();
    if (g_usb_cstd_event.write_pointer != g_usb_cstd_event.read_pointer)
    {
        *p_ctrl  = g_usb_cstd_event.ctrl[g_usb_cstd_event.read_pointer];
        (*event) = g_usb_cstd_event.code[g_usb_cstd_event.read_pointer];
        g_usb_cstd_event.read_pointer++;
        if (g_usb_cstd_event.read_pointer >= USB_EVENT_MAX)
        {
            g_usb_cstd_event.read_pointer = 0;
        }
    }

#else                                  /* (BSP_CFG_RTOS == 0) */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(*event);
    result = FSP_ERR_USB_FAILED;
#endif /* (BSP_CFG_RTOS == 0) */

    return result;
}                                      /* End of function R_USB_EventGet() */

/**************************************************************************//**
 * @brief Register a callback function to be called upon completion of a
 * USB related event. (RTOS only)
 *
 * This function registers a callback function to be called when a USB-related event has completed.
 * If this function is called in the OS-less execution environment, a failure is returned.
 *
 * @retval FSP_SUCCESS        Successfully completed.
 * @retval FSP_ERR_ASSERTION  Parameter is NULL error.
 * @note Do not call this API in the interrupt function.
 ******************************************************************************/
fsp_err_t R_USB_Callback (usb_callback_t * p_callback)
{
#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_callback)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

    g_usb_apl_callback[0] = callback_is_secure ? p_callback :
                            (void (*)(usb_callback_args_t *))cmse_nsfptr_create(p_callback);
#else                                  /* BSP_TZ_SECURE_BUILD */
    g_usb_apl_callback[0] = p_callback;
#endif  /* BSP_TZ_SECURE_BUILD */

#if USB_NUM_USBIP == 2
    g_usb_apl_callback[1] = g_usb_apl_callback[0];
#endif                                 /* USB_NUM_USBIP == 2 */

    return FSP_SUCCESS;
} /* End of function R_USB_Callback() */

/**************************************************************************//**
 * @brief Applies power to the USB module specified in the argument (p_ctrl).
 *
 * @retval FSP_SUCCESS           Success in open.
 * @retval FSP_ERR_USB_BUSY      Specified USB module now in use.
 * @retval FSP_ERR_ASSERTION     Parameter is NULL error.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_Open (usb_ctrl_t * const p_api_ctrl, usb_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
#if (BSP_CFG_RTOS != 0)
    usb_rtos_err_t os_err;
 #if (USB_NUM_USBIP == 2)
    uint16_t usb_mode;
 #endif                                /* (USB_NUM_USBIP == 2) */
#endif                                 /* (BSP_CFG_RTOS != 0) */
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t utr;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if defined(USB_CFG_OTG_USE)
    uint16_t syssts;
#endif                                 /* defined(USB_CFG_OTG_USE) */

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
    FSP_ASSERT(p_cfg)

    /* Check if the module number is valid */
    FSP_ERROR_RETURN(!((USB_IP0 != p_cfg->module_number) && (USB_IP1 != p_cfg->module_number)), FSP_ERR_USB_PARAMETER)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

#if defined(USB_CFG_OTG_USE)
#endif                                 /* !defined (USB_CFG_OTG_USE)*/
    p_ctrl->module_number = p_cfg->module_number;
    p_ctrl->type          = (usb_class_t) (p_cfg->type & USB_VALUE_7FH);
    p_ctrl->p_context     = (void *) p_cfg->p_context;
#if (BSP_CFG_RTOS == 1)
    g_usb_apl_callback[p_ctrl->module_number] = usb_cstd_usbx_callback;
#else                                  /* #if (BSP_CFG_RTOS == 1) */
 #if defined(USB_CFG_HCDC_USE) && defined(USB_CFG_HMSC_USE)

    /* Callback registration is not done yet. */
 #else
    g_usb_apl_callback[p_ctrl->module_number] = p_cfg->p_usb_apl_callback;
 #endif
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    g_usb_compliance_callback[p_ctrl->module_number] = p_cfg->usb_complience_cb;
 #endif                                /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
#endif                                 /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

#if USB_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ERROR_RETURN(!(((USB_SPEED_HS != p_cfg->usb_speed) && (USB_SPEED_FS != p_cfg->usb_speed)) &&
                       (USB_SPEED_LS != p_cfg->usb_speed) &&
                       (USB_MODE_HOST != p_cfg->usb_mode)),
                     FSP_ERR_USB_PARAMETER)

 #if (USB_NUM_USBIP == 1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
 #endif                                /* USB_NUM_USBIP == 1 */

    switch ((usb_class_internal_t) p_ctrl->type)
    {
        case USB_CLASS_INTERNAL_PCDC:
        case USB_CLASS_INTERNAL_PHID:
        case USB_CLASS_INTERNAL_PVND:
        case USB_CLASS_INTERNAL_PMSC:
        case USB_CLASS_INTERNAL_PAUD:
        case USB_CLASS_INTERNAL_PPRN:
        case USB_CLASS_INTERNAL_DFU:
        {
            FSP_ERROR_RETURN(USB_MODE_PERI == p_cfg->usb_mode, FSP_ERR_USB_PARAMETER)

 #if (BSP_CFG_RTOS == 1)
            FSP_ERROR_RETURN(!(USB_SPEED_LS == p_cfg->usb_speed), FSP_ERR_USB_PARAMETER)
 #else                                 /*  #if (BSP_CFG_RTOS == 1) */
            FSP_ERROR_RETURN(!((USB_SPEED_LS == p_cfg->usb_speed) || (USB_NULL == p_cfg->p_usb_reg)),
                             FSP_ERR_USB_PARAMETER)
 #endif /*  #if (BSP_CFG_RTOS == 1) */

 #if defined(USB_HIGH_SPEED_MODULE)
            if (USB_IP0 == p_ctrl->module_number)
            {
                FSP_ERROR_RETURN(USB_SPEED_HS != p_cfg->usb_speed, FSP_ERR_USB_PARAMETER)
            }

 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
            FSP_ERROR_RETURN(USB_SPEED_HS != p_cfg->usb_speed, FSP_ERR_USB_PARAMETER)
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
            break;
        }

        /* Host */
        case USB_CLASS_INTERNAL_HCDC:
        case USB_CLASS_INTERNAL_HHID:
        case USB_CLASS_INTERNAL_HVND:
        case USB_CLASS_INTERNAL_HMSC:
        case USB_CLASS_INTERNAL_HPRN:
        case USB_CLASS_INTERNAL_HUVC:
        {
 #if defined(USB_NOT_SUPPORT_HOST)

            return FSP_ERR_USB_PARAMETER;
 #else                                 /* defined(USB_NOT_SUPPORT_HOST) */
            FSP_ERROR_RETURN(USB_MODE_HOST == p_cfg->usb_mode, FSP_ERR_USB_PARAMETER)
  #if defined(USB_HIGH_SPEED_MODULE)
            FSP_ERROR_RETURN(!((USB_SPEED_HS == p_cfg->usb_speed) && (USB_IP1 != p_ctrl->module_number)),
                             FSP_ERR_USB_PARAMETER)
  #else                                /* defined (USB_HIGH_SPEED_MODULE) */
            FSP_ERROR_RETURN(USB_SPEED_HS != p_cfg->usb_speed, FSP_ERR_USB_PARAMETER)
  #endif /* defined (USB_HIGH_SPEED_MODULE) */
 #endif /* defined(USB_NOT_SUPPORT_HOST) */
            break;
        }

        default:
        {
            return FSP_ERR_USB_PARAMETER;
            break;
        }
    }
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

#if (USB_CFG_DMA == USB_CFG_ENABLE)
    p_ctrl->p_transfer_tx = p_cfg->p_transfer_tx;
    p_ctrl->p_transfer_rx = p_cfg->p_transfer_rx;

 #if (BSP_CFG_RTOS == 1)
    g_p_usbx_transfer_tx = p_cfg->p_transfer_tx;
    g_p_usbx_transfer_rx = p_cfg->p_transfer_rx;
 #endif                                /* (BSP_CFG_RTOS == 1) */

 #if defined(USB_CFG_PMSC_USE)
  #if (BSP_CFG_RTOS != 1)
    g_usb_pmsc_utr.p_transfer_rx = p_cfg->p_transfer_rx;
    g_usb_pmsc_utr.p_transfer_tx = p_cfg->p_transfer_tx;
  #endif                               /* (BSP_CFG_RTOS != 1) */
 #endif                                /* defined(USB_CFG_PMSC_USE) */
#endif
    if (USB_YES == is_init[p_ctrl->module_number])
    {
        return FSP_ERR_USB_BUSY;
    }

#if (USB_CFG_DMA == USB_CFG_ENABLE)
    if (USB_IP0 == p_cfg->module_number)
    {
        if (0 != p_ctrl->p_transfer_tx)
        {
            R_DMAC_Open(p_ctrl->p_transfer_tx->p_ctrl, p_ctrl->p_transfer_tx->p_cfg);
        }

        if (0 != p_ctrl->p_transfer_rx)
        {
            R_DMAC_Open(p_ctrl->p_transfer_rx->p_ctrl, p_ctrl->p_transfer_rx->p_cfg);
        }
    }

    if (USB_IP1 == p_cfg->module_number)
    {
        if (0 != p_ctrl->p_transfer_tx)
        {
            R_DMAC_Open(p_ctrl->p_transfer_tx->p_ctrl, p_ctrl->p_transfer_tx->p_cfg);
        }

        if (0 != p_ctrl->p_transfer_rx)
        {
            R_DMAC_Open(p_ctrl->p_transfer_rx->p_ctrl, p_ctrl->p_transfer_rx->p_cfg);
        }
    }
#endif

    if (USB_MODE_HOST == p_cfg->usb_mode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

        /* Be sure set USB_MODE_HOST to g_usb_usbmode variable before calling usb_rtos_configuration function. */
        g_usb_usbmode[p_ctrl->module_number] = USB_MODE_HOST;
#endif
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

        /* Be sure set USB_MODE_PERI to g_usb_usbmode variable before calling usb_rtos_configuration function. */
        g_usb_usbmode[p_ctrl->module_number] = USB_MODE_PERI;
#endif
    }

#if defined(USB_CFG_OTG_USE)
    _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE;
#endif                                 /* defined(USB_CFG_OTG_USE) */

#if (BSP_CFG_RTOS != 0)
 #if (USB_NUM_USBIP == 2)
    usb_mode = g_usb_usbmode[0];
    if (usb_mode != g_usb_usbmode[1])
    {
        os_err = usb_rtos_configuration(p_cfg->usb_mode);
        if (UsbRtos_Success != os_err)
        {
            return FSP_ERR_USB_FAILED;
        }
    }

 #else                                 /* (USB_NUM_USBIP == 2) */
    os_err = usb_rtos_configuration(p_cfg->usb_mode);
    if (UsbRtos_Success != os_err)
    {
        return FSP_ERR_USB_FAILED;
    }
 #endif                                /* (USB_NUM_USBIP == 2) */
#endif                                 /* (BSP_CFG_RTOS != 0) */

#if USB_NUM_USBIP == 2
    if ((USB_NO == is_init[USB_IP0]) && (USB_NO == is_init[USB_IP1]))
    {
#endif                                 /* USB_NUM_USBIP == 2 */

    memset((void *) &g_usb_cstd_event, 0, sizeof(g_usb_cstd_event));

#if USB_NUM_USBIP == 2
}
#endif                                 /* USB_NUM_USBIP == 2 */

    is_init[p_ctrl->module_number] = USB_YES;

    g_usb_open_class[p_ctrl->module_number] = 0;

#if (BSP_CFG_RTOS == 0)
    g_usb_change_device_state[p_ctrl->module_number] = 0;
#endif                                 /* (BSP_CFG_RTOS == 0) */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    g_usb_hstd_use_pipe[p_ctrl->module_number] = 0;
    memset((void *) &g_usb_hdata[p_ctrl->module_number], 0, sizeof(usb_utr_t));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    memset((void *) &g_usb_pdata, 0, ((USB_MAXPIPE_NUM + 1) * sizeof(usb_utr_t)));
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

#if defined(USB_CFG_OTG_USE)
    g_p_usb_otg_cfg = (usb_cfg_t *) p_cfg;
#endif /* defined (USB_CFG_OTG_USE) */

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)
    hw_usb_typec_module_init();
#endif                                 /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */

    if (USB_MODE_HOST == p_cfg->usb_mode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip  = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr((uint16_t) p_ctrl->module_number); /* Get the USB IP base address. */

        err = usb_module_start(utr.ip);
        if (FSP_SUCCESS == err)
        {
            /* USB driver initialization */
            usb_hdriver_init(&utr);

            /* Setting MCU(USB interrupt init) register */
            usb_cpu_usbint_init(utr.ip, p_cfg);

            g_usb_hstd_hs_enable[utr.ip] = USB_HS_DISABLE;

 #if defined(USB_HIGH_SPEED_MODULE)
            if (USB_SPEED_HS == p_cfg->usb_speed)
            {
                g_usb_hstd_hs_enable[utr.ip] = USB_HS_ENABLE;
                hw_usb_set_hse(&utr);
            }
 #endif                                  /* defined (USB_HIGH_SPEED_MODULE) */
            /* Setting USB relation register  */
            hw_usb_hmodule_init(utr.ip); /* MCU */

 #if !defined(USB_CFG_OTG_USE)
  #if defined(USB_CFG_HHID_USE)
            if (USB_CLASS_INTERNAL_HHID == (usb_class_internal_t) p_ctrl->type)
            {
                hw_usb_hset_trnensel(&utr);
            }
  #endif                               /* defined(USB_CFG_HHID_USE) */
 #endif                                /* !defined (USB_CFG_OTG_USE) */

 #if USB_CFG_TYPEC == USB_CFG_DISABLE
  #if USB_CFG_VBUS == USB_CFG_LOW

            /* VBUS OFF process for Low Active Power IC */
            usb_hstd_vbus_control(&utr, (uint16_t) USB_VBOFF);
            usb_cpu_delay_xms(USB_VALUE_50);
  #endif                                                 /* USB_CFG_VBUS == USB_CFG_LOW */
            usb_hstd_vbus_control(&utr, (uint16_t) USB_VBON);
  #if USB_CFG_BC == USB_CFG_DISABLE
            usb_cpu_delay_xms((uint16_t) USB_VALUE_100); /* 100ms wait */
  #endif /*  USB_CFG_BC == USB_CFG_DISABLE */
 #else  /*  USB_CFG_TYPEC == USB_CFG_DISABLE */
            usb_hstd_vbus_control(&utr, (uint16_t) USB_VBOFF);
 #endif /*  USB_CFG_TYPEC == USB_CFG_DISABLE */

 #if (BSP_CFG_RTOS == 1)
  #if !defined(USB_CFG_OTG_USE)
            ux_host_stack_class_register(_ux_system_host_class_hub_name, ux_host_class_hub_entry);
  #endif                               /* !defined(USB_CFG_OTG_USE) */

  #if defined(USB_CFG_HCDC_USE)
            ux_host_stack_class_register(_ux_system_host_class_cdc_acm_name, ux_host_class_cdc_acm_entry);
            if (USB_SPEED_HS == p_cfg->usb_speed)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hcdc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                if (USB_IP0 == p_cfg->module_number)
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hcdc_fs", usb_host_usbx_initialize, R_USB_FS0_BASE,
                                               0);
                }
                else
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hcdc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE,
                                               0);
                }
            }
  #endif                               /* defined(USB_CFG_HCDC_USE) */
  #if defined(USB_CFG_HMSC_USE)
            ux_host_stack_class_register(_ux_system_host_class_storage_name, ux_host_class_storage_entry);
            if (USB_SPEED_HS == p_cfg->usb_speed)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hmsc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                if (USB_IP0 == p_cfg->module_number)
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hmsc_fs", usb_host_usbx_initialize, R_USB_FS0_BASE,
                                               0);
                }
                else
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hmsc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE,
                                               0);
                }
            }
  #endif                               /* defined(USB_CFG_HCDC_USE) */
  #if defined(USB_CFG_HHID_USE)
            ux_host_stack_class_register(_ux_system_host_class_hid_name, ux_host_class_hid_entry);

            ux_host_class_hid_client_register(_ux_system_host_class_hid_client_keyboard_name,
                                              ux_host_class_hid_keyboard_entry);
            ux_host_class_hid_client_register(_ux_system_host_class_hid_client_mouse_name,
                                              ux_host_class_hid_mouse_entry);

            if (USB_IP1 == p_ctrl->module_number)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hhid_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hhid_fs", usb_host_usbx_initialize, R_USB_FS0_BASE, 0);
            }
  #endif                               /* defined(USB_CFG_HHID_USE) */
  #if defined(USB_CFG_HPRN_USE)
            ux_host_stack_class_register(_ux_system_host_class_printer_name, ux_host_class_printer_entry);
            if (USB_SPEED_HS == p_cfg->usb_speed)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hprn_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                if (USB_IP0 == p_cfg->module_number)
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hprn_fs", usb_host_usbx_initialize, R_USB_FS0_BASE,
                                               0);
                }
                else
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hprn_hs", usb_host_usbx_initialize, R_USB_HS0_BASE,
                                               0);
                }
            }
  #endif                               /* defined(USB_CFG_HPRN_USE) */
  #if defined(USB_CFG_HUVC_USE)
            ux_host_stack_class_register(_ux_system_host_class_video_name, ux_host_class_video_entry);
            if (USB_SPEED_HS == p_cfg->usb_speed)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_huvc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                if (USB_IP0 == p_cfg->module_number)
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_huvc_fs", usb_host_usbx_initialize, R_USB_FS0_BASE,
                                               0);
                }
                else
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_huvc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE,
                                               0);
                }
            }
  #endif                               /* defined(USB_CFG_HUVC_USE) */
 #endif                                /* #if (BSP_CFG_RTOS == 0) */
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
 #if defined(USB_CFG_PMSC_USE)
        g_usb_pmsc_usbip = p_ctrl->module_number;
  #if (BSP_CFG_RTOS == 1)
        err = usb_peri_usbx_pmsc_media_initialize(p_cfg->p_context);
  #else
        err = r_usb_pmsc_media_initialize(p_cfg->p_context); /* Register the media device driver. */
  #endif /* (BSP_CFG_RTOS == 1) */
        if (FSP_SUCCESS != err)
        {
            return err;
        }
 #endif                                /* defined(USB_CFG_PMSC_USE) */
        /* USB module start setting */
        err = usb_module_start(p_ctrl->module_number);
        if (FSP_SUCCESS == err)
        {
            /* USB driver initialization */
            usb_pdriver_init(p_ctrl, p_cfg);

            /* Setting MCU(USB interrupt init) register */
            usb_cpu_usbint_init(p_ctrl->module_number, p_cfg);

 #if defined(USB_HIGH_SPEED_MODULE)
            if (USB_SPEED_HS == p_cfg->usb_speed)
            {
                usb_utr_t hse_utr;
                hse_utr.ip = p_ctrl->module_number;
                hw_usb_set_hse(&hse_utr);
            }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

            /* Setting USB relation register  */
            hw_usb_pmodule_init(p_ctrl->module_number);

 #if (BSP_CFG_RTOS == 1)
  #if defined(USB_HIGH_SPEED_MODULE)
            if (USB_IP1 == p_ctrl->module_number)
            {
                usb_peri_usbx_initialize(R_USB_HS0_BASE);
            }
            else
            {
                usb_peri_usbx_initialize(R_USB_FS0_BASE);
            }

  #else
            usb_peri_usbx_initialize(R_USB_FS0_BASE);
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
            if (USB_ATTACH == usb_pstd_chk_vbsts(p_ctrl->module_number))
            {
 #if defined(USB_HIGH_SPEED_MODULE)
                hw_usb_set_cnen(p_ctrl->module_number);
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
                usb_cpu_delay_xms((uint16_t) 10);
                hw_usb_pset_dprpu(p_ctrl->module_number);
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    if (FSP_SUCCESS == err)
    {
        if (USB_MODE_HOST == p_cfg->usb_mode)
        {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << p_ctrl->type);      /* Set USB Open device class */
 /* Check if both HCDC class and HMSC class are enabled */
 #if (defined(USB_CFG_HCDC_USE) && defined(USB_CFG_HMSC_USE))
            /* Set USB Open device class for HCDC Class and HCDCC Class */
            g_usb_open_class[p_ctrl->module_number] |= ((1 << USB_CLASS_INTERNAL_HCDC) | (1 << USB_CLASS_INTERNAL_HCDCC));
 #else
            if (USB_CLASS_INTERNAL_HCDC == (usb_class_internal_t) p_ctrl->type)
            {
                g_usb_open_class[p_ctrl->module_number] |= (1 << USB_CLASS_INTERNAL_HCDCC); /* Set USB Open device class */
            }
 #endif                                /* defined(USB_CFG_HCDC_USE) && defined(USB_CFG_HMSC_USE) */

 #if defined(USB_CFG_OTG_USE)
            g_is_A_device[p_ctrl->module_number]      = USB_YES;
            _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_A;

            (*g_p_otg_callback[p_ctrl->module_number])(UX_OTG_MODE_HOST);
 #endif                                /* defined(USB_CFG_OTG_USE) */
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
#if defined(USB_CFG_PCDC_USE)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PCDC);
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PCDCC);
 #if ((USB_CFG_PCDC_BULK_IN2 != USB_NULL) || (USB_CFG_PCDC_BULK_OUT2 != USB_NULL))
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PCDC2);
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PCDCC2);
 #endif                                /* ((USB_CFG_PCDC_BULK_IN2 != USB_NULL) || (USB_CFG_PCDC_BULK_OUT2 != USB_NULL)) */
#endif                                 /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_PHID_USE)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PHID);
 #if ((USB_CFG_PHID_INT_IN2 != USB_NULL) || (USB_CFG_PHID_INT_OUT2 != USB_NULL))
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PHID2);
 #endif                                /* ((USB_CFG_PHID_INT_IN2 != USB_NULL) || (USB_CFG_PHID_INT_OUT2 != USB_NULL)) */
#endif                                 /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_PMSC_USE)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PMSC);
#endif                                 /* defined(USB_CFG_PMSC_USE) */

#if defined(USB_CFG_PAUD_USE)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PAUD);
#endif                                 /* defined(USB_CFG_PAUD_USE) */

#if defined(USB_CFG_PVND_USE)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PVND);
#endif                                 /* defined(USB_CFG_PVND_USE) */

#if defined(USB_CFG_PPRN_USE)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_PPRN);
#endif                                 /* defined(USB_CFG_PPRN_USE) */

#if defined(USB_CFG_DFU_USE)
            g_usb_open_class[p_ctrl->module_number] |= (uint16_t) (1 << USB_CLASS_INTERNAL_DFU);
#endif                                 /* defined(USB_CFG_PPRN_USE) */

#if defined(USB_CFG_OTG_USE)
            _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_B;
            (*g_p_otg_callback[p_ctrl->module_number])(UX_OTG_MODE_SLAVE);
#endif                                 /* defined(USB_CFG_OTG_USE) */
        }
    }

#if (BSP_CFG_RTOS == 1)
 #if defined(USB_CFG_OTG_USE)

    /* Check the A device cable is connected when starting up MCU */
    /* If A device cable is connected, the following callback function is called */
    utr.ip = p_ctrl->module_number;
    syssts = hw_usb_read_syssts(&utr);
    if (0 == (syssts & USB_IDMON))
    {
        if (USB_IP0 == p_ctrl->module_number)
        {
            usb_otg_irq_callback(0);
        }

  #if USB_NUM_USBIP == 2
        else
        {
            usb2_otg_irq_callback(0);
        }
  #endif                               /* USB_NUM_USBIP == 2 */
    }
 #endif                                /* defined(USB_CFG_OTG_USB) */
#endif                                 /* (BSP_CFG_RTOS == 1) */

    return err;
}

/**************************************************************************//**
 * @brief Terminates power to the USB module specified in argument (p_ctrl).
 * USB0 module stops when USB_IP0 is specified to the member (module),
 * USB1 module stops when USB_IP1 is specified to the member (module).
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_NOT_OPEN  USB module is not open.
 * @retval FSP_ERR_ASSERTION     Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_Close (usb_ctrl_t * const p_api_ctrl)
{
#if defined(USB_CFG_OTG_USE)
    fsp_err_t             ret_code;
    usb_instance_ctrl_t * p_ctrl     = (usb_instance_ctrl_t *) p_api_ctrl;
    uint16_t              is_connect = USB_FALSE;
    uint8_t               class_code = USB_IFCLS_CDC;
    usb_utr_t             utr;
    UINT        old_threshold;
    TX_THREAD * now_thread;

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

  #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
  #endif                               /* #if defined(BSP_BOARD_GROUP_RA2A1) */

    _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE;
    g_is_A_device[p_ctrl->module_number]      = USB_NO;

    switch ((usb_class_internal_t) p_ctrl->type)
    {
        case USB_CLASS_INTERNAL_PCDC:
        {
            class_code = (uint8_t) USB_IFCLS_CDC;
            break;
        }

        case USB_CLASS_INTERNAL_PHID:
        {
            class_code = (uint8_t) USB_IFCLS_HID;
            break;
        }

        case USB_CLASS_INTERNAL_PMSC:
        {
            class_code = (uint8_t) USB_IFCLS_MAS;
            break;
        }

        case USB_CLASS_INTERNAL_PVND:
        {
            class_code = (uint8_t) USB_IFCLS_VEN;
            break;
        }

        case USB_CLASS_INTERNAL_PPRN:
        {
            class_code = (uint8_t) USB_IFCLS_PRN;
            break;
        }

        default:
        {
            return FSP_ERR_ASSERTION;
            break;
        }
    }
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    utr.ip     = p_ctrl->module_number;
    is_connect = usb_pstd_chk_configured(&utr);

 #if (defined(USB_LDO_REGULATOR_MODULE) && (USB_CFG_LDO_REGULATOR == USB_CFG_ENABLE))
    hw_usb_clear_vdcen();
 #endif                                /* (defined(USB_LDO_REGULATOR_MODULE) && (USB_CFG_LDO_REGULATOR == USB_CFG_ENABLE)) */

    ret_code = usb_module_stop(p_ctrl->module_number);

    if (FSP_SUCCESS == ret_code)
    {
        is_init[p_ctrl->module_number] = USB_NO;

        utr.ip  = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        usb_hstd_driver_release(&utr, class_code);

        usb_hstd_clr_pipe_table(utr.ip, USB_ADDRESS1);

        if ((USB_NO == g_is_usbx_otg_host_class_init[p_ctrl->module_number]) ||
            (USB_YES == g_is_A_device[p_ctrl->module_number]))
        {
            if (USB_IP1 == p_ctrl->module_number)
            {
 #if defined(USB_CFG_HCDC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hcdc_hs", R_USB_HS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HCDC_USE) */
 #if defined(USB_CFG_HMSC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hmsc_hs", R_USB_HS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HMSC_USE) */
 #if defined(USB_CFG_HHID_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hhid_hs", R_USB_HS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HHID_USE) */
 #if defined(USB_CFG_HPRN_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hprn_hs", R_USB_HS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HPRN_USE) */
 #if defined(USB_CFG_HUVC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_huvc_hs", R_USB_HS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HUVC_USE) */
                usb_host_usbx_uninitialize(R_USB_HS0_BASE);
            }
            else
            {
 #if defined(USB_CFG_HCDC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hcdc_fs", R_USB_FS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HCDC_USE) */
 #if defined(USB_CFG_HMSC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hmsc_fs", R_USB_FS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HMSC_USE) */
 #if defined(USB_CFG_HHID_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hhid_fs", R_USB_FS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HHID_USE) */
 #if defined(USB_CFG_HPRN_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hprn_fs", R_USB_FS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HPRN_USE) */
 #if defined(USB_CFG_HUVC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_huvc_fs", R_USB_FS0_BASE, 0);
 #endif                                /* #if defined(USB_CFG_HUVC_USE) */
                usb_host_usbx_uninitialize(R_USB_FS0_BASE);
            }

 #if defined(USB_CFG_HCDC_USE)
            ux_host_stack_class_unregister(ux_host_class_cdc_acm_entry);
 #endif                                /* #if defined(USB_CFG_HCDC_USE) */
 #if defined(USB_CFG_HMSC_USE)
            ux_host_stack_class_unregister(ux_host_class_storage_entry);
 #endif                                /* #if defined(USB_CFG_HMSC_USE) */
 #if defined(USB_CFG_HHID_USE)
            ux_host_stack_class_unregister(ux_host_class_hid_entry);
 #endif                                /* #if defined(USB_CFG_HHID_USE) */
 #if defined(USB_CFG_HPRN_USE)
            ux_host_stack_class_unregister(ux_host_class_printer_entry);
 #endif                                /* #if defined(USB_CFG_HPRN_USE) */
 #if defined(USB_CFG_HUVC_USE)
            ux_host_stack_class_unregister(ux_host_class_video_entry);
 #endif                                /* #if defined(USB_CFG_HUVC_USE) */
        }

        g_is_usbx_otg_host_class_init[utr.ip] = USB_NO;

        usb_pstd_driver_release();     /* Clear the information registered in the structure usb_pcdreg_t. */
        usb_pstd_clr_pipe_table(p_ctrl->module_number);
        if (USB_TRUE == is_connect)
        {
            _ux_device_stack_disconnect();
        }

        if (USB_IP1 == p_ctrl->module_number)
        {
            usb_peri_usbx_uninitialize(R_USB_HS0_BASE);
        }
        else
        {
            usb_peri_usbx_uninitialize(R_USB_FS0_BASE);
        }

        g_usb_open_class[p_ctrl->module_number] = 0;

 #if defined(USB_CFG_PMSC_USE)
        ret_code = usb_peri_usbx_media_close();
 #endif                                                             /* defined(USB_CFG_PMSC_USE) */

        /* Settings to prevent preemption. */
        now_thread = tx_thread_identify();
        tx_thread_preemption_change(now_thread, 0, &old_threshold); /* Disable dispatch to the other task */

        usb_rtos_delete(p_ctrl->module_number);

        /* Remove settings that prevent preemption. */
        tx_thread_preemption_change(now_thread, old_threshold, &old_threshold); /* Enable dispach to the other task */

        /* Be sure set 0 to g_usb_usbmode variable after calling usb_rtos_delete function. */
        g_usb_usbmode[p_ctrl->module_number] = 0;
    }
    else
    {
        ret_code = FSP_ERR_USB_NOT_OPEN;
    }

 #if defined(USB_CFG_PMSC_USE)
    g_usb_pmsc_usbip = USB_VALUE_FFH;
 #endif                                /* defined(USB_CFG_PMSC_USE) */

    g_is_A_device[p_ctrl->module_number] = USB_NO;

    _ux_system_otg->ux_system_otg_device_type          = UX_OTG_DEVICE_IDLE;
    _ux_system_otg->ux_system_otg_slave_role_swap_flag = 0;

    return ret_code;
#else                                  /* defined(USB_CFG_OTG_USE) */
    fsp_err_t             ret_code;
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;
 #if (BSP_CFG_RTOS == 1)
    usb_utr_t ux_utr;
 #endif                                /* (BSP_CFG_RTOS == 1) */

 #if (BSP_CFG_RTOS != 0)
  #if (USB_NUM_USBIP == 2)
    uint16_t usb_mode;
  #endif                               /* (USB_NUM_USBIP == 2) */

  #if (BSP_CFG_RTOS == 1)
   #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    uint16_t is_connect = USB_FALSE;
   #endif                              /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
  #endif                               /* (BSP_CFG_RTOS == 1) */
 #endif                                /* (BSP_CFG_RTOS != 0) */

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    uint8_t class_code = USB_IFCLS_CDC;
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

  #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
  #endif                               /* #if defined(BSP_BOARD_GROUP_RA2A1) */

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        switch ((usb_class_internal_t) p_ctrl->type)
        {
            case USB_CLASS_INTERNAL_HCDC:
            {
                class_code = (uint8_t) USB_IFCLS_CDC;
                break;
            }

            case USB_CLASS_INTERNAL_HHID:
            {
                class_code = (uint8_t) USB_IFCLS_HID;
                break;
            }

            case USB_CLASS_INTERNAL_HMSC:
            {
                class_code = (uint8_t) USB_IFCLS_MAS;
                break;
            }

            case USB_CLASS_INTERNAL_HVND:
            {
                class_code = (uint8_t) USB_IFCLS_VEN;
                break;
            }

            case USB_CLASS_INTERNAL_HPRN:
            {
                class_code = (uint8_t) USB_IFCLS_PRN;
                break;
            }

            case USB_CLASS_INTERNAL_HUVC:
            {
                class_code = (uint8_t) USB_IFCLS_VID;
                break;
            }

            default:
            {
                return FSP_ERR_ASSERTION;
                break;
            }
        }
  #endif                               /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

 #if (BSP_CFG_RTOS == 1)
    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        ux_utr.ip  = p_ctrl->module_number;
        is_connect = usb_pstd_chk_configured(&ux_utr);

        usb_pstd_detach_process(&ux_utr);
  #endif                               /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ux_utr.ip  = p_ctrl->module_number;
        ux_utr.ipp = usb_hstd_get_usb_ip_adr((uint16_t) p_ctrl->module_number); /* Get the USB IP base address. */

        usb_hstd_detach_process(&ux_utr);
        usb_cpu_delay_xms(USB_VALUE_50);
  #endif /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
 #endif                                /* (BSP_CFG_RTOS == 1) */

 #if (defined(USB_LDO_REGULATOR_MODULE) && (USB_CFG_LDO_REGULATOR == USB_CFG_ENABLE))
    hw_usb_clear_vdcen();
 #endif                                /* (defined(USB_LDO_REGULATOR_MODULE) && (USB_CFG_LDO_REGULATOR == USB_CFG_ENABLE)) */

 #if defined(USB_SUPPORT_HOCO_MODULE)
    if (0 == (R_SYSTEM->SCKSCR & R_SYSTEM_SCKSCR_CKSEL_Msk))
    {
        /* Use HOCO */
        hw_usb_clear_uckselc();
    }
 #endif                                /* defined(USB_SUPPORT_HOCO_MODULE) */

    ret_code = usb_module_stop(p_ctrl->module_number);

    if (FSP_SUCCESS == ret_code)
    {
        is_init[p_ctrl->module_number] = USB_NO;

        if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
        {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            usb_utr_t utr;

            utr.ip  = p_ctrl->module_number;
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

            usb_hstd_driver_release(&utr, class_code);

            usb_hstd_clr_pipe_table(utr.ip, USB_ADDRESS1);

  #if (BSP_CFG_RTOS == 1)
            if (USB_IP1 == p_ctrl->module_number)
            {
   #if defined(USB_CFG_HCDC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hcdc_hs", R_USB_HS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HCDC_USE) */
   #if defined(USB_CFG_HMSC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hmsc_hs", R_USB_HS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HMSC_USE) */
   #if defined(USB_CFG_HHID_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hhid_hs", R_USB_HS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HHID_USE) */
   #if defined(USB_CFG_HUVC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_huvc_hs", R_USB_HS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HUVC_USE) */
                usb_host_usbx_uninitialize(R_USB_HS0_BASE);
            }
            else
            {
   #if defined(USB_CFG_HCDC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hcdc_fs", R_USB_FS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HCDC_USE) */
   #if defined(USB_CFG_HMSC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hmsc_fs", R_USB_FS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HMSC_USE) */
   #if defined(USB_CFG_HHID_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_hhid_fs", R_USB_FS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HHID_USE) */
   #if defined(USB_CFG_HUVC_USE)
                ux_host_stack_hcd_unregister((UCHAR *) "fsp_usbx_huvc_fs", R_USB_FS0_BASE, 0);
   #endif                              /* #if defined(USB_CFG_HUVC_USE) */
                usb_host_usbx_uninitialize(R_USB_FS0_BASE);
            }

   #if defined(USB_CFG_HCDC_USE)
            ux_host_stack_class_unregister(ux_host_class_cdc_acm_entry);
   #endif                              /* #if defined(USB_CFG_HCDC_USE) */
   #if defined(USB_CFG_HMSC_USE)
            ux_host_stack_class_unregister(ux_host_class_storage_entry);
   #endif                              /* #if defined(USB_CFG_HMSC_USE) */
   #if defined(USB_CFG_HHID_USE)
            ux_host_stack_class_unregister(ux_host_class_hid_entry);
   #endif                              /* #if defined(USB_CFG_HHID_USE) */
   #if defined(USB_CFG_HUVC_USE)
            ux_host_stack_class_unregister(ux_host_class_video_entry);
   #endif                              /* #if defined(USB_CFG_HHID_USE) */

   #if !defined(USB_CFG_OTG_USE)
            ux_host_stack_class_unregister(ux_host_class_hub_entry);
   #endif /* !defined(USB_CFG_OTG_USE) */
  #endif                               /* #if (BSP_CFG_RTOS == 1) */
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
            usb_pstd_driver_release(); /* Clear the information registered in the structure usb_pcdreg_t. */
            usb_pstd_clr_pipe_table(p_ctrl->module_number);
  #if (BSP_CFG_RTOS == 1)
            if (USB_TRUE == is_connect)
            {
                _ux_device_stack_disconnect();
            }

            if (USB_IP1 == p_ctrl->module_number)
            {
                usb_peri_usbx_uninitialize(R_USB_HS0_BASE);
            }
            else
            {
                usb_peri_usbx_uninitialize(R_USB_FS0_BASE);
            }
  #endif                               /* #if (BSP_CFG_RTOS == 1) */
 #endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        }

        g_usb_open_class[p_ctrl->module_number] = 0;

 #if defined(USB_CFG_PMSC_USE)
  #if (BSP_CFG_RTOS == 1)
        ret_code = usb_peri_usbx_media_close();
  #else
        ret_code = r_usb_pmsc_media_close();
  #endif                               /* (BSP_CFG_RTOS == 1) */
 #endif                                /* defined(USB_CFG_PMSC_USE) */
 #if (BSP_CFG_RTOS != 0)
  #if (BSP_CFG_RTOS == 1)
        UINT        old_threshold;
        TX_THREAD * now_thread;
  #endif                               /* (BSP_CFG_RTOS == 1) */
  #if (USB_NUM_USBIP == 2)
        usb_mode = g_usb_usbmode[0];
        if (usb_mode != g_usb_usbmode[1])
        {
   #if (BSP_CFG_RTOS == 1)

            /* Settings to prevent preemption. */
            now_thread = tx_thread_identify();
            tx_thread_preemption_change(now_thread, 0, &old_threshold); /* Disable dispatch to the other task */

            usb_rtos_delete(p_ctrl->module_number);

            /* Remove settings that prevent preemption. */
            tx_thread_preemption_change(now_thread, old_threshold, &old_threshold); /* Enable dispath ti the other task */
   #else                                                                            /* (BSP_CFG_RTOS == 1) */
            usb_rtos_delete(p_ctrl->module_number);
   #endif  /* (BSP_CFG_RTOS == 1) */
        }

  #else                                /* (USB_NUM_USBIP == 2) */
   #if (BSP_CFG_RTOS == 1)

        /* Settings to prevent preemption. */
        now_thread = tx_thread_identify();
        tx_thread_preemption_change(now_thread, 0, &old_threshold); /* Disable dispatch to the other task */

        usb_rtos_delete(p_ctrl->module_number);

        /* Remove settings that prevent preemption. */
        tx_thread_preemption_change(now_thread, old_threshold, &old_threshold); /* Enable dispath ti the other task */
   #else                                                                        /* (BSP_CFG_RTOS == 1) */
        usb_rtos_delete(p_ctrl->module_number);
   #endif  /* (BSP_CFG_RTOS == 1) */
  #endif  /* (USB_NUM_USBIP == 2) */
 #endif  /* (BSP_CFG_RTOS != 0) */

        /* Be sure set 0 to g_usb_usbmode variable after calling usb_rtos_delete function. */
        g_usb_usbmode[p_ctrl->module_number] = 0;
    }
    else
    {
        ret_code = FSP_ERR_USB_NOT_OPEN;
    }

 #if defined(USB_CFG_PMSC_USE)
    g_usb_pmsc_usbip = USB_VALUE_FFH;
 #endif                                /* defined(USB_CFG_PMSC_USE) */

 #if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)
    hw_usb_typec_module_uninit();
 #endif /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */

    return ret_code;
#endif                                 /* defined(USB_CFG_OTG_USE) */
}

/**************************************************************************//**
 * @brief Bulk/Interrupt data transfer
 *
 *   Requests USB data read (bulk/interrupt transfer).
 *   The read data is stored in the area specified by argument (p_buf).
 *   After data read is completed, confirm the operation by checking the return value
 *   (USB_STATUS_READ_COMPLETE) of the R_USB_GetEvent function. The received data size is set in member
 *   (size) of the usb_ctrl_t structure. To figure out the size of the data when a read is complete,
 *   check the return value (USB_STATUS_READ_COMPLETE) of the R_USB_GetEvent function, and then
 *   refer to the member (size) of the usb_crtl_t structure.
 *
 * @retval FSP_SUCCESS           Successfully completed (Data read request completed).
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY      Data receive request already in process for
 *                               USB device with same device address.
 * @retval FSP_ERR_ASSERTION     Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note 1. Do not call this API in the following function.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 * @note 2. Allocate the following the storage area when using DMA transfer and specify the start address of the allocated storage area to the 2nd argument(p_buf).
 * @note  (1). When using High-speed and enabling continuous transfer mode, allocate the storage area with a size that is a multiple of 2048.
 * @note  (2). When using High-speed and disabling continuous transfer mode, allocate the storage area with a size that is a multiple of 512.
 * @note  (3). When using Full-speed, allocate the storage area with a size that is a multiple of 64.
 * @note 3. Specify the following address to the 2nd argument (p_buf) when using DMA transfer.
 * @note  (1). When using High-speed module, specify start address of the buffer area aligned on 4-byte boundary.
 * @note  (2). When using Full-speed module, specify start address of the buffer area aligned on 2-byte boundary.
 ******************************************************************************/
fsp_err_t R_USB_Read (usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size, uint8_t destination)
{
    usb_info_t info;
    usb_er_t   err;
    fsp_err_t  result = FSP_ERR_USB_FAILED;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        FSP_ERROR_RETURN(((USB_CLASS_PCDC <= destination) && (destination < USB_CLASS_END)), FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        FSP_ASSERT(destination)
        FSP_ERROR_RETURN(USB_ADDRESS5 >= destination, FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_ctrl->type = (usb_class_t) (destination & USB_VALUE_7FH);
#endif                                 /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_ctrl->device_address = destination;
 #if defined(USB_CFG_HCDC_USE)

        /* Add the following code. */
        /* Because the value of "type" member change to "USB_CLASS_INTERNAL_HCDCC" */
        /* when calling R_USB_HCDC_ControlDataRead function. */
        p_ctrl->type = (usb_class_t) USB_CLASS_INTERNAL_HCDC;
 #endif                                /* defined(USB_CFG_HCDC_USE) */
#endif                                 /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(!(((USB_NULL == p_buf)) || (USB_NULL == size)))

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

 #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
 #endif

    FSP_ERROR_RETURN(!((USB_CLASS_INTERNAL_PCDCC == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_PVND == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_HVND == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_HMSC == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_PMSC == (usb_class_internal_t) p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] &
                                  (1 << p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
#endif  /* USB_CFG_PARAM_CHECKING_ENABLE */

#if (USB_CFG_DMA == USB_CFG_ENABLE)
    if (USB_IP0 == p_ctrl->module_number)
    {
        /* Alignment checking if "p_buf" is 2-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_2_BYTE)), FSP_ERR_USB_PARAMETER)
    }

 #if defined(USB_HIGH_SPEED_MODULE)
    else
    {
        /* Alignment checking if "p_buf" is 4-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_4_BYTE)), FSP_ERR_USB_PARAMETER)
    }
 #endif                                /* defined(USB_HIGH_SPEED_MODULE) */
#endif /* (USB_CFG_DMA == USB_CFG_ENABLE) */

    (void) R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        err = usb_data_read(p_ctrl, p_buf, size);

        if (USB_OK == err)
        {
            result = FSP_SUCCESS;
        }
        else if (USB_QOVR == err)
        {
            result = FSP_ERR_USB_BUSY;
        }
        else
        {
            /* Noting */
        }
    }

    return result;
}

/**************************************************************************//**
 * @brief Bulk/Interrupt data transfer
 *
 *   Requests USB data write (bulk/interrupt transfer).
 *   Stores write data in area specified by argument (p_buf).
 *   Set the device class type in usb_ctrl_t structure member (type).
 *   Confirm after data write is completed by checking the return value (USB_STATUS_WRITE_COMPLETE)
 *   of the R_USB_GetEvent function.
 *   For sending a zero-length packet, please refer the following Note.
 *
 * @retval FSP_SUCCESS           Successfully completed. (Data write request completed)
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY      Data write request already in process for
 *                               USB device with same device address.
 * @retval FSP_ERR_ASSERTION     Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note 1. The user needs to send the zero-length packet(ZLP) since this USB driver does not send the ZLP automatically.
 * @note   When sending a ZLP, the user sets USB_NULL in the third argument (size) of R_USB_Write function as follow.
 * @note   e.g)
 * @note   R_USB_Write (&g_basic0_ctrl, &g_buf, USB_NULL);
 * @note 2. Specify the following address to the 2nd argument (p_buf) when using DMA transfer.
 * @note  (1). When using High-speed module, specify start address of the buffer area aligned on 4-byte boundary.
 * @note  (2). When using Full-speed module, specify start address of the buffer area aligned on 2-byte boundary.
 * @note 3. Do not call this API in the following function.
 * @note   (1). Interrupt function.
 * @note   (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_Write (usb_ctrl_t * const p_api_ctrl, uint8_t const * const p_buf, uint32_t size, uint8_t destination)
{
    usb_info_t info;
    usb_er_t   err;
    fsp_err_t  result = FSP_ERR_USB_FAILED;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        FSP_ERROR_RETURN(((USB_CLASS_PCDC <= destination) && (destination < USB_CLASS_END)), FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        FSP_ASSERT(destination)
        FSP_ERROR_RETURN(USB_ADDRESS5 >= destination, FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_ctrl->type = (usb_class_t) (destination & USB_VALUE_7FH);
#endif                                 /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_ctrl->device_address = destination;
 #if defined(USB_CFG_HCDC_USE)

        /* Add the following code. */
        /* Because the value of "type" member change to "USB_CLASS_INTERNAL_HCDCC" */
        /* when calling R_USB_HCDC_ControlDataRead function. */
        p_ctrl->type = (usb_class_t) USB_CLASS_INTERNAL_HCDC;
 #endif                                /* defined(USB_CFG_HCDC_USE) */
#endif                                 /* USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(!((USB_NULL == p_buf) && (0 != size)))

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

 #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
 #endif

    FSP_ERROR_RETURN(!((USB_CLASS_INTERNAL_HCDCC == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_PVND == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_HVND == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_HMSC == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_PMSC == (usb_class_internal_t) p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] &
                                  (1 << p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
#endif  /* USB_CFG_PARAM_CHECKING_ENABLE */

#if (USB_CFG_DMA == USB_CFG_ENABLE)
    if (USB_IP0 == p_ctrl->module_number)
    {
        /* Alignment checking if "p_buf" is 2-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_2_BYTE)), FSP_ERR_USB_PARAMETER)
    }

 #if defined(USB_HIGH_SPEED_MODULE)
    else
    {
        /* Alignment checking if "p_buf" is 4-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_4_BYTE)), FSP_ERR_USB_PARAMETER)
    }
 #endif                                /* defined(USB_HIGH_SPEED_MODULE) */
#endif /* (USB_CFG_DMA == USB_CFG_ENABLE) */

    (void) R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        err = usb_data_write(p_ctrl, p_buf, size);

        if (USB_OK == err)
        {
            result = FSP_SUCCESS;
        }
        else if (USB_QOVR == err)
        {
            result = FSP_ERR_USB_BUSY;
        }
        else
        {
            /* Noting */
        }
    }

    return result;
}

/**************************************************************************//**
 * @brief Requests a data read/write transfer be terminated
 * when a data read/write transfer is being performed.
 *
 * To stop a data read, set USB_TRANSFER_READ as the argument (type); to stop a data write,
 * specify USB_WRITE as the argument (type).
 *
 * @retval FSP_SUCCESS           Successfully completed. (stop completed)
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter is NULL error.
 * @retval FSP_ERR_USB_BUSY      Stop processing is called multiple times.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_Stop (usb_ctrl_t * const p_api_ctrl, usb_transfer_t direction, uint8_t destination)
{
    usb_info_t info;
    usb_er_t   err;
    fsp_err_t  result = FSP_ERR_USB_FAILED;
    info.device_status = 0;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        FSP_ERROR_RETURN(((USB_CLASS_PCDC <= destination) && (destination < USB_CLASS_END)), FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        FSP_ASSERT(destination)
        FSP_ERROR_RETURN(USB_ADDRESS5 >= destination, FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_ctrl->type = (usb_class_t) (destination & USB_VALUE_7FH);
#endif                                 /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_ctrl->device_address = destination;
#endif                                 /* USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(!((USB_TRANSFER_WRITE != direction) && (USB_TRANSFER_READ != direction)), FSP_ERR_USB_PARAMETER)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

 #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
 #endif

    FSP_ERROR_RETURN(!((USB_CLASS_INTERNAL_PVND == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_HVND == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_HMSC == (usb_class_internal_t) p_ctrl->type) ||
                       (USB_CLASS_INTERNAL_PMSC == (usb_class_internal_t) p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(!(((USB_CLASS_INTERNAL_HCDCC == (usb_class_internal_t) p_ctrl->type) &&
                        (USB_TRANSFER_WRITE == direction)) ||
                       ((USB_CLASS_INTERNAL_PCDCC == (usb_class_internal_t) p_ctrl->type) &&
                        (USB_TRANSFER_READ == direction))),
                     FSP_ERR_USB_PARAMETER)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    (void) R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    err = usb_data_stop(p_ctrl, direction);

    if (USB_OK == err)
    {
        result = FSP_SUCCESS;
    }
    else if (USB_QOVR == err)
    {
        result = FSP_ERR_USB_BUSY;
    }
    else
    {
        /* Nothing */
    }

    return result;
}

/**************************************************************************//**
 * @brief Sends a SUSPEND signal from the USB module assigned to the member
 * (module) of the usb_crtl_t structure.
 *
 * After the suspend request is completed, confirm the operation with the return value
 * (USB_STATUS_SUSPEND) of the R_USB_EventGet function.
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY      During a suspend request to the specified USB module,
 *                               or when the USB module is already in the suspended state.
 * @retval FSP_ERR_ASSERTION     Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_Suspend (usb_ctrl_t * const p_api_ctrl)
{
#if USB_CFG_MODE == USB_CFG_PERI
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_USB_FAILED;         /* Support Host only. */
#else  /* USB_CFG_MODE == USB_CFG_PERI */
    fsp_err_t ret_code = FSP_SUCCESS;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    FSP_PARAMETER_NOT_USED(*p_ctrl);
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t  utr;
    usb_info_t info;
    usb_er_t   err;
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    FSP_ERROR_RETURN(USB_MODE_PERI != g_usb_usbmode[p_ctrl->module_number], FSP_ERR_USB_FAILED)

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

  #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
  #endif
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    p_ctrl->device_address = USB_DEVICEADDR;

    ret_code = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    utr.ip  = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
  #if (BSP_CFG_RTOS == 0)
    if (USB_NULL != (g_usb_change_device_state[p_ctrl->module_number] & (1 << USB_STATUS_SUSPEND)))
    {
        return FSP_ERR_USB_BUSY;
    }

    err = usb_hstd_change_device_state(&utr,
                                       (usb_cb_t) &usb_hstd_suspend_complete,
                                       USB_DO_GLOBAL_SUSPEND,
                                       USB_DEVICEADDR);

    if (USB_OK == err)
    {
        g_usb_change_device_state[p_ctrl->module_number] |= (1 << USB_STATUS_SUSPEND);
    }
    else
    {
        ret_code = FSP_ERR_USB_FAILED;
    }

  #else                                /* (BSP_CFG_RTOS == 0) */
    if (USB_YES == gs_usb_suspend_ing[p_ctrl->module_number])
    {
        ret_code = FSP_ERR_USB_BUSY;
    }
    else
    {
        gs_usb_suspend_ing[p_ctrl->module_number] = USB_YES;
    }

    err = usb_hstd_change_device_state(&utr,
                                       (usb_cb_t) &usb_hstd_suspend_complete,
                                       USB_DO_GLOBAL_SUSPEND,
                                       USB_DEVICEADDR);

    if (USB_OK != err)
    {
        ret_code = FSP_ERR_USB_FAILED;
    }
    gs_usb_suspend_ing[p_ctrl->module_number] = USB_NO;
  #endif                               /* (BSP_CFG_RTOS == 0) */
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    return ret_code;
#endif                                 /* USB_CFG_MODE == USB_CFG_PERI */
}

/**************************************************************************//**
 * @brief Sends a RESUME signal from the USB module assigned to the
 * member (module) of the usb_ctrl_tstructure.
 *
 * After the resume request is completed, confirm the operation with the return
 * value (USB_STATUS_RESUME) of the R_USB_EventGet function
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY         Resume already requested for same device address.
 *                                  (USB host mode only)
 * @retval FSP_ERR_USB_NOT_SUSPEND  USB device is not in the SUSPEND state.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_Resume (usb_ctrl_t * const p_api_ctrl)
{
#if USB_CFG_MODE == USB_CFG_PERI
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_USB_FAILED;         /* Support Host only. */
#else  /* USB_CFG_MODE == USB_CFG_PERI */
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_utr_t utr;
    usb_er_t  err;

    fsp_err_t  ret_code = FSP_ERR_USB_FAILED;
    usb_info_t info;
    info.device_status = 0;

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

  #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
  #endif

    FSP_ERROR_RETURN(USB_MODE_PERI != g_usb_usbmode[p_ctrl->module_number], FSP_ERR_USB_PARAMETER)
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    ret_code = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_SUSPEND == info.device_status, FSP_ERR_USB_NOT_SUSPEND)

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    utr.ip  = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

  #if (BSP_CFG_RTOS == 0)
    if (USB_NULL != (g_usb_change_device_state[p_ctrl->module_number] & (1 << USB_STATUS_RESUME)))
    {
        return FSP_ERR_USB_BUSY;
    }

    err = usb_hstd_change_device_state(&utr,
                                       (usb_cb_t) &usb_hstd_resume_complete,
                                       USB_DO_GLOBAL_RESUME,
                                       p_ctrl->device_address);
    if (USB_OK == err)
    {
        g_usb_change_device_state[p_ctrl->module_number] |= (1 << USB_STATUS_RESUME);
    }
    else
    {
        ret_code = FSP_ERR_USB_FAILED;
    }

  #else                                /* (BSP_CFG_RTOS == 0) */
    if (USB_YES == g_usb_resume_ing[p_ctrl->module_number])
    {
        ret_code = FSP_ERR_USB_BUSY;
    }
    else
    {
        g_usb_resume_ing[p_ctrl->module_number] = USB_YES;
    }

    if (FSP_ERR_USB_BUSY == ret_code)
    {
        return ret_code;
    }

    err = usb_hstd_change_device_state(&utr,
                                       (usb_cb_t) &usb_hstd_resume_complete,
                                       USB_DO_GLOBAL_RESUME,
                                       p_ctrl->device_address);
    if (USB_OK != err)
    {
        ret_code = FSP_ERR_USB_FAILED;
    }
    g_usb_resume_ing[p_ctrl->module_number] = USB_NO;
  #endif                               /* (BSP_CFG_RTOS == 0) */
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    return ret_code;
#endif                                 /* USB_CFG_MODE == USB_CFG_PERI */
}

/**************************************************************************//**
 * @brief Specifies starting or stopping the VBUS supply.
 *
 * @retval FSP_SUCCESS              Successful completion. (VBUS supply start/stop completed)
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_VbusSet (usb_ctrl_t * const p_api_ctrl, uint16_t state)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if defined(USB_CFG_OTG_USE)
    uint16_t syssts;
#endif                                 /* defined(USB_CFG_OTG_USE) */

#if (USB_CFG_MODE == USB_CFG_PERI)
    FSP_PARAMETER_NOT_USED(state);
    FSP_PARAMETER_NOT_USED(*p_ctrl);

    return FSP_ERR_USB_FAILED;
#else
    usb_utr_t utr;

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

  #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
  #endif                               /* defined(BSP_BOARD_GROUP_RA2A1)  */

    FSP_ERROR_RETURN(!((USB_ON != state) && (USB_OFF != state)), FSP_ERR_USB_PARAMETER)
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    utr.ip  = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

    if (USB_ON == state)
    {
        usb_hstd_vbus_control(&utr, (uint16_t) USB_VBON);
    }
    else
    {
        usb_hstd_vbus_control(&utr, (uint16_t) USB_VBOFF);
 #if defined(USB_CFG_OTG_USE)
        if (1 == g_is_A_device[utr.ip])
        {
            usb_cpu_delay_xms((uint16_t) USB_VALUE_50);

            syssts = hw_usb_read_syssts(&utr);

            if (USB_SE0 == (syssts & USB_LNST))
            {
                utr.ipp->INTENB1 |= USB_BCHGE;
            }
        }
        else
        {
            return FSP_ERR_USB_FAILED;
        }
 #endif                                /* defined (USB_CFG_OTG_USE) */
    }
    return FSP_SUCCESS;
#endif                                 /* (USB_CFG_MODE == USB_CFG_PERI) */
}

/**************************************************************************//**
 * @brief Obtains completed USB-related events.
 *
 * @retval FSP_SUCCESS              Successful completion. (VBUS supply start/stop completed)
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_InfoGet (usb_ctrl_t * const p_api_ctrl, usb_info_t * p_info, uint8_t destination)
{
    fsp_err_t             ret_code = FSP_SUCCESS;
    usb_instance_ctrl_t * p_ctrl   = (usb_instance_ctrl_t *) p_api_ctrl;
    usb_utr_t             utr;

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    uint32_t status;
    FSP_PARAMETER_NOT_USED(destination);
#endif                                 /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
    FSP_ASSERT(p_info)

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        FSP_ASSERT(destination)
        FSP_ERROR_RETURN(USB_ADDRESS5 >= destination, FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

 #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
 #endif                                /* #if defined(BSP_BOARD_GROUP_RA2A1) */
#else                                  /* USB_CFG_PARAM_CHECKING_ENABLE */
    FSP_PARAMETER_NOT_USED(*p_ctrl);
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_ctrl->device_address = destination;
#endif                                         /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }

    p_info->device_status = USB_STATUS_DETACH; /* Initialized for warning measures. */

    FSP_ERROR_RETURN(0 != g_usb_open_class[p_ctrl->module_number], FSP_ERR_USB_FAILED)

    utr.ip = p_ctrl->module_number;

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        /* Set USB Device class */
        switch (g_usb_hstd_device_info[utr.ip][p_ctrl->device_address][3])
        {
            case USB_IFCLS_CDC:
            {
                p_info->class_type = (uint8_t) USB_CLASS_PCDC;
                break;
            }

            case USB_IFCLS_HID:
            {
                p_info->class_type = (uint8_t) USB_CLASS_PHID;
                break;
            }

            case USB_IFCLS_MAS:
            {
                p_info->class_type = (uint8_t) USB_CLASS_PMSC;
                break;
            }

            case USB_IFCLS_VEN:
            {
                p_info->class_type = (uint8_t) USB_CLASS_PVND;
                break;
            }

            default:
            {
                p_info->class_type = USB_NULL;
                break;
            }
        }

        /* Set USB connect speed */
        switch (g_usb_hstd_device_info[utr.ip][p_ctrl->device_address][4])
        {
            case USB_NOCONNECT:
            {
                p_info->speed = USB_NULL;
                break;
            }

            case USB_HSCONNECT:
            {
                p_info->speed = USB_SPEED_HS;
                break;
            }

            case USB_FSCONNECT:
            {
                p_info->speed = USB_SPEED_FS;
                break;
            }

            case USB_LSCONNECT:
            {
                p_info->speed = USB_SPEED_LS;
                break;
            }

            default:
            {
                p_info->speed = USB_NULL;
                break;
            }
        }

        /* Set USB device state */
        switch (g_usb_hstd_device_info[utr.ip][p_ctrl->device_address][1])
        {
            case USB_POWERED:          /* Power state  */
            {
                p_info->device_status = USB_STATUS_POWERED;
                break;
            }

            case USB_DEFAULT:          /* Default state  */
            {
                p_info->device_status = USB_STATUS_DEFAULT;
                break;
            }

            case USB_ADDRESS:          /* Address state  */
            {
                p_info->device_status = USB_STATUS_ADDRESS;
                break;
            }

            case USB_CONFIGURED:       /* Configured state  */
            {
                p_info->device_status = USB_STATUS_CONFIGURED;
                break;
            }

            case USB_SUSPENDED:        /* Suspend state */
            {
                p_info->device_status = USB_STATUS_SUSPEND;
                break;
            }

            case USB_DETACHED:         /* Disconnect(VBUSon) state */
            {
                p_info->device_status = USB_STATUS_DETACH;
                break;
            }

            default:                   /* Error */
            {
                p_info->device_status = USB_NULL;
                break;
            }
        }

        /* Set USB Peri BC port state */
 #if USB_CFG_BC == USB_CFG_ENABLE
        if (USB_DEVICEADDR == p_ctrl->device_address) /* Check Root port address */
        {
            if (USB_BC_STATE_CDP == g_usb_hstd_bc[utr.ip].state)
            {
                p_info->bcport = USB_BCPORT_CDP;
            }
            else
            {
                p_info->bcport = USB_BCPORT_SDP; /* USB_SDP/USB_CDP/USB_DCP */
            }
        }
        else
        {
            p_info->bcport = USB_BCPORT_SDP; /* USB_SDP/USB_CDP/USB_DCP */
        }

 #else  /* #if USB_CFG_BC == USB_CFG_ENABLE */
        p_info->bcport = USB_BCPORT_SDP;     /* USB_SDP/USB_CDP/USB_DCP */
 #endif  /* #if USB_CFG_BC == USB_CFG_ENABLE */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_info->class_type = USB_NULL; /* Device class */
        switch (usb_cstd_port_speed(&utr))
        {
            case USB_NOCONNECT:
            {
                p_info->speed = USB_NULL;
                break;
            }

            case USB_HSCONNECT:
            {
                p_info->speed = USB_SPEED_HS;
                break;
            }

            case USB_FSCONNECT:
            {
                p_info->speed = USB_SPEED_FS;
                break;
            }

            case USB_LSCONNECT:
            {
                p_info->speed = USB_SPEED_LS;
                break;
            }

            default:
            {
                p_info->speed = USB_NULL;
                break;
            }
        }

        status = hw_usb_read_intsts(p_ctrl->module_number);
        switch ((uint16_t) (status & USB_DVSQ))
        {
            case USB_DS_POWR:          /* Power state  */
            {
                p_info->device_status = USB_STATUS_DETACH;
                break;
            }

            case USB_DS_DFLT:          /* Default state  */
            {
                p_info->device_status = USB_STATUS_DEFAULT;
                break;
            }

            case USB_DS_ADDS:          /* Address state  */
            {
                p_info->device_status = USB_STATUS_ADDRESS;
                break;
            }

            case USB_DS_CNFG:          /* Configured state  */
            {
                p_info->device_status = USB_STATUS_CONFIGURED;
                break;
            }

            case USB_DS_SPD_POWR:      /* Power suspend state */
            case USB_DS_SPD_DFLT:      /* Default suspend state */
            case USB_DS_SPD_ADDR:      /* Address suspend state */
            case USB_DS_SPD_CNFG:      /* Configured Suspend state */
            {
                p_info->device_status = USB_STATUS_SUSPEND;
                break;
            }

            default:                   /* Error */
            {
                break;                 /* p_info->device_status = USB_STS_ERROR; */
            }
        }

 #if USB_CFG_BC == USB_CFG_ENABLE
        p_info->bcport = (uint8_t) g_usb_bc_detect; /* USB_SDP/USB_CDP/USB_DCP */
 #else  /* USB_CFG_BC == USB_CFG_ENABLE */
        p_info->bcport = USB_BCPORT_SDP;            /* USB_SDP */
 #endif  /* USB_CFG_BC == USB_CFG_ENABLE */
        ret_code = FSP_SUCCESS;
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return ret_code;
}

/**************************************************************************//**
 * @brief Requests a data read (Bulk/Interrupt transfer) via the pipe specified in the argument.
 *
 * The read data is stored in the area specified in the argument (p_buf).
 * After the data read is completed, confirm the operation with the R_USB_GetEvent function
 * return value(USB_STATUS_READ_COMPLETE).
 * To figure out the size of the data when a read is complete, check the return
 * value (USB_STATUS_READ_COMPLETE) of the R_USB_GetEvent function, and then
 * refer to the member (size) of the usb_crtl_t structure.
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_BUSY         Specified pipe now handling data receive/send request.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note 1. Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 * @note 2. Allocate the following the storage area when using DMA transfer and specify the start address of the allocated storage area to the 2nd argument(p_buf).
 * @note (1). When using High-speed and enabling continuous transfer mode, allocate the storage area with a size that is a multiple of 2048.
 * @note (2). When using High-speed and disabling continuous transfer mode, allocate the storage area with a size that is a multiple of 512.
 * @note (3). When using Full-speed, allocate the storage area with a size that is a multiple of 64.
 * @note 3. Specify the following address to the 2nd argument (p_buf) when using DMA transfer.
 * @note  (1). When using High-speed module, specify start address of the buffer area aligned on 4-byte boundary.
 * @note  (2). When using Full-speed module, specify start address of the buffer area aligned on 2-byte boundary.
 ******************************************************************************/
fsp_err_t R_USB_PipeRead (usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size, uint8_t pipe_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)
    FSP_PARAMETER_NOT_USED(*p_ctrl);
    FSP_PARAMETER_NOT_USED(*p_buf);
    FSP_PARAMETER_NOT_USED(size);
    FSP_PARAMETER_NOT_USED(pipe_number);

    return FSP_ERR_USB_FAILED;
#else                                  /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */
    fsp_err_t   ret_code = FSP_ERR_USB_FAILED;
    usb_utr_t * p_tran_data;
 #if (BSP_CFG_RTOS != 0)
    usb_utr_t tran_data;
 #endif                                /* (BSP_CFG_RTOS != 0) */

    usb_er_t   err;
    usb_info_t info;

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->pipe = pipe_number;

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    p_ctrl->device_address = USB_ADDRESS1;
 #endif                                /* USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(((USB_MIN_PIPE_NO <= p_ctrl->pipe) && (p_ctrl->pipe <= USB_MAX_PIPE_NO)), FSP_ERR_USB_PARAMETER)

    FSP_ASSERT(!((USB_NULL == p_buf) || (USB_NULL == size)))

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] &
                                  (1 << p_ctrl->type)),
                     FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
 #endif  /* USB_CFG_PARAM_CHECKING_ENABLE */

 #if (USB_CFG_DMA == USB_CFG_ENABLE)
    if (USB_IP0 == p_ctrl->module_number)
    {
        /* Alignment checking if "p_buf" is 2-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_2_BYTE)), FSP_ERR_USB_PARAMETER)
    }

  #if defined(USB_HIGH_SPEED_MODULE)
    else
    {
        /* Alignment checking if "p_buf" is 4-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_4_BYTE)), FSP_ERR_USB_PARAMETER)
    }
  #endif                               /* defined(USB_HIGH_SPEED_MODULE) */
 #endif /* (USB_CFG_DMA == USB_CFG_ENABLE) */

    ret_code = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        /* PIPE Transfer set */
        if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
        {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
  #if (BSP_CFG_RTOS != 0)
            p_tran_data = &tran_data;
  #else                                /* (BSP_CFG_RTOS != 0) */
            p_tran_data = &g_usb_hdata[p_ctrl->module_number][p_ctrl->pipe];
  #endif  /* (BSP_CFG_RTOS != 0) */

            p_tran_data->ip           = p_ctrl->module_number;
            p_tran_data->ipp          = usb_hstd_get_usb_ip_adr(p_tran_data->ip);
            p_tran_data->keyword      = p_ctrl->pipe;           /* Pipe No */
            p_tran_data->p_tranadr    = p_buf;                  /* Data address */
            p_tran_data->tranlen      = size;                   /* Data Size */
            p_tran_data->p_setup      = 0;
            p_tran_data->complete     = usb_hvnd_read_complete; /* Callback function */
            p_tran_data->segment      = USB_TRAN_END;
            p_tran_data->read_req_len = size;                   /* Data Size */

  #if (USB_CFG_DMA == USB_CFG_ENABLE)
            if (0 != p_ctrl->p_transfer_tx)
            {
                p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
            }
            else
            {
                p_tran_data->p_transfer_tx = 0;
            }

            if (0 != p_ctrl->p_transfer_rx)
            {
                p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
            }
            else
            {
                p_tran_data->p_transfer_rx = 0;
            }
  #endif

            err = usb_hstd_transfer_start(p_tran_data); /* USB Transfer Start */
            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
  #if (BSP_CFG_RTOS != 0)
            p_tran_data = &tran_data;
  #else                                                                     /* (BSP_CFG_RTOS != 0) */
            p_tran_data = &g_usb_pdata[p_ctrl->pipe];
  #endif  /* (BSP_CFG_RTOS != 0) */

            p_tran_data->ip           = p_ctrl->module_number;              /* USB Module Number */
            p_tran_data->keyword      = p_ctrl->pipe;                       /* Pipe No */
            p_tran_data->p_tranadr    = p_buf;                              /* Data address */
            p_tran_data->tranlen      = size;                               /* Data Size */
            p_tran_data->complete     = (usb_cb_t) &usb_pvnd_read_complete; /* Callback function */
            p_tran_data->read_req_len = size;                               /* Data Size */
            p_tran_data->p_setup      = 0;

  #if (USB_CFG_DMA == USB_CFG_ENABLE)
            if (0 != p_ctrl->p_transfer_tx)
            {
                p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
            }
            else
            {
                p_tran_data->p_transfer_tx = 0;
            }

            if (0 != p_ctrl->p_transfer_rx)
            {
                p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
            }
            else
            {
                p_tran_data->p_transfer_rx = 0;
            }
  #endif

            err = usb_pstd_transfer_start(p_tran_data); /* USB Transfer Start */
            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        }
    }
    else
    {
        ret_code = FSP_ERR_USB_FAILED;
    }
    return ret_code;
#endif                                 /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */
}

/**************************************************************************//**
 * @brief Requests a data write (Bulk/Interrupt transfer).
 *
 * The write data is stored in the area specified in the argument (p_buf).
 * After data write is completed, confirm the operation with the return value
 * (USB_STATUS_WRITE_COMPLETE) of the EventGet function.
 * For sending a zero-length packet, please refer the following Note.
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_BUSY         Specified pipe now handling data receive/send request.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note 1. The user needs to send the zero-length packet(ZLP) since this USB driver does not send the ZLP automatically.
 * @note   When sending a ZLP, the user sets USB_NULL in the third argument (size) of R_USB_PipeWrite function as follow.
 * @note   e.g)
 * @note   R_USB_PipeWrite (&g_basic0_ctrl, &g_buf, USB_NULL, pipe_number);
 * @note 2. Specify the following address to the 2nd argument (p_buf) when using DMA transfer.
 * @note  (1). When using High-speed module, specify start address of the buffer area aligned on 4-byte boundary.
 * @note  (2). When using Full-speed module, specify start address of the buffer area aligned on 2-byte boundary.
 * @note 3. Do not call this API in the following function.
 * @note  (1). Interrupt function.
 * @note  (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_PipeWrite (usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size, uint8_t pipe_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)
    FSP_PARAMETER_NOT_USED(*p_ctrl);
    FSP_PARAMETER_NOT_USED(*p_buf);
    FSP_PARAMETER_NOT_USED(size);
    FSP_PARAMETER_NOT_USED(pipe_number);

    return FSP_ERR_USB_FAILED;
#else
    usb_er_t    err;
    fsp_err_t   ret_code;
    usb_info_t  info;
    usb_utr_t * p_tran_data;
 #if (BSP_CFG_RTOS != 0)
    usb_utr_t tran_data;
 #endif                                /* (BSP_CFG_RTOS != 0) */

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->pipe = pipe_number;

 #if USB_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(((USB_MIN_PIPE_NO <= p_ctrl->pipe) && (p_ctrl->pipe <= USB_MAX_PIPE_NO)), FSP_ERR_USB_PARAMETER)

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        FSP_ASSERT(!((USB_NULL == p_buf) && (0 != size)))
  #endif                               /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    else
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_ctrl->device_address = USB_ADDRESS1;
  #endif                                                                                                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */                                                                                                /* USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] & (1 << p_ctrl->type)), FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
 #endif /* USB_CFG_PARAM_CHECKING_ENABLE */                                                                                                                  /* USB_CFG_PARAM_CHECKING_ENABLE */

 #if (USB_CFG_DMA == USB_CFG_ENABLE)
    if (USB_IP0 == p_ctrl->module_number)
    {
        /* Alignment checking if "p_buf" is 2-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_2_BYTE)), FSP_ERR_USB_PARAMETER)
    }

  #if defined(USB_HIGH_SPEED_MODULE)
    else
    {
        /* Alignment checking if "p_buf" is 4-byte boundary */
        FSP_ERROR_RETURN((0 == ((uint32_t) p_buf & USB_MASK_ALIGN_4_BYTE)), FSP_ERR_USB_PARAMETER)
    }
  #endif                               /* defined(USB_HIGH_SPEED_MODULE) */
 #endif /* (USB_CFG_DMA == USB_CFG_ENABLE) */

    ret_code = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        /* PIPE Transfer set */
        if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
        {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
  #if (BSP_CFG_RTOS != 0)
            p_tran_data = &tran_data;
  #else                                /* (BSP_CFG_RTOS != 0) */
            p_tran_data = &g_usb_hdata[p_ctrl->module_number][p_ctrl->pipe];
  #endif  /* (BSP_CFG_RTOS != 0) */

            p_tran_data->ip        = p_ctrl->module_number;
            p_tran_data->ipp       = usb_hstd_get_usb_ip_adr(p_ctrl->module_number);
            p_tran_data->keyword   = p_ctrl->pipe;            /* Pipe No */
            p_tran_data->p_tranadr = p_buf;                   /* Data address */
            p_tran_data->tranlen   = size;                    /* Data Size */
            p_tran_data->complete  = usb_hvnd_write_complete; /* Callback function */
            p_tran_data->segment   = USB_TRAN_END;
            p_tran_data->p_setup   = 0;

  #if (USB_CFG_DMA == USB_CFG_ENABLE)
            if (0 != p_ctrl->p_transfer_tx)
            {
                p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
            }
            else
            {
                p_tran_data->p_transfer_tx = 0;
            }

            if (0 != p_ctrl->p_transfer_rx)
            {
                p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
            }
            else
            {
                p_tran_data->p_transfer_rx = 0;
            }
  #endif                               /* (USB_CFG_DMA == USB_CFG_ENABLE) */

            err = usb_hstd_transfer_start(p_tran_data);
            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
  #if (BSP_CFG_RTOS != 0)
            p_tran_data = &tran_data;
  #else                                                       /* (BSP_CFG_RTOS != 0) */
            p_tran_data = &g_usb_pdata[p_ctrl->pipe];
  #endif  /* (BSP_CFG_RTOS != 0) */

            p_tran_data->ip        = p_ctrl->module_number;   /* USB Module Number */
            p_tran_data->keyword   = p_ctrl->pipe;            /* Pipe No */
            p_tran_data->p_tranadr = p_buf;                   /* Data address */
            p_tran_data->tranlen   = size;                    /* Data Size */
            p_tran_data->complete  = usb_pvnd_write_complete; /* Callback function */
            p_tran_data->p_setup   = 0;

  #if (USB_CFG_DMA == USB_CFG_ENABLE)
            if (0 != p_ctrl->p_transfer_tx)
            {
                p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
            }
            else
            {
                p_tran_data->p_transfer_tx = 0;
            }

            if (0 != p_ctrl->p_transfer_rx)
            {
                p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
            }
            else
            {
                p_tran_data->p_transfer_rx = 0;
            }
  #endif                               /* (USB_CFG_DMA == USB_CFG_ENABLE) */

            err = usb_pstd_transfer_start(p_tran_data);

            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        }
    }
    else
    {
        ret_code = FSP_ERR_USB_FAILED;
    }
    return ret_code;
#endif                                 /* #if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */
}

/**************************************************************************//**
 * @brief Terminates a data read/write operation.
 *
 * @retval FSP_SUCCESS              Successfully completed. (Stop request completed)
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_PipeStop (usb_ctrl_t * const p_api_ctrl, uint8_t pipe_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)
    FSP_PARAMETER_NOT_USED(*p_ctrl);
    FSP_PARAMETER_NOT_USED(pipe_number);

    return FSP_ERR_USB_FAILED;
#else
    usb_er_t   err      = FSP_ERR_USB_FAILED;
    fsp_err_t  ret_code = FSP_ERR_USB_FAILED;
    usb_info_t info     = {USB_NULL, USB_NULL, USB_NULL, USB_NULL};
    usb_utr_t  utr;

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    utr.ip = p_ctrl->module_number;    /* Update USB module number */

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
        utr.ipp                = usb_hstd_get_usb_ip_adr(utr.ip);
        p_ctrl->device_address = USB_ADDRESS1;
    }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    p_ctrl->pipe = pipe_number;

 #if USB_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_PIPE0 != p_ctrl->pipe, FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_MAXPIPE_NUM > p_ctrl->pipe, FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(USB_NULL != (g_usb_open_class[p_ctrl->module_number] & (1 << p_ctrl->type)), FSP_ERR_USB_PARAMETER) /* Check USB Open device class */
 #endif  /* USB_CFG_PARAM_CHECKING_ENABLE */

    ret_code = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        err = usb_hstd_transfer_end(&utr, p_ctrl->pipe, (uint16_t) USB_DATA_STOP);
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        err = usb_pstd_transfer_end(&utr, p_ctrl->pipe);
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    if (USB_OK == err)
    {
        ret_code = FSP_SUCCESS;
    }
    return ret_code;
#endif                                 /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */
}

/**************************************************************************//**
 * @brief Gets the selected pipe number (number of the pipe that has completed initalization) via bit map information.
 *
 * The bit map information is stored in the area specified in argument (p_pipe).
 * Based on the information (module member and address member) assigned to the usb_ctrl_t structure,
 * obtains the PIPE information of that USB device.
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_UsedPipesGet (usb_ctrl_t * const p_api_ctrl, uint16_t * p_pipe, uint8_t destination)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_info_t info;
    uint32_t   pipe_no;

    info.device_status = 0;

    FSP_PARAMETER_NOT_USED(*p_ctrl);
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    FSP_PARAMETER_NOT_USED(destination);
#endif                                 /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(!((USB_NULL == p_ctrl) || (USB_NULL == p_pipe)))

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        FSP_ASSERT(destination)
        FSP_ERROR_RETURN(USB_ADDRESS5 >= destination, FSP_ERR_USB_PARAMETER)
 #endif                                /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

 #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(USB_IP1 != p_ctrl->module_number, FSP_ERR_USB_PARAMETER)
 #endif                                /* defined(BSP_BOARD_GROUP_RA2A1)  */
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_ctrl->device_address = destination;
#endif                                 /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }

    R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    /* Get PIPE Number from Endpoint address */
    * p_pipe = ((uint16_t) 1 << USB_PIPE0);
    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
        {
            if (USB_TRUE == g_usb_pipe_table[p_ctrl->module_number][pipe_no].use_flag)
            {
                if ((((uint16_t) p_ctrl->device_address) << USB_DEVADDRBIT) ==
                    (uint16_t) (g_usb_pipe_table[p_ctrl->module_number][pipe_no].pipe_maxp & USB_DEVSEL))
                {
                    (*p_pipe) = (uint16_t) ((*p_pipe) | (uint16_t) 1 << pipe_no);
                }
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
        {
            if (USB_TRUE == g_usb_pipe_table[p_ctrl->module_number][pipe_no].use_flag)
            {
                (*p_pipe) = (uint16_t) ((*p_pipe) | (uint16_t) (1 << pipe_no));
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief Gets the following pipe information regarding the pipe specified in the
 * argument (p_ctrl) member (pipe): endpoint number, transfer type,
 * transfer direction and maximum packet size.
 *
 * The obtained pipe information is stored in the area specified in the argument (p_info).
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_PipeInfoGet (usb_ctrl_t * const p_api_ctrl, usb_pipe_t * p_info, uint8_t pipe_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_info_t info;
    info.device_status = 0;
    uint32_t  pipe_type;
    fsp_err_t result = FSP_ERR_ASSERTION;
    usb_utr_t utr;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
    FSP_ASSERT(p_info)
    FSP_ASSERT(pipe_number)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->pipe = pipe_number;

#if USB_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)

    FSP_ERROR_RETURN(!(USB_MAXPIPE_NUM < p_ctrl->pipe), FSP_ERR_USB_PARAMETER)

 #if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ERROR_RETURN(!((USB_IP1 == p_ctrl->module_number) && (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])),
                     FSP_ERR_USB_PARAMETER)
 #endif
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    utr.ip = p_ctrl->module_number;
    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ipp                = usb_hstd_get_usb_ip_adr(utr.ip);
        p_ctrl->device_address = USB_ADDRESS1;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_info->endpoint = usb_hstd_pipe_to_epadr(&utr, p_ctrl->pipe);
        pipe_type        = usb_cstd_get_pipe_type(&utr, p_ctrl->pipe);

        switch (pipe_type)
        {
            case USB_TYPFIELD_ISO:
            {
                p_info->transfer_type = USB_TRANSFER_TYPE_ISO; /* Set Isochronous */
                break;
            }

            case USB_TYPFIELD_BULK:
            {
                p_info->transfer_type = USB_TRANSFER_TYPE_BULK; /* Set Bulk */
                break;
            }

            case USB_TYPFIELD_INT:
            {
                p_info->transfer_type = USB_TRANSFER_TYPE_INT; /* Set Interrupt */
                break;
            }

            default:
            {
                result = FSP_ERR_USB_FAILED;
                break;
            }
        }

        if (FSP_ERR_USB_FAILED != result)
        {
            p_info->maxpacketsize = usb_cstd_get_maxpacket_size(&utr, p_ctrl->pipe); /* Set Max packet size */
            result                = FSP_SUCCESS;
        }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

        /* Get PIPE Number from Endpoint address */
        p_info->endpoint = (uint8_t) (g_usb_pipe_table[p_ctrl->module_number][p_ctrl->pipe].pipe_cfg & USB_EPNUMFIELD); /* Set EP num. */
        if (USB_DIR_P_IN == (g_usb_pipe_table[p_ctrl->module_number][p_ctrl->pipe].pipe_cfg & USB_DIRFIELD))            /* Check dir */
        {
            p_info->endpoint |= USB_EP_DIR_IN;                                                                          /* Set DIR IN */
        }

        pipe_type = usb_cstd_get_pipe_type(&utr, p_ctrl->pipe);

        switch (pipe_type)
        {
            case USB_TYPFIELD_ISO:
            {
                p_info->transfer_type = USB_TRANSFER_TYPE_ISO; /* Set Isochronous */
                break;
            }

            case USB_TYPFIELD_BULK:
            {
                p_info->transfer_type = USB_TRANSFER_TYPE_BULK; /* Set Bulk */
                break;
            }

            case USB_TYPFIELD_INT:
            {
                p_info->transfer_type = USB_TRANSFER_TYPE_INT; /* Set Interrupt */
                break;
            }

            default:
            {
                result = FSP_ERR_USB_FAILED;
                break;
            }
        }

        if (FSP_ERR_USB_FAILED != result)
        {
            p_info->maxpacketsize = usb_cstd_get_maxpacket_size(&utr, p_ctrl->pipe); /* Set Max packet size */
            result                = FSP_SUCCESS;
        }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return result;
}

/**************************************************************************//**
 * @brief This API enables or disables pull-up of D+/D- line.
 *
 * @retval FSP_SUCCESS              Successful completion. (Pull-up enable/disable setting completed)
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_PullUp (usb_ctrl_t * const p_api_ctrl, uint8_t state)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if (USB_CFG_MODE == USB_CFG_HOST)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(state);

    return FSP_ERR_USB_FAILED;
#else                                  /* USB_CFG_MODE == USB_CFG_HOST */
 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_ON != state) && (USB_OFF != state)), FSP_ERR_USB_PARAMETER)
 #endif                                                                                            /* #if USB_CFG_PARAM_CHECKING_ENABLE */

    FSP_ERROR_RETURN(!(USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number]), FSP_ERR_USB_FAILED) /* Support Peri only. */

    hw_usb_pcontrol_dprpu(p_ctrl->module_number, state);

    return FSP_SUCCESS;
#endif                                 /* USB_CFG_MODE == USB_CFG_HOST */
} /* End of function R_USB_PullUp */

/**************************************************************************//**
 * @brief Performs settings and transmission processing when transmitting a setup packet.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @retval FSP_ERR_USB_BUSY         Specified pipe now handling data receive/send request.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_HostControlTransfer (usb_ctrl_t * const p_api_ctrl,
                                     usb_setup_t      * p_setup,
                                     uint8_t          * p_buf,
                                     uint8_t            device_address)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_er_t   err    = USB_ERROR;
    fsp_err_t  result = FSP_ERR_USB_FAILED;
    usb_info_t info;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
    FSP_ASSERT(p_setup)
    FSP_ASSERT(!((USB_NULL == p_buf) && (0 != p_setup->request_length)))
    FSP_ASSERT(device_address)

    FSP_ERROR_RETURN(USB_MAXDEVADDR >= device_address, FSP_ERR_USB_PARAMETER)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    result = R_USB_InfoGet(p_ctrl, &info, device_address);
    if (FSP_SUCCESS != result)
    {
        return FSP_ERR_USB_FAILED;
    }

    p_ctrl->device_address       = device_address;
    p_ctrl->setup.request_type   = p_setup->request_type;
    p_ctrl->setup.request_value  = p_setup->request_value;
    p_ctrl->setup.request_index  = p_setup->request_index;
    p_ctrl->setup.request_length = p_setup->request_length;

    if ((p_ctrl->setup.request_type & USB_DEV_TO_HOST) == USB_DEV_TO_HOST)
    {
        err = usb_ctrl_read(p_ctrl, p_buf, p_ctrl->setup.request_length);  /* Request Control transfer */
    }
    else
    {
        err = usb_ctrl_write(p_ctrl, p_buf, p_ctrl->setup.request_length); /* Request Control transfer */
    }

    if (err == USB_QOVR)
    {
        result = FSP_ERR_USB_BUSY;
    }
    else if (err == USB_ERROR)
    {
        result = FSP_ERR_USB_FAILED;
    }
    else
    {
        result = FSP_SUCCESS;
    }

    return result;
}

/**************************************************************************//**
 * @brief Receives data sent by control transfer.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_BUSY         Specified pipe now handling data receive/send request.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_PeriControlDataGet (usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_er_t   err    = USB_ERROR;
    fsp_err_t  result = FSP_ERR_USB_FAILED;
    usb_info_t info;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
    FSP_ASSERT(p_buf)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    result = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (FSP_SUCCESS != result)
    {
        return FSP_ERR_USB_FAILED;
    }

    err = usb_ctrl_read(p_ctrl, p_buf, size); /* Request Control transfer */
    if (err == USB_QOVR)
    {
        result = FSP_ERR_USB_BUSY;
    }
    else if (err == USB_ERROR)
    {
        result = FSP_ERR_USB_FAILED;
    }
    else
    {
        result = FSP_SUCCESS;
    }

    return result;
}

/**************************************************************************//**
 * @brief Performs transfer processing for control transfer.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_BUSY         Specified pipe now handling data receive/send request.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_PeriControlDataSet (usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_er_t   err    = USB_ERROR;
    fsp_err_t  result = FSP_ERR_USB_FAILED;
    usb_info_t info;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
    FSP_ASSERT(p_buf)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

    result = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (FSP_SUCCESS != result)
    {
        return FSP_ERR_USB_FAILED;
    }

    err = usb_ctrl_write(p_ctrl, p_buf, size); /* Request Control transfer */
    if (err == USB_QOVR)
    {
        result = FSP_ERR_USB_BUSY;
    }
    else if (err == USB_ERROR)
    {
        result = FSP_ERR_USB_FAILED;
    }
    else
    {
        result = FSP_SUCCESS;
    }

    return result;
}

/**************************************************************************//**
 * @brief Set the response to the setup packet.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_PARAMETER    Parameter error.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_PeriControlStatusSet (usb_ctrl_t * const p_api_ctrl, usb_setup_status_t status)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if (USB_CFG_MODE == USB_CFG_HOST)
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(status);

    return FSP_ERR_USB_FAILED;
#else                                  /* USB_CFG_MODE == USB_CFG_HOST */
    fsp_err_t  result = FSP_ERR_USB_FAILED;
    usb_info_t info;

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    result = R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    if (FSP_SUCCESS != result)
    {
        return FSP_ERR_USB_FAILED;
    }

    p_ctrl->status = (uint16_t) status;

    hw_usb_pcontrol_dcpctr_pid(p_ctrl->module_number, (uint16_t) status);

    return FSP_SUCCESS;
#endif                                 /* #if (USB_CFG_MODE == USB_CFG_HOST) */
}

/**************************************************************************//**
 * @brief Sends a remote wake-up signal to the connected Host.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @retval FSP_ERR_USB_NOT_SUSPEND  Device is not suspended.
 * @retval FSP_ERR_USB_BUSY         The device is in resume operation.
 * @note Do not call this API in the following function.
 * @note (1). Interrupt function.
 * @note (2). Callback function ( for RTOS ).
 ******************************************************************************/
fsp_err_t R_USB_RemoteWakeup (usb_ctrl_t * const p_api_ctrl)
{
    fsp_err_t ret_code = FSP_ERR_USB_FAILED;
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;
    usb_utr_t             utr;
    uint16_t              ret_val;

 #if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
 #endif                                /* USB_CFG_PARAM_CHECKING_ENABLE */

    utr.ip = p_ctrl->module_number;

 #if (BSP_CFG_RTOS == 0)
    ret_val = usb_cstd_remote_wakeup(&utr);
    switch (ret_val)
    {
        case USB_OK:
        {
            ret_code = FSP_SUCCESS;
            break;
        }

        case USB_QOVR:
        {
            ret_code = FSP_ERR_USB_NOT_SUSPEND;
            break;
        }

        case USB_ERROR:
        default:
        {
            ret_code = FSP_ERR_USB_FAILED;
            break;
        }
    }

 #else                                 /* (BSP_CFG_RTOS == 0) */
    if (USB_YES == g_usb_resume_ing[p_ctrl->module_number])
    {
        ret_code = FSP_ERR_USB_BUSY;
    }
    else
    {
        g_usb_resume_ing[p_ctrl->module_number] = USB_YES;
    }

    if (FSP_ERR_USB_BUSY == ret_code)
    {
        return ret_code;
    }

    ret_val = usb_cstd_remote_wakeup(&utr);
    switch (ret_val)
    {
        case USB_OK:
        {
            ret_code = FSP_SUCCESS;
            break;
        }

        case USB_QOVR:
        {
            ret_code = FSP_ERR_USB_NOT_SUSPEND;
            break;
        }

        case USB_ERROR:
        default:
        {
            ret_code = FSP_ERR_USB_FAILED;
            break;
        }
    }
    g_usb_resume_ing[p_ctrl->module_number] = USB_NO;
 #endif                                /* BSP_CFG_RTOS == 0 */
#else  /*((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)*/
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif  /*((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)*/

    return ret_code;
}

/**************************************************************************//**
 * @brief Activate USB Driver for USB Peripheral BareMetal.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @note Call this API in the in the infinite loop of the application program or a timer interrupt.
 ******************************************************************************/
fsp_err_t R_USB_DriverActivate (usb_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_ERR_USB_FAILED;
#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

#if (BSP_CFG_RTOS == 0)
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
        usb_cstd_usb_task();
        err = FSP_SUCCESS;
    }

#else                                  /* (BSP_CFG_RTOS == 0) */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    err = FSP_ERR_USB_FAILED;
#endif /* (BSP_CFG_RTOS == 0) */
    return err;
}

/**************************************************************************//**
 * @brief Set callback memory to USB Driver for USB Peripheral BareMetal.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @note Call this API after calling R_USB_Open function.
 ******************************************************************************/
fsp_err_t R_USB_CallbackMemorySet (usb_ctrl_t * const p_api_ctrl, usb_callback_args_t * p_callback_memory)
{
    fsp_err_t err = FSP_ERR_USB_FAILED;

#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)
    FSP_ASSERT(p_callback_memory)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE */

#if (BSP_CFG_RTOS == 0)
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
        g_usb_apl_callback_memory[p_ctrl->module_number] = p_callback_memory;
        err = FSP_SUCCESS;
    }

#else                                  /* (BSP_CFG_RTOS == 0) */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback_memory);
#endif  /* (BSP_CFG_RTOS == 0) */
    return err;
}

/**************************************************************************//**
 * @brief This API gets the module number.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_ModuleNumberGet (usb_ctrl_t * const p_api_ctrl, uint8_t * module_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *module_number = p_ctrl->module_number;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the class type.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @note In Bare-Metal, In the Bare-Metal version, please specify the variable specified by the 1st argument of
 *       the R_USB_EventGet function to the 1st argument of this API.
 * @note In the FreeRTOS, please specify one of the following to the 1st argument of this API.
 * @note 1. The 1st argument of the callback function specified in Conguration.
 * @note 2. The start address of the area where the structure area of the 1st argument was copied.
 ******************************************************************************/
fsp_err_t R_USB_ClassTypeGet (usb_ctrl_t * const p_api_ctrl, usb_class_t * class_type)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *class_type = (usb_class_t) (p_ctrl->type | USB_VALUE_80H);

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the device address.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @note In Bare-Metal, In the Bare-Metal version, please specify the variable specified by the 1st argument of
 *       the R_USB_EventGet function to the 1st argument of this API.
 * @note In the FreeRTOS, please specify one of the following to the 1st argument of this API.
 * @note 1. The 1st argument of the callback function specified in Conguration.
 * @note 2. The start address of the area where the structure area of the 1st argument was copied.
 ******************************************************************************/
fsp_err_t R_USB_DeviceAddressGet (usb_ctrl_t * const p_api_ctrl, uint8_t * device_address)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *device_address = p_ctrl->device_address;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the pipe number.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @note In Bare-Metal, In the Bare-Metal version, please specify the variable specified by the 1st argument of
 *       the R_USB_EventGet function to the 1st argument of this API.
 * @note In the FreeRTOS, please specify one of the following to the 1st argument of this API.
 * @note 1. The 1st argument of the callback function specified in Conguration.
 * @note 2. The start address of the area where the structure area of the 1st argument was copied.
 ******************************************************************************/
fsp_err_t R_USB_PipeNumberGet (usb_ctrl_t * const p_api_ctrl, uint8_t * pipe_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *pipe_number = p_ctrl->pipe;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the state of the device.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @note In Bare-Metal, In the Bare-Metal version, please specify the variable specified by the 1st argument of
 *       the R_USB_EventGet function to the 1st argument of this API.
 * @note In the FreeRTOS, please specify one of the following to the 1st argument of this API.
 * @note 1. The 1st argument of the callback function specified in Conguration.
 * @note 2. The start address of the area where the structure area of the 1st argument was copied.
 ******************************************************************************/
fsp_err_t R_USB_DeviceStateGet (usb_ctrl_t * const p_api_ctrl, uint16_t * state)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        switch (g_usb_hstd_device_info[p_ctrl->module_number][p_ctrl->device_address][1])
        {
            case USB_POWERED:          /* Power state  */
            {
                *state = USB_STATUS_POWERED;
                break;
            }

            case USB_DEFAULT:          /* Default state  */
            {
                *state = USB_STATUS_DEFAULT;
                break;
            }

            case USB_ADDRESS:          /* Address state  */
            {
                *state = USB_STATUS_ADDRESS;
                break;
            }

            case USB_CONFIGURED:       /* Configured state  */
            {
                *state = USB_STATUS_CONFIGURED;
                break;
            }

            case USB_SUSPENDED:        /* Suspend state */
            {
                *state = USB_STATUS_SUSPEND;
                break;
            }

            case USB_DETACHED:         /* Disconnect(VBUSon) state */
            {
                *state = USB_STATUS_DETACH;
                break;
            }

            default:                   /* Error */
            {
                *state = USB_NULL;
                break;
            }
        }
#endif                                 /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        uint16_t status;

        status = hw_usb_read_intsts(p_ctrl->module_number);
        switch ((uint16_t) (status & USB_DVSQ))
        {
            case USB_DS_POWR:          /* Power state  */
            {
                *state = USB_STATUS_DETACH;
                break;
            }

            case USB_DS_DFLT:          /* Default state  */
            {
                *state = USB_STATUS_DEFAULT;
                break;
            }

            case USB_DS_ADDS:          /* Address state  */
            {
                *state = USB_STATUS_ADDRESS;
                break;
            }

            case USB_DS_CNFG:          /* Configured state  */
            {
                *state = USB_STATUS_CONFIGURED;
                break;
            }

            case USB_DS_SPD_POWR:      /* Power suspend state */
            case USB_DS_SPD_DFLT:      /* Default suspend state */
            case USB_DS_SPD_ADDR:      /* Address suspend state */
            case USB_DS_SPD_CNFG:      /* Configured Suspend state */
            {
                *state = USB_STATUS_SUSPEND;
                break;
            }

            default:                   /* Error */
                *state = USB_NULL;
        }
#endif /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
    }

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the read data size.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @note In Bare-Metal, In the Bare-Metal version, please specify the variable specified by the 1st argument of
 *       the R_USB_EventGet function to the 1st argument of this API.
 * @note In the FreeRTOS, please specify one of the following to the 1st argument of this API.
 * @note 1. The 1st argument of the callback function specified in Conguration.
 * @note 2. The start address of the area where the structure area of the 1st argument was copied.
 ******************************************************************************/
fsp_err_t R_USB_DataSizeGet (usb_ctrl_t * const p_api_ctrl, uint32_t * data_size)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *data_size = p_ctrl->data_size;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the setup information.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @note In Bare-Metal, In the Bare-Metal version, please specify the variable specified by the 1st argument of
 *       the R_USB_EventGet function to the 1st argument of this API.
 * @note In the FreeRTOS, please specify one of the following to the 1st argument of this API.
 * @note 1. The 1st argument of the callback function specified in Conguration.
 * @note 2. The start address of the area where the structure area of the 1st argument was copied.
 ******************************************************************************/
fsp_err_t R_USB_SetupGet (usb_ctrl_t * const p_api_ctrl, usb_setup_t * setup)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *setup = p_ctrl->setup;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief Set callback function to be called when the OTG role swap was completed on Azure RTOS
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 ******************************************************************************/
fsp_err_t R_USB_OtgCallbackSet (usb_ctrl_t * const p_api_ctrl, usb_otg_callback_t * p_callback)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    FSP_ASSERT(USB_NULL != p_api_ctrl);
    FSP_ASSERT(USB_NULL != p_callback);

#if (BSP_CFG_RTOS == 1)
 #if defined(USB_CFG_OTG_USE)
    g_p_otg_callback[p_ctrl->module_number] = p_callback;

    return FSP_SUCCESS;
 #else                                 /* defined(USB_CFG_OTG_USE) */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);

    return FSP_ERR_USB_FAILED;
 #endif                                /* defined(USB_CFG_OTG_USE) */
#else                                  /* (BSP_CFG_RTOS == 1) */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);

    return FSP_ERR_USB_FAILED;
#endif                                 /* (BSP_CFG_RTOS == 1) */
}

/**************************************************************************//**
 * @brief  Start the SRP processing for OTG on Azure RTOS
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter is NULL error.
 * @note Do not support the VBUS Pulsing since OTG 2.0 does not support the VBUS Pulsing..
 ******************************************************************************/
fsp_err_t R_USB_OtgSRP (usb_ctrl_t * const p_api_ctrl)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    FSP_ASSERT(USB_NULL != p_api_ctrl)

#if (BSP_CFG_RTOS == 1)
 #if defined(USB_CFG_OTG_USE)
    usb_utr_t utr;
    uint16_t syssts;
    uint16_t intsts;

    if ((USB_MODE_PERI != g_usb_usbmode[p_ctrl->module_number]) || (USB_YES == g_is_A_device[p_ctrl->module_number]))
    {
        return FSP_ERR_USB_FAILED;
    }
    else
    {
        utr.ip = p_ctrl->module_number;
        syssts = hw_usb_read_syssts(&utr);
        intsts = hw_usb_read_intsts(utr.ip);

        if ((USB_SE0 == (syssts & USB_LNST)) && (0 == (intsts & USB_VBSTS)))
        {
            /* Data Pulsing Processing */
            hw_usb_pset_dprpu(utr.ip);   // D+ PullUp ON

            usb_cpu_delay_xms((uint16_t) 5);

            hw_usb_pclear_dprpu(utr.ip); // D+ PullUp OFF
        }
        else
        {
            return FSP_ERR_USB_FAILED;
        }
    }

    return FSP_SUCCESS;
 #else                                 /* USB_CFG_OTG_USE */
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_USB_FAILED;
 #endif                                /* USB_CFG_OTG_USE */
#else                                  /* (BSP_CFG_RTOS == 1) */
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_USB_FAILED;
#endif  /* (BSP_CFG_RTOS == 1) */
}

/**************************************************************************//**
 * @brief USB Type-C connect Information get.
 *
 * @retval FSP_SUCCESS              Successful completion.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 ******************************************************************************/
fsp_err_t R_USB_TypeCInfoGet (usb_ctrl_t * const p_api_ctrl, usb_typec_info_t * p_info)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)

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
    if (USB_TYPEC_TCS_PLUG == (g_usb_typec_reg_tcs & USB_TYPEC_TCS_PLUG))
    {
        p_info->plug = USB_TYPEC_PLUG_CC2_CONNECTED; /* CC2 connected */
    }
    else
    {
        p_info->plug = USB_TYPEC_PLUG_CC1_CONNECTED; /* CC1 connected */
    }

    /* Set Status of VBUS */
    if (USB_TYPEC_TCS_VBUSS == (g_usb_typec_reg_tcs & USB_TYPEC_TCS_VBUSS))
    {
        p_info->vbus_status = USB_TYPEC_VBUS_STATUS_ON;  /* VBUS On State */
    }
    else
    {
        p_info->vbus_status = USB_TYPEC_VBUS_STATUS_OFF; /* VBUS Off State */
    }

    /* Set Status of Connection State Machine */
    p_info->connection_status = (g_usb_typec_reg_tcs & USB_TYPEC_TCS_CNS_MASK) >> 4;

    return FSP_SUCCESS;
#else                                  /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */
    FSP_PARAMETER_NOT_USED(p_info);

    return FSP_ERR_USB_FAILED;
#endif /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */
}

/*******************************************************************************************************************//**
 * @} (end addtogroup USB)
 **********************************************************************************************************************/
