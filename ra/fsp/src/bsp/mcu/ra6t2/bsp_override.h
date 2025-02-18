/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA6T2
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA6T2) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

#include "bsp_elc.h"

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */
#define BSP_OVERRIDE_LPM_SNOOZE_CANCEL_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Snooze cancel control */
typedef enum e_lpm_snooze_cancel
{
    LPM_SNOOZE_CANCEL_SOURCE_NONE         = ELC_EVENT_NONE,         ///< No snooze cancel source
    LPM_SNOOZE_CANCEL_SOURCE_SCI0_AM      = ELC_EVENT_SCI0_AM,      ///< SCI0 address match event
    LPM_SNOOZE_CANCEL_SOURCE_DTC_COMPLETE = ELC_EVENT_DTC_COMPLETE, ///< DTC transfer completion
    LPM_SNOOZE_CANCEL_SOURCE_DOC_DOPCI    = ELC_EVENT_DOC_INT,      ///< Data operation circuit interrupt
} lpm_snooze_cancel_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
