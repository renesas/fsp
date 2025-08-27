/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_PAUD_API USB PAUD Interface
 * @brief Interface for USB PAUD functions.
 *
 * @section USB_PAUD_API_Summary Summary
 * The USB PAUD interface provides USB PAUD functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_PAUD_API_H
#define R_USB_PAUD_API_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_basic_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* Audio Class Requests IDs (Audio 2.0) */
#define USB_PAUD_CUR                       (0x0100U) ///< CUR Request
#define USB_PAUD_RANGE                     (0x0200U) ///< RANGE Request

/* Audio Class Requests IDs (Audio 1.0) */
#define USB_PAUD_SET_CUR                   (0x0100U) ///< SET_CUR Request
#define USB_PAUD_GET_CUR                   (0x8100U) ///< GET_CUR Request
#define USB_PAUD_GET_MIN                   (0x8200U) ///< GET_MIN Request
#define USB_PAUD_GET_MAX                   (0x8300U) ///< GET_MAX Request
#define USB_PAUD_GET_RES                   (0x8400U) ///< GET_RES Request

#define USB_PAUD_MUTE_CONTROL              (0x0100U) ///< Mute Control in Feature Unit
#define USB_PAUD_VOLUME_CONTROL            (0x0200U) ///< Volume Control in Feature Unit
#define USB_PAUD_CLOCK_FREQUENCY_CONTROL   (0x0100U) ///< Clock Frequency Control

/*******************************************************************************
 * Typedef definitions
 *******************************************************************************/

/** Audio Control Settings */
typedef struct st_usb_paud_audio_control
{
    union
    {
        uint32_t    ep_addr;        ///< Endpoint Address (bEndpointAddress of Endpoint Descriptor)
        uint32_t    cs_id;          ///< Control Selector ID
    };
    uint32_t        sam_freq;       ///< Sampling Frequency
    uint32_t        fu_id;          ///< Feature Unit ID
    uint16_t        mute;           ///< Mute Control
    int16_t         volume_min;     ///< Minimum (Attribute of Volume Control)
    int16_t         volume_max;     ///< Maximum (Attribute of Volume Control)
    uint16_t        volume_res;     ///< Resolution (Attribute of Volume Control)
    int16_t         volume;         ///< Volume Control
} usb_paud_audio_control_t;

/** Audio Control Setting Group */
typedef struct st_usb_paud_audio_control_group
{
    uint32_t                   controls_nb; ///< Number of Audio Control Group
    usb_paud_audio_control_t  *p_controls;  ///< Pointer for access to Audio Control Settings
} usb_paud_audio_control_group_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_PAUD_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PAUD_API)
 **********************************************************************************************************************/
