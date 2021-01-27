/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "bsp_api.h"
#include "bsp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_DRIVER_OPEN                (0X4D445241L)

#define     MOTOR_DRIVER_FLG_CLR             (0)     /* For flag clear */
#define     MOTOR_DRIVER_FLG_SET             (1)     /* For flag set */

#define     MOTOR_DRIVER_MULTIPLE_2          (2.0F)  /* x2 */
#define     MOTOR_DRIVER_DEV_HALF            (0.5F)  /* 1/2 */

#define     MOTOR_DRIVER_KHZ_TRANS           (1000U) /* x1000 */

#define     MOTOR_DRIVER_DEF_HALF            (0.5F)
#define     MOTOR_DRIVER_MULTIPLE_TWO        (2.0F)

/* Select SVPWM as default method when MOD_METHOD is undefined */
#define     MOTOR_DRIVER_DEFAULT_MAX_DUTY    (1.0F)   /* Default maximum duty cycle */
#define     MOTOR_DRIVER_METHOD_SPWM         (0)      /* Sinusoidal pulse-width-modulation */
#define     MOTOR_DRIVER_METHOD_SVPWM        (1)      /* Space vector pulse-width-modulation */
#define     MOTOR_DRIVER_SATFLAG_BITU        (1 << 0) /* Saturation flag bit for U phase */
#define     MOTOR_DRIVER_SATFLAG_BITV        (1 << 1) /* Saturation flag bit for V phase */
#define     MOTOR_DRIVER_SATFLAG_BITW        (1 << 2) /* Saturation flag bit for W phase */

#ifndef MOTOR_DRIVER_METHOD
 #define MOTOR_DRIVER_METHOD                 (MOTOR_DRIVER_METHOD_SVPWM)
#endif

/*
 * Vamax in this module is calculated by the following equation
 *   SVPWM :  Vdc * (MOD_VDC_TO_VAMAX_MULT) * (Max duty - Min duty) * (MOD_SVPWM_MULT)
 *   SPWM  :  Vdc * (MOD_VDC_TO_VAMAX_MULT) * (Max duty - Min duty)
 */
#define MOTOR_DRIVER_VDC_TO_VAMAX_MULT       (0.6124F) /* The basic coefficient used to convert Vdc to Vamax */
#define MOTOR_DRIVER_SVPWM_MULT              (1.155F)  /* The usable voltage is multiplied by sqrt(4/3) when using SVPWM */

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

static void rm_motor_driver_reset(motor_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_driver_set_uvw_duty(motor_driver_instance_ctrl_t * p_ctrl,
                                         float                          f_duty_u,
                                         float                          f_duty_v,
                                         float                          f_duty_w);
static void rm_motor_driver_current_get(motor_driver_instance_ctrl_t * p_ctrl);
static void rm_motor_driver_modulation(motor_driver_instance_ctrl_t * p_ctrl);

/* Modulation functions */
static void  rm_motor_driver_mod_run(motor_driver_modulation_t * p_mod, const float * p_f4_v_in, float * p_f4_duty_out);
static void  rm_motor_driver_mod_set_max_duty(motor_driver_modulation_t * p_mod, float f4_max_duty);
static void  rm_motor_driver_mod_set_min_duty(motor_driver_modulation_t * p_mod, float f4_min_duty);
static float rm_motor_driver_mod_get_vamax(motor_driver_modulation_t * p_mod);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure. */
static const fsp_version_t g_motor_driver_version =
{
    .api_version_minor  = MOTOR_DRIVER_API_VERSION_MINOR,
    .api_version_major  = MOTOR_DRIVER_API_VERSION_MAJOR,
    .code_version_major = MOTOR_DRIVER_CODE_VERSION_MAJOR,
    .code_version_minor = MOTOR_DRIVER_CODE_VERSION_MINOR
};

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
    .versionGet           = RM_MOTOR_DRIVER_VersionGet
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
                    p_extended_cfg->u2_pwm_carrier_freq / (uint16_t) MOTOR_DRIVER_MULTIPLE_2);
    p_instance_ctrl->u2_deadtime_count =
        (uint16_t) (p_extended_cfg->u2_deadtime * p_extended_cfg->u2_pwm_timer_freq);

    rm_motor_driver_reset(p_instance_ctrl);

    p_instance_ctrl->st_modulation = p_extended_cfg->mod_param;
    rm_motor_driver_mod_set_max_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_max_duty);
    rm_motor_driver_mod_set_min_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_min_duty);

    /* Start ADC module */
    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->open(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_cfg);
        p_cfg->p_adc_instance->p_api->scanCfg(p_cfg->p_adc_instance->p_ctrl, p_cfg->p_adc_instance->p_channel_cfg);
        p_cfg->p_adc_instance->p_api->callbackSet(p_cfg->p_adc_instance->p_ctrl,
                                                  rm_motor_driver_cyclic,
                                                  p_instance_ctrl,
                                                  &(p_instance_ctrl->adc_callback_args));
        p_cfg->p_adc_instance->p_api->scanStart(p_cfg->p_adc_instance->p_ctrl);
    }

    /* Start GPT Three Phase Module */
    if (p_cfg->p_three_phase_instance != NULL)
    {
        p_cfg->p_three_phase_instance->p_api->open(p_cfg->p_three_phase_instance->p_ctrl,
                                                   p_cfg->p_three_phase_instance->p_cfg);
        rm_motor_driver_set_uvw_duty(p_instance_ctrl,
                                     p_instance_ctrl->st_modulation.f4_neutral_duty,
                                     p_instance_ctrl->st_modulation.f4_neutral_duty,
                                     p_instance_ctrl->st_modulation.f4_neutral_duty);
        p_cfg->p_three_phase_instance->p_api->start(p_cfg->p_three_phase_instance->p_ctrl);
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

    motor_driver_cfg_t * p_cfg = (motor_driver_cfg_t *) p_instance_ctrl->p_cfg;

    rm_motor_driver_reset(p_instance_ctrl);

    /* Close ADC Module */
    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->close(p_cfg->p_adc_instance->p_ctrl);
    }

    /* Close GPT Three Phase Module */
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

    p_instance_ctrl->f_refu = p_instance_ctrl->st_modulation.f4_neutral_duty;
    p_instance_ctrl->f_refv = p_instance_ctrl->st_modulation.f4_neutral_duty;
    p_instance_ctrl->f_refw = p_instance_ctrl->st_modulation.f4_neutral_duty;

    rm_motor_driver_set_uvw_duty(p_instance_ctrl,
                                 p_instance_ctrl->st_modulation.f4_neutral_duty,
                                 p_instance_ctrl->st_modulation.f4_neutral_duty,
                                 p_instance_ctrl->st_modulation.f4_neutral_duty);
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

    p_current_get->iu     = p_instance_ctrl->f_iu_ad - p_instance_ctrl->f_offset_iu;
    p_current_get->iw     = p_instance_ctrl->f_iw_ad - p_instance_ctrl->f_offset_iw;
    p_current_get->vdc    = p_instance_ctrl->f_vdc_ad;
    p_current_get->va_max = rm_motor_driver_mod_get_vamax(&(p_instance_ctrl->st_modulation));

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

    /* Measure Current A/D Offset */
    if (MOTOR_DRIVER_FLG_CLR == p_instance_ctrl->u1_flag_offset_calc)
    {
        /* Output Neautral PWM */
        rm_motor_driver_set_uvw_duty(p_instance_ctrl,
                                     p_instance_ctrl->st_modulation.f4_neutral_duty,
                                     p_instance_ctrl->st_modulation.f4_neutral_duty,
                                     p_instance_ctrl->st_modulation.f4_neutral_duty);

        u2_temp_offset_count = p_extended_cfg->u2_offset_calc_count;
        if (MOTOR_DRIVER_FLG_CLR == p_instance_ctrl->u1_flag_offset_calc)
        {
            if (p_instance_ctrl->u2_offset_calc_times < u2_temp_offset_count)
            {
                p_instance_ctrl->f_sum_iu_ad += p_instance_ctrl->f_iu_ad;
                p_instance_ctrl->f_sum_iw_ad += p_instance_ctrl->f_iw_ad;
                p_instance_ctrl->u2_offset_calc_times++;
            }
            else
            {
                p_instance_ctrl->f_offset_iu = p_instance_ctrl->f_sum_iu_ad /
                                               u2_temp_offset_count;
                p_instance_ctrl->f_offset_iw = p_instance_ctrl->f_sum_iw_ad /
                                               u2_temp_offset_count;
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
                    p_extended_cfg->u2_pwm_carrier_freq / (uint16_t) MOTOR_DRIVER_MULTIPLE_2);
    p_instance_ctrl->u2_deadtime_count =
        (uint16_t) (p_extended_cfg->u2_deadtime * p_extended_cfg->u2_pwm_timer_freq);

    p_instance_ctrl->st_modulation = p_extended_cfg->mod_param;
    rm_motor_driver_mod_set_max_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_max_duty);
    rm_motor_driver_mod_set_min_duty(&(p_instance_ctrl->st_modulation), p_extended_cfg->mod_param.f4_min_duty);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * DEPRECATED Return Motor Driver Module version. Implements @ref motor_driver_api_t::versionGet.
 *
 * @retval      FSP_SUCCESS             Version information successfully read.
 * @retval      FSP_ERR_ASSERTION       Null pointer passed as a parameter
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_DRIVER_VersionGet (fsp_version_t * const p_version)
{
#if MOTOR_DRIVER_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_motor_driver_version.version_id;

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
    p_ctrl->f_iw_ad  = 0.0F;
    p_ctrl->f_vdc_ad = 0.0F;
    p_ctrl->f_refu   = 0.0F;
    p_ctrl->f_refv   = 0.0F;
    p_ctrl->f_refw   = 0.0F;

    p_ctrl->u1_flag_offset_calc  = MOTOR_DRIVER_FLG_CLR;
    p_ctrl->u2_offset_calc_times = 0U;
    p_ctrl->f_offset_iu          = 0.0F;
    p_ctrl->f_offset_iw          = 0.0F;
    p_ctrl->f_sum_iu_ad          = 0.0F;
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

    u2_count_u = (uint16_t) ((u2_temp_base * (1.0F - f_duty_u)) + (u2_temp_deadt * MOTOR_DRIVER_DEV_HALF));
    u2_count_v = (uint16_t) ((u2_temp_base * (1.0F - f_duty_v)) + (u2_temp_deadt * MOTOR_DRIVER_DEV_HALF));
    u2_count_w = (uint16_t) ((u2_temp_base * (1.0F - f_duty_w)) + (u2_temp_deadt * MOTOR_DRIVER_DEV_HALF));

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
    uint16_t u2_addata[3]                      = {0U};
    float    f_addata[2]                       = {0.0F};
    motor_driver_cfg_t const    * p_cfg        = p_ctrl->p_cfg;
    motor_driver_extended_cfg_t * p_extend_cfg = (motor_driver_extended_cfg_t *) p_cfg->p_extend;

    /* Read A/D converted data */
    if (p_cfg->p_adc_instance != NULL)
    {
        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->iu_ad_ch, &u2_addata[0]);
        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->iw_ad_ch, &u2_addata[1]);
        p_cfg->p_adc_instance->p_api->read(p_cfg->p_adc_instance->p_ctrl, p_cfg->vdc_ad_ch, &u2_addata[2]);
    }

    f_addata[0] = (float) u2_addata[0];
    f_addata[1] = (float) u2_addata[1];
    f_addata[0] = f_addata[0] - p_extend_cfg->f_ad_current_offset;
    f_addata[1] = f_addata[1] - p_extend_cfg->f_ad_current_offset;

    p_ctrl->f_iu_ad = -(f_addata[0]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);
    p_ctrl->f_iw_ad = -(f_addata[1]) * (p_extend_cfg->f_current_range / p_extend_cfg->f_ad_resolution);

    p_ctrl->f_vdc_ad = (float) u2_addata[2] * (p_extend_cfg->f_vdc_range / p_extend_cfg->f_ad_resolution) *
                       p_extend_cfg->f_ad_voltage_conversion;
}                                      /* End of function rm_motor_driver_current_get */

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

    rm_motor_driver_mod_run(&(p_ctrl->st_modulation), &(f_v_in[0]), &(f_mod_out[0]));

    rm_motor_driver_set_uvw_duty(p_ctrl, f_mod_out[0], f_mod_out[1], f_mod_out[2]);
}                                      /* End of function rm_motor_driver_modulation */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_svpwm
 * Description  : Space vector modulation
 * Arguments    : p_f4_v_in -
 *                    Input data, in an array [Vu,Vv,Vw]
 *                p_f4_v_out -
 *                    Where to store output data, in an array [Vu,Vv,Vw]
 * Return Value : None
 ***********************************************************************************************************************/
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
 ***********************************************************************************************************************/
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
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *              : p_f4_v_in -
 *                    Pointer to the 3-phase input voltage
 *              : p_f4_duty_out -
 *                    Where to store the 3-phase output duty cycle
 * Return Value : None
 ***********************************************************************************************************************/
static void rm_motor_driver_mod_run (motor_driver_modulation_t * p_mod, const float * p_f4_v_in, float * p_f4_duty_out)
{
    float f4_v_out[3];

    if ((0 == p_mod) || (0 == p_f4_duty_out))
    {
        return;
    }

#if (MOTOR_DRIVER_METHOD == MOTOR_DRIVER_METHOD_SVPWM)
    rm_motor_driver_mod_svpwm(p_f4_v_in, f4_v_out);
#else
    f4_v_out[0] = p_f4_v_in[0];
    f4_v_out[1] = p_f4_v_in[1];
    f4_v_out[2] = p_f4_v_in[2];
#endif

    p_f4_duty_out[0] = (f4_v_out[0] * p_mod->f4_1_div_vdc) + p_mod->f4_neutral_duty;
    p_f4_duty_out[1] = (f4_v_out[1] * p_mod->f4_1_div_vdc) + p_mod->f4_neutral_duty;
    p_f4_duty_out[2] = (f4_v_out[2] * p_mod->f4_1_div_vdc) + p_mod->f4_neutral_duty;

    rm_motor_driver_mod_limit(p_mod, p_f4_duty_out);
}                                      /* End of function rm_motor_driver_mod_run() */

/***********************************************************************************************************************
 * Function Name: rm_motor_driver_mod_set_max_duty
 * Description  : Sets the maximum duty cycle
 * Arguments    : p_mod -
 *                    Pointer to the modulation data structure
 *                f4_max_duty -
 *                    Maximum duty cycle to set
 * Return Value : None
 ***********************************************************************************************************************/
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
 ***********************************************************************************************************************/
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
 ***********************************************************************************************************************/
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
 ***********************************************************************************************************************/
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

    /* Get A/D converted data (Phase Current & Main Line Voltage) */
    rm_motor_driver_current_get(p_instance);

    /* Invoke the callback function if it is set. */
    if (NULL != p_instance->p_cfg->p_callback)
    {
        temp_args_t.event     = MOTOR_DRIVER_EVENT_FORWARD;
        temp_args_t.p_context = p_instance->p_cfg->p_context;
        (p_instance->p_cfg->p_callback)(&temp_args_t);
    }

    /* Perform Current Control Process (if set) */
    if (NULL != p_instance->p_cfg->p_callback)
    {
        temp_args_t.event     = MOTOR_DRIVER_EVENT_CURRENT;
        temp_args_t.p_context = p_instance->p_cfg->p_context;
        (p_instance->p_cfg->p_callback)(&temp_args_t);
    }

    /* PWM Modulation */
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
