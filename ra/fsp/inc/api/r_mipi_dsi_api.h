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
 * @defgroup MIPI_DSI_API MIPI DSI Interface
 * @brief Interface for MIPI DSI communications.
 *
 * @section MIPI_DSI_API_SUMMARY Summary
 * The MIPI DSI interface provides functionality involved with driving display panels over MIPI.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_MIPI_DSI_API_H
#define R_MIPI_DSI_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_mipi_dsi_cfg.h"

#include "r_mipi_phy.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** MIPI DSI packet Data Type (commands) - See MIPI specification for additional information */
typedef enum e_mipi_dsi_cmd_id
{
    MIPI_DSI_CMD_ID_V_SYNC_START = 0x01,                        ///< (Short) Sync Event, V Sync Start
    MIPI_DSI_CMD_ID_V_SYNC_END   = 0x11,                        ///< (Short) Sync Event, V Sync End
    MIPI_DSI_CMD_ID_H_SYNC_START = 0x21,                        ///< (Short) Sync Event, H Sync Start
    MIPI_DSI_CMD_ID_H_SYNC_END   = 0x31,                        ///< (Short) Sync Event, H Sync End

    MIPI_DSI_CMD_ID_COMPRESSION_MODE    = 0x07,                 ///< (Short) Compression Mode Command
    MIPI_DSI_CMD_ID_END_OF_TRANSMISSION = 0x08,                 ///< (Short) End of Transmission packet (EoTp)

    MIPI_DSI_CMD_ID_COLOR_MODE_OFF      = 0x02,                 ///< (Short) Color Mode (CM) Off Command
    MIPI_DSI_CMD_ID_COLOR_MODE_ON       = 0x12,                 ///< (Short) Color Mode (CM) On Command
    MIPI_DSI_CMD_ID_SHUTDOWN_PERIPHERAL = 0x22,                 ///< (Short) Shut Down Peripheral Command
    MIPI_DSI_CMD_ID_TURN_ON_PERIPHERAL  = 0x32,                 ///< (Short) Turn On Peripheral Command

    MIPI_DSI_CMD_ID_GENERIC_SHORT_WRITE_0_PARAM = 0x03,         ///< (Short) Generic Short WRITE, no parameters
    MIPI_DSI_CMD_ID_GENERIC_SHORT_WRITE_1_PARAM = 0x13,         ///< (Short) Generic Short WRITE, 1 parameter
    MIPI_DSI_CMD_ID_GENERIC_SHORT_WRITE_2_PARAM = 0x23,         ///< (Short) Generic Short WRITE, 2 parameters

    MIPI_DSI_CMD_ID_GENERIC_READ_REQUEST_0_PARAM = 0x04,        ///< (Short) Generic READ, no parameters
    MIPI_DSI_CMD_ID_GENERIC_READ_REQUEST_1_PARAM = 0x14,        ///< (Short) Generic READ, 1 parameter
    MIPI_DSI_CMD_ID_GENERIC_READ_REQUEST_2_PARAM = 0x24,        ///< (Short) Generic READ, 2 parameters

    MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_0_PARAM = 0x05,             ///< (Short) DCS Short WRITE, no parameters
    MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_1_PARAM = 0x15,             ///< (Short) DCS Short WRITE, 1 parameter

    MIPI_DSI_CMD_ID_DCS_READ      = 0x06,                       ///< (Short) DCS READ, no parameters
    MIPI_DSI_CMD_ID_EXECUTE_QUEUE = 0x16,                       ///< (Short) Execute Queue

    MIPI_DSI_CMD_ID_SET_MAXIMUM_RETURN_PACKET_SIZE = 0x37,      ///< (Short) Set Maximum Return Packet Size

    MIPI_DSI_CMD_ID_NULL_PACKET        = 0x09,                  ///< (Long) Null Packet, no data
    MIPI_DSI_CMD_ID_BLANKING_PACKET    = 0x19,                  ///< (Long) Blanking Packet, no data
    MIPI_DSI_CMD_ID_GENERIC_LONG_WRITE = 0x29,                  ///< (Long) Generic Long Write
    MIPI_DSI_CMD_ID_DCS_LONG_WRITE     = 0x39,                  ///< (Long) DCS Long Write/write_LUT Command Packet

    MIPI_DSI_CMD_ID_PICTURE_PARAMETER_SET   = 0x0A,             ///< (Long) Picture Parameter Set
    MIPI_DSI_CMD_ID_COMPRESSED_PIXEL_STREAM = 0x0B,             ///< (Long) Compressed Pixel Stream

    MIPI_DSI_CMD_ID_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20 = 0x0C, ///< (Long) Loosely Packed Pixel Stream, 20-bit YCbCr, 4:2:2 Format
    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_YCBCR24         = 0x1C, ///< (Long) Packed Pixel Stream, 24-bit YCbCr, 4:2:2 Format
    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_YCBCR16         = 0x2C, ///< (Long) Packed Pixel Stream, 16-bit YCbCr, 4:2:2 Format

    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_30      = 0x0D,         ///< (Long) Packed Pixel Stream, 30-bit RGB, 10-10-10 Format
    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_36      = 0x1D,         ///< (Long) Packed Pixel Stream, 36-bit RGB, 12-12-12 Format
    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_YCBCR12 = 0x3D,         ///< (Long) Packed Pixel Stream, 12-bit YCbCr, 4:2:0 Format

    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_16 = 0x0E,              ///< (Long) Packed Pixel Stream, 16-bit RGB, 5-6-5 Format
    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_18 = 0x1E,              ///< (Long) Packed Pixel Stream, 18-bit RGB, 6-6-6 Format
    MIPI_DSI_CMD_ID_LOOSELY_PACKED_PIXEL_STREAM_18  = 0x2E,     ///< (Long) Loosely Packed Pixel Stream, 18-bit RGB, 6-6-6 Format
    MIPI_DSI_CMD_ID_PACKED_PIXEL_STREAM_24 = 0x3E,              ///< (Long) Packed Pixel Stream, 24-bit RGB, 8-8-8 Format
} mipi_dsi_cmd_id_t;

/** MIPI DCS ID types - See MIPI DCS specification for additional information */
typedef enum e_mipi_dsi_dcs_id
{
    MIPI_DSI_DCS_ID_ENTER_IDLE_MODE         = 0x39, ///< Enter idle mode
    MIPI_DSI_DCS_ID_ENTER_INVERT_MODE       = 0x21, ///< Displayed image colors inverted
    MIPI_DSI_DCS_ID_ENTER_NORMAL_MODE       = 0x13, ///< Whole display area used for image
    MIPI_DSI_DCS_ID_ENTER_PARTIAL_MODE      = 0x12, ///< Part of display area used for image
    MIPI_DSI_DCS_ID_ENTER_SLEEP_MODE        = 0x10, ///< Power off the display panel
    MIPI_DSI_DCS_ID_EXIT_IDLE_MODE          = 0x38, ///< Full color depth used
    MIPI_DSI_DCS_ID_EXIT_INVERT_MODE        = 0x20, ///< Displayed image colors not inverted
    MIPI_DSI_DCS_ID_EXIT_SLEEP_MODE         = 0x11, ///< Power on the display panel
    MIPI_DSI_DCS_ID_GET_3D_CONTROL          = 0x3F, ///< Get display module 3D mode
    MIPI_DSI_DCS_ID_GET_ADDRESS_MODE        = 0x0B, ///< Get data order for transfers from host to the display device
    MIPI_DSI_DCS_ID_GET_BLUE_CHANNEL        = 0x08, ///< Get blue component of pixel at 0,0
    MIPI_DSI_DCS_ID_GET_CABC_MIN_BRIGHTNESS = 0x5F, ///< Get current minimum brightness level of the active CABC mode
    MIPI_DSI_DCS_ID_GET_COMPRESSION_MODE    = 0x03, ///< Get current compression mode
    MIPI_DSI_DCS_ID_GET_CONTROL_DISPLAY     = 0x54, ///< Get control display mode
    MIPI_DSI_DCS_ID_GET_DIAGNOSTIC_RESULT   = 0x0F, ///< Get peripheral self-diagnostic result
    MIPI_DSI_DCS_ID_GET_DISPLAY_BRIGHTNESS  = 0x52, ///< Get current display brightness level
    MIPI_DSI_DCS_ID_GET_DISPLAY_MODE        = 0x0D, ///< Get current display mode from the peripheral
    MIPI_DSI_DCS_ID_GET_DSI_MODE            = 0x70, ///< Get DSI operation mode
    MIPI_DSI_DCS_ID_GET_ERROR_COUNT_ON_DSI  = 0x05, ///< Get number of corrupted packets on DSI
    MIPI_DSI_DCS_ID_GET_GREEN_CHANNEL       = 0x07, ///< Get green component of pixel at 0,0
    MIPI_DSI_DCS_ID_GET_IMAGE_CHECKSUM_CT   = 0x15, ///< Returns checksum of frame of color-transformed pixel data
    MIPI_DSI_DCS_ID_GET_IMAGE_CHECKSUM_RGB  = 0x14, ///< Returns checksum of frame of RGB pixel data
    MIPI_DSI_DCS_ID_GET_PIXEL_FORMAT        = 0x0C, ///< Get current pixel format
    MIPI_DSI_DCS_ID_GET_POWER_MODE          = 0x0A, ///< Get current power mode
    MIPI_DSI_DCS_ID_GET_POWER_SAVE          = 0x56, ///< Get current power-save mode
    MIPI_DSI_DCS_ID_GET_RED_CHANNEL         = 0x06, ///< Get red component of pixel at 0,0
    MIPI_DSI_DCS_ID_GET_SCANLINE            = 0x45, ///< Get current scanline
    MIPI_DSI_DCS_ID_GET_SIGNAL_MODE         = 0x0E, ///< Get display module signaling mode
    MIPI_DSI_DCS_ID_NOP                     = 0x00, ///< No operation
    MIPI_DSI_DCS_ID_READ_ACMD               = 0x62, ///< Perform read access to the ACMD registers
    MIPI_DSI_DCS_ID_READ_DDB_CONTINUE       = 0xA8, ///< Continue reading the DDB from the last read location
    MIPI_DSI_DCS_ID_READ_DDB_START          = 0xA1, ///< Read the DDB from the provided location
    MIPI_DSI_DCS_ID_READ_DSE_MAILBOX        = 0x57, ///< Read access to the registers of the DSE read or write control mailbox
    MIPI_DSI_DCS_ID_READ_MEMORY_CONTINUE    = 0x3E, ///< Read image data from peripheral, continuing after last read
    MIPI_DSI_DCS_ID_READ_MEMORY_START       = 0x2E, ///< Read image data from the peripheral to the host
    MIPI_DSI_DCS_ID_READ_PPS_CONTINUE       = 0xA9, ///< Continue reading the specified length of PPS data
    MIPI_DSI_DCS_ID_READ_PPS_START          = 0xA2, ///< Read PPS data
    MIPI_DSI_DCS_ID_SET_3D_CONTROL          = 0x3D, ///< 3D is used on the display panel
    MIPI_DSI_DCS_ID_SET_ADDRESS_MODE        = 0x36, ///< Set data order for transfers from host to peripheral
    MIPI_DSI_DCS_ID_SET_ARP_OFF             = 0x60, ///< Disable ARP
    MIPI_DSI_DCS_ID_SET_ARP_ON              = 0x61, ///< Enable ARP and set T2 timer
    MIPI_DSI_DCS_ID_SET_CABC_MIN_BRIGHTNESS = 0x5E, ///< Set minimum brightness level for CABC mode
    MIPI_DSI_DCS_ID_SET_COLUMN_ADDRESS      = 0x2A, ///< Set column extent
    MIPI_DSI_DCS_ID_SET_DISPLAY_BRIGHTNESS  = 0x51, ///< Set display brightness level
    MIPI_DSI_DCS_ID_SET_DISPLAY_OFF         = 0x28, ///< Blank the display device
    MIPI_DSI_DCS_ID_SET_DISPLAY_ON          = 0x29, ///< Show image on display device
    MIPI_DSI_DCS_ID_SET_DSI_MODE            = 0x71, ///< Set DSI operation mode
    MIPI_DSI_DCS_ID_SET_GAMMA_CURVE         = 0x26, ///< Select gamma curve used by display
    MIPI_DSI_DCS_ID_SET_PAGE_ADDRESS        = 0x2B, ///< Set page extent
    MIPI_DSI_DCS_ID_SET_PARTIAL_COLUMNS     = 0x31, ///< Define the number of columns in the partial display area
    MIPI_DSI_DCS_ID_SET_PARTIAL_ROWS        = 0x30, ///< Define the number of rows in the partial display area
    MIPI_DSI_DCS_ID_SET_PIXEL_FORMAT        = 0x3A, ///< Define how many bits per pixel are used
    MIPI_DSI_DCS_ID_SET_SCROLL_AREA         = 0x33, ///< Define vertical scrolling and fixed area
    MIPI_DSI_DCS_ID_SET_SCROLL_START        = 0x37, ///< Define vertical scrolling starting point
    MIPI_DSI_DCS_ID_SET_TEAR_OFF            = 0x34, ///< Sync information not sent from the display module to the host
    MIPI_DSI_DCS_ID_SET_TEAR_ON             = 0x35, ///< Sync information is sent from the display module to the host
    MIPI_DSI_DCS_ID_SET_TEAR_SCANLINE       = 0x44, ///< Sync information is sent from display to the host when display refresh reaches profivided scan line
    MIPI_DSI_DCS_ID_SET_VSYNC_TIMING        = 0x40, ///< Set VSYNC timing to the specified length of PPS data
    MIPI_DSI_DCS_ID_SOFT_RESET              = 0x01, ///< Software reset
    MIPI_DSI_DCS_ID_WRITE_ACMD              = 0x63, ///< Write access to ACMD registers
    MIPI_DSI_DCS_ID_WRITE_CONTROL_DISPLAY   = 0x53, ///< Write control mode of display brightness
    MIPI_DSI_DCS_ID_WRITE_DSE_MAILBOX       = 0x58, ///< Write registers of DSE read or write control mailbox
    MIPI_DSI_DCS_ID_WRITE_LUT               = 0x2D, ///< Fill peripheral look-up table with provided data
    MIPI_DSI_DCS_ID_WRITE_MEMORY_CONTINUE   = 0x3C, ///< Continue image information transfer from last address
    MIPI_DSI_DCS_ID_WRITE_MEMORY_START      = 0x2C, ///< Transfer image information from host to peripheral
    MIPI_DSI_DCS_ID_WRITE_POWER_SAVE        = 0x55, ///< Writes power save mode
} mipi_dsi_dcs_id_t;

/** MIPI DSI Video Data type */
typedef enum e_mipi_dsi_video_data
{
    MIPI_DSI_VIDEO_DATA_16RGB_PIXEL_STREAM = 0x0E, ///< 16-bit RGB Packed Pixel Stream
    MIPI_DSI_VIDEO_DATA_18RGB_PIXEL_STREAM = 0x1E, ///< 18-bit RGB Packed Pixel Stream
    MIPI_DSI_VIDEO_DATA_24RGB_PIXEL_STREAM = 0x3E, ///< 24-bit RGB Packed Pixel Stream
} mipi_dsi_video_data_t;

/** MIPI DSI Acknowledge and Error type */
typedef enum e_mipi_dsi_ack_err
{
    MIPI_DSI_ACK_ERR_NONE                     = 0x0000, ///< No Errors
    MIPI_DSI_ACK_ERR_SOT_ERROR                = 0x0001, ///< SoT Error
    MIPI_DSI_ACK_ERR_SOT_SYNC_ERROR           = 0x0002, ///< SoT Sync Error
    MIPI_DSI_ACK_ERR_EOT_SYNC_ERROR           = 0x0004, ///< EoT Sync Error
    MIPI_DSI_ACK_ERR_ESCAPE_ENTRY_ERROR       = 0x0008, ///< Escape Mode Entry Error
    MIPI_DSI_ACK_ERR_LOW_POWER_SYNC_ERROR     = 0x0010, ///< Low-Power Transmit Sync Error
    MIPI_DSI_ACK_ERR_PERIPHERAL_TIMEOUT_ERROR = 0x0020, ///< Peripheral Timeout Error
    MIPI_DSI_ACK_ERR_FALSE_CONTROL_ERROR      = 0x0040, ///< False Control Error
    MIPI_DSI_ACK_ERR_CONTENTION_DETECTED      = 0x0080, ///< Contention Detected Error
    MIPI_DSI_ACK_ERR_ECC_SINGLE               = 0x0100, ///< ECC Error, single-bit
    MIPI_DSI_ACK_ERR_ECC_MULTI                = 0x0200, ///< ECC Error, multi-bit
    MIPI_DSI_ACK_ERR_CKSM_ERROR               = 0x0400, ///< Checksum Error (Long packet only)
    MIPI_DSI_ACK_ERR_DSI_DATA_ERROR           = 0x0800, ///< DSI Data Type Not Recognized
    MIPI_DSI_ACK_ERR_DSI_VC_ID_ERROR          = 0x1000, ///< DSI VC ID Invalid
    MIPI_DSI_ACK_ERR_INVALID_TX_LEN           = 0x2000, ///< Invalid Transmission Length
    MIPI_DSI_ACK_ERR_DSI_PROTOCOL_VIOLATION   = 0x8000, ///< DSI Protocol Violation
} mipi_dsi_ack_err_t;

/* MIPI DSI Virtual Channel ID Type*/
typedef enum e_mipi_dsi_vc
{
    MIPI_DSI_VC_NONE = 0x0,    ///< No channels selected
    MIPI_DSI_VC_0    = 0x1,    ///< Virtual channel 0
    MIPI_DSI_VC_1    = 0x2,    ///< Virtual channel 1
    MIPI_DSI_VC_2    = 0x4,    ///< Virtual channel 2
    MIPI_DSI_VC_3    = 0x8,    ///< Virtual channel 3
} mipi_dsi_vc_t;

/** MIPI DSI Message Flags */
typedef enum e_mipi_dsi_cmd_flag
{
    MIPI_DSI_CMD_FLAG_NONE                       = 0x00, ///< No flags
    MIPI_DSI_CMD_FLAG_BTA                        = 0x01, ///< Assert bus turnaround at end of transfer
    MIPI_DSI_CMD_FLAG_BTA_READ                   = 0x02, ///< Assert bus turnaround followed by read request (No WRITE request before BTA)
    MIPI_DSI_CMD_FLAG_BTA_NO_WRITE               = 0x03, ///< Immediately assert bus turnaround (No WRITE request before BTA)
    MIPI_DSI_CMD_FLAG_AUX_OPERATION              = 0x20, ///< Execute auxiliary operation command
    MIPI_DSI_CMD_FLAG_ACT_CODE_RESET_TRIGGER     = 0x20, ///< Send action code reset trigger message.
    MIPI_DSI_CMD_FLAG_ACT_CODE_INITIAL_SKEW_CAL  = 0x24, ///< Send action code initial skew calibration message.
    MIPI_DSI_CMD_FLAG_ACT_CODE_PERIODIC_SKEW_CAL = 0x25, ///< Send action code periodic skew message.
    MIPI_DSI_CMD_FLAG_ACT_CODE_NO_OPERATION      = 0x28, ///< Send action code NOOP message.
    MIPI_DSI_CMD_FLAG_LOW_POWER                  = 0x40, ///< Transmit in low-power mode
} mipi_dsi_cmd_flag_t;

/** MIPI DSI event codes */
typedef enum e_mipi_dsi_event
{
    MIPI_DSI_EVENT_SEQUENCE_0,         ///< Sequence 0 event (Low-Power)
    MIPI_DSI_EVENT_SEQUENCE_1,         ///< Sequence 1 event (High-Speed)
    MIPI_DSI_EVENT_VIDEO,              ///< Video event
    MIPI_DSI_EVENT_RECEIVE,            ///< Receive event
    MIPI_DSI_EVENT_FATAL,              ///< Fatal event
    MIPI_DSI_EVENT_PHY,                ///< Physical layer event

    /* Software triggered events - To allow application specific processing */
    MIPI_DSI_EVENT_POST_OPEN,          ///< Interface has been opened. Perform post-open application processing
    MIPI_DSI_EVENT_PRE_START,          ///< Video is about to start. Perform pre-video application processing
} mipi_dsi_event_t;

/** MIPI DSI Sequence status */
typedef enum e_mipi_dsi_sequence_status
{
    MIPI_DSI_SEQUENCE_STATUS_NONE                  = 0X00000000, ///< Sequence status not set
    MIPI_DSI_SEQUENCE_STATUS_RUNNING               = 0x00000004, ///< Sequence operation in progress
    MIPI_DSI_SEQUENCE_STATUS_ACTIONS_FINISHED      = 0x00000010, ///< All descriptor actions finished
    MIPI_DSI_SEQUENCE_STATUS_DESCRIPTORS_FINISHED  = 0x00000100, ///< All descriptors finished
    MIPI_DSI_SEQUENCE_STATUS_DESCRIPTOR_ABORT      = 0x00010000, ///< Descriptor abort interrupt
    MIPI_DSI_SEQUENCE_STATUS_SIZE_ERROR            = 0x00080000, ///< Packet size error
    MIPI_DSI_SEQUENCE_STATUS_TX_INTERNAL_BUS_ERROR = 0x01000000, ///< Tx internal bus error
    MIPI_DSI_SEQUENCE_STATUS_RX_FATAL_ERROR        = 0x04800000, ///< Receive fatal error
    MIPI_DSI_SEQUENCE_STATUS_RX_FAIL               = 0x08000000, ///< Receive fail
    MIPI_DSI_SEQUENCE_STATUS_RX_PACKET_DATA_FAIL   = 0x10000000, ///< Receive packet data fail
    MIPI_DSI_SEQUENCE_STATUS_RX_CORRECTABLE_ERROR  = 0x20000000, ///< Receive correctable error
    MIPI_DSI_SEQUENCE_STATUS_RX_ACK_AND_ERROR      = 0x40000000, ///< Receive acknowledge and error report
} mipi_dsi_sequence_status_t;

/** MIPI DSI video status errors */
typedef enum e_mipi_dsi_video_status
{
    MIPI_DSI_VIDEO_STATUS_NONE         = 0x00000000, ///< Video status not set
    MIPI_DSI_VIDEO_STATUS_START        = 0x00000001, ///< Video started event
    MIPI_DSI_VIDEO_STATUS_STOP         = 0x00000002, ///< Video stopped event
    MIPI_DSI_VIDEO_STATUS_RUNNING      = 0x00000004, ///< Video running status
    MIPI_DSI_VIDEO_STATUS_READY        = 0x00000008, ///< Video ready event
    MIPI_DSI_VIDEO_STATUS_TIMING_ERROR = 0x00100000, ///< Video timing error event
    MIPI_DSI_VIDEO_STATUS_UNDERFLOW    = 0x00400000, ///< Video buffer underflow event
    MIPI_DSI_VIDEO_STATUS_OVERFLOW     = 0x00800000, ///< Video buffer overflow event
} mipi_dsi_video_status_t;

/** MIPI DSI receive status errors */
typedef enum e_mipi_dsi_receive_status
{
    MIPI_DSI_RECEIVE_STATUS_NONE               = 0x00000000, ///< Receive status not set
    MIPI_DSI_RECEIVE_STATUS_BTA_REQUEST_END    = 0x00000001, ///< Receive BTA request end
    MIPI_DSI_RECEIVE_STATUS_LP_RX_HOST_TIMEOUT = 0x00000002, ///< Receive low power receive timeout
    MIPI_DSI_RECEIVE_STATUS_BTA_ACK_TIMEOUT    = 0x00000004, ///< Receive BTA ack timeout
    MIPI_DSI_RECEIVE_STATUS_RESPONSE_PACKET    = 0x00000100, ///< Receive response
    MIPI_DSI_RECEIVE_STATUS_EOTP               = 0x00000400, ///< Receive end of transmission packet
    MIPI_DSI_RECEIVE_STATUS_TEARING_TRIGGER    = 0x00002000, ///< Receive tearing trigger
    MIPI_DSI_RECEIVE_STATUS_ACK_TRIGGER        = 0x00004000, ///< Receive ack trigger
    MIPI_DSI_RECEIVE_STATUS_TEARING_DETECT     = 0x00008000, ///< Receive tearing detect
    MIPI_DSI_RECEIVE_STATUS_MALFORM_ERROR      = 0x00010000, ///< Receive malform error
    MIPI_DSI_RECEIVE_STATUS_ECC_MULTI          = 0x00020000, ///< Receive ecc multi-bit error
    MIPI_DSI_RECEIVE_STATUS_UNEXPECTED_PACKET  = 0x00040000, ///< Receive unexpected packet
    MIPI_DSI_RECEIVE_STATUS_WORD_COUNT         = 0x00100000, ///< Receive word count
    MIPI_DSI_RECEIVE_STATUS_CRC                = 0x00200000, ///< Receive crc error
    MIPI_DSI_RECEIVE_STATUS_INTERNAL_BUS       = 0x00400000, ///< Receive internal bus error
    MIPI_DSI_RECEIVE_STATUS_BUFFER_OVERFLOW    = 0x00800000, ///< Receive buffer overflow
    MIPI_DSI_RECEIVE_STATUS_TIMEOUT            = 0x01000000, ///< Receive timeout
    MIPI_DSI_RECEIVE_STATUS_NO_RESPONSE        = 0x02000000, ///< Receive no response
    MIPI_DSI_RECEIVE_STATUS_PACKET_SIZE        = 0x04000000, ///< Receive packet size error
    MIPI_DSI_RECEIVE_STATUS_ECC_SINGLE         = 0x10000000, ///< Receive ecc single bit error
    MIPI_DSI_RECEIVE_STATUS_ACK_AND_ERROR      = 0x40000000, ///< Receive ack and error
} mipi_dsi_receive_status_t;

/** MIPI DSI fatal status errors */
typedef enum e_mipi_dsi_fatal_status
{
    MIPI_DSI_FATAL_STATUS_NONE                  = 0x00000000, ///< Fatal status not set
    MIPI_DSI_FATAL_STATUS_HS_TX_TIMEOUT         = 0x00000001, ///< Fatal high speed transmit timeout
    MIPI_DSI_FATAL_STATUS_LP_RX_TIMEOUT         = 0x00000002, ///< Fatal low power receive timeout
    MIPI_DSI_FATAL_STATUS_BTA_ACK_TIMEOUT       = 0x00000004, ///< Fatal BTA ack timeout
    MIPI_DSI_FATAL_STATUS_ESCAPE_ENTRY_ERROR    = 0x00010000, ///< Fatal escape mode entry error
    MIPI_DSI_FATAL_STATUS_LPDT_SYNC_ERROR       = 0x00020000, ///< Fatal low power data transmission synchronization error
    MIPI_DSI_FATAL_STATUS_CTRL_ERROR            = 0x00040000, ///< Fatal control error
    MIPI_DSI_FATAL_STATUS_LP0_CONTENTION_DETECT = 0x00080000, ///< Fatal lane 0 low power contention detect
    MIPI_DSI_FATAL_STATUS_LP1_CONTENTION_DETECT = 0x00100000, ///< Fatal lane 1 low power contention detect
    MIPI_DSI_FATAL_STATUS_LP0_CONTENTION        = 0x80000000, ///< Fatal lane 0 low power contention status
    MIPI_DSI_FATAL_STATUS_LP1_CONTENTION        = 0x10000000, ///< Fatal lane 1 low power contention status
} mipi_dsi_fatal_status_t;

/** MIPI DSI physical lane status */
typedef enum e_mipi_dsi_phy_status
{
    MIPI_DSI_PHY_STATUS_NONE                 = 0x00000000, ///< Physical lane status not set
    MIPI_DSI_PHY_STATUS_ULP_NOT_ACTIVE       = 0x00000001, ///< Physical lane ULP not active
    MIPI_DSI_PHY_STATUS_CLOCK_LANE_STOP      = 0x00000002, ///< Clock lane in stopped state
    MIPI_DSI_PHY_STATUS_DATA_LANE0_LP_RX     = 0x00000004, ///< Data lane low power receive mode
    MIPI_DSI_PHY_STATUS_DATA_LANE0_ULP_RX    = 0x00000008, ///< Data lane ultra low power receive mode
    MIPI_DSI_PHY_STATUS_DATA_LANE0_NOT_ULP   = 0x00000010, ///< Data lane 0 not in ULP mode
    MIPI_DSI_PHY_STATUS_DATA_LANE1_NOT_ULP   = 0x00000020, ///< Data lane 1 not in ULP mode
    MIPI_DSI_PHY_STATUS_DATA_LANE0_STOP      = 0x00000100, ///< Data lane 0 stop state
    MIPI_DSI_PHY_STATUS_DATA_LANE1_STOP      = 0x00000200, ///< Data lane 1 stop state
    MIPI_DSI_PHY_STATUS_DATA_LANE0_RX_TO_TX  = 0x00001000, ///< Data lane Rx to Tx transition event
    MIPI_DSI_PHY_STATUS_DATA_LANE0_TX_TO_RX  = 0x00002000, ///< Data lane Tx to Rx transition event
    MIPI_DSI_PHY_STATUS_DATA_LANE0_RX_STATE  = 0x00008000, ///< Data lane Rx active state
    MIPI_DSI_PHY_STATUS_CLOCK_ULPS_ENTER     = 0x01000000, ///< Clock lane ULPS enter event
    MIPI_DSI_PHY_STATUS_CLOCK_ULPS_EXIT      = 0x02000000, ///< Clock lane ULPS exit event
    MIPI_DSI_PHY_STATUS_CLOCK_LP_TO_HS       = 0x04000000, ///< Clock lane LP to HS transition event
    MIPI_DSI_PHY_STATUS_CLOCK_HS_TO_LP       = 0x08000000, ///< Clock lane HS to LP transition event
    MIPI_DSI_PHY_STATUS_DATA_LANE_ULPS_ENTER = 0x10000000, ///< Data lane ULPS enter event
    MIPI_DSI_PHY_STATUS_DATA_LANE_ULPS_EXIT  = 0x20000000, ///< Data lane ULPS exit event
} mipi_dsi_phy_status_t;

/** MIPI DSI link status bits */
typedef enum e_mipi_dsi_link_status
{
    MIPI_DSI_LINK_STATUS_IDLE          = 0x0000, ///< Link idle or uninitialized
    MIPI_DSI_LINK_STATUS_CH0_RUNNING   = 0x0001, ///< Channel 0 running
    MIPI_DSI_LINK_STATUS_CH1_RUNNING   = 0x0010, ///< Channel 1 running
    MIPI_DSI_LINK_STATUS_VIDEO_RUNNING = 0x0100, ///< Video output running
    MIPI_DSI_LINK_STATUS_HP_MODE_BUSY  = 0x1000, ///< HP operation busy
    MIPI_DSI_LINK_STATUS_LP_MODE_BUSY  = 0x2000, ///< LP operation busy
} mipi_dsi_link_status_t;

/** MIPI DSI Lane Type */
typedef enum e_mipi_dsi_lane
{
    MIPI_DSI_LANE_CLOCK    = 0x01,     ///< Clock Lanes
    MIPI_DSI_LANE_DATA_ALL = 0x02,     ///< All Data Lanes
} mipi_dsi_lane_t;

/** MIPI DSI Command */
typedef struct st_mipi_dsi_cmd
{
    uint8_t              channel;      ///< Virtual Channel ID
    mipi_dsi_cmd_id_t    cmd_id;       ///< Message ID
    mipi_dsi_cmd_flag_t  flags;        ///< Flags controlling this message transition
    uint16_t             tx_len;       ///< Transmit buffer size
    const uint8_t      * p_tx_buffer;  ///< Transmit buffer pointer
    const uint8_t      * p_rx_buffer;  ///< Receive buffer pointer
} mipi_dsi_cmd_t;

/** MIPI DSI Acknowledge and Error status type */
typedef union st_mipi_dsi_ack_err_status_t
{
    __PACKED_STRUCT
    {
        mipi_dsi_ack_err_t error_report    : 16; ///< Error report bits
        mipi_dsi_vc_t      virtual_channel : 4;  ///< Virtual Channel ID
        uint32_t                           : 12; // Padding
    };
    uint32_t bits;
} mipi_dsi_ack_err_status_t;

/** MIPI DSI status type */
typedef struct st_mipi_dsi_status_t
{
    mipi_dsi_link_status_t    link_status;         ///< Link status
    mipi_dsi_ack_err_status_t ack_err_latest;      ///< Latest Acknowledge and Error Report Packet Latest Info
    mipi_dsi_ack_err_status_t ack_err_accumulated; ///< Accumulated Acknowledge and Error Report Packet Latest Info
} mipi_dsi_status_t;

/** MIPI DSI Result */
typedef __PACKED_STRUCT st_mipi_dsi_result
{
    uint8_t           data[2];                  ///< Data of received packet header
    mipi_dsi_cmd_id_t cmd_id               : 6; ///< Data type
    uint8_t           virtual_channel_id   : 2; ///< Virtual channel ID
    uint8_t           long_packet          : 1; ///< Sort packet (0) or Long packet (1)
    uint8_t           rx_success           : 1; ///< Response packet or ack trigger received
    uint8_t           timeout              : 1; ///< Fatal timeout error
    uint8_t           rx_fail              : 1; ///< Expected receive not done
    uint8_t           rx_data_fail         : 1; ///< Receive packet data fail
    uint8_t           rx_correctable_error : 1; ///< Correctable error detected
    uint8_t           rx_ack_err           : 1; ///< Rx acknowledge and error report packet received
    uint8_t           info_overwrite       : 1; ///< This information was overwritten
} mipi_dsi_receive_result_t;

/** MIPI DSI callback parameter definition */
typedef struct st_mipi_dsi_callback_args
{
    mipi_dsi_event_t event;                      ///< Event code
    union
    {
        mipi_dsi_sequence_status_t tx_status;    ///< Sequence status
        mipi_dsi_receive_status_t  rx_status;    ///< Receive status
        mipi_dsi_fatal_status_t    fatal_status; ///< Fatal status
        mipi_dsi_video_status_t    video_status; ///< Video status
        mipi_dsi_phy_status_t      phy_status;   ///< Phy Status
    };
    mipi_dsi_receive_result_t * p_result;        ///< Receive result pointer
    void const                * p_context;       ///< Context provided to user during callback
} mipi_dsi_callback_args_t;

/** MIPI DSI transition timing */
typedef struct st_mipi_dsi_timing
{
    uint32_t clock_stop_time;          ///< Clock stop time
    uint32_t clock_beforehand_time;    ///< Clock beforehand time
    uint32_t clock_keep_time;          ///< Clock Keep time
    uint32_t go_lp_and_back;           ///< Go LP and Back time
} mipi_dsi_timing_t;

/** MIPI DSI main configuration structure */
typedef struct st_mipi_dsi_cfg
{
    mipi_phy_instance_t const * p_mipi_phy_instance;        ///< Pointer to mipi physical layer instance

    mipi_dsi_timing_t const * p_timing;                     ///< Pointer to MIPI DSI timing configuration

    bool                  hsa_no_lp;                        ///< Suppress the transition to LP during HSA period and keep HS
    bool                  hbp_no_lp;                        ///< Suppress the transition to LP during HBP period and keep HS
    bool                  hfp_no_lp;                        ///< Suppress the transition to LP during HFP period and keep HS
    uint8_t               num_lanes;                        ///< Number of MIPI lanes to use.
    uint8_t               ulps_wakeup_period;               ///< ULPS wakeup period
    uint8_t               continuous_clock;                 ///< Always run HS clock on/off
    uint32_t              hs_tx_timeout;                    ///< HS-Tx Timeout value
    uint32_t              lp_rx_timeout;                    ///< LP-Rx host processor timeout
    uint32_t              turnaround_timeout;               ///< Turnaround Acknowledge Timeout
    uint32_t              bta_timeout;                      ///< Peripheral Response Timeout
    uint32_t              lprw_timeout;                     ///< LP Read and Write Timeouts
    uint32_t              hsrw_timeout;                     ///< HS Read and Write Timeouts
    uint32_t              max_return_packet_size;           ///< Maximum return packet size
    bool                  ecc_enable;                       ///< ECC Check enable
    mipi_dsi_vc_t         crc_check_mask;                   ///< Virtual channel CRC check enable
    bool                  scramble_enable;                  ///< Scramble on/off
    bool                  tearing_detect;                   ///< External tearing effect detection mode (0:rising, 1:falling edge)
    bool                  eotp_enable;                      ///< End of Transmit Packet (EoTP) on/off
    bool                  sync_pulse;                       ///< Enable for Non-Burst Mode with Sync Pulse sequence
    mipi_dsi_video_data_t data_type;                        ///< Video mode data type: 16-bit RGB, 18-bit RGB, 24-bit RGB
    uint8_t               virtual_channel_id;               ///< Video mode virtual channel to use (from 0x0 to 0x3)
    uint32_t              vertical_sync_lines;              ///< Number of vertical sync active lines
    bool                  vertical_sync_polarity;           ///< V-Sync Polarity
    uint32_t              vertical_active_lines;            ///< Number of vertical active lines
    uint32_t              vertical_back_porch;              ///< Vertical back porch
    uint32_t              vertical_front_porch;             ///< Vertical front porch
    uint32_t              horizontal_sync_lines;            ///< Number of horizontal sync active lines
    bool                  horizontal_sync_polarity;         ///< H-Sync Polarity
    uint32_t              horizontal_active_lines;          ///< Number of horizontal active lines
    uint32_t              horizontal_back_porch;            ///< Horizontal back porch
    uint32_t              horizontal_front_porch;           ///< Horizontal front porch
    uint32_t              video_mode_delay;

    /** Callback configuration */
    void (* p_callback)(mipi_dsi_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                                 ///< User defined context passed into callback function

    /** Pointer to display peripheral specific configuration */
    void const * p_extend;                                  ///< MIPI hardware dependent configuration
} mipi_dsi_cfg_t;

/** MIPI DSI control block. Allocate an instance specific control block to pass into the MIPI DSI API calls. */
typedef void mipi_dsi_ctrl_t;

/** Shared Interface definition for MIPI DSI peripheral */
typedef struct st_mipi_dsi_api
{
    /** Open MIPI DSI device.
     *
     * @param[in,out]  p_ctrl   Pointer to MIPI DSI interface control block. Must be declared by user. Value set here.
     * @param[in]      p_cfg    Pointer to MIPI DSI configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(mipi_dsi_ctrl_t * const p_ctrl, mipi_dsi_cfg_t const * const p_cfg);

    /** Close MIPI DSI device.
     *
     * @param[in]     p_ctrl   Pointer to MIPI DSI interface control block.
     */
    fsp_err_t (* close)(mipi_dsi_ctrl_t * const p_ctrl);

    /** Start pixel data output.
     *
     * @param[in]     p_ctrl   Pointer to MIPI DSI interface control block.
     */
    fsp_err_t (* start)(mipi_dsi_ctrl_t * const p_ctrl);

    /** Stop pixel data output.
     *
     * @param[in]     p_ctrl   Pointer to MIPI DSI interface control block.
     */
    fsp_err_t (* stop)(mipi_dsi_ctrl_t * const p_ctrl);

    /** Enter Ultra-low Power State (ULPS).
     *
     * @param[in]   p_ctrl     Pointer to MIPI DSI interface control block.
     * @param[in]   lane       Physical lane(s) to transition into ULPS
     */
    fsp_err_t (* ulpsEnter)(mipi_dsi_ctrl_t * const p_ctrl, mipi_dsi_lane_t lane);

    /** Exit Ultra-low Power State (ULPS).
     *
     * @param[in]   p_ctrl     Pointer to MIPI DSI interface control block.
     * @param[in]   lane       Physical lane(s) to transition from ULPS
     */
    fsp_err_t (* ulpsExit)(mipi_dsi_ctrl_t * const p_ctrl, mipi_dsi_lane_t lane);

    /** Send a command to the display.
     *
     * @param[in]   p_ctrl     Pointer to MIPI DSI interface control block.
     * @param[in]   p_cmd      Pointer to a command structure
     */
    fsp_err_t (* command)(mipi_dsi_ctrl_t * const p_api_ctrl, mipi_dsi_cmd_t * p_cmd);

    /** Get status of MIPI link.
     *
     * @param[in]   p_ctrl     Pointer to MIPI DSI interface control block.
     * @param[in]   p_status   Pointer to MIPI DSI interface status structure.
     */
    fsp_err_t (* statusGet)(mipi_dsi_ctrl_t * const p_ctrl, mipi_dsi_status_t * p_status);
} mipi_dsi_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_mipi_dsi_instance
{
    mipi_dsi_ctrl_t      * p_ctrl;     ///< Pointer to the control structure for this instance
    mipi_dsi_cfg_t const * p_cfg;      ///< Pointer to the configuration structure for this instance
    mipi_dsi_api_t const * p_api;      ///< Pointer to the API structure for this instance
} mipi_dsi_instance_t;

/* @} (end defgroup MIPI_DSI_API) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
