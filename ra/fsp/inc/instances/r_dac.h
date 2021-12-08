/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_DAC_H
#define R_DAC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_dac_cfg.h"
#include "r_dac_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup DAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DAC instance control block. */
typedef struct st_dac_instance_ctrl
{
    uint8_t      channel;                  // DAC channel number
    uint8_t      channel_index;            // Channel index to access bits
    uint32_t     channel_opened;           // DAC Driver ID
    bool         output_amplifier_enabled; // DAC Output amplifier (on selected MCUs) enabled/disabled.
    bool         internal_output_enabled;  // Output provided to internal modules (on selected MCUs) enabled/disabled.
    R_DAC_Type * p_reg;                    // Base register for this channel
} dac_instance_ctrl_t;

/** DAC extended configuration */
typedef struct st_dac_extended_cfg
{
    bool              enable_charge_pump;       ///< Enable DAC charge pump available on selected MCUs.
    bool              output_amplifier_enabled; ///< Output amplifier enable available on selected MCUs.
    bool              internal_output_enabled;  ///< Internal output enable available on selected MCUs.
    dac_data_format_t data_format;              ///< Data format
} dac_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const dac_api_t g_dac_on_dac;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_DAC_Open(dac_ctrl_t * p_api_ctrl, dac_cfg_t const * const p_cfg);
fsp_err_t R_DAC_Write(dac_ctrl_t * p_api_ctrl, uint16_t value);
fsp_err_t R_DAC_Start(dac_ctrl_t * p_api_ctrl);
fsp_err_t R_DAC_Stop(dac_ctrl_t * p_api_ctrl);
fsp_err_t R_DAC_Close(dac_ctrl_t * p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup DAC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_DAC_H
