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

#include "../driver/inc/r_usb_typedef.h"
#include "../driver/inc/r_usb_extern.h"
#include "inc/r_usb_bitdefine.h"
#include "inc/r_usb_reg_access.h"

#define USB_VALUE_50     (50)
#define USB_VALUE_300    (300)

#if defined(USB_HIGH_SPEED_MODULE)
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : usb_hstd_test_stop
 * Description     : Host electrical test stop
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     port    : Port number
 * Return value    : none
 ******************************************************************************/
void usb_hstd_test_stop (usb_utr_t * ptr)
{
    /* USBRST=0, RESUME=0, UACT=1 */
    usb_hstd_set_uact(ptr);
}

/******************************************************************************
 * End of function usb_hstd_test_stop
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_test_signal
 * Description     : Host electrical test signal control.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     command : USB_UACTON / OFF
 * Return value    : none
 ******************************************************************************/
void usb_hstd_test_signal (usb_utr_t * ptr, uint16_t command)
{
    uint16_t buff;

    switch (command)
    {
        case 1:
        {
            buff = USB_H_TST_J;
            break;
        }

        case 2:
        {
            buff = USB_H_TST_K;
            break;
        }

        case 3:
        {
            buff = USB_H_TST_SE0_NAK;
            break;
        }

        case 4:
        {
            buff = USB_H_TST_PACKET;
            break;
        }

        default:
        {
            buff = USB_H_TST_NORMAL;
            hw_usb_set_utst(ptr, buff);
            usb_hstd_sw_reset(ptr);
            break;
        }
    }

    usb_hstd_test_uact_ctrl(ptr, (uint16_t) USB_UACTOFF);
    hw_usb_set_utst(ptr, buff);
    usb_hstd_test_uact_ctrl(ptr, (uint16_t) USB_UACTON);
}

/******************************************************************************
 * End of function usb_hstd_test_signal
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_test_uact_ctrl
 * Description     : Host electrical test SOF control.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     command : USB_UACTON / OFF
 * Return value    : none
 ******************************************************************************/
void usb_hstd_test_uact_ctrl (usb_utr_t * ptr, uint16_t command)
{
    if (USB_UACTON == command)
    {
        /* SOF out disable */
        hw_usb_hset_uact(ptr);
    }
    else
    {
        /* SOF out disable */
        hw_usb_hclear_uact(ptr);
    }

    /* Wait 1ms */
    usb_cpu_delay_xms((uint16_t) 1);
}

/******************************************************************************
 * End of function usb_hstd_test_uact_ctrl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_test_vbus_ctrl
 * Description     : Host electrical test VBUS control.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     command : USB_UACTON / OFF
 * Return value    : none
 ******************************************************************************/
void usb_hstd_test_vbus_ctrl (usb_utr_t * ptr, uint16_t command)
{
    if (USB_VBON == command)
    {
        /* VBUS on */
        hw_usb_set_vbout(ptr);
    }
    else
    {
        /* VBUS off */
        hw_usb_clear_vbout(ptr);
    }

    /* Wait 1ms */
    usb_cpu_delay_xms((uint16_t) 1);
}

/******************************************************************************
 * End of function usb_hstd_test_vbus_ctrl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_test_bus_reset
 * Description     : Host electrical test USB-reset signal control.
 * Arguments       : usb_utr_t    *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_test_bus_reset (usb_utr_t * ptr)
{
    /* USBRST=1, UACT=0 */
    hw_usb_rmw_dvstctr(ptr, USB_USBRST, (USB_USBRST | USB_UACT));

    /* Wait 50ms */
    usb_cpu_delay_xms((uint16_t) USB_VALUE_50);

    /* USBRST=0 */
    hw_usb_clear_dvstctr(ptr, USB_USBRST); /* for UTMI */
    usb_cpu_delay_1us(USB_VALUE_300);      /* for UTMI */

    /* USBRST=0, RESUME=0, UACT=1 */
    usb_hstd_set_uact(ptr);

    /* Wait 10ms or more (USB reset recovery) */
    usb_cpu_delay_xms((uint16_t) 20);
}

/******************************************************************************
 * End of function usb_hstd_test_bus_reset
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_test_suspend
 * Description     : Host electrical test suspend control.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_test_suspend (usb_utr_t * ptr)
{
    /* SOF out disable */
    hw_usb_hclear_uact(ptr);

    /* Wait 1ms */
    usb_cpu_delay_xms((uint16_t) 1);
}                                      /* End of function */

/******************************************************************************
 * End of function usb_hstd_test_suspend
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_test_resume
 * Description     : Host electrical test resume control.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_test_resume (usb_utr_t * ptr)
{
    /* RESUME bit on */
    hw_usb_hset_resume(ptr);

    /* Wait */
    usb_cpu_delay_xms((uint16_t) 20);

    /* RESUME bit off */
    hw_usb_hclear_resume(ptr);

    /* SOF on */
    hw_usb_hset_uact(ptr);
}

/******************************************************************************
 * End of function usb_hstd_test_resume
 ******************************************************************************/

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */

/******************************************************************************
 * End of file
 ******************************************************************************/
