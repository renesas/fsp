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

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Renesas Abstracted Peripheral FIFO access functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_brdy_pipe
 * Description     : Execute data transfer for the PIPE for which a BRDY interrupt
 *               : occurred.
 * Arguments       : uint16_t bitsts : BRDYSTS register & BRDYENB register.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_brdy_pipe (usb_utr_t * p_utr, uint16_t bitsts)
{
    /* When operating by the peripheral function, usb_pstd_brdy_pipe() is executed with PIPEx request because */
    /* two BRDY messages are issued even when the demand of PIPE0 and PIPEx has been generated at the same time. */
    if (USB_BRDY0 == (bitsts & USB_BRDY0))
    {
        switch (usb_pstd_read_data(USB_PIPE0, USB_CUSE, p_utr))
        {
            /* End of data read */
            case USB_READEND:

            /* Continue */
            /* End of data read */
            case USB_READSHRT:
            {
                hw_usb_clear_brdyenb(p_utr, (uint16_t) USB_PIPE0);
                break;
            }

            /* Continue of data read */
            case USB_READING:
            {
                /* PID = BUF */
                usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                break;
            }

            /* FIFO access error */
            case USB_READOVER:
            {
                USB_PRINTF0("### Receive data over PIPE0 \n");

                /* Clear BVAL */
                hw_usb_set_bclr(p_utr, USB_CUSE);

                /* Control transfer stop(end) */
                usb_pstd_ctrl_end((uint16_t) USB_DATA_OVR, p_utr);
                break;
            }

            /* FIFO access error */
            case USB_FIFOERROR:
            {
                USB_PRINTF0("### FIFO access error \n");

                /* Control transfer stop(end) */
                usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, p_utr);
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
        /* not PIPE0 */
        usb_pstd_brdy_pipe_process(p_utr, bitsts);
    }
}

/******************************************************************************
 * End of function usb_pstd_brdy_pipe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_nrdy_pipe
 * Description     : Execute appropriate processing for the PIPE for which a NRDY
 *               : interrupt occurred.
 * Arguments       : uint16_t bitsts : NRDYSTS register & NRDYENB register.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_nrdy_pipe (usb_utr_t * p_utr, uint16_t bitsts)
{
    /* The function for peripheral driver is created here. */
    if (USB_NRDY0 == (bitsts & USB_NRDY0))
    {
        /* Non processing. */
    }
    else
    {
        /* Nrdy Pipe interrupt */
        usb_pstd_nrdy_pipe_process(p_utr, bitsts);
    }
}

/******************************************************************************
 * End of function usb_pstd_nrdy_pipe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_bemp_pipe
 * Description     : Execute data transfer for the PIPE for which a BEMP interrupt
 *               : occurred.
 * Arguments       : uint16_t bitsts : BEMPSTS register & BEMPENB register.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_bemp_pipe (usb_utr_t * p_utr, uint16_t bitsts)
{
    /* When operating by the peripheral function, usb_pstd_bemp_pipe() is executed with PIPEx request because */
    /* two BEMP messages are issued even when the demand of PIPE0 and PIPEx has been generated at the same time. */
    if (USB_BEMP0 == (bitsts & USB_BEMP0))
    {
        switch (usb_pstd_write_data(USB_PIPE0, USB_CUSE, p_utr))
        {
            /* End of data write (not null) */
            case USB_WRITEEND:

            /* Continue */
            /* End of data write */
            case USB_WRITESHRT:
            {
                /* Enable empty interrupt */
                hw_usb_clear_bempenb(p_utr, (uint16_t) USB_PIPE0);
                break;
            }

            /* Continue of data write */
            case USB_WRITING:
            {
                /* PID = BUF */
                usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                break;
            }

            /* FIFO access error */
            case USB_FIFOERROR:
            {
                USB_PRINTF0("### FIFO access error \n");

                /* Control transfer stop(end) */
                usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, p_utr);
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
        /* BEMP interrupt */
        usb_pstd_bemp_pipe_process(p_utr, bitsts);
    }
}

/******************************************************************************
 * End of function usb_pstd_bemp_pipe
 ******************************************************************************/
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
