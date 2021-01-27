/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * @addtogroup WIFI_ONCHIP_SILEX WIFI_ONCHIP_SILEX
 * @{
 **********************************************************************************************************************/

#ifndef RM_WIFI_ONCHIP_SILEX_H
#define RM_WIFI_ONCHIP_SILEX_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

#include "iot_wifi.h"

#include "r_uart_api.h"
#include "r_sci_uart.h"

#include "rm_wifi_onchip_silex_cfg.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "stream_buffer.h"

#include "aws_secure_sockets_config.h"
#include "aws_wifi_config.h"

#include "r_ioport_api.h"

extern const ioport_instance_t g_ioport;

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH    (13 + 1) // Length of the tailing buffer used by command parser
#define WIFI_ONCHIP_SILEX_CODE_VERSION_MAJOR    (1U)     // DEPRECATED
#define WIFI_ONCHIP_SILEX_CODE_VERSION_MINOR    (2U)     // DEPRECATED

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Silex ULPGN Wifi security types */
typedef enum
{
    WIFI_ONCHIP_SILEX_SECURITY_OPEN = 0,
    WIFI_ONCHIP_SILEX_SECURITY_WPA,
    WIFI_ONCHIP_SILEX_SECURITY_WPA2,
    WIFI_ONCHIP_SILEX_SECURITY_WEP,
    WIFI_ONCHIP_SILEX_SECURITY_UNDEFINED,
} sx_ulpgn_security_t;

/** Silex ULPGN Wifi socket status types */
typedef enum
{
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_CLOSED = 0,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_SOCKET,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_BOUND,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_LISTEN,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED,
} sx_ulpgn_socket_status_t;

/** Silex socket shutdown channels */
typedef enum
{
    WIFI_ONCHIP_SILEX_SOCKET_READ  = 1,
    WIFI_ONCHIP_SILEX_SOCKET_WRITE = 2,
} sx_ulpgn_socket_rw;

/** User configuration structure, used in open function */
typedef struct st_wifi_onchip_cfg
{
    const uint32_t          num_uarts;                                                   ///< Number of UART interfaces to use
    const uint32_t          num_sockets;                                                 ///< Number of sockets to initialize
    const bsp_io_port_pin_t reset_pin;                                                   ///< Reset pin used for module
    const uart_instance_t * uart_instances[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS]; ///< SCI UART instances
    void const            * p_context;                                                   ///< User defined context passed into callback function.
    void const            * p_extend;                                                    ///< Pointer to extended configuration by instance of interface.
} wifi_onchip_silex_cfg_t;

/** Silex ULPGN Wifi internal socket instance structure */
typedef struct
{
    StreamBufferHandle_t socket_byteq_hdl;                                           ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                        ///< Structure to hold stream buffer info
    uint8_t              socket_recv_buff[WIFI_ONCHIP_SILEX_CFG_MAX_SOCKET_RX_SIZE]; ///< Socket receive buffer used by byte queue
    uint32_t             socket_status;                                              ///< Current socket status
    uint32_t             socket_recv_error_count;                                    ///< Socket receive error count
    uint32_t             socket_create_flag;                                         ///< Flag to determine in socket has been created.
    uint32_t             socket_read_write_flag;                                     ///< flag to determine if read and/or write channels are active.
} ulpgn_socket_t;

/** Silex ULPGN Wifi SCI UART state information */
typedef struct
{
    SemaphoreHandle_t uart_tei_sem;    ///< UART transmission end binary semaphore
} uart_state_t;

/** WIFI_ONCHIP_SILEX private control block. DO NOT MODIFY. */
typedef struct
{
    uint32_t open;                                                                           ///< Flag to indicate if wifi instance has been initialized
    wifi_onchip_silex_cfg_t const * p_wifi_onchip_silex_cfg;                                 ///< Pointer to initial configurations.
    bsp_io_port_pin_t               reset_pin;                                               ///< Wifi module reset pin
    uint32_t             num_uarts;                                                          ///< number of UARTS currently used for communication with module
    uint32_t             tx_data_size;                                                       ///< Size of the data to send
    uint32_t             num_creatable_sockets;                                              ///< Number of simultaneous sockets supported
    uint32_t             curr_cmd_port;                                                      ///< Current UART instance index for AT commands
    uint32_t             curr_data_port;                                                     ///< Current UART instance index for data
    uint8_t              cmd_rx_queue_buf[WIFI_ONCHIP_SILEX_CFG_CMD_RX_BUF_SIZE];            ///< Command port receive buffer used by byte queue
    StreamBufferHandle_t socket_byteq_hdl;                                                   ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                                ///< Structure to hold stream buffer info
    volatile uint32_t    curr_socket_index;                                                  ///< Currently active socket instance
    uint8_t              cmd_tx_buff[WIFI_ONCHIP_SILEX_CFG_CMD_TX_BUF_SIZE];                 ///< Command send buffer
    uint8_t              cmd_rx_buff[WIFI_ONCHIP_SILEX_CFG_CMD_RX_BUF_SIZE];                 ///< Command receive buffer
    uint32_t             at_cmd_mode;                                                        ///< Current command mode
    uint8_t              curr_ipaddr[4];                                                     ///< Current IP address of module
    uint8_t              curr_subnetmask[4];                                                 ///< Current Subnet Mask of module
    uint8_t              curr_gateway[4];                                                    ///< Current GAteway of module
    SemaphoreHandle_t    tx_sem;                                                             ///< Transmit binary semaphore handle
    SemaphoreHandle_t    rx_sem;                                                             ///< Receive binary semaphore handle
    uint8_t              last_data[WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH];                    ///< Tailing buffer used for command parser
    uart_instance_t    * uart_instance_objects[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS]; ///< UART instance objects
    uart_state_t         uart_state_info[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS];       ///< UART instance state information
    ulpgn_socket_t       sockets[WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS];              ///< Internal socket instances
} wifi_onchip_silex_instance_ctrl_t;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_open(wifi_onchip_silex_cfg_t const * const p_cfg);
fsp_err_t rm_wifi_onchip_silex_version_get(fsp_version_t * const p_version);
fsp_err_t rm_wifi_onchip_silex_close();
fsp_err_t rm_wifi_onchip_silex_connect(const char * p_ssid, uint32_t security, const char * p_passphrase);
fsp_err_t rm_wifi_onchip_silex_mac_addr_get(uint8_t * p_macaddr);
fsp_err_t rm_wifi_onchip_silex_scan(WIFIScanResult_t * p_results, uint32_t maxNetworks);
fsp_err_t rm_wifi_onchip_silex_ping(uint8_t * p_ip_addr, uint32_t count, uint32_t interval_ms);
fsp_err_t rm_wifi_onchip_silex_ip_addr_get(uint8_t * p_ip_addr);
fsp_err_t rm_wifi_onchip_silex_avail_socket_get(uint32_t * p_socket_id);
fsp_err_t rm_wifi_onchip_silex_socket_status_get(uint32_t socket_no, uint32_t * p_socket_status);
fsp_err_t rm_wifi_onchip_silex_socket_create(uint32_t socket_no, uint32_t type, uint32_t ipversion);
fsp_err_t rm_wifi_onchip_silex_tcp_connect(uint32_t socket_no, uint32_t ipaddr, uint32_t port);
int32_t   rm_wifi_onchip_silex_tcp_send(uint32_t socket_no, const uint8_t * p_data, uint32_t length,
                                        uint32_t timeout_ms);
int32_t   rm_wifi_onchip_silex_tcp_recv(uint32_t socket_no, uint8_t * p_data, uint32_t length, uint32_t timeout_ms);
int32_t   rm_wifi_onchip_silex_tcp_shutdown(uint32_t socket_no, uint32_t shutdown_channels);
fsp_err_t rm_wifi_onchip_silex_socket_disconnect(uint32_t socket_no);
fsp_err_t rm_wifi_onchip_silex_disconnect();
fsp_err_t rm_wifi_onchip_silex_dns_query(const char * p_textstring, uint8_t * p_ip_addr);
fsp_err_t rm_wifi_onchip_silex_socket_connected(fsp_err_t * p_status);

/*******************************************************************************************************************//**
 *  Callback function for first UART port in command mode. Used specifically for the SCI UART driver.
 *
 * @param[in]  p_args           Pointer to callback arguments structure.
 *
 **********************************************************************************************************************/
void rm_wifi_onchip_silex_uart_callback(uart_callback_args_t * p_args);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_WIFI_ONCHIP_SILEX_H

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_ONCHIP_SILEX)
 **********************************************************************************************************************/
