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

#if (BSP_CFG_RTOS == 1)
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_api.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_system.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_utility.h"
 #include "../../../../../microsoft/azure-rtos/usbx/common/core/inc/ux_device_stack.h"
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
 #if USB_CFG_BC == USB_CFG_ENABLE
extern uint16_t g_usb_bc_detect;
 #endif                                /* USB_CFG_BC == USB_CFG_ENABLE */

 #if (BSP_CFG_RTOS == 1)
extern TX_SEMAPHORE g_usb_peri_usbx_sem[USB_MAX_PIPE_NO + 1];
extern bool         g_usb_peri_usbx_is_detach[USB_MAX_PIPE_NO + 1];
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Renesas Abstracted Peripheral signal control functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_bus_reset
 * Description     : A USB bus reset was issued by the host. Execute relevant pro-
 *               : cessing.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_bus_reset (usb_utr_t * p_utr)
{
    uint16_t connect_info;

    /* Bus Reset */
    usb_pstd_busreset_function();

    /* Memory clear */
    usb_pstd_clr_mem();
    connect_info = usb_cstd_port_speed(p_utr);

 #if (BSP_CFG_RTOS == 1)
    switch (connect_info)
    {
        case USB_HSCONNECT:
        {
            _ux_system_slave->ux_system_slave_speed = (uint32_t) UX_HIGH_SPEED_DEVICE;
            break;
        }

        case USB_FSCONNECT:
        {
            _ux_system_slave->ux_system_slave_speed = (uint32_t) UX_FULL_SPEED_DEVICE;
            break;
        }

        case USB_LSCONNECT:
        {
            _ux_system_slave->ux_system_slave_speed = (uint32_t) UX_LOW_SPEED_DEVICE;
            break;
        }

        default:
        {
            break;
        }
    }
 #endif                                /* #if (BSP_CFG_RTOS == 1) */

    /* Callback */
    if (USB_NULL != g_usb_pstd_driver.devdefault)
    {
 #if USB_CFG_BC == USB_CFG_ENABLE
        (*g_usb_pstd_driver.devdefault)(p_utr, connect_info, g_usb_bc_detect);
 #else                                 /* USB_CFG_BC == USB_CFG_ENABLE */
        (*g_usb_pstd_driver.devdefault)(p_utr, connect_info, USB_NULL);
 #endif /* USB_CFG_BC == USB_CFG_ENABLE */

 #if (BSP_CFG_RTOS == 1)
        usb_peri_usbx_initialize_complete();
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
    }

    /* DCP configuration register  (0x5C) */
    hw_usb_write_dcpcfg(p_utr, 0);

    /* DCP maxpacket size register (0x5E) */
    hw_usb_write_dcpmxps(p_utr, g_usb_pstd_driver.p_devicetbl[USB_DEV_MAX_PKT_SIZE]);
}

/******************************************************************************
 * End of function usb_pstd_bus_reset
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_attach_process
 * Description     : USB attach setting.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_attach_process (usb_utr_t * p_utr)
{
    usb_cpu_delay_xms((uint16_t) 10);
 #if USB_CFG_BC == USB_CFG_ENABLE
    usb_pstd_bc_detect_process(p_utr);
 #endif                                /* USB_CFG_BC == USB_CFG_ENABLE */
    hw_usb_pset_dprpu(p_utr->ip);
}

/******************************************************************************
 * End of function usb_pstd_attach_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_detach_process
 * Description     : Initialize USB registers for detaching, and call the callback
 *               : function that completes the detach.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_detach_process (usb_utr_t * p_utr)
{
    uint16_t i;

 #if defined(USB_HIGH_SPEED_MODULE)
    hw_usb_clear_cnen(p_utr);
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
    /* Pull-up disable */
    hw_usb_pclear_dprpu(p_utr->ip);

    /* Configuration number */
    g_usb_pstd_config_num = 0;

    /* Remote wakeup enable flag */
    g_usb_pstd_remote_wakeup = USB_FALSE;

    /* WAIT_LOOP */
    for (i = USB_MIN_PIPE_NO; i < (USB_MAX_PIPE_NO + 1); i++)
    {
        if (USB_TRUE == g_usb_pipe_table[p_utr->ip][i].use_flag)
        {
            usb_pstd_forced_termination(i, (uint16_t) USB_DATA_STOP, p_utr);
            usb_cstd_clr_pipe_cnfg(p_utr, i);
 #if (BSP_CFG_RTOS == 1)
            g_usb_peri_usbx_is_detach[i] = USB_YES;
            tx_semaphore_put(&g_usb_peri_usbx_sem[i]);
            tx_semaphore_delete(&g_usb_peri_usbx_sem[i]);
 #endif                                /* #if (BSP_CFG_RTOS == 1) */
        }
    }

    /* Callback */
    if (USB_NULL != g_usb_pstd_driver.devdetach)
    {
        (*g_usb_pstd_driver.devdetach)(p_utr, USB_POWERED, USB_NULL);
    }
}

/******************************************************************************
 * End of function usb_pstd_detach_process
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_suspend_process
 * Description     : Perform a USB peripheral suspend.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_suspend_process (usb_utr_t * p_utr)
{
    uint16_t intsts0;
    uint16_t buf;

    /* Resume interrupt enable */
    hw_usb_pset_enb_rsme(p_utr->ip);

    intsts0 = hw_usb_read_intsts(p_utr->ip);
    buf     = hw_usb_read_syssts(p_utr);
    if (((uint16_t) 0 != (intsts0 & USB_DS_SUSP)) && (USB_FS_JSTS == (buf & USB_LNST)))
    {
        /* Suspend */
        usb_pstd_stop_clock(p_utr->ip);
        usb_pstd_suspend_function();

        /* Callback */
        if (USB_NULL != g_usb_pstd_driver.devsuspend)
        {
            (*g_usb_pstd_driver.devsuspend)(p_utr, g_usb_pstd_remote_wakeup, USB_NULL);
        }
    }

    /* --- SUSPEND -> RESUME --- */
    else
    {
        /* RESM status clear */
        hw_usb_pclear_sts_resm(p_utr->ip);

        /* RESM interrupt disable */
        hw_usb_pclear_enb_rsme(p_utr->ip);
    }
}

/******************************************************************************
 * End of function usb_pstd_suspend_process
 ******************************************************************************/
#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
