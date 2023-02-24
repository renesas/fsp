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
 * @defgroup MOTOR_CURRENT_API Motor current Interface
 * @brief Interface for motor current functions.
 *
 * @section MOTOR_CURRENT_API_Summary Summary
 * The Motor current interface for getting the PWM modulation duty from electric current and speed
 *
 * The motor current control interface can be implemented by:
 * - @ref MOTOR_CURRENT
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_CURRENT_API_H
#define RM_MOTOR_CURRENT_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "rm_motor_driver_api.h"
#include "rm_motor_angle_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_motor_current_event
{
    MOTOR_CURRENT_EVENT_FORWARD = 1,   ///< Event forward current control
    MOTOR_CURRENT_EVENT_DATA_SET,      ///< Event set speed control output data
    MOTOR_CURRENT_EVENT_BACKWARD,      ///< Event backward current control
} motor_current_event_t;

typedef struct st_motor_current_callback_args
{
    void const          * p_context;
    motor_current_event_t event;
} motor_current_callback_args_t;

/** Structure of interface to speed control */
/** Output parameters */
typedef struct st_motor_current_output
{
    float f_id;                        ///< D-axis current [A]
    float f_iq;                        ///< Q-axis current [A]
    float f_vamax;
    float f_speed_rad;                 ///< Speed value [rad/s]
    float f_speed_rpm;                 ///< Speed value [rpm]
    float f_rotor_angle;               ///< Motor rotor angle [rad]
    float f_position_rad;              ///< Motor rotor position [rad]

    float f_ed;                        ///< Estimated d-axis component[V] of flux due to the permanent magnet
    float f_eq;                        ///< Estimated q-axis component[V] of flux due to the permanent magnet
    float f_phase_err_rad;             ///< Phase error [rad]

    uint8_t u1_flag_get_iref;          ///< Flag to set d/q-axis current reference

    /* Encoder interface */
    uint8_t u1_adjust_status;          ///< Angle adjustment satatus
    uint8_t u1_adjust_count_full;      ///< Angle adjustment count full

    /* Induction sensor adjustment interface */
    uint8_t u1_openloop_status;        ///< Openloop status
    float   f_openloop_speed;          ///< Openloop speed
    float   f_openloop_id_ref;         ///< Openloop d-axis current
} motor_current_output_t;

/* Input parameters */
typedef struct st_motor_current_input
{
    float f_id_ref;                    ///< D-axis current reference [A] for calculation
    float f_iq_ref;                    ///< Q-axis current reference [A] for calculation

    float f_ref_speed_rad_ctrl;        ///< Command speed value for speed PI control[rad/s]
    float f_damp_comp_speed;           ///< The speed for open-loop damping

    uint8_t u1_flag_pi;                ///< PI output started flag
} motor_current_input_t;

/** Three-phase input current */
typedef struct st_motor_current_input_current
{
    float iu;                          ///< U phase current[A]
    float iv;                          ///< V phase current[A]
    float iw;                          ///< W phase current[A]
} motor_current_input_current_t;

/** Input voltage */
typedef struct st_motor_current_input_voltage
{
    float vdc;                         ///< Main line voltage[V]
    float va_max;                      ///< Maximum magnitude of voltage vector[V]
} motor_current_input_voltage_t;

/** Struct to get motor current */
typedef struct st_motor_current_get_voltage
{
    float u_voltage;                   ///< U phase voltage[V]
    float v_voltage;                   ///< V phase voltage[V]
    float w_voltage;                   ///< W phase voltage[V]
    float vd_reference;                ///< d-axis voltage reference
    float vq_reference;                ///< q-axis voltage reference
} motor_current_get_voltage_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - motor_current_ctrl_t
 */
typedef void motor_current_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_current_cfg
{
    /* Motor Driver Access Module */
    motor_driver_instance_t const * p_motor_driver_instance;

    /* Motor Angle Module */
    motor_angle_instance_t const * p_motor_angle_instance;

    /* Callback function */
    void (* p_callback)(motor_current_callback_args_t * p_args);
    void const * p_context;

    void const * p_extend;
} motor_current_cfg_t;

/** Functions implemented at the Motor Current Module will follow these APIs. */
typedef struct st_motor_current_api
{
    /** Initialize the motor current module.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_current_ctrl_t * const p_ctrl, motor_current_cfg_t const * const p_cfg);

    /** Close (Finish) the motor current module.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_current_ctrl_t * const p_ctrl);

    /** Reset variables for the motor current module.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_Reset()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_current_ctrl_t * const p_ctrl);

    /** Activate the motor current control.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_Run()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* run)(motor_current_ctrl_t * const p_ctrl);

    /** Set (Input) parameters into the motor current module.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_ParameterSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_st_input   Pointer to input data structure(speed control output data)
     */
    fsp_err_t (* parameterSet)(motor_current_ctrl_t * const p_ctrl, motor_current_input_t const * const p_st_input);

    /** Set (Input) Current reference into the motor current module.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_CurrentReferenceSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  id_reference D-axis current reference [A]
     * @param[in]  iq_reference Q-axis current reference [A]
     */
    fsp_err_t (* currentReferenceSet)(motor_current_ctrl_t * const p_ctrl, float const id_reference,
                                      float const iq_reference);

    /** Set (Input) Speed & Phase data into the motor current module.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_SpeedPhaseSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  speed_rad    Rotational speed [rad/s]
     * @param[in]  phase_rad    Rotor phase [rad]
     */
    fsp_err_t (* speedPhaseSet)(motor_current_ctrl_t * const p_ctrl, float const speed_rad, float const phase_rad);

    /** Set (Input) Current data into the motor current module.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_CurrentSet()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  p_st_current  Pointer to input current structure
     * @param[in]  p_st_voltage  Pointer to input voltage structure
     */
    fsp_err_t (* currentSet)(motor_current_ctrl_t * const                p_ctrl,
                             motor_current_input_current_t const * const p_st_current,
                             motor_current_input_voltage_t const * const p_st_voltage);

    /** Get (output) parameters from the motor current module
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_ParameterGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_st_output  Pointer to output data structure(speed control input data)
     */
    fsp_err_t (* parameterGet)(motor_current_ctrl_t * const p_ctrl, motor_current_output_t * const p_st_output);

    /** Get d/q-axis current
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_CurrentGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_id         Pointer to get d-axis current [A]
     * @param[out] p_iq         Pointer to get q-axis current [A]
     */
    fsp_err_t (* currentGet)(motor_current_ctrl_t * const p_ctrl, float * const p_id, float * const p_iq);

    /** Get phase output voltage
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_PhaseVoltageGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_voltage    Pointer to get voltages
     */
    fsp_err_t (* phaseVoltageGet)(motor_current_ctrl_t * const p_ctrl, motor_current_get_voltage_t * const p_voltage);

    /** Update parameters for the calculation in the motor current control.
     * @par Implemented as
     * - @ref RM_MOTOR_CURRENT_ParameterUpdate()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_current_ctrl_t * const p_ctrl, motor_current_cfg_t const * const p_cfg);
} motor_current_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_current_instance
{
    motor_current_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    motor_current_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    motor_current_api_t const * p_api;  ///< Pointer to the API structure for this instance
} motor_current_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_CURRENT_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_CURRENT_API_H */
