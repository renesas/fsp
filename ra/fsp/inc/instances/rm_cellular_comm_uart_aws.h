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

#ifndef RM_CELLULAR_COMM_UART_AWS_H
#define RM_CELLULAR_COMM_UART_AWS_H

/*******************************************************************************************************************//**
 * @addtogroup RM_CELLULAR_COMM_UART_AWS
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_uart_api.h"
#include "cellular_config.h"
#include "cellular_config_defaults.h"
#include "cellular_comm_interface.h"
#include "rm_cellular_comm_uart_aws_cfg.h"

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
 #include "FreeRTOS.h"
 #include "stream_buffer.h"
 #include "semphr.h"
 #include "portmacro.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef struct st_rm_cellular_comm_uart_aws_instance_ctrl
{
    uart_instance_t * p_lower_level_instance;                              ///< Lower level UART instance
    uint8_t         * p_recv_buffer;                                       ///< Receieve buffer to zero copy to
    uint32_t          remaining_recv_read_length;                          ///< Length left overall to read to receive buffer
    uint32_t          current_recv_read_length;                            ///< Length to read to receive buffer for current cluster of bytes
    bool              transfer_in_progress;                                ///< Indicates if transfer is in progress for recv
    uint8_t           rx_buffer[RM_CELLULAR_COMM_UART_AWS_RX_BUFFER_SIZE]; ///< Receive Buffer
    uint32_t          read_count;                                          ///< Number of bytes read into rx_buffer so far
    StaticSemaphore_t tx_semaphore_buffer;                                 ///< Transmit semaphore buffer
    SemaphoreHandle_t tx_semaphore_handle;                                 ///< Transmit semaphore handle
    StaticSemaphore_t rx_semaphore_buffer;                                 ///< Receive semaphore buffer
    SemaphoreHandle_t rx_semaphore_handle;                                 ///< Receive semaphore handle
    CellularCommInterfaceReceiveCallback_t receive_callback;               ///< Receive Callback
    void   * p_user_data;                                                  ///< Callback user data
    uint32_t open;                                                         ///< Open indicator
} rm_cellular_comm_uart_aws_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Open(rm_cellular_comm_uart_aws_instance_ctrl_t * p_instance_ctrl,
                                                            CellularCommInterfaceReceiveCallback_t      receive_callback,
                                                            void                                      * pUserData);
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Send(CellularCommInterfaceHandle_t commInterfaceHandle,
                                                            const uint8_t               * pData,
                                                            uint32_t                      dataLength,
                                                            uint32_t                      timeoutMilliseconds,
                                                            uint32_t                    * pDataSentLength);
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Receive(CellularCommInterfaceHandle_t commInterfaceHandle,
                                                               uint8_t                     * pBuffer,
                                                               uint32_t                      bufferLength,
                                                               uint32_t                      timeoutMilliseconds,
                                                               uint32_t                    * pDataReceivedLength);
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Close(CellularCommInterfaceHandle_t commInterfaceHandle);

void comm_uart_aws_callback(uart_callback_args_t * p_args);

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_CELLULAR_COMM_UART_AWS)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
