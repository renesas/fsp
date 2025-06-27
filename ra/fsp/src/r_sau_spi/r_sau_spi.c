/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_sau_spi.h"
#include "r_sau_spi_cfg.h"
#if SAU_SPI_CFG_DTC_SUPPORT_ENABLE
 #include "r_dtc.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define R_SAU0_SCR_DCP1_Pos                               (13U)
#define SAU_SPI_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL <<              \
                                                            TRANSFER_SETTINGS_MODE_BITS) |       \
                                                           (TRANSFER_CHAIN_MODE_EACH <<          \
                                                            TRANSFER_SETTINGS_CHAIN_MODE_BITS) | \
                                                           (TRANSFER_SIZE_1_BYTE <<              \
                                                            TRANSFER_SETTINGS_SIZE_BITS) |       \
                                                           (TRANSFER_ADDR_MODE_FIXED <<          \
                                                            TRANSFER_SETTINGS_SRC_ADDR_BITS) |   \
                                                           (TRANSFER_IRQ_END <<                  \
                                                            TRANSFER_SETTINGS_IRQ_BITS) |        \
                                                           (TRANSFER_ADDR_MODE_INCREMENTED <<    \
                                                            TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SAU_SPI_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL <<              \
                                                            TRANSFER_SETTINGS_MODE_BITS) |       \
                                                           (TRANSFER_CHAIN_MODE_DISABLED <<      \
                                                            TRANSFER_SETTINGS_CHAIN_MODE_BITS) | \
                                                           (TRANSFER_SIZE_1_BYTE <<              \
                                                            TRANSFER_SETTINGS_SIZE_BITS) |       \
                                                           (TRANSFER_ADDR_MODE_FIXED <<          \
                                                            TRANSFER_SETTINGS_SRC_ADDR_BITS) |   \
                                                           (TRANSFER_IRQ_END <<                  \
                                                            TRANSFER_SETTINGS_IRQ_BITS) |        \
                                                           (TRANSFER_ADDR_MODE_INCREMENTED <<    \
                                                            TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SAU_SPI_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL <<              \
                                                            TRANSFER_SETTINGS_MODE_BITS) |       \
                                                           (TRANSFER_CHAIN_MODE_DISABLED <<      \
                                                            TRANSFER_SETTINGS_CHAIN_MODE_BITS) | \
                                                           (TRANSFER_SIZE_1_BYTE <<              \
                                                            TRANSFER_SETTINGS_SIZE_BITS) |       \
                                                           (TRANSFER_ADDR_MODE_INCREMENTED <<    \
                                                            TRANSFER_SETTINGS_SRC_ADDR_BITS) |   \
                                                           (TRANSFER_IRQ_END <<                  \
                                                            TRANSFER_SETTINGS_IRQ_BITS) |        \
                                                           (TRANSFER_ADDR_MODE_FIXED <<          \
                                                            TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SAU_REG_SIZE                                      (R_SAU1_BASE - R_SAU0_BASE)
#define SAU_SPI_SMR_INIT_VALUE                            (0x0020U)
#define SAU_SPI_SCR_INIT_VALUE                            (0x0007U | \
                                                           (SAU_SPI_TRANSFER_OPERATION_MODE << R_SAU0_SCR_TRXE_Pos))
#define SAU0_SPS_REG_INIT                                 ((BSP_CFG_SAU_CK01_DIV << R_SAU0_SPS_PRS1_Pos) | \
                                                           BSP_CFG_SAU_CK00_DIV)
#define SAU1_SPS_REG_INIT                                 ((BSP_CFG_SAU_CK11_DIV << R_SAU0_SPS_PRS1_Pos) | \
                                                           BSP_CFG_SAU_CK10_DIV)

#define SAU_SPI_PSR_MIN_DIV_2                             (2U)
#define SAU_SPI_PSR_MIN_DIV_4                             (4U)
#define SAU_SPI_SDR_STCLK_MAX_DIV                         (256U)
#define SAU_SPI_PSR_MAX_DIV                               (32768U)
#define R_SAU_SDR_DUMMY_DATA                              (0xFFU)
#define SAU_SPI_STCLK_MAX                                 (127)

#if 0 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE /* Only SPI00 used (Unit 0 Channel 0) */
 #define SAU_SPI_PRV_CHANNEL                              (0)
 #define SAU_SPI_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_SPS_REG_INIT                                 (SAU0_SPS_REG_INIT)
#elif 1 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE /* Only SPI01 used (Unit 0 Channel 1) */
 #define SAU_SPI_PRV_CHANNEL                              (1)
 #define SAU_SPI_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_SPS_REG_INIT                                 (SAU0_SPS_REG_INIT)
#elif 10 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE /* Only SPI10 used (Unit 0 Channel 2) */
 #define SAU_SPI_PRV_CHANNEL                              (2)
 #define SAU_SPI_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_SPS_REG_INIT                                 (SAU0_SPS_REG_INIT)
#elif 11 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE /* Only SPI11 used (Unit 0 Channel 3) */
 #define SAU_SPI_PRV_CHANNEL                              (3)
 #define SAU_SPI_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_SPS_REG_INIT                                 (SAU0_SPS_REG_INIT)
#elif 20 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE /* Only SPI20 used (Unit 1 Channel 0) */
 #define SAU_SPI_PRV_CHANNEL                              (0)
 #define SAU_SPI_PRV_UNIT                                 (1)
 #define SAU_REG                                          (R_SAU1)
 #define SAU_SPS_REG_INIT                                 (SAU1_SPS_REG_INIT)
#elif 21 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE /* Only SPI21 used (Unit 1 Channel 1) */
 #define SAU_SPI_PRV_CHANNEL                              (1)
 #define SAU_SPI_PRV_UNIT                                 (1)
 #define SAU_REG                                          (R_SAU1)
 #define SAU_SPS_REG_INIT                                 (SAU1_SPS_REG_INIT)
#endif

#if -1 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE /* Single channel configuration disabled. */
 #define SAU_REG                                          (p_ctrl->p_reg)
 #define SAU_SPI_PRV_UNIT                                 (p_extend->sau_unit)
 #define SAU_SPI_PRV_CHANNEL_DECLARATION                  uint8_t channel = p_ctrl->p_cfg->channel
 #define SAU_SPI_PRV_CHANNEL                              (channel)
 #define SAU_SPS_REG_INIT                                 (SAU_SPI_PRV_UNIT ? SAU1_SPS_REG_INIT : SAU0_SPS_REG_INIT)
#else
 #define SAU_SPI_PRV_CHANNEL_DECLARATION
#endif

/** "SAU" in ASCII, used to determine if channel is open. */
#define SAU_SPI_OPEN    (0x53415553ULL)

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

#if SAU_SPI_CFG_DTC_SUPPORT_ENABLE == 1
 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION || \
    SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION

/* constant used as the source location for the DTC dummy write */
static const uint8_t g_dummy_write_data_for_read_op = R_SAU_SDR_DUMMY_DATA;
 #endif
static fsp_err_t r_sau_spi_transfer_config(sau_spi_instance_ctrl_t * const p_ctrl);
static void      r_sau_spi_reconfigure_for_transfer(sau_spi_instance_ctrl_t * const p_ctrl, uint8_t const length);

 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION
static uint8_t dummy_rx;
 #endif
#endif
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
static void r_sau_spi_do_transmission(sau_spi_instance_ctrl_t * p_ctrl);

#elif (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION)
static void r_sau_spi_do_reception(sau_spi_instance_ctrl_t * p_ctrl);

#else
static void r_sau_spi_do_transmission_reception(sau_spi_instance_ctrl_t * p_ctrl);

#endif
#if SAU_SPI_CFG_MULTIPLE_SLAVE_COMPATIBILITY_MODE_ENABLE
static void r_sau_spi_reset_pin(sau_spi_instance_ctrl_t * p_ctrl, bool reset);

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

#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SAU_SPI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(p_cfg->tei_irq >= 0);
#endif
    sau_spi_extended_cfg_t const * const p_extend = (sau_spi_extended_cfg_t *) p_cfg->p_extend;
#if -1 == SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE
    p_ctrl->p_reg = ((R_SAU0_Type *) (R_SAU0_BASE + (SAU_REG_SIZE * SAU_SPI_PRV_UNIT)));
#endif
    p_ctrl->p_cfg = p_cfg;

    p_ctrl->p_callback           = p_cfg->p_callback;
    p_ctrl->p_context            = p_cfg->p_context;
    p_ctrl->transfer_in_progress = false;

#if SAU_SPI_CFG_DTC_SUPPORT_ENABLE == 1

    /* Open the SAU SPI transfer interface if available. */
    err = r_sau_spi_transfer_config(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Enable Clock for the SAU Channel. */
    R_BSP_MODULE_START(FSP_IP_SAU, SAU_SPI_PRV_UNIT);

    /* Write user configuration to registers. */
    r_sau_spi_hw_config(p_ctrl);

    /* Enable required interrupts. */
    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->tei_ipl, p_ctrl);

    p_ctrl->open = SAU_SPI_OPEN;

    /* Set SCK pin to input in slave mode by clearing PDR. */
    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        R_BSP_PinAccessEnable();
        R_BSP_PinCfg(p_extend->sck_pin_settings.pin,
                     (uint32_t) (p_extend->sck_pin_settings.cfg & ~R_PFS_PORT_PIN_PmnPFS_PDR_Msk));
        R_BSP_PinAccessDisable();
    }

#if SAU_SPI_CFG_MULTIPLE_SLAVE_COMPATIBILITY_MODE_ENABLE
    r_sau_spi_reset_pin(p_ctrl, true);
#endif

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
 * @param[in]  bit_width            Data frame length (Set to SPI_BIT_WIDTH_7_BITS or SPI_BIT_WIDTH_8_BITS).
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
#if SAU_SPI_TRANSFER_OPERATION_MODE != SAU_SPI_TRANSFER_MODE_TRANSMISSION
 #if SAU_SPI_CFG_PARAM_CHECKING_ENABLE

    /* Check the destination, should not be NULL. */
    FSP_ASSERT(NULL != p_dest);
 #endif
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

    return r_sau_spi_write_read_common(p_ctrl, NULL, p_dest, length, bit_width);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(length);
    FSP_PARAMETER_NOT_USED(bit_width);

    return FSP_ERR_UNSUPPORTED;
#endif
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
 * @param[in]  bit_width            Data frame length (Set to SPI_BIT_WIDTH_7_BITS or SPI_BIT_WIDTH_8_BITS).
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
#if SAU_SPI_TRANSFER_OPERATION_MODE != SAU_SPI_TRANSFER_MODE_RECEPTION
 #if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_src);
 #endif
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;
 #if SAU_SPI_CFG_MULTIPLE_SLAVE_COMPATIBILITY_MODE_ENABLE
    r_sau_spi_reset_pin(p_ctrl, false);
 #endif

    return r_sau_spi_write_read_common(p_ctrl, p_src, NULL, length, bit_width);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(length);
    FSP_PARAMETER_NOT_USED(bit_width);

    return FSP_ERR_UNSUPPORTED;
#endif
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
 * @param[in]  bit_width            Data frame length (Set to SPI_BIT_WIDTH_7_BITS or SPI_BIT_WIDTH_8_BITS).
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
#if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION
 #if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
 #endif
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

 #if SAU_SPI_CFG_MULTIPLE_SLAVE_COMPATIBILITY_MODE_ENABLE
    r_sau_spi_reset_pin(p_ctrl, false);
 #endif

    return r_sau_spi_write_read_common(p_ctrl, p_src, p_dest, length, bit_width);
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(length);
    FSP_PARAMETER_NOT_USED(bit_width);

    return FSP_ERR_UNSUPPORTED;
#endif
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
                                 void * const                p_context,
                                 spi_callback_args_t * const p_callback_memory)
{
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) p_api_ctrl;

#if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
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

    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    /* Clear the RE and TE bits in SCR. */
    SAU_REG->SCR[SAU_SPI_PRV_CHANNEL] = 0;

#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif
    SAU_REG->ST  |= (uint16_t) (1 << SAU_SPI_PRV_CHANNEL);
    SAU_REG->SOE &= (uint16_t) ~(1 << SAU_SPI_PRV_CHANNEL);
#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    p_ctrl->open = 0U;

#if SAU_SPI_CFG_DTC_SUPPORT_ENABLE
    p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculate the register settings required to achieve the desired bitrate.
 *
 * @note This function calculates the bitrate settings with both operation clocks CK0 and CK1, then selects the operation
 * clock and register setting combination that would produce the lowest error.
 *
 * @param[in]  bitrate            bitrate [bps]. For example, 250,000; 500,00; 16,000,000 (max), etc.
 * @param[out] sclk_div           Pointer to sau_spi_div_setting_t used to configure baudrate settings.
 * @param      sau_unit           SAU unit.
 * @param      channel            SAU channel.
 *
 * @retval     FSP_SUCCESS        Bitrate is calculated successfully.
 * @retval     FSP_ERR_ASSERTION  Bitrate is not achievable or not valid for the selected unit/channel.
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
        FSP_ASSERT(bitrate <= peripheral_clock / SAU_SPI_PSR_MIN_DIV_2);
    }
    else
    {
        FSP_ASSERT(bitrate <= peripheral_clock / SAU_SPI_PSR_MIN_DIV_4);
    }

    FSP_ASSERT(bitrate >= peripheral_clock / SAU_SPI_SDR_STCLK_MAX_DIV / SAU_SPI_PSR_MAX_DIV);
#else
    FSP_PARAMETER_NOT_USED(channel);
#endif
    uint32_t best_delta_error = UINT32_MAX;

#if SAU_SPI_CFG_SINGLE_CHANNEL_ENABLE != -1
    const uint32_t sps = SAU_SPS_REG_INIT;
    FSP_PARAMETER_NOT_USED(sau_unit);
#else
    const uint32_t sps = sau_unit ? SAU1_SPS_REG_INIT : SAU0_SPS_REG_INIT;
#endif

    /* Calculate settings twice, once for CK0 and once for CK1, selecting the result with the lowest error */
    for (uint8_t prs_shift = 0; prs_shift <= R_SAU0_SPS_PRS1_Pos; prs_shift += R_SAU0_SPS_PRS1_Pos)
    {
        uint8_t prs = (sps >> prs_shift) & R_SAU0_SPS_PRS0_Msk;

        /* To get the stclk divider calculate the divisor to apply to ICLK. There's a built in div/2. */
        const uint32_t divisor = bitrate << (prs + 1);

        /* Calculate stclk register value: STCLK = (f_mck / (2*bitrate)) - 1 */
        const uint32_t stclk = (peripheral_clock + (divisor >> 1)) / divisor - 1;

        /* Get the actual bitrate given the current settings.
         * peripheral_clock / 2^prs / (2 * (stclk + 1)) */
        const uint32_t actual_bitrate = (peripheral_clock >> (prs + 1)) / (stclk + 1);
        uint32_t       delta_error    = bitrate > actual_bitrate ? bitrate - actual_bitrate : actual_bitrate - bitrate;

        /* Keep settings which are valid and provide the lowest error. */
        if ((stclk <= SAU_SPI_STCLK_MAX) && (delta_error < best_delta_error))
        {
            best_delta_error          = delta_error;
            sclk_div->stclk           = (uint8_t) stclk;
            sclk_div->operation_clock = (sau_spi_operation_clock_t) (prs_shift == R_SAU0_SPS_PRS1_Pos);
        }
    }

    /* Return an error if no valid STCLK setting was found with either operation clock */
    FSP_ERROR_RETURN(best_delta_error != UINT32_MAX, FSP_ERR_INVALID_ARGUMENT);

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
    R_SAU0_Type            * p_reg    = SAU_REG;

    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    /* Initialize registers to their reset values. */
    uint16_t smr = SAU_SPI_SMR_INIT_VALUE;
    uint16_t scr = SAU_SPI_SCR_INIT_VALUE;

    /* Write settings that are common to master and slave mode. */
#if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    smr |= ((uint16_t) (p_cfg->operating_mode << R_SAU0_SMR_CCS_Pos) |
            (uint16_t) (p_extend->transfer_mode << R_SAU0_SMR_MD0_Pos));
#else
    smr |= (uint16_t) (p_cfg->operating_mode << R_SAU0_SMR_CCS_Pos);
#endif
    scr |= (uint16_t) (p_extend->data_phase << R_SAU0_SCR_DCP1_Pos) |
           (uint16_t) (p_extend->clock_phase << R_SAU0_SCR_DCP_Pos) |
           (uint16_t) (p_cfg->bit_order << R_SAU0_SCR_DIR_Pos);

#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE

    /* Enter critical section when modifying registers that are shared between channels (SPS, SS, SO, SOE). */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif

    uint16_t so  = p_reg->SO;
    uint16_t sdr = 0;

    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        /* Write settings that are only used in master mode. */
        p_reg->SPS = SAU_SPS_REG_INIT;

        smr |= (uint16_t) (p_extend->clk_div.operation_clock << R_SAU0_SMR_CKS_Pos);
        sdr  = (uint16_t) (p_extend->clk_div.stclk << R_SAU0_SDR_STCLK_Pos);

        if (SAU_SPI_CLOCK_PHASE_REVERSE == p_extend->clock_phase)
        {
            so &= (uint16_t) ~(1 << (R_SAU0_SO_CKO_Pos + SAU_SPI_PRV_CHANNEL));
        }
        else
        {
            so |= (uint16_t) (1 << (R_SAU0_SO_CKO_Pos + SAU_SPI_PRV_CHANNEL));
        }
    }
    else
    {
        /* Write settings that are only used in slave mode. */
        if ((0 == SAU_SPI_PRV_UNIT) && (0 == SAU_SPI_PRV_CHANNEL))
        {
            /* Enable IRQ0 pin as an external interrupt for SAU unit 0 channel 0. */
            R_PORGA->ISC_b.SSIE00 = 1U;
        }
    }

#if SAU_SPI_TRANSFER_OPERATION_MODE != SAU_SPI_TRANSFER_MODE_RECEPTION

    /* Set initial serial output data to 0 if transmit is enabled. */
    so &= (uint16_t) ~(1 << SAU_SPI_PRV_CHANNEL);

    /* Only enable serial output if transmit is enabled. */
    p_reg->SOE |= (uint16_t) (1 << (SAU_SPI_PRV_CHANNEL));
#endif

    p_reg->SMR[SAU_SPI_PRV_CHANNEL] = smr;
    p_reg->SCR[SAU_SPI_PRV_CHANNEL] = scr;
    p_reg->SDR[SAU_SPI_PRV_CHANNEL] = sdr;
    p_reg->SO = so;

    SAU_REG->SS = (uint16_t) (1 << (SAU_SPI_PRV_CHANNEL));

#if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

#if SAU_SPI_CFG_DTC_SUPPORT_ENABLE == 1

/*******************************************************************************************************************//**
 * Configures SAU SPI related transfer drivers (if enabled).
 *
 * @param[in]     p_ctrl                    Pointer to the control structure.
 *
 * @retval        FSP_SUCCESS               Operation successfully completed.
 * @retval        FSP_ERR_ASSERTION         One of the following invalid parameters passed:
 *                                          - Pointer p_cfg is NULL
 *                                          - Interrupt is not enabled
 * @retval        FSP_ERR_INVALID_ARGUMENT  DTC is used for data transmission but not used for data reception or
 *                                          vice versa.
 **********************************************************************************************************************/
static fsp_err_t r_sau_spi_transfer_config (sau_spi_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t               err   = FSP_SUCCESS;
    spi_cfg_t const * const p_cfg = p_ctrl->p_cfg;

    /* Set default transfer info and open receive transfer module, if enabled. */
 #if SAU_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg->p_transfer_tx->p_api);
    FSP_ASSERT(NULL != p_cfg->p_transfer_tx->p_ctrl);
    FSP_ASSERT(NULL != p_cfg->p_transfer_tx->p_cfg);
 #endif
 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION
    transfer_info_t * p_info_rx = &(p_cfg->p_transfer_tx->p_cfg->p_info[0]);
    transfer_info_t * p_info_tx = &(p_cfg->p_transfer_tx->p_cfg->p_info[1]);

    /* Set the initial configuration for the rx transfer instance. */
    p_info_rx->transfer_settings_word = SAU_SPI_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS;
    p_info_rx->p_src = (void *) (&(SAU_REG->SDR[p_cfg->channel]));

    /* Set the initial configuration for the tx transfer instance. */
    p_info_tx->transfer_settings_word = SAU_SPI_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;
    p_info_tx->p_dest                 = (void *) (&(SAU_REG->SDR[p_cfg->channel]));
 #endif
 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION
    transfer_info_t * p_info_tx = &(p_cfg->p_transfer_tx->p_cfg->p_info[1]);

    /* Set the initial configuration for the tx transfer instance. */
    p_info_tx->transfer_settings_word = SAU_SPI_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;
    p_info_tx->p_dest                 = (void *) (&(SAU_REG->SDR[p_cfg->channel]));
 #endif
 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION
    transfer_info_t * p_info_rx = &(p_cfg->p_transfer_tx->p_cfg->p_info[0]);
    transfer_info_t * p_info_tx = &(p_cfg->p_transfer_tx->p_cfg->p_info[1]);
    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        p_info_rx->transfer_settings_word = SAU_SPI_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS;
        p_info_rx->p_src = (void *) (&(SAU_REG->SDR[p_cfg->channel]));

        /* Set the initial configuration for the tx transfer instance. */
        p_info_tx->transfer_settings_word = SAU_SPI_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;
        p_info_tx->p_dest                 = (void *) (&(SAU_REG->SDR[p_cfg->channel]));
    }
    else
    {
        /* Set the initial configuration for the tx transfer instance. */
        p_info_tx->transfer_settings_word = SAU_SPI_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS;
        p_info_tx->p_src = (void *) (&(SAU_REG->SDR[p_cfg->channel]));
    }
 #endif
    err = p_cfg->p_transfer_tx->p_api->open(p_cfg->p_transfer_tx->p_ctrl, p_cfg->p_transfer_tx->p_cfg);

    return err;
}

/******************************************************************************************************************//**
 * Reconfigure the address mode for transfer interface
 *
 * @param[in]  p_ctrl     Pointer to the control structure.
 * @param[in]  p_cfg      Pointer to a configuration structure.
 * @param[in]  length     Number of data already transferred.
 **********************************************************************************************************************/
static void r_sau_spi_reconfigure_for_transfer (sau_spi_instance_ctrl_t * const p_ctrl, uint8_t const length)
{
    spi_cfg_t const * const p_cfg = p_ctrl->p_cfg;

    transfer_instance_t const * p_transfer = p_cfg->p_transfer_tx;
 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION
    transfer_info_t * p_info_tx = &(p_transfer->p_cfg->p_info[1]);
    p_info_tx->length                 = (uint16_t) (p_ctrl->count - length);
    p_info_tx->p_src                  = p_ctrl->p_src + length;
    p_info_tx->transfer_settings_word = SAU_SPI_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;
    p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info_tx);
 #endif
 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    transfer_info_t * p_info_rx = &(p_transfer->p_cfg->p_info[0]);
    transfer_info_t * p_info_tx = &(p_transfer->p_cfg->p_info[1]);
    p_info_tx->length = (uint16_t) (p_ctrl->count - length);

    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        p_info_rx->p_dest                 = p_ctrl->p_dest;
        p_info_tx->p_src                  = (void *) &g_dummy_write_data_for_read_op;
        p_info_tx->p_dest                 = (void *) &(SAU_REG->SDR[SAU_SPI_PRV_CHANNEL]);
        p_info_tx->transfer_settings_word = SAU_SPI_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;
        p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info_rx);
    }
    else
    {
        /* Configure the tx transfer instance. */
        p_info_tx->p_src = (void *) &(SAU_REG->SDR[SAU_SPI_PRV_CHANNEL]);
        p_info_tx->transfer_settings_word = SAU_SPI_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS;
        p_info_tx->p_dest                 = p_ctrl->p_dest;

        /* Enable the transfer instance. */
        p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info_tx);
    }
 #endif
 #if SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION_RECEPTION
    transfer_info_t * p_info_rx = &(p_transfer->p_cfg->p_info[0]);
    transfer_info_t * p_info_tx = &(p_transfer->p_cfg->p_info[1]);
    p_info_tx->length = (uint16_t) (p_ctrl->count - length);
    if (NULL == p_ctrl->p_dest)
    {
        p_info_rx->p_dest = &dummy_rx;
        p_info_rx->transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
        p_info_tx->p_src = p_ctrl->p_src + length;
    }
    else if (NULL == p_ctrl->p_src)
    {
        p_info_rx->p_dest                 = p_ctrl->p_dest;
        p_info_rx->transfer_settings_word = SAU_SPI_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS;
        p_info_tx->p_src = (void *) &g_dummy_write_data_for_read_op;
    }
    else
    {
        p_info_rx->p_dest                 = p_ctrl->p_dest;
        p_info_rx->transfer_settings_word = SAU_SPI_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS;
        p_info_tx->p_src = p_ctrl->p_src + length;
    }
    p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info_rx);
 #endif
    p_ctrl->activation_on_tei = true;
}

#endif

/*******************************************************************************************************************//**
 * Initiates write or read process. Common routine used by SPI API write or read functions.
 *
 * @param[in]  p_ctrl             Pointer to the control block.
 * @param[in]  p_src              Pointer to data buffer which need to be sent.
 * @param[out] p_dest             Pointer to buffer where received data will be stored.
 * @param[in]  length             Number of data transactions to be performed.
 * @param[in]  bit_width          Data frame length (Set to SPI_BIT_WIDTH_7_BITS or SPI_BIT_WIDTH_8_BITS).
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
    FSP_ERROR_RETURN((SPI_BIT_WIDTH_8_BITS == bit_width) || (SPI_BIT_WIDTH_7_BITS == bit_width), FSP_ERR_UNSUPPORTED);

 #if SAU_SPI_CFG_DTC_SUPPORT_ENABLE

    /* DTC on RX could actually receive 65535+3 = 65538 bytes as 3 bytes are handled separately.
     * Forcing to 65535 to keep TX and RX uniform with respect to max transaction length via DTC.
     */
    FSP_ASSERT(length <= UINT16_MAX);
 #endif
#endif

    FSP_ERROR_RETURN(p_ctrl->transfer_in_progress == false, FSP_ERR_IN_USE);

    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    /* Writing to SCR is prohibited while the channel is enabled. If the bit width is changed, disable communication
     * before writing to SCR. See in hardware manual: SAU > Register Descriptions > SCRm0 */
    SAU_REG->ST = (uint16_t) (1 << SAU_SPI_PRV_CHANNEL);

    /* Bit width is configured in SCR::DLS[1:0]:
     * - 7bit: 0b10
     * - 8bit: 0b11
     */
    uint16_t tmp = SAU_REG->SCR[SAU_SPI_PRV_CHANNEL];
    SAU_REG->SCR[SAU_SPI_PRV_CHANNEL] = (uint16_t) (tmp & (uint16_t) ~1) | (SPI_BIT_WIDTH_8_BITS == bit_width);

    SAU_REG->SS = (uint16_t) (1 << SAU_SPI_PRV_CHANNEL);
#if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    sau_spi_extended_cfg_t * p_extend = (sau_spi_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    tmp = SAU_REG->SMR[SAU_SPI_PRV_CHANNEL];
    if (SAU_SPI_TRANSFER_MODE_CONTINUOUS == p_extend->transfer_mode)
    {
        tmp &= (uint16_t) ~R_SAU0_SMR_MD0_Msk;

        /* Continuous mode can be used only when length > 1. When DTC is enabled, the length needs to be greater than 2. */
        if (2 < length)
        {
            tmp |= (uint16_t) R_SAU0_SMR_MD0_Msk;
        }

        SAU_REG->SMR[SAU_SPI_PRV_CHANNEL] = tmp;
    }
#endif

    /* Setup the control block. */
    p_ctrl->count    = length;
    p_ctrl->tx_count = 0U;
    p_ctrl->rx_count = 0U;
    p_ctrl->p_src    = (uint8_t *) p_src;
    p_ctrl->p_dest   = (uint8_t *) p_dest;
#if SAU_SPI_CFG_DTC_SUPPORT_ENABLE == 1
    p_ctrl->activation_on_tei = false;
 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    if ((1 < length) && !(tmp & (SAU_SPI_TRANSFER_MODE_CONTINUOUS << R_SAU0_SMR_MD0_Pos)))
 #else
    if (1 < length)
 #endif
    {
        r_sau_spi_reconfigure_for_transfer(p_ctrl, 1);
    }
#endif

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

    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    spi_cfg_t const * p_cfg = p_ctrl->p_cfg;
    if (SPI_MODE_MASTER == p_cfg->operating_mode)
    {
        /* start receive by dummy write */
        SAU_REG->SDR[SAU_SPI_PRV_CHANNEL] = R_SAU_SDR_DUMMY_DATA;
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
    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    uint16_t dat = p_ctrl->p_src ? p_ctrl->p_src[p_ctrl->tx_count] : R_SAU_SDR_DUMMY_DATA;
    SAU_REG->SDR[SAU_SPI_PRV_CHANNEL] = dat;

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
    uint8_t           dat   = (uint8_t) (SAU_REG->SDR[p_cfg->channel] & R_SAU_SDR_DUMMY_DATA);
    if (p_ctrl->p_dest)
    {
        p_ctrl->p_dest[p_ctrl->rx_count] = dat;
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
#if SAU_SPI_CFG_MULTIPLE_SLAVE_COMPATIBILITY_MODE_ENABLE
    r_sau_spi_reset_pin(p_ctrl, true);
#endif
}

/*******************************************************************************************************************//**
 * This function is the ISR handler for R_SAU_SPI Transmit End IRQ.
 *
 * The Transmit End IRQ is enabled after the last byte of data has been transferred.
 *
 **********************************************************************************************************************/
void sau_spi_txrxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type                 irq    = R_FSP_CurrentIrqGet();
    sau_spi_instance_ctrl_t * p_ctrl = (sau_spi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    uint16_t err_type = SAU_REG->SSR[SAU_SPI_PRV_CHANNEL] & R_SAU0_SSR_OVF_Msk;
    if (err_type)
    {
        SAU_REG->SIR[SAU_SPI_PRV_CHANNEL] = err_type;
        r_sau_spi_call_callback(p_ctrl, SPI_EVENT_ERR_READ_OVERFLOW);
    }
    else
    {
#if (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION)
        r_sau_spi_do_reception(p_ctrl);
#elif (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION)
        r_sau_spi_do_transmission(p_ctrl);
#else
        r_sau_spi_do_transmission_reception(p_ctrl);
#endif
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#if (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_RECEPTION)
static void r_sau_spi_do_reception (sau_spi_instance_ctrl_t * p_ctrl)
{
    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;
 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    uint16_t smr                 = SAU_REG->SMR[SAU_SPI_PRV_CHANNEL];
    uint8_t  continuous_transfer = smr & R_SAU0_SMR_MD0_Msk;
 #endif
 #if SAU_SPI_CFG_DTC_SUPPORT_ENABLE
    if (true == p_ctrl->activation_on_tei)
    {
        p_ctrl->activation_on_tei = false;
  #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
        p_ctrl->rx_count = p_ctrl->count - 1 - continuous_transfer;
  #else
        p_ctrl->rx_count = p_ctrl->count - 1;
  #endif
        p_ctrl->tx_count = p_ctrl->count;

        return;
    }
 #endif
 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    if (continuous_transfer)
    {
        if (0 == p_ctrl->tx_count)
        {
  #if SAU_SPI_CFG_DTC_SUPPORT_ENABLE
            r_sau_spi_reconfigure_for_transfer(p_ctrl, 2);
  #endif
            SAU_REG->SDR_b[SAU_SPI_PRV_CHANNEL].DAT = R_SAU_SDR_DUMMY_DATA;
            p_ctrl->tx_count++;
        }
        else
        {
            r_sau_spi_receive(p_ctrl);
            if (p_ctrl->rx_count < (p_ctrl->count - 1U))
            {
                SAU_REG->SDR[SAU_SPI_PRV_CHANNEL] = R_SAU_SDR_DUMMY_DATA;
            }
            else if (p_ctrl->rx_count == (p_ctrl->count - 1U))
            {
                smr &= (uint16_t) ~SAU_SPI_TRANSFER_MODE_CONTINUOUS;
                SAU_REG->SMR[SAU_SPI_PRV_CHANNEL] = smr;
            }
            else
            {
                r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
                p_ctrl->transfer_in_progress = false;
            }
        }
    }
    else
 #endif
    {
        r_sau_spi_receive(p_ctrl);
        if (p_ctrl->rx_count == p_ctrl->count)
        {
            r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
            p_ctrl->transfer_in_progress = false;
        }
        else
        {
            if (SPI_MODE_MASTER == p_ctrl->p_cfg->operating_mode)
            {
                SAU_REG->SDR[SAU_SPI_PRV_CHANNEL] = R_SAU_SDR_DUMMY_DATA;
            }
        }
    }
}

#elif (SAU_SPI_TRANSFER_OPERATION_MODE == SAU_SPI_TRANSFER_MODE_TRANSMISSION)
static void r_sau_spi_do_transmission (sau_spi_instance_ctrl_t * p_ctrl)
{
 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE

    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    uint16_t smr                 = SAU_REG->SMR[SAU_SPI_PRV_CHANNEL];
    uint8_t  continuous_transfer = smr & R_SAU0_SMR_MD0_Msk;
 #endif
 #if SAU_SPI_CFG_DTC_SUPPORT_ENABLE
    if (true == p_ctrl->activation_on_tei)
    {
        p_ctrl->activation_on_tei = false;
        p_ctrl->tx_count          = p_ctrl->count;

        return;
    }

  #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    if (continuous_transfer)
    {
        if (1U == p_ctrl->tx_count)
        {
            r_sau_spi_reconfigure_for_transfer(p_ctrl, 2);
        }
    }
  #endif
 #endif
    if (p_ctrl->tx_count < p_ctrl->count)
    {
        r_sau_spi_transmit(p_ctrl);
    }

 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    else if (continuous_transfer)
    {
        smr &= (uint16_t) ~SAU_SPI_TRANSFER_MODE_CONTINUOUS;
        SAU_REG->SMR[SAU_SPI_PRV_CHANNEL] = smr;
    }
 #endif
    else
    {
        r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
        p_ctrl->transfer_in_progress = false;
    }
}

#else
static void r_sau_spi_do_transmission_reception (sau_spi_instance_ctrl_t * p_ctrl)
{
 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE

    /* If single channel is disabled, then save the channel number on the stack. */
    SAU_SPI_PRV_CHANNEL_DECLARATION;

    uint16_t smr                 = SAU_REG->SMR[SAU_SPI_PRV_CHANNEL];
    uint8_t  continuous_transfer = smr & R_SAU0_SMR_MD0_Msk;
 #endif
 #if SAU_SPI_CFG_DTC_SUPPORT_ENABLE
    if (true == p_ctrl->activation_on_tei)
    {
        p_ctrl->activation_on_tei = false;
  #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
        p_ctrl->rx_count = p_ctrl->count - 1 - continuous_transfer;
  #else
        p_ctrl->rx_count = p_ctrl->count - 1;
  #endif
        p_ctrl->tx_count = p_ctrl->count;

        return;
    }
 #endif
 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    if (continuous_transfer)
    {
        if (1U < p_ctrl->tx_count)
        {
            r_sau_spi_receive(p_ctrl);
        }

  #if SAU_SPI_CFG_DTC_SUPPORT_ENABLE
        else
        {
            r_sau_spi_reconfigure_for_transfer(p_ctrl, 2);
        }
  #endif
    }
    else
 #endif
    {
        r_sau_spi_receive(p_ctrl);
    }

    if (p_ctrl->tx_count < p_ctrl->count)
    {
        r_sau_spi_transmit(p_ctrl);
    }

 #if SAU_SPI_TRANSFER_MODE_CONTINUOUS_ENABLE
    else if (continuous_transfer)
    {
        /* 2nd to last byte */
        smr &= (uint16_t) ~SAU_SPI_TRANSFER_MODE_CONTINUOUS;
        SAU_REG->SMR[SAU_SPI_PRV_CHANNEL] = smr;
    }
 #endif
    else
    {
        /* last byte */
        r_sau_spi_call_callback(p_ctrl, SPI_EVENT_TRANSFER_COMPLETE);
        p_ctrl->transfer_in_progress = false;
    }
}

#endif

#if SAU_SPI_CFG_MULTIPLE_SLAVE_COMPATIBILITY_MODE_ENABLE

/*******************************************************************************************************************//**
 * Reset SO pin setting.
 *
 * @param[in]     p_ctrl    Pointer to the control structure.
 * @param[in]     reset     Reset SO pin.
 **********************************************************************************************************************/
static void r_sau_spi_reset_pin (sau_spi_instance_ctrl_t * p_ctrl, bool reset)
{
    spi_cfg_t const * p_cfg = p_ctrl->p_cfg;
    if (SPI_MODE_SLAVE == p_cfg->operating_mode)
    {
        sau_spi_extended_cfg_t * p_extend = (sau_spi_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

        /* If single channel is disabled, then save the channel number on the stack. */
        SAU_SPI_PRV_CHANNEL_DECLARATION;

 #if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;
 #endif
        if (true == reset)
        {
            SAU_REG->SOE &= (uint16_t) ~(1 << SAU_SPI_PRV_CHANNEL);
        }
        else
        {
            SAU_REG->SOE |= (uint16_t) (1 << SAU_SPI_PRV_CHANNEL);
        }

 #if SAU_SPI_CFG_CRITICAL_SECTION_ENABLE
        FSP_CRITICAL_SECTION_EXIT;
 #endif
        R_BSP_PinAccessEnable();
        R_BSP_PinCfg(p_extend->so_pin_settings.pin,
                     reset ? ((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT) : p_extend->so_pin_settings.cfg);
        R_BSP_PinAccessDisable();
    }
}

#endif
