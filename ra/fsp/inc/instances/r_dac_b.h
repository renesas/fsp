/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_DAC_B_H
#define R_DAC_B_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_dac_b_cfg.h"
#include "r_dac_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup DAC_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DAC Vref Type */
typedef enum e_dac_b_vrefh
{
    DAC_B_VREFH_NORMAL = 0,            ///< VREFH >= 2.7v
    DAC_B_VREFH_LOW    = 1,            ///< VREFH < 2.7v
} dac_b_vrefh_t;

/** DAC instance control block. */
typedef struct st_dac_b_instance_ctrl
{
    uint8_t         channel;           // DAC channel number
    uint32_t        channel_opened;    // DAC Driver ID
    R_DAC_B0_Type * p_reg;             // Base register for this channel
} dac_b_instance_ctrl_t;

/** DAC extended configuration */
typedef struct st_dac_b_extended_cfg
{
    bool              internal_output_enabled; ///< Internal output enable available on selected MCUs.
    dac_data_format_t data_format;             ///< Data format
    dac_b_vrefh_t     vrefh;                   ///< High voltage reference range
} dac_b_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const dac_api_t g_dac_on_dac_b;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_DAC_B_Open(dac_ctrl_t * p_api_ctrl, dac_cfg_t const * const p_cfg);
fsp_err_t R_DAC_B_Write(dac_ctrl_t * p_api_ctrl, uint16_t value);
fsp_err_t R_DAC_B_Start(dac_ctrl_t * p_api_ctrl);
fsp_err_t R_DAC_B_Stop(dac_ctrl_t * p_api_ctrl);
fsp_err_t R_DAC_B_Close(dac_ctrl_t * p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup DAC_B)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_DAC_B_H
