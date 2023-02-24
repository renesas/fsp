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

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_SENSE_INDUCTION
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_SENSE_INDUCTION_H
#define RM_MOTOR_SENSE_INDUCTION_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <math.h>

#include "rm_motor_angle_api.h"
#include "rm_motor_sense_induction_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MOTOR_SENSE_INDUCTION_AVERAGE    (4U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum  e_motor_sense_induction_loop
{
    MOTOR_SENSE_INDUCTION_LOOP_SPEED    = 0, ///< Speed control mode
    MOTOR_SENSE_INDUCTION_LOOP_POSITION = 1  ///< Position control mode
} motor_sense_induction_loop_t;

typedef enum  e_motor_sense_induction_calibration
{
    MOTOR_SENSE_INDUCTION_CALIBRATION_DISABLE = 0, ///< Disable calibration
    MOTOR_SENSE_INDUCTION_CALIBRATION_ENABLE  = 1  ///< Enable calibration
} motor_sense_induction_calibration_t;

typedef enum e_motor_sense_induction_mode
{
    MOTOR_SENSE_INDUCTION_MODE_INIT = 0, ///< Initialize mode (Start status)
    MOTOR_SENSE_INDUCTION_MODE_BOOT,     ///< Boot mode (Angle adjustment status)
    MOTOR_SENSE_INDUCTION_MODE_DRIVE     ///< Drive mode (Normal work status)
} motor_sense_induction_mode_t;

typedef struct st_motor_sense_induction_extended_cfg
{
    uint8_t  u1_speed_detection_count;                 ///< Speed detection count
    uint8_t  u1_get_timing_count;                      ///< Data acquisition decimation count
    float    f_current_frequency;                      ///< Frequency of current control [kHz]
    uint16_t u2_signal_error_limit;                    ///< Limit of the first and second data comparison results
    float    f_speed_lpf;                              ///< Low-pass filter coefficient for speed
    float    f_reference_voltage;                      ///< Supplyed reference voltage [V]
    float    f_ad_conversion_scale;                    ///< A/D conversion scale
    float    f_openloop_speed_rpm;                     ///< Openloop speed [rpm]
    float    f_openloop_id_ref;                        ///< Openloop d-axis current [A]
    uint16_t u2_angle_adjustment_time;                 ///< Times of induction sensor angle adjustment
    uint8_t  u1_induction_polepairs;                   ///< Pole pairs of induction sensor
    uint8_t  u1_motor_polepairs;                       ///< Pole pairs of motor

    motor_sense_induction_loop_t        e_loop_mode;   ///< Selection loop mode (Speed or Position)
    motor_sense_induction_calibration_t e_calibration; ///< Selection of calibration behavior
} motor_sense_induction_extended_cfg_t;

/* Variables used to correct signal */
typedef struct st_motor_sense_induction_correct_data
{
    float f_maximum[2];                ///< Sensor output value at maximum signal
    float f_maximum_average;           ///< Average of two maximum values
    float f_maximum_phase[2];          ///< Angle at maximum signal
    float f_maximum_phase_average;     ///< Average of angle at maximum signal
    float f_minimum[2];                ///< Minimum value of acquired signal
    float f_minimum_average;           ///< Average of two minimum values
    float f_minimum_phase[2];          ///< Angle at minimum signal
    float f_minimum_phase_average;     ///< Average of angle at minimum signal
    float f_integral[2];               ///< Integrated value
    float f_integral_average;          ///< Average of integrated value

    /* Variable used to correct temporary */
    float f_temp_maximum;              ///< Temporary save for maximum value search
    float f_temp_maximum_phase;        ///< Temporary save for maximum value search
    float f_temp_minimum;              ///< Temporary save for minimum value search
    float f_temp_minimum_phase;        ///< Temporary save for minimum value search
    float f_temp_integral;             ///< Temporary save for integrated value
} motor_sense_induction_correct_data_t;

/* Speed and position(angle) information */
typedef struct st_motor_sense_induction_information
{
    float f_position_radian;           /* Value of induction sensor position [rad] (mechanical) */
    float f_speed_radian;              /* Value of induction sensor speed [rad] (mechanical) */
    float f_angle_openloop;            /* Value of induction sensor position during open loop[rad] (mechanical) */
    float f_speed_openloop;            /* Value of induction sensor speed during open loop[rad] (mechanical) */
} motor_sense_induction_information_t;

typedef struct st_motor_sense_induction_instance_ctrl
{
    uint32_t open;

    float f_angle_radian;                         ///< Current rotor angle[rad]
    float f_adc_scaling;                          ///< A/D scaling

    float f_sense_sin_adc;                        ///< Sensed A/D sin data
    float f_sense_cos_adc;                        ///< Sensed A/D cos data

    uint8_t  u1_correct_status;                   ///< Error correction completion flag
    uint8_t  u1_openloop_trigger;                 ///< Open loop control trigger
    uint8_t  u1_sensor_count;                     ///< Correction data acquisition counter
    uint8_t  u1_calibration_status;               ///< Error calibration process status
    uint8_t  u1_calibration_count;                ///< Auxiliary counter for error calibration processing
    uint16_t u2_signal_maximum_difference;        ///< Comparison between sensor outputs
    uint8_t  u1_speed_calculate_counter;          ///< Speed detection timing adjustment counter
    uint8_t  u1_angle_adjust_status;              ///< Induction sensor angle adjustment status
    uint16_t u2_get_adc_count;                    ///< Data acquisition timing adjustment counter
    uint16_t u2_angle_adjustment_count;           ///< Counter of induction sensor angle adjustment
    uint8_t  u1_angle_adjustment_flag;            ///< Flag of induction sensor angle adjustment
    int16_t  s2_cycle_counter;                    ///< Cycle counter of induction sensor
    float    f_pre_position_radian;               ///< Angle information for calculating position information

    motor_sense_induction_correct_data_t sin;     ///< Data to correction about sin
    motor_sense_induction_correct_data_t cos;     ///< Data to correction about cos

    /* Variable used to correct phase of sensor output signal */
    float f_add_cos_sin_maximum;                  ///< Sensor output value at maximum cos + sin signal measurement
    float f_add_cos_sin_minimum;                  ///< Sensor output value at minimum cos + sin signal measurement
    float f_sub_cos_sin_maximum;                  ///< Sensor output value at maximum cos - sin signal measurement
    float f_sub_cos_sin_minimum;                  ///< Sensor output value at minimum cos - sin signal measurement

    /* Sensor calibration parameters */
    float f_sin_offset;                           ///< Offset of sin signal for sensor output
    float f_cos_offset;                           ///< Offset of cos signal for sensor output
    float f_sin_gain;                             ///< Gain correction coefficient of sensor output sin signal
    float f_cos_gain;                             ///< Gain correction coefficient of sensor output cos signal
    float f_induction_phase_offset;               ///< Offset of induction sensor and motor position
    float f_add_cos_sin_gain;                     ///< Phase correction coefficient of sensor output cos + sin signal
    float f_sub_cos_sin_gain;                     ///< Phase correction coefficient of sensor output cos - sin signal

    motor_sense_induction_information_t current;  ///< Current speed and angle
    motor_sense_induction_information_t previous; ///< Previous speed and angle
    float f_position_offset_radian;               ///< Value of induction sensor offset [rad] (mechanical)

    float    f_current_ctrl_period;               ///< Period of current control
    float    f_openloop_speed;                    ///< Openloop speed;
    uint16_t u2_adc_sample_count;                 ///< Data acquisition decimation count
    float    f_calibration_period;
    float    f_get_adc_resolution;

    float f_inverse_polepairs;                    ///< Inverse of pole pairs of induction sensor

    motor_sense_induction_loop_t e_loop_mode;     ///< Selected loop mode (Speed or Position)
    motor_sense_induction_mode_t e_move_mode;

    motor_angle_cfg_t const * p_cfg;
} motor_sense_induction_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_angle_api_t g_motor_angle_on_motor_sense_induction;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_Open(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_Close(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_Reset(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_InternalCalculate(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_AngleSpeedGet(motor_angle_ctrl_t * const p_ctrl,
                                                 float * const              p_angle,
                                                 float * const              p_speed,
                                                 float * const              p_phase_err);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_AngleAdjust(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_EncoderCyclic(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_CyclicProcess(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_SensorDataSet(motor_angle_ctrl_t * const    p_ctrl,
                                                 motor_angle_ad_data_t * const p_ad_data);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_InfoGet(motor_angle_ctrl_t * const         p_ctrl,
                                           motor_angle_encoder_info_t * const p_info);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_CorrectReset(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_ErrorGet(motor_angle_ctrl_t * const p_ctrl, motor_angle_error_t * const p_error);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_ParameterUpdate(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * p_cfg);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_CurrentSet(motor_angle_ctrl_t * const              p_ctrl,
                                              motor_angle_current_t * const           p_st_current,
                                              motor_angle_voltage_reference_t * const p_st_voltage);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_SpeedSet(motor_angle_ctrl_t * const p_ctrl,
                                            float const                speed_ctrl,
                                            float const                damp_speed);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_FlagPiCtrlSet(motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi);

fsp_err_t RM_MOTOR_SENSE_INDUCTION_EstimatedComponentGet(motor_angle_ctrl_t * const p_ctrl,
                                                         float * const              p_ed,
                                                         float * const              p_eq);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_SENSE_INDUCTION_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SENSE_INDUCTION)
 **********************************************************************************************************************/
