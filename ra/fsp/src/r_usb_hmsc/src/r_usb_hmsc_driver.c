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
#include <r_usb_basic.h>
#include <r_usb_basic_cfg.h>
#include <string.h>

#include "../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#if (BSP_CFG_RTOS == 2)
 #include "../../r_usb_basic/src/driver/inc/r_usb_cstd_rtos.h"
#endif
#include "../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "../../r_usb_basic/src/hw/inc/r_usb_reg_access.h"

#include "r_usb_hmsc.h"
#include "r_usb_hmsc_api.h"
#include "inc/r_usb_hmsc_driver.h"

#if defined(USB_CFG_HMSC_USE)

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
 #define USB_VALUE_20H          (0x20)
 #define USB_VALUE_3FH          (0x3F)
 #define USB_VALUE_36           (36)
 #define USB_VALUE_200          (200)
 #define USB_VALUE_FFH          (0xFF)
 #define USB_VALUE_3000         (3000)
 #define USB_VALUE_FEA1H        (0xFEA1)
 #define USB_VALUE_FE21H        (0xFE21)
 #define USB_ALL_PAGES          (0x3F)
 #define USB_VALUE_ALL_PAGES    (44)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/* functions */
 #if (BSP_CFG_RTOS == 2)
static uint16_t usb_hmsc_data_act(usb_utr_t * mess);
static uint16_t usb_hmsc_get_string_desc(usb_utr_t * ptr, uint16_t addr, uint16_t string, usb_cb_t complete);
static uint16_t usb_hmsc_send_cbw(usb_utr_t * ptr, uint16_t side);
static uint16_t usb_hmsc_send_data(usb_utr_t * ptr, uint16_t side, uint8_t * buff, uint32_t size);
static uint16_t usb_hmsc_get_data(usb_utr_t * ptr, uint16_t side, uint8_t * buff, uint32_t size);
static uint16_t usb_hmsc_get_csw(usb_utr_t * ptr, uint16_t side);
static usb_er_t usb_hmsc_clear_stall(usb_utr_t * ptr, uint16_t Pipe, usb_cb_t complete);

 #else                                 /* (BSP_CFG_RTOS == 2) */
static uint16_t usb_hmsc_data_act(usb_utr_t * mess);
static void     usb_hmsc_stall_err(usb_utr_t * mess);
static void     usb_hmsc_specified_path(usb_utr_t * mess);
static void     usb_hmsc_check_result(usb_utr_t * mess, uint16_t data1, uint16_t data2);
static void     usb_hmsc_command_result(usb_utr_t * ptr, uint16_t result);
static uint16_t usb_hmsc_get_string_desc(usb_utr_t * ptr, uint16_t addr, uint16_t string, usb_cb_t complete);
static uint16_t usb_hmsc_send_cbw(usb_utr_t * ptr, uint16_t side);
static uint16_t usb_hmsc_send_cbw_check(usb_utr_t * ptr, uint16_t side, uint16_t result);
static uint16_t usb_hmsc_send_data(usb_utr_t * ptr, uint16_t side, uint8_t * buff, uint32_t size);
static uint16_t usb_hmsc_send_data_check(usb_utr_t * ptr, uint16_t side, uint16_t result);
static uint16_t usb_hmsc_get_data(usb_utr_t * ptr, uint16_t side, uint8_t * buff, uint32_t size);
static uint16_t usb_hmsc_get_data_check(usb_utr_t * ptr, uint16_t side, uint16_t result);
static uint16_t usb_hmsc_get_csw(usb_utr_t * ptr, uint16_t side);
static uint16_t usb_hmsc_get_csw_check(usb_utr_t * ptr, uint16_t side, uint16_t result);
static usb_er_t usb_hmsc_clear_stall(usb_utr_t * ptr, uint16_t Pipe, usb_cb_t complete);
static uint16_t usb_hmsc_std_req_check(uint16_t result);

static void usb_hmsc_class_check_result(usb_utr_t * mess, uint16_t data1, uint16_t data2);
static void usb_hmsc_enumeration(usb_utr_t * mess);

 #endif                                /* (BSP_CFG_RTOS == 2) */
static void usb_hmsc_configured(usb_utr_t * ptr, uint16_t devadr, uint16_t data2);
static void usb_hmsc_detach(usb_utr_t * ptr, uint16_t addr, uint16_t data2);

/* variables */
static usb_utr_t       usb_hmsc_trans_data[USB_NUM_USBIP][USB_MAXSTRAGE];   /* Send data transfer message */
static usb_utr_t       usb_hmsc_receive_data[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Receive data transfer message */
static uint32_t        usb_hmsc_trans_size[USB_NUM_USBIP];
static uint8_t const * pusb_hmsc_buff[USB_NUM_USBIP];
static uint16_t        usb_shmsc_process[USB_NUM_USBIP];
 #if (BSP_CFG_RTOS == 0)
static uint16_t usb_shmsc_data_seq[USB_NUM_USBIP];
static uint16_t usb_shmsc_stall_err_seq[USB_NUM_USBIP];
static uint16_t usb_hmsc_csw_err_loop[USB_NUM_USBIP];
 #endif                                           /* (BSP_CFG_RTOS == 0) */

 #if (BSP_CFG_RTOS == 2)
static uint16_t  usb_hmsc_csw_err_stall[USB_NUM_USBIP];
static usb_utr_t gs_usb_hmsc_tran_result_msg;     /* Send:usb_hmsc_req_trans_result -> To:usb_hmsc_req_trans_wait_tmo */
static usb_utr_t gs_usb_hmsc_req_tran_result_msg; /* Send:usb_hmsc_trans_result -> To:usb_hmsc_trans_wait_tmo */
 #endif /* (BSP_CFG_RTOS == 2) */

uint32_t g_usb_hmsc_cmd_data_length[USB_NUM_USBIP];

/******************************************************************************
 * Exported global variables
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 2)
extern SemaphoreHandle_t SemaphoreHandleRead;
 #endif                                /*BSP_CFG_RTOS == 2 */

 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern const uint16_t USB_CFG_TPL_TABLE[];
 #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

const uint16_t g_usb_hmsc_devicetpl[] =
{
    1,                                 /* Number of tpl table */
    0,                                 /* Reserved */
    0xFFFFU, 0xFFFFU                   /* Vendor ID, Product ID */
};

usb_pipe_table_reg_t g_usb_hmsc_pipe_table[USB_MAXSTRAGE][USB_PIPE_DIR_MAX];

drive_management_t g_usb_hmsc_drvno_tbl[USB_MAXSTRAGE];                  /* Drive no. management table */
uint16_t           g_usb_hmsc_out_pipe[USB_NUM_USBIP][USB_MAXSTRAGE];    /* Pipenumber */
uint16_t           g_usb_hmsc_in_pipe[USB_NUM_USBIP][USB_MAXSTRAGE];     /* Pipenumber */
uint16_t           g_usb_hmsc_out_pipectr[USB_NUM_USBIP][USB_MAXSTRAGE]; /* Pipectr(SQTGL) */
uint16_t           g_usb_hmsc_in_pipectr[USB_NUM_USBIP][USB_MAXSTRAGE];  /* Pipectr(SQTGL) */
usb_msc_cbw_t      g_usb_hmsc_cbw[USB_NUM_USBIP][USB_MAXSTRAGE];         /* CBW headder */
usb_msc_csw_t      g_usb_hmsc_csw[USB_NUM_USBIP][USB_MAXSTRAGE];         /* CSW headder */
uint32_t           g_usb_hmsc_csw_tag_no[USB_NUM_USBIP][USB_MAXSTRAGE];  /* CBW tag number */
uint8_t            g_usb_hmsc_sub_class[USB_NUM_USBIP][USB_MAXSTRAGE];
uint8_t            g_usb_hmsc_tmp_sub_class[USB_NUM_USBIP];

uint16_t g_usb_hmsc_init_seq[USB_NUM_USBIP];

uint8_t * g_p_usb_hmsc_device_table[USB_NUM_USBIP];
uint8_t * g_p_usb_hmsc_config_table[USB_NUM_USBIP];
uint8_t * g_p_usb_hmsc_interface_table[USB_NUM_USBIP];
uint16_t  g_usb_hmsc_devaddr[USB_NUM_USBIP];

usb_utr_t g_usb_hmsc_class_control[USB_NUM_USBIP];
uint8_t   g_usb_hmsc_class_data[USB_NUM_USBIP][USB_HMSC_CLSDATASIZE];

uint16_t g_usb_shmsc_data_stall_seq[USB_NUM_USBIP];
uint16_t g_usb_hmsc_speed[USB_NUM_USBIP];

 #if (BSP_CFG_RTOS == 0)
uint8_t g_drive_search_que[USB_MAXSTRAGE];
uint8_t g_drive_search_que_cnt;
uint8_t g_drive_search_lock;
 #endif                                /* BSP_CFG_RTOS == 0 */

/******************************************************************************
 * Renesas Abstracted HMSC Driver functions
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_task
 * Description     : USB HMSC Task
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_task (void)
{
    usb_utr_t * pmess;
    usb_er_t    err;

    /* Receive message */
    err = USB_RCV_MSG(USB_HMSC_MBX, (usb_msg_t **) &pmess);
    if (USB_OK != err)
    {
        return;
    }

    switch (pmess->msginfo)
    {
        case USB_MSG_CLS_INIT:
        {
            usb_hmsc_enumeration(pmess);
            break;
        }

        case USB_MSG_HMSC_NO_DATA:
        case USB_MSG_HMSC_DATA_IN:
        case USB_MSG_HMSC_DATA_OUT:
        {
            usb_hmsc_data_act(pmess);
            break;
        }

        case USB_MSG_HMSC_CBW_ERR:
        case USB_MSG_HMSC_CSW_PHASE_ERR:
        {
            usb_hmsc_stall_err(pmess);
            break;
        }

        default:
        {
            break;
        }
    }

    err = USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t) pmess);
    if (USB_OK != err)
    {
        USB_PRINTF0("### USB hmsc Task rel_blk error\n");
    }
}

/******************************************************************************
 * End of function usb_hmsc_task
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_enumeration
 * Description     : check class
 * Arguments       : usb_utr_t *mess   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_enumeration (usb_utr_t * mess)
{
    uint16_t retval;
    uint16_t result;
    uint16_t iproduct;

    result = USB_OK;
    switch (g_usb_hmsc_init_seq[mess->ip])
    {
        case USB_SEQ_0:
        {
            /* Check Interface Descriptor (deviceclass) */
            if (USB_IFCLS_MAS != g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACECLASS])
            {
                USB_PRINTF1("### Interface deviceclass is %x , not support.\n",
                            g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACECLASS]);
                result = USB_ERROR;
            }

            /* Check Interface Descriptor (subclass) */
            g_usb_hmsc_tmp_sub_class[mess->ip] = g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACESUBCLASS];
            if (USB_ATAPI == g_usb_hmsc_tmp_sub_class[mess->ip])
            {
                USB_PRINTF0("    Interface subclass  : SFF-8070i\n");
            }
            else if (USB_SCSI == g_usb_hmsc_tmp_sub_class[mess->ip])
            {
                USB_PRINTF0("Interface subclass  : SCSI transparent command set\n");
            }
            else if (USB_ATAPI_MMC5 == g_usb_hmsc_tmp_sub_class[mess->ip])
            {
                USB_PRINTF0("   Interface subclass   : ATAPI command set\n");
            }
            else
            {
                USB_PRINTF1("### Interface subclass is %x , not support.\n", g_usb_hmsc_tmp_sub_class[mess->ip]);
                result = USB_ERROR;
            }

            /* Check Interface Descriptor (protocol) */
            if (USB_BOTP == g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACEPROTOCOL])
            {
                USB_PRINTF0("   Interface protocol   : BOT \n");
            }
            else
            {
                USB_PRINTF1("### Interface protocol is %x , not support.\n",
                            g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_INTERFACEPROTOCOL]);
                result = USB_ERROR;
            }

            /* Check Endpoint number */
            if (g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_NUMENDPOINTS] < 2)
            {
                USB_PRINTF1("### Endpoint number is %x , less than 2.\n",
                            g_p_usb_hmsc_interface_table[mess->ip][USB_IF_B_NUMENDPOINTS]);
                result = USB_ERROR;
            }

            /* Send GetDescriptor(Stirng) */
            if (USB_ERROR != result)
            {
                usb_hmsc_get_string_desc(mess, g_usb_hmsc_devaddr[mess->ip], 0, usb_hmsc_class_check_result);
                g_usb_hmsc_init_seq[mess->ip]++;
            }

            break;
        }

        case USB_SEQ_1:
        {
            retval = usb_hmsc_std_req_check(mess->result);
            if (USB_ERROR == retval)
            {
                result = USB_ERROR;
            }
            else
            {
                /* Send GetDescriptor(Stirng) */
                iproduct = g_p_usb_hmsc_device_table[mess->ip][USB_DEV_I_PRODUCT];
                usb_hmsc_get_string_desc(mess, g_usb_hmsc_devaddr[mess->ip], iproduct, usb_hmsc_class_check_result);
                g_usb_hmsc_init_seq[mess->ip]++;
            }

            break;
        }

        case USB_SEQ_2:
        {
            retval = usb_hmsc_std_req_check(mess->result);
            if (USB_ERROR == retval)
            {
                result = USB_ERROR;
            }

            if (USB_ERROR != result)
            {
                /* Return to MGR */
                usb_hstd_return_enu_mgr(mess, retval);
                g_usb_hmsc_init_seq[mess->ip] = USB_SEQ_0;
            }

            break;
        }

        default:
        {
            result = USB_ERROR;
            break;
        }
    }

    if (USB_ERROR == result)
    {
        /* Return to MGR */
        usb_hstd_return_enu_mgr(mess, USB_ERROR);
        g_usb_hmsc_init_seq[mess->ip] = USB_SEQ_0;
        usb_hstd_connect_err_event_set(mess->ip);
    }
}

/******************************************************************************
 * End of function usb_hmsc_enumeration
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_set_rw_cbw
 * Description     : CBW parameter initialization for the READ10/WRITE10 command
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     command     : ATAPI command
 *               : uint32_t     secno       : Sector number
 *               : uint16_t     seccnt      : Sector count
 *               : uint32_t     trans_byte  : Transfer size
 *               : uint16_t     side        : Driver number
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_set_rw_cbw (usb_utr_t * ptr,
                          uint16_t    command,
                          uint32_t    secno,
                          uint16_t    seccnt,
                          uint32_t    trans_byte,
                          uint16_t    side)
{
    /* CBW parameter set */
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag                    = g_usb_hmsc_csw_tag_no[ptr->ip][side];
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_lo                 = (uint8_t) trans_byte;
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_ml                 = (uint8_t) (trans_byte >> 8);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_mh                 = (uint8_t) (trans_byte >> 16);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_hi                 = (uint8_t) (trans_byte >> 24);
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir        = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.reserved7      = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.bcbw_lun           = 0; /*** Support LUN0 ONLY ***/
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.reserved4          = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.reserved3     = 0;

    /* ATAPI_COMMAND */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[0] = (uint8_t) command;

    /* LUN */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[1] = 0x00;

    /* sector address */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[2] = (uint8_t) (secno >> 24);
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[3] = (uint8_t) (secno >> 16);
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[4] = (uint8_t) (secno >> 8);
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[5] = (uint8_t) secno;

    /* Reserved */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[6] = 0x00;

    /* Sector length */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[7] = (uint8_t) (seccnt >> 8);

    /* Block address */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[8] = (uint8_t) seccnt;

    /* Control data */
    g_usb_hmsc_cbw[ptr->ip][side].cbwcb[9] = (uint8_t) 0x00;

    /* ATAPI command check */
    switch (command)
    {
        case USB_ATAPI_TEST_UNIT_READY:
        case USB_ATAPI_REQUEST_SENSE:
        case USB_ATAPI_INQUIRY:
        case USB_ATAPI_MODE_SELECT6:
        case USB_ATAPI_MODE_SENSE6:
        case USB_ATAPI_START_STOP_UNIT:
        case USB_ATAPI_PREVENT_ALLOW:
        case USB_ATAPI_READ_FORMAT_CAPACITY:
        case USB_ATAPI_READ_CAPACITY:
        {
            USB_PRINTF0("### Non-mounted command demand generating !\n");
            break;
        }

        /* Initialized READ CBW TAG */
        case USB_ATAPI_READ10:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 1;

            /* 10bytes */
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
            break;
        }

        /* Initialized WRITE CBW TAG */
        case USB_ATAPI_WRITE10:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir = 0;

            /* 10bytes */
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
            break;
        }

        case USB_ATAPI_SEEK:
        case USB_ATAPI_WRITE_AND_VERIFY:
        case USB_ATAPI_VERIFY10:
        case USB_ATAPI_MODE_SELECT10:
        case USB_ATAPI_MODE_SENSE10:
        default:
        {
            USB_PRINTF0("### Non-mounted command demand generating !\n");
            break;
        }
    }

    if (USB_ATAPI == g_usb_hmsc_sub_class[ptr->ip][side])
    {
        /* 12bytes */
        g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = USB_MSC_CBWCB_LENGTH;
    }
}

/******************************************************************************
 * End of function usb_hmsc_set_rw_cbw
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_set_els_cbw
 * Description     : CBW parameter initialization for other commands
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint8_t      *cbwcb      : Pointer to the CBW area
 *               : uint32_t     trans_byte  : Transfer size
 *               : uint16_t     side        : Drive number
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_set_els_cbw (usb_utr_t * ptr, uint8_t * cbwcb, uint32_t trans_byte, uint16_t side)
{
    uint8_t i;

    /* CBW parameter set */
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag    = g_usb_hmsc_csw_tag_no[ptr->ip][side];
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_lo = (uint8_t) trans_byte;
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_ml = (uint8_t) (trans_byte >> 8);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_mh = (uint8_t) (trans_byte >> 16);
    g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_hi = (uint8_t) (trans_byte >> 24);

    /* Receive */
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir    = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.reserved7  = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.bcbw_lun       = 0; /*** Support LUN0 ONLY ***/
    g_usb_hmsc_cbw[ptr->ip][side].bcbw_lun.reserved4      = 0;
    g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.reserved3 = 0;

    /* WAIT_LOOP */
    for (i = 0; i < 12; i++)
    {
        g_usb_hmsc_cbw[ptr->ip][side].cbwcb[i] = cbwcb[i];
    }

    /* ATAPI command check */
    switch (cbwcb[0])
    {
        /* No data */
        case USB_ATAPI_TEST_UNIT_READY:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
            break;
        }

        /* Receive */
        case USB_ATAPI_REQUEST_SENSE:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir        = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
            break;
        }

        /* Send */
        case USB_ATAPI_FORMAT_UNIT:
        {
            USB_PRINTF0("### Non-mounted command demand generating !\n");
            break;
        }

        /* Receive */
        case USB_ATAPI_INQUIRY:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir        = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
            break;
        }

        case USB_ATAPI_MODE_SELECT6:
        case USB_ATAPI_MODE_SENSE6:
        {
            break;
        }

        /* No data */
        case USB_ATAPI_START_STOP_UNIT:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
            break;
        }

        /* No data */
        case USB_ATAPI_PREVENT_ALLOW:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 6;
            break;
        }

        /* Receive */
        case USB_ATAPI_READ_FORMAT_CAPACITY:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir        = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
            break;
        }

        /* Receive */
        case USB_ATAPI_READ_CAPACITY:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir        = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
            break;
        }

        case USB_ATAPI_READ10:
        case USB_ATAPI_WRITE10:
        {
            USB_PRINTF0("### Non-mounted command demand generating !\n");
            break;
        }

        case USB_ATAPI_SEEK:
        case USB_ATAPI_WRITE_AND_VERIFY:
        case USB_ATAPI_VERIFY10:
        {
            USB_PRINTF0("### Non-mounted command demand generating !\n");
            break;
        }

        /* Send */
        case USB_ATAPI_MODE_SELECT10:
        {
            USB_PRINTF0("### Non-mounted command demand generating !\n");
            break;
        }

        /* Receive */
        case USB_ATAPI_MODE_SENSE10:
        {
            g_usb_hmsc_cbw[ptr->ip][side].bm_cbw_flags.cbw_dir        = 1;
            g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = 10;
            break;
        }

        default:
        {
            USB_PRINTF0("### Non-mounted command demand generating !\n");
            break;
        }
    }

    if (USB_ATAPI == g_usb_hmsc_sub_class[ptr->ip][side])
    {
        /* 12bytes */
        g_usb_hmsc_cbw[ptr->ip][side].bcbwcb_length.bcbwcb_length = USB_MSC_CBWCB_LENGTH;
    }
}

/******************************************************************************
 * End of function usb_hmsc_set_els_cbw
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_clr_data
 * Description     : data clear
 * Arguments       : uint16_t len : Clear size
 *               : uint8_t *buf : Pointer to the area to clear
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_clr_data (uint16_t len, uint8_t * buf)
{
    uint16_t i;

    /* WAIT_LOOP */
    for (i = 0; i < len; ++i)
    {
        *buf++ = 0x00;
    }
}

/******************************************************************************
 * End of function usb_hmsc_clr_data
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_no_data
 * Description     : HMSC No data
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Driver number
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_no_data (usb_utr_t * ptr, uint16_t side)
{
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;

    ptr->keyword               = side;
    usb_shmsc_process[ptr->ip] = USB_MSG_HMSC_NO_DATA;
    hmsc_retval                = usb_hmsc_data_act(ptr);

    return hmsc_retval;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_utr_t mess;

    mess.ip                    = ptr->ip;
    mess.ipp                   = ptr->ipp;
    mess.keyword               = side;
    mess.result                = USB_DATA_NONE;
    mess.tranlen               = 0;
    usb_shmsc_process[ptr->ip] = USB_MSG_HMSC_NO_DATA;
    usb_hmsc_specified_path(&mess);
    usb_shmsc_data_seq[ptr->ip] = USB_SEQ_0;

    return USB_OK;
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_no_data
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_data_in
 * Description     : HMSC Data In
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Driver number
 *               : uint8_t      *buff   : Pointer to the buffer area
 *               : uint32_t     size    : Data size
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_data_in (usb_utr_t * ptr, uint16_t side, uint8_t * const buff, uint32_t size)
{
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;

    ptr->keyword                 = side;
    pusb_hmsc_buff[ptr->ip]      = buff;
    usb_hmsc_trans_size[ptr->ip] = size;
    usb_shmsc_process[ptr->ip]   = USB_MSG_HMSC_DATA_IN;
    hmsc_retval = usb_hmsc_data_act(ptr);

    return hmsc_retval;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_utr_t mess;

    mess.ip      = ptr->ip;
    mess.ipp     = ptr->ipp;
    mess.keyword = side;
    mess.result  = USB_DATA_NONE;
    mess.tranlen = 0;
  #if (USB_CFG_DMA == USB_CFG_ENABLE)
    mess.p_transfer_rx = ptr->p_transfer_rx;
    mess.p_transfer_tx = ptr->p_transfer_tx;
  #endif                               /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */
    pusb_hmsc_buff[ptr->ip]      = buff;
    usb_hmsc_trans_size[ptr->ip] = size;
    usb_shmsc_process[ptr->ip]   = USB_MSG_HMSC_DATA_IN;
    usb_hmsc_specified_path(&mess);
    usb_shmsc_data_seq[ptr->ip] = USB_SEQ_0;

    return USB_OK;
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_data_in
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_data_out
 * Description     : HMSC Data Out
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Driver number
 *               : uint8_t      *buff   : Pointer to the buffer area
 *               : uint32_t     size    : Data size
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_data_out (usb_utr_t * ptr, uint16_t side, uint8_t const * const buff, uint32_t size)
{
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;

    ptr->keyword                 = side;
    pusb_hmsc_buff[ptr->ip]      = buff;
    usb_hmsc_trans_size[ptr->ip] = size;
    usb_shmsc_process[ptr->ip]   = USB_MSG_HMSC_DATA_OUT;
    hmsc_retval = usb_hmsc_data_act(ptr);

    return hmsc_retval;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_utr_t mess;

    mess.ip      = ptr->ip;
    mess.ipp     = ptr->ipp;
    mess.keyword = side;
    mess.result  = USB_DATA_NONE;
    mess.tranlen = 0;
  #if (USB_CFG_DMA == USB_CFG_ENABLE)
    mess.p_transfer_rx = ptr->p_transfer_rx;
    mess.p_transfer_tx = ptr->p_transfer_tx;
  #endif                               /* #if (USB_CFG_DMA == USB_CFG_ENABLE) */
    pusb_hmsc_buff[ptr->ip]      = buff;
    usb_hmsc_trans_size[ptr->ip] = size;
    usb_shmsc_process[ptr->ip]   = USB_MSG_HMSC_DATA_OUT;
    usb_hmsc_specified_path(&mess);
    usb_shmsc_data_seq[ptr->ip] = USB_SEQ_0;

    return USB_OK;
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_data_out
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_data_act
 * Description     : Send Data request
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 * Return value    : uint16_t :
 ******************************************************************************/
static uint16_t usb_hmsc_data_act (usb_utr_t * mess)
{
 #if (BSP_CFG_RTOS == 2)
    uint16_t  hmsc_retval;
    uint16_t  side;
    uint8_t * pbuff;
    uint32_t  size;

    side  = mess->keyword;
    pbuff = (uint8_t *) pusb_hmsc_buff[mess->ip];
    size  = usb_hmsc_trans_size[mess->ip];

    /* CBW */
    hmsc_retval = usb_hmsc_send_cbw(mess, side);
    if (USB_HMSC_OK != hmsc_retval)
    {
        USB_PRINTF1("### Data :SendCBW error(drive:%d) \n", side);
    }
    else
    {
        if (USB_MSG_HMSC_DATA_IN == usb_shmsc_process[mess->ip]) /* DataIn */
        {
            hmsc_retval = usb_hmsc_get_data(mess, side, pbuff, size);
            if (USB_HMSC_OK != hmsc_retval)
            {
                USB_PRINTF1("### DataIN : GetData error(drive:%d) \n", side);
                usb_hmsc_get_csw(mess, side);

                return USB_HMSC_CSW_ERR;
            }
        }
        else if (USB_MSG_HMSC_DATA_OUT == usb_shmsc_process[mess->ip]) /* DataOut */
        {
            hmsc_retval = usb_hmsc_send_data(mess, side, pbuff, size);
            if (USB_HMSC_OK != hmsc_retval)
            {
                USB_PRINTF1("### DataOUT : SendData error(drive:%d) \n", side);
                usb_hmsc_get_csw(mess, side);

                return USB_HMSC_CSW_ERR;
            }
        }
        else
        {
            /* None */
        }

        /* CSW */
        hmsc_retval = usb_hmsc_get_csw(mess, side);
        switch (hmsc_retval)
        {
            case USB_HMSC_OK:
            {
                break;
            }

            case USB_HMSC_CSW_ERR:
            {
                USB_PRINTF1("*** Data : CSW-NG(drive:%d) \n", side);
                usb_cpu_delay_xms((uint16_t) USB_VALUE_200);
                break;
            }

            case USB_HMSC_STALL:
            {
                USB_PRINTF1("*** Data : CSW-STALL(drive:%d) \n", side);
                usb_hmsc_csw_err_stall[mess->ip]      = USB_ON;
                g_usb_hmsc_in_pipectr[mess->ip][side] = 0;
                usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], class_trans_result);
                hmsc_retval = usb_hmsc_get_csw(mess, side);
                break;
            }

            case USB_MSC_CSW_PHASE_ERR:
            {
                USB_PRINTF1("*** Data : CSW-PhaseError(drive:%d) \n", side);

                /* Reset */
                usb_hmsc_mass_storage_reset(mess, g_usb_hmsc_drvno_tbl[side].devadr, usb_hmsc_trans_result);

                /* Clear STALL for OUT pipe */
                usb_hmsc_clear_stall(mess, g_usb_hmsc_out_pipe[mess->ip][side], class_trans_result);
                g_usb_hmsc_out_pipectr[mess->ip][side] = 0;

                /* Clear STALL for IN pipe */
                usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], class_trans_result);
                g_usb_hmsc_in_pipectr[mess->ip][side] = 0;
                break;
            }

            case USB_HMSC_SUBMIT_ERR:
            {
                USB_PRINTF1("### Data : GetCSW error(drive:%d) \n", side);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    return hmsc_retval;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    static uint16_t side;
    uint16_t        hmsc_retval;
    uint16_t        result;
    uint8_t       * pbuff;
    uint32_t        size;

    pbuff       = (uint8_t *) pusb_hmsc_buff[mess->ip];
    size        = usb_hmsc_trans_size[mess->ip];
    result      = mess->result;
    hmsc_retval = USB_HMSC_CSW_ERR;

    switch (usb_shmsc_data_seq[mess->ip])
    {
        case USB_SEQ_0:                /* CBW */
        {
            side        = mess->keyword;
            hmsc_retval = usb_hmsc_send_cbw(mess, side);
            usb_shmsc_data_seq[mess->ip]++;
            break;
        }

        case USB_SEQ_1:                /* Check CBW and Send Data */
        {
            hmsc_retval = usb_hmsc_send_cbw_check(mess, side, result);
            if (USB_HMSC_STALL == hmsc_retval)
            {
                usb_shmsc_process[mess->ip]       = USB_MSG_HMSC_CBW_ERR;
                usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
                mess->keyword = g_usb_hmsc_drvno_tbl[side].devadr;
                usb_hmsc_specified_path(mess);
                usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
            }
            else if (USB_HMSC_OK != hmsc_retval)
            {
                USB_PRINTF1("### Data : SendCBW error(drive:%d) \n", side);
                usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
                usb_hmsc_command_result(mess, hmsc_retval);
            }
            else                       /* Success */
            {
                switch (usb_shmsc_process[mess->ip])
                {
                    case USB_MSG_HMSC_NO_DATA:
                    {
                        hmsc_retval = usb_hmsc_get_csw(mess, side);
                        usb_shmsc_data_seq[mess->ip] = USB_SEQ_4;
                        break;
                    }

                    case USB_MSG_HMSC_DATA_OUT:
                    {
                        hmsc_retval = usb_hmsc_send_data(mess, side, pbuff, size);
                        usb_shmsc_data_seq[mess->ip]++;
                        break;
                    }

                    case USB_MSG_HMSC_DATA_IN:
                    {
                        g_usb_hmsc_cmd_data_length[mess->ip] = 0;
                        hmsc_retval = usb_hmsc_get_data(mess, side, pbuff, size);
                        usb_shmsc_data_seq[mess->ip]++;
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }

            break;
        }

        case USB_SEQ_2:                /* Check Data and Send CSW*/
        {
            if (USB_MSG_HMSC_DATA_OUT == usb_shmsc_process[mess->ip])
            {
                hmsc_retval = usb_hmsc_send_data_check(mess, side, result);
                if (USB_HMSC_STALL == hmsc_retval)
                {
                    usb_hmsc_clear_stall(mess, g_usb_hmsc_out_pipe[mess->ip][side], usb_hmsc_check_result);
                    usb_shmsc_data_seq[mess->ip]++;
                }
                else if (USB_HMSC_OK != hmsc_retval)
                {
                    USB_PRINTF1("### Data : SendData error(drive:%d) \n", side);
                    usb_hmsc_command_result(mess, hmsc_retval);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
                }
                else                   /* Success */
                {
                    hmsc_retval = usb_hmsc_get_csw(mess, side);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_4;
                }
            }
            else if (USB_MSG_HMSC_DATA_IN == usb_shmsc_process[mess->ip])
            {
                hmsc_retval = usb_hmsc_get_data_check(mess, side, result);
                if (USB_HMSC_STALL == hmsc_retval)
                {
                    usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], usb_hmsc_check_result);
                    usb_shmsc_data_seq[mess->ip]++;
                }
                else if (USB_HMSC_OK != hmsc_retval)
                {
                    USB_PRINTF1("### Data : SendData error(drive:%d) \n", side);
                    usb_hmsc_command_result(mess, hmsc_retval);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
                }
                else                   /* Success */
                {
                    g_usb_hmsc_cmd_data_length[mess->ip] = mess->tranlen;
                    hmsc_retval = usb_hmsc_get_csw(mess, side);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_4;
                }
            }
            else
            {
                /* Non */
            }

            break;
        }

        case USB_SEQ_3:                /* Check ClearStall and Send CSW */
        {
            hmsc_retval = usb_hmsc_get_csw(mess, side);
            usb_shmsc_data_seq[mess->ip]++;
            break;
        }

        case USB_SEQ_4:                /* Check CSW */
        {
            usb_shmsc_data_seq[mess->ip] = USB_SEQ_0;
            hmsc_retval = usb_hmsc_get_csw_check(mess, side, result);
            switch (hmsc_retval)
            {
                case USB_HMSC_OK:      /* Success */
                {
                    if (USB_ON == usb_hmsc_csw_err_loop[mess->ip])
                    {
                        usb_hmsc_csw_err_loop[mess->ip] = USB_OFF;
                        hmsc_retval = USB_HMSC_CSW_ERR;
                    }

                    usb_hmsc_command_result(mess, hmsc_retval);
                    break;
                }

                case USB_HMSC_CSW_ERR:
                {
                    USB_PRINTF1("*** Data : CSW-NG(drive:%d) \n", side);

                    if (USB_MSG_HMSC_STRG_USER_COMMAND != g_usb_hmsc_strg_process[mess->ip])
                    {
                        usb_hmsc_csw_err_loop[mess->ip] = USB_ON;
                        usb_hmsc_request_sense(mess, side, pbuff);
                    }
                    else
                    {
                        if (USB_ON == usb_hmsc_csw_err_loop[mess->ip])
                        {
                            usb_hmsc_csw_err_loop[mess->ip] = USB_OFF;
                        }

                        usb_hmsc_command_result(mess, hmsc_retval);
                    }

                    break;
                }

                case USB_HMSC_STALL:
                {
                    USB_PRINTF1("*** Data : CSW-STALL(drive:%d) \n", side);
                    g_usb_hmsc_in_pipectr[mess->ip][side] = 0;
                    usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], usb_hmsc_check_result);
                    usb_shmsc_data_seq[mess->ip] = USB_SEQ_3;
                    break;
                }

                case USB_HMSC_CSW_PHASE_ERR:
                {
                    USB_PRINTF1("*** Data : CSW-PhaseError(drive:%d) \n", side);
                    usb_shmsc_process[mess->ip]       = USB_MSG_HMSC_CSW_PHASE_ERR;
                    usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
                    mess->keyword = g_usb_hmsc_drvno_tbl[side].devadr;
                    usb_hmsc_specified_path(mess);
                    break;
                }

                default:
                {
                    /* Non */
                    break;
                }
            }

            break;
        }

        default:
        {
            /* WAIT_LOOP */
            while (1)
            {
                /* Non */
            }

            break;
        }
    }

    /* Data read error */
    return hmsc_retval;
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_data_act
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_stall_err
 * Description     : HMSC Stall Error
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_stall_err (usb_utr_t * mess)
{
    static uint16_t devadr;
    uint16_t        side;
    uint16_t        result;
    usb_er_t        err;

    switch (usb_shmsc_stall_err_seq[mess->ip])
    {
        case USB_SEQ_0:
        {
            devadr = mess->keyword;
            err    = usb_hmsc_mass_storage_reset(mess, devadr, (usb_cb_t) usb_hmsc_check_result);

            /* Control Transfer overlaps */
            if (USB_QOVR == err)
            {
                usb_hmsc_message_retry(USB_HMSC_MBX, mess);
            }
            else
            {
                /* Control Transfer not overlaps */
                usb_shmsc_stall_err_seq[mess->ip]++;
            }

            break;
        }

        case USB_SEQ_1:
        {
            if (USB_IP1 == mess->ip)
            {
                devadr |= USBA_ADDRESS_OFFSET;
            }

            side = usb_hmsc_ref_drvno(devadr);

            if (USB_ERROR == side)
            {
                usb_hmsc_command_result(mess, USB_HMSC_CBW_ERR);
                usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;

                return;
            }

            usb_hmsc_clear_stall(mess, g_usb_hmsc_out_pipe[mess->ip][side], usb_hmsc_check_result);
            usb_shmsc_stall_err_seq[mess->ip]++;
            g_usb_hmsc_out_pipectr[mess->ip][side] = 0;
            break;
        }

        case USB_SEQ_2:
        {
            if (USB_IP1 == mess->ip)
            {
                devadr |= USBA_ADDRESS_OFFSET;
            }

            side = usb_hmsc_ref_drvno(devadr);

            if (USB_ERROR == side)
            {
                usb_hmsc_command_result(mess, USB_HMSC_CBW_ERR);
                usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;

                return;
            }

            usb_hmsc_clear_stall(mess, g_usb_hmsc_in_pipe[mess->ip][side], usb_hmsc_check_result);
            usb_shmsc_stall_err_seq[mess->ip]++;
            g_usb_hmsc_in_pipectr[mess->ip][side] = 0;
            break;
        }

        case USB_SEQ_3:
        {
            if (USB_MSG_HMSC_CSW_PHASE_ERR == mess->msginfo)
            {
                result = USB_HMSC_CSW_PHASE_ERR;
            }
            else
            {
                result = USB_HMSC_CBW_ERR;
            }

            usb_hmsc_command_result(mess, result);
            usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
            break;
        }

        default:
        {
            if (USB_MSG_HMSC_CSW_PHASE_ERR == mess->msginfo)
            {
                result = USB_HMSC_CSW_PHASE_ERR;
            }
            else
            {
                result = USB_HMSC_CBW_ERR;
            }

            usb_hmsc_command_result(mess, result);
            usb_shmsc_stall_err_seq[mess->ip] = USB_SEQ_0;
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hmsc_stall_err
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_specified_path
 * Description     : Next Process Selector
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_specified_path (usb_utr_t * mess)
{
    usb_utr_t * pblf;
    usb_er_t    err;

    /* Get mem pool blk */
    if (USB_OK == USB_PGET_BLK(USB_HMSC_MPL, &pblf))
    {
        *pblf         = *mess;
        pblf->msginfo = usb_shmsc_process[mess->ip];

        /* Send message */
        err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t *) pblf);
        if (USB_OK != err)
        {
            USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t) pblf);
            USB_PRINTF0("### SpecifiedPass function snd_msg error\n");
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
 * End of function usb_hmsc_specified_path
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_check_result
 * Description     : Hub class check result
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_check_result (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;
    mess->result = mess->status;
    usb_hmsc_specified_path(mess);
}

/******************************************************************************
 * End of function usb_hmsc_check_result
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_command_result
 * Description     : Hub class check result
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     result  : Command Result
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_command_result (usb_utr_t * ptr, uint16_t result)
{
    usb_utr_t * pblf;
    usb_er_t    err;

    /* Get mem pool blk */
    if (USB_OK == USB_PGET_BLK(USB_HSTRG_MPL, &pblf))
    {
        pblf->msginfo = g_usb_hmsc_strg_process[ptr->ip];
        pblf->result  = result;
        pblf->ip      = ptr->ip;
        pblf->ipp     = ptr->ipp;
        pblf->tranlen = ptr->tranlen;

        /* Send message */
        err = USB_SND_MSG(USB_HSTRG_MBX, (usb_msg_t *) pblf);
        if (USB_OK != err)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) pblf);
            USB_PRINTF0("### CheckResult function snd_msg error\n");
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
 * End of function usb_hmsc_command_result
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_get_string_desc
 * Description     : Set GetDescriptor
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     addr        : Device address
 *               : uint16_t     string      : String Descriptor index
 *               : usb_cb_t     complete    : callback function
 * Return value    : uint16_t                 : error info
 ******************************************************************************/
static uint16_t usb_hmsc_get_string_desc (usb_utr_t * ptr, uint16_t addr, uint16_t string, usb_cb_t complete)
{
 #if (BSP_CFG_RTOS == 0)
    uint16_t ret_code;
 #endif                                /* (BSP_CFG_RTOS == 0) */
    uint16_t                i;
    static usb_ctrl_trans_t string_setup[USB_NUM_USBIP];
 #if (BSP_CFG_RTOS == 2)
    usb_er_t err;
    uint16_t hmsc_retval;
 #endif                                /* (BSP_CFG_RTOS == 2) */

    if (0 == string)
    {
        string_setup[ptr->ip].setup.request_index  = (uint16_t) 0x0000;
        string_setup[ptr->ip].setup.request_length = (uint16_t) 0x0004;
    }
    else
    {
        /* Set LanguageID */
        string_setup[ptr->ip].setup.request_index  = (uint16_t) (g_usb_hmsc_class_data[ptr->ip][2]);
        string_setup[ptr->ip].setup.request_index |= (uint16_t) ((uint16_t) (g_usb_hmsc_class_data[ptr->ip][3]) << 8);
        string_setup[ptr->ip].setup.request_length = (uint16_t) USB_HMSC_CLSDATASIZE;
    }

    string_setup[ptr->ip].setup.request_type  = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    string_setup[ptr->ip].setup.request_value = (uint16_t) (USB_STRING_DESCRIPTOR + string);
    string_setup[ptr->ip].address             = addr;

    /* WAIT_LOOP */
    for (i = 0; i < string_setup[ptr->ip].setup.request_length; i++)
    {
        g_usb_hmsc_class_data[ptr->ip][i] = (uint8_t) USB_VALUE_FFH;
    }

    g_usb_hmsc_class_control[ptr->ip].p_tranadr = (void *) g_usb_hmsc_class_data[ptr->ip];
    g_usb_hmsc_class_control[ptr->ip].complete  = complete;
    g_usb_hmsc_class_control[ptr->ip].tranlen   = (uint32_t) string_setup[ptr->ip].setup.request_length;
    g_usb_hmsc_class_control[ptr->ip].keyword   = USB_PIPE0;
    g_usb_hmsc_class_control[ptr->ip].p_setup   = (uint16_t *) &string_setup[ptr->ip];
    g_usb_hmsc_class_control[ptr->ip].segment   = USB_TRAN_END;

    g_usb_hmsc_class_control[ptr->ip].ip  = ptr->ip;
    g_usb_hmsc_class_control[ptr->ip].ipp = ptr->ipp;

 #if (BSP_CFG_RTOS == 2)
    err = usb_hstd_transfer_start_req(&g_usb_hmsc_class_control[ptr->ip]);
    if (USB_OK == err)
    {
        hmsc_retval = usb_hmsc_req_trans_wait_tmo((uint16_t) USB_VALUE_3000);
        if (USB_DATA_STALL == hmsc_retval)
        {
            USB_PRINTF0("*** GetStringDesc STALL !\n");
            hmsc_retval = USB_ERROR;
        }
        else if (USB_DATA_TMO == hmsc_retval)
        {
            USB_PRINTF0("*** GetStringDesc Timeout error !\n");
            hmsc_retval = USB_ERROR;
        }
        else if (USB_CTRL_END != hmsc_retval)
        {
            USB_PRINTF0("*** GetStringDesc error !\n");
            hmsc_retval = USB_ERROR;
        }
        else
        {
            hmsc_retval = USB_OK;
        }
    }
    else
    {
        hmsc_retval = USB_ERROR;
    }

    return hmsc_retval;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    if (USB_OK == usb_hstd_transfer_start_req(&g_usb_hmsc_class_control[ptr->ip]))
    {
        ret_code = USB_OK;
    }
    else
    {
        ret_code = USB_ERROR;
    }
    return ret_code;
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_get_string_desc
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_send_cbw
 * Description     : Send CBW
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 * Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_cbw (usb_utr_t * ptr, uint16_t side)
{
    usb_er_t err;
    uint16_t toggle;
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;
 #endif                                /* (BSP_CFG_RTOS == 2) */
    uint16_t pipe;

    pipe = g_usb_hmsc_out_pipe[ptr->ip][side];

    /* Set CBW TAG usb_hmsc_CbwTagCount()*/
    g_usb_hmsc_csw_tag_no[ptr->ip][side]++;
    if ((uint16_t) 0 == g_usb_hmsc_csw_tag_no[ptr->ip][side])
    {
        g_usb_hmsc_csw_tag_no[ptr->ip][side] = (uint16_t) 1;
    }

    /* pipe number */
    usb_hmsc_trans_data[ptr->ip][side].keyword = pipe;

    /* Transfer data address */
    usb_hmsc_trans_data[ptr->ip][side].p_tranadr = (void *) &g_usb_hmsc_cbw[ptr->ip][side];

    /* Transfer data length */
    usb_hmsc_trans_data[ptr->ip][side].tranlen = (uint32_t) USB_MSC_CBWLENGTH;

    /* Call Back Function Info */
 #if (BSP_CFG_RTOS == 2)
    usb_hmsc_trans_data[ptr->ip][side].complete = &usb_hmsc_trans_result;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_hmsc_trans_data[ptr->ip][side].complete = &usb_hmsc_check_result;
 #endif /* (BSP_CFG_RTOS == 2) */

    /* Not control transfer */
    usb_hmsc_trans_data[ptr->ip][side].p_setup = 0;
    usb_hmsc_trans_data[ptr->ip][side].segment = USB_TRAN_END;

    usb_hmsc_trans_data[ptr->ip][side].ip  = ptr->ip;
    usb_hmsc_trans_data[ptr->ip][side].ipp = ptr->ipp;

    usb_hmsc_trans_data[ptr->ip][side].p_transfer_rx = ptr->p_transfer_rx;
    usb_hmsc_trans_data[ptr->ip][side].p_transfer_tx = ptr->p_transfer_tx;

    usb_hstd_set_pipe_info(ptr->ip, pipe, &g_usb_hmsc_pipe_table[side][USB_PIPE_DIR_OUT]);
    usb_hstd_set_pipe_reg(ptr, pipe);

    if (USB_SQMON == (USB_SQMON & g_usb_hmsc_out_pipectr[ptr->ip][side]))
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }

    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, pipe);
    err = usb_hstd_transfer_start(&usb_hmsc_trans_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);

        return USB_HMSC_SUBMIT_ERR;
    }

 #if (BSP_CFG_RTOS == 2)
    hmsc_retval = usb_hmsc_trans_wait_tmo((uint16_t) USB_VALUE_3000);
    ptr->status = hmsc_retval;         /* Record the result of the request */
    switch (hmsc_retval)
    {
        case USB_DATA_NONE:            /* Send CBW */
        {
            g_usb_hmsc_out_pipectr[ptr->ip][side] = hw_usb_read_pipectr(ptr, pipe);

            return USB_HMSC_OK;
            break;
        }

        case USB_DATA_STALL:           /* Stall */
        {
            USB_PRINTF1("*** CBW Transfer STALL(drive:%d) !\n", side);

            /* Reset */
            usb_hmsc_mass_storage_reset(ptr, g_usb_hmsc_drvno_tbl[side].devadr, usb_hmsc_trans_result);

            /* Clear Stall for OUT pipe */
            usb_hmsc_clear_stall(ptr, g_usb_hmsc_out_pipe[ptr->ip][side], class_trans_result);
            g_usb_hmsc_out_pipectr[ptr->ip][side] = 0;

            /* Clear Stall for IN pipe */
            usb_hmsc_clear_stall(ptr, g_usb_hmsc_in_pipe[ptr->ip][side], class_trans_result);
            g_usb_hmsc_in_pipectr[ptr->ip][side] = 0;
            break;
        }

        case USB_DATA_TMO:             /* Timeout */
        {
            USB_PRINTF1("### CBW Transfer timeout ERROR(drive:%d) !\n", side);
            usb_hstd_transfer_end(ptr, g_usb_hmsc_out_pipe[ptr->ip][side], hmsc_retval);
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### CBW Transfer ERROR(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF1("### CBW Transfer ERROR(drive:%d) !\n", side);
            break;
        }
    }

    return USB_HMSC_CBW_ERR;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    return USB_HMSC_OK;
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_send_cbw
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_send_cbw_check
 * Description     : Check send CBW
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 *               : uint16_t     result      : Transfer Result
 * Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_cbw_check (usb_utr_t * ptr, uint16_t side, uint16_t result)
{
    switch (result)
    {
        case USB_DATA_NONE:            /* Send CBW */
        {
            g_usb_hmsc_out_pipectr[ptr->ip][side] = usb_hmsc_trans_data[ptr->ip][side].pipectr;

            return USB_HMSC_OK;
            break;
        }

        case USB_DATA_STALL:           /* Stall */
        {
            USB_PRINTF1("*** CBW Transfer STALL(drive:%d) !\n", side);

/*        return USB_DATA_STALL;*/
            return USB_HMSC_STALL;
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### CBW Transfer ERROR(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF2("### CBW Transfer error(drive:%d) result:%d !\n", side, result);
            break;
        }
    }

    return USB_HMSC_CBW_ERR;
}

/******************************************************************************
 * End of function usb_hmsc_send_cbw_check
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_get_data
 * Description     : Receive Data request
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 *               : uint8_t      *buff       : Pointer to the area to store the data
 *               : uint32_t     size        : Receive Data Size
 * Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_data (usb_utr_t * ptr, uint16_t side, uint8_t * buff, uint32_t size)
{
    usb_er_t err;
    uint16_t toggle;
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;
 #endif                                /* (BSP_CFG_RTOS == 2) */
    uint16_t pipe;

    pipe = g_usb_hmsc_in_pipe[ptr->ip][side];

    /* pipe number */
    usb_hmsc_receive_data[ptr->ip][side].keyword = pipe;

    /* Transfer data address */
    usb_hmsc_receive_data[ptr->ip][side].p_tranadr = (void *) buff;

    /* Transfer data length */
    usb_hmsc_receive_data[ptr->ip][side].tranlen = size;

    /* Call Back Function Info */
 #if (BSP_CFG_RTOS == 2)
    usb_hmsc_receive_data[ptr->ip][side].complete = &usb_hmsc_trans_result;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_hmsc_receive_data[ptr->ip][side].complete = &usb_hmsc_check_result;
 #endif /* (BSP_CFG_RTOS == 2) */

    /* Not control transfer */
    usb_hmsc_receive_data[ptr->ip][side].p_setup = 0;
    usb_hmsc_receive_data[ptr->ip][side].segment = USB_TRAN_END;
    usb_hmsc_receive_data[ptr->ip][side].ip      = ptr->ip;
    usb_hmsc_receive_data[ptr->ip][side].ipp     = ptr->ipp;

    usb_hmsc_receive_data[ptr->ip][side].p_transfer_rx = ptr->p_transfer_rx;
    usb_hmsc_receive_data[ptr->ip][side].p_transfer_tx = ptr->p_transfer_tx;

    usb_hstd_set_pipe_info(ptr->ip, pipe, &g_usb_hmsc_pipe_table[side][USB_PIPE_DIR_IN]);
    usb_hstd_set_pipe_reg(ptr, pipe);

    if (USB_SQMON == (USB_SQMON & g_usb_hmsc_in_pipectr[ptr->ip][side]))
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }

    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, pipe);

    err = usb_hstd_transfer_start(&usb_hmsc_receive_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);

        return USB_HMSC_SUBMIT_ERR;
    }

 #if (BSP_CFG_RTOS == 2)
    hmsc_retval = usb_hmsc_trans_wait_tmo((uint16_t) USB_VALUE_3000);
    ptr->status = hmsc_retval;         /* Record the result of the request */
    switch (hmsc_retval)
    {
        case USB_DATA_SHT:             /* Continue */
        case USB_DATA_OK:
        {
            g_usb_hmsc_in_pipectr[ptr->ip][side] = hw_usb_read_pipectr(ptr, pipe);

            return USB_HMSC_OK;
            break;
        }

        case USB_DATA_STALL:
        {
            USB_PRINTF1("*** GetData STALL(drive:%d) !\n", side);
            g_usb_hmsc_in_pipectr[ptr->ip][side] = 0;
            usb_hmsc_clear_stall(ptr, g_usb_hmsc_in_pipe[ptr->ip][side], class_trans_result);

            return USB_HMSC_OK;
            break;
        }

        case USB_DATA_TMO:             /* Timeout */
        {
            USB_PRINTF1("### GetData time-out ERROR(drive:%d) !\n", side);
            usb_hstd_transfer_end(ptr, g_usb_hmsc_in_pipe[ptr->ip][side], (uint16_t) USB_DATA_TMO);
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### GetData ERROR(drive:%d) !\n", side);
            break;
        }

        case USB_DATA_OVR:
        {
            USB_PRINTF1("### GetData over(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF1("### GetData ERROR(drive:%d) !\n", side);
            break;
        }
    }

    return USB_HMSC_DAT_RD_ERR;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    return USB_HMSC_OK;
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_get_data
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_get_data_check
 * Description     : Check Get Data
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 *               : uint16_t     result      : Transfer Result
 * Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_data_check (usb_utr_t * ptr, uint16_t side, uint16_t result)
{
    switch (result)
    {
        case USB_DATA_SHT:

        /* Continue */
        case USB_DATA_OK:
        {
            g_usb_hmsc_in_pipectr[ptr->ip][side] = usb_hmsc_receive_data[ptr->ip][side].pipectr;

            return USB_HMSC_OK;
            break;
        }

        case USB_DATA_STALL:
        {
            USB_PRINTF1("*** GetData STALL(drive:%d) !\n", side);
            g_usb_hmsc_in_pipectr[ptr->ip][side] = 0;

            return USB_HMSC_STALL;
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### GetData ERROR(drive:%d) !\n", side);
            break;
        }

        case USB_DATA_OVR:
        {
            USB_PRINTF1("### GetData over(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF1("### GetData error(drive:%d) !\n", side);
            break;
        }
    }

    return USB_HMSC_DAT_RD_ERR;
}

 #endif                                /* (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * End of function usb_hmsc_get_data_check
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_send_data
 * Description     : Send Pipe Data
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 *               : uint8_t      *buff       : Pointer to the area to store the data
 *               : uint32_t     size        : Receive Data Size
 * Return value    : uint16_t                : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_data (usb_utr_t * ptr, uint16_t side, uint8_t * buff, uint32_t size)
{
    usb_er_t err;
    uint16_t toggle;
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;
 #endif                                /* (BSP_CFG_RTOS == 2) */
    uint16_t pipe;

    pipe = g_usb_hmsc_out_pipe[ptr->ip][side];

    /* pipe number */
    usb_hmsc_trans_data[ptr->ip][side].keyword = pipe;

    /* Transfer data address */
    usb_hmsc_trans_data[ptr->ip][side].p_tranadr = (void *) buff;

    /* Transfer data length */
    usb_hmsc_trans_data[ptr->ip][side].tranlen = size;

    /* Call Back Function Info */
 #if (BSP_CFG_RTOS == 2)
    usb_hmsc_trans_data[ptr->ip][side].complete = &usb_hmsc_trans_result;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_hmsc_trans_data[ptr->ip][side].complete = &usb_hmsc_check_result;
 #endif /* (BSP_CFG_RTOS == 2) */

    /* Not control transfer */
    usb_hmsc_trans_data[ptr->ip][side].p_setup = 0;
    usb_hmsc_trans_data[ptr->ip][side].segment = USB_TRAN_END;
    usb_hmsc_trans_data[ptr->ip][side].ip      = ptr->ip;
    usb_hmsc_trans_data[ptr->ip][side].ipp     = ptr->ipp;

    usb_hstd_set_pipe_info(ptr->ip, pipe, &g_usb_hmsc_pipe_table[side][USB_PIPE_DIR_OUT]);
    usb_hstd_set_pipe_reg(ptr, pipe);

    if (USB_SQMON == (USB_SQMON & g_usb_hmsc_out_pipectr[ptr->ip][side]))
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }

    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, pipe);
    err = usb_hstd_transfer_start(&usb_hmsc_trans_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);

        return USB_HMSC_SUBMIT_ERR;
    }

 #if (BSP_CFG_RTOS == 2)
    hmsc_retval = usb_hmsc_trans_wait_tmo((uint16_t) USB_VALUE_3000);
    ptr->status = hmsc_retval;         /* Record the result of the request */
    switch (hmsc_retval)
    {
        case USB_DATA_NONE:
        {
            g_usb_hmsc_out_pipectr[ptr->ip][side] = hw_usb_read_pipectr(ptr, pipe);

            return USB_HMSC_OK;
            break;
        }

        case USB_DATA_STALL:
        {
            USB_PRINTF1("*** SendData STALL(drive:%d) !\n", side);
            g_usb_hmsc_out_pipectr[ptr->ip][side] = 0;
            usb_hmsc_clear_stall(ptr, g_usb_hmsc_out_pipe[ptr->ip][side], class_trans_result);

            return USB_HMSC_STALL;
            break;
        }

        case USB_DATA_TMO:             /* Timeout */
        {
            USB_PRINTF1("### SendData time-out ERROR(drive:%d) !\n", side);
            usb_hstd_transfer_end(ptr, g_usb_hmsc_out_pipe[ptr->ip][side], (uint16_t) USB_DATA_TMO);
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### SendData ERROR(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF1("### SendData ERROR(drive:%d) !\n", side);
            break;
        }
    }

    return USB_HMSC_DAT_WR_ERR;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    return USB_HMSC_OK;
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_send_data
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_send_data_check
 * Description     : Check Send Data
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 *               : uint16_t     result      : Transfer Result
 * Return value    : uint16_t                  : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_send_data_check (usb_utr_t * ptr, uint16_t side, uint16_t result)
{
    switch (result)
    {
        case USB_DATA_NONE:
        {
            g_usb_hmsc_out_pipectr[ptr->ip][side] = usb_hmsc_trans_data[ptr->ip][side].pipectr;

            return USB_HMSC_OK;
            break;
        }

        case USB_DATA_STALL:
        {
            USB_PRINTF1("*** SendData STALL(drive:%d) !\n", side);
            g_usb_hmsc_out_pipectr[ptr->ip][side] = 0;

            return USB_HMSC_STALL;
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### SendData ERROR(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF1("### SendData error(drive:%d) !\n", side);
            break;
        }
    }

    return USB_HMSC_DAT_WR_ERR;
}

/******************************************************************************
 * End of function usb_hmsc_send_data_check
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_get_csw
 * Description     : Receive CSW
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 * Return value    : uint16_t                  : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_csw (usb_utr_t * ptr, uint16_t side)
{
    usb_er_t err;
    uint16_t toggle;
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;
    uint32_t request_size;
 #endif                                /* (BSP_CFG_RTOS == 2) */
    uint16_t pipe;

    pipe = g_usb_hmsc_in_pipe[ptr->ip][side];

    /* pipe number */
    usb_hmsc_receive_data[ptr->ip][side].keyword = pipe;

    /* Transfer data address */
    usb_hmsc_receive_data[ptr->ip][side].p_tranadr = (void *) &g_usb_hmsc_csw[ptr->ip][side];

    /* Transfer data length */
    usb_hmsc_receive_data[ptr->ip][side].tranlen = (uint32_t) USB_MSC_CSW_LENGTH;

    /* Call Back Function Info */
 #if (BSP_CFG_RTOS == 2)
    usb_hmsc_receive_data[ptr->ip][side].complete = &usb_hmsc_trans_result;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_hmsc_receive_data[ptr->ip][side].complete = &usb_hmsc_check_result;
 #endif /* (BSP_CFG_RTOS == 2) */
    usb_hmsc_receive_data[ptr->ip][side].p_setup = 0;

    /* Not control transfer */
    usb_hmsc_receive_data[ptr->ip][side].segment = USB_TRAN_END;
    usb_hmsc_receive_data[ptr->ip][side].ip      = ptr->ip;
    usb_hmsc_receive_data[ptr->ip][side].ipp     = ptr->ipp;

    usb_hstd_set_pipe_info(ptr->ip, pipe, &g_usb_hmsc_pipe_table[side][USB_PIPE_DIR_IN]);
    usb_hstd_set_pipe_reg(ptr, pipe);

    if (USB_SQMON == (USB_SQMON & g_usb_hmsc_in_pipectr[ptr->ip][side]))
    {
        toggle = USB_DO_SET_SQTGL;
    }
    else
    {
        toggle = USB_DO_CLR_SQTGL;
    }

    usb_hstd_change_device_state(ptr, (usb_cb_t) &usb_hstd_dummy_function, toggle, pipe);

    err = usb_hstd_transfer_start(&usb_hmsc_receive_data[ptr->ip][side]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### Mass Storage Device Class submit error(drive:%d) !\n", side);

        return USB_HMSC_SUBMIT_ERR;
    }

 #if (BSP_CFG_RTOS == 2)
    hmsc_retval = usb_hmsc_trans_wait_tmo((uint16_t) USB_VALUE_3000);
    ptr->status = hmsc_retval;         /* Record the result of the request */
    switch (hmsc_retval)
    {
        case USB_DATA_SHT:             /* Continue */
        case USB_DATA_OK:
        {
            g_usb_hmsc_in_pipectr[ptr->ip][side] = hw_usb_read_pipectr(ptr, pipe);

            request_size = g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_lo;
            request_size = (uint32_t) (request_size | (uint32_t) (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_ml << 8));
            request_size = (uint32_t) (request_size | (uint32_t) (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_mh << 16));
            request_size = (uint32_t) (request_size | (uint32_t) (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_hi << 24));
            ptr->tranlen = request_size - g_usb_hmsc_cmd_data_length[ptr->ip];

            /* CSW Check */
            if (USB_MSC_CSW_SIGNATURE != g_usb_hmsc_csw[ptr->ip][side].dcsw_signature)
            {
                USB_PRINTF2("### CSW signature error 0x%08lx:SIGN=0x%08lx.\n",
                            (unsigned long) g_usb_hmsc_csw[ptr->ip][side].dcsw_signature,
                            (unsigned long) USB_MSC_CSW_SIGNATURE);

                return USB_HMSC_CSW_ERR;
            }

            if (g_usb_hmsc_csw[ptr->ip][side].dcsw_tag != g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag)
            {
                USB_PRINTF2("### CSW Tag error 0x%08lx:CBWTAG=0x%08lx.\n",
                            (unsigned long) g_usb_hmsc_csw[ptr->ip][side].dcsw_tag,
                            (unsigned long) g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag);

                return USB_HMSC_CSW_ERR;
            }

            switch (g_usb_hmsc_csw[ptr->ip][side].dcsw_status)
            {
                case USB_MSC_CSW_OK:
                {
                    return USB_HMSC_OK;
                    break;
                }

                case USB_MSC_CSW_NG:
                {
                    return USB_HMSC_CSW_ERR;
                    break;
                }

                case USB_MSC_CSW_PHASE_ERR:
                {
                    if (USB_ON == usb_hmsc_csw_err_stall[ptr->ip])
                    {
                        usb_hmsc_csw_err_stall[ptr->ip] = USB_OFF;

                        /* Reset */
                        usb_hmsc_mass_storage_reset(ptr, g_usb_hmsc_drvno_tbl[side].devadr, usb_hmsc_trans_result);

                        /* Clear STALL for OUT pipe */
                        usb_hmsc_clear_stall(ptr, g_usb_hmsc_out_pipe[ptr->ip][side], class_trans_result);
                        g_usb_hmsc_out_pipectr[ptr->ip][side] = 0;

                        /* Clear STALL for IN pipe */
                        usb_hmsc_clear_stall(ptr, g_usb_hmsc_in_pipe[ptr->ip][side], class_trans_result);
                        g_usb_hmsc_in_pipectr[ptr->ip][side] = 0;
                    }

                    return USB_HMSC_CSW_PHASE_ERR;
                    break;
                }

                default:
                {
                    break;
                }
            }

            return USB_HMSC_CSW_ERR;
            break;
        }

        case USB_DATA_STALL:           /* Stall */
        {
            USB_PRINTF1("*** GetCSW Transfer STALL(drive:%d) !\n", side);

            return USB_HMSC_STALL;
            break;
        }

        case USB_DATA_TMO:
        {
            USB_PRINTF1("### GetCSW Transfer error(drive:%d) !\n", side);
            usb_hstd_transfer_end(ptr, g_usb_hmsc_in_pipe[ptr->ip][side], (uint16_t) USB_DATA_TMO);
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### GetCSW Transfer ERROR(drive:%d) !\n", side);
            break;
        }

        case USB_DATA_OVR:
        {
            USB_PRINTF1("### GetCSW receive over(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF1("### GetCSW Transfer error(drive:%d) !\n", side);
            break;
        }
    }

    return USB_HMSC_CSW_ERR;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    return USB_HMSC_OK;
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_get_csw
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_get_csw_check
 * Description     : Check Receive CSW
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     side        : Drive Number
 *               : uint16_t     result      : Transfer Result
 * Return value    : uint16_t                 : Error Code
 ******************************************************************************/
static uint16_t usb_hmsc_get_csw_check (usb_utr_t * ptr, uint16_t side, uint16_t result)
{
    uint32_t request_size;

    ptr->tranlen = 0;
    ptr->status  = g_usb_hmsc_csw[ptr->ip][side].dcsw_status;

    switch (result)
    {
        case USB_DATA_SHT:

        /* Continue */
        case USB_DATA_OK:
        {
            g_usb_hmsc_in_pipectr[ptr->ip][side] = usb_hmsc_receive_data[ptr->ip][side].pipectr;

            request_size = g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_lo;
            request_size = (uint32_t) (request_size | (uint32_t) (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_ml << 8));
            request_size = (uint32_t) (request_size | (uint32_t) (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_mh << 16));
            request_size = (uint32_t) (request_size | (uint32_t) (g_usb_hmsc_cbw[ptr->ip][side].dcbw_dtl_hi << 24));
            ptr->tranlen = request_size - g_usb_hmsc_cmd_data_length[ptr->ip];

            /* CSW Check */
            if (USB_MSC_CSW_SIGNATURE != g_usb_hmsc_csw[ptr->ip][side].dcsw_signature)
            {
                USB_PRINTF2("### CSW signature error 0x%08lx:SIGN=0x%08lx.\n",
                            (unsigned long) g_usb_hmsc_csw[ptr->ip][side].dcsw_signature,
                            (unsigned long) USB_MSC_CSW_SIGNATURE);

                return USB_HMSC_CSW_ERR;
            }

            if (g_usb_hmsc_csw[ptr->ip][side].dcsw_tag != g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag)
            {
                USB_PRINTF2("### CSW Tag error 0x%08lx:CBWTAG=0x%08lx.\n",
                            (unsigned long) g_usb_hmsc_csw[ptr->ip][side].dcsw_tag,
                            (unsigned long) g_usb_hmsc_cbw[ptr->ip][side].dcbw_tag);

                return USB_HMSC_CSW_ERR;
            }

            switch (g_usb_hmsc_csw[ptr->ip][side].dcsw_status)
            {
                case USB_MSC_CSW_OK:
                {
                    return USB_HMSC_OK;
                    break;
                }

                case USB_MSC_CSW_NG:
                {
                    return USB_HMSC_CSW_ERR;
                    break;
                }

                case USB_MSC_CSW_PHASE_ERR:
                {
                    return USB_HMSC_CSW_PHASE_ERR;
                    break;
                }

                default:
                {
                    break;
                }
            }

            return USB_HMSC_CSW_ERR;
            break;
        }

        case USB_DATA_STALL:
        {
            /* Stall */
            USB_PRINTF1("*** GetCSW Transfer STALL(drive:%d) !\n", side);

            return USB_HMSC_STALL;
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF1("### GetCSW Transfer ERROR(drive:%d) !\n", side);
            break;
        }

        case USB_DATA_OVR:
        {
            USB_PRINTF1("### GetCSW receive over(drive:%d) !\n", side);
            break;
        }

        default:
        {
            USB_PRINTF1("### GetCSW Transfer error(drive:%d) !\n", side);
            break;
        }
    }

    return USB_HMSC_CSW_ERR;
}

/******************************************************************************
 * End of function usb_hmsc_get_csw_check
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_clear_stall
 * Description     : Clear Stall
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     pipe        : Pipe number
 *               : usb_cb_t     complete    : Callback function
 * Return value    : uint16_t
 ******************************************************************************/
static usb_er_t usb_hmsc_clear_stall (usb_utr_t * ptr, uint16_t pipe, usb_cb_t complete)
{
    usb_er_t err;

 #if (BSP_CFG_RTOS == 2)
    err = usb_hstd_clr_stall(ptr, pipe, complete);
    if (USB_OK == err)
    {
        /* Clear STALL pipe 0 */
        usb_cstd_clr_stall(ptr, (uint16_t) USB_PIPE0);

        /* SQCLR */
        usb_hstd_change_device_state(ptr, usb_hstd_dummy_function, USB_DO_CLR_SQTGL, (uint16_t) USB_PIPE0);
    }

 #else
    err = usb_hstd_change_device_state(ptr, complete, USB_DO_CLR_STALL, pipe);
 #endif                                /* (BSP_CFG_RTOS == 2) */

    return err;
}

/******************************************************************************
 * End of function usb_hmsc_clear_stall
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_std_req_check
 * Description     : Sample Standard Request Check
 * Arguments       : uint16_t result        : Transfer Result
 * Return value    : uint16_t               : error info
 ******************************************************************************/
static uint16_t usb_hmsc_std_req_check (uint16_t result)
{
    uint16_t ret_code;

    ret_code = USB_OK;

    if (USB_DATA_STALL == result)
    {
        USB_PRINTF0("*** Standard Request STALL !\n");
        ret_code = USB_ERROR;
    }
    else if (USB_CTRL_END != result)
    {
        USB_PRINTF0("*** Standard Request error !\n");
        ret_code = USB_ERROR;
    }
    else
    {
        /* Non */
    }

    return ret_code;
}

/******************************************************************************
 * End of function usb_hmsc_std_req_check
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_class_check_result
 * Description     : Hub class check result
 * Arguments       : usb_utr_t    *mess       : Pointer to usb_utr_t structure
 *               : uint16_t     data1       : Not used
 *               : uint16_t     data2       : Not used
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_class_check_result (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_utr_t * pblf;
    usb_er_t    err;

    (void) data1;
    (void) data2;

    /* Get mem pool blk */
    if (USB_OK == USB_PGET_BLK(USB_HMSC_MPL, &pblf))
    {
        pblf->msginfo = USB_MSG_CLS_INIT;
        pblf->keyword = mess->keyword;
        pblf->result  = mess->status;

        pblf->ip  = mess->ip;
        pblf->ipp = mess->ipp;

        USB_PRINTF0("### usb_hmsc_class_check_resultn snd_msg \n");

        /* Send message */
        err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t *) pblf);
        if (USB_OK != err)
        {
            USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t) pblf);
            USB_PRINTF0("### usb_hmsc_class_check_resultn snd_msg error\n");
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

 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * End of function usb_hmsc_class_check_result
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_pipe_info
 * Description     : Pipe Information
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint8_t      *table  : Pointer to the pipe information table
 *               : uint16_t     side    : Drive number
 *               : uint16_t     speed   : USB speed
 *               : uint16_t     length  : Data size
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_pipe_info (usb_utr_t * ptr, uint8_t * table, uint16_t side, uint16_t speed, uint16_t length)
{
    uint16_t  epcnt = 0;
    uint16_t  ofdsc;
    uint16_t  ip;
    uint8_t * pdescriptor;
    usb_utr_t devadr;

    ip = ptr->ip;
    if (USB_DT_INTERFACE != table[1])                    /* Check Descriptor */
    {
        USB_PRINTF0("### Not Interface pdescriptor.\n"); /* Configuration Descriptor */

        return USB_ERROR;
    }

    ofdsc = table[0];                           /* Check Endpoint Descriptor */
    g_usb_hmsc_out_pipe[ip][side] = USB_NOPORT; /* Pipe initial */
    g_usb_hmsc_in_pipe[ip][side]  = USB_NOPORT;

    /* WAIT_LOOP */
    while (ofdsc < (length - table[0]))
    {
        if (USB_DT_ENDPOINT == table[ofdsc + 1])                     /* Search within Interface */
        {
            if (USB_EP_BULK == (table[ofdsc + 3] & USB_EP_TRNSMASK)) /* Bulk Endpoint */
            {
                pdescriptor = &table[ofdsc];

                usb_hmsc_drive_to_addr(side, &devadr);               /* Get USB Device address -> "devadr.keyword" */

                if (USB_EP_IN == (pdescriptor[2] & USB_EP_DIRMASK))
                {
                    g_usb_hmsc_in_pipe[ip][side] = usb_hstd_make_pipe_reg_info(ip,
                                                                               devadr.keyword,
                                                                               USB_CLASS_INTERNAL_HMSC,
                                                                               speed,
                                                                               pdescriptor,
                                                                               &g_usb_hmsc_pipe_table[side][
                                                                                   USB_PIPE_DIR_IN]);
                }
                else
                {
                    g_usb_hmsc_out_pipe[ip][side] = usb_hstd_make_pipe_reg_info(ip,
                                                                                devadr.keyword,
                                                                                USB_CLASS_INTERNAL_HMSC,
                                                                                speed,
                                                                                pdescriptor,
                                                                                &g_usb_hmsc_pipe_table[side][
                                                                                    USB_PIPE_DIR_OUT]);
                }

                if ((USB_NOPORT != g_usb_hmsc_in_pipe[ip][side]) && (USB_NOPORT != g_usb_hmsc_out_pipe[ip][side]))
                {
                    return USB_OK;
                }

                epcnt++;
                if (epcnt >= 2)
                {
                    USB_PRINTF0("### Endpoint Descriptor error.\n");

                    return USB_ERROR;
                }
            }
        }

        ofdsc = (uint16_t) (ofdsc + table[ofdsc]);
    }

    return USB_ERROR;
}

/******************************************************************************
 * End of function usb_hmsc_pipe_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_configured
 * Description     : Callback function for MSC device configured
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     devadr  : Device Address
 *               : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_configured (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    uint16_t ret;
    uint16_t side;

    (void) data2;

    ret = usb_hmsc_strg_drive_open(ptr, devadr, &side);
    if (USB_ERROR == ret)
    {
        USB_PRINTF1("### usb_hmsc_strg_drive_open error (%x)\n", ret);
        usb_hstd_connect_err_event_set(ptr->ip);
    }

 #if (BSP_CFG_RTOS == 2)
    xSemaphoreTake(SemaphoreHandleRead, portMAX_DELAY);
    usb_hmsc_strg_drive_search(ptr, devadr, (usb_cb_t) usb_hmsc_drive_complete);
    xSemaphoreGive(SemaphoreHandleRead);
 #endif                                /* BSP_CFG_RTOS == 2 */
}

/******************************************************************************
 * End of function usb_hmsc_configured
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_detach
 * Description     : Callback function for MSC device detach
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     addr    : Device Address
 *               : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_detach (usb_utr_t * ptr, uint16_t addr, uint16_t data2)
{
 #if (BSP_CFG_RTOS == 0)
    uint16_t            i;
    uint16_t            j;
    uint16_t            side;
    uint16_t            que_cnt;
    usb_instance_ctrl_t ctrl;
    uint16_t            ipno_devaddr;
    usb_cfg_t         * p_cfg = USB_NULL;
    (void) data2;

    if (ptr->ip)
    {
  #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
  #endif                               /* #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME) */
    }
    else
    {
  #if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
  #endif                               /* #if defined(VECTOR_NUMBER_USBFS_INT) */
    }

    /* Clear pipe table. */
    usb_hstd_clr_pipe_table(ptr->ip, addr);

    ipno_devaddr = addr;
    if (USB_IP1 == ptr->ip)
    {
        ipno_devaddr |= USBA_ADDRESS_OFFSET;
    }

    if (g_drive_search_lock == ipno_devaddr)
    {
        g_drive_search_lock = USB_FALSE;
    }

    que_cnt = g_drive_search_que_cnt;

    /* WAIT_LOOP */
    for (i = 0; i < que_cnt; i++)
    {
        if (g_drive_search_que[i] == ipno_devaddr)
        {
            g_drive_search_que[i] = USB_FALSE;

            /* WAIT_LOOP */
            for (j = i; j < que_cnt; j++)
            {
                g_drive_search_que[j] = g_drive_search_que[j + 1];
            }

            g_drive_search_que_cnt--;
        }
    }

    side = usb_hmsc_ref_drvno(ipno_devaddr);
    if (USB_ERROR != side)
    {
        usb_hmsc_strg_drive_close(ptr, side); /* Callback when device is detached. */
    }

    ctrl.module_number  = ptr->ip;            /* Module number setting */
    ctrl.device_address = (uint8_t) addr;
    if (USB_NULL != p_cfg)
    {
        ctrl.p_context = (void *) p_cfg->p_context;
    }

    usb_set_event(USB_STATUS_DETACH, &ctrl); /* Set Event()  */
 #else  /* BSP_CFG_RTOS == 0 */
    usb_instance_ctrl_t ctrl;
    uint16_t            side;
    uint16_t            ipno_devaddr;
    usb_cfg_t         * p_cfg = USB_NULL;
    (void) data2;

    if (ptr->ip)
    {
  #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
  #endif                               /* #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME) */
    }
    else
    {
  #if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
  #endif                               /* #if defined(VECTOR_NUMBER_USBFS_INT) */
    }

    ipno_devaddr = addr;
    if (USB_IP1 == ptr->ip)
    {
        ipno_devaddr |= USBA_ADDRESS_OFFSET;
    }

    side = usb_hmsc_ref_drvno(ipno_devaddr);
    if (USB_ERROR != side)
    {
        usb_hmsc_strg_drive_close(ptr, side); /* Callback when device is detached. */
    }

    ctrl.module_number  = ptr->ip;            /* Module number setting */
    ctrl.device_address = (uint8_t) addr;
    if (USB_NULL != p_cfg)
    {
        ctrl.p_context     = (void *) p_cfg->p_context;
        ctrl.p_transfer_rx = p_cfg->p_transfer_rx;
        ctrl.p_transfer_rx = p_cfg->p_transfer_tx;
    }
    usb_set_event(USB_STATUS_DETACH, &ctrl); /* Set Event()  */
 #endif /* BSP_CFG_RTOS == 0 */
}

/******************************************************************************
 * End of function usb_hmsc_detach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_drive_complete
 * Description     : Next Process Selector
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     addr    : Device Address
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_hmsc_drive_complete (usb_utr_t * ptr, uint16_t addr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    usb_cfg_t         * p_cfg = USB_NULL;
    (void) data2;

    if (ptr->ip)
    {
 #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
 #endif                                /* #if defined(VECTOR_NUMBER_USBHS_USB_INT_RESUME) */
    }
    else
    {
 #if defined(VECTOR_NUMBER_USBFS_INT)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBFS_INT);
 #endif                                /* #if defined(VECTOR_NUMBER_USBFS_INT) */
    }

 #if (BSP_CFG_RTOS == 0)
    uint16_t que_cnt;
    uint16_t i;

    que_cnt = g_drive_search_que_cnt;
    if (g_drive_search_que_cnt)
    {
        g_drive_search_que[0] = USB_NULL;

        /* WAIT_LOOP */
        for (i = 0; i < que_cnt; i++)
        {
            g_drive_search_que[i] = g_drive_search_que[i + 1];
        }

        g_drive_search_que_cnt--;
    }
    g_drive_search_lock = USB_FALSE;
 #endif                                /* BSP_CFG_RTOS == 0 */

    ctrl.module_number  = ptr->ip;     /* Module number setting */
    ctrl.device_address = (uint8_t) addr;
    if (USB_NULL != p_cfg)
    {
        ctrl.p_context = (void *) p_cfg->p_context;
    }

    usb_set_event(USB_STATUS_CONFIGURED, &ctrl); /* Set Event()  */
} /* End of function usb_hmsc_drive_complete() */

/******************************************************************************
 * Function Name   : usb_hmsc_classinit
 * Description     : Host msc driver init
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t data1    : Not used.
 *               : uint16_t data2    : Not used.
 * Return value    : none
 ******************************************************************************/
static void usb_hmsc_classinit (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    uint16_t side;
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

 #if (BSP_CFG_RTOS_USED)
    usb_hmsc_csw_err_stall[ptr->ip] = USB_OFF;
 #endif                                /* BSP_CFG_RTOS_USED */

    for (side = 0; side < USB_MAXSTRAGE; side++)
    {
        usb_hmsc_strg_drive_close(ptr, side);
    }
}

/******************************************************************************
 * End of function usb_hmsc_classinit
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_registration
 * Description     : registration of Host msc driver.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_registration (usb_utr_t * ptr)
{
    usb_hcdreg_t driver;
 #if USB_CFG_HUB == USB_CFG_ENABLE
    uint8_t i;
 #endif                                                /* USB_CFG_HUB == USB_CFG_ENABLE */

    /* Driver registration */
    driver.ifclass = (uint16_t) USB_IFCLS_MAS;         /* Use Interface class for MSC. */
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    driver.p_tpl = (uint16_t *) USB_CFG_TPL_TABLE;
 #else /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.p_tpl = (uint16_t *) &g_usb_hmsc_devicetpl; /* Target peripheral list. */
 #endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.classinit  = &usb_hmsc_classinit;           /* Driver init. */
    driver.classcheck = &usb_hmsc_class_check;         /* Driver check. */
    driver.devconfig  = &usb_hmsc_configured;          /* Callback when device is configured. */
    driver.devdetach  = &usb_hmsc_detach;              /* Callback when device is detached. */
    driver.devsuspend = &usb_hstd_dummy_function;      /* Callback when device is suspended. */
    driver.devresume  = &usb_hstd_dummy_function;      /* Callback when device is resumed. */

 #if USB_CFG_HUB == USB_CFG_ENABLE

    /* WAIT_LOOP */
    for (i = 0; i < USB_MAXSTRAGE; i++)                    /* Loop support HID device count */
    {
        usb_hstd_driver_registration(ptr, &driver);        /* Host MSC class driver registration. */
    }

  #if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HUB_TSK, USB_PRI_3);         /* Hub Task Priority set */
  #endif /* BSP_CFG_RTOS == 0 */

    usb_hhub_registration(ptr, (usb_hcdreg_t *) USB_NULL); /* Hub registration. */
 #else  /* USB_CFG_HUB == USB_CFG_ENABLE */
    usb_hstd_driver_registration(ptr, &driver);            /* Host MSC class driver registration. */
 #endif /* USB_CFG_HUB == USB_CFG_ENABLE */
}

/******************************************************************************
 * End of function usb_hmsc_registration
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_message_retry
 * Description     : Message transfer retry for Que Over
 * Arguments       : uint16_t     id      : Message ID
 *               : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 * usb_utr_t *mess
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_message_retry (uint16_t id, usb_utr_t * mess)
{
  #if (USB_UT_MODE == 0)
    usb_er_t    err;
    usb_utr_t * pblf;

    err = USB_ERROR;

    /* Resend message */
    if (USB_HSTRG_MBX == id)
    {
        err = USB_PGET_BLK(USB_HSTRG_MPL, &pblf);
    }

    if (USB_OK == err)
    {
        pblf->msginfo  = mess->msginfo;
        pblf->keyword  = mess->keyword;
        pblf->result   = mess->result;
        pblf->complete = mess->complete;
        pblf->ip       = mess->ip;
        pblf->ipp      = mess->ipp;

        /* Send message */
        err = USB_SND_MSG(id, (usb_msg_t *) pblf);
        if (USB_OK != err)
        {
            USB_PRINTF1("### snd_msg error (%ld)\n", err);
            err = USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) pblf);
            if (USB_OK != err)
            {
                USB_PRINTF1("### rel_blk error (%ld)\n", err);
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

  #else                                /* (USB_UT_MODE == 0) */
    FSP_PARAMETER_NOT_USED(id);
    FSP_PARAMETER_NOT_USED(*mess);
  #endif /* (USB_UT_MODE == 0) */
}

/******************************************************************************
 * End of function usb_hmsc_message_retry
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_drive_to_addr
 * Description     : Retrieves device address
 * Arguments       : uint16_t     side    : Drive number
 *               : usb_utr_t    *devadr : Pointer to usb_utr_t structure
 * Return value    : uint16_t             : Device address
 ******************************************************************************/
void usb_hmsc_drive_to_addr (uint16_t side, usb_utr_t * devadr)
{
    devadr->keyword = g_usb_hmsc_drvno_tbl[side].devadr; /* Device Address */
    devadr->ip      = g_usb_hmsc_drvno_tbl[side].ip;     /* USB IP No.     */
    devadr->ipp     = usb_hstd_get_usb_ip_adr(devadr->ip);
}

/******************************************************************************
 * End of function usb_hmsc_smp_drive2_addr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_strg_cmd_complete
 * Description     : Serial state receive complete call-back.
 * Argument        : usb_utr_t    *mess   : Pointer to usb_utr_t structure
 *               : uint16_t     devadr  : Device address
 *               : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_hmsc_strg_cmd_complete (usb_utr_t * mess, uint16_t devadr, uint16_t data2)
{
    FSP_PARAMETER_NOT_USED(data2);
 #if (BSP_CFG_RTOS == 0)
    usb_instance_ctrl_t ctrl;

    FSP_PARAMETER_NOT_USED(devadr);
    ctrl.module_number  = mess->ip;                /* Module number setting */
    ctrl.pipe           = (uint8_t) mess->keyword; /* Pipe number setting */
    ctrl.device_address = (uint8_t) (usb_hstd_get_devsel(mess, ctrl.pipe) >> 12);
    ctrl.data_size      = 0;

    switch (mess->result)
    {
        case USB_HMSC_OK:
        {
            ctrl.data_size = mess->tranlen;
            ctrl.status    = USB_CSW_RESULT_SUCCESS;
            break;
        }

        case USB_HMSC_CSW_ERR:
        {
            ctrl.status = USB_CSW_RESULT_FAIL;
            break;
        }

        case USB_HMSC_CSW_PHASE_ERR:
        {
            ctrl.status = USB_CSW_RESULT_PHASE;
            break;
        }

        default:
        {
            ctrl.status = USB_CSW_RESULT_FAIL;
            break;
        }
    }

    usb_set_event(USB_STATUS_MSC_CMD_COMPLETE, &ctrl); /* Set Event(USB receive complete)  */
 #else
    (void) *mess;
    (void) devadr;
 #endif /* BSP_CFG_RTOS == 0 */
}                                      /* End of function usb_hmsc_strg_cmd_complete() */

 #if (BSP_CFG_RTOS == 2)

/******************************************************************************
 * Function Name   : usb_hmsc_get_string_info
 * Description     : Get string descriptors.
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t addr
 *                 uint16_t string
 * Return value    : none
 ******************************************************************************/
uint16_t usb_hmsc_get_string_info (usb_utr_t * mess, uint16_t addr, uint16_t string)
{
    uint16_t retval;

    /* Send GetDescriptor(String) */
    retval = usb_hmsc_get_string_desc(mess, addr, (uint16_t) 0, usb_hmsc_req_trans_result);
    if (USB_OK != retval)
    {
        return USB_ERROR;
    }

    /* Send GetDescriptor(String) */
    retval = usb_hmsc_get_string_desc(mess, addr, string, usb_hmsc_req_trans_result);
    if (USB_OK != retval)
    {
        return USB_ERROR;
    }

    return USB_OK;
}                                      /* End of function usb_hmsc_get_string_info() */

/******************************************************************************
 * Function Name   : usb_hmsc_req_trans_result
 * Description     : Send a message to notify the result of the hmsc class request (PIPE0).
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t data1
 *                 uint16_t data2
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_req_trans_result (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_er_t err;
    (void) data1;
    (void) data2;

  #if BSP_CFG_RTOS == 2
    gs_usb_hmsc_req_tran_result_msg = *mess;

    /* Send a message to HMSC mailbox */
    err = USB_SND_MSG(USB_HMSC_REQ_MBX, (usb_msg_t *) &gs_usb_hmsc_req_tran_result_msg);
  #else                                /* BSP_CFG_RTOS == 2 */
    err = USB_SND_MSG(USB_HMSC_REQ_MBX, (usb_msg_t *) mess);
  #endif /* BSP_CFG_RTOS == 2 */
    if (USB_OK != err)
    {
        USB_PRINTF1("### HMSC snd_msg error (%ld)\n", err);
    }
}                                      /* End of function usb_hmsc_req_trans_result() */

/******************************************************************************
 * Function Name   : usb_hmsc_req_trans_wait_tmo
 * Description     : Receive the result of the hmsc class request with a timeout (PIPE0).
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t tmo     : Time-out value.
 * Return value    : USB_OK/USB_ERROR
 ******************************************************************************/
uint16_t usb_hmsc_req_trans_wait_tmo (uint16_t tmo)
{
    usb_utr_t * mess;
    usb_er_t    err;

    /* Receive message from HMSC_REQ mailbox with time-out */
    err = USB_TRCV_MSG(USB_HMSC_REQ_MBX, (usb_msg_t **) &mess, (usb_tm_t) tmo);
    if (USB_OK != err)
    {
        USB_PRINTF1("### HMSC trcv_msg error (%ld)\n", err);

        return USB_ERROR;
    }

    return mess->status;
}                                      /* End of function usb_hmsc_req_trans_wait_tmo() */

/******************************************************************************
 * Function Name   : usb_hmsc_trans_result
 * Description     : Send a message to notify the result of the hmsc class request.
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t data1
 *                 uint16_t data2
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_trans_result (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_er_t err;
    (void) data1;
    (void) data2;

  #if BSP_CFG_RTOS == 2
    gs_usb_hmsc_tran_result_msg = *mess;

    /* Send a message to HMSC mailbox */
    err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t *) &gs_usb_hmsc_tran_result_msg);
  #else                                /* BSP_CFG_RTOS == 2 */
    err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t *) mess);
  #endif /* BSP_CFG_RTOS == 2 */
    if (USB_OK != err)
    {
        USB_PRINTF1("### HMSC snd_msg error (%ld)\n", err);
    }
}                                      /* End of function usb_hmsc_trans_result() */

/******************************************************************************
 * Function Name   : usb_hmsc_trans_wait_tmo
 * Description     : Receive the result of the hmsc class request with a timeout.
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t tmo     : Time-out value.
 * Return value    : USB_OK/USB_ERROR
 ******************************************************************************/
uint16_t usb_hmsc_trans_wait_tmo (uint16_t tmo)
{
    usb_utr_t * mess;
    usb_er_t    err;

    /* Receive message from HMSC mailbox with time-out */
    err = USB_TRCV_MSG(USB_HMSC_MBX, (usb_msg_t **) &mess, (usb_tm_t) tmo);
    if (USB_OK != err)
    {
        USB_PRINTF1("### HMSC trcv_msg error (%ld)\n", err);

        return USB_ERROR;
    }

    return mess->status;
}                                      /* End of function usb_hmsc_trans_wait_tmo() */

 #endif /* (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * Function Name   : usb_hmsc_driver_start
 * Description     : USB Host Initialize process
 * Argument        : none
 * Return          : none
 ******************************************************************************/
void usb_hmsc_driver_start (uint16_t ip_no)
{
    uint16_t        i;
    static uint16_t init_flag = 0;

    /* WAIT_LOOP */
    for (i = 0; i < USB_MAXSTRAGE; i++)
    {
        if (0 == init_flag)
        {
            g_usb_hmsc_drvno_tbl[i].use_flag = USB_NOUSE;
        }
        else
        {
            if (USB_TRUE == g_usb_hmsc_drvno_tbl[i].use_flag)
            {
                if (ip_no == g_usb_hmsc_drvno_tbl[i].ip)
                {
                    g_usb_hmsc_drvno_tbl[i].use_flag = USB_NOUSE;
                }
            }
        }

        g_usb_hmsc_in_pipe[ip_no][i]  = USB_NOPORT; /* Pipenumber */
        g_usb_hmsc_out_pipe[ip_no][i] = USB_NOPORT; /* Pipenumber */

        g_usb_hmsc_csw_tag_no[ip_no][i] = (uint16_t) 1;

        g_usb_hmsc_cbw[ip_no][i].dcbw_signature              = USB_MSC_CBW_SIGNATURE;
        g_usb_hmsc_cbw[ip_no][i].dcbw_tag                    = g_usb_hmsc_csw_tag_no[ip_no][i];
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_lo                 = 0;
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_ml                 = 0;
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_mh                 = 0;
        g_usb_hmsc_cbw[ip_no][i].dcbw_dtl_hi                 = 0;
        g_usb_hmsc_cbw[ip_no][i].bm_cbw_flags.cbw_dir        = 0;
        g_usb_hmsc_cbw[ip_no][i].bm_cbw_flags.reserved7      = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbw_lun.bcbw_lun           = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbw_lun.reserved4          = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbwcb_length.bcbwcb_length = 0;
        g_usb_hmsc_cbw[ip_no][i].bcbwcb_length.reserved3     = 0;

        g_usb_hmsc_cbw[ip_no][i].cbwcb[0]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[1]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[2]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[3]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[4]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[5]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[6]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[7]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[8]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[9]  = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[10] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[11] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[12] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[13] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[14] = 0;
        g_usb_hmsc_cbw[ip_no][i].cbwcb[15] = 0;
    }

 #if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HMSC_TSK, USB_PRI_3);
    usb_cstd_set_task_pri(USB_HSTRG_TSK, USB_PRI_3);
 #endif                                /* (BSP_CFG_RTOS == 0) */
}

/******************************************************************************
 * End of function usb_hmsc_driver_start
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_class_check
 * Description     : check connected device
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t **table     : Pointer to the class information table
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_class_check (usb_utr_t * ptr, uint16_t ** table)
{
 #if (BSP_CFG_RTOS == 2)
    uint16_t retval;
    uint16_t iproduct;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_utr_t * pblf;
    usb_er_t    err;
 #endif /* (BSP_CFG_RTOS == 2) */

    g_p_usb_hmsc_device_table[ptr->ip]    = (uint8_t *) (table[0]);
    g_p_usb_hmsc_config_table[ptr->ip]    = (uint8_t *) (table[1]);
    g_p_usb_hmsc_interface_table[ptr->ip] = (uint8_t *) (table[2]);
    g_usb_hmsc_speed[ptr->ip]             = *table[6];
    g_usb_hmsc_devaddr[ptr->ip]           = *table[7];
    *table[3] = USB_OK;

 #if (BSP_CFG_RTOS == 2)

    /* Check Interface Descriptor (device-class) */
    if (USB_IFCLS_MAS != g_p_usb_hmsc_interface_table[ptr->ip][USB_IF_B_INTERFACECLASS])
    {
        USB_PRINTF1("### Interface deviceclass is %x , not support.\n",
                    g_p_usb_hmsc_interface_table[ptr->ip][USB_IF_B_INTERFACECLASS]);
        *table[3] = USB_ERROR;

        return;
    }

    /* Check Interface Descriptor (subclass) */
    g_usb_hmsc_tmp_sub_class[ptr->ip] = g_p_usb_hmsc_interface_table[ptr->ip][USB_IF_B_INTERFACESUBCLASS];
    if (USB_ATAPI == g_usb_hmsc_tmp_sub_class[ptr->ip])
    {
        USB_PRINTF0("    Interface subclass  : SFF-8070i\n");
    }
    else if (USB_SCSI == g_usb_hmsc_tmp_sub_class[ptr->ip])
    {
        USB_PRINTF0("Interface subclass  : SCSI transparent command set\n");
    }
    else if (USB_ATAPI_MMC5 == g_usb_hmsc_tmp_sub_class[ptr->ip])
    {
        USB_PRINTF0("   Interface subclass   : ATAPI command set\n");
    }
    else
    {
        USB_PRINTF1("### Interface subclass is %x , not support.\n", g_usb_hmsc_tmp_sub_class[ptr->ip]);
        *table[3] = USB_ERROR;

        return;
    }

    /* Check Interface Descriptor (protocol) */
    if (USB_BOTP == g_p_usb_hmsc_interface_table[ptr->ip][USB_IF_B_INTERFACEPROTOCOL])
    {
        USB_PRINTF0("   Interface protocol   : BOT \n");
    }
    else
    {
        USB_PRINTF1("### Interface protocol is %x , not support.\n",
                    g_p_usb_hmsc_interface_table[ptr->ip][USB_IF_B_INTERFACEPROTOCOL]);
        *table[3] = USB_ERROR;

        return;
    }

    /* Check Endpoint number */
    if (g_p_usb_hmsc_interface_table[ptr->ip][USB_IF_B_NUMENDPOINTS] < 2)
    {
        USB_PRINTF1("### Endpoint number is %x , less than 2.\n",
                    g_p_usb_hmsc_interface_table[ptr->ip][USB_IF_B_NUMENDPOINTS]);
        *table[3] = USB_ERROR;

        return;
    }

    /* Get String Descriptors */
    iproduct = g_p_usb_hmsc_device_table[ptr->ip][USB_DEV_I_PRODUCT];
    retval   = usb_hmsc_get_string_info(ptr, g_usb_hmsc_devaddr[ptr->ip], iproduct);
    if (USB_OK != retval)
    {
        USB_PRINTF0("   GetDescriptor(String) failed!     \n");
        *table[3] = USB_ERROR;

        return;
    }

 #else                                 /* (BSP_CFG_RTOS == 2) */
    /* Get mem pool blk */
    if (USB_PGET_BLK(USB_HMSC_MPL, &pblf) == USB_OK)
    {
        pblf->msginfo                = USB_MSG_CLS_INIT;
        g_usb_hmsc_init_seq[ptr->ip] = USB_SEQ_0;

        pblf->ip  = ptr->ip;
        pblf->ipp = ptr->ipp;

        /* Send message */
        err = USB_SND_MSG(USB_HMSC_MBX, (usb_msg_t *) pblf);
        if (USB_OK != err)
        {
            USB_REL_BLK(USB_HMSC_MPL, (usb_mh_t) pblf);
            USB_PRINTF0("### ClassCheck function snd_msg error\n");
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
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_class_check
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_read10
 * Description     : Read10
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t side        : Side
 *               : uint8_t  *buff       : Buffer address
 *               : uint32_t secno       : Sector number
 *               : uint16_t seccnt      : Sector count
 *               : uint32_t trans_byte  : Trans byte
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_read10 (usb_utr_t     * ptr,
                          uint16_t        side,
                          uint8_t * const buff,
                          uint32_t        secno,
                          uint16_t        seccnt,
                          uint32_t        trans_byte)
{
    uint16_t hmsc_retval;

    /* set CBW parameter */
    usb_hmsc_set_rw_cbw(ptr, (uint16_t) USB_ATAPI_READ10, secno, seccnt, trans_byte, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, trans_byte);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_read10
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_write10
 * Description     : Write10
 * Arguments       : usb_utr_t *ptr      : Pointer to usb_utr_t structure.
 *               : uint16_t side       : Drive number
 *               : uint8_t *buff       : Buffer address
 *               : uint32_t secno      : Sector number
 *               : uint16_t seccnt     : Sector count
 *               : uint32_t trans_byte : Trans byte
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_write10 (usb_utr_t           * ptr,
                           uint16_t              side,
                           uint8_t const * const buff,
                           uint32_t              secno,
                           uint16_t              seccnt,
                           uint32_t              trans_byte)
{
    uint16_t hmsc_retval;

    /* set CBW parameter */
    usb_hmsc_set_rw_cbw(ptr, (uint16_t) USB_ATAPI_WRITE10, secno, seccnt, trans_byte, side);

    /* Data OUT */
    hmsc_retval = usb_hmsc_data_out(ptr, side, buff, trans_byte);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_write10
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_test_unit
 * Description     : TestUnit
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_test_unit (usb_utr_t * ptr, uint16_t side)
{
    uint8_t  cbwcb[12];
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_TEST_UNIT_READY;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) 0, side);

    /* No Data */
    hmsc_retval = usb_hmsc_no_data(ptr, side);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_test_unit
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_request_sense
 * Description     : RequestSense
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 *               : uint8_t      *buff   : Pointer to the buffer area
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_request_sense (usb_utr_t * ptr, uint16_t side, uint8_t * buff)
{
    uint8_t  cbwcb[12];
    uint8_t  length = 18;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_REQUEST_SENSE;

    /* Allocation length */
    cbwcb[4] = length;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_request_sense
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_inquiry
 * Description     : Inquiry
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 *               : uint8_t      *buff   : Pointer to the buffer area
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_inquiry (usb_utr_t * ptr, uint16_t side, uint8_t * buff)
{
    uint8_t  cbwcb[12];
    uint8_t  length = USB_VALUE_36;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_INQUIRY;

    /* Allocation length */
    cbwcb[4] = length;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_inquiry
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_read_capacity
 * Description     : ReadCapacity
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 *               : uint8_t      *buff   : Pointer to the buffer area
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_read_capacity (usb_utr_t * ptr, uint16_t side, uint8_t * buff)
{
    uint8_t  cbwcb[12];
    uint8_t  length = 8;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_READ_CAPACITY;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_read_capacity
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_read_format_capacity
 * Description     : ReadFormatCapacity
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 *               : uint8_t      *buff   : Pointer to the buffer area
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_read_format_capacity (usb_utr_t * ptr, uint16_t side, uint8_t * buff)
{
    uint8_t  cbwcb[12];
    uint8_t  length = USB_VALUE_20H;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_READ_FORMAT_CAPACITY;

    /* Allocation length */
    cbwcb[8] = length;

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_read_format_capacity
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_get_max_unit
 * Description     : Get Max LUN request
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     addr    : Device address
 *               : uint8_t      *buff   : Pointer to the buffer area
 *               : usb_cb_t     complete: CallBack Function
 * Return value    : usb_er_t                  : Error Code
 ******************************************************************************/
usb_er_t usb_hmsc_get_max_unit (usb_utr_t * ptr, uint16_t addr, uint8_t * buff, usb_cb_t complete)
{
    usb_er_t                err;
    static usb_ctrl_trans_t get_max_lun_table;
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;
 #endif                                /* (BSP_CFG_RTOS == 2) */

    get_max_lun_table.setup.request_type   = USB_VALUE_FEA1H;
    get_max_lun_table.setup.request_value  = 0x0000;
    get_max_lun_table.setup.request_index  = 0x0000;
    get_max_lun_table.setup.request_length = 0x0001;
    get_max_lun_table.address              = addr;

    /* Recieve MaxLUN */
    g_usb_hmsc_class_control[ptr->ip].keyword   = USB_PIPE0;
    g_usb_hmsc_class_control[ptr->ip].p_tranadr = buff;
    g_usb_hmsc_class_control[ptr->ip].tranlen   = get_max_lun_table.setup.request_length;
    g_usb_hmsc_class_control[ptr->ip].p_setup   = (uint16_t *) &get_max_lun_table;
    g_usb_hmsc_class_control[ptr->ip].complete  = complete;
    g_usb_hmsc_class_control[ptr->ip].segment   = USB_TRAN_END;
    g_usb_hmsc_class_control[ptr->ip].ip        = ptr->ip;
    g_usb_hmsc_class_control[ptr->ip].ipp       = ptr->ipp;

 #if (BSP_CFG_RTOS == 2)

    /* WAIT_LOOP */
    while (1)
    {
        err = usb_hstd_transfer_start_req(&g_usb_hmsc_class_control[ptr->ip]);
        if (USB_QOVR != err)
        {
            break;                     /* Control Transfer not overlaps */
        }

        /* Control Transfer overlaps. Should retry */
        usb_cpu_delay_xms((uint16_t) 1);
    }

    hmsc_retval = usb_hmsc_trans_wait_tmo((uint16_t) USB_VALUE_3000);
    if (USB_DATA_STALL == hmsc_retval)
    {
        USB_PRINTF0("### GetMaxUnit not support !\n");
        err = USB_ERROR;
    }
    else if (USB_DATA_TMO == hmsc_retval)
    {
        USB_PRINTF0("### GetMaxUnit not support(time out) !\n");
        usb_hstd_transfer_end(ptr, USB_PIPE0, hmsc_retval);
        err = USB_ERROR;
    }
    else if (USB_CTRL_END != hmsc_retval)
    {
        USB_PRINTF0("### GetMaxUnit error\n");
        err = USB_ERROR;
    }
    else
    {
        err = USB_OK;
    }

    return err;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    err = usb_hstd_transfer_start(&g_usb_hmsc_class_control[ptr->ip]);

    return err;
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_get_max_unit
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_mass_storage_reset
 * Description     : Mass Strage Reset request
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     addr    : Device address
 *               : usb_cb_t     complete: CallBack Function
 * Return value    : usb_er_t                 : Error Code
 ******************************************************************************/
usb_er_t usb_hmsc_mass_storage_reset (usb_utr_t * ptr, uint16_t addr, usb_cb_t complete)
{
    usb_er_t err;
 #if (BSP_CFG_RTOS == 2)
    uint16_t hmsc_retval;
 #endif                                /* (BSP_CFG_RTOS == 2) */

    static usb_ctrl_trans_t mass_storage_reset_table;

    mass_storage_reset_table.setup.request_type   = USB_VALUE_FE21H;
    mass_storage_reset_table.setup.request_value  = 0x0000;
    mass_storage_reset_table.setup.request_index  = 0x0000;
    mass_storage_reset_table.setup.request_length = 0x0000;
    mass_storage_reset_table.address              = addr;

    /* Set MassStorageReset */
    g_usb_hmsc_class_control[ptr->ip].keyword   = USB_PIPE0;
    g_usb_hmsc_class_control[ptr->ip].p_tranadr = USB_NULL;
    g_usb_hmsc_class_control[ptr->ip].tranlen   = mass_storage_reset_table.setup.request_length;
    g_usb_hmsc_class_control[ptr->ip].p_setup   = (uint16_t *) &mass_storage_reset_table;
    g_usb_hmsc_class_control[ptr->ip].complete  = complete;
    g_usb_hmsc_class_control[ptr->ip].segment   = USB_TRAN_END;
    g_usb_hmsc_class_control[ptr->ip].ip        = ptr->ip;
    g_usb_hmsc_class_control[ptr->ip].ipp       = ptr->ipp;

 #if (BSP_CFG_RTOS == 2)
    while (1)
    {
        err = usb_hstd_transfer_start(&g_usb_hmsc_class_control[ptr->ip]);
        if (USB_QOVR != err)
        {
            break;                     /* Control Transfer not overlaps */
        }

        /* Control Transfer overlaps. Should retry */
        usb_cpu_delay_xms((uint16_t) 1);
    }

    hmsc_retval = usb_hmsc_trans_wait_tmo((uint16_t) USB_VALUE_3000);
    if (USB_DATA_STALL == hmsc_retval)
    {
        USB_PRINTF0("*** MassStorageReset not support !\n");
        err = USB_ERROR;
    }
    else if (USB_DATA_TMO == hmsc_retval)
    {
        USB_PRINTF0("*** MassStorageReset not support(time out) !\n");
        usb_hstd_transfer_end(ptr, USB_PIPE0, hmsc_retval);
        err = USB_ERROR;
    }
    else if (USB_CTRL_END != hmsc_retval)
    {
        USB_PRINTF1("### MassStorageReset control transfer error(%d) !\n", hmsc_retval);
        err = USB_ERROR;
    }
    else
    {
        err = USB_OK;
    }

    return err;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    err = usb_hstd_transfer_start(&g_usb_hmsc_class_control[ptr->ip]);

    return err;
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_mass_storage_reset
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_prevent_allow
 * Description     : PreventAllow
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 *               : uint8_t      *buff   : Pointer to the buffer area
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_prevent_allow (usb_utr_t * ptr, uint16_t side, uint8_t * buff)
{
    uint8_t  cbwcb[12];
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_PREVENT_ALLOW;

    /* Reserved */
    cbwcb[4] = buff[0];

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) 0, side);

    /* No Data */
    hmsc_retval = usb_hmsc_no_data(ptr, side);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_prevent_allow
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_mode_sense10
 * Description     : ModeSense10
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 *               : uint8_t      *buff   : [OUT]Pointer to the buffer area/[IN]buff[0] Page Code
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_mode_sense10 (usb_utr_t * ptr, uint16_t side, uint8_t * buff)
{
    uint8_t  cbwcb[12];
    uint8_t  length;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_MODE_SENSE10;

    /* Set LUN / DBD=1 */
    /* b7-b5:LUN (=0),b4-b0:Reserved */
    cbwcb[1] = 0x00;

    /* b7-b6:PageControl = Current values(=0),b5-b0:PageCode */
    cbwcb[2] = buff[0];

    switch (buff[0])                      /* [IN]buff[0] Page Code */
    {
        case 0x01:                        /* Read-Write Error Recovery Page */
        case 0x08:                        /* Caching Page */
        case 0x1B:                        /* Removable Block Access Capacities Page */
        {
            length = 20;                  /* 8 + 12 */
            break;
        }

        case 0x1C:                        /* Timer & Protect Page */
        {
            length = 16;                  /* 8 + 8 */
            break;
        }

        case USB_VALUE_ALL_PAGES:         /* Return all pages(valid only for MODE SENSE command) */
        {
            length = USB_VALUE_ALL_PAGES; /* 8 + 12 + 12 +12 */
            break;
        }

        default:
        {
            return USB_PAR;
            break;
        }
    }

    /* Allocation length */
    cbwcb[7] = 0x00;                   /* MSB */
    cbwcb[8] = length;                 /* LSB */

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) length, side);

    /* Data IN */
    hmsc_retval = usb_hmsc_data_in(ptr, side, buff, (uint32_t) length);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_mode_sense10
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_mode_select10
 * Description     : ModeSelect6
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 *               : uint8_t      *buff   : Pointer to the buffer area
 *               :              buff[0]-[7]:Mode Parameter Header
 *               :              buff[8]-[n]:Page(s)
 *               :               buff[8] b7:Parameter Savable(PS)
 *               :               buff[8] b6:Reserved
 *               :               buff[8] b5-b0:Page Code
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_mode_select10 (usb_utr_t * ptr, uint16_t side, uint8_t * buff)
{
    uint8_t  cbwcb[12];
    uint8_t  length = 18;
    uint16_t hmsc_retval;

    /* Data clear */
    usb_hmsc_clr_data((uint16_t) 12, cbwcb);

    /* Data set */
    /* Command */
    cbwcb[0] = USB_ATAPI_MODE_SELECT10;

    /* Logical Unit Number = 0/ Save Pages(SP) = 0 */
    cbwcb[1] = 0x10;

    switch ((buff[8] & USB_VALUE_3FH))
    {
        case 0x01:                     /* Read-Write Error Recovery Page */
        case 0x08:                     /* Caching Page */
        case 0x1B:                     /* Removable Block Access Capacities Page */
        {
            length = 20;               /* 8 + 12 */
            break;
        }

        case 0x1C:                     /* Timer & Protect Page */
        {
            length = 16;               /* 8 + 8 */
            break;
        }

        default:
        {
            return USB_PAR;
            break;
        }
    }

    /* Parameter list length */
    cbwcb[7] = 0x00;                   /* MSB */
    cbwcb[8] = length;                 /* LSB */

    /* Set CBW parameter */
    usb_hmsc_set_els_cbw(ptr, (uint8_t *) &cbwcb, (uint32_t) length, side);

    /* Data OUT */
    hmsc_retval = usb_hmsc_data_out(ptr, side, buff, (uint32_t) length);

    return hmsc_retval;
}

/******************************************************************************
 * End of function usb_hmsc_mode_select10
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_get_dev_sts
 * Description     : Responds to HMSCD operation state
 * Arugments       : uint16_t     side    : Drive number
 * Return value    : uint16_t :
 ******************************************************************************/
uint16_t usb_hmsc_get_dev_sts (uint16_t side)
{
    return g_usb_hmsc_drvno_tbl[side].use_flag;
}

/******************************************************************************
 * End of function usb_hmsc_get_dev_sts
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_alloc_drvno
 * Description     : Alloc Drive no.
 * Arguments       : uint16_t devadr       : Device address
 * Return value    : Drive no.
 ******************************************************************************/
uint16_t usb_hmsc_alloc_drvno (uint16_t devadr)
{
    uint16_t side;
    uint8_t  ipno;

    if (USBA_ADDRESS_OFFSET == (devadr & USB_IP_MASK))
    {
        ipno = USB_IP1;
    }
    else
    {
        ipno = USB_IP0;
    }

    devadr &= USB_ADDRESS_MASK;

    /* WAIT_LOOP */
    for (side = 0; side < USB_MAXSTRAGE; side++)
    {
        if (USB_NOUSE == g_usb_hmsc_drvno_tbl[side].use_flag)
        {
            g_usb_hmsc_drvno_tbl[side].use_flag = USB_TRUE;
            g_usb_hmsc_drvno_tbl[side].devadr   = devadr;
            g_usb_hmsc_drvno_tbl[side].ip       = ipno;

            return side;
        }
    }

    USB_PRINTF0("DRIVE ALLOC ERROR");

    return USB_ERROR;
}

/******************************************************************************
 * End of function usb_hmsc_alloc_drvno
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_free_drvno
 * Description     : Release Drive no.
 * Arugments       : uint16_t     side    : Drive number
 * Return value    : result
 ******************************************************************************/
uint16_t usb_hmsc_free_drvno (uint16_t side)
{
    if (side > USB_MAXSTRAGE)
    {
        return USB_ERROR;
    }

    g_usb_hmsc_drvno_tbl[side].use_flag = USB_NOUSE;
    g_usb_hmsc_drvno_tbl[side].ip       = USB_NOUSE;
    g_usb_hmsc_drvno_tbl[side].devadr   = USB_NOUSE;

    return USB_OK;
}

/******************************************************************************
 * End of function usb_hmsc_free_drvno
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_ref_drvno
 * Description     : Get Drive no.
 * Arguments       : uint16_t devadr       : Device address
 * Return value    : Drive no.
 ******************************************************************************/
uint16_t usb_hmsc_ref_drvno (uint16_t devadr)
{
    uint16_t side;
    uint16_t ipno;

    if (USBA_ADDRESS_OFFSET == (devadr & USB_IP_MASK))
    {
        ipno = USB_IP1;
    }
    else
    {
        ipno = USB_IP0;
    }

    devadr &= USB_ADDRESS_MASK;

    /* WAIT_LOOP */
    for (side = 0; side < USB_MAXSTRAGE; side++)
    {
        if ((devadr == g_usb_hmsc_drvno_tbl[side].devadr) && (ipno == g_usb_hmsc_drvno_tbl[side].ip))
        {
            return side;
        }
    }

    return USB_ERROR;
}

/******************************************************************************
 * End of function usb_hmsc_ref_drvno
 ******************************************************************************/
 #endif                                /* (USB_UT_MODE == 1) */

 #if USB_CFG_HUB != USB_CFG_ENABLE

/******************************************************************************
 * Function Name   : usb_hhub_task
 * Description     : HUB task
 * Arguments       : usb_vp_int_t stacd          : Start Code of Hub Task
 * Return value    : none
 ******************************************************************************/
void usb_hhub_task (void * stacd)
{
    (void) stacd;
}

/******************************************************************************
 * End of function usb_hhub_task
 ******************************************************************************/
 #endif                                /* USB_CFG_HUB != USB_CFG_ENABLE */

#endif                                 /* defined(USB_CFG_HMSC_USE) */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
