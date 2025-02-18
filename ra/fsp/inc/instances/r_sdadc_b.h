/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SDADC_B_H
#define R_SDADC_B_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sdadc_b_cfg.h"
#include "r_adc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup SDADC_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SDADC_B_MAX_NUM_CHANNELS         (8U)
#define SDADC_B_ZD_DETECT_CIRCUIT_NUM    (2U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Operating clock of the digital block. */
typedef enum e_sdadc_b_oper_clk
{
    SDADC_B_CLOCK_DISABLE  = 0,        ///< Disable operating clock
    SDADC_B_CLOCK_IS_12MHZ = 2,        ///< Clock frequency is 12MHz or 12.8MHz
    SDADC_B_CLOCK_IS_16MHZ = 3,        ///< Clock frequency is 16MHz
} sdadc_b_oper_clk_t;

/** Per channel operation mode. */
typedef enum e_sdadc_b_channel_mode
{
    SDADC_B_ELECTRIC_CHARGE_RESET = 0, ///< Electric charge reset
    SDADC_B_NORMAL_OPERATION      = 1, ///< Normal operation
} sdadc_b_channel_mode_t;

/** Per channel power-on control. */
typedef enum e_sdadc_b_channel_power
{
    SDADC_B_CHANNEL_POWER_OFF = 0,     ///< Power off
    SDADC_B_CHANNEL_POWER_ON  = 1,     ///< Power on
} sdadc_b_channel_power_t;

/** Sampling mode select. */
typedef enum e_sdadc_b_samp_mode
{
    SDADC_B_4KHZ_SAMPLING_MODE   = 0,  ///< 4 kHz sampling mode
    SDADC_B_8KHZ_SAMPLING_MODE   = 1,  ///< 8 kHz sampling mode
    SDADC_B_HYBRID_SAMPLING_MODE = 2   ///< 8 kHz / 4 kHz hybird sampling mode
} sdadc_b_samp_mode_t;

/** Per channel preamplifier gain options. */
typedef enum e_sdadc_b_channel_gain
{
    SDADC_B_CHANNEL_GAIN_1  = 0,       ///< Gain of 1
    SDADC_B_CHANNEL_GAIN_2  = 1,       ///< Gain of 2
    SDADC_B_CHANNEL_GAIN_4  = 2,       ///< Gain of 4
    SDADC_B_CHANNEL_GAIN_8  = 3,       ///< Gain of 8
    SDADC_B_CHANNEL_GAIN_16 = 4,       ///< Gain of 16
    SDADC_B_CHANNEL_GAIN_32 = 5,       ///< Gain of 32
} sdadc_b_channel_gain_t;

/** Per channel HPF bypass. */
typedef enum e_sdadc_b_channel_hpf
{
    SDADC_B_CHANNEL_HPF_ENABLE  = 0,   ///< HPF enable
    SDADC_B_CHANNEL_HPF_DISABLE = 1,   ///< HPF disable
} sdadc_b_channel_hpf_t;

/** SDADC data resolution definitions */
typedef enum e_sdadc_b_resolution
{
    SDADC_B_RESOLUTION_24_BIT = 0,     ///< 24 bit resolution
    SDADC_B_RESOLUTION_16_BIT = 1,     ///< 16 bit resolution
} sdadc_b_resolution_t;

/** Zero-cross detection channel  */
typedef enum e_sdadc_b_zc_channel
{
    SDADC_B_ZC_CHANNEL_2_OR_3 = 0,     ///< Detect channel 2 (ZCCTL0) or channel 3 (ZCCTL1)
    SDADC_B_ZC_CHANNEL_1_OR_0 = 1,     ///< Detect channel 1 (ZCCTL0) or channel 0 (ZCCTL1)
} sdadc_b_zc_channel_t;

/** Zero-cross detection output mode. */
typedef enum e_sdadc_b_zc_output_mode
{
    SDADC_B_ZC_PULSE_OUTPUT_MODE = 0,  ///< Pulse output mode
    SDADC_B_ZC_LEVEL_OUTPUT_MODE = 1,  ///< Level output mode
} sdadc_b_zc_output_mode_t;

/** Zero-cross detection output mode. */
typedef enum e_sdadc_b_zc_falling_edge_detection
{
    SDADC_B_ZC_FALLING_EDGE_DETECTION_DISABLE = 0, ///< Disabled
    SDADC_B_ZC_FALLING_EDGE_DETECTION_ENABLE  = 1, ///< Enabled
} sdadc_b_zc_falling_edge_detection_t;

/** Zero-cross detection output mode. */
typedef enum e_sdadc_b_zc_rising_edge_detection
{
    SDADC_B_ZC_RISING_EDGE_DETECTION_DISABLE = 0, ///< Disabled
    SDADC_B_ZC_RISING_EDGE_DETECTION_ENABLE  = 1, ///< Enabled
} sdadc_b_zc_rising_edge_detection_t;

/** HPF cut off. The enum value is to set to SDADHPFCR register. See Table 31.8 Cut-off frequency of HPF of the manual R01UH1005EJ0051 */
typedef enum e_sdadc_b_cutoff
{
    SDADC_B_CUTOFF_00B = 0,            ///< Cut-off frequency 0
    SDADC_B_CUTOFF_01B = 1,            ///< Cut-off frequency 1
    SDADC_B_CUTOFF_10B = 2,            ///< Cut-off frequency 2
    SDADC_B_CUTOFF_11B = 3,            ///< Cut-off frequency 3
} sdadc_b_cutoff_t;

/** SDADC_B active channel configuration. */
typedef struct st_sdadc_b_channel_cfg
{
    union
    {
        uint16_t scan_cfg_mask;                                        ///< Scan channel mask: bit 0 is ch0; bit 7 is channel 7
        __PACKED_STRUCT
        {
            uint8_t channel_0 : 1;                                     // Enable/disable virtual channel 0
            uint8_t channel_1 : 1;                                     // Enable/disable virtual channel 1
            uint8_t channel_2 : 1;                                     // Enable/disable virtual channel 2
            uint8_t channel_3 : 1;                                     // Enable/disable virtual channel 3
            uint8_t channel_4 : 1;                                     // Enable/disable virtual channel 4
            uint8_t channel_5 : 1;                                     // Enable/disable virtual channel 5
            uint8_t channel_6 : 1;                                     // Enable/disable virtual channel 6
            uint8_t channel_7 : 1;                                     // Enable/disable virtual channel 7
            uint8_t           : 8;
        } scan_cfg_mask_b;                                             ///< Scan channel mask bitfield
    };
    sdadc_b_cutoff_t       hpf_cutoff;                                 ///< Cut-off frequency of HPF
    sdadc_b_channel_gain_t gain_setting[SDADC_B_MAX_NUM_CHANNELS - 1]; ///< Gain setting
    sdadc_b_channel_hpf_t  hpf_setting[SDADC_B_MAX_NUM_CHANNELS];      ///< High pass filter on-off
    uint16_t               phase_adjustment[SDADC_B_MAX_NUM_CHANNELS]; ///< Phase adjustment for each channels.
} sdadc_b_scan_cfg_t;

/** SDADC configuration extension. This extension is required and must be provided in adc_cfg_t::p_extend. */
typedef struct st_sdadc_b_on_adc_cfg
{
    sdadc_b_oper_clk_t         oper_clk;      ///< Operating clock of the digital block
    sdadc_b_samp_mode_t        sampling_mode; ///< Sampling mode select
    sdadc_b_scan_cfg_t const * p_channel_cfg; ///< Pointer to original channel config data
    uint8_t   conv_end_ipl;                   ///< Conversion end interrupt priority
    IRQn_Type conv_end_irq;                   ///< Conversion type 1 end IRQ number
    IRQn_Type conv_end_irq2;                  ///< Conversion type 2 end IRQ number
    uint8_t   zc_ipl;                         ///< Zero-cross detection 0 interrupt priority
    IRQn_Type zc_irq;                         ///< Zero-cross detection 0 IRQ number
    uint8_t   zc_ipl2;                        ///< Zero-cross detection 1 interrupt priority
    IRQn_Type zc_irq2;                        ///< Zero-cross detection 1 IRQ number
    union
    {
        uint8_t zc_detection_setting;         ///< Configuration for ZC detection circuits
        __PACKED_STRUCT
        {
            uint8_t channel_zc0   : 1;        // Detection channel for zero-cross detection 0
            uint8_t int_mode_zc0  : 1;        // Interrupt output mode for zero-cross detection 0
            uint8_t fall_edge_zc0 : 1;        // Falling edge detection enable for zero-cross detection 0
            uint8_t rise_edge_zc0 : 1;        // Rising edge detection enable for zero-cross detection 0
            uint8_t channel_zc1   : 1;        // Detection channel for zero-cross detection 1
            uint8_t int_mode_zc1  : 1;        // Interrupt output mode for zero-cross detection 1
            uint8_t fall_edge_zc1 : 1;        // Falling edge detection enable for zero-cross detection 1
            uint8_t rise_edge_zc1 : 1;        // Rising edge detection enable for zero-cross detection 1
        } zc_detection_setting_b;             ///< Configuration for ZC detection bitfield
    };
} sdadc_b_extended_cfg_t;

/** SDADC instance control block. DO NOT INITIALIZE.  Initialized in @ref adc_api_t::open(). */
typedef struct
{
    adc_cfg_t const * p_cfg;
    uint32_t          opened;          ///< Boolean to verify that the Unit has been initialized
    uint32_t          channel_mask;    ///< Channel mask to keep track of channels enabled in scanCfg
    struct
    {
        uint32_t result[SDADC_B_MAX_NUM_CHANNELS];
    }        results;
    uint32_t setup_time_cnt;           ///< Period of 80 conversions for internal setup time
    uint8_t  calibration_complete;     ///< Calibration is completed if set
} sdadc_b_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_sdadc_b;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_SDADC_B_ScanCfg(adc_ctrl_t * p_ctrl, void const * const p_extend);
fsp_err_t R_SDADC_B_InfoGet(adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info);
fsp_err_t R_SDADC_B_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_SDADC_B_ScanGroupStart(adc_ctrl_t * p_ctrl, adc_group_mask_t group_id);
fsp_err_t R_SDADC_B_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_SDADC_B_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_SDADC_B_Read(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);
fsp_err_t R_SDADC_B_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);
fsp_err_t R_SDADC_B_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t const offset);
fsp_err_t R_SDADC_B_Calibrate(adc_ctrl_t * const p_ctrl, void const * p_extend);
fsp_err_t R_SDADC_B_Close(adc_ctrl_t * p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup ADC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
