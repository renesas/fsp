/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup GPTP
 * @{
 **********************************************************************************************************************/

#ifndef R_GPTP_H
#define R_GPTP_H

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_gptp_cfg.h"
#include "r_gptp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Pulsed output configuration. */
typedef struct st_gptp_pulsed_output_cfg
{
    uint8_t  pulse_num;                ///< Pulse generator number.
    uint16_t start_sec_upper;          ///< Pulse start second(upper 16 bit).
    uint32_t start_sec_lower;          ///< Pulse start second(lower 32 bit).
    uint32_t start_ns;                 ///< Pulse start nanosecond.
    uint16_t wide;                     ///< Pulse width.
    uint16_t period_sec_upper;         ///< Pulse period second(upper 16 bit).
    uint32_t period_sec_lower;         ///< Pulse period second(lower 32 bit).
    uint32_t period_ns;                ///< Pulse period nanosecond.
} gptp_pulsed_output_cfg_t;

/** Pulse generator. */
typedef struct st_gptp_pulse_generator
{
    gptp_pulsed_output_cfg_t * p_pulsed_output_cfg_list[BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM]; ///< List of pointer to pulsed output configuration.
} gptp_pulse_generator_t;

/** GPTP control block. DO NOT INITIALIZE.  Initialization occurs when @ref gptp_api_t::open is called. */
typedef struct st_gptp_instance_ctrl
{
    uint32_t           open;                     ///< Indicates whether the open() API has been successfully called.
    gptp_cfg_t const * p_cfg;                    ///< Pointer to initial configurations.

    R_GPTP_Type * p_reg_gptp;                    ///< Pointer to GPTP timer register.

    void (* p_callback)(gptp_callback_args_t *); ///< Pointer to callback that is called.
    gptp_callback_args_t * p_callback_memory;    ///< Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.

    void const * p_context;                      ///< Pointer to context to be passed into callback function.
} gptp_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const gptp_api_t g_gptp_on_gptp;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_GPTP_Open(gptp_ctrl_t * const p_ctrl, gptp_cfg_t const * const p_cfg);

fsp_err_t R_GPTP_Close(gptp_ctrl_t * const p_ctrl);

fsp_err_t R_GPTP_TimerCfg(gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_timer_cfg_t const * const p_timer_cfg);

fsp_err_t R_GPTP_Start(gptp_ctrl_t * const p_ctrl, uint8_t timer);

fsp_err_t R_GPTP_Stop(gptp_ctrl_t * const p_ctrl, uint8_t timer);

fsp_err_t R_GPTP_TimerValueGet(gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_timer_value_t * const p_timer_value);

fsp_err_t R_GPTP_TimerOffsetSet(gptp_ctrl_t * const p_ctrl, uint8_t timer, int64_t offset);

fsp_err_t R_GPTP_TimerRateSet(gptp_ctrl_t * const p_ctrl, uint8_t timer, uint32_t rate);

fsp_err_t R_GPTP_PulseGeneratorSet(gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_pulse_generator_t * p_pulse);

fsp_err_t R_GPTP_CallbackSet(gptp_ctrl_t * const          p_ctrl,
                             void (                     * p_callback)(gptp_callback_args_t *),
                             void * const                 p_context,
                             gptp_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end addtogroup GPTP)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_GPTP_H
