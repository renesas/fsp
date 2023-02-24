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
#include "bsp_api.h"
#include "rm_motor_sense_hall.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_SENSE_HALL_OPEN             (('M' << 24U) | ('T' << 16U) | ('S' << 8U) | ('H' << 0U))

#define     MOTOR_SENSE_HALL_TWOPI            (3.14159265358979F * 2.0F)
#define     MOTOR_SENSE_HALL_30DEGREE         (MOTOR_SENSE_HALL_TWOPI / 12.0F)
#define     MOTOR_SENSE_HALL_60DEGREE         (60.0F)
#define     MOTOR_SENSE_HALL_360DEGREE        (360.0F)

#define     MOTOR_SENSE_HALL_U_SHIFT          (2)
#define     MOTOR_SENSE_HALL_V_SHIFT          (1)

#define     MOTOR_SENSE_HALL_CALCULATE_KHZ    (1000.0F)

#ifndef MTR_SENSE_HALL_ERROR_RETURN

 #define MTR_SENSE_HALL_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void motor_sense_hall_reset(motor_sense_hall_instance_ctrl_t * p_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_angle_api_t g_motor_angle_on_motor_sense_hall =
{
    .open                  = RM_MOTOR_SENSE_HALL_Open,
    .close                 = RM_MOTOR_SENSE_HALL_Close,
    .reset                 = RM_MOTOR_SENSE_HALL_Reset,
    .currentSet            = RM_MOTOR_SENSE_HALL_CurrentSet,
    .speedSet              = RM_MOTOR_SENSE_HALL_SpeedSet,
    .flagPiCtrlSet         = RM_MOTOR_SENSE_HALL_FlagPiCtrlSet,
    .angleSpeedGet         = RM_MOTOR_SENSE_HALL_AngleSpeedGet,
    .estimatedComponentGet = RM_MOTOR_SENSE_HALL_EstimatedComponentGet,
    .parameterUpdate       = RM_MOTOR_SENSE_HALL_ParameterUpdate,
    .internalCalculate     = RM_MOTOR_SENSE_HALL_InternalCalculate,
    .angleAdjust           = RM_MOTOR_SENSE_HALL_AngleAdjust,
    .encoderCyclic         = RM_MOTOR_SENSE_HALL_EncoderCyclic,
    .infoGet               = RM_MOTOR_SENSE_HALL_InfoGet,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_SENSE_HALL
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the angle hall sensor module. Implements @ref motor_angle_api_t::open.
 *
 * @retval FSP_SUCCESS              MTR_ANGL_EST successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_Open (motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg)
{
    motor_sense_hall_instance_ctrl_t * p_instance_ctrl = (motor_sense_hall_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_HALL_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    MTR_SENSE_HALL_ERROR_RETURN(MOTOR_SENSE_HALL_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

#if (MOTOR_SENSE_HALL_CFG_PARAM_CHECKING_ENABLE)
    motor_sense_hall_extended_cfg_t * p_extended_cfg = (motor_sense_hall_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(p_extended_cfg != NULL);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    motor_sense_hall_reset(p_instance_ctrl);

    p_instance_ctrl->open = MOTOR_SENSE_HALL_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified Angle Estimation module. Implements @ref motor_angle_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_Close (motor_angle_ctrl_t * const p_ctrl)
{
    motor_sense_hall_instance_ctrl_t * p_instance_ctrl = (motor_sense_hall_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_HALL_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MTR_SENSE_HALL_ERROR_RETURN(MOTOR_SENSE_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_hall_reset(p_instance_ctrl);

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of Angle Estimation module. Implements @ref motor_angle_api_t::reset
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_Reset (motor_angle_ctrl_t * const p_ctrl)
{
    motor_sense_hall_instance_ctrl_t * p_instance_ctrl = (motor_sense_hall_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_HALL_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MTR_SENSE_HALL_ERROR_RETURN(MOTOR_SENSE_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_hall_reset(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set d/q-axis Current Data & Voltage Reference. Implements @ref motor_angle_api_t::currentSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_CurrentSet (motor_angle_ctrl_t * const              p_ctrl,
                                          motor_angle_current_t * const           p_st_current,
                                          motor_angle_voltage_reference_t * const p_st_voltage)

{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_st_current);
    FSP_PARAMETER_NOT_USED(p_st_voltage);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Set Speed Information. Implements @ref motor_angle_api_t::speedSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_SpeedSet (motor_angle_ctrl_t * const p_ctrl,
                                        float const                speed_ctrl,
                                        float const                damp_speed)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(speed_ctrl);
    FSP_PARAMETER_NOT_USED(damp_speed);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Set the flag of PI Control runs. Implements @ref motor_angle_api_t::flagPiCtrlSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_FlagPiCtrlSet (motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(flag_pi);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Gets the current rotor's angle and rotation speed. Implements @ref motor_angle_api_t::angleSpeedGet
 *
 * @retval FSP_SUCCESS              Successful data get.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Output pointer is invalid.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_AngleSpeedGet (motor_angle_ctrl_t * const p_ctrl,
                                             float * const              p_angle,
                                             float * const              p_speed,
                                             float * const              p_phase_err)
{
    motor_sense_hall_instance_ctrl_t * p_instance_ctrl = (motor_sense_hall_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_HALL_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MTR_SENSE_HALL_ERROR_RETURN(p_angle != NULL, FSP_ERR_INVALID_ARGUMENT);
    MTR_SENSE_HALL_ERROR_RETURN(p_speed != NULL, FSP_ERR_INVALID_ARGUMENT);
    MTR_SENSE_HALL_ERROR_RETURN(p_phase_err != NULL, FSP_ERR_INVALID_ARGUMENT);
    MTR_SENSE_HALL_ERROR_RETURN(MOTOR_SENSE_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_hall_extended_cfg_t * p_extended_cfg =
        (motor_sense_hall_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint32_t u4_uvw_sum    = 0U;
    uint32_t u4_temp_level = 0U;
    float    f_temp_angle  = 0.0F;
    uint8_t  i             = 0U;

    FSP_PARAMETER_NOT_USED(p_phase_err);

    /* Position aquisition (hall sensor) */
    p_instance_ctrl->u1_last_hall_signal = p_instance_ctrl->u1_hall_signal;

    u4_temp_level = R_BSP_PinRead(p_extended_cfg->port_hall_sensor_u);
    p_instance_ctrl->u1_hall_signal = (uint8_t) (u4_temp_level << MOTOR_SENSE_HALL_U_SHIFT);
    u4_temp_level = R_BSP_PinRead(p_extended_cfg->port_hall_sensor_v);
    p_instance_ctrl->u1_hall_signal |= (uint8_t) (u4_temp_level << MOTOR_SENSE_HALL_V_SHIFT);
    u4_temp_level = R_BSP_PinRead(p_extended_cfg->port_hall_sensor_w);
    p_instance_ctrl->u1_hall_signal |= (uint8_t) (u4_temp_level);

    if (0U == p_instance_ctrl->u1_last_hall_signal)
    {
        return FSP_SUCCESS;
    }

    /* Count time with limitation */
    p_instance_ctrl->u2_carrier_count++;
    if (p_instance_ctrl->u2_carrier_count > p_extended_cfg->u2_maximum_period)
    {
        p_instance_ctrl->u2_carrier_count = p_extended_cfg->u2_maximum_period;
    }

    /* Speed & angle estimation */
    /* At the boundary of hall signal change */
    if (p_instance_ctrl->u1_hall_signal != p_instance_ctrl->u1_last_hall_signal)
    {
        /* Rotation direction judge */
        p_instance_ctrl->last_direction = p_instance_ctrl->direction;

        for (i = 1; i < MOTOR_SENSE_HALL_SPEED_COUNTS + 1; i++)
        {
            if (p_instance_ctrl->u1_hall_signal == p_extended_cfg->u1_hall_pattern[i])
            {
                if (p_instance_ctrl->u1_last_hall_signal == p_extended_cfg->u1_hall_pattern[i - 1])
                {
                    p_instance_ctrl->direction = MOTOR_SENSE_HALL_DIRECTION_CW;
                }
            }
        }

        for (i = 0; i < MOTOR_SENSE_HALL_SPEED_COUNTS; i++)
        {
            if (p_instance_ctrl->u1_hall_signal == p_extended_cfg->u1_hall_pattern[i])
            {
                if (p_instance_ctrl->u1_last_hall_signal == p_extended_cfg->u1_hall_pattern[i + 1])
                {
                    p_instance_ctrl->direction = MOTOR_SENSE_HALL_DIRECTION_CCW;
                }
            }
        }

        p_instance_ctrl->u2_hall_period[p_instance_ctrl->u1_period_counter] = p_instance_ctrl->u2_carrier_count;

        p_instance_ctrl->u1_period_counter++;

        if (p_instance_ctrl->u1_period_counter >= MOTOR_SENSE_HALL_SPEED_COUNTS)
        {
            p_instance_ctrl->u1_period_counter = 0;
        }

        /* When the change of rotational direction happens */
        if (p_instance_ctrl->last_direction != p_instance_ctrl->direction)
        {
            /* Once the period is set to fix value */
            p_instance_ctrl->u2_hall_period[0] = p_extended_cfg->u2_default_counts;
            p_instance_ctrl->u2_hall_period[1] = p_extended_cfg->u2_default_counts;
            p_instance_ctrl->u2_hall_period[2] = p_extended_cfg->u2_default_counts;
            p_instance_ctrl->u2_hall_period[3] = p_extended_cfg->u2_default_counts;
            p_instance_ctrl->u2_hall_period[4] = p_extended_cfg->u2_default_counts;
            p_instance_ctrl->u2_hall_period[5] = p_extended_cfg->u2_default_counts;
        }

        u4_uvw_sum = (uint32_t) p_instance_ctrl->u2_hall_period[0] + (uint32_t) p_instance_ctrl->u2_hall_period[1] +
                     (uint32_t) p_instance_ctrl->u2_hall_period[2] + (uint32_t) p_instance_ctrl->u2_hall_period[3] +
                     (uint32_t) p_instance_ctrl->u2_hall_period[4] + (uint32_t) p_instance_ctrl->u2_hall_period[5];

        p_instance_ctrl->u2_carrier_count = 0U;

        /* Increase direction */
        if (MOTOR_SENSE_HALL_DIRECTION_CW == p_instance_ctrl->direction)
        {
            p_instance_ctrl->f_angle           = -(MOTOR_SENSE_HALL_30DEGREE);
            p_instance_ctrl->f_angle_per_count = (MOTOR_SENSE_HALL_TWOPI / (float) u4_uvw_sum);
        }
        /* Decrease direction */
        else
        {
            p_instance_ctrl->f_angle           = MOTOR_SENSE_HALL_30DEGREE;
            p_instance_ctrl->f_angle_per_count = -(MOTOR_SENSE_HALL_TWOPI / (float) u4_uvw_sum);
        }

        p_instance_ctrl->f_calculated_speed = p_instance_ctrl->f_angle_per_count *
                                              (p_extended_cfg->f_pwm_carrier_freq * MOTOR_SENSE_HALL_CALCULATE_KHZ);
    }
    /* During the same hall signal is detected */
    else
    {
        p_instance_ctrl->f_angle = p_instance_ctrl->f_angle + p_instance_ctrl->f_angle_per_count;
        if (p_instance_ctrl->f_angle > MOTOR_SENSE_HALL_30DEGREE)
        {
            p_instance_ctrl->f_angle = MOTOR_SENSE_HALL_30DEGREE;
        }
        else if (p_instance_ctrl->f_angle < -(MOTOR_SENSE_HALL_30DEGREE))
        {
            p_instance_ctrl->f_angle = -(MOTOR_SENSE_HALL_30DEGREE);
        }
        else
        {
            /* Do nothing */
        }
    }

    /* Set the angle according to hall signal */
    f_temp_angle = p_extended_cfg->f_angle_correct + p_instance_ctrl->f_angle;
    for (i = 0; i < MOTOR_SENSE_HALL_SPEED_COUNTS; i++)
    {
        if (p_instance_ctrl->u1_hall_signal == p_extended_cfg->u1_hall_pattern[i])
        {
            f_temp_angle += MOTOR_SENSE_HALL_TWOPI * (MOTOR_SENSE_HALL_60DEGREE * i) / MOTOR_SENSE_HALL_360DEGREE;
        }
    }

    /* Converted angle within 0..2PI */
    if (f_temp_angle > MOTOR_SENSE_HALL_TWOPI)
    {
        f_temp_angle = f_temp_angle - MOTOR_SENSE_HALL_TWOPI;
    }
    else if (f_temp_angle < 0.0F)
    {
        f_temp_angle = f_temp_angle + MOTOR_SENSE_HALL_TWOPI;
    }
    else
    {
        /* Do nothing */
    }

    *p_speed = p_instance_ctrl->f_calculated_speed;
    *p_angle = f_temp_angle;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Gets estimated d/q-axis component. Implements @ref motor_angle_api_t::estimatedComponentGet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_EstimatedComponentGet (motor_angle_ctrl_t * const p_ctrl,
                                                     float * const              p_ed,
                                                     float * const              p_eq)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_ed);
    FSP_PARAMETER_NOT_USED(p_eq);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of Angle&Speed Estimation. Implements @ref motor_angle_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data is update.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_ParameterUpdate (motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg)
{
    motor_sense_hall_instance_ctrl_t * p_instance_ctrl = (motor_sense_hall_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_HALL_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    MTR_SENSE_HALL_ERROR_RETURN(MOTOR_SENSE_HALL_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    motor_sense_hall_reset(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculate internal parameters. Implements @ref motor_angle_api_t::internalCalculate
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_InternalCalculate (motor_angle_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Angle Adjustment Process. Implements @ref motor_angle_api_t::angleAdjust
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_AngleAdjust (motor_angle_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Encoder Cyclic Process (Call in cyclic timer). Implements @ref motor_angle_api_t::encoderCyclic
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_EncoderCyclic (motor_angle_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Gets information of Encoder Angle Module. Implements @ref motor_angle_api_t::infoGet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_HALL_InfoGet (motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_info);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SENSE_HALL)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : motor_sense_hall_reset
 * Description   : Reset internal variables
 * Arguments     : p_ctrl - The pointer to module variables
 * Return Value  : None
 **********************************************************************************************************************/
static void motor_sense_hall_reset (motor_sense_hall_instance_ctrl_t * p_ctrl)
{
    uint8_t i;
    motor_sense_hall_extended_cfg_t * p_extended_cfg = (motor_sense_hall_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    p_ctrl->u1_hall_signal      = 0U;
    p_ctrl->u1_last_hall_signal = 0U;
    p_ctrl->direction           = MOTOR_SENSE_HALL_DIRECTION_CW;
    p_ctrl->last_direction      = MOTOR_SENSE_HALL_DIRECTION_CW;
    p_ctrl->u2_carrier_count    = 0U;
    p_ctrl->u1_period_counter   = 0U;
    p_ctrl->f_angle             = 0.0F;
    p_ctrl->f_angle_per_count   = 0.0F;
    p_ctrl->f_calculated_speed  = 0.0F;

    for (i = 0; i < MOTOR_SENSE_HALL_SPEED_COUNTS; i++)
    {
        p_ctrl->u2_hall_period[i] = p_extended_cfg->u2_default_counts;
    }
}                                      /* End of function motor_sense_hall_reset */
