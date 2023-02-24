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
#include "rm_motor_sense_induction.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define  MOTOR_SENSE_INDUCTION_OPEN       (('M' << 24U) | ('T' << 16U) | ('S' << 8U) | ('I' << 0U))

#define  MOTOR_SENSE_INDUCTION_QUARTER    (0.25F)

#ifndef MOTOR_SENSE_INDUCTION_ERROR_RETURN

 #define MOTOR_SENSE_INDUCTION_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

#define MOTOR_SENSE_INDUCTION_FLAG_CLEAR              (0U)
#define MOTOR_SENSE_INDUCTION_FLAG_SET                (1U)

#define MOTOR_SENSE_INDUCTION_CW                      (0)
#define MOTOR_SENSE_INDUCTION_CCW                     (1)

#define MOTOR_SENSE_INDUCTION_ONEPI                   (3.14159265358979F)
#define MOTOR_SENSE_INDUCTION_TWOPI                   (3.14159265358979F * 2.0F)
#define MOTOR_SENSE_INDUCTION_HALF_PI                 (3.14159265358979F * 0.5F)

/* Open loop operation */
#define MOTOR_SENSE_INDUCTION_OPENLOOP_INACTIVE       (0)
#define MOTOR_SENSE_INDUCTION_OPENLOOP_ACTIVE         (1)

/* Const value definition */
#define MOTOR_SENSE_INDUCTION_CALCULATE_KHz           (1000.0F)
#define MOTOR_SENSE_INDUCTION_CALCULATE_360           (360.0F)
#define MOTOR_SENSE_INDUCTION_CALCULATE_60            (60.0F)
#define MOTOR_SENSE_INDUCTION_CALCULATE_QUARTER       (0.25F)
#define MOTOR_SENSE_INDUCTION_CALCULATE_HALF          (0.5F)
#define MOTOR_SENSE_INDUCTION_CORRECT_ANGLE           (MOTOR_SENSE_INDUCTION_TWOPI / 8.0F) /* Shift 45 degrees. */
#define MOTOR_SENSE_INDUCTION_CALCULATE_SIX           (6.0F)

/* Induction sensor calibration status */
#define MOTOR_SENSE_INDUCTION_PREPARED                (0)
#define MOTOR_SENSE_INDUCTION_RUNNING                 (1)
#define MOTOR_SENSE_INDUCTION_CORRECT_FINISH          (2)
#define MOTOR_SENSE_INDUCTION_ERROR_FINISH            (3)

/* Induction sensor calibration sequence */
#define MOTOR_SENSE_INDUCTION_INIT                    (0)
#define MOTOR_SENSE_INDUCTION_DATA_GET_ERR_CORRECT    (1)
#define MOTOR_SENSE_INDUCTION_RESULT_JUDGE            (2)
#define MOTOR_SENSE_INDUCTION_CALIB_SEQ_FIN           (3)

/* Induction sensor calibration status */
#define MOTOR_SENSE_INDUCTION_CALIBRATION_NONE        (0)
#define MOTOR_SENSE_INDUCTION_GET_SIGNAL_1ST          (1)
#define MOTOR_SENSE_INDUCTION_GET_SIGNAL_2ND          (2)
#define MOTOR_SENSE_INDUCTION_GAIN_CORRECTION         (3)
#define MOTOR_SENSE_INDUCTION_GET_PHASE_DATA          (4)
#define MOTOR_SENSE_INDUCTION_PHASE_CORRECTION        (5)
#define MOTOR_SENSE_INDUCTION_CALIBRATION_FINISH      (6)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_motor_sense_induction_cyclic(motor_sense_induction_instance_ctrl_t * p_instance_ctrl);

static void rm_motor_sense_induction_init(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_reset(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_info_reset(motor_sense_induction_correct_data_t * p_info);
static void rm_motor_sense_induction_angle_adjust_excite(motor_sense_induction_instance_ctrl_t * p_ctrl);

static void rm_motor_sense_induction_position_speed_calculation(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_angle_speed(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_correction_sequence(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_get_data_for_gain_calibration(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_correction(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_get_data_phase_calibration(motor_sense_induction_instance_ctrl_t * p_ctrl);
static void rm_motor_sense_induction_initial_position_adjust(motor_sense_induction_instance_ctrl_t * p_ctrl);

static float rm_motor_sense_induction_lpff(float f4_lpf_input, float f4_pre_lpf_output, float f4_lpf_k);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_angle_api_t g_motor_angle_on_motor_sense_induction =
{
    .open                  = RM_MOTOR_SENSE_INDUCTION_Open,
    .close                 = RM_MOTOR_SENSE_INDUCTION_Close,
    .reset                 = RM_MOTOR_SENSE_INDUCTION_Reset,
    .internalCalculate     = RM_MOTOR_SENSE_INDUCTION_InternalCalculate,
    .angleSpeedGet         = RM_MOTOR_SENSE_INDUCTION_AngleSpeedGet,
    .angleAdjust           = RM_MOTOR_SENSE_INDUCTION_AngleAdjust,
    .encoderCyclic         = RM_MOTOR_SENSE_INDUCTION_EncoderCyclic,
    .cyclicProcess         = RM_MOTOR_SENSE_INDUCTION_CyclicProcess,
    .sensorDataSet         = RM_MOTOR_SENSE_INDUCTION_SensorDataSet,
    .infoGet               = RM_MOTOR_SENSE_INDUCTION_InfoGet,
    .parameterUpdate       = RM_MOTOR_SENSE_INDUCTION_ParameterUpdate,
    .currentSet            = RM_MOTOR_SENSE_INDUCTION_CurrentSet,
    .speedSet              = RM_MOTOR_SENSE_INDUCTION_SpeedSet,
    .flagPiCtrlSet         = RM_MOTOR_SENSE_INDUCTION_FlagPiCtrlSet,
    .estimatedComponentGet = RM_MOTOR_SENSE_INDUCTION_EstimatedComponentGet,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_SENSE_INDUCTION
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the Angle module. Implements @ref motor_angle_api_t::open.
 *
 * @retval FSP_SUCCESS              Angle Induction module successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Configuration parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_Open (motor_angle_ctrl_t * const p_ctrl, motor_angle_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
#endif
    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_cfg->p_extend;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_extended_cfg != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(0.0F <= p_extended_cfg->f_current_frequency, FSP_ERR_INVALID_ARGUMENT);
#endif

    rm_motor_sense_induction_init(p_instance_ctrl);

    p_instance_ctrl->e_loop_mode = p_extended_cfg->e_loop_mode;

    p_instance_ctrl->f_current_ctrl_period =
        1.0F / (p_extended_cfg->f_current_frequency * MOTOR_SENSE_INDUCTION_CALCULATE_KHz);

    p_instance_ctrl->f_adc_scaling =
        p_extended_cfg->f_reference_voltage / p_extended_cfg->f_ad_conversion_scale;

    p_instance_ctrl->f_inverse_polepairs = 1.0F / p_extended_cfg->u1_induction_polepairs;

    p_instance_ctrl->f_openloop_speed =
        (p_extended_cfg->f_openloop_speed_rpm * MOTOR_SENSE_INDUCTION_TWOPI) / MOTOR_SENSE_INDUCTION_CALCULATE_60;

    p_instance_ctrl->f_calibration_period =
        (MOTOR_SENSE_INDUCTION_CALCULATE_60 / p_extended_cfg->f_openloop_speed_rpm) *
        p_instance_ctrl->f_current_ctrl_period / (float) p_extended_cfg->u1_get_timing_count;

    p_instance_ctrl->f_get_adc_resolution =
        (p_extended_cfg->f_openloop_speed_rpm * MOTOR_SENSE_INDUCTION_CALCULATE_SIX) *
        (p_instance_ctrl->f_current_ctrl_period * (float) p_extended_cfg->u1_get_timing_count);

    p_instance_ctrl->u2_adc_sample_count =
        (uint16_t) (MOTOR_SENSE_INDUCTION_CALCULATE_360 / p_instance_ctrl->f_get_adc_resolution);

    p_instance_ctrl->p_cfg = p_cfg;

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_SENSE_INDUCTION_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Disables specified Angle module. Implements @ref motor_angle_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_Close (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_sense_induction_init(p_instance_ctrl);

    p_instance_ctrl->open = 0U;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of Angle module. Implements @ref motor_angle_api_t::reset
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_Reset (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_sense_induction_reset(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Calculate internal parameters. Implements @ref motor_angle_api_t::internalCalculate
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_InternalCalculate (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* After the rotor initialization and sensor error correction finished, this process is active. */
    if (MOTOR_SENSE_INDUCTION_CORRECT_FINISH == p_instance_ctrl->u1_correct_status)
    {
        rm_motor_sense_induction_position_speed_calculation(p_instance_ctrl);
    }

    rm_motor_sense_induction_angle_speed(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets the current rotor's angle and rotation speed. Implements @ref motor_angle_api_t::angleSpeedGet
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_AngleSpeedGet (motor_angle_ctrl_t * const p_ctrl,
                                                  float * const              p_angle,
                                                  float * const              p_speed,
                                                  float * const              p_phase_err)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_angle);
    FSP_ASSERT(p_speed);
    FSP_ASSERT(p_phase_err);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    *p_angle     = p_instance_ctrl->f_angle_radian;
    *p_speed     = p_instance_ctrl->current.f_speed_radian;
    *p_phase_err = p_instance_ctrl->current.f_position_radian;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Angle Adjustment Process. Implements @ref motor_angle_api_t::angleAdjust
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_AngleAdjust (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if ((MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE == p_instance_ctrl->u1_angle_adjust_status) ||
        (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE == p_instance_ctrl->u1_angle_adjust_status))
    {
        rm_motor_sense_induction_angle_adjust_excite(p_instance_ctrl);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Encoder Cyclic Process (Call in cyclic timer). Implements @ref motor_angle_api_t::encoderCyclic
 *
 * @retval FSP_ERR_UNSUPPORTED      Motor sense induction software encoderCyclic is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_EncoderCyclic (motor_angle_ctrl_t * const p_ctrl)
{
    /* This function isn't supported.  It is defined only to implement a required function of motor_angle_api_t.
     * Mark the input parameter as unused since this function isn't supported. */

    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Induction sensor Cyclic Process (Call in cyclic timer). Implements @ref motor_angle_api_t::cyclicProcess
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_CyclicProcess (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_sense_induction_cyclic(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets information of Angle Module. Implements @ref motor_angle_api_t::infoGet
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_InfoGet (motor_angle_ctrl_t * const         p_ctrl,
                                            motor_angle_encoder_info_t * const p_info)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

    uint8_t temp      = MOTOR_SENSE_INDUCTION_OPENLOOP_INACTIVE;
    uint8_t temp_full = 0U;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_info);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    p_info->e_adjust_status = (motor_sense_encoder_angle_adjust_t) p_instance_ctrl->u1_angle_adjust_status;
    temp_full               = p_instance_ctrl->u1_angle_adjustment_flag;

    p_info->u1_adjust_count_full = temp_full;

    if (MOTOR_SENSE_INDUCTION_OPENLOOP_ACTIVE == p_instance_ctrl->u1_openloop_trigger)
    {
        p_info->f_openloop_speed  = p_extended_cfg->f_openloop_speed_rpm;
        p_info->f_openloop_id_ref = p_extended_cfg->f_openloop_id_ref;

        temp = MOTOR_SENSE_INDUCTION_OPENLOOP_ACTIVE;
    }
    else
    {
        p_info->f_openloop_speed  = 0.0F;
        p_info->f_openloop_id_ref = 0.0F;
    }

    p_info->e_open_loop_status = (motor_angle_open_loop_t) temp;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Reset to restart calibration Angle module.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_CorrectReset (motor_angle_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_sense_induction_init(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Gets the error information about induction correction.
 *
 * @retval FSP_SUCCESS              Successfully data calculated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_ErrorGet (motor_angle_ctrl_t * const p_ctrl, motor_angle_error_t * const p_error)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_error);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (MOTOR_SENSE_INDUCTION_ERROR_FINISH == p_instance_ctrl->u1_correct_status)
    {
        *p_error = MOTOR_ANGLE_ERROR_INDUCTION;
    }
    else
    {
        *p_error = MOTOR_ANGLE_ERROR_NONE;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of angle & speed calculation. Implements @ref motor_angle_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data is update.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_ParameterUpdate (motor_angle_ctrl_t * const      p_ctrl,
                                                    motor_angle_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_cfg->p_extend;

    p_instance_ctrl->e_loop_mode = p_extended_cfg->e_loop_mode;

    p_instance_ctrl->f_current_ctrl_period =
        1.0F / (p_extended_cfg->f_current_frequency * MOTOR_SENSE_INDUCTION_CALCULATE_KHz);

    p_instance_ctrl->f_adc_scaling =
        p_extended_cfg->f_reference_voltage / p_extended_cfg->f_ad_conversion_scale;

    p_instance_ctrl->f_inverse_polepairs = 1.0F / p_extended_cfg->u1_induction_polepairs;

    p_instance_ctrl->f_openloop_speed =
        (p_extended_cfg->f_openloop_speed_rpm * MOTOR_SENSE_INDUCTION_TWOPI) / MOTOR_SENSE_INDUCTION_CALCULATE_60;

    p_instance_ctrl->f_calibration_period =
        (MOTOR_SENSE_INDUCTION_CALCULATE_60 / p_extended_cfg->f_openloop_speed_rpm) *
        p_instance_ctrl->f_current_ctrl_period / (float) p_extended_cfg->u1_get_timing_count;

    p_instance_ctrl->f_get_adc_resolution =
        (p_extended_cfg->f_openloop_speed_rpm * MOTOR_SENSE_INDUCTION_CALCULATE_SIX) *
        (p_instance_ctrl->f_current_ctrl_period * (float) p_extended_cfg->u1_get_timing_count);

    p_instance_ctrl->u2_adc_sample_count =
        (uint16_t) (MOTOR_SENSE_INDUCTION_CALCULATE_360 / p_instance_ctrl->f_get_adc_resolution);

    rm_motor_sense_induction_init(p_instance_ctrl);

    p_instance_ctrl->p_cfg = p_cfg;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set A/D Converted Data. Implements @ref motor_angle_api_t::sensorDataSet
 *
 * @retval FSP_SUCCESS              Successfully data is update.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_SensorDataSet (motor_angle_ctrl_t * const    p_ctrl,
                                                  motor_angle_ad_data_t * const p_ad_data)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_sense_induction_instance_ctrl_t * p_instance_ctrl = (motor_sense_induction_instance_ctrl_t *) p_ctrl;

#if (MOTOR_SENSE_INDUCTION_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_ad_data);
    MOTOR_SENSE_INDUCTION_ERROR_RETURN(MOTOR_SENSE_INDUCTION_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->f_sense_sin_adc = p_ad_data->sin_ad_data;
    p_instance_ctrl->f_sense_cos_adc = p_ad_data->cos_ad_data;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set d/q-axis Current Data & Voltage Reference. Implements @ref motor_angle_api_t::currentSet
 *
 * @retval FSP_ERR_UNSUPPORTED      Motor sense induction software currentSet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_CurrentSet (motor_angle_ctrl_t * const              p_ctrl,
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
 * @retval FSP_ERR_UNSUPPORTED      Motor sense induction software speedSet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_SpeedSet (motor_angle_ctrl_t * const p_ctrl,
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
 * @retval FSP_ERR_UNSUPPORTED      Motor sense induction software flagPiCtrlSet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_FlagPiCtrlSet (motor_angle_ctrl_t * const p_ctrl, uint32_t const flag_pi)
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
 * @retval FSP_ERR_UNSUPPORTED       Motor sense induction software estimatedComponentGet is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_SENSE_INDUCTION_EstimatedComponentGet (motor_angle_ctrl_t * const p_ctrl,
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
 * @} (end addtogroup MOTOR_SENSE_INDUCTION)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_cyclic
 * Description   : Cyclic process of induction sensor (Call at timer interrupt)
 * Arguments     : p_instance_ctrl - The pointer to control instance structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_cyclic (motor_sense_induction_instance_ctrl_t * p_instance_ctrl)
{
    /* This process works only at Initialization */
    if (p_instance_ctrl->e_move_mode != MOTOR_SENSE_INDUCTION_MODE_DRIVE)
    {
        /* After forced drawing of the rotor */
        if ((MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH == p_instance_ctrl->u1_angle_adjust_status) ||
            (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_OPENLOOP == p_instance_ctrl->u1_angle_adjust_status))
        {
            /* After the finish of induction sensor error correnction */
            if (MOTOR_SENSE_INDUCTION_CORRECT_FINISH == p_instance_ctrl->u1_correct_status)
            {
                rm_motor_sense_induction_initial_position_adjust(p_instance_ctrl);
                p_instance_ctrl->e_move_mode = MOTOR_SENSE_INDUCTION_MODE_DRIVE;
            }
            /* Start induction sensor error correction */
            else if (MOTOR_SENSE_INDUCTION_PREPARED == p_instance_ctrl->u1_correct_status)
            {
                p_instance_ctrl->u1_correct_status   = MOTOR_SENSE_INDUCTION_RUNNING;
                p_instance_ctrl->u1_openloop_trigger = MOTOR_SENSE_INDUCTION_OPENLOOP_ACTIVE;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_init
 * Description   : Initialize variables when control init
 * Arguments     : p_ctrl  - control structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_init (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    p_ctrl->u1_correct_status            = MOTOR_SENSE_INDUCTION_PREPARED;
    p_ctrl->u1_calibration_status        = MOTOR_SENSE_INDUCTION_INIT;
    p_ctrl->u1_calibration_count         = MOTOR_SENSE_INDUCTION_CALIBRATION_NONE;
    p_ctrl->u2_signal_maximum_difference = 0U;
    p_ctrl->s2_cycle_counter             = 0;
    p_ctrl->f_pre_position_radian        = 0.0F;

    rm_motor_sense_induction_info_reset(&(p_ctrl->sin));
    rm_motor_sense_induction_info_reset(&(p_ctrl->cos));

    p_ctrl->f_add_cos_sin_maximum    = 0.0F;
    p_ctrl->f_add_cos_sin_minimum    = 0.0F;
    p_ctrl->f_sub_cos_sin_maximum    = 0.0F;
    p_ctrl->f_sub_cos_sin_minimum    = 0.0F;
    p_ctrl->f_sin_offset             = 0.0F;
    p_ctrl->f_cos_offset             = 0.0F;
    p_ctrl->f_sin_gain               = 0.0F;
    p_ctrl->f_cos_gain               = 0.0F;
    p_ctrl->f_induction_phase_offset = 0.0F;
    p_ctrl->f_add_cos_sin_gain       = 0.0F;
    p_ctrl->f_sub_cos_sin_gain       = 0.0F;
    p_ctrl->f_position_offset_radian = 0.0F;

    rm_motor_sense_induction_reset(p_ctrl);
}                                      /* End of function rm_motor_sense_induction_init */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_reset
 * Description   : Reset variables when control
 * Arguments     : p_ctrl  - control structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_reset (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    p_ctrl->e_move_mode                = MOTOR_SENSE_INDUCTION_MODE_INIT;
    p_ctrl->u1_openloop_trigger        = MOTOR_SENSE_INDUCTION_OPENLOOP_INACTIVE;
    p_ctrl->u1_sensor_count            = 0U;
    p_ctrl->u1_speed_calculate_counter = 0U;
    p_ctrl->u1_angle_adjust_status     = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE;
    p_ctrl->u1_angle_adjustment_flag   = MOTOR_SENSE_INDUCTION_FLAG_CLEAR;
    p_ctrl->u2_angle_adjustment_count  = 0U;
    p_ctrl->u2_get_adc_count           = 0U;
    p_ctrl->current.f_position_radian  = 0.0F;
    p_ctrl->previous.f_position_radian = 0.0F;
    p_ctrl->current.f_speed_radian     = 0.0F;
    p_ctrl->previous.f_speed_radian    = 0.0F;
    p_ctrl->current.f_angle_openloop   = 0.0F;
    p_ctrl->previous.f_angle_openloop  = 0.0F;
    p_ctrl->current.f_speed_openloop   = 0.0F;
    p_ctrl->previous.f_speed_openloop  = 0.0F;
}                                      /* End of function rm_motor_sense_induction_reset */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_info_reset
 * Description   : Reset correction data
 * Arguments     : p_info  - induction sensor correnction data structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_info_reset (motor_sense_induction_correct_data_t * p_info)
{
    p_info->f_maximum[0]            = 0.0F;
    p_info->f_maximum[1]            = 0.0F;
    p_info->f_maximum_average       = 0.0F;
    p_info->f_maximum_phase[0]      = 0.0F;
    p_info->f_maximum_phase[1]      = 0.0F;
    p_info->f_maximum_phase_average = 0.0F;
    p_info->f_minimum[0]            = 0.0F;
    p_info->f_minimum[1]            = 0.0F;
    p_info->f_minimum_average       = 0.0F;
    p_info->f_minimum_phase[0]      = 0.0F;
    p_info->f_minimum_phase[1]      = 0.0F;
    p_info->f_minimum_phase_average = 0.0F;
    p_info->f_integral[0]           = 0.0F;
    p_info->f_integral[1]           = 0.0F;
    p_info->f_integral_average      = 0.0F;
    p_info->f_temp_maximum          = 0.0F;
    p_info->f_temp_maximum_phase    = 0.0F;
    p_info->f_temp_minimum          = 0.0F;
    p_info->f_temp_minimum_phase    = 0.0F;
    p_info->f_temp_integral         = 0.0F;
}                                      /* End of function rm_motor_sense_induction_info_reset */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_angle_adjust_excite
 * Description   : Angle adjust with forced excitation
 * Arguments     : p_ctrl  - control structure (pointer)
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_angle_adjust_excite (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (p_ctrl->u2_angle_adjustment_count >= p_extended_cfg->u2_angle_adjustment_time)
    {
        /* Angle adjusted to 90 degree */
        if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE == p_ctrl->u1_angle_adjust_status)
        {
            /* Reset angle adjust counter */
            p_ctrl->u2_angle_adjustment_count = 0U;
            p_ctrl->u1_angle_adjustment_flag  = MOTOR_SENSE_INDUCTION_FLAG_SET;
            p_ctrl->u1_angle_adjust_status    = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE;
        }
        /* Angle adjusted to 0 degree */
        else if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE == p_ctrl->u1_angle_adjust_status)
        {
            p_ctrl->u1_angle_adjustment_flag = MOTOR_SENSE_INDUCTION_FLAG_SET;

            /* When induction sensor error correction is disable, forced to set the status as "FINISH". */
            if ((MOTOR_SENSE_INDUCTION_CALIBRATION_DISABLE == p_extended_cfg->e_calibration) ||
                (MOTOR_SENSE_INDUCTION_CORRECT_FINISH == p_ctrl->u1_correct_status))
            {
                p_ctrl->u1_angle_adjust_status = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH;
                p_ctrl->u1_correct_status      = MOTOR_SENSE_INDUCTION_CORRECT_FINISH;
            }
            else
            {
                p_ctrl->u1_angle_adjust_status = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_OPENLOOP;
                if (MOTOR_SENSE_INDUCTION_CORRECT_FINISH != p_ctrl->u1_correct_status)
                {
                    p_ctrl->u1_openloop_trigger = MOTOR_SENSE_INDUCTION_OPENLOOP_ACTIVE;
                }
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        p_ctrl->u1_angle_adjustment_flag = MOTOR_SENSE_INDUCTION_FLAG_CLEAR;
        p_ctrl->u2_angle_adjustment_count++;
    }
}                                      /* End of function rm_motor_sense_induction_angle_adjust_excite */

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_position_speed_calculation
 * Description   : Calculate rotor position and speed by induction sensor
 * Arguments     : p_ctrl - The pointer to the sense induction module data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_position_speed_calculation (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    float f4_temp0;
    float f4_temp1;
    float f4_sens_sin_adc;
    float f4_sens_cos_adc;
    float f4_angle;
    float f4_pos_err;
    float f4_half_voltage_reference;
    float f4_pos_cnt_error;

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Get ADC for sensor output */
    f4_sens_sin_adc = p_ctrl->f_sense_sin_adc * p_ctrl->f_adc_scaling;
    f4_sens_cos_adc = p_ctrl->f_sense_cos_adc * p_ctrl->f_adc_scaling;

    if (MOTOR_SENSE_INDUCTION_CALIBRATION_ENABLE == p_extended_cfg->e_calibration)
    {
        /* Gain correction */
        f4_sens_sin_adc = (f4_sens_sin_adc - p_ctrl->f_sin_offset) * p_ctrl->f_sin_gain;
        f4_sens_cos_adc = (f4_sens_cos_adc - p_ctrl->f_cos_offset) * p_ctrl->f_cos_gain;

        /* Phase correction */
        f4_temp0 = f4_sens_cos_adc + f4_sens_sin_adc;
        f4_temp1 = f4_sens_cos_adc - f4_sens_sin_adc;
        f4_temp0 = f4_temp0 * p_ctrl->f_add_cos_sin_gain; /* Scaling of sin + cos */
        f4_temp1 = f4_temp1 * p_ctrl->f_sub_cos_sin_gain; /* Scaling of sin - cos */

        /* Angle calculation */
        f4_angle = atan2f(f4_temp1, f4_temp0) + MOTOR_SENSE_INDUCTION_CORRECT_ANGLE;
    }
    else
    {
        f4_half_voltage_reference = p_extended_cfg->f_reference_voltage * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        f4_temp0 = f4_sens_sin_adc - f4_half_voltage_reference; /* Remove for sin wave offset */
        f4_temp1 = f4_sens_cos_adc - f4_half_voltage_reference; /* Remove for cos wave offset */

        /* Angle calculation */
        f4_angle = atan2f(f4_temp1, f4_temp0);
    }

    /* Remove for detection phase offset */
    f4_angle = f4_angle - p_ctrl->f_induction_phase_offset;

    if (f4_angle >= MOTOR_SENSE_INDUCTION_TWOPI)
    {
        f4_angle = f4_angle - MOTOR_SENSE_INDUCTION_TWOPI;
    }
    else if (f4_angle < 0.0F)
    {
        f4_angle = f4_angle + MOTOR_SENSE_INDUCTION_TWOPI;
    }
    else
    {
        /* Do nothing */
    }

    /* Induction sensor angle cycle count */
    f4_pos_cnt_error = p_ctrl->f_pre_position_radian - f4_angle;
    if (f4_pos_cnt_error >= MOTOR_SENSE_INDUCTION_ONEPI)
    {
        p_ctrl->s2_cycle_counter++;
    }
    else if (f4_pos_cnt_error <= (-MOTOR_SENSE_INDUCTION_ONEPI))
    {
        p_ctrl->s2_cycle_counter--;
    }
    else
    {
        /* Do Nothing */
    }

    p_ctrl->f_pre_position_radian = f4_angle;

    if (MOTOR_SENSE_INDUCTION_LOOP_SPEED == p_ctrl->e_loop_mode)
    {
        /* Completion of induction sensor angle calculation */
        p_ctrl->current.f_position_radian = f4_angle;
    }
    else if (MOTOR_SENSE_INDUCTION_LOOP_POSITION == p_ctrl->e_loop_mode)
    {
        /* Completion of induction sensor angle calculation */
        p_ctrl->current.f_position_radian = f4_angle + (p_ctrl->s2_cycle_counter * MOTOR_SENSE_INDUCTION_TWOPI);
    }
    else
    {
        /* Do Nothing */
    }

    /* Speed calculation timing adjustment */
    if (p_extended_cfg->u1_speed_detection_count == p_ctrl->u1_speed_calculate_counter)
    {
        /* Calculation of position deviation */
        f4_pos_err = p_ctrl->current.f_position_radian - p_ctrl->previous.f_position_radian;

        if (fabsf(f4_pos_err) > MOTOR_SENSE_INDUCTION_ONEPI)
        {
            f4_pos_err = copysignf((fabsf(f4_pos_err) - MOTOR_SENSE_INDUCTION_TWOPI), -f4_pos_err);
        }

        f4_temp0 = f4_pos_err /
                   (p_ctrl->f_current_ctrl_period * (float) (p_extended_cfg->u1_speed_detection_count + 1));

        /* Smoothed by low pass filter */
        p_ctrl->current.f_speed_radian =
            rm_motor_sense_induction_lpff(f4_temp0, p_ctrl->previous.f_speed_radian, p_extended_cfg->f_speed_lpf);
        p_ctrl->previous.f_position_radian = p_ctrl->current.f_position_radian;
        p_ctrl->previous.f_speed_radian    = p_ctrl->current.f_speed_radian;
        p_ctrl->u1_speed_calculate_counter = 0;
    }
    else
    {
        p_ctrl->u1_speed_calculate_counter++;
    }
}

/**********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_angle_speed
 * Description   : Angle and speed detection by induction sensor
 * Arguments     : p_ctrl - The pointer to the sense induction module data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_angle_speed (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    float f4_angle_rad = 0.0F;

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* At the rotor initializing */
    if (MOTOR_SENSE_INDUCTION_MODE_INIT == p_ctrl->e_move_mode)
    {
        if (MOTOR_SENSE_INDUCTION_RUNNING == p_ctrl->u1_correct_status)
        {
            /* Induction sensor correction get ADC */
            rm_motor_sense_induction_correction_sequence(p_ctrl);

            /* Open loop operation while acquiring the correction data of the induction sensor */
            if (MOTOR_SENSE_INDUCTION_OPENLOOP_ACTIVE == p_ctrl->u1_openloop_trigger)
            {
                f4_angle_rad  = p_ctrl->f_angle_radian;
                f4_angle_rad += (p_ctrl->f_openloop_speed * p_ctrl->f_current_ctrl_period);
            }
        }
        else
        {
            /* speed must be zero while adjusting angle */
            p_ctrl->current.f_speed_radian = 0.0F;
            if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_90_DEGREE == p_ctrl->u1_angle_adjust_status)
            {
                /* set alignment angle to PI/2[rad] */
                f4_angle_rad = MOTOR_SENSE_INDUCTION_HALF_PI;
            }
            else if (MOTOR_SENSE_ENCODER_ANGLE_ADJUST_0_DEGREE == p_ctrl->u1_angle_adjust_status)
            {
                /* set alignment angle to 0[rad] */
                f4_angle_rad = 0.0F;
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
    /* Normal rotation */
    else if (MOTOR_SENSE_INDUCTION_MODE_DRIVE == p_ctrl->e_move_mode)
    {
        p_ctrl->current.f_speed_radian *=
            (p_ctrl->f_inverse_polepairs * p_extended_cfg->u1_motor_polepairs);
        p_ctrl->current.f_position_radian *= p_ctrl->f_inverse_polepairs;
        f4_angle_rad = fmodf((p_ctrl->current.f_position_radian * p_extended_cfg->u1_motor_polepairs),
                             MOTOR_SENSE_INDUCTION_TWOPI);
    }
    else
    {
        /* Do Nothing */
    }

    if (f4_angle_rad >= MOTOR_SENSE_INDUCTION_TWOPI)
    {
        f4_angle_rad = f4_angle_rad - MOTOR_SENSE_INDUCTION_TWOPI;
    }
    else if (f4_angle_rad < 0.0F)
    {
        f4_angle_rad = f4_angle_rad + MOTOR_SENSE_INDUCTION_TWOPI;
    }
    else
    {
        /* Do nothing */
    }

    p_ctrl->f_angle_radian = f4_angle_rad;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_correction_sequence
 * Description   : Correction sequence processing of induction sensor
 * Arguments     : p_ctrl - The pointer to the sense induction module data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_correction_sequence (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    uint16_t u2_temp;

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    switch (p_ctrl->u1_calibration_status)
    {
        /* Initialize of Error correction */
        case MOTOR_SENSE_INDUCTION_INIT:
        {
            /* Sequence status update */
            p_ctrl->u1_calibration_status = MOTOR_SENSE_INDUCTION_DATA_GET_ERR_CORRECT;
            p_ctrl->u1_calibration_count  = MOTOR_SENSE_INDUCTION_GET_SIGNAL_1ST;
            break;
        }

        /* Acquisition and calculation of error correction data */
        case MOTOR_SENSE_INDUCTION_DATA_GET_ERR_CORRECT:
        {
            switch (p_ctrl->u1_calibration_count)
            {
                case MOTOR_SENSE_INDUCTION_GET_SIGNAL_1ST: /* First time to get sensor output value */
                case MOTOR_SENSE_INDUCTION_GET_SIGNAL_2ND: /* Second time to get sensor output value */
                {
                    /* Get gain calibration data */
                    rm_motor_sense_induction_get_data_for_gain_calibration(p_ctrl);
                    break;
                }

                case MOTOR_SENSE_INDUCTION_GAIN_CORRECTION:  /* Processing gain correction */
                case MOTOR_SENSE_INDUCTION_PHASE_CORRECTION: /* Processing phase correction */
                {
                    /* Gain or phase error correction */
                    rm_motor_sense_induction_correction(p_ctrl);
                    break;
                }

                case MOTOR_SENSE_INDUCTION_GET_PHASE_DATA: /* Get data for phase correction */
                {
                    /* Get phase calibration data */
                    rm_motor_sense_induction_get_data_phase_calibration(p_ctrl);
                    break;
                }

                case MOTOR_SENSE_INDUCTION_CALIBRATION_FINISH: /* Calibration finish */
                {
                    p_ctrl->u1_openloop_trigger   = MOTOR_SENSE_INDUCTION_OPENLOOP_INACTIVE;
                    p_ctrl->u1_calibration_status = MOTOR_SENSE_INDUCTION_RESULT_JUDGE;
                    p_ctrl->u1_calibration_count  = MOTOR_SENSE_INDUCTION_CALIBRATION_NONE;
                    break;
                }

                default:
                {
                    p_ctrl->u1_calibration_count = MOTOR_SENSE_INDUCTION_CALIBRATION_NONE;
                    break;
                }
            }

            break;
        }

        case MOTOR_SENSE_INDUCTION_RESULT_JUDGE:
        {
            /* Validity confirmation of acquired value */
            /* Data comparison of max sin value */
            p_ctrl->u2_signal_maximum_difference =
                (uint16_t) fabsf(p_ctrl->sin.f_maximum[0] - p_ctrl->sin.f_maximum[1]);

            /* Find the maximum difference */
            /* Data comparison of min sin value */
            u2_temp = (uint16_t) fabsf(p_ctrl->sin.f_minimum[0] - p_ctrl->sin.f_minimum[1]);
            if (u2_temp > p_ctrl->u2_signal_maximum_difference)
            {
                p_ctrl->u2_signal_maximum_difference = u2_temp;
            }

            /* Data comparison of max cos value */
            u2_temp = (uint16_t) fabsf(p_ctrl->cos.f_maximum[0] - p_ctrl->cos.f_maximum[1]);
            if (u2_temp > p_ctrl->u2_signal_maximum_difference)
            {
                p_ctrl->u2_signal_maximum_difference = u2_temp;
            }

            /* Data comparison of min cos value */
            u2_temp = (uint16_t) fabsf(p_ctrl->cos.f_minimum[0] - p_ctrl->cos.f_minimum[1]);
            if (u2_temp > p_ctrl->u2_signal_maximum_difference)
            {
                p_ctrl->u2_signal_maximum_difference = u2_temp;
            }

            if (p_ctrl->u2_signal_maximum_difference < p_extended_cfg->u2_signal_error_limit)
            {
                /* Finish the error correction process normaly */
                p_ctrl->u1_correct_status      = MOTOR_SENSE_INDUCTION_CORRECT_FINISH;
                p_ctrl->u1_angle_adjust_status = MOTOR_SENSE_ENCODER_ANGLE_ADJUST_FINISH;
            }
            else
            {
                /* Error end processing */
                p_ctrl->u1_correct_status = MOTOR_SENSE_INDUCTION_ERROR_FINISH;
            }

            p_ctrl->u1_calibration_status = MOTOR_SENSE_INDUCTION_CALIB_SEQ_FIN;
            break;
        }

        default:
        {
            break;
        }
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_get_data_for_gain_calibration
 * Description   : Get output signal of induction sensor
 * Arguments     : p_ctrl - The pointer to the sense induction module data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_get_data_for_gain_calibration (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    float f4_temp0                  = 0.0F;
    float f4_temp1                  = 0.0F;
    float f4_sens_sin_adc           = 0.0F;
    float f4_sens_cos_adc           = 0.0F;
    float f4_half_voltage_reference = 0.0F;

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Completed getting data for one lap */
    if (p_ctrl->u2_get_adc_count >= p_ctrl->u2_adc_sample_count)
    {
        /* Processing after data acquisition */
        p_ctrl->u2_get_adc_count           = 0U;
        p_ctrl->u1_sensor_count            = 0U;
        p_ctrl->u1_speed_calculate_counter = 0U;

        /* Get 1st data */
        if (MOTOR_SENSE_INDUCTION_GET_SIGNAL_1ST == p_ctrl->u1_calibration_count)
        {
            p_ctrl->sin.f_maximum[0]       = p_ctrl->sin.f_temp_maximum;
            p_ctrl->sin.f_maximum_phase[0] = p_ctrl->sin.f_temp_maximum_phase;
            p_ctrl->sin.f_minimum[0]       = p_ctrl->sin.f_temp_minimum;
            p_ctrl->sin.f_minimum_phase[0] = p_ctrl->sin.f_temp_minimum_phase;
            p_ctrl->cos.f_maximum[0]       = p_ctrl->cos.f_temp_maximum;
            p_ctrl->cos.f_maximum_phase[0] = p_ctrl->sin.f_temp_maximum_phase;
            p_ctrl->cos.f_minimum[0]       = p_ctrl->cos.f_temp_minimum;
            p_ctrl->cos.f_minimum_phase[0] = p_ctrl->cos.f_temp_minimum_phase;
            p_ctrl->sin.f_integral[0]      = p_ctrl->sin.f_temp_integral * p_ctrl->f_calibration_period;
            p_ctrl->cos.f_integral[0]      = p_ctrl->cos.f_temp_integral * p_ctrl->f_calibration_period;
        }
        /* Get 2nd data */
        else if (MOTOR_SENSE_INDUCTION_GET_SIGNAL_2ND == p_ctrl->u1_calibration_count)
        {
            p_ctrl->sin.f_maximum[1]       = p_ctrl->sin.f_temp_maximum;
            p_ctrl->sin.f_maximum_phase[1] = p_ctrl->sin.f_temp_maximum_phase;
            p_ctrl->sin.f_minimum[1]       = p_ctrl->sin.f_temp_minimum;
            p_ctrl->sin.f_minimum_phase[1] = p_ctrl->sin.f_temp_minimum_phase;
            p_ctrl->cos.f_maximum[1]       = p_ctrl->cos.f_temp_maximum;
            p_ctrl->cos.f_maximum_phase[1] = p_ctrl->sin.f_temp_maximum_phase;
            p_ctrl->cos.f_minimum[1]       = p_ctrl->cos.f_temp_minimum;
            p_ctrl->cos.f_minimum_phase[1] = p_ctrl->cos.f_temp_minimum_phase;
            p_ctrl->sin.f_integral[1]      = p_ctrl->sin.f_temp_integral * p_ctrl->f_calibration_period;
            p_ctrl->cos.f_integral[1]      = p_ctrl->cos.f_temp_integral * p_ctrl->f_calibration_period;
        }
        else
        {
            /* Do nothing */
        }

        /* Initialize temporary variables of sin */
        p_ctrl->sin.f_temp_maximum       = 0.0F;
        p_ctrl->sin.f_temp_maximum_phase = 0.0F;
        p_ctrl->sin.f_temp_minimum       = 0.0F;
        p_ctrl->sin.f_temp_minimum_phase = 0.0F;
        p_ctrl->sin.f_temp_integral      = 0.0F;

        /* Initialize temporary variables of cos */
        p_ctrl->cos.f_temp_maximum       = 0.0F;
        p_ctrl->cos.f_temp_maximum_phase = 0.0F;
        p_ctrl->cos.f_temp_minimum       = 0.0F;
        p_ctrl->cos.f_temp_minimum_phase = 0.0F;
        p_ctrl->cos.f_temp_integral      = 0.0F;
        p_ctrl->u1_calibration_count++;
    }
    else
    {
        if (0U == p_ctrl->u1_sensor_count)
        {
            /* Get ADC for sensor output */
            f4_sens_sin_adc = p_ctrl->f_sense_sin_adc;
            f4_sens_cos_adc = p_ctrl->f_sense_cos_adc;

            /* angle calcuration in open loop */
            /* scaling of sin signal */
            f4_half_voltage_reference = p_extended_cfg->f_reference_voltage * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
            f4_temp0 = (f4_sens_sin_adc * p_ctrl->f_adc_scaling) - f4_half_voltage_reference;

            /* scaling of cos signal */
            f4_temp1 = (f4_sens_cos_adc * p_ctrl->f_adc_scaling) - f4_half_voltage_reference;
            p_ctrl->current.f_angle_openloop = atan2f(f4_temp1, f4_temp0);
            if (p_ctrl->current.f_angle_openloop >= MOTOR_SENSE_INDUCTION_TWOPI)
            {
                p_ctrl->current.f_angle_openloop -= MOTOR_SENSE_INDUCTION_TWOPI;
            }
            else if (p_ctrl->current.f_angle_openloop < 0.0F)
            {
                p_ctrl->current.f_angle_openloop += MOTOR_SENSE_INDUCTION_TWOPI;
            }
            else
            {
                /* Do nothing */
            }

            if (p_extended_cfg->u1_speed_detection_count == p_ctrl->u1_speed_calculate_counter)
            {
                f4_temp1 = p_ctrl->current.f_angle_openloop - p_ctrl->previous.f_angle_openloop;
                if (fabsf(f4_temp1) > MOTOR_SENSE_INDUCTION_ONEPI)
                {
                    f4_temp1 = copysignf((fabsf(f4_temp1) - MOTOR_SENSE_INDUCTION_TWOPI), f4_temp1);
                }

                f4_temp0 = f4_temp1 /
                           (p_ctrl->f_current_ctrl_period * (float) (p_extended_cfg->u1_speed_detection_count + 1));

                if (isnan(f4_temp0))
                {
                    f4_temp0 = 0.0F;
                }

                p_ctrl->current.f_speed_openloop = rm_motor_sense_induction_lpff(f4_temp0,
                                                                                 p_ctrl->previous.f_speed_openloop,
                                                                                 p_extended_cfg->f_speed_lpf);
                p_ctrl->previous.f_angle_openloop  = p_ctrl->current.f_angle_openloop;
                p_ctrl->u1_speed_calculate_counter = 0U;
            }
            else
            {
                p_ctrl->u1_speed_calculate_counter++;
            }

            p_ctrl->current.f_angle_openloop =
                fmodf((p_ctrl->current.f_angle_openloop * p_extended_cfg->u1_motor_polepairs),
                      MOTOR_SENSE_INDUCTION_TWOPI);

            /* angle calcuration end */

            /* Calculate integral value of sensor signal */
            p_ctrl->sin.f_temp_integral += f4_sens_sin_adc;
            p_ctrl->cos.f_temp_integral += f4_sens_cos_adc;

            if (0U == p_ctrl->u2_get_adc_count)
            {
                p_ctrl->sin.f_temp_maximum = f4_sens_sin_adc;
                p_ctrl->sin.f_temp_minimum = f4_sens_sin_adc;
                p_ctrl->cos.f_temp_maximum = f4_sens_cos_adc;
                p_ctrl->cos.f_temp_minimum = f4_sens_cos_adc;
            }
            else
            {
                /* Search max and min value and angle of sin signal */
                /* Find the maximum value */
                if (p_ctrl->sin.f_temp_maximum < f4_sens_sin_adc)
                {
                    p_ctrl->sin.f_temp_maximum = f4_sens_sin_adc;

                    /* Convert to degree */
                    p_ctrl->sin.f_temp_maximum_phase = p_ctrl->u2_get_adc_count * p_ctrl->f_get_adc_resolution;
                }
                /* Find the minimum value */
                else if (p_ctrl->sin.f_temp_minimum > f4_sens_sin_adc)
                {
                    p_ctrl->sin.f_temp_minimum = f4_sens_sin_adc;

                    /* Convert to degree */
                    p_ctrl->sin.f_temp_minimum_phase = p_ctrl->u2_get_adc_count * p_ctrl->f_get_adc_resolution;
                }
                else
                {
                    /* Do nothing */
                }

                /* Search max and min value and angle of cos signal */
                /* Find the maximum value */
                if (p_ctrl->cos.f_temp_maximum < f4_sens_cos_adc)
                {
                    p_ctrl->cos.f_temp_maximum = f4_sens_cos_adc;

                    /* Convert to degree */
                    p_ctrl->cos.f_temp_maximum_phase = p_ctrl->u2_get_adc_count * p_ctrl->f_get_adc_resolution;
                }
                /* Find the minimum value */
                else if (p_ctrl->cos.f_temp_minimum > f4_sens_cos_adc)
                {
                    p_ctrl->cos.f_temp_minimum = f4_sens_cos_adc;

                    /* Convert to degree */
                    p_ctrl->cos.f_temp_minimum_phase = p_ctrl->u2_get_adc_count * p_ctrl->f_get_adc_resolution;
                }
                else
                {
                    /* Do nothing */
                }
            }

            p_ctrl->u1_sensor_count++;  /* increment counter for data acquisition timing */
            p_ctrl->u2_get_adc_count++; /* increment counter for angle information */
        }
        else
        {
            p_ctrl->u1_sensor_count++;
            if (p_extended_cfg->u1_get_timing_count == p_ctrl->u1_sensor_count)
            {
                p_ctrl->u1_sensor_count = 0U;
            }
        }
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_correction
 * Description   : Error correction of induction sensor
 * Arguments     : p_ctrl - The pointer to the sense induction module data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_correction (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    float f4_temp_sin_gain = 0.0F;
    float f4_temp_cos_gain = 0.0F;
    float f4_temp_gain     = 0.0F;

    /* Gain correction process */
    if (MOTOR_SENSE_INDUCTION_GAIN_CORRECTION == p_ctrl->u1_calibration_count)
    {
        /* Convert to the value used for correction */
        p_ctrl->sin.f_maximum_average =
            (p_ctrl->sin.f_maximum[0] + p_ctrl->sin.f_maximum[1]) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        p_ctrl->sin.f_minimum_average =
            (p_ctrl->sin.f_minimum[0] + p_ctrl->sin.f_minimum[1]) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        p_ctrl->cos.f_maximum_average =
            (p_ctrl->cos.f_maximum[0] + p_ctrl->cos.f_maximum[1]) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        p_ctrl->cos.f_minimum_average =
            (p_ctrl->cos.f_minimum[0] + p_ctrl->cos.f_minimum[1]) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        p_ctrl->sin.f_integral_average =
            (p_ctrl->sin.f_integral[0] + p_ctrl->sin.f_integral[1]) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        p_ctrl->cos.f_integral_average =
            (p_ctrl->cos.f_integral[0] + p_ctrl->cos.f_integral[1]) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;

        /* offset rejection */
        p_ctrl->f_sin_offset = p_ctrl->sin.f_integral_average * p_ctrl->f_adc_scaling;
        p_ctrl->f_cos_offset = p_ctrl->cos.f_integral_average * p_ctrl->f_adc_scaling;

        /* gain correction */
        f4_temp_sin_gain =
            (p_ctrl->sin.f_maximum_average - p_ctrl->sin.f_minimum_average) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        f4_temp_cos_gain =
            (p_ctrl->cos.f_maximum_average - p_ctrl->cos.f_minimum_average) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        f4_temp_sin_gain  *= p_ctrl->f_adc_scaling;
        f4_temp_cos_gain  *= p_ctrl->f_adc_scaling;
        p_ctrl->f_sin_gain = 1.0F / f4_temp_sin_gain; /* Inverse value to reduce CPU process */
        p_ctrl->f_cos_gain = 1.0F / f4_temp_cos_gain; /* Inverse value to reduce CPU process */
    }
    /* Phase correction process */
    else if (MOTOR_SENSE_INDUCTION_PHASE_CORRECTION == p_ctrl->u1_calibration_count)
    {
        f4_temp_gain =
            (p_ctrl->f_add_cos_sin_maximum - p_ctrl->f_add_cos_sin_minimum) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        p_ctrl->f_add_cos_sin_gain = 1.0F / f4_temp_gain; /* Inverse value to reduce CPU process */
        f4_temp_gain               =
            (p_ctrl->f_sub_cos_sin_maximum - p_ctrl->f_sub_cos_sin_minimum) * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        p_ctrl->f_sub_cos_sin_gain = 1.0F / f4_temp_gain; /* Inverse value to reduce CPU process */
    }
    else
    {
        /* Do nothing */
    }

    /* Update status of calibration */
    p_ctrl->u1_calibration_count++;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_get_data_phase_calibration
 * Description   : Obtain the output signal of the induction sensor for phase error correction
 * Arguments     : p_ctrl - The pointer to the sense induction module data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_get_data_phase_calibration (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    float f4_temp0                  = 0.0F;
    float f4_temp1                  = 0.0F;
    float f4_sens_sin_adc           = 0.0F;
    float f4_sens_cos_adc           = 0.0F;
    float f4_pos_err                = 0.0F;
    float f4_half_voltage_reference = 0.0F;

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Completed getting data for one lap */
    if (p_ctrl->u2_get_adc_count >= p_ctrl->u2_adc_sample_count)
    {
        /* Processing after data acquisition */
        /* Do not allow open loop operation */
        p_ctrl->u2_get_adc_count           = 0U;
        p_ctrl->u1_sensor_count            = 0U;
        p_ctrl->u1_speed_calculate_counter = 0U;
        p_ctrl->u1_calibration_count++;
    }
    else
    {
        if (0U == p_ctrl->u1_sensor_count)
        {
            /* Get ADC for sensor output */
            f4_sens_sin_adc = p_ctrl->f_sense_sin_adc;
            f4_sens_cos_adc = p_ctrl->f_sense_cos_adc;

            /* angle calcuration in open loop */
            f4_half_voltage_reference = p_extended_cfg->f_reference_voltage * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
            f4_temp0 = (f4_sens_sin_adc * p_ctrl->f_adc_scaling) - f4_half_voltage_reference;
            f4_temp1 = (f4_sens_cos_adc * p_ctrl->f_adc_scaling) - f4_half_voltage_reference;
            p_ctrl->current.f_angle_openloop = atan2f(f4_temp1, f4_temp0);
            if (p_ctrl->current.f_angle_openloop >= MOTOR_SENSE_INDUCTION_TWOPI)
            {
                p_ctrl->current.f_angle_openloop -= MOTOR_SENSE_INDUCTION_TWOPI;
            }
            else if (p_ctrl->current.f_angle_openloop < 0.0F)
            {
                p_ctrl->current.f_angle_openloop += MOTOR_SENSE_INDUCTION_TWOPI;
            }
            else
            {
                /* Do nothing */
            }

            if (p_extended_cfg->u1_speed_detection_count == p_ctrl->u1_speed_calculate_counter)
            {
                f4_pos_err = p_ctrl->current.f_angle_openloop - p_ctrl->previous.f_angle_openloop;
                if (fabsf(f4_pos_err) > MOTOR_SENSE_INDUCTION_ONEPI)
                {
                    f4_pos_err = copysignf((fabsf(f4_pos_err) - MOTOR_SENSE_INDUCTION_TWOPI), f4_pos_err);
                }

                f4_temp0 = f4_pos_err /
                           (p_ctrl->f_current_ctrl_period * (float) (p_extended_cfg->u1_speed_detection_count + 1U));

                if (isnan(f4_temp0))
                {
                    f4_temp0 = 0.0F;
                }

                /* Smoothed by low pass filter */
                p_ctrl->current.f_speed_openloop = rm_motor_sense_induction_lpff(f4_temp0,
                                                                                 p_ctrl->previous.f_speed_openloop,
                                                                                 p_extended_cfg->f_speed_lpf);
                p_ctrl->previous.f_angle_openloop  = p_ctrl->current.f_angle_openloop;
                p_ctrl->u1_speed_calculate_counter = 0U;
            }
            else
            {
                p_ctrl->u1_speed_calculate_counter++;
            }

            p_ctrl->current.f_angle_openloop =
                fmodf((p_ctrl->current.f_angle_openloop * p_extended_cfg->u1_motor_polepairs),
                      MOTOR_SENSE_INDUCTION_TWOPI);

            /* angle calcuration end */

            f4_sens_sin_adc = (f4_sens_sin_adc * p_ctrl->f_adc_scaling);
            f4_sens_cos_adc = (f4_sens_cos_adc * p_ctrl->f_adc_scaling);

            /* signal correctin */
            f4_sens_sin_adc = (f4_sens_sin_adc - p_ctrl->f_sin_offset) * p_ctrl->f_sin_gain;
            f4_sens_cos_adc = (f4_sens_cos_adc - p_ctrl->f_cos_offset) * p_ctrl->f_cos_gain;

            f4_temp0 = f4_sens_cos_adc + f4_sens_sin_adc; /* cos + sin signal */
            f4_temp1 = f4_sens_cos_adc - f4_sens_sin_adc; /* cos - sin signal */

            if (0 == p_ctrl->u2_get_adc_count)
            {
                p_ctrl->f_add_cos_sin_maximum = f4_temp0;
                p_ctrl->f_add_cos_sin_minimum = f4_temp0;
                p_ctrl->f_sub_cos_sin_maximum = f4_temp1;
                p_ctrl->f_sub_cos_sin_minimum = f4_temp1;
            }
            else
            {
                /* Search max and min value and angle of cos + sin signal */
                if (p_ctrl->f_add_cos_sin_maximum < f4_temp0)
                {
                    p_ctrl->f_add_cos_sin_maximum = f4_temp0;
                }
                else if (p_ctrl->f_add_cos_sin_minimum > f4_temp0)
                {
                    p_ctrl->f_add_cos_sin_minimum = f4_temp0;
                }
                else
                {
                }

                /* Search max and min value and angle of cos - sin signal end */
                if (p_ctrl->f_sub_cos_sin_maximum < f4_temp1)
                {
                    p_ctrl->f_sub_cos_sin_maximum = f4_temp1;
                }
                else if (p_ctrl->f_sub_cos_sin_minimum > f4_temp1)
                {
                    p_ctrl->f_sub_cos_sin_minimum = f4_temp1;
                }
                else
                {
                }
            }

            p_ctrl->u1_sensor_count++;  /* incriment counter for data acquisition timing */
            p_ctrl->u2_get_adc_count++; /* incriment counter for angle information */
        }
        else
        {
            p_ctrl->u1_sensor_count++;
            if (p_extended_cfg->u1_get_timing_count == p_ctrl->u1_sensor_count)
            {
                p_ctrl->u1_sensor_count = 0U;
            }
        }
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_initial_position_adjust
 * Description   : Initialize position adjustment of induction sensor
 * Arguments     : p_ctrl - The pointer to the sense induction module data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_sense_induction_initial_position_adjust (motor_sense_induction_instance_ctrl_t * p_ctrl)
{
    float f4_temp0                  = 0.0F;
    float f4_temp1                  = 0.0F;
    float f4_sens_sin_adc           = 0.0F;
    float f4_sens_cos_adc           = 0.0F;
    float f4_angle                  = 0.0F;
    float f4_half_voltage_reference = 0.0F;

    motor_sense_induction_extended_cfg_t * p_extended_cfg =
        (motor_sense_induction_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Adjust the position of the motor and sensor */
    f4_sens_sin_adc = p_ctrl->f_sense_sin_adc * p_ctrl->f_adc_scaling;
    f4_sens_cos_adc = p_ctrl->f_sense_cos_adc * p_ctrl->f_adc_scaling;

    if (MOTOR_SENSE_INDUCTION_CALIBRATION_ENABLE == p_extended_cfg->e_calibration)
    {
        /* Gain correction */
        f4_sens_sin_adc = (f4_sens_sin_adc - p_ctrl->f_sin_offset) * p_ctrl->f_sin_gain;
        f4_sens_cos_adc = (f4_sens_cos_adc - p_ctrl->f_cos_offset) * p_ctrl->f_cos_gain;

        /* Phase correction */
        f4_temp0  = f4_sens_cos_adc + f4_sens_sin_adc; /* Make a "cos + sin" signal */
        f4_temp1  = f4_sens_cos_adc - f4_sens_sin_adc; /* Make a "cos - sin" signal */
        f4_temp0 *= p_ctrl->f_add_cos_sin_gain;        /* Scaling of sin + cos */
        f4_temp1 *= p_ctrl->f_sub_cos_sin_gain;        /* Scaling of sin - cos */

        /* Angle calculation */
        f4_angle = atan2f(f4_temp1, f4_temp0) + MOTOR_SENSE_INDUCTION_CORRECT_ANGLE;
    }
    else
    {
        f4_half_voltage_reference = p_extended_cfg->f_reference_voltage * MOTOR_SENSE_INDUCTION_CALCULATE_HALF;
        f4_temp0 = f4_sens_sin_adc - f4_half_voltage_reference; /* Remove for sin wave offset */
        f4_temp1 = f4_sens_cos_adc - f4_half_voltage_reference; /* Remove for cos wave offset */
        f4_angle = atan2f(f4_temp1, f4_temp0);                  /* Angle calculation */
    }

    p_ctrl->f_induction_phase_offset = f4_angle;
    if (p_ctrl->f_induction_phase_offset >= MOTOR_SENSE_INDUCTION_TWOPI)
    {
        p_ctrl->f_induction_phase_offset -= MOTOR_SENSE_INDUCTION_TWOPI;
    }
    else if (p_ctrl->f_induction_phase_offset < 0.0F)
    {
        p_ctrl->f_induction_phase_offset += MOTOR_SENSE_INDUCTION_TWOPI;
    }
    else
    {
        /* Do nothing */
    }
}

/***********************************************************************************************************************
 * Function Name : rm_motor_sense_induction_lpff
 * Description   : LPF process
 * Arguments     : f4_lpf_input      - LPF input value
 *                f4_pre_lpf_output - Previous LPF output value
 *                f4_lpf_k          - LPF parameter
 * Return Value  : LPF output value
 **********************************************************************************************************************/
static float rm_motor_sense_induction_lpff (float f4_lpf_input, float f4_pre_lpf_output, float f4_lpf_k)
{
    float f4_temp;

    f4_temp = f4_pre_lpf_output + (f4_lpf_k * (f4_lpf_input - f4_pre_lpf_output));

    return f4_temp;
}                                      /* End of function rm_motor_sense_induction_lpff */
