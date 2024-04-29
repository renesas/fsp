/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#include "r_usb_basic.h"
#include "r_usb_typedef.h"

#if (BSP_CFG_RTOS != 0)

 #if (BSP_CFG_RTOS == 2)
  #include "FreeRTOS.h"
  #include "task.h"
  #include "queue.h"
 #elif   (BSP_CFG_RTOS == 1)
  #include "tx_api.h"
 #endif

 #ifndef R_USB_CSTD_RTOS_H
  #define R_USB_CSTD_RTOS_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

  #if (BSP_CFG_RTOS == 2)
typedef TaskHandle_t      rtos_task_id_t;
typedef QueueHandle_t     rtos_mbx_id_t;
typedef QueueHandle_t     rtos_mem_id_t;
typedef SemaphoreHandle_t rtos_sem_id_t;
typedef TickType_t        rtos_time_t;

/** USB task's priority **/
   #define HCD_TSK_PRI     (configMAX_PRIORITIES - 1)
   #define HUB_TSK_PRI     (configMAX_PRIORITIES - 3)
   #define MGR_TSK_PRI     (configMAX_PRIORITIES - 2)
   #define PCD_TSK_PRI     (configMAX_PRIORITIES - 1)
   #define PMSC_TSK_PRI    (configMAX_PRIORITIES - 2)

  #elif   (BSP_CFG_RTOS == 1)
typedef TX_THREAD    rtos_task_id_t;
typedef TX_QUEUE     rtos_mbx_id_t;
typedef TX_BYTE_POOL rtos_mem_id_t;
typedef TX_SEMAPHORE rtos_sem_id_t;
typedef uint32_t     rtos_time_t;

   #define USB_TASK_PRI_BASE    (10)
   #define HCD_TSK_PRI          (USB_TASK_PRI_BASE)
   #define HUB_TSK_PRI          (HCD_TSK_PRI + 2)
   #define MGR_TSK_PRI          (HCD_TSK_PRI + 1)
   #define PCD_TSK_PRI          (USB_TASK_PRI_BASE)
   #define PMSC_TSK_PRI         (PCD_TSK_PRI + 1)

  #endif                               /* (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/** Size of a queue **/
  #define QUEUE_SIZE          (10)

/** USB task stack size in words **/
  #if (BSP_CFG_RTOS == 1)
   #if defined(USB_CFG_HMSC_USE)
    #define HCD_STACK_SIZE    (2048)
    #define MGR_STACK_SIZE    (2048)
   #else

// #define HCD_STACK_SIZE    (1536)
// #define MGR_STACK_SIZE    (1536)
    #define HCD_STACK_SIZE    (1536 + 1024)
    #define MGR_STACK_SIZE    (1536 + 1024)
   #endif
   #define HUB_STACK_SIZE     (512)
   #define PCD_STACK_SIZE     (1024)
   #define PMSC_STACK_SIZE    (512)
   #define HCDC_STACK_SIZE    (512)
   #define HHID_STACK_SIZE    (512)
  #elif (BSP_CFG_RTOS == 2)            /* #if (BSP_CFG_RTOS == 1) */
   #define HCD_STACK_SIZE     (512)
   #define HUB_STACK_SIZE     (512)
   #define MGR_STACK_SIZE     (512)
   #define PCD_STACK_SIZE     (512)
   #define PMSC_STACK_SIZE    (512)
   #define HCDC_STACK_SIZE    (512)
   #define HHID_STACK_SIZE    (512)
  #endif                               /* #if (BSP_CFG_RTOS == 1) */
/* Number of Memory Block */
  #define    NUM_OF_BLOCK     (8)

/******************************************************************************
 * Typedef definitions
 ******************************************************************************/
typedef enum e_usb_rtos_err
{
    UsbRtos_Success = 0,                   // Successful
    UsbRtos_Err_Init_Mbx,                  // Failure of Mailbox Creation
    UsbRtos_Err_Init_Mpl,                  // Failure of Memory Pool Creation
    UsbRtos_Err_Init_Tsk,                  // Failure of Task Creation
    UsbRtos_Err_Init_Sem,                  // Failure of Semaphore Creation
    UsbRtos_Err_Delete_Mbx,                // Failure of Mailbox Delete
    UsbRtos_Err_Delete_Mpl,                // Failure of Memory Pool Delete
    UsbRtos_Err_Delete_Tsk,                // Failure of Task Delete
  #if defined(USB_CFG_OTG_USE)
    UsbRtos_Err_Init_OTG_Detach_Tmr,       // Failure of OTG Detach Timer Creation
    UsbRtos_Err_Delete_OTG_Detach_Tmr,     // Failure of OTG Detach Timer Delete
    UsbRtos_Err_Init_OTG_Chattering_Tmr,   // Failure of OTG Chattering Timer Creation
    UsbRtos_Err_Delete_OTG_Chattering_Tmr, // Failure of OTG Chattering Timer Creation
    UsbRtos_Err_Init_OTG_HNP_Tmr,          // Failure of OTG HNP Timer Creation
    UsbRtos_Err_Delete_OTG_HNP_Tmr,        // Failure of OTG HNP Timer Delete
  #endif /* defined(USB_CFG_OTG_USE) */
} usb_rtos_err_t;

/******************************************************************************
 * Exported global variables
 ******************************************************************************/
extern rtos_mbx_id_t * g_mbx_table[];
extern rtos_mem_id_t * g_mpl_table[];

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/
usb_rtos_err_t usb_rtos_configuration(usb_mode_t usb_mode);
usb_rtos_err_t usb_rtos_delete(uint8_t module_number);

 #endif                                /* #if (BSP_CFG_RTOS != 0) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_CSTD_RTOS_H */
