/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_wifi_da16xxx.h"

/*! \cond PRIVATE */

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/

/* Mutex give/take defines */
#define WIFI_DA16XXX_MUTEX_TX                   (1 << 0)
#define WIFI_DA16XXX_MUTEX_RX                   (1 << 1)

#define WIFI_DA16XXX_TEMP_BUFFER_SIZE           (256)

/* Text full versions of AT command returns */
#define WIFI_DA16XXX_RETURN_TEXT_OK             "OK"
#define WIFI_DA16XXX_RETURN_CONN_TEXT           "+WFJAP:1"

#define WIFI_DA16XXX_MIN_SDK_VER_MAJOR          (3)
#define WIFI_DA16XXX_MIN_SDK_VER_MINOR          (2)
#define WIFI_DA16XXX_MIN_SDK_VER_REVISION       (6)
#define WIFI_DA16XXX_MIN_SDK_VER_ENGI           (0)

/* Predefined timeout values */
#define WIFI_DA16XXX_TIMEOUT_1MS                (1)
#define WIFI_DA16XXX_TIMEOUT_3MS                (3)
#define WIFI_DA16XXX_TIMEOUT_5MS                (5)
#define WIFI_DA16XXX_TIMEOUT_10MS               (10)
#define WIFI_DA16XXX_TIMEOUT_20MS               (20)
#define WIFI_DA16XXX_TIMEOUT_30MS               (30)
#define WIFI_DA16XXX_TIMEOUT_100MS              (100)
#define WIFI_DA16XXX_TIMEOUT_200MS              (200)
#define WIFI_DA16XXX_TIMEOUT_300MS              (300)
#define WIFI_DA16XXX_TIMEOUT_400MS              (400)
#define WIFI_DA16XXX_TIMEOUT_500MS              (500)
#define WIFI_DA16XXX_TIMEOUT_1SEC               (1000)
#define WIFI_DA16XXX_TIMEOUT_2SEC               (2000)
#define WIFI_DA16XXX_TIMEOUT_3SEC               (3000)
#define WIFI_DA16XXX_TIMEOUT_4SEC               (4000)
#define WIFI_DA16XXX_TIMEOUT_5SEC               (5000)
#define WIFI_DA16XXX_TIMEOUT_8SEC               (8000)
#define WIFI_DA16XXX_TIMEOUT_15SEC              (15000)
#define WIFI_DA16XXX_TIMEOUT_20SEC              (20000)

/* Minimum string size for getting local time string */
#define WIFI_DA16XXX_LOCAL_TIME_STR_SIZE        (25)

#define WIFI_DA16XXX_IPV4_MAX_LENGTH            (15)

#define HOURS_IN_SECONDS                        (3600)
#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */
/* Socket Types supported */
 #define WIFI_DA16XXX_SOCKET_TYPE_TCP_SERVER    (0)
 #define WIFI_DA16XXX_SOCKET_TYPE_TCP_CLIENT    (1)
 #define WIFI_DA16XXX_SOCKET_TYPE_UDP           (2)
 #define WIFI_DA16XXX_SOCKET_TYPE_MAX           (3)

 #define sbFLAGS_IS_MESSAGE_BUFFER              ((uint8_t) 1) /* Set if the stream buffer was created as a message buffer, in which case it holds discrete messages rather than a stream. */
 #define sbBYTES_TO_STORE_MESSAGE_LENGTH        (sizeof(configMESSAGE_BUFFER_LENGTH_TYPE))
#endif

/* Unique number for WIFI Open status */
#define WIFI_OPEN                               (0x57495749ULL) // Is "WIFI" in ASCII

/***********************************************************************************************************************
 * Enumerations
 **********************************************************************************************************************/

/* Numeric return types for AT basic function commands */
typedef enum
{
    WIFI_DA16XXX_RETURN_OK = 0,        ///< WIFI_DA16XXX_RETURN_OK
    WIFI_DA16XXX_RETURN_INIT_OK,       ///< WIFI_DA16XXX_RETURN_INIT_OK
    WIFI_DA16XXX_RETURN_CONNECT,       ///< WIFI_DA16XXX_RETURN_CONNECT
    WIFI_DA16XXX_RETURN_CONNECT_FAIL,  ///< WIFI_DA16XXX_RETURN_CONNECT_FAIL
    WIFI_DA16XXX_RETURN_ERROR_CODES,
    WIFI_DA16XXX_RETURN_PROVISION_IDLE,
    WIFI_DA16XXX_RETURN_PROVISION_START
} da16xxx_return_code_t;

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/

/* Control instance for the da16xxx wifi module */
static wifi_da16xxx_instance_ctrl_t g_rm_wifi_da16xxx_instance;

#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */
static uint8_t rx_buffer[WIFI_DA16XXX_TEMP_BUFFER_SIZE] = {0};
static uint8_t rx_data_index = 0;

/* Structure that hold state information on the buffer. */
typedef struct StreamBufferDef_t                 /*lint !e9058 Style convention uses tag. */
{
    volatile size_t       xTail;                 /* Index to the next item to read within the buffer. */
    volatile size_t       xHead;                 /* Index to the next item to write within the buffer. */
    size_t                xLength;               /* The length of the buffer pointed to by pucBuffer. */
    size_t                xTriggerLevelBytes;    /* The number of bytes that must be in the stream buffer before a task that is waiting for data is unblocked. */
    volatile TaskHandle_t xTaskWaitingToReceive; /* Holds the handle of a task waiting for data, or NULL if no tasks are waiting. */
    volatile TaskHandle_t xTaskWaitingToSend;    /* Holds the handle of a task waiting to send data to a message buffer that is full. */
    uint8_t             * pucBuffer;             /* Points to the buffer itself - that is - the RAM that stores the data passed through the buffer. */
    uint8_t               ucFlags;
 #if (configUSE_TRACE_FACILITY == 1)
    UBaseType_t uxStreamBufferNumber;            /* Used for tracing purposes. */
 #endif
} StreamBuffer_t;

 #ifndef sbRECEIVE_COMPLETED
  #define sbRECEIVE_COMPLETED(pxStreamBuffer)                                                  \
    vTaskSuspendAll();                                                                         \
    {                                                                                          \
        if ((pxStreamBuffer)->xTaskWaitingToSend != NULL)                                      \
        {                                                                                      \
            (void) xTaskNotify((pxStreamBuffer)->xTaskWaitingToSend, (uint32_t) 0, eNoAction); \
            (pxStreamBuffer)->xTaskWaitingToSend = NULL;                                       \
        }                                                                                      \
    }                                                                                          \
    (void) xTaskResumeAll();
 #endif                                /* sbRECEIVE_COMPLETED */

/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/

static bool rm_wifi_da16xxx_handle_incoming_socket_data(da16xxx_socket_t * pSocket, uint8_t data_byte);

#endif

#if (WIFI_DA16XXX_CFG_CHECK_SDK_VERSION)
static fsp_err_t rm_wifi_da16xxx_check_sdk_version(void);

#endif

#if (1 == WIFI_DA16XXX_CFG_SNTP_ENABLE)
static fsp_err_t rm_wifi_da16xxx_sntp_service_init(wifi_da16xxx_instance_ctrl_t * const p_instance_ctrl);

#endif

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Opens and configures the WIFI_DA16XXX Middleware module.
 *
 *  @param[in]  p_cfg        Pointer to pin configuration structure.
 *
 *  @retval FSP_SUCCESS              WIFI_DA16XXX successfully configured.
 *  @retval FSP_ERR_ASSERTION        The parameter p_cfg or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_OUT_OF_MEMORY    There is no more heap memory available.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 *  @retval FSP_ERR_WIFI_INIT_FAILED WiFi module initialization failed.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_open (wifi_da16xxx_cfg_t const * const p_cfg)
{
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance;
    at_transport_da16xxx_data_t             atcmd;
    fsp_err_t err = FSP_SUCCESS;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(WIFI_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Clear the control structure */
    memset(p_instance_ctrl, 0, sizeof(wifi_da16xxx_instance_ctrl_t));

    p_instance_ctrl->num_creatable_sockets = p_cfg->num_sockets;
    if (1 < p_instance_ctrl->num_creatable_sockets)
    {
        p_instance_ctrl->curr_socket = 0;
    }

    /* Update control structure from configuration values */
    p_instance_ctrl->p_wifi_da16xxx_cfg = p_cfg;
    p_transport_instance                = p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;

    err = p_transport_instance->p_api->open(p_transport_instance->p_ctrl, p_transport_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if (WIFI_DA16XXX_CFG_CHECK_SDK_VERSION)
    err = rm_wifi_da16xxx_check_sdk_version();
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set AP mode */
    atcmd.p_at_cmd_string      = (uint8_t *) "AT+WFMODE=0\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_500MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

    /* Set Country Code */
    snprintf((char *) p_instance_ctrl->cmd_tx_buff,
             sizeof(p_instance_ctrl->cmd_tx_buff),
             "AT+WFCC=%s\r",
             p_cfg->country_code);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_500MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

#if (1 == WIFI_DA16XXX_CFG_SNTP_ENABLE)
    p_instance_ctrl->open = WIFI_OPEN; // Allows interface calls to complete for SNTP init.
    err = rm_wifi_da16xxx_sntp_service_init(p_instance_ctrl);
    p_instance_ctrl->open = 0;
    if (FSP_SUCCESS != err)
    {
        p_transport_instance->p_api->close(p_transport_instance->p_ctrl);
    }
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
#endif

    p_instance_ctrl->curr_socket_index = 0;
    p_instance_ctrl->open              = WIFI_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Disables WIFI_DA16XXX.
 *
 *  @retval FSP_SUCCESS              WIFI_DA16XXX closed successfully.
 *  @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_close (void)
{
    uint32_t  mutex_flag;
    fsp_err_t err = FSP_SUCCESS;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    atcmd.p_at_cmd_string      = (uint8_t *) "AT+WFQAP\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_200MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

    /* Tell wifi module to disconnect from the current AP */
    err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    p_instance_ctrl->open = 0;

    p_transport_instance->p_api->close(p_transport_instance->p_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 *  Disconnects from connected AP.
 *
 *  @retval FSP_SUCCESS              WIFI_DA16XXX disconnected successfully.
 *  @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_disconnect (void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    atcmd.p_at_cmd_string      = (uint8_t *) "AT+WFQAP\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_3SEC;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

    /* Tell wifi module to disconnect from the current AP */
    err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    if (FSP_SUCCESS == err)
    {
        memset(p_instance_ctrl->curr_ipaddr, 0, 4);
        memset(p_instance_ctrl->curr_subnetmask, 0, 4);
        memset(p_instance_ctrl->curr_gateway, 0, 4);
    }

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    return err;
}

/*******************************************************************************************************************//**
 *  Check if DA16XXX module is connected to an Access point.
 *
 * @param[out]  p_status                    Pointer to integer holding the socket connection status.
 *
 * @retval FSP_SUCCESS                      Function completed successfully.
 * @retval FSP_ERR_WIFI_AP_NOT_CONNECTED    WiFi module is not connected to access point.
 * @retval FSP_ERR_NOT_OPEN                 The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_connected (fsp_err_t * p_status)
{
    wifi_da16xxx_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t value = *((uint32_t *) &p_instance_ctrl->curr_ipaddr[0]);
    if (value != 0)
    {
        *p_status = FSP_SUCCESS;
    }
    else
    {
        *p_status = FSP_ERR_WIFI_AP_NOT_CONNECTED;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Return the network information for the connection to the access point.
 *
 * @param[out]  p_ip_addr           Pointer to integer holding the IP address.
 * @param[out]  p_subnet_mask       Pointer to integer holding the subnet mask.
 * @param[out]  p_gateway           Pointer to integer holding the gateway.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        A parameter pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_WIFI_AP_NOT_CONNECTED      No connection to access point has happened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_network_info_get (uint32_t * p_ip_addr, uint32_t * p_subnet_mask, uint32_t * p_gateway)
{
    wifi_da16xxx_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ASSERT(NULL != p_subnet_mask);
    FSP_ASSERT(NULL != p_gateway);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Make sure IP address has been assigned */
    uint32_t ip = *((uint32_t *) p_instance_ctrl->curr_ipaddr);
    if (!ip)
    {
        return FSP_ERR_WIFI_AP_NOT_CONNECTED;
    }

    *p_ip_addr     = ip;
    *p_subnet_mask = *((uint32_t *) p_instance_ctrl->curr_subnetmask);
    *p_gateway     = *((uint32_t *) p_instance_ctrl->curr_gateway);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Connects to the specified Wifi Access Point.
 *
 * @param[in]  p_ssid       Pointer to SSID of Wifi Access Point.
 * @param[in]  security     Security type to use for connection.
 * @param[in]  p_passphrase Pointer to the passphrase to use for connection.
 * @param[in]  enc_type     Encryption type to use for connection.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The parameter pSSID or p_passphrase is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_INVALID_ARGUMENT No commas are accepted in the SSID or Passphrase.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_connect (const char   * p_ssid,
                                   WIFISecurity_t security,
                                   const char   * p_passphrase,
                                   uint8_t        enc_type)
{
    fsp_err_t ret;
    uint32_t  mutex_flag;
    fsp_err_t status = FSP_SUCCESS;
    int32_t   scanf_ret;
    int       ipaddr[4]     = {0, 0, 0, 0};
    int       subnetmask[4] = {0, 0, 0, 0};
    int       gateway[4]    = {0, 0, 0, 0};

    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ssid);
    FSP_ASSERT(NULL != p_passphrase);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Commas are not accepted by the WiFi module in the SSID or Passphrase */
    FSP_ERROR_RETURN((NULL == strchr(p_ssid, ',') && NULL == strchr(p_passphrase, ',')), FSP_ERR_INVALID_ARGUMENT);

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    rm_wifi_da16xxx_connected(&status);

    if (FSP_SUCCESS == status)
    {
        /* If Wifi is already connected, do nothing and return fail. */
        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    memset(p_instance_ctrl->cmd_tx_buff, 0, sizeof(p_instance_ctrl->cmd_tx_buff));

    /* Connect to an OPEN security AP */
    if (eWiFiSecurityOpen == security)
    {
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+WFJAP=", 10);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, p_ssid, wificonfigMAX_SSID_LEN);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, ",", 2);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, "0", 2);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, ",", 2);
    }
    else if ((eWiFiSecurityWPA == security) || (eWiFiSecurityWPA2 == security))
    {
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+WFJAP=", 10);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, p_ssid, wificonfigMAX_SSID_LEN);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, ",", 2);
        if (eWiFiSecurityWPA == security)
        {
            strncat((char *) p_instance_ctrl->cmd_tx_buff, "2,", 3);
        }
        else
        {
            strncat((char *) p_instance_ctrl->cmd_tx_buff, "3,", 3);
        }

        switch (enc_type)
        {
            case WIFI_DA16XXX_TKIP_ENC_TYPE:
            {
                strncat((char *) p_instance_ctrl->cmd_tx_buff, "0,", 3);
                break;
            }

            case WIFI_DA16XXX_AES_ENC_TYPE:
            {
                strncat((char *) p_instance_ctrl->cmd_tx_buff, "1,", 3);
                break;
            }

            case WIFI_DA16XXX_TKIP_AES_ENC_TYPE:
            {
                strncat((char *) p_instance_ctrl->cmd_tx_buff, "2,", 3);
                break;
            }
        }
    }
    else if (eWiFiSecurityWPA3 == security)
    {
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+WFJAPA=", 11);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, p_ssid, wificonfigMAX_SSID_LEN);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, ",", 2);
    }
    else
    {
        /* Return with error for unsupported security types */
        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    strncat((char *) p_instance_ctrl->cmd_tx_buff, p_passphrase, wificonfigMAX_PASSPHRASE_LEN);
    strncat((char *) p_instance_ctrl->cmd_tx_buff, "\r", 2);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_5SEC;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_CONN_TEXT;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

    ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    if (FSP_SUCCESS == ret)
    {
        /* Parsing the response */
        p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag);

        atcmd.p_at_cmd_string      = (uint8_t *) "AT+NWDHC=1\r";
        atcmd.at_cmd_string_length = 0;
        atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
        atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
        atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_200MS;
        atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

        /* Enable DHCP */
        ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

        char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

        R_BSP_SoftwareDelay(WIFI_DA16XXX_TIMEOUT_3SEC, BSP_DELAY_UNITS_MILLISECONDS);

        /* Call to get IP address does not always work the first time */
        for (int index = 0; index < AT_TRANSPORT_DA16XXX_CFG_MAX_RETRIES_UART_COMMS; index++)
        {
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                             FSP_ERR_WIFI_FAILED);

            atcmd.p_at_cmd_string      = (uint8_t *) "AT+NWIP=?\r";
            atcmd.at_cmd_string_length = 0;
            atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
            atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
            atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_5SEC;
            atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
            atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

            /* Query the IP address from the current AP */
            ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

            p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

            FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

            /* Parsing the response */
            ptr = strstr(ptr, "+NWIP:");
            if (ptr == NULL)
            {
                R_BSP_SoftwareDelay(WIFI_DA16XXX_TIMEOUT_3SEC, BSP_DELAY_UNITS_MILLISECONDS);
            }
            else
            {
                ptr = ptr + strlen("+NWIP: ,");

                // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
                scanf_ret = sscanf((const char *) ptr,
                                   "%d.%d.%d.%d,%d.%d.%d.%d,%d.%d.%d.%d",
                                   &ipaddr[0],
                                   &ipaddr[1],
                                   &ipaddr[2],
                                   &ipaddr[3],
                                   &subnetmask[0],
                                   &subnetmask[1],
                                   &subnetmask[2],
                                   &subnetmask[3],
                                   &gateway[0],
                                   &gateway[1],
                                   &gateway[2],
                                   &gateway[3]);

                FSP_ERROR_RETURN(12 == scanf_ret, FSP_ERR_WIFI_FAILED);
                FSP_ERROR_RETURN(0 != (ipaddr[0] | ipaddr[1] | ipaddr[2] | ipaddr[3]), FSP_ERR_WIFI_FAILED);

                for (int i = 0; i < 4; i++)
                {
                    p_instance_ctrl->curr_ipaddr[i]     = (uint8_t) ipaddr[i];
                    p_instance_ctrl->curr_subnetmask[i] = (uint8_t) subnetmask[i];
                    p_instance_ctrl->curr_gateway[i]    = (uint8_t) gateway[i];
                }

                break;
            }
        }
    }

    return ret;
}

/*******************************************************************************************************************//**
 *  Get MAC address.
 *
 * @param[out] p_macaddr     Pointer array to hold mac address.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The parameter p_macaddr is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_mac_addr_get (uint8_t * p_macaddr)
{
    fsp_err_t    ret;
    int32_t      err;
    unsigned int macaddr[6];
    uint32_t     mutex_flag;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_macaddr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    atcmd.p_at_cmd_string      = (uint8_t *) "AT+WFMAC=?\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

    if (FSP_SUCCESS == ret)
    {
        /* Parsing the response */
        ptr = strstr(ptr, "+WFMAC:");
        FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);

        ptr = ptr + strlen("+WFMAC:");

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        err = sscanf((const char *) ptr,
                     "%2x:%2x:%2x:%2x:%2x:%2x",
                     &macaddr[0],
                     &macaddr[1],
                     &macaddr[2],
                     &macaddr[3],
                     &macaddr[4],
                     &macaddr[5]);
        if (6 == err)
        {
            for (int i = 0; i < 6; i++)
            {
                p_macaddr[i] = (uint8_t) macaddr[i];
            }
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
        }
    }

    return ret;
}

/*******************************************************************************************************************//**
 *  Get the information about local Wifi Access Points.
 *
 * @param[out]  p_results      Pointer to a structure array holding scanned Access Points.
 * @param[in]   maxNetworks  Size of the structure array for holding APs.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The parameter p_results or p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_WIFI_SCAN_COMPLETE Wifi scan has completed.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_scan (WIFIScanResult_t * p_results, uint32_t maxNetworks)
{
    fsp_err_t ret = FSP_ERR_INTERNAL;
    int32_t   err;
    uint32_t  idx = 0;
    uint8_t * bssid;
    uint32_t  mutex_flag;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_results);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

    FSP_ERROR_RETURN((NULL != p_results) && (0 != maxNetworks), FSP_ERR_INVALID_ARGUMENT);

    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    atcmd.p_at_cmd_string      = (uint8_t *) "AT+WFSCAN\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_8SEC;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

    /* Parsing the response */
    ptr = strstr(ptr, "+WFSCAN:");
    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);
    ptr = ptr + strlen("+WFSCAN:");

    if (((*(ptr) == 'O') && (*(ptr + 1) == 'K')))
    {

        /* Returning if there are ZERO scanned APs */
        return ret;
    }

    do
    {
        if (((*(ptr + 2) == 'O') && (*(ptr + 3) == 'K')) || (idx >= 10))
        {
            break;
        }

        /* BSSID */
        bssid = &p_results[idx].ucBSSID[0];
        unsigned int bssid2[6];
        memset(bssid2, 0, sizeof(bssid2));

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        err = sscanf(ptr, "%x:%x:%x:%x:%x:%x", &bssid2[0], &bssid2[1], &bssid2[2], &bssid2[3], &bssid2[4], &bssid2[5]);

        FSP_ERROR_RETURN(6 == err, FSP_ERR_WIFI_FAILED);

        if (6 != err)
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        /* Copy the bssid data into result */
        for (int i = 0; i < wificonfigMAX_BSSID_LEN; i++)
        {
            bssid[i] = (uint8_t) bssid2[i];
        }

        /* Advance string pointer to next section of scan info */
        ptr = strchr(ptr, '\t');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        /* Ignore the frequency */
        ptr = strchr(ptr, '\t');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        /* Copy signal strength from scan info buffer */
        uint32_t temp_val;

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        err = sscanf(ptr, "%d", (int *) &temp_val);
        if (1 != err)
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        p_results[idx].cRSSI = (int8_t) temp_val;;

        /* Advance string pointer to next section of scan info */
        ptr = strchr(ptr, '\t');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        if ('\t' != *(ptr))
        {
            if (0 == strncmp(ptr, "[WPA2-PSK", 9))
            {
                p_results[idx].xSecurity = eWiFiSecurityWPA2;
            }
            else if (0 == strncmp(ptr, "[WPA-PSK", 8))
            {
                p_results[idx].xSecurity = eWiFiSecurityWPA;
            }
            else if (0 == strncmp(ptr, "[OPEN]", 6))
            {
                p_results[idx].xSecurity = eWiFiSecurityOpen;
            }
            else if (0 == strncmp(ptr, "[WPS]", 5))
            {
                p_results[idx].xSecurity = eWiFiSecurityNotSupported;
            }
            else
            {
                /* Do Nothing */
            }
        }

        /* Advance string pointer to next section of scan info */
        ptr = strchr(ptr, '\t');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        /* Copy SSID from scan info buffer */
        int idx_ssid = 0;
        while ((*ptr != '\n') && (idx_ssid < (wificonfigMAX_SSID_LEN - 1)))
        {
            p_results[idx].ucSSID[idx_ssid++] = (uint8_t) *ptr;
            ptr++;
        }

        /* Advance string pointer to next section of scan info */
        ptr++;
    } while (++idx < maxNetworks);

    return ret;
}

/*******************************************************************************************************************//**
 *  Ping an IP address on the network.
 *
 * @param[in]   p_ip_addr    Pointer to IP address array.
 * @param[in]   count      Number of pings to attempt.
 * @param[in]   interval_ms Interval between ping attempts.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The parameter p_ip_addr is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_ping (uint8_t * p_ip_addr, int count, uint32_t interval_ms)
{
    FSP_PARAMETER_NOT_USED(interval_ms);
    fsp_err_t func_ret = FSP_ERR_WIFI_FAILED;
    uint32_t  mutex_flag;
    int       sent_cnt = 0;
    int       recv_cnt = 0;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ERROR_RETURN(0 != count, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));
    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN((FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag)),
                     FSP_ERR_WIFI_FAILED);

    snprintf((char *) p_instance_ctrl->cmd_tx_buff,
             sizeof(p_instance_ctrl->cmd_tx_buff),
             "AT+NWPING=0,%d.%d.%d.%d,%d\r",
             p_ip_addr[0],
             p_ip_addr[1],
             p_ip_addr[2],
             p_ip_addr[3],
             count);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_3SEC;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    func_ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    /* Parsing the response */
    ptr = strstr(ptr, "+NWPING:");
    if (ptr != NULL)
    {
        ptr = ptr + strlen("+NWPING:");

        sent_cnt = strtol(ptr, NULL, 10);

        /* Advance string pointer to next section */
        ptr = strchr(ptr, ',');
        if (NULL != ptr)
        {
            ptr++;
        }

        recv_cnt = strtol(ptr, NULL, 10);

        if (sent_cnt != recv_cnt)
        {
            func_ret = FSP_ERR_WIFI_FAILED;
        }
    }
    else
    {
        func_ret = FSP_ERR_WIFI_FAILED;
    }

    return func_ret;
}

/*******************************************************************************************************************//**
 *  Get the IP address from the module.
 *
 * @param[in]  p_ip_addr            Pointer to the IP address string.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_ipaddr_get (uint32_t * p_ip_addr)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    int32_t   scanf_ret;
    int       index         = 0;
    int       ipaddr[4]     = {0, 0, 0, 0};
    int       subnetmask[4] = {0, 0, 0, 0};
    int       gateway[4]    = {0, 0, 0, 0};

    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);
    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    /* Take mutexes */
    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);

    /* Call to get IP address does not always work the first time */
    for (index = 0; index < AT_TRANSPORT_DA16XXX_CFG_MAX_RETRIES_UART_COMMS; index++)
    {
        FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl,
                                                                               mutex_flag),
                         FSP_ERR_WIFI_FAILED);

        /* Query the IP address from the current AP */
        atcmd.p_at_cmd_string      = (uint8_t *) "AT+NWIP=?\r";
        atcmd.at_cmd_string_length = 0;
        atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
        atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
        atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_5SEC;
        atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
        err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        /* Parsing the response */
        ptr = strstr(ptr, "+NWIP:");
        if (ptr == NULL)
        {
            R_BSP_SoftwareDelay(WIFI_DA16XXX_TIMEOUT_3SEC, BSP_DELAY_UNITS_MILLISECONDS);
        }
        else
        {
            ptr = ptr + strlen("+NWIP: ,");

            // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
            scanf_ret = sscanf((const char *) ptr,
                               "%d.%d.%d.%d,%d.%d.%d.%d,%d.%d.%d.%d",
                               &ipaddr[0],
                               &ipaddr[1],
                               &ipaddr[2],
                               &ipaddr[3],
                               &subnetmask[0],
                               &subnetmask[1],
                               &subnetmask[2],
                               &subnetmask[3],
                               &gateway[0],
                               &gateway[1],
                               &gateway[2],
                               &gateway[3]);

            FSP_ERROR_RETURN(12 == scanf_ret, FSP_ERR_WIFI_FAILED);
            FSP_ERROR_RETURN(0 != (ipaddr[0] | ipaddr[1] | ipaddr[2] | ipaddr[3]), FSP_ERR_WIFI_FAILED);

            for (int i = 0; i < 4; i++)
            {
                p_instance_ctrl->curr_ipaddr[i] = (uint8_t) ipaddr[i];
                p_ip_addr[i] = (uint8_t) ipaddr[i];
                p_instance_ctrl->curr_subnetmask[i] = (uint8_t) subnetmask[i];
                p_instance_ctrl->curr_gateway[i]    = (uint8_t) gateway[i];
            }

            break;
        }
    }

    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_CFG_MAX_RETRIES_UART_COMMS != (index), FSP_ERR_WIFI_FAILED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Initiate a DNS lookup for a given URL.
 *
 * @param[in]  p_textstring      Pointer to array holding URL to query from DNS.
 * @param[out]  p_ip_addr          Pointer to IP address returned from look up.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl, p_textstring, p_ip_addr is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_INVALID_ARGUMENT The URL passed in is to long.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_dns_query (const char * p_textstring, uint8_t * p_ip_addr)
{
    fsp_err_t func_ret;
    int32_t   scanf_ret;
    int       temp_addr[4] = {0, 0, 0, 0};
    int32_t   i            = 0;
    uint32_t  mutex_flag;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    char * buff = (char *) p_instance_ctrl->cmd_rx_buff;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_textstring);
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((sizeof(p_instance_ctrl->cmd_tx_buff) - 16) > strlen(p_textstring), FSP_ERR_INVALID_ARGUMENT)
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWHOST=", sizeof(p_instance_ctrl->cmd_tx_buff));
    snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
             sizeof(p_instance_ctrl->cmd_tx_buff), "%s\r\n", p_textstring);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_8SEC;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    func_ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    if (FSP_SUCCESS == func_ret)
    {
        /* Parsing the response */
        buff = strstr(buff, "+NWHOST:");
        FSP_ERROR_RETURN(NULL != buff, FSP_ERR_INVALID_DATA);

        buff = buff + strlen("+NWHOST:");

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        scanf_ret = sscanf((const char *) buff,
                           "%d.%d.%d.%d",
                           &temp_addr[0],
                           &temp_addr[1],
                           &temp_addr[2],
                           &temp_addr[3]);

        FSP_ERROR_RETURN(4 == scanf_ret, FSP_ERR_WIFI_FAILED);

        for (i = 0; i < 4; i++)
        {
            if (temp_addr[i] <= UINT8_MAX)
            {
                p_ip_addr[i] = (uint8_t) temp_addr[i];
            }
            else
            {
                func_ret = FSP_ERR_WIFI_FAILED;
                break;
            }
        }
    }

    return func_ret;
}

#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */

/*******************************************************************************************************************//**
 *  Get the next available socket ID.
 *
 * @param[out]  p_socket_id    Pointer to an integer to hold the socket ID.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_socket_id is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred in the execution of this function
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_avail_socket_get (uint32_t * p_socket_id)
{
    wifi_da16xxx_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;

 #if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_socket_id);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    for (uint32_t i = 0; i < p_instance_ctrl->num_creatable_sockets; i++)
    {
        if (0 == p_instance_ctrl->sockets[i].socket_create_flag)
        {
            *p_socket_id = (uint8_t) i;

            return FSP_SUCCESS;
        }
    }

    *p_socket_id = UINT8_MAX;

    return FSP_ERR_WIFI_FAILED;
}

/*******************************************************************************************************************//**
 *  Get the socket status.
 *
 * @param[in]  socket_no        Socket ID number.
 * @param[out] p_socket_status    Pointer to an integer to hold the socket status
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl or p_socket_status is NULL. The value of socket_no
 *                                  is greater than/equal num_creatable_sockets.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_socket_status_get (uint32_t socket_no, uint32_t * p_socket_status)
{
    wifi_da16xxx_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;

 #if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_socket_status);
    FSP_ASSERT(socket_no < p_instance_ctrl->num_creatable_sockets);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    *p_socket_status = p_instance_ctrl->sockets[socket_no].socket_status;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Create a new socket instance.
 *
 * @param[in]  socket_no        Socket ID number.
 * @param[in]  type             Socket type.
 * @param[in]  ipversion        Socket IP type.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_UNSUPPORTED      Selected mode not supported by this API
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_socket_create (uint32_t socket_no, uint32_t type, uint32_t ipversion)
{
    wifi_da16xxx_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;

 #if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(type <= WIFI_DA16XXX_SOCKET_TYPE_MAX);
 #endif

    if ((1 == p_instance_ctrl->sockets[socket_no].socket_create_flag) || (1 < p_instance_ctrl->num_creatable_sockets))
    {
        return FSP_ERR_WIFI_FAILED;
    }

    if (WIFI_DA16XXX_SOCKET_TYPE_TCP_CLIENT == type)
    {
        p_instance_ctrl->sockets[socket_no].socket_type = WIFI_DA16XXX_SOCKET_TYPE_TCP_CLIENT;
    }
    else
    {
        return FSP_ERR_UNSUPPORTED;
    }

    for (uint32_t i = 0; i < p_instance_ctrl->num_creatable_sockets; i++)
    {
        if (NULL == p_instance_ctrl->sockets[i].socket_byteq_hdl)
        {
            p_instance_ctrl->sockets[i].socket_byteq_hdl =
                xStreamBufferCreateStatic(sizeof(p_instance_ctrl->sockets[i].socket_recv_buff),
                                          1,
                                          p_instance_ctrl->sockets[i].socket_recv_buff,
                                          &p_instance_ctrl->sockets[i].socket_byteq_struct);
        }

        FSP_ERROR_RETURN(NULL != p_instance_ctrl->sockets[i].socket_byteq_hdl, FSP_ERR_WIFI_FAILED);
    }

    p_instance_ctrl->curr_socket_index = socket_no;
    memset(rx_buffer, 0, sizeof(rx_buffer));

    BaseType_t rst_status = xStreamBufferReset(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl);
    if (pdPASS != rst_status)
    {
        return FSP_ERR_WIFI_FAILED;
    }

    FSP_PARAMETER_NOT_USED(ipversion);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Connect to a specific IP and Port using socket.
 *
 * @param[in]  socket_no        Socket ID number.
 * @param[in]  ipaddr           IP address for socket connection.
 * @param[in]  port             Port number for socket connection.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_tcp_connect (uint32_t socket_no, uint32_t ipaddr, uint32_t port)
{
    fsp_err_t ret = FSP_SUCCESS;
    uint32_t  mutex_flag;

    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

 #if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    memset(p_instance_ctrl->cmd_tx_buff, 0, sizeof(p_instance_ctrl->cmd_tx_buff));
    memset(p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.strcpy) Disable warning about use of strcpy
    strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+TRTC=", sizeof(p_instance_ctrl->cmd_tx_buff));
    snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
             sizeof(p_instance_ctrl->cmd_tx_buff), "%d.%d.%d.%d,%d\r\n", (uint8_t) (ipaddr >> 24),
             (uint8_t) (ipaddr >> 16),
             (uint8_t) (ipaddr >> 8), (uint8_t) (ipaddr), (int) port);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_5SEC;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

    p_instance_ctrl->sockets[socket_no].remote_ipaddr[0]       = (uint8_t) (ipaddr >> 24);
    p_instance_ctrl->sockets[socket_no].remote_ipaddr[1]       = (uint8_t) (ipaddr >> 16);
    p_instance_ctrl->sockets[socket_no].remote_ipaddr[2]       = (uint8_t) (ipaddr >> 8);
    p_instance_ctrl->sockets[socket_no].remote_ipaddr[3]       = (uint8_t) (ipaddr);
    p_instance_ctrl->sockets[socket_no].remote_port            = (int) port;
    p_instance_ctrl->sockets[socket_no].socket_status          = WIFI_DA16XXX_SOCKET_STATUS_CONNECTED;
    p_instance_ctrl->sockets[socket_no].socket_read_write_flag = WIFI_DA16XXX_SOCKET_READ |
                                                                 WIFI_DA16XXX_SOCKET_WRITE;
    p_instance_ctrl->sockets[socket_no].socket_recv_state  = WIFI_DA16XXX_RECV_PREFIX;
    p_instance_ctrl->sockets[socket_no].socket_create_flag = 1;

    return ret;
}

/***********************************************************************************************************************
 *  Send data over TCP to a server.
 *
 * @param[in]  socket_no        Socket ID number.
 * @param[in]  p_data            Pointer to data to send.
 * @param[in]  length           Length of data to send.
 * @param[in]  timeout_ms       Timeout to wait for transmit end event
 *
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl or parameter p_data is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
int32_t rm_wifi_da16xxx_send (uint32_t socket_no, const uint8_t * p_data, uint32_t length, uint32_t timeout_ms)
{
    uint32_t  sent_count = 0;
    uint32_t  tx_length;
    fsp_err_t ret;
    uint32_t  mutex_flag;
    int       header_len;

    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

 #if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(WIFI_DA16XXX_CFG_CMD_TX_BUF_SIZE > length, FSP_ERR_INVALID_ARGUMENT);
 #endif

    /* If socket write has been disabled by shutdown call then return 0 bytes sent */
    if (!(p_instance_ctrl->sockets[socket_no].socket_read_write_flag & WIFI_DA16XXX_SOCKET_WRITE))
    {
        return 0;
    }

    if ((0 == p_instance_ctrl->sockets[socket_no].socket_create_flag) ||
        (WIFI_DA16XXX_SOCKET_STATUS_CONNECTED != p_instance_ctrl->sockets[socket_no].socket_status))
    {
        return -FSP_ERR_WIFI_FAILED;
    }

    mutex_flag = WIFI_DA16XXX_MUTEX_TX;
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     -FSP_ERR_WIFI_FAILED);

    if (socket_no != p_instance_ctrl->curr_socket_index)
    {
        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        return -FSP_ERR_WIFI_FAILED;
    }

    memset(p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

 #define DATA_IP_MODE    "\x1B"

    while (sent_count < length)
    {
        /* Put the DA16XXX module into data input mode */
        header_len = snprintf((char *) p_instance_ctrl->cmd_tx_buff,
                              sizeof(p_instance_ctrl->cmd_tx_buff),
                              "%s%s%d%d,%d.%d.%d.%d,%d,%s,",
                              DATA_IP_MODE,
                              "S",
                              p_instance_ctrl->sockets[socket_no].socket_type,
                              (int) length,
                              p_instance_ctrl->sockets[socket_no].remote_ipaddr[0],
                              p_instance_ctrl->sockets[socket_no].remote_ipaddr[1],
                              p_instance_ctrl->sockets[socket_no].remote_ipaddr[2],
                              p_instance_ctrl->sockets[socket_no].remote_ipaddr[3],
                              p_instance_ctrl->sockets[socket_no].remote_port,
                              "r");

        if (length - sent_count > (uint32_t) (WIFI_DA16XXX_CFG_CMD_TX_BUF_SIZE - header_len))
        {
            tx_length = (uint32_t) (WIFI_DA16XXX_CFG_CMD_TX_BUF_SIZE - header_len);
        }
        else
        {
            tx_length = length - sent_count;
        }

        /* Send data through a socket */
        memcpy((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
               (char *) p_data,
               tx_length);

        atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
        atcmd.at_cmd_string_length = tx_length + (uint32_t) header_len;
        atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
        atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
        atcmd.timeout_ms           = timeout_ms;
        atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
        ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

        if (FSP_SUCCESS != ret)
        {
            p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == ret, -FSP_ERR_WIFI_FAILED);

        sent_count += tx_length;
        p_data      = p_data + sent_count;
    }

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    return (int32_t) sent_count;
}

/*******************************************************************************************************************//**
 *  Receive data over TCP from a server.
 *
 * @param[in]  socket_no        Socket ID number.
 * @param[out] p_data           Pointer to data received from socket.
 * @param[in]  length           Length of data array used for receive.
 * @param[in]  timeout_ms       Timeout to wait for data to be received from socket.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl or parameter p_data is NULL.
 **********************************************************************************************************************/
int32_t rm_wifi_da16xxx_recv (uint32_t socket_no, uint8_t * p_data, uint32_t length, uint32_t timeout_ms)
{
    uint32_t mutex_flag;
    uint32_t recvcnt = 0;
    int32_t  ret     = 0;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;

 #if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0 != length, FSP_ERR_INVALID_ARGUMENT);
 #endif

    /* if socket read has been disabled by shutdown call then return any bytes left in the stream buffer.
     * However if 0 bytes left, return error. */
    if (!(p_instance_ctrl->sockets[socket_no].socket_read_write_flag & WIFI_DA16XXX_SOCKET_READ))
    {
        size_t xReceivedBytes = xStreamBufferReceive(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl,
                                                     p_data,
                                                     length,
                                                     0); /* No wait needed as data is already in stream buffer*/
        if (0 < xReceivedBytes)
        {
            return (int32_t) xReceivedBytes;
        }

        return -FSP_ERR_WIFI_FAILED;
    }

    /* Take the receive mutex */
    mutex_flag = (WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     -FSP_ERR_WIFI_FAILED);

    if (0 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        return -FSP_ERR_WIFI_FAILED;
    }

    if (socket_no != p_instance_ctrl->curr_socket_index)
    {
        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        return AT_TRANSPORT_DA16XXX_ERR_UNKNOWN;
    }

    volatile size_t xReceivedBytes =
        xStreamBufferReceive(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl, (p_data + recvcnt), 1,
                             pdMS_TO_TICKS(timeout_ms));
    if (xReceivedBytes == 1)
    {
        recvcnt++;

        /* Get the rest of the transmitted data from the stream buffer */
        for (uint32_t i = 0; i < length; i++)
        {
            uint32_t num_bytes_left = length - recvcnt;

            if (0 == num_bytes_left)
            {
                ret = (int32_t) recvcnt;
                break;
            }

            xStreamBufferSetTriggerLevel(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl, num_bytes_left);
            xReceivedBytes =
                xStreamBufferReceive(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl,
                                     (p_data + recvcnt),
                                     num_bytes_left,
                                     pdMS_TO_TICKS(WIFI_DA16XXX_TIMEOUT_10MS));
            if (xReceivedBytes > 0)
            {
                recvcnt += xReceivedBytes;
            }
            else
            {
                ret = (int32_t) recvcnt;
                break;
            }
        }                              /* For */
    }
    else
    {
        ret = 0;                       // Timeout occurred
    }

    /* Reset the trigger level for socket stream buffer */
    xStreamBufferSetTriggerLevel(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl, 1);
    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    return ret;
}

/*******************************************************************************************************************//**
 *  Disconnect a specific socket connection.
 *
 * @param[in]  socket_no    Socket ID to disconnect
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_INVALID_ARGUMENT Bad parameter value was passed into function.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_da16xxx_socket_disconnect (uint32_t socket_no)
{
    fsp_err_t ret = FSP_ERR_WIFI_FAILED;
    uint32_t  mutex_flag;

    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

 #if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Test if socket has been created for socket index passed in to function */
    if (1 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
        FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl,
                                                                               mutex_flag),
                         FSP_ERR_WIFI_FAILED);

        // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+TRTRM=", sizeof(p_instance_ctrl->cmd_tx_buff));
        snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
                 sizeof(p_instance_ctrl->cmd_tx_buff), "%d\r", p_instance_ctrl->sockets[socket_no].socket_type);

        atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
        atcmd.at_cmd_string_length = 0;
        atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
        atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
        atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_2SEC;
        atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
        ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

        p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

        FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

        /* Clear the create flag, set status to closed, and flush the stream buffer */
        if (FSP_SUCCESS == ret)
        {
            p_instance_ctrl->sockets[socket_no].socket_create_flag     = 0;
            p_instance_ctrl->sockets[socket_no].socket_status          = WIFI_DA16XXX_SOCKET_STATUS_CLOSED;
            p_instance_ctrl->sockets[socket_no].socket_read_write_flag = 0;

            BaseType_t rst_status = xStreamBufferReset(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl);
            if (pdPASS != rst_status)
            {
                return FSP_ERR_WIFI_FAILED;
            }
        }
    }

    return ret;
}

#endif

#if (1 == WIFI_DA16XXX_CFG_SNTP_ENABLE)

/*******************************************************************************************************************//**
 *  Initialize DA16XXX module SNTP client service.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_INVALID_ARGUMENT Parameter passed into function was invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_da16xxx_sntp_service_init (wifi_da16xxx_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err = FSP_ERR_INTERNAL;
    uint8_t   ip_address_sntp_server[4] = {0, 0, 0, 0};
    int       err_scan = 0;
    char    * token;
    char      sntp_ip[WIFI_DA16XXX_IPV4_MAX_LENGTH + 1];

    /* Check if the input IP address length exceeds the expected length */
    FSP_ERROR_RETURN(strlen(
                         (char *) p_instance_ctrl->p_wifi_da16xxx_cfg->sntp_server_ip) < WIFI_DA16XXX_IPV4_MAX_LENGTH,
                     FSP_ERR_INVALID_ARGUMENT);

    /* Set the SNTP server IP address */
    strncpy(sntp_ip, (char *) p_instance_ctrl->p_wifi_da16xxx_cfg->sntp_server_ip, WIFI_DA16XXX_IPV4_MAX_LENGTH + 1);
    token = strtok(sntp_ip, ".");

    while ((token != NULL) && (err_scan < 4))
    {
        ip_address_sntp_server[err_scan++] = (uint8_t) strtol(token, NULL, 10);
        token = strtok(NULL, ".");
    }

    /* Check if the input IP address length did not contain 4 segments */
    FSP_ERROR_RETURN(4 == err_scan, FSP_ERR_INVALID_ARGUMENT);

    /* Configure the SNTP Server Address */
    err = RM_WIFI_DA16XXX_SntpServerIpAddressSet((uint8_t *) ip_address_sntp_server);

    if (FSP_SUCCESS == err)
    {
        /* Enable/disable the SNTP clinet */
        err = RM_WIFI_DA16XXX_SntpEnableSet(WIFI_DA16XXX_SNTP_ENABLE);
    }

    /* Set the SNTP Timezone configuration string */
    if (FSP_SUCCESS == err)
    {
        err = RM_WIFI_DA16XXX_SntpTimeZoneSet(p_instance_ctrl->p_wifi_da16xxx_cfg->sntp_utc_offset_in_hours,
                                              0,
                                              WIFI_DA16XXX_SNTP_DAYLIGHT_SAVINGS_DISABLE);
    }

    return err;
}

#endif

/*! \endcond */

/*******************************************************************************************************************//**
 * @addtogroup WIFI_DA16XXX WIFI_DA16XXX
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Set the SNTP Client Server IP Address
 *
 *  @param[in]  p_server_ip_addr     Pointer to IP address of SNTP server in byte array format.
 *
 *  @retval FSP_SUCCESS              Successfully set the value.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 *  @retval FSP_ERR_ASSERTION        The parameter p_server_ip_addr is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_SntpServerIpAddressSet (uint8_t * p_server_ip_addr)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_server_ip_addr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
    strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWSNS=", sizeof(p_instance_ctrl->cmd_tx_buff));

    snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
             sizeof(p_instance_ctrl->cmd_tx_buff), "%u.%u.%u.%u\r\n", p_server_ip_addr[0], p_server_ip_addr[1],
             p_server_ip_addr[2], p_server_ip_addr[3]);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    return err;
}

/*******************************************************************************************************************//**
 *  Set the SNTP Client to Enable or Disable
 *
 *  @param[in]  enable               Flag to indicate enable/disable for SNTP support.
 *
 *  @retval FSP_SUCCESS              Successfully set the value.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_SntpEnableSet (wifi_da16xxx_sntp_enable_t enable)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    if (WIFI_DA16XXX_SNTP_ENABLE == enable)
    {
        // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWSNTP=1\r\n", sizeof(p_instance_ctrl->cmd_tx_buff));

        atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
        atcmd.at_cmd_string_length = 0;
        atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
        atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
        atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_400MS;
        atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
        err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

        p_instance_ctrl->is_sntp_enabled = true;
    }
    else
    {
        // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWSNTP=0\r\n", sizeof(p_instance_ctrl->cmd_tx_buff));

        atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
        atcmd.at_cmd_string_length = 0;
        atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
        atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
        atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_400MS;
        atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
        err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

        p_instance_ctrl->is_sntp_enabled = false;
    }

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    return err;
}

/*******************************************************************************************************************//**
 *  Set the SNTP Client Timezone
 *
 *  @param[in]  utc_offset_in_hours  Timezone in UTC offset in hours
 *  @param[in]  minutes               Number of minutes used for timezone offset from GMT.
 *  @param[in]  daylightSavingsEnable Enable/Disable daylight saving in the timezone calculation.
 *
 *  @retval FSP_SUCCESS              Successfully set the value.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 *  @retval FSP_ERR_INVALID_ARGUMENT Parameter passed into function was invalid.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_SntpTimeZoneSet (int                                         utc_offset_in_hours,
                                           uint32_t                                    minutes,
                                           wifi_da16xxx_sntp_daylight_savings_enable_t daylightSavingsEnable)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(((utc_offset_in_hours >= -12) && (utc_offset_in_hours <= 12)), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0 == minutes) && (0 == daylightSavingsEnable), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    int utc_offset_in_secs = (utc_offset_in_hours * HOURS_IN_SECONDS);
    snprintf((char *) p_instance_ctrl->cmd_tx_buff,
             sizeof(p_instance_ctrl->cmd_tx_buff),
             "AT+TZONE=%d\r",
             utc_offset_in_secs);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_400MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

    err = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    FSP_PARAMETER_NOT_USED(minutes);
    FSP_PARAMETER_NOT_USED(daylightSavingsEnable);

    return err;
}

/*******************************************************************************************************************//**
 *  Get the current local time based on current timezone in a string . Exp: YYYY-MM-DD,HOUR:MIN:SECS
 *
 *  @param[out]  p_local_time        Returns local time in string format.
 *  @param[in]  size_string          Size of p_local_time string buffer.The size of this string needs to be at least 25 bytes
 *
 *  @retval FSP_SUCCESS              Successfully returned the local time string.
 *  @retval FSP_ERR_ASSERTION        The parameter local_time or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 *  @retval FSP_ERR_INVALID_SIZE     String size value passed in exceeds maximum.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_LocalTimeGet (uint8_t * p_local_time, uint32_t size_string)
{
    uint32_t  mutex_flag;
    fsp_err_t ret;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    char * p_str = (char *) p_instance_ctrl->cmd_rx_buff;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_local_time);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(WIFI_DA16XXX_LOCAL_TIME_STR_SIZE <= size_string, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN(p_instance_ctrl->is_sntp_enabled == true, FSP_ERR_WIFI_FAILED);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    memset(p_local_time, 0, size_string);
    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    atcmd.p_at_cmd_string      = (uint8_t *) "AT+TIME=?\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_2SEC;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

    ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    if (FSP_SUCCESS == ret)
    {
        /* Parse the response */
        p_str = strstr(p_str, "+TIME:");
        FSP_ERROR_RETURN(NULL != p_str, FSP_ERR_WIFI_FAILED);

        p_str = p_str + strlen("+TIME:");

        /* Copy SSID from scan info buffer */
        uint32_t idx = 0;
        while ((*p_str != '\r') && (idx < (size_string - 1)))
        {
            p_local_time[idx++] = (uint8_t) *p_str;
            p_str++;
        }
    }

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    return ret;
}

/*******************************************************************************************************************//**
 *  Sends any AT command compatible with the DA16XXX module. Provide optional buffer to receive the response.
 *
 * @param[in]  at_string            Input AT command string from the user.
 * @param[in]  response_buffer      Optional buffer for receiving the response.
 * @param[in]  length               Size of optional buffer.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_ARGUMENT Input was not a valid AT command.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_DA16XXX_GenericAtSendRcv (char const * const at_string, char * const response_buffer, uint32_t length)
{
    uint32_t  mutex_flag;
    fsp_err_t ret;
    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

#if (WIFI_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != at_string, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Check if the user input string is a valid AT command e.g. ATE, AT+SDKVER */
    FSP_ERROR_RETURN((0 == strncmp(at_string, "?", 1)) ||
                     (0 == strncmp(at_string, "help", 4)) ||
                     (0 == strncmp(at_string, "AT", 2)),
                     FSP_ERR_INVALID_ARGUMENT);

    /* Take mutexes */
    mutex_flag = (WIFI_DA16XXX_MUTEX_TX | WIFI_DA16XXX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == p_transport_instance->p_api->takeMutex(p_transport_instance->p_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    snprintf((char *) p_instance_ctrl->cmd_tx_buff, sizeof(p_instance_ctrl->cmd_tx_buff), "%s\r", at_string);

    atcmd.p_at_cmd_string      = (uint8_t *) p_instance_ctrl->cmd_tx_buff;
    atcmd.at_cmd_string_length = 0;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_500MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;

    if (response_buffer != NULL)
    {
        memset(response_buffer, 0, length);

        atcmd.p_response_buffer = (uint8_t *) response_buffer;
    }
    else
    {
        memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

        atcmd.p_response_buffer = p_instance_ctrl->cmd_rx_buff;
    }

    ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    p_transport_instance->p_api->giveMutex(p_transport_instance->p_ctrl, mutex_flag);

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_INIT_FAILED);

    return ret;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_DA16XXX)
 **********************************************************************************************************************/

/*! \cond PRIVATE */

/***********************************************************************************************************************
 * Local Functions definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Common callback function called in the AT Transport callback function.
 **********************************************************************************************************************/
bool rm_wifi_da16xxx_callback (at_transport_da16xxx_callback_args_t * p_args)
{
    bool ret = 0;

    if (p_args->event == AT_TRANSPORT_RX_BYTE_EVENT)
    {
#if (BSP_CFG_RTOS == 0)                /* Baremetal */
        ret = false;
#endif

#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */
        wifi_da16xxx_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;

        if (1 == p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_create_flag)
        {
            ret = rm_wifi_da16xxx_handle_incoming_socket_data(&p_instance_ctrl->sockets[p_instance_ctrl->
                                                                                        curr_socket_index],
                                                              p_args->data);
        }
#endif
    }

    return ret;
}

#if (WIFI_DA16XXX_CFG_CHECK_SDK_VERSION)

/*******************************************************************************************************************//**
 *  Checks the minimum SDK version of the DA16XXX module is valid
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_INVALID_DATA     Function did not return a valid SDK version.
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_da16xxx_check_sdk_version (void)
{
    fsp_err_t ret = FSP_SUCCESS;

    wifi_da16xxx_instance_ctrl_t          * p_instance_ctrl      = &g_rm_wifi_da16xxx_instance;
    at_transport_da16xxx_instance_t const * p_transport_instance =
        p_instance_ctrl->p_wifi_da16xxx_cfg->p_transport_instance;
    at_transport_da16xxx_data_t atcmd;

    /* Get SDK version */
    atcmd.p_at_cmd_string      = (uint8_t *) "AT+SDKVER\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = p_instance_ctrl->cmd_rx_buff;
    atcmd.response_buffer_size = sizeof(p_instance_ctrl->cmd_rx_buff);
    atcmd.timeout_ms           = WIFI_DA16XXX_TIMEOUT_500MS;
    atcmd.p_expect_code        = WIFI_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_socket;
    ret = p_transport_instance->p_api->atCommandSend(p_transport_instance->p_ctrl, &atcmd);

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_INIT_FAILED);

    char * ptr = (char *) p_instance_ctrl->cmd_rx_buff;

    /* Check that version data exists */
    FSP_ERROR_RETURN(0 == strncmp(ptr, "\r\n+SDKVER:", 10), FSP_ERR_INVALID_DATA);

    /* Advance pointer to the version number */
    ptr = ptr + strlen("\r\n+SDKVER:");

    int version[4] = {0};

    /* Extracting major, minor, revision, and engineering numbers from the current version string */
    ptr = strtok(ptr, ".");

    for (int i = 0; i < 3; i++)
    {
        FSP_ERROR_RETURN((ptr != NULL), FSP_ERR_INVALID_DATA);

        version[i] = strtol(ptr, NULL, 10);

        ptr = strtok(NULL, ".");
    }

    /* Extracting major, minor, revision, and engineering numbers from the minimum version string */

    /* Checking if each part of the version string is greater than or equal to the minimum version */
    FSP_ERROR_RETURN(((version[0] > WIFI_DA16XXX_MIN_SDK_VER_MAJOR) ||
                      ((version[0] == WIFI_DA16XXX_MIN_SDK_VER_MAJOR) &&
                       (version[1] > WIFI_DA16XXX_MIN_SDK_VER_MINOR)) ||
                      ((version[0] == WIFI_DA16XXX_MIN_SDK_VER_MAJOR) &&
                       (version[1] == WIFI_DA16XXX_MIN_SDK_VER_MINOR) &&
                       (version[2] > WIFI_DA16XXX_MIN_SDK_VER_REVISION)) ||
                      ((version[0] == WIFI_DA16XXX_MIN_SDK_VER_MAJOR) &&
                       (version[1] == WIFI_DA16XXX_MIN_SDK_VER_MINOR) &&
                       (version[2] == WIFI_DA16XXX_MIN_SDK_VER_REVISION) &&
                       (version[3] >= WIFI_DA16XXX_MIN_SDK_VER_ENGI))),
                     FSP_ERR_INVALID_DATA);

    return ret;
}

#endif

#if (BSP_CFG_RTOS == 2)                /* FreeRTOS */

/*******************************************************************************************************************//**
 *  Handles incoming socket data.
 *
 *  @param[in]  pSocket             Pointer to socket instance structure.
 *  @param[in]  data_byte           Incoming data in byte
 *
 **********************************************************************************************************************/
static bool rm_wifi_da16xxx_handle_incoming_socket_data (da16xxx_socket_t * pSocket, uint8_t data_byte)
{
    wifi_da16xxx_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_da16xxx_instance;
    da16xxx_socket_t             * p_socket        = pSocket;
    BaseType_t xHigherPriorityTaskWoken            = pdFALSE; // Initialized to pdFALSE.
    bool       err = true;
    switch (p_socket->socket_recv_state)
    {
        case WIFI_DA16XXX_RECV_PREFIX:
        {
            if ('+' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_DA16XXX_RECV_CMD;
                rx_data_index               = 0;
            }
            else
            {
                err = false;
            }

            break;
        }

        case WIFI_DA16XXX_RECV_CMD:
        {
            rx_buffer[rx_data_index++] = data_byte;
            rx_data_index              = (rx_data_index) % WIFI_DA16XXX_TEMP_BUFFER_SIZE;

            if (5 == rx_data_index)
            {
                /* Check for incoming data through socket */
                if (0 == strncmp("TRDTC", (char *) rx_buffer, strlen("TRDTC")))
                {
                    p_socket->socket_recv_state = WIFI_DA16XXX_RECV_SUFFIX;
                }
                /* Check for TCP socket disconnect notification */
                else if (0 == strncmp("TRXTC", (char *) rx_buffer, strlen("TRXTC")))
                {
                    p_socket->socket_recv_state = WIFI_DA16XXX_RECV_PREFIX;

                    /* Socket disconnect event received */
                    p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_status =
                        WIFI_DA16XXX_SOCKET_STATUS_CLOSED;
                    p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_read_write_flag = 0;
                }
                else
                {
                    p_socket->socket_recv_state = WIFI_DA16XXX_RECV_PREFIX;
                }
            }

            break;
        }

        case WIFI_DA16XXX_RECV_SUFFIX:
        {
            if (':' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_DA16XXX_RECV_PARAM_CID;
            }

            break;
        }

        case WIFI_DA16XXX_RECV_PARAM_CID:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_DA16XXX_RECV_PARAM_IP;
                rx_data_index               = 0;
            }

            break;
        }

        case WIFI_DA16XXX_RECV_PARAM_IP:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_DA16XXX_RECV_PARAM_PORT;
                rx_data_index               = 0;
            }

            break;
        }

        case WIFI_DA16XXX_RECV_PARAM_PORT:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_DA16XXX_RECV_PARAM_LEN;
                rx_data_index               = 0;
            }

            break;
        }

        case WIFI_DA16XXX_RECV_PARAM_LEN:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_data_len = strtol((char *) rx_buffer, NULL, 10);
                p_socket->socket_recv_state    = WIFI_DA16XXX_RECV_DATA;
                rx_data_index = 0;
            }
            else
            {
                rx_buffer[rx_data_index++] = data_byte;
                rx_data_index              = (rx_data_index) % WIFI_DA16XXX_TEMP_BUFFER_SIZE;
            }

            break;
        }

        case WIFI_DA16XXX_RECV_DATA:
        {
            if (0 < p_socket->socket_recv_data_len--)
            {
                xStreamBufferSendFromISR(p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_byteq_hdl,
                                         &data_byte,
                                         1,
                                         &xHigherPriorityTaskWoken);
            }

            if (0 >= p_socket->socket_recv_data_len)
            {
                p_socket->socket_recv_state = WIFI_DA16XXX_RECV_PREFIX;
            }

            break;
        }
    }

    return err;
}

#endif

/*! \endcond */
