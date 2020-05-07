/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef R_AGT_H
#define R_AGT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_agt_cfg.h"
#include "r_timer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Leading zeroes removed to avoid coding standards violation. */
#define AGT_CODE_VERSION_MAJOR    (1U)
#define AGT_CODE_VERSION_MINOR    (1U)

/** Maximum number of clock counts in 16 bit timer. */
#define AGT_MAX_CLOCK_COUNTS      (UINT16_MAX)

/** Maximum period value allowed for AGT. */
#define AGT_MAX_PERIOD            (UINT16_MAX + 1U)

/*******************************************************************************************************************//**
 * @addtogroup AGT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Count source */
typedef enum e_agt_clock
{
    AGT_CLOCK_PCLKB          = 0x00,   ///< PCLKB count source, division by 1, 2, or 8 allowed
    AGT_CLOCK_LOCO           = 0x40,   ///< LOCO count source, division by 1, 2, 4, 8, 16, 32, 64, or 128 allowed
    AGT_CLOCK_AGT0_UNDERFLOW = 0x50,   ///< Underflow event signal from AGT0, division must be 1
    AGT_CLOCK_SUBCLOCK       = 0x60,   ///< Subclock count source, division by 1, 2, 4, 8, 16, 32, 64, or 128 allowed
    AGT_CLOCK_P402           = 0x92,   ///< Counts events on P402, events are counted in deep software standby mode
    AGT_CLOCK_P403           = 0x93,   ///< Counts events on P403, events are counted in deep software standby mode
    AGT_CLOCK_AGTIO          = 0x80,   ///< Counts events on AGTIOn, events are not counted in software standby modes
} agt_clock_t;

/** Enable pin for event counting mode. */
typedef enum e_agt_measure
{
    AGT_MEASURE_DISABLED               = 1U,    ///< AGT used as a counter
    AGT_MEASURE_PULSE_WIDTH_LOW_LEVEL  = 3U,    ///< AGT used to measure low level pulse width
    AGT_MEASURE_PULSE_WIDTH_HIGH_LEVEL = 0x13U, ///< AGT used to measure high level pulse width
    AGT_MEASURE_PULSE_PERIOD           = 4U,    ///< AGT used to measure pulse period
} agt_measure_t;

/** Input filter, applies AGTIO in pulse period measurement, pulse width measurement, or event counter mode. The filter
 * requires the signal to be at the same level for 3 successive reads at the specified filter frequency. */
typedef enum e_agt_agtio_filter
{
    AGT_AGTIO_FILTER_NONE         = 0x00U, ///< No filter
    AGT_AGTIO_FILTER_PCLKB        = 0x10U, ///< Filter at PCLKB
    AGT_AGTIO_FILTER_PCLKB_DIV_8  = 0x20U, ///< Filter at PCLKB / 8
    AGT_AGTIO_FILTER_PCLKB_DIV_32 = 0x30U, ///< Filter at PCLKB / 32
} agt_agtio_filter_t;

/** Enable pin for event counting mode. */
typedef enum e_agt_enable_pin
{
    AGT_ENABLE_PIN_NOT_USED    = 0U,    ///< AGTEE is not used
    AGT_ENABLE_PIN_ACTIVE_LOW  = 0x40U, ///< Events are only counted when AGTEE is low
    AGT_ENABLE_PIN_ACTIVE_HIGH = 0x44U, ///< Events are only counted when AGTEE is high
} agt_enable_pin_t;

/** Trigger edge for pulse period measurement mode and event counting mode. */
typedef enum e_agt_trigger_edge
{
    AGT_TRIGGER_EDGE_RISING  = 0U,     ///< Measurement starts or events are counted on rising edge
    AGT_TRIGGER_EDGE_FALLING = 1U,     ///< Measurement starts or events are counted on falling edge
    AGT_TRIGGER_EDGE_BOTH    = 8U,     ///< Events are counted on both edges (n/a for pulse period mode)
} agt_trigger_edge_t;

/** Output pins, used to select which duty cycle to update in R_AGT_DutyCycleSet(). */
typedef enum e_agt_output_pin
{
    AGT_OUTPUT_PIN_AGTOA = 0,          ///< GTIOCA
    AGT_OUTPUT_PIN_AGTOB = 1,          ///< GTIOCB
} agt_output_pin_t;

/** Level of AGT pin */
typedef enum e_agt_pin_cfg
{
    AGT_PIN_CFG_DISABLED         = 0,  ///< Not used as output pin
    AGT_PIN_CFG_START_LEVEL_LOW  = 3,  ///< Pin level low
    AGT_PIN_CFG_START_LEVEL_HIGH = 7,  ///< Pin level high
} agt_pin_cfg_t;

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when @ref timer_api_t::open is called. */
typedef struct st_agt_instance_ctrl
{
    uint32_t            open;          ///< Whether or not channel is open
    const timer_cfg_t * p_cfg;         ///< Pointer to initial configurations
    R_AGT0_Type       * p_reg;         ///< Base register for this channel
    uint32_t            period;        ///< Current timer period (counts)
} agt_instance_ctrl_t;

/** Optional AGT extension data structure.*/
typedef struct st_agt_extended_cfg
{
    agt_clock_t count_source;          ///< AGT channel clock source. Valid values are: AGT_CLOCK_PCLKB, AGT_CLOCK_LOCO, AGT_CLOCK_FSUB

    /* Output pin settings. */
    union
    {
        uint8_t agtoab_settings;
        struct
        {
            agt_pin_cfg_t agtoa : 3;     ///< Configure AGTOA pin
            uint8_t             : 1;
            agt_pin_cfg_t agtob : 3;     ///< Configure AGTOB pin
        };
    };
    agt_pin_cfg_t agto : 3;              ///< Configure AGTO pin @note AGTIO polarity is opposite AGTO

    /* Input pin settings. */
    agt_measure_t      measurement_mode; ///< Measurement mode
    agt_agtio_filter_t agtio_filter;     ///< Input filter for AGTIO
    agt_enable_pin_t   enable_pin;       ///< Enable pin (event counting only)
    agt_trigger_edge_t trigger_edge;     ///< Trigger edge to start pulse period measurement or count external event
} agt_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const timer_api_t g_timer_on_agt;

/** @endcond */

fsp_err_t R_AGT_Close(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_PeriodSet(timer_ctrl_t * const p_ctrl, uint32_t const period_counts);
fsp_err_t R_AGT_DutyCycleSet(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);
fsp_err_t R_AGT_Reset(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Start(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Enable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Disable(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_InfoGet(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);
fsp_err_t R_AGT_StatusGet(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);
fsp_err_t R_AGT_Stop(timer_ctrl_t * const p_ctrl);
fsp_err_t R_AGT_Open(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
fsp_err_t R_AGT_VersionGet(fsp_version_t * const p_version);

/*******************************************************************************************************************//**
 * @} (end defgroup AGT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */

FSP_FOOTER

#endif                                 // R_AGT_H
