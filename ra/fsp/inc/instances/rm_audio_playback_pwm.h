/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_AUDIO_PLAYBACK_PWM_H
#define RM_AUDIO_PLAYBACK_PWM_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "rm_audio_playback_api.h"
#include "rm_audio_playback_pwm_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_AUDIO_PLAYBACK_PWM
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_audio_playback_pwm_extended_cfg
{
    void                      * p_timer_duty_reg;     ///< Pointer to target timer duty cycle register.
    transfer_size_t             transfer_size;        ///< Transfer size (timer duty register size).
    timer_instance_t const    * p_lower_lvl_timer;    ///< Timer API used to generate sampling frequency and GPT/AGT API used to access PWM hardware.
    transfer_instance_t const * p_lower_lvl_transfer; ///< Transfer API used to transfer data each sampling frequency.
} audio_playback_pwm_extended_cfg_t;

/** AUDIO_PLAYBACK_PWM instance control block. DO NOT MODIFY. Initialization occurs when RM_AUDIO_PLAYBACK_PWM_Open() is called. */

typedef struct st_audio_playback_pwm_instance_ctrl
{
    /** Callback called when play is complete. */
    void (* p_callback)(audio_playback_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in @ref audio_playback_callback_args_t. */
    void * p_context;
    audio_playback_callback_args_t * p_callback_memory;
    audio_playback_cfg_t const     * p_cfg;           ///< Pointer to the configuration structure
    uint32_t open;                                    ///< Used by driver to check if the control structure is valid

    timer_instance_t const    * p_lower_lvl_timer;    ///< Timer API used to generate sampling frequency and GPT/AGT API used to access PWM hardware.
    transfer_instance_t const * p_lower_lvl_transfer; ///< Transfer API used to transfer data each sampling frequency.
} audio_playback_pwm_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const audio_playback_api_t g_audio_playback_on_audio_playback_pwm;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_AUDIO_PLAYBACK_PWM_Open(audio_playback_ctrl_t * const      p_api_ctrl,
                                     audio_playback_cfg_t const * const p_cfg);

fsp_err_t RM_AUDIO_PLAYBACK_PWM_Start(audio_playback_ctrl_t * const p_api_ctrl);

fsp_err_t RM_AUDIO_PLAYBACK_PWM_Stop(audio_playback_ctrl_t * const p_api_ctrl);

fsp_err_t RM_AUDIO_PLAYBACK_PWM_Play(audio_playback_ctrl_t * const p_api_ctrl,
                                     void const * const            p_buffer,
                                     uint32_t                      length);

fsp_err_t RM_AUDIO_PLAYBACK_PWM_Close(audio_playback_ctrl_t * const p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_AUDIO_PLAYBACK_PWM_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_AUDIO_PLAYBACK_PWM)
 **********************************************************************************************************************/
