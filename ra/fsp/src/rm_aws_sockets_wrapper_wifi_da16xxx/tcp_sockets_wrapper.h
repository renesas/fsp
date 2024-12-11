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

#ifndef TCP_SOCKETS_WRAPPER_H
#define TCP_SOCKETS_WRAPPER_H

/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

/* Logging related header files are required to be included in the following order:
 * 1. Include the header file "logging_levels.h".
 * 2. Define LIBRARY_LOG_NAME and  LIBRARY_LOG_LEVEL.
 * 3. Include the header file "logging_stack.h".
 */

/* Include header that defines log levels. */
#include "logging_levels.h"

/* Logging configuration for the Sockets. */
#ifndef LIBRARY_LOG_NAME
 #define LIBRARY_LOG_NAME     "Sockets"
#endif
#ifndef LIBRARY_LOG_LEVEL
 #define LIBRARY_LOG_LEVEL    LOG_INFO
#endif

extern void vLoggingPrintf(const char * pcFormatString, ...);

#include "logging_stack.h"

/************ End of logging configuration ****************/

/* Error codes. */
#define TCP_SOCKETS_ERRNO_NONE                (0)    /*!< No error. */
#define TCP_SOCKETS_ERRNO_ERROR               (-1)   /*!< Catch-all sockets error code. */
#define TCP_SOCKETS_ERRNO_EWOULDBLOCK         (-2)   /*!< A resource is temporarily unavailable. */
#define TCP_SOCKETS_ERRNO_ENOMEM              (-3)   /*!< Memory allocation failed. */
#define TCP_SOCKETS_ERRNO_EINVAL              (-4)   /*!< Invalid argument. */
#define TCP_SOCKETS_ERRNO_ENOPROTOOPT         (-5)   /*!< A bad option was specified . */
#define TCP_SOCKETS_ERRNO_ENOTCONN            (-6)   /*!< The supplied socket is not connected. */
#define TCP_SOCKETS_ERRNO_EISCONN             (-7)   /*!< The supplied socket is already connected. */
#define TCP_SOCKETS_ERRNO_ECLOSED             (-8)   /*!< The supplied socket has already been closed. */
#define TCP_SOCKETS_ERRNO_PERIPHERAL_RESET    (-9)   /*!< Communications peripheral has been reset. */
#define TCP_SOCKETS_ERRNO_ENOSPC              (-10)  /*!< No space left on device */
#define TCP_SOCKETS_ERRNO_EINTR               (-11)  /*!< Interrupted system call */
#define TCP_SOCKETS_ENRNO_SOCKETS             (-13)  /*!< Max number of sockets has been used. */
#define TCP_SOCKETS_ENRNO_DNS                 (-200) /*!< DNS lookup failed. */

#define SOCKETS_INVALID_SOCKET                ((Socket_t) ~0U)

#ifndef SOCKET_T_TYPEDEFED
struct xSOCKET;
typedef struct xSOCKET * Socket_t;     /**< @brief Socket handle data type. */
#endif

/**
 * @brief Establish a connection to server.
 *
 * @param[out] pTcpSocket The output parameter to return the created socket descriptor.
 * @param[in] pHostName Server hostname to connect to.
 * @param[in] port Server port to connect to.
 * @param[in] receiveTimeoutMs Timeout (in milliseconds) for transport receive.
 * @param[in] sendTimeoutMs Timeout (in milliseconds) for transport send.
 *
 * @note A timeout of 0 means infinite timeout.
 *
 * @return Non-zero value on error, 0 on success.
 */
BaseType_t TCP_Sockets_Connect(Socket_t   * pTcpSocket,
                               const char * pHostName,
                               uint16_t     port,
                               uint32_t     receiveTimeoutMs,
                               uint32_t     sendTimeoutMs);

/**
 * @brief End connection to server.
 *
 * @param[in] xSocket The socket descriptor.
 */
void TCP_Sockets_Disconnect(Socket_t xSocket);

/**
 * @brief Transmit data to the remote socket.
 *
 * The socket must have already been created using a call to Sockets_Connect().
 *
 * @param[in] xSocket The handle of the sending socket.
 * @param[in] pvBuffer The buffer containing the data to be sent.
 * @param[in] xDataLength The length of the data to be sent.
 *
 * @return
 * * On success, the number of bytes actually sent is returned.
 * * If an error occurred, a negative value is returned.
 */
int32_t TCP_Sockets_Send(Socket_t xSocket, const void * pvBuffer, size_t xDataLength);

/**
 * @brief Receive data from a TCP socket.
 *
 * The socket must have already been created using a call to Sockets_Connect().
 *
 * @param[in] xSocket The handle of the socket from which data is being received.
 * @param[out] pvBuffer The buffer into which the received data will be placed.
 * @param[in] xBufferLength The maximum number of bytes which can be received.
 * pvBuffer must be at least xBufferLength bytes long.
 *
 * @return
 * * If the receive was successful then the number of bytes received (placed in the
 *   buffer pointed to by pvBuffer) is returned.
 * * If a timeout occurred before data could be received then 0 is returned.
 * * If an error occurred, a negative value is returned.
 */
int32_t TCP_Sockets_Recv(Socket_t xSocket, void * pvBuffer, size_t xBufferLength);

#endif                                 /* ifndef TCP_SOCKETS_WRAPPER_H */
