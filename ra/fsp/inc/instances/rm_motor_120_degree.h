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
 * @addtogroup MOTOR_120_DEGREE
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_120_DEGREE_H
#define RM_MOTOR_120_DEGREE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_motor_120_degree_cfg.h"
#include "rm_motor_api.h"
#include "rm_motor_120_control_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Control state */
typedef enum  e_motor_120_degree_ctrl_status
{
    MOTOR_120_DEGREE_CTRL_STATUS_STOP  = 0, ///< Stop mode
    MOTOR_120_DEGREE_CTRL_STATUS_RUN   = 1, ///< Run mode
    MOTOR_120_DEGREE_CTRL_STATUS_ERROR = 2, ///< Error mode
} motor_120_degree_ctrl_status_t;

/** Control event */
typedef enum  e_motor_120_degree_ctrl_event
{
    MOTOR_120_DEGREE_CTRL_EVENT_STOP  = 0, ///< Stop event
    MOTOR_120_DEGREE_CTRL_EVENT_RUN   = 1, ///< Run event
    MOTOR_120_DEGREE_CTRL_EVENT_ERROR = 2, ///< Error event
    MOTOR_120_DEGREE_CTRL_EVENT_RESET = 3  ///< Reset event
} motor_120_degree_ctrl_event_t;

/** Statemachine structure for motor 120 degree */
typedef struct  rm_motor_120_degree_statemachine
{
    motor_120_degree_ctrl_status_t status;        ///< The current system status
    motor_120_degree_ctrl_status_t status_next;   ///< The next system status
    motor_120_degree_ctrl_event_t  current_event; ///< The current event index

    uint16_t u2_error_status;                     ///< The error information
} motor_120_degree_statemachine_t;

/** Extended configurations for motor 120 degree */
typedef struct st_motor_120_degree_extended_cfg
{
    motor_120_control_instance_t const * p_motor_120_control_instance; ///< 120 degree control Instance

    float f_overcurrent_limit;                                         ///< Over-current limit (A)
    float f_overvoltage_limit;                                         ///< Over-voltage limit (V)
    float f_overspeed_limit;                                           ///< Over-speed limit (rpm)
    float f_lowvoltage_limit;                                          ///< Low-voltage limit (V)
} motor_120_degree_extended_cfg_t;

typedef struct st_motor_120_degree_instance_ctrl
{
    uint32_t open;                             ///< Used to determine if the channel is configured

    uint16_t u2_error_info;                    ///< Happened error

    float f_speed_rpm;                         ///< motor speed reference (rpm)

    motor_120_degree_statemachine_t st_statem; ///< Statemachine structure

    motor_cfg_t const * p_cfg;                 ///< Pointer of configuration structure
} motor_120_degree_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in interface API structure for this instance. */
extern const motor_api_t g_motor_on_motor_120_degree;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_Open(motor_ctrl_t * const p_ctrl, motor_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_120_DEGREE_Close(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DEGREE_Run(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DEGREE_Stop(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DEGREE_Reset(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_120_DEGREE_ErrorSet(motor_ctrl_t * const p_ctrl, motor_error_t const error);

fsp_err_t RM_MOTOR_120_DEGREE_SpeedSet(motor_ctrl_t * const p_ctrl, float const speed_rpm);

fsp_err_t RM_MOTOR_120_DEGREE_StatusGet(motor_ctrl_t * const p_ctrl, uint8_t * const p_status);

fsp_err_t RM_MOTOR_120_DEGREE_SpeedGet(motor_ctrl_t * const p_ctrl, float * const p_speed_rpm);

fsp_err_t RM_MOTOR_120_DEGREE_WaitStopFlagGet(motor_ctrl_t * const           p_ctrl,
                                              motor_wait_stop_flag_t * const p_flag_wait_stop);

fsp_err_t RM_MOTOR_120_DEGREE_ErrorCheck(motor_ctrl_t * const p_ctrl, uint16_t * const p_error);

fsp_err_t RM_MOTOR_120_DEGREE_PositionSet(motor_ctrl_t * const                      p_ctrl,
                                          motor_speed_position_data_t const * const p_position);

fsp_err_t RM_MOTOR_120_DEGREE_AngleGet(motor_ctrl_t * const p_ctrl, float * const p_angle_rad);

fsp_err_t RM_MOTOR_120_DEGREE_FunctionSelect(motor_ctrl_t * const p_ctrl, motor_function_select_t const function);

extern void rm_motor_120_degree_120_control_callback(motor_120_control_callback_args_t * p_args);

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_DEGREE)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_120_DEGREE_H
