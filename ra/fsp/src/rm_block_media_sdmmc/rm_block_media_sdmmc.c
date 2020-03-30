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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_block_media_sdmmc.h"
#include "rm_block_media_sdmmc_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "MESD" in ASCII. */
#define RM_BLOCK_MEDIA_SDMMC_OPEN                (0x4D454D53)

#define RM_BLOCK_MEDIA_SDMMC_PRV_SD_R1_ERRORS    (0xFDF98008U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void rm_block_media_sdmmc_callback(sdmmc_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure. */
static const fsp_version_t g_rm_block_media_sdmmc_version =
{
    .api_version_minor  = RM_BLOCK_MEDIA_API_VERSION_MINOR,
    .api_version_major  = RM_BLOCK_MEDIA_API_VERSION_MAJOR,
    .code_version_major = RM_BLOCK_MEDIA_SDMMC_CODE_VERSION_MAJOR,
    .code_version_minor = RM_BLOCK_MEDIA_SDMMC_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const rm_block_media_api_t g_rm_block_media_on_sdmmc =
{
    .open       = RM_BLOCK_MEDIA_SDMMC_Open,
    .mediaInit  = RM_BLOCK_MEDIA_SDMMC_MediaInit,
    .read       = RM_BLOCK_MEDIA_SDMMC_Read,
    .write      = RM_BLOCK_MEDIA_SDMMC_Write,
    .erase      = RM_BLOCK_MEDIA_SDMMC_Erase,
    .infoGet    = RM_BLOCK_MEDIA_SDMMC_InfoGet,
    .statusGet  = RM_BLOCK_MEDIA_SDMMC_StatusGet,
    .close      = RM_BLOCK_MEDIA_SDMMC_Close,
    .versionGet = RM_BLOCK_MEDIA_SDMMC_VersionGet,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_BLOCK_MEDIA_SDMMC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the module.
 *
 * Implements @ref rm_block_media_api_t::open().
 *
 * @retval     FSP_SUCCESS                     Module is available and is now open.
 * @retval     FSP_ERR_ASSERTION               An input parameter is invalid.
 * @retval     FSP_ERR_ALREADY_OPEN            Module has already been opened with this instance of the control
 *                                             structure.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref sdmmc_api_t::open
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_Open (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_cfg_t const * const p_cfg)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
#endif

    rm_block_media_sdmmc_extended_cfg_t * p_extended_cfg = (rm_block_media_sdmmc_extended_cfg_t *) p_cfg->p_extend;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg);
    FSP_ASSERT(NULL != p_extended_cfg->p_sdmmc);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif
    p_instance_ctrl->p_cfg = p_cfg;

    /* Open the underlying driver. */
    sdmmc_instance_t * p_sdmmc = (sdmmc_instance_t *) p_extended_cfg->p_sdmmc;
    fsp_err_t          err     = p_sdmmc->p_api->open(p_sdmmc->p_ctrl, p_sdmmc->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* This module is now open. */
    p_instance_ctrl->initialized = false;
    p_instance_ctrl->open        = RM_BLOCK_MEDIA_SDMMC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the SD or eMMC device.  This procedure requires several sequential commands.  This function blocks
 * until all identification and configuration commands are complete.
 *
 * Implements @ref rm_block_media_api_t::mediaInit().
 *
 * @retval     FSP_SUCCESS               Module is initialized and ready to access the memory device.
 * @retval     FSP_ERR_ASSERTION         An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN          Module is not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref sdmmc_api_t::mediaInit
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_MediaInit (rm_block_media_ctrl_t * const p_ctrl)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_block_media_sdmmc_extended_cfg_t * p_extended_cfg =
        (rm_block_media_sdmmc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Call the underlying driver. */
    sdmmc_instance_t * p_sdmmc = (sdmmc_instance_t *) p_extended_cfg->p_sdmmc;
    sdmmc_device_t     device;
    fsp_err_t          err = p_sdmmc->p_api->mediaInit(p_sdmmc->p_ctrl, &device);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_instance_ctrl->sector_count      = device.sector_count;
    p_instance_ctrl->sector_size_bytes = device.sector_size_bytes;
    p_instance_ctrl->initialized       = true;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads data from an SD or eMMC device.  Up to 0x10000 sectors can be read at a time. Implements
 * @ref rm_block_media_api_t::read().
 *
 * This function blocks until the data is read into the destination buffer.
 *
 * @retval     FSP_SUCCESS                   Data read successfully.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref sdmmc_api_t::read
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_Read (rm_block_media_ctrl_t * const p_ctrl,
                                     uint8_t * const               p_dest_address,
                                     uint32_t const                block_address,
                                     uint32_t const                num_blocks)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_dest_address);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_sdmmc_extended_cfg_t * p_extended_cfg =
        (rm_block_media_sdmmc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    sdmmc_instance_t * p_sdmmc = (sdmmc_instance_t *) p_extended_cfg->p_sdmmc;

    /* Call the underlying driver. */
    fsp_err_t err = p_sdmmc->p_api->read(p_sdmmc->p_ctrl, p_dest_address, block_address, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes data to an SD or eMMC device. Up to 0x10000 sectors can be written at a time. Implements
 * @ref rm_block_media_api_t::write().
 *
 * This function blocks until the write operation completes.
 *
 * @retval     FSP_SUCCESS                   Write finished successfully.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref sdmmc_api_t::write
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_Write (rm_block_media_ctrl_t * const p_ctrl,
                                      uint8_t const * const         p_src_address,
                                      uint32_t const                block_address,
                                      uint32_t const                num_blocks)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_src_address);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_sdmmc_extended_cfg_t * p_extended_cfg =
        (rm_block_media_sdmmc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    sdmmc_instance_t * p_sdmmc = (sdmmc_instance_t *) p_extended_cfg->p_sdmmc;

    /* Call the underlying driver. */
    fsp_err_t err = p_sdmmc->p_api->write(p_sdmmc->p_ctrl, p_src_address, block_address, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erases sectors of an SD card or eMMC device.  Implements @ref rm_block_media_api_t::erase().
 *
 * This function blocks until erase is complete.
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref sdmmc_api_t::erase
 *             * @ref sdmmc_api_t::statusGet
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_Erase (rm_block_media_ctrl_t * const p_ctrl,
                                      uint32_t const                block_address,
                                      uint32_t const                num_blocks)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_sdmmc_extended_cfg_t * p_extended_cfg =
        (rm_block_media_sdmmc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    sdmmc_instance_t * p_sdmmc = (sdmmc_instance_t *) p_extended_cfg->p_sdmmc;

    /* Call the underlying driver. */
    fsp_err_t err = p_sdmmc->p_api->erase(p_sdmmc->p_ctrl, block_address, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides driver status.  Implements @ref rm_block_media_api_t::statusGet().
 *
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_StatusGet (rm_block_media_ctrl_t * const   p_api_ctrl,
                                          rm_block_media_status_t * const p_status)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_api_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_block_media_sdmmc_extended_cfg_t * p_extended_cfg =
        (rm_block_media_sdmmc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    sdmmc_instance_t * p_sdmmc = (sdmmc_instance_t *) p_extended_cfg->p_sdmmc;

    /* Call the underlying driver. */
    sdmmc_status_t status;
    fsp_err_t      err = p_sdmmc->p_api->statusGet(p_sdmmc->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_status->media_inserted = status.card_inserted;
    p_status->initialized    = p_instance_ctrl->initialized;
    p_status->busy           = status.transfer_in_progress;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Retrieves module information.  Implements @ref rm_block_media_api_t::infoGet().
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_InfoGet (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_info_t * const p_info)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    p_info->sector_size_bytes = p_instance_ctrl->sector_size_bytes;
    p_info->num_sectors       = p_instance_ctrl->sector_count;
    p_info->reentrant         = false;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes an open SD/MMC device.  Implements @ref rm_block_media_api_t::close().
 *
 * @retval     FSP_SUCCESS                   Successful close.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_Close (rm_block_media_ctrl_t * const p_ctrl)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->open = 0U;

    rm_block_media_sdmmc_extended_cfg_t * p_extended_cfg =
        (rm_block_media_sdmmc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Call the underlying driver. */
    sdmmc_instance_t * p_sdmmc = (sdmmc_instance_t *) p_extended_cfg->p_sdmmc;
    p_sdmmc->p_api->close(p_sdmmc->p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the version of the firmware and API.  Implements @ref rm_block_media_api_t::versionGet().
 *
 * @retval     FSP_SUCCESS        Function executed successfully.
 * @retval     FSP_ERR_ASSERTION  Null Pointer.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_VersionGet (fsp_version_t * const p_version)
{
    fsp_err_t err = FSP_SUCCESS;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE

    /* Check pointers for NULL values */
    FSP_ASSERT(NULL != p_version);
#endif
    p_version->version_id = g_rm_block_media_sdmmc_version.version_id;

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLOCK_MEDIA_SDMMC)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Passes callback event from the lower layer driver to the user.
 *
 * @param[in] p_args              SD/MMC callback arguments.
 **********************************************************************************************************************/
void rm_block_media_sdmmc_callback (sdmmc_callback_args_t * p_args)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_args->p_context;

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    args.p_context = p_instance_ctrl->p_cfg->p_context;
    if ((SDMMC_EVENT_ERASE_COMPLETE | SDMMC_EVENT_TRANSFER_COMPLETE) & p_args->event)
    {
        args.event |= RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
    }

    if ((SDMMC_EVENT_TRANSFER_ERROR & p_args->event) ||
        (p_instance_ctrl->initialized && (RM_BLOCK_MEDIA_SDMMC_PRV_SD_R1_ERRORS & p_args->response.status)))
    {
        args.event |= RM_BLOCK_MEDIA_EVENT_ERROR;
    }

    if (SDMMC_EVENT_ERASE_BUSY & p_args->event)
    {
        args.event |= RM_BLOCK_MEDIA_EVENT_POLL_STATUS;
    }

    if (SDMMC_EVENT_CARD_REMOVED & p_args->event)
    {
        p_instance_ctrl->initialized = false;
        args.event |= RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED;
    }

    if (SDMMC_EVENT_CARD_INSERTED & p_args->event)
    {
        args.event |= RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED;
    }

    if (args.event)
    {
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }
}
