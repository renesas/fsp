/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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

 #if defined(USB_CFG_PHID2_USE)
    if (g_usb_phid_int_in_pipe[ctrl.module_number] == ctrl.pipe)
    {
        ctrl.type = USB_CLASS_PHID;    /* Device class setting  */
    }
    else
    {
        ctrl.type = USB_CLASS_PHID2;   /* Device class setting  */
    }
 #else
    ctrl.type = USB_CLASS_PHID;        /* HID Data class  */
 #endif

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

 #if defined(USB_CFG_PHID2_USE)
    if (g_usb_phid_int_out_pipe[ctrl.module_number] == ctrl.pipe)
    {
        ctrl.type = USB_CLASS_PHID;    /* Device class setting  */
    }
    else
    {
        ctrl.type = USB_CLASS_PHID2;   /* Device class setting  */
    }
 #else
    ctrl.type = USB_CLASS_PHID;
 #endif

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
