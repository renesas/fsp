/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "rm_at_transport_da16xxx_uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "semphr.h"

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/
#if (BSP_FEATURE_SCI_VERSION == 2U)
 #include "r_sci_b_uart.h"
typedef sci_b_uart_instance_ctrl_t rm_at_transport_da16xxx_uart_instance_ctrl_t;
typedef sci_b_uart_extended_cfg_t  at_transport_da16xxx_uart_extended_cfg_t;
typedef sci_b_baud_setting_t       rm_at_transport_da16xxx_baud_setting_t;
 #define RM_AT_TRANSPORT_DA16XXX_SCI_UART_FLOW_CONTROL_RTS                SCI_B_UART_FLOW_CONTROL_RTS
 #define RM_AT_TRANSPORT_DA16XXX_SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS    SCI_B_UART_FLOW_CONTROL_HARDWARE_CTSRTS
static fsp_err_t (* p_sci_uart_baud_calculate)(uint32_t, bool, uint32_t,
                                               struct st_sci_b_baud_setting_t * const) = &R_SCI_B_UART_BaudCalculate;
#else
 #include "r_sci_uart.h"
typedef sci_uart_instance_ctrl_t rm_at_transport_da16xxx_uart_instance_ctrl_t;
typedef sci_uart_extended_cfg_t  at_transport_da16xxx_uart_extended_cfg_t;
typedef baud_setting_t           rm_at_transport_da16xxx_baud_setting_t;
 #define RM_AT_TRANSPORT_DA16XXX_SCI_UART_FLOW_CONTROL_RTS                SCI_UART_FLOW_CONTROL_RTS
 #define RM_AT_TRANSPORT_DA16XXX_SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS    SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS
static fsp_err_t (* p_sci_uart_baud_calculate)(uint32_t, bool, uint32_t,
                                               baud_setting_t * const) = &R_SCI_UART_BaudCalculate;
#endif

/* Mutex give/take defines */
#define AT_TRANSPORT_DA16XXX_MUTEX_TX                                     (1 << 0)
#define AT_TRANSPORT_DA16XXX_MUTEX_RX                                     (1 << 1)

/* Text full versions of AT command returns */
#define AT_TRANSPORT_DA16XXX_RETURN_TEXT_OK                               "OK"
#define AT_TRANSPORT_DA16XXX_RETURN_CONN_TEXT                             "+WFJAP:1"

/* DA16XXX UART port defines */
#define AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT                            (0)
#define AT_TRANSPORT_DA16XXX_UART_SECOND_PORT                             (1)

/* Initial DA16XXX Wifi module UART settings */
#define AT_TRANSPORT_DA16XXX_DEFAULT_BAUDRATE                             (115200)
#define AT_TRANSPORT_DA16XXX_DEFAULT_MODULATION                           false
#define AT_TRANSPORT_DA16XXX_DEFAULT_ERROR                                (9000)

/* Pin or port invalid definition */
#define AT_TRANSPORT_DA16XXX_BSP_PIN_PORT_INVALID                         (UINT16_MAX)

#define AT_TRANSPORT_DA16XXX_TEMP_BUFF_SIZE                               (30)

/* Predefined timeout values */
#define AT_TRANSPORT_DA16XXX_TIMEOUT_1MS                                  (1)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_3MS                                  (3)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_5MS                                  (5)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_10MS                                 (10)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_20MS                                 (20)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_30MS                                 (30)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_100MS                                (100)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_200MS                                (200)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_300MS                                (300)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_400MS                                (400)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_500MS                                (500)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_1SEC                                 (1000)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_2SEC                                 (2000)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_3SEC                                 (3000)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_4SEC                                 (4000)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_5SEC                                 (5000)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_8SEC                                 (8000)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_15SEC                                (15000)
#define AT_TRANSPORT_DA16XXX_TIMEOUT_20SEC                                (20000)

/* Unique number for SCI Open Status */
#if (BSP_FEATURE_SCI_VERSION == 2U)
 #define SCIU_OPEN                                                        (0x53434942U) // Is "SCIB" in ASCII
#else
 #define SCIU_OPEN                                                        (0x53434955U) // Is "SCIU" in ASCII
#endif

#define UART_BAUD_MAX_CNT                                                 (4)

/* UART Baud rates */
#define UART_BAUD_115200                                                  (115200)
#define UART_BAUD_230400                                                  (230400)
#define UART_BAUD_460800                                                  (460800)
#define UART_BAUD_921600                                                  (921600)

/* Definitions of Open flag "DATU" */
#define AT_TRANSPORT_DA16XXX_UART_OPEN                                    (0x44415455ULL)

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/
extern const ioport_instance_t g_ioport;

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
at_transport_da16xxx_api_t const g_at_transport_da16xxx_on_uart =
{
    .open  = rm_at_transport_da16xxx_uartOpen,
    .close = rm_at_transport_da16xxx_uartClose,
    .atCommandSendThreadSafe = rm_at_transport_da16xxx_uart_atCommandSendThreadSafe,
    .atCommandSend           = rm_at_transport_da16xxx_uart_atCommandSend,
    .giveMutex               = rm_at_transport_da16xxx_uart_giveMutex,
    .takeMutex               = rm_at_transport_da16xxx_uart_takeMutex,
    .bufferRecv              = rm_at_transport_da16xxx_uart_bufferRecv,
    .statusGet               = rm_at_transport_da16xxx_statusGet,
};

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/
static rm_at_transport_da16xxx_baud_setting_t g_baud_setting =
{
#if (2U == BSP_FEATURE_SCI_VERSION)
    .baudrate_bits_b.brme  = 0,
    .baudrate_bits_b.abcse = 0,
    .baudrate_bits_b.abcs  = 0,
    .baudrate_bits_b.bgdm  = 0,
    .baudrate_bits_b.brr   = 0,
    .baudrate_bits_b.mddr  = 0,
#else
    .semr_baudrate_bits_b.brme  = 0,
    .semr_baudrate_bits_b.abcse = 0,
    .semr_baudrate_bits_b.abcs  = 0,
    .semr_baudrate_bits_b.bgdm  = 0,
    .brr  = 0,
    .mddr = 0,
#endif
};

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

/* Transmit and receive mutexes for UARTs */
static StaticSemaphore_t g_socket_mutexes[2];
static StaticSemaphore_t g_uart_tei_mutex[2];

#define RX_CMD_BUFFER_SIZE    100
static uint8_t rx_cmd_buffer[RX_CMD_BUFFER_SIZE];

/**
 *  Maximum time in ticks to wait for obtaining a semaphore.
 */
static const TickType_t wifi_sx_wifi_da16xxx_sem_block_timeout =
    pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_CFG_SEM_MAX_TIMEOUT);

static void      rm_at_transport_da16xxx_cleanup_open(at_transport_da16xxx_ctrl_t * const p_ctrl);
static fsp_err_t rm_at_transport_da16xxx_error_lookup(char * p_resp);
static void      rm_at_transport_da16xxx_reset(at_transport_da16xxx_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 *  Opens and configures the WIFI_DA16XXX Middleware module.
 *
 *  @param[in]  p_ctrl       Pointer to Transport layer instance control structure.
 *  @param[in]  p_cfg        Pointer to pin configuration structure.
 *
 *  @retval FSP_SUCCESS              WIFI_DA16XXX successfully configured.
 *  @retval FSP_ERR_ASSERTION        The parameter p_cfg or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_OUT_OF_MEMORY    There is no more heap memory available.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 *  @retval FSP_ERR_WIFI_INIT_FAILED WiFi module initialization failed.
 **********************************************************************************************************************/
fsp_err_t rm_at_transport_da16xxx_uartOpen (at_transport_da16xxx_ctrl_t * const      p_ctrl,
                                            at_transport_da16xxx_cfg_t const * const p_cfg)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;
    fsp_err_t         err    = FSP_SUCCESS;
    uart_instance_t * p_uart = NULL;
    at_transport_da16xxx_uart_extended_cfg_t uart0_cfg_extended;
    at_transport_da16xxx_extended_cfg_t    * p_da16xxx_transport_extended_cfg;
    uart_cfg_t uart0_cfg;
    uint8_t    temp_buff[AT_TRANSPORT_DA16XXX_TEMP_BUFF_SIZE] = {0};
    uint8_t  * p_temp_buff = temp_buff;
    uint32_t   uart_baud_rates[UART_BAUD_MAX_CNT] =
    {
        UART_BAUD_115200, UART_BAUD_230400, UART_BAUD_460800, UART_BAUD_921600
    };
    uint32_t curr_uart_baud = 0;
    int      index          = 0;
    at_transport_da16xxx_data_t atcmd;

#if (AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_UART_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Clear the control structure */
    memset(p_instance_ctrl, 0, sizeof(at_transport_da16xxx_instance_ctrl_t));

    /* Update control structure from configuration values */
    p_instance_ctrl->p_cfg           = p_cfg;
    p_da16xxx_transport_extended_cfg =
        (at_transport_da16xxx_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    p_instance_ctrl->p_context     = p_cfg->p_context;
    p_instance_ctrl->p_callback    = p_cfg->p_callback;
    p_instance_ctrl->curr_cmd_port = AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT;

    for (uint32_t i = 0; i < p_da16xxx_transport_extended_cfg->num_uarts; i++)
    {
        p_instance_ctrl->uart_instance_objects[i] =
            (uart_instance_t *) p_da16xxx_transport_extended_cfg->uart_instances[i];

        p_instance_ctrl->uart_tei_sem[i] = xSemaphoreCreateBinaryStatic(&g_uart_tei_mutex[i]);
        if (NULL == p_instance_ctrl->uart_tei_sem[i])
        {
            rm_at_transport_da16xxx_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(NULL != p_instance_ctrl->uart_tei_sem[i], FSP_ERR_OUT_OF_MEMORY);

        xSemaphoreTake(p_instance_ctrl->uart_tei_sem[i], 0);
    }

    /* Create the Tx/Rx mutexes */
    if (p_instance_ctrl->tx_sem != NULL)
    {
        vSemaphoreDelete(p_instance_ctrl->tx_sem);
    }

    p_instance_ctrl->tx_sem = xSemaphoreCreateMutexStatic(&g_socket_mutexes[0]);
    if (NULL == p_instance_ctrl->tx_sem)
    {
        rm_at_transport_da16xxx_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->tx_sem, FSP_ERR_OUT_OF_MEMORY);

    if (p_instance_ctrl->rx_sem != NULL)
    {
        vSemaphoreDelete(p_instance_ctrl->rx_sem);
    }

    p_instance_ctrl->rx_sem = xSemaphoreCreateMutexStatic(&g_socket_mutexes[1]);
    if (NULL == p_instance_ctrl->rx_sem)
    {
        rm_at_transport_da16xxx_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->rx_sem, FSP_ERR_OUT_OF_MEMORY);

    /* Create the stream buffer used to transfer UART data from ISR */
    p_instance_ctrl->socket_byteq_hdl = xStreamBufferCreateStatic(sizeof(p_instance_ctrl->cmd_rx_queue_buf),
                                                                  1,
                                                                  p_instance_ctrl->cmd_rx_queue_buf,
                                                                  &p_instance_ctrl->socket_byteq_struct);
    if (NULL == p_instance_ctrl->socket_byteq_hdl)
    {
        rm_at_transport_da16xxx_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->socket_byteq_hdl, FSP_ERR_OUT_OF_MEMORY);

    /* Create memory copy of uart extended configuration and then copy new configuration values in. */
    memcpy((void *) &uart0_cfg_extended, (void *) p_instance_ctrl->uart_instance_objects[0]->p_cfg->p_extend,
           sizeof(at_transport_da16xxx_uart_extended_cfg_t));

    /* Create memory copy of uart configuration and update with new extended configuration structure. */
    memcpy((void *) &uart0_cfg, p_instance_ctrl->uart_instance_objects[0]->p_cfg, sizeof(uart_cfg_t));

    rm_at_transport_da16xxx_reset(p_instance_ctrl);

    p_instance_ctrl->open = AT_TRANSPORT_DA16XXX_UART_OPEN;
    for (index = 0; index < UART_BAUD_MAX_CNT; index++)
    {
        curr_uart_baud = uart_baud_rates[index];

        (*p_sci_uart_baud_calculate)(curr_uart_baud, AT_TRANSPORT_DA16XXX_DEFAULT_MODULATION,
                                     AT_TRANSPORT_DA16XXX_DEFAULT_ERROR, &g_baud_setting);

        uart0_cfg_extended.p_baud_setting   = &g_baud_setting;
        uart0_cfg_extended.flow_control     = RM_AT_TRANSPORT_DA16XXX_SCI_UART_FLOW_CONTROL_RTS;
        uart0_cfg_extended.flow_control_pin = (bsp_io_port_pin_t) AT_TRANSPORT_DA16XXX_BSP_PIN_PORT_INVALID;

        uart0_cfg.p_extend   = (void *) &uart0_cfg_extended;
        uart0_cfg.p_callback = rm_at_transport_da16xxx_uart_callback;
        uart0_cfg.p_context  = p_instance_ctrl;

        /* Open UART */
        p_uart = p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT];
        err    = p_uart->p_api->open(p_uart->p_ctrl, &uart0_cfg);

        if (FSP_SUCCESS != err)
        {
            rm_at_transport_da16xxx_uartClose(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

        /* Delay after open */
        vTaskDelay(pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_TIMEOUT_10MS));
        atcmd.p_at_cmd_string      = (uint8_t *) "ATZ\r";
        atcmd.at_cmd_string_length = 0;
        atcmd.p_response_buffer    = rx_cmd_buffer;
        atcmd.response_buffer_size = RX_CMD_BUFFER_SIZE;
        atcmd.timeout_ms           = AT_TRANSPORT_DA16XXX_TIMEOUT_200MS;
        atcmd.p_expect_code        = AT_TRANSPORT_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_cmd_port;

        /* Test basic communications with an AT command. */
        err = rm_at_transport_da16xxx_uart_atCommandSend(p_instance_ctrl, &atcmd);

        if (FSP_SUCCESS != err)
        {
            vTaskDelay(pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_TIMEOUT_2SEC));

            /* Test basic communications with an AT command. */
            atcmd.p_at_cmd_string      = (uint8_t *) "ATZ\r";
            atcmd.at_cmd_string_length = 0;
            atcmd.p_response_buffer    = rx_cmd_buffer;
            atcmd.response_buffer_size = RX_CMD_BUFFER_SIZE;
            atcmd.timeout_ms           = AT_TRANSPORT_DA16XXX_TIMEOUT_200MS;
            atcmd.p_expect_code        = AT_TRANSPORT_DA16XXX_RETURN_TEXT_OK;
            atcmd.comm_ch_id           = p_instance_ctrl->curr_cmd_port;

            /* Test basic communications with an AT command. */
            err = rm_at_transport_da16xxx_uart_atCommandSend(p_instance_ctrl, &atcmd);
            if (FSP_SUCCESS != err)
            {
                /* Close the UART port */
                err = p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT]->p_api->close(
                    p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT]->p_ctrl);

                if (FSP_SUCCESS != err)
                {
                    rm_at_transport_da16xxx_uartClose(p_instance_ctrl);
                    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
                }

                /* Delay after close */
                vTaskDelay(pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_TIMEOUT_10MS));
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    if (UART_BAUD_MAX_CNT == (index))
    {
        rm_at_transport_da16xxx_uartClose(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(UART_BAUD_MAX_CNT != (index), FSP_ERR_WIFI_FAILED);

    /* Update the module baud rate in case if it doesn't match with user configured baud rate */
    if (curr_uart_baud != (uint32_t) strtol((char *) g_at_transport_da16xxx_uart_cmd_baud, NULL, 10))
    {
        strncpy((char *) p_temp_buff, "ATB=", 5);
        strncat((char *) p_temp_buff, g_at_transport_da16xxx_uart_cmd_baud, 10);
        strncat((char *) p_temp_buff, "\r", 3);

        atcmd.p_at_cmd_string      = p_temp_buff;
        atcmd.at_cmd_string_length = 0;
        atcmd.p_response_buffer    = rx_cmd_buffer;
        atcmd.response_buffer_size = RX_CMD_BUFFER_SIZE;
        atcmd.timeout_ms           = AT_TRANSPORT_DA16XXX_TIMEOUT_200MS;
        atcmd.p_expect_code        = AT_TRANSPORT_DA16XXX_RETURN_TEXT_OK;
        atcmd.comm_ch_id           = p_instance_ctrl->curr_cmd_port;

        /* Test basic communications with an AT command. */
        err = rm_at_transport_da16xxx_uart_atCommandSend(p_instance_ctrl, &atcmd);
        if (FSP_SUCCESS != err)
        {
            rm_at_transport_da16xxx_uartClose(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
    }

    /* Close the UART port */
    err = p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT]->p_api->close(
        p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT]->p_ctrl);

    if (FSP_SUCCESS != err)
    {
        rm_at_transport_da16xxx_uartClose(p_instance_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
    }

    /* Delay after close */
    vTaskDelay(pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_TIMEOUT_10MS));

    /* Open uart port with config values from the configurator */
    p_uart = p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT];
    err    = p_uart->p_api->open(p_uart->p_ctrl, p_uart->p_cfg);
    if (FSP_SUCCESS != err)
    {
        rm_at_transport_da16xxx_uartClose(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

    p_uart->p_api->callbackSet(p_uart->p_ctrl, rm_at_transport_da16xxx_uart_callback, p_instance_ctrl, NULL);

    /* Delay after open */
    vTaskDelay(pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_TIMEOUT_100MS));

    /* Test basic communications with an AT command. */
    atcmd.p_at_cmd_string      = (uint8_t *) "ATZ\r";
    atcmd.at_cmd_string_length = 0;
    atcmd.p_response_buffer    = rx_cmd_buffer;
    atcmd.response_buffer_size = RX_CMD_BUFFER_SIZE;
    atcmd.timeout_ms           = AT_TRANSPORT_DA16XXX_TIMEOUT_500MS;
    atcmd.p_expect_code        = AT_TRANSPORT_DA16XXX_RETURN_TEXT_OK;
    atcmd.comm_ch_id           = p_instance_ctrl->curr_cmd_port;

    /* Test basic communications with an AT command. */
    err = rm_at_transport_da16xxx_uart_atCommandSend(p_instance_ctrl, &atcmd);

    if (FSP_SUCCESS != err)
    {
        rm_at_transport_da16xxx_uartClose(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Closes the AT Transport DA16XXX Middleware module.
 *
 *  @param[in]  p_ctrl       Pointer to Transport layer instance control structure.
 *
 *  @retval FSP_SUCCESS              WIFI_DA16XXX successfully configured.
 *  @retval FSP_ERR_ASSERTION        The parameter p_cfg or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_NOT_OPEN         The Transport layer instance is not open.
 **********************************************************************************************************************/
fsp_err_t rm_at_transport_da16xxx_uartClose (at_transport_da16xxx_ctrl_t * const p_ctrl)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;

    /* Do parameter checking */
#if (1 == AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    rm_at_transport_da16xxx_cleanup_open(p_instance_ctrl);
    p_instance_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets the status of the configured DA16xxx transport.
 *
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 **********************************************************************************************************************/
fsp_err_t rm_at_transport_da16xxx_statusGet (at_transport_da16xxx_ctrl_t * const p_ctrl,
                                             at_transport_da16xxx_status_t     * p_status)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;

#if AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED
    FSP_ASSERT(p_instance_ctrl != NULL);
    FSP_ASSERT(p_status != NULL);
#endif

    p_status->open = (AT_TRANSPORT_DA16XXX_UART_OPEN == p_instance_ctrl->open);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Send an AT command with testing for return response.
 *
 * @param[in]  p_ctrl               Pointer to Transport layer instance control structure.
 * @param[in]  p_at_cmd              Pointer to AT command data structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 **********************************************************************************************************************/
fsp_err_t rm_at_transport_da16xxx_uart_atCommandSendThreadSafe (at_transport_da16xxx_ctrl_t * const p_ctrl,
                                                                at_transport_da16xxx_data_t       * p_at_cmd)
{
    fsp_err_t err = FSP_SUCCESS;
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;
    uint32_t mutex_flag;

#if (AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_at_cmd);
    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (AT_TRANSPORT_DA16XXX_MUTEX_TX | AT_TRANSPORT_DA16XXX_MUTEX_RX);

    FSP_ERROR_RETURN(FSP_SUCCESS == rm_at_transport_da16xxx_uart_takeMutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    /* Test basic communications with an AT command. */
    err = rm_at_transport_da16xxx_uart_atCommandSend(p_instance_ctrl, p_at_cmd);

    rm_at_transport_da16xxx_uart_giveMutex(p_instance_ctrl, mutex_flag);

    /* Check response for 'OK' */
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Receive data from stream buffer.
 *
 * @param[in]  p_ctrl               Pointer to Transport layer instance control structure.
 * @param[in]  p_data               Pointer to data.
 * @param[in]  length               Data length.
 * @param[in]  rx_timeout           Timeout for receiving data on the buffer.
 *
 * @retval Number of bytes pulled from Streambuffer
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_INVALID_DATA     Accuracy of data is not guaranteed
 **********************************************************************************************************************/
size_t rm_at_transport_da16xxx_uart_bufferRecv (at_transport_da16xxx_ctrl_t * const p_ctrl,
                                                const char                        * p_data,
                                                uint32_t                            length,
                                                uint32_t                            rx_timeout)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;
    uint32_t mutex_flag;
    size_t   xReceivedBytes = 0;
#if (AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ASSERT(0 != length);
    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    uint8_t * p_rcv      = (uint8_t *) p_data;
    uint32_t  recv_index = 0;

    mutex_flag = (AT_TRANSPORT_DA16XXX_MUTEX_RX);
    rm_at_transport_da16xxx_uart_takeMutex(p_instance_ctrl, mutex_flag);
    xStreamBufferSetTriggerLevel(p_instance_ctrl->socket_byteq_hdl, 1);
    size_t incomeBytes =
        xStreamBufferReceive(p_instance_ctrl->socket_byteq_hdl,
                             &p_rcv[recv_index],
                             (length - recv_index),
                             pdMS_TO_TICKS(rx_timeout));
    if (incomeBytes > 0)
    {
        xReceivedBytes = incomeBytes;
        recv_index     = recv_index + incomeBytes;
        do
        {
            incomeBytes =
                xStreamBufferReceive(p_instance_ctrl->socket_byteq_hdl,
                                     &p_rcv[recv_index],
                                     (length - recv_index),
                                     pdMS_TO_TICKS(100));
            if (incomeBytes > 0)
            {
                xReceivedBytes += incomeBytes;
                recv_index      = recv_index + incomeBytes;
            }
        } while ((incomeBytes > 0) && (recv_index < length));
    }

    rm_at_transport_da16xxx_uart_giveMutex(p_instance_ctrl, mutex_flag);

    return xReceivedBytes;
}

/*******************************************************************************************************************//**
 *  UART Callback routine.
 *
 *  @param[in]  p_args              Pointer to uart callback structure.
 *
 **********************************************************************************************************************/
void rm_at_transport_da16xxx_uart_callback (uart_callback_args_t * p_args)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE; // Initialized to pdFALSE.

    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_args->p_context;
    volatile uint32_t uart_context_index = 0;
    at_transport_da16xxx_callback_args_t at_transp_da16xxx_callback_args;

#if (AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    if (NULL == p_args)
    {
        return;
    }
#endif

    if ((NULL != p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_SECOND_PORT]) &&
        (p_args->channel ==
         p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_SECOND_PORT]->p_cfg->channel))
    {
        uart_context_index = 1;
    }

    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
            uint8_t data_byte = (uint8_t) p_args->data;
            at_transp_da16xxx_callback_args.data  = data_byte;
            at_transp_da16xxx_callback_args.event = AT_TRANSPORT_RX_BYTE_EVENT;
            if (uart_context_index == AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT)
            {
                if (NULL != p_instance_ctrl->p_callback)
                {
                    /* Call callback function */
                    if (0 == p_instance_ctrl->p_callback(&at_transp_da16xxx_callback_args))
                    {
                        xStreamBufferSendFromISR(p_instance_ctrl->socket_byteq_hdl,
                                                 &data_byte,
                                                 1,
                                                 &xHigherPriorityTaskWoken);
                    }
                }
                else
                {
                    xStreamBufferSendFromISR(p_instance_ctrl->socket_byteq_hdl, &data_byte, 1,
                                             &xHigherPriorityTaskWoken);
                }
            }
            else if (uart_context_index == AT_TRANSPORT_DA16XXX_UART_SECOND_PORT)
            {
                xStreamBufferSendFromISR(p_instance_ctrl->socket_byteq_hdl, &data_byte, 1, &xHigherPriorityTaskWoken);
            }
            else
            {
                /* Do Nothing */
            }

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            break;
        }

        case UART_EVENT_TX_DATA_EMPTY:
        {
            if ((0 == uxQueueMessagesWaitingFromISR((QueueHandle_t) p_instance_ctrl->uart_tei_sem[uart_context_index])))
            {
                xSemaphoreGiveFromISR(p_instance_ctrl->uart_tei_sem[uart_context_index], &xHigherPriorityTaskWoken);
            }

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
 *  Send and receive an AT command with testing for return. Thread-Safe
 *
 * @param[in]  p_ctrl               Pointer to Transport layer instance control structure.
 * @param[in]  p_at_cmd              Pointer to Transport layer instance data structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
fsp_err_t rm_at_transport_da16xxx_uart_atCommandSend (at_transport_da16xxx_ctrl_t * const p_ctrl,
                                                      at_transport_da16xxx_data_t       * p_at_cmd)
{
    fsp_err_t        err         = FSP_SUCCESS;
    volatile uint8_t retry_count = 0U;
    char           * ret         = NULL;
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;
#if (AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_at_cmd);
    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    xStreamBufferReset(p_instance_ctrl->socket_byteq_hdl);
    memset(p_at_cmd->p_response_buffer, 0, p_at_cmd->response_buffer_size);

    if (p_at_cmd->p_at_cmd_string != NULL)
    {
        if (uxQueueMessagesWaiting((QueueHandle_t) p_instance_ctrl->uart_tei_sem[p_at_cmd->comm_ch_id]) != 0)
        {
            return FSP_ERR_WIFI_FAILED;
        }

        if (0 == p_at_cmd->at_cmd_string_length)
        {
            err =
                p_instance_ctrl->uart_instance_objects[p_at_cmd->comm_ch_id]->p_api->write(p_instance_ctrl->uart_instance_objects[
                                                                                               p_at_cmd->comm_ch_id]->p_ctrl,
                                                                                           p_at_cmd->p_at_cmd_string,
                                                                                           strlen((char *) p_at_cmd->
                                                                                                  p_at_cmd_string));
        }
        else
        {
            err =
                p_instance_ctrl->uart_instance_objects[p_at_cmd->comm_ch_id]->p_api->write(p_instance_ctrl->uart_instance_objects[
                                                                                               p_at_cmd->comm_ch_id]->p_ctrl,
                                                                                           p_at_cmd->p_at_cmd_string,
                                                                                           p_at_cmd->at_cmd_string_length);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        FSP_ERROR_RETURN(pdTRUE ==
                         xSemaphoreTake(p_instance_ctrl->uart_tei_sem[p_at_cmd->comm_ch_id],
                                        (p_at_cmd->timeout_ms / portTICK_PERIOD_MS)),
                         FSP_ERR_WIFI_FAILED);
    }

    if (NULL != p_at_cmd->p_expect_code)
    {
        uint8_t * p_rcv      = (p_at_cmd->p_response_buffer);
        uint32_t  recv_index = 0;
        xStreamBufferSetTriggerLevel(p_instance_ctrl->socket_byteq_hdl, 1);
        for (retry_count = 0; retry_count < AT_TRANSPORT_DA16XXX_CFG_MAX_RETRIES_UART_COMMS; retry_count++)
        {
            size_t xReceivedBytes =
                xStreamBufferReceive(p_instance_ctrl->socket_byteq_hdl, &p_rcv[recv_index],
                                     (p_at_cmd->response_buffer_size - recv_index),
                                     pdMS_TO_TICKS(p_at_cmd->timeout_ms));
            if (xReceivedBytes > 0)
            {
                recv_index = recv_index + xReceivedBytes;
                do
                {
                    xReceivedBytes =
                        xStreamBufferReceive(p_instance_ctrl->socket_byteq_hdl, &p_rcv[recv_index],
                                             (p_at_cmd->response_buffer_size - recv_index), pdMS_TO_TICKS(10));
                    if (xReceivedBytes > 0)
                    {
                        recv_index = recv_index + xReceivedBytes;
                    }
                } while ((xReceivedBytes > 0) && (recv_index < p_at_cmd->response_buffer_size));
            }

            ret = strstr((char *) p_at_cmd->p_response_buffer, p_at_cmd->p_expect_code);
            if (ret != NULL)
            {
                break;
            }
        }
    }

    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_CFG_MAX_RETRIES_UART_COMMS != (retry_count), FSP_ERR_WIFI_FAILED);
    if (ret == NULL)
    {
        if (p_at_cmd->p_response_buffer[0] != 0)
        {
            err = rm_at_transport_da16xxx_error_lookup((char *) p_at_cmd->p_response_buffer);
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 *  Give the mutex for the send basic call.
 *
 *  @param[in]  p_ctrl               Pointer to Transport layer instance control structure.
 *  @param[in] mutex_flag           Flags for the mutex.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred giving the mutex.
 **********************************************************************************************************************/
fsp_err_t rm_at_transport_da16xxx_uart_giveMutex (at_transport_da16xxx_ctrl_t * const p_ctrl, uint32_t mutex_flag)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;
    BaseType_t volatile xSemRet = pdFALSE;
    fsp_err_t           err     = FSP_SUCCESS;

#if (AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (0 != (mutex_flag & AT_TRANSPORT_DA16XXX_MUTEX_RX))
    {
        xSemRet = xSemaphoreGive(p_instance_ctrl->rx_sem);
        if (xSemRet != pdTRUE)
        {
            return FSP_ERR_WIFI_FAILED;
        }
    }

    if (0 != (mutex_flag & AT_TRANSPORT_DA16XXX_MUTEX_TX))
    {
        xSemRet = xSemaphoreGive(p_instance_ctrl->tx_sem);
        if (xSemRet != pdTRUE)
        {
            return FSP_ERR_WIFI_FAILED;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 *  Take the mutex for the send basic call.
 *
 *  @param[in]  p_ctrl               Pointer to Transport layer instance control structure.
 *  @param[in] mutex_flag           Flags for the mutex.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred taking the mutex.
 **********************************************************************************************************************/
fsp_err_t rm_at_transport_da16xxx_uart_takeMutex (at_transport_da16xxx_ctrl_t * const p_ctrl, uint32_t mutex_flag)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;
    BaseType_t volatile xSemRet = pdFALSE;
    fsp_err_t           err     = FSP_SUCCESS;

#if (AT_TRANSPORT_DA16XXX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(AT_TRANSPORT_DA16XXX_UART_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (0 != (mutex_flag & AT_TRANSPORT_DA16XXX_MUTEX_TX))
    {
        if (NULL != p_instance_ctrl->tx_sem)
        {
            xSemRet =
                xSemaphoreTake(p_instance_ctrl->tx_sem, (wifi_sx_wifi_da16xxx_sem_block_timeout / portTICK_PERIOD_MS));
            if (xSemRet != pdTRUE)
            {
                return FSP_ERR_WIFI_FAILED;
            }
        }
    }

    if (0 != (mutex_flag & AT_TRANSPORT_DA16XXX_MUTEX_RX))
    {
        if (NULL != p_instance_ctrl->rx_sem)
        {
            xSemRet =
                xSemaphoreTake(p_instance_ctrl->rx_sem, (wifi_sx_wifi_da16xxx_sem_block_timeout / portTICK_PERIOD_MS));
            if (xSemRet != pdTRUE)
            {
                if (0 != (mutex_flag & AT_TRANSPORT_DA16XXX_MUTEX_TX))
                {
                    xSemaphoreGive(p_instance_ctrl->tx_sem);
                }

                return FSP_ERR_WIFI_FAILED;
            }
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 *  Parse the incoming DA16XXX error code and translates into FSP error.
 *
 *  @param[in]  p_ctrl               Pointer to Transport layer instance control structure.
 *
 **********************************************************************************************************************/
static void rm_at_transport_da16xxx_cleanup_open (at_transport_da16xxx_ctrl_t * const p_ctrl)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;

    /* Delete the semaphores */
    if (NULL != p_instance_ctrl->tx_sem)
    {
        vSemaphoreDelete(p_instance_ctrl->tx_sem);
        p_instance_ctrl->tx_sem = NULL;
    }

    if (NULL != p_instance_ctrl->rx_sem)
    {
        vSemaphoreDelete(p_instance_ctrl->rx_sem);
        p_instance_ctrl->rx_sem = NULL;
    }

    /* Delete the command channel stream buffer */
    if (NULL != p_instance_ctrl->socket_byteq_hdl)
    {
        vStreamBufferDelete(p_instance_ctrl->socket_byteq_hdl);
        p_instance_ctrl->socket_byteq_hdl = NULL;
    }

    if (NULL != p_instance_ctrl->uart_tei_sem[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT])
    {
        vSemaphoreDelete(p_instance_ctrl->uart_tei_sem[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT]);
        p_instance_ctrl->uart_tei_sem[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT] = NULL;
    }

    uart_instance_t * p_uart = p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_INITIAL_PORT];
    if (SCIU_OPEN == ((rm_at_transport_da16xxx_uart_instance_ctrl_t *) p_uart->p_ctrl)->open)
    {
        p_uart->p_api->close(p_uart->p_ctrl);
    }

    if (p_instance_ctrl->num_uarts > 1)
    {
        if (NULL != p_instance_ctrl->uart_tei_sem[AT_TRANSPORT_DA16XXX_UART_SECOND_PORT])
        {
            vSemaphoreDelete(p_instance_ctrl->uart_tei_sem[AT_TRANSPORT_DA16XXX_UART_SECOND_PORT]);
            p_instance_ctrl->uart_tei_sem[AT_TRANSPORT_DA16XXX_UART_SECOND_PORT] = NULL;
        }

        p_uart = p_instance_ctrl->uart_instance_objects[AT_TRANSPORT_DA16XXX_UART_SECOND_PORT];
        if (SCIU_OPEN == ((rm_at_transport_da16xxx_uart_instance_ctrl_t *) p_uart->p_ctrl)->open)
        {
            p_uart->p_api->close(p_uart->p_ctrl);
        }
    }
}

/*******************************************************************************************************************//**
 *  Parse the incoming DA16XXX error code and translates into FSP error.
 *
 * @param[in]  p_resp                        Pointer to response string.
 *
 * @retval FSP_ERR_WIFI_UNKNOWN_AT_CMD       DA16XXX Unknown AT command Error.
 * @retval FSP_ERR_WIFI_INSUF_PARAM          DA16XXX Insufficient parameter.
 * @retval FSP_ERR_WIFI_TOO_MANY_PARAMS      DA16XXX Too many parameters.
 * @retval FSP_ERR_WIFI_INV_PARAM_VAL        DA16XXX Wrong parameter value.
 * @retval FSP_ERR_UNSUPPORTED               Selected mode not supported by this API.
 * @retval FSP_ERR_WIFI_AP_NOT_CONNECTED     DA16XXX Not connected to an AP or Communication peer.
 * @retval FSP_ERR_WIFI_NO_RESULT            DA16XXX No result.
 * @retval FSP_ERR_WIFI_RSP_BUF_OVFLW        DA16XXX Response buffer overflow.
 * @retval FSP_ERR_WIFI_FUNC_NOT_CONFIG      DA16XXX Function is not configured.
 * @retval FSP_ERR_TIMEOUT                   Timeout error
 * @retval FSP_ERR_WIFI_NVRAM_WR_FAIL        DA16XXX NVRAM write failure
 * @retval FSP_ERR_WIFI_RET_MEM_WR_FAIL      DA16XXX Retention memory write failure
 * @retval FSP_ERR_WIFI_UNKNOWN_ERR          DA16XXX unknown error
 * @retval FSP_ERR_INVALID_DATA              Accuracy of data is not guaranteed
 * @retval FSP_ERR_INTERNAL                  Internal error
 **********************************************************************************************************************/
static fsp_err_t rm_at_transport_da16xxx_error_lookup (char * p_resp)
{
    int8_t    err_code;
    int32_t   scanf_ret;
    fsp_err_t err = FSP_ERR_INTERNAL;

    // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
    scanf_ret = sscanf(p_resp, "\r\nERROR:%d\r\n", (int *) &err_code);
    if (1 != scanf_ret)
    {
        return FSP_ERR_INVALID_DATA;
    }

    switch (err_code)
    {
        case AT_TRANSPORT_DA16XXX_ERR_UNKNOWN_CMD:
        {
            err = FSP_ERR_WIFI_UNKNOWN_AT_CMD;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_INSUF_PARAMS:
        {
            err = FSP_ERR_WIFI_INSUF_PARAM;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_TOO_MANY_PARAMS:
        {
            err = FSP_ERR_WIFI_TOO_MANY_PARAMS;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_INVALID_PARAM:
        {
            err = FSP_ERR_WIFI_INV_PARAM_VAL;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_UNSUPPORTED_FUN:
        {
            err = FSP_ERR_UNSUPPORTED;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_NOT_CONNECTED_AP:
        {
            err = FSP_ERR_WIFI_AP_NOT_CONNECTED;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_NO_RESULT:
        {
            err = FSP_ERR_WIFI_NO_RESULT;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_RESP_BUF_OVERFLOW:
        {
            err = FSP_ERR_WIFI_RSP_BUF_OVFLW;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_FUNC_NOT_CONFIG:
        {
            err = FSP_ERR_WIFI_FUNC_NOT_CONFIG;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_CMD_TIMEOUT:
        {
            err = FSP_ERR_TIMEOUT;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_NVRAM_WR_FAIL:
        {
            err = FSP_ERR_WIFI_NVRAM_WR_FAIL;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_RETEN_MEM_WR_FAIL:
        {
            err = FSP_ERR_WIFI_RET_MEM_WR_FAIL;
            break;
        }

        case AT_TRANSPORT_DA16XXX_ERR_UNKNOWN:
        {
            err = FSP_ERR_WIFI_UNKNOWN_ERR;
            break;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 *  Resets the DA16XXX module.
 *
 *  @param[in]  p_ctrl              Pointer to DA16XXX instance structure.
 *
 **********************************************************************************************************************/
static void rm_at_transport_da16xxx_reset (at_transport_da16xxx_ctrl_t * const p_ctrl)
{
    at_transport_da16xxx_instance_ctrl_t * p_instance_ctrl = (at_transport_da16xxx_instance_ctrl_t *) p_ctrl;
    at_transport_da16xxx_extended_cfg_t  * p_extend        =
        (at_transport_da16xxx_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Reset the wifi module */
    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, p_extend->reset_pin, BSP_IO_LEVEL_LOW);

    vTaskDelay(pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_TIMEOUT_20MS));

    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, p_extend->reset_pin, BSP_IO_LEVEL_HIGH);

    vTaskDelay(pdMS_TO_TICKS(AT_TRANSPORT_DA16XXX_TIMEOUT_1MS));
}
