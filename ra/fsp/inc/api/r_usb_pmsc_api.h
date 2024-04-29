/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_PMSC_API USB PMSC Interface
 * @brief Interface for USB PMSC functions.
 *
 * @section USB_PMSC_API_Summary Summary
 * The USB PMSC interface provides USB PMSC functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef USB_PMSC_API_H
#define USB_PMSC_API_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

/* User specific options for USB PMSC API */
#include "r_usb_basic_cfg.h"
#if defined(USB_CFG_OTG_USE)
 #include "r_usb_otg_msc_cfg.h"
#else                                  /* defined(USB_CFG_OTG_USE) */
 #include "r_usb_pmsc_cfg.h"
#endif  /* defined(USB_CFG_OTG_USE) */

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/* MSC Request codes */
#define USB_MASS_STORAGE_RESET    (0xFF00) ///< Mass storage reset request code
#define USB_GET_MAX_LUN           (0xFE00) ///< Get max logical unit number request code

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_PMSC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PMSC_API)
 **********************************************************************************************************************/
