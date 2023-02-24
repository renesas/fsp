/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <string.h>

#include <r_usb_basic.h>
#include "r_usb_basic_api.h"
#include "../../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "r_usb_hcdc_api.h"
#include "inc/r_usb_hcdc.h"

#define USB_VALUE_32    (32)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

#if (BSP_CFG_RTOS == 2)
uint16_t usb_hcdc_get_string_info(usb_utr_t * mess, uint16_t addr, uint16_t string);

#else                                  /* (BSP_CFG_RTOS == 2) */
static void usb_hcdc_check_result(usb_utr_t * mess, uint16_t data1, uint16_t data2);

#endif  /* (BSP_CFG_RTOS == 2) */
static void usb_hcdc_init(usb_utr_t * ptr, uint16_t data1, uint16_t data2);

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

const uint16_t g_usb_hcdc_device_tpl[] =
{
    USB_CFG_TPLCNT,                    /* Number of tpl table */
    0,                                 /* Reserved */
    USB_CFG_TPL                        /* Vendor ID, Product ID */
};

int16_t g_usb_hcdc_smpl_class_seq[USB_NUM_USBIP];

uint8_t * g_p_usb_hcdc_device_table[USB_NUM_USBIP];
uint8_t * g_p_usb_hcdc_config_table[USB_NUM_USBIP];
uint8_t * g_p_usb_hcdc_interface_table[USB_NUM_USBIP];
uint16_t  g_usb_hcdc_speed[USB_NUM_USBIP];
uint16_t  g_usb_hcdc_devaddr[USB_NUM_USBIP];

#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern const uint16_t USB_CFG_TPL_TABLE[];
#endif                                 /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Renesas USB Host CDC Driver functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_enumeration
 * Description     : USB CDC Class Enumeration
 * Argument        : usb_utr_t *mess           : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
#if (BSP_CFG_RTOS == 0)
void usb_hcdc_enumeration (usb_clsinfo_t * mess)
{
    /* Condition compilation by the difference of useful function */
 #if defined(USB_DEBUG_ON)
    uint8_t  p_data[32];
    uint16_t j;
 #endif                                /* defined(USB_DEBUG_ON) */
    uint16_t  retval;
    uint8_t   string;
    uint8_t * p_desc;
    uint16_t  desc_len;

    uint8_t * p_config_desc;

    /* Manager Mode Change */
    switch (g_usb_hcdc_smpl_class_seq[mess->ip])
    {
        case USB_SEQ_0:
        {
            p_config_desc = g_p_usb_hcdc_config_table[mess->ip];

            if (USB_DT_CONFIGURATION != p_config_desc[1])
            {
                USB_PRINTF0("### Configuration descriptor error !\n");
                usb_hstd_connect_err_event_set(mess->ip);
            }
            else
            {
                /* String descriptor */
                usb_hstd_get_string_desc(mess,
                                         g_usb_hcdc_devaddr[mess->ip],
                                         (uint16_t) 0,
                                         (usb_cb_t) &usb_hcdc_check_result);
                g_usb_hcdc_smpl_class_seq[mess->ip]++;
            }

            break;
        }

        case USB_SEQ_1:
        {
            /* String descriptor check */
            if (USB_CTRL_END == mess->result)
            {
                string = g_p_usb_hcdc_device_table[mess->ip][15];

                /* String descriptor */
                usb_hstd_get_string_desc(mess, g_usb_hcdc_devaddr[mess->ip], string, (usb_cb_t) &usb_hcdc_check_result);
                g_usb_hcdc_smpl_class_seq[mess->ip]++;
            }
            else                                          /* USB_ERROR */
            {
                USB_PRINTF0("### Enumeration is stoped(ClassCode-ERROR)\n");
                usb_hstd_return_enu_mgr(mess, USB_ERROR); /* Return to MGR */
                usb_hstd_connect_err_event_set(mess->ip);
            }

            break;
        }

        case USB_SEQ_2:
        {
            /* String descriptor check */
            if (USB_CTRL_END == mess->result)
            {
                if (g_usb_hstd_class_data[mess->ip][0] < (uint8_t) ((USB_MAX_WLANGID_NUM * 2) + 2))
                {
                    g_usb_hstd_class_data[mess->ip][0] = (uint8_t) (g_usb_hstd_class_data[mess->ip][0] / 2);
                    g_usb_hstd_class_data[mess->ip][0] = (uint8_t) (g_usb_hstd_class_data[mess->ip][0] - 1);
                }
                else
                {
                    g_usb_hstd_class_data[mess->ip][0] = (uint8_t) USB_MAX_WLANGID_NUM;
                }

                /* Condition compilation by the difference of useful function */
 #if defined(USB_DEBUG_ON)
                for (j = (uint16_t) 0; j < g_usb_hstd_class_data[mess->ip][0]; j++)
                {
                    p_data[j] = g_usb_hstd_class_data[mess->ip][j * (uint16_t) 2 + (uint16_t) 2];
                }

                p_data[g_usb_hstd_class_data[mess->ip][0]] = 0;
                USB_PRINTF1("  %s\n", p_data);
 #endif                                /* defined(USB_DEBUG_ON) */
            }
            else
            {
                USB_PRINTF0("*** Product name error\n");
            }

            p_desc   = (uint8_t *) g_usb_hstd_config_descriptor[mess->ip];
            desc_len = (uint16_t) (((uint16_t) *(p_desc + 3)) << 8);
            desc_len = (uint16_t) (desc_len + *(p_desc + 2));

            /* Pipe Information table set */
            retval = usb_hcdc_pipe_info(mess, p_desc, g_usb_hcdc_speed[mess->ip], desc_len);
            if (USB_ERROR == retval)
            {
                /* Pipe Information table error */
                USB_PRINTF0("### Device information error !\n");
                usb_hstd_connect_err_event_set(mess->ip);
            }
            else
            {
                retval = USB_OK;
            }

            usb_hstd_return_enu_mgr(mess, retval); /* Return to MGR */
            break;
        }

        default:
        {
            g_usb_hcdc_smpl_class_seq[mess->ip] = USB_SEQ_0;
            usb_hstd_return_enu_mgr(mess, USB_ERROR); /* Return to MGR */
            usb_hstd_connect_err_event_set(mess->ip);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hcdc_enumeration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_check_result
 * Description     : Host CDC class check result
 * Argument        : usb_utr_t *mess           : Pointer to usb_utr_t structure.
 *               : uint16_t data1   : Not used.
 *               : uint16_t data2   : Not used.
 * Return          : none
 ******************************************************************************/
static void usb_hcdc_check_result (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_clsinfo_t * ptr;

    (void) data1;
    (void) data2;

    /* Get mem pool blk */
    if (USB_PGET_BLK(USB_HCDC_MPL, &p_blf) == USB_OK)
    {
        ptr          = (usb_clsinfo_t *) p_blf;
        ptr->msginfo = USB_MSG_CLS_CHECKREQUEST;
        ptr->keyword = mess->keyword;
        ptr->result  = mess->status;
        ptr->ip      = mess->ip;
        ptr->ipp     = mess->ipp;

        /* Send message */
        err = USB_SND_MSG(USB_HCDC_MBX, (usb_msg_t *) p_blf);
        if (USB_OK != err)
        {
            USB_REL_BLK(USB_HCDC_MPL, (usb_mh_t) p_blf);
            USB_PRINTF0("### CheckResult function snd_msg(HCDC) error\n");
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
 * End of function usb_hcdc_check_result
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_task
 * Description     : CDC Host task
 * Argument        : stacd    : Task Start Code
 * Return          : none
 ******************************************************************************/
void usb_hcdc_task (usb_vp_int_t stacd)
{
    usb_utr_t * p_mess;
    usb_er_t    err = 0;

    (void) stacd;

    err = USB_TRCV_MSG(USB_HCDC_MBX, (usb_msg_t **) &p_mess, (uint16_t) 3000);
    if (USB_OK == err)
    {
        switch (p_mess->msginfo)
        {
            case USB_MSG_CLS_CHECKREQUEST:
            {
                usb_hcdc_enumeration((usb_clsinfo_t *) p_mess);
                err = USB_REL_BLK(USB_HCDC_MPL, (usb_mh_t) p_mess);
                if (USB_OK != err)
                {
                    USB_PRINTF0("### USB HCDC Task rel_blk error\n");
                }

                break;
            }

            default:
            {
                break;
            }
        }

        err = USB_REL_BLK(USB_HCDC_MPL, (usb_mh_t) p_mess);
        if (USB_OK != err)
        {
            USB_PRINTF0("### USB HCDC Task rel_blk error\n");
        }
    }
}

/******************************************************************************
 * End of function usb_hcdc_task
 ******************************************************************************/
#endif                                 /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hcdc_pipe_info
 * Description     : Host Pipe Information check and EP Table Set
 * Argument        : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *               : uint8_t      *table  : Check Start Descriptor address
 *               : uint16_t     speed   : Device connected speed
 *               : uint16_t     length  : Configuration Descriptor Length
 * Return value    : uint16_t             : USB_OK / USB_ERROR
 ******************************************************************************/
uint16_t usb_hcdc_pipe_info (usb_utr_t * ptr, uint8_t * table, uint16_t speed, uint16_t length)
{
    uint16_t ofdsc;
    uint16_t pipe_no;
    uint16_t in_pipe;
    uint16_t out_pipe;
    uint16_t status_pipe;
    uint16_t result_code;

    usb_pipe_table_reg_t ep_tbl;

    result_code = USB_OK;

    /* Check Endpoint Descriptor */
    ofdsc = table[0];

    /* Pipe initial */
    in_pipe     = USB_NOPIPE;
    out_pipe    = USB_NOPIPE;
    status_pipe = USB_NOPIPE;

    /* WAIT_LOOP */
    while (ofdsc < length)
    {
        /* Endpoint Descriptor */
        if (USB_DT_ENDPOINT == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
        {
            /* Transfer Type */
            if (USB_EP_BULK == (table[ofdsc + USB_EP_B_ATTRIBUTES] & USB_EP_TRNSMASK))
            {
                /* Check if transfer direction is IN */
                if ((table[ofdsc + USB_EP_B_ENDPOINTADDRESS] & USB_EP_DIRMASK) == USB_EP_IN)
                {
                    out_pipe = USB_TRUE;
                }
                else
                {
                    in_pipe = USB_TRUE;
                }
            }
            else if (USB_EP_INT == (table[ofdsc + USB_EP_B_ATTRIBUTES] & USB_EP_TRNSMASK))
            {
                status_pipe = USB_TRUE;
            }
            else
            {
                result_code = USB_ERROR;
                break;
            }

            /* EP Table pipe Information set */
            pipe_no = usb_hstd_make_pipe_reg_info(ptr->ip,
                                                  g_usb_hcdc_devaddr[ptr->ip],
                                                  USB_CLASS_INTERNAL_HCDC,
                                                  speed,
                                                  &table[ofdsc],
                                                  &ep_tbl);
            if (USB_NULL == pipe_no)
            {
                result_code = USB_ERROR;
            }
            else
            {
                usb_hstd_set_pipe_info(ptr->ip, pipe_no, &ep_tbl);
            }

            if (result_code == USB_ERROR)
            {
                break;
            }

            if (((USB_NOPIPE != in_pipe) && (USB_NOPIPE != out_pipe)) && (USB_NOPIPE != status_pipe))
            {
                result_code = USB_OK;
                break;
            }
        }

        ofdsc = (uint16_t) (ofdsc + table[ofdsc]);
    }

    return result_code;
}

/******************************************************************************
 * End of function usb_hcdc_pipe_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_configured
 * Description     : Callback function for CDC device configuered
 * Argument        : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     devadr  : Device Adrress
 *               : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_hcdc_configured (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) data2;

    usb_hcdc_set_pipe_registration(ptr, devadr); /* Host CDC Pipe registration */
    ctrl.module_number  = ptr->ip;               /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    ctrl.type           = (usb_class_t) USB_CLASS_INTERNAL_HCDC;

    usb_set_event(USB_STATUS_CONFIGURED, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hcdc_configured
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_detach
 * Description     : Callback function for CDC device detach
 * Argument        : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     devadr  : Device Adrress
 *               : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_hcdc_detach (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) data2;
    usb_hstd_clr_pipe_table(ptr->ip, devadr);
    ctrl.module_number  = ptr->ip;           /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    usb_set_event(USB_STATUS_DETACH, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hcdc_detach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_read_complete
 * Description     : CallBack Function
 * Argument        : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_hcdc_read_complete (usb_utr_t * mess, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) devadr;
    (void) data2;

    ctrl.module_number = mess->ip;                            /* Module number setting */
    ctrl.pipe          = (uint8_t) mess->keyword;             /* Pipe number setting */
    if ((USB_CFG_HCDC_BULK_IN == ctrl.pipe) || (USB_CFG_HCDC_BULK_IN2 == ctrl.pipe))
    {
        ctrl.type = USB_CLASS_HCDC;                           /* CDC Data class  */
    }
    else /* USB_CFG_HCDC_INT_IN */
    {
        ctrl.type = USB_CLASS_HCDCC;                          /* CDC Control class  */
    }

    ctrl.device_address = (uint8_t) (usb_hstd_get_devsel(mess, ctrl.pipe) >> 12);
    ctrl.data_size      = mess->read_req_len - mess->tranlen; /* Set Receive data length */

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

#if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) mess->cur_task_hdl;
#endif                                              /* (BSP_CFG_RTOS == 2) */

    usb_set_event(USB_STATUS_READ_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hcdc_read_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_write_complete
 * Description     : CallBack Function
 * Argument        : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_hcdc_write_complete (usb_utr_t * mess, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) devadr;
    (void) data2;

    ctrl.module_number = mess->ip;                /* Module number setting */
    ctrl.pipe          = (uint8_t) mess->keyword; /* Pipe number setting */
    ctrl.type          = USB_CLASS_HCDC;          /* CDC Data class  */

    if (USB_DATA_NONE == mess->status)
    {
        ctrl.status = FSP_SUCCESS;
    }
    else
    {
        ctrl.status = FSP_ERR_USB_FAILED;
    }

    ctrl.device_address = (uint8_t) (usb_hstd_get_devsel(mess, ctrl.pipe) >> 12);
#if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) mess->cur_task_hdl;
#endif                                               /* (BSP_CFG_RTOS == 2) */

    usb_set_event(USB_STATUS_WRITE_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hcdc_write_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_registration
 * Description     : registration of Communications Devices class Driver
 * Argument        : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hcdc_registration (usb_utr_t * ptr)
{
    usb_hcdreg_t driver;
#if USB_CFG_HUB == USB_CFG_ENABLE
    uint8_t i;
#endif                                         /* USB_CFG_HUB == USB_CFG_ENABLE */

    /* Driver registration */
#if USB_CFG_HCDC_IFCLS == USB_CFG_CDC
    driver.ifclass = (uint16_t) USB_IFCLS_CDC; /* CDC Communications Interface */
#else                                          /* USB_CFG_HCDC_IFCLS == USB_CFG_CDC */
    driver.ifclass = (uint16_t) USB_IFCLS_VEN; /* CDC Communications Interface */
#endif  /* USB_CFG_HCDC_IFCLS == USB_CFG_CDC */
#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    driver.p_tpl = (uint16_t *) USB_CFG_TPL_TABLE;
#else /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.p_tpl = (uint16_t *) &g_usb_hcdc_device_tpl;         /* Target peripheral list */
#endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.classinit  = (usb_cb_t) &usb_hcdc_init;              /* Driver init */
    driver.classcheck = (usb_cb_check_t) &usb_hcdc_class_check; /* Driver check */
    driver.devconfig  = (usb_cb_t) &usb_hcdc_configured;        /* Device configuered */
    driver.devdetach  = (usb_cb_t) &usb_hcdc_detach;            /* Device detach */
    driver.devsuspend = (usb_cb_t) &usb_hstd_dummy_function;    /* Device suspend */
    driver.devresume  = (usb_cb_t) &usb_hstd_dummy_function;    /* Device resume */

#if USB_CFG_HUB == USB_CFG_ENABLE
    /* WAIT_LOOP */
    for (i = 0; i < USB_MAX_CONNECT_DEVICE_NUM; i++)            /* Loop support CDC device count */
    {
        usb_hstd_driver_registration(ptr, &driver);             /* Host CDC class driver registration. */
    }

 #if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HUB_TSK, USB_PRI_3);              /* Hub Task Priority set */
 #endif /* (BSP_CFG_RTOS == 0) */
    usb_hhub_registration(ptr, USB_NULL);                       /* Hub registration. */
#else                                                           /* USB_CFG_HUB == USB_CFG_ENABLE */
    usb_hstd_driver_registration(ptr, &driver);                 /* Host CDC class driver registration. */
#endif  /* USB_CFG_HUB == USB_CFG_ENABLE */
}

/******************************************************************************
 * End of function usb_hcdc_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_init
 * Description     : Initialize of Host CDC driver.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     data1   : not use
 *               : uint16_t     data2   : not use
 * Return value    : none
 ******************************************************************************/
static void usb_hcdc_init (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    static uint8_t init = 0;

    (void) data1;
    (void) data2;

    if (0 == (init & (1 << ptr->ip)))
    {
        g_usb_hcdc_smpl_class_seq[ptr->ip]    = 0;
        g_usb_hcdc_speed[ptr->ip]             = 0;
        g_usb_hcdc_devaddr[ptr->ip]           = 0;
        g_p_usb_hcdc_device_table[ptr->ip]    = 0;
        g_p_usb_hcdc_config_table[ptr->ip]    = 0;
        g_p_usb_hcdc_interface_table[ptr->ip] = 0;

        init = init | (uint8_t) (1 << ptr->ip);
    }
}

/******************************************************************************
 * End of function usb_hcdc_init
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_class_check
 * Description     : class check.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     **table : Pointer to data table.
 * Return          : none
 ******************************************************************************/
void usb_hcdc_class_check (usb_utr_t * ptr, uint16_t ** table)
{
#if (BSP_CFG_RTOS == 2)
    uint16_t retval;
    uint16_t iproduct;
#else                                  /* (BSP_CFG_RTOS == 2) */
    usb_clsinfo_t * p_blf;
    usb_clsinfo_t * cp;
    usb_er_t        err;
#endif  /* (BSP_CFG_RTOS == 2) */

    g_p_usb_hcdc_device_table[ptr->ip]    = (uint8_t *) (table[0]); /* Set device descriptor address */
    g_p_usb_hcdc_config_table[ptr->ip]    = (uint8_t *) (table[1]); /* Set configuration descriptor address */
    g_p_usb_hcdc_interface_table[ptr->ip] = (uint8_t *) (table[2]); /* Set interface descriptor address */
    g_usb_hcdc_speed[ptr->ip]             = *table[6];              /* Set device connect speed */
    g_usb_hcdc_devaddr[ptr->ip]           = *table[7];              /* Set device address */

    *table[3] = USB_OK;                                             /* Set class check done  */

#if (BSP_CFG_RTOS == 2)
    /* Get String Descriptors */
    iproduct = g_p_usb_hcdc_device_table[ptr->ip][USB_DEV_I_PRODUCT];
    retval   = usb_hcdc_get_string_info(ptr, g_usb_hcdc_devaddr[ptr->ip], iproduct);
    if (USB_OK != retval)
    {
        USB_PRINTF0("   GetDescriptor(String) failed!     \n");
        *table[3] = USB_ERROR;

        return;
    }
#else                                               /* (BSP_CFG_RTOS == 2) */
    g_usb_hcdc_smpl_class_seq[ptr->ip] = USB_SEQ_0; /* Initialize sequence number for enumeration */

    /* Get mem block from pool. */
    if (USB_PGET_BLK(USB_HCDC_MPL, &p_blf) == USB_OK)
    {
        cp          = p_blf;
        cp->msginfo = USB_MSG_CLS_CHECKREQUEST; /* Set message information: Check request */

        cp->ipp = ptr->ipp;                     /* IP address (USB0 or USB1) */
        cp->ip  = ptr->ip;                      /* IP number(0or1) */

        /* Specify to perform next enumeration sequence to class function */
        err = USB_SND_MSG(USB_HCDC_MBX, (usb_msg_t *) cp);
        if (USB_OK != err)
        {
            USB_PRINTF1("Host Sample snd_msg error %x\n", err);
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
#endif                                 /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hcdc_class_check()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_set_pipe_registration
 * Description     : Host CDC pipe registration.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  devadr     : Device address
 * Return          : usb_er_t             : Error info
 ******************************************************************************/
usb_er_t usb_hcdc_set_pipe_registration (usb_utr_t * ptr, uint16_t dev_addr)
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
 * End of function usb_hcdc_set_pipe_registration()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hcdc_driver_start
 * Description     : USB host Initialize process
 * Arguments       : none
 * Return          : none
 ******************************************************************************/
void usb_hcdc_driver_start (usb_utr_t * ptr)
{
    static uint8_t is_init = USB_NO;

    g_usb_hcdc_smpl_class_seq[ptr->ip]    = 0;
    g_usb_hcdc_speed[ptr->ip]             = 0;
    g_usb_hcdc_devaddr[ptr->ip]           = 0;
    g_p_usb_hcdc_device_table[ptr->ip]    = 0;
    g_p_usb_hcdc_config_table[ptr->ip]    = 0;
    g_p_usb_hcdc_interface_table[ptr->ip] = 0;

    if (USB_NO == is_init)
    {
        /* Set host CDC Task priority */
#if (BSP_CFG_RTOS == 0)
        usb_cstd_set_task_pri(USB_HCDC_TSK, USB_PRI_4);
#endif                                 /* (BSP_CFG_RTOS == 0) */
        is_init = USB_YES;
    }
}

/******************************************************************************
 * End of function usb_hcdc_driver_start()
 ******************************************************************************/

#if (BSP_CFG_RTOS == 2)

/******************************************************************************
 * Function Name   : usb_hcdc_get_string_info
 * Description     : Get string descriptors.
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t addr
 *                 uint16_t string
 * Return value    : none
 ******************************************************************************/
uint16_t usb_hcdc_get_string_info (usb_utr_t * mess, uint16_t addr, uint16_t string)
{
    uint8_t * p_config_desc;
    uint16_t  retval;
    uint8_t * p_desc;
    uint16_t  desc_len;

    (void) addr;
    retval        = USB_OK;
    p_config_desc = g_p_usb_hcdc_config_table[mess->ip];

    if (USB_DT_CONFIGURATION != p_config_desc[1])
    {
        USB_PRINTF0("### Configuration descriptor error !\n");
        usb_hstd_connect_err_event_set(mess->ip);
        retval = USB_ERROR;
    }
    else
    {
        /* String descriptor */
        usb_hstd_get_string_desc(mess, g_usb_hcdc_devaddr[mess->ip], 0);
        g_usb_hcdc_smpl_class_seq[mess->ip]++;
    }

    if (retval == USB_ERROR)
    {
        return retval;
    }

    /* String descriptor check */
    if (USB_CTRL_END == mess->result)
    {
        string = g_p_usb_hcdc_device_table[mess->ip][15];

        /* String descriptor */
        usb_hstd_get_string_desc(mess, g_usb_hcdc_devaddr[mess->ip], string);
        g_usb_hcdc_smpl_class_seq[mess->ip]++;
    }
    else                               /* USB_ERROR */
    {
        USB_PRINTF0("### Enumeration is stoped(ClassCode-ERROR)\n");
        usb_hstd_connect_err_event_set(mess->ip);
    }

    /* String descriptor check */
    if (USB_CTRL_END == mess->result)
    {
        if (g_usb_hstd_class_data[mess->ip][0] < (uint8_t) ((USB_VALUE_32 * 2) + 2))
        {
            g_usb_hstd_class_data[mess->ip][0] = (uint8_t) (g_usb_hstd_class_data[mess->ip][0] / 2);
            g_usb_hstd_class_data[mess->ip][0] = (uint8_t) (g_usb_hstd_class_data[mess->ip][0] - 1);
        }
        else
        {
            g_usb_hstd_class_data[mess->ip][0] = (uint8_t) USB_VALUE_32;
        }

        /* Condition compilation by the difference of useful function */
 #if defined(USB_DEBUG_ON)
        for (j = (uint16_t) 0; j < g_usb_hstd_class_data[mess->ip][0]; j++)
        {
            p_data[j] = g_usb_hstd_class_data[mess->ip][j * (uint16_t) 2 + (uint16_t) 2];
        }

        p_data[g_usb_hstd_class_data[mess->ip][0]] = 0;
        USB_PRINTF1("  %s\n", p_data);
 #endif                                /* defined(USB_DEBUG_ON) */
    }
    else
    {
        USB_PRINTF0("*** Product name error\n");
    }

    p_desc   = (uint8_t *) g_usb_hstd_config_descriptor[mess->ip];
    desc_len = (uint16_t) (*(p_desc + 3) << 8);
    desc_len = (uint16_t) (desc_len + (uint16_t) *(p_desc + 2));

    /* Pipe Information table set */
    retval = usb_hcdc_pipe_info(mess, p_desc, g_usb_hcdc_speed[mess->ip], desc_len);
    if (USB_ERROR == retval)
    {
        /* Pipe Information table error */
        USB_PRINTF0("### Device information error !\n");
        usb_hstd_connect_err_event_set(mess->ip);
    }
    else
    {
        retval = USB_OK;
    }

    return retval;
}                                      /* End of function usb_hcdc_get_string_info() */

#endif /* (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
