/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
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
 * The USB HCDCinterface provides USB HCDC functionality.
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
typedef enum
{
    USB_HCDC_DATA_BIT_7 = 7U,          /* Line Coding 7Data bits */
    USB_HCDC_DATA_BIT_8 = 8U           /* Line Coding 8Data bits */
} usb_hcdc_data_bit_t;

typedef enum
{
    USB_HCDC_STOP_BIT_1  = 0U,         /* Line Coding 1Stop bits */
    USB_HCDC_STOP_BIT_15 = 1U,         /* Line Coding 1.5Stop bits */
    USB_HCDC_STOP_BIT_2  = 2U          /* Line Coding 2Stop bits */
} usb_hcdc_stop_bit_t;

typedef enum
{
    USB_HCDC_PARITY_BIT_NONE = 0U,     /* Line Coding None Parity */
    USB_HCDC_PARITY_BIT_ODD  = 1U,     /* Line Coding Odd Parity */
    USB_HCDC_PARITY_BIT_EVEN = 2U      /* Line Coding Even Parity */
} usb_hcdc_parity_bit_t;

typedef enum
{
#if USB_CFG_ENDIAN == USB_CFG_BIG
    USB_HCDC_SPEED_1200   = 0xb0040000U, /* Line Coding 1200bps */
    USB_HCDC_SPEED_2400   = 0x60090000U, /* Line Coding 2400bps */
    USB_HCDC_SPEED_4800   = 0xc0120000U, /* Line Coding 4800bps */
    USB_HCDC_SPEED_9600   = 0x80250000U, /* Line Coding 9600bps */
    USB_HCDC_SPEED_14400  = 0x40380000U, /* Line Coding 14400bps */
    USB_HCDC_SPEED_19200  = 0x004b0000U, /* Line Coding 19200bps */
    USB_HCDC_SPEED_38400  = 0x00960000U, /* Line Coding 38400bps */
    USB_HCDC_SPEED_57600  = 0x00e10000U, /* Line Coding 57600bps */
    USB_HCDC_SPEED_115200 = 0x00c20100U  /* Line Coding 115200bps */
#else /* USB_CFG_ENDIAN == USB_CFG_BIG */
    USB_HCDC_SPEED_1200   = 1200U,       /* Line Coding 1200bps */
    USB_HCDC_SPEED_2400   = 2400U,       /* Line Coding 2400bps */
    USB_HCDC_SPEED_4800   = 4800U,       /* Line Coding 4800bps */
    USB_HCDC_SPEED_9600   = 9600U,       /* Line Coding 9600bps */
    USB_HCDC_SPEED_14400  = 14400U,      /* Line Coding 14400bps */
    USB_HCDC_SPEED_19200  = 19200U,      /* Line Coding 19200bps */
    USB_HCDC_SPEED_38400  = 38400U,      /* Line Coding 38400bps */
    USB_HCDC_SPEED_57600  = 57600U,      /* Line Coding 57600bps */
    USB_HCDC_SPEED_115200 = 115200U      /* Line Coding 115200bps */
#endif /* USB_CFG_ENDIAN == USB_CFG_BIG */
} usb_hcdc_line_speed_t;

typedef enum
{
    USB_HCDC_ABSTRACT_STATE = 0x01U, USB_HCDC_COUNTRY_SETTING = 0x02U,
} usb_hcdc_feature_selctor_t;

/*****************************************************************************
 * Struct definition
 ******************************************************************************/

typedef struct
{
    uint8_t * p_data;                  /* Protocol dependent data */
    uint16_t  wlength;                 /* Amount of data, in bytes, associated with this recipient. */
} usb_hcdc_encapsulated_t;

// R_BSP_PRAGMA_UNPACK
typedef struct
{
    /* CPU bit order rigth */
    uint16_t bis  : 1;                 /* Idle Setting */
    uint16_t bdms : 1;                 /* Data Multiplexed State */
    uint16_t rsv  : 14;                /* Reserve */
} usb_hcdc_abstractstate_t;

// R_BSP_PRAGMA_PACKOPTION

typedef struct
{
    uint16_t country_code;
} usb_hcdc_countrysetting_t;

typedef union
{
    usb_hcdc_abstractstate_t  abstract_state;
    usb_hcdc_countrysetting_t country_setting;
} usb_hcdc_commfeature_t;

typedef struct
{
    uint32_t dwdte_rate;               /* Data terminal rate, in bits per second */
    uint8_t  bchar_format;             /* Stop bits */
    uint8_t  bparity_type;             /* Parity */
    uint8_t  bdata_bits;               /* Data bits */
    uint8_t  rsv;                      /* Reserve */
} usb_hcdc_linecoding_t;

// R_BSP_PRAGMA_UNPACK
typedef struct
{
    /* CPU bit order rigth */
    uint16_t bdtr : 1;                 /* DTR */
    uint16_t brts : 1;                 /* RTS */
    uint16_t rsv  : 14;                /* Reserve */
} usb_hcdc_controllinestate_t;

// BSP_PRAGMA_PACKOPTION

// R_BSP_PRAGMA_UNPACK
typedef struct
{
    /* CPU bit order rigth */
    uint16_t brx_carrier  : 1;         /* DCD signal */
    uint16_t btx_carrier  : 1;         /* DSR signal */
    uint16_t bbreak       : 1;         /* State of break detection mechanism of the device */
    uint16_t bring_signal : 1;         /* State of ring signal detection of the device */
    uint16_t bframing     : 1;         /* Framing error */
    uint16_t bparity      : 1;         /* Parity error */
    uint16_t bover_run    : 1;         /* Over Run error */
    uint16_t rsv          : 9;         /* Reserve */
} usb_hcdc_serialstate_t;

// R_BSP_PRAGMA_PACKOPTION

typedef struct
{
    uint16_t wtime_ms;                 /* Duration of Break */
} usb_hcdc_breakduration_t;

#endif /* R_USB_HCDC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HCDC_API)
 **********************************************************************************************************************/
