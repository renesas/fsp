/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_TML_H
#define R_TML_H

/*******************************************************************************************************************//**
 * @addtogroup TML
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Enumeration for TML FITL0, FITL1 clock source */
typedef enum e_tml_clock
{
    TML_CLOCK_HOCO      = 1U,          ///< HOCO
    TML_CLOCK_MOCO      = 2U,          ///< MOCO
    TML_CLOCK_MOSC      = 3U,          ///< MOSC
    TML_CLOCK_LOCO_SOSC = 4U,          ///< SOSC
    TML_CLOCK_ELC_EVENT = 5U,          ///< Event input from the ELC
} tml_clock_t;

/** Enumeration for TML FITL2 capture trigger source */
typedef enum e_tml_capture_trigger
{
    TML_CAPTURE_TRIGGER_SOFTWARE  = 0U, ///< Software trigger
    TML_CAPTURE_TRIGGER_ITLCMP01  = 1U, ///< Interrupt on compare match with ITLCMP01
    TML_CAPTURE_TRIGGER_LOCO_SOSC = 2U, ///< LOCO/SOSC (rising edge)
    TML_CAPTURE_TRIGGER_EVENT_ELC = 3U, ///< Event input from ELC (rising edge)
} tml_capture_trigger_t;

/** Enumeration for status of 16-bit counter (ITL000 + ITL001) after completion of capturing */
typedef enum e_tml_counter_status
{
    TML_COUNTER_STATUS_RETAINED_AFTER_CAPTURING = 0U, ///< 16-bit counter (ITL000 + ITL001) is retained after the completion of capturing
    TML_COUNTER_STATUS_CLEARED_AFTER_CAPTURING  = 1U, ///< 16-bit counter (ITL000 + ITL001) is cleared after the completion of capturing
} tml_counter_status_t;

/** User configuration structure, used in open function */
typedef struct st_tml_extended_cfg
{
    tml_capture_trigger_t capture_trigger; ///< Select the capture source for capture channel
    tml_counter_status_t  counter_status;  ///< Status of 16-bit counter (ITL000 + ITL001) after completion of capturing
} tml_extended_cfg_t;

/** TML instance control block. */
typedef struct st_tml_instance_ctrl
{
    uint32_t            open;                     ///< Used to determine if the channel is configured
    const timer_cfg_t * p_cfg;                    ///< Pointer to the configuration block.
    uint8_t             channel_mask;             ///< Mask value of channel used.

    void (* p_callback)(timer_callback_args_t *); ///< Pointer to callback that is called when a timer event occurs.
    void * p_context;                             ///< Pointer to context to be passed into callback function
} tml_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_tml;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_TML_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_TML_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TML_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TML_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TML_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TML_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_TML_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_TML_CompareMatchSet(timer_ctrl_t * const        p_ctrl,
                                uint32_t const              compare_match_value,
                                timer_compare_match_t const match_channel);
fsp_err_t R_TML_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_TML_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_TML_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_TML_CallbackSet(timer_ctrl_t * const          p_api_ctrl,
                            void (                      * p_callback)(timer_callback_args_t *),
                            void * const                  p_context,
                            timer_callback_args_t * const p_callback_memory);
fsp_err_t R_TML_Close(timer_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup TML)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
