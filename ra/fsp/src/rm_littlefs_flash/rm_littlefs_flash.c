/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/* FSP includes. */
#include "rm_littlefs_flash.h"
#include "rm_littlefs_flash_cfg.h"

/* Get the data flash block size defined in bsp_feature.h for this MCU. */
#if BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE != 0
 #define RM_LITTLEFS_FLASH_DATA_BLOCK_SIZE      BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE
#elif BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE != 0
 #define RM_LITTLEFS_FLASH_DATA_BLOCK_SIZE      BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE
#else
 #error "Missing data flash block size as defined in bsp_feature.h"
#endif

#define RM_LITTLEFS_FLASH_MINIMUM_BLOCK_SIZE    (104)

#ifndef RM_LITTLEFS_FLASH_SEMAPHORE_TIMEOUT
 #define RM_LITTLEFS_FLASH_SEMAPHORE_TIMEOUT    UINT32_MAX
#endif

#ifdef RM_LITTLEFS_FLASH_DATA_START
static const uint32_t rm_littlefs_flash_data_start = RM_LITTLEFS_FLASH_DATA_START;
#else
 #define rm_littlefs_flash_data_start    BSP_FEATURE_FLASH_DATA_FLASH_START
#endif

/** "RLFS" in ASCII, used to determine if channel is open. */
#define RM_LITTLEFS_FLASH_OPEN           (0x524C4653ULL)

/** LittleFS API mapping for LittleFS Port interface */
const rm_littlefs_api_t g_rm_littlefs_on_flash =
{
    .open  = RM_LITTLEFS_FLASH_Open,
    .close = RM_LITTLEFS_FLASH_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_LITTLEFS_FLASH
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
 *             * @ref flash_api_t::open
 **********************************************************************************************************************/
fsp_err_t RM_LITTLEFS_FLASH_Open (rm_littlefs_ctrl_t * const p_ctrl, rm_littlefs_cfg_t const * const p_cfg)
{
    rm_littlefs_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_flash_instance_ctrl_t *) p_ctrl;

#if RM_LITTLEFS_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_lfs_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    rm_littlefs_flash_cfg_t const * p_extend = (rm_littlefs_flash_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(NULL != p_extend->p_flash);

    FSP_ERROR_RETURN(false == ((flash_instance_t *) p_extend->p_flash)->p_cfg->data_flash_bgo,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(RM_LITTLEFS_FLASH_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(p_cfg->p_lfs_cfg->block_size >= RM_LITTLEFS_FLASH_MINIMUM_BLOCK_SIZE, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN((p_cfg->p_lfs_cfg->block_size % RM_LITTLEFS_FLASH_DATA_BLOCK_SIZE) == 0, FSP_ERR_INVALID_SIZE);

    FSP_ERROR_RETURN((p_cfg->p_lfs_cfg->block_size * p_cfg->p_lfs_cfg->block_count) <= BSP_DATA_FLASH_SIZE_BYTES,
                     FSP_ERR_INVALID_SIZE);
#else
    rm_littlefs_flash_cfg_t const * p_extend = (rm_littlefs_flash_cfg_t *) p_cfg->p_extend;
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    /* Open the underlying driver. */
    flash_instance_t const * p_flash = p_extend->p_flash;
    fsp_err_t                err     = p_flash->p_api->open(p_flash->p_ctrl, p_flash->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if LFS_THREAD_SAFE
    p_instance_ctrl->xSemaphore = xSemaphoreCreateMutexStatic(&p_instance_ctrl->xMutexBuffer);

    if (NULL == p_instance_ctrl->xSemaphore)
    {
        p_flash->p_api->close(p_flash->p_ctrl);

        return FSP_ERR_INTERNAL;
    }
#endif

    /* This module is now open. */
    p_instance_ctrl->open = RM_LITTLEFS_FLASH_OPEN;

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
 *             * @ref flash_api_t::close
 **********************************************************************************************************************/
fsp_err_t RM_LITTLEFS_FLASH_Close (rm_littlefs_ctrl_t * const p_ctrl)
{
    rm_littlefs_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_flash_instance_ctrl_t *) p_ctrl;
#if RM_LITTLEFS_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_LITTLEFS_FLASH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->open = 0;

    rm_littlefs_flash_cfg_t const * p_extend = (rm_littlefs_flash_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    flash_instance_t const        * p_flash  = p_extend->p_flash;

    p_flash->p_api->close(p_extend->p_flash->p_ctrl);

#if LFS_THREAD_SAFE
    vSemaphoreDelete(p_instance_ctrl->xSemaphore);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_LITTLEFS_FLASH)
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
int rm_littlefs_flash_read (const struct lfs_config * c,
                            lfs_block_t               block,
                            lfs_off_t                 off,
                            void                    * buffer,
                            lfs_size_t                size)
{
    rm_littlefs_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_flash_instance_ctrl_t *) c->context;
#if RM_LITTLEFS_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RM_LITTLEFS_FLASH_OPEN == p_instance_ctrl->open, LFS_ERR_IO);
#endif

    /* Read directly from the flash. */
    memcpy(buffer,
           (uint8_t *) (rm_littlefs_flash_data_start + (p_instance_ctrl->p_cfg->p_lfs_cfg->block_size * block) + off),
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
int rm_littlefs_flash_write (const struct lfs_config * c,
                             lfs_block_t               block,
                             lfs_off_t                 off,
                             const void              * buffer,
                             lfs_size_t                size)
{
    rm_littlefs_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_flash_instance_ctrl_t *) c->context;
#if RM_LITTLEFS_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RM_LITTLEFS_FLASH_OPEN == p_instance_ctrl->open, LFS_ERR_IO);
#endif

    rm_littlefs_flash_cfg_t const * p_extend = (rm_littlefs_flash_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    flash_instance_t const        * p_flash  = p_extend->p_flash;

    /* Call the underlying driver. */
    fsp_err_t err =
        p_flash->p_api->write(p_flash->p_ctrl,
                              (uint32_t) buffer,
                              (rm_littlefs_flash_data_start +
                               (p_instance_ctrl->p_cfg->p_lfs_cfg->block_size * block) + off),
                              size);

    /* Write failed. Return IO error. Negative error codes are propogated to the user. */
    FSP_ERROR_RETURN(FSP_SUCCESS == err, LFS_ERR_IO);

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
int rm_littlefs_flash_erase (const struct lfs_config * c, lfs_block_t block)
{
    rm_littlefs_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_flash_instance_ctrl_t *) c->context;
#if RM_LITTLEFS_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(RM_LITTLEFS_FLASH_OPEN == p_instance_ctrl->open, LFS_ERR_IO);
#endif
    rm_littlefs_flash_cfg_t const * p_extend = (rm_littlefs_flash_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    flash_instance_t const        * p_flash  = p_extend->p_flash;

    /* Call the underlying driver. */
    fsp_err_t err =
        p_flash->p_api->erase(p_flash->p_ctrl,
                              (rm_littlefs_flash_data_start + (p_instance_ctrl->p_cfg->p_lfs_cfg->block_size * block)),
                              p_instance_ctrl->p_cfg->p_lfs_cfg->block_size / RM_LITTLEFS_FLASH_DATA_BLOCK_SIZE);

    /* Erase failed. Return IO error. Negative error codes are propogated to the user. */
    FSP_ERROR_RETURN(FSP_SUCCESS == err, LFS_ERR_IO);

    return LFS_ERR_OK;
}

/*******************************************************************************************************************//**
 * Returns the version of this module.
 *
 * @retval     LFS_ERR_OK  Success.
 * @retval     LFS_ERR_IO  Lower layer is not open or failed to lock the flash.
 **********************************************************************************************************************/
int rm_littlefs_flash_lock (const struct lfs_config * c)
{
#if LFS_THREAD_SAFE
    rm_littlefs_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_flash_instance_ctrl_t *) c->context;
 #if RM_LITTLEFS_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_LITTLEFS_FLASH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif
    BaseType_t err = xSemaphoreTake(p_instance_ctrl->xSemaphore, RM_LITTLEFS_FLASH_SEMAPHORE_TIMEOUT);

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
int rm_littlefs_flash_unlock (const struct lfs_config * c)
{
#if LFS_THREAD_SAFE
    rm_littlefs_flash_instance_ctrl_t * p_instance_ctrl = (rm_littlefs_flash_instance_ctrl_t *) c->context;
 #if RM_LITTLEFS_FLASH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_LITTLEFS_FLASH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
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
int rm_littlefs_flash_sync (const struct lfs_config * c)
{
    FSP_PARAMETER_NOT_USED(c);

    return LFS_ERR_OK;
}
