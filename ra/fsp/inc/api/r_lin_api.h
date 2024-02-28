/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 *
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
    LIN_CHECKSUM_TYPE_CLASSIC  = 0U,   ///< 8 bit LIN classic checksum over information bytes only
    LIN_CHECKSUM_TYPE_ENHANCED = 1U,   ///< 8 bit LIN enhanced checksum over information bytes and PID
    LIN_CHECKSUM_TYPE_NONE     = 2U,   ///< Skip driver checksum generation/validation
} lin_checksum_type_t;

/** LIN Event codes */
typedef enum e_lin_event
{
    LIN_EVENT_NONE = (0),                                  ///< No event present
    LIN_EVENT_RX_START_FRAME_COMPLETE       = (1UL << 1),  ///< Start frame received event.
    LIN_EVENT_RX_INFORMATION_FRAME_COMPLETE = (1UL << 2),  ///< Information frame received event.
    LIN_EVENT_TX_START_FRAME_COMPLETE       = (1UL << 3),  ///< Start frame transmission complete event
    LIN_EVENT_TX_INFORMATION_FRAME_COMPLETE = (1UL << 4),  ///< Information transmission complete event
    LIN_EVENT_ERR_INVALID_CHECKSUM          = (1UL << 5),  ///< Information frame received successfully, but checksum was invalid
    LIN_EVENT_ERR_BUS_COLLISION_DETECTED    = (1UL << 9),  ///< Bus collision detection event
    LIN_EVENT_ERR_FRAMING                   = (1UL << 28), ///< Framing error event
    LIN_EVENT_ERR_COUNTER_OVERFLOW          = (1UL << 14), ///< Counter overflow event
    LIN_EVENT_ERR_OVERRUN                   = (1UL << 24), ///< Overrun error event
    LIN_EVENT_ERR_PARITY                    = (1UL << 27), ///< Parity error event (start frame only, LIN information is sent without parity)
} lin_event_t;

/** LIN Transfer Parameters */
typedef struct st_lin_transfer_params
{
    uint8_t             id;            ///< The unprotected frame ID associated with the information frame transfer
    uint8_t           * p_information; ///< Pointer to rx or tx buffer associated with the information frame transfer.
    uint8_t             num_bytes;     ///< Length of buffer pointed to by p_information, in bytes
    lin_checksum_type_t checksum_type; ///< Checksum type to use for checksum generation (when writing frame) or validation (when reading frame). See @ref lin_checksum_type_t
} lin_transfer_params_t;

/** LIN Callback Arguments */
typedef struct st_lin_callback_arg
{
    uint32_t    channel;               ///< Channel number
    lin_event_t event;                 ///< Event code

    /** Valid for the following events:
     *    - LIN_EVENT_RX_INFORMATION_FRAME_COMPLETE
     *    - LIN_EVENT_ERR_FRAMING
     *    - LIN_EVENT_ERR_INVALID_CHECKSUM
     *
     * Contains the number of information bytes received for an
     * information frame reception.
     */
    uint8_t bytes_received;

    /** For LIN slave: Contains the most recently received protected identifier
     * For LIN master: Contains the most recently transmitted protected identifier.
     */
    uint8_t pid;

    /** Received checksum. Valid for the following events:
     *   - LIN_EVENT_RX_INFORMATION_FRAME_COMPLETE
     *   - LIN_EVENT_ERR_INVALID_CHECKSUM.
     */
    uint8_t checksum;

    void const * p_context;            ///< Context provided to user during callback
} lin_callback_args_t;

/** LIN configuration block */
typedef struct st_lin_cfg
{
    /* LIN generic configuration */
    uint8_t    channel;                                ///< Select a channel corresponding to the channel number of the hardware.
    lin_mode_t mode;                                   ///< Driver mode (master or slave)
    uint8_t    rxi_ipl;                                ///< Receive interrupt priority
    IRQn_Type  rxi_irq;                                ///< Receive interrupt IRQ number
    uint8_t    txi_ipl;                                ///< Transmit interrupt priority
    IRQn_Type  txi_irq;                                ///< Transmit interrupt IRQ number
    uint8_t    tei_ipl;                                ///< Transmit end interrupt priority
    IRQn_Type  tei_irq;                                ///< Transmit end interrupt IRQ number
    uint8_t    eri_ipl;                                ///< Error interrupt priority
    IRQn_Type  eri_irq;                                ///< Error interrupt IRQ number

    /* Configuration for LIN Event processing */
    void (* p_callback)(lin_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                            ///< User defined context passed into callback function

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

    /** Begin non-blocking transmission of the LIN start frame. The start frame consists of the break pattern,
     *  sync word, and protected frame identifier (PID). The unprotected identifier should be supplied.
     *  The driver will compute the PID.
     *
     * When the start frame has been transmitted, the callback is called with event LIN_EVENT_TX_START_FRAME_COMPLETE.
     *
     * @param[in,out]  p_ctrl     Pointer to the LIN control block.
     * @param[in]      id         Unprotected frame identifier
     */
    fsp_err_t (* startFrameWrite)(lin_ctrl_t * const p_ctrl, uint8_t const id);

    /** Begin non-blocking transmission of the LIN information frame.
     *
     * The write buffer is used until the write is complete.  When the write completes successfully
     * (all bytes are fully transmitted on the wire) the callback is called with event
     * LIN_EVENT_TX_INFORMATION_FRAME_COMPLETE.
     *
     * @param[in,out]   p_ctrl               Pointer to the LIN control block.
     * @param[in]       p_transfer_params    Pointer to parameters required for the write transaction.
     */
    fsp_err_t (* informationFrameWrite)(lin_ctrl_t * const                  p_ctrl,
                                        const lin_transfer_params_t * const p_transfer_params);

    /** Begin non-blocking read of information frame bytes.
     *
     * When a read completes successfully, the callback is called with event LIN_EVENT_RX_INFORMATION_FRAME_COMPLETE.
     *
     * @param[in]   p_ctrl                   Pointer to the LIN control block for the channel.
     * @param[in]   p_transfer_params        Pointer to parameters required for the read transaction.
     */
    fsp_err_t (* informationFrameRead)(lin_ctrl_t * const p_ctrl, lin_transfer_params_t * const p_transfer_params);

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
                              void const * const p_context, lin_callback_args_t * const p_callback_memory);

    /** Close LIN device.
     *
     * @param[in]   p_ctrl                  Pointer to the LIN control block.
     */
    fsp_err_t (* close)(lin_ctrl_t * const p_ctrl);
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
