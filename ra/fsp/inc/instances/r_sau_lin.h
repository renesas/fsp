/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup SAU_LIN
 * @{
 **********************************************************************************************************************/

#ifndef R_SAU_LIN_H
#define R_SAU_LIN_H

#include "r_sau_lin_cfg.h"
#include "r_lin_api.h"
#include "r_sau_uart.h"
#include "r_timer_api.h"
#include "r_external_irq_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** SAU LIN Event codes */
typedef enum e_sau_lin_state
{
    SAU_LIN_STATE_NONE,                 ///< Master mode: No event present Slave mode: Waiting for break field signal
    SAU_LIN_STATE_SENDING_WAKEUP,       ///< Transmitting wakeup signal
    SAU_LIN_STATE_SENDING_BREAK_FIELD,  ///< Transmitting break field signal
    SAU_LIN_STATE_SENDING_SYNC,         ///< Transmitting sync word
    SAU_LIN_STATE_AWAITING_SYNC_SIGNAL, ///< Waiting to receive sync word
    SAU_LIN_STATE_SENDING_PID,          ///< Transmitting protected identifier
    SAU_LIN_STATE_AWAITING_PID_SIGNAL,  ///< Waiting to receive protected identifier
    SAU_LIN_STATE_HEADER_RECEIVED,      ///< LIN header received
    SAU_LIN_STATE_SENDING_DATA,         ///< Transmitting LIN data
    SAU_LIN_STATE_AWAITING_DATA,        ///< Receiving LIN data
    SAU_LIN_STATE_AWAITING_CHECKSUM,    ///< Receiving LIN checksum
    SAU_LIN_STATE_BUS_SLEEP,            ///< Bus sleep state
} sau_lin_state_t;

/** Auto synchronization setting. */
typedef enum e_sau_lin_synchronization
{
    SAU_LIN_AUTO_SYNCHRONIZATION_DISABLE = 0, ///< Disable auto synchronization during sync byte reception.
    SAU_LIN_AUTO_SYNCHRONIZATION_ENABLE  = 1, ///< Enable auto synchronization during sync byte reception.
} sau_lin_synchronization_t;

/** SAU UART LIN extended configuration */
typedef struct st_sau_lin_extended_cfg
{
    const uart_instance_t         * p_uart;               ///< The UART instance used in SAU LIN
    const external_irq_instance_t * p_icu;                ///< The IRQ instance used in SAU LIN
#if SAU_LIN_CFG_MASTER_SUPPORT_ENABLE
    sau_uart_baudrate_setting_t * p_break_field_baudrate; ///< Alternate baud rate setting for sending break field
#endif
#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
    const timer_instance_t  * p_timer;                    ///< The TAU instance used in SAU LIN
    uint32_t                  timer_clock_frequency;      ///< Timer clock frequency
    sau_lin_synchronization_t auto_synchronization;       ///< Auto synchronization setting
#endif
} sau_lin_extended_cfg_t;

/** LIN Instance Control Block. DO NOT INITIALIZE. */
typedef struct st_sau_lin_instance_ctrl
{
    lin_cfg_t const * p_cfg;                    // Pointer to the configuration structure
    uint32_t          open;                     // Used to determine if the channel is configured
    void (* p_callback)(lin_callback_args_t *); // Pointer to callback
    void              * p_context;              // Pointer to context to be passed into callback function
    uint8_t           * p_data;                 // Data frame buffer pointer (used for both transmission and reception)
    uint8_t             count;                  // Tracks number of data bytes expected in the transfer (used for both transmission and reception).
    lin_checksum_type_t checksum_type;          // Checksum type to use for checksum generation
    uint8_t             checksum;               // Transmission: stores the computed checksum for transmitted data. Reception: upon receiving the checksum byte, stores the received checksum.
    uint8_t             validate_checksum;      // Indicates whether checksum should be validated by driver
    uint8_t             last_pid;               // Last PID transmitted or received
    sau_lin_state_t     state;                  // Tracks LIN transmission/reception state
#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
    uint32_t sync_bits_sum;                     // Stores the calculated sum of pulse widths
    uint8_t  sync_bits_received;                // Stores the calculated sum of pulse times
#endif
} sau_lin_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern lin_api_t const g_lin_on_sau_lin;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_Open(lin_ctrl_t * const p_api_ctrl, lin_cfg_t const * const p_cfg);
fsp_err_t R_SAU_LIN_Write(lin_ctrl_t * const p_api_ctrl, const lin_transfer_params_t * const p_transfer_params);
fsp_err_t R_SAU_LIN_StartFrameWrite(lin_ctrl_t * const p_api_ctrl, uint8_t const id);             // [DEPRECATED]
fsp_err_t R_SAU_LIN_InformationFrameWrite(lin_ctrl_t * const                  p_api_ctrl,
                                          const lin_transfer_params_t * const p_transfer_params); // [DEPRECATED]
fsp_err_t R_SAU_LIN_InformationFrameRead(lin_ctrl_t * const            p_api_ctrl,
                                         lin_transfer_params_t * const p_transfer_params);        // [DEPRECATED]
fsp_err_t R_SAU_LIN_Read(lin_ctrl_t * const p_api_ctrl, lin_transfer_params_t * const p_transfer_params);
fsp_err_t R_SAU_LIN_CommunicationAbort(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_LIN_CallbackSet(lin_ctrl_t * const          p_api_ctrl,
                                void (                    * p_callback)(lin_callback_args_t *),
                                void * const                p_context,
                                lin_callback_args_t * const p_callback_memory);
fsp_err_t R_SAU_LIN_WakeupSend(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_LIN_SleepEnter(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_LIN_SleepExit(lin_ctrl_t * const p_api_ctrl);
fsp_err_t R_SAU_LIN_Close(lin_ctrl_t * const p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup SAU_LIN)
 **********************************************************************************************************************/
