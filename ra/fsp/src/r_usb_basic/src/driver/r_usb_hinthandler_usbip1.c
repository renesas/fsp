/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
 #if USB_NUM_USBIP == 2

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 * Renesas Abstracted common Interrupt handler functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb2_hstd_usb_handler
 * Description     : USB2 interrupt routine. Analyze which USB interrupt occurred
 *               : and send message to PCD/HCD task.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb2_hstd_usb_handler (void)
{
    usb_utr_t * ptr;
    usb_er_t    err;
    IRQn_Type   irq;
    usb_cfg_t * p_cfg;

    irq   = R_FSP_CurrentIrqGet();
    p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet(irq);

    /* Initial pointer */
    ptr                = &g_usb_cstd_int_msg[1][g_usb_cstd_int_msg_cnt[1]];
    ptr->ip            = USB_IP1;
    ptr->ipp           = usb_hstd_get_usb_ip_adr(ptr->ip);
    ptr->p_transfer_rx = p_cfg->p_transfer_rx;
    ptr->p_transfer_tx = p_cfg->p_transfer_tx;

    /* Host Function */
    /* Host Interrupt handler */
    usb_hstd_interrupt_handler(ptr);
    ptr->msghead = (usb_mh_t) USB_NULL;

    /* Send message */
    err = USB_ISND_MSG(USB_HCD_MBX, (usb_msg_t *) ptr);
    if (err != USB_OK)
    {
        /*USB_PRINTF1("### lib_UsbHandler DEF2 isnd_msg error (%ld)\n", err);*/
    }

    /* Renewal Message count  */
    g_usb_cstd_int_msg_cnt[1]++;
    if (USB_INTMSGMAX == g_usb_cstd_int_msg_cnt[1])
    {
        g_usb_cstd_int_msg_cnt[1] = 0;
    }
}

 #endif                                /* #if USB_NUM_USBIP == 2 */
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
