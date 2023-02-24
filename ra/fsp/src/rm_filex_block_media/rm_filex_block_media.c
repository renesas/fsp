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
#include "rm_filex_block_media.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "FXBM" in ASCII, used to determine if channel is open. */
#define RM_FILEX_BLOCK_MEDIA_OPEN    (0x70886677ULL)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t rm_filex_block_media_driver_request_handler(FX_MEDIA * p_fx_media);
void             rm_filex_block_media_memory_callback(rm_block_media_callback_args_t * p_args);
static fsp_err_t rm_filex_block_media_wait_event(rm_filex_block_media_instance_ctrl_t * p_instance_ctrl);
static fsp_err_t rm_filex_block_media_write(rm_filex_block_media_instance_ctrl_t * p_instance_ctrl,
                                            uint8_t                              * p_src_address,
                                            uint32_t                               block_address,
                                            uint32_t                               num_blocks);
static fsp_err_t rm_filex_block_media_read(rm_filex_block_media_instance_ctrl_t * p_instance_ctrl,
                                           uint8_t                              * p_dest_address,
                                           uint32_t                               block_address,
                                           uint32_t                               num_blocks);

/* FileX utility functions */
extern UINT _fx_partition_offset_calculate(void  * partition_sector,
                                           UINT    partition,
                                           ULONG * partition_start,
                                           ULONG * partition_size);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** File X HAL API mapping for File X Block Media interface */
const rm_filex_block_media_api_t g_filex_on_block_media =
{
    .open  = RM_FILEX_BLOCK_MEDIA_Open,
    .close = RM_FILEX_BLOCK_MEDIA_Close
};

/*******************************************************************************************************************//**
 * @addtogroup RM_FILEX_BLOCK_MEDIA
 * @{
 **********************************************************************************************************************/

/** The file system relies on the media to be formatted prior to creating directories and files
 *  The sector size and sector count will change depending on the media type and size.
 *
 *  The File Allocation Table (FAT) starts after the reserved sectors in the media. The FAT area is
 *  basically an array of 12-bit, 16-bit, or 32-bit entries that determine if that cluster is
 *  allocated or part of a chain of clusters comprising a subdirectory or a file.
 *  The size of each FAT entry is determined by the number of clusters that need to be represented.
 *  If the number of clusters (derived from the total sectors divided by the sectors per cluster)
 *  is less than 4,086, 12-bit FAT entries are used. If the total number of clusters is greater
 *  than 4,086 and less than or equal to 65,525, 16-bit FAT entries are used. Otherwise, if the
 *  total number of clusters is greater than 65,525, 32-bit FAT entries are used.
 */

/*******************************************************************************************************************//**
 * Initializes callback and configuration for FileX Block Media interface.
 * Call this before calling any FileX functions.
 *
 * Implements @ref rm_filex_block_media_api_t::open().
 *
 * @retval FSP_SUCCESS              Success.
 * @retval FSP_ERR_ASSERTION        An input parameter was invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_FILEX_BLOCK_MEDIA_Open (rm_filex_block_media_ctrl_t * const      p_ctrl,
                                     rm_filex_block_media_cfg_t const * const p_cfg)
{
    rm_filex_block_media_instance_ctrl_t * p_instance_ctrl = (rm_filex_block_media_instance_ctrl_t *) p_ctrl;
    fsp_err_t err;

#if RM_FILEX_BLOCK_MEDIA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_lower_lvl_block_media);
    FSP_ERROR_RETURN(RM_FILEX_BLOCK_MEDIA_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Open the lower level block media. */
    rm_block_media_instance_t * p_lower_lvl_block_media = p_cfg->p_lower_lvl_block_media;
    err = p_lower_lvl_block_media->p_api->open(p_lower_lvl_block_media->p_ctrl, p_lower_lvl_block_media->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Initialize control structure. */
    p_instance_ctrl->p_cfg = p_cfg;
    p_instance_ctrl->open  = RM_FILEX_BLOCK_MEDIA_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes media device.
 *
 * Implements @ref rm_filex_block_media_api_t::close().
 *
 * @retval FSP_SUCCESS           Media device closed.
 * @retval FSP_ERR_ASSERTION     An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN      Module not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_FILEX_BLOCK_MEDIA_Close (rm_filex_block_media_ctrl_t * const p_ctrl)
{
    rm_filex_block_media_instance_ctrl_t * p_instance_ctrl = (rm_filex_block_media_instance_ctrl_t *) p_ctrl;
#if RM_FILEX_BLOCK_MEDIA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_FILEX_BLOCK_MEDIA_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close lower level block media*/
    rm_block_media_instance_t * p_lower_lvl_block_media = p_instance_ctrl->p_cfg->p_lower_lvl_block_media;
    p_lower_lvl_block_media->p_api->close(p_lower_lvl_block_media->p_ctrl);

    p_instance_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Access Block Media device functions open, close, read, write and control.
 *
 * The RM_FILEX_BLOCK_MEDIA_BlockDriver function is called from the FileX file system driver and issues requests
 * to a Block Media device through the FSP Block Media Interface. Uses block media driver for accesses.
 *
 * @param[in,out] p_fx_media        FileX media control block. All information about each open media
 *                                  device are maintained in the FX_MEDIA data type.
 *                                  The I/O driver communicates the success or failure of the request
 *                                  through the fx_media_driver_status member of FX_MEDIA
 *                                  (p_fx_media->fx_media_driver_status).
 *                                  Possible values are documented in the FileX User Guide.
 *
 * @retval None
 *
 * @return Nothing, but updates FileX media control block.
 **********************************************************************************************************************/
void RM_FILEX_BLOCK_MEDIA_BlockDriver (FX_MEDIA * p_fx_media)
{
    fsp_err_t ret_val = FSP_SUCCESS;

    /* Initialize FileX I/O status to error. It will change to FX_SUCCESS unless an operation fails. */
    p_fx_media->fx_media_driver_status = FX_IO_ERROR;

#if  (RM_FILEX_BLOCK_MEDIA_CFG_PARAM_CHECKING_ENABLE)

    /* Validate FX_MEDIA::fx_media_driver_info and update FX_MEDIA::fx_media_driver_status to FX_PTR_ERROR in case of any failure. */
    if (NULL == p_fx_media->fx_media_driver_info)
    {
        return;
    }
#endif

    /* Pass control to request handler, which is responsible for setting FX_MEDIA::fx_media_driver_status in-case of any failure. */
    ret_val = rm_filex_block_media_driver_request_handler(p_fx_media);

    if (FSP_SUCCESS == ret_val)
    {
        /* Update FX_MEDIA::fx_media_driver_status to FX_SUCCESS on successful driver request. */
        p_fx_media->fx_media_driver_status = FX_SUCCESS;
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_FILEX_BLOCK_MEDIA)
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * @brief      Handles the FileX driver request
 * @param      p_fx_media      The pointer to FileX media
 *
 * @retval     FSP_SUCCESS                 Driver request fulfilled.
 * @retval     FSP_ERR_MEDIA_OPEN_FAILED   Not a valid boot record or partition table
 * @retval     FSP_ERR_UNSUPPORTED         Requested FileX command is not supported
 * @retval     FSP_ERR_INTERNAL            An error has occured with the lower level block media driver
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref rm_block_media_api_t::open
 *             * @ref rm_block_media_api_t::mediaInit
 *             * @ref rm_block_media_api_t::infoGet
 *             * @ref rm_block_media_api_t::close
 *********************************************************************************************************************/
static fsp_err_t rm_filex_block_media_driver_request_handler (FX_MEDIA * p_fx_media)
{
    fsp_err_t err;

    rm_filex_block_media_instance_ctrl_t * p_filex_block_media_instance_ctrl =
        ((rm_filex_block_media_instance_t *) p_fx_media->fx_media_driver_info)->p_ctrl;

    rm_block_media_instance_t * p_block_media = p_filex_block_media_instance_ctrl->p_cfg->p_lower_lvl_block_media;

    /* Process the driver request specified in the media control block. */
    switch (p_fx_media->fx_media_driver_request)
    {
        /* FX_DRIVER_READ
         *  FileX reads one or more sectors into memory by issuing a read request to the I/O driver. */
        case (UINT) FX_DRIVER_READ:
        {
            err = rm_filex_block_media_read(p_filex_block_media_instance_ctrl,
                                            p_fx_media->fx_media_driver_buffer,
                                            p_fx_media->fx_media_driver_logical_sector + p_fx_media->fx_media_hidden_sectors,
                                            p_fx_media->fx_media_driver_sectors);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            break;
        }

        /* FX_DRIVER_WRITE
         *  FileX writes one or more sectors to the physical media by issuing a write request to the I/O driver. */
        case (UINT) FX_DRIVER_WRITE:
        {
            err = rm_filex_block_media_write(p_filex_block_media_instance_ctrl,
                                             p_fx_media->fx_media_driver_buffer,
                                             p_fx_media->fx_media_driver_logical_sector +
                                             p_fx_media->fx_media_hidden_sectors,
                                             p_fx_media->fx_media_driver_sectors);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            break;
        }

        /* FX_DRIVER_FLUSH
         *  FileX flushes all sectors currently in the driver's sector cache to the physical media by issuing a flush request to the I/O driver.
         *  Command not supported in available FSP modules. Return driver success. */
        case (UINT) FX_DRIVER_FLUSH:
        {
            break;
        }

        /* FX_DRIVER_RELEASE_SECTORS
         *  If previously selected by the driver during initialization, FileX informs the driver whenever one or more
         *  consecutive sectors become free. FileX only sends the FX_DRIVER_RELEASE_SECTORS request
         *  if fx_media_driver_free_sector_update is FX_TRUE */
        case (UINT) FX_DRIVER_RELEASE_SECTORS:
        {
            /* Not currently implemented for any block media instances */
            break;
        }

        /* FX_DRIVER_ABORT
         *  FileX informs the driver to abort all further physical I/O activity with the physical media by issuing an
         *  abort request to the I/O driver. The driver should not perform any I/O again until it is re-initialized.
         *  This is typically called on fx_media_abort */
        case (UINT) FX_DRIVER_ABORT:
        {
            break;
        }

        /* FX_DRIVER_INIT
         *  Although the actual driver initialization processing is application specific, it usually consists of data
         *  structure initialization and possibly some preliminary hardware initialization. This request is the first
         *  made by FileX and is done from within the fx_media_open service. If media write protection is detected,
         *  the fx_media_driver_write_protect member of FX_MEDIA should be set to FX_TRUE. */
        case (UINT) FX_DRIVER_INIT:
        {
            rm_block_media_info_t block_media_info;

            /* Initialize the block media. */
            err = p_block_media->p_api->mediaInit(p_block_media->p_ctrl);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            /* Get block media info to see if write protect and sector release are set. */
            err = p_block_media->p_api->infoGet(p_block_media->p_ctrl, &block_media_info);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            /* Update FX_MEDIA::fx_media_driver_write_protect to FX_TRUE if write protect is enabled. */
            if (block_media_info.write_protected)
            {
                p_fx_media->fx_media_driver_write_protect = FX_TRUE;
            }

            /* Sector release isn't supported by any block media drivers. */
            p_fx_media->fx_media_driver_free_sector_update = FX_FALSE;

            break;
        }

        /* FX_DRIVER_UNINIT
         *  FileX uses the uninit command to close the media. This is typically called on fx_media_close. */
        case (UINT) FX_DRIVER_UNINIT:
        {
            break;
        }

        /* FX_DRIVER_BOOT_READ
         *  Instead of using a standard read request, FileX makes a specific request to read the media's boot
         *  sector. */
        case (UINT) FX_DRIVER_BOOT_READ:
        {
            ULONG partition_offset;
            UINT  fx_err;

            /* Read the first sector. */
            err =
                rm_filex_block_media_read(p_filex_block_media_instance_ctrl, p_fx_media->fx_media_driver_buffer, 0, 1);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            /* Check the partition offset to determine if the current sector is the boot record or partition table. */
            fx_err = _fx_partition_offset_calculate(p_fx_media->fx_media_driver_buffer,
                                                    p_filex_block_media_instance_ctrl->p_cfg->partition,
                                                    &partition_offset,
                                                    FX_NULL);

            if (FX_SUCCESS != fx_err)
            {
                p_fx_media->fx_media_driver_status = FX_MEDIA_INVALID;

                return FSP_ERR_MEDIA_OPEN_FAILED;
            }

            if (partition_offset > 0)
            {
                /* Read the sector at the offset indicated in the partition table. */
                err = rm_filex_block_media_read(p_filex_block_media_instance_ctrl,
                                                p_fx_media->fx_media_driver_buffer,
                                                partition_offset,
                                                1);
                FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
            }

            break;
        }

        /* FX_DRIVER_BOOT_WRITE
         *  Instead of using a standard write request, FileX makes a specific request to write the media's boot
         *  sector. */
        case (UINT) FX_DRIVER_BOOT_WRITE:
        {
            /* Write the boot record and return to the caller. */
            err = rm_filex_block_media_write(p_filex_block_media_instance_ctrl,
                                             p_fx_media->fx_media_driver_buffer,
                                             p_fx_media->fx_media_hidden_sectors,
                                             1);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
            break;
        }

        /* default
         *  Invalid driver request. */
        default:
        {
            p_fx_media->fx_media_driver_status = (UINT) FX_IO_ERROR;

            return FSP_ERR_UNSUPPORTED;
            break;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Notifies task of event completion.
 *
 * @param[in] p_args     Pointer to block media callback structure.
 **********************************************************************************************************************/
void rm_filex_block_media_memory_callback (rm_block_media_callback_args_t * p_args)
{
    /* Pass the event up to the application layer. */
    rm_filex_block_media_instance_ctrl_t * p_instance_ctrl = (rm_filex_block_media_instance_ctrl_t *) p_args->p_context;

    if ((RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED | RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED |
         RM_BLOCK_MEDIA_EVENT_MEDIA_SUSPEND | RM_BLOCK_MEDIA_EVENT_MEDIA_RESUME) & p_args->event)
    {
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            /* Pass insertion and removal events up to the application. */
            rm_filex_block_media_callback_args_t args;
            args.event     = p_args->event;
            args.p_context = p_args->p_context;
            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }

    if ((RM_BLOCK_MEDIA_EVENT_POLL_STATUS) &p_args->event)
    {
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            xPSR_Type xpsr;
            xpsr.w = __get_xPSR();

            /* Check if POLL_STATUS is from an ISR or a THREAD.
             * If from an ISR, handling is done later with WAIT_END event. */
            if (0 == xpsr.b.ISR)
            {
                /* Called from a thread, pass POLL_STATUS to application. */
                rm_filex_block_media_callback_args_t args;
                args.event     = RM_BLOCK_MEDIA_EVENT_POLL_STATUS;
                args.p_context = p_args->p_context;
                p_instance_ctrl->p_cfg->p_callback(&args);

                p_instance_ctrl->event_ready = true;

                return;
            }
        }
    }

    if ((RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE | RM_BLOCK_MEDIA_EVENT_POLL_STATUS |
         RM_BLOCK_MEDIA_EVENT_ERROR) & p_args->event)
    {
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            rm_filex_block_media_callback_args_t args;
            args.event     = RM_BLOCK_MEDIA_EVENT_WAIT_END;
            args.p_context = p_args->p_context;
            p_instance_ctrl->p_cfg->p_callback(&args);
        }

        p_instance_ctrl->last_event |= p_args->event;
        p_instance_ctrl->event_ready = true;
    }
}

/*******************************************************************************************************************//**
 * Writes blocks of data to the specified device memory address.
 *
 * @param[in]   p_instance_ctrl    Control block for the FileX Block Media instance.
 * @param[in]   p_src_address      Address to read the data to be written.
 * @param[in]   block_address      Block address to write the data to.
 * @param[in]   num_blocks         Number of blocks of data to write.
 *
 * @retval     FSP_SUCCESS         Write finished successfully.
 * @retval     FSP_ERR_INTERNAL    Error reported by lower layer driver callback.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref rm_block_media_api_t::write
 **********************************************************************************************************************/
static fsp_err_t rm_filex_block_media_write (rm_filex_block_media_instance_ctrl_t * p_instance_ctrl,
                                             uint8_t                              * p_src_address,
                                             uint32_t                               block_address,
                                             uint32_t                               num_blocks)
{
    fsp_err_t err;
    rm_block_media_instance_t * p_block_media = p_instance_ctrl->p_cfg->p_lower_lvl_block_media;

    p_instance_ctrl->event_ready = false;

    err = p_block_media->p_api->write(p_block_media->p_ctrl, p_src_address, block_address, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = rm_filex_block_media_wait_event(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads blocks of data from the specified memory device address to the location specified by the caller.
 *
 * @param[in]   p_instance_ctrl     Control block for the FileX Block Media instance.
 * @param[out]  p_dest_address      Destination to read the data into.
 * @param[in]   block_address       Block address to read the data from.
 * @param[in]   num_blocks          Number of blocks of data to read.
 *
 * @retval     FSP_SUCCESS          Data read successfully.
 * @retval     FSP_ERR_INTERNAL     Error reported by lower layer driver callback.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref rm_block_media_api_t::read
 **********************************************************************************************************************/
static fsp_err_t rm_filex_block_media_read (rm_filex_block_media_instance_ctrl_t * p_instance_ctrl,
                                            uint8_t                              * p_dest_address,
                                            uint32_t                               block_address,
                                            uint32_t                               num_blocks)
{
    fsp_err_t err;
    rm_block_media_instance_t * p_block_media = p_instance_ctrl->p_cfg->p_lower_lvl_block_media;

    p_instance_ctrl->event_ready = false;

    err = p_block_media->p_api->read(p_block_media->p_ctrl, p_dest_address, block_address, num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = rm_filex_block_media_wait_event(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Waits for block media transfer complete event.
 *
 * @param[in] p_instance_ctrl          Pointer to instance control structure.
 *
 * @retval     FSP_SUCCESS             Media device no longer busy.
 * @retval     FSP_ERR_INTERNAL        Error reported by lower layer driver callback.
 **********************************************************************************************************************/
static fsp_err_t rm_filex_block_media_wait_event (rm_filex_block_media_instance_ctrl_t * p_instance_ctrl)
{
    rm_block_media_status_t     status;
    rm_block_media_instance_t * p_block_media = p_instance_ctrl->p_cfg->p_lower_lvl_block_media;

    while (!p_instance_ctrl->event_ready)
    {
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            /* Signal wait to user through callback */
            rm_filex_block_media_callback_args_t args;
            args.event     = RM_BLOCK_MEDIA_EVENT_WAIT;
            args.p_context = p_instance_ctrl;
            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }

    FSP_ERROR_RETURN(0U == (RM_BLOCK_MEDIA_EVENT_ERROR & p_instance_ctrl->last_event), FSP_ERR_INTERNAL);

    if (RM_BLOCK_MEDIA_EVENT_POLL_STATUS & p_instance_ctrl->last_event)
    {
        do
        {
            fsp_err_t err = p_block_media->p_api->statusGet(p_block_media->p_ctrl, &status);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
            if (!status.busy)
            {
                break;
            }

            if (NULL != p_instance_ctrl->p_cfg->p_callback)
            {
                /* Signal wait to user through callback */
                rm_filex_block_media_callback_args_t args;
                args.event     = RM_BLOCK_MEDIA_EVENT_POLL_STATUS;
                args.p_context = p_instance_ctrl;
                p_instance_ctrl->p_cfg->p_callback(&args);
            }
        } while (true);
    }

    return FSP_SUCCESS;
}
