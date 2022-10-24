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
#include "r_lpm.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Clock control register addresses */
#define LPM_CLOCK_HOCOCR              ((uint8_t *) 0x4001E036U)
#define LPM_CLOCK_MOCOCR              ((uint8_t *) 0x4001E038U)
#define LPM_CLOCK_LOCOCR              ((uint8_t *) 0x4001E490U)
#define LPM_CLOCK_MOSCCR              ((uint8_t *) 0x4001E032U)
#define LPM_CLOCK_SOSCCR              ((uint8_t *) 0x4001E480U)
#define LPM_CLOCK_PLLCR               ((uint8_t *) 0x4001E02AU)
#define LPM_CLOCK_HOCO                0 // The high speed on chip oscillator.
#define LPM_CLOCK_MOCO                1 // The middle speed on chip oscillator.
#define LPM_CLOCK_LOCO                2 // The low speed on chip oscillator.
#define LPM_CLOCK_MAIN_OSC            3 // The main oscillator.
#define LPM_CLOCK_SUBCLOCK            4 // The subclock oscillator.
#define LPM_CLOCK_PLL                 5 // The PLL oscillator.

/* From user's manual and discussions with hardware group,
 * using the maximum is safe for all MCUs, will be updated and restored in LPM when entering
 * low power mode on RA6 MCUs (lowPowerModeEnter())
 */

#define LPM_SW_STANDBY_STCONR         (0x0U)
#define LPM_SW_STANDBY_WAKE_STCONR    (0x3U)

#define LPM_SNZREQCR1_OFFSET          (32ULL)
#define LPM_WUPEN1_OFFSET             (32ULL)

#define LPM_OPEN                      (0x524c504d)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* This array stores the address of the register containing the stop bit for each clock. All of these registers are
 * 8-bit registers and only bit 0 is valid.  All other bits are read as 0 and should be written to 0.  Bit 0 of each
 * of these registers indicates that the corresponding clock is stopped when set, or that the corresponding clock
 * is operating when cleared. */
static uint8_t volatile * const gp_lpm_clock_stp_registers[] =
{
    [LPM_CLOCK_HOCO]     = LPM_CLOCK_HOCOCR,
    [LPM_CLOCK_MOCO]     = LPM_CLOCK_MOCOCR,
    [LPM_CLOCK_LOCO]     = LPM_CLOCK_LOCOCR,
    [LPM_CLOCK_MAIN_OSC] = LPM_CLOCK_MOSCCR,
    [LPM_CLOCK_SUBCLOCK] = LPM_CLOCK_SOSCCR,
#if BSP_FEATURE_CGC_HAS_PLL
    [LPM_CLOCK_PLL] = LPM_CLOCK_PLLCR,
#endif
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
const lpm_api_t g_lpm_on_lpm =
{
    .open                = R_LPM_Open,
    .close               = R_LPM_Close,
    .lowPowerReconfigure = R_LPM_LowPowerReconfigure,
    .lowPowerModeEnter   = R_LPM_LowPowerModeEnter,
    .ioKeepClear         = R_LPM_IoKeepClear,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
static fsp_err_t r_lpm_configure(lpm_cfg_t const * const p_cfg);
static fsp_err_t r_lpm_low_power_enter(lpm_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t r_lpm_check_clocks(uint32_t clock_source);
static void      r_lpm_wait_for_operating_mode_flags(void);

#if LPM_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_lpm_mcu_specific_low_power_check(lpm_cfg_t const * const p_cfg);

#endif

/*******************************************************************************************************************//**
 * @addtogroup LPM
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Perform any necessary initialization
 *
 * @retval     FSP_SUCCESS                   LPM instance opened
 * @retval     FSP_ERR_ASSERTION             Null Pointer
 * @retval     FSP_ERR_ALREADY_OPEN          LPM instance is already open
 * @retval     FSP_ERR_UNSUPPORTED           This MCU does not support Deep Software Standby
 * @retval     FSP_ERR_INVALID_ARGUMENT      One of the following:
 *                                           - Invalid snooze entry source
 *                                           - Invalid snooze end sources
 * @retval     FSP_ERR_INVALID_MODE          One of the following:
 *                                           - Invalid low power mode
 *                                           - Invalid DTC option for snooze mode
 *                                           - Invalid deep standby end sources
 *                                           - Invalid deep standby end sources edges
 *                                           - Invalid power supply option for deep standby
 *                                           - Invalid IO port option for deep standby
 *                                           - Invalid output port state setting for standby or deep standby
 *                                           - Invalid sources for wake from standby mode
 *                                           - Invalid power supply option for standby
 *                                           - Invalid IO port option for standby
 *                                           - Invalid standby end sources
 *                                           - Invalid standby end sources edges
 **********************************************************************************************************************/
fsp_err_t R_LPM_Open (lpm_ctrl_t * const p_api_ctrl, lpm_cfg_t const * const p_cfg)
{
    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;
#if LPM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(LPM_OPEN != p_ctrl->lpm_open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Save the configuration  */
    p_ctrl->p_cfg = p_cfg;

    fsp_err_t err = r_lpm_configure(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_ctrl->lpm_open = LPM_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configure a low power mode
 *
 * NOTE: This function does not enter the low power mode, it only configures parameters of the mode. Execution of the
 * WFI instruction is what causes the low power mode to be entered.
 *
 * @retval     FSP_SUCCESS                   Low power mode successfuly applied
 * @retval     FSP_ERR_ASSERTION             Null Pointer
 * @retval     FSP_ERR_NOT_OPEN              LPM instance is not open
 * @retval     FSP_ERR_UNSUPPORTED           This MCU does not support Deep Software Standby
 * @retval     FSP_ERR_INVALID_ARGUMENT      One of the following:
 *                                           - Invalid snooze entry source
 *                                           - Invalid snooze end sources
 * @retval     FSP_ERR_INVALID_MODE          One of the following:
 *                                           - Invalid low power mode
 *                                           - Invalid DTC option for snooze mode
 *                                           - Invalid deep standby end sources
 *                                           - Invalid deep standby end sources edges
 *                                           - Invalid power supply option for deep standby
 *                                           - Invalid IO port option for deep standby
 *                                           - Invalid output port state setting for standby or deep standby
 *                                           - Invalid sources for wake from standby mode
 *                                           - Invalid power supply option for standby
 *                                           - Invalid IO port option for standby
 *                                           - Invalid standby end sources
 *                                           - Invalid standby end sources edges
 **********************************************************************************************************************/
fsp_err_t R_LPM_LowPowerReconfigure (lpm_ctrl_t * const p_api_ctrl, lpm_cfg_t const * const p_cfg)
{
    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;

#if LPM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(LPM_OPEN == p_ctrl->lpm_open, FSP_ERR_NOT_OPEN);
#endif

    /* Save the configuration  */
    p_ctrl->p_cfg = p_cfg;

    return r_lpm_configure(p_cfg);
}

/*******************************************************************************************************************//**
 * Enter low power mode (sleep/standby/deep standby) using WFI macro.
 *
 * Function will return after waking from low power mode.
 *
 * @retval     FSP_SUCCESS                   Successful.
 * @retval     FSP_ERR_ASSERTION             Null pointer.
 * @retval     FSP_ERR_NOT_OPEN              LPM instance is not open
 * @retval     FSP_ERR_INVALID_MODE          One of the following:
 *                                           - HOCO was not system clock when using snooze mode with SCI0/RXD0.
 *                                           - HOCO was not stable when using snooze mode with SCI0/RXD0.
 *                                           - MOCO was running when using snooze mode with SCI0/RXD0.
 *                                           - MAIN OSCILLATOR was running when using snooze mode with SCI0/RXD0.
 *                                           - PLL was running when using snooze mode with SCI0/RXD0.
 *                                           - Unable to disable ocillator stop detect when using standby or deep standby.
 **********************************************************************************************************************/
fsp_err_t R_LPM_LowPowerModeEnter (lpm_ctrl_t * const p_api_ctrl)
{
    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;
#if LPM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(LPM_OPEN == p_ctrl->lpm_open, FSP_ERR_NOT_OPEN);
#endif

    /* Wait for ongoing operating mode transition (OPCMTSF, SOPCMTSF) */
    r_lpm_wait_for_operating_mode_flags();

    /* Must enable writing to Low Power Mode register prior to entering Low Power Mode. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
#if LPM_CFG_STANDBY_LIMIT
    if (LPM_MODE_SLEEP != p_ctrl->p_cfg->low_power_mode)
    {
        R_SYSTEM->SBYCR |= (1U << R_SYSTEM_SBYCR_SSBY_Pos);
    }
#endif

    fsp_err_t err = r_lpm_low_power_enter(p_ctrl);

#if LPM_CFG_STANDBY_LIMIT
    if (LPM_MODE_SLEEP != p_ctrl->p_cfg->low_power_mode)
    {
        R_SYSTEM->SBYCR &= (uint16_t) (~(1U << R_SYSTEM_SBYCR_SSBY_Pos));
    }
#endif
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);

    return err;
}

/*******************************************************************************************************************//**
 * Clear the IOKEEP bit after deep software standby
 *
 * @retval     FSP_SUCCESS          DPSBYCR_b.IOKEEP bit cleared Successfully.
 * @retval     FSP_ERR_UNSUPPORTED  Deep standby mode not supported on this MCU.
 **********************************************************************************************************************/
fsp_err_t R_LPM_IoKeepClear (lpm_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);

    R_SYSTEM->DPSBYCR_b.IOKEEP = 0U;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);

    return FSP_SUCCESS;
#else

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Close the LPM Instance
 *
 * @retval     FSP_SUCCESS        LPM driver closed
 * @retval     FSP_ERR_NOT_OPEN   LPM instance is not open
 * @retval     FSP_ERR_ASSERTION  Null Pointer
 **********************************************************************************************************************/
fsp_err_t R_LPM_Close (lpm_ctrl_t * const p_api_ctrl)
{
    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;
#if LPM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN(LPM_OPEN == p_ctrl->lpm_open, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->lpm_open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup LPM)
 **********************************************************************************************************************/

#if LPM_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Verifies all MCU specific settings related to low power modes
 * @param      p_cfg           the MCU specific configuration
 *
 * @retval     FSP_SUCCESS              Configuration is valid
 * @retval     FSP_ERR_UNSUPPORTED      This MCU does not support Deep Software Standby
 * @retval     FSP_ERR_INVALID_ARGUMENT One of the following:
 *                                      - Invalid snooze entry source
 *                                      - Invalid snooze end sources
 * @retval     FSP_ERR_INVALID_MODE     One of the following:
 *                                      - Invalid low power mode
 *                                      - Invalid DTC option for snooze mode
 *                                      - Invalid deep standby end sources
 *                                      - Invalid deep standby end sources edges
 *                                      - Invalid power supply option for deep standby
 *                                      - Invalid IO port option for deep standby
 *                                      - Invalid output port state setting for standby or deep standby
 *                                      - Invalid sources for wake from standby mode
 *                                      - Invalid power supply option for standby
 *                                      - Invalid IO port option for standby
 *                                      - Invalid standby end sources
 *                                      - Invalid standby end sources edges
 *
 * @note       This function assumes the register has been unlocked by the calling application
 **********************************************************************************************************************/
fsp_err_t r_lpm_mcu_specific_low_power_check (lpm_cfg_t const * const p_cfg)
{
    if (LPM_MODE_SLEEP != p_cfg->low_power_mode)
    {
        if (LPM_MODE_STANDBY_SNOOZE == p_cfg->low_power_mode)
        {
            FSP_ERROR_RETURN(0U == ((uint64_t) p_cfg->snooze_request_source & (~BSP_FEATURE_LPM_SNZREQCR_MASK)),
                             FSP_ERR_INVALID_ARGUMENT);
            FSP_ERROR_RETURN(0U == ((uint32_t) p_cfg->snooze_end_sources & (~BSP_FEATURE_LPM_SNZEDCR_MASK)),
                             FSP_ERR_INVALID_ARGUMENT);
        }
        else if (LPM_MODE_DEEP == p_cfg->low_power_mode)
        {
 #if BSP_FEATURE_LPM_HAS_DEEP_STANDBY

            /* Verify the deep software standby interrupt source is valid. */
            FSP_ERROR_RETURN(0U == (uint32_t) (~BSP_FEATURE_LPM_DPSIER_MASK & p_cfg->deep_standby_cancel_source),
                             FSP_ERR_INVALID_MODE);

            /* Verify the deep software standby interrupt edge is valid. */
            FSP_ERROR_RETURN(0U == (uint32_t) (~BSP_FEATURE_LPM_DPSIEGR_MASK & p_cfg->deep_standby_cancel_edge),
                             FSP_ERR_INVALID_MODE);

            /* Verify all configured edges have a source configured. */
            FSP_ERROR_RETURN(0U ==
                             (~p_cfg->deep_standby_cancel_source &
                              (lpm_deep_standby_cancel_source_t) p_cfg->deep_standby_cancel_edge),
                             FSP_ERR_INVALID_MODE);
 #else

            return FSP_ERR_UNSUPPORTED;
 #endif
        }
        else
        {
            /* Do nothing. */
        }

        FSP_ERROR_RETURN(0U == ((uint64_t) p_cfg->standby_wake_sources & ~BSP_FEATURE_ICU_WUPEN_MASK),
                         FSP_ERR_INVALID_MODE);
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Configures all MCU specific settings related to low power modes
 * @param      p_cfg           the MCU specific configuration
 *
 * @note       This function assumes the register has been unlocked by the calling application
 *
 * @retval     FSP_SUCCESS                   Configuration is valid
 * @retval     FSP_ERR_UNSUPPORTED           This MCU does not support Deep Software Standby
 * @retval     FSP_ERR_ASSERTION             NULL p_extend when low power mode is not Sleep
 * @retval     FSP_ERR_INVALID_ARGUMENT      One of the following:
 *                                           - Invalid snooze entry source
 *                                           - Invalid snooze end sources
 * @retval     FSP_ERR_INVALID_MODE          One of the following:
 *                                           - Invalid low power mode
 *                                           - Invalid DTC option for snooze mode
 *                                           - Invalid deep standby end sources
 *                                           - Invalid deep standby end sources edges
 *                                           - Invalid power supply option for deep standby
 *                                           - Invalid IO port option for deep standby
 *                                           - Invalid output port state setting for standby or deep standby
 *                                           - Invalid sources for wake from standby mode
 *                                           - Invalid power supply option for standby
 *                                           - Invalid IO port option for standby
 *                                           - Invalid standby end sources
 *                                           - Invalid standby end sources edges
 **********************************************************************************************************************/
fsp_err_t r_lpm_configure (lpm_cfg_t const * const p_cfg)
{
#if LPM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    fsp_err_t err = r_lpm_mcu_specific_low_power_check(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    uint32_t snzcr = 0;
    uint32_t sbycr = 0;
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    uint32_t dpsbycr = 0;
#endif

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);

    /* Wait for ongoing operating mode transition (OPCMTSF, SOPCMTSF) */
    r_lpm_wait_for_operating_mode_flags();

    /* Configure registers for modes other than Sleep */
    if (LPM_MODE_SLEEP != p_cfg->low_power_mode)
    {
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY

        /* Configure Deep Software Standby registers. */
        if (LPM_MODE_DEEP == p_cfg->low_power_mode)
        {
            R_SYSTEM->DPSIER0 = (uint8_t) (p_cfg->deep_standby_cancel_source);
            R_SYSTEM->DPSIER1 = (uint8_t) (p_cfg->deep_standby_cancel_source >> 8U);
            R_SYSTEM->DPSIER2 = (uint8_t) (p_cfg->deep_standby_cancel_source >> 16U);
            R_SYSTEM->DPSIER3 = (uint8_t) (p_cfg->deep_standby_cancel_source >> 24U);

            R_SYSTEM->DPSIEGR0 = (uint8_t) (p_cfg->deep_standby_cancel_edge);
            R_SYSTEM->DPSIEGR1 = (uint8_t) (p_cfg->deep_standby_cancel_edge >> 8U);
            R_SYSTEM->DPSIEGR2 = (uint8_t) (p_cfg->deep_standby_cancel_edge >> 16U);

            dpsbycr = (R_SYSTEM_DPSBYCR_DPSBY_Msk |
                       (((uint32_t) p_cfg->io_port_state << R_SYSTEM_DPSBYCR_IOKEEP_Pos) &
                        R_SYSTEM_DPSBYCR_IOKEEP_Msk) |
                       (((uint32_t) p_cfg->power_supply_state << R_SYSTEM_DPSBYCR_DEEPCUT_Pos) &
                        R_SYSTEM_DPSBYCR_DEEPCUT_Msk));
        }
#endif

        /* Configure Snooze registers */
        if (LPM_MODE_STANDBY_SNOOZE == p_cfg->low_power_mode)
        {
            /* Configure RXD0 falling edge detect */
            if (LPM_SNOOZE_REQUEST_RXD0_FALLING == p_cfg->snooze_request_source)
            {
                snzcr = 1U << R_SYSTEM_SNZCR_RXDREQEN_Pos;
            }

            /* Set the request condition that can trigger entry in to snooze mode */
            R_SYSTEM->SNZREQCR = (uint32_t) p_cfg->snooze_request_source & UINT32_MAX;

#if BSP_FEATURE_LPM_HAS_SNZREQCR1 == 1
            R_SYSTEM->SNZREQCR1 = (uint32_t) (p_cfg->snooze_request_source >> LPM_SNZREQCR1_OFFSET) & UINT32_MAX;
#endif

            /* Enable/disable DTC operation */
            snzcr |= (uint32_t) (p_cfg->dtc_state_in_snooze << R_SYSTEM_SNZCR_SNZDTCEN_Pos);

            /* Set the source that can cause an exit from snooze to normal mode */
            R_ICU->SELSR0_b.SELS = R_ICU_SELSR0_SELS_Msk & p_cfg->snooze_cancel_sources;

            /* Set all sources that can cause an exit from snooze mode to software standby. */
            R_SYSTEM->SNZEDCR = (uint8_t) p_cfg->snooze_end_sources & UINT8_MAX;

#if BSP_FEATURE_LPM_HAS_SNZEDCR1 == 1
            R_SYSTEM->SNZEDCR1 = (uint8_t) (p_cfg->snooze_end_sources >> 8U) & UINT8_MAX;
#endif
        }

        /* Set SBYCR to Standby/Deep Standby. */
#if BSP_FEATURE_LPM_HAS_SBYCR_OPE
        sbycr = (((uint32_t) p_cfg->output_port_enable) << R_SYSTEM_SBYCR_OPE_Pos) | (1U << R_SYSTEM_SBYCR_SSBY_Pos);
#elif BSP_FEATURE_LPM_SBYCR_WRITE1_B14
        sbycr = (1U << R_SYSTEM_SBYCR_OPE_Pos) | (1U << R_SYSTEM_SBYCR_SSBY_Pos);
#else
        sbycr = (1U << R_SYSTEM_SBYCR_SSBY_Pos);
#endif

        R_ICU->WUPEN = (uint32_t) p_cfg->standby_wake_sources & UINT32_MAX;
#if BSP_FEATURE_ICU_HAS_WUPEN1 == 1
        R_ICU->WUPEN1 = (uint32_t) (p_cfg->standby_wake_sources >> LPM_WUPEN1_OFFSET) & UINT32_MAX;
#endif
    }
    else
    {
        /* Set SBYCR to Sleep mode. */
#if BSP_FEATURE_LPM_SBYCR_WRITE1_B14
        sbycr = 1U << R_SYSTEM_SBYCR_OPE_Pos;
#else
        sbycr = 0;
#endif
    }

#if LPM_CFG_STANDBY_LIMIT
    R_SYSTEM->SBYCR = (uint16_t) (sbycr & ~(1U << R_SYSTEM_SBYCR_SSBY_Pos));
#else
    R_SYSTEM->SBYCR = (uint16_t) sbycr;
#endif

    R_SYSTEM->SNZCR = (uint8_t) snzcr;

#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    R_SYSTEM->DPSBYCR = (uint8_t) dpsbycr;
#endif

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Check the clock settings
 *
 * @param[in]  clock_source  The clock source
 *
 * @retval     FSP_SUCCESS                   Clock settings are valid.
 * @retval     FSP_ERR_INVALID_MODE          One of the following:
 *                                           - HOCO was not system clock when using snooze mode with SCI0/RXD0.
 *                                           - HOCO was not stable when using snooze mode with SCI0/RXD0.
 *                                           - MOCO was running when using snooze mode with SCI0/RXD0.
 *                                           - MAIN OSCILLATOR was running when using snooze mode with SCI0/RXD0.
 *                                           - PLL was running when using snooze mode with SCI0/RXD0.
 **********************************************************************************************************************/
fsp_err_t r_lpm_check_clocks (uint32_t clock_source)
{
    /* Verify the clock source is HOCO */
    FSP_ERROR_RETURN(LPM_CLOCK_HOCO == clock_source, FSP_ERR_INVALID_MODE);

    /* Verify Moco, Main Osc and PLL are stopped. */
    FSP_ERROR_RETURN(1U == (*gp_lpm_clock_stp_registers[LPM_CLOCK_MOCO]), FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(1U == (*gp_lpm_clock_stp_registers[LPM_CLOCK_MAIN_OSC]), FSP_ERR_INVALID_MODE);
#if BSP_FEATURE_CGC_HAS_PLL
    FSP_ERROR_RETURN(1U == (*gp_lpm_clock_stp_registers[LPM_CLOCK_PLL]), FSP_ERR_INVALID_MODE);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Perform pre-WFI execution tasks, enter low power mode, Perform post-WFI execution tasks
 *
 * @note       This function will unlock and lock registers as needed
 *
 * @retval     FSP_SUCCESS                   Successfully entered and woke from low power mode.
 * @retval     FSP_ERR_INVALID_MODE          One of the following:
 *                                           - FLL function is enabled when requesting Software Standby.
 *                                           - HOCO was not system clock when using snooze mode with SCI0/RXD0.
 *                                           - HOCO was not stable when using snooze mode with SCI0/RXD0.
 *                                           - MOCO was running when using snooze mode with SCI0/RXD0.
 *                                           - MAIN OSCILLATOR was running when using snooze mode with SCI0/RXD0.
 *                                           - PLL was running when using snooze mode with SCI0/RXD0.
 *                                           - Unable to disable ocillator stop detect when using standby or deep standby.
 **********************************************************************************************************************/
fsp_err_t r_lpm_low_power_enter (lpm_instance_ctrl_t * const p_instance_ctrl)
{
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    uint32_t saved_opccr        = 0U;
    uint32_t saved_sopccr       = 0U;
    uint32_t saved_ostdcr_ostde = 0U;
 #if BSP_FEATURE_CGC_HOCOWTCR_SCI_SNOOZE_VALUE > 0
    uint32_t saved_hocowtcr = 0U;
    uint32_t new_hocowtcr   = 0U;
 #endif
 #if BSP_FEATURE_BSP_POWER_CHANGE_MSTP_REQUIRED
    uint32_t stopped_modules = 0;
 #endif
#endif
#if BSP_PRV_POWER_USE_DCDC
    bsp_power_mode_t power_mode = BSP_POWER_MODE_LDO;
#endif

    if (1U == R_SYSTEM->SBYCR_b.SSBY)
    {
        /* Execute pre-wfi standby tasks */

#if BSP_PRV_HOCO_USE_FLL

        /* If FLL is available it must not be active when entering Software Standby. */
        FSP_ERROR_RETURN(0U == R_SYSTEM->FLLCR1, FSP_ERR_INVALID_MODE);
#endif

        /* Get system clock */
        uint32_t clock_source = R_SYSTEM->SCKSCR;

#if !BSP_FEATURE_LPM_HAS_DEEP_STANDBY
        if (1U == R_SYSTEM->SNZCR_b.RXDREQEN)
        {
            /* Verify clock settings. */
            FSP_ERROR_RETURN(FSP_SUCCESS == r_lpm_check_clocks(clock_source), FSP_ERR_INVALID_MODE);
        }

        /* Enable writing to CGC register. */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
#else

        /* RA6 Series Only:
         * Save the OPCCR and SOPCCR registers. When transitioning from Software Standby mode to Normal or Snooze mode
         * these registers are overwritten. See Section 11.2.6 "Operating Power Control Register" in the RA6M3 manual
         * R01UM0004EU0110 */
        saved_opccr  = R_SYSTEM->OPCCR_b.OPCM;
        saved_sopccr = R_SYSTEM->SOPCCR_b.SOPCM;

 #if BSP_FEATURE_CGC_HOCOWTCR_SCI_SNOOZE_VALUE > 0

        /* Save HOCOWTCR_b.HSTS */
        saved_hocowtcr = R_SYSTEM->HOCOWTCR_b.HSTS;
 #endif

        if (0U == R_SYSTEM->DPSBYCR_b.DPSBY)
        {
            /* RA6 Series Only:
             * Check Snooze configuration settings. Set HOCOWTCR based on current configuration. See Section 11.2.1
             * "Standby Control Register" in the RA6M3 manual  R01UM0004EU0110 */
            if (1U == R_SYSTEM->SNZCR_b.RXDREQEN)
            {
                /* Verify clock settings. */
                FSP_ERROR_RETURN(FSP_SUCCESS == r_lpm_check_clocks(clock_source), FSP_ERR_INVALID_MODE);
 #if BSP_FEATURE_CGC_HOCOWTCR_SCI_SNOOZE_VALUE > 0
                new_hocowtcr = BSP_FEATURE_CGC_HOCOWTCR_SCI_SNOOZE_VALUE;
            }
            else
            {
                new_hocowtcr = BSP_FEATURE_CGC_HOCOWTCR_VALUE;
 #endif
            }

            /* Enable writing to CGC register. */
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);

 #if BSP_FEATURE_LPM_HAS_STCONR == 1

            /* Set STCONR based on the current system clock. */
            if (LPM_CLOCK_HOCO == clock_source)
            {
  #if BSP_FEATURE_CGC_HOCOWTCR_SCI_SNOOZE_VALUE > 0

                /* Set HOCOWTCR_b.HSTS when using HOCO as the system clock */
                R_SYSTEM->HOCOWTCR_b.HSTS = R_SYSTEM_HOCOWTCR_HSTS_Msk & (new_hocowtcr << R_SYSTEM_HOCOWTCR_HSTS_Pos);
  #endif

                R_SYSTEM->STCONR = LPM_SW_STANDBY_STCONR;
            }
            else
            {
                R_SYSTEM->STCONR = LPM_SW_STANDBY_WAKE_STCONR;
            }
 #endif
        }
        else
        {
            /* Enable writing to CGC register. */
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);

            /* Execute pre-wfi deep standby tasks */
            /* Clear the DOCDF flag to 0 before entering Deep Software Standby mode. */
            R_SYSTEM->SYOCDCR_b.DOCDF = 0U;

            /* Clear Deep Software Standby Interrupt Flag Registers. A dummy read is required before writing to DPSIFR.
             * See Section 11.2.16 "Deep Software Standby Interrupt Flag Register 0" in the
             * RA6M3 manual  R01UM0004EU0110 */
            R_SYSTEM->DPSIFR0;
            R_SYSTEM->DPSIFR0 = 0U;

            R_SYSTEM->DPSIFR1;
            R_SYSTEM->DPSIFR1 = 0U;

            R_SYSTEM->DPSIFR2;
            R_SYSTEM->DPSIFR2 = 0U;

            R_SYSTEM->DPSIFR3;
            R_SYSTEM->DPSIFR3 = 0U;
        }

        /* Save oscillator stop detect state. */
        saved_ostdcr_ostde       = R_SYSTEM->OSTDCR_b.OSTDE;
        R_SYSTEM->OSTDCR_b.OSTDE = 0U;

 #if BSP_FEATURE_BSP_POWER_CHANGE_MSTP_REQUIRED
        stopped_modules = bsp_prv_power_change_mstp_set();

        /* Delay for >750 ns if any modules changed state */
        if (0 != stopped_modules)
        {
            R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        }
 #endif
#endif
#if BSP_PRV_POWER_USE_DCDC

        /* DCDC cannot be used in Software Standby, so switch back to LDO if needed (see RA2L1 User's Manual
         * (R01UH0853EJ0100) Section 40.3 Usage Notes). */
        if (R_SYSTEM->DCDCCTL & R_SYSTEM_DCDCCTL_DCDCON_Msk)
        {
            power_mode = R_BSP_PowerModeSet(BSP_POWER_MODE_LDO_BOOST);
        }
#endif
    }

    if (LPM_MODE_STANDBY_SNOOZE == p_instance_ctrl->p_cfg->low_power_mode)
    {
        /* Enable Snooze mode (SNZCR.SNZE = 1) immediately before entering to Software Standby mode.
         * See Section 11.8.2 "Canceling Snooze Mode" in the RA6M3 manual  R01UM0004EU0110 */
        R_SYSTEM->SNZCR_b.SNZE = 1;

        /* Dummy read required.
         * infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dai0321a/BIHICBGB.html */
        R_SYSTEM->SNZCR;
    }

    /* DSB should be last instruction executed before WFI
     * infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dai0321a/BIHICBGB.html */
    __DSB();

    __WFI();

    /* Disable Snooze mode (SNZCR.SNZE = 0) immediately after canceling Snooze mode.
     * See Section 11.8.2 "Canceling Snooze Mode" in the RA6M3 manual  R01UM0004EU0110 */
    R_SYSTEM->SNZCR_b.SNZE = 0;

#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY || (BSP_PRV_POWER_USE_DCDC)
    if (1U == R_SYSTEM->SBYCR_b.SSBY)
    {
 #if BSP_FEATURE_LPM_HAS_DEEP_STANDBY

        /* Wait for ongoing operating mode transition (OPCMTSF, SOPCMTSF) */
        r_lpm_wait_for_operating_mode_flags();

        /* Restore system registers to the values prior to entering standby. */
        R_SYSTEM->OPCCR          = saved_opccr & R_SYSTEM_OPCCR_OPCM_Msk;
        R_SYSTEM->SOPCCR         = saved_sopccr & R_SYSTEM_SOPCCR_SOPCM_Msk;
        R_SYSTEM->OSTDCR_b.OSTDE = 0x1U & saved_ostdcr_ostde;
  #if BSP_FEATURE_CGC_HOCOWTCR_SCI_SNOOZE_VALUE > 0
        R_SYSTEM->HOCOWTCR_b.HSTS = R_SYSTEM_HOCOWTCR_HSTS_Msk & (saved_hocowtcr << R_SYSTEM_HOCOWTCR_HSTS_Pos);
  #endif

        /* Disable writing to CGC register. */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

  #if BSP_FEATURE_BSP_POWER_CHANGE_MSTP_REQUIRED
        bsp_prv_power_change_mstp_clear(stopped_modules);
  #endif
 #endif
 #if BSP_PRV_POWER_USE_DCDC
        if (power_mode < BSP_POWER_MODE_LDO)
        {
            /* Switch back to DCDC if it was enabled before. */
            R_BSP_PowerModeSet(power_mode);
        }
 #endif
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Wait for opccr and sopccr transition flags to clear.
 **********************************************************************************************************************/
void r_lpm_wait_for_operating_mode_flags (void)
{
    /* Wait for transition to complete. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->OPCCR_b.OPCMTSF, 0U);

    /* Wait for transition to complete. */
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SOPCCR_b.SOPCMTSF, 0U);
}
