/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef R_USB_TYPEDEF_H
#define R_USB_TYPEDEF_H

/******************************************************************************
 * Includes <System Includes>
 ******************************************************************************/
#include <stdint.h>
#include "r_usb_basic_api.h"
#include "r_usb_cstd_rtos.h"
#include "r_usb_basic.h"
#include "r_usb_basic_define.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Typedef definitions
 ******************************************************************************/
typedef void * VP;                     /* Pointer to variable      */
typedef long   ER;                     /* Error code               */
typedef short  ID;                     /* Object ID (xxxid)        */
typedef long   TMO;                    /* Time out                 */
typedef long   VP_INT;                 /* Integer data             */

/*----------- msghead -----------*/
typedef struct
{
    VP msghead;                        /* Message header */
} t_msg_t;

typedef t_msg_t usb_msg_t;
typedef ER      usb_er_t;
typedef ID      usb_id_t;
typedef TMO     usb_tm_t;
typedef VP      usb_mh_t;
typedef VP_INT  usb_vp_int_t;

#if defined(USB_HIGH_SPEED_MODULE)
typedef volatile R_USB_HS0_Type * usb_regadr1_t; // @@
#else /* defined(USB_HIGH_SPEED_MODULE) */
typedef volatile R_USB_FS0_Type * usb_regadr1_t;
#endif /* defined(USB_HIGH_SPEED_MODULE) */

typedef volatile R_USB_FS0_Type * usb_regadr_t;

typedef struct usb_utr usb_utr_t;
typedef void        (* usb_cb_t)(struct usb_utr *, uint16_t, uint16_t);

typedef struct usb_utr
{
    usb_mh_t     msghead;              /* Message header (for SH-solution) */
    usb_cb_t     complete;             /* Call Back Function Info */
    void const * p_tranadr;            /* Transfer data Start address */
#if (BSP_CFG_RTOS == 1)                /* Azure RTOS */
 #if (USB_CFG_DMA == USB_CFG_ENABLE)
    void const * p_tranadr_hold;
 #endif /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */
#endif /* (BSP_CFG_RTOS == 1) */
    uint32_t   read_req_len;                   /* Read Request Length */
    uint32_t   tranlen;                        /* Transfer data length */
    uint16_t * p_setup;                        /* Setup packet(for control only) */
    void     * p_usr_data;
#if (BSP_CFG_RTOS != 0)
    usb_hdl_t cur_task_hdl;                    /* Task Handle */
#endif /* #if (BSP_CFG_RTOS != 0) */
    uint16_t msginfo;                          /* Message Info for F/W */
    uint16_t keyword;                          /* Root port / Device address / Pipe number */
    uint8_t  ip;                               /* USB module number(0 or 1) */
    uint16_t result;                           /* Result */
    uint16_t status;                           /* Status */
    uint16_t pipectr;                          /* Pipe control register */
#if (BSP_CFG_RTOS != 0)
    uint16_t setup_data[5];                    /* Save setup for Request */
#endif /* #if (BSP_CFG_RTOS != 0) */
    uint8_t errcnt;                            /* Error count */
    uint8_t segment;                           /* Last flag */
    const transfer_instance_t * p_transfer_tx; ///< Send context
    const transfer_instance_t * p_transfer_rx; ///< Receive context
    union
    {
        usb_regadr_t ipp;                      /* USB module startAddress(USB0/USB1)*/
#if USB_NUM_USBIP == 2
        usb_regadr1_t ipp1;                    /* USB module start address(USBA) */
#endif                                         /* USB_NUM_USBIP == 2 */
    };
#if (BSP_CFG_RTOS == 1)                        /* Azure RTOS */
 #if (defined(USB_CFG_PPRN_USE) || defined(USB_CFG_PCDC_USE))
    uint32_t timeout;
    uint8_t  is_timeout;
 #endif /* define(USB_CFG_PPRN_USE) ||  defined(USB_CFG_PCDC_USE) */
#endif                                 /* (BSP_CFG_RTOS == 1) */
} usb_message_t;

typedef struct st_usb usb_stnbyint_t;

typedef void (* usb_cb_check_t)(struct usb_utr *, uint16_t **);

/* Class request processing function type. */
typedef void (* usb_cb_trn_t)(usb_setup_t * preq, uint16_t ctsq, usb_utr_t * p_utr);

typedef struct
{
    uint16_t       rootport;           /* Root port */
    uint16_t       devaddr;            /* Device address */
    uint16_t       devstate;           /* Device state */
    uint16_t       ifclass;            /* Interface Class */
    uint16_t     * p_tpl;              /* Target peripheral list(Vendor ID, Product ID) */
    usb_cb_t       classinit;          /* Driver init */
    usb_cb_check_t classcheck;         /* Driver check */
    usb_cb_t       devconfig;          /* Device configured */
    usb_cb_t       devdetach;          /* Device detach */
    usb_cb_t       devsuspend;         /* Device suspend */
    usb_cb_t       devresume;          /* Device resume */
} usb_hcdreg_t;

typedef struct
{
    uint8_t    * p_devicetbl;          /* Device descriptor Table address */
    uint8_t    * p_qualitbl;           /* Qualifier descriptor Table address */
    uint8_t    * p_configtbl;          /* Configuration descriptor Table address */
    uint8_t    * p_othertbl;           /* Other configuration descriptor Table address */
    uint8_t   ** p_stringtbl;          /* String descriptor Table address */
    usb_cb_t     devdefault;           /* Device default */
    usb_cb_t     devconfig;            /* Device configured */
    usb_cb_t     devdetach;            /* Device detach */
    usb_cb_t     devsuspend;           /* Device suspend */
    usb_cb_t     devresume;            /* Device resume */
    usb_cb_t     interface;            /* Interface changed */
    usb_cb_trn_t ctrltrans;            /* Control Transfer */
    uint8_t      num_string;           /* Num entry String Descriptor */
} usb_pcdreg_t;

typedef struct usb_utr usb_hcdinfo_t;
typedef struct usb_utr usb_mgrinfo_t;
typedef struct usb_utr usb_pcdinfo_t;
typedef struct usb_utr usb_clsinfo_t;

typedef struct
{
    uint8_t state;                     /* BC State */
    uint8_t pd_detect;                 /* PD Detect Flag */
} usb_bc_status_t;

typedef struct usb_ctrl_trans
{
    usb_setup_t setup;                 /* Request command */
    uint16_t    address;               /* Device address setting */
} usb_ctrl_trans_t;

#if (BSP_CFG_RTOS == 0)
typedef struct
{
    uint16_t    type;
    uint16_t    status;
    usb_cfg_t * p_cfg;
} usb_int_info_t;
#endif                                 /*(BSP_CFG_RTOS == 0)*/

typedef struct
{
#if (BSP_CFG_RTOS != 0)
    uint16_t type;
    uint16_t status;
    uint16_t ip;
    uint16_t fifo_type;
#else                                    /* #if (BSP_CFG_RTOS != 0) */
    usb_int_info_t buf[USB_INT_BUFSIZE]; /* Interrupt Info */
    uint8_t        wp;                   /* Write pointer */
    uint8_t        rp;                   /* Read pointer */
#endif /* #if (BSP_CFG_RTOS != 0) */
} usb_int_t;

typedef struct
{
    uint16_t    ip;                    /* USB IP(USB_IP0/USB_IP1) */
    uint16_t    fifo_type;             /* Use FIFO type(USB_CUSE/USB_D0USE/USB_D1USE) */
    usb_cfg_t * p_cfg;
} usb_fifo_type_t;

typedef struct
{
#if (BSP_CFG_RTOS != 0)
    uint16_t type;
    uint16_t status;
    uint16_t ip;
    uint16_t fifo_type;
#else                                     /* #if (BSP_CFG_RTOS != 0) */
    usb_fifo_type_t buf[USB_INT_BUFSIZE]; /* Complete DMA Info */
    uint8_t         wp;                   /* Write pointer */
    uint8_t         rp;                   /* Read pointer */
#endif /* #if (BSP_CFG_RTOS != 0) */
} usb_dma_int_t;

typedef struct usb_event
{
#if (BSP_CFG_RTOS != 0)
    usb_instance_ctrl_t ctrl;                /* Control Information */
    uint8_t             code;
#else /* #if (BSP_CFG_RTOS != 0) */
    uint8_t             write_pointer;       /* Write pointer */
    uint8_t             read_pointer;        /* Read pointer */
    usb_status_t        code[USB_EVENT_MAX]; /* Event code */
    usb_instance_ctrl_t ctrl[USB_EVENT_MAX]; /* Control Information */
#endif /* #if (BSP_CFG_RTOS != 0) */
} usb_event_t;

typedef struct usb_pipe_table
{
    uint16_t use_flag;
    uint16_t pipe_cfg;
    uint16_t pipe_buf;
    uint16_t pipe_maxp;
    uint16_t pipe_peri;
} usb_pipe_table_t;

typedef struct usb_pipe_reg
{
    uint16_t pipe_cfg;
    uint16_t pipe_buf;
    uint16_t pipe_maxp;
    uint16_t pipe_peri;
} usb_pipe_table_reg_t;

typedef enum e_usb_class_internal
{
    USB_CLASS_INTERNAL_PCDC = 0,       ///< PCDC Class      0
    USB_CLASS_INTERNAL_PCDCC,          ///< PCDCC Class     1
    USB_CLASS_INTERNAL_PCDC2,          ///< PCDC2 Class     2
    USB_CLASS_INTERNAL_PCDCC2,         ///< PCDCC2 Class    3
    USB_CLASS_INTERNAL_PHID,           ///< PHID Class      4
    USB_CLASS_INTERNAL_PHID2,          ///< PHID2 Class     5
    USB_CLASS_INTERNAL_PAUD,           ///< PAUD Class      6
    USB_CLASS_INTERNAL_PPRN,           ///< PPRN Class      7
    USB_CLASS_INTERNAL_DFU,            ///< DFU Class       8
    USB_CLASS_INTERNAL_PVND,           ///< PVND Class      9
    USB_CLASS_INTERNAL_HCDC,           ///< HCDC Class      10
    USB_CLASS_INTERNAL_HCDCC,          ///< HCDCC Class     11
    USB_CLASS_INTERNAL_HHID,           ///< HHID Class      12
    USB_CLASS_INTERNAL_HVND,           ///< HVND Class      13
    USB_CLASS_INTERNAL_HMSC,           ///< HMSC Class      14
    USB_CLASS_INTERNAL_PMSC,           ///< PMSC Class      15
    USB_CLASS_INTERNAL_HPRN,           ///< HPRN Class      16
    USB_CLASS_INTERNAL_HUVC,           ///< HUVC Class      17
    USB_CLASS_INTERNAL_REQUEST,        ///< USB Class Request      18
    USB_CLASS_INTERNAL_END,            ///< USB Class       19
} usb_class_internal_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_TYPEDEF_H */
