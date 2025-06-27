/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_uarta.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef UARTA_CFG_RX_ENABLE
 #define UARTA_CFG_RX_ENABLE               1
#endif
#ifndef UARTA_CFG_TX_ENABLE
 #define UARTA_CFG_TX_ENABLE               1
#endif

/* "UART" in ASCII.  Used to determine if the control block is open. */
#define UARTA_OPEN                         (0x55415254)

/* UARTA parity bit mapping */
#define UARTA_PARITY_OFF_MAPPING           (0U)
#define UARTA_PARITY_ZERO_MAPPING          (1U)
#define UARTA_PARITY_ODD_MAPPING           (2U)
#define UARTA_PARITY_EVEN_MAPPING          (3U)

#define UARTA_MAX_TRANSFER_BYTES           (0x10000)

/* Number of clock select and divider */
#define UARTA_UATCK_UATSEL_COUNT           (4U)

/* Mask for valid mapping of uart_clock_div_t to UTA0CK.CK */
#define UARTA_CLOCK_DIV_MASK               (0x07U)

/* Maximum and minimum BRGCA*/
#define UARTA_BRGCA_MAX                    (255)
#define UARTA_BRGCA_MIN                    (2)

/* Mask 2 bit for bit UTA0CK.SEL[1:0] */
#define UARTA_UTA0SEL_MASK                 (0x03U)

/* DTC transfer setting information */
#define UARTA_DTC_RX_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |                \
                                            (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |                \
                                            (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) |        \
                                            (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |                     \
                                            (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS) | \
                                            (TRANSFER_REPEAT_AREA_DESTINATION << TRANSFER_SETTINGS_REPEAT_AREA_BITS))
#define UARTA_DTC_TX_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |               \
                                            (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |               \
                                            (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                            (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |                    \
                                            (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS) |      \
                                            (TRANSFER_REPEAT_AREA_SOURCE << TRANSFER_SETTINGS_REPEAT_AREA_BITS))

/* Wait time needs to be rounded up to enable TX/RX. */
#define UARTA_CONVERT_TO_MICRO_SECOND      (999999U)

#define UARTA_MAX_BAUD_RATE_ERROR_10PPM    (4740U)

/* Scaling factor for baud rate error values, 10ppm or .001% */
#define UARTA_BAUD_ERROR_SCALING_10PPM     (100000)

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
 #define UARTA_MAX_BAUD_RATE               (153600)
#endif

/***********************************************************************************************************************
 * Private constants
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * uarta_prv_ns_callback)(uart_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile uarta_prv_ns_callback)(uart_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_uarta_read_write_param_check(uarta_instance_ctrl_t const * const p_ctrl,
                                                uint8_t const * const               addr,
                                                uint32_t const                      bytes);

 #if (BSP_FEATURE_UARTA_PCLK_RESTRICTION)
static fsp_err_t r_uarta_operation_clock_validation(uarta_baud_setting_t const * const p_baud_setting);

 #endif

#endif

#if UARTA_CFG_DTC_SUPPORT_ENABLE
static fsp_err_t r_uarta_transfer_configure(uarta_instance_ctrl_t * const p_ctrl);
static fsp_err_t r_uarta_transfer_configure_helper(uarta_instance_ctrl_t     * p_ctrl,
                                                   transfer_instance_t const * p_transfer,
                                                   uart_dir_t                  direction);

#endif

static void r_uarta_baud_set(uarta_instance_ctrl_t * p_ctrl, uarta_baud_setting_t const * const p_baud_setting);

static void r_uarta_call_callback(uarta_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event);

static uint16_t r_uarta_calculate_wait_time(uarta_baud_setting_t const * const p_baud_setting);

#if (UARTA_CFG_RX_ENABLE)

void uarta_rxi_isr(void);
void uarta_eri_isr(void);

#endif

#if (UARTA_CFG_TX_ENABLE)

void uarta_txi_isr(void);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Look-up table for parity values */
static const uint8_t uarta_parity_lut[] =
{
    [UART_PARITY_OFF]  = UARTA_PARITY_OFF_MAPPING << R_UARTA0_ASIMAn1_PS_Pos,
    [UART_PARITY_ZERO] = UARTA_PARITY_ZERO_MAPPING << R_UARTA0_ASIMAn1_PS_Pos,
    [UART_PARITY_EVEN] = UARTA_PARITY_EVEN_MAPPING << R_UARTA0_ASIMAn1_PS_Pos,
    [UART_PARITY_ODD]  = UARTA_PARITY_ODD_MAPPING << R_UARTA0_ASIMAn1_PS_Pos
};

/** Look-up table for converting UARTA clock source, used to get the clock value from R_BSP_SourceClockHzGet */
static fsp_priv_source_clock_t uarta_f_uta0_sel_lut[] =
{
    [UARTA_CLOCK_SOURCE_SOSC_LOCO] = FSP_PRIV_CLOCK_LOCO,
    [UARTA_CLOCK_SOURCE_SOSC]      = FSP_PRIV_CLOCK_SUBCLOCK,
    [UARTA_CLOCK_SOURCE_MOSC]      = FSP_PRIV_CLOCK_MAIN_OSC,
    [UARTA_CLOCK_SOURCE_HOCO]      = FSP_PRIV_CLOCK_HOCO,
    [UARTA_CLOCK_SOURCE_MOCO]      = FSP_PRIV_CLOCK_MOCO
};

#if (UARTA_CFG_RX_ENABLE)

/** Look-up table for event types */
static const uint8_t uarta_event_lut[] =
{
    [0] = 0,
    [1] = UART_EVENT_ERR_OVERFLOW,
    [2] = UART_EVENT_ERR_FRAMING,
    [3] = UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING,
    [4] = UART_EVENT_ERR_PARITY,
    [5] = UART_EVENT_ERR_PARITY | UART_EVENT_ERR_OVERFLOW,
    [6] = UART_EVENT_ERR_PARITY | UART_EVENT_ERR_FRAMING,
    [7] = UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING | UART_EVENT_ERR_PARITY
};

 #define UARTA_ASISA_RCVR_ERR_MASK    (R_UARTA0_ASISAn_OVEA_Msk | R_UARTA0_ASISAn_FEA_Msk | R_UARTA0_ASISAn_PEA_Msk)

#endif

/* UART on UARTA HAL API mapping for UART interface */
const uart_api_t g_uart_on_uarta =
{
    .open               = R_UARTA_Open,
    .close              = R_UARTA_Close,
    .write              = R_UARTA_Write,
    .read               = R_UARTA_Read,
    .infoGet            = R_UARTA_InfoGet,
    .baudSet            = R_UARTA_BaudSet,
    .communicationAbort = R_UARTA_Abort,
    .callbackSet        = R_UARTA_CallbackSet,
    .readStop           = R_UARTA_ReadStop,
    .receiveSuspend     = R_UARTA_ReceiveSuspend,
    .receiveResume      = R_UARTA_ReceiveResume,
};

/*******************************************************************************************************************//**
 * @addtogroup UARTA
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the UARTA driver based on the input configurations. If transmission/reception is enabled at compile time,
 * transmission/reception is enabled at the end of this function. Implements @ref uart_api_t::open
 *
 * @retval  FSP_SUCCESS                    Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to UARTA control block or configuration structure is NULL.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT The requested channel does not exist on this MCU.
 * @retval  FSP_ERR_INVALID_ARGUMENT       Invalid clock select (f_UTA0) and baudrate configuration.
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::open
 **********************************************************************************************************************/
fsp_err_t R_UARTA_Open (uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg)
{
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ASSERT(p_cfg->p_extend);
    FSP_ASSERT(((uarta_extended_cfg_t *) p_cfg->p_extend)->p_baud_setting);
    FSP_ERROR_RETURN(UARTA_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(((1 << p_cfg->channel) & BSP_PERIPHERAL_UARTA_CHANNEL_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);

 #if (UARTA_CFG_RECEIVE_ERROR_INTERRUPT_MODE == 0)

    /* UARTA0_ERRI interrupt request should be greater than 0 when Receive Error Interrupt Mode is disabled */
    FSP_ASSERT(p_cfg->eri_irq >= 0);
 #endif

 #if (BSP_FEATURE_UARTA_PCLK_RESTRICTION)

    /* Validate the f_uta before setting the baud rate*/
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     r_uarta_operation_clock_validation(((uarta_extended_cfg_t *) p_cfg->p_extend)->p_baud_setting),
                     FSP_ERR_INVALID_ARGUMENT);
 #endif
#endif

    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

#if (BSP_PERIPHERAL_UARTA_CHANNEL_MASK > 1)

    /* Calculate the register base address. */
    uint32_t address_gap = (uint32_t) R_UARTA1 - (uint32_t) R_UARTA0;
    p_ctrl->p_reg = (R_UARTA0_Type *) ((uint32_t) R_UARTA0 + (address_gap * p_cfg->channel));
#else
    p_ctrl->p_reg = R_UARTA0;
#endif

#if UARTA_CFG_DTC_SUPPORT_ENABLE

    /* Configure the transfer interface for transmission and reception if provided. */
    err = r_uarta_transfer_configure(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Enable the UARTA channel */
    R_BSP_MODULE_START(FSP_IP_UARTA, 0);

    /* Set the UART configuration settings provided in ::uart_cfg_t and :: uarta_extended_cfg_t. */
    uarta_extended_cfg_t * p_extend = (uarta_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Set the baud rate settings for the internal baud rate generator. */
    r_uarta_baud_set(p_ctrl, p_extend->p_baud_setting);

    /* Setting parity, length, stop, direction, and level bit */
    p_ctrl->p_reg->ASIMAn1 = (uint8_t) (uarta_parity_lut[p_cfg->parity] |
                                        ((uint8_t) (p_cfg->data_bits << R_UARTA0_ASIMAn1_CL_Pos)) |
                                        ((uint8_t) (p_cfg->stop_bits << R_UARTA0_ASIMAn1_SL_Pos)) |
                                        ((uint8_t) (p_extend->transfer_dir << R_UARTA0_ASIMAn1_DIR_Pos)) |
                                        ((uint8_t) (p_extend->transfer_level << R_UARTA0_ASIMAn1_ALV_Pos)));

    /* Setting interrupt for continuous transmission and receive interrupt mode select */
    uint8_t asima0 = (uint8_t) ((R_UARTA0_ASIMAn0_ISSMA_Msk) |
                                ((uint8_t) (UARTA_CFG_RECEIVE_ERROR_INTERRUPT_MODE << R_UARTA0_ASIMAn0_ISRMA_Pos)));

    /* Configure for register ASIMA0 */
    p_ctrl->p_reg->ASIMAn0 = asima0;

    /* Enables the UARTA operation clock */
    asima0                |= R_UARTA0_ASIMAn0_EN_Msk;
    p_ctrl->p_reg->ASIMAn0 = asima0;

#if (UARTA_CFG_RX_ENABLE)
    p_ctrl->rx_dest_bytes = 0;

    /* If reception is enabled at build time, enable reception. */
    asima0 |= R_UARTA0_ASIMAn0_RXEA_Msk;
#endif

#if (UARTA_CFG_TX_ENABLE)
    p_ctrl->tx_src_bytes = 0;

    /* If transmission is enabled at build time, enable transmission. */
    asima0 |= R_UARTA0_ASIMAn0_TXEA_Msk;
#endif

    p_ctrl->p_reg->ASIMAn0 = asima0;

#if (UARTA_CFG_RX_ENABLE)
 #if (UARTA_CFG_RECEIVE_ERROR_INTERRUPT_MODE == 0)
    R_BSP_IrqCfgEnable(p_cfg->eri_irq, p_cfg->eri_ipl, p_ctrl);
 #endif
    R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->rxi_ipl, p_ctrl);
#endif

#if (UARTA_CFG_TX_ENABLE)

    /* Wait for at least one cycle of the UARTA operation clock
     * See in hardware manual: UARTA > Register Descriptions > ASIMA00 > Note */
    R_BSP_SoftwareDelay(p_extend->p_baud_setting->delay_time, BSP_DELAY_UNITS_MICROSECONDS);

    R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->txi_ipl, p_ctrl);
#endif

    p_ctrl->open = UARTA_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Aborts any in progress transfers. Disables interrupts, receiver, and transmitter.  Closes lower level transfer
 * drivers if used. Removes power. Implements @ref uart_api_t::close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to UARTA control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_UARTA_Close (uart_ctrl_t * const p_api_ctrl)
{
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uart_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Mark UARTA not open so it can be used again. */
    p_ctrl->open = 0;

    /* Disable receiver, and transmitter. */
    uint8_t current_value = p_ctrl->p_reg->ASIMAn0;

    /* Do read-modify-write for TXEA/RXEA */
    current_value &= (uint8_t) ~(R_UARTA0_ASIMAn0_TXEA_Msk | R_UARTA0_ASIMAn0_RXEA_Msk);

    p_ctrl->p_reg->ASIMAn0 = current_value;

    /* Disable baud clock output. Must be done separately after disabling TX/RX. */
    p_ctrl->p_reg->ASIMAn0 = (uint8_t) (current_value & ~R_UARTA0_ASIMAn0_EN_Msk);

#if (UARTA_CFG_RX_ENABLE)
 #if (UARTA_CFG_RECEIVE_ERROR_INTERRUPT_MODE == 0)
    R_BSP_IrqDisable(p_cfg->eri_irq);
 #endif

    /* If reception is enabled at build time, disable reception irqs. */
    R_BSP_IrqDisable(p_cfg->rxi_irq);
#endif
#if (UARTA_CFG_TX_ENABLE)

    /* If transmission is enabled at build time, disable transmission irqs. */
    R_BSP_IrqDisable(p_cfg->txi_irq);
#endif

#if UARTA_CFG_DTC_SUPPORT_ENABLE
 #if (UARTA_CFG_RX_ENABLE)
    transfer_instance_t const * p_transfer_rx = p_cfg->p_transfer_rx;
    if (NULL != p_transfer_rx)
    {
        p_transfer_rx->p_api->close(p_transfer_rx->p_ctrl);
    }
 #endif
 #if (UARTA_CFG_TX_ENABLE)
    transfer_instance_t const * p_transfer_tx = p_cfg->p_transfer_tx;
    if (NULL != p_transfer_tx)
    {
        p_transfer_tx->p_api->close(p_transfer_tx->p_ctrl);
    }
 #endif
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Receives user specified number of bytes into destination buffer pointer. Implements @ref uart_api_t::read
 *
 * @retval  FSP_SUCCESS                  Data reception successfully ends.
 * @retval  FSP_ERR_ASSERTION            Pointer to UARTA control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A previous read operation is still in progress.
 * @retval  FSP_ERR_UNSUPPORTED          UARTA_CFG_RX_ENABLE is set to 0
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reset
 *
 **********************************************************************************************************************/
fsp_err_t R_UARTA_Read (uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
#if (UARTA_CFG_RX_ENABLE)
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;

 #if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    err = r_uarta_read_write_param_check(p_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->rx_dest_bytes, FSP_ERR_IN_USE);
 #endif

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    transfer_instance_t const * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;

    /* Configure transfer instance to receive the requested number of bytes if transfer is used for reception. */
    if (NULL != p_transfer_rx)
    {
        err = p_transfer_rx->p_api->reset(p_transfer_rx->p_ctrl, NULL, (void *) p_dest, (uint16_t) bytes);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    /* Save the destination address and size for use in rxi_isr. */
    p_ctrl->p_rx_dest     = p_dest;
    p_ctrl->rx_dest_bytes = bytes;

    return err;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(bytes);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Transmits user specified number of bytes from the source buffer pointer. Implements @ref uart_api_t::write
 *
 * @retval  FSP_SUCCESS                  Data transmission finished successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UARTA control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A UARTA transmission is in progress
 * @retval  FSP_ERR_UNSUPPORTED          UART_CFG_TX_ENABLE is set to 0
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reset
 *
 **********************************************************************************************************************/
fsp_err_t R_UARTA_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
#if (UARTA_CFG_TX_ENABLE)
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
 #if UARTA_CFG_PARAM_CHECKING_ENABLE || UARTA_CFG_DTC_SUPPORT_ENABLE
    fsp_err_t err = FSP_SUCCESS;
 #endif

 #if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    err = r_uarta_read_write_param_check(p_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->tx_src_bytes, FSP_ERR_IN_USE);
 #endif

    /* Disable transmit interrupt */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

    /* The first data will be assigned to TXBA0, Get the next value for the next transmit */
    p_ctrl->p_tx_src = p_src + 1;
    uint32_t num_transfers = bytes - 1;

 #if UARTA_CFG_DTC_SUPPORT_ENABLE

    /* If a transfer instance is used for transmission, reset the transfer instance to transmit the requested
     * data. */
    transfer_instance_t const * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
    if ((NULL != p_transfer_tx) && (num_transfers))
    {
  #if (UARTA_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(num_transfers <= UARTA_MAX_TRANSFER_BYTES);
  #endif

        err = p_transfer_tx->p_api->reset(p_transfer_tx->p_ctrl,
                                          (void const *) p_ctrl->p_tx_src,
                                          NULL,
                                          (uint16_t) num_transfers);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    p_ctrl->tx_src_bytes           = num_transfers;
    p_ctrl->p_reg->ASIMAn0_b.ISSMA = 1;

    /* Enable transmit interrupt */
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);

    /* Assign to first byte */
    p_ctrl->p_reg->TXBAn = *(p_src);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(bytes);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements uart_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_UARTA_CallbackSet (uart_ctrl_t * const          p_api_ctrl,
                               void (                     * p_callback)(uart_callback_args_t *),
                               void * const                 p_context,
                               uart_callback_args_t * const p_callback_memory)
{
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
#if UARTA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if UARTA_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    uart_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                       CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(uart_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the baud rate using the clock selected in Open. p_baud_setting is a pointer to a uarta_baud_setting_t
 * structure.
 * Implements @ref uart_api_t::baudSet
 *
 * @warning This terminates any in-progress transmission.
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer to UARTA control block is NULL or the UART is not configured to use the
 *                                       internal clock.
 * @retval  FSP_ERR_INVALID_ARGUMENT       Invalid clock select (f_UTA0) and baudrate configuration.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_UARTA_BaudSet (uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting)
{
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #if (BSP_FEATURE_UARTA_PCLK_RESTRICTION)
    FSP_ERROR_RETURN(FSP_SUCCESS ==
                     r_uarta_operation_clock_validation(p_baud_setting),
                     FSP_ERR_INVALID_ARGUMENT);
 #endif
#endif

    /* Disable transmit interrupt.  Resuming transmission after reconfiguring baud settings is
     * not supported. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

    uint8_t preserved_asiman0 = p_ctrl->p_reg->ASIMAn0;

    /* Modify the BRGCAn bits while the TXEAn and RXEAn bits are 0 (in the transmission/reception stopped state).*/
    p_ctrl->p_reg->ASIMAn0 = (preserved_asiman0 & (uint8_t) (~(R_UARTA0_ASIMAn0_RXEA_Msk | R_UARTA0_ASIMAn0_TXEA_Msk)));

    /* Apply new baud rate register settings. */
    r_uarta_baud_set(p_ctrl, p_baud_setting);

    /* To enable transmission or reception again, set the TXEAn or RXEAn bit to 1 at least two cycles of the UARTAn
     * operation clock after clearing the TXEAn or RXEAn bit to 0
     * See in hardware manual: UARTA > Register Descriptions > ASIMA00 > Note */
    uint16_t delay_time = r_uarta_calculate_wait_time(p_baud_setting);
    R_BSP_SoftwareDelay((uint32_t) delay_time << 1U, BSP_DELAY_UNITS_MICROSECONDS);

    /* Restore all settings. */
    p_ctrl->p_reg->ASIMAn0 = preserved_asiman0;
#if (UARTA_CFG_TX_ENABLE)

    /* If transmission is enabled at build time, enable transmission. */
    if (preserved_asiman0 & R_UARTA0_ASIMAn0_TXEA_Msk)
    {
        /* Wait for at least one cycle of the UARTA operation clock
         * See in hardware manual: UARTA > Register Descriptions > ASIMA00 > Note */
        R_BSP_SoftwareDelay((uint32_t) delay_time, BSP_DELAY_UNITS_MICROSECONDS);
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the driver information, including the maximum number of bytes that can be received or transmitted at a time.
 * Implements @ref uart_api_t::infoGet
 *
 * @retval  FSP_SUCCESS                  Information stored in provided p_info.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_UARTA_InfoGet (uart_ctrl_t * const p_api_ctrl, uart_info_t * const p_info)
{
#if UARTA_CFG_PARAM_CHECKING_ENABLE
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_info);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

    p_info->read_bytes_max  = UARTA_MAX_TRANSFER_BYTES;
    p_info->write_bytes_max = UARTA_MAX_TRANSFER_BYTES;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides API to abort ongoing transfer. Transmission is aborted after the current character is transmitted.
 * Reception is still enabled after abort(). Any characters received after abort() and before the transfer
 * is reset in the next call to read(), will arrive via the callback function with event UART_EVENT_RX_CHAR.
 * Implements @ref uart_api_t::communicationAbort
 *
 * @retval  FSP_SUCCESS                  UARTA transaction aborted successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UARTA control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls: @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_UARTA_Abort (uart_ctrl_t * const p_api_ctrl, uart_dir_t communication_to_abort)
{
#if (UARTA_CFG_PARAM_CHECKING_ENABLE) || (UARTA_CFG_TX_ENABLE) || (UARTA_CFG_RX_ENABLE)
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
#endif
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (UARTA_CFG_TX_ENABLE)
    if (UART_DIR_TX & communication_to_abort)
    {
        err = FSP_SUCCESS;

        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
        transfer_instance_t const * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
        if (NULL != p_transfer_tx)
        {
            err = p_transfer_tx->p_api->disable(p_transfer_tx->p_ctrl);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }
 #endif
        p_ctrl->tx_src_bytes = 0;
    }
#endif

#if (UARTA_CFG_RX_ENABLE)
    if (UART_DIR_RX & communication_to_abort)
    {
        err = FSP_SUCCESS;

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
        transfer_instance_t const * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;
        if (NULL != p_transfer_rx)
        {
            err = p_transfer_rx->p_api->disable(p_transfer_rx->p_ctrl);
        }
 #endif
        p_ctrl->rx_dest_bytes = 0U;
    }
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Provides API to abort ongoing read. Reception is still enabled after abort(). Any characters received after abort()
 * and before the transfer is reset in the next call to read(), will arrive via the callback function with event
 * UART_EVENT_RX_CHAR.
 * Implements @ref uart_api_t::readStop
 *
 * @retval  FSP_SUCCESS                  UARTA transaction aborted successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UARTA control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls: @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_UARTA_ReadStop (uart_ctrl_t * const p_api_ctrl, uint32_t * p_remaining_bytes)
{
#if (UARTA_CFG_RX_ENABLE)
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;

 #if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    uint32_t remaining_bytes = p_ctrl->rx_dest_bytes;
    p_ctrl->rx_dest_bytes = 0;

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    transfer_instance_t const * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;
    if (NULL != p_transfer_rx)
    {
        fsp_err_t err = p_transfer_rx->p_api->disable(p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        transfer_properties_t transfer_info;
        err = p_transfer_rx->p_api->infoGet(p_transfer_rx->p_ctrl, &transfer_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        remaining_bytes = transfer_info.transfer_length_remaining;
    }
 #endif

    *p_remaining_bytes = remaining_bytes;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_remaining_bytes);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Calculates baud rate register settings. Evaluates and determines the best possible settings set to the baud rate
 * related registers.
 *
 * @param[in]  baudrate                      Baud rate [bps]. For example, 19200, 57600, 115200, etc.
 * @param[in]  baud_rate_percent_error_x1000 Max baud rate error. At most baud_rate_percent_error x 1000 required
 *                                           for module to function. Absolute max baud_rate_error is 4740 (4.74%).
 * @param[in]  clock_source                  Clock Source. Required for module to generate baudrate. The clock sources
 *                                           can be select include UARTA_CLOCK_SOURCE_MOSC, UARTA_CLOCK_SOURCE_HOCO,
 *                                           UARTA_CLOCK_SOURCE_MOCO, UARTA_CLOCK_SOURCE_SOSC_LOCO.
 * @param[out] p_baud_setting                Baud setting information stored here if successful
 *
 * @retval     FSP_SUCCESS               Baud rate is set successfully
 * @retval     FSP_ERR_ASSERTION         Null pointer
 * @retval     FSP_ERR_INVALID_ARGUMENT  Argument is out of available range, baud rate is '0'.
 * @retval     FSP_ERR_INVALID_RATE      Baud rate error is outside the range or the baud rate could not be set given
 *                                       the current clock source.
 **********************************************************************************************************************/
fsp_err_t R_UARTA_BaudCalculate (uint32_t                     baudrate,
                                 uint32_t                     baud_rate_percent_error_x1000,
                                 uarta_clock_source_t         clock_source,
                                 uarta_baud_setting_t * const p_baud_setting)
{
#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_baud_setting);
    FSP_ERROR_RETURN(UARTA_MAX_BAUD_RATE_ERROR_10PPM >= baud_rate_percent_error_x1000, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(UARTA_MAX_BAUD_RATE >= baudrate, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0U != baudrate), FSP_ERR_INVALID_ARGUMENT);
#endif

    fsp_err_t ret = FSP_ERR_INVALID_RATE;

    /* UARTA_MAX_BAUD_RATE * UARTA_MAX_BAUD_RATE_ERROR_10PPM < UINT32_MAX */
    uint32_t delta_max = baudrate * baud_rate_percent_error_x1000 / UARTA_BAUD_ERROR_SCALING_10PPM;

    uint32_t clock_source_value = R_BSP_SourceClockHzGet(uarta_f_uta0_sel_lut[clock_source]);

#if (BSP_FEATURE_UARTA_PCLK_RESTRICTION)
    uint32_t pclk_constraint = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);
#endif

    /* Go ahead and set the clock source here. It stays constant through the baud rate search. */
    p_baud_setting->utanck_clock_b.utasel = (uint8_t) (clock_source & UARTA_UTA0SEL_MASK);

    for (uarta_clock_div_t f_uta0_div = UARTA_CLOCK_DIV_1; f_uta0_div < UARTA_CLOCK_DIV_COUNT; f_uta0_div++)
    {
        /* Calculate UARTA operation clock (f_UTA0)*/
        uint32_t f_uta0_value = clock_source_value >> f_uta0_div;

        /* Find the appropriate divider for the requested baud rate.
         * divider = round(f_UTA0 / (2 * Desired baud rate))
         * Integer round to the nearest divider.
         */
        uint32_t divider = ((f_uta0_value + baudrate) >> 1) / baudrate;
        if ((divider >= UARTA_BRGCA_MIN) && (divider <= UARTA_BRGCA_MAX)
#if (BSP_FEATURE_UARTA_PCLK_RESTRICTION)
            && (f_uta0_value <= pclk_constraint)
#endif
            )
        {
            /* Calculate actual baudrate using the divider. */
            uint32_t actual_baudrate = (f_uta0_value >> 1) / divider;
            uint32_t delta           = baudrate >=
                                       actual_baudrate ? (baudrate - actual_baudrate) : (actual_baudrate - baudrate);
            if (delta < delta_max)
            {
                delta_max                             = delta;
                p_baud_setting->brgca                 = (uint8_t) divider;
                p_baud_setting->utanck_clock_b.utanck = (uint8_t) (f_uta0_div & R_UARTA_CK_UTAnCK_CK_Msk);
                ret = FSP_SUCCESS;
            }
        }

        if (UARTA_CLOCK_SOURCE_LOCO == clock_source)
        {
            p_baud_setting->utanck_clock_b.utanck = UARTA_UTAnCK_LOCO_SETTING;
            break;
        }

#if (!BSP_FEATURE_BSP_HAS_FSXP_CLOCK)
        if (UARTA_CLOCK_SOURCE_SOSC == clock_source)
        {
            p_baud_setting->utanck_clock_b.utanck = UARTA_UTAnCK_SOSC_SETTING;
            break;
        }
#endif
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Suspend Reception
 *
 * @retval     FSP_ERR_UNSUPPORTED       Functionality not supported by this driver instance
 **********************************************************************************************************************/
fsp_err_t R_UARTA_ReceiveSuspend (uart_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Resume Reception
 *
 * @retval     FSP_ERR_UNSUPPORTED       Functionality not supported by this driver instance
 **********************************************************************************************************************/
fsp_err_t R_UARTA_ReceiveResume (uart_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup UARTA)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Parameter error check function for read/write.
 *
 * @param[in] p_ctrl Pointer to the control block for the channel
 * @param[in] addr   Pointer to the buffer
 * @param[in] bytes  Number of bytes to read or write
 *
 * @retval  FSP_SUCCESS              No parameter error found
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 * @retval  FSP_ERR_ASSERTION        Pointer to UARTA control block or configuration structure is NULL
 **********************************************************************************************************************/
static fsp_err_t r_uarta_read_write_param_check (uarta_instance_ctrl_t const * const p_ctrl,
                                                 uint8_t const * const               addr,
                                                 uint32_t const                      bytes)
{
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(addr);
    FSP_ASSERT(0U != bytes);
    FSP_ASSERT(UARTA_MAX_TRANSFER_BYTES >= bytes);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

#endif

#if UARTA_CFG_DTC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Subroutine to apply common UARTA transfer settings.
 *
 * @param[in]  p_ctrl             Pointer to instance control block.
 *
 * @retval     FSP_SUCCESS        UARTA transfer drivers successfully configured
 * @retval     FSP_ERR_ASSERTION  Invalid pointer
 **********************************************************************************************************************/
static fsp_err_t r_uarta_transfer_configure (uarta_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

 #if (UARTA_CFG_RX_ENABLE)
    transfer_instance_t const * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;

    /* If a transfer instance is used for reception, apply UART specific settings and open the transfer instance. */
    err = r_uarta_transfer_configure_helper(p_ctrl, p_transfer_rx, UART_DIR_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif

 #if (UARTA_CFG_TX_ENABLE)
    transfer_instance_t const * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    /* If a transfer instance is used for transmission, apply UART specific settings and open the transfer instance. */
    err = r_uarta_transfer_configure_helper(p_ctrl, p_transfer_tx, UART_DIR_TX);
  #if (UARTA_CFG_RX_ENABLE)
    if ((err != FSP_SUCCESS) && (NULL != p_transfer_rx))
    {
        p_transfer_rx->p_api->close(p_transfer_rx->p_ctrl);
    }
  #endif
 #endif

    return err;
}

/*******************************************************************************************************************//**
 * This function initializes transfer descriptor
 *
 * @param[in] p_transfer                     Pointer to transfer instance.
 * @param[in] direction                      UART_DIR_TX or UART_DIR_RX.
 **********************************************************************************************************************/
static fsp_err_t r_uarta_transfer_configure_helper (uarta_instance_ctrl_t * const p_ctrl,
                                                    transfer_instance_t const   * p_transfer,
                                                    uart_dir_t                    direction)
{
    fsp_err_t err = FSP_SUCCESS;

    if (NULL != p_transfer)
    {
        /* Configure the transfer instance, if enabled. */
 #if (UARTA_CFG_PARAM_CHECKING_ENABLE)
        FSP_ASSERT(NULL != p_transfer->p_api);
        FSP_ASSERT(NULL != p_transfer->p_ctrl);
        FSP_ASSERT(NULL != p_transfer->p_cfg);
        FSP_ASSERT(NULL != p_transfer->p_cfg->p_info);
        FSP_ASSERT(NULL != p_transfer->p_cfg->p_extend);
 #endif

        transfer_info_t * p_info = p_transfer->p_cfg->p_info;

        /* Casting for compatibility with 5, 7 or 8 bit mode. */
        if (UART_DIR_RX == direction)
        {
            p_info->transfer_settings_word = UARTA_DTC_RX_TRANSFER_SETTINGS;
            p_info->p_src = (void *) &(p_ctrl->p_reg->RXBAn);
        }
        else
        {
            p_info->transfer_settings_word = UARTA_DTC_TX_TRANSFER_SETTINGS;
            p_info->p_dest                 = (void *) &(p_ctrl->p_reg->TXBAn);
        }

        err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    }

    return err;
}

#endif

/*******************************************************************************************************************//**
 * Changes baud rate based on predetermined register settings.
 *
 * @param[in]  p_ctrl            Pointer to instance control block.
 * @param[in]  p_baud_setting    Pointer to other divisor related settings
 *
 * @note   The transmitter and receiver (TXEA and RXEA bits in ASIMA00) must be disabled prior to calling this function.
 **********************************************************************************************************************/
static void r_uarta_baud_set (uarta_instance_ctrl_t * p_ctrl, uarta_baud_setting_t const * const p_baud_setting)
{
    /* Set BRGCA register value. */
    p_ctrl->p_reg->BRGCAn = p_baud_setting->brgca;
    uint8_t utack_value = p_baud_setting->utanck_clock;

#if (BSP_FEATURE_UARTA_HAS_CLOCK_OUTPUT)

    /* Set the UART configuration settings provided in ::uart_cfg_t and :: uarta_extended_cfg_t. */
    utack_value |= (uint8_t) (((uarta_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clock_output <<
                              R_UARTA_CK_UTAnCK_EN_Pos);
#endif

    /* Set UTA0CK/UTA1CK register value. */
    R_UARTA_CK->UTAnCK[p_ctrl->p_cfg->channel] = utack_value;

#if (BSP_PERIPHERAL_UARTA_CHANNEL_MASK > 1)

    /* Set fSEL clock select */
    R_UARTA_CK->UTAnCK_b[0].SEL = p_baud_setting->utanck_clock_b.utasel;
#endif
}

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
 #if (BSP_FEATURE_UARTA_PCLK_RESTRICTION)

/*******************************************************************************************************************//**
 * Validates the baud rate divisor for the given UARTA clock frequency against PCLK constraints.
 *
 * This function checks if the UARTA operation clock (derived from the frequency settings of the baud rate generator)
 * is within acceptable limits as defined by the PCLK.
 *
 * @param[in]  p_baud_setting       Pointer to the baud rate settings structure which includes the UARTA clock selection.
 * @retval FSP_SUCCESS              The UARTA operation clock is within acceptable limits.
 * @retval FSP_ERR_INVALID_ARGUMENT The UARTA operation clock exceeds PCLK constraints.
 **********************************************************************************************************************/
static fsp_err_t r_uarta_operation_clock_validation (uarta_baud_setting_t const * const p_baud_setting)
{
    /* Retrieve the PCLKB constraint and operation clock uarta value */
    uint32_t pclk_constraint    = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);
    uint32_t clock_source_value = R_BSP_SourceClockHzGet(uarta_f_uta0_sel_lut[p_baud_setting->utanck_clock_b.utasel]);
    uint32_t f_uta              = clock_source_value >> (p_baud_setting->utanck_clock_b.utanck & UARTA_CLOCK_DIV_MASK);

    /* Check if UARTA operation clock exceeds the PCLK constraint */
    if (f_uta > pclk_constraint)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    return FSP_SUCCESS;
}

 #endif
#endif

/*******************************************************************************************************************//**
 * This function calculates the wait time to enable TX
 *
 * @param[in] p_baud_setting         Pointer to baud rate settings.
 **********************************************************************************************************************/
static uint16_t r_uarta_calculate_wait_time (uarta_baud_setting_t const * const p_baud_setting)
{
    uint8_t utanck = p_baud_setting->utanck_clock_b.utanck;
    uint8_t utasel = p_baud_setting->utanck_clock_b.utasel;

    /* Get UARTA clock divider shift.
     * Anything outside UARTA_CLOCK_DIV_MASK is not a valid divider and is probably LOCO/SOSC selection instead.
     */
    uint32_t divider_shift = (uint32_t) (utanck & UARTA_CLOCK_DIV_MASK);

    /* Calculate frequency UARTA0 operation clock */
    uint32_t f_uta0 = (R_BSP_SourceClockHzGet(uarta_f_uta0_sel_lut[utasel]) >> divider_shift);

    /* Round up especially for the use case f_uta0 > UARTA_CONVERT_TO_MICRO_SECOND */
    return (uint16_t) ((UARTA_CONVERT_TO_MICRO_SECOND + f_uta0) / f_uta0);
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to UARTA instance control block
 * @param[in]     data       See uart_callback_args_t in r_uart_api.h
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_uarta_call_callback (uarta_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event)
{
    if (NULL != p_ctrl->p_callback)
    {
        uart_callback_args_t args;

        /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
         * stored in non-secure memory so they can be accessed by a non-secure callback function. */
        uart_callback_args_t * p_args = p_ctrl->p_callback_memory;
        if (NULL == p_args)
        {
            /* Store on stack */
            p_args = &args;
        }
        else
        {
            /* Save current arguments on the stack in case this is a nested interrupt. */
            args = *p_args;
        }

        p_args->channel   = p_ctrl->p_cfg->channel;
        p_args->data      = data;
        p_args->event     = event;
        p_args->p_context = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

        /* p_callback can point to a secure function or a non-secure function. */
        if (!cmse_is_nsfptr(p_ctrl->p_callback))
        {
            /* If p_callback is secure, then the project does not need to change security state. */
            p_ctrl->p_callback(p_args);
        }
        else
        {
            /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
            uarta_prv_ns_callback p_callback = (uarta_prv_ns_callback) (p_ctrl->p_callback);
            p_callback(p_args);
        }

#else

        /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
        p_ctrl->p_callback(p_args);
#endif
        if (NULL != p_ctrl->p_callback_memory)
        {
            /* Restore callback memory in case this is a nested interrupt. */
            *p_ctrl->p_callback_memory = args;
        }
    }
}

#if (UARTA_CFG_TX_ENABLE)

/*******************************************************************************************************************//**
 * TXI interrupt processing for UART mode. TXI interrupt fires when:
 * - The data in the data register has been transferred to the data shift register, and the next data can be
 * written (ISSMAn = 1). This interrupt writes the next data. After the last data byte is written, set ISSMAn = 0.
 * - After the last byte is transmitted on the TX pin (ISSMAn = 0). The user callback function is called with
 * the UART_EVENT_TX_COMPLETE event code (if it is registered in R_UARTA_Open()).
 **********************************************************************************************************************/
void uarta_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

 #if (BSP_FEATURE_ICU_HAS_IELSR)

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);
 #endif

    /* Recover ISR context saved in open. */
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (0U < p_ctrl->tx_src_bytes)
    {
 #if UARTA_CFG_DTC_SUPPORT_ENABLE
        if (NULL == p_ctrl->p_cfg->p_transfer_tx)
 #endif
        {
            /* Write 1byte (uint8_t) data to (uint8_t) data register */
            p_ctrl->p_reg->TXBAn = *(p_ctrl->p_tx_src);

            /* Update pointer to the next data and number of remaining bytes in the control block. */
            p_ctrl->tx_src_bytes -= 1U;
            p_ctrl->p_tx_src     += 1U;
        }

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
        else
        {
            p_ctrl->tx_src_bytes = 0;
        }
 #endif
    }
    else if (0U != (p_ctrl->p_reg->ASIMAn0 & R_UARTA0_ASIMAn0_ISSMA_Msk))
    {
        p_ctrl->p_reg->ASIMAn0_b.ISSMA = 0U;
    }
    else if (0 == p_ctrl->tx_src_bytes)
    {
        r_uarta_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
    }
    else
    {
        /* Do nothing */
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif

#if (UARTA_CFG_RX_ENABLE)

/*******************************************************************************************************************//**
 * RXI interrupt processing for UART mode. RXI interrupt happens when data arrives to the data register or the
 * register.  This function calls callback function when it meets conditions below.
 *  - UART_EVENT_RX_COMPLETE: The number of data which has been read reaches to the number specified in R_UARTA_Read()
 *    if a transfer instance is used for reception.
 *  - UART_EVENT_RX_CHAR: Data is received asynchronously (read has not been called)
 *
 * @retval    none
 **********************************************************************************************************************/
void uarta_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

 #if (BSP_FEATURE_ICU_HAS_IELSR)

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);
 #endif

    /* Recover ISR context saved in open. */
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    if ((p_ctrl->p_cfg->p_transfer_rx == NULL) || (0 == p_ctrl->rx_dest_bytes))
 #endif
    {
        uint8_t data = p_ctrl->p_reg->RXBAn;
 #if (UARTA_CFG_RECEIVE_ERROR_INTERRUPT_MODE != 0)

        /* Determine cause of error. */
        uint8_t err_type = p_ctrl->p_reg->ASISAn;

        /* Clear error condition. */
        p_ctrl->p_reg->ASCTAn = UARTA_ASISA_RCVR_ERR_MASK;

        err_type &= (uint8_t) UARTA_ASISA_RCVR_ERR_MASK;
        err_type  = uarta_event_lut[err_type];
        if (err_type)
        {
            r_uarta_call_callback(p_ctrl, data, (uart_event_t) err_type);
        }
        else
 #endif
        {
            if (0 == p_ctrl->rx_dest_bytes)
            {
                /* Call user callback with the data. */
                r_uarta_call_callback(p_ctrl, (uint32_t) data, UART_EVENT_RX_CHAR);
            }
            else
            {
                *(p_ctrl->p_rx_dest)   = data;
                p_ctrl->p_rx_dest     += 1;
                p_ctrl->rx_dest_bytes -= 1;

                if (0 == p_ctrl->rx_dest_bytes)
                {
                    r_uarta_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
                }
            }
        }
    }

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    else
    {
        p_ctrl->rx_dest_bytes = 0;
        r_uarta_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
    }
 #endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * ERI interrupt processing for UARTA mode. When an ERI interrupt fires, the user callback function is called if it is
 * registered in R_UARTA_Open() with the event code that triggered the interrupt.
 **********************************************************************************************************************/
void uarta_eri_isr (void)
{
 #if (UARTA_CFG_RECEIVE_ERROR_INTERRUPT_MODE == 0)

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint8_t data = p_ctrl->p_reg->RXBAn;

    uint8_t err_type = p_ctrl->p_reg->ASISAn;

    /* Clear error condition. */
    p_ctrl->p_reg->ASCTAn = UARTA_ASISA_RCVR_ERR_MASK;

    err_type &= (uint8_t) UARTA_ASISA_RCVR_ERR_MASK;
    err_type  = uarta_event_lut[err_type];
    r_uarta_call_callback(p_ctrl, data, (uart_event_t) err_type);

  #if (BSP_FEATURE_ICU_HAS_IELSR)

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);
  #endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
 #endif
}

#endif
