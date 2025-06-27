/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_ADC_D_H
#define R_ADC_D_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "bsp_api.h"
#include "r_adc_api.h"
#include "r_adc_d_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup ADC_D
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

/** ADC_D channels mode selection */
typedef enum e_adc_d_channel_mode
{
    ADC_D_CHANNEL_MODE_SELECT = 0,     ///< Select mode
    ADC_D_CHANNEL_MODE_SCAN   = 1      ///< Scan mode
} adc_d_channel_mode_t;

/** Operation voltage mode selection */
typedef enum e_adc_d_voltage_mode
{
    ADC_D_VOLTAGE_MODE_NORMAL_1 = 0,   ///< Normal 1
    ADC_D_VOLTAGE_MODE_NORMAL_2 = 1,   ///< Normal 2
    ADC_D_VOLTAGE_MODE_LOW_1    = 2,   ///< Low voltage 1
    ADC_D_VOLTAGE_MODE_LOW_2    = 3    ///< Low voltage 2
} adc_d_voltage_mode_t;

/** Divider for Conversion Clock (fAD) */
typedef enum e_adc_d_clock_div
{
    ADC_D_CLOCK_DIV_32 = 0,            ///< ADC_D clock division ICLK/32
    ADC_D_CLOCK_DIV_16 = 1,            ///< ADC_D clock division ICLK/16
    ADC_D_CLOCK_DIV_8  = 2,            ///< ADC_D clock division ICLK/8
    ADC_D_CLOCK_DIV_4  = 3,            ///< ADC_D clock division ICLK/4
    ADC_D_CLOCK_DIV_2  = 4,            ///< ADC_D clock division ICLK/2
    ADC_D_CLOCK_DIV_1  = 5,            ///< ADC_D clock division ICLK/1
} adc_d_clock_div_t;

/** Selection trigger signal */
typedef enum e_adc_d_trigger_source
{
    ADC_D_TRIGGER_SOURCE_TAU0_TMI01          = 0,   ///< Timer channel 01 count or capture end interrupt signal
    ADC_D_TRIGGER_SOURCE_RTC_ALARM_OR_PERIOD = 2,   ///< Realtime clock interrupt signal
    ADC_D_TRIGGER_SOURCE_TML0_ITL0           = 3,   ///< 32-bit interval timer interrupt signal
    ADC_D_TRIGGER_SOURCE_ELC                 = 4,   ///< Event input from ELC
    ADC_D_TRIGGER_SOURCE_SOFTWARE            = 0xFF ///< Software trigger, this option is controlled by bit ADCS, ADCE
} adc_d_trigger_source_t;

/** Select trigger mode */
typedef enum e_adc_d_trigger_mode
{
    ADC_D_TRIGGER_MODE_NO_WAIT = 0,    ///< Trigger no-wait mode
    ADC_D_TRIGGER_MODE_WAIT    = 1     ///< Trigger wait mode
} adc_d_trigger_mode_t;

/** Select conversion operation mode */
typedef enum e_adc_d_conversion_mode
{
    ADC_D_CONVERSION_MODE_SEQUENTIAL = 0, ///< Continuous conversion mode
    ADC_D_CONVERSION_MODE_ONESHOT    = 1  ///< Single conversion mode
} adc_d_conversion_mode_t;

/** Select the upper limit and lower limit conversion result values */
typedef enum e_adc_d_boundary
{
    ADC_D_BOUNDARY_IN_RANGE     = 0,   ///< The interrupt signal (INTAD) is output in range ADLL and AULL
    ADC_D_BOUNDARY_OUT_OF_RANGE = 1    ///< The interrupt signal (INTAD) is output out of range ADLL and AULL
} adc_d_boundary_t;

/** The negative side reference voltage selection */
typedef enum e_adc_d_negative_vref
{
    ADC_D_NEGATIVE_VREF_VSS    = 0,    ///< Supplied from VSS
    ADC_D_NEGATIVE_VREF_VREFL0 = 1     ///< Supplied from VREFL0
} adc_d_negative_vref_t;

/** The positive side reference voltage selection */
typedef enum e_adc_d_positive_vref
{
    ADC_D_POSITIVE_VREF_VCC    = 0,    ///< Supplied from VSS
    ADC_D_POSITIVE_VREF_VREFH0 = 1,    ///< Supplied from VREFH0
    ADC_D_POSITIVE_VREF_IVREF  = 2     ///< Supplied from the internal reference voltage
} adc_d_positive_vref_t;

/** ADC_D channel(s) configuration */
typedef struct st_adc_d_channel_cfg
{
    adc_channel_t channel_input;
} adc_d_channel_cfg_t;

/** Extended configuration structure for ADC. */
typedef struct st_adc_d_extended_cfg
{
    adc_d_channel_mode_t    channel_mode;         ///< ADC_D channels mode setting
    adc_d_voltage_mode_t    operation_voltage;    ///< Voltage mode setting
    adc_d_clock_div_t       conversion_clockdiv;  ///< Divider for conversion clock (fAD) setting
    adc_d_trigger_source_t  trigger_source;       ///< Trigger source hardware and software setting
    adc_d_trigger_mode_t    operation_trigger;    ///< Operation mode wait/no wait setting
    adc_d_conversion_mode_t conversion_operation; ///< Sequential/one-shot conversion setting
    adc_d_boundary_t        upper_lower_bound;    ///< Upper limit and lower limit conversion setting
    adc_d_negative_vref_t   negative_vref;        ///< Negative side reference voltage setting
    adc_d_positive_vref_t   positive_vref;        ///< Positive side reference voltage setting
    uint8_t                 upper_bound_limit;    ///< Setting upper limit conversion value
    uint8_t                 lower_bound_limit;    ///< Setting lower limit conversion value
} adc_d_extended_cfg_t;

/** ADC_D instance control block. DO NOT INITIALIZE.  Initialized in @ref adc_api_t::open(). */
typedef struct st_adc_d_instance_ctrl
{
    adc_cfg_t const * p_cfg;                    // Setting the resolution of ADC_D.
    void (* p_callback)(adc_callback_args_t *); // Pointer to callback that is called when an adc_d_event_t occurs.
    void   * p_context;                         // User defined context passed into callback function.
    uint32_t initialized;                       // Initialized status of ADC_D.
    uint32_t opened;                            // Open status of ADC_D.
} adc_d_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adc_api_t g_adc_on_adc_d;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_Open(adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg);
fsp_err_t R_ADC_D_ScanCfg(adc_ctrl_t * p_ctrl, void const * const p_channel_cfg);
fsp_err_t R_ADC_D_InfoGet(adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info);
fsp_err_t R_ADC_D_ScanStart(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_D_ScanGroupStart(adc_ctrl_t * p_ctrl, adc_group_mask_t group_id);
fsp_err_t R_ADC_D_ScanStop(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_D_StatusGet(adc_ctrl_t * p_ctrl, adc_status_t * p_status);
fsp_err_t R_ADC_D_Read(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data);
fsp_err_t R_ADC_D_Read32(adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data);
fsp_err_t R_ADC_D_Close(adc_ctrl_t * p_ctrl);
fsp_err_t R_ADC_D_OffsetSet(adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset);
fsp_err_t R_ADC_D_Calibrate(adc_ctrl_t * const p_ctrl, void const * p_extend);
fsp_err_t R_ADC_D_CallbackSet(adc_ctrl_t * const          p_api_ctrl,
                              void (                    * p_callback)(adc_callback_args_t *),
                              void * const                p_context,
                              adc_callback_args_t * const p_callback_memory);

fsp_err_t R_ADC_D_SnoozeModePrepare(adc_ctrl_t * const p_ctrl);
fsp_err_t R_ADC_D_SnoozeModeExit(adc_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup ADC_D)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
