/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sau_uart.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef SAU_UART_CFG_RX_ENABLE
 #define SAU_UART_CFG_RX_ENABLE    1
#endif
#ifndef SAU_UART_CFG_TX_ENABLE
 #define SAU_UART_CFG_TX_ENABLE    1
#endif

#define SAU0_SPS_REG_INIT          ((BSP_CFG_SAU_CK01_DIV << R_SAU0_SPS_PRS1_Pos) | BSP_CFG_SAU_CK00_DIV)
#define SAU1_SPS_REG_INIT          ((BSP_CFG_SAU_CK11_DIV << R_SAU0_SPS_PRS1_Pos) | BSP_CFG_SAU_CK10_DIV)

#if SAU_UART_CFG_SINGLE_CHANNEL > 2
 #define SAU_DEFINE_LOCALS(p_ctrl)     /* Not used. All compile time macros instead. */
 #define SAU_REG                   (R_SAU1)
 #define SAU_UNIT                  (1)
 #define SAU_TX_INDEX              ((SAU_UART_CFG_SINGLE_CHANNEL - 3) << 1)
 #define SAU_RX_INDEX              (SAU_TX_INDEX + 1)
 #define SAU_SPS_REG_INIT          (SAU1_SPS_REG_INIT)
#elif SAU_UART_CFG_SINGLE_CHANNEL > 0
 #define SAU_DEFINE_LOCALS(p_ctrl)     /* Not used. All compile time macros instead. */
 #define SAU_REG                   (R_SAU0)
 #define SAU_UNIT                  (0)
 #define SAU_TX_INDEX              ((SAU_UART_CFG_SINGLE_CHANNEL - 1) << 1)
 #define SAU_RX_INDEX              (SAU_TX_INDEX + 1)
 #define SAU_SPS_REG_INIT          (SAU0_SPS_REG_INIT)
#else
 #define SAU_DEFINE_LOCALS(p_ctrl)    R_SAU0_Type * const _p_reg = (p_ctrl)->p_reg;     \
    const uint8_t _sau_unit     = (p_ctrl)->sau_unit;                                   \
    const uint8_t _sau_tx_index = (p_ctrl)->sau_tx_channel;                             \
    const uint8_t _sau_rx_index = (p_ctrl)->sau_tx_channel + 1;                         \
    /* These locals will not always be used. Void cast to quiet unused variable warn */ \
    (void) _p_reg; (void) _sau_unit; (void) _sau_tx_index; (void) _sau_rx_index
 #define SAU_REG                   (_p_reg)
 #define SAU_UNIT                  (_sau_unit)
 #define SAU_TX_INDEX              (_sau_tx_index)
 #define SAU_RX_INDEX              (_sau_rx_index)
 #define SAU_SPS_REG_INIT          (SAU_UNIT ? SAU1_SPS_REG_INIT : SAU0_SPS_REG_INIT)
#endif

#if SAU_UART_CFG_CRITICAL_SECTION_ENABLE
 #define SAU_CRITICAL_SECTION_ENTER()    {FSP_CRITICAL_SECTION_DEFINE; FSP_CRITICAL_SECTION_ENTER
 #define SAU_CRITICAL_SECTION_EXIT()     FSP_CRITICAL_SECTION_EXIT;}
#else
 #define SAU_CRITICAL_SECTION_ENTER()
 #define SAU_CRITICAL_SECTION_EXIT()
#endif

#define SAU_UART_DTC_RX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |                \
                                              (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |                \
                                              (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_SRC_ADDR_BITS) |        \
                                              (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |                     \
                                              (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS) | \
                                              (TRANSFER_REPEAT_AREA_DESTINATION << TRANSFER_SETTINGS_REPEAT_AREA_BITS))
#define SAU_UART_DTC_TX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << TRANSFER_SETTINGS_MODE_BITS) |               \
                                              (TRANSFER_SIZE_1_BYTE << TRANSFER_SETTINGS_SIZE_BITS) |               \
                                              (TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                              (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) |                    \
                                              (TRANSFER_ADDR_MODE_FIXED << TRANSFER_SETTINGS_DEST_ADDR_BITS) |      \
                                              (TRANSFER_REPEAT_AREA_SOURCE << TRANSFER_SETTINGS_REPEAT_AREA_BITS))

/* Mask of invalid data bits in 9-bit mode. */
#define SAU_UART_ALIGN_2_BYTES               (0x1U)

/* No limit to the number of bytes to read or write if DTC is not used. */
#define SAU_UART_MAX_READ_WRITE_NO_DTC       (0xFFFFFFFFU)
#define SAU_UART_DTC_MAX_TRANSFER            (0x10000U)

/* "SAUU" in ASCII.  Used to determine if the control block is open. */
#define SAU_UART_OPEN                        (0x53415555U)
#define SAU_UART_SCR_TRXE_TRANSMISSION       (2U << R_SAU0_SCR_TRXE_Pos)
#define SAU_UART_SCR_TRXE_RECEPTION          (1U << R_SAU0_SCR_TRXE_Pos)
#define SAU_UART_SMR_STS_TRIGGER_SOFTWARE    (0U << R_SAU0_SMR_STS_Pos)
#define SAU_UART_SMR_STS_TRIGGER_RXD         (1U << R_SAU0_SMR_STS_Pos)
#define SAU_UART_SMR_MD1_UART_MODE           (1U << R_SAU0_SMR_MD1_Pos)
#define SAU_UART_SMR_MD0_BUFFER_EMPTY        (1U << R_SAU0_SMR_MD0_Pos)
#define SAU_UART_SCR_SLC_STOP_BIT1           (1U << R_SAU0_SCR_SLC_Pos)
#define SAU_UART_SIR_FRAME_ERROR_CLEAR       (1U << R_SAU0_SIR_FECT_Pos)
#define SAU_UART_SIR_PARITY_ERROR_CLEAR      (1U << R_SAU0_SIR_PECT_Pos)
#define SAU_UART_SIR_OVERRUN_ERROR_CLEAR     (1U << R_SAU0_SIR_OVCT_Pos)
#define SAU_UART_SSR_OVF_OVERRUN             (1U << R_SAU0_SSR_OVF_Pos)
#define SAU_UART_SSR_PEF_PARITY              (1U << R_SAU0_SSR_PEF_Pos)
#define SAU_UART_SSR_FEF_FRAME               (1U << R_SAU0_SSR_FEF_Pos)
#define SAU_UART_SOE_OUTPUT_ENABLE           (1U << R_SAU0_SOE_SOE_Pos)
#define SAU_UART_SS_START_TRG_ON             (1U << R_SAU0_SS_SS_Pos)
#define SAU_UART_ST_START_TRG_ON             (1U << R_SAU0_ST_ST_Pos)
#define SAU_REG_CHANNEL_SIZE                 (R_SAU1_BASE - R_SAU0_BASE)

#define SAU_UART_SMR_DEFAULT_VALUE           (0x0020U)
#define SAU_UART_SCR_DEFAULT_VALUE           (0x0004U)
#define SAU_UART_STCLK_MAX                   (127)
#define SAU_UART_STCLK_MIN                   (2)
#define SAU_UART_PRS_DIVIDER_MAX             (0xFU)

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_sau_read_write_param_check(sau_uart_instance_ctrl_t const * const p_ctrl,
                                              uint8_t const * const                  addr,
                                              uint32_t const                         bytes);

#endif

static void r_sau_uart_config_set(sau_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);

#if (SAU_UART_CFG_RX_ENABLE)
void sau_uart_eri_isr(void);
void sau_uart_rxi_isr(void);

#endif

#if (SAU_UART_CFG_TX_ENABLE)
void sau_uart_txi_isr(void);

#endif

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE
static fsp_err_t r_sau_uart_transfer_disable(transfer_instance_t const * const p_transfer);
static fsp_err_t r_sau_uart_transfer_configure(sau_uart_instance_ctrl_t * const p_ctrl);

#endif

/* UART on SAU HAL API mapping for UART interface */
const uart_api_t g_uart_on_sau =
{
    .open               = R_SAU_UART_Open,
    .close              = R_SAU_UART_Close,
    .write              = R_SAU_UART_Write,
    .read               = R_SAU_UART_Read,
    .infoGet            = R_SAU_UART_InfoGet,
    .baudSet            = R_SAU_UART_BaudSet,
    .communicationAbort = R_SAU_UART_Abort,
    .callbackSet        = R_SAU_UART_CallbackSet,
    .readStop           = R_SAU_UART_ReadStop,
    .receiveSuspend     = R_SAU_UART_ReceiveSuspend,
    .receiveResume      = R_SAU_UART_ReceiveResume,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup SAU_UART
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the UART driver based on the input configurations.  If reception is enabled at compile time, reception is
 * enabled at the end of this function. Implements @ref uart_api_t::open
 *
 * @retval  FSP_SUCCESS                    Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to UART control block or configuration structure is NULL.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT The requested channel does not exist on this MCU.
 * @retval  FSP_ERR_INVALID_ARGUMENT       Flow control is enabled but flow control pin is not defined or selected channel
 *                                         does not support "Hardware CTS and Hardware RTS" flow control.
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::open
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_Open (uart_ctrl_t * const p_api_ctrl, uart_cfg_t const * const p_cfg)
{
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_cfg);

    sau_uart_extended_cfg_t * p_extend_cfg = (sau_uart_extended_cfg_t *) p_cfg->p_extend;

    FSP_ASSERT(p_extend_cfg);
    FSP_ASSERT(p_extend_cfg->p_baudrate);

 #if (SAU_UART_CFG_TX_ENABLE)
    FSP_ERROR_RETURN(p_cfg->txi_irq >= 0, FSP_ERR_INVALID_ARGUMENT);
 #endif

 #if (SAU_UART_CFG_RX_ENABLE)
    FSP_ERROR_RETURN(p_cfg->rxi_irq >= 0, FSP_ERR_INVALID_ARGUMENT);
    if (FSP_INVALID_VECTOR != p_cfg->eri_irq)
    {
        FSP_ERROR_RETURN(p_cfg->eri_irq >= 0, FSP_ERR_INVALID_ARGUMENT);
    }
 #endif

    FSP_ERROR_RETURN(SAU_UART_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

 #if !SAU_UART_CFG_SINGLE_CHANNEL

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_SAU_UART_VALID_CHANNEL_MASK & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #else
    FSP_ERROR_RETURN((SAU_UART_CFG_SINGLE_CHANNEL - 1) == p_cfg->channel, FSP_ERR_INVALID_ARGUMENT);
 #endif
#endif

#if !SAU_UART_CFG_SINGLE_CHANNEL

    /* Don't use the macros here since the macros use defined locals which copy from p_ctrl. */

    /* Each SAU can contain up to two UART channels */
    p_ctrl->sau_unit = p_cfg->channel / 2;

    /* The transmission channel only occupies the even channels of the current SAU unit. */
    p_ctrl->sau_tx_channel = (uint8_t) ((p_cfg->channel & 1) << 1);

    p_ctrl->p_reg = (R_SAU0_Type *) (R_SAU0_BASE + (SAU_REG_CHANNEL_SIZE * p_ctrl->sau_unit));

    SAU_DEFINE_LOCALS(p_ctrl);
#endif

    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback      = p_cfg->p_callback;
    p_ctrl->p_context       = p_cfg->p_context;
    p_ctrl->extra_data_byte = (UART_DATA_BITS_9 == p_cfg->data_bits);

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE

    /* Configure the transfer interface for transmission and reception if provided. */
    fsp_err_t err = r_sau_uart_transfer_configure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Enable the SAU unit */
    R_BSP_MODULE_START(FSP_IP_SAU, SAU_UNIT);

    /* Set the UART configuration settings provided in ::uart_cfg_t and ::sau_uart_extended_cfg_t. */
    r_sau_uart_config_set(p_ctrl, p_cfg);

    p_ctrl->p_src    = NULL;
    p_ctrl->tx_count = 0U;
    p_ctrl->p_dest   = NULL;
    p_ctrl->rx_count = 0U;

#if (SAU_UART_CFG_RX_ENABLE)
    R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->rxi_ipl, p_ctrl);
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->eri_irq)
    {
        R_BSP_IrqCfgEnable(p_cfg->eri_irq, p_cfg->eri_ipl, p_ctrl);
    }
    SAU_REG->SS = (uint16_t) (SAU_UART_SS_START_TRG_ON << SAU_RX_INDEX);
#endif

#if (SAU_UART_CFG_TX_ENABLE)
    R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->txi_ipl, p_ctrl);
    SAU_REG->SS = (uint16_t) (SAU_UART_SS_START_TRG_ON << SAU_TX_INDEX);
#endif

    p_ctrl->open = SAU_UART_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Aborts any in progress transfers. Disables interrupts, receiver, and transmitter.  Closes lower level transfer
 * drivers if used. Removes power. Implements @ref uart_api_t::close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_Close (uart_ctrl_t * const p_api_ctrl)
{
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);

    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    SAU_DEFINE_LOCALS(p_ctrl);

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    /* Stop the appropriate SAU channels.
     * This is kept as an intermediate so the wait can be performed after. */
    uint16_t reg_st = 0;
#if (SAU_UART_CFG_TX_ENABLE)
    reg_st |= (uint16_t) (SAU_UART_ST_START_TRG_ON << SAU_TX_INDEX);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    reg_st |= (uint16_t) (SAU_UART_ST_START_TRG_ON << SAU_RX_INDEX);
#endif

    /* Write stop trigger. */
    SAU_REG->ST = reg_st;

    /* Verify the channels are no longer enabled. */
    FSP_HARDWARE_REGISTER_WAIT((SAU_REG->SE & reg_st), 0U);

    /* Clear the TX/RX configuration. */
#if (SAU_UART_CFG_TX_ENABLE)
    SAU_REG->SCR[SAU_TX_INDEX] = 0U;
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    SAU_REG->SCR[SAU_RX_INDEX] = 0U;
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->eri_irq)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    }
#endif

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE

    /* Close UART instances. */
 #if (SAU_UART_CFG_RX_ENABLE)
    transfer_instance_t const * p_dtc_rx = p_ctrl->p_cfg->p_transfer_rx;
    if (NULL != p_dtc_rx)
    {
        p_dtc_rx->p_api->close(p_dtc_rx->p_ctrl);
    }
 #endif

 #if (SAU_UART_CFG_TX_ENABLE)
    transfer_instance_t const * p_dtc_tx = p_ctrl->p_cfg->p_transfer_tx;
    if (NULL != p_dtc_tx)
    {
        p_dtc_tx->p_api->close(p_dtc_tx->p_ctrl);
    }
 #endif
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures UART related registers based on user configurations. Assumes the channel is stopped.
 *
 * @param[in]     p_ctrl  Pointer to UART control structure
 * @param[in]     p_cfg   Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_sau_uart_config_set (sau_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
#if SAU_UART_CFG_SINGLE_CHANNEL
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif
    sau_uart_extended_cfg_t * p_extend_cfg = (sau_uart_extended_cfg_t *) p_cfg->p_extend;

    SAU_DEFINE_LOCALS(p_ctrl);

#if (0 == SAU_UART_CFG_FIXED_BAUDRATE_ENABLE)
    sau_uart_baudrate_setting_t * p_sau_baud_setting = p_extend_cfg->p_baudrate;

    /* Configure the operation clock divisor based on extended configuration settings */
    uint32_t sps_prs_offset = p_sau_baud_setting->operation_clock * R_SAU0_SPS_PRS1_Pos;
    uint32_t sps_prs_mask   = R_SAU0_SPS_PRS0_Msk << sps_prs_offset;
    SAU_REG->SPS =
        (uint16_t) ((SAU_REG->SPS & (~sps_prs_mask)) |
                    ((uint32_t) p_sau_baud_setting->prs << sps_prs_offset));
#else

    /* Configure the operation clock divisor based on BSP settings */
    SAU_REG->SPS = SAU_SPS_REG_INIT;
#endif

#if (SAU_UART_CFG_TX_ENABLE)

    /* Configure register SMR setting. */
    SAU_REG->SMR[SAU_TX_INDEX] = (uint16_t) (SAU_UART_SMR_DEFAULT_VALUE |
                                             (uint16_t) (p_extend_cfg->p_baudrate->operation_clock <<
                                                         R_SAU0_SMR_CKS_Pos) |
                                             SAU_UART_SMR_STS_TRIGGER_SOFTWARE |
                                             SAU_UART_SMR_MD1_UART_MODE |
                                             SAU_UART_SMR_MD0_BUFFER_EMPTY);

    /* Configure register SCR setting. */
    SAU_REG->SCR[SAU_TX_INDEX] = (uint16_t) ((SAU_UART_SCR_DEFAULT_VALUE |
                                              SAU_UART_SCR_TRXE_TRANSMISSION) |
                                             (uint16_t) (p_cfg->parity << R_SAU0_SCR_PTC_Pos) |
                                             (uint16_t) (p_extend_cfg->sequence << R_SAU0_SCR_DIR_Pos) |
                                             (uint16_t) ((p_cfg->stop_bits + 1) << R_SAU0_SCR_SLC_Pos) |
                                             p_cfg->data_bits);

    /* Set SDR register value. */
    SAU_REG->SDR[SAU_TX_INDEX] = (uint16_t) (p_extend_cfg->p_baudrate->stclk << R_SAU0_SDR_STCLK_Pos);

    const uint16_t tx_mask     = (uint16_t) (1U << SAU_TX_INDEX);
    const uint16_t tx_clr_mask = (uint16_t) ~tx_mask;
#else

    /* Configure register SMR setting (setting for transmit channel in Reception only mode). */
    SAU_REG->SMR[SAU_TX_INDEX] = SAU_UART_SMR_DEFAULT_VALUE |
                                 (uint16_t) (p_extend_cfg->p_baudrate->operation_clock << R_SAU0_SMR_CKS_Pos) |
                                 SAU_UART_SMR_STS_TRIGGER_RXD |
                                 SAU_UART_SMR_MD1_UART_MODE;
#endif

    SAU_CRITICAL_SECTION_ENTER();
#if SAU_UART_CFG_TX_ENABLE

    /* Output levels cannot be changed while output is enabled. Disable, make changes, then re-enable. */
    uint16_t reg_soe = (uint16_t) (SAU_REG->SOE & tx_clr_mask);
    SAU_REG->SOE = reg_soe;

    /* Set the idle output level and signal level for the UART TX pin. */
    uint16_t reg_sol = SAU_REG->SOL;
    uint16_t reg_so  = SAU_REG->SO;

    if (SAU_UART_SIGNAL_LEVEL_INVERTED == p_extend_cfg->signal_level)
    {
        reg_sol |= tx_mask;            // Inverted signal
        reg_so  &= tx_clr_mask;        // Set idle to low
    }
    else
    {
        reg_sol &= tx_clr_mask;        // Normal signal
        reg_so  |= tx_mask;            // Set idle to high
    }

    SAU_REG->SOL = reg_sol;
    SAU_REG->SO  = reg_so;

    /* Configure register SOE setting to enable serial output. */
    SAU_REG->SOE = (uint16_t) (reg_soe | tx_mask);
#endif

#if SAU_UART_CFG_RX_ENABLE

    /* Configure register SNFENn setting.
     * Use a critical section since I2C and SPI need this to be disabled for their channels. */
    R_PORGA->SNFEN |= (uint8_t) (R_PORGA_SNFEN_SNFEN00_Msk << (p_cfg->channel << 1));
#endif
    SAU_CRITICAL_SECTION_EXIT();

#if (SAU_UART_CFG_RX_ENABLE)

    /* Configure register SIR setting. */
    SAU_REG->SIR[SAU_RX_INDEX] = (uint16_t) (SAU_UART_SIR_FRAME_ERROR_CLEAR |
                                             SAU_UART_SIR_PARITY_ERROR_CLEAR |
                                             SAU_UART_SIR_OVERRUN_ERROR_CLEAR);

    /* Configure register SMR setting. */
    SAU_REG->SMR[SAU_RX_INDEX] = (uint16_t) (SAU_UART_SMR_DEFAULT_VALUE |
                                             (uint16_t) (p_extend_cfg->p_baudrate->operation_clock <<
                                                         R_SAU0_SMR_CKS_Pos) |
                                             SAU_UART_SMR_STS_TRIGGER_RXD |
                                             (uint16_t) (p_extend_cfg->signal_level << R_SAU0_SMR_SIS0_Pos) |
                                             SAU_UART_SMR_MD1_UART_MODE);

    /* Configure register SCR setting. */
    SAU_REG->SCR[SAU_RX_INDEX] = (uint16_t) (SAU_UART_SCR_DEFAULT_VALUE |
                                             SAU_UART_SCR_TRXE_RECEPTION |
                                             (BSP_IRQ_DISABLED != p_cfg->eri_ipl ? R_SAU0_SCR_EOC_Msk : 0U) |
                                             (uint16_t) (p_cfg->parity << R_SAU0_SCR_PTC_Pos) |
                                             (uint16_t) (p_extend_cfg->sequence << R_SAU0_SCR_DIR_Pos) |
                                             SAU_UART_SCR_SLC_STOP_BIT1 |
                                             p_cfg->data_bits);

    /* Set SDR register value. */
    SAU_REG->SDR[SAU_RX_INDEX] = (uint16_t) (p_extend_cfg->p_baudrate->stclk << R_SAU0_SDR_STCLK_Pos);
#endif
}

/*******************************************************************************************************************//**
 * Receives user specified number of bytes into destination buffer pointer. Implements @ref uart_api_t::read
 *
 * @retval  FSP_SUCCESS                  Data reception successfully ends.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_INVALID_ARGUMENT     Destination address or data size is not valid for 9-bit mode.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A previous read operation is still in progress.
 * @retval  FSP_ERR_UNSUPPORTED          current operation mode is transmission only.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reset
 *
 * @note If 9-bit data length is specified at R_SAU_UART_Open call, p_dest must be aligned 16-bit boundary.
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_Read (uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
#if (SAU_UART_CFG_RX_ENABLE)
    fsp_err_t err = FSP_SUCCESS;
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;

 #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    err = r_sau_read_write_param_check(p_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->rx_count, FSP_ERR_IN_USE);
 #endif

    SAU_DEFINE_LOCALS(p_ctrl);

    /* Total number of words to read in this transfer.
     * Bytes is total length of the buffer, so for 9-bit it needs to be divided by 2. */
    uint32_t words = bytes >> p_ctrl->extra_data_byte;

    /* Save the destination address and size for use in sr_isr. */
    p_ctrl->p_dest   = p_dest;
    p_ctrl->rx_count = words;

 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    const transfer_instance_t * p_dtc_rx = p_ctrl->p_cfg->p_transfer_rx;

    /* Configure transfer instance to receive the requested number of bytes if transfer is used for reception. */
    if (NULL != p_dtc_rx)
    {
  #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(words <= SAU_UART_DTC_MAX_TRANSFER);
  #endif
        err = p_dtc_rx->p_api->reset(p_dtc_rx->p_ctrl, NULL, (void *) p_dest, (uint16_t) words);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
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
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 *                                       Number of transfers outside the max or min boundary when transfer instance used
 * @retval  FSP_ERR_INVALID_ARGUMENT     Source address or data size is not valid for 9-bit mode.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_IN_USE               A UART transmission is in progress
 * @retval  FSP_ERR_UNSUPPORTED          SAU_UART_CFG_TX_ENABLE is set to 0
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::reset
 *
 * @note If 9-bit data length is specified at R_SAU_UART_Open call, p_src must be aligned on a 16-bit boundary.
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_Write (uart_ctrl_t * const p_api_ctrl, uint8_t const * const p_src, uint32_t const bytes)
{
#if (SAU_UART_CFG_TX_ENABLE)
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;

 #if SAU_UART_CFG_PARAM_CHECKING_ENABLE || SAU_UART_CFG_DTC_SUPPORT_ENABLE
    fsp_err_t err = FSP_SUCCESS;
 #endif

 #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    err = r_sau_read_write_param_check(p_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ERROR_RETURN(0U == p_ctrl->tx_count, FSP_ERR_IN_USE);

    FSP_ERROR_RETURN(p_ctrl->p_cfg, FSP_ERR_INVALID_ARGUMENT);
 #endif

    SAU_DEFINE_LOCALS(p_ctrl);

    /* Total number of words to write in this transfer.
     * Bytes is total length of the buffer, so for 9-bit it needs to be divided by 2.
     * Subtract one to take into account the manual write at the end of this function. */
    const uint32_t words = (bytes >> p_ctrl->extra_data_byte) - 1;

    /* Enable interrupt on buffer empty. */
    SAU_REG->SMR[SAU_TX_INDEX] |= SAU_UART_SMR_MD0_BUFFER_EMPTY;

    p_ctrl->p_src = (uint8_t *) (p_src + p_ctrl->extra_data_byte + 1);

 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    const transfer_instance_t * p_dtc_tx = p_ctrl->p_cfg->p_transfer_tx;

    /* If a transfer instance is used for transmission, reset the transfer instance to transmit the requested data. */
    if ((NULL != p_dtc_tx) && (words > 0))
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

  #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(words <= SAU_UART_DTC_MAX_TRANSFER);
  #endif

        err = p_dtc_tx->p_api->reset(p_dtc_tx->p_ctrl, (void const *) p_ctrl->p_src, NULL, (uint16_t) words);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
    else
 #endif
    {
        /* TX Count is only used for non-DTC transfers. It can be ignored if the DTC is being used. */
        p_ctrl->tx_count = words;
    }

    /* Manually write the first data word.
     * Use p_src instead of p_ctrl->p_src because the latter is already adjusted for the next byte. */
    uint16_t data_word = 0;

    if (p_ctrl->extra_data_byte)
    {
        /* Using 2 data bytes for 9-bit transfers. */
        data_word = *((uint16_t *) p_src);
    }
    else
    {
        data_word = *p_src;
    }

    SAU_REG->SDR[SAU_TX_INDEX] = data_word;

    R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->txi_irq);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(bytes);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Updates the baud rate using the clock selected in Open. p_baud_setting is a pointer to a sau_uart_baudrate_setting_t structure.
 * Implements @ref uart_api_t::baudSet
 *
 * @warning This terminates any in-progress transmission.
 * @warning This function may change the operation clock frequency. Select a unique operation clock for each SAU
 * instance if using this function.
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer p_ctrl is NULL
 * @retval  FSP_ERR_INVALID_ARGUMENT     p_api_ctrl is empty.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 * @retval  FSP_ERR_UNSUPPORTED          Fixed baud rate is enabled
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_BaudSet (uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting)
{
#if SAU_UART_CFG_FIXED_BAUDRATE_ENABLE
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_baud_setting);

    return FSP_ERR_UNSUPPORTED;
#else
    sau_uart_instance_ctrl_t    * p_ctrl             = (sau_uart_instance_ctrl_t *) p_api_ctrl;
    sau_uart_baudrate_setting_t * p_sau_baud_setting = (sau_uart_baudrate_setting_t *) p_baud_setting;

 #if (0 == SAU_UART_CFG_SINGLE_CHANNEL || (0 == SAU_UART_CFG_PARAM_CHECKING_ENABLE))
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

 #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(p_sau_baud_setting, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    SAU_DEFINE_LOCALS(p_ctrl);

    uint16_t reg_ss = 0U;
 #if (SAU_UART_CFG_TX_ENABLE)
    reg_ss |= (uint16_t) (SAU_UART_ST_START_TRG_ON << SAU_TX_INDEX);
 #endif

 #if (SAU_UART_CFG_RX_ENABLE)
    reg_ss |= (uint16_t) (SAU_UART_ST_START_TRG_ON << SAU_RX_INDEX);
 #endif

    /* Request the channels stop and wait for it to apply. */
    SAU_REG->ST = reg_ss;
    FSP_HARDWARE_REGISTER_WAIT((SAU_REG->SE & reg_ss), 0U);

    /* Configure the operation clock divisor */
    uint32_t sps_prs_offset = p_sau_baud_setting->operation_clock * R_SAU0_SPS_PRS1_Pos;
    uint32_t sps_prs_mask   = R_SAU0_SPS_PRS0_Msk << sps_prs_offset;
    SAU_REG->SPS =
        (uint16_t) ((SAU_REG->SPS & (~sps_prs_mask)) |
                    ((uint32_t) p_sau_baud_setting->prs << sps_prs_offset));

    /* Set SDR register value and re-enable. */
    reg_ss = 0U;
 #if (SAU_UART_CFG_RX_ENABLE)
    SAU_REG->SDR[SAU_RX_INDEX] = (uint16_t) (p_sau_baud_setting->stclk << R_SAU0_SDR_STCLK_Pos);
    reg_ss |= (uint16_t) (SAU_UART_SS_START_TRG_ON << SAU_RX_INDEX);
 #endif

 #if (SAU_UART_CFG_TX_ENABLE)
    SAU_REG->SDR[SAU_TX_INDEX] = (uint16_t) (p_sau_baud_setting->stclk << R_SAU0_SDR_STCLK_Pos);
    reg_ss |= (uint16_t) (SAU_UART_SS_START_TRG_ON << SAU_TX_INDEX);
 #endif

    /* Request the channels start and wait for it to apply. */
    SAU_REG->SS = reg_ss;
    FSP_HARDWARE_REGISTER_WAIT((SAU_REG->SE & reg_ss), reg_ss);

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 * Updates the user callback for callback structure.
 * Implements uart_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer p_ctrl is NULL or p_callback_memory is not NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_CallbackSet (uart_ctrl_t * const          p_api_ctrl,
                                  void (                     * p_callback)(uart_callback_args_t *),
                                  void * const                 p_context,
                                  uart_callback_args_t * const p_callback_memory)
{
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(NULL == p_callback_memory);
    FSP_ERROR_RETURN(p_callback, FSP_ERR_ASSERTION);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the driver information, including the maximum number of bytes that can be received or transmitted at a time.
 * Implements @ref uart_api_t::infoGet
 *
 * @retval  FSP_SUCCESS                  Information stored in provided p_info.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_InfoGet (uart_ctrl_t * const p_api_ctrl, uart_info_t * const p_info)
{
#if SAU_UART_CFG_PARAM_CHECKING_ENABLE || SAU_UART_CFG_DTC_SUPPORT_ENABLE
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
#endif

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN(p_ctrl, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_info, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    p_info->read_bytes_max = SAU_UART_MAX_READ_WRITE_NO_DTC;

    /* Store number of bytes that can be read at a time. */
 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_info->read_bytes_max = SAU_UART_DTC_MAX_TRANSFER;
    }
 #endif
#endif

#if (SAU_UART_CFG_TX_ENABLE)
    p_info->write_bytes_max = SAU_UART_MAX_READ_WRITE_NO_DTC;

    /* Store number of bytes that can be written at a time. */
 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_info->write_bytes_max = SAU_UART_DTC_MAX_TRANSFER;
    }
 #endif
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides API to abort ongoing transfer. Transmission is aborted after the current character is transmitted.
 * Reception is still enabled after abort(). Any characters received after abort() and before the transfer
 * is reset in the next call to read(), will arrive via the callback function with event UART_EVENT_RX_CHAR.
 * Implements @ref uart_api_t::communicationAbort
 *
 * @retval  FSP_SUCCESS                  UART transaction aborted successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_Abort (uart_ctrl_t * const p_api_ctrl, uart_dir_t communication_to_abort)
{
#if !(SAU_UART_CFG_TX_ENABLE) && !(SAU_UART_CFG_RX_ENABLE)
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(communication_to_abort);

    return FSP_ERR_UNSUPPORTED;
#else
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_SUCCESS;

 #if (SAU_UART_CFG_TX_ENABLE) || (SAU_UART_CFG_DTC_SUPPORT_ENABLE)
    uart_cfg_t const * const p_cfg = p_ctrl->p_cfg;
 #endif

 #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

 #if (SAU_UART_CFG_TX_ENABLE)
    if (UART_DIR_TX & communication_to_abort)
    {
        R_BSP_IrqDisable(p_cfg->txi_irq);
        p_ctrl->tx_count = 0;

  #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
        err = r_sau_uart_transfer_disable(p_cfg->p_transfer_tx);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
  #endif
    }
 #endif

 #if (SAU_UART_CFG_RX_ENABLE)
    if (UART_DIR_RX & communication_to_abort)
    {
  #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
        err = r_sau_uart_transfer_disable(p_cfg->p_transfer_rx);
  #endif

        p_ctrl->rx_count = 0;
    }
 #endif

    return err;
#endif
}

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE

/**
 * Performs a NULL check and disables a transfer instance.
 * @param[in] p_transfer Transfer instance to disable
 * @return The error code from the disable api or FSP_SUCCESS if p_transfer is NULL.
 */
static fsp_err_t r_sau_uart_transfer_disable (transfer_instance_t const * const p_transfer)
{
    if (NULL == p_transfer)
    {
        return FSP_SUCCESS;
    }

    return p_transfer->p_api->disable(p_transfer->p_ctrl);
}

#endif

/*******************************************************************************************************************//**
 * Provides API to abort ongoing read. Reception is still enabled after abort(). Any characters received after abort()
 * and before the transfer is reset in the next call to read(), will arrive via the callback function with event
 * UART_EVENT_RX_CHAR.
 * Implements @ref uart_api_t::readStop
 *
 * @retval  FSP_SUCCESS                  UART transaction aborted successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to UART control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_UNSUPPORTED          The requested Abort direction is unsupported.
 *
 * @return                       See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                               return codes. This function calls:
 *                                   * @ref transfer_api_t::disable
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_ReadStop (uart_ctrl_t * const p_api_ctrl, uint32_t * remaining_bytes)
{
#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE || SAU_UART_CFG_RX_ENABLE)
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;
#endif

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    *remaining_bytes = p_ctrl->rx_count;
    p_ctrl->rx_count = 0U;
 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    transfer_instance_t const * const p_dtc_rx = p_ctrl->p_cfg->p_transfer_rx;
    if (NULL != p_dtc_rx)
    {
        fsp_err_t err = p_dtc_rx->p_api->disable(p_dtc_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        transfer_properties_t transfer_info;
        err = p_dtc_rx->p_api->infoGet(p_dtc_rx->p_ctrl, &transfer_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        *remaining_bytes = transfer_info.transfer_length_remaining;
    }
 #endif

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(remaining_bytes);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Calculates baud rate register settings (SDR.STCLK) for the specified SAU unit.
 *
 * @param[in]  p_ctrl                    Pointer to the SAU UART control block.
 * @param[in]  baudrate                  Baud rate [bps]. For example, 19200, 57600, 115200, etc.
 * @param[out] p_baud_setting            Baud setting information stored here if successful
 *
 * @retval     FSP_SUCCESS               Baud rate is successfully calculated
 * @retval     FSP_ERR_UNSUPPORTED       Fixed baudrate is being used
 * @retval     FSP_ERR_ASSERTION         Null pointer
 * @retval     FSP_ERR_INVALID_ARGUMENT  Baud rate is not achievable with selected operation clock frequency
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_BaudCalculate (sau_uart_instance_ctrl_t * const    p_ctrl,
                                    uint32_t                            baudrate,
                                    sau_uart_baudrate_setting_t * const p_baud_setting)
{
#if SAU_UART_CFG_FIXED_BAUDRATE_ENABLE
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(baudrate);
    FSP_PARAMETER_NOT_USED(p_baud_setting);

    return FSP_ERR_UNSUPPORTED;
#else
 #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN(p_baud_setting, FSP_ERR_ASSERTION);
    FSP_ERROR_RETURN((0U != baudrate), FSP_ERR_INVALID_ARGUMENT);
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    SAU_DEFINE_LOCALS(p_ctrl);

 #if SAU_UART_CFG_SINGLE_CHANNEL
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    uint32_t peripheral_clock = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK);

    /* Calculate the optimal value of STCLK for the given CKn clock. The divisor with the lowest error
     * is always the smallest divisor that produces valid STCLK settings. Since we search the divisors
     * low to high, the first divisor is the optimal divisor. */
    for (uint8_t prs = 0; prs <= SAU_UART_PRS_DIVIDER_MAX; prs++)
    {
        /* To get the stclk divider calculate the divisor to apply to ICLK. There's a built in div/2. */
        const uint32_t divisor = baudrate << (prs + 1);

        /* Calculate stclk register value: STCLK = (f_mck / (2*bitrate)) - 1 */
        const uint32_t stclk = (peripheral_clock + (divisor >> 1)) / divisor - 1;

        if ((SAU_UART_STCLK_MIN <= stclk) && (stclk <= SAU_UART_STCLK_MAX))
        {
            /* Save the settings that provide the lowest error. */
            p_baud_setting->prs             = prs;
            p_baud_setting->stclk           = (uint8_t) stclk;
            p_baud_setting->operation_clock =
                ((sau_uart_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->p_baudrate->operation_clock;

            return FSP_SUCCESS;
        }
    }

    /* Return an error if no valid STCLK setting was found */
    return FSP_ERR_INVALID_ARGUMENT;
#endif
}

/*******************************************************************************************************************//**
 * Suspend Reception
 *
 * @retval     FSP_ERR_UNSUPPORTED       Functionality not supported by this driver instance
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_ReceiveSuspend (uart_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Resume Reception
 *
 * @retval     FSP_ERR_UNSUPPORTED       Functionality not supported by this driver instance
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_ReceiveResume (uart_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SAU_UART)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Parameter error check function for read/write.
 *
 * @param[in] p_ctrl Pointer to the control block for the channel
 * @param[in] addr   Pointer to the buffer
 * @param[in] bytes  Number of bytes to read or write
 *
 * @retval  FSP_SUCCESS              No parameter error found
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 * @retval  FSP_ERR_ASSERTION        Pointer p_ctrl is NULL
 * @retval  FSP_ERR_INVALID_ARGUMENT Address is not aligned to 2-byte boundary or size is the odd number when the data
 *                                   length is 9-bit
 **********************************************************************************************************************/
static fsp_err_t r_sau_read_write_param_check (sau_uart_instance_ctrl_t const * const p_ctrl,
                                               uint8_t const * const                  addr,
                                               uint32_t const                         bytes)
{
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(addr, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(0U != bytes, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    if (p_ctrl->extra_data_byte)
    {
        /* Do not allow odd buffer address if data length is 9 bits. */
        FSP_ERROR_RETURN((0U == ((uint32_t) addr & SAU_UART_ALIGN_2_BYTES)), FSP_ERR_INVALID_ARGUMENT);

        /* Do not allow odd number of data bytes if data length is 9 bits. */
        FSP_ERROR_RETURN(0U == (bytes & 1U), FSP_ERR_INVALID_ARGUMENT);
    }

    return FSP_SUCCESS;
}

#endif

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Subroutine to apply common UART transfer settings.
 *
 * @param[in]  p_ctrl             Pointer to instance control block.
 *
 * @retval     FSP_SUCCESS        UART transfer drivers successfully configured
 * @retval     FSP_ERR_ASSERTION  Invalid pointer
 **********************************************************************************************************************/
static fsp_err_t r_sau_uart_transfer_configure (sau_uart_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t         err    = FSP_SUCCESS;
    transfer_info_t * p_info = NULL;

    SAU_DEFINE_LOCALS(p_ctrl);

 #if (SAU_UART_CFG_RX_ENABLE)
    transfer_instance_t const * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;

    /* If a transfer instance is used for reception, apply UART specific settings and open the transfer instance. */
    if (NULL != p_transfer_rx)
    {
        /* Configure the transfer instance, if enabled. */
  #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
        FSP_ASSERT(NULL != p_transfer_rx->p_api);
        FSP_ASSERT(NULL != p_transfer_rx->p_ctrl);
        FSP_ASSERT(NULL != p_transfer_rx->p_cfg);
        FSP_ASSERT(NULL != p_transfer_rx->p_cfg->p_info);
        FSP_ASSERT(NULL != p_transfer_rx->p_cfg->p_extend);
  #endif

        p_info = p_transfer_rx->p_cfg->p_info;

        p_info->transfer_settings_word        = SAU_UART_DTC_RX_TRANSFER_SETTINGS;
        p_info->transfer_settings_word_b.size = (transfer_size_t) p_ctrl->extra_data_byte;
        p_info->p_src = (void *) &(SAU_REG->SDR[SAU_RX_INDEX]);

        err = p_transfer_rx->p_api->open(p_transfer_rx->p_ctrl, p_transfer_rx->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

 #if (SAU_UART_CFG_TX_ENABLE)
    transfer_instance_t const * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    /* If a transfer instance is used for transmission, apply UART specific settings and open the transfer instance. */
    if (NULL != p_transfer_tx)
    {
        /* Configure the transfer instance, if enabled. */
  #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
        FSP_ASSERT(NULL != p_transfer_tx->p_api);
        FSP_ASSERT(NULL != p_transfer_tx->p_ctrl);
        FSP_ASSERT(NULL != p_transfer_tx->p_cfg);
        FSP_ASSERT(NULL != p_transfer_tx->p_cfg->p_info);
        FSP_ASSERT(NULL != p_transfer_tx->p_cfg->p_extend);
  #endif

        p_info = p_transfer_tx->p_cfg->p_info;

        p_info->transfer_settings_word        = SAU_UART_DTC_TX_TRANSFER_SETTINGS;
        p_info->transfer_settings_word_b.size = (transfer_size_t) p_ctrl->extra_data_byte;
        p_info->p_dest = (void *) &(SAU_REG->SDR[SAU_TX_INDEX]);

        err = p_transfer_tx->p_api->open(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg);

  #if (SAU_UART_CFG_RX_ENABLE)
        if ((err != FSP_SUCCESS) && (NULL != p_transfer_rx))
        {
            p_transfer_rx->p_api->close(p_transfer_rx->p_ctrl);
        }
  #endif
    }
 #endif

    return err;
}

#endif

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to UART instance control block
 * @param[in]     data       See uart_callback_args_t in r_uart_api.h
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sau_uart_call_callback (sau_uart_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event)
{
    if (NULL == p_ctrl->p_callback)
    {
        return;
    }

    uart_callback_args_t args;

    args.channel   = p_ctrl->p_cfg->channel;
    args.data      = data;
    args.event     = event;
    args.p_context = p_ctrl->p_context;

    p_ctrl->p_callback(&args);
}

#if (SAU_UART_CFG_TX_ENABLE)

/*******************************************************************************************************************//**
 * INTSTn interrupt processing for UART mode. This function is UART0 write interrupt service routine
 **********************************************************************************************************************/
void sau_uart_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    SAU_DEFINE_LOCALS(p_ctrl);

    uint16_t reg_smr = SAU_REG->SMR[SAU_TX_INDEX];

    if ((p_ctrl->tx_count) && (NULL == p_ctrl->p_cfg->p_transfer_rx))
    {
        uint16_t reg_sdr = 0U;

        if (0U != p_ctrl->extra_data_byte)
        {
            reg_sdr = *((uint16_t *) p_ctrl->p_src);
        }
        else
        {
            reg_sdr = *p_ctrl->p_src;
        }

        SAU_REG->SDR[SAU_TX_INDEX] = reg_sdr;
        p_ctrl->p_src             += 1 + p_ctrl->extra_data_byte;

        p_ctrl->tx_count--;

        if (!p_ctrl->tx_count)
        {
            /* Change the TX interrupt to end of transfer instead so the complete callback happens at the right time. */
            reg_smr &= (uint16_t) ~SAU_UART_SMR_MD0_BUFFER_EMPTY;
        }
    }
    else
    {
        /* Could be the end of a DTC transfer so reset all the TX intermediates. */
        p_ctrl->p_src = NULL;
        if (reg_smr & R_SAU0_SMR_MD0_Msk)
        {
            /* Change the TX interrupt to end of transfer instead so the complete callback happens at the right time. */
            reg_smr &= (uint16_t) ~SAU_UART_SMR_MD0_BUFFER_EMPTY;
        }
        else if (!SAU_REG->SSR[SAU_TX_INDEX])
        {
            /* Only send TX COMPLETE if the SAU channel has returned to idle. */
            r_sau_uart_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
        }
        else
        {
            /* Do nothing. The second to last word has finished transmitting. Keep waiting for the last one.*/
        }
    }

    /* Commit any changes to the SMR. */
    SAU_REG->SMR[SAU_TX_INDEX] = reg_smr;

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif

#if (SAU_UART_CFG_RX_ENABLE)

/*******************************************************************************************************************//**
 * INTSRn interrupt processing for UART mode. This function is UART0 receive interrupt service routine
 **********************************************************************************************************************/
void sau_uart_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    SAU_DEFINE_LOCALS(p_ctrl);

    const uint16_t data = SAU_REG->SDR[SAU_RX_INDEX];

    if (!p_ctrl->rx_count)
    {
        /* This is the case where an abort or readStop was called.
         * Notify the application of the received data using a callback. */
        p_ctrl->p_dest = NULL;
        r_sau_uart_call_callback(p_ctrl, data, UART_EVENT_RX_CHAR);
    }
    else
    {
 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
        if (NULL != p_ctrl->p_cfg->p_transfer_rx)
        {
            p_ctrl->p_dest   = NULL;
            p_ctrl->rx_count = 0;
            r_sau_uart_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
        }
        else
 #endif
        {
            if (p_ctrl->extra_data_byte)
            {
                *((uint16_t *) p_ctrl->p_dest) = data;
                p_ctrl->p_dest                += 2;
            }
            else
            {
                *p_ctrl->p_dest = (uint8_t) data;
                p_ctrl->p_dest += 1;
            }

            p_ctrl->rx_count--;

            if (!p_ctrl->rx_count)
            {
                p_ctrl->p_dest = NULL;
                r_sau_uart_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
            }
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * INTSREn interrupt processing for UART mode. This function is UART0 receive error interrupt service routine
 **********************************************************************************************************************/
void sau_uart_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    SAU_DEFINE_LOCALS(p_ctrl);

    /* The data buffer must be read as part of clearing the error to avoid an overrun error after recovery. */
    const uint16_t data    = SAU_REG->SDR[SAU_RX_INDEX];
    const uint16_t ssr_reg = SAU_REG->SSR[SAU_RX_INDEX];
    uart_event_t   event   = (uart_event_t) 0U;
    uint16_t       flag    = 0U;

    if (SAU_UART_SSR_OVF_OVERRUN & ssr_reg)
    {
        flag  = SAU_UART_SSR_OVF_OVERRUN;
        event = UART_EVENT_ERR_OVERFLOW;
    }
    else if (SAU_UART_SSR_PEF_PARITY & ssr_reg)
    {
        flag  = SAU_UART_SSR_PEF_PARITY;
        event = UART_EVENT_ERR_PARITY;
    }
    else if (SAU_UART_SSR_FEF_FRAME & ssr_reg)
    {
        flag  = SAU_UART_SSR_FEF_FRAME;
        event = UART_EVENT_ERR_FRAMING;
    }
    else
    {
        // Do nothing. Undefined error type.
    }

    if (event)
    {
        SAU_REG->SIR[SAU_RX_INDEX] = flag;
        r_sau_uart_call_callback(p_ctrl, data, event);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif
