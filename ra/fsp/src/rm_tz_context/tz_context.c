/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/* This file is based on a template provided in ARM CMSIS_5:
 * https://github.com/ARM-software/CMSIS_5/blob/5.6.0/CMSIS/Core/Template/ARMv8-M/tz_context.c */

/* UNCRUSTIFY-OFF */

#include "bsp_api.h"

#if BSP_TZ_SECURE_BUILD

#include "tz_context.h"
#include "rm_tz_context_cfg.h"

/// Number of process slots (threads may call secure library code)
#ifndef TZ_PROCESS_STACK_SLOTS
#define TZ_PROCESS_STACK_SLOTS     8U
#endif

/// Stack size of the secure library code
#ifndef TZ_PROCESS_STACK_SIZE
#define TZ_PROCESS_STACK_SIZE      256U
#endif

#define TZ_PROCESS_STACK_SEAL_SIZE     8U

#define TZ_PROCESS_STACK_SEAL_VALUE    0xFEF5EDA5

/// MPU is not yet supported
#define RM_TZ_CONTEXT_CFG_MPU_ENABLE   0U

typedef struct {
  uint32_t sp_top;      // stack space top
  uint32_t sp_limit;    // stack space limit
  uint32_t sp;          // current stack pointer
} stack_info_t;

static stack_info_t ProcessStackInfo  [TZ_PROCESS_STACK_SLOTS];
static uint32_t     ProcessStackMemory[TZ_PROCESS_STACK_SLOTS][(TZ_PROCESS_STACK_SIZE + TZ_PROCESS_STACK_SEAL_SIZE)/sizeof(uint32_t)] BSP_ALIGN_VARIABLE(8);
static uint32_t     ProcessStackFreeSlot = UINT32_MAX;

/// Initialize secure context memory system
/// \return execution status (1: success, 0: error)
BSP_CMSE_NONSECURE_ENTRY
uint32_t TZ_InitContextSystem_S (void) {
  uint32_t n;

  if (__get_IPSR() == 0U) {
    return 0U;  // Thread Mode
  }

  for (n = 0U; n < TZ_PROCESS_STACK_SLOTS; n++) {
    ProcessStackInfo[n].sp = 0U;
    ProcessStackInfo[n].sp_limit = (uint32_t)&ProcessStackMemory[n];
    ProcessStackInfo[n].sp_top   = (uint32_t)&ProcessStackMemory[n] + TZ_PROCESS_STACK_SIZE;
    *((uint32_t *)ProcessStackMemory[n]) = n + 1U;

    /* Seal each process stack. */
    ProcessStackMemory[n][TZ_PROCESS_STACK_SIZE/sizeof(uint32_t)] = TZ_PROCESS_STACK_SEAL_VALUE;
  }
  *((uint32_t *)ProcessStackMemory[--n]) = UINT32_MAX;

  ProcessStackFreeSlot = 0U;

  // Default process stack pointer and stack limit
  __set_PSPLIM((uint32_t)ProcessStackMemory);
  __set_PSP   ((uint32_t)ProcessStackMemory);

#if RM_TZ_CONTEXT_CFG_MPU_ENABLE
  {
    /* Configure thread mode to use PSP and to be unprivileged. */
    __set_CONTROL(0x03U);
  }
#else
  {
    /* Configure thread mode to use PSP and to be privileged. */
    __set_CONTROL(0x02U);
  }
#endif

  return 1U;    // Success
}


/// Allocate context memory for calling secure software modules in TrustZone
/// \param[in]  module   identifies software modules called from non-secure mode
/// \return value != 0 id TrustZone memory slot identifier
/// \return value 0    no memory available or internal error
BSP_CMSE_NONSECURE_ENTRY
TZ_MemoryId_t TZ_AllocModuleContext_S (TZ_ModuleId_t module) {
  uint32_t slot;

  FSP_PARAMETER_NOT_USED(module); // Ignore (fixed Stack size)

  if (__get_IPSR() == 0U) {
    return 0U;  // Thread Mode
  }

  if (ProcessStackFreeSlot == UINT32_MAX) {
    return 0U;  // No slot available
  }

  slot = ProcessStackFreeSlot;
  ProcessStackFreeSlot = *((uint32_t *)ProcessStackMemory[slot]);

  ProcessStackInfo[slot].sp = ProcessStackInfo[slot].sp_top;

  return (slot + 1U);
}


/// Free context memory that was previously allocated with \ref TZ_AllocModuleContext_S
/// \param[in]  id  TrustZone memory slot identifier
/// \return execution status (1: success, 0: error)
BSP_CMSE_NONSECURE_ENTRY
uint32_t TZ_FreeModuleContext_S (TZ_MemoryId_t id) {
  uint32_t slot;

  if (__get_IPSR() == 0U) {
    return 0U;  // Thread Mode
  }

  if ((id == 0U) || (id > TZ_PROCESS_STACK_SLOTS)) {
    return 0U;  // Invalid ID
  }

  slot = id - 1U;

  if (ProcessStackInfo[slot].sp == 0U) {
    return 0U;  // Inactive slot
  }
  ProcessStackInfo[slot].sp = 0U;

  *((uint32_t *)ProcessStackMemory[slot]) = ProcessStackFreeSlot;
  ProcessStackFreeSlot = slot;

  return 1U;    // Success
}


/// Load secure context (called on RTOS thread context switch)
/// \param[in]  id  TrustZone memory slot identifier
/// \return execution status (1: success, 0: error)
BSP_CMSE_NONSECURE_ENTRY
uint32_t TZ_LoadContext_S (TZ_MemoryId_t id) {
  uint32_t slot;

  if ((__get_IPSR() == 0U) || ((__get_CONTROL() & 2U) == 0U)) {
    return 0U;  // Thread Mode or using Main Stack for threads
  }

  if ((id == 0U) || (id > TZ_PROCESS_STACK_SLOTS)) {
    return 0U;  // Invalid ID
  }

  slot = id - 1U;

  if (ProcessStackInfo[slot].sp == 0U) {
    return 0U;  // Inactive slot
  }

  // Setup process stack pointer and stack limit
  __set_PSPLIM(ProcessStackInfo[slot].sp_limit);
  __set_PSP   (ProcessStackInfo[slot].sp);

  return 1U;    // Success
}


/// Store secure context (called on RTOS thread context switch)
/// \param[in]  id  TrustZone memory slot identifier
/// \return execution status (1: success, 0: error)
BSP_CMSE_NONSECURE_ENTRY
uint32_t TZ_StoreContext_S (TZ_MemoryId_t id) {
  uint32_t slot;
  uint32_t sp;

  if ((__get_IPSR() == 0U) || ((__get_CONTROL() & 2U) == 0U)) {
    return 0U;  // Thread Mode or using Main Stack for threads
  }

  if ((id == 0U) || (id > TZ_PROCESS_STACK_SLOTS)) {
    return 0U;  // Invalid ID
  }

  slot = id - 1U;

  if (ProcessStackInfo[slot].sp == 0U) {
    return 0U;  // Inactive slot
  }

  sp = __get_PSP();
  if ((sp < ProcessStackInfo[slot].sp_limit) ||
      (sp > ProcessStackInfo[slot].sp_top)) {
    return 0U;  // SP out of range
  }
  ProcessStackInfo[slot].sp = sp;

  __asm volatile (
    "MRS    R1, PSP                          \n" /* r1 = PSP. */
    "VSTMDB R1!, {S0}                        \n" /* Trigger the deferred stacking of FPU registers. */
    "VLDMIA R1!, {S0}                        \n" /* Nullify the effect of the pervious statement. */
    ::: "r1", "memory"
  );

  // Default process stack pointer and stack limit
  __set_PSPLIM((uint32_t)ProcessStackMemory);
  __set_PSP   ((uint32_t)ProcessStackMemory);

  return 1U;    // Success
}

#endif
