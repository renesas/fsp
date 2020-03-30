/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_sci_spi.h"
#include "r_sci_spi_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SCI_SPI_PRV_SCMR_RESERVED_MASK          (0x62U)

#define SCI_SPI_PRV_DTC_RX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << 30U) | (TRANSFER_SIZE_1_BYTE << 28U) | \
                                                 (TRANSFER_ADDR_MODE_FIXED << 26U) | (TRANSFER_IRQ_END << 21U) | \
                                                 (TRANSFER_ADDR_MODE_INCREMENTED << 18U))

#define SCI_SPI_PRV_DTC_TX_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL << 30U) | (TRANSFER_SIZE_1_BYTE << 28U) |       \
                                                 (TRANSFER_ADDR_MODE_INCREMENTED << 26U) | (TRANSFER_IRQ_END << 21U) | \
                                                 (TRANSFER_ADDR_MODE_FIXED << 18U))

#define SCI_SPI_PRV_CLK_MIN_DIV                 (4U)
#define SCI_SPI_PRV_CLK_MAX_DIV                 ((UINT16_MAX + 1U) * 2U)

/** "SCIS" in ASCII, used to determine if channel is open. */
#define SCI_SPI_OPEN                            (0x53434953ULL)

/***********************************************************************************************************************
 * Private global variables.
 **********************************************************************************************************************/

/** SPI HAL module version data structure */
static const fsp_version_t g_sci_spi_version =
{
    .api_version_major  = SPI_API_VERSION_MAJOR,
    .api_version_minor  = SPI_API_VERSION_MINOR,
    .code_version_major = SCI_SPI_CODE_VERSION_MAJOR,
    .code_version_minor = SCI_SPI_CODE_VERSION_MINOR
};

const spi_api_t g_spi_on_sci =
{
    .open       = R_SCI_SPI_Open,
    .read       = R_SCI_SPI_Read,
    .write      = R_SCI_SPI_Write,
    .writeRead  = R_SCI_SPI_WriteRead,
    .close      = R_SCI_SPI_Close,
    .versionGet = R_SCI_SPI_VersionGet
};

/***********************************************************************************************************************
 * Private function declarations.
 **********************************************************************************************************************/

static void r_sci_spi_hw_config(sci_spi_instance_ctrl_t * const p_ctrl);

#if SCI_SPI_DTC_SUPPORT_ENABLE == 1
static fsp_err_t r_sci_spi_transfer_config(sci_spi_instance_ctrl_t * const p_ctrl);

#endif
static fsp_err_t r_sci_spi_write_read_common(sci_spi_instance_ctrl_t * const p_ctrl,
                                             void const                    * p_src,
                                             void                          * p_dest,
                                             uint32_t const                  length);
static void r_sci_spi_start_transfer(sci_spi_instance_ctrl_t * const p_ctrl);
static void r_sci_spi_transmit(sci_spi_instance_ctrl_t * p_ctrl);

void sci_spi_txi_isr(void);
void sci_spi_rxi_isr(void);
void sci_spi_tei_isr(void);
void sci_spi_eri_isr(void);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup SCI_SPI
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize a channel for SPI communication mode. Implements @ref spi_api_t::open.
 *
 * This function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enables the clock for the SCI channel.
 *   - Initializes the associated registers with default value and the user-configurable options.
 *   - Provides the channel handle for use with other API functions.
 *
 * @param      p_api_ctrl                      Pointer to the control structure.
 * @param      p_cfg                           Pointer to a configuration structure.
 *
 * @retval     FSP_SUCCESS                     Channel initialized successfully.
 * @retval     FSP_ERR_ASSERTION               An input parameter is invalid or NULL.
 * @retval     FSP_ERR_ALREADY_OPEN            The instance has already been opened.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  The channel number is invalid.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_Open (spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t                 err    = FSP_SUCCESS;

#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_SPI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ERROR_RETURN(BSP_FEATURE_SCI_CHANNELS & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ASSERT(p_cfg->rxi_irq >= 0);
    FSP_ASSERT(p_cfg->txi_irq >= 0);
    FSP_ASSERT(p_cfg->tei_irq >= 0);
    FSP_ASSERT(p_cfg->eri_irq >= 0);
#endif

    p_ctrl->p_reg = (R_SCI0_Type *) ((R_SCI1_BASE - R_SCI0_BASE) * p_cfg->channel + R_SCI0_BASE);
    p_ctrl->p_cfg = p_cfg;

#if SCI_SPI_DTC_SUPPORT_ENABLE == 1

    /* Open the SCI SPI transfer interface if available. */
    err = r_sci_spi_transfer_config(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Write user configuration to registers. */
    r_sci_spi_hw_config(p_ctrl);

    /* Enable required interrupts. */
    R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->rxi_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->txi_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->tei_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->eri_irq, p_cfg->eri_ipl, p_ctrl);

    p_ctrl->open = SCI_SPI_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Receive data from an SPI device. Implements @ref spi_api_t::read.
 *
 * The function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enable transmitter.
 *   - Enable receiver.
 *   - Enable interrupts.
 *   - Start data transmission by writing data to the TXD register.
 *   - Receive data from receive buffer full interrupt occurs and copy data to the buffer of destination.
 *   - Complete data reception via receive buffer full interrupt and transmitting dummy data.
 *   - Disable transmitter.
 *   - Disable receiver.
 *   - Disable interrupts.
 *
 * @param      p_api_ctrl           Pointer to the control structure.
 * @param      p_dest               Pointer to the destination buffer.
 * @param[in]  length               The number of bytes to transfer.
 * @param[in]  bit_width            Invalid for SCI_SPI (Set to SPI_BIT_WIDTH_8_BITS).
 *
 * @retval     FSP_SUCCESS          Read operation successfully completed.
 * @retval     FSP_ERR_ASSERTION    One of the following invalid parameters passed:
 *                                  - Pointer p_api_ctrl is NULL
 *                                  - Bit width is not 8 bits
 *                                  - Length is equal to 0
 *                                  - Pointer to destination is NULL
 * @retval     FSP_ERR_NOT_OPEN     The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_UNSUPPORTED  The given bit_width is not supported.
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_Read (spi_ctrl_t * const    p_api_ctrl,
                          void                * p_dest,
                          uint32_t const        length,
                          spi_bit_width_t const bit_width)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE

    /* Check bit_width parameter, in simple SPI, only 8 bits operation is allowed. */
    FSP_ERROR_RETURN(SPI_BIT_WIDTH_8_BITS == bit_width, FSP_ERR_UNSUPPORTED);

    /* Check the destination, should not be NULL. */
    FSP_ASSERT(NULL != p_dest);
#else
    FSP_PARAMETER_NOT_USED(bit_width);
#endif

    return r_sci_spi_write_read_common(p_ctrl, NULL, p_dest, length);
}

/*******************************************************************************************************************//**
 * Transmit data to a SPI  device. Implements @ref spi_api_t::write.
 *
 * The function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enable transmitter.
 *   - Enable interrupts.
 *   - Start data transmission with data via transmit buffer empty interrupt.
 *   - Copy data from source buffer to the SPI data register for transmission.
 *   - Complete data transmission via transmit buffer empty interrupt.
 *   - Disable transmitter.
 *   - Disable receiver.
 *   - Disable interrupts.
 *
 * @param      p_api_ctrl           Pointer to the control structure.
 * @param      p_src                Pointer to the source buffer.
 * @param[in]  length               The number of bytes to transfer.
 * @param[in]  bit_width            Invalid for SCI_SPI (Set to SPI_BIT_WIDTH_8_BITS).
 *
 * @retval     FSP_SUCCESS          Write operation successfully completed.
 * @retval     FSP_ERR_ASSERTION    One of the following invalid parameters passed:
 *                                  - Pointer p_api_ctrl is NULL
 *                                  - Pointer to source is NULL
 *                                  - Length is equal to 0
 *                                  - Bit width is not equal to 8 bits
 * @retval     FSP_ERR_NOT_OPEN     The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_UNSUPPORTED  The given bit_width is not supported.
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_Write (spi_ctrl_t * const    p_api_ctrl,
                           void const          * p_src,
                           uint32_t const        length,
                           spi_bit_width_t const bit_width)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(SPI_BIT_WIDTH_8_BITS == bit_width, FSP_ERR_UNSUPPORTED);
    FSP_ASSERT(NULL != p_src);
#else
    FSP_PARAMETER_NOT_USED(bit_width);
#endif

    return r_sci_spi_write_read_common(p_ctrl, p_src, NULL, length);
}

/*******************************************************************************************************************//**
 * Simultaneously transmit data to SPI device while receiving data from SPI device (full duplex).
 * Implements @ref spi_api_t::writeRead.
 *
 * The function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enable transmitter.
 *   - Enable receiver.
 *   - Enable interrupts.
 *   - Start data transmission using transmit buffer empty interrupt (or by writing to the TDR register).
 *   - Copy data from source buffer to the SPI data register for transmission.
 *   - Receive data from receive buffer full interrupt and copy data to the destination buffer.
 *   - Complete data transmission and reception via transmit end interrupt.
 *   - Disable transmitter.
 *   - Disable receiver.
 *   - Disable interrupts.
 *
 * @param      p_api_ctrl           Pointer to the control structure.
 * @param      p_src                Pointer to the source buffer.
 * @param      p_dest               Pointer to the destination buffer.
 * @param[in]  length               The number of bytes to transfer.
 * @param[in]  bit_width            Invalid for SCI_SPI (Set to SPI_BIT_WIDTH_8_BITS).
 *
 * @retval     FSP_SUCCESS          Write operation successfully completed.
 * @retval     FSP_ERR_ASSERTION    One of the following invalid parameters passed:
 *                                  - Pointer p_api_ctrl is NULL
 *                                  - Pointer to source is NULL
 *                                  - Pointer to destination is NULL
 *                                  - Length is equal to 0
 *                                  - Bit width is not equal to 8 bits
 * @retval     FSP_ERR_NOT_OPEN     The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_UNSUPPORTED  The given bit_width is not supported.
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_WriteRead (spi_ctrl_t * const    p_api_ctrl,
                               void const          * p_src,
                               void                * p_dest,
                               uint32_t const        length,
                               spi_bit_width_t const bit_width)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(SPI_BIT_WIDTH_8_BITS == bit_width, FSP_ERR_UNSUPPORTED);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
#else
    FSP_PARAMETER_NOT_USED(bit_width);
#endif

    return r_sci_spi_write_read_common(p_ctrl, p_src, p_dest, length);
}

/*******************************************************************************************************************//**
 * Disable the SCI channel and set the instance as not open. Implements @ref spi_api_t::close.
 *
 * @param      p_api_ctrl         Pointer to an opened instance.
 *
 * @retval     FSP_SUCCESS        Channel successfully closed.
 * @retval     FSP_ERR_ASSERTION  The parameter p_api_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN   The channel has not been opened. Open the channel first.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_Close (spi_ctrl_t * const p_api_ctrl)
{
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) p_api_ctrl;

#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear the RE and TE bits in SCR. */
    p_ctrl->p_reg->SCR = 0;

    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    /* Disable the clock to the SCI channel. */
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_ctrl->p_cfg->channel);

    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }

    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the version information of the underlying driver. Implements @ref spi_api_t::versionGet.
 * @param      p_version          Pointer to version structure.
 * @retval     FSP_SUCCESS        Successful version get.
 * @retval     FSP_ERR_ASSERTION  The parameter p_version is NULL.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_VersionGet (fsp_version_t * p_version)
{
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_sci_spi_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculate the register settings required to achieve the desired bitrate.
 *
 * @param[in]  bitrate            bitrate[bps] e.g. 250,000; 500,00; 2,500,000(max), etc.
 * @param      sclk_div           Pointer to sci_spi_div_setting_t used to configure baudrate settings.
 * @param[in]  use_mddr           Calculate the divider settings for use with MDDR.
 *
 * @retval     FSP_SUCCESS        Baud rate is set successfully.
 * @retval     FSP_ERR_ASSERTION  Baud rate is not achievable.
 * @note       The application must pause for 1 bit time after the BRR register is loaded before transmitting/receiving
 *             to allow time for the clock to settle.
 **********************************************************************************************************************/
fsp_err_t R_SCI_SPI_CalculateBitrate (uint32_t bitrate, sci_spi_div_setting_t * sclk_div, bool use_mddr)
{
    uint32_t peripheral_clock = R_FSP_SystemClockHzGet(BSP_FEATURE_SCI_CLOCK);

#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != sclk_div);
    FSP_ASSERT(bitrate);
    FSP_ASSERT(bitrate >= (peripheral_clock + SCI_SPI_PRV_CLK_MAX_DIV - 1U) / SCI_SPI_PRV_CLK_MAX_DIV);
#endif

    int32_t divisor = 0;
    int32_t brr     = 0;
    int32_t cks     = -1;

    for (uint32_t i = 0; i <= 3; i++)
    {
        cks++;
        divisor = (1 << (2 * (i + 1))) * (int32_t) bitrate;

        /* Calculate BRR so that the bit rate is the largest possible value less than or equal to the desired
         * bitrate. */
        brr = ((int32_t) peripheral_clock + divisor - 1) / divisor - 1;

        if (brr <= UINT8_MAX)
        {
            break;
        }
    }

    /* If mddr is not used, set it to 0. */
    int64_t mddr = 0;

    if (use_mddr)
    {
        /* Calculate BRR by rounding down. */
        brr = (int32_t) peripheral_clock / divisor - 1;

        /*
         * If a bit rate greater than the max possible bit rate is passed in, this
         * calculation will be negative.
         */
        if (brr < 0)
        {
            brr = 0;
        }

        /* In the most extreme case this will result in a bit rate that is ~2 times the
         * desired bitrate (This will be compensated for by setting MDDR).
         */
        if (brr > UINT8_MAX)
        {
            brr = UINT8_MAX;
        }

        /* The maximum result of this calculation is 256 which occurs when the exact bitrate can be achieved without
         * using mddr (promote to 64 bit so the intermediate calculation does not overflow). */
        mddr = (int64_t) divisor * (brr + 1) * (UINT8_MAX + 1) / peripheral_clock;

        if (mddr > UINT8_MAX)
        {
            /* Set MDDR to 0 to disable it. */
            mddr = 0;
        }
    }

    sclk_div->brr  = (uint8_t) brr;
    sclk_div->cks  = (uint8_t) (cks & 3);
    sclk_div->mddr = (uint8_t) mddr;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_SPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures SCI registers based on the user configuration.
 * @param      p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_sci_spi_hw_config (sci_spi_instance_ctrl_t * const p_ctrl)
{
    spi_cfg_t const        * p_cfg    = p_ctrl->p_cfg;
    sci_spi_extended_cfg_t * p_extend = (sci_spi_extended_cfg_t *) p_cfg->p_extend;

    /* Initialize registers to their reset values. */
    uint32_t smr  = R_SCI0_SMR_CM_Msk;
    uint32_t scr  = 0;
    uint32_t scmr = (2U << R_SCI0_SCMR_CHR1_Pos) | R_SCI0_SCMR_BCP2_Msk | SCI_SPI_PRV_SCMR_RESERVED_MASK;
    uint32_t spmr = 0U;
    uint32_t mddr = UINT8_MAX;
    uint32_t semr = 0;

    /* Select the baud rate generator clock divider. */
    smr |= (uint32_t) (p_extend->clk_div.cks << R_SCI0_SMR_CKS_Pos);

    if (p_extend->clk_div.mddr > INT8_MAX)
    {
        /* If a valid MDDR setting is given than enable MDDR. */
        semr |= R_SCI0_SEMR_BRME_Msk;
        mddr  = p_extend->clk_div.mddr;
    }

    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        /* Select slave mode. */
        spmr |= R_SCI0_SPMR_MSS_Msk;

        /* Select to use SSLn input pin */
        spmr |= R_SCI0_SPMR_SSE_Msk;

        /* Use external clock for baud rate (Default is on-chip baud rate generator). */
        scr |= (2U << R_SCI0_SCR_CKE_Pos);
    }

    if (SPI_CLK_PHASE_EDGE_EVEN == p_cfg->clk_phase)
    {
        /* In order to get sampling on the even clock edge (CPHA = 1) set SPMR.CKPH to 0. */
        if (SPI_CLK_POLARITY_LOW == p_cfg->clk_polarity)
        {
            /* If SPMR.CKPH is set to 0 then CKPOL must be set to 1 to make the clock low during idle (CPOL = 0).
             * See Figure 34.70 in the RA6M3 manual R01UH0886EJ0100. */
            spmr |= R_SCI0_SPMR_CKPOL_Msk;
        }
    }
    else
    {
        /* In order to get sampling on the ODD edge (CPHA = 0) set SPMR.CKPH to 1. */
        spmr |= R_SCI0_SPMR_CKPH_Msk;

        if (SPI_CLK_POLARITY_HIGH == p_cfg->clk_polarity)
        {
            /* If SPMR.CKPH is set to 1 then CKPOL must be set to 1 to make the clock high during idle (CPOL = 1).
             * See Figure 34.70 in the RA6M3 manual R01UH0886EJ0100. */
            spmr |= R_SCI0_SPMR_CKPOL_Msk;
        }
    }

    if (SPI_BIT_ORDER_MSB_FIRST == p_cfg->bit_order)
    {
        /* Configure MSB first (Default is LSB). */
        scmr |= R_SCI0_SCMR_SDIR_Msk;
    }

    /* Enable Clock for the SCI Channel. */
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);

    /* Clear the RE and TE bits before writing other settings. See section 34.2 Register Descriptions in the
     * RA6M3 manual R01UH0886EJ0100. */
    p_ctrl->p_reg->SCR = 0;

    /* Must read SSR in order to clear the RX overflow error. Reference section 34.2.13 Serial Status Register (SSR)
     * in the RA6M3 manual R01UH0886EJ0100.*/
    p_ctrl->p_reg->SSR;

    /* Clear the error status flags. */
    p_ctrl->p_reg->SSR = (uint8_t) (R_SCI0_SSR_TDRE_Msk | R_SCI0_SSR_TEND_Msk);

    /* Disable fifo mode. See Figure 34.32 Example flow of SCI initialization in clock synchronous mode with non-FIFO
     * selected in the RA6M3 manual R01UH0886EJ0100. */
    p_ctrl->p_reg->FCR = R_SCI0_FCR_RSTRG_Msk | (8U << R_SCI0_FCR_RTRG_Pos);

    /* Write settings to registers. */
    p_ctrl->p_reg->SMR  = (uint8_t) smr;
    p_ctrl->p_reg->SCR  = (uint8_t) scr;
    p_ctrl->p_reg->SCMR = (uint8_t) scmr;
    p_ctrl->p_reg->BRR  = p_extend->clk_div.brr;
    p_ctrl->p_reg->MDDR = (uint8_t) mddr;
    p_ctrl->p_reg->SEMR = (uint8_t) semr;
    p_ctrl->p_reg->SPMR = (uint8_t) spmr;

    /* Set unused registers to their value after reset. */
    p_ctrl->p_reg->SNFR  = 0;
    p_ctrl->p_reg->SIMR1 = 0;
    p_ctrl->p_reg->SIMR2 = 0;
    p_ctrl->p_reg->SIMR3 = 0;
    p_ctrl->p_reg->CDR   = 0;
    p_ctrl->p_reg->DCCR  = R_SCI0_DCCR_IDSEL_Msk;
    p_ctrl->p_reg->SPTR  = R_SCI0_SPTR_SPB2DT_Msk;
}

#if SCI_SPI_DTC_SUPPORT_ENABLE == 1

/*******************************************************************************************************************//**
 * Configures SCI SPI related transfer drivers (if enabled).
 *
 * @param[in]     p_cfg                     Pointer to SCI SPI specific configuration structure.
 * @param[in]     p_fsp_feature             FSP feature.
 *
 * @retval        FSP_SUCCESS               Operation successfully completed.
 * @retval        FSP_ERR_ASSERTION         One of the following invalid parameters passed:
 *                                          - Pointer p_cfg is NULL
 *                                          - Interrupt is not enabled
 * @retval        FSP_ERR_INVALID_ARGUMENT  DTC is used for data transmission but not used for data reception or
 *                                          vice versa.
 **********************************************************************************************************************/
static fsp_err_t r_sci_spi_transfer_config (sci_spi_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t               err   = FSP_SUCCESS;
    spi_cfg_t const * const p_cfg = p_ctrl->p_cfg;

    if (NULL != p_cfg->p_transfer_rx)
    {
        /* Set the initial configuration for the rx transfer instance. */
        transfer_instance_t const * p_transfer = p_cfg->p_transfer_rx;
        p_transfer->p_cfg->p_info->transfer_settings_word = SCI_SPI_PRV_DTC_RX_TRANSFER_SETTINGS;
        p_transfer->p_cfg->p_info->p_src = (void *) &p_ctrl->p_reg->RDR;

        /* Open the transfer instance. */
        err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        /* Set the initial configuration for the tx transfer instance. */
        transfer_instance_t const * p_transfer = p_cfg->p_transfer_tx;
        p_transfer->p_cfg->p_info->transfer_settings_word = SCI_SPI_PRV_DTC_TX_TRANSFER_SETTINGS;
        p_transfer->p_cfg->p_info->p_dest                 = (void *) &p_ctrl->p_reg->TDR;

        /* Open the transfer instance. */
        err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
        if (FSP_SUCCESS != err)
        {
            if (NULL != p_cfg->p_transfer_rx)
            {
                /* If the tx transfer instance could not be opened, close the rx transfer instance. */
                p_cfg->p_transfer_rx->p_api->close(p_cfg->p_transfer_rx->p_ctrl);
            }

            return err;
        }
    }

    return err;
}

#endif

/*******************************************************************************************************************//**
 * Initiates writ or read process. Common routine used by SPI API write or read functions.
 *
 * @param[in]  p_ctrl             Pointer to the control block.
 * @param[in]  p_src              Pointer to data buffer which need to be sent.
 * @param[out] p_dest             Pointer to buffer where received data will be stored.
 * @param[in]  length             Number of data transactions to be performed.
 *
 * @retval     FSP_SUCCESS        Operation successfully completed.
 * @retval     FSP_ERR_NOT_OPEN   The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_ASSERTION  One of the following invalid parameters passed:
 *                                  - Pointer p_ctrl is NULL
 *                                  - length == 0
 *                                  - if DTC is used and length > UINT16_MAX
 * @retval     FSP_ERR_IN_USE     A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
static fsp_err_t r_sci_spi_write_read_common (sci_spi_instance_ctrl_t * const p_ctrl,
                                              void const                    * p_src,
                                              void                          * p_dest,
                                              uint32_t const                  length)
{
#if SCI_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0 != length);
    if ((NULL != p_ctrl->p_cfg->p_transfer_tx) || (NULL != p_ctrl->p_cfg->p_transfer_rx))
    {
        /* The DTC is only capable of a max of 64K transfers. */
        FSP_ASSERT(length <= UINT16_MAX);
    }
#endif

    /* TE and RE must be zero in order to write one to TE or RE (TE and RE will only be set if there is a transfer in
     * progress. Reference section 34.2.11 Serial Control Register (SCR) in the RA6M3 manual R01UH0886EJ0100. */
    FSP_ERROR_RETURN(0 == (p_ctrl->p_reg->SCR & (R_SCI0_SCR_RE_Msk | R_SCI0_SCR_TE_Msk)), FSP_ERR_IN_USE);

    /* Setup the control block. */
    p_ctrl->count    = length;
    p_ctrl->tx_count = 0U;
    p_ctrl->rx_count = 0U;
    p_ctrl->p_src    = (uint8_t *) p_src;
    p_ctrl->p_dest   = (uint8_t *) p_dest;

#if SCI_SPI_DTC_SUPPORT_ENABLE == 1
    if (p_ctrl->p_cfg->p_transfer_tx)
    {
        /* Configure the tx transfer instance. */
        p_ctrl->tx_count = length;
        transfer_instance_t const * p_transfer = p_ctrl->p_cfg->p_transfer_tx;
        p_transfer->p_cfg->p_info->length = (uint16_t) length;

        if (NULL == p_src)
        {
            /* If the source is NULL transmit using a dummy value using FIXED mode. */
            static uint8_t tx_dummy = 0;
            p_transfer->p_cfg->p_info->src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
            p_transfer->p_cfg->p_info->p_src         = &tx_dummy;
        }
        else
        {
            p_transfer->p_cfg->p_info->src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
            p_transfer->p_cfg->p_info->p_src         = p_src;
        }

        /* Enable the transfer instance. */
        fsp_err_t err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_transfer->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* The rx transfer instance is not used if p_dest is NULL. */
    if ((NULL != p_ctrl->p_cfg->p_transfer_rx) && (NULL != p_dest))
    {
        /* Configure the rx transfer instance. */
        p_ctrl->rx_count = length;
        transfer_instance_t const * p_transfer = p_ctrl->p_cfg->p_transfer_rx;

        /* Enable the transfer instance. */
        fsp_err_t err = p_transfer->p_api->reset(p_transfer->p_ctrl, NULL, p_dest, (uint16_t) length);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    /* Enable transmit and receive interrupts. */
    r_sci_spi_start_transfer(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables and disables Receive and Transmit mode based on the current configuration.
 *
 * @param      p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_sci_spi_start_transfer (sci_spi_instance_ctrl_t * const p_ctrl)
{
    /* TE must always be enabled even when receiving data. When RE is enabled without also enabling TE, the SCI will
     * continue transfering data until the RE bit is cleared. At high bitrates, it is not possible to clear the RE bit
     * fast enough and there will be additional clock pulses at the end of the transfer. */
    uint32_t interrupt_settings = R_SCI0_SCR_TE_Msk;

    if ((NULL == p_ctrl->p_dest) || (NULL != p_ctrl->p_cfg->p_transfer_tx) || (NULL != p_ctrl->p_cfg->p_transfer_rx))
    {
        /* Enable the transmit IRQ. */
        interrupt_settings |= R_SCI0_SCR_TIE_Msk;
    }

    if (NULL != p_ctrl->p_dest)
    {
        /* Enable Receive mode and the Receive buffer full IRQ. */
        interrupt_settings |= (R_SCI0_SCR_RE_Msk | R_SCI0_SCR_RIE_Msk);
    }

    /* Write the transfer settings. */
    p_ctrl->p_reg->SCR |= (uint8_t) interrupt_settings;

    /* Transmit from RXI interrupt. */
    if ((NULL == p_ctrl->p_cfg->p_transfer_tx) && (NULL == p_ctrl->p_cfg->p_transfer_rx) && (NULL != p_ctrl->p_dest))
    {
        /* The rxi interrupt must be disabled so that r_sci_spi_transmit is not interrupted before it updates the
         * tx_count. */
        R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);

        /* When transmitting from the RXI interrupt, the first byte must be written here because the transmit buffer
         * empty IRQ is disabled. */
        r_sci_spi_transmit(p_ctrl);

        if ((SPI_MODE_SLAVE == p_ctrl->p_cfg->operating_mode) && (1 < p_ctrl->count))
        {
            /* First call writes directly to the TSR register. The second call writes to the TDR register. */
            r_sci_spi_transmit(p_ctrl);
        }

        /* In master mode the rxi interrupt will fire as soon as it is enabled. */
        R_BSP_IrqEnableNoClear(p_ctrl->p_cfg->rxi_irq);
    }
}

/*******************************************************************************************************************//**
 * Transmit a single byte of data.
 * @param      p_ctrl          Pointer to the control structure.
 **********************************************************************************************************************/
static void r_sci_spi_transmit (sci_spi_instance_ctrl_t * p_ctrl)
{
    if (p_ctrl->tx_count < p_ctrl->count)
    {
        if (p_ctrl->p_src)
        {
            p_ctrl->p_reg->TDR = p_ctrl->p_src[p_ctrl->tx_count];
        }
        else
        {
            /* Do a dummy write if there is no tx buffer. */
            p_ctrl->p_reg->TDR = 0;
        }

        p_ctrl->tx_count++;
    }
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SCI_SPI Transmit Buffer Empty IRQ.
 *
 * The Transmit Buffer Empty IRQ is enabled in the following conditions:
 *   - The transfer is started using R_SCI_SPI_Write API (There is no data to receive).
 *   - The rxi IRQ is serviced using a DTC instance.
 *   - The txi IRQ is serviced using a DTC instance (The interrupt will fire on the last byte transfered).
 *
 **********************************************************************************************************************/
void sci_spi_txi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Write the next byte to the TDR register. */
    r_sci_spi_transmit(p_ctrl);

    if ((p_ctrl->tx_count == p_ctrl->count) && (NULL == p_ctrl->p_dest))
    {
        /* If the last byte is transmitted and there is no data to receive then enable the transmit end IRQ and disable
         * the transmit IRQ. */
        p_ctrl->p_reg->SCR = (uint8_t) ((p_ctrl->p_reg->SCR & ~R_SCI0_SCR_TIE_Msk) | R_SCI0_SCR_TEIE_Msk);
    }

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SCI_SPI Receive Buffer Full IRQ.
 * This handler also handles Transmit Buffer Empty IRQs.
 *
 * The Receive Buffer Full IRQ is enabled in the following conditions:
 *   - The transfer is started using either the R_SCI_SPI_Read or R_SCI_SPI_WriteRead API.
 *
 **********************************************************************************************************************/
void sci_spi_rxi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Write the next byte to the TDR register
     * (Whenever the rxi isr is enabled, the transmit isr is disabled and transmit is handled here). */
    r_sci_spi_transmit(p_ctrl);

    /* Read the next byte from the RDR register. */
    if (p_ctrl->rx_count < p_ctrl->count)
    {
        p_ctrl->p_dest[p_ctrl->rx_count++] = p_ctrl->p_reg->RDR;
    }

    if (p_ctrl->rx_count == p_ctrl->count)
    {
        /* If the last byte is received then enable the transmit end IRQ and disable the receive and transmit IRQs. */
        p_ctrl->p_reg->SCR =
            (uint8_t) ((p_ctrl->p_reg->SCR & ~(R_SCI0_SCR_TIE_Msk | R_SCI0_SCR_RIE_Msk)) | R_SCI0_SCR_TEIE_Msk);
    }

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SCI_SPI Transmit End IRQ.
 *
 * The Transmit End IRQ is enabled after the last byte of data has been transfered.
 *
 **********************************************************************************************************************/
void sci_spi_tei_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type                 irq    = R_FSP_CurrentIrqGet();
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disables receiver, transmitter and transmit end IRQ. */
    p_ctrl->p_reg->SCR &= (uint8_t) R_SCI0_SCR_CKE_Msk;

    /* Notify the user that the transfer has completed. */
    spi_callback_args_t sci_spi_cb_data =
    {
        .channel   = p_ctrl->p_cfg->channel,
        .event     = SPI_EVENT_TRANSFER_COMPLETE,
        .p_context = p_ctrl->p_cfg->p_context
    };

    p_ctrl->p_cfg->p_callback(&sci_spi_cb_data);

    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for  R_SCI_SPI Error IRQs.
 *
 * This handler is only enabled if the user passes in a valid IRQ number in Pointer to a configuration structure.
 * structure.
 **********************************************************************************************************************/
void sci_spi_eri_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE;

    IRQn_Type                 irq    = R_FSP_CurrentIrqGet();
    sci_spi_instance_ctrl_t * p_ctrl = (sci_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disables receiver, transmitter and transmit end IRQ. */
    p_ctrl->p_reg->SCR &= (uint8_t) R_SCI0_SCR_CKE_Msk;

    /* Must read SSR in order to clear the RX overflow error. Reference section 34.2.13 Serial Status Register (SSR)
     * in the RA6M3 manual R01UH0886EJ0100.*/
    p_ctrl->p_reg->SSR;

    /* Clear the error status flags (The only possible error is an RX overflow). */
    p_ctrl->p_reg->SSR = (uint8_t) (R_SCI0_SSR_TDRE_Msk | R_SCI0_SSR_TEND_Msk);

    /* Notify the user that an error occurred. */
    spi_callback_args_t sci_spi_cb_data = {0};
    sci_spi_cb_data.channel   = p_ctrl->p_cfg->channel;
    sci_spi_cb_data.event     = SPI_EVENT_ERR_READ_OVERFLOW;
    sci_spi_cb_data.p_context = p_ctrl->p_cfg->p_context;
    p_ctrl->p_cfg->p_callback(&sci_spi_cb_data);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting. */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE;
}
