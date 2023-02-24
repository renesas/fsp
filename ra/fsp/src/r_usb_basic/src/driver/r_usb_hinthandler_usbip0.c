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
