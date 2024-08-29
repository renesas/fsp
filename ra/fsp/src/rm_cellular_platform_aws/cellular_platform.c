/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
