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
#include "rm_motor_return_origin.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define     MOTOR_RETURN_ORIGIN_OPEN             (('M' << 24U) | ('T' << 16U) | ('R' << 8U) | ('Z' << 0U))

#define     MOTOR_RETURN_ORIGIN_TWO_PI           (6.283185307F)
#define     MOTOR_RETURN_ORIGIN_TWO_PI_60        (6.283185307F / 60.0F)
#define     MOTOR_RETURN_ORIGIN_RAD_TO_DEGREE    (360.0F / MOTOR_RETURN_ORIGIN_TWO_PI)
#define     MOTOR_RETURN_ORIGIN_DEGREE_TO_RAD    (MOTOR_RETURN_ORIGIN_TWO_PI / 360.0F)
#define     MOTOR_RETURN_ORIGIN_HALF             (0.5F)

#ifndef MOTOR_RETURN_ORIGIN_ERROR_RETURN

 #define    MOTOR_RETURN_ORIGIN_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void  rm_motor_return_origin_initialize(motor_return_origin_instance_ctrl_t * const p_ctrl);
static void  rm_motor_return_origin_speed_cyclic(motor_return_origin_instance_ctrl_t * const p_ctrl);
static float rm_motor_return_origin_push(motor_return_origin_instance_ctrl_t * const p_ctrl);
static float rm_motor_return_origin_calculate_search_speed_accel(motor_return_origin_instance_ctrl_t * p_ctrl);
static float rm_motor_return_origin_calculate_search_speed_decleration(motor_return_origin_instance_ctrl_t * p_ctrl);
static float rm_motor_return_origin_calc_decele_rad(float f4_move_pos, float f4_speed, float f4_acc);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_return_origin_api_t g_motor_return_origin_on_motor_return_origin =
{
    .open            = RM_MOTOR_RETURN_ORIGIN_Open,
    .close           = RM_MOTOR_RETURN_ORIGIN_Close,
    .start           = RM_MOTOR_RETURN_ORIGIN_Start,
    .stop            = RM_MOTOR_RETURN_ORIGIN_Stop,
    .reset           = RM_MOTOR_RETURN_ORIGIN_Reset,
    .infoGet         = RM_MOTOR_RETURN_ORIGIN_InfoGet,
    .dataSet         = RM_MOTOR_RETURN_ORIGIN_DataSet,
    .speedCyclic     = RM_MOTOR_RETURN_ORIGIN_SpeedCyclic,
    .parameterUpdate = RM_MOTOR_RETURN_ORIGIN_ParameterUpdate,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_RETURN_ORIGIN
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the motor return origin module. Implements @ref motor_return_origin_api_t::open.
 *
 * Example:
 * @snippet rm_motor_return_origin_example.c RM_MOTOR_RETURN_ORIGIN_Open
 *
 * @retval FSP_SUCCESS              Motor return origin module successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_Open (motor_return_origin_ctrl_t * const      p_ctrl,
                                       motor_return_origin_cfg_t const * const p_cfg)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    motor_return_origin_extended_cfg_t * p_extended_cfg = (motor_return_origin_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_extended_cfg);

    MOTOR_RETURN_ORIGIN_ERROR_RETURN(p_extended_cfg->f_speed_ctrl_period >= 0, FSP_ERR_INVALID_ARGUMENT);
#endif
    p_instance_ctrl->p_cfg = p_cfg;

    rm_motor_return_origin_initialize(p_instance_ctrl);
    p_instance_ctrl->f_angle_degree_on_edge         = 0.0F;
    p_instance_ctrl->f_origin_position_angle_degree = 0.0F;

    /* Pushing mode */
    if (MOTOR_RETURN_ORIGIN_MODE_PUSH == p_instance_ctrl->p_cfg->mode)
    {
        float temp_search_speed;
        p_instance_ctrl->st_pushing.f_judge_iq =
            p_extended_cfg->f_maximum_current * p_extended_cfg->f_current_limit_percent_push;
        p_instance_ctrl->st_pushing.f_pushing_counts =
            p_extended_cfg->f_pushing_time / p_extended_cfg->f_speed_ctrl_period;
        p_instance_ctrl->f_accel_speed =
            fabsf((MOTOR_RETURN_ORIGIN_TWO_PI_60 * p_extended_cfg->f_speed_ctrl_period *
                   p_extended_cfg->f_speed_ctrl_period) * p_extended_cfg->f_return_accel_rpm *
                  p_extended_cfg->f_mechanical_gear_ratio);
        temp_search_speed = p_extended_cfg->f_search_speed_rpm * p_extended_cfg->f_mechanical_gear_ratio *
                            MOTOR_RETURN_ORIGIN_TWO_PI_60;
        if (temp_search_speed < 0.0F)
        {
            p_instance_ctrl->s1_direction = -1;
        }
        else
        {
            p_instance_ctrl->s1_direction = 1;
        }

        p_instance_ctrl->f_search_speed = fabsf(temp_search_speed * p_extended_cfg->f_speed_ctrl_period);
    }

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_RETURN_ORIGIN_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified motor return origin module. Implements @ref motor_return_origin_api_t::close.
 *
 * Example:
 * @snippet rm_motor_return_origin_example.c RM_MOTOR_RETURN_ORIGIN_Close
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_Close (motor_return_origin_ctrl_t * const p_ctrl)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_return_origin_initialize(p_instance_ctrl);
    p_instance_ctrl->f_angle_degree_on_edge         = 0.0F;
    p_instance_ctrl->f_origin_position_angle_degree = 0.0F;

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Start return origin function. Implements @ref motor_return_origin_api_t::start.
 *
 * Example:
 * @snippet rm_motor_return_origin_example.c RM_MOTOR_RETURN_ORIGIN_Start
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_Start (motor_return_origin_ctrl_t * const p_ctrl)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->start_flag = MOTOR_RETURN_ORIGIN_START_FLAG_START;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop (Cancel) return origin function. Implements @ref motor_return_origin_api_t::stop.
 *
 * Example:
 * @snippet rm_motor_return_origin_example.c RM_MOTOR_RETURN_ORIGIN_Stop
 *
 * @retval FSP_SUCCESS              Successfully stopped (canceled).
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_Stop (motor_return_origin_ctrl_t * const p_ctrl)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->start_flag = MOTOR_RETURN_ORIGIN_START_FLAG_STOP;

    rm_motor_return_origin_initialize(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset variables of return origin module. Implements @ref motor_return_origin_api_t::reset.
 *
 * @retval FSP_SUCCESS              Successfully reset.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_Reset (motor_return_origin_ctrl_t * const p_ctrl)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_return_origin_initialize(p_instance_ctrl);
    p_instance_ctrl->f_angle_degree_on_edge         = 0.0F;
    p_instance_ctrl->f_origin_position_angle_degree = 0.0F;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get information of return origin. Implements @ref motor_return_origin_api_t::infoGet.
 *
 * Example:
 * @snippet rm_motor_return_origin_example.c RM_MOTOR_RETURN_ORIGIN_InfoGet
 *
 * @retval FSP_SUCCESS              Successfully get data.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_InfoGet (motor_return_origin_ctrl_t * const p_ctrl,
                                          motor_return_origin_info_t * const p_info)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(p_info != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_info->f_position_reference_degree = p_instance_ctrl->f_position_reference_degree;
    p_info->state          = p_instance_ctrl->state;
    p_info->f_result_angle = p_instance_ctrl->f_angle_degree_on_edge;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set necessary data to return origin function. Implements @ref motor_return_origin_api_t::dataSet.
 *
 * Example:
 * @snippet rm_motor_return_origin_example.c RM_MOTOR_RETURN_ORIGIN_DataSet
 *
 * @retval FSP_SUCCESS              Successfully set data.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_DataSet (motor_return_origin_ctrl_t * const     p_ctrl,
                                          motor_return_origin_set_data_t * const p_set_data)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(p_set_data != NULL, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->receive_data = *p_set_data;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Cyclic process of return origin function at speed control period. (Called at timer interrupt.)
 * Implements @ref motor_return_origin_api_t::speedCyclic.
 *
 * @retval FSP_SUCCESS              Successfully perform the process.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_SpeedCyclic (motor_return_origin_ctrl_t * const p_ctrl)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Only work after started */
    if (MOTOR_RETURN_ORIGIN_START_FLAG_START == p_instance_ctrl->start_flag)
    {
        rm_motor_return_origin_speed_cyclic(p_instance_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Update the parameters of return origin function. Implements @ref motor_return_origin_api_t::parameterUpdate
 *
 * @retval FSP_SUCCESS              Successfully data was updated.
 * @retval FSP_ERR_ASSERTION        Null pointer.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input parameter error.
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_RETURN_ORIGIN_ParameterUpdate (motor_return_origin_ctrl_t * const      p_ctrl,
                                                  motor_return_origin_cfg_t const * const p_cfg)
{
    motor_return_origin_instance_ctrl_t * p_instance_ctrl = (motor_return_origin_instance_ctrl_t *) p_ctrl;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(MOTOR_RETURN_ORIGIN_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_return_origin_extended_cfg_t * p_extended_cfg = (motor_return_origin_extended_cfg_t *) p_cfg->p_extend;

#if MOTOR_RETURN_ORIGIN_CFG_PARAM_CHECKING_ENABLE
    MOTOR_RETURN_ORIGIN_ERROR_RETURN(p_extended_cfg->f_speed_ctrl_period >= 0, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    if (MOTOR_RETURN_ORIGIN_MODE_PUSH == p_instance_ctrl->p_cfg->mode)
    {
        float temp_search_speed;
        p_instance_ctrl->st_pushing.f_judge_iq =
            p_extended_cfg->f_maximum_current * p_extended_cfg->f_current_limit_percent_push;
        p_instance_ctrl->st_pushing.f_pushing_counts =
            p_extended_cfg->f_pushing_time / p_extended_cfg->f_speed_ctrl_period;
        p_instance_ctrl->f_accel_speed =
            fabsf((MOTOR_RETURN_ORIGIN_TWO_PI_60 * p_extended_cfg->f_speed_ctrl_period *
                   p_extended_cfg->f_speed_ctrl_period) * p_extended_cfg->f_return_accel_rpm *
                  p_extended_cfg->f_mechanical_gear_ratio);
        temp_search_speed = p_extended_cfg->f_search_speed_rpm * p_extended_cfg->f_mechanical_gear_ratio *
                            MOTOR_RETURN_ORIGIN_TWO_PI_60;
        if (temp_search_speed < 0.0F)
        {
            p_instance_ctrl->s1_direction = -1;
        }
        else
        {
            p_instance_ctrl->s1_direction = 1;
        }

        p_instance_ctrl->f_search_speed = fabsf(temp_search_speed * p_extended_cfg->f_speed_ctrl_period);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_RETURN_ORIGIN)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name : rm_motor_return_origin_initialize
 * Description   : Initialize variables
 * Arguments     : p_ctrl - pointer of module data
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_return_origin_initialize (motor_return_origin_instance_ctrl_t * const p_ctrl)
{
    p_ctrl->start_flag      = MOTOR_RETURN_ORIGIN_START_FLAG_STOP;
    p_ctrl->state           = MOTOR_RETURN_ORIGIN_STATE_START;
    p_ctrl->s1_direction    = 1;
    p_ctrl->f_current_speed = 0.0F;

    p_ctrl->f_position_reference_degree = 0.0F;

    if (MOTOR_RETURN_ORIGIN_MODE_PUSH == p_ctrl->p_cfg->mode)
    {
        p_ctrl->st_pushing.u4_time_counter = 0U;
        p_ctrl->st_pushing.f_sum_position  = 0.0F;
        p_ctrl->st_pushing.u4_sum_counter  = 0U;
        p_ctrl->st_pushing.f_move_amount   = 0.0F;
    }
}                                      /* End of function rm_motor_return_origin_initialize */

/***********************************************************************************************************************
 * Function Name : rm_motor_return_origin_speed_cyclic
 * Description   : Cyclic process at speed control (Call at timer interrupt)
 * Arguments     : p_ctrl - pointer of module data
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_return_origin_speed_cyclic (motor_return_origin_instance_ctrl_t * const p_ctrl)
{
    /* Select the origin return method. */
    switch (p_ctrl->p_cfg->mode)
    {
        case MOTOR_RETURN_ORIGIN_MODE_PUSH:
        {
            p_ctrl->f_position_reference_degree = rm_motor_return_origin_push(p_ctrl);
            break;
        }

        default:
        {
            /* Do Nothing */
            break;
        }
    }
}                                      /* End of function rm_motor_return_origin_speed_cyclic */

/***********************************************************************************************************************
 * Function Name : rm_motor_return_origin_push
 * Description   : Cyclic process at speed control with pushing
 * Arguments     : p_ctrl - pointer of module data
 * Return Value  : Calculated position reference
 **********************************************************************************************************************/
static float rm_motor_return_origin_push (motor_return_origin_instance_ctrl_t * const p_ctrl)
{
    float          f_mechanical_reverse;      /* mechanical reverse angle [rad] */
    volatile float f_calculated_ref_position; /* calculated reference potition */
    motor_return_origin_extended_cfg_t * p_extended_cfg =
        (motor_return_origin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    f_calculated_ref_position = p_ctrl->f_position_reference_degree;

    switch (p_ctrl->state)
    {
        default:
        {
            /* Do Nothing */
            break;
        }

        case MOTOR_RETURN_ORIGIN_STATE_START:
        {
            /* Initilize valiables to calculate */
            p_ctrl->st_pushing.u4_time_counter     = 0U;
            p_ctrl->st_pushing.f_sum_position      = 0.0F;
            p_ctrl->st_pushing.u4_sum_counter      = 0U;
            p_ctrl->st_pushing.f_move_amount       = 0.0F;
            p_ctrl->f_angle_degree_on_edge         = 0.0F;
            p_ctrl->f_origin_position_angle_degree = 0.0F;

            /* Go to search the stopper */
            p_ctrl->state = MOTOR_RETURN_ORIGIN_STATE_SEARCH_STOPPER;
            break;
        }

        case MOTOR_RETURN_ORIGIN_STATE_SEARCH_STOPPER:
        {
            /* iq reached set the value to judge the collision (push to the stopper) */
            if (fabsf(p_ctrl->receive_data.f_iq) >= p_ctrl->st_pushing.f_judge_iq)
            {
                /* Measure time for pushing */
                p_ctrl->st_pushing.u4_time_counter++;

                /* Reach to pushing time */
                if (p_ctrl->st_pushing.u4_time_counter >= (uint32_t) p_ctrl->st_pushing.f_pushing_counts)
                {
                    /* Calculate stopper position (average) */
                    p_ctrl->f_angle_degree_on_edge =
                        p_ctrl->st_pushing.f_sum_position / (float) p_ctrl->st_pushing.u4_sum_counter;

                    /* Calculate origin position */
                    f_mechanical_reverse =
                        fabsf(p_extended_cfg->f_mechanical_gear_ratio) *
                        p_ctrl->s1_direction * p_extended_cfg->f_return_degree;
                    p_ctrl->f_origin_position_angle_degree = p_ctrl->f_angle_degree_on_edge - f_mechanical_reverse;

                    f_mechanical_reverse *= MOTOR_RETURN_ORIGIN_DEGREE_TO_RAD;

                    /* Set reference to current position */
                    f_calculated_ref_position = p_ctrl->receive_data.f_position_degree;

                    p_ctrl->f_current_speed = 0.0F;

                    p_ctrl->st_pushing.f_move_amount  = fabsf(f_mechanical_reverse);
                    p_ctrl->st_pushing.f_move_amount -=
                        rm_motor_return_origin_calc_decele_rad(p_ctrl->st_pushing.f_move_amount,
                                                               p_ctrl->f_search_speed,
                                                               p_ctrl->f_accel_speed);

                    p_ctrl->state = MOTOR_RETURN_ORIGIN_STATE_REVERSE;
                }
                /* Over the half of pushing time */
                else if (p_ctrl->st_pushing.u4_time_counter >= ((uint32_t) p_ctrl->st_pushing.f_pushing_counts >> 1))
                {
                    /* Count up the summary counter */
                    p_ctrl->st_pushing.u4_sum_counter++;

                    /* Summurise current position data to calculate the average value of rotor position */
                    p_ctrl->st_pushing.f_sum_position += p_ctrl->receive_data.f_position_degree;
                }
                else
                {
                    /* Do nothing */
                }
            }
            /* The stopper could not be detected. */
            else if (((p_extended_cfg->f_over_degree > 0.0F) || (p_extended_cfg->f_over_degree < 0.0F)) &&
                     (p_ctrl->st_pushing.f_move_amount >
                      (p_extended_cfg->f_over_degree * MOTOR_RETURN_ORIGIN_DEGREE_TO_RAD)))
            {
                // Set state to error and stop the process
                f_calculated_ref_position =
                    (float) p_ctrl->s1_direction *
                    p_ctrl->st_pushing.f_move_amount * MOTOR_RETURN_ORIGIN_RAD_TO_DEGREE;
                p_ctrl->state      = MOTOR_RETURN_ORIGIN_STATE_ERROR;
                p_ctrl->start_flag = MOTOR_RETURN_ORIGIN_START_FLAG_STOP;
            }
            else
            {
                /* Do nothing */
            }

            if (MOTOR_RETURN_ORIGIN_STATE_SEARCH_STOPPER == p_ctrl->state)
            {
                rm_motor_return_origin_calculate_search_speed_accel(p_ctrl);
                p_ctrl->st_pushing.f_move_amount += p_ctrl->f_current_speed;
                f_calculated_ref_position         =
                    (float) p_ctrl->s1_direction *
                    p_ctrl->st_pushing.f_move_amount * MOTOR_RETURN_ORIGIN_RAD_TO_DEGREE;
            }

            break;
        }

        /* Reverse from stopper */
        case MOTOR_RETURN_ORIGIN_STATE_REVERSE:
        {
            rm_motor_return_origin_calculate_search_speed_accel(p_ctrl);
            p_ctrl->st_pushing.f_move_amount -= p_ctrl->f_current_speed;
            f_calculated_ref_position        -=
                (float) p_ctrl->s1_direction * p_ctrl->f_current_speed * MOTOR_RETURN_ORIGIN_RAD_TO_DEGREE;
            if (p_ctrl->st_pushing.f_move_amount <= 0.0F)
            {
                p_ctrl->state = MOTOR_RETURN_ORIGIN_STATE_DECELERATE;
            }

            break;
        }

        /* Deceleration of speed */
        case MOTOR_RETURN_ORIGIN_STATE_DECELERATE:
        {
            f_calculated_ref_position -=
                (float) p_ctrl->s1_direction * rm_motor_return_origin_calculate_search_speed_decleration(p_ctrl) *
                MOTOR_RETURN_ORIGIN_RAD_TO_DEGREE;
            if ((p_ctrl->f_current_speed > 0.0F) || (p_ctrl->f_current_speed < 0.0F))
            {
                /* Do nothing */
            }
            else                       // p_ctrl->f_current_speed == 0.0F
            {
                f_calculated_ref_position = p_ctrl->f_origin_position_angle_degree;
                p_ctrl->state             = MOTOR_RETURN_ORIGIN_STATE_DONE;
                p_ctrl->start_flag        = MOTOR_RETURN_ORIGIN_START_FLAG_STOP;
            }

            break;
        }
    }

    return f_calculated_ref_position;
}                                      /* End of function rm_motor_return_origin_push */

/***********************************************************************************************************************
 * Function Name: rm_motor_return_origin_calculate_search_speed_accel
 * Description  : Speed calculation when accelerating
 * Arguments    : p_ctrl - pointer of module data
 * Return Value : speed[rad / sample time] ,absolute value.
 ***********************************************************************************************************************/
static float rm_motor_return_origin_calculate_search_speed_accel (motor_return_origin_instance_ctrl_t * p_ctrl)
{
    p_ctrl->f_current_speed += p_ctrl->f_accel_speed;
    if (p_ctrl->f_current_speed > p_ctrl->f_search_speed)
    {
        p_ctrl->f_current_speed = p_ctrl->f_search_speed;
    }

    return p_ctrl->f_current_speed;
}                                      /* End of function rm_motor_return_origin_calculate_search_speed_accel */

/***********************************************************************************************************************
 * Function Name: rm_motor_return_origin_calculate_search_speed_decleration
 * Description  : Speed calculation during deceleration
 * Arguments    : p_ctrl - pointer of module data
 * Return Value : speed[rad / sample time] ,absolute value.
 ***********************************************************************************************************************/
static float rm_motor_return_origin_calculate_search_speed_decleration (motor_return_origin_instance_ctrl_t * p_ctrl)
{
    p_ctrl->f_current_speed -= p_ctrl->f_accel_speed;
    if (p_ctrl->f_current_speed <= 0.0F)
    {
        p_ctrl->f_current_speed = 0.0F;
    }

    return p_ctrl->f_current_speed;
}                                      /* End of function rm_motor_return_origin_calculate_search_speed_decleration */

/***********************************************************************************************************************
 * Function Name: rm_motor_return_origin_calc_decele_rad
 * Description  : Calculate deceleration distance.
 * Arguments    : f4_move_pos - Amount of movement [rad]
 *               f4_speed - max speed [rad / sample time] ,absolute value
 *               f4_acc -  acc  [rad / sample time^2] ,absolute value
 * Return Value : deceleration distance [rad] ,absolute value
 ***********************************************************************************************************************/
static float rm_motor_return_origin_calc_decele_rad (float f4_move_pos, float f4_speed, float f4_acc)
{
    float f4_ret = 0.0F;               /* return value */
    float f4_work;                     /* work buffer */
    float f4_ratio;                    /* movement amount ratio */

    if ((f4_speed > 0.0F) || (f4_speed < 0.0F))
    {
        f4_work  = f4_speed * f4_speed / f4_acc;
        f4_ratio = sqrtf(fabsf(f4_move_pos / f4_work));
        if (f4_ratio < 1.0F)
        {
            f4_ret = fabsf(MOTOR_RETURN_ORIGIN_HALF * f4_ratio * f4_work);
        }
        else
        {
            f4_ret = fabsf(MOTOR_RETURN_ORIGIN_HALF * f4_work);
        }
    }

    return f4_ret;
}                                      /* End of function rm_motor_return_origin_calc_decele_rad */
