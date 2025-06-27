/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup WIFI_DA16XXX WIFI_DA16XXX
 * @{
 **********************************************************************************************************************/
#ifndef RM_WIFI_DA16XXX_H
#define RM_WIFI_DA16XXX_H

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

/* DA16XXX transport includes. */
#include "rm_at_transport_da16xxx.h"
#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */
 #include "FreeRTOS.h"
 #include "semphr.h"
 #include "stream_buffer.h"
 #include "rm_wifi_config.h"
#endif
#include "rm_wifi_api.h"
#include "rm_wifi_da16xxx_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Encryption Type supported by DA16XXX module */
#define WIFI_DA16XXX_TKIP_ENC_TYPE        (0)
#define WIFI_DA16XXX_AES_ENC_TYPE         (1)
#define WIFI_DA16XXX_TKIP_AES_ENC_TYPE    (2)

#define SOCKETS_IPPROTO_V4_DA16XXX        (4)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DA16XXX WiFi module enable/disable for SNTP */
typedef enum e_wifi_da16xxx_sntp_enable
{
    WIFI_DA16XXX_SNTP_DISABLE = 0,
    WIFI_DA16XXX_SNTP_ENABLE  = 1
} wifi_da16xxx_sntp_enable_t;
#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */
/** DA16XXX Wifi socket status types */
typedef enum e_da16xxx_socket_status
{
    WIFI_DA16XXX_SOCKET_STATUS_CLOSED = 0,
    WIFI_DA16XXX_SOCKET_STATUS_SOCKET,
    WIFI_DA16XXX_SOCKET_STATUS_BOUND,
    WIFI_DA16XXX_SOCKET_STATUS_LISTEN,
    WIFI_DA16XXX_SOCKET_STATUS_CONNECTED
} da16xxx_socket_status_t;

/** DA16XXX socket shutdown channels */
typedef enum e_da16xxx_socket_rw
{
    WIFI_DA16XXX_SOCKET_READ  = 1,
    WIFI_DA16XXX_SOCKET_WRITE = 2
} da16xxx_socket_rw;

/** DA16XXX socket receive state */
typedef enum e_da16xxx_recv_state
{
    WIFI_DA16XXX_RECV_PREFIX,          // +
    WIFI_DA16XXX_RECV_CMD,             // command
    WIFI_DA16XXX_RECV_SUFFIX,          // :
    WIFI_DA16XXX_RECV_PARAM_CID,       // cid parameter
    WIFI_DA16XXX_RECV_PARAM_IP,        // ip parameter
    WIFI_DA16XXX_RECV_PARAM_PORT,      // port parameter
    WIFI_DA16XXX_RECV_PARAM_LEN,       // length parameter
    WIFI_DA16XXX_RECV_DATA
} da16xxx_recv_state;
#endif

/** DA16XXX WiFi module enable/disable for SNTP Daylight */
typedef enum e_wifi_da16xxx_sntp_daylight_savings_enable
{
    WIFI_DA16XXX_SNTP_DAYLIGHT_SAVINGS_DISABLE = 0,
    WIFI_DA16XXX_SNTP_DAYLIGHT_SAVINGS_ENABLE  = 1,
} wifi_da16xxx_sntp_daylight_savings_enable_t;

/** User configuration structure, used in open function */
typedef struct st_wifi_cfg
{
    at_transport_da16xxx_instance_t const * p_transport_instance;
    const uint32_t  num_sockets;                                                ///< Number of sockets to initialize
    const uint8_t * country_code;                                               ///< Country code defined in ISO3166-1 alpha-2 standard
    const uint8_t * sntp_server_ip;                                             ///< The SNTP server IP address string
    const int32_t   sntp_utc_offset_in_hours;                                   ///< Timezone offset in secs (-43200 - 43200)
    void          * p_context;                                                  ///< User defined context passed into callback function.
    void const    * p_extend;                                                   ///< Pointer to extended configuration by instance of interface.
} wifi_da16xxx_cfg_t;

#if (BSP_CFG_RTOS == 2)                                                         /* FreeRTOS */
/** DA16XXX Wifi internal socket instance structure */
typedef struct
{
    uint8_t            remote_ipaddr[4];                                        ///< Remote IP address
    int                remote_port;                                             ///< Remote Port
    int                socket_recv_data_len;                                    ///< Data length of incoming socket data
    int                socket_type;                                             ///< Socket type (TCP Server | TCP Client | UDP)
    uint32_t           socket_status;                                           ///< Current socket status
    uint32_t           socket_recv_error_count;                                 ///< Socket receive error count
    uint32_t           socket_create_flag;                                      ///< Flag to determine in socket has been created.
    uint32_t           socket_read_write_flag;                                  ///< flag to determine if read and/or write channels are active.
    da16xxx_recv_state socket_recv_state;                                       ///< Incoming Socket data header information

    StreamBufferHandle_t socket_byteq_hdl;                                      ///< Socket stream buffer handle
    StaticStreamBuffer_t socket_byteq_struct;                                   ///< Structure to hold stream buffer info
    uint8_t              socket_recv_buff[WIFI_DA16XXX_CFG_MAX_SOCKET_RX_SIZE]; ///< Socket receive buffer used by byte queue
} da16xxx_socket_t;
#endif

/** WIFI_DA16XXX private control block. DO NOT MODIFY. */
typedef struct st_wifi_da16xxx_instance_ctrl
{
    wifi_da16xxx_cfg_t const * p_wifi_da16xxx_cfg;                     ///< Pointer to initial configurations.
    uint32_t num_creatable_sockets;                                    ///< Number of simultaneous sockets supported
    uint32_t curr_socket;                                              ///< Current Socket index for AT commands
    uint32_t open;                                                     ///< Flag to indicate if wifi instance has been initialized
    uint8_t  is_sntp_enabled;                                          ///< Flag to indicate Enable/Disable of SNTP Client

    uint8_t cmd_tx_buff[WIFI_DA16XXX_CFG_CMD_TX_BUF_SIZE];             ///< Command send buffer
    uint8_t cmd_rx_buff[WIFI_DA16XXX_CFG_CMD_RX_BUF_SIZE];             ///< Command receive buffer

    volatile uint32_t curr_socket_index;                               ///< Currently active socket instance
    uint8_t           curr_ipaddr[4];                                  ///< Current IP address of module
    uint8_t           curr_subnetmask[4];                              ///< Current Subnet Mask of module
    uint8_t           curr_gateway[4];                                 ///< Current GAteway of module
#if (BSP_CFG_RTOS == 2)                                                /* FreeRTOS */
    da16xxx_socket_t sockets[WIFI_DA16XXX_CFG_NUM_CREATEABLE_SOCKETS]; ///< Internal socket instances
#endif
} wifi_da16xxx_instance_ctrl_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_DA16XXX)
 **********************************************************************************************************************/

extern const wifi_da16xxx_cfg_t g_wifi_da16xxx_cfg;
extern bool rm_wifi_da16xxx_callback(at_transport_da16xxx_callback_args_t * p_args);

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_open(wifi_da16xxx_cfg_t const * const p_cfg);
fsp_err_t rm_wifi_da16xxx_close(void);
fsp_err_t rm_wifi_da16xxx_disconnect(void);
fsp_err_t rm_wifi_da16xxx_connected(fsp_err_t * p_status);
fsp_err_t rm_wifi_da16xxx_network_info_get(uint32_t * p_ip_addr, uint32_t * p_subnet_mask, uint32_t * p_gateway);
fsp_err_t rm_wifi_da16xxx_connect(const char   * p_ssid,
                                  WIFISecurity_t security,
                                  const char   * p_passphrase,
                                  uint8_t        enc_type);
fsp_err_t rm_wifi_da16xxx_mac_addr_get(uint8_t * p_macaddr);
fsp_err_t rm_wifi_da16xxx_scan(WIFIScanResult_t * p_results, uint32_t maxNetworks);
fsp_err_t rm_wifi_da16xxx_ping(uint8_t * p_ip_addr, int count, uint32_t interval_ms);
fsp_err_t rm_wifi_da16xxx_ipaddr_get(uint32_t * p_ip_addr);
fsp_err_t rm_wifi_da16xxx_dns_query(const char * p_textstring, uint8_t * p_ip_addr);

#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */
/* TCP Socket public function prototypes */
fsp_err_t rm_wifi_da16xxx_avail_socket_get(uint32_t * p_socket_id);
fsp_err_t rm_wifi_da16xxx_socket_status_get(uint32_t socket_no, uint32_t * p_socket_status);
fsp_err_t rm_wifi_da16xxx_socket_create(uint32_t socket_no, uint32_t type, uint32_t ipversion);
fsp_err_t rm_wifi_da16xxx_tcp_connect(uint32_t socket_no, uint32_t ipaddr, uint32_t port);
int32_t   rm_wifi_da16xxx_send(uint32_t socket_no, const uint8_t * p_data, uint32_t length, uint32_t timeout_ms);
int32_t   rm_wifi_da16xxx_recv(uint32_t socket_no, uint8_t * p_data, uint32_t length, uint32_t timeout_ms);
fsp_err_t rm_wifi_da16xxx_socket_disconnect(uint32_t socket_no);

#endif

/**********************************************************************************************************************************//**
 * @addtogroup WIFI_DA16XXX WIFI_DA16XXX
 * @{
 *************************************************************************************************************************************/

/**********************************************************************************************************************************//**
 *  Update the SNTP Server IP Address
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_SntpServerIpAddressSet(uint8_t * p_server_ip_addr);

/**********************************************************************************************************************************//**
 *  Enable or Disable the SNTP Client Service
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_SntpEnableSet(wifi_da16xxx_sntp_enable_t enable);

/**********************************************************************************************************************************//**
 *  Send a generic AT command to the DA16XXX and optionally receive a response
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_GenericAtSendRcv(char const * const at_string, char * const response_buffer, uint32_t length);

/**********************************************************************************************************************************//**
 *  Update the SNTP Timezone
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_SntpTimeZoneSet(int                                         utc_offset_in_hours,
                                          uint32_t                                    minutes,
                                          wifi_da16xxx_sntp_daylight_savings_enable_t daylightSavingsEnable);

/**********************************************************************************************************************************//**
 *  Get the current local time based on current timezone in a string format
 *
 *************************************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_LocalTimeGet(uint8_t * p_local_time, uint32_t size_string);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_WIFI_DA16XXX_H

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_DA16XXX)
 **********************************************************************************************************************/
