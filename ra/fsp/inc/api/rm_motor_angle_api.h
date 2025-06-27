/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MOTOR_INTERFACES
 * @defgroup MOTOR_ANGLE_API Motor angle Interface
 * @brief Interface for motor angle and speed calculation functions.
 *
 * @section MOTOR_ANGLE_API_Summary Summary
 * The Motor angle interface calculates the rotor angle and rotational speed from other data.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_ANGLE_API_H
#define RM_MOTOR_ANGLE_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Motor Angle Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void motor_angle_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_angle_cfg
{
    void       * p_context;
    void const * p_extend;
} motor_angle_cfg_t;

/** Interface structure **/
typedef struct st_motor_angle_current
{
    float id;                          ///< d-axis current
    float iq;                          ///< q-axis current
} motor_angle_current_t;

/** Motor angle voltage reference */
typedef struct st_motor_angle_voltage_reference
{
    float vd;                          ///< d-axis voltage reference
    float vq;                          ///< q-axis voltage reference
} motor_angle_voltage_reference_t;

/** A/D conversion data */
typedef struct st_motor_angle_ad_data
{
    float sin_ad_data;                 ///< sin A/D data of induction sensor
    float cos_ad_data;                 ///< cos A/D data of induction sensor
} motor_angle_ad_data_t;

/* encoder angle adjustment status */
typedef enum e_motor_sense_encoder_angle_adjust
{
    MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE = 1, ///< Roter Angle Adjustment to pull in 90degree
    MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE,      ///< Roter Angle Adjustment to pull in 0degree
    MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH,        ///< Roter Angle Adjustment Finish
    MOTOR_SENSE_ENCODER_ANGLE_ADJUST_OPENLOOP,      ///< Roter Angle Adjustment Finish
} motor_sense_encoder_angle_adjust_t;

/* openloop status to measure indcution sensor offset */
typedef enum e_motor_angle_open_loop
{
    MOTOR_ANGLE_OPEN_LOOP_INACTIVE = 0, ///< Openloop inactive
    MOTOR_ANGLE_OPEN_LOOP_ACTIVE,       ///< Openloop active
} motor_angle_open_loop_t;

/** Motor angle encoder adjustment info */
typedef struct st_motor_angle_encoder_info
{
    motor_sense_encoder_angle_adjust_t e_adjust_status; ///< Encoder Adjustment Status
    uint8_t u1_adjust_count_full;                       ///< Adjustment count became full

    /* For induction sensor */
    motor_angle_open_loop_t e_open_loop_status;         ///< Openloop status
    float f_openloop_speed;                             ///< Openloop speed
    float f_openloop_id_ref;                            ///< Openloop d-axis current
} motor_angle_encoder_info_t;

/** Flag for induction correction error status */
typedef enum  e_motor_angle_error
{
    MOTOR_ANGLE_ERROR_NONE      = 0,   ///< No error happen
    MOTOR_ANGLE_ERROR_INDUCTION = 1,   ///< Error happens in induction sensor correction process
} motor_angle_error_t;

/** Functions implemented as application interface will follow these APIs. */
typedef struct st_motor_angle_api
{
    /** Initialize the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg);

    /** Close (Finish) the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_angle_ctrl_t * const p_ctrl);

    /** Reset the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_angle_ctrl_t * const p_ctrl);

    /** Set (Input) Current & Voltage Reference data into the Motor_Angle.
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  p_st_current   Pointer to current structure
     * @param[in]  p_st_voltage   Pointer to voltage Reference structure
     */
    fsp_err_t (* currentSet)(motor_angle_ctrl_t * const p_ctrl, motor_angle_current_t * const p_st_current,
                             motor_angle_voltage_reference_t * const p_st_voltage);

    /** Set (Input) Speed Information into the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  speed_ctrl   Control reference of rotational speed [rad/s]
     * @param[in]  damp_speed   Damping rotational speed [rad/s]
     */
    fsp_err_t (* speedSet)(motor_angle_ctrl_t * const p_ctrl, float const speed_ctrl, float const damp_speed);

    /** Set the flag of PI Control runs.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  flag_pi      The flag of PI control runs
     */
    fsp_err_t (* flagPiCtrlSet)(motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi);

    /** Calculate internal parameters of encoder process.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* internalCalculate)(motor_angle_ctrl_t * const p_ctrl);

    /** Get rotor angle and rotational speed from the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_angl       Memory address to get rotor angle data
     * @param[out] p_speed      Memory address to get rotational speed data
     * @param[out] p_phase_err  Memory address to get phase(angle) error data
     */
    fsp_err_t (* angleSpeedGet)(motor_angle_ctrl_t * const p_ctrl, float * const p_angle, float * const p_speed,
                                float * const p_phase_err);

    /** Angle Adjustment Process.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* angleAdjust)(motor_angle_ctrl_t * const p_ctrl);

    /** DEPRECATED Encoder Cyclic Process.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* encoderCyclic)(motor_angle_ctrl_t * const p_ctrl);

    /** Cyclic Process. please
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* cyclicProcess)(motor_angle_ctrl_t * const p_ctrl);

    /** Set sensor A/D data into the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_ad_data    Pointer to A/D conversion data
     */
    fsp_err_t (* sensorDataSet)(motor_angle_ctrl_t * const p_ctrl, motor_angle_ad_data_t * const p_ad_data);

    /** Get estimated d/q-axis component from the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_ed         Memory address to get estimated d-axis component
     * @param[out] p_eq         Memory address to get estimated q-axis component
     */
    fsp_err_t (* estimatedComponentGet)(motor_angle_ctrl_t * const p_ctrl, float * const p_ed, float * const p_eq);

    /** Get Encoder Calculate Information.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_info       Memory address to get angle internal information
     */
    fsp_err_t (* infoGet)(motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info);

    /** Update Parameters for the calculation in the Motor_Angle.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * p_cfg);
} motor_angle_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_angle_instance
{
    motor_angle_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance
    motor_angle_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance
    motor_angle_api_t const * p_api;   ///< Pointer to the API structure for this instance
} motor_angle_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_ANGLE_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_ANGLE_API_H */
