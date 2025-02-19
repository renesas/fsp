/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_DAC8_H
#define R_DAC8_H

/*******************************************************************************************************************//**
 * @addtogroup DAC8
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_dac8_cfg.h"
#include "r_dac_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DAC8 instance control block.  DO NOT INITIALIZE.  */
typedef struct st_dac8_instance_ctrl
{
    void   * p_reg;                    // Pointer to DAC base register
    uint8_t  channel;                  // ID associated with this DAC channel
    uint8_t  channel_started;          // DAC operation on channel started
    uint32_t channel_opened;           // DAC channel open
} dac8_instance_ctrl_t;

typedef enum e_dac8_mode
{
    DAC8_MODE_NORMAL,                  ///< DAC Normal mode
    DAC8_MODE_REAL_TIME                ///< DAC Real-time (event link) mode
} dac8_mode_t;

/** DAC8 extended configuration */
typedef struct st_dac8_extended_cfg
{
    bool        enable_charge_pump;    ///< Enable DAC charge pump
    dac8_mode_t dac_mode;              ///< DAC mode
} dac8_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const dac_api_t g_dac_on_dac8;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_DAC8_Open(dac_ctrl_t * const p_ctrl, dac_cfg_t const * const p_cfg);
fsp_err_t R_DAC8_Close(dac_ctrl_t * const p_ctrl);
fsp_err_t R_DAC8_Write(dac_ctrl_t * const p_ctrl, uint16_t value);
fsp_err_t R_DAC8_Start(dac_ctrl_t * const p_ctrl);
fsp_err_t R_DAC8_Stop(dac_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup DAC8)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_DAC8_H
