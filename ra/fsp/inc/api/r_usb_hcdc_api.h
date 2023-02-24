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
 * @defgroup USB_HCDC_API USB HCDC Interface
 * @brief Interface for USB HCDC functions.
 *
 * @section USB_HCDC_API_Summary Summary
 * The USB HCDC interface provides USB HCDC functionality.
 *
 * The USB HCDC interface can be implemented by:
 * - @ref USB_HCDC
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_HCDC_API_H
 #define R_USB_HCDC_API_H

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
 #include "r_usb_hcdc_cfg.h"

 #ifdef __cplusplus
extern "C" {
 #endif

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

/* Serial State message Length */
 #define     USB_HCDC_SERIAL_STATE_MSG_LEN         (10)

/* CDC Class Requests IDs*/
 #define     USB_CDC_SEND_ENCAPSULATED_COMMAND     (0x0000)
 #define     USB_CDC_GET_ENACAPSULATED_RESPONSE    (0x0100)
 #define     USB_CDC_SET_COMM_FEATURE              (0x0200)
 #define     USB_CDC_GET_COMM_FEATURE              (0x0300)
 #define     USB_CDC_CLR_COMM_FEATURE              (0x0400)
 #define     USB_CDC_SET_LINE_CODING               (0x2000)
 #define     USB_CDC_GET_LINE_CODING               (0x2100)
 #define     USB_CDC_SET_CONTROL_LINE_STATE        (0x2200)
 #define     USB_CDC_SEND_BREAK                    (0x2300)
 #define     USB_CDC_REQUEST_NONE                  (0xffff)

/*****************************************************************************
 * Enumerated Types
 ******************************************************************************/

/** Virtual UART data length */
typedef enum
{
    USB_HCDC_DATA_BIT_7 = 7U,          ///< 7 bits
    USB_HCDC_DATA_BIT_8 = 8U           ///< 8 bits
} usb_hcdc_data_bit_t;

/** Virtual UART stop bit length */
typedef enum
{
    USB_HCDC_STOP_BIT_1  = 0U,         ///< 1 bit
    USB_HCDC_STOP_BIT_15 = 1U,         ///< 1.5 bits
    USB_HCDC_STOP_BIT_2  = 2U          ///< 2 bits
} usb_hcdc_stop_bit_t;

/** Virtual UART parity bit setting */
typedef enum
{
    USB_HCDC_PARITY_BIT_NONE = 0U,     ///< No parity bit
    USB_HCDC_PARITY_BIT_ODD  = 1U,     ///< Odd parity
    USB_HCDC_PARITY_BIT_EVEN = 2U      ///< Even parity
} usb_hcdc_parity_bit_t;

/** Virtual UART bitrate */
typedef enum
{
 #if USB_CFG_ENDIAN == USB_CFG_BIG
    USB_HCDC_SPEED_1200   = 0xb0040000U,
    USB_HCDC_SPEED_2400   = 0x60090000U,
    USB_HCDC_SPEED_4800   = 0xc0120000U,
    USB_HCDC_SPEED_9600   = 0x80250000U,
    USB_HCDC_SPEED_14400  = 0x40380000U,
    USB_HCDC_SPEED_19200  = 0x004b0000U,
    USB_HCDC_SPEED_38400  = 0x00960000U,
    USB_HCDC_SPEED_57600  = 0x00e10000U,
    USB_HCDC_SPEED_115200 = 0x00c20100U
 #else
    USB_HCDC_SPEED_1200   = 1200U,     ///< 1200bps
    USB_HCDC_SPEED_2400   = 2400U,     ///< 2400bps
    USB_HCDC_SPEED_4800   = 4800U,     ///< 4800bps
    USB_HCDC_SPEED_9600   = 9600U,     ///< 9600bps
    USB_HCDC_SPEED_14400  = 14400U,    ///< 14400bps
    USB_HCDC_SPEED_19200  = 19200U,    ///< 19200bps
    USB_HCDC_SPEED_38400  = 38400U,    ///< 38400bps
    USB_HCDC_SPEED_57600  = 57600U,    ///< 57600bps
    USB_HCDC_SPEED_115200 = 115200U    ///< 115200bps
 #endif
} usb_hcdc_line_speed_t;

/** Feature Selector */
typedef enum
{
    USB_HCDC_ABSTRACT_STATE  = 0x01U,
    USB_HCDC_COUNTRY_SETTING = 0x02U,
} usb_hcdc_feature_selector_t;

/*****************************************************************************
 * Struct definition
 ******************************************************************************/

/** Encapsulated data */
typedef struct
{
    uint8_t * p_data;                  ///< Protocol dependent data
    uint16_t  wlength;                 ///< Data length in bytes
} usb_hcdc_encapsulated_t;

/** Abstract Control Model (ACM) settings bitmap */
typedef struct
{
    uint16_t bis  : 1;                 ///< Idle enable
    uint16_t bdms : 1;                 ///< Data multiplexing enable
    uint16_t rsv  : 14;                ///< Reserved
} usb_hcdc_abstractstate_t;

/** Country code data */
typedef struct
{
    uint16_t country_code;             ///< Country code
} usb_hcdc_countrysetting_t;

/** Feature setting data */
typedef union
{
    usb_hcdc_abstractstate_t  abstract_state;  ///< ACM settings bitmap
    usb_hcdc_countrysetting_t country_setting; ///< Country code
} usb_hcdc_commfeature_t;

/** Virtual UART configuration (line coding) */
typedef struct
{
    usb_hcdc_line_speed_t dwdte_rate;   ///< Data terminal rate in bits per second
    usb_hcdc_stop_bit_t   bchar_format; ///< Stop bits
    usb_hcdc_parity_bit_t bparity_type; ///< Parity
    usb_hcdc_data_bit_t   bdata_bits;   ///< Data bits
    uint8_t               rsv;          ///< Reserved
} usb_hcdc_linecoding_t;

/** Virtual UART control signal bitmap */
typedef struct
{
    uint16_t bdtr : 1;                 ///< DTR
    uint16_t brts : 1;                 ///< RTS
    uint16_t rsv  : 14;                ///< Reserved
} usb_hcdc_controllinestate_t;

/** Virtual UART state bitmap */
typedef struct
{
    uint16_t brx_carrier  : 1;         ///< DCD signal
    uint16_t btx_carrier  : 1;         ///< DSR signal
    uint16_t bbreak       : 1;         ///< Break detection status
    uint16_t bring_signal : 1;         ///< Ring signal
    uint16_t bframing     : 1;         ///< Framing error
    uint16_t bparity      : 1;         ///< Parity error
    uint16_t bover_run    : 1;         ///< Over Run error
    uint16_t rsv          : 9;         ///< Reserved
} usb_hcdc_serialstate_t;

/** Break duration data */
typedef struct
{
    uint16_t wtime_ms;                 ///< Duration of Break
} usb_hcdc_breakduration_t;

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R_USB_HCDC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HCDC_API)
 **********************************************************************************************************************/
