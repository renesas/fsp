/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA8E2
 * @{
 **********************************************************************************************************************/

#ifndef R_OSPI_B_DEVICE_TYPES_H
#define R_OSPI_B_DEVICE_TYPES_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_OVERRIDE_BSP_CLOCKS_OCTACLK_DIV_T

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** OCTACLK divider values. */
typedef enum e_bsp_clocks_octaclk_div
{
    BSP_CLOCKS_OCTACLK_DIV_1 = 0,      ///< Divide OCTA source clock by 1
    BSP_CLOCKS_OCTACLK_DIV_2,          ///< Divide OCTA source clock by 2
    BSP_CLOCKS_OCTACLK_DIV_4,          ///< Divide OCTA source clock by 4
    BSP_CLOCKS_OCTACLK_DIV_6,          ///< Divide OCTA source clock by 6
    BSP_CLOCKS_OCTACLK_DIV_8,          ///< Divide OCTA source clock by 8
    BSP_CLOCKS_OCTACLK_DIV_3,          ///< Divide OCTA source clock by 3
    BSP_CLOCKS_OCTACLK_DIV_5,          ///< Divide OCTA source clock by 5
} bsp_clocks_octaclk_div_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/** @} (end addtogroup BSP_MCU_RA8E2) */
