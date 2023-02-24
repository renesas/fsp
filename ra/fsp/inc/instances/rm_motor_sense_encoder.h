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
 * @addtogroup MOTOR_SENSE_ENCODER
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_SENSE_ENCODER_H
#define RM_MOTOR_SENSE_ENCODER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <math.h>

#include "rm_motor_angle_api.h"
#include "rm_motor_sense_encoder_cfg.h"
#include "r_timer_api.h"
#include "r_gpt.h"

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
 #include "r_external_irq_api.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MOTOR_SENSE_ENCODER_AVERAGE    (4U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum  e_motor_sense_encoder_loop
{
    MOTOR_SENSE_ENCODER_LOOP_SPEED    = 0, ///< Speed control mode
    MOTOR_SENSE_ENCODER_LOOP_POSITION = 1  ///< Position control mode
} motor_sense_encoder_loop_t;

typedef enum e_motor_sense_encoder_mode
{
    MOTOR_SENSE_ENCODER_MODE_INIT = 0, ///< Initialize mode (Start status)
    MOTOR_SENSE_ENCODER_MODE_BOOT,     ///< Boot mode (Angle adjustment status)
    MOTOR_SENSE_ENCODER_MODE_DRIVE     ///< Drive mode (Normal work status)
} motor_sense_encoder_mode_t;

typedef struct st_motor_sense_encoder_motor_parameter
{
    uint16_t u2_mtr_pp;                ///< Pole pairs
    float    f4_mtr_r;                 ///< Resistance [ohm]
    float    f4_mtr_ld;                ///< Inductance for d-axis [H]
    float    f4_mtr_lq;                ///< Inductance for q-axis [H]
    float    f4_mtr_m;                 ///< Magnet flux [Wb]
    float    f4_mtr_j;                 ///< Rotor inertia [kgm^2]
} motor_sense_encoder_motor_parameter_t;

typedef struct st_motor_sense_encoder_parameter
{
    motor_sense_encoder_angle_adjust_t u1_encoder_angle_adj_status; ///< Rotor angle adjustment status

    ///< Encoder angle adjustment status
    uint16_t u2_encoder_angle_adj_time;                             ///< Time of encoder angle adjustment
    uint16_t u2_encoder_angle_adj_count;                            ///< Counter of encoder angle adjustment
    uint32_t u2_encoder_pre_phase_count;                            ///< Previous value of encoder phase counter
    uint32_t u4_encoder_timer_capture;                              ///< Current capture counter value
    uint32_t u4_encoder_timer_pre_capture;                          ///< Previous capture counter value
    uint16_t u2_encoder_timer_cnt_num;                              ///< u4_encoder_timer_cnt_buff index
    int16_t  s2_encoder_cpr;                                        ///< Encoder counts per revolution (mechanical)
    int32_t  s4_encoder_timer_count_buff[MOTOR_SENSE_ENCODER_AVERAGE];

    ///< Stored width of captured pulses
    int32_t s4_encoder_pulse_width;                                 ///< Stored captured pulse width
    int32_t s4_encoder_pulse_width_buff;                            ///< Stored captured pulse width buffer
    int32_t s4_encoder_pulse_width_sum;                             ///< Sum of last 4 pulse width
    int32_t s4_encoder_angle_count;                                 ///< Counter of encoder position
    float   f4_encoder_angle_difference;                            ///< Angle of encoder 1 pulse width
    float   f4_encoder_cpr_inverse;                                 ///< Inverse number of encoder counts per revolution (mechanical)
    float   f4_encoder_speed_pre_rad;                               ///< Encoder speed of previous edge detection
    float   f4_encoder_speed_rad;                                   ///< Encoder speed of current edge detection [rad/s] (mechanical)
    float   f4_encoder_position_rad;                                ///< Encoder rotor position angle [radian] (mechanical)
} motor_sense_encoder_parameter_t;

typedef struct st_motor_sense_encoder_highspeed
{
    uint8_t  u1_encoder_position_speed_calc_mode;      ///< Position and speed calculation mode
    uint8_t  u1_encoder_interrupt_on_flag;             ///< Flag of encoder interrupt
    uint8_t  u1_encoder_position_speed_count;          ///< Change counter
    uint16_t u2_encoder_highspeed_pre_phase_count;     ///< Previous value of encoder phase counter for high speed mode
    int32_t  s4_encoder_highspeed_angle_count;         ///< Counter of encoder position for high speed mode
    float    f4_encoder_highspeed_position_rad;        ///< Encoder rotor position angle [radian] (mechanical)
    float    f4_encoder_highspeed_previous_rad;        ///< Previous value of encoder rotor position angle [radian] (mechanical)
    float    f4_encoder_highspeed_speed_rad;           ///< Encoder speed of current edge detection [rad/s] (mechanical)
    float    f4_encoder_highspeed_speed_pre_rad;       ///< Previous value of encoder speed of current edge detection
    float    f4_encoder_highspeed_sw_speed_rad;        ///< Toggle speed for high speed mode [rad/s] (mechanical)
    float    f4_encoder_highspeed_sw_speed_margin_rad; ///< Margin of toggle speed for high speed mode [rad/s] (mechanical)
} motor_sense_encoder_highspeed_t;

typedef struct st_motor_sense_encoder_hall
{
    uint8_t u1_hall_signal;            ///< Hall signal
    uint8_t u1_hall_pre_signal;        ///< Previous value of hall signal
    uint8_t u1_hall_interrupt_flag;    ///< Flag of hall interrupt
    float   f4_hall_angle_rad;         ///< Using hall signal to set rotor initial angle [rad]
} motor_sense_encoder_hall_t;

typedef struct st_motor_sense_encoder_config
{
    float   f_carrier_frequency;
    uint8_t u1_interrupt_decimation;

    uint16_t u2_cpr;                   ///< Counter per rotation
    uint16_t u2_angle_adjust_time;     ///< Angle adjustment time [msec]
    uint32_t u4_zero_speed_count;      ///< Pulse counts to judge zero speed
    float    f_speed_timer_frequency;  ///< Timer frequnecy of speed calculation timer [MHz]

    float f_occupancy_time;
    float f_carrier_time;
    float f_process_time;

    uint16_t u2_highspeed_change_margin_rpm;
    float    f_highspeed_lpf_parameter;

    uint8_t u1_position_speed_change_counts;
} motor_sense_encoder_config_t;

typedef struct st_motor_sense_encoder_extended_cfg
{
    /* Encoder counter timer instance */
    timer_instance_t const * p_timer_instance;
    timer_instance_t const * p_input_capture_instance;

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL

    /* Instances of Hall signal interrupts */
    external_irq_instance_t const * p_u_hall_irq_instance; ///< U phase Hall Interrupt
    external_irq_instance_t const * p_v_hall_irq_instance; ///< V phase Hall Interrupt
    external_irq_instance_t const * p_w_hall_irq_instance; ///< W phase Hall Interrupt

    bsp_io_port_pin_t u_phase_port;
    bsp_io_port_pin_t v_phase_port;
    bsp_io_port_pin_t w_phase_port;
#endif

    float f_current_ctrl_period;       ///< Period of current control
    float f_speed_ctrl_period;         ///< Period of speed control

    motor_sense_encoder_loop_t            loop_mode;
    motor_sense_encoder_config_t          encoder_config;
    motor_sense_encoder_motor_parameter_t st_motor_params;
} motor_sense_encoder_extended_cfg_t;

typedef struct st_motor_sense_encoder_instance_ctrl
{
    uint32_t open;

    uint8_t u1_direction;
    float   f_speed_rad;

    motor_sense_encoder_loop_t e_loop_mode;

    motor_sense_encoder_mode_t e_move_mode;

    motor_sense_encoder_parameter_t st_encoder_parameter;
    motor_sense_encoder_highspeed_t st_encoder_highspeed;
    motor_sense_encoder_hall_t      st_encoder_hall;

    timer_instance_t const  * p_timer;
    timer_instance_t const  * p_input_capture;
    motor_angle_cfg_t const * p_cfg;

    /* input capture callback */
    timer_callback_args_t input_capture_args;

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL

    /* External IRQ callback (Hall interrupt) */
    external_irq_callback_args_t hall_interrupt_args;
#endif
} motor_sense_encoder_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_angle_api_t g_motor_angle_on_motor_encoder;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_Open(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_SENSE_ENCODER_Close(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_ENCODER_Reset(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_ENCODER_InternalCalculate(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_ENCODER_AngleSpeedGet(motor_angle_ctrl_t * const p_ctrl,
                                               float * const              p_angle,
                                               float * const              p_speed,
                                               float * const              p_phase_err);

fsp_err_t RM_MOTOR_SENSE_ENCODER_AngleAdjust(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_ENCODER_EncoderCyclic(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_ENCODER_InfoGet(motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info);

fsp_err_t RM_MOTOR_SENSE_ENCODER_ParameterUpdate(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * p_cfg);

fsp_err_t RM_MOTOR_SENSE_ENCODER_CurrentSet(motor_angle_ctrl_t * const              p_ctrl,
                                            motor_angle_current_t * const           p_st_current,
                                            motor_angle_voltage_reference_t * const p_st_voltage);

fsp_err_t RM_MOTOR_SENSE_ENCODER_SpeedSet(motor_angle_ctrl_t * const p_ctrl,
                                          float const                speed_ctrl,
                                          float const                damp_speed);

fsp_err_t RM_MOTOR_SENSE_ENCODER_FlagPiCtrlSet(motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi);

fsp_err_t RM_MOTOR_SENSE_ENCODER_EstimatedComponentGet(motor_angle_ctrl_t * const p_ctrl,
                                                       float * const              p_ed,
                                                       float * const              p_eq);

fsp_err_t RM_MOTOR_SENSE_ENCODER_CyclicProcess(motor_angle_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_SENSE_ENCODER_SensorDataSet(motor_angle_ctrl_t * const    p_ctrl,
                                               motor_angle_ad_data_t * const p_ad_data);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_SENSE_ENCODER_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SENSE_ENCODER)
 **********************************************************************************************************************/
