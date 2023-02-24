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
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include <stdint.h>
#include <stddef.h>

#include <r_usb_basic.h>
#include "r_usb_basic_api.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_reg_access.h"

#include "inc/r_usb_pmsc_driver.h"
#include "inc/r_usb_patapi.h"
#include "rm_block_media_api.h"

#define USB_VALUE_MASK_FF_ULH             (0xFFUL)
#define USB_VALUE_MASK_FF_UH              (0xFFU)
#define USB_FAT_TOTAL_SECTOR_INDEX        (0x20)
#define USB_FAT_FILE_SYSTEM_TYPE_INDEX    (0x36)
#define USB_FAT_SIGNATURE_INDEX           (0x1fe)

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
void        r_usb_pmsc_block_media_event_callback(rm_block_media_callback_args_t * p_args);
static void r_usb_pmsc_block_media_operation_event(void);
static void r_usb_pmsc_memory_wait_for_device(void);

volatile bool g_card_inserted                 = false;
volatile bool g_blockmedia_complete_event     = false;
volatile bool g_blockmedia_poll_status_events = false;
volatile bool g_status_busy = false;

uint32_t g_media_sector_size_bytes;
uint32_t g_media_total_sector;
rm_block_media_instance_t * gp_block_media_instance;

/*
 * Media driver list
 * This array is defined to hold a set of pointers to media_driver_t type structures.
 * This provides a means to manage multiple media device drivers in the same system.
 * An individual media driver is accessed by means of indexing into this array by use of the logical unit number (lun)
 * parameter of the media driver API function call.
 * The maximum number of drivers loaded at any given time is limited by the user configurable value MAX_NUM_LUNS.
 * This list may contain duplicate pointers to the same driver in order to support multiple media devices of the same type.
 */

#if (USB_UT_MODE == 0)

/*******************************************************************************************************************//**
 * Function Name: r_usb_pmsc_media_initialize
 * @brief   This function initializes data structures and variables that are used by the media device to support its operation for the first time.
 * Arguments    : void const * p_context
 * @retval FSP_SUCCESS        Success
 * @retval FSP_ERR_USB_FAILED The function could not be completed successfully.
 ***********************************************************************************************************************/
fsp_err_t r_usb_pmsc_media_initialize (void const * p_context)
{
    fsp_err_t               err_code = FSP_ERR_USB_FAILED;
    rm_block_media_status_t status;
    rm_block_media_info_t   info;

    if (USB_NULL != p_context)
    {
        gp_block_media_instance = (rm_block_media_instance_t *) p_context;
        err_code                = gp_block_media_instance->p_api->open(gp_block_media_instance->p_ctrl,
                                                                       gp_block_media_instance->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err_code, FSP_ERR_USB_FAILED);
        err_code = gp_block_media_instance->p_api->mediaInit(gp_block_media_instance->p_ctrl);
        if (FSP_SUCCESS == err_code)
        {
            err_code = gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status);
            if (FSP_SUCCESS == err_code)
            {
                if ((status.initialized == true) && (status.busy == false) && (status.media_inserted == true))
                {
                    err_code = gp_block_media_instance->p_api->infoGet(gp_block_media_instance->p_ctrl, &info);
                    if (FSP_SUCCESS == err_code)
                    {
                        g_media_total_sector      = info.num_sectors;
                        g_media_sector_size_bytes = info.sector_size_bytes;
                    }
                    else
                    {
                        gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
                        err_code = FSP_ERR_USB_FAILED;
                    }
                }
                else
                {
                    gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
                    err_code = FSP_ERR_USB_FAILED;
                }
            }
            else
            {
                gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
                err_code = FSP_ERR_USB_FAILED;
            }
        }
        else
        {
            gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);
            err_code = FSP_ERR_USB_FAILED;
        }
    }

    return err_code;
}                                      /* End of function R_USB_media_initialize() */

/***********************************************************************************************************************
 * Function Name: r_usb_pmsc_media_close
 * Description  : Close the media.
 * Arguments    : none
 * Return value : result -
 *                    FSP_SUCCESS:         Success
 *                    FSP_ERR_USB_FAILED:  The function could not be completed successfully.
 ***********************************************************************************************************************/
fsp_err_t r_usb_pmsc_media_close (void)
{
    fsp_err_t err_code;

    err_code = gp_block_media_instance->p_api->close(gp_block_media_instance->p_ctrl);

    return err_code;
}                                      /* End of function R_USB_media_close() */

#endif /* (USB_UT_MODE == 0) */

/***********************************************************************************************************************//**
 * Function Name: r_usb_pmsc_media_read
 * Description  : This function reads data from a specified location of the
 *                storage medium
 * Arguments    : p_rbuffer -
 *                    Pointer to the read data buffer.
 *              : start_block -
 *                    Start block number.
 *              : block_count -
 *                    Number of blocks to read.
 * @retval FSP_SUCCESS Success
 ***********************************************************************************************************************/
fsp_err_t r_usb_pmsc_media_read (uint8_t * const p_rbuffer, uint32_t const start_block, uint8_t const block_count)
{
    fsp_err_t               err_code;
    rm_block_media_status_t status;

    err_code = gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err_code, err_code);
    if ((status.initialized == true) && (status.busy == false) && (status.media_inserted == true))
    {
        err_code = gp_block_media_instance->p_api->read(gp_block_media_instance->p_ctrl,
                                                        p_rbuffer,
                                                        start_block,
                                                        block_count);
        if (err_code == FSP_SUCCESS)
        {
            r_usb_pmsc_block_media_operation_event();
        }
    }
    else
    {
        g_status_busy = true;
    }

    return err_code;
}                                      /* End of function R_USB_media_read() */

/********************************************************************************************************************//**
 * Function Name: r_usb_pmsc_media_write
 * Description  : This function writes data to a specified location of the storage medium
 * Arguments    : p_wbuffer -
 *                    Pointer to the write data buffer.
 *              : start_block -
 *                    Start block number.
 *              : block_count -
 *                    Number of blocks to write.
 * @retval FSP_SUCCESS Success
 ***********************************************************************************************************************/
fsp_err_t r_usb_pmsc_media_write (uint8_t const * const p_wbuffer, uint32_t const start_block,
                                  uint8_t const block_count)
{
    fsp_err_t               err_code;
    rm_block_media_status_t status;

    err_code = gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err_code, err_code);
    if ((status.initialized == true) && (status.busy == false) && (status.media_inserted == true))
    {
        err_code =
            gp_block_media_instance->p_api->write(gp_block_media_instance->p_ctrl,
                                                  p_wbuffer,
                                                  start_block,
                                                  (uint32_t) block_count);
        if (err_code == FSP_SUCCESS)
        {
            r_usb_pmsc_block_media_operation_event();
        }
    }
    else
    {
        g_status_busy = true;
    }

    return err_code;
}                                      /* End of function R_USB_media_write() */

/***********************************************************************************************************************
 * Function Name: r_usb_pmsc_media_ioctl
 * Description  : This function provides a generalized means to pass special
 *                command and control instructions to the media driver and for
 *                the driver to return information.
 * Arguments    : ioctl_cmd -
 *                    Control command code.
 *              : ioctl_data -
 *                    Data transfer buffer
 * Return value : non
 ***********************************************************************************************************************/
void r_usb_pmsc_media_ioctl (usb_ioctl_cmd_t ioctl_cmd, uint32_t * ioctl_data)
{
    rm_block_media_info_t info;

    switch (ioctl_cmd)
    {
        case USB_MEDIA_IOCTL_GET_NUM_BLOCKS:
        {
            *ioctl_data = g_media_total_sector;
            break;
        }

        case USB_MEDIA_IOCTL_GET_SECTOR_SIZE:
        case USB_MEDIA_IOCTL_GET_BLOCK_SIZE:
        {
            /* Get the size of the logical block in the RAM disk */
            *ioctl_data = g_media_sector_size_bytes;
            break;
        }

        case USB_MEDIA_IOCTL_SYNC:
        {
            /* TODO: Flush write cache if necessary */
            break;
        }

        case USB_MEDIA_IOCTL_GET_WRITE_PROTECT_INFO:
        {
            gp_block_media_instance->p_api->infoGet(gp_block_media_instance->p_ctrl, &info);
            *ioctl_data = (uint32_t) info.write_protected;
            break;
        }

        default:
        {
            break;
        }
    }
}                                      /* End of function R_USB_media_ioctl() */

/* The callback is called when a card detection event occurs if the card detection interrupt is enabled. */
void r_usb_pmsc_block_media_event_callback (rm_block_media_callback_args_t * p_args)
{
    if (RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED == p_args->event)
    {
        g_card_inserted = true;
    }

    if (RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED == p_args->event)
    {
        g_card_inserted = false;
    }

    if (RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE == p_args->event)
    {
        g_blockmedia_complete_event = true;
    }

    if (RM_BLOCK_MEDIA_EVENT_POLL_STATUS & p_args->event)
    {
        g_blockmedia_poll_status_events = true;
    }
}

static void r_usb_pmsc_block_media_operation_event (void)
{
    uint32_t timeout = UINT32_MAX;
    while (timeout > 0)
    {
        timeout--;
        if (g_blockmedia_complete_event == true)
        {
            break;
        }

        if (g_blockmedia_poll_status_events == true)
        {
            r_usb_pmsc_memory_wait_for_device();
            break;
        }
    }

    g_blockmedia_complete_event = false;
}

static void r_usb_pmsc_memory_wait_for_device (void)
{
    rm_block_media_status_t status;
    memset(&status, 0U, sizeof(status));
    uint32_t timeout = UINT32_MAX;
    do
    {
        timeout--;
        if (0U == timeout)
        {
            break;
        }

        gp_block_media_instance->p_api->statusGet(gp_block_media_instance->p_ctrl, &status);
    } while (status.busy);

    g_blockmedia_complete_event     = false;
    g_blockmedia_poll_status_events = false;
}

/***********************************************************************************************************************
 * End Of File
 ***********************************************************************************************************************/
