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

#ifndef R_CAN_API_H
#define R_CAN_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup CAN_API CAN Interface
 * @brief Interface for CAN peripheral
 *
 * @section CAN_INTERFACE_SUMMARY Summary
 * The CAN interface provides common APIs for CAN HAL drivers. CAN interface supports following features.
 * - Full-duplex CAN communication
 * - Generic CAN parameter setting
 * - Interrupt driven transmit/receive processing
 * - Callback function support with returning event code
 * - Hardware resource locking during a transaction
 *
 * Implemented by: @ref CAN
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
 * Macro definitions
 **********************************************************************************************************************/
#define CAN_API_VERSION_MAJOR    (1U)  // DEPRECATED
#define CAN_API_VERSION_MINOR    (1U)  // DEPRECATED

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CAN event codes */
typedef enum e_can_event
{
    CAN_EVENT_ERR_WARNING          = 2,    ///< Error Warning event.
    CAN_EVENT_ERR_PASSIVE          = 4,    ///< Error Passive event.
    CAN_EVENT_ERR_BUS_OFF          = 8,    ///< Bus Off event.
    CAN_EVENT_BUS_RECOVERY         = 16,   ///< Bus Off Recovery event.
    CAN_EVENT_MAILBOX_MESSAGE_LOST = 32,   ///< Mailbox has been overrun.
    CAN_EVENT_RX_COMPLETE          = 1024, ///< Receive complete event.
    CAN_EVENT_TX_COMPLETE          = 2048  ///< Transmit complete event.
} can_event_t;

/** CAN Status */
typedef enum e_can_status
{
    CAN_STATUS_NEW_DATA                 = 1,  ///< New Data status flag
    CAN_STATUS_SENT_DATA                = 2,  ///< Sent Data status flag
    CAN_STATUS_RECEIVE_FIFO             = 4,  ///< Receive FIFO status flag (Not supported)
    CAN_STATUS_TRANSMIT_FIFO            = 8,  ///< Transmit FIFO status flag (Not supported)
    CAN_STATUS_NORMAL_MBOX_MESSAGE_LOST = 16, ///< Normal mailbox message lost status flag
    CAN_STATUS_FIFO_MBOX_MESSAGE_LOST   = 32, ///< FIFO mailbox message lost status flag (Not Supported)
    CAN_STATUS_TRANSMISSION_ABORT       = 64, ///< Transmission abort status flag
    CAN_STATUS_ERROR         = 128,           ///< Error status flag
    CAN_STATUS_RESET_MODE    = 256,           ///< Reset mode status flag
    CAN_STATUS_HALT_MODE     = 512,           ///< Halt mode status flag
    CAN_STATUS_SLEEP_MODE    = 1024,          ///< Sleep mode status flag
    CAN_STATUS_ERROR_PASSIVE = 2048,          ///< Error-passive status flag
    CAN_STATUS_BUS_OFF       = 4096,          ///< Bus-off status flag
} can_status_t;

/** CAN Error Code */
typedef enum e_can_error
{
    CAN_ERROR_STUFF              = 1,   ///< Stuff Error
    CAN_ERROR_FORM               = 2,   ///< Form Error
    CAN_ERROR_ACK                = 4,   ///< ACK Error
    CAN_ERROR_CRC                = 8,   ///< CRC Error
    CAN_ERROR_BIT_RECESSIVE      = 16,  ///< Bit Error (recessive) Error
    CAN_ERROR_BIT_DOMINANT       = 32,  ///< Bit Error (dominant) Error
    CAN_ERROR_ACK_DELIMITER      = 64,  ///< ACK Delimiter Error
    CAN_ERROR_ERROR_DISPLAY_MODE = 128, ///< Error Display mode
} can_error_t;

/** CAN Operation modes */
typedef enum e_can_operation_mode
{
    CAN_OPERATION_MODE_NORMAL = 0,     ///< CAN Normal Operation Mode.
    CAN_OPERATION_MODE_RESET,          ///< CAN Reset Operation Mode.
    CAN_OPERATION_MODE_HALT,           ///< CAN Halt Operation Mode.
    CAN_OPERATION_MODE_SLEEP           ///< CAN SLEEP Operation Mode.
} can_operation_mode_t;

/** CAN Test modes */
typedef enum e_can_test_mode
{
    CAN_TEST_MODE_DISABLED          = 0, ///< CAN Test Mode Disabled.
    CAN_TEST_MODE_LISTEN            = 3, ///< CAN Test Listen Mode.
    CAN_TEST_MODE_LOOPBACK_EXTERNAL = 5, ///< CAN Test External Loopback Mode.
    CAN_TEST_MODE_LOOPBACK_INTERNAL = 7  ///< CAN Test Internal Loopback Mode.
} can_test_mode_t;

typedef struct st_can_info
{
    can_status_t status;               ///< Useful information from the CAN status register.
    uint8_t      error_count_transmit; ///< Transmit error count.
    uint8_t      error_count_receive;  ///< Receive error count.
    can_error_t  error_code;           ///< Error code, cleared after reading.
} can_info_t;

/** CAN ID modes */
typedef enum e_can_id_mode
{
    CAN_ID_MODE_STANDARD,              ///< Standard IDs of 11 bits used.
    CAN_ID_MODE_EXTENDED,              ///< Extended IDs of 29 bits used.
} can_id_mode_t;

/** CAN frame types */
typedef enum e_can_frame_type
{
    CAN_FRAME_TYPE_DATA,               ///< Data frame type.
    CAN_FRAME_TYPE_REMOTE,             ///< Remote frame type.
} can_frame_type_t;

/** CAN Message Modes */
typedef enum e_can_message_mode
{
    CAN_MESSAGE_MODE_OVERWRITE = 0,    ///< Receive data will be overwritten if not read before the next frame.
    CAN_MESSAGE_MODE_OVERRUN,          ///< Receive data will be retained until it is read.
} can_message_mode_t;

/** CAN Source Clock */
typedef enum e_can_clock_source
{
    CAN_CLOCK_SOURCE_PCLKB = 0,        ///< PCLKB is the source of the CAN Clock
    CAN_CLOCK_SOURCE_CANMCLK,          ///< CANMCLK is the source of the CAN Clock
} can_clock_source_t;

/** CAN Time Segment 1 Time Quanta */
typedef enum e_can_time_segment1
{
    CAN_TIME_SEGMENT1_TQ4 = 3,         ///< Time Segment 1 setting for  4 Time Quanta
    CAN_TIME_SEGMENT1_TQ5,             ///< Time Segment 1 setting for  5 Time Quanta
    CAN_TIME_SEGMENT1_TQ6,             ///< Time Segment 1 setting for  6 Time Quanta
    CAN_TIME_SEGMENT1_TQ7,             ///< Time Segment 1 setting for  7 Time Quanta
    CAN_TIME_SEGMENT1_TQ8,             ///< Time Segment 1 setting for  8 Time Quanta
    CAN_TIME_SEGMENT1_TQ9,             ///< Time Segment 1 setting for  9 Time Quanta
    CAN_TIME_SEGMENT1_TQ10,            ///< Time Segment 1 setting for 10 Time Quanta
    CAN_TIME_SEGMENT1_TQ11,            ///< Time Segment 1 setting for 11 Time Quanta
    CAN_TIME_SEGMENT1_TQ12,            ///< Time Segment 1 setting for 12 Time Quanta
    CAN_TIME_SEGMENT1_TQ13,            ///< Time Segment 1 setting for 13 Time Quanta
    CAN_TIME_SEGMENT1_TQ14,            ///< Time Segment 1 setting for 14 Time Quanta
    CAN_TIME_SEGMENT1_TQ15,            ///< Time Segment 1 setting for 15 Time Quanta
    CAN_TIME_SEGMENT1_TQ16,            ///< Time Segment 1 setting for 16 Time Quanta
} can_time_segment1_t;

/** CAN Time Segment 2 Time Quanta */
typedef enum e_can_time_segment2
{
    CAN_TIME_SEGMENT2_TQ2 = 1,         ///< Time Segment 2 setting for 2 Time Quanta
    CAN_TIME_SEGMENT2_TQ3,             ///< Time Segment 2 setting for 3 Time Quanta
    CAN_TIME_SEGMENT2_TQ4,             ///< Time Segment 2 setting for 4 Time Quanta
    CAN_TIME_SEGMENT2_TQ5,             ///< Time Segment 2 setting for 5 Time Quanta
    CAN_TIME_SEGMENT2_TQ6,             ///< Time Segment 2 setting for 6 Time Quanta
    CAN_TIME_SEGMENT2_TQ7,             ///< Time Segment 2 setting for 7 Time Quanta
    CAN_TIME_SEGMENT2_TQ8,             ///< Time Segment 2 setting for 8 Time Quanta
} can_time_segment2_t;

/** CAN Synchronization Jump Width Time Quanta */
typedef enum e_can_sync_jump_width
{
    CAN_SYNC_JUMP_WIDTH_TQ1 = 1,       ///< Synchronization Jump Width setting for 1 Time Quanta
    CAN_SYNC_JUMP_WIDTH_TQ2,           ///< Synchronization Jump Width setting for 2 Time Quanta
    CAN_SYNC_JUMP_WIDTH_TQ3,           ///< Synchronization Jump Width setting for 3 Time Quanta
    CAN_SYNC_JUMP_WIDTH_TQ4,           ///< Synchronization Jump Width setting for 4 Time Quanta
} can_sync_jump_width_t;

/** CAN bit rate configuration. */
typedef struct st_can_bit_timing_cfg
{
    uint32_t              baud_rate_prescaler;        ///< Baud rate prescaler. Valid values: 1 - 1024.
    can_time_segment1_t   time_segment_1;             ///< Time segment 1 control.
    can_time_segment2_t   time_segment_2;             ///< Time segment 2 control.
    can_sync_jump_width_t synchronization_jump_width; ///< Synchronization jump width.
} can_bit_timing_cfg_t;

/** CAN Id */
typedef uint32_t can_id_t;

/** CAN data Frame */
typedef struct st_can_frame
{
    can_id_t         id;               ///< CAN id.
    uint8_t          data_length_code; ///< CAN Data Length code, number of bytes in the message.
    uint8_t          data[8];          ///< CAN data, up to 8 bytes.
    can_frame_type_t type;             ///< Frame type, data or remote frame.
} can_frame_t;

/** CAN  Mailbox type */
typedef enum e_can_mailbox_send_receive
{
    CAN_MAILBOX_RECEIVE,               ///< Mailbox is for receiving.
    CAN_MAILBOX_TRANSMIT,              ///< Mailbox is for sending.
} can_mailbox_send_receive_t;

/** CAN Mailbox */
typedef struct st_can_mailbox
{
    can_id_t mailbox_id;                     ///< Mailbox ID.
    can_mailbox_send_receive_t mailbox_type; ///< Receive or Transmit mailbox type.
    can_frame_type_t           frame_type;   ///< Frame type for receive mailbox.
} can_mailbox_t;

/** CAN callback parameter definition */
typedef struct st_can_callback_arg
{
    uint32_t      channel;             ///< Device channel number.
    can_event_t   event;               ///< Event code.
    uint32_t      mailbox;             ///< Mailbox number of interrupt source.
    can_frame_t * p_frame;             ///< Pointer to the received frame.
    void const  * p_context;           ///< Context provided to user during callback.
} can_callback_args_t;

/** CAN Configuration */
typedef struct st_can_cfg
{
    /* CAN generic configuration */
    uint32_t               channel;                    ///< CAN channel.
    can_bit_timing_cfg_t * p_bit_timing;               ///< CAN bit timing.
    can_id_mode_t          id_mode;                    ///< Standard or Extended ID mode.
    uint32_t               mailbox_count;              ///< Number of mailboxes.
    can_mailbox_t        * p_mailbox;                  ///< Pointer to mailboxes.
    can_message_mode_t     message_mode;               ///< Overwrite message or overrun.
    can_operation_mode_t   operation_mode;             ///< CAN operation mode.
    can_test_mode_t        test_mode;                  ///< CAN operation mode.

    /* Configuration for CAN Event processing */
    void (* p_callback)(can_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                            ///< User defined callback context.

    /* Pointer to CAN peripheral specific configuration */
    void const * p_extend;                             ///< CAN hardware dependent configuration
    uint8_t      ipl;                                  ///< Error/Transmit/Receive interrupt priority
    IRQn_Type    error_irq;                            ///< Error IRQ number
    IRQn_Type    mailbox_rx_irq;                       ///< Receive mailbox IRQ number
    IRQn_Type    mailbox_tx_irq;                       ///< Transmit mailbox IRQ number
} can_cfg_t;

/** CAN control block.  Allocate an instance specific control block to pass into the CAN API calls.
 * @par Implemented as
 * - can_instance_ctrl_t
 */
typedef void can_ctrl_t;

/** Shared Interface definition for CAN */
typedef struct st_can_api
{
    /** Open function for CAN device
     * @par Implemented as
     * - R_CAN_Open()
     *
     * @param[in,out]  p_ctrl     Pointer to the CAN control block. Must be declared by user. Value set here.
     * @param[in]      can_cfg_t  Pointer to CAN configuration structure. All elements of this structure must be set by
     *                            user.
     */
    fsp_err_t (* open)(can_ctrl_t * const p_ctrl, can_cfg_t const * const p_cfg);

    /** Write function for CAN device
     * @par Implemented as
     * - R_CAN_Write()
     * @param[in]   p_ctrl          Pointer to the CAN control block.
     * @param[in]   mailbox         Mailbox (number) to write to.
     * @param[in]   p_frame         Pointer for frame of CAN ID, DLC, data and frame type to write.
     */
    fsp_err_t (* write)(can_ctrl_t * const p_ctrl, uint32_t mailbox, can_frame_t * const p_frame);

    /** Close function for CAN device
     * @par Implemented as
     * - R_CAN_Close()
     * @param[in]   p_ctrl     Pointer to the CAN control block.
     */
    fsp_err_t (* close)(can_ctrl_t * const p_ctrl);

    /** Mode Transition function for CAN device
     * @par Implemented as
     * - R_CAN_ModeTransition()
     * @param[in]   p_ctrl               Pointer to the CAN control block.
     * @param[in]   operation_mode       Destination CAN operation state.
     * @param[in]   test_mode            Destination CAN test state.
     */
    fsp_err_t (* modeTransition)(can_ctrl_t * const p_api_ctrl, can_operation_mode_t operation_mode,
                                 can_test_mode_t test_mode);

    /** Get CAN channel info.
     * @par Implemented as
     * - R_CAN_InfoGet()
     *
     * @param[in]   p_ctrl  Handle for channel (pointer to channel control block)
     * @param[out]  p_info  Memory address to return channel specific data to.
     */
    fsp_err_t (* infoGet)(can_ctrl_t * const p_ctrl, can_info_t * const p_info);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_CAN_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref can_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(can_ctrl_t * const p_api_ctrl, void (* p_callback)(can_callback_args_t *),
                              void const * const p_context, can_callback_args_t * const p_callback_memory);

    /* DEPRECATED Version get function for CAN device
     * @par Implemented as
     * - R_CAN_VersionGet()
     * @param[in]   p_version  Pointer to the memory to store the version information
     */
    fsp_err_t (* versionGet)(fsp_version_t * const p_version);
} can_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_can_instance
{
    can_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    can_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    can_api_t const * p_api;           ///< Pointer to the API structure for this instance
} can_instance_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup CAN_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
