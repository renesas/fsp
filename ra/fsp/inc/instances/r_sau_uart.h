/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef R_SAU_UART_H
#define R_SAU_UART_H

/*******************************************************************************************************************//**
 * @addtogroup SAU_UART
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_uart_api.h"
#include "r_sau_uart_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** UART Data transfer sequence definition */
typedef enum e_sau_uart_data_sequence
{
    SAU_UART_DATA_SEQUENCE_MSB = 0U,   ///< Data sequence MSB first
    SAU_UART_DATA_SEQUENCE_LSB = 1U,   ///< Data sequence LSB first
} sau_uart_data_sequence_t;

/** UART operation clock selection definition */
typedef enum e_sau_operation_clock
{
    SAU_UART_OPERATION_CLOCK_CK0 = 0U, ///< Operating clock use CK0
    SAU_UART_OPERATION_CLOCK_CK1 = 1U, ///< Operating clock use CK1
} sau_operation_clock_t;

/** UART data signal level definition */
typedef enum e_sau_uart_signal_level
{
    SAU_UART_SIGNAL_LEVEL_STANDARD = 0U, ///< Uart data signal level standard
    SAU_UART_SIGNAL_LEVEL_INVERTED = 1U, ///< Uart data signal level inverted
} sau_uart_signal_level_t;

typedef struct
{
    sau_operation_clock_t operation_clock; ///< Select operation clock
    uint8_t               stclk;           ///< Transfer clock setting by dividing the operation clock
    uint8_t               prs;             ///< Operation clock divider register setting
} sau_uart_baudrate_setting_t;

/** UART Configuration */
typedef struct st_sau_uart_extended_cfg
{
    /* UART generic configuration */
    sau_uart_data_sequence_t      sequence;     ///< Transfer sequence (LSB or MSB)
    sau_uart_signal_level_t       signal_level; ///< Transfer data signal level (standard or inverted)
    sau_uart_baudrate_setting_t * p_baudrate;   ///< Baud rate setting (SPS and SDR value)
} sau_uart_extended_cfg_t;

/** UART instance control block. DO NOT INITIALIZE. */
typedef struct st_sau_uart_instance_ctrl
{
    uint8_t            extra_data_byte; ///< 0 for 7 or 8 bit data length(1-byte), 1 for 9 bit data length(2-byte)
    uint32_t           open;            ///< Used to determine if the channel is configured
    uart_cfg_t const * p_cfg;           ///< Pointer to the configuration block.
    R_SAU0_Type      * p_reg;           ///< Base register for the transmit channel
    uint8_t            sau_unit;        ///< SAU unit information
    uint8_t            sau_tx_channel;  ///< SAU channel information
    uint8_t          * p_src;           ///< Source buffer pointer
    uint32_t           tx_count;        ///< Size of destination buffer pointer from transmit ISR
    uint8_t          * p_dest;          ///< Destination buffer pointer
    uint32_t           rx_count;        ///< Size of destination buffer pointer used for receiving data

    /* Pointer to callback and optional working memory. */
    void (* p_callback)(uart_callback_args_t *);

    /* Pointer to context to be passed into callback function. */
    void * p_context;
} sau_uart_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const uart_api_t g_uart_on_sau;

/** @endcond */

fsp_err_t R_SAU_UART_Open(uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg);
fsp_err_t R_SAU_UART_Read(uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_SAU_UART_Write(uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes);
fsp_err_t R_SAU_UART_BaudSet(uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting);
fsp_err_t R_SAU_UART_InfoGet(uart_ctrl_t * const p_api_ctrl, uart_info_t * const p_info);
fsp_err_t R_SAU_UART_Close(uart_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_UART_Abort(uart_ctrl_t * const p_api_ctrl, uart_dir_t communication_to_abort);
fsp_err_t R_SAU_UART_CallbackSet(uart_ctrl_t * const          p_api_ctrl,
                                 void (                     * p_callback)(uart_callback_args_t *),
                                 void * const                 p_context,
                                 uart_callback_args_t * const p_callback_memory);
fsp_err_t R_SAU_UART_ReadStop(uart_ctrl_t * const p_api_ctrl, uint32_t * remaining_bytes);
fsp_err_t R_SAU_UART_BaudCalculate(sau_uart_instance_ctrl_t * const    p_ctrl,
                                   uint32_t                            baudrate,
                                   sau_uart_baudrate_setting_t * const p_baud_setting);
fsp_err_t R_SAU_UART_ReceiveSuspend(uart_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_UART_ReceiveResume(uart_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end addtogroup SAU_UART)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
