/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_KINT_H
#define R_KINT_H

/*******************************************************************************************************************//**
 * @addtogroup KINT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_keymatrix_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Channel instance control block. DO NOT INITIALIZE. Initialization occurs when @ref keymatrix_api_t::open is called. */
typedef struct st_kint_instance_ctrl
{
    uint32_t                open;
    keymatrix_cfg_t const * p_cfg;
} kint_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const keymatrix_api_t g_keymatrix_on_kint;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_KINT_Open(keymatrix_ctrl_t * const p_api_ctrl, keymatrix_cfg_t const * const p_cfg);
fsp_err_t R_KINT_Enable(keymatrix_ctrl_t * const p_api_ctrl);
fsp_err_t R_KINT_Disable(keymatrix_ctrl_t * const p_api_ctrl);
fsp_err_t R_KINT_Close(keymatrix_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end addtogroup KINT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
