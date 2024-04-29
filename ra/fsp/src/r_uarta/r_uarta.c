/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

/* UARTA ASISA register receiver error bit masks */
#define UARTA_ASISA_RCVR_ERR_MASK          (R_UARTA_ASISA0_PEA_Msk | R_UARTA_ASISA0_FEA_Msk | R_UARTA_ASISA0_OVEA_Msk)

/* UARTA parity bit mapping */
#define UARTA_PARITY_OFF_MAPPING           (0U)
#define UARTA_PARITY_ZERO_MAPPING          (1U)
#define UARTA_PARITY_ODD_MAPPING           (2U)
#define UARTA_PARITY_EVEN_MAPPING          (3U)

/* No limit to the number of bytes to read or write if DTC is not used. */
#define UARTA_MAX_READ_WRITE_NO_DTC        (0xFFFFFFFFU)

/* Number of clock select and divider */
#define UARTA_UATCK_UATSEL_COUNT           (4U)

/* Mask for valid mapping of uart_clock_div_t to UTA0CK.CK */
#define UARTA_CLOCK_DIV_MASK               (0x07U)

/* Maximum and minimum BRGCA*/
#define UARTA_BRGCA_MAX                    (255)
#define UARTA_BRGCA_MIN                    (2)

/* Maximum DTC transfer value is 65536 */
#define UARTA_DTC_MAX_TRANSFER             (0x10000U)

/* Delay cycles */
#define UARTA_DELAY_2_CYCLE_UATCK          (2U)
#define UARTA_DELAY_1_CYCLE_UATCK          (1U)

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

#define UARTA_CONVERT_TO_MICRO_SECOND      (1000000U)
#define UARTA_MAX_BAUD_RATE_ERROR_10PPM    (4740U)

/* Scaling factor for baud rate error values, 10ppm or .001% */
#define UARTA_BAUD_ERROR_SCALING_10PPM     (100000)

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
 #define UARTA_MAX_BAUD_RATE               (153600)
#endif

#define UARTA_ERR_OVERFLOW_SHIFT_VALUE     (5)
#define UARTA_ERR_FRAMING_SHIFT_VALUE      (4)
#define UARTA_ERR_PARITY_SHIFT_VALUE       (3)

/***********************************************************************************************************************
 * Private constants
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_uarta_read_write_param_check(uarta_instance_ctrl_t const * const p_ctrl,
                                                uint8_t const * const               addr,
                                                uint32_t const                      bytes);

#endif

#if UARTA_CFG_DTC_SUPPORT_ENABLE
static fsp_err_t r_uarta_transfer_configure(uarta_instance_ctrl_t * const p_ctrl);

#endif

static fsp_err_t r_uarta_baud_validate(uint32_t   baudrate,
                                       uint32_t   f_uta,
                                       uint32_t   baud_divider,
                                       uint32_t   max_error_10ppm,
                                       uint32_t * p_error_10ppm);

static void r_uarta_baud_set(R_UARTA_Type * p_uarta_reg, uarta_baud_setting_t const * const p_baud_setting);

static void r_uarta_call_callback(uarta_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event);

static void r_uarta_wait_time(uarta_instance_ctrl_t * const p_ctrl, uint32_t delay_cyles);

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
    [UART_PARITY_OFF]  = UARTA_PARITY_OFF_MAPPING,
    [UART_PARITY_ZERO] = UARTA_PARITY_ZERO_MAPPING,
    [UART_PARITY_EVEN] = UARTA_PARITY_EVEN_MAPPING,
    [UART_PARITY_ODD]  = UARTA_PARITY_ODD_MAPPING
};

/** Look-up table for converting UARTA clock source, used to get the clock value from R_BSP_SourceClockHzGet */
static fsp_priv_source_clock_t uarta_f_uta0_sel_lut[] =
{
    [UARTA_CLOCK_SOURCE_SOSC_LOCO] = FSP_PRIV_CLOCK_LOCO,
    [UARTA_CLOCK_SOURCE_MOSC]      = FSP_PRIV_CLOCK_MAIN_OSC,
    [UARTA_CLOCK_SOURCE_HOCO]      = FSP_PRIV_CLOCK_HOCO,
    [UARTA_CLOCK_SOURCE_MOCO]      = FSP_PRIV_CLOCK_MOCO
};

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
    FSP_ERROR_RETURN(0U == p_cfg->channel, FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);

    /* UARTA0_ERRI interrupt request should be greater than 0 when Receive Error Interrupt Mode is disabled */
    if (UARTA_RXI_MODE_ERROR_TRIGGER_ERI == (uarta_extended_cfg_t *) p_cfg->p_extend)
    {
        FSP_ASSERT(p_cfg->eri_irq >= 0);
    }
#endif

    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

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
    r_uarta_baud_set(R_UARTA, p_extend->p_baud_setting);

    uint8_t asima1 = 0;

    /* Setting parity, length, stop, direction, and level bit */
    asima1 = (uint8_t) ((uarta_parity_lut[p_cfg->parity] << R_UARTA_ASIMA01_PS_Pos) |
                        ((uint8_t) (p_cfg->data_bits << R_UARTA_ASIMA01_CL_Pos)) |
                        ((uint8_t) (p_cfg->stop_bits << R_UARTA_ASIMA01_SL_Pos)) |
                        ((uint8_t) (p_extend->transfer_dir << R_UARTA_ASIMA01_DIR_Pos)) |
                        ((uint8_t) (p_extend->transfer_level << R_UARTA_ASIMA01_ALV_Pos)));

    uint8_t asima0 = 0;

    /* Setting interrupt for continuous transmission and receive interrupt mode select */
    asima0 |= (uint8_t) ((R_UARTA_ASIMA00_ISSMA_Msk) |
                         ((uint8_t) (p_extend->rxi_mode << R_UARTA_ASIMA00_ISRMA_Pos)));

    /* Configure for register ASIMA1 and ASIMA0 */
    R_UARTA->ASIMA01 = asima1;
    R_UARTA->ASIMA00 = asima0;

    p_ctrl->p_tx_src      = NULL;
    p_ctrl->tx_src_bytes  = 0U;
    p_ctrl->p_rx_dest     = NULL;
    p_ctrl->rx_dest_bytes = 0U;

    /* Enables the UARTA operation clock */
    asima0          |= R_UARTA_ASIMA00_EN_Msk;
    R_UARTA->ASIMA00 = asima0;

#if (UARTA_CFG_RX_ENABLE)

    /* If reception is enabled at build time, enable reception. */
    asima0          |= R_UARTA_ASIMA00_RXEA_Msk;
    R_UARTA->ASIMA00 = asima0;

    /* ERI is optional. */
    if (0 <= p_cfg->eri_irq)
    {
        R_BSP_IrqCfgEnable(p_cfg->eri_irq, p_cfg->eri_ipl, p_ctrl);
    }
    R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->rxi_ipl, p_ctrl);
#endif

#if (UARTA_CFG_TX_ENABLE)

    /* If transmission is enabled at build time, enable transmission. */
    asima0          |= R_UARTA_ASIMA00_TXEA_Msk;
    R_UARTA->ASIMA00 = asima0;

    /* Wait for the period of at least one cycle of the UARTA operation clock according to "Note" section 22.2.3
     * "ASIMA00 : Operation Mode Setting Register 00" in the RA0E1 manual r01uh1040ej0060-ra0e1.pdf .*/
    r_uarta_wait_time(p_ctrl, UARTA_DELAY_1_CYCLE_UATCK);

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

    /* Mark UARTA not open so it can be used again. */
    p_ctrl->open = 0;

    /* Disable receiver, and transmitter. */
    uint8_t current_value = R_UARTA->ASIMA00;

    /* Do read-modify-write for TXEA/RXEA */
    current_value &= (uint8_t) ~(R_UARTA_ASIMA00_TXEA_Msk | R_UARTA_ASIMA00_RXEA_Msk);

    R_UARTA->ASIMA00 = current_value;

    /* Disable baud clock output. Must be done separately after disabling TX/RX. */
    R_UARTA->ASIMA00 = (uint8_t) (current_value & ~R_UARTA_ASIMA00_EN_Msk);

#if (UARTA_CFG_RX_ENABLE)

    /* If reception is enabled at build time, disable reception irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);

    /* ERI is optional. */
    if (0 <= p_ctrl->p_cfg->eri_irq)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    }
#endif
#if (UARTA_CFG_TX_ENABLE)

    /* If transmission is enabled at build time, disable transmission irqs. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
#endif

#if UARTA_CFG_DTC_SUPPORT_ENABLE
 #if (UARTA_CFG_RX_ENABLE)
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }
 #endif
 #if (UARTA_CFG_TX_ENABLE)
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
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

    /* Configure transfer instance to receive the requested number of bytes if transfer is used for reception. */
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        uint32_t size = bytes;
  #if (UARTA_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 65536 limit. */
        FSP_ASSERT(size <= UARTA_DTC_MAX_TRANSFER);
  #endif
        err =
            p_ctrl->p_cfg->p_transfer_rx->p_api->reset(p_ctrl->p_cfg->p_transfer_rx->p_ctrl, NULL, (void *) p_dest,
                                                       (uint16_t) size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        p_ctrl->p_rx_dest     = NULL;
        p_ctrl->rx_dest_bytes = bytes;
    }
    else
    {
        /* Data can be received when DTC support is enabled but the transfer instances are null.*/
        p_ctrl->p_rx_dest     = p_dest;
        p_ctrl->rx_dest_bytes = bytes;
    }

 #else

    /* Save the destination address and size for use in rxi_isr. */
    p_ctrl->p_rx_dest     = p_dest;
    p_ctrl->rx_dest_bytes = bytes;
 #endif

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
    if ((NULL != p_ctrl->p_cfg->p_transfer_tx) && (num_transfers))
    {
  #if (UARTA_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(num_transfers <= UARTA_DTC_MAX_TRANSFER);
  #endif

        err = p_ctrl->p_cfg->p_transfer_tx->p_api->reset(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                         (void const *) p_ctrl->p_tx_src,
                                                         NULL,
                                                         (uint16_t) num_transfers);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    p_ctrl->tx_src_bytes     = num_transfers;
    R_UARTA->ASIMA00_b.ISSMA = 1;

    /* Enable transmit interrupt */
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);

    /* Assign to first byte */
    R_UARTA->TXBA0 = *(p_src);

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
 **********************************************************************************************************************/
fsp_err_t R_UARTA_CallbackSet (uart_ctrl_t * const          p_api_ctrl,
                               void (                     * p_callback)(uart_callback_args_t *),
                               void const * const           p_context,
                               uart_callback_args_t * const p_callback_memory)
{
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_callback_memory);
#if UARTA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

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
#endif

    /* Disable transmit interrupt.  Resuming transmission after reconfiguring baud settings is
     * not supported. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

    uint8_t preserved_asima00 = R_UARTA->ASIMA00;

    /* Modify the BRGCAn bits while the TXEAn and RXEAn bits are 0 (in the transmission/reception stopped state).*/
    R_UARTA->ASIMA00 = (preserved_asima00 & (uint8_t) (~(R_UARTA_ASIMA00_RXEA_Msk | R_UARTA_ASIMA00_TXEA_Msk)));

    p_ctrl->p_tx_src = NULL;

    /* Apply new baud rate register settings. */
    r_uarta_baud_set(R_UARTA, p_baud_setting);

    /* To enable transmission or reception again, set the TXEAn or RXEAn bit to 1 at least two cycles of the UARTAn
     * operation clock after clearing the TXEAn or RXEAn bit to 0 according to "Note" section 22.2.3
     * "ASIMA00 : Operation Mode Setting Register 00" in the RA0E1 manual r01uh1040ej0060-ra0e1.pdf.*/
    r_uarta_wait_time(p_ctrl, UARTA_DELAY_2_CYCLE_UATCK);

    /* Restore all settings. */
    R_UARTA->ASIMA00 = preserved_asima00;
#if (UARTA_CFG_TX_ENABLE)

    /* If transmission is enabled at build time, enable transmission. */
    if (preserved_asima00 & R_UARTA_ASIMA00_TXEA_Msk)
    {
        /* Wait for the period of at least one cycle of the UARTA operation clock according to "Note" section 22.2.3
         * "ASIMA00 : Operation Mode Setting Register 00" in the RA0E1 manual r01uh1040ej0060-ra0e1.pdf .*/
        r_uarta_wait_time(p_ctrl, UARTA_DELAY_1_CYCLE_UATCK);
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
#if UARTA_CFG_PARAM_CHECKING_ENABLE || UARTA_CFG_DTC_SUPPORT_ENABLE
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

#if (UARTA_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_info);
    FSP_ERROR_RETURN(UARTA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint32_t read_bytes_max  = UARTA_MAX_READ_WRITE_NO_DTC;
    uint32_t write_bytes_max = UARTA_MAX_READ_WRITE_NO_DTC;

#if (UARTA_CFG_RX_ENABLE)

    /* Store number of bytes that can be read at a time. */
 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        read_bytes_max = UARTA_DTC_MAX_TRANSFER;
    }
 #endif
#endif

#if (UARTA_CFG_TX_ENABLE)

    /* Store number of bytes that can be written at a time. */
 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        write_bytes_max = UARTA_DTC_MAX_TRANSFER;
    }
 #endif
#endif

    p_info->read_bytes_max  = read_bytes_max;
    p_info->write_bytes_max = write_bytes_max;

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
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_ERR_UNSUPPORTED;

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
        if (NULL != p_ctrl->p_cfg->p_transfer_tx)
        {
            err = p_ctrl->p_cfg->p_transfer_tx->p_api->disable(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
        }
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif
        p_ctrl->tx_src_bytes = 0U;
    }
#endif

#if (UARTA_CFG_RX_ENABLE)
    if (UART_DIR_RX & communication_to_abort)
    {
        err = FSP_SUCCESS;

        p_ctrl->rx_dest_bytes = 0U;

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
        if (NULL != p_ctrl->p_cfg->p_transfer_rx)
        {
            err = p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        }
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif
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
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        fsp_err_t err = p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        transfer_properties_t transfer_info;
        err = p_ctrl->p_cfg->p_transfer_rx->p_api->infoGet(p_ctrl->p_cfg->p_transfer_rx->p_ctrl, &transfer_info);
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
    uint32_t min_error_10ppm = UINT32_MAX;

    uint32_t clock_source_value = R_BSP_SourceClockHzGet(uarta_f_uta0_sel_lut[clock_source]);

    if (UARTA_CLOCK_SOURCE_SOSC_LOCO == clock_source)
    {
        /* Find the appropriate divider for the requested baud rate.
         * k = round(f_UTA0 / (2 * Desired baud rate))
         * Integer round to the nearest divider.
         */
        const uint32_t k = (clock_source_value + baudrate) / (2U * baudrate);

        uint32_t error_10ppm = 0;

        /* Validate the baud rate and get the error. If invalid, skip to the next divider. */
        fsp_err_t err = r_uarta_baud_validate(baudrate,
                                              clock_source_value,
                                              k,
                                              baud_rate_percent_error_x1000,
                                              &error_10ppm);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Save the settings. */
        p_baud_setting->brgca                 = (uint8_t) k;
        p_baud_setting->uta0ck_clock_b.utasel = 0U;
        p_baud_setting->uta0ck_clock_b.uta0ck = UARTA_UTA0CK_SOSC_LOCO_SETTING;

        return FSP_SUCCESS;
    }

    /* Go ahead and set the clock source here. It stays constant through the baud rate search. */
    p_baud_setting->uta0ck_clock_b.utasel = (uint8_t) (clock_source & UARTA_UTA0SEL_MASK);

    for (uarta_clock_div_t f_uta0_div = UARTA_CLOCK_DIV_1; f_uta0_div < UARTA_CLOCK_DIV_COUNT; f_uta0_div++)
    {
        /* Calculate UARTA operation clock (f_UTA0)*/
        const uint32_t f_uta0_value = clock_source_value >> f_uta0_div;

        /* Find the appropriate divider for the requested baud rate.
         * k = round(f_UTA0 / (2 * Desired baud rate))
         * Integer round to the nearest divider.
         */
        const uint32_t k = (f_uta0_value + baudrate) / (2U * baudrate);

        uint32_t error_10ppm = 0;

        /* Validate the baud rate and get the error. If invalid, skip to the next divider. */
        if (FSP_SUCCESS !=
            r_uarta_baud_validate(baudrate, f_uta0_value, k, baud_rate_percent_error_x1000, &error_10ppm))
        {
            continue;
        }

        if (error_10ppm < min_error_10ppm)
        {
            /* Save the current error and update the settings. */
            min_error_10ppm = error_10ppm;

            p_baud_setting->brgca                 = (uint8_t) k;
            p_baud_setting->uta0ck_clock_b.uta0ck = (uint8_t) (f_uta0_div & R_UARTA_UTA0CK_CK_Msk);
        }
    }

    /* If no divider could be found, min_error_10ppm would still be UINT32_MAX. */
    if (min_error_10ppm == UINT32_MAX)
    {
        return FSP_ERR_INVALID_RATE;
    }

    return FSP_SUCCESS;
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
    fsp_err_t         err    = FSP_SUCCESS;
    transfer_info_t * p_info = NULL;
 #if (UARTA_CFG_RX_ENABLE)
    transfer_instance_t const * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;

    /* If a transfer instance is used for reception, apply UART specific settings and open the transfer instance. */
    if (NULL != p_transfer_rx)
    {
        /* Configure the transfer instance, if enabled. */
  #if (UARTA_CFG_PARAM_CHECKING_ENABLE)
        FSP_ASSERT(NULL != p_transfer_rx->p_api);
        FSP_ASSERT(NULL != p_transfer_rx->p_ctrl);
        FSP_ASSERT(NULL != p_transfer_rx->p_cfg);
        FSP_ASSERT(NULL != p_transfer_rx->p_cfg->p_info);
        FSP_ASSERT(NULL != p_transfer_rx->p_cfg->p_extend);
  #endif

        p_info = p_transfer_rx->p_cfg->p_info;

        p_info->transfer_settings_word = UARTA_DTC_RX_TRANSFER_SETTINGS;

        /* Casting for compatibility with 5, 7 or 8 bit mode. */
        p_info->p_src = (void *) &(R_UARTA->RXBA0);

        err = p_transfer_rx->p_api->open(p_transfer_rx->p_ctrl, p_transfer_rx->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif
 #if (UARTA_CFG_TX_ENABLE)
    transfer_instance_t const * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    /* If a transfer instance is used for transmission, apply UART specific settings and open the transfer instance. */
    if (NULL != p_transfer_tx)
    {
        /* Configure the transfer instance, if enabled. */
  #if (UARTA_CFG_PARAM_CHECKING_ENABLE)
        FSP_ASSERT(NULL != p_transfer_tx->p_api);
        FSP_ASSERT(NULL != p_transfer_tx->p_ctrl);
        FSP_ASSERT(NULL != p_transfer_tx->p_cfg);
        FSP_ASSERT(NULL != p_transfer_tx->p_cfg->p_info);
        FSP_ASSERT(NULL != p_transfer_tx->p_cfg->p_extend);
  #endif

        p_info = p_transfer_tx->p_cfg->p_info;

        p_info->transfer_settings_word = UARTA_DTC_TX_TRANSFER_SETTINGS;

        p_info->p_dest = (void *) &(R_UARTA->TXBA0);

        err = p_transfer_tx->p_api->open(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg);

  #if (UARTA_CFG_RX_ENABLE)
        if ((err != FSP_SUCCESS) && (NULL != p_transfer_rx))
        {
            p_transfer_rx->p_api->close(p_transfer_rx->p_ctrl);
        }
  #endif
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    return err;
}

#endif

/*******************************************************************************************************************//**
 * Changes baud rate based on predetermined register settings.
 *
 * @param[in]  p_uarta_reg       Base pointer for UARTA registers
 * @param[in]  p_baud_setting  Pointer to other divisor related settings
 *
 * @note   The transmitter and receiver (TXEA and RXEA bits in ASIMA00) must be disabled prior to calling this function.
 **********************************************************************************************************************/
static void r_uarta_baud_set (R_UARTA_Type * p_uarta_reg, uarta_baud_setting_t const * const p_baud_setting)
{
    /* Set BRGCA register value. */
    p_uarta_reg->BRGCA0 = p_baud_setting->brgca;

    /* Set UTA0CK register value. */
    p_uarta_reg->UTA0CK = p_baud_setting->uta0ck_clock;
}

/*******************************************************************************************************************//**
 * Validates the baud rate divisor for the given f_UTA0 frequency.
 *
 * @param[in]  baudrate         The desired baud rate.
 * @param[in]  f_uta            The operating frequency of the f_UTA0 clock into the baud rate generator.
 * @param[in]  baud_divider     Baud generator divider configured into BRGCA0.
 * @param[in]  max_error_10ppm  Maximum permissible error in 10ppm units (0.001%).
 * @param[out] p_error_10ppm    Calculated baud rate error in 10ppm units given f_uta and baud_divider.
 *
 * @retval FSP_SUCCESS              The values of f_uta and baud_divider provide an acceptable baud rate.
 * @retval FSP_ERR_INVALID_ARGUMENT The value of baud_divider is out of range.
 * @retval FSP_ERR_INVALID_RATE     The baud rate error is outside the allowed range.
 **********************************************************************************************************************/
static fsp_err_t r_uarta_baud_validate (uint32_t   baudrate,
                                        uint32_t   f_uta,
                                        uint32_t   baud_divider,
                                        uint32_t   max_error_10ppm,
                                        uint32_t * p_error_10ppm)
{
    /* If the divider calculated is out of range return an error. */
    if ((baud_divider < UARTA_BRGCA_MIN) || (baud_divider > UARTA_BRGCA_MAX))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    /* Calculate actual baudrate using the divider (k).
     * The formula to calculate actual baudrate is as:
     * Actual baud rate = f_UTA0 / (2 * k)
     */
    const uint32_t actual_baudrate = f_uta / (2U * baud_divider);

    /* Calculate the error between the actual and desired baud rate in 10ppm. */
    int32_t error_10ppm = (UARTA_BAUD_ERROR_SCALING_10PPM * ((int32_t) actual_baudrate - (int32_t) baudrate)) /
                          ((int32_t) baudrate);

    if (error_10ppm < 0)
    {
        error_10ppm = -error_10ppm;
    }

    /* If the error is outside the provided bound return. */
    if (((uint32_t) error_10ppm) > max_error_10ppm)
    {
        return FSP_ERR_INVALID_RATE;
    }

    /* Pass the calculated error back to the caller. */
    *p_error_10ppm = (uint32_t) error_10ppm;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function implements waiting for the period of at least one cycle of the UARTAn operation clock (f_UTA0)
 *
 * @param[in] p_ctrl         Pointer to instance control block.
 * @param[in] delay_cyles    Delay cycles value of the operating clock (f_UTA0).
 **********************************************************************************************************************/
static void r_uarta_wait_time (uarta_instance_ctrl_t * const p_ctrl, uint32_t delay_cyles)
{
    uint8_t uta0ck = ((uarta_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_baud_setting->uta0ck_clock_b.uta0ck;
    uint8_t utasel = ((uarta_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_baud_setting->uta0ck_clock_b.utasel;

    /* Get UARTA clock divider shift.
     * Anything outside UARTA_CLOCK_DIV_MASK is not a valid divider and is probably LOCO/SOSC selection instead.
     */
    uint32_t divider_shift = (uint32_t) (uta0ck & UARTA_CLOCK_DIV_MASK);

    /* Calculate frequency UARTA0 operation clock */
    uint32_t f_uta0         = (R_BSP_SourceClockHzGet(uarta_f_uta0_sel_lut[utasel]) >> divider_shift);
    uint32_t delay_us_cycle = (uint32_t) (UARTA_CONVERT_TO_MICRO_SECOND / f_uta0);

    /* Waiting for the period */
    R_BSP_SoftwareDelay(delay_us_cycle * delay_cyles, BSP_DELAY_UNITS_MICROSECONDS);
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
    uart_callback_args_t args;

    args.channel   = p_ctrl->p_cfg->channel;
    args.data      = data;
    args.event     = event;
    args.p_context = p_ctrl->p_context;

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(&args);
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

    /* Recover ISR context saved in open. */
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (0U < p_ctrl->tx_src_bytes)
    {
        if (NULL == p_ctrl->p_cfg->p_transfer_tx)
        {
            /* Write 1byte (uint8_t) data to (uint8_t) data register */
            R_UARTA->TXBA0 = *(p_ctrl->p_tx_src);

            /* Update pointer to the next data and number of remaining bytes in the control block. */
            p_ctrl->tx_src_bytes -= 1U;
            p_ctrl->p_tx_src     += 1U;
        }
        else
        {
            p_ctrl->tx_src_bytes = 0;
        }
    }
    else if (0U != (R_UARTA->ASIMA00 & R_UARTA_ASIMA00_ISSMA_Msk))
    {
        R_UARTA->ASIMA00_b.ISSMA = 0U;
    }
    else if (0 == p_ctrl->tx_src_bytes)
    {
        p_ctrl->p_tx_src = NULL;

        /* If a callback was provided, call it with the argument */
        if (NULL != p_ctrl->p_callback)
        {
            r_uarta_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
        }
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

    /* Recover ISR context saved in open. */
    uarta_instance_ctrl_t * p_ctrl   = (uarta_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    uarta_extended_cfg_t  * p_extend = (uarta_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    if ((p_ctrl->p_cfg->p_transfer_rx == NULL) || (0 == p_ctrl->rx_dest_bytes))
 #endif
    {
        uint8_t      data;
        uint8_t      err_type = 0;
        uart_event_t event;
        data = R_UARTA->RXBA0;

        if (UARTA_RXI_MODE_ERROR_TRIGGER_RXI == p_extend->rxi_mode)
        {
            /* Determine cause of error. */
            err_type = R_UARTA->ASISA0;
            event    = (uart_event_t) ((((err_type & R_UARTA_ASISA0_OVEA_Msk) != 0) << UARTA_ERR_OVERFLOW_SHIFT_VALUE) |
                                       (((err_type & R_UARTA_ASISA0_FEA_Msk) != 0) << UARTA_ERR_FRAMING_SHIFT_VALUE) |
                                       (((err_type & R_UARTA_ASISA0_PEA_Msk) != 0) << UARTA_ERR_PARITY_SHIFT_VALUE));
        }

        if (0 != err_type)
        {
            /* Clear error condition. */
            R_UARTA->ASCTA0 &= (uint8_t) (~UARTA_ASISA_RCVR_ERR_MASK);
            r_uarta_call_callback(p_ctrl, (uint32_t) data, event);
        }
        else
        {
            if (0 == p_ctrl->rx_dest_bytes)
            {
                /* If a callback was provided, call it with the argument */
                if (NULL != p_ctrl->p_callback)
                {
                    event = UART_EVENT_RX_CHAR;

                    /* Call user callback with the data. */
                    r_uarta_call_callback(p_ctrl, (uint32_t) data, event);
                }
            }
            else
            {
                *(p_ctrl->p_rx_dest)   = data;
                p_ctrl->p_rx_dest     += 1;
                p_ctrl->rx_dest_bytes -= 1;

                if (0 == p_ctrl->rx_dest_bytes)
                {
                    /* If a callback was provided, call it with the argument */
                    if (NULL != p_ctrl->p_callback)
                    {
                        event = UART_EVENT_RX_COMPLETE;
                        r_uarta_call_callback(p_ctrl, 0U, event);
                    }
                }
            }
        }
    }

 #if UARTA_CFG_DTC_SUPPORT_ENABLE
    else
    {
        p_ctrl->rx_dest_bytes = 0;

        /* If a callback was provided, call it with the argument */
        if (NULL != p_ctrl->p_callback)
        {
            /* Call callback */
            r_uarta_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
        }
    }
 #endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif

#if (UARTA_CFG_RX_ENABLE)

/*******************************************************************************************************************//**
 * ERI interrupt processing for UARTA mode. When an ERI interrupt fires, the user callback function is called if it is
 * registered in R_UARTA_Open() with the event code that triggered the interrupt.
 **********************************************************************************************************************/
void uarta_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    uarta_instance_ctrl_t * p_ctrl = (uarta_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint8_t      data = 0U;
    uart_event_t event;

    /* Read data. */
    data = R_UARTA->RXBA0;

    /* Determine cause of error. */
    uint8_t err_type = R_UARTA->ASISA0;
    event = (uart_event_t) ((((err_type & R_UARTA_ASISA0_OVEA_Msk) != 0) << UARTA_ERR_OVERFLOW_SHIFT_VALUE) |
                            (((err_type & R_UARTA_ASISA0_FEA_Msk) != 0) << UARTA_ERR_FRAMING_SHIFT_VALUE) |
                            (((err_type & R_UARTA_ASISA0_PEA_Msk) != 0) << UARTA_ERR_PARITY_SHIFT_VALUE));

    /* Clear error condition. */
    R_UARTA->ASCTA0 &= (uint8_t) (~UARTA_ASISA_RCVR_ERR_MASK);

    /* If a callback was provided, call it with the argument */
    if (NULL != p_ctrl->p_callback)
    {
        /* Call callback. */
        r_uarta_call_callback(p_ctrl, (uint32_t) data, event);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif
