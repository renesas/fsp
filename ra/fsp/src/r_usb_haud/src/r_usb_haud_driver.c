/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <string.h>

#include <r_usb_basic.h>
#include "r_usb_basic_api.h"
#include "../../../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../../../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../../../r_usb_basic/src/hw/inc/r_usb_bitdefine.h"
#include "r_usb_haud_api.h"
#include "inc/r_usb_haud_driver.h"

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

static void usb_haud_init(usb_utr_t * ptr, uint16_t data1, uint16_t data2);

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

const uint16_t g_usb_haud_device_tpl[] =
{
    USB_CFG_TPLCNT,                    /* Number of tpl table */
    0,                                 /* Reserved */
    USB_CFG_TPL                        /* Vendor ID, Product ID */
};

uint8_t * g_p_usb_haud_device_table[USB_NUM_USBIP];
uint8_t * g_p_usb_haud_config_table[USB_NUM_USBIP];
uint8_t * g_p_usb_haud_interface_table[USB_NUM_USBIP];
uint16_t  g_usb_haud_speed[USB_NUM_USBIP];
uint16_t  g_usb_haud_devaddr[USB_NUM_USBIP];

#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern const uint16_t USB_CFG_TPL_TABLE[];
#endif                                 /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Renesas USB Host Audio Driver functions
 ******************************************************************************/

#if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_haud_task
 * Description     : CDC Host task
 * Argument        : stacd    : Task Start Code
 * Return          : none
 ******************************************************************************/
void usb_haud_task (usb_vp_int_t stacd)
{
    (void) stacd;

    /* Do nothing */
}

/******************************************************************************
 * End of function usb_haud_task
 ******************************************************************************/
#endif                                 /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_haud_configured
 * Description     : Callback function for CDC device configuered
 * Argument        : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *                 : uint16_t     devadr  : Device Adrress
 *                 : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_haud_configured (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) data2;

    ctrl.module_number  = ptr->ip;               /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    ctrl.type           = (usb_class_t) USB_CLASS_HAUD;
    usb_set_event(USB_STATUS_CONFIGURED, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_haud_configured
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_haud_detach
 * Description     : Callback function for CDC device detach
 * Argument        : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *                 : uint16_t     devadr  : Device Adrress
 *                 : uint16_t     data2   : Not used
 * Return value    : none
 ******************************************************************************/
void usb_haud_detach (usb_utr_t * ptr, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) data2;
    usb_hstd_clr_pipe_table(ptr->ip, devadr);
    ctrl.module_number  = ptr->ip;           /* Module number setting */
    ctrl.device_address = (uint8_t) devadr;
    ctrl.type           = (usb_class_t) USB_CLASS_HAUD;
    usb_set_event(USB_STATUS_DETACH, &ctrl); /* Set Event()  */

    g_usb_haud_speed[ptr->ip]             = 0;
    g_usb_haud_devaddr[ptr->ip]           = 0;
    g_p_usb_haud_device_table[ptr->ip]    = 0;
    g_p_usb_haud_config_table[ptr->ip]    = 0;
    g_p_usb_haud_interface_table[ptr->ip] = 0;
    g_usb_haud_iso_in_pipe[ptr->ip]       = 0;
    g_usb_haud_iso_out_pipe[ptr->ip]      = 0;
}

/******************************************************************************
 * End of function usb_haud_detach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_haud_read_complete
 * Description     : CallBack Function
 * Argument        : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *                 : uint16_t     data1   : Not used
 *                 : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_haud_read_complete (usb_utr_t * mess, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) devadr;
    (void) data2;

    ctrl.module_number = mess->ip;                /* Module number setting */
    ctrl.pipe          = (uint8_t) mess->keyword; /* Pipe number setting */
    if (g_usb_haud_iso_in_pipe[ctrl.module_number] == ctrl.pipe)
    {
        ctrl.type = USB_CLASS_HAUD;
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
 * End of function usb_haud_read_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_haud_write_complete
 * Description     : CallBack Function
 * Argument        : usb_utr_t    *mess   : Pointer to usb_utr_t structure.
 *                 : uint16_t     data1   : Not used
 *                 : uint16_t     data2   : Not used
 * Return          : none
 ******************************************************************************/
void usb_haud_write_complete (usb_utr_t * mess, uint16_t devadr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) devadr;
    (void) data2;

    ctrl.module_number = mess->ip;                /* Module number setting */
    ctrl.pipe          = (uint8_t) mess->keyword; /* Pipe number setting */
    ctrl.type          = USB_CLASS_HAUD;          /* Audio class  */

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
 * End of function usb_haud_write_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_haud_registration
 * Description     : registration of Communications Devices class Driver
 * Argument        : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_haud_registration (usb_utr_t * ptr)
{
    usb_hcdreg_t driver;

    /* Driver registration */
    driver.ifclass = (uint16_t) USB_IFCLS_AUD; /* Audio Interface */

#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    driver.p_tpl = (uint16_t *) USB_CFG_TPL_TABLE;
#else /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.p_tpl = (uint16_t *) &g_usb_haud_device_tpl;         /* Target peripheral list */
#endif /* #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
    driver.classinit  = (usb_cb_t) &usb_haud_init;              /* Driver init */
    driver.classcheck = (usb_cb_check_t) &usb_haud_class_check; /* Driver check */
    driver.devconfig  = (usb_cb_t) &usb_haud_configured;        /* Device configuered */
    driver.devdetach  = (usb_cb_t) &usb_haud_detach;            /* Device detach */
    driver.devsuspend = (usb_cb_t) &usb_hstd_dummy_function;    /* Device suspend */
    driver.devresume  = (usb_cb_t) &usb_hstd_dummy_function;    /* Device resume */

    usb_hstd_driver_registration(ptr, &driver);                 /* Host Audio class driver registration. */
}

/******************************************************************************
 * End of function usb_haud_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_haud_init
 * Description     : Initialize of Host Audio driver.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *                 : uint16_t     data1   : not use
 *                 : uint16_t     data2   : not use
 * Return value    : none
 ******************************************************************************/
static void usb_haud_init (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    static uint8_t init = 0;

    (void) data1;
    (void) data2;

    if (0 == (init & (1 << ptr->ip)))
    {
        g_usb_haud_speed[ptr->ip]             = 0;
        g_usb_haud_devaddr[ptr->ip]           = 0;
        g_p_usb_haud_device_table[ptr->ip]    = 0;
        g_p_usb_haud_config_table[ptr->ip]    = 0;
        g_p_usb_haud_interface_table[ptr->ip] = 0;

        init = init | (uint8_t) (1 << ptr->ip);
    }
}

/******************************************************************************
 * End of function usb_haud_init
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_haud_class_check
 * Description     : class check.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *                 : uint16_t     **table : Pointer to data table.
 * Return          : none
 ******************************************************************************/
void usb_haud_class_check (usb_utr_t * ptr, uint16_t ** table)
{
    g_p_usb_haud_device_table[ptr->ip]    = (uint8_t *) (table[0]); /* Set device descriptor address */
    g_p_usb_haud_config_table[ptr->ip]    = (uint8_t *) (table[1]); /* Set configuration descriptor address */
    g_p_usb_haud_interface_table[ptr->ip] = (uint8_t *) (table[2]); /* Set interface descriptor address */
    g_usb_haud_speed[ptr->ip]             = *table[6];              /* Set device connect speed */
    g_usb_haud_devaddr[ptr->ip]           = *table[7];              /* Set device address */

    *table[3] = USB_OK;                                             /* Set class check done  */
}

/******************************************************************************
 * End of function usb_haud_class_check()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_haud_driver_start
 * Description     : USB host Initialize process
 * Arguments       : none
 * Return          : none
 ******************************************************************************/
void usb_haud_driver_start (usb_utr_t * ptr)
{
    static uint8_t is_init = USB_NO;

    g_usb_haud_speed[ptr->ip]             = 0;
    g_usb_haud_devaddr[ptr->ip]           = 0;
    g_p_usb_haud_device_table[ptr->ip]    = 0;
    g_p_usb_haud_config_table[ptr->ip]    = 0;
    g_p_usb_haud_interface_table[ptr->ip] = 0;

    if (USB_NO == is_init)
    {
        /* Set host Audio Task priority */
#if (BSP_CFG_RTOS == 0)
        usb_cstd_set_task_pri(USB_HAUD_TSK, USB_PRI_4);
#endif                                 /* (BSP_CFG_RTOS == 0) */
        is_init = USB_YES;
    }
}

/******************************************************************************
 * End of function usb_haud_driver_start()
 ******************************************************************************/

/******************************************************************************
 * End  Of File
 ******************************************************************************/
