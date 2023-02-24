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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include <stdlib.h>

#include "r_ble_api.h"

#include "fsp_common_api.h"

#if (BSP_CFG_RTOS == 1)
 #include "tx_api.h"
#elif (BSP_CFG_RTOS == 2)
 #include "FreeRTOS.h"
 #include "task.h"
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 0)
  #include "semphr.h"
 #else
  #include "event_groups.h"
 #endif
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if (BSP_CFG_RTOS == 2)
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 1)
  #define BLE_EVENT_PATTERN    (0x0A0A)
 #endif
#endif

/***********************************************************************************************************************
 * Local Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions
 **********************************************************************************************************************/

void    r_ble_rf_control_error(uint32_t err_no);
uint8_t r_ble_rf_power_save_mode(void);

#if (BSP_CFG_RTOS == 1) || (BSP_CFG_RTOS == 2)
void r_ble_wake_up_task(void * EventGroupHandle);
void r_ble_wake_up_task_from_isr(void * EventGroupHandle);

#endif

/*** platform control functions added start ***/

void r_ble_rf_control_error (uint32_t err_no)
{
    FSP_PARAMETER_NOT_USED(err_no);
}

uint8_t r_ble_rf_power_save_mode (void)
{
    uint8_t ret = BLE_CFG_RF_DEEP_SLEEP_EN;

    return ret;
}

/*** platform control functions end ***/

#if (BSP_CFG_RTOS == 1)
void r_ble_wake_up_task (void * EventGroupHandle)
{
    if (NULL != EventGroupHandle)
    {
        tx_semaphore_put((TX_SEMAPHORE *) EventGroupHandle);
    }
}

void r_ble_wake_up_task_from_isr (void * EventGroupHandle)
{
    if (NULL != EventGroupHandle)
    {
        tx_semaphore_put((TX_SEMAPHORE *) EventGroupHandle);
    }
}

#elif (BSP_CFG_RTOS == 2)
void r_ble_wake_up_task (void * EventGroupHandle)
{
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 0)

    /* Semaphore notifications */
    SemaphoreHandle_t semaphore_handle = (SemaphoreHandle_t) EventGroupHandle;

    if (NULL != EventGroupHandle)
    {
        xSemaphoreGive(semaphore_handle);
    }
 #else
    EventGroupHandle_t event_group_handle = (EventGroupHandle_t) EventGroupHandle;

    /* Event flag notifications */

    if (event_group_handle != NULL)
    {
        xEventGroupSetBits(event_group_handle, (EventBits_t) BLE_EVENT_PATTERN);
        portYIELD();
    }
 #endif
}

void r_ble_wake_up_task_from_isr (void * EventGroupHandle)
{
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;
 #if (BLE_CFG_SYNCHRONIZATION_TYPE == 0)

    /* Semaphore notifications */
    SemaphoreHandle_t semaphore_handle = (SemaphoreHandle_t) EventGroupHandle;

    if (NULL != EventGroupHandle)
    {
        xSemaphoreGiveFromISR(semaphore_handle, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
 #else

    /* Event flag notifications */
    EventGroupHandle_t event_group_handle = (EventGroupHandle_t) EventGroupHandle;

    if (event_group_handle != NULL)
    {
        xEventGroupSetBitsFromISR(event_group_handle, (EventBits_t) BLE_EVENT_PATTERN, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
 #endif
}

#endif
