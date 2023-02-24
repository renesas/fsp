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
#include "rm_motor_current.h"
#include "rm_motor_current_library.h"
#include "bsp_api.h"
#include "bsp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_CURRENT_OPEN         (0X4D435043L)

#define     MOTOR_CURRENT_FLG_CLR      (0)                           /* For flag clear */
#define     MOTOR_CURRENT_FLG_SET      (1)                           /* For flag set */

#define     MOTOR_CURRENT_TWOPI        (3.14159265358979F * 2.0F)
#define     MOTOR_CURRENT_60_TWOPI     (60.0F / MOTOR_CURRENT_TWOPI) /* To translate rad/s => rpm */
#define     MOTOR_CURRENT_SQRT_2       (1.41421356F)                 /* Sqrt(2) */
#define     MOTOR_CURRENT_SQRT_3       (1.7320508F)                  /* Sqrt(3) */
#define     MOTOR_CURRENT_DIV_KHZ      (0.001F)

#define     MOTOR_CURRENT_MAGNITUDE    (1.0F)

#ifndef MOTOR_CURRENT_ERROR_RETURN
 #define    MOTOR_CURRENT_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/*******************************************/
/* A/D conversion finish interrupt routine */
/*******************************************/
/* Process from "A/D conversion" to "PWM Moduration" */
void rm_motor_current_cyclic(motor_driver_callback_args_t * p_args);

/* Process to get rotor angle and speed information from angle module */
static void motor_current_angle_cyclic(motor_current_instance_t * p_instance);

/* static functions */
static void  motor_current_reset(motor_current_instance_ctrl_t * p_ctrl);
static float motor_current_limit_abs(float f4_value, float f4_limit_value);
static void  motor_current_pi_calculation(motor_current_instance_ctrl_t * p_ctrl);
static float motor_current_pi_control(motor_current_pi_params_t * pi_ctrl);
static void  motor_current_decoupling(motor_current_instance_ctrl_t         * p_ctrl,
                                      float                                   f_speed_rad,
                                      const motor_current_motor_parameter_t * p_mtr);
static void motor_current_voltage_limit(motor_current_instance_ctrl_t * p_ctrl);
static void motor_current_transform_uvw_dq_abs(const float f_angle, const float * f_uvw, float * f_dq);
static void motor_current_transform_dq_uvw_abs(const float f_angle, const float * f_dq, float * f_uvw);

static float motor_current_sample_delay_compensation(float f4_angle_rad, float f4_speed_rad, float f4_ctrl_period);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_current_api_t g_motor_current_on_motor_current =
{
    .open                = RM_MOTOR_CURRENT_Open,
    .close               = RM_MOTOR_CURRENT_Close,
    .reset               = RM_MOTOR_CURRENT_Reset,
    .run                 = RM_MOTOR_CURRENT_Run,
    .parameterSet        = RM_MOTOR_CURRENT_ParameterSet,
    .currentReferenceSet = RM_MOTOR_CURRENT_CurrentReferenceSet,
    .speedPhaseSet       = RM_MOTOR_CURRENT_SpeedPhaseSet,
    .currentSet          = RM_MOTOR_CURRENT_CurrentSet,
    .parameterGet        = RM_MOTOR_CURRENT_ParameterGet,
    .currentGet          = RM_MOTOR_CURRENT_CurrentGet,
    .phaseVoltageGet     = RM_MOTOR_CURRENT_PhaseVoltageGet,
    .parameterUpdate     = RM_MOTOR_CURRENT_ParameterUpdate,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_CURRENT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the Motor Current Module. Implements @ref motor_current_api_t::open.
 *
 * @retval FSP_SUCCESS              Motor Current successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Configuration parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_Open (motor_current_ctrl_t * const p_ctrl, motor_current_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
#endif

    motor_current_extended_cfg_t * p_extended_cfg = (motor_current_extended_cfg_t *) p_cfg->p_extend;

    p_instance_ctrl->p_driver_instance = p_cfg->p_motor_driver_instance;
    p_instance_ctrl->p_angle_instance  = p_cfg->p_motor_angle_instance;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_driver_instance);
    FSP_ASSERT(NULL != p_instance_ctrl->p_angle_instance);
    float check_period = 0.0F;
    check_period = p_extended_cfg->f_current_ctrl_period * MOTOR_CURRENT_DIV_KHZ;

    MOTOR_CURRENT_ERROR_RETURN(check_period >= 0.0F, FSP_ERR_INVALID_ARGUMENT);
#endif

    FSP_ERROR_RETURN(MOTOR_CURRENT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    p_instance_ctrl->p_cfg = p_cfg;

    motor_current_reset(p_instance_ctrl);

    p_instance_ctrl->st_pi_id.f_ilimit = p_extended_cfg->f_ilimit;
    p_instance_ctrl->st_pi_iq.f_ilimit = p_extended_cfg->f_ilimit;

    rm_motor_current_pi_gain_calc(p_extended_cfg->p_motor_parameter,
                                  p_extended_cfg->p_design_parameter,
                                  &(p_instance_ctrl->st_pi_id),
                                  &(p_instance_ctrl->st_pi_iq),
                                  p_extended_cfg->f_current_ctrl_period * MOTOR_CURRENT_DIV_KHZ);

    p_instance_ctrl->st_vcomp.f_comp_v[0]             = p_extended_cfg->f_comp_v[0];
    p_instance_ctrl->st_vcomp.f_comp_v[1]             = p_extended_cfg->f_comp_v[1];
    p_instance_ctrl->st_vcomp.f_comp_v[2]             = p_extended_cfg->f_comp_v[2];
    p_instance_ctrl->st_vcomp.f_comp_v[3]             = p_extended_cfg->f_comp_v[3];
    p_instance_ctrl->st_vcomp.f_comp_v[4]             = p_extended_cfg->f_comp_v[4];
    p_instance_ctrl->st_vcomp.f_comp_i[0]             = p_extended_cfg->f_comp_i[0];
    p_instance_ctrl->st_vcomp.f_comp_i[1]             = p_extended_cfg->f_comp_i[1];
    p_instance_ctrl->st_vcomp.f_comp_i[2]             = p_extended_cfg->f_comp_i[2];
    p_instance_ctrl->st_vcomp.f_comp_i[3]             = p_extended_cfg->f_comp_i[3];
    p_instance_ctrl->st_vcomp.f_comp_i[4]             = p_extended_cfg->f_comp_i[4];
    p_instance_ctrl->st_vcomp.u1_volt_err_comp_enable = p_extended_cfg->vcomp_enable;
    rm_motor_voltage_error_compensation_init(&(p_instance_ctrl->st_vcomp));

    /* Open Motor Driver Access Module */
    if (p_instance_ctrl->p_driver_instance != NULL)
    {
        p_instance_ctrl->p_driver_instance->p_api->open(p_instance_ctrl->p_driver_instance->p_ctrl,
                                                        p_instance_ctrl->p_driver_instance->p_cfg);
    }

    /* Open Motor Angle Module */
    if (p_instance_ctrl->p_angle_instance != NULL)
    {
        p_instance_ctrl->p_angle_instance->p_api->open(p_instance_ctrl->p_angle_instance->p_ctrl,
                                                       p_instance_ctrl->p_angle_instance->p_cfg);
    }

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_CURRENT_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Disables specified Motor Current Module. Implements @ref motor_current_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_Close (motor_current_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    motor_current_reset(p_instance_ctrl);

    rm_motor_voltage_error_compensation_init(&(p_instance_ctrl->st_vcomp));

    /* Close motor driver access */
    if (p_instance_ctrl->p_driver_instance != NULL)
    {
        p_instance_ctrl->p_driver_instance->p_api->close(p_instance_ctrl->p_driver_instance->p_ctrl);
    }

    /* Close motor angle */
    if (p_instance_ctrl->p_angle_instance != NULL)
    {
        p_instance_ctrl->p_angle_instance->p_api->close(p_instance_ctrl->p_angle_instance->p_ctrl);
    }

    p_instance_ctrl->open = 0U;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of Motor Current Module. Implements @ref motor_current_api_t::reset.
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_Reset (motor_current_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->u1_active = MOTOR_CURRENT_FLG_CLR;

    /* Reset motor driver access */
    if (p_instance_ctrl->p_driver_instance != NULL)
    {
        p_instance_ctrl->p_driver_instance->p_api->reset(p_instance_ctrl->p_driver_instance->p_ctrl);
    }

    motor_current_reset(p_instance_ctrl);

    rm_motor_voltage_error_compensation_reset(&(p_instance_ctrl->st_vcomp));

    /* Reset motor angle */
    if (p_instance_ctrl->p_angle_instance != NULL)
    {
        p_instance_ctrl->p_angle_instance->p_api->reset(p_instance_ctrl->p_angle_instance->p_ctrl);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Run(Start) the Current Control. Implements @ref motor_current_api_t::run
 *
 * @retval FSP_SUCCESS              Successfully run.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_Run (motor_current_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->u1_active = MOTOR_CURRENT_FLG_SET;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set (Input) Parameter Data. Implements @ref motor_current_api_t::parameterSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input argument error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_ParameterSet (motor_current_ctrl_t * const        p_ctrl,
                                         motor_current_input_t const * const p_st_input)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_CURRENT_ERROR_RETURN(p_st_input != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->st_input = *p_st_input;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set Current Reference Data. Implements @ref motor_current_api_t::currentReferenceSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_CurrentReferenceSet (motor_current_ctrl_t * const p_ctrl,
                                                float const                  id_reference,
                                                float const                  iq_reference)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->f_id_ref = id_reference;
    p_instance_ctrl->f_iq_ref = iq_reference;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set Current Speed & rotor phase Data. Implements @ref motor_current_api_t::speedPhaseSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_SpeedPhaseSet (motor_current_ctrl_t * const p_ctrl, float const speed, float const phase)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->f_speed_rad   = speed;
    p_instance_ctrl->f_rotor_angle = phase;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set d/q-axis Current & Voltage Data. Implements @ref motor_current_api_t::currentSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_CurrentSet (motor_current_ctrl_t * const                p_ctrl,
                                       motor_current_input_current_t const * const p_st_current,
                                       motor_current_input_voltage_t const * const p_st_voltage)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_CURRENT_ERROR_RETURN(p_st_voltage->vdc >= 0.0F, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->f_iu_ad  = p_st_current->iu;
    p_instance_ctrl->f_iv_ad  = p_st_current->iv;
    p_instance_ctrl->f_iw_ad  = p_st_current->iw;
    p_instance_ctrl->f_vdc_ad = p_st_voltage->vdc;
    p_instance_ctrl->f_va_max = p_st_voltage->va_max;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Get Output Parameters. Implements @ref motor_current_api_t::parameterGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_ParameterGet (motor_current_ctrl_t * const   p_ctrl,
                                         motor_current_output_t * const p_st_output)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_CURRENT_ERROR_RETURN(p_st_output != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_current_extended_cfg_t * p_extended_cfg =
        (motor_current_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    motor_angle_instance_t const * p_angle = p_instance_ctrl->p_angle_instance;
    motor_angle_encoder_info_t     temp_info;

    p_st_output->f_id        = p_instance_ctrl->f_id_ad;
    p_st_output->f_iq        = p_instance_ctrl->f_iq_ad;
    p_st_output->f_vamax     = p_instance_ctrl->f_va_max;
    p_st_output->f_speed_rad = p_instance_ctrl->f_speed_rad;
    p_st_output->f_speed_rpm = p_instance_ctrl->f_speed_rad / p_extended_cfg->p_motor_parameter->u2_mtr_pp *
                               MOTOR_CURRENT_60_TWOPI;
    p_st_output->f_rotor_angle    = p_instance_ctrl->f_rotor_angle;
    p_st_output->f_position_rad   = p_instance_ctrl->f_position_rad;
    p_st_output->f_ed             = p_instance_ctrl->f_ed;
    p_st_output->f_eq             = p_instance_ctrl->f_eq;
    p_st_output->f_phase_err_rad  = p_instance_ctrl->f_phase_err;
    p_st_output->u1_flag_get_iref = p_instance_ctrl->u1_flag_crnt_offset;

    if (MOTOR_CURRENT_CONTROL_TYPE_ENCODER == p_extended_cfg->u1_control_type)
    {
        p_angle->p_api->infoGet(p_angle->p_ctrl, &temp_info);
        p_st_output->u1_adjust_status     = (uint8_t) temp_info.e_adjust_status;
        p_st_output->u1_adjust_count_full = temp_info.u1_adjust_count_full;
    }
    else if (MOTOR_CURRENT_CONTROL_TYPE_INDUCTION == p_extended_cfg->u1_control_type)
    {
        p_angle->p_api->infoGet(p_angle->p_ctrl, &temp_info);
        p_st_output->u1_adjust_status     = (uint8_t) temp_info.e_adjust_status;
        p_st_output->u1_adjust_count_full = temp_info.u1_adjust_count_full;

        p_st_output->u1_openloop_status = (uint8_t) temp_info.e_open_loop_status;
        p_st_output->f_openloop_speed   = temp_info.f_openloop_speed;
        p_st_output->f_openloop_id_ref  = temp_info.f_openloop_id_ref;
    }
    else
    {
        /* Do nothing */
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Get d/q-axis Current. Implements @ref motor_current_api_t::currentGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_CurrentGet (motor_current_ctrl_t * const p_ctrl, float * const p_id, float * const p_iq)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_CURRENT_ERROR_RETURN(p_id != NULL, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_CURRENT_ERROR_RETURN(p_iq != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_current_transform_uvw_dq_abs(p_instance_ctrl->f_rotor_angle, &(p_instance_ctrl->f_iu_ad),
                                       &(p_instance_ctrl->f_id_ad));

    *p_id = p_instance_ctrl->f_id_ad;
    *p_iq = p_instance_ctrl->f_iq_ad;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets the set phase voltage. Implements @ref motor_current_api_t::phaseVoltageGet
 *
 * @retval FSP_SUCCESS              Successful data calculation.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_PhaseVoltageGet (motor_current_ctrl_t * const        p_ctrl,
                                            motor_current_get_voltage_t * const p_voltage)
{
    float     f4_iuvw_ref[3] = {0.0F};
    fsp_err_t err            = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_CURRENT_ERROR_RETURN(p_voltage != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_current_extended_cfg_t * p_extended_cfg =
        (motor_current_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Feedback control (Current) */
    motor_current_pi_calculation(p_instance_ctrl);

    /* Decoupling control */
    motor_current_decoupling(p_instance_ctrl, p_instance_ctrl->f_speed_rad, p_extended_cfg->p_motor_parameter);

    /* Limit voltage vector */
    motor_current_voltage_limit(p_instance_ctrl);
    p_voltage->vd_reference = p_instance_ctrl->f_vd_ref;
    p_voltage->vq_reference = p_instance_ctrl->f_vq_ref;

    // Encoder New Process (Angle Update by sample delay compensation)
    if (MOTOR_CURRENT_SAMPLE_DELAY_COMPENSATION_ENABLE == p_extended_cfg->u1_sample_delay_comp_enable)
    {
        p_instance_ctrl->f_rotor_angle =
            motor_current_sample_delay_compensation(p_instance_ctrl->f_rotor_angle,
                                                    p_instance_ctrl->f_speed_rad,
                                                    p_extended_cfg->f_current_ctrl_period * MOTOR_CURRENT_DIV_KHZ);
    }

    /* Coordinate transformation (dq->uvw) */
    motor_current_transform_dq_uvw_abs(p_instance_ctrl->f_rotor_angle, &(p_instance_ctrl->f_vd_ref),
                                       &(p_instance_ctrl->f_refu));

    /* Voltage error compensation */
    motor_current_transform_dq_uvw_abs(p_instance_ctrl->f_rotor_angle, &(p_instance_ctrl->f_id_ref), &(f4_iuvw_ref[0]));

    rm_motor_voltage_error_compensation_main(&(p_instance_ctrl->st_vcomp),
                                             &(p_instance_ctrl->f_refu),
                                             &(f4_iuvw_ref[0]),
                                             p_instance_ctrl->f_vdc_ad);

    p_voltage->u_voltage = p_instance_ctrl->f_refu;
    p_voltage->v_voltage = p_instance_ctrl->f_refv;
    p_voltage->w_voltage = p_instance_ctrl->f_refw;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of Current Control. Implements @ref motor_current_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data was updated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_CURRENT_ParameterUpdate (motor_current_ctrl_t * const      p_ctrl,
                                            motor_current_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_ctrl;

#if MOTOR_CURRENT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_CURRENT_ERROR_RETURN(MOTOR_CURRENT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_cfg);
#endif
    motor_current_extended_cfg_t * p_extended_cfg = (motor_current_extended_cfg_t *) p_cfg->p_extend;

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->st_pi_id.f_ilimit = p_extended_cfg->f_ilimit;
    p_instance_ctrl->st_pi_iq.f_ilimit = p_extended_cfg->f_ilimit;

    rm_motor_current_pi_gain_calc(p_extended_cfg->p_motor_parameter,
                                  p_extended_cfg->p_design_parameter,
                                  &(p_instance_ctrl->st_pi_id),
                                  &(p_instance_ctrl->st_pi_iq),
                                  p_extended_cfg->f_current_ctrl_period * MOTOR_CURRENT_DIV_KHZ);

    rm_motor_voltage_error_compensation_init(&(p_instance_ctrl->st_vcomp));

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_CURRENT)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : rm_motor_current_encoder_cyclic
 * Description   : Wrapper Cyclic Process of Encoder Control by Current Control
 * Arguments     : p_ctrl - The pointer to current control
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_current_encoder_cyclic (motor_current_instance_t const * p_ctrl)
{
    motor_current_instance_ctrl_t * p_instance_ctrl  = (motor_current_instance_ctrl_t *) p_ctrl->p_ctrl;
    motor_angle_instance_t const  * p_angle_instance = p_instance_ctrl->p_angle_instance;

    p_angle_instance->p_api->cyclicProcess(p_angle_instance->p_ctrl);
}

/***********************************************************************************************************************
 * Function Name : rm_motor_current_encoder_angle_adjust
 * Description   : Wrapper Angle Adjustment Process of Encoder Control by Current Control
 * Arguments     : p_ctrl - The pointer to current control
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_current_encoder_angle_adjust (motor_current_instance_t const * p_ctrl)
{
    motor_current_instance_ctrl_t * p_instance_ctrl  = (motor_current_instance_ctrl_t *) p_ctrl->p_ctrl;
    motor_angle_instance_t const  * p_angle_instance = p_instance_ctrl->p_angle_instance;

    if (MOTOR_CURRENT_FLG_SET == p_instance_ctrl->u1_active)
    {
        p_angle_instance->p_api->angleAdjust(p_angle_instance->p_ctrl);
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_current_induction_cyclic
 * Description   : Wrapper Cyclic Process of Induction sensor Control by Current Control
 * Arguments     : p_ctrl - The pointer to current control
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_current_induction_cyclic (motor_current_instance_t const * p_ctrl)
{
    motor_current_instance_ctrl_t * p_instance_ctrl  = (motor_current_instance_ctrl_t *) p_ctrl->p_ctrl;
    motor_angle_instance_t const  * p_angle_instance = p_instance_ctrl->p_angle_instance;

    p_angle_instance->p_api->cyclicProcess(p_angle_instance->p_ctrl);
}

/***********************************************************************************************************************
 * Function Name : rm_motor_current_induction_angle_adjust
 * Description   : Wrapper Angle Adjustment Process of Induction sensor Control by Current Control
 * Arguments     : p_ctrl - The pointer to current control
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_current_induction_angle_adjust (motor_current_instance_t const * p_ctrl)
{
    motor_current_instance_ctrl_t * p_instance_ctrl  = (motor_current_instance_ctrl_t *) p_ctrl->p_ctrl;
    motor_angle_instance_t const  * p_angle_instance = p_instance_ctrl->p_angle_instance;

    if (MOTOR_CURRENT_FLG_SET == p_instance_ctrl->u1_active)
    {
        p_angle_instance->p_api->angleAdjust(p_angle_instance->p_ctrl);
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_current_cyclic
 * Description   : Cyclic Process of Current Control (Performed at ADC Finish Interrupt)
 * Arguments     : p_args - The pointer to used arguments
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_current_cyclic (motor_driver_callback_args_t * p_args)
{
    float f_iu_ad  = 0.0F;
    float f_iv_ad  = 0.0F;
    float f_iw_ad  = 0.0F;
    float f_vdc_ad = 0.0F;
    float f_ref[3] = {0.0F};
    motor_driver_current_get_t temp_drv_crnt_get;

    motor_current_instance_t      * p_instance      = (motor_current_instance_t *) p_args->p_context;
    motor_current_instance_ctrl_t * p_instance_ctrl = (motor_current_instance_ctrl_t *) p_instance->p_ctrl;

    motor_current_extended_cfg_t * p_extended_cfg =
        (motor_current_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    motor_driver_instance_t const * p_driver_instance = p_instance_ctrl->p_driver_instance;

    motor_current_callback_args_t temp_args_t;

    motor_current_input_current_t temp_input_current;
    motor_current_input_voltage_t temp_input_voltage;
    motor_current_get_voltage_t   temp_get_voltage;

    switch (p_args->event)
    {
        case MOTOR_DRIVER_EVENT_FORWARD:
        {
            /* Invoke the callback function if it is set. */
            if (NULL != p_instance->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_CURRENT_EVENT_FORWARD;
                temp_args_t.p_context = p_instance->p_cfg->p_context;
                (p_instance->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        /* Current Control Timing */
        case MOTOR_DRIVER_EVENT_CURRENT:
        {
            /* Get A/D converted data */
            p_driver_instance->p_api->currentGet(p_driver_instance->p_ctrl, &temp_drv_crnt_get);
            f_iu_ad  = temp_drv_crnt_get.iu;
            f_iw_ad  = temp_drv_crnt_get.iw;
            f_vdc_ad = temp_drv_crnt_get.vdc;
            p_instance_ctrl->f_va_max      = temp_drv_crnt_get.va_max;
            p_instance_ctrl->f_sin_ad_data = temp_drv_crnt_get.sin_ad;
            p_instance_ctrl->f_cos_ad_data = temp_drv_crnt_get.cos_ad;

            if (MOTOR_CURRENT_SHUNT_TYPE_2_SHUNT == p_extended_cfg->shunt)
            {
                f_iv_ad = -(f_iu_ad + f_iw_ad);
            }
            else
            {
                f_iv_ad = temp_drv_crnt_get.iv;
            }

            /* Active Current Control */
            if (MOTOR_CURRENT_FLG_SET == p_instance_ctrl->u1_active)
            {
                /* Measure current offset values */
                p_driver_instance->p_api->flagCurrentOffsetGet(p_driver_instance->p_ctrl,
                                                               &(p_instance_ctrl->u1_flag_crnt_offset));

                /* After current offset was measured */
                if (MOTOR_CURRENT_FLG_SET == p_instance_ctrl->u1_flag_crnt_offset)
                {
                    /* Invoke the callback function if it is set. */
                    if (NULL != p_instance->p_cfg->p_callback)
                    {
                        temp_args_t.event     = MOTOR_CURRENT_EVENT_DATA_SET;
                        temp_args_t.p_context = p_instance->p_cfg->p_context;
                        (p_instance->p_cfg->p_callback)(&temp_args_t);
                    }

                    /* Coordinate transformation (UVW->dq) */
                    temp_input_current.iu     = f_iu_ad;
                    temp_input_current.iv     = f_iv_ad;
                    temp_input_current.iw     = f_iw_ad;
                    temp_input_voltage.vdc    = f_vdc_ad;
                    temp_input_voltage.va_max = p_instance_ctrl->f_va_max;

                    p_instance->p_api->currentSet(p_instance_ctrl, &temp_input_current, &temp_input_voltage);

                    p_instance->p_api->currentGet(p_instance_ctrl, &(p_instance_ctrl->f_id_ad),
                                                  &(p_instance_ctrl->f_iq_ad));

                    /* Angle & speed process */
                    motor_current_angle_cyclic(p_instance);

                    /* Current control */
                    p_instance->p_api->currentReferenceSet(p_instance_ctrl,
                                                           p_instance_ctrl->st_input.f_id_ref,
                                                           p_instance_ctrl->st_input.f_iq_ref);

                    p_instance->p_api->phaseVoltageGet(p_instance_ctrl, &temp_get_voltage);

                    f_ref[0] = temp_get_voltage.u_voltage;
                    f_ref[1] = temp_get_voltage.v_voltage;
                    f_ref[2] = temp_get_voltage.w_voltage;

                    /* Space vector modulation */
                    p_driver_instance->p_api->phaseVoltageSet(p_driver_instance->p_ctrl, f_ref[0], f_ref[1], f_ref[2]);
                }
            }

            break;
        }

        case MOTOR_DRIVER_EVENT_BACKWARD:
        {
            /* Invoke the callback function if it is set. */
            if (NULL != p_instance->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_CURRENT_EVENT_BACKWARD;
                temp_args_t.p_context = p_instance->p_cfg->p_context;
                (p_instance->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        default:
        {
            break;
        }
    }
}                                      /* End of function rm_motor_current_cyclic() */

/***********************************************************************************************************************
 * Function Name : motor_current_angle_cyclic
 * Description   : Angle/Speed Process in Cyclic Process of Current Control
 * Arguments     : p_ctrl - The pointer to current control module control instance
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_current_angle_cyclic (motor_current_instance_t * p_instance)
{
    motor_current_instance_ctrl_t * p_ctrl = (motor_current_instance_ctrl_t *) p_instance->p_ctrl;

    motor_current_extended_cfg_t * p_extended_cfg =
        (motor_current_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    motor_angle_instance_t const * p_angle = p_ctrl->p_angle_instance;

    if (MOTOR_CURRENT_CONTROL_TYPE_SENSORLESS == p_extended_cfg->u1_control_type)
    {
        motor_angle_current_t           temp_current;
        motor_angle_voltage_reference_t temp_vol_ref;

        temp_current.id = p_ctrl->f_id_ad;
        temp_current.iq = p_ctrl->f_iq_ad;
        temp_vol_ref.vd = p_ctrl->f_vd_ref;
        temp_vol_ref.vq = p_ctrl->f_vq_ref;

        p_angle->p_api->flagPiCtrlSet(p_angle->p_ctrl, p_ctrl->st_input.u1_flag_pi);
        p_angle->p_api->speedSet(p_angle->p_ctrl,
                                 p_ctrl->st_input.f_ref_speed_rad_ctrl,
                                 p_ctrl->st_input.f_damp_comp_speed);
        p_angle->p_api->currentSet(p_angle->p_ctrl, &temp_current, &temp_vol_ref);
        p_angle->p_api->angleSpeedGet(p_angle->p_ctrl, &(p_ctrl->f_rotor_angle), &(p_ctrl->f_speed_rad),
                                      &(p_ctrl->f_phase_err));
        p_angle->p_api->estimatedComponentGet(p_angle->p_ctrl, &(p_ctrl->f_ed), &(p_ctrl->f_eq));
    }
    else if (MOTOR_CURRENT_CONTROL_TYPE_ENCODER == p_extended_cfg->u1_control_type)
    {
        /* Position & speed calculation */
        p_angle->p_api->internalCalculate(p_angle->p_ctrl);

        /* Speed & angle detection */
        p_angle->p_api->angleSpeedGet(p_angle->p_ctrl, &(p_ctrl->f_rotor_angle), &(p_ctrl->f_speed_rad),
                                      &(p_ctrl->f_position_rad));
    }
    else if (MOTOR_CURRENT_CONTROL_TYPE_HALL == p_extended_cfg->u1_control_type)
    {
        /* Speed & angle detection */
        p_angle->p_api->angleSpeedGet(p_angle->p_ctrl, &(p_ctrl->f_rotor_angle), &(p_ctrl->f_speed_rad),
                                      &(p_ctrl->f_phase_err));
    }
    else if (MOTOR_CURRENT_CONTROL_TYPE_INDUCTION == p_extended_cfg->u1_control_type)
    {
        motor_angle_ad_data_t temp_ad_data;
        temp_ad_data.sin_ad_data = p_ctrl->f_sin_ad_data;
        temp_ad_data.cos_ad_data = p_ctrl->f_cos_ad_data;

        /* Set induction sensor output */
        p_angle->p_api->sensorDataSet(p_angle->p_ctrl, &temp_ad_data);

        /* Position & speed calculation */
        p_angle->p_api->internalCalculate(p_angle->p_ctrl);

        /* Speed & angle detection */
        p_angle->p_api->angleSpeedGet(p_angle->p_ctrl, &(p_ctrl->f_rotor_angle), &(p_ctrl->f_speed_rad),
                                      &(p_ctrl->f_position_rad));
    }
    else
    {
        /* Do nothing */
    }
}                                      /* End of function motor_current_angle_cyclic */

/***********************************************************************************************************************
 * Function Name : motor_current_reset
 * Description   : Resets FOC current control module
 * Arguments     : p_ctrl - The pointer to the FOC current control instance
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_current_reset (motor_current_instance_ctrl_t * p_ctrl)
{
    p_ctrl->u1_active     = MOTOR_CURRENT_FLG_CLR;
    p_ctrl->f_vd_ref      = 0.0F;
    p_ctrl->f_vq_ref      = 0.0F;
    p_ctrl->f_id_ref      = 0.0F;
    p_ctrl->f_iq_ref      = 0.0F;
    p_ctrl->f_id_ad       = 0.0F;
    p_ctrl->f_iq_ad       = 0.0F;
    p_ctrl->f_vdc_ad      = 0.0F;
    p_ctrl->f_speed_rad   = 0.0F;
    p_ctrl->f_rotor_angle = 0.0F;
    p_ctrl->f_refu        = 0.0F;
    p_ctrl->f_refv        = 0.0F;
    p_ctrl->f_refw        = 0.0F;

    p_ctrl->st_pi_id.f_err  = 0.0F;
    p_ctrl->st_pi_iq.f_err  = 0.0F;
    p_ctrl->st_pi_id.f_refi = 0.0F;
    p_ctrl->st_pi_iq.f_refi = 0.0F;

    p_ctrl->u1_flag_crnt_offset = MOTOR_CURRENT_FLG_CLR;
}                                      /* End of function motor_current_reset */

/***********************************************************************************************************************
 * Function Name : motor_current_limit_abs
 * Description   : Limit with absolute value
 * Arguments     : f4_value       - Target value
 *                f4_limit_value - Limit
 * Return Value  : Limited value
 **********************************************************************************************************************/
static float motor_current_limit_abs (float f4_value, float f4_limit_value)
{
    float f4_temp0 = 0.0F;

    f4_temp0 = fabsf(f4_value);
    if (f4_temp0 > f4_limit_value)
    {
        f4_value = copysignf(f4_limit_value, f4_value);
    }

    return f4_value;
}                                      /* End of function motor_current_limit_abs */

/***********************************************************************************************************************
 * Function Name : motor_current_pi_calculation
 * Description   : Current PI control
 *                 Calculates the output voltage vector from current vector command and actual current vector
 * Arguments     : p_ctrl - The pointer to the FOC current control structure
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_current_pi_calculation (motor_current_instance_ctrl_t * p_ctrl)
{
    /* The d-axis */
    p_ctrl->st_pi_id.f_err = p_ctrl->f_id_ref - p_ctrl->f_id_ad;
    p_ctrl->f_vd_ref       = motor_current_pi_control(&(p_ctrl->st_pi_id));

    /* The q-axis */
    p_ctrl->st_pi_iq.f_err = p_ctrl->f_iq_ref - p_ctrl->f_iq_ad;
    p_ctrl->f_vq_ref       = motor_current_pi_control(&(p_ctrl->st_pi_iq));
}                                      /* End of function motor_current_pi_calculation */

/***********************************************************************************************************************
 * Function Name : motor_current_pi_control
 * Description   : PI control
 * Arguments     : pi_ctrl - The pointer to the PI control structure
 * Return Value  : PI control output value
 **********************************************************************************************************************/
static float motor_current_pi_control (motor_current_pi_params_t * pi_ctrl)
{
    float f4_err;
    float f4_kp;
    float f4_ki;
    float f4_refp;
    float f4_refi;
    float f4_ref;
    float f4_ilimit;

    f4_err    = pi_ctrl->f_err;
    f4_kp     = pi_ctrl->f_kp;
    f4_ki     = pi_ctrl->f_ki;
    f4_refi   = pi_ctrl->f_refi;
    f4_ilimit = pi_ctrl->f_ilimit;

    f4_refp  = f4_err * f4_kp;         /* Proportional part */
    f4_refi += (f4_err * f4_ki);       /* Integral part */

    /* Integral part limit */
    f4_refi         = motor_current_limit_abs(f4_refi, f4_ilimit);
    pi_ctrl->f_refi = f4_refi;

    f4_ref = f4_refp + f4_refi;        /* PI output */

    return f4_ref;
} /* End of function motor_current_pi_control */

/***********************************************************************************************************************
 * Function Name : motor_current_decoupling
 * Description   : Decoupling control, c ancels the interference voltage due to the magnet and inductance
 * Arguments     : p_ctrl       - The pointer to the FOC current control instance
 *                 f_speed_rad  - The electrical speed [rad/s]
 *                 p_mtr        - The pointer to the motor parameter data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_current_decoupling (motor_current_instance_ctrl_t         * p_ctrl,
                                      float                                   f_speed_rad,
                                      const motor_current_motor_parameter_t * p_mtr)
{
    float f4_temp0 = 0.0F;

    f4_temp0          = p_mtr->f4_mtr_lq * p_ctrl->f_iq_ad; /* Lq * Iq */
    f4_temp0          = f_speed_rad * f4_temp0;             /* Speed * Lq * Iq */
    p_ctrl->f_vd_ref -= f4_temp0;                           /* Vd - Speed * Lq * Iq */

    f4_temp0          = p_mtr->f4_mtr_ld * p_ctrl->f_id_ad; /* Ld * id */
    f4_temp0          = f4_temp0 + p_mtr->f4_mtr_m;         /* Ld * Id + Flux */
    f4_temp0          = f_speed_rad * f4_temp0;             /* Speed * (Ld * id + Flux) */
    p_ctrl->f_vq_ref += f4_temp0;                           /* Vq + Speed*(Ld * id + Flux) */
} /* End of function motor_current_decoupling */

/***********************************************************************************************************************
 * Function Name : motor_current_voltage_limit
 * Description   : Limit voltage vector, d-axis voltage has higher priority than q-axis voltage
 * Arguments     : p_ctrl - The pointer to the FOC current control structure
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_current_voltage_limit (motor_current_instance_ctrl_t * p_ctrl)
{
    float f4_vq_lim = 0.0F;
    float f4_vd_ref = 0.0F;
    float f4_va_max = 0.0F;

    f4_vd_ref = p_ctrl->f_vd_ref;
    f4_va_max = p_ctrl->f_va_max;

    /* The d-axis voltage has high priority than the q-axis */
    /* If absolute value of D-axis voltage exceeds maximum voltage, limit it to the maximum voltage */
    if (f4_vd_ref > f4_va_max)
    {
        p_ctrl->f_vd_ref = f4_va_max;
        p_ctrl->f_vq_ref = 0.0F;
    }
    else if (f4_vd_ref < -f4_va_max)
    {
        p_ctrl->f_vd_ref = -f4_va_max;
        p_ctrl->f_vq_ref = 0.0F;
    }
    else
    {
        f4_vq_lim        = sqrtf((f4_va_max * f4_va_max) - (f4_vd_ref * f4_vd_ref));
        p_ctrl->f_vq_ref = motor_current_limit_abs(p_ctrl->f_vq_ref, f4_vq_lim);
    }
}                                      /* End of function motor_current_voltage_limit */

/***********************************************************************************************************************
 * Function Name : motor_current_transform_uvw_dq_abs
 * Description   : Coordinate transform UVW to dq (absolute transform)
 * Arguments     : f_angle  - rotor angle
 *                 f_uvw    - the pointer to the UVW-phase array in [U,V,W] format
 *                 f_dq     - where to store the [d,q] formated array on dq coordinates
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_current_transform_uvw_dq_abs (const float f_angle, const float * f_uvw, float * f_dq)
{
    float f4_temp0   = 0.0F;
    float f4_temp1   = 0.0F;
    float f4_temp2   = 0.0F;
    float f4_temp3   = 0.0F;
    float f4_u       = f_uvw[0];
    float f4_v_sub_w = f_uvw[1] - f_uvw[2];
    float f4_cos     = cosf(f_angle);
    float f4_sin     = sinf(f_angle);

    f4_temp0 = f4_cos * (1.0F / MOTOR_CURRENT_SQRT_2);
    f4_temp1 = f4_sin * (1.0F / MOTOR_CURRENT_SQRT_2);
    f4_temp2 = MOTOR_CURRENT_SQRT_3 * f4_temp0;
    f4_temp3 = MOTOR_CURRENT_SQRT_3 * f4_temp1;
    f_dq[0]  = (f4_temp2 * f4_u) + (f4_temp1 * f4_v_sub_w);
    f_dq[1]  = ((-f4_temp3) * f4_u) + (f4_temp0 * f4_v_sub_w);
}                                      /* End of function motor_current_transform_uvw_dq_abs */

/***********************************************************************************************************************
 * Function Name : motor_current_transform_dq_uvw_abs
 * Description   : Coordinate transform dq to UVW 3-phase (absolute transform)
 * Arguments     : angle     - rotor angle
 *                 f_dq     - the pointer to the dq-axis value array in [D,Q] format
 *                 f_uvw    - where to store the [U,V,W] formated 3-phase quantities array
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_current_transform_dq_uvw_abs (const float f_angle, const float * f_dq, float * f_uvw)
{
    float f4_cos_div_sqrt3 = 0.0F;
    float f4_sin_div_sqrt3 = 0.0F;
    float f4_output_d      = 0.0F;
    float f4_output_q      = 0.0F;
    float f4_input_d       = f_dq[0];
    float f4_input_q       = f_dq[1];
    float f4_cos           = cosf(f_angle);
    float f4_sin           = sinf(f_angle);

    f4_cos_div_sqrt3 = f4_cos * (1.0F / MOTOR_CURRENT_SQRT_3);
    f4_sin_div_sqrt3 = f4_sin * (1.0F / MOTOR_CURRENT_SQRT_3);

    f_uvw[0] = MOTOR_CURRENT_SQRT_2 * ((f4_cos_div_sqrt3 * f4_input_d) - (f4_sin_div_sqrt3 * f4_input_q));

    f4_output_d = ((-f4_cos_div_sqrt3) + f4_sin) * f4_input_d;
    f4_output_q = (f4_sin_div_sqrt3 + f4_cos) * f4_input_q;
    f_uvw[1]    = (f4_output_d + f4_output_q) * (1.0F / MOTOR_CURRENT_SQRT_2);

    f4_output_d = ((-f4_cos_div_sqrt3) - f4_sin) * f4_input_d;
    f4_output_q = (f4_sin_div_sqrt3 - f4_cos) * f4_input_q;
    f_uvw[2]    = (f4_output_d + f4_output_q) * (1.0F / MOTOR_CURRENT_SQRT_2);
}                                      /* End of function motor_current_transform_dq_uvw_abs */

/***********************************************************************************************************************
 * Function Name: motor_current_sample_delay_compensation
 * Description  : current control sampling delay compensation
 * Arguments    : f4_angle_rad   - motor angle (electrical) [rad]
 *              : f4_speed_rad   - motor speed (electrical) [rad/s]
 *              : f4_ctrl_period - motor current control period
 * Return Value : motor angle (electrical) [rad/s]
 **********************************************************************************************************************/
static float motor_current_sample_delay_compensation (float f4_angle_rad, float f4_speed_rad, float f4_ctrl_period)
{
    float f4_comp_angle_rad = 0.0F;

    f4_comp_angle_rad = f4_speed_rad * f4_ctrl_period * MOTOR_CURRENT_MAGNITUDE;
    f4_comp_angle_rad = f4_angle_rad + f4_comp_angle_rad;

    /* Limit angle value of one rotation */
    if (f4_comp_angle_rad >= MOTOR_CURRENT_TWOPI)
    {
        f4_comp_angle_rad -= MOTOR_CURRENT_TWOPI;
    }
    else if (f4_comp_angle_rad < 0.0F)
    {
        f4_comp_angle_rad += MOTOR_CURRENT_TWOPI;
    }
    else
    {
        /* Do nothing */
    }

    return f4_comp_angle_rad;
}                                      /* End of function motor_current_sample_delay_compensation */
