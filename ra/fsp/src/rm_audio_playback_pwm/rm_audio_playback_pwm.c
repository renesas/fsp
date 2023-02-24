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
#include "bsp_cfg.h"
#include <string.h>
#include "rm_audio_playback_pwm.h"
#include "rm_audio_playback_api.h"
#if AUDIO_PLAYBACK_PWM_DMAC_SUPPORT_ENABLE
 #include "r_dmac.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define AUDIO_PWM_OPEN                   (0x4150574dU)
#define AUDIO_PLAYBACK_PRV_MAX_LENGTH    (0x10000U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if AUDIO_PLAYBACK_PWM_DMAC_SUPPORT_ENABLE
void rm_audio_playback_pwm_callback_dmac(dmac_callback_args_t * p_args);

#endif
void rm_audio_playback_pwm_callback_timer(timer_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const audio_playback_api_t g_audio_playback_on_audio_playback_pwm =
{
    .open  = RM_AUDIO_PLAYBACK_PWM_Open,
    .start = RM_AUDIO_PLAYBACK_PWM_Start,
    .stop  = RM_AUDIO_PLAYBACK_PWM_Stop,
    .play  = RM_AUDIO_PLAYBACK_PWM_Play,
    .close = RM_AUDIO_PLAYBACK_PWM_Close,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_AUDIO_PLAYBACK_PWM
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens and configures the Audio Playback with PWM driver. Sets playback speed and transfer rate to read the audio buffer.
 *
 * Example:
 * @snippet rm_audio_playback_pwm_example.c RM_AUDIO_PLAYBACK_PWM_Open
 *
 * @retval FSP_SUCCESS                  Audio Playback module successfully configured.
 * @retval FSP_ERR_ALREADY_OPEN         Module already open.
 * @retval FSP_ERR_ASSERTION            One or more pointers point to NULL or callback is NULL.
 *
 ***********************************************************************************************************************/
fsp_err_t RM_AUDIO_PLAYBACK_PWM_Open (audio_playback_ctrl_t * const      p_api_ctrl,
                                      audio_playback_cfg_t const * const p_cfg)
{
    audio_playback_pwm_instance_ctrl_t * p_ctrl = (audio_playback_pwm_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err;

    /* Validate the parameters and check if the module is initialized */
#if AUDIO_PLAYBACK_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    audio_playback_pwm_extended_cfg_t * p_extend = (audio_playback_pwm_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_extend->p_lower_lvl_timer);
    FSP_ASSERT(NULL != p_extend->p_lower_lvl_transfer);
    FSP_ERROR_RETURN(AUDIO_PWM_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#else
    audio_playback_pwm_extended_cfg_t * p_extend = (audio_playback_pwm_extended_cfg_t *) p_cfg->p_extend;
#endif

    /* save pointers for later use */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback_memory = NULL;

    /* Open timer instance in PWM mode at the user selected playback frequency */
    timer_instance_t const * p_timer = p_extend->p_lower_lvl_timer;
    err = p_timer->p_api->open(p_timer->p_ctrl, p_timer->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Configure transfer */
    transfer_instance_t const * p_transfer = p_extend->p_lower_lvl_transfer;
    transfer_info_t           * p_info     = p_transfer->p_cfg->p_info;
    p_info->p_dest = p_extend->p_timer_duty_reg;
    p_info->transfer_settings_word_b.size = p_extend->transfer_size;

    /* Open transfer driver */
    err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /** Store driver data. */
    p_ctrl->p_lower_lvl_timer    = p_timer;
    p_ctrl->p_lower_lvl_transfer = p_transfer;

    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

    /* Mark driver as open. */
    p_ctrl->open = AUDIO_PWM_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the module driver. Enables module stop mode.
 *
 * @retval FSP_SUCCESS          Module successfully closed.
 * @retval FSP_ERR_NOT_OPEN     Driver not open.
 * @retval FSP_ERR_ASSERTION    Pointer pointing to NULL.
 *
 * @note This function will close all the lower level HAL drivers as well.
 **********************************************************************************************************************/
fsp_err_t RM_AUDIO_PLAYBACK_PWM_Close (audio_playback_ctrl_t * const p_api_ctrl)
{
    audio_playback_pwm_instance_ctrl_t * p_ctrl = (audio_playback_pwm_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err;

    /* Validate the parameter and check if the module is initialized */
#if AUDIO_PLAYBACK_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(AUDIO_PWM_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close timer/PWM driver. */
    err = p_ctrl->p_lower_lvl_timer->p_api->close(p_ctrl->p_lower_lvl_timer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Close transfer driver. */
    err = p_ctrl->p_lower_lvl_transfer->p_api->close(p_ctrl->p_lower_lvl_transfer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Mark driver as closed.  */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Start the PWM HAL driver (AGT or GPT) and timer HAL (AGT or GPT) drivers.
 *
 * * Example:
 * @snippet rm_audio_playback_pwm_example.c RM_AUDIO_PLAYBACK_PWM_Start
 *
 * @retval FSP_SUCCESS              Audio playback hardware started successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Driver not open.
 *                                  This function calls
 *                                  * timer_api_t::start
 *
 **********************************************************************************************************************/
fsp_err_t RM_AUDIO_PLAYBACK_PWM_Start (audio_playback_ctrl_t * const p_api_ctrl)
{
    audio_playback_pwm_instance_ctrl_t * p_ctrl = (audio_playback_pwm_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err;

#if AUDIO_PLAYBACK_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(AUDIO_PWM_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start periodic timer interrupts and PWM peripheral. */
    err = p_ctrl->p_lower_lvl_timer->p_api->start(p_ctrl->p_lower_lvl_timer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stop the PWM HAL driver (AGT or GPT) and timer HAL driver (AGT or GPT).
 *
 * * Example:
 * @snippet rm_audio_playback_pwm_example.c RM_AUDIO_PLAYBACK_PWM_Stop
 *
 * @retval FSP_SUCCESS              Audio playback hardware stopped successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Driver not open.
 *                                  This function calls
 *                                  * timer_api_t::stop
 **********************************************************************************************************************/
fsp_err_t RM_AUDIO_PLAYBACK_PWM_Stop (audio_playback_ctrl_t * const p_api_ctrl)
{
    audio_playback_pwm_instance_ctrl_t * p_ctrl = (audio_playback_pwm_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err;

#if AUDIO_PLAYBACK_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(AUDIO_PWM_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer and PWM Peripheral. */
    err = p_ctrl->p_lower_lvl_timer->p_api->stop(p_ctrl->p_lower_lvl_timer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Play a single audio buffer by input samples to the PWM HAL (AGT or GPT) at the sampling frequency configured by the timer.
 *
 * * Example:
 * @snippet rm_audio_playback_pwm_example.c RM_AUDIO_PLAYBACK_PWM_Play
 *
 * @retval FSP_SUCCESS              Buffer playback began successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_ctrl or p_buffer is NULL or buffer length is greater than 0x10000.
 * @retval FSP_ERR_NOT_OPEN         Driver not open..
 *                                  This function calls
 *                                  * transfer_api_t::reset
 *
 **********************************************************************************************************************/
fsp_err_t RM_AUDIO_PLAYBACK_PWM_Play (audio_playback_ctrl_t * const p_api_ctrl,
                                      void const * const            p_buffer,
                                      uint32_t                      length)
{
    audio_playback_pwm_instance_ctrl_t * p_ctrl = (audio_playback_pwm_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err;

#if AUDIO_PLAYBACK_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_buffer);

    /* Data length should be greater than zero. */
    FSP_ASSERT(length > 0U);

    /* Length restriction is based on DMAC/DTC limitation. */
    FSP_ASSERT(length < AUDIO_PLAYBACK_PRV_MAX_LENGTH);
    FSP_ERROR_RETURN(AUDIO_PWM_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Reset transfer. */
    err = p_ctrl->p_lower_lvl_transfer->p_api->reset(p_ctrl->p_lower_lvl_transfer->p_ctrl,
                                                     p_buffer,
                                                     NULL,
                                                     (uint16_t) length);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/** @} (end defgroup RM_AUDIO_PLAYBACK_PWM) */

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Callback function intercepted from DMAC driver.
 *
 * @param[in]  p_args Callback data can be used to identify what triggered the interrupt.
 **********************************************************************************************************************/
#if AUDIO_PLAYBACK_PWM_DMAC_SUPPORT_ENABLE
void rm_audio_playback_pwm_callback_dmac (dmac_callback_args_t * p_args)
{
    /* Recover context from ISR. */
    audio_playback_pwm_instance_ctrl_t * p_ctrl = (audio_playback_pwm_instance_ctrl_t *) (p_args->p_context);

    /* Create callback arguments. */
    audio_playback_callback_args_t args;
    args.p_context = p_ctrl->p_context;
    args.event     = AUDIO_PLAYBACK_EVENT_PLAYBACK_COMPLETE;

    /* Call user callback. */
    p_ctrl->p_callback(&args);
}                                      /* End of function rm_audio_playback_pwm_callback_dmac */

#endif

/*******************************************************************************************************************//**
 * Callback function intercepted from timer driver.
 *
 * @param[in]  p_args Callback data can be used to identify what triggered the interrupt.
 **********************************************************************************************************************/

void rm_audio_playback_pwm_callback_timer (timer_callback_args_t * p_args)
{
    /* Recover context from ISR. */
    audio_playback_pwm_instance_ctrl_t * p_ctrl = (audio_playback_pwm_instance_ctrl_t *) (p_args->p_context);

    /* Create callback arguments. */
    audio_playback_callback_args_t args;
    args.p_context = p_ctrl->p_context;
    args.event     = AUDIO_PLAYBACK_EVENT_PLAYBACK_COMPLETE;

    p_ctrl->p_callback(&args);
}                                      /* End of function rm_audio_playback_pwm_callback_timer */
