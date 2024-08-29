/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_usb_hmsc.h
 * Description  : USB HMSC public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HMSC
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_HMSC_H
#define R_USB_HMSC_H

#include "r_usb_hmsc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/
fsp_err_t R_USB_HMSC_StorageCommand(usb_ctrl_t * const p_api_ctrl, uint8_t * p_buf, uint8_t command,
                                    uint8_t destination);

fsp_err_t R_USB_HMSC_DriveNumberGet(usb_ctrl_t * const p_api_ctrl, uint8_t * p_drive, uint8_t destination);

fsp_err_t R_USB_HMSC_SemaphoreGet(void);

fsp_err_t R_USB_HMSC_SemaphoreRelease(void);

fsp_err_t R_USB_HMSC_StorageReadSector(uint16_t        drive_number,
                                       uint8_t * const buff,
                                       uint32_t        sector_number,
                                       uint16_t        sector_count);

fsp_err_t R_USB_HMSC_StorageWriteSector(uint16_t              drive_number,
                                        uint8_t const * const buff,
                                        uint32_t              sector_number,
                                        uint16_t              sector_count);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_HMSC_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HMSC)
 **********************************************************************************************************************/
