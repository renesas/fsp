/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CGC_H
#define R_CGC_H

/*******************************************************************************************************************//**
 * @addtogroup CGC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_cgc_cfg.h"
#include "r_cgc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CGC private control block. DO NOT MODIFY. Initialization occurs when R_CGC_Open() is called. */
typedef struct st_cgc_instance_ctrl
{
    uint32_t open;

    cgc_callback_args_t * p_callback_memory;           // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void (* p_callback)(cgc_callback_args_t * p_args); // Pointer to callback that is called when a cgc_event_t occurs.

    /** Placeholder for user data.  Passed to the user callback in ::cgc_callback_args_t. */
    void const * p_context;
#if BSP_FEATURE_CGC_HAS_OSTDCSE
    void const * p_extend;
#endif
} cgc_instance_ctrl_t;

#if BSP_FEATURE_CGC_HAS_OSTDCSE

/** CGC extend configuration */
typedef struct s_cgc_extended_cfg_t
{
    bool      ostd_enable;                 /// <Enable Oscillation Stop Detection Function for System Clock
    bool      mostd_enable;                /// <Enable Main Oscillation Stop Detection
    bool      sostd_enable;                /// <Enable Sub Clock Oscillation Stop Detection
    IRQn_Type mostd_irq;                   ///< Main Oscillation Stop IRQ number
    uint8_t   mostd_ipl;                   ///< Main Oscillation Stop interrupt priority
    IRQn_Type sostd_irq;                   ///< Sub Clock Oscillation Stop IRQ number
    uint8_t   sostd_ipl;                   ///< Sub Clock Oscillation Stop interrupt priority
    uint8_t   sdadc_b_clock_switch_enable; ///< Enable switch to HOCO when oscillation stop occurs
    uint16_t  mostd_detection_time;        ///< Main Oscillation Stop Detection Time
    uint16_t  sostd_detection_time;        ///< Sub Clock Oscillation Stop Detection Time
} cgc_extended_cfg_t;
#endif

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const cgc_api_t g_cgc_on_cgc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CGC_Open(cgc_ctrl_t * const p_ctrl, cgc_cfg_t const * const p_cfg);
fsp_err_t R_CGC_ClocksCfg(cgc_ctrl_t * const p_ctrl, cgc_clocks_cfg_t const * const p_clock_cfg);
fsp_err_t R_CGC_ClockStart(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source, cgc_pll_cfg_t const * const p_pll_cfg);
fsp_err_t R_CGC_ClockStop(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source);
fsp_err_t R_CGC_ClockCheck(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source);
fsp_err_t R_CGC_SystemClockSet(cgc_ctrl_t * const              p_ctrl,
                               cgc_clock_t                     clock_source,
                               cgc_divider_cfg_t const * const p_divider_cfg);
fsp_err_t R_CGC_SystemClockGet(cgc_ctrl_t * const        p_ctrl,
                               cgc_clock_t * const       p_clock_source,
                               cgc_divider_cfg_t * const p_divider_cfg);
fsp_err_t R_CGC_OscStopDetectEnable(cgc_ctrl_t * const p_ctrl);
fsp_err_t R_CGC_OscStopDetectDisable(cgc_ctrl_t * const p_ctrl);
fsp_err_t R_CGC_OscStopStatusClear(cgc_ctrl_t * const p_ctrl);
fsp_err_t R_CGC_CallbackSet(cgc_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(cgc_callback_args_t *),
                            void const * const          p_context,
                            cgc_callback_args_t * const p_callback_memory);
fsp_err_t R_CGC_Close(cgc_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup CGC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/* R_CGC_H */
#endif                                 // R_CGC_H
