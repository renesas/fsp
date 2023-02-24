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
#include "../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "r_usb_hhid_api.h"
#include "r_usb_hhid.h"
#include "inc/r_usb_hhid_driver.h"

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/* variables */
static uint16_t  g_usb_hhid_request_setup[USB_NUM_USBIP][5]; /* Control Transfer Request field */
static usb_utr_t usb_shhid_string_req[USB_NUM_USBIP];        /* Request for String discriptor */

/* functions */
static uint16_t usb_hhid_cmd_submit(usb_utr_t * ptr, usb_cb_t complete);

#if (BSP_CFG_RTOS)
uint16_t usb_hhid_get_string_info(usb_utr_t * mess, uint16_t addr, uint16_t string);
uint16_t usb_hhid_req_trans_wait_tmo(uint16_t tmo);
void     usb_hhid_req_trans_result(usb_utr_t * mess, uint16_t data1, uint16_t data2);

#else                                  /* (BSP_CFG_RTOS) */
static void usb_hhid_check_result(usb_utr_t * ptr, uint16_t unused, uint16_t status);
static void usb_hhid_enumeration(usb_utr_t * mess);

#endif /* (BSP_CFG_RTOS) */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* Host HID TPL */
const uint16_t g_usb_hhid_devicetpl[] =
{
    1,                                                               /* Number of tpl table */
    0,                                                               /* Reserved */
    USB_NOVENDOR, USB_NOPRODUCT                                      /* Vendor ID, Product ID */
};

uint16_t  g_usb_hhid_protocol[USB_NUM_USBIP][USB_MAXDEVADDR];        /* HID Device protocol(Mouse/Keyboard) */
uint16_t  g_usb_hhid_num_endpoint[USB_NUM_USBIP][USB_MAXDEVADDR];    /* Num Endpoints */
uint16_t  g_usb_hhid_outpipe_support[USB_NUM_USBIP][USB_MAXDEVADDR]; /* OUT pipe support */
uint8_t   g_usb_hhid_string_data[USB_NUM_USBIP][USB_HHID_CLSDATASIZE];
uint16_t  g_usb_hhid_devaddr[USB_NUM_USBIP];                         /* Device Address */
uint16_t  g_usb_hhid_enum_seq[USB_NUM_USBIP];                        /* Enumeration Sequence */
uint16_t  g_usb_hhid_speed[USB_NUM_USBIP];                           /* Device speed */
uint8_t * g_p_usb_hhid_config_table[USB_NUM_USBIP];                  /* Configuration Descriptor Table */
uint8_t * g_p_usb_hhid_device_table[USB_NUM_USBIP];                  /* Device Descriptor Table */
uint8_t * g_p_usb_hhid_interface_table[USB_NUM_USBIP];               /* Interface Descriptor Table */

#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern const uint16_t USB_CFG_TPL_TABLE[];
#endif  /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Renesas Abstracted USB Driver functions
 ******************************************************************************/
#if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hhid_check_result
 * Description     : String Descriptor receive complete callback.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *                 : uint16_t unused      : Not used
 *                 : uint16_t status      : Not used
 * Return          : none
 ******************************************************************************/
static void usb_hhid_check_result (usb_utr_t * ptr, uint16_t unused, uint16_t status)
{
    usb_mh_t        p_blf;
    usb_clsinfo_t * cp;
    usb_er_t        err = USB_OK;
    FSP_PARAMETER_NOT_USED(unused);
    FSP_PARAMETER_NOT_USED(status);

    /* Get mem pool blk */
    if (USB_PGET_BLK(USB_HHID_MPL, &p_blf) == USB_OK)
    {
        cp          = (usb_clsinfo_t *) p_blf;
        cp->msghead = (usb_mh_t) USB_NULL;
        cp->msginfo = USB_HHID_TCMD_OPEN;
        cp->ip      = ptr->ip;
        cp->ipp     = ptr->ipp;

        /* Send message */
        err = USB_SND_MSG(USB_HHID_MBX, (usb_msg_t *) cp);
        if (USB_OK != err)
        {
            /* error */
            USB_REL_BLK(USB_HHID_MPL, (usb_mh_t) p_blf);
            USB_PRINTF0("### usb_open_hstd function snd_msg error\n");
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
 * End of function usb_hhid_check_result
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_enumeration
 * Description     : Enumeration( Get String Descriptor ) and Pipe tabele set.
 * Arguments       : usb_utr_t *mess      : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
static void usb_hhid_enumeration (usb_utr_t * mess)
{
    uint16_t  retval;
    uint8_t   string;
    uint8_t * p_desc;
    uint8_t * p_iftable;
    uint16_t  desc_len;
    uint8_t   protocol;
 #ifdef USB_DEBUGPRINT_PP
    uint8_t * table;
    uint8_t   pdata[32], j;
 #endif                                /* #ifdef USB_DEBUGPRINT_PP */

    /* Branch for Enumeration Sequence */
    switch (g_usb_hhid_enum_seq[mess->ip])
    {
        /* Enumeration Sequence String Descriptor #0 receive request */
        case USB_HHID_ENUM_STR_DT0_REQ:
        {
            /* Get String descriptor */
            usb_hhid_get_string_desc(mess,
                                     g_usb_hhid_devaddr[mess->ip],
                                     (uint16_t) 0,
                                     (usb_cb_t) &usb_hhid_check_result);

            /* String Descriptor #0 Receive wait */
            g_usb_hhid_enum_seq[mess->ip]++;
            break;
        }

        /* Enumeration Sequence String Descriptor #0 Receive complete */
        case USB_HHID_ENUM_STR_DT0_WAIT:
        {
            /* String descriptor check */
            if ((usb_er_t) USB_CTRL_END == mess->status)
            {
                /* Set iProduct */
                string = g_p_usb_hhid_device_table[mess->ip][15];

                /* Get String descriptor */
                usb_hhid_get_string_desc(mess,
                                         g_usb_hhid_devaddr[mess->ip],
                                         (uint16_t) string,
                                         (usb_cb_t) &usb_hhid_check_result);
            }

            /* StringDescriptor iProduct Receive */
            g_usb_hhid_enum_seq[mess->ip]++;
            break;
        }

        /* StringDescriptor iProduct Receive complete */
        case USB_HHID_ENUM_STR_IPRODUCT_WAIT:
        {
            /* String descriptor check */
            if ((usb_er_t) USB_CTRL_END == mess->status)
            {
 #ifdef USB_DEBUGPRINT_PP
                /* String descriptor iProduct Address set */
                table = (uint8_t *) &g_usb_hhid_string_data[mess->ip];

                /* String descriptor bLength check */
                if (table[0] < (uint8_t) (32 * 2 + 2))
                {
                    /* Number of characters = bLength /2 -1  */
                    /* 1 character 16bit(UNICODE String) */
                    table[0] = (uint8_t) (table[0] / 2 - 1);
                }
                else
                {
                    /* Number of characters = 32 set */
                    table[0] = (uint8_t) 32;
                }

                /* WAIT_LOOP */
                for (j = 0; j < table[0]; j++)
                {
                    pdata[j] = table[j * 2 + 2];
                }

                pdata[table[0]] = 0;

                /* Display Product name */
                USB_PRINTF1("  %s\n", pdata);
 #endif                                /* #ifdef USB_DEBUGPRINT_PP */
            }
            else
            {
                USB_PRINTF0("*** Product name error\n");
            }

            protocol = usb_hhid_get_hid_protocol(mess->ip, g_usb_hhid_devaddr[mess->ip]); /* Get HID Protocol */
            if ((USB_HID_KEYBOARD != protocol) && (USB_HID_MOUSE != protocol))
            {
                USB_PRINTF0("### Device information error !\n");

                /* Enumeration Sequence Complete */
                g_usb_hhid_enum_seq[mess->ip] = USB_HHID_ENUM_COMPLETE;
            }

            p_desc = g_p_usb_hhid_config_table[mess->ip];

            desc_len = (uint16_t) (((uint16_t) *(p_desc + 3)) << 8);

            desc_len = (uint16_t) (desc_len + (uint16_t) *(p_desc + 2));

            /* Searching InterfaceDescriptor */
            p_iftable = g_p_usb_hhid_interface_table[mess->ip];

            desc_len = (uint16_t) (desc_len - ((uint16_t) (p_iftable - p_desc)));

            /* pipe information table set */
            retval = usb_hhid_pipe_info(mess, p_iftable, g_usb_hhid_speed[mess->ip], desc_len);
            if (USB_ERROR == retval)
            {
                USB_PRINTF0("### Device information error !\n");

                /* Enumeration Sequence Complete */
                g_usb_hhid_enum_seq[mess->ip] = USB_HHID_ENUM_COMPLETE;

                /* Enumeration class check error */
                retval = USB_ERROR;
                usb_hstd_connect_err_event_set(mess->ip);
            }
            else
            {
                /* Enumeration Sequence Complete */
                g_usb_hhid_enum_seq[mess->ip] = USB_HHID_ENUM_COMPLETE;

                /* Enumeration class check OK */
                retval = USB_OK;
            }

            /* return to MGR */
            usb_hstd_return_enu_mgr(mess, retval);
            break;
        }

        default:
        {
            g_usb_hhid_enum_seq[mess->ip] = USB_HHID_ENUM_STR_DT0_REQ;
            usb_hstd_return_enu_mgr(mess, USB_ERROR); /* Return to MGR */
            usb_hstd_connect_err_event_set(mess->ip);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hhid_enumeration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_task
 * Description     : Host HIT Task
 * Argument        : usb_vp_int_t stacd   : Start code
 * Return value    : none
 ******************************************************************************/
void usb_hhid_task (usb_vp_int_t stacd)
{
    usb_utr_t * p_mess;
    usb_er_t    err = 0;
    FSP_PARAMETER_NOT_USED(stacd);

    err = USB_TRCV_MSG(USB_HHID_MBX, (usb_msg_t **) &p_mess, (uint16_t) 3000);
    if (USB_OK == err)
    {
        switch (p_mess->msginfo)
        {
            case USB_HHID_TCMD_OPEN:
            {
                usb_hhid_enumeration(p_mess);
                break;
            }

            default:
            {
                break;
            }
        }

        err = USB_REL_BLK(USB_HHID_MPL, (usb_mh_t) p_mess);
        if (USB_OK != err)
        {
            USB_PRINTF0("### USB HHID Task rel_blk error\n");
        }

        /* Conditional compile dep. on OS usage. */
    }
    else
    {
        return;
    }
}

/******************************************************************************
 * End of function usb_hhid_task
 ******************************************************************************/
#endif                                 /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hhid_pipe_info
 * Description     : pipe information table set
 * Arguments       : usb_utr_t *mess         : Pointer to usb_utr_t structure.
 *                 : uint8_t *table          : Descriptor store address
 *                 : uint16_t speed          : Conect Dpeed(Hi/Full/...)
 *                 : uint16_t length         : Descriptor total lenght
 * Return value    : uint16_t                : Error info
 ******************************************************************************/
uint16_t usb_hhid_pipe_info (usb_utr_t * ptr, uint8_t * table, uint16_t speed, uint16_t length)
{
    /* Offset for Descriptor Top Address */
    uint16_t ofdsc;
    uint16_t pipe_no;
    uint16_t detect_in_pipe  = USB_OFF;
    uint16_t detect_out_pipe = USB_ON;

    usb_pipe_table_reg_t ep_tbl;

    /* Check configuration descriptor */
    if (USB_DT_INTERFACE != table[1])
    {
        USB_PRINTF0("### Descriptor is not Interface descriptor.\n");

        return USB_ERROR;
    }

    /* Descriptor Address set */
    ofdsc = table[0];

    g_usb_hhid_outpipe_support[ptr->ip][g_usb_hhid_devaddr[ptr->ip]] = USB_OFF;

    if (USB_HID_OTHER == g_usb_hhid_protocol[ptr->ip][g_usb_hhid_devaddr[ptr->ip]])
    {
        if (2 == g_usb_hhid_num_endpoint[ptr->ip][g_usb_hhid_devaddr[ptr->ip]])
        {
            detect_out_pipe = USB_OFF;
        }
    }

    /* Loop for Endpoint Descriptor search */
    /* WAIT_LOOP */
    while (ofdsc < length)
    {
        /* Endpoint Descriptor */
        if (USB_DT_ENDPOINT == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
        {
            /* Check pipe information */
            pipe_no = usb_hstd_make_pipe_reg_info(ptr->ip,
                                                  g_usb_hhid_devaddr[ptr->ip],
                                                  USB_CLASS_INTERNAL_HHID,
                                                  speed,
                                                  &table[ofdsc],
                                                  &ep_tbl);
            if (USB_NULL != pipe_no)
            {
                usb_hstd_set_pipe_info(ptr->ip, pipe_no, &ep_tbl);
            }
            else
            {
                return USB_ERROR;
            }

            if (USB_DIR_H_IN == (ep_tbl.pipe_cfg & USB_DIRFIELD))
            {
                /* Get Max Packet size */
                detect_in_pipe = USB_ON;
            }
            else if (USB_DIR_H_OUT == (ep_tbl.pipe_cfg & USB_DIRFIELD))
            {
                g_usb_hhid_outpipe_support[ptr->ip][g_usb_hhid_devaddr[ptr->ip]] = USB_ON;
                detect_out_pipe = USB_ON;
            }
            else
            {
                /* error */
            }

            if ((USB_ON == detect_in_pipe) && (USB_ON == detect_out_pipe))
            {
                return USB_OK;
            }
        }

        ofdsc = (uint16_t) (ofdsc + (uint16_t) table[ofdsc]); /* Next descriptor point set */
    }

    return USB_ERROR;
}

/******************************************************************************
 * End of function usb_hhid_pipe_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_get_string_desc
 * Description     : Set GetDescriptor
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *                 : uint16_t     addr        : device address
 *                 : uint16_t     string      : descriptor index
 *                 : usb_cb_t     complete    : callback function
 * Return value    : uint16_t                 : error info
 ******************************************************************************/
uint16_t usb_hhid_get_string_desc (usb_utr_t * ptr, uint16_t addr, uint16_t string, usb_cb_t complete)
{
    uint16_t i;

    if (0 == string)
    {
        g_usb_hhid_request_setup[ptr->ip][2] = (uint16_t) 0x0000;
        g_usb_hhid_request_setup[ptr->ip][3] = (uint16_t) 0x0004;
    }
    else
    {
        /* Set LanguageID */
        g_usb_hhid_request_setup[ptr->ip][2]  = (uint16_t) (g_usb_hhid_string_data[ptr->ip][2]);
        g_usb_hhid_request_setup[ptr->ip][2] |= (uint16_t) ((uint16_t) (g_usb_hhid_string_data[ptr->ip][3]) << 8);
        g_usb_hhid_request_setup[ptr->ip][3]  = (uint16_t) USB_HHID_CLSDATASIZE;
    }

    g_usb_hhid_request_setup[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    g_usb_hhid_request_setup[ptr->ip][1] = (uint16_t) (USB_STRING_DESCRIPTOR + string);
    g_usb_hhid_request_setup[ptr->ip][4] = addr;

    /* WAIT_LOOP */
    for (i = 0; i < g_usb_hhid_request_setup[ptr->ip][3]; i++)
    {
        g_usb_hhid_string_data[ptr->ip][i] = (uint8_t) USB_VALUE_FFH;
    }

    return usb_hhid_cmd_submit(ptr, complete);
}

/******************************************************************************
 * End of function usb_hhid_get_string_desc
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_cmd_submit
 * Description     : command submit
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *                 : usb_cb_t     complete    : callback function
 * Return value    : uint16_t                  : USB_DONE
 ******************************************************************************/
static uint16_t usb_hhid_cmd_submit (usb_utr_t * ptr, usb_cb_t complete)
{
    usb_er_t err;
#if (BSP_CFG_RTOS)
    uint16_t hhid_retval;
    uint16_t ret = USB_OK;
#endif                                 /* (BSP_CFG_RTOS) */

    usb_shhid_string_req[ptr->ip].p_tranadr = (void *) g_usb_hhid_string_data[ptr->ip];
    usb_shhid_string_req[ptr->ip].complete  = complete;
    usb_shhid_string_req[ptr->ip].tranlen   = (uint32_t) g_usb_hhid_request_setup[ptr->ip][3];
    usb_shhid_string_req[ptr->ip].keyword   = USB_PIPE0;
    usb_shhid_string_req[ptr->ip].p_setup   = g_usb_hhid_request_setup[ptr->ip];
    usb_shhid_string_req[ptr->ip].segment   = USB_TRAN_END;

    usb_shhid_string_req[ptr->ip].ip  = ptr->ip;
    usb_shhid_string_req[ptr->ip].ipp = ptr->ipp;

#if (BSP_CFG_RTOS)
    err = usb_hstd_transfer_start_req(&usb_shhid_string_req[ptr->ip]);
    if (USB_OK == err)
    {
        hhid_retval = usb_hhid_req_trans_wait_tmo((uint16_t) USB_VALUE_3000);
        if (USB_DATA_STALL == hhid_retval)
        {
            USB_PRINTF0("*** GetStringDesc STALL !\n");

            ret = USB_ERROR;
        }
        else if (USB_DATA_TMO == hhid_retval)
        {
            USB_PRINTF0("*** GetStringDesc Timeout error !\n");

            ret = USB_ERROR;
        }
        else if (USB_CTRL_END != hhid_retval)
        {
            USB_PRINTF0("*** GetStringDesc error !\n");

            ret = USB_ERROR;
        }
        else
        {
            ret = USB_OK;
        }
    }
    else
    {
        ret = USB_ERROR;
    }

    return ret;
#else                                  /* (BSP_CFG_RTOS) */
    err = usb_hstd_transfer_start_req(&usb_shhid_string_req[ptr->ip]);
    if (USB_QOVR == err)
    {
        /* error */
        USB_PRINTF0("### usb_hhid_cmd_submit() : USB_E_QOVR \n");
    }
    return USB_OK;
#endif                                 /* (BSP_CFG_RTOS) */
}

/******************************************************************************
 * End of function usb_hhid_cmd_submit
 ******************************************************************************/

#if 0

/******************************************************************************
 * Function Name   : usb_hid_suspended
 * Description     : Suspended state process
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 * Arguments       : uint16_t     devadr      : Device Adrress
 * Return value    : none
 ******************************************************************************/
void usb_hid_suspended (usb_utr_t * ptr, uint16_t devadr)
{
    usb_instance_ctrl_t ctrl;

    ctrl.module_number  = ptr->ip;     /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    ctrl.type           = USB_CLASS_HHID;
 #if (BSP_CFG_RTOS == 1)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
 #endif                                /* (BSP_CFG_RTOS == 1) */
    usb_set_event(USB_STATUS_SUSPEND, &ctrl);
} /* End of function hid_suspended() */

/******************************************************************************
 * End of function usb_hid_suspended
 ******************************************************************************/
#endif

/******************************************************************************
 * Callback functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hid_configured
 * Description     : Callback function for HID device configuered
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *                 : uint16_t     devadr  : Device Adrress
 *                 : uint16_t     data2   : Not use
 * Return value    : none
 ******************************************************************************/
void usb_hid_configured (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    FSP_PARAMETER_NOT_USED(data2);

    usb_hhid_set_pipe_registration(ptr, devadr); /* Host HID Pipe registration */
    ctrl.module_number  = ptr->ip;               /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    ctrl.type           = USB_CLASS_HHID;
    usb_set_event(USB_STATUS_CONFIGURED, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hid_configured
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hid_detach
 * Description     : Callback function for HID device detach
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *                 : uint16_t     devadr  : Device Adrress
 *                 : uint16_t     data2   : Not use
 * Return value    : none
 ******************************************************************************/
void usb_hid_detach (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    FSP_PARAMETER_NOT_USED(data2);

    usb_hstd_clr_pipe_table(ptr->ip, devadr);
    ctrl.module_number  = ptr->ip;           /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    ctrl.type           = USB_CLASS_HHID;
    usb_set_event(USB_STATUS_DETACH, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hid_detach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hid_resume_complete
 * Description     : Resume complete callback.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     devadr  : Device Adrress
 *               : uint16_t     data2   : Not use
 * Return value    : none
 ******************************************************************************/
void usb_hid_resume_complete (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    FSP_PARAMETER_NOT_USED(data2);

    ctrl.module_number  = ptr->ip;     /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    ctrl.type           = USB_CLASS_HHID;
#if (BSP_CFG_RTOS == 1)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
#endif                                 /* (BSP_CFG_RTOS == 1) */
    usb_set_event(USB_STATUS_RESUME, &ctrl);
}

/******************************************************************************
 * End of function usb_hid_resume_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_read_complete
 * Description     : data receive complete process.
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *                 : uint16_t     data1   : Not used
 *                 : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_hhid_read_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    ctrl.module_number  = mess->ip;                  /* Module number setting */
    ctrl.pipe           = (uint8_t) (mess->keyword); /* Pipe number setting */
    ctrl.device_address = (uint8_t) (usb_hstd_get_devsel(mess, ctrl.pipe) >> 12);
    ctrl.type           = USB_CLASS_HHID;            /* hid Data class  */
    ctrl.data_size      = mess->read_req_len - mess->tranlen;

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

#if (BSP_CFG_RTOS == 1)
    ctrl.p_data = (void *) mess->cur_task_hdl;
#endif                                              /* (BSP_CFG_RTOS == 1) */

    usb_set_event(USB_STATUS_READ_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hhid_read_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_write_complete
 * Description     : data transfer complete process.
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *                 : uint16_t     data1   : Not used
 *                 : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_hhid_write_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    ctrl.module_number  = mess->ip;                  /* Module number setting */
    ctrl.pipe           = (uint8_t) (mess->keyword); /* Pipe number setting */
    ctrl.device_address = (uint8_t) (usb_hstd_get_devsel(mess, ctrl.pipe) >> 12);
    ctrl.type           = USB_CLASS_HHID;            /* hid Data class  */

    if (USB_DATA_NONE == mess->status)               /* USB_CFG_PHID_INT_OUT */
    {
        ctrl.status = FSP_SUCCESS;
    }
    else
    {
        ctrl.status = FSP_ERR_USB_FAILED;
    }

#if (BSP_CFG_RTOS == 1)
    ctrl.p_data = (void *) mess->cur_task_hdl;
#endif                                               /* (BSP_CFG_RTOS == 1) */

    usb_set_event(USB_STATUS_WRITE_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hhid_write_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_registration
 * Description     : registration of Host HID driver.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hhid_registration (usb_utr_t * ptr)
{
    usb_hcdreg_t driver;
#if USB_CFG_HUB == USB_CFG_ENABLE
    uint8_t i;
#endif                                                          /* USB_CFG_HUB == USB_CFG_ENABLE */

    driver.ifclass = (uint16_t) USB_IFCLS_HID;                  /* Interface class : HID */
#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    driver.p_tpl = (uint16_t *) USB_CFG_TPL_TABLE;
#else /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.p_tpl = (uint16_t *) &g_usb_hhid_devicetpl;          /* Target peripheral list */
#endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.classinit  = (usb_cb_t) &usb_hstd_dummy_function;    /* Driver init */
    driver.classcheck = (usb_cb_check_t) &usb_hhid_class_check; /* Driver check */
    driver.devconfig  = (usb_cb_t) &usb_hid_configured;         /* Device configuered */
    driver.devdetach  = (usb_cb_t) &usb_hid_detach;             /* Device detach */
    driver.devsuspend = (usb_cb_t) &usb_hstd_dummy_function;    /* Device suspend */
    driver.devresume  = (usb_cb_t) &usb_hid_resume_complete;    /* Device resume */

#if USB_CFG_HUB == USB_CFG_ENABLE
    /* WAIT_LOOP */
    for (i = 0; i < USB_MAX_DEVICE; i++)                        /* Loop support HID device count */
    {
        usb_hstd_driver_registration(ptr, &driver);             /* Host HID class driver registration. */
    }

 #if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HUB_TSK, USB_PRI_3);              /* Hub Task Priority set */
 #endif /* (BSP_CFG_RTOS == 0) */
    usb_hhub_registration(ptr, (usb_hcdreg_t *) USB_NULL);      /* Hub registration. */
#else                                                           /* USB_CFG_HUB == USB_CFG_ENABLE */
    usb_hstd_driver_registration(ptr, &driver);                 /* Host HID class driver registration. */
#endif  /* USB_CFG_HUB == USB_CFG_ENABLE */
}

/******************************************************************************
 * End of function usb_hhid_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_driver_start
 * Description     : USB Host Initialize process
 * Arguments       : usb_utr_t    *ptr : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hhid_driver_start (usb_utr_t * ptr)
{
    static uint8_t init = 0;
    uint16_t       i;

    if (0 == (init & (1 << ptr->ip)))
    {
        /* WAIT_LOOP */
        for (i = 0; i < (USB_MAXDEVADDR); i++)
        {
            g_usb_hhid_protocol[ptr->ip][i]        = 0;
            g_usb_hhid_num_endpoint[ptr->ip][i]    = 0;
            g_usb_hhid_outpipe_support[ptr->ip][i] = 0;
        }

        memset(g_usb_hhid_string_data[ptr->ip], 0, USB_HHID_CLSDATASIZE);
        memset(g_usb_hhid_request_setup[ptr->ip], 0, (5 * 2));
        memset((void *) &usb_shhid_string_req[ptr->ip], 0, sizeof(usb_utr_t));

        g_usb_hhid_devaddr[ptr->ip]           = 0;
        g_usb_hhid_enum_seq[ptr->ip]          = 0;
        g_usb_hhid_speed[ptr->ip]             = 0;
        g_p_usb_hhid_config_table[ptr->ip]    = 0;
        g_p_usb_hhid_device_table[ptr->ip]    = 0;
        g_p_usb_hhid_interface_table[ptr->ip] = 0;

        init |= (uint8_t) (1 << ptr->ip);
    }

#if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HHID_TSK, USB_PRI_3); /* Host HID task priority set */
#endif /* (BSP_CFG_RTOS == 0) */
}

/******************************************************************************
 * End of function usb_hhid_driver_start()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_set_pipe_registration
 * Description     : Host HID Pipe registration
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     devadr      : Device address
 * Return          : none
 ******************************************************************************/
void usb_hhid_set_pipe_registration (usb_utr_t * ptr, uint16_t devadr)
{
    uint8_t pipe_no;

    /* Search use pipe block */
    /* WAIT_LOOP */
    for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
    {
        /* Check use block */
        if (USB_TRUE == g_usb_pipe_table[ptr->ip][pipe_no].use_flag)
        {
            /* Check USB Device address */
            if ((devadr << (uint16_t) USB_DEVADDRBIT) ==
                (g_usb_pipe_table[ptr->ip][pipe_no].pipe_maxp & (uint16_t) USB_DEVSEL))
            {
                usb_hstd_set_pipe_reg(ptr, pipe_no);
            }
        }
    }
}

/******************************************************************************
 * End of function usb_hhid_set_pipe_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_get_hid_protocol
 * Description     : Get HID Protocol
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     devadr      : Device address
 * Return          : Hid Protocol
 ******************************************************************************/
uint8_t usb_hhid_get_hid_protocol (uint16_t ipno, uint16_t devadr)
{
    /* table[7]:Interface Descriptor-bInterfaceProtocol */
    return (uint8_t) g_usb_hhid_protocol[ipno][devadr];
}

/******************************************************************************
 * End of function usb_hhid_get_hid_protocol
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_class_check
 * Description     : Driver check.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     **table     : Pointer to HID class information table
 * Return value    : none
 ******************************************************************************/
void usb_hhid_class_check (usb_utr_t * ptr, uint16_t ** table)
{
#if (BSP_CFG_RTOS)
    uint16_t retval;
    uint16_t iproduct;
#else                                  /* (BSP_CFG_RTOS) */
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_clsinfo_t * cp;
#endif /* (BSP_CFG_RTOS) */

    g_p_usb_hhid_device_table[ptr->ip]    = (uint8_t *) table[0];        /* Device Descriptor Table */
    g_p_usb_hhid_config_table[ptr->ip]    = (uint8_t *) table[1];        /* Configuration Descriptor Table */
    g_usb_hhid_speed[ptr->ip]             = *table[6];                   /* Device speed */
    g_usb_hhid_devaddr[ptr->ip]           = *table[7];                   /* Device Address */
    g_p_usb_hhid_interface_table[ptr->ip] = (uint8_t *) table[2];        /* Interface Descriptor Table */
    g_usb_hhid_protocol[ptr->ip][g_usb_hhid_devaddr[ptr->ip]] =
        g_p_usb_hhid_interface_table[ptr->ip][USB_B_INTERFACE_PROTOCOL]; /* Interface Protocol */

    g_usb_hhid_num_endpoint[ptr->ip][g_usb_hhid_devaddr[ptr->ip]] =
        g_p_usb_hhid_interface_table[ptr->ip][USB_IF_B_NUMENDPOINTS];    /* Num Endpoints */

    /* Enumeration Sequence String Descriptor #0 receive request */
    g_usb_hhid_enum_seq[ptr->ip] = (uint16_t) USB_HHID_ENUM_STR_DT0_REQ;

    /* Descriptor check result */
    *table[3] = USB_OK;

#if (BSP_CFG_RTOS)
    /* Get String Descriptors */
    iproduct = g_p_usb_hhid_device_table[ptr->ip][USB_DEV_I_PRODUCT];
    retval   = usb_hhid_get_string_info(ptr, g_usb_hhid_devaddr[ptr->ip], iproduct);
    if (USB_OK != retval)
    {
        USB_PRINTF0("   GetDescriptor(String) failed!     \n");
        *table[3] = USB_ERROR;

        return;
    }
#else                                  /* (BSP_CFG_RTOS) */
    /* Get mem block from pool. */
    if (USB_PGET_BLK(USB_HHID_MPL, &p_blf) == USB_OK)
    {
        cp          = (usb_clsinfo_t *) p_blf;
        cp->msghead = (usb_mh_t) USB_NULL;
        cp->msginfo = USB_HHID_TCMD_OPEN; /* Set message information :USB transfer. */
        cp->ip      = ptr->ip;            /* IP number(0or1) */
        cp->ipp     = ptr->ipp;           /* IP address (USB0 or USB1) */

        /* Send message */
        err = USB_SND_MSG(USB_HHID_MBX, (usb_msg_t *) cp);
        if (USB_OK != err)
        {
            /* Error */
            USB_REL_BLK(USB_HHID_MPL, (usb_mh_t) p_blf);
            USB_PRINTF1("Host Sample snd_msg error %x\n", err);

            /* Transfer start request send NG */
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
#endif                                 /* (BSP_CFG_RTOS) */
}

/******************************************************************************
 * End of function usb_hhid_class_check
 ******************************************************************************/

#if (BSP_CFG_RTOS)

/******************************************************************************
 * Function Name   : usb_hhid_get_string_info
 * Description     : Get string descriptors.
 * Argument        : usb_utr_t *mess
 *                 uint16_t addr
 *                 uint16_t string
 * Return value    : none
 ******************************************************************************/
uint16_t usb_hhid_get_string_info (usb_utr_t * mess, uint16_t addr, uint16_t string)
{
    uint16_t  retval;
    uint8_t   protocol;
    uint8_t * p_desc;
    uint8_t * p_iftable;
    uint16_t  desc_len;

    /* Send GetDescriptor(String) */
    retval = usb_hhid_get_string_desc(mess, addr, (uint16_t) 0, usb_hhid_req_trans_result);
    if (USB_OK != retval)
    {
        return USB_ERROR;
    }

    /* Send GetDescriptor(String) */
    retval = usb_hhid_get_string_desc(mess, addr, string, usb_hhid_req_trans_result);
    if (USB_OK != retval)
    {
        return USB_ERROR;
    }

    protocol = usb_hhid_get_hid_protocol(mess->ip, g_usb_hhid_devaddr[mess->ip]); /* Get HID Protocol */
    if ((USB_HID_KEYBOARD != protocol) && (USB_HID_MOUSE != protocol))
    {
        USB_PRINTF0("### Device information error !\n");

        /* Enumeration Sequence Complete */
        g_usb_hhid_enum_seq[mess->ip] = USB_HHID_ENUM_COMPLETE;
    }

    p_desc = g_p_usb_hhid_config_table[mess->ip];

    desc_len = (uint16_t) (((uint16_t) *(p_desc + 3)) << 8);

    desc_len = (uint16_t) (desc_len + (uint16_t) *(p_desc + 2));

    /* Searching InterfaceDescriptor */
    p_iftable = g_p_usb_hhid_interface_table[mess->ip];

    desc_len = (uint16_t) (desc_len - (p_iftable - p_desc));

    /* pipe information table set */
    retval = usb_hhid_pipe_info(mess, p_iftable, g_usb_hhid_speed[mess->ip], desc_len);
    if (USB_ERROR == retval)
    {
        USB_PRINTF0("### Device information error !\n");

        /* Enumeration Sequence Complete */
        g_usb_hhid_enum_seq[mess->ip] = USB_HHID_ENUM_COMPLETE;

        /* Enumeration class check error */
        retval = USB_ERROR;
        usb_hstd_connect_err_event_set(mess->ip);
    }
    else
    {
        /* Enumeration Sequence Complete */
        g_usb_hhid_enum_seq[mess->ip] = USB_HHID_ENUM_COMPLETE;

        /* Enumeration class check OK */
        retval = USB_OK;
    }

    return retval;
}

/******************************************************************************
 * End of function usb_hhid_get_string_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_req_trans_result
 * Description     : Send a message to notify the result of the hhid class request (PIPE0).
 * Argument        : usb_utr_t *mess
 *                 uint16_t data1
 *                 uint16_t data2
 * Return value    : none
 ******************************************************************************/
void usb_hhid_req_trans_result (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_er_t err;
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    /* Send a message to HHID mailbox */
    err = USB_SND_MSG(USB_HHID_MBX, (usb_msg_t *) mess);
    if (USB_OK != err)
    {
        USB_PRINTF1("### HHID snd_msg error (%ld)\n", err);
    }
}

/******************************************************************************
 * End of function usb_hhid_req_trans_result
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hhid_req_trans_wait_tmo
 * Description     : Receive the result of the hhid class request with a timeout (PIPE0).
 * Argument        : uint16_t tmo     : Time-out value.
 * Return value    : USB_OK/USB_ERROR
 ******************************************************************************/
uint16_t usb_hhid_req_trans_wait_tmo (uint16_t tmo)
{
    usb_utr_t * mess;
    usb_er_t    err;

    /* Receive message from HHID mailbox with time-out */
    err = USB_TRCV_MSG(USB_HHID_MBX, (usb_msg_t **) &mess, (usb_tm_t) tmo);
    if (USB_OK != err)
    {
        USB_PRINTF1("### HHID trcv_msg error (%ld)\n", err);

        return USB_ERROR;
    }

    return mess->status;
}

/******************************************************************************
 * End of function usb_hhid_req_trans_wait_tmo
 ******************************************************************************/
#endif                                 /* (BSP_CFG_RTOS) */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
