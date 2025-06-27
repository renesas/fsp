/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_SENSE_HALL
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_SENSE_HALL_H
#define RM_MOTOR_SENSE_HALL_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_motor_sense_hall_cfg.h"
#include "rm_motor_angle_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MOTOR_SENSE_HALL_SPEED_COUNTS    (6)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_motor_sense_hall_direction
{
    MOTOR_SENSE_HALL_DIRECTION_CW  = 1, ///< Rotation direction clockwise
    MOTOR_SENSE_HALL_DIRECTION_CCW = 0, ///< Rotation direction counter clockwise
} motor_sense_hall_direction_t;

typedef enum e_motor_sense_hall_signal_status
{
    MOTOR_SENSE_HALL_SIGNAL_STATUS_INITIAL  = 1, ///< Hall signal isn't captured. (Initial)
    MOTOR_SENSE_HALL_SIGNAL_STATUS_CAPTURED = 0, ///< Hall signal is captured.
} motor_sense_hall_signal_status_t;

/** This structure is provided to receive speed information. */
typedef struct st_motor_sense_hall_input
{
    float f4_ref_speed_rad_ctrl;       ///< Speed Reference [rad/sec]
} motor_sense_hall_input_t;

/** Optional Motor sense hall extension data structure. */
typedef struct st_motor_sense_hall_extended_cfg
{
    bsp_io_port_pin_t port_hall_sensor_u;                       ///< Hall U-signal input port
    bsp_io_port_pin_t port_hall_sensor_v;                       ///< Hall V-signal input port
    bsp_io_port_pin_t port_hall_sensor_w;                       ///< Hall W-signal input port

    uint8_t u1_hall_pattern[MOTOR_SENSE_HALL_SPEED_COUNTS + 1]; ///< The order of hall signal pattern

    float f_pwm_carrier_freq;                                   ///< PWM carrier frequency (or Decimated frequency at decimation of current process)
    float f_angle_correct;                                      ///< Coefficient to correct angle

    uint8_t  u1_trigger_hall_signal_count;                      ///< Rotation counts to wait the stability
    float    f4_target_pseudo_speed_rad;                        ///< Target value for pseudo speed estimates [radian/second]
    float    f4_reach_time_msec;                                ///< Time until the pseudo speed estimate reaches the target value [msec]
    uint16_t u2_trigger_carrier_count;                          ///< Estimated speed 0 until this trigger

    uint16_t u2_default_counts;                                 ///< Default counts for period of hall signal to reset
    uint16_t u2_maximum_period;                                 ///< Maximum counts of hall signal period

    uint8_t u1_hall_polepairs;                                  ///< Hall pole pairs

    float f4_start_speed_rad;                                   ///< Speed to judge start [radian/second]
} motor_sense_hall_extended_cfg_t;

/** SENSE_HALL control block. DO NOT INITIALIZE. Initialization occurs when @ref motor_angle_api_t::open is called. */
typedef struct st_motor_sense_hall_instance_ctrl
{
    uint32_t open;

    uint8_t u1_hall_signal;                                 ///< Hall signal pattern
    uint8_t u1_last_hall_signal;                            ///< Last hall signal pattern
    motor_sense_hall_direction_t direction;                 ///< Rotation direction
    motor_sense_hall_direction_t last_direction;            ///< Last rotation direction
    uint16_t u2_carrier_count;                              ///< Carrier count
    uint16_t u2_hall_period[MOTOR_SENSE_HALL_SPEED_COUNTS]; ///< Array of carrier count to calculate 2PI
    uint8_t  u1_period_counter;                             ///< Counter for above array
    float    f_angle;                                       ///< Rotor angle [radian]
    float    f_angle_per_count;                             ///< Angle per 1 count
    float    f_calculated_speed;                            ///< Calculated speed [radian/second]

    /* For startup */
    uint8_t u1_hall_signal_memory;                          ///< Memorized hall signal at startup
    motor_sense_hall_signal_status_t hall_signal_status;    ///< Hall signal status
    uint8_t                  u1_hall_signal_count;          ///< Rotation counter
    float                    f4_pseudo_speed_rad;           ///< Pseudo speed used for startup [radian/second]
    float                    f4_add_pseudo_speed_rad;       ///< Step of pseudo speed to update [radian/second]
    uint16_t                 u2_startup_carrier_count;      ///< Counter of carrier interrupt for startup
    motor_sense_hall_input_t st_input;                      ///< Input parameter structure

    uint8_t u1_startup_flag;                                ///< Flag for startup

    motor_angle_cfg_t const * p_cfg;
} motor_sense_hall_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_angle_api_t g_motor_angle_on_motor_sense_hall;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_Open(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_SENSE_HALL_Close(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_HALL_Reset(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_HALL_CurrentSet(motor_angle_ctrl_t * const              p_ctrl,
                                         motor_angle_current_t * const           p_st_current,
                                         motor_angle_voltage_reference_t * const p_st_voltage);

fsp_err_t RM_MOTOR_SENSE_HALL_SpeedSet(motor_angle_ctrl_t * const p_ctrl, float const speed_ctrl,
                                       float const damp_speed);

fsp_err_t RM_MOTOR_SENSE_HALL_FlagPiCtrlSet(motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi);

fsp_err_t RM_MOTOR_SENSE_HALL_AngleSpeedGet(motor_angle_ctrl_t * const p_ctrl,
                                            float * const              p_angle,
                                            float * const              p_speed,
                                            float * const              p_phase_err);

fsp_err_t RM_MOTOR_SENSE_HALL_EstimatedComponentGet(motor_angle_ctrl_t * const p_ctrl,
                                                    float * const              p_ed,
                                                    float * const              p_eq);

fsp_err_t RM_MOTOR_SENSE_HALL_ParameterUpdate(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * p_cfg);

fsp_err_t RM_MOTOR_SENSE_HALL_InternalCalculate(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_HALL_AngleAdjust(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_HALL_EncoderCyclic(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_HALL_InfoGet(motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_SENSE_HALL_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SENSE_HALL)
 **********************************************************************************************************************/
