/*
 * FreeRTOS+FAT Labs Build 160919a (C) 2016 Real Time Engineers ltd.
 * Authors include James Walmsley, Hein Tibosch and Richard Barry
 *
 *******************************************************************************
 ***** NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ***
 ***                                                                         ***
 ***                                                                         ***
 ***   FREERTOS+FAT IS STILL IN THE LAB:                                     ***
 ***                                                                         ***
 ***   Be aware we are still refining the FreeRTOS+FAT design,               ***
 ***   the source code does not yet fully conform to the strict quality and  ***
 ***   style standards mandated by Real Time Engineers ltd., and the         ***
 ***   documentation and testing is not necessarily complete.                ***
 ***                                                                         ***
 ***   PLEASE REPORT EXPERIENCES USING THE SUPPORT RESOURCES FOUND ON THE    ***
 ***   URL: http://www.FreeRTOS.org/contact  Active early adopters may, at   ***
 ***   the sole discretion of Real Time Engineers Ltd., be offered versions  ***
 ***   under a license other than that described below.                      ***
 ***                                                                         ***
 ***                                                                         ***
 ***** NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ***
 *******************************************************************************
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 1 tab == 4 spaces!
 *
 * http://www.FreeRTOS.org
 * http://www.FreeRTOS.org/plus
 * http://www.FreeRTOS.org/labs
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp_api.h"

/* Scheduler include files. */
#if 2 == BSP_CFG_RTOS
#include "FreeRTOS.h"
#endif
#include "ff_headers.h"
#if 2 == BSP_CFG_RTOS
#include "event_groups.h"

#ifndef configUSE_RECURSIVE_MUTEXES
	#error configUSE_RECURSIVE_MUTEXES must be set to 1 in FreeRTOSConfig.h
#else
	#if( configUSE_RECURSIVE_MUTEXES != 1 )
		#error configUSE_RECURSIVE_MUTEXES must be set to 1 in FreeRTOSConfig.h
	#endif
#endif /* configUSE_RECURSIVE_MUTEXES */

#if ( INCLUDE_vTaskDelay != 1 )
	#error Missing some FreeRTOS define
#endif

/* There are two areas which are protected with a semaphore:
Directories and the FAT area.
The masks below are used when calling Group Event functions. */
#define FF_FAT_LOCK_EVENT_BITS    ( ( const EventBits_t ) FF_FAT_LOCK )
#define FF_DIR_LOCK_EVENT_BITS    ( ( const EventBits_t ) FF_DIR_LOCK )

/* This is not a real lock: it is a bit (or semaphore) will will be given
each time when a sector buffer is released. */
#define FF_BUF_LOCK_EVENT_BITS    ( ( const EventBits_t ) FF_BUF_LOCK )
#endif

/*-----------------------------------------------------------*/

BaseType_t FF_TrySemaphore( void *pxSemaphore, uint32_t ulTime_ms )
{
#if 2 == BSP_CFG_RTOS
BaseType_t xReturn;

	configASSERT( pxSemaphore );
	xReturn = xSemaphoreTakeRecursive( ( SemaphoreHandle_t ) pxSemaphore, pdMS_TO_TICKS( ulTime_ms ) );
	return xReturn;
#else
	FSP_PARAMETER_NOT_USED(pxSemaphore);
	FSP_PARAMETER_NOT_USED(ulTime_ms);
	return pdPASS;
#endif
}
/*-----------------------------------------------------------*/

void FF_PendSemaphore( void *pxSemaphore )
{
#if 2 == BSP_CFG_RTOS
	configASSERT( pxSemaphore );
	xSemaphoreTakeRecursive( ( SemaphoreHandle_t ) pxSemaphore, portMAX_DELAY );
#else
	FSP_PARAMETER_NOT_USED(pxSemaphore);
#endif
}
/*-----------------------------------------------------------*/

void FF_ReleaseSemaphore( void *pxSemaphore )
{
#if 2 == BSP_CFG_RTOS
	configASSERT( pxSemaphore );
	xSemaphoreGiveRecursive( ( SemaphoreHandle_t ) pxSemaphore );
#else
	FSP_PARAMETER_NOT_USED(pxSemaphore);
#endif
}
/*-----------------------------------------------------------*/

void FF_Sleep( uint32_t ulTime_ms )
{
#if 2 == BSP_CFG_RTOS
	vTaskDelay( pdMS_TO_TICKS( ulTime_ms ) );
#else
	FSP_PARAMETER_NOT_USED(ulTime_ms);
#endif
}
/*-----------------------------------------------------------*/

void FF_DeleteEvents( FF_IOManager_t *pxIOManager )
{
#if 2 == BSP_CFG_RTOS
	if( pxIOManager->xEventGroup != NULL )
	{
		vEventGroupDelete( pxIOManager->xEventGroup );
	}
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
#endif
}
/*-----------------------------------------------------------*/

BaseType_t FF_CreateEvents( FF_IOManager_t *pxIOManager )
{
#if 2 == BSP_CFG_RTOS
BaseType_t xResult;

	pxIOManager->xEventGroup = xEventGroupCreate();
	if( pxIOManager->xEventGroup != NULL )
	{
		xEventGroupSetBits( pxIOManager->xEventGroup,
			FF_FAT_LOCK_EVENT_BITS | FF_DIR_LOCK_EVENT_BITS | FF_BUF_LOCK_EVENT_BITS );
		xResult = pdTRUE;
	}
	else
	{
		xResult = pdFALSE;
	}

	return xResult;
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
	return pdPASS;
#endif
}
/*-----------------------------------------------------------*/

void FF_LockDirectory( FF_IOManager_t *pxIOManager )
{
#if 2 == BSP_CFG_RTOS
	EventBits_t xBits;

	for( ;; )
	{
		/* Called when a task want to make changes to a directory.
		First it waits for the desired bit to come high. */
		xEventGroupWaitBits( pxIOManager->xEventGroup,
			FF_DIR_LOCK_EVENT_BITS, /* uxBitsToWaitFor */
			( EventBits_t )0,       /* xClearOnExit */
			pdFALSE,                /* xWaitForAllBits n.a. */
			pdMS_TO_TICKS( 10000UL ) );

		/* The next operation will only succeed for 1 task at a time,
		because it is an atomary test & set operation: */
		xBits = xEventGroupClearBits( pxIOManager->xEventGroup, FF_DIR_LOCK_EVENT_BITS );

		if( ( xBits & FF_DIR_LOCK_EVENT_BITS ) != 0 )
		{
			/* This task has cleared the desired bit.
			It now 'owns' the resource. */
			break;
		}
	}
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
#endif
}
/*-----------------------------------------------------------*/

void FF_UnlockDirectory( FF_IOManager_t *pxIOManager )
{
#if 2 == BSP_CFG_RTOS
	configASSERT( ( xEventGroupGetBits( pxIOManager->xEventGroup ) & FF_DIR_LOCK_EVENT_BITS ) == 0 );
	xEventGroupSetBits( pxIOManager->xEventGroup, FF_DIR_LOCK_EVENT_BITS );
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
#endif
}
/*-----------------------------------------------------------*/

int FF_Has_Lock( FF_IOManager_t *pxIOManager, uint32_t aBits )
{
#if 2 == BSP_CFG_RTOS
int iReturn;

	void *handle = xTaskGetCurrentTaskHandle();
	if( ( aBits & FF_FAT_LOCK_EVENT_BITS ) != 0 )
	{
		if( ( pxIOManager->pvFATLockHandle != NULL ) && ( pxIOManager->pvFATLockHandle == handle ) )
		{
			iReturn = pdTRUE;
		}
		else
		{
			iReturn = pdFALSE;
		}
	}
	else
	{
		iReturn = pdFALSE;
	}
	return iReturn;
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
	FSP_PARAMETER_NOT_USED(aBits);
	return pdTRUE;
#endif
}

void FF_Assert_Lock( FF_IOManager_t *pxIOManager, uint32_t aBits )
{
#if 2 == BSP_CFG_RTOS
	void *handle = xTaskGetCurrentTaskHandle();

	if( ( aBits & FF_FAT_LOCK_EVENT_BITS ) != 0 )
	{
		configASSERT( ( pxIOManager->pvFATLockHandle != NULL ) && ( pxIOManager->pvFATLockHandle == handle ) );

		/* In case configASSERT() is not defined. */
		( void ) pxIOManager;
		( void ) handle;
	}
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
	FSP_PARAMETER_NOT_USED(aBits);
#endif
}

void FF_LockFAT( FF_IOManager_t *pxIOManager )
{
#if 2 == BSP_CFG_RTOS
EventBits_t xBits;

	configASSERT( FF_Has_Lock( pxIOManager, FF_FAT_LOCK ) == pdFALSE );

	for( ;; )
	{
		/* Called when a task want to make changes to the FAT area.
		First it waits for the desired bit to come high. */
		xEventGroupWaitBits( pxIOManager->xEventGroup,
			FF_FAT_LOCK_EVENT_BITS, /* uxBitsToWaitFor */
			( EventBits_t )0,       /* xClearOnExit */
			pdFALSE,                /* xWaitForAllBits n.a. */
			pdMS_TO_TICKS( 10000UL ) );

		/* The next operation will only succeed for 1 task at a time,
		because it is an atomary test & set operation: */
		xBits = xEventGroupClearBits( pxIOManager->xEventGroup, FF_FAT_LOCK_EVENT_BITS );

		if( ( xBits & FF_FAT_LOCK_EVENT_BITS ) != 0 )
		{
			/* This task has cleared the desired bit.
			It now 'owns' the resource. */
			pxIOManager->pvFATLockHandle = xTaskGetCurrentTaskHandle();
			break;
		}
	}
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
#endif
}
/*-----------------------------------------------------------*/

void FF_UnlockFAT( FF_IOManager_t *pxIOManager )
{
#if 2 == BSP_CFG_RTOS
	configASSERT( ( xEventGroupGetBits( pxIOManager->xEventGroup ) & FF_FAT_LOCK_EVENT_BITS ) == 0 );
	pxIOManager->pvFATLockHandle = NULL;
	xEventGroupSetBits( pxIOManager->xEventGroup, FF_FAT_LOCK_EVENT_BITS );
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
#endif
}
/*-----------------------------------------------------------*/

BaseType_t FF_BufferWait( FF_IOManager_t *pxIOManager, uint32_t xWaitMS )
{
#if 2 == BSP_CFG_RTOS
EventBits_t xBits;
BaseType_t xReturn;

	/* This function is called when a task is waiting for a sector buffer
	to become available. */
	xBits = xEventGroupWaitBits( pxIOManager->xEventGroup,
		FF_BUF_LOCK_EVENT_BITS, /* uxBitsToWaitFor */
		FF_BUF_LOCK_EVENT_BITS, /* xClearOnExit */
		pdFALSE,                /* xWaitForAllBits n.a. */
		pdMS_TO_TICKS( xWaitMS ) );
	if( ( xBits & FF_BUF_LOCK_EVENT_BITS ) != 0 )
	{
		xReturn = pdTRUE;
	}
	else
	{
		xReturn = pdFALSE;
	}

	return xReturn;
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
	FSP_PARAMETER_NOT_USED(xWaitMS);
	return pdTRUE;
#endif
}
/*-----------------------------------------------------------*/

void FF_BufferProceed( FF_IOManager_t *pxIOManager )
{
#if 2 == BSP_CFG_RTOS
	/* Wake-up all tasks that are waiting for a sector buffer to become available. */
	xEventGroupSetBits( pxIOManager->xEventGroup, FF_BUF_LOCK_EVENT_BITS );
#else
	FSP_PARAMETER_NOT_USED(pxIOManager);
#endif
}
/*-----------------------------------------------------------*/

#if 2 != BSP_CFG_RTOS
void vTaskSuspendAll( void )
{
	/* Do nothing. */
}
BaseType_t xTaskResumeAll( void )
{
	return pdTRUE;
}

void vPortEnterCritical (void)
{
	/* Do nothing. */
}
void vPortExitCritical (void)
{
	/* Do nothing. */
}

#if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )
/* Each task has its own Current Working Directory (CWD).  The CWD is used
to extend relative paths to absolute paths. */
typedef struct WORKING_DIR
{
	char pcCWD[ ffconfigMAX_FILENAME ];		/* The current working directory. */
	char pcFileName[ ffconfigMAX_FILENAME ];	/* The created absolute path. */
} WorkingDirectory_t;

WorkingDirectory_t g_ff_cwd;
void *pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery, BaseType_t xIndex )
{
	FSP_PARAMETER_NOT_USED(xTaskToQuery);
	FSP_PARAMETER_NOT_USED(xIndex);
	return &g_ff_cwd;
}
void vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet, BaseType_t xIndex, void *pvValue )
{
	FSP_PARAMETER_NOT_USED(xTaskToSet);
	FSP_PARAMETER_NOT_USED(xIndex);
	FSP_PARAMETER_NOT_USED(pvValue);
}
#endif

#endif
