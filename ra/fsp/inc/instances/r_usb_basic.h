/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup USB USB
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_H
#define R_USB_H

#include "bsp_api.h"
#include "r_usb_basic_cfg.h"
#include "r_usb_basic_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** USB private control block. DO NOT MODIFY.  Initialization occurs when R_USB_Open is called. */

typedef usb_event_info_t usb_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
extern const usb_api_t g_usb_on_usb;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_USB_Open(usb_ctrl_t * const p_api_ctrl, usb_cfg_t const * const cfg);

fsp_err_t R_USB_Close(usb_ctrl_t * const p_api_ctrl);

fsp_err_t R_USB_Read(usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size, uint8_t destination);

fsp_err_t R_USB_Write(usb_ctrl_t * const p_api_ctrl, uint8_t const * const p_buf, uint32_t size, uint8_t destination);

fsp_err_t R_USB_Stop(usb_ctrl_t * const p_api_ctrl, usb_transfer_t direction, uint8_t destination);

fsp_err_t R_USB_Suspend(usb_ctrl_t * const p_api_ctrl);

fsp_err_t R_USB_Resume(usb_ctrl_t * const p_api_ctrl);

fsp_err_t R_USB_VbusSet(usb_ctrl_t * const p_api_ctrl, uint16_t state);

fsp_err_t R_USB_InfoGet(usb_ctrl_t * const p_api_ctrl, usb_info_t * p_info, uint8_t destination);

fsp_err_t R_USB_PipeRead(usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size, uint8_t pipe_number);

fsp_err_t R_USB_PipeWrite(usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size, uint8_t pipe_number);

fsp_err_t R_USB_PipeStop(usb_ctrl_t * const p_api_ctrl, uint8_t pipe_number);

fsp_err_t R_USB_UsedPipesGet(usb_ctrl_t * const p_api_ctrl, uint16_t * p_pipe, uint8_t destination);

fsp_err_t R_USB_PipeInfoGet(usb_ctrl_t * const p_api_ctrl, usb_pipe_t * p_info, uint8_t pipe_number);

fsp_err_t R_USB_PullUp(usb_ctrl_t * const p_api_ctrl, uint8_t state);

fsp_err_t R_USB_EventGet(usb_ctrl_t * const p_api_ctrl, usb_status_t * event);

fsp_err_t R_USB_Callback(usb_callback_t * p_callback);

fsp_err_t R_USB_HostControlTransfer(usb_ctrl_t * const p_api_ctrl,
                                    usb_setup_t      * p_setup,
                                    uint8_t          * p_buf,
                                    uint8_t            device_address);

fsp_err_t R_USB_PeriControlDataGet(usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size);

fsp_err_t R_USB_PeriControlDataSet(usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint32_t size);

fsp_err_t R_USB_PeriControlStatusSet(usb_ctrl_t * const p_api_ctrl, usb_setup_status_t status);

fsp_err_t R_USB_RemoteWakeup(usb_ctrl_t * const p_api_ctrl);

fsp_err_t R_USB_ModuleNumberGet(usb_ctrl_t * const p_api_ctrl, uint8_t * module_number);

fsp_err_t R_USB_ClassTypeGet(usb_ctrl_t * const p_api_ctrl, usb_class_t * class_type);

fsp_err_t R_USB_DeviceAddressGet(usb_ctrl_t * const p_api_ctrl, uint8_t * device_address);

fsp_err_t R_USB_PipeNumberGet(usb_ctrl_t * const p_api_ctrl, uint8_t * pipe_number);

fsp_err_t R_USB_DeviceStateGet(usb_ctrl_t * const p_api_ctrl, uint16_t * state);

fsp_err_t R_USB_DataSizeGet(usb_ctrl_t * const p_api_ctrl, uint32_t * data_size);

fsp_err_t R_USB_SetupGet(usb_ctrl_t * const p_api_ctrl, usb_setup_t * setup);

fsp_err_t R_USB_OtgCallbackSet(usb_ctrl_t * const p_api_ctrl, usb_otg_callback_t * p_callback);

fsp_err_t R_USB_OtgSRP(usb_ctrl_t * const p_api_ctrl);

fsp_err_t R_USB_DriverActivate(usb_ctrl_t * const p_api_ctrl);

fsp_err_t R_USB_CallbackMemorySet(usb_ctrl_t * const p_api_ctrl, usb_callback_args_t * p_callback_memory);

fsp_err_t R_USB_TypeCInfoGet(usb_ctrl_t * const p_api_ctrl, usb_typec_info_t * p_info);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_USB_H

/*******************************************************************************************************************//**
 * @} (end addtogroup USB)
 **********************************************************************************************************************/
