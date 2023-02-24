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

#ifndef RM_BLOCK_MEDIA_USB_H
#define RM_BLOCK_MEDIA_USB_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_block_media_api.h"
#include "r_usb_basic_api.h"
#include "r_usb_basic_cfg.h"
#include "r_usb_hmsc_api.h"
#if BSP_CFG_RTOS == 2
 #include "FreeRTOS.h"
 #include "semphr.h"
 #include "event_groups.h"
 #include "projdefs.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_BLOCK_MEDIA_USB
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Extended configuration structure. */
typedef struct st_rm_block_media_usb_extended_cfg
{
    usb_instance_t const * p_usb;
} rm_block_media_usb_extended_cfg_t;

/** Instance control block.  This is private to the FSP and should not be used or modified by the application. */
typedef struct st_rm_block_media_usb_instance_ctrl
{
    uint32_t open;
    rm_block_media_cfg_t const * p_cfg;
    uint32_t sector_count;
    uint32_t sector_size_bytes;
    uint8_t  device_address;
    bool     initialized;
    uint8_t  p_read_buffer[USB_HMSC_SECTOR_SIZE] __attribute__((__aligned__(4)));
#if 2 == BSP_CFG_RTOS
    EventGroupHandle_t event_group;
#endif
} rm_block_media_usb_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_block_media_api_t g_rm_block_media_on_usb;

/** @endcond */

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_Open(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_cfg_t const * const p_cfg);
fsp_err_t RM_BLOCK_MEDIA_USB_MediaInit(rm_block_media_ctrl_t * const p_ctrl);
fsp_err_t RM_BLOCK_MEDIA_USB_Read(rm_block_media_ctrl_t * const p_ctrl,
                                  uint8_t * const               p_dest_address,
                                  uint32_t const                block_address,
                                  uint32_t const                num_blocks);
fsp_err_t RM_BLOCK_MEDIA_USB_Write(rm_block_media_ctrl_t * const p_ctrl,
                                   uint8_t const * const         p_src_address,
                                   uint32_t const                block_address,
                                   uint32_t const                num_blocks);
fsp_err_t RM_BLOCK_MEDIA_USB_Flush(rm_block_media_ctrl_t * const p_ctrl);
fsp_err_t RM_BLOCK_MEDIA_USB_Erase(rm_block_media_ctrl_t * const p_ctrl,
                                   uint32_t const                block_address,
                                   uint32_t const                num_blocks);
fsp_err_t RM_BLOCK_MEDIA_USB_CallbackSet(rm_block_media_ctrl_t * const p_ctrl,
                                         void (                      * p_callback)(
                                             rm_block_media_callback_args_t *),
                                         void const * const                     p_context,
                                         rm_block_media_callback_args_t * const p_callback_memory);
fsp_err_t RM_BLOCK_MEDIA_USB_StatusGet(rm_block_media_ctrl_t * const   p_api_ctrl,
                                       rm_block_media_status_t * const p_status);
fsp_err_t RM_BLOCK_MEDIA_USB_InfoGet(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_info_t * const p_info);
fsp_err_t RM_BLOCK_MEDIA_USB_Close(rm_block_media_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_BLOCK_MEDIA_USB_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLOCK_MEDIA_USB)
 **********************************************************************************************************************/
