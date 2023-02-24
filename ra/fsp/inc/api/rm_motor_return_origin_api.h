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
 * @defgroup MOTOR_RETURN_ORIGIN_API Motor Return Origin Function Interface
 * @brief Interface for Motor return origin functions.
 *
 * @section MOTOR_RETURN_ORIGIN_API_Summary Summary
 * The Motor interface provides Motor return origin functionality.
 *
 * Implemented by:
 * - @ref MOTOR_RETURN_ORIGIN
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
 * @par Implemented as
 * - motor_return_origin_instance_ctrl_t
 */
typedef void motor_return_origin_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_return_origin_cfg
{
    motor_return_origin_mode_t mode;

    void const * p_context;
    void const * p_extend;             ///< Placeholder for user extension.
} motor_return_origin_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_motor_return_origin_api
{
    /** Open driver.
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_return_origin_ctrl_t * const p_ctrl, motor_return_origin_cfg_t const * const p_cfg);

    /** Close driver.
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Start the function.
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_Start()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* start)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Stop the function. (Cancel the function works.)
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_Stop()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* stop)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Reset the function. (Initialize the function.)
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_Reset()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Get the function information.
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_InfoGet()
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[out] p_info   Pointer to info
     */
    fsp_err_t (* infoGet)(motor_return_origin_ctrl_t * const p_ctrl, motor_return_origin_info_t * const p_info);

    /** Set the data to the function
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_DataSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_set_data   Pointer to set the data
     */
    fsp_err_t (* dataSet)(motor_return_origin_ctrl_t * const p_ctrl, motor_return_origin_set_data_t * const p_set_data);

    /** Speed cyclic process of the function
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_SpeedCyclic()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* speedCyclic)(motor_return_origin_ctrl_t * const p_ctrl);

    /** Update parameters for the function.
     * @par Implemented as
     * - @ref RM_MOTOR_RETURN_ORIGIN_ParameterUpdate()
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
