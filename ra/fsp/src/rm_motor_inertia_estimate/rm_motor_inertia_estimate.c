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
#include "rm_motor_inertia_estimate.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_INERTIA_ESTIMATE_OPEN                (('M' << 24U) | ('T' << 16U) | ('I' << 8U) | ('E' << 0U))

#define     MOTOR_INERTIA_ESTIMATE_TWO_PI              (6.283185307F)
#define     MOTOR_INERTIA_ESTIMATE_TWO_PI_60           (MOTOR_INERTIA_ESTIMATE_TWO_PI / 60.0F)
#define     MOTOR_INERTIA_ESTIMATE_DEGREE_TO_RAD       (MOTOR_INERTIA_ESTIMATE_TWO_PI / 360.0F)
#define     MOTOR_INERTIA_ESTIMATE_HALF                (0.5F)
#define     MOTOR_INERTIA_ESTIMATE_TWO                 (2.0F)
#define     MOTOR_INERTIA_ESTIMATE_THREE               (3.0F)

#define     MOTOR_INERTIA_ESTIMATE_MOVE_TRIANGLE       (0)
#define     MOTOR_INERTIA_ESTIMATE_MOVE_TRAPEZOIDAL    (1)

#define     MOTOR_INERTIA_ESTIMATE_POS_STEADY          (0)
#define     MOTOR_INERTIA_ESTIMATE_POS_TRANSITION      (1)

#ifndef MOTOR_INERTIA_ESTIMATE_ERROR_RETURN

 #define    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_motor_inertia_estimate_initialize(motor_inertia_estimate_instance_ctrl_t * p_ctrl);
static void rm_motor_inertia_estimate_set_parameter(motor_inertia_estimate_instance_ctrl_t * p_ctrl);

static void rm_motor_inertia_estimate_speed_cyclic(motor_inertia_estimate_ctrl_t * const p_ctrl);
static void rm_motor_inertia_estimate_steady_process(motor_inertia_estimate_instance_ctrl_t * p_ctrl);
static void rm_motor_inertia_estimate_transition_process(motor_inertia_estimate_instance_ctrl_t * p_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_inertia_estimate_api_t g_motor_inertia_estimate_on_motor_inertia_estimate =
{
    .open            = RM_MOTOR_INERTIA_ESTIMATE_Open,
    .close           = RM_MOTOR_INERTIA_ESTIMATE_Close,
    .start           = RM_MOTOR_INERTIA_ESTIMATE_Start,
    .stop            = RM_MOTOR_INERTIA_ESTIMATE_Stop,
    .reset           = RM_MOTOR_INERTIA_ESTIMATE_Reset,
    .infoGet         = RM_MOTOR_INERTIA_ESTIMATE_InfoGet,
    .dataSet         = RM_MOTOR_INERTIA_ESTIMATE_DataSet,
    .speedCyclic     = RM_MOTOR_INERTIA_ESTIMATE_SpeedCyclic,
    .currentCyclic   = RM_MOTOR_INERTIA_ESTIMATE_CurrentCyclic,
    .parameterUpdate = RM_MOTOR_INERTIA_ESTIMATE_ParameterUpdate,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_INERTIA_ESTIMATE
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the motor inertia estimate module. Implements @ref motor_inertia_estimate_api_t::open.
 *
 * Example:
 * @snippet rm_motor_inertia_estimate_example.c RM_MOTOR_INERTIA_ESTIMATE_Open
 *
 * @retval FSP_SUCCESS              Motor inertia estimate module successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Open (motor_inertia_estimate_ctrl_t * const      p_ctrl,
                                          motor_inertia_estimate_cfg_t const * const p_cfg)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    motor_inertia_estimate_extended_cfg_t * p_extend = (motor_inertia_estimate_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extend);

    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(p_extend->u1_motor_polepairs != 0, FSP_ERR_INVALID_ARGUMENT);
#endif
    p_instance_ctrl->p_cfg = p_cfg;

    rm_motor_inertia_estimate_initialize(p_instance_ctrl);

    p_instance_ctrl->f_inverse_motor_polepairs = 1.0F / (float) p_extend->u1_motor_polepairs;

    rm_motor_inertia_estimate_set_parameter(p_instance_ctrl);

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_INERTIA_ESTIMATE_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified motor inertia estimate module. Implements @ref motor_inertia_estimate_api_t::close.
 *
 * Example:
 * @snippet rm_motor_inertia_estimate_example.c RM_MOTOR_INERTIA_ESTIMATE_Close
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Close (motor_inertia_estimate_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_inertia_estimate_initialize(p_instance_ctrl);

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Start inertia estimation. Implements @ref motor_inertia_estimate_api_t::start.
 *
 * Example:
 * @snippet rm_motor_inertia_estimate_example.c RM_MOTOR_INERTIA_ESTIMATE_Start
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Start (motor_inertia_estimate_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_inertia_estimate_initialize(p_instance_ctrl);

    p_instance_ctrl->start_flag = MOTOR_INERTIA_ESTIMATE_START_FLAG_START;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop (Cancel) inertia estimation. Implements @ref motor_inertia_estimate_api_t::stop.
 *
 * Example:
 * @snippet rm_motor_inertia_estimate_example.c RM_MOTOR_INERTIA_ESTIMATE_Stop
 *
 * @retval FSP_SUCCESS              Successfully stopped (canceled).
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Stop (motor_inertia_estimate_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_inertia_estimate_initialize(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of inertia estimate module. Implements @ref motor_inertia_estimate_api_t::reset.
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_Reset (motor_inertia_estimate_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_inertia_estimate_initialize(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get information of inertia estimation. Implements @ref motor_inertia_estimate_api_t::infoGet.
 *
 * Example:
 * @snippet rm_motor_inertia_estimate_example.c RM_MOTOR_INERTIA_ESTIMATE_InfoGet
 *
 * @retval FSP_SUCCESS              Successfully get data.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Argument pointer is invalid.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_InfoGet (motor_inertia_estimate_ctrl_t * const p_ctrl,
                                             motor_inertia_estimate_info_t * const p_info)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(p_info != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_info->s2_position_reference_degree = p_instance_ctrl->s2_position_reference_degree;
    p_info->mode                = p_instance_ctrl->mode;
    p_info->f_estimated_inertia = p_instance_ctrl->f_estimated_value;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set necessary data to inertia estimation. Implements @ref motor_inertia_estimate_api_t::dataSet.
 *
 * Example:
 * @snippet rm_motor_inertia_estimate_example.c RM_MOTOR_INERTIA_ESTIMATE_DataSet
 *
 * @retval FSP_SUCCESS              Successfully set data.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_DataSet (motor_inertia_estimate_ctrl_t * const     p_ctrl,
                                             motor_inertia_estimate_set_data_t * const p_set_data)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(p_set_data != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    motor_inertia_estimate_extended_cfg_t * p_extend =
        (motor_inertia_estimate_extended_cfg_t *) (p_instance_ctrl->p_cfg->p_extend);

    p_instance_ctrl->receive_data = *p_set_data;

    p_instance_ctrl->f_iq_ad = p_set_data->f_iq * p_extend->f_current_ctrl_period;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Cyclic process of inertia estimation at speed control period.
 * Implements @ref motor_inertia_estimate_api_t::speedCyclic.
 *
 * @retval FSP_SUCCESS              Successfully perform the process.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_SpeedCyclic (motor_inertia_estimate_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Only work at inertia estimation started */
    if (MOTOR_INERTIA_ESTIMATE_START_FLAG_START == p_instance_ctrl->start_flag)
    {
        /* Copy moving state */
        p_instance_ctrl->speed_period_buffer = p_instance_ctrl->speed_period;

        /* Perform cyclic process */
        rm_motor_inertia_estimate_speed_cyclic(p_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Cyclic process of inertia estimation at current control period (called at A/D conversion finish interrupt).
 * Implements @ref motor_inertia_estimate_api_t::currentCyclic.
 *
 * @retval FSP_SUCCESS              Successfully perform the process.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_CurrentCyclic (motor_inertia_estimate_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_inertia_estimate_extended_cfg_t * p_extend =
        (motor_inertia_estimate_extended_cfg_t *) (p_instance_ctrl->p_cfg->p_extend);

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extend);
#endif

    float f_inertia = 0.0F;
    float f_iq_ad   = 0.0F;
    float f_time    = 0.0F;
    float f_temp    = 0.0F;

    /* Only work at inertia estimation started */
    if (MOTOR_INERTIA_ESTIMATE_START_FLAG_START == p_instance_ctrl->start_flag)
    {
        if (MOTOR_INERTIA_ESTIMATE_PERIOD_MEASURE_FINISH == p_instance_ctrl->speed_period)
        {
            /* Do nothing */
        }
        /* Reached at calculate position */
        else if (MOTOR_INERTIA_ESTIMATE_PERIOD_NO_MOVE == p_instance_ctrl->speed_period)
        {
            // Memorize current speed
            f_inertia = p_instance_ctrl->receive_data.f_speed_radian_control *
                        p_instance_ctrl->f_inverse_motor_polepairs;

            // Memorize sum of iq
            f_iq_ad = p_instance_ctrl->f_summary_iq_ad;

            // Memorize moving time
            f_time = (float) p_instance_ctrl->u4_measure_count * p_extend->f_current_ctrl_period;

            switch (p_instance_ctrl->speed_period_buffer)
            {
                default:
                case MOTOR_INERTIA_ESTIMATE_PERIOD_NO_MOVE:
                {
                    p_instance_ctrl->f_summary_iq_ad  = 0.0F;
                    p_instance_ctrl->u4_measure_count = 0U;
                    break;
                }

                case MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_ACCELL:
                {
                    p_instance_ctrl->f_inertia_speed_ctrl2 = f_inertia;
                    p_instance_ctrl->f_inertia_integ_iq1   = f_iq_ad;
                    p_instance_ctrl->f_inertia_integ_time1 = f_time;
                    break;
                }

                case MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_DECELERATE:
                {
                    p_instance_ctrl->f_inertia_speed_ctrl4 = f_inertia;
                    p_instance_ctrl->f_inertia_integ_iq2   = f_iq_ad;
                    p_instance_ctrl->f_inertia_integ_time2 = f_time;
                    break;
                }

                case MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_ACCELL:
                {
                    p_instance_ctrl->f_inertia_speed_ctrl6 = f_inertia;
                    p_instance_ctrl->f_inertia_integ_iq3   = f_iq_ad;
                    p_instance_ctrl->f_inertia_integ_time3 = f_time;
                    break;
                }

                case MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_DECELERATE:
                {
                    p_instance_ctrl->f_inertia_speed_ctrl8 = f_inertia;
                    p_instance_ctrl->f_inertia_integ_iq4   = f_iq_ad;
                    p_instance_ctrl->f_inertia_integ_time4 = f_time;
                    break;
                }
            }
        }
        /* During the motor moves */
        else
        {
            /* When reached reference position */
            if (MOTOR_INERTIA_ESTIMATE_PERIOD_NO_MOVE == p_instance_ctrl->speed_period_buffer)
            {
                /* Memorize current speed */
                f_temp = p_instance_ctrl->receive_data.f_speed_radian_control *
                         p_instance_ctrl->f_inverse_motor_polepairs;
                switch (p_instance_ctrl->speed_period)
                {
                    default:
                    {
                        break;
                    }

                    case MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_ACCELL:
                    {
                        p_instance_ctrl->f_inertia_speed_ctrl1 = f_temp;
                        break;
                    }

                    case MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_DECELERATE:
                    {
                        p_instance_ctrl->f_inertia_speed_ctrl3 = f_temp;
                        break;
                    }

                    case MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_ACCELL:
                    {
                        p_instance_ctrl->f_inertia_speed_ctrl5 = f_temp;
                        break;
                    }

                    case MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_DECELERATE:
                    {
                        p_instance_ctrl->f_inertia_speed_ctrl7 = f_temp;
                        break;
                    }
                }
            }

            p_instance_ctrl->f_summary_iq_ad += p_instance_ctrl->f_iq_ad;

            // measure moving time
            p_instance_ctrl->u4_measure_count++;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of inertia estimate. Implements @ref motor_inertia_estimate_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data was updated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_INERTIA_ESTIMATE_ParameterUpdate (motor_inertia_estimate_ctrl_t * const      p_ctrl,
                                                     motor_inertia_estimate_cfg_t const * const p_cfg)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(MOTOR_INERTIA_ESTIMATE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_inertia_estimate_extended_cfg_t * p_extend = (motor_inertia_estimate_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_INERTIA_ESTIMATE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extend);

    MOTOR_INERTIA_ESTIMATE_ERROR_RETURN(p_extend->u1_motor_polepairs != 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->f_inverse_motor_polepairs = 1.0F / (float) p_extend->u1_motor_polepairs;

    rm_motor_inertia_estimate_set_parameter(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_INERTIA_ESTIMATE)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : rm_motor_inertia_estimate_initialize
 * Description   : Initialize variables
 * Arguments     : p_ctrl - pointer of module data
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_inertia_estimate_initialize (motor_inertia_estimate_instance_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_extended_cfg_t * p_extend =
        (motor_inertia_estimate_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    p_ctrl->start_flag = MOTOR_INERTIA_ESTIMATE_START_FLAG_STOP;

    p_ctrl->mode                = MOTOR_INERTIA_ESTIMATE_MODE_START;
    p_ctrl->u1_mode_count       = (uint8_t) MOTOR_INERTIA_ESTIMATE_MODE_START;
    p_ctrl->speed_period        = MOTOR_INERTIA_ESTIMATE_PERIOD_NO_MOVE;
    p_ctrl->speed_period_buffer = p_ctrl->speed_period;

    p_ctrl->u4_measure_count = 0U;
    p_ctrl->u4_wait_count    = 0U;

    p_ctrl->u1_position_move_mode = MOTOR_INERTIA_ESTIMATE_MOVE_TRIANGLE;

    p_ctrl->f_iq_ad              = 0.0F;
    p_ctrl->f_summary_iq_ad      = 0.0F;
    p_ctrl->f_position_mode_time = 0.0F;

    p_ctrl->f_estimated_value = p_extend->f_rotor_inertia;
    p_ctrl->f_inertia_value1  = 0.0F;
    p_ctrl->f_inertia_value2  = 0.0F;

    p_ctrl->f_inertia_speed_ctrl1 = 0.0F;
    p_ctrl->f_inertia_speed_ctrl2 = 0.0F;
    p_ctrl->f_inertia_speed_ctrl3 = 0.0F;
    p_ctrl->f_inertia_speed_ctrl4 = 0.0F;
    p_ctrl->f_inertia_speed_ctrl5 = 0.0F;
    p_ctrl->f_inertia_speed_ctrl6 = 0.0F;
    p_ctrl->f_inertia_speed_ctrl7 = 0.0F;
    p_ctrl->f_inertia_speed_ctrl8 = 0.0F;

    p_ctrl->f_inertia_integ_iq1 = 0.0F;
    p_ctrl->f_inertia_integ_iq2 = 0.0F;
    p_ctrl->f_inertia_integ_iq3 = 0.0F;
    p_ctrl->f_inertia_integ_iq4 = 0.0F;

    p_ctrl->f_inertia_integ_time1 = 0.0F;
    p_ctrl->f_inertia_integ_time2 = 0.0F;
    p_ctrl->f_inertia_integ_time3 = 0.0F;
    p_ctrl->f_inertia_integ_time4 = 0.0F;
}                                      /* End of function rm_motor_inertia_estimate_initialize */

/***********************************************************************************************************************
 * Function Name : rm_motor_inertia_estimate_set_parameter
 * Description   : Necessary parameters are calculated according to extended settings
 * Arguments     : p_ctrl - pointer of module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_inertia_estimate_set_parameter (motor_inertia_estimate_instance_ctrl_t * p_ctrl)
{
    float f_temp_move_rad  = 0.0F;
    float f_temp_max_speed = 0.0F;

    motor_inertia_estimate_extended_cfg_t * p_extend =
        (motor_inertia_estimate_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Decision of the profile mode of position control */
    f_temp_move_rad                = fabsf((float) p_extend->s2_move_degree * MOTOR_INERTIA_ESTIMATE_DEGREE_TO_RAD);
    f_temp_max_speed               = (float) p_extend->u2_J_max_speed_rpm * MOTOR_INERTIA_ESTIMATE_TWO_PI_60;
    p_ctrl->f_position_dt_time_sec = f_temp_move_rad / f_temp_max_speed;

    f_temp_max_speed = p_extend->f_accel_time * f_temp_max_speed;
    if (f_temp_max_speed >= f_temp_move_rad)
    {
        p_ctrl->u1_position_move_mode = MOTOR_INERTIA_ESTIMATE_MOVE_TRIANGLE;
    }
    else
    {
        p_ctrl->u1_position_move_mode = MOTOR_INERTIA_ESTIMATE_MOVE_TRAPEZOIDAL;
    }

    /* Set interval time */
    p_ctrl->f_interval_time = p_extend->f_position_interval * p_extend->f_speed_ctrl_period;
}

/***********************************************************************************************************************
 * Function Name : rm_motor_inertia_estimate_speed_cyclic
 * Description   : Cyclic process at speed control (Call at timer interrupt)
 * Arguments     : p_ctrl - pointer of module instance
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_inertia_estimate_speed_cyclic (motor_inertia_estimate_ctrl_t * const p_ctrl)
{
    motor_inertia_estimate_instance_ctrl_t * p_instance_ctrl = (motor_inertia_estimate_instance_ctrl_t *) p_ctrl;

    /* Position control reached to reference */
    if (MOTOR_INERTIA_ESTIMATE_POS_STEADY == p_instance_ctrl->receive_data.u1_position_state)
    {
        rm_motor_inertia_estimate_steady_process(p_instance_ctrl);
    }
    /* Position control transition */
    else
    {
        rm_motor_inertia_estimate_transition_process(p_instance_ctrl);
    }
}                                      /* End of function rm_motor_inertia_estimate_speed_cyclic */

/***********************************************************************************************************************
 * Function Name : rm_motor_inertia_estimate_steady_process
 * Description   : Process at positon control in steady state (reached to reference position)
 * Arguments     : p_ctrl - pointer of module data
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_inertia_estimate_steady_process (motor_inertia_estimate_instance_ctrl_t * p_ctrl)
{
    motor_inertia_estimate_extended_cfg_t * p_extend =
        (motor_inertia_estimate_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    float f_temp1 = 0.0F;
    float f_temp2 = 0.0F;
    float f_time1 = 0.0F;
    float f_time2 = 0.0F;

    switch (p_ctrl->mode)
    {
        default:
        {
            // Do nothing
            break;
        }

        case MOTOR_INERTIA_ESTIMATE_MODE_START:
        {
            p_ctrl->s2_initial_position_degree = p_ctrl->receive_data.s2_position_degree;
            p_ctrl->u1_mode_count              = (uint8_t) MOTOR_INERTIA_ESTIMATE_MODE_WAIT;
            p_ctrl->mode = MOTOR_INERTIA_ESTIMATE_MODE_WAIT;
            break;
        }

        case MOTOR_INERTIA_ESTIMATE_MODE_WAIT:
        {
            p_ctrl->u4_wait_count++;

            /* wait set time (confirm the stability of position control) */
            if (p_ctrl->u4_wait_count >= (uint32_t) p_extend->f_change_mode_time)
            {
                /* Move to next step(mode) */
                p_ctrl->u1_mode_count++;
                p_ctrl->mode = (motor_inertia_estimate_mode_t) p_ctrl->u1_mode_count;

                /* measurement finished */
                if ((uint8_t) MOTOR_INERTIA_ESTIMATE_MODE_CALCULATE == p_ctrl->u1_mode_count)
                {
                    p_ctrl->u1_mode_count = (uint8_t) MOTOR_INERTIA_ESTIMATE_MODE_START;
                }

                /* Shorten last state transition */
                if ((uint8_t) MOTOR_INERTIA_ESTIMATE_MODE_REVERSE == p_ctrl->u1_mode_count)
                {
                    p_ctrl->u4_wait_count = (uint32_t) (p_extend->f_change_mode_time * MOTOR_INERTIA_ESTIMATE_HALF);
                }
                else
                {
                    p_ctrl->u4_wait_count = 0U;
                }
            }

            break;
        }

        case MOTOR_INERTIA_ESTIMATE_MODE_FORWARD:
        {
            // Set position reference to forward (initial + set degree)
            p_ctrl->s2_position_reference_degree =
                (int16_t) (p_extend->s2_move_degree + p_ctrl->s2_initial_position_degree);

            // return to wait steady state (wait the motor will move to the reference.)
            p_ctrl->mode = MOTOR_INERTIA_ESTIMATE_MODE_WAIT;
            break;
        }

        case MOTOR_INERTIA_ESTIMATE_MODE_REVERSE:
        {
            // Set position reference to reverse (initial)
            p_ctrl->s2_position_reference_degree = p_ctrl->s2_initial_position_degree;

            // return to wait steady state (wait the motor will move to the reference.)
            p_ctrl->mode = MOTOR_INERTIA_ESTIMATE_MODE_WAIT;
            break;
        }

        case MOTOR_INERTIA_ESTIMATE_MODE_CALCULATE:
        {
            /* Stop current cyclic process */
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_MEASURE_FINISH;

            /* calculate estimated inertia data */
            f_time1 = p_ctrl->f_inertia_integ_time1;
            f_time2 = p_ctrl->f_inertia_integ_time2;

            /* Check none zero */
            if (((0.0F < f_time1) || (f_time1 < 0.0F)) && ((0.0F < f_time2) || (0.0F > f_time2)))
            {
                f_temp1 = (float) p_extend->u1_motor_polepairs * p_extend->f_motor_m *
                          ((p_ctrl->f_inertia_integ_iq1 / f_time1) -
                           (p_ctrl->f_inertia_integ_iq2 / f_time2));
                f_temp2 = ((p_ctrl->f_inertia_speed_ctrl2 - p_ctrl->f_inertia_speed_ctrl1) / f_time1) -
                          ((p_ctrl->f_inertia_speed_ctrl4 - p_ctrl->f_inertia_speed_ctrl3) / f_time2);
                p_ctrl->f_inertia_value1 = f_temp1 / f_temp2;
            }
            else
            {
                /* set error value */
                p_ctrl->f_inertia_value1 = -1.0F;
            }

            f_time1 = p_ctrl->f_inertia_integ_time3;
            f_time2 = p_ctrl->f_inertia_integ_time4;

            /* Check none zero */
            if (((0.0F < f_time1) || (f_time1 < 0.0F)) && ((0.0F < f_time2) || (0.0F > f_time2)))
            {
                f_temp1 = (float) p_extend->u1_motor_polepairs * p_extend->f_motor_m *
                          ((p_ctrl->f_inertia_integ_iq3 / f_time1) - (p_ctrl->f_inertia_integ_iq4 / f_time2));
                f_temp2 = ((p_ctrl->f_inertia_speed_ctrl6 - p_ctrl->f_inertia_speed_ctrl5) / f_time1) -
                          ((p_ctrl->f_inertia_speed_ctrl8 - p_ctrl->f_inertia_speed_ctrl7) / f_time2);
                p_ctrl->f_inertia_value2 = f_temp1 / f_temp2;
            }
            else
            {
                /* set error value */
                p_ctrl->f_inertia_value2 = -1.0F;
            }

            p_ctrl->f_estimated_value =
                (p_ctrl->f_inertia_value1 + p_ctrl->f_inertia_value2) * MOTOR_INERTIA_ESTIMATE_HALF;

            /* When estimated value is minus, an error happened */
            if (p_ctrl->f_estimated_value < 0.0F)
            {
                p_ctrl->f_estimated_value = -1.0F;
                p_ctrl->mode              = MOTOR_INERTIA_ESTIMATE_MODE_ERROR;
            }
            else
            {
                /* Set status to normal finish. */
                p_ctrl->mode = MOTOR_INERTIA_ESTIMATE_MODE_FINISH;
            }

            break;
        }
    }
}                                      /* End of function rm_motor_inertia_estimate_steady_process */

/***********************************************************************************************************************
 * Function Name : rm_motor_inertia_estimate_transition_process
 * Description   : Process at positon control in transition state
 * Arguments     : p_ctrl - pointer of module data
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_inertia_estimate_transition_process (motor_inertia_estimate_instance_ctrl_t * p_ctrl)
{
    motor_inertia_estimate_extended_cfg_t * p_extend =
        (motor_inertia_estimate_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    float f_pos_mode_time = 0.0F;
    float aTemp_time      = p_extend->f_accel_time;

    p_ctrl->f_position_mode_time += p_extend->f_speed_ctrl_period;

    /* Moving time */
    f_pos_mode_time = p_ctrl->f_position_mode_time;

    /* Triangle mode */
    if (MOTOR_INERTIA_ESTIMATE_MOVE_TRIANGLE == p_ctrl->u1_position_move_mode)
    {
        if ((f_pos_mode_time >= (p_extend->f_judge_low_threshold * aTemp_time)) &&
            (f_pos_mode_time <= (p_extend->f_judge_high_threshold * aTemp_time)))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_ACCELL;
        }
        else if ((f_pos_mode_time >= ((1.0F + p_extend->f_judge_low_threshold) * aTemp_time)) &&
                 (f_pos_mode_time <= ((1.0F + p_extend->f_judge_high_threshold) * aTemp_time)))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_DECELERATE;
        }
        else if ((f_pos_mode_time >= ((MOTOR_INERTIA_ESTIMATE_TWO + p_extend->f_judge_low_threshold) * aTemp_time) +
                  p_ctrl->f_interval_time) &&
                 (f_pos_mode_time <= ((MOTOR_INERTIA_ESTIMATE_TWO + p_extend->f_judge_high_threshold) * aTemp_time) +
                  p_ctrl->f_interval_time))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_ACCELL;
        }
        else if ((f_pos_mode_time >= ((MOTOR_INERTIA_ESTIMATE_THREE + p_extend->f_judge_low_threshold) * aTemp_time) +
                  p_ctrl->f_interval_time) &&
                 (f_pos_mode_time <= ((MOTOR_INERTIA_ESTIMATE_THREE + p_extend->f_judge_high_threshold) * aTemp_time) +
                  p_ctrl->f_interval_time))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_DECELERATE;
        }
        else
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_NO_MOVE;
        }
    }
    /* Trapezoidal mode */
    else if (MOTOR_INERTIA_ESTIMATE_MOVE_TRAPEZOIDAL == p_ctrl->u1_position_move_mode)
    {
        if ((f_pos_mode_time >= (p_extend->f_judge_low_threshold * aTemp_time)) &&
            (f_pos_mode_time <= (p_extend->f_judge_high_threshold * aTemp_time)))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_ACCELL;
        }
        else if ((f_pos_mode_time >=
                  (p_ctrl->f_position_dt_time_sec + p_extend->f_judge_low_threshold * aTemp_time)) &&
                 (f_pos_mode_time <=
                  (p_ctrl->f_position_dt_time_sec + p_extend->f_judge_high_threshold * aTemp_time)))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_FORWARD_DECELERATE;
        }
        else if ((f_pos_mode_time >=
                  (p_ctrl->f_position_dt_time_sec +
                   (1.0F + p_extend->f_judge_low_threshold) * aTemp_time + p_ctrl->f_interval_time)) &&
                 (f_pos_mode_time <=
                  (p_ctrl->f_position_dt_time_sec +
                   (1.0F + p_extend->f_judge_high_threshold) * aTemp_time + p_ctrl->f_interval_time)))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_ACCELL;
        }
        else if ((f_pos_mode_time >=
                  (MOTOR_INERTIA_ESTIMATE_TWO * p_ctrl->f_position_dt_time_sec +
                   (1.0F + p_extend->f_judge_low_threshold) * aTemp_time + p_ctrl->f_interval_time)) &&
                 (f_pos_mode_time <=
                  (MOTOR_INERTIA_ESTIMATE_TWO * p_ctrl->f_position_dt_time_sec +
                   (1.0F + p_extend->f_judge_high_threshold) * aTemp_time + p_ctrl->f_interval_time)))
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_REVERSE_DECELERATE;
        }
        else
        {
            p_ctrl->speed_period = MOTOR_INERTIA_ESTIMATE_PERIOD_NO_MOVE;
        }
    }
    else
    {
        /* Do nothing */
    }
}                                      /* End of function rm_motor_inertia_estimate_transition_process */
