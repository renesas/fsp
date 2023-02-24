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

#ifndef R_POEG_H
#define R_POEG_H

/*******************************************************************************************************************//**
 * @addtogroup POEG
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_poeg_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref poeg_api_t::open is called. */
typedef struct st_poeg_instance_ctrl
{
    uint32_t           open;                     // Whether or not channel is open
    const poeg_cfg_t * p_cfg;                    // Pointer to initial configurations
    R_GPT_POEG0_Type * p_reg;                    // Base register for this channel

    void (* p_callback)(poeg_callback_args_t *); // Pointer to callback
    poeg_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void const           * p_context;            // Pointer to context to be passed into callback function
} poeg_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const poeg_api_t g_poeg_on_poeg;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_POEG_Open(poeg_ctrl_t * const p_ctrl, poeg_cfg_t const * const p_cfg);
fsp_err_t R_POEG_StatusGet(poeg_ctrl_t * const p_ctrl, poeg_status_t * const p_status);
fsp_err_t R_POEG_CallbackSet(poeg_ctrl_t * const          p_ctrl,
                             void (                     * p_callback)(poeg_callback_args_t *),
                             void const * const           p_context,
                             poeg_callback_args_t * const p_callback_memory);
fsp_err_t R_POEG_OutputDisable(poeg_ctrl_t * const p_ctrl);
fsp_err_t R_POEG_Reset(poeg_ctrl_t * const p_ctrl);
fsp_err_t R_POEG_Close(poeg_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup POEG)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
