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
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if defined(USB_CFG_OTG_USE)
 #if (defined(USB_CFG_HCDC_USE) | defined(USB_CFG_PCDC_USE))
  #include "r_usb_otg_cdc_cfg.h"
  #include "r_usb_pcdc_api.h"
 #endif                                /* (defined(USB_CFG_HCDC_USE) | defined(USB_CFG_PCDC_USE)) */
#else                                  /* defined(USB_CFG_OTG_USE) */
 #if defined(USB_CFG_HCDC_USE)
  #include "r_usb_hcdc_cfg.h"
 #endif                                /* defined(USB_CFG_HCDC_USE) */
 #if defined(USB_CFG_PCDC_USE)
  #include "r_usb_pcdc_api.h"
  #include "r_usb_pcdc_cfg.h"
 #endif                                /* defined(USB_CFG_PCDC_USE) */
#endif                                 /* defined(USB_CFG_OTG_USE) */

#if defined(USB_CFG_PPRN_USE)
 #include "r_usb_pprn_api.h"
 #if (BSP_CFG_RTOS != 1)
  #include "r_usb_pprn_cfg.h"
 #endif                                /* (BSP_CFG_RTOS != 1) */
#endif                                 /* defined(USB_CFG_PPRN_USE) */

#if defined(USB_CFG_HPRN_USE)
 #include "r_usb_hprn_cfg.h"
#endif                                 /* defined(USB_CFG_HPRN_USE) */

#if defined(USB_CFG_PMSC_USE)
 #include "r_usb_pmsc_api.h"
#endif                                 /* defined(USB_CFG_PMSC_USE) */

#if defined(USB_CFG_PHID_USE) && !defined(USB_CFG_OTG_USE)
 #include "r_usb_phid_api.h"
#endif                                 /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_HHID_USE) && defined(USB_CFG_OTG_USE)
 #include "r_usb_otg_hid_cfg.h"
#else
 #if defined(USB_CFG_HHID_USE)
  #include "r_usb_hhid_cfg.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */
#endif                                 /* defined(USB_CFG_HHID_USE) && defined(USB_CFG_OTG_USE) */
#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HMSC_USE)
  #include "r_usb_hmsc.h"
 #endif                                /* defined(USB_CFG_HMSC_USE) */
#else  /* #if (BSP_CFG_RTOS != 1) */
 #if defined(USB_CFG_PAUD_USE)
  #include "r_usb_paud_cfg.h"
 #endif                                /* defined(USB_CFG_PAUD_USE) */
 #if defined(USB_CFG_HUVC_USE)
  #include "r_usb_huvc_cfg.h"
 #endif                                /* defined(USB_CFG_HUVC_USE) */

#endif /* #if (BSP_CFG_RTOS != 1) */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
 #include "../hw/inc/r_usb_dmac.h"
#endif                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/* Pipe number of USB Host transfer.(Read pipe/Write pipe) */
static const uint8_t g_usb_pipe_host[] =
{
    /* READ pipe *//* WRITE pipe */
    /* IN pipe *//* OUT pipe */
 #if defined(USB_CFG_HCDC_USE)
    USB_CFG_HCDC_BULK_IN,  USB_CFG_HCDC_BULK_OUT,  /* HCDC: Address 1 */
    USB_CFG_HCDC_BULK_IN,  USB_CFG_HCDC_BULK_OUT,  /* HCDC: Address 2 using Hub */
    USB_CFG_HCDC_BULK_IN2, USB_CFG_HCDC_BULK_OUT2, /* HCDC: Address 3 using Hub */
    USB_NULL,              USB_NULL,
    USB_CFG_HCDC_INT_IN,   USB_NULL,               /* HCDCC: Address 1 */
    USB_CFG_HCDC_INT_IN,   USB_NULL,               /* HCDCC: Address 2 using Hub */
    USB_CFG_HCDC_INT_IN2,  USB_NULL,               /* HCDCC: Address 3 using Hub */
    USB_NULL,              USB_NULL,
 #else                                             /* defined(USB_CFG_HCDC_USE) */
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
 #endif                                          /* defined(USB_CFG_HCDC_USE) */

 #if defined(USB_CFG_HHID_USE)
    USB_CFG_HHID_INT_IN,   USB_CFG_HHID_INT_OUT, /* HHID: Address 1 */
    USB_CFG_HHID_INT_IN,   USB_CFG_HHID_INT_OUT, /* HHID: Address 2 using Hub */
    USB_CFG_HHID_INT_IN2,  USB_NULL,             /* HHID: Address 3 using Hub */
    USB_CFG_HHID_INT_IN3,  USB_NULL,             /* HHID: Address 4 using Hub */
 #else                                           /* defined(USB_CFG_HHID_USE) */
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
 #endif                                           /* defined(USB_CFG_HHID_USE) */

 #if defined(USB_CFG_HPRN_USE)
    USB_CFG_HPRN_BULK_IN,  USB_CFG_HPRN_BULK_OUT, /* HPRN: Address 1 */
    USB_CFG_HPRN_BULK_IN,  USB_CFG_HPRN_BULK_OUT, /* HPRN: Address 2 using Hub */
    USB_NULL,              USB_NULL,              /* HPRN: Address 3 using Hub */
    USB_NULL,              USB_NULL,              /* HPRN: Address 4 using Hub */
 #else                                            /* defined(USB_CFG_HPRN_USE) */
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
 #endif                                          /* defined(USB_CFG_HPRN_USE) */

 #if defined(USB_CFG_HUVC_USE)
    USB_CFG_HUVC_ISO_IN,   USB_CFG_HUVC_ISO_OUT, /* HPRN: Address 1 */
    USB_CFG_HUVC_ISO_IN,   USB_CFG_HUVC_ISO_OUT, /* HPRN: Address 2 using Hub */
    USB_NULL,              USB_NULL,             /* HPRN: Address 3 using Hub */
    USB_NULL,              USB_NULL,             /* HPRN: Address 4 using Hub */
 #else                                           /* defined(USB_CFG_HPRN_USE) */
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
    USB_NULL,              USB_NULL,
 #endif                                /* defined(USB_CFG_HPRN_USE) */
};
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static const uint8_t g_usb_pipe_peri[] =
{
    /* OUT pipe */          /* IN pipe */
 #if defined(USB_CFG_PCDC_USE)
    USB_CFG_PCDC_BULK_OUT,  USB_CFG_PCDC_BULK_IN,  /* USB_PCDC   (0) */
    USB_NULL,               USB_CFG_PCDC_INT_IN,   /* USB_PCDCC  (1) */
    USB_CFG_PCDC_BULK_OUT2, USB_CFG_PCDC_BULK_IN2, /* USB_PCDC2  (2) */
    USB_NULL,               USB_CFG_PCDC_INT_IN2,  /* USB_PCDCC2 (3) */
 #else                                             /* defined(USB_CFG_PCDC_USE) */
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
 #endif                                           /* defined(USB_CFG_PCDC_USE) */

 #if defined(USB_CFG_PHID_USE)
  #if (BSP_CFG_RTOS != 1)
    USB_CFG_PHID_INT_OUT,   USB_CFG_PHID_INT_IN,  /* USB_PHID  (4) */
    USB_CFG_PHID_INT_OUT2,  USB_CFG_PHID_INT_IN2, /* USB_PHID2 (5) */
  #else /* #if (BSP_CFG_RTOS != 1) */
    USB_CFG_PHID_INT_OUT,   USB_CFG_PHID_INT_IN,  /* USB_PHID  (4) */
    USB_NULL,               USB_NULL,             /* USB_PHID2 (5) */
  #endif /* #if (BSP_CFG_RTOS != 1) */
 #else                                            /* defined(USB_CFG_PHID_USE) */
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
 #endif                                           /* defined(USB_CFG_PHID_USE) */

 #if defined(USB_CFG_PAUD_USE)
    USB_CFG_PAUD_ISO_OUT,   USB_CFG_PAUD_ISO_IN,  /* USB_PAUD (6) */
 #else                                            /* defined(USB_CFG_PAUD_USE) */
    USB_NULL,               USB_NULL,
 #endif                                           /* defined(USB_CFG_PAUD_USE) */

 #if defined(USB_CFG_PPRN_USE)
    USB_CFG_PPRN_BULK_OUT,  USB_CFG_PPRN_BULK_IN, /* USB_PPRN (7) */
 #else                                            /* defined(USB_CFG_PPRN_USE) */
    USB_NULL,               USB_NULL,
 #endif                                           /* defined(USB_CFG_PPRN_USE) */

    USB_NULL,               USB_NULL,             /* USB_DFU (8) */
};
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/* USB data transfer */
/* PIPEn Buffer counter */
uint32_t g_usb_pstd_data_cnt[USB_MAX_PIPE_NO + 1U];

/* PIPEn Buffer pointer(8bit) */
uint8_t * gp_usb_pstd_data[USB_MAX_PIPE_NO + 1U];

/* Message pipe */
usb_utr_t * g_p_usb_pstd_pipe[USB_MAX_PIPE_NO + 1U];

#endif                                 /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */

/* Callback function of USB Read/USB Write */
void (* g_usb_callback[])(usb_utr_t *, uint16_t, uint16_t) =
{
    /* PCDC, PCDCC */
#if defined(USB_CFG_PCDC_USE)
 #if (BSP_CFG_RTOS == 1)
    USB_NULL, USB_NULL,                              /* USB_PCDC  (0) */
    USB_NULL, USB_NULL,                              /* USB_PCDCC (1) */
    USB_NULL, USB_NULL,                              /* USB_PCDC2  (2) */
    USB_NULL, USB_NULL,                              /* USB_PCDCC2 (3) */
 #else  /* #if (BSP_CFG_RTOS == 1) */
    usb_pcdc_read_complete, usb_pcdc_write_complete, /* USB_PCDC  (0) */
    USB_NULL, usb_pcdc_write_complete,               /* USB_PCDCC (1) */
    usb_pcdc_read_complete, usb_pcdc_write_complete, /* USB_PCDC2  (2) */
    USB_NULL, usb_pcdc_write_complete,               /* USB_PCDCC2 (3) */
 #endif /* #if (BSP_CFG_RTOS == 1) */
#else
    USB_NULL, USB_NULL,                              /* USB_PCDC  (0) */
    USB_NULL, USB_NULL,                              /* USB_PCDCC (1) */
    USB_NULL, USB_NULL,                              /* USB_PCDC2  (2) */
    USB_NULL, USB_NULL,                              /* USB_PCDCC2 (3) */
#endif

    /* PHID */
#if defined(USB_CFG_PHID_USE)
 #if (BSP_CFG_RTOS != 1)
    usb_phid_read_complete, usb_phid_write_complete, /* USB_PHID (4) */
    usb_phid_read_complete, usb_phid_write_complete, /* USB_PHID2 (5) */
 #else /*  #if (BSP_CFG_RTOS == 1) */
    USB_NULL, USB_NULL,                              /* USB_PHID (4) */
    USB_NULL, USB_NULL,                              /* USB_PHID (5) */
 #endif /*  #if (BSP_CFG_RTOS == 1) */
#else
    USB_NULL, USB_NULL,                              /* USB_PHID (4) */
    USB_NULL, USB_NULL,                              /* USB_PHID (5) */
#endif

    /* PAUD */
    USB_NULL, USB_NULL,                              /* USB_PAUD (6) */

    /* PPRN */
#if defined(USB_CFG_PPRN_USE)
 #if (BSP_CFG_RTOS != 1)
    usb_pprn_read_complete, usb_pprn_write_complete, /* USB_PPRN (7) */
 #else  /* BSP_CFG_RTOS != 1 */
    USB_NULL, USB_NULL,                              /* USB_PPRN (7) */
 #endif /* BSP_CFG_RTOS != 1 */
#else                                                /* defined(USB_CFG_PPRN_USE) */
    USB_NULL, USB_NULL,                              /* USB_PPRN (7) */
#endif /* defined(USB_CFG_PPRN_USE) */

    /* DFU */
    USB_NULL, USB_NULL,                              /* USB_DFU (8) */

    /* PVND */
    USB_NULL, USB_NULL,                              /* USB_PVND (9) */

    /* HCDC, HCDCC */
#if defined(USB_CFG_HCDC_USE)
 #if (BSP_CFG_RTOS == 1)
    USB_NULL, USB_NULL,                              /* USB_HCDC  (10) */
    USB_NULL, USB_NULL,                              /* USB_HCDCC (11) */
 #else  /* #if (BSP_CFG_RTOS == 1) */
    usb_hcdc_read_complete, usb_hcdc_write_complete, /* USB_HCDC  (10) */
    usb_hcdc_read_complete, USB_NULL,                /* USB_HCDCC (11) */
 #endif /* #if (BSP_CFG_RTOS == 1) */
#else
    USB_NULL, USB_NULL,                              /* USB_HCDC  (10) */
    USB_NULL, USB_NULL,                              /* USB_HCDCC (11) */
#endif

    /* HHID */
#if defined(USB_CFG_HHID_USE)
 #if (BSP_CFG_RTOS == 1)
    USB_NULL, USB_NULL,                              /* USB_HHID (12) */
 #else                                               /* #if (BSP_CFG_RTOS == 1) */
    usb_hhid_read_complete, usb_hhid_write_complete, /* USB_HHID  (12) */
 #endif /* #if (BSP_CFG_RTOS == 1) */
#else
    USB_NULL, USB_NULL,                              /* USB_HHID  (12) */
#endif

    /* HVND */
#if defined(USB_CFG_HVND_USE)
    usb_hvnd_read_complete, usb_hvnd_write_complete, /* USB_HVND  (13) */
#else
    USB_NULL, USB_NULL,                              /* USB_HVND  (13) */
#endif

    /* HMSC */
    USB_NULL, USB_NULL,                              /* USB_HMSC  (14) */

    /* PMSC */
    USB_NULL, USB_NULL,                              /* USB_PMSC  (15) */

    /* HPRN */
#if defined(USB_CFG_HPRN_USE)
 #if (BSP_CFG_RTOS == 1)
    USB_NULL, USB_NULL,                              /* USB_HPRN (16) */
 #else                                               /* #if (BSP_CFG_RTOS == 1) */
    usb_hprn_read_complete, usb_hprn_write_complete, /* USB_HPRN (16) */
 #endif /* #if (BSP_CFG_RTOS == 1) */
#else
    USB_NULL, USB_NULL,                              /* USB_HPRN (16) */
#endif

    /* HUVC */

    USB_NULL, USB_NULL,                /* USB_HUVC (17) */
};                                     /* const void (g_usb_callback[])(usb_utr_t *, uint16_t, uint16_t) */

#if defined(USB_CFG_PCDC_USE)

/* Abstract Control Model Notification - SerialState */
uint8_t g_usb_pcdc_serialstate_table[USB_PCDC_SETUP_TBL_BSIZE] =
{
    USB_DEV_TO_HOST | USB_CLASS | USB_INTERFACE, /* bmRequestType */
    USB_PCDC_SERIAL_STATE,                       /* bNotification:SERIAL_STATE */
    0x00, 0x00,                                  /* wValue:Zero */
    0x00, 0x00,                                  /* wIndex:Interface */
    0x02, 0x00,                                  /* wLength:2 */
    0x00, 0x00,                                  /* Data:UART State bitmap */
};

#endif /* defined(USB_CFG_PCDC_USE) */

usb_pipe_table_t g_usb_pipe_table[USB_NUM_USBIP][USB_MAXPIPE_NUM + 1];
uint16_t         g_usb_cstd_bemp_skip[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

/******************************************************************************
 * Renesas Abstracted common data I/O functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_debug_hook
 * Description     : Debug hook
 * Arguments       : uint16_t error_code          : error code
 * Return value    : none
 ******************************************************************************/
void usb_cstd_debug_hook (uint16_t error_code)
{
    FSP_PARAMETER_NOT_USED(error_code);

    /* WAIT_LOOP */

    while (1)
    {
        /* Non */
    }
}                                      /* End of function usb_cstd_debug_hook() */

#if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_ctrl_read
 * Description     : Receive process for Control transfer
 * Arguments       : usb_instance_ctrl_t *p_ctrl: Control structure for USB API.
 *               : uint8_t *buf      : transfer data address
 *               : uint32_t size     : transfer length
 * Return value    : usb_er_t          : USB_SUCCESS(USB_OK) / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_ctrl_read (usb_instance_ctrl_t * p_ctrl, uint8_t * buf, uint32_t size)
{
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_er_t    err;
    usb_utr_t * p_tran_data;
  #if (BSP_CFG_RTOS != 0)
    usb_utr_t tran_data_host;
  #endif                               /* #if (BSP_CFG_RTOS != 0) */

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
  #if (BSP_CFG_RTOS != 0)
        p_tran_data = &tran_data_host;
  #else                                        /* #if (BSP_CFG_RTOS != 0) */
        p_tran_data = &g_usb_hdata[p_ctrl->module_number][USB_PIPE0];
  #endif /* #if (BSP_CFG_RTOS != 0) */

        p_tran_data->read_req_len = size;      /* Save Read Request Length */
        p_tran_data->keyword      = USB_PIPE0; /* Pipe No */
        p_tran_data->p_tranadr    = buf;       /* Data address */
        p_tran_data->tranlen      = size;      /* Data Size */

        /* Callback function */
        p_tran_data->complete = usb_class_request_complete;
        g_usb_ctrl_request[p_ctrl->module_number][p_ctrl->device_address].address = p_ctrl->device_address;
        g_usb_ctrl_request[p_ctrl->module_number][p_ctrl->device_address].setup   = p_ctrl->setup;

        /* Setup message address set */
        p_tran_data->p_setup =
            (uint16_t *) &g_usb_ctrl_request[p_ctrl->module_number][p_ctrl->device_address];
        p_tran_data->segment = USB_TRAN_END;
        p_tran_data->ip      = p_ctrl->module_number;
        p_tran_data->ipp     = usb_hstd_get_usb_ip_adr(p_ctrl->module_number);
        err = usb_hstd_transfer_start(p_tran_data);

        return err;
    }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_utr_t tran_data_peri;

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
        if (USB_ON == g_usb_pstd_pipe0_request)
        {
            return USB_QOVR;
        }

        tran_data_peri.ip      = p_ctrl->module_number;
        g_usb_pstd_std_request = USB_YES;
        usb_pstd_ctrl_write(size, buf, &tran_data_peri);
    }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

    return USB_OK;
} /* End of function usb_ctrl_read() */

/******************************************************************************
 * Function Name   : usb_ctrl_write
 * Description     : Send process for Control transfer
 * Arguments       : usb_instance_ctrl_t *p_ctrl: Control structure for USB API.
 *               : uint8_t *buf      : transfer data address
 *               : uint32_t size     : transfer length
 * Return value    : usb_er_t          : USB_SUCCESS(USB_OK) / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_ctrl_write (usb_instance_ctrl_t * p_ctrl, uint8_t * buf, uint32_t size)
{
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_er_t    err;
    usb_utr_t * p_tran_data;
  #if (BSP_CFG_RTOS != 0)
    usb_utr_t tran_data_host;
  #endif                               /* #if (BSP_CFG_RTOS != 0) */

    if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
    {
  #if (BSP_CFG_RTOS != 0)
        p_tran_data = &tran_data_host;
  #else                                     /* #if (BSP_CFG_RTOS != 0) */
        p_tran_data = &g_usb_hdata[p_ctrl->module_number][USB_PIPE0];
  #endif /* #if (BSP_CFG_RTOS != 0) */

        p_tran_data->read_req_len = size;   /* Save Read Request Length */

        p_tran_data->keyword   = USB_PIPE0; /* Pipe No */
        p_tran_data->p_tranadr = buf;       /* Data address */
        p_tran_data->tranlen   = size;      /* Data Size */

        /* Callback function */
        p_tran_data->complete = usb_class_request_complete;
        g_usb_ctrl_request[p_ctrl->module_number][p_ctrl->device_address].address = p_ctrl->device_address;
        g_usb_ctrl_request[p_ctrl->module_number][p_ctrl->device_address].setup   = p_ctrl->setup;

        /* Setup message address set */
        p_tran_data->p_setup =
            (uint16_t *) &g_usb_ctrl_request[p_ctrl->module_number][p_ctrl->device_address];
        p_tran_data->segment = USB_TRAN_END;
        p_tran_data->ip      = p_ctrl->module_number;
        p_tran_data->ipp     = usb_hstd_get_usb_ip_adr(p_ctrl->module_number);
        err = usb_hstd_transfer_start(p_tran_data);

        return err;
    }
 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_instance_ctrl_t ctrl;
    usb_utr_t           tran_data_peri;

    tran_data_peri.ip = p_ctrl->module_number;

    if (USB_MODE_PERI == g_usb_usbmode[p_ctrl->module_number])
    {
        if ((USB_NULL == buf) && (USB_NULL == size))
        {
            if (USB_SETUP_STATUS_ACK == p_ctrl->status)
            {
                usb_cstd_set_buf(&tran_data_peri, (uint16_t) USB_PIPE0); /* Set BUF */
            }
            else /* USB_STALL */
            {
                usb_pstd_set_stall_pipe0(&tran_data_peri);
            }

            ctrl.setup         = p_ctrl->setup; /* Save setup data. */
            ctrl.module_number = p_ctrl->module_number;
            ctrl.data_size     = 0;
            ctrl.status        = USB_SETUP_STATUS_ACK;
            ctrl.type          = USB_CLASS_REQUEST;
  #if (BSP_CFG_RTOS == 1)
            ctrl.p_data = (void *) tx_thread_identify();
  #elif (BSP_CFG_RTOS == 2)
            ctrl.p_data = (void *) xTaskGetCurrentTaskHandle();
  #endif                               /* #if (BSP_CFG_RTOS == 1) */
            usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl);
        }
        else
        {
            if (USB_ON == g_usb_pstd_pipe0_request)
            {
                return USB_QOVR;
            }

            g_usb_pstd_std_request = USB_YES;
            usb_pstd_ctrl_read(size, buf, &tran_data_peri);
        }
    }
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

    return USB_OK;
} /* End of function usb_ctrl_write() */

/******************************************************************************
 * Function Name   : usb_ctrl_stop
 * Description     : Stop of USB Control transfer.
 * Arguments       : usb_instance_ctrl_t *p_ctrl: Control structure for USB API.
 * Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_ctrl_stop (usb_instance_ctrl_t * p_ctrl)
{
    usb_er_t  err = USB_OK;
    usb_utr_t utr;

    if (USB_CLASS_INTERNAL_PVND < (usb_class_internal_t) (p_ctrl->type))
    {
        /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip  = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
        err     = usb_hstd_transfer_end(&utr, USB_PIPE0, (uint16_t) USB_DATA_STOP);
 #endif
    }
    else
    {
        /* Peripheral only */
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        utr.ip = p_ctrl->module_number;
        err    = usb_pstd_transfer_end(&utr, USB_PIPE0);
 #endif
    }

    return err;
}                                      /* End of function usb_ctrl_stop() */

#endif /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_data_read
 * Description     : USB data read processing
 * Arguments       : usb_instance_ctrl_t *p_ctrl: Control structure for USB API.
 *               : uint8_t *buf      : Transfer data address
 *               : uint32_t size     : Transfer length
 * Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_data_read (usb_instance_ctrl_t * p_ctrl, uint8_t * buf, uint32_t size)
{
    uint8_t     pipe;
    usb_er_t    err = USB_OK;
    usb_utr_t * p_tran_data;
#if (BSP_CFG_RTOS != 0)
    usb_utr_t tran_data;
#endif                                 /* #if (BSP_CFG_RTOS != 0) */

    pipe = usb_get_usepipe(p_ctrl, USB_TRANSFER_READ);

    if (USB_CLASS_INTERNAL_PVND < (usb_class_internal_t) (p_ctrl->type))
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
 #if (BSP_CFG_RTOS != 0)
        p_tran_data = &tran_data;
 #else                                                             /* #if (BSP_CFG_RTOS != 0) */
        p_tran_data = &g_usb_hdata[p_ctrl->module_number][pipe];
 #endif /* #if (BSP_CFG_RTOS != 0) */

        p_tran_data->read_req_len = size;                          /* Save Read Request Length */

        p_tran_data->keyword   = pipe;                             /* Pipe No */
        p_tran_data->p_tranadr = buf;                              /* Data address */
        p_tran_data->tranlen   = size;                             /* Data Size */
        p_tran_data->complete  = g_usb_callback[p_ctrl->type * 2]; /* Callback function */
        p_tran_data->segment   = USB_TRAN_END;
        p_tran_data->ip        = p_ctrl->module_number;
        p_tran_data->ipp       = usb_hstd_get_usb_ip_adr(p_ctrl->module_number);
 #if (USB_CFG_DMA == USB_CFG_ENABLE)
        if (0 != p_ctrl->p_transfer_tx)
        {
            p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
        }
        else
        {
            p_tran_data->p_transfer_tx = 0;
        }

        if (0 != p_ctrl->p_transfer_rx)
        {
            p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
        }
        else
        {
            p_tran_data->p_transfer_rx = 0;
        }
 #endif
        err = usb_hstd_transfer_start(p_tran_data);
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
 #if (BSP_CFG_RTOS != 0)
        p_tran_data = &tran_data;
 #else                                                                        /* #if (BSP_CFG_RTOS != 0) */
        p_tran_data = &g_usb_pdata[pipe];
 #endif /* #if (BSP_CFG_RTOS != 0) */

        p_tran_data->read_req_len = size;                                     /* Save Read Request Length */

        p_tran_data->ip        = p_ctrl->module_number;                       /* USB Module Number */
        p_tran_data->keyword   = pipe;                                        /* Pipe No */
        p_tran_data->p_tranadr = buf;                                         /* Data address */
        p_tran_data->tranlen   = size;                                        /* Data Size */
        p_tran_data->complete  = (usb_cb_t) g_usb_callback[p_ctrl->type * 2]; /* Callback function */
 #if (USB_CFG_DMA == USB_CFG_ENABLE)
        if (0 != p_ctrl->p_transfer_tx)
        {
            p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
        }
        else
        {
            p_tran_data->p_transfer_tx = 0;
        }

        if (0 != p_ctrl->p_transfer_rx)
        {
            p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
        }
        else
        {
            p_tran_data->p_transfer_rx = 0;
        }
 #endif
        err = usb_pstd_transfer_start(p_tran_data);
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return err;
} /* End of function usb_data_read() */

/******************************************************************************
 * Function Name   : usb_data_write
 * Description     : USB data write processing
 * Arguments       : usb_instance_ctrl_t *p_ctrl: Control structure for USB API.
 *               : uint8_t *buf      : Transfer data address
 *               : uint32_t size     : Transfer length
 * Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_data_write (usb_instance_ctrl_t * p_ctrl, uint8_t const * const buf, uint32_t size)
{
    uint8_t     pipe;
    usb_er_t    err = USB_OK;
    usb_utr_t * p_tran_data;
#if (BSP_CFG_RTOS != 0)
    usb_utr_t tran_data;
#endif                                 /* #if (BSP_CFG_RTOS != 0) */

    pipe = usb_get_usepipe(p_ctrl, USB_TRANSFER_WRITE);

    if (USB_CLASS_INTERNAL_PVND < (usb_class_internal_t) (p_ctrl->type))
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
 #if (BSP_CFG_RTOS != 0)
        p_tran_data = &tran_data;
 #else                                                                   /* #if (BSP_CFG_RTOS != 0) */
        p_tran_data = &g_usb_hdata[p_ctrl->module_number][pipe];
 #endif /* #if (BSP_CFG_RTOS != 0) */

        p_tran_data->keyword   = pipe;                                   /* Pipe No */
        p_tran_data->p_tranadr = buf;                                    /* Data address */
        p_tran_data->tranlen   = size;                                   /* Data Size */
        p_tran_data->complete  = g_usb_callback[(p_ctrl->type * 2) + 1]; /* Callback function */
        p_tran_data->segment   = USB_TRAN_END;
        p_tran_data->ip        = p_ctrl->module_number;
        p_tran_data->ipp       = usb_hstd_get_usb_ip_adr(p_ctrl->module_number);
 #if (USB_CFG_DMA == USB_CFG_ENABLE)
        if (0 != p_ctrl->p_transfer_tx)
        {
            p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
        }
        else
        {
            p_tran_data->p_transfer_tx = 0;
        }

        if (0 != p_ctrl->p_transfer_rx)
        {
            p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
        }
        else
        {
            p_tran_data->p_transfer_rx = 0;
        }
 #endif
        err = usb_hstd_transfer_start(p_tran_data);
#endif                                 /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
 #if (BSP_CFG_RTOS != 0)
        p_tran_data = &tran_data;
 #else                                 /* #if (BSP_CFG_RTOS != 0) */
        p_tran_data = &g_usb_pdata[pipe];
 #endif /* #if (BSP_CFG_RTOS != 0) */

 #if defined(USB_CFG_PCDC_USE)
        if (USB_CFG_PCDC_INT_IN != pipe)
        {
            p_tran_data->p_tranadr = buf;  /* Data address */
            p_tran_data->tranlen   = size; /* Data Size */
        }
        else
        {
            g_usb_pcdc_serialstate_table[8] = buf[0];
            g_usb_pcdc_serialstate_table[9] = buf[1];
            p_tran_data->p_tranadr          = g_usb_pcdc_serialstate_table;        /* Data address */
            p_tran_data->tranlen            = 10;                                  /* Data Size */
        }
 #else                                                                             /* defined(USB_CFG_PCDC_USE) */
        p_tran_data->p_tranadr = buf;                                              /* Data address */
        p_tran_data->tranlen   = size;                                             /* Data Size */
 #endif                                                                            /* defined(USB_CFG_PCDC_USE) */
        p_tran_data->ip       = p_ctrl->module_number;                             /* USB Module Number */
        p_tran_data->keyword  = pipe;                                              /* Pipe No */
        p_tran_data->complete = (usb_cb_t) g_usb_callback[(p_ctrl->type * 2) + 1]; /* Callback function */
 #if (USB_CFG_DMA == USB_CFG_ENABLE)
        if (0 != p_ctrl->p_transfer_tx)
        {
            p_tran_data->p_transfer_tx = p_ctrl->p_transfer_tx;
        }
        else
        {
            p_tran_data->p_transfer_tx = 0;
        }

        if (0 != p_ctrl->p_transfer_rx)
        {
            p_tran_data->p_transfer_rx = p_ctrl->p_transfer_rx;
        }
        else
        {
            p_tran_data->p_transfer_rx = 0;
        }
 #endif
        err = usb_pstd_transfer_start(p_tran_data);
#endif                                 /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
    }

    return err;
} /* End of function usb_data_write() */

#if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_data_stop
 * Description     : USB data transfer stop processing
 * Arguments       : usb_instance_ctrl_t *p_ctrl: control structure for USB API.
 *               : usb_transfer_t type  : USB_TRANSFER_READ(0)/USB_TRANSFER_WRITE(1)
 * Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_data_stop (usb_instance_ctrl_t * p_ctrl, usb_transfer_t type)
{
    uint8_t   pipe;
    usb_er_t  err = USB_ERROR;
    usb_utr_t utr;

    pipe = usb_get_usepipe(p_ctrl, type);

    if (USB_NULL == pipe)
    {
        return USB_ERROR;
    }

    if (USB_CLASS_INTERNAL_PVND < (usb_class_internal_t) (p_ctrl->type))
    {
        /* Host only */
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip  = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
        err     = usb_hstd_transfer_end(&utr, pipe, (uint16_t) USB_DATA_STOP);
 #endif
    }
    else
    {
        /* Peripheral only */
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        utr.ip = p_ctrl->module_number;
        err    = usb_pstd_transfer_end(&utr, pipe);
 #endif
    }

    return err;
}                                      /* End of function usb_data_stop() */

#endif /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_get_usepipe
 * Description     : Get pipe number for USB Read/USB Write
 * Arguments       : usb_instance_ctrl_t *p_ctrl: Control structure for USB API.
 *               : usb_transfer_t dir       : USB_TRANSFER_READ(0)/USB_TRANSFER_WRITE(1)
 * Return value    : Bitmap of Use pipe
 ******************************************************************************/
uint8_t usb_get_usepipe (usb_instance_ctrl_t * p_ctrl, usb_transfer_t dir)
{
    uint8_t pipe = USB_NULL;
    uint8_t idx;

    if (USB_CLASS_INTERNAL_PVND < (usb_class_internal_t) (p_ctrl->type))
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

        /* Host */
        idx =
            (uint8_t) (((((usb_class_internal_t) p_ctrl->type - USB_CLASS_INTERNAL_HCDC) * 8) +
                        ((p_ctrl->device_address - 1) * 2)) + dir);
        pipe = g_usb_pipe_host[idx];
#endif
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

        /* Peripheral */
        idx  = (uint8_t) ((p_ctrl->type * 2) + dir);
        pipe = g_usb_pipe_peri[idx];
#endif
    }

    return pipe;
}                                      /* End of function usb_get_usepipe() */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
