/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_UARTA_H
#define R_UARTA_H

/*******************************************************************************************************************//**
 * @addtogroup UARTA
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_uart_api.h"
#include "r_uarta_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define UARTA_UTA0CK_SOSC_LOCO_SETTING    (0x08U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Enumeration for UARTA clock source */
typedef enum e_uarta_clock_source
{
    UARTA_CLOCK_SOURCE_SOSC_LOCO = 0U, ///< SOSC/LOCO
    UARTA_CLOCK_SOURCE_MOSC      = 1U, ///< MOSC
    UARTA_CLOCK_SOURCE_HOCO      = 2U, ///< HOCO
    UARTA_CLOCK_SOURCE_MOCO      = 3U, ///< MOCO
} uarta_clock_source_t;

/** Enumeration for UARTA clock divider */
typedef enum e_uarta_clock_div
{
    UARTA_CLOCK_DIV_1 = 0U,            ///< fSEL/1
    UARTA_CLOCK_DIV_2,                 ///< fSEL/2
    UARTA_CLOCK_DIV_4,                 ///< fSEL/4
    UARTA_CLOCK_DIV_8,                 ///< fSEL/8
    UARTA_CLOCK_DIV_16,                ///< fSEL/16
    UARTA_CLOCK_DIV_32,                ///< fSEL/32
    UARTA_CLOCK_DIV_64,                ///< fSEL/64
    UARTA_CLOCK_DIV_COUNT,             ///< Total number of clock divider options.
} uarta_clock_div_t;

/** Receive interrupt mode select */
typedef enum e_uarta_rxi_mode
{
    UARTA_RXI_MODE_ERROR_TRIGGER_ERI = 0U, ///< The receive error interrupt is generated when a reception error occurs.
    UARTA_RXI_MODE_ERROR_TRIGGER_RXI = 1U, ///< The receive interrupt is generated when a reception error occurs.
} uarta_rxi_mode_t;

/** Transmission/reception order configuration. */
typedef enum e_uarta_dir_bit
{
    UARTA_DIR_BIT_MSB_FIRST = 0U,      ///< MSB first
    UARTA_DIR_BIT_LSB_FIRST = 1U,      ///< LSB first
} uarta_dir_bit_t;

/** Transmission/reception level configuration. */
typedef enum e_uarta_alv_bit
{
    UARTA_ALV_BIT_POSITIVE_LOGIC = 0U, ///< Positive logic (wait state = high level, start bit = low level, stop bit = high level)
    UARTA_ALV_BIT_NEGATIVE_LOGIC = 1U, ///< Negative logic (wait state = low level, start bit = high level, stop bit = low level)
} uarta_alv_bit_t;

/** Register settings to acheive a desired baud rate and modulation duty. */
typedef struct st_uarta_baud_setting
{
    union
    {
        uint8_t uta0ck_clock;

        struct
        {
            uint8_t uta0ck : 4;        ///< UARTA operation clock select (f_UTA0n)
            uint8_t utasel : 2;        ///< fSEL clock select
            uint8_t        : 2;
        } uta0ck_clock_b;
    };
    uint8_t brgca;                     ///< Baud rate generator control setting
} uarta_baud_setting_t;

/** UART on UARTA device Configuration */
typedef struct st_uarta_extended_cfg
{
    uarta_rxi_mode_t       rxi_mode;       ///< Receive interrupt mode select
    uarta_dir_bit_t        transfer_dir;   ///< Transmission/reception order configuration
    uarta_alv_bit_t        transfer_level; ///< Transmission/reception level configuration
    uarta_baud_setting_t * p_baud_setting; ///< Register settings for a desired baud rate.
} uarta_extended_cfg_t;

/** UARTA instance control block. */
typedef struct st_uarta_instance_ctrl
{
    /* Parameters to control UARTA peripheral device */
    uint8_t  rx_transfer_in_progress;  // Set to 1 if a receive transfer is in progress, 0 otherwise
    uint32_t open;                     // Used to determine if the channel is configured

    /* Source buffer pointer used for transmitting data. */
    uint8_t const * p_tx_src;

    /* Size of source buffer pointer used for transmitting data. */
    uint32_t tx_src_bytes;

    /* Destination buffer pointer used for receiving data. */
    uint8_t * p_rx_dest;

    /* Size of destination buffer pointer used for receiving data. */
    uint32_t rx_dest_bytes;

    /* Pointer to the configuration block. */
    uart_cfg_t const * p_cfg;

    /* Pointer to callback that is called when a uart_event_t occurs. */
    void (* p_callback)(uart_callback_args_t *);

    /* Pointer to context to be passed into callback function */
    void const * p_context;
} uarta_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const uart_api_t g_uart_on_uarta;

/** @endcond */

fsp_err_t R_UARTA_Open(uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg);
fsp_err_t R_UARTA_Read(uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_UARTA_Write(uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes);
fsp_err_t R_UARTA_BaudSet(uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting);
fsp_err_t R_UARTA_InfoGet(uart_ctrl_t * const p_api_ctrl, uart_info_t * const p_info);
fsp_err_t R_UARTA_Close(uart_ctrl_t * const p_api_ctrl);
fsp_err_t R_UARTA_Abort(uart_ctrl_t * const p_api_ctrl, uart_dir_t communication_to_abort);
fsp_err_t R_UARTA_BaudCalculate(uint32_t                     baudrate,
                                uint32_t                     baud_rate_percent_error_x1000,
                                uarta_clock_source_t         clock_source,
                                uarta_baud_setting_t * const p_baud_setting);
fsp_err_t R_UARTA_CallbackSet(uart_ctrl_t * const          p_api_ctrl,
                              void (                     * p_callback)(uart_callback_args_t *),
                              void const * const           p_context,
                              uart_callback_args_t * const p_callback_memory);
fsp_err_t R_UARTA_ReadStop(uart_ctrl_t * const p_api_ctrl, uint32_t * p_remaining_bytes);

/*******************************************************************************************************************//**
 * @} (end addtogroup UARTA)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
