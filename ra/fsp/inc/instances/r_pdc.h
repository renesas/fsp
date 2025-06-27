/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup PDC
 * @{
 **********************************************************************************************************************/

#ifndef R_PDC_H
#define R_PDC_H

#include "bsp_api.h"
#include "r_capture_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** PDC events */
typedef enum e_pdc_event
{
    PDC_EVENT_TRANSFER_COMPLETE = 0U,    ///< Complete frame transferred by DMAC/DTC
    PDC_EVENT_RX_DATA_READY     = 0x01U, ///< Receive data ready interrupt
    PDC_EVENT_FRAME_END         = 0x04U, ///< Frame end interrupt
    PDC_EVENT_ERR_OVERRUN       = 0x08U, ///< Overrun interrupt
    PDC_EVENT_ERR_UNDERRUN      = 0x10U, ///< Underrun interrupt
    PDC_EVENT_ERR_V_SET         = 0x20U, ///< Vertical line setting error interrupt
    PDC_EVENT_ERR_H_SET         = 0x40U, ///< Horizontal byte number setting error interrupt
} pdc_event_t;

/** Clock divider applied to PDC clock to provide PCKO output frequency  */
typedef enum e_pdc_clock_division
{
    PDC_CLOCK_DIVISION_2  = 0U,        ///< CLK / 2
    PDC_CLOCK_DIVISION_4  = 1U,        ///< CLK / 4
    PDC_CLOCK_DIVISION_6  = 2U,        ///< CLK / 6
    PDC_CLOCK_DIVISION_8  = 3U,        ///< CLK / 8
    PDC_CLOCK_DIVISION_10 = 4U,        ///< CLK / 10
    PDC_CLOCK_DIVISION_12 = 5U,        ///< CLK / 12
    PDC_CLOCK_DIVISION_14 = 6U,        ///< CLK / 14
    PDC_CLOCK_DIVISION_16 = 7U,        ///< CLK / 16
} pdc_clock_division_t;

/** Endian of captured data  */
typedef enum e_pdc_endian
{
    PDC_ENDIAN_LITTLE = 0U,            ///< Data is in little endian format
    PDC_ENDIAN_BIG    = 1U,            ///< Data is in big endian format
} pdc_endian_t;

/** Polarity of input HSYNC signal  */
typedef enum e_pdc_hsync_polarity
{
    PDC_HSYNC_POLARITY_HIGH = 0U,      ///< HSYNC signal is active high
    PDC_HSYNC_POLARITY_LOW  = 1U,      ///< HSYNC signal is active low
} pdc_hsync_polarity_t;

/** Polarity of input VSYNC signal  */
typedef enum e_pdc_vsync_polarity
{
    PDC_VSYNC_POLARITY_HIGH = 0U,      ///< VSYNC signal is active high
    PDC_VSYNC_POLARITY_LOW  = 1U,      ///< VSYNC signal is active low
} pdc_vsync_polarity_t;

/** Extended configuration structure for PDC. */
typedef struct st_pdc_extended_cfg
{
    pdc_clock_division_t        clock_division;       ///< Clock divider
    pdc_endian_t                endian;               ///< Endian of capture data
    pdc_hsync_polarity_t        hsync_polarity;       ///< Polarity of HSYNC input
    pdc_vsync_polarity_t        vsync_polarity;       ///< Polarity of VSYNC input
    uint8_t                     pdc_ipl;              ///< PDC interrupt priority
    uint8_t                     transfer_req_ipl;     ///< Transfer interrupt priority
    IRQn_Type                   pdc_irq;              ///< PDC IRQ number
    IRQn_Type                   transfer_req_irq;     ///< Transfer request IRQ number
    transfer_instance_t const * p_lower_lvl_transfer; ///< Pointer to the transfer instance the PDC should use
} pdc_extended_cfg_t;

/** PDC instance control block. DO NOT INITIALIZE. */
typedef struct st_pdc_instance_ctrl
{
    capture_cfg_t const * p_cfg;                           // Pointer to the configuration structure
    uint32_t              open;                            // Indicates whether or not the driver is open called.
    uint16_t              num_blocks;                      // Number of blocks to be transferred using DMA
    uint8_t             * p_current_buffer;                // Pointer to buffer currently in use
    bool   transfer_in_progress;                           // Indicates if a PDC transfer is already in progress
    void * p_context;                                      // Placeholder for user data.  Passed to the user callback.
    void (* p_callback)(capture_callback_args_t * p_args); // Callback provided when a PDC transfer ISR occurs.
} pdc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const capture_api_t g_pdc_on_capture;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_PDC_Open(capture_ctrl_t * const p_ctrl, capture_cfg_t const * const p_cfg);

fsp_err_t R_PDC_Close(capture_ctrl_t * const p_ctrl);

fsp_err_t R_PDC_CaptureStart(capture_ctrl_t * const p_ctrl, uint8_t * const p_buffer);

fsp_err_t R_PDC_StatusGet(capture_ctrl_t * const p_ctrl, capture_status_t * p_status);

fsp_err_t R_PDC_CallbackSet(capture_ctrl_t * const          p_ctrl,
                            void (                        * p_callback)(capture_callback_args_t *),
                            void * const                    p_context,
                            capture_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_PDC_H

/*******************************************************************************************************************//**
 * @} (end defgroup PDC)
 **********************************************************************************************************************/
