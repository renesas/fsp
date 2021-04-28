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

/**********************************************************************************************************************
 * File Name    : r_jpeg.h
 * Description  : JPEG Module instance header file.
 **********************************************************************************************************************/

/*****************************************************************************************************************//**
 * @addtogroup JPEG
 * @{
 **********************************************************************************************************************/

#ifndef R_JPEG_H
#define R_JPEG_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_jpeg_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** JPEG Codec module control block.  DO NOT INITIALIZE.  Initialization occurs when jpep_api_t::open is called. */
typedef struct st_jpeg_instance_ctrl
{
    uint32_t      open;                           ///< JPEG Codec driver status
    jpeg_status_t status;                         ///< JPEG Codec operational status
    fsp_err_t     error_code;                     ///< JPEG Codec error code (if any).
    jpeg_mode_t   mode;                           ///< Current mode (decode or encode).

    uint32_t horizontal_stride_bytes;             ///< Horizontal Stride settings.
    uint32_t output_buffer_size;                  ///< Output buffer size

    /* Pointer to JPEG codec peripheral specific configuration */
    jpeg_cfg_t const * p_cfg;                     ///< JPEG Decode configuration struct
    void const       * p_extend;                  ///< JPEG Codec hardware dependent configuration */

#if JPEG_CFG_DECODE_ENABLE
    jpeg_decode_pixel_format_t pixel_format;      ///< Pixel format
    uint16_t                total_lines_decoded;  ///< Track the number of lines decoded so far.
    jpeg_decode_subsample_t horizontal_subsample; ///< Horizontal sub-sample setting.
#endif

#if JPEG_CFG_ENCODE_ENABLE
    uint16_t lines_to_encode;                     ///< Number of lines to encode
    uint16_t vertical_resolution;                 ///< vertical size
    uint16_t total_lines_encoded;                 ///< Number of lines encoded
#endif
} jpeg_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Open(jpeg_ctrl_t * const p_api_ctrl, jpeg_cfg_t const * const p_cfg);
fsp_err_t R_JPEG_OutputBufferSet(jpeg_ctrl_t * p_api_ctrl, void * output_buffer, uint32_t output_buffer_size);
fsp_err_t R_JPEG_InputBufferSet(jpeg_ctrl_t * constp_api_ctrl, void * p_data_buffer, uint32_t data_buffer_size);
fsp_err_t R_JPEG_StatusGet(jpeg_ctrl_t * p_api_ctrl, jpeg_status_t * p_status);
fsp_err_t R_JPEG_Close(jpeg_ctrl_t * p_api_ctrl);

#if JPEG_CFG_ENCODE_ENABLE
fsp_err_t R_JPEG_EncodeImageSizeSet(jpeg_ctrl_t * const p_api_ctrl, jpeg_encode_image_size_t * p_image_size);

#endif

#if JPEG_CFG_DECODE_ENABLE
fsp_err_t R_JPEG_DecodeLinesDecodedGet(jpeg_ctrl_t * const p_api_ctrl, uint32_t * const p_lines);
fsp_err_t R_JPEG_DecodeHorizontalStrideSet(jpeg_ctrl_t * p_api_ctrl, uint32_t horizontal_stride);
fsp_err_t R_JPEG_DecodeImageSizeGet(jpeg_ctrl_t * p_api_ctrl, uint16_t * p_horizontal_size, uint16_t * p_vertical_size);
fsp_err_t R_JPEG_DecodeImageSubsampleSet(jpeg_ctrl_t * const     p_api_ctrl,
                                         jpeg_decode_subsample_t horizontal_subsample,
                                         jpeg_decode_subsample_t vertical_subsample);
fsp_err_t R_JPEG_DecodePixelFormatGet(jpeg_ctrl_t * p_api_ctrl, jpeg_color_space_t * p_color_space);

#endif

#if JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE
fsp_err_t R_JPEG_ModeSet(jpeg_ctrl_t * const p_api_ctrl, jpeg_mode_t mode);

#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
extern const jpeg_api_t g_jpeg_on_jpeg;

/** @endcond */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup JPEG)
 **********************************************************************************************************************/
