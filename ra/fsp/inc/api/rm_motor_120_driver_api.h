/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MOTOR_INTERFACES
 * @defgroup MOTOR_120_DRIVER_API Motor 120-Degree Driver Interface
 * @brief Interface for motor driver functions.
 *
 * @section MOTOR_120_DRIVER_API_Summary Summary
 * The MOTOR_120_DRIVER interface for setting the PWM modulation duty
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_120_DRIVER_API_H
#define RM_MOTOR_120_DRIVER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_motor_120_driver_event
{
    MOTOR_120_DRIVER_EVENT_FORWARD = 1, ///< Event before motor 120 driver process (before current control timing)
    MOTOR_120_DRIVER_EVENT_120_CONTROL, ///< Event 120 detection
    MOTOR_120_DRIVER_EVENT_BACKWARD,    ///< Event after motor 120 driver process (after PWM duty setting)
} motor_120_driver_event_t;

/** The flag represents that the offset measurement is finished */
typedef enum e_motor_120_driver_flag_offset_calc
{
    MOTOR_120_DRIVER_FLAG_OFFSET_CALC_CLEAR = 0,  ///< Offset calculation not finished
    MOTOR_120_DRIVER_FLAG_OFFSET_CALC_OFF_FINISH, ///< Off voltage offset calculation finished
    MOTOR_120_DRIVER_FLAG_OFFSET_CALC_ALL_FINISH, ///< All offset calculation finished
} motor_120_driver_flag_offset_calc_t;

/** Phase voltage pattern */
typedef enum e_motor_120_driver_phase_pattern
{
    MOTOR_120_DRIVER_PHASE_PATTERN_ERROR = 0,    ///< Phase voltage pattern error

    /* Non-complementary synchronous pattern */
    MOTOR_120_DRIVER_PHASE_PATTERN_UP_PWM_VN_ON, ///< Up(PWM) to Vn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_UP_PWM_WN_ON, ///< Up(PWM) to Wn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_VP_PWM_UN_ON, ///< Vp(PWM) to Un(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_VP_PWM_WN_ON, ///< Vp(PWM) to Wn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_WP_PWM_UN_ON, ///< Wp(PWM) to Un(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_WP_PWM_VN_ON, ///< Wp(PWM) to Vn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_VN_PWM, ///< Up(on) to Vn(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_WN_PWM, ///< Up(on) to Wn(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_UN_PWM, ///< Vp(on) to Un(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_WN_PWM, ///< Vp(on) to Wn(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_UN_PWM, ///< Wp(on) to Un(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_VN_PWM, ///< Wp(on) to Vn(PWM)

    /* Complementary synchronous pattern */
    MOTOR_120_DRIVER_PHASE_PATTERN_U_PWM_VN_ON,  ///< U(PWM) to Vn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_U_PWM_WN_ON,  ///< U(PWM) to Wn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_V_PWM_UN_ON,  ///< V(PWM) to Un(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_V_PWM_WN_ON,  ///< V(PWM) to Wn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_W_PWM_UN_ON,  ///< W(PWM) to Un(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_W_PWM_VN_ON,  ///< W(PWM) to Vn(on)
    MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_V_PWM,  ///< Up(on) to V(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_W_PWM,  ///< Up(on) to W(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_U_PWM,  ///< Vp(on) to U(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_W_PWM,  ///< Vp(on) to W(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_U_PWM,  ///< Wp(on) to U(PWM)
    MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_V_PWM,  ///< Wp(on) to V(PWM)
} motor_120_driver_phase_pattern_t;

/** Callback function parameter data */
typedef struct st_motor_120_driver_callback_args
{
    motor_120_driver_event_t event;    ///< Event trigger
    void * p_context;                  ///< Placeholder for user data.
} motor_120_driver_callback_args_t;

/** Current data get structure */
typedef struct st_motor_120_driver_current_status
{
    float iu;                          ///< U phase current (A)
    float iv;                          ///< V phase current (A)
    float iw;                          ///< W phase current (A)
    float vdc;                         ///< Main line voltage (V)
    float vu;                          ///< U phase voltage (V)
    float vv;                          ///< V phase voltage (V)
    float vw;                          ///< W phase voltage (V)
} motor_120_driver_current_status_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void motor_120_driver_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_120_driver_cfg
{
    void (* p_callback)(motor_120_driver_callback_args_t * p_args); ///< Callback function
    void       * p_context;                                         ///< Placeholder for user data.
    void const * p_extend;                                          ///< Placeholder for user extension.
} motor_120_driver_cfg_t;

/** Functions implemented at the HAL layer will follow these APIs. */
typedef struct st_motor_120_driver_api
{
    /** Initialize the motor 120 driver module.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_120_driver_ctrl_t * const p_ctrl, motor_120_driver_cfg_t const * const p_cfg);

    /** Close the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_120_driver_ctrl_t * const p_ctrl);

    /** Run the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* run)(motor_120_driver_ctrl_t * const p_ctrl);

    /** Stop the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* stop)(motor_120_driver_ctrl_t * const p_ctrl);

    /** Reset variables of the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_120_driver_ctrl_t * const p_ctrl);

    /** Set (Input) phase voltage data into the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  u_voltage    U phase voltage [V]
     * @param[in]  v_voltage    V phase voltage [V]
     * @param[in]  w_voltage    W phase voltage [V]
     */
    fsp_err_t (* phaseVoltageSet)(motor_120_driver_ctrl_t * const p_ctrl, float const u_voltage, float const v_voltage,
                                  float const w_voltage);

    /** Set phase voltage pattern the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  pattern      Voltage pattern
     */
    fsp_err_t (* phasePatternSet)(motor_120_driver_ctrl_t * const        p_ctrl,
                                  motor_120_driver_phase_pattern_t const pattern);

    /** Get phase current, Vdc and Va_max data from the motor 120 driver module
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_current_status Pointer to get data structure.
     */
    fsp_err_t (* currentGet)(motor_120_driver_ctrl_t * const           p_ctrl,
                             motor_120_driver_current_status_t * const p_current_status);

    /** current offset detection from the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* currentOffsetCalc)(motor_120_driver_ctrl_t * const p_ctrl);

    /** Get the flag of finish current offset detection from the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_flag_offset   Flag of finish current offset detection
     */
    fsp_err_t (* flagCurrentOffsetGet)(motor_120_driver_ctrl_t * const             p_ctrl,
                                       motor_120_driver_flag_offset_calc_t * const p_flag_offset);

    /** Update configuration parameters for the calculation in the motor 120 driver module
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_120_driver_ctrl_t * const p_ctrl, motor_120_driver_cfg_t const * const p_cfg);
} motor_120_driver_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_120_driver_instance
{
    motor_120_driver_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    motor_120_driver_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    motor_120_driver_api_t const * p_api;  ///< Pointer to the API structure for this instance
} motor_120_driver_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_DRIVER_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_120_DRIVER_API_H */
