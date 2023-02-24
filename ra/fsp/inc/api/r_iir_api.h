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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup IIR_API IIR Interface
 * @brief Interface for IIR filter functionality.
 *
 * @section IIR_API_SUMMARY Summary
 *    The IIR interface allows access to the IIRFA peripheral for hardware acceleration of direct form 2
 *    transposed biquad IIR filters.
 *
 * Implemented by:
 * - @ref IIRFA
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_IIR_API_H
#define R_IIR_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common error codes and definitions. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Filter stage coefficient data */
typedef struct st_iir_filter_coeffs
{
    float b0;                          ///< Coefficient B0
    float b1;                          ///< Coefficient B1
    float b2;                          ///< Coefficient B2
    float a1;                          ///< Coefficient A0
    float a2;                          ///< Coefficient A1
} iir_filter_coeffs_t;

/** Filter stage state data */
typedef struct st_iir_filter_state
{
    float d0;                          ///< State variable D0
    float d1;                          ///< State variable D1
} iir_filter_state_t;

/** Filter configuration */
typedef struct st_iir_filter_cfg
{
    iir_filter_coeffs_t * p_filter_coeffs; ///< Filter coefficients
    iir_filter_state_t  * p_filter_state;  ///< Filter state data
    uint8_t               stage_base;      ///< Hardware stage to start from
    uint8_t               stage_num;       ///< Number of filter stages to use
} iir_filter_cfg_t;

/** Filter state register status */
typedef struct st_iir_status
{
    iir_filter_state_t * p_filter_state;
} iir_status_t;

/** IIRFA API configuration parameter */
typedef struct st_iir_cfg
{
    void const * p_extend;
    uint8_t      channel;              ///< IIRFA channel to use
} iir_cfg_t;

/** IIR control block.  Allocate an instance specific control block to pass into the DAC API calls.
 * @par Implemented as
 * - iirfa_instance_ctrl_t
 */
typedef void iir_ctrl_t;

/** IIR driver structure.  IIR functions implemented at the HAL layer follow this API. */
typedef struct st_iir_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_IIRFA_Open()
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(iir_ctrl_t * const p_ctrl, iir_cfg_t const * const p_cfg);

    /** Close the IIRFA channel.
     * @par Implemented as
     * - @ref R_IIRFA_Close()
     *
     * @param[in]   p_ctrl     Control block set in @ref iir_api_t::open.
     */
    fsp_err_t (* close)(iir_ctrl_t * const p_ctrl);

    /** Configure filter coefficients and state variables.
     * @par Implemented as
     * - @ref R_IIRFA_Configure()
     *
     * @param[in]   p_ctrl         Control block set in @ref iir_api_t::open.
     * @param[in]   p_filter_cfg   Pointer to filter configuration to write.
     */
    fsp_err_t (* configure)(iir_ctrl_t * const p_ctrl, iir_filter_cfg_t const * const p_filter_cfg);

    /** Filter the specified data.
     * @par Implemented as
     * - @ref R_IIRFA_Filter()
     *
     * @param[in]   p_ctrl        Control block set in @ref iir_api_t::open.
     * @param[in]   p_data_in     Pointer to float input data.
     * @param[in]   p_data_out    Pointer to float output buffer.
     * @param[in]   num_samples   Number of samples to process.
     */
    fsp_err_t (* filter)(iir_ctrl_t * const p_ctrl, float const * p_data_in, float * p_data_out,
                         uint16_t const num_samples);

    /** Retrieve current status (including state registers).
     * @par Implemented as
     * - @ref R_IIRFA_StatusGet()
     *
     * @param[in]   p_ctrl     Control block set in @ref iir_api_t::open.
     * @param[in]   p_status   Pointer to status struct.
     */
    fsp_err_t (* statusGet)(iir_ctrl_t * const p_ctrl, iir_status_t * const p_status);
} iir_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_iirfa_instance
{
    iir_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    iir_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    iir_api_t const * p_api;           ///< Pointer to the API structure for this instance
} iirfa_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup DAC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
