/*
 * Copyright (c) 2018-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include "cmsis.h"
#include "tfm_spm_hal.h"
#include "tfm_platform_core_api.h"
#include "target_cfg.h"
#include "bsp_api.h"
#include "mpu_armv8m_drv.h"
#include "region_defs.h"
#include "utilities.h"
#include "tfm_hal_platform.h"
#include "tfm_common_config.h"

/* Get address of memory regions to configure MPU */
extern const struct memory_region_limits memory_regions;

struct mpu_armv8m_dev_t dev_mpu_s = { MPU_BASE };

#ifdef CONFIG_TFM_ENABLE_MEMORY_PROTECT
#define PARTITION_REGION_PERIPH_START   6
#define PARTITION_REGION_PERIPH_MAX_NUM 2

uint32_t periph_num_count = 0;
#endif /* CONFIG_TFM_ENABLE_MEMORY_PROTECT */

enum tfm_plat_err_t tfm_spm_hal_init_isolation_hw(void)
{
    return TFM_PLAT_ERR_SUCCESS;
}

#ifndef TFM_PSA_API
enum tfm_plat_err_t tfm_spm_hal_configure_default_isolation(
                  bool privileged,
                  const struct platform_data_t *platform_data)
{
#if defined(CONFIG_TFM_ENABLE_MEMORY_PROTECT) && (TFM_LVL != 1)
    struct mpu_armv8m_region_cfg_t region_cfg;
#endif

    if (!platform_data) {
        return TFM_PLAT_ERR_INVALID_INPUT;
    }

#if defined(CONFIG_TFM_ENABLE_MEMORY_PROTECT) && (TFM_LVL != 1)
    if (!privileged) {
        region_cfg.region_nr = PARTITION_REGION_PERIPH_START + periph_num_count;
        periph_num_count++;
        if (periph_num_count >= PARTITION_REGION_PERIPH_MAX_NUM) {
            return TFM_PLAT_ERR_MAX_VALUE;
        }
        region_cfg.region_base = platform_data->periph_start;
        region_cfg.region_limit = platform_data->periph_limit;
        region_cfg.region_attridx = MPU_ARMV8M_MAIR_ATTR_DEVICE_IDX;
        region_cfg.attr_access = MPU_ARMV8M_AP_RW_PRIV_UNPRIV;
        region_cfg.attr_sh = MPU_ARMV8M_SH_NONE;
        region_cfg.attr_exec = MPU_ARMV8M_XN_EXEC_NEVER;

        mpu_armv8m_disable(&dev_mpu_s);

        if (mpu_armv8m_region_enable(&dev_mpu_s, &region_cfg)
            != MPU_ARMV8M_OK) {
            return TFM_PLAT_ERR_SYSTEM_ERR;
        }
        mpu_armv8m_enable(&dev_mpu_s, PRIVILEGED_DEFAULT_ENABLE,
                          HARDFAULT_NMI_ENABLE);
    }
#endif /* defined(CONFIG_TFM_ENABLE_MEMORY_PROTECT) && (TFM_LVL != 1) */

    return TFM_PLAT_ERR_SUCCESS;
}
#endif /* TFM_PSA_API */

uint32_t tfm_spm_hal_get_ns_VTOR(void)
{
    return memory_regions.non_secure_code_start;
}

uint32_t tfm_spm_hal_get_ns_MSP(void)
{
    return *((uint32_t *)memory_regions.non_secure_code_start);
}

uint32_t tfm_spm_hal_get_ns_entry_point(void)
{
    return *((uint32_t *)(memory_regions.non_secure_code_start+ 4));
}

enum tfm_plat_err_t tfm_spm_hal_set_secure_irq_priority(IRQn_Type irq_line)
{
    NVIC_SetPriority(irq_line, DEFAULT_IRQ_PRIORITY);
    return TFM_PLAT_ERR_SUCCESS;
}

void tfm_spm_hal_clear_pending_irq(IRQn_Type irq_line)
{
    NVIC_ClearPendingIRQ(irq_line);
}

void tfm_spm_hal_enable_irq(IRQn_Type irq_line)
{
    NVIC_EnableIRQ(irq_line);
}

void tfm_spm_hal_disable_irq(IRQn_Type irq_line)
{
    NVIC_DisableIRQ(irq_line);
}

enum irq_target_state_t tfm_spm_hal_set_irq_target_state(
                                           IRQn_Type irq_line,
                                           enum irq_target_state_t target_state)
{
    uint32_t result;

    if (target_state == TFM_IRQ_TARGET_STATE_SECURE) {
        result = NVIC_ClearTargetState(irq_line);
    } else {
        result = NVIC_SetTargetState(irq_line);
    }

    if (result) {
        return TFM_IRQ_TARGET_STATE_NON_SECURE;
    } else {
        return TFM_IRQ_TARGET_STATE_SECURE;
    }
}

enum tfm_plat_err_t tfm_spm_hal_enable_fault_handlers(void)
{
    return enable_fault_handlers();
}

enum tfm_plat_err_t tfm_spm_hal_system_reset_cfg(void)
{
    return system_reset_cfg();
}

void tfm_hal_system_reset(void)
{
    __disable_irq();

    NVIC->ICPR[0] = UINT32_MAX;         /* Clear all pending interrupts */
    NVIC->ICPR[1] = UINT32_MAX;         /* Clear all pending interrupts */
    NVIC->ICPR[2] = UINT32_MAX;         /* Clear all pending interrupts */
    NVIC->ICPR[3] = UINT32_MAX;         /* Clear all pending interrupts */
    NVIC->ICPR[4] = UINT32_MAX;         /* Clear all pending interrupts */
    NVIC->ICPR[5] = UINT32_MAX;         /* Clear all pending interrupts */
    NVIC->ICPR[6] = UINT32_MAX;         /* Clear all pending interrupts */
    NVIC->ICPR[7] = UINT32_MAX;         /* Clear all pending interrupts */

    NVIC_SystemReset();
}

enum tfm_plat_err_t tfm_spm_hal_init_debug(void)
{
    return init_debug();
}

enum tfm_plat_err_t tfm_spm_hal_nvic_interrupt_target_state_cfg(void)
{
    return nvic_interrupt_target_state_cfg();
}

enum tfm_plat_err_t tfm_spm_hal_nvic_interrupt_enable(void)
{
    return nvic_interrupt_enable();
}
