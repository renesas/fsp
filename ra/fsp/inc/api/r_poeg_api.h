/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_TIMERS_INTERFACES
 * @defgroup POEG_API POEG Interface
 *
 * @brief Interface for the Port Output Enable for GPT.
 *
 * Defines the API and data structures for the Port Output Enable for GPT (POEG) interface.
 *
 * @section POEG_API_SUMMARY Summary
 * @brief The POEG disables GPT output pins based on configurable events.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_POEG_API_H
#define R_POEG_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#ifndef BSP_OVERRIDE_POEG_STATE_T

/** POEG states. */
typedef enum e_poeg_state
{
    POEG_STATE_NO_DISABLE_REQUEST                = 0,       ///< GPT output is not disabled by POEG
    POEG_STATE_PIN_DISABLE_REQUEST               = 1U << 0, ///< GPT output disabled due to GTETRG pin level
    POEG_STATE_GPT_OR_COMPARATOR_DISABLE_REQUEST = 1U << 1, ///< GPT output disabled due to high speed analog comparator or GPT
    POEG_STATE_OSCILLATION_STOP_DISABLE_REQUEST  = 1U << 2, ///< GPT output disabled due to main oscillator stop
    POEG_STATE_SOFTWARE_STOP_DISABLE_REQUEST     = 1U << 3, ///< GPT output disabled due to poeg_api_t::outputDisable()

    /** GPT output disable request active from the GTETRG pin. If a filter is used, this flag represents the state of
     * the filtered input. */
    POEG_STATE_PIN_DISABLE_REQUEST_ACTIVE = 1U << 16,
} poeg_state_t;

#endif

#ifndef BSP_OVERRIDE_POEG_TRIGGER_T

/** Triggers that will disable GPT output pins. */
typedef enum e_poeg_trigger
{
    /** Software disable is always supported with POEG. Select this option if no other triggers are used. */
    POEG_TRIGGER_SOFTWARE         = 0U,
    POEG_TRIGGER_PIN              = 1U << 0, ///< Disable GPT output based on GTETRG input level
    POEG_TRIGGER_GPT_OUTPUT_LEVEL = 1U << 1, ///< Disable GPT output based on GPT output pin levels
    POEG_TRIGGER_OSCILLATION_STOP = 1U << 2, ///< Disable GPT output based on main oscillator stop
    POEG_TRIGGER_ACMPHS0          = 1U << 4, ///< Disable GPT output based on ACMPHS0 comparator result
    POEG_TRIGGER_ACMPHS1          = 1U << 5, ///< Disable GPT output based on ACMPHS1 comparator result
    POEG_TRIGGER_ACMPHS2          = 1U << 6, ///< Disable GPT output based on ACMPHS2 comparator result
    POEG_TRIGGER_ACMPHS3          = 1U << 7, ///< Disable GPT output based on ACMPHS3 comparator result
    POEG_TRIGGER_ACMPHS4          = 1U << 8, ///< Disable GPT output based on ACMPHS4 comparator result
    POEG_TRIGGER_ACMPHS5          = 1U << 9, ///< Disable GPT output based on ACMPHS5 comparator result
} poeg_trigger_t;

#endif

/** GTETRG polarity. */
typedef enum e_poeg_gtetrg_polarity
{
    POEG_GTETRG_POLARITY_ACTIVE_HIGH = 0U, ///< Disable GPT output based when GTETRG input level is high
    POEG_GTETRG_POLARITY_ACTIVE_LOW  = 1U, ///< Disable GPT output based when GTETRG input level is low
} poeg_gtetrg_polarity_t;

/** GTETRG noise filter. For the input signal to pass through the noise filter, the active level set in
 * @ref poeg_gtetrg_polarity_t must be read 3 consecutive times at the sampling clock selected.
 */
typedef enum e_poeg_gtetrg_noise_filter
{
    POEG_GTETRG_NOISE_FILTER_DISABLED           = 0U, ///< No noise filter applied to GTETRG input
    POEG_GTETRG_NOISE_FILTER_CLK_SOURCE_DIV_1   = 1U, ///< Apply noise filter with sample clock equal to Clock source/1
    POEG_GTETRG_NOISE_FILTER_CLK_SOURCE_DIV_8   = 3U, ///< Apply noise filter with sample clock equal to Clock source/8
    POEG_GTETRG_NOISE_FILTER_CLK_SOURCE_DIV_32  = 5U, ///< Apply noise filter with sample clock equal to Clock source/32
    POEG_GTETRG_NOISE_FILTER_CLK_SOURCE_DIV_128 = 7U, ///< Apply noise filter with sample clock equal to Clock source/128
} poeg_gtetrg_noise_filter_t;

/** POEG status */
typedef struct st_poeg_status
{
    poeg_state_t state;                ///< Current state of POEG
} poeg_status_t;

/** Callback function parameter data. */
typedef struct st_poeg_callback_args
{
    void const * p_context;            ///< Placeholder for user data, set in @ref poeg_cfg_t.
} poeg_callback_args_t;

/** POEG control block.  Allocate an instance specific control block to pass into the POEG API calls.
 */
typedef void poeg_ctrl_t;

/** User configuration structure, used in the open function. */
typedef struct st_poeg_cfg
{
    poeg_trigger_t             trigger;      ///< Select one or more triggers for the POEG
    poeg_gtetrg_polarity_t     polarity;     ///< Select the polarity for the GTETRG pin
    poeg_gtetrg_noise_filter_t noise_filter; ///< Configure the GTETRG noise filter

    /** Callback called when a POEG interrupt occurs. */
    void (* p_callback)(poeg_callback_args_t * p_args);

    /** Placeholder for user data. Passed to the user callback in @ref poeg_callback_args_t. */
    void const * p_context;
    uint32_t     unit;                 ///< POEG unit to be used
    uint32_t     channel;              ///< Channel 0 corresponds to GTETRGA, 1 to GTETRGB, etc.
    IRQn_Type    irq;                  ///< Interrupt number assigned to this instance
    uint8_t      ipl;                  ///< POEG interrupt priority
} poeg_cfg_t;

/** Port Output Enable for GPT (POEG) API structure. POEG functions implemented at the HAL layer will follow this API. */
typedef struct st_poeg_api
{
    /** Initial configuration.
     *
     * @param[in]   p_ctrl      Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg       Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(poeg_ctrl_t * const p_ctrl, poeg_cfg_t const * const p_cfg);

    /** Gets the current driver state.
     *
     * @param[in]   p_ctrl      Control block set in @ref poeg_api_t::open call.
     * @param[out]  p_status    Provides the current state of the POEG.
     */
    fsp_err_t (* statusGet)(poeg_ctrl_t * const p_ctrl, poeg_status_t * p_status);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Control block set in @ref poeg_api_t::open call for this timer.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(poeg_ctrl_t * const p_ctrl, void (* p_callback)(poeg_callback_args_t *),
                              void const * const p_context, poeg_callback_args_t * const p_callback_memory);

    /** Disables GPT output pins by software request.
     *
     * @param[in]   p_ctrl      Control block set in @ref poeg_api_t::open call.
     */
    fsp_err_t (* outputDisable)(poeg_ctrl_t * const p_ctrl);

    /** Attempts to clear status flags to reenable GPT output pins. Confirm all status flags are cleared after calling
     * this function by calling poeg_api_t::statusGet().
     *
     * @param[in]   p_ctrl      Control block set in @ref poeg_api_t::open call.
     */
    fsp_err_t (* reset)(poeg_ctrl_t * const p_ctrl);

    /** Disables POEG interrupt.
     *
     * @param[in]   p_ctrl      Control block set in @ref poeg_api_t::open call.
     */
    fsp_err_t (* close)(poeg_ctrl_t * const p_ctrl);
} poeg_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_poeg_instance
{
    poeg_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    poeg_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    poeg_api_t const * p_api;          ///< Pointer to the API structure for this instance
} poeg_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup POEG_API)
 **********************************************************************************************************************/
