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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <math.h>
#include <stdint.h>
#include "rm_motor_position.h"
#include "rm_motor_position_library.h"
#include "bsp_api.h"
#include "bsp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_POSITION_OPEN                      (0X4D504F53L)

#define     MOTOR_POSITION_LIMIT                     ((32767.0F * MOTOR_POSITION_TWOPI) / 360.0F) /* position limit */

/* reference position profiling mode */
#define     MOTOR_POSITION_CTRL_TRIANGLE             (0)
#define     MOTOR_POSITION_CTRL_TRAPEZOIDAL          (1)

/* position status */
#define     MOTOR_POSITION_STEADY_STATE              (0)
#define     MOTOR_POSITION_TRANSITION_STATE          (1)

#define     MOTOR_POSITION_PROFILE_MULTIPLE_TWO      (2.0F)
#define     MOTOR_POSITION_PROFILE_MULTIPLE_THREE    (3.0F)
#define     MOTOR_POSITION_PROFILE_HALF              (0.5F)

#ifndef MOTOR_POSITION_ERROR_RETURN

 #define    MOTOR_POSITION_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void  motor_position_control_init(motor_position_variables_t * st_pc);
static void  motor_position_set_reference_position(motor_position_variables_t * st_pc, int16_t s2_ref_position_deg);
static float motor_position_p_ctrl(motor_position_variables_t       * st_pc,
                                   motor_position_motor_parameter_t * st_motor,
                                   float                              f4_pos_err_rad);
static float motor_position_speed_feedforward(motor_position_instance_ctrl_t * p_ctrl,
                                              float                            f4_speed_ff_rad,
                                              float                            f4_speed_ref_calc_rad,
                                              unsigned short                   u2_mtr_pp);
static float motor_position_deadband_set(motor_position_instance_ctrl_t * p_ctrl, float f4_dead_band);

/* for Position Profiling */
static void motor_position_profiling_init(motor_position_profiling_t         * st_pf,
                                          motor_position_profiling_setting_t * setting);
static void  motor_position_profiling_reset(motor_position_profiling_t * st_pf);
static float motor_position_speed_profile_feed_forward(motor_position_profiling_t * st_pf);
static float motor_position_profile(motor_position_instance_ctrl_t * p_ctrl);
static float motor_position_triangle(motor_position_profiling_t * st_pf);
static float motor_position_trapezoid(motor_position_profiling_t * st_pf);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_position_api_t g_motor_position_on_motor_position =
{
    .open                         = RM_MOTOR_POSITION_Open,
    .close                        = RM_MOTOR_POSITION_Close,
    .reset                        = RM_MOTOR_POSITION_Reset,
    .positionGet                  = RM_MOTOR_POSITION_PositionGet,
    .positionSet                  = RM_MOTOR_POSITION_PositionSet,
    .positionReferenceSet         = RM_MOTOR_POSITION_PositionReferenceSet,
    .controlModeSet               = RM_MOTOR_POSITION_ControlModeSet,
    .positionControl              = RM_MOTOR_POSITION_PositionControl,
    .ipdSpeedPControl             = RM_MOTOR_POSITION_IpdSpeedPControl,
    .speedReferencePControlGet    = RM_MOTOR_POSITION_SpeedReferencePControlGet,
    .speedReferenceIpdControlGet  = RM_MOTOR_POSITION_SpeedReferenceIpdControlGet,
    .speedReferenceFeedforwardGet = RM_MOTOR_POSITION_SpeedReferenceFeedforwardGet,
    .infoGet                      = RM_MOTOR_POSITION_InfoGet,
    .parameterUpdate              = RM_MOTOR_POSITION_ParameterUpdate,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_POSITION
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the Motor Position Module. Implements @ref motor_position_api_t::open.
 *
 * @retval FSP_SUCCESS              Motor Position Module successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Set parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_Open (motor_position_ctrl_t * const p_ctrl, motor_position_cfg_t const * const p_cfg)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
#endif
    motor_position_extended_cfg_t * p_extended_cfg = (motor_position_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg);

    FSP_ERROR_RETURN(MOTOR_POSITION_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(0.0F <= p_extended_cfg->f_speed_ctrl_period, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->st_variable.f4_pos_rad = 0.0F;
    motor_position_control_init(&(p_instance_ctrl->st_variable));
    motor_position_ipd_ctrl_init(&(p_instance_ctrl->st_ipd), p_extended_cfg->ipd_lpf, &(p_extended_cfg->st_ipd_design));
    motor_position_profiling_init(&(p_instance_ctrl->st_profiling), &(p_extended_cfg->st_profiling_set));

    p_instance_ctrl->st_variable.f4_pos_kp = MOTOR_POSITION_TWOPI * p_extended_cfg->f_pos_omega;

    motor_position_ipd_ctrl_gain_calc(&(p_extended_cfg->st_motor),
                                      &(p_instance_ctrl->st_ipd),
                                      p_extended_cfg->f_pos_omega,
                                      p_extended_cfg->f_speed_ctrl_period);

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_POSITION_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified Motor Position Module. Implements @ref motor_position_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_Close (motor_position_ctrl_t * const p_ctrl)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->st_variable.f4_pos_rad = 0.0F;
    motor_position_control_init(&(p_instance_ctrl->st_variable));
    motor_position_ipd_ctrl_reset(&(p_instance_ctrl->st_ipd));
    motor_position_profiling_reset(&(p_instance_ctrl->st_profiling));

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset the variables of Motor Position Module. Implements @ref motor_position_api_t::reset
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_Reset (motor_position_ctrl_t * const p_ctrl)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_position_control_init(&(p_instance_ctrl->st_variable));
    motor_position_ipd_ctrl_reset(&(p_instance_ctrl->st_ipd));
    motor_position_profiling_reset(&(p_instance_ctrl->st_profiling));

    p_instance_ctrl->e_ctrl_mode = MOTOR_POSITION_CTRL_MODE_TRAPEZOID;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get Rotor Position Data [degree]. Implements @ref motor_position_api_t::positionGet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Output pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_PositionGet (motor_position_ctrl_t * const p_ctrl, int16_t * const p_position)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_POSITION_ERROR_RETURN(NULL != p_position, FSP_ERR_INVALID_ARGUMENT);
#endif

    *p_position = (int16_t) (p_instance_ctrl->st_variable.f4_pos_rad * MOTOR_POSITION_360_TWOPI);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set Position Data from Encoder [radian]. Implements @ref motor_position_api_t::positionSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_PositionSet (motor_position_ctrl_t * const p_ctrl, float const position_rad)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->st_variable.f4_pos_rad = position_rad;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set Position Reference Data [degree]. Implements @ref motor_position_api_t::positionReferenceSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_PositionReferenceSet (motor_position_ctrl_t * const p_ctrl,
                                                  int16_t const                 position_reference_deg)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_position_set_reference_position(&(p_instance_ctrl->st_variable), position_reference_deg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set Position Control Mode. Implements @ref motor_position_api_t::controlModeSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_ControlModeSet (motor_position_ctrl_t * const p_ctrl, motor_position_ctrl_mode_t const mode)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->e_ctrl_mode = mode;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculates internal position reference.(Main process of Position Control) Implements @ref motor_position_api_t::positionControl
 *
 * @retval FSP_SUCCESS              Successful data calculation.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_PositionControl (motor_position_ctrl_t * const p_ctrl)
{
    float f_temp;
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    switch (p_instance_ctrl->e_ctrl_mode)
    {
        case MOTOR_POSITION_CTRL_MODE_CONSTANT:
        {
            /* position zero constant */
            p_instance_ctrl->st_variable.f4_ref_pos_rad_ctrl = 0.0F;
            break;
        }

        case MOTOR_POSITION_CTRL_MODE_TRAPEZOID:
        {
            /* check reference position update */
            f_temp = p_instance_ctrl->st_variable.f4_ref_pos_pre_rad - p_instance_ctrl->st_variable.f4_ref_pos_rad;
            if ((f_temp > 0.0F) || (f_temp < 0.0F))
            {
                p_instance_ctrl->st_profiling.f4_pos_st_rad     = p_instance_ctrl->st_variable.f4_ref_pos_pre_rad;
                p_instance_ctrl->st_profiling.f4_pos_ed_rad     = p_instance_ctrl->st_variable.f4_ref_pos_rad;
                p_instance_ctrl->st_variable.f4_ref_pos_pre_rad = p_instance_ctrl->st_variable.f4_ref_pos_rad;
            }

            p_instance_ctrl->st_variable.f4_ref_pos_rad_ctrl =
                motor_position_profile(p_instance_ctrl);
            break;
        }

        case MOTOR_POSITION_CTRL_MODE_STEP:
        {
            p_instance_ctrl->st_variable.f4_ref_pos_rad_ctrl = p_instance_ctrl->st_variable.f4_ref_pos_rad;
            break;
        }

        default:
        {
            break;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculates the q-axis current reference by P control. Implements @ref motor_position_api_t::ipdSpeedPControl
 *
 * @retval FSP_SUCCESS              Successful data calculation.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Output pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_IpdSpeedPControl (motor_position_ctrl_t * const p_ctrl,
                                              float const                   ref_speed_rad,
                                              float const                   speed_rad,
                                              float * const                 p_iq_ref)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_POSITION_ERROR_RETURN(NULL != p_iq_ref, FSP_ERR_INVALID_ARGUMENT);
#endif

    *p_iq_ref = motor_position_ipd_speed_p_ctrl(&(p_instance_ctrl->st_ipd), ref_speed_rad, speed_rad);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get Speed Reference by P Control. Implements @ref motor_position_api_t::speedReferencePControlGet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Output pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_SpeedReferencePControlGet (motor_position_ctrl_t * const p_ctrl, float * const p_speed_ref)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_POSITION_ERROR_RETURN(NULL != p_speed_ref, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_position_extended_cfg_t * p_extended_cfg =
        (motor_position_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    p_instance_ctrl->st_variable.f4_pos_err_rad =
        p_instance_ctrl->st_variable.f4_ref_pos_rad_ctrl - p_instance_ctrl->st_variable.f4_pos_rad;
    p_instance_ctrl->st_variable.f4_pos_err_rad =
        motor_position_deadband_set(p_ctrl, p_instance_ctrl->st_variable.f4_pos_err_rad);
    *p_speed_ref = motor_position_p_ctrl(&(p_instance_ctrl->st_variable),
                                         &(p_extended_cfg->st_motor),
                                         p_instance_ctrl->st_variable.f4_pos_err_rad);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get Speed Reference by IPD Control. Implements @ref motor_position_api_t::speedReferenceIpdControlGet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Output pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_SpeedReferenceIpdControlGet (motor_position_ctrl_t * const p_ctrl,
                                                         float const                   max_speed_rad,
                                                         float * const                 p_speed_ref)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_POSITION_ERROR_RETURN(NULL != p_speed_ref, FSP_ERR_INVALID_ARGUMENT);
#endif
    motor_position_extended_cfg_t * p_extended_cfg =
        (motor_position_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    p_instance_ctrl->st_variable.f4_pos_err_rad =
        motor_position_ipd_error_calc(&(p_instance_ctrl->st_ipd),
                                      p_instance_ctrl->st_variable.f4_pos_rad,
                                      p_instance_ctrl->st_variable.f4_ref_pos_rad_ctrl);
    p_instance_ctrl->st_variable.f4_pos_err_rad =
        motor_position_deadband_set(p_ctrl, p_instance_ctrl->st_variable.f4_pos_err_rad);
    *p_speed_ref = motor_position_ipd_ctrl(&(p_instance_ctrl->st_ipd),
                                           &(p_extended_cfg->st_motor),
                                           p_instance_ctrl->st_variable.f4_pos_err_rad,
                                           max_speed_rad);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get Speed Reference by Feedforward. Implements @ref motor_position_api_t::speedReferenceFeedforwardGet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Output pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_SpeedReferenceFeedforwardGet (motor_position_ctrl_t * const p_ctrl,
                                                          float * const                 p_speed_ref)
{
    float f4_speed_ff_rad = 0.0F;
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_POSITION_ERROR_RETURN(NULL != p_speed_ref, FSP_ERR_INVALID_ARGUMENT);
#endif
    motor_position_extended_cfg_t * p_extended_cfg =
        (motor_position_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    float f_temp_speed_ref = *p_speed_ref;

    f4_speed_ff_rad = motor_position_speed_profile_feed_forward(&(p_instance_ctrl->st_profiling));
    *p_speed_ref    = motor_position_speed_feedforward(p_instance_ctrl,
                                                       f4_speed_ff_rad,
                                                       f_temp_speed_ref,
                                                       p_extended_cfg->st_motor.u2_mtr_pp);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get position information.
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Output pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_InfoGet (motor_position_ctrl_t * const p_ctrl, motor_position_info_t * const p_info)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_POSITION_ERROR_RETURN(NULL != p_info, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_info->u1_state_position_profile = p_instance_ctrl->st_profiling.u1_state_pos_pf;
    p_info->s2_position_degree        =
        (int16_t) (p_instance_ctrl->st_variable.f4_pos_rad * MOTOR_POSITION_360_TWOPI);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of Position Control Calculation. Implements @ref motor_position_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data was updated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Configuration parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_POSITION_ParameterUpdate (motor_position_ctrl_t * const      p_ctrl,
                                             motor_position_cfg_t const * const p_cfg)
{
    motor_position_instance_ctrl_t * p_instance_ctrl = (motor_position_instance_ctrl_t *) p_ctrl;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
    MOTOR_POSITION_ERROR_RETURN(MOTOR_POSITION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_position_extended_cfg_t * p_extended_cfg = (motor_position_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_POSITION_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(0.0F <= p_extended_cfg->f_speed_ctrl_period, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->st_variable.f4_pos_kp = MOTOR_POSITION_TWOPI * p_extended_cfg->f_pos_omega;

    motor_position_ipd_ctrl_init(&(p_instance_ctrl->st_ipd), p_extended_cfg->ipd_lpf, &(p_extended_cfg->st_ipd_design));
    motor_position_ipd_ctrl_gain_calc(&(p_extended_cfg->st_motor),
                                      &(p_instance_ctrl->st_ipd),
                                      p_extended_cfg->f_pos_omega,
                                      p_extended_cfg->f_speed_ctrl_period);
    motor_position_profiling_init(&(p_instance_ctrl->st_profiling), &(p_extended_cfg->st_profiling_set));

    p_instance_ctrl->p_cfg = p_cfg;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_POSITION)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : motor_position_control_init
 * Description   : Initialize variables when motor position control init
 * Arguments     : st_pc               - position control structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_position_control_init (motor_position_variables_t * st_pc)
{
    /* position control */
    st_pc->f4_ref_pos_rad      = 0.0F;
    st_pc->f4_ref_pos_pre_rad  = 0.0F;
    st_pc->f4_ref_pos_rad_ctrl = 0.0F;
    st_pc->f4_pos_err_rad      = 0.0F;
    st_pc->f4_speed_ff_rad     = 0.0F;
}                                      /* End of function motor_position_control_init */

/***********************************************************************************************************************
 * Function Name : motor_position_set_reference_position
 * Description   : Set position reference
 * Arguments     : st_pc               - position control structure (pointer)
 *                 s2_ref_position_deg - position reference [degree]
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_position_set_reference_position (motor_position_variables_t * st_pc, int16_t s2_ref_position_deg)
{
    st_pc->f4_ref_pos_rad = (float) s2_ref_position_deg * MOTOR_POSITION_TWOPI_360;
    if (MOTOR_POSITION_LIMIT <= st_pc->f4_ref_pos_rad)
    {
        st_pc->f4_ref_pos_rad = MOTOR_POSITION_LIMIT;
    }
    else if (-(MOTOR_POSITION_LIMIT + 1.0F) >= st_pc->f4_ref_pos_rad)
    {
        st_pc->f4_ref_pos_rad = -MOTOR_POSITION_LIMIT;
    }
    else
    {
        /* Do Nothing */
    }
}                                      /* End of function motor_position_set_reference_position */

/***********************************************************************************************************************
 * Function Name : motor_position_p_ctrl
 * Description   : Position Proportional control
 * Arguments     : st_pc          - position control structure (pointer)
 *               : st_motor       - motor parameter structure (pointer)
 *               : f4_pos_err_rad - position error [rad]
 * Return Value  : Speed reference [rad/s]
 **********************************************************************************************************************/
static float motor_position_p_ctrl (motor_position_variables_t       * st_pc,
                                    motor_position_motor_parameter_t * st_motor,
                                    float                              f4_pos_err_rad)
{
    float f4_speed_ref_calc_rad;

    f4_speed_ref_calc_rad = f4_pos_err_rad * st_pc->f4_pos_kp * st_motor->u2_mtr_pp;

    return f4_speed_ref_calc_rad;
}                                      /* End of function motor_position_p_ctrl */

/***********************************************************************************************************************
 * Function Name : motor_position_speed_feedforward
 * Description   : speed feed-forword control
 * Arguments     : st_pc           - position control structure (pointer)
 *                 f4_speed_ff_rad - feed forwarded speed [rad/s]
 *                 f4_ref_calc_rad - current speed reference [rad/s]
 *                 u2_mtr_pp       - Motor Pole Pairs
 * Return Value  : Speed reference [rad/s]
 **********************************************************************************************************************/
static float motor_position_speed_feedforward (motor_position_instance_ctrl_t * p_ctrl,
                                               float                            f4_speed_ff_rad,
                                               float                            f4_speed_ref_calc_rad,
                                               unsigned short                   u2_mtr_pp)
{
    float f4_temp0 = 0.0F;
    motor_position_extended_cfg_t * p_extended_cfg = (motor_position_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* speed feed-forward control */
    p_ctrl->st_variable.f4_speed_ff_rad = f4_speed_ff_rad;
    f4_temp0               = p_extended_cfg->f_speed_ff_ratio * p_ctrl->st_variable.f4_speed_ff_rad * u2_mtr_pp;
    f4_speed_ref_calc_rad += f4_temp0;

    return f4_speed_ref_calc_rad;
}                                      /* End of function motor_position_speed_feedforward */

/***********************************************************************************************************************
 * Function Name : motor_position_deadband_set
 * Description   : Set position dead-band
 * Arguments     : p_ctrl        - The pointer to position instance ctrl
 *               : f4_dead_band  - Dead band
 * Return Value  : None
 **********************************************************************************************************************/
static float motor_position_deadband_set (motor_position_instance_ctrl_t * p_ctrl, float f4_dead_band)
{
    float f4_temp0 = 0.0F;
    motor_position_extended_cfg_t * p_extended_cfg = (motor_position_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    f4_temp0 = fabsf(f4_dead_band);
    if ((float) p_extended_cfg->u2_pos_dead_band * p_extended_cfg->f_encd_angle_diff >= f4_temp0)
    {
        f4_dead_band = 0.0F;
    }

    return f4_dead_band;
}                                      /* End of function motor_position_deadband_set */

/* for Position Profiling */

/***********************************************************************************************************************
 * Function Name : motor_position_profiling_init
 * Description   : Initialize variables when motor position profiling init
 * Arguments     : st_pf  - position profiling structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_position_profiling_init (motor_position_profiling_t         * st_pf,
                                           motor_position_profiling_setting_t * setting)
{
    /* initialize member of position profiling structure */
    st_pf->u1_state_pos_pf         = MOTOR_POSITION_STEADY_STATE;
    st_pf->u1_pos_ref_mode         = MOTOR_POSITION_CTRL_TRIANGLE;
    st_pf->u2_interval_time        = setting->u2_interval_time;
    st_pf->u2_interval_time_buff   = setting->u2_interval_time;
    st_pf->f4_accel_time           = setting->f4_accel_time;
    st_pf->f4_accel_time_buff      = setting->f4_accel_time;
    st_pf->f4_accel_time_inv       = 1.0F / setting->f4_accel_time;
    st_pf->f4_accel_max_speed      = setting->f4_accel_max_speed * MOTOR_POSITION_TWOPI_60;
    st_pf->f4_accel_max_speed_buff = setting->f4_accel_max_speed * MOTOR_POSITION_TWOPI_60;
    st_pf->f4_max_accel_time       = st_pf->f4_accel_max_speed / setting->f4_max_accel;

    motor_position_profiling_reset(st_pf);
}                                      /* End of function motor_position_profiling_init */

/***********************************************************************************************************************
 * Function Name : motor_position_profiling_reset
 * Description   : Reset variables when motor control
 * Arguments     : st_pf  - position profiling structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_position_profiling_reset (motor_position_profiling_t * st_pf)
{
    /* position profiling structure */
    st_pf->f4_time_sec          = 0.0F;
    st_pf->u2_interval_time_cnt = 0U;
    st_pf->f4_pos_dt_rad        = 0.0F;
    st_pf->f4_pos_st_rad        = 0.0F;
    st_pf->f4_pos_ed_rad        = 0.0F;
    st_pf->f4_pos_dt_time_sec   = 0.0F;
}                                      /* End of function motor_position_profiling_reset */

/***********************************************************************************************************************
 * Function Name : motor_position_triangle
 * Description   : triangle profile for position reference
 *               : Acceleration does not reach the maximum speed
 *               : (f4_accel_max_ref_speed_rad * f4_accel_time) >= f4_pos_dt_rad
 * Arguments     : st_pf         - position profiling structure (pointer)
 * Return Value  : reference position
 **********************************************************************************************************************/
static float motor_position_triangle (motor_position_profiling_t * st_pf)
{
    float f4_temp0            = 0.0F;
    float f4_temp1            = 0.0F;
    float f4_temp2            = 0.0F;
    float f4_temp3            = 0.0F;
    float f4_ref_pos_rad_calc = 0.0F;

    if (st_pf->f4_time_sec <= st_pf->f4_accel_time)
    {
        f4_temp0            = st_pf->f4_time_sec * st_pf->f4_time_sec;
        f4_temp0            = st_pf->f4_accel_max_speed * f4_temp0;
        f4_temp1            = MOTOR_POSITION_PROFILE_HALF * st_pf->f4_accel_time_inv;
        f4_temp0            = f4_temp0 * f4_temp1;
        f4_ref_pos_rad_calc = f4_temp0 + st_pf->f4_pos_st_rad;
    }                                  /* rise section for triangle */
    else if ((st_pf->f4_time_sec > st_pf->f4_accel_time) &&
             (st_pf->f4_time_sec <= (MOTOR_POSITION_PROFILE_MULTIPLE_TWO * st_pf->f4_accel_time)))
    {
        f4_temp0            = MOTOR_POSITION_PROFILE_MULTIPLE_TWO * st_pf->f4_accel_max_speed;
        f4_temp0            = f4_temp0 * st_pf->f4_time_sec;
        f4_temp1            = st_pf->f4_time_sec * st_pf->f4_time_sec;
        f4_temp1            = st_pf->f4_accel_max_speed * f4_temp1;
        f4_temp2            = MOTOR_POSITION_PROFILE_HALF * st_pf->f4_accel_time_inv;
        f4_temp1            = -(f4_temp1 * f4_temp2);
        f4_temp2            = st_pf->f4_pos_dt_rad * MOTOR_POSITION_PROFILE_HALF;
        f4_temp3            = st_pf->f4_accel_max_speed * st_pf->f4_accel_time;
        f4_temp3            = MOTOR_POSITION_PROFILE_MULTIPLE_THREE * f4_temp3;
        f4_temp3            = -(f4_temp3 * MOTOR_POSITION_PROFILE_HALF);
        f4_ref_pos_rad_calc = f4_temp0 + f4_temp1 + f4_temp3 + f4_temp2 + st_pf->f4_pos_st_rad;
    }                                  /* reduce the speed */
    /* reach the target position */
    else if (st_pf->f4_time_sec > (MOTOR_POSITION_PROFILE_MULTIPLE_TWO * st_pf->f4_accel_time))
    {
        st_pf->f4_pos_st_rad = st_pf->f4_pos_ed_rad;
        f4_ref_pos_rad_calc  = st_pf->f4_pos_st_rad;
    }
    else
    {
        /* Do Nothing */
    }

    return f4_ref_pos_rad_calc;
}                                      /* End of function motor_position_triangle */

/***********************************************************************************************************************
 * Function Name : motor_position_trapezoid
 * Description   : trapezoid profile for position reference
 *               : Acceleration reach the maximum speed
 *               : (f4_accel_max_ref_speed_rad * f4_accel_time) <  f4_pos_dt_rad
 * Arguments     : st_pf         - position profiling structure (pointer)
 * Return Value  : reference position
 **********************************************************************************************************************/
static float motor_position_trapezoid (motor_position_profiling_t * st_pf)
{
    float f4_temp0            = 0.0F;
    float f4_temp1            = 0.0F;
    float f4_temp2            = 0.0F;
    float f4_temp3            = 0.0F;
    float f4_temp4            = 0.0F;
    float f4_temp5            = 0.0F;
    float f4_ref_pos_rad_calc = 0.0F;

    if (st_pf->f4_time_sec <= st_pf->f4_accel_time)
    {
        f4_temp0            = st_pf->f4_time_sec * st_pf->f4_time_sec;
        f4_temp0            = st_pf->f4_accel_max_speed * f4_temp0;
        f4_temp1            = MOTOR_POSITION_PROFILE_HALF * st_pf->f4_accel_time_inv;
        f4_temp0            = f4_temp0 * f4_temp1;
        f4_ref_pos_rad_calc = f4_temp0 + st_pf->f4_pos_st_rad;
    }                                  /* speed up */
    else if ((st_pf->f4_time_sec > st_pf->f4_accel_time) && (st_pf->f4_time_sec <= st_pf->f4_pos_dt_time_sec))
    {
        f4_temp0            = st_pf->f4_accel_max_speed * st_pf->f4_time_sec;
        f4_temp1            = st_pf->f4_accel_max_speed * st_pf->f4_accel_time;
        f4_temp1            = -(f4_temp1 * MOTOR_POSITION_PROFILE_HALF);
        f4_ref_pos_rad_calc = f4_temp0 + f4_temp1 + st_pf->f4_pos_st_rad;
    }                                  /* constant speed */
    else if ((st_pf->f4_time_sec > st_pf->f4_pos_dt_time_sec) &&
             (st_pf->f4_time_sec <= (st_pf->f4_pos_dt_time_sec + st_pf->f4_accel_time)))
    {
        f4_temp0            = st_pf->f4_accel_max_speed * st_pf->f4_time_sec;
        f4_temp1            = st_pf->f4_time_sec * st_pf->f4_time_sec;
        f4_temp1            = st_pf->f4_accel_max_speed * f4_temp1;
        f4_temp2            = MOTOR_POSITION_PROFILE_HALF * st_pf->f4_accel_time_inv;
        f4_temp1            = -(f4_temp1 * f4_temp2);
        f4_temp2            = st_pf->f4_pos_dt_rad * st_pf->f4_time_sec;
        f4_temp2            = f4_temp2 * st_pf->f4_accel_time_inv;;
        f4_temp3            = st_pf->f4_accel_max_speed * st_pf->f4_accel_time;
        f4_temp3            = -(f4_temp3 * MOTOR_POSITION_PROFILE_HALF);
        f4_temp4            = st_pf->f4_pos_dt_rad * st_pf->f4_pos_dt_rad;
        f4_temp5            = MOTOR_POSITION_PROFILE_HALF * st_pf->f4_accel_time_inv;
        f4_temp4            = -(f4_temp4 * f4_temp5) / st_pf->f4_accel_max_speed;
        f4_ref_pos_rad_calc = f4_temp0 + f4_temp1 + f4_temp2 + f4_temp3 + f4_temp4 + st_pf->f4_pos_st_rad;
    }                                  /* reduce the speed */
    else if (st_pf->f4_time_sec > (st_pf->f4_pos_dt_time_sec + st_pf->f4_accel_time))
    {
        st_pf->f4_pos_st_rad = st_pf->f4_pos_ed_rad;
        f4_ref_pos_rad_calc  = st_pf->f4_pos_st_rad;
    }                                  /* reach the target position */
    else
    {
        /* Do Nothing */
    }

    return f4_ref_pos_rad_calc;
}                                      /* End of function motor_position_trapezoid */

/***********************************************************************************************************************
 * Function Name : motor_position_speed_profile_feed_forward
 * Description   : trapezoid profile for speed feed-forward
 * Arguments     : st_pf         - position profiling structure (pointer)
 * Return Value  : reference speed (feed-forward)
 **********************************************************************************************************************/
static float motor_position_speed_profile_feed_forward (motor_position_profiling_t * st_pf)
{
    float f4_speed_ff_rad = 0.0F;
    float f4_temp0        = 0.0F;
    float f4_temp1        = 0.0F;

    /* speed feed-forward profile for triangle*/
    if (MOTOR_POSITION_CTRL_TRIANGLE == st_pf->u1_pos_ref_mode)
    {
        if (st_pf->f4_time_sec <= st_pf->f4_accel_time)
        {
            f4_speed_ff_rad = (st_pf->f4_accel_max_speed * st_pf->f4_time_sec) * st_pf->f4_accel_time_inv;
        }
        else if ((st_pf->f4_time_sec > st_pf->f4_accel_time) &&
                 (st_pf->f4_time_sec <= (MOTOR_POSITION_PROFILE_MULTIPLE_TWO * st_pf->f4_accel_time)))
        {
            f4_temp0        = (st_pf->f4_accel_max_speed * st_pf->f4_time_sec) * st_pf->f4_accel_time_inv;
            f4_speed_ff_rad = MOTOR_POSITION_PROFILE_MULTIPLE_TWO * st_pf->f4_accel_max_speed - f4_temp0;
        }
        else if (st_pf->f4_time_sec > (MOTOR_POSITION_PROFILE_MULTIPLE_TWO * st_pf->f4_accel_time))
        {
            f4_speed_ff_rad = 0.0F;
        }
        else
        {
            /* Do Nothing */
        }
    }
    /* speed feed-forward profile for trapezoidal*/
    else if (MOTOR_POSITION_CTRL_TRAPEZOIDAL == st_pf->u1_pos_ref_mode)
    {
        if (st_pf->f4_time_sec <= st_pf->f4_accel_time)
        {
            f4_speed_ff_rad = (st_pf->f4_accel_max_speed * st_pf->f4_time_sec) * st_pf->f4_accel_time_inv;
        }
        else if ((st_pf->f4_time_sec > st_pf->f4_accel_time) && (st_pf->f4_time_sec <= st_pf->f4_pos_dt_time_sec))
        {
            f4_speed_ff_rad = st_pf->f4_accel_max_speed;
        }
        else if ((st_pf->f4_time_sec > st_pf->f4_pos_dt_time_sec) &&
                 (st_pf->f4_time_sec <= (st_pf->f4_pos_dt_time_sec + st_pf->f4_accel_time)))
        {
            f4_temp0        = st_pf->f4_pos_dt_rad * st_pf->f4_accel_time_inv;
            f4_temp1        = (st_pf->f4_accel_max_speed * st_pf->f4_time_sec) * st_pf->f4_accel_time_inv;
            f4_speed_ff_rad = st_pf->f4_accel_max_speed + f4_temp0 - f4_temp1;
        }
        else if (st_pf->f4_time_sec > (st_pf->f4_pos_dt_time_sec + st_pf->f4_accel_time))
        {
            f4_speed_ff_rad = 0.0F;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    return f4_speed_ff_rad;
}                                      /* End of function motor_position_speed_profile_feed_forward */

/***********************************************************************************************************************
 * Function Name : motor_position_profile
 * Description   : position profile (trapezoid)
 * Arguments     : p_ctrl  - position control structure (pointer)
 * Return Value  : reference position
 **********************************************************************************************************************/
static float motor_position_profile (motor_position_instance_ctrl_t * p_ctrl)
{
    float f4_temp_diff        = 0.0F;
    float f4_temp0            = 0.0F;
    float f4_ref_pos_rad_calc = 0.0F;
    motor_position_profiling_t          * st_pf    = &(p_ctrl->st_profiling);
    motor_position_extended_cfg_t const * p_extend = p_ctrl->p_cfg->p_extend;

    f4_ref_pos_rad_calc = st_pf->f4_pos_st_rad;

    /* position control reference state - steady state */
    if (MOTOR_POSITION_STEADY_STATE == st_pf->u1_state_pos_pf)
    {
        f4_temp_diff = st_pf->f4_pos_st_rad - st_pf->f4_pos_ed_rad;
        if ((f4_temp_diff > 0.0F) || (f4_temp_diff < 0.0F))
        /* difference in reference position check */

        // if (st_pf->f4_pos_st_rad != st_pf->f4_pos_ed_rad)
        {
            /* update variables */
            st_pf->f4_accel_max_speed = st_pf->f4_accel_max_speed_buff;
            st_pf->f4_accel_time      = st_pf->f4_accel_time_buff;
            st_pf->f4_accel_time_inv  = 1.0F / st_pf->f4_accel_time;
            st_pf->u2_interval_time   = st_pf->u2_interval_time_buff;
            st_pf->f4_time_sec        = 0.0F;
            st_pf->f4_pos_dt_rad      = st_pf->f4_pos_ed_rad - st_pf->f4_pos_st_rad;
            f4_temp0 = fabsf(st_pf->f4_pos_dt_rad);
            st_pf->f4_pos_dt_time_sec = f4_temp0 / st_pf->f4_accel_max_speed;

            /* trapezoid mode check */
            if (st_pf->f4_accel_time * st_pf->f4_accel_max_speed >= f4_temp0)
            {
                st_pf->u1_pos_ref_mode    = MOTOR_POSITION_CTRL_TRIANGLE;
                st_pf->f4_accel_max_speed = st_pf->f4_pos_dt_rad * st_pf->f4_accel_time_inv;
            }
            else
            {
                st_pf->u1_pos_ref_mode    = MOTOR_POSITION_CTRL_TRAPEZOIDAL;
                st_pf->f4_accel_max_speed = copysignf(st_pf->f4_accel_max_speed, st_pf->f4_pos_dt_rad);
            }

            st_pf->u1_state_pos_pf = MOTOR_POSITION_TRANSITION_STATE;
        }
    }

    /* position control reference state - transition state */
    if (MOTOR_POSITION_TRANSITION_STATE == st_pf->u1_state_pos_pf)
    {
        if (MOTOR_POSITION_CTRL_TRIANGLE == st_pf->u1_pos_ref_mode)
        {
            /* profiling triangle position reference */
            f4_ref_pos_rad_calc = motor_position_triangle(st_pf);
        }
        else if (MOTOR_POSITION_CTRL_TRAPEZOIDAL == st_pf->u1_pos_ref_mode)
        {
            /* profiling trapezoid position reference */
            f4_ref_pos_rad_calc = motor_position_trapezoid(st_pf);
        }
        else
        {
            /* Do Nothing */
        }

        st_pf->f4_time_sec += p_extend->st_profiling_set.f4_timer_update_step;

        /* reach the target position */
        f4_temp_diff = st_pf->f4_pos_st_rad - st_pf->f4_pos_ed_rad;
        if ((f4_temp_diff > 0.0F) || (f4_temp_diff < 0.0F))
        {
        }
        else
        // if (st_pf->f4_pos_st_rad == st_pf->f4_pos_ed_rad)
        {
            /* Transition Interval Time */
            if (st_pf->u2_interval_time <= st_pf->u2_interval_time_cnt++)
            {
                st_pf->u2_interval_time_cnt = 0U;
                st_pf->u1_state_pos_pf      = MOTOR_POSITION_STEADY_STATE;
            }

            f4_ref_pos_rad_calc = st_pf->f4_pos_st_rad;
        }
    }

    return f4_ref_pos_rad_calc;
}                                      /* End of function motor_position_profile */
