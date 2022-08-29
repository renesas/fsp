#ifndef RM_CELLULAR_PLATFORM_AWS_H
#define RM_CELLULAR_PLATFORM_AWS_H

/*******************************************************************************************************************//**
 * @addtogroup RM_CELLULAR_PLATFORM_AWS
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
 #include "FreeRTOS.h"
 #include "queue.h"
 #include "semphr.h"
 #include "event_groups.h"
 #include "task.h"
#endif

#include "cellular_config.h"
#include "cellular_config_defaults.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**
 * @brief Cellular library platform event group APIs.
 *
 * Cellular library use platform event group for process synchronization.
 *
 * The EventGroup functions in the following link can be referenced as function prototype.
 * https://www.freertos.org/event-groups-API.html
 *
 */

#define Platform_Delay(delayMs)    vTaskDelay(pdMS_TO_TICKS(delayMs))

#define PlatformEventGroupHandle_t           EventGroupHandle_t
#define PlatformEventGroup_Delete            vEventGroupDelete
#define PlatformEventGroup_ClearBits         xEventGroupClearBits
#define PlatformEventGroup_Create            xEventGroupCreate
#define PlatformEventGroup_GetBits           xEventGroupGetBits
#define PlatformEventGroup_SetBits           xEventGroupSetBits
#define PlatformEventGroup_SetBitsFromISR    xEventGroupSetBitsFromISR
#define PlatformEventGroup_WaitBits          xEventGroupWaitBits
#define PlatformEventGroup_EventBits         EventBits_t

#define PlatformTickType                     TickType_t

/* Converts a time in milliseconds to a time in ticks.  This macro can be
 * overridden by a macro of the same name defined in FreeRTOSConfig.h in case the
 * definition here is not suitable for your application. */
#ifndef pdMS_TO_TICKS
 #define pdMS_TO_TICKS(xTimeInMs)    ((TickType_t) (((TickType_t) (xTimeInMs) * (TickType_t) 1000) / \
                                                    (TickType_t) 1000U))
#endif

/**
 * @brief Cellular library platform thread API and configuration.
 *
 * Cellular library create a detached thread by this API.
 * The threadRoutine should be called with pArgument in the created thread.
 *
 * PLATFORM_THREAD_DEFAULT_STACK_SIZE and PLATFORM_THREAD_DEFAULT_PRIORITY defines
 * the platform related stack size and priority.
 */

bool Platform_CreateDetachedThread(void ( * threadRoutine)(void *),
                                   void   * pArgument,
                                   uint32_t priority,
                                   size_t   stackSize);

#define PLATFORM_THREAD_DEFAULT_STACK_SIZE    (2048U)
#define PLATFORM_THREAD_DEFAULT_PRIORITY      (configMAX_PRIORITIES - 1)

/*-----------------------------------------------------------*/

/**
 * @brief Cellular library platform mutex APIs.
 *
 * Cellular library use platform mutex to protect resource.
 *
 * The IotMutex_ functions can be referenced as function prototype for
 * PlatfromMutex_ prefix function in the following link.
 * https://docs.aws.amazon.com/freertos/latest/lib-ref/c-sdk/platform/platform_threads_functions.html
 *
 */

// typedef long BaseType_t;
typedef struct PlatformMutex
{
    StaticSemaphore_t xMutex;          /**< FreeRTOS mutex. */
    BaseType_t        recursive;       /**< Type; used for indicating if this is reentrant or normal. */
    bool              created;
} PlatformMutex_t;

bool PlatformMutex_Create(PlatformMutex_t * pNewMutex, bool recursive);
void PlatformMutex_Destroy(PlatformMutex_t * pMutex);
void PlatformMutex_Lock(PlatformMutex_t * pMutex);
bool PlatformMutex_TryLock(PlatformMutex_t * pMutex);
void PlatformMutex_Unlock(PlatformMutex_t * pMutex);

/*-----------------------------------------------------------*/

/**
 * @brief Cellular library platform memory allocation APIs.
 *
 * Cellular library use platform memory allocation APIs to allocate memory dynamically.
 * The FreeRTOS memory management document can be referenced for these APIs.
 * https://www.freertos.org/a00111.html
 *
 */

#define Platform_Malloc    pvPortMalloc
#define Platform_Free      vPortFree

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_CELLULAR_PLATFORM_AWS)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
