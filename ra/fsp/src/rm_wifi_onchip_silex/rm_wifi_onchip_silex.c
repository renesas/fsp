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

#include <stdio.h>
#include <string.h>
#include "limits.h"
#include "r_ioport.h"
#include "rm_wifi_onchip_silex.h"

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
 #include "FreeRTOS.h"
 #include "stream_buffer.h"
 #include "semphr.h"
 #include "portmacro.h"
#else                                  // Azure RTOS
 #include "tx_api.h"
#endif
#if (BSP_FEATURE_SCI_VERSION == 2U)
 #include "r_sci_b_uart.h"
typedef sci_b_uart_instance_ctrl_t rm_wifi_onchip_silex_uart_instance_ctrl_t;
typedef sci_b_uart_extended_cfg_t  rm_wifi_onchip_silex_uart_extended_cfg_t;
typedef sci_b_baud_setting_t       rm_wifi_onchip_silex_baud_setting_t;
 #define RM_WIFI_ONCHIP_SILEX_SCI_UART_FLOW_CONTROL_RTS                SCI_B_UART_FLOW_CONTROL_RTS
 #define RM_WIFI_ONCHIP_SILEX_SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS    SCI_B_UART_FLOW_CONTROL_HARDWARE_CTSRTS
static fsp_err_t (* p_sci_uart_baud_calculate)(uint32_t, bool, uint32_t,
                                               struct st_sci_b_baud_setting_t * const) = &R_SCI_B_UART_BaudCalculate;
#else
 #include "r_sci_uart.h"
typedef sci_uart_instance_ctrl_t rm_wifi_onchip_silex_uart_instance_ctrl_t;
typedef sci_uart_extended_cfg_t  rm_wifi_onchip_silex_uart_extended_cfg_t;
typedef baud_setting_t           rm_wifi_onchip_silex_baud_setting_t;
 #define RM_WIFI_ONCHIP_SILEX_SCI_UART_FLOW_CONTROL_RTS                SCI_UART_FLOW_CONTROL_RTS
 #define RM_WIFI_ONCHIP_SILEX_SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS    SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS
static fsp_err_t (* p_sci_uart_baud_calculate)(uint32_t, bool, uint32_t,
                                               baud_setting_t * const) = &R_SCI_UART_BaudCalculate;
#endif

/*! \cond PRIVATE */

/***********************************************************************************************************************
 * Externs
 **********************************************************************************************************************/

extern const ioport_instance_t g_ioport;

/***********************************************************************************************************************
 * Enumerations
 **********************************************************************************************************************/

/* Numeric return types for AT commands */
typedef enum
{
    WIFI_ONCHIP_SILEX_RETURN_OK = 0,      ///< WIFI_ONCHIP_SILEX_RETURN_OK
    WIFI_ONCHIP_SILEX_RETURN_CONNECT,     ///< WIFI_ONCHIP_SILEX_RETURN_CONNECT
    WIFI_ONCHIP_SILEX_RETURN_RING,        ///< WIFI_ONCHIP_SILEX_RETURN_RING
    WIFI_ONCHIP_SILEX_RETURN_NO_CARRIER,  ///< WIFI_ONCHIP_SILEX_RETURN_NO_CARRIER
    WIFI_ONCHIP_SILEX_RETURN_ERROR,       ///< WIFI_ONCHIP_SILEX_RETURN_ERROR
    WIFI_ONCHIP_SILEX_RETURN_DUMMY,       ///< WIFI_ONCHIP_SILEX_RETURN_DUMMY
    WIFI_ONCHIP_SILEX_RETURN_NO_DIALTONE, ///< WIFI_ONCHIP_SILEX_RETURN_NO_DIALTONE
    WIFI_ONCHIP_SILEX_RETURN_BUSY,        ///< WIFI_ONCHIP_SILEX_RETURN_BUSY
    WIFI_ONCHIP_SILEX_RETURN_NO_ANSWER,   ///< WIFI_ONCHIP_SILEX_RETURN_NO_ANSWER
} sx_ulpgn_return_code_t;

/* Type of return message from AT command */
typedef enum
{
    WIFI_ONCHIP_SILEX_RETURN_STRING_TEXT = 0, ///< WIFI_ONCHIP_SILEX_RETURN_STRING_TEXT
    WIFI_ONCHIP_SILEX_RETURN_STRING_NUMERIC,  ///< WIFI_ONCHIP_SILEX_RETURN_STRING_NUMERIC
} sx_ulpgn_return_string_t;

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/

/* Max number of AT command return types supported by the modem */
#define WIFI_ONCHIP_SILEX_MAX_AT_COMMAND_TYPES             2

/* Silex uart port defines */
#define WIFI_ONCHIP_SILEX_UART_INITIAL_PORT                (0)
#define WIFI_ONCHIP_SILEX_UART_SECOND_PORT                 (1)

/* Mutex give/take defines */
#define WIFI_ONCHIP_SILEX_MUTEX_TX                         (1 << 0)
#define WIFI_ONCHIP_SILEX_MUTEX_RX                         (1 << 1)

/* Text full versions of AT command returns */
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_OK                   "OK\r\n"
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_CONNECT              "CONNECT\r\n"
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_RING                 "RING\r\n"
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_NO_CARRIER           "NO_CARRIER\r\n"
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_ERROR                "ERROR\r\n"
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_NO_DIALTONE          "NO_DIALTONE\r\n"
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_BUSY                 "BUSY\r\n"
#define WIFI_ONCHIP_SILEX_RETURN_TEXT_NO_ANSWER            "NO_ANSWER\r\n"

/* Text numeric versions of AT command returns */
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_OK                "0\r"
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_CONNECT           "1\r"
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_RING              "2\r"
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_NO_CARRIER        "3\r"
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_ERROR             "4\r"
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_NO_DIALTONE       "6\r"
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_BUSY              "7\r"
#define WIFI_ONCHIP_SILEX_RETURN_NUMERIC_NO_ANSWER         "8\r"

/* Socket status return values */
#define WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_CLOSED        "CLOSED"
#define WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_SOCKET        "SOCKET"
#define WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_BOUND         "BOUND"
#define WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_LISTEN        "LISTEN"
#define WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_CONNECTED     "CONNECTED"

/* Error type defines */
#define WIFI_ONCHIP_SILEX_ERR_BUSY                         (4)
#define WIFI_ONCHIP_SILEX_ERR_NO_SUPPORT                   (7)
#define WIFI_ONCHIP_SILEX_ERR_TIMEOUT                      (-4)
#define WIFI_ONCHIP_SILEX_ERR_UNKNOWN                      (-3)
#define WIFI_ONCHIP_SILEX_ERR_COMMS                        (-2)
#define WIFI_ONCHIP_SILEX_ERR_ERROR                        (-1)
#define WIFI_ONCHIP_SILEX_ERR_BUSY_CHAR                    ('4')
#define WIFI_ONCHIP_SILEX_ERR_NO_SUPPORT_CHAR              ('7')
#define WIFI_ONCHIP_SILEX_ERR_NONE_CHAR                    ('0')

#if (BSP_CFG_RTOS == 1)                // Azure RTOS
 #define TickType_t                                        unsigned long
 #define configTICK_RATE_HZ                                TX_TIMER_TICKS_PER_SECOND
 #define MS_TO_TICKS(xTimeInMs)    ((TickType_t) (((TickType_t) (xTimeInMs) * (TickType_t) configTICK_RATE_HZ * 1ULL) / \
                                                  (TickType_t) 1000ULL))
 #define WIFI_ONCHIP_SILEX_TIMEOUT_1MS                     (10)
 #define WIFI_ONCHIP_SILEX_TIMEOUT_3MS                     (10)
 #define WIFI_ONCHIP_SILEX_TIMEOUT_5MS                     (10)
 #define WIFI_ONCHIP_SILEX_TIMEOUT_MIN_TICKS               (2)
 #define WIFI_ONCHIP_SILEX_TEMPORARY_BUFFER_SIZE           (30)
#else                                  // FreeRTOS
 #define WIFI_ONCHIP_SILEX_TIMEOUT_1MS                     (1)
 #define WIFI_ONCHIP_SILEX_TIMEOUT_3MS                     (3)
 #define WIFI_ONCHIP_SILEX_TIMEOUT_5MS                     (5)
#endif

/* Predefined timeout values */
#define WIFI_ONCHIP_SILEX_TIMEOUT_10MS                     (10)
#define WIFI_ONCHIP_SILEX_TIMEOUT_25MS                     (25)
#define WIFI_ONCHIP_SILEX_TIMEOUT_30MS                     (30)
#define WIFI_ONCHIP_SILEX_TIMEOUT_100MS                    (100)
#define WIFI_ONCHIP_SILEX_TIMEOUT_200MS                    (200)
#define WIFI_ONCHIP_SILEX_TIMEOUT_300MS                    (300)
#define WIFI_ONCHIP_SILEX_TIMEOUT_400MS                    (400)
#define WIFI_ONCHIP_SILEX_TIMEOUT_500MS                    (500)
#define WIFI_ONCHIP_SILEX_TIMEOUT_1SEC                     (1000)
#define WIFI_ONCHIP_SILEX_TIMEOUT_2SEC                     (2000)
#define WIFI_ONCHIP_SILEX_TIMEOUT_3SEC                     (3000)
#define WIFI_ONCHIP_SILEX_TIMEOUT_4SEC                     (4000)
#define WIFI_ONCHIP_SILEX_TIMEOUT_5SEC                     (5000)
#define WIFI_ONCHIP_SILEX_TIMEOUT_8SEC                     (8000)
#define WIFI_ONCHIP_SILEX_TIMEOUT_15SEC                    (15000)
#define WIFI_ONCHIP_SILEX_TIMEOUT_20SEC                    (20000)

/* Max IP packet size */
#define WIFI_ONCHIP_SILEX_CFG_MAX_PACKET_SIZE              (1420)
#define WIFI_ONCHIP_SILEX_MAX_IP_FRAME_SIZE                (5000)

/* Max retry attempts for socket index change */
#define WIFI_ONCHIP_SILEX_MAX_SOCKET_INDEX_RETRIES         (10)

/* Flag definitions for TCP Timeout */
#define WIFI_ONCHIP_SILEX_TCP_TIMEOUT_FLAG_SEND            (0)
#define WIFI_ONCHIP_SILEX_TCP_TIMEOUT_FLAG_RECV            (1)

/* Pulse timing for reset pin CHIP_PWD_L of the Silex module */
#define WIFI_ONCHIP_SILEX_RESET_PIN_PULSE                  (WIFI_ONCHIP_SILEX_TIMEOUT_25MS)

/* Pin or port invalid definition */
#define WIFI_ONCHIP_SILEX_BSP_PIN_PORT_INVALID             (UINT16_MAX)

/* Minimum string size for getting local time string */
#define RM_WIFI_ONCHIP_SILEX_MIN_LOCAL_TIME_STRING_SIZE    25

/* Initial Silex Wifi module UART settings */
#define WIFI_ONCHIP_SILEX_DEFAULT_BAUDRATE                 115200
#define WIFI_ONCHIP_SILEX_DEFAULT_MODULATION               false
#define WIFI_ONCHIP_SILEX_DEFAULT_ERROR                    9000

#define WIFI_ONCHIP_SILEX_SOCKET_TYPE_TCP                  (0)
#define WIFI_ONCHIP_SILEX_SOCKET_TYPE_UDP                  (1)
#define WIFI_ONCHIP_SILEX_SOCKET_TYPE_MAX                  (2)

/* Unique number for WIFI Open status */
#define WIFI_OPEN                                          (0x57495749ULL) // Is "WIFI" in ASCII

/* Unique number for SCI Open Status */
#if (BSP_FEATURE_SCI_VERSION == 2U)
 #define SCIU_OPEN                                         (0x53434942U)   // Is "SCIB" in ASCII
#else
 #define SCIU_OPEN                                         (0x53434955U)   // Is "SCIU" in ASCII
#endif

/***********************************************************************************************************************
 * Constants
 **********************************************************************************************************************/

/* Const strings used for return type in full version */
const uint8_t g_wifi_onchip_silex_return_text_ok[]          = WIFI_ONCHIP_SILEX_RETURN_TEXT_OK;
const uint8_t g_wifi_onchip_silex_return_text_connect[]     = WIFI_ONCHIP_SILEX_RETURN_TEXT_CONNECT;
const uint8_t g_wifi_onchip_silex_return_text_ring[]        = WIFI_ONCHIP_SILEX_RETURN_TEXT_RING;
const uint8_t g_wifi_onchip_silex_return_text_no_carrier[]  = WIFI_ONCHIP_SILEX_RETURN_TEXT_NO_CARRIER;
const uint8_t g_wifi_onchip_silex_return_text_error[]       = WIFI_ONCHIP_SILEX_RETURN_TEXT_ERROR;
const uint8_t g_wifi_onchip_silex_return_text_no_dialtone[] = WIFI_ONCHIP_SILEX_RETURN_TEXT_NO_DIALTONE;
const uint8_t g_wifi_onchip_silex_return_text_busy[]        = WIFI_ONCHIP_SILEX_RETURN_TEXT_BUSY;
const uint8_t g_wifi_onchip_silex_return_text_no_answer[]   = WIFI_ONCHIP_SILEX_RETURN_TEXT_NO_ANSWER;

/* Const strings used for return types in numeric version */
const uint8_t g_wifi_onchip_silex_return_numeric_ok[]          = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_OK;
const uint8_t g_wifi_onchip_silex_return_numeric_connect[]     = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_CONNECT;
const uint8_t g_wifi_onchip_silex_return_numeric_ring[]        = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_RING;
const uint8_t g_wifi_onchip_silex_return_numeric_no_carrier[]  = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_NO_CARRIER;
const uint8_t g_wifi_onchip_silex_return_numeric_error[]       = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_ERROR;
const uint8_t g_wifi_onchip_silex_return_numeric_no_dialtone[] = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_NO_DIALTONE;
const uint8_t g_wifi_onchip_silex_return_numeric_busy[]        = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_BUSY;
const uint8_t g_wifi_onchip_silex_return_numeric_no_answer[]   = WIFI_ONCHIP_SILEX_RETURN_NUMERIC_NO_ANSWER;

/* Const strings used for socket status */
const uint8_t g_wifi_onchip_silex_socket_status_closed[]    = WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_CLOSED;
const uint8_t g_wifi_onchip_silex_socket_status_socket[]    = WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_SOCKET;
const uint8_t g_wifi_onchip_silex_socket_status_bound[]     = WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_BOUND;
const uint8_t g_wifi_onchip_silex_socket_status_listen[]    = WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_LISTEN;
const uint8_t g_wifi_onchip_silex_socket_status_connected[] = WIFI_ONCHIP_SILEX_SOCKET_STATUS_TEXT_CONNECTED;
const uint8_t g_wifi_onchip_silex_return_dummy[]            = "";

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

/**
 *  Maximum time in ticks to wait for obtaining a semaphore.
 */
static const TickType_t wifi_sx_wifi_onchip_silex_sem_block_timeout = pdMS_TO_TICKS(
    WIFI_ONCHIP_SILEX_CFG_SEM_MAX_TIMEOUT);
#else
static const uint32_t wifi_sx_wifi_onchip_silex_sem_block_timeout = MS_TO_TICKS(WIFI_ONCHIP_SILEX_CFG_SEM_MAX_TIMEOUT);
#endif

/* Result code array used for AT command return parsing */
const uint8_t * const g_wifi_onchip_silex_result_code[][WIFI_ONCHIP_SILEX_MAX_AT_COMMAND_TYPES] =
{
    /* Text mode*/                  /* Numeric mode */
    {g_wifi_onchip_silex_return_text_ok,
     g_wifi_onchip_silex_return_numeric_ok},
    {g_wifi_onchip_silex_return_text_connect,
     g_wifi_onchip_silex_return_numeric_connect},
    {g_wifi_onchip_silex_return_text_ring,
     g_wifi_onchip_silex_return_numeric_ring},
    {g_wifi_onchip_silex_return_text_no_carrier,
     g_wifi_onchip_silex_return_numeric_no_carrier},
    {g_wifi_onchip_silex_return_text_error,
     g_wifi_onchip_silex_return_numeric_error},
    {g_wifi_onchip_silex_return_dummy,
     g_wifi_onchip_silex_return_dummy},
    {g_wifi_onchip_silex_return_text_no_dialtone,
     g_wifi_onchip_silex_return_numeric_no_dialtone},
    {g_wifi_onchip_silex_return_text_busy,
     g_wifi_onchip_silex_return_numeric_busy},
    {g_wifi_onchip_silex_return_text_no_answer,
     g_wifi_onchip_silex_return_numeric_no_answer},
};

/* Text return codes for socket status val */
const uint8_t * const g_wifi_onchip_silex_socket_status[] =
{
    g_wifi_onchip_silex_socket_status_closed,
    g_wifi_onchip_silex_socket_status_socket,
    g_wifi_onchip_silex_socket_status_bound,
    g_wifi_onchip_silex_socket_status_listen,
    g_wifi_onchip_silex_socket_status_connected,
};

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

/* Transmit and receive mutexes for UARTs */
static StaticSemaphore_t g_socket_mutexes[2];
static StaticSemaphore_t g_uart_tei_mutexes[2];
#endif

/* Control instance for the Silex wifi module */
static wifi_onchip_silex_instance_ctrl_t g_rm_wifi_onchip_silex_instance;

static rm_wifi_onchip_silex_baud_setting_t g_baud_setting_115200 =
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

/***********************************************************************************************************************
 * Private Function Definitions
 **********************************************************************************************************************/

fsp_err_t rm_wifi_onchip_silex_send_basic(wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl,
                                          uint32_t                            serial_ch_id,
                                          const char                        * p_textstring,
                                          uint32_t                            byte_timeout,
                                          uint32_t                            timeout_ms,
                                          sx_ulpgn_return_code_t              expect_code);

fsp_err_t rm_wifi_onchip_silex_send_basic_take_mutex(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl,
                                                     uint32_t                                  mutex_flag);

void rm_wifi_onchip_silex_send_basic_give_mutex(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl,
                                                uint32_t                                  mutex_flag);

static fsp_err_t rm_wifi_onchip_silex_change_socket_index(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl,
                                                          uint32_t                                  socket_no);

static fsp_err_t rm_wifi_onchip_silex_socket_init(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl);

static fsp_err_t rm_wifi_onchip_silex_get_ipaddress(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl);

static void rm_wifi_onchip_silex_wifi_module_reset(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl);

static void rm_wifi_onchip_silex_cleanup_open(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl);

#if (1 == WIFI_ONCHIP_SILEX_CFG_SNTP_ENABLE)
static fsp_err_t rm_wifi_onchip_silex_sntp_service_init(wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl);

#endif

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
size_t xStreamBufferReceiveAlternate(StreamBufferHandle_t xStreamBuffer,
                                     void               * pvRxData,
                                     size_t               xBufferLengthBytes,
                                     TickType_t           xTicksToWait);

#endif

static fsp_err_t rm_wifi_onchip_silex_send_scan(wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl,
                                                uint32_t                            serial_ch_id,
                                                bool                                send_scan_cmd,
                                                uint32_t                            byte_timeout,
                                                uint32_t                            timeout_ms);

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Opens and configures the WIFI_ONCHIP_SILEX Middleware module.
 *
 *  @param[in]  p_cfg        Pointer to pin configuration structure.
 *
 *  @retval FSP_SUCCESS              WIFI_ONCHIP_SILEX successfully configured.
 *  @retval FSP_ERR_ASSERTION        The parameter p_cfg or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_OUT_OF_MEMORY    There is no more heap memory available.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 *  @retval FSP_ERR_INVALID_ARGUMENT Parameter passed into function was invalid.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_open (wifi_onchip_silex_cfg_t const * const p_cfg)
{
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;
    fsp_err_t         err    = FSP_SUCCESS;
    uart_instance_t * p_uart = NULL;
    rm_wifi_onchip_silex_uart_extended_cfg_t uart0_cfg_extended_115200;
    uart_cfg_t uart0_cfg_115200;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(WIFI_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Clear the control structure*/
    memset(p_instance_ctrl, 0, sizeof(wifi_onchip_silex_instance_ctrl_t));

    /* Update control structure from configuration values */
    p_instance_ctrl->p_wifi_onchip_silex_cfg = p_cfg;
    p_instance_ctrl->num_uarts               = p_cfg->num_uarts;
    for (uint32_t i = 0; i < p_instance_ctrl->num_uarts; i++)
    {
        p_instance_ctrl->uart_instance_objects[i] = (uart_instance_t *) p_cfg->uart_instances[i];
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        p_instance_ctrl->uart_tei_sem[i] = xSemaphoreCreateBinaryStatic(&g_uart_tei_mutexes[i]);
        if (NULL == p_instance_ctrl->uart_tei_sem[i])
        {
            rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(NULL != p_instance_ctrl->uart_tei_sem[i], FSP_ERR_OUT_OF_MEMORY);
        xSemaphoreTake(p_instance_ctrl->uart_tei_sem[i], 0);
#else
        uint32_t status = tx_semaphore_create(&p_instance_ctrl->uart_tei_sem[i], "uart tei sem", 1);
        if (TX_SUCCESS != status)
        {
            rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
            FSP_ERROR_RETURN(TX_SUCCESS != status, FSP_ERR_WIFI_FAILED);
        }

        tx_semaphore_get(&p_instance_ctrl->uart_tei_sem[i], TX_NO_WAIT);

        status = tx_semaphore_create(&p_instance_ctrl->uart_rx_sem[i], "uart rx sem", 1);
        if (TX_SUCCESS != status)
        {
            rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
            FSP_ERROR_RETURN(TX_SUCCESS != status, FSP_ERR_WIFI_FAILED);
        }
        tx_semaphore_get(&p_instance_ctrl->uart_rx_sem[i], TX_NO_WAIT);
#endif
    }

    p_instance_ctrl->reset_pin             = p_cfg->reset_pin;
    p_instance_ctrl->num_creatable_sockets = p_cfg->num_sockets;
    p_instance_ctrl->curr_cmd_port         = WIFI_ONCHIP_SILEX_UART_INITIAL_PORT;
    p_instance_ctrl->tx_data_size          = WIFI_ONCHIP_SILEX_MAX_IP_FRAME_SIZE;
#if (BSP_CFG_RTOS == 1)
    p_instance_ctrl->p_current_packet_buffer = NULL;
    p_instance_ctrl->p_next_packet_buffer    = NULL;
    p_instance_ctrl->packet_buffer_size      = 0;
#endif

    /* Reset the wifi module to a known state */
    rm_wifi_onchip_silex_wifi_module_reset(p_instance_ctrl);

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

    /* Create the TX/RX mutexes */
    if (p_instance_ctrl->tx_sem != NULL)
    {
        vSemaphoreDelete(p_instance_ctrl->tx_sem);
    }

    p_instance_ctrl->tx_sem = xSemaphoreCreateMutexStatic(&g_socket_mutexes[0]);
    if (NULL == p_instance_ctrl->tx_sem)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->tx_sem, FSP_ERR_OUT_OF_MEMORY);

    if (p_instance_ctrl->rx_sem != NULL)
    {
        vSemaphoreDelete(p_instance_ctrl->rx_sem);
    }

    p_instance_ctrl->rx_sem = xSemaphoreCreateMutexStatic(&g_socket_mutexes[1]);
    if (NULL == p_instance_ctrl->rx_sem)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->rx_sem, FSP_ERR_OUT_OF_MEMORY);

    /* Create the stream buffer used to transfer UART data from ISR */
    p_instance_ctrl->socket_byteq_hdl = xStreamBufferCreateStatic(sizeof(p_instance_ctrl->cmd_rx_queue_buf),
                                                                  1,
                                                                  p_instance_ctrl->cmd_rx_queue_buf,
                                                                  &p_instance_ctrl->socket_byteq_struct);
    if (NULL == p_instance_ctrl->socket_byteq_hdl)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(NULL != p_instance_ctrl->socket_byteq_hdl, FSP_ERR_WIFI_FAILED);
#else
    uint32_t tx_status;
    tx_status = tx_mutex_create(&p_instance_ctrl->tx_sem, "tx mut", TX_INHERIT);
    if (TX_SUCCESS != tx_status)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        FSP_ERROR_RETURN(TX_SUCCESS != tx_status, FSP_ERR_WIFI_FAILED);
    }

    tx_status = tx_mutex_create(&p_instance_ctrl->rx_sem, "rx mut", TX_INHERIT);
    if (TX_SUCCESS != tx_status)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        FSP_ERROR_RETURN(TX_SUCCESS != tx_status, FSP_ERR_WIFI_FAILED);
    }

    tx_status = tx_semaphore_create(&p_instance_ctrl->uart_data_rx_start_sem, "uart rx sem", 1);
    if (TX_SUCCESS != tx_status)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        FSP_ERROR_RETURN(TX_SUCCESS != tx_status, FSP_ERR_WIFI_FAILED);
    }
    tx_semaphore_get(&p_instance_ctrl->uart_data_rx_start_sem, TX_NO_WAIT);
#endif

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_1SEC));
#else
    tx_thread_sleep(MS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_1SEC));
#endif

    /* Create memory copy of uart extended configuration and then copy new configuration values in. */
    memcpy((void *) &uart0_cfg_extended_115200,
           (void *) p_instance_ctrl->uart_instance_objects[0]->p_cfg->p_extend,
           sizeof(rm_wifi_onchip_silex_uart_extended_cfg_t));

    /* Create memory copy of uart configuration and update with new extended configuration structure. */
    memcpy((void *) &uart0_cfg_115200, p_instance_ctrl->uart_instance_objects[0]->p_cfg, sizeof(uart_cfg_t));
    p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT];
    (*p_sci_uart_baud_calculate)(WIFI_ONCHIP_SILEX_DEFAULT_BAUDRATE, WIFI_ONCHIP_SILEX_DEFAULT_MODULATION,
                                 WIFI_ONCHIP_SILEX_DEFAULT_ERROR, &g_baud_setting_115200);

    uart0_cfg_extended_115200.p_baud_setting   = &g_baud_setting_115200;
    uart0_cfg_extended_115200.flow_control     = RM_WIFI_ONCHIP_SILEX_SCI_UART_FLOW_CONTROL_RTS;
    uart0_cfg_extended_115200.flow_control_pin =
        (bsp_io_port_pin_t) WIFI_ONCHIP_SILEX_BSP_PIN_PORT_INVALID;

    uart0_cfg_115200.p_extend = (void *) &uart0_cfg_extended_115200;

    /* Open uart 1 with module default values for baud. 115200 and no hardware flow control. */
    err = p_uart->p_api->open(p_uart->p_ctrl, &uart0_cfg_115200);

    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_100MS));
#else
    tx_thread_sleep(MS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_100MS));
#endif

    p_instance_ctrl->at_cmd_mode       = 0;
    p_instance_ctrl->curr_socket_index = 0;

    /* Test basic communications with an AT command. */
    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "AT\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_10MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_400MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    /* Create string for wifi modem baud rate change. using currently unused socket RX buffer for temp string. */
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    uint8_t * p_temp_buff = p_instance_ctrl->sockets[0].socket_recv_buff;
    memset(p_instance_ctrl->sockets[0].socket_recv_buff, 0, sizeof(p_instance_ctrl->sockets[0].socket_recv_buff));
#else                                  // AzureRTOS
    uint8_t   temp_buff[WIFI_ONCHIP_SILEX_TEMPORARY_BUFFER_SIZE] = {0};
    uint8_t * p_temp_buff = temp_buff;
#endif

    strncat((char *) p_temp_buff, "ATB=", 5);
    strncat((char *) p_temp_buff, g_wifi_onchip_silex_uart_cmd_baud, 10);
    strncat((char *) p_temp_buff, ",,,,", 5);

    rm_wifi_onchip_silex_uart_extended_cfg_t * ext_cfg =
        (rm_wifi_onchip_silex_uart_extended_cfg_t *) p_instance_ctrl->uart_instance_objects[
            WIFI_ONCHIP_SILEX_UART_INITIAL_PORT]->p_cfg->p_extend;

    if (((uint32_t) ext_cfg->flow_control_pin != (uint32_t) WIFI_ONCHIP_SILEX_BSP_PIN_PORT_INVALID) ||
        (ext_cfg->flow_control == RM_WIFI_ONCHIP_SILEX_SCI_UART_FLOW_CONTROL_HARDWARE_CTSRTS))
    {
        strncat((char *) p_temp_buff, "h\r", 3);
    }
    else
    {
        strncat((char *) p_temp_buff, "n\r", 3);
    }

    /* Send reconfiguration AT command to wifi module */
    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (char *) p_temp_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_10MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_400MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);
    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    /* Close initial uart port */
    err =
        p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT]->p_api->close(
            p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT]->p_ctrl);

    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    /* Delay after close */
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_100MS));
#else
    tx_thread_sleep(MS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_100MS));
#endif

    /* Open first uart port with config values from the configurator */
    p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT];
    err    = p_uart->p_api->open(p_uart->p_ctrl, p_uart->p_cfg);

    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    /* Delay after open */
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_1SEC));
#else
    tx_thread_sleep(MS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_1SEC));
#endif

    /* Flush the uart channel */
    rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                    p_instance_ctrl->curr_cmd_port,
                                    "AT\r",
                                    WIFI_ONCHIP_SILEX_TIMEOUT_10MS,
                                    WIFI_ONCHIP_SILEX_TIMEOUT_400MS,
                                    WIFI_ONCHIP_SILEX_RETURN_OK);

    /* Turn off AT command echo */
    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATE0\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_10MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_400MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);
    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    /* Change to numeric command mode */
    p_instance_ctrl->at_cmd_mode = 1;

    /* Result code format = numeric */
    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATV0\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);
    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    /* Check if a second UART port was instantiated */
    if (2 == p_instance_ctrl->num_uarts)
    {
        /* Check HSUART2 connection */
        /* Command Port = HSUART2 */
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATUART=2\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_2SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
        if (FSP_SUCCESS != err)
        {
            rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        p_instance_ctrl->curr_cmd_port = WIFI_ONCHIP_SILEX_UART_SECOND_PORT;

        p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_SILEX_UART_SECOND_PORT];
        err    = p_uart->p_api->open(p_uart->p_ctrl, p_uart->p_cfg);

        /* Set uart enabled value */
        if (FSP_SUCCESS != err)
        {
            rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        /* Command Port = HSUART2, Data Port = HSUART1
         * Attempt to communicate with module on second UART */
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATV0\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_2SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        /* Turn off AT command echo */
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATE0\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_400MS,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
        if (FSP_SUCCESS != err)
        {
            rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        /* Change UART assignments for command and data */
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATUART=2,1\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_2SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
        if (FSP_SUCCESS != err)
        {
            rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
        }

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

        p_instance_ctrl->curr_cmd_port  = WIFI_ONCHIP_SILEX_UART_SECOND_PORT;
        p_instance_ctrl->curr_data_port = WIFI_ONCHIP_SILEX_UART_INITIAL_PORT;
    }
    else
    {
        p_instance_ctrl->num_creatable_sockets = 1;
        p_instance_ctrl->curr_cmd_port         = WIFI_ONCHIP_SILEX_UART_INITIAL_PORT;
        p_instance_ctrl->curr_data_port        = WIFI_ONCHIP_SILEX_UART_INITIAL_PORT;
        p_instance_ctrl->tx_data_size          = WIFI_ONCHIP_SILEX_MAX_IP_FRAME_SIZE;
    }

    rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                    p_instance_ctrl->curr_cmd_port,
                                    "ATS108?\r",
                                    WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                    WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                    WIFI_ONCHIP_SILEX_RETURN_OK);
    if (FSP_SUCCESS == err)
    {
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATS108=1\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_100MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_8SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
    }

    if (FSP_SUCCESS == err)
    {
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATS12=1\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_8SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
    }

    if (FSP_SUCCESS == err)
    {
        /* Set buffer size for socket receive */
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATBSIZE=1420\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
    }

    if (FSP_SUCCESS == err)
    {
        /* Disconnect from currently connected Access Point, */
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATWD\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
    }

    /* Enable DHCP */
    if (FSP_SUCCESS == err)
    {
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATNDHCP=1\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
    }

    if (FSP_SUCCESS == err)
    {
        err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATTO=1\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
    }

#if (1 == WIFI_ONCHIP_SILEX_CFG_SNTP_ENABLE)
    if ((FSP_SUCCESS == err) && p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_enabled)
    {
        p_instance_ctrl->open = WIFI_OPEN; // Allows interface calls to complete for SNTP init.
        err = rm_wifi_onchip_silex_sntp_service_init(p_instance_ctrl);
        p_instance_ctrl->open = 0;         // Reset open since this will be determined later
    }
#endif

    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

    p_instance_ctrl->curr_socket_index = 0;

    p_instance_ctrl->open = WIFI_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Disables WIFI_ONCHIP_SILEX.
 *
 *  @retval FSP_SUCCESS              WIFI_ONCHIP_SILEX closed successfully.
 *  @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_close ()
{
    uint32_t  mutex_flag;
    fsp_err_t err = FSP_SUCCESS;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    p_instance_ctrl->open = 0;

    /* If only one UART is used then send escape sequence command to exit transparent mode */
    if ((1 == p_instance_ctrl->num_uarts) &&
        (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
    {
#if (BSP_CFG_RTOS == 1)
        p_instance_ctrl->sockets[0].socket_status = WIFI_ONCHIP_SILEX_SOCKET_STATUS_CLOSED;
#endif
        rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                        p_instance_ctrl->curr_cmd_port,
                                        "+++",
                                        WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                        WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                        WIFI_ONCHIP_SILEX_RETURN_OK);
    }

    /* Tell wifi module to disconnect from the current AP */
    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATWD\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    if (FSP_SUCCESS != err)
    {
        rm_wifi_onchip_silex_wifi_module_reset(p_instance_ctrl);
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    rm_wifi_onchip_silex_cleanup_open(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Disconnects from connected AP.
 *
 *  @retval FSP_SUCCESS              WIFI_ONCHIP_SILEX disconnected successfully.
 *  @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_disconnect ()
{
    uint32_t mutex_flag;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    /* If only one UART is used then send escape sequence command to exit transparent mode */
    if ((1 == p_instance_ctrl->num_uarts) &&
        (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
    {
#if (BSP_CFG_RTOS == 1)
        p_instance_ctrl->sockets[0].socket_status = WIFI_ONCHIP_SILEX_SOCKET_STATUS_CLOSED;
#endif
        rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                        p_instance_ctrl->curr_cmd_port,
                                        "+++",
                                        WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                        WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                        WIFI_ONCHIP_SILEX_RETURN_OK);
    }

    /* Tell wifi module to disconnect from the current AP */
    rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                    p_instance_ctrl->curr_cmd_port,
                                    "ATWD\r",
                                    WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                    WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                    WIFI_ONCHIP_SILEX_RETURN_OK);

    memset(p_instance_ctrl->curr_ipaddr, 0, 4);
    memset(p_instance_ctrl->curr_subnetmask, 0, 4);
    memset(p_instance_ctrl->curr_gateway, 0, 4);

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Check if a specific socket instance is connected.
 *
 * @param[out]  p_status            Pointer to integer holding the socket connection status.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_status is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_socket_connected (fsp_err_t * p_status)
{
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
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
        *p_status = FSP_ERR_WIFI_FAILED;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Return the network information for the connection to the access point.
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
fsp_err_t rm_wifi_onchip_silex_network_info_get (uint32_t * p_ip_addr, uint32_t * p_subnet_mask, uint32_t * p_gateway)
{
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
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
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The parameter p_ssid or p_passphrase is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_INVALID_ARGUMENT No commas are accepted in the SSID or Passphrase.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_connect (const char * p_ssid, WIFISecurity_t security, const char * p_passphrase)
{
    fsp_err_t ret;
    char    * pstr;
    char    * pstr2;
    uint32_t  security_encrypt_type = 1;
    uint32_t  mutex_flag;
    fsp_err_t status = FSP_SUCCESS;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ssid);
    FSP_ASSERT(NULL != p_passphrase);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Commas are not accepted by the Silex WiFi module in the SSID or Passphrase */
    FSP_ERROR_RETURN((NULL == strchr(p_ssid, ',') && NULL == strchr(p_passphrase, ',')), FSP_ERR_INVALID_ARGUMENT); // NOLINT(clang-analyzer-security.insecureAPI.strchr) Disable warning about use of strcpy

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    rm_wifi_onchip_silex_socket_connected(&status);
    if (FSP_SUCCESS == status)
    {
        /* If Wifi is already connected, do nothing and return fail. */
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    memset(p_instance_ctrl->cmd_tx_buff, 0, sizeof(p_instance_ctrl->cmd_tx_buff));

    /* Turn off AT command echo */
    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATE0\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_400MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);
    if (FSP_SUCCESS != ret)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    /* Connect to an OPEN security AP */
    if (eWiFiSecurityOpen == security)
    {
        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "ATWA=", 6);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, p_ssid, wificonfigMAX_SSID_LEN);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, "\r", 2);
    }
    else if ((eWiFiSecurityWPA == security) || (eWiFiSecurityWPA2 == security))
    {
        /* Connect to an WPA security AP */

        strncpy((char *) p_instance_ctrl->cmd_tx_buff, "ATWAWPA=", 9);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, p_ssid, wificonfigMAX_SSID_LEN);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, ",", 2);

        if (security == eWiFiSecurityWPA)
        {
            strncat((char *) p_instance_ctrl->cmd_tx_buff, "1,", 3);
        }
        else
        {
            strncat((char *) p_instance_ctrl->cmd_tx_buff, "2,", 3);
        }

        if (security_encrypt_type == 1)
        {
            strncat((char *) p_instance_ctrl->cmd_tx_buff, "1,1,", 5);
        }
        else
        {
            strncat((char *) p_instance_ctrl->cmd_tx_buff, "0,0,", 5);
        }

        strncat((char *) p_instance_ctrl->cmd_tx_buff, p_passphrase, wificonfigMAX_PASSPHRASE_LEN);
        strncat((char *) p_instance_ctrl->cmd_tx_buff, "\r", 2);
    }
    else
    {
        /* Return with error for unsupported secuirty types */
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (char *) p_instance_ctrl->cmd_tx_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_20SEC,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    /* Clear password from command buffer before function return */
    memset(&p_instance_ctrl->cmd_tx_buff[0], 0, sizeof(p_instance_ctrl->cmd_tx_buff));

    if (FSP_SUCCESS == ret)
    {
        if (WIFI_ONCHIP_SILEX_RETURN_BUSY == (sx_ulpgn_return_code_t) ret)
        {
            ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                                  p_instance_ctrl->curr_cmd_port,
                                                  "ATW\r",
                                                  WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                                  WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                                  WIFI_ONCHIP_SILEX_RETURN_OK);
            if (FSP_SUCCESS == ret)
            {
                ret = (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;

                /* Test that connection was made to ssid passed in parameter */
                pstr = strstr((char *) p_instance_ctrl->cmd_rx_buff, "ssid         =   ");
                if (NULL != pstr)
                {
                    pstr2 = (char *) p_instance_ctrl->cmd_rx_buff + strlen("ssid         =   ");
                    pstr  = strstr(pstr2, "\r\n");
                    if (NULL != pstr)
                    {
                        *pstr = '\0';  // \r -> \0
                        if (0 == strcmp(pstr, p_ssid))
                        {
                            ret = FSP_SUCCESS;
                        }
                    }
                }
            }
        }

        if (FSP_SUCCESS == ret)
        {
            /* Call to get IP address does not always work the first time */
            for (int i = 0; i < 5; i++)
            {
                /* Get the device IP address */
                ret = rm_wifi_onchip_silex_get_ipaddress(p_instance_ctrl);
                if (FSP_SUCCESS == ret)
                {
                    /* Initialize the socket interface */
                    ret = rm_wifi_onchip_silex_socket_init(p_instance_ctrl);
                    break;
                }

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
                vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_8SEC));
#else
                tx_thread_sleep(MS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_8SEC));
#endif
            }
        }
    }
    else
    {
        /* Disconnect the current connection if we are already connected */
        rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                        p_instance_ctrl->curr_cmd_port,
                                        "ATWD\r",
                                        WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                        WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                        WIFI_ONCHIP_SILEX_RETURN_OK);

        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    rm_wifi_onchip_silex_socket_connected(&status);

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    FSP_ERROR_RETURN(FSP_SUCCESS == status, FSP_ERR_WIFI_FAILED);

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
fsp_err_t rm_wifi_onchip_silex_mac_addr_get (uint8_t * p_macaddr)
{
    fsp_err_t    ret;
    int32_t      err;
    unsigned int macaddr[6];
    uint32_t     mutex_flag;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_macaddr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);

    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    if (NULL == p_macaddr)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    /* Return an error if a socket is connected */
    if ((1 == p_instance_ctrl->num_uarts) &&
        (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATW\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_100MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3SEC,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    if (FSP_SUCCESS == ret)
    {
        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        err = sscanf((const char *) p_instance_ctrl->cmd_rx_buff,
                     "%*[^\n]\n%*[^\n]\n%*[^\n]\nMac Addr     =   %2x:%2x:%2x:%2x:%2x:%2x\r",
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

    if (FSP_SUCCESS != ret)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return FSP_SUCCESS;
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
fsp_err_t rm_wifi_onchip_silex_scan (WIFIScanResult_t * p_results, uint32_t maxNetworks)
{
    fsp_err_t ret;
    int32_t   err;
    uint32_t  idx = 0;
    uint8_t * bssid;
    uint32_t  mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_results);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    char * ptr = (char *) (p_instance_ctrl->cmd_rx_buff + 2);

    FSP_ERROR_RETURN((NULL != p_results) && (0 != maxNetworks), FSP_ERR_WIFI_FAILED);

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    /* Return an error if a socket is connected */
    if ((1 == p_instance_ctrl->num_uarts) &&
        (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    ret = rm_wifi_onchip_silex_send_scan(p_instance_ctrl,
                                         p_instance_ctrl->curr_cmd_port,
                                         true,
                                         WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                         WIFI_ONCHIP_SILEX_TIMEOUT_8SEC);

    /* Test if AT commands were successful */
    if (FSP_SUCCESS != ret)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    do
    {
        /* Test for end of list */
        p_results[idx].ucSSID[0] = '\0';
        int32_t test_ssid = strncmp(ptr, "ssid =", 6);
        if (0 != test_ssid)
        {
            break;
        }

        /* Copy SSID from scan info buffer */
        ptr += 7;
        int idx_ssid = 0;
        while ((*ptr != '\r') && (idx_ssid < (wificonfigMAX_SSID_LEN - 1)))
        {
            p_results[idx].ucSSID[idx_ssid++] = (uint8_t) *ptr;
            ptr++;
        }

        /* Advance string pointer to next section of scan info */
        ptr = strchr(ptr, '\n');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        /* BSSID */
        bssid = &p_results[idx].ucBSSID[0];
        unsigned int bssid2[6];
        memset(bssid2, 0, sizeof(bssid2));

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        err = sscanf(ptr,
                     "bssid = %x:%x:%x:%x:%x:%x\r",
                     &bssid2[0],
                     &bssid2[1],
                     &bssid2[2],
                     &bssid2[3],
                     &bssid2[4],
                     &bssid2[5]);
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
        ptr = strchr(ptr, '\n');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        uint32_t temp_val;

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        err = sscanf(ptr, "channel = %d\r", (int *) &temp_val);
        if (1 != err)
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        p_results[idx].ucChannel = (uint8_t) temp_val;

        /* Advance to string pointer next section of scan info */
        ptr = strchr(ptr, '\n');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        err = sscanf(ptr, "indicator = %d\r", (int *) &temp_val);
        if (1 != err)
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        p_results[idx].cRSSI = (int8_t) temp_val;

        /* Advance to string pointer next section of scan info */
        ptr = strchr(ptr, '\n');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            ret = FSP_ERR_WIFI_FAILED;
            break;
        }

        if (0 == strncmp(ptr, "security = NONE!", 16))
        {
            p_results[idx].xSecurity = eWiFiSecurityOpen;

            /* Advance string pointer to next section of scan info */
            ptr = strchr(ptr, '\n');
            if (NULL != ptr)
            {
                ptr++;
            }
            else
            {
                ret = FSP_ERR_WIFI_FAILED;
                break;
            }
        }
        else
        {
            /* Advance string pointer to next section of scan info */
            ptr = strchr(ptr, '\n');
            if (NULL != ptr)
            {
                ptr++;
            }
            else
            {
                ret = FSP_ERR_WIFI_FAILED;
                break;
            }

            if ('\r' != *(ptr))
            {
                if (0 == strncmp(ptr, "WPA", 3))
                {
                    p_results[idx].xSecurity = eWiFiSecurityWPA;
                }
                else if (0 == strncmp(ptr, "RSN/WPA2", 8))
                {
                    p_results[idx].xSecurity = eWiFiSecurityWPA2;
                }
                else
                {
                    /* Do Nothing */
                }

                /* Advance string pointer to next section of scan info */
                ptr = strchr(ptr, '\n');
                if (NULL != ptr)
                {
                    ptr++;
                }
                else
                {
                    ret = FSP_ERR_WIFI_FAILED;
                    break;
                }
            }
        }

        /* Advance string pointer to next section of scan info. Quite the loop if no more newlines */
        ptr = strchr(ptr, '\n');
        if (NULL != ptr)
        {
            ptr++;
        }
        else
        {
            break;
        }

        rm_wifi_onchip_silex_send_scan(p_instance_ctrl,
                                       p_instance_ctrl->curr_cmd_port,
                                       false,
                                       WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                       WIFI_ONCHIP_SILEX_TIMEOUT_8SEC);

        ptr = (char *) (p_instance_ctrl->cmd_rx_buff);
    } while (++idx < maxNetworks);

    /* Clear out the rest of the access points returned from the module */
    while (FSP_ERR_WIFI_FAILED !=
           rm_wifi_onchip_silex_send_scan(p_instance_ctrl, p_instance_ctrl->curr_cmd_port, false,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_1SEC, WIFI_ONCHIP_SILEX_TIMEOUT_8SEC))
    {
        ;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t rm_wifi_onchip_silex_ping (uint8_t * p_ip_addr, uint32_t count, uint32_t interval_ms)
{
    FSP_PARAMETER_NOT_USED(interval_ms);

    fsp_err_t ret = FSP_SUCCESS;
    uint32_t  i;
    uint32_t  mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN((FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag)),
                     FSP_ERR_WIFI_FAILED);

    sprintf((char *) p_instance_ctrl->cmd_tx_buff,
            "ATNPING=%d.%d.%d.%d\r",
            p_ip_addr[0],
            p_ip_addr[1],
            p_ip_addr[2],
            p_ip_addr[3]);

    /* Return an error if a socket is connected */
    if ((1 == p_instance_ctrl->num_uarts) &&
        (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    for (i = 0; i < count; i++)
    {
        ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              (char *) p_instance_ctrl->cmd_tx_buff,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_8SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);
        if (FSP_SUCCESS != ret)
        {
            break;
        }
    }

    if (FSP_SUCCESS != ret)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Get the assigned module IP address.
 *
 * @param[out]  p_ip_addr    Pointer an array to hold the IP address.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The parameter p_ip_addr is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_ip_addr_get (uint32_t * p_ip_addr)
{
    fsp_err_t    ret;
    int32_t      err;
    unsigned int temp_addr[4];
    uint32_t     i = 0;
    uint32_t     mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    char * buff = (char *) p_instance_ctrl->cmd_rx_buff;

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    /* Return an error if a socket is connected */
    if ((1 == p_instance_ctrl->num_uarts) &&
        (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATNSET?\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_30MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_5SEC,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    if (FSP_SUCCESS == ret)
    {
        if ((buff[0] == '\n') && (buff[1] == '\0'))
        {
            buff += 2;
        }

        err =

            // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
            sscanf((const char *) buff, "IP:%u.%u.%u.%u,", &temp_addr[0], &temp_addr[1], &temp_addr[2], &temp_addr[3]);

        if (4 == err)
        {
            for (i = 0; i < 4; i++)
            {
                if (temp_addr[i] <= UINT8_MAX)
                {
                    p_ip_addr[i] = (uint8_t) temp_addr[i];
                }
                else
                {
                    ret = FSP_ERR_WIFI_FAILED;
                    break;
                }
            }
        }
    }

    if (FSP_SUCCESS != ret)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return FSP_SUCCESS;
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
fsp_err_t rm_wifi_onchip_silex_avail_socket_get (uint32_t * p_socket_id)
{
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
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
fsp_err_t rm_wifi_onchip_silex_socket_status_get (uint32_t socket_no, uint32_t * p_socket_status)
{
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_socket_status);
    FSP_ASSERT(socket_no < p_instance_ctrl->num_creatable_sockets);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    *p_socket_status = p_instance_ctrl->sockets[socket_no].socket_status;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Shutdown portion of a socket
 *
 * @param[in]  socket_no          Socket ID number.
 * @param[in]  shutdown_channels    Specify if read or write channel is shutdown for socket
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        The parameter p_instance_ctrl is NULL. The value of socket_no
 *                                  is greater than/equal num_creatable_sockets.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
int32_t rm_wifi_onchip_silex_tcp_shutdown (uint32_t socket_no, uint32_t shutdown_channels)
{
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(socket_no < p_instance_ctrl->num_creatable_sockets);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (shutdown_channels & WIFI_ONCHIP_SILEX_SOCKET_READ)
    {
        p_instance_ctrl->sockets[socket_no].socket_read_write_flag &= ~((uint32_t) WIFI_ONCHIP_SILEX_SOCKET_READ); // clear read flag
    }

    if (shutdown_channels & WIFI_ONCHIP_SILEX_SOCKET_WRITE)
    {
        p_instance_ctrl->sockets[socket_no].socket_read_write_flag &= ~((uint32_t) WIFI_ONCHIP_SILEX_SOCKET_WRITE); // clear write flag
    }

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
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_socket_create (uint32_t socket_no, uint32_t type, uint32_t ipversion)
{
    fsp_err_t ret;
    uint32_t  mutex_flag;

    FSP_PARAMETER_NOT_USED(ipversion);

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(type <= WIFI_ONCHIP_SILEX_SOCKET_TYPE_MAX);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    if (1 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    if (2 == p_instance_ctrl->num_uarts)
    {
        ret = rm_wifi_onchip_silex_change_socket_index(p_instance_ctrl, socket_no);
        if (ret != FSP_SUCCESS)
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return FSP_ERR_WIFI_FAILED;
        }
    }

    /* If type is anything but 0 or 1 then assign type to UDP */
    if (1 >= type)
    {
        type = WIFI_ONCHIP_SILEX_SOCKET_TYPE_TCP; // TCP type selected
    }
    else
    {
        type = WIFI_ONCHIP_SILEX_SOCKET_TYPE_UDP; // UDP type selected
    }

    sprintf((char *) p_instance_ctrl->cmd_tx_buff, "ATNSOCK=%u,%u\r", (unsigned int) type, 4);

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (char *) p_instance_ctrl->cmd_tx_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_200MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);
    if ((FSP_SUCCESS != ret) && (WIFI_ONCHIP_SILEX_RETURN_BUSY != (sx_ulpgn_return_code_t) ret))
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return ret;
    }

    p_instance_ctrl->sockets[socket_no].socket_create_flag = 1;
    if (FSP_SUCCESS == ret)
    {
        p_instance_ctrl->sockets[socket_no].socket_status = WIFI_ONCHIP_SILEX_SOCKET_STATUS_SOCKET;

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        if (p_instance_ctrl->sockets[socket_no].socket_byteq_hdl)
        {
            BaseType_t reset_success = xStreamBufferReset(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl);
            if (pdPASS != reset_success)
            {
                /* Give back the socketInUse mutex. */
                rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

                return FSP_ERR_WIFI_FAILED;
            }
        }
#endif
    }

    /* Give back the socketInUse mutex. */
    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

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
fsp_err_t rm_wifi_onchip_silex_tcp_connect (uint32_t socket_no, uint32_t ipaddr, uint32_t port)
{
    fsp_err_t ret = FSP_SUCCESS;
    uint32_t  mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    if (0 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    if (2 == p_instance_ctrl->num_uarts)
    {
        ret = rm_wifi_onchip_silex_change_socket_index(p_instance_ctrl, socket_no);
        if (FSP_SUCCESS != ret)
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return FSP_ERR_WIFI_FAILED;
        }
    }

    memset(p_instance_ctrl->cmd_tx_buff, 0, sizeof(p_instance_ctrl->cmd_tx_buff));

    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.strcpy) Disable warning about use of strcpy
    strcpy((char *) p_instance_ctrl->cmd_tx_buff, "ATNCTCP=");
    sprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff), "%d.%d.%d.%d,%d\r",
            (uint8_t) (ipaddr >> 24), (uint8_t) (ipaddr >> 16), (uint8_t) (ipaddr >> 8), (uint8_t) (ipaddr),
            (int) port);

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (char *) p_instance_ctrl->cmd_tx_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_15SEC,
                                          WIFI_ONCHIP_SILEX_RETURN_CONNECT);

    if ((FSP_SUCCESS == ret) || (WIFI_ONCHIP_SILEX_RETURN_BUSY == (sx_ulpgn_return_code_t) ret) ||
        (WIFI_ONCHIP_SILEX_RETURN_CONNECT == (sx_ulpgn_return_code_t) ret))
    {
        p_instance_ctrl->sockets[socket_no].socket_status          = WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED;
        p_instance_ctrl->sockets[socket_no].socket_read_write_flag = WIFI_ONCHIP_SILEX_SOCKET_READ |
                                                                     WIFI_ONCHIP_SILEX_SOCKET_WRITE;
    }
    else
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Connect to a specific IP and Port using UDP socket.
 *
 * @param[in]  socket_no        Socket ID number.
 * @param[in]  ipaddr           IP address for socket connection. 0 if type is server.
 * @param[in]  port             Port number for socket connection.
 * @param[in]  type             Type of UDP connection. Can be client or server.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_udp_connect (uint32_t socket_no, uint32_t ipaddr, uint32_t port, uint32_t type)
{
    fsp_err_t ret = FSP_SUCCESS;
    uint32_t  mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    if (0 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    if (2 == p_instance_ctrl->num_uarts)
    {
        ret = rm_wifi_onchip_silex_change_socket_index(p_instance_ctrl, socket_no);
        if (FSP_SUCCESS != ret)
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return FSP_ERR_WIFI_FAILED;
        }
    }

    memset(p_instance_ctrl->cmd_tx_buff, 0, sizeof(p_instance_ctrl->cmd_tx_buff));

    if (type == 0)
    {
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.strcpy) Disable warning about use of strcpy
        strcpy((char *) p_instance_ctrl->cmd_tx_buff, "ATNCUDP=");
        sprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
                "%d.%d.%d.%d,%d\r",
                (uint8_t) (ipaddr >> 24),
                (uint8_t) (ipaddr >> 16),
                (uint8_t) (ipaddr >> 8),
                (uint8_t) (ipaddr),
                (int) port);
    }
    else
    {
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.strcpy) Disable warning about use of strcpy
        strcpy((char *) p_instance_ctrl->cmd_tx_buff, "ATNSUDP=");
        sprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff),
                "%d\r",
                (int) port);
    }

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (char *) p_instance_ctrl->cmd_tx_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_15SEC,
                                          WIFI_ONCHIP_SILEX_RETURN_CONNECT);

    if ((FSP_SUCCESS == ret) || (WIFI_ONCHIP_SILEX_RETURN_BUSY == (sx_ulpgn_return_code_t) ret) ||
        (WIFI_ONCHIP_SILEX_RETURN_CONNECT == (sx_ulpgn_return_code_t) ret))
    {
        p_instance_ctrl->sockets[socket_no].socket_status          = WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED;
        p_instance_ctrl->sockets[socket_no].socket_read_write_flag = WIFI_ONCHIP_SILEX_SOCKET_READ |
                                                                     WIFI_ONCHIP_SILEX_SOCKET_WRITE;
    }
    else
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
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
int32_t rm_wifi_onchip_silex_send (uint32_t socket_no, const uint8_t * p_data, uint32_t length, uint32_t timeout_ms)
{
    uint32_t  sent_count = 0;
    uint32_t  lenghttmp1;
    fsp_err_t ret;
    fsp_err_t err;
    uint32_t  mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* If socket write has been disabled by shutdown call then return 0 bytes sent. */
    if (!(p_instance_ctrl->sockets[socket_no].socket_read_write_flag & WIFI_ONCHIP_SILEX_SOCKET_WRITE))
    {
        return 0;
    }

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     WIFI_ONCHIP_SILEX_ERR_ERROR);

    if ((0 == p_instance_ctrl->sockets[socket_no].socket_create_flag) ||
        (WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED != p_instance_ctrl->sockets[socket_no].socket_status))
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return WIFI_ONCHIP_SILEX_ERR_ERROR;
    }

    if (2 == p_instance_ctrl->num_uarts)
    {
        if (socket_no != p_instance_ctrl->curr_socket_index)
        {
            if (FSP_SUCCESS != rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, WIFI_ONCHIP_SILEX_MUTEX_RX))
            {
                rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

                return WIFI_ONCHIP_SILEX_ERR_ERROR;
            }

            ret = rm_wifi_onchip_silex_change_socket_index(p_instance_ctrl, socket_no);

            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, WIFI_ONCHIP_SILEX_MUTEX_RX);
            if (FSP_SUCCESS != ret)
            {
                rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

                return WIFI_ONCHIP_SILEX_ERR_ERROR;
            }
        }
    }

    while (sent_count < length)
    {
        if (length - sent_count > WIFI_ONCHIP_SILEX_CFG_MAX_PACKET_SIZE)
        {
            lenghttmp1 = WIFI_ONCHIP_SILEX_CFG_MAX_PACKET_SIZE;
        }
        else
        {
            lenghttmp1 = length - sent_count;
        }

        err =
            p_instance_ctrl->uart_instance_objects[p_instance_ctrl->curr_data_port]->p_api->write(
                p_instance_ctrl->uart_instance_objects[p_instance_ctrl->curr_data_port]->p_ctrl,
                (uint8_t *) p_data + sent_count,
                lenghttmp1);
        if (FSP_SUCCESS != err)
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return WIFI_ONCHIP_SILEX_ERR_ERROR;
        }

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        if (pdFALSE ==
            xSemaphoreTake(p_instance_ctrl->uart_tei_sem[p_instance_ctrl->curr_data_port], pdMS_TO_TICKS(timeout_ms)))
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return WIFI_ONCHIP_SILEX_ERR_ERROR;
        }

#else
        if (tx_semaphore_get(&p_instance_ctrl->uart_tei_sem[p_instance_ctrl->curr_data_port], MS_TO_TICKS(timeout_ms)))
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return WIFI_ONCHIP_SILEX_ERR_ERROR;
        }
#endif

        sent_count += lenghttmp1;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return (int32_t) sent_count;
}

/*******************************************************************************************************************//**
 *  Receive data over TCP from a server.
 *
 * @param[in]  socket_no        Socket ID number.
 * @param[out]  p_data            Pointer to data received from socket.
 * @param[in]  length           Length of data array used for receive.
 * @param[in]  timeout_ms       Timeout to wait for data to be received from socket.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_NOT_OPEN         The instance has not been opened.
 * @retval FSP_ERR_ASSERTION        The p_instance_ctrl or parameter p_data is NULL.
 **********************************************************************************************************************/
int32_t rm_wifi_onchip_silex_recv (uint32_t socket_no, uint8_t * p_data, uint32_t length, uint32_t timeout_ms)
{
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    uint32_t  recvcnt = 0;
    int32_t   ret     = 0;
    fsp_err_t err;
    uint32_t  mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

 #if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* If socket read has been disabled by shutdown call then return 0 bytes received. */
    if (!(p_instance_ctrl->sockets[socket_no].socket_read_write_flag & WIFI_ONCHIP_SILEX_SOCKET_READ))
    {
        return 0;
    }

    /* Take the receive mutex */
    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     WIFI_ONCHIP_SILEX_ERR_ERROR);

    /* Recv data if using 2 UARTS */
    if (2 == p_instance_ctrl->num_uarts)
    {
        /* Check is socket has been initialized */
        if ((0 == p_instance_ctrl->sockets[socket_no].socket_create_flag) ||
            (WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED != p_instance_ctrl->sockets[socket_no].socket_status))
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return WIFI_ONCHIP_SILEX_ERR_ERROR;
        }

        /* Change socket index if needed */
        if (socket_no != p_instance_ctrl->curr_socket_index)
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);
            FSP_ERROR_RETURN(FSP_SUCCESS ==
                             rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl,
                                                                        (WIFI_ONCHIP_SILEX_MUTEX_RX |
                                                                         WIFI_ONCHIP_SILEX_MUTEX_TX)),
                             WIFI_ONCHIP_SILEX_ERR_ERROR);

            err = rm_wifi_onchip_silex_change_socket_index(p_instance_ctrl, socket_no);

            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, WIFI_ONCHIP_SILEX_MUTEX_TX);

            if (FSP_SUCCESS != err)
            {
                rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

                return WIFI_ONCHIP_SILEX_ERR_ERROR;
            }
        }

        /* Get first byte or timeout */
        size_t xReceivedBytes =
            xStreamBufferReceiveAlternate(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl,
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
                    xStreamBufferReceiveAlternate(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl,
                                                  (p_data + recvcnt), num_bytes_left,
                                                  pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_10MS));

                if (xReceivedBytes > 0)
                {
                    recvcnt += xReceivedBytes;
                }
                else
                {
                    ret = (int32_t) recvcnt;
                    break;
                }
            }                          /* For */
        }
        else
        {
            ret = 0;                   // timeout occurred
        }

        /* Reset the trigger level for socket stream buffer */
        xStreamBufferSetTriggerLevel(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl, 1);
    }
    else                               /* Num uarts = 1 */
    {
        if (0 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
        {
            rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

            return WIFI_ONCHIP_SILEX_ERR_ERROR;
        }

        volatile size_t xReceivedBytes =
            xStreamBufferReceiveAlternate(p_instance_ctrl->socket_byteq_hdl, (p_data + recvcnt), 1,
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

                xStreamBufferSetTriggerLevel(p_instance_ctrl->socket_byteq_hdl, num_bytes_left);

                xReceivedBytes = xStreamBufferReceiveAlternate(p_instance_ctrl->socket_byteq_hdl,
                                                               (p_data + recvcnt),
                                                               num_bytes_left,
                                                               pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_10MS));

                if (xReceivedBytes > 0)
                {
                    recvcnt += xReceivedBytes;
                }
                else
                {
                    ret = (int32_t) recvcnt;
                    break;
                }
            }                          /* For */
        }
        else
        {
            ret = 0;                   // Timeout occurred
        }

        /* Reset the trigger level for socket stream buffer */
        xStreamBufferSetTriggerLevel(p_instance_ctrl->socket_byteq_hdl, 1);
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return ret;
#else
    FSP_PARAMETER_NOT_USED(socket_no);
    FSP_PARAMETER_NOT_USED(p_data);
    FSP_PARAMETER_NOT_USED(length);
    FSP_PARAMETER_NOT_USED(timeout_ms);

    return FSP_ERR_UNSUPPORTED;
#endif
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
fsp_err_t rm_wifi_onchip_silex_socket_disconnect (uint32_t socket_no)
{
    fsp_err_t ret = FSP_SUCCESS;
    uint32_t  mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Test if socket has been created for socket index passed in to function */
    if (1 == p_instance_ctrl->sockets[socket_no].socket_create_flag)
    {
        mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
        FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                         FSP_ERR_WIFI_FAILED);

        /* Switch socket index if necessary */
        if ((p_instance_ctrl->num_uarts == 2) && (p_instance_ctrl->curr_socket_index != socket_no))
        {
            ret = rm_wifi_onchip_silex_change_socket_index(p_instance_ctrl, socket_no);
            if (FSP_SUCCESS != ret)
            {
                rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

                return FSP_ERR_WIFI_FAILED;
            }
        }

        /* If only one UART is used then send escape sequence command */
        if ((1 == p_instance_ctrl->num_uarts) &&
            (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
        {
#if (BSP_CFG_RTOS == 1)
            p_instance_ctrl->sockets[0].socket_status = WIFI_ONCHIP_SILEX_SOCKET_STATUS_CLOSED;
#endif
            rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                            p_instance_ctrl->curr_cmd_port,
                                            "+++",
                                            WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                            WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                            WIFI_ONCHIP_SILEX_RETURN_OK);
        }

        /* Close the socket using ATNCLOSE command */
        ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                              p_instance_ctrl->curr_cmd_port,
                                              "ATNCLOSE\r",
                                              WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                              WIFI_ONCHIP_SILEX_TIMEOUT_1SEC,
                                              WIFI_ONCHIP_SILEX_RETURN_OK);

        /* Release the mutexes acquired previously */
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        /* Clear the create flag, set status to closed, and flush the stream buffer */
        if (FSP_SUCCESS == ret)
        {
            p_instance_ctrl->sockets[socket_no].socket_create_flag     = 0;
            p_instance_ctrl->sockets[socket_no].socket_status          = WIFI_ONCHIP_SILEX_SOCKET_STATUS_CLOSED;
            p_instance_ctrl->sockets[socket_no].socket_read_write_flag = 0;

            if (p_instance_ctrl->num_uarts == 2)
            {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
                BaseType_t reset_success = xStreamBufferReset(p_instance_ctrl->sockets[socket_no].socket_byteq_hdl);
                if (reset_success != pdPASS)
                {
                    return FSP_ERR_WIFI_FAILED;
                }
#endif
            }
        }
        else
        {
            return FSP_ERR_WIFI_FAILED;
        }
    }
    else
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

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
fsp_err_t rm_wifi_onchip_silex_dns_query (const char * p_textstring, uint8_t * p_ip_addr)
{
    unsigned int result;
    fsp_err_t    func_ret;
    int32_t      scanf_ret;
    unsigned int temp_addr[4];
    int32_t      i = 0;
    uint32_t     mutex_flag;

    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_textstring);
    FSP_ASSERT(NULL != p_ip_addr);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((sizeof(p_instance_ctrl->cmd_tx_buff) - 16) > strlen(p_textstring), FSP_ERR_INVALID_ARGUMENT)
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.strcpy) Disable warning about use of strcpy
    strcpy((char *) p_instance_ctrl->cmd_tx_buff, "ATNDNSQUERY=");
    sprintf((char *) p_instance_ctrl->cmd_tx_buff + strlen((char *) p_instance_ctrl->cmd_tx_buff), "%s\r",
            p_textstring);

    /* Return an error if a socket is connected */
    if ((1 == p_instance_ctrl->num_uarts) &&
        (p_instance_ctrl->sockets[0].socket_status == WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED))
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    func_ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                               p_instance_ctrl->curr_cmd_port,
                                               (char *) p_instance_ctrl->cmd_tx_buff,
                                               WIFI_ONCHIP_SILEX_TIMEOUT_300MS,
                                               WIFI_ONCHIP_SILEX_TIMEOUT_3SEC,
                                               WIFI_ONCHIP_SILEX_RETURN_OK);

    if (FSP_SUCCESS == func_ret)
    {
        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        scanf_ret = sscanf((const char *) p_instance_ctrl->cmd_rx_buff,
                           "%u\r\n%u.%u.%u.%u\r\n",
                           &result,
                           &temp_addr[0],
                           &temp_addr[1],
                           &temp_addr[2],
                           &temp_addr[3]);

        if ((scanf_ret == 5) && (result == 1))
        {
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
        else
        {
            func_ret = FSP_ERR_WIFI_FAILED;
        }
    }

    if (FSP_SUCCESS != func_ret)
    {
        rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

        return FSP_ERR_WIFI_FAILED;
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return FSP_SUCCESS;
}

#if (BSP_CFG_RTOS == 1)

/*******************************************************************************************************************//**
 *  Initialize packet buffers with packet pointers and set the size of the packet.
 *
 * @param[in]  p_current_packet_buffer   Starting packet buffer address to read packets into.
 * @param[in]  p_next_packet_buffer      Packet buffer address to switch to after initial packet is full.
 * @param[in]  packet_buffer_size        Size to read into each packet.
 **********************************************************************************************************************/
void rm_wifi_onchip_silex_initialize_packet_buffers (uint8_t * p_current_packet_buffer,
                                                     uint8_t * p_next_packet_buffer,
                                                     uint32_t  packet_buffer_size)
{
    g_rm_wifi_onchip_silex_instance.p_current_packet_buffer = p_current_packet_buffer;
    g_rm_wifi_onchip_silex_instance.p_next_packet_buffer    = p_next_packet_buffer;
    g_rm_wifi_onchip_silex_instance.packet_buffer_size      = packet_buffer_size;
}

/*******************************************************************************************************************//**
 *  Set next packet buffer pointer.
 *
 * @param[in]  p_next_packet_buffer         Packet buffer address to switch to after current packet is full.
 **********************************************************************************************************************/
void rm_wifi_onchip_silex_set_next_packet_buffer (uint8_t * p_next_packet_buffer)
{
    g_rm_wifi_onchip_silex_instance.p_next_packet_buffer = p_next_packet_buffer;
}

/*******************************************************************************************************************//**
 *  Advance current packet buffer pointer to the next packet buffer pointer.
 **********************************************************************************************************************/
void rm_wifi_onchip_silex_move_to_next_packet_buffer (void)
{
    g_rm_wifi_onchip_silex_instance.p_current_packet_buffer = g_rm_wifi_onchip_silex_instance.p_next_packet_buffer;
}

/*******************************************************************************************************************//**
 *  Change the current socket index.
 *
 * @param[in]  socket_no      Socket index number to change to.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 *
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_change_socket (uint32_t socket_no)
{
    if ((g_rm_wifi_onchip_silex_instance.num_uarts == 1) ||
        (g_rm_wifi_onchip_silex_instance.curr_socket_index == socket_no))
    {
        return FSP_SUCCESS;
    }

    return rm_wifi_onchip_silex_change_socket_index(&g_rm_wifi_onchip_silex_instance, socket_no);
}

/*******************************************************************************************************************//**
 *  Cancel the current read operation over UART. Return the number of bytes received.
 *
 * @param[in,out]  bytes_received    Location to store number of bytes recieved.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 *
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_stop_tcp_recv (uint32_t * bytes_received)
{
    fsp_err_t err;
    uint32_t  remaining_bytes;

    uart_instance_t * p_uart_instance =
        g_rm_wifi_onchip_silex_instance.uart_instance_objects[g_rm_wifi_onchip_silex_instance.curr_data_port];

    err = p_uart_instance->p_api->readStop(p_uart_instance->p_ctrl, &remaining_bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    *bytes_received = g_rm_wifi_onchip_silex_instance.packet_buffer_size - remaining_bytes;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Get the recieve start semaphore for the module.
 *
 * @param[in]  wait_option              How long to wait for the semaphore, this accepts the
 *                                      same values as the wait_option for tx_semaphore_get.
 *
 * @retval See tx_semaphore_get return values.
 *
 **********************************************************************************************************************/
UINT rm_wifi_onchip_silex_get_rx_start_semaphore (ULONG wait_option)
{
    return tx_semaphore_get(&g_rm_wifi_onchip_silex_instance.uart_data_rx_start_sem, wait_option);
}

/*******************************************************************************************************************//**
 *  Get the recieve complete (packet filled) semaphore for the module.
 *
 * @param[in]  wait_option              How long to wait for the semaphore, this accepts the
 *                                      same values as the wait_option for tx_semaphore_get.
 *
 * @retval See tx_semaphore_get return values.
 *
 **********************************************************************************************************************/
UINT rm_wifi_onchip_silex_get_rx_complete_semaphore (ULONG wait_option)
{
    return tx_semaphore_get(&g_rm_wifi_onchip_silex_instance.uart_rx_sem[g_rm_wifi_onchip_silex_instance.
                                                                         curr_data_port],
                            wait_option);
}

/*******************************************************************************************************************//**
 *  Retrieve the current socket index.
 *
 * @retval The current socket index
 *
 **********************************************************************************************************************/
uint32_t rm_wifi_onchip_silex_get_current_socket_index ()
{
    uint32_t index = g_rm_wifi_onchip_silex_instance.curr_socket_index;

    return index;
}

#endif

/***********************************************************************************************************************
 * Private Functions Implementation
 **********************************************************************************************************************/

static void rm_wifi_onchip_silex_cleanup_open (wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl)
{
#if (BSP_CFG_RTOS == 2)                // FreeRTOS

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

    if (NULL != p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT])
    {
        vSemaphoreDelete(p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT]);
        p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT] = NULL;
    }

    if (NULL != p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_SECOND_PORT])
    {
        vSemaphoreDelete(p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_SECOND_PORT]);
        p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_SECOND_PORT] = NULL;
    }

    /* Clean up the stream buffers that were allocated */
    for (int i = 0; i < WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS; i++)
    {
        if (p_instance_ctrl->sockets[i].socket_byteq_hdl)
        {
            vStreamBufferDelete(p_instance_ctrl->sockets[i].socket_byteq_hdl);
            p_instance_ctrl->sockets[i].socket_byteq_hdl = NULL;
        }
    }

#else
    tx_semaphore_delete(&p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT]);
    tx_semaphore_delete(&p_instance_ctrl->uart_tei_sem[WIFI_ONCHIP_SILEX_UART_SECOND_PORT]);
    tx_semaphore_delete(&p_instance_ctrl->uart_rx_sem[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT]);
    tx_semaphore_delete(&p_instance_ctrl->uart_rx_sem[WIFI_ONCHIP_SILEX_UART_SECOND_PORT]);
    tx_semaphore_delete(&p_instance_ctrl->uart_data_rx_start_sem);
    tx_mutex_delete(&p_instance_ctrl->tx_sem);
    tx_mutex_delete(&p_instance_ctrl->rx_sem);
#endif

    uart_instance_t * p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_SILEX_UART_INITIAL_PORT];
    if (SCIU_OPEN == ((rm_wifi_onchip_silex_uart_instance_ctrl_t *) p_uart->p_ctrl)->open)
    {
        p_uart->p_api->close(p_uart->p_ctrl);
    }

    p_uart = p_instance_ctrl->uart_instance_objects[WIFI_ONCHIP_SILEX_UART_SECOND_PORT];
    if (SCIU_OPEN == ((rm_wifi_onchip_silex_uart_instance_ctrl_t *) p_uart->p_ctrl)->open)
    {
        p_uart->p_api->close(p_uart->p_ctrl);
    }
}

static void rm_wifi_onchip_silex_wifi_module_reset (wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl)
{
    /* Reset the wifi module. */
    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, p_instance_ctrl->reset_pin, BSP_IO_LEVEL_LOW);
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_25MS));
#else
    tx_thread_sleep(MS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_25MS));
#endif
    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, p_instance_ctrl->reset_pin, BSP_IO_LEVEL_HIGH);
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    vTaskDelay(pdMS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_1MS));
#else
    tx_thread_sleep(MS_TO_TICKS(WIFI_ONCHIP_SILEX_TIMEOUT_1MS));
#endif
}

/*******************************************************************************************************************//**
 *  Get the IP address from the module.
 *
 * @param[in]  p_instance_ctrl      Pointer to the control structure.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_onchip_silex_get_ipaddress (wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl)
{
    int       ipaddr[4];
    int       subnetmask[4];
    int       gateway[4];
    fsp_err_t func_ret;
    int32_t   scanf_ret;

    func_ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                               p_instance_ctrl->curr_cmd_port,
                                               "ATNSET=\?\r",
                                               WIFI_ONCHIP_SILEX_TIMEOUT_100MS,
                                               WIFI_ONCHIP_SILEX_TIMEOUT_100MS,
                                               WIFI_ONCHIP_SILEX_RETURN_OK);

    FSP_ERROR_RETURN(FSP_SUCCESS == func_ret, (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR);

    // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
    scanf_ret = sscanf((const char *) p_instance_ctrl->cmd_rx_buff,
                       "IP:%d.%d.%d.%d, Mask:%d.%d.%d.%d, Gateway:%d.%d.%d.%d\r\n",
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

    FSP_ERROR_RETURN(12 == scanf_ret, (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR);

    FSP_ERROR_RETURN(0 != (ipaddr[0] | ipaddr[1] | ipaddr[2] | ipaddr[3]), (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR);

    for (int i = 0; i < 4; i++)
    {
        p_instance_ctrl->curr_ipaddr[i]     = (uint8_t) ipaddr[i];
        p_instance_ctrl->curr_subnetmask[i] = (uint8_t) subnetmask[i];
        p_instance_ctrl->curr_gateway[i]    = (uint8_t) gateway[i];
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Take the mutex for the send basic call.
 *
 *  @param[in] p_instance_ctrl      Pointer to control instance.
 *  @param[in] mutex_flag           Flags for the mutex.
 *
 *  @retval FSP_SUCCESS             Function completed successfully.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_send_basic_take_mutex (wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl,
                                                      uint32_t                            mutex_flag)
{
    if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_TX))
    {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        if (xSemaphoreTake(p_instance_ctrl->tx_sem,
                           (wifi_sx_wifi_onchip_silex_sem_block_timeout / portTICK_PERIOD_MS)) != pdTRUE)
        {
            return (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;
        }

#else
        if (tx_mutex_get(&p_instance_ctrl->tx_sem, wifi_sx_wifi_onchip_silex_sem_block_timeout))
        {
            return (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;
        }
#endif
    }

    if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_RX))
    {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        if (xSemaphoreTake(p_instance_ctrl->rx_sem,
                           (wifi_sx_wifi_onchip_silex_sem_block_timeout / portTICK_PERIOD_MS)) != pdTRUE)
        {
            if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_TX))
            {
                xSemaphoreGive(p_instance_ctrl->tx_sem);
            }

            return (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;
        }

#else
        if (tx_mutex_get(&p_instance_ctrl->rx_sem, wifi_sx_wifi_onchip_silex_sem_block_timeout))
        {
            if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_TX))
            {
                tx_mutex_put(&p_instance_ctrl->tx_sem);
            }

            return (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;
        }
#endif
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Give the mutex for the send basic call.
 *
 *  @param[in] p_instance_ctrl      Pointer to control instance.
 *  @param[in] mutex_flag           Flags for the mutex.
 *
 *  @retval FSP_SUCCESS             Function completed successfully.
 **********************************************************************************************************************/
void rm_wifi_onchip_silex_send_basic_give_mutex (wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl,
                                                 uint32_t                            mutex_flag)
{
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_RX))
    {
        xSemaphoreGive(p_instance_ctrl->rx_sem);
    }

    if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_TX))
    {
        xSemaphoreGive(p_instance_ctrl->tx_sem);
    }

#else
    if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_RX))
    {
        tx_mutex_put(&p_instance_ctrl->rx_sem);
    }

    if (0 != (mutex_flag & WIFI_ONCHIP_SILEX_MUTEX_TX))
    {
        tx_mutex_put(&p_instance_ctrl->tx_sem);
    }
#endif
}

/*******************************************************************************************************************//**
 *  Send and receive an AT command with testing for return.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 * @param[in]  serial_ch_id           Pointer to IP address returned from look up.
 * @param[in]  p_textstring           Pointer to IP address returned from look up.
 * @param[in]  byte_timeout           Pointer to IP address returned from look up.
 * @param[in]  timeout_ms           Pointer to IP address returned from look up.
 * @param[in]  expect_code           Pointer to IP address returned from look up.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
fsp_err_t rm_wifi_onchip_silex_send_basic (wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl,
                                           uint32_t                            serial_ch_id,
                                           const char                        * p_textstring,
                                           uint32_t                            byte_timeout,
                                           uint32_t                            timeout_ms,
                                           sx_ulpgn_return_code_t              expect_code)
{
    fsp_err_t err;
    uint32_t  recvcnt = 0;
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    uint8_t  receive_data;
    uint32_t last_data_cnt = 0;
#else
    ULONG byte_timeout_ticks = MS_TO_TICKS(byte_timeout);
    ULONG timeout_ticks      = MS_TO_TICKS(timeout_ms);

    /* Make sure timeouts are at least 2 ticks */
    if (timeout_ticks < WIFI_ONCHIP_SILEX_TIMEOUT_MIN_TICKS)
    {
        timeout_ticks = WIFI_ONCHIP_SILEX_TIMEOUT_MIN_TICKS;
    }

    if (byte_timeout_ticks < WIFI_ONCHIP_SILEX_TIMEOUT_MIN_TICKS)
    {
        byte_timeout_ticks = WIFI_ONCHIP_SILEX_TIMEOUT_MIN_TICKS;
    }
#endif
    uint32_t retry_count;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_textstring);
#endif

    for (retry_count = 0; retry_count < WIFI_ONCHIP_SILEX_CFG_MAX_RETRIES_UART_COMMS; retry_count++)
    {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        last_data_cnt = 0;
#else
        p_instance_ctrl->current_cmd_buffer_index = 0;
#endif

        memset(p_instance_ctrl->last_data, 0, sizeof(p_instance_ctrl->last_data));
        memset(p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

        if (p_textstring != NULL)
        {
            recvcnt = 0;
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
            if (uxQueueMessagesWaiting((QueueHandle_t) p_instance_ctrl->uart_tei_sem[serial_ch_id]) !=
                0)
            {
                return FSP_ERR_WIFI_FAILED;
            }
#endif

            err = p_instance_ctrl->uart_instance_objects[serial_ch_id]->p_api->write(
                p_instance_ctrl->uart_instance_objects[serial_ch_id]->p_ctrl,
                (uint8_t *) &p_textstring[0],
                strlen(p_textstring));
            FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
            FSP_ERROR_RETURN(pdTRUE ==
                             xSemaphoreTake(p_instance_ctrl->uart_tei_sem[serial_ch_id],
                                            (timeout_ms / portTICK_PERIOD_MS)),
                             FSP_ERR_WIFI_FAILED);
#else
            FSP_ERROR_RETURN(TX_SUCCESS ==
                             tx_semaphore_get(&p_instance_ctrl->uart_tei_sem[serial_ch_id], MS_TO_TICKS(timeout_ticks)),
                             FSP_ERR_WIFI_FAILED);
#endif
        }
        else
        {
            return FSP_ERR_WIFI_FAILED;
        }

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

        /* Detect the first transmitted byte from the message */
        size_t xReceivedBytes = xStreamBufferReceiveAlternate(p_instance_ctrl->socket_byteq_hdl,
                                                              &receive_data,
                                                              1,
                                                              pdMS_TO_TICKS(timeout_ms));

        if (xReceivedBytes == 1)
        {
            p_instance_ctrl->cmd_rx_buff[recvcnt] = receive_data;
            recvcnt++;

            if (last_data_cnt < (WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH - 2))
            {
                p_instance_ctrl->last_data[last_data_cnt] = receive_data;
                last_data_cnt++;
            }
            else
            {
                memmove(&p_instance_ctrl->last_data[0],
                        &p_instance_ctrl->last_data[1],
                        WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH - 2);
                last_data_cnt--;
                p_instance_ctrl->last_data[last_data_cnt] = receive_data;
                last_data_cnt++;
            }

            /* Get the rest of the transmitted message from the stream buffer */
            xStreamBufferSetTriggerLevel(p_instance_ctrl->socket_byteq_hdl,
                                         sizeof(p_instance_ctrl->cmd_rx_buff) - recvcnt);

            xReceivedBytes = xStreamBufferReceiveAlternate(p_instance_ctrl->socket_byteq_hdl,
                                                           &p_instance_ctrl->cmd_rx_buff[recvcnt],
                                                           sizeof(p_instance_ctrl->cmd_rx_buff) - recvcnt,
                                                           pdMS_TO_TICKS(byte_timeout));
            xStreamBufferSetTriggerLevel(p_instance_ctrl->socket_byteq_hdl, 1);

            if (xReceivedBytes > 0)
            {
                for (unsigned int i = 0; i < xReceivedBytes; i++)
                {
                    if (last_data_cnt < (WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH - 2))
                    {
                        p_instance_ctrl->last_data[last_data_cnt] = p_instance_ctrl->cmd_rx_buff[recvcnt];
                    }
                    else
                    {
                        memmove(&p_instance_ctrl->last_data[0],
                                &p_instance_ctrl->last_data[1],
                                WIFI_ONCHIP_SILEX_RETURN_TEXT_LENGTH - 2);
                        last_data_cnt--;
                        p_instance_ctrl->last_data[last_data_cnt] = p_instance_ctrl->cmd_rx_buff[recvcnt];
                    }

                    last_data_cnt++;
                    recvcnt++;
                }
            }
            else
            {
                return FSP_SUCCESS;
            }
        }
        else
        {
            return FSP_ERR_WIFI_FAILED;
        }

        /* Response data check */
        FSP_ERROR_RETURN(recvcnt >=
                         strlen((const char *) g_wifi_onchip_silex_result_code[expect_code][p_instance_ctrl->at_cmd_mode
                                ]),
                         FSP_ERR_WIFI_FAILED);

        if (0 !=
            strncmp((const char *) &p_instance_ctrl->last_data[last_data_cnt -
                                                               strlen((const char *) g_wifi_onchip_silex_result_code[
                                                                          expect_code][
                                                                          p_instance_ctrl->at_cmd_mode])],
                    (const char *) g_wifi_onchip_silex_result_code[expect_code][p_instance_ctrl->at_cmd_mode],
                    strlen((const char *) g_wifi_onchip_silex_result_code[expect_code][p_instance_ctrl->at_cmd_mode])))
        {
            if (0 ==
                strncmp((const char *) &p_instance_ctrl->last_data[last_data_cnt -
                                                                   strlen((const char *) g_wifi_onchip_silex_result_code
                                                                          [expect_code
                                                                          ][
                                                                              p_instance_ctrl->at_cmd_mode])],
                        (const char *) g_wifi_onchip_silex_result_code[WIFI_ONCHIP_SILEX_RETURN_BUSY][p_instance_ctrl->
                                                                                                      at_cmd_mode],
                        strlen((const char *) g_wifi_onchip_silex_result_code[WIFI_ONCHIP_SILEX_RETURN_BUSY][
                                   p_instance_ctrl->at_cmd_mode])))
            {

                /* Busy */
                return (fsp_err_t) WIFI_ONCHIP_SILEX_RETURN_BUSY;
            }

#else                                  // AzureRTOS

        /* Wait for first byte */
        if (TX_NO_INSTANCE ==
            tx_semaphore_get(&p_instance_ctrl->uart_rx_sem[p_instance_ctrl->curr_cmd_port], timeout_ms))
        {
            continue;
        }

        recvcnt++;

        for ( ; ; )
        {
            /* Wait for the rest of the response */
            if (TX_SUCCESS ==
                tx_semaphore_get(&p_instance_ctrl->uart_rx_sem[p_instance_ctrl->curr_cmd_port], byte_timeout))
            {
                /* Next byte recieved */
                recvcnt++;
            }
            else
            {
                /* Byte timed out */
                FSP_CRITICAL_SECTION_DEFINE;
                FSP_CRITICAL_SECTION_ENTER;

                /* Get semaphore again in case operation completed between semaphore timeout and critical section entry */
                UINT semaphore_err = tx_semaphore_get(&p_instance_ctrl->uart_rx_sem[p_instance_ctrl->curr_cmd_port],
                                                      TX_NO_WAIT);

                if (TX_NO_INSTANCE == semaphore_err)
                {
                    /* No more data at the moment */
                    uart_instance_t * p_uart_instance =
                        p_instance_ctrl->uart_instance_objects[p_instance_ctrl->curr_cmd_port];

                    p_uart_instance->p_api->communicationAbort(p_uart_instance->p_ctrl, UART_DIR_RX);
                }
                else
                {
                    /* Got another byte */
                    recvcnt++;
                }

                FSP_CRITICAL_SECTION_EXIT;

                if (TX_NO_INSTANCE == semaphore_err)
                {
                    break;
                }
            }
        }

        char * p_response_string =
            (char *) &p_instance_ctrl->cmd_rx_buff[recvcnt -
                                                   strlen((const char *) g_wifi_onchip_silex_result_code[expect_code][
                                                              p_instance_ctrl->at_cmd_mode])];

        /* Response data check */
        FSP_ERROR_RETURN(recvcnt >=
                         strlen((const char *) g_wifi_onchip_silex_result_code[expect_code][p_instance_ctrl->at_cmd_mode
                                ]),
                         FSP_ERR_WIFI_FAILED);

        if (0 !=
            strncmp(p_response_string,
                    (const char *) g_wifi_onchip_silex_result_code[expect_code][p_instance_ctrl->at_cmd_mode],
                    strlen((const char *) g_wifi_onchip_silex_result_code[expect_code][p_instance_ctrl->at_cmd_mode])))
        {
            if (0 ==
                strncmp(p_response_string,
                        (const char *) g_wifi_onchip_silex_result_code[WIFI_ONCHIP_SILEX_RETURN_BUSY][p_instance_ctrl->
                                                                                                      at_cmd_mode],
                        strlen((const char *) g_wifi_onchip_silex_result_code[WIFI_ONCHIP_SILEX_RETURN_BUSY][
                                   p_instance_ctrl->at_cmd_mode])))
            {

                /* Busy */
                return (fsp_err_t) WIFI_ONCHIP_SILEX_RETURN_BUSY;
            }
#endif

            FSP_ERROR_RETURN(WIFI_ONCHIP_SILEX_CFG_MAX_RETRIES_UART_COMMS != (retry_count + 1), FSP_ERR_WIFI_FAILED);
        }
        else
        {
            /* Success */
            break;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Send and receive wifi scan command.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 * @param[in]  serial_ch_id         Uart channel ID.
 * @param[in]  send_scan_cmd        Enable or disable the AT command transmit.
 * @param[in]  byte_timeout         Timeout value between bytes received.
 * @param[in]  timeout_ms           Timeout value before first byte received.
 *
 * @retval FSP_SUCCESS                   Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED           Error occurred with command to Wifi module.
 * @retval FSP_ERR_WIFI_SCAN_COMPLETE    All scan data have been received from the module.
 *
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_onchip_silex_send_scan (wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl,
                                                 uint32_t                            serial_ch_id,
                                                 bool                                send_scan_cmd,
                                                 uint32_t                            byte_timeout,
                                                 uint32_t                            timeout_ms)
{
    fsp_err_t err;
    uint32_t  recvcnt = 0;
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    uint8_t receive_data;
#else
    p_instance_ctrl->current_cmd_buffer_index = 0;
#endif

    memset(&p_instance_ctrl->cmd_rx_buff, 0, sizeof(p_instance_ctrl->cmd_rx_buff));

    if (true == send_scan_cmd)
    {
        recvcnt = 0;

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        if (uxQueueMessagesWaiting((QueueHandle_t) p_instance_ctrl->uart_tei_sem[serial_ch_id]) !=
            0)
        {
            return FSP_ERR_WIFI_FAILED;
        }
#endif

        err =
            p_instance_ctrl->uart_instance_objects[serial_ch_id]->p_api->write(p_instance_ctrl->uart_instance_objects[
                                                                                   serial_ch_id]->p_ctrl,
                                                                               (uint8_t *) "ATWS\r",
                                                                               5);

        FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WIFI_FAILED);
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
        FSP_ERROR_RETURN(pdTRUE ==
                         xSemaphoreTake(p_instance_ctrl->uart_tei_sem[serial_ch_id], (timeout_ms / portTICK_PERIOD_MS)),
                         FSP_ERR_WIFI_FAILED);
#else
        FSP_ERROR_RETURN(TX_SUCCESS ==
                         tx_semaphore_get(&p_instance_ctrl->uart_tei_sem[serial_ch_id], MS_TO_TICKS(timeout_ms)),
                         FSP_ERR_WIFI_FAILED);
#endif
    }

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

    /* Detect the first transmitted byte from the message */
    size_t xReceivedBytes = xStreamBufferReceiveAlternate(p_instance_ctrl->socket_byteq_hdl,
                                                          &receive_data,
                                                          1,
                                                          pdMS_TO_TICKS(timeout_ms));

    if (xReceivedBytes == 1)
    {
        p_instance_ctrl->cmd_rx_buff[recvcnt++] = receive_data;

        while (xReceivedBytes == 1)
        {
            xReceivedBytes = xStreamBufferReceiveAlternate(p_instance_ctrl->socket_byteq_hdl,
                                                           &receive_data,
                                                           1,
                                                           pdMS_TO_TICKS(byte_timeout));

            if (xReceivedBytes == 1)
            {
                p_instance_ctrl->cmd_rx_buff[recvcnt++] = receive_data;

                /* Return success if a access point has been returned. */
                if ((recvcnt >= 4) &&
                    (0 == strncmp((const char *) &p_instance_ctrl->cmd_rx_buff[recvcnt - 4], "\r\n\r\n", 4)))
                {
                    return FSP_SUCCESS;
                }

                /* Return success if the last access point has been returned. */
                if ((recvcnt >= 3) &&
                    (0 == strncmp((const char *) &p_instance_ctrl->cmd_rx_buff[recvcnt - 3], "\r\n0", 3)))
                {
                    return FSP_ERR_WIFI_SCAN_COMPLETE;
                }
            }
            else
            {
                return FSP_ERR_WIFI_FAILED;
            }
        }
    }
    else
    {
        return FSP_ERR_WIFI_FAILED;
    }

#else                                  // AzureRTOS

    /* Wait for first byte */
    if (TX_NO_INSTANCE ==
        tx_semaphore_get(&p_instance_ctrl->uart_rx_sem[p_instance_ctrl->curr_cmd_port], MS_TO_TICKS(timeout_ms)))
    {
        return FSP_ERR_WIFI_FAILED;
    }

    recvcnt++;

    for ( ; ; )
    {
        /* Wait for the rest of the response */
        if (TX_SUCCESS ==
            tx_semaphore_get(&p_instance_ctrl->uart_rx_sem[p_instance_ctrl->curr_cmd_port], MS_TO_TICKS(byte_timeout)))
        {
            /* Next byte recieved */
            recvcnt++;
        }
        else
        {
            /* Byte timed out */
            FSP_CRITICAL_SECTION_DEFINE;
            FSP_CRITICAL_SECTION_ENTER;

            /* Get semaphore again in case operation completed between semaphore timeout and critical section entry */
            UINT semaphore_err = tx_semaphore_get(&p_instance_ctrl->uart_rx_sem[p_instance_ctrl->curr_cmd_port],
                                                  TX_NO_WAIT);

            if (TX_NO_INSTANCE == semaphore_err)
            {
                /* No more data at the moment */
                uart_instance_t * p_uart_instance =
                    p_instance_ctrl->uart_instance_objects[p_instance_ctrl->curr_cmd_port];

                p_uart_instance->p_api->communicationAbort(p_uart_instance->p_ctrl, UART_DIR_RX);
            }
            else
            {
                /* Got another byte */
                recvcnt++;
            }

            FSP_CRITICAL_SECTION_EXIT;

            if (TX_NO_INSTANCE == semaphore_err)
            {
                break;
            }
        }
    }

    /* Return success if a access point has been returned. */
    if ((recvcnt >= 4) &&
        (0 == strncmp((const char *) &p_instance_ctrl->cmd_rx_buff[recvcnt - 4], "\r\n\r\n", 4)))
    {
        return FSP_SUCCESS;
    }

    /* Return success if the last access point has been returned. */
    if ((recvcnt >= 3) &&
        (0 == strncmp((const char *) &p_instance_ctrl->cmd_rx_buff[recvcnt - 3], "\r\n0", 3)))
    {
        return FSP_ERR_WIFI_SCAN_COMPLETE;
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Change the socket index.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 * @param[in]  socket_no            Number of socket to change to.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_onchip_silex_change_socket_index (wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl,
                                                           uint32_t                            socket_no)
{
    fsp_err_t ret = FSP_SUCCESS;

    if (p_instance_ctrl->num_uarts == 2)
    {
        if (socket_no != p_instance_ctrl->curr_socket_index) // Only attempt change if socket number is different than current.
        {
#if (BSP_CFG_RTOS == 1)
            rm_wifi_onchip_silex_uart_instance_ctrl_t * p_data_port_uart_ctrl =
                (rm_wifi_onchip_silex_uart_instance_ctrl_t *) p_instance_ctrl->uart_instance_objects[p_instance_ctrl->
                                                                                                     curr_data_port]->
                p_ctrl;

            /* Set flow control in order to pause data over data port. */
            R_BSP_PinAccessEnable();
            R_BSP_PinWrite(p_data_port_uart_ctrl->flow_pin, BSP_IO_LEVEL_HIGH);
#endif

            for (int i = 0; i < WIFI_ONCHIP_SILEX_MAX_SOCKET_INDEX_RETRIES; i++) // Retry to change socket index number max 10 times.
            {
                sprintf((char *) p_instance_ctrl->cmd_tx_buff, "ATNSOCKINDEX=%d\r", (int) socket_no);
                ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                                      p_instance_ctrl->curr_cmd_port,
                                                      (char *) p_instance_ctrl->cmd_tx_buff,
                                                      WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                                      WIFI_ONCHIP_SILEX_TIMEOUT_4SEC,
                                                      WIFI_ONCHIP_SILEX_RETURN_OK);

                if (FSP_SUCCESS == ret)
                {
                    if (p_instance_ctrl->cmd_rx_buff[1] == '\r')
                    {
                        switch (p_instance_ctrl->cmd_rx_buff[0])
                        {
                            case WIFI_ONCHIP_SILEX_ERR_BUSY_CHAR:
                            {
                                ret = (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_BUSY;
                                break;
                            }

                            case WIFI_ONCHIP_SILEX_ERR_NO_SUPPORT_CHAR:
                            {
                                ret = (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;
                                break;
                            }

                            case WIFI_ONCHIP_SILEX_ERR_NONE_CHAR:
                            {
                                p_instance_ctrl->curr_socket_index = socket_no;

                                ret = FSP_SUCCESS;
                                break;
                            }

                            default:
                            {
                                ret = (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;
                                break;
                            }
                        }

                        if (ret == WIFI_ONCHIP_SILEX_ERR_BUSY)
                        {
                            continue;
                        }

#if (BSP_CFG_RTOS == 1)

                        /* Clear flow control in order to resume data over data port. */
                        R_BSP_PinWrite(p_data_port_uart_ctrl->flow_pin, BSP_IO_LEVEL_LOW);
                        R_BSP_PinAccessDisable();
#endif

                        if ((int) ret == WIFI_ONCHIP_SILEX_ERR_ERROR)
                        {
                            break;
                        }

                        if (FSP_SUCCESS == ret)
                        {
                            return FSP_SUCCESS;
                        }
                    }
                    else               // UNKNOWN ERROR
                    {
                        return (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_UNKNOWN;
                    }
                }
                else                   // Module comms error.
                {
                    return (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_COMMS;
                }
            }
        }
    }
    else
    {
        return (fsp_err_t) WIFI_ONCHIP_SILEX_ERR_ERROR;
    }

    return ret;
}

/*******************************************************************************************************************//**
 *  Initialize the sockets interface.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 **********************************************************************************************************************/
static fsp_err_t rm_wifi_onchip_silex_socket_init (wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl)
{
    if (2 == p_instance_ctrl->num_uarts)
    {
        for (uint32_t i = 0; i < p_instance_ctrl->num_creatable_sockets; i++)
        {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
            p_instance_ctrl->sockets[i].socket_byteq_hdl =
                xStreamBufferCreateStatic(sizeof(p_instance_ctrl->sockets[i].socket_recv_buff),
                                          1,
                                          p_instance_ctrl->sockets[i].socket_recv_buff,
                                          &p_instance_ctrl->sockets[i].socket_byteq_struct);

            FSP_ERROR_RETURN(NULL != p_instance_ctrl->sockets[i].socket_byteq_hdl, FSP_ERR_WIFI_FAILED);
#endif
        }
    }

    /* Success. */
    return FSP_SUCCESS;
}

void rm_wifi_onchip_silex_uart_callback (uart_callback_args_t * p_args)
{
#if (BSP_CFG_RTOS == 2)                            // FreeRTOS
    BaseType_t xHigherPriorityTaskWoken = pdFALSE; // Initialized to pdFALSE.
#endif
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;
    uint32_t uart_context_index = 0;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    if (NULL == p_args)
    {
        return;
    }
#endif

    if ((NULL != p_instance_ctrl->uart_instance_objects[1]) &&
        (p_args->channel == p_instance_ctrl->uart_instance_objects[1]->p_cfg->channel))
    {
        uart_context_index = 1;
    }

    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
            if (uart_context_index == WIFI_ONCHIP_SILEX_UART_INITIAL_PORT)
            {
                /* Handle event from UART 0 */
                if ((0 == p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_create_flag) ||
                    (p_instance_ctrl->num_uarts == 1))
                {
                    uint8_t data_byte = (uint8_t) p_args->data;
                    xStreamBufferSendFromISR(p_instance_ctrl->socket_byteq_hdl, &data_byte, 1,
                                             &xHigherPriorityTaskWoken);
                }
                else
                {
                    uint8_t data_byte = (uint8_t) p_args->data;
                    size_t  send_size =
                        xStreamBufferSendFromISR(
                            p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_byteq_hdl,
                            &data_byte,
                            1,
                            &xHigherPriorityTaskWoken);
                    if (1 != send_size)
                    {
                        p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_recv_error_count++;
                    }
                }
            }
            else if (uart_context_index == WIFI_ONCHIP_SILEX_UART_SECOND_PORT)
            {
                /* Handle event from UART1 */
                uint8_t data_byte = (uint8_t) p_args->data;
                xStreamBufferSendFromISR(p_instance_ctrl->socket_byteq_hdl, &data_byte, 1, &xHigherPriorityTaskWoken);
            }
            else
            {
                /* Do Nothing */
            }

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#else                                  // AzureRTOS
            uart_instance_t * p_uart_instance = p_instance_ctrl->uart_instance_objects[uart_context_index];

            /* Check if socket is connected */
            if ((WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED !=
                 p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_status) ||
                (uart_context_index == WIFI_ONCHIP_SILEX_UART_SECOND_PORT))
            {
                /* Socket isn't connected, data should go to command buffer */
                p_instance_ctrl->cmd_rx_buff[p_instance_ctrl->current_cmd_buffer_index] = (uint8_t) p_args->data;
                p_instance_ctrl->current_cmd_buffer_index++;
                p_uart_instance->p_api->read(p_uart_instance->p_ctrl,
                                             &p_instance_ctrl->cmd_rx_buff[p_instance_ctrl->current_cmd_buffer_index],
                                             1);

                /* Notify that reception has started */
                tx_semaphore_put(&p_instance_ctrl->uart_rx_sem[uart_context_index]);
            }
            else
            {
                /* If we don't have a packet buffer then don't recieve anything */
                if (NULL == p_instance_ctrl->p_current_packet_buffer)
                {
                    break;
                }

                /* Socket is connected, data should go to packet buffer */
                p_uart_instance->p_api->read(p_uart_instance->p_ctrl,
                                             &p_instance_ctrl->p_current_packet_buffer[1],
                                             p_instance_ctrl->packet_buffer_size - 1);

                p_instance_ctrl->p_current_packet_buffer[0] = (uint8_t) p_args->data;

                /* Notify that reception has started */
                tx_semaphore_put(&p_instance_ctrl->uart_data_rx_start_sem);
            }
#endif

            break;
        }

#if (BSP_CFG_RTOS == 1)                // AzureRTOS
        case UART_EVENT_RX_COMPLETE:
        {
            uart_instance_t * p_uart_instance = p_instance_ctrl->uart_instance_objects[uart_context_index];

            /* Check if socket is open and UART port is the data port */
            if ((WIFI_ONCHIP_SILEX_SOCKET_STATUS_CONNECTED ==
                 p_instance_ctrl->sockets[p_instance_ctrl->curr_socket_index].socket_status) &&
                (uart_context_index == WIFI_ONCHIP_SILEX_UART_INITIAL_PORT))
            {
                /* Packet buffer has been filled, move to next one */
                p_instance_ctrl->p_current_packet_buffer = p_instance_ctrl->p_next_packet_buffer;

                /* If we don't have a packet buffer then don't recieve anything */
                if (NULL == p_instance_ctrl->p_current_packet_buffer)
                {
                    break;
                }

                /* Start recieving next packet */
                p_uart_instance->p_api->read(p_uart_instance->p_ctrl,
                                             p_instance_ctrl->p_current_packet_buffer,
                                             p_instance_ctrl->packet_buffer_size);
            }
            else
            {
                /* Read next byte to command buffer */
                p_instance_ctrl->current_cmd_buffer_index++;
                p_uart_instance->p_api->read(p_uart_instance->p_ctrl,
                                             &p_instance_ctrl->cmd_rx_buff[p_instance_ctrl->current_cmd_buffer_index],
                                             1);
            }

            /* Notify that reception has completed */
            tx_semaphore_put(&p_instance_ctrl->uart_rx_sem[uart_context_index]);

            break;
        }
#endif

        case UART_EVENT_TX_DATA_EMPTY:
        {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS
            if ((0 ==
                 uxQueueMessagesWaitingFromISR((QueueHandle_t) p_instance_ctrl->uart_tei_sem[uart_context_index])))
            {
                xSemaphoreGiveFromISR(p_instance_ctrl->uart_tei_sem[uart_context_index], &xHigherPriorityTaskWoken);
            }

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#else
            tx_semaphore_put(&p_instance_ctrl->uart_tei_sem[uart_context_index]);
#endif

            break;
        }

        default:
        {
            /* Do Nothing */
        }
    }
}

/*******************************************************************************************************************//**
 *  Initialize silex module SNTP client service.
 *
 * @param[in]  p_instance_ctrl      Pointer to array holding URL to query from DNS.
 *
 * @retval FSP_SUCCESS              Function completed successfully.
 * @retval FSP_ERR_ASSERTION        Assertion error occurred.
 * @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 * @retval FSP_ERR_INVALID_ARGUMENT Parameter passed into function was invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
#if (1 == WIFI_ONCHIP_SILEX_CFG_SNTP_ENABLE)
static fsp_err_t rm_wifi_onchip_silex_sntp_service_init (wifi_onchip_silex_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t   ip_address_sntp_server[4] = {0, 0, 0, 0};
    int32_t   err_scan;

    /* Enable/disable the SNTP clinet */
    err = RM_WIFI_ONCHIP_SILEX_SntpEnableSet(p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_enabled);

    /* Set the SNTP server IP address */
    if ((FSP_SUCCESS == err) && (1 == p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_enabled))
    {
        err_scan =

            // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
            sscanf((const char *) p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_server_ip,
                   "%u.%u.%u.%u,",
                   (unsigned int *) &ip_address_sntp_server[0],
                   (unsigned int *) &ip_address_sntp_server[1],
                   (unsigned int *) &ip_address_sntp_server[2],
                   (unsigned int *) &ip_address_sntp_server[3]);

        if (4 == err_scan)
        {
            err = RM_WIFI_ONCHIP_SILEX_SntpServerIpAddressSet((uint8_t *) ip_address_sntp_server);
        }
    }

    /* Set the SNTP Timezone configuration string */
    if ((FSP_SUCCESS == err) && (1 == p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_enabled))
    {
        err = RM_WIFI_ONCHIP_SILEX_SntpTimeZoneSet(
            p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_timezone_offset_from_utc_hours,
            p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_timezone_offset_from_utc_minutes,
            p_instance_ctrl->p_wifi_onchip_silex_cfg->sntp_timezone_use_daylight_savings);
    }

    return err;
}

#endif

/*! \endcond */

/*******************************************************************************************************************//**
 * @addtogroup WIFI_ONCHIP_SILEX WIFI_ONCHIP_SILEX
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This will retrieve time info from an NTP server at the address entered via an during configuration. If the server
 * isn’t set or the client isn’t enabled, then it will return an error. The date/time is retrieved as the number of
 * seconds since 00:00:00 UTC January 1, 1970
 *
 *  @param[out]  p_utc_time          Returns the epoch time in seconds.
 *
 *  @retval FSP_SUCCESS              Successfully retrieved the system time from module.
 *  @retval FSP_ERR_ASSERTION        The parameter utc_time or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_EpochTimeGet (time_t * p_utc_time)
{
    uint32_t  mutex_flag;
    fsp_err_t ret;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_utc_time);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATNTPTIMESEC=?\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_100MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_500MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    if (FSP_SUCCESS == ret)
    {
        // NOLINTNEXTLINE(cert-err34-c) Disable warning about the use of sscanf
        sscanf((const char *) p_instance_ctrl->cmd_rx_buff, "%u", (unsigned int *) p_utc_time);
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return ret;
}

/*******************************************************************************************************************//**
 *  Get the current local time based on current timezone in a string . Exp: Wed Oct 15 1975 07:06:00
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
fsp_err_t RM_WIFI_ONCHIP_SILEX_LocalTimeGet (uint8_t * p_local_time, uint32_t size_string)
{
    uint32_t  mutex_flag;
    fsp_err_t ret;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_local_time);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(RM_WIFI_ONCHIP_SILEX_MIN_LOCAL_TIME_STRING_SIZE <= size_string, FSP_ERR_INVALID_SIZE);
#endif

    /* Take mutexes */
    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    memset(p_local_time, 0, size_string);

    ret = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          "ATNTPTIME=?\r",
                                          WIFI_ONCHIP_SILEX_TIMEOUT_100MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_500MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    if (FSP_SUCCESS == ret)
    {
        /* Copy local time and crop out only the date/time string */
        strncpy((char *) p_local_time, (const char *) p_instance_ctrl->cmd_rx_buff, size_string);
        char * cr_loc = strchr((char *) p_local_time, '\r');
        cr_loc[0] = '\0';
    }

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return ret;
}

/*******************************************************************************************************************//**
 *  Set the SNTP Client to Enable or Disable
 *
 *  @param[in]  enable           Can be set to enable/disable for SNTP support.
 *
 *  @retval FSP_SUCCESS              Successfully set the value.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_SntpEnableSet (wifi_onchip_silex_sntp_enable_t enable)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);

    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    uint8_t * p_temp_buff = p_instance_ctrl->sockets[0].socket_recv_buff;
    size_t    buff_size   = sizeof(p_instance_ctrl->sockets[0].socket_recv_buff);
#else                                  // AzureRTOS
    uint8_t   temp_buff[WIFI_ONCHIP_SILEX_TEMPORARY_BUFFER_SIZE] = {0};
    uint8_t * p_temp_buff = temp_buff;
    size_t    buff_size   = sizeof(temp_buff);
#endif

    snprintf((char *) p_temp_buff, buff_size, "ATNTPCLIENT=%u\r", (unsigned int) enable);

    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (const char *) p_temp_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_500MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return err;
}

/*******************************************************************************************************************//**
 *  Set the SNTP Client Server IP Address
 *
 *  @param[in]  p_ip_address         Pointer to IP address of SNTP server in byte array format.
 *
 *  @retval FSP_SUCCESS              Successfully set the value.
 *  @retval FSP_ERR_ASSERTION        The parameter p_ip_address or p_instance_ctrl is NULL.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_SntpServerIpAddressSet (uint8_t * p_ip_address)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ASSERT(NULL != p_ip_address);
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);

    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    uint8_t * p_temp_buff = p_instance_ctrl->sockets[0].socket_recv_buff;
    size_t    buff_size   = sizeof(p_instance_ctrl->sockets[0].socket_recv_buff);
#else                                  // AzureRTOS
    uint8_t   temp_buff[WIFI_ONCHIP_SILEX_TEMPORARY_BUFFER_SIZE] = {0};
    uint8_t * p_temp_buff = temp_buff;
    size_t    buff_size   = sizeof(temp_buff);
#endif

    snprintf((char *) p_temp_buff, buff_size, "ATNTPSRVR=%u.%u.%u.%u\r", p_ip_address[0], p_ip_address[1],
             p_ip_address[2], p_ip_address[3]);

    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (const char *) p_temp_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_500MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return err;
}

/*******************************************************************************************************************//**
 *  Set the SNTP Client Timezone
 *
 *  @param[in]  hours                 Number of hours (+/-) used for timezone offset from GMT.
 *  @param[in]  minutes               Number of minutes used for timezone offset from GMT.
 *  @param[in]  daylightSavingsEnable Enable/Disable daylight saving in the timezone calculation.
 *
 *  @retval FSP_SUCCESS              Successfully set the value.
 *  @retval FSP_ERR_WIFI_FAILED      Error occurred with command to Wifi module.
 *  @retval FSP_ERR_NOT_OPEN         Module is not open.
 *  @retval FSP_ERR_INVALID_ARGUMENT Parameter passed into function was invalid.
 **********************************************************************************************************************/
fsp_err_t RM_WIFI_ONCHIP_SILEX_SntpTimeZoneSet (int32_t                                          hours,
                                                uint32_t                                         minutes,
                                                wifi_onchip_silex_sntp_daylight_savings_enable_t daylightSavingsEnable)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mutex_flag;
    wifi_onchip_silex_instance_ctrl_t * p_instance_ctrl = &g_rm_wifi_onchip_silex_instance;

#if (WIFI_ONCHIP_SILEX_CFG_PARAM_CHECKING_ENABLED == 1)
    FSP_ERROR_RETURN(WIFI_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(((hours >= -12) && (hours <= 12)), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((minutes <= 59), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(!(((hours == -12) || (hours == 12)) && (minutes > 0)), FSP_ERR_INVALID_ARGUMENT);
#endif

    mutex_flag = (WIFI_ONCHIP_SILEX_MUTEX_TX | WIFI_ONCHIP_SILEX_MUTEX_RX);

    FSP_ERROR_RETURN(FSP_SUCCESS == rm_wifi_onchip_silex_send_basic_take_mutex(p_instance_ctrl, mutex_flag),
                     FSP_ERR_WIFI_FAILED);

    uint32_t is_positive = 0;

    if (0 <= hours)
    {
        is_positive = 1;
    }
    else
    {
        hours = -hours;
    }

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    uint8_t * p_temp_buff = p_instance_ctrl->sockets[0].socket_recv_buff;
    size_t    buff_size   = sizeof(p_instance_ctrl->sockets[0].socket_recv_buff);
#else                                  // AzureRTOS
    uint8_t   temp_buff[WIFI_ONCHIP_SILEX_TEMPORARY_BUFFER_SIZE] = {0};
    uint8_t * p_temp_buff = temp_buff;
    size_t    buff_size   = sizeof(temp_buff);
#endif

    snprintf((char *) p_temp_buff, buff_size, "ATNTPZONE=%d,%u,%u,%u\r", (int) hours, (unsigned int) minutes,
             (unsigned int) is_positive, (unsigned int) daylightSavingsEnable);

    err = rm_wifi_onchip_silex_send_basic(p_instance_ctrl,
                                          p_instance_ctrl->curr_cmd_port,
                                          (const char *) p_temp_buff,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_3MS,
                                          WIFI_ONCHIP_SILEX_TIMEOUT_500MS,
                                          WIFI_ONCHIP_SILEX_RETURN_OK);

    rm_wifi_onchip_silex_send_basic_give_mutex(p_instance_ctrl, mutex_flag);

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup WIFI_ONCHIP_SILEX)
 **********************************************************************************************************************/

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

/*! \cond PRIVATE */

///////////////////////////////////////////////////////////////////////////////

/*
 * Alternate function for the StreamBufferReceive call. Allows for the byte
 * triggering mechanism to work correctly. The alternate function does perform
 * thread blocking when the trigger level has not been reached.
 */

///////////////////////////////////////////////////////////////////////////////

 #define sbFLAGS_IS_MESSAGE_BUFFER          ((uint8_t) 1) /* Set if the stream buffer was created as a message buffer, in which case it holds discrete messages rather than a stream. */
 #define sbBYTES_TO_STORE_MESSAGE_LENGTH    (sizeof(configMESSAGE_BUFFER_LENGTH_TYPE))

/* Structure that hold state information on the buffer. */
typedef struct StreamBufferDef_t                          /*lint !e9058 Style convention uses tag. */
{
    volatile size_t       xTail;                          /* Index to the next item to read within the buffer. */
    volatile size_t       xHead;                          /* Index to the next item to write within the buffer. */
    size_t                xLength;                        /* The length of the buffer pointed to by pucBuffer. */
    size_t                xTriggerLevelBytes;             /* The number of bytes that must be in the stream buffer before a task that is waiting for data is unblocked. */
    volatile TaskHandle_t xTaskWaitingToReceive;          /* Holds the handle of a task waiting for data, or NULL if no tasks are waiting. */
    volatile TaskHandle_t xTaskWaitingToSend;             /* Holds the handle of a task waiting to send data to a message buffer that is full. */
    uint8_t             * pucBuffer;                      /* Points to the buffer itself - that is - the RAM that stores the data passed through the buffer. */
    uint8_t               ucFlags;
 #if (configUSE_TRACE_FACILITY == 1)
    UBaseType_t uxStreamBufferNumber;                     /* Used for tracing purposes. */
 #endif
} StreamBuffer_t;

 #ifndef sbRECEIVE_COMPLETED
  #define sbRECEIVE_COMPLETED(pxStreamBuffer)                                                  \
    vTaskSuspendAll();                                                                         \
    {                                                                                          \
        if ((pxStreamBuffer)->xTaskWaitingToSend != NULL)                                      \
        {                                                                                      \
            (void) xTaskNotify((pxStreamBuffer)->xTaskWaitingToSend, (uint32_t) 0, eNoAction); \
            (pxStreamBuffer)->xTaskWaitingToSend = NULL;                                       \
        }                                                                                      \
    }                                                                                          \
    (void) xTaskResumeAll();
 #endif                                /* sbRECEIVE_COMPLETED */

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

size_t xStreamBufferReceiveAlternate (StreamBufferHandle_t xStreamBuffer,
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

#endif                                 // FREERTOS
