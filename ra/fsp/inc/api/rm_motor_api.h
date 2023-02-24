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
 * @defgroup MOTOR_API Motor Interface
 * @brief Interface for Motor functions.
 *
 * @section MOTOR_API_Summary Summary
 * The Motor interface provides Motor functionality.
 *
 * Implemented by:
 * - @ref MOTOR_SENSORLESS
 * - @ref MOTOR_ENCODER
 * - @ref MOTOR_HALL
 * - @ref MOTOR_120_DEGREE
 * - @ref MOTOR_INDUCTION
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_API_H
#define RM_MOTOR_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "rm_motor_speed_api.h"
#include "rm_motor_current_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Error information */
typedef enum e_rm_motor_error
{
    MOTOR_ERROR_NONE              = 0x0000,
    MOTOR_ERROR_OVER_CURRENT_HW   = 0x0001,
    MOTOR_ERROR_OVER_VOLTAGE      = 0x0002,
    MOTOR_ERROR_OVER_SPEED        = 0x0004,
    MOTOR_ERROR_HALL_TIMEOUT      = 0x0008,
    MOTOR_ERROR_BEMF_TIMEOUT      = 0x0010,
    MOTOR_ERROR_HALL_PATTERN      = 0x0020,
    MOTOR_ERROR_BEMF_PATTERN      = 0x0040,
    MOTOR_ERROR_LOW_VOLTAGE       = 0x0080,
    MOTOR_ERROR_OVER_CURRENT_SW   = 0x0100,
    MOTOR_ERROR_INDUCTION_CORRECT = 0x0200,
    MOTOR_ERROR_UNKNOWN           = 0xFFFF,
} motor_error_t;

/** Events that can trigger a callback function */
typedef enum e_motor_callback_event
{
    MOTOR_CALLBACK_EVENT_SPEED_FORWARD = 1, ///< Event forward speed control
    MOTOR_CALLBACK_EVENT_SPEED_BACKWARD,    ///< Event backward speed control
    MOTOR_CALLBACK_EVENT_CURRENT_FORWARD,   ///< Event forward current control
    MOTOR_CALLBACK_EVENT_CURRENT_BACKWARD,  ///< Event backward current control
    MOTOR_CALLBACK_EVENT_ADC_FORWARD,       ///< Event before motor 120 driver process
    MOTOR_CALLBACK_EVENT_ADC_BACKWARD,      ///< Event after motor 120 driver process
    MOTOR_CALLBACK_EVENT_CYCLE_FORWARD,     ///< Before cyclic process of speed control
    MOTOR_CALLBACK_EVENT_CYCLE_BACKWARD,    ///< After cyclic process of speed control
} motor_callback_event_t;

/** Flag for waiting for motor stop */
typedef enum  e_motor_wait_stop_flag
{
    MOTOR_WAIT_STOP_FLAG_CLEAR = 0,    ///< Wait stop flag clear
    MOTOR_WAIT_STOP_FLAG_SET   = 1,    ///< Wait stop flag set
} motor_wait_stop_flag_t;

/** Function select */
typedef enum e_motor_function_select
{
    MOTOR_FUNCTION_SELECT_NONE             = 0, ///< No function selected
    MOTOR_FUNCTION_SELECT_INERTIA_ESTIMATE = 1, ///< Inertia estimation
    MOTOR_FUNCTION_SELECT_RETURN_ORIGIN    = 2, ///< Return origin position
} motor_function_select_t;

/** callback function parameter data */
typedef struct st_rm_motor_callback_args
{
    void const           * p_context;  ///< Placeholder for user data.
    motor_callback_event_t event;
} motor_callback_args_t;

/** Motor Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - motor_instance_ctrl_t
 */
typedef void motor_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_cfg
{
    motor_speed_instance_t const   * p_motor_speed_instance;   ///< Speed Instance
    motor_current_instance_t const * p_motor_current_instance; ///< Current Instance

    /** Placeholder for user data.  Passed to the user callback in motor_callback_args_t. */
    void (* p_callback)(motor_callback_args_t * p_args);
    void const * p_context;
    void const * p_extend;             ///< Placeholder for user extension.
} motor_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_motor_api
{
    /** Open driver.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_Open()
     * - @ref RM_MOTOR_ENCODER_Open()
     * - @ref RM_MOTOR_120_DEGREE_Open()
     * - @ref RM_MOTOR_INDUCTION_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_ctrl_t * const p_ctrl, motor_cfg_t const * const p_cfg);

    /** Close driver.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_Close()
     * - @ref RM_MOTOR_ENCODER_Close()
     * - @ref RM_MOTOR_120_DEGREE_Close()
     * - @ref RM_MOTOR_INDUCTION_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_ctrl_t * const p_ctrl);

    /** Run the motor. (Start the motor rotation.)
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_Run()
     * - @ref RM_MOTOR_ENCODER_Run()
     * - @ref RM_MOTOR_120_DEGREE_Run()
     * - @ref RM_MOTOR_INDUCTION_Run()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* run)(motor_ctrl_t * const p_ctrl);

    /** Stop the motor. (Stop the motor rotation.)
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_Stop()
     * - @ref RM_MOTOR_ENCODER_Stop()
     * - @ref RM_MOTOR_120_DEGREE_Stop()
     * - @ref RM_MOTOR_INDUCTION_Stop()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* stop)(motor_ctrl_t * const p_ctrl);

    /** Reset the motor control. (Recover from the error status.)
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_Reset()
     * - @ref RM_MOTOR_ENCODER_Reset()
     * - @ref RM_MOTOR_120_DEGREE_Reset()
     * - @ref RM_MOTOR_INDUCTION_Reset()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_ctrl_t * const p_ctrl);

    /** Set Error Information.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_ErrorSet()
     * - @ref RM_MOTOR_ENCODER_ErrorSet()
     * - @ref RM_MOTOR_120_DEGREE_ErrorSet()
     * - @ref RM_MOTOR_INDUCTION_ErrorSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  error        Happend error code
     */
    fsp_err_t (* errorSet)(motor_ctrl_t * const p_ctrl, motor_error_t const error);

    /** Set rotation speed.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_SpeedSet()
     * - @ref RM_MOTOR_ENCODER_SpeedSet()
     * - @ref RM_MOTOR_120_DEGREE_SpeedSet()
     * - @ref RM_MOTOR_INDUCTION_SpeedSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  speed_rpm    Required rotation speed [rpm]
     */
    fsp_err_t (* speedSet)(motor_ctrl_t * const p_ctrl, float const speed_rpm);

    /** Set reference position.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_PositionSet()
     * - @ref RM_MOTOR_ENCODER_PositionSet()
     * - @ref RM_MOTOR_120_DEGREE_PositionSet()
     * - @ref RM_MOTOR_INDUCTION_PositionSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_position   Pointer to set required data
     */
    fsp_err_t (* positionSet)(motor_ctrl_t * const p_ctrl, motor_speed_position_data_t const * const p_position);

    /** Get the motor control status.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_StatusGet()
     * - @ref RM_MOTOR_ENCODER_StatusGet()
     * - @ref RM_MOTOR_120_DEGREE_StatusGet()
     * - @ref RM_MOTOR_INDUCTION_StatusGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_status     Pointer to get the motor control status
     */
    fsp_err_t (* statusGet)(motor_ctrl_t * const p_ctrl, uint8_t * const p_status);

    /** Get the rotor angle.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_AngleGet()
     * - @ref RM_MOTOR_ENCODER_AngleGet()
     * - @ref RM_MOTOR_120_DEGREE_AngleGet()
     * - @ref RM_MOTOR_INDUCTION_AngleGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_angle_rad  Pointer to get the rotor angle [rad]
     */
    fsp_err_t (* angleGet)(motor_ctrl_t * const p_ctrl, float * const p_angle_rad);

    /** Get the rotation speed.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_SpeedGet()
     * - @ref RM_MOTOR_ENCODER_SpeedGet()
     * - @ref RM_MOTOR_120_DEGREE_SpeedGet()
     * - @ref RM_MOTOR_INDUCTION_SpeedGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_speed_rpm  Pointer to get the rotation speed [rpm]
     */
    fsp_err_t (* speedGet)(motor_ctrl_t * const p_ctrl, float * const p_speed_rpm);

    /** Get wait stop flag.
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_WaitStopFlagGet()
     * - @ref RM_MOTOR_ENCODER_WaitStopFlagGet()
     * - @ref RM_MOTOR_120_DEGREE_WaitStopFlagGet()
     * - @ref RM_MOTOR_INDUCTION_WaitStopFlagGet()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[out] p_flag              Pointer to wait stop flag
     */
    fsp_err_t (* waitStopFlagGet)(motor_ctrl_t * const p_ctrl, motor_wait_stop_flag_t * const p_flag);

    /** Check the error occurrence
     * @par Implemented as
     * - @ref RM_MOTOR_SENSORLESS_ErrorCheck()
     * - @ref RM_MOTOR_ENCODER_ErrorCheck()
     * - @ref RM_MOTOR_120_DEGREE_ErrorCheck()
     * - @ref RM_MOTOR_INDUCTION_ErrorCheck()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_error      Pointer to get occured error
     */
    fsp_err_t (* errorCheck)(motor_ctrl_t * const p_ctrl, uint16_t * const p_error);

    /** FunctionSelect.
     * @par Implemented as
     * - @ref RM_MOTOR_ENCODER_FunctionSelect()
     * - @ref RM_MOTOR_INDUCTION_FunctionSelect()
     * - @ref RM_MOTOR_SENSORLESS_FunctionSelect()
     * - @ref RM_MOTOR_HALL_FunctionSelect()
     * - @ref RM_MOTOR_120_DEGREE_FunctionSelect()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[in]  function            Selected function
     */
    fsp_err_t (* functionSelect)(motor_ctrl_t * const p_ctrl, motor_function_select_t const function);
} motor_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_instance
{
    motor_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    motor_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    motor_api_t const * p_api;         ///< Pointer to the API structure for this instance
} motor_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_API_H */
