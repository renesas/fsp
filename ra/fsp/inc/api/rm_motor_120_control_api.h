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
 * @ingroup RENESAS_INTERFACES
 * @defgroup MOTOR_120_CONTROL_API Motor 120-Degree Control Interface
 * @brief Interface for motor 120 control functions.
 *
 * @section MOTOR_120_CONTROL_API_Summary Summary
 * The motor 120 control interface for speed calculation and setting, fixed cycle processing
 *
 * The motor 120 control interface can be implemented by:
 * - @ref MOTOR_120_CONTROL_SENSORLESS
 * - @ref MOTOR_120_CONTROL_HALL
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_120_CONTROL_API_H
#define RM_MOTOR_120_CONTROL_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "rm_motor_120_driver_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_motor_120_control_event
{
    MOTOR_120_CONTROL_EVENT_ADC_FORWARD = 1, ///< Event before motor 120 driver process
    MOTOR_120_CONTROL_EVENT_ADC_BACKWARD,    ///< Event after motor 120 driver process
    MOTOR_120_CONTROL_EVENT_CYCLE_FORWARD,   ///< Before cyclic process of speed control
    MOTOR_120_CONTROL_EVENT_CYCLE_BACKWARD,  ///< After cyclic process of speed control
} motor_120_control_event_t;

/** Callback function parameter data */
typedef struct st_motor_120_control_callback_args
{
    motor_120_control_event_t event;     ///< Event trigger
    void const              * p_context; ///< Placeholder for user data.
} motor_120_control_callback_args_t;

/** Motor parameter for motor 120 control */
typedef struct st_motor_120_control_motor_parameter
{
    uint32_t u4_motor_pp;              ///< Pole pairs
    float    f4_motor_r;               ///< Resistance (ohm)
    float    f4_motor_ld;              ///< Inductance for d-axis (H)
    float    f4_motor_lq;              ///< Inductance for q-axis (H)
    float    f4_motor_m;               ///< Magnet flux (Wb)
    float    f4_motor_j;               ///< Rotor inertia (kgm^2)
} motor_120_control_motor_parameter_t;

typedef enum e_motor_120_conduction_type
{
    MOTOR_120_CONDUCTION_TYPE_FIRST60 = 0,   ///< First 60 degree PWM
    MOTOR_120_CONDUCTION_TYPE_COMPLEMENTARY, ///< Complementary first 60 degree PWM
} motor_120_conduction_type_t;

/** 120 control status */
typedef enum  e_motor_120_control_status
{
    MOTOR_120_CONTROL_STATUS_INACTIVE = 0, ///< 120 control status inactive
    MOTOR_120_CONTROL_STATUS_ACTIVE   = 1, ///< 120 control status active
} motor_120_control_status_t;

/** Run mode */
typedef enum  e_motor_120_control_run_mode
{
    MOTOR_120_CONTROL_RUN_MODE_INIT  = 0, ///< Run mode init
    MOTOR_120_CONTROL_RUN_MODE_BOOT  = 1, ///< Run mode boot
    MOTOR_120_CONTROL_RUN_MODE_DRIVE = 2, ///< Run mode drive
} motor_120_control_run_mode_t;

/** Rotation direction */
typedef enum  e_motor_120_control_rotation_direction
{
    MOTOR_120_CONTROL_ROTATION_DIRECTION_CW  = 0, ///< Clockwise
    MOTOR_120_CONTROL_ROTATION_DIRECTION_CCW = 1, ///< Counter clockwise
    MOTOR_120_CONTROL_ROTATION_DIRECTION_MAX = 2, ///< Max value
} motor_120_control_rotation_direction_t;

/** Flag for waiting for motor stop */
typedef enum  e_motor_120_control_wait_stop_flag
{
    MOTOR_120_CONTROL_WAIT_STOP_FLAG_CLEAR = 0, ///< Wait stop flag clear
    MOTOR_120_CONTROL_WAIT_STOP_FLAG_SET   = 1, ///< Wait stop flag set
} motor_120_control_wait_stop_flag_t;

/** Flag for timeout error status */
typedef enum  e_motor_120_control_timeout_error_flag
{
    MOTOR_120_CONTROL_TIMEOUT_ERROR_FLAG_CLEAR = 0, ///< Timeout error flag clear
    MOTOR_120_CONTROL_TIMEOUT_ERROR_FLAG_SET   = 1, ///< Timeout error flag set
} motor_120_control_timeout_error_flag_t;

/** Flag for pattern error status */
typedef enum  e_motor_120_control_pattern_error_flag
{
    MOTOR_120_CONTROL_PATTERN_ERROR_FLAG_CLEAR = 0, ///< Pattern error flag clear
    MOTOR_120_CONTROL_PATTERN_ERROR_FLAG_SET   = 1, ///< Pattern error flag set
} motor_120_control_pattern_error_flag_t;

/** Speed reference status */
typedef enum  e_motor_120_control_speed_ref
{
    MOTOR_120_CONTROL_SPEED_REF_ZERO_CONST = 0, ///< Speed reference zero const
    MOTOR_120_CONTROL_SPEED_REF_OPENLOOP_1 = 1, ///< Speed reference openloop 1
    MOTOR_120_CONTROL_SPEED_REF_OPENLOOP_2 = 2, ///< Speed reference openloop 2
    MOTOR_120_CONTROL_SPEED_REF_OPENLOOP_3 = 3, ///< Speed reference openloop 3
    MOTOR_120_CONTROL_SPEED_REF_CHANGE     = 4, ///< Speed reference change
} motor_120_control_speed_ref_t;

/** Voltage reference status */
typedef enum  e_motor_120_control_voltage_ref
{
    MOTOR_120_CONTROL_VOLTAGE_REF_ZERO_CONST = 0, ///< Voltage reference zero const
    MOTOR_120_CONTROL_VOLTAGE_REF_UP         = 1, ///< Voltage reference up
    MOTOR_120_CONTROL_VOLTAGE_REF_CONST      = 2, ///< Voltage reference const
    MOTOR_120_CONTROL_VOLTAGE_REF_OPENLOOP   = 3, ///< Voltage reference opneloop
    MOTOR_120_CONTROL_VOLTAGE_REF_PI_OUTPUT  = 4, ///< Voltage reference pi output
} motor_120_control_voltage_ref_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - motor_120_control_sensorless_instance_ctrl_t
 * - motor_120_control_hall_instance_ctrl_t
 */
typedef void motor_120_control_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_120_control_cfg
{
    motor_120_conduction_type_t conduction_type;                     ///< 0:First 60 degree PWM, 1:Complementary first 60 degree PWM
    uint32_t u4_timeout_cnt;                                         ///< Undetected time
    float    f4_max_drive_v;                                         ///< Max output voltage (V)
    float    f4_min_drive_v;                                         ///< Min output voltage (V)
    uint32_t u4_speed_pi_decimation;                                 ///< Speed PI control decimation counter
    uint32_t u4_free_run_timer_freq;                                 ///< Speed calc free run timer frequency (MHz)
    float    f4_speed_lpf_k;                                         ///< Speed LPF parameter
    float    f4_limit_speed_change;                                  ///< Speed ref change limit
    float    f4_pi_ctrl_kp;                                          ///< PI control error
    float    f4_pi_ctrl_ki;                                          ///< PI control buffer of integral term
    float    f4_pi_ctrl_ilimit;                                      ///< PI control limit of integral term

    motor_120_control_motor_parameter_t motor_param;                 ///< Motor parameter

    void (* p_callback)(motor_120_control_callback_args_t * p_args); ///< Callback function
    void const * p_context;                                          ///< Placeholder for user data.
    void const * p_extend;                                           ///< Extended configurations
} motor_120_control_cfg_t;

/** Functions implemented at the HAL layer will follow these APIs. */
typedef struct st_motor_120_control_api
{
    /** Initialize the motor 120 control module.
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_Open()
     * - @ref RM_MOTOR_120_CONTROL_HALL_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_120_control_ctrl_t * const p_ctrl, motor_120_control_cfg_t const * const p_cfg);

    /** Close the motor 120 control module
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_Close()
     * - @ref RM_MOTOR_120_CONTROL_HALL_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_120_control_ctrl_t * const p_ctrl);

    /** Run the motor 120 control module
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_Run()
     * - @ref RM_MOTOR_120_CONTROL_HALL_Run()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* run)(motor_120_control_ctrl_t * const p_ctrl);

    /** Stop the motor 120 control module
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_Stop()
     * - @ref RM_MOTOR_120_CONTROL_HALL_Stop()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* stop)(motor_120_control_ctrl_t * const p_ctrl);

    /** Reset variables of the motor 120 control module
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_Reset()
     * - @ref RM_MOTOR_120_CONTROL_HALL_Reset()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_120_control_ctrl_t * const p_ctrl);

    /** Set speed[rpm]
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_SpeedSet()
     * - @ref RM_MOTOR_120_CONTROL_HALL_SpeedSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] speed_rpm    Pointer to get speed data[rpm]
     */
    fsp_err_t (* speedSet)(motor_120_control_ctrl_t * const p_ctrl, float const speed_rpm);

    /** Get speed.
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_SpeedGet()
     * - @ref RM_MOTOR_120_CONTROL_HALL_SpeedGet()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[out] p_speed_rpm         Pointer to get speed data[rpm]
     */
    fsp_err_t (* speedGet)(motor_120_control_ctrl_t * const p_ctrl, float * const p_speed_rpm);

    /** Get phase current, Vdc and Va_max data.
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_CurrentGet()
     * - @ref RM_MOTOR_120_CONTROL_HALL_CurrentGet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_current_status Pointer to get data structure.
     */
    fsp_err_t (* currentGet)(motor_120_control_ctrl_t * const          p_ctrl,
                             motor_120_driver_current_status_t * const p_current_status);

    /** Get wait stop flag.
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_WaitStopFlagGet()
     * - @ref RM_MOTOR_120_CONTROL_HALL_WaitStopFlagGet()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[out] p_flag              Pointer to wait stop flag
     */
    fsp_err_t (* waitStopFlagGet)(motor_120_control_ctrl_t * const           p_ctrl,
                                  motor_120_control_wait_stop_flag_t * const p_flag);

    /** Get timerout error flag.
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_TimeoutErrorFlagGet()
     * - @ref RM_MOTOR_120_CONTROL_HALL_TimeoutErrorFlagGet()
     *
     * @param[in]  p_ctrl                   Pointer to control structure.
     * @param[out] p_timeout_error_flag     Pointer to timeout error flag
     */
    fsp_err_t (* timeoutErrorFlagGet)(motor_120_control_ctrl_t * const               p_ctrl,
                                      motor_120_control_timeout_error_flag_t * const p_timeout_error_flag);

    /** Get pattern error flag.
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_PatternErrorFlagGet()
     * - @ref RM_MOTOR_120_CONTROL_HALL_PatternErrorFlagGet()
     *
     * @param[in]  p_ctrl                       Pointer to control structure.
     * @param[out] p_pattern_error_flag         Pointer to pattern error flag
     */
    fsp_err_t (* patternErrorFlagGet)(motor_120_control_ctrl_t * const               p_ctrl,
                                      motor_120_control_pattern_error_flag_t * const p_pattern_error_flag);

    /** Get voltage ref.
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_VoltageRefGet()
     * - @ref RM_MOTOR_120_CONTROL_HALL_VoltageRefGet()
     *
     * @param[in]  p_ctrl                       Pointer to control structure.
     * @param[out] p_voltage_ref                Pointer to flag voltage ref
     */
    fsp_err_t (* voltageRefGet)(motor_120_control_ctrl_t * const        p_ctrl,
                                motor_120_control_voltage_ref_t * const p_voltage_ref);

    /** Update configuration parameters for the calculation in the motor 120 control module
     * @par Implemented as
     * - @ref RM_MOTOR_120_CONTROL_SENSORLESS_ParameterUpdate()
     * - @ref RM_MOTOR_120_CONTROL_HALL_ParameterUpdate()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_120_control_ctrl_t * const p_ctrl, motor_120_control_cfg_t const * const p_cfg);
} motor_120_control_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_120_control_instance
{
    motor_120_control_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    motor_120_control_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    motor_120_control_api_t const * p_api;  ///< Pointer to the API structure for this instance
} motor_120_control_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_CONTROL_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_120_CONTROL_API_H */
