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
#include "rm_motor_driver.h"
#include "r_gpt.h"

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)
 #include "r_adc_b.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_DRIVER_OPEN                   (0X4D445241L)

#define     MOTOR_DRIVER_FLG_CLR                (0)     /* For flag clear */
#define     MOTOR_DRIVER_FLG_SET                (1)     /* For flag set */

#define     MOTOR_DRIVER_KHZ_TRANS              (1000U) /* x1000 */

#define     MOTOR_DRIVER_DEF_HALF               (0.5F)
#define     MOTOR_DRIVER_MULTIPLE_TWO           (2.0F)

#define     MOTOR_DRIVER_ADC_DATA_MASK          (0x00000FFF)

/* Select SVPWM as default method when MOD_METHOD is undefined */
#define     MOTOR_DRIVER_METHOD_SPWM            (0)      /* Sinusoidal pulse-width-modulation */
#define     MOTOR_DRIVER_METHOD_SVPWM           (1)      /* Space vector pulse-width-modulation */
#define     MOTOR_DRIVER_SATFLAG_BITU           (1 << 0) /* Saturation flag bit for U phase */
#define     MOTOR_DRIVER_SATFLAG_BITV           (1 << 1) /* Saturation flag bit for V phase */
#define     MOTOR_DRIVER_SATFLAG_BITW           (1 << 2) /* Saturation flag bit for W phase */

#ifndef MOTOR_DRIVER_METHOD
 #define MOTOR_DRIVER_METHOD                    (MOTOR_DRIVER_METHOD_SPWM)
#endif

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
static float rm_motor_driver_mod_get_vamax(motor_driver_modulation_t * p_mod);

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
                    p_extended_cfg->u2_pwm_carrier_freq / (uint16_t) MOTOR_DRIVER_MULTIPLE_TWO);
    p_instance_ctrl->u2_deadtime_count =
        (uint16_t) (p_extended_cfg->u2_deadtime * p_extended_cfg->u2_pwm_timer_freq);

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
        p_u_phase_gpt        = p_three_phase->p_cfg->p_timer_instance[0];
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
            p_cfg->p_three_phase_instance->p_cfg->p_timer_instance[0]->p_api->callbackSet(
                p_cfg->p_three_phase_instance->p_cfg->p_timer_instance[0]->p_ctrl,
                rm_motor_driver_1shunt_cyclic,
                p_instance_ctrl,
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
    /* For 1shunt, Vdc is need to read by ADC module #1. */
    if (MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT == p_cfg->shunt)
    {
#if (BSP_FEATURE_ADC_UNIT_1_CHANNELS != 0)
        if (p_cfg->p_adc2_instance != NULL)
        {
            p_cfg->p_adc2_instance->p_api->open(p_cfg->p_adc2_instance->p_ctrl, p_cfg->p_adc2_instance->p_cfg);
            p_cfg->p_adc2_instance->p_api->scanCfg(p_cfg->p_adc2_instance->p_ctrl,
                                                   p_cfg->p_adc2_instance->p_channel_cfg);
        }
#endif
    }

    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->open(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg);
        p_cfg->p_adc_instance->p_api->scanCfg(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_channel_cfg);
        p_cfg->p_adc_instance->p_api->calibrate(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg->p_extend);

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 1)
        adc_status_t status = {.state = ADC_STATE_SCAN_IN_PROGRESS};
        while (ADC_STATE_SCAN_IN_PROGRESS == status.state)
        {
            p_cfg->p_adc_instance->p_api->scanStatusGet(p_cfg->p_adc_instance->p_ctrl, &status);
        }
#endif

        if (p_cfg->shunt != MOTOR_DRIVER_SHUNT_TYPE_1_SHUNT)
        {
            p_cfg->p_adc_instance->p_api->callbackSet(p_cfg->p_adc_instance->p_ctrl,
                                                      rm_motor_driver_cyclic,
                                                      p_instance_ctrl,
                                                      &(p_instance_ctrl->adc_callback_args));
        }

        p_cfg->p_adc_instance->p_api->scanStart(p_cfg->p_adc_instance->p_ctrl);
    }

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
    p_current_get->va_max = rm_motor_driver_mod_get_vamax(&(p_instance_ctrl->st_modulation));

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
                    p_extended_cfg->u2_pwm_carrier_freq / (uint16_t) MOTOR_DRIVER_MULTIPLE_TWO);
    p_instance_ctrl->u2_deadtime_count =
        (uint16_t) (p_extended_cfg->u2_deadtime * p_extended_cfg->u2_pwm_timer_freq);

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

    /* Read A/D converted data */
    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->iu_ad_ch, &u2_addata[0]);
        if (MOTOR_DRIVER_SHUNT_TYPE_3_SHUNT == p_cfg->shunt)
        {
            p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->iv_ad_ch, &u2_addata[1]);
        }
        else
        {
            u2_addata[1] = 0U;
        }

        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->iw_ad_ch, &u2_addata[2]);
        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[3]);

        /* For induction sensor */
        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->sin_ad_ch, &u2_addata[4]);
        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->cos_ad_ch, &u2_addata[5]);
    }

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

#if (MOTOR_DRIVER_CFG_ADC_B_SUPPORTED == 0)
    adc_status_t temp_adc_status;

    /* Get double buffer data */
    p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, ADC_CHANNEL_DUPLEX_A, &u2_Iac_raw0);
    p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, ADC_CHANNEL_DUPLEX_B, &u2_Iac_raw1);

    /* Not using ADC_B module */
    /* Read A/D converted data */
    if (p_cfg->p_adc2_instance != NULL)
    {
 #if (BSP_FEATURE_ADC_UNIT_1_CHANNELS == 0)
        p_cfg->p_adc_instance->p_api->close(p_cfg->p_adc_instance->p_ctrl);
        p_cfg->p_adc2_instance->p_api->open(p_cfg->p_adc2_instance->p_ctrl, p_cfg->p_adc2_instance->p_cfg);
        p_cfg->p_adc2_instance->p_api->scanCfg(p_cfg->p_adc2_instance->p_ctrl, p_cfg->p_adc2_instance->p_channel_cfg);
 #endif
        p_cfg->p_adc2_instance->p_api->scanStart(p_cfg->p_adc2_instance->p_ctrl);
        p_cfg->p_adc2_instance->p_api->scanStatusGet(p_cfg->p_adc2_instance->p_ctrl, &temp_adc_status);
        while (ADC_STATE_SCAN_IN_PROGRESS == temp_adc_status.state)
        {
            /* wait A/D conversion finish */
            p_cfg->p_adc2_instance->p_api->scanStatusGet(p_cfg->p_adc2_instance->p_ctrl, &temp_adc_status);
        }

        p_cfg->p_adc2_instance->p_api->read(p_cfg->p_adc2_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[0]);
 #if (BSP_FEATURE_ADC_UNIT_1_CHANNELS == 0)
        p_cfg->p_adc2_instance->p_api->close(p_cfg->p_adc2_instance->p_ctrl);
        p_cfg->p_adc_instance->p_api->open(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg);
        p_cfg->p_adc_instance->p_api->scanCfg(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_channel_cfg);
        p_cfg->p_adc_instance->p_api->calibrate(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg->p_extend);
        p_cfg->p_adc_instance->p_api->scanStart(p_cfg->p_adc_instance->p_ctrl);
 #endif
    }

#else
    adc_b_fifo_read_t temp_fifo;

    /* Using ADC_B module */
    /* Get Vdc */
    p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[0]);

    /* Get induction sensor output */
    p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->sin_ad_ch, &u2_addata[1]);
    p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->cos_ad_ch, &u2_addata[2]);

    /* Get FIFO data */
    R_ADC_B_FifoRead(p_cfg->p_adc_instance->p_ctrl, ADC_GROUP_MASK_0, &temp_fifo);
    temp_fifo.fifo_data[0].data &= MOTOR_DRIVER_ADC_DATA_MASK;
    u2_Iac_raw0                  = (uint16_t) temp_fifo.fifo_data[0].data;
    temp_fifo.fifo_data[1].data &= MOTOR_DRIVER_ADC_DATA_MASK;
    u2_Iac_raw1                  = (uint16_t) temp_fifo.fifo_data[1].data;
#endif

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
    timer_instance_t const       * timer_u        = p_three_phase->p_cfg->p_timer_instance[0];
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
 * Return Value : Voltage multiplier
 **********************************************************************************************************************/
static float rm_motor_driver_mod_get_voltage_multiplier (motor_driver_modulation_t * p_mod)
{
    float f4_usable_duty_cycle;

    f4_usable_duty_cycle = (p_mod->f4_max_duty - p_mod->f4_min_duty) -
                           (MOTOR_DRIVER_MULTIPLE_TWO * p_mod->f4_voltage_error_ratio);

#if (MOTOR_DRIVER_METHOD == MOTOR_DRIVER_METHOD_SVPWM)
    f4_usable_duty_cycle = f4_usable_duty_cycle * MOTOR_DRIVER_SVPWM_MULT;
#endif

    return f4_usable_duty_cycle;
}                                      /* End of function rm_motor_driver_mod_get_voltage_multiplier */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_get_vamax
 * Description  : Gets the maximum magnitude of voltage vector
 * Arguments    : p_mod -
 *                    The pointer to the modulation data structure
 * Return Value : The maximum magnitude of voltage vector
 **********************************************************************************************************************/
static float rm_motor_driver_mod_get_vamax (motor_driver_modulation_t * p_mod)
{
    return (MOTOR_DRIVER_VDC_TO_VAMAX_MULT * p_mod->f4_vdc) * rm_motor_driver_mod_get_voltage_multiplier(p_mod);
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
