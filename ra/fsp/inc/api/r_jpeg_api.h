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
 * File Name    : r_jpeg_api.h
 * Description  : JPEG_interface layer API
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup JPEG_API JPEG Codec Interface
 * @brief Interface for JPEG functions.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_JPEG_API_H
#define R_JPEG_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/** Register definitions, common services and error codes. */
#include "bsp_api.h"

/** Configuration for this module */
#include "r_jpeg_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define JPEG_DECODE_API_VERSION_MAJOR    (1U)
#define JPEG_DECODE_API_VERSION_MINOR    (3U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Image color space definitions */
typedef enum e_jpeg_decode_color_space
{
    JPEG_DECODE_COLOR_SPACE_YCBCR444 = 0, ///< Color Space YCbCr 444
    JPEG_DECODE_COLOR_SPACE_YCBCR422 = 1, ///< Color Space YCbCr 422
    JPEG_DECODE_COLOR_SPACE_YCBCR420 = 2, ///< Color Space YCbCr 420
    JPEG_DECODE_COLOR_SPACE_YCBCR411 = 6, ///< Color Space YCbCr 411
} jpeg_decode_color_space_t;

/** Multi-byte Data Format */
typedef enum e_jpeg_data_order
{
    JPEG_DATA_ORDER_NORMAL                  = 0, ///< (1)(2)(3)(4)(5)(6)(7)(8) Normal byte order
    JPEG_DATA_ORDER_BYTE_SWAP               = 1, ///< (2)(1)(4)(3)(6)(5)(8)(7) Byte Swap
    JPEG_DATA_ORDER_WORD_SWAP               = 2, ///< (3)(4)(1)(2)(7)(8)(5)(6) Word Swap
    JPEG_DATA_ORDER_WORD_BYTE_SWAP          = 3, ///< (4)(3)(2)(1)(8)(7)(6)(5) Word-Byte Swap
    JPEG_DATA_ORDER_LONGWORD_SWAP           = 4, ///< (5)(6)(7)(8)(1)(2)(3)(4) Longword Swap
    JPEG_DATA_ORDER_LONGWORD_BYTE_SWAP      = 5, ///< (6)(5)(8)(7)(2)(1)(4)(3) Longword Byte Swap
    JPEG_DATA_ORDER_LONGWORD_WORD_SWAP      = 6, ///< (7)(8)(5)(6)(3)(4)(1)(2) Longword Word Swap
    JPEG_DATA_ORDER_LONGWORD_WORD_BYTE_SWAP = 7, ///< (8)(7)(6)(5)(4)(3)(2)(1) Longword Word Byte Swap
} jpeg_data_order_t;

/** Pixel Data Format */
typedef enum e_jpeg_decode_pixel_format
{
    JPEG_DECODE_PIXEL_FORMAT_ARGB8888 = 1, ///< Pixel Data ARGB8888 format
    JPEG_DECODE_PIXEL_FORMAT_RGB565        ///< Pixel Data RGB565 format
} jpeg_decode_pixel_format_t;

/** JPEG HLD driver internal status information.
 * The driver can simultaneously be in more than any one status at the same time.
 * Parse the status bit-fields using the definitions in this enum to determine driver status */
typedef enum e_jpeg_decode_status
{
    JPEG_DECODE_STATUS_NOT_OPEN          = 0x0,  ///< JPEG codec module is not yet open.
    JPEG_DECODE_STATUS_OPEN              = 0x1,  ///< JPEG Codec module is open, and is not operational.
    JPEG_DECODE_STATUS_RUNNING           = 0x2,  ///< JPEG Codec is running.
    JPEG_DECODE_STATUS_DONE              = 0x4,  ///< JPEG Codec has successfully finished the operation.
    JPEG_DECODE_STATUS_INPUT_PAUSE       = 0x8,  ///< JPEG Codec paused waiting for more input data.
    JPEG_DECODE_STATUS_OUTPUT_PAUSE      = 0x10, ///< JPEG Codec paused after decoded the number of lines specified by user.
    JPEG_DECODE_STATUS_IMAGE_SIZE_READY  = 0x20, ///< JPEG decoding operation obtained image size, and paused.
    JPEG_DECODE_STATUS_ERROR             = 0x40, ///< JPEG Codec module encountered an error.
    JPEG_DECODE_STATUS_HEADER_PROCESSING = 0x80  ///< JPEG Codec module is reading the JPEG header information.
} jpeg_decode_status_t;

/** Data type for horizontal and vertical subsample settings. This setting applies only to the decoding operation. */
typedef enum e_jpeg_decode_subsample
{
    JPEG_DECODE_OUTPUT_NO_SUBSAMPLE          = 0, ///< No subsample. The image is decoded with no reduction in size.
    JPEG_DECODE_OUTPUT_SUBSAMPLE_HALF        = 1, ///< The output image size is reduced by half.
    JPEG_DECODE_OUTPUT_SUBSAMPLE_ONE_QUARTER = 2, ///< The output image size is reduced to one-quarter.
    JPEG_DECODE_OUTPUT_SUBSAMPLE_ONE_EIGHTH  = 3  ///< The output image size is reduced to one-eighth.
} jpeg_decode_subsample_t;

/** Data type for decoding count mode enable. */
typedef enum e_jpeg_decode_count_enable
{
    JPEG_DECODE_COUNT_DISABLE = 0,     ///< Count mode disable.
    JPEG_DECODE_COUNT_ENABLE           ///< Count mode enable.
} jpeg_decode_count_enable_t;

/** Data type for decoding count mode enable. */
typedef enum e_jpeg_decode_resume_mode
{
    JPEG_DECODE_COUNT_MODE_ADDRESS_CONTINUE = 0, ///< The data buffer address will not be initialized when resuming image data lines.
    JPEG_DECODE_COUNT_MODE_ADDRESS_REINITIALIZE  ///< The data buffer address will be initialized when resuming image data lines.
} jpeg_decode_resume_mode_t;

/** Callback status structure */
typedef struct st_jpeg_decode_callback_args
{
    jpeg_decode_status_t status;       ///< JPEG status
    void const         * p_context;    ///< Pointer to user-provided context
} jpeg_decode_callback_args_t;

/** User configuration structure, used in open function. */
typedef struct st_jpeg_decode_cfg
{
    jpeg_decode_color_space_t  color_space;                    ///< Color space
    jpeg_data_order_t          input_data_order;               ///< Input data stream byte order
    jpeg_data_order_t          output_data_order;              ///< Output data stream byte order
    jpeg_decode_pixel_format_t pixel_format;                   ///< Pixel format
    uint8_t   alpha_value;                                     ///< Alpha value to be applied to decoded pixel data. Only valid for ARGB888 format.
    IRQn_Type jedi_irq;                                        ///< Data transfer interrupt IRQ number
    IRQn_Type jdti_irq;                                        ///< Decompression interrupt IRQ number
    uint8_t   jdti_ipl;                                        ///< Data transfer interrupt priority
    uint8_t   jedi_ipl;                                        ///< Decompression interrupt priority
    void (* p_callback)(jpeg_decode_callback_args_t * p_args); ///< User-supplied callback functions.
    void const * p_context;                                    ///< Placeholder for user data.  Passed to user callback in ::jpeg_decode_callback_args_t.
} jpeg_decode_cfg_t;

/** JPEG decode control block.  Allocate an instance specific control block to pass into the JPEG decode API calls.
 * @par Implemented as
 * - jpeg_decode_instance_ctrl_t
 */
typedef void jpeg_decode_ctrl_t;

/** JPEG functions implemented at the HAL layer will follow this API. */
typedef struct st_jpeg_decode_api
{
    /** Initial configuration
     * @par Implemented as
     * - R_JPEG_Decode_Open()
     *
     * @pre none
     *
     * @param[in,out] p_ctrl    Pointer to control block.  Must be declared by user. Elements set here.
     * @param[in]     p_cfg     Pointer to configuration structure. All elements of this structure  must be set by user.
     */
    fsp_err_t (* open)(jpeg_decode_ctrl_t * const p_ctrl, jpeg_decode_cfg_t const * const p_cfg);

    /** Assign output buffer to JPEG codec for storing output data.
     * @par Implemented as
     * - R_JPEG_Decode_OutputBufferSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     * @note The buffer starting address must be 8-byte aligned.
     * For the decoding process, the HLD driver automatically computes the number of lines of the image to decoded so the
     * output data fits into the given space.  If the supplied output buffer is not able to hold the entire frame,
     * the application should call the Output Full Callback function so it can be notified when additional buffer space is
     * needed.
     * @param[in]     p_ctrl      Control block set in jpeg_decode_api_t::open call.
     * @param[in]     p_buffer    Pointer to the output buffer space
     * @param[in]     buffer_size Size of the output buffer
     */
    fsp_err_t (* outputBufferSet)(jpeg_decode_ctrl_t * const p_ctrl, void * p_buffer, uint32_t buffer_size);

    /** Configure the horizontal stride value.
     * @par Implemented as
     * - R_JPEG_Decode_HorizontalStrideSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl      Control block set in jpeg_decode_api_t::open call.
     * @param[in]     horizontal_stride  Horizontal stride value to be used for the decoded image data.
     * @param[in]     buffer_size Size of the output buffer
     */
    fsp_err_t (* horizontalStrideSet)(jpeg_decode_ctrl_t * const p_ctrl, uint32_t horizontal_stride);

    /** Configure the horizontal and vertical subsample settings.
     * @par Implemented as
     * - R_JPEG_Decode_ImageSubsampleSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl      Control block set in jpeg_decode_api_t::open call.
     * @param[in]     horizontal_subsample    Horizontal subsample value
     * @param[in]     vertical_subsample      Vertical subsample value
     */
    fsp_err_t (* imageSubsampleSet)(jpeg_decode_ctrl_t * const p_ctrl, jpeg_decode_subsample_t horizontal_subsample,
                                    jpeg_decode_subsample_t vertical_subsample);

    /** Assign input data buffer to JPEG codec.
     * @par Implemented as
     * - R_JPEG_Decode_InputBufferSet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @note The buffer starting address must be 8-byte aligned.
     * @param[in]     p_ctrl      Control block set in jpeg_decode_api_t::open call.
     * @param[in]     p_buffer    Pointer to the input buffer space
     * @param[in]     buffer_size Size of the input buffer
     */
    fsp_err_t (* inputBufferSet)(jpeg_decode_ctrl_t * const p_ctrl, void * p_buffer, uint32_t buffer_size);

    /** Return the number of lines decoded into the output buffer.
     * @par Implemented as
     * - R_JPEG_Decode_LinesDecodedGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl      Control block set in jpeg_decode_api_t::open call.
     * @param[out]    p_lines     Number of lines decoded
     */
    fsp_err_t (* linesDecodedGet)(jpeg_decode_ctrl_t * const p_ctrl, uint32_t * const p_lines);

    /** Retrieve image size during decoding operation.
     * @par Implemented as
     * - R_JPEG_Decode_ImageSizeGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @note If the encoding or the decoding operation is finished without errors, the HLD driver
     * automatically closes the device. In this case, application does not need to explicitly close the
     * JPEG device.
     * @param[in]     p_ctrl               Control block set in jpeg_decode_api_t::open call.
     * @param[out]    p_horizontal_size    Image horizontal size, in number of pixels.
     * @param[out]    p_vertical_size      Image vertical size, in number of pixels.
     */
    fsp_err_t (* imageSizeGet)(jpeg_decode_ctrl_t * const p_ctrl, uint16_t * p_horizontal_size,
                               uint16_t * p_vertical_size);

    /** Retrieve current status of the JPEG codec module.
     * @par Implemented as
     * - R_JPEG_Decode_StatusGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl               Control block set in jpeg_decode_api_t::open call.
     * @param[out]    p_status             JPEG module status
     */
    fsp_err_t (* statusGet)(jpeg_decode_ctrl_t * const p_ctrl, jpeg_decode_status_t * const p_status);

    /** Cancel an outstanding operation.
     * @par Implemented as
     * - R_JPEG_Decode_Close()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @note If the encoding or the decoding operation is finished without errors, the HLD driver
     * automatically closes the device. In this case, application does not need to explicitly close the
     * JPEG device.
     * @param[in]     p_ctrl      Control block set in jpeg_decode_api_t::open call.
     */
    fsp_err_t (* close)(jpeg_decode_ctrl_t * const p_ctrl);

    /** Get version and store it in provided pointer p_version.
     * @par Implemented as
     * - R_JPEG_Decode_VersionGet()
     *
     * @param[out]  p_version  Code and API version used.
     */
    fsp_err_t (* versionGet)(fsp_version_t * p_version);

    /** Get the input pixel format.
     * @par Implemented as
     * - R_JPEG_Decode_PixelFormatGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl               Control block set in jpeg_decode_api_t::open call.
     * @param[out]    p_color_space        JPEG input format.
     */
    fsp_err_t (* pixelFormatGet)(jpeg_decode_ctrl_t * const p_ctrl, jpeg_decode_color_space_t * const p_color_space);
} jpeg_decode_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_jpeg_decode_instance
{
    jpeg_decode_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance
    jpeg_decode_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance
    jpeg_decode_api_t const * p_api;   ///< Pointer to the API structure for this instance
} jpeg_decode_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup JPEG_DECODE_API)
 **********************************************************************************************************************/
