/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_clocks.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Key code for writing PRCR register. */
#define BSP_PRV_PRCR_KEY                        (0xA500U)
#define BSP_PRV_PRCR_UNLOCK                     ((BSP_PRV_PRCR_KEY) | 0x3U)
#define BSP_PRV_PRCR_LOCK                       ((BSP_PRV_PRCR_KEY) | 0x0U)

#define BSP_PRV_MAXIMUM_HOCOWTR_HSTS            ((uint8_t) 0x6U)

/* Wait state definitions for MEMWAIT. */
#define BSP_PRV_MEMWAIT_ZERO_WAIT_CYCLES        (0U)
#define BSP_PRV_MEMWAIT_TWO_WAIT_CYCLES         (1U)
#define BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ      (32000000U)

/* Wait state definitions for FLDWAITR. */
#define BSP_PRV_FLDWAITR_ONE_WAIT_CYCLES        (0U)
#define BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES        (1U)
#define BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ      (32000000U)

/* Temporary solution until R_FACI is added to renesas.h. */
#define BSP_PRV_FLDWAITR_REG_ACCESS             (*((volatile uint8_t *) (0x407EFFC4U)))

/* Wait state definitions for MCUS with SRAMWTSC and FLWT. */
#define BSP_PRV_SYS_CLOCK_FREQ_NO_RAM_WAITS     (60000000U)
#define BSP_PRV_SYS_CLOCK_FREQ_ONE_ROM_WAITS    (40000000U)
#define BSP_PRV_SYS_CLOCK_FREQ_TWO_ROM_WAITS    (80000000U)
#define BSP_PRV_SRAMWTSC_ZERO_WAIT_CYCLES       (0U)
#define BSP_PRV_SRAMWTSC_ONE_WAIT_CYCLES        (0xEU)
#define BSP_PRV_ROM_ZERO_WAIT_CYCLES            (0U)
#define BSP_PRV_ROM_ONE_WAIT_CYCLES             (1U)
#define BSP_PRV_ROM_TWO_WAIT_CYCLES             (2U)
#define BSP_PRV_SRAM_PRCR_KEY                   (0x78U)
#define BSP_PRV_SRAM_UNLOCK                     (((BSP_PRV_SRAM_PRCR_KEY) << 1) | 0x1U)
#define BSP_PRV_SRAM_LOCK                       (((BSP_PRV_SRAM_PRCR_KEY) << 1) | 0x0U)

/* Calculate value to write to MOMCR (MODRV controls main clock drive strength and MOSEL determines the source of the
 * main oscillator). */
#define BSP_PRV_MOMCR_MOSEL_BIT                 (6)
#define BSP_PRV_MODRV                           ((CGC_MAINCLOCK_DRIVE << BSP_FEATURE_CGC_MODRV_SHIFT) & \
                                                 BSP_FEATURE_CGC_MODRV_MASK)
#define BSP_PRV_MOSEL                           (BSP_CLOCK_CFG_MAIN_OSC_CLOCK_SOURCE << BSP_PRV_MOMCR_MOSEL_BIT)
#define BSP_PRV_MOMCR                           (BSP_PRV_MODRV | BSP_PRV_MOSEL)

/* Locations of bitfields used to configure CLKOUT. */
#define BSP_PRV_CKOCR_CKODIV_BIT                (4U)
#define BSP_PRV_CKOCR_CKOEN_BIT                 (7U)

/* Location of bitfield used to configure USB clock divider. */
#define BSP_PRV_SCKDIVCR2_UCK_BIT               (4U)

/* Calculate the value to write to SCKDIVCR. */
#define BSP_PRV_STARTUP_SCKDIVCR_ICLK_BITS      ((BSP_CFG_ICLK_DIV & 7U) << 24U)
#if BSP_FEATURE_CGC_HAS_PCLKD
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKD_BITS    (BSP_CFG_PCLKD_DIV & 0x7U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKD_BITS    (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKC
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKC_BITS    ((BSP_CFG_PCLKC_DIV & 0x7U) << 4U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKC_BITS    (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKB
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKB_BITS    ((BSP_CFG_PCLKB_DIV & 0x7U) << 8U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKB_BITS    (0U)
#endif
#if BSP_FEATURE_CGC_HAS_PCLKA
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKA_BITS    ((BSP_CFG_PCLKA_DIV & 0x7U) << 12U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_PCLKA_BITS    (0U)
#endif
#if BSP_FEATURE_CGC_HAS_BCLK
 #define BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS     ((BSP_CFG_BCLK_DIV & 0x7U) << 16U)
#elif BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB

/* Some MCUs have a requirement that bits 18-16 be set to the same value as the bits for configuring the PCLKB divisor. */
 #define BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS     ((BSP_CFG_PCLKB_DIV & 0x7U) << 16U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS     (0U)
#endif
#if BSP_FEATURE_CGC_HAS_FCLK
 #define BSP_PRV_STARTUP_SCKDIVCR_FCLK_BITS     ((BSP_CFG_FCLK_DIV & 0x7U) << 28U)
#else
 #define BSP_PRV_STARTUP_SCKDIVCR_FCLK_BITS     (0U)
#endif
#define BSP_PRV_STARTUP_SCKDIVCR                (BSP_PRV_STARTUP_SCKDIVCR_ICLK_BITS |  \
                                                 BSP_PRV_STARTUP_SCKDIVCR_PCLKD_BITS | \
                                                 BSP_PRV_STARTUP_SCKDIVCR_PCLKC_BITS | \
                                                 BSP_PRV_STARTUP_SCKDIVCR_PCLKB_BITS | \
                                                 BSP_PRV_STARTUP_SCKDIVCR_PCLKA_BITS | \
                                                 BSP_PRV_STARTUP_SCKDIVCR_BCLK_BITS |  \
                                                 BSP_PRV_STARTUP_SCKDIVCR_FCLK_BITS)

/* The number of clocks is used to size the g_clock_freq array. */
#if BSP_PRV_PLL_SUPPORTED
 #define BSP_PRV_NUM_CLOCKS                     ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_PLL + 1U)
#else
 #define BSP_PRV_NUM_CLOCKS                     ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK + 1U)
#endif

/* Frequencies of clocks with fixed freqencies. */
#define BSP_PRV_LOCO_FREQ                       (32768U)   // LOCO frequency is fixed at 32768 Hz
#define BSP_PRV_SUBCLOCK_FREQ                   (32768U)   // Subclock frequency is 32768 Hz
#define BSP_PRV_MOCO_FREQ                       (8000000U) // MOCO frequency is fixed at 8 MHz

/* Calculate PLLCCR value. */
#if BSP_PRV_PLL_SUPPORTED
 #if (1U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #if BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLSRCSEL              (0)
  #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE
   #define BSP_PRV_PLSRCSEL              (1)
  #endif
  #define BSP_PRV_PLLCCR_PLLMUL_MASK     (0x3F) // PLLMUL in PLLCCR is 6 bits wide
  #define BSP_PRV_PLLCCR_PLLMUL_BIT      (8)    // PLLMUL in PLLCCR starts at bit 8
  #define BSP_PRV_PLLCCR_PLSRCSEL_BIT    (4)    // PLSRCSEL in PLLCCR starts at bit 4
  #define BSP_PRV_PLLCCR                 ((((BSP_CFG_PLL_MUL & BSP_PRV_PLLCCR_PLLMUL_MASK) <<   \
                                            BSP_PRV_PLLCCR_PLLMUL_BIT) |                        \
                                           (BSP_PRV_PLSRCSEL << BSP_PRV_PLLCCR_PLSRCSEL_BIT)) | \
                                          BSP_CFG_PLL_DIV)
 #endif
 #if (2U == BSP_FEATURE_CGC_PLLCCR_TYPE)
  #define BSP_PRV_PLLCCR2_PLLMUL_MASK    (0x1F) // PLLMUL in PLLCCR2 is 5 bits wide
  #define BSP_PRV_PLLCCR2_PLODIV_BIT     (6)    // PLODIV in PLLCCR2 starts at bit 6

  #define BSP_PRV_PLLCCR2_PLLMUL         (BSP_CFG_PLL_MUL >> 1)
  #define BSP_PRV_PLLCCR                 (BSP_PRV_PLLCCR2_PLLMUL & BSP_PRV_PLLCCR2_PLLMUL_MASK) | \
    (BSP_CFG_PLL_DIV << BSP_PRV_PLLCCR2_PLODIV_BIT)
 #endif
#endif

/* Determine the optimal operating speed mode to apply after clock configuration based on the startup clock
 * frequency. */
#if BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_CGC_LOW_SPEED_MAX_FREQ_HZ && \
    BSP_CLOCKS_SOURCE_CLOCK_PLL != BSP_CFG_CLOCK_SOURCE
 #define BSP_PRV_STARTUP_OPERATING_MODE    (BSP_PRV_OPERATING_MODE_LOW_SPEED)
#elif BSP_STARTUP_ICLK_HZ <= BSP_FEATURE_CGC_MIDDLE_SPEED_MAX_FREQ_HZ
 #define BSP_PRV_STARTUP_OPERATING_MODE    (BSP_PRV_OPERATING_MODE_MIDDLE_SPEED)
#else
 #define BSP_PRV_STARTUP_OPERATING_MODE    (BSP_PRV_OPERATING_MODE_HIGH_SPEED)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static uint8_t bsp_clock_set_prechange(uint32_t requested_freq_hz);
static void    bsp_clock_set_postchange(uint32_t updated_freq_hz, uint8_t new_rom_wait_state);

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
static void bsp_prv_operating_mode_opccr_set(uint8_t operating_mode);

#endif

#if !BSP_CFG_SOFT_RESET_SUPPORTED
static void bsp_prv_clock_set_hard_reset(void);

#endif

/* This array stores the clock frequency of each system clock. This section of RAM should not be initialized by the C
 * runtime environment. This is initialized and used in bsp_clock_init, which is called before the C runtime
 * environment is initialized. */
static uint32_t g_clock_freq[BSP_PRV_NUM_CLOCKS]  BSP_PLACE_IN_SECTION(".noinit");

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

/* List of MSTP bits that must be set before entering low power modes or changing SCKDIVCR. */
static const uint8_t g_bsp_prv_power_change_mstp_data[][2] = BSP_FEATURE_LPM_CHANGE_MSTP_ARRAY;

static const uint8_t g_bsp_prv_power_change_mstp_length = sizeof(g_bsp_prv_power_change_mstp_data) /
                                                          sizeof(g_bsp_prv_power_change_mstp_data[0]);

static volatile uint32_t * const gp_bsp_prv_mstp = &R_MSTP->MSTPCRB;
#endif

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

/***********************************************************************************************************************
 * Changes the operating speed in OPCCR.  Assumes the LPM registers are unlocked in PRCR and cache is off.
 *
 * @param[in]  operating_mode  Desired operating mode, must be one of the BSP_PRV_OPERATING_MODE_* macros, cannot be
 *                             BSP_PRV_OPERATING_MODE_SUBOSC_SPEED
 **********************************************************************************************************************/
static void bsp_prv_operating_mode_opccr_set (uint8_t operating_mode)
{
 #if BSP_FEATURE_CGC_HOCOSF_BEFORE_OPCCR

    /* If the desired operating mode is already set, return. */
    if (operating_mode == R_SYSTEM->OPCCR)
    {
        return;
    }

    /* On some MCUs, the HOCO must be stable before updating OPCCR.OPCM. */
    if (0U == R_SYSTEM->HOCOCR)
    {
        /* Wait for HOCO to stabilize. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 1U);
    }
 #endif

    /* Wait for transition to complete. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OPCCR_b.OPCMTSF, 0U);

    /* Apply requested operating speed mode. */
    R_SYSTEM->OPCCR = operating_mode;

    /* Wait for transition to complete. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OPCCR_b.OPCMTSF, 0U);
}

#endif

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

/***********************************************************************************************************************
 * Changes the operating speed mode.  Assumes the LPM registers are unlocked in PRCR and cache is off.
 *
 * @param[in]  operating_mode  Desired operating mode, must be one of the BSP_PRV_OPERATING_MODE_* macros
 **********************************************************************************************************************/
void bsp_prv_operating_mode_set (uint8_t operating_mode)
{
    if (BSP_PRV_OPERATING_MODE_SUBOSC_SPEED == operating_mode)
    {
        /* Wait for transition to complete. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR_b.SOPCMTSF, 0U);

        /* Set subosc speed mode. */
        R_SYSTEM->SOPCCR = 0x1U;

        /* Wait for transition to complete. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR_b.SOPCMTSF, 0U);
    }
    else
    {
        /* Wait for transition to complete. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR_b.SOPCMTSF, 0U);

        /* Exit subosc speed mode first. */
        R_SYSTEM->SOPCCR = 0U;

        /* Wait for transition to complete. Check the entire register here since it should be set to 0 at this point.
         * Checking the entire register is slightly more efficient. This will also hang the program if the LPM
         * registers are not unlocked, which can help catch programming errors. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR, 0U);

        bsp_prv_operating_mode_opccr_set(operating_mode);
    }
}

#endif

#if BSP_PRV_PLL_SUPPORTED

/***********************************************************************************************************************
 * Updates the operating frequency of the PLL.
 *
 * @param[in] pll_freq_hz              New frequency of the PLL after the PLL is configured
 **********************************************************************************************************************/
void bsp_prv_prepare_pll (uint32_t pll_freq_hz)
{
    /* Store the PLL frequency, which is required to update SystemCoreClock after switching to PLL. */
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = pll_freq_hz;
}

#endif

/*******************************************************************************************************************//**
 * Update SystemCoreClock variable based on current clock settings.
 **********************************************************************************************************************/
void SystemCoreClockUpdate (void)
{
    uint32_t clock_index = R_SYSTEM->SCKSCR;
    SystemCoreClock = g_clock_freq[clock_index] >> R_SYSTEM->SCKDIVCR_b.ICK;
}

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

/*******************************************************************************************************************//**
 * Sets MSTP bits as required by the hardware manual for the MCU (reference Figure 9.2 "Example flow for changing the
 * value of SCKDIVCR" in the RA6M3 manual R01UH0886EJ0100).
 *
 * This function must be called before entering standby or changing SCKDIVCR.
 *
 * @return bitmask of bits set, where each bit corresponds to an index in g_bsp_prv_power_change_mstp_data
 **********************************************************************************************************************/
uint32_t bsp_prv_power_change_mstp_set (void)
{
    uint32_t mstp_set_bitmask = 0U;
    for (uint32_t i = 0U; i < g_bsp_prv_power_change_mstp_length; i++)
    {
        /* Get the MSTP register index and the bit to test from the MCU specific array. */
        uint32_t mstp_index = g_bsp_prv_power_change_mstp_data[i][0];
        uint32_t mstp_bit   = 1U << g_bsp_prv_power_change_mstp_data[i][1];

        /* Only set the bit if it's currently cleared. */
        if (!(gp_bsp_prv_mstp[mstp_index] & mstp_bit))
        {
            gp_bsp_prv_mstp[mstp_index] |= mstp_bit;
            mstp_set_bitmask            |= 1U << i;
        }

        /* This loop takes over 250 ns (30 cycles at 120 MHz) between 2 consecutive bits being set. It was measured
         * at 58 cycles for default IAR build configurations and 59 cycles for default GCC build configurations. */
    }

    /* The time between setting last MSTP bit and setting SCKDIVCR takes over 750 ns (90 cycles at 120 MHz). It was
     * measured at 96 cycles for default IAR build configurations and 102 cycles for default GCC build
     * configurations. */

    return mstp_set_bitmask;
}

#endif

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

/*******************************************************************************************************************//**
 * Clears MSTP bits set by bsp_prv_power_change_mstp_set as required by the hardware manual for the MCU (reference
 * Figure 9.2 "Example flow for changing the value of SCKDIVCR" in the RA6M3 manual R01UH0886EJ0100).
 *
 * This function must be called after exiting standby or changing SCKDIVCR.
 *
 * @param[in] mstp_clear_bitmask       bitmask of bits to clear, where each bit corresponds to an index in
 *                                     g_bsp_prv_power_change_mstp_data
 **********************************************************************************************************************/
void bsp_prv_power_change_mstp_clear (uint32_t mstp_clear_bitmask)
{
    /* The time between setting SCKDIVCR and clearing the first MSTP bit takes over 250 ns (30 cycles at 120 MHz). It
     * was measured at 38 cycles for default IAR build configurations and 68 cycles for default GCC build
     * configurations. */

    for (uint32_t i = 0U; i < g_bsp_prv_power_change_mstp_length; i++)
    {
        /* Only clear the bit if it was set in bsp_prv_power_change_mstp_set. */
        if ((1U << i) & mstp_clear_bitmask)
        {
            /* Get the MSTP register index and the bit to test from the MCU specific array. */
            uint32_t mstp_index = g_bsp_prv_power_change_mstp_data[i][0];
            uint32_t mstp_bit   = 1U << g_bsp_prv_power_change_mstp_data[i][1];

            gp_bsp_prv_mstp[mstp_index] &= ~mstp_bit;
        }

        /* This loop takes over 250 ns (30 cycles at 120 MHz) between 2 consecutive bits being cleared. It was measured
         * at 44 cycles for default IAR build configurations and 53 cycles for default GCC build configurations. */
    }
}

#endif

/*******************************************************************************************************************//**
 * Applies system core clock source and divider changes.  The MCU is expected to be in high speed mode during this
 * configuration and the CGC registers are expected to be unlocked in PRCR.
 *
 * @param[in] clock                    Desired system clock
 * @param[in] sckdivcr                 Value to set in SCKDIVCR register
 **********************************************************************************************************************/
void bsp_prv_clock_set (uint32_t clock, uint32_t sckdivcr)
{
#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

    /* Set MSTP bits as required by the hardware manual. This is done first to ensure the 750 ns delay required after
     * increasing any division ratio in SCKDIVCR is met. */
    uint32_t mstp_set_bitmask = bsp_prv_power_change_mstp_set();
#endif

    uint32_t iclk_div = (sckdivcr >> FSP_PRIV_CLOCK_ICLK) & FSP_PRIV_SCKDIVCR_DIV_MASK;

    /* Adjust the MCU specific wait state right before the system clock is set, if the system clock frequency to be
     * set is higher than before. */
    uint32_t clock_freq_hz_post_change = g_clock_freq[clock] >> iclk_div;
    uint8_t  new_rom_wait_state        = bsp_clock_set_prechange(clock_freq_hz_post_change);

    /* In order to avoid a system clock (momentarily) higher than expected, the order of switching the clock and
     * dividers must be so that the frequency of the clock goes lower, instead of higher, before being correct. */

    /* If the current ICLK divider is less (higher frequency) than the requested ICLK divider, set the divider
     * first. */
    sckdivcr = sckdivcr & BSP_PRV_SCKDIVCR_MASK;
    if (R_SYSTEM->SCKDIVCR_b.ICK < iclk_div)
    {
        /* Set the system dividers */
        R_SYSTEM->SCKDIVCR = sckdivcr;

        /* Set the system source clock */
        R_SYSTEM->SCKSCR = (uint8_t) clock;
    }

    /* If the current ICLK divider is greater (lower frequency) than the requested ICLK divider, set the clock
     * source first. If the ICLK divider is the same, order does not matter. */
    else
    {
        /* Set the system source clock */
        R_SYSTEM->SCKSCR = (uint8_t) clock;

        /* Set the system dividers */
        R_SYSTEM->SCKDIVCR = sckdivcr;
    }

    /* Clock is now at requested frequency. */

    /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
    SystemCoreClock = clock_freq_hz_post_change;

    /* Adjust the MCU specific wait state soon after the system clock is set, if the system clock frequency to be
     * set is lower than previous. */
    bsp_clock_set_postchange(SystemCoreClock, new_rom_wait_state);

#if BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED

    /* Clear MSTP bits as required by the hardware manual. This is done last to ensure the 250 ns delay required after
     * decreasing any division ratio in SCKDIVCR is met. */
    bsp_prv_power_change_mstp_clear(mstp_set_bitmask);
#endif
}

#if !BSP_CFG_SOFT_RESET_SUPPORTED

static void bsp_prv_clock_set_hard_reset (void)
{
    /* Wait states in SRAMWTSC are set after hard reset. No change required here. */

    /* Calculate the wait states for ROM */
 #if BSP_FEATURE_CGC_HAS_FLWT
  #if BSP_STARTUP_ICLK_HZ <= BSP_PRV_SYS_CLOCK_FREQ_ONE_ROM_WAITS

    /* Do nothing. Default setting in FLWT is correct. */
  #elif BSP_STARTUP_ICLK_HZ <= BSP_PRV_SYS_CLOCK_FREQ_TWO_ROM_WAITS
    R_FCACHE->FLWT = BSP_PRV_ROM_ONE_WAIT_CYCLES;
  #else
    R_FCACHE->FLWT = BSP_PRV_ROM_TWO_WAIT_CYCLES;
  #endif
 #endif

 #if BSP_FEATURE_CGC_HAS_MEMWAIT
  #if BSP_STARTUP_ICLK_HZ > BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ

    /* The MCU must be in high speed mode to set wait states to 2. High speed mode is the default out of reset. */
    R_SYSTEM->MEMWAIT = BSP_PRV_MEMWAIT_TWO_WAIT_CYCLES;
  #endif
 #endif

 #if BSP_FEATURE_CGC_HAS_FLDWAITR
  #if BSP_STARTUP_ICLK_HZ > BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ

    /* The MCU must be in high speed mode to set wait states to 2. High speed mode is the default out of reset. */
    BSP_PRV_FLDWAITR_REG_ACCESS = BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES;
  #endif
 #endif

    /* In order to avoid a system clock (momentarily) higher than expected, the order of switching the clock and
     * dividers must be so that the frequency of the clock goes lower, instead of higher, before being correct. */

    /* ICLK divider at reset is lowest possible, so set dividers first. */

    /* Set the system dividers first if ICLK divisor is larger than reset value. */
 #if BSP_CFG_ICLK_DIV >= BSP_FEATURE_CGC_ICLK_DIV_RESET
    R_SYSTEM->SCKDIVCR = BSP_PRV_STARTUP_SCKDIVCR;
 #endif

    /* Set the system source clock */
    R_SYSTEM->SCKSCR = BSP_CFG_CLOCK_SOURCE;

    /* Set the system dividers after setting the system clock source if ICLK divisor is smaller than reset value. */
 #if BSP_CFG_ICLK_DIV < BSP_FEATURE_CGC_ICLK_DIV_RESET
    R_SYSTEM->SCKDIVCR = BSP_PRV_STARTUP_SCKDIVCR;
 #endif

    /* Clock is now at requested frequency. */

    /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
    SystemCoreClockUpdate();

    /* Adjust the MCU specific wait state soon after the system clock is set, if the system clock frequency to be
     * set is lower than previous. */
 #if BSP_FEATURE_CGC_HAS_SRAMWTSC
  #if BSP_STARTUP_ICLK_HZ <= BSP_PRV_SYS_CLOCK_FREQ_NO_RAM_WAITS
    R_SRAM->SRAMPRCR = BSP_PRV_SRAM_UNLOCK;
    R_SRAM->SRAMWTSC = BSP_PRV_SRAMWTSC_ZERO_WAIT_CYCLES;
    R_SRAM->SRAMPRCR = BSP_PRV_SRAM_LOCK;
  #endif
 #endif

    /* ROM wait states are 0 by default.  No change required here. */
}

#endif

/*******************************************************************************************************************//**
 * Initializes system clocks.  Makes no assumptions about current register settings.
 **********************************************************************************************************************/
void bsp_clock_init (void)
{
    /* Unlock CGC and LPM protection registers. */
    R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_UNLOCK;

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE && BSP_FEATURE_BSP_FLASH_CACHE

    /* Disable ROM cache. */
    R_FCACHE->FCACHEE = 0U;
#endif
#if BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER

    /* Disable the flash prefetch buffer. */
    R_FACI_LP->PFBER = 0;
#endif

    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_HOCO]     = BSP_HOCO_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_MOCO]     = BSP_PRV_MOCO_FREQ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_LOCO]     = BSP_PRV_LOCO_FREQ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC] = BSP_CFG_XTAL_HZ;
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK] = BSP_PRV_SUBCLOCK_FREQ;
#if BSP_PRV_PLL_SUPPORTED

    /* The PLL value will be calculated at initialization. */
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = BSP_CFG_XTAL_HZ;
#endif

    /* The SystemCoreClock needs to be updated before calling R_BSP_SoftwareDelay. */
    SystemCoreClockUpdate();

#if BSP_CFG_SOFT_RESET_SUPPORTED

    /* Update the main oscillator drive, source, and wait states if the main oscillator is stopped.  If the main
     * oscillator is running, the drive, source, and wait states are assumed to be already set appropriately. */
    if (R_SYSTEM->MOSCCR)
    {
        /* Don't write to MOSCWTCR unless MOSTP is 1 and MOSCSF = 0. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.MOSCSF, 0U);

        /* Configure main oscillator drive. */
        R_SYSTEM->MOMCR = BSP_PRV_MOMCR;

        /* Set the main oscillator wait time. */
        R_SYSTEM->MOSCWTCR = (uint8_t) BSP_CLOCK_CFG_MAIN_OSC_WAIT;
    }
#else

    /* Configure main oscillator drive. */
    R_SYSTEM->MOMCR = BSP_PRV_MOMCR;

    /* Set the main oscillator wait time. */
    R_SYSTEM->MOSCWTCR = (uint8_t) BSP_CLOCK_CFG_MAIN_OSC_WAIT;
#endif

#if BSP_CLOCK_CFG_SUBCLOCK_POPULATED

    /* If the board has a subclock, set the subclock drive and start the subclock if the subclock is stopped.  If the
     * subclock is running, the subclock drive is assumed to be set appropriately. */
    if (R_SYSTEM->SOSCCR)
    {
        /* Configure the subclock drive if the subclock is not already running. */
        R_SYSTEM->SOMCR  = ((BSP_CLOCK_CFG_SUBCLOCK_DRIVE << BSP_FEATURE_CGC_SODRV_SHIFT) & BSP_FEATURE_CGC_SODRV_MASK);
        R_SYSTEM->SOSCCR = 0U;
 #if BSP_CLOCKS_SOURCE_CLOCK_SUBCLOCK == BSP_CFG_CLOCK_SOURCE

        /* If the subclock is the system clock source, wait for it to stabilize. */
        R_BSP_SoftwareDelay(BSP_CLOCK_CFG_SUBCLOCK_STABILIZATION_MS, BSP_DELAY_UNITS_MILLISECONDS);
 #endif
    }
#else
    R_SYSTEM->SOSCCR = 1U;
#endif

#if BSP_FEATURE_CGC_HAS_HOCOWTCR
 #if BSP_FEATURE_CGC_HOCOWTCR_64MHZ_ONLY

    /* These MCUs only require writes to HOCOWTCR if HOCO is set to 64 MHz. */
  #if 64000000 == BSP_HOCO_HZ
   #if BSP_CFG_USE_LOW_VOLTAGE_MODE

    /* Wait for HOCO to stabilize before writing to HOCOWTCR. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 1U);
   #else

    /* HOCO is assumed to be stable because these MCUs also require the HOCO to be stable before changing the operating
     * power control mode. */
   #endif
    R_SYSTEM->HOCOWTCR = BSP_PRV_MAXIMUM_HOCOWTR_HSTS;
  #endif
 #else

    /* These MCUs require HOCOWTCR to be set to the maximum value except in snooze mode.  There is no restriction to
     * writing this register. */
    R_SYSTEM->HOCOWTCR = BSP_PRV_MAXIMUM_HOCOWTR_HSTS;
 #endif
#endif

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
 #if BSP_CFG_SOFT_RESET_SUPPORTED

    /* Switch to high-speed to prevent any issues with the subsequent clock configurations. */
    bsp_prv_operating_mode_set(BSP_PRV_OPERATING_MODE_HIGH_SPEED);
 #elif BSP_FEATURE_CGC_LOW_VOLTAGE_MAX_FREQ_HZ > 0U

    /* MCUs that support low voltage mode start up in low voltage mode. */
    bsp_prv_operating_mode_opccr_set(BSP_PRV_OPERATING_MODE_HIGH_SPEED);

  #if BSP_CLOCKS_SOURCE_CLOCK_HOCO != BSP_CFG_CLOCK_SOURCE && BSP_CLOCKS_SOURCE_CLOCK_HOCO != BSP_CFG_PLL_SOURCE

    /* HOCO must be running during startup in low voltage mode. If HOCO is not used, turn it off after exiting low
     * voltage mode. */
    R_SYSTEM->HOCOCR = 1U;
  #endif
 #endif
#endif

    /* If the PLL is the desired source clock, ensure the source clock is running and stable and the power mode
     * allows PLL operation. */
#if BSP_PRV_PLL_SUPPORTED
 #if BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_CLOCK_SOURCE

    /* Start PLL source clock. */
  #if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE
    R_SYSTEM->HOCOCR = 0U;
  #else
    R_SYSTEM->MOSCCR = 0U;
  #endif

    /* Store PLL frequency. */
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = BSP_STARTUP_SOURCE_CLOCK_HZ;

    /* Configure the PLL registers. */
  #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE
    R_SYSTEM->PLLCCR = (uint16_t) BSP_PRV_PLLCCR;
  #elif 2U == BSP_FEATURE_CGC_PLLCCR_TYPE
    R_SYSTEM->PLLCCR2 = (uint8_t) BSP_PRV_PLLCCR;
  #endif

  #if BSP_FEATURE_CGC_PLLCCR_WAIT_US > 0

    /* This loop is provided to ensure at least 1 us passes between setting PLLMUL and clearing PLLSTP on some
     * MCUs (see PLLSTP notes in Section 8.2.4 "PLL Control Register (PLLCR)" of the RA4M1 manual R01UH0887EJ0100).
     * Five loops are needed here to ensure the most efficient path takes at least 1 us from the setting of
     * PLLMUL to the clearing of PLLSTP. HOCO is the fastest clock we can be using here since PLL cannot be running
     * while setting PLLCCR. */
    bsp_prv_software_delay_loop(BSP_DELAY_LOOPS_CALCULATE(BSP_PRV_MAX_HOCO_CYCLES_PER_US));
  #endif

    /* Verify PLL source is stable before starting PLL. */
  #if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_PLL_SOURCE

    /* Wait for HOCO to stabilize. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 1U);
  #else

    /* Wait for main oscillator to stabilize. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.MOSCSF, 1U);
  #endif
 #endif
#endif

    /* Start source clock. */
#if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_CLOCK_SOURCE
    R_SYSTEM->HOCOCR = 0U;

    /* Wait for HOCO to stabilize. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.HOCOSF, 1U);
#elif BSP_CLOCKS_SOURCE_CLOCK_MOCO == BSP_CFG_CLOCK_SOURCE
 #if BSP_CFG_SOFT_RESET_SUPPORTED

    /* If the MOCO is not running, start it and wait for it to stabilize using a software delay. */
    if (0U != R_SYSTEM->MOCOCR)
    {
        R_SYSTEM->MOCOCR = 0U;
        R_BSP_SoftwareDelay(BSP_FEATURE_CGC_MOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);
    }
 #endif
#elif BSP_CLOCKS_SOURCE_CLOCK_LOCO == BSP_CFG_CLOCK_SOURCE
 #if BSP_CFG_SOFT_RESET_SUPPORTED

    /* If the LOCO is not running, start it and wait for it to stabilize using a software delay. */
    if (0U != R_SYSTEM->LOCOCR)
    {
        R_SYSTEM->LOCOCR = 0U;
        R_BSP_SoftwareDelay(BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);
    }
 #else
    R_SYSTEM->LOCOCR = 0U;
    R_BSP_SoftwareDelay(BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);
 #endif
#elif BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_CLOCK_SOURCE
    R_SYSTEM->MOSCCR = 0U;

    /* Wait for main oscillator to stabilize. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.MOSCSF, 1U);
#elif BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_CLOCK_SOURCE
    R_SYSTEM->PLLCR = 0U;

    /* Wait for PLL to stabilize. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.PLLSF, 1U);
#else

    /* Do nothing. Subclock is already started and stabilized if it is populated and selected as system clock. */
#endif

    /* Set source clock and dividers. */
#if BSP_CFG_SOFT_RESET_SUPPORTED
    bsp_prv_clock_set(BSP_CFG_CLOCK_SOURCE, BSP_PRV_STARTUP_SCKDIVCR);
#else
    bsp_prv_clock_set_hard_reset();
#endif

    /* If the MCU can run in a lower power mode, apply the optimal operating speed mode. */
#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
 #if BSP_PRV_STARTUP_OPERATING_MODE != BSP_PRV_OPERATING_MODE_HIGH_SPEED
  #if BSP_PRV_PLL_SUPPORTED
   #if BSP_CFG_SOFT_RESET_SUPPORTED
    if (BSP_PRV_OPERATING_MODE_LOW_SPEED == BSP_PRV_STARTUP_OPERATING_MODE)
    {
        /* If the MCU has a PLL, ensure PLL is stopped and stable before entering low speed mode. */
        R_SYSTEM->PLLCR = 1U;

        /* Wait for PLL to stabilize. */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OSCSF_b.PLLSF, 0U);
    }
   #endif
  #endif
    bsp_prv_operating_mode_set(BSP_PRV_STARTUP_OPERATING_MODE);
 #endif
#endif

    /* Set USB clock divisor if it exists on the MCU. */
#ifdef BSP_CFG_UCK_DIV
    R_SYSTEM->SCKDIVCR2 = BSP_CFG_UCK_DIV << BSP_PRV_SCKDIVCR2_UCK_BIT;
#endif

#if BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL

    /* Some MCUs have an alternate register for selecting the USB clock source. */
 #if BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL_ALT
  #if BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_UCK_SOURCE

    /* Write to USBCKCR to select the PLL. */
    R_SYSTEM->USBCKCR = 0;
  #elif BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_UCK_SOURCE

    /* Write to USBCKCR to select the HOCO. */
    R_SYSTEM->USBCKCR = 1;
  #endif
 #endif
#endif

    /* Configure BCLK if it exists on the MCU. */
#ifdef BSP_CFG_BCLK_OUTPUT
 #if BSP_CFG_BCLK_OUTPUT > 0U
    R_SYSTEM->BCKCR   = BSP_CFG_BCLK_OUTPUT - 1U;
    R_SYSTEM->EBCKOCR = 1U;
 #else
  #if BSP_CFG_SOFT_RESET_SUPPORTED
    R_SYSTEM->EBCKOCR = 0U;
  #endif
 #endif
#endif

    /* Configure SDRAM clock if it exists on the MCU. */
#ifdef BSP_CFG_SDCLK_OUTPUT
    R_SYSTEM->SDCKOCR = BSP_CFG_SDCLK_OUTPUT;
#endif

    /* Configure CLKOUT. */
#if BSP_CFG_CLKOUT_SOURCE == BSP_CLOCKS_CLKOUT_DISABLED
 #if BSP_CFG_SOFT_RESET_SUPPORTED
    R_SYSTEM->CKOCR = 0U;
 #endif
#else
    uint8_t ckocr = BSP_CFG_CLKOUT_SOURCE | (BSP_CFG_CLKOUT_DIV << BSP_PRV_CKOCR_CKODIV_BIT);
    R_SYSTEM->CKOCR = ckocr;
    ckocr          |= (1U << BSP_PRV_CKOCR_CKOEN_BIT);
    R_SYSTEM->CKOCR = ckocr;
#endif

    /* Lock CGC and LPM protection registers. */
    R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_LOCK;

#if BSP_FEATURE_BSP_FLASH_CACHE

    /* Invalidate flash cache. */
    R_FCACHE->FCACHEIV = 1U;
    FSP_HARDWARE_REGISTER_WAIT(R_FCACHE->FCACHEIV, 0U);

    /* Enable flash cache. */
    R_FCACHE->FCACHEE = 1U;
#endif

#if BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER
    R_FACI_LP->PFBER = 1;
#endif
}

/*******************************************************************************************************************//**
 * Increases the ROM and RAM wait state settings to the minimum required based on the requested clock change.
 *
 * @param[in] requested_freq_hz        New core clock frequency after the clock change.
 *
 * @return The wait states for FLWT required after the clock change (or 0 if FLWT does not exist).
 **********************************************************************************************************************/
static uint8_t bsp_clock_set_prechange (uint32_t requested_freq_hz)
{
    uint8_t new_rom_wait_state = 0U;

#if BSP_FEATURE_CGC_HAS_SRAMWTSC

    /* Wait states for SRAM (SRAM0, SRAM1 and SRAM0 (DED)). */
    if (requested_freq_hz > BSP_PRV_SYS_CLOCK_FREQ_NO_RAM_WAITS)
    {
        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_UNLOCK;
        R_SRAM->SRAMWTSC = BSP_PRV_SRAMWTSC_ONE_WAIT_CYCLES;
        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_LOCK;
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLWT

    /* Calculate the wait states for ROM */
    if (requested_freq_hz <= BSP_PRV_SYS_CLOCK_FREQ_ONE_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ZERO_WAIT_CYCLES;
    }
    else if (requested_freq_hz <= BSP_PRV_SYS_CLOCK_FREQ_TWO_ROM_WAITS)
    {
        new_rom_wait_state = BSP_PRV_ROM_ONE_WAIT_CYCLES;
    }
    else
    {
        new_rom_wait_state = BSP_PRV_ROM_TWO_WAIT_CYCLES;
    }

    /* If more wait states are required after the change, then set the wait states before changing the clock. */
    if (new_rom_wait_state > R_FCACHE->FLWT)
    {
        R_FCACHE->FLWT = new_rom_wait_state;
    }
#endif

#if BSP_FEATURE_CGC_HAS_MEMWAIT
    if (requested_freq_hz > BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ)
    {
        /* The MCU must be in high speed mode to set wait states to 2. The MCU should already be in high speed mode as
         * a precondition to bsp_prv_clock_set. */
        R_SYSTEM->MEMWAIT = BSP_PRV_MEMWAIT_TWO_WAIT_CYCLES;
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLDWAITR
    if (requested_freq_hz > BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ)
    {
        /* The MCU must be in high speed mode to set wait states to 2. The MCU should already be in high speed mode as
         * a precondition to bsp_prv_clock_set. */
        BSP_PRV_FLDWAITR_REG_ACCESS = BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES;
    }
#endif

    return new_rom_wait_state;
}

/*******************************************************************************************************************//**
 * Decreases the ROM and RAM wait state settings to the minimum supported based on the applied clock change.
 *
 * @param[in] updated_freq_hz          New clock frequency after clock change
 * @param[in] new_rom_wait_state       Optimal value for FLWT if it exists, 0 if FLWT does not exist on the MCU
 **********************************************************************************************************************/
static void bsp_clock_set_postchange (uint32_t updated_freq_hz, uint8_t new_rom_wait_state)
{
    /* These variables are unused for some MCUs. */
    FSP_PARAMETER_NOT_USED(new_rom_wait_state);
    FSP_PARAMETER_NOT_USED(updated_freq_hz);

#if BSP_FEATURE_CGC_HAS_SRAMWTSC

    /* Wait states for SRAM (SRAM0, SRAM1 and SRAM0 (DED)). */
    if (updated_freq_hz <= BSP_PRV_SYS_CLOCK_FREQ_NO_RAM_WAITS)
    {
        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_UNLOCK;
        R_SRAM->SRAMWTSC = BSP_PRV_SRAMWTSC_ZERO_WAIT_CYCLES;
        R_SRAM->SRAMPRCR = BSP_PRV_SRAM_LOCK;
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLWT
    if (new_rom_wait_state != R_FCACHE->FLWT)
    {
        R_FCACHE->FLWT = new_rom_wait_state;
    }
#endif

#if BSP_FEATURE_CGC_HAS_MEMWAIT
    if (updated_freq_hz <= BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ)
    {
        R_SYSTEM->MEMWAIT = BSP_PRV_MEMWAIT_ZERO_WAIT_CYCLES;
    }
#endif

#if BSP_FEATURE_CGC_HAS_FLDWAITR
    if (updated_freq_hz <= BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ)
    {
        BSP_PRV_FLDWAITR_REG_ACCESS = BSP_PRV_FLDWAITR_ONE_WAIT_CYCLES;
    }
#endif
}

/** @} (end addtogroup BSP_MCU_PRV) */
