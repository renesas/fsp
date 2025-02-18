/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <math.h>
#include <stdint.h>
#include "rm_motor_driver.h"
#include "r_gpt.h"

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)
 #include "r_adc_b.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_DRIVER_OPEN                   (0X4D445241L)
#define     MOTOR_DRIVER_SHARED_ADC_OPEN        (('M' << 24U) | ('T' << 16U) | ('S' << 8U) | ('A' << 0U))

#define     MOTOR_DRIVER_FLG_CLR                (0)     /* For flag clear */
#define     MOTOR_DRIVER_FLG_SET                (1)     /* For flag set */

#define     MOTOR_DRIVER_KHZ_TRANS              (1000U) /* x1000 */

#define     MOTOR_DRIVER_DEF_HALF               (0.5F)
#define     MOTOR_DRIVER_MULTIPLE_TWO           (2.0F)

#define     MOTOR_DRIVER_ADC_DATA_MASK          (0x00000FFF)

/* Select SVPWM as default method when MOD_METHOD is undefined */
#define     MOTOR_DRIVER_METHOD_SPWM            (0)         /* Sinusoidal pulse-width-modulation */
#define     MOTOR_DRIVER_METHOD_SVPWM           (1)         /* Space vector pulse-width-modulation */
#define     MOTOR_DRIVER_SATFLAG_BITU           (1 << 0)    /* Saturation flag bit for U phase */
#define     MOTOR_DRIVER_SATFLAG_BITV           (1 << 1)    /* Saturation flag bit for V phase */
#define     MOTOR_DRIVER_SATFLAG_BITW           (1 << 2)    /* Saturation flag bit for W phase */

/*
 * Vamax in this module is calculated by the following equation
 *   SVPWM :  Vdc * (MOD_VDC_TO_VAMAX_MULT) * (Max duty - Min duty) * (MOD_SVPWM_MULT)
 *   SPWM  :  Vdc * (MOD_VDC_TO_VAMAX_MULT) * (Max duty - Min duty)
 */
#define MOTOR_DRIVER_VDC_TO_VAMAX_MULT          (0.6124F)   /* The basic coefficient used to convert Vdc to Vamax */
#define MOTOR_DRIVER_SVPWM_MULT                 (1.155F)    /* The usable voltage is multiplied by sqrt(4/3) when using SVPWM */

#define MOTOR_DRIVER_IO_PORT_CFG_LOW            (0x3000004) /* Set I/O port with low output */
#define MOTOR_DRIVER_IO_PORT_CFG_HIGH           (0x3000005) /* Set I/O port with high output*/
#define MOTOR_DRIVER_IO_PORT_PERIPHERAL_MASK    (0x0010000) /* Mask for pin to operate as a peripheral pin */
#define MOTOR_DRIVER_IO_PORT_GPIO_MASK          (0xFFEFFFF) /* Mask for pin to operate as a GPIO pin */

#ifndef MOTOR_DRIVER_ERROR_RETURN
 #define    MOTOR_DRIVER_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void rm_motor_driver_cyclic(adc_callback_args_t * p_args);
void rm_motor_driver_1shunt_cyclic(timer_callback_args_t * p_args);
void rm_motor_driver_shared_cyclic(adc_callback_args_t * p_args);

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)
static void rm_motor_driver_adc_b_open(motor_driver_instance_ctrl_t   * p_instance_ctrl,
                                       motor_driver_cfg_t const * const p_cfg);

static void rm_motor_driver_adc_b_close(motor_driver_instance_ctrl_t * p_instance_ctrl);

#else
static void rm_motor_driver_adc_open(motor_driver_instance_ctrl_t   * p_instance_ctrl,
                                     motor_driver_cfg_t const * const p_cfg);

static void rm_motor_driver_adc_close(motor_driver_instance_ctrl_t * p_instance_ctrl);

#endif

static void rm_motor_driver_reset(motor_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_driver_set_uvw_duty(motor_driver_instance_ctrl_t * p_ctrl,
                                         float                          f_duty_u,
                                         float                          f_duty_v,
                                         float                          f_duty_w);
static void rm_motor_driver_current_get(motor_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_driver_1shunt_current_get(motor_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_driver_modulation(motor_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_driver_1shunt_modulation(motor_driver_instance_ctrl_t * p_ctrl);

static void rm_motor_driver_pin_cfg(bsp_io_port_pin_t pin, uint32_t cfg);
static void rm_motor_driver_output_enable(motor_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_driver_output_disable(motor_driver_instance_ctrl_t * p_ctrl);

/* Modulation functions */
static void rm_motor_driver_mod_run(motor_driver_instance_ctrl_t * p_ctrl,
                                    const float                  * p_f4_v_in,
                                    float                        * p_f4_duty_out);
static void  rm_motor_driver_mod_set_max_duty(motor_driver_modulation_t * p_mod, float f4_max_duty);
static void  rm_motor_driver_mod_set_min_duty(motor_driver_modulation_t * p_mod, float f4_min_duty);
static float rm_motor_driver_mod_get_vamax(motor_driver_modulation_t * p_mod, uint8_t u1_method);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_driver_api_t g_motor_driver_on_motor_driver =
{
    .open                 = RM_MOTOR_DRIVER_Open,
    .close                = RM_MOTOR_DRIVER_Close,
    .reset                = RM_MOTOR_DRIVER_Reset,
    .phaseVoltageSet      = RM_MOTOR_DRIVER_PhaseVoltageSet,
    .currentGet           = RM_MOTOR_DRIVER_CurrentGet,
    .flagCurrentOffsetGet = RM_MOTOR_DRIVER_FlagCurrentOffsetGet,
    .currentOffsetRestart = RM_MOTOR_DRIVER_CurrentOffsetRestart,
    .parameterUpdate      = RM_MOTOR_DRIVER_ParameterUpdate,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_DRIVER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the Motor Driver module. Implements @ref motor_driver_api_t::open.
 *
 * @retval FSP_SUCCESS              Motor Driver successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_Open (motor_driver_ctrl_t * const p_ctrl, motor_driver_cfg_t const * const p_cfg)
{
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
#endif

    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg);
#endif

    FSP_ERROR_RETURN(MOTOR_DRIVER_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->u2_carrier_base =
        (uint16_t) (p_extended_cfg->u2_pwm_timer_freq * MOTOR_DRIVER_KHZ_TRANS /
                    p_extended_cfg->pwm_carrier_freq / (uint16_t) MOTOR_DRIVER_MULTIPLE_TWO);
    p_instance_ctrl->u2_deadtime_count = p_extended_cfg->u2_deadtime;

    rm_motor_driver_reset(p_instance_ctrl);

    p_instance_ctrl->st_modulation = p_extended_cfg->mod_param;
    rm_motor_driver_mod_set_max_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_max_duty);
    rm_motor_driver_mod_set_min_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_min_duty);

    /* Start GPT three phase module */
    if (p_cfg->p_three_phase_instance != NULL)
    {
        /* For Port setting */
        three_phase_instance_t const * p_three_phase;
        timer_instance_t const       * p_u_phase_gpt;
        timer_cfg_t const            * p_u_phase_gpt_cfg;
        gpt_extended_cfg_t const     * p_u_phase_gpt_extend;

        p_three_phase        = p_cfg->p_three_phase_instance;
        p_u_phase_gpt        = p_three_phase->p_cfg->p_timer_instance[p_extended_cfg->trigger_phase];
        p_u_phase_gpt_cfg    = p_u_phase_gpt->p_cfg;
        p_u_phase_gpt_extend = p_u_phase_gpt_cfg->p_extend;

        if (p_u_phase_gpt_extend->gtioca.stop_level == GPT_PIN_LEVEL_LOW)
        {
            p_instance_ctrl->u4_gtioca_low_cfg = MOTOR_DRIVER_IO_PORT_CFG_LOW;
        }
        else
        {
            p_instance_ctrl->u4_gtioca_low_cfg = MOTOR_DRIVER_IO_PORT_CFG_HIGH;
        }

        if (p_u_phase_gpt_extend->gtiocb.stop_level == GPT_PIN_LEVEL_HIGH)
        {
            p_instance_ctrl->u4_gtiocb_low_cfg = MOTOR_DRIVER_IO_PORT_CFG_LOW;
        }
        else
        {
            p_instance_ctrl->u4_gtiocb_low_cfg = MOTOR_DRIVER_IO_PORT_CFG_HIGH;
        }

        p_cfg->p_three_phase_instance->p_api->open(p_cfg->p_three_phase_instance->p_ctrl,
                                                   p_cfg->p_three_phase_instance->p_cfg);

        if (MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT == p_cfg->shunt)
        {
            p_u_phase_gpt->p_api->callbackSet(p_u_phase_gpt->p_ctrl, rm_motor_driver_1shunt_cyclic, p_instance_ctrl,
                                              &(p_instance_ctrl->timer_callback_args));
        }
        else
        {
            rm_motor_driver_set_uvw_duty(p_instance_ctrl,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty);
        }

        if (p_extended_cfg->port_up != 0)
        {
            rm_motor_driver_output_disable(p_instance_ctrl);
        }

        p_cfg->p_three_phase_instance->p_api->start(p_cfg->p_three_phase_instance->p_ctrl);
    }

    /* Start ADC module */
#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)
    rm_motor_driver_adc_b_open(p_instance_ctrl, p_cfg);
#else                                  /* ADC_B_SUPPORT == 0 (for adc) */
    rm_motor_driver_adc_open(p_instance_ctrl, p_cfg);
#endif                                 /* ADC_B_SUPPORT == 0 (for adc) */

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_DRIVER_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified Motor Driver Module. Implements @ref motor_driver_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_Close (motor_driver_ctrl_t * const p_ctrl)
{
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_DRIVER_ERROR_RETURN(MOTOR_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_driver_cfg_t          * p_cfg          = (motor_driver_cfg_t *) p_instance_ctrl->p_cfg;
    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

    if (p_extended_cfg->port_up != 0)
    {
        rm_motor_driver_output_disable(p_instance_ctrl);
    }

    rm_motor_driver_reset(p_instance_ctrl);

    /* Close ADC module */
#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)
    rm_motor_driver_adc_b_close(p_instance_ctrl);
#else                                  /* ADC_B_SUPPORTED == 0 (for adc) */
    rm_motor_driver_adc_close(p_instance_ctrl);
#endif                                 /* ADC_B_SUPPORTED == 0 (for adc) */

    /* Close GPT three phase module */
    if (p_cfg->p_three_phase_instance != NULL)
    {
        p_cfg->p_three_phase_instance->p_api->close(p_cfg->p_three_phase_instance->p_ctrl);
    }

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of Motor Driver Module. Implements @ref motor_driver_api_t::reset.
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_Reset (motor_driver_ctrl_t * const p_ctrl)
{
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_DRIVER_ERROR_RETURN(MOTOR_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_driver_cfg_t          * p_cfg          = (motor_driver_cfg_t *) p_instance_ctrl->p_cfg;
    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

    p_instance_ctrl->f_refu = p_instance_ctrl->st_modulation.f4_neutral_duty;
    p_instance_ctrl->f_refv = p_instance_ctrl->st_modulation.f4_neutral_duty;
    p_instance_ctrl->f_refw = p_instance_ctrl->st_modulation.f4_neutral_duty;

    rm_motor_driver_set_uvw_duty(p_instance_ctrl,
                                 p_instance_ctrl->st_modulation.f4_neutral_duty,
                                 p_instance_ctrl->st_modulation.f4_neutral_duty,
                                 p_instance_ctrl->st_modulation.f4_neutral_duty);

    if (p_extended_cfg->port_up != 0)
    {
        rm_motor_driver_output_disable(p_instance_ctrl);
    }

    rm_motor_driver_reset(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set Phase Voltage Data to calculate PWM duty. Implements @ref motor_driver_api_t::phaseVoltageSet
 *
 * @retval FSP_SUCCESS              Successfully data is set.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_PhaseVoltageSet (motor_driver_ctrl_t * const p_ctrl,
                                           float const                 u_voltage,
                                           float const                 v_voltage,
                                           float const                 w_voltage)
{
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_DRIVER_ERROR_RETURN(MOTOR_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->f_refu = u_voltage;
    p_instance_ctrl->f_refv = v_voltage;
    p_instance_ctrl->f_refw = w_voltage;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get calculated phase Current, Vdc & Va_max data. Implements @ref motor_driver_api_t::currentGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_CurrentGet (motor_driver_ctrl_t * const        p_ctrl,
                                      motor_driver_current_get_t * const p_current_get)
{
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_DRIVER_ERROR_RETURN(MOTOR_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_DRIVER_ERROR_RETURN(p_current_get != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_driver_extended_cfg_t * p_extended_cfg =
        (motor_driver_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT != p_instance_ctrl->p_cfg->shunt)
    {
        p_current_get->iu = p_instance_ctrl->f_iu_ad - p_instance_ctrl->f_offset_iu;
        p_current_get->iv = p_instance_ctrl->f_iv_ad - p_instance_ctrl->f_offset_iv;
        p_current_get->iw = p_instance_ctrl->f_iw_ad - p_instance_ctrl->f_offset_iw;
    }
    else
    {
        p_current_get->iu = p_instance_ctrl->f_iu_ad;
        p_current_get->iv = p_instance_ctrl->f_iv_ad;
        p_current_get->iw = p_instance_ctrl->f_iw_ad;
    }

    p_current_get->vdc    = p_instance_ctrl->f_vdc_ad;
    p_current_get->va_max = rm_motor_driver_mod_get_vamax(&(p_instance_ctrl->st_modulation),
                                                          (uint8_t) p_extended_cfg->modulation_method);

    /* For induction sensor */
    p_current_get->sin_ad = p_instance_ctrl->f_sin_ad;
    p_current_get->cos_ad = p_instance_ctrl->f_cos_ad;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get the flag of finish current offset detection. Implements @ref motor_driver_api_t::flagCurrentOffsetGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_FlagCurrentOffsetGet (motor_driver_ctrl_t * const p_ctrl, uint8_t * const p_flag_offset)
{
    uint16_t u2_temp_offset_count = 0U;
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_DRIVER_ERROR_RETURN(MOTOR_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_DRIVER_ERROR_RETURN(p_flag_offset != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_driver_extended_cfg_t * p_extended_cfg =
        (motor_driver_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Enable PWM output */
    if (p_extended_cfg->port_up != 0)
    {
        rm_motor_driver_output_enable(p_instance_ctrl);
    }

    /* Measure current A/D offset */
    if (MOTOR_DRIVER_FLG_CLR == p_instance_ctrl->u1_flag_offset_calc)
    {
        /* 2 or 3 shunt */
        if (MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT != p_instance_ctrl->p_cfg->shunt)
        {
            /* Output neutral PWM */
            rm_motor_driver_set_uvw_duty(p_instance_ctrl,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty,
                                         p_instance_ctrl->st_modulation.f4_neutral_duty);

            u2_temp_offset_count = p_extended_cfg->u2_offset_calc_count;

            if (p_instance_ctrl->u2_offset_calc_times < u2_temp_offset_count)
            {
                p_instance_ctrl->f_sum_iu_ad += p_instance_ctrl->f_iu_ad;
                p_instance_ctrl->f_sum_iv_ad += p_instance_ctrl->f_iv_ad;
                p_instance_ctrl->f_sum_iw_ad += p_instance_ctrl->f_iw_ad;
                p_instance_ctrl->u2_offset_calc_times++;
            }
            else
            {
                p_instance_ctrl->f_offset_iu         = p_instance_ctrl->f_sum_iu_ad / u2_temp_offset_count;
                p_instance_ctrl->f_offset_iv         = p_instance_ctrl->f_sum_iv_ad / u2_temp_offset_count;
                p_instance_ctrl->f_offset_iw         = p_instance_ctrl->f_sum_iw_ad / u2_temp_offset_count;
                p_instance_ctrl->u1_flag_offset_calc = MOTOR_DRIVER_FLG_SET;
            }
        }
        /* 1 shunt */
        else
        {
            u2_temp_offset_count = p_extended_cfg->u2_offset_calc_count;
            if (p_instance_ctrl->u2_offset_calc_times < u2_temp_offset_count)
            {
                p_instance_ctrl->f_sum_iu_ad += p_instance_ctrl->f_iu_ad;
                p_instance_ctrl->f_sum_iw_ad += p_instance_ctrl->f_iw_ad;
                p_instance_ctrl->u2_offset_calc_times++;
            }
            else
            {
                p_instance_ctrl->f_offset_iu         = p_instance_ctrl->f_sum_iu_ad / u2_temp_offset_count;
                p_instance_ctrl->f_offset_iw         = p_instance_ctrl->f_sum_iw_ad / u2_temp_offset_count;
                p_instance_ctrl->u1_flag_offset_calc = MOTOR_DRIVER_FLG_SET;
            }
        }
    }

    *p_flag_offset = p_instance_ctrl->u1_flag_offset_calc;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Restart the current offset detection. Implements @ref motor_driver_api_t::currentOffsetRestart
 *
 * @retval FSP_SUCCESS              Successfully restarted.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_CurrentOffsetRestart (motor_driver_ctrl_t * const p_ctrl)
{
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_DRIVER_ERROR_RETURN(MOTOR_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->u1_flag_offset_calc  = MOTOR_DRIVER_FLG_CLR;
    p_instance_ctrl->u2_offset_calc_times = 0U;
    p_instance_ctrl->f_sum_iu_ad          = 0.0F;
    p_instance_ctrl->f_sum_iv_ad          = 0.0F;
    p_instance_ctrl->f_sum_iw_ad          = 0.0F;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of Driver Module. Implements @ref motor_driver_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data was updated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_ParameterUpdate (motor_driver_ctrl_t * const p_ctrl, motor_driver_cfg_t const * const p_cfg)
{
    motor_driver_instance_ctrl_t * p_instance_ctrl = (motor_driver_instance_ctrl_t *) p_ctrl;

#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    MOTOR_DRIVER_ERROR_RETURN(MOTOR_DRIVER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_cfg);
#endif

    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->u2_carrier_base =
        (uint16_t) (p_extended_cfg->u2_pwm_timer_freq * MOTOR_DRIVER_KHZ_TRANS /
                    p_extended_cfg->pwm_carrier_freq / (uint16_t) MOTOR_DRIVER_MULTIPLE_TWO);
    p_instance_ctrl->u2_deadtime_count = p_extended_cfg->u2_deadtime;

    p_instance_ctrl->st_modulation = p_extended_cfg->mod_param;
    rm_motor_driver_mod_set_max_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_max_duty);
    rm_motor_driver_mod_set_min_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_min_duty);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_DRIVER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_reset
 * Description   : Resets driver variables
 * Arguments     : p_ctrl - The pointer to the motor driver instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_reset (motor_driver_instance_ctrl_t * p_ctrl)
{
    p_ctrl->f_iu_ad  = 0.0F;
    p_ctrl->f_iv_ad  = 0.0F;
    p_ctrl->f_iw_ad  = 0.0F;
    p_ctrl->f_vdc_ad = 0.0F;
    p_ctrl->f_refu   = 0.0F;
    p_ctrl->f_refv   = 0.0F;
    p_ctrl->f_refw   = 0.0F;

    p_ctrl->u1_flag_offset_calc  = MOTOR_DRIVER_FLG_CLR;
    p_ctrl->u2_offset_calc_times = 0U;
    p_ctrl->f_offset_iu          = 0.0F;
    p_ctrl->f_offset_iv          = 0.0F;
    p_ctrl->f_offset_iw          = 0.0F;
    p_ctrl->f_sum_iu_ad          = 0.0F;
    p_ctrl->f_sum_iv_ad          = 0.0F;
    p_ctrl->f_sum_iw_ad          = 0.0F;

    p_ctrl->st_modulation.u1_sat_flag = 0U;

    p_ctrl->u1_flag_port_enable = 1U;
}                                      /* End of function rm_motor_driver_reset */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_set_uvw_duty
 * Description   : PWM duty setting
 * Arguments     : p_instance - Pointer to Motor Driver instance
 *                 f_duty_u - The duty cycle of Phase-U (0.0 - 1.0)
 *                 f_duty_v - The duty cycle of Phase-V (0.0 - 1.0)
 *                 f_duty_w - The duty cycle of Phase-W (0.0 - 1.0)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_set_uvw_duty (motor_driver_instance_ctrl_t * p_ctrl,
                                          float                          f_duty_u,
                                          float                          f_duty_v,
                                          float                          f_duty_w)
{
    three_phase_instance_t const * p_three_phase = p_ctrl->p_cfg->p_three_phase_instance;
    uint16_t                 u2_count_u          = 0U;
    uint16_t                 u2_count_v          = 0U;
    uint16_t                 u2_count_w          = 0U;
    three_phase_duty_cycle_t temp_duty;
    uint16_t                 u2_temp_base  = p_ctrl->u2_carrier_base;
    uint16_t                 u2_temp_deadt = p_ctrl->u2_deadtime_count;

    u2_count_u = (uint16_t) ((u2_temp_base * (1.0F - f_duty_u)) + (u2_temp_deadt * MOTOR_DRIVER_DEF_HALF));
    u2_count_v = (uint16_t) ((u2_temp_base * (1.0F - f_duty_v)) + (u2_temp_deadt * MOTOR_DRIVER_DEF_HALF));
    u2_count_w = (uint16_t) ((u2_temp_base * (1.0F - f_duty_w)) + (u2_temp_deadt * MOTOR_DRIVER_DEF_HALF));

    temp_duty.duty[0] = (uint32_t) u2_count_u;
    temp_duty.duty[1] = (uint32_t) u2_count_v;
    temp_duty.duty[2] = (uint32_t) u2_count_w;

    if (MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT == p_ctrl->p_cfg->shunt)
    {
        temp_duty.duty_buffer[0] = (uint32_t) u2_count_u;
        temp_duty.duty_buffer[1] = (uint32_t) u2_count_v;
        temp_duty.duty_buffer[2] = (uint32_t) u2_count_w;
    }

    if (p_three_phase != NULL)
    {
        p_three_phase->p_api->dutyCycleSet(p_three_phase->p_ctrl, &temp_duty);
    }
}                                      /* End of function rm_motor_driver_set_uvw_duty */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_current_get
 * Description   : Get Iu/Iw & Vdc process
 * Arguments     : p_ctrl - The pointer to the motor driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_current_get (motor_driver_instance_ctrl_t * p_ctrl)
{
    uint16_t u2_addata[6]                      = {0U};
    float    f_addata[3]                       = {0.0F};
    motor_driver_cfg_t const    * p_cfg        = p_ctrl->p_cfg;
    motor_driver_extended_cfg_t * p_extend_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

    adc_instance_t const * p_adc_instance;

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)
 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    p_adc_instance = p_cfg->p_adc_instance;
 #else
    p_adc_instance = p_extend_cfg->p_shared_cfg->p_adc_instance_first;
 #endif

    /* Read A/D converted data */
    if (p_adc_instance != NULL)
    {
        p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iu_ad_ch, &u2_addata[0]);
        if (MOTOR_DRIVER_SHUNT_TYPE_3_SHUNT == p_cfg->shunt)
        {
            p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iv_ad_ch, &u2_addata[1]);
        }
        else
        {
            u2_addata[1] = 0U;
        }

        p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iw_ad_ch, &u2_addata[2]);
        p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[3]);

        /* For induction sensor */
        p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->sin_ad_ch, &u2_addata[4]);
        p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->cos_ad_ch, &u2_addata[5]);
    }

#else                                           /* MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 0 */
 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    p_adc_instance = p_cfg->p_adc_instance;
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iu_ad_ch, &u2_addata[0]);
    if (MOTOR_DRIVER_SHUNT_TYPE_3_SHUNT == p_cfg->shunt)
    {
        p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iv_ad_ch, &u2_addata[1]);
    }
    else
    {
        u2_addata[1] = 0U;
    }

    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iw_ad_ch, &u2_addata[2]);
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[3]);

    /* For induction sensor */
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->sin_ad_ch, &u2_addata[4]);
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->cos_ad_ch, &u2_addata[5]);
 #else                                 /* SUPPORT_SHARED_ADC == 1 */
    /* Read A/D converted data */
    adc_instance_t const * pp_adc_instance[2] =
    {
        p_extend_cfg->p_shared_cfg->p_adc_instance_first,
        p_extend_cfg->p_shared_cfg->p_adc_instance_second,
    };

    p_adc_instance = pp_adc_instance[p_extend_cfg->iu_ad_unit];
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iu_ad_ch, &u2_addata[0]);

    if (MOTOR_DRIVER_SHUNT_TYPE_3_SHUNT == p_cfg->shunt)
    {
        p_adc_instance = pp_adc_instance[p_extend_cfg->iv_ad_unit];
        p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iv_ad_ch, &u2_addata[1]);
    }
    else
    {
        u2_addata[1] = 0U;
    }

    p_adc_instance = pp_adc_instance[p_extend_cfg->iw_ad_unit];
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->iw_ad_ch, &u2_addata[2]);

    p_adc_instance = pp_adc_instance[p_extend_cfg->vdc_ad_unit];
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[3]);

    /* For induction sensor */
    p_adc_instance = pp_adc_instance[p_extend_cfg->sin_ad_unit];
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->sin_ad_ch, &u2_addata[4]);
    p_adc_instance = pp_adc_instance[p_extend_cfg->cos_ad_unit];
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->cos_ad_ch, &u2_addata[5]);
 #endif                                /* SUPPORT_SHARED_ADC == 1 */
#endif                                 /* ADC_B_SUPPORTED == 0 */

    f_addata[0] = (float) u2_addata[0];
    f_addata[1] = (float) u2_addata[1];
    f_addata[2] = (float) u2_addata[2];
    f_addata[0] = f_addata[0] - p_extend_cfg->f_ad_current_offset;
    f_addata[1] = f_addata[1] - p_extend_cfg->f_ad_current_offset;
    f_addata[2] = f_addata[2] - p_extend_cfg->f_ad_current_offset;

    p_ctrl->f_iu_ad = -(f_addata[0]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);
    p_ctrl->f_iv_ad = -(f_addata[1]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);
    p_ctrl->f_iw_ad = -(f_addata[2]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);

    p_ctrl->f_vdc_ad = (float) u2_addata[3] * (p_extend_cfg->f_vdc_range / p_extend_cfg->f_ad_resolution) *
                       p_extend_cfg->f_ad_voltage_conversion;

    /* For induction sensor */
    p_ctrl->f_sin_ad = (float) u2_addata[4];
    p_ctrl->f_cos_ad = (float) u2_addata[5];
}                                      /* End of function rm_motor_driver_current_get */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_1shunt_current_get
 * Description   : Get Iu/Iw & Vdc process for 1shunt
 * Arguments     : p_ctrl - The pointer to the motor driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_1shunt_current_get (motor_driver_instance_ctrl_t * p_ctrl)
{
    uint16_t u2_addata[3]                      = {0U};
    float    f_Iac_ad[2]                       = {0.0F};
    float    f_addata[3]                       = {0.0F};
    float    f_Iac_ad2                         = 0.0F;
    uint16_t u2_Iac_raw0                       = 0U;
    uint16_t u2_Iac_raw1                       = 0U;
    motor_driver_cfg_t const    * p_cfg        = p_ctrl->p_cfg;
    motor_driver_extended_cfg_t * p_extend_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

    adc_instance_t const * p_adc_instance;

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)

    /* g_adc_b module */
 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    p_adc_instance = p_cfg->p_adc_instance;
 #else
    p_adc_instance = p_extend_cfg->p_shared_cfg->p_adc_instance_first;
 #endif

    adc_b_fifo_read_t temp_fifo;

    /* Using ADC_B module */
    /* Get Vdc */
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[0]);

    /* Get induction sensor output */
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->sin_ad_ch, &u2_addata[1]);
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, p_cfg->cos_ad_ch, &u2_addata[2]);

    /* Get FIFO data */
    R_ADC_B_FifoRead(p_adc_instance->p_ctrl, ADC_GROUP_MASK_0, &temp_fifo);
    temp_fifo.fifo_data[0].data &= MOTOR_DRIVER_ADC_DATA_MASK;
    u2_Iac_raw0                  = (uint16_t) temp_fifo.fifo_data[0].data;
    temp_fifo.fifo_data[1].data &= MOTOR_DRIVER_ADC_DATA_MASK;
    u2_Iac_raw1                  = (uint16_t) temp_fifo.fifo_data[1].data;
#else                                  /* ADC_B_SUPPORTED == 0 */
    /* g_adc module */
    adc_instance_t const * p_adc2_instance;
    adc_status_t           temp_adc_status;

 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    p_adc_instance  = p_cfg->p_adc_instance;
    p_adc2_instance = p_cfg->p_adc2_instance;
 #else
    p_adc_instance  = p_extend_cfg->p_shared_cfg->p_adc_instance_first;
    p_adc2_instance = p_extend_cfg->p_shared_cfg->p_adc_instance_second;
 #endif

    /* Get double buffer data */
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, ADC_CHANNEL_DUPLEX_A, &u2_Iac_raw0);
    p_adc_instance->p_api->read(p_adc_instance->p_ctrl, ADC_CHANNEL_DUPLEX_B, &u2_Iac_raw1);

    /* Read A/D converted data */
    if (p_adc2_instance != NULL)
    {
        /* When an AD unit is used to read 1shunt current and vdc,
         * once close the unit and reopen with other configuration. */
        if (p_extend_cfg->iu_ad_unit == p_extend_cfg->vdc_ad_unit)
        {
            /* Close first ADC instance */
            p_adc_instance->p_api->close(p_adc_instance->p_ctrl);

            /* Open second ADC instance */
            p_adc2_instance->p_api->open(p_adc2_instance->p_ctrl, p_adc2_instance->p_cfg);
            p_adc2_instance->p_api->scanCfg(p_adc2_instance->p_ctrl, p_adc2_instance->p_channel_cfg);
        }

        p_adc2_instance->p_api->scanStart(p_adc2_instance->p_ctrl);

        p_adc2_instance->p_api->scanStatusGet(p_adc2_instance->p_ctrl, &temp_adc_status);
        while (ADC_STATE_SCAN_IN_PROGRESS == temp_adc_status.state)
        {
            /* wait A/D conversion finish */
            p_adc2_instance->p_api->scanStatusGet(p_adc2_instance->p_ctrl, &temp_adc_status);
        }

        p_adc2_instance->p_api->read(p_adc2_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[0]);

        /* When an AD unit is used to read 1shunt current and vdc,
         * once close the unit and reopen with other configuration again. */
        if (p_extend_cfg->iu_ad_unit == p_extend_cfg->vdc_ad_unit)
        {
            /* Close second ADC instance */
            p_adc2_instance->p_api->close(p_adc2_instance->p_ctrl);

            /* Open & Start first ADC instance again */
            p_adc_instance->p_api->open(p_adc_instance->p_ctrl, p_adc_instance->p_cfg);
            p_adc_instance->p_api->scanCfg(p_adc_instance->p_ctrl, p_adc_instance->p_channel_cfg);
            p_adc_instance->p_api->calibrate(p_adc_instance->p_ctrl, p_adc_instance->p_cfg->p_extend);
            p_adc_instance->p_api->scanStart(p_adc_instance->p_ctrl);
        }
    }
#endif                                 /* ADC_B_SUPPORTED == 0 */

    /* Get main line voltage */
    p_ctrl->f_vdc_ad = (float) u2_addata[0] * (p_extend_cfg->f_vdc_range / p_extend_cfg->f_ad_resolution) *
                       p_extend_cfg->f_ad_voltage_conversion;

    /* Get induction sensor output sin/cos */
    p_ctrl->f_sin_ad = (float) u2_addata[1];
    p_ctrl->f_cos_ad = (float) u2_addata[2];

    /* Translate double buffer A/D data to 3 phase currents */
    f_Iac_ad[0] = (float) (u2_Iac_raw0 - (uint16_t) p_ctrl->f_offset_iu);
    f_Iac_ad[1] = (float) (u2_Iac_raw1 - (uint16_t) p_ctrl->f_offset_iw) - p_extend_cfg->f_ad_current_adjust;

    f_Iac_ad[0] = (f_Iac_ad[0]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);
    f_Iac_ad[1] = -(f_Iac_ad[1]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);

    f_Iac_ad2 = -(f_Iac_ad[0] + f_Iac_ad[1]);

    switch (p_ctrl->min_phase)
    {
        case MOTOR_DRIVER_PHASE_U_PHASE:
        {
            f_addata[0] = f_Iac_ad[0];
            if (MOTOR_DRIVER_PHASE_V_PHASE == p_ctrl->mid_phase)
            {
                f_addata[2] = f_Iac_ad[1];
                f_addata[1] = f_Iac_ad2;
            }
            else
            {
                f_addata[1] = f_Iac_ad[1];
                f_addata[2] = f_Iac_ad2;
            }

            break;
        }

        case MOTOR_DRIVER_PHASE_V_PHASE:
        {
            f_addata[1] = f_Iac_ad[0];
            if (MOTOR_DRIVER_PHASE_W_PHASE == p_ctrl->mid_phase)
            {
                f_addata[0] = f_Iac_ad[1];
                f_addata[2] = f_Iac_ad2;
            }
            else
            {
                f_addata[2] = f_Iac_ad[1];
                f_addata[0] = f_Iac_ad2;
            }

            break;
        }

        case MOTOR_DRIVER_PHASE_W_PHASE:
        {
            f_addata[2] = f_Iac_ad[0];
            if (MOTOR_DRIVER_PHASE_U_PHASE == p_ctrl->mid_phase)
            {
                f_addata[1] = f_Iac_ad[1];
                f_addata[0] = f_Iac_ad2;
            }
            else
            {
                f_addata[0] = f_Iac_ad[1];
                f_addata[1] = f_Iac_ad2;
            }

            break;
        }

        default:
        {
            break;
        }
    }

    if (MOTOR_DRIVER_FLG_SET == p_ctrl->u1_flag_offset_calc)
    {
        p_ctrl->f_iu_ad = f_addata[0];
        p_ctrl->f_iv_ad = f_addata[1];
        p_ctrl->f_iw_ad = f_addata[2];
    }
    else
    /* Offset measurement with ADC raw data */
    {
        p_ctrl->f_iu_ad = (float) u2_Iac_raw0;
        p_ctrl->f_iw_ad = (float) u2_Iac_raw1;
    }
}                                      /* End of function rm_motor_driver_1shunt_current_get */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_modulation
 * Description   : Perform PWM modulation
 * Arguments     : p_ctrl - The pointer to the motor driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_modulation (motor_driver_instance_ctrl_t * p_ctrl)
{
    float f_v_in[3]    = {0.0F};
    float f_mod_out[3] = {0.0F};

    p_ctrl->st_modulation.f4_vdc       = p_ctrl->f_vdc_ad;
    p_ctrl->st_modulation.f4_1_div_vdc = 1.0F / p_ctrl->f_vdc_ad;
    f_v_in[0] = p_ctrl->f_refu;
    f_v_in[1] = p_ctrl->f_refv;
    f_v_in[2] = p_ctrl->f_refw;

    rm_motor_driver_mod_run(p_ctrl, &(f_v_in[0]), &(f_mod_out[0]));

    rm_motor_driver_set_uvw_duty(p_ctrl, f_mod_out[0], f_mod_out[1], f_mod_out[2]);
}                                      /* End of function rm_motor_driver_modulation */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_1shunt_modulation
 * Description   : Perform PWM modulation for 1shunt
 * Arguments     : p_ctrl - The pointer to the motor driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_1shunt_modulation (motor_driver_instance_ctrl_t * p_ctrl)
{
    float   f_v_in[3]      = {0.0F};
    float   f_mod_out[3]   = {0.0F};
    int32_t s4_ref_max1    = 0;
    int32_t s4_ref_max2    = 0;
    int32_t s4_ref_mid1    = 0;
    int32_t s4_ref_mid2    = 0;
    int32_t s4_ref_temp    = 0;
    int32_t s4_raw_InvPeak = 0;
    int32_t s4_ref_max     = 0;
    int32_t s4_ref_mid     = 0;
    int32_t s4_ref_min     = 0;
    int32_t s4_AD1_trigger = 10;
    int32_t s4_AD2_trigger = 10;
    int32_t s4_mu_ref1     = 0;
    int32_t s4_mu_ref2     = 0;
    int32_t s4_mv_ref1     = 0;
    int32_t s4_mv_ref2     = 0;
    int32_t s4_mw_ref1     = 0;
    int32_t s4_mw_ref2     = 0;

    three_phase_duty_cycle_t temp_duty;

    motor_driver_phase_t max_phase;
    motor_driver_phase_t temp_phase;
    uint16_t             u2_temp_base  = p_ctrl->u2_carrier_base;
    uint16_t             u2_temp_deadt = p_ctrl->u2_deadtime_count;

    motor_driver_extended_cfg_t  * p_extended_cfg = (motor_driver_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    three_phase_instance_t const * p_three_phase  = p_ctrl->p_cfg->p_three_phase_instance;
    timer_instance_t const       * timer_u        =
        p_three_phase->p_cfg->p_timer_instance[p_extended_cfg->trigger_phase];
    timer_info_t temp_info;

    if (p_three_phase != NULL)
    {
        timer_u->p_api->infoGet(timer_u->p_ctrl, &temp_info);
        s4_raw_InvPeak = (int32_t) temp_info.period_counts;

        p_ctrl->st_modulation.f4_vdc       = p_ctrl->f_vdc_ad;
        p_ctrl->st_modulation.f4_1_div_vdc = 1.0F / p_ctrl->f_vdc_ad;
        f_v_in[0] = p_ctrl->f_refu;
        f_v_in[1] = p_ctrl->f_refv;
        f_v_in[2] = p_ctrl->f_refw;

        rm_motor_driver_mod_run(p_ctrl, &(f_v_in[0]), &(f_mod_out[0]));

        s4_ref_max = (uint16_t) ((u2_temp_base * (1.0F - f_mod_out[0])) + (u2_temp_deadt * MOTOR_DRIVER_DEF_HALF));
        s4_ref_mid = (uint16_t) ((u2_temp_base * (1.0F - f_mod_out[1])) + (u2_temp_deadt * MOTOR_DRIVER_DEF_HALF));
        s4_ref_min = (uint16_t) ((u2_temp_base * (1.0F - f_mod_out[2])) + (u2_temp_deadt * MOTOR_DRIVER_DEF_HALF));

        max_phase         = MOTOR_DRIVER_PHASE_U_PHASE;
        p_ctrl->mid_phase = MOTOR_DRIVER_PHASE_V_PHASE;
        p_ctrl->min_phase = MOTOR_DRIVER_PHASE_W_PHASE;

        /* Judge the phase value */
        if (s4_ref_max < s4_ref_mid)
        {
            s4_ref_temp       = s4_ref_max;
            s4_ref_max        = s4_ref_mid;
            s4_ref_mid        = s4_ref_temp;
            temp_phase        = max_phase;
            max_phase         = p_ctrl->mid_phase;
            p_ctrl->mid_phase = temp_phase;
        }

        if (s4_ref_max < s4_ref_min)
        {
            s4_ref_temp       = s4_ref_max;
            s4_ref_max        = s4_ref_min;
            s4_ref_min        = s4_ref_temp;
            temp_phase        = max_phase;
            max_phase         = p_ctrl->min_phase;
            p_ctrl->min_phase = temp_phase;
        }

        if (s4_ref_mid < s4_ref_min)
        {
            s4_ref_temp       = s4_ref_mid;
            s4_ref_mid        = s4_ref_min;
            s4_ref_min        = s4_ref_temp;
            temp_phase        = p_ctrl->mid_phase;
            p_ctrl->mid_phase = p_ctrl->min_phase;
            p_ctrl->min_phase = temp_phase;
        }

        /* Adjust middle PWM timing */
        if ((s4_ref_mid - s4_ref_min) < p_extended_cfg->s4_difference_minimum)
        {
            s4_ref_mid1 = s4_ref_min + p_extended_cfg->s4_difference_minimum;
            if (s4_ref_mid1 > (s4_raw_InvPeak - 1))
            {
                s4_ref_mid1 = s4_raw_InvPeak - 1;
            }

            s4_ref_mid2 = s4_ref_mid - (s4_ref_mid1 - s4_ref_mid);
        }
        else
        {
            s4_ref_mid1 = s4_ref_mid;
            s4_ref_mid2 = s4_ref_mid;
        }

        /* Adjust maximum PWM timing */
        if ((s4_ref_max - s4_ref_mid1) < p_extended_cfg->s4_difference_minimum)
        {
            s4_ref_max1 = s4_ref_mid1 + p_extended_cfg->s4_difference_minimum;
            if (s4_ref_max1 > (s4_raw_InvPeak - 1))
            {
                s4_ref_max1 = s4_raw_InvPeak - 1;
            }

            s4_ref_max2 = s4_ref_max - (s4_ref_max1 - s4_ref_max);
        }
        else
        {
            s4_ref_max1 = s4_ref_max;
            s4_ref_max2 = s4_ref_max;
        }

        /* Shift limit */
        if (s4_ref_mid2 < 1)
        {
            s4_ref_mid2 = 1;
        }

        if (s4_ref_max2 < 1)
        {
            s4_ref_max2 = 1;
        }

        /* Set A/D trigger timing */
        s4_AD1_trigger = s4_ref_mid1 - (p_extended_cfg->s4_difference_minimum - p_extended_cfg->s4_adjust_adc_delay);
        s4_AD2_trigger = s4_ref_max1 - (p_extended_cfg->s4_difference_minimum - p_extended_cfg->s4_adjust_adc_delay);

        switch (p_ctrl->min_phase)
        {
            case MOTOR_DRIVER_PHASE_U_PHASE:
            {
                s4_mu_ref1 = s4_ref_min;
                s4_mu_ref2 = s4_ref_min;
                break;
            }

            case MOTOR_DRIVER_PHASE_V_PHASE:
            {
                s4_mv_ref1 = s4_ref_min;
                s4_mv_ref2 = s4_ref_min;
                break;
            }

            case MOTOR_DRIVER_PHASE_W_PHASE:
            {
                s4_mw_ref1 = s4_ref_min;
                s4_mw_ref2 = s4_ref_min;
                break;
            }

            default:
            {
                break;
            }
        }

        switch (p_ctrl->mid_phase)
        {
            case MOTOR_DRIVER_PHASE_U_PHASE:
            {
                s4_mu_ref1 = s4_ref_mid1;
                s4_mu_ref2 = s4_ref_mid2;
                break;
            }

            case MOTOR_DRIVER_PHASE_V_PHASE:
            {
                s4_mv_ref1 = s4_ref_mid1;
                s4_mv_ref2 = s4_ref_mid2;
                break;
            }

            case MOTOR_DRIVER_PHASE_W_PHASE:
            {
                s4_mw_ref1 = s4_ref_mid1;
                s4_mw_ref2 = s4_ref_mid2;
                break;
            }

            default:
            {
                break;
            }
        }

        switch (max_phase)
        {
            case MOTOR_DRIVER_PHASE_U_PHASE:
            {
                s4_mu_ref1 = s4_ref_max1;
                s4_mu_ref2 = s4_ref_max2;
                break;
            }

            case MOTOR_DRIVER_PHASE_V_PHASE:
            {
                s4_mv_ref1 = s4_ref_max1;
                s4_mv_ref2 = s4_ref_max2;
                break;
            }

            case MOTOR_DRIVER_PHASE_W_PHASE:
            {
                s4_mw_ref1 = s4_ref_max1;
                s4_mw_ref2 = s4_ref_max2;
                break;
            }

            default:
            {
                break;
            }
        }

        temp_duty.duty[0]        = (uint32_t) s4_mu_ref1;
        temp_duty.duty[1]        = (uint32_t) s4_mv_ref1;
        temp_duty.duty[2]        = (uint32_t) s4_mw_ref1;
        temp_duty.duty_buffer[0] = (uint32_t) s4_mu_ref2;
        temp_duty.duty_buffer[1] = (uint32_t) s4_mv_ref2;
        temp_duty.duty_buffer[2] = (uint32_t) s4_mw_ref2;

        p_three_phase->p_api->dutyCycleSet(p_three_phase->p_ctrl, &temp_duty);

        R_GPT_AdcTriggerSet(timer_u->p_ctrl, GPT_ADC_COMPARE_MATCH_ADC_A, (uint32_t) s4_AD1_trigger);
        R_GPT_AdcTriggerSet(timer_u->p_ctrl, GPT_ADC_COMPARE_MATCH_ADC_B, (uint32_t) s4_AD2_trigger);
    }
}                                      /* End of function rm_motor_driver_1shunt_modulation */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_pin_cfg
 * Description  : Configure a pin
 * Arguments    : pin -
 *                    The pin
 *                cfg -
 *                    Configuration for the pin (PmnPFS register setting)
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_driver_pin_cfg (bsp_io_port_pin_t pin, uint32_t cfg)
{
    R_BSP_PinAccessEnable();
    R_BSP_PinCfg(pin, cfg);
    R_BSP_PinAccessDisable();
}                                      /* End of function rm_motor_driver_pin_cfg() */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_output_enable
 * Description   : Enable PWM output
 * Arguments     : p_ctrl - The pointer to the motor driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_output_enable (motor_driver_instance_ctrl_t * p_ctrl)
{
    if (1U == p_ctrl->u1_flag_port_enable)
    {
        motor_driver_cfg_t           * p_cfg         = (motor_driver_cfg_t *) p_ctrl->p_cfg;
        motor_driver_extended_cfg_t  * p_extended    = (motor_driver_extended_cfg_t *) p_cfg->p_extend;
        three_phase_instance_t const * p_three_phase = p_cfg->p_three_phase_instance;
        timer_instance_t const       * p_u_phase_gpt = p_three_phase->p_cfg->p_timer_instance[0];
        timer_instance_t const       * p_v_phase_gpt = p_three_phase->p_cfg->p_timer_instance[1];
        timer_instance_t const       * p_w_phase_gpt = p_three_phase->p_cfg->p_timer_instance[2];

        p_ctrl->u4_gtioca_low_cfg |= MOTOR_DRIVER_IO_PORT_PERIPHERAL_MASK;
        p_ctrl->u4_gtiocb_low_cfg |= MOTOR_DRIVER_IO_PORT_PERIPHERAL_MASK;

        /* Set pin function */
        rm_motor_driver_pin_cfg(p_extended->port_up, p_ctrl->u4_gtioca_low_cfg);
        rm_motor_driver_pin_cfg(p_extended->port_un, p_ctrl->u4_gtiocb_low_cfg);
        rm_motor_driver_pin_cfg(p_extended->port_vp, p_ctrl->u4_gtioca_low_cfg);
        rm_motor_driver_pin_cfg(p_extended->port_vn, p_ctrl->u4_gtiocb_low_cfg);
        rm_motor_driver_pin_cfg(p_extended->port_wp, p_ctrl->u4_gtioca_low_cfg);
        rm_motor_driver_pin_cfg(p_extended->port_wn, p_ctrl->u4_gtiocb_low_cfg);

        /* PWM output enable */
        R_GPT_OutputEnable(p_u_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputEnable(p_v_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
        R_GPT_OutputEnable(p_w_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

        p_ctrl->u1_flag_port_enable = 0U;
    }
}                                      /* End of function rm_motor_driver_output_enable */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_output_disable
 * Description   : Disable PWM output
 * Arguments     : p_ctrl - The pointer to the motor driver module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_output_disable (motor_driver_instance_ctrl_t * p_ctrl)
{
    motor_driver_cfg_t           * p_cfg         = (motor_driver_cfg_t *) p_ctrl->p_cfg;
    motor_driver_extended_cfg_t  * p_extended    = (motor_driver_extended_cfg_t *) p_cfg->p_extend;
    three_phase_instance_t const * p_three_phase = p_cfg->p_three_phase_instance;
    timer_instance_t const       * p_u_phase_gpt = p_three_phase->p_cfg->p_timer_instance[0];
    timer_instance_t const       * p_v_phase_gpt = p_three_phase->p_cfg->p_timer_instance[1];
    timer_instance_t const       * p_w_phase_gpt = p_three_phase->p_cfg->p_timer_instance[2];

    /* PWM output disable */
    R_GPT_OutputDisable(p_u_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
    R_GPT_OutputDisable(p_v_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);
    R_GPT_OutputDisable(p_w_phase_gpt->p_ctrl, GPT_IO_PIN_GTIOCA_AND_GTIOCB);

    p_ctrl->u4_gtioca_low_cfg &= MOTOR_DRIVER_IO_PORT_GPIO_MASK;
    p_ctrl->u4_gtiocb_low_cfg &= MOTOR_DRIVER_IO_PORT_GPIO_MASK;

    rm_motor_driver_pin_cfg(p_extended->port_up, p_ctrl->u4_gtioca_low_cfg);
    rm_motor_driver_pin_cfg(p_extended->port_un, p_ctrl->u4_gtiocb_low_cfg);
    rm_motor_driver_pin_cfg(p_extended->port_vp, p_ctrl->u4_gtioca_low_cfg);
    rm_motor_driver_pin_cfg(p_extended->port_vn, p_ctrl->u4_gtiocb_low_cfg);
    rm_motor_driver_pin_cfg(p_extended->port_wp, p_ctrl->u4_gtioca_low_cfg);
    rm_motor_driver_pin_cfg(p_extended->port_wn, p_ctrl->u4_gtiocb_low_cfg);

    p_ctrl->u1_flag_port_enable = 1U;
}                                      /* End of function rm_motor_driver_output_disable */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_svpwm
 * Description  : Space vector modulation
 * Arguments    : p_f4_v_in -
 *                    Input data, in an array [Vu,Vv,Vw]
 *                p_f4_v_out -
 *                    Where to store output data, in an array [Vu,Vv,Vw]
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_driver_mod_svpwm (const float * p_f4_v_in, float * p_f4_v_out)
{
    float f4_v_max;
    float f4_v_min;
    float f4_v_com;

    /* Sort vu vv vw */
    if (p_f4_v_in[0] > p_f4_v_in[1])
    {
        f4_v_max = p_f4_v_in[0];
        f4_v_min = p_f4_v_in[1];
    }
    else
    {
        f4_v_max = p_f4_v_in[1];
        f4_v_min = p_f4_v_in[0];
    }

    /* Vcom = (Vmin + Vmax)/2 */
    if (p_f4_v_in[2] > f4_v_max)
    {
        f4_v_com = (p_f4_v_in[2] + f4_v_min) * MOTOR_DRIVER_DEF_HALF;
    }
    else if (p_f4_v_in[2] < f4_v_min)
    {
        f4_v_com = (f4_v_max + p_f4_v_in[2]) * MOTOR_DRIVER_DEF_HALF;
    }
    else
    {
        f4_v_com = (f4_v_max + f4_v_min) * MOTOR_DRIVER_DEF_HALF;
    }

    p_f4_v_out[0] = p_f4_v_in[0] - f4_v_com;
    p_f4_v_out[1] = p_f4_v_in[1] - f4_v_com;
    p_f4_v_out[2] = p_f4_v_in[2] - f4_v_com;
}                                      /* End of function rm_motor_driver_mod_svpwm() */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_limit
 * Description  : Limits the duty cycle, and detect saturation (if function enabled)
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *                p_f4_duty -
 *                    Pointer to the input and output duty cycle array, array length = 3
 * Return Value : None
 **********************************************************************************************************************/
static inline void rm_motor_driver_mod_limit (motor_driver_modulation_t * p_mod, float * p_f4_duty)
{
    float f4_min_duty = p_mod->f4_min_duty;
    float f4_max_duty = p_mod->f4_max_duty;

    if (p_f4_duty[0] > f4_max_duty)
    {
        p_f4_duty[0] = f4_max_duty;
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag |= MOTOR_DRIVER_SATFLAG_BITU;
#endif
    }
    else if (p_f4_duty[0] < f4_min_duty)
    {
        p_f4_duty[0] = f4_min_duty;
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag |= MOTOR_DRIVER_SATFLAG_BITU;
#endif
    }
    else
    {
        /* Clear correspond saturation flag bit */
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag &= (~MOTOR_DRIVER_SATFLAG_BITU);
#endif
    }

    if (p_f4_duty[1] > f4_max_duty)
    {
        p_f4_duty[1] = f4_max_duty;
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag |= MOTOR_DRIVER_SATFLAG_BITV;
#endif
    }
    else if (p_f4_duty[1] < f4_min_duty)
    {
        p_f4_duty[1] = f4_min_duty;
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag |= MOTOR_DRIVER_SATFLAG_BITV;
#endif
    }
    else
    {
        /* Clear correspond saturation flag bit */
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag &= (~MOTOR_DRIVER_SATFLAG_BITV);
#endif
    }

    if (p_f4_duty[2] > f4_max_duty)
    {
        p_f4_duty[2] = f4_max_duty;
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag |= MOTOR_DRIVER_SATFLAG_BITW;
#endif
    }
    else if (p_f4_duty[2] < f4_min_duty)
    {
        p_f4_duty[2] = f4_min_duty;
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag |= MOTOR_DRIVER_SATFLAG_BITW;
#endif
    }
    else
    {
        /* Clear correspond saturation flag bit */
#if (MOD_DETECT_SATURATION == 1)
        p_mod->u1_sat_flag &= (~MOTOR_DRIVER_SATFLAG_BITW);
#endif
    }
}                                      /* End of function rm_motor_driver_mod_limit() */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_run
 * Description  : Calculates duty cycle from input 3-phase voltage (bipolar)
 * Arguments    : p_ctrl -
 *                    Pointer to the motor driver module valuables
 *              : p_f4_v_in -
 *                    Pointer to the 3-phase input voltage
 *              : p_f4_duty_out -
 *                    Where to store the 3-phase output duty cycle
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_driver_mod_run (motor_driver_instance_ctrl_t * p_ctrl,
                                     const float                  * p_f4_v_in,
                                     float                        * p_f4_duty_out)
{
    float f4_v_out[3];
    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (MOTOR_DRIVER_MODULATION_METHOD_SVPWM == p_extended_cfg->modulation_method)
    {
        rm_motor_driver_mod_svpwm(p_f4_v_in, f4_v_out);
    }
    else
    {
        f4_v_out[0] = p_f4_v_in[0];
        f4_v_out[1] = p_f4_v_in[1];
        f4_v_out[2] = p_f4_v_in[2];
    }

    p_f4_duty_out[0] = (f4_v_out[0] * p_ctrl->st_modulation.f4_1_div_vdc) + p_ctrl->st_modulation.f4_neutral_duty;
    p_f4_duty_out[1] = (f4_v_out[1] * p_ctrl->st_modulation.f4_1_div_vdc) + p_ctrl->st_modulation.f4_neutral_duty;
    p_f4_duty_out[2] = (f4_v_out[2] * p_ctrl->st_modulation.f4_1_div_vdc) + p_ctrl->st_modulation.f4_neutral_duty;

    rm_motor_driver_mod_limit(&(p_ctrl->st_modulation), p_f4_duty_out);
}                                      /* End of function rm_motor_driver_mod_run() */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_set_max_duty
 * Description  : Sets the maximum duty cycle
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *                f4_max_duty -
 *                    Maximum duty cycle to set
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_driver_mod_set_max_duty (motor_driver_modulation_t * p_mod, float f4_max_duty)
{
    if ((0 != p_mod) && ((f4_max_duty > 0.0F) && (f4_max_duty <= 1.0F)))
    {
        p_mod->f4_max_duty     = f4_max_duty;
        p_mod->f4_neutral_duty = (p_mod->f4_max_duty + p_mod->f4_min_duty) * MOTOR_DRIVER_DEF_HALF;
    }
}                                      /* End of function rm_motor_driver_mod_set_max_duty() */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_set_min_duty
 * Description  : Sets the minimum duty cycle
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *                f4_max_duty -
 *                    Minimum duty cycle to set
 * Return Value : None
 **********************************************************************************************************************/
static void rm_motor_driver_mod_set_min_duty (motor_driver_modulation_t * p_mod, float f4_min_duty)
{
    if ((0 != p_mod) && (f4_min_duty > 0.0F))
    {
        p_mod->f4_min_duty     = f4_min_duty;
        p_mod->f4_neutral_duty = (p_mod->f4_max_duty + p_mod->f4_min_duty) * MOTOR_DRIVER_DEF_HALF;
    }
}                                      /* End of function rm_motor_driver_mod_set_min_duty() */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_get_voltage_multiplier
 * Description  : Gets the voltage multiplier
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *                u1_method -
 *                    Modulation method (SPWM or SVPWM)
 * Return Value : Voltage multiplier
 **********************************************************************************************************************/
static float rm_motor_driver_mod_get_voltage_multiplier (motor_driver_modulation_t * p_mod, uint8_t u1_method)
{
    float f4_usable_duty_cycle;

    f4_usable_duty_cycle = (p_mod->f4_max_duty - p_mod->f4_min_duty) -
                           (MOTOR_DRIVER_MULTIPLE_TWO * p_mod->f4_voltage_error_ratio);

    if (MOTOR_DRIVER_METHOD_SVPWM == u1_method)
    {
        f4_usable_duty_cycle = f4_usable_duty_cycle * MOTOR_DRIVER_SVPWM_MULT;
    }

    return f4_usable_duty_cycle;
}                                      /* End of function rm_motor_driver_mod_get_voltage_multiplier */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_get_vamax
 * Description  : Gets the maximum magnitude of voltage vector
 * Arguments    : p_mod -
 *                    The pointer to the modulation data structure
 *                u1_method -
 *                    Modulation method (SPWM or SVPWM)
 * Return Value : The maximum magnitude of voltage vector
 **********************************************************************************************************************/
static float rm_motor_driver_mod_get_vamax (motor_driver_modulation_t * p_mod, uint8_t u1_method)
{
    float ret = (MOTOR_DRIVER_VDC_TO_VAMAX_MULT * p_mod->f4_vdc);
    ret *= rm_motor_driver_mod_get_voltage_multiplier(p_mod, u1_method);

    return ret;
}                                      /* End of function rm_motor_driver_mod_get_vamax */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_cyclic
 * Description   : Cyclic process for driver accsess (Call at A/D conversion finish interrupt)
 * Arguments     : p_args - The pointer to arguments of A/D conversion finish intterupt callback
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_driver_cyclic (adc_callback_args_t * p_args)
{
    motor_driver_instance_ctrl_t * p_instance = (motor_driver_instance_ctrl_t *) p_args->p_context;
    motor_driver_callback_args_t   temp_args_t;

    /* Get A/D converted data (Phase current & main line voltage) */
    rm_motor_driver_current_get(p_instance);

    if (MOTOR_DRIVER_OPEN == p_instance->open)
    {
        /* Invoke the callback function if it is set. */
        if (NULL != p_instance->p_cfg->p_callback)
        {
            temp_args_t.event     = MOTOR_DRIVER_EVENT_FORWARD;
            temp_args_t.p_context = p_instance->p_cfg->p_context;
            (p_instance->p_cfg->p_callback)(&temp_args_t);
        }

        /* Perform current control process (if set) */
        if (NULL != p_instance->p_cfg->p_callback)
        {
            temp_args_t.event     = MOTOR_DRIVER_EVENT_CURRENT;
            temp_args_t.p_context = p_instance->p_cfg->p_context;
            (p_instance->p_cfg->p_callback)(&temp_args_t);
        }

        /* PWM modulation */
        if (MOTOR_DRIVER_FLG_SET == p_instance->u1_flag_offset_calc)
        {
            rm_motor_driver_modulation(p_instance);
        }

        /* Invoke the callback function if it is set. */
        if (NULL != p_instance->p_cfg->p_callback)
        {
            temp_args_t.event     = MOTOR_DRIVER_EVENT_BACKWARD;
            temp_args_t.p_context = p_instance->p_cfg->p_context;
            (p_instance->p_cfg->p_callback)(&temp_args_t);
        }
    }
}                                      /* End of function rm_motor_driver_cyclic */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_1shunt_cyclic
 * Description   : Cyclic process for driver accsess (Call at GPT underflow interrupt)
 * Arguments     : p_args - The pointer to arguments of timer intterupt callback
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_driver_1shunt_cyclic (timer_callback_args_t * p_args)
{
    motor_driver_instance_ctrl_t * p_instance = (motor_driver_instance_ctrl_t *) p_args->p_context;
    motor_driver_callback_args_t   temp_args_t;

    if (MOTOR_DRIVER_OPEN == p_instance->open)
    {
        if (TIMER_EVENT_CYCLE_END == p_args->event)
        {
            /* Get A/D converted data (Phase current & main line voltage) */
            rm_motor_driver_1shunt_current_get(p_instance);

            /* Invoke the callback function if it is set. */
            if (NULL != p_instance->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_DRIVER_EVENT_FORWARD;
                temp_args_t.p_context = p_instance->p_cfg->p_context;
                (p_instance->p_cfg->p_callback)(&temp_args_t);
            }

            /* Perform current control process (if set) */
            if (NULL != p_instance->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_DRIVER_EVENT_CURRENT;
                temp_args_t.p_context = p_instance->p_cfg->p_context;
                (p_instance->p_cfg->p_callback)(&temp_args_t);
            }

            /* PWM modulation */
            if (MOTOR_DRIVER_FLG_SET == p_instance->u1_flag_offset_calc)
            {
                rm_motor_driver_1shunt_modulation(p_instance);
            }
            else
            {
                p_instance->f_refu = 0.0F;
                p_instance->f_refv = 0.0F;
                p_instance->f_refw = 0.0F;
                rm_motor_driver_1shunt_modulation(p_instance);
            }

            /* Invoke the callback function if it is set. */
            if (NULL != p_instance->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_DRIVER_EVENT_BACKWARD;
                temp_args_t.p_context = p_instance->p_cfg->p_context;
                (p_instance->p_cfg->p_callback)(&temp_args_t);
            }
        }
    }
}                                      /* End of function rm_motor_driver_1shunt_cyclic */

#if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 1)

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_shared_cyclic
 * Description   : Cyclic process by using shared instance for driver accsess (Call at A/D conversion finish interrupt)
 * Arguments     : p_args - The pointer to arguments of A/D conversion finish intterupt callback
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_driver_shared_cyclic (adc_callback_args_t * p_args)
{
    motor_driver_shared_instance_ctrl_t * p_instance = (motor_driver_shared_instance_ctrl_t *) p_args->p_context;
    adc_callback_args_t            temp_args_t;
    motor_driver_instance_ctrl_t * p_ctrl;

    uint8_t i;

    if (MOTOR_DRIVER_SHARED_ADC_OPEN == p_instance->open)
    {
        switch (p_args->event)
        {
            default:
            {
                break;
            }

            case ADC_EVENT_SCAN_COMPLETE:
            case ADC_EVENT_SCAN_COMPLETE_GROUP_B:
            {
                for (i = 0; i < MOTOR_DRIVER_CFG_SUPPORT_MOTOR_NUM; i++)
                {
                    p_ctrl = (motor_driver_instance_ctrl_t *) p_instance->p_context[i];

                    if (NULL == p_ctrl)
                    {
                        /* Do nothing */
                    }
                    else
                    {
                        motor_driver_extended_cfg_t * p_extended_cfg =
                            (motor_driver_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

                        /* Check scan complete ad channel */
                        if (p_args->group_mask & (1 << p_extended_cfg->adc_group))
                        {
                            temp_args_t = *p_args;

                            /* Set motor_driver instance */
                            temp_args_t.p_context = p_instance->p_context[i];
                            rm_motor_driver_cyclic(&temp_args_t);
                        }
                    }
                }

                break;
            }
        }
    }
}                                      /* End of function rm_motor_driver_shared_cyclic */

#endif // MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 1

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_adc_b_open
 * Description   : Open operation with adc_b module
 * Arguments     : p_instance_ctrl - The pointer to instance control
 *               : p_cfg  - The pointer to configuration data
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_adc_b_open (motor_driver_instance_ctrl_t   * p_instance_ctrl,
                                        motor_driver_cfg_t const * const p_cfg)
{
 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->open(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg);
        p_cfg->p_adc_instance->p_api->scanCfg(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_channel_cfg);

        if (p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT)
        {
            p_cfg->p_adc_instance->p_api->callbackSet(p_cfg->p_adc_instance->p_ctrl,
                                                      rm_motor_driver_cyclic,
                                                      p_instance_ctrl,
                                                      &(p_instance_ctrl->adc_callback_args));
        }

        p_cfg->p_adc_instance->p_api->calibrate(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg->p_extend);

        adc_status_t status = {.state = ADC_STATE_SCAN_IN_PROGRESS};
        while (ADC_STATE_IDLE != status.state)
        {
            p_cfg->p_adc_instance->p_api->scanStatusGet(p_cfg->p_adc_instance->p_ctrl, &status);
        }

        p_cfg->p_adc_instance->p_api->scanStart(p_cfg->p_adc_instance->p_ctrl);
    }

 #else                                 /* SUPPORT_SHARED_ADC == 1 */
    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;
    p_instance_ctrl->p_shared_instance_ctrl = p_extended_cfg->p_shared_cfg->p_shared_instance_ctrl;

    motor_driver_shared_instance_ctrl_t * p_shared_ctrl = p_instance_ctrl->p_shared_instance_ctrl;

    /* After the second motor */
    if (p_shared_ctrl->registered_motor_count != 0)
    {
        /* Register driver module instance for callback */
        p_instance_ctrl->p_shared_instance_ctrl->p_context[p_shared_ctrl->registered_motor_count] = p_instance_ctrl;

        /* count up the number of registered motor */
        (p_shared_ctrl->registered_motor_count)++;
    }
    /* For the first motor */
    else
    {
        if (p_extended_cfg->p_shared_cfg->p_adc_instance_first != NULL)
        {
            adc_instance_t const * p_adc_instance;
            p_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_first;

            FSP_CRITICAL_SECTION_DEFINE;
            FSP_CRITICAL_SECTION_ENTER;

            /* Open and setting ADC instance */
            p_adc_instance->p_api->open(p_adc_instance->p_ctrl, p_adc_instance->p_cfg);
            FSP_CRITICAL_SECTION_EXIT;
            p_adc_instance->p_api->scanCfg(p_adc_instance->p_ctrl, p_adc_instance->p_channel_cfg);

            if (p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT)
            {
                /* Register callback to ADC module */
                p_adc_instance->p_api->callbackSet(p_adc_instance->p_ctrl,
                                                   rm_motor_driver_shared_cyclic,
                                                   p_instance_ctrl->p_shared_instance_ctrl,
                                                   &(p_instance_ctrl->adc_callback_args));
            }

            p_adc_instance->p_api->calibrate(p_adc_instance->p_ctrl, p_adc_instance->p_cfg->p_extend);

            adc_status_t status = {.state = ADC_STATE_SCAN_IN_PROGRESS};
            while (ADC_STATE_IDLE != status.state)
            {
                p_adc_instance->p_api->scanStatusGet(p_adc_instance->p_ctrl, &status);
            }

            /* Start ADC module */
            p_adc_instance->p_api->scanStart(p_adc_instance->p_ctrl);

            /* Set ADC shared information */
            p_instance_ctrl->p_shared_instance_ctrl->open = MOTOR_DRIVER_SHARED_ADC_OPEN;
            p_instance_ctrl->p_shared_instance_ctrl->p_context[p_shared_ctrl->registered_motor_count] =
                p_instance_ctrl;
            (p_shared_ctrl->registered_motor_count)++;
        }
    }
 #endif                                /* SUPPORT_SHARED_ADC == 1 */
}                                      /* End of function rm_motor_driver_adc_b_open() */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_adc_b_close
 * Description   : Close operation with adc_b module
 * Arguments     : p_instance_ctrl - The pointer to instance control
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_adc_b_close (motor_driver_instance_ctrl_t * p_instance_ctrl)
{
    motor_driver_cfg_t * p_cfg = (motor_driver_cfg_t *) p_instance_ctrl->p_cfg;

 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    /* Close ADC module */
    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->close(p_cfg->p_adc_instance->p_ctrl);
    }

 #else                                 /* SUPPORT_SHARED_ADC == 1 */
    adc_instance_t const                * p_adc_instance;
    motor_driver_shared_instance_ctrl_t * p_shared_ctrl  = p_instance_ctrl->p_shared_instance_ctrl;
    motor_driver_extended_cfg_t         * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* When the first motor is closed, ADC module should be closed. */
    if (1 == p_shared_ctrl->registered_motor_count)
    {
        p_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_first;
        p_adc_instance->p_api->close(p_adc_instance->p_ctrl);

        /* Clear context array */
        uint8_t i;
        for (i = 0; i < MOTOR_DRIVER_CFG_SUPPORT_MOTOR_NUM; i++)
        {
            p_instance_ctrl->p_shared_instance_ctrl->p_context[i] = NULL;
        }

        p_instance_ctrl->p_shared_instance_ctrl->open = 0U;
        p_shared_ctrl->registered_motor_count         = 0U;
    }
    else
    {
        /* Only declease motor count */
        p_shared_ctrl->registered_motor_count--;
    }
    FSP_CRITICAL_SECTION_EXIT;
 #endif                                /* SUPPORT_SHARED_ADC == 1 */
}

#else                                  // MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 0

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_adc_open
 * Description   : Open operation with adc_b module
 * Arguments     : p_instance_ctrl - The pointer to instance control
 *               : p_cfg  - The pointer to configuration data
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_adc_open (motor_driver_instance_ctrl_t   * p_instance_ctrl,
                                      motor_driver_cfg_t const * const p_cfg)
{
    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;
 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    /* Start ADC module */
    /* For 1shunt, Vdc is need to read by ADC module #1. */
    if (MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT == p_cfg->shunt)
    {
        /* When different AD units are used to read 1shunt current and vdc,
         * the unit for vdc should be open. */
        if (p_extended_cfg->iu_ad_unit != p_extended_cfg->vdc_ad_unit)
        {
            if (p_cfg->p_adc2_instance != NULL)
            {
                p_cfg->p_adc2_instance->p_api->open(p_cfg->p_adc2_instance->p_ctrl, p_cfg->p_adc2_instance->p_cfg);
                p_cfg->p_adc2_instance->p_api->scanCfg(p_cfg->p_adc2_instance->p_ctrl,
                                                       p_cfg->p_adc2_instance->p_channel_cfg);
            }
        }
    }

    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->open(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg);
        p_cfg->p_adc_instance->p_api->scanCfg(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_channel_cfg);
        p_cfg->p_adc_instance->p_api->calibrate(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg->p_extend);

        if (p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT)
        {
            p_cfg->p_adc_instance->p_api->callbackSet(p_cfg->p_adc_instance->p_ctrl,
                                                      rm_motor_driver_cyclic,
                                                      p_instance_ctrl,
                                                      &(p_instance_ctrl->adc_callback_args));
        }

        p_cfg->p_adc_instance->p_api->scanStart(p_cfg->p_adc_instance->p_ctrl);
    }

 #else                                 /* SUPPORT_SHARED_ADC == 1 */
    p_instance_ctrl->p_shared_instance_ctrl = p_extended_cfg->p_shared_cfg->p_shared_instance_ctrl;

    motor_driver_shared_instance_ctrl_t * p_shared_ctrl = p_instance_ctrl->p_shared_instance_ctrl;
    adc_instance_t const                * p_adc_instance;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* For the first motor */
    if (0 == p_shared_ctrl->registered_motor_count)
    {
        if (p_extended_cfg->p_shared_cfg->p_adc_instance_first != NULL)
        {
            p_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_first;

            /* Open and setting ADC instance */
            p_adc_instance->p_api->open(p_adc_instance->p_ctrl, p_adc_instance->p_cfg);
            p_adc_instance->p_api->scanCfg(p_adc_instance->p_ctrl, p_adc_instance->p_channel_cfg);
            p_adc_instance->p_api->calibrate(p_adc_instance->p_ctrl, p_adc_instance->p_cfg->p_extend);

            if ((p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT) &&
                (MOTOR_DRIVER_SELECT_ADC_INSTANCE_FIRST == p_extended_cfg->interrupt_adc))
            {
                /* Register callback to ADC module */
                p_adc_instance->p_api->callbackSet(p_adc_instance->p_ctrl, rm_motor_driver_cyclic, p_instance_ctrl,
                                                   &(p_instance_ctrl->adc_callback_args));
            }

            /* Start ADC module */
            p_adc_instance->p_api->scanStart(p_adc_instance->p_ctrl);

            /* Set ADC shared information */
            p_instance_ctrl->p_shared_instance_ctrl->open = MOTOR_DRIVER_SHARED_ADC_OPEN;
            p_instance_ctrl->p_shared_instance_ctrl->p_context[p_shared_ctrl->registered_motor_count] =
                p_instance_ctrl;
            (p_shared_ctrl->registered_motor_count)++;
        }

        if ((MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT == p_cfg->shunt) &&
            (p_extended_cfg->iu_ad_unit == p_extended_cfg->vdc_ad_unit))
        {
            /* When 1shunt current and Vdc are read with same ADC channel,
             * second ADC module should not be opened. */
        }
        /* In other case, second ADC module is opened here. */
        else
        {
            if (p_extended_cfg->p_shared_cfg->p_adc_instance_second != NULL)
            {
                p_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_second;

                if (p_adc_instance != NULL)
                {
                    p_adc_instance->p_api->open(p_adc_instance->p_ctrl, p_adc_instance->p_cfg);
                    p_adc_instance->p_api->scanCfg(p_adc_instance->p_ctrl, p_adc_instance->p_channel_cfg);
                    p_adc_instance->p_api->calibrate(p_adc_instance->p_ctrl, p_adc_instance->p_cfg->p_extend);

                    if ((p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT) &&
                        (MOTOR_DRIVER_SELECT_ADC_INSTANCE_SECOND == p_extended_cfg->interrupt_adc))
                    {
                        /* Register callback to ADC module */
                        p_adc_instance->p_api->callbackSet(p_adc_instance->p_ctrl,
                                                           rm_motor_driver_cyclic,
                                                           p_instance_ctrl,
                                                           &(p_instance_ctrl->adc_callback_args));
                    }

                    /* Not 1 shunt, start 2nd adc here */
                    if (p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT)
                    {
                        p_adc_instance->p_api->scanStart(p_adc_instance->p_ctrl);
                    }
                }
            }
        }
    }
    /* After the second motor */
    else
    {
        if (p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT)
        {
            if (MOTOR_DRIVER_SELECT_ADC_INSTANCE_FIRST == p_extended_cfg->interrupt_adc)
            {
                p_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_first;

                p_adc_instance->p_api->scanStop(p_adc_instance->p_ctrl);

                /* Register callback to ADC module */
                p_adc_instance->p_api->callbackSet(p_adc_instance->p_ctrl, rm_motor_driver_cyclic, p_instance_ctrl,
                                                   &(p_instance_ctrl->adc_callback_args));
                p_adc_instance->p_api->scanStart(p_adc_instance->p_ctrl);
            }
            else if (MOTOR_DRIVER_SELECT_ADC_INSTANCE_SECOND == p_extended_cfg->interrupt_adc)
            {
                p_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_second;

                p_adc_instance->p_api->scanStop(p_adc_instance->p_ctrl);

                /* Register callback to ADC module */
                p_adc_instance->p_api->callbackSet(p_adc_instance->p_ctrl, rm_motor_driver_cyclic, p_instance_ctrl,
                                                   &(p_instance_ctrl->adc_callback_args));
                p_adc_instance->p_api->scanStart(p_adc_instance->p_ctrl);
            }
            else
            {
                /* Do nothing */
            }
        }

        /* Register driver module instance for callback */
        p_instance_ctrl->p_shared_instance_ctrl->p_context[p_shared_ctrl->registered_motor_count] = p_instance_ctrl;

        /* count up the number of registered motor */
        (p_shared_ctrl->registered_motor_count)++;
    }
    FSP_CRITICAL_SECTION_EXIT;
 #endif                                /* SUPPORT_SHARED_ADC == 1 */
}                                      /* End of function rm_motor_driver_adc_open() */

/***********************************************************************************************************************
 * Function Name : rm_motor_driver_adc_close
 * Description   : Close operation with adc_b module
 * Arguments     : p_instance_ctrl - The pointer to instance control
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_driver_adc_close (motor_driver_instance_ctrl_t * p_instance_ctrl)
{
    motor_driver_cfg_t * p_cfg = (motor_driver_cfg_t *) p_instance_ctrl->p_cfg;

 #if (MOTOR_DRIVER_CFG_SUPPORT_SHARED_ADC == 0) /* Original ADC module support */
    /* Close ADC module */
    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->close(p_cfg->p_adc_instance->p_ctrl);
    }

    if (MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT == p_cfg->shunt)
    {
        if (p_cfg->p_adc2_instance != NULL)
        {
            p_cfg->p_adc2_instance->p_api->close(p_cfg->p_adc2_instance->p_ctrl);
        }
    }

 #else                                 /* SUPPORT_SHARED_ADC == 1 */
    motor_driver_extended_cfg_t * p_extended_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;
    p_instance_ctrl->p_shared_instance_ctrl = p_extended_cfg->p_shared_cfg->p_shared_instance_ctrl;
    motor_driver_shared_instance_ctrl_t * p_shared_ctrl = p_instance_ctrl->p_shared_instance_ctrl;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* When the first motor is closed, all ADC modules should be closed. */
    if (1U == p_shared_ctrl->registered_motor_count)
    {
        adc_instance_t const * p_temp_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_first;

        if (p_temp_adc_instance != NULL)
        {
            /* Close ADC module */
            p_temp_adc_instance->p_api->close(p_temp_adc_instance->p_ctrl);
        }

        p_temp_adc_instance = p_extended_cfg->p_shared_cfg->p_adc_instance_second;

        if (p_temp_adc_instance != NULL)
        {
            /* Close second ADC module */
            p_temp_adc_instance->p_api->close(p_temp_adc_instance->p_ctrl);
        }

        /* Clear context array */
        uint8_t i;
        for (i = 0; i < MOTOR_DRIVER_CFG_SUPPORT_MOTOR_NUM; i++)
        {
            p_instance_ctrl->p_shared_instance_ctrl->p_context[i] = NULL;
        }

        p_instance_ctrl->p_shared_instance_ctrl->open = 0U;
        p_shared_ctrl->registered_motor_count         = 0U;
    }
    else
    {
        /* Only declease motor count */
        p_shared_ctrl->registered_motor_count--;
    }
    FSP_CRITICAL_SECTION_EXIT;
 #endif                                /* SUPPORT_SHARED_ADC == 1 */
}

#endif                                 // MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 0
