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
#include "bsp_api.h"
#include "r_sau_uart.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef SAU_UART_CFG_RX_ENABLE
 #define SAU_UART_CFG_RX_ENABLE              1
#endif
#ifndef SAU_UART_CFG_TX_ENABLE
 #define SAU_UART_CFG_TX_ENABLE              1
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
#define SAU_UART_SMR_MD_UART_MODE            (1U << R_SAU0_SMR_MD1_Pos)
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
#define SAU_UART_SDR_MASK_HIGH8BIT           (0x00FFU)
#define SAU_UART_SDR_MAX                     (127)
#define SAU_UART_SDR_MIN                     (2)

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_sau_read_write_param_check(sau_uart_instance_ctrl_t const * const p_ctrl,
                                              uint8_t const * const                  addr,
                                              uint32_t const                         bytes);

#endif

static void r_sau_irqs_cfg(sau_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);
static void r_sau_uart_config_set(sau_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg);

#if (SAU_UART_CFG_RX_ENABLE)
void sau_uart_eri_isr(void);
void sau_uart_rxi_isr(void);

#endif

#if (SAU_UART_CFG_TX_ENABLE)
void sau_uart_txi_isr(void);

#endif

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE
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

    /* Make sure this channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_SAU_UART_VALID_CHANNEL_MASK & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

    /* Each SAU can contain up to two UART channels */
    p_ctrl->sau_unit = p_cfg->channel / 2;

    /* The transmission channel only occupies the even channels of the current SAU unit. */
    p_ctrl->sau_tx_channel = (uint8_t) ((p_cfg->channel & 1) << 1);

    p_ctrl->p_reg = (R_SAU0_Type *) (R_SAU0_BASE + (SAU_REG_CHANNEL_SIZE * p_ctrl->sau_unit));

    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback      = p_cfg->p_callback;
    p_ctrl->p_context       = p_cfg->p_context;
    p_ctrl->extra_data_byte = 0;
    if (UART_DATA_BITS_9 == p_cfg->data_bits)
    {
        p_ctrl->extra_data_byte = 1;
    }

    /* Configure the interrupts. */
    r_sau_irqs_cfg(p_ctrl, p_cfg);

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE

    /* Configure the transfer interface for transmission and reception if provided. */
    fsp_err_t err = r_sau_uart_transfer_configure(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Enable the SAU unit and reset the registers to their initial state. */
    R_BSP_MODULE_START(FSP_IP_SAU, p_ctrl->sau_unit);

    /* Set the UART configuration settings provided in ::uart_cfg_t and ::sau_uart_extended_cfg_t. */
    r_sau_uart_config_set(p_ctrl, p_cfg);

    p_ctrl->p_src    = NULL;
    p_ctrl->tx_count = 0U;
    p_ctrl->p_dest   = NULL;
    p_ctrl->rx_count = 0U;

    uint16_t ss = 0;
#if (SAU_UART_CFG_RX_ENABLE)
    R_BSP_IrqEnable(p_cfg->rxi_irq);
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->eri_irq)
    {
        R_BSP_IrqEnable(p_cfg->eri_irq);
    }
    ss = (uint16_t) (SAU_UART_SS_START_TRG_ON << (p_ctrl->sau_tx_channel + 1));
#endif

#if (SAU_UART_CFG_TX_ENABLE)
    R_BSP_IrqEnable(p_cfg->txi_irq);
    ss |= (uint16_t) (SAU_UART_SS_START_TRG_ON << p_ctrl->sau_tx_channel);
#endif

#if SAU_UART_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif
    p_ctrl->p_reg->SS |= ss;
#if SAU_UART_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
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
    uint16_t reg_st = 0;
#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters. */
    FSP_ASSERT(p_ctrl);

    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

#if SAU_UART_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif

#if (SAU_UART_CFG_TX_ENABLE)
    reg_st |= (uint16_t) (SAU_UART_ST_START_TRG_ON << p_ctrl->sau_tx_channel);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    reg_st |= (uint16_t) (SAU_UART_ST_START_TRG_ON << (p_ctrl->sau_tx_channel + 1));
#endif

    /* Stop the appropriate SAU channels. */
    p_ctrl->p_reg->ST |= reg_st;

    /* Verify the channels are no longer enabled. */
    FSP_HARDWARE_REGISTER_WAIT((p_ctrl->p_reg->SE & reg_st), 0U);

    /* Clear the TX/RX configuration. */
#if (SAU_UART_CFG_TX_ENABLE)
    p_ctrl->p_reg->SCR[p_ctrl->sau_tx_channel] = 0U;
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    p_ctrl->p_reg->SCR[p_ctrl->sau_tx_channel + 1] = 0U;
#endif

#if SAU_UART_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif

#if (SAU_UART_CFG_TX_ENABLE)
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->eri_irq)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    }
#endif

#if SAU_UART_CFG_DTC_SUPPORT_ENABLE

    /* Close UART instances. */
 #if (SAU_UART_CFG_RX_ENABLE)
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }
 #endif

 #if (SAU_UART_CFG_TX_ENABLE)
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
 #endif
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  ipl                       Interrupt priority level
 * @param[in]  irq                       IRQ number for this interrupt
 **********************************************************************************************************************/
static void r_sau_irq_cfg (sau_uart_instance_ctrl_t * const p_ctrl, uint8_t const ipl, IRQn_Type const irq)
{
    /* Disable interrupts, set priority, and store control block in the vector information so it can be accessed
     * from the callback. */
    R_BSP_IrqDisable(irq);
    R_BSP_IrqCfg(irq, ipl, p_ctrl);
}

/*******************************************************************************************************************//**
 * Sets interrupt priority and initializes vector info for all interrupts.
 *
 * @param[in]  p_ctrl                    Pointer to UART instance control block
 * @param[in]  p_cfg                     Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_sau_irqs_cfg (sau_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
#if (SAU_UART_CFG_TX_ENABLE)
    r_sau_irq_cfg(p_ctrl, p_cfg->txi_ipl, p_cfg->txi_irq);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    r_sau_irq_cfg(p_ctrl, p_cfg->rxi_ipl, p_cfg->rxi_irq);
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->eri_irq)
    {
        r_sau_irq_cfg(p_ctrl, p_cfg->eri_ipl, p_cfg->eri_irq);
    }
#endif
}

/*******************************************************************************************************************//**
 * Configures UART related registers based on user configurations.
 *
 * @param[in]     p_ctrl  Pointer to UART control structure
 * @param[in]     p_cfg   Pointer to UART specific configuration structure
 **********************************************************************************************************************/
static void r_sau_uart_config_set (sau_uart_instance_ctrl_t * const p_ctrl, uart_cfg_t const * const p_cfg)
{
    sau_uart_extended_cfg_t * p_extend_cfg = (sau_uart_extended_cfg_t *) p_cfg->p_extend;

    uint16_t smr = 0;
    uint16_t scr = 0;
#if (SAU_UART_CFG_TX_ENABLE)
    uint16_t sol = 0;
    uint16_t so  = 0;
#endif

    /* Set SPS register value. */
    if (SAU_UART_OPERATION_CLOCK_CK1 == p_extend_cfg->operation_clock)
    {
        p_ctrl->p_reg->SPS_b.PRS1 = (uint16_t) (p_extend_cfg->p_baudrate->prs & 0x0F);
    }
    else
    {
        p_ctrl->p_reg->SPS_b.PRS0 = (uint16_t) (p_extend_cfg->p_baudrate->prs & 0x0F);
    }

#if (SAU_UART_CFG_TX_ENABLE)

    /* Configure register SMR setting. */
    smr = (uint16_t) (SAU_UART_SMR_DEFAULT_VALUE |
                      (uint16_t) (p_extend_cfg->operation_clock << R_SAU0_SMR_CKS_Pos) |
                      SAU_UART_SMR_STS_TRIGGER_SOFTWARE | SAU_UART_SMR_MD_UART_MODE |
                      (uint16_t) p_extend_cfg->transfer_mode);
    p_ctrl->p_reg->SMR[p_ctrl->sau_tx_channel] = smr;

    /* Configure register SCR setting. */
    scr = (uint16_t) ((SAU_UART_SCR_DEFAULT_VALUE | SAU_UART_SCR_TRXE_TRANSMISSION) |
                      (uint16_t) (p_cfg->parity << R_SAU0_SCR_PTC_Pos) |
                      (uint16_t) (p_extend_cfg->sequence << R_SAU0_SCR_DIR_Pos) |
                      (uint16_t) ((p_cfg->stop_bits + 1) << R_SAU0_SCR_SLC_Pos) |
                      p_cfg->data_bits);
    p_ctrl->p_reg->SCR[p_ctrl->sau_tx_channel] = scr;

    /* Set SDR register value. */
    p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel] = (uint16_t) (p_extend_cfg->p_baudrate->stclk << R_SAU0_SDR_STCLK_Pos);

    /* Set the idle output level and signal level for the UART TX pin. */
    if (SAU_UART_SIGNAL_LEVEL_INVERTED == p_extend_cfg->signal_level)
    {
        sol = (uint16_t) (1U << p_ctrl->sau_tx_channel);
    }
    else
    {
        so = (uint16_t) (1U << p_ctrl->sau_tx_channel);
    }

    p_ctrl->p_reg->SOL = (p_ctrl->p_reg->SOL & ((uint16_t) ~(1U << p_ctrl->sau_tx_channel))) | sol;

 #if SAU_UART_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
 #endif
    p_ctrl->p_reg->SO = (p_ctrl->p_reg->SO & ((uint16_t) ~(1U << p_ctrl->sau_tx_channel))) | so;

    /* Configure register SOE setting, the default value isn't necessary to set for UART1. */
    p_ctrl->p_reg->SOE |= (uint16_t) (SAU_UART_SOE_OUTPUT_ENABLE << p_ctrl->sau_tx_channel);
 #if SAU_UART_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
 #endif
#else

    /* Configure register SMR setting (setting for transmit channel in Reception only mode). */
    smr = SAU_UART_SMR_DEFAULT_VALUE | (uint16_t) (p_extend_cfg->operation_clock << R_SAU0_SMR_CKS_Pos) |
          SAU_UART_SMR_STS_TRIGGER_RXD | SAU_UART_SMR_MD_UART_MODE;
    p_ctrl->p_reg->SMR[p_ctrl->sau_tx_channel] = smr;
#endif

#if (SAU_UART_CFG_RX_ENABLE)

    /* Configure register NFEN0 setting. */
    R_PORGA->SNFEN |= (uint8_t) (1 << (p_cfg->channel * 2));

    /* Configure register SIR setting. */
    p_ctrl->p_reg->SIR[p_ctrl->sau_tx_channel + 1] = (uint16_t) (SAU_UART_SIR_FRAME_ERROR_CLEAR |
                                                                 SAU_UART_SIR_PARITY_ERROR_CLEAR |
                                                                 SAU_UART_SIR_OVERRUN_ERROR_CLEAR);

    /* Configure register SMR setting. */
    smr = (uint16_t) (SAU_UART_SMR_DEFAULT_VALUE |
                      (uint16_t) (p_extend_cfg->operation_clock << R_SAU0_SMR_CKS_Pos) |
                      SAU_UART_SMR_STS_TRIGGER_RXD | (uint16_t) (p_extend_cfg->signal_level << R_SAU0_SMR_SIS0_Pos) |
                      SAU_UART_SMR_MD_UART_MODE);
    p_ctrl->p_reg->SMR[p_ctrl->sau_tx_channel + 1] = smr;

    /* Configure register SCR setting. */
    scr = (uint16_t) (SAU_UART_SCR_DEFAULT_VALUE | SAU_UART_SCR_TRXE_RECEPTION |
                      (uint16_t) (p_cfg->parity << R_SAU0_SCR_PTC_Pos) |
                      (uint16_t) (p_extend_cfg->sequence << R_SAU0_SCR_DIR_Pos) |
                      SAU_UART_SCR_SLC_STOP_BIT1 | p_cfg->data_bits);

    if (BSP_IRQ_DISABLED != (p_cfg->eri_ipl))
    {
        scr |= R_SAU0_SCR_EOC_Msk;
    }

    p_ctrl->p_reg->SCR[p_ctrl->sau_tx_channel + 1] = scr;

    /* Set SDR register value. */
    p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel +
                       1] = (uint16_t) (p_extend_cfg->p_baudrate->stclk << R_SAU0_SDR_STCLK_Pos);
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

 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    const transfer_instance_t * p_dtc_rx = p_ctrl->p_cfg->p_transfer_rx;

    /* Configure transfer instance to receive the requested number of bytes if transfer is used for reception. */
    if (NULL != p_dtc_rx)
    {
        uint32_t size = bytes >> (p_ctrl->extra_data_byte);
  #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(size <= SAU_UART_DTC_MAX_TRANSFER);
  #endif
        err = p_dtc_rx->p_api->reset(p_dtc_rx->p_ctrl, NULL, (void *) p_dest, (uint16_t) size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    /* Save the destination address and size for use in sr_isr. */
    p_ctrl->p_dest    = p_dest;
    p_ctrl->rx_count  = bytes;
    p_ctrl->rx_number = 0;

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
    sau_uart_extended_cfg_t * p_extend_cfg = (sau_uart_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Single transmission mode initialized to transfer end interrupt, continuous transmission mode initialized to buffer empty interrupt */
    p_ctrl->p_reg->SMR[p_ctrl->sau_tx_channel] |= p_extend_cfg->transfer_mode;

    p_ctrl->tx_count  = bytes;
    p_ctrl->tx_number = p_ctrl->extra_data_byte + 1;
    p_ctrl->p_src     = (uint8_t *) p_src;

 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    const transfer_instance_t * p_dtc_tx = p_ctrl->p_cfg->p_transfer_tx;

    /* If a transfer instance is used for transmission, reset the transfer instance to transmit the requested data. */
    if ((NULL != p_dtc_tx) && p_ctrl->tx_count)
    {
        uint32_t num_transfers = p_ctrl->tx_count >> (p_ctrl->extra_data_byte);
        p_ctrl->tx_count = 0U;
  #if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)

        /* Check that the number of transfers is within the 16-bit limit. */
        FSP_ASSERT(num_transfers <= SAU_UART_DTC_MAX_TRANSFER);
  #endif

        err = p_dtc_tx->p_api->reset(p_dtc_tx->p_ctrl,
                                     (void const *) (p_src + p_ctrl->extra_data_byte + 1),
                                     NULL,
                                     (uint16_t)-- num_transfers);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif

    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

    if (0U != p_ctrl->extra_data_byte)
    {
        p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel] = (uint16_t) (p_ctrl->p_src[0] |
                                                                 (p_ctrl->p_src[1] & 0x0001UL) << 8U);
    }
    else
    {
        p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel] = p_ctrl->p_src[0];
    }

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
 *
 * @retval  FSP_SUCCESS                  Baud rate was successfully changed.
 * @retval  FSP_ERR_ASSERTION            Pointer p_ctrl is NULL
 * @retval  FSP_ERR_INVALID_ARGUMENT     p_api_ctrl is empty.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_BaudSet (uart_ctrl_t * const p_api_ctrl, void const * const p_baud_setting)
{
    sau_uart_instance_ctrl_t    * p_ctrl             = (sau_uart_instance_ctrl_t *) p_api_ctrl;
    sau_uart_baudrate_setting_t * p_sau_baud_setting = (sau_uart_baudrate_setting_t *) p_baud_setting;

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(p_sau_baud_setting, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    sau_uart_extended_cfg_t * p_extend_cfg = (sau_uart_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN(p_extend_cfg, FSP_ERR_INVALID_ARGUMENT);
#endif
#if (SAU_UART_CFG_TX_ENABLE)
    p_ctrl->p_reg->ST |= (uint16_t) (SAU_UART_ST_START_TRG_ON << p_ctrl->sau_tx_channel);
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    p_ctrl->p_reg->ST |= (uint16_t) (SAU_UART_ST_START_TRG_ON << (p_ctrl->sau_tx_channel + 1));
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->eri_irq)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    }
#endif

    /* Set SPS register value. */
    if (SAU_UART_OPERATION_CLOCK_CK1 == p_extend_cfg->operation_clock)
    {
        p_ctrl->p_reg->SPS = (uint16_t) ((p_ctrl->p_reg->SPS & ~R_SAU0_SPS_PRS1_Msk) |
                                         (uint16_t) (p_sau_baud_setting->prs << R_SAU0_SPS_PRS1_Pos));
    }
    else
    {
        p_ctrl->p_reg->SPS = (uint16_t) ((p_ctrl->p_reg->SPS & ~R_SAU0_SPS_PRS0_Msk) |
                                         (uint16_t) (p_sau_baud_setting->prs << R_SAU0_SPS_PRS0_Pos));
    }

    /* Set SDR register value. */
    p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel] =
        (uint16_t) (p_extend_cfg->p_baudrate->stclk << R_SAU0_SDR_STCLK_Pos);
    p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel +
                       1] = (uint16_t) (p_extend_cfg->p_baudrate->stclk << R_SAU0_SDR_STCLK_Pos);

#if (SAU_UART_CFG_RX_ENABLE)
    R_BSP_IrqEnable(p_ctrl->p_cfg->rxi_irq);
    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->eri_irq)
    {
        R_BSP_IrqEnable(p_ctrl->p_cfg->eri_irq);
    }
    p_ctrl->p_reg->SS |= (uint16_t) (SAU_UART_SS_START_TRG_ON << (p_ctrl->sau_tx_channel + 1));
#endif

#if (SAU_UART_CFG_TX_ENABLE)
    R_BSP_IrqEnable(p_ctrl->p_cfg->txi_irq);
    p_ctrl->p_reg->SS |= (uint16_t) (SAU_UART_SS_START_TRG_ON << p_ctrl->sau_tx_channel);
#endif

    return FSP_SUCCESS;
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
                                  void const * const           p_context,
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
    sau_uart_instance_ctrl_t * p_ctrl = (sau_uart_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t err = FSP_ERR_UNSUPPORTED;

#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(SAU_UART_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if (SAU_UART_CFG_TX_ENABLE)
    if (UART_DIR_TX & communication_to_abort)
    {
        err = FSP_SUCCESS;
        R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
        if (NULL != p_ctrl->p_cfg->p_transfer_tx)
        {
            err = p_ctrl->p_cfg->p_transfer_tx->p_api->disable(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
        }
 #endif

        p_ctrl->tx_count = 0;
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

#if (SAU_UART_CFG_RX_ENABLE)
    if (UART_DIR_RX & communication_to_abort)
    {
        err              = FSP_SUCCESS;
        p_ctrl->rx_count = 0;
 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
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
    *remaining_bytes  = p_ctrl->rx_count - p_ctrl->rx_number;
    p_ctrl->rx_count  = 0U;
    p_ctrl->rx_number = 0U;
 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        fsp_err_t err = p_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        transfer_properties_t transfer_info;
        err = p_ctrl->p_cfg->p_transfer_rx->p_api->infoGet(p_ctrl->p_cfg->p_transfer_rx->p_ctrl, &transfer_info);
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
 * Calculates baud rate register settings. Evaluates and determines the best possible settings set to the baud rate
 * related registers.
 *
 * @param[in]  baudrate                  Baud rate [bps]. For example, 19200, 57600, 115200, etc.
 * @param[out] p_baud_setting            Baud setting information stored here if successful
 *
 * @retval     FSP_SUCCESS               Baud rate is set successfully
 * @retval     FSP_ERR_ASSERTION         Null pointer
 * @retval     FSP_ERR_INVALID_ARGUMENT  Baud rate is not in intput range
 *                                       max error, or requested max error in baud rate is larger than 15%.
 **********************************************************************************************************************/
fsp_err_t R_SAU_UART_BaudCalculate (uint32_t baudrate, sau_uart_baudrate_setting_t * const p_baud_setting)
{
#if (SAU_UART_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN(p_baud_setting, FSP_ERR_ASSERTION);
    FSP_ERROR_RETURN((0U != baudrate), FSP_ERR_INVALID_ARGUMENT);
#endif

    uint32_t divisor          = 0;
    uint32_t stclk_temp       = 0;
    uint16_t sdr_stclk        = 0U;
    uint16_t cks              = 0U;
    uint32_t delta_error      = INT32_MAX;
    uint32_t temp_delta_error = 0;
    uint32_t temp_actual_rate = 0;

    uint32_t peripheral_clock = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK);

    for (uint16_t cks_index = 0; cks_index <= 15; cks_index++)
    {
        divisor = (1 << (cks_index + 1)) * baudrate;

        /* Calculation and get the nearest integer. */
        stclk_temp = (uint32_t) (((peripheral_clock + divisor / 2) / divisor - 1) + 0.5); // NOLINT(readability-magic-numbers)

        if ((SAU_UART_SDR_MAX >= stclk_temp) && (SAU_UART_SDR_MIN <= stclk_temp))
        {
            temp_actual_rate = (peripheral_clock >> (cks_index + 1)) / ((stclk_temp + 1));
            temp_delta_error = baudrate >=
                               temp_actual_rate ? (baudrate - temp_actual_rate) : (temp_actual_rate - baudrate);
            if (temp_delta_error < delta_error)
            {
                delta_error = temp_delta_error;
                cks         = cks_index;
                sdr_stclk   = (uint16_t) stclk_temp;
            }
        }
    }

    /* Return an error if the percent error is larger than the maximum percent error allowed for this instance */
    FSP_ERROR_RETURN((sdr_stclk != 0), FSP_ERR_INVALID_ARGUMENT);

    p_baud_setting->prs   = cks;
    p_baud_setting->stclk = sdr_stclk;

    return FSP_SUCCESS;
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

    if (0U != p_ctrl->extra_data_byte)
    {
        /* Do not allow odd buffer address if data length is 9 bits. */
        FSP_ERROR_RETURN((0U == ((uint32_t) addr & SAU_UART_ALIGN_2_BYTES)), FSP_ERR_INVALID_ARGUMENT);

        /* Do not allow odd number of data bytes if data length is 9 bits. */
        FSP_ERROR_RETURN(0U == (bytes % 2U), FSP_ERR_INVALID_ARGUMENT);
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

        p_info->transfer_settings_word = SAU_UART_DTC_RX_TRANSFER_SETTINGS;

        /* Casting for compatibility with 7, 8 or 9 bits mode. */
        p_info->p_src = (void *) &(p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel + 1]);

        if (UART_DATA_BITS_9 == p_ctrl->p_cfg->data_bits)
        {
            p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;
        }

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

        p_info->transfer_settings_word = SAU_UART_DTC_TX_TRANSFER_SETTINGS;

        p_info->p_dest = (void *) &(p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel]);

        if (UART_DATA_BITS_9 == p_ctrl->p_cfg->data_bits)
        {
            p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;
        }

        err = p_transfer_tx->p_api->open(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg);

  #if (SAU_UART_CFG_RX_ENABLE)
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
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to UART instance control block
 * @param[in]     data       See uart_callback_args_t in r_uart_api.h
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sau_uart_call_callback (sau_uart_instance_ctrl_t * p_ctrl, uint32_t data, uart_event_t event)
{
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

    if (p_ctrl->tx_count > p_ctrl->tx_number)
    {
        if (0U != p_ctrl->extra_data_byte)
        {
            p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel] = (uint16_t) (p_ctrl->p_src[p_ctrl->tx_number] |
                                                                     (p_ctrl->p_src[p_ctrl->tx_number + 1] &
                                                                      0x0001UL) << 8U);
        }
        else
        {
            p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel] = p_ctrl->p_src[p_ctrl->tx_number];
        }

        p_ctrl->tx_number += p_ctrl->extra_data_byte + 1;
    }
    else
    {
        p_ctrl->p_src     = NULL;
        p_ctrl->tx_count  = 0;
        p_ctrl->tx_number = 0;

        sau_uart_extended_cfg_t * p_extend_cfg = (sau_uart_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
        if (SAU_UART_TRANSFER_MODE_CONTINUOUS == p_extend_cfg->transfer_mode)
        {
            p_ctrl->p_reg->SMR[p_ctrl->sau_tx_channel] &= (uint16_t) ~SAU_UART_SMR_MD0_BUFFER_EMPTY;
        }

        /* If a callback was provided, call it with the argument */
        if (NULL != p_ctrl->p_callback)
        {
            r_sau_uart_call_callback(p_ctrl, 0U, UART_EVENT_TX_COMPLETE);
        }
    }

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

 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    if ((NULL == p_ctrl->p_cfg->p_transfer_rx) || (p_ctrl->rx_number == p_ctrl->rx_count))
 #endif
    {
        uint16_t stclk = p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel + 1];

        if (0U != p_ctrl->extra_data_byte)
        {
            p_ctrl->p_dest[p_ctrl->rx_number] = (uint8_t) (stclk & SAU_UART_SDR_MASK_HIGH8BIT);

            p_ctrl->p_dest[p_ctrl->rx_number + 1] = (uint8_t) (stclk >> 8U);
        }
        else
        {
            p_ctrl->p_dest[p_ctrl->rx_number] = (uint8_t) stclk;
        }

        if (p_ctrl->rx_number < p_ctrl->rx_count)
        {
            p_ctrl->rx_number += p_ctrl->extra_data_byte + 1;

            if (p_ctrl->rx_number == p_ctrl->rx_count)
            {
                p_ctrl->rx_number = 0;
                p_ctrl->rx_count  = 0;
                p_ctrl->p_dest    = NULL;

                /* Call user callback. */
                if (NULL != p_ctrl->p_callback)
                {
                    /* Call callback */
                    r_sau_uart_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
                }
            }
        }
        else
        {
            /* Call user callback. */
            if (NULL != p_ctrl->p_callback)
            {
                /* Call callback */
                r_sau_uart_call_callback(p_ctrl, stclk, UART_EVENT_RX_CHAR);
            }
        }
    }

 #if SAU_UART_CFG_DTC_SUPPORT_ENABLE
    else
    {
        p_ctrl->rx_count = 0;

        p_ctrl->p_dest = NULL;

        /* If a callback was provided, call it with the argument */
        if (NULL != p_ctrl->p_callback)
        {
            /* Call callback */
            r_sau_uart_call_callback(p_ctrl, 0U, UART_EVENT_RX_COMPLETE);
        }
    }
 #endif

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

    if (NULL != p_ctrl->p_callback)
    {
        uint16_t sdr = p_ctrl->p_reg->SDR[p_ctrl->sau_tx_channel + 1];
        uint16_t ssr = p_ctrl->p_reg->SSR[p_ctrl->sau_tx_channel + 1];

        if (SAU_UART_SSR_OVF_OVERRUN & ssr)
        {
            p_ctrl->p_reg->SIR[p_ctrl->sau_tx_channel + 1] |= SAU_UART_SSR_OVF_OVERRUN;
            r_sau_uart_call_callback(p_ctrl, sdr, UART_EVENT_ERR_OVERFLOW);
        }
        else if (SAU_UART_SSR_PEF_PARITY & ssr)
        {
            p_ctrl->p_reg->SIR[p_ctrl->sau_tx_channel + 1] |= SAU_UART_SSR_PEF_PARITY;
            r_sau_uart_call_callback(p_ctrl, sdr, UART_EVENT_ERR_PARITY);
        }
        else if (SAU_UART_SSR_FEF_FRAME & ssr)
        {
            p_ctrl->p_reg->SIR[p_ctrl->sau_tx_channel + 1] |= SAU_UART_SSR_FEF_FRAME;
            r_sau_uart_call_callback(p_ctrl, sdr, UART_EVENT_ERR_FRAMING);
        }
        else
        {
            // Do nothing. Unsupported error type.
        }
    }
    else
    {
        p_ctrl->p_reg->SIR[p_ctrl->sau_tx_channel + 1] = 0;
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif
