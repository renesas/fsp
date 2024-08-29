/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************
 * Includes   <System Includes>, "Project Includes"
 *******************************************************************************/
#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "../driver/inc/r_usb_typedef.h"
#include "../driver/inc/r_usb_extern.h"
#include "inc/r_usb_bitdefine.h"
#include "inc/r_usb_reg_access.h"

#define ACTIVE_CNT_NUMBER    (100)

#if (USB_CFG_DMA == USB_CFG_ENABLE)
 #include "r_dmac.h"
 #include "inc/r_usb_dmac.h"

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 0)
usb_dma_int_t gs_usb_cstd_dma_int;
 #endif                                                                   /* (BSP_CFG_RTOS == 0) */
 #if (BSP_CFG_RTOS != 0)
static usb_utr_t g_usb_cstd_int_dma[USB_INT_BUFSIZE];
 #endif                                                                   /* #if (BSP_CFG_RTOS != 0)*/

usb_utr_t * get_usb_int_buf_dma(void);

uint32_t g_usb_cstd_dma_size[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];          /* DMA0 and DMA1 buffer size */
uint16_t g_usb_cstd_dma_fifo[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];          /* DMA0 and DMA1 FIFO buffer size */
uint16_t g_usb_cstd_dma_pipe[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];          /* DMA0 and DMA1 pipe number */

uint8_t g_usb_cstd_dma_ch[USB_NUM_USBIP][USB_FIFO_ACCESS_NUM_MAX];        /* DMA ch no. table */

uint8_t  g_usb_cstd_dma_fraction_size[USB_NUM_USBIP][USB_DMA_USE_CH_MAX]; /* fraction size(1-3) */
uint32_t g_usb_cstd_dma_fraction_adr[USB_NUM_USBIP][USB_DMA_USE_CH_MAX];  /* fraction data address */
uint32_t g_fifo_address[USB_NUM_USBIP][USB_FIFO_ACCESS_NUM_MAX][USB_FIFO_ACCSESS_TYPE_NUM] =
{
    {
        /* IP0 */
        /* 32bit                        16bit                           8bit */
        {(uint32_t) 0,               (uint32_t) &USB_M0->CFIFOL,
         (uint32_t) &USB_M0->CFIFOLL},  /* USB0 CFIFO  address */
        {(uint32_t) 0,               (uint32_t) &USB_M0->D0FIFOL,
         (uint32_t) &USB_M0->D0FIFOLL}, /* USB0 D0FIFO address */
        {(uint32_t) 0,               (uint32_t) &USB_M0->D1FIFOL,
         (uint32_t) &USB_M0->D1FIFOLL},
    },
 #if USB_NUM_USBIP == 2
    {
        /* IP1 */

  #if defined(USB_HIGH_SPEED_MODULE)

        /* Little */
   #if USB_CFG_ENDIAN == USB_CFG_LITTLE
        {(uint32_t) &USB_M1->CFIFO,  (uint32_t) &USB_M1->CFIFOH,
         (uint32_t) &USB_M1->CFIFOHH},  /* USBA CFIFO  adr Little */
        {(uint32_t) &USB_M1->D0FIFO, (uint32_t) &USB_M1->D0FIFOH,
         (uint32_t) &USB_M1->D0FIFOHH}, /* USBA D0FIFO adr Little */
        {(uint32_t) &USB_M1->D1FIFO, (uint32_t) &USB_M1->D1FIFOH,
         (uint32_t) &USB_M1->D1FIFOHH}  /* USBA D1FIFO adr Little */
   #endif /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

        /* Big */
   #if USB_CFG_ENDIAN == USB_CFG_BIG
        {(uint32_t) &USB_M1->CFIFO,  (uint32_t) &USB_M1->CFIFOL,
         (uint32_t) &USB_M1->CFIFOLL},  /* USBA CFIFO  adr Big */
        {(uint32_t) &USB_M1->D0FIFO, (uint32_t) &USB_M1->D0FIFOL,
         (uint32_t) &USB_M1->D0FIFOLL}, /* USBA D0FIFO adr Big */
        {(uint32_t) &USB_M1->D1FIFO, (uint32_t) &USB_M1->D1FIFOL,
         (uint32_t) &USB_M1->D1FIFOLL}  /* USBA D1FIFO adr Big */
   #endif /* USB_CFG_ENDIAN == USB_CFG_BIG */
  #else /* defined (USB_HIGH_SPEED_MODULE) */
        {(uint32_t) 0,               (uint32_t) &USB_M1->CFIFOL,
         (uint32_t) &USB_M1->CFIFOLL},  /* USB0 CFIFO  address */
        {(uint32_t) 0,               (uint32_t) &USB_M1->D0FIFOL,
         (uint32_t) &USB_M1->D0FIFOLL}, /* USB0 D0FIFO address */
        {(uint32_t) 0,               (uint32_t) &USB_M1->D1FIFOL,
         (uint32_t) &USB_M1->D1FIFOLL},
  #endif /* defined (USB_HIGH_SPEED_MODULE) */
    }
 #endif                                /* USB_NUM_USBIP == 2 */
};

/******************************************************************************
 * Function Name   : usb_cstd_dma_send_start
 * Description     : Start transfer using DMA. If transfer size is 0, write
 *              : more data to buffer.
 * Arguments       : usb_utr_t *ptr  : Pointer to usb_utr_t structure
 *              : uint16_t pipe   : Pipe number
 *              : uint16_t useport: FIFO select
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_send_start (usb_utr_t * ptr, uint16_t pipe, uint16_t useport)
{
    uint32_t  dma_size;
    uint8_t * p_data_ptr = 0;
    uint16_t  ip;
    uint16_t  ch;

    ip = ptr->ip;

    if (USB_MODE_HOST == g_usb_usbmode[ip])
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_data_ptr = gp_usb_hstd_data_ptr[ptr->ip][pipe];
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_data_ptr = gp_usb_pstd_data[pipe];
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    ch = usb_cstd_dma_ref_ch_no(ptr, useport);

    dma_size = g_usb_cstd_dma_size[ip][ch];

    if (USB_IP0 == ip)
    {
        dma_size &= ~USB_BIT_MBW16;
    }
    else
    {
 #if defined(USB_HIGH_SPEED_MODULE)
        dma_size &= ~USB_BIT_MBW32;
 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
        dma_size &= ~USB_BIT_MBW16;
 #endif /* defined (USB_HIGH_SPEED_MODULE) */
    }

    if (0U != dma_size)
    {
        hw_usb_clear_dreqe(ptr, useport); /* DMA Transfer request disable */

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

 #if USB_NUM_USBIP == 2
            else
            {
  #if defined(USB_HIGH_SPEED_MODULE)

                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW32;
  #else                                /* defined (USB_HIGH_SPEED_MODULE) */
                /* fraction size(1-3) */
                g_usb_cstd_dma_fraction_size[ip][ch] = g_usb_cstd_dma_size[ip][ch] & USB_BIT_MBW16;
  #endif /* defined (USB_HIGH_SPEED_MODULE) */
            }
 #endif                                                                               /* USB_NUM_USBIP == 2 */

            g_usb_cstd_dma_fraction_adr[ip][ch] = (uint32_t) (p_data_ptr + dma_size); /* fraction data address */
        }

        g_usb_cstd_dma_size[ip][ch] = dma_size;

        usb_cstd_dma_send_setting(ptr, (uint32_t) p_data_ptr, useport, dma_size);

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
        if (USB_MODE_HOST == g_usb_usbmode[ip])
        {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            usb_hstd_buf_to_fifo(ptr, pipe, useport);
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
            usb_pstd_buf_to_fifo(pipe, useport, ptr);
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
        } /* if (USB_MODE_HOST == g_usb_usbmode[ip]) */
    } /* if (0U != dma_size) */
}

/******************************************************************************
 * End of function usb_cstd_dma_send_start
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_rcv_start
 * Description     : Start transfer using DMA. If transfer size is 0, clear DMA.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
 *              : uint16_t pipe     : Pipe number
 *              : uint16_t useport  : FIFO select
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_rcv_start (usb_utr_t * ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t  mxps;
    uint8_t * p_data_ptr = 0;
    uint16_t  ip;
    uint16_t  ch;
    uint16_t  trncnt;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_HOST)
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_data_ptr = gp_usb_hstd_data_ptr[ptr->ip][pipe];
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        ip = ptr->ip;
    }
    else
    {
        ip = ptr->ip;
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_data_ptr = gp_usb_pstd_data[pipe];
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    ch = usb_cstd_dma_ref_ch_no(ptr, useport);

    /* Data size check */
    if (0U != g_usb_cstd_dma_size[ip][ch])
    {
        hw_usb_clear_dreqe(ptr, useport); /* DMA Transfer request disable */

        usb_cstd_dma_clear_ir(ptr, useport);

        usb_cstd_dma_rcv_setting(ptr, (uint32_t) p_data_ptr, useport, g_usb_cstd_dma_size[ip][ch]);

        /* Changes the FIFO port by the pipe. */
        if (false == usb_check_use_usba_module(ptr))
        {
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
        }

        /* Max Packet Size */
        mxps = usb_cstd_get_maxpacket_size(ptr, pipe);

        /* Set Transaction counter */
        trncnt = (uint16_t) (((g_usb_cstd_dma_size[ip][ch] - (uint32_t) 1U) / mxps) + (uint32_t) 1U);
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
 * End of function usb_cstd_dma_rcv_start
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dfifo_end
 * Description     : Setup external variables used for USB data transfer; to reg-
 *              : ister if you want to stop the transfer of DMA.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
 *              : uint16_t useport  : FIFO select
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dfifo_end (usb_utr_t * ptr, uint16_t useport)
{
    uint16_t pipe;
    uint16_t ip;
    uint16_t channel;

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
        if (USB_CFG_IP0 == ptr->ip)
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
        ip = ptr->ip;
    }

    channel = usb_cstd_dma_ref_ch_no(ptr, useport);
    pipe    = g_usb_cstd_dma_pipe[ip][channel];

    if (g_usb_usbmode[ptr->ip] == USB_MODE_PERI)
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
  #if (BSP_CFG_RTOS == 1)
        if (g_usb_pstd_data_cnt[pipe] < g_usb_cstd_dma_size[ip][channel])
        {
            g_usb_pstd_data_cnt[pipe] = 0U;
        }
        else
        {
            g_usb_pstd_data_cnt[pipe] -= g_usb_cstd_dma_size[ip][channel];
        }

  #else                                /* BSP_CFG_RTOS == 1 */
        /* received data size */
        g_usb_pstd_data_cnt[pipe] -= g_usb_cstd_dma_size[ip][channel];
  #endif /* BSP_CFG_RTOS == 1 */
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
  #if (BSP_CFG_RTOS == 1)
        if (g_usb_hstd_data_cnt[ptr->ip][pipe] < g_usb_cstd_dma_size[ip][channel])
        {
            g_usb_hstd_data_cnt[ptr->ip][pipe] = 0U;
        }
        else
        {
            g_usb_hstd_data_cnt[ptr->ip][pipe] -= g_usb_cstd_dma_size[ip][channel];
        }

  #else                                /* BSP_CFG_RTOS == 1 */
        /* received data size */
        g_usb_hstd_data_cnt[ptr->ip][pipe] -= g_usb_cstd_dma_size[ip][channel];
  #endif /* BSP_CFG_RTOS == 1 */
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
}

/******************************************************************************
 * End of function usb_cstd_dfifo_end
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_cstd_dma_driver
 * Description     : USB DMA transfer complete process.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_driver (void)
{
    usb_utr_t utr;

    if (gs_usb_cstd_dma_int.wp != gs_usb_cstd_dma_int.rp)
    {
        utr.ip            = (uint8_t) gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].ip;
        utr.p_transfer_tx = gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.wp].p_cfg->p_transfer_tx;
        utr.p_transfer_rx = gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.wp].p_cfg->p_transfer_rx;
        if (USB_MODE_HOST == g_usb_usbmode[utr.ip])
        {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

            usb_cstd_dma_stop(&utr, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type); /* Stop DMA,FIFO access */

            usb_cstd_dma_send_continue(&utr, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type);
  #endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
        }
        else
        {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
            usb_cstd_dma_stop(&utr, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type); /* Stop DMA,FIFO access */

            usb_cstd_dma_send_continue(&utr, gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.rp].fifo_type);
  #endif /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
        }

        /* Read count up */
        gs_usb_cstd_dma_int.rp = (uint8_t) (((uint8_t) (gs_usb_cstd_dma_int.rp + 1)) % USB_INT_BUFSIZE);
    }
}

/******************************************************************************
 * End of function usb_cstd_dma_driver
 ******************************************************************************/
 #endif                                /* BSP_CFG_RTOS_USED == 0 */

/******************************************************************************
 * Function Name   : usb_cstd_dma_send_restart
 * Description     : Start transfer using DMA0. accsess size 32bytes.
 * Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
 *              : uint32_t src       : transfer data pointer
 *              : uint32_t data_size : transfer data size
 *              : uint16_t pipe      : Pipe number
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_send_restart (usb_utr_t * ptr, uint32_t src, uint32_t data_size, uint8_t pipe)
{
    uint16_t useport = 0;
    uint16_t usb_dir;

    if ((USB_PIPE1 == pipe) || (USB_PIPE2 == pipe))
    {
        hw_usb_write_pipesel(ptr, pipe);
        usb_dir = hw_usb_read_pipecfg(ptr);
        usb_dir = usb_dir & USB_DIRFIELD;
        if (0 == usb_dir)
        {
            useport = USB_D0USE;
        }
        else
        {
            useport = USB_D1USE;
        }
    }

    /* Changes the FIFO port by the pipe. */
    if (false == usb_check_use_usba_module(ptr))
    {
        usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
    }

    hw_usb_clear_dreqe(ptr, useport);  /* DMA Transfer request disable */

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
 * End of function usb_cstd_dma_send_restart
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_send_continue
 * Description     : Set end of DMA transfer. Set to restart DMA trans-
 *              : fer according to data size of remaining functions to be pro-
 *              : cessed.
 * Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
 *              : uint16_t useport   : FIFO select
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_send_continue (usb_utr_t * ptr, uint16_t useport)
{
    uint8_t  * p_src_adr;
    uint8_t    pipe;
    uint32_t * p_data_cnt = 0;
    uint8_t  * p_data_ptr = 0;
    uint16_t   ip;
    uint16_t   channel;
    uint16_t   dma_size;
    bool       cpu_write = false;

    ip = ptr->ip;

    channel = usb_cstd_dma_ref_ch_no(ptr, useport);
    pipe    = (uint8_t) g_usb_cstd_dma_pipe[ip][channel];

    if (g_usb_usbmode[ip] == USB_MODE_HOST)
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        p_data_cnt = &g_usb_hstd_data_cnt[ptr->ip][pipe];
        p_data_ptr = gp_usb_hstd_data_ptr[ptr->ip][pipe];
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        p_data_cnt = &g_usb_pstd_data_cnt[pipe];
        p_data_ptr = gp_usb_pstd_data[pipe];
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    /*  trans data smaller than Buffer size */
    /*  equal all data transfer end  */
    if (p_data_cnt)
    {
        if ((*p_data_cnt) < g_usb_cstd_dma_fifo[ip][channel])
        {
            if (g_usb_cstd_dma_fraction_size[ip][channel] > 0) /* fraction size(1-3) */
            {
                cpu_write = true;                              /* Set flag for CPU FIFO Write */
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
            if (0U == (*p_data_cnt))
            {
                /* FIFO buffer empty flag clear */
                hw_usb_clear_status_bemp(ptr, pipe);

                /* check FIFO_EMPTY / INBUF bit */
                if ((hw_usb_read_pipectr(ptr, pipe) & USB_INBUFM) != USB_INBUFM)
                {
                    /* DMA transfer function end. call callback function */

                    if (g_usb_usbmode[ip] == USB_MODE_HOST)
                    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
                        usb_hstd_data_end(ptr, pipe, (uint16_t) USB_DATA_NONE);
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
                    }
                    else
                    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                        usb_pstd_data_end(pipe, (uint16_t) USB_DATA_NONE, ptr);
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
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
                p_src_adr = (uint8_t *) ((uint32_t) p_data_ptr + g_usb_cstd_dma_size[ip][channel]);

                /* DMA Transfer size update */
                g_usb_cstd_dma_size[ip][channel] = *p_data_cnt;

                dma_size = (uint16_t) g_usb_cstd_dma_size[ip][channel];

                if (USB_IP0 == ip)
                {
                    g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW16; /* fraction size(1-3) */
                    dma_size = (uint16_t) (dma_size & ~USB_BIT_MBW16);
                }

 #if USB_NUM_USBIP == 2
                else
                {
  #if defined(USB_HIGH_SPEED_MODULE)
                    g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW32; /* fraction size(1-3) */
                    dma_size = (uint16_t) (dma_size & ~USB_BIT_MBW32);
  #else                                                                                                           /* defined (USB_HIGH_SPEED_MODULE) */
                    g_usb_cstd_dma_fraction_size[ip][channel] = g_usb_cstd_dma_size[ip][channel] & USB_BIT_MBW16; /* fraction size(1-3) */
                    dma_size = (uint16_t) (dma_size & ~USB_BIT_MBW16);
  #endif                                                                                                          /* defined (USB_HIGH_SPEED_MODULE) */
                }
 #endif /* USB_NUM_USBIP == 2 */

                g_usb_cstd_dma_fraction_adr[ip][channel] = (uint32_t) (p_src_adr + dma_size);                     /* fraction data address */

                if (0 != dma_size)
                {
                    g_usb_cstd_dma_size[ip][channel] = dma_size;

                    /* DMA0 1byte trans */
                    usb_cstd_dma_send_restart(ptr, (uint32_t) p_src_adr, dma_size, pipe);
                }
                else
                {
                    cpu_write = true;  /* Set flag for CPU FIFO Write */
                }
            }
        }
    }

    if (true == cpu_write)
    {
        if (USB_MODE_HOST == g_usb_usbmode[ip])
        {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
            g_usb_hstd_data_cnt[ptr->ip][pipe]  = (uint32_t) g_usb_cstd_dma_fraction_size[ip][channel]; /* fraction size(1-3) */
            gp_usb_hstd_data_ptr[ptr->ip][pipe] = (uint8_t *) g_usb_cstd_dma_fraction_adr[ip][channel]; /* fraction data address */
            usb_hstd_buf_to_fifo(ptr, pipe, useport);
 #endif /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
            g_usb_pstd_data_cnt[pipe] = (uint32_t) g_usb_cstd_dma_fraction_size[ip][channel]; /* fraction size(1-3) */
            gp_usb_pstd_data[pipe]    = (uint8_t *) g_usb_cstd_dma_fraction_adr[ip][channel]; /* fraction data address */
            usb_pstd_buf_to_fifo(pipe, useport, ptr);
 #endif /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
        }

        g_usb_cstd_dma_fraction_size[ip][channel] = 0;
    }
}

/******************************************************************************
 * End of function usb_cstd_dma_send_continue
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_get_ir_vect
 * Description     : Get vector no. of USB DxFIFO
 * Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
 *              : uint16_t  useport     : FIFO select
 * Return value    : Vector no.
 ******************************************************************************/
uint16_t usb_cstd_dma_get_ir_vect (usb_utr_t * ptr, uint16_t use_port)
{
    uint16_t ip;
    uint16_t vect = USB_NULL;

    ip = ptr->ip;

    if (USB_IP0 == ip)
    {
        if (USB_D0USE == use_port)
        {
 #if defined(ELC_EVENT_USBFS_FIFO_0)
            vect = ELC_EVENT_USBFS_FIFO_0;
 #endif                                /* define(ELC_EVENT_USBFS_FIFO_0) */
        }
        else
        {
 #if defined(ELC_EVENT_USBFS_FIFO_1)
            vect = ELC_EVENT_USBFS_FIFO_1;
 #endif                                /* ELC_EVENT_USBFS_FIFO_1 */
        }
    }

 #if USB_NUM_USBIP == 2
    else
    {
  #if defined(USB_HIGH_SPEED_MODULE)
        if (USB_D0USE == use_port)
        {
   #if defined(ELC_EVENT_USBHS_FIFO_0)
            vect = ELC_EVENT_USBHS_FIFO_0;
   #endif                              /* defined(ELC_EVENT_USBHS_FIFO_0) */
        }
        else
        {
   #if defined(ELC_EVENT_USBHS_FIFO_1)
            vect = ELC_EVENT_USBHS_FIFO_1;
   #endif                              /* defined(ELC_EVENT_USBHS_FIFO_1) */
        }
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */

  #if (!defined(USB_HIGH_SPEED_MODULE))
        if (USB_D0USE == use_port)
        {
   #if defined(ELC_EVENT_USBFS_FIFO_0)
            vect = ELC_EVENT_USBFS_FIFO_0;
   #endif                              /* defined(ELC_EVENT_USBFS_FIFO_0) */
        }
        else
        {
   #if defined(ELC_EVENT_USBFS_FIFO_1)
            vect = ELC_EVENT_USBFS_FIFO_1;
   #endif                              /* defined(ELC_EVENT_USBFS_FIFO_1) */
        }
  #endif                               /* (!defined(USB_HIGH_SPEED_MODULE)) */
    }
 #endif                                /* USB_NUM_USBIP == 2 */

    return vect;
}

/******************************************************************************
 * End of function usb_cstd_dma_get_ir_vect
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_clear_ir
 * Description     : Clear Interrupt status of USB DxFIFO.
 * Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
 *              : uint16_t  useport     : FIFO select
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_clear_ir (usb_utr_t * ptr, uint16_t use_port)
{
    uint16_t  ip;
    IRQn_Type irq;

    ip = ptr->ip;

    if (USB_IP0 == ip)
    {
        if (USB_D0USE == use_port)
        {
 #if defined(VECTOR_NUMBER_USBFS_FIFO_0)
            irq = (IRQn_Type) VECTOR_NUMBER_USBFS_FIFO_0;
            R_BSP_IrqStatusClear(irq);
 #endif                                /* defined(VECTOR_NUMBER_USBFS_FIFO_0) */
        }
        else
        {
 #if defined(VECTOR_NUMBER_USBFS_FIFO_1)
            irq = (IRQn_Type) VECTOR_NUMBER_USBFS_FIFO_1;
            R_BSP_IrqStatusClear(irq);
 #endif                                /* defined(VECTOR_NUMBER_USBFS_FIFO_1) */
        }
    }

 #if USB_NUM_USBIP == 2
    else
    {
  #if defined(USB_HIGH_SPEED_MODULE)
        if (USB_D0USE == use_port)
        {
   #if defined(VECTOR_NUMBER_USBHS_FIFO_0)
            irq = (IRQn_Type) VECTOR_NUMBER_USBHS_FIFO_0;
            R_BSP_IrqStatusClear(irq);
   #endif                              /* defined(VECTOR_NUMBER_USBHS_FIFO_0) */
        }
        else
        {
   #if defined(VECTOR_NUMBER_USBHS_FIFO_1)
            irq = (IRQn_Type) VECTOR_NUMBER_USBHS_FIFO_1;
            R_BSP_IrqStatusClear(irq);
   #endif                              /* defined(VECTOR_NUMBER_USBHS_FIFO_1) */
        }
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */

  #if (!defined(USB_HIGH_SPEED_MODULE))
        if (USB_D0USE == use_port)
        {
   #if defined(VECTOR_NUMBER_USBFS_FIFO_0)
            irq = (IRQn_Type) VECTOR_NUMBER_USBFS_FIFO_0;
            R_BSP_IrqStatusClear(irq);
   #endif                              /* defined(VECTOR_NUMBER_USBFS_FIFO_0) */
        }
        else
        {
   #if defined(VECTOR_NUMBER_USBFS_FIFO_1)
            irq = (IRQn_Type) VECTOR_NUMBER_USBFS_FIFO_1;
            R_BSP_IrqStatusClear(irq);
   #endif                              /* defined(VECTOR_NUMBER_USBFS_FIFO_1) */
        }
  #endif                               /* (!defined(USB_HIGH_SPEED_MODULE)) */
    }
 #endif                                /* USB_NUM_USBIP == 2 */
}

/******************************************************************************
 * End of function usb_cstd_dma_clear_ir
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_ref_ch_no
 * Description     : Get DMA channel no.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure
 *              : uint16_t  useport : FIFO select
 * Return value    : DMA channel no.
 ******************************************************************************/
uint8_t usb_cstd_dma_ref_ch_no (usb_utr_t * p_utr, uint16_t use_port)
{
    uint8_t               result = 10;
    dmac_extended_cfg_t * channel_info;

    if (p_utr)
    {
        if (USB_D0USE == use_port)
        {
            channel_info = (dmac_extended_cfg_t *) p_utr->p_transfer_rx->p_cfg->p_extend;
        }
        else
        {
            channel_info = (dmac_extended_cfg_t *) p_utr->p_transfer_tx->p_cfg->p_extend;
        }

        result = channel_info->channel;
    }

    return result;                     /* DMA ch no. table */
}

/******************************************************************************
 * End of function usb_cstd_dma_ref_ch_no
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_send_complete
 * Description     : Set event for DMA transfer complete of Buffer to DxFIFO.
 * Arguments       : uint16_t ip_no  : IP no.(USB_IP0/USB_IP1)
 *              : uint16_t useport: FIFO select(USB_D0USE/USB_D1USE)
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_send_complete (uint8_t ip_no, uint16_t use_port)
{
    usb_cfg_t * p_cfg = USB_NULL;
    usb_utr_t   utr;
 #if (BSP_CFG_RTOS != 0)
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t * p_host;
  #endif
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_utr_t * p_peri;
  #endif                               /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

    if (ip_no)
    {
 #if defined(USB_HIGH_SPEED_MODULE)
  #if defined(VECTOR_NUMBER_USBHS_FIFO_1)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_FIFO_1);
  #endif                               /* defined(VECTOR_NUMBER_USBHS_FIFO_1) */
 #else /* defined(USB_HIGH_SPEED_MODULE) */
  #if defined(VECTOR_NUMBER_USBFS_FIFO_1)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_FIFO_1);
  #endif                               /* defined(VECTOR_NUMBER_USBFS_FIFO_1) */
 #endif                                /* defined(USB_HIGH_SPEED_MODULE) */
    }
    else
    {
 #if defined(VECTOR_NUMBER_USBFS_FIFO_1)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_FIFO_1);
 #endif                                /* defined(VECTOR_NUMBER_USBFS_FIFO_1) */
    }

 #if (BSP_CFG_RTOS != 0)
  #if USB_NUM_USBIP == 2
    if (USB_MODE_HOST == g_usb_usbmode[ip_no])
  #else                                /* USB_NUM_USBIP == 2 */
    if (USB_MODE_HOST == g_usb_usbmode[0])
  #endif /* USB_NUM_USBIP == 2 */
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip  = ip_no;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        hw_usb_clear_dreqe(&utr, use_port); /* DMA Transfer request disable */

        p_host                = get_usb_int_buf_dma();
        p_host->ip            = ip_no;
        p_host->msginfo       = USB_MSG_HCD_INT;
        p_host->keyword       = USB_INT_DXFIFO;
        p_host->status        = use_port;
        p_host->p_transfer_tx = p_cfg->p_transfer_tx;
        p_host->p_transfer_rx = p_cfg->p_transfer_rx;

        p_host->ipp = utr.ipp;
        USB_ISND_MSG(USB_HCD_MBX, (usb_msg_t *) p_host);
  #endif                               /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
    else
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        utr.ip = ip_no;

        hw_usb_clear_dreqe(&utr, use_port); /* DMA Transfer request disable */

        p_peri                = get_usb_int_buf_dma();
        p_peri->ip            = ip_no;
        p_peri->msginfo       = USB_MSG_PCD_INT;
        p_peri->keyword       = USB_INT_DXFIFO;
        p_peri->status        = use_port;
        p_peri->p_transfer_tx = p_cfg->p_transfer_tx;
        p_peri->p_transfer_rx = p_cfg->p_transfer_rx;

        USB_ISND_MSG(USB_PCD_MBX, (usb_msg_t *) p_peri);
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }

 #else  /* (BSP_CFG_RTOS != 0) */
    gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.wp].ip        = ip_no;
    gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.wp].fifo_type = use_port;
    gs_usb_cstd_dma_int.wp = (uint8_t) (((uint8_t) (gs_usb_cstd_dma_int.wp + 1)) % USB_INT_BUFSIZE);
    gs_usb_cstd_dma_int.buf[gs_usb_cstd_dma_int.wp].p_cfg = p_cfg;

    utr.ip = ip_no;
  #if USB_NUM_USBIP == 2
    if (USB_MODE_HOST == g_usb_usbmode[utr.ip])
  #else                                /* USB_NUM_USBIP == 2 */
    if (USB_MODE_HOST == g_usb_usbmode[0])
  #endif /* USB_NUM_USBIP == 2 */
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        hw_usb_clear_dreqe(&utr, use_port); /* DMA Transfer request disable */
  #endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }
    else
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        hw_usb_clear_dreqe(&utr, use_port); /* DMA Transfer request disable */
  #endif /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }
 #endif /* (BSP_CFG_RTOS != 0) */
}

/******************************************************************************
 * End of function usb_cstd_dma_send_complete
 ******************************************************************************/

/*******************************************************************************
 * Function Name: usb_ip0_d0fifo_callback
 * Description  : Interrupt service routine of D0FIFO
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void usb_ip0_d0fifo_callback (dmac_callback_args_t * cb_data)
{
    (void) *cb_data;
    usb_cstd_dma_send_complete(USB_IP0, USB_D0USE);
}

/******************************************************************************
 * End of function usb_cstd_d0fifo_cb
 ******************************************************************************/

/*******************************************************************************
 * Function Name: usb_ip0_d1fifo_callback
 * Description  : Interrupt service routine of D1FIFO
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void usb_ip0_d1fifo_callback (dmac_callback_args_t * cb_data)
{
    (void) *cb_data;
    usb_cstd_dma_send_complete(USB_IP0, USB_D1USE);
}

/******************************************************************************
 * End of function usb_ip1_d0fifo_callback
 ******************************************************************************/

/*******************************************************************************
 * Function Name: usb_ip1_d0fifo_callback
 * Description  : Interrupt service routine of D0FIFO
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void usb_ip1_d0fifo_callback (dmac_callback_args_t * cb_data)
{
    (void) *cb_data;
    usb_cstd_dma_send_complete(USB_IP1, USB_D0USE);
}

/******************************************************************************
 * End of function usb_ip1_d0fifo_callback
 ******************************************************************************/

/*******************************************************************************
 * Function Name: usb_ip1_d1fifo_callback
 * Description  : Interrupt service routine of D1FIFO
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void usb_ip1_d1fifo_callback (dmac_callback_args_t * cb_data)
{
    (void) *cb_data;
    usb_cstd_dma_send_complete(USB_IP1, USB_D1USE);
}

/******************************************************************************
 * End of function usb_ip1_d1fifo_callback
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_get_dxfifo_adr
 * Description     : Get FIFO port address of DMA/DTC.
 * Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure
 *              : uint16_t  use_port    : FIFO select
 *              : uint16_t  bit_width   : Access bit size of USB DxFIFO
 * Return          : Address of FIFO port.
 ******************************************************************************/
uint32_t hw_usb_get_dxfifo_adr (usb_utr_t * ptr, uint16_t use_port, uint16_t bit_width)
{
    uint32_t address;
    uint8_t  ip;

    /* Host mode */
    if (USB_IP0 == ptr->ip)
    {
        ip = USB_IP0;
    }
    else
    {
        ip = USB_IP1;
    }

    address = g_fifo_address[ip][use_port][bit_width]; /* Set address of FIFO port */
    return address;
}

/******************************************************************************
 * End of function hw_usb_get_dxfifo_adr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_rcv_setting
 * Description     : FIFO to Buffer data read DMA start
 * Arguments       : usb_utr_t *ptr         : Pointer to usb_utr_t structure
 *              : uint32_t des_addr      : Source address
 *              : uint16_t useport       : FIFO Access mode
 *              : uint32_t transfer_size : Transfer size
 * Return value    : void
 ******************************************************************************/
void usb_cstd_dma_rcv_setting (usb_utr_t * ptr, uint32_t des_addr, uint16_t useport, uint32_t transfer_size)
{
    uint8_t                dma_ch;
    uint16_t               ip;
    uint16_t               active_cnt;
    uint16_t               block_size;
    dmac_extended_cfg_t  * channel_info;
    dmac_instance_ctrl_t * p_dmac_ctrl;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;

        dma_ch = usb_cstd_dma_ref_ch_no(ptr, useport);

        active_cnt = 0;

        /* Wait for Complete of DMA transfer. */
        /* WAIT_LOOP */
        do
        {
            channel_info       = (dmac_extended_cfg_t *) ptr->p_transfer_rx->p_cfg->p_extend;
            p_dmac_ctrl        = (dmac_instance_ctrl_t *) ptr->p_transfer_rx->p_ctrl;
            p_dmac_ctrl->p_reg = USB_DMAC_PRV_REG(channel_info->channel);
            if (1 == p_dmac_ctrl->p_reg->DMSTS_b.ACT)
            {
                active_cnt = 0;
            }
            else
            {
                active_cnt++;
            }
        } while (active_cnt < ACTIVE_CNT_NUMBER);

/* DMA test code start */
        /* Operation - No Extended Repeat Area Function and No Offset Subtraction */

        /* Source address is fixed
         * Transfer data size is 32-bit (long word).
         * DMAC transfer mode is Repeat mode & Source side is repeat area
         * At the beginning of transfer, clear the interrupt flag of the activation source
         * to 0.
         * Transfer Request source is software. *//* Set Transfer data configuration. */
 #if defined(USB_HIGH_SPEED_MODULE)
        if (USB_IP1 == ip)
        {
            ptr->p_transfer_rx->p_cfg->p_info->p_src = (void *) hw_usb_get_dxfifo_adr(ptr,
                                                                                      useport,
                                                                                      USB_FIFO_ACCESS_TYPE_32BIT);
            block_size = (uint16_t) (((g_usb_cstd_dma_fifo[ip][dma_ch] - 1) / 4) + 1);
        }
        else
        {
            ptr->p_transfer_rx->p_cfg->p_info->p_src = (void *) hw_usb_get_dxfifo_adr(ptr,
                                                                                      useport,
                                                                                      USB_FIFO_ACCESS_TYPE_16BIT);
            block_size = (uint16_t) (((g_usb_cstd_dma_fifo[ip][dma_ch] - 1) / 2) + 1);
        }

 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
        ptr->p_transfer_rx->p_cfg->p_info->p_src = (void *) hw_usb_get_dxfifo_adr(ptr,
                                                                                  useport,
                                                                                  USB_FIFO_ACCESS_TYPE_16BIT);
        block_size = (uint16_t) (((g_usb_cstd_dma_fifo[ip][dma_ch] - 1) / 2) + 1);
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

        ptr->p_transfer_rx->p_cfg->p_info->p_dest     = (void *) des_addr;
        ptr->p_transfer_rx->p_cfg->p_info->length     = block_size;
        ptr->p_transfer_rx->p_cfg->p_info->num_blocks =
            (uint16_t) (((transfer_size - 1) / g_usb_cstd_dma_fifo[ip][dma_ch]) + 1);

        /* Call R_DMAC_Reconfigure(). */
        R_DMAC_Reconfigure(ptr->p_transfer_rx->p_ctrl, ptr->p_transfer_rx->p_cfg->p_info);
    }                                  /* if (USB_NULL != ptr) */
}

/******************************************************************************
 * End of function usb_cstd_dma_rcv_setting
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_send_setting
 * Description     : Buffer to FIFO data write DMA start
 * Arguments       : usb_utr_t *ptr            : Pointer to usb_utr_t structure
 *              : uint32_t  src_adr         : Source address
 *              : uint16_t  useport         : FIFO Access mode
 *              : uint32_t  transfer_size   : Transfer size
 * Return value    : none
 ******************************************************************************/
void usb_cstd_dma_send_setting (usb_utr_t * ptr, uint32_t src_adr, uint16_t useport, uint32_t transfer_size)
{
    uint8_t                dma_ch;
    uint16_t               ip;
    uint32_t               block_size;
    uint16_t               active_cnt;
    dmac_extended_cfg_t  * channel_info;
    dmac_instance_ctrl_t * p_dmac_ctrl;

    if (USB_NULL != ptr)
    {
        ip = ptr->ip;

        dma_ch = usb_cstd_dma_ref_ch_no(ptr, useport);

        if (g_usb_cstd_dma_fifo[ip][dma_ch] > transfer_size)
        {
            block_size = transfer_size;
        }
        else
        {
            block_size = g_usb_cstd_dma_fifo[ip][dma_ch];
        }

 #if defined(USB_HIGH_SPEED_MODULE)
        if ((0 == (transfer_size & 0x03)) && (USB_IP1 == ip))
        {
            ptr->p_transfer_tx->p_cfg->p_info->p_dest = (void *) hw_usb_get_dxfifo_adr(ptr,
                                                                                       useport,
                                                                                       USB_FIFO_ACCESS_TYPE_32BIT);
            block_size = (block_size / USB_BIT_32_WIDTH);
        }
        else
        {
            ptr->p_transfer_tx->p_cfg->p_info->p_dest = (void *) hw_usb_get_dxfifo_adr(ptr,
                                                                                       useport,
                                                                                       USB_FIFO_ACCESS_TYPE_16BIT);
            block_size = (block_size / USB_BIT_16_WIDTH);
        }

 #else                                 /* defined (USB_HIGH_SPEED_MODULE) */
        ptr->p_transfer_tx->p_cfg->p_info->p_dest = (void *) hw_usb_get_dxfifo_adr(ptr,
                                                                                   useport,
                                                                                   USB_FIFO_ACCESS_TYPE_16BIT);
        block_size = (block_size / USB_BIT_16_WIDTH);
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

        active_cnt = 0;

        /* Wait for Complete of DMA transfer. */
        /* WAIT_LOOP */
        do
        {
            channel_info       = (dmac_extended_cfg_t *) ptr->p_transfer_tx->p_cfg->p_extend;
            p_dmac_ctrl        = (dmac_instance_ctrl_t *) ptr->p_transfer_tx->p_ctrl;
            p_dmac_ctrl->p_reg = USB_DMAC_PRV_REG(channel_info->channel);
            if (1 == p_dmac_ctrl->p_reg->DMSTS_b.ACT)
            {
                active_cnt = 0;
            }
            else
            {
                active_cnt++;
            }
        } while (active_cnt < ACTIVE_CNT_NUMBER);

/* DMA test code start */
        /* Operation - No Extended Repeat Area Function and No Offset Subtraction */

        /* Source address is fixed
         * Transfer data size is 32-bit (long word).
         * DMAC transfer mode is Repeat mode & Source side is repeat area
         * At the beginning of transfer, clear the interrupt flag of the activation source
         * to 0.
         * Transfer Request source is software. *//* Set Transfer data configuration. */
        ptr->p_transfer_tx->p_cfg->p_info->p_src      = (void *) src_adr;
        ptr->p_transfer_tx->p_cfg->p_info->length     = (uint16_t) block_size;
        ptr->p_transfer_tx->p_cfg->p_info->num_blocks =
            (uint16_t) ((transfer_size - 1) / (g_usb_cstd_dma_fifo[ip][dma_ch]) + 1);

        /* Call R_DMACA_Create(). */
        R_DMAC_Reconfigure(ptr->p_transfer_tx->p_ctrl, ptr->p_transfer_tx->p_cfg->p_info);
    }                                  /* if (USB_NULL != ptr) */
}

/******************************************************************************
 * End of function usb_cstd_dma_send_setting
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_stop
 * Description     : DMA stop
 * Arguments       : uint8_t   ip_type     : USB_IP0/USB_IP1
 *              : uint16_t  use_port    : FIFO select
 * Return value    : void
 ******************************************************************************/
void usb_cstd_dma_stop (usb_utr_t * p_utr, uint16_t use_port)
{
    uint16_t               active_cnt;
    dmac_extended_cfg_t  * channel_info;
    dmac_instance_ctrl_t * p_dmac_ctrl;

    active_cnt = 0;

    /* Wait for Complete of DMA transfer. */
    /* WAIT_LOOP */
    do
    {
        if (USB_D0USE == use_port)
        {
            if (p_utr)
            {
                channel_info       = (dmac_extended_cfg_t *) p_utr->p_transfer_rx->p_cfg->p_extend;
                p_dmac_ctrl        = (dmac_instance_ctrl_t *) p_utr->p_transfer_rx->p_ctrl;
                p_dmac_ctrl->p_reg = USB_DMAC_PRV_REG(channel_info->channel);
                if (1 == p_dmac_ctrl->p_reg->DMSTS_b.ACT)
                {
                    active_cnt = 0;
                }
                else
                {
                    active_cnt++;
                }
            }
        }
        else
        {
            if (p_utr)
            {
                channel_info       = (dmac_extended_cfg_t *) p_utr->p_transfer_tx->p_cfg->p_extend;
                p_dmac_ctrl        = (dmac_instance_ctrl_t *) p_utr->p_transfer_tx->p_ctrl;
                p_dmac_ctrl->p_reg = USB_DMAC_PRV_REG(channel_info->channel);
                if (1 == p_dmac_ctrl->p_reg->DMSTS_b.ACT)
                {
                    active_cnt = 0;
                }
                else
                {
                    active_cnt++;
                }
            }
        }
    } while (active_cnt < ACTIVE_CNT_NUMBER);
}

/******************************************************************************
 * End of function usb_cstd_dma_stop
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_dma_get_crtb
 * Description     : Get DMA Current Transaction Byte reg B(CRTB).
 * Arguments       : uint16_t dma_ch : DMA Channel no.
 * Return value    : DMA Current Transaction Byte reg B(CRTB)
 ******************************************************************************/
uint16_t usb_cstd_dma_get_crtb (usb_utr_t * p_utr)
{
    transfer_properties_t result;

    R_DMAC_InfoGet(p_utr->p_transfer_rx->p_ctrl, &result);

    return (uint16_t) result.block_count_remaining;
}

/******************************************************************************
 * End of function usb_cstd_dma_get_crtb
 ******************************************************************************/

 #if (BSP_CFG_RTOS != 0)

/******************************************************************************
 * Function Name   : get_usb_int_buf_dma
 * Description     : USB interrupt routine. Analyze which USB interrupt occurred
 *               : and send message to DMA.
 * Arguments       : none
 * Return value    : Point to the area for usb_int_t structure
 ******************************************************************************/
usb_utr_t * get_usb_int_buf_dma (void)
{
    static uint16_t count = 0;
    usb_utr_t     * p;

    p = &g_usb_cstd_int_dma[count];

    count = ((uint16_t) (((uint16_t) (count + 1)) % USB_INT_BUFSIZE));

    return p;
}

/******************************************************************************
 * End of function get_usb_int_buf_dma
 ******************************************************************************/
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

#endif                                 /* USB_CFG_DMA == USB_CFG_ENABLE */

/******************************************************************************
 * End of file
 ******************************************************************************/
