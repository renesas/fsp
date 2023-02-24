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
 * Includes
 **********************************************************************************************************************/
#include "tx_cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Used to convert an evaluated macro into a string. */
#define RM_THREADX_PORT_STRINGIFY_EXPANDED(s)    RM_THREADX_PORT_STRINGIFY(s)

/* Used to convert text into a string. */
#define RM_THREADX_PORT_STRINGIFY(s)             #s

/* This is the base address for the SPMON registers. */
#define RM_THREADX_PORT_SPMON_BASE            0x40000D00

/* The following macros are defined as hard coded numbers so they can be converted to strings in the
 * assembly language of PendSV_Handler. They are verified to be correct using compile time assertions
 * at the beginning of PendSV_Handler. */

/* The following offsets are relative to the base of the TX_THREAD structure.  For example:
 * offsetof(TX_THREAD, tx_thread_run_count) == 4 */
#define RM_THREADX_PORT_OFFSET_STACK_START    12
#define RM_THREADX_PORT_OFFSET_STACK_END      16

/* The following offsets are relative to the base of the R_SPMON_Type structure.  For example:
 * offsetof(R_SPMON_Type, PSPMPUCTL) == 20 */
#define RM_THREADX_PORT_OFFSET_PSPMPUCTL      20
#define RM_THREADX_PORT_OFFSET_PSPMPUSA       24
#define RM_THREADX_PORT_OFFSET_PSPMPUEA       28

#ifndef TX_INCLUDE_USER_DEFINE_FILE
 #define TX_INCLUDE_USER_DEFINE_FILE
#endif

#ifdef __ARM_ARCH_8M_MAIN__            // CM33
 #define TX_PORT_PSPLIM_PRESENT
#else
 #define TX_PORT_VENDOR_STACK_MONITOR_ENABLE
#endif

#ifdef TX_PORT_VENDOR_STACK_MONITOR_ENABLE
 #define TX_PORT_VENDOR_ASM_STACK_MONITOR_CONFIGURE                                                    \
    /* Setup the Hardware Stack Monitor for thread to schedule.  */                                    \
                                                                                                       \
    /* Disable PSP monitoring  */                                                                      \
                                                                                                       \
    /* R_MPU_SPMON->SP[1].CTL = 0; */                                                                  \
    "LDR     r0, ="RM_THREADX_PORT_STRINGIFY_EXPANDED (RM_THREADX_PORT_SPMON_BASE) /* R_SPMON base. */ \
    "                                    \n"                                                           \
    "LDR     r1, =0                      \n"                                       /* r1 = 0. */       \
    "STR     r1, [r0, #"RM_THREADX_PORT_STRINGIFY_EXPANDED (RM_THREADX_PORT_OFFSET_PSPMPUCTL)          \
    "]                                   \n"                                                           \
                                                                                                       \
    /* Setup start address  */                                                                         \
                                                                                                       \
    /* Bits 0 and 1 of _tx_thread_current_ptr->tx_thread_stack_start are always 0 since the stack must be aligned \
     * on an 8 byte boundary. */                                                                \
                                                                                                \
    /* R_MPU_SPMON->SP[1].SA = (uint32_t)_tx_thread_current_ptr->tx_thread_stack_start; */      \
    "LDR     r1, [r6, #"RM_THREADX_PORT_STRINGIFY_EXPANDED (RM_THREADX_PORT_OFFSET_STACK_START) \
    "]                                   \n"                                                    \
    "STR     r1, [r0, #"RM_THREADX_PORT_STRINGIFY_EXPANDED (RM_THREADX_PORT_OFFSET_PSPMPUSA)    \
    "]                                   \n"                                                    \
                                                                                                \
    /* Setup end address  */                                                                    \
                                                                                                \
    /* Bits 0 and 1 of _tx_thread_current_ptr->tx_thread_stack_end are always 1 since the stack must be aligned \
     * on an 8 byte boundary and a multiple of 8 bytes. */                                    \
                                                                                              \
    /* R_MPU_SPMON->SP[1].EA = (uint32_t)_tx_thread_current_ptr->tx_thread_stack_end; */      \
    "LDR     r1, [r6, #"RM_THREADX_PORT_STRINGIFY_EXPANDED (RM_THREADX_PORT_OFFSET_STACK_END) \
    "]                                   \n"                                                  \
    "STR     r1, [r0, #"RM_THREADX_PORT_STRINGIFY_EXPANDED (RM_THREADX_PORT_OFFSET_PSPMPUEA)  \
    "]                                   \n"

 #define TX_PORT_VENDOR_ASM_STACK_MONITOR_ENABLE                                              \
                                                                                              \
    /* Enable PSP monitoring  */                                                              \
                                                                                              \
    /* R_MPU_SPMON->SP[1].CTL = 1; */                                                         \
    "LDR     r1, =1                      \n" /* r1 = 1. */                                    \
    "STR     r1, [r0, #"RM_THREADX_PORT_STRINGIFY_EXPANDED (RM_THREADX_PORT_OFFSET_PSPMPUCTL) \
    "]                                   \n"
#endif

/***********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/

void * _tx_port_wait_thread_ready(void);

#ifdef __cplusplus
}
#endif
