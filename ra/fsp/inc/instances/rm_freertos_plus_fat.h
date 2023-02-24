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
 * @addtogroup RM_FREERTOS_PLUS_FAT
 * @{
 **********************************************************************************************************************/

#ifndef RM_FREERTOS_PLUS_FAT_H
 #define RM_FREERTOS_PLUS_FAT_H

 #ifdef __cplusplus
extern "C" {
 #endif

/* FreeRTOS+FAT includes. */
 #include "ff_headers.h"
 #include "ff_sys.h"

/* FSP includes. */
 #include "rm_freertos_plus_fat_api.h"
 #include "rm_block_media_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** FreeRTOS plus FAT private control block. DO NOT MODIFY.  Initialization occurs when RM_FREERTOS_PLUS_FAT_Open is called. */
typedef struct
{
    uint32_t open;
    rm_freertos_plus_fat_cfg_t const * p_cfg;
    volatile rm_block_media_event_t    last_event;
    bool reentrant;
 #if 2 == BSP_CFG_RTOS
    volatile TaskHandle_t current_task;
    SemaphoreHandle_t     p_mutex;
 #else
    volatile bool event_ready;
 #endif
} rm_freertos_plus_fat_instance_ctrl_t;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

fsp_err_t RM_FREERTOS_PLUS_FAT_Open(rm_freertos_plus_fat_ctrl_t * const      p_ctrl,
                                    rm_freertos_plus_fat_cfg_t const * const p_cfg);
fsp_err_t RM_FREERTOS_PLUS_FAT_MediaInit(rm_freertos_plus_fat_ctrl_t * const   p_ctrl,
                                         rm_freertos_plus_fat_device_t * const p_device);
fsp_err_t RM_FREERTOS_PLUS_FAT_DiskInit(rm_freertos_plus_fat_ctrl_t * const           p_ctrl,
                                        rm_freertos_plus_fat_disk_cfg_t const * const p_disk_cfg,
                                        FF_Disk_t * const                             p_disk);
fsp_err_t RM_FREERTOS_PLUS_FAT_DiskDeinit(rm_freertos_plus_fat_ctrl_t * const p_ctrl, FF_Disk_t * const p_disk);
fsp_err_t RM_FREERTOS_PLUS_FAT_InfoGet(rm_freertos_plus_fat_ctrl_t * const p_ctrl,
                                       FF_Disk_t * const                   p_disk,
                                       rm_freertos_plus_fat_info_t * const p_info);
fsp_err_t RM_FREERTOS_PLUS_FAT_Close(rm_freertos_plus_fat_ctrl_t * const p_ctrl);

 #ifdef __cplusplus
}                                      /* extern "C" */
 #endif

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_freertos_plus_fat_api_t g_fat_on_freertos;

/** @endcond */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_FREERTOS_PLUS_FAT_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_FREERTOS_PLUS_FAT)
 **********************************************************************************************************************/
