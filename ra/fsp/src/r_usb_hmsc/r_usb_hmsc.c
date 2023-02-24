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

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "r_usb_hmsc_api.h"
#include "r_usb_hmsc.h"
#include "src/inc/r_usb_hmsc_driver.h"

#if (BSP_CFG_RTOS == 2)
 #include "FreeRTOS.h"
#endif                                 /* (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if (BSP_CFG_RTOS == 2)
extern SemaphoreHandle_t SemaphoreHandleRead;
#endif                                 /* (BSP_CFG_RTOS == 2) */

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const usb_hmsc_api_t g_hmsc_on_usb =
{
    .storageCommand     = R_USB_HMSC_StorageCommand,
    .driveNumberGet     = R_USB_HMSC_DriveNumberGet,
    .storageReadSector  = R_USB_HMSC_StorageReadSector,
    .storageWriteSector = R_USB_HMSC_StorageWriteSector,
    .semaphoreGet       = R_USB_HMSC_SemaphoreGet,
    .semaphoreRelease   = R_USB_HMSC_SemaphoreRelease,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HMSC USB_HMSC
 * @{
 **********************************************************************************************************************/

/*************************************************************************//**
 * @brief Processing for MassStorage(ATAPI) command.
 *
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_HMSC_StorageCommand (usb_ctrl_t * const p_api_ctrl, uint8_t * buf, uint8_t command, uint8_t destination)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t  err = FSP_SUCCESS;
    usb_info_t info;
    usb_utr_t  utr;
    uint8_t    side;
    uint16_t   ret;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)

    FSP_ASSERT(buf)

    /* Argument Checking */
    FSP_ASSERT(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)))

 #if defined(BSP_MCU_GROUP_RA2A1)
    FSP_ASSERT(USB_IP1 != p_api_trans->module)
 #endif                                /* defined(BSP_MCU_GROUP_RA2A1) */
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    FSP_ASSERT(destination)
    FSP_ERROR_RETURN(USB_ADDRESS5 >= destination, FSP_ERR_USB_PARAMETER)
 #endif                                /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
#endif                                 /* #if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    utr.ip                 = p_ctrl->module_number;
    utr.ipp                = usb_hstd_get_usb_ip_adr(utr.ip);
    p_ctrl->device_address = destination;
    utr.p_transfer_rx      = p_ctrl->p_transfer_rx;
    utr.p_transfer_tx      = p_ctrl->p_transfer_tx;

    R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    err = R_USB_HMSC_DriveNumberGet(p_ctrl, &side, p_ctrl->device_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_USB_FAILED)

    ret = usb_hmsc_strg_user_command(&utr, side, command, buf, usb_hmsc_strg_cmd_complete);
#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_PAR != ret)
#endif                                 /* #if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    if (USB_OK != ret)
    {
#if (BSP_CFG_RTOS == 2)
        if (USB_HMSC_CSW_ERR == utr.result)
        {
            p_ctrl->status         = USB_CSW_RESULT_FAIL;
            p_ctrl->module_number  = utr.ip;                /* Module number setting */
            p_ctrl->pipe           = (uint8_t) utr.keyword; /* Pipe number setting */
            p_ctrl->device_address = (uint8_t) (usb_hstd_get_devsel(&utr, p_ctrl->pipe) >> 12);
            p_ctrl->data_size      = 0;
 #if (BSP_CFG_RTOS == 2)
            p_ctrl->p_data = (void *) xTaskGetCurrentTaskHandle();
 #endif                                                         /* (BSP_CFG_RTOS == 2) */
            usb_set_event(USB_STATUS_MSC_CMD_COMPLETE, p_ctrl); /* Set Event(USB receive complete)  */
            err = FSP_SUCCESS;
        }
        else
        {
            err = FSP_ERR_USB_FAILED;
        }

#else                                  /* (BSP_CFG_RTOS == 2) */
        err = FSP_ERR_USB_FAILED;
#endif  /* (BSP_CFG_RTOS == 2) */
    }

#if (BSP_CFG_RTOS == 2)
    else
    {
        p_ctrl->module_number  = utr.ip;                /* Module number setting */
        p_ctrl->pipe           = (uint8_t) utr.keyword; /* Pipe number setting */
        p_ctrl->device_address = (uint8_t) (usb_hstd_get_devsel(&utr, p_ctrl->pipe) >> 12);
        p_ctrl->data_size      = 0;

        switch (utr.result)
        {
            case USB_HMSC_OK:
            {
                p_ctrl->data_size = utr.tranlen;
                p_ctrl->status    = USB_CSW_RESULT_SUCCESS;
                break;
            }

            case USB_HMSC_CSW_ERR:
            {
                p_ctrl->status = USB_CSW_RESULT_FAIL;
                break;
            }

            case USB_HMSC_CSW_PHASE_ERR:
            {
                p_ctrl->status = USB_CSW_RESULT_PHASE;
                break;
            }

            default:
            {
                p_ctrl->status = USB_CSW_RESULT_FAIL;
                break;
            }
        }

 #if (BSP_CFG_RTOS == 2)
        p_ctrl->p_data = (void *) xTaskGetCurrentTaskHandle();
 #endif                                                     /* (BSP_CFG_RTOS == 2) */
        usb_set_event(USB_STATUS_MSC_CMD_COMPLETE, p_ctrl); /* Set Event(USB receive complete)  */
    }
#endif                                                      /* (BSP_CFG_RTOS == 2) */

    return err;
}

/******************************************************************************
 * End of function R_USB_HmscStrgCmd
 ******************************************************************************/

/*************************************************************************//**
 * @brief Get number of Storage drive.
 *
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_HMSC_DriveNumberGet (usb_ctrl_t * const p_api_ctrl, uint8_t * p_drive, uint8_t destination)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_info_t        info;
    usb_utr_t         utr;
    volatile uint16_t address;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl)

    FSP_ASSERT(p_drive)

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)), FSP_ERR_USB_PARAMETER)
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    FSP_ASSERT(destination)
    FSP_ERROR_RETURN(USB_ADDRESS5 >= destination, FSP_ERR_USB_PARAMETER)
 #endif                                /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    utr.ip                 = p_ctrl->module_number;
    utr.ipp                = usb_hstd_get_usb_ip_adr(utr.ip);
    p_ctrl->device_address = destination;

    R_USB_InfoGet(p_ctrl, &info, p_ctrl->device_address);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    address = p_ctrl->device_address;
    if (USB_IP1 == p_ctrl->module_number)
    {
        address |= USBA_ADDRESS_OFFSET;
    }

    *p_drive = (uint8_t) usb_hmsc_ref_drvno(address);
    FSP_ERROR_RETURN(USB_ERROR != *p_drive, FSP_ERR_USB_FAILED)

    return FSP_SUCCESS;
}

/******************************************************************************
 * End of function R_USB_HmscGetDriveNo
 ******************************************************************************/

/*************************************************************************//**
 * @brief Read sector information.
 *
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note The address specified in the argument buff must be 4-byte aligned.
 ******************************************************************************/
fsp_err_t R_USB_HMSC_StorageReadSector (uint16_t        drive_number,
                                        uint8_t * const buff,
                                        uint32_t        sector_number,
                                        uint16_t        sector_count)
{
    fsp_err_t   result = FSP_ERR_USB_FAILED;
    uint32_t    trans_byte;
    usb_utr_t   ptr;
    uint16_t    err_code;
    usb_cfg_t * p_cfg = USB_NULL;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(buff)
    FSP_ERROR_RETURN(USB_MAXSTRAGE >= drive_number, FSP_ERR_USB_PARAMETER)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    /* set sector size */
    trans_byte = (uint32_t) (sector_count * USB_HMSC_SECTOR_SIZE);

    /* Drive no. -> USB IP no. and IO Reg Base address */
    usb_hmsc_drive_to_addr(drive_number, &ptr);

    /* Device Status */
    if (USB_TRUE != usb_hmsc_get_dev_sts(drive_number))
    {
        return FSP_ERR_USB_FAILED;
    }

    if (ptr.ip)
    {
#if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
#endif                                 /* #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME) */
    }
    else
    {
#if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
#endif                                 /* #if defined(VECTOR_NUMBER_USBFS_INT) */
    }

    if (USB_NULL != p_cfg)
    {
        ptr.p_transfer_rx = p_cfg->p_transfer_rx;
        ptr.p_transfer_tx = p_cfg->p_transfer_tx;
    }

    g_usb_hmsc_strg_process[ptr.ip] = USB_MSG_HMSC_STRG_RW_END;
    err_code = usb_hmsc_read10(&ptr, drive_number, buff, sector_number, sector_count, trans_byte);
    if (USB_HMSC_OK == err_code)
    {
        result = FSP_SUCCESS;
    }
    else
    {
#if (BSP_CFG_RTOS == 2)
        hmsc_error_process(&ptr, drive_number, err_code);
#endif                                 /* (BSP_CFG_RTOS == 2) */
        result = FSP_ERR_USB_FAILED;
    }

    return result;
}

/******************************************************************************
 * End of function R_USB_HMSC_StrgReadSector
 ******************************************************************************/

/*************************************************************************//**
 * @brief Write sector information.
 *
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 * @note The address specified in the argument buff must be 4-byte aligned.
 ******************************************************************************/
fsp_err_t R_USB_HMSC_StorageWriteSector (uint16_t              drive_number,
                                         uint8_t const * const buff,
                                         uint32_t              sector_number,
                                         uint16_t              sector_count)
{
    fsp_err_t   result = FSP_ERR_USB_FAILED;
    uint32_t    trans_byte;
    usb_utr_t   ptr;
    uint16_t    err_code;
    usb_cfg_t * p_cfg = USB_NULL;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(buff)
    FSP_ERROR_RETURN(USB_MAXSTRAGE >= drive_number, FSP_ERR_USB_PARAMETER)
#endif                                 /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    /* set sector size */
    trans_byte = (uint32_t) (sector_count * USB_HMSC_SECTOR_SIZE);

    /* Drive no. -> USB IP no. and IO Reg Base address */
    usb_hmsc_drive_to_addr(drive_number, &ptr);

    /* Device Status */
    if (USB_TRUE != usb_hmsc_get_dev_sts(drive_number))
    {
        return FSP_ERR_USB_FAILED;
    }

    if (ptr.ip)
    {
#if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
#endif                                 /* #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME) */
    }
    else
    {
#if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
#endif                                 /* #if defined(VECTOR_NUMBER_USBFS_INT) */
    }

    if (USB_NULL != p_cfg)
    {
        ptr.p_transfer_rx = p_cfg->p_transfer_rx;
        ptr.p_transfer_tx = p_cfg->p_transfer_tx;
    }

    g_usb_hmsc_strg_process[ptr.ip] = USB_MSG_HMSC_STRG_RW_END;
    err_code = usb_hmsc_write10(&ptr, drive_number, buff, sector_number, sector_count, trans_byte);
    if (USB_HMSC_OK == err_code)
    {
        result = FSP_SUCCESS;
    }
    else
    {
#if (BSP_CFG_RTOS == 2)
        hmsc_error_process(&ptr, drive_number, err_code);
#endif                                 /* (BSP_CFG_RTOS == 2) */
        result = FSP_ERR_USB_FAILED;
    }

    return result;
}

/******************************************************************************
 * End of function R_USB_HMSC_StrgWriteSector
 ******************************************************************************/

/*************************************************************************//**
 * @brief Get a semaphore. (RTOS only)
 *
 * If this function is called in the OS less execution environment, a failure is returned.
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 ******************************************************************************/
fsp_err_t R_USB_HMSC_SemaphoreGet (void)
{
    fsp_err_t result;
#if (BSP_CFG_RTOS == 2)
    BaseType_t err_code;

    err_code = xSemaphoreTake(SemaphoreHandleRead, portMAX_DELAY);

    if (pdPASS == err_code)
    {
        result = FSP_SUCCESS;
    }
    else
    {
        result = FSP_ERR_USB_FAILED;
    }

#else                                  /* (BSP_CFG_RTOS == 2) */
    result = FSP_ERR_USB_FAILED;
#endif /* (BSP_CFG_RTOS == 2) */
    return result;
}

/******************************************************************************
 * End of function R_USB_HmscGetSem
 ******************************************************************************/

/*************************************************************************//**
 * @brief Release a semaphore. (RTOS only)
 *
 * If this function is called in the OS less execution environment, a failure is returned.
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 ******************************************************************************/
fsp_err_t R_USB_HMSC_SemaphoreRelease (void)
{
    fsp_err_t result;
#if (BSP_CFG_RTOS == 2)
    BaseType_t err_code;
    err_code = xSemaphoreGive(SemaphoreHandleRead);

    if (pdPASS == err_code)
    {
        result = FSP_SUCCESS;
    }
    else
    {
        result = FSP_ERR_USB_FAILED;
    }

#else                                  /* (BSP_CFG_RTOS == 2) */
    result = FSP_ERR_USB_FAILED;
#endif /* (BSP_CFG_RTOS == 2) */

    return result;
}

/******************************************************************************
 * End of function R_USB_HmscRelSem
 ******************************************************************************/

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HMSC)
 **********************************************************************************************************************/
