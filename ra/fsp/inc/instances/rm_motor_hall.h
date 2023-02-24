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
 * @addtogroup MOTOR_HALL
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_HALL_H
#define RM_MOTOR_HALL_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "rm_motor_api.h"
#include "rm_motor_speed.h"
#include "rm_motor_current.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum  e_motor_hall_ctrl_status
{
    MOTOR_HALL_CTRL_STATUS_STOP  = 0,
    MOTOR_HALL_CTRL_STATUS_RUN   = 1,
    MOTOR_HALL_CTRL_STATUS_ERROR = 2,
} motor_hall_ctrl_status_t;

typedef enum  e_motor_hall_ctrl_event
{
    MOTOR_HALL_CTRL_EVENT_STOP  = 0,
    MOTOR_HALL_CTRL_EVENT_RUN   = 1,
    MOTOR_HALL_CTRL_EVENT_ERROR = 2,
    MOTOR_HALL_CTRL_EVENT_RESET = 3
} motor_hall_ctrl_event_t;

typedef struct  rm_motor_hall_statemachine
{
    motor_hall_ctrl_status_t status;        ///< The current system status
    motor_hall_ctrl_status_t next_status;   ///< The next system status
    motor_hall_ctrl_event_t  current_event; ///< The current event index

    uint16_t u2_error_status;               ///< The error information
} motor_hall_statemachine_t;

typedef struct st_motor_hall_extended_cfg
{
    float f_overcurrent_limit;         ///< Over-current limit [A]
    float f_overvoltage_limit;         ///< Over-voltage limit [V]
    float f_overspeed_limit;           ///< Over-speed limit [rpm]
    float f_lowvoltage_limit;          ///< Low-voltage limit [V]
} motor_hall_extended_cfg_t;

typedef struct st_motor_hall_instance_ctrl
{
    uint32_t open;                     ///< Used to determine if the channel is configured

    uint16_t u2_error_info;            ///< Happened error

    motor_hall_statemachine_t st_statem;

    /* Speed control <=> Current control interface */
    motor_speed_input_t    st_speed_input;
    motor_speed_output_t   st_speed_output;
    motor_current_input_t  st_current_input;
    motor_current_output_t st_current_output;

    motor_cfg_t const * p_cfg;
} motor_hall_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const motor_api_t g_motor_on_motor_hall;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_HALL_Open(motor_ctrl_t * const p_ctrl, motor_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_HALL_Close(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_HALL_Run(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_HALL_Stop(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_HALL_Reset(motor_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_HALL_ErrorSet(motor_ctrl_t * const p_ctrl, motor_error_t const error);

fsp_err_t RM_MOTOR_HALL_SpeedSet(motor_ctrl_t * const p_ctrl, float const speed_rpm);

fsp_err_t RM_MOTOR_HALL_StatusGet(motor_ctrl_t * const p_ctrl, uint8_t * const p_status);

fsp_err_t RM_MOTOR_HALL_AngleGet(motor_ctrl_t * const p_ctrl, float * const p_angle_rad);

fsp_err_t RM_MOTOR_HALL_SpeedGet(motor_ctrl_t * const p_ctrl, float * const p_speed_rpm);

fsp_err_t RM_MOTOR_HALL_ErrorCheck(motor_ctrl_t * const p_ctrl, uint16_t * const p_error);

fsp_err_t RM_MOTOR_HALL_PositionSet(motor_ctrl_t * const p_ctrl, motor_speed_position_data_t const * const p_position);

fsp_err_t RM_MOTOR_HALL_WaitStopFlagGet(motor_ctrl_t * const p_ctrl, motor_wait_stop_flag_t * const p_flag);

fsp_err_t RM_MOTOR_HALL_FunctionSelect(motor_ctrl_t * const p_ctrl, motor_function_select_t const function);

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_HALL)
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_HALL_H
