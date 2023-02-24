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
#include "rm_filex_levelx_nor.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "FXLX" in ASCII, used to determine if driver is open. */
#define RM_FILEX_LEVELX_NOR_OPEN                  (0x46584C58ULL)

#define RM_FILEX_LEVELX_NOR_LEVELX_SECTOR_SIZE    (512)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static UINT      rm_filex_levelx_nor_driver_request_handler(FX_MEDIA * p_fx_media);
void             rm_filex_levelx_nor_spi_callback(rm_levelx_nor_spi_callback_args_t * p_args);
static fsp_err_t rm_filex_levelx_nor_open(rm_filex_levelx_nor_instance_ctrl_t * const p_ctrl,
                                          rm_filex_levelx_nor_cfg_t const * const     p_cfg);

/* FileX utility functions */
extern UINT _fx_partition_offset_calculate(void  * partition_sector,
                                           UINT    partition,
                                           ULONG * partition_start,
                                           ULONG * partition_size);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_FILEX_LEVELX_NOR
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Access LevelX NOR device functions open, close, read, write and control.
 *
 * The RM_FILEX_LEVELX_NOR_DeviceDriver function is called from the FileX file system driver and issues requests
 * to a LevelX NOR device through the LevelX API.
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
void RM_FILEX_LEVELX_NOR_DeviceDriver (FX_MEDIA * p_fx_media)
{
#if  (RM_FILEX_LEVELX_NOR_CFG_PARAM_CHECKING_ENABLE)

    /* Validate FX_MEDIA::fx_media_driver_info and update FX_MEDIA::fx_media_driver_status to FX_PTR_ERROR in case of any failure. */
    if (NULL == p_fx_media->fx_media_driver_info)
    {
        p_fx_media->fx_media_driver_status = FX_IO_ERROR;

        return;
    }
#endif

    /* Pass control to request handler, which is responsible for setting FX_MEDIA::fx_media_driver_status in-case of any failure. */
    p_fx_media->fx_media_driver_status = rm_filex_levelx_nor_driver_request_handler(p_fx_media);
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_FILEX_LEVELX_NOR)
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * @brief      Handles the FileX driver request
 * @param      p_fx_media      The pointer to FileX media
 *
 * @retval     FX_SUCCESS           Driver request fulfilled.
 * @retval     FX_MEDIA_INVALID     Not a valid boot record
 * @retval     FX_IO_ERROR          An error has occurred with the lower level LevelX driver
 *
 * @return See functions called by this function for other possible return codes.
 *********************************************************************************************************************/
static UINT rm_filex_levelx_nor_driver_request_handler (FX_MEDIA * p_fx_media)
{
    UINT    err;
    UCHAR * p_buffer;
    ULONG   logical_sector;

    rm_filex_levelx_nor_instance_t * p_filex_levelx_nor_instance =
        (rm_filex_levelx_nor_instance_t *) p_fx_media->fx_media_driver_info;

    rm_filex_levelx_nor_instance_ctrl_t * p_filex_levelx_nor_ctrl = p_filex_levelx_nor_instance->p_ctrl;
    rm_filex_levelx_nor_cfg_t const     * p_filex_levelx_nor_cfg  = p_filex_levelx_nor_instance->p_cfg;

    /* Process the driver request specified in the media control block. */
    switch (p_fx_media->fx_media_driver_request)
    {
        /* FX_DRIVER_READ
         *  FileX reads one or more sectors into memory by issuing a read request to the I/O driver. */
        case (UINT) FX_DRIVER_READ:
        {
            logical_sector = p_fx_media->fx_media_driver_logical_sector;
            p_buffer       = p_fx_media->fx_media_driver_buffer;

            for (ULONG i = 0; i < p_fx_media->fx_media_driver_sectors; i++)
            {
                err = lx_nor_flash_sector_read(p_filex_levelx_nor_cfg->p_nor_flash, logical_sector, p_buffer);

                if (LX_SUCCESS != err)
                {
                    return FX_IO_ERROR;
                }

                /* Move to the next entries. */
                logical_sector++;
                p_buffer += RM_FILEX_LEVELX_NOR_LEVELX_SECTOR_SIZE;
            }

            break;
        }

        /* FX_DRIVER_WRITE
         *  FileX writes one or more sectors to the physical media by issuing a write request to the I/O driver. */
        case (UINT) FX_DRIVER_WRITE:
        {
            logical_sector = p_fx_media->fx_media_driver_logical_sector;
            p_buffer       = p_fx_media->fx_media_driver_buffer;

            for (ULONG i = 0; i < p_fx_media->fx_media_driver_sectors; i++)
            {
                err = lx_nor_flash_sector_write(p_filex_levelx_nor_cfg->p_nor_flash, logical_sector, p_buffer);

                if (LX_SUCCESS != err)
                {
                    return FX_IO_ERROR;
                }

                /* Move to the next entries. */
                logical_sector++;
                p_buffer += RM_FILEX_LEVELX_NOR_LEVELX_SECTOR_SIZE;
            }

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
         *  consecutive sectors become free. */
        case (UINT) FX_DRIVER_RELEASE_SECTORS:
        {
            logical_sector = p_fx_media->fx_media_driver_logical_sector;

            /* Release sectors. */
            for (ULONG i = 0; i < p_fx_media->fx_media_driver_sectors; i++)
            {
                err = lx_nor_flash_sector_release(p_filex_levelx_nor_cfg->p_nor_flash, logical_sector);

                /* Determine if the sector release was successful.  */
                if (LX_SUCCESS != err)
                {
                    return FX_IO_ERROR;
                }

                /* Move to the next entries. */
                logical_sector++;
            }

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
         *  made by FileX and is done from within the fx_media_open service. */
        case (UINT) FX_DRIVER_INIT:
        {
            fsp_err_t fsp_err;

            /* With flash wear leveling, FileX should tell wear leveling when sectors
             * are no longer in use. */
            p_fx_media->fx_media_driver_free_sector_update = FX_TRUE;

            fsp_err = rm_filex_levelx_nor_open(p_filex_levelx_nor_ctrl, p_filex_levelx_nor_instance->p_cfg);

            if (FSP_SUCCESS != fsp_err)
            {
                return FX_IO_ERROR;
            }

            err = lx_nor_flash_open(p_filex_levelx_nor_cfg->p_nor_flash,
                                    p_filex_levelx_nor_cfg->p_nor_flash_name,
                                    p_filex_levelx_nor_cfg->nor_driver_initialize);

            if (err != LX_SUCCESS)
            {
                return FX_IO_ERROR;
            }

            break;
        }

        /* FX_DRIVER_UNINIT
         *  FileX uses the uninit command to close the media. This is typically called on fx_media_close. */
        case (UINT) FX_DRIVER_UNINIT:
        {
            err = lx_nor_flash_close(p_filex_levelx_nor_cfg->p_nor_flash);

            p_filex_levelx_nor_cfg->close();

            /* Determine if the flash close was successful.  */
            if (LX_SUCCESS != err)
            {
                return FX_IO_ERROR;
            }

            break;
        }

        /* FX_DRIVER_BOOT_READ
         *  Instead of using a standard read request, FileX makes a specific request to read the media's boot
         *  sector. */
        case (UINT) FX_DRIVER_BOOT_READ:
        {
            p_buffer = p_fx_media->fx_media_driver_buffer;

            err = lx_nor_flash_sector_read(p_filex_levelx_nor_cfg->p_nor_flash, 0, p_buffer);

            /* Determine if the boot read was successful. */
            if (LX_SUCCESS != err)
            {
                return FX_IO_ERROR;
            }

            /* Use _fx_partition_offset_calculate to read the boot record and check the signature. Partitions not supported for LevelX NOR. */
            err = _fx_partition_offset_calculate(p_buffer, 0, FX_NULL, FX_NULL);
            if (LX_SUCCESS != err)
            {
                return FX_MEDIA_INVALID;
            }

            break;
        }

        /* FX_DRIVER_BOOT_WRITE
         *  Instead of using a standard write request, FileX makes a specific request to write the media's boot
         *  sector. */
        case (UINT) FX_DRIVER_BOOT_WRITE:
        {
            p_buffer = p_fx_media->fx_media_driver_buffer;

            /* Write boot sector to NOR flash.  */
            err = lx_nor_flash_sector_write(p_filex_levelx_nor_cfg->p_nor_flash, 0, p_buffer);

            /* Determine if the boot write was successful. */
            if (LX_SUCCESS != err)
            {
                return FX_IO_ERROR;
            }

            break;
        }

        /* default
         *  Invalid driver request. */
        default:
        {
            return FX_IO_ERROR;
            break;
        }
    }

    return FX_SUCCESS;
}

/*******************************************************************************************************************//**
 * Notifies task of event completion.
 *
 * @param[in] p_args     Pointer to LevelX NOR SPI callback structure.
 **********************************************************************************************************************/
void rm_filex_levelx_nor_spi_callback (rm_levelx_nor_spi_callback_args_t * p_args)
{
    /* Pass the event up to the application layer. */
    rm_filex_levelx_nor_instance_ctrl_t * p_instance_ctrl = (rm_filex_levelx_nor_instance_ctrl_t *) p_args->p_context;
    rm_filex_levelx_nor_callback_args_t   args;

    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        args.event     = (rm_filex_levelx_nor_event_t) p_args->event;
        args.p_context = p_instance_ctrl->p_cfg->p_context;
        p_instance_ctrl->p_cfg->p_callback(&args);
    }
}

/*******************************************************************************************************************//**
 * Initializes callback and configuration for FileX LevelX NOR Driver
 *
 * @retval FSP_SUCCESS              Success.
 * @retval FSP_ERR_ASSERTION        An input parameter was invalid.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
static fsp_err_t rm_filex_levelx_nor_open (rm_filex_levelx_nor_instance_ctrl_t * const p_ctrl,
                                           rm_filex_levelx_nor_cfg_t const * const     p_cfg)
{
#if RM_FILEX_LEVELX_NOR_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->nor_driver_initialize);
    FSP_ASSERT(NULL != p_cfg->p_nor_flash);
    FSP_ASSERT(NULL != p_cfg->p_nor_flash_name);
    FSP_ASSERT(NULL != p_cfg->close);
#endif

    /* Initialize control structure. */
    p_ctrl->p_cfg = p_cfg;

    return FSP_SUCCESS;
}
