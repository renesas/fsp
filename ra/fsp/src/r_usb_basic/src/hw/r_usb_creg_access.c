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
#include <r_usb_basic_cfg.h>

#include "../driver/inc/r_usb_typedef.h"
#include "../driver/inc/r_usb_extern.h"
#include "inc/r_usb_bitdefine.h"
#include "inc/r_usb_reg_access.h"
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
 #include "inc/r_usb_dmac.h"
#endif                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#define USB_VALUE_0F00H    (0x0f00)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
static void * hw_usb_get_fifosel_adr(usb_utr_t * ptr, uint16_t pipemode);
static void * hw_usb_get_fifoctr_adr(usb_utr_t * ptr, uint16_t pipemode);

/******************************************************************************
 * Function Name   : hw_usb_read_syscfg
 * Description     : Returns the specified port's SYSCFG register value.
 * Arguments       : usb_utr_t    *ptr   : Pointer to usb_utr_t structure.
 * Return value    : SYSCFG content.
 ******************************************************************************/
uint16_t hw_usb_read_syscfg (usb_utr_t * ptr)
{
    uint16_t ret_code = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            ret_code = USB_M0->SYSCFG;
        }
        else
        {
            ret_code = USB_M1->SYSCFG;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ret_code = ptr->ipp->SYSCFG;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return ret_code;
}

/******************************************************************************
 * End of function hw_usb_read_syscfg
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_write_syscfg
 * Description     : Write specified value to the SYSCFG register of the given port.
 * Arguments       : usb_utr_t    *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t     data   : Value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_syscfg (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->SYSCFG = data;
}

/******************************************************************************
 * End of function hw_usb_write_syscfg
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if defined(USB_HIGH_SPEED_MODULE)
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Function Name   : hw_usb_set_cnen
 * Description     : Enable single end receiver.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_cnen (uint8_t usb_ip)
{
    /* Only USBA module */
    if (USB_CFG_IP1 == usb_ip)
    {
        USB_M1->SYSCFG |= USB_CNEN;
    }
}

/******************************************************************************
 * End of function hw_usb_set_cnen
 ******************************************************************************/
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * Function Name   : hw_usb_clear_cnen
 * Description     : Disable single end receiver.
 * Arguments       : usb_utr_t    *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_cnen (usb_utr_t * ptr)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            USB_M1->SYSCFG = (uint16_t) (USB_M1->SYSCFG & (~USB_CNEN));
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp1->SYSCFG = (uint16_t) (ptr->ipp1->SYSCFG & (~USB_CNEN));
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_cnen
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_hse
 * Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 * Arguments       : usb_utr_t    *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_hse (usb_utr_t * ptr)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            USB_M1->SYSCFG |= USB_HSE;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP1 == ptr->ip)
        {
            ptr->ipp1->SYSCFG |= USB_HSE;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_hse
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_hse
 * Description     : Clears HSE bit of the specified port's SYSCFG register
 * Arguments       : usb_utr_t    *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_hse (usb_utr_t * ptr)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            USB_M1->SYSCFG = (uint16_t) (USB_M1->SYSCFG & (~USB_HSE));
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP1 == ptr->ip)
        {
            ptr->ipp->SYSCFG = (uint16_t) (ptr->ipp->SYSCFG & (~USB_HSE));
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
} /* End of function hw_usb_clear_hse */

/******************************************************************************
 * End of function hw_usb_clear_hse
 ******************************************************************************/
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */

/******************************************************************************
 * Function Name   : hw_usb_set_dcfm
 * Description     : DCFM-bit set of register SYSCFG
 *               : (USB Host mode is selected.)
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_dcfm (usb_utr_t * p_utr)
{
    if (USB_CFG_IP0 == p_utr->ip)
    {
        USB_M0->SYSCFG |= USB_DCFM;
    }
    else
    {
        USB_M1->SYSCFG |= USB_DCFM;
    }
}

/******************************************************************************
 * End of function hw_usb_set_dcfm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_dcfm
 * Description     : DCFM-bit clear of register SYSCFG.
 *               : (USB Peripheral mode is selected.)
 * Arguments       : usb_utr_t    *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_dcfm (usb_utr_t * ptr)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->SYSCFG = (uint16_t) (USB_M0->SYSCFG & (~USB_DCFM));
        }
        else
        {
            USB_M1->SYSCFG = (uint16_t) (USB_M1->SYSCFG & (~USB_DCFM));
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->SYSCFG = (uint16_t) (ptr->ipp->SYSCFG & (~USB_DCFM));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_dcfm
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_set_drpd
 * Description     : Set bit of the specified port's SYSCFG DRPD register.
 * Arguments       : usb_utr_t    *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_drpd (usb_utr_t * ptr)
{
    ptr->ipp->SYSCFG |= USB_DRPD;
}

/******************************************************************************
 * End of function hw_usb_clear_drpd
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_drpd
 * Description     : Clear bit of the specified port's SYSCFG DRPD register.
 *               : (for USB Host mode; Enable D + / D-line PullDown.)
 * Arguments       : usb_utr_t    *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_drpd (usb_utr_t * ptr)
{
    ptr->ipp->SYSCFG = (uint16_t) (ptr->ipp->SYSCFG & (~USB_DRPD));
}

/******************************************************************************
 * End of function hw_usb_clear_drpd
 ******************************************************************************/
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_set_usbe
 * Description     : Enable USB operation.
 * Arguments       : usb_utr_t    *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_usbe (usb_utr_t * ptr)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->SYSCFG |= USB_USBE;
        }
        else
        {
            USB_M1->SYSCFG |= USB_USBE;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->SYSCFG |= USB_USBE;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_usbe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_usbe
 * Description     : Enable USB operation.
 * Arguments       : usb_utr_t    *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_usbe (usb_utr_t * ptr)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->SYSCFG = (uint16_t) (USB_M0->SYSCFG & (~USB_USBE));
        }
        else
        {
            USB_M1->SYSCFG = (uint16_t) (USB_M1->SYSCFG & (~USB_USBE));
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->SYSCFG = (uint16_t) (ptr->ipp->SYSCFG & (~USB_USBE));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_usbe
 ******************************************************************************/

#if defined(USB_HIGH_SPEED_MODULE)
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_set_buswait
 * Description     : Set BUSWAIT register.
 * Arguments       : usb_utr_t    *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_buswait (usb_utr_t * ptr)
{
    ptr->ipp1->BUSWAIT = (USB_VALUE_0F00H | USB_CFG_BUSWAIT);
}

/******************************************************************************
 * End of function hw_usb_set_buswait
 ******************************************************************************/
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_set_bcctrl
 * Description     : Set BCCTRL's bits.
 * Arguments       : usb_utr_t     *ptr   : Pointer to usb_utr_t structure.
 *              : uint16_t      data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_bcctrl (usb_utr_t * ptr, uint16_t data)
{
    FSP_PARAMETER_NOT_USED(data);

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            USB_M1->BCCTRL |= data;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP1 == ptr->ip)
        {
            ptr->ipp1->BCCTRL |= data;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_bcctrl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_bcctrl
 * Description     : Clear BCCTRL's bits.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *              : uint16_t  data    : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_bcctrl (usb_utr_t * ptr, uint16_t data)
{
    FSP_PARAMETER_NOT_USED(data);

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            USB_M1->BCCTRL = (uint16_t) (USB_M1->BCCTRL & (~data));
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP1 == ptr->ip)
        {
            ptr->ipp1->BCCTRL = (uint16_t) (ptr->ipp1->BCCTRL & (~data));
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_bcctrl
 ******************************************************************************/
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */

/******************************************************************************
 * Function Name   : hw_usb_read_syssts
 * Description     : Returns the value of the specified port's SYSSTS register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : SYSSTS0 content
 ******************************************************************************/
uint16_t hw_usb_read_syssts (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = USB_M0->SYSSTS0;
        }
        else
        {
            result = USB_M1->SYSSTS0;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        result = (ptr->ipp->SYSSTS0);
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_syssts
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_dvstctr
 * Description     : Returns the specified port's DVSTCTR register content.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : DVSTCTR0 content
 ******************************************************************************/
uint16_t hw_usb_read_dvstctr (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = USB_M0->DVSTCTR0;
        }
        else
        {
            result = USB_M1->DVSTCTR0;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp = usb_hstd_get_usb_ip_adr(ptr->ip);
        result   = (ptr->ipp->DVSTCTR0);
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_dvstctr
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_write_dvstctr
 * Description     : Write data to the specified port's DVSTCTR register.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_dvstctr (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->DVSTCTR0 = data;
}

/******************************************************************************
 * End of function hw_usb_write_dvstctr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_rmw_dvstctr
 * Description     : Read-modify-write the specified port's DVSTCTR.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : The value to write.
 *               : uint16_t  bitptn: Bit pattern to read-modify-write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_rmw_dvstctr (usb_utr_t * ptr, uint16_t data, uint16_t bitptn)
{
    uint16_t buf;

    buf                = ptr->ipp->DVSTCTR0;
    buf                = (uint16_t) (buf & (~bitptn));
    buf               |= (data & bitptn);
    ptr->ipp->DVSTCTR0 = buf;
}

/******************************************************************************
 * End of function hw_usb_rmw_dvstctr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_dvstctr
 * Description     : Clear the bit pattern specified in argument, of the specified
 *               : port's DVSTCTR register.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  bitptn: Bit pattern to read-modify-write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_dvstctr (usb_utr_t * ptr, uint16_t bitptn)
{
    ptr->ipp->DVSTCTR0 = (uint16_t) (ptr->ipp->DVSTCTR0 & (~bitptn));
}

/******************************************************************************
 * End of function hw_usb_clear_dvstctr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_vbout
 * Description     : Set specified port's VBOUT-bit in the DVSTCTR register.
 *               : (To output a "High" to pin VBOUT.)
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_vbout (usb_utr_t * ptr)
{
 #if USB_CFG_VBUS == USB_CFG_HIGH
  #if defined(USB_CFG_OTG_USE)
    ptr->ipp->DVSTCTR0 |= USB_EXICEN;
  #endif                               /* defined(USB_CFG_OTG_USE) */
    ptr->ipp->DVSTCTR0 |= USB_VBUSEN;
 #else                                 /* USB_CFG_VBUS == USB_CFG_HIGH */
  #if defined(USB_CFG_OTG_USE)
    ptr->ipp->DVSTCTR0 = (uint16_t) (ptr->ipp->DVSTCTR0 & (~USB_EXICEN));
  #endif                               /* defined(USB_CFG_OTG_USE) */
    ptr->ipp->DVSTCTR0 = (uint16_t) (ptr->ipp->DVSTCTR0 & (~USB_VBUSEN));
 #endif                                /* USB_CFG_VBUS == USB_CFG_HIGH */
}

/******************************************************************************
 * End of function hw_usb_set_vbout
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_hnpbtoa
 * Description     : Set specified port's HNPBTOA bit in the DVSTCTR register.
 * Arguments       : usb_utr_t *p_utr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_hnpbtoa (usb_utr_t * p_utr)
{
    p_utr->ipp->DVSTCTR0 |= USB_HNPBTOA;
}

/******************************************************************************
 * End of function hw_usb_set_hnpbtoa
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_hnpbtoa
 * Description     : Clear specified port's HNPBTOA bit in the DVSTCTR register.
 * Arguments       : usb_utr_t *p_utr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_hnpbtoa (usb_utr_t * p_utr)
{
    p_utr->ipp->DVSTCTR0 = (uint16_t) (p_utr->ipp->DVSTCTR0 & (~USB_HNPBTOA));
}

/******************************************************************************
 * End of function hw_usb_clear_hnpbtoa
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_vbout
 * Description     : Clear specified port's VBOUT-bit in the DVSTCTR register.
 *               : (To output a "Low" to pin VBOUT.)
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_vbout (usb_utr_t * ptr)
{
 #if USB_CFG_VBUS == USB_CFG_HIGH
    ptr->ipp->DVSTCTR0 = (uint16_t) (ptr->ipp->DVSTCTR0 & (~USB_VBUSEN));
 #else                                 /* USB_CFG_VBUS == USB_CFG_HIGH */
    ptr->ipp->DVSTCTR0 |= USB_VBUSEN;
 #endif /* USB_CFG_VBUS == USB_CFG_HIGH */
}

/******************************************************************************
 * End of function hw_usb_clear_vbout
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if defined(USB_HIGH_SPEED_MODULE)

/******************************************************************************
 * Function Name   : hw_usb_set_utst
 * Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_utst (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            FSP_PARAMETER_NOT_USED(data);
        }
        else
        {
            USB_M1->TESTMODE = data;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp1->TESTMODE = data;
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_utst
 ******************************************************************************/
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */

#if defined(USB_HIGH_SPEED_MODULE)

/******************************************************************************
 * Function Name   : hw_usb_read_fifo32
 * Description     : Data is read from the specified pipemode's FIFO register, 32-bits
 *               : wide, corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode   : CUSE/D0DMA/D1DMA
 * Return value    : CFIFO/D0FIFO/D1FIFO content (32-bit)
 ******************************************************************************/
uint32_t hw_usb_read_fifo32 (usb_utr_t * ptr, uint16_t pipemode)
{
    uint32_t data = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    data = USB_M1->CFIFO;
                }
                else
                {
                    USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE2);
                }

                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE2);
                break;
            }
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                data = ptr->ipp1->CFIFO;
                break;
            }

            case USB_D0USE:
            {
                data = ptr->ipp1->D0FIFO;
                break;
            }

            case USB_D1USE:
            {
                data = ptr->ipp1->D1FIFO;
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE2);
                break;
            }
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return data;
}

/******************************************************************************
 * End of function hw_usb_read_fifo32
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_fifo32
 * Description     : Data is written to the specified pipemode's FIFO register, 32-bits
 *               : wide, corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 *               : uint32_t  data      : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_fifo32 (usb_utr_t * ptr, uint16_t pipemode, uint32_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    R_USB_HS0->CFIFO = data;
                }
                else
                {
                    FSP_PARAMETER_NOT_USED(data);
                    USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE2);
                }

                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE3);
                break;
            }
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                ptr->ipp1->CFIFO = data;
                break;
            }

            case USB_D0USE:
            {
                ptr->ipp1->D0FIFO = data;
                break;
            }

            case USB_D1USE:
            {
                ptr->ipp1->D1FIFO = data;
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE3);
                break;
            }
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_fifo32
 ******************************************************************************/
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */

/******************************************************************************
 * Function Name   : hw_usb_read_fifo16
 * Description     : Data is read from the specified pipemode's FIFO register, 16-bits
 *               : wide, corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 * Return value    : CFIFO/D0FIFO/D1FIFO content (16-bit)
 ******************************************************************************/
uint16_t hw_usb_read_fifo16 (usb_utr_t * ptr, uint16_t pipemode)
{
    uint16_t data = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                if (USB_IP1 == ptr->ip)
                {
                    data = USB_M1->CFIFOH;
                }
                else
                {
                    data = USB_M0->CFIFOL;
                }

                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE5);
                break;
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP0 == ptr->ip)
        {
            switch (pipemode)
            {
                case USB_CUSE:
                {
                    data = ptr->ipp->CFIFOL;
                    break;
                }

                case USB_D0USE:
                {
                    data = ptr->ipp->D0FIFOL;
                    break;
                }

                case USB_D1USE:
                {
                    data = ptr->ipp->D1FIFOL;
                    break;
                }

                default:
                {
                    USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE4);
                    break;
                }
            }
        }

 #if USB_NUM_USBIP == 2
        else if (USB_IP1 == ptr->ip)
        {
            switch (pipemode)
            {
  #if USB_CFG_ENDIAN == USB_CFG_LITTLE
                case USB_CUSE:
                {
   #if defined(USB_HIGH_SPEED_MODULE)
                    data = ptr->ipp1->CFIFOH;
   #else                               /* defined (USB_HIGH_SPEED_MODULE) */
                    data = (uint16_t) ptr->ipp1->CFIFO;
   #endif /* defined (USB_HIGH_SPEED_MODULE) */
                    break;
                }

                case USB_D0USE:
                {
   #if defined(USB_HIGH_SPEED_MODULE)
                    data = ptr->ipp1->D0FIFOH;
   #else                               /* defined (USB_HIGH_SPEED_MODULE) */
                    data = (uint16_t) ptr->ipp1->D0FIFO;
   #endif /* defined (USB_HIGH_SPEED_MODULE) */
                    break;
                }

                case USB_D1USE:
                {
   #if defined(USB_HIGH_SPEED_MODULE)
                    data = ptr->ipp1->D1FIFOH;
   #else                               /* defined (USB_HIGH_SPEED_MODULE) */
                    data = (uint16_t) ptr->ipp1->D1FIFO;
   #endif /* defined (USB_HIGH_SPEED_MODULE) */
                    break;
                }
  #else                                /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
                case USB_CUSE:
                {
   #if defined(USB_HIGH_SPEED_MODULE)
                    data = ptr->ipp1->CFIFOL;
   #else                               /* defined (USB_HIGH_SPEED_MODULE) */
                    data = (uint16_t) ptr->ipp1->CFIFO;
   #endif                              /* defined (USB_HIGH_SPEED_MODULE) */
                    break;
                }

                case USB_D0USE:
                {
   #if defined(USB_HIGH_SPEED_MODULE)
                    data = ptr->ipp1->D0FIFOL;
   #else                               /* defined (USB_HIGH_SPEED_MODULE) */
                    data = (uint16_t) ptr->ipp1->D0FIFO;
   #endif                              /* defined (USB_HIGH_SPEED_MODULE) */
                    break;
                }

                case USB_D1USE:
                {
   #if defined(USB_HIGH_SPEED_MODULE)
                    data = ptr->ipp1->D1FIFOL;
   #else                               /* defined (USB_HIGH_SPEED_MODULE) */
                    data = (uint16_t) ptr->ipp1->D1FIFO;
   #endif                              /* defined (USB_HIGH_SPEED_MODULE) */
                    break;
                }
  #endif  /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

                default:
                {
                    USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE5);
                    break;
                }
            }
        }
 #endif                                /* USB_NUM_USBIP == 2 */
        else
        {
            /* None */
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return data;
}

/******************************************************************************
 * End of function hw_usb_read_fifo16
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_fifo16
 * Description     : Data is written to the specified pipemode's FIFO register, 16-bits
 *               : wide, corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 *               : uint16_t  data      : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_fifo16 (usb_utr_t * ptr, uint16_t pipemode, uint16_t data)
{
    uint16_t ip = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            ip = USB_IP1;
        }
        else
        {
            ip = USB_IP0;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ip = ptr->ip;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    if (USB_IP0 == ip)
    {
        switch (pipemode)
        {
            case USB_CUSE:
            {
                USB0_CFIFO16 = data;
                break;
            }

            case USB_D0USE:
            {
                USB0_D0FIFO16 = data;
                break;
            }

            case USB_D1USE:
            {
                USB0_D1FIFO16 = data;
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE6);
                break;
            }
        }
    }

#if USB_NUM_USBIP == 2
    else if (USB_IP1 == ip)
    {
        switch (pipemode)
        {
            case USB_CUSE:
            {
                USB1_CFIFO16 = data;
                break;
            }

            case USB_D0USE:
            {
                USB1_D0FIFO16 = data;
                break;
            }

            case USB_D1USE:
            {
                USB1_D1FIFO16 = data;
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE7);
                break;
            }
        }
    }
#endif                                 /* USB_NUM_USBIP == 2 */
    else
    {
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE8);
    }
}

/******************************************************************************
 * End of function hw_usb_write_fifo16
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_fifo8
 * Description     : Data is written to the specified pipemode's FIFO register, 8-bits
 *               : wide, corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 *               : uint8_t  data       : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_fifo8 (usb_utr_t * ptr, uint16_t pipemode, uint8_t data)
{
    uint16_t ip = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            ip = USB_IP1;
        }
        else
        {
            ip = USB_IP0;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ip = ptr->ip;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    if (USB_IP0 == ip)
    {
        switch (pipemode)
        {
            case USB_CUSE:
            {
                USB0_CFIFO8 = data;
                break;
            }

            case USB_D0USE:
            {
                USB0_D0FIFO8 = data;
                break;
            }

            case USB_D1USE:
            {
                USB0_D1FIFO8 = data;
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE9);
                break;
            }
        }
    }

#if USB_NUM_USBIP == 2
    else if (USB_IP1 == ip)
    {
        switch (pipemode)
        {
            case USB_CUSE:
            {
                USB1_CFIFO8 = data;
                break;
            }

            case USB_D0USE:
            {
                USB1_D0FIFO8 = data;
                break;
            }

            case USB_D1USE:
            {
                USB1_D1FIFO8 = data;
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE10);
                break;
            }
        }
    }
#endif                                 /* USB_NUM_USBIP == 2 */
    else
    {
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE11);
    }
}

/******************************************************************************
 * End of function hw_usb_write_fifo8
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_get_fifosel_adr
 * Description     : Returns the *address* of the FIFOSEL register corresponding to
 *               : specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
static void * hw_usb_get_fifosel_adr (usb_utr_t * ptr, uint16_t pipemode)
{
    void * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    p_reg = (void *) &(USB_M1->CFIFOSEL);
                }
                else
                {
                    p_reg = (void *) &(USB_M0->CFIFOSEL);
                }

                break;
            }

            case USB_D0USE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    p_reg = (void *) &(USB_M1->D0FIFOSEL);
                }
                else
                {
                    p_reg = (void *) &(USB_M0->D0FIFOSEL);
                }

                break;
            }

            case USB_D1USE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    p_reg = (void *) &(USB_M1->D1FIFOSEL);
                }
                else
                {
                    p_reg = (void *) &(USB_M0->D1FIFOSEL);
                }

                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE12);
                break;
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                p_reg = (void *) &(ptr->ipp->CFIFOSEL);
                break;
            }

            case USB_D0USE:
            {
                p_reg = (void *) &(ptr->ipp->D0FIFOSEL);
                break;
            }

            case USB_D1USE:
            {
                p_reg = (void *) &(ptr->ipp->D1FIFOSEL);
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE12);
                break;
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return p_reg;
}

/******************************************************************************
 * End of function hw_usb_get_fifosel_adr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_fifosel
 * Description     : Returns the value of the specified pipemode's FIFOSEL register.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 * Return value    : FIFOSEL content
 ******************************************************************************/
uint16_t hw_usb_read_fifosel (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = (uint16_t *) hw_usb_get_fifosel_adr(ptr, pipemode);

    return *p_reg;
}

/******************************************************************************
 * End of function hw_usb_read_fifosel
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_rmw_fifosel
 * Description     : Data is written to the specified pipemode's FIFOSEL register
 *               : (the FIFOSEL corresponding to the specified PIPEMODE), using
 *               : read-modify-write.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 *               : uint16_t  data      : Setting value
 *               : uint16_t bitptn   : bitptn: Bit pattern to read-modify-write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_rmw_fifosel (usb_utr_t * ptr, uint16_t pipemode, uint16_t data, uint16_t bitptn)
{
    uint16_t            buf;
    volatile uint16_t * p_reg = 0;

    p_reg = (uint16_t *) hw_usb_get_fifosel_adr(ptr, pipemode);

    buf    = *p_reg;
    buf    = (uint16_t) (buf & (~bitptn));
    buf   |= (data & bitptn);
    *p_reg = buf;
}

/******************************************************************************
 * End of function hw_usb_rmw_fifosel
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_dclrm
 * Description     : Set DCLRM-bits (FIFO buffer auto clear) of the FIFOSEL cor-
 *               : responding to specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_dclrm (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = (uint16_t *) hw_usb_get_fifosel_adr(ptr, pipemode);

    (*p_reg) |= USB_DCLRM;
}

/******************************************************************************
 * End of function hw_usb_set_dclrm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_dclrm
 * Description     : Reset DCLRM-bits (FIFO buffer not auto-cleared) of the FIFOSEL
 *               : corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_dclrm (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = hw_usb_get_fifosel_adr(ptr, pipemode);

    (*p_reg) = (uint16_t) ((*p_reg) & (~USB_DCLRM));
}

/******************************************************************************
 * End of function hw_usb_clear_dclrm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_dreqe
 * Description     : Set DREQE-bits (to output signal DxREQ_Na) of the FIFOSEL cor-
 *               : responding to specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_dreqe (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = hw_usb_get_fifosel_adr(ptr, pipemode);

    if (true == usb_check_use_usba_module(ptr))
    {
        (*p_reg) = (uint16_t) ((*p_reg) & (uint16_t) (~(USB_DREQE | USB_CURPIPE)));

        /* WAIT_LOOP */
        while (0 != ((*p_reg) & USB_CURPIPE))
        {
            /* Wait Clear CURPIPE */
        }
    }
    else
    {
        (*p_reg) = (uint16_t) ((*p_reg) & (~USB_DREQE));
    }

    (*p_reg) |= USB_DREQE;
}

/******************************************************************************
 * End of function hw_usb_set_dreqe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_dreqe
 * Description     : Clear DREQE-bits (To prohibit the output of the signal DxREQ_N)
 *               : of the FIFOSEL corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode  : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_dreqe (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = hw_usb_get_fifosel_adr(ptr, pipemode);

    (*p_reg) = (uint16_t) ((*p_reg) & (~USB_DREQE));
}

/******************************************************************************
 * End of function hw_usb_clear_dreqe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_mbw
 * Description     : Set MBW-bits (CFIFO Port Access Bit Width) of the FIFOSEL cor-
 *               : responding to the specified PIPEMODE, to select 8 or 16-bit
 *               : wide FIFO port access.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode   : CUSE/D0DMA/D1DMA
 *               : uint16_t  data       : Setting value
 *               : (data = 0x0400), 32 bit (data = 0x0800) access mode.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_mbw (usb_utr_t * ptr, uint16_t pipemode, uint16_t data)
{
    volatile uint16_t * p_reg = 0;

    p_reg = hw_usb_get_fifosel_adr(ptr, pipemode);

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        (*p_reg) = (uint16_t) ((*p_reg) & (~USB_MBW));
        if (0 != data)
        {
            (*p_reg) |= data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP0 == ptr->ip)
        {
            if (0 != data)
            {
                (*p_reg) |= USB_MBW_16;
            }
            else
            {
                (*p_reg) = (uint16_t) ((*p_reg) & (~USB_MBW_16));
            }
        }
        else if (USB_IP1 == ptr->ip)
        {
            (*p_reg) = (uint16_t) ((*p_reg) & (~USB_MBW));

            if (0 != data)
            {
                (*p_reg) |= data;
            }
        }
        else
        {
            /* None */
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_mbw
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_curpipe
 * Description     : Set pipe to the number given; in the FIFOSEL corresponding
 *               : to specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode   : CUSE/D0DMA/D1DMA
 *               : uint16_t  pipeno     : Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_curpipe (usb_utr_t * ptr, uint16_t pipemode, uint16_t pipeno)
{
    volatile uint16_t * p_reg = 0;
    volatile uint16_t   reg;

    p_reg = hw_usb_get_fifosel_adr(ptr, pipemode);
    reg   = *p_reg;

    if ((USB_D0USE == pipemode) || (USB_D1USE == pipemode))
    {
        if (false == usb_check_use_usba_module(ptr))
        {
            reg = (uint16_t) (reg & (~USB_DREQE));
        }
    }

    reg    = (uint16_t) (reg & (~USB_CURPIPE));
    *p_reg = reg;

    /* WAIT_LOOP */
    while (0 != ((*p_reg) & USB_CURPIPE))
    {
        /* Wait Clear CURPIPE */
    }

    reg |= pipeno;

    *p_reg = reg;
}

/******************************************************************************
 * End of function hw_usb_set_curpipe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_get_fifoctr_adr
 * Description     : Returns the *address* of the FIFOCTR register corresponding to
 *               : specified PIPEMODE.
 *               : (FIFO Port Control Register.)
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode   : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
static void * hw_usb_get_fifoctr_adr (usb_utr_t * ptr, uint16_t pipemode)
{
    void * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    p_reg = (void *) &(USB_M1->CFIFOCTR);
                }
                else
                {
                    p_reg = (void *) &(USB_M0->CFIFOCTR);
                }

                break;
            }

            case USB_D0USE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    p_reg = (void *) &(USB_M1->D0FIFOCTR);
                }
                else
                {
                    p_reg = (void *) &(USB_M0->D0FIFOCTR);
                }

                break;
            }

            case USB_D1USE:
            {
                if (USB_CFG_IP1 == ptr->ip)
                {
                    p_reg = (void *) &(USB_M1->D1FIFOCTR);
                }
                else
                {
                    p_reg = (void *) &(USB_M0->D1FIFOCTR);
                }

                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE13);
                break;
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        switch (pipemode)
        {
            case USB_CUSE:
            {
                p_reg = (void *) &(ptr->ipp->CFIFOCTR);
                break;
            }

            case USB_D0USE:
            {
                p_reg = (void *) &(ptr->ipp->D0FIFOCTR);
                break;
            }

            case USB_D1USE:
            {
                p_reg = (void *) &(ptr->ipp->D1FIFOCTR);
                break;
            }

            default:
            {
                USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE13);
                break;
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return p_reg;
}

/******************************************************************************
 * End of function hw_usb_get_fifoctr_adr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_fifoctr
 * Description     : Returns the value of the FIFOCTR register corresponding to
 *               : specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode   : CUSE/D0DMA/D1DMA
 * Return value    : FIFOCTR content
 ******************************************************************************/
uint16_t hw_usb_read_fifoctr (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = (uint16_t *) hw_usb_get_fifoctr_adr(ptr, pipemode);

    return *p_reg;
}

/******************************************************************************
 * End of function hw_usb_read_fifoctr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_bval
 * Description     : Set BVAL (Buffer Memory Valid Flag) to the number given; in
 *               : the FIFOCTR corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode   : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_bval (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = (uint16_t *) hw_usb_get_fifoctr_adr(ptr, pipemode);

    (*p_reg) |= USB_BVAL;
}

/******************************************************************************
 * End of function hw_usb_set_bval
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_bclr
 * Description     : Set BCLR (CPU Buffer Clear) to the number given; in the
 *               : FIFOCTR corresponding to the specified PIPEMODE.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipemode   : CUSE/D0DMA/D1DMA
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_bclr (usb_utr_t * ptr, uint16_t pipemode)
{
    volatile uint16_t * p_reg = 0;

    p_reg = (uint16_t *) hw_usb_get_fifoctr_adr(ptr, pipemode);

    *p_reg = USB_BCLR;
}

/******************************************************************************
 * End of function hw_usb_set_bclr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_intenb
 * Description     : Data is written to INTENB register,
 *               : enabling/disabling the various USB interrupts.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_intenb (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->INTENB0 = data;
        }
        else
        {
            USB_M1->INTENB0 = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->INTENB0 = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_intenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_intenb
 * Description     : Bit(s) to be set in INTENB register,
 *               : enabling the respective USB interrupt(s).
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : Bit pattern: Respective interrupts with '1'
 *               :                   will be enabled.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_intenb (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->INTENB0 |= data;
        }
        else
        {
            USB_M1->INTENB0 |= data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->INTENB0 |= data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_intenb
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_clear_enb_vbse
 * Description     : Clear the VBE-bit of INTENB register,
 *               : to prohibit VBUS interrupts.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_enb_vbse (usb_utr_t * ptr)
{
    ptr->ipp->INTENB0 = (uint16_t) (ptr->ipp->INTENB0 & (~USB_VBSE));
}

/******************************************************************************
 * End of function hw_usb_clear_enb_vbse
 ******************************************************************************/

/******************************************************************************
 * Description     : Clear the SOFE-bit of INTENB register,
 * : to prohibit Frame Number Update interrupts.
 * Function Name   : hw_usb_clear_enb_sofe
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_enb_sofe (usb_utr_t * ptr)
{
    ptr->ipp->INTENB0 = (uint16_t) (ptr->ipp->INTENB0 & (~USB_SOFE));
}

/******************************************************************************
 * End of function hw_usb_clear_enb_sofe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_brdyenb
 * Description     : Data is written to BRDYENB register,
 *               : enabling/disabling each respective pipe's BRDY interrupt.
 *               : (The BRDY interrupt indicates that a FIFO port is accessible.)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_brdyenb (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->BRDYENB = data;
}

/******************************************************************************
 * End of function hw_usb_write_brdyenb
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_set_brdyenb
 * Description     : A bit is set in the specified pipe's BRDYENB, enabling the
 *               : respective pipe BRDY interrupt(s).
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_brdyenb (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->BRDYENB = (uint16_t) (USB_M0->BRDYENB | (1 << pipeno));
        }
        else
        {
            USB_M1->BRDYENB = (uint16_t) (USB_M1->BRDYENB | (1 << pipeno));
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->BRDYENB = (uint16_t) (ptr->ipp->BRDYENB | (1 << pipeno));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_brdyenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_brdyenb
 * Description     : Clear the PIPExBRDYE-bit of the specified pipe to prohibit
 *               : BRDY interrupts of that pipe.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_brdyenb (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->BRDYENB = (uint16_t) (USB_M0->BRDYENB & (~(1 << pipeno)));
        }
        else
        {
            USB_M1->BRDYENB = (uint16_t) (USB_M1->BRDYENB & (~(1 << pipeno)));
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->BRDYENB = (uint16_t) (ptr->ipp->BRDYENB & (~(1 << pipeno)));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_brdyenb
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_write_nrdyenb
 * Description     : Data is written to NRDYENB register,
 *               : enabling/disabling each respective pipe's NRDY interrupt
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_nrdyenb (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->NRDYENB = data;
}

/******************************************************************************
 * End of function hw_usb_write_nrdyenb
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_set_nrdyenb
 * Description     : A bit is set in the specified pipe's NRDYENB, enabling the
 *               : respective pipe NRDY interrupt(s).
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_nrdyenb (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->NRDYENB = (uint16_t) (USB_M0->NRDYENB | (1 << pipeno));
        }
        else
        {
            USB_M1->NRDYENB = (uint16_t) (USB_M1->NRDYENB | (1 << pipeno));
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->NRDYENB = (uint16_t) (ptr->ipp->NRDYENB | (1 << pipeno));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_nrdyenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_nrdyenb
 * Description     : Clear the PIPExNRDYE-bit of the specified pipe to prohibit
 *               : NRDY interrupts of that pipe.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_nrdyenb (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->NRDYENB = (uint16_t) (USB_M0->NRDYENB & (~(1 << pipeno)));
        }
        else
        {
            USB_M1->NRDYENB = (uint16_t) (USB_M1->NRDYENB & (~(1 << pipeno)));
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->NRDYENB = (uint16_t) (ptr->ipp->NRDYENB & (~(1 << pipeno)));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_nrdyenb
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_write_bempenb
 * Description     : Data is written to BEMPENB register,
 *               : enabling/disabling each respective pipe's BEMP interrupt.
 *               : (The BEMP interrupt indicates that the USB buffer is empty,
 *               : and so the FIFO can now be written to.)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_bempenb (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->BEMPENB = data;
}

/******************************************************************************
 * End of function hw_usb_write_bempenb
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_set_bempenb
 * Description     : A bit is set in the specified pipe's BEMPENB enabling the
 *               : respective pipe's BEMP interrupt(s).
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno  : Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_bempenb (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            g_usb_cstd_bemp_skip[USB_IP0][pipeno] = USB_OFF;
            USB_M0->BEMPENB = (uint16_t) (USB_M0->BEMPENB | (1 << pipeno));
        }

 #if USB_NUM_USBIP == 2
        else
        {
            g_usb_cstd_bemp_skip[USB_IP1][pipeno] = USB_OFF;
            USB_M1->BEMPENB = (uint16_t) (USB_M1->BEMPENB | (1 << pipeno));
        }
 #endif                                /* USB_NUM_USBIP == 2 */
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        g_usb_cstd_bemp_skip[ptr->ip][pipeno] = USB_OFF;
        ptr->ipp->BEMPENB = (uint16_t) (ptr->ipp->BEMPENB | (1 << pipeno));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_bempenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_bempenb
 * Description     : Clear the PIPExBEMPE-bit of the specified pipe to prohibit
 *               : BEMP interrupts of that pipe.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_bempenb (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->BEMPENB = (uint16_t) (USB_M0->BEMPENB & (~(1 << pipeno)));
        }
        else
        {
            USB_M1->BEMPENB = (uint16_t) (USB_M1->BEMPENB & (~(1 << pipeno)));
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->BEMPENB = (uint16_t) (ptr->ipp->BEMPENB & (~(1 << pipeno)));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_bempenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_sofcfg
 * Description     : Set Bit pattern for SOFCFG
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : The value to OR.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_sofcfg (usb_utr_t * ptr, uint16_t data)
{
    FSP_PARAMETER_NOT_USED(data);
    FSP_PARAMETER_NOT_USED(*ptr);
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
 #if USB_NUM_USBIP == 2
        if (USB_IP1 == ptr->ip)
        {
            ptr->ipp1->SOFCFG |= data;
        }
 #endif                                /* USB_NUM_USBIP == 2 */
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_sofcfg
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : hw_usb_read_intsts
 * Description     : Returns INTSTS0 register content.
 * Arguments       : none
 * Return value    : INTSTS0 content
 ******************************************************************************/
uint16_t hw_usb_read_intsts (uint8_t usb_ip)
{
    if (USB_CFG_IP0 == usb_ip)
    {
        return USB_M0->INTSTS0;
    }
    else
    {
        return USB_M1->INTSTS0;
    }
}

/******************************************************************************
 * End of function hw_usb_read_intsts
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * Function Name   : hw_usb_write_intsts
 * Description     : Data is written to INTSTS0 register.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_intsts (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->INTSTS0 = data;
        }
        else
        {
            USB_M1->INTSTS0 = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->INTSTS0 = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_intsts
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_clear_sts_sofr
 * Description     : Clear the SOFR-bit (Frame Number Refresh Interrupt Status) of
 *               : the clear SOF interrupt status.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_sts_sofr (usb_utr_t * ptr)
{
    ptr->ipp->INTSTS0 = (uint16_t) ~USB_SOFR;
}

/******************************************************************************
 * End of function hw_usb_clear_sts_sofr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_brdysts
 * Description     : Returns BRDYSTS register content.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : BRDYSTS content
 ******************************************************************************/
uint16_t hw_usb_read_brdysts (usb_utr_t * ptr)
{
    return ptr->ipp->BRDYSTS;
}

/******************************************************************************
 * End of function hw_usb_read_brdysts
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_brdysts
 * Description     : Data is written to BRDYSTS register, to set the BRDY interrupt status.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_brdysts (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->BRDYSTS = data;
}                                      /* End of function hw_usb_write_brdysts() */

/******************************************************************************
 * End of function hw_usb_write_brdysts
 ******************************************************************************/
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_clear_sts_brdy
 * Description     : Clear the PIPExBRDY status bit of the specified pipe to clear
 *               : its BRDY interrupt status.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno: Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_sts_brdy (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->BRDYSTS = (uint16_t) (~(1 << pipeno)) & BRDYSTS_MASK;
        }
        else
        {
            USB_M1->BRDYSTS = (uint16_t) (~(1 << pipeno)) & BRDYSTS_MASK;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->BRDYSTS = (uint16_t) (~(1 << pipeno)) & BRDYSTS_MASK;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_sts_brdy
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_write_nrdy_sts
 * Description     : Data is written to NRDYSTS register, to
 *               : set the NRDY interrupt status.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_nrdy_sts (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->NRDYSTS = data;
}

/******************************************************************************
 * End of function hw_usb_clear_status_nrdy
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_clear_status_nrdy
 * Description     : Clear the PIPExNRDY status bit of the specified pipe to clear
 *               : its NRDY interrupt status.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno: Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_status_nrdy (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->NRDYSTS = (uint16_t) ((uint16_t) (~(1 << pipeno)) & NRDYSTS_MASK);
        }
        else
        {
            USB_M1->NRDYSTS = (uint16_t) ((uint16_t) (~(1 << pipeno)) & NRDYSTS_MASK);
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->NRDYSTS = (uint16_t) (~(1 << pipeno)) & NRDYSTS_MASK;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_status_nrdy
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_write_bempsts
 * Description     : Data is written to BEMPSTS register, to set the BEMP interrupt status.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  data  : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_bempsts (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->BEMPSTS = data;
}

/******************************************************************************
 * End of function hw_usb_write_bempsts
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_clear_status_bemp
 * Description     : Clear the PIPExBEMP status bit of the specified pipe to clear
 *               : its BEMP interrupt status.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno: Pipe number.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_status_bemp (usb_utr_t * ptr, uint16_t pipeno)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->BEMPSTS = (uint16_t) ((uint16_t) (~(1 << pipeno)) & BEMPSTS_MASK);
        }
        else
        {
            USB_M1->BEMPSTS = (uint16_t) ((uint16_t) (~(1 << pipeno)) & BEMPSTS_MASK);
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->BEMPSTS = (uint16_t) (~(1 << pipeno)) & BEMPSTS_MASK;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_status_bemp
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_frmnum
 * Description     : Returns FRMNUM register content.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : FRMNUM content
 ******************************************************************************/
uint16_t hw_usb_read_frmnum (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = USB_M0->FRMNUM;
        }
        else
        {
            result = USB_M1->FRMNUM;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        result = ptr->ipp->FRMNUM;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_frmnum
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Function Name   : hw_usb_read_usbreq
 * Description     : Returns USBREQ register content.
 * Arguments       : none
 * Return value    : USBREQ content
 ******************************************************************************/
uint16_t hw_usb_read_usbreq (uint8_t usb_ip)
{
    uint16_t result = 0;

    if (USB_CFG_IP0 == usb_ip)
    {
        result = USB_M0->USBREQ;
    }
    else
    {
        result = USB_M1->USBREQ;
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_usbreq
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_usbval
 * Description     : Returns USBVAL register content.
 * Arguments       : none
 * Return value    : USBVAL content
 ******************************************************************************/
uint16_t hw_usb_read_usbval (uint8_t usb_ip)
{
    uint16_t result = 0;

    if (USB_CFG_IP0 == usb_ip)
    {
        result = USB_M0->USBVAL;
    }
    else
    {
        result = USB_M1->USBVAL;
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_usbval
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_usbindx
 * Description     : Returns USBINDX register content.
 * Arguments       : none
 * Return value    : USBINDX content
 ******************************************************************************/
uint16_t hw_usb_read_usbindx (uint8_t usb_ip)
{
    uint16_t result = 0;

    if (USB_CFG_IP0 == usb_ip)
    {
        result = USB_M0->USBINDX;
    }
    else
    {
        result = USB_M1->USBINDX;
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_usbindx
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_usbleng
 * Description     : Returns USBLENG register content.
 * Arguments       : none
 * Return value    : USBLENG content
 ******************************************************************************/
uint16_t hw_usb_read_usbleng (uint8_t usb_ip)
{
    uint16_t result = 0;

    if (USB_CFG_IP0 == usb_ip)
    {
        result = USB_M0->USBLENG;
    }
    else
    {
        result = USB_M1->USBLENG;
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_usbleng
 ******************************************************************************/
#else
 #if defined(USB_CFG_HUVC_USE)

/******************************************************************************
 * Function Name   : hw_usb_read_usbreq
 * Description     : Returns USBREQ register content.
 * Arguments       : none
 * Return value    : USBREQ content
 ******************************************************************************/
uint16_t hw_usb_read_usbreq (uint8_t usb_ip)
{
    uint16_t result = 0;

    if (USB_CFG_IP0 == usb_ip)
    {
        result = USB_M0->USBREQ;
    }
    else
    {
        result = USB_M1->USBREQ;
    }

    return result;
}

 #endif
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * Function Name   : hw_usb_read_dcpcfg
 * Description     : Returns DCPCFG register content.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 * Return value    : DCPCFG content
 ******************************************************************************/
uint16_t hw_usb_read_dcpcfg (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = USB_M0->DCPCFG;
        }
        else
        {
            result = USB_M1->DCPCFG;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        result = ptr->ipp->DCPCFG;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_dcpcfg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_dcpcfg
 * Description     : Specified data is written to DCPCFG register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_dcpcfg (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->DCPCFG = data;
        }
        else
        {
            USB_M1->DCPCFG = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->DCPCFG = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_dcpcfg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_dcpmaxp
 * Description     : Returns DCPMAXP register content.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : DCPMAXP content
 ******************************************************************************/
uint16_t hw_usb_read_dcpmaxp (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = USB_M0->DCPMAXP;
        }
        else
        {
            result = USB_M1->DCPMAXP;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        result = ptr->ipp->DCPMAXP;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_dcpmaxp
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_dcpmxps
 * Description     : Specified data is written to DCPMAXP register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_dcpmxps (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->DCPMAXP = data;
        }
        else
        {
            USB_M1->DCPMAXP = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->DCPMAXP = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_dcpmxps
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Function Name   : hw_usb_read_dcpctr
 * Description     : Returns DCPCTR register content.
 * Arguments       : none
 * Return value    : DCPCTR content
 ******************************************************************************/
uint16_t hw_usb_read_dcpctr (uint8_t usb_ip)
{
    uint16_t result;

    if (USB_CFG_IP0 == usb_ip)
    {
        result = USB_M0->DCPCTR;
    }
    else
    {
        result = USB_M1->DCPCTR;
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_dcpctr
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * Function Name   : hw_usb_write_pipesel
 * Description     : Specified data is written to PIPESEL register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_pipesel (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->PIPESEL = data;
        }
        else
        {
            USB_M1->PIPESEL = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->PIPESEL = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_pipesel
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_pipecfg
 * Description     : Returns PIPECFG register content.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : PIPECFG content
 ******************************************************************************/
uint16_t hw_usb_read_pipecfg (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = USB_M0->PIPECFG;
        }
        else
        {
            result = USB_M1->PIPECFG;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        result = ptr->ipp->PIPECFG;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_pipecfg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_pipecfg
 * Description     : Specified data is written to PIPECFG register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_pipecfg (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->PIPECFG = data;
        }
        else
        {
            USB_M1->PIPECFG = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->PIPECFG = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_pipecfg
 ******************************************************************************/

#if defined(USB_HIGH_SPEED_MODULE)

/******************************************************************************
 * Function Name   : hw_usb_write_pipebuf
 * Description     : Specified the value by 2nd argument is set to PIPEBUF register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_pipebuf (usb_utr_t * ptr, uint16_t data)
{
    FSP_PARAMETER_NOT_USED(data);
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            USB_M1->PIPEBUF = data;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP1 == ptr->ip)
        {
            ptr->ipp1->PIPEBUF = data;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_pipebuf
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_pipebuf
 * Description     : Returns PIPECFG register content.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : PIPEBUF content
 ******************************************************************************/
uint16_t hw_usb_read_pipebuf (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = 0;
        }
        else
        {
            result = USB_M1->PIPEBUF;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP1 == ptr->ip)
        {
            result = ptr->ipp1->PIPEBUF;
        }
        else
        {
            result = 0;
        }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_pipebuf
 ******************************************************************************/

#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */

/******************************************************************************
 * Function Name   : hw_usb_read_pipemaxp
 * Description     : Returns PIPEMAXP register content.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : PIPEMAXP content
 ******************************************************************************/
uint16_t hw_usb_read_pipemaxp (usb_utr_t * ptr)
{
    uint16_t result = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            result = USB_M0->PIPEMAXP;
        }
        else
        {
            result = USB_M1->PIPEMAXP;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        result = ptr->ipp->PIPEMAXP;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_read_pipemaxp
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_pipemaxp
 * Description     : Specified data is written to PIPEMAXP register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_pipemaxp (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->PIPEMAXP = data;
        }
        else
        {
            USB_M1->PIPEMAXP = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->PIPEMAXP = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_pipemaxp
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_pipeperi
 * Description     : Specified data is written to PIPEPERI register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_pipeperi (usb_utr_t * ptr, uint16_t data)
{
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            USB_M0->PIPEPERI = data;
        }
        else
        {
            USB_M1->PIPEPERI = data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        ptr->ipp->PIPEPERI = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_pipeperi
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_read_pipectr
 * Description     : Returns DCPCTR or the specified pipe's PIPECTR register content.
 *               : The Pipe Control Register returned is determined by the speci-
 *               : fied pipe number.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number.
 * Return value    : PIPExCTR content
 ******************************************************************************/
uint16_t hw_usb_read_pipectr (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg;
    volatile uint16_t   reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            if (USB_PIPE0 == pipeno)
            {
                p_reg = (uint16_t *) &(USB_M0->DCPCTR);
            }
            else
            {
                p_reg = (uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1);
            }

            reg = *p_reg;
        }
        else
        {
            if (USB_PIPE0 == pipeno)
            {
                p_reg = (uint16_t *) &(USB_M1->DCPCTR);
            }
            else
            {
                p_reg = (uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1);
            }

            reg = *p_reg;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_PIPE0 == pipeno)
        {
            p_reg = (uint16_t *) &(ptr->ipp->DCPCTR);
        }
        else
        {
            p_reg = (uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1);
        }
        reg = *p_reg;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    return reg;
}

/******************************************************************************
 * End of function hw_usb_read_pipectr
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : hw_usb_write_pipectr
 * Description     : Specified data is written to the specified pipe's PIPEPERI register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_pipectr (usb_utr_t * ptr, uint16_t pipeno, uint16_t data)
{
    volatile uint16_t * p_reg;

    if (USB_PIPE0 == pipeno)
    {
        p_reg = (uint16_t *) &(ptr->ipp->DCPCTR);
    }
    else
    {
        p_reg = (uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1);
    }

    *p_reg = data;
}

/******************************************************************************
 * End of function hw_usb_write_pipectr
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : hw_usb_set_csclr
 * Description     : Set CSCLR bit in the specified pipe's PIPECTR register
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_csclr (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            p_reg = (uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1);
        }
        else
        {
            p_reg = (uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1);
        }
        (*p_reg) |= USB_CSCLR;
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_reg     = (uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1);
        (*p_reg) |= USB_CSCLR;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_csclr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_aclrm
 * Description     : The ACLRM-bit (Auto Buffer Clear Mode) is set in the specified
 *               : pipe's control register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_aclrm (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            p_reg     = (uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1);
            (*p_reg) |= USB_ACLRM;
        }
        else
        {
            p_reg     = (uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1);
            (*p_reg) |= USB_ACLRM;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_reg     = (uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1);
        (*p_reg) |= USB_ACLRM;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_aclrm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_aclrm
 * Description     : Clear the ACLRM bit in the specified pipe's control register
 *               : to disable Auto Buffer Clear Mode.
 *               : its BEMP interrupt status.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_aclrm (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            p_reg = (uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1);
        }
        else
        {
            p_reg = (uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1);
        }
        (*p_reg) = (uint16_t) ((*p_reg) & (~USB_ACLRM));
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_reg    = (uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1);
        (*p_reg) = (uint16_t) ((*p_reg) & (~USB_ACLRM));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_aclrm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_sqclr
 * Description     : The SQCLR-bit (Toggle Bit Clear) is set in the specified pipe's
 *               : control register. Setting SQSET to 1 makes DATA0 the expected
 *               : data in the pipe's next transfer.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_sqclr (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            if (USB_PIPE0 == pipeno)
            {
                USB_M0->DCPCTR |= USB_SQCLR;
            }
            else
            {
                p_reg     = ((uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1));
                (*p_reg) |= USB_SQCLR;
            }
        }
        else
        {
            if (USB_PIPE0 == pipeno)
            {
                USB_M1->DCPCTR |= USB_SQCLR;
            }
            else
            {
                p_reg     = ((uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1));
                (*p_reg) |= USB_SQCLR;
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_PIPE0 == pipeno)
        {
            ptr->ipp->DCPCTR |= USB_SQCLR;
        }
        else
        {
            p_reg     = ((uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1));
            (*p_reg) |= USB_SQCLR;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_sqclr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_sqset
 * Description     : The SQSET-bit (Toggle Bit Set) is set in the specified pipe's
 *               : control register. Setting SQSET to 1 makes DATA1 the expected
 *               : data in the next transfer.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_sqset (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            if (USB_PIPE0 == pipeno)
            {
                USB_M0->DCPCTR |= USB_SQSET;
            }
            else
            {
                p_reg     = ((uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1));
                (*p_reg) |= USB_SQSET;
            }
        }
        else
        {
            if (USB_PIPE0 == pipeno)
            {
                USB_M1->DCPCTR |= USB_SQSET;
            }
            else
            {
                p_reg     = ((uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1));
                (*p_reg) |= USB_SQSET;
            }
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_PIPE0 == pipeno)
        {
            ptr->ipp->DCPCTR |= USB_SQSET;
        }
        else
        {
            p_reg     = ((uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1));
            (*p_reg) |= USB_SQSET;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_sqset
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_pid
 * Description     : Set the specified PID of the specified pipe's DCPCTR/PIPECTR
 *               : register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 *               : uint16_t  data   : NAK/BUF/STALL.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_pid (usb_utr_t * ptr, uint16_t pipeno, uint16_t data)
{
    volatile uint16_t * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            if (USB_PIPE0 == pipeno)
            {
                p_reg = ((uint16_t *) &(USB_M0->DCPCTR));
            }
            else
            {
                p_reg = ((uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1));
            }

            (*p_reg)  = (uint16_t) ((*p_reg) & (~USB_PID));
            (*p_reg) |= data;
        }
        else
        {
            if (USB_PIPE0 == pipeno)
            {
                p_reg = ((uint16_t *) &(USB_M1->DCPCTR));
            }
            else
            {
                p_reg = ((uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1));
            }

            (*p_reg)  = (uint16_t) ((*p_reg) & (~USB_PID));
            (*p_reg) |= data;
        }
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_PIPE0 == pipeno)
        {
            p_reg = ((uint16_t *) &(ptr->ipp->DCPCTR));
        }
        else
        {
            p_reg = ((uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1));
        }

        (*p_reg)  = (uint16_t) ((*p_reg) & (~USB_PID));
        (*p_reg) |= data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_pid
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_pid
 * Description     : Clear the specified PID-bits of the specified pipe's DCPCTR/
 *               : PIPECTR register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 *               : uint16_t  data  : NAK/BUF/STALL - to be cleared.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_pid (usb_utr_t * ptr, uint16_t pipeno, uint16_t data)
{
    volatile uint16_t * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            if (USB_PIPE0 == pipeno)
            {
                p_reg = ((uint16_t *) &(USB_M0->DCPCTR));
            }
            else
            {
                p_reg = ((uint16_t *) &(USB_M0->PIPE_CTR[0]) + (pipeno - 1));
            }
        }
        else
        {
            if (USB_PIPE0 == pipeno)
            {
                p_reg = ((uint16_t *) &(USB_M1->DCPCTR));
            }
            else
            {
                p_reg = ((uint16_t *) &(USB_M1->PIPE_CTR[0]) + (pipeno - 1));
            }
        }
        (*p_reg) = (uint16_t) ((*p_reg) & (~data));
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_PIPE0 == pipeno)
        {
            p_reg = ((uint16_t *) &(ptr->ipp->DCPCTR));
        }
        else
        {
            p_reg = ((uint16_t *) &(ptr->ipp->PIPE_CTR[0]) + (pipeno - 1));
        }
        (*p_reg) = (uint16_t) ((*p_reg) & (~data));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_pid
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_trenb
 * Description     : The TRENB-bit (Transaction Counter Enable) is set in the speci-
 *               : fied pipe's control register, to enable the counter.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_trenb (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            p_reg = (uint16_t *) &(USB_M0->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        }
        else
        {
            p_reg = (uint16_t *) &(USB_M1->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        }
        (*p_reg) |= USB_TRENB;
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_reg     = (uint16_t *) &(ptr->ipp->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        (*p_reg) |= USB_TRENB;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_trenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_trenb
 * Description     : The TRENB-bit (Transaction Counter Enable) is cleared in the
 *               : specified pipe's control register, to disable the counter.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_trenb (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            p_reg = (uint16_t *) &(USB_M0->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        }
        else
        {
            p_reg = (uint16_t *) &(USB_M1->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        }
        (*p_reg) = (uint16_t) ((*p_reg) & (~USB_TRENB));
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_reg    = (uint16_t *) &(ptr->ipp->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        (*p_reg) = (uint16_t) ((*p_reg) & (~USB_TRENB));
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_trenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_trclr
 * Description     : The TRENB-bit (Transaction Counter Clear) is set in the speci-
 *               : fied pipe's control register to clear the current counter
 *               : value.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_trclr (usb_utr_t * ptr, uint16_t pipeno)
{
    volatile uint16_t * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            p_reg = (uint16_t *) &(USB_M0->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        }
        else
        {
            p_reg = (uint16_t *) &(USB_M1->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        }
        (*p_reg) |= USB_TRCLR;
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_reg     = (uint16_t *) &(ptr->ipp->PIPE_TR[0].E) + ((pipeno - 1) * 2);
        (*p_reg) |= USB_TRCLR;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_set_trclr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_write_pipetrn
 * Description     : Specified data is written to the specified pipe's PIPETRN reg-
 *               : ister.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  pipeno : Pipe number
 *               : uint16_t  data   : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_write_pipetrn (usb_utr_t * ptr, uint16_t pipeno, uint16_t data)
{
    volatile uint16_t * p_reg = 0;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP0 == ptr->ip)
        {
            p_reg = (uint16_t *) &(USB_M0->PIPE_TR[0].N) + ((pipeno - 1) * 2);
        }
        else
        {
            p_reg = (uint16_t *) &(USB_M1->PIPE_TR[0].N) + ((pipeno - 1) * 2);
        }
        *p_reg = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_reg  = (uint16_t *) &(ptr->ipp->PIPE_TR[0].N) + ((pipeno - 1) * 2);
        *p_reg = data;
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function hw_usb_write_pipetrn
 ******************************************************************************/

#if USB_CFG_BC == USB_CFG_ENABLE

/******************************************************************************
 * Function Name   : hw_usb_read_bcctrl
 * Description     : Returns BCCTRL register content.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : BCCTRL content
 ******************************************************************************/
uint16_t hw_usb_read_bcctrl (usb_utr_t * ptr)
{
    uint16_t rtn_val = 0;

    FSP_PARAMETER_NOT_USED(*ptr);
 #if defined(USB_HIGH_SPEED_MODULE)
    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CFG_IP1 == ptr->ip)
        {
            return USB_M1->BCCTRL;
        }
  #endif                               /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_IP1 == ptr->ip)
        {
            rtn_val = (uint16_t) ptr->ipp1->BCCTRL;
        }
  #endif                               /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

    return rtn_val;
} /* End of function hw_usb_read_bcctrl() */

/******************************************************************************
 * End of function hw_usb_read_bcctrl
 ******************************************************************************/
#endif                                 /* USB_CFG_BC == USB_CFG_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
 #if USB_CFG_BC == USB_CFG_ENABLE

/******************************************************************************
 * Function Name   : hw_usb_set_vdmsrce
 * Description     : Set VDMSRCE bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_vdmsrce (usb_utr_t * ptr)
{
    if (USB_IP1 == ptr->ip)
    {
  #if defined(USB_HIGH_SPEED_MODULE)
        ptr->ipp1->BCCTRL = (uint16_t) (ptr->ipp1->BCCTRL | (USB_VDMSRCE));
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
    }
}

/******************************************************************************
 * End of function hw_usb_set_vdmsrce
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_vdmsrce
 * Description     : Clear VDMSRCE bits.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_vdmsrce (usb_utr_t * ptr)
{
    if (USB_IP1 == ptr->ip)
    {
  #if defined(USB_HIGH_SPEED_MODULE)
        ptr->ipp1->BCCTRL = (uint16_t) (ptr->ipp1->BCCTRL & (~USB_VDMSRCE));
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_vdmsrce
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_set_idpsinke
 * Description     : Set IDPSINKE bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_idpsinke (usb_utr_t * ptr)
{
    if (USB_IP1 == ptr->ip)
    {
  #if defined(USB_HIGH_SPEED_MODULE)
        ptr->ipp1->BCCTRL = (uint16_t) (ptr->ipp1->BCCTRL | (USB_IDPSINKE));
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
    }
}

/******************************************************************************
 * End of function hw_usb_set_idpsinke
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_idpsinke
 * Description     : Clear IDPSINKE bits.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_idpsinke (usb_utr_t * ptr)
{
    if (USB_IP1 == ptr->ip)
    {
  #if defined(USB_HIGH_SPEED_MODULE)
        ptr->ipp1->BCCTRL = (uint16_t) (ptr->ipp1->BCCTRL & (~USB_IDPSINKE));
  #endif                               /* vdefined (USB_HIGH_SPEED_MODULE) */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_idpsinke
 ******************************************************************************/

 #endif                                /* USB_CFG_BC == USB_CFG_ENABLE */
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Function Name   : hw_usb_set_suspendm
 * Description     : Set SUSPM bit.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_suspendm (uint8_t usb_ip)
{
    if (USB_CFG_IP1 == usb_ip)
    {
 #if defined(USB_HIGH_SPEED_MODULE)
        USB_M1->LPSTS = (uint16_t) (USB_M1->LPSTS | (USB_SUSPENDM));
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    }
}

/******************************************************************************
 * End of function hw_usb_set_suspendm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_suspm
 * Description     : Clear SUSPM bit.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_suspm (uint8_t usb_ip)
{
    if (USB_CFG_IP1 == usb_ip)
    {
 #if defined(USB_HIGH_SPEED_MODULE)
        USB_M1->LPSTS = (uint16_t) (USB_M1->LPSTS & (~USB_SUSPENDM));
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    }
}

/******************************************************************************
 * End of function hw_usb_clear_suspm
 ******************************************************************************/

#endif                                 /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */

#if (defined(USB_LDO_REGULATOR_MODULE) && (USB_CFG_LDO_REGULATOR == USB_CFG_ENABLE))

/******************************************************************************
 * Function Name   : hw_usb_set_vdcen
 * Description     : Set VDCEN bit.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_vdcen (void)
{
    USB_M0->USBMC = (USB_M0->USBMC | USB_VDCEN);
}

/******************************************************************************
 * End of function hw_usb_set_vdcen
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_vdcen
 * Description     : Clear VDCEN bit.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_vdcen (void)
{
    USB_M0->USBMC = (uint16_t) (USB_M0->USBMC & (~USB_VDCEN));
}

/******************************************************************************
 * End of function hw_usb_clear_vdcen
 ******************************************************************************/

#endif                                 /* (defined(USB_LDO_REGULATOR_MODULE) && (USB_CFG_LDO_REGULATOR == USB_CFG_ENABLE)) */

#if defined(USB_SUPPORT_HOCO_MODULE)

/******************************************************************************
 * Function Name   : hw_usb_set_uckselc
 * Description     : Set UCKSELC bit in UCKSEL register.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_set_uckselc (void)
{
    USB_M0->UCKSEL |= USB_UCKSELC;
}

/******************************************************************************
 * End of function hw_usb_set_uckselc
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_clear_uckselc
 * Description     : Clear UCLKSELC bit in UCKSEL register.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_clear_uckselc (void)
{
    USB_M0->UCKSEL = (uint16_t) (USB_M0->UCKSEL & (~USB_UCKSELC));
}

/******************************************************************************
 * End of function hw_usb_clear_uckselc
 ******************************************************************************/

#endif                                 /* defined(USB_SUPPORT_HOCO_MODULE) */

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)

/******************************************************************************
 * Function Name   : hw_usb_typec_module_init
 * Description     : Initialization of USB TypeC module
 * Arguments       : none
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_BUSY      USB is in use.
 ******************************************************************************/
fsp_err_t hw_usb_typec_module_init (void)
{
 #if defined(USB_SUPPORT_TYPEC) && (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)
    FSP_ERROR_RETURN(0 != R_MSTP->MSTPCRB_b.MSTPB14, FSP_ERR_USB_BUSY)

    /* Enable module start for TypeC module */
    R_BSP_MODULE_START(FSP_IP_USBCC, 0);

    /* Type-C Reset Processing */
    R_USBCC->TCC |= USB_TYPEC_TCC_RESET;
    while (0 != (R_USBCC->TCC & USB_TYPEC_TCC_RESET))
    {
        ;
    }

    /* CC1 and CC2 pin setting */

    /* CCC-PHY not Power Down  */
    R_USBCC->CCC = (R_USBCC->CCC & (~USB_TYPEC_CCC_PDOWN));

    /* Change to Unattached_SNK */
    R_USBCC->MEC |= USB_TYPEC_MEC_GUS;
 #endif                                /* defined(USB_SUPPORT_TYPEC) && (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE) */

    return FSP_SUCCESS;
}

/******************************************************************************
 * End of function hw_usb_typec_module_init
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_typec_module_uninit
 * Description     : Uninitialization of USB TypeC module
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_typec_module_uninit (void)
{
 #if defined(USB_SUPPORT_TYPEC) && (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)

    /* Change to Unattached_SNK */
    R_USBCC->MEC |= USB_TYPEC_MEC_GD;

    /* CCC-PHY Power Down  */
    R_USBCC->CCC |= USB_TYPEC_CCC_PDOWN;

    /* Disable module start for TypeC module */
    R_BSP_MODULE_STOP(FSP_IP_USBCC, 0);
 #endif                                /* defined(USB_SUPPORT_TYPEC) && (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE) */
}

/******************************************************************************
 * End of function hw_usb_typec_module_uninit
 ******************************************************************************/

#endif                                 /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */

/******************************************************************************
 * End of file
 ******************************************************************************/
