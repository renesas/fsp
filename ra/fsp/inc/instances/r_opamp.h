/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_OPAMP_H
#define R_OPAMP_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_opamp_cfg.h"
#include "r_opamp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup OPAMP
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Version of code that implements the API defined in this file */

#define OPAMP_MASK_CHANNEL_0    (1U << 0)
#define OPAMP_MASK_CHANNEL_1    (1U << 1)
#define OPAMP_MASK_CHANNEL_2    (1U << 2)
#define OPAMP_MASK_CHANNEL_3    (1U << 3)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Start and stop trigger for the op-amp. */
typedef enum e_opamp_trigger
{
    OPAMP_TRIGGER_SOFTWARE_START_SOFTWARE_STOP = 0, ///< Start and stop with APIs
    OPAMP_TRIGGER_AGT_START_SOFTWARE_STOP      = 1, ///< Start by AGT compare match and stop with API
    OPAMP_TRIGGER_AGT_START_ADC_STOP           = 3, ///< Start by AGT compare match and stop after ADC conversion
} opamp_trigger_t;

/** Which AGT timer starts the op-amp. Only applies to channels if OPAMP_TRIGGER_AGT_START_SOFTWARE_STOP or
 * OPAMP_TRIGGER_AGT_START_ADC_STOP is selected for the channel. If OPAMP_TRIGGER_SOFTWARE_START_SOFTWARE_STOP is
 * selected for a channel, then no AGT compare match event will start that op-amp channel. */
typedef enum e_opamp_agt_link
{
    /** OPAMP channel 0 and 2 are started by AGT1 compare match.  OPAMP channel 1 and 3 are started by AGT0 compare
     * match. */
    OPAMP_AGT_LINK_AGT1_OPAMP_0_2_AGT0_OPAMP_1_3 = 0,

    /** OPAMP channel 0 and 1 are started by AGT1 compare match.  OPAMP channel 2 and 3 are started by AGT0 compare
     * match. */
    OPAMP_AGT_LINK_AGT1_OPAMP_0_1_AGT0_OPAMP_2_3 = 1,

    /** All OPAMP channels are started by AGT1 compare match. */
    OPAMP_AGT_LINK_AGT1_OPAMP_0_1_2_3 = 3,
} opamp_agt_link_t;

/** Op-amp mode. */
typedef enum e_opamp_mode
{
    OPAMP_MODE_LOW_POWER    = 0,       ///< Low power mode
    OPAMP_MODE_MIDDLE_SPEED = 1,       ///< Middle speed mode (not supported on all MCUs)
    OPAMP_MODE_HIGH_SPEED   = 3        ///< High speed mode
} opamp_mode_t;

/* Op-amp trim state. */
typedef enum e_opamp_priv_trim_state
{
    OPAMP_PRIV_TRIM_STATE_INVALID = -1,
    OPAMP_PRIV_TRIM_STATE_END     = 0,
    OPAMP_PRIV_TRIM_STATE_BIT_0   = 0,
    OPAMP_PRIV_TRIM_STATE_BIT_1   = 1,
    OPAMP_PRIV_TRIM_STATE_BIT_2   = 2,
    OPAMP_PRIV_TRIM_STATE_BIT_3   = 3,
    OPAMP_PRIV_TRIM_STATE_BIT_4   = 4,
    OPAMP_PRIV_TRIM_STATE_BEGIN   = 5,
} opamp_priv_trim_state_t;

/** Options to connect AMPnPS pins. */
typedef enum e_opamp_plus_input
{
    OPAMP_PLUS_INPUT_NONE   = 0,       ///< No Connection
    OPAMP_PLUS_INPUT_AMPPS0 = 1,       ///< Set AMPPS0. See hardware manual for channel specific options
    OPAMP_PLUS_INPUT_AMPPS1 = 2,       ///< Set AMPPS1. See hardware manual for channel specific options
    OPAMP_PLUS_INPUT_AMPPS2 = 4,       ///< Set AMPPS2. See hardware manual for channel specific options
    OPAMP_PLUS_INPUT_AMPPS3 = 8,       ///< Set AMPPS3. See hardware manual for channel specific options
    OPAMP_PLUS_INPUT_AMPPS7 = 128,     ///< Set AMPPS7. See hardware manual for channel specific options
} opamp_plus_input_t;

/** Options to connect AMPnMS pins. */
typedef enum e_opamp_minus_input
{
    OPAMP_MINUS_INPUT_NONE   = 0,      ///< No Connection
    OPAMP_MINUS_INPUT_AMPMS0 = 1,      ///< Set AMPMS0. See hardware manual for channel specific options
    OPAMP_MINUS_INPUT_AMPMS1 = 2,      ///< Set AMPMS1. See hardware manual for channel specific options
    OPAMP_MINUS_INPUT_AMPMS2 = 4,      ///< Set AMPMS2. See hardware manual for channel specific options
    OPAMP_MINUS_INPUT_AMPMS3 = 8,      ///< Set AMPMS3. See hardware manual for channel specific options
    OPAMP_MINUS_INPUT_AMPMS4 = 16,     ///< Set AMPMS4. See hardware manual for channel specific options
    OPAMP_MINUS_INPUT_AMPMS7 = 128,    ///< Set AMPMS7. See hardware manual for channel specific options
} opamp_minus_input_t;

/** Options to connect AMP0OS pin. */
typedef enum e_opamp_output
{
    OPAMP_OUTPUT_NONE   = 0,           ///< No Connection
    OPAMP_OUTPUT_AMPOS0 = 1,           ///< Set AMPOS0. See hardware manual for channel specific options
    OPAMP_OUTPUT_AMPOS1 = 2,           ///< Set AMPOS1. See hardware manual for channel specific options
    OPAMP_OUTPUT_AMPOS2 = 4,           ///< Set AMPOS2. See hardware manual for channel specific options
    OPAMP_OUTPUT_AMPOS3 = 8,           ///< Set AMPOS3. See hardware manual for channel specific options
} opamp_output_t;

/** OPAMP configuration extension. This extension is required and must be provided in opamp_cfg_t::p_extend. */
typedef struct st_opamp_extended_cfg
{
    /** Configure which AGT links are paired to which channel. Only applies to channels if
     * OPAMP_TRIGGER_AGT_START_SOFTWARE_STOP or OPAMP_TRIGGER_AGT_START_ADC_STOP is selected for the channel. */
    opamp_agt_link_t    agt_link;
    opamp_mode_t        mode;                      ///< Low power, middle speed, or high speed mode
    opamp_trigger_t     trigger_channel_0;         ///< Start and stop triggers for channel 0
    opamp_trigger_t     trigger_channel_1;         ///< Start and stop triggers for channel 1
    opamp_trigger_t     trigger_channel_2;         ///< Start and stop triggers for channel 2
    opamp_trigger_t     trigger_channel_3;         ///< Start and stop triggers for channel 3
    opamp_plus_input_t  plus_input_select_opamp0;  ///< OPAMP0+ connection
    opamp_minus_input_t minus_input_select_opamp0; ///< OPAMP0- connection
    opamp_output_t      output_select_opamp0;      ///< OPAMP0O connection
    opamp_plus_input_t  plus_input_select_opamp1;  ///< OPAMP1+ connection
    opamp_minus_input_t minus_input_select_opamp1; ///< OPAMP1- connection
    opamp_plus_input_t  plus_input_select_opamp2;  ///< OPAMP2+ connection
    opamp_minus_input_t minus_input_select_opamp2; ///< OPAMP2- connection
} opamp_extended_cfg_t;

/** OPAMP instance control block. DO NOT INITIALIZE.  Initialized in @ref opamp_api_t::open(). */
typedef struct
{
    opamp_cfg_t const     * p_cfg;        // Pointer to the configuration structure
    uint32_t                opened;       // Boolean to verify that the Unit has been initialized
    opamp_priv_trim_state_t trim_state;   // Trim state for each op-amp
    uint8_t                 trim_channel; // Channel
    opamp_trim_input_t      trim_input;   // Which input of the channel above
} opamp_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_Open(opamp_ctrl_t * const p_api_ctrl, opamp_cfg_t const * const p_cfg);
fsp_err_t R_OPAMP_InfoGet(opamp_ctrl_t * const p_api_ctrl, opamp_info_t * const p_info);
fsp_err_t R_OPAMP_Start(opamp_ctrl_t * const p_api_ctrl, uint32_t const channel_mask);
fsp_err_t R_OPAMP_Stop(opamp_ctrl_t * const p_api_ctrl, uint32_t const channel_mask);
fsp_err_t R_OPAMP_StatusGet(opamp_ctrl_t * const p_api_ctrl, opamp_status_t * const p_status);
fsp_err_t R_OPAMP_Trim(opamp_ctrl_t * const            p_api_ctrl,
                       opamp_trim_cmd_t const          cmd,
                       opamp_trim_args_t const * const p_args);
fsp_err_t R_OPAMP_Close(opamp_ctrl_t * const p_api_ctrl);

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const opamp_api_t g_opamp_on_opamp;

/** @endcond */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup OPAMP)
 **********************************************************************************************************************/
