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
#include "rm_motor_120_degree.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define MOTOR_120_DEGREE_OPEN                                  (0x4D314C53L)

/* For Statemachine */
#define MOTOR_120_DEGREE_STATEMACHINE_SIZE_STATE               (3)
#define MOTOR_120_DEGREE_STATEMACHINE_SIZE_EVENT               (4)

/* State machine error flags */
#define MOTOR_120_DEGREE_STATEMACHINE_ERROR_NONE               (0x00) /* None error flag */
#define MOTOR_120_DEGREE_STATEMACHINE_ERROR_EVENTOUTBOUND      (0x01) /* The event index is out of bound */
#define MOTOR_120_DEGREE_STATEMACHINE_ERROR_STATEOUTBOUND      (0x02) /* The state index is out of bound */
#define MOTOR_120_DEGREE_STATEMACHINE_ERROR_ACTIONEXCEPTION    (0x04) /* The action function returns failure */

#ifndef MOTOR_120_DEGREE_ERROR_RETURN

 #define  MOTOR_120_DEGREE_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static uint16_t rm_motor_120_degree_error_check(motor_120_degree_instance_ctrl_t * p_ctrl,
                                                float                              f_iu,
                                                float                              f_iv,
                                                float                              f_iw,
                                                float                              f_vdc,
                                                float                              f_speed);

/* action functions */
static uint8_t rm_motor_120_degree_active(motor_120_degree_instance_ctrl_t * p_ctrl);
static uint8_t rm_motor_120_degree_inactive(motor_120_degree_instance_ctrl_t * p_ctrl);
static uint8_t rm_motor_120_degree_reset(motor_120_degree_instance_ctrl_t * p_ctrl);
static uint8_t rm_motor_120_degree_error(motor_120_degree_instance_ctrl_t * p_ctrl);
static uint8_t rm_motor_120_degree_nowork(motor_120_degree_instance_ctrl_t * p_ctrl);

static const uint8_t state_transition_table[MOTOR_120_DEGREE_STATEMACHINE_SIZE_EVENT][
    MOTOR_120_DEGREE_STATEMACHINE_SIZE_STATE
] =
{
/* State            0:MOTOR_120_DEGREE_CTRL_STATUS_STOP,
 *                  1:MOTOR_120_DEGREE_CTRL_STATUS_RUN,
 *                  2:MOTOR_120_DEGREE_CTRL_STATUS_ERROR */

/* Event */
/* 0:EVENT_STOP  */ {MOTOR_120_DEGREE_CTRL_STATUS_STOP,
                     MOTOR_120_DEGREE_CTRL_STATUS_STOP,
                     MOTOR_120_DEGREE_CTRL_STATUS_ERROR},

/* 1:EVENT_RUN   */ {MOTOR_120_DEGREE_CTRL_STATUS_RUN,
                     MOTOR_120_DEGREE_CTRL_STATUS_RUN,
                     MOTOR_120_DEGREE_CTRL_STATUS_ERROR},

/* 2:EVENT_ERROR */ {MOTOR_120_DEGREE_CTRL_STATUS_ERROR,
                     MOTOR_120_DEGREE_CTRL_STATUS_ERROR,
                     MOTOR_120_DEGREE_CTRL_STATUS_ERROR},

/* 3:EVENT_RESET */ {MOTOR_120_DEGREE_CTRL_STATUS_STOP,
                     MOTOR_120_DEGREE_CTRL_STATUS_ERROR,
                     MOTOR_120_DEGREE_CTRL_STATUS_STOP},
};

typedef uint8_t (* motor_120_degree_action_t)(motor_120_degree_instance_ctrl_t * p_ctrl);

static const motor_120_degree_action_t motor_120_degree_action_table[MOTOR_120_DEGREE_STATEMACHINE_SIZE_EVENT][
    MOTOR_120_DEGREE_STATEMACHINE_SIZE_STATE] =
{
/* State                        0:STOP,                    1:RUN,                    2:ERROR */
/* Event */
/* 0:EVENT_STOP     */ {rm_motor_120_degree_inactive, rm_motor_120_degree_inactive, rm_motor_120_degree_nowork      },

/* 1:EVENT_RUN      */ {rm_motor_120_degree_active,   rm_motor_120_degree_nowork,   rm_motor_120_degree_nowork      },

/* 2:EVENT_ERROR    */ {rm_motor_120_degree_error,    rm_motor_120_degree_error,    rm_motor_120_degree_nowork      },

/* 3:EVENT_RESET    */ {rm_motor_120_degree_reset,    rm_motor_120_degree_error,    rm_motor_120_degree_reset       },
};

/* statemachine functions */
static void     rm_motor_120_degree_statemachine_init(motor_120_degree_statemachine_t * p_state_machine);
static void     rm_motor_120_degree_statemachine_reset(motor_120_degree_statemachine_t * p_state_machine);
static uint16_t rm_motor_120_degree_statemachine_event(motor_120_degree_instance_ctrl_t * p_ctrl,
                                                       motor_120_degree_ctrl_event_t      u1_event);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const motor_api_t g_motor_on_motor_120_degree =
{
    .open            = RM_MOTOR_120_DEGREE_Open,
    .close           = RM_MOTOR_120_DEGREE_Close,
    .run             = RM_MOTOR_120_DEGREE_Run,
    .stop            = RM_MOTOR_120_DEGREE_Stop,
    .reset           = RM_MOTOR_120_DEGREE_Reset,
    .errorSet        = RM_MOTOR_120_DEGREE_ErrorSet,
    .speedSet        = RM_MOTOR_120_DEGREE_SpeedSet,
    .positionSet     = RM_MOTOR_120_DEGREE_PositionSet,
    .statusGet       = RM_MOTOR_120_DEGREE_StatusGet,
    .angleGet        = RM_MOTOR_120_DEGREE_AngleGet,
    .speedGet        = RM_MOTOR_120_DEGREE_SpeedGet,
    .waitStopFlagGet = RM_MOTOR_120_DEGREE_WaitStopFlagGet,
    .errorCheck      = RM_MOTOR_120_DEGREE_ErrorCheck,
    .functionSelect  = RM_MOTOR_120_DEGREE_FunctionSelect,
};

/*******************************************************************************************************************//**
 * @addtogroup MOTOR_120_DEGREE
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Configure the motor in register start mode. Implements @ref motor_api_t::open.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_Open
 *
 * @retval FSP_SUCCESS              Successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 *
 * @note
 * This function should only be called once as motor configuration registers can only be written to once so subsequent
 * calls will have no effect.
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_Open (motor_ctrl_t * const p_ctrl, motor_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    motor_120_degree_extended_cfg_t * p_extended_cfg = (motor_120_degree_extended_cfg_t *) p_cfg->p_extend;

    /* Start 120 control module */
    if (p_extended_cfg != NULL)
    {
        p_extended_cfg->p_motor_120_control_instance->p_api->open(p_extended_cfg->p_motor_120_control_instance->p_ctrl,
                                                                  p_extended_cfg->p_motor_120_control_instance->p_cfg);
    }

    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->u2_error_info = MOTOR_ERROR_NONE;

    rm_motor_120_degree_statemachine_init(&(p_instance_ctrl->st_statem));

    /* Mark driver as open */
    p_instance_ctrl->open = MOTOR_120_DEGREE_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Disables specified motor control block. Implements @ref motor_api_t::close.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_Close
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_Close (motor_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_degree_extended_cfg_t * p_extended_cfg =
        (motor_120_degree_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* close using modules */
    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        p_extended_cfg->p_motor_120_control_instance->p_api->close(p_extended_cfg->p_motor_120_control_instance->p_ctrl);
    }

    p_instance_ctrl->open = 0;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Reset motor control block. Implements @ref motor_api_t::reset.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_Reset
 *
 * @retval FSP_SUCCESS              Successfully resetted.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_Reset (motor_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Reset is valid only at "ERROR" status */
    if (MOTOR_ERROR_NONE != p_instance_ctrl->u2_error_info)
    {
        rm_motor_120_degree_statemachine_event(p_instance_ctrl, MOTOR_120_DEGREE_CTRL_EVENT_RESET);

        /* clear error info */
        p_instance_ctrl->u2_error_info = MOTOR_ERROR_NONE;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Run motor (Start motor rotation). Implements @ref motor_api_t::run.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_Run
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_Run (motor_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_120_degree_statemachine_event(p_instance_ctrl, MOTOR_120_DEGREE_CTRL_EVENT_RUN);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Stop motor (Stop motor rotation). Implements @ref motor_api_t::stop.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_Stop
 *
 * @retval FSP_SUCCESS              Successfully stopped.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_Stop (motor_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rm_motor_120_degree_statemachine_event(p_instance_ctrl, MOTOR_120_DEGREE_CTRL_EVENT_STOP);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set error information. Implements @ref motor_api_t::errorSet.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_ErrorSet
 *
 * @retval FSP_SUCCESS              Successfully set error infomation.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_ErrorSet (motor_ctrl_t * const p_ctrl, motor_error_t const error)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->u2_error_info |= (uint16_t) error;
    rm_motor_120_degree_statemachine_event(p_instance_ctrl, MOTOR_120_DEGREE_CTRL_EVENT_ERROR);

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set speed reference[rpm]. Implements @ref motor_api_t::speedSet.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_SpeedSet
 *
 * @retval FSP_SUCCESS              Successfully set speed reference.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_SpeedSet (motor_ctrl_t * const p_ctrl, float const speed_rpm)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    motor_120_degree_extended_cfg_t * p_extended_cfg =
        (motor_120_degree_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    p_instance_ctrl->f_speed_rpm = speed_rpm;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        err = p_extended_cfg->p_motor_120_control_instance->p_api->speedSet(
            p_extended_cfg->p_motor_120_control_instance->p_ctrl,
            speed_rpm);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Get current control status. Implements @ref motor_api_t::statusGet.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_StatusGet
 *
 * @retval FSP_SUCCESS              Successfully got current control status.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_POINTER  Data received pointer is invalid.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_StatusGet (motor_ctrl_t * const p_ctrl, uint8_t * const p_status)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_DEGREE_ERROR_RETURN(p_status != NULL, FSP_ERR_INVALID_POINTER);
#endif

    *p_status = (uint8_t) p_instance_ctrl->st_statem.status;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Get rotational speed. Implements @ref motor_api_t::speedGet.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_SpeedGet
 *
 * @retval FSP_SUCCESS              Successfully got rotational speed.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_POINTER  Data received pointer is invalid.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_SpeedGet (motor_ctrl_t * const p_ctrl, float * const p_speed_rpm)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_DEGREE_ERROR_RETURN(p_speed_rpm != NULL, FSP_ERR_INVALID_POINTER);
#endif

    motor_120_degree_extended_cfg_t * p_extended_cfg =
        (motor_120_degree_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        err = p_extended_cfg->p_motor_120_control_instance->p_api->speedGet(
            p_extended_cfg->p_motor_120_control_instance->p_ctrl,
            p_speed_rpm);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Get wait stop flag. Implements @ref motor_api_t::waitStopFlagGet.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_WaitStopFlagGet
 *
 * @retval FSP_SUCCESS              Successfully got wait stop flag.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_POINTER  Data received pointer is invalid.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_WaitStopFlagGet (motor_ctrl_t * const           p_ctrl,
                                               motor_wait_stop_flag_t * const p_flag_wait_stop)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_DEGREE_ERROR_RETURN(p_flag_wait_stop != NULL, FSP_ERR_INVALID_POINTER);
#endif

    motor_120_control_wait_stop_flag_t temp_flag;

    motor_120_degree_extended_cfg_t * p_extended_cfg =
        (motor_120_degree_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        err = p_extended_cfg->p_motor_120_control_instance->p_api->waitStopFlagGet(
            p_extended_cfg->p_motor_120_control_instance->p_ctrl,
            &temp_flag);

        if (temp_flag == MOTOR_120_CONTROL_WAIT_STOP_FLAG_CLEAR)
        {
            *p_flag_wait_stop = MOTOR_WAIT_STOP_FLAG_CLEAR;
        }
        else
        {
            *p_flag_wait_stop = MOTOR_WAIT_STOP_FLAG_SET;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Check the occurunce of error. Implements @ref motor_api_t::errorCheck.
 *
 * Example:
 * @snippet rm_motor_120_degree_example.c RM_MOTOR_120_DEGREE_ErrorCheck
 *
 * @retval FSP_SUCCESS              Successfully error checke process.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_POINTER  Data received pointer is invalid.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_ErrorCheck (motor_ctrl_t * const p_ctrl, uint16_t * const p_error)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_instance_ctrl_t * p_instance_ctrl = (motor_120_degree_instance_ctrl_t *) p_ctrl;

#if MOTOR_120_DEGREE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    MOTOR_120_DEGREE_ERROR_RETURN(MOTOR_120_DEGREE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    MOTOR_120_DEGREE_ERROR_RETURN(p_error != NULL, FSP_ERR_INVALID_POINTER);
#endif

    motor_120_degree_extended_cfg_t * p_extended_cfg =
        (motor_120_degree_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    float f4_temp_speed = 0.0F;
    motor_120_driver_current_status_t temp_crnt_status;

    temp_crnt_status.iu  = 0.0F;
    temp_crnt_status.iv  = 0.0F;
    temp_crnt_status.iw  = 0.0F;
    temp_crnt_status.vdc = 0.0F;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        p_extended_cfg->p_motor_120_control_instance->p_api->speedGet(
            p_extended_cfg->p_motor_120_control_instance->p_ctrl,
            &f4_temp_speed);

        p_extended_cfg->p_motor_120_control_instance->p_api->currentGet(
            p_extended_cfg->p_motor_120_control_instance->p_ctrl,
            &temp_crnt_status);
    }

    p_instance_ctrl->u2_error_info |= rm_motor_120_degree_error_check(p_instance_ctrl,
                                                                      temp_crnt_status.iu,
                                                                      temp_crnt_status.iv,
                                                                      temp_crnt_status.iw,
                                                                      temp_crnt_status.vdc,
                                                                      f4_temp_speed);

    *p_error = p_instance_ctrl->u2_error_info;

    if (MOTOR_ERROR_NONE != p_instance_ctrl->u2_error_info)
    {
        rm_motor_120_degree_statemachine_event(p_instance_ctrl, MOTOR_120_DEGREE_CTRL_EVENT_ERROR);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief Set position reference. Implements @ref motor_api_t::positionSet.
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_PositionSet (motor_ctrl_t * const                      p_ctrl,
                                           motor_speed_position_data_t const * const p_position)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_position);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Set position reference. Implements @ref motor_api_t::angleGet.
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_AngleGet (motor_ctrl_t * const p_ctrl, float * const p_angle_rad)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_angle_rad);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Select using function. Implements @ref motor_api_t::functionSelect.
 *
 * @retval FSP_ERR_UNSUPPORTED      Unsupported.
 *
 * @note
 *
 **********************************************************************************************************************/
fsp_err_t RM_MOTOR_120_DEGREE_FunctionSelect (motor_ctrl_t * const p_ctrl, motor_function_select_t const function)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(function);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MOTOR_120_DEGREE)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*****  For Status Transition *****/

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_active
 * Description   : Activates the motor control system and enables PWM output
 * Arguments     : p_ctrl  - Pointer to motor control structure
 * Return Value  : error information
 **********************************************************************************************************************/
static uint8_t rm_motor_120_degree_active (motor_120_degree_instance_ctrl_t * p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_extended_cfg_t * p_extended_cfg = (motor_120_degree_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        err = p_extended_cfg->p_motor_120_control_instance->p_api->run(
            p_extended_cfg->p_motor_120_control_instance->p_ctrl);
    }

    return (uint8_t) err;
}                                      /* End of function rm_motor_120_degree_active() */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_inactive
 * Description   : Deactivates the motor control system and disables PWM output
 * Arguments     : p_ctrl  - Pointer to motor control structure
 * Return Value  : error information
 **********************************************************************************************************************/
static uint8_t rm_motor_120_degree_inactive (motor_120_degree_instance_ctrl_t * p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    motor_120_degree_extended_cfg_t * p_extended_cfg = (motor_120_degree_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        err = p_extended_cfg->p_motor_120_control_instance->p_api->stop(
            p_extended_cfg->p_motor_120_control_instance->p_ctrl);
    }

    return (uint8_t) err;
}                                      /* End of function rm_motor_120_degree_inactive() */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_nowork
 * Description   : The empty dummy function used to fill the blank in action table
 * Arguments     : p_ctrl  - Pointer to motor control structure
 * Return Value  : Always success (0)
 **********************************************************************************************************************/
static uint8_t rm_motor_120_degree_nowork (motor_120_degree_instance_ctrl_t * p_ctrl)
{
    motor_120_degree_extended_cfg_t * p_extended_cfg = (motor_120_degree_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        /* Do nothing because it is a dummy function */
    }

    return 0;
}                                      /* End of function rm_motor_120_degree_nowork() */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_reset
 * Description   : Resets the configurations to default and clear error flags
 * Arguments     : p_ctrl  - Pointer to motor control structure
 * Return Value  : The result of action, Always success(0)
 **********************************************************************************************************************/
static uint8_t rm_motor_120_degree_reset (motor_120_degree_instance_ctrl_t * p_ctrl)
{
    motor_120_degree_extended_cfg_t * p_extended_cfg = (motor_120_degree_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        p_extended_cfg->p_motor_120_control_instance->p_api->reset(p_extended_cfg->p_motor_120_control_instance->p_ctrl);
    }

    return 0;
}                                      /* End of function rm_motor_120_degree_reset() */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_error
 * Description   : Executes the post-processing (include stopping the PWM output) when an error has been detected
 * Arguments     : p_ctrl  - Pointer to motor control structure
 * Return Value  : The result of action, Always success(0)
 **********************************************************************************************************************/
static uint8_t rm_motor_120_degree_error (motor_120_degree_instance_ctrl_t * p_ctrl)
{
    motor_120_degree_extended_cfg_t * p_extended_cfg = (motor_120_degree_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (p_extended_cfg->p_motor_120_control_instance != NULL)
    {
        p_extended_cfg->p_motor_120_control_instance->p_api->reset(p_extended_cfg->p_motor_120_control_instance->p_ctrl);
    }

    return 0;
}                                      /* End of function mtr_act_error */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_statemachine_init
 * Description   : Initializes state machine for motor drive system
 * Arguments     : p_state_machine   - the pointer to the state machine data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_degree_statemachine_init (motor_120_degree_statemachine_t * p_state_machine)
{
    rm_motor_120_degree_statemachine_reset(p_state_machine);
}                                      /* End of function rm_motor_120_degree_statemachine_init */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_statemachine_reset
 * Description   : Resets state machine
 * Arguments     : p_state_machine   - the pointer to the state machine data structure
 * Return Value  : None
 **********************************************************************************************************************/
static void rm_motor_120_degree_statemachine_reset (motor_120_degree_statemachine_t * p_state_machine)
{
    p_state_machine->status          = MOTOR_120_DEGREE_CTRL_STATUS_STOP;
    p_state_machine->status_next     = MOTOR_120_DEGREE_CTRL_STATUS_STOP;
    p_state_machine->u2_error_status = MOTOR_120_DEGREE_STATEMACHINE_ERROR_NONE;
}                                      /* End of function rm_motor_120_degree_statemachine_reset */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_statemachine_event
 * Description   : Performs state transition and execute corresponding action when
 *                 specified event happen
 * Arguments     : p_ctrl  - the pointer to the structure of motor senserless control
 *                 u1_event          - the event index to be executed
 *                   MOTOR_120_DEGREE_CTRL_EVENT_STOP    Stop the motor drive system
 *                   MOTOR_120_DEGREE_CTRL_EVENT_RUN     Activate the motor drive system
 *                   MOTOR_120_DEGREE_CTRL_EVENT_ERROR   Throw an error and stop driving
 *                   MOTOR_120_DEGREE_CTRL_EVENT_RESET   Reset the configurations of motor drive system
 * Return Value  : The error flags of the state machine
 *                   BIT0: Event index is out of bound, please check the u1_event
 *                   BIT1: State index is out of bound
 *                   BIT2: Action error (value other than 0 returned from action)
 **********************************************************************************************************************/
static uint16_t rm_motor_120_degree_statemachine_event (motor_120_degree_instance_ctrl_t * p_ctrl,
                                                        motor_120_degree_ctrl_event_t      u1_event)
{
    motor_120_degree_action_t func_action;
    uint8_t action_ret;

    p_ctrl->st_statem.u2_error_status = MOTOR_120_DEGREE_STATEMACHINE_ERROR_NONE;

    /* Check if accessing state transition table out of bound */
    if (MOTOR_120_DEGREE_STATEMACHINE_SIZE_EVENT <= u1_event)
    {
        /* Event is out of bound */
        u1_event = MOTOR_120_DEGREE_CTRL_EVENT_ERROR;
        p_ctrl->st_statem.u2_error_status |= MOTOR_120_DEGREE_STATEMACHINE_ERROR_EVENTOUTBOUND;
    }

    if (MOTOR_120_DEGREE_STATEMACHINE_SIZE_STATE <= p_ctrl->st_statem.status)
    {
        /* State is out of bound */
        u1_event                           = MOTOR_120_DEGREE_CTRL_EVENT_ERROR;
        p_ctrl->st_statem.status           = MOTOR_120_DEGREE_CTRL_STATUS_STOP;
        p_ctrl->st_statem.u2_error_status |= MOTOR_120_DEGREE_STATEMACHINE_ERROR_STATEOUTBOUND;
    }

    /*
     * current_event : Event happening
     * status        : Current status
     * status_next   : Status after action executed
     */
    p_ctrl->st_statem.current_event = u1_event;
    p_ctrl->st_statem.status_next   =
        (motor_120_degree_ctrl_status_t) (state_transition_table[u1_event][p_ctrl->st_statem.status]);

    /* Get action function from action table and execute action */
    func_action = motor_120_degree_action_table[u1_event][p_ctrl->st_statem.status];
    action_ret  = func_action(p_ctrl);

    /* If return value is not zero, set the action exception flag */
    if (action_ret != 0U)
    {
        p_ctrl->st_statem.u2_error_status |= MOTOR_120_DEGREE_STATEMACHINE_ERROR_ACTIONEXCEPTION;
    }

    p_ctrl->st_statem.status = p_ctrl->st_statem.status_next;

    return p_ctrl->st_statem.u2_error_status;
}                                      /* End of function rm_motor_120_degree_statemachine_event */

/*****  For Status Transition *****/

/***********************************************************************************************************************
 * Function Name : rm_motor_check_over_speed_error
 * Description   : Checks over-speed error
 * Arguments     : f4_speed - The electrical speed
 *                 f4_speed_limit - The speed threshold of the over-speed error, should be a positive value
 * Return Value  : The over-speed error flag
 **********************************************************************************************************************/
static inline uint16_t rm_motor_check_over_speed_error (float f4_speed, float f4_speed_limit)
{
    float    f4_temp0;
    uint16_t u2_temp0;

    u2_temp0 = MOTOR_ERROR_NONE;

    f4_temp0 = fabsf(f4_speed);
    if (f4_temp0 > f4_speed_limit)
    {
        u2_temp0 = MOTOR_ERROR_OVER_SPEED;
    }

    return u2_temp0;
}                                      /* End of function rm_motor_check_over_speed_error */

/***********************************************************************************************************************
 * Function Name : rm_motor_check_over_voltage_error
 * Description   : Checks over-voltage error
 * Arguments     : f4_vdc - The actual VDC value [V]
 *                f4_overvoltage_limit - The threshold voltage[V] of over-voltage error
 * Return Value  : The flag of over-voltage error
 **********************************************************************************************************************/
static inline uint16_t rm_motor_check_over_voltage_error (float f4_vdc, float f4_overvoltage_limit)
{
    uint16_t u2_temp0;

    u2_temp0 = MOTOR_ERROR_NONE;

    if (f4_vdc > f4_overvoltage_limit)
    {
        u2_temp0 = MOTOR_ERROR_OVER_VOLTAGE;
    }

    return u2_temp0;
}                                      /* End of function rm_motor_check_over_voltage_error */

/***********************************************************************************************************************
 * Function Name : rm_motor_check_low_voltage_error
 * Description   : Checks low-voltage error
 * Arguments     : f4_vdc - The actual Vdc value [V]
 *                f4_lowvoltage_limit - The threshold voltage[V] of low-voltage error
 * Return Value  : The flag of low-voltage error
 **********************************************************************************************************************/
static inline uint16_t rm_motor_check_low_voltage_error (float f4_vdc, float f4_lowvoltage_limit)
{
    uint16_t u2_temp0;

    u2_temp0 = MOTOR_ERROR_NONE;

    if (f4_vdc < f4_lowvoltage_limit)
    {
        u2_temp0 = MOTOR_ERROR_LOW_VOLTAGE;
    }

    return u2_temp0;
}                                      /* End of function rm_motor_check_low_voltage_error */

/***********************************************************************************************************************
 * Function Name : rm_motor_check_over_current_error
 * Description   : Checks over-current error
 * Arguments     : f4_iu - The actual U-phase current value [A]
 *                f4_iv - The actual V-phase current value [A]
 *                f4_iw - The actual W-phase current value [A]
 *                f4_oc_limit - The threshold current[A] of over-current error
 * Return Value  : The flag of over-current error
 **********************************************************************************************************************/
static inline uint16_t rm_motor_check_over_current_error (float f4_iu, float f4_iv, float f4_iw, float f4_oc_limit)
{
    float    f4_temp0 = 0.0F;
    uint16_t u2_temp0 = 0U;

    u2_temp0 = MOTOR_ERROR_NONE;       /* Initialize */

    f4_temp0 = fabsf(f4_iu);
    if (f4_temp0 > f4_oc_limit)
    {
        u2_temp0 = 1U;
    }

    f4_temp0 = fabsf(f4_iv);
    if (f4_temp0 > f4_oc_limit)
    {
        u2_temp0 = 1U;
    }

    f4_temp0 = fabsf(f4_iw);
    if (f4_temp0 > f4_oc_limit)
    {
        u2_temp0 = 1U;
    }

    if (1U == u2_temp0)
    {
        u2_temp0 = MOTOR_ERROR_OVER_CURRENT_SW;
    }

    return u2_temp0;
}                                      /* End of function rm_motor_check_over_current_error */

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_error_check
 * Description   : Checks the errors
 * Arguments     : p_ctrl - Pointer to motor control structure
 *               : f_iu  - U Phase current
 *               : f_iv  - V Phase current
 *               : f_iw  - W Phase current
 *               : f_vdc - Main line voltage
 *               : f_speed - Motor rotational speed [rpm]
 * Return Value  : Detected error information
 **********************************************************************************************************************/
static uint16_t rm_motor_120_degree_error_check (motor_120_degree_instance_ctrl_t * p_ctrl,
                                                 float                              f_iu,
                                                 float                              f_iv,
                                                 float                              f_iw,
                                                 float                              f_vdc,
                                                 float                              f_speed)
{
    uint16_t u2_error_flags = 0U;
    motor_120_control_timeout_error_flag_t u1_temp_to_error_flag;
    motor_120_control_pattern_error_flag_t u1_temp_ptn_error_flag;
    motor_120_control_voltage_ref_t        u1_voltage_ref;
    motor_120_degree_extended_cfg_t      * p_extended_cfg =
        (motor_120_degree_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    motor_120_control_instance_t const * p_motor_120_control_instance =
        (motor_120_control_instance_t *) p_extended_cfg->p_motor_120_control_instance;

    /* Over current error check */
    u2_error_flags |= rm_motor_check_over_current_error(f_iu, f_iv, f_iw, p_extended_cfg->f_overcurrent_limit);

    /* Over voltage error check */
    u2_error_flags |= rm_motor_check_over_voltage_error(f_vdc, p_extended_cfg->f_overvoltage_limit);

    /* Low voltage error check */
    u2_error_flags |= rm_motor_check_low_voltage_error(f_vdc, p_extended_cfg->f_lowvoltage_limit);

    if (p_motor_120_control_instance != NULL)
    {
        /* Over speed error check */
        p_motor_120_control_instance->p_api->voltageRefGet(p_motor_120_control_instance->p_ctrl, &u1_voltage_ref);
        if (u1_voltage_ref == MOTOR_120_CONTROL_VOLTAGE_REF_PI_OUTPUT)
        {
            u2_error_flags |= rm_motor_check_over_speed_error(f_speed, p_extended_cfg->f_overspeed_limit);
        }

        /* timeout error check (undetected zerocross) */
        p_motor_120_control_instance->p_api->timeoutErrorFlagGet(p_motor_120_control_instance->p_ctrl,
                                                                 &u1_temp_to_error_flag);

        if (MOTOR_120_CONTROL_TIMEOUT_ERROR_FLAG_SET == u1_temp_to_error_flag)
        {
            u2_error_flags |= MOTOR_ERROR_BEMF_TIMEOUT;
        }

        /* Bemf/Hall pattern error check */
        p_motor_120_control_instance->p_api->patternErrorFlagGet(p_motor_120_control_instance->p_ctrl,
                                                                 &u1_temp_ptn_error_flag);

        if (MOTOR_120_CONTROL_PATTERN_ERROR_FLAG_SET == u1_temp_ptn_error_flag)
        {
            u2_error_flags |= MOTOR_ERROR_BEMF_PATTERN;
        }
    }

    return u2_error_flags;
}                                      /* End of function rm_motor_120_degree_error_check */

/*****  Callback Function *****/

/***********************************************************************************************************************
 * Function Name : rm_motor_120_degree_120_control_callback
 * Description   : 120 control callback function (Perform at timer cyclic interrupt)
 * Arguments     : p_args - speed control interface argument
 * Return Value  : None
 **********************************************************************************************************************/
void rm_motor_120_degree_120_control_callback (motor_120_control_callback_args_t * p_args)
{
    motor_instance_t                 * p_instance = (motor_instance_t *) p_args->p_context;
    motor_120_degree_instance_ctrl_t * p_ctrl     = (motor_120_degree_instance_ctrl_t *) p_instance->p_ctrl;
    motor_callback_args_t              temp_args_t;

    switch (p_args->event)
    {
        case MOTOR_120_CONTROL_EVENT_ADC_FORWARD:
        {
            /* Invoke the callback function if it is set. */
            if (NULL != p_ctrl->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_CALLBACK_EVENT_ADC_FORWARD;
                temp_args_t.p_context = p_ctrl->p_cfg->p_context;
                (p_ctrl->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        case MOTOR_120_CONTROL_EVENT_ADC_BACKWARD:
        {
            /* Invoke the callback function if it is set. */
            if (NULL != p_ctrl->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_CALLBACK_EVENT_ADC_BACKWARD;
                temp_args_t.p_context = p_ctrl->p_cfg->p_context;
                (p_ctrl->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        case MOTOR_120_CONTROL_EVENT_CYCLE_FORWARD:
        {
            /* Invoke the callback function if it is set. */
            if (NULL != p_ctrl->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_CALLBACK_EVENT_CYCLE_FORWARD;
                temp_args_t.p_context = p_ctrl->p_cfg->p_context;
                (p_ctrl->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        case MOTOR_120_CONTROL_EVENT_CYCLE_BACKWARD:
        {
            /* Invoke the callback function if it is set. */
            if (NULL != p_ctrl->p_cfg->p_callback)
            {
                temp_args_t.event     = MOTOR_CALLBACK_EVENT_CYCLE_BACKWARD;
                temp_args_t.p_context = p_ctrl->p_cfg->p_context;
                (p_ctrl->p_cfg->p_callback)(&temp_args_t);
            }

            break;
        }

        default:
        {
            /* Do nothing */
            break;
        }
    }
}                                      /* End of function rm_motor_120_degree_120_control_callback() */
