/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @defgroup MOTOR_SPEED_API Motor speed Interface
 * @brief Interface for motor speed functions.
 *
 * @section MOTOR_SPEED_API_Summary Summary
 * The Motor speed interface for getting the current references from electric current and rotational speed
 *
 * The motor speed interface can be implemented by:
 * - @ref MOTOR_SPEED
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_SPEED_API_H
#define RM_MOTOR_SPEED_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MOTOR_SPEED_API_VERSION_MAJOR    (1U) // DEPRECATED
#define MOTOR_SPEED_API_VERSION_MINOR    (0U) // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_motor_speed_event
{
    MOTOR_SPEED_EVENT_FORWARD = 1,     ///< Event forward Speed Control
    MOTOR_SPEED_EVENT_BACKWARD,        ///< Event backward Speed Control
} motor_speed_event_t;

/** Callback function parameter data */
typedef struct st_rm_motor_speed_callback_args
{
    void const        * p_context;     ///< Placeholder for user data.
    motor_speed_event_t event;
} motor_speed_callback_args_t;

/* Structure of input parameters */
typedef struct st_motor_speed_input
{
    float f_id;                        ///< D-axis current [A]
    float f_iq;                        ///< Q-axis current [A]
    float f_vamax;
    float f_speed_rad;                 ///< Speed value [rad/s]

    float f_ed;                        ///< Estimated d-axis component[V] of flux due to the permanent magnet
    float f_eq;                        ///< Estimated q-axis component[V] of flux due to the permanent magnet
    float f_phase_err_rad;             ///< Phase Error [rad]

    uint8_t u1_flag_get_iref;          ///< Flag to set d/q-axis current reference
} motor_speed_input_t;

/* Structure of output parameters */
typedef struct st_motor_speed_output
{
    float f_id_ref;                    ///< D-axis current reference [A] for calculation
    float f_iq_ref;                    ///< Q-axis current reference [A] for calculation

    float f_ref_speed_rad_ctrl;        ///< Command speed value for speed PI control[rad/s]
    float f_damp_comp_speed;           ///< The speed for open-loop damping

    uint8_t u1_flag_pi;                ///< PI output started flag
} motor_speed_output_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - motor_speed_ctrl_t
 */
typedef void motor_speed_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_speed_cfg
{
    motor_speed_input_t  * st_input;   ///< Input data structure for automatic set
    motor_speed_output_t * st_output;  ///< Output data structure for automatic receive

    timer_instance_t const * p_timer_instance;

    /* Callback function to perform at cyclic timer interrupt */
    void (* p_callback)(motor_speed_callback_args_t * p_args);
    void const * p_context;            ///< Placeholder for user data.

    void const * p_extend;
} motor_speed_cfg_t;

/** Functions implemented at the HAL layer will follow these APIs. */
typedef struct st_motor_speed_api
{
    /** Initialize the Motor Speed Module.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_speed_ctrl_t * const p_ctrl, motor_speed_cfg_t const * const p_cfg);

    /** Close (Finish) the Motor Speed Module.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_speed_ctrl_t * const p_ctrl);

    /** Reset(Stop) the Motor Speed Module.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_Reset()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_speed_ctrl_t * const p_ctrl);

    /** Activate the Motor Speed Control.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_Run()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* run)(motor_speed_ctrl_t * const p_ctrl);

    /** Set (Input) Speed reference into the Motor Speed Module.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_SpeedReferenceSet()
     *
     * @param[in]  p_ctrl              Pointer to control structure.
     * @param[in]  speed_refernce_rpm  Speed reference [rpm]
     */
    fsp_err_t (* speedReferenceSet)(motor_speed_ctrl_t * const p_ctrl, float const speed_reference_rpm);

    /** Set (Input) Speed Parameters into the Motor Speed Module.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_ParameterSet()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[in]  p_st_input     Pointer to structure to input parameters.
     */
    fsp_err_t (* parameterSet)(motor_speed_ctrl_t * const p_ctrl, motor_speed_input_t const * const p_st_input);

    /** Calculate Current Reference
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_SpeedControl()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* speedControl)(motor_speed_ctrl_t * const p_ctrl);

    /** Get Speed Control Output Parameters
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_ParameterGet()
     *
     * @param[in]  p_ctrl         Pointer to control structure.
     * @param[out] p_st_output    Pointer to get speed control parameters
     */
    fsp_err_t (* parameterGet)(motor_speed_ctrl_t * const p_ctrl, motor_speed_output_t * const p_st_output);

    /** Update Parameters for the calculation in the Motor Speed Module.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_ParameterUpdate()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_speed_ctrl_t * const p_ctrl, motor_speed_cfg_t const * const p_cfg);

    /* DEPRECATED Return the version of the driver.
     * @par Implemented as
     * - @ref RM_MOTOR_SPEED_VersionGet()
     *
     * @param[out] p_version    Memory address to return version information to.
     */
    fsp_err_t (* versionGet)(fsp_version_t * const p_version);
} motor_speed_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_speed_instance
{
    motor_speed_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance
    motor_speed_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance
    motor_speed_api_t const * p_api;   ///< Pointer to the API structure for this instance
} motor_speed_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SPEED_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_SPEED_API_H */
