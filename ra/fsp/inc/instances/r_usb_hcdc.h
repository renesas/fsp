/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_usb_hcdc.h
 * Description  : USB HCDC public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HCDC
 * @{
 **********************************************************************************************************************/

#ifndef USB_HCDC_H
#define USB_HCDC_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_hcdc_cfg.h"
#include "r_usb_basic_api.h"
#include "r_usb_hcdc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/
fsp_err_t R_USB_HCDC_ControlDataRead(usb_ctrl_t * const p_api_ctrl,
                                     uint8_t          * p_buf,
                                     uint32_t           size,
                                     uint8_t            device_address);
fsp_err_t R_USB_HCDC_SpecificDeviceRegister(usb_ctrl_t * const p_api_ctrl, uint16_t vendor_id, uint16_t product_id);
fsp_err_t R_USB_HCDC_DeviceInfoGet(usb_ctrl_t * const       p_api_ctrl,
                                   usb_hcdc_device_info_t * p_info,
                                   uint8_t                  device_address);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_HCDC_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HCDC)
 **********************************************************************************************************************/
