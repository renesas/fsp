/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_LIN_API_H
#define R_LIN_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup LIN_API LIN Interface
 * @brief Interface for LIN communications.
 *
 * @section LIN_INTERFACE_SUMMARY Summary
 * The LIN interface provides common APIs for LIN HAL drivers. The LIN interface supports the following features:
 *  - Half-duplex master or slave LIN communication
 *  - Interrupt driven transmit/receive processing
 *  - Callback function with returned event code and data
 *  - Checksum generation and validation (standard or enhanced)
 *  - Bus Sleep and Wakeup
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** LIN driver mode */
typedef enum e_lin_mode
{
    LIN_MODE_SLAVE  = 0U,              ///< Slave mode
    LIN_MODE_MASTER = 1U,              ///< Master mode
} lin_mode_t;

/** LIN checksum type */
typedef enum e_lin_checksum_type
{
    LIN_CHECKSUM_TYPE_CLASSIC  = 0U,   ///< 8 bit LIN classic checksum over data bytes only
    LIN_CHECKSUM_TYPE_ENHANCED = 1U,   ///< 8 bit LIN enhanced checksum over data bytes and PID
    LIN_CHECKSUM_TYPE_NONE     = 2U,   ///< Skip driver checksum generation/validation
} lin_checksum_type_t;

/** LIN Event codes */
typedef enum e_lin_event
{
    LIN_EVENT_NONE = (0),                                  ///< No event present
    LIN_EVENT_RX_START_FRAME_COMPLETE       = (1UL << 1),  ///< DEPRECATED, do not use
    LIN_EVENT_RX_INFORMATION_FRAME_COMPLETE = (1UL << 2),  ///< DEPRECATED, do not use
    LIN_EVENT_TX_START_FRAME_COMPLETE       = (1UL << 3),  ///< DEPRECATED, do not use
    LIN_EVENT_TX_INFORMATION_FRAME_COMPLETE = (1UL << 4),  ///< DEPRECATED, do not use
    LIN_EVENT_RX_HEADER_COMPLETE            = (1UL << 1),  ///< Header received event.
    LIN_EVENT_RX_DATA_COMPLETE              = (1UL << 2),  ///< Data received event.
    LIN_EVENT_TX_HEADER_COMPLETE            = (1UL << 3),  ///< Header transmission complete event
    LIN_EVENT_TX_DATA_COMPLETE              = (1UL << 4),  ///< Data transmission complete event
    LIN_EVENT_ERR_INVALID_CHECKSUM          = (1UL << 5),  ///< Data received successfully, but checksum was invalid
    LIN_EVENT_TX_WAKEUP_COMPLETE            = (1UL << 6),  ///< Transmit wake up complete event
    LIN_EVENT_RX_WAKEUP_COMPLETE            = (1UL << 7),  ///< Receive wake up complete event
    LIN_EVENT_ERR_BUS_COLLISION_DETECTED    = (1UL << 9),  ///< Bus collision detection event
    LIN_EVENT_ERR_COUNTER_OVERFLOW          = (1UL << 14), ///< Counter overflow event
    LIN_EVENT_ERR_OVERRUN                   = (1UL << 24), ///< Overrun error event
    LIN_EVENT_ERR_PARITY                    = (1UL << 27), ///< Parity error event (header only, LIN data is sent without parity)
    LIN_EVENT_ERR_FRAMING                   = (1UL << 28), ///< Framing error event
} lin_event_t;

/** LIN Transfer Parameters */
typedef struct st_lin_transfer_params
{
    uint8_t id;                        ///< The unprotected frame ID associated with the data transfer
    union
    {
        uint8_t * p_information;       ///< DEPRECATED, do not use
        uint8_t * p_data;              ///< Pointer to rx or tx buffer associated with the data transfer.
    };

    uint8_t             num_bytes;     ///< Length of buffer pointed to by p_data, in bytes
    lin_checksum_type_t checksum_type; ///< Checksum type to use for checksum generation (when writing data) or validation (when reading data). See @ref lin_checksum_type_t
} lin_transfer_params_t;

/** LIN Callback Arguments */
typedef struct st_lin_callback_arg
{
    uint32_t    channel;               ///< Channel number
    lin_event_t event;                 ///< Event code

    /** Valid for the following events:
     *    - LIN_EVENT_RX_DATA_COMPLETE
     *    - LIN_EVENT_ERR_FRAMING
     *    - LIN_EVENT_ERR_INVALID_CHECKSUM
     *
     * Contains the number of data bytes received for a
     * data reception.
     */
    uint8_t bytes_received;

    /** For LIN slave: Contains the most recently received protected identifier
     * For LIN master: Contains the most recently transmitted protected identifier.
     */
    uint8_t pid;

    /** Received checksum. Valid for the following events:
     *   - LIN_EVENT_RX_DATA_COMPLETE
     *   - LIN_EVENT_ERR_INVALID_CHECKSUM.
     */
    uint8_t checksum;

    void * p_context;                  ///< Context provided to user during callback
} lin_callback_args_t;

/** LIN configuration block */
typedef struct st_lin_cfg
{
    /* LIN generic configuration */
    uint8_t    channel;                                ///< Select a channel corresponding to the channel number of the hardware.
    lin_mode_t mode;                                   ///< Driver mode (master or slave)

    /* Configuration for LIN Event processing */
    void (* p_callback)(lin_callback_args_t * p_args); ///< Pointer to callback function
    void * p_context;                                  ///< User defined context passed into callback function

    /* Pointer to LIN peripheral specific configuration */
    void const * p_extend;                             ///< LIN hardware dependent configuration
} lin_cfg_t;

/** LIN control block.  Allocate an instance specific control block to pass into the LIN API calls.
 */
typedef void lin_ctrl_t;

/** Interface definition for LIN */
typedef struct st_lin_api
{
    /** Open LIN device.  Transmission and reception of LIN frames is enabled upon successful return from this function.
     *
     * @param[in,out]  p_ctrl     Pointer to the LIN control block.  Must be declared by user.  Value set here.
     * @param[in]      p_cfg      Pointer to LIN configuration structure.  All elements of this structure must be set by
     *                            user.
     */
    fsp_err_t (* open)(lin_ctrl_t * const p_ctrl, lin_cfg_t const * const p_cfg);

    /** Begin non-blocking transmission of a LIN frame.
     *
     * If the node is a LIN master, the LIN header is transmitted before data, if present.
     *
     * For header-only transmissions (master mode), when the header transmission completes successfully, the
     * callback is called with the event LIN_EVENT_TX_HEADER_COMPLETE.
     *
     * For header+data (master mode) or data-only transmission (slave mode), when the data transmission completes
     * successfully, the callback is called with event LIN_EVENT_TX_DATA_COMPLETE.
     *
     * @param[in,out]   p_ctrl               Pointer to the LIN control block.
     * @param[in]       p_transfer_params    Pointer to parameters required for the write transaction.
     */
    fsp_err_t (* write)(lin_ctrl_t * const p_ctrl, const lin_transfer_params_t * const p_transfer_params);

    /** Begin non-blocking read of data bytes.
     *
     * When a read completes successfully, the callback is called with event LIN_EVENT_RX_DATA_COMPLETE.
     *
     * @param[in]   p_ctrl                   Pointer to the LIN control block for the channel.
     * @param[in]   p_transfer_params        Pointer to parameters required for the read transaction.
     */
    fsp_err_t (* read)(lin_ctrl_t * const p_ctrl, lin_transfer_params_t * const p_transfer_params);

    /** Abort ongoing transfer.
     *
     * @param[in]   p_ctrl                   Pointer to the LIN control block.
     */
    fsp_err_t (* communicationAbort)(lin_ctrl_t * const p_ctrl);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the LIN control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(lin_ctrl_t * const p_ctrl, void (* p_callback)(lin_callback_args_t *),
                              void * const p_context, lin_callback_args_t * const p_callback_memory);

    /** Send wakeup signal for LIN device.
     *
     * @param[in]   p_ctrl                  Pointer to the LIN control block.
     */
    fsp_err_t (* wakeupSend)(lin_ctrl_t * const p_ctrl);

    /** Place the LIN node in bus sleep mode.
     *
     * @param[in]   p_ctrl                  Pointer to the LIN control block.
     */
    fsp_err_t (* sleepEnter)(lin_ctrl_t * const p_ctrl);

    /** Exit the bus sleep mode for LIN device.
     *
     * @param[in]   p_ctrl                  Pointer to the LIN control block.
     */
    fsp_err_t (* sleepExit)(lin_ctrl_t * const p_ctrl);

    /** Close LIN device.
     *
     * @param[in]   p_ctrl                  Pointer to the LIN control block.
     */
    fsp_err_t (* close)(lin_ctrl_t * const p_ctrl);

    /** [DEPRECATED] Use @ref lin_api_t::read
     */
    fsp_err_t (* informationFrameRead)(lin_ctrl_t * const p_ctrl, lin_transfer_params_t * const p_transfer_params);

    /** [DEPRECATED] Use @ref lin_api_t::write
     */
    fsp_err_t (* startFrameWrite)(lin_ctrl_t * const p_ctrl, uint8_t const id);

    /** [DEPRECATED] Use @ref lin_api_t::write
     */
    fsp_err_t (* informationFrameWrite)(lin_ctrl_t * const                  p_ctrl,
                                        const lin_transfer_params_t * const p_transfer_params);
} lin_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_lin_instance
{
    lin_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    lin_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    lin_api_t const * p_api;           ///< Pointer to the API structure for this instance
} lin_instance_t;

/******************************************************************************************************************//**
 * @} (end addtogroup LIN_API)
 *********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
