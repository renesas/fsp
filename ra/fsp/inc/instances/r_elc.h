/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup ELC
 * @{
 **********************************************************************************************************************/

#ifndef R_ELC_H
#define R_ELC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_elc_cfg.h"
#include "r_elc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** ELC private control block. DO NOT MODIFY. Initialization occurs when R_ELC_Open() is called. */
typedef struct st_elc_instance_ctrl
{
    uint32_t open;
    void   * p_context;
} elc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const elc_api_t g_elc_on_elc;

/** @endcond */

/**********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_ELC_Open(elc_ctrl_t * const p_ctrl, elc_cfg_t const * const p_cfg);
fsp_err_t R_ELC_Close(elc_ctrl_t * const p_ctrl);
fsp_err_t R_ELC_SoftwareEventGenerate(elc_ctrl_t * const p_ctrl, elc_software_event_t event_number);
fsp_err_t R_ELC_LinkSet(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral, elc_event_t signal);
fsp_err_t R_ELC_LinkBreak(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral);
fsp_err_t R_ELC_Enable(elc_ctrl_t * const p_ctrl);
fsp_err_t R_ELC_Disable(elc_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ELC_H

/*******************************************************************************************************************//**
 * @} (end defgroup ELC)
 **********************************************************************************************************************/
