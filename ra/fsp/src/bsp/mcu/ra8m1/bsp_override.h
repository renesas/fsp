/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
