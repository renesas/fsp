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

#if defined(USB_CFG_PMSC_USE)
 #include "r_usb_pmsc_api.h"
#endif                                 /* defined(USB_CFG_PMSC_USE) */

#if defined(USB_CFG_PCDC_USE)
 #include "r_usb_pcdc_api.h"
#endif                                 /* defined(USB_CFG_PCDC_USE) */

#if (BSP_CFG_RTOS == 1)
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_api.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_system.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_utility.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_device_stack.h"
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
#define STRING_BUFFER_LEN          (256)
#define VALUE_FFH                  (0xFF)
#define FSP_SETUP_REQUEST          (1)
#define FSP_SETUP_VALUE            (2)
#define FSP_SETUP_LENGTH           (6)
#if defined(USB_CFG_PAUD_USE) || defined(USB_CFG_DFU_USE)
 #define FSP_SETUP_REQUEST_TYPE    (0)
 #define FSP_SETUP_INDEX_L         (4)
 #define FSP_SETUP_INDEX_H         (5)
#endif                                 /* #if defined(USB_CFG_PAUD_USE) || defined(USB_CFG_DFU_USE)*/

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
extern void usb_peri_usbx_set_control_length(usb_setup_t * p_req);

extern uint8_t g_usb_peri_usbx_is_configured[USB_NUM_USBIP];

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
static void usb_pstd_get_status1(usb_utr_t * p_utr);
static void usb_pstd_get_descriptor1(usb_utr_t * p_utr);
static void usb_pstd_get_configuration1(usb_utr_t * p_utr);
static void usb_pstd_get_interface1(usb_utr_t * p_utr);
static void usb_pstd_clr_feature0(void);
static void usb_pstd_clr_feature3(usb_utr_t * p_utr);
static void usb_pstd_set_feature0(void);
static void usb_pstd_set_feature3(usb_utr_t * p_utr);
static void usb_pstd_set_address0(void);
static void usb_pstd_set_address3(usb_utr_t * p_utr);
static void usb_pstd_set_descriptor2(usb_utr_t * p_utr);
static void usb_pstd_set_configuration0(usb_utr_t * p_utr);
static void usb_pstd_set_configuration3(usb_utr_t * p_utr);
static void usb_pstd_set_interface0(usb_utr_t * p_utr);
static void usb_pstd_set_interface3(usb_utr_t * p_utr);
static void usb_pstd_synch_rame1(usb_utr_t * p_utr);

 #if (BSP_CFG_RTOS == 1)
static void usb_peri_class_request_usbx(usb_setup_t * p_req);
static void usb_peri_class_reqeust_usbx_get_data(usb_setup_t * p_req, usb_utr_t * p_utr);

 #endif                                /* #if (BSP_CFG_RTOS == 1) */

 #if USB_CFG_REQUEST == USB_CFG_ENABLE
static void usb_pstd_request_event_set(usb_utr_t * p_utr);

 #endif                                /* USB_CFG_REQUEST == USB_CFG_ENABLE */

 #if (BSP_CFG_RTOS == 1)
static uint8_t g_usbx_string[STRING_BUFFER_LEN];
 #endif /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Renesas Abstracted Peripheral standard request functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_stand_req0
 * Description     : The idle and setup stages of a standard request from host.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_stand_req0 (usb_utr_t * p_utr)
{
    g_usb_pstd_std_request = USB_NO;

    switch ((g_usb_pstd_req_type & USB_BREQUEST))
    {
        case USB_CLEAR_FEATURE:
        {
            usb_pstd_clr_feature0();   /* Clear Feature0 */
            break;
        }

        case USB_SET_FEATURE:
        {
            usb_pstd_set_feature0();   /* Set Feature0 */
            break;
        }

        case USB_SET_ADDRESS:
        {
            usb_pstd_set_address0();   /* Set Address0 */
            break;
        }

        case USB_SET_CONFIGURATION:
        {
            usb_pstd_set_configuration0(p_utr); /* Set Configuration0 */
            break;
        }

        case USB_SET_INTERFACE:
        {
            usb_pstd_set_interface0(p_utr); /* Set Interface0 */
            break;
        }

        default:
        {
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_stand_req0
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_stand_req1
 * Description     : The control read data stage of a standard request from host.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_stand_req1 (usb_utr_t * p_utr)
{
    switch ((g_usb_pstd_req_type & USB_BREQUEST))
    {
        case USB_GET_STATUS:
        {
            usb_pstd_get_status1(p_utr); /* Get Status1 */
            break;
        }

        case USB_GET_DESCRIPTOR:
        {
            usb_pstd_get_descriptor1(p_utr); /* Get Descriptor1 */
            break;
        }

        case USB_GET_CONFIGURATION:
        {
            usb_pstd_get_configuration1(p_utr); /* Get Configuration1 */
            break;
        }

        case USB_GET_INTERFACE:
        {
            usb_pstd_get_interface1(p_utr); /* Get Interface1 */
            break;
        }

        case USB_SYNCH_FRAME:
        {
            usb_pstd_synch_rame1(p_utr); /* Synch Frame */
            break;
        }

        default:
        {
            usb_pstd_set_stall_pipe0(p_utr); /* Set pipe USB_PID_STALL */
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_stand_req1
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_stand_req2
 * Description     : The control write data stage of a standard request from host.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_stand_req2 (usb_utr_t * p_utr)
{
    if (USB_SET_DESCRIPTOR == (g_usb_pstd_req_type & USB_BREQUEST))
    {
        /* Set Descriptor2 */
        usb_pstd_set_descriptor2(p_utr);
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_stand_req2
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_stand_req3
 * Description     : Standard request process. This is for the status stage of a
 *               : control write where there is no data stage.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_stand_req3 (usb_utr_t * p_utr)
{
    usb_instance_ctrl_t ctrl;

    switch ((g_usb_pstd_req_type & USB_BREQUEST))
    {
        case USB_CLEAR_FEATURE:
        {
            usb_pstd_clr_feature3(p_utr); /* ClearFeature3 */
            break;
        }

        case USB_SET_FEATURE:
        {
            usb_pstd_set_feature3(p_utr); /* SetFeature3 */
            break;
        }

        case USB_SET_ADDRESS:
        {
            usb_pstd_set_address3(p_utr); /* SetAddress3 */
            break;
        }

        case USB_SET_CONFIGURATION:
        {
            usb_pstd_set_configuration3(p_utr); /* SetConfiguration3 */
            break;
        }

        case USB_SET_INTERFACE:
        {
            usb_pstd_set_interface3(p_utr); /* SetInterface3 */
            break;
        }

        default:
        {
            usb_pstd_set_stall_pipe0(p_utr); /* Set pipe USB_PID_STALL */
            break;
        }
    }

    if (USB_YES == g_usb_pstd_std_request)
    {
        ctrl.setup.request_type   = g_usb_pstd_req_type;   /* Request type */
        ctrl.setup.request_value  = g_usb_pstd_req_value;  /* Value */
        ctrl.setup.request_index  = g_usb_pstd_req_index;  /* Index */
        ctrl.setup.request_length = g_usb_pstd_req_length; /* Length */
        ctrl.data_size            = 0;
        ctrl.status               = USB_SETUP_STATUS_ACK;
        ctrl.type                 = USB_CLASS_REQUEST;
        ctrl.module_number        = p_utr->ip;
 #if (BSP_CFG_RTOS == 1)
        ctrl.p_data = (void *) tx_thread_identify();
 #elif (BSP_CFG_RTOS == 2)             /* (BSP_CFG_RTOS == 1) */
        ctrl.p_data = (void *) xTaskGetCurrentTaskHandle();
 #endif                                /* (BSP_CFG_RTOS == 1) */
        usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl);

        g_usb_pstd_std_request = USB_NO;
    }

    usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* Control transfer stop(end) */
}

/******************************************************************************
 * End of function usb_pstd_stand_req3
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_stand_req4
 * Description     : The control read status stage of a standard request from host.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_stand_req4 (usb_utr_t * p_utr)
{
    usb_instance_ctrl_t ctrl;

    switch ((g_usb_pstd_req_type & USB_BREQUEST))
    {
        case USB_GET_STATUS:
        {
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* GetStatus4 */
            break;
        }

        case USB_GET_DESCRIPTOR:
        {
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* GetDescriptor4 */
            break;
        }

        case USB_GET_CONFIGURATION:
        {
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* GetConfiguration4 */
            break;
        }

        case USB_GET_INTERFACE:
        {
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* GetInterface4 */
            break;
        }

        case USB_SYNCH_FRAME:
        {
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* SynchFrame4 */
            break;
        }

        default:
        {
            usb_pstd_set_stall_pipe0(p_utr); /* Set pipe USB_PID_STALL */
            break;
        }
    }

    if (USB_YES == g_usb_pstd_std_request)
    {
        ctrl.setup.request_type   = g_usb_pstd_req_type;   /* Request type */
        ctrl.setup.request_value  = g_usb_pstd_req_value;  /* Value */
        ctrl.setup.request_index  = g_usb_pstd_req_index;  /* Index */
        ctrl.setup.request_length = g_usb_pstd_req_length; /* Length */
        ctrl.data_size            = 0;
        ctrl.status               = USB_SETUP_STATUS_ACK;
        ctrl.type                 = USB_CLASS_REQUEST;
        ctrl.module_number        = p_utr->ip;
 #if (BSP_CFG_RTOS == 1)
        ctrl.p_data = (void *) tx_thread_identify();
 #elif (BSP_CFG_RTOS == 2)             /* (BSP_CFG_RTOS == 1) */
        ctrl.p_data = (void *) xTaskGetCurrentTaskHandle();
 #endif                                /* (BSP_CFG_RTOS == 1) */
        usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl);

        g_usb_pstd_std_request = USB_NO;
    }

    usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* Control transfer stop(end) */
}

/******************************************************************************
 * End of function usb_pstd_stand_req4
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_stand_req5
 * Description     : The control write status stage of a standard request from host.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_stand_req5 (usb_utr_t * p_utr)
{
    usb_instance_ctrl_t ctrl;

    if (USB_SET_DESCRIPTOR == (g_usb_pstd_req_type & USB_BREQUEST))
    {
        /* Set pipe PID_BUF */
        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_set_stall_pipe0(p_utr);
    }

    if (USB_YES == g_usb_pstd_std_request)
    {
        ctrl.setup.request_type   = g_usb_pstd_req_type;   /* Request type */
        ctrl.setup.request_value  = g_usb_pstd_req_value;  /* Value */
        ctrl.setup.request_index  = g_usb_pstd_req_index;  /* Index */
        ctrl.setup.request_length = g_usb_pstd_req_length; /* Length */

        ctrl.data_size     = 0;
        ctrl.status        = USB_SETUP_STATUS_ACK;
        ctrl.type          = USB_CLASS_REQUEST;
        ctrl.module_number = p_utr->ip;
 #if (BSP_CFG_RTOS == 1)
        ctrl.p_data = (void *) tx_thread_identify();
 #elif (BSP_CFG_RTOS == 2)             /* (BSP_CFG_RTOS == 1) */
        ctrl.p_data = (void *) xTaskGetCurrentTaskHandle();
 #endif                                /* (BSP_CFG_RTOS == 1) */

        usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl);

        g_usb_pstd_std_request = USB_NO;
    }

    usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* Control transfer stop(end) */
}

/******************************************************************************
 * End of function usb_pstd_stand_req5
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_get_status1
 * Description     : Analyze a Get Status command and process it.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_get_status1 (usb_utr_t * p_utr)
{
    static uint8_t tbl[2];
    uint16_t       ep;
    uint16_t       buffer;
    uint16_t       pipe;

 #if defined(USB_CFG_OTG_USE)
    if ((0 == g_usb_pstd_req_value) && (1 == g_usb_pstd_req_length))
 #else
    if ((0 == g_usb_pstd_req_value) && (2 == g_usb_pstd_req_length))
 #endif
    {
        tbl[0] = 0;
        tbl[1] = 0;

        /* Check request type */
        switch ((g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
        {
            case USB_DEVICE:
            {
                if (0 == g_usb_pstd_req_index)
                {
                    /* Self powered / Bus powered */
                    tbl[0] = usb_pstd_get_current_power();

                    /* Support remote wakeup ? */
                    if (USB_TRUE == g_usb_pstd_remote_wakeup)
                    {
                        tbl[0] |= USB_GS_REMOTEWAKEUP;
                    }

                    /* Control read start */
                    usb_pstd_ctrl_read((uint32_t) 2, tbl, p_utr);
                }

 #if defined(USB_CFG_OTG_USE)
                else if (USB_OTG_SELECTOR == g_usb_pstd_req_index)
                {
                    tbl[0] = (uint8_t) _ux_system_otg->ux_system_otg_slave_role_swap_flag;

                    /* Control read start */
                    usb_pstd_ctrl_read((uint32_t) 1, tbl, p_utr);
                }
 #endif                                /* defined(USB_CFG_OTG_USE) */
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            case USB_INTERFACE:
            {
                if (USB_TRUE == usb_pstd_chk_configured(p_utr))
                {
                    if (g_usb_pstd_req_index < usb_pstd_get_interface_num())
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) 2, tbl, p_utr);
                    }
                    else
                    {
                        /* Request error (not exist interface) */
                        usb_pstd_set_stall_pipe0(p_utr);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            case USB_ENDPOINT:
            {
                /* Endpoint number */
                ep = (uint16_t) (g_usb_pstd_req_index & USB_EPNUMFIELD);

                /* Endpoint 0 */
                if (0 == ep)
                {
                    buffer = hw_usb_read_dcpctr(p_utr->ip);
                    if ((uint16_t) 0 != (buffer & USB_PID_STALL))
                    {
                        /* Halt set */
                        tbl[0] = USB_GS_HALT;
                    }

                    /* Control read start */
                    usb_pstd_ctrl_read((uint32_t) 2, tbl, p_utr);
                }
                /* EP1 to max */
                else if (ep <= USB_MAX_EP_NO)
                {
                    if (USB_TRUE == usb_pstd_chk_configured(p_utr))
                    {
                        pipe = usb_pstd_epadr2pipe(g_usb_pstd_req_index, p_utr);
                        if (USB_ERROR == pipe)
                        {
                            /* Set pipe USB_PID_STALL */
                            usb_pstd_set_stall_pipe0(p_utr);
                        }
                        else
                        {
                            buffer = usb_cstd_get_pid(p_utr, pipe);
                            if ((uint16_t) 0 != (buffer & USB_PID_STALL))
                            {
                                /* Halt set */
                                tbl[0] = USB_GS_HALT;
                            }

                            /* Control read start */
                            usb_pstd_ctrl_read((uint32_t) 2, tbl, p_utr);
                        }
                    }
                    else
                    {
                        /* Set pipe USB_PID_STALL */
                        usb_pstd_set_stall_pipe0(p_utr);
                    }
                }
                else
                {
                    /* Set pipe USB_PID_STALL */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            default:
            {
                /* Set pipe USB_PID_STALL */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }
        }
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_get_status1
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_get_descriptor1
 * Description     : Analyze a Get Descriptor command from host and process it.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_get_descriptor1 (usb_utr_t * p_utr)
{
    uint16_t  len;
    uint16_t  idx;
    uint8_t * p_table;
    uint16_t  connect_info;
 #if (BSP_CFG_RTOS == 1)
    uint8_t i = 0;
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

    if (USB_DEVICE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
    {
        idx = (uint16_t) (g_usb_pstd_req_value & USB_DT_INDEX);
        switch ((uint16_t) USB_GET_DT_TYPE(g_usb_pstd_req_value))
        {
            /*---- Device descriptor ----*/
            case USB_DT_DEVICE:
            {
                if (((uint16_t) 0 == g_usb_pstd_req_index) && ((uint16_t) 0 == idx))
                {
                    p_table = g_usb_pstd_driver.p_devicetbl;
                    if (g_usb_pstd_req_length < p_table[0])
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) g_usb_pstd_req_length, p_table, p_utr);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) p_table[0], p_table, p_utr);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            /*---- Configuration descriptor ----*/
            case USB_DT_CONFIGURATION:
            {
                if ((0 == g_usb_pstd_req_index) && ((uint16_t) 0 == idx))
                {
                    connect_info = usb_cstd_port_speed(p_utr);
                    if (USB_HSCONNECT == connect_info)
                    {
                        p_table = g_usb_pstd_driver.p_othertbl;
                    }
                    else
                    {
                        p_table = g_usb_pstd_driver.p_configtbl;
                    }

                    len = (uint16_t) (*(uint8_t *) ((uint32_t) p_table + (uint32_t) 3));
                    len = (uint16_t) (len << 8);
                    len = (uint16_t) (len + (uint16_t) (*(uint8_t *) ((uint32_t) p_table + (uint32_t) 2)));

                    /* Descriptor > wLength */
                    if (g_usb_pstd_req_length < len)
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) g_usb_pstd_req_length, p_table, p_utr);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) len, p_table, p_utr);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            /*---- String descriptor ----*/
            case USB_DT_STRING:
            {
                if (idx < g_usb_pstd_driver.num_string)
                {
 #if (BSP_CFG_RTOS == 1)
                    g_usbx_string[1] = USB_DT_STRING;
                    p_table          = g_usb_pstd_driver.p_stringtbl[idx];
                    if (0 == idx)
                    {
                        if (g_usb_pstd_req_length == 2)
                        {
                            /* Lang ID */
                            len              = g_usb_pstd_req_length;
                            g_usbx_string[0] = (uint8_t) len;
                            g_usbx_string[2] = *p_table;
                            g_usbx_string[3] = *(p_table + 1);
                        }
                        else
                        {
                            /* Lang ID */
                            len              = 4;
                            g_usbx_string[0] = (uint8_t) len;
                            g_usbx_string[2] = *p_table;
                            g_usbx_string[3] = *(p_table + 1);
                        }
                    }
                    else
                    {
                        /* Other than Land ID */
                        len              = (uint16_t) (*(p_table + 3));
                        g_usbx_string[0] = (uint8_t) ((len * 2) + 2);
                        if (g_usbx_string[0] > g_usb_pstd_req_length)
                        {
                            len = (uint16_t) ((g_usb_pstd_req_length - 2) / 2);
                        }

                        for (i = 0; i < len; i++)
                        {
                            g_usbx_string[2 + (i * 2)] = *(p_table + i + 4);
                            g_usbx_string[3 + (i * 2)] = 0x00;
                        }

                        len = (uint16_t) ((len * 2) + 2);
                    }

                    usb_pstd_ctrl_read((uint32_t) len, g_usbx_string, p_utr);
 #else                                 /* #if (BSP_CFG_RTOS == 1) */
                    p_table = g_usb_pstd_driver.p_stringtbl[idx];
                    len     = (uint16_t) (*(uint8_t *) ((uint32_t) p_table + (uint32_t) 0));
                    if (g_usb_pstd_req_length < len)
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) g_usb_pstd_req_length, p_table, p_utr);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) len, p_table, p_utr);
                    }
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
                }
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            /*---- Interface descriptor ----*/
            case USB_DT_INTERFACE:
            {
                /* Set pipe USB_PID_STALL */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }

            /*---- Endpoint descriptor ----*/
            case USB_DT_ENDPOINT:
            {
                /* Set pipe USB_PID_STALL */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }

            case USB_DT_DEVICE_QUALIFIER:
            {
                if ((USB_TRUE == usb_pstd_hi_speed_enable(p_utr)) && ((0 == g_usb_pstd_req_index) && (0 == idx)))
                {
                    p_table = g_usb_pstd_driver.p_qualitbl;
                    if (g_usb_pstd_req_length < p_table[0])
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) g_usb_pstd_req_length, p_table, p_utr);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) p_table[0], p_table, p_utr);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            case USB_DT_OTHER_SPEED_CONF:
            {
                if ((USB_TRUE == usb_pstd_hi_speed_enable(p_utr)) &&
                    ((0 == g_usb_pstd_req_index) && ((uint16_t) 0 == idx)))
                {
                    connect_info = usb_cstd_port_speed(p_utr);
                    if (USB_HSCONNECT == connect_info)
                    {
                        p_table = g_usb_pstd_driver.p_configtbl;
                    }
                    else
                    {
                        p_table = g_usb_pstd_driver.p_othertbl;
                    }

                    len = (uint16_t) (*(uint8_t *) ((uint32_t) p_table + (uint32_t) 3));
                    len = (uint16_t) (len << 8);
                    len = (uint16_t) (len + (uint16_t) (*(uint8_t *) ((uint32_t) p_table + (uint32_t) 2)));

                    /* Descriptor > wLength */
                    if (g_usb_pstd_req_length < len)
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) g_usb_pstd_req_length, p_table, p_utr);
                    }
                    else
                    {
                        /* Control read start */
                        usb_pstd_ctrl_read((uint32_t) len, p_table, p_utr);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            case USB_DT_INTERFACE_POWER:
            {
                /* Not support */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }

            default:
            {
                /* Set pipe USB_PID_STALL */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }
        }
    }
    else if (USB_INTERFACE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
    {
        g_usb_pstd_req_reg.request_type   = g_usb_pstd_req_type;
        g_usb_pstd_req_reg.request_value  = g_usb_pstd_req_value;
        g_usb_pstd_req_reg.request_index  = g_usb_pstd_req_index;
        g_usb_pstd_req_reg.request_length = g_usb_pstd_req_length;
        if (USB_NULL != g_usb_pstd_driver.ctrltrans)
        {
            (*g_usb_pstd_driver.ctrltrans)(&g_usb_pstd_req_reg, (uint16_t) USB_NO_ARG, p_utr);
        }
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_get_descriptor1
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_get_configuration1
 * Description     : Analyze a Get Configuration command and process it.
 *               : (for control read data stage)
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_get_configuration1 (usb_utr_t * p_utr)
{
    static uint8_t tbl[2];

    /* check request */
    if ((((USB_DEVICE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP)) && (0 == g_usb_pstd_req_value)) &&
         (0 == g_usb_pstd_req_index)) && (1 == g_usb_pstd_req_length))
    {
        tbl[0] = (uint8_t) g_usb_pstd_config_num;

        /* Control read start */
        usb_pstd_ctrl_read((uint32_t) 1, tbl, p_utr);
    }
    else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_get_configuration1
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_get_interface1
 * Description     : Analyze a Get Interface command and process it.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_get_interface1 (usb_utr_t * p_utr)
{
    static uint8_t tbl[2];

    /* check request */
    if (((USB_INTERFACE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP)) && (0 == g_usb_pstd_req_value)) &&
        (1 == g_usb_pstd_req_length))
    {
        if (g_usb_pstd_req_index < USB_ALT_NO)
        {
            tbl[0] = (uint8_t) g_usb_pstd_alt_num[g_usb_pstd_req_index];

            /* Start control read */
            usb_pstd_ctrl_read((uint32_t) 1, tbl, p_utr);
        }
        else
        {
            /* Request error */
            usb_pstd_set_stall_pipe0(p_utr);
        }
    }
    else
    {
        /* Request error */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_get_interface1
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_clr_feature0
 * Description     : Clear Feature0
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_clr_feature0 (void)
{
 #if USB_CFG_REQUEST == USB_CFG_ENABLE
    if (0 == g_usb_pstd_req_length)
    {
        /* check request type */
        if (USB_DEVICE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
        {
            if ((USB_DEV_REMOTE_WAKEUP == g_usb_pstd_req_value) && (0 == g_usb_pstd_req_index))
            {
                if (USB_TRUE == usb_pstd_chk_remote())
                {
                    usb_pstd_request_event_set(p_utr);
                }
            }
        }
    }
 #endif                                /* USB_CFG_REQUEST == USB_CFG_ENABLE */
} /* End of function usb_pstd_clr_feature0 */

/******************************************************************************
 * Function Name   : usb_pstd_clr_feature3
 * Description     : Analyze a Clear Feature command and process it.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_clr_feature3 (usb_utr_t * p_utr)
{
    uint16_t pipe;
    uint16_t ep;

    if (0 == g_usb_pstd_req_length)
    {
        /* check request type */
        switch ((g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
        {
            case USB_DEVICE:
            {
                if ((USB_DEV_REMOTE_WAKEUP == g_usb_pstd_req_value) && (0 == g_usb_pstd_req_index))
                {
                    if (USB_TRUE == usb_pstd_chk_remote())
                    {
                        g_usb_pstd_remote_wakeup = USB_FALSE;

                        /* Set pipe PID_BUF */
                        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                    }
                    else
                    {
                        /* Not support remote wakeup */
                        /* Request error */
                        usb_pstd_set_stall_pipe0(p_utr);
                    }
                }
                else
                {
                    /* Not specification */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

 #if (BSP_CFG_RTOS == 1)
                _ux_device_stack_clear_feature((ULONG) g_usb_pstd_req_type,
                                               (ULONG) g_usb_pstd_req_value,
                                               (ULONG) g_usb_pstd_req_index);
 #endif                                /* BSP_CFG_RTOS == 1 */
                break;
            }

            case USB_INTERFACE:
            {
                /* Request error */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }

            case USB_ENDPOINT:
            {
                /* Endpoint number */
                ep = (uint16_t) (g_usb_pstd_req_index & USB_EPNUMFIELD);
                if (USB_ENDPOINT_HALT == g_usb_pstd_req_value)
                {
                    /* EP0 */
                    if (0 == ep)
                    {
                        /* Stall clear */
                        usb_cstd_clr_stall(p_utr, (uint16_t) USB_PIPE0);

                        /* Set pipe PID_BUF */
                        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                    }
                    /* EP1 to max */
                    else if (ep <= USB_MAX_EP_NO)
                    {
                        pipe = usb_pstd_epadr2pipe(g_usb_pstd_req_index, p_utr);
                        if (USB_ERROR == pipe)
                        {
                            /* Request error */
                            usb_pstd_set_stall_pipe0(p_utr);
                        }
                        else
                        {
                            if (USB_PID_BUF == usb_cstd_get_pid(p_utr, pipe))
                            {
                                usb_cstd_set_nak(p_utr, pipe);

                                /* SQCLR=1 */
                                hw_usb_set_sqclr(p_utr, pipe);

                                /* Set pipe PID_BUF */
                                usb_cstd_set_buf(p_utr, pipe);
                            }
                            else
                            {
                                usb_cstd_clr_stall(p_utr, pipe);

                                /* SQCLR=1 */
                                hw_usb_set_sqclr(p_utr, pipe);
                            }

                            /* Set pipe PID_BUF */
                            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                            if (USB_TRUE == g_usb_pstd_stall_pipe[pipe])
                            {
                                g_usb_pstd_stall_pipe[pipe] = USB_FALSE;
                                (*g_usb_pstd_stall_cb)(p_utr, USB_NULL, USB_NULL);
                            }
                        }
                    }
                    else
                    {
                        /* Request error */
                        usb_pstd_set_stall_pipe0(p_utr);
                    }
                }
                else
                {
                    /* Request error */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

 #if (BSP_CFG_RTOS == 1)
                _ux_device_stack_clear_feature((ULONG) g_usb_pstd_req_type,
                                               (ULONG) g_usb_pstd_req_value,
                                               (ULONG) g_usb_pstd_req_index);
 #endif                                /* BSP_CFG_RTOS == 1 */
                break;
            }

            default:
            {
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }
        }
    }
    else
    {
        /* Not specification */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_clr_feature3
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_feature0
 * Description     : Set Feature0 (for idle/setup stage)
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_feature0 (void)
{
 #if USB_CFG_REQUEST == USB_CFG_ENABLE
    if (0 == g_usb_pstd_req_length)
    {
        /* check request type */
        if (USB_DEVICE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
        {
            if ((USB_DEV_REMOTE_WAKEUP == g_usb_pstd_req_value) && (0 == g_usb_pstd_req_index))
            {
                if (USB_TRUE == usb_pstd_chk_remote())
                {
                    usb_pstd_request_event_set(p_utr);
                }
            }
        }
    }
 #endif                                /* USB_CFG_REQUEST == USB_CFG_ENABLE */
} /* End of function usb_pstd_set_feature0 */

/******************************************************************************
 * Function Name   : usb_pstd_set_feature3
 * Description     : Analyze a Set Feature command and process it.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_feature3 (usb_utr_t * p_utr)
{
    uint16_t pipe;
    uint16_t ep;

    if (0 == g_usb_pstd_req_length)
    {
        /* check request type */
        switch ((g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
        {
            case USB_DEVICE:
            {
                switch (g_usb_pstd_req_value)
                {
                    case USB_DEV_REMOTE_WAKEUP:
                    {
                        if (0 == g_usb_pstd_req_index)
                        {
                            if (USB_TRUE == usb_pstd_chk_remote())
                            {
                                g_usb_pstd_remote_wakeup = USB_TRUE;

                                /* Set pipe PID_BUF */
                                usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                            }
                            else
                            {
                                /* Not support remote wakeup */
                                /* Request error */
                                usb_pstd_set_stall_pipe0(p_utr);
                            }
                        }
                        else
                        {
                            /* Not specification */
                            usb_pstd_set_stall_pipe0(p_utr);
                        }

                        break;
                    }

                    case USB_TEST_MODE:
                    {
                        if (USB_HSCONNECT == usb_cstd_port_speed(p_utr))
                        {
                            if ((g_usb_pstd_req_index < USB_TEST_RESERVED) ||
                                (USB_TEST_VSTMODES <= g_usb_pstd_req_index))
                            {
                                g_usb_pstd_test_mode_flag   = USB_TRUE;
                                g_usb_pstd_test_mode_select = g_usb_pstd_req_index;

                                /* Set pipe PID_BUF */
                                usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                            }
                            else
                            {
                                /* Not specification */
                                usb_pstd_set_stall_pipe0(p_utr);
                            }
                        }
                        else
                        {
                            /* Not specification */
                            usb_pstd_set_stall_pipe0(p_utr);
                        }

                        break;
                    }

 #ifdef  USB_CFG_OTG_USE
                    case B_HNP_ENABLE:
                    {
                        g_usb_otg_hnp_process[p_utr->ip] = USB_ON;
                        hw_usb_set_hnpbtoa(p_utr);
                        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);

                        break;
                    }

                    case A_HNP_SUPPORT:
                    {
                        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                        break;
                    }
 #endif                                /* USB_CFG_OTG_USE */

                    default:
                    {
                        usb_pstd_set_feature_function(p_utr);
                        break;
                    }
                }

                break;
            }

            case USB_INTERFACE:
            {
                /* Set pipe USB_PID_STALL */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }

            case USB_ENDPOINT:
            {
                /* Endpoint number */
                ep = (uint16_t) (g_usb_pstd_req_index & USB_EPNUMFIELD);
                if (USB_ENDPOINT_HALT == g_usb_pstd_req_value)
                {
                    /* EP0 */
                    if (0 == ep)
                    {
                        /* Set pipe PID_BUF */
                        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                    }
                    /* EP1 to max */
                    else if (ep <= USB_MAX_EP_NO)
                    {
                        pipe = usb_pstd_epadr2pipe(g_usb_pstd_req_index, p_utr);
                        if (USB_ERROR == pipe)
                        {
                            /* Request error */
                            usb_pstd_set_stall_pipe0(p_utr);
                        }
                        else
                        {
                            /* Set pipe USB_PID_STALL */
                            usb_pstd_set_stall(pipe, p_utr);

                            /* Set pipe PID_BUF */
                            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                        }
                    }
                    else
                    {
                        /* Request error */
                        usb_pstd_set_stall_pipe0(p_utr);
                    }
                }
                else
                {
                    /* Not specification */
                    usb_pstd_set_stall_pipe0(p_utr);
                }

                break;
            }

            default:
            {
                /* Request error */
                usb_pstd_set_stall_pipe0(p_utr);
                break;
            }
        }

 #if BSP_CFG_RTOS == 1
        _ux_device_stack_set_feature((ULONG) g_usb_pstd_req_type,
                                     (ULONG) g_usb_pstd_req_value,
                                     (ULONG) g_usb_pstd_req_index);
 #endif
    }
    else
    {
        /* Request error */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_set_feature3
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_address0
 * Description     : Set Address0 (for idle/setup stage).
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_address0 (void)
{
    /* Non processing. */
}

/******************************************************************************
 * End of function usb_pstd_set_address0
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_address3
 * Description     : Analyze a Set Address command and process it.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_address3 (usb_utr_t * p_utr)
{
    if (USB_DEVICE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
    {
        if ((0 == g_usb_pstd_req_index) && (0 == g_usb_pstd_req_length))
        {
            if (g_usb_pstd_req_value <= USB_DEVICE_ADDRESS_MAX)
            {
                /* Set pipe PID_BUF */
                usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
            }
            else
            {
                /* Not specification */
                usb_pstd_set_stall_pipe0(p_utr);
            }
        }
        else
        {
            /* Not specification */
            usb_pstd_set_stall_pipe0(p_utr);
        }
    }
    else
    {
        /* Request error */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_set_address3
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_descriptor2
 * Description     : Return STALL in response to a Set Descriptor command.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_descriptor2 (usb_utr_t * p_utr)
{
    /* Not specification */
    usb_pstd_set_stall_pipe0(p_utr);
}

/******************************************************************************
 * End of function usb_pstd_set_descriptor2
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_configuration0
 * Description     : Call callback function to notify the reception of SetConfiguration command
 *               : (for idle /setup stage)
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_configuration0 (usb_utr_t * p_utr)
{
    uint16_t config_num;

    config_num = g_usb_pstd_config_num;

    /* Configuration number set */
    usb_pstd_set_config_num(g_usb_pstd_req_value);

    if (g_usb_pstd_req_value != config_num)
    {
        if (USB_NULL != g_usb_pstd_driver.devconfig)
        {
            /* Registration open function call */
            (*g_usb_pstd_driver.devconfig)(p_utr, g_usb_pstd_config_num, USB_NULL);

 #if (BSP_CFG_RTOS == 1)
  #if defined(USB_CFG_PHID_USE)
            _ux_system_slave->ux_system_slave_remote_wakeup_enabled = UX_FALSE;
  #endif                               /* #if defined(USB_CFG_PHID_USE) */
            g_usb_peri_usbx_is_configured[p_utr->ip] = USB_YES;
            _ux_device_stack_configuration_set((uint32_t) g_usb_pstd_config_num);
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
        }
    }
}

/******************************************************************************
 * End of function usb_pstd_set_configuration0
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_configuration3
 * Description     : Analyze a Set Configuration command and process it. This is
 *               : for the status stage of a control write where there is no data
 *               : stage.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_configuration3 (usb_utr_t * p_utr)
{
    uint16_t i;

    uint16_t ifc;

    uint16_t  cfgok;
    uint8_t * p_table2;

    if (USB_DEVICE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP))
    {
        cfgok = USB_ERROR;

        p_table2 = g_usb_pstd_driver.p_configtbl;

        if ((((g_usb_pstd_req_value == p_table2[5]) || (0 == g_usb_pstd_req_value)) && (0 == g_usb_pstd_req_index)) &&
            (0 == g_usb_pstd_req_length))
        {
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
            cfgok = USB_OK;

            if ((g_usb_pstd_req_value > 0) && (g_usb_pstd_req_value != g_usb_pstd_config_num))
            {
                usb_pstd_clr_eptbl_index();
                ifc = usb_pstd_get_interface_num();

                /* WAIT_LOOP */
                for (i = 0; i < ifc; ++i)
                {
                    /* Pipe Information Table ("endpoint table") initialize */
                    usb_pstd_set_eptbl_index(i, (uint16_t) 0);
                }

                /* Clear pipe register */
                usb_pstd_clr_pipe_reg(p_utr);

                /* Set pipe register */
                usb_pstd_set_pipe_reg(p_utr);
            }
        }

        if (USB_ERROR == cfgok)
        {
            /* Request error */
            usb_pstd_set_stall_pipe0(p_utr);
        }
    }
    else
    {
        /* Request error */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_set_configuration3
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_interface0
 * Description     : Call callback function to notify reception of SetInterface com-
 *               : mand. For idle/setup stage.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_interface0 (usb_utr_t * p_utr)
{
    if (USB_NULL != g_usb_pstd_driver.interface)
    {
        /* Interfaced change function call */
        (*g_usb_pstd_driver.interface)(p_utr, g_usb_pstd_alt_num[g_usb_pstd_req_index], USB_NULL);
    }

 #if USB_CFG_REQUEST == USB_CFG_ENABLE
    usb_pstd_request_event_set(p_utr);
 #endif                                /* USB_CFG_REQUEST == USB_CFG_ENABLE */
}

/******************************************************************************
 * End of function usb_pstd_set_interface0
 ******************************************************************************/

 #define NUM_OF_INTERFACE    (8U)
extern uint8_t g_usb_paud_iso_pipe[NUM_OF_INTERFACE];
 #if (BSP_CFG_RTOS == 1)
extern TX_SEMAPHORE g_usb_peri_usbx_sem[USB_MAX_PIPE_NO + 1];
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Function Name   : usb_pstd_set_interface3
 * Description     : Analyze a Set Interface command and request the process for
 *               : the command. This is for a status stage of a control write
 *               : where there is no data stage.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_set_interface3 (usb_utr_t * p_utr)
{
 #ifdef  USB_CFG_PAUD_USE
    uint16_t current_alt_value;
    uint8_t  pipe;
 #endif                                // USB_CFG_PAUD_USE

    /* Configured ? */
    if ((USB_TRUE == usb_pstd_chk_configured(p_utr)) &&
        (USB_INTERFACE == (g_usb_pstd_req_type & USB_BMREQUESTTYPERECIP)))
    {
 #if defined(USB_CFG_PPRN_USE)
        if (((1 == usb_pstd_get_interface_num()) && (0 == usb_pstd_get_alternate_num(0))) &&
            ((0 == g_usb_pstd_req_index) && (0 == g_usb_pstd_req_value)))
        {
            /* Do nothing about alternate setting */
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
        }

 #else                                 /* defined(USB_CFG_PPRN_USE) */
        if ((g_usb_pstd_req_index <= usb_pstd_get_interface_num()) && (0 == g_usb_pstd_req_length))
        {
            if (g_usb_pstd_req_value <= usb_pstd_get_alternate_num(g_usb_pstd_req_index))
            {
  #ifdef  USB_CFG_PAUD_USE
                current_alt_value = g_usb_pstd_alt_num[g_usb_pstd_req_index];
  #endif                               // USB_CFG_PAUD_USE
                g_usb_pstd_alt_num[g_usb_pstd_req_index] = (uint16_t) (g_usb_pstd_req_value & USB_ALT_SET);
                usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
                usb_pstd_clr_eptbl_index();

                /* Search endpoint setting */
                usb_pstd_set_eptbl_index(g_usb_pstd_req_index, g_usb_pstd_alt_num[g_usb_pstd_req_index]);
  #if !defined(USB_CFG_PAUD_USE) && !defined(USB_CFG_DFU_USE)
                usb_pstd_set_pipe_reg(p_utr);
  #endif                               /* #if !defined(USB_CFG_PAUD_USE) && !defined(USB_CFG_DFU_USE) */
  #if BSP_CFG_RTOS == 1
   #ifdef  USB_CFG_PAUD_USE
                if (0 == (g_usb_pstd_req_value & USB_ALT_SET))
                {
                    if (current_alt_value == 1)
                    {
                        /* Alternate Setting 1 --> 0 */
                        pipe = g_usb_paud_iso_pipe[g_usb_pstd_req_index]; // g_usb_pstd_req_index: Interface Number
                        usb_pstd_forced_termination(pipe, (uint16_t) USB_DATA_STOP, p_utr);
                    }
                }
   #endif                                                                 // USB_CFG_PAUD_USE
                _ux_device_stack_alternate_setting_set((ULONG) g_usb_pstd_req_index, (ULONG) g_usb_pstd_req_value);
  #endif
            }
            else
            {
                /* Request error */
                usb_pstd_set_stall_pipe0(p_utr);
            }
        }
 #endif                                /* defined(USB_CFG_PPRN_USE) */
        else
        {
            /* Request error */
            usb_pstd_set_stall_pipe0(p_utr);
        }
    }
    else
    {
        /* Request error */
        usb_pstd_set_stall_pipe0(p_utr);
    }
}

/******************************************************************************
 * End of function usb_pstd_set_interface3
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_synch_rame1
 * Description     : Return STALL response to SynchFrame command.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_pstd_synch_rame1 (usb_utr_t * p_utr)
{
    /* Set pipe USB_PID_STALL */
    usb_pstd_set_stall_pipe0(p_utr);
}

/******************************************************************************
 * End of function usb_pstd_synch_rame1
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 1)

/******************************************************************************
 * Function Name   : usb_peri_class_request_usbx
 * Description     : Class request processing for data stage (USBX)
 * Arguments       : usb_setup_t *p_req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
static void usb_peri_class_request_usbx (usb_setup_t * p_req)
{
    UX_SLAVE_DEVICE      * device;
    UX_SLAVE_CLASS       * class;
    UX_SLAVE_CLASS_COMMAND class_command;
    uint32_t               class_index;
    UX_SLAVE_TRANSFER    * transfer_request;
    uint32_t               status;

  #if defined(USB_CFG_PHID_USE)
    if ((USB_CLASS == (p_req->request_type & USB_BMREQUESTTYPETYPE)) ||
        (USB_VENDOR == (p_req->request_type & USB_BMREQUESTTYPETYPE)) ||
        (USB_STANDARD == (p_req->request_type & USB_BMREQUESTTYPETYPE)))
  #else                                /* #if defined(USB_CFG_PHID_USE) */
    if ((USB_CLASS == (p_req->request_type & USB_BMREQUESTTYPETYPE)) ||
        (USB_VENDOR == (p_req->request_type & USB_BMREQUESTTYPETYPE)))
  #endif /* #if defined(USB_CFG_PHID_USE) */
    {
        class_command.ux_slave_class_command_request = UX_SLAVE_CLASS_COMMAND_REQUEST;
        for (class_index = 0; class_index < UX_MAX_SLAVE_INTERFACES; class_index++)
        {
  #if defined(USB_CFG_PAUD_USE)
        	/* Check the received audio class request is for the interface
        	 * (i.e. recipient is interface) or endpoint(i.e. recipient is endpoint). */
            if ((USB_INTERFACE == (p_req->request_type & USB_BMREQUESTTYPERECIP)) ||
                (USB_ENDPOINT == (p_req->request_type & USB_BMREQUESTTYPERECIP)))
  #else  /* defined(USB_CFG_PAUD_USE) */
            if (USB_INTERFACE == (p_req->request_type & USB_BMREQUESTTYPERECIP))
  #endif
            {
  #if defined(USB_CFG_PAUD_USE)
              /* Verify the interface value(i.e. request index value),
               * only when received audio class request is for the interface
               * (i.e. recipient is interface). */
             if (USB_INTERFACE == (p_req->request_type & USB_BMREQUESTTYPERECIP))
             {
  #endif  /* defined(USB_CFG_PAUD_USE) */
            	if ((p_req->request_index & VALUE_FFH) != class_index)
                {
                    continue;
                }
  #if defined(USB_CFG_PAUD_USE)
             }
  #endif  /* defined(USB_CFG_PAUD_USE) */
                class = _ux_system_slave->ux_system_slave_interface_class_array[class_index];
                if (UX_NULL == class)
                {
                    continue;
                }

                device           = &_ux_system_slave->ux_system_slave_device;
                transfer_request =
                    &device->ux_slave_device_control_endpoint.ux_slave_endpoint_transfer_request;
                *(transfer_request->ux_slave_transfer_request_setup +
                  FSP_SETUP_REQUEST) = (uint8_t) (p_req->request_type >> 8);
                *(uint16_t *) (transfer_request->ux_slave_transfer_request_setup +
                               FSP_SETUP_VALUE) = p_req->request_value;
                *(uint16_t *) (transfer_request->ux_slave_transfer_request_setup +
                               FSP_SETUP_LENGTH) = p_req->request_length;
                transfer_request->ux_slave_transfer_request_actual_length = p_req->request_length - g_usb_pstd_data_cnt[USB_PIPE0];
  #if defined(USB_CFG_PAUD_USE) || defined(USB_CFG_DFU_USE)
                *(transfer_request->ux_slave_transfer_request_setup +
                  FSP_SETUP_REQUEST_TYPE) = (uint8_t) (p_req->request_type & VALUE_FFH);
                *(transfer_request->ux_slave_transfer_request_setup +
                  FSP_SETUP_INDEX_L) = (uint8_t) (p_req->request_index & VALUE_FFH);
                *(transfer_request->ux_slave_transfer_request_setup +
                  FSP_SETUP_INDEX_H) = (uint8_t) (p_req->request_index >> 8);
  #endif                               /* #if defined(USB_CFG_PAUD_USE) || defined(USB_CFG_DFU_USE)*/
                class_command.ux_slave_class_command_class_ptr = class;
                status = class->ux_slave_class_entry_function(&class_command);
                if (status == UX_SUCCESS)
                {
                    break;
                }
            }
        }
    }
}                                      /* End of function usb_peri_class_request_usbx */

/******************************************************************************
 * Function Name   : usb_peri_class_reqeust_usbx_get_data
 * Description     : Class request processing for data stage (USBX)
 * Arguments       : usb_setup_t *p_req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
static void usb_peri_class_reqeust_usbx_get_data (usb_setup_t * p_req, usb_utr_t * p_utr)
{
    FSP_PARAMETER_NOT_USED(p_req);
    UX_SLAVE_DEVICE   * device;
    UX_SLAVE_TRANSFER * transfer_request;
    usb_utr_t           tran_data;

    tran_data.ip     = p_utr->ip;
    device           = &_ux_system_slave->ux_system_slave_device;
    transfer_request = &device->ux_slave_device_control_endpoint.ux_slave_endpoint_transfer_request;

    if (USB_YES == g_usb_pstd_pipe0_request)
    {
        while (1)
        {
            ;
        }
    }

    g_usb_pstd_std_request = USB_YES;

    usb_pstd_ctrl_write(p_req->request_length, transfer_request->ux_slave_transfer_request_data_pointer, &tran_data);
}                                      /* End of function usb_peri_class_reqeust_usbx_get_data */

 #endif /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Function Name   : usb_peri_class_request
 * Description     : Class request processing for Device class
 * Arguments       : usb_setup_t *preq    ; Class request information
 *               : uint16_t ctsq        ; Control Stage
 * Return value    : none
 ******************************************************************************/
void usb_peri_class_request (usb_setup_t * preq, uint16_t ctsq, usb_utr_t * p_utr)
{
    /* Check Request type TYPE */
    if ((USB_CLASS == (preq->request_type & USB_BMREQUESTTYPETYPE)) ||
        (USB_VENDOR == (preq->request_type & USB_BMREQUESTTYPETYPE)))
    {
        /* Branch by the Control Transfer Stage */
        switch (ctsq)
        {
            case USB_CS_IDST:
            {
                g_usb_pstd_pipe0_request = USB_OFF;
                g_usb_pstd_std_request   = USB_NO;
                usb_peri_class_request_ioss(preq); /* class request (idle or setup stage) */
                break;
            }

            case USB_CS_RDDS:
            {
                usb_peri_class_request_rwds(preq, p_utr); /* class request (control read data stage) */
                break;
            }

            case USB_CS_WRDS:
            {
                usb_peri_class_request_rwds(preq, p_utr); /* class request (control write data stage) */
                break;
            }

            case USB_CS_WRND:
            {
                usb_peri_class_request_wnss(preq, p_utr); /* class request (control write nodata status stage) */
                break;
            }

            case USB_CS_RDSS:
            {
                usb_peri_class_request_rss(preq, p_utr); /* class request (control read status stage) */
                break;
            }

            case USB_CS_WRSS:
            {
                usb_peri_class_request_wss(preq, p_utr); /* class request (control write status stage) */
                break;
            }

            case USB_CS_SQER:
            {
                usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, p_utr); /* End control transfer. */
                break;
            }

            default:
            {
                usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR, p_utr); /* End control transfer. */
                break;
            }
        }
    }
    else
    {
        usb_peri_other_request(preq, p_utr);
    }
}                                      /* End of function usb_peri_class_request */

/******************************************************************************
 * Function Name   : usb_peri_class_request_ioss
 * Description     : Class Request (idle or setup stage)
 * Arguments       : usb_setup_t *req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
void usb_peri_class_request_ioss (usb_setup_t * req)
{
    (void) *req;

    /* Non */
}                                      /* End of function usb_peri_class_request_ioss */

/******************************************************************************
 * Function Name   : usb_peri_class_request_rwds
 * Description     : Class request processing (control read/write data stage)
 * Arguments       : usb_setup_t *req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
void usb_peri_class_request_rwds (usb_setup_t * req, usb_utr_t * p_utr)
{
 #if (BSP_CFG_RTOS == 1)
    if (0 != (req->request_type & USB_BMREQUESTTYPEDIR))
    {
        /* In Data */
        usb_peri_class_request_usbx(req);
    }
    else
    {
        /* Out Data */
        usb_peri_class_reqeust_usbx_get_data(req, p_utr);
    }

 #else                                 /* (BSP_CFG_RTOS == 1) */
  #if defined(USB_CFG_PMSC_USE)
    usb_instance_ctrl_t ctrl;

    /* Is a request receive target Interface? */
    if (USB_INTERFACE == (req->request_type & USB_BMREQUESTTYPERECIP))
    {
        if (USB_GET_MAX_LUN == (req->request_type & USB_BREQUEST))
        {
            usb_pmsc_get_max_lun(req->request_value, req->request_index, req->request_length, p_utr);
        }
        else
        {
            /* Get Line Coding Request etc */
            ctrl.module_number = p_utr->ip;
            ctrl.setup         = *req; /* Save setup data. */
            ctrl.data_size     = 0;
            ctrl.status        = USB_SETUP_STATUS_ACK;
            ctrl.type          = USB_CLASS_REQUEST;
            usb_set_event(USB_STATUS_REQUEST, &ctrl);
        }
    }
    else
    {
        /* Set Stall */
        usb_pstd_set_stall_pipe0(p_utr); /* Req Error */
    }

  #else /* defined(USB_CFG_PMSC_USE) */
    usb_instance_ctrl_t ctrl;

    /* Is a request receive target Interface? */
    ctrl.module_number = p_utr->ip;
    ctrl.setup         = *req;         /* Save setup data. */
    ctrl.data_size     = 0;
    ctrl.status        = USB_SETUP_STATUS_ACK;
    ctrl.type          = USB_CLASS_REQUEST;
    usb_set_event(USB_STATUS_REQUEST, &ctrl);
  #endif                               /* defined(USB_CFG_PMSC_USE) */
 #endif                                /* (BSP_CFG_RTOS == 1) */
} /* End of function usb_peri_class_request_rwds */

/******************************************************************************
 * Function Name   : usb_peri_other_request
 * Description     : Processing to notify the reception of the USB request
 * Arguments       : usb_setup_t *req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
void usb_peri_other_request (usb_setup_t * req, usb_utr_t * p_utr)
{
 #if (BSP_CFG_RTOS == 1)
    FSP_PARAMETER_NOT_USED(p_utr);
    usb_peri_class_request_usbx(req);
 #else                                 /* #if (BSP_CFG_RTOS == 1) */
    usb_instance_ctrl_t ctrl;

    ctrl.type          = USB_CLASS_REQUEST;
    ctrl.setup         = *req;         /* Save setup data. */
    ctrl.module_number = p_utr->ip;
    ctrl.data_size     = 0;
    ctrl.status        = USB_SETUP_STATUS_ACK;
    usb_set_event(USB_STATUS_REQUEST, &ctrl);
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
}                                      /* End of function usb_peri_other_request */

/******************************************************************************
 * Function Name   : usb_peri_class_request_wnss
 * Description     : class request (control write nodata status stage)
 * Arguments       : usb_setup_t *req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
void usb_peri_class_request_wnss (usb_setup_t * req, usb_utr_t * p_utr)
{
 #if defined(USB_CFG_PCDC_USE) && defined(USB_CFG_PMSC_USE)
    usb_instance_ctrl_t ctrl;

    /* Is a request receive target Interface? */
    if (USB_INTERFACE == (req->request_type & USB_BMREQUESTTYPERECIP))
    {
  #if (BSP_CFG_RTOS == 1)
        if ((USB_MASS_STORAGE_RESET == (req->request_type & USB_BREQUEST)) ||
            (USB_PCDC_SET_CONTROL_LINE_STATE == (req->request_type & USB_BREQUEST)))
  #else
        if (USB_MASS_STORAGE_RESET == (req->request_type & USB_BREQUEST))
  #endif                                /* (BSP_CFG_RTOS == 1) */
        {
  #if (BSP_CFG_RTOS == 1)
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
            usb_pstd_ctrl_end(USB_CTRL_END, p_utr);

            usb_peri_class_request_usbx(req);
  #else                                /* (BSP_CFG_RTOS == 1) */
            usb_pmsc_mass_strage_reset(req->request_value, req->request_index, req->request_length, p_utr);
  #endif /* (BSP_CFG_RTOS == 1) */
        }
        else
        {
            ctrl.setup         = *req; /* Save setup data. */
            ctrl.module_number = p_utr->ip;
            ctrl.data_size     = 0;
            ctrl.status        = USB_SETUP_STATUS_ACK;
            ctrl.type          = USB_CLASS_REQUEST;
            usb_set_event(USB_STATUS_REQUEST, &ctrl);
        }
    }
    else
    {
        usb_pstd_set_stall_pipe0(p_utr); /* Req Error */
    }

  #if (BSP_CFG_RTOS == 1)
    if ((USB_MASS_STORAGE_RESET != (req->request_type & USB_BREQUEST)) &&
        (USB_PCDC_SET_CONTROL_LINE_STATE != (req->request_type & USB_BREQUEST)))
  #else
    if (USB_MASS_STORAGE_RESET != (req->request_type & USB_BREQUEST))
  #endif                                /* (BSP_CFG_RTOS == 1) */
    {
        usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* End control transfer. */
    }

 #elif defined(USB_CFG_PMSC_USE)
    usb_instance_ctrl_t ctrl;

    /* Is a request receive target Interface? */
    if (USB_INTERFACE == (req->request_type & USB_BMREQUESTTYPERECIP))
    {
        if (USB_MASS_STORAGE_RESET == (req->request_type & USB_BREQUEST))
        {
  #if (BSP_CFG_RTOS == 1)
            usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
            usb_pstd_ctrl_end(USB_CTRL_END, p_utr);

            usb_peri_class_request_usbx(req);
  #else                                /* (BSP_CFG_RTOS == 1) */
            usb_pmsc_mass_strage_reset(req->request_value, req->request_index, req->request_length, p_utr);
  #endif /* (BSP_CFG_RTOS == 1) */
        }
        else
        {
            ctrl.setup         = *req; /* Save setup data. */
            ctrl.module_number = p_utr->ip;
            ctrl.data_size     = 0;
            ctrl.status        = USB_SETUP_STATUS_ACK;
            ctrl.type          = USB_CLASS_REQUEST;
            usb_set_event(USB_STATUS_REQUEST, &ctrl);
        }
    }
    else
    {
        usb_pstd_set_stall_pipe0(p_utr); /* Req Error */
    }

    if (USB_MASS_STORAGE_RESET != (req->request_type & USB_BREQUEST))
    {
        usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* End control transfer. */
    }

 #else /* defined(USB_CFG_PCDC_USE) && defined(USB_CFG_PMSC_USE) */
  #if (BSP_CFG_RTOS != 1)

    /* Is a request receive target Interface? */
    usb_instance_ctrl_t ctrl;
    ctrl.setup         = *req;         /* Save setup data. */
    ctrl.module_number = p_utr->ip;
    ctrl.data_size     = 0;
    ctrl.status        = USB_SETUP_STATUS_ACK;
    ctrl.type          = USB_CLASS_REQUEST;
    usb_set_event(USB_STATUS_REQUEST, &ctrl);
  #else                                                /* #if (BSP_CFG_RTOS != 1) */
    FSP_PARAMETER_NOT_USED(req);
    usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);     /* Set pipe PID_BUF */
  #endif  /* #if (BSP_CFG_RTOS != 1) */
    usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* End control transfer. */

  #if (BSP_CFG_RTOS == 1)
    usb_peri_class_request_usbx(req);
  #endif  /* #if (BSP_CFG_RTOS != 1) */
 #endif                                /* defined(USB_CFG_PCDC_USE) && defined(USB_CFG_PMSC_USE) */
} /* End of function usb_peri_class_request_wnss */

/******************************************************************************
 * Function Name   : usb_peri_class_request_rss
 * Description     : class request (control read status stage)
 * Arguments       : usb_setup_t *req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
void usb_peri_class_request_rss (usb_setup_t * req, usb_utr_t * p_utr)
{
 #if defined(USB_CFG_PMSC_USE)

    /* Is a request receive target Interface? */
    usb_instance_ctrl_t ctrl;

    if (USB_GET_MAX_LUN == (req->request_type & USB_BREQUEST))
    {
        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);
    }
    else
    {
        ctrl.setup = *req;                             /* Save setup data. */
        usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* Set pipe PID_BUF */
        ctrl.module_number = p_utr->ip;
        ctrl.data_size     = 0;
        ctrl.status        = USB_SETUP_STATUS_ACK;
        ctrl.type          = USB_CLASS_REQUEST;
  #if (BSP_CFG_RTOS == 1)
        ctrl.p_data = (void *) tx_thread_identify();
  #elif (BSP_CFG_RTOS == 2)            /* (BSP_CFG_RTOS == 1) */
        ctrl.p_data = (void *) xTaskGetCurrentTaskHandle();
  #endif                               /* (BSP_CFG_RTOS == 1) */
        usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl);
        g_usb_pstd_std_request = USB_NO;
    }

    usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* End control transfer. */
 #else  /* defined(USB_CFG_PMSC_USE) */
    /* Is a request receive target Interface? */
  #if (BSP_CFG_RTOS != 1)
    usb_instance_ctrl_t ctrl;

    ctrl.setup = *req;                             /* Save setup data. */
    usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* Set pipe PID_BUF */
    ctrl.module_number = p_utr->ip;
    ctrl.data_size     = 0;
    ctrl.status        = USB_SETUP_STATUS_ACK;
    ctrl.type          = USB_CLASS_REQUEST;
   #if (BSP_CFG_RTOS == 1)
    ctrl.p_data = (void *) tx_thread_identify();
   #elif (BSP_CFG_RTOS == 2)                           /* (BSP_CFG_RTOS == 1) */
    ctrl.p_data = (void *) xTaskGetCurrentTaskHandle();
   #endif                                              /* (BSP_CFG_RTOS == 1) */
    usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl);
  #else /* #if (BSP_CFG_RTOS != 1) */
    FSP_PARAMETER_NOT_USED(req);
    usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0);     /* Set pipe PID_BUF */
  #endif /* #if (BSP_CFG_RTOS != 1) */
    g_usb_pstd_std_request = USB_NO;

    usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr); /* End control transfer. */
 #endif                                                /* defined(USB_CFG_PMSC_USE) */
} /* End of function usb_peri_class_request_rss */

/******************************************************************************
 * Function Name   : usb_peri_class_request_wss
 * Description     : class request (control write status stage)
 * Arguments       : usb_setup_t *req : Pointer to usb_setup_t structure
 * Return value    : none
 ******************************************************************************/
void usb_peri_class_request_wss (usb_setup_t * req, usb_utr_t * p_utr)
{
 #if (BSP_CFG_RTOS != 1)
    usb_instance_ctrl_t ctrl;

    ctrl.setup = *req;
    usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* Set BUF */
    ctrl.module_number = p_utr->ip;
    ctrl.data_size     = ctrl.setup.request_length - g_usb_pstd_data_cnt[USB_PIPE0];
    ctrl.status        = USB_SETUP_STATUS_ACK;
    ctrl.type          = USB_CLASS_REQUEST;
  #if (BSP_CFG_RTOS == 1)
    ctrl.p_data = (void *) tx_thread_identify();
  #elif (BSP_CFG_RTOS == 2)                        /* (BSP_CFG_RTOS == 1) */
    ctrl.p_data = (void *) xTaskGetCurrentTaskHandle();
  #endif                                           /* (BSP_CFG_RTOS == 1) */
    usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl);
 #else  /*#if (BSP_CFG_RTOS != 1) */
    FSP_PARAMETER_NOT_USED(req);
    usb_cstd_set_buf(p_utr, (uint16_t) USB_PIPE0); /* Set BUF */
 #endif /*#if (BSP_CFG_RTOS != 1) */
    g_usb_pstd_std_request = USB_NO;

    usb_pstd_ctrl_end((uint16_t) USB_CTRL_END, p_utr);
 #if (BSP_CFG_RTOS == 1)
  #if defined(USB_CFG_PAUD_USE) || defined(USB_CFG_DFU_USE)
    usb_peri_usbx_set_control_length(req);
  #endif                               /* #if defined(USB_CFG_PAUD_USE) || defined(USB_CFG_DFU_USE)*/
    usb_peri_class_request_usbx(req);
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
}                                      /* End of function usb_peri_class_request_wss */

 #if USB_CFG_REQUEST == USB_CFG_ENABLE

/******************************************************************************
 * Function Name   : usb_pstd_request_event_set
 * Description     :
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_request_event_set (usb_utr_t * p_utr)
{
    usb_instance_ctrl_t ctrl;

    ctrl.setup.request_type   = g_usb_pstd_req_type;   /* Request type */
    ctrl.setup.request_value  = g_usb_pstd_req_value;  /* Value */
    ctrl.setup.request_index  = g_usb_pstd_req_index;  /* Index */
    ctrl.setup.request_length = g_usb_pstd_req_length; /* Length */
    ctrl.data_size            = 0;
    ctrl.status               = USB_SETUP_STATUS_ACK;
    ctrl.type                 = USB_CLASS_REQUEST;
    ctrl.module_number        = p_utr->ip;
    usb_set_event(USB_STATUS_REQUEST, &ctrl);
}                                      /* End of function usb_pstd_request_event_set */

 #endif /* USB_CFG_REQUEST == USB_CFG_ENABLE */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
