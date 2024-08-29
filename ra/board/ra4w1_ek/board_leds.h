/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup BOARD_EK_RA4W1
 * @defgroup BOARD_EK_RA4W1_LEDS Board LEDs
 * @brief LED information for this board.
 *
 * This is code specific to the EK-RA4W1. It includes info on the number of LEDs and which pins are they
 * are on.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BOARD_LEDS_H
#define BOARD_LEDS_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Information on how many LEDs and what pins they are on. */
typedef struct st_bsp_leds
{
    uint16_t         led_count;        ///< The number of LEDs on this board
    uint16_t const * p_leds;           ///< Pointer to an array of IOPORT pins for controlling LEDs
} bsp_leds_t;

/** Available user-controllable LEDs on this board. These enums can be can be used to index into the array of LED pins
 * found in the bsp_leds_t structure. */
typedef enum e_bsp_led
{
    BSP_LED_LED0 = 0,                  ///< LED0
    BSP_LED_LED1 = 1,                  ///< LED1
} bsp_led_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public Functions
 **********************************************************************************************************************/

#endif

/** @} (end defgroup BOARD_EK_RA4W1_LEDS) */
