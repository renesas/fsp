/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup MQTT_ONCHIP_DA16XXX MQTT_ONCHIP_DA16XXX
 * @{
 **********************************************************************************************************************/

#ifndef RM_MQTT_ONCHIP_DA16XXX_H_
#define RM_MQTT_ONCHIP_DA16XXX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rm_wifi_da16xxx.h"
#include "rm_at_transport_da16xxx.h"
#include "rm_mqtt_onchip_da16xxx_cfg.h"

#define MQTT_ONCHIP_DA16XXX_MAX_ALPN                (3)    ///< Maximum number of ALPNs supported by DA16XXX.
#define MQTT_ONCHIP_DA16XXX_MAX_SNI_LEN             (64)   ///< Maximum length of SNI supported by DA16XXX.
#define MQTT_ONCHIP_DA16XXX_TLS_CIPHER_SUITE_MAX    (17)   ///< Maximum number of TLS cipher suites supported by DA16XXX.
#define MQTT_ONCHIP_DA16XXX_TLS_CIPHER_MAX_CNT      (17)   ///< Maximum number of TLS cipher suites supported by DA16XXX.
#define MQTT_ONCHIP_DA16XXX_MAX_TOPIC_LEN           (64)   ///< Maximum total length for topics supported by DA16XXX.
#define MQTT_ONCHIP_DA16XXX_MAX_PUBMSG_LEN          (2048) ///< Maximum total length for message supported by DA16XXX.
#define MQTT_ONCHIP_DA16XXX_MAX_PUBTOPICMSG_LEN     (2063) ///< Maximum total length for message + topic supported by DA16XXX.
#define MQTT_ONCHIP_DA16XXX_SUBTOPIC_MAX_CNT        (32)   ///< Maximum number of subscription topics allowed.

/** MQTT Quality-of-service (QoS) levels */
typedef enum e_mqtt_onchip_da16xxx_qos
{
    MQTT_ONCHIP_DA16XXX_QOS_0 = 0,     ///< Delivery at most once.
    MQTT_ONCHIP_DA16XXX_QOS_1 = 1,     ///< Delivery at least once.
    MQTT_ONCHIP_DA16XXX_QOS_2 = 2      ///< Delivery exactly once.
} mqtt_onchip_da16xxx_qos_t;

/** MQTT TLS Cipher Suites */
typedef enum e_mqtt_onchip_da16xxx_tls_cipher_suites
{
    TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA      = 0xC011, ///< TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA protocol.
    TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA      = 0xC014, ///< TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA protocol.
    TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256   = 0xC027, ///< TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 protocol.
    TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384   = 0xC028, ///< TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 protocol.
    TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256   = 0xC02F, ///< TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 protocol.
    TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384   = 0xC030, ///< TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 protocol.
    TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA    = 0xC009, ///< TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA protocol.
    TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA    = 0xC00A, ///< TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA protocol.
    TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 = 0xC023, ///< TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 protocol.
    TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 = 0xC024, ///< TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 protocol.
    TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 = 0xC02B, ///< TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 protocol.
    TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 = 0xC02C, ///< TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 protocol.
} mqtt_onchip_da16xxx_tls_cipher_suites_t;

/** MQTT SUBSCRIBE packet parameters */
typedef struct st_mqtt_onchip_da16xxx_sub_info
{
    mqtt_onchip_da16xxx_qos_t qos;            ///< Quality of Service for subscription.
    const char              * p_topic_filter; ///< Topic filter to subscribe to.
    uint16_t topic_filter_length;             ///< Length of subscription topic filter.
} mqtt_onchip_da16xxx_sub_info_t;

/** MQTT PUBLISH packet parameters */
typedef struct st_mqtt_onchip_da16xxx_pub_info
{
    mqtt_onchip_da16xxx_qos_t qos;          ///< Quality of Service for subscription.
    const char              * p_topic_name; ///< Topic name on which the message is published.
    uint16_t     topic_name_Length;         ///< Length of topic name.
    const char * p_payload;                 ///< Message payload.
    uint32_t     payload_length;            ///< Message payload length.
} mqtt_onchip_da16xxx_pub_info_t;

/** MQTT Packet info structure to be passed to user callback */
typedef struct st_mqtt_onchip_da16xxx_callback_args
{
    uint8_t    * p_data;               ///< Payload received from subscribed MQTT topic.
    const char * p_topic;              ///< Topic to which the message payload belongs to.
    uint32_t     data_length;          ///< Length of the MQTT payload.
    void       * p_context;            ///< Placeholder for user data.
} mqtt_onchip_da16xxx_callback_args_t;

/** MQTT Configuration */
typedef struct st_mqtt_onchip_da16xxx_cfg
{
    at_transport_da16xxx_instance_t const * p_transport_instance;
    const uint8_t  use_mqtt_v311;                                                                        ///< Flag to use MQTT v3.1.1.
    const uint16_t rx_timeout;                                                                           ///< MQTT Rx timeout in milliseconds.
    const uint16_t tx_timeout;                                                                           ///< MQTT Tx timeout in milliseconds.

    void (* p_callback)(mqtt_onchip_da16xxx_callback_args_t * p_args);                                   ///< Location of user callback.
    void       * p_context;                                                                              ///< Placeholder for user data. Passed to the user callback in mqtt_onchip_da16xxx_callback_args_t.
    uint8_t      clean_session;                                                                          ///< Whether to establish a new, clean session or resume a previous session.
    uint8_t      alpn_count;                                                                             ///< ALPN Protocols count. Max value is 3.
    const char * p_alpns[MQTT_ONCHIP_DA16XXX_MAX_ALPN];                                                  ///< ALPN Protocols.
    uint8_t      tls_cipher_count;                                                                       ///< TLS Cipher suites count. Max value is 17.
    uint16_t     keep_alive_seconds;                                                                     ///< MQTT keep alive period.
    const char * p_client_identifier;                                                                    ///< MQTT Client identifier. Must be unique per client.
    uint16_t     client_identifier_length;                                                               ///< Length of the client identifier.
    const char * p_host_name;                                                                            ///< MQTT endpoint host name.
    uint16_t     mqtt_port;                                                                              ///< MQTT Port number.
    const char * p_mqtt_user_name;                                                                       ///< MQTT user name. Set to NULL if not used.
    uint16_t     user_name_length;                                                                       ///< Length of MQTT user name. Set to 0 if not used.
    const char * p_mqtt_password;                                                                        ///< MQTT password. Set to NULL if not used.
    uint16_t     password_length;                                                                        ///< Length of MQTT password. Set to 0 if not used.
    const char * p_root_ca;                                                                              ///< String representing a trusted server root certificate.
    uint32_t     root_ca_size;                                                                           ///< Size associated with root CA Certificate.
    const char * p_client_cert;                                                                          ///< String representing a Client certificate.
    uint32_t     client_cert_size;                                                                       ///< Size associated with Client certificate.
    const char * p_client_private_key;                                                                   ///< String representing Client Private Key.
    uint32_t     private_key_size;                                                                       ///< Size associated with Client Private Key.
    const char * p_will_topic;                                                                           ///< String representing Will Topic.
    const char * p_will_msg;                                                                             ///< String representing Will Message.
    const char * p_sni_name;                                                                             ///< Server Name Indication.

    mqtt_onchip_da16xxx_qos_t               will_qos_level;                                              ///< Will Topic QoS level.
    mqtt_onchip_da16xxx_tls_cipher_suites_t p_tls_cipher_suites[MQTT_ONCHIP_DA16XXX_TLS_CIPHER_MAX_CNT]; ///< TLS Cipher suites supported.
} mqtt_onchip_da16xxx_cfg_t;

/** MQTT_ONCHIP_DA16XXX private control block. DO NOT MODIFY. */
typedef struct st_mqtt_onchip_da16xxx_instance_ctrl
{
    uint8_t  cmd_tx_buff[MQTT_ONCHIP_DA16XXX_CFG_CMD_TX_BUF_SIZE]; ///< Command send buffer.
    uint8_t  cmd_rx_buff[MQTT_ONCHIP_DA16XXX_CFG_CMD_RX_BUF_SIZE]; ///< Command receive buffer.
    uint32_t open;                                                 ///< Flag to indicate if MQTT has been opened.
    bool     is_mqtt_connected;                                    ///< Flag to track MQTT connection status.
    mqtt_onchip_da16xxx_cfg_t const * p_cfg;                       ///< Pointer to p_cfg for MQTT.
} mqtt_onchip_da16xxx_instance_ctrl_t;

/* MQTT public function prototypes */
fsp_err_t RM_MQTT_DA16XXX_Open(mqtt_onchip_da16xxx_instance_ctrl_t   * p_ctrl,
                               mqtt_onchip_da16xxx_cfg_t const * const p_cfg);
fsp_err_t RM_MQTT_DA16XXX_Disconnect(mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl);
fsp_err_t RM_MQTT_DA16XXX_Connect(mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl, uint32_t timeout_ms);
fsp_err_t RM_MQTT_DA16XXX_Publish(mqtt_onchip_da16xxx_instance_ctrl_t  * p_ctrl,
                                  mqtt_onchip_da16xxx_pub_info_t * const p_pub_info);
fsp_err_t RM_MQTT_DA16XXX_Subscribe(mqtt_onchip_da16xxx_instance_ctrl_t  * p_ctrl,
                                    mqtt_onchip_da16xxx_sub_info_t * const p_sub_info,
                                    size_t                                 subscription_count);
fsp_err_t RM_MQTT_DA16XXX_UnSubscribe(mqtt_onchip_da16xxx_instance_ctrl_t  * p_ctrl,
                                      mqtt_onchip_da16xxx_sub_info_t * const p_sub_info);
fsp_err_t RM_MQTT_DA16XXX_Receive(mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl);
fsp_err_t RM_MQTT_DA16XXX_Close(mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl);

#endif                                 /* RM_MQTT_ONCHIP_DA16XXX_H_ */

/*******************************************************************************************************************//**
 * @} (end addtogroup MQTT_ONCHIP_DA16XXX)
 **********************************************************************************************************************/
