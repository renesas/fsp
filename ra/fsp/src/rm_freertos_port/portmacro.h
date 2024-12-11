/*
 * FreeRTOS Kernel
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 */

#ifndef PORTMACRO_H
 #define PORTMACRO_H

 #ifdef __cplusplus
extern "C" {
 #endif

 #include "bsp_api.h"

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE ensures that PRIVILEGED_FUNCTION
 * is defined correctly and privileged functions are placed in correct sections. */
 #define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

 #include "mpu_wrappers.h"

/* MPU_WRAPPERS_INCLUDED_FROM_API_FILE is needed to be defined only for the
 * header files. */
 #undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Needed for definitions of pdFALSE and pdTRUE. */
 #include "projdefs.h"

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
 #define portCHAR          char
 #define portFLOAT         float
 #define portDOUBLE        double
 #define portLONG          long
 #define portSHORT         short
 #define portSTACK_TYPE    uint32_t
 #define portBASE_TYPE     long

/* Structure passed to pvParameters when task creation code is generated. */
typedef struct st_rm_freertos_port_parameters
{
    void * p_context;                  // Pointer to user data
} rm_freertos_port_parameters_t;

typedef portSTACK_TYPE StackType_t;
typedef long           BaseType_t;
typedef unsigned long  UBaseType_t;

 #if (configUSE_16_BIT_TICKS == 1)
typedef uint16_t TickType_t;
  #define portMAX_DELAY              (TickType_t) 0xffff
 #else
typedef uint32_t TickType_t;
  #define portMAX_DELAY              (TickType_t) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
  #define portTICK_TYPE_IS_ATOMIC    1
 #endif

/*-----------------------------------------------------------*/

/* Architecture specifics. */
 #define portSTACK_GROWTH                    (-1)
 #define portTICK_PERIOD_MS                  ((TickType_t) 1000 / configTICK_RATE_HZ)
 #define portBYTE_ALIGNMENT                  8
 #define portDONT_DISCARD                    BSP_DONT_REMOVE

 #if BSP_FEATURE_BSP_HAS_SP_MON || defined(RENESAS_CORTEX_M33) || defined(RENESAS_CORTEX_M85)
  #define portHAS_STACK_OVERFLOW_CHECKING    (1)
 #endif

/*-----------------------------------------------------------*/

/**
 * @brief SVC numbers.
 */
 #define portSVC_ALLOCATE_SECURE_CONTEXT    0
 #define portSVC_FREE_SECURE_CONTEXT        1
 #define portSVC_START_SCHEDULER            2
 #define portSVC_RAISE_PRIVILEGE            3

/*-----------------------------------------------------------*/

/* Scheduler utilities. */
 #define portYIELD()                                    \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;             \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __DSB();                                                   \
        __ISB();                                                   \
    }
 #define portEND_SWITCHING_ISR(xSwitchRequired)    if (xSwitchRequired != pdFALSE) \
        portYIELD()
 #define portYIELD_FROM_ISR(x)                     portEND_SWITCHING_ISR(x)

/*-----------------------------------------------------------*/

 #if defined(__GNUC__) && !defined(__ARMCC_VERSION) && !defined(__clang_analyzer__)
  #define RM_FREERTOS_PORT_NAKED_FUNCTION    __attribute__((naked, no_instrument_function, \
                                                            no_profile_instrument_function))
 #else
  #define RM_FREERTOS_PORT_NAKED_FUNCTION    __attribute__((naked))
 #endif

/* Critical section management. */
extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);

 #if BSP_TZ_NONSECURE_BUILD
void vPortAllocateSecureContext(uint32_t ulSecureStackSize) RM_FREERTOS_PORT_NAKED_FUNCTION;
void vPortFreeSecureContext(uint32_t * pulTCB) RM_FREERTOS_PORT_NAKED_FUNCTION PRIVILEGED_FUNCTION;

 #endif

 #if (configENABLE_MPU == 1)

BaseType_t xIsPrivileged(void) RM_FREERTOS_PORT_NAKED_FUNCTION;
void       vRaisePrivilege(void) RM_FREERTOS_PORT_NAKED_FUNCTION PRIVILEGED_FUNCTION;
void       vResetPrivilege(void) RM_FREERTOS_PORT_NAKED_FUNCTION;

 #endif

 #if defined(RENESAS_CORTEX_M4) || defined(RENESAS_CORTEX_M33) || defined(RENESAS_CORTEX_M85)
  #define RM_FREERTOS_PORT_HAS_BASEPRI    (1)
 #else
  #define RM_FREERTOS_PORT_HAS_BASEPRI    (0)
 #endif

 #if RM_FREERTOS_PORT_HAS_BASEPRI && configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY > 0

/* Set the interrupt mask and return the previous value. */
  #define portSET_INTERRUPT_MASK()                           __get_BASEPRI(); \
    __set_BASEPRI(configMAX_SYSCALL_INTERRUPT_PRIORITY); // configMAX_SYSCALL_INTERRUPT_PRIORITY is already shifted to the appropriate place for BASEPRI

/* Restore the interrupt mask to the previous value (x). */
  #define portCLEAR_INTERRUPT_MASK(x)                        __set_BASEPRI(x)

 #else

/* Set the interrupt mask and return the previous value. */
  #define portSET_INTERRUPT_MASK()                           __get_PRIMASK(); \
    __set_PRIMASK(1);

/* Restore the interrupt mask to the previous value (x). */
  #define portCLEAR_INTERRUPT_MASK(x)                        __set_PRIMASK(x)
 #endif

 #define portENTER_CRITICAL()                                vPortEnterCritical()
 #define portEXIT_CRITICAL()                                 vPortExitCritical()

 #define portDISABLE_INTERRUPTS()                            __set_PRIMASK(1)
 #define portENABLE_INTERRUPTS()                             __set_PRIMASK(0)

 #define portSET_INTERRUPT_MASK_FROM_ISR()                   portSET_INTERRUPT_MASK()
 #define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)                portCLEAR_INTERRUPT_MASK(x)

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
 #define portTASK_FUNCTION_PROTO(vFunction, pvParameters)    void vFunction(void * pvParameters)
 #define portTASK_FUNCTION(vFunction, pvParameters)          void vFunction(void * pvParameters)

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
 #ifndef portSUPPRESS_TICKS_AND_SLEEP
extern void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime);

  #define portSUPPRESS_TICKS_AND_SLEEP(xExpectedIdleTime)    vPortSuppressTicksAndSleep(xExpectedIdleTime)
 #endif

/* Idle hook, weak implementation. */
void vApplicationIdleHook(void);

/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
 #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
  #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
 #endif

 #if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
__attribute__((always_inline)) static inline uint8_t ucPortCountLeadingZeros (uint32_t ulBitmap)
{
    return (uint8_t) __CLZ(ulBitmap);
}

/* Check the configuration. */
  #if (configMAX_PRIORITIES > 32)
   #error \
    configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice.
  #endif

/* Store/clear the ready priorities in a bit map. */
  #define portRECORD_READY_PRIORITY(uxPriority, uxReadyPriorities)    (uxReadyPriorities) |= (1UL << (uxPriority))
  #define portRESET_READY_PRIORITY(uxPriority, uxReadyPriorities)     (uxReadyPriorities) &= ~(1UL << (uxPriority))

/*-----------------------------------------------------------*/

  #define portGET_HIGHEST_PRIORITY(uxTopPriority,                                     \
                                   uxReadyPriorities)                 uxTopPriority = \
    (31UL - (uint32_t) ucPortCountLeadingZeros((uxReadyPriorities)))

 #endif                                /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

 #ifdef configASSERT
void vPortValidateInterruptPriority(void);

  #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
 #endif

/* portNOP() is not required by this port. */
 #define portNOP()

 #define portMEMORY_BARRIER()    __asm volatile ("" ::: "memory")

 #if defined(__GNUC__) || defined(__ARMCC_VERSION)
  #define portINLINE          __inline
 #elif defined(__ICCARM__)
  #define portINLINE          inline
 #endif

 #ifndef portFORCE_INLINE
  #define portFORCE_INLINE    BSP_FORCE_INLINE
 #endif

portFORCE_INLINE static inline BaseType_t xPortIsInsideInterrupt (void)
{
    uint32_t   ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    ulCurrentInterrupt = __get_IPSR();

    if (ulCurrentInterrupt == 0)
    {
        xReturn = pdFALSE;
    }
    else
    {
        xReturn = pdTRUE;
    }

    return xReturn;
}

 #if BSP_TZ_NONSECURE_BUILD

/**
 * @brief Allocate a secure context for the task.
 *
 * Tasks are not created with a secure context. Any task that is going to call
 * secure functions must call portALLOCATE_SECURE_CONTEXT() to allocate itself a
 * secure context before it calls any secure function.
 *
 * @param[in] ulSecureStackSize The size of the secure stack to be allocated.
 */
  #define portALLOCATE_SECURE_CONTEXT(ulSecureStackSize)    vPortAllocateSecureContext(ulSecureStackSize)

/**
 * @brief Called when a task is deleted to delete the task's secure context,
 * if it has one.
 *
 * @param[in] pxTCB The TCB of the task being deleted.
 */
  #define portCLEAN_UP_TCB(pxTCB)                           vPortFreeSecureContext((uint32_t *) pxTCB)
 #else
  #define portALLOCATE_SECURE_CONTEXT(ulSecureStackSize)
  #define portCLEAN_UP_TCB(pxTCB)
 #endif

/*-----------------------------------------------------------*/

 #if (configENABLE_MPU == 1)

/**
 * @brief Checks whether or not the processor is privileged.
 *
 * @return 1 if the processor is already privileged, 0 otherwise.
 */
  #define portIS_PRIVILEGED()      xIsPrivileged()

/**
 * @brief Raise an SVC request to raise privilege.
 *
 * The SVC handler checks that the SVC was raised from a system call and only
 * then it raises the privilege. If this is called from any other place,
 * the privilege is not raised.
 */
  #define portRAISE_PRIVILEGE()    __asm volatile ("svc %0 \n" ::"i" (portSVC_RAISE_PRIVILEGE) : "memory");

/**
 * @brief Lowers the privilege level by setting the bit 0 of the CONTROL
 * register.
 */
  #define portRESET_PRIVILEGE()    vResetPrivilege()
 #else
  #define portIS_PRIVILEGED()
  #define portRAISE_PRIVILEGE()
  #define portRESET_PRIVILEGE()
 #endif                                /* configENABLE_MPU */

/*-----------------------------------------------------------*/

 #ifdef __cplusplus
}
 #endif

#endif                                 /* PORTMACRO_H */
