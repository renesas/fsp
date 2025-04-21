/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA8M1
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA8M1) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */

#define BSP_OVERRIDE_CGC_SYS_CLOCK_DIV_T
#define BSP_OVERRIDE_GROUP_IRQ_T
#define BSP_OVERRIDE_LVD_PERIPHERAL_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** System clock divider values - The individually selectable divider of each of the system clocks, ICLK, BCLK, FCLK,
 * PCLKS A-D.  */
typedef enum e_cgc_sys_clock_div
{
    CGC_SYS_CLOCK_DIV_1  = 0,          ///< System clock divided by 1
    CGC_SYS_CLOCK_DIV_2  = 1,          ///< System clock divided by 2
    CGC_SYS_CLOCK_DIV_4  = 2,          ///< System clock divided by 4
    CGC_SYS_CLOCK_DIV_8  = 3,          ///< System clock divided by 8
    CGC_SYS_CLOCK_DIV_16 = 4,          ///< System clock divided by 16
    CGC_SYS_CLOCK_DIV_32 = 5,          ///< System clock divided by 32
    CGC_SYS_CLOCK_DIV_64 = 6,          ///< System clock divided by 64
    CGC_SYS_CLOCK_DIV_3  = 8,          ///< System clock divided by 3
    CGC_SYS_CLOCK_DIV_6  = 9,          ///< System clock divided by 6
    CGC_SYS_CLOCK_DIV_12 = 10,         ///< System clock divided by 12
} cgc_sys_clock_div_t;

/* Which interrupts can have callbacks registered. */
typedef enum e_bsp_grp_irq
{
    BSP_GRP_IRQ_IWDT_ERROR      = 0,   ///< IWDT underflow/refresh error has occurred
    BSP_GRP_IRQ_WDT_ERROR       = 1,   ///< WDT underflow/refresh error has occurred
    BSP_GRP_IRQ_LVD1            = 2,   ///< Voltage monitoring 1 interrupt
    BSP_GRP_IRQ_LVD2            = 3,   ///< Voltage monitoring 2 interrupt
    BSP_GRP_IRQ_OSC_STOP_DETECT = 6,   ///< Oscillation stop is detected
    BSP_GRP_IRQ_NMI_PIN         = 7,   ///< NMI Pin interrupt
    BSP_GRP_IRQ_MPU_BUS_TZF     = 12,  ///< MPU Bus or TrustZone Filter Error
    BSP_GRP_IRQ_COMMON_MEMORY   = 13,  ///< SRAM ECC or SRAM Parity Error
    BSP_GRP_IRQ_LOCKUP          = 15,  ///< LockUp Error
} bsp_grp_irq_t;

/** The thresholds supported by each MCU are in the MCU User's Manual as well as
 *  in the r_lvd module description on the stack tab of the RA project. */
typedef enum
{
    LVD_THRESHOLD_MONITOR_LEVEL_3_86V = 0x03UL, ///< 3.86V
    LVD_THRESHOLD_MONITOR_LEVEL_3_14V = 0x04UL, ///< 3.14V
    LVD_THRESHOLD_MONITOR_LEVEL_3_10V = 0x05UL, ///< 3.10V
    LVD_THRESHOLD_MONITOR_LEVEL_3_08V = 0x06UL, ///< 3.08V
    LVD_THRESHOLD_MONITOR_LEVEL_2_85V = 0x07UL, ///< 2.85V
    LVD_THRESHOLD_MONITOR_LEVEL_2_83V = 0x08UL, ///< 2.83V
    LVD_THRESHOLD_MONITOR_LEVEL_2_80V = 0x09UL, ///< 2.80V
    LVD_THRESHOLD_MONITOR_LEVEL_2_62V = 0x0AUL, ///< 2.62V
    LVD_THRESHOLD_MONITOR_LEVEL_2_33V = 0x0BUL, ///< 2.33V
    LVD_THRESHOLD_MONITOR_LEVEL_1_90V = 0x0CUL, ///< 1.90V
    LVD_THRESHOLD_MONITOR_LEVEL_1_86V = 0x0DUL, ///< 1.86V
    LVD_THRESHOLD_MONITOR_LEVEL_1_74V = 0x0EUL, ///< 1.74V
    LVD_THRESHOLD_MONITOR_LEVEL_1_71V = 0x0FUL, ///< 1.71V
    LVD_THRESHOLD_NOT_AVAILABLE       = 0xFFUL, ///< Not Used
} lvd_threshold_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
