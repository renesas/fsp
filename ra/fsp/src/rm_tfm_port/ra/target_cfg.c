/*
 * Copyright (c) 2018-2020 Arm Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bsp_api.h"
#include "target_cfg.h"
#include "Driver_Common.h"
#include "platform_description.h"
#include "platform_irq.h"
#include "region_defs.h"
#include "tfm_plat_defs.h"
#include "region.h"
#include <assert.h>
#include <stdio.h> /* for debugging printfs */

/* The section names come from the scatter file */
REGION_DECLARE(Load$$LR$$, LR_NS_PARTITION, $$Base);
REGION_DECLARE(Load$$LR$$, LR_NS_IMAGE, $$Base);
REGION_DECLARE(Image$$, ER_VENEER, $$Base);
REGION_DECLARE(Image$$, VENEER_ALIGN, $$Limit);
REGION_DECLARE(Load$$LR$$, LR_SECONDARY_PARTITION, $$Base);

const struct memory_region_limits memory_regions = {
  .non_secure_code_start =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_IMAGE, $$Base),

  .non_secure_partition_base =
  (uint32_t) &REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base),

  .non_secure_partition_limit =
  (uint32_t) &REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base) +
  RM_TFM_PORT_NONSECURE_IMAGE_SIZE - 1,

  .veneer_base =
  (uint32_t) &REGION_NAME(Image$$, ER_VENEER, $$Base),

  .veneer_limit =
  (uint32_t) &REGION_NAME(Image$$, VENEER_ALIGN, $$Limit),
};

/* To write into AIRCR register, 0x5FA value must be write to the VECTKEY field,
 * otherwise the processor ignores the write.
 */
#define SCB_AIRCR_WRITE_MASK ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos))

#define All_SEL_STATUS (SPNIDEN_SEL_STATUS | SPIDEN_SEL_STATUS | \
                        NIDEN_SEL_STATUS | DBGEN_SEL_STATUS)

/* Platform data structures:
 *
 * struct tfm_spm_partition_platform_data_t tfm_peripheral_std_uart = {
 *         UART1_NS_BASE,
 *         UART1_NS_BASE + 0xFFF
 * };
 *
 * struct tfm_spm_partition_platform_data_t tfm_peripheral_timer0 = {
 *         TIMER0_S_BASE,
 *         TIMER1_S_BASE -1
 * };
 *
 */


enum tfm_plat_err_t enable_fault_handlers(void)
{
    /* Explicitly set secure fault priority to the highest */
    NVIC_SetPriority(SecureFault_IRQn, 0);

    /* Enables BUS, MEM, USG and Secure faults */
    SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
                  | SCB_SHCSR_BUSFAULTENA_Msk
                  | SCB_SHCSR_MEMFAULTENA_Msk
                  | SCB_SHCSR_SECUREFAULTENA_Msk;
    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t system_reset_cfg(void)
{

    uint32_t reg_value = SCB->AIRCR;

    /* Clear SCB_AIRCR_VECTKEY value */
    reg_value &= ~(uint32_t)(SCB_AIRCR_VECTKEY_Msk);

    /* Enable system reset request only to the secure world */
    reg_value |= (uint32_t)(SCB_AIRCR_WRITE_MASK | SCB_AIRCR_SYSRESETREQS_Msk);

    SCB->AIRCR = reg_value;

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t init_debug(void)
{
    return TFM_PLAT_ERR_SUCCESS;
}

/*----------------- NVIC interrupt target state to NS configuration ----------*/
enum tfm_plat_err_t nvic_interrupt_target_state_cfg(void)
{
    /* Interrupt target state is set in bsp_irq_cfg() in bsp_irq.c */

    return TFM_PLAT_ERR_SUCCESS;
}

/*----------------- NVIC interrupt enabling for S peripherals ----------------*/
enum tfm_plat_err_t nvic_interrupt_enable(void)
{

/*
 *   NVIC_EnableIRQ(FF_TEST_UART_IRQ);
 */

    return TFM_PLAT_ERR_SUCCESS;
}

