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
#include "rm_wifi_onchip_da16200.h"

#if (BSP_FEATURE_SCI_VERSION == 2U)
 #include "r_sci_b_uart.h"
typedef sci_b_uart_instance_ctrl_t rm_wifi_onchip_da16200_uart_instance_ctrl_t;
typedef sci_b_uart_extended_cfg_t  rm_wifi_onchip_da16200_uart_extended_cfg_t;
typedef sci_b_baud_setting_t       rm_wifi_onchip_da16200_baud_setting_t;
 #define RM_WIFI_ONCHIP_DA16200_SCI_UART_FLOW_CONTROL_RTS                SCI_B_UART_FLOW_CONTROL_RTS
 #define RM_WIFI_ONCHIP_DA16200_SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS    SCI_B_UART_FLOW_CONTROL_HARDWARE_CTSRTS
static fsp_err_t (* p_sci_uart_baud_calculate)(uint32_t, bool, uint32_t,
                                               struct st_sci_b_baud_setting_t * const) = &R_SCI_B_UART_BaudCalculate;
#else
 #include "r_sci_uart.h"
typedef sci_uart_instance_ctrl_t rm_wifi_onchip_da16200_uart_instance_ctrl_t;
typedef sci_uart_extended_cfg_t  rm_wifi_onchip_da16200_uart_extended_cfg_t;
typedef baud_setting_t           rm_wifi_onchip_da16200_baud_setting_t;
 #define RM_WIFI_ONCHIP_DA16200_SCI_UART_FLOW_CONTROL_RTS                SCI_UART_FLOW_CONTROL_RTS
 #define RM_WIFI_ONCHIP_DA16200_SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS    SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS
static fsp_err_t (* p_sci_uart_baud_calculate)(uint32_t, bool, uint32_t,
                                               baud_setting_t * const) = &R_SCI_UART_BaudCalculate;
#endif

/*! \cond PRIVATE */

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/
#define WIFI_ONCHIP_DA16200_TEMP_BUFFER_SIZE          (256)

/* Text full versions of AT command returns */
#define WIFI_ONCHIP_DA16200_RETURN_TEXT_OK            "OK"
#define WIFI_ONCHIP_DA16200_RETURN_CONN_TEXT          "+WFJAP:1"

/* DA16200 UART port defines */
#define WIFI_ONCHIP_DA16200_UART_INITIAL_PORT         (0)
#define WIFI_ONCHIP_DA16200_UART_SECOND_PORT          (1)

/* Initial DA16200 Wifi module UART settings */
#define WIFI_ONCHIP_DA16200_DEFAULT_BAUDRATE          (115200)
#define WIFI_ONCHIP_DA16200_DEFAULT_MODULATION        false
#define WIFI_ONCHIP_DA16200_DEFAULT_ERROR             (9000)

/* Pin or port invalid definition */
#define WIFI_ONCHIP_DA16200_BSP_PIN_PORT_INVALID      (UINT16_MAX)

#define WIFI_ONCHIP_DA16200_TEMP_BUFF_SIZE            (30)

/* Mutex give/take defines */
#define WIFI_ONCHIP_DA16200_MUTEX_TX                  (1 << 0)
#define WIFI_ONCHIP_DA16200_MUTEX_RX                  (1 << 1)

/* Predefined timeout values */
#define WIFI_ONCHIP_DA16200_TIMEOUT_1MS               (1)
#define WIFI_ONCHIP_DA16200_TIMEOUT_3MS               (3)
#define WIFI_ONCHIP_DA16200_TIMEOUT_5MS               (5)
#define WIFI_ONCHIP_DA16200_TIMEOUT_10MS              (10)
#define WIFI_ONCHIP_DA16200_TIMEOUT_20MS              (20)
#define WIFI_ONCHIP_DA16200_TIMEOUT_30MS              (30)
#define WIFI_ONCHIP_DA16200_TIMEOUT_100MS             (100)
#define WIFI_ONCHIP_DA16200_TIMEOUT_200MS             (200)
#define WIFI_ONCHIP_DA16200_TIMEOUT_300MS             (300)
#define WIFI_ONCHIP_DA16200_TIMEOUT_400MS             (400)
#define WIFI_ONCHIP_DA16200_TIMEOUT_500MS             (500)
#define WIFI_ONCHIP_DA16200_TIMEOUT_1SEC              (1000)
#define WIFI_ONCHIP_DA16200_TIMEOUT_2SEC              (2000)
#define WIFI_ONCHIP_DA16200_TIMEOUT_3SEC              (3000)
#define WIFI_ONCHIP_DA16200_TIMEOUT_4SEC              (4000)
#define WIFI_ONCHIP_DA16200_TIMEOUT_5SEC              (5000)
#define WIFI_ONCHIP_DA16200_TIMEOUT_8SEC              (8000)
#define WIFI_ONCHIP_DA16200_TIMEOUT_15SEC             (15000)
#define WIFI_ONCHIP_DA16200_TIMEOUT_20SEC             (20000)

/* DA16200 AT command retry delay in milliseconds */
#define WIFI_ONCHIP_DA16200_DELAY_20MS                (20)
#define WIFI_ONCHIP_DA16200_DELAY_50MS                (50)
#define WIFI_ONCHIP_DA16200_DELAY_100MS               (100)
#define WIFI_ONCHIP_DA16200_DELAY_200MS               (200)
#define WIFI_ONCHIP_DA16200_DELAY_300MS               (300)
#define WIFI_ONCHIP_DA16200_DELAY_500MS               (500)
#define WIFI_ONCHIP_DA16200_DELAY_1000MS              (1000)
#define WIFI_ONCHIP_DA16200_DELAY_2000MS              (2000)
#define WIFI_ONCHIP_DA16200_DELAY_5000MS              (5000)
#define WIFI_ONCHIP_DA16200_DELAY_8000MS              (8000)
#define WIFI_ONCHIP_DA16200_DELAY_15SEC               (15000)

/* Minimum string size for getting local time string */
#define WIFI_ONCHIP_DA16200_LOCAL_TIME_STR_SIZE       (25)

#define HOURS_IN_SECONDS                              (3600)

/* Socket Types supported */
#define WIFI_ONCHIP_DA16200_SOCKET_TYPE_TCP_SERVER    (0)
#define WIFI_ONCHIP_DA16200_SOCKET_TYPE_TCP_CLIENT    (1)
#define WIFI_ONCHIP_DA16200_SOCKET_TYPE_UDP           (2)
#define WIFI_ONCHIP_DA16200_SOCKET_TYPE_MAX           (3)

/* Error Response Codes */
#define WIFI_ONCHIP_DA16200_ERR_UNKNOWN_CMD           (-1)
#define WIFI_ONCHIP_DA16200_ERR_INSUF_PARAMS          (-2)
#define WIFI_ONCHIP_DA16200_ERR_TOO_MANY_PARAMS       (-3)
#define WIFI_ONCHIP_DA16200_ERR_INVALID_PARAM         (-4)
#define WIFI_ONCHIP_DA16200_ERR_UNSUPPORTED_FUN       (-5)
#define WIFI_ONCHIP_DA16200_ERR_NOT_CONNECTED_AP      (-6)
#define WIFI_ONCHIP_DA16200_ERR_NO_RESULT             (-7)
#define WIFI_ONCHIP_DA16200_ERR_RESP_BUF_OVERFLOW     (-8)
#define WIFI_ONCHIP_DA16200_ERR_FUNC_NOT_CONFIG       (-9)
#define WIFI_ONCHIP_DA16200_ERR_CMD_TIMEOUT           (-10)
#define WIFI_ONCHIP_DA16200_ERR_NVRAM_WR_FAIL         (-11)
#define WIFI_ONCHIP_DA16200_ERR_RETEN_MEM_WR_FAIL     (-12)
#define WIFI_ONCHIP_DA16200_ERR_UNKNOWN               (-99)

#define sbFLAGS_IS_MESSAGE_BUFFER                     ((uint8_t) 1)   /* Set if the stream buffer was created as a message buffer, in which case it holds discrete messages rather than a stream. */
#define sbBYTES_TO_STORE_MESSAGE_LENGTH               (sizeof(configMESSAGE_BUFFER_LENGTH_TYPE))

/* Unique number for WIFI Open status */
#define WIFI_OPEN                                     (0x57495749ULL) // Is "WIFI" in ASCII

/* Unique number for SCI Open Status */
#if (BSP_FEATURE_SCI_VERSION == 2U)
 #define SCIU_OPEN                                    (0x53434942U)   // Is "SCIB" in ASCII
#else
 #define SCIU_OPEN                                    (0x53434955U)   // Is "SCIU" in ASCII
#endif

#define UART_BAUD_MAX_CNT                             (4)

/* UART Baud rates */
#define UART_BAUD_115200                              (115200)
#define UART_BAUD_230400                              (230400)
#define UART_BAUD_460800                              (460800)
#define UART_BAUD_921600                              (921600)

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/
extern const ioport_instance_t g_ioport;

/***********************************************************************************************************************
 * Enumerations
 **********************************************************************************************************************/

/* Numeric return types for AT basic function commands */
typedef enum
{
    WIFI_ONCHIP_DA16200_RETURN_OK = 0,       ///< WIFI_ONCHIP_DA16200_RETURN_OK
    WIFI_ONCHIP_DA16200_RETURN_INIT_OK,      ///< WIFI_ONCHIP_DA16200_RETURN_INIT_OK
    WIFI_ONCHIP_DA16200_RETURN_CONNECT,      ///< WIFI_ONCHIP_DA16200_RETURN_CONNECT
    WIFI_ONCHIP_DA16200_RETURN_CONNECT_FAIL, ///< WIFI_ONCHIP_DA16200_RETURN_CONNECT_FAIL
    WIFI_ONCHIP_DA16200_RETURN_ERROR_CODES,
    WIFI_ONCHIP_DA16200_RETURN_PROVISION_IDLE,
    WIFI_ONCHIP_DA16200_RETURN_PROVISION_START
} da16200_return_code_t;

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/
static rm_wifi_onchip_da16200_baud_setting_t g_baud_setting =
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

/* Control instance for the da16200 wifi module */
static wifi_onchip_da16200_instance_ctrl_t g_rm_wifi_onchip_da16200_instance;

/* Transmit and receive mutexes for UARTs */
static StaticSemaphore_t g_socket_mutexes[2];
static StaticSemaphore_t g_uart_tei_mutex[2];

/**
 *  Maximum time in ticks to wait for obtaining a semaphore.
 */
static const TickType_t wifi_sx_wifi_onchip_da16200_sem_block_timeout = pdMS_TO_TICKS(
    WIFI_ONCHIP_DA16200_CFG_SEM_MAX_TIMEOUT);

static uint8_t rx_buffer[WIFI_ONCHIP_DA16200_TEMP_BUFFER_SIZE] = {0};
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
 #define sbRECEIVE_COMPLETED(pxStreamBuffer)                                                   \
    vTaskSuspendAll();                                                                         \
    {                                                                                          \
        if ((pxStreamBuffer)->xTaskWaitingToSend != NULL)                                      \
        {                                                                                      \
            (void) xTaskNotify((pxStreamBuffer)->xTaskWaitingToSend, (uint32_t) 0, eNoAction); \
            (pxStreamBuffer)->xTaskWaitingToSend = NULL;                                       \
        }                                                                                      \
    }                                                                                          \
    (void) xTaskResumeAll();
#endif                                 /* sbRECEIVE_COMPLETED */

/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/
static void      rm_wifi_onchip_da16200_cleanup_open(wifi_onchip_da16200_instance_ctrl_t * const p_instance_ctrl);
static void      rm_wifi_onchip_da16200_wifi_module_reset(wifi_onchip_da16200_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t rm_wifi_onchip_da16200_error_lookup(char * resp);
static fsp_err_t rm_wifi_onchip_da16200_send_basic(wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl,
                                                   uint32_t                              serial_ch_id,
                                                   const char                          * p_textstring,
                                                   uint32_t                              length,
                                                   uint32_t                              timeout_ms,
                                                   uint32_t                              retry_delay,
                                                   const char                          * p_expect_code);

static BaseType_t rm_wifi_onchip_da16200_send_basic_take_mutex(wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl,
                                                               uint32_t                              mutex_flag);
static BaseType_t rm_wifi_onchip_da16200_send_basic_give_mutex(wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl,
                                                               uint32_t                              mutex_flag);

static void rm_wifi_da16200_handle_incoming_socket_data(da16200_socket_t * pSocket, uint8_t data_byte);

static size_t xStreamBufferReceiveAlt(StreamBufferHandle_t xStreamBuffer,
                                      void               * pvRxData,
                                      size_t               xBufferLengthBytes,
                                      TickType_t           xTicksToWait);

#if (1 == WIFI_ONCHIP_DA16200_CFG_SNTP_ENABLE)
static fsp_err_t rm_wifi_onchip_da16200_sntp_service_init(wifi_onchip_da16200_instance_ctrl_t * const p_instance_ctrl);

#endif

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Opens and configures the WIFI_ONCHIP_DA16200 Middleware module.
 *
 *  @param[in]  p_cfg        Pointer to pin configuration structure.
 *
 *  @retval FSP_SUCCESS              WIFI_ONCHIP_DA16200 successfully configured.
 *  @retval FSP_ERR_ASSERTION        The parameter p_cfg or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_OUT_OF_MEMORY    There is no more heap memory available.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 *  @retval FSP_ERR_WIFI_INIT_FAILED WiFi module initialization failed.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_da16200_open (wifi_onchip_da16200_cfg_t const * const p_cfg)
{
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;
    fsp_err_t         err    = FSP_SUCCESS;
    uart_instance_t * p_uart = NULL;
    rm_wifi_onchip_da16200_uart_extended_cfg_t uart0_cfg_extended;
    uart_cfg_t uart0_cfg;
    uint8_t    temp_buff[WIFI_ONCHIP_DA16200_TEMP_BUFF_SIZE] = {0};
    uint8_t  * p_temp_buff = temp_buff;
    uint32_t   uart_baud_rates[UART_BAUD_MAX_CNT] =
    {
        UART_BAUD_115200, UART_BAUD_230400, UART_BAUD_460800, UART_BAUD_921600
    };
    uint32_t curr_uart_baud = 0;
    int      index          = 0;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(WIFI_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Clear the control structure */
    memset(p_instance_ctrl, 0, sizeof(wifi_onchip_da16200_instance_ctrl_t));

    /* Update control structure from configuration values */
    p_instance_ctrl->p_wifi_onchip_da16200_cfg = p_cfg;
    p_instance_ctrl->num_uarts                 = p_cfg->num_uarts;

    for (uint32_t i = 0; i < p_instance_ctrl->num_uarts; i++)
    {
        p_instance_ctrl->uart_instance_objects[i] = (uart_instance_t *) p_cfg->uart_instances[i];

        p_instance_ctrl->uart_tei_sem[i] = xSemaphoreCreateBinaryStatic(&g_uart_tei_mutex[i]);
        if (NULL == p_instance_ctrl->uart_tei_sem[i])
        {
            rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(NULL != p_instance_ctrl->uart_tei_sem[i], FSP_ERR_OUT_OF_MEMORY);

        xSemaphoreTake(p_instance_ctrl->uart_tei_sem[i], 0);
    }

    p_instance_ctrl->reset_pin             = p_cfg->reset_pin;
    p_instance_ctrl->num_creatable_sockets = p_cfg->num_sockets;
    p_instance_ctrl->curr_cmd_port         = WIFI_ONCHIP_DA16200_UART_INITIAL_PORT;

    /* Reset the wi-fi module to a known state */
    rm_wifi_onchip_da16200_wifi_module_reset(p_instance_ctrl);

    /* Create the Tx/Rx mutexes */
    if (p_instance_ctrl->tx_sem != NULL)
    {
        vSemaphoreDelete(p_instance_ctrl->tx_sem);
    }

    p_instance_ctrl->tx_sem = xSemaphoreCreateMutexStatic(&g_socket_mutexes[0]);
    if (NULL == p_instance_ctrl->tx_sem)
    {
        rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->tx_sem, FSP_ERR_OUT_OF_MEMORY);

    if (p_instance_ctrl->rx_sem != NULL)
    {
        vSemaphoreDelete(p_instance_ctrl->rx_sem);
    }

    p_instance_ctrl->rx_sem = xSemaphoreCreateMutexStatic(&g_socket_mutexes[1]);
    if (NULL == p_instance_ctrl->rx_sem)
    {
        rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->rx_sem, FSP_ERR_OUT_OF_MEMORY);

    /* Create the stream buffer used to transfer UART data from ISR */
    p_instance_ctrl->socket_byteq_hdl = xStreamBufferCreateStatic(sizeof(p_instance_ctrl->cmd_rx_queue_buf),
                                                                  1,
                                                                  p_instance_ctrl->cmd_rx_queue_buf,
                                                                  &p_instance_ctrl->socket_byteq_struct);
    if (NULL == p_instance_ctrl->socket_byteq_hdl)
    {
        rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->socket_byteq_hdl, FSP_ERR_OUT_OF_MEMORY);

    /* Create memory copy of uart extended configuration and then copy new configuration values in. */
    memcpy((void *) &uart0_cfg_extended, (void *) p_instance_ctrl->uart_instance_objects[0]->p_cfg->p_extend,
           sizeof(rm_wifi_onchip_da16200_uart_extended_cfg_t));

    /* Create memory copy of uart configuration and update with new extended configuration structure. */
    memcpy((void *) &uart0_cfg, p_instance_ctrl->uart_instance_objects[0]->p_cfg, sizeof(uart_cfg_t));

    for (index = 0; index < UART_BAUD_MAX_CNT; index++)
    {
        curr_uart_baud = uart_baud_rates[index];

        (*p_sci_uart_baud_calculate)(curr_uart_baud, WIFI_ONCHIP_DA16200_DEFAULT_MODULATION,
                                     WIFI_ONCHIP_DA16200_DEFAULT_ERROR, &g_baud_setting);

        uart0_cfg_extended.p_baud_setting   = &g_baud_setting;
        uart0_cfg_extended.flow_control     = RM_WIFI_ONCHIP_DA16200_SCI_UART_FLOW_CONTROL_RTS;
        uart0_cfg_extended.flow_control_pin = (bsp_io_port_pin_t) WIFI_ONCHIP_DA16200_BSP_PIN_PORT_INVALID;

        uart0_cfg.p_extend   = (void *) &uart0_cfg_extended;
        uart0_cfg.p_callback = rm_wifi_onchip_da16200_uart_callback;

        /* Open UART */
        p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT];
        err    = p_uart->p_api->open(p_uart->p_ctrl, &uart0_cfg);

        if (FSP_SUCCESS != err)
        {
            rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

        /* Delay after open */
        vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_10MS));

        /* Test basic communications with an AT command. */
        err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                p_instance_ctrl->curr_cmd_port,
                                                "ATZ\r",
                                                0,
                                                WIFI_ONCHIP_DA16200_TIMEOUT_20MS,
                                                WIFI_ONCHIP_DA16200_DELAY_20MS,
                                                WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);
        if (FSP_SUCCESS != err)
        {
            vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_10MS));

            /* Test basic communications with an AT command. */
            err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                    p_instance_ctrl->curr_cmd_port,
                                                    "ATZ\r",
                                                    0,
                                                    WIFI_ONCHIP_DA16200_TIMEOUT_20MS,
                                                    WIFI_ONCHIP_DA16200_DELAY_20MS,
                                                    WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);
            if (FSP_SUCCESS != err)
            {
                /* Close the UART port */
                err = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT]->p_api->close(
                    p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT]->p_ctrl);

                if (FSP_SUCCESS != err)
                {
                    rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
                    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
                }

                /* Delay after close */
                vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_10MS));
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

    FSP_ERROR_RETURN(UART_BAUD_MAX_CNT != (index), FSP_ERR_WIFI_FAILED);

    /* Update the module baud rate in case if it doesn't match with user configured baud rate */
    if (curr_uart_baud != (uint32_t) strtol((char *) g_wifi_onchip_da16200_uart_cmd_baud, NULL, 10))
    {
        strncpy((char *) p_temp_buff, "ATB=", 5);
        strncat((char *) p_temp_buff, g_wifi_onchip_da16200_uart_cmd_baud, 10);
        strncat((char *) p_temp_buff, "\r", 3);

        /* Send UART Baud rate reconfiguration AT command to wifi module */
        err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                p_instance_ctrl->curr_cmd_port,
                                                (char *) p_temp_buff,
                                                0,
                                                WIFI_ONCHIP_DA16200_TIMEOUT_20MS,
                                                WIFI_ONCHIP_DA16200_DELAY_20MS,
                                                WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);
        if (FSP_SUCCESS != err)
        {
            rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
    }

    /* Close the UART port */
    err = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT]->p_api->close(
        p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT]->p_ctrl);

    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
    }

    /* Delay after close */
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_10MS));

    /* Open uart port with config values from the configurator */
    p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT];
    err    = p_uart->p_api->open(p_uart->p_ctrl, p_uart->p_cfg);
    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

    /* Delay after open */
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_100MS));

    /* Test basic communications with an AT command. */
    err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "ATZ\r",
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_500MS,
                                            WIFI_ONCHIP_DA16200_DELAY_20MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

    /* Set AP mode */
    err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "AT+WFMODE=0\r",
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_500MS,
                                            WIFI_ONCHIP_DA16200_DELAY_20MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

    /* Set Country Code */
    snprintf((char *) p_instance_ctrl->cmd_tx_buff,
             sizeof(p_instance_ctrl->cmd_tx_buff),
             "AT+WFCC=%s\r",
             p_cfg->country_code);

    err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            (char *) p_instance_ctrl->cmd_tx_buff,
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_500MS,
                                            WIFI_ONCHIP_DA16200_DELAY_20MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);

#if (1 == WIFI_ONCHIP_DA16200_CFG_SNTP_ENABLE)
    p_instance_ctrl->open = WIFI_OPEN; // Allows interface calls to complete for SNTP init.
    err = rm_wifi_onchip_da16200_sntp_service_init(p_instance_ctrl);
    p_instance_ctrl->open = 0;
    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);
    }
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_INIT_FAILED);
#endif

    p_instance_ctrl->curr_socket_index = 0;
    p_instance_ctrl->open              = WIFI_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Disables WIFI_ONCHIP_DA16200.
 *
 *  @retval FSP_SUCCESS              WIFI_ONCHIP_DA16200 closed successfully.
 *  @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_da16200_close (void)
{
    uint32_t  mutex_flag;
    fsp_err_t err = FSP_SUCCESS;
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    /* Tell wifi module to disconnect from the current AP */
    err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "AT+WFQAP\r",
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_20MS,
                                            WIFI_ONCHIP_DA16200_DELAY_50MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    p_instance_ctrl->open = 0;

    rm_wifi_onchip_da16200_cleanup_open(p_instance_ctrl);

    return err;
}

/*******************************************************************************************************************//**
 *  Disconnects from connected AP.
 *
 *  @retval FSP_SUCCESS              WIFI_ONCHIP_DA16200 disconnected successfully.
 *  @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_da16200_disconnect (void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    /* Tell wifi module to disconnect from the current AP */
    err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "AT+WFQAP\r",
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_3SEC,
                                            WIFI_ONCHIP_DA16200_DELAY_500MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);
    if (FSP_SUCCESS == err)
    {
        memset(p_instance_ctrl->curr_ipaddr, 0, 4);
        memset(p_instance_ctrl->curr_subnetmask, 0, 4);
        memset(p_instance_ctrl->curr_gateway, 0, 4);
    }

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return err;
}

/*******************************************************************************************************************//**
 *  Check if DA16200 module is connected to an Access point.
 *
 * @param[out]  p_status                    Pointer to integer holding the socket connection status.
 *
 * @retval FSP_SUCCESS                      Function completed successfully.
 * @retval FSP_ERR_WIFI_AP_NOT_CONNECTED    WiFi module is not connected to access point.
 * @retval FSP_ERR_NOT_OPEN                 The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_da16200_connected (fsp_err_t * p_status)
{
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
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
fsp_err_t rm_wifi_onchip_da16200_network_info_get (uint32_t * p_ip_addr, uint32_t * p_subnet_mask, uint32_t * p_gateway)
{
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
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
fsp_err_t rm_wifi_onchip_da16200_connect (const char   * p_ssid,
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

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;
    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ssid);
    FSP_ASSERT(NULL != p_passphrase);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Commas are not accepted by the WiFi module in the SSID or Passphrase */
    FSP_ERROR_RETURN((NULL == strchr(p_ssid, ',') && NULL == strchr(p_passphrase, ',')), FSP_ERR_INVALID_ARGUMENT);

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    rm_wifi_onchip_da16200_connected(&status);

    if (FSP_SUCCESS == status)
    {
        /* If Wifi is already connected, do nothing and return fail. */
        rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
            case WIFI_ONCHIP_DA16200_TKIP_ENC_TYPE:
            {
                strncat((char *) p_instance_ctrl->cmd_tx_buff, "0,", 3);
                break;
            }

            case WIFI_ONCHIP_DA16200_AES_ENC_TYPE:
            {
                strncat((char *) p_instance_ctrl->cmd_tx_buff, "1,", 3);
                break;
            }

            case WIFI_ONCHIP_DA16200_TKIP_AES_ENC_TYPE:
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
        /* Return with error for unsupported secuirty types */
        rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    strncat((char *) p_instance_ctrl->cmd_tx_buff, p_passphrase, wificonfigMAX_PASSPHRASE_LEN);
    strncat((char *) p_instance_ctrl->cmd_tx_buff, "\r", 2);

    ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            (char *) p_instance_ctrl->cmd_tx_buff,
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_5SEC,
                                            WIFI_ONCHIP_DA16200_DELAY_500MS,
                                            WIFI_ONCHIP_DA16200_RETURN_CONN_TEXT);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    if (FSP_SUCCESS == ret)
    {
        /* Parse the response */
        ptr = strstr(ptr, "ERROR:");
        if (NULL != ptr)
        {
            ret = rm_wifi_onchip_da16200_error_lookup(ptr);
        }
        else
        {
            /* Parsing the response */
            rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag);

            /* Enable DHCP */
            ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                    p_instance_ctrl->curr_cmd_port,
                                                    "AT+NWDHC=1\r",
                                                    0,
                                                    WIFI_ONCHIP_DA16200_TIMEOUT_200MS,
                                                    WIFI_ONCHIP_DA16200_DELAY_500MS,
                                                    WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

            rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

            ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

            R_BSP_SoftwareDelay(WIFI_ONCHIP_DA16200_TIMEOUT_3SEC, BSP_DELAY_UNITS_MILLISECONDS);

            /* Call to get IP address does not always work the first time */
            for (int index = 0; index < WIFI_ONCHIP_DA16200_CFG_MAX_RETRIES_UART_COMMS; index++)
            {
                FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                                 FSP_ERR_WIFI_FAILED);

                /* Query the IP address from the current AP */
                ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                        p_instance_ctrl->curr_cmd_port,
                                                        "AT+NWIP=?\r",
                                                        0,
                                                        WIFI_ONCHIP_DA16200_TIMEOUT_5SEC,
                                                        WIFI_ONCHIP_DA16200_DELAY_200MS,
                                                        WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

                rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

                FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

                /* Parsing the response */
                ptr = strstr(ptr, "+NWIP:");
                if (ptr == NULL)
                {
                    R_BSP_SoftwareDelay(WIFI_ONCHIP_DA16200_TIMEOUT_3SEC, BSP_DELAY_UNITS_MILLISECONDS);
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
fsp_err_t rm_wifi_onchip_da16200_mac_addr_get (uint8_t * p_macaddr)
{
    fsp_err_t    ret;
    int32_t      err;
    unsigned int macaddr[6];
    uint32_t     mutex_flag;
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;
    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_macaddr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "AT+WFMAC=?\r",
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_400MS,
                                            WIFI_ONCHIP_DA16200_DELAY_200MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t rm_wifi_onchip_da16200_scan (WIFIScanResult_t * p_results, uint32_t maxNetworks)
{
    fsp_err_t ret = FSP_ERR_INTERNAL;
    int32_t   err;
    uint32_t  idx = 0;
    uint8_t * bssid;
    uint32_t  mutex_flag;

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_results);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

    FSP_ERROR_RETURN((NULL != p_results) && (0 != maxNetworks), FSP_ERR_INVALID_ARGUMENT);

    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "AT+WFSCAN\r",
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_8SEC,
                                            WIFI_ONCHIP_DA16200_DELAY_1000MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

    /* Parsing the response */
    ptr = strstr(ptr, "+WFSCAN:");
    FSP_ERROR_RETURN(NULL != ptr, FSP_ERR_INVALID_DATA);
    ptr = ptr + strlen("+WFSCAN:");

    do
    {
        if (((*ptr == 'O') && (*++ptr == 'K')) || (idx >= 10))
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
fsp_err_t rm_wifi_onchip_da16200_ping (uint8_t * p_ip_addr, int count, uint32_t interval_ms)
{
    FSP_PARAMETER_NOT_USED(interval_ms);
    fsp_err_t func_ret = FSP_ERR_WIFI_FAILED;
    uint32_t  mutex_flag;
    int       sent_cnt = 0;
    int       recv_cnt = 0;

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ERROR_RETURN(0 != count, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));
    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN((pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag)),
                     FSP_ERR_WIFI_FAILED);

    snprintf((char *) p_instance_ctrl->cmd_tx_buff,
             sizeof(p_instance_ctrl->cmd_tx_buff),
             "AT+NWPING=0,%d.%d.%d.%d,%d\r",
             p_ip_addr[0],
             p_ip_addr[1],
             p_ip_addr[2],
             p_ip_addr[3],
             count);

    func_ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                 p_instance_ctrl->curr_cmd_port,
                                                 (char *) p_instance_ctrl->cmd_tx_buff,
                                                 0,
                                                 WIFI_ONCHIP_DA16200_TIMEOUT_2SEC,
                                                 WIFI_ONCHIP_DA16200_DELAY_500MS,
                                                 WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t rm_wifi_onchip_da16200_ipaddr_get (uint32_t * p_ip_addr)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    int32_t   scanf_ret;
    int       index         = 0;
    int       ipaddr[4]     = {0, 0, 0, 0};
    int       subnetmask[4] = {0, 0, 0, 0};
    int       gateway[4]    = {0, 0, 0, 0};

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff);
    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);

    /* Call to get IP address does not always work the first time */
    for (index = 0; index < WIFI_ONCHIP_DA16200_CFG_MAX_RETRIES_UART_COMMS; index++)
    {
        FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                         FSP_ERR_WIFI_FAILED);

        /* Query the IP address from the current AP */
        err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                p_instance_ctrl->curr_cmd_port,
                                                "AT+NWIP=?\r",
                                                0,
                                                WIFI_ONCHIP_DA16200_TIMEOUT_5SEC,
                                                WIFI_ONCHIP_DA16200_DELAY_200MS,
                                                WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

        rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        /* Parsing the response */
        ptr = strstr(ptr, "+NWIP:");
        if (ptr == NULL)
        {
            R_BSP_SoftwareDelay(WIFI_ONCHIP_DA16200_TIMEOUT_3SEC, BSP_DELAY_UNITS_MILLISECONDS);
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

    FSP_ERROR_RETURN(WIFI_ONCHIP_DA16200_CFG_MAX_RETRIES_UART_COMMS != (index), FSP_ERR_WIFI_FAILED);

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
fsp_err_t rm_wifi_onchip_da16200_dns_query (const char * p_textstring, uint8_t * p_ip_addr)
{
    fsp_err_t func_ret;
    int32_t   scanf_ret;
    int       temp_addr[4] = {0, 0, 0, 0};
    int32_t   i            = 0;
    uint32_t  mutex_flag;

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;
    char * buff = (char *) p_instance_ctrl->cmd_rx_buff;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_textstring);
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((sizeof(p_instance_ctrl->cmd_tx_buff) - 16) > strlen(p_textstring), FSP_ERR_INVALID_ARGUMENT)
#endif

    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWHOST=", sizeof(p_instance_ctrl->cmd_tx_buff));
    snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
             sizeof(p_instance_ctrl->cmd_tx_buff), "%s\r\n", p_textstring);

    func_ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                 p_instance_ctrl->curr_cmd_port,
                                                 (char *) p_instance_ctrl->cmd_tx_buff,
                                                 0,
                                                 WIFI_ONCHIP_DA16200_TIMEOUT_8SEC,
                                                 WIFI_ONCHIP_DA16200_DELAY_1000MS,
                                                 WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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

/*******************************************************************************************************************//**
 *  Get the next available socket ID.
 *
 * @param[out]  p_socket_id    Pointer to an integer to hold the socket ID.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_socket_id is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_WIFI_FAILED      Error occured in the execution of this function
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_da16200_avail_socket_get (uint32_t * p_socket_id)
{
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
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
fsp_err_t rm_wifi_onchip_da16200_socket_status_get (uint32_t socket_no, uint32_t * p_socket_status)
{
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
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
fsp_err_t rm_wifi_onchip_da16200_socket_create (uint32_t socket_no, uint32_t type, uint32_t ipversion)
{
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(type <= WIFI_ONCHIP_DA16200_SOCKET_TYPE_MAX);
#endif

    if ((1 == p_instance_ctrl->sockets[socket_no].socket_create_flag) || (1 < p_instance_ctrl->num_creatable_sockets))
    {
        return FSP_ERR_WIFI_FAILED;
    }

    if (WIFI_ONCHIP_DA16200_SOCKET_TYPE_TCP_CLIENT == type)
    {
        p_instance_ctrl->sockets[socket_no].socket_type = WIFI_ONCHIP_DA16200_SOCKET_TYPE_TCP_CLIENT;
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
fsp_err_t rm_wifi_onchip_da16200_tcp_connect (uint32_t socket_no, uint32_t ipaddr, uint32_t port)
{
    fsp_err_t ret = FSP_SUCCESS;
    uint32_t  mutex_flag;

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    memset(p_instance_ctrl->cmd_tx_buff, 0, sizeof(p_instance_ctrl->cmd_tx_buff));
    memset(p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.strcpy) Disable warning about use of strcpy
    strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+TRTC=", sizeof(p_instance_ctrl->cmd_tx_buff));
    snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
             sizeof(p_instance_ctrl->cmd_tx_buff), "%d.%d.%d.%d,%d\r\n", (uint8_t) (ipaddr >> 24),
             (uint8_t) (ipaddr >> 16),
             (uint8_t) (ipaddr >> 8), (uint8_t) (ipaddr), (int) port);

    ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            (char *) p_instance_ctrl->cmd_tx_buff,
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_5SEC,
                                            WIFI_ONCHIP_DA16200_DELAY_500MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

    p_instance_ctrl->sockets[socket_no].remote_ipaddr[0]       = (uint8_t) (ipaddr >> 24);
    p_instance_ctrl->sockets[socket_no].remote_ipaddr[1]       = (uint8_t) (ipaddr >> 16);
    p_instance_ctrl->sockets[socket_no].remote_ipaddr[2]       = (uint8_t) (ipaddr >> 8);
    p_instance_ctrl->sockets[socket_no].remote_ipaddr[3]       = (uint8_t) (ipaddr);
    p_instance_ctrl->sockets[socket_no].remote_port            = (int) port;
    p_instance_ctrl->sockets[socket_no].socket_status          = WIFI_ONCHIP_DA16200_SOCKET_STATUS_CONNECTED;
    p_instance_ctrl->sockets[socket_no].socket_read_write_flag = WIFI_ONCHIP_DA16200_SOCKET_READ |
                                                                 WIFI_ONCHIP_DA16200_SOCKET_WRITE;
    p_instance_ctrl->sockets[socket_no].socket_recv_state  = WIFI_ONCHIP_DA16200_RECV_PREFIX;
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
int32_t rm_wifi_onchip_da16200_send (uint32_t socket_no, const uint8_t * p_data, uint32_t length, uint32_t timeout_ms)
{
    uint32_t  sent_count = 0;
    uint32_t  tx_length;
    fsp_err_t ret;
    uint32_t  mutex_flag;
    int       header_len;

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(WIFI_ONCHIP_DA16200_CFG_CMD_TX_BUF_SIZE > length, FSP_ERR_INVALID_ARGUMENT);
#endif

    /* If socket write has been disabled by shutdown call then return 0 bytes sent */
    if (!(p_instance_ctrl->sockets[socket_no].socket_read_write_flag & WIFI_ONCHIP_DA16200_SOCKET_WRITE))
    {
        return 0;
    }

    if ((0 == p_instance_ctrl->sockets[socket_no].socket_create_flag) ||
        (WIFI_ONCHIP_DA16200_SOCKET_STATUS_CONNECTED != p_instance_ctrl->sockets[socket_no].socket_status))
    {
        return FSP_ERR_WIFI_FAILED;
    }

    mutex_flag = WIFI_ONCHIP_DA16200_MUTEX_TX;
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    if (socket_no != p_instance_ctrl->curr_socket_index)
    {
        rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    memset(p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

#define DATA_IP_MODE    "\x1B"

    while (sent_count < length)
    {
        /* Put the DA16200 module into data input mode */
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

        if (length - sent_count > (uint32_t) (WIFI_ONCHIP_DA16200_CFG_CMD_TX_BUF_SIZE - header_len))
        {
            tx_length = (uint32_t) (WIFI_ONCHIP_DA16200_CFG_CMD_TX_BUF_SIZE - header_len);
        }
        else
        {
            tx_length = length - sent_count;
        }

        /* Send data through a socket */
        memcpy((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
               (char *) p_data,
               tx_length);

        ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                p_instance_ctrl->curr_cmd_port,
                                                (char *) p_instance_ctrl->cmd_tx_buff,
                                                tx_length + (uint32_t) header_len,
                                                timeout_ms,
                                                WIFI_ONCHIP_DA16200_DELAY_500MS,
                                                WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);
        if (FSP_SUCCESS != ret)
        {
            rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

        sent_count += tx_length;
        p_data      = p_data + sent_count;
    }

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
int32_t rm_wifi_onchip_da16200_recv (uint32_t socket_no, uint8_t * p_data, uint32_t length, uint32_t timeout_ms)
{
    uint32_t mutex_flag;
    uint32_t recvcnt = 0;
    int32_t  ret     = 0;
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0 != length, FSP_ERR_INVALID_ARGUMENT);
#endif

    /* if socket read has been disabled by shutdown call then return any bytes left in the stream buffer. 
       However if 0 bytes left, return error. */
    if (!(p_instance_ctrl->sockets[socket_no].socket_read_write_flag & WIFI_ONCHIP_DA16200_SOCKET_READ))
    {
        size_t xReceivedBytes = xStreamBufferReceiveAlt(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl,
                                                        p_data,
                                                        length,
                                                        0); /* No wait needed as data is already in stream buffer*/
        if (0 < xReceivedBytes)
        {
            return (int32_t)xReceivedBytes;
        }
        
        return -FSP_ERR_WIFI_FAILED;                
    }

    /* Take the receive mutex */
    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     -FSP_ERR_WIFI_FAILED);

    if (0 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return -FSP_ERR_WIFI_FAILED;
    }

    if (socket_no != p_instance_ctrl->curr_socket_index)
    {
        rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return WIFI_ONCHIP_DA16200_ERR_UNKNOWN;
    }

    volatile size_t xReceivedBytes =
        xStreamBufferReceiveAlt(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl,
                                (p_data + recvcnt),
                                1,
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
                xStreamBufferReceiveAlt(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl,
                                        (p_data + recvcnt),
                                        num_bytes_left,
                                        pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_500MS));
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
    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t rm_wifi_onchip_da16200_socket_disconnect (uint32_t socket_no)
{
    fsp_err_t ret = FSP_ERR_WIFI_FAILED;
    uint32_t  mutex_flag;

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Test if socket has been created for socket index passed in to function */
    if (1 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
        FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                         FSP_ERR_WIFI_FAILED);

        // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+TRTRM=", sizeof(p_instance_ctrl->cmd_tx_buff));
        snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
                 sizeof(p_instance_ctrl->cmd_tx_buff), "%d\r", p_instance_ctrl->sockets[socket_no].socket_type);

        ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                p_instance_ctrl->curr_cmd_port,
                                                (char *) p_instance_ctrl->cmd_tx_buff,
                                                0,
                                                WIFI_ONCHIP_DA16200_TIMEOUT_2SEC,
                                                WIFI_ONCHIP_DA16200_DELAY_500MS,
                                                WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

        rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        FSP_ERROR_RETURN(FSP_SUCCESS == ret, FSP_ERR_WIFI_FAILED);

        /* Clear the create flag, set status to closed, and flush the stream buffer */
        if (FSP_SUCCESS == ret)
        {
            p_instance_ctrl->sockets[socket_no].socket_create_flag     = 0;
            p_instance_ctrl->sockets[socket_no].socket_status          = WIFI_ONCHIP_DA16200_SOCKET_STATUS_CLOSED;
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

#if (1 == WIFI_ONCHIP_DA16200_CFG_SNTP_ENABLE)

/*******************************************************************************************************************//**
 *  Initialize DA16200 module SNTP client service.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_INVALID_ARGUMENT Parameter passed into function was invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_onchip_da16200_sntp_service_init (wifi_onchip_da16200_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err = FSP_ERR_INTERNAL;
    uint8_t   ip_address_sntp_server[4] = {0, 0, 0, 0};
    int32_t   err_scan;

    /* Set the SNTP server IP address */
    err_scan =

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        sscanf((const char *) p_instance_ctrl->p_wifi_onchip_da16200_cfg->sntp_server_ip,
               "%u.%u.%u.%u,",
               (unsigned int *) &ip_address_sntp_server[0],
               (unsigned int *) &ip_address_sntp_server[1],
               (unsigned int *) &ip_address_sntp_server[2],
               (unsigned int *) &ip_address_sntp_server[3]);
    if (4 == err_scan)
    {
        /* Configure the SNTP Server Address */
        err = RM_WIFI_ONCHIP_DA16200_SntpServerIpAddressSet((uint8_t *) ip_address_sntp_server);
    }

    if (FSP_SUCCESS == err)
    {
        /* Enable/disable the SNTP clinet */
        err = RM_WIFI_ONCHIP_DA16200_SntpEnableSet(WIFI_ONCHIP_DA16200_SNTP_ENABLE);
    }

    /* Set the SNTP Timezone configuration string */
    if (FSP_SUCCESS == err)
    {
        err = RM_WIFI_ONCHIP_DA16200_SntpTimeZoneSet(
            p_instance_ctrl->p_wifi_onchip_da16200_cfg->sntp_utc_offset_in_hours,
            0,
            WIFI_ONCHIP_DA16200_SNTP_DAYLIGHT_SAVINGS_DISABLE);
    }

    return err;
}

#endif

/*! \endcond */

/*******************************************************************************************************************//**
 * @addtogroup WIFI_ONCHIP_DA16200 WIFI_ONCHIP_DA16200
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
fsp_err_t RM_WIFI_ONCHIP_DA16200_SntpServerIpAddressSet (uint8_t * p_server_ip_addr)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_server_ip_addr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
    strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWSNS=", sizeof(p_instance_ctrl->cmd_tx_buff));

    snprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
             sizeof(p_instance_ctrl->cmd_tx_buff), "%u.%u.%u.%u\r\n", p_server_ip_addr[0], p_server_ip_addr[1],
             p_server_ip_addr[2], p_server_ip_addr[3]);

    err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            (char *) p_instance_ctrl->cmd_tx_buff,
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_400MS,
                                            WIFI_ONCHIP_DA16200_DELAY_500MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t RM_WIFI_ONCHIP_DA16200_SntpEnableSet (wifi_onchip_da16200_sntp_enable_t enable)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    if (WIFI_ONCHIP_DA16200_SNTP_ENABLE == enable)
    {
        // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWSNTP=1\r\n", sizeof(p_instance_ctrl->cmd_tx_buff));

        err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                p_instance_ctrl->curr_cmd_port,
                                                (char *) p_instance_ctrl->cmd_tx_buff,
                                                0,
                                                WIFI_ONCHIP_DA16200_TIMEOUT_400MS,
                                                WIFI_ONCHIP_DA16200_DELAY_500MS,
                                                WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

        p_instance_ctrl->is_sntp_enabled = true;
    }
    else
    {
        // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "AT+NWSNTP=0\r\n", sizeof(p_instance_ctrl->cmd_tx_buff));
        err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                                p_instance_ctrl->curr_cmd_port,
                                                (char *) p_instance_ctrl->cmd_tx_buff,
                                                0,
                                                WIFI_ONCHIP_DA16200_TIMEOUT_400MS,
                                                WIFI_ONCHIP_DA16200_DELAY_500MS,
                                                WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

        p_instance_ctrl->is_sntp_enabled = false;
    }

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t RM_WIFI_ONCHIP_DA16200_SntpTimeZoneSet (
    int                                                utc_offset_in_hours,
    uint32_t                                           minutes,
    wifi_onchip_da16200_sntp_daylight_savings_enable_t daylightSavingsEnable)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(((utc_offset_in_hours >= -12) && (utc_offset_in_hours <= 12)), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0 == minutes) && (0 == daylightSavingsEnable), FSP_ERR_INVALID_ARGUMENT);
#endif

    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    int utc_offset_in_secs = (utc_offset_in_hours * HOURS_IN_SECONDS);
    snprintf((char *) p_instance_ctrl->cmd_tx_buff,
             sizeof(p_instance_ctrl->cmd_tx_buff),
             "AT+TZONE=%d\r",
             utc_offset_in_secs);

    err = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            (char *) p_instance_ctrl->cmd_tx_buff,
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_400MS,
                                            WIFI_ONCHIP_DA16200_DELAY_200MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t RM_WIFI_ONCHIP_DA16200_LocalTimeGet (uint8_t * p_local_time, uint32_t size_string)
{
    uint32_t  mutex_flag;
    fsp_err_t ret;

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;
    char * p_str = (char *) p_instance_ctrl->cmd_rx_buff;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_local_time);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(WIFI_ONCHIP_DA16200_LOCAL_TIME_STR_SIZE <= size_string, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN(p_instance_ctrl->is_sntp_enabled == true, FSP_ERR_WIFI_FAILED);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_DA16200_MUTEX_TX | WIFI_ONCHIP_DA16200_MUTEX_RX);
    FSP_ERROR_RETURN(pdTRUE == rm_wifi_onchip_da16200_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    memset(p_local_time, 0, size_string);
    memset((char *) p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    ret = rm_wifi_onchip_da16200_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "AT+TIME=?\r",
                                            0,
                                            WIFI_ONCHIP_DA16200_TIMEOUT_2SEC,
                                            WIFI_ONCHIP_DA16200_DELAY_1000MS,
                                            WIFI_ONCHIP_DA16200_RETURN_TEXT_OK);
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

    rm_wifi_onchip_da16200_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return ret;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_ONCHIP_DA16200)
 **********************************************************************************************************************/

/*! \cond PRIVATE */

/***********************************************************************************************************************
 * Local Functions definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Handles incoming socket data.
 *
 *  @param[in]  pSocket             Pointer to socket instance structure.
 *  @param[in]  data_byte           Incoming data in byte
 *
 **********************************************************************************************************************/
static void rm_wifi_da16200_handle_incoming_socket_data (da16200_socket_t * pSocket, uint8_t data_byte)
{
    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;
    da16200_socket_t * p_socket                 = pSocket;
    BaseType_t         xHigherPriorityTaskWoken = pdFALSE; // Initialized to pdFALSE.

    switch (p_socket->socket_recv_state)
    {
        case WIFI_ONCHIP_DA16200_RECV_PREFIX:
        {
            if ('+' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_CMD;
                rx_data_index               = 0;
            }
            else
            {
                xStreamBufferSendFromISR(p_instance_ctrl->socket_byteq_hdl, &data_byte, 1, &xHigherPriorityTaskWoken);
            }

            break;
        }

        case WIFI_ONCHIP_DA16200_RECV_CMD:
        {
            rx_buffer[rx_data_index++] = data_byte;
            rx_data_index              = (rx_data_index) % WIFI_ONCHIP_DA16200_TEMP_BUFFER_SIZE;

            if (5 == rx_data_index)
            {
                /* Check for incoming data through socket */
                if (0 == strncmp("TRDTC", (char *) rx_buffer, strlen("TRDTC")))
                {
                    p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_SUFFIX;
                }
                /* Check for TCP socket disconnect notification */
                else if (0 == strncmp("TRXTC", (char *) rx_buffer, strlen("TRXTC")))
                {
                    p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_PREFIX;

                    /* Socket disconnect event received */
                    p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_create_flag = 0;
                    p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_status      =
                        WIFI_ONCHIP_DA16200_SOCKET_STATUS_CLOSED;
                    p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_read_write_flag = 0;
                }
                else
                {
                    p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_PREFIX;
                }
            }

            break;
        }

        case WIFI_ONCHIP_DA16200_RECV_SUFFIX:
        {
            if (':' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_PARAM_CID;
            }

            break;
        }

        case WIFI_ONCHIP_DA16200_RECV_PARAM_CID:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_PARAM_IP;
                rx_data_index               = 0;
            }

            break;
        }

        case WIFI_ONCHIP_DA16200_RECV_PARAM_IP:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_PARAM_PORT;
                rx_data_index               = 0;
            }

            break;
        }

        case WIFI_ONCHIP_DA16200_RECV_PARAM_PORT:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_PARAM_LEN;
                rx_data_index               = 0;
            }

            break;
        }

        case WIFI_ONCHIP_DA16200_RECV_PARAM_LEN:
        {
            if (',' == data_byte)
            {
                p_socket->socket_recv_data_len = strtol((char *) rx_buffer, NULL, 10);
                p_socket->socket_recv_state    = WIFI_ONCHIP_DA16200_RECV_DATA;
                rx_data_index = 0;
            }
            else
            {
                rx_buffer[rx_data_index++] = data_byte;
                rx_data_index              = (rx_data_index) % WIFI_ONCHIP_DA16200_TEMP_BUFFER_SIZE;
            }

            break;
        }

        case WIFI_ONCHIP_DA16200_RECV_DATA:
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
                p_socket->socket_recv_state = WIFI_ONCHIP_DA16200_RECV_PREFIX;
            }

            break;
        }
    }
}

/*******************************************************************************************************************//**
 *  UART Callback routine.
 *
 *  @param[in]  p_args              Pointer to uart callback structure.
 *
 **********************************************************************************************************************/
void rm_wifi_onchip_da16200_uart_callback (uart_callback_args_t * p_args)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE; // Initialized to pdFALSE.

    wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_da16200_instance;
    volatile uint32_t uart_context_index = 0;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    if (NULL == p_args)
    {
        return;
    }
#endif

    if ((NULL != p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_SECOND_PORT]) &&
        (p_args->channel ==
         p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_SECOND_PORT]->p_cfg->channel))
    {
        uart_context_index = 1;
    }

    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
            uint8_t data_byte = (uint8_t) p_args->data;

            if (uart_context_index == WIFI_ONCHIP_DA16200_UART_INITIAL_PORT)
            {
                if (0 == p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_create_flag)
                {
                    xStreamBufferSendFromISR(p_instance_ctrl->socket_byteq_hdl, &data_byte, 1,
                                             &xHigherPriorityTaskWoken);
                }
                else                   // socket data mode
                {
                    rm_wifi_da16200_handle_incoming_socket_data(&p_instance_ctrl->sockets[p_instance_ctrl->
                                                                                          curr_socket_index],
                                                                data_byte);
                }
            }
            else if (uart_context_index == WIFI_ONCHIP_DA16200_UART_SECOND_PORT)
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
 *  Clean up the DA16200 instance.
 *
 *  @param[in]  p_instance_ctrl              Pointer to DA16200 instance structure.
 *
 **********************************************************************************************************************/
static void rm_wifi_onchip_da16200_cleanup_open (wifi_onchip_da16200_instance_ctrl_t * const p_instance_ctrl)
{
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

    if (NULL != p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT])
    {
        vSemaphoreDelete(p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT]);
        p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT] = NULL;
    }

    if (p_instance_ctrl->num_uarts > 1)
    {
        if (NULL != p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_DA16200_UART_SECOND_PORT])
        {
            vSemaphoreDelete(p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_DA16200_UART_SECOND_PORT]);
            p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_DA16200_UART_SECOND_PORT] = NULL;
        }
    }

    uart_instance_t * p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_INITIAL_PORT];
    if (SCIU_OPEN == ((rm_wifi_onchip_da16200_uart_instance_ctrl_t *) p_uart->p_ctrl)->open)
    {
        p_uart->p_api->close(p_uart->p_ctrl);
    }

    p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_DA16200_UART_SECOND_PORT];
    if (SCIU_OPEN == ((rm_wifi_onchip_da16200_uart_instance_ctrl_t *) p_uart->p_ctrl)->open)
    {
        p_uart->p_api->close(p_uart->p_ctrl);
    }
}

/*******************************************************************************************************************//**
 *  Resets the DA16200 module.
 *
 *  @param[in]  p_instance_ctrl              Pointer to DA16200 instance structure.
 *
 **********************************************************************************************************************/
static void rm_wifi_onchip_da16200_wifi_module_reset (wifi_onchip_da16200_instance_ctrl_t * const p_instance_ctrl)
{
    /* Reset the wifi module */
    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, p_instance_ctrl->reset_pin, BSP_IO_LEVEL_LOW);

    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_20MS));

    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, p_instance_ctrl->reset_pin, BSP_IO_LEVEL_HIGH);

    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_DA16200_TIMEOUT_1MS));
}

/*******************************************************************************************************************//**
 *  Give the mutex for the send basic call.
 *
 *  @param[in] p_instance_ctrl      Pointer to control instance.
 *  @param[in] mutex_flag           Flags for the mutex.
 *
 *  @retval pdTrue             Function completed successfully.
 **********************************************************************************************************************/
static BaseType_t rm_wifi_onchip_da16200_send_basic_give_mutex (wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl,
                                                                uint32_t                              mutex_flag)
{
    BaseType_t volatile xSemRet = pdFALSE;

    if (0 != (mutex_flag & WIFI_ONCHIP_DA16200_MUTEX_RX))
    {
        xSemRet = xSemaphoreGive(p_instance_ctrl->rx_sem);
        if (xSemRet != pdTRUE)
        {
            return pdFALSE;
        }
    }

    if (0 != (mutex_flag & WIFI_ONCHIP_DA16200_MUTEX_TX))
    {
        xSemRet = xSemaphoreGive(p_instance_ctrl->tx_sem);
        if (xSemRet != pdTRUE)
        {
            return pdFALSE;
        }
    }

    return xSemRet;
}

/*******************************************************************************************************************//**
 *  Take the mutex for the send basic call.
 *
 *  @param[in] p_instance_ctrl      Pointer to control instance.
 *  @param[in] mutex_flag           Flags for the mutex.
 *
 *  @retval pdTrue             Function completed successfully.
 **********************************************************************************************************************/
static BaseType_t rm_wifi_onchip_da16200_send_basic_take_mutex (wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl,
                                                                uint32_t                              mutex_flag)
{
    BaseType_t volatile xSemRet = pdFALSE;

    if (0 != (mutex_flag & WIFI_ONCHIP_DA16200_MUTEX_TX))
    {
        if (NULL != p_instance_ctrl->tx_sem)
        {
            xSemRet =
                xSemaphoreTake(p_instance_ctrl->tx_sem,
                               (wifi_sx_wifi_onchip_da16200_sem_block_timeout / portTICK_PERIOD_MS));
            if (xSemRet != pdTRUE)
            {
                return pdFALSE;
            }
        }
    }

    if (0 != (mutex_flag & WIFI_ONCHIP_DA16200_MUTEX_RX))
    {
        if (NULL != p_instance_ctrl->rx_sem)
        {
            xSemRet =
                xSemaphoreTake(p_instance_ctrl->rx_sem,
                               (wifi_sx_wifi_onchip_da16200_sem_block_timeout / portTICK_PERIOD_MS));
            if (xSemRet != pdTRUE)
            {
                if (0 != (mutex_flag & WIFI_ONCHIP_DA16200_MUTEX_TX))
                {
                    xSemaphoreGive(p_instance_ctrl->tx_sem);
                }

                return pdFALSE;
            }
        }
    }

    return xSemRet;
}

/*******************************************************************************************************************//**
 *  Send and receive an AT command with testing for return.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 * @param[in]  serial_ch_id         Pointer to IP address returned from look up.
 * @param[in]  p_textstring         Pointer to IP address returned from look up.
 * @param[in]  length               length of data to be send.
 * @param[in]  timeout_ms           Pointer to IP address returned from look up.
 * @param[in]  retry_delay          retry delay in milliseconds
 * @param[in]  p_expect_code        Pointer containing AT command response.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_INVALID_DATA     Accuracy of data is not guaranteed
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_onchip_da16200_send_basic (wifi_onchip_da16200_instance_ctrl_t * p_instance_ctrl,
                                                    uint32_t                              serial_ch_id,
                                                    const char                          * p_textstring,
                                                    uint32_t                              length,
                                                    uint32_t                              timeout_ms,
                                                    uint32_t                              retry_delay,
                                                    const char                          * p_expect_code)
{
    fsp_err_t        err         = FSP_SUCCESS;
    volatile uint8_t retry_count = 0U;
    uint32_t         recvcnt     = 0;
    char           * ret         = NULL;

#if (WIFI_ONCHIP_DA16200_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_textstring);
#endif

    memset(p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    if (p_textstring != NULL)
    {
        recvcnt = 0;

        if (uxQueueMessagesWaiting((QueueHandle_t) p_instance_ctrl->uart_tei_sem[serial_ch_id]) != 0)
        {
            return FSP_ERR_WIFI_FAILED;
        }

        if (0 == length)
        {
            err =
                p_instance_ctrl->uart_instance_objects[serial_ch_id]->p_api->write(p_instance_ctrl->uart_instance_objects[
                                                                                       serial_ch_id]->p_ctrl,
                                                                                   (uint8_t *) p_textstring,
                                                                                   strlen(
                                                                                       p_textstring));
        }
        else
        {
            err =
                p_instance_ctrl->uart_instance_objects[serial_ch_id]->p_api->write(p_instance_ctrl->uart_instance_objects[
                                                                                       serial_ch_id]->p_ctrl,
                                                                                   (uint8_t *) p_textstring,
                                                                                   length);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        FSP_ERROR_RETURN(pdTRUE ==
                         xSemaphoreTake(p_instance_ctrl->uart_tei_sem[serial_ch_id], (timeout_ms / portTICK_PERIOD_MS)),
                         FSP_ERR_WIFI_FAILED);
    }

    for (retry_count = 0; retry_count < WIFI_ONCHIP_DA16200_CFG_MAX_RETRIES_UART_COMMS; retry_count++)
    {
        if (NULL != p_expect_code)
        {
            /* Get the transmitted message from the stream buffer */
            xStreamBufferSetTriggerLevel(p_instance_ctrl->socket_byteq_hdl, sizeof(p_instance_ctrl->cmd_rx_buff));

            size_t xReceivedBytes = xStreamBufferReceiveAlt(p_instance_ctrl->socket_byteq_hdl,
                                                            &p_instance_ctrl->cmd_rx_buff[recvcnt],
                                                            (int) sizeof(p_instance_ctrl->cmd_rx_buff),
                                                            pdMS_TO_TICKS(timeout_ms));

            /* Response data check */
            if (xReceivedBytes > 0)
            {
                ret = strstr((char *) &p_instance_ctrl->cmd_rx_buff[0], p_expect_code);
                if (ret == NULL)
                {
                    R_BSP_SoftwareDelay(retry_delay, BSP_DELAY_UNITS_MILLISECONDS);
                }
                else
                {
                    break;
                }
            }
            else
            {
                R_BSP_SoftwareDelay(retry_delay, BSP_DELAY_UNITS_MILLISECONDS);
            }
        }
        else
        {
            break;
        }
    }

    FSP_ERROR_RETURN(WIFI_ONCHIP_DA16200_CFG_MAX_RETRIES_UART_COMMS != (retry_count), FSP_ERR_WIFI_FAILED);
    if (ret == NULL)
    {
        if (p_instance_ctrl->cmd_rx_buff[0] != 0)
        {
            err = rm_wifi_onchip_da16200_error_lookup((char *) p_instance_ctrl->cmd_rx_buff);
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 *  Parse the incoming DA16200 error code and translates into FSP error.
 *
 * @param[in]  p_resp                        Pointer to response string.
 *
 * @retval FSP_ERR_WIFI_UNKNOWN_AT_CMD       DA16200 Unknown AT command Error.
 * @retval FSP_ERR_WIFI_INSUF_PARAM          DA16200 Insufficient parameter.
 * @retval FSP_ERR_WIFI_TOO_MANY_PARAMS      DA16200 Too many parameters.
 * @retval FSP_ERR_WIFI_INV_PARAM_VAL        DA16200 Wrong parameter value.
 * @retval FSP_ERR_UNSUPPORTED               Selected mode not supported by this API.
 * @retval FSP_ERR_WIFI_AP_NOT_CONNECTED     DA16200 Not connected to an AP or Communication peer.
 * @retval FSP_ERR_WIFI_NO_RESULT            DA16200 No result.
 * @retval FSP_ERR_WIFI_RSP_BUF_OVFLW        DA16200 Response buffer overflow.
 * @retval FSP_ERR_WIFI_FUNC_NOT_CONFIG      DA16200 Function is not configured.
 * @retval FSP_ERR_TIMEOUT                   Timeout error
 * @retval FSP_ERR_WIFI_NVRAM_WR_FAIL        DA16200 NVRAM write failure
 * @retval FSP_ERR_WIFI_RET_MEM_WR_FAIL      DA16200 Retention memory write failure
 * @retval FSP_ERR_WIFI_UNKNOWN_ERR          DA16200 unknown error
 * @retval FSP_ERR_INVALID_DATA              Accuracy of data is not guaranteed
 * @retval FSP_ERR_INTERNAL                  Internal error
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_onchip_da16200_error_lookup (char * p_resp)
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
        case WIFI_ONCHIP_DA16200_ERR_UNKNOWN_CMD:
        {
            err = FSP_ERR_WIFI_UNKNOWN_AT_CMD;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_INSUF_PARAMS:
        {
            err = FSP_ERR_WIFI_INSUF_PARAM;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_TOO_MANY_PARAMS:
        {
            err = FSP_ERR_WIFI_TOO_MANY_PARAMS;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_INVALID_PARAM:
        {
            err = FSP_ERR_WIFI_INV_PARAM_VAL;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_UNSUPPORTED_FUN:
        {
            err = FSP_ERR_UNSUPPORTED;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_NOT_CONNECTED_AP:
        {
            err = FSP_ERR_WIFI_AP_NOT_CONNECTED;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_NO_RESULT:
        {
            err = FSP_ERR_WIFI_NO_RESULT;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_RESP_BUF_OVERFLOW:
        {
            err = FSP_ERR_WIFI_RSP_BUF_OVFLW;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_FUNC_NOT_CONFIG:
        {
            err = FSP_ERR_WIFI_FUNC_NOT_CONFIG;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_CMD_TIMEOUT:
        {
            err = FSP_ERR_TIMEOUT;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_NVRAM_WR_FAIL:
        {
            err = FSP_ERR_WIFI_NVRAM_WR_FAIL;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_RETEN_MEM_WR_FAIL:
        {
            err = FSP_ERR_WIFI_RET_MEM_WR_FAIL;
            break;
        }

        case WIFI_ONCHIP_DA16200_ERR_UNKNOWN:
        {
            err = FSP_ERR_WIFI_UNKNOWN_ERR;
            break;
        }
    }

    return err;
}

///////////////////////////////////////////////////////////////////////////////

/*
 * Alternate function for the StreamBufferReceive call. Allows for the byte
 * triggering mechanism to work correctly. The alternate function does perform
 * thread blocking when the trigger level has not been reached.
 */

///////////////////////////////////////////////////////////////////////////////
static size_t prvBytesInBuffer (const StreamBuffer_t * const pxStreamBuffer)
{
/* Returns the distance between xTail and xHead. */
    size_t xCount;

    xCount  = pxStreamBuffer->xLength + pxStreamBuffer->xHead;
    xCount -= pxStreamBuffer->xTail;
    if (xCount >= pxStreamBuffer->xLength)
    {
        xCount -= pxStreamBuffer->xLength;
    }
    else
    {
        mtCOVERAGE_TEST_MARKER();
    }

    return xCount;
}

static size_t prvReadBytesFromBuffer (StreamBuffer_t * pxStreamBuffer,
                                      uint8_t        * pucData,
                                      size_t           xMaxCount,
                                      size_t           xBytesAvailable)
{
    size_t xCount;
    size_t xFirstLength;
    size_t xNextTail;

    /* Use the minimum of the wanted bytes and the available bytes. */
    xCount = configMIN(xBytesAvailable, xMaxCount);

    if (xCount > (size_t) 0)
    {
        xNextTail = pxStreamBuffer->xTail;

        /* Calculate the number of bytes that can be read - which may be
         * less than the number wanted if the data wraps around to the start of
         * the buffer. */
        xFirstLength = configMIN(pxStreamBuffer->xLength - xNextTail, xCount);

        /* Obtain the number of bytes it is possible to obtain in the first
         * read.  Asserts check bounds of read and write. */
        configASSERT(xFirstLength <= xMaxCount);
        configASSERT((xNextTail + xFirstLength) <= pxStreamBuffer->xLength);
        (void) memcpy((void *) pucData, (const void *) &(pxStreamBuffer->pucBuffer[xNextTail]), xFirstLength); /*lint !e9087 memcpy() requires void *. */

        /* If the total number of wanted bytes is greater than the number
         * that could be read in the first read... */
        if (xCount > xFirstLength)
        {
            /*...then read the remaining bytes from the start of the buffer. */
            configASSERT(xCount <= xMaxCount);
            (void) memcpy((void *) &(pucData[xFirstLength]), (void *) (pxStreamBuffer->pucBuffer),
                          xCount - xFirstLength); /*lint !e9087 memcpy() requires void *. */
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }

        /* Move the tail pointer to effectively remove the data read from
         * the buffer. */
        xNextTail += xCount;

        if (xNextTail >= pxStreamBuffer->xLength)
        {
            xNextTail -= pxStreamBuffer->xLength;
        }

        pxStreamBuffer->xTail = xNextTail;
    }
    else
    {
        mtCOVERAGE_TEST_MARKER();
    }

    return xCount;
}

static size_t prvReadMessageFromBuffer (StreamBuffer_t * pxStreamBuffer,
                                        void           * pvRxData,
                                        size_t           xBufferLengthBytes,
                                        size_t           xBytesAvailable,
                                        size_t           xBytesToStoreMessageLength)
{
    size_t xOriginalTail;
    size_t xReceivedLength;
    size_t xNextMessageLength;
    configMESSAGE_BUFFER_LENGTH_TYPE xTempNextMessageLength;

    if (xBytesToStoreMessageLength != (size_t) 0)
    {
        /* A discrete message is being received.  First receive the length
         * of the message.  A copy of the tail is stored so the buffer can be
         * returned to its prior state if the length of the message is too
         * large for the provided buffer. */
        xOriginalTail = pxStreamBuffer->xTail;
        (void) prvReadBytesFromBuffer(pxStreamBuffer,
                                      (uint8_t *) &xTempNextMessageLength,
                                      xBytesToStoreMessageLength,
                                      xBytesAvailable);
        xNextMessageLength = xTempNextMessageLength;

        /* Reduce the number of bytes available by the number of bytes just
         * read out. */
        xBytesAvailable -= xBytesToStoreMessageLength;

        /* Check there is enough space in the buffer provided by the
         * user. */
        if (xNextMessageLength > xBufferLengthBytes)
        {
            /* The user has provided insufficient space to read the message
             * so return the buffer to its previous state (so the length of
             * the message is in the buffer again). */
            pxStreamBuffer->xTail = xOriginalTail;
            xNextMessageLength    = 0;
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    else
    {
        /* A stream of bytes is being received (as opposed to a discrete
         * message), so read as many bytes as possible. */
        xNextMessageLength = xBufferLengthBytes;
    }

    /* Read the actual data. */
    xReceivedLength = prvReadBytesFromBuffer(pxStreamBuffer, (uint8_t *) pvRxData, xNextMessageLength, xBytesAvailable); /*lint !e9079 Data storage area is implemented as uint8_t array for ease of sizing, indexing and alignment. */

    return xReceivedLength;
}

static size_t xStreamBufferReceiveAlt (StreamBufferHandle_t xStreamBuffer,
                                       void               * pvRxData,
                                       size_t               xBufferLengthBytes,
                                       TickType_t           xTicksToWait)
{
    StreamBuffer_t * const pxStreamBuffer  = xStreamBuffer;
    size_t                 xReceivedLength = 0;
    size_t                 xBytesAvailable;
    size_t                 xBytesToStoreMessageLength;

    configASSERT(pvRxData);
    configASSERT(pxStreamBuffer);

    /* This receive function is used by both message buffers, which store
     * discrete messages, and stream buffers, which store a continuous stream of
     * bytes.  Discrete messages include an additional
     * sbBYTES_TO_STORE_MESSAGE_LENGTH bytes that hold the length of the
     * message. */
    if ((pxStreamBuffer->ucFlags & sbFLAGS_IS_MESSAGE_BUFFER) != (uint8_t) 0)
    {
        xBytesToStoreMessageLength = sbBYTES_TO_STORE_MESSAGE_LENGTH;
    }
    else
    {
        /* if this is a stream buffer then set wait count to the trigger level */
        xBytesToStoreMessageLength = pxStreamBuffer->xTriggerLevelBytes;
    }

    if (xTicksToWait != (TickType_t) 0)
    {
        /* Checking if there is data and clearing the notification state must be
         * performed atomically. */
        taskENTER_CRITICAL();
        {
            xBytesAvailable = prvBytesInBuffer(pxStreamBuffer);

            /* If this function was invoked by a message buffer read then
             * xBytesToStoreMessageLength holds the number of bytes used to hold
             * the length of the next discrete message.  If this function was
             * invoked by a stream buffer read then xBytesToStoreMessageLength will
             * be 0. */
            if (xBytesAvailable <= xBytesToStoreMessageLength)
            {
                /* Clear notification state as going to wait for data. */
                (void) xTaskNotifyStateClear(NULL);

                /* Should only be one reader. */
                configASSERT(pxStreamBuffer->xTaskWaitingToReceive == NULL);
                pxStreamBuffer->xTaskWaitingToReceive = xTaskGetCurrentTaskHandle();
            }
            else
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        taskEXIT_CRITICAL();

        if (xBytesAvailable <= xBytesToStoreMessageLength)
        {
            /* Wait for data to be available. */
            traceBLOCKING_ON_STREAM_BUFFER_RECEIVE(xStreamBuffer);
            (void) xTaskNotifyWait((uint32_t) 0, (uint32_t) 0, NULL, xTicksToWait);
            pxStreamBuffer->xTaskWaitingToReceive = NULL;

            /* Recheck the data available after blocking. */
            xBytesAvailable = prvBytesInBuffer(pxStreamBuffer);
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    else
    {
        xBytesAvailable = prvBytesInBuffer(pxStreamBuffer);
    }

    /* Set bytes to store message to length to 0 if this is a stream buffer */
    /* since stream buffers have no byte count header.                      */
    if ((pxStreamBuffer->ucFlags & sbFLAGS_IS_MESSAGE_BUFFER) == (uint8_t) 0)
    {
        xBytesToStoreMessageLength = 0;
    }

    /* Whether receiving a discrete message (where xBytesToStoreMessageLength
     * holds the number of bytes used to store the message length) or a stream of
     * bytes (where xBytesToStoreMessageLength is zero), the number of bytes
     * available must be greater than xBytesToStoreMessageLength to be able to
     * read bytes from the buffer. */
    if (xBytesAvailable > xBytesToStoreMessageLength)
    {
        xReceivedLength = prvReadMessageFromBuffer(pxStreamBuffer,
                                                   pvRxData,
                                                   xBufferLengthBytes,
                                                   xBytesAvailable,
                                                   xBytesToStoreMessageLength);

        /* Was a task waiting for space in the buffer? */
        if (xReceivedLength != (size_t) 0)
        {
            traceSTREAM_BUFFER_RECEIVE(xStreamBuffer, xReceivedLength);
            sbRECEIVE_COMPLETED(pxStreamBuffer);
        }
        else
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    else
    {
        traceSTREAM_BUFFER_RECEIVE_FAILED(xStreamBuffer);
        mtCOVERAGE_TEST_MARKER();
    }

    return xReceivedLength;
}

/*! \endcond */
