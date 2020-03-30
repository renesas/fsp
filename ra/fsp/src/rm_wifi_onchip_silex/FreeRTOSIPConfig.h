/*
 * FreeRTOS Kernel V10.3.0
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
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 */

/*****************************************************************************
 *
 * See the following URL for configuration information.
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_IP_Configuration.html
 *
 *****************************************************************************/

#ifndef FREERTOS_IP_CONFIG_H
#define FREERTOS_IP_CONFIG_H

/* PLACEHOLDER FOR USE WITH RM_WIFI_ON_SILEX TO SATISFY AWS DEPENDENCIES. */
#define ipconfigEVENT_QUEUE_LENGTH    (ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS + 5)

#define ipconfigNETWORK_MTU           46

#endif                                 /* FREERTOS_IP_CONFIG_H */
