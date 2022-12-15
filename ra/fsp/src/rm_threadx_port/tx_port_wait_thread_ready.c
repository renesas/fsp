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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "tx_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_THREADX_PORT_PRCR_UNLOCK_LPM_REGISTER_ACCESS    (0xA502U)
#define RM_THREADX_PORT_PRCR_LOCK_LPM_REGISTER_ACCESS      (0xA500U)

/* The following offsets are relative to the base of the TX_THREAD structure.  For example:
 * offsetof(TX_THREAD, tx_thread_run_count) == 4 */
#define RM_THREADX_PORT_OFFSET_STACK_START                 12
#define RM_THREADX_PORT_OFFSET_STACK_END                   16

/* Used to generate a compiler error (negative array size error) if the assertion fails.  This is used in place of "#error"
 * for expressions that cannot be evaluated by the preprocessor like offsetof(). */
#ifndef RM_THREADX_PORT_COMPILE_TIME_ASSERT
 #define RM_THREADX_PORT_COMPILE_TIME_ASSERT(e)    ((void) sizeof(char[1 - 2 * !(e)]))
#endif

/***********************************************************************************************************************
 * Variables
 **********************************************************************************************************************/
extern TX_THREAD * volatile _tx_thread_current_ptr;
extern TX_THREAD * volatile _tx_thread_execute_ptr;

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _tx_port_wait_thread_ready                        Cortex-M/CMSIS    */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    Waits for a new thread to become ready.                             */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Pointer to thread ready to run                                      */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    PendSV_Handler                                                      */
/*                                                                        */
/**************************************************************************/

/* These variables are global because this function is called from PendSV_Handler, which is a stackless
 * function. */
static volatile uint16_t g_saved_lpm_state = 0U;
static volatile uint32_t g_prcr            = 0U;
void * _tx_port_wait_thread_ready (void)
{
    /* The following compile time assertions validate offsets used in the assembly code
     * of PendSV_Handler.  These assertions cannot be in PendSV_Handler because only
     * assembly code is allowed in naked/stackless functions.  These statements generate
     * build errors if the offset of any of the structure members used in this code changes.
     * These structure offsets are hardcoded because offsetof() is not supported in inline
     * assembly. */
    RM_THREADX_PORT_COMPILE_TIME_ASSERT(RM_THREADX_PORT_OFFSET_STACK_START ==
                                        offsetof(TX_THREAD, tx_thread_stack_start));
    RM_THREADX_PORT_COMPILE_TIME_ASSERT(RM_THREADX_PORT_OFFSET_STACK_END == offsetof(TX_THREAD, tx_thread_stack_end));

#ifdef TX_PORT_VENDOR_STACK_MONITOR_ENABLE
    RM_THREADX_PORT_COMPILE_TIME_ASSERT(RM_THREADX_PORT_SPMON_BASE == (uint32_t) R_MPU_SPMON);
    RM_THREADX_PORT_COMPILE_TIME_ASSERT(RM_THREADX_PORT_OFFSET_PSPMPUCTL ==
                                        ((uint32_t) &R_MPU_SPMON->SP[1].CTL - (uint32_t) R_MPU_SPMON));
    RM_THREADX_PORT_COMPILE_TIME_ASSERT(RM_THREADX_PORT_OFFSET_PSPMPUSA ==
                                        ((uint32_t) &R_MPU_SPMON->SP[1].SA - (uint32_t) R_MPU_SPMON));
    RM_THREADX_PORT_COMPILE_TIME_ASSERT(RM_THREADX_PORT_OFFSET_PSPMPUEA ==
                                        ((uint32_t) &R_MPU_SPMON->SP[1].EA - (uint32_t) R_MPU_SPMON));
#endif

    /* The following is the idle wait processing. In this case, no threads are ready for execution and the
     * system will simply be idle until an interrupt occurs that makes a thread ready. Note that interrupts
     * are disabled to allow use of WFI for waiting for a thread to arrive.  */

    TX_THREAD * new_thread_ptr;

    while (1)
    {
        /* Disable interrupts - The next block is critical. Interrupts are disabled with PRIMASK event if
         * BASEPRI is used elsewhere because the WFI wake condition includes interrupts masked by PRIMASK,
         * but does not include interrupts masked by BASEPRI.
         * https://developer.arm.com/documentation/100235/0002/the-cortex-m33-instruction-set/miscellaneous-instructions/wfi?lang=en
         */
        __disable_irq();

        /* Make the new thread the current thread. */
        new_thread_ptr         = _tx_thread_execute_ptr;
        _tx_thread_current_ptr = new_thread_ptr;

        /* If non-NULL, a new thread is ready! */
        if (new_thread_ptr != 0)
        {
            /* At this point, we have a new thread ready to go.  */

            /* Clear any newly pended PendSV - since we are already in the handler!  */
            SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk;

            /* Re-enable interrupts. */
            __enable_irq();
            break;
        }

        /* Save LPM Mode */
#if BSP_FEATURE_LPM_HAS_SBYCR_SSBY
        g_saved_lpm_state = R_SYSTEM->SBYCR;
#elif BSP_FEATURE_LPM_HAS_LPSCR
        g_saved_lpm_state = R_SYSTEM->LPSCR;
#endif

#if BSP_FEATURE_LPM_HAS_SBYCR_SSBY

        /* Check if the LPM peripheral is set to go to Software Standby mode with WFI instruction.
         * If yes, change the LPM peripheral to go to Sleep mode. Otherwise skip following procedures
         * to avoid the LPM register access which is high latency and impacts kernel performance.
         */
        if (g_saved_lpm_state & R_SYSTEM_SBYCR_SSBY_Msk)
        {
            /* Save register protect value */
            g_prcr = R_SYSTEM->PRCR;

            /* Unlock LPM peripheral registers */
            R_SYSTEM->PRCR = RM_THREADX_PORT_PRCR_UNLOCK_LPM_REGISTER_ACCESS;

            /* Clear to set to sleep low power mode (not standby or deep standby) */
            R_SYSTEM->SBYCR = g_saved_lpm_state & (uint16_t) ~R_SYSTEM_SBYCR_SSBY_Msk;
        }
#elif BSP_FEATURE_LPM_HAS_LPSCR
        if (R_SYSTEM_LPSCR_LPMD_Msk & g_saved_lpm_state)
        {
            /* Save register protect value */
            g_prcr = R_SYSTEM->PRCR;

            /* Unlock LPM peripheral registers */
            R_SYSTEM->PRCR = RM_THREADX_PORT_PRCR_UNLOCK_LPM_REGISTER_ACCESS;

            /* Clear to set to sleep low power mode (not standby or deep standby) */
            R_SYSTEM->LPSCR = 0U;
        }
#endif

        /**
         * DSB should be last instruction executed before WFI
         * infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dai0321a/BIHICBGB.html
         */
        __DSB();

        /* If there is a pending interrupt (wake up condition for WFI is true), the MCU does not enter low power mode:
         * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/BABHHGEB.html
         * After exiting from low power mode, interrupt must be re-enabled. */
        __WFI();

        /* Instruction Synchronization Barrier. */
        __ISB();

#if BSP_FEATURE_LPM_HAS_SBYCR_SSBY

        /* Check if the LPM peripheral was supposed to go to Software Standby mode with WFI instruction.
         * If yes, restore the LPM peripheral setting. Otherwise skip following procedures to avoid the
         * LPM register access which is high latency and impacts kernel performance.
         */
        if (g_saved_lpm_state & R_SYSTEM_SBYCR_SSBY_Msk)
        {
            /* Restore LPM Mode */
            R_SYSTEM->SBYCR = g_saved_lpm_state;

            /* Restore register lock */
            R_SYSTEM->PRCR = (uint16_t) (RM_THREADX_PORT_PRCR_LOCK_LPM_REGISTER_ACCESS | g_prcr);
        }
#elif BSP_FEATURE_LPM_HAS_LPSCR
        if (R_SYSTEM_LPSCR_LPMD_Msk & g_saved_lpm_state)
        {
            /* Restore LPM Mode */
            R_SYSTEM->LPSCR = (uint8_t) g_saved_lpm_state;

            /* Restore register lock */
            R_SYSTEM->PRCR = (uint16_t) (RM_THREADX_PORT_PRCR_LOCK_LPM_REGISTER_ACCESS | g_prcr);
        }
#endif

        /* Re-enable interrupts. */
        __enable_irq();
        __ISB();
    }

    return new_thread_ptr;
}
