/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_ADPCM_DECODER_API_H_
#define RM_ADPCM_DECODER_API_H_

/*******************************************************************************************************************//**
 * @ingroup RENESAS_AUDIO_INTERFACES
 * @defgroup RM_ADPCM_DECODER_API ADPCM Decoder Interface
 * @brief Interface for ADPCM decoder.
 *
 * @section RM_ADPCM_DECODER_API_SUMMARY Summary
 * The ADPCM decoder interface provides functionality to decode the 4bit ADPCM data to 16bit PCM output.
 *
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
    void const * p_extend;             // Placeholder for implementation specific configuration
} adpcm_decoder_cfg_t;

/** Audio Decoder control block.  Allocate an instance specific control block to pass into the Audio Decoder API calls.
 */
typedef void adpcm_decoder_ctrl_t;

/** Audio Decoder interface API. */
typedef struct st_adpcm_decoder_api
{
    /** Initialize Audio Decoder device.
     *
     * @note To reconfigure after calling this function, call @ref adpcm_decoder_api_t::close first.
     * @param[in]  p_ctrl  Pointer to control handle structure
     * @param[in]  p_cfg   Pointer to configuration structure
     */
    fsp_err_t (* open)(adpcm_decoder_ctrl_t * const p_ctrl, adpcm_decoder_cfg_t const * const p_cfg);

    /** Decodes the compressed data and stores it in output buffer.
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
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     *
     */
    fsp_err_t (* reset)(adpcm_decoder_ctrl_t * const p_ctrl);

    /** Close the specified Audio decoder modules.
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
