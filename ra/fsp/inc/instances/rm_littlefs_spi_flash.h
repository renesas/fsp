/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_LITTLEFS_SPI_FLASH_H
#define RM_LITTLEFS_SPI_FLASH_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_littlefs_api.h"
#include "r_spi_flash_api.h"
#include "lfs.h"
#include "rm_littlefs_spi_flash_cfg.h"
#ifdef LFS_THREADSAFE
 #include "FreeRTOS.h"
 #include "semphr.h"

#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_LITTLEFS_SPI_FLASH
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Options for the callback events. */
typedef enum e_rm_littlefs_spi_flash_event
{
    RM_LITTLEFS_SPI_FLASH_EVENT_BUSY,  ///< Pending operation, user can define their own wait functionality.
} rm_littlefs_spi_flash_event_t;

/** RM_LITTLEFS callback arguments definitions  */
typedef struct st_rm_littlefs_spi_flash_callback_args
{
    rm_littlefs_spi_flash_event_t event; ///< LevelX NOR driver callback event
    void * p_context;                    ///< Placeholder for user data
} rm_littlefs_spi_flash_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_rm_littlefs_spi_flash_cfg
{
    spi_flash_instance_t const * p_lower_lvl;                            ///< Pointer to a spi flash instance
    uint32_t base_address;                                               ///< Base address of memory mapped region.
    uint32_t address_offset;                                             ///< Offset to use subset of available flash size if desired.
    uint32_t size;                                                       ///< Size of the partitioned region.
    uint32_t poll_status_count;                                          ///< Number of times to poll for operation complete status before returning an error.
    void   * p_context;                                                  ///< Placeholder for user data. Passed to the user callback.
    void (* p_callback)(rm_littlefs_spi_flash_callback_args_t * p_args); ///< Callback function
} rm_littlefs_spi_flash_cfg_t;

/** Instance control block.  This is private to the FSP and should not be used or modified by the application. */
typedef struct st_rm_littlefs_spi_flash_instance_ctrl
{
    uint32_t open;
    rm_littlefs_cfg_t const * p_cfg;
    uint32_t start_address;            ///< Start address of partition to use within memory mapped region.
    uint32_t size;                     ///< Size of partition to use within memory mapped region.
#ifdef LFS_THREADSAFE
    SemaphoreHandle_t xSemaphore;
    StaticSemaphore_t xMutexBuffer;
#endif
} rm_littlefs_spi_flash_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_littlefs_api_t g_rm_littlefs_on_flash;

/** @endcond */

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_LITTLEFS_SPI_FLASH_Open(rm_littlefs_ctrl_t * const p_ctrl, rm_littlefs_cfg_t const * const p_cfg);

fsp_err_t RM_LITTLEFS_SPI_FLASH_Close(rm_littlefs_ctrl_t * const p_ctrl);

int rm_littlefs_spi_flash_read(const struct lfs_config * c,
                               lfs_block_t               block,
                               lfs_off_t                 off,
                               void                    * buffer,
                               lfs_size_t                size);

int rm_littlefs_spi_flash_write(const struct lfs_config * c,
                                lfs_block_t               block,
                                lfs_off_t                 off,
                                const void              * buffer,
                                lfs_size_t                size);

int rm_littlefs_spi_flash_erase(const struct lfs_config * c, lfs_block_t block);

int rm_littlefs_spi_flash_lock(const struct lfs_config * c);

int rm_littlefs_spi_flash_unlock(const struct lfs_config * c);

int rm_littlefs_spi_flash_sync(const struct lfs_config * c);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_LITTLEFS_SPI_FLASH_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_LITTLEFS)
 **********************************************************************************************************************/
