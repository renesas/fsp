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
#include <string.h>
#include "r_sau_spi.h"
#include "r_sau_spi_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SAU_SPI_SCR_RX_MSK           (0x4000U)
#define SAU_SPI_SCR_TX_MSK           (0x8000U)
#define R_SAU0_SCR_DCP1_Pos          (13U)

#define SAU_REG_SIZE                 (R_SAU1_BASE - R_SAU0_BASE)
#define SAU_SPI_SMR_INIT_VALUE       (0x0020U)
#define SAU_SPI_SCR_INIT_VALUE       (0x0007U)

#define SAU_SPI_PSR_MIN_DIV_2        (2U)
#define SAU_SPI_PSR_MIN_DIV_4        (4U)
#define SAU_SPI_SDR_STCLK_MAX_DIV    (256U)
#define SAU_SPI_PSR_MAX_DIV          (32768U)
#define R_SAU_SDR_DUMMY_DATA         (0xFFU)
#if SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE == 1
 #define SAU_REG                     (R_SAU0)
#elif SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE == 2
 #define SAU_REG                     (R_SAU1)
#else
 #define SAU_REG                     (p_ctrl->p_reg)
#endif

/** "SAU" in ASCII, used to determine if channel is open. */
#define SAU_SPI_OPEN                 (0x53415553ULL)

/***********************************************************************************************************************
 * Private global variables.
 **********************************************************************************************************************/

const spi_api_t g_spi_on_sau =
{
    .open        = R_SAU_SPI_Open,
    .read        = R_SAU_SPI_Read,
    .write       = R_SAU_SPI_Write,
    .writeRead   = R_SAU_SPI_WriteRead,
    .close       = R_SAU_SPI_Close,
    .callbackSet = R_SAU_SPI_CallbackSet
};

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function declarations.
 **********************************************************************************************************************/

static void r_sau_spi_hw_config(sau_spi_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sau_spi_write_read_common(sau_spi_instance_ctrl_t * const p_ctrl,
                                             void const                    * p_src,
                                             void                          * p_dest,
                                             uint32_t const                  length,
                                             spi_bit_width_t const           bit_width);
static void r_sau_spi_start_transfer(sau_spi_instance_ctrl_t * const p_ctrl);

#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION || \
    SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION
static void r_sau_spi_transmit(sau_spi_instance_ctrl_t * p_ctrl);

#endif
#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION || \
    SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION
static void r_sau_spi_receive(sau_spi_instance_ctrl_t * p_ctrl);

#endif
static void r_sau_spi_call_callback(sau_spi_instance_ctrl_t * p_ctrl, spi_event_t event);

#if (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION)
static void r_sau_spi_do_transmission(sau_spi_instance_ctrl_t * p_ctrl, spi_cfg_t const * p_cfg);

#elif (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION)
static void r_sau_spi_do_reception(sau_spi_instance_ctrl_t * p_ctrl, spi_cfg_t const * p_cfg);

#else
static void r_sau_spi_do_transmission_reception(sau_spi_instance_ctrl_t * p_ctrl, spi_cfg_t const * p_cfg);

#endif
void sau_spi_txrxi_isr(void);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup SAU_SPI
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize a channel for SPI communication mode. Implements @ref spi_api_t::open.
 *
 * This function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enables the clock for the SAU channel.
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
fsp_err_t R_SAU_SPI_Open (spi_ctrl_t * p_api_ctrl, spi_cfg_t const * const p_cfg)
{
    fsp_err_t                 err    = FSP_SUCCESS;
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;
#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
#endif
    sau_spi_extended_cfg_t * p_extend = (sau_spi_extended_cfg_t *) p_cfg->p_extend;

#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SAU_SPI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(p_cfg->tei_irq >= 0);
#endif
#if !SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE
    p_ctrl->p_reg = ((R_SAU0_Type *) (R_SAU0_BASE + (SAU_REG_SIZE * p_extend->sau_unit)));
#endif
    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

    /* Enable Clock for the SAU Channel. */
    R_BSP_MODULE_START(FSP_IP_SAU, p_extend->sau_unit);

    /* Write user configuration to registers. */
    r_sau_spi_hw_config(p_ctrl);

    /* Enable required interrupts. */
    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->tei_ipl, p_ctrl);

    p_ctrl->open = SAU_SPI_OPEN;

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
 * @param[in]  bit_width            Invalid for SAU_SPI (Set to SPI_BIT_WIDTH_8_BITS).
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
fsp_err_t R_SAU_SPI_Read (spi_ctrl_t * const    p_api_ctrl,
                          void                * p_dest,
                          uint32_t const        length,
                          spi_bit_width_t const bit_width)
{
#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);

    /* Check bit_width parameter, in simple SPI, 7 or 8 bits operation is allowed. */
    FSP_ERROR_RETURN((SPI_BIT_WIDTH_8_BITS == bit_width) || (SPI_BIT_WIDTH_7_BITS == bit_width), FSP_ERR_UNSUPPORTED);

    /* Check the destination, should not be NULL. */
    FSP_ASSERT(NULL != p_dest);
#endif
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

    return r_sau_spi_write_read_common(p_ctrl, NULL, p_dest, length, bit_width);
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
 * @param[in]  bit_width            Invalid for SAU_SPI (Set to SPI_BIT_WIDTH_8_BITS).
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
fsp_err_t R_SAU_SPI_Write (spi_ctrl_t * const    p_api_ctrl,
                           void const          * p_src,
                           uint32_t const        length,
                           spi_bit_width_t const bit_width)
{
#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN((SPI_BIT_WIDTH_8_BITS == bit_width) || (SPI_BIT_WIDTH_7_BITS == bit_width), FSP_ERR_UNSUPPORTED);
    FSP_ASSERT(NULL != p_src);
#endif
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

    return r_sau_spi_write_read_common(p_ctrl, p_src, NULL, length, bit_width);
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
 * @param[in]  bit_width            Invalid for SAU_SPI (Set to SPI_BIT_WIDTH_8_BITS).
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
fsp_err_t R_SAU_SPI_WriteRead (spi_ctrl_t * const    p_api_ctrl,
                               void const          * p_src,
                               void                * p_dest,
                               uint32_t const        length,
                               spi_bit_width_t const bit_width)
{
#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_api_ctrl);
    FSP_ERROR_RETURN((SPI_BIT_WIDTH_8_BITS == bit_width) || (SPI_BIT_WIDTH_7_BITS == bit_width), FSP_ERR_UNSUPPORTED);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
#endif
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

    return r_sau_spi_write_read_common(p_ctrl, p_src, p_dest, length, bit_width);
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements spi_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_SAU_SPI_CallbackSet (spi_ctrl_t * const          p_api_ctrl,
                                 void (                    * p_callback)(spi_callback_args_t *),
                                 void const * const          p_context,
                                 spi_callback_args_t * const p_callback_memory)
{
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

#if (SAU_SPI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SAU_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL == p_callback_memory);
#else
    FSP_PARAMETER_NOT_USED(p_callback_memory);
#endif

    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable the SAU channel and set the instance as not open. Implements @ref spi_api_t::close.
 *
 * @param      p_api_ctrl         Pointer to an opened instance.
 *
 * @retval     FSP_SUCCESS        Channel successfully closed.
 * @retval     FSP_ERR_ASSERTION  The parameter p_api_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN   The channel has not been opened. Open the channel first.
 **********************************************************************************************************************/
fsp_err_t R_SAU_SPI_Close (spi_ctrl_t * const p_api_ctrl)
{
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SAU_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    spi_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Clear the RE and TE bits in SCR. */
    SAU_REG->SCR[p_cfg->channel] = 0;

#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif
    SAU_REG->ST  |= (uint16_t) (1 << p_cfg->channel);
    SAU_REG->SOE &= (uint16_t) ~(1 << p_cfg->channel);
#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculate the register settings required to achieve the desired bitrate.
 *
 * @param[in]  bitrate            bitrate [bps]. For example, 250,000; 500,00; 16,000,000 (max), etc.
 * @param      sclk_div           Pointer to sau_spi_div_setting_t used to configure baudrate settings.
 * @param      sau_unit           Sau unit.
 * @param      channel            Sau channel.
 *
 * @retval     FSP_SUCCESS        Baud rate is set successfully.
 * @retval     FSP_ERR_ASSERTION  Baud rate is not achievable.
 * @note       The application must pause for 1 bit time after the BRR register is loaded before transmitting/receiving
 *             to allow time for the clock to settle.
 **********************************************************************************************************************/
fsp_err_t R_SAU_SPI_CalculateBitrate (uint32_t                bitrate,
                                      sau_spi_div_setting_t * sclk_div,
                                      uint8_t                 sau_unit,
                                      uint8_t                 channel)
{
    uint32_t peripheral_clock = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK);

#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != sclk_div);
    FSP_ASSERT(bitrate);
    if ((0 == sau_unit) && (0 == channel))
    {
        FSP_ASSERT(bitrate <= (peripheral_clock) / SAU_SPI_PSR_MIN_DIV_2);
    }
    else
    {
        FSP_ASSERT(bitrate <= (peripheral_clock) / SAU_SPI_PSR_MIN_DIV_4);
    }

    FSP_ASSERT(bitrate >= (peripheral_clock) / SAU_SPI_SDR_STCLK_MAX_DIV / SAU_SPI_PSR_MAX_DIV);
#else
    FSP_PARAMETER_NOT_USED(sau_unit);
    FSP_PARAMETER_NOT_USED(channel);
#endif
    uint32_t temp_sdr            = 0;
    uint32_t delta_error         = INT32_MAX;
    uint32_t temp_delta_error    = 0;
    uint32_t temp_actual_bitrate = 0;

    for (uint8_t i = 0; i <= R_SAU0_SPS_PRS0_Msk; i++)
    {
        /* Calculate BRR so that the bit rate is the largest possible value less than or equal to the desired
         * bitrate. */
        temp_sdr            = (uint32_t) (((peripheral_clock >> (i + 1)) / bitrate - 1) + 0.5); // NOLINT(readability-magic-numbers)
        temp_actual_bitrate = (peripheral_clock >> (i + 1)) / ((temp_sdr + 1));
        temp_delta_error    = bitrate >=
                              temp_actual_bitrate ? (bitrate - temp_actual_bitrate) : (temp_actual_bitrate - bitrate);
        if ((temp_delta_error < delta_error) && (temp_sdr <= INT8_MAX))
        {
            sclk_div->stclk = (uint8_t) temp_sdr;
            delta_error     = temp_delta_error;
            sclk_div->prs   = i;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SAU_SPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures SAU registers based on the user configuration.
 * @param      p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_sau_spi_hw_config (sau_spi_instance_ctrl_t * const p_ctrl)
{
    spi_cfg_t const        * p_cfg    = p_ctrl->p_cfg;
    sau_spi_extended_cfg_t * p_extend = (sau_spi_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Initialize registers to their reset values. */
    uint16_t smr = SAU_SPI_SMR_INIT_VALUE;
    uint16_t scr = SAU_SPI_SCR_INIT_VALUE;
#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif
    uint16_t so = SAU_REG->SO;
#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif
    p_ctrl->transfer_in_progress = false;

    /* Select the baud rate generator clock divider. */
    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        if (SAU_SPI_OPERATION_CLOCK_CK0 == p_extend->operation_clock)
        {
            SAU_REG->SPS_b.PRS0 = (uint16_t) (p_extend->clk_div.prs & 0x0F);
        }
        else
        {
            SAU_REG->SPS_b.PRS1 = (uint16_t) (p_extend->clk_div.prs & 0x0F);
        }

        smr |= (uint16_t) (p_extend->operation_clock << R_SAU0_SMR_CKS_Pos);
    }

    smr |=
        (uint16_t) ((uint16_t) (p_cfg->operating_mode << R_SAU0_SMR_CCS_Pos) |
                    (uint16_t) (p_extend->transfer_mode << R_SAU0_SMR_MD0_Pos));

    SAU_REG->SMR[p_cfg->channel] = smr;
#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION
    scr |= (uint16_t) (SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION << R_SAU0_SCR_TRXE_Pos) |
           (uint16_t) (p_extend->data_phase << R_SAU0_SCR_DCP1_Pos) |
           (uint16_t) (p_extend->clock_phase << R_SAU0_SCR_DCP_Pos) |
           (uint16_t) (p_cfg->bit_order << R_SAU0_SCR_DIR_Pos);
#endif
#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION
    scr |= (uint16_t) (SAU_SPI_TRANSFER_MODE_RECEPTION << R_SAU0_SCR_TRXE_Pos) |
           (uint16_t) (p_extend->data_phase << R_SAU0_SCR_DCP1_Pos) |
           (uint16_t) (p_extend->clock_phase << R_SAU0_SCR_DCP_Pos) |
           (uint16_t) (p_cfg->bit_order << R_SAU0_SCR_DIR_Pos);
#endif
#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION
    scr |= (uint16_t) (SAU_SPI_TRANSFER_MODE_TRANSMISSION << R_SAU0_SCR_TRXE_Pos) |
           (uint16_t) (p_extend->data_phase << R_SAU0_SCR_DCP1_Pos) |
           (uint16_t) (p_extend->clock_phase << R_SAU0_SCR_DCP_Pos) |
           (uint16_t) (p_cfg->bit_order << R_SAU0_SCR_DIR_Pos);
#endif
    SAU_REG->SCR[p_cfg->channel] = scr;

    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        SAU_REG->SDR[p_cfg->channel] = ((uint16_t) (p_extend->clk_div.stclk << R_SAU0_SDR_STCLK_Pos));
        if (SAU_SPI_CLOCK_PHASE_REVERSE == p_extend->clock_phase)
        {
            so &= (uint16_t) ~(1 << (R_SAU0_SO_CKO_Pos + p_cfg->channel));
        }
        else
        {
            so |= (uint16_t) (1 << (R_SAU0_SO_CKO_Pos + p_cfg->channel));
        }
    }
    else
    {
        SAU_REG->SDR[p_cfg->channel] = 0;
    }

#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION
    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        SAU_REG->SO = so;
    }

#else
    so &= (uint16_t) ~(1 << (p_cfg->channel));
 #if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_ENTER;
 #endif
    SAU_REG->SO   = so;
    SAU_REG->SOE |= (uint16_t) (1 << (p_cfg->channel));
 #if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
 #endif
#endif
    if ((0 == p_extend->sau_unit) && (0 == p_cfg->channel))
    {
        if (SPI_MODE_SLAVE == p_cfg->operating_mode)
        {
            R_PORGA->ISC_b.SSIE00 = 1U;
        }
    }

#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_ENTER;
#endif
    SAU_REG->SS |= (uint16_t) (1 << (p_cfg->channel));
#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

/*******************************************************************************************************************//**
 * Initiates writ or read process. Common routine used by SPI API write or read functions.
 *
 * @param[in]  p_ctrl             Pointer to the control block.
 * @param[in]  p_src              Pointer to data buffer which need to be sent.
 * @param[out] p_dest             Pointer to buffer where received data will be stored.
 * @param[in]  length             Number of data transactions to be performed.
 * @param[in]  bit_width            Invalid for SAU_SPI (Set to SPI_BIT_WIDTH_8_BITS).
 *
 * @retval     FSP_SUCCESS        Operation successfully completed.
 * @retval     FSP_ERR_NOT_OPEN   The channel has not been opened. Open the channel first.
 * @retval     FSP_ERR_ASSERTION  One of the following invalid parameters passed:
 *                                  - Pointer p_ctrl is NULL
 *                                  - length == 0
 * @retval     FSP_ERR_IN_USE       A transfer is already in progress.
 *
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               - @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
static fsp_err_t r_sau_spi_write_read_common (sau_spi_instance_ctrl_t * const p_ctrl,
                                              void const                    * p_src,
                                              void                          * p_dest,
                                              uint32_t const                  length,
                                              spi_bit_width_t const           bit_width)
{
#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SAU_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0 != length);
#endif

    spi_cfg_t const        * p_cfg    = p_ctrl->p_cfg;
    sau_spi_extended_cfg_t * p_extend = (sau_spi_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    FSP_ERROR_RETURN(p_ctrl->transfer_in_progress == false, FSP_ERR_IN_USE);

    if (SPI_BIT_WIDTH_8_BITS == bit_width)
    {
        SAU_REG->SCR[p_cfg->channel] |= R_SAU0_SCR_DLS_Msk;
    }
    else
    {
        SAU_REG->SCR[p_cfg->channel] &= (uint16_t) ~1;
    }

    if (SAU_SPI_TRANSFER_MODE_CONTINUOUS == p_extend->transfer_mode)
    {
        if (1 == length)
        {
            SAU_REG->SMR[p_cfg->channel] &= (uint16_t) ~R_SAU0_SMR_MD0_Msk;
        }
        else
        {
            SAU_REG->SMR[p_cfg->channel] |= (uint16_t) R_SAU0_SMR_MD0_Msk;
        }
    }

    /* Setup the control block. */
    p_ctrl->count    = length;
    p_ctrl->tx_count = 0U;
    p_ctrl->rx_count = 0U;
    p_ctrl->p_src    = (uint8_t *) p_src;
    p_ctrl->p_dest   = (uint8_t *) p_dest;

    /* Enable transmit and receive interrupts. */
    r_sau_spi_start_transfer(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Start transmit data Settings.
 *
 * @param      p_ctrl          Pointer to control structure.
 **********************************************************************************************************************/
static void r_sau_spi_start_transfer (sau_spi_instance_ctrl_t * const p_ctrl)
{
    p_ctrl->transfer_in_progress = true;

#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION
    spi_cfg_t const * p_cfg = p_ctrl->p_cfg;
    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        /* start receive by dummy write */
        SAU_REG->SDR_b[p_cfg->channel].DAT = R_SAU_SDR_DUMMY_DATA;
    }

#else

    /* When transmitting from the TXRXI interrupt, the first byte must be written here because the transmit buffer
     * empty IRQ is disabled. */
    r_sau_spi_transmit(p_ctrl);
#endif
}

#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION || \
    SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION

/*******************************************************************************************************************//**
 * Transmit a single byte of data.
 * @param      p_ctrl          Pointer to the control structure.
 **********************************************************************************************************************/
static void r_sau_spi_transmit (sau_spi_instance_ctrl_t * p_ctrl)
{
    spi_cfg_t const * p_cfg = p_ctrl->p_cfg;
    if (p_ctrl->p_src)
    {
        SAU_REG->SDR_b[p_cfg->channel].DAT = (p_ctrl->p_src[p_ctrl->tx_count]);
    }
    else
    {
        /* start receive by dummy write */
        SAU_REG->SDR_b[p_cfg->channel].DAT = R_SAU_SDR_DUMMY_DATA;
    }

    p_ctrl->tx_count++;
}

#endif

#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION || \
    SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION

/*******************************************************************************************************************//**
 * The receive buffer is read the data register.
 * @param[in]  p_ctrl          pointer to control structure.
 **********************************************************************************************************************/
static void r_sau_spi_receive (sau_spi_instance_ctrl_t * p_ctrl)
{
    spi_cfg_t const * p_cfg = p_ctrl->p_cfg;
    if (p_ctrl->p_dest)
    {
        p_ctrl->p_dest[p_ctrl->rx_count] = (uint8_t) SAU_REG->SDR_b[p_cfg->channel].DAT;
    }
    else
    {
        /* Read the received data but do nothing with it. */
        SAU_REG->SDR_b[p_cfg->channel].DAT;
    }

    p_ctrl->rx_count++;
}

#endif

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to SPI instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sau_spi_call_callback (sau_spi_instance_ctrl_t * p_ctrl, spi_event_t event)
{
    spi_callback_args_t args;

    args.channel   = p_ctrl->p_cfg->channel;
    args.event     = event;
    args.p_context = p_ctrl->p_context;

    p_ctrl->p_callback(&args);
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SAU_SPI Transmit End IRQ.
 *
 * The Transmit End IRQ is enabled after the last byte of data has been transfered.
 *
 **********************************************************************************************************************/
void sau_spi_txrxi_isr (void)
{
    uint8_t                   err_type;
    IRQn_Type                 irq    = R_FSP_CurrentIrqGet();
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    spi_cfg_t const         * p_cfg  = p_ctrl->p_cfg;

    err_type = (uint8_t) (SAU_REG->SSR[p_cfg->channel] & R_SAU0_SSR_OVF_Msk);
    SAU_REG->SIR[p_cfg->channel] = (uint16_t) err_type;

    if (1U == err_type)
    {
        r_sau_spi_call_callback(p_ctrl, SPI_EVENT_ERR_READ_OVERFLOW);
    }
    else
    {
#if (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION)
        r_sau_spi_do_reception(p_ctrl, p_cfg);
#elif (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION)
        r_sau_spi_do_transmission(p_ctrl, p_cfg);
#else
        r_sau_spi_do_transmission_reception(p_ctrl, p_cfg);
#endif
    }
}

#if (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION)
void r_sau_spi_do_reception (sau_spi_instance_ctrl_t * p_ctrl, spi_cfg_t const * p_cfg)
{
    uint16_t smr = SAU_REG->SMR[p_cfg->channel];
    if (smr & (SAU_SPI_TRANSFER_MODE_CONTINUOUS << R_SAU0_SMR_MD0_Pos))
    {
        if (0 == p_ctrl->tx_count)
        {
            SAU_REG->SDR_b[p_cfg->channel].DAT = R_SAU_SDR_DUMMY_DATA;
            p_ctrl->tx_count++;
        }
        else
        {
            r_sau_spi_receive(p_ctrl);
            if (p_ctrl->rx_count < (p_ctrl->count - 1U))
            {
                SAU_REG->SDR_b[p_cfg->channel].DAT = R_SAU_SDR_DUMMY_DATA;
            }
            else if (p_ctrl->rx_count == (p_ctrl->count - 1U))
            {
                smr &= (uint16_t) ~(SAU_SPI_TRANSFER_MODE_CONTINUOUS);
                SAU_REG->SMR[p_cfg->channel] = smr;
            }
            else
            {
                r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
                p_ctrl->transfer_in_progress = false;
            }
        }
    }
    else
    {
        r_sau_spi_receive(p_ctrl);
        if (p_ctrl->rx_count == p_ctrl->count)
        {
            r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
            p_ctrl->transfer_in_progress = false;
        }
        else
        {
            if (SPI_MODE_MASTER == p_cfg->operating_mode)
            {
                SAU_REG->SDR_b[p_cfg->channel].DAT = R_SAU_SDR_DUMMY_DATA;
            }
        }
    }
}

#elif (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION)
void r_sau_spi_do_transmission (sau_spi_instance_ctrl_t * p_ctrl, spi_cfg_t const * p_cfg)
{
    uint16_t smr = SAU_REG->SMR[p_cfg->channel];
    if (p_ctrl->tx_count < p_ctrl->count)
    {
        r_sau_spi_transmit(p_ctrl);
    }
    else if (smr & (SAU_SPI_TRANSFER_MODE_CONTINUOUS << R_SAU0_SMR_MD0_Pos))
    {
        smr &= (uint16_t) ~(SAU_SPI_TRANSFER_MODE_CONTINUOUS);
        SAU_REG->SMR[p_cfg->channel] = smr;
    }
    else
    {
        r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
        p_ctrl->transfer_in_progress = false;
    }
}

#else
void r_sau_spi_do_transmission_reception (sau_spi_instance_ctrl_t * p_ctrl, spi_cfg_t const * p_cfg)
{
    uint16_t smr = SAU_REG->SMR[p_cfg->channel];
    if (smr & (SAU_SPI_TRANSFER_MODE_CONTINUOUS << R_SAU0_SMR_MD0_Pos))
    {
        if (1U < p_ctrl->tx_count)
        {
            r_sau_spi_receive(p_ctrl);
        }
    }
    else
    {
        r_sau_spi_receive(p_ctrl);
    }

    if (p_ctrl->tx_count < p_ctrl->count)
    {
        r_sau_spi_transmit(p_ctrl);
    }
    else if (smr & (SAU_SPI_TRANSFER_MODE_CONTINUOUS << R_SAU0_SMR_MD0_Pos))
    {
        /* 2nd to last byte */
        smr &= (uint16_t) ~(SAU_SPI_TRANSFER_MODE_CONTINUOUS);
        SAU_REG->SMR[p_cfg->channel] = smr;
    }
    else
    {
        /* last byte */
        r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
        p_ctrl->transfer_in_progress = false;
    }
}

#endif
