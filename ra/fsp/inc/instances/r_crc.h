/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CRC_H
#define R_CRC_H

/*******************************************************************************************************************//**
 * @addtogroup CRC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_crc_cfg.h"
#include "r_crc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Driver instance control structure. */
typedef struct st_crc_instance_ctrl
{
    uint32_t          open;
    const crc_cfg_t * p_cfg;           // Pointer to initial configurations
} crc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const crc_api_t g_crc_on_crc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CRC_Open(crc_ctrl_t * const p_ctrl, crc_cfg_t const * const p_cfg);
fsp_err_t R_CRC_Close(crc_ctrl_t * const p_ctrl);
fsp_err_t R_CRC_Calculate(crc_ctrl_t * const p_ctrl, crc_input_t * const p_crc_input, uint32_t * calculatedValue);
fsp_err_t R_CRC_CalculatedValueGet(crc_ctrl_t * const p_ctrl, uint32_t * calculatedValue);
fsp_err_t R_CRC_SnoopEnable(crc_ctrl_t * const p_ctrl, uint32_t crc_seed);
fsp_err_t R_CRC_SnoopDisable(crc_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup CRC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
