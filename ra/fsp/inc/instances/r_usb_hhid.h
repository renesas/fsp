/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_usb_hhid.h
 * Description  : USB HHID public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HHID
 * @{
 **********************************************************************************************************************/

#ifndef USB_HHID_H
#define USB_HHID_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_hhid_cfg.h"
#include "r_usb_basic_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/
fsp_err_t R_USB_HHID_TypeGet(usb_ctrl_t * const p_api_ctrl, uint8_t * p_type, uint8_t device_address);
fsp_err_t R_USB_HHID_MaxPacketSizeGet(usb_ctrl_t * const p_api_ctrl,
                                      uint16_t         * p_size,
                                      uint8_t            direction,
                                      uint8_t            device_address);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_HHID_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HHID)
 **********************************************************************************************************************/
