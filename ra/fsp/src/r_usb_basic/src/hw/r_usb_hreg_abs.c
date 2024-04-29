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

#define USB_VALUE_50           (50)
#define USB_VALUE_300          (300)
#define USB_VALUE_00FFH        (0x00FF)
#define USB_VALUE_000000FFH    (0x000000FF)

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : usb_hstd_set_hub_port
 * Description     : Set up-port hub
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t addr     : device address
 *               : uint16_t upphub   : up-port hub address
 *               : uint16_t hubport  : hub port number
 * Return value    : none
 ******************************************************************************/
void usb_hstd_set_hub_port (usb_utr_t * ptr, uint16_t addr, uint16_t upphub, uint16_t hubport)
{
 #if defined(USB_HIGH_SPEED_MODULE)
    if (USB_IP1 == ptr->ip)
    {
        hw_usb_hrmw_devadd(ptr, addr, (upphub | hubport), (uint16_t) (USB_UPPHUB | USB_HUBPORT));
    }
 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
    FSP_PARAMETER_NOT_USED(*ptr);
    FSP_PARAMETER_NOT_USED(addr);
    FSP_PARAMETER_NOT_USED(upphub);
    FSP_PARAMETER_NOT_USED(hubport);
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
}

/******************************************************************************
 * End of function usb_hstd_set_hub_port
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_interrupt_handler
 * Description     : Analyzes which USB interrupt is generated
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hstd_interrupt_handler (usb_utr_t * ptr)
{
    uint16_t intsts0;
    uint16_t intenb0;
    uint16_t ists0;

    uint16_t intsts1;
    uint16_t intenb1;
    uint16_t ists1;

    uint16_t brdysts;
    uint16_t brdyenb;
    uint16_t bsts;

    uint16_t nrdysts;
    uint16_t nrdyenb;
    uint16_t nsts;

    uint16_t bempsts;
    uint16_t bempenb;
    uint16_t ests;

    intsts0 = ptr->ipp->INTSTS0;
    intsts1 = ptr->ipp->INTSTS1;
    brdysts = ptr->ipp->BRDYSTS;
    nrdysts = ptr->ipp->NRDYSTS;
    bempsts = ptr->ipp->BEMPSTS;
    intenb0 = ptr->ipp->INTENB0;
    intenb1 = ptr->ipp->INTENB1;
    brdyenb = ptr->ipp->BRDYENB;
    nrdyenb = ptr->ipp->NRDYENB;
    bempenb = ptr->ipp->BEMPENB;

    /* Interrupt Status Get */
    ptr->keyword = USB_INT_UNKNOWN;
    ptr->status  = 0;

    ists0 = (uint16_t) (intsts0 & intenb0);
    ists1 = (uint16_t) (intsts1 & intenb1);

    /*  ists2 = (uint16_t)(intsts2 & intenb2);*/
    bsts = (uint16_t) (brdysts & brdyenb);
    nsts = (uint16_t) (nrdysts & nrdyenb);
    ests = (uint16_t) (bempsts & bempenb);

    /***** Processing Setup transaction *****/
    if (USB_SACK == (ists1 & USB_SACK))
    {
        /***** Setup ACK *****/
        /* SACK Clear */
        ptr->ipp->INTSTS1 = (uint16_t) ((~USB_SACK) & INTSTS1_MASK);

        /* Setup Ignore,Setup Acknowledge disable */
        ptr->ipp->INTENB1 &= (uint16_t) ~(USB_SIGNE | USB_SACKE);
        ptr->keyword       = USB_INT_SACK;
    }
    else if (USB_SIGN == (ists1 & USB_SIGN))
    {
        /***** Setup Ignore *****/
        /* SIGN Clear */
        ptr->ipp->INTSTS1 = (uint16_t) ((~USB_SIGN) & INTSTS1_MASK);

        /* Setup Ignore,Setup Acknowledge disable */
        ptr->ipp->INTENB1 &= (uint16_t) ~((USB_SIGNE) | USB_SACKE);
        ptr->keyword       = USB_INT_SIGN;
    }

    /***** Processing PIPE0-MAX_PIPE_NO data *****/
    else if (USB_BRDY == (ists0 & USB_BRDY)) /***** EP0-7 BRDY *****/
    {
        ptr->ipp->BRDYSTS = (uint16_t) ((uint16_t) (~bsts) & BRDYSTS_MASK);
        ptr->keyword      = USB_INT_BRDY;
        ptr->status       = bsts;
    }
    else if (USB_BEMP == (ists0 & USB_BEMP)) /***** EP0-7 BEMP *****/
    {
        ptr->ipp->BEMPSTS = (uint16_t) ((uint16_t) (~ests) & BEMPSTS_MASK);
        ptr->keyword      = USB_INT_BEMP;
        ptr->status       = ests;
    }
    else if (USB_NRDY == (ists0 & USB_NRDY)) /***** EP0-7 NRDY *****/
    {
        ptr->ipp->NRDYSTS = (uint16_t) ((uint16_t) (~nsts) & NRDYSTS_MASK);
        ptr->keyword      = USB_INT_NRDY;
        ptr->status       = nsts;
    }

    /***** Processing rootport0 *****/
    else if (USB_OVRCR == (ists1 & USB_OVRCR)) /***** OVER CURRENT *****/
    {
        /* OVRCR Clear */
        ptr->ipp->INTSTS1 = (uint16_t) ((~USB_OVRCR) & INTSTS1_MASK);
        ptr->keyword      = USB_INT_OVRCR0;
    }
    else if (USB_ATTCH == (ists1 & USB_ATTCH)) /***** ATTCH INT *****/
    {
        /* DTCH  interrupt disable */
        usb_hstd_bus_int_disable(ptr);
        ptr->keyword = USB_INT_ATTCH0;
 #if defined(USB_CFG_OTG_USE)
        if (USB_YES == g_usb_otg_hnp_process[ptr->ip])
        {
            g_usb_is_otg_attach_interrupt[ptr->ip] = USB_YES;
        }
 #endif                                          /* defined(USB_CFG_OTG_USE) */
    }
    else if (USB_EOFERR == (ists1 & USB_EOFERR)) /***** EOFERR INT *****/
    {
        /* EOFERR Clear */
        ptr->ipp->INTSTS1 = (uint16_t) ((~USB_EOFERR) & INTSTS1_MASK);
        ptr->keyword      = USB_INT_EOFERR0;
    }
    else if (USB_BCHG == (ists1 & USB_BCHG)) /***** BCHG INT *****/
    {
        /* BCHG  interrupt disable */
        usb_hstd_bchg_disable(ptr);
        ptr->keyword = USB_INT_BCHG0;
    }
    else if (USB_DTCH == (ists1 & USB_DTCH)) /***** DETACH *****/
    {
        /* DTCH  interrupt disable */
        usb_hstd_bus_int_disable(ptr);
        ptr->keyword = USB_INT_DTCH0;
    }

 #if USB_CFG_BC == USB_CFG_ENABLE
    else if (USB_PDDETINT == (ists1 & USB_PDDETINT)) /***** PDDETINT INT *****/
    {
        if (USB_IP1 == ptr->ip)
        {
            /* PDDETINT  interrupt disable */
            ptr->ipp1->INTSTS1 = (uint16_t) ((~USB_PDDETINT) & INTSTS1_MASK);
            ptr->keyword       = USB_INT_PDDETINT0;
        }
    }
 #endif                                        /* USB_CFG_BC == USB_CFG_ENABLE */
    /***** Processing VBUS/SOF *****/
    else if (USB_VBINT == (ists0 & USB_VBINT)) /***** VBUS change *****/
    {
        /* Status Clear */
        ptr->ipp->INTSTS0 = (uint16_t) ~USB_VBINT;
        ptr->keyword      = USB_INT_VBINT;
    }
    else if (USB_SOFR == (ists0 & USB_SOFR)) /***** SOFR change *****/
    {
        /* SOFR Clear */
        ptr->ipp->INTSTS0 = (uint16_t) ~USB_SOFR;
        ptr->keyword      = USB_INT_SOFR;
    }
    else
    {
        /* Non */
    }
}

/******************************************************************************
 * End of function usb_hstd_interrupt_handler
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_chk_attach
 * Description     : Checks whether USB Device is attached or not and return USB speed
 *               : of USB Device
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : uint16_t          : connection status
 *               :                   : (USB_ATTACHF/USB_ATTACHL/USB_DETACH/USB_OK)
 * Note            : Please change for your SYSTEM
 ******************************************************************************/
uint16_t usb_hstd_chk_attach (usb_utr_t * ptr)
{
    uint16_t buf[3];
    uint16_t result = USB_DETACH;

    usb_hstd_read_lnst(ptr, buf);

    if (USB_UNDECID == (uint16_t) (buf[1] & USB_RHST))
    {
        if (USB_FS_JSTS == (buf[0] & USB_LNST))
        {
            /* High/Full speed device */
            USB_PRINTF0(" Detect FS-J\n");
 #if !defined(USB_CFG_OTG_USE)
  #if defined(USB_HIGH_SPEED_MODULE)
            usb_hstd_set_hse(ptr, g_usb_hstd_hs_enable[ptr->ip]);
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
 #endif                                /* !defined(USB_CFG_OTG_USE) */
            result = USB_ATTACHF;
        }
        else if (USB_LS_JSTS == (buf[0] & USB_LNST))
        {
            /* Low speed device */
            USB_PRINTF0(" Attach LS device\n");
 #if !defined(USB_CFG_OTG_USE)
  #if defined(USB_HIGH_SPEED_MODULE)
            usb_hstd_set_hse(ptr, USB_HS_DISABLE);
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
 #endif                                /* !defined(USB_CFG_OTG_USE) */
            result = USB_ATTACHL;
        }
        else if (USB_SE0 == (buf[0] & USB_LNST))
        {
            USB_PRINTF0(" Detach device\n");
        }
        else
        {
            USB_PRINTF0(" Attach unknown speed device\n");
        }
    }
    else
    {
        USB_PRINTF0(" Already device attached\n");
        result = USB_OK;
    }

    return result;
}

/******************************************************************************
 * End of function usb_hstd_chk_attach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_chk_clk
 * Description     : Checks SOF sending setting when USB Device is detached or suspended
 *               : , BCHG interrupt enable setting and clock stop processing
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t event    : device state
 * Return value    : none
 ******************************************************************************/
void usb_hstd_chk_clk (usb_utr_t * ptr, uint16_t event)
{
    (void) event;
    if ((USB_DETACHED == g_usb_hstd_mgr_mode[ptr->ip]) || (USB_SUSPENDED == g_usb_hstd_mgr_mode[ptr->ip]))
    {
        usb_hstd_chk_sof(ptr);

        /* Enable port BCHG interrupt */
        usb_hstd_bchg_enable(ptr);
    }
}                                      /* End of function usb_hstd_chk_clk */

/******************************************************************************
 * End of function usb_hstd_chk_clk
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_detach_process
 * Description     : Handles the require processing when USB device is detached
 *               : (Data transfer forcibly termination processing to the connected USB Device,
 *               : the clock supply stop setting and the USB interrupt dissable setteing etc)
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_detach_process (usb_utr_t * ptr)
{
    uint16_t connect_inf;
    uint16_t md;
    uint16_t i;
    uint16_t addr;

    /* ATTCH interrupt disable */
    usb_hstd_attch_disable(ptr);

    /* DTCH  interrupt disable */
    usb_hstd_dtch_disable(ptr);
    usb_hstd_bchg_disable(ptr);

    /* WAIT_LOOP */
    for (md = 1U; md < (USB_MAXDEVADDR + 1U); md++)
    {
        addr = (uint16_t) (md << USB_DEVADDRBIT);
        if (usb_hstd_chk_dev_addr(ptr, addr) != USB_NOCONNECT)
        {
            if (USB_IDLEST != g_usb_hstd_ctsq[ptr->ip])
            {
                /* Control Read/Write End */
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
            }

            /* WAIT_LOOP */
            for (i = USB_MIN_PIPE_NO; i <= USB_MAX_PIPE_NO; i++)
            {
                /* Not control transfer */
                /* Agreement device address */
                if (usb_hstd_get_devsel(ptr, i) == addr)
                {
                    if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][i])
                    {
                        /* End of data transfer (IN/OUT) */
                        usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_STOP);
                    }

                    usb_cstd_clr_pipe_cnfg(ptr, i);
                }
            }

            usb_hstd_set_dev_addr(ptr, addr, USB_NOCONNECT);
            usb_hstd_set_hub_port(ptr, addr, USB_NULL, USB_NULL);
            USB_PRINTF1("*** Device address %d clear.\n", md);
        }
    }

    /* Decide USB Line state (ATTACH) */
    connect_inf = usb_hstd_chk_attach(ptr);
    switch (connect_inf)
    {
        case USB_ATTACHL:
        {
            usb_hstd_attach(ptr, connect_inf);
            break;
        }

        case USB_ATTACHF:
        {
            usb_hstd_attach(ptr, connect_inf);
            break;
        }

        case USB_DETACH:
        {
            /* USB detach */
            usb_hstd_detach(ptr);

 #if !defined(USB_CFG_OTG_USE)

            /* Check clock */
            usb_hstd_chk_clk(ptr, (uint16_t) USB_DETACHED);
 #endif                                /* !defined (USB_CFG_OTG_USE) */
            break;
        }

        default:
        {
            /* USB detach */
            usb_hstd_detach(ptr);

            /* Check clock */
            usb_hstd_chk_clk(ptr, (uint16_t) USB_DETACHED);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_detach_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_read_lnst
 * Description     : Reads LNST register two times, checks whether these values
 *               : are equal and returns the value of DVSTCTR register that correspond to
 *               : the port specified by 2nd argument.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t *buf     : Pointer to the buffer to store DVSTCTR register
 * Return value    : none
 * Note            : Please change for your SYSTEM
 ******************************************************************************/
void usb_hstd_read_lnst (usb_utr_t * ptr, uint16_t * buf)
{
    /* WAIT_LOOP */
    do
    {
        buf[0] = hw_usb_read_syssts(ptr);

        /* 30ms wait */
        usb_cpu_delay_xms((uint16_t) 30);
        buf[1] = hw_usb_read_syssts(ptr);
        if ((buf[0] & USB_LNST) == (buf[1] & USB_LNST))
        {
            /* 20ms wait */
            usb_cpu_delay_xms((uint16_t) 20);
            buf[1] = hw_usb_read_syssts(ptr);
        }
    } while ((buf[0] & USB_LNST) != (buf[1] & USB_LNST));

    buf[1] = hw_usb_read_dvstctr(ptr);
}

/******************************************************************************
 * End of function usb_hstd_read_lnst
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_attach_process
 * Description     : Interrupt disable setting when USB Device is attached and
 *               : handles the required interrupt disable setting etc when USB device
 *               : is attached.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 * Note            : Please change for your SYSTEM
 ******************************************************************************/
void usb_hstd_attach_process (usb_utr_t * ptr)
{
    uint16_t connect_inf;

    /* ATTCH interrupt disable */
    usb_hstd_attch_disable(ptr);

    /* DTCH  interrupt disable */
    usb_hstd_dtch_disable(ptr);
    usb_hstd_bchg_disable(ptr);

    /* Decide USB Line state (ATTACH) */
    connect_inf = usb_hstd_chk_attach(ptr);
    switch (connect_inf)
    {
        case USB_ATTACHL:
        {
            usb_hstd_attach(ptr, connect_inf);
            break;
        }

        case USB_ATTACHF:
        {
            usb_hstd_attach(ptr, connect_inf);
            break;
        }

        case USB_DETACH:
        {
            /* USB detach */
            usb_hstd_detach(ptr);

            /* Check clock */
            usb_hstd_chk_clk(ptr, (uint16_t) USB_DETACHED);
            break;
        }

        default:
        {
            usb_hstd_attach(ptr, (uint16_t) USB_ATTACHF);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_attach_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_chk_sof
 * Description     : Checks whether SOF is sended or not
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_chk_sof (usb_utr_t * ptr)
{
    (void) *ptr;
    usb_cpu_delay_1us((uint16_t) 1);   /* Wait 640ns */
}

/******************************************************************************
 * End of function usb_hstd_chk_sof
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_bus_reset
 * Description     : Setting USB register when BUS Reset
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_bus_reset (usb_utr_t * ptr)
{
    uint16_t buf;
    uint16_t i;

    /* USBRST=1, UACT=0 */
    hw_usb_rmw_dvstctr(ptr, USB_USBRST, (USB_USBRST | USB_UACT));

    /* Wait 50ms */
    usb_cpu_delay_xms((uint16_t) USB_VALUE_50);
    if (USB_IP1 == ptr->ip)
    {
        /* USBRST=0 */
        hw_usb_clear_dvstctr(ptr, USB_USBRST); /* for UTMI */
        usb_cpu_delay_1us(USB_VALUE_300);      /* for UTMI */
    }

 #if defined(USB_CFG_OTG_USE)
    hw_usb_clear_hnpbtoa(ptr);
 #endif                                /* defined (USB_CFG_OTG_USE) */

    /* USBRST=0, RESUME=0, UACT=1 */
    usb_hstd_set_uact(ptr);

    /* Wait 10ms or more (USB reset recovery) */
    usb_cpu_delay_xms((uint16_t) 20);

    buf = USB_HSPROC;

    /* WAIT_LOOP */
    for (i = 0; (i < 3) && (USB_HSPROC == buf); ++i)
    {
        /* DeviceStateControlRegister - ResetHandshakeStatusCheck */
        buf = hw_usb_read_dvstctr(ptr);
        buf = (uint16_t) (buf & USB_RHST);
        if (USB_HSPROC == buf)
        {
            /* Wait */
            usb_cpu_delay_xms((uint16_t) 10);
        }
    }

    /* 30ms wait */
    usb_cpu_delay_xms((uint16_t) 30);
}

/******************************************************************************
 * End of function usb_hstd_bus_reset
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_resume_process
 * Description     : Setting USB register when RESUME signal is detected
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_resume_process (usb_utr_t * ptr)
{
    usb_hstd_bchg_disable(ptr);

    /* RESUME=1, RWUPE=0 */
    hw_usb_rmw_dvstctr(ptr, USB_RESUME, (USB_RESUME | USB_RWUPE));

    /* Wait */
    usb_cpu_delay_xms((uint16_t) 20);

    /* USBRST=0, RESUME=0, UACT=1 */
    usb_hstd_set_uact(ptr);

    /* Wait */
    usb_cpu_delay_xms((uint16_t) 5);
}

/******************************************************************************
 * End of function usb_hstd_resume_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_support_speed_check
 * Description     : Get USB-speed of the specified port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : uint16_t         : HSCONNECT : Hi-Speed
 *               :                  : FSCONNECT : Full-Speed
 *               :                  : LSCONNECT : Low-Speed
 *               :                  : NOCONNECT : not connect
 ******************************************************************************/
uint16_t usb_hstd_support_speed_check (usb_utr_t * ptr)
{
    uint16_t buf;
    uint16_t conn_inf;

    buf = hw_usb_read_dvstctr(ptr);

    /* Reset handshake status get */
    buf = (uint16_t) (buf & USB_RHST);

    switch (buf)
    {
        /* Get port speed */
        case USB_HSMODE:
        {
            conn_inf = USB_HSCONNECT;
            break;
        }

        case USB_FSMODE:
        {
            conn_inf = USB_FSCONNECT;
            break;
        }

        case USB_LSMODE:
        {
            conn_inf = USB_LSCONNECT;
            break;
        }

        case USB_HSPROC:
        {
            conn_inf = USB_NOCONNECT;
            break;
        }

        default:
        {
            conn_inf = USB_NOCONNECT;
            break;
        }
    }

    return conn_inf;
}

/******************************************************************************
 * End of function usb_hstd_support_speed_check
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_write_fifo
 * Description     : Write specified amount of data to specified USB FIFO.
 * Arguments       : usb_utr_t    *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t     count      : Write size
 *               : uint16_t     pipemode   : The mode of CPU/DMA(D0)/DMA(D1).
 *               : uint16_t     *write_p   : Address of buffer of data to write.
 * Return value    : The incremented address of last argument (write_p).
 ******************************************************************************/
uint8_t * usb_hstd_write_fifo (usb_utr_t * ptr, uint16_t count, uint16_t pipemode, uint8_t * write_p)
{
    uint16_t even;
 #if defined(USB_HIGH_SPEED_MODULE)
    uint16_t odd;
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

 #if defined(USB_HIGH_SPEED_MODULE)
    if (USB_IP0 == ptr->ip)
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 1); (0 != even); --even)
        {
            /* 16bit access */
            hw_usb_write_fifo16(ptr, pipemode, *((uint16_t *) write_p));

            /* Renewal write pointer */
            write_p += sizeof(uint16_t);
        }

        if ((count & (uint16_t) 0x0001U) != 0U)
        {
            /* 8bit access */
            /* count == odd */
            /* Change FIFO access width */
            hw_usb_set_mbw(ptr, pipemode, USB_MBW_8);

            /* FIFO write */
            hw_usb_write_fifo8(ptr, pipemode, *write_p);

            /* Return FIFO access width */
            hw_usb_set_mbw(ptr, pipemode, USB_MBW_16);

            /* Renewal write pointer */
            write_p++;
        }
    }
    else if (USB_IP1 == ptr->ip)
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 2); (0 != even); --even)
        {
            /* 16bit access */
            hw_usb_write_fifo32(ptr, pipemode, *((uint32_t *) write_p));

            /* Renewal write pointer */
            write_p += sizeof(uint32_t);
        }

        odd = count % 4;
        if ((odd & (uint16_t) 0x0002U) != 0U)
        {
            /* 16bit access */
            /* Change FIFO access width */
            hw_usb_set_mbw(ptr, pipemode, USB_MBW_16);

            /* FIFO write */
            hw_usb_write_fifo16(ptr, pipemode, *((uint16_t *) write_p));

            /* Renewal write pointer */
            write_p += sizeof(uint16_t);
        }

        if ((odd & (uint16_t) 0x0001U) != 0U)
        {
            /* 8bit access */
            /* count == odd */
            /* Change FIFO access width */
            hw_usb_set_mbw(ptr, pipemode, USB_MBW_8);

            /* FIFO write */
            hw_usb_write_fifo8(ptr, pipemode, *write_p);

            /* Renewal write pointer */
            write_p++;
        }

        /* Return FIFO access width */
        hw_usb_set_mbw(ptr, pipemode, USB_MBW_32);
    }
    else
    {
        /* Non */
    }
 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
    /* WAIT_LOOP */
    for (even = (uint16_t) (count >> 1); (0 != even); --even)
    {
        /* 16bit access */
        hw_usb_write_fifo16(ptr, pipemode, *((uint16_t *) write_p));

        /* Renewal write pointer */
        write_p += sizeof(uint16_t);
    }

    if ((count & (uint16_t) 0x0001U) != 0U)
    {
        /* 8bit access */
        /* count == odd */
        /* Change FIFO access width */
        hw_usb_set_mbw(ptr, pipemode, USB_MBW_8);

        /* FIFO write */
        hw_usb_write_fifo8(ptr, pipemode, *write_p);

        /* Return FIFO access width */
        hw_usb_set_mbw(ptr, pipemode, USB_MBW_16);

        /* Renewal write pointer */
        write_p++;
    }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    return write_p;
}

/******************************************************************************
 * End of function usb_hstd_write_fifo
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_read_fifo
 * Description     : Read specified buffer size from the USB FIFO.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     count       : Read size
 *               : uint16_t     pipemode    : The mode of CPU/DMA(D0)/DMA(D1).
 *               : uint16_t     *read_p     : Address of buffer to store the read data
 * Return value    : Pointer to a buffer that contains the data to be read next.
 ******************************************************************************/
uint8_t * usb_hstd_read_fifo (usb_utr_t * ptr, uint16_t count, uint16_t pipemode, uint8_t * read_p)
{
    uint16_t even;
 #if defined(USB_HIGH_SPEED_MODULE)
    uint16_t odd;
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    uint32_t odd_byte_data_temp;

 #if defined(USB_HIGH_SPEED_MODULE)
  #if USB_CFG_ENDIAN == USB_CFG_BIG
    uint16_t i;
  #endif                               /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

 #if defined(USB_HIGH_SPEED_MODULE)
    if (USB_IP0 == ptr->ip)
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 1); (0 != even); --even)
        {
            /* 16bit FIFO access */
            *(uint16_t *) read_p = hw_usb_read_fifo16(ptr, pipemode);

            /* Renewal read pointer */
            read_p += sizeof(uint16_t);
        }

        if ((count & (uint16_t) 0x0001) != 0)
        {
            /* 16bit FIFO access */
            odd_byte_data_temp = hw_usb_read_fifo16(ptr, pipemode);

            /* Condition compilation by the difference of the little endian */
  #if USB_CFG_ENDIAN == USB_CFG_LITTLE
            *read_p = (uint8_t) (odd_byte_data_temp & USB_VALUE_00FFH);
  #else                                /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
            *read_p = (uint8_t) (odd_byte_data_temp >> 8);
  #endif /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

            /* Renewal read pointer */
            read_p += sizeof(uint8_t);
        }
    }
    else if (USB_IP1 == ptr->ip)
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 2); (0 != even); --even)
        {
            /* 32bit FIFO access */
            *(uint32_t *) read_p = hw_usb_read_fifo32(ptr, pipemode);

            /* Renewal read pointer */
            read_p += sizeof(uint32_t);
        }

        odd = count % 4;
        if (count < 4)
        {
            odd = count;
        }

        if (odd != 0)
        {
            /* 32bit FIFO access */
            odd_byte_data_temp = hw_usb_read_fifo32(ptr, pipemode);

            /* Condition compilation by the difference of the little endian */
  #if USB_CFG_ENDIAN == USB_CFG_LITTLE

            /* WAIT_LOOP */
            do
            {
                *read_p            = (uint8_t) (odd_byte_data_temp & USB_VALUE_000000FFH);
                odd_byte_data_temp = odd_byte_data_temp >> 8;

                /* Renewal read pointer */
                read_p += sizeof(uint8_t);
                odd--;
            } while (odd != 0);
  #else                                /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
            /* WAIT_LOOP */
            for (i = 0; i < odd; i++)
            {
                *read_p = (uint8_t) ((odd_byte_data_temp >> (24 - (i * 8))) & 0x000000ff);

                /* Renewal read pointer */
                read_p += sizeof(uint8_t);
            }
  #endif                               /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
        }
    }
    else
    {
        /* None */
    }
 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
    /* WAIT_LOOP */
    for (even = (uint16_t) (count >> 1); (0 != even); --even)
    {
        /* 16bit FIFO access */
        *(uint16_t *) read_p = hw_usb_read_fifo16(ptr, pipemode);

        /* Renewal read pointer */
        read_p += sizeof(uint16_t);
    }

    if ((count & (uint16_t) 0x0001) != 0)
    {
        /* 16bit FIFO access */
        odd_byte_data_temp = hw_usb_read_fifo16(ptr, pipemode);

        /* Condition compilation by the difference of the little endian */
  #if USB_CFG_ENDIAN == USB_CFG_LITTLE
        *read_p = (uint8_t) (odd_byte_data_temp & USB_VALUE_00FFH);
  #else                                /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
        *read_p = (uint8_t) (odd_byte_data_temp >> 8);
  #endif /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

        /* Renewal read pointer */
        read_p += sizeof(uint8_t);
    }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    return read_p;
}

/******************************************************************************
 * End of function usb_hstd_read_fifo
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_forced_termination
 * Description     : Terminate data transmission and reception.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     pipe    : Pipe Number
 *               : uint16_t     status  : Transfer status type
 * Return value    : none
 * Note            : In the case of timeout status, it does not call back.
 ******************************************************************************/
void usb_hstd_forced_termination (usb_utr_t * ptr, uint16_t pipe, uint16_t status)
{
    uint16_t buffer;

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_set_nak(ptr, pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(ptr, pipe);

    /* Disable Not Ready Interrupt */
    hw_usb_clear_nrdyenb(ptr, pipe);

    /* Disable Empty Interrupt */
    hw_usb_clear_bempenb(ptr, pipe);

    usb_cstd_clr_transaction_counter(ptr, pipe);

    /* Clear CFIFO-port */
    buffer = hw_usb_read_fifosel(ptr, USB_CUSE);
    if ((buffer & USB_CURPIPE) == pipe)
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_CUSE, USB_FALSE);
    }

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

    /* Clear D0FIFO-port */
    buffer = hw_usb_read_fifosel(ptr, USB_D0USE);
    if ((buffer & USB_CURPIPE) == pipe)
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D0USE, USB_FALSE);
    }

    /* Clear D1FIFO-port */
    buffer = hw_usb_read_fifosel(ptr, USB_D1USE);
    if ((buffer & USB_CURPIPE) == pipe)
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D1USE, USB_FALSE);
    }
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    /* Do Aclr */
    usb_cstd_do_aclrm(ptr, pipe);

    /* FIFO buffer SPLIT transaction initialized */
    hw_usb_set_csclr(ptr, pipe);

    /* Call Back */
    if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipe])
    {
        /* Transfer information set */
        g_p_usb_hstd_pipe[ptr->ip][pipe]->tranlen = g_usb_hstd_data_cnt[ptr->ip][pipe];
        g_p_usb_hstd_pipe[ptr->ip][pipe]->status  = status;
        g_p_usb_hstd_pipe[ptr->ip][pipe]->pipectr = hw_usb_read_pipectr(ptr, pipe);
        g_p_usb_hstd_pipe[ptr->ip][pipe]->errcnt  = (uint8_t) g_usb_hstd_ignore_cnt[ptr->ip][pipe];
        g_p_usb_hstd_pipe[ptr->ip][pipe]->ipp     = ptr->ipp;
        g_p_usb_hstd_pipe[ptr->ip][pipe]->ip      = ptr->ip;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        g_p_usb_hstd_pipe[ptr->ip][pipe]->p_transfer_rx = ptr->p_transfer_rx;
        g_p_usb_hstd_pipe[ptr->ip][pipe]->p_transfer_tx = ptr->p_transfer_tx;
 #endif

        if (USB_NULL != (g_p_usb_hstd_pipe[ptr->ip][pipe]->complete))
        {
            (g_p_usb_hstd_pipe[ptr->ip][pipe]->complete)(g_p_usb_hstd_pipe[ptr->ip][pipe], 0, 0);
        }

 #if (BSP_CFG_RTOS == 0)
        g_p_usb_hstd_pipe[ptr->ip][pipe] = (usb_utr_t *) USB_NULL;
 #else                                               /* (BSP_CFG_RTOS == 0) */
  #if (BSP_CFG_RTOS == 1)
        USB_REL_BLK(1, g_p_usb_hstd_pipe[ptr->ip][pipe]);
  #elif (BSP_CFG_RTOS == 2)                          /* #if (BSP_CFG_RTOS == 1) */
        vPortFree(g_p_usb_hstd_pipe[ptr->ip][pipe]);
  #endif                                             /* #if (BSP_CFG_RTOS == 1) */
        g_p_usb_hstd_pipe[ptr->ip][pipe] = (usb_utr_t *) USB_NULL;
        usb_cstd_pipe_msg_re_forward(ptr->ip, pipe); /* Get PIPE Transfer wait que and Message send to HCD */
 #endif                                              /* (BSP_CFG_RTOS == 0) */
    }
}

/******************************************************************************
 * End of function usb_hstd_forced_termination
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_get_usb_ip_adr
 * Description     : Get base address of the selected USB channel's peripheral
 *               : registers.
 * Argument        : uint16_t ipnum  : USB_IP0 (0), or USB_IP1 (1).
 * Return          : usb_regadr_t    : A pointer to the USB_597IP register
 *               : structure USB_REGISTER containing all USB
 *               : channel's registers.
 ******************************************************************************/
usb_regadr_t usb_hstd_get_usb_ip_adr (uint16_t ipnum)
{
    usb_regadr_t ptr = 0;

    if (USB_IP0 == ipnum)
    {
        ptr = (usb_regadr_t) R_USB_FS0;
    }

 #if USB_NUM_USBIP == 2
    else if (USB_IP1 == ipnum)
    {
  #if defined(USB_HIGH_SPEED_MODULE)
        ptr = (usb_regadr_t) R_USB_HS0;
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
    }
 #endif                                /* USB_NUM_USBIP == 2 */
    else
    {
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_STD | USB_DEBUG_HOOK_CODE1);
    }

    return ptr;
}

/******************************************************************************
 * End of function usb_hstd_get_usb_ip_adr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_nrdy_endprocess
 * Description     : NRDY interrupt processing. (Forced termination of data trans-
 *               : mission and reception of specified pipe.)
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     pipe        : Pipe No
 * Return value    : none
 * Note            : none
 ******************************************************************************/
void usb_hstd_nrdy_endprocess (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t buffer;

    /*
     * Host Function
     */
    buffer = usb_cstd_get_pid(ptr, pipe);

    /* STALL ? */
    if (USB_PID_STALL == (buffer & USB_PID_STALL))
    {
        /*USB_PRINTF1("### STALL Pipe %d\n", pipe);*/
        /* @4 */
        /* End of data transfer */
        usb_hstd_forced_termination(ptr, pipe, USB_DATA_STALL);
    }
    else
    {
        /* Wait for About 60ns */
        hw_usb_read_syssts(ptr);

        /* @3 */
        g_usb_hstd_ignore_cnt[ptr->ip][pipe]++;

        /*USB_PRINTF2("### IGNORE Pipe %d is %d times \n", pipe, g_usb_hstd_ignore_cnt[ptr->ip][pipe]);*/
        if (USB_PIPEERROR == g_usb_hstd_ignore_cnt[ptr->ip][pipe])
        {
            /* Data Device Ignore X 3 call back */
            /* End of data transfer */
            usb_hstd_forced_termination(ptr, pipe, USB_DATA_ERR);
        }
        else
        {
            /* 5ms wait */
            usb_cpu_delay_xms(5);

            /* PIPEx Data Retry */
            usb_cstd_set_buf(ptr, pipe);
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_nrdy_endprocess
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End of file
 ******************************************************************************/
