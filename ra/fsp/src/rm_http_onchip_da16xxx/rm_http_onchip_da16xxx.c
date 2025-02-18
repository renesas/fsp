/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_wifi_da16xxx.h"
#include "rm_http_onchip_da16xxx.h"

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/
#define HTTP_ONCHIP_DA16XXX_CERT_START           "\x1B"
#define HTTP_ONCHIP_DA16XXX_CERT_END             "\x03"

#define HTTP_ONCHIP_DA16XXX_TX_BUFF_SIZE         (80)
#define HTTP_ONCHIP_DA16XXX_RX_BUFF_SIZE         (7)

/* Predefined timeout values */
#define HTTP_ONCHIP_DA16XXX_TIMEOUT_100MS        (100)
#define HTTP_ONCHIP_DA16XXX_TIMEOUT_400MS        (400)
#define HTTP_ONCHIP_DA16XXX_TIMEOUT_1SEC         (1000)
#define HTTP_ONCHIP_DA16XXX_TIMEOUT_5SEC         (5000)

#define HTTP_ONCHIP_DA16XXX_MAX_CERT_SIZE        (2045)

#define HTTP_ONCHIP_DA16XXX_MAX_CERT_SIZE        (2045)

#define HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK       "OK"
#define HTTP_OPEN                                (0x4d515454ULL)
#define HTTP_CLOSED                              (0)

#define HTTP_ONCHIP_DA16XXX_PAYLOAD_MAX          (1460)
#define HTTP_ONCHIP_DA16XXX_RESPONSE_TAG_SIZE    (50)
#define HTTP_ONCHIP_DA16XXX_DATA_TAG_SIZE        (16)

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/
uint8_t g_cmd_tx_buff[HTTP_ONCHIP_DA16XXX_TX_BUFF_SIZE];
uint8_t g_cmd_rx_buff[HTTP_ONCHIP_DA16XXX_RX_BUFF_SIZE];

/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/
static fsp_err_t rm_http_da16xxx_add_header(http_onchip_da16xxx_request_t * p_request, char * p_req_buf,
                                            uint32_t length);

static fsp_err_t rm_http_da16xxx_read_header(http_onchip_da16xxx_instance_ctrl_t * p_ctrl,
                                             char                                * p_resp_buf,
                                             uint32_t                              length);

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup HTTP_ONCHIP_DA16XXX HTTP_ONCHIP_DA16XXX
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Initialize the DA16XXX on-chip HTTP Client service.
 *
 * @param[in]  p_ctrl               Pointer to HTTP Client instance control structure.
 * @param[in]  p_cfg                Pointer to HTTP Client configuration structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Parameter checking was unsuccessful.
 * @retval FSP_ERR_INVALID_ARGUMENT Data size is too large or NULL.
 * @retval FSP_ERR_ALREADY_OPEN     The instance has already been opened.
 **********************************************************************************************************************/
fsp_err_t RM_HTTP_DA16XXX_Open (http_onchip_da16xxx_instance_ctrl_t   * p_ctrl,
                                http_onchip_da16xxx_cfg_t const * const p_cfg)
{
    /* Do parameter checking */
#if (1 == HTTP_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(HTTP_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Check if DA16xxx transport has already been opened */
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_cfg->p_transport_instance;
    at_transport_da16xxx_status_t status;
    FSP_ASSERT(NULL != p_transport_instance);
    fsp_err_t err = p_transport_instance->p_api->statusGet(p_transport_instance->p_ctrl, &status);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(true == status.open, FSP_ERR_WIFI_FAILED);
#else
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_cfg->p_transport_instance;
#endif
    at_transport_da16xxx_data_t atcmd;
    p_ctrl->p_cfg = p_cfg;

    atcmd.p_at_cmd_string      = g_cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = g_cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(g_cmd_rx_buff);
    atcmd.timeout_ms           = HTTP_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    fsp_err_t (* p_send_cmd)(at_transport_da16xxx_ctrl_t *,
                             at_transport_da16xxx_data_t *) = p_transport_instance->p_api->atCommandSendThreadSafe;

    /* Clear ALPN and SNI settings */
    snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "AT+NWHTCSNIDEL\r");
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "AT+NWHTCALPNDEL\r");
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    if ((NULL != p_ctrl->p_cfg->p_sni_name) && (sizeof(p_ctrl->p_cfg->p_sni_name) < HTTP_ONCHIP_DA16XXX_MAX_SNI_LEN))
    {
        /* Set Server Name Indication (SNI) */
        snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "AT+NWHTCSNI=%s\r", p_ctrl->p_cfg->p_sni_name);
        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    /* Set HTTP ALPN settings */
    if (p_cfg->alpn_count != 0)
    {
        /* Set up ALPN protocol and count packet */
        snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "AT+NWHTCALPN=%d", p_cfg->alpn_count);

        for (int i = 0; i < p_cfg->alpn_count; i++)
        {
            snprintf((char *) g_cmd_tx_buff + strlen((char *) g_cmd_tx_buff),
                     sizeof(g_cmd_tx_buff),
                     ",%s",
                     p_cfg->p_alpns[i]);
        }

        snprintf((char *) g_cmd_tx_buff + strlen((char *) g_cmd_tx_buff), sizeof(g_cmd_tx_buff), "\r");

        FSP_ERROR_RETURN(FSP_SUCCESS ==
                         p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                         FSP_ERR_WIFI_FAILED);
    }

    /* Set TLS Authentication Level with AT+NWHTCTLSAUTH */
    snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "AT+NWHTCTLSAUTH=%d\r", p_ctrl->p_cfg->tls_level);
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    if (p_ctrl->p_cfg->tls_level != HTTP_ONCHIP_DA16XXX_TLS_VERIFY_NONE)
    {
        if ((NULL != p_cfg->p_root_ca) && (NULL != p_cfg->p_client_cert) &&
            (NULL != p_cfg->p_client_private_key))
        {
            /* Check the certificates/keys provided to ensure they are smaller than the maximum size */
            FSP_ERROR_RETURN((p_cfg->root_ca_size <= HTTP_ONCHIP_DA16XXX_MAX_CERT_SIZE) ||
                             (p_cfg->client_cert_size <= HTTP_ONCHIP_DA16XXX_MAX_CERT_SIZE) ||
                             (p_cfg->private_key_size <= HTTP_ONCHIP_DA16XXX_MAX_CERT_SIZE),
                             FSP_ERR_INVALID_ARGUMENT);

            /* Program the root CA Certificate */

            /* Put the DA16XXX module into certificate/key input mode */
            snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%sC3,", HTTP_ONCHIP_DA16XXX_CERT_START);
            atcmd.p_expect_code = NULL;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send certificate/key ascii text */
            atcmd.p_at_cmd_string = (uint8_t *) p_cfg->p_root_ca;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send Indication of the end of content  */
            snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%s", HTTP_ONCHIP_DA16XXX_CERT_END);
            atcmd.p_at_cmd_string = (uint8_t *) g_cmd_tx_buff;
            atcmd.p_expect_code   = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Put the DA16XXX module into certificate/key input mode */
            snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%sC4,", HTTP_ONCHIP_DA16XXX_CERT_START);
            atcmd.p_expect_code = NULL;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send certificate/key ascii text */
            atcmd.p_at_cmd_string = (uint8_t *) p_cfg->p_client_cert;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send Indication of the end of content  */
            snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%s", HTTP_ONCHIP_DA16XXX_CERT_END);
            atcmd.p_at_cmd_string = (uint8_t *) g_cmd_tx_buff;
            atcmd.p_expect_code   = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Program the private key */

            /* Put the DA16XXX module into certificate/key input mode */
            snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%sC5,", HTTP_ONCHIP_DA16XXX_CERT_START);
            atcmd.p_expect_code = NULL;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send certificate/key ascii text */
            atcmd.p_at_cmd_string = (uint8_t *) p_cfg->p_client_private_key;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);

            /* Send Indication of the end of content  */
            snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%s", HTTP_ONCHIP_DA16XXX_CERT_END);
            atcmd.p_at_cmd_string = (uint8_t *) g_cmd_tx_buff;
            atcmd.p_expect_code   = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                             FSP_ERR_WIFI_FAILED);
        }
    }

    p_ctrl->open = HTTP_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Send the HTTP request with the configured buffers.
 *
 * @param[in]  p_ctrl               Pointer to HTTP Client instance control structure.
 * @param[in]  p_request            Pointer to HTTP request control structure.
 * @param[in]  p_buffer             Pointer to HTTP user buffer struct for request and response.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Parameter checking was unsuccessful.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_INVALID_ARGUMENT Data size is too large.
 * @retval FSP_ERR_INVALID_DATA     Data was not received correctly.
 **********************************************************************************************************************/
fsp_err_t RM_HTTP_DA16XXX_Send (http_onchip_da16xxx_instance_ctrl_t * p_ctrl,
                                http_onchip_da16xxx_request_t       * p_request,
                                http_onchip_da16xxx_buffer_t        * p_buffer)
{
    /* Do parameter checking */
#if (1 == HTTP_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_request);
    FSP_ASSERT(NULL != p_buffer);
    FSP_ERROR_RETURN(HTTP_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;

    at_transport_da16xxx_data_t atcmd;
    atcmd.p_at_cmd_string      = (uint8_t *) p_buffer->p_request_buffer;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = (uint8_t *) p_buffer->p_response_buffer;
    atcmd.response_buffer_size = p_buffer->resp_length;
    atcmd.timeout_ms           = HTTP_ONCHIP_DA16XXX_TIMEOUT_1SEC;
    atcmd.p_expect_code        = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    fsp_err_t (* p_send_cmd)(at_transport_da16xxx_ctrl_t *,
                             at_transport_da16xxx_data_t *) = p_transport_instance->p_api->atCommandSendThreadSafe;

    /* Create request buffer */
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     rm_http_da16xxx_add_header(p_request, p_buffer->p_request_buffer, p_buffer->req_length),
                     FSP_ERR_WIFI_FAILED);

    /* Send out the HTTP request */
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    /* Parse the HTTP response */
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     rm_http_da16xxx_read_header(p_ctrl, p_buffer->p_response_buffer, p_buffer->resp_length),
                     FSP_ERR_WIFI_FAILED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Start the HTTP server.
 *
 * @param[in]  p_ctrl               Pointer to HTTP Client instance control structure.
 * @param[in]  enable               Enum value to enable or disable SSL.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Parameter checking was unsuccessful.
 * @retval FSP_ERR_INVALID_ARGUMENT SSl enable is either null or incorrect.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t RM_HTTP_DA16XXX_Start (http_onchip_da16xxx_instance_ctrl_t * p_ctrl, http_onchip_da16xxx_ssl_enable_t enable)
{
    /* Do parameter checking */
#if (1 == HTTP_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(HTTP_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((enable == HTTP_ONCHIP_DA16XXX_SSL_ENABLE) || (enable == HTTP_ONCHIP_DA16XXX_SSL_DISABLE),
                     FSP_ERR_INVALID_ARGUMENT);
#endif

    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;

    at_transport_da16xxx_data_t atcmd;

    p_ctrl->enable = HTTP_ONCHIP_DA16XXX_SSL_DISABLE;

    atcmd.p_at_cmd_string      = g_cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = g_cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(g_cmd_rx_buff);
    atcmd.timeout_ms           = HTTP_ONCHIP_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    fsp_err_t (* p_send_cmd)(at_transport_da16xxx_ctrl_t *,
                             at_transport_da16xxx_data_t *) = p_transport_instance->p_api->atCommandSendThreadSafe;

    char * httpcmd;

    p_ctrl->enable = enable;

    if (enable == HTTP_ONCHIP_DA16XXX_SSL_ENABLE)
    {
        httpcmd = "AT+NWHTSS=1\r";
    }
    else
    {
        httpcmd = "AT+NWHTS=1\r";
    }

    snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%s", httpcmd);
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Start the HTTP server.
 *
 * @param[in]  p_ctrl               Pointer to HTTP Client instance control structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Parameter checking was unsuccessful.
 * @retval FSP_ERR_INVALID_ARGUMENT SSl enable is either null or incorrect.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t RM_HTTP_DA16XXX_Stop (http_onchip_da16xxx_instance_ctrl_t * p_ctrl)
{
    /* Do parameter checking */
#if (1 == HTTP_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(HTTP_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;

    at_transport_da16xxx_data_t atcmd;

    atcmd.p_at_cmd_string      = g_cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = g_cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(g_cmd_rx_buff);
    atcmd.timeout_ms           = HTTP_ONCHIP_DA16XXX_TIMEOUT_100MS;
    atcmd.p_expect_code        = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    fsp_err_t (* p_send_cmd)(at_transport_da16xxx_ctrl_t *,
                             at_transport_da16xxx_data_t *) = p_transport_instance->p_api->atCommandSendThreadSafe;

    char * httpcmd;

    if (p_ctrl->enable == HTTP_ONCHIP_DA16XXX_SSL_ENABLE)
    {
        httpcmd = "AT+NWHTSS=0\r";
    }
    else
    {
        httpcmd = "AT+NWHTS=0\r";
    }

    snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "%s", httpcmd);
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_send_cmd(p_transport_instance->p_ctrl, &atcmd),
                     FSP_ERR_WIFI_FAILED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Close the DA16XXX HTTP Client service.
 *
 * @param[in]  p_ctrl               Pointer to HTTP Client instance control structure.
 *
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter checking was unsuccessful.
 **********************************************************************************************************************/
fsp_err_t RM_HTTP_DA16XXX_Close (http_onchip_da16xxx_instance_ctrl_t * p_ctrl)
{
    /* Do parameter checking */
#if (1 == HTTP_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(HTTP_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;
    atcmd.p_at_cmd_string      = g_cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = g_cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(g_cmd_rx_buff);
    atcmd.timeout_ms           = HTTP_ONCHIP_DA16XXX_TIMEOUT_100MS;
    atcmd.p_expect_code        = HTTP_ONCHIP_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = 0;

    fsp_err_t (* p_send_cmd)(at_transport_da16xxx_ctrl_t *,
                             at_transport_da16xxx_data_t *) = p_transport_instance->p_api->atCommandSendThreadSafe;

    /* Clear ALPN and SNI settings */
    snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "AT+NWHTCSNIDEL\r");
    p_send_cmd(p_transport_instance->p_ctrl, &atcmd);

    snprintf((char *) g_cmd_tx_buff, sizeof(g_cmd_tx_buff), "AT+NWHTCALPNDEL\r");
    p_send_cmd(p_transport_instance->p_ctrl, &atcmd);

    p_ctrl->open = HTTP_CLOSED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup HTTP_ONCHIP_DA16XXX)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Optional configurations for DA16XXX HTTP Client service.
 *
 * @param[in]  p_request           Pointer to HTTP request control structure.
 * @param[in]  p_req_buf           Pointer to HTTP user buffer for request and response.
 * @param[in]  length              Size of HTTP user buffer.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter checking was unsuccessful.
 * @retval FSP_ERR_INVALID_ARGUMENT Data size is too large.
 **********************************************************************************************************************/
static fsp_err_t rm_http_da16xxx_add_header (http_onchip_da16xxx_request_t * p_request,
                                             char                          * p_req_buf,
                                             uint32_t                        length)
{
    /* Do parameter checking */
#if (1 == HTTP_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_request);
    FSP_ASSERT(NULL != p_req_buf);
    FSP_ERROR_RETURN(strlen(p_request->p_http_endpoint) < HTTP_ONCHIP_DA16XXX_MAX_GET_LEN, FSP_ERR_INVALID_ARGUMENT);
#endif

    int buffer_len = 0;

    /* Convert request method to string */
    switch (p_request->method)
    {
        case HTTP_ONCHIP_DA16XXX_GET:
        {
            /* Construct the Send Request packet <url><method> */
            buffer_len = snprintf(p_req_buf, length, "AT+NWHTCH=%s,get", p_request->p_http_endpoint);
            break;
        }

        case HTTP_ONCHIP_DA16XXX_POST:
        {
            /* Construct the Send Request packet <url><method> */
            buffer_len = snprintf(p_req_buf, length, "AT+NWHTCH=%s,post", p_request->p_http_endpoint);
            break;
        }

        case HTTP_ONCHIP_DA16XXX_PUT:
        {
            /* Construct the Send Request packet <url><method> */
            buffer_len = snprintf(p_req_buf, length, "AT+NWHTCH=%s,put", p_request->p_http_endpoint);
            break;
        }
    }

    /* Check if optional request body was added */
    if (p_request->p_request_body != NULL)
    {
        /* Construct the Send Request packet <url><method><body> */
        buffer_len += snprintf(p_req_buf + strlen(p_req_buf), length, ",%s\r", p_request->p_request_body);
    }
    else
    {
        buffer_len += snprintf(p_req_buf + strlen(p_req_buf), length, "\r");
    }

    /* Error checking on the request string length */
    FSP_ERROR_RETURN((0 > buffer_len) || (length >= (unsigned) buffer_len), FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Optional configurations for DA16XXX HTTP Client service.
 *
 * @param[in]  p_ctrl               Pointer to HTTP Client instance control structure.
 * @param[in]  p_resp_buf           Pointer to HTTP user buffer for request and response.
 * @param[in]  length               Size of HTTP user buffer.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter checking was unsuccessful.
 * @retval FSP_ERR_INVALID_DATA     Data was not received correctly.
 **********************************************************************************************************************/
static fsp_err_t rm_http_da16xxx_read_header (http_onchip_da16xxx_instance_ctrl_t * p_ctrl,
                                              char                                * p_resp_buf,
                                              uint32_t                              length)
{
    /* Do parameter checking */
#if (1 == HTTP_ONCHIP_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_resp_buf);
#endif

    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_ctrl->p_cfg->p_transport_instance;

    /* Check if the buffer has contents already */
    char * ptr = (p_resp_buf);

    /* Check for meta data header */
    ptr = strstr(ptr, "+NWHTCDATA:");

    /* If the buffer doesn't have the response, attempt to get response data */
    if (NULL == ptr)
    {
        size_t xReceivedBytes = p_transport_instance->p_api->bufferRecv(p_transport_instance->p_ctrl,
                                                                        p_resp_buf,
                                                                        length,
                                                                        HTTP_ONCHIP_DA16XXX_TIMEOUT_5SEC);

        /* Check for response data */
        FSP_ERROR_RETURN(xReceivedBytes > 0, FSP_ERR_INVALID_DATA)

        ptr = (p_resp_buf);

        /* Ensure that the end of HTTP buffer is NULL-terminated for string safety */
        p_resp_buf[xReceivedBytes] = 0;

        /* Check for meta data header */
        ptr = strstr(ptr, "+NWHTCDATA:");

        FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);
    }

    int64_t header_size;
    int64_t data_size;
    int64_t payload_size = 0;
    int64_t content_length;
    uint8_t data_multiplier = 0;

    /* Advance pointer and track start of header data length */
    ptr = ptr + strlen("+NWHTCDATA:");

    /* Parse data length for response header */
    header_size = strtol(ptr, NULL, 10);

    FSP_ERROR_RETURN(0 != header_size, FSP_ERR_INVALID_DATA);

    /* Check that header size is not bigger than length of buffer */
    FSP_ERROR_RETURN((uint32_t) (header_size + HTTP_ONCHIP_DA16XXX_RESPONSE_TAG_SIZE) < length, FSP_ERR_INVALID_DATA);

    /* Check for OK status of 2xx */
    ptr = strstr(ptr, "200 OK");

    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

    /* Check for length of data */
    ptr = strstr(ptr, "Content-Length: ");

    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

    /* Advance pointer and track start of header data length */
    ptr = ptr + strlen("Content-Length: ");

    /* Parse data length for payload size (expected length) */
    content_length = strtol(ptr, NULL, 10);

    FSP_ERROR_RETURN(0 != content_length, FSP_ERR_INVALID_DATA);

    /* Advance pointer to payload tag */
    ptr = strstr(ptr, "\r\n+NWHTCDATA:");

    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

    /* Loop around to check the data size matches the expected content length */
    do
    {
        /* Advance pointer to payload tag */
        ptr = strstr(ptr, "NWHTCDATA:");

        FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

        /* Advance pointer and track start of payload data length*/
        ptr = ptr + strlen("NWHTCDATA:");

        /* Parse data length for data payload */
        data_size = strtol(ptr, NULL, 10);

        FSP_ERROR_RETURN(0 != data_size, FSP_ERR_INVALID_DATA);

        /* Add current data packet to total data size */
        payload_size += data_size;

        data_multiplier++;
    } while (content_length != payload_size);

    /* Add header size to the total payload size */
    payload_size += header_size + HTTP_ONCHIP_DA16XXX_RESPONSE_TAG_SIZE;

    /* Add data tag to the total payload size */
    payload_size += (HTTP_ONCHIP_DA16XXX_DATA_TAG_SIZE * data_multiplier);

    /* Check that header and payload is not bigger than length of buffer */
    FSP_ERROR_RETURN((uint32_t) payload_size < length, FSP_ERR_INVALID_DATA);

    /* Advance pointer to final status tag */
    ptr = strstr(ptr, "\r\n+NWHTCSTATUS:");

    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

    ptr = ptr + strlen("\n\r+NWHTCSTATUS:");

    /* check that the final status is also NX_SUCCESS */
    FSP_ERROR_RETURN(0x00 == (strtol(ptr, NULL, 10)), FSP_ERR_INVALID_DATA);

    return FSP_SUCCESS;
}
