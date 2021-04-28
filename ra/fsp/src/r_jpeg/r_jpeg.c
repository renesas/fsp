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

/* "JPEG" in ASCII, used to determine if the module is open */
#define JPEG_OPEN                              (0x4A504547)
#define JPEG_CLOSED                            (0x00000000)

#define JPEG_PRV_ALIGNMENT_8                   (0x07U)
#define JPEG_PRV_ALIGNMENT_16                  (0x0FU)
#define JPEG_PRV_ALIGNMENT_32                  (0x1FU)

#define JPEG_PRV_BUFFER_MAX_SIZE               (0xfff8U)

/* Table 0 is used for Luminance (Y) and Table 1 is used for Chrominance (Cb, Cr) */
#define JPEG_PRV_QUANTIZATION_TABLE_SETTING    (0x14U)

/* AC and DC table for Luminance and Chrominance */
#define JPEG_PRV_HUFFMAN_TABLE_SETTING         (0x3cU)

/* Y'CbCr 4:2:2 settings */
#define JPEG_PRV_YCBCR_BYTES_PER_PIXEL         (2U)
#define JPEG_PRV_YCBCR422                      (0x1U)

/* Huffman and Quantization table address/dimensions */
#define JPEG_PRV_QUANT_TABLE_SIZE              (64)
#define JPEG_PRV_HUFFM_DC_TABLE_SIZE           (28)
#define JPEG_PRV_HUFFM_AC_TABLE_SIZE           (178)

/* End-of-Image (EOI) marker */
#define JPEG_PRV_EOI_B0                        (0xFFU)
#define JPEG_PRV_EOI_B1                        (0xD9U)

#define JPEG_PRV_OPERATION_ENCODE              (0x00U)
#define JPEG_PRV_OPERATION_DECODE              (0x08U)

/***********************************************************************************************************************
 * Constant data
 **********************************************************************************************************************/
#if JPEG_CFG_ENCODE_ENABLE
static const uint8_t g_initial_data[6] =
{
    0xFFU,
    0xD8U,
    0xFFU,
    0xDBU,
    0x00U,
    0x84U
};
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

#if (1 == JPEG_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_jpeg_bufferset_param_check(jpeg_instance_ctrl_t const * const p_ctrl,
                                              void                             * p_buffer,
                                              uint32_t                           buffer_size);

#endif

#if JPEG_CFG_DECODE_ENABLE

static void      r_jpeg_decode_init(jpeg_instance_ctrl_t * p_ctrl);
static void      r_jpeg_decode_image_size_get(uint16_t * p_horizontal, uint16_t * p_vertical);
static fsp_err_t r_jpeg_decode_line_number_get(jpeg_instance_ctrl_t * const p_ctrl, uint16_t * p_lines_to_decode);
static void      r_jpeg_decode_output_start(jpeg_instance_ctrl_t * const p_ctrl, const uint16_t lines_to_decode);

__STATIC_INLINE void r_jpeg_status_change(jpeg_instance_ctrl_t * const p_ctrl, uint8_t clear, uint8_t set);

#endif

#if JPEG_CFG_ENCODE_ENABLE

 #if JPEG_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_jpeg_encode_image_size_param_check(uint16_t horizontal, uint16_t vertical, uint16_t stride);
static fsp_err_t r_jpeg_encode_init_param_check(jpeg_cfg_t const * const p_cfg);

 #endif

static void r_jpeg_encode_init(jpeg_instance_ctrl_t * p_ctrl);
static void r_jpeg_data_correction(jpeg_instance_ctrl_t * p_ctrl, uint8_t final_output);
static void r_jpeg_encode_image_size_set(uint16_t horizontal, uint16_t vertical, uint16_t stride);

#endif

#if JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE

static void r_jpeg_mode_init(jpeg_instance_ctrl_t * p_ctrl, jpeg_mode_t mode);

#endif

static void r_jpeg_mode_deinit(jpeg_mode_t mode);

void jpeg_jdti_isr();
void jpeg_jedi_isr();

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Implementation of General JPEG Codec Driver  */
const jpeg_api_t g_jpeg_on_jpeg =
{
    .open            = R_JPEG_Open,
    .outputBufferSet = R_JPEG_OutputBufferSet,
    .inputBufferSet  = R_JPEG_InputBufferSet,
#if JPEG_CFG_DECODE_ENABLE
    .linesDecodedGet     = R_JPEG_DecodeLinesDecodedGet,
    .horizontalStrideSet = R_JPEG_DecodeHorizontalStrideSet,
    .imageSubsampleSet   = R_JPEG_DecodeImageSubsampleSet,
    .imageSizeGet        = R_JPEG_DecodeImageSizeGet,
    .pixelFormatGet      = R_JPEG_DecodePixelFormatGet,
#endif
#if JPEG_CFG_ENCODE_ENABLE
    .imageSizeSet        = R_JPEG_EncodeImageSizeSet,
#endif
#if JPEG_CFG_ENCODE_ENABLE && JPEG_CFG_DECODE_ENABLE
    .modeSet             = R_JPEG_ModeSet,
#endif
    .statusGet = R_JPEG_StatusGet,
    .close     = R_JPEG_Close,
};

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup JPEG
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the JPEG Codec module.
 * @note   This function configures the JPEG Codec for operation and sets up the registers for data format and
 *         pixel format based on user-supplied configuration parameters.  Interrupts are enabled to support callbacks.
 *
 * @retval  FSP_SUCCESS               JPEG Codec module is properly configured and is ready to take input data.
 * @retval  FSP_ERR_ALREADY_OPEN      JPEG Codec is already open.
 * @retval  FSP_ERR_ASSERTION         Pointer to the control block or the configuration structure is NULL.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED  JEDI interrupt does not have an IRQ number.
 * @retval  FSP_ERR_INVALID_ARGUMENT  (Encode only) Quality factor, horizontal resolution and/or vertical resolution are invalid.
 * @retval  FSP_ERR_INVALID_ALIGNMENT (Encode only) The horizontal resolution (at 16bpp) is not divisible by 8 bytes.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Open (jpeg_ctrl_t * const p_api_ctrl, jpeg_cfg_t const * const p_cfg)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_cfg->jdti_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
 #if JPEG_CFG_DECODE_ENABLE
    FSP_ERROR_RETURN(p_cfg->jedi_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
 #endif

    FSP_ERROR_RETURN((JPEG_OPEN != p_ctrl->open), FSP_ERR_ALREADY_OPEN);

 #if JPEG_CFG_ENCODE_ENABLE
  #if JPEG_CFG_DECODE_ENABLE
    if (p_cfg->default_mode == JPEG_MODE_ENCODE)
  #endif
    {
        fsp_err_t err = r_jpeg_encode_init_param_check(p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif
#endif

    /* Provide clock to the JPEG module */
    R_BSP_MODULE_START(FSP_IP_JPEG, 0U);

    /* Set pointer to control block in configuration */
    p_ctrl->p_cfg = p_cfg;

#if JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE

    /* Initialize based on the default mode */
    r_jpeg_mode_init(p_ctrl, p_cfg->default_mode);
#elif JPEG_CFG_DECODE_ENABLE

    /* Set mode to decode */
    p_ctrl->mode = JPEG_MODE_DECODE;

    r_jpeg_decode_init(p_ctrl);
#else

    /* Set mode to encode */
    p_ctrl->mode = JPEG_MODE_ENCODE;

    r_jpeg_encode_init(p_ctrl);
#endif

    /* Enable interrupts in NVIC */
    R_BSP_IrqCfgEnable(p_cfg->jdti_irq, p_cfg->jdti_ipl, p_ctrl);

#if JPEG_CFG_DECODE_ENABLE
    R_BSP_IrqCfgEnable(p_cfg->jedi_irq, p_cfg->jedi_ipl, p_ctrl);
#endif

    /* Set the status to idle */
    p_ctrl->status = JPEG_STATUS_IDLE;

    /* Set driver status to open */
    p_ctrl->open = JPEG_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Assign a buffer to the JPEG Codec for storing output data.
 * @note   In Decode mode, the number of image lines to be decoded depends on the size of the buffer and the horizontal stride
 *         settings. Once the output buffer size is known, the horizontal stride value is known, and the input
 *         pixel format is known (the input pixel format is obtained by the JPEG decoder from the JPEG headers),
 *         the driver automatically computes the number of lines that can be decoded into the output buffer.
 *         After these lines are decoded, the JPEG engine pauses and a callback function is triggered, so the application
 *         is able to provide the next buffer for the JPEG module to resume the operation.
 *
 *         The JPEG decoding operation automatically starts after both the input buffer and the output buffer are set
 *         and the output buffer is big enough to hold at least eight lines of decoded image data.
 *
 * @retval  FSP_SUCCESS                           The output buffer is properly assigned to JPEG codec device.
 * @retval  FSP_ERR_ASSERTION                     Pointer to the control block or output_buffer
 *                                                is NULL or output_buffer_size is 0.
 * @retval  FSP_ERR_INVALID_ALIGNMENT             Buffer starting address is not 8-byte aligned.
 * @retval  FSP_ERR_NOT_OPEN                      JPEG not opened.
 * @retval  FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE   The number of horizontal pixels exceeds horizontal memory stride.
 * @retval  FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH    Invalid buffer size.
 * @retval  FSP_ERR_IN_USE                        The output buffer cannot be changed during codec operation.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_OutputBufferSet (jpeg_ctrl_t * p_api_ctrl, void * p_output_buffer, uint32_t output_buffer_size)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    err = r_jpeg_bufferset_param_check(p_ctrl, p_output_buffer, output_buffer_size);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN((0 != output_buffer_size) || (p_ctrl->mode == JPEG_MODE_ENCODE),
                     FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH);
#endif

#if JPEG_CFG_ENCODE_ENABLE
 #if JPEG_CFG_DECODE_ENABLE
    if (p_ctrl->mode == JPEG_MODE_ENCODE)
 #endif
    {
        /* These parameters are only used during decode operations */
        FSP_PARAMETER_NOT_USED(p_ctrl);
        FSP_PARAMETER_NOT_USED(output_buffer_size);

 #if JPEG_CFG_PARAM_CHECKING_ENABLE

        /* Output buffer cannot be changed during codec operation */
        FSP_ERROR_RETURN(!((uint32_t) (JPEG_STATUS_RUNNING | JPEG_STATUS_INPUT_PAUSE) & (uint32_t) p_ctrl->status),
                         FSP_ERR_IN_USE);
 #endif

        /* Set the encoding destination address. */
        R_JPEG->JIFEDA = (uint32_t) p_output_buffer;
    }
#endif
#if JPEG_CFG_DECODE_ENABLE
 #if JPEG_CFG_ENCODE_ENABLE
    else
 #endif
    {
        /* Return error code if any errors were detected */
        if ((uint32_t) (JPEG_STATUS_ERROR) &p_ctrl->status)
        {
            return p_ctrl->error_code;
        }

        /* Set the decoding destination address */
        R_JPEG->JIFDDA = (uint32_t) p_output_buffer;

        /* Record the size of the output buffer */
        p_ctrl->output_buffer_size = output_buffer_size;

        /* If the image size is not ready yet, the driver does not know the input pixel format.
         *  Without that information, the driver is unable to compute the number of lines of image
         *  to decode.  In this case, the driver would record the output buffer size.  Once all the
         *  information is ready, the driver would attempt to start the decoding process. */
        if (((uint32_t) JPEG_STATUS_IMAGE_SIZE_READY & (uint32_t) p_ctrl->status) && (p_ctrl->horizontal_stride_bytes))
        {
            uint16_t lines_to_decode = 0;

            /* Determine number of lines to decode */
            err = r_jpeg_decode_line_number_get(p_ctrl, &lines_to_decode);
            if (FSP_SUCCESS == err)
            {
                /* If the driver status is IMAGE_SIZE_READY with no other flags,
                 *  that means the driver just received IMAGE_SIZE.  It has not started
                 *  the decoding process yet */
                if (JPEG_STATUS_IMAGE_SIZE_READY == p_ctrl->status)
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
                else if ((uint32_t) (JPEG_STATUS_OUTPUT_PAUSE) &(uint32_t) p_ctrl->status)
                {
                    /* Set status to running */
                    r_jpeg_status_change(p_ctrl, JPEG_STATUS_OUTPUT_PAUSE, JPEG_STATUS_RUNNING);

                    /* Set number of lines */
                    R_JPEG->JIFDDLC = lines_to_decode;

                    /* Resume the JPEG core (set DOUTRINI and DOUTRCMD) */
                    R_JPEG->JIFDCNT |= (R_JPEG_JIFDCNT_DOUTRINI_Msk | R_JPEG_JIFDCNT_DOUTRCMD_Msk);
                }
                else
                {
                    /* Do nothing */
                }
            }
        }
    }
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Assign an input data buffer to the JPEG codec for processing.
 * @note   After the amount of data is processed, the JPEG driver triggers a callback function with the flag
 *         JPEG_PRV_OPERATION_INPUT_PAUSE set.
 *         The application supplies the next chunk of data to the driver so processing can resume.
 *
 * @note   The JPEG decoding operation automatically starts after both the input buffer and the output buffer are set,
 *         and the output buffer is big enough to hold at least one line of decoded image data.
 *
 *         If zero is provided for the decode data buffer size the JPEG Codec will never pause for more input data and will
 *         continue to read until either an image has been fully decoded or an error condition occurs.
 *
 * @note   When encoding images the minimum data buffer size is 8 lines by 16 Y'CbCr 4:2:2 pixels (256 bytes).  This
 *         corresponds to one minimum coded unit (MCU) of the resulting JPEG output.
 *
 * @retval        FSP_SUCCESS                    The input data buffer is properly assigned to JPEG Codec device.
 * @retval        FSP_ERR_ASSERTION              Pointer to the control block is NULL, or the pointer to the input_buffer is
 *                                               NULL, or the input_buffer_size is 0.
 * @retval        FSP_ERR_INVALID_ALIGNMENT      Buffer starting address is not 8-byte aligned.
 * @retval        FSP_ERR_NOT_OPEN               JPEG not opened.
 * @retval        FSP_ERR_IN_USE                 The input buffer cannot be changed while the codec is running.
 * @retval        FSP_ERR_INVALID_CALL           In encode mode the output buffer must be set first.
 * @retval        FSP_ERR_JPEG_IMAGE_SIZE_ERROR  The buffer size is smaller than the minimum coded unit (MCU).
 **********************************************************************************************************************/
fsp_err_t R_JPEG_InputBufferSet (jpeg_ctrl_t * const p_api_ctrl, void * p_data_buffer, uint32_t data_buffer_size)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t              err    = FSP_SUCCESS;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    err = r_jpeg_bufferset_param_check(p_ctrl, p_data_buffer, data_buffer_size);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

#if JPEG_CFG_ENCODE_ENABLE
 #if JPEG_CFG_DECODE_ENABLE
    if (p_ctrl->mode == JPEG_MODE_ENCODE)
 #endif
    {
        /* Calculate the number of lines to encode */
        p_ctrl->lines_to_encode = (uint16_t) (data_buffer_size / p_ctrl->horizontal_stride_bytes);

 #if JPEG_CFG_PARAM_CHECKING_ENABLE

        /* The JPEG Codec can process a minimum of 8 lines by 16 YCbCr422 pixels (8x16x2 = 256) */
        FSP_ERROR_RETURN((!(data_buffer_size < 256U)), FSP_ERR_JPEG_IMAGE_SIZE_ERROR);

        /* The JPEG Codec requires lines to be 8-byte aligned */
        FSP_ERROR_RETURN(!((uint32_t) p_ctrl->lines_to_encode & JPEG_PRV_ALIGNMENT_8), FSP_ERR_INVALID_ALIGNMENT);

        /* Check if output image buffer is set or not */
        FSP_ERROR_RETURN(0U != R_JPEG->JIFEDA, FSP_ERR_INVALID_CALL);
 #endif

        /* Configure the input buffer address. */
        R_JPEG->JIFESA = (uint32_t) p_data_buffer;

        /* Set the line count */
        R_JPEG->JIFESLC = p_ctrl->lines_to_encode;

        /* Get the status */
        uint32_t status = p_ctrl->status;

        /* If JPEG was just opened or has completed one image, start encoding the new image */
        if (JPEG_STATUS_IDLE & status)
        {
            /* Set the status to running */
            p_ctrl->status = JPEG_STATUS_RUNNING;

            /* Clear lines encoded */
            p_ctrl->total_lines_encoded = 0U;

            /* Start the encoder */

            /* If the vertical resolution is greater than or equal to the number of lines to encode the encoder does not
             * need to stop. In this case input count mode does not need to be enabled. */
            if (p_ctrl->lines_to_encode < p_ctrl->vertical_resolution)
            {
                /* Enable count mode */
                R_JPEG->JIFECNT_b.DINLC = 1;
            }
            else
            {
                /* Disable count mode */
                R_JPEG->JIFECNT_b.DINLC = 0;
            }

            R_JPEG->JCCMD = R_JPEG_JCCMD_JSRT_Msk;
        }
        /* Codec is paused for next chunk of image */
        else if ((uint32_t) JPEG_STATUS_INPUT_PAUSE & status)
        {
            /* Set the status to running */
            p_ctrl->status = JPEG_STATUS_RUNNING;

            /* Resume count mode
             * (See RA6M3 User's Manual (R01UH0886EJ0100) Section 57.3.1.(2).(b) "Compression process") */
            R_JPEG->JIFECNT_b.DINRCMD = 1;
        }
        else
        {
            /* Codec is running, so return error */
            err = FSP_ERR_IN_USE;
        }
    }
#endif
#if JPEG_CFG_DECODE_ENABLE
 #if JPEG_CFG_ENCODE_ENABLE
    else
 #endif
    {
        /* Return error code if any errors were detected */
        if ((uint32_t) JPEG_STATUS_ERROR & p_ctrl->status)
        {
            return p_ctrl->error_code;
        }

        /* Configure the input buffer address */
        R_JPEG->JIFDSA = (uint32_t) p_data_buffer;

        /* If the system is idle, start the JPEG engine.  This allows the
         *  system to obtain image information (image size and input pixel format).  This
         *  information is needed to drive the decode process later on */
        if (JPEG_STATUS_IDLE & p_ctrl->status)
        {
            uint32_t jifdcnt = R_JPEG->JIFDCNT;

            /* Based on buffer size, detect the in count mode setting.
             *  The driver is able to read input data in chunks.  However the size of each chunk
             *  is limited to JPEG_PRV_BUFFER_MAX_SIZE.   Therefore, if the input data size is larger than
             *  JPEG_PRV_BUFFER_MAX_SIZE, the driver assumes the entire input data is present, and can be decoded
             *  without additional input data.   Otherwise, the driver enables input stream feature.
             *  This works even if the entire input size is smaller than JPEG_PRV_BUFFER_MAX_SIZE
             */
            if ((0 != data_buffer_size) && (data_buffer_size <= JPEG_PRV_BUFFER_MAX_SIZE))
            {
                /* Enable input data count interrupt */
                R_JPEG->JINTE1 |= R_JPEG_JINTE1_JINEN_Msk;

                /* Start reading input data */
                jifdcnt |= (R_JPEG_JIFDCNT_JINC_Msk | R_JPEG_JIFDCNT_JINRINI_Msk);

                /* Set number of input bytes to read */
                R_JPEG->JIFDSDC = data_buffer_size; // Number of data is transfer when count-mode is on (in 8-bytes uint);
            }
            else
            {
                /* Start reading input data (JINRINI not needed when not in count mode) */
                jifdcnt &= (uint32_t) ~(R_JPEG_JIFDCNT_JINC_Msk);
            }

            R_JPEG->JIFDCNT = jifdcnt;

            /* Set the internal status */
            p_ctrl->status = JPEG_STATUS_HEADER_PROCESSING;

            /* Start the core */
            R_JPEG->JCCMD = R_JPEG_JCCMD_JSRT_Msk;
        }
        /* If the JPEG driver is paused for input data, the driver needs to resume the
         * operation */
        else if ((uint32_t) JPEG_STATUS_INPUT_PAUSE & p_ctrl->status)
        {
            /* Set status to running */
            r_jpeg_status_change(p_ctrl, JPEG_STATUS_INPUT_PAUSE, JPEG_STATUS_RUNNING);

            /* Set number of transfers (in 8-byte increments) */
            R_JPEG->JIFDSDC = data_buffer_size;

            /* Resume the JPEG core (set JINRINI and JINRCMD) */
            R_JPEG->JIFDCNT |= (R_JPEG_JIFDCNT_JINRINI_Msk | R_JPEG_JIFDCNT_JINRCMD_Msk);
        }
        else
        {
            /* Do nothing */
        }
    }
#endif

    return err;
}

#if JPEG_CFG_DECODE_ENABLE

/*******************************************************************************************************************//**
 * Returns the number of lines decoded into the output buffer.
 * @note   Use this function to retrieve the number of image lines written to the output buffer after a partial decode
 *         operation.  Combined with the horizontal stride settings and the output pixel format the application
 *         can compute the amount of data to read from the output buffer.
 *
 * @retval        FSP_SUCCESS                Line count successfully returned.
 * @retval        FSP_ERR_ASSERTION          Pointer to the control block or p_lines is NULL.
 * @retval        FSP_ERR_NOT_OPEN           JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_DecodeLinesDecodedGet (jpeg_ctrl_t * p_api_ctrl, uint32_t * p_lines)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

 #if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_lines);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
 #endif

    /* Return error code if any errors were detected */
    if ((uint32_t) (JPEG_STATUS_ERROR) &(uint32_t) p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    /* Get decoded line count */
    uint32_t lines = R_JPEG->JIFDDLC & UINT16_MAX;

    /* In 4:2:0 subsampling mode the decoded line count is doubled */
    if (((uint32_t) JPEG_COLOR_SPACE_YCBCR420 | R_JPEG_JCMOD_DSP_Msk) == R_JPEG->JCMOD)
    {
        lines *= 2U;
    }

    *p_lines = lines;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configure horizontal and vertical subsampling.
 * @note   This function can be used to scale the output of decoded image data.
 *
 * @retval        FSP_SUCCESS                Horizontal subsample value is properly configured.
 * @retval        FSP_ERR_ASSERTION          Pointer to the control block is NULL.
 * @retval        FSP_ERR_NOT_OPEN           JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_DecodeImageSubsampleSet (jpeg_ctrl_t * const     p_api_ctrl,
                                          jpeg_decode_subsample_t horizontal_subsample,
                                          jpeg_decode_subsample_t vertical_subsample)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

 #if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
 #endif

    /* Return error code if any errors were detected */
    if ((uint32_t) JPEG_STATUS_ERROR & p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

    /* Update horizontal sub-sample setting */
    p_ctrl->horizontal_subsample = horizontal_subsample;

    /* Set vertical and horizontal rescaling factors */
    R_JPEG->JIFDCNT_b.VINTER = vertical_subsample;
    R_JPEG->JIFDCNT_b.HINTER = horizontal_subsample;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configure horizontal stride setting for decode operations.
 * @note   If the image size is known prior to the open call and/or the output buffer stride is constant, pass the
 *         horizontal stride value in the jpeg_cfg_t structure. Otherwise, after the image size becomes available use
 *         this function to set the output buffer horizontal stride value.
 *
 * @retval  FSP_SUCCESS                           Horizontal stride value is properly configured.
 * @retval  FSP_ERR_ASSERTION                     Pointer to the control block is NULL.
 * @retval  FSP_ERR_INVALID_ALIGNMENT             Horizontal stride is zero or is not 8-byte aligned.
 * @retval  FSP_ERR_NOT_OPEN                      JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_DecodeHorizontalStrideSet (jpeg_ctrl_t * p_api_ctrl, uint32_t horizontal_stride)
{
    fsp_err_t              err    = FSP_SUCCESS;
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

 #if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((0U != horizontal_stride), FSP_ERR_INVALID_ALIGNMENT);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
 #endif

    /* Return error code if any errors were detected */
    if ((uint32_t) JPEG_STATUS_ERROR & p_ctrl->status)
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
    p_ctrl->horizontal_stride_bytes = horizontal_stride;

    /* Set the horizontal stride */
    R_JPEG->JIFDDOFST = horizontal_stride;

    return err;
}

/*******************************************************************************************************************//**
 * Obtain the size of an image being decoded.
 *
 * @retval        FSP_SUCCESS             The image size is available and the horizontal and vertical values are
 *                                        stored in the memory pointed to by p_horizontal_size and p_vertical_size.
 * @retval        FSP_ERR_ASSERTION       Pointer to the control block is NULL and/or size is not ready.
 * @retval        FSP_ERR_NOT_OPEN        JPEG is not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_DecodeImageSizeGet (jpeg_ctrl_t * p_api_ctrl, uint16_t * p_horizontal_size, uint16_t * p_vertical_size)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

 #if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_horizontal_size);
    FSP_ASSERT(NULL != p_vertical_size);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Get the image horizontal and vertical size */
    r_jpeg_decode_image_size_get(p_horizontal_size, p_vertical_size);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the color format of the JPEG being decoded.
 *
 * @retval         FSP_SUCCESS                 The color format was successfully retrieved.
 * @retval         FSP_ERR_ASSERTION           Pointer to the control block is NULL.
 * @retval         FSP_ERR_NOT_OPEN            JPEG is not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_DecodePixelFormatGet (jpeg_ctrl_t * p_api_ctrl, jpeg_color_space_t * p_color_space)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

 #if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_color_space);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Return color format as reported by the JPEG Codec */
    *p_color_space = (jpeg_color_space_t) (R_JPEG->JCMOD_b.REDU);

    return FSP_SUCCESS;
}

#endif

#if JPEG_CFG_ENCODE_ENABLE

/*******************************************************************************************************************//**
 * Set the image dimensions for an encode operation.
 * @note   Image dimensions must be set before setting the input buffer.
 *
 * @retval   FSP_SUCCESS                Image size was successfully written to the JPEG Codec.
 * @retval   FSP_ERR_ASSERTION          Pointer to the control block or p_image_size is NULL.
 * @retval   FSP_ERR_INVALID_ALIGNMENT  Horizontal stride is not 8-byte aligned.
 * @retval   FSP_ERR_INVALID_ARGUMENT   Horizontal or vertical resolution is invalid or zero.
 * @retval   FSP_ERR_NOT_OPEN           JPEG not opened.
 * @retval   FSP_ERR_IN_USE             Image parameters cannot be changed while the codec is running.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_EncodeImageSizeSet (jpeg_ctrl_t * const p_api_ctrl, jpeg_encode_image_size_t * p_image_size)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

 #if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_image_size);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);

    /* Do not change the JPEG Codec image setting while an operation is in progress */
    FSP_ERROR_RETURN(!((uint32_t) (JPEG_STATUS_RUNNING | JPEG_STATUS_INPUT_PAUSE) & (uint32_t) p_ctrl->status),
                     FSP_ERR_IN_USE);

    fsp_err_t err = r_jpeg_encode_image_size_param_check(p_image_size->horizontal_resolution,
                                                         p_image_size->vertical_resolution,
                                                         p_image_size->horizontal_stride_pixels);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif

    /* Record the horizontal stride and vertical size value in the control block */
    p_ctrl->horizontal_stride_bytes = p_image_size->horizontal_stride_pixels * JPEG_PRV_YCBCR_BYTES_PER_PIXEL;
    p_ctrl->vertical_resolution     = p_image_size->vertical_resolution;

    /* Set the image horizontal and vertical size.*/
    r_jpeg_encode_image_size_set(p_image_size->horizontal_resolution,
                                 p_image_size->vertical_resolution,
                                 (uint16_t) p_ctrl->horizontal_stride_bytes);

    return FSP_SUCCESS;
}

 #if JPEG_CFG_DECODE_ENABLE

/*******************************************************************************************************************//**
 * Switch between encode and decode mode (or vice-versa).
 * @note   The codec must not be idle in order to switch modes.
 *
 * @retval   FSP_SUCCESS               Mode changed successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Module is not open.
 * @retval   FSP_ERR_IN_USE            JPEG Codec is currently in use.
 * @retval   FSP_ERR_INVALID_ARGUMENT  (Encode only) Quality factor, horizontal resolution and/or vertical resolution are invalid.
 * @retval   FSP_ERR_INVALID_ALIGNMENT (Encode only) The horizontal resolution (at 16bpp) is not divisible by 8 bytes.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_ModeSet (jpeg_ctrl_t * const p_api_ctrl, jpeg_mode_t mode)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

  #if JPEG_CFG_ENCODE_ENABLE && JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);

    /* Don't allow changing mode while JPEG unit is in use */
    FSP_ERROR_RETURN(p_ctrl->status & JPEG_STATUS_IDLE, FSP_ERR_IN_USE);

    if (mode == JPEG_MODE_ENCODE)
    {
        fsp_err_t err = r_jpeg_encode_init_param_check(p_ctrl->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
  #endif

    /* Deinitialize previous mode */
    r_jpeg_mode_deinit(p_ctrl->mode);

    /* Set and initialize the new mode */
    r_jpeg_mode_init(p_ctrl, mode);

    return FSP_SUCCESS;
}

 #endif

#endif

/*******************************************************************************************************************//**
 * Cancel an outstanding JPEG codec operation and close the device.
 *
 * @retval        FSP_SUCCESS                The JPEG unit is stopped and the driver is closed.
 * @retval        FSP_ERR_ASSERTION          Pointer to the control block is NULL.
 * @retval        FSP_ERR_NOT_OPEN           JPEG not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_Close (jpeg_ctrl_t * p_api_ctrl)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    /* Set JPEG driver status to CLOSED */
    p_ctrl->open = JPEG_CLOSED;

    /* Disable and clear all interrupts */
    R_BSP_IrqDisable(p_ctrl->p_cfg->jdti_irq);
    R_JPEG->JINTE1 = 0;
#if JPEG_CFG_DECODE_ENABLE
    R_BSP_IrqDisable(p_ctrl->p_cfg->jedi_irq);
    R_JPEG->JINTE0 = 0;
#endif

    /* Flush input and output data */
#if JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE
    r_jpeg_mode_deinit(p_ctrl->mode);
#elif JPEG_CFG_DECODE_ENABLE
    r_jpeg_mode_deinit(JPEG_MODE_DECODE);
#else
    r_jpeg_mode_deinit(JPEG_MODE_ENCODE);
#endif

    /* Power off the JPEG unit */
    R_BSP_MODULE_STOP(FSP_IP_JPEG, 0);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the status of the JPEG codec.  This function can also be used to poll the device.
 *
 * @retval         FSP_SUCCESS                 The status information is successfully retrieved.
 * @retval         FSP_ERR_ASSERTION           Pointer to the control block or p_status is NULL.
 * @retval         FSP_ERR_NOT_OPEN            JPEG is not opened.
 **********************************************************************************************************************/
fsp_err_t R_JPEG_StatusGet (jpeg_ctrl_t * p_api_ctrl, jpeg_status_t * p_status)
{
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) p_api_ctrl;

#if JPEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    /* HW does not report error.  Return internal status information */
    *p_status = p_ctrl->status;

    if ((uint32_t) JPEG_STATUS_ERROR & p_ctrl->status)
    {
        return p_ctrl->error_code;
    }

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
 * Parameter checking for buffer setting functions.
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   p_buffer             Pointer to the output buffer.
 * @param[in]   buffer_size          Size of the output buffer.
 * @retval FSP_SUCCESS               All the parameter are valid.
 * @retval FSP_ERR_NOT_OPEN          JPEG module is closed or in use.
 * @retval FSP_ERR_ASSERTION         p_ctrl or p_buffer is NULL.
 * @retval FSP_ERR_INVALID_ALIGNMENT p_output_buffer is not on 8-byte memory boundary, or output_buffer_size is not a
 *                                   multiple of eight.
 **********************************************************************************************************************/
static fsp_err_t r_jpeg_bufferset_param_check (jpeg_instance_ctrl_t const * const p_ctrl,
                                               void                             * p_buffer,
                                               uint32_t                           buffer_size)
{
    FSP_ASSERT(NULL != p_buffer);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN((JPEG_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(!((uint32_t) p_buffer & JPEG_PRV_ALIGNMENT_8), FSP_ERR_INVALID_ALIGNMENT);

 #if JPEG_CFG_DECODE_ENABLE
  #if JPEG_CFG_ENCODE_ENABLE
    if (p_ctrl->mode == JPEG_MODE_DECODE)
  #endif
    {
        FSP_ERROR_RETURN(!(buffer_size & JPEG_PRV_ALIGNMENT_8), FSP_ERR_INVALID_ALIGNMENT);
    }

 #else
    FSP_PARAMETER_NOT_USED(buffer_size);
 #endif

    return FSP_SUCCESS;
}

 #if JPEG_CFG_ENCODE_ENABLE

/*******************************************************************************************************************//**
 * Parameter check function for JPEG Encode image size parameters.
 *
 * @param[in]   horizontal           Horizontal size (in pixels)
 * @param[in]   vertical             Vertical size (in pixels)
 * @param[in]   stride               Horizontal stride (in pixels)
 * @retval FSP_SUCCESS               All parameters are valid.
 * @retval FSP_ERR_INVALID_ARGUMENT  Horizontal resolution and/or vertical resolution are invalid.
 * @retval FSP_ERR_INVALID_ALIGNMENT The resolution is not compatible with the minimum coded unit (MCU) size
 *                                   (16x8 pixels) and/or the horizontal stride is not divisible by 8.
 **********************************************************************************************************************/
static fsp_err_t r_jpeg_encode_image_size_param_check (uint16_t horizontal, uint16_t vertical, uint16_t stride)
{
    FSP_ERROR_RETURN(0U != horizontal, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0U != vertical, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0U == (horizontal & 0x07), FSP_ERR_INVALID_ALIGNMENT);
    FSP_ERROR_RETURN(0U == (vertical & 0x03), FSP_ERR_INVALID_ALIGNMENT);
    FSP_ERROR_RETURN(stride >= horizontal, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(!(stride & JPEG_PRV_ALIGNMENT_8), FSP_ERR_INVALID_ALIGNMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter check function for JPEG Encode initialization.
 *
 * @param[in]   p_cfg                Pointer to config block structure.
 * @retval FSP_SUCCESS               All parameters are valid.
 * @retval FSP_ERR_INVALID_ARGUMENT  Quality factor, horizontal resolution and/or vertical resolution are invalid.
 * @retval FSP_ERR_INVALID_ALIGNMENT The horizontal resolution (at 16bpp) is not divisible by 8 bytes.
 **********************************************************************************************************************/
static fsp_err_t r_jpeg_encode_init_param_check (jpeg_cfg_t const * const p_cfg)
{
    fsp_err_t err = r_jpeg_encode_image_size_param_check(p_cfg->horizontal_resolution,
                                                         p_cfg->vertical_resolution,
                                                         p_cfg->horizontal_stride_pixels);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

 #endif

#endif

#if JPEG_CFG_DECODE_ENABLE

/*******************************************************************************************************************//**
 * Decode initialization function.
 *
 * @param[in,out]  p_ctrl        Pointer to control structure.
 * @retval      None
 **********************************************************************************************************************/
static void r_jpeg_decode_init (jpeg_instance_ctrl_t * p_ctrl)
{
    jpeg_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Set control block */
    p_ctrl->pixel_format            = p_cfg->pixel_format;
    p_ctrl->horizontal_stride_bytes = 0U;
    p_ctrl->output_buffer_size      = 0U;
    p_ctrl->total_lines_decoded     = 0U;
    p_ctrl->horizontal_subsample    = JPEG_DECODE_OUTPUT_NO_SUBSAMPLE;

    /* Perform bus reset */
    R_JPEG->JCCMD = R_JPEG_JCCMD_BRST_Msk;

    /* Reset the JPEG unit buffer addresses and horizontal stride setting */
    R_JPEG->JIFDDA    = 0U;
    R_JPEG->JIFDSA    = 0U;
    R_JPEG->JIFDDOFST = 0U;

    /* Reset encode size registers in case they were in use */
    R_JPEG->JCVSZU = 0;
    R_JPEG->JCVSZD = 0;
    R_JPEG->JCHSZU = 0;
    R_JPEG->JCHSZD = 0;

    /* Configure the JPEG module for decode operation */
    R_JPEG->JCMOD = JPEG_PRV_OPERATION_DECODE;

    /* Set data order (byte swapping) and output format */
    R_JPEG->JIFDCNT = (uint32_t) (p_cfg->decode_output_data_order + (p_cfg->decode_input_data_order << 8) +
                                  (p_cfg->pixel_format << 24));

    /* If the output pixel format is ARGB8888, also configure the alpha value */
    if (JPEG_DECODE_PIXEL_FORMAT_ARGB8888 == p_cfg->pixel_format)
    {
        R_JPEG->JIFDADT = p_cfg->alpha_value;
    }

    /* Clear interrupt status */
    R_JPEG->JINTS0 = 0;
    R_JPEG->JINTS1 = 0;

    /* Clear interrupt request in JCCMD
     * (See RA6M3 User's Manual (R01UH0886EJ0100) Section 57.2.15 "JPEG Interrupt Status Register 0 (JINTS0)" Note 1) */
    R_JPEG->JCCMD = R_JPEG_JCCMD_JEND_Msk;

    /* The following interrupts are enabled:
     *  Interrupt on all errors
     *  Interrupt on Image Size
     */
    R_JPEG->JINTE0 = R_JPEG_JINTE0_INT3_Msk | R_JPEG_JINTE0_INT5_Msk | R_JPEG_JINTE0_INT6_Msk | R_JPEG_JINTE0_INT7_Msk;
    R_JPEG->JINTE1 = R_JPEG_JINTE1_DBTEN_Msk;
}

/*******************************************************************************************************************//**
 * Get JPEG image size (horizontal and vertical) from JCU registers.
 *
 * @param      p_horizontal  Pointer to the storage space for the horizontal value
 * @param      p_vertical    Pointer to the storage space for the vertical value
 ***********************************************************************************************************************/
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
 * Get the number of lines to decode and check that the image size is valid against the output buffer.
 *
 * @param[in]   p_ctrl                Pointer to control block structure.
 * @param[out]  p_lines_to_decode     Pointer to number of Output data lines.
 *
 * @retval      FSP_SUCCESS                           Line count returned successfully.
 * @retval      FSP_ERR_JPEG_BUFFERSIZE_NOT_ENOUGH    The output buffer is too small.
 * @retval      FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE   The number of horizontal pixels exceeds horizontal memory stride.
 **********************************************************************************************************s************/
static fsp_err_t r_jpeg_decode_line_number_get (jpeg_instance_ctrl_t * const p_ctrl, uint16_t * p_lines_to_decode)
{
    fsp_err_t err = FSP_SUCCESS;
    uint16_t  horizontal;
    uint16_t  vertical;
    uint16_t  horizontal_bytes;
    uint16_t  lines_to_decode;

    lines_to_decode = (uint16_t) (p_ctrl->output_buffer_size / p_ctrl->horizontal_stride_bytes);

    r_jpeg_decode_image_size_get(&horizontal, &vertical);

    /* If the decode has been partially completed set lines_to_decode appropriately */
    uint16_t remaining_lines = (uint16_t) (vertical - p_ctrl->total_lines_decoded);
    if (lines_to_decode > remaining_lines)
    {
        lines_to_decode = remaining_lines;
    }

    /* With 4:2:0 subsampling there are half the lines and in any mode the decode line count must be a multiple of 8
     * (see RA6M3 User's Manual R01UH0886EJ0100 section 57.2.28 "JPEG Interface Decompression ... (JIFDDLC)") */
    if (JPEG_COLOR_SPACE_YCBCR420 == (jpeg_color_space_t) (R_JPEG->JCMOD_b.REDU))
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
        if ((uint32_t) (horizontal_bytes >> p_ctrl->horizontal_subsample) > p_ctrl->horizontal_stride_bytes)
        {
            p_ctrl->status     = (jpeg_status_t) (p_ctrl->status | JPEG_STATUS_ERROR);
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
 * Set the JPEG hardware to run in the Output Count mode and start JPEG decompression.
 *
 * @param[in]   p_ctrl              Pointer to control block structure.
 * @param[in]   lines_to_decode     Number of Output data lines.
 * @note This is a private function in the driver module so not check the input parameter.
 **********************************************************************************************************************/
static void r_jpeg_decode_output_start (jpeg_instance_ctrl_t * const p_ctrl, const uint16_t lines_to_decode)
{
    /* Enable the data transfer interrupt */
    R_JPEG->JINTE1 |= R_JPEG_JINTE1_DOUTLEN_Msk;

    /* Enable data output */
    R_JPEG->JIFDCNT |= (R_JPEG_JIFDCNT_DOUTLC_Msk | R_JPEG_JIFDCNT_DOUTRINI_Msk);

    /* Set number of lines to decode */
    R_JPEG->JIFDDLC = lines_to_decode;

    /* Set the driver status to JPEG_STATUS_RUNNING */
    p_ctrl->status = (jpeg_status_t) ((uint32_t) p_ctrl->status | (uint32_t) JPEG_STATUS_RUNNING);

    /* Clear JPEG stop */
    R_JPEG->JCCMD = R_JPEG_JCCMD_JRST_Msk;
}

/*******************************************************************************************************************//**
 * Check if number of pixels is valid against JPEG hardware constraints (the number must be a multiple of the MCU).
 *
 * @param[in]   p_ctrl               Pointer to control block structure.
 * @param[in]   horizontal           Number of horizontal pixels.
 * @param[in]   vertical             Number of vertical pixels.
 **********************************************************************************************************************/
static void r_jpeg_decode_pixel_number_check (jpeg_instance_ctrl_t * const p_ctrl,
                                              const uint16_t               horizontal,
                                              const uint16_t               vertical)
{
    jpeg_color_space_t color_format;

    /* Look-up table for horizontal alignment versus color space */
    uint16_t alignment_lut_h[] =
    {
        [JPEG_COLOR_SPACE_YCBCR444] = JPEG_PRV_ALIGNMENT_8,
        [JPEG_COLOR_SPACE_YCBCR422] = JPEG_PRV_ALIGNMENT_8,
        [JPEG_COLOR_SPACE_YCBCR420] = JPEG_PRV_ALIGNMENT_16,
        [JPEG_COLOR_SPACE_YCBCR411] = JPEG_PRV_ALIGNMENT_8,
    };

    /* Look-up table for vertical alignment versus color space */
    uint16_t alignment_lut_v[] =
    {
        [JPEG_COLOR_SPACE_YCBCR444] = JPEG_PRV_ALIGNMENT_8,
        [JPEG_COLOR_SPACE_YCBCR422] = JPEG_PRV_ALIGNMENT_16,
        [JPEG_COLOR_SPACE_YCBCR420] = JPEG_PRV_ALIGNMENT_16,
        [JPEG_COLOR_SPACE_YCBCR411] = JPEG_PRV_ALIGNMENT_32,
    };

    color_format = (jpeg_color_space_t) (R_JPEG->JCMOD_b.REDU);

    /* Check the number of pixels for individual YCbCr color space formats:
     *   - All formats must be 8-byte aligned
     *   - 4:2:2 horizontal size must be 16-byte aligned
     *   - 4:1:1 horizontal size must be 32-byte aligned
     *   - 4:2:2 horizontal and vertical size must be 16-byte aligned
     */
    if ((horizontal & alignment_lut_h[color_format]) || (vertical & alignment_lut_v[color_format]))
    {
        p_ctrl->status     = (jpeg_status_t) ((uint32_t) p_ctrl->status | (uint32_t) JPEG_STATUS_ERROR);
        p_ctrl->error_code = FSP_ERR_JPEG_UNSUPPORTED_IMAGE_SIZE;
    }
}

/*******************************************************************************************************************//**
 * Inline function to change status bits.
 *
 * @param[in]   p_ctrl    Pointer to control block structure.
 * @param[in]   clear     Bitmask to clear
 * @param[in]   set       Bitmask to set
 * @retval      None
 **********************************************************************************************************************/
__STATIC_INLINE void r_jpeg_status_change (jpeg_instance_ctrl_t * const p_ctrl, uint8_t clear, uint8_t set)
{
    p_ctrl->status = (jpeg_status_t) ((p_ctrl->status & ~clear) | set);
}

#endif

#if JPEG_CFG_ENCODE_ENABLE

/*******************************************************************************************************************//**
 * Encode initialization function.
 *
 * @param[in,out]  p_ctrl        Pointer to control structure.
 * @retval      None
 **********************************************************************************************************************/
static void r_jpeg_encode_init (jpeg_instance_ctrl_t * p_ctrl)
{
    jpeg_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Perform bus reset */
    R_JPEG->JCCMD = R_JPEG_JCCMD_BRST_Msk;

    /* Configure the JPEG module for encode operation and set input pixel format (YCbCr 4:2:2 only) */
    /* (This must be done first as many registers/bitfields are read-only depending on the mode) */
    R_JPEG->JCMOD = JPEG_PRV_OPERATION_ENCODE | (JPEG_PRV_YCBCR422 << R_JPEG_JCMOD_REDU_Pos);

    /* Reset the destination buffer address so the driver knows it has not been set */
    R_JPEG->JIFEDA = 0;

    /* Set the image horizontal and vertical size.*/
    r_jpeg_encode_image_size_set(p_cfg->horizontal_resolution,
                                 p_cfg->vertical_resolution,
                                 p_cfg->horizontal_stride_pixels);

    /* Set the output data format. */
    R_JPEG->JIFECNT = (uint32_t) (p_cfg->encode_input_data_order + (uint32_t) (p_cfg->encode_output_data_order << 8) +
                                  R_JPEG_JIFECNT_DINRINI_Msk);

    /* Quantization table setting
     * NOTE: Table 0 is used for Luminance (Y) and Table 1 is used for Chrominance (Cr and Cb) */
    R_JPEG->JCQTN = JPEG_PRV_QUANTIZATION_TABLE_SETTING;

    /* Huffman table setting */
    R_JPEG->JCHTN = JPEG_PRV_HUFFMAN_TABLE_SETTING;

    /* Upload Huffman and quantization tables to JPEG Codec */
    for (uint8_t i = 0; i < JPEG_PRV_HUFFM_AC_TABLE_SIZE; i++)
    {
        if (i < JPEG_PRV_HUFFM_DC_TABLE_SIZE)
        {
            R_JPEG->JCHTBD0[i] = p_cfg->p_huffman_luma_dc_table[i];
            R_JPEG->JCHTBD1[i] = p_cfg->p_huffman_chroma_dc_table[i];
        }

        if (i < JPEG_PRV_QUANT_TABLE_SIZE)
        {
            R_JPEG->JCQTBL0[i] = p_cfg->p_quant_luma_table[i];
            R_JPEG->JCQTBL1[i] = p_cfg->p_quant_chroma_table[i];
        }

        R_JPEG->JCHTBA0[i] = p_cfg->p_huffman_luma_ac_table[i];
        R_JPEG->JCHTBA1[i] = p_cfg->p_huffman_chroma_ac_table[i];
    }

    /* Reset interval setting */
    R_JPEG->JCDRIU = (uint8_t) (p_cfg->dri_marker >> 8);
    R_JPEG->JCDRID = (uint8_t) (p_cfg->dri_marker & UINT8_MAX);

    /* Record image parameters to ctrl */
    p_ctrl->vertical_resolution     = p_cfg->vertical_resolution;
    p_ctrl->horizontal_stride_bytes = p_cfg->horizontal_stride_pixels * JPEG_PRV_YCBCR_BYTES_PER_PIXEL;

    /* Enabled JPEG Compression data transfer complete interrupt and Count mode Interrupt  */
    R_JPEG->JINTE0 = 0;
    R_JPEG->JINTE1 = R_JPEG_JINTE1_CBTEN_Msk | R_JPEG_JINTE1_DINLEN_Msk;
}

/*******************************************************************************************************************//**
 * Function to correct output data when needed.  (See RA6M3 User's Manual (R01UH0886EJ0100) Section
 *              57.3.1.(2).(c) "Data correction")
 *
 * @param[in]   p_ctrl        Pointer to control block structure.
 * @param[in]   final_output  Number of bytes that may need to be corrected.
 * @retval      None
 **********************************************************************************************************************/
static void r_jpeg_data_correction (jpeg_instance_ctrl_t * p_ctrl, uint8_t final_output)
{
    uint8_t * p_end_data   = NULL;
    uint8_t * p_start_data = NULL;

    /* Get pointer to start and end of JPEG */
    p_start_data = (uint8_t *) R_JPEG->JIFEDA;
    p_end_data   = (uint8_t *) (R_JPEG->JIFEDA + p_ctrl->output_buffer_size) - 2;

    /* Is the final coded data EOI (0xFFD9)? */
    if ((JPEG_PRV_EOI_B1 != p_end_data[1]) && (JPEG_PRV_EOI_B0 != p_end_data[0]))
    {
        /* Correct final data */
        memcpy((p_end_data - (final_output - 1U)), p_start_data, final_output);
    }

    /* Correct data at JIFEDA address */
    memcpy(p_start_data, g_initial_data, 6);
}

/*******************************************************************************************************************//**
 * Set JPEG image size (horizontal and vertical).
 *
 * @param[in]   horizontal   Horizontal size of image (in pixels).
 * @param[in]   vertical     Vertical size of image (in pixels).
 * @param[in]   stride       Horizontal stride of image (in pixels).
 * @retval      None
 **********************************************************************************************************************/
static void r_jpeg_encode_image_size_set (uint16_t horizontal, uint16_t vertical, uint16_t stride)
{
    /* Set the horizontal stride.  */
    R_JPEG->JIFESOFST = stride & R_JPEG_JIFESOFST_ESMW_Msk;

    /* Vertical image size */
    R_JPEG->JCVSZU = (uint8_t) (vertical >> 8);
    R_JPEG->JCVSZD = (uint8_t) vertical;

    /* Horizontal image size */
    R_JPEG->JCHSZU = (uint8_t) (horizontal >> 8);
    R_JPEG->JCHSZD = (uint8_t) horizontal;
}

#endif

#if JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE

/*******************************************************************************************************************//**
 * Initialize the JPEG unit for a specific mode.
 *
 * @param[in]   p_ctrl    Pointer to control block structure.
 * @param[in]   mode      Mode to initialize.
 * @retval      None
 **********************************************************************************************************************/
static void r_jpeg_mode_init (jpeg_instance_ctrl_t * p_ctrl, jpeg_mode_t mode)
{
    /* Set the startup mode */
    p_ctrl->mode = mode;

    if (mode == JPEG_MODE_DECODE)
    {
        r_jpeg_decode_init(p_ctrl);
    }
    else
    {
        r_jpeg_encode_init(p_ctrl);
    }
}

#endif

/*******************************************************************************************************************//**
 * Deinitialize the current mode.
 *
 * @param[in]   mode    Mode to deinitialize
 * @retval      None
 **********************************************************************************************************************/
static void r_jpeg_mode_deinit (jpeg_mode_t mode)
{
#if !(JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE)
    FSP_PARAMETER_NOT_USED(mode);
#endif

#if JPEG_CFG_DECODE_ENABLE
 #if JPEG_CFG_ENCODE_ENABLE
    if (mode == JPEG_MODE_DECODE)
 #endif
    {
        /* JINRCMD and DOUTRCMD must be set for the JPEG Codec to stop cleanly in Decode mode */
        R_JPEG->JIFDCNT |= (R_JPEG_JIFDCNT_JINRCMD_Msk | R_JPEG_JIFDCNT_DOUTRCMD_Msk);
    }
#endif

    /* Perform bus reset to stop any ongoing operation
     * Note: Verified with design team that setting BRST during codec operation is okay. */
    R_JPEG->JCCMD = R_JPEG_JCCMD_BRST_Msk;
}

/*******************************************************************************************************************//**
 * Data Transfer Interrupt (JDTI) Interrupt Service Routine (ISR).
 * @retval None
 **********************************************************************************************************************/
void jpeg_jdti_isr ()
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Obtain the control block. */
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) R_FSP_IsrContextGet(R_FSP_CurrentIrqGet());

    uint32_t             intertype;
    jpeg_callback_args_t args;

    /* Get the interrupt type */
    intertype = R_JPEG->JINTS1;

    /* Clear the interrupt flag */
    R_JPEG->JINTS1 = 0x0;
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

#if JPEG_CFG_DECODE_ENABLE

    /* Return if there are errors */
    if ((uint32_t) JPEG_STATUS_ERROR & p_ctrl->status)
    {

        /* If error is detected, no need to further process this interrupt.  Simply return */
        return;
    }

    /* Check for input pause, output pause and decompression output complete statuses */
    if (intertype & (R_JPEG_JINTS1_JINF_Msk | R_JPEG_JINTS1_DOUTLF_Msk | R_JPEG_JINTS1_DBTF_Msk))
    {
        uint32_t status = p_ctrl->status;

        /* Clear internal status information */
        status &= ~((uint32_t) JPEG_STATUS_RUNNING);

        /* Input data pause (specified number of bytes read) */
        if (intertype & R_JPEG_JINTS1_JINF_Msk)
        {
            /* Set the ctrl status */
            status |= (uint32_t) JPEG_STATUS_INPUT_PAUSE;

            /* Clear the source address */
            R_JPEG->JIFDSA = (uint32_t) 0;
        }

        /* Output data pause (specified number of lines written) */
        if (intertype & R_JPEG_JINTS1_DOUTLF_Msk)
        {
            uint32_t lines_decoded = 0;

            /* Set the ctrl status */
            status |= (uint32_t) JPEG_STATUS_OUTPUT_PAUSE;

            /* Clear the destination address */
            R_JPEG->JIFDDA = 0;

            /* Obtain the number of lines decoded in this operation */
            if (FSP_SUCCESS != R_JPEG_DecodeLinesDecodedGet(p_ctrl, &lines_decoded))
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
        if ((intertype & R_JPEG_JINTS1_DBTF_Msk) || ((p_ctrl->total_lines_decoded >= vertical) && vertical))
        {
            /* Set the ctrl status to done */
            status = (uint32_t) (JPEG_STATUS_IDLE | JPEG_STATUS_OPERATION_COMPLETE);
        }

        /* Write updated status back to control block */
        p_ctrl->status = (jpeg_status_t) status;

        /* Invoke user-supplied callback function if it is set */
        if (NULL != p_ctrl->p_cfg->p_decode_callback)
        {
            args.status    = p_ctrl->status;
            args.p_context = p_ctrl->p_cfg->p_decode_context;
            p_ctrl->p_cfg->p_decode_callback(&args);
        }
    }
#endif

#if JPEG_CFG_ENCODE_ENABLE
    if (intertype & (R_JPEG_JINTS1_CBTF_Msk | R_JPEG_JINTS1_DINLF_Msk))
    {
        /* Record the output buffer size */
        int32_t output_buffer_size = R_JPEG->JCDTCD;
        output_buffer_size        += (R_JPEG->JCDTCM << 8);
        p_ctrl->output_buffer_size = (uint32_t) ((R_JPEG->JCDTCU << 16) + output_buffer_size);

        /* Do not call the callback unless one of the two following events has occurred */
        bool valid = false;

        /* Encode complete */
        if (intertype & R_JPEG_JINTS1_CBTF_Msk)
        {
            /* Data correction */
            uint8_t remainder = (p_ctrl->output_buffer_size % 8);

            /* Data correction decision, if remainder is 1 to 6 bytes */
            if (remainder && (remainder < 7U))
            {
                r_jpeg_data_correction(p_ctrl, remainder);
            }

            p_ctrl->status = (jpeg_status_t) (JPEG_STATUS_IDLE | JPEG_STATUS_OPERATION_COMPLETE);

            valid = true;
        }
        /* Input pause (and not yet complete) */
        else if ((p_ctrl->total_lines_encoded) <= (p_ctrl->vertical_resolution - p_ctrl->lines_to_encode))
        {
            p_ctrl->status = JPEG_STATUS_INPUT_PAUSE;

            valid = true;
        }
        else
        {
            /* Do nothing */
        }

        if (valid)
        {
            /* Update number of lines encoded */
            p_ctrl->total_lines_encoded = (uint16_t) (p_ctrl->total_lines_encoded + p_ctrl->lines_to_encode);

            /* Invoke the callback (if available and requested) */
            if (NULL != p_ctrl->p_cfg->p_encode_callback)
            {
                args.image_size = p_ctrl->output_buffer_size;
                args.status     = p_ctrl->status;
                args.p_context  = p_ctrl->p_cfg->p_encode_context;
                p_ctrl->p_cfg->p_encode_callback(&args);
            }
        }
    }
#endif

    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * JPEG Compression/Decompression Process Interrupt (JEDI) Interrupt Service Routine (ISR).
 *
 * @note The INS6 interrupt (JPEG Process End) is not used as it does not indicate when the data transfer from the JPEG
 *       codec has completed. CBTF and DBTF are used to ensure an operation is only deemed complete when data is ready
 *       for use.
 *
 * @retval None
 **********************************************************************************************************************/
void jpeg_jedi_isr ()
{
#if JPEG_CFG_DECODE_ENABLE

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Obtain the control block. */
    jpeg_instance_ctrl_t * p_ctrl = (jpeg_instance_ctrl_t *) R_FSP_IsrContextGet(R_FSP_CurrentIrqGet());

    uint8_t intertype;

    /* Get the interrupt type */
    intertype = R_JPEG->JINTS0;

    /* Clear the interrupt status */
    R_JPEG->JINTS0 = 0;

    /* Clear the request */
    R_JPEG->JCCMD = R_JPEG_JCCMD_JEND_Msk;
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    uint16_t             horizontal = 0;
    uint16_t             vertical   = 0;
    jpeg_callback_args_t args;

    /* Decompression error */
    if (intertype & R_JPEG_JINTS0_INS5_Msk)
    {
        /* Set the internal status and error code */
        p_ctrl->status     = JPEG_STATUS_ERROR;
        p_ctrl->error_code = (fsp_err_t) (R_JPEG->JCDERR + (uint32_t) FSP_ERR_JPEG_ERR);

        /* Invoke user-supplied callback function if it is set */
        if (NULL != p_ctrl->p_cfg->p_decode_callback)
        {
            args.status    = p_ctrl->status;
            args.p_context = p_ctrl->p_cfg->p_decode_context;
            p_ctrl->p_cfg->p_decode_callback(&args);
        }

        /* If error is detected, no need to further process this interrupt.  Simply return */
        return;
    }

    /* Image size acquired */
    if (intertype & R_JPEG_JINTS0_INS3_Msk)
    {
        /* Set status to image size ready */

        r_jpeg_status_change(p_ctrl, (JPEG_STATUS_HEADER_PROCESSING | JPEG_STATUS_RUNNING),
                             JPEG_STATUS_IMAGE_SIZE_READY);

        /* JPEG header is decoded.  Obtain image size, and input pixel format.  Verify that image size (width and height)
         *      is aligned to the Minimum Coded Unit */
        r_jpeg_decode_image_size_get(&horizontal, &vertical);
        r_jpeg_decode_pixel_number_check(p_ctrl, horizontal, vertical);

        /* Invoke user-supplied callback function if it is set */
        if (NULL != p_ctrl->p_cfg->p_decode_callback)
        {
            args.status    = p_ctrl->status;
            args.p_context = p_ctrl->p_cfg->p_decode_context;
            p_ctrl->p_cfg->p_decode_callback(&args);
        }

        /* If both Input buffer and  output buffer are set, and horizontal stride is set, the driver is available
         *  to determine the number of lines to decode, and start the decoding operation */
        if ((R_JPEG->JIFDSA) && (p_ctrl->output_buffer_size) && (p_ctrl->horizontal_stride_bytes))
        {
            uint16_t lines_to_decode = 0;

            /* Get number of lines that can be decoded at once based on the output buffer size */
            if (FSP_SUCCESS != r_jpeg_decode_line_number_get(p_ctrl, &lines_to_decode))
            {

                /* If error was detected in pixel_number_check there is no need to further process this interrupt */
                return;
            }

            /* Set the ctrl status */
            p_ctrl->status |= (uint32_t) JPEG_STATUS_RUNNING;

            /* Detect the output count mode setting based on buffer size */
            r_jpeg_decode_output_start(p_ctrl, lines_to_decode);
        }
        else
        {
            /* Otherwise clear running status */
            p_ctrl->status &= ~((uint32_t) JPEG_STATUS_RUNNING);
        }
    }
    FSP_CONTEXT_RESTORE
#endif
}
