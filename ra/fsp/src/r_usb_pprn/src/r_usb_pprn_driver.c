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
#include "r_usb_basic_cfg.h"
#include "r_usb_pprn_cfg.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "r_usb_pprn_api.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"

#ifdef USB_CFG_PPRN_USE

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 * Exported global variables
 ******************************************************************************/

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 * Renesas Abstracted Peripheral Communications Devices Class Driver API functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pprn_read_complete
 * Description     : CallBack Function
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_pprn_read_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    if (USB_TRUE == g_usb_peri_connected)
    {
        /* Set Receive data length */
        ctrl.data_size = mess->read_req_len - mess->tranlen; /* Received Data Size */
        ctrl.pipe      = (uint8_t) mess->keyword;            /* Pipe number setting */
        ctrl.type      = USB_CLASS_PPRN;

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

        ctrl.module_number = mess->ip;
 #if (BSP_CFG_RTOS == 2)
        ctrl.p_data = (void *) mess->cur_task_hdl;
 #endif                                /* (BSP_CFG_RTOS == 2) */
        usb_set_event(USB_STATUS_READ_COMPLETE, &ctrl);
    }
}

/******************************************************************************
 * End of function usb_pprn_read_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pprn_write_complete
 * Description     : CallBack Function
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_pprn_write_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    if (USB_TRUE == g_usb_peri_connected)
    {
        ctrl.pipe = (uint8_t) mess->keyword; /* Pipe number setting */
        ctrl.type = USB_CLASS_PPRN;

        if (USB_DATA_NONE == mess->status)
        {
            ctrl.status = FSP_SUCCESS;
        }
        else
        {
            ctrl.status = FSP_ERR_USB_FAILED;
        }

        ctrl.module_number = mess->ip;
 #if (BSP_CFG_RTOS == 2)
        ctrl.p_data = (void *) mess->cur_task_hdl;
 #endif                                /* (BSP_CFG_RTOS == 2) */
        usb_set_event(USB_STATUS_WRITE_COMPLETE, &ctrl);
    }
}

/******************************************************************************
 * End of function usb_pprn_write_complete
 ******************************************************************************/
#endif                                 /* USB_CFG_PPRN_USE */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
