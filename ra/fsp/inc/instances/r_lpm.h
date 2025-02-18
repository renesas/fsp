/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup LPM
 * @{
 **********************************************************************************************************************/

#ifndef R_LPM_H
#define R_LPM_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_lpm_cfg.h"
#include "r_lpm_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** LPM private control block. DO NOT MODIFY. Initialization occurs when R_LPM_Open() is called. */
typedef struct st_lpm_instance_ctrl
{
    uint32_t          lpm_open;        // Indicates whether the open() API has been successfully called.
    lpm_cfg_t const * p_cfg;           // Pointer to initial configurations
} lpm_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const lpm_api_t g_lpm_on_lpm;

/** @endcond */

fsp_err_t R_LPM_Open(lpm_ctrl_t * const p_api_ctrl, lpm_cfg_t const * const p_cfg);
fsp_err_t R_LPM_Close(lpm_ctrl_t * const p_api_ctrl);
fsp_err_t R_LPM_LowPowerReconfigure(lpm_ctrl_t * const p_api_ctrl, lpm_cfg_t const * const p_cfg);
fsp_err_t R_LPM_LowPowerModeEnter(lpm_ctrl_t * const p_api_ctrl);
fsp_err_t R_LPM_IoKeepClear(lpm_ctrl_t * const p_api_ctrl);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup LPM)
 **********************************************************************************************************************/
