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
 * @defgroup USB_PPRN_API USB PPRN Interface
 * @brief Interface for USB PPRN functions.
 *
 * @section USB_PPRN_API_Summary Summary
 * The USB PPRN interface provides USB PPRN functionality.
 *
 * The USB PPRN interface can be implemented by:
 * - @ref USBX
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_PPRN_API_H
#define R_USB_PPRN_API_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_pprn_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define USB_PPRN_GET_DEVICE_ID              (0x0000U) ///< Get Device ID
#define USB_PRPN_GET_PORT_STATUS            (0x0100U) ///< Get Port Status
#define USB_PPRN_SOFT_RESET                 (0x0200U) ///< Soft Reset

#define USB_PPRN_PORT_STATUS_PAPER_EMPTY    (1U << 5) ///< 1: Paper Empty, 0: Paper Not Empty
#define USB_PPRN_PORT STATUS_SELECT         (1U << 4) ///< 1: Selected, 0: Not Selected
#define USB_PPRN_PORT_STATUS_NOT_ERROR      (1U << 3) ///< 1: No Error, 0; Error

/*******************************************************************************
 * Typedef definitions
 *******************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_PPRN_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PPRN_API)
 **********************************************************************************************************************/
