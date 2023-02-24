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

#ifndef R_ULPT_H
#define R_ULPT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_ulpt_cfg.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup ULPT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Count source. */
typedef enum e_ulpt_clock
{
    ULPT_CLOCK_LOCO     = 0x00U,       ///< LOCO count source, division by 1, 2, 4, 8, 16, 32, 64, 128.
    ULPT_CLOCK_SUBCLOCK = 0x20U,       ///< Subclock count source, division by 1, 2, 4, 8, 16, 32, 64, 128.
    ULPT_CLOCK_ULPTEVI  = 0x02U,       ///< Counts external events on ULPTEVI.
} ulpt_clock_t;

/** Counter mode for event enable. */
typedef enum e_ulpt_enable_function
{
   // R_ULPT0_ULPTIOC_TIOGT0_Msk    0X00 0000 0=Always count, 1 count external events (Not to be mized with nonzero TEECTL)
   // R_ULPT0_ULPTISR_RCCPSEL2_Msk  0000 0X00 0=count low level, 1 count high level, only valid when TIOGT0=1 (Not to be mized with nonzero TEECTL)
   // R_ULPT0_ULPTMR3_TEECTL_Msk    00XX 0000
    //0100 0000 Count external high,
    //0100 0100 Count external low
    ULPT_ENABLE_FUNCTION_IGNORED     = 0x00U, ///< Always count external events, ignore ULPTEE.
    ULPT_ENABLE_FUNCTION_ENABLE_LOW  = 0x40U, ///< Event counting is enabled while ULPTEE is low (event counting only).
    ULPT_ENABLE_FUNCTION_ENABLE_HIGH = 0x44U, ///< Event counting is enabled while ULPTEE is high (event counting only).
    ULPT_ENABLE_FUNCTION_START       = 0x20U, ///< Counting is started after ULPTEE.
    ULPT_ENABLE_FUNCTION_RESTART     = 0x30U, ///< Counting is restarted after ULPTEE.

} ulpt_enable_function_t;

/** Enable signal trigger edge for start and restart functions. */
typedef enum e_ulpt_trigger_edge
{
    ULPT_TRIGGER_EDGE_RISING  = 0x00U, ///< Timer enable function occurs on the rising edge of ULPTEE.
    ULPT_TRIGGER_EDGE_FALLING = 0x40U, ///< Timer enable function occurs on the falling edge of ULPTEE.
    ULPT_TRIGGER_EDGE_BOTH    = 0x80U, ///< Timer enable function occurs on any edge of ULPTEE.
} ulpt_trigger_edge_t;

/** Event signal pin. */
typedef enum e_ulpt_event_pin
{
    ULPT_EVENT_PIN_RISING  = 0x00U,    ///< Event count occurs on the rising edge.
    ULPT_EVENT_PIN_FALLING = 0x02U,    ///< Event count occurs on the falling edge.
    ULPT_EVENT_PIN_BOTH    = 0x08U,    ///< Event count occurs on both edges.
} ulpt_event_pin_t;

/** Output pins, used to select which duty cycle to update in R_ULPT_DutyCycleSet(). */
typedef enum e_ulpt_output_pin
{
    ULPT_OUTPUT_PIN_ULPTOA = 0U,       ///< Compare match A output.
    ULPT_OUTPUT_PIN_ULPTOB = 1U,       ///< Compare match B output.
} ulpt_output_pin_t;

/** ULPTO pulse output pin. */
typedef enum e_ulpt_pulse_pin_cfg
{
    ULPT_PULSE_PIN_CFG_DISABLED = 0x00U, ///< Output pin disabled.
    ULPT_PULSE_PIN_CFG_ENABLED_START_LEVEL_LOW  = 0x01U, ///< Output pin Enabled Start Low
    ULPT_PULSE_PIN_CFG_ENABLED_START_LEVEL_HIGH  = 0x02U, ///< Output pin enabled Start Hig
} ulpt_pulse_pin_cfg_t;

/** ULPT match output pin. */
typedef enum e_ulpt_match_pin_cfg
{
    ULPT_MATCH_PIN_CFG_DISABLED         = 0x00U, ///< Match output disabled.
    ULPT_MATCH_PIN_CFG_START_LEVEL_LOW  = 0x03U, ///< Match output enabled, starts low.
    ULPT_MATCH_PIN_CFG_START_LEVEL_HIGH = 0x07U, ///< Match output enabled, starts high.
} ulpt_match_pin_cfg_t;

/** Input filter, applied to ULPTEVI in event counter mode. The filter requires the signal to be at the same level for
 *  3 successive reads at the specified filter frequency. */
typedef enum e_ulpt_ulptevi_filter
{
    ULPT_ULPTEVI_FILTER_NONE         = 0x00U, ///< No filter
    ULPT_ULPTEVI_FILTER_PCLKB        = 0x10U, ///< Filter at PCLKB
    ULPT_ULPTEVI_FILTER_PCLKB_DIV_8  = 0x20U, ///< Filter at PCLKB / 8
    ULPT_ULPTEVI_FILTER_PCLKB_DIV_32 = 0x30U, ///< Filter at PCLKB / 32
} ulpt_ulptevi_filter_t;

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref timer_api_t::open is called. */
typedef struct st_ulpt_instance_ctrl
{
    uint32_t            open;                     // Whether or not the channel is open.
    const timer_cfg_t * p_cfg;                    // Pointer to initial configuration.
    R_ULPT0_Type      * p_reg;                    // Base register for this channel.
    uint32_t            period;                   // Current timer period (counts).

    void (* p_callback)(timer_callback_args_t *); // Pointer to callback that is called when a timer_event_t occurs.
    timer_callback_args_t * p_callback_memory;    // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
    void const            * p_context;            // Pointer to context to be passed into callback function
} ulpt_instance_ctrl_t;

/** Optional ULPT extension data structure. */
typedef struct st_ulpt_extended_cfg
{
    ulpt_clock_t count_source;               ///< ULPT channel clock source.

    /* Input pin settings */
    ulpt_ulptevi_filter_t  ulptevi_filter;   ///< Input filter for ULTPEVI.
    ulpt_enable_function_t enable_function;  ///< Counter function when ULPTEE is valid.
    ulpt_trigger_edge_t    trigger_edge;     ///< Enable trigger edge (start and restart functions only).
    ulpt_event_pin_t       event_pin;        ///< Event pin (event counting only).

    /* Output settings */
    ulpt_pulse_pin_cfg_t ulpto;              ///< Pulse output pin.
    union
    {
        uint8_t ulptoab_settings;            ///< Compare match output register.
        struct
        {
            ulpt_match_pin_cfg_t ulptoa : 3; ///< Compare match A output pin.
            uint8_t                     : 1;
            ulpt_match_pin_cfg_t ulptob : 3; ///< Compare match B output pin.
            uint8_t                     : 1;
        } ulptoab_settings_b;
    };
} ulpt_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_ulpt;

/** @endcond */

fsp_err_t R_ULPT_Close(timer_ctrl_t * const p_ctrl);
fsp_err_t R_ULPT_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_ULPT_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_ULPT_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_ULPT_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_ULPT_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_ULPT_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_ULPT_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_ULPT_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_ULPT_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_ULPT_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_ULPT_CallbackSet(timer_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(timer_callback_args_t *),
                             void const * const            p_context,
                             timer_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end defgroup ULPT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */

FSP_FOOTER

#endif                                 // R_ULPT_H
