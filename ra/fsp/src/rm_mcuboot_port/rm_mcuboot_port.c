#include <stdio.h>
#include "bsp_api.h"
#include "rm_mcuboot_port.h"
#include "rm_mcuboot_port_cfg.h"
#include "bootutil/bootutil_log.h"
#include "flash_map_backend/flash_map_backend.h"
#include "sysflash/sysflash.h"
#if RM_MCUBOOT_DUAL_BANK_ENABLED
 #include "r_flash_hp.h"
#endif

#if defined(__GNUC__) && !defined(__ARMCC_VERSION) && !defined(__clang_analyzer__)
 #define RM_MCUBOOT_PORT_NAKED_FUNCTION    __attribute__((naked, no_instrument_function, \
                                                          no_profile_instrument_function))
#else
 #define RM_MCUBOOT_PORT_NAKED_FUNCTION    __attribute__((naked))
#endif

extern void * const gp_mcuboot_flash_ctrl;
static void start_app(uint32_t pc, uint32_t sp) RM_MCUBOOT_PORT_NAKED_FUNCTION;

/* This function jumps to the application image. */
static void start_app (uint32_t pc __attribute__((unused)), uint32_t sp __attribute__((unused))) {
    /* This is a naked/stackless function. Do not pass arguments to the inline assembly when the GCC compiler is
     * used. */
    __asm volatile (

        /* Set stack pointer. */
        "MSR     MSP, R1                         \n"
        "DSB                                     \n"
        "ISB                                     \n"

        /* Branch to application. */
        "BX      R0                              \n"
        );
}

/*******************************************************************************************************************//**
 * Cleans up resources used by bootloader port and branches to application image.
 **********************************************************************************************************************/
void RM_MCUBOOT_PORT_BootApp (struct boot_rsp * rsp) {
    BOOT_LOG_DBG("Starting Application Image\n");
    BOOT_LOG_DBG("Image Offset: 0x%x\n", (int) rsp->br_image_off);

    /* The vector table is located after the header. Only running from internal flash is supported now. */
    uint32_t vector_table = rsp->br_image_off + rsp->br_hdr->ih_hdr_size;

#if RM_MCUBOOT_DUAL_BANK_ENABLED
    if (vector_table & BSP_FEATURE_FLASH_HP_CF_DUAL_BANK_START)
    {
        R_FLASH_HP_BankSwap(gp_mcuboot_flash_ctrl);

        /* Reset the MCU to swap to the other bank */
        __NVIC_SystemReset();
    }
#endif

    uint32_t * app_image = (uint32_t *) vector_table;
    uint32_t   app_sp    = app_image[0];
    uint32_t   app_pc    = app_image[1];

    /* Clean up internal flash driver. */
    flash_on_chip_cleanup();

    BOOT_LOG_DBG("Vector Table: 0x%x. PC=0x%x, SP=0x%x\n", (unsigned int) vector_table, (unsigned int) app_pc,
                 (unsigned int) app_sp);

    /* Set the applications vector table. */
    SCB->VTOR = vector_table;

    /* Disable MSP monitoring. */
#if BSP_FEATURE_TZ_HAS_TRUSTZONE
    __set_MSPLIM(0);
#else
    R_MPU_SPMON->SP[0].CTL = 0;
#endif

    /* Set SP and branch to PC. */
    start_app(app_pc, app_sp);
}

#if defined(__ARMCC_VERSION)           /* AC6 compiler */

 #if defined MCUBOOT_SIGN_EC256 && !defined MCUBOOT_USE_MBED_TLS

/* This function is only used by MCUboot for RSA keys with mbedtls.
 * When it's not used, this function should be compiled out, but AC6 has a known issue where unused functions are not compiled out
 * so this function is created as a placeholder to get rid of the linker error. */
int mbedtls_mpi_read_binary (void * X, const unsigned char * buf, size_t buflen)
{
    FSP_PARAMETER_NOT_USED(X);
    FSP_PARAMETER_NOT_USED(buf);
    FSP_PARAMETER_NOT_USED(buflen);

    return 0;
}

 #endif
#endif
