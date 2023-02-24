/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#include "rm_cellular_comm_uart_aws.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define RM_CELLULAR_COMM_UART_AWS_OPEN    (0x434C4946ULL) // Is "CLIF" in ASCII

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Callback for UART driver
 *
 * @param[in]     p_args  Arguments from UART RX/TX callback
 **********************************************************************************************************************/
void comm_uart_aws_callback (uart_callback_args_t * p_args)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE; // Initialized to pdFALSE.
    rm_cellular_comm_uart_aws_instance_ctrl_t * p_instance_ctrl =
        (rm_cellular_comm_uart_aws_instance_ctrl_t *) p_args->p_context;
    uart_instance_t * p_uart_instance = p_instance_ctrl->p_lower_level_instance;

    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
            uint8_t data_byte = (uint8_t) p_args->data;

            if (NULL == p_instance_ctrl->p_recv_buffer)
            {
                /* Read into temp buffer */
                if (p_instance_ctrl->read_count < RM_CELLULAR_COMM_UART_AWS_RX_BUFFER_SIZE)
                {
                    p_instance_ctrl->rx_buffer[p_instance_ctrl->read_count] = data_byte;
                    p_instance_ctrl->read_count++;

                    p_instance_ctrl->receive_callback(p_instance_ctrl->p_user_data,
                                                      (CellularCommInterfaceHandle_t) p_instance_ctrl);
                }
            }
            else
            {
                /* Kick off zero-copy transfer */
                p_instance_ctrl->p_recv_buffer[0] = data_byte;
                p_instance_ctrl->remaining_recv_read_length--;
                p_instance_ctrl->p_recv_buffer++;
                p_instance_ctrl->current_recv_read_length--;

                p_uart_instance->p_api->read(p_uart_instance->p_ctrl,
                                             p_instance_ctrl->p_recv_buffer,
                                             p_instance_ctrl->current_recv_read_length);

                p_instance_ctrl->transfer_in_progress = true;
            }

            break;
        }

        case UART_EVENT_RX_COMPLETE:
        {
            /* Read complete, update remaining length */
            p_instance_ctrl->remaining_recv_read_length = p_instance_ctrl->remaining_recv_read_length -
                                                          p_instance_ctrl->current_recv_read_length;

            if (p_instance_ctrl->remaining_recv_read_length > 0)
            {
                p_instance_ctrl->p_recv_buffer += p_instance_ctrl->current_recv_read_length;

                /* Buffer hasn't been filled yet, continue reading */
                if (p_instance_ctrl->remaining_recv_read_length > RM_CELLULAR_COMM_UART_AWS_RECEIVE_CLUSTER_BYTE_COUNT)
                {
                    p_instance_ctrl->current_recv_read_length = RM_CELLULAR_COMM_UART_AWS_RECEIVE_CLUSTER_BYTE_COUNT;
                }
                else
                {
                    p_instance_ctrl->current_recv_read_length = p_instance_ctrl->remaining_recv_read_length;
                }

                p_uart_instance->p_api->read(p_uart_instance->p_ctrl,
                                             p_instance_ctrl->p_recv_buffer,
                                             p_instance_ctrl->current_recv_read_length);
            }
            else
            {
                /* Buffer has been filled, don't read any more bytes into buffer */
                p_instance_ctrl->p_recv_buffer = NULL;
            }

            /* Notify of byte read */
            xSemaphoreGiveFromISR(p_instance_ctrl->rx_semaphore_handle, &xHigherPriorityTaskWoken);

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            break;
        }

        case UART_EVENT_TX_DATA_EMPTY:
        {
            xSemaphoreGiveFromISR(p_instance_ctrl->tx_semaphore_handle, &xHigherPriorityTaskWoken);

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            break;
        }

        default:
        {
            /* Do Nothing */
        }
    }
}

/*******************************************************************************************************************//**
 * Implements open for CellularCommInterface_t
 *
 * @param[in] receive_callback      Callback to call upon receiving data
 * @param[in] pUserData             Pointer to user data to be passed through callback
 * @param[in] p_instance_ctrl       Pointer to a rm_cellular_comm_uart_aws_instance_ctrl_t
 *
 * @retval  IOT_COMM_INTERFACE_SUCCESS          Open succeeded
 * @retval  IOT_COMM_INTERFACE_BAD_PARAMETER    Bad parameter was passed in
 * @retval  IOT_COMM_INTERFACE_FAILURE          General failure
 * @retval  IOT_COMM_INTERFACE_DRIVER_ERROR     Lower level failure
 **********************************************************************************************************************/
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Open (
    rm_cellular_comm_uart_aws_instance_ctrl_t * p_instance_ctrl,
    CellularCommInterfaceReceiveCallback_t      receive_callback,
    void                                      * pUserData)
{
    uart_instance_t * p_uart_instance;

#if RM_CELLULAR_COMM_UART_AWS_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != p_instance_ctrl, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(RM_CELLULAR_COMM_UART_AWS_OPEN != p_instance_ctrl->open, IOT_COMM_INTERFACE_FAILURE);
    FSP_ERROR_RETURN(NULL != p_instance_ctrl->p_lower_level_instance, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(NULL != receive_callback, IOT_COMM_INTERFACE_BAD_PARAMETER);
#endif

    p_instance_ctrl->p_user_data          = pUserData;
    p_instance_ctrl->receive_callback     = receive_callback;
    p_instance_ctrl->read_count           = 0;
    p_instance_ctrl->p_recv_buffer        = NULL;
    p_instance_ctrl->transfer_in_progress = false;

    p_uart_instance = p_instance_ctrl->p_lower_level_instance;

    /* Create semaphore for send */
    p_instance_ctrl->tx_semaphore_handle = xSemaphoreCreateBinaryStatic(&p_instance_ctrl->tx_semaphore_buffer);
    FSP_ERROR_RETURN(NULL != p_instance_ctrl->tx_semaphore_handle, IOT_COMM_INTERFACE_FAILURE);

    xSemaphoreTake(p_instance_ctrl->tx_semaphore_handle, 0);

    /* Create semaphore for receieve */
    p_instance_ctrl->rx_semaphore_handle = xSemaphoreCreateBinaryStatic(&p_instance_ctrl->rx_semaphore_buffer);
    FSP_ERROR_RETURN(NULL != p_instance_ctrl->rx_semaphore_handle, IOT_COMM_INTERFACE_FAILURE);

    xSemaphoreTake(p_instance_ctrl->rx_semaphore_handle, 0);

    /* Open lower level UART driver */
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_uart_instance->p_api->open(p_uart_instance->p_ctrl, p_uart_instance->p_cfg),
                     IOT_COMM_INTERFACE_DRIVER_ERROR);

    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     p_uart_instance->p_api->callbackSet(p_uart_instance->p_ctrl, comm_uart_aws_callback,
                                                         p_instance_ctrl, NULL),
                     IOT_COMM_INTERFACE_DRIVER_ERROR);

    p_instance_ctrl->open = RM_CELLULAR_COMM_UART_AWS_OPEN;

    return IOT_COMM_INTERFACE_SUCCESS;
}

/*******************************************************************************************************************//**
 * Implements send for CellularCommInterface_t. This function will block the calling thread until data is sent.
 *
 * @param[in] commInterfaceHandle   CellularCommInterfaceHandle_t assigned in open
 * @param[in] pData                 Pointer to data to send
 * @param[in] dataLength            Length of data to send
 * @param[in] timeoutMilliseconds   Timeout in MS to wait for data to send
 * @param[in] pDataSentLength       Actual length of data sent
 *
 * @retval  IOT_COMM_INTERFACE_SUCCESS          Send succeeded
 * @retval  IOT_COMM_INTERFACE_BAD_PARAMETER    Bad parameter was passed in
 * @retval  IOT_COMM_INTERFACE_FAILURE          General failure
 * @retval  IOT_COMM_INTERFACE_DRIVER_ERROR     Lower level failure
 * @retval  IOT_COMM_INTERFACE_TIMEOUT          Send operation timed out
 **********************************************************************************************************************/
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Send (CellularCommInterfaceHandle_t commInterfaceHandle,
                                                             const uint8_t               * pData,
                                                             uint32_t                      dataLength,
                                                             uint32_t                      timeoutMilliseconds,
                                                             uint32_t                    * pDataSentLength)
{
    rm_cellular_comm_uart_aws_instance_ctrl_t * p_instance_ctrl =
        (rm_cellular_comm_uart_aws_instance_ctrl_t *) commInterfaceHandle;
    uart_instance_t            * p_uart_instance;
    CellularCommInterfaceError_t comm_err = IOT_COMM_INTERFACE_SUCCESS;

#if RM_CELLULAR_COMM_UART_AWS_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != p_instance_ctrl, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(NULL != pData, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(NULL != pDataSentLength, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(RM_CELLULAR_COMM_UART_AWS_OPEN == p_instance_ctrl->open, IOT_COMM_INTERFACE_FAILURE);
#endif

    p_uart_instance  = p_instance_ctrl->p_lower_level_instance;
    *pDataSentLength = 0;

    /* Write to lower level driver */
    if (FSP_SUCCESS == p_uart_instance->p_api->write(p_uart_instance->p_ctrl, pData, dataLength))
    {
        /* Wait for UART_EVENT_TX_DATA_EMPTY semaphore */
        if (pdTRUE == xSemaphoreTake(p_instance_ctrl->tx_semaphore_handle, pdMS_TO_TICKS(timeoutMilliseconds)))
        {
            /* Set sent data length */
            *pDataSentLength = dataLength;
        }
        else
        {
            comm_err = IOT_COMM_INTERFACE_TIMEOUT;
        }
    }
    else
    {
        comm_err = IOT_COMM_INTERFACE_DRIVER_ERROR;
    }

    return comm_err;
}

/*******************************************************************************************************************//**
 * Implements receive for CellularCommInterface_t. This function will block the
 * calling thread until data is received.
 *
 * @param[in] commInterfaceHandle   CellularCommInterfaceHandle_t assigned in open
 * @param[in] pBuffer               Pointer to buffer to receive to
 * @param[in] bufferLength          Length of buffer
 * @param[in] timeoutMilliseconds   Timeout in MS to wait for data reception
 * @param[in] pDataReceivedLength   Actual length of data received
 *
 * @retval  IOT_COMM_INTERFACE_SUCCESS          Receieve succeeded
 * @retval  IOT_COMM_INTERFACE_BAD_PARAMETER    Bad parameter was passed in
 * @retval  IOT_COMM_INTERFACE_FAILURE          General failure
 * @retval  IOT_COMM_INTERFACE_DRIVER_ERROR     Lower level failure
 **********************************************************************************************************************/
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Receive (CellularCommInterfaceHandle_t commInterfaceHandle,
                                                                uint8_t                     * pBuffer,
                                                                uint32_t                      bufferLength,
                                                                uint32_t                      timeoutMilliseconds,
                                                                uint32_t                    * pDataReceivedLength)
{
    rm_cellular_comm_uart_aws_instance_ctrl_t * p_instance_ctrl =
        (rm_cellular_comm_uart_aws_instance_ctrl_t *) commInterfaceHandle;

#if RM_CELLULAR_COMM_UART_AWS_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != p_instance_ctrl, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(NULL != pBuffer, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(NULL != pDataReceivedLength, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(RM_CELLULAR_COMM_UART_AWS_OPEN == p_instance_ctrl->open, IOT_COMM_INTERFACE_FAILURE);
#endif

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if (bufferLength > p_instance_ctrl->read_count)
    {
        p_instance_ctrl->remaining_recv_read_length = bufferLength - p_instance_ctrl->read_count;
        p_instance_ctrl->p_recv_buffer              = pBuffer + p_instance_ctrl->read_count;

        if (p_instance_ctrl->remaining_recv_read_length > RM_CELLULAR_COMM_UART_AWS_RECEIVE_CLUSTER_BYTE_COUNT)
        {
#if RM_CELLULAR_COMM_UART_AWS_RECEIVE_CLUSTER_BYTE_COUNT > 1
            p_instance_ctrl->current_recv_read_length = RM_CELLULAR_COMM_UART_AWS_RECEIVE_CLUSTER_BYTE_COUNT;
#else

            /* Special case for 1 */
            p_instance_ctrl->current_recv_read_length = RM_CELLULAR_COMM_UART_AWS_RECEIVE_CLUSTER_BYTE_COUNT + 1;
#endif
        }
        else
        {
            p_instance_ctrl->current_recv_read_length = p_instance_ctrl->remaining_recv_read_length;
        }

        memcpy(pBuffer, p_instance_ctrl->rx_buffer, p_instance_ctrl->read_count);

        p_instance_ctrl->read_count = 0;
    }
    else
    {
        /* Amount to store in read buffer is less than or equal to what has been read in rx_buffer, only copy bufferLength */
        memcpy(pBuffer, p_instance_ctrl->rx_buffer, bufferLength);

        if (bufferLength < p_instance_ctrl->read_count)
        {
            /* Buffer length is less than read count, move bytes not copied to pBuffer to front of rx_buffer */
            p_instance_ctrl->read_count = p_instance_ctrl->read_count - bufferLength;

            memcpy(p_instance_ctrl->rx_buffer, p_instance_ctrl->rx_buffer + bufferLength, p_instance_ctrl->read_count);
        }
        else
        {
            p_instance_ctrl->read_count = 0;
        }

        *pDataReceivedLength = bufferLength;
    }

    FSP_CRITICAL_SECTION_EXIT;

    if (NULL != p_instance_ctrl->p_recv_buffer)
    {
        /* Loop until timeout/transfer complete */
        while (true)
        {
            /* Wait for UART_EVENT_RX_COMPLETE semaphore */
            if (pdTRUE == xSemaphoreTake(p_instance_ctrl->rx_semaphore_handle, pdMS_TO_TICKS(timeoutMilliseconds)))
            {
                if ((0 == p_instance_ctrl->remaining_recv_read_length) && (NULL == p_instance_ctrl->p_recv_buffer))
                {
                    /* Full bufferLength was read */
                    *pDataReceivedLength = bufferLength;
                    break;
                }
            }
            else
            {
                /* Byte read timed out */
                FSP_CRITICAL_SECTION_ENTER;

                p_instance_ctrl->p_recv_buffer = NULL;

                /* Check for semaphore one more time inside critical section */
                if (pdTRUE != xSemaphoreTake(p_instance_ctrl->rx_semaphore_handle, 0))
                {
                    /* Semaphore not posted, continue to abort read */
                    uart_instance_t * p_uart_instance = p_instance_ctrl->p_lower_level_instance;
                    uint32_t          remaining_bytes;

                    if (p_instance_ctrl->transfer_in_progress)
                    {
                        if (FSP_SUCCESS != p_uart_instance->p_api->readStop(p_uart_instance->p_ctrl, &remaining_bytes))
                        {
                            /* No more data received, cancel transfer */
                            FSP_CRITICAL_SECTION_EXIT;
                            *pDataReceivedLength = 0;

                            return IOT_COMM_INTERFACE_DRIVER_ERROR;
                        }

                        /* Get received data length */
                        uint32_t current_bytes_read    = p_instance_ctrl->current_recv_read_length - remaining_bytes;
                        uint32_t total_remaining_bytes = p_instance_ctrl->remaining_recv_read_length -
                                                         current_bytes_read;
                        *pDataReceivedLength = bufferLength - total_remaining_bytes;
                    }
                    else
                    {
                        /* Transfer never started */
                        *pDataReceivedLength = bufferLength - p_instance_ctrl->remaining_recv_read_length;
                    }

                    FSP_CRITICAL_SECTION_EXIT;
                    break;
                }

                if ((0 == p_instance_ctrl->remaining_recv_read_length) && (NULL == p_instance_ctrl->p_recv_buffer))
                {
                    /* Full bufferLength was read */
                    *pDataReceivedLength = bufferLength;
                    FSP_CRITICAL_SECTION_EXIT;
                    break;
                }

                FSP_CRITICAL_SECTION_EXIT;
            }
        }

        p_instance_ctrl->transfer_in_progress = false;
    }

    return IOT_COMM_INTERFACE_SUCCESS;
}

/*******************************************************************************************************************//**
 * Implements close for CellularCommInterface_t
 *
 * @param[in] commInterfaceHandle   CellularCommInterfaceHandle_t assigned in open
 *
 * @retval  IOT_COMM_INTERFACE_SUCCESS          Close succeeded
 * @retval  IOT_COMM_INTERFACE_BAD_PARAMETER    Bad parameter was passed in
 * @retval  IOT_COMM_INTERFACE_FAILURE          General failure
 **********************************************************************************************************************/
CellularCommInterfaceError_t RM_CELLULAR_COMM_UART_AWS_Close (CellularCommInterfaceHandle_t commInterfaceHandle)
{
    rm_cellular_comm_uart_aws_instance_ctrl_t * p_instance_ctrl =
        (rm_cellular_comm_uart_aws_instance_ctrl_t *) commInterfaceHandle;
    uart_instance_t * p_uart_instance;

#if RM_CELLULAR_COMM_UART_AWS_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != p_instance_ctrl, IOT_COMM_INTERFACE_BAD_PARAMETER);
    FSP_ERROR_RETURN(RM_CELLULAR_COMM_UART_AWS_OPEN == p_instance_ctrl->open, IOT_COMM_INTERFACE_FAILURE);
#endif

    /* Clear open indicator */
    p_instance_ctrl->open = 0;

    p_uart_instance = p_instance_ctrl->p_lower_level_instance;

    /* Close UART */
    p_uart_instance->p_api->close(p_uart_instance->p_ctrl);

    return IOT_COMM_INTERFACE_SUCCESS;
}
