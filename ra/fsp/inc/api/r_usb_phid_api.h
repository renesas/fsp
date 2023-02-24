/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup USB_PHID_API USB PHID Interface
 * @brief Interface for USB PHID functions.
 *
 * @section USB_PHID_API_Summary Summary
 * The USB interface provides USB functionality.
 *
 * The USB PHID interface can be implemented by:
 * - @ref USB_PHID
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_PHID_API_H
#define R_USB_PHID_API_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

/* User specific options for Flash API */
#include "r_usb_phid_cfg.h"

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define USB_PHID_ECHO_MODE           (0) /*  Peripheral HID Application echo mode */
#define USB_PHID_KEYBOARD_MODE       (1) /* Peripheral HID Application keyboard mode */
#define USB_PHID_MOUSE_MODE          (2) /* Peripheral HID Application mouse mode */

/*----- HID Mouse Class Request Defines --------*/
/* HID Class Request codes */
#define USB_GET_REPORT               (0x0100U)
#define USB_GET_IDLE                 (0x0200U)
#define USB_GET_PROTOCOL             (0x0300U)
#define USB_SET_IDLE                 (0x0A00U)
#define USB_SET_REPORT               (0x0900U)
#define USB_SET_PROTOCOL             (0x0B00U)

/* PHID reception message type definition */
#define USB_GET_REPORT_DESCRIPTOR    (0x2200U)
#define USB_GET_HID_DESCRIPTOR       (0x2100U)

/* ----- DESCRIPTOR Types ----- */
#define USB_DT_TYPE_GETREPORT        ((uint8_t) 0x01) /* Report Type Input */
#define USB_DT_TYPE_SETREPORT        ((uint8_t) 0x02) /* Report Type Output */
#define USB_DT_TYPE_HIDDESCRIPTOR    ((uint8_t) 0x21) /* HID descriptor type */
#define USB_DT_TYPE_RPTDESCRIPTOR    ((uint8_t) 0x22) /* Report descriptor type */

/* ----- Subclass Codes ----- */
#define USB_IFSUB_NOBOOT             ((uint8_t) 0x00) /* No Subclass */
#define USB_IFSUB_BOOT               ((uint8_t) 0x01) /* Boot Interface Subclass */

/* ----- Protocol Codes ----- */
#define USB_IFPRO_NONE               ((uint8_t) 0x00) /* Demonstration */
#define USB_IFPRO_KBD                ((uint8_t) 0x01) /* Keyboard */
#define USB_IFPRO_MSE                ((uint8_t) 0x02) /* Mouse */

/* Peripheral HID Max Packet Size */
#define USB_PHID_MXPS_KBD            (8U)
#define USB_PHID_MXPS_MSE            (3U)
#define USB_PHID_MXPS_ECHO           (64U)

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_PHID_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PHID_API)
 **********************************************************************************************************************/
