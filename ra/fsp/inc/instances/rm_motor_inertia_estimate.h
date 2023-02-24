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
 * @addtogroup MOTOR_INERTIA_ESTIMATE
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_INERTIA_ESTIMATE_H
#define RM_MOTOR_INERTIA_ESTIMATE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "rm_motor_inertia_estimate_cfg.h"
#include "rm_motor_inertia_estimate_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_motor_inertia_estimate_start_flag
{
    MOTOR_INERTIA_ESTIMATE_START_FLAG_STOP  = 0,
    MOTOR_INERTIA_ESTIMATE_START_FLAG_START = 1,
} motor_inertia_estimate_start_flag_t;

/* Measure period */
typedef enum e_motor_inertia_estimate_period
{
    MOTOR_INERTIA_ESTIMATE_PERIOD_NO_MOVE = 0,
    MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_ACCELL,
    MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_DECELERATE,
    MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_ACCELL,
    MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_DECELERATE,
    MOTOR_INERTIA_ESTIMATE_PERIOD_MEASURE_FINISH,
} motor_inertia_estimate_period_t;

/** Extended configurations for motor inertia estimate */
typedef struct st_motor_inertia_estimate_extended_cfg
{
    int16_t  s2_move_degree;           ///< Moving position reference [degree]
    uint16_t u2_J_max_speed_rpm;       ///< Maximum Speed [rpm]
    float    f_accel_time;             ///< Acceleration time
    float    f_rotor_inertia;          ///< Initialized rotor inertia value

    float f_judge_low_threshold;       ///< Low threshold to judge speed
    float f_judge_high_threshold;      ///< High threshold to judge speed
    float f_change_mode_time;          ///< Timing value to change internal mode

    float   f_current_ctrl_period;     ///< Period of current control [sec]
    float   f_speed_ctrl_period;       ///< Period of speed control [sec]
    uint8_t u1_motor_polepairs;        ///< Motor pole pairs
    float   f_motor_m;                 ///< Motor magnet flux [Wb]
    float   f_position_interval;       ///< Interval counts for reference position change
} motor_inertia_estimate_extended_cfg_t;

/** Inertia estimate instance control block */
typedef struct st_motor_inertia_estimate_instance_ctrl
{
    uint32_t open;                                       ///< Used to determine if the module is configured

    motor_inertia_estimate_start_flag_t start_flag;      ///< start/stop flag
    motor_inertia_estimate_mode_t       mode;            ///< Internal mode
    uint8_t u1_mode_count;                               ///< Use to manage internal mode
    motor_inertia_estimate_period_t speed_period;        ///< Measure period
    motor_inertia_estimate_period_t speed_period_buffer; ///< Buffer of measure period to be reffered by current cyclic

    uint32_t u4_measure_count;                           ///< Counter for speed control cycle
    uint32_t u4_wait_count;                              ///< Counter to wait change mode timing

    uint8_t u1_position_move_mode;                       ///< Position move mode (TRIANGLE/TRAPEZOID)

    int16_t s2_initial_position_degree;                  ///< Initial position
    float   f_iq_ad;                                     ///< q-axis current [A]
    float   f_summary_iq_ad;                             ///< Summary of q-axis current
    float   f_position_mode_time;                        ///< Summary of speed control period to judge the timing
    float   f_position_dt_time_sec;                      ///< Differencial time of move

    int16_t s2_position_reference_degree;                ///< Position reference [degree]

    float f_estimated_value;                             ///< Estimated inertia
    float f_inertia_value1;                              ///< Buffer to calculate inertia 1
    float f_inertia_value2;                              ///< Buffer to calculate inertia 2

    float f_interval_time;                               ///< Interval time about position transition

    /* Measured data to estimate inertia */
    float f_inertia_speed_ctrl1;
    float f_inertia_speed_ctrl2;
    float f_inertia_speed_ctrl3;
    float f_inertia_speed_ctrl4;
    float f_inertia_speed_ctrl5;
    float f_inertia_speed_ctrl6;
    float f_inertia_speed_ctrl7;
    float f_inertia_speed_ctrl8;

    float f_inertia_integ_iq1;
    float f_inertia_integ_iq2;
    float f_inertia_integ_iq3;
    float f_inertia_integ_iq4;

    float f_inertia_integ_time1;
    float f_inertia_integ_time2;
    float f_inertia_integ_time3;
    float f_inertia_integ_time4;

    float f_inverse_motor_polepairs;                   ///< Inverse motor pole pairs (for calculation)

    motor_inertia_estimate_set_data_t    receive_data; ///< Received data set from speed(position) and current
    motor_inertia_estimate_cfg_t const * p_cfg;        ///< Pointer of configuration structure
} motor_inertia_estimate_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in interface API structure for this instance. */
extern const motor_inertia_estimate_api_t g_motor_inertia_estimate_on_motor_inertia_estimate;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Open(motor_inertia_estimate_ctrl_t * const      p_ctrl,
                                         motor_inertia_estimate_cfg_t const * const p_cfg);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Close(motor_inertia_estimate_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Start(motor_inertia_estimate_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Stop(motor_inertia_estimate_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Reset(motor_inertia_estimate_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_InfoGet(motor_inertia_estimate_ctrl_t * const p_ctrl,
                                            motor_inertia_estimate_info_t * const p_info);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_DataSet(motor_inertia_estimate_ctrl_t * const     p_ctrl,
                                            motor_inertia_estimate_set_data_t * const p_set_data);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_SpeedCyclic(motor_inertia_estimate_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_CurrentCyclic(motor_inertia_estimate_ctrl_t * const p_ctrl);

fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_ParameterUpdate(motor_inertia_estimate_ctrl_t * const      p_ctrl,
                                                    motor_inertia_estimate_cfg_t const * const p_cfg);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_MOTOR_INERTIA_ESTIMATE_H

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_INERTIA_ESTIMATE)
 **********************************************************************************************************************/
