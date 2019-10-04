/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/
/*******************************************************************************
Includes   <System Includes>, "Project Includes"
*******************************************************************************/
#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "../driver/inc/r_usb_typedef.h"
#include "../driver/inc/r_usb_extern.h"
#include "inc/r_usb_bitdefine.h"
#include "inc/r_usb_reg_access.h"

#define ACTIVE_CNT_NUMBER       (100)


#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
#include "r_usb_dmac.h"

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
#if USB_CFG_DTC == USB_CFG_ENABLE
dtc_transfer_data_t        g_usb_dtc_transfer_data[USB_DMA_USE_CH_MAX];

#endif  /* USB_CFG_DTC == USB_CFG_ENABLE */

#if (BSP_CFG_RTOS == 0)
usb_dma_int_t   gs_usb_cstd_dma_int;
#endif /* (BSP_CFG_RTOS == 0) */

uint32_t    g_usb_cstd_dma_size[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 buffer size */
uint16_t    g_usb_cstd_dma_fifo[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 FIFO buffer size */
uint16_t    g_usb_cstd_dma_pipe[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 pipe number */

uint8_t     g_usb_cstd_dma_ch[USB_NUM_USBIP][USB_FIFO_ACCESS_NUM_MAX];  /* DMA ch no. table */

uint8_t     g_usb_cstd_dma_fraction_size[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];   /* fraction size(1-3) */
uint32_t    g_usb_cstd_dma_fraction_adr[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];    /* fraction data address */
uint32_t  g_fifo_address[USB_NUM_USBIP][USB_FIFO_ACCESS_NUM_MAX][USB_FIFO_ACCSESS_TYPE_NUM] =
{
  {
    /* IP0 */
    /* 32bit                        16bit                           8bit */
    {(uint32_t)0,                   (uint32_t)&USB_M0.CFIFO.WORD,   (uint32_t)&USB_M0.CFIFO.BYTE.L},    /* USB0 CFIFO  address */
    {(uint32_t)0,                   (uint32_t)&USB_M0.D0FIFO.WORD,  (uint32_t)&USB_M0.D0FIFO.BYTE.L},   /* USB0 D0FIFO address */
    {(uint32_t)0,                   (uint32_t)&USB_M0.D1FIFO.WORD,  (uint32_t)&USB_M0.D1FIFO.BYTE.L},
  },
#if USB_NUM_USBIP == 2
  {
    /* IP1 */

#if defined(BSP_MCU_GROUP_RA6M3)

    /* Little */
#if USB_CFG_ENDIAN == USB_CFG_LITTLE
    {(uint32_t)&USB_M1.CFIFO.LONG,  (uint32_t)&USB_M1.CFIFO.WORD.H, (uint32_t)&USB_M1.CFIFO.BYTE.HH},  /* USBA CFIFO  adr Little */
    {(uint32_t)&USB_M1.D0FIFO.LONG, (uint32_t)&USB_M1.D0FIFO.WORD.H,(uint32_t)&USB_M1.D0FIFO.BYTE.HH}, /* USBA D0FIFO adr Little */
    {(uint32_t)&USB_M1.D1FIFO.LONG, (uint32_t)&USB_M1.D1FIFO.WORD.H,(uint32_t)&USB_M1.D1FIFO.BYTE.HH}  /* USBA D1FIFO adr Little */

#endif  /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

    /* Big */
#if USB_CFG_ENDIAN == USB_CFG_BIG
    {(uint32_t)&USB_M1.CFIFO.LONG,  (uint32_t)&USB_M1.CFIFO.WORD.L, (uint32_t)&USB_M1.CFIFO.BYTE.LL},  /* USBA CFIFO  adr Big */
    {(uint32_t)&USB_M1.D0FIFO.LONG, (uint32_t)&USB_M1.D0FIFO.WORD.L,(uint32_t)&USB_M1.D0FIFO.BYTE.LL}, /* USBA D0FIFO adr Big */
    {(uint32_t)&USB_M1.D1FIFO.LONG, (uint32_t)&USB_M1.D1FIFO.WORD.L,(uint32_t)&USB_M1.D1FIFO.BYTE.LL}  /* USBA D1FIFO adr Big */

#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
  }

#endif  /* USB_NUM_USBIP == 2 */
};

/******************************************************************************
Function Name   : usb_cstd_dma_send_start
Description     : Start transfer using DMA. If transfer size is 0, write
                : more data to buffer.
Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure
                : uint16_t pipe   : Pipe number
                : uint16_t useport: FIFO select
Return value    : none
******************************************************************************/
void usb_cstd_dma_send_start(usb_utr_t *ptr, uint16_t pipe, uint16_t useport)
{
    uint32_t    dma_size;
    uint8_t     *p_data_ptr;
    uint16_t    ip;
    uint16_t    ch;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_data_ptr = gp_usb_hstd_data_ptr[ptr->ip][pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_data_ptr = gp_usb_pstd_data[pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    ch = usb_cstd_dma_ref_ch_no(ip, useport);

    dma_size = g_usb_cstd_dma_size[ip][ch];

     if (USB_IP0 == ip)
     {
        dma_size &= ~USB_BIT_MBW16;
     }
     else
     {
#if defined(BSP_MCU_GROUP_RA6M3)
        dma_size &= ~USB_BIT_MBW32;
#else /* defined(BSP_MCU_GROUP_RA6M3) */
        dma_size &= ~USB_BIT_MBW16;
#endif /* defined(BSP_MCU_GROUP_RA6M3) */
     }

    if (0u != dma_size)
    {
        hw_usb_clear_dreqe(ptr, useport);       /* DMA Transfer request disable */

        usb_cstd_dma_clear_ir(ptr, useport);

        if (dma_size >= g_usb_cstd_dma_fifo[ip][ch])
        {
            /* Fifo size block transfer */
            dma_size = (dma_size - (dma_size % g_usb_cstd_dma_fifo[ip][ch]));
        }
        else
        {
            if (USB_IP0 == ip)
            {
                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW16;
            }
            else
            {
    #if defined(BSP_MCU_GROUP_RA6M3)
                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW32;
    #else /* defined(BSP_MCU_GROUP_RA6M3) */
                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW16;
    #endif /* defined(BSP_MCU_GROUP_RA6M3) */
            }

            g_usb_cstd_dma_fraction_adr[ip][ch]  = (uint32_t)(p_data_ptr + dma_size);  /* fraction data address */
        }

        g_usb_cstd_dma_size[ip][ch] = dma_size;

        usb_cstd_dma_send_setting(ptr, (uint32_t)p_data_ptr, useport, dma_size);

        /* Changes the FIFO port by the pipe. */
        if (false == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }

        hw_usb_set_dreqe(ptr, useport);

        if (true == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }
    }
    else
    {
        if (USB_HOST == g_usb_usbmode)
        {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            usb_hstd_buf_to_fifo(ptr, pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
            usb_pstd_buf_to_fifo(pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
        }
    }
}
/******************************************************************************
End of function usb_cstd_dma_send_start
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_rcv_start
Description     : Start transfer using DMA. If transfer size is 0, clear DMA.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t pipe     : Pipe number
                : uint16_t useport  : FIFO select
Return value    : none
******************************************************************************/
void usb_cstd_dma_rcv_start(usb_utr_t *ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t mxps;
    uint8_t     *p_data_ptr;
    uint16_t    ip;
    uint16_t    ch;
    uint16_t    trncnt;

    if (USB_NULL != ptr)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_data_ptr = gp_usb_hstd_data_ptr[ptr->ip][pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_data_ptr = gp_usb_pstd_data[pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    ch = usb_cstd_dma_ref_ch_no(ip, useport);

    /* Data size check */
    if (0u != g_usb_cstd_dma_size[ip][ch])
    {
        hw_usb_clear_dreqe(ptr, useport);       /* DMA Transfer request disable */

        usb_cstd_dma_clear_ir(ptr, useport);

        usb_cstd_dma_rcv_setting(ptr, (uint32_t)p_data_ptr, useport, g_usb_cstd_dma_size[ip][ch]);

        /* Changes the FIFO port by the pipe. */
        if (false == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }

        /* Max Packet Size */
        mxps = usb_cstd_get_maxpacket_size(ptr, pipe);

        /* Set Transaction counter */
        trncnt = (uint16_t)(((g_usb_cstd_dma_size[ip][ch] - (uint32_t)1U)/ mxps) + (uint32_t)1U);
        usb_cstd_set_transaction_counter(ptr, pipe, trncnt);


        /* Enable Ready Interrupt */
        hw_usb_set_brdyenb(ptr, pipe);

        /* Enable Not Ready Interrupt */
        usb_cstd_nrdy_enable(ptr, pipe);

        /* usb fifo set automatic clear mode  */
        hw_usb_clear_dclrm(ptr, useport);

        /* Set DREQ enable */
        hw_usb_set_dreqe(ptr, useport);

        if (true == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }
        /* Set BUF */
        usb_cstd_set_buf(ptr, pipe);
    }
}
/******************************************************************************
End of function usb_cstd_dma_rcv_start
******************************************************************************/


/******************************************************************************
Function Name   : usb_cstd_dfifo_end
Description     : Setup external variables used for USB data transfer; to reg-
                : ister if you want to stop the transfer of DMA.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t useport  : FIFO select
Return value    : none
******************************************************************************/
void usb_cstd_dfifo_end(usb_utr_t *ptr, uint16_t useport)
{
    uint16_t    pipe;
    uint16_t    ip;
    uint16_t    channel;

    if (USB_NULL == ptr)
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP0
        ip = USB_IP0;

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        ip = USB_IP1;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }
    else
    {
        ip = ptr->ip;
    }

    channel = usb_cstd_dma_ref_ch_no(ip, useport);
    pipe = g_usb_cstd_dma_pipe[ip][channel];

    if (USB_NULL == ptr)
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        /* received data size */
        g_usb_pstd_data_cnt[pipe] -= g_usb_cstd_dma_size[ip][channel];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        /* received data size */
        g_usb_hstd_data_cnt[ptr->ip][pipe] -= g_usb_cstd_dma_size[ip][channel];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}
/******************************************************************************
End of function usb_cstd_dfifo_end
******************************************************************************/

#if (BSP_CFG_RTOS == 0)
/******************************************************************************
Function Name   : usb_cstd_dma_driver
Description     : USB DMA transfer complete process.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_cstd_dma_driver(void)
{
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;

#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

    if (gs_usb_cstd_dma_int.wp != gs_usb_cstd_dma_int.rp)
    {
        if (USB_HOST == g_usb_usbmode)
        {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            utr.ip = gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].ip;
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

            usb_cstd_dma_stop(utr.ip, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type);  /* Stop DMA,FIFO access */

            usb_cstd_dma_send_continue(&utr, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type);

#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
        }
        else
        {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

            usb_cstd_dma_stop(USB_CFG_USE_USBIP, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type);  /* Stop DMA,FIFO access */

            usb_cstd_dma_send_continue(USB_NULL, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type);

#endif  /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
        }

        /* Read count up */
        gs_usb_cstd_dma_int.rp = ((gs_usb_cstd_dma_int.rp+1) % USB_INT_BUFSIZE);
    }
}
/******************************************************************************
End of function usb_cstd_dma_driver
******************************************************************************/
#endif  /* BSP_CFG_RTOS_USED == 0 */

/******************************************************************************
Function Name   : usb_cstd_dma_send_restart
Description     : Start transfer using DMA0. accsess size 32bytes.
Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
                : uint32_t src       : transfer data pointer
                : uint32_t data_size : transfer data size
                : uint16_t pipe      : Pipe number
Return value    : none
******************************************************************************/
void usb_cstd_dma_send_restart(usb_utr_t *ptr, uint32_t src, uint32_t data_size, uint8_t pipe)
{
    uint16_t useport;

    if (USB_PIPE1 == pipe)
    {
        useport = USB_D0USE;
    }
    else
    {
        useport = USB_D1USE;
    }

    /* Changes the FIFO port by the pipe. */
    if (false == usb_check_use_usba_module(ptr))
    {
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
    }

    hw_usb_clear_dreqe(ptr, useport);       /* DMA Transfer request disable */

    usb_cstd_dma_clear_ir(ptr, useport);

    /* dma trans setting Divisible by FIFO buffer size  */
    usb_cstd_dma_send_setting(ptr, src, useport, data_size);

    /* Set DREQ enable */
    hw_usb_set_dreqe(ptr, useport);

    if (true == usb_check_use_usba_module(ptr))
    {
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
    }
}
/******************************************************************************
End of function usb_cstd_dma_send_restart
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_send_continue
Description     : Set end of DMA transfer. Set to restart DMA trans-
                : fer according to data size of remaining functions to be pro-
                : cessed.
Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
                : uint16_t useport   : FIFO select
Return value    : none
******************************************************************************/
void usb_cstd_dma_send_continue(usb_utr_t *ptr, uint16_t useport)
{
    uint8_t     *p_src_adr;
    uint16_t    pipe;
    uint32_t    *p_data_cnt;
    uint8_t     *p_data_ptr;
    uint16_t    ip;
    uint16_t    channel;
    uint16_t    dma_size;
    bool        cpu_write = false;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    channel = usb_cstd_dma_ref_ch_no(ip, useport);
    pipe = g_usb_cstd_dma_pipe[ip][channel];

    if (USB_NULL != ptr)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_data_cnt = &g_usb_hstd_data_cnt[ptr->ip][pipe];
        p_data_ptr = gp_usb_hstd_data_ptr[ptr->ip][pipe];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_data_cnt = &g_usb_pstd_data_cnt[pipe];
        p_data_ptr = gp_usb_pstd_data[pipe];
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    /* trans data smaller than Buffer size */
    /*  equal all data transfer end  */
    if ((*p_data_cnt) < g_usb_cstd_dma_fifo[ip][channel])
    {
        if (g_usb_cstd_dma_fraction_size[ip][channel] > 0)  /* fraction size(1-3) */
        {
            cpu_write = true;           /* Set flag for CPU FIFO Write */
        }
        else
        {
            /* FIFO buffer empty flag clear */
            hw_usb_clear_status_bemp(ptr, pipe);

            /* bval control for transfer enable fifo 2 usb control */
            hw_usb_set_bval(ptr, useport);

            /* FIFO bufer empty interrupt enable */
            hw_usb_set_bempenb(ptr, pipe);
        }
    }
    else
    {
        /* update remaining transfer data size */
        (*p_data_cnt) -= g_usb_cstd_dma_size[ip][channel];

        /* check transfer remaining data */
        if (0u == (*p_data_cnt))
        {
            /* FIFO buffer empty flag clear */
            hw_usb_clear_status_bemp(ptr, pipe);

            /* check FIFO_EMPTY / INBUF bit */
            if ((hw_usb_read_pipectr(ptr,  pipe ) & USB_INBUFM) != USB_INBUFM)
            {
                /* DMA transfer function end. call callback function */

                if (USB_NULL != ptr)
                {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
                    usb_hstd_data_end(ptr, pipe, (uint16_t)USB_DATA_NONE);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
                }
                else
                {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                    usb_pstd_data_end(pipe, (uint16_t)USB_DATA_NONE);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
                }
            }
            else
            {
                /* FIFO bufer empty interrupt enable */
                hw_usb_set_bempenb(ptr, pipe);
            }
        }
        else
        {
            /* dma trans remaining data */
            /* DMA source address update */
            p_src_adr = (uint8_t *)((uint32_t)p_data_ptr + g_usb_cstd_dma_size[ip][channel]);

            /* DMA Transfer size update */
            g_usb_cstd_dma_size[ip][channel] = *p_data_cnt;

            dma_size = g_usb_cstd_dma_size[ip][channel];

            if (USB_IP0 == ip)
            {
                g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW16;   /* fraction size(1-3) */
                dma_size &= ~USB_BIT_MBW16;
            }
            else
            {
#if defined(BSP_MCU_GROUP_RA6M3)
                g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW32;   /* fraction size(1-3) */
                dma_size &= ~USB_BIT_MBW32;
#else /* defined(BSP_MCU_GROUP_RA6M3) */
                g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW16;   /* fraction size(1-3) */
                dma_size &= ~USB_BIT_MBW16;
#endif /* defined(BSP_MCU_GROUP_RA6M3) */
            }
            g_usb_cstd_dma_fraction_adr[ip][channel]  = (uint32_t)(p_src_adr + dma_size);   /* fraction data address */

            if (0 != dma_size)
            {
                g_usb_cstd_dma_size[ip][channel] = dma_size;

                /* DMA0 1byte trans */
                usb_cstd_dma_send_restart(ptr, (uint32_t)p_src_adr, dma_size, pipe);
            }
            else
            {
                cpu_write = true;           /* Set flag for CPU FIFO Write */
            }
        }
    }

    if (true == cpu_write)
    {
        if (USB_HOST == g_usb_usbmode)
        {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            g_usb_hstd_data_cnt[ptr->ip][pipe] = (uint32_t)g_usb_cstd_dma_fraction_size[ip][channel]; /* fraction size(1-3) */
            gp_usb_hstd_data_ptr[ptr->ip][pipe] = (uint8_t *)g_usb_cstd_dma_fraction_adr[ip][channel];    /* fraction data address */
            usb_hstd_buf_to_fifo(ptr, pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
            g_usb_pstd_data_cnt[pipe] = (uint32_t)g_usb_cstd_dma_fraction_size[ip][channel];          /* fraction size(1-3) */
            gp_usb_pstd_data[pipe] = (uint8_t *)g_usb_cstd_dma_fraction_adr[ip][channel];             /* fraction data address */
            usb_pstd_buf_to_fifo(pipe, useport);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
        }
        g_usb_cstd_dma_fraction_size[ip][channel] = 0;
    }
}
/******************************************************************************
End of function usb_cstd_dma_send_continue
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_get_ir_vect
Description     : Get vector no. of USB DxFIFO
Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
                : uint16_t  useport     : FIFO select
Return value    : Vector no.
******************************************************************************/
uint16_t    usb_cstd_dma_get_ir_vect(usb_utr_t *ptr, uint16_t use_port)
{
    uint16_t    ip;
    uint16_t    vect;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    if (USB_IP0 == ip)
    {
        if (USB_D0USE == use_port)
        {
            vect = IR_USB0_D0FIFO0;
        }
        else
        {
            vect = IR_USB0_D1FIFO0;
        }
    }
#if USB_NUM_USBIP == 2
    else
    {
#if defined(BSP_MCU_GROUP_RA6M3)
        if (USB_D0USE == use_port)
        {
            vect = IR_USBA_D0FIFO2;
        }
        else
        {
            vect = IR_USBA_D1FIFO2;
        }
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

#if defined(BSP_MCU_RX63N)
        if (USB_D0USE == use_port)
        {
            vect = IR_USB1_D0FIFO1;
        }
        else
        {
            vect = IR_USB1_D1FIFO1;
        }
#endif  /* defined(BSP_MCU_RX63N) */
    }

#endif /* USB_NUM_USBIP == 2 */

    return vect;
}
/******************************************************************************
End of function usb_cstd_dma_get_ir_vect
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_clear_ir
Description     : Clear Interrupt status of USB DxFIFO.
Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
                : uint16_t  useport     : FIFO select
Return value    : none
******************************************************************************/
void    usb_cstd_dma_clear_ir(usb_utr_t *ptr, uint16_t use_port)
{
    uint16_t    ip;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    if (USB_IP0 == ip)
    {
        if (USB_D0USE == use_port)
        {
            IR (USB0, D0FIFO0) = 0;
        }
        else
        {
            IR (USB0, D1FIFO0) = 0;
        }
    }
#if USB_NUM_USBIP == 2
    else
    {
#if defined(BSP_MCU_GROUP_RA6M3)
        if (USB_D0USE == use_port)
        {
            IR (USBA, D0FIFO2) = 0;
        }
        else
        {
            IR (USBA, D1FIFO2) = 0;
        }
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

#if defined(BSP_MCU_RX63N)
        if (USB_D0USE == use_port)
        {
            IR (USB1, D0FIFO1) = 0;
        }
        else
        {
            IR (USB1, D1FIFO1) = 0;
        }
#endif  /* defined(BSP_MCU_RX63N) */
    }
#endif /* USB_NUM_USBIP == 2 */
}
/******************************************************************************
End of function usb_cstd_dma_clear_ir
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_set_ch_no
Description     : Set DMA channel no.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t useport  : FIFO select
                : uint8_t dma_ch_no : DMA channel no.
Return value    : none
******************************************************************************/
void        usb_cstd_dma_set_ch_no(uint16_t ip_no, uint16_t use_port, uint8_t dma_ch_no)
{
    g_usb_cstd_dma_ch[ip_no][use_port] = dma_ch_no;  /* DMA ch no. table */
}
/******************************************************************************
End of function usb_cstd_dma_set_ch_no
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_ref_ch_no
Description     : Get DMA channel no.
Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
                : uint16_t  useport : FIFO select
Return value    : DMA channel no.
******************************************************************************/
uint8_t     usb_cstd_dma_ref_ch_no(uint16_t ip_no, uint16_t use_port)
{
    return g_usb_cstd_dma_ch[ip_no][use_port];  /* DMA ch no. table */
}
/******************************************************************************
End of function usb_cstd_dma_ref_ch_no
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_send_complete
Description     : Set event for DMA transfer complete of Buffer to DxFIFO.
Arguments       : uint16_t ip_no  : IP no.(USB_IP0/USB_IP1)
                : uint16_t useport: FIFO select(USB_D0USE/USB_D1USE)
Return value    : none
******************************************************************************/
void usb_cstd_dma_send_complete(uint16_t ip_no, uint16_t use_port)
{
#if (BSP_CFG_RTOS == 2)

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   *p_host;
    usb_utr_t   utr;
#endif
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_utr_t   *p_peri;
#endif

    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip = ip_no;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        hw_usb_clear_dreqe(&utr, use_port);       /* DMA Transfer request disable */

        p_host          = (usb_utr_t *)get_usb_int_buf();
        p_host->ip      = ip_no;
        p_host->msginfo = USB_MSG_HCD_INT;
        p_host->keyword = USB_INT_DXFIFO;
        p_host->status  = use_port;

        p_host->ipp     = utr.ipp;
        USB_ISND_MSG(USB_HCD_MBX, (usb_msg_t *)p_host);
#endif  /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        hw_usb_clear_dreqe(USB_NULL, use_port);       /* DMA Transfer request disable */

        p_peri              = (usb_utr_t *)get_usb_int_buf();
        p_peri->ip          = ip_no;
        p_peri->msginfo     = USB_MSG_PCD_INT;
        p_peri->keyword     = USB_INT_DXFIFO;
        p_peri->status      = use_port;

        USB_ISND_MSG(USB_PCD_MBX, (usb_msg_t *)p_peri);
#endif  /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }


#else   /* (BSP_CFG_RTOS == 2) */


#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t   utr;
#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.wp].ip = ip_no;
    gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.wp].fifo_type = use_port;
    gs_usb_cstd_dma_int.wp = ((gs_usb_cstd_dma_int.wp+1) % USB_INT_BUFSIZE);

    if (USB_HOST == g_usb_usbmode)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip = ip_no;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        hw_usb_clear_dreqe(&utr, use_port);       /* DMA Transfer request disable */

#endif  /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        hw_usb_clear_dreqe(USB_NULL, use_port);       /* DMA Transfer request disable */

#endif  /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }
#endif  /* (BSP_CFG_RTOS == 2) */
}
/******************************************************************************
End of function usb_cstd_dma_send_complete
******************************************************************************/

/*******************************************************************************
* Function Name: usb_cstd_d0fifo_cb
* Description  : Interrupt service routine of D0FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_cstd_d0fifo_cb (void)
{
    usb_cstd_dma_send_complete(USB_IP0, USB_D0USE);
}
/******************************************************************************
End of function usb_cstd_d0fifo_cb
******************************************************************************/

/*******************************************************************************
* Function Name: usb_cstd_d1fifo_cb
* Description  : Interrupt service routine of D1FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_cstd_d1fifo_cb (void)
{
    usb_cstd_dma_send_complete(USB_IP0, USB_D1USE);
}
/******************************************************************************
End of function usb_ip1_d0fifo_callback
******************************************************************************/

/*******************************************************************************
* Function Name: usb_ip1_d0fifo_callback
* Description  : Interrupt service routine of D0FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_ip1_d0fifo_callback (void)
{
    usb_cstd_dma_send_complete(USB_IP1, USB_D0USE);
}
/******************************************************************************
End of function usb_ip1_d0fifo_callback
******************************************************************************/

/*******************************************************************************
* Function Name: usb_ip1_d1fifo_callback
* Description  : Interrupt service routine of D1FIFO
* Arguments    : none
* Return Value : none
*******************************************************************************/
void usb_ip1_d1fifo_callback (void)
{
    usb_cstd_dma_send_complete(USB_IP1, USB_D1USE);
}
/******************************************************************************
End of function usb_ip1_d1fifo_callback
******************************************************************************/

/******************************************************************************
Function Name   : hw_usb_get_dxfifo_adr
Description     : Get FIFO port address of DMA/DTC.
Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
                : uint16_t  use_port    : FIFO select
                : uint16_t  bit_width   : Access bit size of USB DxFIFO
Return          : Address of FIFO port.
******************************************************************************/
uint32_t hw_usb_get_dxfifo_adr(usb_utr_t *ptr, uint16_t use_port, uint16_t bit_width)
{
    uint32_t    address;
    uint8_t     ip;
    


    if (USB_NULL != ptr)
    {
        /* Host mode */
        if (USB_IP0 == ptr->ip)
        {
            ip = USB_IP0;
        }
        else
        {
            ip = USB_IP1;
        }
    }
    else
    {
        /* Peri mode */
#if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;
#else
        /* USB1/USBA */
        ip = USB_IP1;
#endif
    }

    address = g_fifo_address[ip][use_port][bit_width];      /* Set address of FIFO port */
    return address;
}
/******************************************************************************
End of function hw_usb_get_dxfifo_adr
******************************************************************************/

#if USB_CFG_DMA == USB_CFG_ENABLE
/******************************************************************************
Function Name   : usb_cstd_dma_rcv_setting
Description     : FIFO to Buffer data read DMA start
Arguments       : usb_utr_t *ptr         : Pointer to usb_utr_t structure
                : uint32_t des_addr      : Source address
                : uint16_t useport       : FIFO Access mode
                : uint32_t transfer_size : Transfer size
Return value    : void
******************************************************************************/
void usb_cstd_dma_rcv_setting(usb_utr_t *ptr, uint32_t des_addr, uint16_t useport, uint32_t transfer_size)
{
    dmaca_transfer_data_cfg_t   td_cfg;
    dmaca_stat_t                dmac_status;
    uint8_t                     dma_ch;
    uint16_t                    vect;
    uint16_t                    ip;
    uint16_t                    active_cnt;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_cstd_dma_ref_ch_no(ip, useport);


    vect = usb_cstd_dma_get_ir_vect(ptr, useport);

    active_cnt = 0;
    /* Wait for Complete of DMA transfer. */
    /* WAIT_LOOP */
    do
    {
        R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);
        if(true == dmac_status.act_stat)
        {
            active_cnt = 0;
        }
        else
        {
            active_cnt ++;
        }
    }
    while(active_cnt < ACTIVE_CNT_NUMBER);

    R_DMACA_Control(dma_ch, DMACA_CMD_DTIF_STATUS_CLR, &dmac_status);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
#if defined(BSP_MCU_GROUP_RA6M3)
    if (USB_IP1 == ip)
    {
        td_cfg.data_size    = DMACA_DATA_SIZE_LWORD;
        td_cfg.p_src_addr   = (void *)hw_usb_get_dxfifo_adr(ptr, useport, USB_FIFO_ACCESS_TYPE_32BIT);
        td_cfg.block_size   = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /4) +1;
    }
    else
    {

#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
        td_cfg.data_size    = DMACA_DATA_SIZE_WORD;
        td_cfg.p_src_addr   = (void *)hw_usb_get_dxfifo_adr(ptr, useport, USB_FIFO_ACCESS_TYPE_16BIT);
        td_cfg.block_size   = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /2) +1;
#if defined(BSP_MCU_GROUP_RA6M3)
    }

#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

    td_cfg.transfer_mode  = DMACA_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side = DMACA_REPEAT_BLOCK_DISABLE;
    td_cfg.act_source     = (dmaca_activation_source_t)vect;
    td_cfg.request_source = DMACA_TRANSFER_REQUEST_PERIPHERAL;
    td_cfg.dtie_request   = DMACA_TRANSFER_END_INTERRUPT_DISABLE;
    td_cfg.esie_request   = DMACA_TRANSFER_ESCAPE_END_INTERRUPT_DISABLE;
    td_cfg.rptie_request  = DMACA_REPEAT_SIZE_END_INTERRUPT_DISABLE;
    td_cfg.sarie_request  = DMACA_SRC_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.darie_request  = DMACA_DES_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.src_addr_mode  = DMACA_SRC_ADDR_FIXED;
    td_cfg.src_addr_repeat_area = DMACA_SRC_ADDR_EXT_REP_AREA_NONE;
    td_cfg.des_addr_mode  = DMACA_DES_ADDR_INCR;
    td_cfg.des_addr_repeat_area = DMACA_DES_ADDR_EXT_REP_AREA_NONE;
    td_cfg.offset_value   = 0x00000000;
    td_cfg.interrupt_sel  = DMACA_CLEAR_INTERRUPT_FLAG_BEGINNING_TRANSFER;
    td_cfg.p_des_addr     = (void *)des_addr;
    td_cfg.transfer_count = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;

    /* Call R_DMACA_Create(). */
    R_DMACA_Create(dma_ch, &td_cfg);

    R_DMACA_Int_Enable(dma_ch, USB_DMA_CH_PRI);

    /* Call R_DMACA_Control().
    Enable DMAC transfer. */
    R_DMACA_Control(dma_ch, DMACA_CMD_ENABLE, &dmac_status);
}
/******************************************************************************
End of function usb_cstd_dma_rcv_setting
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_send_setting
Description     : Buffer to FIFO data write DMA start
Arguments       : usb_utr_t *ptr            : Pointer to usb_utr_t structure
                : uint32_t  src_adr         : Source address
                : uint16_t  useport         : FIFO Access mode
                : uint32_t  transfer_size   : Transfer size
Return value    : none
******************************************************************************/
void usb_cstd_dma_send_setting(usb_utr_t *ptr, uint32_t src_adr, uint16_t useport, uint32_t transfer_size)
{
    dmaca_transfer_data_cfg_t   td_cfg;
    dmaca_stat_t                dmac_status;
    uint16_t                    vect;
    uint16_t                    bit_width;
    uint8_t                     dma_ch;
    uint16_t                    ip;
    uint16_t                    block_size;
    uint16_t                    active_cnt;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_cstd_dma_ref_ch_no(ip, useport);

    if (USB_D0USE == useport)
    {
        if (USB_IP0 == ip)
        {
            R_DMACA_Int_Callback(dma_ch, (void *) usb_cstd_d0fifo_cb);
        }
        else
        {
            R_DMACA_Int_Callback(dma_ch, (void *) usb_ip1_d0fifo_callback);
        }
    }
    else
    {
        if (USB_IP0 == ip)
        {
            R_DMACA_Int_Callback(dma_ch, (void *) usb_cstd_d1fifo_cb);
        }
        else
        {
            R_DMACA_Int_Callback(dma_ch, (void *) usb_ip1_d1fifo_callback);
        }
    }

    if (g_usb_cstd_dma_fifo[ip][dma_ch] > transfer_size)
    {
        block_size       = transfer_size;
    }
    else
    {
        block_size       = g_usb_cstd_dma_fifo[ip][dma_ch];
    }

#if defined(BSP_MCU_GROUP_RA6M3)
    if ((0 == (transfer_size & 0x03)) && (USB_IP1 == ip))
    {
        block_size       = ((block_size -1) /4) +1;
        bit_width        = USB_FIFO_ACCESS_TYPE_32BIT;
        td_cfg.data_size = DMACA_DATA_SIZE_LWORD;
    }
    else
    {

#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
        block_size       = ((block_size -1) /2) +1;
        bit_width        = USB_FIFO_ACCESS_TYPE_16BIT;
        td_cfg.data_size = DMACA_DATA_SIZE_WORD;
#if defined(BSP_MCU_GROUP_RA6M3)
    }

#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

    vect = usb_cstd_dma_get_ir_vect(ptr, useport);

    active_cnt = 0;
    /* Wait for Complete of DMA transfer. */
    /* WAIT_LOOP */
    do
    {
        R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);
        if(true == dmac_status.act_stat)
        {
            active_cnt = 0;
        }
        else
        {
            active_cnt ++;
        }
    }
    while(active_cnt < ACTIVE_CNT_NUMBER);

    R_DMACA_Control(dma_ch, DMACA_CMD_DTIF_STATUS_CLR, &dmac_status);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
    td_cfg.transfer_mode        = DMACA_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side    = DMACA_REPEAT_BLOCK_DISABLE;
    td_cfg.act_source           = (dmaca_activation_source_t)vect;
    td_cfg.request_source       = DMACA_TRANSFER_REQUEST_PERIPHERAL;
    td_cfg.dtie_request         = DMACA_TRANSFER_END_INTERRUPT_ENABLE;
    td_cfg.esie_request         = DMACA_TRANSFER_ESCAPE_END_INTERRUPT_DISABLE;
    td_cfg.rptie_request        = DMACA_REPEAT_SIZE_END_INTERRUPT_DISABLE;
    td_cfg.sarie_request        = DMACA_SRC_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.darie_request        = DMACA_DES_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
    td_cfg.src_addr_mode        = DMACA_SRC_ADDR_INCR;
    td_cfg.src_addr_repeat_area = DMACA_SRC_ADDR_EXT_REP_AREA_NONE;
    td_cfg.des_addr_mode        = DMACA_DES_ADDR_FIXED;
    td_cfg.des_addr_repeat_area = DMACA_DES_ADDR_EXT_REP_AREA_NONE;
    td_cfg.offset_value         = 0x00000000;
    td_cfg.interrupt_sel        = DMACA_CLEAR_INTERRUPT_FLAG_BEGINNING_TRANSFER;
    td_cfg.p_src_addr           = (void *)src_adr;
    td_cfg.p_des_addr           = (void *)hw_usb_get_dxfifo_adr(ptr, useport, bit_width);
    td_cfg.transfer_count       = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;
    td_cfg.block_size           = block_size;

    /* Call R_DMACA_Create(). */
    R_DMACA_Create(dma_ch, &td_cfg);

    R_DMACA_Int_Enable(dma_ch, USB_DMA_CH2_PRI);

    /* Call R_DMACA_Control().
    Enable DMAC transfer. */
    R_DMACA_Control(dma_ch, DMACA_CMD_ENABLE, &dmac_status);
}
/******************************************************************************
End of function usb_cstd_dma_send_setting
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_stop
Description     : DMA stop
Arguments       : uint8_t   ip_type     : USB_IP0/USB_IP1
                : uint16_t  use_port    : FIFO select
Return value    : void
******************************************************************************/
void usb_cstd_dma_stop(uint8_t ip_type, uint16_t use_port)
{
    uint16_t    active_cnt;
    dmaca_stat_t                dmac_status;
    uint8_t                     dma_ch;

    dma_ch = usb_cstd_dma_ref_ch_no(ip_type, use_port);  /* Get DMA channel no. */

    active_cnt = 0;
    /* Wait for Complete of DMA transfer. */
    /* WAIT_LOOP */
    do
    {
        R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);
        if(true == dmac_status.act_stat)
        {
            active_cnt = 0;
        }
        else
        {
            active_cnt ++;
        }
    }
    while(active_cnt < ACTIVE_CNT_NUMBER);

    R_DMACA_Control(dma_ch, DMACA_CMD_DTIF_STATUS_CLR, &dmac_status); /* Clear DMA status */
}
/******************************************************************************
End of function usb_cstd_dma_stop
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_get_crtb
Description     : Get DMA Current Transaction Byte reg B(CRTB).
Arguments       : uint16_t dma_ch : DMA Channel no.
Return value    : DMA Current Transaction Byte reg B(CRTB)
******************************************************************************/
uint16_t usb_cstd_dma_get_crtb(uint16_t dma_ch)
{
    dmaca_stat_t                dmac_status;

    R_DMACA_Control(dma_ch, DMACA_CMD_STATUS_GET, &dmac_status);

    return dmac_status.transfer_count;
}
/******************************************************************************
End of function usb_cstd_dma_get_crtb
******************************************************************************/

#endif /* USB_CFG_DMA == USB_CFG_ENABLE */

#if USB_CFG_DTC == USB_CFG_ENABLE
/******************************************************************************
Function Name   : usb_cstd_dma_rcv_setting
Description     : FIFO to Buffer data read DMA start
Arguments       : usb_utr_t *ptr         : Pointer to usb_utr_t structure
                : uint32_t des_addr      : Source address
                : uint16_t useport       : FIFO Access mode
                : uint32_t transfer_size : Transfer size
Return value    : void
******************************************************************************/
void usb_cstd_dma_rcv_setting(usb_utr_t *ptr, uint32_t des_addr, uint16_t useport, uint32_t transfer_size)
{
    dtc_transfer_data_cfg_t     td_cfg;
    dtc_stat_t                  dmac_status;
    dtc_cmd_arg_t               args;
    uint8_t                     dma_ch;
    uint16_t                    vect;
    uint16_t                    ip;
    uint16_t                    active_cnt;

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DTC_START, USB_NULL, 0);

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_DISABLE, USB_NULL, 0);

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_ENABLE, USB_NULL, 0);

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_cstd_dma_ref_ch_no(ip, useport);

    vect = usb_cstd_dma_get_ir_vect(ptr, useport);

    active_cnt = 0;
    /* Wait for Complete of DMA transfer. */
    /* WAIT_LOOP */
    do
    {
        R_DTC_Control(DTC_CMD_STATUS_GET, &dmac_status, &args);
        if(true == dmac_status.in_progress)
        {
            active_cnt = 0;
        }
        else
        {
            active_cnt ++;
        }
    }
    while(active_cnt < ACTIVE_CNT_NUMBER);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
#if defined(BSP_MCU_GROUP_RA6M3)
    if (USB_IP1 == ip)
    {
        td_cfg.data_size  = DTC_DATA_SIZE_LWORD;
        td_cfg.source_addr= hw_usb_get_dxfifo_adr(ptr, useport, USB_FIFO_ACCESS_TYPE_32BIT);
        td_cfg.block_size = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /4) +1;
    }
    else
    {
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
        td_cfg.data_size  = DTC_DATA_SIZE_WORD;
        td_cfg.source_addr= hw_usb_get_dxfifo_adr(ptr, useport, USB_FIFO_ACCESS_TYPE_16BIT);
        td_cfg.block_size = ((g_usb_cstd_dma_fifo[ip][dma_ch] -1) /2) +1;
#if defined(BSP_MCU_GROUP_RA6M3)
    }
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

    td_cfg.transfer_mode  = DTC_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side = DTC_REPEAT_BLOCK_SOURCE;
    td_cfg.src_addr_mode  = DTC_SRC_ADDR_FIXED;
    td_cfg.dest_addr_mode = DTC_DES_ADDR_INCR;
    td_cfg.dest_addr      = des_addr;
    td_cfg.transfer_count = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;
    td_cfg.chain_transfer_enable = DTC_CHAIN_TRANSFER_DISABLE;
    td_cfg.chain_transfer_mode  = DTC_CHAIN_TRANSFER_CONTINUOUSLY;
    td_cfg.response_interrupt = DTC_INTERRUPT_AFTER_ALL_COMPLETE;
#if defined(BSP_MCU_RX65N)
    td_cfg.writeback_disable = DTC_WRITEBACK_ENABLE;     /* Write-back disable or enable */
    td_cfg.sequence_end = DTC_SEQUENCE_TRANSFER_CONTINUE;          /* Sequence transfer end or continue */
    td_cfg.refer_index_table_enable = DTC_REFER_INDEX_TABLE_DISABLE; /* Index table refer or not refer */
    td_cfg.disp_add_enable = DTC_SRC_ADDR_DISP_ADD_DISABLE;       /* The displacement value is added or not added */
#endif /* defined(BSP_MCU_RX65N) */

    /* Call R_DTC_Create(). */
    R_DTC_Create((dtc_activation_source_t)vect, &g_usb_dtc_transfer_data[dma_ch], &td_cfg, 0);

    if (USB_IP0 == ip)
    {
        if (USB_D0USE == useport)
        {
            /* DTC start enable register (USB0 D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB0, D0FIFO0) = 1;
        }
        else
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB0, D1FIFO0) = 1;
        }
    }
    else
    {
#if defined(BSP_MCU_GROUP_RA6M3)
        if (USB_D0USE == useport)
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USBA, D0FIFO2) = 1;
        }
        else
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USBA, D1FIFO2) = 1;
        }
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

#if defined(BSP_MCU_RX63N)
        if (USB_D0USE == useport)
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB1, D0FIFO1) = 1;
        }
        else
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB1, D1FIFO1) = 1;
        }
#endif  /* defined(BSP_MCU_RX63N) */
    }
}
/******************************************************************************
End of function usb_cstd_dma_rcv_setting
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_send_setting
Description     : Buffer to FIFO data write DMA start
Arguments       : usb_utr_t *ptr            : Pointer to usb_utr_t structure
                : uint32_t  src_adr         : Source address
                : uint16_t  useport         : FIFO Access mode
                : uint32_t  transfer_size   : Transfer size
Return value    : none
******************************************************************************/
void usb_cstd_dma_send_setting(usb_utr_t *ptr, uint32_t src_adr, uint16_t useport, uint32_t transfer_size)
{
    dtc_transfer_data_cfg_t     td_cfg;
    dtc_stat_t                  dmac_status;
    dtc_cmd_arg_t               args;
    uint16_t                    bit_width;
    uint8_t                     dma_ch;
    uint16_t                    vect;
    uint16_t                    ip;
    uint16_t                    block_size;
    uint16_t                    active_cnt;

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    R_DTC_Control( DTC_CMD_DTC_START, USB_NULL, 0 );

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control( DTC_CMD_DATA_READ_SKIP_DISABLE, USB_NULL, 0 );

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    R_DTC_Control(DTC_CMD_DATA_READ_SKIP_ENABLE, USB_NULL, 0);

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;
    }
    else
    {
  #if USB_CFG_USE_USBIP == USB_CFG_IP0
        /* USB0 */
        ip = USB_IP0;

  #else     /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* USB1/USBA */
        ip = USB_IP1;

  #endif    /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    }

    dma_ch = usb_cstd_dma_ref_ch_no(ip, useport);

    if (g_usb_cstd_dma_fifo[ip][dma_ch] > transfer_size)
    {
        block_size       = transfer_size;
    }
    else
    {
        block_size       = g_usb_cstd_dma_fifo[ip][dma_ch];
    }

#if defined(BSP_MCU_GROUP_RA6M3)
    if ((0 == (transfer_size & 0x03)) && (USB_IP1 == ip))
    {
        block_size       = ((block_size -1) /4) +1;
        bit_width        = USB_FIFO_ACCESS_TYPE_32BIT;
        td_cfg.data_size = DTC_DATA_SIZE_LWORD;
    }
    else
    {

#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
        block_size       = ((block_size -1) /2) +1;
        bit_width        = USB_FIFO_ACCESS_TYPE_16BIT;
        td_cfg.data_size = DTC_DATA_SIZE_WORD;
#if defined(BSP_MCU_GROUP_RA6M3)
    }

#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

    vect = usb_cstd_dma_get_ir_vect(ptr, useport);

    active_cnt = 0;
    /* Wait for Complete of DMA transfer. */
    /* WAIT_LOOP */
    do
    {
        R_DTC_Control(DTC_CMD_STATUS_GET, &dmac_status, &args);
        if(true == dmac_status.in_progress)
        {
            active_cnt = 0;
        }
        else
        {
            active_cnt ++;
        }
    }
    while(active_cnt < ACTIVE_CNT_NUMBER);

/* DMA test code start */
    /* Operation - No Extended Repeat Area Function and No Offset Subtraction */
    /* Source address is fixed
    * Transfer data size is 32-bit (long word).
    * DMAC transfer mode is Repeat mode & Source side is repeat area
    * At the beginning of transfer, clear the interrupt flag of the activation source
    to 0.
    * Transfer Request source is software. */
    /* Set Transfer data configuration. */
    td_cfg.transfer_mode        = DTC_TRANSFER_MODE_BLOCK;
    td_cfg.repeat_block_side    = DTC_REPEAT_BLOCK_DESTINATION;
    td_cfg.src_addr_mode        = DTC_SRC_ADDR_INCR;
    td_cfg.dest_addr_mode       = DTC_DES_ADDR_FIXED;
    td_cfg.source_addr          = src_adr;
    td_cfg.dest_addr            = hw_usb_get_dxfifo_adr(ptr, useport, bit_width);
    td_cfg.transfer_count       = ((transfer_size -1) / g_usb_cstd_dma_fifo[ip][dma_ch]) +1;
    td_cfg.block_size           = block_size;
    td_cfg.chain_transfer_enable = DTC_CHAIN_TRANSFER_DISABLE;
    td_cfg.chain_transfer_mode  = DTC_CHAIN_TRANSFER_CONTINUOUSLY;
    td_cfg.response_interrupt   = DTC_INTERRUPT_AFTER_ALL_COMPLETE;
#if defined(BSP_MCU_RX65N)
    td_cfg.writeback_disable = DTC_WRITEBACK_ENABLE;     /* Write-back disable or enable */
    td_cfg.sequence_end = DTC_SEQUENCE_TRANSFER_CONTINUE;          /* Sequence transfer end or continue */
    td_cfg.refer_index_table_enable = DTC_REFER_INDEX_TABLE_DISABLE; /* Index table refer or not refer */
    td_cfg.disp_add_enable = DTC_SRC_ADDR_DISP_ADD_DISABLE;       /* The displacement value is added or not added */
#endif /* defined(BSP_MCU_RX65N) */

    /* Call R_DTC_Create(). */
    R_DTC_Create((dtc_activation_source_t)vect, &g_usb_dtc_transfer_data[dma_ch], &td_cfg, 0);

    if (USB_IP0 == ip)
    {
        if (USB_D0USE == useport)
        {
            /* DTC start enable register (USB0 D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB0, D0FIFO0) = 1;
            IPR (USB0, D0FIFO0) = 4U;                   /* D0FIFO0 Enable */
        }
        else
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB0, D1FIFO0) = 1;
            IPR (USB0, D1FIFO0) = 4U;                   /* D0FIFO0 Enable */
        }
    }
    else
    {
#if defined(BSP_MCU_GROUP_RA6M3)
        if (USB_D0USE == useport)
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USBA, D0FIFO2) = 1;
            IPR (USBA, D0FIFO2) = 4U;                   /* D0FIFO0 Enable */
        }
        else
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USBA, D1FIFO2) = 1;
            IPR (USBA, D1FIFO2) = 4U;                   /* D0FIFO0 Enable */
        }
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

#if defined(BSP_MCU_RX63N)
        if (USB_D0USE == useport)
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB1, D0FIFO1) = 1;
            IPR (USB1, D0FIFO1) = 4U;                   /* D0FIFO0 Enable */
        }
        else
        {
            /* DTC start enable register (USBA D0FIFO transfer enable)
            b0    DTCE     DTC start enable bit
            b7-b1 Reserved 0
            */
            DTCE (USB1, D1FIFO1) = 1;
            IPR (USB1, D1FIFO1) = 4U;                   /* D0FIFO0 Enable */
        }
#endif  /* defined(BSP_MCU_RX63N) */
    }
}
/******************************************************************************
End of function usb_cstd_dma_send_setting
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_stop
Description     : DMA stop
Arguments       : uint8_t   ip_type     : USB_IP0/USB_IP1
                : uint16_t  use_port    : FIFO select
Return value    : void
******************************************************************************/
void usb_cstd_dma_stop(uint8_t ip_type, uint16_t use_port)
{
    uint16_t    active_cnt;
    dtc_stat_t      stat;
    dtc_cmd_arg_t   args;
    usb_utr_t       utr;

    active_cnt = 0;
    /* Wait for Complete of DTC transfer. */
    /* WAIT_LOOP */
    do
    {
        R_DTC_Control(DTC_CMD_STATUS_GET, &stat, &args);
        if(true == stat.in_progress)
        {
            active_cnt = 0;
        }
        else
        {
            active_cnt ++;
        }
    }
    while(active_cnt < ACTIVE_CNT_NUMBER);

    if (USB_IP0 == ip_type)
    {
        /* DTC start enable register (USB0 D0FIFO transfer disable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        if (USB_D0USE == use_port)
        {
            DTCE (USB0, D0FIFO0) = 0;
            IPR (USB0, D0FIFO0) = 0U;                   /* D0FIFO0 Disable */
        }
        else
        {
            DTCE (USB0, D1FIFO0) = 0;
            IPR (USB0, D1FIFO0) = 0U;                   /* D0FIFO0 Disable */
        }
    }
    else
    {
        /* DTC start enable register (USBA D0FIFO transfer disable)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
#if defined(BSP_MCU_GROUP_RA6M3)
        if (USB_D0USE == use_port)
        {
            DTCE (USBA, D0FIFO2) = 0;
            IPR (USBA, D0FIFO2) = 0U;                   /* D0FIFO0 Disable */
        }
        else
        {
            DTCE (USBA, D1FIFO2) = 0;
            IPR (USBA, D1FIFO2) = 0U;                   /* D0FIFO0 Disable */
        }
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */

#if defined(BSP_MCU_RX63N)
        if (USB_D0USE == use_port)
        {
            DTCE (USB1, D0FIFO1) = 0;
            IPR (USB1, D0FIFO1) = 0U;                   /* D0FIFO0 Disable */
        }
        else
        {
            DTCE (USB1, D1FIFO1) = 0;
            IPR (USB1, D1FIFO1) = 0U;                   /* D0FIFO0 Disable */
        }
#endif  /* defined(BSP_MCU_RX63N) */
    }

    utr.ip = ip_type;
    usb_cstd_dma_clear_ir(&utr, use_port);
}
/******************************************************************************
End of function usb_cstd_dma_stop
******************************************************************************/

/******************************************************************************
Function Name   : usb_cstd_dma_get_crtb
Description     : Get DMA Current Transaction Byte reg B(CRTB).
Arguments       : uint16_t dma_ch : DMA Channel no.
Return value    : DMA Current Transaction Byte reg B(CRTB)
******************************************************************************/
uint16_t usb_cstd_dma_get_crtb(uint16_t dma_ch)
{
    uint16_t value;
    dtc_stat_t      dmac_status;
    dtc_cmd_arg_t   args;

    /* Wait Complete DTC Transfer */
    /* WAIT_LOOP */
    do
    {
        R_DTC_Control(DTC_CMD_STATUS_GET, &dmac_status, &args);
    }
    while (true == dmac_status.in_progress);  /* DTC is not active */

    /* Read DTC transfer count (CRB) */
    value = (uint16_t)(g_usb_dtc_transfer_data[dma_ch].lw4 & 0xffff);

    return value;
}
/******************************************************************************
End of function usb_cstd_dma_get_crtb
******************************************************************************/
#endif /* USB_CFG_DTC == USB_CFG_ENABLE */

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
End of file
******************************************************************************/
