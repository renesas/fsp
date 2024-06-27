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
#include "inc/r_usb_dmac.h"

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define USB_VAL_FFH    (0x00FFU)
#define USB_VAL_100    (100U)

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
uint16_t g_usb_cstd_suspend_mode = USB_NORMAL_MODE;

/******************************************************************************
 * Function Name   : usb_pstd_interrupt_handler
 * Description     : Determine which USB interrupt occurred and report results to
 *               : the usb_utr_t argument's ipp, type, and status members.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_interrupt_handler (uint16_t * type, uint16_t * status, uint8_t usb_ip)
{
    uint16_t intsts0;
    uint16_t intenb0;
    uint16_t ists0;
    uint16_t brdysts;
    uint16_t brdyenb;
    uint16_t bsts;
    uint16_t nrdysts;
    uint16_t nrdyenb;
    uint16_t nsts;
    uint16_t bempsts;
    uint16_t bempenb;
    uint16_t ests;

    /* Register Save */
    if (USB_CFG_IP1 == usb_ip)
    {
        intsts0 = USB_M1->INTSTS0;
        brdysts = USB_M1->BRDYSTS;
        nrdysts = USB_M1->NRDYSTS;
        bempsts = USB_M1->BEMPSTS;
        intenb0 = USB_M1->INTENB0;
        brdyenb = USB_M1->BRDYENB;
        nrdyenb = USB_M1->NRDYENB;
        bempenb = USB_M1->BEMPENB;
    }
    else
    {
        intsts0 = USB_M0->INTSTS0;
        brdysts = USB_M0->BRDYSTS;
        nrdysts = USB_M0->NRDYSTS;
        bempsts = USB_M0->BEMPSTS;
        intenb0 = USB_M0->INTENB0;
        brdyenb = USB_M0->BRDYENB;
        nrdyenb = USB_M0->NRDYENB;
        bempenb = USB_M0->BEMPENB;
    }

    *type   = USB_INT_UNKNOWN;
    *status = 0;

    /* Interrupt status get */
    ists0 = (uint16_t) (intsts0 & intenb0);
    bsts  = (uint16_t) (brdysts & brdyenb);
    nsts  = (uint16_t) (nrdysts & nrdyenb);
    ests  = (uint16_t) (bempsts & bempenb);

    if (0U == ((USB_VBINT | USB_RESM | USB_SOFR | USB_DVST |
                USB_CTRT | USB_BEMP | USB_NRDY | USB_BRDY) & intsts0))
    {
        return;
    }

    /***** Processing USB bus signal *****/
    /***** Resume signal *****/
    if (USB_RESM == (ists0 & USB_RESM))
    {
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->INTSTS0 = (uint16_t) ~USB_RESM;
        }
        else
        {
            USB_M0->INTSTS0 = (uint16_t) ~USB_RESM;
        }

        *type = USB_INT_RESM;
    }

    /***** Vbus change *****/
    else if (USB_VBINT == (ists0 & USB_VBINT))
    {
        /* Status clear */
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->INTSTS0 = (uint16_t) ~USB_VBINT;
        }
        else
        {
            USB_M0->INTSTS0 = (uint16_t) ~USB_VBINT;
        }

        *type = USB_INT_VBINT;
    }

    /***** SOFR change *****/
    else if (USB_SOFR == (ists0 & USB_SOFR))
    {
        /* SOFR Clear */
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->INTSTS0 = (uint16_t) ~USB_SOFR;
        }
        else
        {
            USB_M0->INTSTS0 = (uint16_t) ~USB_SOFR;
        }

        *type = USB_INT_SOFR;
    }

    /***** Processing device state *****/
    /***** DVST change *****/
    else if (USB_DVST == (ists0 & USB_DVST))
    {
        /* DVST clear */
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->INTSTS0 = (uint16_t) ~USB_DVST;
        }
        else
        {
            USB_M0->INTSTS0 = (uint16_t) ~USB_DVST;
        }

        *type   = USB_INT_DVST;
        *status = intsts0;
    }

    /***** Processing PIPE0 data *****/
    else if ((USB_BRDY == (ists0 & USB_BRDY)) && ((USB_BRDY0) == (bsts & USB_BRDY0)))
    {
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->BRDYSTS = (uint16_t) ((~USB_BRDY0) & BRDYSTS_MASK);
        }
        else
        {
            USB_M0->BRDYSTS = (uint16_t) ((~USB_BRDY0) & BRDYSTS_MASK);
        }

        *type   = USB_INT_BRDY;
        *status = USB_BRDY0;
    }
    else if ((USB_BEMP == (ists0 & USB_BEMP)) && (USB_BEMP0 == (ests & USB_BEMP0)))
    {
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->BEMPSTS = (uint16_t) ((~USB_BEMP0) & BEMPSTS_MASK);
        }
        else
        {
            USB_M0->BEMPSTS = (uint16_t) ((~USB_BEMP0) & BEMPSTS_MASK);
        }

        *type   = USB_INT_BEMP;
        *status = USB_BEMP0;
    }
    else if ((USB_NRDY == (ists0 & USB_NRDY)) && (USB_NRDY0 == (nsts & USB_NRDY0)))
    {
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->NRDYSTS = (uint16_t) ((~USB_NRDY0) & NRDYSTS_MASK);
        }
        else
        {
            USB_M0->NRDYSTS = (uint16_t) ((~USB_NRDY0) & NRDYSTS_MASK);
        }

        *type   = USB_INT_NRDY;
        *status = USB_NRDY0;
    }

    /***** Processing setup transaction *****/
    else if (USB_CTRT == (ists0 & USB_CTRT))
    {
        /* CTSQ bit changes later than CTRT bit for ASSP. */
        /* CTSQ reloading */
        *status = hw_usb_read_intsts(usb_ip);

        /* USB_CTRT clear */
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->INTSTS0 = (uint16_t) ~USB_CTRT;
        }
        else
        {
            USB_M0->INTSTS0 = (uint16_t) ~USB_CTRT;
        }

        *type = USB_INT_CTRT;

        if (USB_CS_SQER == (uint8_t) ((*status) & USB_CTSQ))
        {
            hw_usb_pclear_sts_valid(usb_ip);
            *type   = USB_INT_UNKNOWN;
            *status = 0;

            return;
        }
    }

    /***** Processing PIPE1-MAX_PIPE_NO data *****/
    else if (USB_BRDY == (ists0 & USB_BRDY))
    {
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->BRDYSTS = (uint16_t) ((uint16_t) (~bsts) & BRDYSTS_MASK);
        }
        else
        {
            USB_M0->BRDYSTS = (uint16_t) ((uint16_t) (~bsts) & BRDYSTS_MASK);
        }

        *type   = USB_INT_BRDY;
        *status = bsts;
    }
    else if (USB_BEMP == (ists0 & USB_BEMP))
    {
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->BEMPSTS = (uint16_t) ((uint16_t) (~ests) & BEMPSTS_MASK);
        }
        else
        {
            USB_M0->BEMPSTS = (uint16_t) ((uint16_t) (~ests) & BEMPSTS_MASK);
        }

        *type   = USB_INT_BEMP;
        *status = ests;
    }
    else if (USB_NRDY == (ists0 & USB_NRDY))
    {
        if (USB_CFG_IP1 == usb_ip)
        {
            USB_M1->NRDYSTS = (uint16_t) ((uint16_t) (~nsts) & NRDYSTS_MASK);
        }
        else
        {
            USB_M0->NRDYSTS = (uint16_t) ((uint16_t) (~nsts) & NRDYSTS_MASK);
        }

        *type   = USB_INT_NRDY;
        *status = nsts;
    }
    else
    {
        /* Non processing. */
    }
}

/******************************************************************************
 * End of function usb_pstd_interrupt_handler
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_save_request
 * Description     : Save received USB command.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_save_request (uint8_t usb_ip)
{
    /* Valid clear */
    hw_usb_pclear_sts_valid(usb_ip);

    g_usb_pstd_req_type   = hw_usb_read_usbreq(usb_ip);
    g_usb_pstd_req_value  = hw_usb_read_usbval(usb_ip);
    g_usb_pstd_req_index  = hw_usb_read_usbindx(usb_ip);
    g_usb_pstd_req_length = hw_usb_read_usbleng(usb_ip);
}

/******************************************************************************
 * End of function usb_pstd_save_request
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_chk_configured
 * Description     : Check if USB Device is in a CONFIGURED state.
 * Arguments       : none
 * Return value    : Configuration state (YES/NO)
 ******************************************************************************/
uint16_t usb_pstd_chk_configured (usb_utr_t * p_utr)
{
    uint16_t buf;
    uint16_t err;

    buf = hw_usb_read_intsts(p_utr->ip);

    /* Device Status - Configured check */
    if (USB_DS_CNFG == (buf & USB_DVSQ))
    {
        /* Configured */
        err = USB_TRUE;
    }
    else
    {
        /* not Configured */
        err = USB_FALSE;
    }

    return err;
}

/******************************************************************************
 * End of function usb_pstd_chk_configured
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_remote_wakeup
 * Description     : Set the USB peripheral to implement remote wake up.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_remote_wakeup (uint8_t usb_ip)
{
    uint16_t buf;

    g_usb_pstd_remote_wakeup_state = USB_ERROR;

    /* Support remote wakeup ? */
    if (USB_TRUE == g_usb_pstd_remote_wakeup)
    {
        /* RESM interrupt disable */
        hw_usb_pclear_enb_rsme(usb_ip);

        /* RESM status read */
        buf = hw_usb_read_intsts(usb_ip);
        if ((buf & USB_RESM) != (uint16_t) 0)
        {
            g_usb_pstd_remote_wakeup_state = USB_QOVR;

            /* RESM status clear */
            hw_usb_pclear_sts_resm(usb_ip);
        }
        else
        {
            if ((buf & USB_DS_SUSP) != (uint16_t) 0)
            {
                /* Remote wakeup set */
                hw_usb_pset_wkup(usb_ip);
                g_usb_pstd_remote_wakeup_state = USB_OK;
            }
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_remote_wakeup
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_test_mode
 * Description     : USB Peripheral test mode function.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_test_mode (usb_utr_t * p_utr)
{
    (void) *p_utr;
    switch ((uint16_t) (g_usb_pstd_test_mode_select & USB_TEST_SELECT))
    {
        case USB_TEST_J:

        /* Continue */
        case USB_TEST_K:

        /* Continue */
        case USB_TEST_SE0_NAK:

        /* Continue */
        case USB_TEST_PACKET:
        {
 #if defined(USB_HIGH_SPEED_MODULE)
            hw_usb_set_utst(p_utr, 0);
            hw_usb_set_utst(p_utr, (uint16_t) (g_usb_pstd_test_mode_select >> 8));
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
            break;
        }

        case USB_TEST_FORCE_ENABLE:

        /* Continue */
        default:
        {
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_test_mode
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_resume_process
 * Description     : Set USB registers to implement resume processing.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_resume_process (usb_utr_t * p_utr)
{
    /* RESM status clear */
    hw_usb_pclear_sts_resm(p_utr->ip);

    /* RESM interrupt disable */
    hw_usb_pclear_enb_rsme(p_utr->ip);
}

/******************************************************************************
 * End of function usb_pstd_resume_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_stall
 * Description     : Set the specified pipe's PID to STALL.
 * Arguments       : uint16_t pipe   : Pipe Number
 * Return value    : none
 ******************************************************************************/
void usb_pstd_set_stall (uint16_t pipe, usb_utr_t * p_utr)
{
    /* PIPE control reg set */
    hw_usb_set_pid(p_utr, pipe, USB_PID_STALL);
}

/******************************************************************************
 * End of function usb_pstd_set_stall
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_stall_pipe0
 * Description     : Set pipe "0" PID to STALL.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_set_stall_pipe0 (usb_utr_t * p_utr)
{
    /* PIPE control reg set */
    hw_usb_set_pid(p_utr, USB_PIPE0, USB_PID_STALL);
}

/******************************************************************************
 * End of function usb_pstd_set_stall_pipe0
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_write_fifo
 * Description     : Write specified amount of data to specified USB FIFO.
 * Arguments       : uint16_t  count       : Write size.
 *               : uint16_t  pipemode    : The mode of CPU/DMA(D0)/DMA(D1).
 *               : uint16_t  *write_p    : Address of buffer of data to write.
 * Return value    : The incremented address of last argument (write_p).
 ******************************************************************************/
uint8_t * usb_pstd_write_fifo (uint16_t count, uint16_t pipemode, uint8_t * write_p, usb_utr_t * p_utr)
{
    uint16_t even;
 #if defined(USB_HIGH_SPEED_MODULE)
    uint16_t odd;
    uint16_t hs_flag = 1;
 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
    uint16_t hs_flag = 0;
 #endif /* defined (USB_HIGH_SPEED_MODULE) */

 #if defined(USB_UNALIGNED_MEMORY_ACCESS_NG_MCU)

    /* The value of "write_p" is odd */
    if (USB_ODD == ((uint32_t) write_p & USB_ODD))
    {
        /* 8bit access */
        /* write_p == odd */
        /* Change FIFO access width */
        hw_usb_set_mbw(p_utr, pipemode, USB_MBW_8);

        for ( ; (0 != count); count--)
        {
            USB0_CFIFO8 = *write_p++;
        }

        /* Return FIFO access width */
        hw_usb_set_mbw(p_utr, pipemode, USB_MBW_16);

        return write_p;
    }
 #endif                                /* defined(USB_UNALIGNED_MEMORY_ACCESS_NG_MCU) */

    if ((USB_CFG_IP0 == p_utr->ip) || (0 == hs_flag))
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 1); (0 != even); --even)
        {
            /* 16bit access */
            hw_usb_write_fifo16(p_utr, pipemode, *((uint16_t *) write_p));

            /* Renewal write pointer */
            write_p += sizeof(uint16_t);
        }

        if ((count & (uint16_t) 0x0001U) != 0U)
        {
            /* 8bit access */
            /* count == odd */
            /* Change FIFO access width */
            hw_usb_set_mbw(p_utr, pipemode, USB_MBW_8);

            /* FIFO write */
            hw_usb_write_fifo8(p_utr, pipemode, *write_p);

            /* Return FIFO access width */
            hw_usb_set_mbw(p_utr, pipemode, USB_MBW_16);

            /* Renewal write pointer */
            write_p++;
        }
    }

 #if defined(USB_HIGH_SPEED_MODULE)
    else
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 2); (even != 0); --even)
        {
            /* 32bit access */
            hw_usb_write_fifo32(p_utr, pipemode, *((uint32_t *) write_p));

            /* Renewal write pointer */
            write_p += sizeof(uint32_t);
        }

        odd = count % 4;
        if ((odd & (uint16_t) 0x0002U) != 0U)
        {
            /* 16bit access */
            /* Change FIFO access width */
            hw_usb_set_mbw(p_utr, pipemode, USB_MBW_16);

            /* FIFO write */
            hw_usb_write_fifo16(p_utr, pipemode, *((uint16_t *) write_p));

            /* Renewal write pointer */
            write_p += sizeof(uint16_t);
        }

        if ((odd & (uint16_t) 0x0001U) != 0U)
        {
            /* 8bit access */
            /* count == odd */
            /* Change FIFO access width */
            hw_usb_set_mbw(p_utr, pipemode, USB_MBW_8);

            /* FIFO write */
            hw_usb_write_fifo8(p_utr, pipemode, *write_p);

            /* Renewal write pointer */
            write_p++;
        }

        /* Return FIFO access width */
        hw_usb_set_mbw(p_utr, pipemode, USB_MBW_32);
    }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    return write_p;
}

/******************************************************************************
 * End of function usb_pstd_write_fifo
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_read_fifo
 * Description     : Read specified buffer size from the USB FIFO.
 * Arguments       : uint16_t  count       : Read size.
 *               : uint16_t  pipemode    : The mode of CPU/DMA(D0)/DMA(D1).
 *               : uint16_t  *write_p    : Address of buffer to store the read data.
 * Return value    : Pointer to a buffer that contains the data to be read next.
 ******************************************************************************/
uint8_t * usb_pstd_read_fifo (uint16_t count, uint16_t pipemode, uint8_t * read_p, usb_utr_t * p_utr)
{
    uint16_t even;
    uint32_t odd_byte_data_temp;
 #if USB_CFG_ENDIAN == USB_CFG_BIG
    uint16_t i;
 #endif
 #if defined(USB_HIGH_SPEED_MODULE)
    uint16_t odd;
    uint16_t hs_flag = 1;
 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
    uint16_t hs_flag = 0;
 #endif /* defined (USB_HIGH_SPEED_MODULE) */

 #if defined(USB_UNALIGNED_MEMORY_ACCESS_NG_MCU)

    /* The value of "read_p" is odd */
    if (USB_ODD == ((uint32_t) read_p & USB_ODD))
    {
        /* 8bit access */
        /* read_p == odd */
        /* Change FIFO access width */
        hw_usb_set_mbw(p_utr, pipemode, USB_MBW_8);

        for ( ; (0 != count); count--)
        {
            *read_p++ = USB0_CFIFO8;
        }

        /* Return FIFO access width */
        hw_usb_set_mbw(p_utr, pipemode, USB_MBW_16);

        return read_p;
    }
 #endif                                /* defined(USB_UNALIGNED_MEMORY_ACCESS_NG_MCU) */

    if ((USB_CFG_IP0 == p_utr->ip) || (0 == hs_flag))
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 1); (0 != even); --even)
        {
            /* 16bit FIFO access */
            *(uint16_t *) read_p = hw_usb_read_fifo16(p_utr, pipemode);

            /* Renewal read pointer */
            read_p += sizeof(uint16_t);
        }

        if ((count & (uint16_t) 0x0001) != 0)
        {
            /* 16bit FIFO access */
            odd_byte_data_temp = hw_usb_read_fifo16(p_utr, pipemode);

            /* Condition compilation by the difference of the little endian */
 #if USB_CFG_ENDIAN == USB_CFG_LITTLE
            *read_p = (uint8_t) (odd_byte_data_temp & USB_VAL_FFH);
 #else                                 /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
            *read_p = (uint8_t) (odd_byte_data_temp >> 8);
 #endif                                /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

            /* Renewal read pointer */
            read_p += sizeof(uint8_t);
        }
    }

 #if defined(USB_HIGH_SPEED_MODULE)
    else
    {
        /* WAIT_LOOP */
        for (even = (uint16_t) (count >> 2); (even != 0); --even)
        {
            /* 32bit FIFO access */
            *(uint32_t *) read_p = hw_usb_read_fifo32(p_utr, pipemode);

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
            odd_byte_data_temp = hw_usb_read_fifo32(p_utr, pipemode);

            /* Condition compilation by the difference of the endian */
  #if USB_CFG_ENDIAN == USB_CFG_LITTLE

            /* WAIT_LOOP */
            do
            {
                *read_p            = (uint8_t) (odd_byte_data_temp & USB_VAL_FFH);
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
 #endif /* defined (USB_HIGH_SPEED_MODULE) */

    return read_p;
}

/******************************************************************************
 * End of function usb_pstd_read_fifo
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_forced_termination
 * Description     : Terminate data transmission and reception.
 * Arguments       : uint16_t pipe     : Pipe Number
 *               : uint16_t status   : Transfer status type
 * Return value    : none
 * Note            : In the case of timeout status, it does not call back.
 ******************************************************************************/
void usb_pstd_forced_termination (uint16_t pipe, uint16_t status, usb_utr_t * p_utr)
{
    uint16_t buffer;

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_set_nak(p_utr, pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(p_utr, pipe);

    /* Disable Not Ready Interrupt */
    hw_usb_clear_nrdyenb(p_utr, pipe);

    /* Disable Empty Interrupt */
    hw_usb_clear_bempenb(p_utr, pipe);

    usb_cstd_clr_transaction_counter(p_utr, pipe);

    /* Clear CFIFO-port */
    buffer = hw_usb_read_fifosel(p_utr, USB_CUSE);
    if ((buffer & USB_CURPIPE) == pipe)
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(p_utr, (uint16_t) USB_PIPE0, (uint16_t) USB_CUSE, USB_FALSE);
    }

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

    /* Clear D0FIFO-port */
    buffer = hw_usb_read_fifosel(p_utr, USB_D0USE);
    if ((buffer & USB_CURPIPE) == pipe)
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(p_utr, (uint16_t) USB_PIPE0, (uint16_t) USB_D0USE, USB_FALSE);

        /* DMA Transfer request disable */
        hw_usb_clear_dreqe(p_utr, USB_D0USE);
    }

    /* Clear D1FIFO-port */
    buffer = hw_usb_read_fifosel(p_utr, USB_D1USE);
    if ((buffer & USB_CURPIPE) == pipe)
    {
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(p_utr, (uint16_t) USB_PIPE0, (uint16_t) USB_D1USE, USB_FALSE);

        /* DMA Transfer request disable */
        hw_usb_clear_dreqe(p_utr, USB_D1USE);
    }
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    /* Do Aclr */
    usb_cstd_do_aclrm(p_utr, pipe);

    /* FIFO buffer SPLIT transaction initialized */
    hw_usb_set_csclr(p_utr, pipe);

    /* Call Back */
    if (USB_NULL != g_p_usb_pstd_pipe[pipe])
    {
        /* Transfer information set */
        g_p_usb_pstd_pipe[pipe]->tranlen = g_usb_pstd_data_cnt[pipe];
        g_p_usb_pstd_pipe[pipe]->status  = status;
        g_p_usb_pstd_pipe[pipe]->pipectr = hw_usb_read_pipectr(p_utr, pipe);

        if (USB_NULL != (g_p_usb_pstd_pipe[pipe]->complete))
        {
            (g_p_usb_pstd_pipe[pipe]->complete)(g_p_usb_pstd_pipe[pipe], USB_NULL, USB_NULL);
        }

 #if (BSP_CFG_RTOS == 0)
        g_p_usb_pstd_pipe[pipe] = (usb_utr_t *) USB_NULL;
 #else                                 /* (BSP_CFG_RTOS == 0) */
  #if (BSP_CFG_RTOS == 1)
        USB_REL_BLK(1, g_p_usb_pstd_pipe[pipe]);
  #elif (BSP_CFG_RTOS == 2)            /* #if (BSP_CFG_RTOS == 1) */
        vPortFree(g_p_usb_pstd_pipe[pipe]);
  #endif                               /* #if (BSP_CFG_RTOS == 1) */
        g_p_usb_pstd_pipe[pipe] = (usb_utr_t *) USB_NULL;
        usb_cstd_pipe_msg_re_forward(p_utr->ip, pipe);
 #endif                                /* (BSP_CFG_RTOS == 0) */
    }
}

/******************************************************************************
 * End of function usb_pstd_forced_termination
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_interrupt_clock
 * Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_interrupt_clock (uint8_t usb_ip)
{
    if (g_usb_cstd_suspend_mode != USB_NORMAL_MODE)
    {
        hw_usb_set_suspendm(usb_ip);   /* UTMI Normal Mode (Not Suspend Mode) */
        usb_cpu_delay_1us(USB_CPU_DELAY_US);
        g_usb_cstd_suspend_mode = USB_NORMAL_MODE;
    }
}

/******************************************************************************
 * End of function usb_pstd_interrupt_clock
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_self_clock
 * Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_self_clock (uint8_t usb_ip)
{
    if (g_usb_cstd_suspend_mode != USB_NORMAL_MODE)
    {
        hw_usb_set_suspendm(usb_ip);   /* UTMI Normal Mode (Not Suspend Mode) */
        usb_cpu_delay_1us(USB_CPU_DELAY_US);
        g_usb_cstd_suspend_mode = USB_NORMAL_MODE;
    }
}

/******************************************************************************
 * End of function usb_pstd_self_clock
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_stop_clock
 * Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_stop_clock (uint8_t usb_ip)
{
    g_usb_cstd_suspend_mode = USB_SUSPEND_MODE;
    hw_usb_clear_suspm(usb_ip);        /* UTMI Suspend Mode */
}

/******************************************************************************
 * End of function usb_pstd_stop_clock
 ******************************************************************************/
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

/******************************************************************************
 * End of file
 ******************************************************************************/
