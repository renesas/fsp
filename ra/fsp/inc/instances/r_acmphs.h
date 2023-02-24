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

#ifndef R_ACMPHS_H
#define R_ACMPHS_H

/*******************************************************************************************************************//**
 * @addtogroup ACMPHS
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
    ACMPHS_INPUT_NONE   = 0,
    ACMPHS_INPUT_IVCMP0 = 1,
    ACMPHS_INPUT_IVCMP1 = 2,
    ACMPHS_INPUT_IVCMP2 = 4,
    ACMPHS_INPUT_IVCMP3 = 8,
    ACMPHS_INPUT_IVCMP4 = 16,
    ACMPHS_INPUT_IVCMP5 = 32,
} acmphs_input_t;

typedef enum
{
    ACMPHS_REFERENCE_NONE   = 0,
    ACMPHS_REFERENCE_IVREF0 = 1,
    ACMPHS_REFERENCE_IVREF1 = 2,
    ACMPHS_REFERENCE_IVREF2 = 4,
    ACMPHS_REFERENCE_IVREF3 = 8,
    ACMPHS_REFERENCE_IVREF4 = 16,
    ACMPHS_REFERENCE_IVREF5 = 32,
} acmphs_reference_t;

/* ACMPHS extended configuration */
typedef struct
{
    acmphs_input_t     input_voltage;
    acmphs_reference_t reference_voltage;
    uint32_t           maximum_status_retries; // Maximum number of status retries alowed
} r_acmphs_extended_cfg_t;

/* Channel instance control block. DO NOT INITIALIZE.  Initialization occurs in @ref comparator_api_t::open. */
typedef struct st_acmphs_instance_ctrl
{
    uint32_t                 open;                   // Used to determine if channel control block is in use
    const comparator_cfg_t * p_cfg;                  // Pointer to initial configurations
    R_ACMPHS0_Type         * p_reg;                  // Pointer to register base address
    uint32_t                 maximum_status_retries; // Maximum number of status retries alowed
} acmphs_instance_ctrl_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/* @cond INC_HEADER_DEFS_SEC */
/* Filled in Interface API structure for this Instance. */
extern const comparator_api_t g_comparator_on_acmphs;

/* @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_Open(comparator_ctrl_t * p_ctrl, comparator_cfg_t const * const p_cfg);
fsp_err_t R_ACMPHS_OutputEnable(comparator_ctrl_t * const p_ctrl);
fsp_err_t R_ACMPHS_InfoGet(comparator_ctrl_t * const p_ctrl, comparator_info_t * const p_info);
fsp_err_t R_ACMPHS_StatusGet(comparator_ctrl_t * const p_ctrl, comparator_status_t * const p_status);
fsp_err_t R_ACMPHS_Close(comparator_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup ACMPHS)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ACMPHS_H
