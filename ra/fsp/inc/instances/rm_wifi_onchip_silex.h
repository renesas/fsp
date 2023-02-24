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
#include "time.h"

#include "r_ioport_api.h"
#include "r_uart_api.h"

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
 #include "FreeRTOS.h"
 #include "semphr.h"
 #include "stream_buffer.h"
 #include "rm_wifi_config.h"
 #include "rm_wifi_api.h"
 #include "rm_wifi_onchip_silex_cfg.h"
#else                                  // Azure RTOS
 #include "tx_api.h"
 #include "rm_wifi_onchip_silex_cfg_azure.h"

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

/**
 * @brief Wi-Fi Security types.
 *
 * @ingroup WiFi_datatypes_enums
 */
typedef enum
{
    eWiFiSecurityOpen = 0,             /**< Open - No Security. */
    eWiFiSecurityWEP,                  /**< WEP Security. */
    eWiFiSecurityWPA,                  /**< WPA Security. */
    eWiFiSecurityWPA2,                 /**< WPA2 Security. */
    eWiFiSecurityWPA2_ent,             /**< WPA2 Enterprise Security. */
    eWiFiSecurityWPA3,                 /**< WPA3 Security. */
    eWiFiSecurityNotSupported          /**< Unknown Security. */
} WIFISecurity_t;

/**
 * @brief Wi-Fi scan results.
 *
 * Structure to store the Wi-Fi scan results.
 *
 * @note The size of char arrays are the MAX lengths + 1 to
 * account for possible null terminating at the end of the
 * strings.
 *
 * @see WIFI_Scan
 *
 * @ingroup WiFi_datatypes_returnstructs
 */
typedef struct
{
    uint8_t        ucSSID[wificonfigMAX_SSID_LEN];   /**< SSID of the Wi-Fi network (binary array, not C-string). */
    uint8_t        ucSSIDLength;                     /**< SSID length. */
    uint8_t        ucBSSID[wificonfigMAX_BSSID_LEN]; /**< BSSID of the Wi-Fi network (binary array, not C-string). */
    WIFISecurity_t xSecurity;                        /**< Security type of the Wi-Fi network. */
    int8_t         cRSSI;                            /**< Signal strength of the Wi-Fi network. */
    uint8_t        ucChannel;                        /**< Channel of the Wi-Fi network. */
} WIFIScanResult_t;

 #ifndef rm_wifi_onchip_silex_uart_callback
void rm_wifi_onchip_silex_uart_callback(uart_callback_args_t * p_args);

 #endif

#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH    (13 + 1) // Length of the tailing buffer used by command parser
#define SOCKETS_SOCK_DGRAM_RECV                 (3)
#define SOCKETS_IPPROTO_V4_SILEX                (4)
#define WIFI_ONCHIP_SILEX_UDP_TRANSMIT_TYPE     (0)
#define WIFI_ONCHIP_SILEX_UDP_RECEIVE_TYPE      (1)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Silex ULPGN Wifi socket status types */
typedef enum e_sx_ulpgn_socket_status
{
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_CLOSED = 0,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_SOCKET,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_BOUND,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_LISTEN,
    WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED,
} sx_ulpgn_socket_status_t;

/** Silex socket shutdown channels */
typedef enum e_sx_ulpgn_socket_rw
{
    WIFI_ONCHIP_SILEX_SOCKET_READ  = 1,
    WIFI_ONCHIP_SILEX_SOCKET_WRITE = 2,
} sx_ulpgn_socket_rw;

/** Silex WiFi module enable/disable for SNTP */
typedef enum e_wifi_onchip_silex_sntp_enable
{
    WIFI_ONCHIP_SILEX_SNTP_DISABLE = 0,
    WIFI_ONCHIP_SILEX_SNTP_ENABLE  = 1,
} wifi_onchip_silex_sntp_enable_t;

/** Silex WiFi module enable/disable for SNTP */
typedef enum e_wifi_onchip_silex_sntp_daylight_savings_enable
{
    WIFI_ONCHIP_SILEX_SNTP_DAYLIGHT_SAVINGS_DISABLE = 0,
    WIFI_ONCHIP_SILEX_SNTP_DAYLIGHT_SAVINGS_ENABLE  = 1,
} wifi_onchip_silex_sntp_daylight_savings_enable_t;

/** User configuration structure, used in open function */
typedef struct st_wifi_onchip_cfg
{
    const uint32_t                        num_uarts;                                                   ///< Number of UART interfaces to use
    const uint32_t                        num_sockets;                                                 ///< Number of sockets to initialize
    const bsp_io_port_pin_t               reset_pin;                                                   ///< Reset pin used for module
    const uart_instance_t               * uart_instances[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS]; ///< SCI UART instances
    const wifi_onchip_silex_sntp_enable_t sntp_enabled;                                                ///< Enable/Disable the SNTP Client
    const uint8_t                       * sntp_server_ip;                                              ///< The SNTP server IP address string
    const int32_t  sntp_timezone_offset_from_utc_hours;                                                ///< Timezone offset from UTC in (+/-) hours
    const uint32_t sntp_timezone_offset_from_utc_minutes;                                              ///< Timezone offset from UTC in minutes
    const wifi_onchip_silex_sntp_daylight_savings_enable_t sntp_timezone_use_daylight_savings;         ///< Enable/Disable use of daylight saving time.
    void const * p_context;                                                                            ///< User defined context passed into callback function.
    void const * p_extend;                                                                             ///< Pointer to extended configuration by instance of interface.
} wifi_onchip_silex_cfg_t;

/** Silex ULPGN Wifi internal socket instance structure */
typedef struct
{
#if (BSP_CFG_RTOS == 2)                                                              // FreeRTOS
    StreamBufferHandle_t socket_byteq_hdl;                                           ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                        ///< Structure to hold stream buffer info
    uint8_t              socket_recv_buff[WIFI_ONCHIP_SILEX_CFG_MAX_SOCKET_RX_SIZE]; ///< Socket receive buffer used by byte queue
#endif
    uint32_t socket_status;                                                          ///< Current socket status
    uint32_t socket_recv_error_count;                                                ///< Socket receive error count
    uint32_t socket_create_flag;                                                     ///< Flag to determine in socket has been created.
    uint32_t socket_read_write_flag;                                                 ///< flag to determine if read and/or write channels are active.
} ulpgn_socket_t;

/** WIFI_ONCHIP_SILEX private control block. DO NOT MODIFY. */
typedef struct
{
    uint32_t open;                                                                ///< Flag to indicate if wifi instance has been initialized
    wifi_onchip_silex_cfg_t const * p_wifi_onchip_silex_cfg;                      ///< Pointer to initial configurations.
    bsp_io_port_pin_t               reset_pin;                                    ///< Wifi module reset pin
    uint32_t num_uarts;                                                           ///< number of UARTS currently used for communication with module
    uint32_t tx_data_size;                                                        ///< Size of the data to send
    uint32_t num_creatable_sockets;                                               ///< Number of simultaneous sockets supported
    uint32_t curr_cmd_port;                                                       ///< Current UART instance index for AT commands
    uint32_t curr_data_port;                                                      ///< Current UART instance index for data

#if (BSP_CFG_RTOS == 2)
    uint8_t              cmd_rx_queue_buf[WIFI_ONCHIP_SILEX_CFG_CMD_RX_BUF_SIZE]; ///< Command port receive buffer used by byte queue                                           // FreeRTOS
    StreamBufferHandle_t socket_byteq_hdl;                                        ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                     ///< Structure to hold stream buffer info
#else // Azure RTOS
    uint8_t * p_current_packet_buffer;
    uint8_t * p_next_packet_buffer;
    uint32_t  packet_buffer_size;
    uint32_t  current_cmd_buffer_index;
#endif
    volatile uint32_t curr_socket_index;                                  ///< Currently active socket instance
    uint8_t           cmd_tx_buff[WIFI_ONCHIP_SILEX_CFG_CMD_TX_BUF_SIZE]; ///< Command send buffer
    uint8_t           cmd_rx_buff[WIFI_ONCHIP_SILEX_CFG_CMD_RX_BUF_SIZE]; ///< Command receive buffer
    uint32_t          at_cmd_mode;                                        ///< Current command mode
    uint8_t           curr_ipaddr[4];                                     ///< Current IP address of module
    uint8_t           curr_subnetmask[4];                                 ///< Current Subnet Mask of module
    uint8_t           curr_gateway[4];                                    ///< Current GAteway of module
#if (BSP_CFG_RTOS == 2)                                                   // FreeRTOS
    SemaphoreHandle_t tx_sem;                                             ///< Transmit binary semaphore handle
    SemaphoreHandle_t rx_sem;                                             ///< Receive binary semaphore handle
#else // Azure RTOS
    TX_MUTEX tx_sem;
    TX_MUTEX rx_sem;
#endif
    uint8_t           last_data[WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH];                    ///< Tailing buffer used for command parser
    uart_instance_t * uart_instance_objects[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS]; ///< UART instance objects
#if (BSP_CFG_RTOS == 2)                                                                   // FreeRTOS
    SemaphoreHandle_t uart_tei_sem[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS];          ///< UART transmission end binary semaphore
#else // Azure RTOS
    TX_SEMAPHORE uart_tei_sem[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS];
    TX_SEMAPHORE uart_rx_sem[WIFI_ONCHIP_SILEX_CFG_MAX_NUMBER_UART_PORTS];
    TX_SEMAPHORE uart_data_rx_start_sem;
#endif
    ulpgn_socket_t sockets[WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS]; ///< Internal socket instances
} wifi_onchip_silex_instance_ctrl_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_ONCHIP_SILEX)
 **********************************************************************************************************************/

extern const wifi_onchip_silex_cfg_t g_wifi_onchip_silex_cfg;
extern const char * g_wifi_onchip_silex_uart_cmd_baud;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_open(wifi_onchip_silex_cfg_t const * const p_cfg);
fsp_err_t rm_wifi_onchip_silex_close();
fsp_err_t rm_wifi_onchip_silex_connect(const char * p_ssid, WIFISecurity_t security, const char * p_passphrase);
fsp_err_t rm_wifi_onchip_silex_mac_addr_get(uint8_t * p_macaddr);
fsp_err_t rm_wifi_onchip_silex_scan(WIFIScanResult_t * p_results, uint32_t maxNetworks);
fsp_err_t rm_wifi_onchip_silex_ping(uint8_t * p_ip_addr, uint32_t count, uint32_t interval_ms);
fsp_err_t rm_wifi_onchip_silex_ip_addr_get(uint32_t * p_ip_addr);
fsp_err_t rm_wifi_onchip_silex_network_info_get(uint32_t * p_ip_addr, uint32_t * p_subnet_mask, uint32_t * p_gateway);
fsp_err_t rm_wifi_onchip_silex_avail_socket_get(uint32_t * p_socket_id);
fsp_err_t rm_wifi_onchip_silex_socket_status_get(uint32_t socket_no, uint32_t * p_socket_status);
fsp_err_t rm_wifi_onchip_silex_socket_create(uint32_t socket_no, uint32_t type, uint32_t ipversion);
fsp_err_t rm_wifi_onchip_silex_tcp_connect(uint32_t socket_no, uint32_t ipaddr, uint32_t port);
fsp_err_t rm_wifi_onchip_silex_udp_connect(uint32_t socket_no, uint32_t ipaddr, uint32_t port, uint32_t type);
int32_t   rm_wifi_onchip_silex_send(uint32_t socket_no, const uint8_t * p_data, uint32_t length, uint32_t timeout_ms);
int32_t   rm_wifi_onchip_silex_recv(uint32_t socket_no, uint8_t * p_data, uint32_t length, uint32_t timeout_ms);
int32_t   rm_wifi_onchip_silex_tcp_shutdown(uint32_t socket_no, uint32_t shutdown_channels);
fsp_err_t rm_wifi_onchip_silex_socket_disconnect(uint32_t socket_no);
fsp_err_t rm_wifi_onchip_silex_disconnect();
fsp_err_t rm_wifi_onchip_silex_dns_query(const char * p_textstring, uint8_t * p_ip_addr);
fsp_err_t rm_wifi_onchip_silex_socket_connected(fsp_err_t * p_status);
void      rm_wifi_onchip_silex_uart_callback(uart_callback_args_t * p_args);

#if (BSP_CFG_RTOS == 1)
void rm_wifi_onchip_silex_initialize_packet_buffers(uint8_t * p_current_packet_buffer,
                                                    uint8_t * p_next_packet_buffer,
                                                    uint32_t  packet_buffer_size);
void      rm_wifi_onchip_silex_set_next_packet_buffer(uint8_t * p_next_packet_buffer);
void      rm_wifi_onchip_silex_move_to_next_packet_buffer(void);
fsp_err_t rm_wifi_onchip_silex_change_socket(uint32_t socket_no);
fsp_err_t rm_wifi_onchip_silex_stop_tcp_recv(uint32_t * bytes_received);
UINT      rm_wifi_onchip_silex_get_rx_start_semaphore(ULONG wait_option);
UINT      rm_wifi_onchip_silex_get_rx_complete_semaphore(ULONG wait_option);
uint32_t  rm_wifi_onchip_silex_get_current_socket_index();

#endif

/*******************************************************************************************************************//**
 * @addtogroup WIFI_ONCHIP_SILEX WIFI_ONCHIP_SILEX
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Get the current system time as the number of seconds since epoch 1970-01-01 00:00:00 UTC
 *
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_EpochTimeGet(time_t * p_utc_time);

/*******************************************************************************************************************//**
 *  Get the current local time based on current timezone in a string format
 *
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_LocalTimeGet(uint8_t * p_local_time, uint32_t size_string);

/*******************************************************************************************************************//**
 *  Enable or Disable the SNTP Client Service
 *
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_SntpEnableSet(wifi_onchip_silex_sntp_enable_t enable);

/*******************************************************************************************************************//**
 *  Update the SNTP Server IP Address
 *
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_SntpServerIpAddressSet(uint8_t * p_ip_address);

/*******************************************************************************************************************//**
 *  Update the SNTP Timezone
 *
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_SntpTimeZoneSet(int32_t                                          hours,
                                               uint32_t                                         minutes,
                                               wifi_onchip_silex_sntp_daylight_savings_enable_t daylightSavingsEnable);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_WIFI_ONCHIP_SILEX_H

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_ONCHIP_SILEX)
 **********************************************************************************************************************/
