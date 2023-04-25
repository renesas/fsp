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
#include <stdio.h>
#include "rm_motor_estimate.h"
#include "rm_motor_estimate_library.h"
#include "bsp_api.h"
#include "bsp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_ESTIMATE_OPEN       (0X4D414553ULL)

#define     MOTOR_ESTIMATE_FLG_CLR    (0U)
#define     MOTOR_ESTIMATE_FLG_SET    (1U)

#define     MOTOR_ESTIMATE_TWOPI      (3.14159265358979F * 2.0F)

#ifndef MTR_ESTIMATE_ERROR_RETURN

 #define MTR_ESTIMATE_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_angle_api_t g_motor_angle_on_motor_estimate =
{
    .open                  = RM_MOTOR_ESTIMATE_Open,
    .close                 = RM_MOTOR_ESTIMATE_Close,
    .reset                 = RM_MOTOR_ESTIMATE_Reset,
    .currentSet            = RM_MOTOR_ESTIMATE_CurrentSet,
    .speedSet              = RM_MOTOR_ESTIMATE_SpeedSet,
    .flagPiCtrlSet         = RM_MOTOR_ESTIMATE_FlagPiCtrlSet,
    .angleSpeedGet         = RM_MOTOR_ESTIMATE_AngleSpeedGet,
    .estimatedComponentGet = RM_MOTOR_ESTIMATE_EstimatedComponentGet,
    .parameterUpdate       = RM_MOTOR_ESTIMATE_ParameterUpdate,
    .internalCalculate     = RM_MOTOR_ESTIMATE_InternalCalculate,
    .angleAdjust           = RM_MOTOR_ESTIMATE_AngleAdjust,
    .encoderCyclic         = RM_MOTOR_ESTIMATE_EncoderCyclic,
    .infoGet               = RM_MOTOR_ESTIMATE_InfoGet,
    .cyclicProcess         = RM_MOTOR_ESTIMATE_CyclicProcess,
    .sensorDataSet         = RM_MOTOR_ESTIMATE_SensorDataSet,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_ESTIMATE
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the Angle Estimation module. Implements @ref motor_angle_api_t::open.
 *
 * @retval FSP_SUCCESS              MTR_ANGL_EST successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Configuration parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_Open (motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
#endif
    motor_estimate_extended_cfg_t * p_extended_cfg = (motor_estimate_extended_cfg_t *) p_cfg->p_extend;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_extended_cfg != NULL);
    FSP_ERROR_RETURN(0.0F <= p_extended_cfg->f_e_obs_omega, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0.0F <= p_extended_cfg->f_e_obs_zeta, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0.0F <= p_extended_cfg->f_pll_est_omega, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0.0F <= p_extended_cfg->f_pll_est_zeta, FSP_ERR_INVALID_ARGUMENT);
#endif

    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    p_instance_ctrl->p_cfg = p_cfg;

    /* Mark driver as open */

    rm_motor_estimate_bemf_obs_init(&(p_instance_ctrl->st_bemf_obs), &(p_extended_cfg->st_motor_params));

    rm_motor_estimate_bemf_observer_gain_calc(&(p_extended_cfg->st_motor_params), p_extended_cfg,
                                              &(p_instance_ctrl->st_bemf_obs), p_extended_cfg->f4_ctrl_period);

    rm_motor_estimate_speed_gain_calc(p_extended_cfg, &(p_instance_ctrl->st_pll_est), p_extended_cfg->f4_ctrl_period);

    rm_motor_estimate_speed_reset(&(p_instance_ctrl->st_pll_est));

    p_instance_ctrl->f4_angle_rad     = 0.0F;
    p_instance_ctrl->u1_flg_pi_ctrl   = MOTOR_ESTIMATE_FLG_CLR;
    p_instance_ctrl->u1_flg_pll_start = MOTOR_ESTIMATE_FLG_SET;

    p_instance_ctrl->open = MOTOR_ESTIMATE_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Disables specified Angle Estimation module. Implements @ref motor_angle_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_Close (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MTR_ESTIMATE_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_estimate_bemf_obs_reset(&(p_instance_ctrl->st_bemf_obs));
    rm_motor_estimate_speed_reset(&(p_instance_ctrl->st_pll_est));
    p_instance_ctrl->u1_flg_pi_ctrl = MOTOR_ESTIMATE_FLG_CLR;

    p_instance_ctrl->open = 0U;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of Angle Estimation module. Implements @ref motor_angle_api_t::reset
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_Reset (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MTR_ESTIMATE_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_estimate_bemf_obs_reset(&(p_instance_ctrl->st_bemf_obs));
    rm_motor_estimate_speed_reset(&(p_instance_ctrl->st_pll_est));
    p_instance_ctrl->u1_flg_pi_ctrl   = MOTOR_ESTIMATE_FLG_CLR;
    p_instance_ctrl->u1_flg_pll_start = MOTOR_ESTIMATE_FLG_SET;
    p_instance_ctrl->f4_angle_rad     = 0.0F;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set d/q-axis Current Data & Voltage Reference. Implements @ref motor_angle_api_t::currentSet
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_CurrentSet (motor_angle_ctrl_t * const              p_ctrl,
                                        motor_angle_current_t * const           p_st_current,
                                        motor_angle_voltage_reference_t * const p_st_voltage)

{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->st_input.f_id     = p_st_current->id;
        p_instance_ctrl->st_input.f_iq     = p_st_current->iq;
        p_instance_ctrl->st_input.f_vd_ref = p_st_voltage->vd;
        p_instance_ctrl->st_input.f_vq_ref = p_st_voltage->vq;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set Speed Information. Implements @ref motor_angle_api_t::speedSet
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_SpeedSet (motor_angle_ctrl_t * const p_ctrl, float const speed_ctrl, float const damp_speed)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MTR_ESTIMATE_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->st_input.f4_ref_speed_rad_ctrl = speed_ctrl;
        p_instance_ctrl->st_input.f4_damp_comp_speed    = damp_speed;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set the flag of PI Control runs. Implements @ref motor_angle_api_t::flagPiCtrlSet
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_FlagPiCtrlSet (motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->u1_flg_pi_ctrl = (uint8_t) flag_pi;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets the current rotor's angle and rotation speed. Implements @ref motor_angle_api_t::angleSpeedGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_AngleSpeedGet (motor_angle_ctrl_t * const p_ctrl,
                                           float * const              p_angle,
                                           float * const              p_speed,
                                           float * const              p_phase_err)
{
    float     f_temp_angle_rad;
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_angle);
    FSP_ASSERT(p_speed);
    FSP_ASSERT(p_phase_err);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (FSP_SUCCESS == err)
    {
        motor_estimate_extended_cfg_t * p_extended_cfg =
            (motor_estimate_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

        /* Estimate voltage disturbance */
        rm_motor_estimate_bemf_observer(&(p_instance_ctrl->st_bemf_obs),
                                        p_instance_ctrl->st_input.f_vd_ref,
                                        p_instance_ctrl->st_input.f_vq_ref,
                                        p_instance_ctrl->st_input.f_id,
                                        p_instance_ctrl->st_input.f_iq);

        /* Calculate BEMF */
        p_instance_ctrl->f4_ed = rm_motor_estimate_bemf_calc_d(&(p_instance_ctrl->st_bemf_obs),
                                                               p_instance_ctrl->f4_speed_rad,
                                                               p_instance_ctrl->st_input.f_iq);
        p_instance_ctrl->f4_eq = rm_motor_estimate_bemf_calc_q(&(p_instance_ctrl->st_bemf_obs),
                                                               p_instance_ctrl->f4_speed_rad,
                                                               p_instance_ctrl->st_input.f_id);

        /* Calculate phase error */
        p_instance_ctrl->f4_phase_err_rad = atanf(p_instance_ctrl->f4_ed / p_instance_ctrl->f4_eq);
        *p_phase_err = p_instance_ctrl->f4_phase_err_rad;

        /* Prevent phase error becoming NAN when eq is 0 */
        if (isnan(p_instance_ctrl->f4_phase_err_rad))
        {
            p_instance_ctrl->f4_phase_err_rad = 0.0F;
        }

        if (MOTOR_ESTIMATE_FLG_SET == p_instance_ctrl->u1_flg_pi_ctrl)
        {
            if (MOTOR_ESTIMATE_FLG_SET == p_instance_ctrl->u1_flg_pll_start)
            {
                p_instance_ctrl->st_pll_est.f4_i_est_speed = p_instance_ctrl->st_input.f4_ref_speed_rad_ctrl;
                p_instance_ctrl->u1_flg_pll_start          = MOTOR_ESTIMATE_FLG_CLR;
            }

            /* Estimate angle and speed */
            rm_motor_estimate_speed_pll(&(p_instance_ctrl->st_pll_est), p_instance_ctrl->f4_phase_err_rad,
                                        &(p_instance_ctrl->f4_speed_rad));
        }
        else
        {
            p_instance_ctrl->u1_flg_pll_start = MOTOR_ESTIMATE_FLG_SET;

            if (MOTOR_ESTIMATE_OPENLOOP_DAMPING_ENABLE == p_extended_cfg->openloop_damping)
            {
                p_instance_ctrl->f4_speed_rad =
                    p_instance_ctrl->st_input.f4_ref_speed_rad_ctrl - p_instance_ctrl->st_input.f4_damp_comp_speed;
            }
            else
            {
                p_instance_ctrl->f4_speed_rad = p_instance_ctrl->st_input.f4_ref_speed_rad_ctrl;
            }
        }

        *p_speed = p_instance_ctrl->f4_speed_rad;

        f_temp_angle_rad  = p_instance_ctrl->f4_angle_rad;
        f_temp_angle_rad += (p_instance_ctrl->f4_speed_rad * (p_extended_cfg->f4_ctrl_period));

        if (f_temp_angle_rad >= MOTOR_ESTIMATE_TWOPI)
        {
            f_temp_angle_rad = f_temp_angle_rad - MOTOR_ESTIMATE_TWOPI;
        }
        else if (f_temp_angle_rad < 0.0F)
        {
            f_temp_angle_rad = f_temp_angle_rad + MOTOR_ESTIMATE_TWOPI;
        }
        else
        {
            /* Do nothing */
        }

        p_instance_ctrl->f4_angle_rad = f_temp_angle_rad;
        *p_angle = f_temp_angle_rad;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets estimated d/q-axis component. Implements @ref motor_angle_api_t::estimatedComponentGet
 *
 * @retval FSP_SUCCESS              Successfully data gotten.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_EstimatedComponentGet (motor_angle_ctrl_t * const p_ctrl,
                                                   float * const              p_ed,
                                                   float * const              p_eq)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_ed != NULL);
    FSP_ASSERT(p_eq != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (FSP_SUCCESS == err)
    {
        *p_ed = p_instance_ctrl->f4_ed;
        *p_eq = p_instance_ctrl->f4_eq;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of Angle&Speed Estimation. Implements @ref motor_angle_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data is update.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_ParameterUpdate (motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    motor_estimate_extended_cfg_t * p_extended_cfg = (motor_estimate_extended_cfg_t *) p_cfg->p_extend;

    if (FSP_SUCCESS == err)
    {
        p_instance_ctrl->p_cfg = p_cfg;

        rm_motor_estimate_bemf_observer_gain_calc(&(p_extended_cfg->st_motor_params), p_extended_cfg,
                                                  &(p_instance_ctrl->st_bemf_obs), p_extended_cfg->f4_ctrl_period);

        rm_motor_estimate_speed_gain_calc(p_extended_cfg, &(p_instance_ctrl->st_pll_est),
                                          p_extended_cfg->f4_ctrl_period);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Calculate internal parameters. Implements @ref motor_angle_api_t::internalCalculate
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_InternalCalculate (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @brief Angle Adjustment Process. Implements @ref motor_angle_api_t::angleAdjust
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_AngleAdjust (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @brief Encoder Cyclic Process (Call in cyclic timer). Implements @ref motor_angle_api_t::encoderCyclic
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_EncoderCyclic (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets information of Encoder Angle Module. Implements @ref motor_angle_api_t::infoGet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_InfoGet (motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info)
{
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (MOTOR_ESTIMATE_CFG_PARAM_CHECKING_ENABLE)
    motor_estimate_instance_ctrl_t * p_instance_ctrl = (motor_estimate_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_info != NULL);
    FSP_ERROR_RETURN(MOTOR_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif
    FSP_PARAMETER_NOT_USED(p_info);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Perform induction cyclic process. Implements @ref motor_angle_api_t::cyclicProcess
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_CyclicProcess (motor_angle_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Set sensor data. Implements @ref motor_angle_api_t::sensorDataSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_ESTIMATE_SensorDataSet (motor_angle_ctrl_t * const p_ctrl, motor_angle_ad_data_t * const p_ad_data)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_ad_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_ESTIMATE)
 **********************************************************************************************************************/
