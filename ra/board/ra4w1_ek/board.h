/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup BOARDS
 * @defgroup BOARD_RA4W1_EK BSP for the EK-RA4W1
 * @brief BSP for the EK-RA4W1
 *
 * The EK-RA4W1 is a development kit for the Renesas RA Flex RA4W1 microcontroller. This board has connections
 * for PMOD and USB as well as headers for Arduino shield modules. An onboard Bluetooth antenna is available with an
 * optional connection for an external antenna.
 *
 * @note This board does not ship with main or subclock oscillators populated.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BOARD_H
#define BOARD_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/* BSP Board Specific Includes. */
#include "board_init.h"
#include "board_leds.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BOARD_RA4W1_EK

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/** @} (end defgroup BOARD_RA4W1_EK) */

#endif
