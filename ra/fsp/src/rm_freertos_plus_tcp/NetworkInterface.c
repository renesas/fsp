/*
 * FreeRTOS+TCP V2.2.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Copyright (C) 2025 Modified by Renesas Electronics Corporation and/or its affiliates
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

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

#include "NetworkInterface.h"
#include "NetworkBufferManagement.h"

/* Renesas includes. */
#include "r_ether_api.h"

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
static TaskHandle_t xRxHanderTaskHandle        = NULL;
static TaskHandle_t xCheckLinkStatusTaskHandle = NULL;

/* Pointer to the interface object of this NIC */
static NetworkInterface_t * pxFSPInterface = NULL;

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Prototype declaration of global functions
 **********************************************************************************************************************/
void                 vEtherISRCallback(ether_callback_args_t * p_args);
NetworkInterface_t * pxFSP_Eth_FillInterfaceDescriptor(BaseType_t xEMACIndex, NetworkInterface_t * pxInterface);

/***********************************************************************************************************************
 * Prototype declaration of private functions
 **********************************************************************************************************************/
static BaseType_t prvNetworkInterfaceInput(void);
static void       prvRXHandlerTask(void * pvParameters);
static void       prvCheckLinkStatusTask(void * pvParameters);

static BaseType_t xFSP_Eth_NetworkInterfaceInitialise(NetworkInterface_t * pxInterface);
static BaseType_t xFSP_Eth_NetworkInterfaceOutput(NetworkInterface_t              * pxInterface,
                                                  NetworkBufferDescriptor_t * const pxNetworkBuffer,
                                                  BaseType_t                        xReleaseAfterSend);
static BaseType_t xFSP_Eth_GetPhyLinkStatus(struct xNetworkInterface * pxInterface);

/***********************************************************************************************************************
 * Interface functions
 **********************************************************************************************************************/
static BaseType_t xFSP_Eth_NetworkInterfaceInitialise (NetworkInterface_t * pxInterface)
{
    fsp_err_t  err;
    BaseType_t xReturn = pdFAIL;

    configASSERT(NULL != gp_freertos_ether);

    pxFSPInterface = pxInterface;

    if (ETHER_ZEROCOPY_ENABLE == gp_freertos_ether->p_cfg->zerocopy)
    {
        /*NOTE:Currently does not support zero copy mode*/
        while (1)
        {
            ;
        }
    }

    err = gp_freertos_ether->p_api->open(gp_freertos_ether->p_ctrl, gp_freertos_ether->p_cfg);

    if ((FSP_SUCCESS != err) && (FSP_ERR_ALREADY_OPEN != err))
    {
        gp_freertos_ether->p_api->close(gp_freertos_ether->p_ctrl);

        return pdFAIL;
    }

    err = gp_freertos_ether->p_api->linkProcess(gp_freertos_ether->p_ctrl);

    if (NULL == xRxHanderTaskHandle)
    {
        xTaskCreate(prvRXHandlerTask,
                    "RXHandlerTask",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    configMAX_PRIORITIES - 1,
                    &xRxHanderTaskHandle);
    }

    if (NULL == xCheckLinkStatusTaskHandle)
    {
        xTaskCreate(prvCheckLinkStatusTask,
                    "CheckLinkStatusTask",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    configMAX_PRIORITIES - 1,
                    &xCheckLinkStatusTaskHandle);
    }

    if ((FSP_SUCCESS == err) && (NULL != xRxHanderTaskHandle) && (NULL != xCheckLinkStatusTaskHandle))
    {
        xReturn = pdPASS;
    }
    else
    {
        xReturn = pdFAIL;
    }

    return xReturn;
}

static BaseType_t xFSP_Eth_NetworkInterfaceOutput (NetworkInterface_t              * pxInterface,
                                                   NetworkBufferDescriptor_t * const pxNetworkBuffer,
                                                   BaseType_t                        xReleaseAfterSend)
{
    fsp_err_t  err;
    BaseType_t xReturn = pdPASS;

    FSP_PARAMETER_NOT_USED(pxInterface);

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

static BaseType_t xFSP_Eth_GetPhyLinkStatus (struct xNetworkInterface * pxInterface)
{
    BaseType_t xReturn = pdPASS;

    FSP_PARAMETER_NOT_USED(pxInterface);

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
    if ((p_args->event == ETHER_EVENT_RX_COMPLETE) || (p_args->event == ETHER_EVENT_RX_MESSAGE_LOST))
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
    else if (p_args->event == ETHER_EVENT_GET_NIC_INFO)
    {
#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 1) && (ipconfigUSE_IPv4 != 0)
        FreeRTOS_UpdateMACAddress(p_args->p_nic_info->p_mac_address);
#endif
    }
    else
    {
        /* Do nothing. */
    }
}

void vNetworkInterfaceAllocateRAMToBuffers (
    NetworkBufferDescriptor_t pxNetworkBuffers[ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS])
{
    /* Remove compiler warning about unused parameter. */
    (void) pxNetworkBuffers;
}

NetworkInterface_t * pxFSP_Eth_FillInterfaceDescriptor (BaseType_t xEMACIndex, NetworkInterface_t * pxInterface)
{
    static char pcName[17];

    /* This function pxFSP_Eth_FillInterfaceDescriptor() adds a network-interface. */

    snprintf(pcName, sizeof(pcName), "eth%u", (unsigned) xEMACIndex);

    memset(pxInterface, '\0', sizeof(*pxInterface));
    pxInterface->pcName             = pcName;              /* Just for logging, debugging. */
    pxInterface->pvArgument         = (void *) xEMACIndex; /* Has only meaning for the driver functions. */
    pxInterface->pfInitialise       = xFSP_Eth_NetworkInterfaceInitialise;
    pxInterface->pfOutput           = xFSP_Eth_NetworkInterfaceOutput;
    pxInterface->pfGetPhyLinkStatus = xFSP_Eth_GetPhyLinkStatus;

    FreeRTOS_AddNetworkInterface(pxInterface);

    return pxInterface;
}

/*-----------------------------------------------------------*/

#if defined(ipconfigIPv4_BACKWARD_COMPATIBLE) && (ipconfigIPv4_BACKWARD_COMPATIBLE == 1)

/* Do not call the following function directly. It is there for downward compatibility.
 * The function FreeRTOS_IPInit() will call it to initialice the interface and end-point
 * objects.  See the description in FreeRTOS_Routing.h. */
NetworkInterface_t * pxFillInterfaceDescriptor (BaseType_t xEMACIndex, NetworkInterface_t * pxInterface)
{
    return pxFSP_Eth_FillInterfaceDescriptor(xEMACIndex, pxInterface);
}

#endif

/*-----------------------------------------------------------*/

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
        pxBufferDescriptor->pxInterface = pxFSPInterface;
        pxBufferDescriptor->pxEndPoint  =
            FreeRTOS_MatchingEndpoint(pxFSPInterface, pxBufferDescriptor->pucEthernetBuffer);

        /* When driver received any data. */
        if ((FSP_SUCCESS == err) || (FSP_ERR_ETHER_ERROR_NO_DATA == err))
        {
            if ((pxBufferDescriptor->pxEndPoint != NULL) &&
                (eConsiderFrameForProcessing(pxBufferDescriptor->pucEthernetBuffer) == eProcessBuffer))
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

    fsp_err_t            current_link_status  = FSP_ERR_ETHER_ERROR_LINK;
    fsp_err_t            previous_link_status = FSP_ERR_ETHER_ERROR_LINK;
    const IPStackEvent_t xNetworkDownEvent    = {eNetworkDownEvent, pxFSPInterface};

    for ( ; ; )
    {
        vTaskDelay(ETHER_LINK_STATUS_CHECK_INTERVAL);
        current_link_status = gp_freertos_ether->p_api->linkProcess(gp_freertos_ether->p_ctrl);

        /* Link status is changed. */
        if (previous_link_status != current_link_status)
        {
            if (FSP_SUCCESS == current_link_status)
            {
                /* Link status changed to up. */
                previous_link_status = current_link_status;

                vIPNetworkUpCalls(pxFSPInterface->pxEndPoint);
            }
            else if ((FSP_ERR_ETHER_ERROR_LINK == current_link_status) ||
                     (FSP_ERR_ETHER_PHY_ERROR_LINK == current_link_status))
            {
                /* Link status changed to down. Send the data to the TCP/IP stack. */
                if (pdPASS == xSendEventStructToIPTask(&xNetworkDownEvent, 0))
                {
                    previous_link_status = current_link_status;
                }
            }
            else
            {
                /* Correct Link status could not be retrieved. */
                ;
            }
        }
    }
}

__attribute__((weak)) BaseType_t xApplicationGetRandomNumber (uint32_t * pulNumber)
{
    /* example of a 32-bit random number generator.
     * rand() in returns a 16-bit number. so create 32 bit Random number using 16 bit rand().
     * In this case just a pseudo random number is used so THIS IS NOT RECOMMENDED FOR PRODUCTION SYSTEMS.
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
     * Initial Sequence Number per RFC 6528.  In this case just a pseudo random
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
