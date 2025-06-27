/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_sau_lin.h"
#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
 #include "r_icu.h"
#endif
#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
 #include "r_tau.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "SLIN" in ASCII.  Used to determine if the control block is open for SAU LIN. */
#define SAU_LIN_OPEN                          (0x534C494EU)

/* Mask for checking valid frame identifiers */
#define SAU_LIN_FRAME_ID_MASK                 (0x3FU)

/* Number of pulse intervals required to measure the sync byte in slave mode */
#define SAU_LIN_PULSE_INTERVAL_MAX_COUNT      (5)

/* LIN Wakeup Pattern */
#define SAU_LIN_WAKEUP                        (0x80U)

/* LIN Sync Word Pattern */
#define SAU_LIN_SYNC                          (0x55U)

/* LIN Break Field Pattern */
#define SAU_LIN_BREAK_FIELD                   (0x00U)

/* Microseconds per second */
#define SAU_LIN_MICROSECONDS_PER_SECOND       (1000000U)

/* Number of bits to detect break field */
#define SAU_LIN_DETECTED_BREAK_FIELD_WIDTH    (11)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* LIN on SAU HAL API mapping for LIN interface */
const lin_api_t g_lin_on_sau_lin =
{
    .open                  = R_SAU_LIN_Open,
    .read                  = R_SAU_LIN_Read,
    .write                 = R_SAU_LIN_Write,
    .communicationAbort    = R_SAU_LIN_CommunicationAbort,
    .callbackSet           = R_SAU_LIN_CallbackSet,
    .close                 = R_SAU_LIN_Close,
    .sleepEnter            = R_SAU_LIN_SleepEnter,
    .sleepExit             = R_SAU_LIN_SleepExit,
    .wakeupSend            = R_SAU_LIN_WakeupSend,
    .informationFrameRead  = R_SAU_LIN_InformationFrameRead,  // [DEPRECATED]
    .startFrameWrite       = R_SAU_LIN_StartFrameWrite,       // [DEPRECATED]
    .informationFrameWrite = R_SAU_LIN_InformationFrameWrite, // [DEPRECATED]
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* Checksum helper functions */
#if SAU_LIN_CFG_CHECKSUM_SUPPORT_ENABLE
static uint8_t r_sau_lin_checksum_initialize(uint8_t id, lin_checksum_type_t checksum_type);
static uint8_t r_sau_lin_checksum_add_byte_to_sum(uint8_t byte, uint8_t current_sum);
static uint8_t r_sau_lin_checksum_calculate(uint8_t               id,
                                            uint8_t const * const p_data,
                                            uint8_t               num_bytes,
                                            lin_checksum_type_t   checksum_type);

#endif

#if (SAU_LIN_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t r_sau_lin_common_parameter_checking(sau_lin_instance_ctrl_t const * const p_ctrl);

static fsp_err_t r_sau_lin_read_write_param_check(sau_lin_instance_ctrl_t const * const p_ctrl,
                                                  lin_transfer_params_t const * const   p_transfer_params);

#endif

/* Transmission/reception helper functions */
static fsp_err_t r_sau_lin_communication_abort(sau_lin_instance_ctrl_t * const p_ctrl);
static fsp_err_t r_sau_lin_frame_write(sau_lin_instance_ctrl_t * const     p_ctrl,
                                       const lin_transfer_params_t * const p_transfer_params,
                                       uint8_t const                       send_header);
static void r_sau_lin_call_callback(sau_lin_instance_ctrl_t * p_ctrl, lin_event_t event);

#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
static uint32_t r_sau_lin_uart_current_baudrate_get(const uart_instance_t * p_uart);

 #if SAU_LIN_AUTO_SYNC_SUPPORT_ENABLE
static bool r_sau_lin_verify_sync_baudrate(uint32_t current_baud, uint32_t sync_baud);

 #endif
#endif

/* PID helper functions */
static uint8_t r_sau_lin_pid_calculate(uint8_t id);

static void r_sau_lin_tx_complete(sau_lin_instance_ctrl_t * const p_ctrl, sau_uart_instance_ctrl_t * const p_uart_ctrl);
static void r_sau_lin_rx_complete(sau_lin_instance_ctrl_t * const p_ctrl, sau_uart_instance_ctrl_t * const p_uart_ctrl);
static void r_sau_lin_err_complete(sau_lin_instance_ctrl_t * const p_ctrl, uart_callback_args_t const * const p_args);

#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
static fsp_err_t r_sau_lin_set_state_active(sau_lin_instance_ctrl_t * const p_ctrl);

void r_sau_lin_icu_callback(external_irq_callback_args_t * p_args);

#endif

#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
void r_sau_lin_tau_callback(timer_callback_args_t * p_args);

#endif
void r_sau_lin_uart_callback(uart_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* 1 byte "buffer" used to transmit header sync word. */
#if SAU_LIN_CFG_MASTER_SUPPORT_ENABLE
static const uint8_t g_header_sync_word        = SAU_LIN_SYNC;
static const uint8_t g_header_break_field_word = SAU_LIN_BREAK_FIELD;
#endif

#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
static const uint8_t g_wake_up_send_word = SAU_LIN_WAKEUP;
#endif

/*******************************************************************************************************************//**
 * @addtogroup SAU_LIN
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the LIN driver channel based on the input configuration.
 *
 * Implements @ref lin_api_t::open.
 *
 * Example:
 * @snippet r_sau_lin_example.c R_SAU_LIN_Open
 *
 * @retval  FSP_SUCCESS                    Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to LIN control block, configuration structure, or required dependency is NULL
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_MODE           Setting not supported for selected mode
 *
 * @return                                 See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                         return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_Open (lin_ctrl_t * const p_api_ctrl, lin_cfg_t const * const p_cfg)
{
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
#if (SAU_LIN_CFG_PARAM_CHECKING_ENABLE)

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);
#endif
    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_cfg->p_extend;
#if (SAU_LIN_CFG_PARAM_CHECKING_ENABLE)

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_extend);

    /* Check control block isn't already open */
    FSP_ERROR_RETURN(p_ctrl->open != SAU_LIN_OPEN, FSP_ERR_ALREADY_OPEN);
 #if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE

    /* Check for required modules for slave mode */
    FSP_ASSERT(NULL != p_extend->p_timer || LIN_MODE_MASTER == p_cfg->mode);

  #if SAU_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Auto Synchronization not supported in master mode */
    FSP_ERROR_RETURN((SAU_LIN_AUTO_SYNCHRONIZATION_DISABLE == p_extend->auto_synchronization) ||
                     (LIN_MODE_SLAVE == p_cfg->mode),
                     FSP_ERR_INVALID_MODE);
  #endif
 #endif

    /* Check for required modules for both modes */
    FSP_ASSERT(NULL != p_extend->p_uart);
#endif

    /* Initialize control block */
    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;
    p_ctrl->p_data     = NULL;
    p_ctrl->state      = SAU_LIN_STATE_NONE;

    /* Open the UART driver */
    const uart_instance_t * p_uart = p_extend->p_uart;
    fsp_err_t               status = R_SAU_UART_Open(p_uart->p_ctrl, p_uart->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    /* Set the callback function and context for the UART driver */
    status = R_SAU_UART_CallbackSet(p_uart->p_ctrl, r_sau_lin_uart_callback, p_ctrl, NULL);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
    const external_irq_instance_t * p_icu = p_extend->p_icu;
    if (NULL != p_icu)
    {
        /* Critical section required because ISC register is shared with other instances. */
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        /* Set IRQn input source for the wakeup signal detection */
        R_PORGA->ISC |= R_PORGA_ISC_ISC0_Msk;

        FSP_CRITICAL_SECTION_EXIT;

        /* Open the ICU driver */
        status = R_ICU_ExternalIrqOpen(p_icu->p_ctrl, p_icu->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

        /* Set the callback function and context for the ICU driver */
        status = R_ICU_ExternalIrqCallbackSet(p_icu->p_ctrl, r_sau_lin_icu_callback, p_ctrl, NULL);
        FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

        /* Initialize bus state */
        status = r_sau_lin_set_state_active(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
    }
#endif

#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
    if (LIN_MODE_SLAVE == p_ctrl->p_cfg->mode)
    {
        /* Configure the TAU to detect the break field */
        const timer_instance_t * p_timer = p_extend->p_timer;
        status = R_TAU_Open(p_timer->p_ctrl, p_timer->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

        /* Set the callback function and context for the TAU driver */
        status = R_TAU_CallbackSet(p_timer->p_ctrl, r_sau_lin_tau_callback, p_ctrl, NULL);
        FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

        /* Start the TAU */
        status = R_TAU_Start(p_timer->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
    }
#endif

    /* Mark the control block as open */
    p_ctrl->open = SAU_LIN_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Begins non-blocking transmission of a LIN frame.
 *
 * In master mode, the LIN header (break, sync and protected identifier) is sent before the LIN data.
 *  - To transmit the LIN header only, set p_transfer_params->p_data to NULL.
 *  - To transmit both header and data, set p_transfer_params->p_data to the TX buffer to transmit.
 *
 * The LIN header is not transmitted in slave mode. Set p_transfer_params->p_data to the TX buffer to transmit.
 *
 * On successful header-only transmission completion, the callback is called with event @ref lin_event_t::LIN_EVENT_TX_HEADER_COMPLETE.
 * On successful data transmission or header+data transmission completion, the callback is called with event @ref lin_event_t::LIN_EVENT_TX_DATA_COMPLETE.
 *
 * Implements @ref lin_api_t::write.
 *
 * Example:
 * @snippet r_sau_lin_example.c R_SAU_LIN_Write
 *
 * @retval  FSP_SUCCESS              Data transmission started successfully.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0 bytes length provided。
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call @ref R_SAU_LIN_CommunicationAbort
 *                                   to cancel it if desired, or wait for the current transfer operation to complete before starting a new one.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_Write (lin_ctrl_t * const p_api_ctrl, const lin_transfer_params_t * const p_transfer_params)
{
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                 status = FSP_SUCCESS;

#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_transfer_params);
    fsp_err_t err = r_sau_lin_read_write_param_check(p_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    uint8_t is_master_write = (LIN_MODE_MASTER == p_ctrl->p_cfg->mode);

#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE && SAU_LIN_CFG_MASTER_SUPPORT_ENABLE

    /* Check ID is at most 6 bits (only for master header transmission) */
    FSP_ERROR_RETURN((0 == (p_transfer_params->id & 0xC0)) || !is_master_write, FSP_ERR_INVALID_ARGUMENT);
#endif

#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE && SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE

    /* Check p_data is not null in slave mode */
    FSP_ASSERT(NULL != p_transfer_params->p_data || is_master_write);
#endif

    status = r_sau_lin_frame_write(p_ctrl, p_transfer_params, is_master_write);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Begins non-blocking data reception to receive user specified number of bytes into destination buffer pointer.
 *
 * The checksum type specifies the checksum type used for validation. If a non-standard algorithm is used,
 * or the application prefers to validate the checksum outside the driver, or the application prefers
 * to skip checksum validation, specify @ref lin_checksum_type_t::LIN_CHECKSUM_TYPE_NONE. If checksum
 * validation is skipped, the @ref lin_checksum_type_t::LIN_EVENT_ERR_INVALID_CHECKSUM event is not possible.
 * When  @ref lin_checksum_type_t::LIN_CHECKSUM_TYPE_NONE is used, the number of bytes specified in the receive
 * buffer length will be received  (the driver will not expect to receive an additional 1 checksum byte), so
 * if a non-standard checksum is used,  sufficient space must be allocated in the write buffer and accounted for
 * in the provided length.
 *
 * On successful data reception, the callback is called with event @ref lin_event_t::LIN_EVENT_RX_DATA_COMPLETE.
 *
 * Implements @ref lin_api_t::read.
 *
 * Example:
 * @snippet r_sau_lin_example.c R_SAU_LIN_Read
 *
 * @retval  FSP_SUCCESS              Data reception started successfully.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0 bytes length provided,
 *                                   no header matching pid was received(only for slave mode).
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call @ref R_SAU_LIN_CommunicationAbort
 *                                   to cancel it if desired, or wait for the current transfer operation to complete before starting a new one.
 *
 * @retval  FSP_ERR_INVALID_CALL     Data reception is not possible because a header frame has not been received yet (slave mode only).
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_Read (lin_ctrl_t * const p_api_ctrl, lin_transfer_params_t * const p_transfer_params)
{
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                 status;
#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    status = r_sau_lin_read_write_param_check(p_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
    FSP_ASSERT(NULL != p_transfer_params->p_data);

    /* In slave mode, check that data reception is possible (due to successful header reception) */
    FSP_ERROR_RETURN((LIN_MODE_MASTER == p_ctrl->p_cfg->mode) || (SAU_LIN_STATE_HEADER_RECEIVED == p_ctrl->state),
                     FSP_ERR_INVALID_CALL);
#endif

#if SAU_LIN_CFG_CHECKSUM_SUPPORT_ENABLE
    p_ctrl->checksum          = 0;
    p_ctrl->checksum_type     = p_transfer_params->checksum_type;
    p_ctrl->validate_checksum = p_transfer_params->checksum_type != LIN_CHECKSUM_TYPE_NONE;
#endif
    p_ctrl->count  = p_transfer_params->num_bytes;
    p_ctrl->p_data = p_transfer_params->p_data;
    p_ctrl->state  = SAU_LIN_STATE_AWAITING_DATA;

    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    status = R_SAU_UART_Read(p_extend->p_uart->p_ctrl, p_transfer_params->p_data, p_transfer_params->num_bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Cancels in progress data read or write, or header read or write. Break field reception cannot be
 * cancelled. For slave nodes, reception of a new header reception is still enabled after a call to this function.
 *
 * Implements @ref lin_api_t::communicationAbort.
 *
 * @retval  FSP_SUCCESS            Data transfer aborted successfully or no transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN       The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION      Pointer to LIN control block is NULL.
 * @retval  FSP_ERR_INVALID_STATE  Driver is in bus sleep state. Call @ref R_SAU_LIN_SleepExit to return to active state or wait for wakeup signal.
 *
 * @return                         See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                 return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_CommunicationAbort (lin_ctrl_t * const p_api_ctrl)
{
    fsp_err_t                 status = FSP_SUCCESS;
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    status = r_sau_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
#endif

    status = r_sau_lin_communication_abort(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    return status;
}

/*******************************************************************************************************************//**
 * Updates the user callback and callback context.
 * @note Providing callback memory is not supported, pass NULL to this function for p_callback_memory.
 *
 * Implements @ref lin_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS            Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION      Pointer to LIN control block, callback function is NULL, or p_callback_memory is not NULL.
 * @retval  FSP_ERR_NOT_OPEN       The control block has not been opened.
 * @retval  FSP_ERR_INVALID_STATE  Driver is in bus sleep state. Call @ref R_SAU_LIN_SleepExit to return to active state or wait for wakeup signal.
 *
 * @return                         See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                 return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_CallbackSet (lin_ctrl_t * const          p_api_ctrl,
                                 void (                    * p_callback)(lin_callback_args_t *),
                                 void * const                p_context,
                                 lin_callback_args_t * const p_callback_memory)
{
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;

#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t status = r_sau_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    /* Check for null parameters */
    FSP_ASSERT(NULL == p_callback_memory);
    FSP_ASSERT(NULL != p_callback);
#endif
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    p_ctrl->p_context  = p_context;
    p_ctrl->p_callback = p_callback;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Begins non-blocking transmission of the LIN wakeup signal.
 *
 * On successful wakeup signal transmission, the callback is called with event @ref lin_event_t::LIN_EVENT_TX_WAKEUP_COMPLETE.
 *
 * Implements @ref lin_api_t::wakeupSend.
 *
 * Example:
 * @snippet r_sau_lin_example.c R_SAU_LIN_WakeupSend
 *
 * @retval  FSP_SUCCESS            Wakeup signal transmission successfully started.
 * @retval  FSP_ERR_ASSERTION      Pointer to LIN control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN       The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED    Unsupported when Wake-up Support build option is disabled.
 * @retval  FSP_ERR_INVALID_STATE  Driver is in bus sleep state. Call @ref R_SAU_LIN_SleepExit to return to active state or wait for wakeup signal.
 *
 * @return                         See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                 return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_WakeupSend (lin_ctrl_t * const p_api_ctrl)
{
#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;

 #if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t status = r_sau_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
 #endif

    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    p_ctrl->state = SAU_LIN_STATE_SENDING_WAKEUP;

    return R_SAU_UART_Write(p_extend->p_uart->p_ctrl, &g_wake_up_send_word, 1);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Places the LIN node in bus sleep mode. Enables the external IRQ that can be used to detect the LIN wakeup signal.
 *
 * On wakeup signal reception, the callback is called with event @ref lin_event_t::LIN_EVENT_RX_WAKEUP_COMPLETE and
 * bus sleep mode is automatically exited.
 *
 * @note This function does not put the MCU into a low power mode. Call this function prior to entering a low power mode
 * to enable LIN wakeup signal detection support.
 *
 * Implements @ref lin_api_t::sleepEnter.
 *
 * Example:
 * @snippet r_sau_lin_example.c R_SAU_LIN_SleepEnter
 *
 * @retval  FSP_SUCCESS            Bus successfully transitioned to sleep state.
 * @retval  FSP_ERR_ASSERTION      Pointer to LIN control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN       The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED    Unsupported when Wake-up Support build option is disabled.
 * @retval  FSP_ERR_INVALID_STATE  Driver is in bus sleep state. Call @ref R_SAU_LIN_SleepExit to return to active state or wait for wakeup signal.
 * @retval  FSP_ERR_NOT_ENABLED    ICU module is not enabled.
 *
 * @return                         See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                 return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_SleepEnter (lin_ctrl_t * const p_api_ctrl)
{
#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                 status;

 #if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    status = r_sau_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
 #endif

    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

 #if SAU_LIN_CFG_PARAM_CHECKING_ENABLE

    /* Ensure sleep/wakeup is enabled */
    FSP_ERROR_RETURN(NULL != p_extend->p_icu, FSP_ERR_NOT_ENABLED);
 #endif

    icu_instance_ctrl_t * p_icu_ctrl = (icu_instance_ctrl_t *) p_extend->p_icu->p_ctrl;

    p_ctrl->state = SAU_LIN_STATE_BUS_SLEEP;
    status        = R_ICU_ExternalIrqEnable(p_icu_ctrl);

    if (FSP_SUCCESS != status)
    {
        p_ctrl->state = SAU_LIN_STATE_NONE;
    }

    return status;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Exits the bus sleep mode for LIN device. Disables wakeup signal detection.
 *
 * Implements @ref lin_api_t::sleepExit.
 *
 * @retval  FSP_SUCCESS            Bus successfully transitioned to active state
 * @retval  FSP_ERR_ASSERTION      Pointer to LIN control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN       The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED    Unsupported when Wake-up Support build option is disabled.
 * @retval  FSP_ERR_NOT_ENABLED    ICU module is not enabled.
 *
 * @return                         See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                 return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_SleepExit (lin_ctrl_t * const p_api_ctrl)
{
#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
    fsp_err_t                 status = FSP_SUCCESS;
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;

 #if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SAU_LIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    FSP_ERROR_RETURN(NULL != p_extend->p_icu, FSP_ERR_NOT_ENABLED);
 #endif

    status = r_sau_lin_set_state_active(p_ctrl);

    return status;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Closes the LIN driver.
 *
 * Implements @ref lin_api_t::close.
 *
 * Example:
 * @snippet r_sau_lin_example.c R_SAU_LIN_Close
 *
 * @retval  FSP_SUCCESS           Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION     Pointer to LIN control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN      The control block has not been opened.
 *
 * @return                        See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_Close (lin_ctrl_t * const p_api_ctrl)
{
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SAU_LIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
    const external_irq_instance_t * p_icu = p_extend->p_icu;
    if (NULL != p_icu)
    {
        /* Critical section required because ISC register is shared with other instances. */
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        /* Restore IRQn input source */
        R_PORGA->ISC &= (uint8_t) ~R_PORGA_ISC_ISC0_Msk;

        FSP_CRITICAL_SECTION_EXIT;

        /* Close the ICU driver */
        R_ICU_ExternalIrqClose(p_icu->p_ctrl);
    }
#endif

#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
    if (LIN_MODE_SLAVE == p_ctrl->p_cfg->mode)
    {
        /* Close the TAU driver */
        const timer_instance_t * p_timer = p_extend->p_timer;
        R_TAU_Close(p_timer->p_ctrl);
    }
#endif

    /* Close the UART driver */
    R_SAU_UART_Close(p_extend->p_uart->p_ctrl);

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * DEPRECATED. Use @ref R_SAU_LIN_Read.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_InformationFrameRead (lin_ctrl_t * const            p_api_ctrl,
                                          lin_transfer_params_t * const p_transfer_params)
{
    return R_SAU_LIN_Read(p_api_ctrl, p_transfer_params);
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SAU_LIN_Write
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_StartFrameWrite (lin_ctrl_t * const p_api_ctrl, uint8_t const id)
{
#if SAU_LIN_CFG_MASTER_SUPPORT_ENABLE
    lin_transfer_params_t params =
    {
        .id            = id,
        .p_data        = NULL,
        .num_bytes     = 0,
        .checksum_type = LIN_CHECKSUM_TYPE_NONE,
    };

    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                 status;
 #if SAU_LIN_CFG_PARAM_CHECKING_ENABLE
    status = r_sau_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    /* Check ID is at most 6 bits */
    FSP_ERROR_RETURN(0 == (id & 0xC0), FSP_ERR_INVALID_ARGUMENT);

    /* Function only supported for master mode */
    FSP_ERROR_RETURN(LIN_MODE_MASTER == p_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(SAU_LIN_STATE_NONE == p_ctrl->state, FSP_ERR_IN_USE);
 #endif

    status = r_sau_lin_frame_write(p_ctrl, &params, true);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(id);

    return FSP_ERR_INVALID_MODE;
#endif
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SAU_LIN_Write
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SAU_LIN_InformationFrameWrite (lin_ctrl_t * const                  p_api_ctrl,
                                           const lin_transfer_params_t * const p_transfer_params)
{
    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                 status = FSP_SUCCESS;

#if SAU_LIN_CFG_PARAM_CHECKING_ENABLE

    /* Common parameter checking */
    status = r_sau_lin_read_write_param_check(p_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
    FSP_ASSERT(NULL != p_transfer_params->p_data);
#endif

    status = r_sau_lin_frame_write(p_ctrl, p_transfer_params, false);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SAU_LIN)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (SAU_LIN_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Verifies the control structure is not NULL and the module is open. This reduces code size when parameter checking is
 * enabled.
 *
 * @param[in] p_ctrl                    Pointer to the control block for the channel
 *
 * @retval FSP_SUCCESS                  No error detected.
 * @retval FSP_ERR_ASSERTION            NULL input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_INVALID_STATE        Driver is in bus sleep state. Call @ref R_SAU_LIN_SleepExit to return to active state or wait for wakeup signal.
 **********************************************************************************************************************/
static fsp_err_t r_sau_lin_common_parameter_checking (sau_lin_instance_ctrl_t const * const p_ctrl)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SAU_LIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(SAU_LIN_STATE_BUS_SLEEP != p_ctrl->state, FSP_ERR_INVALID_STATE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter error check function for R_SAU_LIN_Write and R_SAU_LIN_Read
 *
 * @param[in] p_ctrl                 Pointer to the control block for the channel
 * @param[in] p_transfer_params      Pointer to the transfer parameters for the transfer
 *
 * @retval  FSP_SUCCESS              No parameter error found
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call R_SAU_LIN_CommunicationAbort
 *                                   to cancel it if desired, or wait for the current transfer operation to complete before starting a new one.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0 bytes length provided
 * @retval  FSP_ERR_INVALID_STATE    Driver is in bus sleep state. Call @ref R_SAU_LIN_SleepExit to return to active state or wait for wakeup signal.
 **********************************************************************************************************************/
static fsp_err_t r_sau_lin_read_write_param_check (sau_lin_instance_ctrl_t const * const p_ctrl,
                                                   lin_transfer_params_t const * const   p_transfer_params)
{
    fsp_err_t status = r_sau_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

    FSP_ASSERT(NULL != p_transfer_params);

    /* Number of bytes and checksum parameters are only checked for data transfers */
    if (NULL != p_transfer_params->p_data)
    {
        FSP_ASSERT(p_transfer_params->num_bytes > 0);
        FSP_ASSERT(((p_transfer_params->num_bytes < UINT8_MAX) ||
                    (LIN_CHECKSUM_TYPE_NONE == p_transfer_params->checksum_type)));
    }

    /* Cannot start read/write when another write is in progress */
    FSP_ERROR_RETURN((SAU_LIN_STATE_NONE == p_ctrl->state) || (SAU_LIN_STATE_HEADER_RECEIVED == p_ctrl->state),
                     FSP_ERR_IN_USE);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Calculates the protected identifier.
 *
 * Implements the algorithm according to LIN Protocol Specification Rev. 2.2A pg.53.
 *
 * The PID is an 8 bit field: [p1 p0 id5 id4 id3 id2 id1 id0].
 * P1 is bit 7 and is calculated as id1 XOR id3 XOR id4 XOR id5.
 * P0 is bit 6 and is calculated as id0 XOR id1 XOR ix2 XOR id4.
 *
 * @param[in] id LIN unprotected frame identifier
 *
 * @retval       LIN protected frame identifier result
 **********************************************************************************************************************/
static uint8_t r_sau_lin_pid_calculate (uint8_t id)
{
    /* ID is 6 bits */
    uint8_t pid = id & SAU_LIN_FRAME_ID_MASK;

    /* P0 = id0 ^ id1 ^ id2 ^ id4*/
    uint8_t tmp = (((id >> 0) ^ (id >> 1) ^ (id >> 2) ^ (id >> 4)) & 0x01);
    pid |= (uint8_t) (tmp << 6U);

    /* P1 = ~(id1 ^ id3 ^ id4 ^ id5) */
    tmp  = (uint8_t) ~(((id >> 1) ^ (id >> 3) ^ (id >> 4) ^ (id >> 5)) & 0x01);
    pid |= (uint8_t) (tmp << 7U);

    return pid;
}

#if SAU_LIN_CFG_CHECKSUM_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Add byte to checksum
 *
 * @param[in] byte         Byte to add to current sum
 * @param[in] current_sum  Current checksum (intermediate sum)
 *
 * @retval       New checksum result (after adding byte)
 **********************************************************************************************************************/
static uint8_t r_sau_lin_checksum_add_byte_to_sum (uint8_t byte, uint8_t current_sum)
{
    uint16_t new_sum = current_sum;

    new_sum += byte;

    /* LIN Protocol Specification Rev. 2.2A pg.32 section 2.3.1.5:
     * 8-bit sum with carry is equivalent to sum all values and subtract
     * 255 every time the sum is greater than or equal to 256 */
    if (new_sum > UINT8_MAX)
    {
        new_sum -= UINT8_MAX;
    }

    return (uint8_t) new_sum;
}

/*******************************************************************************************************************//**
 * Initialize the checksum based on the checksum type
 *
 * @param[in] id                LIN unprotected frame identifier
 * @param[in] checksum_type     Checksum type (classic or enhanced)
 *
 * @retval   Initial checksum value for the provided checksum type
 **********************************************************************************************************************/
static uint8_t r_sau_lin_checksum_initialize (uint8_t id, lin_checksum_type_t checksum_type)
{
    uint8_t checksum = 0;

    if (LIN_CHECKSUM_TYPE_ENHANCED == checksum_type)
    {
        /* Compute PID and add to checksum. Enhanced checksum includes data and PID. Standard is data only. */
        checksum = r_sau_lin_pid_calculate(id);
    }

    return checksum;
}

/*******************************************************************************************************************//**
 * Calculates the LIN checksum on data to be transmitted. For received frames,
 * the checksum is calculated at the end of the reception.
 *
 * @param[in] id             LIN unprotected frame identifier.
 * @param[in] p_data         Pointer to frame data.
 * @param[in] num_bytes      Frame data length.
 * @param[in] checksum_type  Checksum type (classic or enhanced). Frame ID 0x3C and 0x3D always use classic checksum.
 *
 * @retval                   LIN checksum result
 **********************************************************************************************************************/
static uint8_t r_sau_lin_checksum_calculate (uint8_t               id,
                                             uint8_t const * const p_data,
                                             uint8_t               num_bytes,
                                             lin_checksum_type_t   checksum_type)
{
    uint8_t checksum = r_sau_lin_checksum_initialize(id, checksum_type);

    for (uint8_t i = 0; i < num_bytes; i++)
    {
        checksum = r_sau_lin_checksum_add_byte_to_sum(p_data[i], checksum);
    }

    return (uint8_t) ~checksum;
}

#endif

/*******************************************************************************************************************//**
 * Transmit the LIN frame
 *
 * @param[in]   p_ctrl                   Pointer to driver control block
 * @param[in]  p_transfer_params         Pointer to the transfer parameters for the transfer
 * @param[in]  send_header               Set to true if the LIN header should be transmitted before the data (master mode only)
 *
 * @retval     FSP_SUCCESS               Transmission started successfully
 * @retval     FSP_ERR_ASSERTION         The new SDR register setting will exceed the register upper limit,
 *                                       please increase the baud rate or adjust the clock setting first.
 * **********************************************************************************************************************/
static fsp_err_t r_sau_lin_frame_write (sau_lin_instance_ctrl_t * const     p_ctrl,
                                        const lin_transfer_params_t * const p_transfer_params,
                                        uint8_t const                       send_header)
{
    fsp_err_t status    = FSP_SUCCESS;
    uint8_t * p_data    = p_transfer_params->p_data;
    uint8_t   num_bytes = p_transfer_params->num_bytes;

#if SAU_LIN_CFG_MASTER_SUPPORT_ENABLE
    if (p_data)
#endif
    {
#if SAU_LIN_CFG_CHECKSUM_SUPPORT_ENABLE
        p_ctrl->validate_checksum = p_transfer_params->checksum_type != LIN_CHECKSUM_TYPE_NONE;

        if (p_ctrl->validate_checksum)
        {
            /* If checksum generation is enabled, calculate the checksum */
            p_ctrl->checksum = r_sau_lin_checksum_calculate(p_transfer_params->id,
                                                            p_data,
                                                            num_bytes,
                                                            p_transfer_params->checksum_type);
        }
#endif
        p_ctrl->p_data = p_data;
        p_ctrl->count  = num_bytes;
        p_ctrl->state  = SAU_LIN_STATE_SENDING_DATA;
    }

    sau_lin_extended_cfg_t const * const p_extend    = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    sau_uart_instance_ctrl_t           * p_uart_ctrl = (sau_uart_instance_ctrl_t *) p_extend->p_uart->p_ctrl;

#if SAU_LIN_CFG_MASTER_SUPPORT_ENABLE
    if (send_header)
    {
        /* Configure the baud rate for sending the break field */
        status = R_SAU_UART_BaudSet(p_uart_ctrl, p_extend->p_break_field_baudrate);
        FSP_ERROR_RETURN(FSP_SUCCESS == status, status);

        /* Calculation and set protected identifier */
        p_ctrl->last_pid = r_sau_lin_pid_calculate(p_transfer_params->id);

        p_ctrl->state = SAU_LIN_STATE_SENDING_BREAK_FIELD;
        p_data        = (uint8_t *) &g_header_break_field_word;
        num_bytes     = 1;
    }

#else
    FSP_PARAMETER_NOT_USED(send_header);
#endif

    status = R_SAU_UART_Write(p_uart_ctrl, p_data, num_bytes);

    return status;
}

#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Place the LIN bus in the active state by disabling wakeup interrupt
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *
 * @retval     FSP_SUCCESS               Transmission started successfully
 **********************************************************************************************************************/
static fsp_err_t r_sau_lin_set_state_active (sau_lin_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t status = FSP_SUCCESS;

    /* Disable IRQ interrupt */
    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    const external_irq_instance_t      * p_icu    = p_extend->p_icu;
    status        = R_ICU_ExternalIrqDisable(p_icu->p_ctrl);
    p_ctrl->state = SAU_LIN_STATE_NONE;

    return status;
}

#endif

/*******************************************************************************************************************//**
 * Abort communication
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *
 * @retval     FSP_SUCCESS               Communication aborted successfully
 **********************************************************************************************************************/
static fsp_err_t r_sau_lin_communication_abort (sau_lin_instance_ctrl_t * const p_ctrl)
{
    sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    fsp_err_t status = R_SAU_UART_Abort(p_extend->p_uart->p_ctrl, UART_DIR_RX_TX);
    FSP_ERROR_RETURN(FSP_SUCCESS == status, status);
    p_ctrl->p_data = NULL;
    p_ctrl->state  = SAU_LIN_STATE_NONE;
    p_ctrl->count  = 0;

    return status;
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to LIN instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sau_lin_call_callback (sau_lin_instance_ctrl_t * p_ctrl, lin_event_t event)
{
    sau_lin_extended_cfg_t const * const p_extend    = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    sau_uart_instance_ctrl_t           * p_uart_ctrl = p_extend->p_uart->p_ctrl;
    uint8_t received_bytes = (uint8_t) (p_ctrl->count - p_uart_ctrl->rx_count);

    lin_callback_args_t args;

    args.channel        = 0;           // not used for SAU LIN
    args.event          = event;
    args.pid            = p_ctrl->last_pid;
    args.p_context      = p_ctrl->p_context;
    args.checksum       = p_ctrl->checksum;
    args.bytes_received = received_bytes;

    p_ctrl->p_callback(&args);
}

#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Callback function called in the ICU driver callback function when LIN is used.
 *
 * @param[in]     p_args      ICU callback parameters
 *
 * @retval        none
 **********************************************************************************************************************/
void r_sau_lin_icu_callback (external_irq_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    /* Recover ISR context saved in open. */
    IRQn_Type irq = R_FSP_CurrentIrqGet();

    icu_instance_ctrl_t * p_icu_ctrl = (icu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    sau_lin_instance_ctrl_t * p_ctrl = (sau_lin_instance_ctrl_t *) p_icu_ctrl->p_context;

    r_sau_lin_set_state_active(p_ctrl);

    r_sau_lin_call_callback(p_ctrl, LIN_EVENT_RX_WAKEUP_COMPLETE);
}

#endif

#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * TAU driver callback function.
 *
 * Handles break field detection and baud rate adjustment during sync byte measurement.
 *
 * @param[in]     p_args      TAU callback parameters
 *
 * @retval        none
 **********************************************************************************************************************/
void r_sau_lin_tau_callback (timer_callback_args_t * p_args)
{
    if (TIMER_EVENT_CAPTURE_EDGE == p_args->event)
    {
        IRQn_Type irq = R_FSP_CurrentIrqGet();

        /* Recover ISR context saved in open. */
        tau_instance_ctrl_t * p_tau_ctrl = (tau_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

        sau_lin_instance_ctrl_t            * p_ctrl   = (sau_lin_instance_ctrl_t *) p_tau_ctrl->p_context;
        sau_lin_extended_cfg_t const * const p_extend = (sau_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
        uint32_t current_baud = r_sau_lin_uart_current_baudrate_get(p_extend->p_uart);

 #if SAU_LIN_AUTO_SYNC_SUPPORT_ENABLE
        if ((SAU_LIN_AUTO_SYNCHRONIZATION_ENABLE == p_extend->auto_synchronization) &&
            (SAU_LIN_STATE_AWAITING_SYNC_SIGNAL == p_ctrl->state))
        {
            /* Ignore the first measurement, refer to hardware manual: SAU > Operation of LIN Communication >
             * LIN Reception > Figure "Flowchart of LIN reception" */
            if ((0 < p_ctrl->sync_bits_received) && (SAU_LIN_PULSE_INTERVAL_MAX_COUNT > p_ctrl->sync_bits_received))
            {
                p_ctrl->sync_bits_sum += p_args->capture;
            }

            p_ctrl->sync_bits_received++;

            if (SAU_LIN_PULSE_INTERVAL_MAX_COUNT == p_ctrl->sync_bits_received)
            {
                uint32_t sync_baud = (p_extend->timer_clock_frequency / p_ctrl->sync_bits_sum) * 8;
                sau_uart_instance_ctrl_t * p_uart_ctrl   = p_extend->p_uart->p_ctrl;
                sau_uart_extended_cfg_t  * p_uart_extend = (sau_uart_extended_cfg_t *) p_uart_ctrl->p_cfg->p_extend;

                if ((r_sau_lin_verify_sync_baudrate(current_baud, sync_baud)) &&
                    (FSP_SUCCESS == R_SAU_UART_BaudCalculate(p_uart_ctrl, sync_baud, p_uart_extend->p_baudrate)))
                {
                    R_SAU_UART_BaudSet(p_uart_ctrl, p_uart_extend->p_baudrate);
                    p_ctrl->state = SAU_LIN_STATE_AWAITING_PID_SIGNAL;
                    R_SAU_UART_Read(p_uart_ctrl, &p_ctrl->last_pid, 1);
                }
                else
                {
                    p_ctrl->state = SAU_LIN_STATE_NONE;
                }

                R_TAU_LinMeasurementFuncSwitch(p_tau_ctrl, TAU_FUNCTION_LOW_LEVEL_WIDTH_MEASUREMENT);
            }
        }
        else
 #endif
        {
            uint32_t break_field_threshold_ticks =
                (SAU_LIN_DETECTED_BREAK_FIELD_WIDTH * p_extend->timer_clock_frequency) / current_baud;

            /* If the detected pulse width is 11 bits or more, it is judged as the break field.
             * See in hardware manual: SAU > Operation of LIN Communication > LIN Reception */
            if (p_args->capture >= break_field_threshold_ticks)
            {
                p_ctrl->state = SAU_LIN_STATE_AWAITING_SYNC_SIGNAL;

 #if SAU_LIN_AUTO_SYNC_SUPPORT_ENABLE
                if (SAU_LIN_AUTO_SYNCHRONIZATION_ENABLE == p_extend->auto_synchronization)
                {
                    p_ctrl->sync_bits_sum      = 0;
                    p_ctrl->sync_bits_received = 0;

                    R_TAU_LinMeasurementFuncSwitch(p_tau_ctrl, TAU_FUNCTION_INPUT_PULSE_INTERVAL_MEASUREMENT);
                }
                else
 #endif
                {
                    sau_uart_instance_ctrl_t * p_uart_ctrl = p_extend->p_uart->p_ctrl;
                    R_SAU_UART_Read(p_uart_ctrl, &p_ctrl->last_pid, 1);
                }
            }
        }
    }
}

 #if SAU_LIN_AUTO_SYNC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Helper function to verify synchronization baudrate.
 *
 * @param[in]  current_baud           Baudrate before synchronization
 * @param[in]  sync_baud              Baudrate measured by TAU after synchronization
 *
 * @return   1 if the sync baudrate within +-12.5% of baudrate before synchronization, 0 otherwise
 **********************************************************************************************************************/
static bool r_sau_lin_verify_sync_baudrate (uint32_t current_baud, uint32_t sync_baud)
{
    /* Compute absolute value of difference in bit duration */
    uint32_t delta = current_baud > sync_baud ? (current_baud - sync_baud) : (sync_baud - current_baud);

    /* Check that measured baudrate is within 12.5% of the current baudrate */
    uint32_t threshold = (current_baud >> 3U);

    return delta <= threshold;
}

 #endif

/*******************************************************************************************************************//**
 * Helper function to calculate the baud rate.
 *
 * @param[in]  p_uart           UART instance control
 *
 * @return     Baud rate [bps].
 **********************************************************************************************************************/
static uint32_t r_sau_lin_uart_current_baudrate_get (const uart_instance_t * p_uart)
{
    sau_uart_extended_cfg_t * p_uart_extend = (sau_uart_extended_cfg_t *) p_uart->p_cfg->p_extend;

    uint32_t peripheral_clock = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK);
    uint32_t fmck_clock       = peripheral_clock >> p_uart_extend->p_baudrate->prs;

    /* (Baud rate) = {Operation clock (fMCK) frequency of target channel} ÷ (SDRmn.STCLK[6:0] + 1) ÷ 2 [bps] */
    return (fmck_clock / (p_uart_extend->p_baudrate->stclk + 1)) >> 1;
}

#endif

/*******************************************************************************************************************//**
 * UART receive complete processing.
 *
 * @param[in] p_ctrl LIN instance control
 * @param[in] p_uart_ctrl UART instance control
 *
 * @retval        none
 **********************************************************************************************************************/
static void r_sau_lin_rx_complete (sau_lin_instance_ctrl_t * const p_ctrl, sau_uart_instance_ctrl_t * const p_uart_ctrl)
{
    lin_event_t event = LIN_EVENT_NONE;

    if (SAU_LIN_STATE_AWAITING_CHECKSUM == p_ctrl->state)
    {
#if SAU_LIN_CFG_CHECKSUM_SUPPORT_ENABLE
        if (p_ctrl->validate_checksum)
        {
            uint8_t sum = r_sau_lin_checksum_calculate(p_ctrl->last_pid,
                                                       p_ctrl->p_data,
                                                       p_ctrl->count,
                                                       p_ctrl->checksum_type);

            /* Validate checksum. At this point, p_ctrl->checksum contains the checksum over the data bytes. */
            event =
                (sum == p_ctrl->checksum) ? LIN_EVENT_RX_DATA_COMPLETE : LIN_EVENT_ERR_INVALID_CHECKSUM;
            p_ctrl->p_data = NULL;
            p_ctrl->state  = SAU_LIN_STATE_NONE;
        }

#else
        FSP_PARAMETER_NOT_USED(p_uart_ctrl);
#endif
    }
    else if (SAU_LIN_STATE_AWAITING_DATA == p_ctrl->state)
    {
#if SAU_LIN_CFG_CHECKSUM_SUPPORT_ENABLE
        if (p_ctrl->validate_checksum)
        {
            R_SAU_UART_Read(p_uart_ctrl, &p_ctrl->checksum, 1);

            p_ctrl->state = SAU_LIN_STATE_AWAITING_CHECKSUM;

            /* Since the checksum data has not yet been received, the callback call is not required now. */
            return;
        }
#endif
        event          = LIN_EVENT_RX_DATA_COMPLETE;
        p_ctrl->p_data = NULL;
        p_ctrl->state  = SAU_LIN_STATE_NONE;
    }

#if SAU_LIN_CFG_SLAVE_SUPPORT_ENABLE
    else if (SAU_LIN_STATE_AWAITING_PID_SIGNAL == p_ctrl->state)
    {
        uint8_t pid = p_ctrl->last_pid;

        if (r_sau_lin_pid_calculate(pid) != pid)
        {
            p_ctrl->state = SAU_LIN_STATE_NONE;
            event         = LIN_EVENT_ERR_PARITY;
        }
        else
        {
            p_ctrl->state = SAU_LIN_STATE_HEADER_RECEIVED;
            event         = LIN_EVENT_RX_HEADER_COMPLETE;
        }
    }
    else if (SAU_LIN_STATE_AWAITING_SYNC_SIGNAL == p_ctrl->state)
    {
        p_ctrl->state = SAU_LIN_STATE_AWAITING_PID_SIGNAL;
        R_SAU_UART_Read(p_uart_ctrl, &p_ctrl->last_pid, 1);
    }
#endif
    else
    {

        /* No conditions are met. */
        return;
    }

    if (event)
    {
        /* Call user callback */
        r_sau_lin_call_callback(p_ctrl, event);
    }
}

/*******************************************************************************************************************//**
 * UART transmit complete processing.
 *
 * @param[in] p_ctrl LIN instance control
 * @param[in] p_uart_ctrl UART instance control
 *
 * @retval        none
 **********************************************************************************************************************/
static void r_sau_lin_tx_complete (sau_lin_instance_ctrl_t * const p_ctrl, sau_uart_instance_ctrl_t * const p_uart_ctrl)
{
    lin_event_t event = LIN_EVENT_NONE;

    switch (p_ctrl->state)
    {
#if SAU_LIN_CFG_WAKEUP_SUPPORT_ENABLE
        case SAU_LIN_STATE_SENDING_WAKEUP:
        {
            FSP_PARAMETER_NOT_USED(p_uart_ctrl);
            event = LIN_EVENT_TX_WAKEUP_COMPLETE;

            break;
        }
#endif
#if SAU_LIN_CFG_MASTER_SUPPORT_ENABLE
        case SAU_LIN_STATE_SENDING_BREAK_FIELD:
        {
            sau_uart_extended_cfg_t * p_uart_extend = (sau_uart_extended_cfg_t *) p_uart_ctrl->p_cfg->p_extend;
            R_SAU_UART_BaudSet(p_uart_ctrl, p_uart_extend->p_baudrate);

            p_ctrl->state = SAU_LIN_STATE_SENDING_SYNC;
            R_SAU_UART_Write(p_uart_ctrl, &g_header_sync_word, 1);

            break;
        }

        case SAU_LIN_STATE_SENDING_SYNC:
        {
            p_ctrl->state = SAU_LIN_STATE_SENDING_PID;
            R_SAU_UART_Write(p_uart_ctrl, &(p_ctrl->last_pid), 1);

            break;
        }

        case SAU_LIN_STATE_SENDING_PID:
        {
            if (p_ctrl->p_data)
            {
                p_ctrl->state = SAU_LIN_STATE_SENDING_DATA;
                R_SAU_UART_Write(p_uart_ctrl, p_ctrl->p_data, p_ctrl->count);
            }
            else
            {
                event = LIN_EVENT_TX_HEADER_COMPLETE;
            }

            break;
        }
#endif
        case SAU_LIN_STATE_SENDING_DATA:
        {
#if SAU_LIN_CFG_CHECKSUM_SUPPORT_ENABLE
            if (p_ctrl->validate_checksum)
            {
                p_ctrl->validate_checksum = false;
                R_SAU_UART_Write(p_uart_ctrl, &p_ctrl->checksum, 1);

                /* Since the checksum data has not yet been sent, the callback call is not required now. */
                break;
            }
#endif
            FSP_PARAMETER_NOT_USED(p_uart_ctrl);
            p_ctrl->p_data = NULL;
            event          = LIN_EVENT_TX_DATA_COMPLETE;

            break;
        }

        default:
        {
            break;
        }
    }

    if (event)
    {
        /* Reset state */
        p_ctrl->state = SAU_LIN_STATE_NONE;

        /* Call user callback */
        r_sau_lin_call_callback(p_ctrl, event);
    }
}

/*******************************************************************************************************************//**
 * UART transfer error processing.
 *
 * @param[in]     p_args      UART callback parameters
 * @param[in]     p_ctrl      LIN instance control
 *
 * @retval        none
 **********************************************************************************************************************/
static void r_sau_lin_err_complete (sau_lin_instance_ctrl_t * const p_ctrl, uart_callback_args_t const * const p_args)
{
    lin_event_t event = LIN_EVENT_NONE;

    if (UART_EVENT_ERR_OVERFLOW == p_args->event)
    {
        event = LIN_EVENT_ERR_OVERRUN;
    }
    else if (UART_EVENT_ERR_FRAMING == p_args->event)
    {
        if ((p_ctrl->state <= SAU_LIN_STATE_AWAITING_SYNC_SIGNAL) || (NULL == p_ctrl->p_data))
        {

            /* In the break field signal phase, LIN will have a frame error exception that does not require a callback call. */
            return;
        }

        event = LIN_EVENT_ERR_FRAMING;
    }
    else
    {
        /* No handler. */
    }

    if (event)
    {
        /* Stop reception */
        r_sau_lin_communication_abort(p_ctrl);

        /* Call user callback */
        r_sau_lin_call_callback(p_ctrl, event);
    }
}

/*******************************************************************************************************************//**
 * Callback function called in the UART driver callback function when LIN is used.
 *
 * @param[in]     p_args      UART callback parameters
 *
 * @retval        none
 **********************************************************************************************************************/
void r_sau_lin_uart_callback (uart_callback_args_t * p_args)
{
    /* Recover ISR context saved in open. */
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    sau_uart_instance_ctrl_t * p_uart_ctrl = (sau_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    sau_lin_instance_ctrl_t  * p_ctrl      = (sau_lin_instance_ctrl_t *) p_uart_ctrl->p_context;

    if (UART_EVENT_RX_COMPLETE == p_args->event)
    {
        r_sau_lin_rx_complete(p_ctrl, p_uart_ctrl);
    }
    else if (UART_EVENT_TX_COMPLETE == p_args->event)
    {
        r_sau_lin_tx_complete(p_ctrl, p_uart_ctrl);
    }
    else if (UART_EVENT_RX_CHAR == p_args->event)
    {
        /* No handle for rx char data */
    }
    else
    {
        r_sau_lin_err_complete(p_ctrl, p_args);
    }
}
