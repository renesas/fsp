/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_AUDIO_INTERFACES
 * @defgroup PDM_API PDM Interface
 * @brief Interface for PDM audio communication.
 *
 * @section PDM_API_SUMMARY Summary
 * @brief The pulse-density modulation(PDM) interface provides APIs and definitions for PDM audio communication.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_PDM_API_H
#define R_PDM_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Audio PCM width */
typedef enum e_pdm_pcm_width
{
    PDM_PCM_WIDTH_20_BITS_0_18 = 0x00, ///< Using 20-bit PCM Clips [18:0] bit of the buffer and 1-bit of sign
    PDM_PCM_WIDTH_20_BITS_1_18 = 0x01, ///< Using 20-bit PCM Clips [18:1] bit of the buffer and 2-bits of sign
    PDM_PCM_WIDTH_20_BITS_2_18 = 0x02, ///< Using 20-bit PCM Clips [18:2] bit of the buffer and 3-bits of sign
    PDM_PCM_WIDTH_20_BITS_3_18 = 0x03, ///< Using 20-bit PCM Clips [18:3] bit of the buffer and 4-bits of sign
    PDM_PCM_WIDTH_16_BITS_4_18 = 0x08, ///< Using 16-bit PCM Clips [18:4] bit of the buffer and 1-bit of sign
    PDM_PCM_WIDTH_16_BITS_3_17 = 0x09, ///< Using 16-bit PCM Clips [17:3] bit of the buffer and 1-bit of sign
    PDM_PCM_WIDTH_16_BITS_2_16 = 0x0A, ///< Using 16-bit PCM Clips [16:2] bit of the buffer and 1-bit of sign
    PDM_PCM_WIDTH_16_BITS_1_15 = 0x0B, ///< Using 16-bit PCM Clips [15:1] bit of the buffer and 1-bit of sign
    PDM_PCM_WIDTH_16_BITS_0_14 = 0x0C, ///< Using 16-bit PCM Clips [14:0] bit of the buffer and 1-bit of sign
} pdm_pcm_width_t;

/** Input data select. */
typedef enum e_pdm_input_data_edge
{
    PDM_INPUT_DATA_EDGE_RISE = 0,      ///< Rise-edge data of channel n
    PDM_INPUT_DATA_EDGE_FALL = 1,      ///< Fall-edge data of channel n-1 (In case of n = 0, fall-edge data of channel 2 is selected.)
} pdm_input_data_edge_t;

/** Events that can trigger a callback function */
typedef enum e_pdm_event
{
    PDM_EVENT_IDLE,                    ///< IDLE
    PDM_EVENT_DATA,                    ///< Data reception
    PDM_EVENT_SOUND_DETECTION,         ///< Sound detection
    PDM_EVENT_ERROR,                   ///< Error
} pdm_event_t;

/** Error information included in a callback function */
typedef enum e_pdm_error
{
    PDM_ERROR_NONE              = 0,          ///< No error
    PDM_ERROR_SHORT_CIRCUIT     = (1UL << 0), ///< Short circuit detection
    PDM_ERROR_OVERVOLTAGE_LOWER = (1UL << 1), ///< Overvoltage lower limit exceeded detection
    PDM_ERROR_OVERVOLTAGE_UPPER = (1UL << 2), ///< Overvoltage upper limit exceeded detection
    PDM_ERROR_BUFFER_OVERWRITE  = (1UL << 11) ///< Buffer overwriting detection
} pdm_error_t;

/** Possible status values returned by @ref pdm_api_t::statusGet. */
typedef enum e_pdm_state
{
    PDM_STATE_IN_USE,                  ///< PDM is actively reading data
    PDM_STATE_STOPPED                  ///< PDM is stopped and not actively reading data
} pdm_state_t;

/** Callback function parameter data */
typedef struct st_pdm_callback_args
{
    /** Placeholder for user data.  Set in @ref pdm_api_t::open function in @ref pdm_cfg_t. */
    void      * p_context;
    pdm_event_t event;                 ///< The event can be used to identify what caused the callback (overflow or error).
    pdm_error_t error;                 ///< The kind of error.
} pdm_callback_args_t;

/** Sound detection window setting */
typedef struct st_pdm_sound_detection_setting
{
    uint32_t sound_detection_lower_limit; ///< Sound detection lower limit (20-bit signed fixed point data)
    uint32_t sound_detection_upper_limit; ///< Sound detection upper limit (20-bit signed fixed point data)
} pdm_sound_detection_setting_t;

/** PDM control block.  Allocate an instance specific control block to pass into the PDM API calls.
 */
typedef void pdm_ctrl_t;

/** PDM status. */
typedef struct st_pdm_status
{
    pdm_state_t state;                   ///< Current PDM data state
    bool        sound_detection_enabled; ///< Current PDM sound detection status
    pdm_error_t error;                   ///< Bitfield of current PDM errors
} pdm_status_t;

/** User configuration structure, used in open function */
typedef struct st_pdm_cfg
{
    /** Select a unit/channel corresponding to the unit/channel number of the hardware. */
    uint32_t              unit;
    uint32_t              channel;
    pdm_pcm_width_t       pcm_width;   ///< Audio PCM data width
    pdm_input_data_edge_t pcm_edge;    ///< Input data select

    /** To use DMA for receiving link a Transfer instance here.  Set to NULL if unused. */
    transfer_instance_t const * p_transfer_rx;

    /** Callback provided when an PDM ISR occurs.  Set to NULL for no CPU interrupt. */
    void (* p_callback)(pdm_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in @ref pdm_callback_args_t. */
    void       * p_context;
    void const * p_extend;             ///< Extension parameter for hardware specific settings.
    uint8_t      dat_ipl;              ///< Data reception interrupt priority
    uint8_t      sdet_ipl;             ///< Sound detection interrupt priority
    uint8_t      err_ipl;              ///< Idle/Error interrupt priority
    IRQn_Type    dat_irq;              ///< IRQ number of data reception interrupt
    IRQn_Type    sdet_irq;             ///< IRQ number of sound detection interrupt
    IRQn_Type    err_irq;              ///< IRQ number of error detection interrupt
} pdm_cfg_t;

/** PDM functions implemented at the HAL layer will follow this API. */
typedef struct st_pdm_api
{
    /** Initial configuration.
     *
     * @pre Peripheral clocks and any required output pins should be configured prior to calling this function.
     * @note To reconfigure after calling this function, call @ref pdm_api_t::close first.
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(pdm_ctrl_t * const p_ctrl, pdm_cfg_t const * const p_cfg);

    /** Start communication.
     *
     * @param[in]   p_ctrl                     Control block set in @ref pdm_api_t::open call for this instance.
     * @param[in]   p_buffer                   Pointer to the reception buffer
     * @param[in]   buffer_size                Size of the buffer
     * @param[in]   number_of_data_to_callback Number of the data to call the callback function from dat_isr
     */
    fsp_err_t (* start)(pdm_ctrl_t * const p_ctrl, void * const p_buffer, size_t const buffer_size,
                        uint32_t const number_of_data_to_callback);

    /** Stop communication. Communication is stopped when callback is called with PDM_EVENT_IDLE.
     *
     * @param[in]   p_ctrl     Control block set in @ref pdm_api_t::open call for this instance.
     */
    fsp_err_t (* stop)(pdm_ctrl_t * const p_ctrl);

    /** Enable sound detection with the specified settings.
     *
     * @param[in]   p_ctrl                     Control block set in @ref pdm_api_t::open call for this instance.
     * @param[in]   pdm_sound_detection_setting    Settings to configure sound detection.
     */
    fsp_err_t (* soundDetectionEnable)(pdm_ctrl_t * const            p_ctrl,
                                       pdm_sound_detection_setting_t pdm_sound_detection_setting);

    /** Disable sound detection.
     *
     * @param[in]   p_ctrl                     Control block set in @ref pdm_api_t::open call for this instance.
     */
    fsp_err_t (* soundDetectionDisable)(pdm_ctrl_t * const p_ctrl);

    /** Read remaining PDM data. This function can be called during PDM_STATE_STOPPED.
     *
     * @param[in]   p_ctrl     Control block set in @ref pdm_api_t::open call for this instance.
     * @param[in]   p_dest     Buffer to store PCM samples.  Must be 4 byte aligned.
     * @param[in]   bytes      Number of bytes in the buffer.  Recommended requesting a multiple of 8 bytes.  If not
     *                         a multiple of 8, receive will stop at the multiple of 8 below requested bytes.
     */
    fsp_err_t (* read)(pdm_ctrl_t * const p_ctrl, void * const p_dest, uint32_t const bytes);

    /** Get current status and store it in provided pointer p_status.
     *
     * @param[in]   p_ctrl     Control block set in @ref pdm_api_t::open call for this instance.
     * @param[out]  p_status   Current status of the driver.
     */
    fsp_err_t (* statusGet)(pdm_ctrl_t * const p_ctrl, pdm_status_t * const p_status);

    /** Allows driver to be reconfigured and may reduce power consumption.
     *
     * @param[in]   p_ctrl     Control block set in @ref pdm_api_t::open call for this instance.
     */
    fsp_err_t (* close)(pdm_ctrl_t * const p_ctrl);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the PDM control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_callback_memory        Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(pdm_ctrl_t * const p_ctrl, void (* p_callback)(pdm_callback_args_t *),
                              void * const p_context, pdm_callback_args_t * const p_callback_memory);
} pdm_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_pdm_instance
{
    pdm_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    pdm_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    pdm_api_t const * p_api;           ///< Pointer to the API structure for this instance
} pdm_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup PDM_API)
 **********************************************************************************************************************/
