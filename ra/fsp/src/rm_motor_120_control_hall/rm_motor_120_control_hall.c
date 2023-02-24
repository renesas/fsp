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
#include "rm_motor_120_control_hall.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_120_CONTROL_HALL_OPEN               (0X3132484CL)

#define     MOTOR_120_CONTROL_HALL_TWOPI              (3.14159265358979F * 2.0F)

/* To translate (rpm) => (rad/s) */
#define     MOTOR_120_CONTROL_HALL_TWOPI_DIV_60       (MOTOR_120_CONTROL_HALL_TWOPI / 60.0F)

#define     MOTOR_120_CONTROL_HALL_HZ_TRANS           (1000U) /* x1000 */

/* value of hall signal (CW) */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CW_V_U     (2)     /* V phase to U phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CW_W_U     (3)     /* W phase to U phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CW_W_V     (1)     /* W phase to V phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CW_U_V     (5)     /* U phase to V phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CW_U_W     (4)     /* U phase to W phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CW_V_W     (6)     /* V phase to W phase */
/* value of hall signal (CCW) */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CCW_V_U    (5)     /* V phase to U phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CCW_V_W    (1)     /* V phase to W phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CCW_U_W    (3)     /* U phase to W phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CCW_U_V    (2)     /* U phase to V phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CCW_W_V    (6)     /* W phase to V phase */
#define     MOTOR_120_CONTROL_HALL_PATTERN_CCW_W_U    (4)     /* W phase to U phase */

#ifndef MOTOR_120_CONTROL_HALL_ERROR_RETURN

 #define    MOTOR_120_CONTROL_HALL_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void rm_motor_120_control_hall_interrupt(external_irq_callback_args_t * p_args);
void rm_motor_120_control_hall_speed_cyclic(timer_callback_args_t * p_args);
void rm_motor_120_control_hall_driver_callback(motor_120_driver_callback_args_t * p_args);

static void rm_motor_120_control_hall_reset(motor_120_control_hall_instance_ctrl_t * p_ctrl);
static void rm_motor_120_control_hall_speed_calc(motor_120_control_hall_instance_ctrl_t * p_ctrl);
static void rm_motor_120_control_hall_wait_motorstop(motor_120_control_hall_instance_ctrl_t * p_ctrl);
static void rm_motor_120_control_hall_pattern_set(motor_120_control_hall_instance_ctrl_t * p_ctrl);
static void rm_motor_120_control_hall_pattern_first60(motor_120_control_hall_instance_ctrl_t * p_ctrl,
                                                      uint8_t                                  u1_signal);
static void rm_motor_120_control_hall_pattern_first60_comp(motor_120_control_hall_instance_ctrl_t * p_ctrl,
                                                           uint8_t                                  u1_signal);
static void  rm_motor_120_control_hall_speed_ref_set(motor_120_control_hall_instance_ctrl_t * const p_ctrl);
static void  rm_motor_120_control_hall_voltage_ref_set(motor_120_control_hall_instance_ctrl_t * const p_ctrl);
static float rm_motor_120_control_hall_pi_ctrl(motor_120_control_hall_instance_ctrl_t * p_ctrl);
static void  rm_motor_120_control_hall_check_timeout_error(motor_120_control_hall_instance_ctrl_t * p_ctrl,
                                                           uint32_t                                 u4_timeout_limit);
static float rm_motor_120_control_hall_lpff(float f4_lpf_input, float f4_pre_lpf_output, float f4_lpf_k);
static float rm_motor_120_control_hall_limitf(float f4_value, float f4_max, float f4_min);
static float rm_motor_120_control_hall_limitf_h(float f4_value, float f4_max);
static float rm_motor_120_control_hall_limitf_l(float f4_value, float f4_min);
static float rm_motor_120_control_hall_limitf_abs(float f4_value, float f4_limit_value);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_120_control_api_t g_motor_120_control_on_motor_120_control_hall =
{
    .open                = RM_MOTOR_120_CONTROL_HALL_Open,
    .close               = RM_MOTOR_120_CONTROL_HALL_Close,
    .run                 = RM_MOTOR_120_CONTROL_HALL_Run,
    .stop                = RM_MOTOR_120_CONTROL_HALL_Stop,
    .reset               = RM_MOTOR_120_CONTROL_HALL_Reset,
    .speedSet            = RM_MOTOR_120_CONTROL_HALL_SpeedSet,
    .speedGet            = RM_MOTOR_120_CONTROL_HALL_SpeedGet,
    .currentGet          = RM_MOTOR_120_CONTROL_HALL_CurrentGet,
    .waitStopFlagGet     = RM_MOTOR_120_CONTROL_HALL_WaitStopFlagGet,
    .timeoutErrorFlagGet = RM_MOTOR_120_CONTROL_HALL_TimeoutErrorFlagGet,
    .patternErrorFlagGet = RM_MOTOR_120_CONTROL_HALL_PatternErrorFlagGet,
    .voltageRefGet       = RM_MOTOR_120_CONTROL_HALL_VoltageRefGet,
    .parameterUpdate     = RM_MOTOR_120_CONTROL_HALL_ParameterUpdate,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_120_CONTROL_HALL
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the motor hall 120 detection module. Implements @ref motor_120_control_api_t::open.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_Open
 *
 * @retval FSP_SUCCESS              Motor 120 driver successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_Open (motor_120_control_ctrl_t * const      p_ctrl,
                                          motor_120_control_cfg_t const * const p_cfg)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    motor_120_control_hall_extended_cfg_t * p_extended_cfg = (motor_120_control_hall_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(p_cfg->motor_param.u4_motor_pp != 0, FSP_ERR_INVALID_ARGUMENT);
#endif
    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->f_rpm2rad = (float) (p_instance_ctrl->p_cfg->motor_param.u4_motor_pp) *
                                 MOTOR_120_CONTROL_HALL_TWOPI_DIV_60;
    p_instance_ctrl->f4_speed_calc_base =
        MOTOR_120_CONTROL_HALL_TWOPI * (float) p_instance_ctrl->p_cfg->u4_free_run_timer_freq *
        (float) MOTOR_120_CONTROL_HALL_HZ_TRANS * (float) MOTOR_120_CONTROL_HALL_HZ_TRANS;

    /* Open motor 120 driver access module */
    if (p_extended_cfg->p_motor_120_driver_instance != NULL)
    {
        p_extended_cfg->p_motor_120_driver_instance->p_api->open(p_extended_cfg->p_motor_120_driver_instance->p_ctrl,
                                                                 p_extended_cfg->p_motor_120_driver_instance->p_cfg);
    }

    /* Open speed cyclic timer module */
    if (p_extended_cfg->p_speed_cyclic_timer_instance != NULL)
    {
        p_extended_cfg->p_speed_cyclic_timer_instance->p_api->open(
            p_extended_cfg->p_speed_cyclic_timer_instance->p_ctrl,
            p_extended_cfg->p_speed_cyclic_timer_instance->p_cfg);
        p_extended_cfg->p_speed_cyclic_timer_instance->p_api->start(
            p_extended_cfg->p_speed_cyclic_timer_instance->p_ctrl);
    }

    /* Open speed calculation timer module */
    if (p_extended_cfg->p_speed_calc_timer_instance != NULL)
    {
        p_extended_cfg->p_speed_calc_timer_instance->p_api->open(p_extended_cfg->p_speed_calc_timer_instance->p_ctrl,
                                                                 p_extended_cfg->p_speed_calc_timer_instance->p_cfg);
        p_extended_cfg->p_speed_calc_timer_instance->p_api->start(p_extended_cfg->p_speed_calc_timer_instance->p_ctrl);

        timer_info_t timer_info;
        p_extended_cfg->p_speed_calc_timer_instance->p_api->infoGet(p_extended_cfg->p_speed_calc_timer_instance->p_ctrl,
                                                                    &timer_info);
        p_instance_ctrl->timer_direction = timer_info.count_direction;
    }

    /* Open hall interrupt module */
    if ((p_extended_cfg->p_u_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_v_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_w_hall_irq_instance != NULL))
    {
        p_extended_cfg->p_u_hall_irq_instance->p_api->open(p_extended_cfg->p_u_hall_irq_instance->p_ctrl,
                                                           p_extended_cfg->p_u_hall_irq_instance->p_cfg);
        p_extended_cfg->p_v_hall_irq_instance->p_api->open(p_extended_cfg->p_v_hall_irq_instance->p_ctrl,
                                                           p_extended_cfg->p_v_hall_irq_instance->p_cfg);
        p_extended_cfg->p_w_hall_irq_instance->p_api->open(p_extended_cfg->p_w_hall_irq_instance->p_ctrl,
                                                           p_extended_cfg->p_w_hall_irq_instance->p_cfg);
        p_extended_cfg->p_u_hall_irq_instance->p_api->callbackSet(p_extended_cfg->p_u_hall_irq_instance->p_ctrl,
                                                                  rm_motor_120_control_hall_interrupt,
                                                                  p_instance_ctrl,
                                                                  NULL);
        p_extended_cfg->p_v_hall_irq_instance->p_api->callbackSet(p_extended_cfg->p_v_hall_irq_instance->p_ctrl,
                                                                  rm_motor_120_control_hall_interrupt,
                                                                  p_instance_ctrl,
                                                                  NULL);
        p_extended_cfg->p_w_hall_irq_instance->p_api->callbackSet(p_extended_cfg->p_w_hall_irq_instance->p_ctrl,
                                                                  rm_motor_120_control_hall_interrupt,
                                                                  p_instance_ctrl,
                                                                  NULL);
        p_extended_cfg->p_u_hall_irq_instance->p_api->enable(p_extended_cfg->p_u_hall_irq_instance->p_ctrl);
        p_extended_cfg->p_v_hall_irq_instance->p_api->enable(p_extended_cfg->p_v_hall_irq_instance->p_ctrl);
        p_extended_cfg->p_w_hall_irq_instance->p_api->enable(p_extended_cfg->p_w_hall_irq_instance->p_ctrl);
    }

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_120_CONTROL_HALL_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified motor hall 120 detection module. Implements @ref motor_120_control_api_t::close.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_Close
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_Close (motor_120_control_ctrl_t * const p_ctrl)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    rm_motor_120_control_hall_reset(p_instance_ctrl);

    /* close motor 120 driver access */
    if (p_extended_cfg->p_motor_120_driver_instance != NULL)
    {
        p_extended_cfg->p_motor_120_driver_instance->p_api->close(p_extended_cfg->p_motor_120_driver_instance->p_ctrl);
    }

    /* close speed cyclic timer module */
    if (p_extended_cfg->p_speed_cyclic_timer_instance != NULL)
    {
        p_extended_cfg->p_speed_cyclic_timer_instance->p_api->close(
            p_extended_cfg->p_speed_cyclic_timer_instance->p_ctrl);
    }

    /* close speed calculation timer module */
    if (p_extended_cfg->p_speed_calc_timer_instance != NULL)
    {
        p_extended_cfg->p_speed_calc_timer_instance->p_api->close(p_extended_cfg->p_speed_calc_timer_instance->p_ctrl);
    }

    /* close hall interrupt module */
    if ((p_extended_cfg->p_u_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_v_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_w_hall_irq_instance != NULL))
    {
        p_extended_cfg->p_u_hall_irq_instance->p_api->close(p_extended_cfg->p_u_hall_irq_instance->p_ctrl);
        p_extended_cfg->p_v_hall_irq_instance->p_api->close(p_extended_cfg->p_v_hall_irq_instance->p_ctrl);
        p_extended_cfg->p_w_hall_irq_instance->p_api->close(p_extended_cfg->p_w_hall_irq_instance->p_ctrl);
        p_extended_cfg->p_u_hall_irq_instance->p_api->disable(p_extended_cfg->p_u_hall_irq_instance->p_ctrl);
        p_extended_cfg->p_v_hall_irq_instance->p_api->disable(p_extended_cfg->p_v_hall_irq_instance->p_ctrl);
        p_extended_cfg->p_w_hall_irq_instance->p_api->disable(p_extended_cfg->p_w_hall_irq_instance->p_ctrl);
    }

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Run motor (Start motor rotation). Implements @ref motor_120_control_api_t::run.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_Run
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_Run (motor_120_control_ctrl_t * const p_ctrl)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    p_instance_ctrl->active = MOTOR_120_CONTROL_STATUS_ACTIVE;

    if (p_extended_cfg->p_motor_120_driver_instance != NULL)
    {
        p_extended_cfg->p_motor_120_driver_instance->p_api->run(p_extended_cfg->p_motor_120_driver_instance->p_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop motor (Stop motor rotation). Implements @ref motor_120_control_api_t::stop.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_Stop
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_Stop (motor_120_control_ctrl_t * const p_ctrl)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    rm_motor_120_control_hall_reset(p_instance_ctrl);

    if (p_extended_cfg->p_motor_120_driver_instance != NULL)
    {
        p_extended_cfg->p_motor_120_driver_instance->p_api->stop(p_extended_cfg->p_motor_120_driver_instance->p_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of motor hall 120 detection module. Implements @ref motor_120_control_api_t::reset.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_Reset
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_Reset (motor_120_control_ctrl_t * const p_ctrl)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    rm_motor_120_control_hall_reset(p_instance_ctrl);

    /* reset motor 120 driver access */
    if (p_extended_cfg->p_motor_120_driver_instance != NULL)
    {
        p_extended_cfg->p_motor_120_driver_instance->p_api->reset(p_extended_cfg->p_motor_120_driver_instance->p_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set speed[rpm]. Implements @ref motor_120_control_api_t::speedSet.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_SpeedSet
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_SpeedSet (motor_120_control_ctrl_t * const p_ctrl, float const speed_rpm)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (speed_rpm >= 0)
    {
        p_instance_ctrl->direction        = MOTOR_120_CONTROL_ROTATION_DIRECTION_CW;
        p_instance_ctrl->f4_ref_speed_rad = speed_rpm * p_instance_ctrl->f_rpm2rad;
    }
    else
    {
        p_instance_ctrl->direction        = MOTOR_120_CONTROL_ROTATION_DIRECTION_CCW;
        p_instance_ctrl->f4_ref_speed_rad = (-speed_rpm) * p_instance_ctrl->f_rpm2rad;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get speed. Implements @ref motor_120_control_api_t::speedGet.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_SpeedGet
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_SpeedGet (motor_120_control_ctrl_t * const p_ctrl, float * const p_speed_rpm)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(p_speed_rpm != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    if (p_instance_ctrl->direction == MOTOR_120_CONTROL_ROTATION_DIRECTION_CW)
    {
        *p_speed_rpm = p_instance_ctrl->f4_speed_rad / p_instance_ctrl->f_rpm2rad;
    }
    else
    {
        *p_speed_rpm = (-p_instance_ctrl->f4_speed_rad) / p_instance_ctrl->f_rpm2rad;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get current. Implements @ref motor_120_control_api_t::currentGet.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_CurrentGet
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_CurrentGet (motor_120_control_ctrl_t * const          p_ctrl,
                                                motor_120_driver_current_status_t * const p_current_status)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl =
        (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(NULL != p_current_status, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_driver_instance != NULL)
    {
        p_extended_cfg->p_motor_120_driver_instance->p_api->currentGet(
            p_extended_cfg->p_motor_120_driver_instance->p_ctrl,
            p_current_status);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get wait stop flag. Implements @ref motor_120_control_api_t::waitStopFlagGet.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_WaitStopFlagGet
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_WaitStopFlagGet (motor_120_control_ctrl_t * const           p_ctrl,
                                                     motor_120_control_wait_stop_flag_t * const p_flag)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(p_flag != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    *p_flag = p_instance_ctrl->flag_wait_stop;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get timeout error flag. Implements @ref motor_120_control_api_t::timeoutErrorFlagGet.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_TimeoutErrorFlagGet
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_TimeoutErrorFlagGet (motor_120_control_ctrl_t * const               p_ctrl,
                                                         motor_120_control_timeout_error_flag_t * const p_timeout_error_flag)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(p_timeout_error_flag != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    *p_timeout_error_flag = p_instance_ctrl->timeout_error_flag;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get pattern error flag. Implements @ref motor_120_control_api_t::patternErrorFlagGet.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_PatternErrorFlagGet
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_PatternErrorFlagGet (motor_120_control_ctrl_t * const               p_ctrl,
                                                         motor_120_control_pattern_error_flag_t * const p_pattern_error_flag)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(p_pattern_error_flag != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    *p_pattern_error_flag = p_instance_ctrl->pattern_error_flag;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get voltage ref. Implements @ref motor_120_control_api_t::voltageRefGet.
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_VoltageRefGet
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_VoltageRefGet (motor_120_control_ctrl_t * const        p_ctrl,
                                                   motor_120_control_voltage_ref_t * const p_voltage_ref)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl =
        (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(p_voltage_ref != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    *p_voltage_ref = p_instance_ctrl->flag_voltage_ref;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of hall 120 detection module. Implements @ref motor_120_control_api_t::parameterUpdate
 *
 * Example:
 * @snippet rm_motor_120_control_hall_example.c RM_MOTOR_120_CONTROL_HALL_ParameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data was updated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_CONTROL_HALL_ParameterUpdate (motor_120_control_ctrl_t * const      p_ctrl,
                                                     motor_120_control_cfg_t const * const p_cfg)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl = (motor_120_control_hall_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_CONTROL_HALL_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(MOTOR_120_CONTROL_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_CONTROL_HALL_ERROR_RETURN(p_cfg->motor_param.u4_motor_pp != 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->f_rpm2rad = (float) (p_instance_ctrl->p_cfg->motor_param.u4_motor_pp) *
                                 MOTOR_120_CONTROL_HALL_TWOPI_DIV_60;
    p_instance_ctrl->f4_speed_calc_base =
        MOTOR_120_CONTROL_HALL_TWOPI * (float) p_instance_ctrl->p_cfg->u4_free_run_timer_freq *
        (float) MOTOR_120_CONTROL_HALL_HZ_TRANS * (float) MOTOR_120_CONTROL_HALL_HZ_TRANS;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_CONTROL_HALL)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/******************************************************************************
 * Function Name : rm_motor_120_control_hall_interrupt
 * Description   : Process for hall sensor interrupt
 * Arguments     : p_args - The pointer to used arguments
 * Return Value  : none
 ******************************************************************************/
void rm_motor_120_control_hall_interrupt (external_irq_callback_args_t * p_args)
{
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl =
        (motor_120_control_hall_instance_ctrl_t *) p_args->p_context;
    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (p_instance_ctrl->u4_adc_interrupt_cnt == 0)
    {
        if (MOTOR_120_CONTROL_WAIT_STOP_FLAG_SET != p_instance_ctrl->flag_wait_stop) /* waiting for motor stop */
        {
            if (MOTOR_120_CONTROL_STATUS_ACTIVE == p_instance_ctrl->active)          /* check system mode */
            {
                rm_motor_120_control_hall_pattern_set(p_instance_ctrl);
            }
        }
        else
        {
            p_instance_ctrl->u4_cnt_wait_stop = p_extended_cfg->u4_stop_judge_time;
        }

        if (p_instance_ctrl->u4_hall_intr_cnt < (p_extended_cfg->u4_hall_wait_cnt + 1))
        {
            p_instance_ctrl->u4_hall_intr_cnt++;
        }

        /* timeout error check */
        if ((MOTOR_120_CONTROL_STATUS_ACTIVE == p_instance_ctrl->active) &&
            (MOTOR_120_CONTROL_RUN_MODE_INIT != p_instance_ctrl->run_mode))

        /* check system & run mode */
        {
            p_instance_ctrl->u4_cnt_timeout = 0; /* timeout counter reset */
        }

        p_instance_ctrl->u4_adc_interrupt_cnt = p_extended_cfg->u4_hall_interrupt_mask_value;
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_speed_cyclic
 * Description   : Cyclic process of speed control (Call at timer interrupt)
 * Arguments     : p_args - The pointer to used arguments
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_120_control_hall_speed_cyclic (timer_callback_args_t * p_args)
{
    motor_120_control_instance_t           * p_instance      = (motor_120_control_instance_t *) p_args->p_context;
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl =
        (motor_120_control_hall_instance_ctrl_t *) p_instance->p_ctrl;
    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    motor_120_driver_instance_t const * p_driver_instance = p_extended_cfg->p_motor_120_driver_instance;

    motor_120_driver_flag_offset_calc_t u1_temp_flag_offset;

    motor_120_control_callback_args_t temp_args_t;

    if (NULL != p_instance->p_cfg->p_callback)
    {
        temp_args_t.event     = MOTOR_120_CONTROL_EVENT_CYCLE_FORWARD;
        temp_args_t.p_context = p_instance->p_cfg->p_context;
        (p_instance->p_cfg->p_callback)(&temp_args_t);
    }

    if (MOTOR_120_CONTROL_STATUS_ACTIVE == p_instance_ctrl->active)
    {
        /* RUN mode state management */
        switch (p_instance_ctrl->run_mode)
        {
            /* Init state */
            case MOTOR_120_CONTROL_RUN_MODE_INIT:
            {
                p_driver_instance->p_api->flagCurrentOffsetGet(p_driver_instance->p_ctrl, &u1_temp_flag_offset);

                /* When offset calibration finished & motor stopped, motor control starts. */
                if ((MOTOR_120_DRIVER_FLAG_OFFSET_CALC_ALL_FINISH == u1_temp_flag_offset) &&
                    (MOTOR_120_CONTROL_WAIT_STOP_FLAG_CLEAR == p_instance_ctrl->flag_wait_stop))
                {
                    p_instance_ctrl->flag_voltage_ref = MOTOR_120_CONTROL_VOLTAGE_REF_CONST;
                    rm_motor_120_control_hall_voltage_ref_set(p_instance_ctrl); /* set voltage reference */

                    p_driver_instance->p_api->phaseVoltageSet(p_driver_instance->p_ctrl,
                                                              p_instance_ctrl->f4_v_ref,
                                                              p_instance_ctrl->f4_v_ref,
                                                              p_instance_ctrl->f4_v_ref);

                    rm_motor_120_control_hall_pattern_set(p_instance_ctrl); /* Set voltage pattern */

                    p_instance_ctrl->run_mode = MOTOR_120_CONTROL_RUN_MODE_BOOT;
                }

                break;
            }

            /* Boot state */
            case MOTOR_120_CONTROL_RUN_MODE_BOOT:
            {
                /* wait the speed become over minimum speed */
                if (p_instance_ctrl->f4_speed_rad >=
                    ((float) p_extended_cfg->u4_min_speed_rpm * p_instance_ctrl->f_rpm2rad))
                {
                    p_instance_ctrl->run_mode = MOTOR_120_CONTROL_RUN_MODE_DRIVE;

                    /* change to normal(PI) control mode */
                }

                rm_motor_120_control_hall_speed_ref_set(p_instance_ctrl);   /* set speed reference */
                rm_motor_120_control_hall_voltage_ref_set(p_instance_ctrl); /* set voltage reference */

                p_driver_instance->p_api->phaseVoltageSet(p_driver_instance->p_ctrl,
                                                          p_instance_ctrl->f4_v_ref,
                                                          p_instance_ctrl->f4_v_ref,
                                                          p_instance_ctrl->f4_v_ref);
                break;
            }

            /* Normal drive (PI control) state */
            case MOTOR_120_CONTROL_RUN_MODE_DRIVE:
            {
                rm_motor_120_control_hall_speed_ref_set(p_instance_ctrl);   /* set speed reference */
                rm_motor_120_control_hall_voltage_ref_set(p_instance_ctrl); /* set voltage reference */

                /* duty calculate */
                p_driver_instance->p_api->phaseVoltageSet(p_driver_instance->p_ctrl,
                                                          p_instance_ctrl->f4_v_ref,
                                                          p_instance_ctrl->f4_v_ref,
                                                          p_instance_ctrl->f4_v_ref);
                break;
            }

            default:
            {
                /* Do nothing */
                break;
            }
        }

        /* Timeout error handling */
        /* check run mode */
        if (MOTOR_120_CONTROL_RUN_MODE_INIT != p_instance_ctrl->run_mode)
        {
            if (p_instance_ctrl->u4_cnt_timeout <= p_instance->p_cfg->u4_timeout_cnt)
            {
                p_instance_ctrl->u4_cnt_timeout++;
            }
        }
        else
        {
            p_instance_ctrl->u4_cnt_timeout = 0;
        }
    }

    if (NULL != p_instance->p_cfg->p_callback)
    {
        temp_args_t.event     = MOTOR_120_CONTROL_EVENT_CYCLE_BACKWARD;
        temp_args_t.p_context = p_instance->p_cfg->p_context;
        (p_instance->p_cfg->p_callback)(&temp_args_t);
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_driver_callback
 * Description   : Cyclic process for driver accsess (Call at A/D conversion finish interrupt)
 * Arguments     : p_args - The pointer to used arguments
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_120_control_hall_driver_callback (motor_120_driver_callback_args_t * p_args)
{
    motor_120_control_instance_t           * p_instance      = (motor_120_control_instance_t *) p_args->p_context;
    motor_120_control_hall_instance_ctrl_t * p_instance_ctrl =
        (motor_120_control_hall_instance_ctrl_t *) p_instance->p_ctrl;
    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    motor_120_driver_instance_t const * p_driver_instance =
        (motor_120_driver_instance_t *) p_extended_cfg->p_motor_120_driver_instance;
    motor_120_control_callback_args_t temp_args_t;

    switch (p_args->event)
    {
        case MOTOR_120_DRIVER_EVENT_FORWARD:
        {
            if (NULL != p_instance->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_120_CONTROL_EVENT_ADC_FORWARD;
                temp_args_t.p_context = p_instance->p_cfg->p_context;
                (p_instance->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        case MOTOR_120_DRIVER_EVENT_120_CONTROL:
        {
            p_driver_instance->p_api->currentOffsetCalc(p_driver_instance->p_ctrl);

            /* wait motor stop */
            rm_motor_120_control_hall_wait_motorstop(p_instance_ctrl);

            rm_motor_120_control_hall_check_timeout_error(p_instance_ctrl, p_instance->p_cfg->u4_timeout_cnt);

            if (p_instance_ctrl->u4_adc_interrupt_cnt != 0)
            {
                p_instance_ctrl->u4_adc_interrupt_cnt--;
            }

            break;
        }

        case MOTOR_120_DRIVER_EVENT_BACKWARD:
        {
            if (NULL != p_instance->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_120_CONTROL_EVENT_ADC_BACKWARD;
                temp_args_t.p_context = p_instance->p_cfg->p_context;
                (p_instance->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        default:
        {
            /* Do nothing */
            break;
        }
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_reset
 * Description   : Resets driver variables
 * Arguments     : p_ctrl - The pointer to the motor 120 driver instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_reset (motor_120_control_hall_instance_ctrl_t * p_ctrl)
{
    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    uint8_t u8_loop_cnt;

    p_ctrl->active             = MOTOR_120_CONTROL_STATUS_INACTIVE;
    p_ctrl->run_mode           = MOTOR_120_CONTROL_RUN_MODE_INIT;
    p_ctrl->timeout_error_flag = MOTOR_120_CONTROL_TIMEOUT_ERROR_FLAG_CLEAR;
    p_ctrl->pattern_error_flag = MOTOR_120_CONTROL_PATTERN_ERROR_FLAG_CLEAR;

    p_ctrl->direction             = MOTOR_120_CONTROL_ROTATION_DIRECTION_CW;
    p_ctrl->f4_v_ref              = 0.0F;
    p_ctrl->f4_ref_speed_rad      = 0.0F;
    p_ctrl->f4_ref_speed_rad_ctrl = 0.0F;
    p_ctrl->u4_cnt_speed_pi       = 0U;
    p_ctrl->flag_wait_stop        = MOTOR_120_CONTROL_WAIT_STOP_FLAG_CLEAR;
    p_ctrl->f4_speed_rad          = 0.0F;
    p_ctrl->v_pattern             = MOTOR_120_DRIVER_PHASE_PATTERN_ERROR;
    p_ctrl->flag_speed_ref        = MOTOR_120_CONTROL_SPEED_REF_ZERO_CONST;
    p_ctrl->flag_voltage_ref      = MOTOR_120_CONTROL_VOLTAGE_REF_ZERO_CONST;
    p_ctrl->u4_cnt_timeout        = 0U;
    p_ctrl->u4_hall_timer_cnt     = 0U;
    p_ctrl->u4_pre_hall_timer_cnt = 0U;
    p_ctrl->s4_timer_cnt_ave      = 0U;
    for (u8_loop_cnt = 0; u8_loop_cnt < MOTOR_120_CONTROL_HALL_TIMES; u8_loop_cnt++)
    {
        p_ctrl->u4_timer_cnt_buf[u8_loop_cnt] = 0U;
    }

    p_ctrl->u4_timer_cnt_num = 0U;
    p_ctrl->u4_cnt_wait_stop = p_extended_cfg->u4_stop_judge_time;

    p_ctrl->u4_hall_intr_cnt = 0U;

    p_ctrl->u4_adc_interrupt_cnt = 0U;
}                                      /* End of function rm_motor_120_control_hall_reset() */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_speed_calc
 * Description   : Calculate motor speed
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_speed_calc (motor_120_control_hall_instance_ctrl_t * p_ctrl)
{
    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint32_t       u4_temp;
    float          f4_temp_speed_rad;
    timer_status_t gpt_timer_status;

    p_extended_cfg->p_speed_calc_timer_instance->p_api->statusGet(p_extended_cfg->p_speed_calc_timer_instance->p_ctrl,
                                                                  &gpt_timer_status); /* get value of timer counter */
    p_ctrl->u4_hall_timer_cnt = gpt_timer_status.counter;

    if (TIMER_DIRECTION_UP == p_ctrl->timer_direction)
    {
        if (p_ctrl->u4_pre_hall_timer_cnt != 0)
        {
            if (p_ctrl->u4_hall_timer_cnt >= p_ctrl->u4_pre_hall_timer_cnt)
            {
                u4_temp = (p_ctrl->u4_hall_timer_cnt - p_ctrl->u4_pre_hall_timer_cnt);

                /* calculate timer count in 60 degrees */
            }
            else
            {
                u4_temp = ((p_extended_cfg->p_speed_calc_timer_instance->p_cfg->period_counts - 1) -
                           p_ctrl->u4_pre_hall_timer_cnt) + p_ctrl->u4_hall_timer_cnt;
            }
        }
        else
        {
            u4_temp = p_ctrl->u4_hall_timer_cnt;
        }
    }
    else
    {
        if (p_ctrl->u4_pre_hall_timer_cnt != 0)
        {
            if (p_ctrl->u4_hall_timer_cnt <= p_ctrl->u4_pre_hall_timer_cnt)
            {
                u4_temp = (p_ctrl->u4_pre_hall_timer_cnt - p_ctrl->u4_hall_timer_cnt);

                /* calculate timer count in 60 degrees */
            }
            else
            {
                u4_temp = ((p_extended_cfg->p_speed_calc_timer_instance->p_cfg->period_counts - 1) -
                           p_ctrl->u4_hall_timer_cnt) + p_ctrl->u4_pre_hall_timer_cnt;
            }
        }
        else
        {
            u4_temp = p_ctrl->u4_hall_timer_cnt;
        }
    }

    /* average 6 times of motor speed timer */
    p_ctrl->s4_timer_cnt_ave -= (int32_t) p_ctrl->u4_timer_cnt_buf[p_ctrl->u4_timer_cnt_num];
    p_ctrl->u4_timer_cnt_buf[p_ctrl->u4_timer_cnt_num] = u4_temp;
    p_ctrl->s4_timer_cnt_ave += (int32_t) u4_temp;

    p_ctrl->u4_timer_cnt_num++;
    if (p_ctrl->u4_timer_cnt_num >= MOTOR_120_CONTROL_HALL_TIMES)
    {
        p_ctrl->u4_timer_cnt_num = 0;
    }

    /* calculate motor speed */
    /* check start calculation */
    if ((MOTOR_120_CONTROL_RUN_MODE_INIT != p_ctrl->run_mode) &&
        (p_ctrl->u4_hall_intr_cnt > p_extended_cfg->u4_hall_wait_cnt))
    {
        /* Avoid zero divide */
        if (p_ctrl->s4_timer_cnt_ave != 0)
        {
            f4_temp_speed_rad = p_ctrl->f4_speed_calc_base / (float) p_ctrl->s4_timer_cnt_ave;
        }
        else
        {
            f4_temp_speed_rad = 0;
        }

        p_ctrl->f4_speed_rad = rm_motor_120_control_hall_lpff(f4_temp_speed_rad,
                                                              p_ctrl->f4_speed_rad,
                                                              p_ctrl->p_cfg->f4_speed_lpf_k);
    }

    p_ctrl->u4_pre_hall_timer_cnt = p_ctrl->u4_hall_timer_cnt; /* keep timer counter value */
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_wait_motorstop
 * Description   : Wait for motor stop
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_wait_motorstop (motor_120_control_hall_instance_ctrl_t * p_ctrl)
{
    /* wait motor stop */
    if (MOTOR_120_CONTROL_WAIT_STOP_FLAG_SET == p_ctrl->flag_wait_stop) /* waiting for motor stop */
    {
        p_ctrl->u4_cnt_wait_stop--;
        if (0 == p_ctrl->u4_cnt_wait_stop)                              /* motor stop detect counter */
        {
            p_ctrl->flag_wait_stop = MOTOR_120_CONTROL_WAIT_STOP_FLAG_CLEAR;
        }
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_pattern_set
 * Description   : Set voltage pattern
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance,
 *               : u1_signal - voltage pattern
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_pattern_set (motor_120_control_hall_instance_ctrl_t * p_ctrl)
{
    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    motor_120_driver_instance_t const * p_driver_instance = p_extended_cfg->p_motor_120_driver_instance;

    uint32_t u4_temp_level;
    uint8_t  u1_signal = 0x00;

    rm_motor_120_control_hall_speed_calc(p_ctrl);

    /* Get/save the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* get hall signal */
    u4_temp_level = R_BSP_PinRead(p_extended_cfg->port_hall_sensor_u);
    u1_signal     = (uint8_t) (u4_temp_level << 2);
    u4_temp_level = R_BSP_PinRead(p_extended_cfg->port_hall_sensor_v);
    u1_signal    |= (uint8_t) (u4_temp_level << 1);
    u4_temp_level = R_BSP_PinRead(p_extended_cfg->port_hall_sensor_w);
    u1_signal    |= (uint8_t) (u4_temp_level);

    /* set voltage pattern */
    if (MOTOR_120_CONDUCTION_TYPE_FIRST60 == p_ctrl->p_cfg->conduction_type)
    {
        /* First 60 degree PWM */
        rm_motor_120_control_hall_pattern_first60(p_ctrl, u1_signal);
    }
    else
    {
        /* Complementary first 60 degree PWM */
        rm_motor_120_control_hall_pattern_first60_comp(p_ctrl, u1_signal);
    }

    if (MOTOR_120_DRIVER_PHASE_PATTERN_ERROR == p_ctrl->v_pattern)
    {
        p_ctrl->pattern_error_flag = MOTOR_120_CONTROL_PATTERN_ERROR_FLAG_SET;
    }
    else
    {
        p_ctrl->pattern_error_flag = MOTOR_120_CONTROL_PATTERN_ERROR_FLAG_CLEAR;
    }

    if (MOTOR_120_CONTROL_STATUS_ACTIVE == p_ctrl->active) /* check system mode */
    {
        p_driver_instance->p_api->phasePatternSet(p_driver_instance->p_ctrl, p_ctrl->v_pattern);
    }

    /* Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_pattern_first60
 * Description   : Set voltage pattern first 60 degree PWM
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance,
 *               : u1_signal - voltage pattern
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_pattern_first60 (motor_120_control_hall_instance_ctrl_t * p_ctrl,
                                                       uint8_t                                  u1_signal)
{
    /* set voltage pattern */
    if (MOTOR_120_CONTROL_ROTATION_DIRECTION_CW == p_ctrl->direction) /* check rotational direction */
    {
        switch (u1_signal)
        {
            case MOTOR_120_CONTROL_HALL_PATTERN_CW_W_V:               /* from W phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_VN_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_U_V: /* from U phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_UP_PWM_VN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_U_W: /* from U phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_WN_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_V_W: /* from V phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_VP_PWM_WN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_V_U: /* from V phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_UN_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_W_U: /* from W phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_WP_PWM_UN_ON;
                break;
            }

            default:                   /* hall signal pattern error */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_ERROR;
                break;
            }
        }
    }
    else if (MOTOR_120_CONTROL_ROTATION_DIRECTION_CCW == p_ctrl->direction) /* check rotational direction */
    {
        switch (u1_signal)
        {
            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_W_V:                    /* from W phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_WP_PWM_VN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_W_U: /* from W phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_UN_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_V_U: /* from V phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_VP_PWM_UN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_V_W: /* from V phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_WN_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_U_W: /* from U phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_UP_PWM_WN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_U_V: /* from U phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_VN_PWM;
                break;
            }

            default:                   /* hall signal pattern error */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_ERROR;
                break;
            }
        }
    }
    else
    {
        /* Do nothing */
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_pattern_first60_comp
 * Description   : Set voltage pattern first 60 degree PWM
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance,
 *               : u1_signal - voltage pattern
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_pattern_first60_comp (motor_120_control_hall_instance_ctrl_t * p_ctrl,
                                                            uint8_t                                  u1_signal)
{
    /* set voltage pattern */
    if (MOTOR_120_CONTROL_ROTATION_DIRECTION_CW == p_ctrl->direction) /* check rotational direction */
    {
        switch (u1_signal)
        {
            case MOTOR_120_CONTROL_HALL_PATTERN_CW_W_V:               /* from W phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_V_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_U_V: /* from U phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_U_PWM_VN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_U_W: /* from U phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_W_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_V_W: /* from V phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_V_PWM_WN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_V_U: /* from V phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_U_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CW_W_U: /* from W phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_W_PWM_UN_ON;
                break;
            }

            default:                   /* hall signal pattern error */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_ERROR;
                break;
            }
        }
    }
    else if (MOTOR_120_CONTROL_ROTATION_DIRECTION_CCW == p_ctrl->direction) /* check rotational direction */
    {
        switch (u1_signal)
        {
            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_W_V:                    /* from W phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_W_PWM_VN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_W_U: /* from W phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_U_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_V_U: /* from V phase to U phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_V_PWM_UN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_V_W: /* from V phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_W_PWM;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_U_W: /* from U phase to W phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_U_PWM_WN_ON;
                break;
            }

            case MOTOR_120_CONTROL_HALL_PATTERN_CCW_U_V: /* from U phase to V phase */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_V_PWM;
                break;
            }

            default:                   /* hall signal pattern error */
            {
                p_ctrl->v_pattern = MOTOR_120_DRIVER_PHASE_PATTERN_ERROR;
                break;
            }
        }
    }
    else
    {
        /* Do nothing */
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_speed_ref_set
 * Description   : Set speed reference
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance,
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_speed_ref_set (motor_120_control_hall_instance_ctrl_t * const p_ctrl)
{
    float f4_ref_speed_rad_buff;
    float f4_limit_speed_change;

    f4_ref_speed_rad_buff = p_ctrl->f4_ref_speed_rad_ctrl;

    switch (p_ctrl->flag_speed_ref)
    {
        case MOTOR_120_CONTROL_SPEED_REF_ZERO_CONST:
        {
            if (MOTOR_120_CONTROL_RUN_MODE_DRIVE == p_ctrl->run_mode)
            {
                /* Set PI control parameter for start */
                f4_ref_speed_rad_buff  = p_ctrl->f4_speed_rad;
                p_ctrl->flag_speed_ref = MOTOR_120_CONTROL_SPEED_REF_CHANGE;
            }

            break;
        }

        case MOTOR_120_CONTROL_SPEED_REF_CHANGE:
        {
            f4_limit_speed_change = p_ctrl->p_cfg->f4_limit_speed_change;

            if (p_ctrl->f4_ref_speed_rad > f4_ref_speed_rad_buff)
            {
                f4_ref_speed_rad_buff += f4_limit_speed_change;
                f4_ref_speed_rad_buff  = rm_motor_120_control_hall_limitf_h(f4_ref_speed_rad_buff,
                                                                            p_ctrl->f4_ref_speed_rad);
            }
            else if (p_ctrl->f4_ref_speed_rad < f4_ref_speed_rad_buff)
            {
                f4_ref_speed_rad_buff -= f4_limit_speed_change;
                f4_ref_speed_rad_buff  = rm_motor_120_control_hall_limitf_l(f4_ref_speed_rad_buff,
                                                                            p_ctrl->f4_ref_speed_rad);
            }
            else
            {
                /* Do nothing */
            }

            break;
        }

        default:
        {
            /* Do nothing */
            break;
        }
    }

    p_ctrl->f4_ref_speed_rad_ctrl = f4_ref_speed_rad_buff;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_voltage_ref_set
 * Description   : Set voltage reference
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance,
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_voltage_ref_set (motor_120_control_hall_instance_ctrl_t * const p_ctrl)
{
    motor_120_control_hall_extended_cfg_t * p_extended_cfg =
        (motor_120_control_hall_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    float f4_temp;

    switch (p_ctrl->flag_voltage_ref)
    {
        case MOTOR_120_CONTROL_VOLTAGE_REF_CONST:
        {
            /* Set start reference voltage(constant) */
            p_ctrl->f4_v_ref = p_extended_cfg->f4_start_refv;
            if (MOTOR_120_CONTROL_RUN_MODE_DRIVE == p_ctrl->run_mode)
            {
                /* Set PI control parameter for start */
                p_ctrl->f4_pi_ctrl_refi  = p_ctrl->f4_v_ref;
                p_ctrl->flag_voltage_ref = MOTOR_120_CONTROL_VOLTAGE_REF_PI_OUTPUT;
            }

            break;
        }

        case MOTOR_120_CONTROL_VOLTAGE_REF_PI_OUTPUT:
        {
            /* PI control */
            p_ctrl->u4_cnt_speed_pi++;
            if (p_ctrl->p_cfg->u4_speed_pi_decimation < p_ctrl->u4_cnt_speed_pi)
            /* check PI period  */
            {
                p_ctrl->u4_cnt_speed_pi = 0;

                p_ctrl->f4_pi_ctrl_err = p_ctrl->f4_ref_speed_rad_ctrl - p_ctrl->f4_speed_rad;
                f4_temp                = rm_motor_120_control_hall_pi_ctrl(p_ctrl);

                /* limit voltage */
                p_ctrl->f4_v_ref = rm_motor_120_control_hall_limitf(f4_temp,
                                                                    p_ctrl->p_cfg->f4_max_drive_v,
                                                                    p_ctrl->p_cfg->f4_min_drive_v);
            }

            break;
        }

        default:
        {
            /* Do nothing */
            break;
        }
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_pi_ctrl
 * Description   : PI control
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance,
 * Return Value  : PI control output value
 **********************************************************************************************************************/
static float rm_motor_120_control_hall_pi_ctrl (motor_120_control_hall_instance_ctrl_t * p_ctrl)
{
    float f4_err    = 0.0F;
    float f4_kp     = 0.0F;
    float f4_ki     = 0.0F;
    float f4_refp   = 0.0F;
    float f4_refi   = 0.0F;
    float f4_ref    = 0.0F;
    float f4_ilimit = 0.0F;

    f4_err    = p_ctrl->f4_pi_ctrl_err;
    f4_kp     = p_ctrl->p_cfg->f4_pi_ctrl_kp;
    f4_ki     = p_ctrl->p_cfg->f4_pi_ctrl_ki;
    f4_refi   = p_ctrl->f4_pi_ctrl_refi;
    f4_ilimit = p_ctrl->p_cfg->f4_pi_ctrl_ilimit;

    f4_refp  = f4_err * f4_kp;         /* proportional part */
    f4_refi += f4_err * f4_ki;         /* integral part */

    /* integral part limit */
    f4_refi                 = rm_motor_120_control_hall_limitf_abs(f4_refi, f4_ilimit);
    p_ctrl->f4_pi_ctrl_refi = f4_refi;

    f4_ref = f4_refp + f4_refi;        /* PI output */

    return f4_ref;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_check_timeout_error
 * Description   : Check timeout error
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance,
 *               : u2_timeout_limit - Hall timeout error detection time,
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_control_hall_check_timeout_error (motor_120_control_hall_instance_ctrl_t * p_ctrl,
                                                           uint32_t                                 u4_timeout_limit)
{
    if (p_ctrl->u4_cnt_timeout > u4_timeout_limit)
    {
        p_ctrl->timeout_error_flag = MOTOR_120_CONTROL_TIMEOUT_ERROR_FLAG_SET; /* hall timeout error */
    }
    else
    {
        p_ctrl->timeout_error_flag = MOTOR_120_CONTROL_TIMEOUT_ERROR_FLAG_CLEAR;
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_lpff
 * Description   : LPF prosess
 * Arguments     : f4_lpf_input      - LPF input value,
 *               : f4_pre_lpf_output - Previous LPF output value,
 *               : f4_lpf_k          - LPF parameter
 * Return Value  : LPF output value
 **********************************************************************************************************************/
static float rm_motor_120_control_hall_lpff (float f4_lpf_input, float f4_pre_lpf_output, float f4_lpf_k)
{
    float f4_temp;

    f4_temp = f4_pre_lpf_output + f4_lpf_k * (f4_lpf_input - f4_pre_lpf_output);

    return f4_temp;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_limitf
 * Description   : Limit with max limit value and minimum limit value
 * Arguments     : f4_value - Target value,
 *               : f4_max   - Max limit value,
 *               : f4_min   - Minimum limit value
 * Return Value  : limited target value
 **********************************************************************************************************************/
static float rm_motor_120_control_hall_limitf (float f4_value, float f4_max, float f4_min)
{
    float f4_temp;

    f4_temp = f4_value;
    if (f4_value > f4_max)
    {
        f4_temp = f4_max;
    }
    else if (f4_value < f4_min)
    {
        f4_temp = f4_min;
    }
    else
    {
        /* Do nothing */
    }

    return f4_temp;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_limitf_h
 * Description   : Limit with max limit value and minimum limit value
 * Arguments     : f4_value - Target value, f4_max - Max limit value
 * Return Value  : limited target value
 **********************************************************************************************************************/
static float rm_motor_120_control_hall_limitf_h (float f4_value, float f4_max)
{
    float f4_temp;

    f4_temp = f4_value;
    if (f4_value > f4_max)
    {
        f4_temp = f4_max;
    }

    return f4_temp;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_limitf_l
 * Description   : Limit with minimum limit value
 * Arguments     : f4_value - Target value, f4_min - Minimum limit value
 * Return Value  : limited target value
 **********************************************************************************************************************/
static float rm_motor_120_control_hall_limitf_l (float f4_value, float f4_min)
{
    float f4_temp;

    f4_temp = f4_value;
    if (f4_value < f4_min)
    {
        f4_temp = f4_min;
    }

    return f4_temp;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_120_control_hall_limitf_abs
 * Description   : Limit with absolute value
 * Arguments     : f4_value - Target value, f4_limit_value - Limit value
 * Return Value  : limited value
 **********************************************************************************************************************/
static float rm_motor_120_control_hall_limitf_abs (float f4_value, float f4_limit_value)
{
    float f4_temp0;

    f4_temp0 = fabsf(f4_value);
    if (f4_temp0 > f4_limit_value)
    {
        f4_value = copysignf(f4_limit_value, f4_value);
    }

    return f4_value;
}
