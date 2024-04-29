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

#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"
#include "inc/r_usb_basic_define.h"
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if (BSP_CFG_RTOS == 1)
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_api.h"
 #if defined(USB_CFG_OTG_USE)
  #if defined(USB_CFG_HCDC_USE)
   #include "ux_host_class_cdc_acm.h"
  #endif                               /* defined(USB_CFG_HCDC_USE) */
  #if defined(USB_CFG_HHID_USE)
   #include "ux_host_class_hid.h"
   #include "ux_host_class_hid_keyboard.h"
   #include "ux_host_class_hid_mouse.h"
   #include "ux_host_class_hid_remote_control.h"
  #endif                               /* defined(USB_CFG_HHID_USE) */
  #if defined(USB_CFG_HMSC_USE)
   #include "ux_host_class_storage.h"
  #endif                               /* defined(USB_CFG_HMSC_USE) */
 #endif                                /* defined(USB_CFG_OTG_USE) */
 #if defined(USB_CFG_PCDC_USE)
  #include "r_usb_pcdc_cfg.h"
 #endif                                /* defined(USB_CFG_PCDC_USE) */
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
 #include "../hw/inc/r_usb_dmac.h"
#endif                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/*******************************************************************************
 * Macro definitions
 ******************************************************************************/

 #define USB_VALUE_100       (100)
 #define USB_OTG_SE0_BRST    (16)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
 #if (BSP_CFG_RTOS != 0)
static void usb_pstd_interrupt(usb_utr_t * p_mess);

 #else                                 /*(BSP_CFG_RTOS != 0)*/
static void usb_pstd_interrupt(uint16_t type, uint16_t status, usb_cfg_t * p_cfg);

 #endif /*(BSP_CFG_RTOS != 0)*/

 #if defined(USB_CFG_OTG_USE)
static void usb_pstd_otg_hnp_process(usb_utr_t * p_utr);
static void usb_pstd_otg_mode_to_host(usb_utr_t * p_utr);

 #endif                                                 /* defined(USB_CFG_OTG_USE) */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
uint16_t g_usb_pstd_config_num = 0;                     /* Current configuration number */
uint16_t g_usb_pstd_alt_num[USB_ALT_NO];                /* Alternate number */
#endif /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

usb_cb_t g_usb_pstd_stall_cb;                           /* Stall Callback function */
uint16_t g_usb_pstd_stall_pipe[USB_MAX_PIPE_NO + 1U];   /* Stall Pipe info */
uint16_t g_usb_pstd_remote_wakeup = USB_FALSE;          /* Remote wake up enable flag */
uint16_t g_usb_pstd_remote_wakeup_state;                /* Result for Remote wake up */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
uint16_t g_usb_pstd_test_mode_select;                   /* Test mode selectors */
uint16_t g_usb_pstd_test_mode_flag = USB_FALSE;         /* Test mode flag */

uint16_t g_usb_pstd_eptbl_index[2][USB_MAX_EP_NO + 1U]; /* Index of endpoint information table */
uint16_t g_usb_pstd_req_type;                           /* Request type */
uint16_t g_usb_pstd_req_value;                          /* Value */
uint16_t g_usb_pstd_req_index;                          /* Index */
uint16_t g_usb_pstd_req_length;                         /* Length */

uint16_t g_usb_pstd_pipe0_request;
uint16_t g_usb_pstd_std_request;
uint16_t g_usb_peri_connected;                          /* Status for USB connect. */

/* Driver registration */
usb_pcdreg_t g_usb_pstd_driver;
usb_setup_t  g_usb_pstd_req_reg;                        /* Device Request - Request structure */

 #if (BSP_CFG_RTOS == 1)
uint8_t g_usb_peri_usbx_is_configured[USB_NUM_USBIP];
 #endif /* (BSP_CFG_RTOS == 1) */

volatile uint8_t g_usb_is_otg_attach_interrupt[USB_NUM_USBIP];

 #if (BSP_CFG_RTOS == 1)
extern bool         g_usb_peri_usbx_is_detach[USB_MAX_PIPE_NO + 1];
extern bool         g_usb_peri_usbx_is_fifo_error[USB_MAX_PIPE_NO + 1];
extern TX_SEMAPHORE g_usb_peri_usbx_sem[USB_MAX_PIPE_NO + 1];
extern UINT usb_host_usbx_initialize(UX_HCD * hcd);

  #if defined(USB_CFG_OTG_USE)
extern uint8_t        g_is_usbx_otg_host_class_init[USB_NUM_USBIP];
extern rtos_task_id_t g_hcd_tsk_hdl;
extern uint8_t        g_usb_otg_suspend_flag[USB_NUM_USBIP];

  #endif                               /* #if defined(USB_CFG_OTG_USE) */
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Renesas Abstracted Peripheral Driver functions
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_pstd_interrupt
 * Description     : Analyze the USB Peripheral interrupt event and execute the
 *               : appropriate process.
 * Arguments       : uint16_t type      : Interrupt type.
 *               : uint16_t status    : BRDYSTS register & BRDYENB register.
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_interrupt (uint16_t type, uint16_t status, usb_cfg_t * p_cfg)
{
    uint16_t  stginfo;
    usb_utr_t utr;

    utr.ip = p_cfg->module_number;
  #if (USB_CFG_DMA == USB_CFG_ENABLE)
    utr.p_transfer_rx = p_cfg->p_transfer_rx;
    utr.p_transfer_tx = p_cfg->p_transfer_tx;
  #endif

    /* check interrupt status */
    switch (type)
    {
        /* BRDY, BEMP, NRDY */
        case USB_INT_BRDY:
        {
            usb_pstd_brdy_pipe(&utr, status);
            break;
        }

        case USB_INT_BEMP:
        {
            usb_pstd_bemp_pipe(&utr, status);
            break;
        }

        case USB_INT_NRDY:
        {
            usb_pstd_nrdy_pipe(&utr, status);
            break;
        }

        /* Resume */
        case USB_INT_RESM:
        {
            USB_PRINTF0("RESUME int peri\n");

            /* Callback */
            if (USB_NULL != g_usb_pstd_driver.devresume)
            {
                (*g_usb_pstd_driver.devresume)(&utr, USB_NO_ARG, USB_NULL);
            }

            usb_pstd_resume_process(&utr);
            break;
        }

        /* VBUS */
        case USB_INT_VBINT:
        {
  #if defined(USB_HIGH_SPEED_MODULE)
            hw_usb_set_cnen(p_cfg->module_number);
  #endif                                       /* defined (USB_HIGH_SPEED_MODULE) */
            if (USB_ATTACH == usb_pstd_chk_vbsts(utr.ip))
            {
                USB_PRINTF0("VBUS int attach\n");
                usb_pstd_attach_process(&utr); /* USB attach */
            }
            else
            {
                USB_PRINTF0("VBUS int detach\n");
                usb_pstd_detach_process(&utr); /* USB detach */
            }

            break;
        }

        /* SOF */
        case USB_INT_SOFR:
        {
            /* User program */
            break;
        }

        /* DVST */
        case USB_INT_DVST:
        {
            switch ((uint16_t) (status & USB_DVSQ))
            {
                /* Power state  */
                case USB_DS_POWR:
                {
                    break;
                }

                /* Default state  */
                case USB_DS_DFLT:
                {
                    USB_PRINTF0("USB-reset int peri\n");
                    usb_pstd_bus_reset(&utr);
                    break;
                }

                /* Address state  */
                case USB_DS_ADDS:
                {
                    break;
                }

                /* Configured state  */
                case USB_DS_CNFG:
                {
                    USB_PRINTF0("Device configuration int peri\n");
                    break;
                }

                /* Power suspend state */
                case USB_DS_SPD_POWR:

                /* Continue */
                /* Default suspend state */
                case USB_DS_SPD_DFLT:

                /* Continue */
                /* Address suspend state */
                case USB_DS_SPD_ADDR:

                /* Continue */
                /* Configured Suspend state */
                case USB_DS_SPD_CNFG:
                {
                    USB_PRINTF0("SUSPEND int peri\n");
                    usb_pstd_suspend_process(&utr);
                    break;
                }

                /* Error */
                default:
                {
                    break;
                }
            }

            break;
        }

        /* CTRT */
        case USB_INT_CTRT:
        {
            stginfo = (uint16_t) (status & USB_CTSQ);
            if (USB_CS_IDST == stginfo)
            {
                /* check Test mode */
                if (USB_TRUE == g_usb_pstd_test_mode_flag)
                {
                    /* Test mode */
                    usb_pstd_test_mode(&utr);
                }
            }
            else
            {
                if (((USB_CS_RDDS == stginfo) || (USB_CS_WRDS == stginfo)) || (USB_CS_WRND == stginfo))
                {
                    /* Save request register */
                    usb_pstd_save_request(p_cfg->module_number);
                }
            }

            if (USB_STANDARD == (g_usb_pstd_req_type & USB_BMREQUESTTYPETYPE))
            {
                /* Switch on the control transfer stage (CTSQ). */
                switch (stginfo)
                {
                    /* Idle or setup stage */
                    case USB_CS_IDST:
                    {
                        g_usb_pstd_pipe0_request = USB_OFF;
                        g_usb_pstd_std_request   = USB_NO;
                        usb_pstd_stand_req0(&utr);
                        break;
                    }

                    /* Control read data stage */
                    case USB_CS_RDDS:
                    {
                        usb_pstd_stand_req1(&utr);
                        break;
                    }

                    /* Control write data stage */
                    case USB_CS_WRDS:
                    {
                        usb_pstd_stand_req2(&utr);
                        break;
                    }

                    /* Status stage of a control write where there is no data stage. */
                    case USB_CS_WRND:
                    {
                        usb_pstd_stand_req3(&utr);
                        break;
                    }

                    /* Control read status stage */
                    case USB_CS_RDSS:
                    {
                        usb_pstd_stand_req4(&utr);
                        break;
                    }

                    /* Control write status stage */
                    case USB_CS_WRSS:
                    {
                        usb_pstd_stand_req5(&utr);
                        break;
                    }

                    /* Control sequence error */
                    case USB_CS_SQER:
                    {
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, &utr);
                        break;
                    }

                    /* Illegal */
                    default:
                    {
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, &utr);
                        break;
                    }
                }
            }
            else
            {
                /* Vender Specific */
                g_usb_pstd_req_reg.request_type   = g_usb_pstd_req_type;
                g_usb_pstd_req_reg.request_value  = g_usb_pstd_req_value;
                g_usb_pstd_req_reg.request_index  = g_usb_pstd_req_index;
                g_usb_pstd_req_reg.request_length = g_usb_pstd_req_length;

                /* Callback */
                if (USB_NULL != g_usb_pstd_driver.ctrltrans)
                {
                    (*g_usb_pstd_driver.ctrltrans)(&g_usb_pstd_req_reg, stginfo, &utr);
                }
            }

            break;
        }

        /* Error */
        case USB_INT_UNKNOWN:
        {
            USB_PRINTF0("pINT_UNKNOWN\n");
            break;
        }

        default:
        {
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_interrupt
 ******************************************************************************/
 #endif                                /*(BSP_CFG_RTOS == 0)*/

 #if (BSP_CFG_RTOS != 0)

/******************************************************************************
 * Function Name   : usb_pstd_interrupt
 * Description     : Analyze the USB Peripheral interrupt event and execute the
 * : appropriate process.
 * Arguments       : uint16_t type      : Interrupt type.
 *               : uint16_t status    : BRDYSTS register & BRDYENB register.
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_interrupt (usb_utr_t * p_mess)
{
    uint16_t stginfo;
    uint16_t type;
    uint16_t status;
  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t fifo_type;

    fifo_type = p_mess->status;
  #endif
    type   = p_mess->keyword;
    status = p_mess->status;

    /* check interrupt status */
    switch (type)
    {
        /* BRDY, BEMP, NRDY */
        case USB_INT_BRDY:
        {
            usb_pstd_brdy_pipe(p_mess, status);
            break;
        }

        case USB_INT_BEMP:
        {
            usb_pstd_bemp_pipe(p_mess, status);
            break;
        }

        case USB_INT_NRDY:
        {
            usb_pstd_nrdy_pipe(p_mess, status);
            break;
        }

        /* Resume */
        case USB_INT_RESM:
        {
            USB_PRINTF0("RESUME int peri\n");

            /* Callback */
            if (USB_NULL != g_usb_pstd_driver.devresume)
            {
                (*g_usb_pstd_driver.devresume)(p_mess, USB_NO_ARG, USB_NULL);
            }

            usb_pstd_resume_process(p_mess);
            break;
        }

        /* VBUS */
        case USB_INT_VBINT:
        {
  #if defined(USB_HIGH_SPEED_MODULE)
            hw_usb_set_cnen(p_mess->ip);
  #endif                                                                     /* defined (USB_HIGH_SPEED_MODULE) */
            if (USB_ATTACH == usb_pstd_chk_vbsts(p_mess->ip))
            {
                USB_PRINTF0("VBUS int attach\n");
                usb_pstd_attach_process(p_mess);                             /* USB attach */
  #if defined(USB_CFG_OTG_USE)
                _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_B; /* IDLE --> DEVICE_B */
                (*g_p_otg_callback[p_mess->ip])(UX_OTG_MODE_SLAVE);
  #endif /* defined(USB_CFG_OTG_USE) */
            }
            else
            {
                USB_PRINTF0("VBUS int detach\n");
                usb_pstd_detach_process(p_mess); /* USB detach */
  #if (BSP_CFG_RTOS == 1)
                if (USB_YES == g_usb_peri_usbx_is_configured[p_mess->ip])
                {
                    _ux_device_stack_disconnect();
                    g_usb_peri_usbx_is_configured[p_mess->ip] = USB_NO;
                }
  #endif                               /* (BSP_CFG_RTOS == 1) */

  #if defined(USB_CFG_OTG_USE)
                if (USB_YES == g_is_A_device[p_mess->ip])
                {
                    if (USB_YES == g_is_A_cable_detach[p_mess->ip])
                    {
                        g_is_A_device[p_mess->ip] = USB_NO;

                        /* A device and A cable detach --> Peri mode */
                        g_is_A_cable_detach[p_mess->ip]           = USB_NO;
                        _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE; /* A Device --> IDLE */
                        (*g_p_otg_callback[p_mess->ip])(UX_OTG_MODE_IDLE);
                    }
                    else
                    {
                        /* B cable detach in A device --> Host mode */
                        p_mess->ipp = usb_hstd_get_usb_ip_adr(p_mess->ip);
                        usb_pstd_otg_mode_to_host(p_mess);
                        if (USB_IP0 == p_mess->ip)
                        {
                            tx_timer_deactivate(&g_usb_otg_detach_timer);
                        }

   #if USB_NUM_USBIP == 2
                        else
                        {
                            tx_timer_deactivate(&g_usb2_otg_detach_timer);
                        }
   #endif                              /* USB_NUM_USBIP == 2 */
                        _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_A;
                        (*g_p_otg_callback[p_mess->ip])(UX_OTG_MODE_HOST);
                    }
                }
                else
                {
                    /* B Device only */
                    g_usb_otg_suspend_flag[p_mess->ip]        = USB_NO;
                    _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE;
                    (*g_p_otg_callback[p_mess->ip])(UX_OTG_MODE_IDLE);
                }
  #endif                               /* defined(USB_CFG_OTG_USE) */
            }

            break;
        }

        /* SOF */
        case USB_INT_SOFR:
        {
            /* User program */
            break;
        }

        /* DVST */
        case USB_INT_DVST:
        {
            switch ((uint16_t) (status & USB_DVSQ))
            {
                /* Power state  */
                case USB_DS_POWR:
                {
                    break;
                }

                /* Default state  */
                case USB_DS_DFLT:
                {
                    USB_PRINTF0("USB-reset int peri\n");
                    usb_pstd_bus_reset(p_mess);
                    break;
                }

                /* Address state  */
                case USB_DS_ADDS:
                {
                    break;
                }

                /* Configured state  */
                case USB_DS_CNFG:
                {
                    USB_PRINTF0("Device configuration int peri\n");
                    break;
                }

                /* Power suspend state */
                case USB_DS_SPD_POWR:

                /* Continue */
                /* Default suspend state */
                case USB_DS_SPD_DFLT:

                /* Continue */
                /* Address suspend state */
                case USB_DS_SPD_ADDR:

                /* Continue */
                /* Configured Suspend state */
                case USB_DS_SPD_CNFG:
  #if defined(USB_CFG_OTG_USE)
                    {
                        if ((USB_NO == g_usb_otg_suspend_flag[p_mess->ip]) &&
                            (USB_DS_SPD_POWR == (uint16_t) (status & USB_DVSQ)))
                        {
                            g_usb_otg_suspend_flag[p_mess->ip] = USB_YES;
                            break;
                        }
                    }
  #endif                               /* defined (USB_CFG_OTG_USE) */
                    {
                        USB_PRINTF0("SUSPEND int peri\n");

  #if defined(USB_CFG_OTG_USE)
                        p_mess->ipp = usb_hstd_get_usb_ip_adr(p_mess->ip); /* Get the USB IP base address. */

                        if (USB_ON == g_usb_otg_hnp_process[p_mess->ip])
                        {
                            usb_pstd_otg_hnp_process(p_mess);
                        }
                        else
  #endif                               /* defined(USB_CFG_OTG_USE) */
                        {
                            usb_pstd_suspend_process(p_mess);
                        }

                        break;
                    }

                /* Error */
                default:
                {
                    break;
                }
            }

            break;
        }

        /* CTRT */
        case USB_INT_CTRT:
        {
            stginfo = (uint16_t) (status & USB_CTSQ);
            if (USB_CS_IDST == stginfo)
            {
                /* check Test mode */
                if (USB_TRUE == g_usb_pstd_test_mode_flag)
                {
                    /* Test mode */
                    usb_pstd_test_mode(p_mess);
                }
            }
            else
            {
                if (((USB_CS_RDDS == stginfo) || (USB_CS_WRDS == stginfo)) || (USB_CS_WRND == stginfo))
                {
                    /* Save request register */
                    usb_pstd_save_request(p_mess->ip);
                }
            }

            if (USB_STANDARD == (g_usb_pstd_req_type & USB_BMREQUESTTYPETYPE))
            {
                /* Switch on the control transfer stage (CTSQ). */
                switch (stginfo)
                {
                    /* Idle or setup stage */
                    case USB_CS_IDST:
                    {
                        usb_pstd_stand_req0(p_mess);
                        break;
                    }

                    /* Control read data stage */
                    case USB_CS_RDDS:
                    {
                        usb_pstd_stand_req1(p_mess);
                        break;
                    }

                    /* Control write data stage */
                    case USB_CS_WRDS:
                    {
                        usb_pstd_stand_req2(p_mess);
                        break;
                    }

                    /* Status stage of a control write where there is no data stage. */
                    case USB_CS_WRND:
                    {
                        usb_pstd_stand_req3(p_mess);
                        break;
                    }

                    /* Control read status stage */
                    case USB_CS_RDSS:
                    {
                        usb_pstd_stand_req4(p_mess);
                        break;
                    }

                    /* Control write status stage */
                    case USB_CS_WRSS:
                    {
                        usb_pstd_stand_req5(p_mess);
                        break;
                    }

                    /* Control sequence error */
                    case USB_CS_SQER:
                    {
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, p_mess);
                        break;
                    }

                    /* Illegal */
                    default:
                    {
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, p_mess);
                        break;
                    }
                }
            }
            else
            {
                /* Vender Specific */
                g_usb_pstd_req_reg.request_type   = g_usb_pstd_req_type;
                g_usb_pstd_req_reg.request_value  = g_usb_pstd_req_value;
                g_usb_pstd_req_reg.request_index  = g_usb_pstd_req_index;
                g_usb_pstd_req_reg.request_length = g_usb_pstd_req_length;

                /* Callback */
                if (USB_NULL != g_usb_pstd_driver.ctrltrans)
                {
                    (*g_usb_pstd_driver.ctrltrans)(&g_usb_pstd_req_reg, stginfo, p_mess);
                }
            }

            break;
        }

  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        case USB_INT_DXFIFO:
        {
            usb_cstd_dma_stop(p_mess, fifo_type); /* Stop DMA,FIFO access */
            usb_cstd_dma_send_continue(p_mess, fifo_type);
            break;
        }
  #endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        /* Error */
        case USB_INT_UNKNOWN:
        {
            USB_PRINTF0("pINT_UNKNOWN\n");
            break;
        }

        default:
        {
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_interrupt
 ******************************************************************************/

  #if (BSP_CFG_RTOS == 1)
   #if defined(USB_CFG_OTG_USE)

/******************************************************************************
 * Function Name   : usb_pstd_otg_mode_to_host
 * Description     : Initialize regsister and driver from USB Peripheral to USB Host
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_otg_mode_to_host (usb_utr_t * p_utr)
{
    /* D+ Pullup Off */
    hw_usb_pclear_dprpu(p_utr->ip);

    /* D+ Pulldown On */
    hw_usb_set_drpd(p_utr);

    /* Change to Host mode */
    hw_usb_set_dcfm(p_utr);

    /* Peri UninItialization  */
    usb_module_register_clear(p_utr->ip);

    usb_pstd_clr_pipe_table(p_utr->ip);

    /* Host Initialization  */
    usb_hdriver_init(p_utr);

    g_usb_usbmode[p_utr->ip] = USB_MODE_HOST;

    /* Attach Interrupt Enable */
    hw_usb_hset_enb_attche(p_utr);
}

/******************************************************************************
 * End of function usb_pstd_otg_mode_to_host
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_otg_hnp_process
 * Description     : Swap Process from USB Peripheral to USB Host
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_otg_hnp_process (usb_utr_t * p_utr)
{
    uint16_t i;
    uint16_t usb_reg;
    uint8_t  is_otg_hnp_possible = USB_NO;

    p_utr->ipp = (usb_regadr_t) usb_hstd_get_usb_ip_adr(p_utr->ip); /* Get the USB IP base address. */

    /* D+ Pullup Off */
    hw_usb_pclear_dprpu(p_utr->ip);

    g_usb_otg_hnp_counter = 0;
    tx_timer_activate(&g_usb_otg_hnp_timer);

    /* Change to Host mode */
    hw_usb_set_dcfm(p_utr);

    /* D+ Pulldown On */
    hw_usb_set_drpd(p_utr);

    g_usb_usbmode[p_utr->ip] = USB_MODE_HOST;

    _ux_utility_thread_suspend(&g_hcd_tsk_hdl);

    for (i = 0; i < USB_VALUE_100; i++)
    {
        /* Wait 3ms */
        usb_cpu_delay_xms((uint16_t) 1);
        if (USB_ATTCH == (p_utr->ipp->INTSTS1 & USB_ATTCH))
        {
            break;
        }
    }

    /* Attach Interrupt Enable */
    hw_usb_hset_enb_attche(p_utr);

    /* Wait 3ms */
    usb_cpu_delay_xms((uint16_t) 3);

    g_usb_otg_hnp_counter = 0;
    if (g_usb_otg_hnp_counter <= USB_OTG_SE0_BRST)
    {
        is_otg_hnp_possible = USB_YES;
    }

    tx_timer_deactivate(&g_usb_otg_hnp_timer);

    if (((USB_YES == g_usb_is_otg_attach_interrupt[p_utr->ip]) ||
         ((USB_YES == g_is_A_device[p_utr->ip]) && (USB_NO == g_is_A_cable_detach[p_utr->ip]))) &&
        (USB_YES == is_otg_hnp_possible))
    {
        g_usb_is_otg_attach_interrupt[p_utr->ip] = USB_NO;
        is_otg_hnp_possible = USB_NO;

        /* USB Peripheral --> USB Host */

        /* Peri UninItialization  */
        usb_module_register_clear(p_utr->ip);

        usb_pstd_clr_pipe_table(p_utr->ip);

        _ux_device_stack_disconnect();

        /* Host Initialization  */
        usb_hdriver_init(p_utr);

        if (USB_NO == g_is_usbx_otg_host_class_init[p_utr->ip])
        {
    #if defined(USB_CFG_HCDC_USE)
            ux_host_stack_class_register(_ux_system_host_class_cdc_acm_name, ux_host_class_cdc_acm_entry);
            if (USB_IP1 == p_utr->ip)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hcdc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hcdc_fs", usb_host_usbx_initialize, R_USB_FS0_BASE, 0);
            }
    #endif                             /* defined(USB_CFG_HCDC_USE) */
    #if defined(USB_CFG_HMSC_USE)
            ux_host_stack_class_register(_ux_system_host_class_storage_name, ux_host_class_storage_entry);
            if (USB_IP1 == p_utr->ip)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hmsc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hmsc_fs", usb_host_usbx_initialize, R_USB_FS0_BASE, 0);
            }
    #endif                             /* defined(USB_CFG_HCDC_USE) */
    #if defined(USB_CFG_HHID_USE)
            ux_host_stack_class_register(_ux_system_host_class_hid_name, ux_host_class_hid_entry);

            ux_host_class_hid_client_register(_ux_system_host_class_hid_client_keyboard_name,
                                              ux_host_class_hid_keyboard_entry);
            ux_host_class_hid_client_register(_ux_system_host_class_hid_client_mouse_name,
                                              ux_host_class_hid_mouse_entry);

            if (USB_IP1 == p_utr->ip)
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hhid_hs", usb_host_usbx_initialize, R_USB_HS0_BASE, 0);
            }
            else
            {
                ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hhid_fs", usb_host_usbx_initialize, R_USB_FS0_BASE, 0);
            }
    #endif                             /* defined(USB_CFG_HHID_USE) */

            g_is_usbx_otg_host_class_init[p_utr->ip] = USB_YES;
        }

        (*g_p_otg_callback[p_utr->ip])(UX_OTG_MODE_HOST);

        p_utr->ipp->INTENB1 &= (uint16_t) (~(uint16_t) USB_ATTCHE);
        p_utr->ipp->INTENB1 |= (uint16_t) (USB_ATTCHE);
    }
    else
    {
        /* There is no Attach interrupt */

        /* Host Uinitialization */
        usb_module_register_clear(p_utr->ip);

        /* D+ Pullup Off */
        hw_usb_pclear_dprpu(p_utr->ip);

        /* D+ Pulldown Off */
        hw_usb_clear_drpd(p_utr);

        /* Change to Peri mode */
        hw_usb_clear_dcfm(p_utr);

        /* D+ Pullup On */
        hw_usb_pset_dprpu(p_utr->ip);

        g_usb_usbmode[p_utr->ip] = USB_MODE_PERI;

        p_utr->ipp->INTENB0 = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);

        if (USB_YES == g_is_A_device[p_utr->ip])
        {
            usb_reg = hw_usb_read_syssts(p_utr);
            if (0 == (usb_reg & USB_IDMON))
            {
                (*g_p_otg_callback[p_utr->ip])(UX_OTG_MODE_SLAVE);
            }
            else
            {
                (*g_p_otg_callback[p_utr->ip])(UX_OTG_MODE_IDLE);
            }
        }
        else
        {
            usb_reg = hw_usb_read_intsts(p_utr->ip);
            if (USB_VBSTS == (usb_reg & USB_VBSTS))
            {
                (*g_p_otg_callback[p_utr->ip])(UX_OTG_MODE_SLAVE);
            }
            else
            {
                (*g_p_otg_callback[p_utr->ip])(UX_OTG_MODE_IDLE);
            }
        }
    }

    _ux_utility_thread_resume(&g_hcd_tsk_hdl);

    g_usb_otg_hnp_process[p_utr->ip] = USB_OFF;
}

   #endif                              /* defined(USB_CFG_OTG_USE) */
  #endif                               /* BSP_CFG_RTOS == 1 */

 #endif                                /*(BSP_CFG_RTOS != 0)*/

/******************************************************************************
 * End of function usb_pstd_otg_hnp_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_pcd_task
 * Description     : The Peripheral Control Driver(PCD) task.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 1)
void usb_pstd_pcd_task (ULONG entry_input)
 #else                                 /* #if (BSP_CFG_RTOS == 1) */
void usb_pstd_pcd_task (void)
 #endif /* #if (BSP_CFG_RTOS == 1) */
{
 #if (BSP_CFG_RTOS == 1)
    (void) entry_input;
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
 #if (BSP_CFG_RTOS == 0)
    if (g_usb_pstd_usb_int.wp != g_usb_pstd_usb_int.rp)
    {
        /* Pop Interrupt info */
        usb_pstd_interrupt(g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.rp].type,
                           g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.rp].status,
                           g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.rp].p_cfg);

        /* Read CountUp */
        g_usb_pstd_usb_int.rp = (uint8_t) ((uint8_t) (g_usb_pstd_usb_int.rp + 1) % USB_INT_BUFSIZE);
    }

  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    usb_cstd_dma_driver();             /* USB DMA driver */
  #endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
 #endif /*(BSP_CFG_RTOS == 0)*/

 #if (BSP_CFG_RTOS != 0)
    usb_er_t    err;
    usb_utr_t * p_mess;

    /* WAIT_LOOP */
    while (1)
    {
        err = USB_TRCV_MSG(USB_PCD_MBX, (usb_msg_t **) &p_mess, (usb_tm_t) 1000);
        if (USB_OK == err)
        {
            switch (p_mess->msginfo)
            {
                case USB_MSG_PCD_INT:
                {
                    usb_pstd_interrupt(p_mess);
                    break;
                }

                case USB_MSG_PCD_SUBMITUTR:
                {
                    usb_pstd_set_submitutr(p_mess);
                    break;
                }

                case USB_MSG_PCD_TRANSEND1:
                {
                    usb_pstd_forced_termination(p_mess->keyword, (uint16_t) USB_DATA_STOP, p_mess);
                    break;
                }

                case USB_MSG_PCD_REMOTEWAKEUP:
                {
                    usb_pstd_self_clock(p_mess->ip);
                    usb_pstd_remote_wakeup(p_mess->ip);
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }
 #endif                                /*(BSP_CFG_RTOS != 0)*/
}

/******************************************************************************
 * End of function usb_pstd_pcd_task
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_submitutr
 * Description     : USB Peripheral Submit utr.
 * Arguments       : usb_utr_t *utrmsg    : Pointer to usb_utr_t structure
 * Return value    : usb_er_t
 ******************************************************************************/
usb_er_t usb_pstd_set_submitutr (usb_utr_t * utrmsg)
{
    uint16_t pipenum;

    pipenum = utrmsg->keyword;

 #if (BSP_CFG_RTOS == 0)
    g_p_usb_pstd_pipe[pipenum] = utrmsg;
 #endif                                /* (BSP_CFG_RTOS == 0) */

    /* Check state (Configured) */
    if (USB_TRUE == usb_pstd_chk_configured(utrmsg))
    {
 #if (BSP_CFG_RTOS != 0)
        if (USB_NULL != g_p_usb_pstd_pipe[pipenum])
        {
            usb_cstd_pipe_msg_forward(utrmsg, pipenum);

            return USB_OK;
        }
 #endif                                /* (BSP_CFG_RTOS != 0) */

 #if (BSP_CFG_RTOS != 0)
        g_p_usb_pstd_pipe[pipenum] = utrmsg;
 #endif                                /* (BSP_CFG_RTOS != 0) */

        /* Data transfer */
        if (USB_DIR_P_OUT == usb_cstd_get_pipe_dir(utrmsg, pipenum))
        {
            usb_pstd_receive_start(pipenum); /* Out transfer */
        }
        else
        {
            /* In transfer */
            usb_pstd_send_start(pipenum);
        }
    }
    else
    {
 #if (BSP_CFG_RTOS != 0)
        if (USB_PIPE0 == pipenum)
        {
            usb_cstd_pipe0_msg_clear(utrmsg, 0);
        }
        else
        {
            usb_cstd_pipe_msg_clear(utrmsg, pipenum);
        }

 #else                                 /* (BSP_CFG_RTOS != 0) */
        /* Transfer stop */
        usb_pstd_forced_termination(pipenum, (uint16_t) USB_DATA_ERR, utrmsg);
 #endif /* (BSP_CFG_RTOS != 0) */
    }

    return USB_OK;
}

/******************************************************************************
 * End of function usb_pstd_set_submitutr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_clr_alt
 * Description     : Zero-clear the alternate table (buffer).
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_clr_alt (void)
{
    uint16_t i;

    /* WAIT_LOOP */
    for (i = 0; i < USB_ALT_NO; ++i)
    {
        /* Alternate table clear */
        g_usb_pstd_alt_num[i] = 0;
    }
}

/******************************************************************************
 * End of function usb_pstd_clr_alt
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_clr_mem
 * Description     : Initialize global variables defined for peripheral mode.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_clr_mem (void)
{
    g_usb_pstd_config_num    = 0;         /* Configuration number */
    g_usb_pstd_remote_wakeup = USB_FALSE; /* Remote wake up enable flag */
    usb_pstd_clr_alt();                   /* Alternate setting clear */
}

/******************************************************************************
 * End of function usb_pstd_clr_mem
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_config_num
 * Description     : Set specified configuration number.
 * Arguments       : uint16_t value    : Configuration number
 * Return value    : none
 ******************************************************************************/
void usb_pstd_set_config_num (uint16_t value)
{
    g_usb_pstd_config_num = value;     /* Set configuration number */
    usb_pstd_clr_alt();                /* Alternate setting clear */
}

/******************************************************************************
 * End of function usb_pstd_set_config_num
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_clr_eptbl_index
 * Description     : Clear Endpoint Index Table (buffer).
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_clr_eptbl_index (void)
{
    uint16_t i;

    /* WAIT_LOOP */
    for (i = 0; i <= USB_MAX_EP_NO; ++i)
    {
        /* EndPoint index table clear */
        g_usb_pstd_eptbl_index[0][i] = USB_ERROR;
        g_usb_pstd_eptbl_index[1][i] = USB_ERROR;
    }
}

/******************************************************************************
 * End of function usb_pstd_clr_eptbl_index
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_get_interface_num
 * Description     : Get interface number
 * Arguments       : void
 * Return value    : uint16_t         : Number of this interface(bNumInterfaces)
 ******************************************************************************/
uint16_t usb_pstd_get_interface_num (void)
{
    uint16_t num_if = 0;

    /* Get NumInterfaces.        4:bNumInterfaces */
    num_if = *(g_usb_pstd_driver.p_configtbl + USB_DEV_B_NUM_INTERFACES);

    return num_if;
}

/******************************************************************************
 * End of function usb_pstd_get_interface_num
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_get_alternate_num
 * Description     : Get Alternate Setting Number
 * Arguments       : uint16_t con_num : Configuration Number
 *               : uint16_t int_num : Interface Number
 * Return value    : uint16_t         : Value used to select this alternate (bAlternateSetting)
 ******************************************************************************/
uint16_t usb_pstd_get_alternate_num (uint16_t int_num)
{
    uint16_t  i;
    uint16_t  alt_num = 0;
    uint8_t * ptr;
    uint16_t  length;

    ptr = g_usb_pstd_driver.p_configtbl;
    i   = ptr[0];

    /* Interface descriptor[0] */
    ptr     = (uint8_t *) ((uint32_t) ptr + ptr[0]);
    length  = (uint16_t) (*(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint16_t) 2U));
    length |= (uint16_t) ((uint16_t) (*(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint16_t) 3U)) << 8U);

    /* Search descriptor table size */
    /* WAIT_LOOP */
    for ( ; i < length; )
    {
        /* Descriptor type ? */
        switch (ptr[1])
        {
            /* Interface */
            case USB_DT_INTERFACE:
            {
                if (int_num == ptr[2])
                {
                    /* Alternate number count */
                    alt_num = (uint16_t) ptr[3];
                }

                i = (uint16_t) (i + ptr[0]);

                /* Interface descriptor[0] */
                ptr = (uint8_t *) ((uint32_t) ptr + ptr[0]);
                break;
            }

            /* Device */
            case USB_DT_DEVICE:

            /* Continue */
            /* Configuration */
            case USB_DT_CONFIGURATION:

            /* Continue */
            /* String */
            case USB_DT_STRING:

            /* Continue */
            /* EndPoint */
            case USB_DT_ENDPOINT:

            /* Continue */
            /* Class, Vendor, else */
            default:
            {
                i = (uint16_t) (i + ptr[0]);

                /* Interface descriptor[0] */
                ptr = (uint8_t *) ((uint32_t) ptr + ptr[0]);
                break;
            }
        }
    }

    return alt_num;
}

/******************************************************************************
 * End of function usb_pstd_get_alternate_num
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_eptbl_index
 * Description     : Set endpoint index in table (buffer) region based on config-
 *               : uration descriptor. In other words, set which endpoints to
 *               : use based on specified configuration,
 * Arguments       : uint16_t con_num : Configuration Number.
 *               : uint16_t int_num : Interface Number.
 *               : uint16_t alt_num : Alternate Setting.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_set_eptbl_index (uint16_t int_num, uint16_t alt_num)
{
    uint8_t * ptr;
    uint16_t  i;
    uint16_t  j;
    uint16_t  length;
    uint16_t  start;
    uint16_t  numbers;
    uint16_t  ep;
    uint16_t  dir;

    /* Configuration descriptor */
    ptr     = g_usb_pstd_driver.p_configtbl;
    i       = *ptr;
    length  = (uint16_t) (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 3U));
    length  = (uint16_t) (length << 8);
    length  = (uint16_t) (length + (uint16_t) (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 2U)));
    ptr     = (uint8_t *) ((uint32_t) ptr + (*ptr));
    start   = 0;
    numbers = 0;
    j       = 0;

    /* WAIT_LOOP */
    for ( ; i < length; )
    {
        /* Descriptor type ? */
        switch (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 1U))
        {
            /* Interface */
            case USB_DT_INTERFACE:
            {
                if (((*(uint8_t *) ((uint32_t) ptr + (uint32_t) 2U)) == int_num) &&
                    ((*(uint8_t *) ((uint32_t) ptr + (uint32_t) 3U)) == alt_num))
                {
                    numbers = *(uint8_t *) ((uint32_t) ptr + (uint32_t) 4U);
                }
                else
                {
                    start = (uint16_t) (start + (uint16_t) (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 4U)));
                }

                i   = (uint8_t) (i + (*ptr));
                ptr = (uint8_t *) ((uint32_t) ptr + (*ptr));
                break;
            }

            /* Endpoint */
            case USB_DT_ENDPOINT:
            {
                if (j < numbers)
                {
                    ep = (uint16_t) *(uint8_t *) ((uint32_t) ptr + (uint32_t) 2U);
                    if (USB_EP_IN == (ep & USB_EP_DIRMASK))
                    {
                        dir = 1;       /* IN */
                    }
                    else
                    {
                        dir = 0;       /* OUT */
                    }

                    ep &= (uint16_t) 0x0f;
                    g_usb_pstd_eptbl_index[dir][ep] = (uint8_t) (start + j);
                    ++j;
                }

                i   = (uint16_t) (i + (*ptr));
                ptr = (uint8_t *) ((uint32_t) ptr + (*ptr));
                break;
            }

            /* Device */
            case USB_DT_DEVICE:

            /* Continue */
            /* Configuration */
            case USB_DT_CONFIGURATION:

            /* Continue */
            /* String */
            case USB_DT_STRING:

            /* Continue */
            /* Class, Vendor, else */
            default:
            {
                i   = (uint16_t) (i + (*ptr));
                ptr = (uint8_t *) ((uint32_t) ptr + (*ptr));
                break;
            }
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_set_eptbl_index
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_chk_remote
 * Description     : Check if the RemoteWakeUp bit for the configuration descriptor is set.
 * Arguments       : none
 * Return value    : uint16_t : remote wakeup status (TRUE/FALSE).
 ******************************************************************************/
uint16_t usb_pstd_chk_remote (void)
{
    uint8_t atr;

    if (0 == g_usb_pstd_config_num)
    {
        return USB_FALSE;
    }

    /* Get Configuration Descriptor - bmAttributes */
    atr = *(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint32_t) 7U);

    /* Remote WakeUp check(= D5) */
    if (USB_CF_RWUPON == (atr & USB_CF_RWUPON))
    {
        return USB_TRUE;
    }

    return USB_FALSE;
}

/******************************************************************************
 * End of function usb_pstd_chk_remote
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_get_current_power
 * Description     : Find out how the peripheral is powered by looking at the con-
 *               : figuration descriptor.
 * Arguments       : none
 * Return value    : uint8_t : Current power means; self-powered or bus-powered
 *               : (GS_SELFPOWERD/GS_BUSPOWERD).
 ******************************************************************************/
uint8_t usb_pstd_get_current_power (void)
{
    /*
     * Please answer the currently power of your system.
     */

    uint8_t tmp;
    uint8_t currentpower;

    /* Standard configuration descriptor */
    tmp = *(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint32_t) 7U);
    if (USB_CF_SELFP == (tmp & USB_CF_SELFP))
    {
        /* Self Powered */
        currentpower = USB_GS_SELFPOWERD;
    }
    else
    {
        /* Bus Powered */
        currentpower = USB_GS_BUSPOWERD;
    }

    /* Check currently powered */

    return currentpower;
}

/******************************************************************************
 * End of function usb_pstd_get_current_power
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_fifo_to_buf
 * Description     : Request readout from USB FIFO to buffer and process depending
 *               : on status; read complete or reading.
 * Arguments       : uint16_t pipe     : Pipe no.
 *               : uint16_t useport  : FIFO select(USB_CUSE,USB_DMA0,....)
 * Return value    : none
 ******************************************************************************/
void usb_pstd_fifo_to_buf (uint16_t pipe, uint16_t useport, usb_utr_t * p_utr)
{
    uint16_t end_flag = USB_ERROR;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    end_flag = usb_pstd_read_data(pipe, useport, p_utr);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_READING:
        {
            /* Continue of data read */
            break;
        }

        case USB_READEND:
        {
            /* End of data read */
            usb_pstd_data_end(pipe, (uint16_t) USB_DATA_OK, p_utr);
            break;
        }

        case USB_READSHRT:
        {
            /* End of data read */
            usb_pstd_data_end(pipe, (uint16_t) USB_DATA_SHT, p_utr);
            break;
        }

        case USB_READOVER:
        {
            /* Buffer over */
            USB_PRINTF1("### Receive data over PIPE%d\n", pipe);
            usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_OVR, p_utr);
            break;
        }

        case USB_FIFOERROR:
        {
            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_FIFO_ERR, p_utr);
            break;
        }

        default:
        {
            usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_ERR, p_utr);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_fifo_to_buf
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_buf_to_fifo
 * Description     : Set USB registers as required to write from data buffer to USB
 * : FIFO, to have USB FIFO to write data to bus.
 * Arguments       : uint16_t pipe     : Pipe no.
 *               : uint16_t useport  : Port no.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_buf_to_fifo (uint16_t pipe, uint16_t useport, usb_utr_t * p_utr)
{
    uint16_t end_flag;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(p_utr, pipe);

    end_flag = usb_pstd_write_data(pipe, useport, p_utr);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_WRITING:
        {
            /* Continue of data write */
            /* Enable Ready Interrupt */
            hw_usb_set_brdyenb(p_utr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(p_utr, pipe);
            break;
        }

        case USB_WRITEEND:

        /* End of data write */
        /* continue */
        case USB_WRITESHRT:
        {
            /* End of data write */
            /* Enable Empty Interrupt */
            hw_usb_set_bempenb(p_utr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(p_utr, pipe);
            break;
        }

        case USB_FIFOERROR:
        {
            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_FIFO_ERR, p_utr);
            break;
        }

        default:
        {
            usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_ERR, p_utr);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_buf_to_fifo
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_pstd_transfer_start
 * Description     : Transfer the data of each pipe
 *               : Request PCD to transfer data, and the PCD transfers the data
 *               : based on the transfer information stored in ptr
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : usb_er_t       : Error info.
 ******************************************************************************/
usb_er_t usb_pstd_transfer_start (usb_utr_t * ptr)
{
    usb_er_t err;
    uint16_t pipenum;
  #if (BSP_CFG_RTOS != 0)
    usb_utr_t * p_tran_data;
  #endif                               /* (BSP_CFG_RTOS != 0) */

  #if (BSP_CFG_RTOS == 1)
   #if (defined(USB_CFG_PCDC_USE) || defined(USB_CFG_PPRN_USE))
    UINT           status;
    CHAR         * p_sem_name;
    ULONG          cur_sem_count_value;
    TX_THREAD    * p_suspend_thread;
    ULONG          suspend_t_count;
    TX_SEMAPHORE * p_next_sem;
   #endif                              /* (defined(USB_CFG_PCDC_USE) ||  defined(USB_CFG_PPRN_USE) */
  #endif                               /* #if (BSP_CFG_RTOS == 1) */

    pipenum = ptr->keyword;
    if (USB_PIPE0 == pipenum)
    {
        USB_PRINTF0("### usb_pstd_transfer_start PIPE0 is not support\n");

        return USB_ERROR;
    }

  #if (BSP_CFG_RTOS == 0)
    if (USB_NULL != g_p_usb_pstd_pipe[pipenum])
    {
        /* Get PIPE TYPE */
        if (USB_TYPFIELD_ISO != usb_cstd_get_pipe_type(ptr, pipenum))
        {
            USB_PRINTF1("### usb_pstd_transfer_start overlaps %d\n", pipenum);

            return USB_QOVR;
        }
    }

    /* Check state (Configured) */
    if (USB_TRUE != usb_pstd_chk_configured(ptr))
    {
        USB_PRINTF0("### usb_pstd_transfer_start not configured\n");

        return USB_ERROR;
    }

    err = usb_pstd_set_submitutr(ptr);
  #else                                /* (BSP_CFG_RTOS == 0) */
   #if (BSP_CFG_RTOS == 1)             /* BSP_CFG_RTOS == 0 */
    ptr->msghead = (usb_mh_t) USB_NULL;
    ptr->msginfo = USB_MSG_PCD_SUBMITUTR;

    err = USB_PGET_BLK(1, &p_tran_data);
    if (TX_SUCCESS != err)
    {
        return USB_ERROR;
    }

   #elif (BSP_CFG_RTOS == 2)           /* BSP_CFG_RTOS == 0 */
    ptr->msghead = (usb_mh_t) USB_NULL;
    ptr->msginfo = USB_MSG_PCD_SUBMITUTR;

    p_tran_data = (usb_utr_t *) pvPortMalloc(sizeof(usb_utr_t));
    if (NULL == p_tran_data)
    {
        return USB_ERROR;
    }
   #endif                              /* (BSP_CFG_RTOS == 0) */

    *p_tran_data = *ptr;
   #if (BSP_CFG_RTOS == 1)
    p_tran_data->cur_task_hdl              = tx_thread_identify();
    g_usb_peri_usbx_is_fifo_error[pipenum] = USB_NO;
    #if defined(USB_CFG_PCDC_USE) && defined(USB_CFG_PMSC_USE)
    if ((USB_CFG_PCDC_BULK_IN == pipenum) || (USB_CFG_PCDC_BULK_OUT == pipenum))
    {
        status = tx_semaphore_info_get(&g_usb_peri_usbx_sem[pipenum],
                                       &p_sem_name,
                                       &cur_sem_count_value,
                                       &p_suspend_thread,
                                       &suspend_t_count,
                                       &p_next_sem);
        if (TX_SUCCESS == status)
        {
            /* Check IOCTL timeout value has been set to the transfer request
             * and check if transfer request semaphore count value is got
             * incremented, due to the previous transfer request timeout.
             * If both conditions true, then clear the previous transfer request semaphore,
             * before starting current transfer request. */
            if ((TX_WAIT_FOREVER != ptr->timeout) && (cur_sem_count_value > 0))
            {
                /* Clear the previous transfer request semaphore,if timeout has occurred. */
                tx_semaphore_get(&g_usb_peri_usbx_sem[pipenum], TX_NO_WAIT);
            }
        }
    }

    #elif (defined(USB_CFG_PCDC_USE) || defined(USB_CFG_PPRN_USE))
    status = tx_semaphore_info_get(&g_usb_peri_usbx_sem[pipenum],
                                   &p_sem_name,
                                   &cur_sem_count_value,
                                   &p_suspend_thread,
                                   &suspend_t_count,
                                   &p_next_sem);
    if (TX_SUCCESS == status)
    {
        /* Check IOCTL timeout value has been set to the transfer request
         * and check if transfer request semaphore count value is got
         * incremented, due to the previous transfer request timeout.
         * If both conditions true, then clear the previous transfer request semaphore,
         * before starting current transfer request. */
        if ((TX_WAIT_FOREVER != ptr->timeout) && (cur_sem_count_value > 0))
        {
            /* Clear the previous transfer request semaphore,if timeout has occurred. */
            tx_semaphore_get(&g_usb_peri_usbx_sem[pipenum], TX_NO_WAIT);
        }
    }
    #endif                             /* defined(USB_CFG_PCDC_USE) || defined(USB_CFG_PPRN_USE) */
   #elif (BSP_CFG_RTOS == 2)           /* (BSP_CFG_RTOS == 1) */
    p_tran_data->cur_task_hdl = xTaskGetCurrentTaskHandle();
   #endif                              /* (BSP_CFG_RTOS == 1) */

    /* Send message */
    err = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t *) p_tran_data);
    if (USB_OK != err)
    {
   #if (BSP_CFG_RTOS == 1)
        USB_REL_BLK(1, p_tran_data);
   #elif (BSP_CFG_RTOS == 2)           /* (BSP_CFG_RTOS == 1) */
        vPortFree(p_tran_data);
   #endif                              /* (BSP_CFG_RTOS == 1) */
    }

   #if (BSP_CFG_RTOS == 1)
    if (0 != pipenum)
    {
    #if defined(USB_CFG_PCDC_USE) && defined(USB_CFG_PMSC_USE)
        if ((USB_CFG_PCDC_BULK_IN == pipenum) || (USB_CFG_PCDC_BULK_OUT == pipenum))
        {
            UINT tx_err;

            /* Wait for the transfer request semaphore to wake up */
            tx_err = tx_semaphore_get(&g_usb_peri_usbx_sem[pipenum], p_tran_data->timeout);

            /* Check the error status code, and if this transfer is not successful end this
             * transfer and return error code to the caller function.*/
            if (TX_SUCCESS != tx_err)
            {
                /* Set transfer request timeout status */
                p_tran_data->is_timeout = USB_YES;

                /* Once Time out occurs for this transfer request, terminate data transmission
                 * or reception. */
                usb_pstd_forced_termination(pipenum, (uint16_t) USB_DATA_STOP, p_tran_data);
                USB_REL_BLK(1, p_tran_data);
                err = USB_ERR_TMOUT;
            }
            else
            {
                /* Check for the FIFO error flag status */
                if (USB_YES == g_usb_peri_usbx_is_fifo_error[pipenum])
                {
                    g_usb_peri_usbx_is_fifo_error[pipenum] = USB_NO;
                    err = USB_ERR_FIFO_ACCESS;
                }
            }
        }
        else
        {
            tx_semaphore_get(&g_usb_peri_usbx_sem[pipenum], TX_WAIT_FOREVER);
        }

    #elif defined(USB_CFG_PPRN_USE)
        UINT tx_err;
        tx_err = tx_semaphore_get(&g_usb_peri_usbx_sem[pipenum], p_tran_data->timeout);
        if (TX_SUCCESS != tx_err)
        {
            p_tran_data->is_timeout = USB_YES;
            err = usb_pstd_transfer_end(p_tran_data, pipenum);
            if (USB_OK != err)
            {
                USB_REL_BLK(1, p_tran_data);
            }

            err = USB_ERR_TMOUT;
        }
        else
        {
            if (USB_YES == g_usb_peri_usbx_is_fifo_error[pipenum])
            {
                g_usb_peri_usbx_is_fifo_error[pipenum] = USB_NO;
                err = USB_ERR_FIFO_ACCESS;
            }
        }

    #elif defined(USB_CFG_PCDC_USE)
        UINT tx_err;

        /* Wait for the transfer request semaphore to wake up */
        tx_err = tx_semaphore_get(&g_usb_peri_usbx_sem[pipenum], p_tran_data->timeout);

        /* Check the error status code, and if this transfer is not successful end this
         * transfer and return error code to the caller function.*/
        if (TX_SUCCESS != tx_err)
        {
            /* Set transfer request timeout status */
            p_tran_data->is_timeout = USB_YES;

            /* Once Time out occurs for this transfer request, terminate data transmission
             * or reception. */
            usb_pstd_forced_termination(pipenum, (uint16_t) USB_DATA_STOP, p_tran_data);
            USB_REL_BLK(1, p_tran_data);
            err = USB_ERR_TMOUT;
        }
        else
        {
            /* Check for the FIFO error flag status */
            if (USB_YES == g_usb_peri_usbx_is_fifo_error[pipenum])
            {
                g_usb_peri_usbx_is_fifo_error[pipenum] = USB_NO;
                err = USB_ERR_FIFO_ACCESS;
            }
        }

    #else
        tx_semaphore_get(&g_usb_peri_usbx_sem[pipenum], TX_WAIT_FOREVER);
    #endif                             /* defined(USB_CFG_PPRN_USE) */
    }
   #endif                              /* #if (BSP_CFG_RTOS == 1) */
  #endif                               /* (BSP_CFG_RTOS == 0) */

    return err;
}

/******************************************************************************
 * End of function usb_pstd_transfer_start
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_transfer_end
 * Description     : Force termination of data transfer of specified pipe. Request
 *               : PCD to force termination data transfer,
 *               : and the PCD forced-terminates data transfer.
 * Arguments       : uint16_t pipe     : Pipe number.
 * Return value    : usb_er_t          : Error info.
 ******************************************************************************/
usb_er_t usb_pstd_transfer_end (usb_utr_t * p_utr, uint16_t pipe)
{
    usb_er_t err = USB_OK;
  #if (BSP_CFG_RTOS != 0)
    usb_utr_t utr;
  #endif                               /* (BSP_CFG_RTOS != 0) */

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR;              /* Error */
    }

    if (USB_NULL == g_p_usb_pstd_pipe[pipe])
    {
        USB_PRINTF0("### usb_pstd_transfer_end overlaps\n");
        err = USB_ERROR;
    }
    else
    {
  #if (BSP_CFG_RTOS == 0)
        usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_STOP, p_utr);
  #else                                /* BSP_CFG_RTOS == 0 */
        utr.msghead = (usb_mh_t) USB_NULL;
        utr.msginfo = USB_MSG_PCD_TRANSEND1;
        utr.keyword = pipe;
        utr.ip      = p_utr->ip;

        /* Send message */
        err = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t *) &utr);
  #endif                               /* (BSP_CFG_RTOS == 0) */
    }

    return err;
}

/******************************************************************************
 * End of function usb_pstd_transfer_end
 ******************************************************************************/
 #endif                                /* (USB_UT_MODE == 0) */

 #if   (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_pstd_change_device_state
 * Description     : Change USB Device to the status specified by argument
 * Arguments       : uint16_t state            : New device status.
 *               : uint16_t keyword          : Pipe number etc.
 *               : usb_cb_t complete         : Callback function.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_change_device_state (uint16_t state, uint16_t keyword, usb_cb_t complete, usb_utr_t * p_utr)
{
    uint16_t pipenum;
  #if (BSP_CFG_RTOS != 0)
    static usb_utr_t utr;
    uint16_t         err;
  #endif                               /* (BSP_CFG_RTOS != 0) */

    pipenum = keyword;
    switch (state)
    {
        case USB_DO_STALL:
        {
            usb_pstd_set_stall(pipenum, p_utr);
            g_usb_pstd_stall_pipe[pipenum] = USB_TRUE;
            g_usb_pstd_stall_cb            = complete;
            break;
        }

        case USB_DO_REMOTEWAKEUP:
        {
  #if (BSP_CFG_RTOS == 0)
            usb_pstd_self_clock(p_utr->ip);
            usb_pstd_remote_wakeup(p_utr->ip);
  #else                                /* BSP_CFG_RTOS == 0 */
            utr.msghead = (usb_mh_t) USB_NULL;
            utr.msginfo = USB_MSG_PCD_REMOTEWAKEUP;
            utr.ip      = p_utr->ip;

            /* Send message */
            err = (uint16_t) USB_SND_MSG(USB_PCD_MBX, (usb_msg_t *) &utr);
            if (USB_OK != err)
            {
                g_usb_pstd_remote_wakeup_state = USB_ERROR;
            }
  #endif                               /* BSP_CFG_RTOS == 0 */
            break;
        }

        case USB_MSG_PCD_DP_ENABLE:
        {
            hw_usb_pset_dprpu(p_utr->ip);
            break;
        }

        case USB_MSG_PCD_DP_DISABLE:
        {
            hw_usb_pclear_dprpu(p_utr->ip);
            break;
        }

        default:
        {
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_change_device_state
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_pstd_driver_registration
 * Description     : Register pipe information table, descriptor information table,
 *               : callback function, etc. This info is specified by the data in
 *               : the structure usb_pcdreg_t.
 * Arguments       : usb_pcdreg_t *registinfo     : Class driver structure.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_driver_registration (usb_pcdreg_t * registinfo)
{
    usb_pcdreg_t * driver;

    driver = &g_usb_pstd_driver;

    driver->p_devicetbl = registinfo->p_devicetbl; /* Device descriptor table address */
    driver->p_qualitbl  = registinfo->p_qualitbl;  /* Qualifier descriptor table address */
    driver->p_configtbl = registinfo->p_configtbl; /* Configuration descriptor table address */
    driver->p_othertbl  = registinfo->p_othertbl;  /* Other configuration descriptor table address */
    driver->p_stringtbl = registinfo->p_stringtbl; /* String descriptor table address */
    driver->devdefault  = registinfo->devdefault;  /* Device default */
    driver->devconfig   = registinfo->devconfig;   /* Device configured */
    driver->devdetach   = registinfo->devdetach;   /* Device detach */
    driver->devsuspend  = registinfo->devsuspend;  /* Device suspend */
    driver->devresume   = registinfo->devresume;   /* Device resume */
    driver->interface   = registinfo->interface;   /* Interfaced change */
    driver->ctrltrans   = registinfo->ctrltrans;   /* Control transfer */
    driver->num_string  = registinfo->num_string;  /* String descriptor number */
}

/******************************************************************************
 * End of function  usb_pstd_driver_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_driver_release
 * Description     : Clear the information registered in the structure usb_pcdreg_t.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_driver_release (void)
{
    usb_pcdreg_t * driver;

    driver              = &g_usb_pstd_driver;
    driver->p_devicetbl = (uint8_t *) 0U;           /* Device descriptor table address */
    driver->p_qualitbl  = (uint8_t *) 0U;           /* Qualifier descriptor table address */
    driver->p_configtbl = (uint8_t *) 0U;           /* Configuration descriptor table address */
    driver->p_othertbl  = (uint8_t *) 0U;           /* Other configuration descriptor table address */
    driver->p_stringtbl = (uint8_t **) 0U;          /* String descriptor table address */
    driver->devdefault  = &usb_pstd_dummy_function; /* Device default */
    driver->devconfig   = &usb_pstd_dummy_function; /* Device configured */
    driver->devdetach   = &usb_pstd_dummy_function; /* Device detach */
    driver->devsuspend  = &usb_pstd_dummy_function; /* Device suspend */
    driver->devresume   = &usb_pstd_dummy_function; /* Device resume */
    driver->interface   = &usb_pstd_dummy_function; /* Interfaced change */
    driver->ctrltrans   = &usb_pstd_dummy_trn;      /* Control transfer */
}/* End of function usb_pstd_driver_release() */

/******************************************************************************
 * Function Name   : usb_pstd_dummy_function
 * Description     : dummy function
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_pstd_dummy_function (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    /* Dummy function */
    FSP_PARAMETER_NOT_USED(*ptr);
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);
}

/******************************************************************************
 * End of function usb_pstd_dummy_function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_dummy_trn
 * Description     : Class request processing for dummy
 * Arguments       : usb_setup_t *preq  ; Class request information
 * : uint16_t ctsq        ; Control Stage
 * Return value    : none
 ******************************************************************************/
void usb_pstd_dummy_trn (usb_setup_t * preq, uint16_t ctsq, usb_utr_t * p_utr)
{
    /* Dummy function */
    FSP_PARAMETER_NOT_USED(*preq);
    FSP_PARAMETER_NOT_USED(ctsq);
    FSP_PARAMETER_NOT_USED(*p_utr);
}                                      /* End of function usb_pstd_dummy_trn */

/******************************************************************************
 * Function Name   : usb_pstd_device_information
 * Description     : Get USB Device information such as USB Device status and con-
 *              : figuration No. etc.
 * Arguments      : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
 *              : uint16_t *tbl   : Device information storage pointer TBL. This
 *              :                   pointer is used to provide the caller with the device's sta-
 *              :                   tus, speed, configuration and interface number, and the value
 *              :                   of the remote wakeup flag.
 * Return value    : none
 ******************************************************************************/
void usb_pstd_device_information (usb_utr_t * ptr, uint16_t * tbl)
{
    /* Device status */
    tbl[0] = hw_usb_read_intsts(ptr->ip) & (uint16_t) (USB_VBSTS | USB_DVSQ);

    /* Speed */
    tbl[1] = usb_cstd_port_speed(ptr);

    /* Configuration number */
    tbl[2] = g_usb_pstd_config_num;

    /* Interface number */
    tbl[3] = usb_pstd_get_interface_num();

    /* Remote Wakeup Flag */
    tbl[4] = g_usb_pstd_remote_wakeup;
}                                      /* End of function usb_pstd_device_information() */

/******************************************************************************
 * Function Name   : usb_pstd_set_stall_clr_feature
 * Description     : Set pipe stall request
 * Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure.
 *              : usb_cb_t  complete    : callback function
 *              : uint16_t  pipe        : pipe number
 * Return value    : usb_er_t              : Error Info
 ******************************************************************************/
usb_er_t usb_pstd_set_stall_clr_feature (usb_utr_t * ptr, usb_cb_t complete, uint16_t pipe)
{
    FSP_PARAMETER_NOT_USED(*ptr);

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR;              /* Error */
    }

    usb_pstd_change_device_state(USB_DO_STALL, pipe, complete, ptr);

    return USB_OK;
}

/******************************************************************************
 * End of function usb_pstd_set_stall_clr_feature
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_peri_registration
 * Description     : Registration of peripheral Devices Class Driver
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_peri_registration (usb_instance_ctrl_t * ctrl, usb_cfg_t const * const cfg)
{
    usb_pcdreg_t pdriver;

    FSP_PARAMETER_NOT_USED(*ctrl);

    /* pdriver registration */
    pdriver.p_devicetbl = cfg->p_usb_reg->p_device;              /* Device descriptor Table address */
    pdriver.p_qualitbl  = cfg->p_usb_reg->p_qualifier;           /* Qualifier descriptor Table address */
    if (USB_NULL == cfg->p_usb_reg->p_config_f)
    {
        pdriver.p_configtbl = cfg->p_usb_reg->p_config_h;        /* Configuration descriptor Table address */
    }
    else
    {
        pdriver.p_configtbl = cfg->p_usb_reg->p_config_f;        /* Configuration descriptor Table address */
    }

    pdriver.p_othertbl  = cfg->p_usb_reg->p_config_h;            /* Other configuration descriptor Table address */
    pdriver.p_stringtbl = cfg->p_usb_reg->p_string;              /* String descriptor Table address */
    pdriver.num_string  = cfg->p_usb_reg->num_string;            /* Num entry String descriptor */

    pdriver.devdefault = &usb_peri_devdefault;                   /* Device default */
    pdriver.devconfig  = &usb_peri_configured;                   /* Device configuered */
    pdriver.devdetach  = &usb_peri_detach;                       /* Device detach */
    pdriver.devsuspend = (usb_cb_t) &usb_peri_suspended;         /* Device suspend */
    pdriver.devresume  = &usb_peri_resume;                       /* Device resume */
    pdriver.interface  = &usb_peri_interface;                    /* Interface changed */
    pdriver.ctrltrans  = (usb_cb_trn_t) &usb_peri_class_request; /* Control Transfer */

    usb_pstd_driver_registration(&pdriver);
} /* End of function usb_peri_registration() */

/******************************************************************************
 * Function Name   : usb_peri_devdefault
 * Description     : Descriptor change
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t mode        ; Speed mode
 *               : uint16_t data2       ; BC Port Detect Result
 * Return value    : none
 ******************************************************************************/
void usb_peri_devdefault (usb_utr_t * ptr, uint16_t mode, uint16_t data2)
{
    uint8_t * ptable;
    uint16_t  len;

    FSP_PARAMETER_NOT_USED(data2);

 #if (defined(USB_CFG_PCDC_USE) | defined(USB_CFG_PHID_USE) | defined(USB_CFG_PPRN_USE))
    usb_instance_ctrl_t ctrl;
  #if (USB_CFG_DMA == USB_CFG_ENABLE)
    ctrl.p_transfer_rx = ptr->p_transfer_rx;
    ctrl.p_transfer_tx = ptr->p_transfer_tx;
  #endif
 #endif

    usb_peri_detach(ptr, USB_DEFAULT, USB_NULL);

    /* Connect Speed = Hi-Speed? */
    if (USB_HSCONNECT == mode)
    {
        ptable = g_usb_pstd_driver.p_othertbl;

        /* Set Descriptor type.  */
        /* Hi-Speed Mode */
        if (USB_NULL != g_usb_pstd_driver.p_configtbl)
        {
            g_usb_pstd_driver.p_configtbl[1] = USB_DT_OTHER_SPEED_CONF;
        }

        if (USB_NULL != g_usb_pstd_driver.p_othertbl)
        {
            g_usb_pstd_driver.p_othertbl[1] = USB_DT_CONFIGURATION;
        }
    }
    else
    {
        ptable = g_usb_pstd_driver.p_configtbl;

        /* Set Descriptor type. */
        /* Full-Speed Mode */
        if (USB_NULL != g_usb_pstd_driver.p_configtbl)
        {
            g_usb_pstd_driver.p_configtbl[1] = USB_DT_CONFIGURATION;
        }

        if (USB_NULL != g_usb_pstd_driver.p_othertbl)
        {
            g_usb_pstd_driver.p_othertbl[1] = USB_DT_OTHER_SPEED_CONF;
        }
    }

    if (USB_NULL == ptable)
    {
        while (1)
        {
            /* Error */
        }
    }

    len = (uint16_t) (*(uint8_t *) ((uint32_t) ptable + (uint32_t) 3));
    len = (uint16_t) (len << 8);
    len = (uint16_t) (len + (uint16_t) (*(uint8_t *) ((uint32_t) ptable + (uint32_t) 2)));

    usb_pstd_clr_pipe_table(ptr->ip);
    usb_peri_pipe_info(ptable, mode, len, ptr);

 #if (defined(USB_CFG_PCDC_USE) | defined(USB_CFG_PHID_USE) | defined(USB_CFG_PPRN_USE))
    ctrl.module_number = ptr->ip;
    usb_set_event(USB_STATUS_DEFAULT, &ctrl);
 #endif
}                                      /* End of function usb_peri_devdefault() */

 #define NUM_OF_INTERFACE    (8U)
uint8_t g_usb_paud_iso_pipe[NUM_OF_INTERFACE];

/******************************************************************************
 * Function Name   : usb_peri_pipe_info
 * Description     : Pipe Information check and EP Table Set
 * Arguments       : uint8_t *table   : Check Start Descriptor address
 *               : uint16_t speed   : Device connected speed
 *               : uint16_t length  : Configuration Descriptor Length
 * Return value    : uint16_t : USB_E_OK / USB_E_ERROR
 ******************************************************************************/
uint16_t usb_peri_pipe_info (uint8_t * table, uint16_t speed, uint16_t length, usb_utr_t * p_utr)
{
    uint16_t ofdsc;
    uint16_t retval = USB_ERROR;
    uint8_t  pipe_no;
    uint8_t  class_info = 0;
 #ifdef  USB_CFG_PAUD_USE
    uint8_t interface_num = 0;
 #endif                                // USB_CFG_PAUD_USE

    FSP_PARAMETER_NOT_USED(speed);

    /* Check Endpoint Descriptor */
    ofdsc = table[0];

    /* WAIT_LOOP */
    while (ofdsc < length)
    {
        if (USB_DT_INTERFACE == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
        {
            class_info = table[ofdsc + USB_IF_B_INTERFACECLASS];
 #ifdef  USB_CFG_PAUD_USE
            interface_num = table[ofdsc + USB_IF_B_INTERFACENUMBER];
 #endif                                // USB_CFG_PAUD_USE
        }

        /* Endpoint Descriptor */
        if (USB_DT_ENDPOINT == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
        {
            /* EP Table pipe Information set */
            pipe_no = usb_pstd_set_pipe_table(&table[ofdsc], p_utr, class_info);
            if (USB_NULL != pipe_no)
            {
                retval = USB_OK;
 #ifdef  USB_CFG_PAUD_USE
                g_usb_paud_iso_pipe[interface_num] = pipe_no;
 #endif                                // USB_CFG_PAUD_USE
            }
        }

        ofdsc = (uint16_t) (ofdsc + table[ofdsc]);
    }

    return retval;
}                                      /* End of function usb_peri_pipe_info() */

/******************************************************************************
 * Function Name   : usb_peri_configured
 * Description     : Peripheral Devices Class open function
 * Arguments       : usb_utr_t    *ptr        : Not used
 *               : uint16_t     data1       : Not used
 *               : uint16_t     data2       : Not used
 * Return value    : none
 ******************************************************************************/
void usb_peri_configured (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    FSP_PARAMETER_NOT_USED(*ptr);
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    g_usb_peri_connected = USB_TRUE;

    ctrl.module_number = ptr->ip;
 #if (USB_CFG_DMA == USB_CFG_ENABLE)
    ctrl.p_transfer_rx = ptr->p_transfer_rx;
    ctrl.p_transfer_tx = ptr->p_transfer_tx;
 #endif
    usb_set_event(USB_STATUS_CONFIGURED, &ctrl);

 #if defined(USB_CFG_PMSC_USE)
  #if (BSP_CFG_RTOS != 1)
    usb_pmsc_receive_cbw(ptr);
  #endif                               /* (BSP_CFG_RTOS != 1) */
 #endif
}                                      /* End of function usb_configured() */

/******************************************************************************
 * Function Name   : usb_peri_detach
 * Description     : Peripheral Devices Class close function
 * Arguments       : usb_utr_t    *ptr              : Not used
 *                 : uint16_t     usb_state         : USB state
 *                 : uint16_t     data2             : Not used
 * Return value    : none
 ******************************************************************************/
void usb_peri_detach (usb_utr_t * ptr, uint16_t usb_state, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
 #if (BSP_CFG_RTOS == 1)
    uint8_t  pipe;
    uint16_t intsts;
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

    FSP_PARAMETER_NOT_USED(*ptr);
    FSP_PARAMETER_NOT_USED(data2);

 #if (BSP_CFG_RTOS == 1)
    intsts = hw_usb_read_intsts(ptr->ip);
    if (USB_VBSTS == (intsts & USB_VBSTS))
    {
        /* When doing the warm start PC(USB_Host), PC sends the USB Reset.                          *
         * The following code is needed to release the waiting status of the semaphore waiting task *
         * before doing the warm start.                                                             */
        if (USB_DEFAULT == usb_state)
        {
            for (pipe = USB_MIN_PIPE_NO; pipe < (USB_MAX_PIPE_NO + 1); pipe++)
            {
                g_usb_peri_usbx_is_detach[pipe] = USB_NO;
                tx_semaphore_put(&g_usb_peri_usbx_sem[pipe]);
                tx_semaphore_delete(&g_usb_peri_usbx_sem[pipe]);
            }

            if (USB_YES == g_usb_peri_usbx_is_configured[ptr->ip])
            {
                /* The "ux_device_stack_disconnect" function must be not executed when attaching USB device to USB Host. */
                /* Because the unnecessary detaching event is notfied to the application program when attaching USB device to USB Host. */
                /* But, when doing the warm start PC, the "ux_device_stack_disconnect" function must be executed. */
                _ux_device_stack_disconnect();
            }
        }
    }

 #else                                 /* #if (BSP_CFG_RTOS == 1) */
    FSP_PARAMETER_NOT_USED(usb_state);
 #endif /* #if (BSP_CFG_RTOS == 1) */

    if (USB_TRUE == g_usb_peri_connected)
    {
        g_usb_peri_connected = USB_FALSE;

        ctrl.module_number = ptr->ip;
        usb_set_event(USB_STATUS_DETACH, &ctrl);
    }
}                                      /* End of function usb_peri_detach() */

/******************************************************************************
 * Function Name   : usb_peri_suspended
 * Description     : Peripheral Devices Class suspended function
 * Arguments       : usb_utr_t    *ptr        : Not used
 *               : uint16_t     data1       : Not used
 *               : uint16_t     data2       : Not used
 * Return value    : none
 ******************************************************************************/
void usb_peri_suspended (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    ctrl.module_number = ptr->ip;
    usb_set_event(USB_STATUS_SUSPEND, &ctrl);

 #if BSP_CFG_RTOS == 1
    if (UX_NULL != _ux_system_slave->ux_system_slave_change_function)
    {
        _ux_system_slave->ux_system_slave_change_function(UX_DEVICE_SUSPENDED);
    }
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
}                                      /* End of function usb_suspended() */

/******************************************************************************
 * Function Name   : usb_peri_resume
 * Description     : Peripheral Devices Class resume function
 * Arguments       : usb_utr_t    *ptr        : Not used
 *               : uint16_t     data1       : Not used
 *               : uint16_t     data2       : Not used
 * Return value    : none
 ******************************************************************************/
void usb_peri_resume (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    ctrl.module_number = ptr->ip;
 #if (USB_CFG_DMA == USB_CFG_ENABLE)
    ctrl.p_transfer_rx = ptr->p_transfer_rx;
    ctrl.p_transfer_tx = ptr->p_transfer_tx;
 #endif
 #if (BSP_CFG_RTOS != 0)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
 #endif                                /* (BSP_CFG_RTOS != 0) */

    usb_set_event(USB_STATUS_RESUME, &ctrl);

 #if BSP_CFG_RTOS == 1
    if (UX_NULL != _ux_system_slave->ux_system_slave_change_function)
    {
        _ux_system_slave->ux_system_slave_change_function(UX_DEVICE_RESUMED);
    }
 #endif
}                                      /* End of function usb_peri_resume() */

/******************************************************************************
 * Function Name   : usb_peri_interface
 * Description     : Peripheral Devices Class set interface function
 * Arguments       : usb_utr_t    *ptr        : Not used
 *               : uint16_t     data1       : Not used
 *               : uint16_t     data2       : Not used
 * Return value    : none
 ******************************************************************************/
void usb_peri_interface (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    FSP_PARAMETER_NOT_USED(*ptr);
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

 #if defined(USB_CFG_PMSC_USE)
  #if (BSP_CFG_RTOS != 1)
    usb_pmsc_receive_cbw(ptr);
  #endif                               /* (BSP_CFG_RTOS != 1) */
 #else                                 /* defined(USB_CFG_PMSC_USE) */
    /* Non processing */
 #endif                                /* defined(USB_CFG_PMSC_USE) */
}                                      /* End of function usb_peri_interface() */

 #if defined(USB_CFG_PVND_USE)

/******************************************************************************
 * Function Name   : usb_pvnd_read_complete
 * Description     : CallBack Function
 * Argument        : usb_utr_t *mess           : Transfer result message
 * Return          : none
 ******************************************************************************/
void usb_pvnd_read_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;

    usb_instance_ctrl_t ctrl;

    /* Set Receive data length */
    ctrl.data_size = mess->read_req_len - mess->tranlen;
    ctrl.pipe      = (uint8_t) mess->keyword; /* Pipe number setting */
    ctrl.type      = USB_CLASS_PVND;          /* Device class setting  */
  #if (BSP_CFG_RTOS != 0)
    ctrl.p_data = (void *) mess->cur_task_hdl;
  #endif /* (BSP_CFG_RTOS != 0) */
    switch (mess->status)
    {
        case USB_DATA_OK:
        {
            ctrl.status = FSP_SUCCESS;
            break;
        }

        case USB_DATA_SHT:
        {
            ctrl.status = FSP_ERR_USB_SIZE_SHORT;
            break;
        }

        case USB_DATA_OVR:
        {
            ctrl.status = FSP_ERR_USB_SIZE_OVER;
            break;
        }

        case USB_DATA_ERR:
        default:
        {
            ctrl.status = FSP_ERR_USB_FAILED;
            break;
        }
    }

    ctrl.module_number = mess->ip;
    usb_set_event(USB_STATUS_READ_COMPLETE, &ctrl);
}                                      /* End of function usb_pvnd_read_complete() */

/******************************************************************************
 * Function Name   : usb_pvnd_write_complete
 * Description     : CallBack Function
 * Argument        : usb_utr_t *mess           : Transfer result message
 * Return          : none
 ******************************************************************************/
void usb_pvnd_write_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;

    usb_instance_ctrl_t ctrl;

    ctrl.pipe = (uint8_t) mess->keyword; /* Pipe number setting */
    ctrl.type = USB_CLASS_PVND;          /* CDC Control class  */
    if (USB_DATA_NONE == mess->status)
    {
        ctrl.status = FSP_SUCCESS;
    }
    else
    {
        ctrl.status = FSP_ERR_USB_FAILED;
    }

    ctrl.module_number = mess->ip;
  #if (BSP_CFG_RTOS != 0)
    ctrl.p_data = (void *) mess->cur_task_hdl;
  #endif                               /* (BSP_CFG_RTOS != 0) */
    usb_set_event(USB_STATUS_WRITE_COMPLETE, &ctrl);
} /* End of function usb_pvnd_write_complete() */

 #endif                                /* defined(USB_CFG_PVND_USE) */

#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
