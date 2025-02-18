/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_AUDIO_INTERFACES
 * @defgroup AUDIO_PLAYBACK_API AUDIO PLAYBACK Interface
 *
 * @brief Interface for the Audio Playback.
 *
 * Defines the API and data structures for the Audio Playback implementation.
 *
 * @section AUDIO_PLAYBACK_API_SUMMARY Summary
 * @brief This module provides common interface for Audio Playback.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_AUDIO_PLAYBACK_API_H
#define RM_AUDIO_PLAYBACK_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_transfer_api.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Callback event types. */
typedef enum e_audio_playback_event
{
    AUDIO_PLAYBACK_EVENT_PLAYBACK_COMPLETE = 1, ///< Audio playback complete event
} audio_playback_event_t;

/** Callback function parameter data */
typedef struct st_audio_playback_callback_args
{
    /** Placeholder for user data. */
    void * p_context;

    audio_playback_event_t event;      ///< Event that triggered the callback
} audio_playback_callback_args_t;

/** Audio Playback control block.  Allocate an instance specific control block to pass into the AUDIO_PLAYBACK API calls.
 */
typedef void audio_playback_ctrl_t;

/** Audio Playback configuration parameters. */
typedef struct st_audio_playback_cfg
{
    void const * p_extend;             ///< Hardware dependent configuration

    /** Callback called when play is complete. */
    void (* p_callback)(audio_playback_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in ::audio_playback_callback_args_t. */
    void * p_context;
} audio_playback_cfg_t;

/** Audio Playback functions implemented by the Audio Playback drivers will follow this API. */
typedef struct st_audio_playback_api
{
    /** Open a audio playback module.
     *
     * @param[in] p_ctrl    Pointer to memory allocated for control block.
     * @param[in]     p_cfg     Pointer to the hardware configurations.
     */
    fsp_err_t (* open)(audio_playback_ctrl_t * const p_ctrl, audio_playback_cfg_t const * const p_cfg);

    /** Start audio playback hardware.
     *
     * @param[in] p_ctrl        Pointer to control block.
     */
    fsp_err_t (* start)(audio_playback_ctrl_t * const p_ctrl);

    /** Stop audio playback hardware.
     *
     * @param[in] p_ctrl        Pointer to control block.
     */
    fsp_err_t (* stop)(audio_playback_ctrl_t * const p_ctrl);

    /** Play audio buffer.
     *
     * @param[in] p_ctrl        Pointer to control block.
     * @param[in] p_buffer      Pointer to buffer with PCM samples to play.  Data must be scaled for audio
     *                          playback hardware.
     * @param[in] length        Length of data in p_buffer.
     */
    fsp_err_t (* play)(audio_playback_ctrl_t * const p_ctrl, void const * const p_buffer, uint32_t length);

    /** Close the audio driver.
     *
     * @param[in] p_ctrl        Pointer to control block initialized in audio_playback_api_t::open.
     */
    fsp_err_t (* close)(audio_playback_ctrl_t * const p_ctrl);
} audio_playback_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_audio_playback_instance
{
    audio_playback_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    audio_playback_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    audio_playback_api_t const * p_api;  ///< Pointer to the API structure for this instance
} audio_playback_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end defgroup AUDIO_PLAYBACK_API)
 **********************************************************************************************************************/
#endif
