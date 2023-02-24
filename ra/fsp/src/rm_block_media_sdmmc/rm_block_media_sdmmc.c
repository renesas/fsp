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
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * rm_block_media_sdmmc_prv_ns_callback)(rm_block_media_callback_args_t *
                                                                              p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile rm_block_media_sdmmc_prv_ns_callback)(rm_block_media_callback_args_t *
                                                                                      p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void rm_block_media_sdmmc_callback(sdmmc_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const rm_block_media_api_t g_rm_block_media_on_sdmmc =
{
    .open        = RM_BLOCK_MEDIA_SDMMC_Open,
    .mediaInit   = RM_BLOCK_MEDIA_SDMMC_MediaInit,
    .read        = RM_BLOCK_MEDIA_SDMMC_Read,
    .write       = RM_BLOCK_MEDIA_SDMMC_Write,
    .erase       = RM_BLOCK_MEDIA_SDMMC_Erase,
    .callbackSet = RM_BLOCK_MEDIA_SDMMC_CallbackSet,
    .infoGet     = RM_BLOCK_MEDIA_SDMMC_InfoGet,
    .statusGet   = RM_BLOCK_MEDIA_SDMMC_StatusGet,
    .close       = RM_BLOCK_MEDIA_SDMMC_Close,
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

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* This module is now open. */
    p_instance_ctrl->initialized     = false;
    p_instance_ctrl->write_protected = false;
    p_instance_ctrl->open            = RM_BLOCK_MEDIA_SDMMC_OPEN;

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
    p_instance_ctrl->write_protected   = device.write_protected;
    p_instance_ctrl->initialized       = true;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads data from an SD or eMMC device.  Up to 0x10000 sectors can be read at a time. Implements
 * @ref rm_block_media_api_t::read().
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
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref rm_block_media_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SDMMC_CallbackSet (rm_block_media_ctrl_t * const p_ctrl,
                                            void (                      * p_callback)(
                                                rm_block_media_callback_args_t *),
                                            void const * const                     p_context,
                                            rm_block_media_callback_args_t * const p_callback_memory)
{
    rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl = (rm_block_media_sdmmc_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SDMMC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if RM_BLOCK_MEDIA_SDMMC_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    rm_block_media_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                                 CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(rm_block_media_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

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
    p_info->write_protected   = p_instance_ctrl->write_protected;

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
 * @} (end addtogroup RM_BLOCK_MEDIA_SDMMC)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Call configured callback function.
 *
 * @param[in] p_instance_ctrl          Pointer to instance control block
 * @param[in] p_args                   Pointer to callback arguments
 **********************************************************************************************************************/
static inline void rm_block_media_sdmmc_call_callback (rm_block_media_sdmmc_instance_ctrl_t * p_instance_ctrl,
                                                       rm_block_media_callback_args_t       * p_args)
{
#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_instance_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_instance_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        rm_block_media_sdmmc_prv_ns_callback p_callback =
            (rm_block_media_sdmmc_prv_ns_callback) (p_instance_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_instance_ctrl->p_callback(p_args);
#endif
}

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
    args.p_context = p_instance_ctrl->p_context;
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
        if (NULL != p_instance_ctrl->p_callback)
        {
            rm_block_media_callback_args_t args_stacked;

            /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
             * stored in non-secure memory so they can be accessed by a non-secure callback function. */
            rm_block_media_callback_args_t * p_args_memory = p_instance_ctrl->p_callback_memory;
            if (NULL == p_args_memory)
            {
                /* Use provided args struct on stack */
                p_args_memory = &args;
            }
            else
            {
                /* Save current arguments on the stack in case this is a nested interrupt. */
                args_stacked = *p_args_memory;

                /* Copy the stacked args to callback memory */
                *p_args_memory = args;
            }

            rm_block_media_sdmmc_call_callback(p_instance_ctrl, p_args_memory);

            if (NULL != p_instance_ctrl->p_callback_memory)
            {
                /* Restore callback memory in case this is a nested interrupt. */
                *p_instance_ctrl->p_callback_memory = args_stacked;
            }
        }
    }
}
