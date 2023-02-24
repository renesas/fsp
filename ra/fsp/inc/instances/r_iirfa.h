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

#ifndef R_IIRFA_H
#define R_IIRFA_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_iirfa_cfg.h"
#include "r_iir_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup IIRFA
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IIRFA instance control block. */
typedef struct st_iirfa_instance_ctrl
{
    uint32_t open;
    uint32_t filter_stages;
    uint8_t  channel;
    uint8_t  stage_base;
    uint8_t  stage_num;
} iirfa_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const iir_api_t g_iir_on_iirfa;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Perform a single inline filter operation.
 *
 * @note This function is intended to be used in performance-critical applications. As such, no parameter checking or
 *       error validation is provided.
 **********************************************************************************************************************/
__STATIC_INLINE float R_IIRFA_SingleFilter (iir_ctrl_t * const p_api_ctrl, float data_in)
{
    iirfa_instance_ctrl_t * p_ctrl = (iirfa_instance_ctrl_t *) p_api_ctrl;

    /* Write input data */
    *(volatile float *) &R_IIRFA->IIRCH[p_ctrl->channel].INP = data_in;

#if IIRFA_CFG_LOOP_USE_POLLING
    volatile uint8_t * const p_reg_status = (volatile uint8_t *) &R_IIRFA->IIRCH[p_ctrl->channel].STS;
    while (!(*p_reg_status & R_IIRFA_IIRCH_STS_ORDYF_Msk))
    {
        /* Wait for IIRFA output data preparation */
    }
#endif

    /* Return output data */
    return *(volatile float *) &R_IIRFA->IIRCH[p_ctrl->channel].OUT;
}

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_IIRFA_Open(iir_ctrl_t * const p_api_ctrl, iir_cfg_t const * const p_cfg);
fsp_err_t R_IIRFA_Configure(iir_ctrl_t * const p_api_ctrl, iir_filter_cfg_t const * const p_filter_cfg);
fsp_err_t R_IIRFA_Filter(iir_ctrl_t * const p_api_ctrl,
                         float const      * p_data_in,
                         float            * p_data_out,
                         uint16_t const     num_samples);
fsp_err_t R_IIRFA_StatusGet(iir_ctrl_t * const p_api_ctrl, iir_status_t * const p_status);
fsp_err_t R_IIRFA_Close(iir_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup IIRFA)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IIRFA_H
