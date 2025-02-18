/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/* FSP includes. */
#include "rm_littlefs_spi_flash.h"
#include "rm_littlefs_spi_flash_cfg.h"

#define RM_LITTLEFS_SPI_FLASH_MINIMUM_BLOCK_SIZE    (104)

#ifndef RM_LITTLEFS_SPI_FLASH_SEMAPHORE_TIMEOUT
 #define RM_LITTLEFS_SPI_FLASH_SEMAPHORE_TIMEOUT    UINT32_MAX
#endif

/** "RLFS" in ASCII, used to determine if channel is open. */
#define RM_LITTLEFS_SPI_FLASH_OPEN                  (0x524C4653ULL)

#define RM_LITTLEFS_SPI_BYTES_PER_WORD              (4U)
#define RM_LITTLEFS_SPI_FLASH_CLEARED               (0xFF)

/** LittleFS API mapping for LittleFS Port interface */
const rm_littlefs_api_t g_rm_littlefs_on_flash =
{
    .open  = RM_LITTLEFS_SPI_FLASH_Open,
    .close = RM_LITTLEFS_SPI_FLASH_Close,
};

static fsp_err_t rm_littlefs_spi_flash_wait_write_erase_complete(rm_littlefs_spi_flash_instance_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @addtogroup RM_LITTLEFS_SPI_FLASH
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the driver and initializes lower layer driver.
 *
 * Implements @ref rm_littlefs_api_t::open().
 *
 * @retval     FSP_SUCCESS                Success.
 * @retval     FSP_ERR_ASSERTION          An input parameter was invalid.
 * @retval     FSP_ERR_ALREADY_OPEN       Module is already open.
 * @retval     FSP_ERR_INVALID_SIZE       The provided block size is invalid.
 * @retval     FSP_ERR_INVALID_ARGUMENT   Flash BGO mode must be disabled.
 * @retval     FSP_ERR_INTERNAL           Failed to create the semaphore.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *             * @ref spi_flash_api_t::open
 **********************************************************************************************************************/
fsp_err_t RM_LITTLEFS_SPI_FLASH_Open (rm_littlefs_ctrl_t * const p_ctrl, rm_littlefs_cfg_t const * const p_cfg)
{
    rm_littlefs_spi_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_spi_flash_instance_ctrl_t *) p_ctrl;

#if RM_LITTLEFS_SPI_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_lfs_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    rm_littlefs_spi_flash_cfg_t const * p_extend = (rm_littlefs_spi_flash_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(NULL != p_extend->p_lower_lvl);

    FSP_ERROR_RETURN(RM_LITTLEFS_SPI_FLASH_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(p_cfg->p_lfs_cfg->block_size >= RM_LITTLEFS_SPI_FLASH_MINIMUM_BLOCK_SIZE, FSP_ERR_INVALID_SIZE);

    spi_flash_instance_t const * p_lower_lvl = p_extend->p_lower_lvl;
    FSP_ERROR_RETURN((p_cfg->p_lfs_cfg->block_size % p_lower_lvl->p_cfg->p_erase_command_list[0].size) == 0,
                     FSP_ERR_INVALID_SIZE);
#else
    rm_littlefs_spi_flash_cfg_t const * p_extend    = (rm_littlefs_spi_flash_cfg_t *) p_cfg->p_extend;
    spi_flash_instance_t const        * p_lower_lvl = p_extend->p_lower_lvl;
#endif

    p_instance_ctrl->p_cfg         = p_cfg;
    p_instance_ctrl->start_address = p_extend->base_address + p_extend->address_offset;
    p_instance_ctrl->size          = p_cfg->p_lfs_cfg->block_count * p_cfg->p_lfs_cfg->block_size;

    /* Open the underlying driver. */
    fsp_err_t err = p_lower_lvl->p_api->open(p_lower_lvl->p_ctrl, p_lower_lvl->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#ifdef LFS_THREADSAFE
    p_instance_ctrl->xSemaphore = xSemaphoreCreateMutexStatic(&p_instance_ctrl->xMutexBuffer);

    if (NULL == p_instance_ctrl->xSemaphore)
    {
        p_lower_lvl->p_api->close(p_lower_lvl->p_ctrl);

        return FSP_ERR_INTERNAL;
    }
#endif

    /* This module is now open. */
    p_instance_ctrl->open = RM_LITTLEFS_SPI_FLASH_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the lower level driver.
 *
 * Implements @ref rm_littlefs_api_t::close().
 *
 * @retval FSP_SUCCESS           Media device closed.
 * @retval FSP_ERR_ASSERTION     An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN      Module not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref spi_flash_api_t::close
 **********************************************************************************************************************/
fsp_err_t RM_LITTLEFS_SPI_FLASH_Close (rm_littlefs_ctrl_t * const p_ctrl)
{
    rm_littlefs_spi_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_spi_flash_instance_ctrl_t *) p_ctrl;
#if RM_LITTLEFS_SPI_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_LITTLEFS_SPI_FLASH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->open = 0;

    rm_littlefs_spi_flash_cfg_t const * p_extend    = (rm_littlefs_spi_flash_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    spi_flash_instance_t const        * p_lower_lvl = p_extend->p_lower_lvl;

    p_lower_lvl->p_api->close(p_extend->p_lower_lvl->p_ctrl);

#ifdef LFS_THREADSAFE
    vSemaphoreDelete(p_instance_ctrl->xSemaphore);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_LITTLEFS_SPI_FLASH)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Read from the flash driver. Negative error codes are propogated to the user.
 *
 * @param[in]  c           Pointer to the LittleFS config block.
 * @param[in]  block       The block number
 * @param[in]  off         Offset in bytes
 * @param[out] buffer      The buffer to copy data into
 * @param[in]  size        The size in bytes
 *
 * @retval     LFS_ERR_OK  Read is complete.
 * @retval     LFS_ERR_IO  Lower level driver is not open.
 **********************************************************************************************************************/
int rm_littlefs_spi_flash_read (const struct lfs_config * c,
                                lfs_block_t               block,
                                lfs_off_t                 off,
                                void                    * buffer,
                                lfs_size_t                size)
{
    rm_littlefs_spi_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_spi_flash_instance_ctrl_t *) c->context;
#if RM_LITTLEFS_SPI_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RM_LITTLEFS_SPI_FLASH_OPEN == p_instance_ctrl->open, LFS_ERR_IO);
#endif

    /* Read directly from the flash. */
    memcpy(buffer,
           (uint8_t *) (p_instance_ctrl->start_address + (p_instance_ctrl->p_cfg->p_lfs_cfg->block_size * block) + off),
           size);

    return LFS_ERR_OK;
}

/*******************************************************************************************************************//**
 * Writes requested bytes to flash.
 *
 * @param[in]  c           Pointer to the LittleFS config block.
 * @param[in]  block       The block number
 * @param[in]  off         Offset in bytes
 * @param[in]  buffer      The buffer containing data to be written.
 * @param[in]  size        The size in bytes
 *
 * @retval     LFS_ERR_OK  Success.
 * @retval     LFS_ERR_IO  Lower layer is not open or failed to write the flash.
 **********************************************************************************************************************/
int rm_littlefs_spi_flash_write (const struct lfs_config * c,
                                 lfs_block_t               block,
                                 lfs_off_t                 off,
                                 const void              * buffer,
                                 lfs_size_t                size)
{
    rm_littlefs_spi_flash_instance_ctrl_t * p_ctrl = (rm_littlefs_spi_flash_instance_ctrl_t *) c->context;
    uint32_t  current_write_size = 0;
    uint8_t * p_local_src_address;
    fsp_err_t err   = FSP_SUCCESS;
    uint8_t * p_src = (uint8_t *) buffer;

#if RM_LITTLEFS_SPI_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RM_LITTLEFS_SPI_FLASH_OPEN == p_ctrl->open, LFS_ERR_IO);
#endif

    rm_littlefs_spi_flash_cfg_t * p_extend             = (rm_littlefs_spi_flash_cfg_t *) p_ctrl->p_cfg->p_extend;
    spi_flash_instance_t        * p_spi_flash_instance = (spi_flash_instance_t *) p_extend->p_lower_lvl;
    uint32_t page_size = p_spi_flash_instance->p_cfg->page_size_bytes;

    uint32_t byte_count   = size;
    uint32_t p_flash_addr = p_ctrl->start_address + (block * p_ctrl->p_cfg->p_lfs_cfg->block_size) + off;

    for (uint32_t offset = 0U; offset < byte_count; offset += current_write_size)
    {
        /* Calculate current write size */
        current_write_size = page_size - ((p_flash_addr + offset) % page_size);

        if (current_write_size > (byte_count - offset))
        {
            current_write_size = byte_count - offset;
        }

        p_local_src_address = (uint8_t *) ((uint32_t) p_src + offset);

        /* Program using underlying SPI memory driver */
        err = p_spi_flash_instance->p_api->write(p_spi_flash_instance->p_ctrl,
                                                 p_local_src_address,
                                                 (uint8_t *) p_flash_addr + offset,
                                                 current_write_size);

        /* Write failed. Return IO error. Negative error codes are propogated to the user. */
        FSP_ERROR_RETURN(FSP_SUCCESS == err, LFS_ERR_IO);

        err = rm_littlefs_spi_flash_wait_write_erase_complete(p_ctrl);

        /* Write failed. Return IO error. Negative error codes are propogated to the user. */
        FSP_ERROR_RETURN(FSP_SUCCESS == err, LFS_ERR_IO);
    }

    return LFS_ERR_OK;
}

/*******************************************************************************************************************//**
 * Erase the logical block. The location and number of blocks to be erased will depend on block size.
 *
 * @param[in]  c           Pointer to the LittleFS config block.
 * @param[in]  block       The logical block number
 *
 * @retval     LFS_ERR_OK  Success.
 * @retval     LFS_ERR_IO  Lower layer is not open or failed to erase the flash.
 **********************************************************************************************************************/
int rm_littlefs_spi_flash_erase (const struct lfs_config * c, lfs_block_t block)
{
    rm_littlefs_spi_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_spi_flash_instance_ctrl_t *) c->context;
#if RM_LITTLEFS_SPI_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RM_LITTLEFS_SPI_FLASH_OPEN == p_instance_ctrl->open, LFS_ERR_IO);
#endif
    rm_littlefs_spi_flash_cfg_t const * p_extend    = (rm_littlefs_spi_flash_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    spi_flash_instance_t const        * p_lower_lvl = p_extend->p_lower_lvl;

    /* Call the underlying driver. */
    fsp_err_t err =
        p_lower_lvl->p_api->erase(p_lower_lvl->p_ctrl,
                                  (uint8_t *) (p_instance_ctrl->start_address +
                                               (p_instance_ctrl->p_cfg->p_lfs_cfg->block_size * block)),
                                  p_instance_ctrl->p_cfg->p_lfs_cfg->block_size);

    /* Erase failed. Return IO error. Negative error codes are propogated to the user. */
    FSP_ERROR_RETURN(FSP_SUCCESS == err, LFS_ERR_IO);

    err = rm_littlefs_spi_flash_wait_write_erase_complete(p_instance_ctrl);

    /* Write failed. Return IO error. Negative error codes are propogated to the user. */
    FSP_ERROR_RETURN(FSP_SUCCESS == err, LFS_ERR_IO);

    return LFS_ERR_OK;
}

/*******************************************************************************************************************//**
 * Returns the version of this module.
 *
 * @retval     LFS_ERR_OK  Success.
 * @retval     LFS_ERR_IO  Lower layer is not open or failed to lock the flash.
 **********************************************************************************************************************/
int rm_littlefs_spi_flash_lock (const struct lfs_config * c)
{
#ifdef LFS_THREADSAFE
    rm_littlefs_spi_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_spi_flash_instance_ctrl_t *) c->context;
 #if RM_LITTLEFS_SPI_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_LITTLEFS_SPI_FLASH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif
    BaseType_t err = xSemaphoreTake(p_instance_ctrl->xSemaphore, RM_LITTLEFS_SPI_FLASH_SEMAPHORE_TIMEOUT);

    FSP_ERROR_RETURN(true == err, LFS_ERR_IO);

    return LFS_ERR_OK;
#else
    FSP_PARAMETER_NOT_USED(c);

    return LFS_ERR_IO;
#endif
}

/*******************************************************************************************************************//**
 * Returns the version of this module.
 *
 * @retval     LFS_ERR_OK  Success.
 * @retval     LFS_ERR_IO  Lower layer is not open or failed to unlock the flash.
 **********************************************************************************************************************/
int rm_littlefs_spi_flash_unlock (const struct lfs_config * c)
{
#ifdef LFS_THREADSAFE
    rm_littlefs_spi_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_spi_flash_instance_ctrl_t *) c->context;
 #if RM_LITTLEFS_SPI_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_LITTLEFS_SPI_FLASH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif
    BaseType_t err = xSemaphoreGive(p_instance_ctrl->xSemaphore);

    FSP_ERROR_RETURN(true == err, LFS_ERR_IO);

    return LFS_ERR_OK;
#else
    FSP_PARAMETER_NOT_USED(c);

    return LFS_ERR_IO;
#endif
}

/*******************************************************************************************************************//**
 * Stub function required by LittleFS. All calls immedialy write/erase the lower layer.
 * @param[in]  c           Pointer to the LittleFS config block.
 * @retval     LFS_ERR_OK  Success.
 **********************************************************************************************************************/
int rm_littlefs_spi_flash_sync (const struct lfs_config * c)
{
    FSP_PARAMETER_NOT_USED(c);

    return LFS_ERR_OK;
}

/*******************************************************************************************************************//**
 * @brief      Wait until the current program or erase operation completes.
 * @param      p_ctrl                   The instance control block
 * @retval     FSP_SUCCESS              Successfully waited.
 * @retval     FSP_ERR_TIMEOUT          Wait timed out.
 * @return                              See @ref Common_Error_Codes or HAL driver for other possible return codes or
 *                                      causes.
 *                                      This function calls
 *                                          * spi_flash_api_t::statusGet
 **********************************************************************************************************************/
static fsp_err_t rm_littlefs_spi_flash_wait_write_erase_complete (rm_littlefs_spi_flash_instance_ctrl_t * const p_ctrl)
{
    spi_flash_status_t            status;
    fsp_err_t                     err;
    rm_littlefs_spi_flash_cfg_t * p_extend             = (rm_littlefs_spi_flash_cfg_t *) p_ctrl->p_cfg->p_extend;
    const spi_flash_instance_t  * p_spi_flash_instance = p_extend->p_lower_lvl;
    uint32_t status_polls_remaining = p_extend->poll_status_count;
    rm_littlefs_spi_flash_callback_args_t args;

    status.write_in_progress = true;

    /* While the SPI driver is busy call the delay callback if defined. If timeout return error. */
    do
    {
        err = p_spi_flash_instance->p_api->statusGet(p_spi_flash_instance->p_ctrl, &status);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* If write in progress call the user defined callback function. */
        if (status.write_in_progress)
        {
            if (NULL != p_extend->p_callback)
            {
                args.event     = RM_LITTLEFS_SPI_FLASH_EVENT_BUSY;
                args.p_context = p_extend->p_context;
                p_extend->p_callback(&args);
            }

            status_polls_remaining--;
        }
    } while (status.write_in_progress && (status_polls_remaining > 0U));

    /* Check whether write completed */
    FSP_ERROR_RETURN(!status.write_in_progress, FSP_ERR_TIMEOUT);

    return FSP_SUCCESS;
}
