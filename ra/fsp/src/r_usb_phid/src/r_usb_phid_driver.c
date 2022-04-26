/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2015(2018) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : r_usb_phid_driver.c
 * Description  : USB HID application code
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.09.2015 1.11 First Release
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 phid_read_complete(),phid_write_complete is fixed.
 *         : 30.09.2017 1.22 Changed function names
 *                           "phid_write_complete"->"usb_phid_write_complete"
 *                           "phid_read_complete"->"usb_phid_read_complete"
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 ***********************************************************************************************************************/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_api.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_reg_access.h"
#include "r_usb_phid_api.h"

#ifdef USB_CFG_PHID_USE

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 * Renesas Abstracted USB Driver functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_phid_write_complete
 * Description     : CallBack Function
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_phid_write_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    usb_instance_ctrl_t ctrl;

    ctrl.pipe          = (uint8_t) mess->keyword; /* Pipe number setting */
    ctrl.module_number = mess->ip;

// ctrl.type          = USB_CLASS_PHID;          /* HID Data class  */
    if (USB_CFG_PHID_INT_IN == ctrl.pipe)
    {
        ctrl.type = USB_CLASS_PHID;    /* Device class setting  */
    }
    else
    {
        ctrl.type = USB_CLASS_PHID2;   /* Device class setting  */
    }

    if (USB_DATA_NONE == mess->status)
    {
        ctrl.status = FSP_SUCCESS;
    }
    else
    {
        ctrl.status = FSP_ERR_USB_FAILED;
    }

 #if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) mess->cur_task_hdl;
 #endif                                /* (BSP_CFG_RTOS_USED == 1) */
    usb_set_event(USB_STATUS_WRITE_COMPLETE, &ctrl);
}

/******************************************************************************
 * End of function usb_phid_write_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_phid_read_complete
 * Description     : CallBack Function
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_phid_read_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    usb_instance_ctrl_t ctrl;

    /* Set Receive data length */
    ctrl.data_size = mess->read_req_len - mess->tranlen;

    ctrl.pipe          = (uint8_t) mess->keyword; /* Pipe number setting */
    ctrl.module_number = mess->ip;

// ctrl.type = USB_CLASS_PHID;                   /* Device class setting  */
    if (USB_CFG_PHID_INT_OUT == ctrl.pipe)
    {
        ctrl.type = USB_CLASS_PHID;    /* Device class setting  */
    }
    else
    {
        ctrl.type = USB_CLASS_PHID2;   /* Device class setting  */
    }

    switch (mess->status)
    {
        case USB_DATA_OK:
        {
            ctrl.status = FSP_SUCCESS;
            break;
        }

        case USB_DATA_SHT:
        {
            ctrl.status = FSP_ERR_USB_SIZE_SHORT;
            break;
        }

        case USB_DATA_OVR:
        {
            ctrl.status = FSP_ERR_USB_SIZE_OVER;
            break;
        }

        case USB_DATA_ERR:
        default:
        {
            ctrl.status = FSP_ERR_USB_FAILED;
            break;
        }
    }

 #if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) mess->cur_task_hdl;
 #endif                                /* (BSP_CFG_RTOS_USED == 1) */
    usb_set_event(USB_STATUS_READ_COMPLETE, &ctrl);
}

/******************************************************************************
 * End of function usb_phid_read_complete
 ******************************************************************************/
#endif                                 /* USB_CFG_PHID_USE */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
