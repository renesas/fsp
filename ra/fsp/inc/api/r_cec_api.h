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

#ifndef R_CEC_API_H
#define R_CEC_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup CEC_API CEC Interface
 * @brief Interface for CEC peripheral
 *
 * @section CEC_INTERFACE_SUMMARY Summary
 * The CEC interface provides common APIs for CEC HAL drivers and supports the following features:
 * - Opening and closing the CEC module.
 * - Allocation for full range of local address settings (TV, Recording Device, Playback Device, etc.)
 * - Supports a user-callback function (required), invoked when transmit, receive, or error interrupts are received.
 *
 * Implemented by:
 * - @ref CEC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_cec_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CEC Addresses */
typedef enum e_cec_addr
{
    CEC_ADDR_TV                 = 0U,  ///< CEC Address for TV
    CEC_ADDR_RECORDING_DEVICE_1 = 1U,  ///< CEC Address for Recording Device 1
    CEC_ADDR_RECORDING_DEVICE_2 = 2U,  ///< CEC Address for Recording Devide 2
    CEC_ADDR_TUNER_1            = 3U,  ///< CEC Address for Tuner 1
    CEC_ADDR_PLAYBACK_DEVICE_1  = 4U,  ///< CEC Address for Playback Device 1
    CEC_ADDR_AUDIO_SYSTEM       = 5U,  ///< CEC Address for Audio System
    CEC_ADDR_TUNER_2            = 6U,  ///< CEC Address for Tuner 2
    CEC_ADDR_TUNER_3            = 7U,  ///< CEC Address for Tuner 3
    CEC_ADDR_PLAYBACK_DEVICE_2  = 8U,  ///< CEC Address for Playback Device 2
    CEC_ADDR_RECORDING_DEVICE_3 = 9U,  ///< CEC Address for Recording Device 3
    CEC_ADDR_TUNER_4            = 10U, ///< CEC Address for Tuner 4
    CEC_ADDR_PLAYBACK_DEVICE_3  = 11U, ///< CEC Address for Playback Device 3
    CEC_ADDR_SPECIFIC_USE       = 14U, ///< CEC Address for Specific Use
    CEC_ADDR_UNREGISTERED       = 15U, ///< CEC Address for Unregistered Devices
    CEC_ADDR_BROADCAST          = 15U  ///< CEC Broadcast message
} cec_addr_t;

/** CEC Source Clock */
typedef enum e_cec_clock_source
{
    CEC_CLOCK_SOURCE_PCLKB_DIV_32   = 0, ///< PCLKB / 32 is the source of the CEC Clock
    CEC_CLOCK_SOURCE_PCLKB_DIV_64   = 1, ///< PCLKB / 64 is the source of the CEC Clock
    CEC_CLOCK_SOURCE_PCLKB_DIV_128  = 2, ///< PCLKB / 128 is the source of the CEC Clock
    CEC_CLOCK_SOURCE_PCLKB_DIV_256  = 3, ///< PCLKB / 256 is the source of the CEC Clock
    CEC_CLOCK_SOURCE_PCLKB_DIV_512  = 4, ///< PCLKB / 512 is the source of the CEC Clock
    CEC_CLOCK_SOURCE_PCLKB_DIV_1024 = 5, ///< PCLKB / 1024 is the source of the CEC Clock
    CEC_CLOCK_SOURCE_CECCLK         = 6, ///< CECCLK is the source of the CEC Clock
    CEC_CLOCK_SOURCE_CECCLK_DIV_256 = 7, ///< CECCLK / 256 is the source of the CEC Clock
} cec_clock_source_t;

/** CEC State */
typedef enum e_cec_state
{
    CEC_STATE_UNINIT    = 0x00,        ///< Module requires initialization
    CEC_STATE_READY     = 0x01,        ///< Module ready for operation
    CEC_STATE_TX_ACTIVE = 0x02,        ///< Transmit in progress, either direct or broadcast
    CEC_STATE_RX_ACTIVE = 0x04,        ///< Receive in progress, either direct or broadcast
    CEC_STATE_BUSY      = 0x08,        ///< CEC Signal Free Time has not yet elapsed
} cec_state_t;

/** CEC Error Code */
typedef enum e_cec_error
{
    CEC_ERROR_NONE   = 0x000,          ///< No errors currently active
    CEC_ERROR_OERR   = 0x001,          ///< Overrun error
    CEC_ERROR_UERR   = 0x002,          ///< Unterrun Error
    CEC_ERROR_ACKERR = 0x004,          ///< ACK Error
    CEC_ERROR_TERR   = 0x008,          ///< Timing Error
    CEC_ERROR_TXERR  = 0x010,          ///< Transmission Error
    CEC_ERROR_AERR   = 0x020,          ///< Bus arbitration Loss
    CEC_ERROR_BLERR  = 0x040,          ///< Bus lock error
    CEC_ERROR_ADDR   = 0x100,          ///< Address allocation error
} cec_error_t;

/** CEC event codes */
typedef enum e_cec_event
{
    CEC_EVENT_RX_DATA,                 ///< Receive Data byte event
    CEC_EVENT_RX_COMPLETE,             ///< Receive complete event
    CEC_EVENT_TX_COMPLETE,             ///< Transmit complete event
    CEC_EVENT_READY,                   ///< CEC Address allocated and module is now ready
    CEC_EVENT_ERR,                     ///< Error has occurred
} cec_event_t;

typedef struct st_cec_status
{
    cec_addr_t  local_address;         ///< Local address
    cec_state_t state;                 ///< CEC module state
} cec_status_t;

/** CEC message */
typedef union
{
    struct
    {
        cec_addr_t destination : 8;                                 ///< Destination Address
        uint8_t    opcode;                                          ///< CEC Opcode
        uint8_t    data[CEC_DATA_BUFFER_LENGTH];                    ///< CEC Message Data
    };
    uint8_t raw_data[CEC_DATA_BUFFER_LENGTH + 2 * sizeof(uint8_t)]; ///< Contiguous raw data
} cec_message_t;

/** CEC callback parameter definition */
typedef struct st_cec_callback_args
{
    cec_event_t  event;                ///< Event code
    void const * p_context;            ///< Context provided to user during callback
    bool         addr_match;           ///< Local addresss matches message destination
    uint8_t      data_byte;            ///< Received data byte (INTDA)
    cec_status_t status;               ///< CEC Module status data
    cec_error_t  errors;               ///< Error code bitfield
} cec_callback_args_t;

typedef struct st_cec_timing_t
{
    uint16_t bit_width_tx_start_low;         ///< Bit Width Transmit Timing Register for Start Bit Low State
    uint16_t bit_width_tx_start_high;        ///< Bit Width Transmit Timing Register for Start Bit High State
    uint16_t bit_width_tx_zero_low;          ///< Bit Width Transmit Timing Register for Logical Zero Low State
    uint16_t bit_width_tx_one_low;           ///< Bit Width Transmit Timing Register for Logical One Low State
    uint16_t bit_width_tx_bit_overall;       ///< Bit Width Transmit Timing Register for Overall Bit Width
    uint16_t bit_width_rx_start_low_min;     ///< Bit Width Receive Timing Register for Start Bit Minimum Low State Time
    uint16_t bit_width_rx_start_low_max;     ///< Bit Width Receive Timing Register for Start Bit Maximum Low State Time
    uint16_t bit_width_rx_start_overall_min; ///< Bit Width Receive Timing Register for Start Bit Minimum High State Time
    uint16_t bit_width_rx_start_overall_max; ///< Bit Width Receive Timing Register for Start Bit Maximum High State Time
    uint16_t bit_width_rx_zero_low_min;      ///< Bit Width Receive Timing Register for Logical Zero Minimum Low State Time
    uint16_t bit_width_rx_zero_low_max;      ///< Bit Width Receive Timing Register for Logical Zero Maximum Low State Time
    uint16_t bit_width_rx_one_low_min;       ///< Bit Width Receive Timing Register for Logical One Minimum Low State Time
    uint16_t bit_width_rx_one_low_max;       ///< Bit Width Receive Timing Register for Logical One Maximum Low State Time
    uint16_t bit_width_rx_bit_overall_min;   ///< Bit Width Receive Timing Register for Overall Minimum Bit Width
    uint16_t bit_width_rx_bit_overall_max;   ///< Bit Width Receive Timing Register for Overall Maximum Bit Width
} cec_timing_t;

/** CEC Configuration */
typedef struct st_cec_cfg
{
    cec_timing_t const * bit_timing_cfg;               ///< CEC Bit Timing Configuration
    uint16_t             rx_data_sample_time;          ///< Receive Data Sample Time Setting
    uint16_t             rx_data_bit_reference_width;  ///< Receive Data Bit Reference Width

    void (* p_callback)(cec_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                            ///< User defined callback context

    uint8_t   ipl;                                     ///< Error/Data/Message interrupt priority level
    IRQn_Type error_irq;                               ///< Error IRQ number
    IRQn_Type data_irq;                                ///< Data IRQ number
    IRQn_Type msg_irq;                                 ///< Communication Complete IRQ number

    void * p_extend;                                   ///< Pointer to extended configuration structure
} cec_cfg_t;

/** CEC control block.  Allocate an instance specific control block to pass into the CEC API calls.
 * @par Implemented as
 * - cec_instance_ctrl_t
 */
typedef void cec_ctrl_t;

/** Shared Interface definition for CEC */
typedef struct st_cec_api
{
    /** Open function for CEC device
     * @par Implemented as
     * - @ref R_CEC_Open()
     *
     * @param[in,out]  p_ctrl           Pointer to the CEC control block. Must be declared by user. Value set here.
     * @param[in]      p_cfg            Pointer to CEC configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(cec_ctrl_t * const p_ctrl, cec_cfg_t const * const p_cfg);

    /** Initializes the CEC device. May be called any time after the CEC module has been opened.
     * This API blocks until the device initialization procedure is complete.
     * @par Implemented as
     * - @ref R_CEC_MediaInit()
     *
     * @param[in]     p_ctrl            Pointer to CEC instance control block.
     * @param[out]    local_address     Desired Logical address for local device.
     */
    fsp_err_t (* mediaInit)(cec_ctrl_t * const p_ctrl, cec_addr_t local_address);

    /** Write function for CEC device
     * @par Implemented as
     * - @ref R_CEC_Write()
     *
     * @param[in]     p_ctrl            Pointer to CEC instance control block
     * @param[in]     p_message         Message data
     * @param[in]     message_size      Total size of entire message
     */
    fsp_err_t (* write)(cec_ctrl_t * const p_ctrl, cec_message_t const * const p_message, uint32_t message_size);

    /** Close function for CEC device
     * @par Implemented as
     * - @ref R_CEC_Close()
     *
     * @param[in]     p_ctrl            Pointer to CEC instance control block
     * @param[out]    p_message         Message data
     */
    fsp_err_t (* close)(cec_ctrl_t * const p_ctrl);

    /** Get CEC channel info.
     * @par Implemented as
     * - @ref R_CEC_StatusGet()
     *
     * @param[in]   p_ctrl              Pointer to CEC instance control block
     * @param[out]  p_status            Memory address to return channel specific data to.
     */
    fsp_err_t (* statusGet)(cec_ctrl_t * const p_ctrl, cec_status_t * const p_status);

    /** Specify callback function, optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_CEC_CallbackSet()
     *
     * @param[in]   p_ctrl              Control block set in @ref cec_api_t::open call.
     * @param[in]   p_callback          Callback function to register
     * @param[in]   p_context           Pointer to send to callback function
     * @param[in]   p_callback_memory   Pointer to volatile memory where callback structure cec be allocated.
     *                                  Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(cec_ctrl_t * const p_ctrl, void (* p_callback)(cec_callback_args_t *),
                              void const * const p_context, cec_callback_args_t * const p_callback_memory);
} cec_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_cec_instance
{
    cec_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    cec_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    cec_api_t const * p_api;           ///< Pointer to the API structure for this instance
} cec_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup CEC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
