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
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
 #include "../hw/inc/r_usb_dmac.h"
#endif                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HMSC_USE)
  #include "../../../r_usb_hmsc/src/inc/r_usb_hmsc_driver.h"
 #endif                                /* defined(USB_CFG_HMSC_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#if defined(USB_CFG_OTG_USE)
 #if defined(USB_CFG_HCDC_USE)
  #include "r_usb_otg_cdc_cfg.h"
 #endif                                /* defined(USB_CFG_HCDC_USE) */
 #if defined(USB_CFG_HHID_USE)
  #include "r_usb_otg_hid_cfg.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */
#else                                  /* defined(USB_CFG_OTG_USE) */
 #if defined(USB_CFG_HCDC_USE)
  #include "r_usb_hcdc_cfg.h"
 #endif                                /* defined(USB_CFG_HCDC_USE) */
 #if defined(USB_CFG_HHID_USE)
  #include "r_usb_hhid_cfg.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */
#endif                                 /* defined(USB_CFG_OTG_USE) */

#if defined(USB_CFG_HPRN_USE)
 #include "r_usb_hprn_cfg.h"
#endif                                 /* defined(USB_CFG_HPRN_USE) */

#if defined(USB_CFG_HUVC_USE)
 #include "r_usb_huvc_cfg.h"
#endif                                 /* defined(USB_CFG_HPRN_USE) */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

 #if (USB_CFG_DMA == USB_CFG_ENABLE)
extern transfer_instance_t * g_p_usbx_transfer_tx;
extern transfer_instance_t * g_p_usbx_transfer_rx;
 #endif                                /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */

/******************************************************************************
 * Renesas Abstracted Host Lib IP functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_dev_addr
 * Description     : Set USB speed (Full/Hi) of the connected USB Device.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t addr    : device address
 *               : uint16_t speed   : device speed
 * Return value    : none
 ******************************************************************************/
void usb_hstd_set_dev_addr (usb_utr_t * ptr, uint16_t addr, uint16_t speed)
{
    if (USB_DEVICE_0 == addr)
    {
        hw_usb_write_dcpmxps(ptr, (uint16_t) (USB_DEFPACKET + USB_DEVICE_0));
    }

    hw_usb_hset_usbspd(ptr, addr, speed);
}

/******************************************************************************
 * End of function usb_hstd_set_dev_addr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_bchg_enable
 * Description     : Enable BCHG interrupt for the specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_bchg_enable (usb_utr_t * ptr)
{
    hw_usb_hclear_sts_bchg(ptr);
    hw_usb_hset_enb_bchge(ptr);
}

/******************************************************************************
 * End of function usb_hstd_bchg_enable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_bchg_disable
 * Description     : Disable BCHG interrupt for specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_bchg_disable (usb_utr_t * ptr)
{
    hw_usb_hclear_sts_bchg(ptr);
    hw_usb_hclear_enb_bchge(ptr);
}

/******************************************************************************
 * End of function usb_hstd_bchg_disable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_uact
 * Description     : Start sending SOF to the connected USB device.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_set_uact (usb_utr_t * ptr)
{
    hw_usb_rmw_dvstctr(ptr, USB_UACT, ((USB_USBRST | USB_RESUME) | USB_UACT));
}

/******************************************************************************
 * End of function usb_hstd_set_uact
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_ovrcr_enable
 * Description     : Enable OVRCR interrupt of the specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_ovrcr_enable (usb_utr_t * ptr)
{
    hw_usb_hclear_sts_ovrcr(ptr);
    hw_usb_hset_enb_ovrcre(ptr);
}

/******************************************************************************
 * End of function usb_hstd_ovrcr_enable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_ovrcr_disable
 * Description     : Disable OVRCR interrupt of the specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_ovrcr_disable (usb_utr_t * ptr)
{
    /* OVRCR Clear(INT_N edge sense) */
    hw_usb_hclear_sts_ovrcr(ptr);

    /* Over-current disable */
    hw_usb_hclear_enb_ovrcre(ptr);
}

/******************************************************************************
 * End of function usb_hstd_ovrcr_disable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_attch_enable
 * Description     : Enable ATTCH (attach) interrupt of the specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_attch_enable (usb_utr_t * ptr)
{
    /* ATTCH status Clear */
    hw_usb_hclear_sts_attch(ptr);

    /* Attach enable */
    hw_usb_hset_enb_attche(ptr);
}

/******************************************************************************
 * End of function usb_hstd_attch_enable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_attch_disable
 * Description     : Disable ATTCH (attach) interrupt of the specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_attch_disable (usb_utr_t * ptr)
{
    /* ATTCH Clear(INT_N edge sense) */
    hw_usb_hclear_sts_attch(ptr);

    /* Attach disable */
    hw_usb_hclear_enb_attche(ptr);
}

/******************************************************************************
 * End of function usb_hstd_attch_disable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_dtch_enable
 * Description     : Enable DTCH (detach) interrupt of the specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_dtch_enable (usb_utr_t * ptr)
{
    /* DTCH Clear */
    hw_usb_hclear_sts_dtch(ptr);

    /* Detach enable */
    hw_usb_hset_enb_dtche(ptr);
}

/******************************************************************************
 * End of function usb_hstd_dtch_enable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_dtch_disable
 * Description     : Disable DTCH (detach) interrupt of the specified USB port.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_dtch_disable (usb_utr_t * ptr)
{
    /* DTCH Clear(INT_N edge sense) */
    hw_usb_hclear_sts_dtch(ptr);

    /* Detach disable */
    hw_usb_hclear_enb_dtche(ptr);
}

/******************************************************************************
 * End of function usb_hstd_dtch_disable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_chk_dev_addr
 * Description     : Get USB speed set in USB register based on the specified USB
 *               : Device address and USB port no.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t addr        : device address
 * Return value    : uint16_t             : USB speed etc
 ******************************************************************************/
uint16_t usb_hstd_chk_dev_addr (usb_utr_t * ptr, uint16_t addr)
{
    uint16_t buffer;

    /* Get device address configuration register from device address */
    buffer = hw_usb_hread_devadd(ptr, addr);
    if (USB_ERROR != buffer)
    {

        /* Return Address check result */
        return (uint16_t) (buffer & USB_USBSPD);
    }

    return USB_NOCONNECT;
}

/******************************************************************************
 * End of function usb_hstd_chk_dev_addr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_get_dev_speed
 * Description     : Get USB speed set in USB register based on the specified USB
 *               : Device address.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t addr        : device address
 * Return value    : uint16_t             : device speed
 * Note            : Use also to a connection check is possible
 ******************************************************************************/
uint16_t usb_hstd_get_dev_speed (usb_utr_t * ptr, uint16_t addr)
{
    uint16_t buffer;

    /* Get device address configuration register from device address */
    buffer = hw_usb_hread_devadd(ptr, addr);
    if (USB_ERROR != buffer)
    {

        /* Return device speed */
        return (uint16_t) (buffer & USB_USBSPD);
    }

    return USB_NOCONNECT;
}

/******************************************************************************
 * End of function usb_hstd_get_dev_speed
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_pipe_to_epadr
 * Description     : Get the associated endpoint value of the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *              : uint16_t pipe  : Pipe number.
 * Return value    : uint8_t        : OK    : Endpoint nr + direction.
 *              :                : ERROR : Error.
 ******************************************************************************/
uint8_t usb_hstd_pipe_to_epadr (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t buffer;
    uint16_t direp;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL;               /* Error */
    }

    /* Pipe select */
    hw_usb_write_pipesel(ptr, pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg(ptr);
    direp  = (uint16_t) ((((buffer & USB_DIRFIELD) ^ USB_DIRFIELD) << 3) + (buffer & USB_EPNUMFIELD));

    return (uint8_t) (direp);
}

/******************************************************************************
 * End of function usb_hstd_pipe_to_epadr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_pipe2fport
 * Description     : Get port No. from the specified pipe No. by argument
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : uint16_t       : FIFO port selector.
 ******************************************************************************/
uint16_t usb_hstd_pipe2fport (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t fifo_mode = USB_CUSE;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t usb_dir;
 #endif                                /* #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL;               /* Error */
    }

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    {
        if ((USB_PIPE1 == pipe) || (USB_PIPE2 == pipe))
        {
            hw_usb_write_pipesel(ptr, pipe);
            usb_dir = hw_usb_read_pipecfg(ptr);
            usb_dir = usb_dir & USB_DIRFIELD;
            if (0 == usb_dir)
            {
  #if (BSP_CFG_RTOS == 1)
                if (0 != g_p_usbx_transfer_rx)
                {
                    fifo_mode = USB_D0USE;
                }

  #else
                if (0 != ptr->p_transfer_rx)
                {
                    fifo_mode = USB_D0USE;
                }
  #endif
            }
            else
            {
  #if (BSP_CFG_RTOS == 1)
                if (0 != g_p_usbx_transfer_tx)
                {
                    fifo_mode = USB_D1USE;
                }

  #else
                if (0 != ptr->p_transfer_tx)
                {
                    fifo_mode = USB_D1USE;
                }
  #endif
            }
        }
    }
 #else                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
    (void) *ptr;
 #endif

    return fifo_mode;
}

/******************************************************************************
 * End of function usb_hstd_pipe2fport
 ******************************************************************************/

 #if defined(USB_HIGH_SPEED_MODULE)

/******************************************************************************
 * Function Name   : usb_hstd_set_hse
 * Description     : Set/clear the HSE-bit of the specified port.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t speed : USB_HS_ENABLE/USB_HS_DISABLE.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_set_hse (usb_utr_t * ptr, uint16_t speed)
{
    if (USB_HS_DISABLE == speed)
    {
        /* HSE = disable */
        hw_usb_clear_hse(ptr);
    }
    else
    {
        /* HSE = enable */
        hw_usb_set_hse(ptr);
    }
}

/******************************************************************************
 * End of function usb_hstd_set_hse
 ******************************************************************************/
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

/******************************************************************************
 * Function Name   : usb_hstd_berne_enable
 * Description     : Enable BRDY/NRDY/BEMP interrupt.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_berne_enable (usb_utr_t * ptr)
{
    /* Enable BEMP, NRDY, BRDY */
    hw_usb_set_intenb(ptr, ((USB_BEMPE | USB_NRDYE) | USB_BRDYE));
}

/******************************************************************************
 * End of function usb_hstd_berne_enable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_sw_reset
 * Description     : Request USB IP software reset
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_sw_reset (usb_utr_t * ptr)
{
    /* USB Enable */
    hw_usb_set_usbe(ptr);

    /* USB Reset */
    hw_usb_clear_usbe(ptr);

    /* USB Enable */
    hw_usb_set_usbe(ptr);
}

/******************************************************************************
 * End of function usb_hstd_sw_reset
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_do_sqtgl
 * Description     : Toggle setting of the toggle-bit for the specified pipe by
 * : argument.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t pipe    : Pipe number.
 *               : uint16_t toggle  : Current toggle status.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_do_sqtgl (usb_utr_t * ptr, uint16_t pipe, uint16_t toggle)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Check toggle */
    if (USB_SQMON == (toggle & USB_SQMON))
    {
        /* Do pipe SQSET */
        hw_usb_set_sqset(ptr, pipe);
    }
    else
    {
        /* Do pipe SQCLR */
        hw_usb_set_sqclr(ptr, pipe);
    }
}

/******************************************************************************
 * End of function usb_hstd_do_sqtgl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_get_devsel
 * Description     : Get device address from pipe number
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : uint16_t DEVSEL-bit status
 ******************************************************************************/
uint16_t usb_hstd_get_devsel (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t devsel;
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL;               /* Error */
    }

    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpmaxp(ptr);
    }
    else
    {
        /* Pipe select */
        hw_usb_write_pipesel(ptr, pipe);
        buffer = hw_usb_read_pipemaxp(ptr);
    }

    /* Device address */
    devsel = (uint16_t) (buffer & USB_DEVSEL);

    return devsel;
}

/******************************************************************************
 * End of function usb_hstd_get_devsel
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_get_device_address
 * Description     : Get the device address associated with the specified pipe.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     pipe    : Pipe number.
 * Return value    : uint16_t     DEVSEL-bit status
 ******************************************************************************/
uint16_t usb_hstd_get_device_address (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t buffer;
    uint16_t result = USB_ERROR;

    if (USB_MAX_PIPE_NO < pipe)
    {
        result = USB_ERROR;            /* Error */
    }

    /* Host */
    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpmaxp(ptr);

        /* Device address */
        result = (uint16_t) (buffer & USB_DEVSEL);
    }
    else
    {
        if (USB_TRUE == g_usb_pipe_table[ptr->ip][pipe].use_flag)
        {
            result = (uint16_t) (g_usb_pipe_table[ptr->ip][pipe].pipe_maxp & USB_DEVSEL);
        }
    }

    return result;
}

/******************************************************************************
 * End of function usb_hstd_get_device_address
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_write_data
 * Description     : Switch PIPE, request the USB FIFO to write data, and manage
 *               : the size of written data.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     pipe        : Pipe no.
 *               : uint16_t     pipemode    : CUSE/D0DMA/D1DMA
 * Return value    : uint16_t end_flag
 ******************************************************************************/
uint16_t usb_hstd_write_data (usb_utr_t * ptr, uint16_t pipe, uint16_t pipemode)
{
    uint16_t size;
    uint16_t count;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t end_flag;
    uint16_t read_pid;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_WRITESHRT;          /* Error */
    }

    /* Changes FIFO port by the pipe. */
    if ((USB_CUSE == pipemode) && (USB_PIPE0 == pipe))
    {
        buffer = usb_cstd_is_set_frdy(ptr, pipe, (uint16_t) USB_CUSE, (uint16_t) USB_ISEL);
    }
    else
    {
        buffer = usb_cstd_is_set_frdy(ptr, pipe, pipemode, USB_FALSE);
    }

    /* Check error */
    if (USB_FIFOERROR == buffer)
    {

        /* FIFO access error */
        return USB_FIFOERROR;
    }

    /* Data buffer size */
    size = usb_cstd_get_buf_size(ptr, pipe);

    /* Max Packet Size */
    mxps = usb_cstd_get_maxpacket_size(ptr, pipe);

    /* Data size check */
    if (g_usb_hstd_data_cnt[ptr->ip][pipe] <= (uint32_t) size)
    {
        count = (uint16_t) g_usb_hstd_data_cnt[ptr->ip][pipe];

        /* Data count check */
        if (0 == count)
        {
            /* Null Packet is end of write */
            end_flag = USB_WRITESHRT;
        }
        else if (0 != (count % mxps))
        {
            /* Short Packet is end of write */
            end_flag = USB_WRITESHRT;
        }
        else
        {
            if (USB_PIPE0 == pipe)
            {
                /* Just Send Size */
                end_flag = USB_WRITING;
            }
            else
            {
                /* Write continues */
                end_flag = USB_WRITEEND;
            }
        }
    }
    else
    {
        /* Write continues */
        end_flag = USB_WRITING;
        count    = size;
    }

    read_pid = usb_cstd_get_pid(ptr, pipe);
    usb_cstd_set_nak(ptr, pipe);

    gp_usb_hstd_data_ptr[ptr->ip][pipe] =
        usb_hstd_write_fifo(ptr, count, pipemode, gp_usb_hstd_data_ptr[ptr->ip][pipe]);

    /* Check data count to remain */
    if (g_usb_hstd_data_cnt[ptr->ip][pipe] < (uint32_t) size)
    {
        /* Clear data count */
        g_usb_hstd_data_cnt[ptr->ip][pipe] = (uint32_t) 0U;
        buffer = hw_usb_read_fifoctr(ptr, pipemode); /* Read CFIFOCTR */

        /* Check BVAL */
        if (0U == (buffer & USB_BVAL))
        {
            /* Short Packet */
            hw_usb_set_bval(ptr, pipemode);
        }
    }
    else
    {
        /* Total data count - count */
        g_usb_hstd_data_cnt[ptr->ip][pipe] -= count;
    }

    hw_usb_clear_status_bemp(ptr, pipe);

    /* USB_PID_BUF ? */
    if (USB_PID_BUF == (USB_PID & read_pid))
    {
        usb_cstd_set_buf(ptr, pipe);
    }

    /* End or Err or Continue */
    return end_flag;
}

/******************************************************************************
 * End of function usb_hstd_write_data
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_receive_start
 * Description     : Start data reception using CPU/DMA transfer to USB Host/USB
 *               : device.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     pipe    : Pipe no.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_receive_start (usb_utr_t * ptr, uint16_t pipe)
{
    usb_utr_t * pp;
    uint32_t    length;
    uint16_t    mxps;
    uint16_t    useport;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint8_t               dma_ch;
    dmac_extended_cfg_t * channel_info;
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Evacuation pointer */
    pp     = g_p_usb_hstd_pipe[ptr->ip][pipe];
    length = pp->tranlen;

    /* Check transfer count */
    if (USB_TRAN_CONT == pp->segment)
    {
        /* Sequence toggle */
        usb_hstd_do_sqtgl(ptr, pipe, pp->pipectr);
    }

    /* Select NAK */
    usb_cstd_set_nak(ptr, pipe);
    g_usb_hstd_data_cnt[ptr->ip][pipe]  = length;                    /* Set data count */
    gp_usb_hstd_data_ptr[ptr->ip][pipe] = (uint8_t *) pp->p_tranadr; /* Set data pointer */

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0U;

    /* Pipe number to FIFO port select */
    useport = usb_hstd_pipe2fport(ptr, pipe);

    /* Check use FIFO access */
    switch (useport)
    {
        /* CFIFO use */
        case USB_CUSE:
        {
            /* Changes the FIFO port by the pipe. */
            usb_cstd_chg_curpipe(ptr, pipe, useport, USB_FALSE);
            mxps = usb_cstd_get_maxpacket_size(ptr, pipe); /* Max Packet Size */
            if ((uint32_t) 0U != length)
            {
                /* Data length check */
                if ((uint32_t) 0U == (length % mxps))
                {
                    /* Set Transaction counter */
                    usb_cstd_set_transaction_counter(ptr, pipe, (uint16_t) (length / mxps));
                }
                else
                {
                    /* Set Transaction counter */
                    usb_cstd_set_transaction_counter(ptr, pipe, (uint16_t) ((length / mxps) + (uint32_t) 1U));
                }
            }

            usb_cstd_set_buf(ptr, pipe); /* Set BUF */

            /* Enable Ready Interrupt */
            hw_usb_set_brdyenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);
            break;
        }

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

        /* D1FIFO DMA */
        case USB_D1USE:

        /* D0FIFO DMA */
        case USB_D0USE:
        {
            if (USB_IP0 == ptr->ip)
            {
                channel_info = (dmac_extended_cfg_t *) pp->p_transfer_rx->p_cfg->p_extend;
                dma_ch       = channel_info->channel;
            }
            else
            {
                channel_info = (dmac_extended_cfg_t *) pp->p_transfer_rx->p_cfg->p_extend;
                dma_ch       = channel_info->channel;
            }

            /* Setting for use PIPE number */
            g_usb_cstd_dma_pipe[ptr->ip][dma_ch] = pipe;

            /* Buffer size */
            g_usb_cstd_dma_fifo[ptr->ip][dma_ch] = usb_cstd_get_buf_size(ptr, pipe);

            /* Transfer data size */
            g_usb_cstd_dma_size[ptr->ip][dma_ch] = g_usb_hstd_data_cnt[ptr->ip][pipe];
            usb_cstd_dma_rcv_start(ptr, pipe, useport);

            break;
        }
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default:
        {
            USB_PRINTF1("### USB-ITRON is not support(RCV-else:pipe%d)\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_receive_start
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_read_data
 * Description     : Request to read data from USB FIFO, and manage the size of
 *               : the data read.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     pipe        : Pipe no.
 *               : uint16_t     pipemode    : Pipe mode (CFIFO/D0FIFO/D1FIFO)
 * Return value    : USB_READING / USB_READEND / USB_READSHRT / USB_READOVER
 ******************************************************************************/
uint16_t usb_hstd_read_data (usb_utr_t * ptr, uint16_t pipe, uint16_t pipemode)
{
    uint16_t count;
    uint16_t buffer;
    uint16_t mxps;
    uint16_t dtln;
    uint16_t end_flag;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR;              /* Error */
    }

    /* Changes FIFO port by the pipe. */
    buffer = usb_cstd_is_set_frdy(ptr, pipe, pipemode, USB_FALSE);
    if (USB_FIFOERROR == buffer)
    {

        /* FIFO access error */
        return USB_FIFOERROR;
    }

    dtln = (uint16_t) (buffer & USB_DTLN);

    /* Max Packet Size */
    mxps = usb_cstd_get_maxpacket_size(ptr, pipe);

    if (g_usb_hstd_data_cnt[ptr->ip][pipe] < dtln)
    {
        /* Buffer Over ? */
        end_flag = USB_READOVER;
        usb_cstd_set_nak(ptr, pipe);   /* Set NAK */
        count = (uint16_t) g_usb_hstd_data_cnt[ptr->ip][pipe];
 #if BSP_CFG_RTOS != 1
        g_usb_hstd_data_cnt[ptr->ip][pipe] = dtln;
 #endif /* BSP_CFG_RTOS != 1 */
    }
    else if (g_usb_hstd_data_cnt[ptr->ip][pipe] == dtln)
    {
        /* Just Receive Size */
        count    = dtln;
        end_flag = USB_READEND;
        usb_cstd_set_nak(ptr, pipe);   /* Set NAK */
    }
    else
    {
        /* Continus Receive data */
        count    = dtln;
        end_flag = USB_READING;
        if ((0 == count) || (0 != (count % mxps)))
        {
            /* Null Packet receive */
            end_flag = USB_READSHRT;
            usb_cstd_set_nak(ptr, pipe); /* Select NAK */
        }
    }

    if (0 == dtln)
    {
        /* 0 length packet */
        /* Clear BVAL */
        hw_usb_set_bclr(ptr, pipemode);
    }
    else
    {
        gp_usb_hstd_data_ptr[ptr->ip][pipe] =
            usb_hstd_read_fifo(ptr, count, pipemode, gp_usb_hstd_data_ptr[ptr->ip][pipe]);
    }

    g_usb_hstd_data_cnt[ptr->ip][pipe] -= count;

    /* End or Err or Continue */
    return end_flag;
}

/******************************************************************************
 * End of function usb_hstd_read_data
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_data_end
 * Description     : Set USB registers as appropriate after data transmission/re-
 *               : ception, and call the callback function as transmission/recep-
 *               : tion is complete.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     pipe    : Pipe no.
 *               : uint16_t     status  : Transfer status type.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_data_end (usb_utr_t * ptr, uint16_t pipe, uint16_t status)
{
    uint16_t useport;
    uint8_t  ip;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    ip = ptr->ip;

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_set_nak(ptr, pipe);

    /* Pipe number to FIFO port select */
    useport = usb_hstd_pipe2fport(ptr, pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(ptr, pipe);

    /* Disable Not Ready Interrupt */
    hw_usb_clear_nrdyenb(ptr, pipe);

    /* Disable Empty Interrupt */
    hw_usb_clear_bempenb(ptr, pipe);

    /* Disable Transaction count */
    usb_cstd_clr_transaction_counter(ptr, pipe);

    /* Check use FIFO */
    switch (useport)
    {
        /* CFIFO use */
        case USB_CUSE:
        {
            break;
        }

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

        /* D0FIFO DMA */
        case USB_D0USE:
        {
            /* DMA buffer clear mode clear */
            hw_usb_clear_dclrm(ptr, USB_D0USE);
            if (USB_IP0 == ip)
            {
                hw_usb_set_mbw(ptr, USB_D0USE, USB0_D0FIFO_MBW);
            }
            else if (USB_IP1 == ip)
            {
                hw_usb_set_mbw(ptr, USB_D0USE, USB1_D0FIFO_MBW);
            }
            else
            {
                /* None */
            }

            break;
        }

        /* D1FIFO DMA */
        case USB_D1USE:
        {
            /* DMA buffer clear mode clear */
            hw_usb_clear_dclrm(ptr, USB_D1USE);
            if (USB_IP0 == ip)
            {
                hw_usb_set_mbw(ptr, USB_D1USE, USB0_D1FIFO_MBW);
            }
            else if (USB_IP1 == ip)
            {
                hw_usb_set_mbw(ptr, USB_D1USE, USB1_D1FIFO_MBW);
            }
            else
            {
                /* None */
            }

            break;
        }
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default:
        {
            break;
        }
    }

    /* Call Back */
    if (USB_NULL != g_p_usb_hstd_pipe[ip][pipe])
    {
        /* Transfer information set */
        g_p_usb_hstd_pipe[ip][pipe]->tranlen = g_usb_hstd_data_cnt[ip][pipe];
        g_p_usb_hstd_pipe[ip][pipe]->status  = status;
        g_p_usb_hstd_pipe[ip][pipe]->pipectr = hw_usb_read_pipectr(ptr, pipe);
        g_p_usb_hstd_pipe[ip][pipe]->errcnt  = (uint8_t) g_usb_hstd_ignore_cnt[ip][pipe];
        g_p_usb_hstd_pipe[ip][pipe]->ipp     = usb_hstd_get_usb_ip_adr(ip);
        g_p_usb_hstd_pipe[ip][pipe]->ip      = ip;
        (g_p_usb_hstd_pipe[ip][pipe]->complete)(g_p_usb_hstd_pipe[ip][pipe], USB_NULL, USB_NULL);

 #if (BSP_CFG_RTOS == 0)
        g_p_usb_hstd_pipe[ip][pipe] = (usb_utr_t *) USB_NULL;
 #else                                          /* (BSP_CFG_RTOS == 0) */
  #if (BSP_CFG_RTOS == 1)
        USB_REL_BLK(1, g_p_usb_hstd_pipe[ip][pipe]);
  #elif (BSP_CFG_RTOS == 2)                     /* #if (BSP_CFG_RTOS == 1) */
        vPortFree(g_p_usb_hstd_pipe[ip][pipe]);
  #endif                                        /* #if (BSP_CFG_RTOS == 1) */
        g_p_usb_hstd_pipe[ip][pipe] = (usb_utr_t *) USB_NULL;
        usb_cstd_pipe_msg_re_forward(ip, pipe); /* Get PIPE Transfer wait que and Message send to HCD */
 #endif                                         /* (BSP_CFG_RTOS == 0) */
    }
}

/******************************************************************************
 * End of function usb_hstd_data_end
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_brdy_pipe_process
 * Description     : Search for the PIPE No. that BRDY interrupt occurred, and
 *               : request data transmission/reception from the PIPE
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     bitsts  : BRDYSTS Register & BRDYENB Register
 * Return value    : none
 ******************************************************************************/
void usb_hstd_brdy_pipe_process (usb_utr_t * ptr, uint16_t bitsts)
{
    uint16_t useport;
    uint16_t i;
    uint16_t ip;

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t buffer;
    uint16_t maxps;
    uint16_t set_dma_block_cnt;
    uint16_t trans_dma_block_cnt;
    uint16_t dma_ch;
    uint16_t status;
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    ip = ptr->ip;

    /* WAIT_LOOP */
    for (i = USB_MIN_PIPE_NO; i <= USB_MAX_PIPE_NO; i++)
    {
        if (0 != (bitsts & USB_BITSET(i)))
        {
            /* Interrupt check */
            hw_usb_clear_status_bemp(ptr, i);

            if (USB_NULL != g_p_usb_hstd_pipe[ip][i])
            {
                /* Pipe number to FIFO port select */
                useport = usb_hstd_pipe2fport(ptr, i);
                if ((USB_D0USE == useport) || (USB_D1USE == useport))
                {
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
                    dma_ch = usb_cstd_dma_ref_ch_no(ptr, useport);

                    maxps = g_usb_cstd_dma_fifo[ip][dma_ch];

                    /* DMA Transfer request disable */
                    hw_usb_clear_dreqe(ptr, useport);

                    /* DMA stop */
                    usb_cstd_dma_stop(ptr, useport);

                    /* Changes FIFO port by the pipe. */
                    buffer = usb_cstd_is_set_frdy(ptr, i, useport, USB_FALSE);

                    set_dma_block_cnt = (uint16_t) (((g_usb_hstd_data_cnt[ip][g_usb_cstd_dma_pipe[ip][dma_ch]] - 1) /
                                                     g_usb_cstd_dma_fifo[ip][dma_ch]) + 1);

                    trans_dma_block_cnt = usb_cstd_dma_get_crtb(ptr);

                    /* Get D0fifo Receive Data Length */
                    g_usb_cstd_dma_size[ip][dma_ch] = buffer & USB_DTLN;
                    if (set_dma_block_cnt > trans_dma_block_cnt)
                    {
                        if (0 != g_usb_cstd_dma_size[ip][dma_ch])
                        {
                            g_usb_cstd_dma_size[ip][dma_ch] =
                                (uint16_t) ((uint16_t) (g_usb_cstd_dma_size[ip][dma_ch]) +
                                            (uint16_t) ((set_dma_block_cnt - (trans_dma_block_cnt + 1)) * maxps));
                        }
                        else
                        {
                            g_usb_cstd_dma_size[ip][dma_ch] =
                                (uint16_t) ((set_dma_block_cnt - (trans_dma_block_cnt)) * maxps);
                        }
                    }

                    /* Check data count */
                    if (g_usb_cstd_dma_size[ip][dma_ch] == g_usb_hstd_data_cnt[ptr->ip][i])
                    {
                        status = USB_DATA_OK;
                    }
                    else if (g_usb_cstd_dma_size[ip][dma_ch] > g_usb_hstd_data_cnt[ip][i])
                    {
                        status = USB_DATA_OVR;
                    }
                    else
                    {
                        status = USB_DATA_SHT;
                    }

                    /* D0FIFO access DMA stop */
                    usb_cstd_dfifo_end(ptr, useport);

                    /* End of data transfer */
                    usb_hstd_data_end(ptr, i, status);

                    /* Set BCLR */
                    hw_usb_set_bclr(ptr, useport);
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
                }
                else
                {
                    if (USB_BUF2FIFO == usb_cstd_get_pipe_dir(ptr, i))
                    {
                        /* Buffer to FIFO data write */
                        usb_hstd_buf_to_fifo(ptr, i, useport);
                    }
                    else
                    {
                        /* FIFO to Buffer data read */
                        usb_hstd_fifo_to_buf(ptr, i, useport);
                    }
                }
            }
        }
    }
}                                      /* End of function usb_hstd_brdy_pipe_process() */

/******************************************************************************
 * Function Name   : usb_hstd_nrdy_pipe_process
 * Description     : Search for PIPE No. that occurred NRDY interrupt, and execute
 *               : the process for PIPE when NRDY interrupt occurred
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     bitsts  : NRDYSTS Register & NRDYENB Register
 * Return value    : none
 ******************************************************************************/
void usb_hstd_nrdy_pipe_process (usb_utr_t * ptr, uint16_t bitsts)
{
    uint16_t buffer;
    uint16_t i;

    /* WAIT_LOOP */
    for (i = USB_MIN_PIPE_NO; i <= USB_MAX_PIPE_NO; i++)
    {
        if (0 != (bitsts & USB_BITSET(i)))
        {
            /* Interrupt check */
            if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][i])
            {
                if (USB_TYPFIELD_ISO == usb_cstd_get_pipe_type(ptr, i))
                {
                    /* Wait for About 60ns */
                    buffer = hw_usb_read_frmnum(ptr);
                    if (USB_OVRN == (buffer & USB_OVRN))
                    {
                        /* @1 */
                        /* End of data transfer */
                        usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_OVR);
                        USB_PRINTF1("###ISO OVRN %lu\n", (unsigned long) g_usb_hstd_data_cnt[ptr->ip][i]);
                    }
                    else
                    {
                        /* @2 */
                        /* End of data transfer */
                        usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_ERR);
                    }
                }
                else
                {
                    usb_hstd_nrdy_endprocess(ptr, i);
                }
            }
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_nrdy_pipe_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_bemp_pipe_process
 * Description     : Search for PIPE No. that BEMP interrupt occurred, and complete data transmission for the PIPE
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     bitsts  : BEMPSTS Register & BEMPENB Register
 * Return value    : none
 ******************************************************************************/
void usb_hstd_bemp_pipe_process (usb_utr_t * ptr, uint16_t bitsts)
{
    uint16_t buffer;
    uint16_t i;
    uint16_t useport;

    /* WAIT_LOOP */
    for (i = USB_MIN_PIPE_NO; i <= USB_PIPE5; i++)
    {
        if (0 != (bitsts & USB_BITSET(i)))
        {
            /* Interrupt check */
            if ((USB_NULL != g_p_usb_hstd_pipe[ptr->ip][i]) && (USB_ON != g_usb_cstd_bemp_skip[ptr->ip][i]))
            {
                buffer = usb_cstd_get_pid(ptr, i);

                /* MAX packet size error ? */
                if (USB_PID_STALL == (buffer & USB_PID_STALL))
                {
                    USB_PRINTF1("### STALL Pipe %d\n", i);
                    usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_STALL);
                }
                else
                {
                    if (USB_INBUFM != (hw_usb_read_pipectr(ptr, i) & USB_INBUFM))
                    {
                        /* Pipe number to FIFO port select */
                        useport = usb_hstd_pipe2fport(ptr, i);

                        if (USB_CUSE != useport)
                        {
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
                            hw_usb_clear_status_bemp(ptr, i);
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
                        }

                        g_usb_cstd_bemp_skip[ptr->ip][i] = USB_ON;

                        /* End of data transfer */
                        usb_hstd_data_end(ptr, i, (uint16_t) USB_DATA_NONE);
                    }
                }
            }
        }
    }

    /* WAIT_LOOP */
    for (i = USB_PIPE6; i <= USB_MAX_PIPE_NO; i++)
    {
        /* Interrupt check */
        if (0 != (bitsts & USB_BITSET(i)))
        {
            if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][i])
            {
                buffer = usb_cstd_get_pid(ptr, i);

                /* MAX packet size error ? */
                if (USB_PID_STALL == (buffer & USB_PID_STALL))
                {
                    /*USB_PRINTF1("### STALL Pipe %d\n", i);*/
                    usb_hstd_forced_termination(ptr, i, (uint16_t) USB_DATA_STALL);
                }
                else
                {
                    /* End of data transfer */
                    usb_hstd_data_end(ptr, i, (uint16_t) USB_DATA_NONE);
                }
            }
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_bemp_pipe_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_make_pipe_reg_info
 * Description     : Make value for USB PIPE registers set value.
 * Arguments       : uint16_t ip_no        : USB Module no.(USB_IP0/USB_IP1)
 *              : uint16_t address      : USB Device address
 *              : usb_class_t usb_class : USB Device class(USB_HVND/USB_HCDC/USB_HHID/USB_HMSC/USB_HUB)
 *              : uint16_t speed        : USB speed
 *              : uint8_t *descriptor   : Address for End Point Descriptor
 *              : usb_pipe_table_reg_t *pipe_table_work : Address for Store PIPE reg set value.
 * Return value    : Pipe no (USB_PIPE1->USB_PIPE9:OK, USB_NULL:Error)
 ******************************************************************************/
uint8_t usb_hstd_make_pipe_reg_info (uint16_t               ip_no,
                                     uint16_t               address,
                                     uint16_t               usb_class,
                                     uint16_t               speed,
                                     uint8_t              * descriptor,
                                     usb_pipe_table_reg_t * pipe_table_work)
{
    uint8_t  pipe_no;
    uint16_t pipe_cfg;
    uint16_t pipe_maxp;
    uint16_t pipe_peri = USB_NULL;
 #if defined(USB_HIGH_SPEED_MODULE)
    uint16_t pipe_buf;
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

    /* Check Endpoint descriptor */
    if (USB_DT_ENDPOINT != descriptor[USB_DEV_B_DESCRIPTOR_TYPE])
    {
        return USB_NULL;               /* Error */
    }

    /* set pipe configuration value */
    switch ((uint16_t) (descriptor[USB_EP_B_ATTRIBUTES] & USB_EP_TRNSMASK))
    {
        /* Bulk Endpoint */
        case USB_EP_BULK:
        {
            /* Set pipe configuration table */
            if (USB_EP_IN == (descriptor[USB_EP_B_ENDPOINTADDRESS] & USB_EP_DIRMASK))
            {
                /* IN(receive) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_BULK | USB_CFG_DBLB | USB_SHTNAKFIELD | USB_DIR_H_IN);
                pipe_no  = usb_hstd_get_pipe_no(ip_no, address, usb_class, USB_EP_BULK, USB_PIPE_DIR_IN);
            }
            else
            {
                /* OUT(send) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_BULK | USB_CFG_DBLB | USB_DIR_H_OUT);
                pipe_no  = usb_hstd_get_pipe_no(ip_no, address, usb_class, USB_EP_BULK, USB_PIPE_DIR_OUT);
            }

 #if defined(USB_HIGH_SPEED_MODULE)
            if (USB_IP1 == ip_no)
            {
                pipe_cfg |= (uint16_t) (USB_CFG_CNTMD);
            }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
            break;
        }

        /* Interrupt Endpoint */
        case USB_EP_INT:
        {
            /* Set pipe configuration table */
            if (USB_EP_IN == (descriptor[USB_EP_B_ENDPOINTADDRESS] & USB_EP_DIRMASK))
            {
                /* IN(receive) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_INT | USB_DIR_H_IN);
                pipe_no  = usb_hstd_get_pipe_no(ip_no, address, usb_class, USB_EP_INT, USB_PIPE_DIR_IN);
            }
            else
            {
                /* OUT(send) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_INT | USB_DIR_H_OUT);
                pipe_no  = usb_hstd_get_pipe_no(ip_no, address, usb_class, USB_EP_INT, USB_PIPE_DIR_OUT);
            }

            /* Get value for Interval Error Detection Interval  */
            pipe_peri = usb_hstd_get_pipe_peri_value(speed, descriptor[USB_EP_B_INTERVAL]);

            break;
        }

        case USB_EP_ISO:
        {
            /* Set pipe configuration table */
            if (USB_EP_IN == (descriptor[USB_EP_B_ENDPOINTADDRESS] & USB_EP_DIRMASK))
            {
                /* IN(receive) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_ISO | USB_CFG_DBLB | USB_SHTNAKFIELD | USB_DIR_H_IN);
                pipe_no  = usb_hstd_get_pipe_no(ip_no, address, usb_class, USB_EP_ISO, USB_PIPE_DIR_IN);
            }
            else
            {
                /* OUT(send) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_ISO | USB_CFG_DBLB | USB_DIR_H_OUT);
                pipe_no  = usb_hstd_get_pipe_no(ip_no, address, usb_class, USB_EP_ISO, USB_PIPE_DIR_OUT);
            }

 #if defined(USB_HIGH_SPEED_MODULE)
            if (USB_IP1 == ip_no)
            {
                pipe_cfg |= (uint16_t) (USB_CFG_CNTMD);
            }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
            break;
        }

        default:
        {
            return USB_NULL;           /* Error */
            break;
        }
    }

    /* Check Pipe no. */
    if (USB_NULL != pipe_no)
    {
        /* Endpoint number set */
        pipe_cfg = (uint16_t) (pipe_cfg | (descriptor[USB_EP_B_ENDPOINTADDRESS] & USB_EP_NUMMASK));

        /* set max packet size */
        pipe_maxp = (uint16_t) ((uint16_t) descriptor[USB_EP_B_MAXPACKETSIZE_L] | (address << USB_DEVADDRBIT));
        pipe_maxp = (uint16_t) (pipe_maxp | ((uint16_t) descriptor[USB_EP_B_MAXPACKETSIZE_H] << 8));

        /* Store PIPE reg set value. */
        pipe_table_work->pipe_cfg  = pipe_cfg;
        pipe_table_work->pipe_maxp = pipe_maxp;
        pipe_table_work->pipe_peri = pipe_peri;
 #if defined(USB_HIGH_SPEED_MODULE)
        if (USB_IP1 == ip_no)
        {
            /* PIPEBUF is USBA module only */
            pipe_buf = usb_hstd_get_pipe_buf_value(pipe_no);
            pipe_table_work->pipe_buf = pipe_buf;
        }
 #endif                                /* #if defined (USB_HIGH_SPEED_MODULE) */
    }

    return pipe_no;
} /* eof usb_hstd_make_pipe_reg_info() */

/******************************************************************************
 * Function Name   : usb_hstd_clr_pipe_table
 * Description     : Clear pipe table.
 * Arguments       : uint16_t ip_no          : USB Module no.(USB_IP0/USB_IP1)
 *              : uint16_t device_address : USB Device address
 * Return value    : none
 ******************************************************************************/
void usb_hstd_clr_pipe_table (uint16_t ip_no, uint16_t device_address)
{
    uint8_t pipe_no;

    /* Search use pipe block */
    /* WAIT_LOOP */
    for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
    {
        /* Check use block */
        if (USB_TRUE == g_usb_pipe_table[ip_no][pipe_no].use_flag)
        {
            /* Check USB Device address */
            if ((device_address << USB_DEVADDRBIT) ==
                (uint16_t) (g_usb_pipe_table[ip_no][pipe_no].pipe_maxp & USB_DEVSEL))
            {
                /* Clear use block */
                g_usb_pipe_table[ip_no][pipe_no].use_flag  = USB_FALSE;
                g_usb_pipe_table[ip_no][pipe_no].pipe_cfg  = USB_NULL;
                g_usb_pipe_table[ip_no][pipe_no].pipe_maxp = USB_NULL;
                g_usb_pipe_table[ip_no][pipe_no].pipe_peri = USB_NULL;
 #if defined(USB_HIGH_SPEED_MODULE)
                if (USB_IP1 == ip_no)
                {
                    /* PIPEBUF is USBA module only */
                    g_usb_pipe_table[ip_no][pipe_no].pipe_buf = USB_NULL;
                }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
 #if BSP_CFG_RTOS == 1
                tx_semaphore_put(&g_usb_host_usbx_sem[ip_no][pipe_no]);
                tx_semaphore_delete(&g_usb_host_usbx_sem[ip_no][pipe_no]);
 #endif
            }
        }
    }
}                                      /* eof usb_hstd_clr_pipe_table() */

/******************************************************************************
 * Function Name   : usb_hstd_set_pipe_reg
 * Description     : Set up USB registers to use specified pipe (Pipe unit).
 * Arguments       : usb_utr_t *ptr          : Pointer to usb_utr_t structure.
 *              : uint16_t pipe_no        : USB Pipe No.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_set_pipe_reg (usb_utr_t * ptr, uint16_t pipe_no)
{
    uint16_t buf;

    /* Check use block */
    if (USB_TRUE == g_usb_pipe_table[ptr->ip][pipe_no].use_flag)
    {
        /* Current FIFO port Clear */
        buf = hw_usb_read_fifosel(ptr, USB_CUSE);
        if ((buf & USB_CURPIPE) == pipe_no)
        {
            usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_CUSE, USB_FALSE);
        }

        buf = hw_usb_read_fifosel(ptr, USB_D0USE);
        if ((buf & USB_CURPIPE) == pipe_no)
        {
            usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D0USE, USB_FALSE);
        }

        buf = hw_usb_read_fifosel(ptr, USB_D1USE);
        if ((buf & USB_CURPIPE) == pipe_no)
        {
            usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_D1USE, USB_FALSE);
        }

        /* PIPE Setting */
        usb_cstd_pipe_init(ptr, pipe_no);
    }
}                                      /* eof usb_hstd_set_pipe_reg() */

/******************************************************************************
 * Function Name   : usb_hstd_get_pipe_no
 * Description     : Get PIPE No.
 * Arguments       : uint16_t ip_no     : USB Module no.(USB_IP0/USB_IP1)
 *              : uint16_t address   : USB Device address
 *              : uint16_t class     : USB Device class(USB_HVND/USB_HCDC/USB_HHID/USB_HMSC/USB_HUB)
 *              : uint8_t  type      : Transfer Type.(USB_EP_BULK/USB_EP_INT)
 *              : uint8_t  dir       : (USB_PIPE_DIR_IN/USB_PIPE_DIR_OUT)
 * Return value    : Pipe no (USB_PIPE1->USB_PIPE9:OK, USB_NULL:Error)
 ******************************************************************************/
uint8_t usb_hstd_get_pipe_no (uint16_t ip_no, uint16_t address, uint16_t usb_class, uint8_t type, uint8_t dir)
{
    uint8_t pipe_no = USB_NULL;
 #if defined(USB_CFG_HVND_USE)
    uint16_t pipe;
 #endif                                /* defined(USB_CFG_HVND_USE) */
 #if (BSP_CFG_RTOS != 1)
  #if defined(USB_CFG_HMSC_USE)
    uint16_t side;
  #endif                               /* defined(USB_CFG_HMSC_USE) */
 #endif /* #if (BSP_CFG_RTOS != 1) */

    switch (usb_class)
    {
        case USB_CLASS_INTERNAL_HVND:
        {
 #if defined(USB_CFG_HVND_USE)
            if (USB_EP_BULK == type)
            {
                /* BULK PIPE Loop */
                /* WAIT_LOOP */
                for (pipe = USB_BULK_PIPE_START; pipe < (USB_BULK_PIPE_END + 1); pipe++)
                {
                    if (USB_FALSE == g_usb_pipe_table[ip_no][pipe].use_flag)
                    {
                        /* Check Free pipe */
                        pipe_no = (uint8_t) pipe; /* Set Free pipe */
                        break;
                    }
                }
            }

            if (USB_EP_INT == type)
            {
                /* Interrupt PIPE Loop */
                /* WAIT_LOOP */
                for (pipe = USB_INT_PIPE_START; pipe < (USB_INT_PIPE_END + 1); pipe++)
                {
                    if (USB_FALSE == g_usb_pipe_table[ip_no][pipe].use_flag)
                    {
                        /* Check Free pipe */
                        pipe_no = (uint8_t) pipe; /* Set Free pipe */
                        break;
                    }
                }
            }
 #endif                                /* defined(USB_CFG_HVND_USE) */
            break;
        }

        case USB_CLASS_INTERNAL_HCDC:
        {
 #if defined(USB_CFG_HCDC_USE)
            if (USB_EP_BULK == type)
            {
                if (USB_PIPE_DIR_IN == dir)
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HCDC_BULK_IN;
                            break;
                        }

                        case 3:        /* Hub downport device2 */
                        {
                            pipe_no = USB_CFG_HCDC_BULK_IN2;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
                else
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HCDC_BULK_OUT;
                            break;
                        }

                        case 3:        /* Hub downport device2 */
                        {
                            pipe_no = USB_CFG_HCDC_BULK_OUT2;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
            }

            if (USB_EP_INT == type)
            {
                if (USB_PIPE_DIR_IN == dir)
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HCDC_INT_IN;
                            break;
                        }

                        case 3:        /* Hub downport device2 */
                        {
                            pipe_no = USB_CFG_HCDC_INT_IN2;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
            }
 #endif                                /* defined(USB_CFG_HCDC_USE) */
            break;
        }

        case USB_CLASS_INTERNAL_HHID:
        {
 #if defined(USB_CFG_HHID_USE)
            if (USB_EP_INT == type)
            {
                if (USB_PIPE_DIR_IN == dir)
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HHID_INT_IN;
                            break;
                        }

                        case 3:        /* Hub downport device2 */
                        {
                            pipe_no = USB_CFG_HHID_INT_IN2;
                            break;
                        }

                        case 4:        /* Hub downport device3 */
                        {
                            pipe_no = USB_CFG_HHID_INT_IN3;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
                else
                {
                    /* Check root port device1 or Hub downport device1 */
                    if ((1 == address) || (2 == address))
                    {
                        pipe_no = USB_CFG_HHID_INT_OUT;
                    }
                }
            }
 #endif                                /* defined(USB_CFG_HHID_USE) */
            break;
        }

        case USB_CLASS_INTERNAL_HMSC:
        {
 #if defined(USB_CFG_HMSC_USE)
            if (USB_EP_BULK == type)
            {
  #if (BSP_CFG_RTOS != 1)

                /* Add USB IP no. for USB Device address */
                if (USB_IP1 == ip_no)
                {
                    address |= USBA_ADDRESS_OFFSET;
                }

                /* Get Strage drive no. */
                side = usb_hmsc_ref_drvno(address);

                /* Check Strage drive no. */
                if (side < USB_MAXSTRAGE)
                {
   #if (USB_PIPE2 >= USB_CFG_HCDC_BULK_IN) && (USB_PIPE2 >= USB_CFG_HCDC_BULK_OUT)

                    /* Calculate the pipe number corresponding to the drive number */
                    if ((USB_PIPE3 + side) <= USB_PIPE5)
                    {
                        pipe_no = (uint8_t) (USB_PIPE3 + side);
                    }

   #else                               /* (USB_PIPE2 >= USB_CFG_HCDC_BULK_IN) && (USB_PIPE2 >= USB_CFG_HCDC_BULK_OUT) */
                    /* Calculate the pipe number corresponding to the drive number */
                    pipe_no = (uint8_t) (USB_PIPE1 + side);
   #endif                              /* (USB_PIPE2 >= USB_CFG_HCDC_BULK_IN) && (USB_PIPE2 >= USB_CFG_HCDC_BULK_OUT) */
                }

  #else                                /* #if (BSP_CFG_RTOS != 1) */
                pipe_no = USB_PIPE1;
  #endif /* #if (BSP_CFG_RTOS != 1) */
            }
 #endif                                /* defined(USB_CFG_HMSC_USE) */
            break;
        }

        case USB_CLASS_INTERNAL_HPRN:
        {
 #if defined(USB_CFG_HPRN_USE)
            if (USB_EP_BULK == type)
            {
                if (USB_PIPE_DIR_IN == dir)
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HPRN_BULK_IN;
                            break;
                        }

                        case 3:        /* Hub downport device2 */
                        {
                            pipe_no = USB_CFG_HPRN_BULK_IN2;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
                else
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HPRN_BULK_OUT;
                            break;
                        }

                        case 3:        /* Hub downport device2 */
                        {
                            pipe_no = USB_CFG_HPRN_BULK_OUT2;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
            }
 #endif                                /* defined(USB_CFG_HPRN_USE) */
            break;
        }

        case USB_CLASS_INTERNAL_HUVC:
        {
 #if defined(USB_CFG_HUVC_USE)
            if (USB_EP_ISO == type)
            {
                if (USB_PIPE_DIR_IN == dir)
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HUVC_ISO_IN;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
                else
                {
                    switch (address)
                    {
                        case 1:        /* Root port device1 */
                        case 2:        /* Hub downport device1 */
                        {
                            pipe_no = USB_CFG_HUVC_ISO_OUT;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
            }
 #endif                                /* defined(USB_CFG_HUVC_USE) */
            break;
        }

        case USB_HUB:
        {
            pipe_no = USB_HUB_PIPE;
            break;
        }

        default:
        {
            (void) ip_no;
            (void) address;
            (void) type;
            (void) dir;

            return USB_NULL;
            break;
        }
    }

    return pipe_no;
}                                      /* eof usb_hstd_get_pipe_no() */

/******************************************************************************
 * Function Name   : usb_hstd_get_pipe_peri_value
 * Description     : Get value to be set in PIPEPERI
 * Arguments       : uint16_t  speed     : USB speed
 *              : uint8_t   binterval : bInterval for ENDPOINT Descriptor.
 * Return value    : Value for set PIPEPERI
 ******************************************************************************/
uint16_t usb_hstd_get_pipe_peri_value (uint16_t speed, uint8_t binterval)
{
    uint16_t pipe_peri = USB_NULL;
    uint16_t work1;
    uint16_t work2;

    /* set interval counter */
    if (0 != binterval)
    {
        /* FS/LS interrupt */
        if (USB_HSCONNECT != speed)
        {
            /* The time of the FS/LS interrupt forwarding of the interval is specified by the unit of ms. */
            /* It is necessary to calculate to specify USB-IP by the n-th power of two. */
            /* The NAK rate of the control and the bulk transfer doesn't correspond. */
            work1 = binterval;
            work2 = 0;
            for ( ; work1 != 0; work2++)
            {
                work1 = (uint16_t) (work1 >> 1);
            }

            if (0 != work2)
            {
                /* Interval time */
                pipe_peri |= (uint16_t) (work2 - 1);
            }
        }
        else
        {
            /* Hi-Speed */
            if (8 >= binterval)
            {
                /* Interval time */
                pipe_peri = (uint16_t) (binterval - 1U);
            }
            else
            {
                /* Max Interval time */
                pipe_peri = (uint16_t) (USB_IITVFIELD);
            }
        }
    }

    return pipe_peri;
}                                      /* eof usb_hstd_get_pipe_peri_value() */

 #if defined(USB_HIGH_SPEED_MODULE)

/******************************************************************************
 * Function Name   : usb_hstd_get_pipe_buf_value
 * Description     : Get Value for USBA Module PIPE BUF REG.
 * Arguments       : Pipe no.
 * Return value    : PIPE BUF set value.
 ******************************************************************************/
uint16_t usb_hstd_get_pipe_buf_value (uint16_t pipe_no)
{
    uint16_t pipe_buf = 0;

    switch (pipe_no)
    {
  #if defined(USB_CFG_HCDC_USE)
        case USB_CFG_HCDC_BULK_IN:
        {
   #if (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HCDC_MULTI == USB_CFG_ENABLE)
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(8U));
   #else                               /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HCDC_MULTI == USB_CFG_ENABLE) */
            pipe_buf = (USB_BUF_SIZE(2048U) | USB_BUF_NUMB(8U));
   #endif                              /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HCDC_MULTI == USB_CFG_ENABLE) */
            break;
        }

        case USB_CFG_HCDC_BULK_OUT:
        {
   #if (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HCDC_MULTI == USB_CFG_ENABLE)
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(40U));
   #else                               /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HCDC_MULTI == USB_CFG_ENABLE) */
            pipe_buf = (USB_BUF_SIZE(2048U) | USB_BUF_NUMB(72U));
   #endif                              /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HCDC_MULTI == USB_CFG_ENABLE) */
            break;
        }

   #if (USB_NULL != USB_CFG_HCDC_BULK_IN2)
        case USB_CFG_HCDC_BULK_IN2:
        {
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(72U));
            break;
        }
   #endif                              /* (USB_NULL != USB_CFG_HCDC_BULK_IN2) */

   #if (USB_NULL != USB_CFG_HCDC_BULK_OUT2)
        case USB_CFG_HCDC_BULK_OUT2:
        {
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(104U));
            break;
        }
   #endif                              /* (USB_NULL != USB_CFG_HCDC_BULK_OUT2) */
  #endif                               /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_HMSC_USE)
   #if defined(USB_CFG_HCDC_USE)
    #if (USB_PIPE2 < USB_CFG_HCDC_BULK_IN) && (USB_PIPE2 < USB_CFG_HCDC_BULK_OUT)
        case USB_PIPE1:
        case USB_PIPE2:
    #else                              /* (USB_PIPE2 < USB_CFG_HCDC_BULK_IN) && (USB_PIPE2 < USB_CFG_HCDC_BULK_OUT) */
        case USB_PIPE3:
        case USB_PIPE4:
        case USB_PIPE5:
    #endif                             /* (USB_PIPE2 < USB_CFG_HCDC_BULK_IN) && (USB_PIPE2 < USB_CFG_HCDC_BULK_OUT) */
            {
    #if USB_CFG_DTC == USB_CFG_ENABLE
                pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(8U));
    #else                              /* USB_CFG_DTC == USB_CFG_ENABLE */
                pipe_buf = (USB_BUF_SIZE(2048U) | USB_BUF_NUMB(8U));
    #endif                             /* USB_CFG_DTC == USB_CFG_ENABLE */
                break;
            }

   #else /* defined(USB_CFG_HCDC_USE) */
        case USB_PIPE1:
        case USB_PIPE2:
        case USB_PIPE3:
        case USB_PIPE4:
        case USB_PIPE5:
        {
    #if USB_CFG_DTC == USB_CFG_ENABLE
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(8U));
    #else                              /* USB_CFG_DTC == USB_CFG_ENABLE */
            pipe_buf = (USB_BUF_SIZE(2048U) | USB_BUF_NUMB(8U));
    #endif                             /* USB_CFG_DTC == USB_CFG_ENABLE */
            break;
        }
   #endif /* defined(USB_CFG_HCDC_USE) */
  #endif /* defined(USB_CFG_HMSC_USE) */

  #if defined(USB_CFG_HVND_USE)
        case USB_PIPE1:
        {
            pipe_buf = (USB_BUF_SIZE(512U) | USB_BUF_NUMB(8U));
            break;
        }

        case USB_PIPE2:
        {
            pipe_buf = (USB_BUF_SIZE(512U) | USB_BUF_NUMB(24U));
            break;
        }

        case USB_PIPE3:
        {
            pipe_buf = (USB_BUF_SIZE(512U) | USB_BUF_NUMB(40U));
            break;
        }

        case USB_PIPE4:
        {
            pipe_buf = (USB_BUF_SIZE(512U) | USB_BUF_NUMB(56U));
            break;
        }

        case USB_PIPE5:
        {
            pipe_buf = (USB_BUF_SIZE(512U) | USB_BUF_NUMB(72U));
            break;
        }
  #endif                               /* defined(USB_CFG_HVND_USE) */

  #if defined(USB_CFG_HPRN_USE)
        case USB_CFG_HPRN_BULK_IN:
        {
   #if (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HPRN_MULTI == USB_CFG_ENABLE)
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(8U));
   #else                               /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HPRN_MULTI == USB_CFG_ENABLE) */
            pipe_buf = (USB_BUF_SIZE(2048U) | USB_BUF_NUMB(8U));
   #endif                              /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HPRN_MULTI == USB_CFG_ENABLE) */
            break;
        }

        case USB_CFG_HPRN_BULK_OUT:
        {
   #if (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HPRN_MULTI == USB_CFG_ENABLE)
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(40U));
   #else                               /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HPRN_MULTI == USB_CFG_ENABLE) */
            pipe_buf = (USB_BUF_SIZE(2048U) | USB_BUF_NUMB(72U));
   #endif                              /* (USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_HPRN_MULTI == USB_CFG_ENABLE) */
            break;
        }

   #if (USB_NULL != USB_CFG_HPRN_BULK_IN2)
        case USB_CFG_HPRN_BULK_IN2:
        {
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(72U));
            break;
        }
   #endif                              /* (USB_NULL != USB_CFG_HPRN_BULK_IN2) */

   #if (USB_NULL != USB_CFG_HPRN_BULK_OUT2)
        case USB_CFG_HPRN_BULK_OUT2:
        {
            pipe_buf = (USB_BUF_SIZE(1024U) | USB_BUF_NUMB(104U));
            break;
        }
   #endif                              /* (USB_NULL != USB_CFG_HPRN_BULK_OUT2) */
  #endif                               /* defined(USB_CFG_HPRN_USE) */

  #if defined(USB_CFG_HUVC_USE)
        case USB_CFG_HUVC_ISO_IN:
        {
            pipe_buf = (USB_BUF_SIZE(2048u) | USB_BUF_NUMB(8u));
            break;
        }

        case USB_CFG_HUVC_ISO_OUT:
        {
            pipe_buf = (USB_BUF_SIZE(2048u) | USB_BUF_NUMB(72u));
            break;
        }
  #endif                               /* defined(USB_CFG_PAUD_USE) */

        default:
        {
            /* Error */
            break;
        }
    }

    return pipe_buf;
}                                      /* End of function usb_hstd_get_pipe_buf_value() */

 #endif /* defined (USB_HIGH_SPEED_MODULE) */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
