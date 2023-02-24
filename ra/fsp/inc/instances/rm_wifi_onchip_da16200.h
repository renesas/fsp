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
 * @addtogroup WIFI_ONCHIP_DA16200 WIFI_ONCHIP_DA16200
 * @{
 **********************************************************************************************************************/
#ifndef RM_WIFI_ONCHIP_DA16200_H
 #define RM_WIFI_ONCHIP_DA16200_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "bsp_api.h"
 #include "time.h"

 #include "r_ioport_api.h"
 #include "r_ioport.h"
 #include "r_uart_api.h"

 #include "FreeRTOS.h"
 #include "semphr.h"
 #include "stream_buffer.h"
 #include "rm_wifi_config.h"
 #include "rm_wifi_api.h"
 #include "rm_wifi_onchip_da16200_cfg.h"

/**
 * @brief Max SSID length
 */
 #ifndef wificonfigMAX_SSID_LEN
  #define wificonfigMAX_SSID_LEN          32
 #endif

/**
 * @brief Max BSSID length
 */
 #ifndef wificonfigMAX_BSSID_LEN
  #define wificonfigMAX_BSSID_LEN         6
 #endif

/**
 * @brief Max passphrase length
 */
 #ifndef wificonfigMAX_PASSPHRASE_LEN
  #define wificonfigMAX_PASSPHRASE_LEN    32
 #endif

 #ifndef rm_wifi_onchip_da16200_uart_callback
void rm_wifi_onchip_da16200_uart_callback(uart_callback_args_t * p_args);

 #endif

#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Encryption Type supported by DA16200 module */
#define WIFI_ONCHIP_DA16200_TKIP_ENC_TYPE        (0)
#define WIFI_ONCHIP_DA16200_AES_ENC_TYPE         (1)
#define WIFI_ONCHIP_DA16200_TKIP_AES_ENC_TYPE    (2)

#define SOCKETS_IPPROTO_V4_DA16200               (4)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DA16200 WiFi module enable/disable for SNTP */
typedef enum e_wifi_onchip_da16200_sntp_enable
{
    WIFI_ONCHIP_DA16200_SNTP_DISABLE = 0,
    WIFI_ONCHIP_DA16200_SNTP_ENABLE  = 1
} wifi_onchip_da16200_sntp_enable_t;

/** DA16200 Wifi socket status types */
typedef enum e_da16200_socket_status
{
    WIFI_ONCHIP_DA16200_SOCKET_STATUS_CLOSED = 0,
    WIFI_ONCHIP_DA16200_SOCKET_STATUS_SOCKET,
    WIFI_ONCHIP_DA16200_SOCKET_STATUS_BOUND,
    WIFI_ONCHIP_DA16200_SOCKET_STATUS_LISTEN,
    WIFI_ONCHIP_DA16200_SOCKET_STATUS_CONNECTED
} da16200_socket_status_t;

/** DA16200 socket shutdown channels */
typedef enum e_da16200_socket_rw
{
    WIFI_ONCHIP_DA16200_SOCKET_READ  = 1,
    WIFI_ONCHIP_DA16200_SOCKET_WRITE = 2
} da16200_socket_rw;

/** DA16200 socket receive state */
typedef enum e_da16200_recv_state
{
    WIFI_ONCHIP_DA16200_RECV_PREFIX,     // +
    WIFI_ONCHIP_DA16200_RECV_CMD,        // command
    WIFI_ONCHIP_DA16200_RECV_SUFFIX,     // :
    WIFI_ONCHIP_DA16200_RECV_PARAM_CID,  // cid parameter
    WIFI_ONCHIP_DA16200_RECV_PARAM_IP,   // ip parameter
    WIFI_ONCHIP_DA16200_RECV_PARAM_PORT, // port parameter
    WIFI_ONCHIP_DA16200_RECV_PARAM_LEN,  // length parameter
    WIFI_ONCHIP_DA16200_RECV_DATA
} da16200_recv_state;

/** DA16200 WiFi module enable/disable for SNTP Daylight */
typedef enum e_wifi_onchip_da16200_sntp_daylight_savings_enable
{
    WIFI_ONCHIP_DA16200_SNTP_DAYLIGHT_SAVINGS_DISABLE = 0,
    WIFI_ONCHIP_DA16200_SNTP_DAYLIGHT_SAVINGS_ENABLE  = 1,
} wifi_onchip_da16200_sntp_daylight_savings_enable_t;

/** User configuration structure, used in open function */
typedef struct st_wifi_onchip_cfg
{
    const uint32_t          num_uarts;                                                     ///< Number of UART interfaces to use
    const uint32_t          num_sockets;                                                   ///< Number of sockets to initialize
    const uint8_t         * country_code;                                                  ///< Country code defined in ISO3166-1 alpha-2 standard
    const bsp_io_port_pin_t reset_pin;                                                     ///< Reset pin used for module
    const uart_instance_t * uart_instances[WIFI_ONCHIP_DA16200_CFG_MAX_NUMBER_UART_PORTS]; ///< SCI UART instances
    const uint8_t         * sntp_server_ip;                                                ///< The SNTP server IP address string
    const int32_t           sntp_utc_offset_in_hours;                                      ///< Timezone offset in secs (-43200 - 43200)
    void const            * p_context;                                                     ///< User defined context passed into callback function.
    void const            * p_extend;                                                      ///< Pointer to extended configuration by instance of interface.
} wifi_onchip_da16200_cfg_t;

/** DA16200 Wifi internal socket instance structure */
typedef struct
{
    uint8_t            remote_ipaddr[4];                                               ///< Remote IP address
    int                remote_port;                                                    ///< Remote Port
    int                socket_recv_data_len;                                           ///< Data length of incoming socket data
    int                socket_type;                                                    ///< Socket type (TCP Server | TCP Client | UDP)
    uint32_t           socket_status;                                                  ///< Current socket status
    uint32_t           socket_recv_error_count;                                        ///< Socket receive error count
    uint32_t           socket_create_flag;                                             ///< Flag to determine in socket has been created.
    uint32_t           socket_read_write_flag;                                         ///< flag to determine if read and/or write channels are active.
    da16200_recv_state socket_recv_state;                                              ///< Incoming Socket data header information

    StreamBufferHandle_t socket_byteq_hdl;                                             ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                          ///< Structure to hold stream buffer info
    uint8_t              socket_recv_buff[WIFI_ONCHIP_DA16200_CFG_MAX_SOCKET_RX_SIZE]; ///< Socket receive buffer used by byte queue
} da16200_socket_t;

/** WIFI_ONCHIP_DA16200 private control block. DO NOT MODIFY. */
typedef struct st_wifi_onchip_da16200_instance_ctrl
{
    wifi_onchip_da16200_cfg_t const * p_wifi_onchip_da16200_cfg;                            ///< Pointer to initial configurations.
    bsp_io_port_pin_t                 reset_pin;                                            ///< Wifi module reset pin
    uint32_t num_uarts;                                                                     ///< number of UARTS currently used for communication with module
    uint32_t num_creatable_sockets;                                                         ///< Number of simultaneous sockets supported
    uint32_t tx_data_size;                                                                  ///< Size of the data to send
    uint32_t curr_cmd_port;                                                                 ///< Current UART instance index for AT commands
    uint32_t open;                                                                          ///< Flag to indicate if wifi instance has been initialized
    uint8_t  is_sntp_enabled;                                                               ///< Flag to indicate Enable/Disable of SNTP Client

    uint8_t              cmd_rx_queue_buf[WIFI_ONCHIP_DA16200_CFG_CMD_RX_BUF_SIZE];         ///< Command port receive buffer used by byte queue                                           // FreeRTOS
    StreamBufferHandle_t socket_byteq_hdl;                                                  ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                               ///< Structure to hold stream buffer info

    volatile uint32_t curr_socket_index;                                                    ///< Currently active socket instance
    uint8_t           cmd_tx_buff[WIFI_ONCHIP_DA16200_CFG_CMD_TX_BUF_SIZE];                 ///< Command send buffer
    uint8_t           cmd_rx_buff[WIFI_ONCHIP_DA16200_CFG_CMD_RX_BUF_SIZE];                 ///< Command receive buffer
    uint8_t           curr_ipaddr[4];                                                       ///< Current IP address of module
    uint8_t           curr_subnetmask[4];                                                   ///< Current Subnet Mask of module
    uint8_t           curr_gateway[4];                                                      ///< Current GAteway of module

    SemaphoreHandle_t tx_sem;                                                               ///< Transmit binary semaphore handle
    SemaphoreHandle_t rx_sem;                                                               ///< Receive binary semaphore handle

    uart_instance_t * uart_instance_objects[WIFI_ONCHIP_DA16200_CFG_MAX_NUMBER_UART_PORTS]; ///< UART instance object
    SemaphoreHandle_t uart_tei_sem[WIFI_ONCHIP_DA16200_CFG_MAX_NUMBER_UART_PORTS];          ///< UART transmission end binary semaphore
    da16200_socket_t  sockets[WIFI_ONCHIP_DA16200_CFG_NUM_CREATEABLE_SOCKETS];              ///< Internal socket instances
} wifi_onchip_da16200_instance_ctrl_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_ONCHIP_DA16200)
 **********************************************************************************************************************/

extern const wifi_onchip_da16200_cfg_t g_wifi_onchip_da16200_cfg;
extern const char * g_wifi_onchip_da16200_uart_cmd_baud;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_da16200_open(wifi_onchip_da16200_cfg_t const * const p_cfg);
fsp_err_t rm_wifi_onchip_da16200_close(void);
fsp_err_t rm_wifi_onchip_da16200_disconnect(void);
fsp_err_t rm_wifi_onchip_da16200_connected(fsp_err_t * p_status);
fsp_err_t rm_wifi_onchip_da16200_network_info_get(uint32_t * p_ip_addr, uint32_t * p_subnet_mask, uint32_t * p_gateway);
fsp_err_t rm_wifi_onchip_da16200_connect(const char   * p_ssid,
                                         WIFISecurity_t security,
                                         const char   * p_passphrase,
                                         uint8_t        enc_type);
fsp_err_t rm_wifi_onchip_da16200_mac_addr_get(uint8_t * p_macaddr);
fsp_err_t rm_wifi_onchip_da16200_scan(WIFIScanResult_t * p_results, uint32_t maxNetworks);
fsp_err_t rm_wifi_onchip_da16200_ping(uint8_t * p_ip_addr, int count, uint32_t interval_ms);
fsp_err_t rm_wifi_onchip_da16200_ipaddr_get(uint32_t * p_ip_addr);
fsp_err_t rm_wifi_onchip_da16200_dns_query(const char * p_textstring, uint8_t * p_ip_addr);

/* TCP Socket public function prototypes */
fsp_err_t rm_wifi_onchip_da16200_avail_socket_get(uint32_t * p_socket_id);
fsp_err_t rm_wifi_onchip_da16200_socket_status_get(uint32_t socket_no, uint32_t * p_socket_status);
fsp_err_t rm_wifi_onchip_da16200_socket_create(uint32_t socket_no, uint32_t type, uint32_t ipversion);
fsp_err_t rm_wifi_onchip_da16200_tcp_connect(uint32_t socket_no, uint32_t ipaddr, uint32_t port);
int32_t   rm_wifi_onchip_da16200_send(uint32_t socket_no, const uint8_t * p_data, uint32_t length, uint32_t timeout_ms);
int32_t   rm_wifi_onchip_da16200_recv(uint32_t socket_no, uint8_t * p_data, uint32_t length, uint32_t timeout_ms);
fsp_err_t rm_wifi_onchip_da16200_socket_disconnect(uint32_t socket_no);

#ifndef rm_wifi_onchip_da16200_uart_callback
void rm_wifi_onchip_da16200_uart_callback(uart_callback_args_t * p_args);

#endif

/**********************************************************************************************************************************//**
 * @addtogroup WIFI_ONCHIP_DA16200 WIFI_ONCHIP_DA16200
 * @{
 *************************************************************************************************************************************/

/**********************************************************************************************************************************//**
 *  Update the SNTP Server IP Address
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_DA16200_SntpServerIpAddressSet(uint8_t * p_server_ip_addr);

/**********************************************************************************************************************************//**
 *  Enable or Disable the SNTP Client Service
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_DA16200_SntpEnableSet(wifi_onchip_da16200_sntp_enable_t enable);

/**********************************************************************************************************************************//**
 *  Update the SNTP Timezone
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_DA16200_SntpTimeZoneSet(int                                                utc_offset_in_hours,
                                                 uint32_t                                           minutes,
                                                 wifi_onchip_da16200_sntp_daylight_savings_enable_t daylightSavingsEnable);

/**********************************************************************************************************************************//**
 *  Get the current local time based on current timezone in a string format
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_DA16200_LocalTimeGet(uint8_t * p_local_time, uint32_t size_string);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_ONCHIP_DA16200)
 **********************************************************************************************************************/
