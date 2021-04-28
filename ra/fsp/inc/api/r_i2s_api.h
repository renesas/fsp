/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup I2S_API I2S Interface
 * @brief Interface for I2S audio communication.
 *
 * @section I2S_API_SUMMARY Summary
 * @brief The I2S (Inter-IC Sound) interface provides APIs and definitions for I2S audio communication.
 *
 * @section I2S_API_INSTANCES Known Implementations
 * @ref SSI
 * @{
 **********************************************************************************************************************/

#ifndef R_I2S_API_H
#define R_I2S_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_timer_api.h"
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
typedef enum e_i2s_pcm_width
{
    I2S_PCM_WIDTH_8_BITS  = 0,         ///< Using 8-bit PCM
    I2S_PCM_WIDTH_16_BITS = 1,         ///< Using 16-bit PCM
    I2S_PCM_WIDTH_18_BITS = 2,         ///< Using 18-bit PCM
    I2S_PCM_WIDTH_20_BITS = 3,         ///< Using 20-bit PCM
    I2S_PCM_WIDTH_22_BITS = 4,         ///< Using 22-bit PCM
    I2S_PCM_WIDTH_24_BITS = 5,         ///< Using 24-bit PCM
    I2S_PCM_WIDTH_32_BITS = 6,         ///< Using 24-bit PCM
} i2s_pcm_width_t;

/** Audio system word length. */
typedef enum e_i2s_word_length
{
    I2S_WORD_LENGTH_8_BITS   = 0,      ///< Using 8-bit system word length
    I2S_WORD_LENGTH_16_BITS  = 1,      ///< Using 16-bit system word length
    I2S_WORD_LENGTH_24_BITS  = 2,      ///< Using 24-bit system word length
    I2S_WORD_LENGTH_32_BITS  = 3,      ///< Using 32-bit system word length
    I2S_WORD_LENGTH_48_BITS  = 4,      ///< Using 48-bit system word length
    I2S_WORD_LENGTH_64_BITS  = 5,      ///< Using 64-bit system word length
    I2S_WORD_LENGTH_128_BITS = 6,      ///< Using 128-bit system word length
    I2S_WORD_LENGTH_256_BITS = 7,      ///< Using 256-bit system word length
} i2s_word_length_t;

/** Events that can trigger a callback function */
typedef enum e_i2s_event
{
    I2S_EVENT_IDLE,                    ///< Communication is idle
    I2S_EVENT_TX_EMPTY,                ///< Transmit buffer is below FIFO trigger level
    I2S_EVENT_RX_FULL,                 ///< Receive buffer is above FIFO trigger level
} i2s_event_t;

/** I2S communication mode */
typedef enum e_i2s_mode
{
    I2S_MODE_SLAVE  = 0,               ///< Slave mode
    I2S_MODE_MASTER = 1,               ///< Master mode
} i2s_mode_t;

/** Mute audio samples. */
typedef enum e_i2s_mute
{
    I2S_MUTE_OFF = 0,                  ///< Disable mute
    I2S_MUTE_ON  = 1,                  ///< Enable mute
} i2s_mute_t;

/** Whether to continue WS (word select line) transmission during idle state. */
typedef enum e_i2s_ws_continue
{
    I2S_WS_CONTINUE_ON  = 0,           ///< Enable WS continue mode
    I2S_WS_CONTINUE_OFF = 1,           ///< Disable WS continue mode
} i2s_ws_continue_t;

/** Possible status values returned by @ref i2s_api_t::statusGet. */
typedef enum e_i2s_state
{
    I2S_STATE_IN_USE,                  ///< I2S is in use
    I2S_STATE_STOPPED                  ///< I2S is stopped
} i2s_state_t;

/** Callback function parameter data */
typedef struct st_i2s_callback_args
{
    /** Placeholder for user data.  Set in @ref i2s_api_t::open function in @ref i2s_cfg_t. */
    void const * p_context;
    i2s_event_t  event;                ///< The event can be used to identify what caused the callback (overflow or error).
} i2s_callback_args_t;

/** I2S control block.  Allocate an instance specific control block to pass into the I2S API calls.
 * @par Implemented as
 * - ssi_instance_ctrl_t
 */
typedef void i2s_ctrl_t;

/** I2S status. */
typedef struct st_i2s_status
{
    i2s_state_t state;                 ///< Current I2S state
} i2s_status_t;

/** User configuration structure, used in open function */
typedef struct st_i2s_cfg
{
    /** Select a channel corresponding to the channel number of the hardware. */
    uint32_t          channel;
    i2s_pcm_width_t   pcm_width;       ///< Audio PCM data width
    i2s_word_length_t word_length;     ///< Audio word length, bits must be >= i2s_cfg_t::pcm_width bits
    i2s_ws_continue_t ws_continue;     ///< Whether to continue WS transmission during idle state.
    i2s_mode_t        operating_mode;  ///< Master or slave mode

    /** To use DTC during write, link a DTC instance here.  Set to NULL if unused. */
    transfer_instance_t const * p_transfer_tx;

    /** To use DTC during read, link a DTC instance here.  Set to NULL if unused. */
    transfer_instance_t const * p_transfer_rx;

    /** Callback provided when an I2S ISR occurs.  Set to NULL for no CPU interrupt. */
    void (* p_callback)(i2s_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in @ref i2s_callback_args_t. */
    void const * p_context;
    void const * p_extend;             ///< Extension parameter for hardware specific settings.
    uint8_t      rxi_ipl;              ///< Receive interrupt priority
    uint8_t      txi_ipl;              ///< Transmit interrupt priority
    uint8_t      idle_err_ipl;         ///< Idle/Error interrupt priority
    IRQn_Type    txi_irq;              ///< Transmit IRQ number
    IRQn_Type    rxi_irq;              ///< Receive IRQ number
    IRQn_Type    int_irq;              ///< Idle/Error IRQ number
} i2s_cfg_t;

/** I2S functions implemented at the HAL layer will follow this API. */
typedef struct st_i2s_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_SSI_Open()
     *
     * @pre Peripheral clocks and any required output pins should be configured prior to calling this function.
     * @note To reconfigure after calling this function, call @ref i2s_api_t::close first.
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(i2s_ctrl_t * const p_ctrl, i2s_cfg_t const * const p_cfg);

    /** Stop communication. Communication is stopped when callback is called with I2S_EVENT_IDLE.
     *
     * @par Implemented as
     * - @ref R_SSI_Stop()
     *
     * @param[in]   p_ctrl     Control block set in @ref i2s_api_t::open call for this instance.
     */
    fsp_err_t (* stop)(i2s_ctrl_t * const p_ctrl);

    /** Enable or disable mute.
     * @par Implemented as
     * - @ref R_SSI_Mute()
     *
     * @param[in]   p_ctrl       Control block set in @ref i2s_api_t::open call for this instance.
     * @param[in]   mute_enable  Whether to enable or disable mute.
     */
    fsp_err_t (* mute)(i2s_ctrl_t * const p_ctrl, i2s_mute_t const mute_enable);

    /** Write I2S data.  All transmit data is queued when callback is called with I2S_EVENT_TX_EMPTY.
     * Transmission is complete when callback is called with I2S_EVENT_IDLE.
     * @par Implemented as
     * - @ref R_SSI_Write()
     *
     * @param[in]   p_ctrl     Control block set in @ref i2s_api_t::open call for this instance.
     * @param[in]   p_src      Buffer of PCM samples.  Must be 4 byte aligned.
     * @param[in]   bytes      Number of bytes in the buffer.  Recommended requesting a multiple of 8 bytes.  If not
     *                         a multiple of 8, padding 0s will be added to transmission to make it a multiple of 8.
     */
    fsp_err_t (* write)(i2s_ctrl_t * const p_ctrl, void const * const p_src, uint32_t const bytes);

    /** Read I2S data.  Reception is complete when callback is called with I2S_EVENT_RX_EMPTY.
     * @par Implemented as
     * - @ref R_SSI_Read()
     *
     * @param[in]   p_ctrl     Control block set in @ref i2s_api_t::open call for this instance.
     * @param[in]   p_dest     Buffer to store PCM samples.  Must be 4 byte aligned.
     * @param[in]   bytes      Number of bytes in the buffer.  Recommended requesting a multiple of 8 bytes.  If not
     *                         a multiple of 8, receive will stop at the multiple of 8 below requested bytes.
     */
    fsp_err_t (* read)(i2s_ctrl_t * const p_ctrl, void * const p_dest, uint32_t const bytes);

    /** Simultaneously write and read I2S data.  Transmission and reception are complete when
     * callback is called with I2S_EVENT_IDLE.
     * @par Implemented as
     * - @ref R_SSI_WriteRead()
     *
     * @param[in]   p_ctrl     Control block set in @ref i2s_api_t::open call for this instance.
     * @param[in]   p_src      Buffer of PCM samples.  Must be 4 byte aligned.
     * @param[in]   p_dest     Buffer to store PCM samples.  Must be 4 byte aligned.
     * @param[in]   bytes      Number of bytes in the buffers.  Recommended requesting a multiple of 8 bytes.  If not
     *                         a multiple of 8, padding 0s will be added to transmission to make it a multiple of 8,
     *                         and receive will stop at the multiple of 8 below requested bytes.
     */
    fsp_err_t (* writeRead)(i2s_ctrl_t * const p_ctrl, void const * const p_src, void * const p_dest,
                            uint32_t const bytes);

    /** Get current status and store it in provided pointer p_status.
     * @par Implemented as
     * - @ref R_SSI_StatusGet()
     *
     * @param[in]   p_ctrl     Control block set in @ref i2s_api_t::open call for this instance.
     * @param[out]  p_status   Current status of the driver.
     */
    fsp_err_t (* statusGet)(i2s_ctrl_t * const p_ctrl, i2s_status_t * const p_status);

    /** Allows driver to be reconfigured and may reduce power consumption.
     * @par Implemented as
     * - @ref R_SSI_Close()
     *
     * @param[in]   p_ctrl     Control block set in @ref i2s_api_t::open call for this instance.
     */
    fsp_err_t (* close)(i2s_ctrl_t * const p_ctrl);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - R_SSI_CallbackSet()
     *
     * @param[in]   p_ctrl                   Pointer to the I2S control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(i2s_ctrl_t * const p_api_ctrl, void (* p_callback)(i2s_callback_args_t *),
                              void const * const p_context, i2s_callback_args_t * const p_callback_memory);
} i2s_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_i2s_instance
{
    i2s_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    i2s_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    i2s_api_t const * p_api;           ///< Pointer to the API structure for this instance
} i2s_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup I2S_API)
 **********************************************************************************************************************/
