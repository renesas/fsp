/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @addtogroup AT_TRANSPORT_DA16XXX_UART
 * @{
 **********************************************************************************************************************/
#ifndef RM_AT_TRANSPORT_DA16XXX_H
#define RM_AT_TRANSPORT_DA16XXX_H

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

#include "r_uart_api.h"
#include "r_ioport_api.h"
#include "r_ioport.h"
#include "rm_at_transport_da16xxx.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "stream_buffer.h"
#include "rm_at_transport_da16xxx_uart_cfg.h"

/** User configuration structure, used in open function */
typedef struct st_da16xxx_extended_transport_cfg
{
    const uint32_t          num_uarts;                                                      ///< Number of UART interfaces to use
    const uart_instance_t * uart_instances[AT_TRANSPORT_DA16XXX_CFG_MAX_NUMBER_UART_PORTS]; ///< SCI UART instances
    const bsp_io_port_pin_t reset_pin;                                                      ///< Reset pin used for module
} at_transport_da16xxx_extended_cfg_t;

/** AT_TRANSPORT_DA16XXX private control block. DO NOT MODIFY. */
typedef struct st_da16xxx_transport_instance_ctrl
{
    at_transport_da16xxx_cfg_t const * p_cfg;                                                      ///< Pointer to initial configurations.
    uint32_t num_uarts;                                                                            ///< number of UARTS currently used for communication with module
    uint32_t curr_cmd_port;                                                                        ///< Current UART instance index for AT commands
    uint32_t open;                                                                                 ///< Flag to indicate if transport instance has been initialized

    uint8_t              cmd_rx_queue_buf[AT_TRANSPORT_DA16XXX_CFG_CMD_RX_BUF_SIZE];               ///< Command port receive buffer used by byte queue // FreeRTOS
    StreamBufferHandle_t socket_byteq_hdl;                                                         ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                                      ///< Structure to hold stream buffer info

    SemaphoreHandle_t tx_sem;                                                                      ///< Transmit binary semaphore handle
    SemaphoreHandle_t rx_sem;                                                                      ///< Receive binary semaphore handle

    uart_instance_t       * uart_instance_objects[AT_TRANSPORT_DA16XXX_CFG_MAX_NUMBER_UART_PORTS]; ///< UART instance object
    SemaphoreHandle_t       uart_tei_sem[AT_TRANSPORT_DA16XXX_CFG_MAX_NUMBER_UART_PORTS];          ///< UART transmission end binary semaphore
    const bsp_io_port_pin_t reset_pin;                                                             ///< Reset pin used for module

    /* Pointer to callback and optional working memory */
    bool (* p_callback)(at_transport_da16xxx_callback_args_t * p_args);                            ///< Pointer to callback function.
    void const * p_context;                                                                        ///< Pointer to the user-provided context
} at_transport_da16xxx_instance_ctrl_t;

extern const char * g_at_transport_da16xxx_uart_cmd_baud;
extern at_transport_da16xxx_api_t const g_at_transport_da16xxx_on_uart;
void rm_at_transport_da16xxx_uart_callback(uart_callback_args_t * p_args);

fsp_err_t rm_at_transport_da16xxx_uartOpen(at_transport_da16xxx_ctrl_t * const      p_ctrl,
                                           at_transport_da16xxx_cfg_t const * const p_cfg);
fsp_err_t rm_at_transport_da16xxx_uart_atCommandSendThreadSafe(at_transport_da16xxx_ctrl_t * const p_ctrl,
                                                               at_transport_da16xxx_data_t       * p_at_cmd);
fsp_err_t rm_at_transport_da16xxx_uart_atCommandSend(at_transport_da16xxx_ctrl_t * const p_ctrl,
                                                     at_transport_da16xxx_data_t       * p_at_cmd);
fsp_err_t rm_at_transport_da16xxx_uart_giveMutex(at_transport_da16xxx_ctrl_t * const p_ctrl, uint32_t mutex_flag);
fsp_err_t rm_at_transport_da16xxx_uart_takeMutex(at_transport_da16xxx_ctrl_t * const p_ctrl, uint32_t mutex_flag);
size_t    rm_at_transport_da16xxx_uart_bufferRecv(at_transport_da16xxx_ctrl_t * const p_ctrl,
                                                  const char                        * p_data,
                                                  uint32_t                            length,
                                                  uint32_t                            rx_timeout);
fsp_err_t rm_at_transport_da16xxx_statusGet(at_transport_da16xxx_ctrl_t * const p_ctrl,
                                            at_transport_da16xxx_status_t     * p_status);
fsp_err_t rm_at_transport_da16xxx_uartClose(at_transport_da16xxx_ctrl_t * const p_ctrl);

#endif                                 // RM_AT_TRANSPORT_DA16XXX_H

/*******************************************************************************************************************//**
 * @} (end addtogroup AT_TRANSPORT_DA16XXX)
 **********************************************************************************************************************/
