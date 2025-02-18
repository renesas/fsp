/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_block_media_usb.h"
#include "rm_block_media_usb_cfg.h"
#include "r_usb_hmsc.h"
#if (BSP_CFG_RTOS == 0)
 #include "../r_usb_basic/src/driver/inc/r_usb_typedef.h"
 #include "../r_usb_basic/src/driver/inc/r_usb_extern.h"
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
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * blockmedia_usb_prv_ns_callback)(rm_block_media_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile blockmedia_usb_prv_ns_callback)(rm_block_media_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (BSP_CFG_RTOS == 2)
void rm_block_media_usb_callback(usb_event_info_t * p_usb_event_info, usb_hdl_t current_task, usb_onoff_t usb_state);

#endif
#if (BSP_CFG_RTOS == 0)
static void rm_block_media_usb_waitloop(void);

#endif

static void rm_block_media_usb_call_callback(rm_block_media_usb_instance_ctrl_t * p_instance_ctrl,
                                             rm_block_media_callback_args_t     * p_callback_args);

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

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

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

    p_instance_ctrl->device_address = USB_DEVICEADDR; /* Temporary proccessing for TrustZone. */

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
    usb_er_t usb_err;

    /* Wait USB read sequence(READ10) */
    do
    {
        /* Check Detach */
        data = usb_hmsc_get_dev_sts(p_drive);
        rm_block_media_usb_waitloop();                                               /* Task Schedule */
        usb_err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
    } while ((usb_err != USB_OK) && (data != USB_FALSE));

    if (usb_err == USB_OK)
    {
        /* Complete R_USB_HmscStrgReadSector() */
        usb_err = p_mess->result;      /* Set result for R_USB_HmscStrgReadSector() */
        USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
    }
    else
    {
        /* Device detach */
        rm_block_media_usb_waitloop();                                               /* Task Schedule */
        usb_err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
        if (USB_OK == usb_err)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
        }

        usb_err = USB_ERROR;
    }

    if (usb_err != USB_OK)
    {
        return FSP_ERR_USB_FAILED;
    }
#endif                                 /* BSP_CFG_RTOS == 0 */

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    args.p_context = p_instance_ctrl->p_cfg->p_context;
    args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
    rm_block_media_usb_call_callback(p_instance_ctrl, &args);

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
    usb_er_t usb_err;

    /* Wait USB write sequence(WRITE10) */
    do
    {
        /* Check Detach */
        data = usb_hmsc_get_dev_sts(p_drive);
        rm_block_media_usb_waitloop();                                               /* Task Schedule */
        usb_err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
    } while ((usb_err != USB_OK) && (data != USB_FALSE));

    if (usb_err == USB_OK)
    {
        /* Complete R_USB_HmscStrgReadSector() */
        usb_err = p_mess->result;      /* Set result for R_USB_HmscStrgReadSector() */
        USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
    }
    else
    {
        /* Device detach */
        rm_block_media_usb_waitloop();                                               /* Task Schedule */
        usb_err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
        if (USB_OK == usb_err)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
        }

        usb_err = USB_ERROR;
    }

    if (usb_err != USB_OK)
    {
        return FSP_ERR_USB_FAILED;
    }
#endif                                 /* BSP_CFG_RTOS == 0 */

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    args.p_context = p_instance_ctrl->p_cfg->p_context;
    args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
    rm_block_media_usb_call_callback(p_instance_ctrl, &args);

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
#if BSP_CFG_RTOS == 0
    uint16_t    data;
    usb_utr_t * p_mess;
#endif                                 /* BSP_CFG_RTOS == 0 */
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

#if BSP_CFG_RTOS == 0
        usb_er_t usb_err;

        /* Wait USB write sequence(WRITE10) */
        do
        {
            /* Check Detach */
            data = usb_hmsc_get_dev_sts(p_drive);
            rm_block_media_usb_waitloop();                                               /* Task Schedule */
            usb_err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
        } while ((usb_err != USB_OK) && (data != USB_FALSE));

        if (usb_err == USB_OK)
        {
            /* Complete R_USB_HmscStrgReadSector() */
            usb_err = p_mess->result;  /* Set result for R_USB_HmscStrgReadSector() */
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
        }
        else
        {
            /* Device detach */
            rm_block_media_usb_waitloop();                                               /* Task Schedule */
            usb_err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess, (uint16_t) 0); /* Receive read complete msg */
            if (USB_OK == usb_err)
            {
                USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
            }

            usb_err = USB_ERROR;
        }

        if (usb_err != USB_OK)
        {
            return FSP_ERR_USB_FAILED;
        }
#endif                                 /* BSP_CFG_RTOS == 0 */
    }

    rm_block_media_callback_args_t args;
    memset(&args, 0U, sizeof(rm_block_media_callback_args_t));
    args.p_context = p_instance_ctrl->p_cfg->p_context;
    args.event     = RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE;
    rm_block_media_usb_call_callback(p_instance_ctrl, &args);

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
fsp_err_t RM_BLOCK_MEDIA_USB_CallbackSet (rm_block_media_ctrl_t * const p_api_ctrl,
                                          void (                      * p_callback)(
                                              rm_block_media_callback_args_t *),
                                          void const * const                     p_context,
                                          rm_block_media_callback_args_t * const p_callback_memory)
{
    rm_block_media_usb_instance_ctrl_t * p_ctrl = (rm_block_media_usb_instance_ctrl_t *) p_api_ctrl;

#if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(RM_BLOCK_MEDIA_USB_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if RM_BLOCK_MEDIA_USB_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    rm_block_media_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                                 CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(rm_block_media_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
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
 * Calls user callback.
 *
 * @param[in]     p_instance_ctrl      Pointer to block media usb instance control block
 * @param[in]     p_callback_args      Pointer to callback args
 **********************************************************************************************************************/
static void rm_block_media_usb_call_callback (rm_block_media_usb_instance_ctrl_t * p_instance_ctrl,
                                              rm_block_media_callback_args_t     * p_callback_args)
{
    rm_block_media_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    rm_block_media_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->event     = p_callback_args->event;
    p_args->p_context = p_instance_ctrl->p_context;

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
        blockmedia_usb_prv_ns_callback p_callback = (blockmedia_usb_prv_ns_callback) (p_instance_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_instance_ctrl->p_callback(p_args);
#endif

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }
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
        if (NULL != p_instance_ctrl->p_callback)
        {
            rm_block_media_usb_call_callback(p_instance_ctrl, &args);
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
        usb_hstd_hcd_task((void *) 0);
        usb_hstd_mgr_task((void *) 0);

        // usb_hhub_task((usb_vp_int_t) 0);
        usb_hmsc_task();               /* HMSC Task */
    }

    usb_cstd_scheduler();
}

#endif                                 /* BSP_CFG_RTOS == 0 */
