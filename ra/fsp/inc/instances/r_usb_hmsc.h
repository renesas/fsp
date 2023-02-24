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
