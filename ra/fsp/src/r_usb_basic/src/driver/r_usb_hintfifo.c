/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
/******************************************************************************
 Renesas Abstracted Host FIFO Interrupt functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_brdy_pipe
 Description     : BRDY Interrupt
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t bitsts  : BRDYSTS Reg & BRDYENB Reg
 Return value    : none
 ******************************************************************************/
void usb_hstd_brdy_pipe (usb_utr_t *ptr)
{
    uint16_t bitsts;

    bitsts = ptr->status;

    /* When operating by the host function, usb_hstd_brdy_pipe() is executed without fail because */
    /* only one BRDY message is issued even when the demand of PIPE0 and PIPEx has been generated at the same time. */
    if (USB_BRDY0 == (bitsts & USB_BRDY0))
    {
        /* Branch  by the Control transfer stage management */
        switch (g_usb_hstd_ctsq[ptr->ip])
        {
            /* Data stage of Control read transfer */
            case USB_DATARD :
                switch (usb_hstd_read_data(ptr, USB_PIPE0, USB_CUSE))
                {
                    /* End of data read */
                    case USB_READEND :

                        /* continue */
                        /* End of data read */
                    case USB_READSHRT :
                        usb_hstd_status_start(ptr);
                    break;
                    case USB_READING : /* Continue of data read */
                    break;
                    case USB_READOVER : /* FIFO access error */
                        USB_PRINTF0("### Receive data over PIPE0 \n");
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_OVR); /* Control Read/Write End */
                    break;

                    case USB_FIFOERROR : /* FIFO access error */
                        USB_PRINTF0("### FIFO access error \n");
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR); /* Control Read/Write End */
                    break;
                    default :
                    break;
                }
            break;

                /* Data stage of Control read transfer */
            case USB_DATARDCNT :
                switch (usb_hstd_read_data(ptr, USB_PIPE0, USB_CUSE))
                {

                    case USB_READEND : /* End of data read */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_CTRL_READING); /* Control Read/Write End */
                    break;
                    case USB_READSHRT : /* End of data read */
                        usb_hstd_status_start(ptr); /* Control Read/Write Status */
                    break;
                    case USB_READING : /* Continue of data read */
                    break;
                    case USB_READOVER : /* FIFO access error */
                        USB_PRINTF0("### Receive data over PIPE0 \n");
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_OVR); /* Control Read/Write End */
                    break;
                    case USB_FIFOERROR : /* FIFO access error */
                        USB_PRINTF0("### FIFO access error \n");
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR); /* Control Read/Write End */
                    break;
                    default :
                    break;
                }
            break;

                /* Status stage of Control write (NoData control) transfer */
            case USB_STATUSWR :
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_CTRL_END); /* Control Read/Write End */
            break;
            default :
            break;
        }
    }

    /* BRDY interrupt */
    usb_hstd_brdy_pipe_process(ptr, bitsts);
}
/******************************************************************************
 End of function usb_hstd_brdy_pipe
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_nrdy_pipe
 Description     : NRDY Interrupt
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t bitsts  : NRDYSTS Reg & NRDYENB Reg
 Return value    : none
 ******************************************************************************/
void usb_hstd_nrdy_pipe (usb_utr_t *ptr)
{
    uint16_t buffer;
    uint16_t bitsts;

    bitsts = ptr->status;

    /* When operating by the host function, usb_hstd_nrdy_pipe() is executed without fail because */
    /* only one NRDY message is issued even when the demand of PIPE0 and PIPEx has been generated at the same time. */
    if (USB_NRDY0 == (bitsts & USB_NRDY0))
    {
        /* Get Pipe PID from pipe number */
        buffer = usb_cstd_get_pid(ptr, (uint16_t) USB_PIPE0);

        /* STALL ? */
        if (USB_PID_STALL == (buffer & USB_PID_STALL))
        {
            USB_PRINTF0("### STALL Pipe 0\n");

            /* PIPE0 STALL call back */
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_STALL);
        }
        else
        {
            /* Ignore count */
            g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]++;
            USB_PRINTF2("### IGNORE Pipe %d is %d times \n", USB_PIPE0, g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]);

            /* Pipe error check */
            if (USB_PIPEERROR == g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0])
            {
                /* Control Data Stage Device Ignore X 3 call back */
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
            }
            else
            {
                /* Control Data Stage Retry */
                /* 5ms wait */
                usb_cpu_delay_xms((uint16_t) 5);

                /* PIPE0 Send IN or OUT token */
                usb_cstd_set_buf(ptr, (uint16_t) USB_PIPE0);
            }
        }
    }

    /* Nrdy Pipe interrupt */
    usb_hstd_nrdy_pipe_process(ptr, bitsts);
}
/******************************************************************************
 End of function usb_hstd_nrdy_pipe
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_bemp_pipe
 Description     : BEMP interrupt
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t bitsts  : BEMPSTS Reg & BEMPENB Reg
 Return value    : none
 ******************************************************************************/
void usb_hstd_bemp_pipe (usb_utr_t *ptr)
{
    uint16_t buffer;
    uint16_t bitsts;

    bitsts = ptr->status;

    /* When operating by the host function, usb_hstd_bemp_pipe() is executed without fail because */
    /* only one BEMP message is issued even when the demand of PIPE0 and PIPEx has been generated at the same time. */
    if (USB_BEMP0 == (bitsts & USB_BEMP0))
    {
        buffer = usb_cstd_get_pid(ptr, (uint16_t) USB_PIPE0); /* Get Pipe PID from pipe number */
        if (USB_PID_STALL == (buffer & USB_PID_STALL)) /* MAX packet size error ? */
        {
            USB_PRINTF0("### STALL Pipe 0\n");
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_STALL); /* PIPE0 STALL call back */
        }
        else
        {
            switch (g_usb_hstd_ctsq[ptr->ip]) /* Branch  by the Control transfer stage management */
            {
                /* Continuas of data stage (Control write) */
                case USB_DATAWR :
                    switch (usb_hstd_write_data(ptr, USB_PIPE0, USB_CUSE)) /* Buffer to CFIFO data write */
                    {
                        /* End of data write */
                        case USB_WRITESHRT :
                            g_usb_hstd_ctsq[ptr->ip] = USB_STATUSWR; /* Next stage is Control write status stage */
                            hw_usb_set_bempenb(ptr, (uint16_t) USB_PIPE0); /* Enable Empty Interrupt */
                            usb_cstd_nrdy_enable(ptr, (uint16_t) USB_PIPE0); /* Enable Not Ready Interrupt */
                        break;

                            /* End of data write (not null) */
                        case USB_WRITEEND :

                            /* continue */
                            /* Continue of data write */
                        case USB_WRITING :
                            hw_usb_set_bempenb(ptr, (uint16_t) USB_PIPE0); /* Enable Empty Interrupt */
                            usb_cstd_nrdy_enable(ptr, (uint16_t) USB_PIPE0); /* Enable Not Ready Interrupt */
                        break;

                            /* FIFO access error */
                        case USB_FIFOERROR :
                            USB_PRINTF0("### FIFO access error \n");
                            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR); /* Control Read/Write End */
                        break;
                        default :
                        break;
                    }
                break;

                    /* Next stage to Control write data */
                case USB_DATAWRCNT :

                    /* Buffer to CFIFO data write */
                    switch (usb_hstd_write_data(ptr, USB_PIPE0, USB_CUSE))
                    {
                        /* End of data write */
                        case USB_WRITESHRT :
                            g_usb_hstd_ctsq[ptr->ip] = USB_STATUSWR; /* Next stage is Control write status stage */
                            hw_usb_set_bempenb(ptr, (uint16_t) USB_PIPE0); /* Enable Empty Interrupt */
                            usb_cstd_nrdy_enable(ptr, (uint16_t) USB_PIPE0); /* Enable Not Ready Interrupt */
                        break;

                            /* End of data write (not null) */
                        case USB_WRITEEND :
                            usb_hstd_ctrl_end(ptr, (uint16_t) USB_CTRL_WRITING); /* Control Read/Write End */
                        break;

                            /* Continue of data write */
                        case USB_WRITING :
                            hw_usb_set_bempenb(ptr, (uint16_t) USB_PIPE0); /* Enable Empty Interrupt */
                            usb_cstd_nrdy_enable(ptr, (uint16_t) USB_PIPE0); /* Enable Not Ready Interrupt */
                        break;

                            /* FIFO access error */
                        case USB_FIFOERROR :
                            USB_PRINTF0("### FIFO access error \n");
                            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR); /* Control Read/Write End */
                        break;
                        default :
                        break;
                    }
                break;
                case USB_STATUSWR : /* End of data stage (Control write) */
                    usb_hstd_status_start(ptr);
                break;
                case USB_STATUSRD : /* Status stage of Control read transfer */
                    usb_hstd_ctrl_end(ptr, (uint16_t) USB_CTRL_END); /* Control Read/Write End */
                break;
                default :
                break;
            }
        }
    }
    usb_hstd_bemp_pipe_process(ptr, bitsts); /* BEMP interrupt */
}
/******************************************************************************
 End of function usb_hstd_bemp_pipe
 ******************************************************************************/
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 End  Of File
 ******************************************************************************/
