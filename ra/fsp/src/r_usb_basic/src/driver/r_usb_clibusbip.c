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
#include "inc/r_usb_extern.h"
#include "inc/r_usb_basic_define.h"
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
#endif                                 /* #if (BSP_CFG_RTOS != 1) */

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

/******************************************************************************
 * Macro definitions
 *****************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * usb_prv_ns_callback)(usb_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile usb_prv_ns_callback)(usb_callback_args_t * p_args);
#endif

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 * Private global variables and functions
 *****************************************************************************/

fsp_err_t usb_cstd_get_semaphore(usb_instance_ctrl_t * p_ctrl);
fsp_err_t usb_cstd_rel_semaphore(usb_instance_ctrl_t * p_ctrl);

/******************************************************************************
 * Renesas Abstracted Driver API functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_nrdy_enable
 * Description     : Enable NRDY interrupt of the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : none
 ******************************************************************************/
void usb_cstd_nrdy_enable (usb_utr_t * ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Enable NRDY */
    hw_usb_set_nrdyenb(ptr, pipe);
}

/******************************************************************************
 * End of function usb_cstd_nrdy_enable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_get_pid
 * Description     : Fetch specified pipe's PID.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : uint16_t PID-bit status
 ******************************************************************************/
uint16_t usb_cstd_get_pid (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t buf;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL;               /* Error */
    }

    /* PIPE control reg read */
    buf = hw_usb_read_pipectr(ptr, pipe);

    return (uint16_t) (buf & USB_PID);
}

/******************************************************************************
 * End of function usb_cstd_get_pid
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_get_maxpacket_size
 * Description     : Fetch MaxPacketSize of the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : uint16_t MaxPacketSize
 ******************************************************************************/
uint16_t usb_cstd_get_maxpacket_size (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t size;
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL;               /* Error */
    }

    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpmaxp(ptr);
    }
    else
    {
        /* Pipe select */
        hw_usb_write_pipesel(ptr, pipe);
        buffer = hw_usb_read_pipemaxp(ptr);
    }

    /* Max Packet Size */
    size = (uint16_t) (buffer & USB_MXPS);

    return size;
}

/******************************************************************************
 * End of function usb_cstd_get_maxpacket_size
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_get_pipe_dir
 * Description     : Get PIPE DIR
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : uint16_t pipe direction.
 ******************************************************************************/
uint16_t usb_cstd_get_pipe_dir (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL;               /* Error */
    }

    /* Pipe select */
    hw_usb_write_pipesel(ptr, pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg(ptr);

    return (uint16_t) (buffer & USB_DIRFIELD);
}

/******************************************************************************
 * End of function usb_cstd_get_pipe_dir
 ******************************************************************************/

#if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_cstd_get_pipe_type
 * Description     : Fetch and return PIPE TYPE.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : uint16_t pipe type
 ******************************************************************************/
uint16_t usb_cstd_get_pipe_type (usb_utr_t * ptr, uint16_t pipe)
{
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL;               /* Error */
    }

    /* Pipe select */
    hw_usb_write_pipesel(ptr, pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg(ptr);

    return (uint16_t) (buffer & USB_TYPFIELD);
}

/******************************************************************************
 * End of function usb_cstd_get_pipe_type
 ******************************************************************************/
#endif                                 /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_cstd_do_aclrm
 * Description     : Set the ACLRM-bit (Auto Buffer Clear Mode) of the specified
 *               : pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : none
 ******************************************************************************/
void usb_cstd_do_aclrm (usb_utr_t * ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Control ACLRM */
    hw_usb_set_aclrm(ptr, pipe);
    hw_usb_clear_aclrm(ptr, pipe);
}

/******************************************************************************
 * End of function usb_cstd_do_aclrm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_set_buf
 * Description     : Set PID (packet ID) of the specified pipe to BUF.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : none
 ******************************************************************************/
void usb_cstd_set_buf (usb_utr_t * ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* PIPE control reg set */
    hw_usb_set_pid(ptr, pipe, USB_PID_BUF);
}

/******************************************************************************
 * End of function usb_cstd_set_buf
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_clr_stall
 * Description     : Set up to NAK the specified pipe, and clear the STALL-bit set
 *               : to the PID of the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe number.
 * Return value    : none
 * Note            : PID is set to NAK.
 ******************************************************************************/
void usb_cstd_clr_stall (usb_utr_t * ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Set NAK */
    usb_cstd_set_nak(ptr, pipe);

    /* Clear STALL */
    hw_usb_clear_pid(ptr, pipe, USB_PID_STALL);
}

/******************************************************************************
 * End of function usb_cstd_clr_stall
 ******************************************************************************/

#if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_cstd_port_speed
 * Description     : Get USB-speed of the specified port.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * :Return value   : uint16_t  : HSCONNECT, Hi-Speed
 *               :           : FSCONNECT : Full-Speed
 *               :           : LSCONNECT : Low-Speed
 *               :           : NOCONNECT : not connect
 ******************************************************************************/
uint16_t usb_cstd_port_speed (usb_utr_t * ptr)
{
    uint16_t buf;
    uint16_t conn_inf;

    buf = hw_usb_read_dvstctr(ptr);

    /* Reset handshake status get */
    buf = (uint16_t) (buf & USB_RHST);

    switch (buf)
    {
        /* Get port speed */
        case USB_HSMODE:
        {
            conn_inf = USB_HSCONNECT;
            break;
        }

        case USB_FSMODE:
        {
            conn_inf = USB_FSCONNECT;
            break;
        }

        case USB_LSMODE:
        {
            conn_inf = USB_LSCONNECT;
            break;
        }

        case USB_HSPROC:
        {
            conn_inf = USB_NOCONNECT;
            break;
        }

        default:
        {
            conn_inf = USB_NOCONNECT;
            break;
        }
    }

    return conn_inf;
}

/******************************************************************************
 * End of function usb_cstd_port_speed
 ******************************************************************************/
#endif                                 /* #if (USB_UT_MODE == 0) */

#if (!(USB_UT_MODE == 1 && BSP_CFG_RTOS != 0))

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_call_callback
 * Description     : Call callback functiont.
 * Arguments       : usb_instance_ctrl_t   *p_ctrl     : control structure for USB API.
 * Return value    : none
 ******************************************************************************/
static void usb_call_callback (usb_instance_ctrl_t * p_ctrl)
{
    usb_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    usb_callback_args_t * p_args = g_usb_apl_callback_memory[p_ctrl->module_number];
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    *p_args = *p_ctrl;

  #if BSP_TZ_SECURE_BUILD

    /* g_usb_apl_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(g_usb_apl_callback[p_ctrl->module_number]))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        (*g_usb_apl_callback[p_ctrl->module_number])(p_args);
    }
    else
    {
        /* If g_usb_apl_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        usb_prv_ns_callback p_callback = (usb_prv_ns_callback) (g_usb_apl_callback[p_ctrl->module_number]);

        p_callback(p_args);
    }

  #else                                /* BSP_TZ_SECURE_BUILD */
    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */

    // p_ctrl->p_callback(p_args);
    (*g_usb_apl_callback[p_ctrl->module_number])(p_args);
  #endif                               /* BSP_TZ_SECURE_BUILD */
}

 #endif /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_set_event
 * Description     : Set event.
 * Arguments       : uint16_t     event       : event code.
 *               : usb_instance_ctrl_t   *p_ctrl     : control structure for USB API.
 * Return value    : none
 ******************************************************************************/
void usb_set_event (usb_status_t event, usb_instance_ctrl_t * p_ctrl)
{
 #if (BSP_CFG_RTOS != 0)
    static uint16_t count = 0;

    p_ctrl->event           = event;
    g_usb_cstd_event[count] = *p_ctrl;

    switch (event)
    {
        case USB_STATUS_DEFAULT:
        case USB_STATUS_CONFIGURED:
        case USB_STATUS_BC:
        case USB_STATUS_OVERCURRENT:
        case USB_STATUS_NOT_SUPPORT:
        case USB_STATUS_DETACH:
        {
            (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count], (usb_hdl_t) USB_NULL, USB_OFF);
            break;
        }

        case USB_STATUS_REQUEST:
        {
            (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count], (usb_hdl_t) USB_NULL, USB_OFF);
            break;
        }

        case USB_STATUS_SUSPEND:
        case USB_STATUS_RESUME:
        {
            if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
            {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
                (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count],
                                                             g_usb_hstd_sus_res_task_id[p_ctrl->module_number],
                                                             USB_OFF);
  #endif                               /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
            else
            {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count], (usb_hdl_t) USB_NULL, USB_OFF);
  #endif                               /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
            }

            break;
        }

        case USB_STATUS_REQUEST_COMPLETE:
        {
            if (USB_MODE_HOST == g_usb_usbmode[p_ctrl->module_number])
            {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
                (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count], (usb_hdl_t) p_ctrl->p_data,
                                                             USB_OFF);
  #endif                               /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
            else
            {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                if (0 == p_ctrl->setup.request_length)
                {
                    /* Processing for USB request has the no data stage */
                    (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count], (usb_hdl_t) USB_NULL,
                                                                 USB_OFF);
                }
                else
                {
                    /* Processing for USB request has the data state */
                    (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count], (usb_hdl_t) p_ctrl->p_data,
                                                                 USB_OFF);
                }
  #endif                               /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
            }

            break;
        }

            /* UNCRUSTIFY-OFF */
        case USB_STATUS_READ_COMPLETE:
        case USB_STATUS_WRITE_COMPLETE:
  #if defined(USB_CFG_HMSC_USE)
        case USB_STATUS_MSC_CMD_COMPLETE:
  #endif                               /* defined(USB_CFG_HMSC_USE) */
            (*g_usb_apl_callback[p_ctrl->module_number])(&g_usb_cstd_event[count], (usb_hdl_t) p_ctrl->p_data, USB_OFF);
            break;

        default:
            /* Do Nothing */
            break;
    }

    count = (uint16_t) ((count + 1) % USB_EVENT_MAX);
                                       /* UNCRUSTIFY-ON */
 #else                                 /* #if (BSP_CFG_RTOS != 0) */
    g_usb_cstd_event.code[g_usb_cstd_event.write_pointer] = event;
    g_usb_cstd_event.ctrl[g_usb_cstd_event.write_pointer] = *p_ctrl;
    g_usb_cstd_event.write_pointer++;
    if (g_usb_cstd_event.write_pointer >= USB_EVENT_MAX)
    {
        g_usb_cstd_event.write_pointer = 0;
    }

    if (NULL != g_usb_apl_callback[p_ctrl->module_number])
    {
        p_ctrl->event = event;
        usb_call_callback(p_ctrl);
    }
 #endif                                /* #if (BSP_CFG_RTOS != 0) */
    } /* End of function usb_set_event() */

#endif                                 /* #if(!(USB_UT_MODE == 1 && BSP_CFG_RTOS == 2)) */

#if (BSP_CFG_RTOS != 0)

/***************************************************************************//**
 * @brief Getting semaphore processing for the thread safe function
 *
 * @retval FSP_SUCCESS         Success.
 * @retval FSP_ERR_USB_FAILED  Semaphore acquisition failure.
 ******************************************************************************/
fsp_err_t usb_cstd_get_semaphore (usb_instance_ctrl_t * p_ctrl)
{
 #if (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE)
    BaseType_t retval   = pdFAIL;
    uint8_t    usbip_no = p_ctrl->module;

    retval = xSemaphoreTake(g_usb_semaphore_hdl[usbip_no], USB_TMO_VAL);

    if (pdPASS == retval)
    {
        g_usb_cur_task_hdl[usbip_no]     = xTaskGetCurrentTaskHandle();
        g_usb_semaphore_holder[usbip_no] = p_ctrl->address;

        return FSP_SUCCESS;
    }

    return FSP_ERR_USB_FAILED;
 #else                                 /* (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE) */
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_SUCCESS;
 #endif /* (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE) */
}

/******************************************************************************
 * End of function usb_cstd_get_semaphore
 ******************************************************************************/

/***************************************************************************//**
 * @brief Releasing semaphore processing for the thread safe function
 *
 * @retval FSP_SUCCESS         Success.
 * @retval FSP_ERR_USB_FAILED  Semaphore release failure.
 ******************************************************************************/
fsp_err_t usb_cstd_rel_semaphore (usb_instance_ctrl_t * p_ctrl)
{
 #if (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE)
    BaseType_t retval   = pdFAIL;
    uint8_t    usbip_no = p_ctrl->module;

    if ((UBaseType_t) 0 == uxSemaphoreGetCount(g_usb_semaphore_hdl[usbip_no]))
    {
        retval = xSemaphoreGive(g_usb_semaphore_hdl[usbip_no]);
    }

    if (pdPASS == retval)
    {
        g_usb_cur_task_hdl[usbip_no]     = (rtos_task_id_t) USB_NULL;
        g_usb_semaphore_holder[usbip_no] = 0;

        return FSP_SUCCESS;
    }

    return FSP_ERR_USB_FAILED;
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_SUCCESS;
 #endif
}

/******************************************************************************
 * End of function usb_cstd_rel_semaphore
 ******************************************************************************/
#endif                                 /* #if (BSP_CFG_RTOS != 0) */

#if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_cstd_usb_task
 * Description     : USB driver main loop processing.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_cstd_usb_task (void)
{
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
  #if defined(USB_CFG_HMSC_USE)
    do
    {
        usb_cstd_scheduler();                        /* Scheduler */
        if (USB_FLGSET == usb_cstd_check_schedule()) /* Check for any task processing requests flags. */
        {
            /** Use only in non-OS. In RTOS, the kernel will schedule these tasks, no polling. **/
            usb_hstd_hcd_task((void *) 0);           /* HCD Task */
            usb_hstd_mgr_task((void *) 0);           /* MGR Task */
   #if USB_CFG_HUB == USB_CFG_ENABLE
            usb_hhub_task((usb_vp_int_t) 0);         /* HUB Task */
   #endif /* USB_CFG_HUB == USB_CFG_ENABLE */
            usb_class_task();
        }
    }
    /* WAIT_LOOP */
    while (USB_FALSE != g_drive_search_lock);

  #else                                          /* defined(USB_CFG_HMSC_USE) */
    usb_cstd_scheduler();                        /* Scheduler */

    if (USB_FLGSET == usb_cstd_check_schedule()) /* Check for any task processing requests flags. */
    {
        /** Use only in non-OS. In RTOS, the kernel will schedule these tasks, no polling. **/
        usb_hstd_hcd_task((void *) 0);           /* HCD Task */
        usb_hstd_mgr_task((void *) 0);           /* MGR Task */
   #if USB_CFG_HUB == USB_CFG_ENABLE
        usb_hhub_task((usb_vp_int_t) 0);         /* HUB Task */
   #endif /* USB_CFG_HUB == USB_CFG_ENABLE */
   #if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HVND_USE)
        usb_class_task();
   #endif /* defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HVND_USE) */
    }
  #endif                               /* defined(USB_CFG_HMSC_USE) */
 #endif                                /*( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )*/
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_pstd_pcd_task();

  #if defined(USB_CFG_PMSC_USE)
   #if (USB_CFG_RTOS != 1)
    usb_pmsc_task();
   #endif                              /* USB_CFG_RTOS != 1 */
  #endif                               /* defined(USB_CFG_PMSC_USE) */
 #endif                                /*( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )*/
} /* End of function usb_cstd_usb_task() */

/******************************************************************************
 * Function Name   : usb_class_task
 * Description     : Each device class task processing
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_class_task (void)
{
 #if defined(USB_CFG_HMSC_USE)
    usb_utr_t utr;
    uint16_t  addr;

    usb_hmsc_task();                   /* USB Host MSC driver task */
    usb_hmsc_strg_drive_task();        /* HSTRG Task */

    if (USB_FALSE == g_drive_search_lock)
    {
        if (g_drive_search_que_cnt > 0)
        {
            g_drive_search_lock = g_drive_search_que[0];

            utr.ip = USB_IP0;
            if (USBA_ADDRESS_OFFSET == (g_drive_search_lock & USB_IP_MASK))
            {
                utr.ip = USB_IP1;
            }

            addr    = g_drive_search_lock & USB_ADDRESS_MASK;
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip); /* Get the USB IP base address. */

            /* Storage drive search. */
            usb_hmsc_strg_drive_search(&utr, addr, (usb_cb_t) usb_hmsc_drive_complete);
        }
    }
 #endif                                /* defined(USB_CFG_HMSC_USE) */

 #if defined(USB_CFG_HCDC_USE)
    usb_hcdc_task((usb_vp_int_t) 0);   /* USB Host CDC driver task */
 #endif                                /* defined(USB_CFG_HCDC_USE) */

 #if defined(USB_CFG_HHID_USE)
    usb_hhid_task((usb_vp_int_t) 0);   /* USB Host CDC driver task */
 #endif                                /* defined(USB_CFG_HHID_USE) */
} /* End of function usb_class_task */

#endif                                 /*(BSP_CFG_RTOS == 0)*/

/******************************************************************************
 * Function Name   : usb_cstd_remote_wakeup
 * Description     : Remote wakeup
 * Arguments       : usb_utr_t *p_utr : Pointer to usb_utr_t structure.
 * Return value    : uint16_t  USB_ERROR
 ******************************************************************************/
uint16_t usb_cstd_remote_wakeup (usb_utr_t * p_utr)
{
#if (USB_CFG_MODE == USB_CFG_PERI)
    if (USB_TRUE == g_usb_pstd_remote_wakeup)
    {
        /* Support remote wakeup ? */
        usb_pstd_change_device_state(USB_DO_REMOTEWAKEUP, USB_NULL, (usb_cb_t) usb_pstd_dummy_function, p_utr);
    }
    else
    {

        // ret_code = FSP_ERR_USB_FAILED;
        return USB_ERROR;
    }

    return g_usb_pstd_remote_wakeup_state;
#else                                  /* (USB_CFG_MODE == USB_CFG_PERI) */
    FSP_PARAMETER_NOT_USED(p_utr);

    return USB_ERROR;
#endif /* (USB_CFG_MODE == USB_CFG_PERI) */
}                                      /* End of function usb_cstd_remote_wakeup */

#if (BSP_CFG_RTOS == 1)

/******************************************************************************
 * Function Name   : usb_cstd_usbx_callback
 * Description     : The callback function is not used when using USBX.
 *                   Therefore, prepared an empty function.
 * Arguments       : usb_event_info_t *p_api_event :
 *                   usb_hdl_t cur_task            :
 *                   usb_onoff_t usb_state         :
 * Return value    : none
 ******************************************************************************/
void usb_cstd_usbx_callback (usb_event_info_t * p_api_event, usb_hdl_t cur_task, usb_onoff_t usb_state)
{
    FSP_PARAMETER_NOT_USED(p_api_event);
    FSP_PARAMETER_NOT_USED(cur_task);
    FSP_PARAMETER_NOT_USED(usb_state);
}

/******************************************************************************
 * End of function usb_cstd_usbx_callback
 ******************************************************************************/
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
