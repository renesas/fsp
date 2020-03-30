/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup USB_PMSC_API USB PMSC Interface
 * @brief Interface for USB PMSC functions.
 *
 * @section USB_PMSC_API_Summary Summary
 * The USB PMSC interface provides USB PMSC functionality.
 *
 * The USB PMSC interface can be implemented by:
 * - @ref USB_PMSC
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

/* Used to get which MCU is currently being used. */
/* User specific options for Flash API */
#include "r_usb_basic_cfg.h"
#include "r_usb_pmsc_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/* MSC Class Request code define. */
#define USB_MASS_STORAGE_RESET    (0xFF00) /* Mass storage reset request */
#define USB_GET_MAX_LUN           (0xFE00) /* Get max logical unit number */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_PMSC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PMSC_API)
 **********************************************************************************************************************/
