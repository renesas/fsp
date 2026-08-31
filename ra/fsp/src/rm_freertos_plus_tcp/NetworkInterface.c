/*
 * FreeRTOS+TCP V2.2.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Copyright (C) 2026 Modified by Renesas Electronics Corporation and/or its affiliates
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

/* Standard libraries includes. */
#include <stdlib.h>

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

#include "NetworkBufferManagement.h"
#include "NetworkInterface.h"

/* Renesas includes. */
#include "r_ether_api.h"
#include "rm_freertos_plus_tcp.h"
#include "rm_freertos_plus_tcp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/* "TCP" in ASCII, used to determine if middleware instance is opened. */
#define TCP_OPEN    (0x00544350ULL)

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
 * driver will filter incoming packets and only pass the stack those packets it
 * considers need processing. */
#if (ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0)
 #define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer)    eProcessBuffer
#else
 #define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer)    eConsiderFrameForProcessing((pucEthernetBuffer))
#endif

/* Minimum Ethernet frame size (without CRC). */
#define MINIMUM_ETHERNET_FRAME_SIZE                    (60U)
#define MAXIMUM_ETHERNET_FRAME_SIZE                    (1514U)

#define ETHER_EDMAC_INTERRUPT_FACTOR_RECEPTION         (0x01070000)

#define UNSIGNED_SHORT_RANDOM_NUMBER_MASK              (0xFFFFUL)

#define FREERTOS_PLUS_TCP_GET_DESCRIPTOR_BLOCK_TIME    (1000)

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)

 #if BSP_PERIPHERAL_ESWM_PRESENT
  #define FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_SIZE       (4)
  #define FREERTOS_PLUS_TCP_ETHER_PADDING_SIZE         (0)
 #else
  #define FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_SIZE       (32)
  #define FREERTOS_PLUS_TCP_ETHER_PADDING_SIZE         (2)
 #endif

 #define FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_MASK        (FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_SIZE - 1UL)

 #if BSP_PERIPHERAL_ESWM_PRESENT
  #define FREERTOS_PLUS_TCP_IP_PADDING_SIZE            (ipBUFFER_PADDING)
 #else
  #define FREERTOS_PLUS_TCP_IP_PADDING_SIZE            ((ipBUFFER_PADDING + FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_MASK) & \
                                                        ~FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_MASK)
 #endif

 #define FREERTOS_PLUS_TCP_ETHER_BUFFER_SIZE           ((FREERTOS_PLUS_TCP_IP_PADDING_SIZE +       \
                                                         ipTOTAL_ETHERNET_FRAME_SIZE +             \
                                                         FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_MASK) & \
                                                        ~FREERTOS_PLUS_TCP_ETHER_ALIGNMENT_MASK)
#endif

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 1)
extern rm_freertos_plus_tcp_instance_t * gp_freertos_plus_tcp_instance;
#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Event flags are set vEtherISRCallback and handled inside prvEthernetDeferredInterruptHandlerTask(). */
typedef enum e_rm_freertos_plus_tcp_notify_event
{
    FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_ON  = (1UL << 0), // Link up event.
    FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_OFF = (1UL << 1), // Link down event.
    FREERTOS_PLUS_TCP_NOTIFY_EVENT_RX       = (1UL << 2), // Receive event.
    FREERTOS_PLUS_TCP_NOTIFY_EVENT_TX       = (1UL << 3), // Transmit complete event.
} rm_freertos_plus_tcp_notify_event_t;

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)
extern uint8_t ** ppucFSP_Eth_GetEthernetBufferAddress(void);

#endif

/***********************************************************************************************************************
 * Prototype declaration of global functions
 **********************************************************************************************************************/
void                 vEtherISRCallback(ether_callback_args_t * p_args);
NetworkInterface_t * pxFSP_Eth_FillInterfaceDescriptor(BaseType_t xEMACIndex, NetworkInterface_t * pxInterface);

/***********************************************************************************************************************
 * Prototype declaration of private functions
 **********************************************************************************************************************/

static BaseType_t prvNetworkInterfaceInput(NetworkInterface_t * pxInterface);
static void       prvEthernetDeferredInterruptHandlerTask(void * pvParameters);
static void       prvCheckLinkStatusTask(void * pvParameters);

static BaseType_t xFSP_Eth_NetworkInterfaceInitialise(NetworkInterface_t * pxInterface);
static BaseType_t xFSP_Eth_NetworkInterfaceOutput(NetworkInterface_t              * pxInterface,
                                                  NetworkBufferDescriptor_t * const pxNetworkBuffer,
                                                  BaseType_t                        xReleaseAfterSend);
static BaseType_t xFSP_Eth_GetPhyLinkStatus(struct xNetworkInterface * pxInterface);

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)
static void prvFSP_Eth_AddNetworkBufferDescriptorToList(
    NetworkBufferDescriptor_t ** ppxHeadBufferDescriptor,
    NetworkBufferDescriptor_t  * pxNewBufferDescriptor);
static void prvFSP_Eth_RemoveNetworkBufferDescriptorFromList(
    NetworkBufferDescriptor_t ** ppxHeadBufferDescriptor,
    NetworkBufferDescriptor_t  * pxRemoveBufferDescriptor);
static NetworkBufferDescriptor_t * pxFSP_Eth_PopNetworkBufferDescriptorFromList(
    NetworkBufferDescriptor_t ** ppxHeadBufferDescriptor);

#endif

/***********************************************************************************************************************
 * Interface functions
 **********************************************************************************************************************/
static BaseType_t xFSP_Eth_NetworkInterfaceInitialise (NetworkInterface_t * pxInterface)
{
    fsp_err_t  err;
    BaseType_t xReturn = pdFAIL;

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = pxInterface->pvArgument;
#else
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = gp_freertos_plus_tcp_instance;
#endif
    configASSERT(NULL != p_freertos_plus_tcp_instance);

    p_freertos_plus_tcp_instance->p_ctrl->p_cfg = p_freertos_plus_tcp_instance->p_cfg;

    ether_instance_t * p_ether_instance = p_freertos_plus_tcp_instance->p_cfg->p_ether_instance;
    configASSERT(NULL != p_ether_instance);

    err = p_ether_instance->p_api->open(p_ether_instance->p_ctrl, p_ether_instance->p_cfg);

    if ((FSP_SUCCESS != err) && (FSP_ERR_ALREADY_OPEN != err))
    {
        p_ether_instance->p_api->close(p_ether_instance->p_ctrl);

        return pdFAIL;
    }

    err = p_ether_instance->p_api->linkProcess(p_ether_instance->p_ctrl);

    if (NULL == (p_freertos_plus_tcp_instance->p_ctrl->xEthernetDeferredInterruptHanderTaskHandle))
    {
        xTaskCreate(prvEthernetDeferredInterruptHandlerTask,
                    "EthernetDeferredInterruptHandlerTask",
                    p_freertos_plus_tcp_instance->p_cfg->ether_deferred_interrupt_handler_task_stacksize,
                    pxInterface,
                    p_freertos_plus_tcp_instance->p_cfg->ether_deferred_interrupt_handler_task_priority,
                    &(p_freertos_plus_tcp_instance->p_ctrl->xEthernetDeferredInterruptHanderTaskHandle));
    }

    if (NULL == (p_freertos_plus_tcp_instance->p_ctrl->xCheckLinkStatusTaskHandle))
    {
        xTaskCreate(prvCheckLinkStatusTask,
                    "CheckLinkStatusTask",
                    p_freertos_plus_tcp_instance->p_cfg->check_link_status_task_stacksize,
                    pxInterface,
                    p_freertos_plus_tcp_instance->p_cfg->check_link_status_task_priority,
                    &(p_freertos_plus_tcp_instance->p_ctrl->xCheckLinkStatusTaskHandle));
    }

    if ((FSP_SUCCESS == err) &&
        (NULL != (p_freertos_plus_tcp_instance->p_ctrl->xEthernetDeferredInterruptHanderTaskHandle)) &&
        (NULL != (p_freertos_plus_tcp_instance->p_ctrl->xCheckLinkStatusTaskHandle)))
    {
        xReturn = pdPASS;

        p_freertos_plus_tcp_instance->p_ctrl->open = TCP_OPEN;
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

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = pxInterface->pvArgument;
#else
    (void) pxInterface;
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = gp_freertos_plus_tcp_instance;
#endif

    ether_instance_t * p_ether_instance = p_freertos_plus_tcp_instance->p_cfg->p_ether_instance;

    /* Simple network interfaces (as opposed to more efficient zero copy network
     * interfaces) just use Ethernet peripheral driver library functions to copy
     * data from the FreeRTOS+TCP buffer into the peripheral driver's own buffer.*/

    if (MINIMUM_ETHERNET_FRAME_SIZE > pxNetworkBuffer->xDataLength)
    {
        pxNetworkBuffer->xDataLength = MINIMUM_ETHERNET_FRAME_SIZE;
    }

    err = p_ether_instance->p_api->write(p_ether_instance->p_ctrl,
                                         pxNetworkBuffer->pucEthernetBuffer,
                                         pxNetworkBuffer->xDataLength);
    if (FSP_SUCCESS == err)
    {
#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)

        /* If zero copy mode is enable, add tx descriptor to list. */
        prvFSP_Eth_AddNetworkBufferDescriptorToList(&p_freertos_plus_tcp_instance->p_ctrl->p_tx_pending_descriptor_list,
                                                    pxNetworkBuffer);
#endif

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
    else
    {
        vReleaseNetworkBufferAndDescriptor(pxNetworkBuffer);
    }

    /* The Ethernet buffer is therefore no longer needed, and must be freed for re-use. */
    if ((xReleaseAfterSend == pdTRUE) && (ETHER_ZEROCOPY_DISABLE == p_ether_instance->p_cfg->zerocopy))
    {
        vReleaseNetworkBufferAndDescriptor(pxNetworkBuffer);
    }

    return xReturn;
}

static BaseType_t xFSP_Eth_GetPhyLinkStatus (struct xNetworkInterface * pxInterface)
{
    BaseType_t xReturn = pdPASS;

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = pxInterface->pvArgument;
#else
    (void) pxInterface;
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = gp_freertos_plus_tcp_instance;
#endif

    ether_instance_t * p_ether_instance = p_freertos_plus_tcp_instance->p_cfg->p_ether_instance;

    if (FSP_SUCCESS == p_ether_instance->p_api->linkProcess(p_ether_instance->p_ctrl))
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
    uint32_t   ulNotifyEvent            = 0;

    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance =
        (rm_freertos_plus_tcp_instance_t *) p_args->p_context;
    configASSERT(NULL != p_freertos_plus_tcp_instance);

    /* If EDMAC FR (Frame Receive Event) or FDE (Receive Descriptor Empty Event)
     * interrupt occurs, wake up prvEthernetDeferredInterruptHandlerTask. */
    if ((p_args->event == ETHER_EVENT_RX_COMPLETE) || (p_args->event == ETHER_EVENT_RX_MESSAGE_LOST))
    {
        ulNotifyEvent |= FREERTOS_PLUS_TCP_NOTIFY_EVENT_RX;
    }
    else if (p_args->event == ETHER_EVENT_GET_NIC_INFO)
    {
#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 1) && (ipconfigUSE_IPv4 != 0)
        FreeRTOS_UpdateMACAddress(p_args->p_nic_info->p_mac_address);
#endif
    }

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)

    /* If zero copy mode is enable and link on interrupt occurs, wake up prvEthernetDeferredInterruptHandlerTask. */
    else if (p_args->event == ETHER_EVENT_LINK_ON)
    {
        ulNotifyEvent |= FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_ON;
    }
    /* If zero copy mode is enable and link off interrupt occurs, wake up prvEthernetDeferredInterruptHandlerTask. */
    else if (p_args->event == ETHER_EVENT_LINK_OFF)
    {
        ulNotifyEvent |= FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_OFF;
    }
    /* If zero copy mode is enable and transmit complete interrupt occurs, wake up prvEthernetDeferredInterruptHandlerTask. */
    else if (p_args->event == ETHER_EVENT_TX_COMPLETE)
    {
        ulNotifyEvent |= FREERTOS_PLUS_TCP_NOTIFY_EVENT_TX;
    }
#endif
    else
    {
        /* Do nothing. */
    }

    if ((0 != ulNotifyEvent) &&
        (NULL != p_freertos_plus_tcp_instance->p_ctrl->xEthernetDeferredInterruptHanderTaskHandle))
    {
        xTaskNotifyFromISR(p_freertos_plus_tcp_instance->p_ctrl->xEthernetDeferredInterruptHanderTaskHandle,
                           ulNotifyEvent,
                           eSetBits,   // Set bits (bitwise OR) into the notification event value.
                           &xHigherPriorityTaskWoken);
    }

    /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context switch
     * should be performed to ensure the interrupt returns directly to the highest
     * priority task.  The macro used for this purpose is dependent on the port in
     * use and may be called portEND_SWITCHING_ISR(). */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

size_t uxNetworkInterfaceAllocateRAMToBuffers (
    NetworkBufferDescriptor_t pxNetworkBuffers[ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS])
{
    size_t buffer_size = 0;
#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)
    uint8_t ** pp_ether_buffers;

    /* Get Ethernet buffer address. */
    pp_ether_buffers = ppucFSP_Eth_GetEthernetBufferAddress();

    configASSERT(NULL != pp_ether_buffers);

    buffer_size = FREERTOS_PLUS_TCP_ETHER_BUFFER_SIZE - FREERTOS_PLUS_TCP_IP_PADDING_SIZE -
                  FREERTOS_PLUS_TCP_ETHER_PADDING_SIZE;

    for (uint32_t i = 0; i < ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS; i++)
    {
        /* Store read Ethernet header pointer. */
        pxNetworkBuffers[i].pucEthernetBuffer = pp_ether_buffers[i] + FREERTOS_PLUS_TCP_IP_PADDING_SIZE +
                                                FREERTOS_PLUS_TCP_ETHER_PADDING_SIZE;

        /* Store back pointer in head of buffer. */
        *((NetworkBufferDescriptor_t **) (pp_ether_buffers[i])) = &pxNetworkBuffers[i];
    }

#else

    /* Remove compiler warning about unused parameter. */
    FSP_PARAMETER_NOT_USED(pxNetworkBuffers);
#endif

    return buffer_size;
}

NetworkInterface_t * pxFSP_Eth_FillInterfaceDescriptor (BaseType_t xEMACIndex, NetworkInterface_t * pxInterface)
{
    static char pcName[17];

    configASSERT(NULL != pxInterface);

    /* This function pxFSP_Eth_FillInterfaceDescriptor() adds a network-interface. */
    snprintf(pcName, sizeof(pcName), "eth%u", (unsigned) xEMACIndex);

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
    void * p_freertos_plus_tcp_instance = pxInterface->pvArgument;
    configASSERT(NULL != p_freertos_plus_tcp_instance);
#endif
    memset(pxInterface, '\0', sizeof(*pxInterface));
    pxInterface->pcName = pcName;                  /* Just for logging, debugging. */
#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 1)
    pxInterface->pvArgument = (void *) xEMACIndex; /* Has only meaning for the driver functions. */
#else
    pxInterface->pvArgument = p_freertos_plus_tcp_instance;
#endif
    pxInterface->pfInitialise       = xFSP_Eth_NetworkInterfaceInitialise;
    pxInterface->pfOutput           = xFSP_Eth_NetworkInterfaceOutput;
    pxInterface->pfGetPhyLinkStatus = xFSP_Eth_GetPhyLinkStatus;

    FreeRTOS_AddNetworkInterface(pxInterface);

    return pxInterface;
}

/*-----------------------------------------------------------*/

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 1)

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

static BaseType_t prvNetworkInterfaceInput (NetworkInterface_t * pxInterface) {
    BaseType_t xResult          = pdFAIL;
    BaseType_t xReadResult      = pdFAIL;
    BaseType_t xBufferAllocated = pdFALSE;
    fsp_err_t  err              = FSP_ERR_ASSERTION;

    /* Used to indicate that xSendEventStructToIPTask() is being called because
     * of an Ethernet receive event. */
    IPStackEvent_t              xRxEvent;
    NetworkBufferDescriptor_t * pxBufferDescriptor = NULL;
    uint32_t xBytesReceived = 0;

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = pxInterface->pvArgument;
#else
    FSP_PARAMETER_NOT_USED(pxInterface);
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = gp_freertos_plus_tcp_instance;
#endif

    ether_instance_t * p_ether_instance = p_freertos_plus_tcp_instance->p_cfg->p_ether_instance;

    /* Set the maximum buffer size when reading. */
    xBytesReceived = p_ether_instance->p_cfg->ether_buffer_size;

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)
    uint8_t * pucReadEthernetBuffer = NULL;
    NetworkBufferDescriptor_t * pxNewBufferDescriptor = NULL;

    err = p_ether_instance->p_api->read(p_ether_instance->p_ctrl, (void *) &pucReadEthernetBuffer, &xBytesReceived);

    /* When driver received data. */
    if (FSP_SUCCESS == err)
    {
        /* Store back pointer in head of buffer. */
        pxBufferDescriptor =
            *((NetworkBufferDescriptor_t **) (pucReadEthernetBuffer - FREERTOS_PLUS_TCP_IP_PADDING_SIZE));

        if (NULL != pxBufferDescriptor)
        {
            /* Remove read descriptor from list. */
            prvFSP_Eth_RemoveNetworkBufferDescriptorFromList(
                &p_freertos_plus_tcp_instance->p_ctrl->p_rx_pending_descriptor_list,
                pxBufferDescriptor);

            pxBufferDescriptor->pxNextBuffer = NULL;

            do
            {
                pxNewBufferDescriptor = pxGetNetworkBufferWithDescriptor((size_t) MAXIMUM_ETHERNET_FRAME_SIZE,
                                                                         FREERTOS_PLUS_TCP_GET_DESCRIPTOR_BLOCK_TIME);
            } while (NULL == pxNewBufferDescriptor);

            /* Update new buffer address. */
            p_ether_instance->p_api->rxBufferUpdate(p_ether_instance->p_ctrl,
                                                    (void *) (pxNewBufferDescriptor->pucEthernetBuffer -
                                                              FREERTOS_PLUS_TCP_ETHER_PADDING_SIZE));

            /* Add new descriptor to list. */
            prvFSP_Eth_AddNetworkBufferDescriptorToList(
                &p_freertos_plus_tcp_instance->p_ctrl->p_rx_pending_descriptor_list,
                pxNewBufferDescriptor);

            xReadResult      = pdPASS;
            xBufferAllocated = pdTRUE;
        }
    }

#else
    pxBufferDescriptor = pxGetNetworkBufferWithDescriptor((size_t) MAXIMUM_ETHERNET_FRAME_SIZE, 0);

    if (NULL != pxBufferDescriptor)
    {
        err = p_ether_instance->p_api->read(p_ether_instance->p_ctrl,
                                            (void *) pxBufferDescriptor->pucEthernetBuffer,
                                            &xBytesReceived);

        if (FSP_SUCCESS != err)
        {
            xBytesReceived = 0;
        }

        /* When driver received any data. */
        if ((FSP_SUCCESS == err) || (FSP_ERR_ETHER_ERROR_NO_DATA == err))
        {
            xReadResult = pdPASS;
        }

        xBufferAllocated = pdTRUE;
    }
#endif

    if (pdPASS == xReadResult)
    {
        pxBufferDescriptor->xDataLength = (size_t) xBytesReceived;
        pxBufferDescriptor->pxInterface = pxInterface;
        pxBufferDescriptor->pxEndPoint  =
            FreeRTOS_MatchingEndpoint(pxInterface, pxBufferDescriptor->pucEthernetBuffer);

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

                /* Buffer is transferred to IP stack. */
                xBufferAllocated = pdFALSE;
            }
        }
    }

    /* The buffer is not used to send to the IP task so it must be released. */
    if (pdTRUE == xBufferAllocated)
    {
        vReleaseNetworkBufferAndDescriptor(pxBufferDescriptor);
        iptraceETHERNET_RX_EVENT_LOST();
    }

    return xResult;
}

static void prvEthernetDeferredInterruptHandlerTask (void * pvParameters) {
    BaseType_t xResult       = pdFALSE;
    uint32_t   ulNotifyValue = 0;

#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = ((NetworkInterface_t *) pvParameters)->pvArgument;
#else
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = gp_freertos_plus_tcp_instance;
#endif

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)
    ether_instance_t * p_ether_instance = p_freertos_plus_tcp_instance->p_cfg->p_ether_instance;
    fsp_err_t          err              = FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_freertos_plus_tcp_instance);
#endif

    for ( ; ; )
    {
        /* Wait for the Ethernet MAC interrupt. */
        xTaskNotifyWait(pdFALSE,
                        FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_ON | FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_OFF | FREERTOS_PLUS_TCP_NOTIFY_EVENT_RX | FREERTOS_PLUS_TCP_NOTIFY_EVENT_TX,
                        &ulNotifyValue,
                        portMAX_DELAY);

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)
        if (FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_ON & ulNotifyValue)
        {
            NetworkBufferDescriptor_t * pxBufferDescriptor = NULL;

            p_freertos_plus_tcp_instance->p_ctrl->p_tx_pending_descriptor_list = NULL;
            p_freertos_plus_tcp_instance->p_ctrl->p_rx_pending_descriptor_list = NULL;

            /* Provide RX buffers to the Ethernet driver. */
            for (uint8_t i = 0; i < p_ether_instance->p_cfg->num_rx_descriptors; i++)
            {
                do
                {
                    pxBufferDescriptor = pxGetNetworkBufferWithDescriptor((size_t) MAXIMUM_ETHERNET_FRAME_SIZE,
                                                                          FREERTOS_PLUS_TCP_GET_DESCRIPTOR_BLOCK_TIME);
                } while (NULL == pxBufferDescriptor);

                p_ether_instance->p_api->rxBufferUpdate(p_ether_instance->p_ctrl,
                                                        (void *) (pxBufferDescriptor->pucEthernetBuffer -
                                                                  FREERTOS_PLUS_TCP_ETHER_PADDING_SIZE));

                /* Add rx descriptor to list. */
                prvFSP_Eth_AddNetworkBufferDescriptorToList(
                    &p_freertos_plus_tcp_instance->p_ctrl->p_rx_pending_descriptor_list,
                    pxBufferDescriptor);
            }
        }
#endif

        if (FREERTOS_PLUS_TCP_NOTIFY_EVENT_RX & ulNotifyValue)
        {
            do
            {
                xResult = prvNetworkInterfaceInput(pvParameters);
            } while (pdFAIL != xResult);
        }

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)
        if (FREERTOS_PLUS_TCP_NOTIFY_EVENT_TX & ulNotifyValue)
        {
            uint8_t * pucLastTxEthernetBuffer;
            NetworkBufferDescriptor_t ** ppxHeadBufferDescriptor;

            /* Get last completed TX Ethernet buffer */
            err = p_ether_instance->p_api->txStatusGet(p_ether_instance->p_ctrl, &pucLastTxEthernetBuffer);

            if ((FSP_SUCCESS == err) && (NULL != pucLastTxEthernetBuffer))
            {
                taskENTER_CRITICAL();

                ppxHeadBufferDescriptor = &p_freertos_plus_tcp_instance->p_ctrl->p_tx_pending_descriptor_list;

                while (NULL != *ppxHeadBufferDescriptor)
                {
                    /* Pop head. */
                    NetworkBufferDescriptor_t * pxHeadBufferDescriptor = pxFSP_Eth_PopNetworkBufferDescriptorFromList(
                        ppxHeadBufferDescriptor);

                    uint8_t * pucEthernetBuffer = pxHeadBufferDescriptor->pucEthernetBuffer;

                    /* Release buffer. */
                    vReleaseNetworkBufferAndDescriptor(pxHeadBufferDescriptor);

                    /* Stop when completed buffer is reached. */
                    if (pucEthernetBuffer == pucLastTxEthernetBuffer)
                    {
                        break;
                    }
                }

                taskEXIT_CRITICAL();
            }
        }

        if (FREERTOS_PLUS_TCP_NOTIFY_EVENT_LINK_OFF & ulNotifyValue)
        {
            /* Release RX buffer. */
            while (NULL != p_freertos_plus_tcp_instance->p_ctrl->p_rx_pending_descriptor_list)
            {
                NetworkBufferDescriptor_t * pxRxBufferDescriptor = pxFSP_Eth_PopNetworkBufferDescriptorFromList(
                    &p_freertos_plus_tcp_instance->p_ctrl->p_rx_pending_descriptor_list);

                vReleaseNetworkBufferAndDescriptor(pxRxBufferDescriptor);
            }

            /* Release TX buffer. */
            while (NULL != p_freertos_plus_tcp_instance->p_ctrl->p_tx_pending_descriptor_list)
            {
                NetworkBufferDescriptor_t * pxTxBufferDescriptor = pxFSP_Eth_PopNetworkBufferDescriptorFromList(
                    &p_freertos_plus_tcp_instance->p_ctrl->p_tx_pending_descriptor_list);

                vReleaseNetworkBufferAndDescriptor(pxTxBufferDescriptor);
            }
        }
#endif
    }
}

static void prvCheckLinkStatusTask (void * pvParameters) {
#if (ipconfigIPv4_BACKWARD_COMPATIBLE == 0)
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = ((NetworkInterface_t *) pvParameters)->pvArgument;
#else
    rm_freertos_plus_tcp_instance_t * p_freertos_plus_tcp_instance = gp_freertos_plus_tcp_instance;
#endif

    ether_instance_t * p_ether_instance = p_freertos_plus_tcp_instance->p_cfg->p_ether_instance;

    fsp_err_t current_link_status  = FSP_ERR_ETHER_ERROR_LINK;
    fsp_err_t previous_link_status = FSP_ERR_ETHER_ERROR_LINK;

    for ( ; ; )
    {
        vTaskDelay(p_freertos_plus_tcp_instance->p_cfg->link_check_interval);
        current_link_status = p_ether_instance->p_api->linkProcess(p_ether_instance->p_ctrl);

        /* Link status is changed. */
        if (previous_link_status != current_link_status)
        {
            if (FSP_SUCCESS == current_link_status)
            {
                /* Link status changed to up. */
                previous_link_status = current_link_status;
            }
            else if ((FSP_ERR_ETHER_ERROR_LINK == current_link_status) ||
                     (FSP_ERR_ETHER_PHY_ERROR_LINK == current_link_status))
            {
                /* Link status changed to down. */
                FreeRTOS_NetworkDown((NetworkInterface_t *) pvParameters);
                previous_link_status = current_link_status;
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

#if (FREERTOS_PLUS_TCP_CFG_ZERO_COPY_SUPPORT == 1)

static void prvFSP_Eth_AddNetworkBufferDescriptorToList (NetworkBufferDescriptor_t ** ppxHeadBufferDescriptor,
                                                         NetworkBufferDescriptor_t  * pxNewBufferDescriptor)
{
    NetworkBufferDescriptor_t * pxCurrentBufferDescriptor;

    taskENTER_CRITICAL();

    if ((NULL != ppxHeadBufferDescriptor) && (NULL != pxNewBufferDescriptor))
    {
        /* Initialise next buffer. */
        pxNewBufferDescriptor->pxNextBuffer = NULL;

        /* If list is empty, add buffer. */
        if (NULL == *ppxHeadBufferDescriptor)
        {
            *ppxHeadBufferDescriptor = pxNewBufferDescriptor;
        }
        else
        {
            pxCurrentBufferDescriptor = *ppxHeadBufferDescriptor;

            while (NULL != pxCurrentBufferDescriptor->pxNextBuffer)
            {
                pxCurrentBufferDescriptor = pxCurrentBufferDescriptor->pxNextBuffer;
            }

            pxCurrentBufferDescriptor->pxNextBuffer = pxNewBufferDescriptor;
        }
    }

    taskEXIT_CRITICAL();
}

static void prvFSP_Eth_RemoveNetworkBufferDescriptorFromList (NetworkBufferDescriptor_t ** ppxHeadBufferDescriptor,
                                                              NetworkBufferDescriptor_t  * pxRemoveBufferDescriptor)
{
    NetworkBufferDescriptor_t * pxCurrentBufferDescriptor  = *ppxHeadBufferDescriptor;
    NetworkBufferDescriptor_t * pxPreviousBufferDescriptor = NULL;

    if ((NULL != ppxHeadBufferDescriptor) && (NULL != *ppxHeadBufferDescriptor) && (NULL != pxRemoveBufferDescriptor))
    {
        taskENTER_CRITICAL();

        while (NULL != pxCurrentBufferDescriptor)
        {
            /* If buffer is matched, remove it. */
            if (pxCurrentBufferDescriptor == pxRemoveBufferDescriptor)
            {
                /* Remove head. */
                if (NULL == pxPreviousBufferDescriptor)
                {
                    *ppxHeadBufferDescriptor = pxCurrentBufferDescriptor->pxNextBuffer;
                }
                else
                {
                    pxPreviousBufferDescriptor->pxNextBuffer = pxCurrentBufferDescriptor->pxNextBuffer;
                }

                pxCurrentBufferDescriptor->pxNextBuffer = NULL;
                break;
            }

            pxPreviousBufferDescriptor = pxCurrentBufferDescriptor;
            pxCurrentBufferDescriptor  = pxCurrentBufferDescriptor->pxNextBuffer;
        }

        taskEXIT_CRITICAL();
    }
}

static NetworkBufferDescriptor_t * pxFSP_Eth_PopNetworkBufferDescriptorFromList (
    NetworkBufferDescriptor_t ** ppxHeadBufferDescriptor)
{
    NetworkBufferDescriptor_t * pxBufferDescriptor = *ppxHeadBufferDescriptor;

    taskENTER_CRITICAL();

    if (pxBufferDescriptor != NULL)
    {
        *ppxHeadBufferDescriptor         = pxBufferDescriptor->pxNextBuffer;
        pxBufferDescriptor->pxNextBuffer = NULL;
    }

    taskEXIT_CRITICAL();

    return pxBufferDescriptor;
}

BSP_WEAK_REFERENCE uint8_t ** ppucFSP_Eth_GetEthernetBufferAddress (void)
{
    /* This function should return Ethernet buffer addresses.
     * It is currently not implemented and will assert if called. */
    assert(0);

    return NULL;
}

#endif
