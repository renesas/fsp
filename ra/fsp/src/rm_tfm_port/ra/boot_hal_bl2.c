/*
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include "cmsis.h"
#include "region.h"
#include "target_cfg.h"
#include "boot_hal.h"
#include "Driver_Flash.h"
#include "region_defs.h"
#include "flash_layout.h"
#include "bootutil/fault_injection_hardening.h"
#include "crypto_keys.h"

#include "r_flash_hp.h"
#include "r_flash_api.h"

#include "psa/crypto.h"
#if defined(MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT)
 #include "mbedtls/platform.h"
#endif

/* Flash device name must be specified by target */
extern ARM_DRIVER_FLASH FLASH_DEV_NAME;

REGION_DECLARE(Image$$, ER_DATA, $$Base)[];
REGION_DECLARE(Image$$, ARM_LIB_HEAP, $$ZI$$Limit)[];
REGION_DECLARE(Image$$, ARM_LIB_STACK, $$ZI$$Base);

__attribute__((naked)) void boot_clear_bl2_ram_area (void)
{
    __ASM volatile (
        "mov     r0, #0                              \n"
        "subs    %1, %1, %0                          \n"
        "Loop:                                       \n"
        "subs    %1, #4                              \n"
        "itt     ge                                  \n"
        "strge   r0, [%0, %1]                        \n"
        "bge     Loop                                \n"
        "bx      lr                                  \n"
        :
        : "r" (REGION_NAME(Image$$, ER_DATA, $$Base)),
        "r" (REGION_NAME(Image$$, ARM_LIB_HEAP, $$ZI$$Limit))
        : "r0", "memory"
        );
}

/*
 * The section 'fsp_dtc_vector_table' is reused to store boot data.
 * This is done to avoid creating a BL2 specific linker script.
 */
uint8_t g_dummy_reserve_for_tfm[BOOT_TFM_SHARED_DATA_TOTAL_SIZE] BSP_PLACE_IN_SECTION(".fsp_dtc_vector_table") = {0};

#define FAW_START_ADDR    (0xFFFC)
#define FAW_END_ADDR      (0x200000)

/* Flash device name must be specified by target */
extern ARM_DRIVER_FLASH FLASH_DEV_NAME;

/* FSP structures required by uart and flash drivers */
extern flash_hp_instance_ctrl_t g_tfm_fsp_flash_ctrl;

static void flash_FAW_Set (uint32_t start_addr, uint32_t end_addr)
{
    int ret_val = 0;

    volatile uint32_t faws = (uint32_t) ((R_FACI_HP->FAWMON_b.FAWS) << 13);
    volatile uint32_t fawe = (uint32_t) ((R_FACI_HP->FAWMON_b.FAWE) << 13);

    if (faws == fawe)
    {
        BOOT_LOG_INF("Configuring FAW settings");

        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;
        ret_val = R_FLASH_HP_AccessWindowSet(&g_tfm_fsp_flash_ctrl, start_addr, end_addr);

        FSP_CRITICAL_SECTION_EXIT;
        if (ret_val)
        {
            BOOT_LOG_ERR("Failed to set Flash Access Window: 0x%x", ret_val);
        }
    }
}

/* bootloader platform-specific HW intialization */
int32_t boot_platform_init (void)
{
    int32_t result;

    result = FLASH_DEV_NAME.Initialize(NULL);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* This line is necessary to prevent the compiler from optimizing out this area */
    memset(g_dummy_reserve_for_tfm, 0x0, BOOT_TFM_SHARED_DATA_TOTAL_SIZE);

    /* Set the FAW to lock the Secure code and data region */

    // flash_FAW_Set(FAW_START_ADDR, FAW_END_ADDR);

    result = mbedtls_platform_setup(NULL);
    if (result != 0)
    {
        return result;
    }

    result = psa_crypto_init();
    if (PSA_SUCCESS == result)
    {
        result = psa_generate_random((uint8_t *) BOOT_TFM_SHARED_SEED_BASE, BOOT_TFM_SHARED_SEED_SIZE);
    }

    return result;
}

__WEAK int32_t boot_platform_post_init (void)
{
#ifdef CRYPTO_HW_ACCELERATOR
    int32_t result;

    result = crypto_hw_accelerator_init();
    if (result)
    {
        return 1;
    }
    (void) fih_delay_init();
#endif                                 /* CRYPTO_HW_ACCELERATOR */

    return 0;
}

void boot_platform_quit (struct boot_arm_vector_table * vt)
{
    /* Clang at O0, stores variables on the stack with SP relative addressing.
     * When manually set the SP then the place of reset vector is lost.
     * Static variables are stored in 'data' or 'bss' section, change of SP has
     * no effect on them.
     */
    static struct boot_arm_vector_table * vt_cpy;
    int32_t result;

#ifdef CRYPTO_HW_ACCELERATOR
    result = crypto_hw_accelerator_finish();
    if (result)
    {
        while (1)
        {
        }
    }
#endif                                 /* CRYPTO_HW_ACCELERATOR */

#ifdef FLASH_DEV_NAME
    result = FLASH_DEV_NAME.Uninitialize();
    if (result != ARM_DRIVER_OK)
    {
        while (1)
        {
        }
    }
#endif                                 /* FLASH_DEV_NAME */
#ifdef FLASH_DEV_NAME_2
    result = FLASH_DEV_NAME_2.Uninitialize();
    if (result != ARM_DRIVER_OK)
    {
        while (1)
        {
        }
    }
#endif                                 /* FLASH_DEV_NAME_2 */
#ifdef FLASH_DEV_NAME_3
    result = FLASH_DEV_NAME_3.Uninitialize();
    if (result != ARM_DRIVER_OK)
    {
        while (1)
        {
        }
    }
#endif                                 /* FLASH_DEV_NAME_3 */
#ifdef FLASH_DEV_NAME_SCRATCH
    result = FLASH_DEV_NAME_SCRATCH.Uninitialize();
    if (result != ARM_DRIVER_OK)
    {
        while (1)
        {
        }
    }
#endif                                 /* FLASH_DEV_NAME_SCRATCH */

    vt_cpy = vt;
#if BSP_FEATURE_BSP_HAS_SP_MON

    /* Disable MSP monitoring  */
    R_MPU_SPMON->SP[0].CTL = 0;
#endif
#if defined(RENESAS_CORTEX_M23) || defined(RENESAS_CORTEX_M33) || defined(RENESAS_CORTEX_M85)

    /* Restore the Main Stack Pointer Limit register's reset value
     * before passing execution to runtime firmware to make the
     * bootloader transparent to it.
     */
    __set_MSPLIM(0);
#endif
    __set_MSP(vt->msp);
    __DSB();
    __ISB();

    boot_jump_to_next_image(vt_cpy->reset);
}

__WEAK int boot_platform_pre_load (uint32_t image_id)
{
    return 0;
}

__WEAK int boot_platform_post_load (uint32_t image_id)
{
    return 0;
}

__WEAK bool boot_platform_should_load_image(uint32_t image_id)
{
    return true;
}

__WEAK int boot_initiate_recovery_mode(uint32_t image_id)
{
    (void)image_id;

    /* We haven't done anything, therefore recovery has failed */
    return 1;
}
