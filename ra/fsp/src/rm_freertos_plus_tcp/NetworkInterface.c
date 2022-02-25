/*
 * FreeRTOS+TCP V2.2.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Standard libraries includes. */
#include <stdlib.h>

#if defined(__IAR_SYSTEMS_ICC__)
 #pragma diag_suppress=Pe1644
#endif

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

#if defined(__IAR_SYSTEMS_ICC__)
 #pragma diag_default=Pe1644
#endif
#include "NetworkInterface.h"
#include "NetworkBufferManagement.h"

/* Renesas includes. */
#include "r_ether.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
 * driver will filter incoming packets and only pass the stack those packets it
 * considers need processing. */
#if (ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0)
 #define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer)    eProcessBuffer
#else
 #define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer)    eConsiderFrameForProcessing((pucEthernetBuffer))
#endif

/* Minimum Ethernet frame size (without CRC). */
#define MINIMUM_ETHERNET_FRAME_SIZE               (60U)
#define MAXIMUM_ETHERNET_FRAME_SIZE               (1514U)

#define ETHER_EDMAC_INTERRUPT_FACTOR_RECEPTION    (0x01070000)
#define ETHER_LINK_STATUS_CHECK_INTERVAL          (1000)

#define UNSIGNED_SHORT_RANDOM_NUMBER_MASK         (0xFFFFUL)

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
extern ether_instance_t * gp_freertos_ether;

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static TaskHandle_t xRxHanderTaskHandle = NULL;

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Prototype declaration of global functions
 **********************************************************************************************************************/
void vEtherISRCallback(ether_callback_args_t * p_args);

/***********************************************************************************************************************
 * Prototype declaration of private functions
 **********************************************************************************************************************/
static BaseType_t prvNetworkInterfaceInput(void);
static void       prvRXHandlerTask(void * pvParameters);
static void       prvCheckLinkStatusTask(void * pvParameters);

/***********************************************************************************************************************
 * Interface functions
 **********************************************************************************************************************/
BaseType_t xNetworkInterfaceInitialise (void)
{
    fsp_err_t  err;
    BaseType_t xReturn = pdFAIL;

    if (ETHER_ZEROCOPY_ENABLE == gp_freertos_ether->p_cfg->zerocopy)
    {
        /*NOTE:Currently does not support zero copy mode*/
        while (1)
        {
            ;
        }
    }

    err = gp_freertos_ether->p_api->open(gp_freertos_ether->p_ctrl, gp_freertos_ether->p_cfg);

    if (FSP_SUCCESS != err)
    {
        return pdFAIL;
    }

    do
    {
        err = gp_freertos_ether->p_api->linkProcess(gp_freertos_ether->p_ctrl);
    } while (FSP_SUCCESS != err);

    xReturn = xTaskCreate(prvRXHandlerTask,
                          "RXHandlerTask",
                          configMINIMAL_STACK_SIZE,
                          NULL,
                          configMAX_PRIORITIES - 1,
                          &xRxHanderTaskHandle);

    if (pdFALSE != xReturn)
    {
        xReturn = xTaskCreate(prvCheckLinkStatusTask,
                              "CheckLinkStatusTask",
                              configMINIMAL_STACK_SIZE,
                              NULL,
                              configMAX_PRIORITIES,
                              NULL);
    }

    return xReturn;
}

BaseType_t xNetworkInterfaceOutput (NetworkBufferDescriptor_t * const pxNetworkBuffer, BaseType_t xReleaseAfterSend)
{
    fsp_err_t  err;
    BaseType_t xReturn = pdPASS;

    /* Simple network interfaces (as opposed to more efficient zero copy network
     * interfaces) just use Ethernet peripheral driver library functions to copy
     * data from the FreeRTOS+TCP buffer into the peripheral driver's own buffer.*/

    if (MINIMUM_ETHERNET_FRAME_SIZE > pxNetworkBuffer->xDataLength)
    {
        pxNetworkBuffer->xDataLength = MINIMUM_ETHERNET_FRAME_SIZE;
    }

    err = gp_freertos_ether->p_api->write(gp_freertos_ether->p_ctrl,
                                          pxNetworkBuffer->pucEthernetBuffer,
                                          pxNetworkBuffer->xDataLength);

    if (FSP_SUCCESS == err)
    {
        xReturn = pdPASS;
    }
    else
    {
        xReturn = pdFAIL;
    }

    if (pdFAIL != xReturn)
    {
        /* Call the standard trace macro to log the send event. */
        iptraceNETWORK_INTERFACE_TRANSMIT();
    }

    /* The Ethernet buffer is therefore no longer needed, and must be freed for re-use. */
    if (xReleaseAfterSend == pdTRUE)
    {
        vReleaseNetworkBufferAndDescriptor(pxNetworkBuffer);
    }

    return xReturn;
}

void vNetworkInterfaceAllocateRAMToBuffers (
    NetworkBufferDescriptor_t pxNetworkBuffers[ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS])
{
    /* Remove compiler warning about unused parameter. */
    (void) pxNetworkBuffers;
}

BaseType_t xGetPhyLinkStatus (void)
{
    BaseType_t xReturn = pdPASS;

    if (FSP_SUCCESS == gp_freertos_ether->p_api->linkProcess(gp_freertos_ether->p_ctrl))
    {
        xReturn = pdPASS;
    }
    else
    {
        xReturn = pdFAIL;
    }

    return xReturn;
}

/***********************************************************************************************************************
 * global functions
 **********************************************************************************************************************/
void vEtherISRCallback (ether_callback_args_t * p_args) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* If EDMAC FR (Frame Receive Event) or FDE (Receive Descriptor Empty Event)
     * interrupt occurs, wake up xRxHanderTask. */
    if (p_args->status_eesr & ETHER_EDMAC_INTERRUPT_FACTOR_RECEPTION)
    {
        if (xRxHanderTaskHandle != NULL)
        {
            vTaskNotifyGiveFromISR(xRxHanderTaskHandle, &xHigherPriorityTaskWoken);
        }

        /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context switch
         * should be performed to ensure the interrupt returns directly to the highest
         * priority task.  The macro used for this purpose is dependent on the port in
         * use and may be called portEND_SWITCHING_ISR(). */
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/***********************************************************************************************************************
 * private functions
 **********************************************************************************************************************/

static BaseType_t prvNetworkInterfaceInput (void) {
    BaseType_t xResult = pdFAIL;
    fsp_err_t  err;

    /* Used to indicate that xSendEventStructToIPTask() is being called because
     * of an Ethernet receive event. */
    IPStackEvent_t              xRxEvent;
    NetworkBufferDescriptor_t * pxBufferDescriptor;
    uint32_t xBytesReceived = 0;

    pxBufferDescriptor = pxGetNetworkBufferWithDescriptor((size_t) MAXIMUM_ETHERNET_FRAME_SIZE, 0);

    if (NULL != pxBufferDescriptor)
    {
        err = gp_freertos_ether->p_api->read(gp_freertos_ether->p_ctrl,
                                             (void *) pxBufferDescriptor->pucEthernetBuffer,
                                             &xBytesReceived);
        pxBufferDescriptor->xDataLength = (size_t) xBytesReceived;

        /* When driver received any data. */
        if ((FSP_SUCCESS == err) || (FSP_ERR_ETHER_ERROR_NO_DATA == err))
        {
            if (eConsiderFrameForProcessing(pxBufferDescriptor->pucEthernetBuffer) == eProcessBuffer)
            {
                /* The event about to be sent to the TCP/IP is an Rx event. */
                xRxEvent.eEventType = eNetworkRxEvent;

                /* pvData is used to point to the network buffer descriptor that
                 * now references the received data. */
                xRxEvent.pvData = (void *) pxBufferDescriptor;

                /* Send the data to the TCP/IP stack. */
                if (pdPASS == xSendEventStructToIPTask(&xRxEvent, 0))
                {
                    /* The message was successfully sent to the TCP/IP stack.
                     * Call the standard trace macro to log the occurrence. */
                    iptraceNETWORK_INTERFACE_RECEIVE();
                    xResult = pdPASS;
                }
            }
        }

        if (pdPASS != xResult)
        {
            /* The buffer could not be sent to the IP task so the buffer must be released. */
            vReleaseNetworkBufferAndDescriptor(pxBufferDescriptor);
            iptraceETHERNET_RX_EVENT_LOST();
        }
    }

    return xResult;
}

static void prvRXHandlerTask (void * pvParameters) {
    BaseType_t xResult = pdFALSE;

    /* Avoid compiler warning about unreferenced parameter. */
    (void) pvParameters;

    for ( ; ; )
    {
        /* Wait for the Ethernet MAC interrupt to indicate that another packet
         * has been received.  */
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);

        do
        {
            xResult = prvNetworkInterfaceInput();
        } while (pdFAIL != xResult);
    }
}

static void prvCheckLinkStatusTask (void * pvParameters) {
    /* Remove compiler warning about unused parameter. */
    (void) pvParameters;

    for ( ; ; )
    {
        vTaskDelay(ETHER_LINK_STATUS_CHECK_INTERVAL);
        gp_freertos_ether->p_api->linkProcess(gp_freertos_ether->p_ctrl);
    }
}

__attribute__((weak)) BaseType_t xApplicationGetRandomNumber (uint32_t * pulNumber)
{
    /* example of a 32-bit random number generator.
     * rand() in returns a 16-bit number. so create 32 bit Random number using 16 bit rand().
     * In this case just a psuedo random number is used so THIS IS NOT RECOMMENDED FOR PRODUCTION SYSTEMS.
     */
    uint32_t ulRandomValue = 0;

    ulRandomValue = ((((uint32_t) rand()) & UNSIGNED_SHORT_RANDOM_NUMBER_MASK)) |      // NOLINT (rand() has limited randomness. But c99 does not support random)
                    ((((uint32_t) rand()) & UNSIGNED_SHORT_RANDOM_NUMBER_MASK) << 16); // NOLINT (rand() has limited randomness. But c99 does not support random)

    *(pulNumber) = ulRandomValue;

    return pdTRUE;
}

BSP_WEAK_REFERENCE uint32_t ulApplicationGetNextSequenceNumber (uint32_t ulSourceAddress,
                                                                uint16_t usSourcePort,
                                                                uint32_t ulDestinationAddress,
                                                                uint16_t usDestinationPort)
{
    /*
     * Callback that provides the inputs necessary to generate a randomized TCP
     * Initial Sequence Number per RFC 6528.  In this case just a psuedo random
     * number is used so THIS IS NOT RECOMMENDED FOR PRODUCTION SYSTEMS.
     */
    FSP_PARAMETER_NOT_USED(ulSourceAddress);
    FSP_PARAMETER_NOT_USED(ulDestinationAddress);
    FSP_PARAMETER_NOT_USED(usSourcePort);
    FSP_PARAMETER_NOT_USED(usDestinationPort);

    uint32_t ulResult = 0;
    while (0 == ulResult)
    {
        xApplicationGetRandomNumber(&ulResult);
    }

    return ulResult;
}

#if defined(__ARMCC_VERSION)

/*******************************************************************************************************************//**
 * Default implementation of IotClock_GetTimestring for AC6.
 **********************************************************************************************************************/
__attribute__((weak))
bool IotClock_GetTimestring (char * pBuffer, size_t bufferSize, size_t * pTimestringLength)
{
    FSP_PARAMETER_NOT_USED(pBuffer);
    FSP_PARAMETER_NOT_USED(bufferSize);
    FSP_PARAMETER_NOT_USED(pTimestringLength);

    return true;
}

#endif
