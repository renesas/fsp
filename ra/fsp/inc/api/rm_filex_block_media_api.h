/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_FILEX_BLOCK_MEDIA_API_H
 #define RM_FILEX_BLOCK_MEDIA_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_STORAGE_INTERFACES
 * @defgroup RM_FILEX_BLOCK_MEDIA_API FileX Block Media Port Interface
 * @brief Interface for FileX Block Media port.
 *
 * @section RM_FILEX_BLOCK_MEDIA_SUMMARY Summary
 * The FileX block media port provides notifications for insertion and removal of removable media and provides
 * initialization functions required by FileX.
 *
 *
 * @{
 **********************************************************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

 #include "bsp_api.h"
 #include "rm_block_media_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Partitions that can be selected to use FileX with */
typedef enum e_rm_filex_block_media_partition
{
    RM_FILEX_BLOCK_MEDIA_PARTITION0 = 0, ///< Partition 0 (0x01BE) in Master Boot Record Partition Table
    RM_FILEX_BLOCK_MEDIA_PARTITION1 = 1, ///< Partition 1 (0x01CE) in Master Boot Record Partition Table
    RM_FILEX_BLOCK_MEDIA_PARTITION2 = 2, ///< Partition 2 (0x01DE) in Master Boot Record Partition Table
    RM_FILEX_BLOCK_MEDIA_PARTITION3 = 3, ///< Partition 3 (0x01EE) in Master Boot Record Partition Table
} rm_filex_block_media_partition_t;

/** Callback function parameter data */
typedef struct st_rm_filex_block_media_callback_args
{
    rm_block_media_event_t event;      ///< The event can be used to identify what caused the callback.
    void                 * p_context;  ///< Placeholder for user data.
} rm_filex_block_media_callback_args_t;

/** Block media configuration structure */
typedef struct st_rm_filex_block_media_cfg
{
    rm_block_media_instance_t      * p_lower_lvl_block_media;           ///< Lower level block media pointer
    rm_filex_block_media_partition_t partition;                         ///< Partition to use for partitioned media
    void (* p_callback)(rm_filex_block_media_callback_args_t * p_args); ///< Pointer to callback function
    void * p_extend;
} rm_filex_block_media_cfg_t;

/** Block media control structure */
typedef void rm_filex_block_media_ctrl_t;

/** FileX block media functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_filex_block_media_api
{
    /** Open media device.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_filex_block_media_ctrl_t * const p_ctrl, rm_filex_block_media_cfg_t const * const p_cfg);

    /** Close media device.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_filex_block_media_ctrl_t * const p_ctrl);
} rm_filex_block_media_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_filex_block_media_instance
{
    rm_filex_block_media_ctrl_t            * p_ctrl; ///< Pointer to the control structure for this instance
    rm_filex_block_media_cfg_t const * const p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_filex_block_media_api_t const       * p_api;  ///< Pointer to the API structure for this instance
} rm_filex_block_media_instance_t;

 #ifdef __cplusplus
} /* extern "C" */
 #endif

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_FILEX_BLOCK_MEDIA_API_H */

/*******************************************************************************************************************//**
 * @} (end defgroup RM_FILEX_BLOCK_MEDIA_API)
 **********************************************************************************************************************/
