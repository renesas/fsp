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
 * @addtogroup MOTOR_RETURN_ORIGIN
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_RETURN_ORIGIN_H
#define RM_MOTOR_RETURN_ORIGIN_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_motor_return_origin_cfg.h"
#include "rm_motor_return_origin_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_motor_return_origin_start_flag
{
    MOTOR_RETURN_ORIGIN_START_FLAG_STOP  = 0,
    MOTOR_RETURN_ORIGIN_START_FLAG_START = 1,
} motor_return_origin_start_flag_t;

/** Extended configurations for return origin function  */
typedef struct st_motor_return_origin_extended_cfg
{
    float f_search_speed_rpm;           ///< Speed to search origin position [rpm]
    float f_return_accel_rpm;           ///< Acceleration speed when return [rpm/s]

    float f_speed_ctrl_period;          ///< Period of speed control [sec]
    float f_maximum_current;            ///< Maximum current [A]
    float f_current_limit_percent_push; ///< Percentage of current at pushing
    float f_pushing_time;               ///< Keep pushing time [sec]
    float f_over_degree;                ///< Angle to judge search impossible [degree]
    float f_return_degree;              ///< Return angle from pushing position [degree]
    float f_mechanical_gear_ratio;      ///< Mechanical gear ratio
} motor_return_origin_extended_cfg_t;

/** Variables for rerutn origin with pushing */
typedef struct st_motor_return_origin_pushing
{
    uint32_t u4_time_counter;          ///< Counter of speed cyclic (to judge the time)
    float    f_sum_position;           ///< Summary of position data
    uint32_t u4_sum_counter;           ///< Counter of summary
    float    f_move_amount;            ///< Movement amount [degree]

    float f_judge_iq;                  ///< q-axis current to judge pushing
    float f_pushing_counts;            ///< Counts to measure pushing time
} motor_return_origin_pushing_t;

/** Return origin function instance control block */
typedef struct st_motor_return_origin_instance_ctrl
{
    uint32_t open;                               ///< Used to determine if the module is configured

    motor_return_origin_start_flag_t start_flag; ///< start/stop flag

    motor_return_origin_state_t state;           ///< State number of return origin process
    int8_t s1_direction;                         ///< Moving direction
    float  f_angle_degree_on_edge;               ///< Rotor angle on the edge [degree]
    float  f_current_speed;                      ///< Current speed
    float  f_origin_position_angle_degree;       ///< Searched origin position [degree]
    float  f_search_speed;                       ///< Speed to search origin position [rad / sampling time]
    float  f_accel_speed;                        ///< Speed accelaration
    float  f_position_reference_degree;          ///< Position reference [degree]

    motor_return_origin_pushing_t st_pushing;    ///< Variables for pushing

    motor_return_origin_set_data_t receive_data; ///< Received data from speed(position) & current

    motor_return_origin_cfg_t const * p_cfg;     ///< Pointer of configuration structure
} motor_return_origin_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in interface API structure for this instance. */
extern const motor_return_origin_api_t g_motor_return_origin_on_motor_return_origin;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_Open(motor_return_origin_ctrl_t * const      p_ctrl,
                                      motor_return_origin_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_Close(motor_return_origin_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_Start(motor_return_origin_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_Stop(motor_return_origin_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_Reset(motor_return_origin_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_InfoGet(motor_return_origin_ctrl_t * const p_ctrl,
                                         motor_return_origin_info_t * const p_info);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_DataSet(motor_return_origin_ctrl_t * const     p_ctrl,
                                         motor_return_origin_set_data_t * const p_set_data);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_SpeedCyclic(motor_return_origin_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_RETURN_ORIGIN_ParameterUpdate(motor_return_origin_ctrl_t * const      p_ctrl,
                                                 motor_return_origin_cfg_t const * const p_cfg);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_RETURN_ORIGIN_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_RETURN_ORIGIN)
 **********************************************************************************************************************/
