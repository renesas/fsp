/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_HHID_API USB HHID Interface
 * @brief Interface for USB HHID functions.
 *
 * @section USB_HHID_API_Summary Summary
 * The USB HHID interface provides USB HHID functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef USB_HHID_API_H
#define USB_HHID_API_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_hhid_cfg.h"
#include "r_usb_basic_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define USB_HHID_ECHO_MODE                 (0) /* Host HID Application echo mode */
#define USB_HHID_MOUSE_KEYBOARD_MODE       (1) /* Host HID Application mouse keyboard mode */

/* ----- HID Mouse Class Request Defines -------- */
/* HID Class Request IDs */
/* It is used by the classification judging of a class request. */
#define USB_HID_GET_REPORT                 (0x0100U)
#define USB_HID_GET_IDLE                   (0x0200U)
#define USB_HID_GET_PROTOCOL               (0x0300U)
#define USB_HID_SET_IDLE                   (0x0A00U)
#define USB_HID_SET_REPORT                 (0x0900U)
#define USB_HID_SET_PROTOCOL               (0x0B00U)
#define USB_HID_GET_HID_DESCRIPTOR         (0x2100U)
#define USB_HID_GET_REPORT_DESCRIPTOR      (0x2200U)
#define USB_HID_GET_PHYSICAL_DESCRIPTOR    (0x2300U)

/* ----- Protocol Codes ----- */
#define USB_HID_OTHER                      ((uint8_t) 0x00) ///< Other
#define USB_HID_KEYBOARD                   ((uint8_t) 0x01) ///< Keyboard
#define USB_HID_MOUSE                      ((uint8_t) 0x02) ///< Mouse

#define USB_HID_IN                         (0U)             ///< In Transfer
#define USB_HID_OUT                        (1U)             ///< Out Transfer

/*****************************************************************************
 * Typedef definitions
 ******************************************************************************/

/** USB HHID functions implemented at the HAL layer will follow this API. */
typedef struct st_usb_hhid_api
{
    /** Get HID protocol.(USB Mouse/USB Keyboard/Other Type.)
     *
     * @param[in]  p_ctrl      Pointer to control structure.
     * @param[in]  p_type          Pointer to store HID protocol value.
     * @param[in]  device_address  Device Address.
     */
    fsp_err_t (* typeGet)(usb_ctrl_t * const p_ctrl, uint8_t * p_type, uint8_t device_address);

    /** Obtains max packet size for the connected HID device.
     *  The max packet size is set to the area.
     *  Set the direction (USB_HID_IN/USB_HID_OUT).
     *
     * @param[in]  p_ctrl      Pointer to control structure.
     * @param[in]  p_size          Pointer to the area to store the max package size.
     * @param[in]  direction       Transfer direction.
     * @param[in]  device_address  Device Address.
     */
    fsp_err_t (* maxPacketSizeGet)(usb_ctrl_t * const p_ctrl, uint16_t * p_size, uint8_t direction,
                                   uint8_t device_address);
} usb_hhid_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_usb_hhid_instance
{
    usb_ctrl_t           * p_ctrl;     ///< Pointer to the control structure for this instance
    usb_cfg_t const      * p_cfg;      ///< Pointer to the configuration structure for this instance
    usb_hhid_api_t const * p_api;      ///< Pointer to the API structure for this instance
} usb_hhid_instance_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_HHID_API_H */

/*******************************************************************************************************************//**
 * @} (end defgroup USB_HHID_API)
 **********************************************************************************************************************/
