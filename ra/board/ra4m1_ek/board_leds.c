/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : board_leds.c
 * Description  : This module has information about the LEDs on this board.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_RA4M1_EK_LEDS
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#if defined(BOARD_RA4M1_EK)

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/** Array of LED IOPORT pins. */
static const uint16_t g_bsp_prv_leds[] =
{
    (uint16_t) BSP_IO_PORT_01_PIN_06,  ///< LED1 - Red
};

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/** Structure with LED information for this board. */

const bsp_leds_t g_bsp_leds =
{
    .led_count = (uint16_t) ((sizeof(g_bsp_prv_leds) / sizeof(g_bsp_prv_leds[0]))),
    .p_leds    = &g_bsp_prv_leds[0]
};

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

#endif

/** @} (end addtogroup BSP_RA4M1_EK_LEDS) */
