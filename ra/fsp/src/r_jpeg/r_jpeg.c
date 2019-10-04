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
 * File Name    : r_jpeg_decode.c
 * Description  : JPEG device low level functions used to implement JPEG_DECODE interface driver.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_jpeg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define JPEG_PRV_ALIGNMENT_8             (0x07U)
#define JPEG_PRV_ALIGNMENT_16            (0x0FU)
#define JPEG_PRV_ALIGNMENT_32            (0x1FU)

#define JPEG_PRV_BUFFER_MAX_SIZE         (0xfff8U)

/* JPEG Decompression Control Register (JIFDCNT) bits */
#define JPEG_PRV_JIFDCNT_DOUTLC_SET      (1U << 4)
#define JPEG_PRV_JIFDCNT_DOUTRCMD_SET    (1U << 5)
#define JPEG_PRV_JIFDCNT_DOUTRINI_SET    (1U << 6)
#define JPEG_PRV_JIFDCNT_JINC_SET        (1U << 12)
#define JPEG_PRV_JIFDCNT_JINRCMD_SET     (1U << 13)
#define JPEG_PRV_JIFDCNT_JINRINI_SET     (1U << 14)

/* JPEG Interrupt Enable Register 0 bits */
#define JPEG_PRV_INTE0_INT3              (0x08U)       ///< Enable image size available in decode.
#define JPEG_PRV_INTE0_INT5              (0x20U)       ///< Enable the final number error in decode.
#define JPEG_PRV_INTE0_INT6              (0x40U)       ///< Enable the total number error in decode.
#define JPEG_PRV_INTE0_INT7              (0x80U)       ///< Enable the number error of restart interval in decode.

/* JPEG Interrupt Enable Register 1 bits */
#define JPEG_PRV_INTE1_DOUTLEN           (0x00000001U) ///< Enable output lines number available in decode.
#define JPEG_PRV_INTE1_JINEN             (0x00000002U) ///< Enable input amount available in decode.
#define JPEG_PRV_INTE1_DBTEN             (0x00000004U) ///< Enable data transfer completed in decode.
#define JPEG_PRV_INTE1_DINLEN            (0x00000020U) ///< Enable input line number available in encode.
#define JPEG_PRV_INTE1_CBTEN             (0x00000040U) ///< Enable data transfer completed in encode.

/* JPEG Interrupt Status Register 0 bits */
#define JPEG_PRV_INTS0_INS3              (0x08U)       ///< image size is available in decode.
#define JPEG_PRV_INTS0_INS5              (0x20U)       ///< encounter a encoded data error in decode.
#define JPEG_PRV_INTS0_INS6              (0x40U)       ///< complete encoding process or decoding process.

/* JPEG Interrupt Status Register 1 bits */
#define JPEG_PRV_INTS1_DOUTLF            (0x00000001U) ///< the number of lines of output image data is available in decode.
#define JPEG_PRV_INTS1_JINF              (0x00000002U) ///< the amount of input coded data is available in decode.
#define JPEG_PRV_INTS1_DBTF              (0x00000004U) ///< the last output image data is written in decode.
#define JPEG_PRV_INTS1_DINLF             (0x00000020U) ///< the number of input data lines is available in encode.
#define JPEG_PRV_INTS1_CBTF              (0x00000040U) ///< the last output coded data is written in encode.

#define JPEG_PRV_OPERATION_ENCODE        (0x00U)
#define JPEG_PRV_OPERATION_DECODE        (0x01U)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

#if (1 == JPEG_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t r_jpeg_decode_open_param_check(jpeg_decode_instance_ctrl_t const * const p_ctrl,
                                                jpeg_decode_cfg_t const * const           p_cfg);
static fsp_err_t r_jpeg_decode_bufferset_param_check(jpeg_decode_instance_ctrl_t const * const p_ctrl,
                                                     void                                    * p_buffer,
                                                     uint32_t                                  buffer_size);
static fsp_err_t r_jpeg_decode_horizontalstrideset_param_check(jpeg_decode_instance_ctrl_t const * const p_ctrl,
                                                               uint32_t                                  horizontal_stride);

#endif

static void      r_jpeg_decode_image_size_get(uint16_t * p_horizontal, uint16_t * p_vertical);
static fsp_err_t r_jpeg_decode_line_number_get(jpeg_decode_instance_ctrl_t * const p_ctrl,
                                               uint16_t                          * p_lines_to_decode);
static void r_jpeg_decode_input_start(jpeg_decode_instance_ctrl_t * const p_ctrl, const uint32_t data_buffer_size);
static void r_jpeg_decode_output_start(jpeg_decode_instance_ctrl_t * const p_ctrl, const uint16_t lines_to_decode);
static void r_jpeg_decode_input_resume(jpeg_decode_instance_ctrl_t * const p_ctrl,
                                       const uint32_t                      data_buffer_size);
static void r_jpeg_decode_output_resume(jpeg_decode_instance_ctrl_t * const p_ctrl,
                                        const uint16_t                      lines_to_decode);
void jpeg_jdti_isr();
void jpeg_jedi_isr();

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Implementation of General JPEG Codec Driver  */
const jpeg_decode_api_t g_jpeg_decode_on_jpeg_decode =
{
    .open                = R_JPEG_Decode_Open,
    .outputBufferSet     = R_JPEG_Decode_OutputBufferSet,
    .inputBufferSet      = R_JPEG_Decode_InputBufferSet,
    .linesDecodedGet     = R_JPEG_Decode_LinesDecodedGet,
    .horizontalStrideSet = R_JPEG_Decode_HorizontalStrideSet,
    .imageSubsampleSet   = R_JPEG_Decode_ImageSubsampleSet,
    .imageSizeGet        = R_JPEG_Decode_ImageSizeGet,
    .statusGet           = R_JPEG_Decode_StatusGet,
    .close               = R_JPEG_Decode_Close,
    .versionGet          = R_JPEG_Decode_VersionGet,
    .pixelFormatGet      = R_JPEG_Decode_PixelFormatGet,
};

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro */
static const fsp_version_t g_module_version =
{
    .api_version_minor  = JPEG_DECODE_API_VERSION_MINOR,
    .api_version_major  = JPEG_DECODE_API_VERSION_MAJOR,
    .code_version_major = JPEG_DECODE_CODE_VERSION_MAJOR,
    .code_version_minor = JPEG_DECODE_CODE_VERSION_MINOR
};

/*******************************************************************************************************************//**
 * @addtogroup JPEG
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Initialize the JPEG Codec module.
 * @note   This function configures the JPEG Codec for decoding operation and sets up the registers for data format and
 *         pixel format based on user-supplied configuration parameters.  Interrupts are enabled to support callbacks.
 *
 * @retval  FSP_SUCCESS               JPEG Codec module is properly configured and is ready to take input data.
 * @retval  FSP_ERR_IN_USE            JPEG Codec is already in use.
 * @retval  FSP_ERR_ASSERTION         Pointer to the control block or the configuration structure is NULL.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED  JEDI interrupt does not have an IRQ number.
 * @return                            See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                    return codes.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_Open (jpeg_decode_ctrl_t * const p_api_ctrl, jpeg_decode_cfg_t const * const p_cfg)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err;
    err = r_jpeg_decode_open_param_check(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN == p_ctrl->status), FSP_ERR_IN_USE);

    /* Set control block */
    p_ctrl->pixel_format         = p_cfg->pixel_format;
    p_ctrl->horizontal_stride    = 0U;
    p_ctrl->outbuffer_size       = 0U;
    p_ctrl->total_lines_decoded  = 0U;
    p_ctrl->horizontal_subsample = JPEG_DECODE_OUTPUT_NO_SUBSAMPLE;
    p_ctrl->p_cfg                = p_cfg;

    /* Provide clock to the JPEG module */
    R_BSP_MODULE_START(FSP_IP_JPEG, 0U);

    /* Perform bus reset */
    R_JPEG->JCCMD_b.BRST = 0x01U;

    /* Reset the JPEG unit buffer addresses and horizontal stride setting */
    R_JPEG->JIFDDA    = 0U;
    R_JPEG->JIFDSA    = 0U;
    R_JPEG->JIFDDOFST = 0U;

    /* Reset encode size registers in case they were in use (per TN-SY*-A039A/E) */
    R_JPEG->JCVSZU = 0;
    R_JPEG->JCVSZD = 0;
    R_JPEG->JCHSZU = 0;
    R_JPEG->JCHSZD = 0;

    /* Configure the JPEG module for decode operation and set target pixel format */
    R_JPEG->JCMOD_b.DSP   = (uint8_t) JPEG_PRV_OPERATION_DECODE & 0x01U;
    R_JPEG->JIFDCNT_b.OPF = p_cfg->pixel_format & 0x03U;

    /* If the output pixel format is ARGB8888, also configure the alpha value */
    if (JPEG_DECODE_PIXEL_FORMAT_ARGB8888 == p_cfg->pixel_format)
    {
        R_JPEG->JIFDADT = p_cfg->alpha_value;
    }

    /* Set data order (byte swapping) */
    R_JPEG->JIFDCNT_b.JINSWAP  = p_cfg->input_data_order & 0x07U;
    R_JPEG->JIFDCNT_b.DOUTSWAP = p_cfg->output_data_order & 0x07U;

    /* Clear interrupt status */
    R_JPEG->JINTS0 = 0;
    R_JPEG->JINTS1 = 0;

    /* Clear interrupt request in JCCMD
     * (See RA6M3 User's Manual (R01UH0886EJ0100) Section 57.2.15 "JPEG Interrupt Status Register 0 (JINTS0)" Note 1) */
    R_JPEG->JCCMD_b.JEND = 1;

    /* The following interrupts are enabled:
     *  Interrupt on all errors
     *  Interrupt on Image Size
     */
    R_JPEG->JINTE0 = JPEG_PRV_INTE0_INT3 | JPEG_PRV_INTE0_INT5 | JPEG_PRV_INTE0_INT6 | JPEG_PRV_INTE0_INT7;
    R_JPEG->JINTE1 = JPEG_PRV_INTE1_DBTEN;

    /* Enable interrupts in NVIC */
    R_BSP_IrqCfgEnable(p_cfg->jdti_irq, p_cfg->jdti_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->jedi_irq, p_cfg->jedi_ipl, p_ctrl);

    /* Set the driver status */
    p_ctrl->status = JPEG_DECODE_STATUS_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Assign output buffer to the JPEG Codec for storing output data.
 * @note   The number of image lines to be decoded depends on the size of the buffer and the horizontal stride
 *         settings. Once the output buffer size is known, the horizontal stride value is known, and the input
 *         pixel format is known (the input pixel format is obtained by the JPEG decoder from the JPEG headers),
 *         the driver automatically computes the number of lines that can be decoded into the output buffer.
 *         After these lines are decoded, the JPEG engine pauses and a callback function is triggered, so the application
 *         is able to provide the next buffer for the JPEG module to resume the operation.
 *
 *         The JPEG decoding operation automatically starts after both the input buffer and the output buffer are set,
 *         and the output buffer is big enough to hold at least eight lines of decoded image data.
 *
 * @retval  FSP_SUCCESS                           The output buffer is properly assigned to JPEG codec device.
 * @retval  FSP_ERR_ASSERTION                     Pointer to the control block or the output_buffer
 *                                                is NULL, or the output_buffer_size is 0.
 * @retval  FSP_ERR_INVALID_ALIGNMENT             Buffer starting address is not 8-byte aligned.
 * @retval  FSP_ERR_NOT_OPEN                      JPEG not opened.
 * @retval  FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE   The number of horizontal pixels exceeds horizontal memory stride.
 * @retval  FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH    Invalid buffer size
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_OutputBufferSet (jpeg_decode_ctrl_t * p_api_ctrl,
                                         void               * p_output_buffer,
                                         uint32_t             output_buffer_size)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err             = FSP_SUCCESS;
    uint16_t  lines_to_decode = 0;
#if JPEG_CFG_PARAM_CHECKING_ENABLE
    err = r_jpeg_decode_bufferset_param_check(p_ctrl, p_output_buffer, output_buffer_size);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN((0 != output_buffer_size), FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH);
#endif

    /* Return error code if any errors were detected */
    if ((uint32_t) (JPEG_DECODE_STATUS_ERROR) &p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    /* Set the decoding destination address */
    R_JPEG->JIFDDA = (uint32_t) p_output_buffer;

    /* Record the size of the output buffer */
    p_ctrl->outbuffer_size = output_buffer_size;

    /* If the image size is not ready yet, the driver does not know the input pixel format.
     *  Without that information, the driver is unable to compute the number of lines of image
     *  to decode.  In this case, the driver would record the output buffer size.  Once all the
     *  information is ready, the driver would attempt to start the decoding process. */
    if (((uint32_t) JPEG_DECODE_STATUS_IMAGE_SIZE_READY & (uint32_t) p_ctrl->status) && (p_ctrl->horizontal_stride))
    {
        /* Determine number of lines to decode */
        err = r_jpeg_decode_line_number_get(p_ctrl, &lines_to_decode);
        if (FSP_SUCCESS == err)
        {
            /* If the driver status is IMAGE_SIZE_READY with no other flags,
             *  that means the driver just received IMAGE_SIZE.  It has not started
             *  the decoding process yet */
            if (JPEG_DECODE_STATUS_IMAGE_SIZE_READY == p_ctrl->status)
            {
                /* If Input buffer is set, output buffer is set, and horizontal stride is set, the driver is
                 *  able to determine the number of lines to decode, and start the decoding operation */
                if (R_JPEG->JIFDSA)
                {
                    r_jpeg_decode_output_start(p_ctrl, lines_to_decode);
                }
            }
            /* If the current status is OUTPUT_PAUSE, the driver
             *  needs to resume the operation */
            else if ((uint32_t) (JPEG_DECODE_STATUS_OUTPUT_PAUSE) &(uint32_t) p_ctrl->status)
            {
                r_jpeg_decode_output_resume(p_ctrl, lines_to_decode);
            }
            else
            {
                /* Do nothing */
            }
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief  Returns the number of lines decoded into the output buffer.
 * @note   Use this function to retrieve number of image lines written to the output buffer after JPEG decoded
 *         a partial image.  Combined with the horizontal stride settings and the output pixel format, the application
 *         can compute the amount of data to read from the output buffer.
 *
 * @retval        FSP_SUCCESS                The output buffer is properly assigned to JPEG codec device.
 * @retval        FSP_ERR_ASSERTION          Pointer to the control block is NULL, or the pointer to the output_buffer
 *                                           is NULL, or the output_buffer_size is 0.
 * @retval        FSP_ERR_NOT_OPEN           JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_LinesDecodedGet (jpeg_decode_ctrl_t * p_api_ctrl, uint32_t * p_lines)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_lines);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);
#endif

    /* Return error code if any errors were detected */
    if ((uint32_t) (JPEG_DECODE_STATUS_ERROR) &(uint32_t) p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    /* Get decoded line count */
    uint32_t lines = R_JPEG->JIFDDLC_b.LINES;

    /* In 4:2:0 subsampling mode the decoded line count is doubled */
    if (JPEG_DECODE_COLOR_SPACE_YCBCR420 == (jpeg_decode_color_space_t) (R_JPEG->JCMOD_b.REDU))
    {
        lines *= 2U;
    }

    *p_lines = lines;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Assign input data buffer to JPEG codec for processing.
 * @note   After the amount of data is processed, the JPEG driver triggers a callback function with the flag
 *         JPEG_PRV_OPERATION_INPUT_PAUSE set.
 *         The application supplies the next chunk of data to the driver so JPEG decoding can resume.
 *
 *         The JPEG decoding operation automatically starts after both the input buffer and the output buffer are set,
 *         and the output buffer is big enough to hold at least one line of decoded image data.
 *
 *         If zero is provided for the data buffer size the JPEG Codec will never pause for more input data and will
 *         continue to read until either an image has been fully decoded or an error condition occurs.
 *
 * @retval        FSP_SUCCESS                The input data buffer is properly assigned to JPEG Codec device.
 * @retval        FSP_ERR_ASSERTION          Pointer to the control block is NULL, or the pointer to the input_buffer is
 *                                           NULL, or the input_buffer_size is 0.
 * @retval        FSP_ERR_INVALID_ALIGNMENT  Buffer starting address is not 8-byte aligned.
 * @retval        FSP_ERR_NOT_OPEN           JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_InputBufferSet (jpeg_decode_ctrl_t * const p_api_ctrl,
                                        void                     * p_data_buffer,
                                        uint32_t                   data_buffer_size)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_jpeg_decode_bufferset_param_check(p_ctrl, p_data_buffer, data_buffer_size);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Return error code if any errors were detected */
    if ((uint32_t) JPEG_DECODE_STATUS_ERROR & p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    /* Configure the input buffer address */
    R_JPEG->JIFDSA = (uint32_t) p_data_buffer;

    /* If the system is idle, start the JPEG engine.  This allows the
     *  system to obtain image information (image size and input pixel format).  This
     *  information is needed to drive the decode process later on */
    if (JPEG_DECODE_STATUS_OPEN == p_ctrl->status)
    {
        /* Based on buffer size, detect the in count mode setting.
         *  The driver is able to read input data in chunks.  However the size of each chunk
         *  is limited to JPEG_PRV_BUFFER_MAX_SIZE.   Therefore, if the input data size is larger than
         *  JPEG_PRV_BUFFER_MAX_SIZE, the driver assumes the entire input data is present, and can be decoded
         *  without additional input data.   Otherwise, the driver enables input stream feature.
         *  This works even if the entire input size is smaller than JPEG_PRV_BUFFER_MAX_SIZE */
        r_jpeg_decode_input_start(p_ctrl, data_buffer_size);
    }
    /* If the JPEG driver is paused for input data, the driver needs to resume the
     * operation */
    else if ((uint32_t) JPEG_DECODE_STATUS_INPUT_PAUSE & p_ctrl->status)
    {
        r_jpeg_decode_input_resume(p_ctrl, data_buffer_size);
    }
    else
    {
        /* Do nothing */
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Configure horizontal and vertical subsample.
 * @note   Use for scaling the decoded image.
 *
 * @retval        FSP_SUCCESS                Horizontal stride value is properly configured.
 * @retval        FSP_ERR_ASSERTION          Pointer to the control block is NULL.
 * @retval        FSP_ERR_NOT_OPEN           JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_ImageSubsampleSet (jpeg_decode_ctrl_t * const p_api_ctrl,
                                           jpeg_decode_subsample_t    horizontal_subsample,
                                           jpeg_decode_subsample_t    vertical_subsample)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);
#endif

    /* Return error code if any errors were detected */
    if ((uint32_t) JPEG_DECODE_STATUS_ERROR & p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    /* Update horizontal sub-sample setting */
    p_ctrl->horizontal_subsample = horizontal_subsample;

    /* Set vertical and horizontal rescaling factors */
    R_JPEG->JIFDCNT_b.VINTER = vertical_subsample & 0x03U;
    R_JPEG->JIFDCNT_b.HINTER = horizontal_subsample & 0x03U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Configure horizontal stride setting.
 * @note   Use when the horizontal stride needs to match the image width and the image size is
 *         unknown when opening the JPEG driver. (If the image size is known prior to the open call,
 *         pass the horizontal stride value in the jpef_cfg_t  structure.) After the image size becomes available,
 *         use this function to update the horizontal stride value. If the driver must decode one
 *         line at a time, the horizontal stride can be set to zero.
 *
 * @retval  FSP_SUCCESS                           Horizontal stride value is properly configured.
 * @retval  FSP_ERR_ASSERTION                     Pointer to the control block is NULL.
 * @retval  FSP_ERR_INVALID_ALIGNMENT             Horizontal stride is zero or not 8-byte aligned.
 * @retval  FSP_ERR_NOT_OPEN                      JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_HorizontalStrideSet (jpeg_decode_ctrl_t * p_api_ctrl, uint32_t horizontal_stride)
{
    fsp_err_t err = FSP_SUCCESS;
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    err = r_jpeg_decode_horizontalstrideset_param_check(p_ctrl, horizontal_stride);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Return error code if any errors were detected */
    if ((uint32_t) JPEG_DECODE_STATUS_ERROR & p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    if (JPEG_DECODE_PIXEL_FORMAT_ARGB8888 == R_JPEG->JIFDCNT_b.OPF)
    {
        horizontal_stride *= 4U;
    }
    else
    {
        horizontal_stride *= 2U;
    }

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(!(horizontal_stride & JPEG_PRV_ALIGNMENT_8), FSP_ERR_INVALID_ALIGNMENT);
#endif

    /* Record the horizontal stride value in the control block */
    p_ctrl->horizontal_stride = horizontal_stride;

    /* Set the horizontal stride */
    R_JPEG->JIFDDOFST = horizontal_stride;

    return err;
}

/*******************************************************************************************************************//**
 * @brief  Cancel an outstanding JPEG codec operation and close the device.
 *
 * @retval        FSP_SUCCESS                The input data buffer is properly assigned to JPEG Codec device.
 * @retval        FSP_ERR_ASSERTION          Pointer to the control block is NULL.
 * @retval        FSP_ERR_NOT_OPEN           JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_Close (jpeg_decode_ctrl_t * p_api_ctrl)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);
#endif

    /* Clear JPEG JINTE0 interrupt and JINTE1 interrupt */
    R_JPEG->JINTE0 = 0;
    R_JPEG->JINTE1 = 0;

    /* Disable JEDI and JDTI at NVIC */
    NVIC_DisableIRQ(p_ctrl->p_cfg->jdti_irq);
    NVIC_DisableIRQ(p_ctrl->p_cfg->jedi_irq);

    /* Flush input and output data */
    R_JPEG->JIFDCNT |= (JPEG_PRV_JIFDCNT_JINRCMD_SET | JPEG_PRV_JIFDCNT_DOUTRCMD_SET);

    /* Power off the JPEG unit */
    R_BSP_MODULE_STOP(FSP_IP_JPEG, 0);

    /* Reset the JPEG status flag in the driver */
    p_ctrl->status = JPEG_DECODE_STATUS_NOT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Obtain the size of the image.  This operation is valid during
 *         JPEG decoding operation.
 *
 * @retval        FSP_SUCCESS                    The image size is available and the horizontal and vertical values are
 *                                               stored in the memory pointed to by p_horizontal_size and p_vertical_size.
 * @retval        FSP_ERR_ASSERTION              Pointer to the control block is NULL and/or size is not ready.
 * @retval        FSP_ERR_NOT_OPEN               JPEG is not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_ImageSizeGet (jpeg_decode_ctrl_t * p_api_ctrl,
                                      uint16_t           * p_horizontal_size,
                                      uint16_t           * p_vertical_size)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_horizontal_size);
    FSP_ASSERT(NULL != p_vertical_size);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get the image horizontal and vertical size */
    r_jpeg_decode_image_size_get(p_horizontal_size, p_vertical_size);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Get the status of the JPEG codec.  This function can also be used to poll the device.
 *
 * @retval         FSP_SUCCESS                 The status information is successfully retrieved.
 * @retval         FSP_ERR_ASSERTION           Pointer to the control block is NULL.
 * @retval         FSP_ERR_NOT_OPEN            JPEG is not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_StatusGet (jpeg_decode_ctrl_t * p_api_ctrl, jpeg_decode_status_t * p_status)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);
#endif

    /* HW does not report error.  Return internal status information */
    *p_status = p_ctrl->status;

    if ((uint32_t) JPEG_DECODE_STATUS_ERROR & p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Get the input pixel format.
 *
 * @retval         FSP_SUCCESS                 The status information is successfully retrieved.
 * @retval         FSP_ERR_ASSERTION           Pointer to the control block is NULL.
 * @retval         FSP_ERR_NOT_OPEN            JPEG is not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_PixelFormatGet (jpeg_decode_ctrl_t * p_api_ctrl, jpeg_decode_color_space_t * p_color_space)
{
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_color_space);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* HW does not report error.  Return internal status information */
    *p_color_space = (jpeg_decode_color_space_t) (R_JPEG->JCMOD_b.REDU);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief   Get the version of the JPEG Codec driver.
 *
 * @retval      FSP_SUCCESS        Version number
 * @retval      FSP_ERR_ASSERTION  The parameter p_version is NULL.
 * @note  This function is reentrant.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Decode_VersionGet (fsp_version_t * p_version)
{
#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    *p_version = g_module_version;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup JPEG_DECODE)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (JPEG_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * @brief  Parameter check function for JPEG Decode driver open processing.
 *
 * @param[in]   p_ctrl                 Pointer to control block structure.
 * @param[in]   p_cfg                  Pointer to configuration structure.
 * @retval FSP_SUCCESS                 All the parameter are valid.
 * @retval FSP_ERR_ASSERTION           One of the following parameters is NULL: p_cfg, or p_ctrl
 * @retval FSP_ERR_IRQ_BSP_DISABLED    One or both of the interrupts are not enabled
 **********************************************************************************************************************/
static fsp_err_t r_jpeg_decode_open_param_check (jpeg_decode_instance_ctrl_t const * const p_ctrl,
                                                 jpeg_decode_cfg_t const * const           p_cfg)
{
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(0 != p_cfg->jdti_irq, FSP_ERR_IRQ_BSP_DISABLED);
    FSP_ERROR_RETURN(0 != p_cfg->jedi_irq, FSP_ERR_IRQ_BSP_DISABLED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Parameter check function for JPEG Decode driver outBufferSet processing.
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   p_buffer             Pointer to the output buffer.
 * @param[in]   buffer_size          Size of the output buffer.
 * @retval FSP_SUCCESS               All the parameter are valid.
 * @retval FSP_ERR_NOT_OPEN          JPEG module is closed or in use.
 * @retval FSP_ERR_ASSERTION         One of the following parameters is NULL: p_cfg, or p_ctrl or the callback.
 * @retval FSP_ERR_INVALID_ALIGNMENT p_output_buffer is not on 8-byte memory boundary, or output_buffer_size is not
 *                                   multiple of eight.
 **********************************************************************************************************************/
static fsp_err_t r_jpeg_decode_bufferset_param_check (jpeg_decode_instance_ctrl_t const * const p_ctrl,
                                                      void                                    * p_buffer,
                                                      uint32_t                                  buffer_size)
{
    FSP_ASSERT(NULL != p_buffer);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(!(buffer_size & JPEG_PRV_ALIGNMENT_8), FSP_ERR_INVALID_ALIGNMENT);
    FSP_ERROR_RETURN(!((uint32_t) p_buffer & JPEG_PRV_ALIGNMENT_8), FSP_ERR_INVALID_ALIGNMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Parameter check function for JPEG Decode driver horizontalStrideSet processing.
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   horizontal_stride    Horizontal stride of the output buffer.
 * @retval FSP_SUCCESS               All the parameters are valid.
 * @retval FSP_ERR_NOT_OPEN          JPEG module is closed or in use.
 * @retval FSP_ERR_ASSERTION         One of the following parameters is NULL: p_cfg, or p_ctrl or the callback.
 * @retval FSP_ERR_INVALID_ALIGNMENT horizontal_stride is zero.
 **********************************************************************************************************************/
static fsp_err_t r_jpeg_decode_horizontalstrideset_param_check (jpeg_decode_instance_ctrl_t const * const p_ctrl,
                                                                uint32_t                                  horizontal_stride)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((0U != horizontal_stride), FSP_ERR_INVALID_ALIGNMENT);
    FSP_ERROR_RETURN((JPEG_DECODE_STATUS_NOT_OPEN != p_ctrl->status), FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************
 * @brief Get JPEG image size (horizontal and vertial)
 *
 * @param      p_horizontal  Pointer to the storage space for the horizontal value
 * @param      p_vertical    Pointer to the storage space for the vertical value
 *******************************************************************************/
static void r_jpeg_decode_image_size_get (uint16_t * p_horizontal, uint16_t * p_vertical)
{
    uint16_t upper;
    uint16_t lower;

    /* The upper and lower bytes of the JPEG size are in separate 8-bit registers and are not 16-bit aligned. */

    upper         = (uint16_t) (R_JPEG->JCHSZU << 8);
    lower         = (uint16_t) (R_JPEG->JCHSZD);
    *p_horizontal = (uint16_t) (upper | lower);

    upper       = (uint16_t) (R_JPEG->JCVSZU << 8);
    lower       = (uint16_t) (R_JPEG->JCVSZD);
    *p_vertical = (uint16_t) (upper | lower);
}

/*******************************************************************************************************************//**
 * @brief Get the number of line to decode and check the image size is valid against the Output buffer.
 *
 * @param[in]   p_ctrl                Pointer to control block structure.
 * @param[out]  p_lines_to_decode     Pointer to number of Output data lines.
 * @retval FSP_SUCCESS               All the parameter are valid.
 * @retval FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH    The size of Output buffer is not enough.
 * @retval FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE   The number of horizontal pixels exceeds horizontal memory stride.
 * @note This is a private function in the driver module so not check the input parameter.
 **********************************************************************************************************s************/
static fsp_err_t r_jpeg_decode_line_number_get (jpeg_decode_instance_ctrl_t * const p_ctrl,
                                                uint16_t                          * p_lines_to_decode)
{
    fsp_err_t err = FSP_SUCCESS;
    uint16_t  horizontal;
    uint16_t  vertical;
    uint16_t  horizontal_bytes;
    uint16_t  lines_to_decode;

    lines_to_decode = (uint16_t) (p_ctrl->outbuffer_size / p_ctrl->horizontal_stride);

    r_jpeg_decode_image_size_get(&horizontal, &vertical);

    /* If the decode has been partially completed set lines_to_decode appropriately */
    uint16_t remaining_lines = (uint16_t) (vertical - p_ctrl->total_lines_decoded);
    if (lines_to_decode > remaining_lines)
    {
        lines_to_decode = remaining_lines;
    }

    /* With 4:2:0 subsampling there are half the lines and in any mode the decode line count must be a multiple of 8
     * (see RA6M3 User's Manual R01UH0886EJ0100 section 57.2.28 "JPEG Interface Decompression ... (JIFDDLC)") */
    if (JPEG_DECODE_COLOR_SPACE_YCBCR420 == (jpeg_decode_color_space_t) (R_JPEG->JCMOD_b.REDU))
    {
        lines_to_decode = lines_to_decode / 2U;
    }

    lines_to_decode &= (uint16_t) (~7U);

    if (0U != lines_to_decode)
    {
        if (JPEG_DECODE_PIXEL_FORMAT_ARGB8888 == p_ctrl->pixel_format)
        {
            horizontal_bytes = (uint16_t) (horizontal * 4U);
        }
        else
        {
            horizontal_bytes = (uint16_t) (horizontal * 2U);
        }

        /* If the decoded image will be wider than the destination framebuffer return an error */
        if ((uint32_t) (horizontal_bytes >> p_ctrl->horizontal_subsample) > p_ctrl->horizontal_stride)
        {
            p_ctrl->status     = (jpeg_decode_status_t) (p_ctrl->status | JPEG_DECODE_STATUS_ERROR);
            p_ctrl->error_code = FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE;

            err = FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE;
        }
    }
    else
    {
        err = FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH;
    }

    *p_lines_to_decode = lines_to_decode;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Start JPEG decompression. The JPEG hardware will be set to the Input Count mode if data_buffer_size is smaller
 *  than or equal to JPEG_PRV_BUFFER_MAX_SIZE, else it will not be set to the Input Count mode and the JPEG hardware will not halt
 *  decompression even if the number of input data bytes processed is reached to data_buffer_size. If zero is given to
 *  data_buffer_size, it will not set the JPEG hardware to the Input Count mode.
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   data_buffer_size     Input data size in bytes.
 * @note This is a private function in the driver module so not check the input parameter.
 **********************************************************************************************************************/
static void r_jpeg_decode_input_start (jpeg_decode_instance_ctrl_t * const p_ctrl, const uint32_t data_buffer_size)
{
    uint32_t jifdcnt = R_JPEG->JIFDCNT;

    /* Configure the input count mode */
    if ((0 != data_buffer_size) && (data_buffer_size <= JPEG_PRV_BUFFER_MAX_SIZE))
    {
        /* Enable input data count interrupt */
        R_JPEG->JINTE1 |= JPEG_PRV_INTE1_JINEN;

        /* Start reading input data */
        jifdcnt |= (JPEG_PRV_JIFDCNT_JINC_SET | JPEG_PRV_JIFDCNT_JINRINI_SET);

        /* Set number of input bytes to read */
        R_JPEG->JIFDSDC_b.JDATAS = (uint16_t) data_buffer_size; // Number of data is transfer when count-mode is on (in 8-bytes uint);
    }
    else
    {
        /* Start reading input data (JINRINI not needed when not in count mode) */
        jifdcnt &= (uint32_t) ~(JPEG_PRV_JIFDCNT_JINC_SET);
    }

    R_JPEG->JIFDCNT = jifdcnt;

    /* Set the internal status */
    p_ctrl->status = JPEG_DECODE_STATUS_HEADER_PROCESSING;

    /* Start the core */
    R_JPEG->JCCMD_b.JSRT = 0x1;
}

/*******************************************************************************************************************//**
 * @brief Set the JPEG hardware to run in the Output Count mode and start JPEG decompression.
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   lines_to_decode     Number of Output data lines.
 * @note This is a private function in the driver module so not check the input parameter.
 **********************************************************************************************************************/
static void r_jpeg_decode_output_start (jpeg_decode_instance_ctrl_t * const p_ctrl, const uint16_t lines_to_decode)
{
    /* Enable the data transfer interrupt */
    R_JPEG->JINTE1 |= JPEG_PRV_INTE1_DOUTLEN;

    /* Enable data output */
    R_JPEG->JIFDCNT |= (JPEG_PRV_JIFDCNT_DOUTLC_SET | JPEG_PRV_JIFDCNT_DOUTRINI_SET);

    /* Set number of lines to decode */
    R_JPEG->JIFDDLC_b.LINES = lines_to_decode;

    /* Set the driver status to JPEG_DECODE_STATUS_RUNNING */
    p_ctrl->status = (jpeg_decode_status_t) ((uint32_t) p_ctrl->status | (uint32_t) JPEG_DECODE_STATUS_RUNNING);

    /* Clear JPEG stop */
    R_JPEG->JCCMD_b.JRST = 1U;
}

/*******************************************************************************************************************//**
 * @brief Set the JPEG hardware to run in the Input Count mode and resume JPEG decompression.
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   data_buffer_size     Input data size in bytes.
 * @note This is a private function in the driver module so not check the input parameter.
 **********************************************************************************************************************/
static void r_jpeg_decode_input_resume (jpeg_decode_instance_ctrl_t * const p_ctrl, const uint32_t data_buffer_size)
{
    /* Clear internal status information */
    uint32_t status = (p_ctrl->status & ~((uint32_t) JPEG_DECODE_STATUS_INPUT_PAUSE));

    /* Set internal status information */
    p_ctrl->status = (jpeg_decode_status_t) (status | (uint32_t) JPEG_DECODE_STATUS_RUNNING);

    /* Set number of transfers (in 8-byte increments) */
    R_JPEG->JIFDSDC_b.JDATAS = (uint16_t) data_buffer_size;

    /* Resume the JPEG core (set JINRINI and JINRCMD) */
    R_JPEG->JIFDCNT |= (JPEG_PRV_JIFDCNT_JINRINI_SET | JPEG_PRV_JIFDCNT_JINRCMD_SET);
}

/*******************************************************************************************************************//**
 * @brief Set the JPEG hardware to run in the Output Count mode and resume JPEG decompression.
 *
 * @param[in]   p_ctrl              Pointer to control block structure.
 * @param[in]   lines_to_decode     Number of Output data lines.
 * @note This is a private function in the driver module so not check the input parameter.
 **********************************************************************************************************************/
static void r_jpeg_decode_output_resume (jpeg_decode_instance_ctrl_t * const p_ctrl, const uint16_t lines_to_decode)
{
    /* Clear internal status information */
    uint32_t status = (p_ctrl->status & ~((uint32_t) JPEG_DECODE_STATUS_OUTPUT_PAUSE));

    /* Set internal status information */
    p_ctrl->status = (jpeg_decode_status_t) (status | (uint32_t) JPEG_DECODE_STATUS_RUNNING);

    /* Set number of lines */
    R_JPEG->JIFDDLC_b.LINES = lines_to_decode;

    /* Resume the JPEG core (set DOUTRINI and DOUTRCMD) */
    R_JPEG->JIFDCNT |= (JPEG_PRV_JIFDCNT_DOUTRINI_SET | JPEG_PRV_JIFDCNT_DOUTRCMD_SET);
}

/*******************************************************************************************************************//**
 * @brief Check if number of pixels is valid against JPEG hardware constraints (the number must be multiple of MCU).
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   horizontal           Number of horizontal pixels.
 * @param[in]   vertical             Number of vertical pixels.
 * @note This is a private function in the driver module so not check the input parameter.
 **********************************************************************************************************************/
static void r_jpeg_decode_pixel_number_check (jpeg_decode_instance_ctrl_t * const p_ctrl,
                                              const uint16_t                      horizontal,
                                              const uint16_t                      vertical)
{
    jpeg_decode_color_space_t color_format;

    /* Look-up table for horizontal alignment versus color space */
    uint16_t alignment_lut_h[] =
    {
        [JPEG_DECODE_COLOR_SPACE_YCBCR444] = JPEG_PRV_ALIGNMENT_8,
        [JPEG_DECODE_COLOR_SPACE_YCBCR422] = JPEG_PRV_ALIGNMENT_8,
        [JPEG_DECODE_COLOR_SPACE_YCBCR420] = JPEG_PRV_ALIGNMENT_16,
        [JPEG_DECODE_COLOR_SPACE_YCBCR411] = JPEG_PRV_ALIGNMENT_8,
    };

    /* Look-up table for vertical alignment versus color space */
    uint16_t alignment_lut_v[] =
    {
        [JPEG_DECODE_COLOR_SPACE_YCBCR444] = JPEG_PRV_ALIGNMENT_8,
        [JPEG_DECODE_COLOR_SPACE_YCBCR422] = JPEG_PRV_ALIGNMENT_16,
        [JPEG_DECODE_COLOR_SPACE_YCBCR420] = JPEG_PRV_ALIGNMENT_16,
        [JPEG_DECODE_COLOR_SPACE_YCBCR411] = JPEG_PRV_ALIGNMENT_32,
    };

    color_format = (jpeg_decode_color_space_t) (R_JPEG->JCMOD_b.REDU);

    /* Check the number of pixels for individual YCbCr color space formats:
     *   - All formats must be 8-byte aligned
     *   - 4:2:2 horizontal size must be 16-byte aligned
     *   - 4:1:1 horizontal size must be 32-byte aligned
     *   - 4:2:2 horizontal and vertical size must be 16-byte aligned
     */
    if ((horizontal & alignment_lut_h[color_format]) || (vertical & alignment_lut_v[color_format]))
    {
        p_ctrl->status     = (jpeg_decode_status_t) ((uint32_t) p_ctrl->status | (uint32_t) JPEG_DECODE_STATUS_ERROR);
        p_ctrl->error_code = FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE;
    }
}

/*******************************************************************************************************************//**
 * @brief JPEG internal function: Data Transfer Interrupt (JDTI) Interrupt Service Routine (ISR).
 * @retval None
 **********************************************************************************************************************/
void jpeg_jdti_isr ()
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Obtain the control block. */
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) R_FSP_IsrContextGet(R_FSP_CurrentIrqGet());

    uint32_t intertype;
    jpeg_decode_callback_args_t args;

    /* Get the interrupt type */
    intertype = R_JPEG->JINTS1;

    /* Clear the interrupt flag */
    R_JPEG->JINTS1 = 0x0;

    /* Clear the interrupt flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Return if there are errors */
    if ((uint32_t) JPEG_DECODE_STATUS_ERROR & p_ctrl->status)
    {

        /* If error is detected, no need to further process this interrupt.  Simply return */
        return;
    }

    /* Check for input pause, output pause and decompression output complete statuses */
    if (intertype & (JPEG_PRV_INTS1_JINF | JPEG_PRV_INTS1_DOUTLF | JPEG_PRV_INTS1_DBTF))
    {
        uint32_t status = p_ctrl->status;

        /* Clear internal status information */
        status &= ~((uint32_t) JPEG_DECODE_STATUS_RUNNING);

        /* Input data pause (specified number of bytes read) */
        if (intertype & JPEG_PRV_INTS1_JINF)
        {
            /* Set the ctrl status */
            status |= (uint32_t) JPEG_DECODE_STATUS_INPUT_PAUSE;

            /* Clear the source address */
            R_JPEG->JIFDSA = (uint32_t) 0;
        }

        /* Output data pause (specified number of lines written) */
        if (intertype & JPEG_PRV_INTS1_DOUTLF)
        {
            uint32_t lines_decoded = 0;

            /* Set the ctrl status */
            status |= (uint32_t) JPEG_DECODE_STATUS_OUTPUT_PAUSE;

            /* Clear the destination address */
            R_JPEG->JIFDDA = 0;

            /* Obtain the number of lines decoded in this operation */
            if (FSP_SUCCESS != R_JPEG_Decode_LinesDecodedGet(p_ctrl, &lines_decoded))
            {

                /* If error is detected, no need to further process this interrupt.  Simply return */
                return;
            }

            /* Increment the number of lines decoded */
            p_ctrl->total_lines_decoded = (uint16_t) (p_ctrl->total_lines_decoded + (uint16_t) lines_decoded);
        }

        uint16_t horizontal;
        uint16_t vertical;

        r_jpeg_decode_image_size_get(&horizontal, &vertical);

        /* Data output complete */
        if ((intertype & JPEG_PRV_INTS1_DBTF) || ((p_ctrl->total_lines_decoded >= vertical) && vertical))
        {
            /* Clear output pause status */
            status &= ~((uint32_t) JPEG_DECODE_STATUS_OUTPUT_PAUSE);

            /* Set the ctrl status to done */
            status |= (uint32_t) JPEG_DECODE_STATUS_DONE;
        }

        /* Write updated status back to control block */
        p_ctrl->status = (jpeg_decode_status_t) status;

        /* Invoke user-supplied callback function if it is set */
        if ((NULL != p_ctrl->p_cfg->p_callback))
        {
            args.status    = p_ctrl->status;
            args.p_context = p_ctrl->p_cfg->p_context;
            p_ctrl->p_cfg->p_callback(&args);
        }
    }

    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * @brief JPEG internal function: JPEG Compression/Decompression Process Interrupt (JEDI) Interrupt Service Routine (ISR).
 * @retval None
 **********************************************************************************************************************/
void jpeg_jedi_isr ()
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Obtain the control block. */
    jpeg_decode_instance_ctrl_t * p_ctrl = (jpeg_decode_instance_ctrl_t *) R_FSP_IsrContextGet(R_FSP_CurrentIrqGet());

    uint8_t  intertype;
    uint16_t horizontal = 0;
    uint16_t vertical   = 0;
    jpeg_decode_callback_args_t args;

    /* Get the interrupt type */
    intertype = R_JPEG->JINTS0;

    /* Clear the interrupt status */
    R_JPEG->JINTS0 = 0;

    /* Clear the request */
    R_JPEG->JCCMD_b.JEND = 0x1;

    /* Clear the interrupt flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Decompression error */
    if (intertype & JPEG_PRV_INTS0_INS5)
    {
        /* Set the internal status and error code */
        p_ctrl->status     = JPEG_DECODE_STATUS_ERROR;
        p_ctrl->error_code = (fsp_err_t) (R_JPEG->JCDERR + (uint32_t) FSP_ERR_JPEG_ERR);

        /* Invoke user-supplied callback function if it is set */
        if (NULL != p_ctrl->p_cfg->p_callback)
        {
            args.status    = p_ctrl->status;
            args.p_context = p_ctrl->p_cfg->p_context;
            p_ctrl->p_cfg->p_callback(&args);
        }

        /* If error is detected, no need to further process this interrupt.  Simply return */
        return;
    }

    uint32_t status = p_ctrl->status;

    /* Image size acquired */
    if (intertype & JPEG_PRV_INTS0_INS3)
    {
        /* Clear internal status information */
        status &= ~((uint32_t) (JPEG_DECODE_STATUS_HEADER_PROCESSING | JPEG_DECODE_STATUS_RUNNING));

        /* Set the ctrl status */
        status |= (uint32_t) JPEG_DECODE_STATUS_IMAGE_SIZE_READY;

        /* JPEG header is decoded.  Obtain image size, and input pixel format.  Verify that image size (width and height)
         *      is aligned to the Minimum Coded Unit */
        r_jpeg_decode_image_size_get(&horizontal, &vertical);
        r_jpeg_decode_pixel_number_check(p_ctrl, horizontal, vertical);

        /* Invoke user-supplied callback function if it is set */
        if (NULL != p_ctrl->p_cfg->p_callback)
        {
            args.status    = (jpeg_decode_status_t) status;
            args.p_context = p_ctrl->p_cfg->p_context;
            p_ctrl->p_cfg->p_callback(&args);
        }

        /* If both Input buffer and  output buffer are set, and horizontal stride is set, the driver is available
         *  to determine the number of lines to decode, and start the decoding operation */
        if ((R_JPEG->JIFDSA) && (p_ctrl->outbuffer_size) && (p_ctrl->horizontal_stride))
        {
            uint16_t lines_to_decode = 0;

            /* Get number of lines that can be decoded at once based on the output buffer size */
            if (FSP_SUCCESS != r_jpeg_decode_line_number_get(p_ctrl, &lines_to_decode))
            {

                /* If error was detected in pixel_number_check there is no need to further process this interrupt */
                return;
            }

            /* Set the ctrl status */
            status |= (uint32_t) JPEG_DECODE_STATUS_RUNNING;

            /* Detect the output count mode setting based on buffer size */
            r_jpeg_decode_output_start(p_ctrl, lines_to_decode);
        }
        else
        {
            /* Otherwise clear running status */
            status &= ~((uint32_t) JPEG_DECODE_STATUS_RUNNING);
        }
    }

    /* Decompression process end */
    if (intertype & JPEG_PRV_INTS0_INS6)
    {
        /* Clear internal status information */
        status &= ~((uint32_t) JPEG_DECODE_STATUS_RUNNING);
    }

    /* Commit status to control block */
    p_ctrl->status = (jpeg_decode_status_t) status;

    FSP_CONTEXT_RESTORE
}
