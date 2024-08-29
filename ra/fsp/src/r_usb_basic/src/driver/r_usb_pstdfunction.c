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

#if (BSP_CFG_RTOS == 1)
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_api.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_system.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_utility.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_device_stack.h"
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
 #define NUM_STRING_DESC    (32)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 1)
extern uint8_t g_usb_peri_usbx_is_configured[USB_NUM_USBIP];
 #endif                                /* (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 1)
static uint8_t * g_p_usbx_string_table[NUM_STRING_DESC];
usb_descriptor_t g_usbx_descriptor;

void usb_pstd_ux_descriptor_to_basic(usb_cfg_t * p_cfg);

 #endif                                /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Renesas Abstracted Peripheral standard function functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_set_feature_function
 * Description     : Process a SET_FEATURE request.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_set_feature_function (usb_utr_t * p_utr)
{
    /* Request error */
    usb_pstd_set_stall_pipe0(p_utr);
}

/******************************************************************************
 * End of function usb_pstd_set_feature_function
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_pstd_chk_vbsts
 * Description     : Return the VBUS status.
 * Arguments       : none
 * Return          : uint16_t connection status(ATTACH/DETACH)
 ******************************************************************************/
uint16_t usb_pstd_chk_vbsts (uint8_t usb_ip)
{
    uint16_t buf1;
    uint16_t buf2;
    uint16_t buf3;
    uint16_t connect_info;

    /* VBUS chattering cut */
    /* WAIT_LOOP */
    do
    {
        buf1 = hw_usb_read_intsts(usb_ip);
        usb_cpu_delay_1us((uint16_t) 10);
        buf2 = hw_usb_read_intsts(usb_ip);
        usb_cpu_delay_1us((uint16_t) 10);
        buf3 = hw_usb_read_intsts(usb_ip);
    } while (((buf1 & USB_VBSTS) != (buf2 & USB_VBSTS)) || ((buf2 & USB_VBSTS) != (buf3 & USB_VBSTS)));

    /* VBUS status judge */
    if ((uint16_t) 0 != (buf1 & USB_VBSTS))
    {
        /* Attach */
        connect_info = USB_ATTACH;
    }
    else
    {
        /* Detach */
        connect_info = USB_DETACH;
    }

    return connect_info;
}

/******************************************************************************
 * End of function usb_pstd_chk_vbsts
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_pstd_busreset_function
 * Description     : Processing for USB bus reset detection.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_busreset_function (void)
{
    /* Non processing. */
}

/******************************************************************************
 * End of function usb_pstd_busreset_function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_suspend_function
 * Description     : Processing for suspend signal detection.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_suspend_function (void)
{
    /* Non processing. */
}

/******************************************************************************
 * End of function usb_pstd_suspend_function
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 1)

/******************************************************************************
 * Function Name   : usb_pstd_ux_descriptor_to_basic
 * Description     : conversion from USBX descriptor to USB basic descriptor
 * Arguments       : p_cfg  : Pointer to USB basic configuration structure
 * Return value    : none
 ******************************************************************************/
void usb_pstd_ux_descriptor_to_basic (usb_cfg_t * p_cfg)
{
    uint8_t * start_address;
    uint8_t * end_address;
    uint8_t * p;
    uint8_t   index;
    uint8_t   num_string = 0;
    uint32_t  length;

    /* Check the speed and set the correct descriptor.  */
    if (USB_SPEED_FS == p_cfg->usb_speed)
    {
        start_address = (uint8_t *) (_ux_system_slave->ux_system_slave_device_framework_full_speed);
        length        = _ux_system_slave->ux_system_slave_device_framework_length_full_speed;
    }
    else
    {
        start_address = (uint8_t *) (_ux_system_slave->ux_system_slave_device_framework_high_speed);
        length        = _ux_system_slave->ux_system_slave_device_framework_length_high_speed;
    }

    end_address = (start_address + length);

    p = start_address;
    while (p < end_address)
    {
        switch (*(p + 1))
        {
            case USB_DT_DEVICE:
            {
                p_cfg->p_usb_reg->p_device = p;
                break;
            }

            case USB_DT_CONFIGURATION:
            {
                if (USB_SPEED_FS == p_cfg->usb_speed)
                {
                    p_cfg->p_usb_reg->p_config_f = p;
                }
                else
                {
                    p_cfg->p_usb_reg->p_config_h = p;
                }

                break;
            }

            case USB_SOFT_CHANGE:
            {
                if (USB_SPEED_FS == p_cfg->usb_speed)
                {
                    p_cfg->p_usb_reg->p_config_f = p;
                }
                else
                {
                    p_cfg->p_usb_reg->p_config_h = p;
                }

                break;
            }

            case USB_DT_OTHER_SPEED_CONF:
            {
                if (USB_SPEED_FS == p_cfg->usb_speed)
                {
                    p_cfg->p_usb_reg->p_config_h = p;
                }
                else
                {
                    p_cfg->p_usb_reg->p_config_f = p;
                }

                break;
            }

            case USB_DT_DEVICE_QUALIFIER:
            {
                p_cfg->p_usb_reg->p_qualifier = p;
                break;
            }

            default:
            {
                break;
            }
        }

        length = *p;
        p      = p + length;
    }

    if (USB_SPEED_HS == p_cfg->usb_speed)
    {
        start_address = (uint8_t *) (_ux_system_slave->ux_system_slave_device_framework_full_speed);
        length        = _ux_system_slave->ux_system_slave_device_framework_length_full_speed;

        end_address = (start_address + length);

        p = start_address;
        if (USB_NULL != p)
        {
            while (p < end_address)
            {
                if ((USB_DT_OTHER_SPEED_CONF == *(p + 1)) || (USB_SOFT_CHANGE == *(p + 1)))
                {
                    p_cfg->p_usb_reg->p_config_f = p;
                    break;
                }

                length = *p;
                p      = p + length;
            }
        }
    }

    if (USB_NULL != _ux_system_slave->ux_system_slave_language_id_framework)
    {
        g_p_usbx_string_table[0] = _ux_system_slave->ux_system_slave_language_id_framework;
    }

    if (USB_NULL != _ux_system_slave->ux_system_slave_string_framework)
    {
        start_address = (uint8_t *) (_ux_system_slave->ux_system_slave_string_framework);
        length        = (uint16_t) (_ux_system_slave->ux_system_slave_string_framework_length);
        end_address   = (start_address + length);

        p = start_address;
        while (p < end_address)
        {
            index = *(p + 2);
            g_p_usbx_string_table[index] = p;
            length = *(p + 3);
            num_string++;
            p = p + length + 4;
        }
    }

    p_cfg->p_usb_reg->p_string   = g_p_usbx_string_table;
    p_cfg->p_usb_reg->num_string = (uint8_t) (num_string + 1);
}                                      /* End of function usb_pdriver_init() */

 #endif /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Function Name   : usb_pdriver_init
 * Description     :
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pdriver_init (usb_instance_ctrl_t * ctrl, usb_cfg_t const * const cfg)
{
    uint16_t i;

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
 #else                                 /*(BSP_CFG_RTOS == 0)*/
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

 #if (BSP_CFG_RTOS == 1)
    {
        usb_cfg_t cfg_usbx;
        cfg_usbx           = *cfg;
        cfg_usbx.p_usb_reg = &g_usbx_descriptor;
        usb_pstd_ux_descriptor_to_basic(&cfg_usbx);
        usb_peri_registration(ctrl, &cfg_usbx);

        g_usb_peri_usbx_is_configured[cfg->module_number] = USB_NO;
    }
 #else                                 /* #if (BSP_CFG_RTOS == 1) */
    usb_peri_registration(ctrl, cfg);
 #endif /* #if (BSP_CFG_RTOS == 1) */
}                                      /* End of function usb_pdriver_init() */

#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
