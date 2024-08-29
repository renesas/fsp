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

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
usb_utr_t g_usb_cstd_int_msg[USB_NUM_USBIP][USB_INTMSGMAX]; /* Interrupt message */
uint16_t  g_usb_cstd_int_msg_cnt[USB_NUM_USBIP];            /* Interrupt message count */

/******************************************************************************
 * Renesas Abstracted common Interrupt handler functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_usb_handler
 * Description     : USB interrupt routine. Analyze which USB interrupt occurred
 *               : and send message to PCD/HCD task.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_hstd_usb_handler (void)
{
    usb_utr_t * ptr;
    usb_er_t    err;
    IRQn_Type   irq;
    usb_cfg_t * p_cfg;

    irq   = R_FSP_CurrentIrqGet();
    p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet(irq);

    /* Initial pointer */
    ptr                = &g_usb_cstd_int_msg[0][g_usb_cstd_int_msg_cnt[0]];
    ptr->ip            = USB_IP0;
    ptr->ipp           = usb_hstd_get_usb_ip_adr(ptr->ip);
    ptr->p_transfer_rx = p_cfg->p_transfer_rx;
    ptr->p_transfer_tx = p_cfg->p_transfer_tx;

    /* Host Function */
    /* Host Interrupt handler */
    usb_hstd_interrupt_handler(ptr);
    ptr->msghead = (usb_mh_t) USB_NULL;

    /* Send message */
    err = USB_ISND_MSG(USB_HCD_MBX, (usb_msg_t *) ptr);
    if (USB_OK != err)
    {
        USB_PRINTF1("### lib_UsbHandler DEF2 isnd_msg error (%ld)\n", err);
    }

    /* Renewal Message count  */
    g_usb_cstd_int_msg_cnt[0]++;
    if (USB_INTMSGMAX == g_usb_cstd_int_msg_cnt[0])
    {
        g_usb_cstd_int_msg_cnt[0] = 0;
    }
}

/******************************************************************************
 * End of function usb_hstd_usb_handler
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_dma_handler
 * Description     : DMA interrupt routine. Send message to PCD/HCD task.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_hstd_dma_handler (void)
{
    /* Non processing*/
}

/******************************************************************************
 * End of function usb_hstd_dma_handler
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_init_usb_message
 * Description     : Initialization of message to be used at time of USB interrupt.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_init_usb_message (usb_utr_t * ptr)
{
    /* TD.5.4 The interruption message of PCD is notified to HCD.  */
    uint16_t i;
    uint16_t msg_info;

    /* Host Function */
    msg_info = USB_MSG_HCD_INT;

    /* WAIT_LOOP */
    for (i = 0; i < USB_INTMSGMAX; i++)
    {
        g_usb_cstd_int_msg[ptr->ip][i].msginfo = msg_info;
    }

    g_usb_cstd_int_msg_cnt[ptr->ip] = 0;
}

/******************************************************************************
 * End of function usb_hstd_init_usb_message
 ******************************************************************************/
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
