/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#include <stdbool.h>

#include "cellular_platform.h"

/*-----------------------------------------------------------*/

typedef struct threadInfo
{
    void * pArgument;                  /**< @brief Argument to `threadRoutine`. */
    void (* threadRoutine)(void *);    /**< @brief Thread function to run. */
} threadInfo_t;

/*-----------------------------------------------------------*/

/**
 * @brief Sends provided buffer to network using transport send.
 *
 * @param[in] pArgument Argument passed to threadRoutine function.
 *
 */
static void prvThreadRoutineWrapper(void * pArgument);

/**
 * @brief Lock mutex with timeout.
 *
 * @param[in] pMutex Mutex to lock.
 * @param[in] timeout Timeout value to lock mutex.
 *
 * @return ture if mutex is locked successfully. Otherwise false.
 */
static bool prIotMutexTimedLock(PlatformMutex_t * pMutex, TickType_t timeout);

/*-----------------------------------------------------------*/

static void prvThreadRoutineWrapper (void * pArgument)
{
    threadInfo_t * pThreadInfo = (threadInfo_t *) pArgument;

    /* Run the thread routine. */
    pThreadInfo->threadRoutine(pThreadInfo->pArgument);
    Platform_Free(pThreadInfo);

    vTaskDelete(NULL);
}

/*-----------------------------------------------------------*/

static bool prIotMutexTimedLock (PlatformMutex_t * pMutex, TickType_t timeout)
{
    BaseType_t lockResult = pdTRUE;

    configASSERT(pMutex != NULL);

    LogDebug(("Locking mutex %p.", pMutex));

    /* Call the correct FreeRTOS mutex take function based on mutex type. */
    if (pMutex->recursive == pdTRUE)
    {
        lockResult = xSemaphoreTakeRecursive((SemaphoreHandle_t) &pMutex->xMutex, timeout);
    }
    else
    {
        lockResult = xSemaphoreTake((SemaphoreHandle_t) &pMutex->xMutex, timeout);
    }

    return lockResult == pdTRUE;
}

/*-----------------------------------------------------------*/

bool Platform_CreateDetachedThread (void ( * threadRoutine)(void *),
                                    void   * pArgument,
                                    uint32_t priority,
                                    size_t   stackSize)
{
    bool           status      = true;
    threadInfo_t * pThreadInfo = NULL;

    configASSERT(threadRoutine != NULL);

    LogDebug(("Creating new thread."));

    pThreadInfo = Platform_Malloc(sizeof(threadInfo_t));

    if (pThreadInfo == NULL)
    {
        LogDebug(("Unable to allocate memory for threadRoutine %p.", (void *) threadRoutine));
        status = false;
    }

    /* Create the FreeRTOS task that will run the thread. */
    if (status == true)
    {
        pThreadInfo->threadRoutine = threadRoutine;
        pThreadInfo->pArgument     = pArgument;

        if (xTaskCreate(prvThreadRoutineWrapper, "Cellular_Thread", (configSTACK_DEPTH_TYPE) stackSize, pThreadInfo,
                        priority, NULL) != pdPASS)
        {
            /* Task creation failed. */
            LogWarn(("Failed to create thread."));
            Platform_Free(pThreadInfo);
            status = false;
        }
        else
        {
            LogDebug(("New thread created."));
        }
    }

    return status;
}

/*-----------------------------------------------------------*/

bool PlatformMutex_Create (PlatformMutex_t * pNewMutex, bool recursive)
{
    SemaphoreHandle_t xSemaphore     = NULL;
    bool              retMutexCreate = false;

    configASSERT(pNewMutex != NULL);

    LogDebug(("Creating new mutex %p.", pNewMutex));

    if (recursive == true)
    {
        xSemaphore = xSemaphoreCreateRecursiveMutexStatic(&pNewMutex->xMutex);
    }
    else
    {
        xSemaphore = xSemaphoreCreateMutexStatic(&pNewMutex->xMutex);
    }

    /* Remember the type of mutex. */
    if (recursive == true)
    {
        pNewMutex->recursive = pdTRUE;
    }
    else
    {
        pNewMutex->recursive = pdFALSE;
    }

    /* Check the handle value returned by the mutex create function. */
    if (xSemaphore == NULL)
    {
        retMutexCreate = false;
    }
    else
    {
        retMutexCreate = true;
    }

    return retMutexCreate;
}

/*-----------------------------------------------------------*/

void PlatformMutex_Destroy (PlatformMutex_t * pMutex)
{
    configASSERT(pMutex != NULL);

    vSemaphoreDelete((SemaphoreHandle_t) &pMutex->xMutex);
}

/*-----------------------------------------------------------*/

void PlatformMutex_Lock (PlatformMutex_t * pMutex)
{
    prIotMutexTimedLock(pMutex, portMAX_DELAY);
}

/*-----------------------------------------------------------*/

bool PlatformMutex_TryLock (PlatformMutex_t * pMutex)
{
    return prIotMutexTimedLock(pMutex, 0);
}

/*-----------------------------------------------------------*/

void PlatformMutex_Unlock (PlatformMutex_t * pMutex)
{
    configASSERT(pMutex != NULL);

    LogDebug(("Unlocking mutex %p.", pMutex));

    /* Call the correct FreeRTOS mutex unlock function based on mutex type. */
    if (pMutex->recursive == pdTRUE)
    {
        (void) xSemaphoreGiveRecursive((SemaphoreHandle_t) &pMutex->xMutex);
    }
    else
    {
        (void) xSemaphoreGive((SemaphoreHandle_t) &pMutex->xMutex);
    }
}

/*-----------------------------------------------------------*/
