/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_CONNECTIVITY_INTERFACES
 * @defgroup USB_PCDC_API USB PCDC Interface
 * @brief Interface for USB PCDC functions.
 *
 * @section USB_PCDC_API_Summary Summary
 * The USB PCDC interface provides USB PCDC functionality.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_PCDC_API_H
#define R_USB_PCDC_API_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_basic_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* CDC Class Requests IDs*/
#define USB_PCDC_SET_LINE_CODING           (0x2000U) ///< Set Line Coding
#define USB_PCDC_GET_LINE_CODING           (0x2100U) ///< Get Line Coding
#define USB_PCDC_SET_CONTROL_LINE_STATE    (0x2200U) ///< Control Line State

#define USB_PCDC_SERIAL_STATE              (0x20)    ///< Serial State Code

#define USB_PCDC_SETUP_TBL_BSIZE           (10U)     ///< Setup packet table size (uint16_t * 5)

/*******************************************************************************
 * Typedef definitions
 *******************************************************************************/

/** Virtual UART signal state */
typedef struct
{
    uint16_t b_rx_carrier  : 1;        ///< DCD signal
    uint16_t b_tx_carrier  : 1;        ///< DSR signal
    uint16_t b_break       : 1;        ///< Break signal
    uint16_t b_ring_signal : 1;        ///< Ring signal
    uint16_t b_framing     : 1;        ///< Framing error
    uint16_t b_parity      : 1;        ///< Parity error
    uint16_t b_over_run    : 1;        ///< Overrun error
    uint16_t rsv           : 9;        ///< Reserved
} usb_serial_state_bitmap_t;

/** Class Notification Serial State */
typedef union
{
    uint32_t word;                     ///< Word Access
    usb_serial_state_bitmap_t bit;     ///< Bit Access
} usb_sci_serialstate_t;

/** Virtual UART communication settings */
typedef struct
{
    uint32_t dw_dte_rate;              ///< Bitrate
    uint8_t  b_char_format;            ///< Stop bits
    uint8_t  b_parity_type;            ///< Parity
    uint8_t  b_data_bits;              ///< Data bits
    uint8_t  rsv;                      ///< Reserved
} usb_pcdc_linecoding_t;

/** Virtual UART control line state */
typedef struct
{
    uint16_t bdtr : 1;                 ///< DTR
    uint16_t brts : 1;                 ///< RTS
    uint16_t rsv  : 14;                ///< Reserved
} usb_pcdc_ctrllinestate_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_PCDC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_PCDC_API)
 **********************************************************************************************************************/
