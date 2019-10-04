/***********************************************************************************************************************
 * Copyright [2015-2017] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 *
 * This file is part of Renesas RA Flex Software Package (FSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas FSP license agreement. Unless otherwise agreed in an FSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
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
#define JPEG_DECODE_CODE_VERSION_MAJOR    (1U)
#define JPEG_DECODE_CODE_VERSION_MINOR    (8U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** JPEG Codec module control block.  DO NOT INITIALIZE.  Initialization occurs when jpep_api_t::open is called. */
typedef struct st_jpeg_decode_instance_ctrl
{
    jpeg_decode_status_t status;                  ///< JPEG Codec module status
    fsp_err_t            error_code;              ///< JPEG Codec error code (if any).

    /* Pointer to JPEG codec peripheral specific configuration */
    jpeg_decode_cfg_t const * p_cfg;              ///< JPEG Decode configuration struct

    jpeg_decode_pixel_format_t pixel_format;      ///< Pixel format
    uint32_t                horizontal_stride;    ///< Horizontal Stride settings.
    uint32_t                outbuffer_size;       ///< Output buffer size
    uint16_t                total_lines_decoded;  ///< Track the number of lines decoded so far.
    jpeg_decode_subsample_t horizontal_subsample; ///< Horizontal sub-sample setting.
} jpeg_decode_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_Open(jpeg_decode_ctrl_t * const p_api_ctrl, jpeg_decode_cfg_t const * const p_cfg);
fsp_err_t R_JPEG_Decode_OutputBufferSet(jpeg_decode_ctrl_t * p_api_ctrl,
                                        void               * output_buffer,
                                        uint32_t             output_buffer_size);
fsp_err_t R_JPEG_Decode_LinesDecodedGet(jpeg_decode_ctrl_t * const p_api_ctrl, uint32_t * const p_lines);
fsp_err_t R_JPEG_Decode_HorizontalStrideSet(jpeg_decode_ctrl_t * p_api_ctrl, uint32_t horizontal_stride);
fsp_err_t R_JPEG_Decode_InputBufferSet(jpeg_decode_ctrl_t * constp_api_ctrl,
                                       void               * p_data_buffer,
                                       uint32_t             data_buffer_size);
fsp_err_t R_JPEG_Decode_Close(jpeg_decode_ctrl_t * p_api_ctrl);
fsp_err_t R_JPEG_Decode_ImageSizeGet(jpeg_decode_ctrl_t * p_api_ctrl,
                                     uint16_t           * p_horizontal_size,
                                     uint16_t           * p_vertical_size);
fsp_err_t R_JPEG_Decode_StatusGet(jpeg_decode_ctrl_t * p_api_ctrl, jpeg_decode_status_t * p_status);
fsp_err_t R_JPEG_Decode_ImageSubsampleSet(jpeg_decode_ctrl_t * const p_api_ctrl,
                                          jpeg_decode_subsample_t    horizontal_subsample,
                                          jpeg_decode_subsample_t    vertical_subsample);
fsp_err_t R_JPEG_Decode_PixelFormatGet(jpeg_decode_ctrl_t * p_api_ctrl, jpeg_decode_color_space_t * p_color_space);
fsp_err_t R_JPEG_Decode_VersionGet(fsp_version_t * p_version);

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
extern const jpeg_decode_api_t g_jpeg_decode_on_jpeg_decode;

/** @endcond */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup JPEG)
 **********************************************************************************************************************/
