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
#include <string.h>

#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HCDC_USE)
  #include "r_usb_hcdc_api.h"

 #endif                                /* defined(USB_CFG_HCDC_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HHID_USE)
  #include "r_usb_hhid_api.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HMSC_USE)
  #include "r_usb_hmsc_api.h"

 #endif                                /* defined(USB_CFG_HMSC_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#if defined(USB_CFG_PCDC_USE)
 #include "r_usb_pcdc_api.h"

#endif                                 /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_PPRN_USE)
 #include "r_usb_pprn_api.h"

#endif                                 /* defined(USB_CFG_PPRN_USE) */

#if defined(USB_CFG_PMSC_USE)
 #include "r_usb_pmsc_api.h"

#endif                                 /* defined(USB_CFG_PMSC_USE) */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
 #include "../hw/inc/r_usb_dmac.h"
#endif                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if (BSP_CFG_RTOS != 0)
 #include "inc/r_usb_cstd_rtos.h"
#endif                                 /* #if (BSP_CFG_RTOS != 0) */

#if (BSP_CFG_RTOS == 1)
 #if defined(USB_CFG_OTG_USE)
  #include "ux_api.h"
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
#endif                                 /* #if (BSP_CFG_RTOS != 0) */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
  #define USB_RESPONCE_COUNTER_VALUE    (6000U)
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

 #if defined(USB_CFG_HVND_USE)
  #define USB_EP_PIPE_NUM               (9)
  #define USB_EP_TBL_WSIZE              ((USB_EPL * USB_EP_PIPE_NUM) + 1)
 #endif                                /* defined(USB_CFG_HVND_USE) */

 #define USB_VALUE_FFH                  (0xFF)
 #define USB_VALUE_3000                 (3000)
 #define USB_VALUE_100U                 (100U)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
static uint16_t  usb_shstd_clr_stall_pipe[USB_NUM_USBIP];
static uint16_t  usb_shstd_clr_stall_request[USB_NUM_USBIP][5];
static usb_utr_t usb_shstd_clr_stall_ctrl[USB_NUM_USBIP];

 #if defined(USB_CFG_HVND_USE)
static usb_er_t usb_hvnd_set_pipe_registration(usb_utr_t * ptr, uint16_t dev_addr);
static void     usb_hvnd_configured(usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2);
static void     usb_hvnd_detach(usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2);
static void     usb_hvnd_enumeration(usb_clsinfo_t * mess, uint16_t ** table);
static void     usb_hvnd_pipe_info(usb_utr_t * p_utr, uint8_t * table, uint16_t speed, uint16_t length);
static uint8_t  usb_hvnd_get_pipe_no(usb_utr_t * p_utr, uint8_t type, uint8_t dir);
static uint8_t  usb_hvnd_make_pipe_reg_info(usb_utr_t            * p_utr,
                                            uint16_t               address,
                                            uint16_t               speed,
                                            uint8_t              * descriptor,
                                            usb_pipe_table_reg_t * pipe_table_work);

 #endif                                /* defined(USB_CFG_HVND_USE) */

static void usb_hstd_set_submitutr(usb_utr_t * ptr);
static void usb_hstd_set_retransfer(usb_utr_t * ptr, uint16_t pipe);

 #if (BSP_CFG_RTOS == 0)
static usb_cb_t usb_shstd_clr_stall_call;
static void usb_hstd_clr_stall_result(usb_utr_t * ptr, uint16_t data1, uint16_t data2);

 #endif                                /* (BSP_CFG_RTOS == 0) */

 #if defined(USB_CFG_OTG_USE)
static void usb_hstd_otg_mode_to_peri(usb_utr_t * p_utr);
static void usb_pdriver_init_otg(void);
extern void usb_pstd_ux_descriptor_to_basic(usb_cfg_t * p_cfg);

extern volatile uint32_t g_usb_open_class[];
extern usb_cfg_t       * g_p_usb_otg_cfg;
extern usb_descriptor_t  g_usbx_descriptor;
 #endif                                /* defined(USB_CFG_OTG_USE) */
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern const uint16_t USB_CFG_TPL_TABLE[];
 #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* Device driver (registration) */
usb_hcdreg_t g_usb_hstd_device_drv[USB_NUM_USBIP][USB_MAXDEVADDR + 1U];

/* Root port, status, config num, interface class, speed, */
volatile uint16_t g_usb_hstd_device_info[USB_NUM_USBIP][USB_MAXDEVADDR + 1U][8U];
uint16_t          g_usb_hstd_remort_port[USB_NUM_USBIP];

/* Control transfer stage management */
uint16_t g_usb_hstd_ctsq[USB_NUM_USBIP];

/* Manager mode */
uint16_t g_usb_hstd_mgr_mode[USB_NUM_USBIP];

/* DEVSEL & DCPMAXP (Multiple device) */
uint16_t g_usb_hstd_dcp_register[USB_NUM_USBIP][USB_MAXDEVADDR + 1U];

/* Device address */
uint16_t g_usb_hstd_device_addr[USB_NUM_USBIP];

/* Reset handshake result */
uint16_t g_usb_hstd_device_speed[USB_NUM_USBIP];

/* Device driver number */
uint16_t g_usb_hstd_device_num[USB_NUM_USBIP];

/* Ignore count */
uint16_t g_usb_hstd_ignore_cnt[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

/* USB data transfer */
/* PIPEn Buffer counter */
uint32_t g_usb_hstd_data_cnt[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];
uint32_t g_usb_hstd_data_cnt_pipe0[USB_NUM_USBIP];

/* PIPEn Buffer pointer(8bit) */
uint8_t * gp_usb_hstd_data_ptr[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

/* Message pipe */
usb_utr_t * g_p_usb_hstd_pipe[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

/* Hi-speed enable */
uint16_t         g_usb_hstd_hs_enable[USB_NUM_USBIP];
usb_ctrl_trans_t g_usb_ctrl_request[USB_NUM_USBIP][USB_MAXDEVADDR + 1];

 #if defined(USB_CFG_OTG_USE)
volatile uint16_t g_usb_otg_intsts1 = 0;
 #endif                                /* defined(USB_CFG_OTG_USE) */

 #if BSP_CFG_RTOS == 0
uint16_t g_usb_hstd_pipe_request[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];
 #endif                                /* BSP_CFG_RTOS == 0 */

 #if defined(USB_CFG_HVND_USE)

/* Target Peripheral List */
const uint16_t g_usb_apl_devicetpl[] =
{
    USB_CFG_TPLCNT,                    /* Number of list */
    0,                                 /* Reserved */
    USB_CFG_TPL                        /* Vendor ID, Product ID */
};
 #endif /* defined(USB_CFG_HVND_USE) */

 #if (BSP_CFG_RTOS != 0)
usb_hdl_t g_usb_hstd_sus_res_task_id[USB_NUM_USBIP];
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

 #if defined(USB_CFG_OTG_USE)
uint8_t g_usb_otg_suspend_flag[USB_NUM_USBIP] =
{
    USB_NO,
  #if USB_NUM_USBIP == 2
    USB_NO,
  #endif                               /* USB_NUM_USBIP == 2 */
};

uint8_t g_is_A_device[USB_NUM_USBIP] =
{
    USB_NO,
  #if USB_NUM_USBIP == 2
    USB_NO,
  #endif                               /* USB_NUM_USBIP == 2 */
};

uint8_t g_is_A_cable_detach[USB_NUM_USBIP] =
{
    USB_NO,
  #if USB_NUM_USBIP == 2
    USB_NO,
  #endif                               /* USB_NUM_USBIP == 2 */
};

extern UINT usb_host_usbx_initialize(UX_HCD * hcd);

 #endif                                /* defined(USB_CFG_OTG_USE) */
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern usb_compliance_cb_t * g_usb_compliance_callback[USB_NUM_USBIP];
 #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Renesas USB Host Driver functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_dev_descriptor
 * Description     : Returns buffer header pointer to fetch device descriptor.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : uint8_t *      : Device Descriptor Pointer
 ******************************************************************************/
uint8_t * usb_hstd_dev_descriptor (usb_utr_t * ptr)
{
    return (uint8_t *) &g_usb_hstd_device_descriptor[ptr->ip];
}

/******************************************************************************
 * End of function usb_hstd_dev_descriptor
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_con_descriptor
 * Description     : Returns buffer header pointer that includes the configuration
 *               : descriptor.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : uint8_t *      : Configuration Descriptor Pointer
 ******************************************************************************/
uint8_t * usb_hstd_con_descriptor (usb_utr_t * ptr)
{
    return (uint8_t *) &g_usb_hstd_config_descriptor[ptr->ip];
}

/******************************************************************************
 * End of function usb_hstd_con_descriptor
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_transfer_start_req
 * Description     : Send a request for data transfer to HCD (Host Control Driver)
 *               : using the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : usb_er_t       : USB_OK/USB_QOVR/USB_ERROR
 ******************************************************************************/
usb_er_t usb_hstd_transfer_start_req (usb_utr_t * ptr)
{
    usb_er_t err;
    uint16_t pipenum;
    uint16_t devsel;
 #if (BSP_CFG_RTOS == 0)
    uint16_t connect_inf;
 #else                                 /* (BSP_CFG_RTOS == 0) */
    usb_utr_t * p_tran_data;
 #endif /* BSP_CFG_RTOS == 0 */

    pipenum = ptr->keyword;

    if (USB_PIPE0 == pipenum)
    {
        devsel = (uint16_t) (ptr->p_setup[4] << USB_DEVADDRBIT);
    }
    else
    {
        /* Get device address from pipe number */
        devsel = usb_hstd_get_devsel(ptr, pipenum);
    }

    if ((USB_DEVICE_0 == devsel) && (USB_PIPE0 != pipenum))
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req not configured %x\n", devsel);

        return USB_ERROR;
    }

    ptr->msghead = (usb_mh_t) USB_NULL;
    ptr->msginfo = USB_MSG_HCD_SUBMITUTR;

    if (USB_MAX_PIPE_NO < pipenum)
    {
        return USB_ERROR;
    }

 #if (BSP_CFG_RTOS == 0)
    if (USB_ON == g_usb_hstd_pipe_request[ptr->ip][pipenum])
    {
        return USB_QOVR;
    }

    /* Pipe Transfer Process check */
    if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
    {
        /* Check PIPE TYPE */
        if (usb_cstd_get_pipe_type(ptr, pipenum) != USB_TYPFIELD_ISO)
        {
            USB_PRINTF1("### usb_hstd_transfer_start_req overlaps %d\n", pipenum);

            return USB_QOVR;
        }
    }

    /* Get device speed from device address */
    connect_inf = usb_hstd_get_dev_speed(ptr, devsel);
    if (USB_NOCONNECT == connect_inf)
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req not connect %x\n", devsel);

        return USB_ERROR;
    }

    /* Send message */
    err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) ptr);
    if (USB_OK == err)
    {
        g_usb_hstd_pipe_request[ptr->ip][pipenum] = USB_ON;
    }
    else
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req snd_msg error (%ld)\n", err);
    }

 #elif (BSP_CFG_RTOS == 1)             /* (BSP_CFG_RTOS == 0) */
    err = USB_PGET_BLK(1, &p_tran_data);
    if (TX_SUCCESS != err)
    {
        return USB_ERROR;
    }

 #elif (BSP_CFG_RTOS == 2)             /* (BSP_CFG_RTOS == 0) */
    p_tran_data = (usb_utr_t *) pvPortMalloc(sizeof(usb_utr_t));
    if (NULL == p_tran_data)
    {
        return USB_ERROR;
    }
 #endif                                /* (BSP_CFG_RTOS == 0) */

 #if (BSP_CFG_RTOS != 0)
    *p_tran_data = *ptr;
    if ((0 != ptr->p_setup) && (USB_PIPE0 == pipenum))
    {
        p_tran_data->setup_data[0] = ptr->p_setup[0];
        p_tran_data->setup_data[1] = ptr->p_setup[1];
        p_tran_data->setup_data[2] = ptr->p_setup[2];
        p_tran_data->setup_data[3] = ptr->p_setup[3];
        p_tran_data->setup_data[4] = ptr->p_setup[4];
        p_tran_data->p_setup       = (uint16_t *) &p_tran_data->setup_data;
    }

  #if (BSP_CFG_RTOS == 1)              /* (BSP_CFG_RTOS == 0) */
    p_tran_data->cur_task_hdl = tx_thread_identify();
  #elif (BSP_CFG_RTOS == 2)            /* (BSP_CFG_RTOS == 0) */
    p_tran_data->cur_task_hdl = xTaskGetCurrentTaskHandle();
  #endif /* (BSP_CFG_RTOS == 2)*/
  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    if (0 != ptr->p_transfer_tx)
    {
        p_tran_data->p_transfer_tx = ptr->p_transfer_tx;
    }
    else
    {
        p_tran_data->p_transfer_tx = 0;
    }

    if (0 != ptr->p_transfer_rx)
    {
        p_tran_data->p_transfer_rx = ptr->p_transfer_rx;
    }
    else
    {
        p_tran_data->p_transfer_rx = 0;
    }
  #endif

    /* Send message */
    err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_tran_data);
    if (USB_OK != err)
    {
  #if (BSP_CFG_RTOS == 1)
        USB_REL_BLK(1, p_tran_data);
  #elif (BSP_CFG_RTOS == 2)            /* (BSP_CFG_RTOS == 1) */
        vPortFree(p_tran_data);
  #endif                               /* (BSP_CFG_RTOS == 1) */
    }
 #endif                                /* (BSP_CFG_RTOS != 0) */

    return err;
}

/******************************************************************************
 * End of function usb_hstd_transfer_start_req
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_device_resume
 * Description     : Send request for RESUME signal output to USB device to MGR task.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 * Argument        : uint16_t  devaddr    : Device Address
 * Return          : none
 ******************************************************************************/
void usb_hstd_device_resume (usb_utr_t * ptr, uint16_t devaddr)
{
    usb_hstd_mgr_snd_mbx(ptr, (uint16_t) USB_MSG_HCD_RESUME, devaddr, (uint16_t) 0U);
}

/******************************************************************************
 * End of function usb_hstd_device_resume
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_hcd_snd_mbx
 * Description     : Send specified message to HCD (Host Control Driver) task.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t  msginfo : Message info..
 *               : uint16_t  dat     : Pipe no.
 *               : uint16_t  *adr    : Address.
 *               : usb_cb_t  callback: Callback function pointer.
 * Return          : usb_er_t          : USB_OK etc.
 ******************************************************************************/
usb_er_t usb_hstd_hcd_snd_mbx (usb_utr_t * ptr, uint16_t msginfo, uint16_t dat, uint16_t * adr, usb_cb_t callback)
{
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_er_t        err2;
    usb_hcdinfo_t * hp;

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_HCD_MPL, &p_blf);
    if (USB_OK == err)
    {
        hp            = (usb_hcdinfo_t *) p_blf;
        hp->msghead   = (usb_mh_t) USB_NULL;
        hp->msginfo   = msginfo;
        hp->keyword   = dat;
        hp->p_tranadr = adr;
        hp->complete  = callback;
        hp->ipp       = ptr->ipp;
        hp->ip        = ptr->ip;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        hp->p_transfer_rx = ptr->p_transfer_rx;
        hp->p_transfer_tx = ptr->p_transfer_tx;
 #endif                                /* #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
 #if (BSP_CFG_RTOS != 0)
        hp->cur_task_hdl = ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

        /* Send message */
        err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) hp);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hHcdSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t) hp);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hHcdSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        /* Error */
        /* WAIT_LOOP */
        while (1)
        {
            /* error */
        }
    }

    return err;
}

/******************************************************************************
 * End of function usb_hstd_hcd_snd_mbx
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_mgr_snd_mbx
 * Description     : Send the message to MGR(Manager) task
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t msginfo  : Message info.
 *               : uint16_t dat      : Port no.
 *               : uint16_t res      : Result
 * Return          : none
 ******************************************************************************/
void usb_hstd_mgr_snd_mbx (usb_utr_t * ptr, uint16_t msginfo, uint16_t dat, uint16_t res)
{
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_er_t        err2;
    usb_mgrinfo_t * mp;

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_MGR_MPL, &p_blf);
    if (USB_OK == err)
    {
        mp          = (usb_mgrinfo_t *) p_blf;
        mp->msghead = (usb_mh_t) USB_NULL;
        mp->msginfo = msginfo;
        mp->keyword = dat;
        mp->result  = res;
        mp->ipp     = ptr->ipp;
        mp->ip      = ptr->ip;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        mp->p_transfer_rx = ptr->p_transfer_rx;
        mp->p_transfer_tx = ptr->p_transfer_tx;
 #endif
 #if (BSP_CFG_RTOS != 0)
        mp->cur_task_hdl = ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS != 0)*/

        /* Send message */
        err = USB_SND_MSG(USB_MGR_MBX, (usb_msg_t *) mp);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hMgrSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_MGR_MPL, (usb_mh_t) mp);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hMgrSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        /* Error */
        /* WAIT_LOOP */
        while (1)
        {
            /* error */
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_mgr_snd_mbx
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_hcd_rel_mpl
 * Description     : Release the secured memory block.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t n        : Error no.
 * Return          : none
 ******************************************************************************/
void usb_hstd_hcd_rel_mpl (usb_utr_t * ptr, uint16_t n)
{
    usb_er_t err;

    (void) n;

    /* Memory Pool Release */
    err = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t) ptr);
    if (USB_OK != err)
    {
        USB_PRINTF1("### USB HCD rel_blk error: %d\n", n);
    }
}

/******************************************************************************
 * End of function usb_hstd_hcd_rel_mpl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_suspend
 * Description     : Request suspend for USB device.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hstd_suspend (usb_utr_t * ptr)
{
    usb_hcdinfo_t * hp;

    /* Control transfer idle stage ? */
    if (USB_IDLEST == g_usb_hstd_ctsq[ptr->ip])
    {
        /* USB suspend process */
        usb_hstd_suspend_process(ptr);
        usb_hstd_chk_clk(ptr, (uint16_t) USB_SUSPENDED); /* Check clock */
        hp = (usb_hcdinfo_t *) ptr;                      /* Callback */
        (hp->complete)(ptr, USB_NULL, ptr->msginfo);
    }
    else
    {
        /* 1ms wait */
        usb_cpu_delay_xms((uint16_t) 1);

        /* Change device state request */
        usb_hstd_hcd_snd_mbx(ptr, ptr->msginfo, USB_NULL, (uint16_t *) 0, &usb_hstd_status_result);
    }
}

/******************************************************************************
 * End of function usb_hstd_suspend
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_submitutr
 * Description     : Submit utr: Get the device address via the specified pipe num-
 *               : ber and do a USB transfer.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
static void usb_hstd_set_submitutr (usb_utr_t * ptr)
{
    uint16_t    pipenum;
    uint16_t    devsel;
    uint16_t    connect_inf;
    uint16_t    end_flag;
    usb_utr_t * pp;

    pipenum = ptr->keyword;
 #if BSP_CFG_RTOS == 0
    g_p_usb_hstd_pipe[ptr->ip][pipenum]       = ptr;
    g_usb_hstd_pipe_request[ptr->ip][pipenum] = USB_OFF;
 #endif                                /* BSP_CFG_RTOS == 0 */

    /* Get device address from pipe number */
    if (USB_PIPE0 == pipenum)
    {
        devsel = (uint16_t) (ptr->p_setup[4] << USB_DEVADDRBIT);
    }
    else
    {
        /* Get device address from pipe number */
        devsel = usb_hstd_get_devsel(ptr, pipenum);
    }

    /* Get device speed from device address */
    connect_inf = usb_hstd_get_dev_speed(ptr, devsel);
    if (USB_NOCONNECT == connect_inf)
    {
 #if (BSP_CFG_RTOS != 0)
        if (USB_PIPE0 == pipenum)
        {
            usb_cstd_pipe0_msg_clear(ptr, ptr->p_setup[4]);
        }
        else
        {
            usb_cstd_pipe_msg_clear(ptr, pipenum);
        }

 #else                                 /* #if (BSP_CFG_RTOS != 0) */
        if (USB_PIPE0 == pipenum)
        {
            /* Control Read/Write End */
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
        }
        else
        {
            /* End of data transfer (IN/OUT) */
            usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_ERR);
        }
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

        return;
    }

 #if (BSP_CFG_RTOS != 0)

    /* Pipe Transfer Process check */
    if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
    {
        if (USB_PIPE0 == pipenum)
        {
            usb_cstd_pipe0_msg_forward(ptr, ptr->p_setup[4]);
        }
        else
        {
            usb_cstd_pipe_msg_forward(ptr, pipenum);
        }

        return;
    }
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

 #if (BSP_CFG_RTOS != 0)
    g_p_usb_hstd_pipe[ptr->ip][pipenum] = ptr;
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

    if ((USB_DEVICE_0 == devsel) && (USB_PIPE0 != pipenum))
    {
        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_ERR);

        return;
    }

    /* Control Transfer */
    if (USB_PIPE0 == pipenum)
    {
        /* Control transfer idle stage ? */
        if (USB_IDLEST == g_usb_hstd_ctsq[ptr->ip])
        {
            usb_hstd_setup_start(ptr);
        }
        /* Control Read Data */
        else if (USB_DATARDCNT == g_usb_hstd_ctsq[ptr->ip])
        {
            pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];
            usb_hstd_ctrl_read_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr); /* Control read start */
        }
        /* Control Write Data */
        else if (USB_DATAWRCNT == g_usb_hstd_ctsq[ptr->ip])
        {
            pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

            /* Control write start */
            end_flag = usb_hstd_ctrl_write_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr);
            if (USB_FIFOERROR == end_flag)
            {
                USB_PRINTF0("### FIFO access error \n");
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR); /* Control Read/Write End */
            }
        }
        else
        {
            USB_PRINTF0("### Control transfer sequence error \n");

            /* Control Read/Write End */
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
        }
    }
    else
    {
        usb_hstd_set_retransfer(ptr, pipenum); /* Data Transfer */
    }
}

/******************************************************************************
 * End of function usb_hstd_set_submitutr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_retransfer
 * Description     : Start IN/OUT transfer based on the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t  pipe : Pipe number
 * Return          : none
 ******************************************************************************/
static void usb_hstd_set_retransfer (usb_utr_t * ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Data Transfer */
    if (usb_cstd_get_pipe_dir(ptr, pipe) == USB_DIR_H_IN)
    {
        /* IN Transfer */
        usb_hstd_receive_start(ptr, pipe);
    }
    else
    {
        /* OUT Transfer */
        usb_hstd_send_start(ptr, pipe);
    }
}

/******************************************************************************
 * End of function usb_hstd_set_retransfer
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_bus_int_disable
 * Description     : Disable USB Bus Interrupts OVRCR, ATTCH, DTCH, and BCHG.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hstd_bus_int_disable (usb_utr_t * ptr)
{
    /* ATTCH interrupt disable */
    usb_hstd_attch_disable(ptr);

    /* DTCH     interrupt disable */
    usb_hstd_dtch_disable(ptr);

    /* BCHG     interrupt disable */
    usb_hstd_bchg_disable(ptr);
}

/******************************************************************************
 * End of function usb_hstd_bus_int_disable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_interrupt
 * Description     : Execute appropriate process depending on which USB interrupt
 *               : occurred.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
static void usb_hstd_interrupt (usb_utr_t * ptr)
{
    uint16_t    intsts;
    uint16_t    end_flag;
    usb_utr_t * pp;
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    usb_compliance_t disp_param;
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

    intsts = ptr->keyword;

    /*    bitsts = ptr->status;*/
    switch (intsts)
    {
        /***** Processing PIPE0-MAX_PIPE_NO data *****/
        case USB_INT_BRDY:
        {
            usb_hstd_brdy_pipe(ptr);
            break;
        }

        case USB_INT_BEMP:
        {
            usb_hstd_bemp_pipe(ptr);
            break;
        }

        case USB_INT_NRDY:
        {
            usb_hstd_nrdy_pipe(ptr);
            break;
        }

        /***** Processing Setup transaction *****/
        case USB_INT_SACK:
        {
            switch (g_usb_hstd_ctsq[ptr->ip])
            {
                case USB_SETUPRD:

                /* Next stage to Control read data */
                /* continue */
                case USB_SETUPRDCNT:
                {
                    /* Next stage to Control read data */
                    pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

                    /* Control read start */
                    usb_hstd_ctrl_read_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr);
                    break;
                }

                case USB_SETUPWR:

                /* Next stage to Control Write data */
                /* continue */
                case USB_SETUPWRCNT:
                {
                    /* Next stage to Control Write data */
                    pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

                    /* Control write start */
                    end_flag = usb_hstd_ctrl_write_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr);
                    if (USB_FIFOERROR == end_flag)
                    {
                        USB_PRINTF0("### FIFO access error \n");

                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
                    }

                    break;
                }

                case USB_SETUPNDC:
                {
                    /* Next stage to Control write no data */
                    usb_hstd_status_start(ptr);
                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        case USB_INT_SIGN:
        {
            USB_PRINTF0("***SIGN\n");
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
            disp_param.status = USB_COMPLIANCETEST_SETUP_ERR;
            disp_param.pid    = USB_NULL;
            disp_param.vid    = USB_NULL;
            (*g_usb_compliance_callback[ptr->ip])((void *) &disp_param);
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            /* Ignore count */
            g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]++;
            USB_PRINTF2("### IGNORE Pipe %d is %d times (Setup) \n",
                        USB_PIPE0,
                        g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]);
            if (USB_PIPEERROR == g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0])
            {
                /* Setup Device Ignore count over */
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
            }
            else
            {
                /* Interrupt enable */
                /* 5ms wait */
                usb_cpu_delay_xms((uint16_t) 5U);

                /* Status Clear */
                hw_usb_hclear_sts_sign(ptr);
                hw_usb_hclear_sts_sack(ptr);

                /* Setup Ignore,Setup Acknowledge enable */
                hw_usb_hset_enb_signe(ptr);
                hw_usb_hset_enb_sacke(ptr);

                /* SETUP request send */
                /* Send SETUP request */
                hw_usb_hset_sureq(ptr);
            }

            break;
        }

        /***** Processing rootport0 *****/
        case USB_INT_OVRCR0:
        {
 #if !defined(USB_CFG_OTG_USE)

            /* Port0 OVCR interrupt function */
            usb_hstd_ovrcr0function(ptr);
 #endif                                /* !defined(USB_CFG_OTG_USE)*/
            break;
        }

        case USB_INT_EOFERR0:
        {
            /* User program */
            break;
        }

        case USB_INT_ATTCH0:
        {
            /* Port0 ATCH interrupt function */
            usb_hstd_attach_process(ptr);
 #if defined(USB_CFG_OTG_USE)
            (*g_p_otg_callback[ptr->ip])(UX_OTG_MODE_HOST);
 #endif                                /* defined(USB_CFG_OTG_USE) */
            break;
        }

        case USB_INT_BCHG0:
        {
            USB_PRINTF0("BCHG int port0\n");
 #if defined(USB_CFG_OTG_USE)
            ptr->ipp->INTENB1 &= (uint16_t) ~USB_BCHGE;
            ptr->ipp->INTENB1 |= USB_ATTCHE;
            hw_usb_set_vbout(ptr);
 #else

            /* Port0 BCHG interrupt function */
            usb_hstd_bchg0function(ptr);
 #endif
            break;
        }

        case USB_INT_DTCH0:
        {
            USB_PRINTF0("DTCH int port0\n");
 #if defined(USB_CFG_OTG_USE)
            {
                CHAR      * p_name;
                UINT        state;
                ULONG       run_count;
                UINT        priority;
                UINT        threshold;
                ULONG       time_slice;
                TX_THREAD * p_thread;
                TX_THREAD * p_next_thread;
                TX_THREAD * p_suspend_thread;

                p_thread = &_ux_system_host->ux_system_host_hnp_polling_thread;
                tx_thread_info_get(p_thread,
                                   &p_name,
                                   &state,
                                   &run_count,
                                   &priority,
                                   &threshold,
                                   &time_slice,
                                   &p_next_thread,
                                   &p_suspend_thread);
                if ((TX_READY == state) || (TX_SLEEP == state) || (TX_SEMAPHORE_SUSP == state))
                {
                    tx_thread_terminate(p_thread);
                    tx_thread_reset(p_thread);
                }
            }

            if (USB_ON == g_usb_otg_hnp_process[ptr->ip])
            {
                /* USB detach process */
                usb_hstd_detach_process(ptr);

                usb_hstd_otg_mode_to_peri(ptr);

                g_usb_usbmode[ptr->ip] = USB_MODE_PERI;

                (*g_p_otg_callback[ptr->ip])(UX_OTG_MODE_SLAVE);

                if (USB_YES == g_is_A_device[ptr->ip])
                {
                    if (USB_IP0 == ptr->ip)
                    {
                        tx_timer_activate(&g_usb_otg_detach_timer);
                    }

  #if USB_NUM_USBIP == 2
                    else
                    {
                        tx_timer_activate(&g_usb2_otg_detach_timer);
                    }
  #endif                               /* USB_NUM_USBIP == 2 */
                }

                g_usb_otg_hnp_process[ptr->ip] = USB_OFF;
            }
            else
 #endif                                /* defined(USB_CFG_OTG_USE) */
            {
                /* USB detach process */
                usb_hstd_detach_process(ptr);
 #if defined(USB_CFG_OTG_USE)
                if (USB_YES == g_is_A_device[ptr->ip])
                {
                    if (USB_YES == g_is_A_cable_detach[ptr->ip])
                    {
                        g_is_A_cable_detach[ptr->ip] = USB_NO;
                        usb_hstd_otg_mode_to_peri(ptr);
                        g_is_A_device[ptr->ip] = USB_NO;
                        _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE;
                    }
                    else
                    {
                        _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_A;
                    }
                }
                else
                {
                    /* Detached B-cable */
                    usb_hstd_otg_mode_to_peri(ptr);
                    _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE;
                }
                (*g_p_otg_callback[ptr->ip])(UX_OTG_MODE_IDLE);
 #endif                                /* defined(USB_CFG_OTG_USE) */
            }

            break;
        }

 #if USB_CFG_BC == USB_CFG_ENABLE
        case USB_INT_PDDETINT0:
        {
  #if defined(USB_HIGH_SPEED_MODULE)

            /* Port0 PDDETINT interrupt function */
            if (USB_IP1 == ptr->ip)
            {
                usb_hstd_pddetint_process(ptr);
            }
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
            break;
        }
 #endif                                /* USB_CFG_BC == USB_CFG_ENABLE */

        case USB_INT_VBINT:
        {
            /* User program */
            hw_usb_clear_enb_vbse(ptr);
            break;
        }

        case USB_INT_SOFR:
        {
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
            g_usb_hstd_response_counter[ptr->ip]++;
            if (USB_RESPONCE_COUNTER_VALUE == g_usb_hstd_response_counter[ptr->ip])
            {
                hw_usb_clear_enb_sofe(ptr);
                disp_param.status = USB_COMPLIANCETEST_NORES;
                disp_param.pid    = USB_NULL;
                disp_param.vid    = USB_NULL;
                (*g_usb_compliance_callback[ptr->ip])((void *) &disp_param);
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_STOP);
            }

 #else                                 /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            /* User program */
            hw_usb_clear_enb_sofe(ptr);
 #endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            break;
        }

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        case USB_INT_DXFIFO:
        {
            usb_cstd_dma_stop(ptr, ptr->status); /* Stop DMA,FIFO access */
            usb_cstd_dma_send_continue(ptr, ptr->status);
            break;
        }
 #endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

 #if (BSP_CFG_RTOS == 1)
  #if defined(USB_CFG_OTG_USE)
        case USB_INT_OTG_HOST_INIT:
        {
            usb_class_internal_t type;

            ptr->ipp = usb_hstd_get_usb_ip_adr((uint16_t) ptr->ip);

            if (USB_MODE_PERI == g_usb_usbmode[ptr->ip])
            {
/**********************************/
/* Peri UninItialization Processing */
/**********************************/
                usb_module_register_clear(ptr->ip);

                usb_pstd_driver_release(); /* Clear the information registered in the structure usb_pcdreg_t. */
                usb_pstd_clr_pipe_table(ptr->ip);

/**********************************/
/* Host InItialization Processing */
/**********************************/
                usb_hdriver_init(ptr);

                /* Setting USB relation register  */
                hw_usb_hmodule_init(ptr->ip); /* MCU */

   #if USB_CFG_TYPEC == USB_CFG_DISABLE
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBON);
    #if USB_CFG_BC == USB_CFG_DISABLE
                usb_cpu_delay_xms((uint16_t) USB_VALUE_100U); /* 100ms wait */
    #endif /*  USB_CFG_BC == USB_CFG_DISABLE */
   #else /*  USB_CFG_TYPEC == USB_CFG_DISABLE */
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBOFF);
   #endif /*  USB_CFG_TYPEC == USB_CFG_DISABLE */

   #if defined(USB_CFG_HCDC_USE)
                ux_host_stack_class_register(_ux_system_host_class_cdc_acm_name, ux_host_class_cdc_acm_entry);
                if (USB_IP1 == ptr->ip)
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hcdc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE,
                                               0);
                }
                else
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hcdc_fs", usb_host_usbx_initialize, R_USB_FS0_BASE,
                                               0);
                }
                type = USB_CLASS_INTERNAL_HCDC;
   #endif                              /* defined(USB_CFG_HCDC_USE) */
   #if defined(USB_CFG_HMSC_USE)
                ux_host_stack_class_register(_ux_system_host_class_storage_name, ux_host_class_storage_entry);
                if (USB_IP1 == ptr->ip)
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hmsc_hs", usb_host_usbx_initialize, R_USB_HS0_BASE,
                                               0);
                }
                else
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hmsc_fs", usb_host_usbx_initialize, R_USB_FS0_BASE,
                                               0);
                }
                type = USB_CLASS_INTERNAL_HMSC;
   #endif                              /* defined(USB_CFG_HMSC_USE) */
   #if defined(USB_CFG_HHID_USE)
                ux_host_stack_class_register(_ux_system_host_class_hid_name, ux_host_class_hid_entry);

                ux_host_class_hid_client_register(_ux_system_host_class_hid_client_keyboard_name,
                                                  ux_host_class_hid_keyboard_entry);
                ux_host_class_hid_client_register(_ux_system_host_class_hid_client_mouse_name,
                                                  ux_host_class_hid_mouse_entry);

                if (USB_IP1 == ptr->ip)
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hhid_hs", usb_host_usbx_initialize, R_USB_HS0_BASE,
                                               0);
                }
                else
                {
                    ux_host_stack_hcd_register((UCHAR *) "fsp_usbx_hhid_fs", usb_host_usbx_initialize, R_USB_FS0_BASE,
                                               0);
                }
                type = USB_CLASS_INTERNAL_HHID;
   #endif                                                                         /* defined(USB_CFG_HHID_USE) */

                g_usb_open_class[ptr->ip] |= (uint16_t) (1 << type);              /* Set USB Open device class */
                if (USB_CLASS_INTERNAL_HCDC == type)
                {
                    g_usb_open_class[ptr->ip] |= (1 << USB_CLASS_INTERNAL_HCDCC); /* Set USB Open device class */
                }

                g_is_A_device[ptr->ip] = USB_YES;
                _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_A;
                g_usb_usbmode[ptr->ip] = USB_MODE_HOST;
                (*g_p_otg_callback[ptr->ip])(UX_OTG_MODE_HOST);
                while (1)
                {
                    if ((ptr->ipp->INTSTS1 & USB_ATTCH) == USB_ATTCH)
                    {
                        break;
                    }
                }

                ptr->ipp->INTENB1 &= (uint16_t) (~(uint16_t) USB_ATTCHE);
                ptr->ipp->INTENB1 |= (uint16_t) (USB_ATTCHE);
            }

            break;
        }
  #endif                               /* defined(USB_CFG_OTG_USE) */
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

        /*** ERROR ***/
        case USB_INT_UNKNOWN:
        {
            USB_PRINTF0("hINT_UNKNOWN\n");
            break;
        }

        default:
        {
            USB_PRINTF1("hINT_default %X\n", intsts);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_interrupt
 ******************************************************************************/

 #if defined(USB_CFG_OTG_USE)

/******************************************************************************
 * Function Name   : usb_hstd_otg_mode_to_peri
 * Description     : Initialize regsister and driver from USB Host to USB Peripheral
 * Arguments       : usb_utr_t *p_utr: Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
static void usb_hstd_otg_mode_to_peri (usb_utr_t * p_utr)
{
    p_utr->ipp = usb_hstd_get_usb_ip_adr(p_utr->ip); /* Get the USB IP base address. */

    /* Host Uinitialization */
    usb_module_register_clear(p_utr->ip);

    usb_hstd_clr_pipe_table(p_utr->ip, USB_ADDRESS1);

    usb_pdriver_init_otg();

    /* D+ Pullup Off */
    hw_usb_pclear_dprpu(p_utr->ip);

    /* D+ Pulldown Off */
    hw_usb_clear_drpd(p_utr);

    /* Change to Peri mode */
    hw_usb_clear_dcfm(p_utr);

    /* D+ Pullup On */
    hw_usb_pset_dprpu(p_utr->ip);

    g_usb_usbmode[p_utr->ip]          = USB_MODE_PERI;
    g_usb_otg_suspend_flag[p_utr->ip] = USB_NO;

    p_utr->ipp->INTENB0 = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);
}

/******************************************************************************
 * Function Name   : usb_pdriver_init_otg
 * Description     : Initialize driver from USB Host to USB Peripheral
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pdriver_init_otg (void)
{
    uint16_t            i;
    usb_cfg_t           cfg_usbx;
    usb_instance_ctrl_t ctrl_usbx;

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAX_EP_NO + 1); i++)
    {
        g_usb_pstd_eptbl_index[0][i] = 0;
        g_usb_pstd_eptbl_index[1][i] = 0;
    }

    /* WAIT_LOOP */
    for (i = 0; i < USB_ALT_NO; i++)
    {
        g_usb_pstd_alt_num[i] = 0;
    }

    g_usb_pstd_test_mode_select = USB_NULL;
    g_usb_pstd_req_type         = USB_NULL;
    g_usb_pstd_req_value        = USB_NULL;
    g_usb_pstd_req_index        = USB_NULL;
    g_usb_pstd_req_length       = USB_NULL;
    g_usb_pstd_pipe0_request    = USB_OFF;
    g_usb_pstd_std_request      = USB_NO;
    g_usb_peri_connected        = USB_FALSE;
    memset((void *) &g_usb_pstd_req_reg, 0, sizeof(usb_setup_t));
    g_usb_pstd_stall_cb = USB_NULL;
    memset((void *) &g_usb_pstd_driver, 0, sizeof(usb_pcdreg_t));

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAX_PIPE_NO + 1); i++)
    {
        gp_usb_pstd_data[i]    = USB_NULL;
        g_usb_pstd_data_cnt[i] = 0;
    }

    /* WAIT_LOOP */
    for (i = 0; i < USB_EVENT_MAX; i++)
    {
  #if (BSP_CFG_RTOS == 0)
        g_usb_cstd_event.code[i] = USB_STATUS_NONE;
  #else                                /*(BSP_CFG_RTOS == 0)*/
        g_usb_cstd_event[i].event = USB_STATUS_NONE;
  #endif /*(BSP_CFG_RTOS == 0)*/
    }

    /* WAIT_LOOP */
    for (i = USB_PIPE0; i <= USB_MAX_PIPE_NO; i++)
    {
        g_usb_pstd_stall_pipe[i] = USB_FALSE;
        g_p_usb_pstd_pipe[i]     = (usb_utr_t *) USB_NULL;
    }

    g_usb_pstd_config_num    = 0;         /* Configuration number */
    g_usb_pstd_remote_wakeup = USB_FALSE; /* Remote wake up enable flag */

    cfg_usbx           = *g_p_usb_otg_cfg;
    cfg_usbx.p_usb_reg = &g_usbx_descriptor;
    usb_pstd_ux_descriptor_to_basic(&cfg_usbx);
    usb_peri_registration(&ctrl_usbx, &cfg_usbx);
}

 #endif                                /* defined(USB_CFG_OTG_USE) */

/******************************************************************************
 * Function Name   : usb_hstd_clr_feature
 * Description     : Send ClearFeature command to the connected USB device.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t addr     : Device address.
 *               : uint16_t epnum    : Endpoint number.
 *               : usb_cb_t complete : Callback function.
 * Return value    : uint16_t          : Error info.
 ******************************************************************************/
usb_er_t usb_hstd_clr_feature (usb_utr_t * ptr, uint16_t addr, uint16_t epnum, usb_cb_t complete)
{
    usb_er_t ret_code;

    if (USB_VALUE_FFH == epnum)
    {
        /* ClearFeature(Device) */
        usb_shstd_clr_stall_request[ptr->ip][0] = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
        usb_shstd_clr_stall_request[ptr->ip][1] = USB_DEV_REMOTE_WAKEUP;
        usb_shstd_clr_stall_request[ptr->ip][2] = (uint16_t) 0x0000;
    }
    else
    {
        /* ClearFeature(endpoint) */
        usb_shstd_clr_stall_request[ptr->ip][0] = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_ENDPOINT;
        usb_shstd_clr_stall_request[ptr->ip][1] = USB_ENDPOINT_HALT;
        usb_shstd_clr_stall_request[ptr->ip][2] = epnum;
    }

    usb_shstd_clr_stall_request[ptr->ip][3] = (uint16_t) 0x0000;
    usb_shstd_clr_stall_request[ptr->ip][4] = addr;

    usb_shstd_clr_stall_ctrl[ptr->ip].p_tranadr = USB_NULL;
    usb_shstd_clr_stall_ctrl[ptr->ip].complete  = complete;
    usb_shstd_clr_stall_ctrl[ptr->ip].tranlen   = 0;
    usb_shstd_clr_stall_ctrl[ptr->ip].keyword   = USB_PIPE0;
    usb_shstd_clr_stall_ctrl[ptr->ip].p_setup   = usb_shstd_clr_stall_request[ptr->ip];
    usb_shstd_clr_stall_ctrl[ptr->ip].segment   = USB_TRAN_END;

    usb_shstd_clr_stall_ctrl[ptr->ip].ip  = ptr->ip;
    usb_shstd_clr_stall_ctrl[ptr->ip].ipp = ptr->ipp;

    ret_code = usb_hstd_transfer_start_req(&usb_shstd_clr_stall_ctrl[ptr->ip]);

 #if (BSP_CFG_RTOS != 0)
    if (USB_QOVR == ret_code)
    {
        /** Submit overlap error **/
        /** Retry **/
        /* WAIT_LOOP */
        do
        {
            usb_cpu_delay_xms((uint16_t) 2);
            ret_code = usb_hstd_transfer_start(&usb_shstd_clr_stall_ctrl[ptr->ip]);
        } while (USB_QOVR == ret_code);
    }

    if (USB_OK == ret_code)
    {
        ret_code = class_trans_wait_tmo(ptr, (uint16_t) USB_VALUE_3000);
    }
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

    return ret_code;
}

/******************************************************************************
 * End of function usb_hstd_clr_feature
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_clr_stall
 * Description     : Clear Stall
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t pipe        : Pipe number.
 *               : usb_cb_t complete    : Callback function
 * Return value    : uint16_t             : Error info.
 ******************************************************************************/
usb_er_t usb_hstd_clr_stall (usb_utr_t * ptr, uint16_t pipe, usb_cb_t complete)
{
    usb_er_t err;
    uint8_t  dir_ep;
    uint16_t devsel;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR;              /* Error */
    }

    dir_ep = usb_hstd_pipe_to_epadr(ptr, pipe);
    devsel = usb_hstd_get_device_address(ptr, pipe);

    err = usb_hstd_clr_feature(ptr, (uint16_t) (devsel >> USB_DEVADDRBIT), (uint16_t) dir_ep, complete);
 #if (BSP_CFG_RTOS != 0)
    if (USB_OK == err)
    {
        usb_cstd_clr_stall(ptr, usb_shstd_clr_stall_pipe[ptr->ip]);
        hw_usb_set_sqclr(ptr, usb_shstd_clr_stall_pipe[ptr->ip]); /* SQCLR */
    }
 #endif /* #if (BSP_CFG_RTOS != 0) */

    return err;
}                                      /* End of function usb_hstd_clr_stall() */

/******************************************************************************
 * End of function usb_hstd_clr_stall
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hstd_clr_stall_result
 * Description     : Callback function to notify HCD task that usb_hstd_clr_stall function is completed
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data1  : Not Use
 *               : uint16_t  data2  : Not Use
 * Return value    : none
 ******************************************************************************/
static void usb_hstd_clr_stall_result (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_mh_t    p_blf;
    usb_er_t    err;
    usb_er_t    err2;
    usb_utr_t * up;

    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_HCD_MPL, &p_blf);
    if (USB_OK == err)
    {
        up          = (usb_utr_t *) p_blf;
        up->msghead = (usb_mh_t) USB_NULL;
        up->msginfo = USB_MSG_HCD_CLR_STALL_RESULT;
        up->status  = ptr->status;

        up->ipp = ptr->ipp;
        up->ip  = ptr->ip;

        /* Send message */
        err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_blf);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hHcdSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t) p_blf);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hHcdSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        /* Error */
        /* WAIT_LOOP */
        while (1)
        {
            /* error */
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_clr_stall_result
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hstd_hcd_task
 * Description     : USB Host Control Driver Task.
 * Argument        : usb_vp_int_t stacd  : Task Start Code.
 * Return          : none
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 1)
void usb_hstd_hcd_task (ULONG entry_input)
 #else                                 /* #if (BSP_CFG_RTOS == 1) */
void usb_hstd_hcd_task (void * stacd)
 #endif /* #if (BSP_CFG_RTOS == 1) */
{
    usb_utr_t * p_mess;
    usb_utr_t * ptr;
    usb_er_t    err;
    uint16_t    rootport;
    uint16_t    pipenum;
    uint16_t    msginfo;
    uint16_t    connect_inf;
    uint16_t    result = 0;
 #if (BSP_CFG_RTOS == 0)
    uint16_t retval;
 #endif                                /* (BSP_CFG_RTOS== 0) */
    usb_hcdinfo_t * hp;

 #if (BSP_CFG_RTOS == 1)
    (void) entry_input;
 #else                                 /* #if (BSP_CFG_RTOS == 1) */
    (void) stacd;
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

 #if (BSP_CFG_RTOS != 0)

    /* WAIT_LOOP */
    while (1)
    {
 #endif                                /* #if (BSP_CFG_RTOS != 0) */
    /* Receive message */
    err = USB_TRCV_MSG(USB_HCD_MBX, (usb_msg_t **) &p_mess, (usb_tm_t) 10000);
    if (USB_OK != err)
    {
 #if (BSP_CFG_RTOS != 0)
        result = 1;
 #else                                 /* #if (BSP_CFG_RTOS != 0) */
        result = 2;
 #endif /* #if (BSP_CFG_RTOS != 0) */
    }

    else
    {
        ptr      = p_mess;
        hp       = (usb_hcdinfo_t *) p_mess;
        rootport = ptr->keyword;
        pipenum  = ptr->keyword;

        /* Branch Hcd Task receive Message Command */
        msginfo = ptr->msginfo;
        switch (msginfo)
        {
            case USB_MSG_HCD_INT:
            {
                /* USB INT */
                usb_hstd_interrupt(ptr);
                break;
            }

            case USB_MSG_HCD_SUBMITUTR:
            {
                /* USB Submit utr */
                usb_hstd_set_submitutr(ptr);
                break;
            }

            case USB_MSG_HCD_ATTACH:
            {
                /* USB attach / detach */
                usb_hstd_attach_process(ptr);

                /* Callback */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_ATTACH);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_ATTACH_MGR:
            {
                /* USB attach / detach */
                usb_hstd_attach_process(ptr);
                connect_inf = usb_cstd_port_speed(ptr);

                /* Callback */
                (hp->complete)(ptr, rootport, connect_inf);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_DETACH:
            {
                /* USB detach process */
                usb_hstd_detach_process(ptr);

                /* Callback */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_DETACH);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_DETACH_MGR:
            {
                hw_usb_clear_dvstctr(ptr, (USB_RWUPE | USB_USBRST | USB_RESUME | USB_UACT));
                usb_cpu_delay_xms(1);

                /* interrupt disable */
                usb_hstd_attch_disable(ptr);
                usb_hstd_dtch_disable(ptr);
                usb_hstd_bchg_disable(ptr);
                (hp->complete)(ptr, USB_NULL, USB_MSG_HCD_DETACH_MGR);
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_USBRESET:
            {
                /* USB bus reset */
                usb_hstd_bus_reset(ptr);

                /* Check current port speed */
                connect_inf = usb_cstd_port_speed(ptr);

                /* Callback */
                (hp->complete)(ptr, USB_NULL, connect_inf);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_REMOTE:
            {
                /* Suspend device */
                g_usb_hstd_remort_port[ptr->ip] = USB_SUSPENDED;
                usb_hstd_suspend(ptr);

                /* CallBack */
                (hp->complete)(ptr, USB_NULL, USB_MSG_HCD_REMOTE);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_SUSPEND:
            {
                usb_hstd_suspend(ptr);              /* Suspend device */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_SUSPEND);
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
                break;
            }

 #if defined(USB_CFG_OTG_USE)
            case USB_MSG_HCD_OTG_SUSPEND:
            {
                ptr->ipp = usb_hstd_get_usb_ip_adr(ptr->ip); /* Get the USB IP base address. */
                hw_usb_hclear_uact(ptr);
                usb_hstd_hcd_rel_mpl(ptr, msginfo);          /* Release Memory Block */
                break;
            }
 #endif /* defined(USB_CFG_OTG_USE) */

            case USB_MSG_HCD_RESUME:
            {
                usb_hstd_resume_process(ptr);                      /* USB resume */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_RESUME); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_VBON:
            {
                usb_hstd_ovrcr_enable(ptr);                      /* Interrupt Enable */
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBON); /* USB VBUS control ON */
 #if USB_CFG_BC == USB_CFG_DISABLE

                /* 100ms wait */
                usb_cpu_delay_xms((uint16_t) USB_VALUE_100U);
 #endif                                                          /* USB_CFG_BC == USB_CFG_DISABLE */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_VBON); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);              /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_VBOFF:
            {
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBOFF); /* USB VBUS control OFF */
                usb_hstd_ovrcr_disable(ptr);
                usb_cpu_delay_xms((uint16_t) USB_VALUE_100U);     /* 100ms wait */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_VBOFF); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);               /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_CLR_STALLBIT:
            {
                usb_cstd_clr_stall(ptr, pipenum);                                                /* STALL */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_CLR_STALLBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                                              /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_SQTGLBIT:
            {
                pipenum = ptr->keyword & USB_PIPENM;
                usb_hstd_do_sqtgl(ptr, pipenum, ptr->keyword);                               /* SQ toggle */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_SQTGLBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                                          /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_CLR_STALL:
            {
 #if (BSP_CFG_RTOS != 0)
                usb_shstd_clr_stall_pipe[ptr->ip] = pipenum;
                err = usb_hstd_clr_stall(ptr, pipenum, (usb_cb_t) &class_trans_result);
                (hp->complete)(ptr, (uint16_t) err, USB_MSG_HCD_CLR_STALL);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
 #else                                 /* #if (BSP_CFG_RTOS != 0) */
                usb_shstd_clr_stall_call          = hp->complete;
                usb_shstd_clr_stall_pipe[ptr->ip] = pipenum;
                err = usb_hstd_clr_stall(ptr, pipenum, (usb_cb_t) &usb_hstd_clr_stall_result);
                if (USB_QOVR == err)
                {
                    USB_WAI_MSG(USB_HCD_MBX, ptr, 1000); /* Retry */
                }
                else
                {
                    /* Release Memory Block */
                    usb_hstd_hcd_rel_mpl(ptr, msginfo);
                }
 #endif                                /* #if (BSP_CFG_RTOS != 0) */
                break;
            }

            case USB_MSG_HCD_CLR_STALL_RESULT:
            {
 #if (BSP_CFG_RTOS != 0)

                /** Do nothing when running in RTOS
                 * The result will be checked immediately after issuing a "USB_MSG_HCD_CLR_STALL" request. **/
 #else                                 /* #if (BSP_CFG_RTOS != 0) */
                ptr    = p_mess;
                retval = ptr->status;

                if (USB_DATA_TMO == retval)
                {
                    USB_PRINTF0("*** Standard Request Timeout error !\n");
                }
                else if (USB_DATA_STALL == retval)
                {
                    USB_PRINTF0("*** Standard Request STALL !\n");
                }
                else if (USB_CTRL_END != retval)
                {
                    USB_PRINTF0("*** Standard Request error !\n");
                }
                else
                {
                    usb_cstd_clr_stall(ptr, usb_shstd_clr_stall_pipe[ptr->ip]);
                    hw_usb_set_sqclr(ptr, usb_shstd_clr_stall_pipe[ptr->ip]); /* SQCLR */
                }

                (*usb_shstd_clr_stall_call)(ptr, retval, USB_MSG_HCD_CLR_STALL);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
 #endif                                /* #if (BSP_CFG_RTOS != 0) */
                break;
            }

            case USB_MSG_HCD_CLRSEQBIT:
            {
                hw_usb_set_sqclr(ptr, pipenum);                                               /* SQCLR */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_CLRSEQBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_SETSEQBIT:
            {
                hw_usb_set_sqset(ptr, pipenum);                                               /* SQSET */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_SETSEQBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                                           /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_TRANSEND1:
            {
                /* Pipe Transfer Process check */
                if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
                {
                    /* Control Transfer stop */
                    if (USB_PIPE0 == pipenum)
                    {
                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_TMO);
                    }
                    else
                    {
                        /* Transfer stop */
                        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_TMO);
                    }
                }
                else
                {
                    USB_PRINTF1("### Host not transfer %d\n", pipenum);
                }

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_TRANSEND2:
            {
                /* Pipe Transfer Process check */
                if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
                {
                    /* Control Transfer stop */
                    if (USB_PIPE0 == pipenum)
                    {
                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_STOP);
                    }
                    else
                    {
                        /* Transfer stop */
                        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_STOP);
                    }
                }
                else
                {
                    USB_PRINTF1("### Host not transfer %d\n", pipenum);
                }

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_D1FIFO_INT:
            {
                break;
            }

            case USB_MSG_HCD_RESM_INT:
            {
                break;
            }

            default:
            {
                break;
            }
        }
    }

 #if (BSP_CFG_RTOS != 0)
    if (result == 1)
    {
        continue;
    }

 #else                                 /* #if (BSP_CFG_RTOS != 0) */
    if (result == 2)
    {
        return;
    }
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

 #if (BSP_CFG_RTOS != 0)
}                                      /* End of while(1) */
 #endif                                /* #if (BSP_CFG_RTOS != 0) */
}

/******************************************************************************
 * End of function usb_hstd_hcd_task
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_send_start
 * Description     : Start data transmission using CPU/DMA transfer to USB host/
 *               : /device.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe no.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_send_start (usb_utr_t * ptr, uint16_t pipe)
{
    usb_utr_t * pp;
    uint32_t    length;
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

    usb_cstd_set_nak(ptr, pipe);                                      /* Select NAK */
    g_usb_hstd_data_cnt[ptr->ip][pipe]   = length;                    /* Set data count */
    gp_usb_hstd_data_ptr[ptr->ip][pipe]  = (uint8_t *) pp->p_tranadr; /* Set data pointer */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;              /* Ignore count clear */

    hw_usb_clear_status_bemp(ptr, pipe);                              /* BEMP Status Clear */
    hw_usb_clear_sts_brdy(ptr, pipe);                                 /* BRDY Status Clear */

    useport = usb_hstd_pipe2fport(ptr, pipe);                         /* Pipe number to FIFO port select */

    /* Check use FIFO access */
    switch (useport)
    {
        case USB_CUSE:                   /* CFIFO use */
        {
            /* Buffer to FIFO data write */
            usb_hstd_buf_to_fifo(ptr, pipe, useport);
            usb_cstd_set_buf(ptr, pipe); /* Set BUF */

            break;
        }

 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

        /* D0FIFO DMA */
        case USB_D0USE:

        /* D1FIFO DMA */
        case USB_D1USE:
        {
            if (USB_IP0 == ptr->ip)
            {
                channel_info = (dmac_extended_cfg_t *) ptr->p_transfer_tx->p_cfg->p_extend;
                dma_ch       = channel_info->channel;
            }
            else
            {
                channel_info = (dmac_extended_cfg_t *) ptr->p_transfer_tx->p_cfg->p_extend;
                dma_ch       = channel_info->channel;
            }

            /* Setting for use PIPE number */
            g_usb_cstd_dma_pipe[ptr->ip][dma_ch] = pipe;

            /* Buffer size */
            g_usb_cstd_dma_fifo[ptr->ip][dma_ch] = usb_cstd_get_buf_size(ptr, pipe);

            /* Check data count */
            if (g_usb_hstd_data_cnt[ptr->ip][pipe] <= g_usb_cstd_dma_fifo[ptr->ip][dma_ch])
            {
                /* Transfer data size */
                g_usb_cstd_dma_size[ptr->ip][dma_ch] = g_usb_hstd_data_cnt[ptr->ip][pipe];

                /* Enable Empty Interrupt */
                hw_usb_set_bempenb(ptr, pipe);
            }
            else
            {
                /* Data size == FIFO size */
                g_usb_cstd_dma_size[ptr->ip][dma_ch] = (g_usb_hstd_data_cnt[ptr->ip][pipe] -
                                                        (g_usb_hstd_data_cnt[ptr->ip][pipe] %
                                                         g_usb_cstd_dma_fifo[ptr->ip][dma_ch]));
            }

            usb_cstd_dma_send_start(ptr, pipe, useport);

            /* Set BUF */
            usb_cstd_set_buf(ptr, pipe);
            break;
        }
 #endif                                /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default:
        {
            /* Access is NG */
            USB_PRINTF1("### USB-ITRON is not support(SND-else:pipe%d)\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_send_start
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_fifo_to_buf
 * Description     : Request readout from USB FIFO to buffer and process depending
 *               : on status; read complete or reading.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe no.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_fifo_to_buf (usb_utr_t * ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag = USB_ERROR;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;

    end_flag = usb_hstd_read_data(ptr, pipe, useport);

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
            usb_hstd_data_end(ptr, pipe, (uint16_t) USB_DATA_OK);

            break;
        }

        case USB_READSHRT:
        {
            /* End of data read */
            usb_hstd_data_end(ptr, pipe, (uint16_t) USB_DATA_SHT);

            break;
        }

        case USB_READOVER:
        {
            /* Buffer over */
            USB_PRINTF1("### Receive data over PIPE%d\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_OVR);

            break;
        }

        case USB_FIFOERROR:
        {
            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

            break;
        }

        default:
        {
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_fifo_to_buf
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_buf_to_fifo
 * Description     : Set USB registers as required to write from data buffer to USB
 *              : FIFO, to have USB FIFO to write data to bus.
 * Arguments       : usb_utr_t    *ptr : Pointer to usb_utr_t structure.
 *              : uint16_t pipe     : Pipe no.
 *              : uint16_t useport  : Port no.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_buf_to_fifo (usb_utr_t * ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(ptr, pipe);

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;

    end_flag = usb_hstd_write_data(ptr, pipe, useport);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_WRITING:
        {
            /* Continue of data write */
            /* Enable Ready Interrupt */
            hw_usb_set_brdyenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);

            break;
        }

        case USB_WRITEEND:

        /* End of data write */
        /* continue */

        case USB_WRITESHRT:
        {
            /* End of data write */
            /* Enable Empty Interrupt */
            hw_usb_set_bempenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);

            break;
        }

        case USB_FIFOERROR:
        {
            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

            break;
        }

        default:
        {
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_buf_to_fifo
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_class_request_complete
 * Description     : Class request transfer complete
 * Arguments       : usb_utr_t *mess  : Pointer to usb_utr_t structure.
 *               : uint16_t  data1  : Not used.
 *               : uint16_t  data2  : Not used.
 * Return          : none
 ******************************************************************************/
void usb_class_request_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) data1;
    (void) data2;

    if (USB_CTRL_END == mess->status)        /* Check usb receive status */
    {
        ctrl.status = USB_SETUP_STATUS_ACK;
    }
    else if (USB_DATA_STALL == mess->status) /* Check usb receive status */
    {
        ctrl.status = USB_SETUP_STATUS_STALL;
    }
    else
    {
        ctrl.status = USB_ERROR;
    }

    ctrl.type                 = USB_CLASS_REQUEST;
    ctrl.module_number        = mess->ip; /* Module number setting */
    ctrl.setup.request_type   = mess->p_setup[0];
    ctrl.pipe                 = USB_PIPE0;
    ctrl.setup.request_value  = mess->p_setup[1];
    ctrl.setup.request_index  = mess->p_setup[2];
    ctrl.setup.request_length = mess->p_setup[3];
    ctrl.device_address       = (uint8_t) mess->p_setup[4];
    ctrl.data_size            = ctrl.setup.request_length - g_usb_hstd_data_cnt_pipe0[mess->ip];
 #if (BSP_CFG_RTOS != 0)
    ctrl.p_data = (void *) mess->cur_task_hdl;
 #endif                                                /* #if (BSP_CFG_RTOS != 0) */

    usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_class_request_complete
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hstd_transfer_end
 * Description     : Request HCD to force termination of data transfer.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t pipe        : Pipe number
 *               : uint16_t status      : Data transfer status
 * Return          : usb_err_t error code : USB_OK etc
 ******************************************************************************/
usb_er_t usb_hstd_transfer_end (usb_utr_t * ptr, uint16_t pipe, uint16_t status)
{
    uint16_t msg;
    usb_er_t err;

  #if (BSP_CFG_RTOS == 0)
    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR;              /* Error */
    }

    if (USB_ON == g_usb_hstd_pipe_request[ptr->ip][pipe])
    {
        return USB_ERROR;
    }
  #endif                               /* (BSP_CFG_RTOS == 0) */

    if (USB_NULL == g_p_usb_hstd_pipe[ptr->ip][pipe])
    {
        USB_PRINTF1("### usb_hstd_transfer_end overlaps %d\n", pipe);

        return USB_QOVR;
    }

    if (USB_DATA_TMO == status)
    {
        msg = USB_MSG_HCD_TRANSEND1;
    }
    else
    {
        msg = USB_MSG_HCD_TRANSEND2;
    }

    err = usb_hstd_hcd_snd_mbx(ptr, msg, pipe, (uint16_t *) 0, &usb_hstd_dummy_function);

    return err;
}

/******************************************************************************
 * End of function usb_hstd_transfer_end
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_hstd_driver_registration
 * Description     : The HDCD information registered in the class driver structure
 *               : is registered in HCD.
 * Arguments       : usb_utr_t *ptr           : Pointer to usb_utr_t structure.
 *               : usb_hcdreg_t *callback   : Pointer to usb_hcdreg_t structure
 * Return          : none
 ******************************************************************************/
void usb_hstd_driver_registration (usb_utr_t * ptr, usb_hcdreg_t * callback)
{
    usb_hcdreg_t * driver;

    if (g_usb_hstd_device_num[ptr->ip] <= USB_MAXDEVADDR)
    {
        driver = &g_usb_hstd_device_drv[ptr->ip][g_usb_hstd_device_num[ptr->ip]];

        driver->rootport   = USB_NOPORT;           /* Root port */
        driver->devaddr    = USB_NODEVICE;         /* Device address */
        driver->devstate   = USB_DETACHED;         /* Device state */
        driver->ifclass    = callback->ifclass;    /* Interface Class */
        driver->p_tpl      = callback->p_tpl;      /* Target peripheral list */
        driver->classinit  = callback->classinit;  /* Driver init */
        driver->classcheck = callback->classcheck; /* Driver check */
        driver->devconfig  = callback->devconfig;  /* Device configured */
        driver->devdetach  = callback->devdetach;  /* Device detach */
        driver->devsuspend = callback->devsuspend; /* Device suspend */
        driver->devresume  = callback->devresume;  /* Device resume */
        /* Initialized device driver */
        (*driver->classinit)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);
        g_usb_hstd_device_num[ptr->ip]++;
        USB_PRINTF1("*** Registration driver 0x%02x\n", driver->ifclass);
    }
}

/******************************************************************************
 * End of function usb_hstd_driver_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_driver_release
 * Description     : Release the Device Class Driver.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint8_t   devclass   : Interface class
 * Return          : none
 ******************************************************************************/
void usb_hstd_driver_release (usb_utr_t * ptr, uint8_t devclass)
{
    usb_hcdreg_t * driver;
    uint16_t       i;
    uint16_t       flg;

    if (USB_IFCLS_NOT == devclass)
    {
        /* Device driver number */
        g_usb_hstd_device_num[ptr->ip] = 0;
    }
    else
    {
        flg = 0U;

        /* WAIT_LOOP */
        for (i = 0U; (i < (USB_MAXDEVADDR + 1U)) && (0U == flg); i++)
        {
            driver = &g_usb_hstd_device_drv[ptr->ip][i];
            if (driver->ifclass == devclass)
            {
                driver->rootport = USB_NOPORT;   /* Root port */
                driver->devaddr  = USB_NODEVICE; /* Device address */
                driver->devstate = USB_DETACHED; /* Device state */

                /* Interface Class : NO class */
                driver->ifclass = (uint16_t) USB_IFCLS_NOT;

                g_usb_hstd_device_num[ptr->ip]--;
                USB_PRINTF1("*** Release class %d driver ***\n", devclass);
                flg = 1U;              /* break; */
            }
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_driver_release
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_pipe_info
 * Description     : Copy information of pipe information table from source
 *               :  (2nd argument) to destination (1st argument)
 * Argument        : usb_pipe_table_t *dst_ep_tbl      : DEF_EP table pointer(destination)
 *               : usb_pipe_table_t *src_ep_tbl      : DEF_EP table pointer(source)
 * Return          : none
 ******************************************************************************/
void usb_hstd_set_pipe_info (uint16_t ip_no, uint16_t pipe_no, usb_pipe_table_reg_t * src_ep_tbl)
{
    g_usb_pipe_table[ip_no][pipe_no].use_flag = USB_TRUE;
    g_usb_pipe_table[ip_no][pipe_no].pipe_cfg = src_ep_tbl->pipe_cfg;
 #if defined(USB_HIGH_SPEED_MODULE)
    if (USB_IP1 == ip_no)
    {
        g_usb_pipe_table[ip_no][pipe_no].pipe_buf = src_ep_tbl->pipe_buf;
    }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    g_usb_pipe_table[ip_no][pipe_no].pipe_maxp = src_ep_tbl->pipe_maxp;
    g_usb_pipe_table[ip_no][pipe_no].pipe_peri = src_ep_tbl->pipe_peri;

 #if BSP_CFG_RTOS == 1
    tx_semaphore_create(&g_usb_host_usbx_sem[ip_no][pipe_no], "USB_FSP_SEMX_HOST", 0);
 #endif
}

/******************************************************************************
 * End of function usb_hstd_set_pipe_info
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hstd_return_enu_mgr
 * Description     : Continuous enumeration is requested to MGR task (API for nonOS)
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t cls_result  : class check result
 * Return          : none
 ******************************************************************************/
void usb_hstd_return_enu_mgr (usb_utr_t * ptr, uint16_t cls_result)
{
    g_usb_hstd_check_enu_result[ptr->ip] = cls_result;
    usb_hstd_mgr_snd_mbx(ptr, USB_MSG_MGR_SUBMITRESULT, USB_PIPE0, USB_CTRL_END);
}

/******************************************************************************
 * End of function usb_hstd_return_enu_mgr
 ******************************************************************************/

 #endif                                /* (BSP_CFG_RTOS == 0) */

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hstd_change_device_state
 * Description     : Request to change the status of the connected USB Device
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : usb_cb_t complete    : callback function pointer
 *               : uint16_t msginfo     : Message Info
 *               : uint16_t member      : Device address/pipe number
 * Return          : usb_err_t            : USB_OK etc
 ******************************************************************************/
usb_er_t usb_hstd_change_device_state (usb_utr_t * ptr, usb_cb_t complete, uint16_t msginfo, uint16_t member)
{
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_er_t        err2;
    usb_hcdinfo_t * hp;

    switch (msginfo)
    {
        /* USB_MSG_HCD_CLR_STALL */
        case USB_DO_CLR_STALL:
        {
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_CLR_STALL, member, (uint16_t *) 0, complete);
            break;
        }

        /* USB_MSG_HCD_SQTGLBIT */
        case USB_DO_SET_SQTGL:
        {
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_SETSEQBIT, member, (uint16_t *) 0, complete);
            break;
        }

        /* USB_MSG_HCD_CLRSEQBIT */
        case USB_DO_CLR_SQTGL:
        {
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_CLRSEQBIT, member, (uint16_t *) 0, complete);
            break;
        }

        default:
        {
            /* Get memory pool blk */
            err = USB_PGET_BLK(USB_MGR_MPL, &p_blf);
            if (FSP_SUCCESS == err)
            {
                USB_PRINTF2("*** member%d : msginfo=%d ***\n", member, msginfo);
                hp           = (usb_hcdinfo_t *) p_blf;
                hp->msghead  = (usb_mh_t) USB_NULL;
                hp->msginfo  = msginfo;
                hp->keyword  = member;
                hp->complete = complete;

                hp->ipp = ptr->ipp;
                hp->ip  = ptr->ip;
  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
                hp->p_transfer_rx = ptr->p_transfer_rx;
                hp->p_transfer_tx = ptr->p_transfer_tx;
  #endif
  #if (BSP_CFG_RTOS == 2)
                hp->cur_task_hdl = xTaskGetCurrentTaskHandle();
  #elif (BSP_CFG_RTOS == 1)            /* #if (BSP_CFG_RTOS == 2) */
                hp->cur_task_hdl = tx_thread_identify();
  #endif                               /* #if (BSP_CFG_RTOS == 2) */

                /* Send message */
                err = USB_SND_MSG(USB_MGR_MBX, (usb_msg_t *) p_blf);
                if (FSP_SUCCESS != err)
                {
                    USB_PRINTF1("### hMgrChangeDeviceState snd_msg error (%ld)\n", err);
                    err2 = USB_REL_BLK(USB_MGR_MPL, (usb_mh_t) p_blf);
                    if (FSP_SUCCESS != err2)
                    {
                        USB_PRINTF1("### hMgrChangeDeviceState rel_blk error (%ld)\n", err2);
                    }
                }
            }
            else
            {
                /* Error */
                /* WAIT_LOOP */
                while (1)
                {
                    /* error */
                }
            }

            break;
        }
    }

    return err;
}

/******************************************************************************
 * End of function usb_hstd_change_device_state
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/***************************************************************************//**
 * @brief Start HCD(Host Control Driver) task
 *
 * @retval FSP_SUCCESS         Success.
 * @retval FSP_ERR_USB_FAILED  Failed in acquiring version information.
 ******************************************************************************/
fsp_err_t usb_hstd_hcd_open (usb_utr_t * ptr)
{
    static uint8_t is_init = USB_NO;
    uint16_t       i;
    uint16_t       j;
    fsp_err_t      err = FSP_SUCCESS;

    if (USB_MAXDEVADDR < USB_DEVICEADDR)
    {
        USB_PRINTF0("Device address error\n");

        /* >yes no process */
        return FSP_ERR_USB_FAILED;
    }

    /* Global Init */
    if (USB_NO == is_init)
    {
 #if (BSP_CFG_RTOS == 0)
        usb_shstd_clr_stall_call = 0;
 #endif                                /* (BSP_CFG_RTOS == 0) */

        usb_shstd_clr_stall_pipe[0] = 0;
        memset((void *) &usb_shstd_clr_stall_ctrl[0], 0, sizeof(usb_utr_t));
        memset((void *) &usb_shstd_clr_stall_request[0], 0, (5 * 2));
 #if (USB_NUM_USBIP == 2)
        usb_shstd_clr_stall_pipe[1] = 0;
        memset((void *) &usb_shstd_clr_stall_ctrl[1], 0, sizeof(usb_utr_t));
        memset((void *) &usb_shstd_clr_stall_request[1], 0, (5 * 2));
 #endif
        is_init = USB_YES;
    }

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAXDEVADDR + 1); i++)
    {
        memset((void *) &g_usb_hstd_device_drv[ptr->ip][i], 0, sizeof(usb_hcdreg_t));
        memset((void *) &g_usb_hstd_device_info[ptr->ip][i], 0, (8 * 2));
        g_usb_hstd_dcp_register[ptr->ip][i] = 0;
        memset((void *) &g_usb_ctrl_request[ptr->ip][i], 0, sizeof(usb_ctrl_trans_t));
    }

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAX_PIPE_NO + 1); i++)
    {
        g_usb_hstd_data_cnt[ptr->ip][i]   = 0;
        gp_usb_hstd_data_ptr[ptr->ip][i]  = 0;
        g_usb_hstd_ignore_cnt[ptr->ip][i] = 0;
 #if (BSP_CFG_RTOS == 0)
        g_usb_hstd_pipe_request[ptr->ip][i] = 0;
 #endif                                /* (BSP_CFG_RTOS == 0) */
    }

    g_usb_hstd_device_addr[ptr->ip]  = 0;
    g_usb_hstd_device_speed[ptr->ip] = 0;
    g_usb_hstd_device_num[ptr->ip]   = 0;

    /* Control transfer stage management */
    g_usb_hstd_ctsq[ptr->ip] = USB_IDLEST;

    g_usb_hstd_remort_port[ptr->ip] = USB_DEFAULT;

    j = ptr->ip;

    /* WAIT_LOOP */
    for (i = USB_PIPE0; i <= USB_MAX_PIPE_NO; i++)
    {
        g_p_usb_hstd_pipe[j][i] = (usb_utr_t *) USB_NULL;
    }

 #if USB_CFG_BC == USB_CFG_ENABLE
  #if defined(USB_HIGH_SPEED_MODULE)
    if (USB_IP1 == ptr->ip)
    {
        g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_INIT;
    }
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
 #endif                                /* USB_CFG_BC == USB_CFG_ENABLE */

    USB_PRINTF0("*** Install USB-HCD ***\n");

    usb_cstd_set_task_pri(USB_HCD_TSK, USB_PRI_1);

    return err;
}

/******************************************************************************
 * End of function usb_hstd_hcd_open
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_dummy_function
 * Description     : Dummy function
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t data1    : Not used.
 *               : uint16_t data2    : Not used.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_dummy_function (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    (void) *ptr;
    (void) data1;
    (void) data2;

    /* None */
}

/******************************************************************************
 * End of function usb_hstd_dummy_function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_suspend_complete
 * Description     : usb_hstd_change_device_state callback (Suspend)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t data1   : Not used.
 *               : uint16_t data2   : Not used.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_suspend_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    usb_cfg_t         * p_cfg = USB_NULL;

    (void) data1;
    (void) data2;

 #if (BSP_CFG_RTOS == 0)
    g_usb_change_device_state[ptr->ip] &= (uint16_t) (~(1 << USB_STATUS_SUSPEND));
 #endif                                /* BSP_CFG_RTOS == 0 */

    ctrl.module_number  = ptr->ip;     /* USB Module Number */
    ctrl.device_address = 1;           /* Device Address Number */
 #if (BSP_CFG_RTOS != 0)
    g_usb_hstd_sus_res_task_id[ptr->ip] = ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

    if (ptr->ip)
    {
 #if defined(USB_HIGH_SPEED_MODULE)
  #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
  #endif                               /* defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME) */
 #else  /* defined(USB_HIGH_SPEED_MODULE) */
  #if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
  #endif                               /* defined(VECTOR_NUMBER_USBFS_INT) */
 #endif /* defined(USB_HIGH_SPEED_MODULE) */
    }
    else
    {
 #if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
 #endif                                /* defined(VECTOR_NUMBER_USBFS_INT) */
    }

    if (USB_NULL != p_cfg)
    {
        ctrl.p_context = (void *) p_cfg->p_context;
    }

    usb_set_event(USB_STATUS_SUSPEND, &ctrl);
}

/******************************************************************************
 * End of function usb_hstd_suspend_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_resume_complete
 * Description     : usb_hstd_change_device_state callback (Resume)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t data1   : Not used.
 *               : uint16_t data2   : Not used.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_resume_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    usb_cfg_t         * p_cfg = USB_NULL;

    (void) data1;
    (void) data2;

 #if (BSP_CFG_RTOS == 0)
    g_usb_change_device_state[ptr->ip] &= (uint16_t) (~(1 << USB_STATUS_RESUME));
 #endif                                /* BSP_CFG_RTOS == 0 */

    ctrl.module_number  = ptr->ip;
    ctrl.device_address = 1;
 #if (BSP_CFG_RTOS != 0)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS != 0) */

    if (ptr->ip)
    {
 #if defined(USB_HIGH_SPEED_MODULE)
  #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
  #endif                               /* defined(USB_HIGH_SPEED_MODULE) */
 #else                                 /* defined(USB_HIGH_SPEED_MODULE) */
  #if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
  #endif                               /* defined(VECTOR_NUMBER_USBFS_INT) */
 #endif                                /* defined(USB_HIGH_SPEED_MODULE) */
    }
    else
    {
 #if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
 #endif                                /* defined(VECTOR_NUMBER_USBFS_INT) */
    }

    if (USB_NULL != p_cfg)
    {
        ctrl.p_context = (void *) p_cfg->p_context;
    }

    usb_set_event(USB_STATUS_RESUME, &ctrl);
}                                      /* End of function usb_hstd_resume_complete */

/******************************************************************************
 * Function Name  : usb_hstd_device_information
 * Description    : Get the status of the connected USB Device
 * Arguments      : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *              : uint16_t devaddr  : Device address
 *              : uint16_t *tbl     : Table Pointer
 * Return         : None
 ******************************************************************************/
void usb_hstd_device_information (usb_utr_t * ptr, uint16_t devaddr, uint16_t * tbl)
{
    uint16_t   i;
    uint16_t   port;
    uint16_t * p;

    if (0 == devaddr)
    {
        p = tbl;
        for (i = 0; i < 8; ++i)
        {
            *p++ = USB_NOPORT;
        }

        port   = g_usb_hstd_device_info[ptr->ip][devaddr][0];
        tbl[0] = port;
        tbl[1] = g_usb_hstd_mgr_mode[ptr->ip];
        tbl[4] = g_usb_hstd_device_info[ptr->ip][devaddr][4];
    }
    else
    {
        for (i = 0; i < 8; ++i)
        {
            tbl[i] = g_usb_hstd_device_info[ptr->ip][devaddr][i];
        }
    }

    tbl[8] = g_usb_hstd_mgr_mode[ptr->ip];
}

/******************************************************************************
 * End of function usb_hstd_device_information
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_host_registration
 * Description     : sample registration.
 * Argument        : usb_utr_t    *ptr   : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_host_registration (usb_utr_t * ptr)
{
    (void) *ptr;

 #if BSP_CFG_RTOS == 1
    usb_host_usbx_registration(ptr);
 #else                                 /* BSP_CFG_RTOS == 1 */
  #if defined(USB_CFG_HCDC_USE)
    usb_hcdc_registration(ptr);
  #endif                               /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_HHID_USE)
    usb_hhid_registration(ptr);
  #endif                               /* defined(USB_CFG_HHID_USE) */

  #if defined(USB_CFG_HMSC_USE)
    usb_hmsc_registration(ptr);
  #endif                               /* defined(USB_CFG_HMSC_USE) */

  #if defined(USB_CFG_HVND_USE)
    usb_hvnd_registration(ptr);
  #endif                               /* defined(USB_CFG_HVND_USE) */
 #endif /* BSP_CFG_RTOS == 1 */
}

/******************************************************************************
 * End of function usb_host_registration
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hstd_transfer_start
 * Description     : Send a request for data transfer to HCD (Host Control Driver)
 *               : using the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : usb_er_t       : USB_OK/USB_QOVR/USB_ERROR
 ******************************************************************************/
usb_er_t usb_hstd_transfer_start (usb_utr_t * ptr)
{
    usb_er_t err;

    /* Check enumeration  */
    if (USB_PIPE0 == ptr->keyword)
    {
        if (USB_DEFAULT == g_usb_hstd_mgr_mode[ptr->ip])
        {
            return USB_QOVR;
        }
    }

    err = usb_hstd_transfer_start_req(ptr);

    return err;
}

/******************************************************************************
 * End of function usb_hstd_transfer_start
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_hstd_connect_err_event_set
 * Description     : Set event for "USB_STS_NOT_SUPPORT"
 * Arguments       : uint16_t ip_no  : IP no.(USB_IP0/USB_IP1)
 * Return          : none
 ******************************************************************************/
void usb_hstd_connect_err_event_set (uint16_t ip_no)
{
    usb_instance_ctrl_t ctrl;

    ctrl.device_address = (uint8_t) g_usb_hstd_device_addr[ip_no]; /* usb device address */
    ctrl.module_number  = (uint8_t) ip_no;                         /* module number setting */
    usb_set_event(USB_STATUS_NOT_SUPPORT, &ctrl);                  /* set event()  */
}

/******************************************************************************
 * End of function usb_hstd_connect_err_event_set
 ******************************************************************************/

 #if defined(USB_CFG_HVND_USE)

/******************************************************************************
 * Function Name   : usb_hvnd_set_pipe_registration
 * Description     : Host CDC pipe registration.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  devadr     : Device address
 * Return          : usb_er_t             : Error info
 ******************************************************************************/
usb_er_t usb_hvnd_set_pipe_registration (usb_utr_t * ptr, uint16_t dev_addr)
{
    usb_er_t err;                      /* Error code */
    uint8_t  pipe_no;

    err = USB_ERROR;

    /* Device address check */
    if (0 != dev_addr)
    {
        /* Search use pipe block */
        /* WAIT_LOOP */
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
        {
            /* Check use block */
            if (USB_TRUE == g_usb_pipe_table[ptr->ip][pipe_no].use_flag)
            {
                /* Check USB Device address */
                if ((uint16_t) (dev_addr << USB_DEVADDRBIT) ==
                    (uint16_t) (g_usb_pipe_table[ptr->ip][pipe_no].pipe_maxp & USB_DEVSEL))
                {
                    usb_hstd_set_pipe_reg(ptr, pipe_no);
                    err = USB_OK;
                }
            }
        }
    }
    else
    {
        /* Error */
        USB_PRINTF1("SmplOpen adr error %x\n", dev_addr);
    }

    return err;
}

/******************************************************************************
 * End of function usb_hvnd_set_pipe_registration()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_configured
 * Description     : Host vendor application initialization.
 * Argument        : usb_utr_t *ptr    : IP info (mode, IP no, reg. address).
 * : uint16_t dev_addr : Device address.
 * : uint16_t data2    : Not used.
 * Return          : none
 ******************************************************************************/
void usb_hvnd_configured (usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2)
{
    (void) data2;

    usb_instance_ctrl_t ctrl;

    ctrl.module_number  = ptr->ip;     /* Module number setting */
    ctrl.device_address = (uint8_t) dev_addr;
    if (0 != dev_addr)
    {
        /* Registration */
        usb_hvnd_set_pipe_registration(ptr, dev_addr); /* Host CDC Pipe registration */
    }

    usb_set_event(USB_STATUS_CONFIGURED, &ctrl);
}

/******************************************************************************
 * End of function usb_hvnd_configured
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_detach
 * Description     : Close host vendor application.
 * Argument        : usb_utr_t *ptr    : IP info (mode, IP no, reg. address).
 * : uint16_t data1            : Not Use
 * : uint16_t data2            : Not Use
 * Return          : none
 ******************************************************************************/
void usb_hvnd_detach (usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2)
{
    (void) data2;

    usb_instance_ctrl_t ctrl;

    usb_hstd_clr_pipe_table(ptr->ip, dev_addr);

    ctrl.module_number  = ptr->ip;     /* Module number setting */
    ctrl.device_address = (uint8_t) dev_addr;
    usb_set_event(USB_STATUS_DETACH, &ctrl);
}

/******************************************************************************
 * End of function usb_hvnd_detach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_enumeration
 * Description     : Vendor class example enumeration execution by host.
 * Argument        : usb_clsinfo_t *mess   : Class info data pointer.
 * Return          : none
 ******************************************************************************/
void usb_hvnd_enumeration (usb_clsinfo_t * mess, uint16_t ** table)
{
    uint8_t * p_desc;
    uint16_t  desc_len;
    uint16_t  speed;

    *table[3] = USB_OK;

    /* Pipe Information table set */
    speed  = *table[6];
    p_desc = (uint8_t *) g_usb_hstd_config_descriptor[mess->ip];

    desc_len = (uint16_t) (((uint16_t) *(p_desc + 3)) << 8);
    desc_len = (uint16_t) (desc_len + *(p_desc + 2));

    /* Pipe Information table set */
    usb_hvnd_pipe_info(mess, p_desc, speed, desc_len);

  #if (BSP_CFG_RTOS == 0)
    usb_hstd_return_enu_mgr(mess, USB_OK); /* Return to MGR */
  #endif /* BSP_CFG_RTOS == 0 */
}

/******************************************************************************
 * End of function usb_hvnd_enumeration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_pipe_info
 * Description     : Host pipe information check. Set EP table.
 * Arguments       : usb_utr_t *p_utr      : Pointer to usb_utr_t structure
 *                 : uint8_t  *table       : Descriptor start address.
 * : uint16_t speed        : Device connected speed
 * : uint16_t length       : Configuration Descriptor Length
 * Return value    : none
 ******************************************************************************/
static void usb_hvnd_pipe_info (usb_utr_t * p_utr, uint8_t * table, uint16_t speed, uint16_t length)
{
    uint16_t             ofdsc;
    uint16_t             pipe_no;
    usb_pipe_table_reg_t ep_tbl;

    /* Check Endpoint Descriptor */
    ofdsc = table[0];

    /* WAIT_LOOP */
    while (ofdsc < length)
    {
        /* Search within Interface */
        if (USB_DT_ENDPOINT == table[ofdsc + 1])
        {
            pipe_no = (uint16_t) (usb_hvnd_make_pipe_reg_info(p_utr, USB_ADDRESS1, speed, &table[ofdsc], &ep_tbl));
            if (USB_NULL != pipe_no)
            {
                usb_hstd_set_pipe_info(p_utr->ip, pipe_no, &ep_tbl);
            }
            else
            {
                return;
            }
        }

        ofdsc = (uint16_t) (ofdsc + table[ofdsc]);
    }
}

/******************************************************************************
 * End of function usb_hvnd_pipe_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_read_complete
 * Description     : Notify application task of data reception completion.
 * : (Callback function at completion of INT data reception.)
 * Arguments       :
 * Return value    : none
 ******************************************************************************/
void usb_hvnd_read_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;

    usb_instance_ctrl_t ctrl;

    ctrl.module_number = ptr->ip;                /* Module number setting */
    ctrl.pipe          = (uint8_t) ptr->keyword; /* Pipe number setting */
    ctrl.type          = USB_CLASS_HVND;         /* Vendor class  */

    ctrl.data_size      = ptr->read_req_len - ptr->tranlen;
    ctrl.device_address = (uint8_t) (usb_hstd_get_devsel(ptr, ctrl.pipe) >> 12);
  #if (BSP_CFG_RTOS != 0)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
  #endif                               /* #if (BSP_CFG_RTOS != 0) */

    switch (ptr->status)
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

    usb_set_event(USB_STATUS_READ_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hvnd_read_complete()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_write_complete
 * Description     : Notify application task of data transmission completion.
 * : (Callback function at completion of INT data reception.)
 * Arguments       :
 * Return value    : none
 ******************************************************************************/
void usb_hvnd_write_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;

    usb_instance_ctrl_t ctrl;

    ctrl.module_number  = ptr->ip;                /* Module number setting */
    ctrl.pipe           = (uint8_t) ptr->keyword; /* Pipe number setting */
    ctrl.type           = USB_CLASS_HVND;         /* Vendor class  */
    ctrl.device_address = (uint8_t) (usb_hstd_get_devsel(ptr, ctrl.pipe) >> 12);
  #if (BSP_CFG_RTOS != 0)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
  #endif /* #if (BSP_CFG_RTOS != 0) */

    if (USB_DATA_NONE == ptr->status)
    {
        ctrl.status = FSP_SUCCESS;
    }
    else
    {
        ctrl.status = FSP_ERR_USB_FAILED;
    }

    usb_set_event(USB_STATUS_WRITE_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hvnd_write_complete()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_registration
 * Description     : Host vendor class registration.
 * Argument        : usb_utr_t *ptr    : IP info (mode, IP no, reg. address).
 * Return          : none
 ******************************************************************************/
void usb_hvnd_registration (usb_utr_t * ptr)
{
    usb_hcdreg_t driver;

    /* Driver registration */

    /* Interface Class */
    driver.ifclass = (uint16_t) USB_IFCLS_VEN;

    /* Target peripheral list */
  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    driver.p_tpl = (uint16_t *) USB_CFG_TPL_TABLE;
  #else                                /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.p_tpl = (uint16_t *) &g_usb_apl_devicetpl;
  #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

    /* Driver init */
    driver.classinit = &usb_hstd_dummy_function;

    /* Driver check */
    driver.classcheck = &usb_hvnd_enumeration;

    /* Device configured */
    driver.devconfig = &usb_hvnd_configured;

    /* Device detach */
    driver.devdetach = &usb_hvnd_detach;

    /* Device suspend */
    driver.devsuspend = &usb_hstd_dummy_function;

    /* Device resume */
    driver.devresume = &usb_hstd_dummy_function;

    usb_hstd_driver_registration(ptr, &driver);

  #if USB_CFG_HUB == USB_CFG_ENABLE
   #if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HUB_TSK, USB_PRI_3);
   #endif                              /* BSP_CFG_RTOS == 0 */
    usb_hhub_registration(ptr, USB_NULL);
  #endif                               /* USB_CFG_HUB == USB_CFG_ENABLE */
}

/******************************************************************************
 * End of function usb_hvnd_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_make_pipe_reg_info
 * Description     : Make value for USB PIPE registers set value.
 * Arguments    : usb_utr_t *p_utr   : Pointer to usb_utr_t structure
 *              : uint16_t address      : USB Device address
 *              : usb_class_t usb_class : USB Device class(USB_HVND/USB_HCDC/USB_HHID/USB_HMSC/USB_HUB)
 *              : uint16_t speed        : USB speed
 *              : uint8_t *descriptor   : Address for End Point Descriptor
 *              : usb_pipe_table_reg_t *pipe_table_work : Address for Store PIPE reg set value.
 * Return value    : Pipe no (USB_PIPE1->USB_PIPE9:OK, USB_NULL:Error)
 ******************************************************************************/
static uint8_t usb_hvnd_make_pipe_reg_info (usb_utr_t            * p_utr,
                                            uint16_t               address,
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
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */

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
                pipe_no  = usb_hvnd_get_pipe_no(p_utr, USB_EP_BULK, USB_PIPE_DIR_IN);
            }
            else
            {
                /* OUT(send) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_BULK | USB_CFG_DBLB | USB_DIR_H_OUT);
                pipe_no  = usb_hvnd_get_pipe_no(p_utr, USB_EP_BULK, USB_PIPE_DIR_OUT);
            }

  #if defined(USB_HIGH_SPEED_MODULE)
            if (USB_IP1 == p_utr->ip)
            {
                pipe_cfg |= (uint16_t) (USB_CFG_CNTMD);
            }
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
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
                pipe_no  = usb_hvnd_get_pipe_no(p_utr, USB_EP_INT, USB_PIPE_DIR_IN);
            }
            else
            {
                /* OUT(send) */
                pipe_cfg = (uint16_t) (USB_TYPFIELD_INT | USB_DIR_H_OUT);
                pipe_no  = usb_hvnd_get_pipe_no(p_utr, USB_EP_INT, USB_PIPE_DIR_OUT);
            }

            /* Get value for Interval Error Detection Interval  */
            pipe_peri = usb_hstd_get_pipe_peri_value(speed, descriptor[USB_EP_B_INTERVAL]);

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
        if (USB_IP1 == p_utr->ip)
        {
            /* PIPEBUF is USBA module only */
            pipe_buf = usb_hstd_get_pipe_buf_value(pipe_no);
            pipe_table_work->pipe_buf = pipe_buf;
        }
  #endif                               /* #if defined (USB_HIGH_SPEED_MODULE) */
    }

    return pipe_no;
}

/******************************************************************************
 * End of function usb_hvnd_make_pipe_reg_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_get_pipe_no
 * Description     : Get PIPE No.
 * Arguments    : usb_utr_t *p_utr   : Pointer to usb_utr_t structure
 *              : uint16_t address   : USB Device address
 *              : uint16_t class     : USB Device class(USB_HVND/USB_HCDC/USB_HHID/USB_HMSC/USB_HUB)
 *              : uint8_t  type      : Transfer Type.(USB_EP_BULK/USB_EP_INT)
 *              : uint8_t  dir       : (USB_PIPE_DIR_IN/USB_PIPE_DIR_OUT)
 * Return value    : Pipe no (USB_PIPE1->USB_PIPE9:OK, USB_NULL:Error)
 ******************************************************************************/
static uint8_t usb_hvnd_get_pipe_no (usb_utr_t * p_utr, uint8_t type, uint8_t dir)
{
  #if (USB_CFG_DMA == USB_CFG_DISABLE)
    (void) dir;
  #endif                               /* (USB_CFG_DMA == USB_CFG_ENABLE) */
    uint8_t pipe_no = USB_NULL;
    uint8_t pipe;

    if (USB_EP_BULK == type)
    {
        /* BULK PIPE Loop */
        /* WAIT_LOOP */
        for (pipe = USB_BULK_PIPE_START; pipe < (USB_BULK_PIPE_END + 1); pipe++)
        {
  #if (USB_CFG_DMA == USB_CFG_ENABLE)
            if ((USB_PIPE1 == pipe) || (USB_PIPE2 == pipe))
            {
                if ((USB_PIPE_DIR_IN == dir) && (0 != p_utr->p_transfer_rx))
                {
                    /* For IN transfer */

                    /* Check Free pipe */
                    if (USB_FALSE == g_usb_pipe_table[p_utr->ip][pipe].use_flag)
                    {
                        pipe_no = pipe; /* Set Free pipe */
                        break;
                    }
                }
                else if ((USB_PIPE_DIR_IN != dir) && (0 != p_utr->p_transfer_tx))
                {
                    /* For OUT Transfer */

                    /* Check Free pipe */
                    if (USB_FALSE == g_usb_pipe_table[p_utr->ip][pipe].use_flag)
                    {
                        pipe_no = pipe; /* Set Free pipe */
                        break;
                    }
                }
                else
                {
                    /* Nothing */
                }
            }
            else
            {
                /* Check Free pipe */
                if (USB_FALSE == g_usb_pipe_table[p_utr->ip][pipe].use_flag)
                {
                    pipe_no = pipe;    /* Set Free pipe */
                    break;
                }
            }

  #else
            if (USB_FALSE == g_usb_pipe_table[p_utr->ip][pipe].use_flag)
            {
                /* Check Free pipe */
                pipe_no = pipe;        /* Set Free pipe */
                break;
            }
  #endif
        }
    }

    if (USB_EP_INT == type)
    {
        /* Interrupt PIPE Loop */
        /* WAIT_LOOP */
        for (pipe = USB_INT_PIPE_START; pipe < (USB_INT_PIPE_END + 1); pipe++)
        {
            if (USB_FALSE == g_usb_pipe_table[p_utr->ip][pipe].use_flag)
            {
                /* Check Free pipe */
                pipe_no = pipe;        /* Set Free pipe */
                break;
            }
        }
    }

    return pipe_no;
}

/******************************************************************************
 * End of function usb_hvnd_get_pipe_no
 ******************************************************************************/
 #endif                                /* defined(USB_CFG_HVND_USE) */

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
