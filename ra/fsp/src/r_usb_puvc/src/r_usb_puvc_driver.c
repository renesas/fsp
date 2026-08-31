/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include "r_usb_basic_cfg.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "r_usb_puvc_api.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"

#ifdef USB_CFG_PUVC_USE

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
 #define NUM_OF_INTERFACE    (8U)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 * Exported global variables
 ******************************************************************************/
extern uint8_t g_usb_puvc_iso_pipe[NUM_OF_INTERFACE];

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 * Renesas Abstracted Peripheral Communications Devices Class Driver API functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_puvc_pipe_set
 * Description     : Pipe information check and EP table set, then USB pipe registers set
 * Arguments       : usb_utr_t *p_utr          : Pointer to usb_utr_t structure
 *                 : uint16_t requested_if_num : Requested interface number
 *                 : uint16_t requested_alt_num : Requested alternative number
 * Return value    : uint16_t : USB_E_OK / USB_E_ERROR
 ******************************************************************************/
uint16_t usb_puvc_pipe_set (usb_utr_t * p_utr, uint16_t requested_if_num, uint16_t requested_alt_num)
{
    uint8_t * table;
    uint16_t  length;
    uint16_t  ofdsc;
    uint16_t  retval = USB_ERROR;
    uint8_t   pipe_no;
    uint8_t   class_info;
    uint8_t   if_num                  = 0;
    uint8_t   alt_num                 = 0;
    uint8_t   is_interface_discovered = 0;

    if (USB_TRUE == g_usb_peri_connected)
    {
        if (NULL != g_usb_pstd_driver.p_othertbl)
        {
            table  = g_usb_pstd_driver.p_othertbl;
            length = (uint16_t) table[3];
            length = (uint16_t) (length << 8);
            length = (uint16_t) (length + (uint16_t) table[2]);

            ofdsc = table[0];

            /* WAIT_LOOP */
            while (ofdsc < length)
            {
                if (USB_DT_INTERFACE == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
                {
                    class_info = table[ofdsc + USB_IF_B_INTERFACECLASS];
                    if_num     = table[ofdsc + USB_IF_B_INTERFACENUMBER];
                    alt_num    = table[ofdsc + USB_IF_B_ALTERNATESETTING];

                    if ((USB_IFCLS_VID == class_info) &&
                        ((requested_if_num == if_num) && (requested_alt_num == alt_num)))
                    {
                        is_interface_discovered = 1;
                    }
                    else
                    {
                        is_interface_discovered = 0;
                    }
                }

                if (1 == is_interface_discovered)
                {
                    /* Endpoint Descriptor */
                    if (USB_DT_ENDPOINT == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
                    {
                        /* EP Table pipe Information set */
                        pipe_no = usb_pstd_set_pipe_table(&table[ofdsc], p_utr, class_info);
                        if (USB_NULL != pipe_no)
                        {
                            g_usb_puvc_iso_pipe[if_num] = pipe_no;

                            usb_pstd_set_pipe_reg(p_utr);
                            retval = USB_OK;
                        }

                        break;
                    }
                }

                ofdsc = (uint16_t) (ofdsc + table[ofdsc]);
            }
        }
    }

    return retval;
}

/******************************************************************************
 * End of function usb_puvc_pipe_set
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_puvc_write_complete
 * Description     : CallBack Function
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
 *                 : uint16_t     data1   : Not used
 *                 : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_puvc_write_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    if (USB_TRUE == g_usb_peri_connected)
    {
        ctrl.pipe = (uint8_t) mess->keyword; /* Pipe number setting */

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
 * End of function usb_puvc_write_complete
 ******************************************************************************/
#endif                                 /* USB_CFG_PUVC_USE */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
