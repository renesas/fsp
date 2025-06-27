/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MOTOR_INTERFACES
 * @defgroup MOTOR_INERTIA_ESTIMATE_API Motor Inertia Estimate Interface
 * @brief Interface for Motor inertia estimate functions.
 *
 * @section MOTOR_INERTIA_ESTIMATE_API_Summary Summary
 * The Motor interface provides Motor inertia estimate functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_INERTIA_ESTIMATE_API_H
#define RM_MOTOR_INERTIA_ESTIMATE_API_H

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

/* Internal mode */
typedef enum e_motor_inertia_estimate_mode
{
    MOTOR_INERTIA_ESTIMATE_MODE_START = 0,
    MOTOR_INERTIA_ESTIMATE_MODE_WAIT,
    MOTOR_INERTIA_ESTIMATE_MODE_FORWARD,
    MOTOR_INERTIA_ESTIMATE_MODE_REVERSE,
    MOTOR_INERTIA_ESTIMATE_MODE_CALCULATE,
    MOTOR_INERTIA_ESTIMATE_MODE_FINISH,
    MOTOR_INERTIA_ESTIMATE_MODE_ERROR,
} motor_inertia_estimate_mode_t;

/** Interface data structure */
typedef struct st_motor_inertia_estimate_info
{
    int16_t s2_position_reference_degree; ///< Position reference [degree]
    motor_inertia_estimate_mode_t mode;   ///< Internal mode of inertia estimation
    float f_estimated_inertia;            ///< Estimated inertia data
} motor_inertia_estimate_info_t;

typedef struct st_motor_inertia_estimate_set_data
{
    float   f_iq;                      ///< q-axis current data
    float   f_speed_radian_control;    ///< Speed information
    int16_t s2_position_degree;        ///< Rotor position [degree]
    uint8_t u1_position_state;         ///< State of position control (0:STEADY 1:TRANSITION)
} motor_inertia_estimate_set_data_t;

/** Motor inertia estimate block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void motor_inertia_estimate_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_inertia_estimate_cfg
{
    void       * p_context;
    void const * p_extend;             ///< Placeholder for user extension.
} motor_inertia_estimate_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_motor_inertia_estimate_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_inertia_estimate_ctrl_t * const p_ctrl, motor_inertia_estimate_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_inertia_estimate_ctrl_t * const p_ctrl);

    /** Start the function.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* start)(motor_inertia_estimate_ctrl_t * const p_ctrl);

    /** Stop( same as cancel ) the function.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* stop)(motor_inertia_estimate_ctrl_t * const p_ctrl);

    /** Reset the function. (recover from error state)
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_inertia_estimate_ctrl_t * const p_ctrl);

    /** Get information from the function (to set speed & position control)
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_info       Pointer to information
     */
    fsp_err_t (* infoGet)(motor_inertia_estimate_ctrl_t * const p_ctrl, motor_inertia_estimate_info_t * const p_info);

    /** Set the data to the function (from speed, position and current control)
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_set_data   Pointer to set the data
     */
    fsp_err_t (* dataSet)(motor_inertia_estimate_ctrl_t * const     p_ctrl,
                          motor_inertia_estimate_set_data_t * const p_set_data);

    /** Speed cyclic process of the function
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* speedCyclic)(motor_inertia_estimate_ctrl_t * const p_ctrl);

    /** Current cyclic process of the function
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* currentCyclic)(motor_inertia_estimate_ctrl_t * const p_ctrl);

    /** Update parameters for the function.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_inertia_estimate_ctrl_t * const p_ctrl,
                                  motor_inertia_estimate_cfg_t const  * p_cfg);
} motor_inertia_estimate_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_inertia_estimate_instance
{
    motor_inertia_estimate_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    motor_inertia_estimate_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    motor_inertia_estimate_api_t const * p_api;  ///< Pointer to the API structure for this instance
} motor_inertia_estimate_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_INERTIA_ESTIMATE_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_INERTIA_ESTIMATE_API_H */
