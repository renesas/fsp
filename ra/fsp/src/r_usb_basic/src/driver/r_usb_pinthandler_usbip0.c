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

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
usb_int_t g_usb_pstd_usb_int;

 #if (BSP_CFG_RTOS != 0)
static usb_utr_t g_usb_pstd_int[USB_INT_BUFSIZE];
 #endif                                /* #if (BSP_CFG_RTOS != 0)*/

 #if (BSP_CFG_RTOS == 1)
extern TX_QUEUE g_pcd_mbx_hdl;
 #endif                                /* (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Renesas Abstracted common Interrupt handler functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_usb_handler
 * Description     : USB interrupt routine. Analyze which USB interrupt occurred
 *               : and send message to PCD task.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_usb_handler (void)
{
 #if (BSP_CFG_RTOS != 0)
    usb_utr_t * p;

    p = get_usb_int_buf();
 #endif                                /*(BSP_CFG_RTOS != 0)*/
    IRQn_Type   irq;
    usb_cfg_t * p_cfg;

    irq   = R_FSP_CurrentIrqGet();
    p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet(irq);

    usb_pstd_interrupt_clock(p_cfg->module_number);

    /* Push Interrupt info */
 #if (BSP_CFG_RTOS != 0)
    p->msginfo       = USB_MSG_PCD_INT;
    p->ip            = p_cfg->module_number;
    p->p_transfer_rx = p_cfg->p_transfer_rx;
    p->p_transfer_tx = p_cfg->p_transfer_tx;
    usb_pstd_interrupt_handler(&p->keyword, &p->status, p->ip);

    USB_ISND_MSG(USB_PCD_MBX, (usb_msg_t *) p);
 #endif                                /*(BSP_CFG_RTOS != 0)*/

 #if (BSP_CFG_RTOS == 0)
    g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].p_cfg = p_cfg;

    usb_pstd_interrupt_handler(&g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].type,
                               &g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].status,
                               g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].p_cfg->module_number);

    /* Write count up */
    g_usb_pstd_usb_int.wp = (uint8_t) ((uint8_t) (g_usb_pstd_usb_int.wp + 1) % USB_INT_BUFSIZE);
 #endif                                /*(BSP_CFG_RTOS == 0)*/
}

/******************************************************************************
 * End of function usb_pstd_usb_handler
 ******************************************************************************/

 #if (BSP_CFG_RTOS != 0)

/******************************************************************************
 * Function Name   : get_usb_int_buf
 * Description     : USB interrupt routine. Analyze which USB interrupt occurred
 *               : and send message to PCD task.
 * Arguments       : none
 * Return value    : Point to the area for usb_int_t structure
 ******************************************************************************/
usb_utr_t * get_usb_int_buf (void)
{
    static uint16_t count = 0;
    usb_utr_t     * p;

    p = &g_usb_pstd_int[count];

    count = ((uint16_t) (((uint16_t) (count + 1)) % USB_INT_BUFSIZE));

    return p;
}

/******************************************************************************
 * End of function get_usb_int_buf
 ******************************************************************************/
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
