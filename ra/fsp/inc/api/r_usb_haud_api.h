/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_HAUD_API USB HAUD Interface
 * @brief Interface for USB HAUD functions.
 *
 * @section USB_HAUD_API_Summary Summary
 * The USB HAUD interface provides USB HAUD functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_HAUD_API_H
#define R_USB_HAUD_API_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
/* Audio Class main constants */
#define     USB_HAUD_SUBCLASS_UNDEFINED              0
#define     USB_HAUD_SUBCLASS_CONTROL                1
#define     USB_HAUD_SUBCLASS_STREAMING              2
#define     USB_HAUD_SUBCLASS_MIDI_STREAMING         3
#define     USB_HAUD_PROTOCOL_UNDEFINED              0
#define     USB_HAUD_PROTOCOL_IP_VERSION_01_00       0x00
#define     USB_HAUD_PROTOCOL_IP_VERSION_02_00       0x20

/* Audio Class main descriptor types */
#define     USB_HAUD_CS_INTERFACE                    0x24
#define     USB_HAUD_CS_ENDPOINT                     0x25

/* Audio10 */
/* Audio Class specific Audio Streaming interface descriptor subclasses */
#define     USB_HAUD_AUDIO10_CS_AS_UNDEFINED         0x00
#define     USB_HAUD_AUDIO10_CS_AS_GENERAL           0x01
#define     USB_HAUD_AUDIO10_CS_FORMAT_TYPE          0x02
#define     USB_HAUD_AUDIO10_CS_FORMAT_SPECIFIC      0x03

/* Audio Class Requests IDs */
#define     USB_HAUD_AUDIO10_REQUEST_CODE_UNDEFINED  (0x0000)
#define     USB_HAUD_AUDIO10_SET_CUR                 (0x0100)
#define     USB_HAUD_AUDIO10_GET_CUR                 (0x8100)
#define     USB_HAUD_AUDIO10_SET_MIN                 (0x0200)
#define     USB_HAUD_AUDIO10_GET_MIN                 (0x8200)
#define     USB_HAUD_AUDIO10_SET_MAX                 (0x0300)
#define     USB_HAUD_AUDIO10_GET_MAX                 (0x8300)
#define     USB_HAUD_AUDIO10_SET_RES                 (0x0400)
#define     USB_HAUD_AUDIO10_GET_RES                 (0x8400)
#define     USB_HAUD_AUDIO10_SET_MEM                 (0x0500)
#define     USB_HAUD_AUDIO10_GET_MEM                 (0x8500)
#define     USB_HAUD_AUDIO10_GET_STAT                (0xFF00)

/* Audio Class endpoint control selectors */
#define     USB_HAUD_AUDIO10_EP_CONTROL_UNDEFINED     (0x00)
#define     USB_HAUD_AUDIO10_EP_SAMPLING_FREQ_CONTROL (0x01)
#define     USB_HAUD_AUDIO10_EP_PITCH_CONTROL         (0x02)

/* Audio 1.0 Format Type Codes */
#define     USB_HAUD_AUDIO10_FORMAT_TYPE_UNDEFINED    0
#define     USB_HAUD_AUDIO10_FORMAT_TYPE_I            1
#define     USB_HAUD_AUDIO10_FORMAT_TYPE_II           2
#define     USB_HAUD_AUDIO10_FORMAT_TYPE_III          3

/* Audio 1.0 descriptor structs.  */
#define     USB_HAUD_AUDIO10_INTERFACE_DESCRIPTOR_LENGTH             8
#define     USB_HAUD_AUDIO10_INPUT_TERMINAL_DESCRIPTOR_LENGTH        12
#define     USB_HAUD_AUDIO10_OUTPUT_TERMINAL_DESCRIPTOR_LENGTH       9
#define     USB_HAUD_AUDIO10_FEATURE_UNIT_DESCRIPTOR_LENGTH          7
#define     USB_HAUD_AUDIO10_STREAMING_INTERFACE_DESCRIPTOR_LENGTH   6
#define     USB_HAUD_AUDIO10_STREAMING_ENDPOINT_DESCRIPTOR_LENGTH    6

/* Audio20 */
/* Audio Class Audio Streaming interface descriptor subclasses */
#define     USB_HAUD_AUDIO20_AS_UNDEFINED             (0x00)
#define     USB_HAUD_AUDIO20_AS_GENERAL               (0x01)
#define     USB_HAUD_AUDIO20_AS_FORMAT_TYPE           (0x02)
#define     USB_HAUD_AUDIO20_AS_ENCODER               (0x03)
#define     USB_HAUD_AUDIO20_AS_DECODER               (0x04)

/* Audio Class request codes */
#define     USB_HAUD_AUDIO20_REQUEST_CODE_UNDEFINED   (0x0000)
#define     USB_HAUD_AUDIO20_CUR                      (0x0100)
#define     USB_HAUD_AUDIO20_RANGE                    (0x0200)
#define     USB_HAUD_AUDIO20_MEM                      (0x0300)

/* Audio Class clock source control selectors */
#define     USB_HAUD_AUDIO20_CS_CONTROL_UNDEFINED     (0x00)
#define     USB_HAUD_AUDIO20_CS_SAM_FREQ_CONTROL      (0x01)
#define     USB_HAUD_AUDIO20_CS_CLOCK_VALID_CONTROL   (0x02)

/* Audio Class Audio Control interface descriptor subclasses */
#define     USB_HAUD_AUDIO20_AC_UNDEFINED             (0x00)
#define     USB_HAUD_AUDIO20_AC_HEADER                (0x01)
#define     USB_HAUD_AUDIO20_AC_INPUT_TERMINAL        (0x02)
#define     USB_HAUD_AUDIO20_AC_OUTPUT_TERMINAL       (0x03)
#define     USB_HAUD_AUDIO20_AC_MIXER_UNIT            (0x04)
#define     USB_HAUD_AUDIO20_AC_SELECTOR_UNIT         (0x05)
#define     USB_HAUD_AUDIO20_AC_FEATURE_UNIT          (0x06)
#define     USB_HAUD_AUDIO20_AC_EFFECT_UNIT           (0x07)
#define     USB_HAUD_AUDIO20_AC_PROCESSING_UNIT       (0x08)
#define     USB_HAUD_AUDIO20_AC_EXTENSION_UNIT        (0x09)
#define     USB_HAUD_AUDIO20_AC_CLOCK_SOURCE          (0x0A)
#define     USB_HAUD_AUDIO20_AC_CLOCK_SELECTOR        (0x0B)
#define     USB_HAUD_AUDIO20_AC_CLOCK_MULTIPLIER      (0x0C)
#define     USB_HAUD_AUDIO20_AC_SAMPLE_RATE_CONVERTER (0x0D)

/* Audio Class format type codes */
#define     USB_HAUD_AUDIO20_FORMAT_TYPE_UNDEFINED    (0x00)
#define     USB_HAUD_AUDIO20_FORMAT_TYPE_I            (0x01)
#define     USB_HAUD_AUDIO20_FORMAT_TYPE_II           (0x02)
#define     USB_HAUD_AUDIO20_FORMAT_TYPE_III          (0x03)
#define     USB_HAUD_AUDIO20_FORMAT_TYPE_IV           (0x04)
#define     USB_HAUD_AUDIO20_EXT_FORMAT_TYPE_I        (0x81)
#define     USB_HAUD_AUDIO20_EXT_FORMAT_TYPE_II       (0x82)
#define     USB_HAUD_AUDIO20_EXT_FORMAT_TYPE_III      (0x83)

/*****************************************************************************
 * Struct definition
 ******************************************************************************/

/** Sampling Frequency Settings */
typedef struct st_usb_haud_sampling
{
    uint32_t  channels;                ///< User Input Parameter : Number of channels
    uint32_t  frequency;               ///< User Input Parameter : Sampling frequency
    uint32_t  resolution;              ///< User Input Parameter : bits per sample

    uint8_t   frequency_setting;       ///< Whether the frequency needs to be set to device
    uint8_t   alternate_setting;       ///< Whether the ALT number is set

    uint32_t  found_channels;          ///< Set by HAUD Driver : [Audio20] Acquired channel number from Descriptor
    uint32_t  found_resolution;        ///< Set by HAUD Driver : [Audio20] Acquired resolution from Descriptor
    uint8_t * p_clock_source;          ///< Set by HAUD Driver : [Audio20] Pointer to Clock Source Descriptor (Audio2.0)
    uint32_t  clock_source_id;         ///< Set by HAUD Driver : [Audio20] Clock Source ID
    uint32_t  clock_numerator;         ///< Set by HAUD Driver : [Audio20] Clock Source numerator
    uint32_t  clock_denominator;       ///< Set by HAUD Driver : [Audio20] Clock Source denominator

    uint32_t  interface_number;        ///< Set by HAUD Driver : Interface number
    uint32_t  alternate_number;        ///< Set by HAUD Driver : Alternate number
    uint8_t * p_sampling_descriptor;   ///< Set by HAUD Driver : [Audio10] Pointer to Audio Streaming Format Type Descriptor (Audio1.0)
    uint16_t  max_packet_size;         ///< Set by HAUD Driver : Max Packet Size
    uint8_t   endpoint_address;        ///< Set by HAUD Driver : Endpoint Address
} usb_haud_sampling_t;

/** Audio protocol data */
typedef struct st_usb_haud_device_info
{
    uint8_t  protocol;                 ///< Protocol code
} usb_haud_device_info_t;

/*****************************************************************************
 * Typedef definitions
 ******************************************************************************/

/** USB HAUD functions implemented at the HAL layer will follow this API. */
typedef struct st_usb_haud_api
{
    /** Get connected device information.
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  p_info          Pointer to store Audio device information.
     * @param[in]  device_address  Device address.
     */
    fsp_err_t (* infoGet)(usb_ctrl_t * const p_ctrl, usb_haud_device_info_t * p_info, uint8_t device_address);

    /** Get clock source and related information.
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  p_info          Pointer to store Audio device information.
     * @param[in]  direction       Streaming data direction.
     * @param[in]  device_address  Device address.
     */
    fsp_err_t (* clockSourceGet)(usb_ctrl_t * const p_ctrl, usb_haud_sampling_t * p_info, uint8_t direction, uint8_t device_address);
    
    /** Get alternate number and related information.
     *
     * @param[in]  p_ctrl          Pointer to control structure.
     * @param[in]  p_info          Pointer to store Audio device information.
     * @param[in]  direction       Streaming data direction.
     * @param[in]  device_address  Device address.
     */
    fsp_err_t (* alternateNumberGet)(usb_ctrl_t * const p_ctrl, usb_haud_sampling_t * p_info, uint8_t direction, uint8_t device_address);

    /** Pipe Setting.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  interface_number Interface number used in SET_INTERFACE.
     * @param[in]  alternate_number Alternate number used in SET_INTERFACE.
     * @param[in]  device_address   Device address.
     */
    fsp_err_t (* pipeSet)(usb_ctrl_t * const p_ctrl, uint32_t interface_number, uint32_t alternate_number, uint8_t device_address);
} usb_haud_api_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_HAUD_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HAUD_API)
 **********************************************************************************************************************/
