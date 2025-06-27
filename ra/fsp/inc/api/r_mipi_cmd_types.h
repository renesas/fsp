/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_GRAPHICS_INTERFACES
 * @defgroup MIPI_CMD_TYPES MIPI CMD Data Types
 * @brief Common data types for MIPI CSI and DSI communication interfaces.
 *
 * @section MIPI_CMD_TYPES_SUMMARY Summary
 * The MIPI CMD interface provides functionality involved with driving display panels over MIPI.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_MIPI_CMD_TYPES_H
#define R_MIPI_CMD_TYPES_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** MIPI CMD packet Data Type (commands) - See MIPI specification for additional information */
typedef enum e_mipi_cmd_id
{
    MIPI_CMD_ID_V_SYNC_START = 0x01,                        ///< (Short) Sync Event, V Sync Start
    MIPI_CMD_ID_V_SYNC_END   = 0x11,                        ///< (Short) Sync Event, V Sync End
    MIPI_CMD_ID_H_SYNC_START = 0x21,                        ///< (Short) Sync Event, H Sync Start
    MIPI_CMD_ID_H_SYNC_END   = 0x31,                        ///< (Short) Sync Event, H Sync End

    MIPI_CMD_ID_COMPRESSION_MODE    = 0x07,                 ///< (Short) Compression Mode Command
    MIPI_CMD_ID_END_OF_TRANSMISSION = 0x08,                 ///< (Short) End of Transmission packet (EoTp)

    MIPI_CMD_ID_COLOR_MODE_OFF      = 0x02,                 ///< (Short) Color Mode (CM) Off Command
    MIPI_CMD_ID_COLOR_MODE_ON       = 0x12,                 ///< (Short) Color Mode (CM) On Command
    MIPI_CMD_ID_SHUTDOWN_PERIPHERAL = 0x22,                 ///< (Short) Shut Down Peripheral Command
    MIPI_CMD_ID_TURN_ON_PERIPHERAL  = 0x32,                 ///< (Short) Turn On Peripheral Command

    MIPI_CMD_ID_GENERIC_SHORT_WRITE_0_PARAM = 0x03,         ///< (Short) Generic Short WRITE, no parameters
    MIPI_CMD_ID_GENERIC_SHORT_WRITE_1_PARAM = 0x13,         ///< (Short) Generic Short WRITE, 1 parameter
    MIPI_CMD_ID_GENERIC_SHORT_WRITE_2_PARAM = 0x23,         ///< (Short) Generic Short WRITE, 2 parameters

    MIPI_CMD_ID_GENERIC_READ_REQUEST_0_PARAM = 0x04,        ///< (Short) Generic READ, no parameters
    MIPI_CMD_ID_GENERIC_READ_REQUEST_1_PARAM = 0x14,        ///< (Short) Generic READ, 1 parameter
    MIPI_CMD_ID_GENERIC_READ_REQUEST_2_PARAM = 0x24,        ///< (Short) Generic READ, 2 parameters

    MIPI_CMD_ID_DCS_SHORT_WRITE_0_PARAM = 0x05,             ///< (Short) DCS Short WRITE, no parameters
    MIPI_CMD_ID_DCS_SHORT_WRITE_1_PARAM = 0x15,             ///< (Short) DCS Short WRITE, 1 parameter

    MIPI_CMD_ID_DCS_READ      = 0x06,                       ///< (Short) DCS READ, no parameters
    MIPI_CMD_ID_EXECUTE_QUEUE = 0x16,                       ///< (Short) Execute Queue

    MIPI_CMD_ID_SET_MAXIMUM_RETURN_PACKET_SIZE = 0x37,      ///< (Short) Set Maximum Return Packet Size

    MIPI_CMD_ID_NULL_PACKET        = 0x09,                  ///< (Long) Null Packet, no data
    MIPI_CMD_ID_BLANKING_PACKET    = 0x19,                  ///< (Long) Blanking Packet, no data
    MIPI_CMD_ID_GENERIC_LONG_WRITE = 0x29,                  ///< (Long) Generic Long Write
    MIPI_CMD_ID_DCS_LONG_WRITE     = 0x39,                  ///< (Long) DCS Long Write/write_LUT Command Packet

    MIPI_CMD_ID_PICTURE_PARAMETER_SET   = 0x0A,             ///< (Long) Picture Parameter Set
    MIPI_CMD_ID_COMPRESSED_PIXEL_STREAM = 0x0B,             ///< (Long) Compressed Pixel Stream

    MIPI_CMD_ID_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20 = 0x0C, ///< (Long) Loosely Packed Pixel Stream, 20-bit YCbCr, 4:2:2 Format
    MIPI_CMD_ID_PACKED_PIXEL_STREAM_YCBCR24         = 0x1C, ///< (Long) Packed Pixel Stream, 24-bit YCbCr, 4:2:2 Format
    MIPI_CMD_ID_PACKED_PIXEL_STREAM_YCBCR16         = 0x2C, ///< (Long) Packed Pixel Stream, 16-bit YCbCr, 4:2:2 Format

    MIPI_CMD_ID_PACKED_PIXEL_STREAM_30      = 0x0D,         ///< (Long) Packed Pixel Stream, 30-bit RGB, 10-10-10 Format
    MIPI_CMD_ID_PACKED_PIXEL_STREAM_36      = 0x1D,         ///< (Long) Packed Pixel Stream, 36-bit RGB, 12-12-12 Format
    MIPI_CMD_ID_PACKED_PIXEL_STREAM_YCBCR12 = 0x3D,         ///< (Long) Packed Pixel Stream, 12-bit YCbCr, 4:2:0 Format

    MIPI_CMD_ID_PACKED_PIXEL_STREAM_16         = 0x0E,      ///< (Long) Packed Pixel Stream, 16-bit RGB, 5-6-5 Format
    MIPI_CMD_ID_PACKED_PIXEL_STREAM_18         = 0x1E,      ///< (Long) Packed Pixel Stream, 18-bit RGB, 6-6-6 Format
    MIPI_CMD_ID_LOOSELY_PACKED_PIXEL_STREAM_18 = 0x2E,      ///< (Long) Loosely Packed Pixel Stream, 18-bit RGB, 6-6-6 Format
    MIPI_CMD_ID_PACKED_PIXEL_STREAM_24         = 0x3E,      ///< (Long) Packed Pixel Stream, 24-bit RGB, 8-8-8 Format
} mipi_cmd_id_t;

/* @} (end defgroup MIPI_CMD_TYPES) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
