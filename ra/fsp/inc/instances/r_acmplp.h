/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_ACMPLP_H
#define R_ACMPLP_H

/*******************************************************************************************************************//**
 * @addtogroup ACMPLP
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

/*********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum
{
    ACMPLP_INPUT_NONE    = 0,
    ACMPLP_INPUT_CMPIN   = 1,
    ACMPLP_INPUT_AMPO    = 2,          ///< Not available on all MCUs
    ACMPLP_INPUT_CMPIN_1 = 4,          ///< Not available on all MCUs
} acmplp_input_t;

typedef enum
{
    ACMPLP_REFERENCE_NONE     = 0,
    ACMPLP_REFERENCE_CMPREF   = 1,
    ACMPLP_REFERENCE_DAC8     = 2,
    ACMPLP_REFERENCE_CMPREF_1 = 4,     ///< Not available on all MCUs
} acmplp_reference_t;

/* ACMPLP extended configuration */
typedef struct
{
    acmplp_input_t     input_voltage;
    acmplp_reference_t reference_voltage;
} r_acmplp_extended_cfg_t;

/* Channel instance control block. DO NOT INITIALIZE.  Initialization occurs in @ref comparator_api_t::open. */
typedef struct st_acmplp_instance_ctrl
{
    uint32_t                 open;     // Used to determine if channel control block is in use
    const comparator_cfg_t * p_cfg;    // Pointer to initial configurations
    uint8_t output_enabled;            // 0: output disabled, 1: output enabled
} acmplp_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const comparator_api_t g_comparator_on_acmplp;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ACMPLP_Open(comparator_ctrl_t * const p_ctrl, comparator_cfg_t const * const p_cfg);
fsp_err_t R_ACMPLP_OutputEnable(comparator_ctrl_t * const p_ctrl);
fsp_err_t R_ACMPLP_InfoGet(comparator_ctrl_t * const p_ctrl, comparator_info_t * const p_info);
fsp_err_t R_ACMPLP_StatusGet(comparator_ctrl_t * const p_ctrl, comparator_status_t * const p_status);
fsp_err_t R_ACMPLP_Close(comparator_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup ACMPLP)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ACMPLP_H
