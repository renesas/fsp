/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_usb_puvc.h
 * Description  : USB PUVC public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//*
 * @addtogroup USB_PUVC
 * @{
 **********************************************************************************************************************/
#ifndef USB_PUVC_H
#define USB_PUVC_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_puvc_cfg.h"
#include "r_usb_basic_api.h"
#include "r_usb_puvc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* Video Class Probe and Commit Controls */
#define USB_PUVC_PROBE_COMMIT_LENGTH_1_1                               (34U)
#define USB_PUVC_PROBE_COMMIT_LENGTH_1_5                               (48U)
#define USB_PUVC_PROBE_COMMIT_HINT_OFFSET                              (0U)
#define USB_PUVC_PROBE_COMMIT_FORMAT_INDEX_OFFSET                      (2U)
#define USB_PUVC_PROBE_COMMIT_FRAME_INDEX_OFFSET                       (3U)
#define USB_PUVC_PROBE_COMMIT_FRAME_INTERVAL_OFFSET                    (4U)
#define USB_PUVC_PROBE_COMMIT_KEY_FRAME_RATE_OFFSET                    (8U)
#define USB_PUVC_PROBE_COMMIT_PFRAME_RATE_OFFSET                       (10U)
#define USB_PUVC_PROBE_COMMIT_COMP_QUALITY_OFFSET                      (12U)
#define USB_PUVC_PROBE_COMMIT_COMP_WINDOW_SIZE_OFFSET                  (14U)
#define USB_PUVC_PROBE_COMMIT_DELAY_OFFSET                             (16U)
#define USB_PUVC_PROBE_COMMIT_MAX_VIDEO_FRAME_SIZE_OFFSET              (18U)
#define USB_PUVC_PROBE_COMMIT_MAX_PAYLOAD_TRANSFER_SIZE_OFFSET         (22U)
#define USB_PUVC_PROBE_COMMIT_CLOCK_FREQUENCY_OFFSET                   (26U)
#define USB_PUVC_PROBE_COMMIT_FRAMING_INFO_OFFSET                      (30U)
#define USB_PUVC_PROBE_COMMIT_PREFERRED_VERSION_OFFSET                 (31U)
#define USB_PUVC_PROBE_COMMIT_MIN_VERSION_OFFSET                       (32U)
#define USB_PUVC_PROBE_COMMIT_MAX_VERSION_OFFSET                       (33U)
#define USB_PUVC_PROBE_COMMIT_USAGE_OFFSET                             (34U)
#define USB_PUVC_PROBE_COMMIT_BIT_DEPTH_LUMA_OFFSET                    (35U)
#define USB_PUVC_PROBE_COMMIT_SETTINGS_OFFSET                          (36U)
#define USB_PUVC_PROBE_COMMIT_MAX_NUMBER_OF_REF_FRAMES_PLUS1_OFFSET    (37U)
#define USB_PUVC_PROBE_COMMIT_RATE_CONTROL_MODES_OFFSET                (38U)
#define USB_PUVC_PROBE_COMMIT_LAYOUT_PER_STREAM_OFFSET                 (40U)

/* Video Class Payload Header definitions */
#define USB_PUVC_PAYLOAD_HEADER_LENGTH_OFFSET                          (0U)
#define USB_PUVC_PAYLOAD_HEADER_BFH_OFFSET                             (1U)
#define USB_PUVC_PAYLOAD_HEADER_PTS_OFFSET                             (2U)
#define USB_PUVC_PAYLOAD_HEADER_SCR_OFFSET                             (6U)

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_PUVC_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PUVC)
 **********************************************************************************************************************/
