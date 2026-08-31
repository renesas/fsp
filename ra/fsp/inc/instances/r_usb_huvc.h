/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Description  : USB HUVC public APIs.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB_HUVC
 * @{
 **********************************************************************************************************************/

#ifndef USB_HUVC_H
#define USB_HUVC_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_huvc_cfg.h"
#include "r_usb_basic_api.h"
#include "r_usb_huvc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* Video Streaming Interface Probe/Commit Control's Struct Index */
#define     USB_HUVC_PROBE_COMMIT_LENGTH                                 (34U)
#define     USB_HUVC_PROBE_COMMIT_HINT                                   (0U)
#define     USB_HUVC_PROBE_COMMIT_FORMAT_INDEX                           (2U)
#define     USB_HUVC_PROBE_COMMIT_FRAME_INDEX                            (3U)
#define     USB_HUVC_PROBE_COMMIT_FRAME_INTERVAL                         (4U)
#define     USB_HUVC_PROBE_COMMIT_KEY_FRAME_RATE                         (8U)
#define     USB_HUVC_PROBE_COMMIT_PFRAME_RAE                             (10U)
#define     USB_HUVC_PROBE_COMMIT_COMP_QUALITY                           (12U)
#define     USB_HUVC_PROBE_COMMIT_COMP_WINDOW_SIZE                       (14U)
#define     USB_HUVC_PROBE_COMMIT_DELAY                                  (16U)
#define     USB_HUVC_PROBE_COMMIT_MAX_VIDEO_FRAME_SIZE                   (18U)
#define     USB_HUVC_PROBE_COMMIT_MAX_PAYLOAD_TRANSFER_SIZE              (22U)
#define     USB_HUVC_PROBE_COMMIT_CLOCK_FREQUENCY                        (26U)
#define     USB_HUVC_PROBE_COMMIT_FRAMING_INFO                           (30U)
#define     USB_HUVC_PROBE_COMMIT_PREFERRED_VERSION                      (31U)
#define     USB_HUVC_PROBE_COMMIT_MIN_VERSION                            (32U)
#define     USB_HUVC_PROBE_COMMIT_MAX_VERSION                            (33U)

/* Restriction of Video Streaming Interface selection (because RA does not support high bandwidth transfers). */
#define     USB_UVC_VS_EP_MPS_ADDITIONAL_TRANSACTION_PER_MICROFRAME      (0x1800)
#define     USB_UVC_VS_EP_MPS_0_ADDITIONAL_TRANSACTION_PER_MICROFRAME    (0x07FF)

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/
fsp_err_t R_USB_HUVC_DeviceInfoGet(usb_ctrl_t * const       p_api_ctrl,
                                   usb_huvc_device_info_t * p_info,
                                   uint8_t                  device_address);
fsp_err_t R_USB_HUVC_FormatAndFrameInfoGet(usb_ctrl_t * const          p_api_ctrl,
                                           usb_huvc_streaming_info_t * p_info,
                                           uint8_t                     device_address);
fsp_err_t R_USB_HUVC_AlternateNumberGet(usb_ctrl_t * const          p_api_ctrl,
                                        usb_huvc_streaming_info_t * p_info,
                                        uint8_t                     device_address);
fsp_err_t R_USB_HUVC_PipeSet(usb_ctrl_t * const p_api_ctrl,
                             uint32_t           interface_number,
                             uint32_t           alternate_number,
                             uint8_t            device_address);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* USB_HUVC_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HUVC)
 **********************************************************************************************************************/
