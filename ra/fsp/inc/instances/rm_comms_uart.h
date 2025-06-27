/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_UART
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_UART_H
#define RM_COMMS_UART_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_uart_api.h"
#include "rm_comms_api.h"
#include "rm_comms_uart_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* UART bus configuration */
typedef struct st_rm_comms_uart_extended_cfg
{
#if BSP_CFG_RTOS
    void * const   p_tx_mutex;         ///< Lock device for writing.
    void * const   p_rx_mutex;         ///< Lock device for reading.
    uint32_t const mutex_timeout;      ///< Timeout for locking device.
    void * const   p_tx_semaphore;     ///< Block write operations. If this is NULL then operations will be non-blocking and require a callback.
    void * const   p_rx_semaphore;     ///< Block read operations. If this is NULL then operations will be non-blocking and require a callback.
#endif
    uart_instance_t const * p_uart;    ///< Pointer to UART instance.
} rm_comms_uart_extended_cfg_t;

/** Communications middleware control structure. */
typedef struct st_rm_comms_uart_instance_ctrl
{
    uint32_t                             open;              ///< Open flag.
    rm_comms_cfg_t const               * p_cfg;             ///< Middleware configuration.
    rm_comms_uart_extended_cfg_t const * p_extend;          ///< Pointer to extended configuration structure

    void (* p_callback)(rm_comms_callback_args_t * p_args); ///< Pointer to callback that is called when a uart_event_t occurs.
    void * p_context;                                       ///< Pointer to context passed into callback function
} rm_comms_uart_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern rm_comms_api_t const g_comms_on_comms_uart;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_Open(rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg);
fsp_err_t RM_COMMS_UART_Close(rm_comms_ctrl_t * const p_api_ctrl);
fsp_err_t RM_COMMS_UART_Read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t RM_COMMS_UART_Write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t RM_COMMS_UART_WriteRead(rm_comms_ctrl_t * const            p_api_ctrl,
                                  rm_comms_write_read_params_t const write_read_params);
fsp_err_t RM_COMMS_UART_CallbackSet(rm_comms_ctrl_t * const p_api_ctrl,
                                    void (                * p_callback)(rm_comms_callback_args_t *),
                                    void * const            p_context);

FSP_FOOTER

#endif                                 /* RM_COMMS_UART_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_UART)
 **********************************************************************************************************************/
