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

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/** Configuration for this module */
#include "r_jpeg_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Image color space definitions */
typedef enum e_jpeg_color_space
{
    JPEG_COLOR_SPACE_YCBCR444 = 0,     ///< Color Space YCbCr 444
    JPEG_COLOR_SPACE_YCBCR422 = 1,     ///< Color Space YCbCr 422
    JPEG_COLOR_SPACE_YCBCR420 = 2,     ///< Color Space YCbCr 420
    JPEG_COLOR_SPACE_YCBCR411 = 6,     ///< Color Space YCbCr 411
} jpeg_color_space_t;

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

/** JPEG HLD driver internal status information.
 * The driver can simultaneously be in more than any one status at the same time.
 * Parse the status bit-fields using the definitions in this enum to determine driver status */
typedef enum e_jpeg_status
{
    JPEG_STATUS_NONE               = 0x0,  ///< JPEG codec module is not initialized.
    JPEG_STATUS_IDLE               = 0x1,  ///< JPEG Codec module is open but not running.
    JPEG_STATUS_RUNNING            = 0x2,  ///< JPEG Codec is running.
    JPEG_STATUS_HEADER_PROCESSING  = 0x4,  ///< JPEG Codec module is reading the JPEG header information.
    JPEG_STATUS_INPUT_PAUSE        = 0x8,  ///< JPEG Codec paused waiting for more input data.
    JPEG_STATUS_OUTPUT_PAUSE       = 0x10, ///< JPEG Codec paused after it decoded the number of lines specified by user.
    JPEG_STATUS_IMAGE_SIZE_READY   = 0x20, ///< JPEG decoding operation obtained image size, and paused.
    JPEG_STATUS_ERROR              = 0x40, ///< JPEG Codec module encountered an error.
    JPEG_STATUS_OPERATION_COMPLETE = 0x80, ///< JPEG Codec has completed the operation.
} jpeg_status_t;

typedef enum e_jpeg_mode
{
    JPEG_MODE_DECODE,
    JPEG_MODE_ENCODE
} jpeg_mode_t;

/** Pixel Data Format */
typedef enum e_jpeg_decode_pixel_format
{
    JPEG_DECODE_PIXEL_FORMAT_ARGB8888 = 1, ///< Pixel Data ARGB8888 format
    JPEG_DECODE_PIXEL_FORMAT_RGB565        ///< Pixel Data RGB565 format
} jpeg_decode_pixel_format_t;

/** Data type for horizontal and vertical subsample settings. This setting applies only to the decoding operation. */
typedef enum e_jpeg_decode_subsample
{
    JPEG_DECODE_OUTPUT_NO_SUBSAMPLE          = 0, ///< No subsample. The image is decoded with no reduction in size.
    JPEG_DECODE_OUTPUT_SUBSAMPLE_HALF        = 1, ///< The output image size is reduced by half.
    JPEG_DECODE_OUTPUT_SUBSAMPLE_ONE_QUARTER = 2, ///< The output image size is reduced to one-quarter.
    JPEG_DECODE_OUTPUT_SUBSAMPLE_ONE_EIGHTH  = 3  ///< The output image size is reduced to one-eighth.
} jpeg_decode_subsample_t;

/** Image parameter structure */
typedef struct st_jpeg_encode_image_size
{
    uint16_t horizontal_stride_pixels; ///< Horizontal stride
    uint16_t horizontal_resolution;    ///< Horizontal Resolution in pixels
    uint16_t vertical_resolution;      ///< Vertical Resolution in pixels
} jpeg_encode_image_size_t;

/** Callback status structure */
typedef struct st_jpeg_callback_args
{
    jpeg_status_t status;              ///< JPEG status
    uint32_t      image_size;          ///< JPEG image size
    void const  * p_context;           ///< Pointer to user-provided context
} jpeg_callback_args_t;

/** User configuration structure, used in open function. */
typedef struct st_jpeg_cfg
{
    /* General configuration */
    IRQn_Type jedi_irq;                ///< Data transfer interrupt IRQ number
    IRQn_Type jdti_irq;                ///< Decompression interrupt IRQ number
    uint8_t   jdti_ipl;                ///< Data transfer interrupt priority
    uint8_t   jedi_ipl;                ///< Decompression interrupt priority

#if JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE
    jpeg_mode_t default_mode;          ///< Mode to use at startup
#endif

#if JPEG_CFG_DECODE_ENABLE

    /* Decode configuration */
    jpeg_data_order_t          decode_input_data_order;        ///< Input data stream byte order
    jpeg_data_order_t          decode_output_data_order;       ///< Output data stream byte order
    jpeg_decode_pixel_format_t pixel_format;                   ///< Pixel format
    uint8_t alpha_value;                                       ///< Alpha value to be applied to decoded pixel data. Only valid for ARGB8888 format.
    void (* p_decode_callback)(jpeg_callback_args_t * p_args); ///< User-supplied callback functions.
    void const * p_decode_context;                             ///< Placeholder for user data.  Passed to user callback in ::jpeg_callback_args_t.
#endif

#if JPEG_CFG_ENCODE_ENABLE

    /* Encode configuration */
    jpeg_data_order_t encode_input_data_order;                 ///< Input data stream byte order
    jpeg_data_order_t encode_output_data_order;                ///< Output data stream byte order
    uint16_t          dri_marker;                              ///< DRI Marker setting (0 = No DRI or RST marker)
    uint16_t          horizontal_resolution;                   ///< Horizontal resolution of input image
    uint16_t          vertical_resolution;                     ///< Vertical resolution of input image
    uint16_t          horizontal_stride_pixels;                ///< Horizontal stride of input image
    uint8_t const   * p_quant_luma_table;                      ///< Luma quantization table
    uint8_t const   * p_quant_chroma_table;                    ///< Chroma quantization table
    uint8_t const   * p_huffman_luma_ac_table;                 ///< Huffman AC table for luma
    uint8_t const   * p_huffman_luma_dc_table;                 ///< Huffman DC table for luma
    uint8_t const   * p_huffman_chroma_ac_table;               ///< Huffman AC table for chroma
    uint8_t const   * p_huffman_chroma_dc_table;               ///< Huffman DC table for chroma
    void (* p_encode_callback)(jpeg_callback_args_t * p_args); ///< User-supplied callback functions.
    void const * p_encode_context;                             ///< Placeholder for user data.  Passed to user callback in ::jpeg_callback_args_t.
#endif
} jpeg_cfg_t;

/** JPEG decode control block.  Allocate an instance specific control block to pass into the JPEG decode API calls.
 * @par Implemented as
 * - jpeg_instance_ctrl_t
 */
typedef void jpeg_ctrl_t;

/** JPEG functions implemented at the HAL layer will follow this API. */
typedef struct st_jpeg_api
{
    /** Initial configuration
     * @par Implemented as
     * - @ref R_JPEG_Open()
     *
     * @pre none
     *
     * @param[in,out] p_ctrl    Pointer to control block.  Must be declared by user. Elements set here.
     * @param[in]     p_cfg     Pointer to configuration structure. All elements of this structure  must be set by user.
     */
    fsp_err_t (* open)(jpeg_ctrl_t * const p_ctrl, jpeg_cfg_t const * const p_cfg);

    /** Assign input data buffer to JPEG codec.
     * @par Implemented as
     * - @ref R_JPEG_InputBufferSet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @note The buffer starting address must be 8-byte aligned.
     * @param[in]     p_ctrl      Control block set in jpeg_api_t::open call.
     * @param[in]     p_buffer    Pointer to the input buffer space
     * @param[in]     buffer_size Size of the input buffer
     */
    fsp_err_t (* inputBufferSet)(jpeg_ctrl_t * const p_ctrl, void * p_buffer, uint32_t buffer_size);

    /** Assign output buffer to JPEG codec for storing output data.
     * @par Implemented as
     * - @ref R_JPEG_OutputBufferSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     * @note The buffer starting address must be 8-byte aligned.
     * For the decoding process, the HLD driver automatically computes the number of lines of the image to decoded so the
     * output data fits into the given space.  If the supplied output buffer is not able to hold the entire frame,
     * the application should call the Output Full Callback function so it can be notified when additional buffer space is
     * needed.
     * @param[in]     p_ctrl      Control block set in jpeg_api_t::open call.
     * @param[in]     p_buffer    Pointer to the output buffer space
     * @param[in]     buffer_size Size of the output buffer
     */
    fsp_err_t (* outputBufferSet)(jpeg_ctrl_t * const p_ctrl, void * p_buffer, uint32_t buffer_size);

    /** Retrieve current status of the JPEG codec module.
     * @par Implemented as
     * - @ref R_JPEG_StatusGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl               Control block set in jpeg_api_t::open call.
     * @param[out]    p_status             JPEG module status
     */
    fsp_err_t (* statusGet)(jpeg_ctrl_t * const p_ctrl, jpeg_status_t * const p_status);

    /** Cancel an outstanding operation.
     * @par Implemented as
     * - @ref R_JPEG_Close()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @note If the encoding or the decoding operation is finished without errors, the HLD driver
     * automatically closes the device. In this case, application does not need to explicitly close the
     * JPEG device.
     * @param[in]     p_ctrl      Control block set in jpeg_api_t::open call.
     */
    fsp_err_t (* close)(jpeg_ctrl_t * const p_ctrl);

#if JPEG_CFG_DECODE_ENABLE

    /** Configure the horizontal stride value.
     * @par Implemented as
     * - @ref R_JPEG_DecodeHorizontalStrideSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl      Control block set in jpeg_api_t::open call.
     * @param[in]     horizontal_stride  Horizontal stride value to be used for the decoded image data.
     * @param[in]     buffer_size Size of the output buffer
     */
    fsp_err_t (* horizontalStrideSet)(jpeg_ctrl_t * const p_ctrl, uint32_t horizontal_stride);

    /** Get the input pixel format.
     * @par Implemented as
     * - @ref R_JPEG_DecodePixelFormatGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl               Control block set in jpeg_api_t::open call.
     * @param[out]    p_color_space        JPEG input format.
     */
    fsp_err_t (* pixelFormatGet)(jpeg_ctrl_t * const p_ctrl, jpeg_color_space_t * const p_color_space);

    /** Configure the horizontal and vertical subsample settings.
     * @par Implemented as
     * - @ref R_JPEG_DecodeImageSubsampleSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl      Control block set in jpeg_api_t::open call.
     * @param[in]     horizontal_subsample    Horizontal subsample value
     * @param[in]     vertical_subsample      Vertical subsample value
     */
    fsp_err_t (* imageSubsampleSet)(jpeg_ctrl_t * const p_ctrl, jpeg_decode_subsample_t horizontal_subsample,
                                    jpeg_decode_subsample_t vertical_subsample);

    /** Return the number of lines decoded into the output buffer.
     * @par Implemented as
     * - @ref R_JPEG_DecodeLinesDecodedGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @param[in]     p_ctrl      Control block set in jpeg_api_t::open call.
     * @param[out]    p_lines     Number of lines decoded
     */
    fsp_err_t (* linesDecodedGet)(jpeg_ctrl_t * const p_ctrl, uint32_t * const p_lines);

    /** Retrieve image size during decoding operation.
     * @par Implemented as
     * - @ref R_JPEG_DecodeImageSizeGet()
     *
     * @pre the JPEG codec module must have been opened properly.
     * @note If the encoding or the decoding operation is finished without errors, the HLD driver
     * automatically closes the device. In this case, application does not need to explicitly close the
     * JPEG device.
     * @param[in]     p_ctrl               Control block set in jpeg_api_t::open call.
     * @param[out]    p_horizontal_size    Image horizontal size, in number of pixels.
     * @param[out]    p_vertical_size      Image vertical size, in number of pixels.
     */
    fsp_err_t (* imageSizeGet)(jpeg_ctrl_t * const p_ctrl, uint16_t * p_horizontal_size, uint16_t * p_vertical_size);
#endif

#if JPEG_CFG_ENCODE_ENABLE

    /** Set image parameters to JPEG Codec
     * @par Implemented as
     * - @ref R_JPEG_EncodeImageSizeSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     *
     * @param[in,out] p_ctrl           Pointer to control block.  Must be declared by user. Elements set here.
     * @param[in]     p_image_size     Pointer to the RAW image parameters
     */
    fsp_err_t (* imageSizeSet)(jpeg_ctrl_t * const p_ctrl, jpeg_encode_image_size_t * p_image_size);

 #if JPEG_CFG_DECODE_ENABLE

    /** Switch between encode and decode mode or vice-versa.
     * @par Implemented as
     * - @ref R_JPEG_ModeSet()
     *
     * @pre The JPEG codec module must have been opened properly.
     * The JPEG Codec can only perform one operation at a time and requires different configuration for encode and
     * decode. This function facilitates easy switching between the two modes in case both are needed in an application.
     * @param[in]     p_ctrl      Control block set in jpeg_api_t::open call.
     * @param[in]     mode        Mode to switch to
     */
    fsp_err_t (* modeSet)(jpeg_ctrl_t * const p_ctrl, jpeg_mode_t mode);
 #endif
#endif
} jpeg_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_jpeg_instance
{
    jpeg_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    jpeg_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    jpeg_api_t const * p_api;          ///< Pointer to the API structure for this instance
} jpeg_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup JPEG_DECODE_API)
 **********************************************************************************************************************/
