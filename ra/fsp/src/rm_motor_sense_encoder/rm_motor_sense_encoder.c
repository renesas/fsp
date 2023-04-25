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
#include "rm_motor_sense_encoder.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define  MOTOR_SENSE_ENCODER_OPEN       (0X4D545345)

#define  MOTOR_SENSE_ENCODER_QUARTER    (0.25F)

#ifndef MOTOR_SENSE_ENCODER_ERROR_RETURN

 #define MOTOR_SENSE_ENCODER_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

#define MOTOR_SENSE_ENCODER_FLAG_CLEAR              (0U)
#define MOTOR_SENSE_ENCODER_FLAG_SET                (1U)

#define MOTOR_SENSE_ENCODER_CW                      (0)
#define MOTOR_SENSE_ENCODER_CCW                     (1)

#define MOTOR_SENSE_ENCODER_TWOPI                   (3.14159265358979F * 2.0F)

#define MOTOR_SENSE_ENCODER_16BIT                   (0x10000U)

/* position and speed calculation mode */
#define MOTOR_SENSE_ENCODER_ENCD_INTERRUPT          (0)
#define MOTOR_SENSE_ENCODER_CTRL_INTERRUPT          (1)

/* encoder const definition */
#define MOTOR_SENSE_ENCODER_CALCULATE_KHz           (1000.0F)
#define MOTOR_SENSE_ENCODER_CALCULATE_60            (60.0F)

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL

/* For HALL Use */
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_CW           (1)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_CCW          (0)

 #define MOTOR_SENSE_ENCODER_HALL_FLAG_SET          (1)
 #define MOTOR_SENSE_ENCODER_HALL_FLAG_CLEAR        (0)

 #define MOTOR_SENSE_ENCODER_HALL_TWOPI             (2.0F * 3.14159265359F)                   /* 2 * PI */
 #define MOTOR_SENSE_ENCODER_HALL_TWOPI_360         (MOTOR_SENSE_ENCODER_HALL_TWOPI / 360.0F) /* 2 * PI / 360 */

 #define MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_30     (30.0F * MOTOR_SENSE_ENCODER_HALL_TWOPI_360)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_90     (90.0F * MOTOR_SENSE_ENCODER_HALL_TWOPI_360)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_150    (150.0F * MOTOR_SENSE_ENCODER_HALL_TWOPI_360)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_210    (210.0F * MOTOR_SENSE_ENCODER_HALL_TWOPI_360)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_270    (270.0F * MOTOR_SENSE_ENCODER_HALL_TWOPI_360)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_330    (330.0F * MOTOR_SENSE_ENCODER_HALL_TWOPI_360)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_OFFSET       (30.0F * MOTOR_SENSE_ENCODER_HALL_TWOPI_360)
 #define MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR        (1)

#endif                                 /* MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_cyclic(motor_sense_encoder_instance_ctrl_t * p_instance_ctrl);
void        rm_motor_sense_encoder_interrupt(timer_callback_args_t * p_args);

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
void rm_motor_sense_encoder_hall_angle_interrupt(external_irq_callback_args_t * p_args);

#endif

static void rm_motor_sense_encoder_init(motor_sense_encoder_parameter_t * p_encoder,
                                        motor_sense_encoder_config_t    * c_config);
static void rm_motor_sense_encoder_reset(motor_sense_encoder_parameter_t * p_encoder);
static void rm_motor_sense_encoder_highspeed_init(motor_sense_encoder_highspeed_t    * p_ehighspeed,
                                                  motor_sense_encoder_extended_cfg_t * p_extended_cfg);
static void rm_motor_sense_encoder_highspeed_reset(motor_sense_encoder_highspeed_t * p_ehighspeed);
static void rm_motor_sense_encoder_reset_count(motor_sense_encoder_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_encoder_angle_adjust_excite(motor_sense_encoder_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_encoder_calculate_count_difference(motor_sense_encoder_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_encoder_highspeed_calculate(motor_sense_encoder_instance_ctrl_t * p_ctrl,
                                                       float                                 f4_position_err,
                                                       float                                 f4_ctrl_period);
static void rm_motor_sense_encoder_switch_encoder_interrupt(motor_sense_encoder_instance_ctrl_t * p_ctrl,
                                                            float                                 f4_speed_rad);
static void rm_motor_sense_encoder_switch_carrier_interrupt(motor_sense_encoder_instance_ctrl_t * p_ctrl,
                                                            float                                 f4_speed_rad);

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
static void  rm_motor_sense_encoder_hall_init(motor_sense_encoder_hall_t * p_hall);
static float rm_motor_sense_encoder_hall_angle_adj_init(motor_sense_encoder_instance_ctrl_t * p_ctrl);
static float rm_motor_sense_encoder_hall_angle_edge_set(uint8_t u1_hall_signal, uint8_t u1_pre_hall_signal);
static float rm_motor_sense_encoder_hall_angle_set(uint8_t u1_hall_signal);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_angle_api_t g_motor_angle_on_motor_encoder =
{
    .open                  = RM_MOTOR_SENSE_ENCODER_Open,
    .close                 = RM_MOTOR_SENSE_ENCODER_Close,
    .reset                 = RM_MOTOR_SENSE_ENCODER_Reset,
    .internalCalculate     = RM_MOTOR_SENSE_ENCODER_InternalCalculate,
    .angleSpeedGet         = RM_MOTOR_SENSE_ENCODER_AngleSpeedGet,
    .angleAdjust           = RM_MOTOR_SENSE_ENCODER_AngleAdjust,
    .encoderCyclic         = RM_MOTOR_SENSE_ENCODER_EncoderCyclic,
    .cyclicProcess         = RM_MOTOR_SENSE_ENCODER_CyclicProcess,
    .infoGet               = RM_MOTOR_SENSE_ENCODER_InfoGet,
    .parameterUpdate       = RM_MOTOR_SENSE_ENCODER_ParameterUpdate,
    .currentSet            = RM_MOTOR_SENSE_ENCODER_CurrentSet,
    .speedSet              = RM_MOTOR_SENSE_ENCODER_SpeedSet,
    .flagPiCtrlSet         = RM_MOTOR_SENSE_ENCODER_FlagPiCtrlSet,
    .estimatedComponentGet = RM_MOTOR_SENSE_ENCODER_EstimatedComponentGet,
    .sensorDataSet         = RM_MOTOR_SENSE_ENCODER_SensorDataSet,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_SENSE_ENCODER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the Angle Encoder module. Implements @ref motor_angle_api_t::open.
 *
 * @retval FSP_SUCCESS              Angle Encoder module successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Configuration parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_Open (motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
#endif
    motor_sense_encoder_extended_cfg_t * p_extended_cfg =
        (motor_sense_encoder_extended_cfg_t *) p_cfg->p_extend;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_extended_cfg != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(0.0F <= p_extended_cfg->f_current_ctrl_period, FSP_ERR_INVALID_ARGUMENT);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(0.0F <= p_extended_cfg->f_speed_ctrl_period, FSP_ERR_INVALID_ARGUMENT);
#endif

    rm_motor_sense_encoder_init(&(p_instance_ctrl->st_encoder_parameter), &(p_extended_cfg->encoder_config));
    rm_motor_sense_encoder_highspeed_init(&(p_instance_ctrl->st_encoder_highspeed), p_extended_cfg);

    /* Set used instances */
    if (p_extended_cfg->p_timer_instance != NULL)
    {
        p_extended_cfg->p_timer_instance->p_api->open(p_extended_cfg->p_timer_instance->p_ctrl,
                                                      p_extended_cfg->p_timer_instance->p_cfg);
        p_instance_ctrl->p_timer = p_extended_cfg->p_timer_instance;
    }

    if (p_extended_cfg->p_input_capture_instance != NULL)
    {
        p_extended_cfg->p_input_capture_instance->p_api->open(p_extended_cfg->p_input_capture_instance->p_ctrl,
                                                              p_extended_cfg->p_input_capture_instance->p_cfg);
        p_extended_cfg->p_input_capture_instance->p_api->enable(p_extended_cfg->p_input_capture_instance->p_ctrl);
        p_extended_cfg->p_input_capture_instance->p_api->start(p_extended_cfg->p_input_capture_instance->p_ctrl);

        p_instance_ctrl->p_input_capture = p_extended_cfg->p_input_capture_instance;
    }

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
    if ((p_extended_cfg->p_u_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_v_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_w_hall_irq_instance != NULL))
    {
        if (MOTOR_SENSE_ENCODER_USE_HALL == p_extended_cfg->use_hall)
        {
            p_extended_cfg->p_u_hall_irq_instance->p_api->open(p_extended_cfg->p_u_hall_irq_instance->p_ctrl,
                                                               p_extended_cfg->p_u_hall_irq_instance->p_cfg);
            p_extended_cfg->p_v_hall_irq_instance->p_api->open(p_extended_cfg->p_v_hall_irq_instance->p_ctrl,
                                                               p_extended_cfg->p_v_hall_irq_instance->p_cfg);
            p_extended_cfg->p_w_hall_irq_instance->p_api->open(p_extended_cfg->p_w_hall_irq_instance->p_ctrl,
                                                               p_extended_cfg->p_w_hall_irq_instance->p_cfg);

            p_extended_cfg->p_u_hall_irq_instance->p_api->callbackSet(p_extended_cfg->p_u_hall_irq_instance->p_ctrl,
                                                                      rm_motor_sense_encoder_hall_angle_interrupt,
                                                                      p_instance_ctrl,
                                                                      &(p_instance_ctrl->hall_interrupt_args));
            p_extended_cfg->p_v_hall_irq_instance->p_api->callbackSet(p_extended_cfg->p_v_hall_irq_instance->p_ctrl,
                                                                      rm_motor_sense_encoder_hall_angle_interrupt,
                                                                      p_instance_ctrl,
                                                                      &(p_instance_ctrl->hall_interrupt_args));
            p_extended_cfg->p_w_hall_irq_instance->p_api->callbackSet(p_extended_cfg->p_w_hall_irq_instance->p_ctrl,
                                                                      rm_motor_sense_encoder_hall_angle_interrupt,
                                                                      p_instance_ctrl,
                                                                      &(p_instance_ctrl->hall_interrupt_args));

            rm_motor_sense_encoder_hall_init(&(p_instance_ctrl->st_encoder_hall));
        }
    }
#endif

    p_instance_ctrl->f_speed_rad = 0.0F;
    p_instance_ctrl->e_loop_mode = p_extended_cfg->loop_mode;

    p_instance_ctrl->p_cfg        = p_cfg;
    p_instance_ctrl->u1_direction = MOTOR_SENSE_ENCODER_CW;

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_SENSE_ENCODER_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Disables specified Angle Encoder module. Implements @ref motor_angle_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_Close (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_angle_cfg_t * p_cfg = (motor_angle_cfg_t *) p_instance_ctrl->p_cfg;
    motor_sense_encoder_extended_cfg_t * p_extended_cfg =
        (motor_sense_encoder_extended_cfg_t *) p_cfg->p_extend;

    rm_motor_sense_encoder_reset(&(p_instance_ctrl->st_encoder_parameter));
    rm_motor_sense_encoder_highspeed_reset(&(p_instance_ctrl->st_encoder_highspeed));

    if (p_extended_cfg->p_timer_instance != NULL)
    {
        p_extended_cfg->p_timer_instance->p_api->close(p_extended_cfg->p_timer_instance->p_ctrl);
    }

    if (p_extended_cfg->p_input_capture_instance != NULL)
    {
        p_extended_cfg->p_input_capture_instance->p_api->close(p_extended_cfg->p_input_capture_instance->p_ctrl);
    }

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
    if ((p_extended_cfg->p_u_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_v_hall_irq_instance != NULL) &&
        (p_extended_cfg->p_w_hall_irq_instance != NULL))
    {
        if (MOTOR_SENSE_ENCODER_USE_HALL == p_extended_cfg->use_hall)
        {
            p_extended_cfg->p_u_hall_irq_instance->p_api->close(p_extended_cfg->p_u_hall_irq_instance->p_ctrl);
            p_extended_cfg->p_v_hall_irq_instance->p_api->close(p_extended_cfg->p_v_hall_irq_instance->p_ctrl);
            p_extended_cfg->p_w_hall_irq_instance->p_api->close(p_extended_cfg->p_w_hall_irq_instance->p_ctrl);
        }
    }
#endif

    p_instance_ctrl->f_speed_rad = 0.0F;
    p_instance_ctrl->open        = 0U;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of Angle Encoder module. Implements @ref motor_angle_api_t::reset
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_Reset (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_encoder_extended_cfg_t const * p_extend = p_instance_ctrl->p_cfg->p_extend;
    gpt_extended_cfg_t * p_gpt_exntend = (gpt_extended_cfg_t *) p_extend->p_input_capture_instance->p_cfg->p_extend;

    rm_motor_sense_encoder_reset(&(p_instance_ctrl->st_encoder_parameter));
    rm_motor_sense_encoder_highspeed_reset(&(p_instance_ctrl->st_encoder_highspeed));
    R_BSP_IrqEnable(p_gpt_exntend->capture_a_irq);

    rm_motor_sense_encoder_reset_count(p_instance_ctrl);

    p_instance_ctrl->f_speed_rad = 0.0F;

    p_instance_ctrl->u1_direction = MOTOR_SENSE_ENCODER_CW;

    if (p_instance_ctrl->p_timer != NULL)
    {
        p_instance_ctrl->p_timer->p_api->stop(p_instance_ctrl->p_timer->p_ctrl);
        p_instance_ctrl->p_timer->p_api->reset(p_instance_ctrl->p_timer->p_ctrl);
    }

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
    rm_motor_sense_encoder_hall_init(&(p_instance_ctrl->st_encoder_hall));
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @brief Calculate internal parameters. Implements @ref motor_angle_api_t::internalCalculate
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_InternalCalculate (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;
    float f4_temp         = 0.0F;
    float f4_temp_pos_err = 0.0F;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    motor_sense_encoder_extended_cfg_t * p_extended_cfg =
        (motor_sense_encoder_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Decide direction */
    p_instance_ctrl->u1_direction = MOTOR_SENSE_ENCODER_CW;
    if (p_instance_ctrl->f_speed_rad < 0)
    {
        p_instance_ctrl->u1_direction = MOTOR_SENSE_ENCODER_CCW;
    }

    if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH == p_instance_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status)
    {
        /* Angle & speed calculation */
        /* Integrate encoder counter difference */
        rm_motor_sense_encoder_calculate_count_difference(p_instance_ctrl);

        /* At Speed Mode */
        if (MOTOR_SENSE_ENCODER_LOOP_SPEED == p_instance_ctrl->e_loop_mode)
        {
            /* Limit count value to counts of one rotation */
            if (p_instance_ctrl->st_encoder_highspeed.s4_encoder_highspeed_angle_count >=
                (int32_t) (p_instance_ctrl->st_encoder_parameter.s2_encoder_cpr))
            {
                p_instance_ctrl->st_encoder_highspeed.s4_encoder_highspeed_angle_count -=
                    (int32_t) (p_instance_ctrl->st_encoder_parameter.s2_encoder_cpr);
                f4_temp_pos_err += MOTOR_SENSE_ENCODER_TWOPI;
            }
            else if (p_instance_ctrl->st_encoder_highspeed.s4_encoder_highspeed_angle_count < 0)
            {
                p_instance_ctrl->st_encoder_highspeed.s4_encoder_highspeed_angle_count +=
                    (int32_t) (p_instance_ctrl->st_encoder_parameter.s2_encoder_cpr);
                f4_temp_pos_err -= MOTOR_SENSE_ENCODER_TWOPI;
            }
            else
            {
                /* Do Nothing */
            }
        }

        /* Calculate angle (mechanical) */
        f4_temp = MOTOR_SENSE_ENCODER_TWOPI *
                  (float) p_instance_ctrl->st_encoder_highspeed.s4_encoder_highspeed_angle_count;
        p_instance_ctrl->st_encoder_highspeed.f4_encoder_highspeed_position_rad =
            f4_temp * p_instance_ctrl->st_encoder_parameter.f4_encoder_cpr_inverse;

        /* Speed calculation */
        f4_temp_pos_err +=
            p_instance_ctrl->st_encoder_highspeed.f4_encoder_highspeed_position_rad -
            p_instance_ctrl->st_encoder_highspeed.f4_encoder_highspeed_previous_rad;
        rm_motor_sense_encoder_highspeed_calculate(p_instance_ctrl,
                                                   f4_temp_pos_err,
                                                   p_extended_cfg->f_current_ctrl_period);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets the current rotor's angle and rotation speed. Implements @ref motor_angle_api_t::angleSpeedGet
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_AngleSpeedGet (motor_angle_ctrl_t * const p_ctrl,
                                                float * const              p_angle,
                                                float * const              p_speed,
                                                float * const              p_phase_err)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;
    float  f4_temp_speed = 0.0F;
    float  f4_angle_rad  = 0.0F;
    double d_temp        = 0.0F;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_angle);
    FSP_ASSERT(p_speed);
    FSP_ASSERT(p_phase_err);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_encoder_extended_cfg_t * p_extended_cfg =
        (motor_sense_encoder_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH !=
        p_instance_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status)
    {
#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
        if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_HALL == p_instance_ctrl->e_adjust_mode)
        {
            f4_angle_rad = p_instance_ctrl->st_encoder_hall.f4_hall_angle_rad;
        }
        else
#endif
        {
            /* Speed must be zero while adjusting angle */
            p_instance_ctrl->st_encoder_parameter.f4_encoder_speed_rad = 0.0F;

            if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE ==
                p_instance_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status)
            {
                /* Set alignment angle to Pi/2[rad] */
                f4_angle_rad = MOTOR_SENSE_ENCODER_TWOPI * MOTOR_SENSE_ENCODER_QUARTER;
            }
        }
    }
    else
    {
        if (MOTOR_SENSE_ENCODER_CTRL_INTERRUPT ==
            p_instance_ctrl->st_encoder_highspeed.u1_encoder_position_speed_calc_mode)
        {
            f4_temp_speed = p_instance_ctrl->st_encoder_highspeed.f4_encoder_highspeed_speed_rad *
                            p_extended_cfg->st_motor_params.u2_mtr_pp;
            *p_speed = f4_temp_speed;
            p_instance_ctrl->f_speed_rad = f4_temp_speed;

            /* Position Radian */
            *p_phase_err = p_instance_ctrl->st_encoder_highspeed.f4_encoder_highspeed_position_rad;

            rm_motor_sense_encoder_switch_encoder_interrupt(p_instance_ctrl, f4_temp_speed);
        }
        else if (MOTOR_SENSE_ENCODER_ENCD_INTERRUPT ==
                 p_instance_ctrl->st_encoder_highspeed.u1_encoder_position_speed_calc_mode)
        {
            f4_temp_speed = p_instance_ctrl->st_encoder_parameter.f4_encoder_speed_rad *
                            p_extended_cfg->st_motor_params.u2_mtr_pp;
            *p_speed = f4_temp_speed;
            p_instance_ctrl->f_speed_rad = f4_temp_speed;

            /* Position Radian */
            *p_phase_err = p_instance_ctrl->st_encoder_parameter.f4_encoder_position_rad;

            rm_motor_sense_encoder_switch_carrier_interrupt(p_instance_ctrl, f4_temp_speed);
        }
        else
        {
            /* Do nothing */
        }

        /* Convert mechanical angle to electrical angle */
        d_temp       = (double) (*p_phase_err * p_extended_cfg->st_motor_params.u2_mtr_pp);
        f4_angle_rad = (float) (fmod(d_temp, (double) MOTOR_SENSE_ENCODER_TWOPI));
#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
        if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_HALL == p_instance_ctrl->e_adjust_mode)
        {
            f4_angle_rad += p_instance_ctrl->st_encoder_hall.f4_hall_angle_rad;
        }
#endif
    }

    if (f4_angle_rad >= MOTOR_SENSE_ENCODER_TWOPI)
    {
        f4_angle_rad -= MOTOR_SENSE_ENCODER_TWOPI;
    }
    else if (f4_angle_rad < 0.0F)
    {
        f4_angle_rad += MOTOR_SENSE_ENCODER_TWOPI;
    }
    else
    {
        /* Do nothing */
    }

    *p_angle = f4_angle_rad;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Angle Adjustment Process. Implements @ref motor_angle_api_t::angleAdjust
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_AngleAdjust (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_sense_encoder_angle_adjust_excite(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Encoder Cyclic Process (Call in cyclic timer). Implements @ref motor_angle_api_t::encoderCyclic
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_EncoderCyclic (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_sense_encoder_cyclic(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Perform cyclic process. Implements @ref motor_angle_api_t::cyclicProcess
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_CyclicProcess (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_sense_encoder_cyclic(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets information of Encoder Angle Module. Implements @ref motor_angle_api_t::infoGet
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_InfoGet (motor_angle_ctrl_t * const p_ctrl, motor_angle_encoder_info_t * const p_info)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

    uint8_t temp_full = 0U;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_info);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_info->e_adjust_status = p_instance_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status;

    if (p_instance_ctrl->st_encoder_parameter.u2_encoder_angle_adj_count >=
        p_instance_ctrl->st_encoder_parameter.u2_encoder_angle_adj_time)
    {
        temp_full = 1U;
    }

    p_info->u1_adjust_count_full = temp_full;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of Angle&Speed calculation with an encoder. Implements @ref motor_angle_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data is update.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_ParameterUpdate (motor_angle_ctrl_t * const      p_ctrl,
                                                  motor_angle_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_encoder_instance_ctrl_t * p_instance_ctrl = (motor_sense_encoder_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_ENCODER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    MOTOR_SENSE_ENCODER_ERROR_RETURN(MOTOR_SENSE_ENCODER_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_encoder_extended_cfg_t * p_extended_cfg =
        (motor_sense_encoder_extended_cfg_t *) p_cfg->p_extend;

    p_instance_ctrl->e_loop_mode = p_extended_cfg->loop_mode;

    rm_motor_sense_encoder_init(&(p_instance_ctrl->st_encoder_parameter), &(p_extended_cfg->encoder_config));
    rm_motor_sense_encoder_highspeed_init(&(p_instance_ctrl->st_encoder_highspeed), p_extended_cfg);

    p_instance_ctrl->p_cfg = p_cfg;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set d/q-axis Current Data & Voltage Reference. Implements @ref motor_angle_api_t::currentSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Motor sense encoder software currentSet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_CurrentSet (motor_angle_ctrl_t * const              p_ctrl,
                                             motor_angle_current_t * const           p_st_current,
                                             motor_angle_voltage_reference_t * const p_st_voltage)
{
    /* This function isn't supported.  It is defined only to implement a required function of motor_angle_api_t.
     * Mark the input parameter as unused since this function isn't supported. */

    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_st_current);
    FSP_PARAMETER_NOT_USED(p_st_voltage);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Set Speed Information. Implements @ref motor_angle_api_t::speedSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Motor sense encoder software speedSet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_SpeedSet (motor_angle_ctrl_t * const p_ctrl,
                                           float const                speed_ctrl,
                                           float const                damp_speed)
{
    /* This function isn't supported.  It is defined only to implement a required function of motor_angle_api_t.
     * Mark the input parameter as unused since this function isn't supported. */

    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(speed_ctrl);
    FSP_PARAMETER_NOT_USED(damp_speed);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Set the flag of PI Control runs. Implements @ref motor_angle_api_t::flagPiCtrlSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Motor sense encoder software flagPiCtrlSet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_FlagPiCtrlSet (motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi)
{
    /* This function isn't supported.  It is defined only to implement a required function of motor_angle_api_t.
     * Mark the input parameter as unused since this function isn't supported. */

    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(flag_pi);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Gets estimated d/q-axis component. Implements @ref motor_angle_api_t::estimatedComponentGet
 *
 * @retval FSP_ERR_UNSUPPORTED       Motor sense encoder software estimatedComponentGet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_EstimatedComponentGet (motor_angle_ctrl_t * const p_ctrl,
                                                        float * const              p_ed,
                                                        float * const              p_eq)
{
    /* This function isn't supported.  It is defined only to implement a required function of motor_angle_api_t.
     * Mark the input parameter as unused since this function isn't supported. */

    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_ed);
    FSP_PARAMETER_NOT_USED(p_eq);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Set sensor data. Implements @ref motor_angle_api_t::sensorDataSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_ENCODER_SensorDataSet (motor_angle_ctrl_t * const    p_ctrl,
                                                motor_angle_ad_data_t * const p_ad_data)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_ad_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_SENSE_ENCODER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_cyclic
 * Description   : Cyclic process of Encoder (Call at timer interrupt)
 * Arguments     : p_instance - The pointer to encoder calculate instance structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_cyclic (motor_sense_encoder_instance_ctrl_t * p_instance_ctrl)
{
    timer_instance_t const * p_timer = p_instance_ctrl->p_timer;
#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
    motor_sense_encoder_extended_cfg_t * p_extended =
        (motor_sense_encoder_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
#endif

    if (p_timer != NULL)
    {
#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
        p_instance_ctrl->st_encoder_hall.f4_hall_angle_rad =
            rm_motor_sense_encoder_hall_angle_adj_init(p_instance_ctrl);
#endif

        /* Reset encoder counter and timer */
        rm_motor_sense_encoder_reset_count(p_instance_ctrl);
        p_timer->p_api->start(p_timer->p_ctrl);

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
        if ((p_extended->p_u_hall_irq_instance != NULL) &&
            (p_extended->p_v_hall_irq_instance != NULL) &&
            (p_extended->p_w_hall_irq_instance != NULL))
        {
            p_extended->p_u_hall_irq_instance->p_api->enable(p_extended->p_u_hall_irq_instance->p_ctrl);
            p_extended->p_v_hall_irq_instance->p_api->enable(p_extended->p_v_hall_irq_instance->p_ctrl);
            p_extended->p_w_hall_irq_instance->p_api->enable(p_extended->p_w_hall_irq_instance->p_ctrl);
        }
#endif

        p_instance_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH;
    }
}

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_hall_angle_interrupt
 * Description   : calculate rotor position at Hall interrupt
 * Arguments     : p_args - The pointer to argument of External IRQ intterupt callback
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_sense_encoder_hall_angle_interrupt (external_irq_callback_args_t * p_args)
{
    float f4_temp;
    motor_sense_encoder_instance_ctrl_t * st_encoder =
        (motor_sense_encoder_instance_ctrl_t *) p_args->p_context;
    motor_sense_encoder_extended_cfg_t * p_extended_cfg =
        (motor_sense_encoder_extended_cfg_t *) st_encoder->p_cfg->p_extend;

    if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH == st_encoder->st_encoder_parameter.u1_encoder_angle_adj_status)
    {
        /* Integrate encoder counter difference */
        rm_motor_sense_encoder_calculate_count_difference(st_encoder);

        /* Calculate angle (mechanical) */
        f4_temp =
            MOTOR_SENSE_ENCODER_TWOPI * (float) (st_encoder->st_encoder_highspeed.s4_encoder_highspeed_angle_count);
        f4_temp = f4_temp * st_encoder->st_encoder_parameter.f4_encoder_cpr_inverse;

        /* Get hall signal */
        st_encoder->st_encoder_hall.u1_hall_signal = rm_motor_sense_encoder_get_hall_signal(st_encoder);

        /* Hall edge angle set */
        st_encoder->st_encoder_hall.f4_hall_angle_rad =
            rm_motor_sense_encoder_hall_angle_edge_set(st_encoder->st_encoder_hall.u1_hall_signal,
                                                       st_encoder->st_encoder_hall.u1_hall_pre_signal);
        if (MOTOR_SENSE_ENCODER_CW == st_encoder->u1_direction)
        {
            st_encoder->st_encoder_hall.f4_hall_angle_rad -=
                (f4_temp * p_extended_cfg->st_motor_params.u2_mtr_pp);
        }
        else
        {
            st_encoder->st_encoder_hall.f4_hall_angle_rad +=
                ((MOTOR_SENSE_ENCODER_HALL_TWOPI - f4_temp) * p_extended_cfg->st_motor_params.u2_mtr_pp);
        }

        st_encoder->st_encoder_hall.u1_hall_interrupt_flag = MOTOR_SENSE_ENCODER_HALL_FLAG_SET;

 #ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL
        if ((p_extended_cfg->p_u_hall_irq_instance != NULL) &&
            (p_extended_cfg->p_v_hall_irq_instance != NULL) &&
            (p_extended_cfg->p_w_hall_irq_instance != NULL))
        {
            p_extended_cfg->p_u_hall_irq_instance->p_api->disable(p_extended_cfg->p_u_hall_irq_instance->p_ctrl);
            p_extended_cfg->p_v_hall_irq_instance->p_api->disable(p_extended_cfg->p_v_hall_irq_instance->p_ctrl);
            p_extended_cfg->p_w_hall_irq_instance->p_api->disable(p_extended_cfg->p_w_hall_irq_instance->p_ctrl);
        }
 #endif
    }
}                                      /* End of function rm_motor_sense_encoder_hall_angle_interrupt */

#endif /* MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_interrupt
 * Description   : calculate rotor position and speed
 * Arguments     : p_args - The pointer to argument of timer interrupt callback
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_sense_encoder_interrupt (timer_callback_args_t * p_args)
{
    int32_t                               s4_encd_delta_tcnt    = 0;
    float                                 f4_temp_speed_rad_avg = 0.0F;
    unsigned short                        u2_temp               = 0U;
    uint32_t                              u4_temp               = 0U;
    int32_t                               s4_temp               = 0;
    float                                 f4_temp0              = 0.0F;
    motor_angle_instance_t              * p_angle               = (motor_angle_instance_t *) p_args->p_context;
    motor_sense_encoder_instance_ctrl_t * st_encoder            =
        (motor_sense_encoder_instance_ctrl_t *) p_angle->p_ctrl;
    motor_sense_encoder_extended_cfg_t * extend_cfg =
        (motor_sense_encoder_extended_cfg_t *) st_encoder->p_cfg->p_extend;
    timer_instance_t const * p_timer         = st_encoder->p_timer;
    timer_instance_t const * p_input_capture = st_encoder->p_input_capture;
    timer_status_t           temp_status;
    timer_info_t             temp_info;

    if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH == st_encoder->st_encoder_parameter.u1_encoder_angle_adj_status)
    {
        /* Integrate encoder counter difference */
        p_input_capture->p_api->statusGet(p_input_capture->p_ctrl, &temp_status);
        p_input_capture->p_api->infoGet(p_input_capture->p_ctrl, &temp_info);
        u4_temp = temp_status.counter;

        if (MOTOR_SENSE_ENCODER_FLAG_SET == st_encoder->st_encoder_highspeed.u1_encoder_interrupt_on_flag)
        {
            st_encoder->st_encoder_parameter.s4_encoder_angle_count =
                st_encoder->st_encoder_highspeed.s4_encoder_highspeed_angle_count;
            st_encoder->st_encoder_parameter.u2_encoder_pre_phase_count =
                st_encoder->st_encoder_highspeed.u2_encoder_highspeed_pre_phase_count;
            st_encoder->st_encoder_highspeed.u1_encoder_interrupt_on_flag = MOTOR_SENSE_ENCODER_FLAG_CLEAR;
        }

        if (temp_info.period_counts > MOTOR_SENSE_ENCODER_16BIT)
        {
            s4_encd_delta_tcnt = (int32_t) (u4_temp - st_encoder->st_encoder_parameter.u2_encoder_pre_phase_count);
        }
        else
        {
            s4_encd_delta_tcnt =
                (int16_t) ((uint16_t) u4_temp - (uint16_t) st_encoder->st_encoder_parameter.u2_encoder_pre_phase_count);
        }

        /* Correction at counter boundary (max=>0 or 0=>max) */
        if (s4_encd_delta_tcnt <= -(st_encoder->st_encoder_parameter.s2_encoder_cpr))
        {
            st_encoder->st_encoder_parameter.s4_encoder_angle_count = (int32_t) u4_temp;
        }
        else if (s4_encd_delta_tcnt >= st_encoder->st_encoder_parameter.s2_encoder_cpr)
        {
            st_encoder->st_encoder_parameter.s4_encoder_angle_count =
                (int32_t) -(temp_info.period_counts - u4_temp);
        }
        else
        {
            st_encoder->st_encoder_parameter.s4_encoder_angle_count += s4_encd_delta_tcnt;
        }

        st_encoder->st_encoder_parameter.u2_encoder_pre_phase_count = u4_temp;

        /* Angle calculation */
        if (MOTOR_SENSE_ENCODER_LOOP_SPEED == st_encoder->e_loop_mode)
        {
            /* Limit count value to counts of one rotation */
            if (st_encoder->st_encoder_parameter.s4_encoder_angle_count >=
                (int32_t) st_encoder->st_encoder_parameter.s2_encoder_cpr)
            {
                st_encoder->st_encoder_parameter.s4_encoder_angle_count -=
                    (int32_t) st_encoder->st_encoder_parameter.s2_encoder_cpr;
            }
            else if (st_encoder->st_encoder_parameter.s4_encoder_angle_count < 0)
            {
                st_encoder->st_encoder_parameter.s4_encoder_angle_count +=
                    (int32_t) st_encoder->st_encoder_parameter.s2_encoder_cpr;
            }
            else
            {
                /* Do Nothing */
            }
        }

        /* Calculate angle (mechanical) */
        st_encoder->st_encoder_parameter.f4_encoder_position_rad =
            (MOTOR_SENSE_ENCODER_TWOPI * (float) (st_encoder->st_encoder_parameter.s4_encoder_angle_count)) *
            st_encoder->st_encoder_parameter.f4_encoder_cpr_inverse;

        /* Pulse width calculation */
        /* Calculate integrated pulse width */
        p_timer->p_api->statusGet(p_timer->p_ctrl, &temp_status);
        p_timer->p_api->infoGet(p_timer->p_ctrl, &temp_info);
        st_encoder->st_encoder_parameter.u4_encoder_timer_capture = temp_status.counter;
        if (temp_info.period_counts > MOTOR_SENSE_ENCODER_16BIT)
        {
            s4_temp =
                (int32_t) (st_encoder->st_encoder_parameter.u4_encoder_timer_capture -
                           st_encoder->st_encoder_parameter.u4_encoder_timer_pre_capture);
        }
        else
        {
            u2_temp =
                ((uint16_t) st_encoder->st_encoder_parameter.u4_encoder_timer_capture -
                 (uint16_t) st_encoder->st_encoder_parameter.u4_encoder_timer_pre_capture);
            s4_temp = (int32_t) u2_temp;
        }

        st_encoder->st_encoder_parameter.s4_encoder_pulse_width_buff += s4_temp;
        st_encoder->st_encoder_parameter.u4_encoder_timer_pre_capture =
            st_encoder->st_encoder_parameter.u4_encoder_timer_capture;

        /* Limit pulse width, prevent s4_encd_pulse_width_buff from overflow */
        s4_temp = (int32_t) extend_cfg->encoder_config.u4_zero_speed_count;
        if (st_encoder->st_encoder_parameter.s4_encoder_pulse_width_buff > s4_temp)
        {
            st_encoder->st_encoder_parameter.s4_encoder_pulse_width_buff = s4_temp;
        }

        /* Push last pulse width to buffer */
        st_encoder->st_encoder_parameter.s4_encoder_pulse_width =
            st_encoder->st_encoder_parameter.s4_encoder_pulse_width_buff;
        st_encoder->st_encoder_parameter.s4_encoder_pulse_width_buff = 0U;
        u2_temp = st_encoder->st_encoder_parameter.u2_encoder_timer_cnt_num;
        s4_temp = st_encoder->st_encoder_parameter.s4_encoder_timer_count_buff[u2_temp];
        st_encoder->st_encoder_parameter.s4_encoder_pulse_width_sum +=
            (st_encoder->st_encoder_parameter.s4_encoder_pulse_width - s4_temp);
        st_encoder->st_encoder_parameter.s4_encoder_timer_count_buff[u2_temp] =
            st_encoder->st_encoder_parameter.s4_encoder_pulse_width;
        st_encoder->st_encoder_parameter.u2_encoder_timer_cnt_num++;
        if (st_encoder->st_encoder_parameter.u2_encoder_timer_cnt_num == MOTOR_SENSE_ENCODER_AVERAGE)
        {
            st_encoder->st_encoder_parameter.u2_encoder_timer_cnt_num = 0U;
        }

        /* Speed averaging */
        if (st_encoder->st_encoder_parameter.s4_encoder_pulse_width_sum != 0)
        {
            /* calculate angle[rad] difference (MTR_ENCD_CNTAVG count of encoder) */
            /* angle[rad] = 2Pi * (Count Difference) / (Count Per Rotation) */
            /* divide angle[rad] by time[s] to calculate speed[rad/s] */
            /* time[s] = pulse_width[count] / (GPT Frequency[Hz]) = pulse_width[count]/(PWM Frequency[Hz]) */
            f4_temp0 = st_encoder->st_encoder_parameter.f4_encoder_angle_difference *
                       (float) MOTOR_SENSE_ENCODER_AVERAGE * (float) temp_info.clock_frequency;
            f4_temp_speed_rad_avg = f4_temp0 / (float) st_encoder->st_encoder_parameter.s4_encoder_pulse_width_sum;

            /* Get speed direction from encoder position change */
            if ((0 > s4_encd_delta_tcnt) &&
                (s4_encd_delta_tcnt > -(st_encoder->st_encoder_parameter.s2_encoder_cpr)))
            {
                f4_temp_speed_rad_avg = -f4_temp_speed_rad_avg;
            }
            else if ((st_encoder->st_encoder_parameter.f4_encoder_speed_pre_rad < 0.0F) &&
                     (s4_encd_delta_tcnt > (st_encoder->st_encoder_parameter.s2_encoder_cpr)))
            {
                f4_temp_speed_rad_avg = -f4_temp_speed_rad_avg;
            }
            else if (0 == s4_encd_delta_tcnt)
            {
                if (0.0F > st_encoder->st_encoder_parameter.f4_encoder_speed_pre_rad)
                {
                    f4_temp_speed_rad_avg = -f4_temp_speed_rad_avg;
                }
            }
            else
            {
                /* Do Nothing*/
            }

            st_encoder->st_encoder_parameter.f4_encoder_speed_pre_rad =
                st_encoder->st_encoder_parameter.f4_encoder_speed_rad;
            st_encoder->st_encoder_parameter.f4_encoder_speed_rad = f4_temp_speed_rad_avg;
        }
    }
}                                      /* End of function rm_motor_sense_encoder_interrupt */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_init
 * Description   : Initialize variables when encoder control init
 * Arguments     : p_encoder  - encoder structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_init (motor_sense_encoder_parameter_t * p_encoder,
                                         motor_sense_encoder_config_t    * c_config)
{
    p_encoder->s2_encoder_cpr              = (int16_t) c_config->u2_cpr;
    p_encoder->f4_encoder_angle_difference = MOTOR_SENSE_ENCODER_TWOPI / (float) c_config->u2_cpr;
    p_encoder->f4_encoder_cpr_inverse      = 1.0F / (float) c_config->u2_cpr;
    p_encoder->u2_encoder_angle_adj_time   = c_config->u2_angle_adjust_time;

    rm_motor_sense_encoder_reset(p_encoder);
}                                      /* End of function rm_motor_sense_encoder_init */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_reset
 * Description   : Reset variables when encoder control
 * Arguments     : p_encoder  - encoder structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_reset (motor_sense_encoder_parameter_t * p_encoder)
{
    p_encoder->u1_encoder_angle_adj_status    = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE;
    p_encoder->u2_encoder_angle_adj_count     = 0U;
    p_encoder->u2_encoder_pre_phase_count     = 0U;
    p_encoder->u4_encoder_timer_capture       = 0U;
    p_encoder->u4_encoder_timer_pre_capture   = 0U;
    p_encoder->u2_encoder_timer_cnt_num       = 0U;
    p_encoder->s4_encoder_timer_count_buff[0] = 0;
    p_encoder->s4_encoder_timer_count_buff[1] = 0;
    p_encoder->s4_encoder_timer_count_buff[2] = 0;
    p_encoder->s4_encoder_timer_count_buff[3] = 0;
    p_encoder->s4_encoder_pulse_width         = 0;
    p_encoder->s4_encoder_pulse_width_buff    = 0;
    p_encoder->s4_encoder_pulse_width_sum     = 0;
    p_encoder->s4_encoder_angle_count         = 0;
    p_encoder->f4_encoder_speed_pre_rad       = 0.0F;
    p_encoder->f4_encoder_speed_rad           = 0.0F;
    p_encoder->f4_encoder_position_rad        = 0.0F;
}                                      /* End of function rm_motor_sense_encoder_reset */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_highspeed_init
 * Description   : Initialize variables when motor control start
 * Arguments     : p_ehighspeed  - encoder highspeed structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_highspeed_init (motor_sense_encoder_highspeed_t    * p_ehighspeed,
                                                   motor_sense_encoder_extended_cfg_t * p_extended_cfg)
{
    float f_temp        = 0.0F;
    float f_ctrl_period = 0.0F;
    float f_rpm_rad;

    f_ctrl_period = ((float) (p_extended_cfg->encoder_config.u1_interrupt_decimation + 1) /
                     (p_extended_cfg->encoder_config.f_carrier_frequency * MOTOR_SENSE_ENCODER_CALCULATE_KHz));

    f_temp = (f_ctrl_period * p_extended_cfg->encoder_config.f_occupancy_time -
              p_extended_cfg->encoder_config.f_carrier_time) / p_extended_cfg->encoder_config.f_process_time;
    f_temp = (f_temp * MOTOR_SENSE_ENCODER_CALCULATE_60) / (f_ctrl_period * p_extended_cfg->encoder_config.u2_cpr);

    f_rpm_rad = (float) p_extended_cfg->st_motor_params.u2_mtr_pp *
                MOTOR_SENSE_ENCODER_TWOPI / MOTOR_SENSE_ENCODER_CALCULATE_60;

    p_ehighspeed->f4_encoder_highspeed_sw_speed_rad = f_temp * f_rpm_rad;

    p_ehighspeed->f4_encoder_highspeed_sw_speed_margin_rad =
        (float) p_extended_cfg->encoder_config.u2_highspeed_change_margin_rpm * f_rpm_rad;

    rm_motor_sense_encoder_highspeed_reset(p_ehighspeed);
}                                      /* End of function rm_motor_sense_encoder_highspeed_init */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_highspeed_reset
 * Description   : Reset variables when motor control start
 * Arguments     : p_ehighspeed  - encoder highspeed structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_highspeed_reset (motor_sense_encoder_highspeed_t * p_ehighspeed)
{
    p_ehighspeed->u1_encoder_position_speed_calc_mode  = MOTOR_SENSE_ENCODER_ENCD_INTERRUPT;
    p_ehighspeed->u1_encoder_interrupt_on_flag         = MOTOR_SENSE_ENCODER_FLAG_CLEAR;
    p_ehighspeed->u1_encoder_position_speed_count      = 0;
    p_ehighspeed->u2_encoder_highspeed_pre_phase_count = 0;
    p_ehighspeed->s4_encoder_highspeed_angle_count     = 0;
    p_ehighspeed->f4_encoder_highspeed_position_rad    = 0.0F;
    p_ehighspeed->f4_encoder_highspeed_previous_rad    = 0.0F;
    p_ehighspeed->f4_encoder_highspeed_speed_rad       = 0.0F;
    p_ehighspeed->f4_encoder_highspeed_speed_pre_rad   = 0.0F;
}                                      /* End of function rm_motor_sense_encoder_highspeed_reset */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_reset_count
 * Description   : Encoder count reset
 * Arguments     : p_ctrl  - encoder calculate structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_reset_count (motor_sense_encoder_instance_ctrl_t * p_ctrl)
{
    timer_instance_t const * p_input_capture = p_ctrl->p_input_capture;

    if (p_input_capture != NULL)
    {
        p_ctrl->st_encoder_parameter.s4_encoder_angle_count     = 0;
        p_ctrl->st_encoder_parameter.u2_encoder_pre_phase_count = 0U;

        p_input_capture->p_api->stop(p_input_capture->p_ctrl);
        p_input_capture->p_api->reset(p_input_capture->p_ctrl);
        p_input_capture->p_api->start(p_input_capture->p_ctrl);
    }
}                                      /* End of function rm_motor_sense_encoder_reset_count */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_angle_adjust_excite
 * Description   : Angle adjust with forced excitation
 * Arguments     : p_ctrl  - encoder calculate structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_angle_adjust_excite (motor_sense_encoder_instance_ctrl_t * p_ctrl)
{
    timer_instance_t const * p_timer = p_ctrl->p_timer;

    if (p_timer != NULL)
    {
        p_ctrl->st_encoder_parameter.u2_encoder_angle_adj_count++;

        if (p_ctrl->st_encoder_parameter.u2_encoder_angle_adj_count >
            p_ctrl->st_encoder_parameter.u2_encoder_angle_adj_time)
        {
            /* Reset angle adjust counter */
            p_ctrl->st_encoder_parameter.u2_encoder_angle_adj_count = 0U;
        }

        if (p_ctrl->st_encoder_parameter.u2_encoder_angle_adj_count ==
            p_ctrl->st_encoder_parameter.u2_encoder_angle_adj_time)
        {
            /* Angle adjusted to 90 degree */
            if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE ==
                p_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status)
            {
                p_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE;
            }
            /* Angle adjusted to 0 degree */
            else if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE ==
                     p_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status)
            {
                /* Reset timer counter */
                rm_motor_sense_encoder_reset_count(p_ctrl);
                p_timer->p_api->reset(p_timer->p_ctrl);
                p_timer->p_api->start(p_timer->p_ctrl);

                p_ctrl->st_encoder_parameter.u1_encoder_angle_adj_status = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH;
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
}                                      /* End of function rm_motor_sense_encoder_angle_adjust_excite */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_calculate_count_difference
 * Description   : Enncoder count difference calculation
 * Arguments     : p_ctrl  - encoder calculate structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_calculate_count_difference (motor_sense_encoder_instance_ctrl_t * p_ctrl)
{
    timer_instance_t const          * p_input_capture = p_ctrl->p_input_capture;
    motor_sense_encoder_highspeed_t * st_ehighspeed   = &(p_ctrl->st_encoder_highspeed);
    timer_status_t temp_status;
    unsigned short u2_temp;
    int16_t        s2_encd_delta_tcnt;

    p_input_capture->p_api->statusGet(p_input_capture->p_ctrl, &temp_status);
    u2_temp = (unsigned short) (temp_status.counter);

    s2_encd_delta_tcnt = (int16_t) -(st_ehighspeed->u2_encoder_highspeed_pre_phase_count - u2_temp);
    st_ehighspeed->s4_encoder_highspeed_angle_count    += (int32_t) s2_encd_delta_tcnt;
    st_ehighspeed->u2_encoder_highspeed_pre_phase_count = u2_temp;
}                                      /* End of function rm_motor_sense_encoder_calculate_count_difference */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_highspeed_calculate
 * Description   : Calculate speed
 * Arguments     : st_ehighspeed   - encoder highspeed structure (pointer)
 *                 f4_position_err - position error [rad]
 *                 f4_ctrl_period  - control period
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_highspeed_calculate (motor_sense_encoder_instance_ctrl_t * p_ctrl,
                                                        float                                 f4_position_err,
                                                        float                                 f4_ctrl_period)
{
    float f4_temp_speed_rad;
    motor_sense_encoder_highspeed_t          * st_ehighspeed = &(p_ctrl->st_encoder_highspeed);
    motor_sense_encoder_extended_cfg_t const * p_extend      = p_ctrl->p_cfg->p_extend;

    f4_temp_speed_rad = f4_position_err / f4_ctrl_period;
    st_ehighspeed->f4_encoder_highspeed_previous_rad = st_ehighspeed->f4_encoder_highspeed_position_rad;
    st_ehighspeed->f4_encoder_highspeed_speed_rad    = st_ehighspeed->f4_encoder_highspeed_speed_pre_rad +
                                                       (p_extend->encoder_config.f_highspeed_lpf_parameter *
                                                        (f4_temp_speed_rad -
                                                         st_ehighspeed->f4_encoder_highspeed_speed_pre_rad));
    st_ehighspeed->f4_encoder_highspeed_speed_pre_rad = st_ehighspeed->f4_encoder_highspeed_speed_rad;
}                                      /* End of function rm_motor_sense_encoder_highspeed_calculate */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_switch_encoder_interrupt
 * Description   : Switch interrupt process of encoder interrupt
 * Arguments     : st_ehighspeed  - encoder highspeed structure (pointer)
 *                 f4_speed_rad   - speed [rad/s]
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_switch_encoder_interrupt (motor_sense_encoder_instance_ctrl_t * p_ctrl,
                                                             float                                 f4_speed_rad)
{
    float f4_temp;
    motor_sense_encoder_highspeed_t          * st_ehighspeed = &(p_ctrl->st_encoder_highspeed);
    motor_sense_encoder_extended_cfg_t const * p_extend      = p_ctrl->p_cfg->p_extend;

    gpt_extended_cfg_t * p_gpt_exntend = (gpt_extended_cfg_t *) p_extend->p_input_capture_instance->p_cfg->p_extend;

    f4_temp =
        st_ehighspeed->f4_encoder_highspeed_sw_speed_rad - st_ehighspeed->f4_encoder_highspeed_sw_speed_margin_rad;
    if (f4_temp > fabsf(f4_speed_rad))
    {
        R_BSP_IrqEnable(p_gpt_exntend->capture_a_irq);
        st_ehighspeed->u1_encoder_interrupt_on_flag = MOTOR_SENSE_ENCODER_FLAG_SET;
        st_ehighspeed->u1_encoder_position_speed_count++;
        if (st_ehighspeed->u1_encoder_position_speed_count >= p_extend->encoder_config.u1_position_speed_change_counts)
        {
            st_ehighspeed->u1_encoder_position_speed_calc_mode = MOTOR_SENSE_ENCODER_ENCD_INTERRUPT;
            st_ehighspeed->u1_encoder_position_speed_count     = 0U;
        }
    }
    else
    {
        R_BSP_IrqDisable(p_gpt_exntend->capture_a_irq);
    }
}                                      /* End of function rm_motor_sense_encoder_switch_encoder_interrupt */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_switch_carrier_interrupt
 * Description   : Switch carrier innterupt process
 * Arguments     : st_ehighspeed  - encoder highspeed structure (pointer)
 *                 f4_speed_rad   - speed [rad/s]
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_switch_carrier_interrupt (motor_sense_encoder_instance_ctrl_t * p_ctrl,
                                                             float                                 f4_speed_rad)
{
    motor_sense_encoder_extended_cfg_t const * p_extend = p_ctrl->p_cfg->p_extend;

    gpt_extended_cfg_t * p_gpt_exntend = (gpt_extended_cfg_t *) p_extend->p_input_capture_instance->p_cfg->p_extend;

    motor_sense_encoder_highspeed_t * st_ehighspeed = &(p_ctrl->st_encoder_highspeed);

    if (st_ehighspeed->f4_encoder_highspeed_sw_speed_rad <= fabsf(f4_speed_rad))
    {
        st_ehighspeed->u1_encoder_position_speed_calc_mode = MOTOR_SENSE_ENCODER_CTRL_INTERRUPT;
        st_ehighspeed->u1_encoder_position_speed_count     = 0U;

        R_BSP_IrqDisable(p_gpt_exntend->capture_a_irq);
    }
}                                      /* End of function rm_motor_sense_encoder_switch_carrier_interrupt */

#ifdef MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_hall_init
 * Description   : Initialize variables when hall control init
 * Arguments     : p_hall   - hall structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_encoder_hall_init (motor_sense_encoder_hall_t * p_hall)
{
    /* Initialize of hall variables */
    p_hall->u1_hall_signal         = 0;
    p_hall->u1_hall_pre_signal     = 0;
    p_hall->u1_hall_interrupt_flag = MOTOR_SENSE_ENCODER_HALL_FLAG_CLEAR;
    p_hall->f4_hall_angle_rad      = 0.0F;
}                                      /* End of function rm_motor_sense_encoder_hall_init */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_hall_angle_adj_init
 * Description   : Initialize hall angle for angle adjust mode
 * Arguments     : p_ctrl   - encoder calculate structure (pointer)
 * Return Value  : Rotor angle of signal detected by hall sensor
 **********************************************************************************************************************/
static float rm_motor_sense_encoder_hall_angle_adj_init (motor_sense_encoder_instance_ctrl_t * p_ctrl)
{
    motor_sense_encoder_hall_t * st_hall = &(p_ctrl->st_encoder_hall);

    /* Get hall signal */
    st_hall->u1_hall_signal     = rm_motor_sense_encoder_get_hall_signal(p_ctrl);
    st_hall->u1_hall_pre_signal = st_hall->u1_hall_signal;

    /* Between the hall edge angle set */
    st_hall->f4_hall_angle_rad = rm_motor_sense_encoder_hall_angle_set(st_hall->u1_hall_signal);

    return st_hall->f4_hall_angle_rad;
}                                      /* End of function mtr_hall_angle_adj_init */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_hall_angle_edge_set
 * Description   : Process for hall edge angle set
 * Arguments     : u1_hall_signal - hall signal
 *                u1_pre_hall_signal - previous value of hall signal
 * Return Value  : Rotor angle of signal detected for hall sensor
 **********************************************************************************************************************/
static float rm_motor_sense_encoder_hall_angle_edge_set (uint8_t u1_hall_signal, uint8_t u1_pre_hall_signal)
{
    float f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;

    switch (u1_pre_hall_signal)
    {
        case MOTOR_SENSE_ENCODER_HALL_W:                            /* (1) */
        {
            if (MOTOR_SENSE_ENCODER_HALL_VW == u1_hall_signal)      /* (1 -> 3) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_330;
            }
            else if (MOTOR_SENSE_ENCODER_HALL_UW == u1_hall_signal) /* (1 -> 5) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_30;
            }
            else
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            }

            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_UW:                          /* (5) */
        {
            if (MOTOR_SENSE_ENCODER_HALL_W == u1_hall_signal)      /* (5 -> 1) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_30;
            }
            else if (MOTOR_SENSE_ENCODER_HALL_U == u1_hall_signal) /* (5 -> 4) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_90;
            }
            else
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            }

            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_U:                            /* (4) */
        {
            if (MOTOR_SENSE_ENCODER_HALL_UW == u1_hall_signal)      /* (4 -> 5) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_90;
            }
            else if (MOTOR_SENSE_ENCODER_HALL_UV == u1_hall_signal) /* (4 -> 6) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_150;
            }
            else
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            }

            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_UV:                          /* (6) */
        {
            if (MOTOR_SENSE_ENCODER_HALL_U == u1_hall_signal)      /* (6 -> 4) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_150;
            }
            else if (MOTOR_SENSE_ENCODER_HALL_V == u1_hall_signal) /* (6 -> 2) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_210;
            }
            else
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            }

            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_V:                            /* (2) */
        {
            if (MOTOR_SENSE_ENCODER_HALL_UV == u1_hall_signal)      /* (2 -> 6) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_210;
            }
            else if (MOTOR_SENSE_ENCODER_HALL_VW == u1_hall_signal) /* (2 -> 3) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_270;
            }
            else
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            }

            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_VW:                          /* (3) */
        {
            if (MOTOR_SENSE_ENCODER_HALL_V == u1_hall_signal)      /* (3 -> 2) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_270;
            }
            else if (MOTOR_SENSE_ENCODER_HALL_W == u1_hall_signal) /* (3 -> 1) */
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_330;
            }
            else
            {
                f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            }

            break;
        }

        default:
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            break;
        }
    }

    return f4_hall_angle_rad;
}                                      /* End of function rm_motor_sense_encoder_hall_angle_edge_set */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_encoder_hall_angle_set
 * Description   : Process for hall sensor interrupt
 * Arguments     : u1_hall_signal - hall signal
 * Return Value  : Rotor angle of signal detected for hall sensor
 **********************************************************************************************************************/
static float rm_motor_sense_encoder_hall_angle_set (uint8_t u1_hall_signal)
{
    float f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;

    switch (u1_hall_signal)
    {
        case MOTOR_SENSE_ENCODER_HALL_W: /* (1) */
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_30 - MOTOR_SENSE_ENCODER_HALL_EDGE_OFFSET;
            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_UW: /* (5) */
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_90 - MOTOR_SENSE_ENCODER_HALL_EDGE_OFFSET;
            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_U: /* (4) */
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_150 - MOTOR_SENSE_ENCODER_HALL_EDGE_OFFSET;
            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_UV: /* (6) */
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_210 - MOTOR_SENSE_ENCODER_HALL_EDGE_OFFSET;
            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_V: /* (2) */
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_270 - MOTOR_SENSE_ENCODER_HALL_EDGE_OFFSET;
            break;
        }

        case MOTOR_SENSE_ENCODER_HALL_VW: /* (3) */
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ANGLE_330 - MOTOR_SENSE_ENCODER_HALL_EDGE_OFFSET;
            break;
        }

        default:
        {
            f4_hall_angle_rad = MOTOR_SENSE_ENCODER_HALL_EDGE_ERROR;
            break;
        }
    }

    return f4_hall_angle_rad;
}                                      /* End of function rm_motor_sense_encoder_hall_angle_set */

#endif /* MOTOR_SENSE_ENCODER_CFG_SUPPORT_HALL */
