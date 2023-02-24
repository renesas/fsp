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
#include "r_usb_hmsc_api.h"
#include "inc/r_usb_hmsc_driver.h"
#if (BSP_CFG_RTOS == 2)
 #include "FreeRTOS.h"
#endif                                 /*BSP_CFG_RTOS == 1 */

#if defined(USB_CFG_HMSC_USE)

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
 #define RETRY_COUNT      (10)
 #define USB_VALUE_512    (512)
 #define USB_VALUE_100    (100)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
uint16_t g_usb_hmsc_strg_process[USB_NUM_USBIP];

/* static uint8_t g_usb_hmsc_data[USB_NUM_USBIP][64];*/     /* Full-Speed MAXPS */
static uint8_t g_usb_hmsc_data[USB_NUM_USBIP][USB_VALUE_512]; /* Hi-Speed MAXPS */
 #if (BSP_CFG_RTOS == 0)

/* Partition */
static uint16_t g_usb_hmsc_read_partition_retry_count[USB_NUM_USBIP];
 #endif                                /* BSP_CFG_RTOS == 0 */

static usb_cb_t usb_shmsc_command_result[USB_NUM_USBIP];

uint16_t g_usb_hmsc_root_devaddr[USB_NUM_USBIP];
uint16_t g_usb_hmsc_drive_search_seq[USB_NUM_USBIP];

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 * Renesas Abstracted Peripheral Driver functions
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_strg_drive_search_act
 * Description     : Storage drive search
 * Arguments       : usb_utr_t *mess   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_strg_drive_search_act (usb_utr_t * mess)
{
    static uint16_t side;
    uint16_t        addr;
    usb_er_t        err;
    uint16_t        ipno_devaddr;

    switch (g_usb_hmsc_drive_search_seq[mess->ip])
    {
        case USB_SEQ_0:                /* Get MAX_LUN */
        {
            USB_PRINTF0("\n*** Drive search !\n");
            g_usb_hmsc_strg_process[mess->ip] = USB_MSG_HMSC_STRG_DRIVE_SEARCH;
            addr         = mess->keyword;
            ipno_devaddr = addr;
            if (USB_IP1 == mess->ip)
            {
                ipno_devaddr |= USBA_ADDRESS_OFFSET;
            }

            side = usb_hmsc_ref_drvno(ipno_devaddr);

            if (USB_ERROR == side)
            {
                g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
                g_usb_hmsc_strg_process[mess->ip]     = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
                usb_hmsc_strg_specified_path(mess);
                usb_hstd_connect_err_event_set(mess->ip);
            }
            else
            {
                err = usb_hmsc_get_max_unit(mess, addr, g_usb_hmsc_data[mess->ip], usb_hmsc_strg_check_result);
                if (USB_QOVR == err)
                {
                    usb_hmsc_message_retry(USB_HSTRG_MBX, mess);
                }
                else
                {
                    g_usb_hmsc_drive_search_seq[mess->ip]++;
                }
            }

            break;
        }

        case USB_SEQ_1:                /* Check result */
        {
            if (USB_CTRL_END != mess->result)
            {
                USB_PRINTF0("### GetMaxLUN error\n");
            }

            USB_PRINTF1(" Unit number is %d\n", g_usb_hmsc_data[mess->ip][0]);
            USB_PRINTF0("\nPlease wait device ready\n");
            usb_cpu_delay_xms(USB_VALUE_100);

            /* Inquiry */
            usb_hmsc_inquiry(mess, side, (uint8_t *) &g_usb_hmsc_data[mess->ip]);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
            break;
        }

        case USB_SEQ_2:                /* Check result */
        {
            if (mess->result != USB_HMSC_OK)
            {
                USB_PRINTF0("### Inquiry error\n");
            }

            /* Read Format Capacity */
            usb_hmsc_read_format_capacity(mess, side, (uint8_t *) &g_usb_hmsc_data[mess->ip]);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
            break;
        }

        case USB_SEQ_3:                /* Read Capacity */
        {
            usb_hmsc_read_capacity(mess, side, (uint8_t *) &g_usb_hmsc_data[mess->ip]);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
            break;
        }

        case USB_SEQ_4:
        {
            if (mess->result != USB_HMSC_OK)
            {
                /* TestUnitReady */
                usb_hmsc_test_unit(mess, side);
                g_usb_hmsc_drive_search_seq[mess->ip]++;
            }
            else
            {
                /* Pass TestUnitReady  */
                g_usb_hmsc_drive_search_seq[mess->ip]           = USB_SEQ_6;
                g_usb_hmsc_read_partition_retry_count[mess->ip] = 0;
                usb_hmsc_strg_specified_path(mess);
            }

            break;
        }

        case USB_SEQ_5:
        {
            if (mess->result != USB_HMSC_OK)
            {
                /* TestUnitReady (Retry) */
                usb_hmsc_test_unit(mess, side);
            }
            else
            {
                /* Read Capacity (Retry) */
                usb_hmsc_read_capacity(mess, side, (uint8_t *) &g_usb_hmsc_data[mess->ip]);
                g_usb_hmsc_read_partition_retry_count[mess->ip] = 0;
                g_usb_hmsc_drive_search_seq[mess->ip]++;
            }

            break;
        }

        case USB_SEQ_6:
        {
            /* Don't delete the following processing!! */
            /* (This is necessary for the specific USB memory.) */
            /* Read10 secno = 0, seccnt = 1 */
            usb_hmsc_read10(mess, side, (uint8_t *) &g_usb_hmsc_data[mess->ip], 0, 1, USB_HMSC_STRG_SECTSIZE);
            g_usb_hmsc_drive_search_seq[mess->ip]++;
            break;
        }

        case USB_SEQ_7:
        {
            if (USB_HMSC_OK == mess->result)
            {
                g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
                g_usb_hmsc_strg_process[mess->ip]     = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
            }
            else
            {
                g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_6;

                /* Drive read error */
                USB_PRINTF0("### drive read error  (times ).\n");
                g_usb_hmsc_read_partition_retry_count[mess->ip]++; /* Update Retry count */
                /* Max Retry count = 10 */
                if ((uint32_t) 10 == g_usb_hmsc_read_partition_retry_count[mess->ip])
                {
                    /* Retry end. */
                    g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
                    g_usb_hmsc_strg_process[mess->ip]     = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
                    usb_hstd_connect_err_event_set(mess->ip);
                }
            }

            usb_hmsc_strg_specified_path(mess);
            break;
        }

        default:
        {
            g_usb_hmsc_drive_search_seq[mess->ip] = USB_SEQ_0;
            g_usb_hmsc_strg_process[mess->ip]     = USB_MSG_HMSC_STRG_DRIVE_SEARCH_END;
            usb_hmsc_strg_specified_path(mess);
            usb_hstd_connect_err_event_set(mess->ip);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hmsc_strg_drive_search_act
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_strg_specified_path
 * Description     : Next Process Selector
 * Arguments       : usb_utr_t *mess   : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_strg_specified_path (usb_utr_t * mess)
{
    usb_utr_t * pblf;
    usb_er_t    err;

    /* Get mem pool blk */
    if (USB_OK == USB_PGET_BLK(USB_HSTRG_MPL, &pblf))
    {
        pblf->msginfo = g_usb_hmsc_strg_process[mess->ip];
        pblf->keyword = mess->keyword;
        pblf->result  = mess->result;

        pblf->ip  = mess->ip;
        pblf->ipp = mess->ipp;

        /* Send message */
        err = USB_SND_MSG(USB_HSTRG_MBX, (usb_msg_t *) pblf);
        if (USB_OK != err)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) pblf);
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
 * End of function usb_hmsc_strg_specified_path
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_strg_check_result
 * Description     : Hub class check result
 * Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_strg_check_result (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);
    mess->result = mess->status;
    usb_hmsc_strg_specified_path(mess);
}

/******************************************************************************
 * End of function usb_hmsc_strg_check_result
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */
 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_strg_drive_task
 * Description     : Storage drive task
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_hmsc_strg_drive_task (void)
{
    usb_utr_t * p_mess;
    usb_er_t    err;

    /* receive message */
    err = USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t **) &p_mess);
    if (USB_OK != err)
    {
        return;
    }

    switch (p_mess->msginfo)
    {
        case USB_MSG_HMSC_STRG_DRIVE_SEARCH:
        {
            /* Start Drive search */
            usb_hmsc_strg_drive_search_act(p_mess);
            break;
        }

        case USB_MSG_HMSC_STRG_DRIVE_SEARCH_END:
        {
            g_usb_hmsc_strg_process[p_mess->ip] = USB_NULL;
            if (USB_NULL != usb_shmsc_command_result[p_mess->ip]) /* Check Callback function */
            {
                (usb_shmsc_command_result[p_mess->ip])(p_mess, g_usb_hmsc_root_devaddr[p_mess->ip], 0);
            }

            break;
        }

        case USB_MSG_HMSC_STRG_USER_COMMAND:
        {
            if (USB_NULL != usb_shmsc_command_result[p_mess->ip]) /* Check Callback function */
            {
                /* usb_hmsc_strg_user_command Result */
                (usb_shmsc_command_result[p_mess->ip])(p_mess, 0, 0);
            }

            break;
        }

        default:
        {
            break;
        }
    }

    err = USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_mess);
    if (USB_OK != err)
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
 * End of function usb_hmsc_strg_drive_task
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 2)

/******************************************************************************
 * Function Name   : hmsc_error_process
 * Description     : Error processing when CSW error is retuned by MSC device.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     side        : Drive number
 *               : uint16_t     err_code    : Error code
 * Return value    : uint16_t                 : Error code
 ******************************************************************************/
uint16_t hmsc_error_process (usb_utr_t * ptr, uint16_t side, uint16_t err_code)
{
    uint16_t       retval;
    static uint8_t g_usb_hmsc_rs_data[USB_VALUE_512]; /* Request Sense Data Buffer */

    retval = err_code;

    if (USB_HMSC_CSW_ERR == err_code)
    {
        retval = usb_hmsc_request_sense(ptr, side, g_usb_hmsc_rs_data);
    }

    return retval;
}

/******************************************************************************
 * End of function hmsc_error_processing
 ******************************************************************************/
 #endif                                /* BSP_CFG_RTOS */

/******************************************************************************
 * Function Name   : usb_hmsc_strg_drive_search
 * Description     : Searches drive SndMsg
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     addr        : Device Address
 *               : usb_cb_t     complete    : Callback function
 * Return value    : uint16_t                 : Status
 ******************************************************************************/
uint16_t usb_hmsc_strg_drive_search (usb_utr_t * ptr, uint16_t addr, usb_cb_t complete)
{
 #if (BSP_CFG_RTOS == 2)
    usb_er_t err;
    uint16_t side;
    uint16_t ipno_devaddr;
    uint16_t hmsc_retval;
    uint16_t count  = 0;
    uint16_t wbreak = 0;

    USB_PRINTF0("\n*** Drive search !\n");

    g_usb_hmsc_root_devaddr[ptr->ip]  = addr;
    usb_shmsc_command_result[ptr->ip] = complete;

    /* Get MAX_LUN */
    ipno_devaddr = addr;
    if (USB_IP1 == ptr->ip)
    {
        ipno_devaddr |= USBA_ADDRESS_OFFSET;
    }

    side = usb_hmsc_ref_drvno(ipno_devaddr);
    if (USB_ERROR == side)
    {
        return USB_ERROR;
    }

    err = usb_hmsc_get_max_unit(ptr, addr, g_usb_hmsc_data[ptr->ip], usb_hmsc_trans_result);
    if (USB_ERROR == err)
    {
        USB_PRINTF0("### GetMaxLUN error\n");

        return USB_ERROR;
    }

    USB_PRINTF1(" Unit number is %d\n", g_usb_hmsc_data[ptr->ip][0]);
    USB_PRINTF0("\nPlease wait device ready\n");

    usb_cpu_delay_xms(USB_VALUE_100);

    /* Inquiry */
    hmsc_retval = usb_hmsc_inquiry(ptr, side, (uint8_t *) &g_usb_hmsc_data[ptr->ip]);
    if (USB_HMSC_OK != hmsc_retval)
    {
        hmsc_retval = hmsc_error_process(ptr, side, hmsc_retval);
        if (USB_HMSC_OK != hmsc_retval)
        {
            return USB_ERROR;
        }
    }

    /* Read Format Capacity */
    hmsc_retval = usb_hmsc_read_format_capacity(ptr, side, (uint8_t *) &g_usb_hmsc_data[ptr->ip]);
    if (USB_HMSC_OK != hmsc_retval)
    {
        hmsc_retval = hmsc_error_process(ptr, side, hmsc_retval);
        if (USB_HMSC_OK != hmsc_retval)
        {
            return USB_ERROR;
        }
    }

    /* Read Capacity */
    hmsc_retval = usb_hmsc_read_capacity(ptr, side, (uint8_t *) &g_usb_hmsc_data[ptr->ip]);
    if (USB_HMSC_OK != hmsc_retval)
    {
        hmsc_retval = hmsc_error_process(ptr, side, hmsc_retval);
        if (USB_HMSC_OK != hmsc_retval)
        {
            return USB_ERROR;
        }

        /* WAIT_LOOP */
        while (1)
        {
            /* TestUnitReady */
            hmsc_retval = usb_hmsc_test_unit(ptr, side);

            if (USB_HMSC_OK == hmsc_retval)
            {
                /* Read Capacity (Retry) */
                hmsc_retval = usb_hmsc_read_capacity(ptr, side, (uint8_t *) &g_usb_hmsc_data[ptr->ip]);
                if (USB_HMSC_OK != hmsc_retval)
                {
                    /* None */
                }

                wbreak = 1;
            }
            else
            {
                hmsc_retval = hmsc_error_process(ptr, side, hmsc_retval);
                if (USB_HMSC_OK != hmsc_retval)
                {
                    return USB_ERROR;
                }
            }

            if (1 == wbreak)
            {
                break;
            }
        }
    }

    /* Don't delete the following processing!! */
    /* (This is necessary for the specific USB memory.) */
    /* Read10 secno = 0, seccnt = 1 */
    /* WAIT_LOOP */
    for (count = 0; ; count++)
    {
        if (RETRY_COUNT != count)
        {
            hmsc_retval =
                usb_hmsc_read10(ptr, side, (uint8_t *) &g_usb_hmsc_data[ptr->ip], 0, 1, USB_HMSC_STRG_SECTSIZE);
            if (USB_HMSC_OK == hmsc_retval)
            {
                break;
            }
        }
        else
        {
            return USB_ERROR;
        }
    }

    /* Storage Drive Search completed. */
    (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_root_devaddr[ptr->ip], 0);

    return USB_OK;
 #else                                 /* (BSP_CFG_RTOS == 2) */
    usb_utr_t * p_blf;
    usb_er_t    err;
    uint16_t    ret_code;

    ret_code = USB_OK;
    g_usb_hmsc_root_devaddr[ptr->ip]     = addr;
    usb_shmsc_command_result[ptr->ip]    = complete;
    g_usb_hmsc_drive_search_seq[ptr->ip] = USB_SEQ_0;

    /* Get mem pool blk */
    if (USB_OK == USB_PGET_BLK(USB_HSTRG_MPL, &p_blf))
    {
        p_blf->msginfo  = USB_MSG_HMSC_STRG_DRIVE_SEARCH;
        p_blf->keyword  = addr;
        p_blf->complete = complete;
        p_blf->ip       = ptr->ip;
        p_blf->ipp      = ptr->ipp;

        /* Send message */
        err = USB_SND_MSG(USB_HSTRG_MBX, (usb_msg_t *) p_blf);
        if (USB_OK != err)
        {
            ret_code = USB_ERROR;
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t) p_blf);
            USB_PRINTF0("### StrgDriveSearch function snd_msg error\n");
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
    return ret_code;
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hmsc_strg_drive_search
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_strg_drive_open
 * Description     : Releases drive
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     addr        : Device Address
 *               : uint16_t     *side       : Pointer to the area to store the drive number
 * Return value    : uint16_t                 : [OK/ERROR]
 ******************************************************************************/
uint16_t usb_hmsc_strg_drive_open (usb_utr_t * ptr, uint16_t addr, uint16_t * side)
{
    uint16_t retval;
    uint16_t ip_addr;

    ip_addr = addr;
    if (USB_IP1 == ptr->ip)
    {
        ip_addr |= USBA_ADDRESS_OFFSET;
    }

    *side = usb_hmsc_alloc_drvno(ip_addr);

    if (USB_ERROR == (*side))
    {
        return USB_ERROR;
    }

    /* Set SubClass */
    g_usb_hmsc_sub_class[ptr->ip][*side] = g_usb_hmsc_tmp_sub_class[ptr->ip];

    /* Pipe Information table set */
    retval = usb_hmsc_pipe_info(ptr,
                                g_p_usb_hmsc_interface_table[ptr->ip],
                                *side,
                                g_usb_hmsc_speed[ptr->ip],
                                (uint16_t) g_p_usb_hmsc_config_table[ptr->ip][2]);
    if (USB_ERROR == retval)
    {
        USB_PRINTF0("### Device information error !\n");

        return USB_ERROR;
    }

 #if (BSP_CFG_RTOS == 0)
    g_drive_search_que[g_drive_search_que_cnt] = (uint8_t) ip_addr;
    g_drive_search_que_cnt++;
 #endif                                /* BSP_CFG_RTOS == 0 */
    return USB_OK;
}

/******************************************************************************
 * End of function usb_hmsc_strg_drive_open
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hmsc_strg_drive_close
 * Description     : Releases drive
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     side    : Drive number
 * Return value    : uint16_t             : [OK/ERROR]
 ******************************************************************************/
uint16_t usb_hmsc_strg_drive_close (usb_utr_t * ptr, uint16_t side)
{
    uint16_t result;

    /* Clear Pipe */
    g_usb_hmsc_out_pipe[ptr->ip][side]    = USB_NOPORT; /* Pipe initial */
    g_usb_hmsc_in_pipe[ptr->ip][side]     = USB_NOPORT; /* Pipe initial */
    g_usb_hmsc_out_pipectr[ptr->ip][side] = 0;          /* Toggle clear */
    g_usb_hmsc_in_pipectr[ptr->ip][side]  = 0;          /* Toggle clear */

    result = usb_hmsc_free_drvno(side);

    return result;
}

/******************************************************************************
 * End of function usb_hmsc_strg_drive_close
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hmsc_strg_user_command
 * Description     : USB Mass Storage Command
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : uint16_t     side        : Drive number
 *               : uint16_t     command     : ATAPI command
 *               : uint8_t      *buff       : Buffer address
 *               : usb_cb_t     complete    : callback info
 * Return value    : uint16_t                 : [DONE/ERROR]
 ******************************************************************************/
uint16_t usb_hmsc_strg_user_command (usb_utr_t * ptr, uint16_t side, uint16_t command, uint8_t * buff,
                                     usb_cb_t complete)
{
    uint16_t result;

    /* Device Status */
    if (USB_TRUE != usb_hmsc_get_dev_sts(side))
    {
        USB_PRINTF1("### device det(StrgUserCommand:side=%d)\n", side);

        return USB_ERROR;
    }

    switch (command)
    {
        case USB_ATAPI_TEST_UNIT_READY:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /* Test unit */
            result = usb_hmsc_test_unit(ptr, side);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        case USB_ATAPI_REQUEST_SENSE:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /*Request sense */
            result = usb_hmsc_request_sense(ptr, side, buff);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        case USB_ATAPI_FORMAT_UNIT:
        {
            return USB_ERROR;
            break;
        }

        case USB_ATAPI_INQUIRY:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /* Inquiry */
            result = usb_hmsc_inquiry(ptr, side, buff);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        case USB_ATAPI_PREVENT_ALLOW:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /* Prevent allow */
            result = usb_hmsc_prevent_allow(ptr, side, buff);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        case USB_ATAPI_READ_FORMAT_CAPACITY:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /* Read format capacity */
            result = usb_hmsc_read_format_capacity(ptr, side, buff);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        case USB_ATAPI_READ_CAPACITY:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /* Read capacity */
            result = usb_hmsc_read_capacity(ptr, side, buff);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        case USB_ATAPI_MODE_SELECT10:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /* Mode select10 */
            result = usb_hmsc_mode_select10(ptr, side, buff);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        case USB_ATAPI_MODE_SENSE10:
        {
            g_usb_hmsc_strg_process[ptr->ip]  = USB_MSG_HMSC_STRG_USER_COMMAND;
            usb_shmsc_command_result[ptr->ip] = complete;

            /* Mode sense10 */
            result = usb_hmsc_mode_sense10(ptr, side, buff);
  #if (BSP_CFG_RTOS == 2)

            /* The result of the user command should be reported before returning this function */
            (usb_shmsc_command_result[ptr->ip])(ptr, g_usb_hmsc_drvno_tbl[side].devadr, 0); /* Result of User commands */
  #endif /* (BSP_CFG_RTOS == 2) */
            break;
        }

        /* USB_ATAPI_FORMAT_UNIT */
        /* USB_ATAPI_MODE_SELECT6 */
        /* USB_ATAPI_MODE_SENSE6 */
        /* USB_ATAPI_START_STOP_UNIT */
        /* USB_ATAPI_READ10 */
        /* USB_ATAPI_WRITE10 */
        /* USB_ATAPI_SEEK */
        /* USB_ATAPI_WRITE_AND_VERIFY */
        /* USB_ATAPI_VERIFY10 */
        default:
        {
            return USB_PAR;
            break;
        }
    }

    ptr->result = result;              /* Set BOT transfer result. (USB_HMSC_OK/USB_HMSC_CSW_ERR/USB_HMSC_CSW_PHASE_ERR...) */

    if (USB_HMSC_OK == result)
    {
        result = USB_OK;
    }
    else if (USB_PAR == result)
    {
        result = USB_PAR;
    }
    else
    {
        result = USB_ERROR;
    }

    return result;
}

/******************************************************************************
 * End of function usb_hmsc_strg_user_command
 ******************************************************************************/
 #endif                                /* (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_hmsc_storage_driver_start
 * Description     : USB Host Initialize process
 * Arguments       : uint16_t ip_no  : USB IP No. (USB_IP0/USB_IP1)
 * Return          : none
 ******************************************************************************/
void usb_hmsc_storage_driver_start (uint16_t ip_no)
{
    g_usb_hmsc_strg_process[ip_no] = 0;
    memset((void *) &g_usb_hmsc_data[ip_no], 0, USB_VALUE_512);
 #if (BSP_CFG_RTOS == 0)
    g_usb_hmsc_read_partition_retry_count[ip_no] = 0;
 #endif                                /* BSP_CFG_RTOS == 0 */

    usb_shmsc_command_result[ip_no]    = 0;
    g_usb_hmsc_root_devaddr[ip_no]     = 0;
    g_usb_hmsc_drive_search_seq[ip_no] = 0;
}

/******************************************************************************
 * End of function usb_hmsc_storage_driver_start
 ******************************************************************************/
#endif                                 /* defined(USB_CFG_HMSC_USE) */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
