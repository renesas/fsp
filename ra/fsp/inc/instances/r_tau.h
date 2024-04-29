/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_TAU_H
#define R_TAU_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_tau_cfg.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup TAU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Timer function */
typedef enum e_tau_function
{
    TAU_FUNCTION_INTERVAL                         = 0U, ///< Interval Timer Function
    TAU_FUNCTION_SQUARE_WAVE                      = 1U, ///< Square Wave Function
    TAU_FUNCTION_EXTERNAL_EVENT_COUNT             = 2U, ///< External Event Count Function
    TAU_FUNCTION_DIVIDER                          = 3U, ///< Divider Function
    TAU_FUNCTION_INPUT_PULSE_INTERVAL_MEASUREMENT = 4U, ///< Input Pulse Interval Function
    TAU_FUNCTION_LOW_LEVEL_WIDTH_MEASUREMENT      = 5U, ///< Low Level Width Measure Function
    TAU_FUNCTION_HIGH_LEVEL_WIDTH_MEASUREMENT     = 6U, ///< High Level Width Measure Function
    TAU_FUNCTION_DELAY_COUNT                      = 7U  ///< Delay Count Function
} tau_function_t;

/** Timer bit mode */
typedef enum e_tau_bit_mode
{
    TAU_BIT_MODE_16BIT             = 0U, ///< 16-Bit Timer Mode
    TAU_BIT_MODE_HIGHER_8BIT       = 1U, ///< Higher 8-bit Timer Mode
    TAU_BIT_MODE_LOWER_8BIT        = 2U, ///< Lower 8-bit Timer Mode
    TAU_BIT_MODE_HIGHER_LOWER_8BIT = 3U, ///< Lower and Higher 8-bit Timer Mode
} tau_bit_mode_t;

/** Timer operation clock. */
typedef enum e_tau_operation_ck
{
    TAU_OPERATION_CK00 = 0U,
    TAU_OPERATION_CK01 = 2U,
    TAU_OPERATION_CK02 = 1U,
    TAU_OPERATION_CK03 = 3U
} tau_operation_ck_t;

/** Trigger edge for pulse period measurement mode, high-low measurement, divider, delay counter
 * and event counting mode. */
typedef enum e_tau_trigger_edge
{
    TAU_TRIGGER_EDGE_FALLING = 0U,     ///< Measurement starts or events are counted on falling edge
    TAU_TRIGGER_EDGE_RISING  = 1U,     ///< Measurement starts or events are counted on rising edge
    TAU_TRIGGER_EDGE_BOTH    = 2U,     ///< Events are counted on both edges (pulse period mode and high-low measurement)
} tau_trigger_edge_t;

/** Interrupt and starting Count Mode */
typedef enum e_tau_interrupt_opirq_bit
{
    /* When OPIRQ bit is 0.
     * + Interval Timer, Square Wave, Divider, External Event Count and Input Pulse Measurement function : Timer
     * interrupt is not generated when counting is started (timer output does not change, either).
     * + High-Low Measurement function Timer: interrupt is not generated when counting is started (timer output
     * does not change, either). Start trigger is invalid during counting operation. At that time interrupt is not generated.
     * + Delay Counter function: Start trigger is invalid during counting operation. At that time, interrupt is not generated.
     */
    TAU_INTERRUPT_OPIRQ_BIT_RESET = 0U,

    /* When OPIRQ bit is 1.
     * + Interval Timer, Square Wave, Divider and Input Pulse Measurement function: Timer interrupt is generated when counting is
     * started (timer output also changes).
     * + Delay Counter function: Start trigger is valid during counting operation. At that time, interrupt is not generated.
     */
    TAU_INTERRUPT_OPIRQ_BIT_SET = 1U,
} tau_interrupt_opirq_bit_t;

/** Input source */
typedef enum e_tau_input_source
{
    TAU_INPUT_SOURCE_TI_PIN   = 0U,    ///< Timer Input Source is input pin
    TAU_INPUT_SOURCE_ELC      = 1U,    ///< ELC Timer Input Source
    TAU_INPUT_SOURCE_RXD2_PIN = 2U,    ///< Timer Input Source is RXD2 pin
    TAU_INPUT_SOURCE_MOCO     = 3U,    ///< Timer Input Source is MOCO
    TAU_INPUT_SOURCE_LOCO     = 4U,    ///< Timer Input Source is LOCO
    TAU_INPUT_SOURCE_FSUB     = 5U,    ///< Timer Input Source is FSUB
    TAU_INPUT_SOURCE_NONE     = 6U,    ///< No Timer Input Source
} tau_input_source_t;

/** Level of TAU pin */
typedef enum e_tau_pin_output_cfg
{
    TAU_PIN_OUTPUT_CFG_START_LEVEL_LOW  = 0U, ///< Pin level low
    TAU_PIN_OUTPUT_CFG_START_LEVEL_HIGH = 1U, ///< Pin level high
    TAU_PIN_OUTPUT_CFG_DISABLED         = 2U, ///< Not used as output pin
} tau_pin_output_cfg_t;

/** Input filter, applies TAU in high-low measurement, pulse width measurement, delay counter, divider,
 * or event counter mode. */
typedef enum e_tau_input_noise_filter
{
    TAU_INPUT_NOISE_FILTER_DISABLE = 0U, ///< Disable noise filter
    TAU_INPUT_NOISE_FILTER_ENABLE  = 1U  ///< Enable noise filter
} tau_input_noise_filter_t;

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref timer_api_t::open is called. */
typedef struct st_tau_instance_ctrl
{
    uint32_t            open;                     // Whether or not channel is open
    const timer_cfg_t * p_cfg;                    // Pointer to initial configurations

    uint16_t channel_mask;                        // Channel bitmask
    uint16_t channel_bitmode_mask;                // Channel bitmode mask

    void (* p_callback)(timer_callback_args_t *); // Pointer to callback that is called when a timer_event_t occurs.

    void const * p_context;                       // Pointer to context to be passed into callback function
} tau_instance_ctrl_t;

/** Optional TAU extension data structure.*/
typedef struct st_tau_extended_cfg
{
    tau_interrupt_opirq_bit_t opirq : 1;   ///< Setting of starting count and interrupt
    tau_function_t            tau_func;    ///< Setting of Function for TAU
    tau_bit_mode_t            bit_mode;    ///< Setting of 16-bit timer or 8-bit timer

    /* Output pin settings. */
    tau_pin_output_cfg_t initial_output;   ///< Setting of Function for TAU

    /* Input settings. */
    tau_input_source_t       input_source;
    tau_input_noise_filter_t tau_filter;   ///< Input filter for TAU
    tau_trigger_edge_t       trigger_edge; ///< Trigger edge to start pulse period measurement or count external event

    tau_operation_ck_t operation_clock;

    uint16_t  period_higher_8bit_counts;   ///< Period in raw higher 8 bit timer counts
    uint8_t   higher_8bit_cycle_end_ipl;   ///< Cycle higher 8-bit end interrupt priority
    IRQn_Type higher_8bit_cycle_end_irq;   ///< Cycle higher 8-bit end interrupt
} tau_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_tau;

/** @endcond */

fsp_err_t R_TAU_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_TAU_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TAU_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TAU_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TAU_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TAU_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TAU_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_TAU_CompareMatchSet(timer_ctrl_t * const        p_ctrl,
                                uint32_t const              compare_match_value,
                                timer_compare_match_t const match_channel);
fsp_err_t R_TAU_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_TAU_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_TAU_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_TAU_CallbackSet(timer_ctrl_t * const          p_api_ctrl,
                            void (                      * p_callback)(timer_callback_args_t *),
                            void const * const            p_context,
                            timer_callback_args_t * const p_callback_memory);
fsp_err_t R_TAU_Close(timer_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup TAU)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */

FSP_FOOTER

#endif                                 // R_TAU_H
