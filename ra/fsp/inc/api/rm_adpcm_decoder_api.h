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

#ifndef RM_ADPCM_DECODER_API_H_
#define RM_ADPCM_DECODER_API_H_

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup RM_ADPCM_DECODER_API ADPCM Decoder Interface
 * @brief Interface for ADPCM decoder.
 *
 * @section RM_ADPCM_DECODER_API_SUMMARY Summary
 * The ADPCM decoder interface provides functionality to decode the 4bit ADPCM data to 16bit PCM output.
 *
 * Implemented by:
 * @ref RM_ADPCM_DECODER
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Audio Decoder general configuration  */
typedef struct st_adpcm_decoder_cfg
{
    void const * p_extend;              // Placeholder for implementation specific configuration
} adpcm_decoder_cfg_t;

/** Audio Decoder control block.  Allocate an instance specific control block to pass into the Audio Decoder API calls.
 * @par Implemented as
 * - @ref adpcm_decoder_instance_ctrl_t
 */
typedef void adpcm_decoder_ctrl_t;

/** Audio Decoder interface API. */
typedef struct st_adpcm_decoder_api
{
    /** Initialize Audio Decoder device.
     * @par Implemented as
     * - @ref RM_ADPCM_DECODER_Open()
     *
     * @note To reconfigure after calling this function, call @ref adpcm_decoder_api_t::close first.
     * @param[in]  p_ctrl  Pointer to control handle structure
     * @param[in]  p_cfg   Pointer to configuration structure
     */
    fsp_err_t (* open)(adpcm_decoder_ctrl_t * const p_ctrl, adpcm_decoder_cfg_t const * const p_cfg);

    /** Decodes the compressed data and stores it in output buffer.
     * @par Implemented as
     * - @ref RM_ADPCM_DECODER_Decode()
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     * @param[in]  p_src    Pointer to a source data buffer from which data will be picked up for decode operation.
     *                      The argument must not be NULL.
     * @param[out] p_dest   Pointer to the location to store the decoded data.
     * @param[in] p_dest    Number of bytes to be decoded.
     *
     */
    fsp_err_t (* decode)(adpcm_decoder_ctrl_t * const p_ctrl, void const * p_src, void * p_dest, 
            uint32_t src_len_bytes);

    /** Resets the ADPCM driver.
     * @par Implemented as
     * - @ref RM_ADPCM_DECODER_Reset()
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     *
     */
    fsp_err_t (* reset)(adpcm_decoder_ctrl_t * const p_ctrl);

    /** Close the specified Audio decoder modules.
     * @par Implemented as
     * - @ref RM_ADPCM_DECODER_Close()
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* close)(adpcm_decoder_ctrl_t * const p_ctrl);

} adpcm_decoder_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_adpcm_decoder_instance
{
    adpcm_decoder_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    adpcm_decoder_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    adpcm_decoder_api_t const * p_api;  ///< Pointer to the API structure for this instance
} adpcm_decoder_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_ADPCM_DECODER_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
