/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_POWER_H
#define BSP_POWER_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2L1
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if BSP_FEATURE_BSP_HAS_DCDC_REGULATOR
 #define BSP_PRV_POWER_USE_DCDC       (BSP_CFG_DCDC_ENABLE)
#else
 #define BSP_PRV_POWER_USE_DCDC       (0)
#endif

#define BSP_PRV_POWER_DCDC_DISABLE    (0)
#define BSP_PRV_POWER_DCDC_MANUAL     (1)
#define BSP_PRV_POWER_DCDC_STARTUP    (2)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Voltage regulator mode */
typedef enum e_bsp_power_mode_t
{
    BSP_POWER_MODE_DCDC_2V4_TO_2V7 = 3, ///< DCDC mode; 2.4V to 2.7V supply
    BSP_POWER_MODE_DCDC_2V7_TO_3V6 = 0, ///< DCDC mode; 2.7V to 3.6V supply
    BSP_POWER_MODE_DCDC_3V6_TO_4V5 = 1, ///< DCDC mode; 3.6V to 4.5V supply
    BSP_POWER_MODE_DCDC_4V5_TO_5V5 = 2, ///< DCDC mode; 4.5V to 5.5V supply

    BSP_POWER_MODE_LDO       = 0x90,    ///< LDO mode
    BSP_POWER_MODE_LDO_BOOST = 0xB0     // Alternate DCDCCTL value for entering subclock and low-power modes
                                        // (see RA2L1 User's Manual (R01UH0853EJ0100) Section 10.5.1 (5))
} bsp_power_mode_t;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

bsp_power_mode_t R_BSP_PowerModeSet(bsp_power_mode_t mode);

/*******************************************************************************************************************//**
 * @} (end addtogroup BSP_MCU_RA2L1)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
