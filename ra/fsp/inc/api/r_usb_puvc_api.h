/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_PUVC_API USB PUVC Interface
 * @brief Interface for USB PUVC functions.
 *
 * @section USB_PUVC_API_Summary Summary
 * The USB PUVC interface provides Peripheral USB Video Class functionality.
 *
 *
 * @{
 **********************************************************************************************************************/
#ifndef R_USB_PUVC_API_H
#define R_USB_PUVC_API_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* Video Class Requests IDs */
#define USB_PUVC_UNDEFINED                 (0x0000U)
#define USB_PUVC_SET_CUR                   (0x0100U)
#define USB_PUVC_GET_CUR                   (0x8100U)
#define USB_PUVC_GET_MIN                   (0x8200U)
#define USB_PUVC_GET_MAX                   (0x8300U)
#define USB_PUVC_GET_RES                   (0x8400U)
#define USB_PUVC_GET_LEN                   (0x8500U)
#define USB_PUVC_GET_INFO                  (0x8600U)
#define USB_PUVC_GET_DEF                   (0x8700U)

/* VideoStreaming (VS) Interface Control Selectors */
#define USB_PUVC_VS_CONTROL_UNDEFINED      (0x0000U)
#define USB_PUVC_VS_PROBE_CONTROL          (0x0100U)
#define USB_PUVC_VS_COMMIT_CONTROL         (0x0200U)

/*******************************************************************************
 * Typedef definitions
 *******************************************************************************/

/* Video Class Video Probe Control struct */
typedef struct st_usb_puvc_video_probe_control
{
    uint16_t    hint;                       ///< bmHint
    uint8_t     format_index;               ///< bFormatIndex
    uint8_t     frame_index;                ///< bFrameIndex
    uint32_t    frame_interval;             ///< dwFrameInterval
    uint16_t    key_frame_rate;             ///< wKeyFrameRate
    uint16_t    frame_rate;                 ///< wPFrameRate
    uint16_t    comp_quality;               ///< wCompQuality
    uint16_t    comp_windows_size;          ///< wCompWindowSize
    uint16_t    delay;                      ///< wDelay
    uint32_t    max_video_frame_size;       ///< dwMaxVideoFrameSize
    uint32_t    max_payload_transfer_size;  ///< dwMaxPayloadTransferSize
    uint32_t    clock_frequency;            ///< dwClockFrequency
    uint8_t     framing_info;               ///< bmFramingInfo
    uint8_t     prefered_version;           ///< bPreferedVersion
    uint8_t     min_version;                ///< bMinVersion
    uint8_t     max_version;                ///< bMaxVersion
} usb_puvc_video_probe_control_t;

/* Video Class Payload Header struct */
typedef struct st_usb_puvc_video_payload_header
{
    uint8_t     header_length;                                  ///< HLE (Header length field)
    uint8_t     bit_field_header;                               ///< BFH (Bit field header field)
    uint8_t     presentation_time[4];                           ///< PTS (Presentation Time Stamp)
    uint8_t     source_clock_reference_time[4];                 ///< D31..D0 of SCR (Source Clock Reference)
    uint8_t     source_clock_reference_sof_taken_counter[2];    ///< D42..D32 of SCR (Source Clock Reference)
} usb_puvc_video_payload_header_t;


/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_PUVC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PUVC_API)
 **********************************************************************************************************************/
