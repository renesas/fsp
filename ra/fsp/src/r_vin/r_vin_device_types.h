/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup VIN
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_VIN_DEVICE_TYPES_H
#define R_VIN_DEVICE_TYPES_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_vin_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

/** VIN Interface Mode Type */
typedef enum e_vin_interlace_mode
{
    VIN_INTERLACE_MODE_ODD_FIELD_CAPTURE      = 0, ///< Odd-field (field 1) Capture Mode
    VIN_INTERLACE_MODE_ODD_EVEN_FIELD_CAPTURE = 1, ///< Odd/Even-field Capture Mode
    VIN_INTERLACE_MODE_EVEN_FEILD_CAPTURE     = 2, ///< Even-field Cature Mode
} vin_interlace_mode_t;

/** VIN Dithering Mode */
typedef enum e_vin_dithering_mode
{
    VIN_DITHERING_MODE_WITH_ADDITION = 0, ///< Dithereing with Cumulative Addition
    VIN_DITHERING_MODE_ORDERED_1     = 1, ///< Ordered Dithering 1
    VIN_DITHERING_MODE_ORDERED_2     = 2, ///< Ordered Dithering 2
} vin_dithering_mode_t;

/** VIN Input format */
typedef enum e_vin_input_format
{
    VIN_INPUT_FORMAT_YCBCR422_8_BIT  = 1, ///< Input Format 8-Bit YCbCr-422
    VIN_INPUT_FORMAT_YCBCR422_10_BIT = 3, ///< Input Format 10-Bit YCbCr-42
    VIN_INPUT_FORMAT_RAW8            = 4, ///< Input Format RAW8
    VIN_INPUT_FORMAT_RGB888_24_BIT   = 6, ///< Input Format 24-Bit RGB888
} vin_input_format_t;

/** VIN Data Type Select */
typedef enum e_vin_data_type
{
    VIN_DATA_TYPE_YUV422_8_BIT  = 0x1E, ///< Data Type YUV422 8-bit
    VIN_DATA_TYPE_YUV422_10_BIT = 0x1F, ///< Data Type YUV422 10-bit
    VIN_DATA_TYPE_RGB888_BIT    = 0x24, ///< Data Type RGB888
    VIN_DATA_TYPE_RAW8_BIT      = 0x2A, ///< Data Type RAW8
} vin_data_type_t;

/** VIN Input YUV444 Conversion Mode */
typedef enum e_vin_yuv444_conversion_mode
{
    VIN_YUV444_CONVERSION_MODE_DATA_EXTEND = 0, ///< The data of CbCr to be interpolated holds the data one pixel before
    VIN_YUV444_CONVERSION_MODE_INTERPOLATE = 1, ///< Generates CbCr data to be interpolated
} vin_yuv444_conversion_mode_t;

/** VIN Pixel Data Clipping */
typedef enum e_vin_pixel_data_clipping
{
    VIN_PIXEL_DATA_CLIPPING_DEFAULT  = 0x0, ///< Default clipping mode
    VIN_PIXEL_DATA_CLIPPING_NIBBLE   = 0x1, ///< Lower 4-bits clipping mode
    VIN_PIXEL_DATA_CLIPPING_DISABLED = 0x3, ///< Clipping mode disabled
} vin_pixel_data_clipping_t;

/** VIN Conversion Mode */
typedef enum e_vin_conversion_mode
{
    VIN_CONVERSION_MODE_NONE         = 0, ///< Data is not converted before output
    VIN_CONVERSION_MODE_RGB_TO_ARGB  = 1, ///< RGB input Data is converted to ARGB before output
    VIN_CONVERSION_MODE_YC_SEPARATED = 2, ///< Y and CbCr data are separated before output
} vin_conversion_mode_t;

/** VIN YC Transform Mode */
typedef enum e_vin_yc_transform_mode
{
    VIN_YC_TRANSFORM_MODE_Y_CBCR   = 0, ///< Y and CbCr data are transferred to memory
    VIN_YC_TRANSFORM_MODE_Y        = 1, ///< Y data is transferred to memory as 8-bit data
    VIN_YC_TRANSFORM_MODE_Y10_CBCR = 2, ///< 10-bit Y data and 8-bit CbCr data are transferred to memory
    VIN_YC_TRANSFORM_MODE_Y10      = 3, ///< 10-bit Y data is transferred to memory
} vin_yc_transform_mode_t;

/** VIN Interpolation Mode */
typedef enum e_vin_interpolation_mode
{
    VIN_INTERPOLATION_MODE_BILINEAR = 0, ///< Y and CbCr data are transferred to memory
    VIN_INTERPOLATION_MODE_NEIGHBOR = 1, ///< Y data is transferred to memory as 8-bit data
} vin_interpolation_mode_t;

/** VIN Input Control Structure */
typedef struct st_vin_input_ctrl
{
    union
    {
        struct
        {
            uint32_t module_enable                         : 1; ///< Module dnable
            uint32_t color_space_convert_bypass            : 1; ///< Colo space conversion bypass mode (1: conversion is not performed)
            uint32_t                                       : 1;
            vin_interlace_mode_t interlace_mode            : 2; ///< Interlace mode selection
            uint32_t                                       : 1;
            uint32_t big_endian                            : 1; ///< Big endian enable
            uint32_t                                       : 7;
            vin_dithering_mode_t dithering_mode            : 2; ///< Dithering mode control
            vin_input_format_t   input_mode                : 3; ///< input format selection
            uint32_t                                       : 1;
            uint32_t lut_enable                            : 1; ///< Look Up Table enabled for 10 to 8 bit conversion
            uint32_t                                       : 1;
            uint32_t startup                               : 1; ///< Set 1 to perform initialization
            uint32_t                                       : 1;
            uint32_t dithering_direction                   : 1; ///< Dithering direction
            vin_yuv444_conversion_mode_t yuv444_conversion : 1; ///< yuv444 conversion type
            uint32_t scaling_enable                        : 1; ///< Enable or disable scaling by the UDS
            uint32_t                                       : 1;
            vin_pixel_data_clipping_t pixel_data_clipping  : 2; ///< Pixel data clipping
            uint32_t                                       : 2;
        }        cfg_bits;
        uint32_t cfg_mask;
    };

    struct
    {
        uint16_t line_start;           ///< Line Start Number
        uint16_t line_end;             ///< Line End Number
        uint16_t pixel_start;          ///< Pixel Start Number
        uint16_t pixel_end;            ///< Pixel End Number
    } preclip;
    union
    {
        struct
        {
            uint32_t virtual_channel     : 4; ///< Virtual (0-15) Channel Select
            uint32_t                     : 4;
            vin_data_type_t data_type    : 6; ///< Data Type Select
            uint32_t                     : 11;
            uint32_t sign_extend_disable : 1; ///< Data Extension Select (0: sign-extend, 1:zero-extend)
            uint32_t                     : 6;
        }        csi_mode_bits;
        uint32_t csi_mode_mask;
    };

    union
    {
        struct
        {
            uint32_t field_detect_enable      : 1; ///< Field Detect Enable (0:Even field detect disabled, 1:Even field detect enabled)
            uint32_t                          : 3;
            uint32_t even_field_detect_enable : 1; ///< Even Field Detect Select (1: When even_field_number matches the field number [0] bit)
            uint32_t                          : 11;
            uint32_t even_field_number        : 1; ///< Value for detecting even fields in an interlaced image
            uint32_t                          : 15;
        }        csi_detect_bits;
        uint32_t csi_detect_mask;
    };

    uint16_t image_stride;             ///< Image Stride (Setting Unit: pixel)
} vin_input_ctrl_t;

/** VIN Output Control Structure */
typedef struct st_vin_output_ctrl
{
    uint8_t * image_buffer[3];         ///< Pointer to Image Buffer Memory Base (64-byte aligned)
} vin_output_ctrl_t;

/** VIN Conversion Control Structure */
typedef struct st_vin_conversion_ctrl
{
    union
    {
        struct
        {
            vin_conversion_mode_t data_conversion_mode       : 2; ///< Data Conversion Mode
            uint32_t              alpha_bit_value            : 1; ///< Alpha-bit value for ARGB-1555 Output
            uint32_t                                         : 1;
            uint32_t output_data_byte_swap                   : 1; ///< Output Data Byte Swap Enable
            uint32_t                                         : 3;
            uint32_t extend_rgb_converted_data               : 1; ///< Extend data to 32-bit RGB conversion (when conversion mode is not YC, separated)
            uint32_t                                         : 2;
            uint32_t                yc_data_transform_enable : 1; ///< Transfer Y and CbCr data as 10-bit data (according to input format) instead of yc_data_transform_mode
            vin_yc_transform_mode_t yc_transform_mode        : 3; ///< YC transfer method of YCbCr data when YC separation is selected data_conversion_mode
            uint32_t                                         : 9;
            uint32_t rgb8888_alpha_value                     : 8; ///< Alpha value to be applied for converted RGB8888 output data format
        }        data_mode_bits;
        uint32_t data_mode_mask;
    };
} vin_conversion_ctrl_t;

/** VIN Conversion Data Structure */
typedef struct st_vin_conversion_data
{
    uint32_t * uv_address;             ///< Address for YC separation of YCbCr-422 UV data. (64-byte aligned)

    union
    {
        struct
        {
            uint32_t y_mul              : 14; ///< Y Multiplication Coefficient2 for RGB Calculation
            uint32_t round_down_disable : 1;  ///< Round Down Disable
            uint32_t                    : 15;
        }        yc_rgb_conversion_setting_1_bits;
        uint32_t yc_rgb_conversion_setting_1_mask;
    };

    union
    {
        struct
        {
            uint32_t csub2 : 12;       ///< CbCr Subtraction Coefficient 2 for RGB Calculation
            uint32_t       : 4;
            uint32_t ysub2 : 12;       ///< Y Subtraction Coefficient 2 for RGB Calculation
            uint32_t       : 4;
        }        yc_rgb_conversion_setting_2_bits;
        uint32_t yc_rgb_conversion_setting_2_mask;
    };

    union
    {
        struct
        {
            uint32_t cgrmul2 : 14;     ///< Cr Multiplication Coefficient 2 for G Calculation
            uint32_t         : 2;
            uint32_t rcrmul2 : 14;     ///< Cr multiplication Coefficient 2 for R Calculation
            uint32_t         : 2;
        }        yc_rgb_conversion_setting_3_bits;
        uint32_t yc_rgb_conversion_setting_3_mask;
    };

    union
    {
        struct
        {
            uint32_t bcbmul2 : 14;     ///< Cb Multiplication Coefficient 2 for B Calculation
            uint32_t         : 2;
            uint32_t gcbmul2 : 14;     ///< Cb Multiplication Coefficient 2 for G Calculation
            uint32_t         : 4;
        }        yc_rgb_conversion_setting_4_bits;
        uint32_t yc_rgb_conversion_setting_4_mask;
    };

    union
    {
        struct
        {
            uint32_t                      : 16;
            uint32_t ne_bcb               : 1; ///< B/Cb Interpolation Method When Bilinear/Nearest Neighbor Interpolation is Selected (0: Bilinear, 1: Nearest Neighbor)
            uint32_t ne_gy                : 1; ///< G/Y Interpolation Method When Bilinear/Nearest Neighbor Interpolation is Selected (0: Bilinear, 1: Nearest Neighbor)
            uint32_t ne_rcr               : 1; ///< R/Cr Interpolation Method When Bilinear/Nearest Neighbor Interpolation is Selected (0: Bilinear, 1: Nearest Neighbor)
            uint32_t                      : 1;
            uint32_t pixel_interpolation  : 1; ///< Specifies the method for interpolating pixel components at scale-up/down (Bilinear or multi-tap mode)
            uint32_t                      : 7;
            uint32_t bilinear_advanced    : 1; ///< Bilinear or Nearest Neighbor Interpolation Characteristic Advanced Mode
            uint32_t                      : 1;
            uint32_t scale_up_pixel_count : 1; ///< Advanced Mode: Pixel Count at Scale Up (0: 1+(n-1)*scalar, 1: n*scalar)
            uint32_t                      : 1;
        }        uds_ctrl_bits;
        uint32_t uds_ctrl_mask;
    };

    union
    {
        struct
        {
            union
            {
                struct
                {
                    uint32_t vfrac : 12; ///< Multiplier (Fractional Part) of Vertical Scaling Factor
                    uint32_t vmant : 4;  ///< Multiplier (Integral Part) of Vertical Scaling Factor
                }        vertical_bits;
                uint16_t vertical_mask;
            };
            union
            {
                struct
                {
                    uint32_t hfrac : 12; ///< Multiplier (Fractional Part) of Horizontal Scaling Factor
                    uint32_t hmant : 4;  ///< Multiplier (Integral Part) of Horizontal Scaling Factor
                }        horizontal_bits;
                uint16_t horizontal_mask;
            };
        }        uds_scale_bits;
        uint32_t uds_scale_mask;
    };

    union
    {
        struct
        {
            uint32_t bwidth_v : 7;     ///< Vertical Signal Passband at Image Scale-Up/Down
            uint32_t          : 9;
            uint32_t bwidth_h : 7;     ///< Horizontal Signal Passband at Image Scale-Up/Down
            uint32_t          : 9;
        }        uds_bwidth_bits;
        uint32_t uds_bwidth_mask;
    };

    union
    {
        struct
        {
            uint32_t cl_vsize : 12;    ///< Clipping Size of Vertical Pixel Count after Scale-Up/-Down
            uint32_t          : 4;
            uint32_t cl_hsize : 12;    ///< Clipping Size of Horizontal Pixel Count after Scale-Up/-Down
            uint32_t          : 4;
        }        uds_clipping_bits;
        uint32_t uds_clipping_mask;
    };

    struct
    {
        union
        {
            struct
            {
                int32_t lrp : 13;      ///< R Multiplication Coefficient for Y/Cr/Cb Calculation
                int32_t     : 19;
            }        setting_1_bits;
            uint32_t setting_1_mask;
        };

        union
        {
            struct
            {
                int32_t lgp : 12;      ///< G Multiplication Coefficient for Y/Cr/Cb Calculation
                int32_t     : 4;
                int32_t lbp : 12;      ///< B Multiplication Coefficient for Y/Cr/Cb Calculation
                int32_t     : 4;
            }        setting_2_bits;
            uint32_t setting_2_mask;
        };

        union
        {
            struct
            {
                uint32_t lap             : 12; ///< Y/Cb/Cr Calculation Data Normalized Additional Value
                uint32_t                 : 4;
                uint32_t persistent_bit0 : 1;
                uint32_t                 : 6;
                uint32_t lhen            : 1;  ///< Y/Cb/Cr Calculation Shift Down Result Round-Off Enable
                uint32_t lsft            : 5;  ///< Y/Cb/Cr Calculation Shift Down Volume
                uint32_t                 : 2;
                uint32_t persistent_bit1 : 1;
            }        setting_3_bits;
            uint32_t setting_3_mask;
        };
    } rgb_to_yuv_conversion_settings[3];
} vin_conversion_data_t;

/** VIN Module Status */
typedef union e_vin_module_status
{
    struct
    {
        uint32_t capture_active : 1;   ///< Capture Active Status
        uint32_t active_video   : 1;   ///< Current field is in the active video area defined by the preclipping configuration.
        uint32_t field_status   : 1;   ///< Current capture field
        uint32_t frame_buffer   : 2;   ///< Latest frame buffer id (0b11 : Invalid). NOTE: Should be read after INTS.FIS is set to 1.
        uint32_t                : 11;
        uint32_t memory_active  : 1;   ///< External memory capture is active
        uint32_t                : 2;
        uint32_t latest_buffer  : 2;   ///< Latest valid frame buffer (0b11 : No valid frame buffer)
    }        bits;
    uint32_t mask;
} vin_module_status_t;

/** VIN Interrupt Status */
typedef union e_vin_interrupt_status
{
    struct
    {
        uint32_t fifo_overfow    : 1;  ///< FIFO overflow has occurre   d
        uint32_t end_of_frame    : 1;  ///< End of frame detect
        uint32_t scanline        : 1;  ///< Scanline detect
        uint32_t                 : 1;
        uint32_t field           : 1;  ///< Field detect
        uint32_t frame_complete  : 1;  ///< Frame memory write complete detect
        uint32_t                 : 2;
        uint32_t preclip_h_err   : 1;  ///< Horizontal preclip error
        uint32_t preclip_v_err   : 1;  ///< Vertical preclip error
        uint32_t                 : 4;
        uint32_t resp_overflow   : 1;  ///< Response overflow
        uint32_t axi_err         : 1;  ///< Axi response error
        uint32_t vsync_deasssert : 1;  ///< V-Sync Deassert detect
        uint32_t vsync_assert    : 1;  ///< V-Sync Assert detect
        uint32_t                 : 13;
        uint32_t field_detect2   : 1;  ///< Field interrupt status 2 - This bit is set to 1 regardless of capture operation state.
    }        bits;
    uint32_t mask;
} vin_interrupt_status_t;

/** VIN IRQ Configuration */
typedef struct st_vin_irq_cfg
{
    uint8_t   ipl;                     ///< Interrupt priority
    IRQn_Type irq;                     ///< Interrupt vector number
} vin_irq_cfg_t;

/** VIN Interrupt Control */
typedef struct st_vin_interrupt_cfg
{
    vin_irq_cfg_t status;
    vin_irq_cfg_t error;

    union
    {
        struct
        {
            uint32_t fifo_overflow         : 1; ///< FIFO Overflow Interrupt Enable
            uint32_t end_of_frame          : 1; ///< End of Frame Interrupt Enable
            uint32_t scanline_detect       : 1; ///< Scanline Interrupt Enable
            uint32_t                       : 1;
            uint32_t field_detect_1        : 1; ///< Field Switching Interrupt Enable
            uint32_t frame_write_complete  : 1; ///< Frame MemoryWrite Completion Interrupt Enable
            uint32_t                       : 2;
            uint32_t pixel_count_error     : 1; ///< Horizontal Valid Pixels of Input is Smaller Than Configuration
            uint32_t line_count_error      : 1; ///< Vertical Valid Lines of Input is Smaller Than Configuration
            uint32_t                       : 4;
            uint32_t response_overflow     : 1; ///< Response Overflow Interrupt Enable
            uint32_t axi_resp_error        : 1; ///< AXI Resp Interrupt Enable
            uint32_t vsync_deassert_detect : 1; ///< VSYNC Deassert Detect Interrupt Enable
            uint32_t vsync_assert_detect   : 1; ///< VSYNC Assert Detect Enable
            uint32_t                       : 13;
            uint32_t field_detect_2        : 1; ///< Field Interrupt Enable
        }        status_enable_bits;
        uint32_t status_enable_mask;
    };
    uint16_t scanline_compare_value;            ///< 12-bit value to be compared with the received line count and trigger interrupt (0: disabled)
} vin_interrupt_cfg_t;

/* @} (end addtogroup VIN) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
