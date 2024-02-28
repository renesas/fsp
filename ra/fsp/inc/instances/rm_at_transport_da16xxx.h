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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_NETWORKING_INTERFACES
 * @defgroup RM_AT_TRANSPORT_DA16XXX_API DA16XXX AT Command Transport Layer
 * @brief Abstraction interface for DA16XXX AT Command functions.
 *
 * @section RM_DA16XXX_TRANSPORT_API_Summary Summary
 * The DA16XXX AT Command Transport Layer interface provides functions for data communication and buffer handling over multiple communications interfaces.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef RM_AT_TRANSPORT_DA16XXX_API_H_
#define RM_AT_TRANSPORT_DA16XXX_API_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "platform.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include <stddef.h>
 #include <stdbool.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
 #include "bsp_api.h"
 #include "rm_at_transport_da16xxx_uart_cfg.h"
#endif

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Error Response Codes */
#define AT_TRANSPORT_DA16XXX_ERR_UNKNOWN_CMD          (-1)
#define AT_TRANSPORT_DA16XXX_ERR_INSUF_PARAMS         (-2)
#define AT_TRANSPORT_DA16XXX_ERR_TOO_MANY_PARAMS      (-3)
#define AT_TRANSPORT_DA16XXX_ERR_INVALID_PARAM        (-4)
#define AT_TRANSPORT_DA16XXX_ERR_UNSUPPORTED_FUN      (-5)
#define AT_TRANSPORT_DA16XXX_ERR_NOT_CONNECTED_AP     (-6)
#define AT_TRANSPORT_DA16XXX_ERR_NO_RESULT            (-7)
#define AT_TRANSPORT_DA16XXX_ERR_RESP_BUF_OVERFLOW    (-8)
#define AT_TRANSPORT_DA16XXX_ERR_FUNC_NOT_CONFIG      (-9)
#define AT_TRANSPORT_DA16XXX_ERR_CMD_TIMEOUT          (-10)
#define AT_TRANSPORT_DA16XXX_ERR_NVRAM_WR_FAIL        (-11)
#define AT_TRANSPORT_DA16XXX_ERR_RETEN_MEM_WR_FAIL    (-12)
#define AT_TRANSPORT_DA16XXX_ERR_UNKNOWN              (-99)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event in the callback function */
typedef enum e_at_transport_da16xxx_event
{
    AT_TRANSPORT_RX_BYTE_EVENT,
} at_transport_da16xxx_event_t;

/** DA16xxx middleware callback parameter definition */
typedef struct st_at_transport_da16xxx_callback_args
{
    void const                 * p_context;
    at_transport_da16xxx_event_t event;
    uint8_t data;
} at_transport_da16xxx_callback_args_t;

/** DA16xxx middleware configuration block */
typedef struct st_at_transport_da16xxx_cfg
{
    void const * p_extend;                                              ///< Pointer to extended configuration by instance of interface.
    void const * p_context;                                             ///< Pointer to the user-provided context
    bool (* p_callback)(at_transport_da16xxx_callback_args_t * p_args); ///< Pointer to callback function.
} at_transport_da16xxx_cfg_t;

/** DA16xxx data structure */
typedef struct st_at_transport_da16xxx_data_t
{
    uint8_t    * p_at_cmd_string;      ///< Pointer to ATCMD string.
    uint32_t     at_cmd_string_length; ///< ATCMD string length.
    uint8_t    * p_response_buffer;    ///< Pointer to ATCMD response buffer.
    uint32_t     response_buffer_size; ///< ATCMD response buffer string length.
    uint32_t     timeout_ms;           ///< ATCMD timeout in ms.
    const char * p_expect_code;        ///< Expected string in the ATCMD response.
    uint32_t     comm_ch_id;           ///< Communication channel ID.
} at_transport_da16xxx_data_t;

/** DA16xxx status indicators */
typedef struct st_at_transport_da16xxx_status
{
    bool open;                         ///< True if driver is open
} at_transport_da16xxx_status_t;

/** At transport control block.  Allocate an instance specific control block to pass into the Communications API calls.
 */
typedef void at_transport_da16xxx_ctrl_t;

/** AT Command APIs */
typedef struct st_at_transport_da16xxx_api
{
    /** Open at cmd instance.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(at_transport_da16xxx_ctrl_t * const p_ctrl, at_transport_da16xxx_cfg_t const * const p_cfg);

    /** Close at cmd instance.
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(at_transport_da16xxx_ctrl_t * const p_ctrl);

    /** at cmd send thread safe.
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_at_cmd      Pointer to AT command data structure.
     */
    fsp_err_t (* atCommandSendThreadSafe)(at_transport_da16xxx_ctrl_t * const p_ctrl,
                                          at_transport_da16xxx_data_t       * p_at_cmd);

    /** at cmd send.
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_at_cmd      Pointer to AT command data structure.
     */
    fsp_err_t (* atCommandSend)(at_transport_da16xxx_ctrl_t * const p_ctrl, at_transport_da16xxx_data_t * p_at_cmd);

    /** Give the mutex.
     *  @param[in]  p_ctrl       Pointer to Transport layer instance control structure.
     *  @param[in] mutex_flag    TX/RX Flags for the mutex.
     */
    fsp_err_t (* giveMutex)(at_transport_da16xxx_ctrl_t * const p_ctrl, uint32_t mutex_flag);

    /** Take the mutex .
     *  @param[in]  p_ctrl       Pointer to Transport layer instance control structure.
     *  @param[in] mutex_flag    TX/RX Flags for the mutex.
     */
    fsp_err_t (* takeMutex)(at_transport_da16xxx_ctrl_t * const p_ctrl, uint32_t mutex_flag);

    /** Gets the status of the configured DA16xxx transport.
     *
     * @param[in]   p_ctrl             Pointer to the to Transport layer instance control structure.
     * @param[out]  p_status           Pointer to store current status.
     */
    fsp_err_t (* statusGet)(at_transport_da16xxx_ctrl_t * const p_ctrl, at_transport_da16xxx_status_t * p_status);

    /** Receive data from stream buffer.
     * @param[in]  p_ctrl               Pointer to Transport layer instance control structure.
     * @param[in]  p_data               Pointer to data.
     * @param[in]  length               Data length.
     * @param[in]  rx_timeout           Timeout for receiving data on the buffer.
     * @param[in]  trigger_level        Trigger level for stream buffer.
     */
    size_t (* bufferRecv)(at_transport_da16xxx_ctrl_t * const p_ctrl, const char * p_data, uint32_t length,
                          uint32_t rx_timeout);
} at_transport_da16xxx_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_at_transport_da16xxx_instance
{
    at_transport_da16xxx_ctrl_t      * p_ctrl;
    at_transport_da16xxx_cfg_t       * p_cfg;
    at_transport_da16xxx_api_t const * p_api;
} at_transport_da16xxx_instance_t;

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_AT_TRANSPORT_DA16XXX_API_H_ */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_AT_TRANSPORT_DA16XXX_API_H_)
 **********************************************************************************************************************/
