/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#include "bsp_api.h"

#if (BSP_CFG_RTOS == 2)

/* Standard includes. */
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

/* FreeRTOS includes. */
 #include "FreeRTOS.h"
 #include "event_groups.h"

/* Sockets wrapper includes. */
 #include "sockets_wrapper.h"

/* WiFi includes. */
 #include "rm_wifi_onchip_da16200.h"

/* Configure logs for the functions in this file. */
 #include "logging_levels.h"
 #ifndef LIBRARY_LOG_NAME
  #define LIBRARY_LOG_NAME      "WIFI_SOCKETS"
 #endif
 #ifndef LIBRARY_LOG_LEVEL
  #define LIBRARY_LOG_LEVEL     LOG_INFO
 #endif
 #include "logging_stack.h"

 #define SOCKETS_SOCK_STREAM    (1)

/* Ticks MS conversion macros. */
 #define TICKS_TO_MS(xTicks)    (((xTicks) * 1000U) / ((uint32_t) configTICK_RATE_HZ))
 #define UINT32_MAX_DELAY_MS    (0xFFFFFFFFUL)
 #define UINT32_MAX_MS_TICKS    (UINT32_MAX_DELAY_MS / (TICKS_TO_MS(1U)))

/* Logging macros definition. */
 #define IotLogError(...)       LogError((__VA_ARGS__))
 #define IotLogWarn(...)        LogWarn((__VA_ARGS__))
 #define IotLogInfo(...)        LogInfo((__VA_ARGS__))
 #define IotLogDebug(...)       LogDebug((__VA_ARGS__))

typedef struct xSOCKET
{
    uint32_t   socketId;
    TickType_t receiveTimeout;
    TickType_t sendTimeout;
} wifiSocketWrapper_t;

static uint32_t g_sockets_num_allocated = 0;

/**
 * @brief Setup socket receive timeout.
 *
 * @param[in] pWiFiSocketContext Cellular socket wrapper context for socket operations.
 * @param[out] receiveTimeout Socket receive timeout in TickType_t.
 *
 * @return On success, SOCKETS_ERROR_NONE is returned. If an error occurred, error code defined
 * in sockets_wrapper.h is returned.
 */
static BaseType_t prvSetupSocketRecvTimeout(wifiSocketWrapper_t * pWiFiSocketContext, TickType_t receiveTimeout);

/**
 * @brief Setup socket send timeout.
 *
 * @param[in] pWiFiSocketContext Cellular socket wrapper context for socket operations.
 * @param[out] sendTimeout Socket send timeout in TickType_t.
 *
 * @note Send timeout unit is TickType_t. The underlying cellular API uses miliseconds for timeout.
 * Any send timeout greater than UINT32_MAX_MS_TICKS( UINT32_MAX_DELAY_MS/MS_PER_TICKS ) or
 * portMAX_DELAY is regarded as UINT32_MAX_DELAY_MS for cellular API.
 *
 * @return On success, SOCKETS_ERROR_NONE is returned. If an error occurred, error code defined
 * in sockets_wrapper.h is returned.
 */
static BaseType_t prvSetupSocketSendTimeout(wifiSocketWrapper_t * pWiFiSocketContext, TickType_t sendTimeout);

/*-----------------------------------------------------------*/

static BaseType_t prvSetupSocketRecvTimeout (wifiSocketWrapper_t * pWiFiSocketContext, TickType_t receiveTimeout)
{
    BaseType_t retSetSockOpt = SOCKETS_ERROR_NONE;

    if (pWiFiSocketContext == NULL)
    {
        retSetSockOpt = SOCKETS_EINVAL;
    }
    else
    {
        if (receiveTimeout >= UINT32_MAX_MS_TICKS)
        {
            /* Check if the ticks cause overflow. */
            pWiFiSocketContext->receiveTimeout = UINT32_MAX_DELAY_MS;
        }
        else if (receiveTimeout >= portMAX_DELAY)
        {
            IotLogWarn("Receievetimeout %d longer than portMAX_DELAY, %d ms is used instead",
                       receiveTimeout,
                       UINT32_MAX_DELAY_MS);
            pWiFiSocketContext->receiveTimeout = UINT32_MAX_DELAY_MS;
        }
        else
        {
            pWiFiSocketContext->receiveTimeout = TICKS_TO_MS(receiveTimeout);
        }
    }

    return retSetSockOpt;
}

/*-----------------------------------------------------------*/

static BaseType_t prvSetupSocketSendTimeout (wifiSocketWrapper_t * pWiFiSocketContext, TickType_t sendTimeout)
{
    BaseType_t retSetSockOpt = SOCKETS_ERROR_NONE;

    if (pWiFiSocketContext == NULL)
    {
        retSetSockOpt = SOCKETS_EINVAL;
    }
    else
    {
        if (sendTimeout >= UINT32_MAX_MS_TICKS)
        {
            /* Check if the ticks cause overflow. */
            pWiFiSocketContext->sendTimeout = UINT32_MAX_DELAY_MS;
        }
        else if (sendTimeout >= portMAX_DELAY)
        {
            IotLogWarn("Sendtimeout %d longer than portMAX_DELAY, %d ms is used instead",
                       sendTimeout,
                       UINT32_MAX_DELAY_MS);
            pWiFiSocketContext->sendTimeout = UINT32_MAX_DELAY_MS;
        }
        else
        {
            pWiFiSocketContext->sendTimeout = TICKS_TO_MS(sendTimeout);
        }
    }

    return retSetSockOpt;
}

/*-----------------------------------------------------------*/

BaseType_t Sockets_Connect (Socket_t   * pTcpSocket,
                            const char * pHostName,
                            uint16_t     port,
                            uint32_t     receiveTimeoutMs,
                            uint32_t     sendTimeoutMs)
{
    wifiSocketWrapper_t * pWiFiSocketContext = NULL;
    uint32_t              socketId           = 0;
    fsp_err_t             err;
    uint8_t               ipAddressArray[4]; // NOLINT
    uint32_t              ipAddress;
    BaseType_t            retConnect = SOCKETS_ERROR_NONE;

    /* Allocate socket context. */
    if (retConnect == SOCKETS_ERROR_NONE)
    {
        pWiFiSocketContext = pvPortMalloc(sizeof(wifiSocketWrapper_t));

        if (pWiFiSocketContext == NULL)
        {
            IotLogError("Failed to allocate new socket context.");
            retConnect = SOCKETS_ENOMEM;
        }
        else
        {
            IotLogDebug("Created WIFI Socket %p.", pWiFiSocketContext);
            memset(pWiFiSocketContext, 0, sizeof(wifiSocketWrapper_t));
            pWiFiSocketContext->socketId = UINT32_MAX;
        }
    }

    rm_wifi_onchip_da16200_avail_socket_get(&socketId);

    if ((g_sockets_num_allocated > WIFI_ONCHIP_DA16200_CFG_NUM_CREATEABLE_SOCKETS) || (socketId == UINT8_MAX))
    {
        retConnect = SOCKETS_ENOSOCKETS;
    }

    if (SOCKETS_ERROR_NONE == retConnect)
    {
        /* Create the wrapped socket. */
        err =
            rm_wifi_onchip_da16200_socket_create(socketId, (uint32_t) SOCKETS_SOCK_STREAM, SOCKETS_IPPROTO_V4_DA16200);
        if (FSP_SUCCESS != err)
        {
            IotLogError("Failed to create WiFi sockets. %d", err);
            retConnect = SOCKETS_SOCKET_ERROR;
        }
    }

    if (SOCKETS_ERROR_NONE == retConnect)
    {
        if (g_sockets_num_allocated < WIFI_ONCHIP_DA16200_CFG_NUM_CREATEABLE_SOCKETS)
        {
            g_sockets_num_allocated++;
        }

        pWiFiSocketContext->socketId = socketId;
    }

    /* Setup cellular socket send/recv timeout. */
    if (retConnect == SOCKETS_ERROR_NONE)
    {
        retConnect = prvSetupSocketSendTimeout(pWiFiSocketContext, pdMS_TO_TICKS(sendTimeoutMs));
    }

    if (retConnect == SOCKETS_ERROR_NONE)
    {
        retConnect = prvSetupSocketRecvTimeout(pWiFiSocketContext, pdMS_TO_TICKS(receiveTimeoutMs));
    }

    /* Perform a DNS lookup */
    if (retConnect == SOCKETS_ERROR_NONE)
    {
        err = rm_wifi_onchip_da16200_dns_query(pHostName, ipAddressArray);

        if (FSP_SUCCESS != err)
        {
            retConnect = SOCKETS_EDNS;
        }
    }

    /* Cellular socket connect. */
    if (retConnect == SOCKETS_ERROR_NONE)
    {
        /* Convert IP address to binary representation */
        ipAddress = ((uint32_t) (ipAddressArray[0]) << 24) + ((uint32_t) (ipAddressArray[1]) << 16) +
                    ((uint32_t) (ipAddressArray[2]) << 8) + (uint32_t) (ipAddressArray[3]);

        err = rm_wifi_onchip_da16200_tcp_connect(socketId, ipAddress, port);

        if (FSP_SUCCESS != err)
        {
            IotLogError("Failed to establish new connection. Connect return %d.", err);
            retConnect = SOCKETS_SOCKET_ERROR;
        }
    }

    /* Cleanup the socket if any error. */
    if (retConnect != SOCKETS_ERROR_NONE)
    {
        if (pWiFiSocketContext != NULL)
        {
            vPortFree(pWiFiSocketContext);
            pWiFiSocketContext = NULL;
        }
    }

    *pTcpSocket = pWiFiSocketContext;

    return retConnect;
}

/*-----------------------------------------------------------*/

void Sockets_Disconnect (Socket_t xSocket)
{
    int32_t               retClose           = SOCKETS_ERROR_NONE;
    wifiSocketWrapper_t * pWiFiSocketContext = (wifiSocketWrapper_t *) xSocket;
    int32_t               recvLength         = 0;
    uint8_t               buf[128]           = {0}; // NOLINT

    /* xSocket need to be check against SOCKET_INVALID_SOCKET. */
    /* coverity[misra_c_2012_rule_11_4_violation] */
    if ((pWiFiSocketContext == NULL) || (xSocket == SOCKETS_INVALID_SOCKET))
    {
        IotLogError("Invalid xSocket %p", pWiFiSocketContext);
        retClose = SOCKETS_EINVAL;
    }

    if (retClose == SOCKETS_ERROR_NONE)
    {
        if (UINT32_MAX != pWiFiSocketContext->socketId)
        {
            /* Receive all the data before socket close. */
            do
            {
                recvLength = rm_wifi_onchip_da16200_recv(pWiFiSocketContext->socketId,
                                                         buf,
                                                         128, // NOLINT
                                                         pWiFiSocketContext->receiveTimeout);
                IotLogDebug("%u bytes received in close", recvLength);
            } while (recvLength > 0);

            /* Close sockets. */
            if (FSP_SUCCESS != rm_wifi_onchip_da16200_socket_disconnect(pWiFiSocketContext->socketId))
            {
                IotLogWarn("Failed to destroy connection.");
                retClose = SOCKETS_SOCKET_ERROR;
            }
        }

        vPortFree(pWiFiSocketContext);

        g_sockets_num_allocated--;
    }

    (void) retClose;
    IotLogDebug("Sockets close exit with code %d", retClose);
}

/*-----------------------------------------------------------*/

int32_t Sockets_Recv (Socket_t xSocket, void * pvBuffer, size_t xBufferLength)
{
    wifiSocketWrapper_t * pWiFiSocketContext = (wifiSocketWrapper_t *) xSocket;
    uint8_t             * buf                = (uint8_t *) pvBuffer;
    int32_t               retRecvLength      = 0;

    if ((pWiFiSocketContext == NULL) || (UINT32_MAX == pWiFiSocketContext->socketId))
    {
        IotLogError("prvNetworkRecv Invalid xSocket %p", pWiFiSocketContext);
        retRecvLength = SOCKETS_EINVAL;
    }
    else
    {
        int32_t recvLength = 0;

        recvLength =
            rm_wifi_onchip_da16200_recv(pWiFiSocketContext->socketId,
                                        buf,
                                        xBufferLength,
                                        pWiFiSocketContext->receiveTimeout);

        if (recvLength >= 0)
        {
            retRecvLength = recvLength;
        }
        else
        {
            retRecvLength = SOCKETS_SOCKET_ERROR;
        }

        IotLogDebug("prvNetworkRecv expect %d read %d", xBufferLength, recvLength);
    }

    return retRecvLength;
}

/*-----------------------------------------------------------*/

/* This function sends the data until timeout or data is completely sent to server.
 * Send timeout unit is TickType_t. Any timeout value greater than UINT32_MAX_MS_TICKS
 * or portMAX_DELAY will be regarded as MAX delay. In this case, this function
 * will not return until all bytes of data are sent successfully or until an error occurs. */
int32_t Sockets_Send (Socket_t xSocket, const void * pvBuffer, size_t xDataLength)
{
    uint8_t             * buf                = (uint8_t *) pvBuffer;
    int32_t               sentLength         = 0;
    wifiSocketWrapper_t * pWiFiSocketContext = (wifiSocketWrapper_t *) xSocket;

    if ((pWiFiSocketContext == NULL) || (UINT32_MAX == pWiFiSocketContext->socketId))
    {
        IotLogError("prvNetworkSend Invalid xSocket %p", pWiFiSocketContext);
        sentLength = SOCKETS_EINVAL;
    }
    else
    {
        sentLength =
            rm_wifi_onchip_da16200_send(pWiFiSocketContext->socketId, buf, xDataLength,
                                        pWiFiSocketContext->sendTimeout);

        if (sentLength < 0)
        {
            IotLogError("prvNetworkSend failed %d");
            sentLength = SOCKETS_SOCKET_ERROR;
        }
    }

    return sentLength;
}

/*-----------------------------------------------------------*/

#endif
