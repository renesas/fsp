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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup PTP_API PTP Interface
 * @brief Interface for PTP functions.
 *
 * @section PTP_API_SUMMARY Summary
 * The PTP interface provides the functionality for using PTP.
 *
 * Implemented by:
 * - @ref PTP
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_PTP_API_H
#define R_PTP_API_H

#include "bsp_api.h"
#include "../../src/r_ptp/r_edmac/r_edmac.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*********************************************************************************************************************
 * Macro definitions
 ********************************************************************************************************************/

/* Internal Oscillator. */
#define PTP_TIMESOURCE_INT_OSC    (0xA0)

#if defined(__GNUC__)
 #define PTP_PACKED               __attribute__((packed))
#else
 #define PTP_PACKED               __PACKED
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_ptp_enable
{
    PTP_DISABLE,
    PTP_ENABLE
} ptp_enable_t;

/** Standard PTP message types. */
typedef enum e_ptp_message_type
{
    PTP_MESSAGE_TYPE_SYNC                  = 0x00U, ///< Sync Message Type
    PTP_MESSAGE_TYPE_DELAY_REQ             = 0x01U, ///< Delay_req Message Type
    PTP_MESSAGE_TYPE_PDELAY_REQ            = 0x02U, ///< PDelay_req Message Type
    PTP_MESSAGE_TYPE_PDELAY_RESP           = 0x03U, ///< PDelay_resp Message Type
    PTP_MESSAGE_TYPE_FOLLOW_UP             = 0x08U, ///< Follow_up Message Type
    PTP_MESSAGE_TYPE_DELAY_RESP            = 0x09U, ///< Delay_resp Message Type
    PTP_MESSAGE_TYPE_PDELAY_RESP_FOLLOW_UP = 0x0AU, ///< PDelay_resp_follow_up Message Type
    PTP_MESSAGE_TYPE_ANNOUNCE              = 0x0BU, ///< Announce Message Type
    PTP_MESSAGE_TYPE_SIGNALING             = 0x0CU, ///< Signaling Message Type
    PTP_MESSAGE_TYPE_MANAGEMENT            = 0x0DU, ///< Management Message Type
} ptp_message_type_t;

/** Possible states that the PTP instance can be in. */
typedef enum e_ptp_port_state
{
    PTP_PORT_STATE_GENERATE_ANNOUNCE   = (1U << 3U),            ///< Generate Announce Messages
    PTP_PORT_STATE_GENERATE_SYNC       = (1U << 7U),            ///< Generate Sync Messages
    PTP_PORT_STATE_GENERATE_DELAY_REQ  = (1U << 11U),           ///< Generate Delay_req Messages
    PTP_PORT_STATE_GENERATE_PDELAY_REQ = (1U << 15U),           ///< Generate PDelay_req Messages

    PTP_PORT_STATE_RECEIVE_ANNOUNCE              = (1U << 0U),  ///< Receive Announce Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_SYNC                  = (1U << 4U),  ///< Receive Sync Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_FOLLOW_UP             = (1U << 8U),  ///< Receive Follow_up Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_DELAY_REQ             = (1U << 12U), ///< Receive Delay_req Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_DELAY_RESP            = (1U << 16U), ///< Receive Delay_resp Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_PDELAY_REQ            = (1U << 20U), ///< Receive PDelay_req Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_PDELAY_RESP           = (1U << 24U), ///< Receive PDelay_resp Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_PDELAY_RESP_FOLLOW_UP = (1U << 28U), ///< Receive PDelay_resp_follow_up Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_MANAGEMENT            = (1U << 1U),  ///< Receive Management Messages from @ref ptp_cfg_t::p_callback
    PTP_PORT_STATE_RECEIVE_SIGNALING             = (1U << 5U),  ///< Receive Signaling Messages from @ref ptp_cfg_t::p_callback

    PTP_PORT_STATE_PROCESS_SYNC                  = (1U << 6U),  ///< Enable Sync Message processing.
    PTP_PORT_STATE_PROCESS_FOLLOW_UP             = (1U << 10U), ///< Enable Follow_up Message processing.
    PTP_PORT_STATE_PROCESS_DELAY_REQ             = (1U << 14U), ///< Enable Delay_req Message processing.
    PTP_PORT_STATE_PROCESS_DELAY_RESP            = (1U << 18U), ///< Enable Delay_resp Message processing.
    PTP_PORT_STATE_PROCESS_PDELAY_REQ            = (1U << 22U), ///< Enable PDelay_req Message processing.
    PTP_PORT_STATE_PROCESS_PDELAY_RESP           = (1U << 26U), ///< Enable PDelay_resp Message processing.
    PTP_PORT_STATE_PROCESS_PDELAY_RESP_FOLLOW_UP = (1U << 30U), ///< Enable PDelay_resp_follow_up Message processing.

    /** Configure the PTP instance to only receive Announce, Management, and Signaling Messages. */
    PTP_PORT_STATE_PASSIVE = (PTP_PORT_STATE_RECEIVE_ANNOUNCE |
                              PTP_PORT_STATE_RECEIVE_MANAGEMENT |
                              PTP_PORT_STATE_RECEIVE_SIGNALING),

    /** Configure the PTP instance to operate as a E2E Master. */
    PTP_PORT_STATE_E2E_MASTER = (PTP_PORT_STATE_GENERATE_ANNOUNCE |
                                 PTP_PORT_STATE_GENERATE_SYNC |
                                 PTP_PORT_STATE_PROCESS_DELAY_REQ |
                                 PTP_PORT_STATE_PASSIVE),

    /** Configure the PTP instance to operate as a E2E Slave. */
    PTP_PORT_STATE_E2E_SLAVE = (PTP_PORT_STATE_GENERATE_DELAY_REQ |
                                PTP_PORT_STATE_PROCESS_SYNC |
                                PTP_PORT_STATE_PROCESS_FOLLOW_UP |
                                PTP_PORT_STATE_PROCESS_DELAY_RESP |
                                PTP_PORT_STATE_PASSIVE),

    /** Configure the PTP instance to operate as a P2P Master. */
    PTP_PORT_STATE_P2P_MASTER = (PTP_PORT_STATE_GENERATE_ANNOUNCE |
                                 PTP_PORT_STATE_GENERATE_SYNC |
                                 PTP_PORT_STATE_GENERATE_PDELAY_REQ |
                                 PTP_PORT_STATE_PROCESS_PDELAY_REQ |
                                 PTP_PORT_STATE_PROCESS_PDELAY_RESP |
                                 PTP_PORT_STATE_PROCESS_PDELAY_RESP_FOLLOW_UP |
                                 PTP_PORT_STATE_PASSIVE),

    /** Configure the PTP instance to operate as a P2P Slave. */
    PTP_PORT_STATE_P2P_SLAVE = (PTP_PORT_STATE_GENERATE_PDELAY_REQ |
                                PTP_PORT_STATE_PROCESS_SYNC |
                                PTP_PORT_STATE_PROCESS_FOLLOW_UP |
                                PTP_PORT_STATE_PROCESS_PDELAY_REQ |
                                PTP_PORT_STATE_PROCESS_PDELAY_RESP |
                                PTP_PORT_STATE_PROCESS_PDELAY_RESP_FOLLOW_UP |
                                PTP_PORT_STATE_PASSIVE),

    /** Configure the PTP instance to receive all messages. */
    PTP_PORT_STATE_RECEIVE_ALL = (PTP_PORT_STATE_RECEIVE_ANNOUNCE |
                                  PTP_PORT_STATE_RECEIVE_SYNC |
                                  PTP_PORT_STATE_RECEIVE_FOLLOW_UP |
                                  PTP_PORT_STATE_RECEIVE_DELAY_REQ |
                                  PTP_PORT_STATE_RECEIVE_DELAY_RESP |
                                  PTP_PORT_STATE_RECEIVE_PDELAY_REQ |
                                  PTP_PORT_STATE_RECEIVE_PDELAY_RESP |
                                  PTP_PORT_STATE_RECEIVE_PDELAY_RESP_FOLLOW_UP |
                                  PTP_PORT_STATE_RECEIVE_MANAGEMENT |
                                  PTP_PORT_STATE_RECEIVE_SIGNALING),

    /** Disable all PTP message generation, processing, and reception. */
    PTP_PORT_STATE_DISABLE = 0,
} ptp_port_state_t;

/** The mechanism used for delay messages. */
typedef enum e_ptp_clock_delay_mechanism
{
    PTP_CLOCK_DELAY_MECHANISM_E2E,     ///< End to end delay mechanism
    PTP_CLOCK_DELAY_MECHANISM_P2P      ///< Peer to peer delay mechanism
} ptp_clock_delay_mechanism_t;

/** Frame formats that PTP messages can be encapsulated in. */
typedef enum e_ptp_frame_format
{
    /** Send PTP messages using Ethernet II frames. */
    PTP_FRAME_FORMAT_ETHERII,

    /** Send PTP messages using IEEE802_3 frames. */
    PTP_FRAME_FORMAT_IEEE802_3,

    /** Send PTP messages using Ethernet II frames with an IP and UDP header. */
    PTP_FRAME_FORMAT_ETHERII_IPV4_UDP,

    /** Send PTP messages using IEEE802.3 frames with an IP and UDP header. */
    PTP_FRAME_FORMAT_IEEE802_3_IPV4_UDP,
} ptp_frame_format_t;

/** Filter PTP messages based on destination MAC address. Messages that pass the filter will be transferred to the ETHERC EDMAC. */
typedef enum e_ptp_frame_filter_mode
{
    PTP_FRAME_FILTER_MODE_EXT_PROMISCUOUS_MODE       = 65536U, ///< Receive all packets.
    PTP_FRAME_FILTER_MODE_UNICAST_MULTICAST          = 0U,     ///< Receive all unicast packets destined for the PTP and all multicast packets.
    PTP_FRAME_FILTER_MODE_UNICAST_MULTICAST_FILTERED = 6U,     ///< Receive Unicast packets destined for the PTP and filter configured multicast packets.
    PTP_FRAME_FILTER_MODE_UNICAST = 5U,                        ///< Receive unicast packets destined for the PTP.
} ptp_frame_filter_mode_t;

/** The control field for PTP message header. */
typedef enum PTP_PACKED e_ptp_ctrl_field
{
    PTP_CTRL_FIELD_SYNC       = 0,
    PTP_CTRL_FIELD_DELAY_REQ  = 1,
    PTP_CTRL_FIELD_FOLLOW_UP  = 2,
    PTP_CTRL_FIELD_DELAY_RESP = 3,
    PTP_CTRL_FIELD_MANAGEMENT = 4,
    PTP_CTRL_FIELD_OTHER      = 5
} ptp_ctrl_field_t;

/** STCA input clock frequency. */
typedef enum e_ptp_stca_clock_freq
{
    PTP_STCA_CLOCK_FREQ_20MHZ,         ///< 20 Mhz Input Clock
    PTP_STCA_CLOCK_FREQ_25MHZ,         ///< 25 Mhz Input Clock
    PTP_STCA_CLOCK_FREQ_50MHZ,         ///< 50 Mhz Input Clock
    PTP_STCA_CLOCK_FREQ_100MHZ,        ///< 100 Mhz Input Clock
} ptp_stca_clock_freq_t;

/** STCA input clock selection. */
typedef enum e_ptp_stca_clock_sel
{
    PTP_STCA_CLOCK_SEL_PCLKA_DIV_1 = 1, ///< PCLKA
    PTP_STCA_CLOCK_SEL_PCLKA_DIV_2,     ///< PCLKA Divided by 2
    PTP_STCA_CLOCK_SEL_PCLKA_DIV_3,     ///< PCLKA Divided by 3
    PTP_STCA_CLOCK_SEL_PCLKA_DIV_4,     ///< PCLKA Divided by 4
    PTP_STCA_CLOCK_SEL_PCLKA_DIV_5,     ///< PCLKA Divided by 5
    PTP_STCA_CLOCK_SEL_PCLKA_DIV_6,     ///< PCLKA Divided by 6
    PTP_STCA_CLOCK_SEL_REF50CK0 = 512,  ///< 50-MHz Reference Signal for timing in RMII mode (STCA clock frequency is 25 Mhz when REF50CK0 is used).
} ptp_stca_clock_sel_t;

/** Message interval for transmitting PTP messages. */
typedef enum e_ptp_message_interval
{
    PTP_MESSAGE_INTERVAL_1_128 = -7,   ///< 1 / 128 seconds
    PTP_MESSAGE_INTERVAL_1_64  = -6,   ///< 1 / 64 seconds
    PTP_MESSAGE_INTERVAL_1_32  = -5,   ///< 1 / 32 seconds
    PTP_MESSAGE_INTERVAL_1_16  = -4,   ///< 1 / 16 seconds
    PTP_MESSAGE_INTERVAL_1_8   = -3,   ///< 1 / 8 seconds
    PTP_MESSAGE_INTERVAL_1_4   = -2,   ///< 1 / 4 seconds
    PTP_MESSAGE_INTERVAL_1_2   = -1,   ///< 1 / 2 seconds
    PTP_MESSAGE_INTERVAL_1     = 0,    ///< 1 seconds
    PTP_MESSAGE_INTERVAL_2     = 1,    ///< 2 seconds
    PTP_MESSAGE_INTERVAL_4     = 2,    ///< 4 seconds
    PTP_MESSAGE_INTERVAL_8     = 3,    ///< 8 seconds
    PTP_MESSAGE_INTERVAL_16    = 4,    ///< 16 seconds
    PTP_MESSAGE_INTERVAL_32    = 5,    ///< 32 seconds
    PTP_MESSAGE_INTERVAL_64    = 6,    ///< 64 seconds
} ptp_message_interval_t;

/** Clock correction mode. */
typedef enum e_ptp_clock_correction_mode
{
    PTP_CLOCK_CORRECTION_MODE1,        ///< Correct the local clock using the current offsetFromMaster value.
    PTP_CLOCK_CORRECTION_MODE2,        ///< Correct the local clock using the calculated clock gradient.
} ptp_clock_correction_mode_t;

/** PTP events provided by @ref ptp_cfg_t::p_callback. */
typedef enum e_ptp_event
{
    PTP_EVENT_SYNC_ACQUIRED                = 0x80, ///< The local clock is synchronized to the master clock.
    PTP_EVENT_SYNC_LOST                    = 0x81, ///< The local clock is not synchronized to the master clcok.
    PTP_EVENT_SYNC_MESSAGE_TIMEOUT         = 0x83, ///< A sync message has not been received for the configured time.
    PTP_EVENT_WORST10_ACQUIRED             = 0x84, ///< Gradient worst10 values has been calcualted.
    PTP_EVENT_OFFSET_FROM_MASTER_UPDATED   = 0x00, ///< The offset from the master clock has been updated.
    PTP_EVENT_LOG_MESSAGE_INT_CHANGED      = 0x01, ///< The message interval was changed.
    PTP_EVENT_MEAN_PATH_DELAY_UPDATED      = 0x02, ///< The mean path delay has been updated.
    PTP_EVENT_DELAY_RESP_TIMEOUT           = 0x04, ///< A delay_resp has not been received for the configured time.
    PTP_EVENT_LOG_MESSAGE_INT_OUT_OF_RANGE = 0x05, ///< The updated message interval is out of range.
    PTP_EVENT_DELAY_REQ_FIFO_OVERFLOW      = 0x06, ///< The FIFO buffer for storing information from received Delay_Req messages holds 32 or more entries.
    PTP_EVENT_LOOP_RECEPTION_DETECTED      = 0x0C, ///< A packet with the same sourcePortIdendity as the local clock was received.
    PTP_EVENT_CTRL_INFO_ABNORMALITY        = 0x0D, ///< A malformed frame was received (EDMAC, ETHERC, and EPTPC must be reset).
    PTP_EVENT_DELAY_RESP_PROCESSING_HALTED = 0x10, ///< Processing of delay_resp messages has been halted.
    PTP_EVENT_MESSAGE_GENERATION_HALTED    = 0x11, ///< Generation of messages has been halted.
    PTP_EVENT_MESSAGE_RECEIVED             = 0x12, ///< A PTP message was received from the EDMAC.
    PTP_EVENT_MESSAGE_TRANSMIT_COMPLETE    = 0x13, ///< A PTP message has been transmitted.
    PTP_EVENT_PULSE_TIMER_MINT_RISING_EDGE = 0x14, ///< A rising edge occurred on a pulse timer channel.
    PTP_EVENT_PULSE_TIMER_IPLS_COMMON      = 0x15, ///< A rising or falling edge occurred on any pulse timer channel.
} ptp_event_t;

/** The Ethernet PHY interface type. */
typedef enum e_ptp_ethernet_phy_interface
{
    PTP_ETHERNET_PHY_INTERFACE_MII,    ///< Media-independant interface.
    PTP_ETHERNET_PHY_INTERFACE_RMII,   ///< Reduced media-independant interface.
} ptp_ethernet_phy_interface_t;

/**
 * Clock properties used in the best master clock algorithm (BMCA) in order to
 * determine the grandmaster clock.
 *
 * In master mode, these properties will be advertised in announce messages.
 *
 * Note: The final property used in BMCA is the clock ID. This is usually
 *       configured at runtime because it is often based on the
 *       hardware address.
 */
typedef struct PTP_PACKED st_ptp_clock_properties
{
    uint8_t  priority1;                ///< Priority1 value used in best master calculation.
    uint8_t  cclass;                   ///< Class value.
    uint8_t  accuracy;                 ///< Accuracy of the clock.
    uint16_t variance;                 ///< Variance of the clock.
    uint8_t  priority2;                ///< Priority2 value used as secondary priority in best master calculation.
} ptp_clock_properties_t;

/** Structure for storing time with nanosecond precision . */
typedef struct PTP_PACKED st_ptp_time
{
    uint16_t seconds_upper;            ///< Upper 16 bits of the seconds.
    uint32_t seconds_lower;            ///< Lower 32 bits of the seconds.
    uint32_t nanoseconds;              ///< Nanoseconds
} ptp_time_t;

/**
 *  Flags field in PTP message header.
 */
typedef struct PTP_PACKED st_ptp_message_flags
{
    union
    {
        uint16_t value;
        struct
        {
            /**
             * Set the flag to indicate that the last minute of the current day has 61 seconds
             * (Add one leap second to currentUtcOffset at the end of the day).
             */
            uint16_t leap61 : 1U;

            /**
             * Set the flag to indicate that the last minute of the current day has 59 seconds
             * (Subtract one leap second from currentUtcOffset at the end of the day).
             */
            uint16_t leap59                : 1U;
            uint16_t currentUtcOffsetValid : 1U; ///< The currentOffsetFromMaster is valid.
            uint16_t ptpTimescale          : 1U; ///< The PTP timescale is used.
            uint16_t timeTraceable         : 1U; ///< The timescale is traceable to a reference clock.
            uint16_t frequencyTraceable    : 1U; ///< The frequency is traceable to a reference clock.
            uint16_t                       : 2U; /* Reserved */
            uint16_t alternateMasterFlag   : 1U; ///< Indicates that the PTP message is transmitted from a PTP Port not in the MASTER state.
            uint16_t twoStep               : 1U; ///< Indicates that a Sync or a Pdelay_Resp message will be followed by a Follow_Up message.
            uint16_t unicast               : 1U; ///< Indicates that the PTP message is transmitted as a unicast PTP message.
            uint16_t                       : 2U; /* Reserved */
            uint16_t profileSpecific1      : 1U; ///< As defined by the applicable PTP Profile.
            uint16_t profileSpecific2      : 1U; ///< As defined by the applicable PTP Profile.
            uint16_t                       : 1U; /* Reserved */
        } value_b;
    };
} ptp_message_flags_t;

/** Commom PTP Message Header. */
typedef struct PTP_PACKED st_ptp_message_header
{
    uint8_t             message_type  : 4;    ///< The message type.
    uint8_t             sdoid_major   : 4;    ///< Standard Organization ID Major.
    uint8_t             version       : 4;    ///< PTP Version.
    uint8_t             minor_version : 4;    ///< PTP Minor Version.
    uint16_t            message_length;       ///< The total message length (Including the header).
    uint8_t             domain;               ///< The clock domain.
    uint8_t             sdoid_minor : 8;      ///< Standard Organization ID minor.
    ptp_message_flags_t flags;                ///< Flags set in the message.
    uint64_t            correction_field;     ///< Correction Field that is updated when a message passes through a transparent clock.
    uint32_t            reserved;             /* Reserved */
    uint8_t             clock_id[8];          ///< Clock ID that the message was sent from.
    uint16_t            source_port_id;       ///< Port ID that the message was sent from.
    uint16_t            sequence_id;          ///< Sequence ID of the message.
    ptp_ctrl_field_t    control_field;        ///< Control field (Message specifc).
    uint8_t             log_message_interval; ///< Logbase2 of the message period.
} ptp_message_header_t;

/** Sync Message Type (0x00). */
typedef struct PTP_PACKED st_ptp_message_sync
{
    ptp_time_t origin_timestamp;       ///< Timestamp when the message was transmitted.
} ptp_message_sync_t;

/** Delay_req Message Type (0x01). */
typedef ptp_message_sync_t ptp_message_delay_req_t;

/** PDelay_req Message Type (0x02). */
typedef struct PTP_PACKED st_ptp_message_pdelay_req
{
    ptp_time_t origin_timestamp;       ///< Timestamp when the message was transmitted.
    uint8_t    reserved[10];           /* Reserved */
} ptp_message_pdelay_req_t;

/** PDelay_resp Message Type (0x03). */
typedef struct PTP_PACKED st_ptp_message_pdelay_resp
{
    ptp_time_t origin_timestamp;         ///< Timestamp when the message was transmitted.
    uint8_t    source_port_identity[10]; ///< Clock ID + sourcePortId.
} ptp_message_pdelay_resp_t;

/** Follow_up Message Type (0x08). */
typedef ptp_message_sync_t ptp_message_follow_up_t;

/** Delay_resp Message Type (0x09). */
typedef ptp_message_pdelay_resp_t ptp_message_delay_resp_t;

/** PDelay_resp_follow_up Message Type (0x0A). */
typedef ptp_message_delay_resp_t ptp_message_pdelay_resp_follow_up_t;

/** Announce Message Type (0x0B). */
typedef struct PTP_PACKED st_ptp_message_announce
{
    ptp_time_t             origin_timestamp;   ///< Timestamp when the message was transmitted.
    uint16_t               current_utc_offset; ///< Offset from UTC in seconds.
    uint8_t                reserved;           /* Reserved */
    ptp_clock_properties_t clock_properties;   ///< Clock properties used in Best Master Clock Algorithm.
    uint8_t                clock_id[8];        ///< Clock ID that the message was sent from.
    uint16_t               steps_removed;      ///< The number of boundary clocks between the clock and the grand master clock.
    uint8_t                time_source;        ///< The source of time (Eg. INTERNAL_OSC).
} ptp_message_announce_t;

/** Signaling Message Type (0x0C). */
typedef struct PTP_PACKED st_ptp_message_signaling
{
    uint8_t  target_clock_id[8];       ///< ID of the target PTP instance.
    uint16_t target_port_id;           ///< Port of the target PTP instance.
} ptp_message_signaling_t;

/** Management Message Type (0x0D). */
typedef struct PTP_PACKED st_ptp_message_management
{
    uint8_t  target_clock_id[8];       ///< ID of the target PTP instance.
    uint16_t target_port_id;           ///< Port of the target PTP instance.
    uint8_t  starting_boundary_hops;   ///< The starting number of times the message is retransmitted by boundary clocks.
    uint8_t  boundary_hops;            ///< The remaining number of retransmissions.
    uint8_t  action;                   ///< The action that will be taken on reception of the message.
    uint8_t  reserved;                 /* Reserved */
} ptp_message_management_t;

/** Complete PTP Message. */
typedef struct PTP_PACKED st_ptp_message
{
    ptp_message_header_t header;                                  ///< Header of the message.
    union
    {
        ptp_message_announce_t              announce;             ///< Valid if this is an announce message.
        ptp_message_sync_t                  sync;                 ///< Valid if this is a sync message.
        ptp_message_follow_up_t             follow_up;            ///< Valid if this is an follow_up message.
        ptp_message_delay_req_t             delay_req;            ///< Valid if this is a delay_req message.
        ptp_message_delay_resp_t            delay_resp;           ///< Valid if this is a delay_resp message.
        ptp_message_pdelay_req_t            pdelay_req;           ///< Valid if this is a p_delay_req message.
        ptp_message_pdelay_resp_t           pdelay_resp;          ///< Valid if this is a p_delay_resp message.
        ptp_message_pdelay_resp_follow_up_t pdelay_resp_followup; ///< Valid if this is a p_delay_resp_follow_up message.
        ptp_message_signaling_t             signaling;            ///< Valid if this is a signaling message.
        ptp_message_management_t            management;           ///< Valid if this is a management message.
    };
} ptp_message_t;

/** Arguments passed to p_ptp_callback. */
typedef struct st_ptp_callback_args
{
    ptp_event_t           event;               ///< Event that caused the callback.
    ptp_message_t const * p_message;           ///< The message received (PTP message fields will be little endian).
    uint8_t const       * p_tlv_data;          ///< Start of TLV data (TLV data will be big endian).
    uint16_t              tlv_data_size;       ///< Total bytes of TLV data.
    uint32_t              pulse_timer_channel; ///< Channel of the pulse timer that caused @ref ptp_event_t::PTP_EVENT_PULSE_TIMER_MINT_RISING_EDGE
    void const          * p_context;           ///< Context value set in the configuration.
} ptp_callback_args_t;

/** Structure for configuring the IPLS IRQ settings that are common to all pulse timer channels. */
typedef struct s_ptp_pulse_timer_common_cfg
{
    ptp_enable_t ipls_rising_irq;             ///< Enable the IPLS IRQ when a rising edge is detected.
    ptp_enable_t ipls_falling_irq;            ///< Enable the IPLS IRQ when a falling edge is detected.
    ptp_enable_t ipls_rising_irq_auto_clear;  ///< Auto disable the rising edge IRQ after the first rising edge is detected.
    ptp_enable_t ipls_falling_irq_auto_clear; ///< Auto disable the falling edge IRQ after the first falling edge is detected.
} ptp_pulse_timer_common_cfg_t;

/** Structure for configuring a pulse timer channel. */
typedef struct st_ptp_pulse_timer_cfg
{
    ptp_time_t   start_time;                    ///< The exact time when the timer will start.
    uint32_t     period;                        ///< The period of the timer in nanoseconds.
    uint32_t     pulse;                         ///< The pulse width of the timer in nanoseconds.
    ptp_enable_t mint_rising_irq;               ///< Enable MINT rising edge IRQ.
    ptp_enable_t ipls_rising_event;             ///< Enable IPLS rising edge ELC event.
    ptp_enable_t ipls_falling_event;            ///< Enable IPLS falling edge ELC event.
    ptp_enable_t ipls_rising_event_auto_clear;  ///< Enable IPLS rising edge ELC event.
    ptp_enable_t ipls_falling_event_auto_clear; ///< Enable IPLS falling edge ELC event.
    ptp_enable_t ipls_irq_source;               ///< Enable using this channel as a source for the IPLS IRQ.
} ptp_pulse_timer_cfg_t;

/** Configuration settings for determining when the PTP clock is synchronized. */
typedef struct st_ptp_sync_state_cfg
{
    /** The maximum clock offset required to transition between synchronization states. */
    uint64_t threshold;

    /**
     * The number of times the clock must be above the threshold in order to transition
     * between synchronization states.
     */
    uint8_t count;
} ptp_sync_state_cfg_t;

/** Configuration settings for the SYNFP. */
typedef struct st_ptp_synfp_cfg
{
    ptp_ethernet_phy_interface_t ethernet_phy_interface; ///< The type of interface used to communicate with the PHY.
    ptp_frame_format_t           frame_format;           ///< Frame format used to transport PTP messages.
    ptp_frame_filter_mode_t      frame_filter;           ///< Frame filter mode.
    uint8_t                clock_domain;                 ///< Clock domain that the clock operates in.
    ptp_enable_t           clock_domain_filter;          ///< Filter out messages from other clock domains.
    ptp_message_interval_t announce_interval;            ///< Interval for transmitting announce messages.
    ptp_message_interval_t sync_interval;                ///< Interval for transmitting sync messages.
    ptp_message_interval_t delay_req_interval;           ///< Interval for transmitting delay_req messages.
    uint32_t               message_timeout;              ///< Timeout in milliseconds for receiving PTP messages.
    ptp_clock_properties_t clock_properties;             ///< Clock properties used in annonce messages.
    uint8_t                timesource;                   ///< TimeSource field used in announce messages.
    uint8_t              * p_multicast_addr_filter;      ///< Filter for multicast packets.

    /** Valid if frame_format is set to Ethernet II or IEEE 802.3. */
    struct
    {
        uint8_t * p_primary_mac_addr;  ///< The MAC address to send primary messages.
        uint8_t * p_pdelay_mac_addr;   ///< The MAC address to send p2p messages.
    } ether;

    /** Valid if frame_format is set to IPV4_UDP. */
    struct
    {
        uint32_t primary_ip_addr;      ///< The IP address to send primary messages.
        uint32_t pdelay_ip_addr;       ///< The IP address to send pdelay messages.
        uint8_t  event_tos;            ///< Type of service for event messages.
        uint8_t  general_tos;          ///< Type of service for general messages.
        uint8_t  primary_ttl;          ///< Time to live for primary messages.
        uint8_t  pdelay_ttl;           ///< Time to live for pdelay messages.
        uint16_t event_udp_port;       ///< The port to send event messages.
        uint16_t general_udp_port;     ///< The port to send general messages.
    } ipv4;
} ptp_synfp_cfg_t;

/** Configuration settings for the STCA. */
typedef struct st_ptp_stca_cfg
{
    ptp_stca_clock_freq_t       clock_freq;            ///< Select the clock frequency of the STCA.
    ptp_stca_clock_sel_t        clock_sel;             ///< Select the input clock to the STCA.
    ptp_clock_correction_mode_t clock_correction_mode; ///< Select the clock correction mode.
    uint8_t              gradient_worst10_interval;    ///< Select the interval for the gradient worst10 acquisition.
    ptp_sync_state_cfg_t sync_threshold;               ///< Configure the synchronization threshold.
    ptp_sync_state_cfg_t sync_loss_threshold;          ///< Configure the SYnchronization lost threshold.
} ptp_stca_cfg_t;

/** User configuration structure, used in open function */
typedef struct st_ptp_cfg
{
    ptp_synfp_cfg_t    synfp;            ///< Configuration settings for the SYNFP.
    ptp_stca_cfg_t     stca;             ///< Configuration settings for the STCA.
    edmac_instance_t * p_edmac_instance; ///< Pointer to PTP edmac instance.
    uint16_t           buffer_size;      ///< The maximum Ethernet packet size that can be transmitted or received.
    uint8_t         ** p_rx_buffers;     ///< Pointer to list of buffers used to receive PTP packets.
    uint8_t         ** p_tx_buffers;     ///< Pointer to list of buffers used to transmit PTP packets.
    IRQn_Type          mint_irq;         ///< Interrupt number for PTP event IRQ.
    IRQn_Type          ipls_irq;         ///< Interrupt number for PTP timer IRQ.
    uint8_t            mint_ipl;         ///< Interrupt priority of the PTP event IRQ.
    uint8_t            ipls_ipl;         ///< Interrupt priority of the PTP timer IRQ.

    /** Callback for handling received PTP events. */
    void (* p_callback)(ptp_callback_args_t * p_args);

    void const * p_context;
    void const * p_extend;
} ptp_cfg_t;

typedef void ptp_ctrl_t;

/** Timer API structure. General timer functions implemented at the HAL layer follow this API. */
typedef struct st_ptp_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_PTP_Open()
     *
     * @note To reconfigure after calling this function, call @ref ptp_api_t::close first.
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ptp_ctrl_t * const p_ctrl, ptp_cfg_t const * const p_cfg);

    /** Set the MAC address for the PTP.
     * @par Implemented as
     * - @ref R_PTP_MacAddrSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_hw_addr    Pointer to the 6 byte MAC address.
     */
    fsp_err_t (* macAddrSet)(ptp_ctrl_t * const p_ctrl, uint8_t const * const p_mac_addr);

    /** Set the IP address for the PTP.
     * @par Implemented as
     * - @ref R_PTP_IpAddrSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  ip_addr      32 bit IPv4 address of the PTP.
     */
    fsp_err_t (* ipAddrSet)(ptp_ctrl_t * const p_ctrl, uint32_t ip_addr);

    /** Set the local clock ID (Usually based off of the PTP MAC address).
     * @par Implemented as
     * - @ref R_PTP_LocalClockIdSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_clock_id   Pointer to 8 byte clock ID.
     */
    fsp_err_t (* localClockIdSet)(ptp_ctrl_t * const p_ctrl, uint8_t const * const p_clock_id);

    /** Set the master clock ID (Usually obtained from previously received announce message).
     * @par Implemented as
     * - @ref R_PTP_MasterClockIdSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_clock_id   Pointer to 8 byte clock ID.
     * @param[in]  port_id      The port on the master clock.
     */
    fsp_err_t (* masterClockIdSet)(ptp_ctrl_t * const p_ctrl, uint8_t const * const p_clock_id, uint16_t port_id);

    /** Set the flags field for the given message type.
     * @par Implemented as
     * - @ref R_PTP_MessageFlagsSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  message_type The message type.
     * @param[in]  flags        Flags to set.
     */
    fsp_err_t (* messageFlagsSet)(ptp_ctrl_t * const p_ctrl, ptp_message_type_t message_type,
                                  ptp_message_flags_t flags);

    /** Sets the offsetFromMaster field in announce messages.
     * @par Implemented as
     * - @ref R_PTP_CurrentUtcOffsetSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  offset       New currentUtcOffset value.
     */
    fsp_err_t (* currentUtcOffsetSet)(ptp_ctrl_t * const p_ctrl, uint16_t offset);

    /** Transition to a new clock state.
     *
     * @par Implemented as
     * - @ref R_PTP_PortStateSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  state        The state to transition into.
     */
    fsp_err_t (* portStateSet)(ptp_ctrl_t * const p_ctrl, uint32_t state);

    /** Send a PTP message. Appropriate fields in the PTP message will be endian swapped.
     * The application must ensure that the TLV data is in big endian format.
     *
     * @par Implemented as
     * - @ref R_PTP_MessageSend()
     *
     * @param[in]  p_ctrl        Pointer to control structure.
     * @param[in]  p_message     Pointer to a PTP message.
     * @param[in]  p_tlv_data    Pointer to TLV data that is appended to the end of the PTP message.
     * @param[in]  tlv_data_size Size of the TLV data in bytes.
     */
    fsp_err_t (* messageSend)(ptp_ctrl_t * const p_ctrl, ptp_message_t const * const p_message,
                              uint8_t const * const p_tlv_data, uint16_t tlv_data_size);

    /** Set the local clock value.
     *
     * @par Implemented as
     * - @ref R_PTP_LocalClockValueSet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_time       Pointer to the new time setting.
     */
    fsp_err_t (* localClockValueSet)(ptp_ctrl_t * const p_ctrl, ptp_time_t const * const p_time);

    /** Get the local clock value.
     *
     * @par Implemented as
     * - @ref R_PTP_LocalClockValueGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_time       Pointer to store the current time setting.
     */
    fsp_err_t (* localClockValueGet)(ptp_ctrl_t * const p_ctrl, ptp_time_t * const p_time);

    /** Configuration that is common to all of the pulse timers.
     *
     * @par Implemented as
     * - @ref R_PTP_PulseTimerCommonConfig()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_timer_cfg  Pointer to the pulse timer common configuration.
     */
    fsp_err_t (* pulseTimerCommonConfig)(ptp_ctrl_t * const p_ctrl, ptp_pulse_timer_common_cfg_t * p_timer_cfg);

    /** Setup a pulse timer.
     *
     * @par Implemented as
     * - @ref R_PTP_PulseTimerEnable()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  channel      The pulse timer channel to setup.
     * @param[in]  p_timer_cfg  Pointer to the pulse timer configuration.
     */
    fsp_err_t (* pulseTimerEnable)(ptp_ctrl_t * const p_ctrl, uint32_t channel,
                                   ptp_pulse_timer_cfg_t * const p_timer_cfg);

    /** Stop a pulse timer.
     *
     * @par Implemented as
     * - @ref R_PTP_PulseTimerDisable()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  channel      The pulse timer channel to stop.
     */
    fsp_err_t (* pulseTimerDisable)(ptp_ctrl_t * const p_ctrl, uint32_t channel);

    /** Stop PTP operation.
     *
     * @par Implemented as
     * - @ref R_PTP_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ptp_ctrl_t * const p_ctrl);
} ptp_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ptp_instance
{
    ptp_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    ptp_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    ptp_api_t const * p_api;           ///< Pointer to the API structure for this instance
} ptp_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end addtogroup PTP_API)
 **********************************************************************************************************************/
