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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup AUDIO_PLAYBACK_API AUDIO PLAYBACK Interface
 *
 * @brief Interface for the Audio Playback.
 *
 * Defines the API and data structures for the Audio Playback implementation.
 *
 * @section AUDIO_PLAYBACK_API_SUMMARY Summary
 * @brief This module provides common interface for Audio Playback.
 *
 * Implemented by:
 * @ref RM_AUDIO_PLAYBACK_PWM
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
 * @par Implemented as
 * - audio_playback_pwm_instance_ctrl_t
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
     * @par Implemented as
     * - RM_AUDIO_PLAYBACK_PWM_Open()
     *
     * @param[in] p_ctrl    Pointer to memory allocated for control block.
     * @param[in]     p_cfg     Pointer to the hardware configurations.
     */
    fsp_err_t (* open)(audio_playback_ctrl_t * const p_ctrl, audio_playback_cfg_t const * const p_cfg);

    /** Start audio playback hardware.
     * @par Implemented as
     * - RM_AUDIO_PLAYBACK_PWM_Start()
     *
     * @param[in] p_ctrl        Pointer to control block.
     */
    fsp_err_t (* start)(audio_playback_ctrl_t * const p_ctrl);

    /** Stop audio playback hardware.
     * @par Implemented as
     * - RM_AUDIO_PLAYBACK_PWM_Stop()
     *
     * @param[in] p_ctrl        Pointer to control block.
     */
    fsp_err_t (* stop)(audio_playback_ctrl_t * const p_ctrl);

    /** Play audio buffer.
     * @par Implemented as
     * - RM_AUDIO_PLAYBACK_PWM_Play()
     *
     * @param[in] p_ctrl        Pointer to control block.
     * @param[in] p_buffer      Pointer to buffer with PCM samples to play.  Data must be scaled for audio
     *                          playback hardware.
     * @param[in] length        Length of data in p_buffer.
     */
    fsp_err_t (* play)(audio_playback_ctrl_t * const p_ctrl, void const * const p_buffer, uint32_t length);

    /** Close the audio driver.
     * @par Implemented as
     * - RM_AUDIO_PLAYBACK_PWM_Close()
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
