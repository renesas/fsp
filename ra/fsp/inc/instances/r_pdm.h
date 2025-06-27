/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup PDM
 * @{
 **********************************************************************************************************************/

#ifndef R_PDM_H
#define R_PDM_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_pdm_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define PDM_NUM_HPF_COEFFICIENT_H                    2  ///< Number of high pass filter h coefficients
#define PDM_NUM_COMPENSATION_FILTER_COEFFICIENT_H    11 ///< Number of compensation filter h coefficients
#define PDM_NUM_LPF_FILTER_COEFFICIENT_H1            20 ///< Number of low pass filter h1 coefficients

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** PDM_CLKn's division ratio to core clock. */
typedef enum e_pdm_clk_div
{
    PDM_CLOCK_DIV_2  = 0x0,            ///< 0000b: 1/2
    PDM_CLOCK_DIV_4  = 0x1,            ///< 0001b: 1/4
    PDM_CLOCK_DIV_6  = 0x2,            ///< 0010b: 1/6
    PDM_CLOCK_DIV_8  = 0x3,            ///< 0011b: 1/8
    PDM_CLOCK_DIV_10 = 0x4,            ///< 0100b: 1/10
    PDM_CLOCK_DIV_12 = 0x5,            ///< 0101b: 1/12
    PDM_CLOCK_DIV_14 = 0x6,            ///< 0110b: 1/14
    PDM_CLOCK_DIV_16 = 0x7,            ///< 0111b: 1/16
    PDM_CLOCK_DIV_18 = 0x8,            ///< 1000b: 1/18
    PDM_CLOCK_DIV_20 = 0x9,            ///< 1001b: 1/20
    PDM_CLOCK_DIV_22 = 0xA,            ///< 1010b: 1/22
    PDM_CLOCK_DIV_24 = 0xB,            ///< 1011b: 1/24
    PDM_CLOCK_DIV_26 = 0xC,            ///< 1100b: 1/26
    PDM_CLOCK_DIV_28 = 0xD,            ///< 1101b: 1/28
    PDM_CLOCK_DIV_30 = 0xE,            ///< 1110b: 1/30
    PDM_CLOCK_DIV_32 = 0xF,            ///< 1111b: 1/32
} pdm_clk_div_t;

/** Moving average mode for sound detection data. */
typedef enum e_pdm_moving_average_mode
{
    PDM_MOVING_AVERAGE_MODE_1_ORDER = 0, ///< 1-order
    PDM_MOVING_AVERAGE_MODE_2_ORDER = 1, ///< 2-order
    PDM_MOVING_AVERAGE_MODE_4_ORDER = 2, ///< 4-order
} pdm_moving_average_mode_t;

/** Low-pass (half-band decimation) filter input shift setting. */
typedef enum e_pdm_low_pass_filter_shift
{
    PDM_LPF_RIGHT_SHIFT_0 = 0,         ///< No shift
    PDM_LPF_RIGHT_SHIFT_1 = 1,         ///< 1-bit right shift
    PDM_LPF_RIGHT_SHIFT_2 = 2,         ///< 2-bit right shift
    PDM_LPF_RIGHT_SHIFT_3 = 3,         ///< 3-bit right shift
} pdm_low_pass_filter_shift_t;

/** Compensation filter input shift setting. */
typedef enum e_pdm_compensation_filter_shift
{
    PDM_COMPENSATION_FILTER_RIGHT_SHIFT_0 = 0, ///< No shift
    PDM_COMPENSATION_FILTER_RIGHT_SHIFT_1 = 1, ///< 1-bit right shift
    PDM_COMPENSATION_FILTER_RIGHT_SHIFT_2 = 2, ///< 2-bit right shift
    PDM_COMPENSATION_FILTER_RIGHT_SHIFT_3 = 3, ///< 3-bit right shift
} pdm_compensation_filter_shift_t;

/** High-pass filter input shift setting. */
typedef enum e_pdm_high_pass_filter_shift
{
    PDM_HPF_RIGHT_SHIFT_0 = 0,         ///< No shift
    PDM_HPF_RIGHT_SHIFT_1 = 1,         ///< 1-bit right shift
    PDM_HPF_RIGHT_SHIFT_2 = 2,         ///< 2-bit right shift
    PDM_HPF_RIGHT_SHIFT_3 = 3,         ///< 3-bit right shift
} pdm_high_pass_filter_shift_t;

/** Sinc filter mode setting. */
typedef enum e_pdm_sinc_filter_mode
{
    PDM_SINC_FILTER_MODE_1 = 1,        ///< 1-order
    PDM_SINC_FILTER_MODE_2 = 2,        ///< 2-order
    PDM_SINC_FILTER_MODE_3 = 3,        ///< 3-order
    PDM_SINC_FILTER_MODE_4 = 4,        ///< 4-order
} pdm_sinc_filter_mode_t;

/** Data reception interrupt threshold. */
typedef enum e_pdm_interrupt_threshold
{
    PDM_INTERRUPT_THRESHOLD_1  = 0,    ///< 000b: Output interrupt when receiving 1 or more data
    PDM_INTERRUPT_THRESHOLD_2  = 1,    ///< 001b: Output interrupt when receiving 2 or more data
    PDM_INTERRUPT_THRESHOLD_4  = 2,    ///< 010b: Output interrupt when receiving 4 or more data
    PDM_INTERRUPT_THRESHOLD_8  = 3,    ///< 011b: Output interrupt when receiving 8 or more data
    PDM_INTERRUPT_THRESHOLD_16 = 4,    ///< 100b: Output interrupt when receiving 16 or more data
} pdm_interrupt_threshold_t;

/** Short circuit detection enable setting. */
typedef enum e_pdm_short_circuit_enable
{
    PDM_SHORT_CIRCUIT_DISABLED = 0,                               ///< Short circuit disabled
    PDM_SHORT_CIRCUIT_ENABLED  = (1 << R_PDM_CH_PDSDCR_SCDE_Pos), ///< Short circuit enabled
} pdm_short_circuit_enable_t;

/** Overvoltage lower limit enable setting. */
typedef enum e_pdm_overvoltage_lower_limit_enable
{
    PDM_OVERVOLTAGE_LOWER_LIMIT_DISABLED = 0,                                ///< Overvoltage lower limit disabled
    PDM_OVERVOLTAGE_LOWER_LIMIT_ENABLED  = (1 << R_PDM_CH_PDSDCR_OVLDE_Pos), ///< Overvoltage lower limit enabled
} pdm_overvoltage_lower_limit_enable_t;

/** Overvoltage upper limit enable setting. */
typedef enum e_pdm_overvoltage_upper_limit_enable
{
    PDM_OVERVOLTAGE_UPPER_LIMIT_DISABLED = 0,                                ///< Overvoltage upper limit disabled
    PDM_OVERVOLTAGE_UPPER_LIMIT_ENABLED  = (1 << R_PDM_CH_PDSDCR_OVUDE_Pos), ///< Overvoltage upper limit enabled
} pdm_overvoltage_upper_limit_enable_t;

/** Buffer overwrite detection enable setting. */
typedef enum e_pdm_buffer_overwrite_detection_enable
{
    PDM_BUFFER_OVERWRITE_DETECTION_DISABLED = 0,                                 ///< Buffer overwrite detection disabled
    PDM_BUFFER_OVERWRITE_DETECTION_ENABLED  = (1 << R_PDM_CH_PDSDCR_BFOWDE_Pos), ///< Buffer overwrite detection enabled
} pdm_buffer_overwrite_detection_enable_t;

/** Channel instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref pdm_api_t::open is called. */
typedef struct st_pdm_instance_ctrl
{
    uint32_t          open;            // Whether or not this control block is initialized
    pdm_cfg_t const * p_cfg;           // Initial configurations
    R_PDM_CH_Type   * p_reg;           // Pointer to channel-specific PDM registers

    /* Data reception */
    void   * p_rx_dest;                // Destination buffer pointer used read data from PDM FIFO
    uint32_t rx_dest_samples;          // Size of destination buffer
    void   * p_read;                   // Read pointer for p_rx_dest, determines where to store the next sample (block of samples for DMA)
    uint32_t rx_int_count;             // Byte count for processing data in the data interrupt
    uint32_t rx_int_count_max;         // Max byte count to receive at a time

    /* Pointer to callback and optional working memory */
    void (* p_callback)(pdm_callback_args_t *);
    pdm_callback_args_t * p_callback_memory;
    void                * p_context;   // User defined context passed into callback function
} pdm_instance_ctrl_t;

/** PDM configuration extension. This extension is optional. */
typedef struct st_pdm_extended_cfg
{
    pdm_clk_div_t clock_div;                                                               ///< PDM_CLKn's division ratio to core clock

    /** Function Settings. */
    pdm_short_circuit_enable_t              short_circuit_detection_enable;                ///< Short circuit detection enable
    pdm_overvoltage_lower_limit_enable_t    over_voltage_lower_limit_detection_enable;     ///< Overvoltage detection lower limit enable
    pdm_overvoltage_upper_limit_enable_t    over_voltage_upper_limit_detection_enable;     ///< Overvoltage detection upper limit enable
    pdm_buffer_overwrite_detection_enable_t buffer_overwrite_detection_enable;             ///< Buffer overwrite detection enable

    /** Filter Settings. */
    pdm_moving_average_mode_t       moving_average_mode;                                   ///< Moving average mode f or sound detection data
    pdm_low_pass_filter_shift_t     low_pass_filter_shift;                                 ///< Low-pass (half -band decimation) filter input shift setting
    pdm_compensation_filter_shift_t compensation_filter_shift;                             ///< Compensation filter input shift setting
    pdm_high_pass_filter_shift_t    high_pass_filter_shift;                                ///< High-pass filter input shift setting
    pdm_sinc_filter_mode_t          sinc_filter_mode;                                      ///< Sinc filter mode setting
    uint8_t  sincrng;                                                                      ///< Sinc filter output valid range
    uint8_t  sincdec;                                                                      ///< Sinc filter decimation ratio
    uint16_t hpf_coefficient_s0;                                                           ///< High-pass filter coefficient s0 (16-bit signed fixed point data)
    uint16_t hpf_coefficient_k1;                                                           ///< High-pass filter coefficient k1 (16-bit signed fixed point data)
    uint16_t hpf_coefficient_h[PDM_NUM_HPF_COEFFICIENT_H];                                 ///< High-pass filter coefficient h(p) (16-bit signed fixed point data)
    uint16_t compensation_filter_coefficient_h[PDM_NUM_COMPENSATION_FILTER_COEFFICIENT_H]; ///< High-pass filter coefficient h(p) (13-bit signed fixed point data)
    uint16_t lpf_coefficient_h0;                                                           ///< Low-pass (half-band decimation) filter coefficient h0 (13-bit signed fixed point data)
    uint16_t lpf_coefficient_h1[PDM_NUM_LPF_FILTER_COEFFICIENT_H1];                        ///< Low-pass (half-band decimation) filter coefficient h1 (13-bit signed fixed point data)

    /** Data Reception. */
    pdm_interrupt_threshold_t interrupt_threshold;                                         ///< Data reception interrupt threshold

    /** Short-Circuit Detection. */
    uint16_t short_circuit_count_h;                                                        ///< Short circuit detection High Continuous detection count
    uint16_t short_circuit_count_l;                                                        ///< Continuous detection count

    /** Overvoltage Detection. */
    uint32_t overvoltage_detection_lower_limit;                                            ///< Overvoltage detection lower limit (20-bit signed fixed point data)
    uint32_t overvoltage_detection_upper_limit;                                            ///< Overvoltage detection upper limit (20-bit signed fixed point data)
} pdm_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
extern const pdm_api_t g_pdm_on_pdm;

/** @endcond */

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_PDM_Open(pdm_ctrl_t * const p_ctrl, pdm_cfg_t const * const p_cfg);
fsp_err_t R_PDM_Start(pdm_ctrl_t * const p_ctrl,
                      void * const       p_buffer,
                      size_t const       buffer_size,
                      uint32_t const     number_of_data_to_callback);
fsp_err_t R_PDM_Stop(pdm_ctrl_t * const p_ctrl);
fsp_err_t R_PDM_SoundDetectionEnable(pdm_ctrl_t * const p_ctrl, pdm_sound_detection_setting_t sound_detection_setting);
fsp_err_t R_PDM_SoundDetectionDisable(pdm_ctrl_t * const p_ctrl);
fsp_err_t R_PDM_Read(pdm_ctrl_t * const p_ctrl, void * const p_dest, uint32_t const bytes);
fsp_err_t R_PDM_StatusGet(pdm_ctrl_t * const p_ctrl, pdm_status_t * const p_status);
fsp_err_t R_PDM_Close(pdm_ctrl_t * const p_ctrl);
fsp_err_t R_PDM_CallbackSet(pdm_ctrl_t * const          p_ctrl,
                            void (                    * p_callback)(pdm_callback_args_t *),
                            void * const                p_context,
                            pdm_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_PDM_H

/*******************************************************************************************************************//**
 * @} (end defgroup PDM)
 **********************************************************************************************************************/
