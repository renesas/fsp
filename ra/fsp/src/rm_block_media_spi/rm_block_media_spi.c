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
#include <string.h>

#include "r_spi_flash_api.h"
#include "rm_block_media_api.h"
#include "rm_block_media_spi.h"
#include "rm_block_media_spi_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "SPI" in ASCII, used to identify general RM_BLOCK_MEDIA_SPI control block */
#define RM_BLOCK_MEDIA_SPI_OPEN    (0x51535049U)
#define SPI_BANK_SIZE              (64UL * 1024UL * 1024UL)

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/* Block Media SPI function pointers   */
const rm_block_media_api_t g_rm_block_media_on_spi =
{
    .open        = RM_BLOCK_MEDIA_SPI_Open,
    .mediaInit   = RM_BLOCK_MEDIA_SPI_MediaInit,
    .read        = RM_BLOCK_MEDIA_SPI_Read,
    .write       = RM_BLOCK_MEDIA_SPI_Write,
    .erase       = RM_BLOCK_MEDIA_SPI_Erase,
    .callbackSet = RM_BLOCK_MEDIA_SPI_CallbackSet,
    .statusGet   = RM_BLOCK_MEDIA_SPI_StatusGet,
    .infoGet     = RM_BLOCK_MEDIA_SPI_InfoGet,
    .close       = RM_BLOCK_MEDIA_SPI_Close,
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static fsp_err_t rm_block_media_spi_program(rm_block_media_spi_instance_ctrl_t * p_instance_ctrl,
                                            uint8_t                            * p_device_address,
                                            uint8_t const                      * p_buffer,
                                            uint32_t const                       num_blocks);

static fsp_err_t rm_block_media_spi_rom_read(rm_block_media_spi_instance_ctrl_t * p_instance_ctrl,
                                             uint8_t * const                      p_dest,
                                             uint32_t const                       start_block,
                                             uint32_t const                       num_blocks);

static void rm_block_media_call_callback(rm_block_media_spi_instance_ctrl_t * p_instance_ctrl,
                                         rm_block_media_event_t               event);

/*******************************************************************************************************************//**
 * @addtogroup RM_BLOCK_MEDIA_SPI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Parameter checking and Acquires mutex, then handles driver initialization at the HAL SPI layer and marking the
 * open flag in control block.
 *
 * Implements @ref rm_block_media_api_t::open.
 *
 * @retval FSP_SUCCESS           Block media for SPI framework is successfully opened.
 * @retval FSP_ERR_ASSERTION     One of the input parameters or their data references may be null.
 * @retval FSP_ERR_ALREADY_OPEN  The channel specified has already been opened. See HAL driver for other possible causes.
 * @return                       See @ref RENESAS_ERROR_CODES or HAL driver for other possible return codes or causes.
 *                               This function calls
 *                                   * @ref spi_flash_api_t::open
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_Open (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_cfg_t const * const p_cfg)
{
    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != ((rm_block_media_spi_extended_cfg_t *) p_cfg->p_extend)->p_spi);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    rm_block_media_spi_extended_cfg_t * p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_cfg->p_extend;
    spi_flash_instance_t              * p_spi_flash    = (spi_flash_instance_t *) p_extended_cfg->p_spi;

    /* Open the underlying driver. */
    fsp_err_t err = p_spi_flash->p_api->open(p_spi_flash->p_ctrl, p_spi_flash->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Populate the control structure */
    p_instance_ctrl->p_spi_flash = p_spi_flash;
    p_instance_ctrl->p_cfg       = p_cfg;

    /* Module is now open */
    p_instance_ctrl->open = RM_BLOCK_MEDIA_SPI_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Retrieves module information.
 *
 * Implements @ref rm_block_media_api_t::infoGet.
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_InfoGet (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_info_t * const p_info)
{
    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_spi_extended_cfg_t * p_extended_cfg;
    p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    p_info->num_sectors       = p_extended_cfg->block_count_total;
    p_info->sector_size_bytes = p_extended_cfg->block_size_bytes;
    p_info->write_protected   = false;
    p_info->reentrant         = false;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the Block Media SPI Flash device.
 *
 * Implements @ref rm_block_media_api_t::mediaInit.
 *
 * @retval     FSP_SUCCESS               Module is initialized and ready to access the memory device.
 * @retval     FSP_ERR_ASSERTION         An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN          Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_MediaInit (rm_block_media_ctrl_t * const p_ctrl)
{
    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;
#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->initialized = true;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Reads a number of blocks from spi flash memory. By default, this is a function is blocking. Non-blocking operation
 * may be achieved by yielding control within the optional callback function.
 *
 * Implements @ref rm_block_media_api_t::read.
 *
 * @retval  FSP_SUCCESS              SPI data read successfully
 * @retval  FSP_ERR_ASSERTION        p_ctrl or p_dest is NULL, or num_blocks is zero
 * @retval  FSP_ERR_NOT_OPEN         Block Media SPI  module is not yet open
 * @retval  FSP_ERR_INVALID_ADDRESS  Invalid address range for read operation
 * @retval  FSP_ERR_NOT_INITIALIZED  Block Media SPI  module is not yet initialized
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_Read (rm_block_media_ctrl_t * const p_ctrl,
                                   uint8_t * const               p_dest,
                                   uint32_t const                start_block,
                                   uint32_t const                num_blocks)
{
    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(num_blocks > 0U);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_spi_extended_cfg_t * p_extended_cfg;
    p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint32_t block_count = p_extended_cfg->block_count_total;

    /* Check if the address is within flash size */
    if (block_count < (start_block + num_blocks))
    {
        return FSP_ERR_INVALID_ADDRESS;
    }

    fsp_err_t err = rm_block_media_spi_rom_read(p_instance_ctrl, p_dest, start_block, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides driver status.
 *
 * Implements @ref rm_block_media_api_t::statusGet.
 *
 * @retval  FSP_SUCCESS              Status stored in p_status.
 * @retval  FSP_ERR_ASSERTION        NULL pointer.
 * @retval  FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @return  See @ref RENESAS_ERROR_CODES or HAL driver for other possible return codes or causes.
 *          This function calls
 *              * @ref spi_flash_api_t::statusGet
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_StatusGet (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_status_t * const p_status)
{
    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Call the underlying driver. */
    rm_block_media_spi_extended_cfg_t * p_extended_cfg;
    spi_flash_instance_t              * p_spi_flash;

    p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    p_spi_flash    = (spi_flash_instance_t *) p_extended_cfg->p_spi;

    spi_flash_status_t status;
    fsp_err_t          err = p_spi_flash->p_api->statusGet(p_spi_flash->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    bool spi_driver_busy   = status.write_in_progress;
    bool block_driver_busy = p_instance_ctrl->read_in_progress || p_instance_ctrl->write_in_progress ||
                             p_instance_ctrl->erase_in_progress;

    p_status->media_inserted = true;
    p_status->initialized    = p_instance_ctrl->initialized;
    p_status->busy           = spi_driver_busy || block_driver_busy;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Writes provided data to a number of blocks of spi flash memory. By default, this is a function is blocking.
 * Non-blocking operation may be achieved by yielding control within the optional callback function.
 *
 * Implements @ref rm_block_media_api_t::write.
 *
 * @retval  FSP_SUCCESS              Flash write finished successfully.
 * @retval  FSP_ERR_ASSERTION        p_ctrl or p_src is NULL. Or num_blocks is zero.
 * @retval  FSP_ERR_NOT_OPEN         Block media SPI Framework module is not yet initialized.
 * @retval  FSP_ERR_INVALID_ADDRESS  Invalid address range
 * @retval  FSP_ERR_NOT_INITIALIZED  Block Media SPI  module is not yet initialized
 *
 * @return  See @ref RENESAS_ERROR_CODES or HAL driver for other possible return codes or causes.
 *          This function calls
 *              * @ref spi_flash_api_t::write
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_Write (rm_block_media_ctrl_t * const p_ctrl,
                                    uint8_t const * const         p_src,
                                    uint32_t const                start_block,
                                    uint32_t const                num_blocks)
{
    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(num_blocks > 0U);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_spi_extended_cfg_t * p_extended_cfg;
    p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Calculate the address of flash */
    uint32_t block_count = p_extended_cfg->block_count_total;

    /* Check if the address is within flash size */
    if (block_count < (start_block + num_blocks))
    {
        return FSP_ERR_INVALID_ADDRESS;
    }

    fsp_err_t err = FSP_SUCCESS;
    err = RM_BLOCK_MEDIA_SPI_Erase(p_instance_ctrl, start_block, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write data into the block media SPI flash */
    uint32_t base_address = p_extended_cfg->base_address;
    uint32_t rom_address  = base_address + (p_extended_cfg->block_size_bytes * start_block);
    err = rm_block_media_spi_program(p_instance_ctrl, (uint8_t *) rom_address, p_src, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure. API not supported.
 *
 * Implements @ref rm_block_media_api_t::callbackSet.
 *
 * @retval  FSP_ERR_UNSUPPORTED         API not supported by RM_BLOCK_MEDIA_SPI.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_CallbackSet (rm_block_media_ctrl_t * const p_ctrl,
                                          void (                      * p_callback)(
                                              rm_block_media_callback_args_t *),
                                          void const * const                     p_context,
                                          rm_block_media_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);
    FSP_PARAMETER_NOT_USED(p_context);
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    return FSP_ERR_UNSUPPORTED;
}

/******************************************************************************************************************//**
 * Closes the Block Media SPI device. Implements @ref rm_block_media_api_t::close.
 *
 * @retval  FSP_SUCCESS           Successful close.
 * @retval  FSP_ERR_ASSERTION     One of the following parameters may be null: p_ctrl.
 * @retval  FSP_ERR_NOT_OPEN      Block media SPI Framework module is not yet initialized.
 * @return                        See @ref RENESAS_ERROR_CODES or HAL driver for other possible return codes or causes.
 *                                This function calls
 *                                    * @ref spi_flash_api_t::close
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_Close (rm_block_media_ctrl_t * const p_ctrl)
{
    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Call lower level API. The error code is not checked here, since module close functions should never fail */
    p_instance_ctrl->p_spi_flash->p_api->close(p_instance_ctrl->p_spi_flash->p_ctrl);
    p_instance_ctrl->open        = 0U;
    p_instance_ctrl->initialized = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function erases blocks of the SPI device. By default, this is a function is blocking. Non-blocking operation
 * may be achieved by yielding control within the optional callback function.
 *
 * Implements @ref rm_block_media_api_t::erase.
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 * @retval     FSP_ERR_INVALID_ADDRESS       Invalid address range
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref spi_flash_api_t::erase
 *             * @ref spi_flash_api_t::statusGet
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_Erase (rm_block_media_ctrl_t * const p_ctrl,
                                    uint32_t const                start_block,
                                    uint32_t const                num_blocks)
{
    rm_block_media_spi_extended_cfg_t * p_extended_cfg;
    spi_flash_instance_t              * p_spi_flash;
    uint8_t * rom_address;

    rm_block_media_spi_instance_ctrl_t * p_instance_ctrl = (rm_block_media_spi_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_SPI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint32_t block_count = p_extended_cfg->block_count_total;
    uint32_t block_size  = p_extended_cfg->block_size_bytes;

    /* Check if the address is within flash size */
    if (block_count < (start_block + num_blocks))
    {
        return FSP_ERR_INVALID_ADDRESS;
    }

#if RM_BLOCK_MEDIA_SPI_CFG_PARAM_CHECKING_ENABLE

    /* Confirm start and end blocks are within range */
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    p_spi_flash = (spi_flash_instance_t *) p_extended_cfg->p_spi;
    rom_address = (uint8_t *) p_extended_cfg->base_address + (start_block * block_size);

    /* Erase the blocks, one at a time */
    fsp_err_t          err       = FSP_SUCCESS;
    uint32_t           iteration = num_blocks;
    spi_flash_status_t status;
    p_instance_ctrl->erase_in_progress = true;
    while ((iteration > 0U) && (FSP_SUCCESS == err))
    {
        err = p_spi_flash->p_api->erase(p_spi_flash->p_ctrl, rom_address, block_size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Wait until operation is in complete */
        err = p_spi_flash->p_api->statusGet(p_spi_flash->p_ctrl, &status);
        while ((FSP_SUCCESS == err) &&
               (true == status.write_in_progress))
        {
            /* Notify application of erase in progress */
            rm_block_media_call_callback(p_instance_ctrl, RM_BLOCK_MEDIA_EVENT_POLL_STATUS);
            err = p_spi_flash->p_api->statusGet(p_spi_flash->p_ctrl, &status);
        }

        /* Calculate next block address */
        rom_address = rom_address + block_size;
        iteration--;
    }

    /* Notify appication of completion */
    p_instance_ctrl->erase_in_progress = false;
    rm_block_media_event_t event =
        (FSP_SUCCESS == err ? RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE : RM_BLOCK_MEDIA_EVENT_ERROR);
    rm_block_media_call_callback(p_instance_ctrl, event);

    return err;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This is the subroutine for the RM_BLOCK_MEDIA_SPI_Write API.
 *
 * @retval  FSP_SUCCESS             No parameter error found
 * @return                          See @ref RENESAS_ERROR_CODES or HAL driver for other possible return codes or causes.
 *                                  This function calls
 *                                      * @ref spi_flash_api_t::write
 *                                      * @ref spi_flash_api_t::statusGet
 **********************************************************************************************************************/
static fsp_err_t rm_block_media_spi_program (rm_block_media_spi_instance_ctrl_t * p_instance_ctrl,
                                             uint8_t                            * p_device_address,
                                             uint8_t const                      * p_buffer,
                                             uint32_t const                       num_blocks)
{
    /* Instance and error data */
    fsp_err_t              err         = FSP_SUCCESS;
    spi_flash_instance_t * p_spi_flash = p_instance_ctrl->p_spi_flash;
    uint32_t               page_size   = p_spi_flash->p_cfg->page_size_bytes;

    rm_block_media_spi_extended_cfg_t * p_extended_cfg;
    p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint32_t           byte_req  = num_blocks * (p_extended_cfg->block_size_bytes);
    uint32_t           iteration = byte_req / page_size;
    spi_flash_status_t status;

    /* Write data into the block media SPI flash */
    p_instance_ctrl->write_in_progress = true;
    while ((iteration > 0U) && (FSP_SUCCESS == err))
    {
        err = p_spi_flash->p_api->write(p_spi_flash->p_ctrl, p_buffer, p_device_address, page_size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = p_spi_flash->p_api->statusGet(p_spi_flash->p_ctrl, &status);
        while ((FSP_SUCCESS == err) &&
               (true == status.write_in_progress))
        {
            /* Notify application of read in progress */
            rm_block_media_call_callback(p_instance_ctrl, RM_BLOCK_MEDIA_EVENT_POLL_STATUS);
            err = p_spi_flash->p_api->statusGet(p_spi_flash->p_ctrl, &status);
        }

        p_device_address = p_device_address + page_size;
        p_buffer         = p_buffer + page_size;
        iteration--;
    }

    /* Notify appication of completion */
    p_instance_ctrl->write_in_progress = false;
    rm_block_media_event_t event =
        (FSP_SUCCESS == err ? RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE : RM_BLOCK_MEDIA_EVENT_ERROR);
    rm_block_media_call_callback(p_instance_ctrl, event);

    return err;
}

/*******************************************************************************************************************//**
 * This is the subroutine for the RM_BLOCK_MEDIA_SPI_READ API to read data from banks using ROM area.
 *
 * @retval  FSP_SUCCESS             No parameter error found
 **********************************************************************************************************************/
static fsp_err_t rm_block_media_spi_rom_read (rm_block_media_spi_instance_ctrl_t * p_instance_ctrl,
                                              uint8_t * const                      p_dest,
                                              uint32_t const                       start_block,
                                              uint32_t const                       num_blocks)
{
    /* Calculate read address and size */
    rm_block_media_spi_extended_cfg_t * p_extended_cfg;
    p_extended_cfg = (rm_block_media_spi_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint32_t block_size   = p_extended_cfg->block_size_bytes;
    uint32_t base_address = p_extended_cfg->base_address;
    uint32_t read_bytes   = num_blocks * block_size;
    uint32_t rom_address  = base_address + (block_size * start_block);

    /* Read data from block media SPI flash */
    p_instance_ctrl->read_in_progress = true;
    memcpy(p_dest, (uint8_t *) rom_address, read_bytes);

    /* Notify application of completion */
    p_instance_ctrl->read_in_progress = false;
    rm_block_media_call_callback(p_instance_ctrl, RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This is the subroutine for validating and calling the application configured callback.
 **********************************************************************************************************************/
static void rm_block_media_call_callback (rm_block_media_spi_instance_ctrl_t * p_instance_ctrl,
                                          rm_block_media_event_t               event)
{
    void (* p_callback)(rm_block_media_callback_args_t *) = p_instance_ctrl->p_cfg->p_callback;

    if (NULL != p_callback)
    {
        rm_block_media_callback_args_t args =
        {
            .event     = event,
            .p_context = p_instance_ctrl->p_cfg->p_context
        };

        p_callback(&args);
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLOCK_MEDIA_SPI)
 **********************************************************************************************************************/
