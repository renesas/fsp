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

typedef struct st_motor_sense_hall_extended_cfg
{
    bsp_io_port_pin_t port_hall_sensor_u;                       ///< Hall U-signal input port     BSP_IO_PORT_12_PIN_04
    bsp_io_port_pin_t port_hall_sensor_v;                       ///< Hall V-signal input port     BSP_IO_PORT_12_PIN_05
    bsp_io_port_pin_t port_hall_sensor_w;                       ///< Hall W-signal input port     BSP_IO_PORT_11_PIN_01

    uint8_t u1_hall_pattern[MOTOR_SENSE_HALL_SPEED_COUNTS + 1]; ///< The order of hall signal pattern

    float f_pwm_carrier_freq;                                   ///< PWM carrier frequency        20.0kHz
    float f_angle_correct;                                      ///< Coefficent to correct angle  0.4

    uint16_t u2_default_counts;                                 ///< Default counts for period of hall signal to reset
    uint16_t u2_maximum_period;                                 ///< Maximum counts of hall signal period

    uint8_t u1_hall_polepairs;                                  ///< Hall pole pairs
} motor_sense_hall_extended_cfg_t;

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
