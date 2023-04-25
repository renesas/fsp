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
#include "rm_motor_120_driver.h"
#include "r_gpt.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define MOTOR_120_DRIVER_OPEN                    (0x4D543144L)

#define MOTOR_120_DRIVER_DEV_HALF                (0.5F)      /* 1/2 */

#define MOTOR_120_DRIVER_KHZ_TRANS               (1000U)     /* x1000 */

#define MOTOR_120_DRIVER_GENERAL_IO_PORT_L       (0x3000004) /* general I/O port low */
#define MOTOR_120_DRIVER_GENERAL_IO_PORT_H       (0x3000005) /* general I/O port high */
#define MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_L    (0x3010004) /* I/O port for peripheral functions low */
#define MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_H    (0x3010005) /* I/O port for peripheral functions high */

#ifndef MOTOR_120_DRIVER_ERROR_RETURN

 #define    MOTOR_120_DRIVER_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void rm_motor_120_driver_cyclic(adc_callback_args_t * p_args);

static void rm_motor_120_driver_reset(motor_120_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_120_driver_output_pwm(motor_120_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_120_driver_ctrl_start(motor_120_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_120_driver_ctrl_stop(motor_120_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_120_driver_set_uvw_duty(motor_120_driver_instance_ctrl_t * p_ctrl,
                                             float                              f_duty_u,
                                             float                              f_duty_v,
                                             float                              f_duty_w);
static void rm_motor_120_driver_current_get(motor_120_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_120_driver_pin_cfg(bsp_io_port_pin_t pin, uint32_t cfg);

/* Modulation functions */
static void rm_motor_120_driver_mod_set_max_duty(motor_120_driver_modulation_t * p_mod, float f4_max_duty);
static void rm_motor_120_driver_mod_set_min_duty(motor_120_driver_modulation_t * p_mod, float f4_min_duty);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_120_driver_api_t g_motor_120_driver_on_motor_120_driver =
{
    .open                 = RM_MOTOR_120_DRIVER_Open,
    .close                = RM_MOTOR_120_DRIVER_Close,
    .run                  = RM_MOTOR_120_DRIVER_Run,
    .stop                 = RM_MOTOR_120_DRIVER_Stop,
    .reset                = RM_MOTOR_120_DRIVER_Reset,
    .phaseVoltageSet      = RM_MOTOR_120_DRIVER_PhaseVoltageSet,
    .phasePatternSet      = RM_MOTOR_120_DRIVER_PhasePatternSet,
    .currentGet           = RM_MOTOR_120_DRIVER_CurrentGet,
    .currentOffsetCalc    = RM_MOTOR_120_DRIVER_CurrentOffsetCalc,
    .flagCurrentOffsetGet = RM_MOTOR_120_DRIVER_FlagCurrentOffsetGet,
    .parameterUpdate      = RM_MOTOR_120_DRIVER_ParameterUpdate,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_120_DRIVER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the motor 120 driver module. Implements @ref motor_120_driver_api_t::open.
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_Open
 *
 * @retval FSP_SUCCESS              Motor 120 driver successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_Open (motor_120_driver_ctrl_t * const p_ctrl, motor_120_driver_cfg_t const * const p_cfg)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    motor_120_driver_extended_cfg_t * p_extended_cfg = (motor_120_driver_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->u4_pwm_carrier_freq > 0, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->f_ad_resolution > 0, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->u4_deadtime > 0, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->u4_pwm_timer_freq > 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    three_phase_instance_t const * p_three_phase;
    timer_instance_t const       * p_u_phase_gpt;
    timer_cfg_t const            * p_u_phase_gpt_cfg;

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->u4_carrier_base =
        (uint32_t) ((float) p_extended_cfg->u4_pwm_timer_freq * (float) MOTOR_120_DRIVER_KHZ_TRANS /
                    (float) p_extended_cfg->u4_pwm_carrier_freq * MOTOR_120_DRIVER_DEV_HALF);
    p_instance_ctrl->u4_deadtime_count = p_extended_cfg->u4_deadtime * p_extended_cfg->u4_pwm_timer_freq;

    p_instance_ctrl->st_modulation = p_extended_cfg->mod_param;
    rm_motor_120_driver_mod_set_max_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_max_duty);
    rm_motor_120_driver_mod_set_min_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_min_duty);

    /* Start ADC module */
    if (p_extended_cfg->p_adc_instance != NULL)
    {
        p_extended_cfg->p_adc_instance->p_api->open(p_extended_cfg->p_adc_instance->p_ctrl,
                                                    p_extended_cfg->p_adc_instance->p_cfg);
        p_extended_cfg->p_adc_instance->p_api->scanCfg(p_extended_cfg->p_adc_instance->p_ctrl,
                                                       p_extended_cfg->p_adc_instance->p_channel_cfg);
        p_extended_cfg->p_adc_instance->p_api->calibrate(p_extended_cfg->p_adc_instance->p_ctrl,
                                                         p_extended_cfg->p_adc_instance->p_cfg->p_extend);
        p_extended_cfg->p_adc_instance->p_api->scanStart(p_extended_cfg->p_adc_instance->p_ctrl);
    }

    /* Start GPT three phase module */
    if (p_extended_cfg->p_three_phase_instance != NULL)
    {
        gpt_extended_cfg_t const * p_u_phase_gpt_extend;

        p_three_phase        = p_extended_cfg->p_three_phase_instance;
        p_u_phase_gpt        = p_three_phase->p_cfg->p_timer_instance[0];
        p_u_phase_gpt_cfg    = p_u_phase_gpt->p_cfg;
        p_u_phase_gpt_extend = p_u_phase_gpt_cfg->p_extend;

        if (p_u_phase_gpt_extend->gtioca.stop_level == GPT_PIN_LEVEL_LOW)
        {
            p_instance_ctrl->u4_gtioca_general_low_cfg    = MOTOR_120_DRIVER_GENERAL_IO_PORT_L;
            p_instance_ctrl->u4_gtioca_general_high_cfg   = MOTOR_120_DRIVER_GENERAL_IO_PORT_H;
            p_instance_ctrl->u4_gtioca_periheral_low_cfg  = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_L;
            p_instance_ctrl->u4_gtioca_periheral_high_cfg = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_H;
        }
        else
        {
            p_instance_ctrl->u4_gtioca_general_low_cfg    = MOTOR_120_DRIVER_GENERAL_IO_PORT_H;
            p_instance_ctrl->u4_gtioca_general_high_cfg   = MOTOR_120_DRIVER_GENERAL_IO_PORT_L;
            p_instance_ctrl->u4_gtioca_periheral_low_cfg  = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_H;
            p_instance_ctrl->u4_gtioca_periheral_high_cfg = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_L;
        }

        if (p_u_phase_gpt_extend->gtiocb.stop_level == GPT_PIN_LEVEL_HIGH)
        {
            p_instance_ctrl->u4_gtiocb_general_low_cfg    = MOTOR_120_DRIVER_GENERAL_IO_PORT_L;
            p_instance_ctrl->u4_gtiocb_general_high_cfg   = MOTOR_120_DRIVER_GENERAL_IO_PORT_H;
            p_instance_ctrl->u4_gtiocb_periheral_low_cfg  = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_L;
            p_instance_ctrl->u4_gtiocb_periheral_high_cfg = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_H;
        }
        else
        {
            p_instance_ctrl->u4_gtiocb_general_low_cfg    = MOTOR_120_DRIVER_GENERAL_IO_PORT_H;
            p_instance_ctrl->u4_gtiocb_general_high_cfg   = MOTOR_120_DRIVER_GENERAL_IO_PORT_L;
            p_instance_ctrl->u4_gtiocb_periheral_low_cfg  = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_H;
            p_instance_ctrl->u4_gtiocb_periheral_high_cfg = MOTOR_120_DRIVER_PERIPHERAL_IO_PORT_L;
        }

        p_extended_cfg->p_three_phase_instance->p_api->open(p_extended_cfg->p_three_phase_instance->p_ctrl,
                                                            p_extended_cfg->p_three_phase_instance->p_cfg);

        p_extended_cfg->p_three_phase_instance->p_api->start(p_extended_cfg->p_three_phase_instance->p_ctrl);
    }

    rm_motor_120_driver_reset(p_instance_ctrl);

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_120_DRIVER_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified motor 120 driver module. Implements @ref motor_120_driver_api_t::close.
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_Close
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_Close (motor_120_driver_ctrl_t * const p_ctrl)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_driver_cfg_t          * p_cfg          = (motor_120_driver_cfg_t *) p_instance_ctrl->p_cfg;
    motor_120_driver_extended_cfg_t * p_extended_cfg = (motor_120_driver_extended_cfg_t *) p_cfg->p_extend;

    rm_motor_120_driver_reset(p_instance_ctrl);

    /* Close ADC module */
    if (p_extended_cfg->p_adc_instance != NULL)
    {
        p_extended_cfg->p_adc_instance->p_api->close(p_extended_cfg->p_adc_instance->p_ctrl);
    }

    /* Close GPT three phase module */
    if (p_extended_cfg->p_three_phase_instance != NULL)
    {
        p_extended_cfg->p_three_phase_instance->p_api->close(p_extended_cfg->p_three_phase_instance->p_ctrl);
    }

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Run motor (Start motor rotation). Implements @ref motor_120_driver_api_t::run.
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_Run
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_Run (motor_120_driver_ctrl_t * const p_ctrl)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->u1_active = MOTOR_120_DRIVER_STATUS_ACTIVE;

    rm_motor_120_driver_ctrl_start(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop motor (Stop motor rotation). Implements @ref motor_120_driver_api_t::stop.
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_Stop
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_Stop (motor_120_driver_ctrl_t * const p_ctrl)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->u1_active = MOTOR_120_DRIVER_STATUS_INACTIVE;

    p_instance_ctrl->f_iu_ad  = 0.0F;
    p_instance_ctrl->f_iw_ad  = 0.0F;
    p_instance_ctrl->f_vdc_ad = 0.0F;
    p_instance_ctrl->f_refu   = 0.0F;
    p_instance_ctrl->f_refv   = 0.0F;
    p_instance_ctrl->f_refw   = 0.0F;
    p_instance_ctrl->f_vu_ad  = 0.0F;
    p_instance_ctrl->f_vv_ad  = 0.0F;
    p_instance_ctrl->f_vw_ad  = 0.0F;

    rm_motor_120_driver_ctrl_stop(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of motor 120 driver module. Implements @ref motor_120_driver_api_t::reset.
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_Reset
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_Reset (motor_120_driver_ctrl_t * const p_ctrl)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->f_refu = p_instance_ctrl->st_modulation.f4_neutral_duty;
    p_instance_ctrl->f_refv = p_instance_ctrl->st_modulation.f4_neutral_duty;
    p_instance_ctrl->f_refw = p_instance_ctrl->st_modulation.f4_neutral_duty;

    rm_motor_120_driver_reset(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set phase voltage data to calculate PWM duty. Implements @ref motor_120_driver_api_t::phaseVoltageSet
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_PhaseVoltageSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_PhaseVoltageSet (motor_120_driver_ctrl_t * const p_ctrl,
                                               float const                     u_voltage,
                                               float const                     v_voltage,
                                               float const                     w_voltage)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->f_refu = u_voltage;
    p_instance_ctrl->f_refv = v_voltage;
    p_instance_ctrl->f_refw = w_voltage;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set phase voltage pattern. Implements @ref motor_120_driver_api_t::phasePatternSet
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_PhasePatternSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_PhasePatternSet (motor_120_driver_ctrl_t * const        p_ctrl,
                                               motor_120_driver_phase_pattern_t const pattern)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_driver_extended_cfg_t * p_extended_cfg =
        (motor_120_driver_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    three_phase_instance_t const * p_three_phase      = p_extended_cfg->p_three_phase_instance;
    timer_instance_t const       * p_u_phase_gpt      = p_three_phase->p_cfg->p_timer_instance[0];
    timer_instance_t const       * p_v_phase_gpt      = p_three_phase->p_cfg->p_timer_instance[1];
    timer_instance_t const       * p_w_phase_gpt      = p_three_phase->p_cfg->p_timer_instance[2];
    gpt_instance_ctrl_t          * p_u_phase_gpt_ctrl = p_u_phase_gpt->p_ctrl;
    gpt_instance_ctrl_t          * p_v_phase_gpt_ctrl = p_v_phase_gpt->p_ctrl;
    gpt_instance_ctrl_t          * p_w_phase_gpt_ctrl = p_w_phase_gpt->p_ctrl;
    three_phase_duty_cycle_t       temp_duty;
    uint32_t temp_carrier_set;

    if ((p_three_phase != NULL) &&
        (p_u_phase_gpt != NULL) &&
        (p_v_phase_gpt != NULL) &&
        (p_w_phase_gpt != NULL))
    {
        if (p_extended_cfg->motor_120_type == MOTOR_120_DRIVER_TYPE_HALL)
        {
            p_three_phase->p_api->stop(p_three_phase->p_ctrl);

            R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
            R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
            R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

            rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);
            rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);
            rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);
            rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
            rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);
            rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
        }

        /* set pwm duty */
        temp_duty.duty[0] = (uint32_t) (((p_instance_ctrl->f_refu * (float) p_instance_ctrl->u4_carrier_base) /
                                         p_instance_ctrl->f_vdc_ad) + (float) p_instance_ctrl->u4_deadtime_count);
        temp_duty.duty[1] = temp_duty.duty[0];
        temp_duty.duty[2] = temp_duty.duty[0];

        /* set register */
        /* PWM output arm setting */
        if (((pattern >= MOTOR_120_DRIVER_PHASE_PATTERN_UP_PWM_VN_ON) &&
             (pattern <= MOTOR_120_DRIVER_PHASE_PATTERN_WP_PWM_VN_ON)) ||
            ((pattern >= MOTOR_120_DRIVER_PHASE_PATTERN_U_PWM_VN_ON) &&
             (pattern <= MOTOR_120_DRIVER_PHASE_PATTERN_W_PWM_VN_ON)))
        {
            temp_carrier_set = p_instance_ctrl->u4_carrier_base + p_instance_ctrl->u4_deadtime_count;

            temp_duty.duty[0] = temp_carrier_set - temp_duty.duty[0];
            temp_duty.duty[1] = temp_carrier_set - temp_duty.duty[1];
            temp_duty.duty[2] = temp_carrier_set - temp_duty.duty[2];

            p_three_phase->p_api->dutyCycleSet(p_three_phase->p_ctrl, &temp_duty);
        }
        else if (((pattern >= MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_VN_PWM) &&
                  (pattern <= MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_VN_PWM)) ||
                 ((pattern >= MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_V_PWM) &&
                  (pattern <= MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_V_PWM)))
        {
            p_three_phase->p_api->dutyCycleSet(p_three_phase->p_ctrl, &temp_duty);
        }
        else
        {
            /* Do nothing */
        }

        /* set pattern */
        switch (pattern)
        {
            /* Non-complementary synchronous pattern */
            case MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_WN_PWM:
            {
                /* PWM output enable Wn*/
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_WP_PWM_VN_ON:
            {
                /* PWM output enable Wp */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Wp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_UN_PWM:
            {
                /* PWM output enable Un */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_UP_PWM_WN_ON:
            {
                /* PWM output enable Up */
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_high_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_VN_PWM:
            {
                /* PWM output enable Vn */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_VP_PWM_UN_ON:
            {
                /* PWM output enable Vp */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Vp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_UP_PWM_VN_ON:
            {
                /* PWM output enable Up */
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_UN_PWM:
            {
                /* PWM output enable Un */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Vp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_VP_PWM_WN_ON:
            {
                /* PWM output enable Vp */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_high_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_VN_PWM:
            {
                /* PWM output enable Vn */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Wp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_WP_PWM_UN_ON:
            {
                /* PWM output enable Wp */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_WN_PWM:
            {
                /* PWM output enable Wn */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCB);

                /* Up = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);
                break;
            }

            /* Complementary synchronous pattern */
            case MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_W_PWM:
            {
                /* PWM output enable W */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Wn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_W_PWM_VN_ON:
            {
                /* PWM output enable W */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Wp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Wn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_U_PWM:
            {
                /* PWM output enable U */
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Un = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_U_PWM_WN_ON:
            {
                /* PWM output enable U */
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Un = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_high_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_V_PWM:
            {
                /* PWM output enable V */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Vn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_V_PWM_UN_ON:
            {
                /* PWM output enable V */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Vp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Vn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_U_PWM_VN_ON:
            {
                /* PWM output enable U */
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Un = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_VP_ON_U_PWM:
            {
                /* PWM output enable U */
                R_GPT_OutputEnable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Un = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Vp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_V_PWM_WN_ON:
            {
                /* PWM output enable V */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Vn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Wp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Wn = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_high_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_WP_ON_V_PWM:
            {
                /* PWM output enable V */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Vn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);

                /* Wp = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Wn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_general_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_W_PWM_UN_ON:
            {
                /* PWM output enable W */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Un = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_high_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Wn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);
                break;
            }

            case MOTOR_120_DRIVER_PHASE_PATTERN_UP_ON_W_PWM:
            {
                /* PWM output enable W */
                R_GPT_OutputDisable(p_u_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputDisable(p_v_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
                R_GPT_OutputEnable(p_w_phase_gpt_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

                /* Up = "H" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_instance_ctrl->u4_gtioca_general_high_cfg);

                /* Un = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Vp = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_instance_ctrl->u4_gtioca_general_low_cfg);

                /* Vn = "L" general I/O port */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_instance_ctrl->u4_gtiocb_general_low_cfg);

                /* Wp = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_instance_ctrl->u4_gtioca_periheral_low_cfg);

                /* Wn = "L" I/O port for peripheral functions */
                rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_instance_ctrl->u4_gtiocb_periheral_low_cfg);
                break;
            }

            /* Default case is intentionally combined */
            case MOTOR_120_DRIVER_PHASE_PATTERN_ERROR:
            default:
            {
                /* Do nothing */
                break;
            }
        }

        /* Reset PWM counter */
        R_GPT_CounterSet(p_u_phase_gpt_ctrl, 0U);
        R_GPT_CounterSet(p_v_phase_gpt_ctrl, 0U);
        R_GPT_CounterSet(p_w_phase_gpt_ctrl, 0U);

        if (p_extended_cfg->motor_120_type == MOTOR_120_DRIVER_TYPE_HALL)
        {
            p_three_phase->p_api->start(p_three_phase->p_ctrl);
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get calculated phase current, Vdc & Va_max data. Implements @ref motor_120_driver_api_t::currentGet
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_CurrentGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_CurrentGet (motor_120_driver_ctrl_t * const           p_ctrl,
                                          motor_120_driver_current_status_t * const p_current_status)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_DRIVER_ERROR_RETURN(p_current_status != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_current_status->iu  = p_instance_ctrl->f_iu_ad - p_instance_ctrl->f_offset_iu;
    p_current_status->iw  = p_instance_ctrl->f_iw_ad - p_instance_ctrl->f_offset_iw;
    p_current_status->iv  = -(p_current_status->iu + p_current_status->iw);
    p_current_status->vdc = p_instance_ctrl->f_vdc_ad;

    if (MOTOR_120_DRIVER_STATUS_ACTIVE == p_instance_ctrl->u1_active)
    {
        p_current_status->vu = p_instance_ctrl->f_vu_ad - p_instance_ctrl->f_offset_vu;
        p_current_status->vv = p_instance_ctrl->f_vv_ad - p_instance_ctrl->f_offset_vv;
        p_current_status->vw = p_instance_ctrl->f_vw_ad - p_instance_ctrl->f_offset_vw;
    }
    else
    {
        p_current_status->vu = p_instance_ctrl->f_vu_ad - p_instance_ctrl->f_offset_off_vu;
        p_current_status->vv = p_instance_ctrl->f_vv_ad - p_instance_ctrl->f_offset_off_vv;
        p_current_status->vw = p_instance_ctrl->f_vw_ad - p_instance_ctrl->f_offset_off_vw;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief current offset detection. Implements @ref motor_120_driver_api_t::currentOffsetCalc
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_CurrentOffsetCalc
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_CurrentOffsetCalc (motor_120_driver_ctrl_t * const p_ctrl)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_driver_extended_cfg_t * p_extended_cfg =
        (motor_120_driver_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->u4_offset_calc_count != 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    /* Measure current A/D offset */
    uint32_t u4_temp_offset_count = p_extended_cfg->u4_offset_calc_count;

    if (MOTOR_120_DRIVER_FLAG_OFFSET_CALC_CLEAR == p_instance_ctrl->u1_flag_offset_calc)
    {
        /* Output neautral PWM */
        rm_motor_120_driver_set_uvw_duty(p_instance_ctrl,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty);
        rm_motor_120_driver_output_pwm(p_instance_ctrl);

        if (p_instance_ctrl->u4_offset_calc_times < u4_temp_offset_count)
        {
            p_instance_ctrl->f_sum_iu_ad += p_instance_ctrl->f_iu_ad;
            p_instance_ctrl->f_sum_iw_ad += p_instance_ctrl->f_iw_ad;

            p_instance_ctrl->f_sum_vu_ad += p_instance_ctrl->f_vu_ad;
            p_instance_ctrl->f_sum_vv_ad += p_instance_ctrl->f_vv_ad;
            p_instance_ctrl->f_sum_vw_ad += p_instance_ctrl->f_vw_ad;

            p_instance_ctrl->u4_offset_calc_times++;
        }
        else
        {
            p_instance_ctrl->f_offset_iu = p_instance_ctrl->f_sum_iu_ad / (float) u4_temp_offset_count;
            p_instance_ctrl->f_offset_iw = p_instance_ctrl->f_sum_iw_ad / (float) u4_temp_offset_count;
            p_instance_ctrl->f_sum_iu_ad = 0;
            p_instance_ctrl->f_sum_iw_ad = 0;

            p_instance_ctrl->f_offset_off_vu = p_instance_ctrl->f_sum_vu_ad / (float) u4_temp_offset_count;
            p_instance_ctrl->f_offset_off_vv = p_instance_ctrl->f_sum_vv_ad / (float) u4_temp_offset_count;
            p_instance_ctrl->f_offset_off_vw = p_instance_ctrl->f_sum_vw_ad / (float) u4_temp_offset_count;
            p_instance_ctrl->f_sum_vu_ad     = 0;
            p_instance_ctrl->f_sum_vv_ad     = 0;
            p_instance_ctrl->f_sum_vw_ad     = 0;

            p_instance_ctrl->u4_offset_calc_times = 0;

            if (MOTOR_120_DRIVER_TYPE_SENSORLESS == p_extended_cfg->motor_120_type)
            {
                p_instance_ctrl->u1_flag_offset_calc = MOTOR_120_DRIVER_FLAG_OFFSET_CALC_OFF_FINISH;
                rm_motor_120_driver_ctrl_start(p_instance_ctrl);
            }
            else
            {
                p_instance_ctrl->u1_flag_offset_calc = MOTOR_120_DRIVER_FLAG_OFFSET_CALC_ALL_FINISH;
                rm_motor_120_driver_ctrl_stop(p_instance_ctrl);
            }
        }
    }
    else if (MOTOR_120_DRIVER_FLAG_OFFSET_CALC_OFF_FINISH == p_instance_ctrl->u1_flag_offset_calc)
    {
        if (p_instance_ctrl->u4_offset_calc_times < u4_temp_offset_count)
        {
            p_instance_ctrl->f_sum_vu_ad += p_instance_ctrl->f_vu_ad;
            p_instance_ctrl->f_sum_vv_ad += p_instance_ctrl->f_vv_ad;
            p_instance_ctrl->f_sum_vw_ad += p_instance_ctrl->f_vw_ad;

            p_instance_ctrl->u4_offset_calc_times++;
        }
        else
        {
            p_instance_ctrl->u1_flag_offset_calc = MOTOR_120_DRIVER_FLAG_OFFSET_CALC_ALL_FINISH;

            p_instance_ctrl->f_offset_vu = p_instance_ctrl->f_sum_vu_ad / (float) u4_temp_offset_count;
            p_instance_ctrl->f_offset_vv = p_instance_ctrl->f_sum_vv_ad / (float) u4_temp_offset_count;
            p_instance_ctrl->f_offset_vw = p_instance_ctrl->f_sum_vw_ad / (float) u4_temp_offset_count;

            if (p_extended_cfg->motor_120_type == MOTOR_120_DRIVER_TYPE_SENSORLESS)
            {
                rm_motor_120_driver_ctrl_stop(p_instance_ctrl);
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get the flag of finish current offset detection. Implements @ref motor_120_driver_api_t::flagCurrentOffsetGet
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_FlagCurrentOffsetGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_FlagCurrentOffsetGet (motor_120_driver_ctrl_t * const             p_ctrl,
                                                    motor_120_driver_flag_offset_calc_t * const p_flag_offset)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_DRIVER_ERROR_RETURN(p_flag_offset != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    *p_flag_offset = p_instance_ctrl->u1_flag_offset_calc;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of 120 driver module. Implements @ref motor_120_driver_api_t::parameterUpdate
 *
 * Example:
 * @snippet rm_motor_120_driver_example.c RM_MOTOR_120_DRIVER_ParameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data was updated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DRIVER_ParameterUpdate (motor_120_driver_ctrl_t * const      p_ctrl,
                                               motor_120_driver_cfg_t const * const p_cfg)
{
    motor_120_driver_instance_ctrl_t * p_instance_ctrl = (motor_120_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_120_DRIVER_ERROR_RETURN(MOTOR_120_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_driver_extended_cfg_t * p_extended_cfg = (motor_120_driver_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_120_DRIVER_CFG_PARAM_CHECKING_ENABLE
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->u4_pwm_carrier_freq > 0, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->f_ad_resolution > 0.0F, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->u4_deadtime > 0, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_120_DRIVER_ERROR_RETURN(p_extended_cfg->u4_pwm_timer_freq > 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->u4_carrier_base =
        (uint32_t) ((float) p_extended_cfg->u4_pwm_timer_freq * (float) MOTOR_120_DRIVER_KHZ_TRANS /
                    (float) p_extended_cfg->u4_pwm_carrier_freq * MOTOR_120_DRIVER_DEV_HALF);
    p_instance_ctrl->u4_deadtime_count = p_extended_cfg->u4_deadtime * p_extended_cfg->u4_pwm_timer_freq;

    p_instance_ctrl->st_modulation = p_extended_cfg->mod_param;
    rm_motor_120_driver_mod_set_max_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_max_duty);
    rm_motor_120_driver_mod_set_min_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_min_duty);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_DRIVER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : rm_motor_120_driver_reset
 * Description   : Resets driver variables
 * Arguments     : p_ctrl - The pointer to the motor 120 driver instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_reset (motor_120_driver_instance_ctrl_t * p_ctrl)
{
    rm_motor_120_driver_ctrl_stop(p_ctrl);

    p_ctrl->u1_active = MOTOR_120_DRIVER_STATUS_INACTIVE;

    p_ctrl->f_iu_ad  = 0.0F;
    p_ctrl->f_iw_ad  = 0.0F;
    p_ctrl->f_vdc_ad = 0.0F;
    p_ctrl->f_refu   = 0.0F;
    p_ctrl->f_refv   = 0.0F;
    p_ctrl->f_refw   = 0.0F;
    p_ctrl->f_vu_ad  = 0.0F;
    p_ctrl->f_vv_ad  = 0.0F;
    p_ctrl->f_vw_ad  = 0.0F;

    p_ctrl->u1_flag_offset_calc  = MOTOR_120_DRIVER_FLAG_OFFSET_CALC_CLEAR;
    p_ctrl->u4_offset_calc_times = 0U;
    p_ctrl->f_offset_iu          = 0.0F;
    p_ctrl->f_offset_iw          = 0.0F;
    p_ctrl->f_sum_iu_ad          = 0.0F;
    p_ctrl->f_sum_iw_ad          = 0.0F;
    p_ctrl->f_offset_vu          = 0.0F;
    p_ctrl->f_offset_vv          = 0.0F;
    p_ctrl->f_offset_vw          = 0.0F;
    p_ctrl->f_offset_off_vu      = 0.0F;
    p_ctrl->f_offset_off_vv      = 0.0F;
    p_ctrl->f_offset_off_vw      = 0.0F;
    p_ctrl->f_sum_vu_ad          = 0.0F;
    p_ctrl->f_sum_vv_ad          = 0.0F;
    p_ctrl->f_sum_vw_ad          = 0.0F;
}                                      /* End of function rm_motor_120_driver_reset() */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_driver_output_pwm
 * Description   : PWM output start
 * Arguments     : p_ctrl - The pointer to the motor 120 driver instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_output_pwm (motor_120_driver_instance_ctrl_t * p_ctrl)
{
    motor_120_driver_extended_cfg_t * p_extended_cfg = (motor_120_driver_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    three_phase_instance_t const    * p_three_phase  = p_extended_cfg->p_three_phase_instance;
    timer_instance_t const          * p_u_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[0];
    timer_instance_t const          * p_v_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[1];
    timer_instance_t const          * p_w_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[2];

    if ((p_three_phase != NULL) &&
        (p_u_phase_gpt != NULL) &&
        (p_v_phase_gpt != NULL) &&
        (p_w_phase_gpt != NULL))
    {
        /* PWM output enable */
        R_GPT_OutputEnable(p_u_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputEnable(p_v_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputEnable(p_w_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_ctrl->u4_gtioca_periheral_low_cfg);  /* Up = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_ctrl->u4_gtiocb_periheral_high_cfg); /* Un = "H" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_ctrl->u4_gtioca_periheral_low_cfg);  /* Vp = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_ctrl->u4_gtiocb_periheral_high_cfg); /* Vn = "H" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_ctrl->u4_gtioca_periheral_low_cfg);  /* Wp = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_ctrl->u4_gtiocb_periheral_high_cfg); /* Wn = "H" */
    }
}                                                                                                   /* End of function rm_motor_120_driver_output_pwm */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_driver_ctrl_start
 * Description   : PWM output start for motor control start
 * Arguments     : p_ctrl - The pointer to the motor 120 driver instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_ctrl_start (motor_120_driver_instance_ctrl_t * p_ctrl)
{
    motor_120_driver_extended_cfg_t * p_extended_cfg = (motor_120_driver_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    three_phase_instance_t const    * p_three_phase  = p_extended_cfg->p_three_phase_instance;
    timer_instance_t const          * p_u_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[0];
    timer_instance_t const          * p_v_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[1];
    timer_instance_t const          * p_w_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[2];

    if ((p_three_phase != NULL) &&
        (p_u_phase_gpt != NULL) &&
        (p_v_phase_gpt != NULL) &&
        (p_w_phase_gpt != NULL))
    {
        /* PWM output enable */
        R_GPT_OutputEnable(p_u_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputEnable(p_v_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputEnable(p_w_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_ctrl->u4_gtioca_general_low_cfg);  /* Up = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_ctrl->u4_gtiocb_general_high_cfg); /* Un = "H" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_ctrl->u4_gtioca_general_low_cfg);  /* Vp = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_ctrl->u4_gtiocb_general_high_cfg); /* Vn = "H" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_ctrl->u4_gtioca_general_low_cfg);  /* Wp = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_ctrl->u4_gtiocb_general_high_cfg); /* Wn = "H" */
    }
}                                                                                                 /* End of function rm_motor_120_driver_ctrl_start */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_driver_ctrl_stop
 * Description   : PWM output disable for motor control stop
 * Arguments     : p_ctrl - The pointer to the motor 120 driver instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_ctrl_stop (motor_120_driver_instance_ctrl_t * p_ctrl)
{
    motor_120_driver_extended_cfg_t * p_extended_cfg = (motor_120_driver_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    three_phase_instance_t const    * p_three_phase  = p_extended_cfg->p_three_phase_instance;
    timer_instance_t const          * p_u_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[0];
    timer_instance_t const          * p_v_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[1];
    timer_instance_t const          * p_w_phase_gpt  = p_three_phase->p_cfg->p_timer_instance[2];

    if ((p_three_phase != NULL) &&
        (p_u_phase_gpt != NULL) &&
        (p_v_phase_gpt != NULL) &&
        (p_w_phase_gpt != NULL))
    {
        /* PWM output disable */
        R_GPT_OutputDisable(p_u_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputDisable(p_v_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputDisable(p_w_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_up, p_ctrl->u4_gtioca_general_low_cfg); /* Up = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_un, p_ctrl->u4_gtiocb_general_low_cfg); /* Un = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vp, p_ctrl->u4_gtioca_general_low_cfg); /* Vp = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_vn, p_ctrl->u4_gtiocb_general_low_cfg); /* Vn = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wp, p_ctrl->u4_gtioca_general_low_cfg); /* Wp = "L" */
        rm_motor_120_driver_pin_cfg(p_extended_cfg->port_wn, p_ctrl->u4_gtiocb_general_low_cfg); /* Wn = "L" */
    }
}                                                                                                /* End of function rm_motor_120_driver_ctrl_stop */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_driver_set_uvw_duty
 * Description   : PWM duty setting
 * Arguments     : p_instance - Pointer to motor 120 driver instance
 *                 f_duty_u - The duty cycle of Phase-U (0.0 - 1.0)
 *                 f_duty_v - The duty cycle of Phase-V (0.0 - 1.0)
 *                 f_duty_w - The duty cycle of Phase-W (0.0 - 1.0)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_set_uvw_duty (motor_120_driver_instance_ctrl_t * p_ctrl,
                                              float                              f_duty_u,
                                              float                              f_duty_v,
                                              float                              f_duty_w)
{
    motor_120_driver_extended_cfg_t * p_extended_cfg = (motor_120_driver_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    three_phase_instance_t const    * p_three_phase  = p_extended_cfg->p_three_phase_instance;
    uint32_t                 u4_count_u              = 0U;
    uint32_t                 u4_count_v              = 0U;
    uint32_t                 u4_count_w              = 0U;
    three_phase_duty_cycle_t temp_duty;
    float f_temp_base  = (float) p_ctrl->u4_carrier_base;
    float f_temp_deadt = (float) p_ctrl->u4_deadtime_count;

    u4_count_u = (uint32_t) ((f_temp_base * (1.0F - f_duty_u)) + (f_temp_deadt * MOTOR_120_DRIVER_DEV_HALF));
    u4_count_v = (uint32_t) ((f_temp_base * (1.0F - f_duty_v)) + (f_temp_deadt * MOTOR_120_DRIVER_DEV_HALF));
    u4_count_w = (uint32_t) ((f_temp_base * (1.0F - f_duty_w)) + (f_temp_deadt * MOTOR_120_DRIVER_DEV_HALF));

    temp_duty.duty[0] = u4_count_u;
    temp_duty.duty[1] = u4_count_v;
    temp_duty.duty[2] = u4_count_w;
    if (p_three_phase != NULL)
    {
        p_three_phase->p_api->dutyCycleSet(p_three_phase->p_ctrl, &temp_duty);
    }
}                                      /* End of function rm_motor_120_driver_set_uvw_duty */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_driver_current_get
 * Description   : Get Iu/Iw & Vdc process
 * Arguments     : p_ctrl - The pointer to the motor 120 driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_current_get (motor_120_driver_instance_ctrl_t * p_ctrl)
{
    uint16_t u2_addata[6] = {0U};
    float    f_addata[5]  = {0.0F};
    motor_120_driver_cfg_t const    * p_cfg        = p_ctrl->p_cfg;
    motor_120_driver_extended_cfg_t * p_extend_cfg = (motor_120_driver_extended_cfg_t *) p_cfg->p_extend;

    /* Read A/D converted data */
    if (p_extend_cfg->p_adc_instance != NULL)
    {
        p_extend_cfg->p_adc_instance->p_api->read(p_extend_cfg->p_adc_instance->p_ctrl,
                                                  p_extend_cfg->iu_ad_ch,
                                                  &u2_addata[0]);
        p_extend_cfg->p_adc_instance->p_api->read(p_extend_cfg->p_adc_instance->p_ctrl,
                                                  p_extend_cfg->iw_ad_ch,
                                                  &u2_addata[1]);
        p_extend_cfg->p_adc_instance->p_api->read(p_extend_cfg->p_adc_instance->p_ctrl,
                                                  p_extend_cfg->vdc_ad_ch,
                                                  &u2_addata[2]);
        p_extend_cfg->p_adc_instance->p_api->read(p_extend_cfg->p_adc_instance->p_ctrl,
                                                  p_extend_cfg->vu_ad_ch,
                                                  &u2_addata[3]);
        p_extend_cfg->p_adc_instance->p_api->read(p_extend_cfg->p_adc_instance->p_ctrl,
                                                  p_extend_cfg->vv_ad_ch,
                                                  &u2_addata[4]);
        p_extend_cfg->p_adc_instance->p_api->read(p_extend_cfg->p_adc_instance->p_ctrl,
                                                  p_extend_cfg->vw_ad_ch,
                                                  &u2_addata[5]);
    }

    f_addata[0] = (float) u2_addata[0];
    f_addata[1] = (float) u2_addata[1];
    f_addata[0] = f_addata[0] - p_extend_cfg->f_ad_current_offset;
    f_addata[1] = f_addata[1] - p_extend_cfg->f_ad_current_offset;

    p_ctrl->f_iu_ad = -(f_addata[0]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);
    p_ctrl->f_iw_ad = -(f_addata[1]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);

    p_ctrl->f_vdc_ad = (float) u2_addata[2] * (p_extend_cfg->f_vdc_range / p_extend_cfg->f_ad_resolution) *
                       p_extend_cfg->f_ad_voltage_conversion;

    p_ctrl->f_vu_ad = (float) u2_addata[3] * (p_extend_cfg->f_vdc_range / p_extend_cfg->f_ad_resolution) *
                      p_extend_cfg->f_ad_voltage_conversion;
    p_ctrl->f_vv_ad = (float) u2_addata[4] * (p_extend_cfg->f_vdc_range / p_extend_cfg->f_ad_resolution) *
                      p_extend_cfg->f_ad_voltage_conversion;
    p_ctrl->f_vw_ad = (float) u2_addata[5] * (p_extend_cfg->f_vdc_range / p_extend_cfg->f_ad_resolution) *
                      p_extend_cfg->f_ad_voltage_conversion;
}                                      /* End of function rm_motor_120_driver_current_get */

/***********************************************************************************************************************
 * Function Name: rm_motor_120_driver_mod_set_max_duty
 * Description  : Sets the maximum duty cycle
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *                f4_max_duty -
 *                    Maximum duty cycle to set
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_mod_set_max_duty (motor_120_driver_modulation_t * p_mod, float f4_max_duty)
{
    if ((0 != p_mod) && ((f4_max_duty > 0.0F) && (f4_max_duty <= 1.0F)))
    {
        p_mod->f4_max_duty     = f4_max_duty;
        p_mod->f4_neutral_duty = (p_mod->f4_max_duty + p_mod->f4_min_duty) * MOTOR_120_DRIVER_DEV_HALF;
    }
}                                      /* End of function rm_motor_120_driver_mod_set_max_duty() */

/***********************************************************************************************************************
 * Function Name: rm_motor_120_driver_mod_set_min_duty
 * Description  : Sets the minimum duty cycle
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *                f4_max_duty -
 *                    Minimum duty cycle to set
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_mod_set_min_duty (motor_120_driver_modulation_t * p_mod, float f4_min_duty)
{
    if ((0 != p_mod) && (f4_min_duty > 0.0F))
    {
        p_mod->f4_min_duty     = f4_min_duty;
        p_mod->f4_neutral_duty = (p_mod->f4_max_duty + p_mod->f4_min_duty) * MOTOR_120_DRIVER_DEV_HALF;
    }
}                                      /* End of function rm_motor_120_driver_mod_set_min_duty() */

/***********************************************************************************************************************
 * Function Name: rm_motor_120_driver_pin_cfg
 * Description  : Configure a pin
 * Arguments    : pin -
 *                    The pin
 *                cfg -
 *                    Configuration for the pin (PmnPFS register setting)
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_120_driver_pin_cfg (bsp_io_port_pin_t pin, uint32_t cfg)
{
    R_BSP_PinAccessEnable();
    R_BSP_PinCfg(pin, cfg);
    R_BSP_PinAccessDisable();
}                                      /* End of function rm_motor_120_driver_pin_cfg() */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_driver_cyclic
 * Description   : Cyclic process for driver accsess (Call at A/D conversion finish interrupt)
 * Arguments     : p_args - The pointer to arguments of A/D conversion finish intterupt callback
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_120_driver_cyclic (adc_callback_args_t * p_args)
{
    motor_120_driver_instance_t    * p_instance = (motor_120_driver_instance_t *) p_args->p_context;
    motor_120_driver_callback_args_t temp_args_t;

    /* Get A/D converted data (Phase current & main line voltage) */
    rm_motor_120_driver_current_get(p_instance->p_ctrl);

    /* Invoke the callback function if it is set. */
    if (NULL != p_instance->p_cfg->p_callback)
    {
        temp_args_t.event     = MOTOR_120_DRIVER_EVENT_FORWARD;
        temp_args_t.p_context = p_instance->p_cfg->p_context;
        (p_instance->p_cfg->p_callback)(&temp_args_t);
    }

    if (NULL != p_instance->p_cfg->p_callback)
    {
        temp_args_t.event     = MOTOR_120_DRIVER_EVENT_120_CONTROL;
        temp_args_t.p_context = p_instance->p_cfg->p_context;
        (p_instance->p_cfg->p_callback)(&temp_args_t);
    }

    /* Invoke the callback function if it is set. */
    if (NULL != p_instance->p_cfg->p_callback)
    {
        temp_args_t.event     = MOTOR_120_DRIVER_EVENT_BACKWARD;
        temp_args_t.p_context = p_instance->p_cfg->p_context;
        (p_instance->p_cfg->p_callback)(&temp_args_t);
    }
}
