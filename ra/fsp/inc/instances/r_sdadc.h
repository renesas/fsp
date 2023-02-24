/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_SDADC_H
#define R_SDADC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sdadc_cfg.h"
#include "r_adc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup SDADC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SDADC_MAX_NUM_CHANNELS    (5U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Source of Vref. */
typedef enum e_sdadc_vref_src
{
    SDADC_VREF_SRC_INTERNAL = 0,       ///< Vref is internally sourced, can be output as SBIAS
    SDADC_VREF_SRC_EXTERNAL = 1,       ///< Vref is externally sourced from the VREFI pin
} sdadc_vref_src_t;

/** Voltage of Vref. */
typedef enum e_sdadc_vref_voltage
{
    SDADC_VREF_VOLTAGE_800_MV  = 0,    ///< Vref is 0.8 V
    SDADC_VREF_VOLTAGE_1000_MV = 1,    ///< Vref is 1.0 V
    SDADC_VREF_VOLTAGE_1200_MV = 2,    ///< Vref is 1.2 V
    SDADC_VREF_VOLTAGE_1400_MV = 3,    ///< Vref is 1.4 V
    SDADC_VREF_VOLTAGE_1600_MV = 4,    ///< Vref is 1.6 V
    SDADC_VREF_VOLTAGE_1800_MV = 5,    ///< Vref is 1.8 V
    SDADC_VREF_VOLTAGE_2000_MV = 6,    ///< Vref is 2.0 V
    SDADC_VREF_VOLTAGE_2200_MV = 7,    ///< Vref is 2.2 V
    SDADC_VREF_VOLTAGE_2400_MV = 15,   ///< Vref is 2.4 V (only valid for external Vref)
} sdadc_vref_voltage_t;

/** Per channel input mode. */
typedef enum e_sdadc_channel_input
{
    SDADC_CHANNEL_INPUT_DIFFERENTIAL = 0, ///< Differential input
    SDADC_CHANNEL_INPUT_SINGLE_ENDED = 1, ///< Single-ended input
} sdadc_channel_input_t;

/** Per channel stage 1 gain options. */
typedef enum e_sdadc_channel_stage_1_gain
{
    SDADC_CHANNEL_STAGE_1_GAIN_1 = 0,  ///< Gain of 1
    SDADC_CHANNEL_STAGE_1_GAIN_2 = 1,  ///< Gain of 2
    SDADC_CHANNEL_STAGE_1_GAIN_3 = 2,  ///< Gain of 3 (only valid for stage 1)
    SDADC_CHANNEL_STAGE_1_GAIN_4 = 3,  ///< Gain of 4
    SDADC_CHANNEL_STAGE_1_GAIN_8 = 4,  ///< Gain of 8
} sdadc_channel_stage_1_gain_t;

/** Per channel stage 2 gain options. */
typedef enum e_sdadc_channel_stage_2_gain
{
    SDADC_CHANNEL_STAGE_2_GAIN_1 = 0,  ///< Gain of 1
    SDADC_CHANNEL_STAGE_2_GAIN_2 = 1,  ///< Gain of 2
    SDADC_CHANNEL_STAGE_2_GAIN_4 = 2,  ///< Gain of 4
    SDADC_CHANNEL_STAGE_2_GAIN_8 = 3,  ///< Gain of 8
} sdadc_channel_stage_2_gain_t;

/** Per channel oversampling ratio. */
typedef enum e_sdadc_channel_oversampling
{
    SDADC_CHANNEL_OVERSAMPLING_64   = 0, ///< Oversampling ratio of 64
    SDADC_CHANNEL_OVERSAMPLING_128  = 1, ///< Oversampling ratio of 128
    SDADC_CHANNEL_OVERSAMPLING_256  = 2, ///< Oversampling ratio of 256
    SDADC_CHANNEL_OVERSAMPLING_512  = 3, ///< Oversampling ratio of 512
    SDADC_CHANNEL_OVERSAMPLING_1024 = 4, ///< Oversampling ratio of 1024
    SDADC_CHANNEL_OVERSAMPLING_2048 = 5, ///< Oversampling ratio of 2048
} sdadc_channel_oversampling_t;

/** Per channel polarity, valid for single-ended input only. */
typedef enum e_sdadc_channel_polarity
{
    SDADC_CHANNEL_POLARITY_POSITIVE = 0, ///< Positive-side single-ended input
    SDADC_CHANNEL_POLARITY_NEGATIVE = 1, ///< Negative-side single-ended input
} sdadc_channel_polarity_t;

/** Per channel number of conversions to average before conversion end callback. */
typedef enum e_sdadc_channel_average_t
{
    SDADC_CHANNEL_AVERAGE_NONE = 0,    ///< Do not average (callback for each conversion)
    SDADC_CHANNEL_AVERAGE_8    = 12,   ///< Average 8 samples for each conversion end callback
    SDADC_CHANNEL_AVERAGE_16   = 13,   ///< Average 16 samples for each conversion end callback
    SDADC_CHANNEL_AVERAGE_32   = 14,   ///< Average 32 samples for each conversion end callback
    SDADC_CHANNEL_AVERAGE_64   = 15,   ///< Average 64 samples for each conversion end callback
} sdadc_channel_average_t;

/** Per channel polarity, valid for negative-side single-ended input only. */
typedef enum e_sdadc_channel_inversion
{
    SDADC_CHANNEL_INVERSION_OFF = 0,   ///< Do not invert conversion result
    SDADC_CHANNEL_INVERSION_ON  = 1,   ///< Invert conversion result
} sdadc_channel_inversion_t;

/** Select a formula to specify the number of conversions. The following symbols are used in the formulas:
 *    * N: Number of conversions
 *    * n: sdadc_channel_cfg_t::coefficient_n, do not set to 0 if m is 0
 *    * m: sdadc_channel_cfg_t::coefficient_m, do not set to 0 if n is 0
 *
 * Either m or n must be non-zero.
 */
typedef enum e_sdadc_channel_count_formula
{
    SDADC_CHANNEL_COUNT_FORMULA_EXPONENTIAL = 0, ///< N = 32 * (2 ^ n - 1) + m * 2 ^ n
    SDADC_CHANNEL_COUNT_FORMULA_LINEAR      = 1, ///< N = (32 * n) + m
} sdadc_channel_count_formula_t;

/** Calibration mode. */
typedef enum e_sdadc_calibration
{
    SDADC_CALIBRATION_INTERNAL_GAIN_OFFSET = 0, ///< Use internal reference to calibrate offset and gain
    SDADC_CALIBRATION_EXTERNAL_OFFSET      = 1, ///< Use external reference to calibrate offset
    SDADC_CALIBRATION_EXTERNAL_GAIN        = 2, ///< Use external reference to calibrate gain
} sdadc_calibration_t;

/** Structure to pass to the @ref adc_api_t::calibrate p_extend argument. */
typedef struct st_sdadc_calibrate_args
{
    adc_channel_t       channel;       ///< Which channel to calibrate
    sdadc_calibration_t mode;          ///< Calibration mode
} sdadc_calibrate_args_t;

/** SDADC per channel configuration. */
typedef struct st_sdadc_channel_cfg
{
    union
    {
        struct
        {
            sdadc_channel_stage_2_gain_t stage_2_gain   : 2; ///< Gain of PGA stage 2, must be 1 for single-ended input
            sdadc_channel_stage_1_gain_t stage_1_gain   : 3; ///< Gain of PGA stage 1, must be 1 for single-ended input
            sdadc_channel_oversampling_t oversampling   : 3; ///< Oversampling ratio, must be 256 in single-ended input
            uint32_t                                    : 6;
            sdadc_channel_polarity_t  polarity          : 1; ///< Polarity, valid for single-ended mode only
            sdadc_channel_input_t     input             : 1; ///< Single-ended or differential input
            uint32_t                  coefficient_m     : 5; ///< See ::sdadc_channel_count_formula_t
            uint32_t                  coefficient_n     : 3; ///< See ::sdadc_channel_count_formula_t
            sdadc_channel_average_t   average           : 4; ///< Number of samples to average for each conversion result
            sdadc_channel_inversion_t invert            : 1; ///< Whether to invert negative single-ended input
            uint32_t                                    : 2;
            sdadc_channel_count_formula_t count_formula : 1; ///< Linear or exponential formula used for number of conversions
        } pgac_setting_b;

        uint32_t pgac_setting;
    };
} sdadc_channel_cfg_t;

/** SDADC active channel configuration       */
typedef struct st_sdadc_scan_cfg
{
    uint32_t scan_mask;                ///< Channels/bits: bit 0 is ch0; bit 15 is ch15.
} sdadc_scan_cfg_t;

/** SDADC configuration extension. This extension is required and must be provided in adc_cfg_t::p_extend. */
typedef struct st_sdadc_on_adc_cfg
{
    uint8_t          conv_end_ipl;                                      ///< Conversion end interrupt priority
    IRQn_Type        conv_end_irq;                                      // Conversion end IRQ number
    sdadc_vref_src_t vref_src;                                          ///< Source of Vref (internal or external)

    /** Voltage of Vref, required for both internal and external Vref.  If Vref is from an external source, the
     * voltage must match the specified voltage within 3%. */
    sdadc_vref_voltage_t        vref_voltage;
    sdadc_channel_cfg_t const * p_channel_cfgs[SDADC_MAX_NUM_CHANNELS]; ///< Configuration for each channel, set to NULL if unused
} sdadc_extended_cfg_t;

/** ADC instance control block. DO NOT INITIALIZE.  Initialized in @ref adc_api_t::open(). */
typedef struct
{
    adc_cfg_t const * p_cfg;
    uint32_t          opened;          // Boolean to verify that the Unit has been initialized
    uint32_t          scan_mask;       // Scan mask of enabled channels.
    uint32_t          scan_cfg_mask;   // Scan mask of configured channels.
    volatile uint8_t  calib_status;    // Calibration in progress if set
    union
    {
        uint16_t results_16[SDADC_MAX_NUM_CHANNELS];
        uint32_t results_32[SDADC_MAX_NUM_CHANNELS];
    } results;
} sdadc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_sdadc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SDADC_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_SDADC_ScanCfg(adc_ctrl_t * p_ctrl, void const * const p_extend);
fsp_err_t R_SDADC_InfoGet(adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info);
fsp_err_t R_SDADC_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_SDADC_ScanGroupStart(adc_ctrl_t * p_ctrl, adc_group_mask_t group_id);
fsp_err_t R_SDADC_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_SDADC_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_SDADC_Read(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);
fsp_err_t R_SDADC_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);
fsp_err_t R_SDADC_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t const offset);
fsp_err_t R_SDADC_Calibrate(adc_ctrl_t * const p_ctrl, void const * p_extend);
fsp_err_t R_SDADC_Close(adc_ctrl_t * p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup ADC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
