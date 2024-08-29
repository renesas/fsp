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

#if defined(USB_CFG_HMSC_USE)
 #if (BSP_CFG_RTOS != 1)
  #include "r_usb_hmsc_api.h"
 #endif                                /* #if (BSP_CFG_RTOS != 1) */
#endif                                 /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_HCDC_USE)
 #if (BSP_CFG_RTOS != 1)
  #include "r_usb_hcdc_driver.h"
 #endif                                /* #if (BSP_CFG_RTOS != 1) */
#endif                                 /* defined(USB_CFG_HCDC_USE) */

#if defined(USB_CFG_HHID_USE)
 #if (BSP_CFG_RTOS != 1)
  #include "r_usb_hhid.h"
 #endif                                /* #if (BSP_CFG_RTOS != 1) */
#endif                                 /* defined(USB_CFG_HHID_USE) */

#if (BSP_CFG_RTOS != 0)
 #include "inc/r_usb_cstd_rtos.h"

/******************************************************************************
 * Macro definitions
 *****************************************************************************/
 #define USB_TMO_VAL    (3000)

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 1)
TX_SEMAPHORE g_usb_peri_usbx_sem[USB_MAX_PIPE_NO + 1];
  #if defined(USB_CFG_OTG_USE)
TX_TIMER g_usb_otg_detach_timer;
TX_TIMER g_usb_otg_chattering_timer;
TX_TIMER g_usb_otg_hnp_timer;
   #if USB_NUM_USBIP == 2
TX_TIMER g_usb2_otg_detach_timer;
   #endif                              /* USB_NUM_USBIP == 2 */
  #endif                               /* defined(USB_CFG_OTG_USE) */

 #endif                                /* #if (BSP_CFG_RTOS == 1) */

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/** Declare a task handler for the created tasks. **/
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
rtos_task_id_t        g_hcd_tsk_hdl;
static rtos_task_id_t g_mgr_tsk_hdl;
  #if (BSP_CFG_RTOS != 1)
   #if USB_CFG_HUB == USB_CFG_ENABLE
static rtos_task_id_t g_hub_tsk_hdl;
   #endif                              /* USB_CFG_HUB == USB_CFG_ENABLE */
  #endif                               /* BSP_CFG_RTOS != 1 */
 #endif                                /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static rtos_task_id_t g_pcd_tsk_hdl;
 #endif                                /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

 #if defined(USB_CFG_PMSC_USE)
  #if (BSP_CFG_RTOS == 2)
static rtos_task_id_t g_pmsc_tsk_hdl;
  #endif                               /* (BSP_CFG_RTOS == 2) */
 #endif                                /* defined(USB_CFG_PMSC_USE) */

 #if defined(USB_CFG_HMSC_USE)
rtos_sem_id_t SemaphoreHandleRead;
 #endif                                /* defined(USB_CFG_HMSC_USE) */

/** Declare a mailbox handler for the created tasks **/
static rtos_mbx_id_t g_hcd_mbx_hdl;
static rtos_mbx_id_t g_mgr_mbx_hdl;
static rtos_mbx_id_t g_hub_mbx_hdl;

static rtos_mbx_id_t g_pcd_mbx_hdl;
static rtos_mbx_id_t g_cls_mbx_hdl;
static rtos_mbx_id_t g_hmsc_mbx_hdl;
static rtos_mbx_id_t g_hmsc_req_mbx_hdl;
static rtos_mbx_id_t g_hcdc_mbx_hdl;
static rtos_mbx_id_t g_hhid_mbx_hdl;
static rtos_mbx_id_t g_pmsc_mbx_hdl;
static rtos_mbx_id_t g_hprn_mbx_hdl;

static rtos_mbx_id_t g_pipe0_hdl[USB_NUM_USBIP][USB_MAXDEVADDR];     /* USB Transfer MBX for PIPE0 wait que */
static rtos_mbx_id_t g_pipe_hdl[USB_NUM_USBIP][USB_MAXPIPE_NUM + 1]; /* USB Transfer MBX for PIPE1-9 wait que */

/** Declare an array of mailbox handlers. **/

rtos_mbx_id_t * g_mbx_table[] =
{
    NULL,                              /* Not used */
    &g_hcd_mbx_hdl,                    /* A mailbox handler of USB HCD task */
    &g_mgr_mbx_hdl,                    /* A mailbox handler of USB MGR task */
    &g_hub_mbx_hdl,                    /* A mailbox handler of USB HUB task */
    &g_cls_mbx_hdl,                    /* A mailbox handler of USB internal communication */
    &g_pcd_mbx_hdl,                    /* A mailbox handler of USB PCD task */
    &g_hmsc_mbx_hdl,                   /* A mailbox handler of USB HMSC */
    &g_hmsc_req_mbx_hdl,               /* A mailbox handler for class request (via PIPE0) of USB HMSC */
    &g_hcdc_mbx_hdl,                   /* A mailbox handler of USB HCDC task */
    &g_hhid_mbx_hdl,                   /* A mailbox handler of USB HHID task */
    &g_pmsc_mbx_hdl,                   /* A mailbox handler of USB PMSC task */
    &g_hprn_mbx_hdl,                   /* A mailbox handler of USB HPRN task */
};

 #if (BSP_CFG_RTOS == 2)

/** Declare a memory handler for the created tasks **/
static rtos_mem_id_t g_hcd_mpl_hdl;
static rtos_mem_id_t g_mgr_mpl_hdl;
static rtos_mem_id_t g_hub_mpl_hdl;
static rtos_mem_id_t g_cls_mpl_hdl;
static rtos_mem_id_t g_hmsc_mpl_hdl;
static rtos_mem_id_t g_hmsc_req_mpl_hdl;
static rtos_mem_id_t g_hcdc_mpl_hdl;
static rtos_mem_id_t g_hhid_mpl_hdl;
static rtos_mem_id_t g_pmsc_mpl_hdl;

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static void * g_p_hcd_mpl[QUEUE_SIZE];
static void * g_p_mgr_mpl[QUEUE_SIZE];
static void * g_p_hub_mpl[QUEUE_SIZE];
static void * g_p_cls_mpl[QUEUE_SIZE];
   #if defined(USB_CFG_HMSC_USE)
static void * g_p_hmsc_mpl[QUEUE_SIZE];
static void * g_p_hmsc_req_mpl[QUEUE_SIZE];
   #endif                              /* defined(USB_CFG_HMSC_USE) */
   #if defined(USB_CFG_HCDC_USE)
static void * g_p_hcdc_mpl[QUEUE_SIZE];
   #endif                              /* defined(USB_CFG_HCDC_USE) */
   #if defined(USB_CFG_HHID_USE)
static void * g_p_hhid_mpl[QUEUE_SIZE];
   #endif                              /* defined(USB_CFG_HHID_USE) */
  #endif                               /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

/** Declare an array of memory pool handlers. **/
rtos_mem_id_t * g_mpl_table[] =
{
    NULL,                              /* Not used */
    &g_hcd_mpl_hdl,                    /* A memory pool handler of USB HCD task */
    &g_mgr_mpl_hdl,                    /* A memory pool handler of USB MGR task */
    &g_hub_mpl_hdl,                    /* A memory pool handler of USB HUB task */
    &g_cls_mpl_hdl,                    /* A memory pool handler of USB internal communication */
    NULL,
    &g_hmsc_mpl_hdl,                   /* A memory pool handler of USB HMSC */
    &g_hmsc_req_mpl_hdl,               /* A memory pool handler for class request (via PIPE0) of USB HMSC */
    &g_hcdc_mpl_hdl,                   /* A memory pool handler of USB HCDC task */
    &g_hhid_mpl_hdl,                   /* A memory pool handler of USB HHID task */
    &g_pmsc_mpl_hdl,                   /* A memory pool handler of USB PMSC task */
};

 #else                                 /* #if (BSP_CFG_RTOS == 2) */
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint8_t g_usb_hcd_stack[HCD_STACK_SIZE];
static uint8_t g_usb_mgr_stack[MGR_STACK_SIZE];
  #endif                               /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static uint8_t g_usb_pcd_stack[PCD_STACK_SIZE];
  #endif                               /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint8_t g_rtos_usb_hcd_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
static uint8_t g_rtos_usb_mgr_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
static uint8_t g_rtos_usb_hub_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
static uint8_t g_rtos_usb_cls_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
  #endif                               /* #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static uint8_t g_rtos_usb_pcd_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
  #endif                               /* #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

  #if defined(USB_CFG_HMSC_USE)
static uint8_t g_rtos_usb_hmsc_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
static uint8_t g_rtos_usb_hmsc_req_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
  #endif                               /* defined(USB_CFG_HMSC_USE) */

  #if defined(USB_CFG_HCDC_USE)
static uint8_t g_rtos_usb_hcdc_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
  #endif                               /* defined(USB_CFG_HCDC_USE) */
  #if defined(USB_CFG_HHID_USE)
static uint8_t g_rtos_usb_hhid_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
  #endif                               /* defined(USB_CFG_HHID_USE) */
  #if defined(USB_CFG_HPRN_USE)
static uint8_t g_rtos_usb_hprn_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
  #endif                               /* defined(USB_CFG_HPRN_USE) */

static TX_BLOCK_POOL g_usb_block_pool_hdl;
static uint8_t       g_usb_rtos_fixed_memblk[((sizeof(usb_utr_t) + sizeof(void *)) * NUM_OF_BLOCK)];

static uint8_t g_rtos_usb_pipe0_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
static uint8_t g_rtos_usb_pipe_mbx[sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)];
 #endif                                /* (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * Function Name: usb_rtos_configuration
 * Description  : Create mailboxes, memory pool using for the created tasks
 *                in usb system.
 * Arguments    : usb_mode_t usb_mode : USB_MODE_HOST or USB_MODE_PERI
 * Return Value : UsbRtos_Success -
 *                   Successful.
 *                UsbRtos_Err_Init_Mbx -
 *                   Failed in mailbox allocation.
 *                UsbRtos_Err_Init_Mpl -
 *                   Failed in memory pool allocation.
 ******************************************************************************/
usb_rtos_err_t usb_rtos_configuration (usb_mode_t usb_mode)
{
    usb_rtos_err_t err = UsbRtos_Success;
    uint16_t       ip_loop;
    uint16_t       pipe_loop;
    uint16_t       addr_loop;
 #if (BSP_CFG_RTOS != 2)
    FSP_PARAMETER_NOT_USED(usb_mode);
 #endif

 #if (BSP_CFG_RTOS == 2)
    BaseType_t ret;
    if (USB_MODE_HOST == usb_mode)
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        uint16_t i;
        void   * tmptr = NULL;

        /** Create mailbox for each task. **/
        /** USB HCD task **/
        g_hcd_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_hcd_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB MGR task **/
        g_mgr_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_mgr_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB HUB task **/
        g_hub_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_hub_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Internal Communication mailbox **/
        g_cls_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_cls_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

   #if defined(USB_CFG_HMSC_USE)
        vSemaphoreCreateBinary(SemaphoreHandleRead);

        /** USB Host MSC **/
        g_hmsc_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_hmsc_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Host MSC (for class request) **/
        g_hmsc_req_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_hmsc_req_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HCDC_USE)

        /** USB Host CDC **/
        g_hcdc_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_hcdc_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HCDC_USE) */

   #if defined(USB_CFG_HHID_USE)

        /** USB Host HID **/
        g_hhid_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_hhid_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HHID_USE) */

   #if defined(USB_CFG_HPRN_USE)

        /** USB Host Printer **/
        g_hprn_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_hprn_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HPRN_USE) */

        /** Create memory pool using for each task **/
        /** USB HCD task **/
        g_hcd_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_hcd_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_hcd_mpl[i] = tmptr;
                xQueueSend(g_hcd_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }

        if (UsbRtos_Err_Init_Mpl == err)
        {
            return err;
        }

        /** USB MGR task **/
        g_mgr_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_mgr_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_mgr_mpl[i] = tmptr;
                xQueueSend(g_mgr_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }

        if (UsbRtos_Err_Init_Mpl == err)
        {
            return err;
        }

        /** USB HUB task **/
        g_hub_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_hub_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_hub_mpl[i] = tmptr;
                xQueueSend(g_hub_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }

        if (UsbRtos_Err_Init_Mpl == err)
        {
            return err;
        }

        /** USB Internal Communication **/
        g_cls_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_cls_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_cls_mpl[i] = tmptr;
                xQueueSend(g_cls_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }

        if (UsbRtos_Err_Init_Mpl == err)
        {
            return err;
        }

   #if defined(USB_CFG_HMSC_USE)

        /** USB Host MSC **/
        g_hmsc_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_hmsc_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_hmsc_mpl[i] = tmptr;
                xQueueSend(g_hmsc_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }

        if (UsbRtos_Err_Init_Mpl == err)
        {
            return err;
        }

        /** USB Host MSC (for class request) **/
        g_hmsc_req_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_hmsc_req_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_hmsc_req_mpl[i] = tmptr;
                xQueueSend(g_hmsc_req_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }

        if (UsbRtos_Err_Init_Mpl == err)
        {
            return err;
        }
   #endif                              /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HCDC_USE)

        /** USB Host CDC **/
        g_hcdc_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_hcdc_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_hcdc_mpl[i] = tmptr;
                xQueueSend(g_hcdc_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }

        if (UsbRtos_Err_Init_Mpl == err)
        {
            return err;
        }
   #endif                              /* defined(USB_CFG_HCDC_USE) */

   #if defined(USB_CFG_HHID_USE)

        /** USB Host HID **/
        g_hhid_mpl_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL != g_hhid_mpl_hdl)
        {
            /* WAIT_LOOP */
            for (i = 0; i < QUEUE_SIZE; i++)
            {
                tmptr = pvPortMalloc(sizeof(usb_utr_t));
                if (NULL == tmptr)
                {
                    err = UsbRtos_Err_Init_Mpl;

                    return err;
                }

                g_p_hhid_mpl[i] = tmptr;
                xQueueSend(g_hhid_mpl_hdl, &tmptr, 0);
            }
        }
        else
        {
            err = UsbRtos_Err_Init_Mpl;

            return err;
        }
   #endif                                                     /* defined(USB_CFG_HHID_USE) */

        /** USB Tasks Creation **/
        ret = xTaskCreate((TaskFunction_t) usb_hstd_hcd_task, /** Entry function of USB HCD task  **/
                          "HCD_TSK",                          /** Name of USB HCD task            **/
                          HCD_STACK_SIZE,                     /** Stack size in words             **/
                          NULL,                               /** Task's parameter                **/
                          HCD_TSK_PRI,                        /** Task's priority                 **/
                          &g_hcd_tsk_hdl);                    /** Task handler for use later      **/
        if (pdPASS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }

   #if USB_CFG_HUB == USB_CFG_ENABLE
        ret = xTaskCreate((TaskFunction_t) usb_hhub_task, /** Entry function of USB HUB task  **/
                          "HUB_TSK",                      /** Name of USB HUB task            **/
                          HUB_STACK_SIZE,                 /** Stack size in words             **/
                          NULL,                           /** Task's parameter                **/
                          HUB_TSK_PRI,                    /** Task's priority                 **/
                          &g_hub_tsk_hdl);                /** Task handler for use later      **/
        if (pdPASS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }
   #endif                                                     /* USB_CFG_HUB == USB_CFG_ENABLE */

        ret = xTaskCreate((TaskFunction_t) usb_hstd_mgr_task, /** Entry function of USB MGR task  **/
                          "MGR_TSK",                          /** Name of USB MGR task            **/
                          MGR_STACK_SIZE,                     /** Stack size in words             **/
                          NULL,                               /** Task's parameter                **/
                          MGR_TSK_PRI,                        /** Task's priority                 **/
                          &g_mgr_tsk_hdl);                    /** Task handler for use later      **/
        if (pdPASS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }
    else
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

        /** Create mailbox **/
        /** USB PCD task **/
        g_pcd_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_pcd_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Tasks Creation **/
        ret = xTaskCreate((TaskFunction_t) usb_pstd_pcd_task, /** Entry function of USB HCD task  **/
                          "PCD_TSK",                          /** Name of USB HCD task            **/
                          PCD_STACK_SIZE,                     /** Stack size in words             **/
                          NULL,                               /** Task's parameter                **/
                          PCD_TSK_PRI,                        /** Task's priority                 **/
                          &g_pcd_tsk_hdl);                    /** Task handler for use later      **/
        if (pdPASS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */

  #if defined(USB_CFG_PMSC_USE)

        /** Create mailbox **/
        /** USB PMSC task **/
        g_pmsc_mbx_hdl = xQueueCreate(QUEUE_SIZE, sizeof(void *));
        if (NULL == g_pmsc_mbx_hdl)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Tasks Creation **/
        ret = xTaskCreate((TaskFunction_t) usb_pmsc_task, /** Entry function of USB PMSC task  **/
                          "PMSC_TSK",                     /** Name of USB HCD task            **/
                          PMSC_STACK_SIZE,                /** Stack size in words             **/
                          NULL,                           /** Task's parameter                **/
                          PMSC_TSK_PRI,                   /** Task's priority                 **/
                          &g_pmsc_tsk_hdl);               /** Task handler for use later      **/
        if (pdPASS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }
  #endif                               /* defined(USB_CFG_PMSC_USE) */
    }

  #if (USB_NUM_USBIP == 2)
    if ((g_usb_usbmode[0] == 0) || (g_usb_usbmode[1] == 0))
    {
  #endif                               /* (USB_NUM_USBIP == 2) */
    /* WAIT_LOOP */
    for (ip_loop = 0; ip_loop < USB_NUM_USBIP; ip_loop++)
    {
        /** Create memory pool using for pipe process **/
        /* WAIT_LOOP */
        for (addr_loop = 0; addr_loop < USB_MAXDEVADDR; addr_loop++)
        {
            g_pipe0_hdl[ip_loop][addr_loop] = xQueueCreate(QUEUE_SIZE, sizeof(void *));
            if (NULL == g_pipe0_hdl[ip_loop][addr_loop])
            {
                err = UsbRtos_Err_Init_Mpl;

                return err;
            }
        }

        /* WAIT_LOOP */
        for (pipe_loop = 0; pipe_loop < (USB_MAXPIPE_NUM + 1); pipe_loop++)
        {
            g_pipe_hdl[ip_loop][pipe_loop] = xQueueCreate(QUEUE_SIZE, sizeof(void *));
            if (NULL == g_pipe_hdl[ip_loop][pipe_loop])
            {
                err = UsbRtos_Err_Init_Mpl;

                return err;
            }
        }
    }

  #if (USB_NUM_USBIP == 2)
}
  #endif                               /* (USB_NUM_USBIP == 2) */
 #elif (BSP_CFG_RTOS == 1)             /* Azure RTOS */
    uint32_t ret;

    ret = tx_block_pool_create(&g_usb_block_pool_hdl,
                               "USB_MEM_BLOCK",
                               sizeof(usb_utr_t),
                               (void *) &g_usb_rtos_fixed_memblk[0],
                               (uint32_t) ((sizeof(usb_utr_t) + sizeof(void *)) * NUM_OF_BLOCK));
    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Init_Mpl;

        return err;
    }

  #if !defined(USB_CFG_OTG_USE)
    if (USB_MODE_HOST == usb_mode)
  #endif                               /* !defined (USB_CFG_OTG_USE)*/
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

        /** Create mailbox for each task. **/
        /** USB HCD task **/
        ret =
            tx_queue_create(&g_hcd_mbx_hdl, "USB_HCD_MBX", TX_1_ULONG, &g_rtos_usb_hcd_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB MGR task **/
        ret =
            tx_queue_create(&g_mgr_mbx_hdl, "USB_MGR_MBX", TX_1_ULONG, &g_rtos_usb_mgr_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB HUB task **/
        ret =
            tx_queue_create(&g_hub_mbx_hdl, "USB_HUB_MBX", TX_1_ULONG, &g_rtos_usb_hub_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Internal Communication mailbox **/
        ret =
            tx_queue_create(&g_cls_mbx_hdl, "USB_CLS_MBX", TX_1_ULONG, &g_rtos_usb_cls_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

   #if defined(USB_CFG_HMSC_USE)
        ret = tx_semaphore_create(&SemaphoreHandleRead, "USB_HMSC_SEM", 1);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Sem;

            return err;
        }

        /** USB Host MSC **/
        ret =
            tx_queue_create(&g_hmsc_mbx_hdl, "USB_HMSC_MBX", TX_1_ULONG, &g_rtos_usb_hmsc_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Host MSC (for class request) **/
        ret =
            tx_queue_create(&g_hmsc_req_mbx_hdl, "USB_HMSC_REQ_MBX", TX_1_ULONG, &g_rtos_usb_hmsc_req_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HCDC_USE)

        /** USB Host CDC **/
        ret =
            tx_queue_create(&g_hcdc_mbx_hdl, "USB_HCDC_MBX", TX_1_ULONG, &g_rtos_usb_hcdc_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HCDC_USE) */

   #if defined(USB_CFG_HHID_USE)

        /** USB Host HID **/

        ret =
            tx_queue_create(&g_hhid_mbx_hdl, "USB_HHID_MBX", TX_1_ULONG, &g_rtos_usb_hhid_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HHID_USE) */

   #if defined(USB_CFG_HPRN_USE)

        /** USB Host Printer **/
        ret =
            tx_queue_create(&g_hprn_mbx_hdl, "USB_HPRN_MBX", TX_1_ULONG, &g_rtos_usb_hprn_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                                                    /* defined(USB_CFG_HPRN_USE) */

        ret = tx_thread_create(&g_hcd_tsk_hdl,               /** Pointer to a thread control block.              **/
                               "HCD_TASK",                   /** Pointer to the name of the thread.              **/
                               usb_hstd_hcd_task,            /** Entry function of USB HCD task                  **/
                               (uint32_t) NULL,              /** Task's parameter                                **/
                               (void *) &g_usb_hcd_stack[0], /** Starting address of the stack fs memory area.   **/
                               HCD_STACK_SIZE,               /** Number bytes in the stack memory area.          **/
                               HCD_TSK_PRI,                  /** Task's priority                                 **/
                               HCD_TSK_PRI,                  /** Preempt Threashold                              **/
                               TX_NO_TIME_SLICE,             /** Time Slice (Yes or No)                          **/
                               TX_AUTO_START);               /** Auto Start (Yes or No)                          **/
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }

        ret = tx_thread_create(&g_mgr_tsk_hdl,               /** Pointer to a thread control block.              **/
                               "MGR_TSK",                    /** Pointer to the name of the thread.              **/
                               usb_hstd_mgr_task,            /** Entry function of USB HCD task                  **/
                               (uint32_t) NULL,              /** Task's parameter                                **/
                               (void *) &g_usb_mgr_stack[0], /** Starting address of the stack fs memory area.   **/
                               MGR_STACK_SIZE,               /** Number bytes in the stack memory area.          **/
                               MGR_TSK_PRI,                  /** Task's priority                                 **/
                               MGR_TSK_PRI,                  /** Task's priority                                 **/
                               TX_NO_TIME_SLICE,             /** Time Slice (Yes or No)                          **/
                               TX_AUTO_START);               /** Auto Start (Yes or No)                          **/
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }

  #if defined(USB_CFG_OTG_USE)
  #else
    else
  #endif                               /* defined (USB_CFG_OTG_USE) */
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

        /** Create mailbox **/
        /** USB PCD task **/
        ret =
            tx_queue_create(&g_pcd_mbx_hdl, "USB_PCD_MBX", TX_1_ULONG, &g_rtos_usb_pcd_mbx[0],
                            (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Tasks Creation **/
        ret = tx_thread_create(&g_pcd_tsk_hdl,               /** Pointer to a thread control block.              **/
                               "PCD_TSK",                    /** Pointer to the name of the thread.              **/
                               usb_pstd_pcd_task,            /** Entry function of USB HCD task                  **/
                               (uint32_t) NULL,              /** Task's parameter                                **/
                               (void *) &g_usb_pcd_stack[0], /** Starting address of the stack fs memory area.   **/
                               PCD_STACK_SIZE,               /** Number bytes in the stack memory area.          **/
                               PCD_TSK_PRI,                  /** Task's priority                                 **/
                               PCD_TSK_PRI,                  /** Preempt_threshold                               **/
                               TX_NO_TIME_SLICE,             /** Time Slice (Yes or No)                          **/
                               TX_AUTO_START);               /** Auto Start (Yes or No)                          **/
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }

    /* WAIT_LOOP */
    for (ip_loop = 0; ip_loop < USB_NUM_USBIP; ip_loop++)
    {
        /** Create memory pool using for pipe process **/
        /* WAIT_LOOP */
        for (addr_loop = 0; addr_loop < USB_MAXDEVADDR; addr_loop++)
        {
            ret = tx_queue_create(&g_pipe0_hdl[ip_loop][addr_loop],
                                  "USB_PIPE0_MBX",
                                  TX_1_ULONG,
                                  &g_rtos_usb_pipe0_mbx[0],
                                  (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));

            if (TX_SUCCESS != ret)
            {
                err = UsbRtos_Err_Init_Mbx;

                return err;
            }
        }

        /* WAIT_LOOP */
        for (pipe_loop = 0; pipe_loop < (USB_MAXPIPE_NUM + 1); pipe_loop++)
        {
            ret = tx_queue_create(&g_pipe_hdl[ip_loop][pipe_loop],
                                  "USB_PIPE_MBX",
                                  TX_1_ULONG,
                                  &g_rtos_usb_pipe_mbx[0],
                                  (sizeof(ULONG) * (TX_1_ULONG) *(QUEUE_SIZE)));
            if (TX_SUCCESS != ret)
            {
                err = UsbRtos_Err_Init_Mbx;

                return err;
            }
        }
    }

  #if defined(USB_CFG_OTG_USE)
    ret = tx_timer_create(&g_usb_otg_detach_timer, /* Pointer to detach timer */
                          "USB OTG Detach Timer",  /* Detach Timer Name */
                          usb_otg_detach_timer,    /* Pointer to detach timer function */
                          (ULONG) 0,               /* Expiration Input */
                          (ULONG) 5,               /* Initial Ticks */
                          (ULONG) 5,               /* Reschedule Ticks */
                          TX_NO_ACTIVATE);         /* Auto Activate */

    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Init_OTG_Detach_Tmr;

        return err;
    }

    ret = tx_timer_create(&g_usb_otg_chattering_timer, /* Pointer to detach timer */
                          "USB OTG Chattering Timer",  /* Detach Timer Name */
                          usb_otg_chattering_timer,    /* Pointer to detach timer function */
                          (ULONG) 0,                   /* Expiration Input */
                          (ULONG) 4,                   /* Initial Ticks */
                          (ULONG) 4,                   /* Reschedule Ticks */
                          TX_AUTO_ACTIVATE);           /* Auto Activate */

    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Init_OTG_Chattering_Tmr;

        return err;
    }

    ret = tx_timer_create(&g_usb_otg_hnp_timer, /* Pointer to detach timer */
                          "USB OTG HNP Timer",  /* Detach Timer Name */
                          usb_otg_hnp_timer,    /* Pointer to detach timer function */
                          (ULONG) 0,            /* Expiration Input */
                          (ULONG) 10,           /* Initial Ticks */
                          (ULONG) 10,           /* Reschedule Ticks */
                          TX_NO_ACTIVATE);      /* Auto Activate */

    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Init_OTG_HNP_Tmr;

        return err;
    }

   #if USB_NUM_USBIP == 2
    ret = tx_timer_create(&g_usb2_otg_detach_timer, /* Pointer to detach timer */
                          "USB2 OTG Detach Timer",  /* Detach Timer Name */
                          usb2_otg_detach_timer,    /* Pointer to detach timer function */
                          (ULONG) 0,                /* Expiration Input */
                          (ULONG) 5,                /* Initial Ticks */
                          (ULONG) 5,                /* Reschedule Ticks */
                          TX_NO_ACTIVATE);          /* Auto Activate */

    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Init_OTG_Detach_Tmr;

        return err;
    }
   #endif                              /* USB_NUM_USBIP == 2 */
  #endif                               /* defined (USB_CFG_OTG_USE) */
 #endif                                /* BSP_CFG_RTOS */

    return err;
}                                      /* End of function usb_rtos_configuration() */

/******************************************************************************
 * Function Name: usb_rtos_delete
 * Description  : Delete mailboxes, memory pool using for the deleted tasks
 *                in usb system.
 * Arguments    : uint8_t module_number : USB module number
 * Return Value : UsbRtos_Success -
 *                   Successful.
 *                UsbRtos_Err_Delete_Mbx -
 *                   Failed in mailbox allocation.
 *                UsbRtos_Err_Delete_Mpl -
 *                   Failed in memory pool allocation.
 ******************************************************************************/
usb_rtos_err_t usb_rtos_delete (uint8_t module_number)
{
    usb_rtos_err_t err = UsbRtos_Success;
    uint16_t       ip_loop;
    uint16_t       pipe_loop;
    uint16_t       addr_loop;
 #if (BSP_CFG_RTOS == 2)
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    uint16_t i;
  #endif                               /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

    if (USB_MODE_HOST == g_usb_usbmode[module_number])
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

        /** Delete mailbox for each task. **/
        /** USB HCD task **/
        vQueueDelete(g_hcd_mbx_hdl);

        /** USB MGR task **/
        vQueueDelete(g_mgr_mbx_hdl);

        /** USB HUB task **/
        vQueueDelete(g_hub_mbx_hdl);

        /** USB Internal Communication mailbox **/
        vQueueDelete(g_cls_mbx_hdl);

   #if defined(USB_CFG_HMSC_USE)
        vSemaphoreDelete(SemaphoreHandleRead);

        /** USB Host MSC **/
        vQueueDelete(g_hmsc_mbx_hdl);

        /** USB Host MSC (for class request) **/
        vQueueDelete(g_hmsc_req_mbx_hdl);
   #endif                              /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HCDC_USE)

        /** USB Host CDC **/
        vQueueDelete(g_hcdc_mbx_hdl);
   #endif                              /* defined(USB_CFG_HCDC_USE) */

   #if defined(USB_CFG_HHID_USE)

        /** USB Host HID **/
        vQueueDelete(g_hhid_mbx_hdl);
   #endif                              /* defined(USB_CFG_HHID_USE) */

   #if defined(USB_CFG_HPRN_USE)

        /** USB Host Printer **/
        vQueueDelete(g_hprn_mbx_hdl);
   #endif                              /* defined(USB_CFG_HPRN_USE) */

        /** Delete memory pool using for each task **/
        /** USB HCD task **/
        vQueueDelete(g_hcd_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_hcd_mpl[i]);
        }

        /** USB MGR task **/
        vQueueDelete(g_mgr_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_mgr_mpl[i]);
        }

        /** USB HUB task **/
        vQueueDelete(g_hub_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_hub_mpl[i]);
        }

        /** USB Internal Communication **/
        vQueueDelete(g_cls_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_cls_mpl[i]);
        }

   #if defined(USB_CFG_HMSC_USE)

        /** USB Host MSC **/
        vQueueDelete(g_hmsc_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_hmsc_mpl[i]);
        }

        /** USB Host MSC (for class request) **/
        vQueueDelete(g_hmsc_req_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_hmsc_req_mpl[i]);
        }
   #endif                              /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HCDC_USE)

        /** USB Host CDC **/
        vQueueDelete(g_hcdc_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_hcdc_mpl[i]);
        }
   #endif                              /* defined(USB_CFG_HCDC_USE) */

   #if defined(USB_CFG_HHID_USE)

        /** USB Host HID **/
        vQueueDelete(g_hhid_mpl_hdl);
        for (i = 0; i < QUEUE_SIZE; i++)
        {
            vPortFree(g_p_hhid_mpl[i]);
        }
   #endif                              /* defined(USB_CFG_HHID_USE) */

        /** USB Tasks Creation **/
        vTaskDelete(g_hcd_tsk_hdl);

   #if USB_CFG_HUB == USB_CFG_ENABLE
        vTaskDelete(g_hub_tsk_hdl);
   #endif                              /* USB_CFG_HUB == USB_CFG_ENABLE */
        vTaskDelete(g_mgr_tsk_hdl);
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }
    else
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

        /** USB Tasks Creation **/
        vTaskDelete(g_pcd_tsk_hdl);

        /** Delete mailbox **/
        /** USB PCD task **/
        vQueueDelete(g_pcd_mbx_hdl);

   #if defined(USB_CFG_PMSC_USE)

        /** USB Tasks Creation **/
        vTaskDelete(g_pmsc_tsk_hdl);

        /** Delete mailbox **/
        /** USB PMSC task **/
        vQueueDelete(g_pmsc_mbx_hdl);
   #endif                              /* defined(USB_CFG_PMSC_USE) */
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }

  #if (USB_NUM_USBIP == 2)
    if ((g_usb_usbmode[0] == 0) || (g_usb_usbmode[1] == 0))
    {
  #endif                               /* (USB_NUM_USBIP == 2) */
    /* WAIT_LOOP */
    for (ip_loop = 0; ip_loop < USB_NUM_USBIP; ip_loop++)
    {
        /** Delete memory pool using for pipe process **/
        /* WAIT_LOOP */
        for (addr_loop = 0; addr_loop < USB_MAXDEVADDR; addr_loop++)
        {
            vQueueDelete(g_pipe0_hdl[ip_loop][addr_loop]);
        }

        /* WAIT_LOOP */
        for (pipe_loop = 0; pipe_loop < (USB_MAXPIPE_NUM + 1); pipe_loop++)
        {
            vQueueDelete(g_pipe_hdl[ip_loop][pipe_loop]);
        }
    }

  #if (USB_NUM_USBIP == 2)
}
  #endif                               /* (USB_NUM_USBIP == 2) */
 #elif (BSP_CFG_RTOS == 1)             /* Azure RTOS */
    uint32_t ret;

    (void) module_number;

    ret = tx_block_pool_delete(&g_usb_block_pool_hdl);
    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Init_Mpl;

        return err;
    }

  #if !defined(USB_CFG_OTG_USE)
    if (USB_MODE_HOST == g_usb_usbmode[module_number])
  #endif                               /* !defined (USB_CFG_OTG_USE)*/
    {
  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

        /** Delete mailbox for each task. **/
        /** USB HCD task **/
        ret = tx_queue_delete(&g_hcd_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB MGR task **/
        ret = tx_queue_delete(&g_mgr_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB HUB task **/
        ret = tx_queue_delete(&g_hub_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Internal Communication mailbox **/
        ret = tx_queue_delete(&g_cls_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

   #if defined(USB_CFG_HMSC_USE)
        ret = tx_semaphore_delete(&SemaphoreHandleRead);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Sem;

            return err;
        }

        /** USB Host MSC **/
        ret = tx_queue_delete(&g_hmsc_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }

        /** USB Host MSC (for class request) **/
        ret = tx_queue_delete(&g_hmsc_req_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HCDC_USE)

        /** USB Host CDC **/
        ret = tx_queue_delete(&g_hcdc_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HCDC_USE) */

   #if defined(USB_CFG_HHID_USE)

        /** USB Host HID **/
        ret = tx_queue_delete(&g_hhid_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HHID_USE) */

   #if defined(USB_CFG_HPRN_USE)

        /** USB Host Printer **/
        ret = tx_queue_delete(&g_hprn_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
   #endif                              /* defined(USB_CFG_HPRN_USE) */

        ret = tx_thread_terminate(&g_hcd_tsk_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }

        ret = tx_thread_delete(&g_hcd_tsk_hdl); /** Pointer to a thread control block.  **/
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }

        ret = tx_thread_terminate(&g_mgr_tsk_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }

        ret = tx_thread_delete(&g_mgr_tsk_hdl); /** Task handler for use later      **/
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
    }

  #if defined(USB_CFG_OTG_USE)
  #else
    else
  #endif
    {
  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        ret = tx_thread_terminate(&g_pcd_tsk_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }

        /** USB Tasks Creation **/
        ret = tx_thread_delete(&g_pcd_tsk_hdl); /** Task handler for use later      **/
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Tsk;

            return err;
        }

        /** Delete mailbox **/
        /** USB PCD task **/
        ret = tx_queue_delete(&g_pcd_mbx_hdl);
        if (TX_SUCCESS != ret)
        {
            err = UsbRtos_Err_Init_Mbx;

            return err;
        }
  #endif                               /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
    }

    /* WAIT_LOOP */
    for (ip_loop = 0; ip_loop < USB_NUM_USBIP; ip_loop++)
    {
        /** Delete memory pool using for pipe process **/
        /* WAIT_LOOP */
        for (addr_loop = 0; addr_loop < USB_MAXDEVADDR; addr_loop++)
        {
            ret = tx_queue_delete(&g_pipe0_hdl[ip_loop][addr_loop]);
            if (TX_SUCCESS != ret)
            {
                err = UsbRtos_Err_Init_Mpl;

                return err;
            }
        }

        /* WAIT_LOOP */
        for (pipe_loop = 0; pipe_loop < (USB_MAXPIPE_NUM + 1); pipe_loop++)
        {
            ret = tx_queue_delete(&g_pipe_hdl[ip_loop][pipe_loop]);
            if (TX_SUCCESS != ret)
            {
                err = UsbRtos_Err_Init_Mpl;

                return err;
            }
        }
    }

  #if defined(USB_CFG_OTG_USE)
    tx_timer_deactivate(&g_usb_otg_detach_timer);
    ret = tx_timer_delete(&g_usb_otg_detach_timer);
    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Delete_OTG_Detach_Tmr;

        return err;
    }

   #if USB_NUM_USBIP == 2
    tx_timer_deactivate(&g_usb2_otg_detach_timer);
    ret = tx_timer_delete(&g_usb2_otg_detach_timer);
    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Delete_OTG_Detach_Tmr;

        return err;
    }
   #endif                              /* USB_NUM_USBIP == 2 */
    ret = tx_timer_delete(&g_usb_otg_chattering_timer);
    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Delete_OTG_Chattering_Tmr;

        return err;
    }

    ret = tx_timer_delete(&g_usb_otg_hnp_timer);
    if (TX_SUCCESS != ret)
    {
        err = UsbRtos_Err_Delete_OTG_HNP_Tmr;

        return err;
    }
  #endif                               /* defined (USB_CFG_OTG_USE) */
 #endif                                /* BSP_CFG_RTOS */

    return err;
}                                      /* End of function usb_rtos_delete() */

/******************************************************************************
 * Function Name   : usb_cstd_rec_msg
 * Description     : Receive a message to the specified id (mailbox).
 * Argument        : uint8_t      id      : ID number (mailbox).
 *               : usb_msg_t**  mess    : Message pointer
 *               : usb_tm_t     tm      : Timeout Value
 * Return          : uint16_t             : USB_OK / USB_ERROR
 ******************************************************************************/
usb_er_t usb_cstd_rec_msg (uint8_t id, usb_msg_t ** mess, usb_tm_t tm)
{
 #if (BSP_CFG_RTOS == 2)
    BaseType_t err;
 #elif   (BSP_CFG_RTOS == 1)
    uint32_t err;
 #endif
    usb_er_t result;

    if (NULL == mess)
    {
        return USB_ERROR;
    }

    *mess = NULL;

    if (0 == tm)
    {
        tm = USB_TMO_VAL;
    }

 #if (BSP_CFG_RTOS == 2)

    /** Receive message from queue specified by *(mbx_table[id]) **/
    err = xQueueReceive(*(g_mbx_table[id]), (void *) mess, (TickType_t) tm);
    if ((pdTRUE == err) && (NULL != (*mess)))
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }

 #elif   (BSP_CFG_RTOS == 1)
    err = tx_queue_receive(g_mbx_table[id], (void *) mess, (uint32_t) tm);
    if ((TX_SUCCESS == err) && (NULL != mess))
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }
 #endif

    return result;
}

/******************************************************************************
 * End of function usb_cstd_rec_msg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_snd_msg
 * Description     : Send a message to the specified id (mailbox).
 * Argument        : uint8_t      id      : ID number (mailbox).
 *               : usb_msg_t*   mess    : Message pointer
 * Return          : usb_er_t             : USB_OK / USB_ERROR
 ******************************************************************************/
usb_er_t usb_cstd_snd_msg (uint8_t id, usb_msg_t * mess)
{
 #if (BSP_CFG_RTOS == 2)
    BaseType_t err;
 #elif   (BSP_CFG_RTOS == 1)
    uint32_t err;
 #endif
    usb_er_t result;

    if (NULL == mess)
    {
        return USB_ERROR;
    }

 #if (BSP_CFG_RTOS == 2)

    /** Send message to queue specified by *(mbx_table[id]) **/
    err = xQueueSend(*(g_mbx_table[id]), (const void *) &mess, (TickType_t) (0));
    if (pdTRUE == err)
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }

 #elif   (BSP_CFG_RTOS == 1)
    err = tx_queue_send(g_mbx_table[id], (void *) &mess, TX_NO_WAIT);
    if ((TX_SUCCESS == err) && (NULL != mess))
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }
 #endif

    return result;
}

/******************************************************************************
 * End of function usb_cstd_snd_msg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_isnd_msg
 * Description     : Send a message to the specified id (mailbox) while executing
 *               : an interrupt.
 * Argument        : uint8_t      id      : ID number (mailbox).
 *               : usb_msg_t*   mess    : Message pointer
 * Return          : usb_er_t             : USB_OK / USB_ERROR
 ******************************************************************************/
usb_er_t usb_cstd_isnd_msg (uint8_t id, usb_msg_t * mess)
{
 #if (BSP_CFG_RTOS == 2)
    BaseType_t err;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
 #elif   (BSP_CFG_RTOS == 1)
    uint32_t err;
 #endif
    usb_er_t result;

    if (NULL == mess)
    {
        return USB_ERROR;
    }

 #if (BSP_CFG_RTOS == 2)

    /** Send message to queue specified by *(mbx_table[id]) from ISR **/
    err = xQueueSendFromISR(*(g_mbx_table[id]), (const void *) &mess, &xHigherPriorityTaskWoken);
    if (pdTRUE == err)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }

 #elif   (BSP_CFG_RTOS == 1)
    err = tx_queue_send(g_mbx_table[id], (void *) &mess, TX_NO_WAIT);
    if ((TX_SUCCESS == err) && (NULL != mess))
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }
 #endif

    return result;
}

/******************************************************************************
 * End of function usb_cstd_isnd_msg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_pget_blk
 * Description     : Get a memory block for the caller.
 * Argument        : uint8_t      id      : ID number (mailbox).
 *               : usb_utr_t**  blk     : Memory block pointer.
 * Return          : usb_er_t             : USB_OK / USB_ERROR
 ******************************************************************************/
usb_er_t usb_cstd_pget_blk (uint8_t id, usb_utr_t ** blk)
{
 #if (BSP_CFG_RTOS == 2)
    BaseType_t    err;
    QueueHandle_t handle;
 #elif   (BSP_CFG_RTOS == 1)
    FSP_PARAMETER_NOT_USED(id);
    uint32_t err;
 #endif
    usb_er_t result;

    if (NULL == blk)
    {
        return USB_ERROR;
    }

 #if (BSP_CFG_RTOS == 2)
    handle = *(g_mpl_table[id]);
    *blk   = NULL;

    /* Look for a free memory block */
    err = xQueueReceive(handle, (void *) blk, (TickType_t) (0));
    if ((pdTRUE == err) && (NULL != (*blk)))
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }

 #elif (BSP_CFG_RTOS == 1)
    err = tx_block_allocate(&g_usb_block_pool_hdl, (void **) blk, TX_NO_WAIT);
    if ((TX_SUCCESS == err) && (NULL != (*blk)))
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }
 #endif                                /* BSP_CFG_RTOS */

    return result;
}

/******************************************************************************
 * End of function usb_cstd_pget_blk
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_rel_blk
 * Description     : Release a memory block.
 * Argument        : uint8_t      id      : ID number (mailbox).
 *               : usb_utr_t*   blk     : Memory block pointer.
 * Return          : usb_er_t             : USB_OK / USB_ERROR
 ******************************************************************************/
usb_er_t usb_cstd_rel_blk (uint8_t id, usb_utr_t * blk)
{
 #if (BSP_CFG_RTOS == 2)
    BaseType_t    err;
    QueueHandle_t handle;
 #elif   (BSP_CFG_RTOS == 1)
    FSP_PARAMETER_NOT_USED(id);
    uint32_t err;
 #endif
    usb_er_t result;

    if (NULL == blk)
    {
        return USB_ERROR;
    }

 #if (BSP_CFG_RTOS == 2)
    handle = (*(g_mpl_table[id]));

    /* Release a memory block specified by id */
    err = xQueueSend(handle, (const void *) &blk, (TickType_t) (0));
    if (pdTRUE == err)
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }

 #elif (BSP_CFG_RTOS == 1)
    err = tx_block_release((void *) blk);
    if (TX_SUCCESS == err)
    {
        result = USB_OK;
    }
    else
    {
        result = USB_ERROR;
    }
 #endif                                /* BSP_CFG_RTOS */

    return result;
}

/******************************************************************************
 * End of function usb_cstd_rel_blk
 ******************************************************************************/

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/***************************************************************************//**
 * @brief Runs USB_SND_MSG after running the scheduler the specified number of times.
 *
 * @retval FSP_SUCCESS         Success.
 * @retval FSP_ERR_USB_FAILED  Failed in acquiring version information.
 ******************************************************************************/
fsp_err_t usb_cstd_wai_msg (uint8_t id, usb_msg_t * mess, usb_tm_t times)
{
    usb_er_t  err;
    fsp_err_t result;

  #if   (BSP_CFG_RTOS == 2)
    vTaskDelay((TickType_t) ((uint16_t) times / portTICK_PERIOD_MS));
  #elif   (BSP_CFG_RTOS == 1)
    tx_thread_sleep((rtos_time_t) times);
  #endif                               /* #if (BSP_CFG_RTOS == 1) */
    err = usb_cstd_snd_msg(id, mess);

    if (USB_OK == err)
    {
        result = FSP_SUCCESS;
    }
    else
    {
        result = FSP_ERR_USB_FAILED;
    }

    return result;
}

/******************************************************************************
 * End of function usb_cstd_wai_msg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_wait_scheduler
 * Description     : Schedules a wait request.
 * Argument        : none
 * Return          : none
 ******************************************************************************/
void usb_cstd_wait_scheduler (void)
{
}

/******************************************************************************
 * End of function usb_cstd_wait_scheduler
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_sche_init
 * Description     : Scheduler initialization.
 * Argument        : none
 * Return          : none
 ******************************************************************************/
void usb_cstd_sche_init (void)
{
}

/******************************************************************************
 * End of function usb_cstd_sche_init
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_set_task_pri
 * Description     : Set a task's priority.
 * Argument        : uint8_t tasknum   : Task id.
 *               : uint8_t pri       : The task priority to be set.
 * Return          : none
 ******************************************************************************/
void usb_cstd_set_task_pri (uint8_t tasknum, uint8_t pri)
{
    (void) tasknum;
    (void) pri;
}

/******************************************************************************
 * End of function usb_cstd_set_task_pri
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_check_schedule
 * Description     : Check schedule flag to see if caller's "time has come", then
 *               : clear it.
 * Argument        : none
 * Return          : flg   : usb_scheduler_schedule_flag
 ******************************************************************************/
uint8_t usb_cstd_check_schedule (void)
{
    return USB_FLGSET;
}

/******************************************************************************
 * End of function usb_cstd_check_schedule
 ******************************************************************************/

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * Function Name   : usb_cstd_pipe_msg_clear
 * Description     : Message clear for PIPE Transfer wait que.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipe_no    : Pipe no.
 * Return          : none
 ******************************************************************************/
void usb_cstd_pipe_msg_clear (usb_utr_t * ptr, uint16_t pipe_no)
{
 #if   (BSP_CFG_RTOS == 2)
    BaseType_t err;
 #elif   (BSP_CFG_RTOS == 1)
    uint32_t err;
 #endif
    usb_msg_t * mess;
    uint16_t    ip;

    ip = ptr->ip;

 #if   (BSP_CFG_RTOS == 2)
    vPortFree(ptr);
    if ((USB_MIN_PIPE_NO > pipe_no) || (USB_MAXPIPE_NUM < pipe_no))
    {
        return;
    }

    /* WAIT_LOOP */
    do
    {
        /** Receive message from queue specified by *(mbx_table[id]) **/
        err = xQueueReceive(g_pipe_hdl[ip][pipe_no], (void *) &mess, (TickType_t) (0));
        if ((pdTRUE == err) && (NULL != (mess)))
        {
            vPortFree(mess);
        }
        else
        {
            break;
        }
    } while (pdTRUE == err);

 #elif   (BSP_CFG_RTOS == 1)
    USB_REL_BLK(1, ptr);
    if ((USB_MIN_PIPE_NO > pipe_no) || (USB_MAXPIPE_NUM < pipe_no))
    {
        return;
    }

    /* WAIT_LOOP */
    do
    {
        /** Receive message from queue specified by *(mbx_table[id]) **/
        err = tx_queue_receive(&g_pipe_hdl[ip][pipe_no], (void *) &mess, TX_NO_WAIT);
        if ((TX_SUCCESS == err) && (NULL != mess))
        {
            USB_REL_BLK(1, mess);
        }
        else
        {
            break;
        }
    } while (TX_SUCCESS == err);
 #endif
}

/******************************************************************************
 * End of function usb_cstd_pipe_msg_clear
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_pipe0_msg_clear
 * Description     : Message clear for PIPE0 Transfer wait que.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  dev_addr   : device address
 * Return          : none
 ******************************************************************************/
void usb_cstd_pipe0_msg_clear (usb_utr_t * ptr, uint16_t dev_addr)
{
 #if   (BSP_CFG_RTOS == 2)
    BaseType_t err;
 #elif   (BSP_CFG_RTOS == 1)
    uint32_t err;
 #endif
    usb_msg_t * mess;
    uint16_t    ip;

    ip = ptr->ip;

 #if   (BSP_CFG_RTOS == 2)
    vPortFree(ptr);
    if ((USB_DEVICEADDR > dev_addr) || (USB_MAXDEVADDR < dev_addr))
    {
        return;
    }

    /* WAIT_LOOP */
    do
    {
        /** Receive message from queue specified by *(mbx_table[id]) **/
        err = xQueueReceive(g_pipe0_hdl[ip][dev_addr], (void *) &mess, (TickType_t) (0));
        if ((pdTRUE == err) && (NULL != (mess)))
        {
            vPortFree(mess);
        }
        else
        {
            break;
        }
    } while (pdTRUE == err);

 #elif (BSP_CFG_RTOS == 1)
    USB_REL_BLK(1, ptr);
    if ((USB_DEVICEADDR > dev_addr) || (USB_MAXDEVADDR < dev_addr))
    {
        return;
    }

    /* WAIT_LOOP */
    do
    {
        err = tx_queue_receive(&g_pipe_hdl[ip][dev_addr], (void *) &mess, TX_NO_WAIT);
        if ((TX_SUCCESS == err) && (NULL != mess))
        {
            USB_REL_BLK(1, mess);
        }
        else
        {
            break;
        }
    } while (TX_SUCCESS == err);

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    tx_semaphore_put(&g_usb_host_usbx_sem[ptr->ip][0]);
  #endif                               /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */
 #endif
}

/******************************************************************************
 * End of function usb_cstd_pipe0_msg_clear
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_pipe_msg_re_forward
 * Description     : Get PIPE Transfer wait que and Message send to HCD/PCD
 * Argument        : uint16_t  pipe_no    : Pipe no.
 * Return          : none
 ******************************************************************************/
void usb_cstd_pipe_msg_re_forward (uint16_t ip_no, uint16_t pipe_no)
{
 #if   (BSP_CFG_RTOS == 2)
    BaseType_t err;
 #elif   (BSP_CFG_RTOS == 1)
    uint32_t err;
 #endif
    usb_msg_t   * mess;
    rtos_mbx_id_t handle;
    uint8_t       id;

    if ((USB_MIN_PIPE_NO > pipe_no) || (USB_MAXPIPE_NUM < pipe_no))
    {
        return;
    }

 #if   (BSP_CFG_RTOS == 2)

    /** Receive message from queue specified by *(mbx_table[id]) **/
    err = xQueueReceive(g_pipe_hdl[ip_no][pipe_no], (void *) &mess, (TickType_t) (0));
    if ((pdTRUE == err) && (NULL != (mess)))
    {
        if (USB_MODE_HOST == g_usb_usbmode[ip_no])
        {
            id = USB_HCD_MBX;
        }
        else
        {
            id = USB_PCD_MBX;
        }

        handle = (*(g_mbx_table[id]));

        /** Send message to queue specified by *(mbx_table[id]) **/
        xQueueSend(handle, (const void *) &mess, (TickType_t) (0));
    }

 #elif   (BSP_CFG_RTOS == 1)

    /** Receive message from queue specified by *(mbx_table[id]) **/
    err = tx_queue_receive(&g_pipe_hdl[ip_no][pipe_no], (void *) &mess, TX_NO_WAIT);
    if ((TX_SUCCESS == err) && (NULL != mess))
    {
        if (USB_MODE_HOST == g_usb_usbmode[ip_no])
        {
            id = USB_HCD_MBX;
        }
        else
        {
            id = USB_PCD_MBX;
        }

        handle = (*(g_mbx_table[id]));

        /** Send message to queue specified by *(mbx_table[id]) **/
        tx_queue_send(&handle, (void *) &mess, TX_NO_WAIT);
    }
 #endif
}

/******************************************************************************
 * End of function usb_cstd_pipe_msg_re_forward
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_pipe0_msg_re_forward
 * Description     : Get PIPE0 Transfer wait que and Message send to HCD/PCD
 * Argument        : none
 * Return          : none
 ******************************************************************************/
void usb_cstd_pipe0_msg_re_forward (uint16_t ip_no)
{
 #if   (BSP_CFG_RTOS == 2)
    BaseType_t err;
 #elif   (BSP_CFG_RTOS == 1)
    uint32_t err;
 #endif
    usb_msg_t   * mess;
    rtos_mbx_id_t handle;
    uint8_t       id;
    uint8_t       dev_addr;

    /* WAIT_LOOP */
    for (dev_addr = 0; dev_addr < USB_MAXDEVADDR; dev_addr++)
    {
 #if   (BSP_CFG_RTOS == 2)

        /** Receive message from queue specified by *(mbx_table[id]) **/
        err = xQueueReceive(g_pipe0_hdl[ip_no][dev_addr], (void *) &mess, (TickType_t) (0));
        if ((pdTRUE == err) && (NULL != (mess)))
        {
            if (USB_MODE_HOST == g_usb_usbmode[ip_no])
            {
                id = USB_HCD_MBX;
            }
            else
            {
                id = USB_PCD_MBX;
            }

            handle = (*(g_mbx_table[id]));

            /** Send message to queue specified by *(mbx_table[id]) **/
            xQueueSend(handle, (const void *) &mess, (TickType_t) (0));

            return;
        }

 #elif   (BSP_CFG_RTOS == 1)

        /** Receive message from queue specified by *(mbx_table[id]) **/
        err = tx_queue_receive(&g_pipe0_hdl[ip_no][dev_addr], (void *) &mess, TX_NO_WAIT);
        if ((TX_SUCCESS == err) && (NULL != mess))
        {
            if (USB_MODE_HOST == g_usb_usbmode[ip_no])
            {
                id = USB_HCD_MBX;
            }
            else
            {
                id = USB_PCD_MBX;
            }

            handle = (*(g_mbx_table[id]));

            /** Send message to queue specified by *(mbx_table[id]) **/
            tx_queue_send(&handle, (void *) &mess, TX_NO_WAIT);
        }
 #endif
    }
}

/******************************************************************************
 * End of function usb_cstd_pipe0_msg_re_forward
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_pipe_msg_forward
 * Description     : Message foward to PIPE Transfer wait que.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  pipe_no    : Pipe no.
 * Return          : none
 ******************************************************************************/
void usb_cstd_pipe_msg_forward (usb_utr_t * ptr, uint16_t pipe_no)
{
    if ((USB_MIN_PIPE_NO > pipe_no) || (USB_MAXPIPE_NUM < pipe_no))
    {
        return;
    }

 #if   (BSP_CFG_RTOS == 2)

    /** Send message to queue specified by *(mbx_table[id]) **/
    xQueueSend(g_pipe_hdl[ptr->ip][pipe_no], (const void *) &ptr, (TickType_t) (0));
 #elif   (BSP_CFG_RTOS == 1)
    tx_queue_send(&g_pipe_hdl[ptr->ip][pipe_no], (void *) &ptr, TX_NO_WAIT);
 #endif                                /* #if (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_cstd_pipe_msg_forward
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cstd_pipe0_msg_forward
 * Description     : Message foward to PIPE0 Transfer wait que.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  dev_addr   : device address
 * Return          : none
 ******************************************************************************/
void usb_cstd_pipe0_msg_forward (usb_utr_t * ptr, uint16_t dev_addr)
{
    if ((USB_DEVICEADDR > dev_addr) || (USB_MAXDEVADDR < dev_addr))
    {
        return;
    }

 #if   (BSP_CFG_RTOS == 2)

    /** Send message to queue specified by *(mbx_table[id]) **/
    xQueueSend(g_pipe0_hdl[ptr->ip][dev_addr], (const void *) &ptr, (TickType_t) (0));
 #elif   (BSP_CFG_RTOS == 1)
    tx_queue_send(&g_pipe_hdl[ptr->ip][dev_addr], (void *) &ptr, TX_NO_WAIT);
 #endif                                /* #if (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_cstd_pipe0_msg_forward
 ******************************************************************************/

#endif                                 /* #if (BSP_CFG_RTOS != 0) */
