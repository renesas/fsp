/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_THREE_PHASE_API_H
#define R_THREE_PHASE_API_H

/*******************************************************************************************************************//**
 * @defgroup THREE_PHASE_API Three-Phase Interface
 * @ingroup RENESAS_TIMERS_INTERFACES
 * @brief Interface for three-phase timer functions.
 *
 * @section THREE_PHASE_API_SUMMARY Summary
 * The Three-Phase interface provides functionality for synchronous start/stop/reset control of three timer channels for
 * use in 3-phase motor control applications.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Leading zeroes removed to avoid coding standard violation. */

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Timer channel indices */
typedef enum e_three_phase_channel
{
    THREE_PHASE_CHANNEL_U,             ///< U-channel index
    THREE_PHASE_CHANNEL_V,             ///< V-channel index
    THREE_PHASE_CHANNEL_W,             ///< W-channel index
} three_phase_channel_t;

/** Buffering mode */
typedef enum e_three_phase_buffer_mode
{
    THREE_PHASE_BUFFER_MODE_SINGLE = 1, ///< Single-buffer mode
    THREE_PHASE_BUFFER_MODE_DOUBLE = 2  ///< Double-buffer mode
} three_phase_buffer_mode_t;

/** Struct for passing duty cycle values to @ref three_phase_api_t::dutyCycleSet */
typedef struct st_three_phase_duty_cycle
{
    /**
     * Duty cycle.
     * Note: When the GPT instances are configured in TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3,
     *       this value sets the duty cycle count that is transfered to GTCCRA/B at the trough.
     */
    uint32_t duty[3];

    /**
     * Double-buffer for duty cycle values.
     * Note: When the GPT instances are configured in TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3,
     *       this value sets the duty cycle count that is transfered to GTCCRA/B at the crest.
     */
    uint32_t duty_buffer[3];
} three_phase_duty_cycle_t;

/** Three-Phase control block.  Allocate an instance specific control block to pass into the timer API calls.
 */
typedef void three_phase_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_three_phase_cfg
{
    three_phase_buffer_mode_t buffer_mode;        ///< Single or double-buffer mode

    /* Pointers to GPT instance structs */
    timer_instance_t const * p_timer_instance[3]; ///< Pointer to the timer instance structs
    three_phase_channel_t    callback_ch;         ///< Channel to enable callback when using three_phase_api_t::callbackSet

    uint32_t channel_mask;                        ///< Bitmask of timer channels used by this module

    /** Placeholder for user data.  Passed to the user callback in @ref timer_callback_args_t. */
    void const * p_context;
    void const * p_extend;                        ///< Extension parameter for hardware specific settings.
} three_phase_cfg_t;

/** Three-Phase API structure. */
typedef struct st_three_phase_api
{
    /** Initial configuration.
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(three_phase_ctrl_t * const p_ctrl, three_phase_cfg_t const * const p_cfg);

    /** Start all three timers synchronously.
     *
     * @param[in]   p_ctrl     Control block set in @ref three_phase_api_t::open call for this timer.
     */
    fsp_err_t (* start)(three_phase_ctrl_t * const p_ctrl);

    /** Stop all three timers synchronously.
     *
     * @param[in]   p_ctrl     Control block set in @ref three_phase_api_t::open call for this timer.
     */
    fsp_err_t (* stop)(three_phase_ctrl_t * const p_ctrl);

    /** Reset all three timers synchronously.
     *
     * @param[in]   p_ctrl     Control block set in @ref three_phase_api_t::open call for this timer.
     */
    fsp_err_t (* reset)(three_phase_ctrl_t * const p_ctrl);

    /** Sets the duty cycle match values.  If the timer is counting, the updated duty cycle is
     * reflected after the next timer expiration.
     *
     *
     * @param[in]   p_ctrl             Control block set in @ref three_phase_api_t::open call for this timer.
     * @param[in]   p_duty_cycle       Duty cycle values for all three timer channels.
     */
    fsp_err_t (* dutyCycleSet)(three_phase_ctrl_t * const p_ctrl, three_phase_duty_cycle_t * const p_duty_cycle);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Control block set in @ref three_phase_api_t::open call.
     * @param[in]   p_callback               Callback function to register with GPT U-channel
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(three_phase_ctrl_t * const p_ctrl, void (* p_callback)(timer_callback_args_t *),
                              void const * const p_context, timer_callback_args_t * const p_callback_memory);

    /** Allows driver to be reconfigured and may reduce power consumption.
     *
     * @param[in]   p_ctrl     Control block set in @ref three_phase_api_t::open call for this timer.
     */
    fsp_err_t (* close)(three_phase_ctrl_t * const p_ctrl);
} three_phase_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_gpt_three_phase_instance
{
    three_phase_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance
    three_phase_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance
    three_phase_api_t const * p_api;   ///< Pointer to the API structure for this instance
} three_phase_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup THREE_PHASE_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
