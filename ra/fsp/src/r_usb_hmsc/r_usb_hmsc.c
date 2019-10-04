/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
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
#endif  /* (BSP_CFG_RTOS == 2) */

#if defined(USB_CFG_HMSC_USE)

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if (BSP_CFG_RTOS == 2)
extern SemaphoreHandle_t  SemaphoreHandleRead;
#endif /* (BSP_CFG_RTOS == 2) */

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const usb_hmsc_api_t g_hmsc_on_usb =
{
    .strgcmd             = R_USB_HmscStrgCmd,
    .drivenoget          = R_USB_HmscDriveNoGet,
    .drive2addr          = R_USB_HmscSmpDrive2Addr,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HMSC USB_HMSC
 * @{
 **********************************************************************************************************************/

/**************************************************************************//**
 * @brief Processing for MassStorage(ATAPI) command.
 *
 * @retval FSP_SUCCESS         Success in open.
 * @retval FSP_ERR_USB_FAILED  The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION   Parameter error.
 ******************************************************************************/
fsp_err_t   R_USB_HmscStrgCmd(usb_ctrl_t * const p_api_ctrl, uint8_t *buf, uint16_t command, usb_instance_transfer_t * p_api_trans)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t   err = FSP_SUCCESS;
    usb_info_t  info;
    usb_utr_t   utr;
    uint8_t     side;
    uint16_t    ret;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    FSP_ASSERT(USB_NULL != p_api_trans)
    /* Argument Checking */
    FSP_ASSERT(!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number)))

#if defined(BSP_MCU_GROUP_RA2A1)
    FSP_ASSERT(USB_IP1 != p_api_trans->module)
#endif /* defined(BSP_MCU_GROUP_RA2A1) */

#endif /* #if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    utr.ip = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

    R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    err = R_USB_HmscDriveNoGet(p_ctrl, &side, p_api_trans);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_USB_FAILED)

    ret = usb_hmsc_strg_user_command(&utr, side, command, buf, usb_hmsc_strg_cmd_complete);
#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_PAR != ret)
#endif /* #if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    if (USB_OK != ret)
    {
#if (BSP_CFG_RTOS == 2)
        if (USB_HMSC_CSW_ERR == utr.result)
        {
            p_ctrl->status         = USB_CSW_RESULT_FAIL;
            p_ctrl->module_number  = (uint8_t)utr.ip;       /* Module number setting */
            p_ctrl->pipe           = (uint8_t)utr.keyword;  /* Pipe number setting */
            p_ctrl->device_address = (uint8_t)(usb_hstd_get_devsel(&utr, p_ctrl->pipe) >> 12);
            p_ctrl->data_size           = 0;
#if (BSP_CFG_RTOS == 2)
            p_ctrl->p_data = (void *)xTaskGetCurrentTaskHandle();
#endif /* (BSP_CFG_RTOS == 2) */
            usb_set_event(USB_STATUS_MSC_CMD_COMPLETE, p_ctrl); /* Set Event(USB receive complete)  */
            err = FSP_SUCCESS;
        }
        else
        {
        	err = FSP_ERR_USB_FAILED;
        }
#else   /* (BSP_CFG_RTOS == 2) */
        err = FSP_ERR_USB_FAILED;
#endif  /* (BSP_CFG_RTOS == 2) */
    }
#if (BSP_CFG_RTOS == 2)
    else
    {
        p_ctrl->module_number  = (uint8_t)utr.ip;       /* Module number setting */
        p_ctrl->pipe           = (uint8_t)utr.keyword;  /* Pipe number setting */
        p_ctrl->device_address = (uint8_t)(usb_hstd_get_devsel(&utr, p_ctrl->pipe) >> 12);
        p_ctrl->data_size      = 0;

        switch (utr.result)
        {
            case USB_HMSC_OK:
                p_ctrl->data_size    = utr.tranlen;
                p_ctrl->status  = USB_CSW_RESULT_SUCCESS;
            break;

            case USB_HMSC_CSW_ERR:
                p_ctrl->status  = USB_CSW_RESULT_FAIL;
            break;

            case USB_HMSC_CSW_PHASE_ERR:
                p_ctrl->status  = USB_CSW_RESULT_PHASE;
            break;

            default:
                p_ctrl->status  = USB_CSW_RESULT_FAIL;
            break;
        }
#if (BSP_CFG_RTOS == 2)
        p_ctrl->p_data = (void *)xTaskGetCurrentTaskHandle();
#endif /* (BSP_CFG_RTOS == 2) */
        usb_set_event(USB_STATUS_MSC_CMD_COMPLETE, p_ctrl); /* Set Event(USB receive complete)  */
    }
#endif  /* (BSP_CFG_RTOS == 2) */

    return err;

}
/******************************************************************************
 End of function R_USB_HmscStrgCmd
 ******************************************************************************/

/**************************************************************************//**
 * @brief Get number of Storage drive.
 *
 * @retval FSP_SUCCESS         Success in open.
 * @retval FSP_ERR_USB_FAILED  The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION   Parameter error.
 ******************************************************************************/
fsp_err_t     R_USB_HmscDriveNoGet(usb_ctrl_t * const p_api_ctrl, uint8_t *p_drive, usb_instance_transfer_t * p_api_trans)
{
	usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_info_t  info;
    usb_utr_t   utr;
    volatile uint16_t   address;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_NULL != p_api_ctrl)

    FSP_ASSERT(USB_NULL != p_api_trans)

    /* Argument Checking */
    FSP_ASSERT(!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number)))


#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */
	if(p_ctrl != (usb_instance_ctrl_t *)p_api_trans)
	{
	    p_ctrl->module_number = p_api_trans->module_number;
	    p_ctrl->type = p_api_trans->type;
	    p_ctrl->device_address = p_api_trans->device_address;
	    p_ctrl->pipe = p_api_trans->pipe;
	    p_ctrl->setup = p_api_trans->setup;
	}

    utr.ip = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

    R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN (USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    address = p_ctrl->device_address;
    if (USB_IP1 == p_ctrl->module_number)
    {
        address |= USBA_ADDRESS_OFFSET;
    }

    *p_drive = (uint8_t)usb_hmsc_ref_drvno(address);
    FSP_ERROR_RETURN(USB_ERROR != *p_drive,FSP_ERR_USB_FAILED)

    return FSP_SUCCESS;

}
/******************************************************************************
 End of function R_USB_HmscGetDriveNo
 ******************************************************************************/

/**************************************************************************//**
 * @brief Retrieves device address.
 *
 * @retval FSP_SUCCESS         Success in open.
 * @retval FSP_ERR_ASSERTION   Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_HmscSmpDrive2Addr (uint16_t side, usb_utr_t *devadr)
{
#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(USB_MAXSTRAGE > side)

	FSP_ASSERT(USB_NULL != devadr)
#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    devadr->keyword = g_usb_hmsc_drvno_tbl[side].devadr; /* Device Address */
    devadr->ip = g_usb_hmsc_drvno_tbl[side].ip; /* USB IP No.     */
    devadr->ipp = usb_hstd_get_usb_ip_adr(devadr->ip);

    return FSP_SUCCESS;
}
/******************************************************************************
 End of function R_USB_HmscSmpDrive2Addr
 ******************************************************************************/

#if (BSP_CFG_RTOS == 2)
/******************************************************************************
Function Name   : R_USB_HmscSemGet
Description     : Get a semaphore.
Arguments       : none
Return value    : none
******************************************************************************/
void     R_USB_HmscSemGet(void)
{
    xSemaphoreTake(SemaphoreHandleRead, portMAX_DELAY);
}
/******************************************************************************
 End of function R_USB_HmscGetSem
 ******************************************************************************/

/******************************************************************************
Function Name   : R_USB_HmscSemRel
Description     : Release a semaphore.
Arguments       : none
Return value    : none
******************************************************************************/
void     R_USB_HmscSemRel(void)
{
    xSemaphoreGive(SemaphoreHandleRead);
}
/******************************************************************************
 End of function R_USB_HmscRelSem
 ******************************************************************************/
#endif /* (BSP_CFG_RTOS == 2) */

#endif /* defined(USB_CFG_HMSC_USE) */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HMSC)
 **********************************************************************************************************************/

