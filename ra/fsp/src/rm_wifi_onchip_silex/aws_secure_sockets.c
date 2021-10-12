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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#if (BSP_CFG_RTOS == 2)
 #include "rm_wifi_onchip_silex.h"

 #include <string.h>
 #include "FreeRTOS.h"
 #include "list.h"
 #include "task.h"
 #include "semphr.h"
 #include "limits.h"

/* Undefine the macro for Keil Compiler to avoid conflict: */
/* __PASTE macro redefinition [-Wmacro-redefinition] */
 #if defined(__ARMCC_VERSION)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wmacro-redefined"
 #endif

 #include "iot_secure_sockets.h"
 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT
  #include "iot_tls.h"
  #include "core_pkcs11.h"
  #include "iot_crypto.h"
 #endif

 #if defined(__ARMCC_VERSION)
  #pragma GCC diagnostic pop
 #endif

/* Internal context structure. */
typedef struct SSOCKETContext
{
    Socket_t   xSocket;
    char     * pcDestination;
    void     * pvTLSContext;
    BaseType_t xRequireTLS;
    BaseType_t xSendFlags;
    BaseType_t xRecvFlags;
    uint32_t   ulSendTimeout;
    uint32_t   ulRecvTimeout;
    char     * pcServerCertificate;
    uint32_t   ulServerCertificateLength;
} SSOCKETContext_t, * SSOCKETContextPtr_t;

static const TickType_t xMaxSemaphoreBlockTime = pdMS_TO_TICKS(60000UL);

/**
 *  Number of secure sockets allocated.
 *
 * Keep a count of the number of open sockets.
 */
static uint32_t g_ssockets_num_allocated = 0;

static SemaphoreHandle_t g_xUcInUse = NULL;

static SSOCKETContext_t  g_socket_instances[WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS];
static StaticSemaphore_t g_socket_mutex;

/* Generate a randomized TCP Initial Sequence Number per RFC. */
uint32_t ulApplicationGetNextSequenceNumber(uint32_t ulSourceAddress,
                                            uint16_t usSourcePort,
                                            uint32_t ulDestinationAddress,
                                            uint16_t usDestinationPort);

/*
 *  Network send callback.
 */
static BaseType_t prvNetworkSend (void * pvContext, const unsigned char * pucData, size_t xDataLength)
{
    int32_t             ret       = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = (SSOCKETContextPtr_t) pvContext; /*lint !e9087 cast used for portability. */

    ret = rm_wifi_onchip_silex_tcp_send(((uint32_t) pxContext->xSocket),
                                        (const uint8_t *) pucData,
                                        (uint32_t) xDataLength,
                                        pxContext->ulSendTimeout);

    return ret;
}

/*
 *  Network receive callback.
 */
static BaseType_t prvNetworkRecv (void * pvContext, unsigned char * pucReceiveBuffer, size_t xReceiveLength)
{
    BaseType_t          receive_byte = 0;
    SSOCKETContextPtr_t pxContext    = (SSOCKETContextPtr_t) pvContext; /*lint !e9087 cast used for portability. */
    uint32_t            socket_num   = ((uint32_t) pxContext->xSocket);

    if (socket_num >= WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS)
    {
        return SOCKETS_SOCKET_ERROR;
    }

    receive_byte = rm_wifi_onchip_silex_tcp_recv(socket_num,
                                                 (uint8_t *) pucReceiveBuffer,
                                                 (uint32_t) xReceiveLength,
                                                 pxContext->ulRecvTimeout);

    return receive_byte;
}

/**
 *  Creates a TCP socket.
 *
 * This call allocates memory and claims a socket resource.
 *
 * @sa SOCKETS_Close()
 *
 * @param[in] lDomain Must be set to SOCKETS_AF_INET. See  SocketDomains.
 * @param[in] lType Set to SOCKETS_SOCK_STREAM to create a TCP socket.
 * No other value is valid.  See  SocketTypes.
 * @param[in] lProtocol Set to SOCKETS_IPPROTO_TCP to create a TCP socket.
 * No other value is valid. See  Protocols.
 *
 * @return
 * * If a socket is created successfully, then the socket handle is
 * returned
 * * SOCKETS_INVALID_SOCKET is returned if an error occurred.
 */
Socket_t SOCKETS_Socket (int32_t lDomain, int32_t lType, int32_t lProtocol)
{
    int32_t             lStatus   = SOCKETS_ERROR_NONE;
    int32_t             ret       = SOCKETS_SOCKET_ERROR;
    uint32_t            socketId  = 0;
    SSOCKETContextPtr_t pxContext = NULL;

    /* Ensure that only supported values are supplied. */
    configASSERT(lDomain == SOCKETS_AF_INET);
    configASSERT(lType == SOCKETS_SOCK_STREAM);
    configASSERT(lProtocol == SOCKETS_IPPROTO_TCP);

    /* Ensure that only supported values are supplied. */
    if ((lDomain != SOCKETS_AF_INET) || (lType != SOCKETS_SOCK_STREAM) || (lProtocol != SOCKETS_IPPROTO_TCP))
    {
        return SOCKETS_INVALID_SOCKET;
    }

    if (xSemaphoreTake(g_xUcInUse, xMaxSemaphoreBlockTime) == pdTRUE)
    {
        rm_wifi_onchip_silex_avail_socket_get(&socketId);

        if ((g_ssockets_num_allocated > WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS) || (socketId == UINT8_MAX))
        {
            lStatus = SOCKETS_SOCKET_ERROR;
        }

        if (SOCKETS_ERROR_NONE == lStatus)
        {
            pxContext = (SSOCKETContextPtr_t) &g_socket_instances[socketId];
        }

        if (SOCKETS_ERROR_NONE == lStatus)
        {
            memset(pxContext, 0, sizeof(SSOCKETContext_t));

            /* Create the wrapped socket. */
            ret = (int32_t) rm_wifi_onchip_silex_socket_create(socketId, 0, 4);
            if (FSP_SUCCESS != ret)
            {
                lStatus = SOCKETS_SOCKET_ERROR;
            }
            else
            {
                pxContext->xSocket       = (void *) (socketId);
                pxContext->ulRecvTimeout = socketsconfigDEFAULT_RECV_TIMEOUT;
                pxContext->ulSendTimeout = socketsconfigDEFAULT_SEND_TIMEOUT;
            }
        }

        if (SOCKETS_ERROR_NONE != lStatus)
        {
            /* Give back the socketInUse mutex. */
            xSemaphoreGive(g_xUcInUse);
            lStatus = (int32_t) SOCKETS_INVALID_SOCKET;
        }
        else
        {
            if (g_ssockets_num_allocated < WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS)
            {
                g_ssockets_num_allocated++;
            }

            /* Give back the socketInUse mutex. */
            xSemaphoreGive(g_xUcInUse);

            return (void *) pxContext;
        }
    }
    else
    {
        lStatus = (int32_t) SOCKETS_INVALID_SOCKET;
    }

    return (void *) lStatus;
}

/**
 *  Connects the socket to the specified IP address and port.
 *
 * The socket must first have been successfully created by a call to SOCKETS_Socket().
 *
 * @param[in] xSocket The handle of the socket to be connected.
 * @param[in] pxAddress A pointer to a SocketsSockaddr_t structure that contains the
 * the address to connect the socket to.
 * @param[in] xAddressLength Should be set to sizeof(  SocketsSockaddr_t ).
 *
 * @return
 * *  SOCKETS_ERROR_NONE if a connection is established.
 * * If an error occured, a negative value is returned.
 */
int32_t SOCKETS_Connect (Socket_t xSocket, SocketsSockaddr_t * pxAddress, Socklen_t xAddressLength)
{
    FSP_PARAMETER_NOT_USED(xAddressLength);

    int32_t             lStatus   = SOCKETS_ERROR_NONE;
    int32_t             ret       = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = (SSOCKETContextPtr_t) xSocket; /*lint !e9087 cast used for portability. */

    if ((pxContext->xSocket != SOCKETS_INVALID_SOCKET) && (pxAddress != NULL))
    {
        ret =
            (int32_t) rm_wifi_onchip_silex_tcp_connect(((uint32_t) pxContext->xSocket),
                                                       SOCKETS_ntohl(pxAddress->ulAddress),
                                                       SOCKETS_ntohs(pxAddress->usPort));

        if (0 != ret)
        {
            lStatus = SOCKETS_SOCKET_ERROR;
        }

        /* Negotiate TLS if requested. */
 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT
        if ((SOCKETS_ERROR_NONE == lStatus) && (pdTRUE == pxContext->xRequireTLS))
        {
            TLSParams_t xTLSParams = {0};
            xTLSParams.ulSize                    = sizeof(xTLSParams);
            xTLSParams.pcDestination             = pxContext->pcDestination;
            xTLSParams.pcServerCertificate       = pxContext->pcServerCertificate;
            xTLSParams.ulServerCertificateLength = pxContext->ulServerCertificateLength;
            xTLSParams.pvCallerContext           = pxContext;
            xTLSParams.pxNetworkRecv             = prvNetworkRecv;
            xTLSParams.pxNetworkSend             = prvNetworkSend;
            lStatus = TLS_Init(&pxContext->pvTLSContext, &xTLSParams);

            if (SOCKETS_ERROR_NONE == lStatus)
            {
                lStatus = TLS_Connect(pxContext->pvTLSContext);
                if (lStatus < 0)
                {
                    lStatus = SOCKETS_TLS_HANDSHAKE_ERROR;
                }
            }
        }
 #endif
    }
    else
    {
        lStatus = SOCKETS_SOCKET_ERROR;
    }

    return lStatus;
}

/**
 *  Receive data from a TCP socket.
 *
 * The socket must have already been created using a call to SOCKETS_Socket()
 * and connected to a remote socket using SOCKETS_Connect().
 *
 * @param[in] xSocket The handle of the socket from which data is being received.
 * @param[out] pvBuffer The buffer into which the received data will be placed.
 * @param[in] xBufferLength The maximum number of bytes which can be received.
 * pvBuffer must be at least xBufferLength bytes long.
 * @param[in] ulFlags Not currently used. Should be set to 0.
 *
 * @return
 * * If the receive was successful then the number of bytes received (placed in the
 *   buffer pointed to by pvBuffer) is returned.
 * * If a timeout occurred before data could be received then 0 is returned (timeout
 *   is set using  SOCKETS_SO_RCVTIMEO).
 * * If an error occured, a negative value is returned.
 */
int32_t SOCKETS_Recv (Socket_t xSocket, void * pvBuffer, size_t xBufferLength, uint32_t ulFlags)
{
    int32_t             lStatus   = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = (SSOCKETContextPtr_t) xSocket; /*lint !e9087 cast used for portability. */

    if ((xSocket != SOCKETS_INVALID_SOCKET) && (pvBuffer != NULL))
    {
        pxContext->xRecvFlags = (BaseType_t) ulFlags;
 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT
        if (pdTRUE == pxContext->xRequireTLS)
        {
            /* Receive through TLS pipe, if negotiated. */
            lStatus = TLS_Recv(pxContext->pvTLSContext, pvBuffer, xBufferLength);
        }
        else
 #endif
        {
            /* Receive unencrypted. */
            lStatus = prvNetworkRecv(pxContext, pvBuffer, xBufferLength);
        }
    }

    return lStatus;
}

/**
 *  Transmit data to the remote socket.
 *
 * The socket must have already been created using a call to SOCKETS_Socket() and
 * connected to a remote socket using SOCKETS_Connect().
 *
 * @param[in] xSocket The handle of the sending socket.
 * @param[in] pvBuffer The buffer containing the data to be sent.
 * @param[in] xDataLength The length of the data to be sent.
 * @param[in] ulFlags Not currently used. Should be set to 0.
 *
 * @return
 * * On success, the number of bytes actually sent is returned.
 * * If an error occured, a negative value is returned.
 */
int32_t SOCKETS_Send (Socket_t xSocket, const void * pvBuffer, size_t xDataLength, uint32_t ulFlags)
{
    int32_t             lStatus   = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = (SSOCKETContextPtr_t) xSocket; /*lint !e9087 cast used for portability. */

    if ((xSocket != SOCKETS_INVALID_SOCKET) && (pvBuffer != NULL))
    {
        pxContext->xSendFlags = (BaseType_t) ulFlags;

 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT
        if (pdTRUE == pxContext->xRequireTLS)
        {
            /* Send through TLS pipe, if negotiated. */
            lStatus = TLS_Send(pxContext->pvTLSContext, pvBuffer, xDataLength);
        }
        else
 #endif
        {
            /* Send unencrypted. */
            lStatus = prvNetworkSend(pxContext, pvBuffer, xDataLength);
        }
    }

    return lStatus;
}

/**
 *  Closes all or part of a full-duplex connection on the socket.
 *
 * @param[in] xSocket The handle of the socket to shutdown.
 * @param[in] ulHow SOCKETS_SHUT_RD, SOCKETS_SHUT_WR or SOCKETS_SHUT_RDWR.
 *  ShutdownFlags
 *
 * @return
 * * If the operation was successful, 0 is returned.
 * * If an error occured, a negative value is returned.
 *
 */
int32_t SOCKETS_Shutdown (Socket_t xSocket, uint32_t ulHow)
{
    int32_t ret = SOCKETS_SOCKET_ERROR;

    SSOCKETContextPtr_t pxContext = (SSOCKETContextPtr_t) xSocket; /*lint !e9087 cast used for portability. */

    if (((int) NULL == (int) pxContext) || ((int) pxContext == (int) SOCKETS_INVALID_SOCKET) ||
        ((int) pxContext->xSocket >= WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS))
    {
        return SOCKETS_EINVAL;
    }

    if ((ulHow != SOCKETS_SHUT_RD) && (ulHow != SOCKETS_SHUT_WR) && (ulHow != SOCKETS_SHUT_RDWR))
    {
        return SOCKETS_EINVAL;
    }

    uint32_t shutdown_value = WIFI_ONCHIP_SILEX_SOCKET_READ | WIFI_ONCHIP_SILEX_SOCKET_WRITE;
    if (SOCKETS_SHUT_RD == ulHow)
    {
        shutdown_value = WIFI_ONCHIP_SILEX_SOCKET_READ;
    }
    else if (SOCKETS_SHUT_WR == ulHow)
    {
        shutdown_value = WIFI_ONCHIP_SILEX_SOCKET_WRITE;
    }
    else
    {
        /* not used */
    }

    ret = rm_wifi_onchip_silex_tcp_shutdown(((uint32_t) pxContext->xSocket), shutdown_value);
    if (0 != ret)
    {
        return SOCKETS_SOCKET_ERROR;
    }

    return SOCKETS_ERROR_NONE;
}

/**
 *  Closes the socket and frees the related resources.
 *
 * @param[in] xSocket The handle of the socket to close.
 *
 * @return
 * * On success, 0 is returned.
 * * If an error occurred, a negative value is returned.
 */
int32_t SOCKETS_Close (Socket_t xSocket)
{
    SSOCKETContextPtr_t pxContext = (SSOCKETContextPtr_t) xSocket; /*lint !e9087 cast used for portability. */
    int32_t             ret       = SOCKETS_SOCKET_ERROR;

    if (((int) NULL != (int) pxContext) && ((int) SOCKETS_INVALID_SOCKET != (int) pxContext) &&
        ((int) pxContext->xSocket < WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS))
    {
 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT
        if (NULL != pxContext->pcDestination)
        {
            vPortFree(pxContext->pcDestination);
        }

        if (NULL != pxContext->pcServerCertificate)
        {
            vPortFree(pxContext->pcServerCertificate);
        }

        if (pdTRUE == pxContext->xRequireTLS)
        {
            TLS_Cleanup(pxContext->pvTLSContext);
        }
 #endif

        ret = (int32_t) rm_wifi_onchip_silex_socket_disconnect(((uint32_t) pxContext->xSocket));
        if (ret != 0)
        {
            return SOCKETS_SOCKET_ERROR;
        }
    }
    else
    {
        return SOCKETS_EINVAL;
    }

    if (g_ssockets_num_allocated > 0)
    {
        g_ssockets_num_allocated--;
    }
    else
    {
        g_ssockets_num_allocated = 0;
    }

    return pdFREERTOS_ERRNO_NONE;
}

/**
 *  Manipulates the options for the socket.
 *
 * @param[in] xSocket The handle of the socket to set the option for.
 * @param[in] lLevel Not currently used. Should be set to 0.
 * @param[in] lOptionName See  SetSockOptOptions.
 * @param[in] pvOptionValue A buffer containing the value of the option to set.
 * @param[in] xOptionLength The length of the buffer pointed to by pvOptionValue.
 *
 * @note Socket option support and possible values vary by port. Please see
 * PORT_SPECIFIC_LINK to check the valid options and limitations of your device.
 *
 *  - Berkeley Socket Options
 *    -  SOCKETS_SO_RCVTIMEO
 *      - Sets the receive timeout
 *      - pvOptionValue (TickType_t) is the number of milliseconds that the
 *      receive function should wait before timing out.
 *      - Setting pvOptionValue = 0 causes receive to wait forever.
 *      - See PORT_SPECIFIC_LINK for device limitations.
 *    -  SOCKETS_SO_SNDTIMEO
 *      - Sets the send timeout
 *      - pvOptionValue (TickType_t) is the number of milliseconds that the
 *      send function should wait before timing out.
 *      - Setting pvOptionValue = 0 causes send to wait forever.
 *      - See PORT_SPECIFIC_LINK for device limitations.
 *  - Non-Standard Options
 *    -  SOCKETS_SO_NONBLOCK
 *      - Makes a socket non-blocking.
 *      - pvOptionValue is ignored for this option.
 *  - Security Sockets Options
 *    -  SOCKETS_SO_REQUIRE_TLS
 *      - Use TLS for all connect, send, and receive on this socket.
 *      - This socket options MUST be set for TLS to be used, even
 *        if other secure socket options are set.
 *      - pvOptionValue is ignored for this option.
 *    -  SOCKETS_SO_TRUSTED_SERVER_CERTIFICATE
 *      - Set the root of trust server certificiate for the socket.
 *      - This socket option only takes effect if  SOCKETS_SO_REQUIRE_TLS
 *        is also set.  If  SOCKETS_SO_REQUIRE_TLS is not set,
 *        this option will be ignored.
 *      - pvOptionValue is a pointer to the formatted server certificate.
 *        TODO: Link to description of how to format certificates with \n
 *      - xOptionLength (BaseType_t) is the length of the certificate
 *        in bytes.
 *    -  SOCKETS_SO_SERVER_NAME_INDICATION
 *      - Use Server Name Indication (SNI)
 *      - This socket option only takes effect if  SOCKETS_SO_REQUIRE_TLS
 *        is also set.  If  SOCKETS_SO_REQUIRE_TLS is not set,
 *        this option will be ignored.
 *      - pvOptionValue is a pointer to a string containing the hostname
 *      - xOptionLength is the length of the hostname string in bytes.
 *
 * @return
 * * On success, 0 is returned.
 * * If an error occured, a negative value is returned.
 */
int32_t SOCKETS_SetSockOpt (Socket_t     xSocket,
                            int32_t      lLevel,
                            int32_t      lOptionName,
                            const void * pvOptionValue,
                            size_t       xOptionLength)
{
    FSP_PARAMETER_NOT_USED(lLevel);
    FSP_PARAMETER_NOT_USED(xOptionLength);

    int32_t             lStatus = SOCKETS_ERROR_NONE;
    TickType_t          xTimeout;
    uint32_t            status    = 0;
    int32_t             ret       = SOCKETS_SOCKET_ERROR;
    SSOCKETContextPtr_t pxContext = (SSOCKETContextPtr_t) xSocket; /*lint !e9087 cast used for portability. */

    if ((xSocket != SOCKETS_INVALID_SOCKET) && (xSocket != NULL))
    {
        ret = (int32_t) rm_wifi_onchip_silex_socket_status_get(((uint32_t) pxContext->xSocket), &status);
        if (ret)
        {
            return SOCKETS_SOCKET_ERROR;
        }

        switch (lOptionName)
        {
            case SOCKETS_SO_SERVER_NAME_INDICATION:
            {
 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT

                /* Do not set the SNI options if the socket is possibly already connected. */
                if (WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED == status)
                {
                    lStatus = SOCKETS_EISCONN;
                }
                else
                {
                    /* Non-NULL destination string indicates that SNI extension should
                     * be used during TLS negotiation. */
                    pxContext->pcDestination = (char *) pvPortMalloc(1U + xOptionLength);
                    if (NULL == pxContext->pcDestination)
                    {
                        lStatus = SOCKETS_ENOMEM;
                    }
                    else
                    {
                        memcpy(pxContext->pcDestination, pvOptionValue, xOptionLength);
                        pxContext->pcDestination[xOptionLength] = '\0';
                    }
                }

 #else
                lStatus = SOCKETS_EINVAL;
 #endif
                break;
            }

            case SOCKETS_SO_TRUSTED_SERVER_CERTIFICATE:
            {
 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT

                /* Do not set the trusted server certificate if the socket is possibly already connected. */
                if (WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED == status)
                {
                    lStatus = SOCKETS_EISCONN;
                }
                else
                {
                    /* Non-NULL server certificate field indicates that the default trust
                     * list should not be used. */
                    pxContext->pcServerCertificate = (char *) pvPortMalloc(xOptionLength);
                    if (NULL == pxContext->pcServerCertificate)
                    {
                        lStatus = SOCKETS_ENOMEM;
                    }
                    else
                    {
                        memcpy(pxContext->pcServerCertificate, pvOptionValue, xOptionLength);
                        pxContext->ulServerCertificateLength = xOptionLength;
                    }
                }

 #else
                lStatus = SOCKETS_EINVAL;
 #endif
                break;
            }

            case SOCKETS_SO_REQUIRE_TLS:
            {
 #if WIFI_ONCHIP_SILEX_CFG_TLS_SUPPORT

                /* Do not set the TLS option if the socket is possibly already connected. */
                if (WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED == status)
                {
                    lStatus = SOCKETS_EISCONN;
                }
                else
                {
                    pxContext->xRequireTLS = pdTRUE;
                }

 #else
                lStatus = SOCKETS_EINVAL;
 #endif

                break;
            }

            case SOCKETS_SO_NONBLOCK:
            {
                /* Non-blocking connect is not supported.  Socket may be set to nonblocking
                 * only after a connection is made. */

                if (WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED == status)
                {
                    pxContext->ulSendTimeout = 1;
                    pxContext->ulRecvTimeout = 1;
                }
                else
                {
                    lStatus = SOCKETS_EISCONN;
                }

                break;
            }

            case SOCKETS_SO_RCVTIMEO:
            {
                /* Comply with Berkeley standard - a 0 timeout is wait forever. */
                xTimeout = *((const TickType_t *) pvOptionValue); /*lint !e9087 pvOptionValue passed should be of TickType_t */

                if (0U == xTimeout)
                {
                    xTimeout = portMAX_DELAY;
                }

                pxContext->ulRecvTimeout = xTimeout;

                break;
            }

            case SOCKETS_SO_SNDTIMEO:
            {
                /* Comply with Berkeley standard - a 0 timeout is wait forever. */
                xTimeout = *((const TickType_t *) pvOptionValue); /*lint !e9087 pvOptionValue passed should be of TickType_t */

                if (0U == xTimeout)
                {
                    xTimeout = portMAX_DELAY;
                }

                pxContext->ulSendTimeout = xTimeout;
                break;
            }

            default:
            {
                lStatus = SOCKETS_ENOPROTOOPT;
                break;
            }
        }
    }
    else
    {
        lStatus = SOCKETS_EINVAL;
    }

    return lStatus;
}

/**
 *  Resolve a host name using Domain Name Service.
 *
 * @param[in] pcHostName The host name to resolve.
 * @return
 * * The IPv4 address of the specified host.
 * * If an error has occured, 0 is returned.
 */
uint32_t SOCKETS_GetHostByName (const char * pcHostName)
{
    uint32_t ulAddr = 0;

    rm_wifi_onchip_silex_dns_query(pcHostName, (uint8_t *) &ulAddr);

    return ulAddr;
}

/**
 *  Secure Sockets library initialization function.
 *
 * This function does general initialization and setup. It must be called once
 * and only once before calling any other function.
 *
 * @return
 * * pdPASS if everything succeeds
 * * pdFAIL otherwise.
 */
BaseType_t SOCKETS_Init (void)
{
    memset(g_socket_instances, 0, sizeof(SSOCKETContext_t) * WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS);

    g_xUcInUse = xSemaphoreCreateMutexStatic(&g_socket_mutex);
    if (g_xUcInUse == NULL)
    {
        return pdFAIL;
    }

    return pdPASS;
}

#endif
