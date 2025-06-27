/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_mqtt_onchip_da16xxx.h"

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/
#define MQTT_ONCHIP_DA16XXX_CERT_START        "\x1B"
#define MQTT_ONCHIP_DA16XXX_CERT_END          "\x03"

/* Predefined timeout values */
#define MQTT_ONCHIP_DA16XXX_TIMEOUT_100MS     (100)
#define MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS     (400)
#define MQTT_ONCHIP_DA16XXX_TIMEOUT_500MS     (500)
#define MQTT_ONCHIP_DA16XXX_TIMEOUT_1SEC      (1000)
#define MQTT_ONCHIP_DA16XXX_TIMEOUT_5SEC      (5000)

#define MQTT_ONCHIP_DA16XXX_MAX_CERT_SIZE     (2045)

#define MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK    "OK"
#define MQTT_OPEN                             (0x4d515454ULL)
#define MQTT_CLOSED                           (0)

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/
static fsp_err_t rm_mqtt_da16xxx_optional_init(mqtt_onchip_da16xxx_instance_ctrl_t   * p_ctrl,
                                               mqtt_onchip_da16xxx_cfg_t const * const p_cfg);

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup MQTT_ONCHIP_DA16XXX MQTT_ONCHIP_DA16XXX
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Initialize the DA16XXX on-chip MQTT Client service.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 * @param[in]  p_cfg                Pointer to MQTT Client configuration structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_cfg instance is NULL.
 * @retval FSP_ERR_INVALID_ARGUMENT Data size is too large or NULL.
 * @retval FSP_ERR_ALREADY_OPEN     The instance has already been opened.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_Open (mqtt_onchip_da16xxx_instance_ctrl_t   * p_ctrl,
                                mqtt_onchip_da16xxx_cfg_t const * const p_cfg)
{
    at_transport_da16xxx_data_t             atcmd;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_cfg->p_transport_instance;

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg->p_callback);

    /* Check if DA16xxx transport has already been opened */
    at_transport_da16xxx_status_t status;
    fsp_err_t err = p_transport_instance->p_api->statusGet(p_transport_instance->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(true == status.open, FSP_ERR_WIFI_FAILED);
    FSP_ERROR_RETURN(MQTT_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg              = p_cfg;
    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    /* Clear the stored ALPNs and SNI configurations */
    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWHTCSNIDEL\r");
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWHTCALPNDEL\r");
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    /* Set MQTT 3.1.1 settings */
    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQV311=%d\r",
             p_ctrl->p_cfg->use_mqtt_v311);
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    /* Check for host name and port */
    FSP_ERROR_RETURN(NULL != p_cfg->p_host_name, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0 != p_cfg->mqtt_port, FSP_ERR_INVALID_ARGUMENT);

    /* Set the host name of the MQTT broker with AT+NWMQBR */
    snprintf((char *) p_ctrl->cmd_tx_buff,
             sizeof(p_ctrl->cmd_tx_buff),
             "AT+NWMQBR=%s,%d\r",
             p_cfg->p_host_name,
             p_cfg->mqtt_port);
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    /* Store the MQTT Username and Password */
    if ((NULL != p_cfg->p_mqtt_user_name) && (NULL != p_cfg->p_mqtt_password))
    {
        snprintf((char *) p_ctrl->cmd_tx_buff,
                 sizeof(p_ctrl->cmd_tx_buff),
                 "AT+NWMQLI=%s,%s\r",
                 p_cfg->p_mqtt_user_name,
                 p_cfg->p_mqtt_password);
        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);

        /* Disable TLS with AT+NWMQTLS */
        snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQTLS=0\r");
        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }
    else
    {
        /* Store the TLS certificate/private key */
        if ((NULL != p_cfg->p_root_ca) && (NULL != p_cfg->p_client_cert) &&
            (NULL != p_cfg->p_client_private_key))
        {
            /* Check the certificates/keys provided to ensure they are smaller than the maximum size */
            FSP_ERROR_RETURN((p_cfg->root_ca_size <= MQTT_ONCHIP_DA16XXX_MAX_CERT_SIZE) ||
                             (p_cfg->client_cert_size <= MQTT_ONCHIP_DA16XXX_MAX_CERT_SIZE) ||
                             (p_cfg->private_key_size <= MQTT_ONCHIP_DA16XXX_MAX_CERT_SIZE),
                             FSP_ERR_INVALID_ARGUMENT);

            /* Enable TLS with AT+NWMQTLS */
            snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQTLS=1\r");
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Program the root CA Certificate */

            /* Put the DA16XXX module into certificate/key input mode */
            snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "%sC0,",
                     MQTT_ONCHIP_DA16XXX_CERT_START);
            atcmd.p_expect_code = NULL;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send certificate/key ascii text */
            atcmd.p_at_cmd_string = (uint8_t *) p_cfg->p_root_ca;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send Indication of the end of content  */
            snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "%s", MQTT_ONCHIP_DA16XXX_CERT_END);
            atcmd.p_at_cmd_string = (uint8_t *) p_ctrl->cmd_tx_buff;
            atcmd.p_expect_code   = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Put the DA16XXX module into certificate/key input mode */
            snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "%sC1,",
                     MQTT_ONCHIP_DA16XXX_CERT_START);
            atcmd.p_expect_code = NULL;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send certificate/key ascii text */
            atcmd.p_at_cmd_string = (uint8_t *) p_cfg->p_client_cert;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send Indication of the end of content  */
            snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "%s", MQTT_ONCHIP_DA16XXX_CERT_END);
            atcmd.p_at_cmd_string = (uint8_t *) p_ctrl->cmd_tx_buff;
            atcmd.p_expect_code   = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Program the private key */

            /* Put the DA16XXX module into certificate/key input mode */
            snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "%sC2,",
                     MQTT_ONCHIP_DA16XXX_CERT_START);
            atcmd.p_expect_code = NULL;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send certificate/key ascii text */
            atcmd.p_at_cmd_string = (uint8_t *) p_cfg->p_client_private_key;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send Indication of the end of content  */
            snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "%s", MQTT_ONCHIP_DA16XXX_CERT_END);
            atcmd.p_at_cmd_string = (uint8_t *) p_ctrl->cmd_tx_buff;
            atcmd.p_expect_code   = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);
        }
    }

    FSP_ERROR_RETURN(0 != p_cfg->keep_alive_seconds, FSP_ERR_INVALID_ARGUMENT);

    /* Set the MQTT ping period */
    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQPING=%d\r", p_cfg->keep_alive_seconds);
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    /* Perform MQTT optional settings */
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_mqtt_da16xxx_optional_init(p_ctrl, p_cfg), FSP_ERR_WIFI_FAILED);

    p_ctrl->open = MQTT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Disconnect from DA16XXX MQTT Client service.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_ctrl instance is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened or the client is not connected.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_Disconnect (mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MQTT_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(true == p_ctrl->is_mqtt_connected, FSP_ERR_NOT_OPEN);
#endif

    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    /* Disable the MQTT Client */
    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQCL=0\r");

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    p_ctrl->is_mqtt_connected = false;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configure and connect the DA16XXX MQTT Client service.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 * @param[in]  timeout_ms           Timeout in milliseconds.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_IN_USE           The MQTT client is already connected.
 * @retval FSP_ERR_INVALID_DATA     Response does not contain Connect status.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_Connect (mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl, uint32_t timeout_ms)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;
    char * ptr = (char *) (p_ctrl->cmd_rx_buff);

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MQTT_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(false == p_ctrl->is_mqtt_connected, FSP_ERR_IN_USE);
#endif

    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = timeout_ms;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    /* Enable the MQTT Client */
    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQCL=1\r");

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    R_BSP_SoftwareDelay(MQTT_ONCHIP_DA16XXX_TIMEOUT_5SEC, BSP_DELAY_UNITS_MILLISECONDS);

    /* Query results of connection */
    atcmd.timeout_ms = MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS;
    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQCL=?\r");

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    /* Parse the response */
    ptr = strstr(ptr, "+NWMQCL:");

    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

    ptr = ptr + strlen("+NWMQCL:");

    FSP_ERROR_RETURN('1' == *ptr, FSP_ERR_WIFI_FAILED);

    p_ctrl->is_mqtt_connected = 1;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Publish a message for a given MQTT topic.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 * @param[in]  p_pub_info           MQTT Publish packet parameters.
 *
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_ctrl, p_pub_info is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened or the client is not connected.
 * @retval FSP_ERR_INVALID_DATA     Data size is too large.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_Publish (mqtt_onchip_da16xxx_instance_ctrl_t  * p_ctrl,
                                   mqtt_onchip_da16xxx_pub_info_t * const p_pub_info)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_pub_info);
    FSP_ERROR_RETURN(p_pub_info->payload_length <= MQTT_ONCHIP_DA16XXX_MAX_PUBMSG_LEN, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_pub_info->topic_name_Length <= MQTT_ONCHIP_DA16XXX_MAX_TOPIC_LEN, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(true == p_ctrl->is_mqtt_connected, FSP_ERR_NOT_OPEN);
#endif

    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = p_ctrl->p_cfg->tx_timeout;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    /* Publish an MQTT message with topic and payload */
    if ((p_pub_info->topic_name_Length + p_pub_info->payload_length) < MQTT_ONCHIP_DA16XXX_MAX_PUBTOPICMSG_LEN)
    {
        /* Set MQTT QoS level settings */
        snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQQOS=%d\r", p_pub_info->qos);

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);

        FSP_ERROR_RETURN((strlen((char *) p_ctrl->cmd_tx_buff) + strlen(p_pub_info->p_payload) +
                          strlen(p_pub_info->p_topic_name)) < MQTT_ONCHIP_DA16XXX_CFG_CMD_TX_BUF_SIZE,
                         FSP_ERR_INVALID_DATA);

        snprintf((char *) p_ctrl->cmd_tx_buff,
                 sizeof(p_ctrl->cmd_tx_buff),
                 "AT+NWMQMSG=%s,%s\r",
                 p_pub_info->p_payload,
                 p_pub_info->p_topic_name);

        /* Only takes TX mutex if expected code is NULL, which enables simultaneous publish/subscribe */
        atcmd.p_expect_code = NULL;
        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }
    else
    {
        return FSP_ERR_WIFI_FAILED;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Subscribe to DA16XXX MQTT topics.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 * @param[in]  p_sub_info           List of MQTT subscription info.
 * @param[in]  subscription_count   Number of topics to subscribe to.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_ctrl, p_sub_info is NULL or subscription_count is 0.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_INVALID_DATA     Data size is too large.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_Subscribe (mqtt_onchip_da16xxx_instance_ctrl_t  * p_ctrl,
                                     mqtt_onchip_da16xxx_sub_info_t * const p_sub_info,
                                     size_t                                 subscription_count)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_sub_info);
    FSP_ASSERT(0 != subscription_count);
    FSP_ERROR_RETURN(MQTT_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    /* Set the MQTT subscriber topic with AT+NWMQTS */
    if (subscription_count < MQTT_ONCHIP_DA16XXX_SUBTOPIC_MAX_CNT)
    {
        /* Set MQTT QoS level settings */
        snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQQOS=%d\r", p_sub_info[0].qos);

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);

        /* Create subscription command by concatenating topics */
        snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQTS=%d", subscription_count);

        for (int i = 0; i < (int) subscription_count; i++)
        {
            FSP_ERROR_RETURN((strlen((char *) p_ctrl->cmd_tx_buff) + strlen(
                                  p_sub_info[i].p_topic_filter + 3)) < MQTT_ONCHIP_DA16XXX_CFG_CMD_TX_BUF_SIZE,
                             FSP_ERR_INVALID_DATA);

            snprintf((char *) p_ctrl->cmd_tx_buff + strlen((char *) p_ctrl->cmd_tx_buff),
                     sizeof(p_ctrl->cmd_tx_buff),
                     ",%s",
                     p_sub_info[i].p_topic_filter);
        }

        snprintf((char *) p_ctrl->cmd_tx_buff + strlen((char *) p_ctrl->cmd_tx_buff), sizeof(p_ctrl->cmd_tx_buff),
                 "\r");

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }
    else
    {
        return FSP_ERR_WIFI_FAILED;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Unsubscribe from DA16XXX MQTT topics.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 * @param[in]  p_sub_info           List of MQTT subscription info.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_ctrl, p_sub_info is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened or the client is not connected.
 * @retval FSP_ERR_INVALID_DATA     Data size is too large.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_UnSubscribe (mqtt_onchip_da16xxx_instance_ctrl_t  * p_ctrl,
                                       mqtt_onchip_da16xxx_sub_info_t * const p_sub_info)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_sub_info);
    FSP_ERROR_RETURN(true == p_ctrl->is_mqtt_connected, FSP_ERR_NOT_OPEN);
#endif

    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    FSP_ERROR_RETURN((strlen((char *) p_ctrl->cmd_tx_buff) + strlen(
                          p_sub_info->p_topic_filter)) < MQTT_ONCHIP_DA16XXX_CFG_CMD_TX_BUF_SIZE,
                     FSP_ERR_INVALID_DATA);

    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQUTS=%s\r", p_sub_info->p_topic_filter);

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Receive data subscribed to on DA16XXX MQTT Client service.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        The p_ctrl, p_textstring, p_ip_addr is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened or the client is not connected.
 * @retval FSP_ERR_INVALID_DATA     Receive function did not receive valid publish data.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_Receive (mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    mqtt_onchip_da16xxx_callback_args_t mqtt_data;
    char * ptr = (char *) p_ctrl->cmd_rx_buff;

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(true == p_ctrl->is_mqtt_connected, FSP_ERR_NOT_OPEN);
#endif

    if (true == p_ctrl->is_mqtt_connected)
    {
        size_t xReceivedBytes = p_transport_instance->p_api->bufferRecv(p_transport_instance->p_ctrl,
                                                                        (char *) p_ctrl->cmd_rx_buff,
                                                                        sizeof(p_ctrl->cmd_rx_buff),
                                                                        p_ctrl->p_cfg->rx_timeout);
        if (xReceivedBytes > 0)
        {
            char    * p_end_of_message = (char *) &p_ctrl->cmd_rx_buff[xReceivedBytes];
            char    * p_header         = "\r\n+NWMQMSG:";
            uint32_t  header_length    = strlen(p_header);
            uint8_t * p_data;
            char    * p_topic;

            /* Ensure that the end of MQTT buffer is NULL-terminated for string safety */
            *p_end_of_message = 0;

            /* Check for data remaining from stream buffer */
            while (ptr < p_end_of_message)
            {
                /* Check for published message string in the buffer e.g."\r\n+NWMQMSG:1,AHRenesas/feeds/led,4\0" */
                if (0 == (strncmp(ptr, p_header, header_length)))
                {
                    /* Advance pointer past the header */
                    ptr = ptr + header_length;

                    /* Assign the data */
                    p_data = (uint8_t *) ptr;

                    /* Advance pointer to the topic */
                    ptr = strchr(ptr, ',');

                    /* Check that topic exists */
                    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

                    /* Replace comma with null termination */
                    *ptr = 0;

                    /* Increment past null terminator and assign topic */
                    FSP_ERROR_RETURN(ptr < p_end_of_message, FSP_ERR_INVALID_DATA);
                    ptr++;

                    /* Assign the topic */
                    p_topic = ptr;

                    /* Advance pointer to the length */
                    ptr = strchr(ptr, ',');

                    /* Check that length exists */
                    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

                    /* Replace comma with null termination */
                    *ptr = 0;

                    /* Increment past null terminator and parse length */
                    FSP_ERROR_RETURN(ptr < p_end_of_message, FSP_ERR_INVALID_DATA);
                    ptr++;

                    long int length = strtol(ptr, NULL, 10);

                    FSP_ERROR_RETURN(0 != length, FSP_ERR_INVALID_DATA);

                    /* If all checks were successful, assign temporary data to callback args */
                    mqtt_data.p_data      = p_data;
                    mqtt_data.p_topic     = p_topic;
                    mqtt_data.data_length = (uint32_t) length;

                    /* Call the user callback with successful data */
                    p_ctrl->p_cfg->p_callback(&mqtt_data);
                }
                else
                {
                    ptr++;
                }
            }
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Close the DA16XXX MQTT Client service.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 *
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        The p_ctrl, p_textstring, p_ip_addr is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_MQTT_DA16XXX_Close (mqtt_onchip_da16xxx_instance_ctrl_t * p_ctrl)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    /* Do parameter checking */
#if (1 == MQTT_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(MQTT_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;
    snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQDEL\r");

    p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd);

    p_ctrl->open = MQTT_CLOSED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup MQTT_ONCHIP_DA16XXX)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Optional configurations for DA16XXX MQTT Client service.
 *
 * @param[in]  p_ctrl               Pointer to MQTT Client instance control structure.
 * @param[in]  p_cfg                Pointer to MQTT Client configuration structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 **********************************************************************************************************************/
static fsp_err_t rm_mqtt_da16xxx_optional_init (mqtt_onchip_da16xxx_instance_ctrl_t   * p_ctrl,
                                                mqtt_onchip_da16xxx_cfg_t const * const p_cfg)
{
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    atcmd.p_at_cmd_string      = (uint8_t *) p_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = MQTT_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = MQTT_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    /* Set MQTT ALPN settings */
    if (p_cfg->alpn_count != 0)
    {
        /* Set up ALPN protocol and count packet */
        snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQALPN=%d", p_cfg->alpn_count);

        for (int i = 0; i < p_cfg->alpn_count; i++)
        {
            snprintf((char *) p_ctrl->cmd_tx_buff + strlen((char *) p_ctrl->cmd_tx_buff),
                     sizeof(p_ctrl->cmd_tx_buff),
                     ",%s",
                     p_cfg->p_alpns[i]);
        }

        snprintf((char *) p_ctrl->cmd_tx_buff + strlen((char *) p_ctrl->cmd_tx_buff), sizeof(p_ctrl->cmd_tx_buff),
                 "\r");

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    /* Set MQTT TLS Cipher Suite settings */
    if (p_cfg->tls_cipher_count > 0)
    {
        strncpy((char *) p_ctrl->cmd_tx_buff, "AT+NWMQCSUIT=", sizeof(p_ctrl->cmd_tx_buff));

        for (int i = 0; i < p_cfg->tls_cipher_count; i++)
        {
            snprintf((char *) p_ctrl->cmd_tx_buff + strlen((char *) p_ctrl->cmd_tx_buff),
                     sizeof(p_ctrl->cmd_tx_buff),
                     "%x,",
                     p_cfg->p_tls_cipher_suites[i]);
        }

        snprintf((char *) p_ctrl->cmd_tx_buff + strlen((char *) p_ctrl->cmd_tx_buff) - 1,
                 sizeof(p_ctrl->cmd_tx_buff),
                 "\r");

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    /* Set MQTT SNI settings */
    if ((NULL != p_cfg->p_sni_name) && (sizeof(p_cfg->p_sni_name) < MQTT_ONCHIP_DA16XXX_MAX_SNI_LEN))
    {
        snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQSNI=%s\r", p_cfg->p_sni_name);

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    /* Set MQTT Clean Session settings */
    if (0 == p_cfg->clean_session)
    {
        snprintf((char *) p_ctrl->cmd_tx_buff, sizeof(p_ctrl->cmd_tx_buff), "AT+NWMQCS=0\r");

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    /* Set MQTT Client Identifier settings */
    if (0 != p_cfg->client_identifier_length)
    {
        snprintf((char *) p_ctrl->cmd_tx_buff,
                 sizeof(p_ctrl->cmd_tx_buff),
                 "AT+NWMQCID=%s\r",
                 p_cfg->p_client_identifier);

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    /* Set MQTT Last Will settings */
    if (NULL != p_cfg->p_will_topic)
    {
        snprintf((char *) p_ctrl->cmd_tx_buff,
                 sizeof(p_ctrl->cmd_tx_buff),
                 "AT+NWMQWILL=%s,%s,%d\r",
                 p_cfg->p_will_topic,
                 p_cfg->p_will_msg,
                 p_cfg->will_qos_level);

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_transport_instance->p_api->atCommandSendThreadSafe(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    return FSP_SUCCESS;
}
