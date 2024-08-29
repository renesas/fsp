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

#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"          /* USB register access function */
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HCDC_USE)
  #include "r_usb_hcdc_api.h"
  #include "r_usb_hcdc_driver.h"

 #endif                                /* defined(USB_CFG_HCDC_USE) */

 #if defined(USB_CFG_HMSC_USE)
  #include "r_usb_hmsc_api.h"

 #endif                                /* defined(USB_CFG_HMSC_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#if (BSP_CFG_RTOS != 1)
 #if defined(USB_CFG_HHID_USE)
  #include "r_usb_hhid_api.h"
 #endif                                /* defined(USB_CFG_HHID_USE) */
#endif /* #if (BSP_CFG_RTOS != 1) */

#define USB_VALUE_100    (100)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint16_t g_usb_cstd_driver_open = USB_FALSE;

/******************************************************************************
 * Renesas Abstracted Host Standard functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_bchg0function
 * Description     : Execute the process appropriate to the status of the connected
 *               : USB device when a BCHG interrupt occurred.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_bchg0function (usb_utr_t * ptr)
{
    uint16_t buf;
    uint16_t connect_inf;

    /* SUSPENDED check */
    if (USB_SUSPENDED == g_usb_hstd_remort_port[ptr->ip])
    {
        /* Device State Control Register - Resume enable check */
        buf = hw_usb_read_dvstctr(ptr);

        if (USB_RESUME == (uint16_t) (buf & USB_RESUME))
        {
            USB_PRINTF0("remote wake up port0\n");
            g_usb_hstd_remort_port[ptr->ip] = USB_DEFAULT;

            /* Change device state to resume */
            usb_hstd_device_resume(ptr, USB_DEVICEADDR);
        }
        else
        {
            /* Decide USB Line state (ATTACH) */
            connect_inf = usb_hstd_chk_attach(ptr);
            if (USB_DETACH == connect_inf)
            {
                g_usb_hstd_remort_port[ptr->ip] = USB_DEFAULT;

                /* USB detach process */
                usb_hstd_detach_process(ptr);
            }
            else
            {
                /* Enable port BCHG interrupt */
                usb_hstd_bchg_enable(ptr);

                /* Check clock */
                usb_hstd_chk_clk(ptr, (uint16_t) USB_SUSPENDED);
            }
        }
    }
    else
    {
        /* USB detach process */
        usb_hstd_detach_process(ptr);
    }
}

/******************************************************************************
 * End of function usb_hstd_bchg0function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_ls_connect_function
 * Description     : Low-speed device connect.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_ls_connect_function (usb_utr_t * ptr)
{
    (*g_usb_hstd_enumaration_process[0])(ptr, (uint16_t) USB_DEVICE_0, (uint16_t) 0);
}

/******************************************************************************
 * End of function usb_hstd_ls_connect_function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_attach_function
 * Description     : Device attach.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_hstd_attach_function (void)
{
    /* 100ms wait */
    usb_cpu_delay_xms((uint16_t) USB_VALUE_100);
}

/******************************************************************************
 * End of function usb_hstd_attach_function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_ovrcr0function
 * Description     : Set USB registers as required due to an OVRCR (over-current)
 *               : interrupt, and notify the MGR (manager) task about this.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_ovrcr0function (usb_utr_t * ptr)
{
    /* Over-current bit check */
    USB_PRINTF0(" OVCR int port0\n");

    /* OVRCR interrupt disable */
    /* Notification over current */
    usb_hstd_ovcr_notifiation(ptr);
}

/******************************************************************************
 * End of function usb_hstd_ovrcr0function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hdriver_init
 * Description     : USB Host driver initialization
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_hdriver_init (usb_utr_t * ptr)
{
    uint16_t i;

    if (USB_FALSE == g_usb_cstd_driver_open)
    {
        usb_cstd_sche_init();                      /* Scheduler init */
 #if (BSP_CFG_RTOS == 0)
        g_usb_cstd_event.write_pointer = USB_NULL; /* Write pointer */
        g_usb_cstd_event.read_pointer  = USB_NULL; /* Read pointer */
 #endif /* (BSP_CFG_RTOS == 0) */

        /* WAIT_LOOP */
        for (i = 0; i < USB_EVENT_MAX; i++)
        {
 #if (BSP_CFG_RTOS != 0)
            g_usb_cstd_event[i].event          = USB_STATUS_NONE;
            g_usb_cstd_event[i].device_address = USB_NULL;
 #else                                 /* (BSP_CFG_RTOS != 0) */
            g_usb_cstd_event.code[i]                = USB_STATUS_NONE;
            g_usb_cstd_event.ctrl[i].device_address = USB_NULL;
 #endif /* (BSP_CFG_RTOS != 0) */
        }

        g_usb_cstd_driver_open = USB_TRUE;
    }

    usb_hstd_init_usb_message(ptr);    /* USB interrupt message initialize */

    usb_hstd_mgr_open(ptr);            /* Manager open */
    usb_hstd_hcd_open(ptr);            /* Hcd open */
 #if (BSP_CFG_RTOS == 1)
    usb_host_registration(ptr);        /* Class Registration */
 #else
  #if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HVND_USE)
    usb_class_driver_start(ptr);       /* Init host class driver task. */
    usb_host_registration(ptr);        /* Class Registration */
  #endif /* defined(USB_CFG_HCDC_USE)||defined(USB_CFG_HHID_USE)||defined(USB_CFG_HMSC_USE)||defined(USB_CFG_HVND_USE) */
 #endif
} /* End of function usb_hdriver_init() */

 #if (BSP_CFG_RTOS != 1)

/******************************************************************************
 * Function Name   : usb_class_driver_start
 * Description     : Init host class driver task.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void usb_class_driver_start (usb_utr_t * ptr)
{
    (void) ptr;
  #if defined(USB_CFG_HCDC_USE)
    usb_hcdc_driver_start(ptr);
  #endif                               /* defined(USB_CFG_HCDC_USE) */
  #if defined(USB_CFG_HMSC_USE)
    usb_hmsc_driver_start(ptr->ip);
    usb_hmsc_storage_driver_start(ptr->ip);
  #endif                               /* defined(USB_CFG_HMSC_USE) */
  #if defined(USB_CFG_HHID_USE)
    usb_hhid_driver_start(ptr);
  #endif                               /* defined(USB_CFG_HHID_USE) */
} /* End of function usb_class_driver_start() */

 #endif /*  #if (BSP_CFG_RTOS != 1) */

 #if (BSP_CFG_RTOS != 0)

/******************************************************************************
 * Function Name   : class_trans_result
 * Description     : Send a message to notify the result of the class request.
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t data1
 *                 uint16_t data2
 * Return value    : none
 ******************************************************************************/
void class_trans_result (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_er_t err;

    (void) data1;
    (void) data2;

    /* Send an internal message */
    err = USB_SND_MSG(USB_CLS_MBX, (usb_msg_t *) ptr);
    if (USB_OK != err)
    {
        USB_PRINTF1("### class_trans_result sends message error (%ld)\n", err);
    }
}                                      /* End of function class_trans_result() */

/******************************************************************************
 * Function Name   : class_trans_wait_tmo
 * Description     : Receive the result of the class request with a timeout.
 * Argument        : usb_utr_t *ptr   : USB system internal structure. Selects channel.
 *                 uint16_t tmo     : Time-out value.
 * Return value    : USB_OK/USB_ERROR
 ******************************************************************************/
uint16_t class_trans_wait_tmo (usb_utr_t * ptr, uint16_t tmo)
{
    usb_utr_t * mess;
    usb_er_t    err;
    uint16_t    result;

    (void) *ptr;

    /* Receive message with time out */
    err = USB_TRCV_MSG(USB_CLS_MBX, (usb_msg_t **) &mess, (usb_tm_t) tmo);
    if (USB_OK != err)
    {
        USB_PRINTF1("### class_trans_wait_tmo receives message error (%ld)\n", err);

        return USB_ERROR;
    }

    /* Check the status of transfer */
    if (USB_DATA_TMO == (mess->status))
    {
        USB_PRINTF0("*** Standard Request Timeout error !\n");
        result = USB_ERROR;
    }
    else if (USB_DATA_STALL == (mess->status))
    {
        USB_PRINTF0("*** Standard Request STALL !\n");
        result = USB_ERROR;
    }
    else if (USB_CTRL_END != (mess->status))
    {
        USB_PRINTF0("*** Standard Request error !\n");
        result = USB_ERROR;
    }
    else
    {
        result = USB_OK;
    }

    return result;
}                                      /* End of function class_trans_wait_tmo() */

 #endif /* (BSP_CFG_RTOS != 0) */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
