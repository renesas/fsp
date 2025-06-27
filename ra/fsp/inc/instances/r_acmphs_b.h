/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_ACMPHS_B_H
#define R_ACMPHS_B_H

/*******************************************************************************************************************//**
 * @addtogroup ACMPHS_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_comparator_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum
{
    ACMPHS_B_INPUT_CMPIN01 = 0,
    ACMPHS_B_INPUT_CMPIN02 = 1,
    ACMPHS_B_INPUT_CMPIN03 = 2,
    ACMPHS_B_INPUT_CMPREF0 = 3,
    ACMPHS_B_INPUT_CMPIN1  = 4,
} acmphs_b_input_t;

typedef enum
{
    ACMPHS_B_REFERENCE_CMPREF0   = 0,
    ACMPHS_B_REFERENCE_CMPIN01   = 1,
    ACMPHS_B_REFERENCE_CMPIN02   = 2,
    ACMPHS_B_REFERENCE_CMPIN03   = 3,
    ACMPHS_B_REFERENCE_INTERNAL0 = 4,
    ACMPHS_B_REFERENCE_CMPREF1   = 0,
    ACMPHS_B_REFERENCE_INTERNAL1 = 1
} acmphs_b_reference_t;

/* ACMPHS_B extended configuration */
typedef struct st_acmphs_b_extended_cfg
{
    acmphs_b_input_t     input_voltage;
    acmphs_b_reference_t reference_voltage;
} r_acmphs_b_extended_cfg_t;

/* Channel instance control block. DO NOT INITIALIZE.  Initialization occurs in @ref comparator_api_t::open. */
typedef struct st_acmphs_b_instance_ctrl
{
    uint32_t                 open;     // Used to determine if channel control block is in use
    const comparator_cfg_t * p_cfg;    // Pointer to initial configurations
    uint8_t output_enabled;            // 0: output disabled, 1: output enabled
} acmphs_b_instance_ctrl_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/* @cond INC_HEADER_DEFS_SEC */
/* Filled in Interface API structure for this Instance. */
extern const comparator_api_t g_comparator_on_acmphs_b;

/* @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_B_Open(comparator_ctrl_t * p_ctrl, comparator_cfg_t const * const p_cfg);
fsp_err_t R_ACMPHS_B_OutputEnable(comparator_ctrl_t * const p_ctrl);
fsp_err_t R_ACMPHS_B_InfoGet(comparator_ctrl_t * const p_ctrl, comparator_info_t * const p_info);
fsp_err_t R_ACMPHS_B_StatusGet(comparator_ctrl_t * const p_ctrl, comparator_status_t * const p_status);
fsp_err_t R_ACMPHS_B_Close(comparator_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup ACMPHS_B)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ACMPHS_B_H
