/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_FREERTOS_PLUS_FAT_API_H
 #define RM_FREERTOS_PLUS_FAT_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_STORAGE_INTERFACES
 * @defgroup RM_FREERTOS_PLUS_FAT_API FreeRTOS+FAT Port Interface
 * @brief Interface for FreeRTOS+FAT port.
 *
 * @section RM_FREERTOS_PLUS_FAT_SUMMARY Summary
 * The FreeRTOS+FAT port provides notifications for insertion and removal of removable media and provides
 * initialization functions required by FreeRTOS+FAT.
 *
 *
 * @{
 **********************************************************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

 #include "bsp_api.h"
 #include "rm_block_media_api.h"
 #include "ff_headers.h"
 #include "ff_stdio.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_rm_freertos_plus_fat_event
{
    RM_FREERTOS_PLUS_FAT_EVENT_MEDIA_REMOVED  = RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED,  ///< Media removed event.
    RM_FREERTOS_PLUS_FAT_EVENT_MEDIA_INSERTED = RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED, ///< Media inserted event.
    RM_FREERTOS_PLUS_FAT_EVENT_MEDIA_SUSPEND  = RM_BLOCK_MEDIA_EVENT_MEDIA_SUSPEND,  ///< Media suspended event.
    RM_FREERTOS_PLUS_FAT_EVENT_MEDIA_RESUME   = RM_BLOCK_MEDIA_EVENT_MEDIA_RESUME,   ///< Media resumed event.
} rm_freertos_plus_fat_event_t;

typedef enum e_rm_freertos_plus_fat_type
{
    RM_FREERTOS_PLUS_FAT_TYPE_FAT32 = FF_T_FAT32, ///< FAT32 disk
    RM_FREERTOS_PLUS_FAT_TYPE_FAT16 = FF_T_FAT16, ///< FAT16 disk
    RM_FREERTOS_PLUS_FAT_TYPE_FAT12 = FF_T_FAT12, ///< FAT12 disk
} rm_freertos_plus_fat_type_t;

/** Callback function parameter data */
typedef struct st_rm_freertos_plus_fat_callback_args
{
    rm_freertos_plus_fat_event_t event;     ///< The event can be used to identify what caused the callback.
    void const                 * p_context; ///< Placeholder for user data.
} rm_freertos_plus_fat_callback_args_t;

/** Information obtained from the media device. */
typedef struct st_rm_freertos_plus_fat_device
{
    uint32_t sector_count;             ///< Sector count
    uint32_t sector_size_bytes;        ///< Sector size in bytes
} rm_freertos_plus_fat_device_t;

typedef struct st_rm_freertos_plus_fat_info
{
    uint32_t  sector_size;             ///< Sector size
    uint32_t  sectors_per_cluster;     ///< Sectors per cluster
    uint32_t  total_sectors;           ///< Total number of sectors
    uint32_t  free_sectors;            ///< Current free sectors
    uint8_t * p_volume_label;          ///< Volume label
    rm_freertos_plus_fat_type_t type;  ///< FAT type for this disk
    uint8_t partition_number;          ///< Partition number for this disk
} rm_freertos_plus_fat_info_t;

typedef struct st_rm_freertos_plus_fat_cfg
{
    rm_block_media_instance_t const * p_block_media;
    void (* p_callback)(rm_freertos_plus_fat_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                                             ///< User defined context passed into callback function

    /** The busy callback function is called when the device is busy with a write or erase operation.  It can be used
     * to pend the current thread while waiting for the operation to complete and to manage timeouts if required.
     * Set to NULL if pending the thread is not required and the thread will block waiting for the device busy status
     * to clear.  If this function returns an error (anything except FSP_SUCCESS), the upper layer function returns
     * FF_ERR_IOMAN_DRIVER_FATAL_ERROR. */
    fsp_err_t (* p_busy_callback)(void const * p_busy_context);
    void const * p_busy_context;                                        ///< User defined context passed into busy callback function
    void const * p_extend;                                              ///< Extension parameter for hardware specific settings.
} rm_freertos_plus_fat_cfg_t;

typedef struct st_rm_freertos_plus_fat_disk_cfg
{
    rm_freertos_plus_fat_device_t device; ///< Device sector data
    uint32_t  cache_size_bytes;           ///< Chache memory size
    uint8_t * p_cache;                    ///< Pointer to cache memory
    uint8_t   partition_number;           ///< Partition number for this disk
} rm_freertos_plus_fat_disk_cfg_t;

typedef void rm_freertos_plus_fat_ctrl_t;

/** FreeRTOS plus Fat functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_freertos_plus_fat_api
{
    /** Open media device.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_freertos_plus_fat_ctrl_t * const p_ctrl, rm_freertos_plus_fat_cfg_t const * const p_cfg);

    /** Initializes a media device.  If the device is removable, it must be plugged in prior to calling this API.
     * This function blocks until media initialization is complete.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_device     Pointer to store device information.
     */
    fsp_err_t (* mediaInit)(rm_freertos_plus_fat_ctrl_t * const p_ctrl, rm_freertos_plus_fat_device_t * const p_device);

    /** Initializes a FreeRTOS+FAT FF_Disk_t structure.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_disk_cfg   Pointer to disk configurations
     * @param[out] p_disk       Pointer to store FreeRTOS+FAT disk structure.
     */
    fsp_err_t (* diskInit)(rm_freertos_plus_fat_ctrl_t * const p_ctrl,
                           rm_freertos_plus_fat_disk_cfg_t const * const p_disk_cfg, FF_Disk_t * const p_disk);

    /** Deinitializes a FreeRTOS+FAT FF_Disk_t structure.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_disk_cfg   Pointer to disk configurations
     * @param[out] p_disk       Pointer to store FreeRTOS+FAT disk structure.
     */
    fsp_err_t (* diskDeinit)(rm_freertos_plus_fat_ctrl_t * const p_ctrl, FF_Disk_t * const p_disk);

    /** Returns information about the media device.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_info       Pointer to information structure. All elements of this structure will be set by the
     *                          function.
     */
    fsp_err_t (* infoGet)(rm_freertos_plus_fat_ctrl_t * const p_ctrl, FF_Disk_t * const p_disk,
                          rm_freertos_plus_fat_info_t * const p_info);

    /** Close media device.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_freertos_plus_fat_ctrl_t * const p_ctrl);
} rm_freertos_plus_fat_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_freertos_plus_fat_instance
{
    rm_freertos_plus_fat_ctrl_t            * p_ctrl; ///< Pointer to the control structure for this instance
    rm_freertos_plus_fat_cfg_t const * const p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_freertos_plus_fat_api_t const       * p_api;  ///< Pointer to the API structure for this instance
} rm_freertos_plus_fat_instance_t;

 #ifdef __cplusplus
} /* extern "C" */
 #endif

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_FREERTOS_PLUS_FAT_API_H */

/*******************************************************************************************************************//**
 * @} (end defgroup RM_FREERTOS_PLUS_FAT_API_TESTS)
 **********************************************************************************************************************/
