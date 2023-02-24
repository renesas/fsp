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
 * @addtogroup MOTOR_120_CONTROL_SENSORLESS
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_120_CONTROL_SENSORLESS_H
#define RM_MOTOR_120_CONTROL_SENSORLESS_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_three_phase_api.h"
#include "rm_motor_120_driver_api.h"
#include "rm_motor_120_control_sensorless_cfg.h"
#include "rm_motor_120_control_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MOTOR_120_CONTROL_SENSORLESS_TIMES    (6U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Draw in a initial position */
typedef enum e_motor_120_control_sensorless_draw_in_position
{
    MOTOR_120_CONTROL_SENSORLESS_DRAW_IN_POSITION_INIT     = 0, ///< Inital parameter
    MOTOR_120_CONTROL_SENSORLESS_DRAW_IN_POSITION_1ST_TIME = 1, ///< Draw in a initial position of the 1st time
    MOTOR_120_CONTROL_SENSORLESS_DRAW_IN_POSITION_2ND_TIME = 2, ///< Draw in a initial position of the 2nd time
} motor_120_control_sensorless_draw_in_position_t;

/** Pattern change */
typedef enum e_motor_120_sensorless_pattern_change_flag
{
    MOTOR_120_CONTROL_SENSORLESS_PATTERN_CHANGE_FLAG_CLEAR = 0, ///< Inital parameter
    MOTOR_120_CONTROL_SENSORLESS_PATTERN_CHANGE_FLAG_SET   = 1, ///< Voltage pattern change
} motor_120_control_sensorless_pattern_change_flag_t;

/** Extended configurations for motor 120 control sensorless */
typedef struct st_motor_120_control_sensorless_extended_cfg
{
    float    f4_stop_bemf;                                             ///< Value of stop motor BEMF (U+V+W)
    float    f4_max_boot_v;                                            ///< Max output voltage for boot mode (V)
    float    f4_carrier_freq;                                          ///< Carrier wave frequency (kHz)
    int32_t  s4_angle_shift_adjust;                                    ///< Adjusting angle
    float    f4_boot_ref_v;                                            ///< Voltage reference when zero speed (V)
    uint32_t u4_v_up_time;                                             ///< Voltage lamping time
    uint32_t u4_v_const_time;                                          ///< Voltage constant adjust time value (ms)
    int32_t  s4_ol_start_rpm;                                          ///< Start speed (rpm)
    int32_t  s4_ol_mode1_change_rpm;                                   ///< To mode2 change speed (rpm)
    int32_t  s4_ol_mode2_change_rpm;                                   ///< To mode3 change speed (rpm)
    float    f4_ol_start_refv;                                         ///< Start reference voltage (V)
    float    f4_ol_mode1_rate_rpm;                                     ///< Increase rate of reference speed (rpm/control period)
    float    f4_ol_mode2_rate_refv;                                    ///< Increase rate of reference voltage (v/control period)
    float    f4_ol_mode2_rate_rpm;                                     ///< Increase rate of reference speed (rpm/control period)
    float    f4_ol_mode3_rate_refv;                                    ///< Increase rate of reference voltage (v/control period)
    float    f4_ol_mode3_max_refv;                                     ///< Openloop max voltage (V)

    motor_120_driver_instance_t const * p_motor_120_driver_instance;   ///< Motor 120 driver access module
    timer_instance_t const            * p_speed_cyclic_timer_instance; ///< Cyclic process of speed control timer module
    timer_instance_t const            * p_speed_calc_timer_instance;   ///< Speed calculate timer module
} motor_120_control_sensorless_extended_cfg_t;

/** 120 control sensorless instance control block */
typedef struct st_motor_120_control_sensorless_instance_ctrl
{
    uint32_t open;                                                          ///< Used to determine if the channel is configured

    motor_120_control_status_t             active;                          ///< Flag to set active/inactive the motor 120 control
    motor_120_control_run_mode_t           run_mode;                        ///< Drive mode
    motor_120_control_timeout_error_flag_t timeout_error_flag;              ///< Timeout error status
    motor_120_control_pattern_error_flag_t pattern_error_flag;              ///< Bemf pattern error status

    motor_120_control_rotation_direction_t direction;                       ///< Rotational direction (0:CW ,1:CCW)
    float    f4_ol_pattern_set_calc;                                        ///< Counts to change timing of open loop pattern
    float    f4_speed_calc_base;                                            ///< Base counts to calculate rotation speed
    float    f_rpm2rad;                                                     ///< Translate value to radian/second to rpm
    float    f4_v_ref;                                                      ///< Voltage reference (output of speed PI control)
    uint32_t u4_pwm_duty;                                                   ///< PWM duty
    float    f4_ref_speed_rad;                                              ///< Motor speed reference
    float    f4_ref_speed_rad_ctrl;                                         ///< Motor speed reference for speed PI control
    float    f4_speed_rad;                                                  ///< Motor speed
    uint32_t u4_cnt_speed_pi;                                               ///< Counter for period of speed PI control
    motor_120_control_wait_stop_flag_t flag_wait_stop;                      ///< Flag for waiting for motor stop
    float    f4_vn_ad;                                                      ///< Neutral voltage
    uint32_t u4_cnt_adj_v;                                                  ///< Voltage lamping count adjustment
    motor_120_control_sensorless_draw_in_position_t flag_draw_in;           ///< Status of draw in a initial position
    motor_120_driver_phase_pattern_t                v_pattern;              ///< Voltage pattern
    uint32_t u4_v_pattern_num;                                              ///< Selecting pattern number for openloop drive
    uint32_t u4_bemf_signal;                                                ///< Pattern of BEMF
    uint32_t u4_pre_bemf_signal;                                            ///< Previous pattern of BEMF
    motor_120_control_sensorless_pattern_change_flag_t flag_pattern_change; ///< Pattern change flag
    motor_120_control_speed_ref_t   flag_speed_ref;                         ///< Speed reference flag
    motor_120_control_voltage_ref_t flag_voltage_ref;                       ///< Voltage reference flag
    uint32_t u4_ol_signal;                                                  ///< Pattern of BEMF
    uint32_t u4_ol_pattern_set;                                             ///< Openloop frequency
    uint32_t u4_cnt_ol_pattern_set;                                         ///< Counter for openloop pattern change
    uint32_t u4_cnt_timeout;                                                ///< Counter for timeout error
    uint32_t u4_bemf_timer_cnt;                                             ///< Value of timer counter
    uint32_t u4_pre_bemf_timer_cnt;                                         ///< Previous value of timer counter
    int32_t  s4_timer_cnt_ave;                                              ///< Counts for 360 degrees
    uint32_t u4_timer_cnt_buf[MOTOR_120_CONTROL_SENSORLESS_TIMES];          ///< Counts for 60 degrees
    uint32_t u4_timer_cnt_num;                                              ///< Array element number before 360 degrees
    uint32_t u4_cnt_carrier;                                                ///< Counter for carrier interrupt
    uint32_t u4_pre_cnt_carrier;                                            ///< Previous carrier interrupt count
    uint32_t u4_angle_shift_cnt;                                            ///< Shift degrees count

    float f4_pi_ctrl_err;                                                   ///< PI control error
    float f4_pi_ctrl_refi;                                                  ///< PI control buffer of integral term

    motor_120_control_cfg_t const * p_cfg;                                  ///< Pointer of configuration structure

    timer_direction_t timer_direction;                                      ///< Hold timer direction

    /* cyclic timer callback */
    timer_callback_args_t timer_args;                                       ///< For call timer callbackSet function
} motor_120_control_sensorless_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in interface API structure for this instance. */
extern const motor_120_control_api_t g_motor_120_control_on_motor_120_control_sensorless;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_Open(motor_120_control_ctrl_t * const      p_ctrl,
                                               motor_120_control_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_Close(motor_120_control_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_Run(motor_120_control_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_Stop(motor_120_control_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_Reset(motor_120_control_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_SpeedSet(motor_120_control_ctrl_t * const p_ctrl, float const speed_rpm);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_SpeedGet(motor_120_control_ctrl_t * const p_ctrl, float * const p_speed_rpm);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_CurrentGet(motor_120_control_ctrl_t * const          p_ctrl,
                                                     motor_120_driver_current_status_t * const p_current_status);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_WaitStopFlagGet(motor_120_control_ctrl_t * const           p_ctrl,
                                                          motor_120_control_wait_stop_flag_t * const p_flag);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_TimeoutErrorFlagGet(motor_120_control_ctrl_t * const               p_ctrl,
                                                              motor_120_control_timeout_error_flag_t * const p_timeout_error_flag);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_PatternErrorFlagGet(motor_120_control_ctrl_t * const               p_ctrl,
                                                              motor_120_control_pattern_error_flag_t * const p_pattern_error_flag);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_VoltageRefGet(motor_120_control_ctrl_t * const        p_ctrl,
                                                        motor_120_control_voltage_ref_t * const p_voltage_ref);

fsp_err_t RM_MOTOR_120_CONTROL_SENSORLESS_ParameterUpdate(motor_120_control_ctrl_t * const      p_ctrl,
                                                          motor_120_control_cfg_t const * const p_cfg);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_120_CONTROL_SENSORLESS_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_CONTROL_SENSORLESS)
 **********************************************************************************************************************/
