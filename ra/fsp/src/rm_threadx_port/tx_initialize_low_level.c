/**************************************************************************/

/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** ThreadX Component                                                     */
/**                                                                       */
/**   Initialize                                                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define TX_SOURCE_CODE

/* Include necessary system files.  */

#include "bsp_api.h"
#include "tx_api.h"
#include "tx_initialize.h"
#include "tx_thread.h"
#include "tx_timer.h"

/* SysTick must not be higher priority (lower numerical value) than maximum
 * ThreadX interrupt priority. */

#if TX_PORT_CFG_SYSTICK_IPL < TX_PORT_MAX_IPL
 #undef TX_PORT_CFG_SYSTICK_IPL
 #define TX_PORT_CFG_SYSTICK_IPL    TX_PORT_MAX_IPL
#endif

extern void * __VECTOR_TABLE[];
#define TX_VECTOR_TABLE             __VECTOR_TABLE

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _tx_initialize_low_level                          Cortex-M/CMSIS    */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is responsible for any low-level processor            */
/*    initialization, including setting up interrupt vectors, setting     */
/*    up a periodic timer interrupt source, saving the system stack       */
/*    pointer for use in ISR processing later, and finding the first      */
/*    available RAM memory address for tx_application_define.             */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _tx_initialize_kernel_enter           ThreadX entry function        */
/*                                                                        */
/**************************************************************************/

VOID _tx_initialize_low_level (VOID)
{
    /* Ensure that interrupts are disabled.  */
#ifdef TX_PORT_USE_BASEPRI
    __set_BASEPRI(TX_PORT_MAX_IPL << (8U - __NVIC_PRIO_BITS));
#else
    __disable_irq();
#endif

    /* Set base of available memory to end of non-initialized RAM area.  */
    _tx_initialize_unused_memory = TX_NULL;

    /* Set system stack pointer from vector value.  */
    _tx_thread_system_stack_ptr = TX_VECTOR_TABLE[0];

#if defined(RENESAS_CORTEX_M4) || defined(RENESAS_CORTEX_M33) || defined(RENESAS_CORTEX_M85)

    /* Enable the cycle count register.  */
    DWT->CTRL |= (uint32_t) DWT_CTRL_CYCCNTENA_Msk;
#endif

#ifndef TX_NO_TIMER

    /* Configure SysTick based on user configuration (100 Hz by default).  */
    SysTick_Config(SystemCoreClock / TX_TIMER_TICKS_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, TX_PORT_CFG_SYSTICK_IPL); // Set User configured Priority for Systick Interrupt
#endif

    /* Configure the handler priorities. */
    NVIC_SetPriority(SVCall_IRQn, UINT8_MAX);                // Note: SVC must be lowest priority, which is 0xFF
    NVIC_SetPriority(PendSV_IRQn, UINT8_MAX);                // Note: PnSV must be lowest priority, which is 0xFF

#ifdef TX_PORT_VENDOR_STACK_MONITOR_ENABLE

    /* Disable PSP monitoring  */
    R_MPU_SPMON->SP[1].CTL = 0;
#endif
}
