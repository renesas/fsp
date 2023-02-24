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

#ifndef R_GPT_THREE_PHASE_H
#define R_GPT_THREE_PHASE_H

/*******************************************************************************************************************//**
 * @addtogroup GPT_THREE_PHASE
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_three_phase_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref three_phase_api_t::open is called. */
typedef struct st_gpt_three_phase_instance_ctrl
{
    uint32_t                  open;         // Whether or not channel is open
    R_GPT0_Type             * p_reg[3];     // Pointer to GPT channel registers
    uint32_t                  channel_mask; // Bitmask of GPT channels used
    three_phase_buffer_mode_t buffer_mode;  // Single- or double-buffer mode
    three_phase_cfg_t const * p_cfg;        // Pointer to configuration struct
} gpt_three_phase_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const three_phase_api_t g_gpt_three_phase_on_gpt_three_phase;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_Open(three_phase_ctrl_t * const p_ctrl, three_phase_cfg_t const * const p_cfg);
fsp_err_t R_GPT_THREE_PHASE_Stop(three_phase_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_THREE_PHASE_Start(three_phase_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_THREE_PHASE_Reset(three_phase_ctrl_t * const p_ctrl);
fsp_err_t R_GPT_THREE_PHASE_DutyCycleSet(three_phase_ctrl_t * const       p_ctrl,
                                         three_phase_duty_cycle_t * const p_duty_cycle);
fsp_err_t R_GPT_THREE_PHASE_CallbackSet(three_phase_ctrl_t * const    p_ctrl,
                                        void (                      * p_callback)(timer_callback_args_t *),
                                        void const * const            p_context,
                                        timer_callback_args_t * const p_callback_memory);
fsp_err_t R_GPT_THREE_PHASE_Close(three_phase_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup GPT_THREE_PHASE)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
