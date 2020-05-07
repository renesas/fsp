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

#define BSP_CLOCK_CFG_MAIN_OSC_POPULATED           (0)
#define BSP_CLOCK_CFG_MAIN_OSC_WAIT                (9)
#define BSP_CLOCK_CFG_MAIN_OSC_CLOCK_SOURCE        (0)
#define BSP_CLOCK_CFG_SUBCLOCK_POPULATED           (0)
#define BSP_CLOCK_CFG_SUBCLOCK_DRIVE               (0)
#define BSP_CLOCK_CFG_SUBCLOCK_STABILIZATION_MS    (1000U)

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
