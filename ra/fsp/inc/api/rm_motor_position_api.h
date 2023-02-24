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
 * @defgroup MOTOR_POSITION_API Motor position Interface
 * @brief Interface for motor position functions.
 *
 * @section MOTOR_POSITION_API_Summary Summary
 * The Motor position interface for getting the speed references from Encoder Sensor
 *
 * The motor position interface can be implemented by:
 * - @ref MOTOR_POSITION
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_MOTOR_POSITION_API_H
#define RM_MOTOR_POSITION_API_H

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
#define MOTOR_POSITION_API_VERSION_MAJOR    (1U)
#define MOTOR_POSITION_API_VERSION_MINOR    (0U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Position Control Mode */
typedef enum  e_motor_position_ctrl_mode
{
    MOTOR_POSITION_CTRL_MODE_CONSTANT = 0,
    MOTOR_POSITION_CTRL_MODE_TRAPEZOID,
    MOTOR_POSITION_CTRL_MODE_STEP,
} motor_position_ctrl_mode_t;

/** Position information */
typedef struct e_motor_position_info
{
    uint8_t u1_state_position_profile; ///< Position control profile state
    int16_t s2_position_degree;        ///< Position data [degree]
} motor_position_info_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - motor_position_ctrl_t
 */
typedef void motor_position_ctrl_t;

/** Configuration parameters. */
typedef struct st_motor_position_cfg
{
    void const * p_context;            ///< Placeholder for user data.
    void const * p_extend;
} motor_position_cfg_t;

/** Functions implemented at the HAL layer will follow these APIs. */
typedef struct st_motor_position_api
{
    /** Initialize the Motor Position Module.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(motor_position_ctrl_t * const p_ctrl, motor_position_cfg_t const * const p_cfg);

    /** Close (Finish) the Motor Position Module.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(motor_position_ctrl_t * const p_ctrl);

    /** Reset(Stop) the Motor Position Module.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_Reset()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* reset)(motor_position_ctrl_t * const p_ctrl);

    /** Get Position data.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_PositionGet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_position       Pointer to get position data
     */
    fsp_err_t (* positionGet)(motor_position_ctrl_t * const p_ctrl, int16_t * const p_position);

    /** Set Position data from Encoder.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_PositionSet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  position_rad     Position data [radian]
     */
    fsp_err_t (* positionSet)(motor_position_ctrl_t * const p_ctrl, float const position_rad);

    /** Set (Input) Position reference into the Motor Position Module.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_PositionReferenceSet()
     *
     * @param[in]  p_ctrl                 Pointer to control structure.
     * @param[in]  position_refernce_deg  Position reference [degree]
     */
    fsp_err_t (* positionReferenceSet)(motor_position_ctrl_t * const p_ctrl, int16_t const position_reference_deg);

    /** Set (Input) Position Control Mode.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_ControlModeSet()
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  mode     Position Control Mode
     */
    fsp_err_t (* controlModeSet)(motor_position_ctrl_t * const p_ctrl, motor_position_ctrl_mode_t const mode);

    /** Calculate internal position reference
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_PositionControl()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* positionControl)(motor_position_ctrl_t * const p_ctrl);

    /** Calculate iq reference
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_IpdSpeedPControl()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  ref_speed_rad    Speed Reference [rad/sec]
     * @param[in]  speed_rad        Current Speed [rad/sec]
     * @param[out] p_iq_ref         Pointer to get iq reference
     */
    fsp_err_t (* ipdSpeedPControl)(motor_position_ctrl_t * const p_ctrl, float const ref_speed_rad,
                                   float const speed_rad, float * const p_iq_ref);

    /** Get Speed Reference by P Control
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_SpeedReferencePControlGet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_speed_ref      Pointer to get speed reference
     */
    fsp_err_t (* speedReferencePControlGet)(motor_position_ctrl_t * const p_ctrl, float * const p_speed_ref);

    /** Get Speed Reference by IPD Control
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_SpeedReferenceIpdControlGet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_speed_ref      Pointer to get speed reference
     */
    fsp_err_t (* speedReferenceIpdControlGet)(motor_position_ctrl_t * const p_ctrl, float const max_speed_rad,
                                              float * const p_speed_ref);

    /** Get Speed Reference by Speed Feedforward
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_SpeedReferenceFeedforwardGet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_speed_ref      Pointer to get speed reference
     */
    fsp_err_t (* speedReferenceFeedforwardGet)(motor_position_ctrl_t * const p_ctrl, float * const p_speed_ref);

    /** Get Position information.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_InfoGet()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_info           Pointer to get information
     */
    fsp_err_t (* infoGet)(motor_position_ctrl_t * const p_ctrl, motor_position_info_t * const p_info);

    /** Update Parameters for the calculation in the Motor Position Module.
     * @par Implemented as
     * - @ref RM_MOTOR_POSITION_ParameterUpdate()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure include update parameters.
     */
    fsp_err_t (* parameterUpdate)(motor_position_ctrl_t * const p_ctrl, motor_position_cfg_t const * const p_cfg);
} motor_position_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_motor_position_instance
{
    motor_position_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    motor_position_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    motor_position_api_t const * p_api;  ///< Pointer to the API structure for this instance
} motor_position_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_POSITION_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_MOTOR_POSITION_API_H */
