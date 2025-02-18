/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_PPRN_API USB PPRN Interface
 * @brief Interface for USB PPRN functions.
 *
 * @section USB_PPRN_API_Summary Summary
 * The USB PPRN interface provides USB PPRN functionality.
 *
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
#define USB_PPRN_PORT_STATUS_SELECT         (1U << 4) ///< 1: Selected, 0: Not Selected
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
