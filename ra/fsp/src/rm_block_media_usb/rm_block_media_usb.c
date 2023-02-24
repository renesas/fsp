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
#include "rm_block_media_usb.h"
#include "rm_block_media_usb_cfg.h"
#include "r_usb_hmsc.h"
#if (BSP_CFG_RTOS == 0)
 #include "r_usb_typedef.h"
 #include "r_usb_extern.h"
 #include "../r_usb_hmsc/src/inc/r_usb_hmsc_driver.h"
#endif                                 /* (BSP_CFG_RTOS == 0) */

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "MEUB" in ASCII. */
#define RM_BLOCK_MEDIA_USB_OPEN                      (0x4D455542)

/* Initial device address. */
#define RM_BLOCK_MEDIA_USB_INVALID_DEVICE_ADDRESS    (0xFF)

/* Command complete */
#define RM_BLOCK_MEDIA_USB_COMMAND_COMPLETE          (1)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (BSP_CFG_RTOS == 2)
void rm_block_media_usb_callback(usb_event_info_t * p_usb_event_info, usb_hdl_t current_task, usb_onoff_t usb_state);

#endif
#if (BSP_CFG_RTOS == 0)
static void rm_block_media_usb_waitloop(void);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
const uint8_t g_block_media_usb_erase_data[512] __attribute__((__aligned__(4))) = {0};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const rm_block_media_api_t g_rm_block_media_on_usb =
{
    .open        = RM_BLOCK_MEDIA_USB_Open,
    .mediaInit   = RM_BLOCK_MEDIA_USB_MediaInit,
    .read        = RM_BLOCK_MEDIA_USB_Read,
    .write       = RM_BLOCK_MEDIA_USB_Write,
    .erase       = RM_BLOCK_MEDIA_USB_Erase,
    .callbackSet = RM_BLOCK_MEDIA_USB_CallbackSet,
    .infoGet     = RM_BLOCK_MEDIA_USB_InfoGet,
    .statusGet   = RM_BLOCK_MEDIA_USB_StatusGet,
    .close       = RM_BLOCK_MEDIA_USB_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_BLOCK_MEDIA_USB
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
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_Open (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_cfg_t const * const p_cfg)
{
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
#endif

    rm_block_media_usb_extended_cfg_t * p_extended_cfg = (rm_block_media_usb_extended_cfg_t *) p_cfg->p_extend;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg);
    FSP_ASSERT(NULL != p_extended_cfg->p_usb);
#endif

    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    p_instance_ctrl->p_cfg = p_cfg;

    /* Open the underlying driver. */
    usb_instance_t * p_usb_instance = (usb_instance_t *) p_extended_cfg->p_usb;

    fsp_err_t err;
    err = p_usb_instance->p_api->open(p_usb_instance->p_ctrl, p_usb_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    p_instance_ctrl->device_address = RM_BLOCK_MEDIA_USB_INVALID_DEVICE_ADDRESS;

#if 2 == BSP_CFG_RTOS

    /* Event group create */
    p_instance_ctrl->event_group = xEventGroupCreate();
#endif

    /* This module is now open. */
    p_instance_ctrl->initialized = false;
    p_instance_ctrl->open        = RM_BLOCK_MEDIA_USB_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the USB device.
 *
 * Implements @ref rm_block_media_api_t::mediaInit().
 *
 * @retval     FSP_SUCCESS               Module is initialized and ready to access the memory device.
 * @retval     FSP_ERR_ASSERTION         An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN          Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_MediaInit (rm_block_media_ctrl_t * const p_ctrl)
{
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_block_media_usb_extended_cfg_t * p_extended_cfg =
        (rm_block_media_usb_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg->p_usb);
#endif

    usb_instance_t * p_usb = (usb_instance_t *) p_extended_cfg->p_usb;
    fsp_err_t        err   = R_USB_HMSC_StorageCommand(p_usb->p_ctrl,
                                                       p_instance_ctrl->p_read_buffer,
                                                       USB_ATAPI_READ_CAPACITY,
                                                       p_instance_ctrl->device_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if 2 == BSP_CFG_RTOS
    xEventGroupWaitBits(p_instance_ctrl->event_group,
                        RM_BLOCK_MEDIA_USB_COMMAND_COMPLETE,
                        pdTRUE,
                        pdFALSE,
                        portMAX_DELAY);
#else
    usb_event_info_t event_info;
    usb_status_t     event;
    while (1)
    {
        R_USB_EventGet(&event_info, &event);
        if (USB_STATUS_MSC_CMD_COMPLETE == event)
        {
            break;
        }
    }
#endif

    p_instance_ctrl->sector_count      = __REV(*(uint32_t *) &p_instance_ctrl->p_read_buffer[0]) + 1;
    p_instance_ctrl->sector_size_bytes = __REV(*(uint32_t *) &p_instance_ctrl->p_read_buffer[4]);

    p_instance_ctrl->initialized = true;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads data from an USB device. Implements @ref rm_block_media_api_t::read().
 *
 * This function blocks until the data is read into the destination buffer.
 *
 * @retval     FSP_SUCCESS                   Data read successfully.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 * @retval     FSP_ERR_USB_FAILED            The message could not received completed successfully.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_Read (rm_block_media_ctrl_t * const p_ctrl,
                                   uint8_t * const               p_dest_address,
                                   uint32_t const                block_address,
                                   uint32_t const                num_blocks)
{
#if BSP_CFG_RTOS == 0
    uint16_t    data;
    usb_utr_t * p_mess;
#endif                                 /* BSP_CFG_RTOS == 0 */
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_dest_address);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_usb_extended_cfg_t * p_extended_cfg =
        (rm_block_media_usb_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg->p_usb);
#endif

    usb_instance_t * p_usb = (usb_instance_t *) p_extended_cfg->p_usb;

    /* Call the underlying driver. */
    uint8_t   p_drive;
    fsp_err_t err = R_USB_HMSC_DriveNumberGet(p_usb->p_ctrl, &p_drive, p_instance_ctrl->device_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = R_USB_HMSC_StorageReadSector(p_drive, p_dest_address, block_address, (uint16_t) num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS == 0

    /* Wait USB read sequence(READ10) */
    do
    {
        /* Check Detach */
        data = usb_hmsc_get_dev_sts(p_drive);
        rm_block_media_usb_waitloop();                                           /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
    } while ((err != USB_OK) && (data != USB_FALSE));

    if (err == USB_OK)
    {
        /* Complete R_USB_HmscStrgReadSector() */
        err = p_mess->result;          /* Set result for R_USB_HmscStrgReadSector() */
        USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
    }
    else
    {
        /* Device detach */
        rm_block_media_usb_waitloop();                                           /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
        if (USB_OK == err)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
        }

        err = USB_ERROR;
    }

    if (err != USB_OK)
    {
        return FSP_ERR_USB_FAILED;
    }
#endif                                 /* BSP_CFG_RTOS == 0 */

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    args.p_context = p_instance_ctrl->p_cfg->p_context;
    args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
    p_instance_ctrl->p_cfg->p_callback(&args);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes data to an USB device. Implements @ref rm_block_media_api_t::write().
 *
 * This function blocks until the write operation completes.
 *
 * @retval     FSP_SUCCESS                   Write finished successfully.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 * @retval     FSP_ERR_USB_FAILED            The message could not received completed successfully.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_Write (rm_block_media_ctrl_t * const p_ctrl,
                                    uint8_t const * const         p_src_address,
                                    uint32_t const                block_address,
                                    uint32_t const                num_blocks)
{
#if BSP_CFG_RTOS == 0
    uint16_t    data;
    usb_utr_t * p_mess;
#endif                                 /* BSP_CFG_RTOS == 0 */
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_src_address);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_usb_extended_cfg_t * p_extended_cfg =
        (rm_block_media_usb_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg->p_usb);
#endif

    usb_instance_t * p_usb = (usb_instance_t *) p_extended_cfg->p_usb;

    /* Call the underlying driver. */
    uint8_t   p_drive;
    fsp_err_t err = R_USB_HMSC_DriveNumberGet(p_usb->p_ctrl, &p_drive, p_instance_ctrl->device_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = R_USB_HMSC_StorageWriteSector(p_drive, p_src_address, block_address, (uint16_t) num_blocks);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS == 0

    /* Wait USB write sequence(WRITE10) */
    do
    {
        /* Check Detach */
        data = usb_hmsc_get_dev_sts(p_drive);
        rm_block_media_usb_waitloop();                                           /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
    } while ((err != USB_OK) && (data != USB_FALSE));

    if (err == USB_OK)
    {
        /* Complete R_USB_HmscStrgReadSector() */
        err = p_mess->result;          /* Set result for R_USB_HmscStrgReadSector() */
        USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
    }
    else
    {
        /* Device detach */
        rm_block_media_usb_waitloop();                                           /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
        if (USB_OK == err)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
        }

        err = USB_ERROR;
    }

    if (err != USB_OK)
    {
        return FSP_ERR_USB_FAILED;
    }
#endif                                 /* BSP_CFG_RTOS == 0 */

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    args.p_context = p_instance_ctrl->p_cfg->p_context;
    args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
    p_instance_ctrl->p_cfg->p_callback(&args);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erases sectors of an USB device. Implements @ref rm_block_media_api_t::erase().
 *
 * This function blocks until erase is complete.
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_Erase (rm_block_media_ctrl_t * const p_ctrl,
                                    uint32_t const                block_address,
                                    uint32_t const                num_blocks)
{
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_usb_extended_cfg_t * p_extended_cfg =
        (rm_block_media_usb_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg->p_usb);
#endif

    usb_instance_t * p_usb = (usb_instance_t *) p_extended_cfg->p_usb;

    /* Call the underlying driver. */
    uint8_t   p_drive;
    fsp_err_t err = R_USB_HMSC_DriveNumberGet(p_usb->p_ctrl, &p_drive, p_instance_ctrl->device_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    for (uint32_t i = 0; i < num_blocks; i++)
    {
        err = R_USB_HMSC_StorageWriteSector(p_drive, &g_block_media_usb_erase_data[0], block_address + i, 1U);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    args.p_context = p_instance_ctrl->p_cfg->p_context;
    args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
    p_instance_ctrl->p_cfg->p_callback(&args);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref rm_block_media_api_t::callbackSet.
 *
 * @note This function is currently unsupported for Block Media over USB.
 *
 * @retval  FSP_ERR_UNSUPPORTED          CallbackSet is not currently supported for Block Media over USB.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_CallbackSet (rm_block_media_ctrl_t * const p_ctrl,
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

/*******************************************************************************************************************//**
 * Provides driver status.  Implements @ref rm_block_media_api_t::statusGet().
 *
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 * @retval     FSP_ERR_NOT_INITIALIZED       Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_StatusGet (rm_block_media_ctrl_t * const   p_api_ctrl,
                                        rm_block_media_status_t * const p_status)
{
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_api_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    rm_block_media_usb_extended_cfg_t * p_extended_cfg =
        (rm_block_media_usb_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg->p_usb);
#endif

    usb_instance_t * p_usb = (usb_instance_t *) p_extended_cfg->p_usb;

    /* Call the underlying driver. */
    usb_info_t status;
    fsp_err_t  err = p_usb->p_api->infoGet(p_usb->p_ctrl, &status, p_instance_ctrl->device_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_status->media_inserted = (USB_STATUS_DETACH != status.device_status);
    p_status->initialized    = p_instance_ctrl->initialized;

    /* USB does not have busy status. */
    p_status->busy = false;

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
fsp_err_t RM_BLOCK_MEDIA_USB_InfoGet (rm_block_media_ctrl_t * const p_ctrl, rm_block_media_info_t * const p_info)
{
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    p_info->sector_size_bytes = p_instance_ctrl->sector_size_bytes;
    p_info->num_sectors       = p_instance_ctrl->sector_count;
    p_info->reentrant         = false;
    p_info->write_protected   = false;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes an open USB device.  Implements @ref rm_block_media_api_t::close().
 *
 * @retval     FSP_SUCCESS                   Successful close.
 * @retval     FSP_ERR_ASSERTION             An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_USB_Close (rm_block_media_ctrl_t * const p_ctrl)
{
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg->p_extend);
#endif

    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    rm_block_media_usb_extended_cfg_t * p_extended_cfg =
        (rm_block_media_usb_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg->p_usb);
#endif

    usb_instance_t * p_usb = (usb_instance_t *) p_extended_cfg->p_usb;

#if 2 == BSP_CFG_RTOS

    /* Event group delete */
    vEventGroupDelete(p_instance_ctrl->event_group);
#endif

    /* Close the underlying driver. */
    fsp_err_t err = p_usb->p_api->close(p_usb->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLOCK_MEDIA_USB)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Passes callback event from the lower layer driver to the user.
 *
 * @param[in] p_usb_event_info              USB callback arguments.
 * @param[in] current_task                      USB callback arguments.
 * @param[in] usb_state                     USB callback arguments.
 **********************************************************************************************************************/
#if BSP_CFG_RTOS == 2
void rm_block_media_usb_callback (usb_event_info_t * p_usb_event_info, usb_hdl_t current_task, usb_onoff_t usb_state)
{
    FSP_PARAMETER_NOT_USED(current_task);
    FSP_PARAMETER_NOT_USED(usb_state);

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    rm_block_media_usb_instance_ctrl_t * p_instance_ctrl = p_usb_event_info->p_context;
    args.p_context = p_instance_ctrl->p_cfg->p_context;

    switch (p_usb_event_info->event)
    {
        case USB_STATUS_CONFIGURED:
        {
            p_instance_ctrl->device_address = p_usb_event_info->device_address;
            args.event = RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED;
            break;
        }

        case USB_STATUS_SUSPEND:
        {
            args.event = RM_BLOCK_MEDIA_EVENT_MEDIA_SUSPEND;
            break;
        }

        case USB_STATUS_RESUME:
        {
            args.event = RM_BLOCK_MEDIA_EVENT_MEDIA_RESUME;
            break;
        }

        case USB_STATUS_DETACH:
        {
            p_instance_ctrl->device_address = RM_BLOCK_MEDIA_USB_INVALID_DEVICE_ADDRESS;
            p_instance_ctrl->initialized    = false;
            args.event = RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED;

            break;
        }

        case USB_STATUS_MSC_CMD_COMPLETE:
        {
            xEventGroupSetBits(p_instance_ctrl->event_group, RM_BLOCK_MEDIA_USB_COMMAND_COMPLETE);
            break;
        }

        default:
        {
            break;
        }
    }

    if (args.event)
    {
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }
}

#endif

#if BSP_CFG_RTOS == 0

/******************************************************************************
 * Function Name   : rm_block_media_usb_waitloop
 * Description     : wait loop function
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void rm_block_media_usb_waitloop (void)
{
    if (USB_FLGSET == usb_cstd_check_schedule())
    {
        usb_hstd_hcd_task((usb_vp_int_t) 0);
        usb_hstd_mgr_task((usb_vp_int_t) 0);

        // usb_hhub_task((usb_vp_int_t) 0);
        usb_hmsc_task();               /* HMSC Task */
    }

    usb_cstd_scheduler();
}

#endif                                 /* BSP_CFG_RTOS == 0 */
