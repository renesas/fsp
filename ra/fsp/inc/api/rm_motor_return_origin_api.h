/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MOTOR_INTERFACES
 * @defgroup MOTOR_RETURN_ORIGIN_API Motor Return Origin Function Interface
 * @brief Interface for Motor return origin functions.
 *
 * @section MOTOR_RETURN_ORIGIN_API_Summary Summary
 * The Motor interface provides Motor return origin functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_RETURN_ORIGIN_API_H
#define RM_MOTOR_RETURN_ORIGIN_API_H

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

/** Selection type of return origin function */
typedef enum  e_motor_return_origin_mode
{
    MOTOR_RETURN_ORIGIN_MODE_PUSH = 1, ///< Return origin position with pushing
    MOTOR_RETURN_ORIGIN_MODE_SENSOR,   ///< Return origin position with origin sensor
    MOTOR_RETURN_ORIGIN_MODE_2_SENSOR, ///< Return origin position with 2 sensors
    MOTOR_RETURN_ORIGIN_MODE_3_SENSOR, ///< Return origin position with 3 sensors
} motor_return_origin_mode_t;

/* Internal state */
typedef enum e_motor_return_origin_state
{
    MOTOR_RETURN_ORIGIN_STATE_NONE = 0,
    MOTOR_RETURN_ORIGIN_STATE_START,
    MOTOR_RETURN_ORIGIN_STATE_SEARCH_STOPPER,
    MOTOR_RETURN_ORIGIN_STATE_REVERSE,
    MOTOR_RETURN_ORIGIN_STATE_DECELERATE,
    MOTOR_RETURN_ORIGIN_STATE_DONE,
    MOTOR_RETURN_ORIGIN_STATE_ERROR,
} motor_return_origin_state_t;

/** Interface data structure */
typedef struct st_motor_return_origin_info
{
    float f_position_reference_degree; ///< Position reference [degree]
    motor_return_origin_state_t state; // < Function state
    float f_result_angle;              ///< Result angle position
} motor_return_origin_info_t;

typedef struct st_motor_return_origin_set_data
{
    float f_iq;                        ///< q-axis current data
    float f_position_degree;           ///< Rotor position [degree]
} motor_return_origin_set_data_t;

/** Motor return origin function block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void motor_return_origin_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_return_origin_cfg
{
    motor_return_origin_mode_t mode;

    void       * p_context;
    void const * p_extend;             ///< Placeholder for user extension.
} motor_return_origin_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_motor_return_origin_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_return_origin_ctrl_t * const p_ctrl, motor_return_origin_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Start the function.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* start)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Stop the function. (Cancel the function works.)
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* stop)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Reset the function. (Initialize the function.)
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Get the function information.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[out] p_info   Pointer to info
     */
    fsp_err_t (* infoGet)(motor_return_origin_ctrl_t * const p_ctrl, motor_return_origin_info_t * const p_info);

    /** Set the data to the function
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_set_data   Pointer to set the data
     */
    fsp_err_t (* dataSet)(motor_return_origin_ctrl_t * const p_ctrl, motor_return_origin_set_data_t * const p_set_data);

    /** Speed cyclic process of the function
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* speedCyclic)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Update parameters for the function.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_return_origin_ctrl_t * const p_ctrl, motor_return_origin_cfg_t const * p_cfg);
} motor_return_origin_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_return_origin_instance
{
    motor_return_origin_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    motor_return_origin_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    motor_return_origin_api_t const * p_api;  ///< Pointer to the API structure for this instance
} motor_return_origin_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_RETURN_ORIGIN_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_RETURN_ORIGIN_API_H */
