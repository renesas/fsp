/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_usb_haud.h
 * Description  : USB HAUD public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HAUD
 * @{
 **********************************************************************************************************************/

#ifndef USB_HAUD_H
#define USB_HAUD_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_haud_cfg.h"
#include "r_usb_basic_api.h"
#include "r_usb_haud_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/
fsp_err_t R_USB_HAUD_DeviceInfoGet(usb_ctrl_t * const       p_api_ctrl,
                                   usb_haud_device_info_t * p_info,
                                   uint8_t                  device_address);
fsp_err_t R_USB_HAUD_ClockSourceGet(usb_ctrl_t * const    p_api_ctrl,
                                    usb_haud_sampling_t * p_info,
                                    uint8_t               direction,
                                    uint8_t               device_address);
fsp_err_t R_USB_HAUD_AlternateNumberGet(usb_ctrl_t * const    p_api_ctrl,
                                        usb_haud_sampling_t * p_info,
                                        uint8_t               direction,
                                        uint8_t               device_address);
fsp_err_t R_USB_HAUD_PipeSet(usb_ctrl_t * const p_api_ctrl,
                             uint32_t           interface_number,
                             uint32_t           alternate_number,
                             uint8_t            device_address);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_HAUD_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HAUD)
 **********************************************************************************************************************/
