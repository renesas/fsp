/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sci_b_lin.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SCI_B_LIN_FRAME_ID_MASK                  (0x3FU)

/* "LINB" in ASCII.  Used to determine if the control block is open. */
#define SCI_B_LIN_OPEN                           (0x4C494E42U)

/* Max value of break field length register */
#define SCI_B_LIN_BFLW_MAX                       (0xFFFEU)

/* Range of LIN timer supported TCSS values */
#define SCI_B_LIN_TCSS_MIN                       (SCI_B_LIN_TIMER_DIV_4)
#define SCI_B_LIN_TCSS_MAX                       (SCI_B_LIN_TIMER_DIV_64)

/* Max value of CKS for setting baud rate */
#define SCI_B_LIN_CKS_MAX                        (3U)

#define SCI_B_LIN_MIN_BAUD_DIVISOR_SHIFT         (5)

/* Used to validate the checksum of received data */
#define SCI_B_LIN_CHECKSUM_OK                    (0xff)

/* LIN Sync Word (Control Field 0) */
#define SCI_B_LIN_SYNC                           (0x55U)

/* Header frame length */
#define SCI_B_LIN_HEADER_NUM_BYTES               (2)

/* Macro to clear all Simple LIN related flags in CFCLR (Common Flag Clear Register). Flags are
 * listed in Figure 26.105 "Example of Start Frame Reception Flowchart" of the RA6T2 manual
 * R01UH0951EJ0130  */
#define SCI_B_LIN_CFCLR_CLEAR_LIN_FLAGS          (                                      \
        R_SCI_B0_CFCLR_RDRFC_Msk | R_SCI_B0_CFCLR_FERC_Msk | R_SCI_B0_CFCLR_DPERC_Msk | \
        R_SCI_B0_CFCLR_PERC_Msk | R_SCI_B0_CFCLR_MFFC_Msk | R_SCI_B0_CFCLR_ORERC_Msk |  \
        R_SCI_B0_CFCLR_DFERC_Msk | R_SCI_B0_CFCLR_DCMFC_Msk | R_SCI_B0_CFCLR_ERSC_Msk)

/* Macro to clear all Simple LIN related flags in XFCLR (Simple LIN Flag Clear Register). Flags
 * are listed in Figure 26.105 "Example of Start Frame Reception Flowchart" of the RA6T2 manual
 * R01UH0951EJ0130 */
#define SCI_B_LIN_XFCLR_CLEAR_LIN_FLAGS          (                                      \
        R_SCI_B0_XFCLR_AEDC_Msk | R_SCI_B0_XFCLR_COFC_Msk | R_SCI_B0_XFCLR_PIBDC_Msk |  \
        R_SCI_B0_XFCLR_CF1MC_Msk | R_SCI_B0_XFCLR_CF0MC_Msk | R_SCI_B0_XFCLR_BFDC_Msk | \
        R_SCI_B0_XFCLR_BCDC_Msk | R_SCI_B0_XFCLR_BFOC_Msk)

/* SCI CCR2 register masks */
#define SCI_B_LIN_CCR2_RESETVALUE                (0xFF00FF04U)

/* SCI CCR2 value with all used bits zeroed and all unused bits set to their reset values (used for baud calculation result) */
#define SCI_B_LIN_CCR2_BAUD_SETTING              (SCI_B_LIN_CCR2_RESETVALUE &           \
                                                  (uint32_t) ~(R_SCI_B0_CCR2_BRR_Msk |  \
                                                               R_SCI_B0_CCR2_ABCS_Msk | \
                                                               R_SCI_B0_CCR2_CKS_Msk))

/* SCI CCR3 register masks */
#define SCI_B_LIN_CCR3_SIMPLE_LIN_MODE           (6U << R_SCI_B0_CCR3_MOD_Pos)
#define SCI_B_LIN_CCR3_8_BITS_DATA               (2U << R_SCI_B0_CCR3_CHR_Pos)
#define SCI_B_LIN_CCR3_LSB_FIRST                 (1U << R_SCI_B0_CCR3_LSBF_Pos)
#define SCI_B_LIN_CCR3_START_BIT_EDGE_FALLING    (1U << R_SCI_B0_CCR3_RXDESEL_Pos)
#define SCI_B_LIN_CCR3_CPOL                      (1U << R_SCI_B0_CCR3_CPOL_Pos)
#define SCI_B_LIN_CCR3_CPHA                      (1U << R_SCI_B0_CCR3_CPHA_Pos)
#define SCI_B_LIN_CCR3_MASK                      (                                               \
        SCI_B_LIN_CCR3_SIMPLE_LIN_MODE | SCI_B_LIN_CCR3_8_BITS_DATA | SCI_B_LIN_CCR3_LSB_FIRST | \
        SCI_B_LIN_CCR3_START_BIT_EDGE_FALLING | SCI_B_LIN_CCR3_CPOL | SCI_B_LIN_CCR3_CPHA)

/* SCI XCR0 register masks */
#define SCI_B_LIN_XCR0_MASK_MASTER               (R_SCI_B0_XCR0_BFOIE_Msk)
#define SCI_B_LIN_XCR0_MASK_SLAVE                (R_SCI_B0_XCR0_BFE_Msk | R_SCI_B0_XCR0_CF0RE_Msk | \
                                                  R_SCI_B0_XCR0_BFDIE_Msk | R_SCI_B0_XCR0_COFIE_Msk)

/* SCI XCR1 register masks */
#define SCI_B_LIN_XCR1_MASK_MASTER               (0U)
#define SCI_B_LIN_XCR1_MASK_SLAVE                (R_SCI_B0_XCR1_SDST_Msk)

/* SCI XCR2 register masks */
#define SCI_B_LIN_XCR2_CF0D                      (SCI_B_LIN_SYNC << R_SCI_B0_XCR2_CF0D_Pos)
#define SCI_B_LIN_XCR2_MASK_MASTER               (0U)
#define SCI_B_LIN_XCR2_MASK_SLAVE                (SCI_B_LIN_XCR2_CF0D)

/* SCI ERI mask helpers */
#define SCI_B_LIN_ERI_CSR_EVENTS_MASK            (LIN_EVENT_ERR_PARITY | LIN_EVENT_ERR_FRAMING | \
                                                  LIN_EVENT_ERR_OVERRUN)
#define SCI_B_LIN_ERI_XSR_EVENTS_MASK            (LIN_EVENT_ERR_BUS_COLLISION_DETECTED | \
                                                  LIN_EVENT_ERR_COUNTER_OVERFLOW)
#define SCI_B_LIN_ERROR_CSR_EVENTS_CLEAR_MASK    (R_SCI_B0_CFCLR_PERC_Msk | R_SCI_B0_CFCLR_FERC_Msk | \
                                                  R_SCI_B0_CFCLR_ORERC_Msk | R_SCI_B0_CFCLR_RDRFC_Msk)
#define SCI_B_LIN_ERROR_XSR_EVENTS_CLEAR_MASK    (R_SCI_B0_XFCLR_BCDC_Msk | R_SCI_B0_XFCLR_COFC_Msk | \
                                                  R_SCI_B0_XFCLR_BFDC_Msk | R_SCI_B0_XFCLR_AEDC_Msk)

/* Number of consecutive measurements used to synchronize the bit rate */
#define SCI_B_LIN_SYNC_EDGES                     (6)

#define SCI_B_LIN_IRQS_ENABLE()     r_sci_b_lin_irqs_enable_disable(p_ctrl, r_sci_b_lin_irq_enable)
#define SCI_B_LIN_IRQS_DISABLE()    r_sci_b_lin_irqs_enable_disable(p_ctrl, r_sci_b_lin_irq_disable)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * sci_b_lin_prv_ns_callback)(lin_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile sci_b_lin_prv_ns_callback)(lin_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* LIN on SCI B HAL API mapping for LIN interface */
const lin_api_t g_lin_on_sci_b =
{
    .open                  = R_SCI_B_LIN_Open,
    .read                  = R_SCI_B_LIN_Read,
    .write                 = R_SCI_B_LIN_Write,
    .communicationAbort    = R_SCI_B_LIN_CommunicationAbort,
    .callbackSet           = R_SCI_B_LIN_CallbackSet,
    .close                 = R_SCI_B_LIN_Close,
    .sleepEnter            = R_SCI_B_LIN_SleepEnter,
    .sleepExit             = R_SCI_B_LIN_SleepExit,
    .wakeupSend            = R_SCI_B_LIN_WakeupSend,
    .informationFrameRead  = R_SCI_B_LIN_InformationFrameRead,  // [DEPRECATED]
    .startFrameWrite       = R_SCI_B_LIN_StartFrameWrite,       // [DEPRECATED]
    .informationFrameWrite = R_SCI_B_LIN_InformationFrameWrite, // [DEPRECATED]
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* PID and checksum helper functions */
static uint8_t r_sci_b_lin_pid_calculate(uint8_t id);

#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE
static uint8_t r_sci_b_lin_checksum_calculate(uint8_t               id,
                                              uint8_t const * const p_data,
                                              uint8_t               num_bytes,
                                              lin_checksum_type_t   checksum_type);
static uint8_t r_sci_b_lin_checksum_initialize(uint8_t id, lin_checksum_type_t checksum_type);
static uint8_t r_sci_b_lin_checksum_add_byte_to_sum(uint8_t byte, uint8_t current_sum);

#endif

/* Initialization helper functions */
static void r_sci_b_lin_hw_configure(sci_b_lin_instance_ctrl_t * const p_ctrl);
static void r_sci_b_lin_irq_cfg(IRQn_Type const irq);
static void r_sci_b_lin_irqs_cfg(sci_b_lin_instance_ctrl_t * const p_ctrl);
static void r_sci_b_lin_irq_enable(IRQn_Type irq, uint8_t ipl, void * p_context);
static void r_sci_b_lin_irq_disable(IRQn_Type irq, uint8_t ipl, void * p_context);
static void r_sci_b_lin_irqs_enable_disable(sci_b_lin_instance_ctrl_t * const p_ctrl,
                                            void (* irqEnableDisableFunc)(IRQn_Type irq, uint8_t ipl,
                                                                          void * p_context));

static void r_sci_b_lin_filter_settings_configure(uint32_t * const                            xcr0,
                                                  uint32_t * const                            xcr1,
                                                  sci_b_lin_id_filter_setting_t const * const p_config);

#if (SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t r_sci_b_lin_common_parameter_checking(sci_b_lin_instance_ctrl_t const * const p_ctrl);
static fsp_err_t r_sci_b_lin_read_write_parameter_checking(sci_b_lin_instance_ctrl_t const * const p_ctrl,
                                                           lin_transfer_params_t const * const     p_transfer_params);

#endif

static fsp_err_t r_sci_b_lin_write(sci_b_lin_instance_ctrl_t * const   p_ctrl,
                                   const lin_transfer_params_t * const p_transfer_params,
                                   uint8_t const                       send_header);

static void        r_sci_b_lin_call_callback(sci_b_lin_instance_ctrl_t * p_ctrl, lin_event_t event);
static lin_event_t r_sci_b_lin_rxi_handler(sci_b_lin_instance_ctrl_t * const p_ctrl);
static void        r_sci_b_lin_txi_handler(sci_b_lin_instance_ctrl_t * const p_ctrl);
static lin_event_t r_sci_b_lin_eri_handler(sci_b_lin_instance_ctrl_t * const p_ctrl);
static void        r_sci_b_lin_bfd_handler(sci_b_lin_instance_ctrl_t * const p_ctrl);

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE
static void r_sci_b_lin_aed_handler(sci_b_lin_instance_ctrl_t * const p_ctrl);

#endif

/* Baud and timing helper functions */
static uint32_t r_sci_b_lin_clock_freq_get(sci_b_lin_clock_source_t clock_source);
static uint32_t r_sci_b_lin_timer_freq_get(sci_b_lin_clock_source_t  clock_source,
                                           sci_b_lin_timer_divider_t lin_divider);
static fsp_err_t r_sci_b_lin_baud_setting_calculate(sci_b_lin_baud_params_t const * const p_baud_params,
                                                    sci_b_lin_base_clock_t                base_clock_cycles_per_bit,
                                                    bool                                  check_bus_conflict_divider,
                                                    sci_b_lin_baud_setting_t * const      p_baud_setting);
static fsp_err_t r_sci_b_lin_timer_setting_calculate(sci_b_lin_baud_params_t const * const p_baud_params,
                                                     sci_b_lin_timer_setting_t * const     p_timer_setting);

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

/* Auto Synchronization helper functions */
static void r_sci_b_lin_aed_synchronize(sci_b_lin_instance_ctrl_t * const p_ctrl);
static bool r_sci_b_lin_aed_latest_bit_has_error(sci_b_lin_instance_ctrl_t * const p_ctrl, uint16_t tcnt);
static void r_sci_b_lin_aed_reset(sci_b_lin_instance_ctrl_t * const p_ctrl);

#endif

static void r_sci_b_lin_flags_clear(R_SCI_B0_Type * const p_reg, uint32_t cfclr, uint32_t xfclr);

/* Interrupt service routines */
void sci_b_lin_rxi_isr(void);
void sci_b_lin_tei_isr(void);
void sci_b_lin_txi_isr(void);
void sci_b_lin_eri_isr(void);
void sci_b_lin_aed_isr(void);
void sci_b_lin_bfd_isr(void);

/*******************************************************************************************************************//**
 * @addtogroup SCI_B_LIN
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
 * @snippet r_sci_b_lin_example.c R_SCI_B_LIN_Open
 *
 * @retval  FSP_SUCCESS                    Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to LIN control block or configuration structure is NULL.
 * @retval  FSP_ERR_INVALID_CHANNEL        The requested channel does not exist on this MCU or the channel does not support Simple LIN mode.
 * @retval  FSP_ERR_INVALID_ARGUMENT       Break field length setting or timer divisor is invalid.
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 * @retval FSP_ERR_INVALID_MODE            Setting not supported for selected mode
 *
 * @return                                 See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                         return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_Open (lin_ctrl_t * const p_api_ctrl, lin_cfg_t const * const p_cfg)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_cfg->p_callback);

    /* Check control block isn't already open */
    FSP_ERROR_RETURN(p_ctrl->open != SCI_B_LIN_OPEN, FSP_ERR_ALREADY_OPEN);

    /* Make sure this channel supports Simple LIN Mode (some MCUs do not support it on all SCI channels) */
    FSP_ERROR_RETURN(BSP_FEATURE_SCI_LIN_CHANNELS & (1U << p_cfg->channel), FSP_ERR_INVALID_CHANNEL);

    sci_b_lin_extended_cfg_t const * const p_extend = (sci_b_lin_extended_cfg_t *) p_cfg->p_extend;

    /* Check for required IRQs */
    FSP_ASSERT(p_extend->rxi_irq >= 0);
    FSP_ASSERT(p_extend->txi_irq >= 0);
    FSP_ASSERT(p_extend->tei_irq >= 0);
    FSP_ASSERT(p_extend->eri_irq >= 0);
    FSP_ASSERT(p_extend->bfd_irq >= 0 || (LIN_MODE_MASTER == p_cfg->mode));
 #if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Auto Synchronization not supported in master mode */
    FSP_ERROR_RETURN((p_extend->sci_b_settings_b.auto_synchronization == SCI_B_LIN_AUTO_SYNCHRONIZATION_DISABLE) ||
                     (LIN_MODE_SLAVE == p_cfg->mode),
                     FSP_ERR_INVALID_MODE);

    FSP_ASSERT((p_extend->aed_irq >= 0) ||
               (((p_extend->sci_b_settings_b.auto_synchronization == SCI_B_LIN_AUTO_SYNCHRONIZATION_DISABLE))));
 #endif

    /* Check timer settings in range */
    FSP_ERROR_RETURN(p_extend->baud_setting.timer_setting.bflw <= SCI_B_LIN_BFLW_MAX, FSP_ERR_INVALID_ARGUMENT);

    FSP_ERROR_RETURN(p_extend->baud_setting.timer_setting.tcss >= SCI_B_LIN_TCSS_MIN, FSP_ERR_INVALID_ARGUMENT);

    /* It is prohibited to set BCCS[1:0] = 1x when CCR2.ABCS = 1. Either bit 2 of BCSS must be 0, or ABCS must be 0, or both. */
    FSP_ERROR_RETURN((SCI_B_LIN_BUS_CONFLICT_DETECTION_BASE_CLOCK_DIV_4 != p_extend->sci_b_settings_b.bus_conflict_clock) ||
                     (0U == (uint32_t) p_extend->baud_setting.baudrate_bits_b.abcs),
                     FSP_ERR_INVALID_ARGUMENT);
#endif

    /* Initialize control block */
    p_ctrl->p_reg =
        (R_SCI_B0_Type *) (R_SCI0_BASE + ((R_SCI1_BASE - R_SCI0_BASE) * p_cfg->channel));
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;
    p_ctrl->p_data            = NULL;
    p_ctrl->rx_bytes_expected = 0;
    p_ctrl->rx_bytes_received = 0;
    p_ctrl->tx_src_bytes      = 0;
    p_ctrl->tx_header_bytes   = 0;

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE
 #if (0 == SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE)
    sci_b_lin_extended_cfg_t const * const p_extend = (sci_b_lin_extended_cfg_t *) p_cfg->p_extend;
 #endif

    /* Calculate timer frequency */
    sci_b_lin_clock_source_t  clock_source  = (sci_b_lin_clock_source_t) p_extend->sci_b_settings_b.clock_source;
    sci_b_lin_timer_divider_t timer_divider = (sci_b_lin_timer_divider_t) p_extend->baud_setting.timer_setting.tcss;
    p_ctrl->timer_freq_hz = r_sci_b_lin_timer_freq_get(clock_source, timer_divider);
#endif

    /* Configure, but do not enable the interrupts in the NVIC */
    r_sci_b_lin_irqs_cfg(p_ctrl);

    /* Initialize the SCI in Simple LIN mode. */
    r_sci_b_lin_hw_configure(p_ctrl);

    /* Enable interrupt handlers in the NVIC */
    SCI_B_LIN_IRQS_ENABLE();

    /* Mark the control block as open */
    p_ctrl->open = SCI_B_LIN_OPEN;

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
 * @snippet r_sci_b_lin_example.c R_SCI_B_LIN_Write
 *
 * @retval  FSP_SUCCESS                  Transmission started successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT     ID out of range (unprotected ID must be less than 64). Only applies in master mode. In slave mode, p_transfer_params->id is ignored.
 * @retval  FSP_ERR_IN_USE               A transmission or reception is currently in progress. Call @ref R_SCI_B_LIN_CommunicationAbort
 *                                       to cancel it if desired, or wait for the current transfer operation to complete before starting a new one.
 *
 * @return                               See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                       return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_Write (lin_ctrl_t * const p_api_ctrl, const lin_transfer_params_t * const p_transfer_params)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_transfer_params);
    fsp_err_t err = r_sci_b_lin_read_write_parameter_checking(p_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Send the header before the data in master mode only */
    uint8_t send_header = LIN_MODE_MASTER == p_ctrl->p_cfg->mode;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE

    /* Check ID is at most 6 bits (only for master header transmission) */
    FSP_ERROR_RETURN((0 == (p_transfer_params->id & 0xC0)) || !send_header, FSP_ERR_INVALID_ARGUMENT);

    /* Check p_data is not null in slave mode */
    FSP_ASSERT(NULL != p_transfer_params->p_data || send_header);
#endif

    return r_sci_b_lin_write(p_ctrl, p_transfer_params, send_header);
}

/*******************************************************************************************************************//**
 * Begins non-blocking data reception to receive user specified number of bytes into destination buffer pointer.
 *
 * The checksum type specifies the checksum type used for validation. If a non-standard algorithm is used,
 * or the application prefers to validate the checksum outside the driver, or the application prefers
 * to skip checksum validation, specify @ref lin_checksum_type_t::LIN_CHECKSUM_TYPE_NONE. If checksum
 * validation is skipped, the @ref lin_checksum_type_t::LIN_EVENT_ERR_INVALID_CHECKSUM event is not possible.
 * When  @ref lin_checksum_type_t::LIN_CHECKSUM_TYPE_NONE is used, the number of bytes specified in the receive
 * buffer length will be received (the driver will not expect to receive an additional 1 checksum byte), so
 * if a non-standard checksum is used, sufficient space must be allocated in the write buffer and accounted for
 * in the provided length.
 *
 * On successful data reception completion, the callback is called with event @ref lin_event_t::LIN_EVENT_RX_DATA_COMPLETE.
 *
 * Implements @ref lin_api_t::read.
 *
 * Example:
 * @snippet r_sci_b_lin_example.c R_SCI_B_LIN_Read
 *
 * @retval  FSP_SUCCESS              Data reception started successfully.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0 bytes length provided
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call @ref R_SCI_B_LIN_CommunicationAbort
 *                                   to cancel it if desired, or wait for the current transfer operation to complete before starting a new one.
 * @retval  FSP_ERR_INVALID_CALL     Data reception is not possible because a header frame has not been received yet (slave mode only).
 *
 *  @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_Read (lin_ctrl_t * const p_api_ctrl, lin_transfer_params_t * const p_transfer_params)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_b_lin_read_write_parameter_checking(p_api_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    FSP_ASSERT(NULL != p_transfer_params->p_data);
#endif

    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE

    /* In slave mode, check that data reception is possible (due to successful header reception) */
    FSP_ERROR_RETURN((LIN_MODE_MASTER == p_ctrl->p_cfg->mode) || (0 == (R_SCI_B0_XSR0_SFSF_Msk & p_reg->XSR0)),
                     FSP_ERR_INVALID_CALL);
#endif

    /* Disable reception interrupts */
    p_reg->CCR0_b.RIE = 0;

    /* Prepare receive state */
    p_ctrl->p_data            = p_transfer_params->p_data;
    p_ctrl->rx_bytes_expected = p_transfer_params->num_bytes;
    p_ctrl->rx_bytes_received = 0;
    p_ctrl->checksum          = 0;

#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE
    p_ctrl->validate_checksum = p_transfer_params->checksum_type != LIN_CHECKSUM_TYPE_NONE;

    /* Initialize checksum tracking fields */
    if (p_ctrl->validate_checksum)
    {
        p_ctrl->rx_bytes_expected++;
        p_ctrl->checksum = r_sci_b_lin_checksum_initialize(p_transfer_params->id, p_transfer_params->checksum_type);
    }
#endif

    /* Enable reception interrupts */
    p_reg->CFCLR      = SCI_B_LIN_ERROR_CSR_EVENTS_CLEAR_MASK;
    p_reg->CCR0_b.RIE = 1;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Cancels in progress data read or write, or header read or write. Break field reception cannot be
 * cancelled. For slave nodes, reception of a new header is still enabled after a call to this function.
 *
 * Implements @ref lin_api_t::communicationAbort.
 *
 * @retval  FSP_SUCCESS              Data transfer aborted successfully or no transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block is NULL.
 *
 * @return                                 See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                         return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_CommunicationAbort (lin_ctrl_t * const p_api_ctrl)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_b_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

    /* Disable transmit interrupts, transmission, and reception interrupts  */
    p_reg->CCR0 &=
        (uint32_t) ~(R_SCI_B0_CCR0_TIE_Msk | R_SCI_B0_CCR0_TEIE_Msk | R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_RIE_Msk);

    /* Wait until internal  state of TE is 0 as it takes some time for the state to be reflected
     * internally after rewriting the control register. Refer to "26.2.29 CESR : Communication
     * Enable Status Register" description in the RA6T2 manual R01UH0951EJ0100 or the relevant section
     * for the MCU being used  */
    FSP_HARDWARE_REGISTER_WAIT(p_reg->CESR_b.TIST, 0U);

    /* Cancel data or header write */
    p_ctrl->tx_src_bytes    = 0U;
    p_ctrl->tx_header_bytes = 0U;

    /* Cancel data read */
    p_ctrl->rx_bytes_expected = 0U;

    /* Reset data buffer pointer */
    p_ctrl->p_data = NULL;

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Reset bit rate measurement hardware state in preparation to receive next header (slave only) */
    r_sci_b_lin_aed_reset(p_ctrl);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 *
 * Implements @ref lin_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to LIN control block or callback is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 *
 * @return                                 See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                         return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_CallbackSet (lin_ctrl_t * const          p_api_ctrl,
                                   void (                    * p_callback)(lin_callback_args_t *),
                                   void * const                p_context,
                                   lin_callback_args_t * const p_callback_memory)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_b_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_callback);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    lin_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(lin_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculates baud rate and LIN timer (BFLW and TCSS) register settings. This function evaluates and determines the
 * most accurate settings for the baud rate and timer related registers.
 *
 * The LIN timer setting is used for break field transmission/detection. Because the timer setting is specified in terms
 * of bits, and the duration of a bit varies depending on baud rate, the baud rate register settings and timer register
 * settings are related. The smallest possible LIN timer divider which can achieve the desired break field bits setting
 * at the configured baud rate is selected to provide the highest measurement accuracy.
 *
 * The baud rate cannot be updated at runtime with this function. This function is provided to ease configuration of
 * the initial baud settings.
 *
 * @note The parameter p_baud_setting->bus_conflict_clock is deprecated and is not used to determine
 * the baud rate settings. See Usage Notes for a description of how to select the bus conflict clock divider.
 *
 * @param[in]  p_baud_params         Parameters required to calculate the baud rate
 * @param[out] p_baud_setting        If calculation succeeds, contains computed values to achieve requested baud rate.
 *                                   If calculation fails, the input structure is not modified.
 *
 * @retval  FSP_SUCCESS                 Register settings updated in provided p_baud_setting
 * @retval  FSP_ERR_ASSERTION           p_baud_setting was NULL
 * @retval  FSP_ERR_INVALID_ARGUMENT    Cannot achieve combination of break field bits and baudrate with provided settings
 *                                      or p_baud_params->baudrate was 0 or p_baud_params->break_bits was 0
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_BaudCalculate (sci_b_lin_baud_params_t const * const p_baud_params,
                                     sci_b_lin_baud_setting_t * const      p_baud_setting)
{
#if (SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_baud_params);
    FSP_ASSERT(p_baud_setting);
    FSP_ERROR_RETURN((0U != p_baud_params->break_bits), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0U != p_baud_params->baudrate), FSP_ERR_INVALID_ARGUMENT);
#endif

    fsp_err_t err;

    /* Use temp variable in order to not update output arg unless both baud and timer calculations succeed */
    sci_b_lin_baud_setting_t tmp_baud_setting;

    err =
        r_sci_b_lin_baud_setting_calculate(p_baud_params,
                                           SCI_B_LIN_BASE_CLOCK_AUTO_CYCLES_PER_BIT,
                                           false,
                                           &tmp_baud_setting);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sci_b_lin_timer_setting_calculate(p_baud_params, &tmp_baud_setting.timer_setting);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    *p_baud_setting = tmp_baud_setting;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the the ID filter settings for filtering control field 1 (PID byte).
 *
 * NOTE: Setting the ID filter will abort any in-progress LIN header reception, as the ID filter
 * settings cannot be changed during reception of the header. The next header will be received with the
 * new settings.
 *
 * @snippet r_sci_b_lin_example.c R_SCI_B_LIN_IdFilterSet
 *
 * @param[in]  p_api_ctrl           Pointer to the LIN control block.
 * @param[in]  p_config             The ID filter settings to apply
 *
 * @retval  FSP_SUCCESS              ID filter updated successfully.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block or p_config is NULL.
 * @retval  FSP_ERR_INVALID_MODE     Function called by master node (not supported for master nodes)
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_IdFilterSet (lin_ctrl_t * const p_api_ctrl, sci_b_lin_id_filter_setting_t const * const p_config)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_b_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_config);

    /* Function only supported for slave mode */
    FSP_ERROR_RETURN(LIN_MODE_SLAVE == p_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
#endif

    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

    /* Disable header reception. See Note 3 in "26.2.14 XCR0 : Simple LIN Control Register 0" R01UH0951EJ0130.
     * XCR0.PIBS, XCR0.PIBE, and XCR0.CF1DS can be rewritten only when Start Frame reception or transmission is not
     * in progress (XCR1.SDST = 0 and XCR1.TCST = 0) */
    p_reg->XCR1 &= (uint32_t) ~(R_SCI_B0_XCR1_SDST_Msk | R_SCI_B0_XCR1_TCST_Msk);

    uint32_t xcr0 = p_reg->XCR0;
    uint32_t xcr1 = p_reg->XCR1;

    /* Clear current XCR0 filter settings */
    xcr0 &= (uint32_t) ~(R_SCI_B0_XCR0_PIBS_Msk | R_SCI_B0_XCR0_PIBE_Msk | R_SCI_B0_XCR0_CF1DS_Msk);

    /* Clear current XCR1 filter settings */
    xcr1 &= (uint32_t) ~(R_SCI_B0_XCR1_CF1CE_Msk | R_SCI_B0_XCR1_PCF1D_Msk | R_SCI_B0_XCR1_SCF1D_Msk);

    /* Apply new filter settings */
    r_sci_b_lin_filter_settings_configure(&xcr0, &xcr1, p_config);

    /* Apply new settings and reenable header reception (TCST should never be set in slave mode) */
    p_reg->XCR0 = xcr0;
    p_reg->XCR1 = xcr1 | R_SCI_B0_XCR1_SDST_Msk;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the currently configured ID filter settings.
 *
 * @param[in]  p_api_ctrl           Pointer to the LIN control block.
 * @param[out] p_config             The current ID filter settings
 *
 * @retval  FSP_SUCCESS              ID filter updated successfully.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block or p_config is NULL.
 * @retval  FSP_ERR_INVALID_MODE     Function called by master node (not supported for master nodes)
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_IdFilterGet (lin_ctrl_t * const p_api_ctrl, sci_b_lin_id_filter_setting_t * const p_config)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_b_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_config);

    /* Function only supported for slave mode */
    FSP_ERROR_RETURN(LIN_MODE_SLAVE == p_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
#endif

    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;
    uint32_t        xcr0  = p_reg->XCR0;
    uint32_t        xcr1  = p_reg->XCR1;

    p_config->compare_data_mask             = (uint8_t) ((xcr1 & R_SCI_B0_XCR1_CF1CE_Msk) >> R_SCI_B0_XCR1_CF1CE_Pos);
    p_config->priority_compare_data         = (uint8_t) ((xcr1 & R_SCI_B0_XCR1_PCF1D_Msk) >> R_SCI_B0_XCR1_PCF1D_Pos);
    p_config->secondary_compare_data        = (uint8_t) ((xcr1 & R_SCI_B0_XCR1_SCF1D_Msk) >> R_SCI_B0_XCR1_SCF1D_Pos);
    p_config->priority_interrupt_bit_select = (uint8_t) ((xcr0 & R_SCI_B0_XCR0_PIBS_Msk) >> R_SCI_B0_XCR0_PIBS_Pos);
    p_config->priority_interrupt_enable     = (uint8_t) ((xcr0 & R_SCI_B0_XCR0_PIBE_Msk) >> R_SCI_B0_XCR0_PIBE_Pos);
    p_config->compare_data_select           = (uint8_t) ((xcr0 & R_SCI_B0_XCR0_CF1DS_Msk) >> R_SCI_B0_XCR0_CF1DS_Pos);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Send wakeup is not supported on the SCI_B LIN driver.
 *
 * Implements @ref lin_api_t::wakeupSend.
 *
 * @retval FSP_ERR_UNSUPPORTED       Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_WakeupSend (lin_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Sleep is not supported on the SCI_B LIN driver.
 *
 * Implements @ref lin_api_t::sleepEnter.
 *
 * @retval FSP_ERR_UNSUPPORTED       Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_SleepEnter (lin_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Sleep is not supported on the SCI_B LIN driver.
 *
 * Implements @ref lin_api_t::sleepExit.
 *
 * @retval FSP_ERR_UNSUPPORTED       Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_SleepExit (lin_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Closes the LIN driver.
 *
 * Implements @ref lin_api_t::close.
 *
 * Example:
 * @snippet r_sci_b_lin_example.c R_SCI_B_LIN_Close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_Close (lin_ctrl_t * const p_api_ctrl)
{
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_b_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

    /* Disable transmission and reception */
    p_reg->CCR0 = 0;

    /* Wait until internal state of TE is 0. See "26.2.29 CESR : Communication Enable Status
     * Register" description in the RA6T2 manual R01UH0951EJ0100. */
    FSP_HARDWARE_REGISTER_WAIT(p_reg->CESR_b.TIST, 0U);

    /* Disable irqs */
    SCI_B_LIN_IRQS_DISABLE();

    /* Disable the clock to the SCI channel. */
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_ctrl->p_cfg->channel);

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SCI_B_LIN_Read.
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_InformationFrameRead (lin_ctrl_t * const            p_api_ctrl,
                                            lin_transfer_params_t * const p_transfer_params)
{
    return R_SCI_B_LIN_Read(p_api_ctrl, p_transfer_params);
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SCI_B_LIN_Write
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_StartFrameWrite (lin_ctrl_t * const p_api_ctrl, uint8_t const id)
{
    lin_transfer_params_t params =
    {
        .id            = id,
        .p_data        = NULL,
        .num_bytes     = 0,
        .checksum_type = LIN_CHECKSUM_TYPE_NONE
    };

#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = r_sci_b_lin_read_write_parameter_checking(p_ctrl, &params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check ID is at most 6 bits */
    FSP_ERROR_RETURN(0 == (id & 0xC0), FSP_ERR_INVALID_ARGUMENT);

    /* Function only supported for master mode */
    FSP_ERROR_RETURN(LIN_MODE_MASTER == p_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
#endif

    return r_sci_b_lin_write(p_api_ctrl, &params, true);
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SCI_B_LIN_Write
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_LIN_InformationFrameWrite (lin_ctrl_t * const                  p_api_ctrl,
                                             const lin_transfer_params_t * const p_transfer_params)
{
#if SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_b_lin_read_write_parameter_checking((sci_b_lin_instance_ctrl_t *) p_api_ctrl,
                                                              p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_transfer_params->p_data);
#endif

    return r_sci_b_lin_write(p_api_ctrl, p_transfer_params, false);
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCI_B_LIN)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (SCI_B_LIN_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Verifies the control structure is not NULL and the module is open. This reduces code size when parameter checking is
 * enabled.
 *
 * @param[in] p_ctrl                    Pointer to the control block for the channel
 *
 * @retval FSP_SUCCESS                  No error detected.
 * @retval FSP_ERR_ASSERTION            NULL input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 **********************************************************************************************************************/
static fsp_err_t r_sci_b_lin_common_parameter_checking (sci_b_lin_instance_ctrl_t const * const p_ctrl)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_B_LIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter error check function for R_SCI_B_LIN_Write and R_SCI_B_LIN_Read
 *
 * @param[in] p_ctrl             Pointer to the control block for the channel
 * @param[in] p_transfer_params  Pointer to the transfer parameters for the transfer
 *
 * @retval  FSP_SUCCESS              No parameter error found
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call R_SCI_B_LIN_CommunicationAbort
 *                                   to cancel it if desired, or wait for the current transfer operation to complete before starting a new one.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0 bytes length provided
 **********************************************************************************************************************/
static fsp_err_t r_sci_b_lin_read_write_parameter_checking (sci_b_lin_instance_ctrl_t const * const p_ctrl,
                                                            lin_transfer_params_t const * const     p_transfer_params)
{
    fsp_err_t err = r_sci_b_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_transfer_params);

    /* Number of bytes and checksum parameters are only checked for data transfers */
    if (NULL != p_transfer_params->p_data)
    {
        FSP_ASSERT(p_transfer_params->num_bytes > 0);
        FSP_ASSERT(((p_transfer_params->num_bytes < UINT8_MAX) ||
                    (LIN_CHECKSUM_TYPE_NONE == p_transfer_params->checksum_type)));
    }

    /* Check that a header transmission, data transmission, or data reception is not currently in progress */
    FSP_ERROR_RETURN((0 == p_ctrl->tx_header_bytes) && (0 == p_ctrl->tx_src_bytes) && (0 == p_ctrl->rx_bytes_expected),
                     FSP_ERR_IN_USE);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Get the frequency of the Simple LIN peripheral clock
 *
 * @param[in]  clock_source           Clock source
 * @returns LIN clock frequency in Hz
 **********************************************************************************************************************/
static uint32_t r_sci_b_lin_clock_freq_get (sci_b_lin_clock_source_t clock_source)
{
    uint32_t freq_hz;

    if (SCI_B_LIN_CLOCK_SOURCE_PCLK == clock_source)
    {
        freq_hz = R_FSP_SystemClockHzGet(BSP_FEATURE_SCI_CLOCK);
    }
    else
    {
#if (BSP_FEATURE_BSP_HAS_SCISPI_CLOCK)
        freq_hz = R_FSP_SciSpiClockHzGet();
#else
        freq_hz = R_FSP_SciClockHzGet();
#endif
    }

    return freq_hz;
}

/*******************************************************************************************************************//**
 * Get the frequency of the LIN timer used for break field generation/detection and Auto Synchronization.
 *
 * @param[in]  clock_source          Driver clock source (PCLK or SCICLK/SCISPICLK)
 * @param[in]  lin_divider           LIN timer TCSS divider value
 *
 * @returns LIN timer frequency in Hz
 **********************************************************************************************************************/
static uint32_t r_sci_b_lin_timer_freq_get (sci_b_lin_clock_source_t  clock_source,
                                            sci_b_lin_timer_divider_t lin_divider)
{
    return r_sci_b_lin_clock_freq_get(clock_source) / (1U << (lin_divider << 1U));
}

/*******************************************************************************************************************//**
 * Calculates the baud rate register settings
 *
 * @param[in]  p_baud_params                 Function inputs required to calculate the baud rate
 * @param      base_clock_cycles_per_bit     Desired ABCS setting
 * @param      check_bus_conflict_divider    True if the bus conflict divider should be checked before selecting ABCS settings,
 *                                           since some combinations of bus conflict divider/ABCS are not allowed.
 * @param[out] p_baud_setting                Baud rate calculation result
 *
 * @note   ABCS controls the SCI_B base clock frequency (BGDM/ABCSE are not used). This frequency is relevant when setting
 *         bus conflict and noise cancellation dividers. When this function is called from R_SCI_B_LIN_BaudCalculate, all
 *         ABCS values are checked, and the one that would produce a valid baud rate with the lowest error is selected.
 *         When this function is called for runtime baudrate change during slave synchronization, ABCS may be fixed to
 *         a specific value to avoid bus conflict/noise cancellation clock dividers being incorrect after the sync.
 *
 * @retval  FSP_SUCCESS                 Calculation succeeded
 * @retval  FSP_ERR_INVALID_ARGUMENT    Calculation failed/register settings not possible
 ***********************************************************************************************************************/
static fsp_err_t r_sci_b_lin_baud_setting_calculate (sci_b_lin_baud_params_t const * const p_baud_params,
                                                     sci_b_lin_base_clock_t                base_clock_cycles_per_bit,
                                                     bool                                  check_bus_conflict_divider,
                                                     sci_b_lin_baud_setting_t * const      p_baud_setting)
{
    uint32_t freq_hz = r_sci_b_lin_clock_freq_get(p_baud_params->clock_source);
    uint32_t divisor = 0;
    uint32_t divisor_shift;
    int32_t  abcs;
    uint32_t brr      = 0;
    int32_t  cks      = -1;
    int32_t  abcs_min = (int32_t) base_clock_cycles_per_bit;
    int32_t  abcs_max = (int32_t) base_clock_cycles_per_bit;

    if (SCI_B_LIN_BASE_CLOCK_AUTO_CYCLES_PER_BIT == base_clock_cycles_per_bit)
    {
        /* If we are auto-selecting the best value, then the min value to check is 0 (16 cycles per bit)
         * and the max value is 1 (8 cycles per bit). If we are using a fixed value, the min and max values
         * to check are the fixed value itself. But it is prohibited to set BCCS[1:0] = 1x when CCR2.ABCS = 1 (8 cycles).
         * This only needs to be checked in auto select mode for slave auto sync adjustment because it will already
         * have been checked in open parameter checking for a fixed base clock cycles value */
        bool bus_conflict_divider_restriction = check_bus_conflict_divider &&
                                                (p_baud_params->bus_conflict_clock & 0x02);
        abcs_min = SCI_B_LIN_BASE_CLOCK_16_CYCLES_PER_BIT;
        abcs_max =
            bus_conflict_divider_restriction ? SCI_B_LIN_BASE_CLOCK_16_CYCLES_PER_BIT :
            SCI_B_LIN_BASE_CLOCK_8_CYCLES_PER_BIT;
    }

    /* BRR is calculated by testing whether each divisor (combination of ABCS, CKS, and N) produces a valid BRR setting.
     * The divisors are checked in order, from smallest to largest. Since the smallest divisor always produces the lowest
     * error, we can break out of the loop as soon as a valid BRR setting is found, since no other setting can have
     * a smaller error. */
    for (uint32_t i = 0; i <= SCI_B_LIN_CKS_MAX; i++)
    {
        cks++;

        /* Count down from max because a higher abcs value produces
         * a smaller divisor (and thus results in lower error) for a given cks. */
        for (abcs = abcs_max; abcs >= abcs_min; abcs--)
        {
            divisor_shift = SCI_B_LIN_MIN_BAUD_DIVISOR_SHIFT + ((uint32_t) cks << 1U) - (uint32_t) abcs;
            divisor       = (1U << divisor_shift) * p_baud_params->baudrate;
            brr           = (freq_hz / divisor) - 1U;

            if (brr <= UINT8_MAX)
            {
                i = (SCI_B_LIN_CKS_MAX + 1); // Break out of outer loop
                break;
            }
        }
    }

    FSP_ERROR_RETURN(brr <= UINT8_MAX, FSP_ERR_INVALID_ARGUMENT);

    /* Ensure unused bits are set to reset values so that unexpected baud setting is not generated
     * when passing in uninitialized stack variable. MSB of CCR2 is fixed to 1. */
    p_baud_setting->baudrate_bits = SCI_B_LIN_CCR2_BAUD_SETTING |
                                    ((uint32_t) abcs << R_SCI_B0_CCR2_ABCS_Pos) |
                                    (brr << R_SCI_B0_CCR2_BRR_Pos) |
                                    ((uint32_t) cks << R_SCI_B0_CCR2_CKS_Pos);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Calculates the lin timer register settings
 *
 * @param[in] p_baud_params     Function inputs required to calculate the baud rate
 * @param[out] p_timer_setting  Timer setting calculation result
 *
 * @retval  FSP_SUCCESS                 Calculation succeeded
 * @retval  FSP_ERR_INVALID_ARGUMENT    Calculation failed/register settings not possible
 ***********************************************************************************************************************/
static fsp_err_t r_sci_b_lin_timer_setting_calculate (sci_b_lin_baud_params_t const * const p_baud_params,
                                                      sci_b_lin_timer_setting_t * const     p_timer_setting)
{
    uint32_t bflw = SCI_B_LIN_BFLW_MAX + 1;
    sci_b_lin_timer_divider_t tcss;

    /* TCSS is calculated so that the smallest divider that produces a valid value for BFLW is selected */
    for (tcss = SCI_B_LIN_TCSS_MIN; tcss <= SCI_B_LIN_TCSS_MAX; tcss++)
    {
        uint32_t lin_timer_freq_hz = r_sci_b_lin_timer_freq_get(p_baud_params->clock_source, tcss);
        bflw =
            (uint32_t) ((((uint64_t) lin_timer_freq_hz * p_baud_params->break_bits) / p_baud_params->baudrate) - 1ULL);

        if (bflw <= SCI_B_LIN_BFLW_MAX)
        {
            break;
        }
    }

    FSP_ERROR_RETURN(bflw <= SCI_B_LIN_BFLW_MAX, FSP_ERR_INVALID_ARGUMENT);

    p_timer_setting->bflw = (uint16_t) bflw;
    p_timer_setting->tcss = (uint8_t) (tcss & 0x3);

    return FSP_SUCCESS;
}

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
static uint8_t r_sci_b_lin_pid_calculate (uint8_t id)
{
    /* ID is 6 bits */
    uint8_t pid = id & SCI_B_LIN_FRAME_ID_MASK;

    /* P0 = id0 ^ id1 ^ id2 ^ id4*/
    uint8_t tmp = (((id >> 0) ^ (id >> 1) ^ (id >> 2) ^ (id >> 4)) & 0x01);
    pid |= (uint8_t) (tmp << 6U);

    /* P1 = ~(id1 ^ id3 ^ id4 ^ id5) */
    tmp  = (uint8_t) ~(((id >> 1) ^ (id >> 3) ^ (id >> 4) ^ (id >> 5)) & 0x01);
    pid |= (uint8_t) (tmp << 7U);

    return pid;
}

#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Add byte to checksum
 *
 * @param[in] byte         Byte to add to current sum
 * @param[in] current_sum  Current checksum (intermediate sum)
 *
 * @retval       New checksum result (after adding byte)
 **********************************************************************************************************************/
static uint8_t r_sci_b_lin_checksum_add_byte_to_sum (uint8_t byte, uint8_t current_sum)
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

#endif

#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Initialize the checksum based on the checksum type
 *
 * @param[in] id                LIN unprotected frame identifier
 * @param[in] checksum_type     Checksum type (classic or enhanced)
 *
 * @retval   Initial checksum value for the provided checksum type
 **********************************************************************************************************************/
static uint8_t r_sci_b_lin_checksum_initialize (uint8_t id, lin_checksum_type_t checksum_type)
{
    uint8_t checksum = 0;

    if (LIN_CHECKSUM_TYPE_ENHANCED == checksum_type)
    {
        /* Compute PID and add to checksum. Enhanced checksum includes data and PID. Standard is data only. */
        checksum = r_sci_b_lin_pid_calculate(id);
    }

    return checksum;
}

#endif

#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Calculates the LIN checksum on data to be transmitted. For received frames,
 * the checksum is calculated incrementally with each byte.
 *
 * @param[in] id             LIN unprotected frame identifier.
 * @param[in] p_data         Pointer to data.
 * @param[in] num_bytes      Data frame data length.
 * @param[in] checksum_type  Checksum type (classic or enhanced). Frame ID 0x3C and 0x3D always use classic checksum.
 *
 * @retval                   LIN checksum result
 **********************************************************************************************************************/
static uint8_t r_sci_b_lin_checksum_calculate (uint8_t               id,
                                               uint8_t const * const p_data,
                                               uint8_t               num_bytes,
                                               lin_checksum_type_t   checksum_type)
{
    uint8_t checksum = r_sci_b_lin_checksum_initialize(id, checksum_type);

    for (uint8_t i = 0; i < num_bytes; i++)
    {
        checksum = r_sci_b_lin_checksum_add_byte_to_sum(p_data[i], checksum);
    }

    return (uint8_t) ~checksum;
}

#endif

/*******************************************************************************************************************//**
 * Initializes the SCI common (CCRn) and Simple LIN (XCRn) register settings.
 *
 * Initial settings are based on Figure 26.105 "Example of Start Frame Reception Flowchart" of the RA6T2 manual
 * R01UH0951EJ0130 and related Table 26.26 "Example flow of SCI initialization in asynchronous mode with non-FIFO selected."
 * of the RA6T2 manual R01UH0951EJ0130 (for CCRn settings).
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 **********************************************************************************************************************/
static void r_sci_b_lin_hw_configure (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    lin_cfg_t const * p_cfg = p_ctrl->p_cfg;
    sci_b_lin_extended_cfg_t const * const p_extend = (sci_b_lin_extended_cfg_t *) p_cfg->p_extend;
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

    /* Enable the SCI channel */
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);

    /* Ensure transmission and reception are disabled during initialization. */
    p_reg->CCR0 = 0;

    uint32_t xcr0;
    uint32_t xcr1;
    uint32_t xcr2;

    /* Make node-specific settings */
    if (LIN_MODE_SLAVE == p_cfg->mode)
    {
        xcr0 = SCI_B_LIN_XCR0_MASK_SLAVE;
        xcr1 = SCI_B_LIN_XCR1_MASK_SLAVE;

        /* Check all bits of CF0 when auto sync is disabled. When enabled, only check the bits received after synchronization. */
        uint32_t cf0ce =
            (UINT8_MAX << (p_extend->sci_b_settings_b.auto_synchronization * (uint8_t) SCI_B_LIN_SYNC_EDGES)) &
            UINT8_MAX;
        xcr2 = SCI_B_LIN_XCR2_MASK_SLAVE | (cf0ce << R_SCI_B0_XCR2_CF0CE_Pos);
    }
    else
    {
        xcr0 = SCI_B_LIN_XCR0_MASK_MASTER;
        xcr1 = SCI_B_LIN_XCR1_MASK_MASTER;
        xcr2 = SCI_B_LIN_XCR2_MASK_MASTER;
    }

    /* Configure LIN timer divider, bus collision, and priority interrupt settings */
    xcr0 |= ((uint32_t) p_extend->baud_setting.timer_setting.tcss << R_SCI_B0_XCR0_TCSS_Pos);
    xcr0 |= ((uint32_t) p_extend->sci_b_settings_b.bus_conflict_clock << R_SCI_B0_XCR0_BCCS_Pos);
    xcr0 |= ((uint32_t) p_extend->sci_b_settings_b.bus_conflict_detection << R_SCI_B0_XCR0_BCDIE_Pos);

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Configure AED interrupt. */
    xcr0 |= ((uint32_t) (p_extend->sci_b_settings_b.auto_synchronization) << R_SCI_B0_XCR0_AEDIE_Pos);
#endif

    /* Configure ID filter settings */
    r_sci_b_lin_filter_settings_configure(&xcr0, &xcr1, &p_extend->filter_setting);

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Configure auto synchronization setting. */
    xcr1 |= ((uint32_t) (p_extend->sci_b_settings_b.auto_synchronization) << R_SCI_B0_XCR1_BMEN_Pos);
#endif

    /* Configure LIN break field length setting */
    xcr2 |= ((uint32_t) p_extend->baud_setting.timer_setting.bflw << R_SCI_B0_XCR2_BFLW_Pos);

    /* Set required Simple LIN settings, and configured break delimeter length and clock source.*/
    uint32_t ccr3 = SCI_B_LIN_CCR3_MASK;
    ccr3 |= (uint32_t) p_extend->sci_b_settings_b.break_delimiter << R_SCI_B0_CCR3_STP_Pos;
    ccr3 |= (uint32_t) p_extend->sci_b_settings_b.clock_source << R_SCI_B0_CCR3_BPEN_Pos;

    /* Set baud rate */
    uint32_t ccr2 = p_extend->baud_setting.baudrate_bits;

    /* Apply noise filter setting. */
    uint32_t ccr1 = (uint32_t) p_extend->sci_b_settings_b.noise_cancel_clock << R_SCI_B0_CCR1_NFCS_Pos;
    ccr1 |= (uint32_t) p_extend->sci_b_settings_b.noise_cancel << R_SCI_B0_CCR1_NFEN_Pos;

    /* Write the settings to the SCI. Do not write XCR1 settings yet, they
     * must be set only after initializing the SCI CCRn registers according
     * to the flow chart. */
    p_reg->XCR0 = xcr0;
    p_reg->XCR1 = 0;
    p_reg->XCR2 = xcr2;

    /* Clear flags */
    r_sci_b_lin_flags_clear(p_ctrl->p_reg, SCI_B_LIN_CFCLR_CLEAR_LIN_FLAGS, SCI_B_LIN_XFCLR_CLEAR_LIN_FLAGS);

    /* Write the settings to the SCI control registers in the order specified by the initialization flow. */
    p_reg->CCR3 = ccr3;
    p_reg->CCR2 = ccr2;
    p_reg->CCR1 = ccr1;
    p_reg->CCR4 = 0;

    /* Enable reception. RE and RIE must be set simultaneously (see RA6T2 manual R01UH0951EJ0130 Table 26.26
     * "Example flow of SCI initialization in asynchronous mode with non-FIFO selected."). The CFCLR
     * flags do not need to be cleared here, as they were cleared above. */
    p_reg->CCR0 = (R_SCI_B0_CCR0_RE_Msk | R_SCI_B0_CCR0_RIE_Msk);

    /* Wait until internal state of RE is 1 as it takes some time for the state to be reflected internally after
     * rewriting the control register. Refer to "26.2.29 CESR : Communication Enable Status Register" description
     * in the RA6T2 manual R01UH0951EJ0100 or the relevant section for the MCU being used  */
    FSP_HARDWARE_REGISTER_WAIT(p_reg->CESR_b.RIST, 1U);

    /* Disable reception interrupts. Reception interrupts are re-enabled on break field detection or a call
     * to R_SCI_B_LIN_Read. RE must remain enabled to keep the clock to the noise filter circuit
     * enabled when the noise cancellation filter is used, as the noise filter circuit requires a clock for the SCI
     * to be able to detect the break field at RXDn. RE also needs to be enabled for the bus collision detection function. */
    p_reg->CCR0_b.RIE = 0;

    /* XCR1 settings should be applied after the SCI core settings have been made. */
    p_reg->XCR1 = xcr1;
}

/*******************************************************************************************************************//**
 * Configures the ID filter settings. Existing register settings are not modified.
 *
 * @param[out]  xcr0       Pointer to XCR0 variable to update
 * @param[out]  xcr1       Pointer to XCR1 settings variable to update
 * @param[in]   p_config   Configuration to apply
 *
 **********************************************************************************************************************/
static void r_sci_b_lin_filter_settings_configure (uint32_t * const                            xcr0,
                                                   uint32_t * const                            xcr1,
                                                   sci_b_lin_id_filter_setting_t const * const p_config)
{
    /* Apply XCR0 filter settings */
    *xcr0 |= ((uint32_t) p_config->priority_interrupt_bit_select << R_SCI_B0_XCR0_PIBS_Pos) |
             ((uint32_t) p_config->priority_interrupt_enable << R_SCI_B0_XCR0_PIBE_Pos) |
             ((uint32_t) p_config->compare_data_select << R_SCI_B0_XCR0_CF1DS_Pos);

    /* Apply XCR1 filter settings */
    *xcr1 |= ((uint32_t) p_config->compare_data_mask << R_SCI_B0_XCR1_CF1CE_Pos) |
             ((uint32_t) p_config->priority_compare_data << R_SCI_B0_XCR1_PCF1D_Pos) |
             ((uint32_t) p_config->secondary_compare_data << R_SCI_B0_XCR1_SCF1D_Pos);
}

/*******************************************************************************************************************//**
 * Clear LIN status flags (CFCLR and XFCLR)
 *
 * @param[in]  p_reg      SCI register pointer
 * @param[in]  cfclr      CFCLR flags to clear
 * @param[in]  xfclr      XFCLR flags to clear
 *
 **********************************************************************************************************************/
static void r_sci_b_lin_flags_clear (R_SCI_B0_Type * const p_reg, uint32_t cfclr, uint32_t xfclr)
{
    p_reg->CFCLR = cfclr;
    p_reg->XFCLR = xfclr;
}

/*******************************************************************************************************************//**
 * Enables the requested IRQ and sets the interrupt context
 *
 * @param[in]  irq        IRQ to enable
 * @param[in]  ipl        Interrupt priority
 * @param[in]  p_context  Pointer to interrupt context
 **********************************************************************************************************************/
static void r_sci_b_lin_irq_enable (IRQn_Type irq, uint8_t ipl, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, ipl, p_context);
    }
}

/*******************************************************************************************************************//**
 * Disables the requested IRQ.
 *
 * @param[in]  irq  IRQ to disable
 * @param[in]  ipl        Interrupt priority
 * @param[in]  p_context  Pointer to interrupt context
 **********************************************************************************************************************/
static void r_sci_b_lin_irq_disable (IRQn_Type irq, uint8_t ipl, void * p_context)
{
    /* Parameters unused to allow using same function signature in r_sci_b_lin_irqs_enable_disable which reduces codes size */
    FSP_PARAMETER_NOT_USED(ipl);
    FSP_PARAMETER_NOT_USED(p_context);

    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
    }
}

/*******************************************************************************************************************//**
 * Disables interrupt and clears pending status
 *
 * @param[in]  irq                       IRQ number for this interrupt
 **********************************************************************************************************************/
static void r_sci_b_lin_irq_cfg (IRQn_Type const irq)
{
    r_sci_b_lin_irq_disable(irq, 0, 0);

    if (irq >= 0)
    {
        R_BSP_IrqStatusClear(irq);
    }
}

/*******************************************************************************************************************//**
 * Intializes interrupts in the NVIC, but does not enable them
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 **********************************************************************************************************************/
static void r_sci_b_lin_irqs_cfg (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    lin_cfg_t const * p_cfg = p_ctrl->p_cfg;
    sci_b_lin_extended_cfg_t const * const p_extend = (sci_b_lin_extended_cfg_t *) p_cfg->p_extend;

    /* Required */
    r_sci_b_lin_irq_cfg(p_extend->rxi_irq);
    r_sci_b_lin_irq_cfg(p_extend->txi_irq);
    r_sci_b_lin_irq_cfg(p_extend->tei_irq);
    r_sci_b_lin_irq_cfg(p_extend->eri_irq);

    /* Slave mode only */
    r_sci_b_lin_irq_cfg(p_extend->bfd_irq);
#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE
    r_sci_b_lin_irq_cfg(p_extend->aed_irq);
#endif
}

/*******************************************************************************************************************//**
 * Enables or disables all LIN interrupts in the NVIC. Enable does not necessarily enable them in the SCI.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  irqEnableDisableFunc      r_sci_b_lin_irq_enable to enable interrupts. r_sci_b_lin_irq_disable to disable interrupts.
 **********************************************************************************************************************/
static void r_sci_b_lin_irqs_enable_disable (sci_b_lin_instance_ctrl_t * const p_ctrl,
                                             void (* irqEnableDisableFunc)(IRQn_Type irq, uint8_t ipl,
                                                                           void * p_context))
{
    lin_cfg_t const * p_cfg = p_ctrl->p_cfg;
    sci_b_lin_extended_cfg_t const * const p_extend = (sci_b_lin_extended_cfg_t *) p_cfg->p_extend;

    irqEnableDisableFunc(p_extend->rxi_irq, p_extend->rxi_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->txi_irq, p_extend->txi_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->tei_irq, p_extend->tei_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->eri_irq, p_extend->eri_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->bfd_irq, p_extend->bfd_ipl, p_ctrl);
#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE
    irqEnableDisableFunc(p_extend->aed_irq, p_extend->aed_ipl, p_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * Transmit the LIN frame
 *
 * Header frame transmission is based on flow chart process in Figure 26.101 "Start Frame Transmission Flowchart Example"
 * in R01UH0951EJ0130 manual. Initial settings of XCR0 and XCR2 have already been made in open.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  p_transfer_params         Pointer to the transfer parameters for the transfer
 * @param[in]  send_header               Set to true if the LIN header should be transmitted before the frame data (master mode only)
 *
 * @retval     FSP_SUCCESS               Transmission started successfully
 **********************************************************************************************************************/
static fsp_err_t r_sci_b_lin_write (sci_b_lin_instance_ctrl_t * const   p_ctrl,
                                    const lin_transfer_params_t * const p_transfer_params,
                                    uint8_t const                       send_header)
{
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

    /* Stop any in-progress break field transmission */
    p_reg->XCR1_b.TCST = 0;

    /* Disable transmit interrupts, reception interrupts, and transmission */
    p_reg->CCR0 &=
        (uint32_t) ~(R_SCI_B0_CCR0_TIE_Msk | R_SCI_B0_CCR0_TEIE_Msk | R_SCI_B0_CCR0_RIE_Msk | R_SCI_B0_CCR0_TE_Msk);

    /* Wait until internal state of TE is 0 as it takes some time for the state to be reflected internally after
     * rewriting the control register. Refer to "26.2.29 CESR : Communication Enable Status Register" description
     * in the RA6T2 manual R01UH0951EJ0100 or the relevant section for the MCU being used  */
    FSP_HARDWARE_REGISTER_WAIT(p_reg->CESR_b.TIST, 0U);

    /* Prepare the data transmission state. */
    p_ctrl->p_data       = p_transfer_params->p_data;
    p_ctrl->tx_src_bytes = 0;
    p_ctrl->event        = LIN_EVENT_NONE;
    p_ctrl->checksum     = 0;

    if (p_transfer_params->p_data)
    {
        p_ctrl->tx_src_bytes = p_transfer_params->num_bytes;

#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE
        if (p_transfer_params->checksum_type != LIN_CHECKSUM_TYPE_NONE)
        {
            /* If checksum generation is enabled, calculate the checksum */
            p_ctrl->checksum = r_sci_b_lin_checksum_calculate(p_transfer_params->id,
                                                              p_transfer_params->p_data,
                                                              p_transfer_params->num_bytes,
                                                              p_transfer_params->checksum_type);
            p_ctrl->tx_src_bytes++;
        }
        else
#endif
        {
            /* User requested not to append checksum. Therefore either we are not using a checksum,
             * or we are using a custom checksum. Copy last byte into 'checksum' field.
             * From txi_isr perspective, last byte is always read from checksum, regardless of
             * whether that byte represents a literal checksum. */
            p_ctrl->checksum = p_transfer_params->p_data[p_transfer_params->num_bytes - 1];
        }
    }

    if (send_header)
    {
        /* Set number of header bytes remaining to transmit */
        p_ctrl->tx_header_bytes = SCI_B_LIN_HEADER_NUM_BYTES;

        /* Save the PID of the last attempted transmit */
        p_ctrl->last_pid = r_sci_b_lin_pid_calculate(p_transfer_params->id);

        /* Ensure transmission is enabled. Do not set CCR0.TE and TIE to 1 at the same time to
         * avoid SCIn_TXI output before the Break Field */
        p_reg->CCR0 |= (uint32_t) (R_SCI_B0_CCR0_TE_Msk);

        /* Wait until internal state of TE is 1 as it takes some time for the state to be reflected
         * internally after rewriting the control register. Refer to "26.2.29 CESR : Communication
         * Enable Status Register" description in the RA6T2 manual R01UH0951EJ0100.  */
        FSP_HARDWARE_REGISTER_WAIT(p_reg->CESR_b.TIST, 1U);

        /* Enable transmit interrupt. Because BFOIE was set during SCI initialization,
         * a SCIn_TXI interrupt will be generated when break field output is complete */
        p_reg->CCR0 |= (uint32_t) (R_SCI_B0_CCR0_TIE_Msk);

        /* Clear flags */
        r_sci_b_lin_flags_clear(p_reg, SCI_B_LIN_CFCLR_CLEAR_LIN_FLAGS, SCI_B_LIN_XFCLR_CLEAR_LIN_FLAGS);

        /* Start outputting break field. */
        p_reg->XCR1_b.TCST = 1;
    }
    else
    {
        /* Clear flags */
        r_sci_b_lin_flags_clear(p_ctrl->p_reg, SCI_B_LIN_CFCLR_CLEAR_LIN_FLAGS, SCI_B_LIN_XFCLR_CLEAR_LIN_FLAGS);

        /* Enable transmit interrupt to start transmission. Setting TE and TIE together causes a
         * TXI interrupt which will kick of transmission of the first data byte. */
        p_reg->CCR0 |= (uint32_t) (R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_TIE_Msk);
    }

    return FSP_SUCCESS;
}

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Calculates the detected baud rate and updates the baud and break field threshold register settings to synchronize
 * with the master's rate.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *
 * @returns True if synchronization completed successfully, false if baud rate or timer setting is not possible in HW
 **********************************************************************************************************************/
static void r_sci_b_lin_aed_synchronize (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI_B0_Type * const p_reg = p_ctrl->p_reg;
    sci_b_lin_extended_cfg_t const * const p_extend     = (sci_b_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    sci_b_lin_clock_source_t               clock_source =
        (sci_b_lin_clock_source_t) p_extend->sci_b_settings_b.clock_source;
    sci_b_lin_bus_conflict_clock_t bccs =
        (sci_b_lin_bus_conflict_clock_t) p_extend->sci_b_settings_b.bus_conflict_clock;

    /* Calculate the baud rate from the measured bit time */
    uint32_t baudrate = (p_ctrl->timer_freq_hz * SCI_B_LIN_SYNC_EDGES) / p_ctrl->sync_bits_sum;

    /* Compute new BFLW setting. TCSS cannot be updated during reception. */
    uint32_t bflw_setting = (((p_ctrl->timer_freq_hz * (uint32_t) p_extend->break_bits) / baudrate) - 1UL);
    if (bflw_setting <= SCI_B_LIN_BFLW_MAX)
    {
        sci_b_lin_baud_params_t  baud_params = {baudrate, clock_source, bccs, p_extend->break_bits};
        sci_b_lin_baud_setting_t baud_setting;
        sci_b_lin_base_clock_t   abcs = (sci_b_lin_base_clock_t) p_extend->sci_b_settings_b.base_clock_cycles_per_bit;

        /* Calculate new baud setting. Only update register settings if they are possible in the hardware */
        if (FSP_SUCCESS ==
            r_sci_b_lin_baud_setting_calculate(&baud_params, abcs, false, &baud_setting))
        {
            /* Adjust new baud rate and BFLW setting.*/
            p_reg->XCR2_b.BFLW = (uint16_t) bflw_setting;
            p_reg->CCR2        = baud_setting.baudrate_bits;
        }
    }
}

#endif

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Check for errors in received AED measurement data. Because the AED interrupt detects edges, the level of the
 * RXDn line is of limited usefulness (it will always alternate between 0 and 1 as we expect in the sync byte because
 * we are detecting all edge changes). But in the event of a bit error, it will appear as if multiple bit times have
 * elapsed between edges instead of just 1. Comparing the duration of each bit to the avergae bit duration received
 * so far can detect bit errors/missed bits and avoid adjusting the baud rate to the wrong value.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  tcnt                      Latest tcnt measurement
 *
 * @returns true if an error occurred, false otherwise
 **********************************************************************************************************************/
static bool r_sci_b_lin_aed_latest_bit_has_error (sci_b_lin_instance_ctrl_t * const p_ctrl, uint16_t tcnt)
{
    bool has_error = false;

    if (p_ctrl->sync_bits_received)
    {
        int32_t avg_tcnt = (int32_t) (p_ctrl->sync_bits_sum / (uint32_t) p_ctrl->sync_bits_received);

        /* Compute absolute value of difference in bit duration */
        int32_t delta = avg_tcnt > tcnt ? (avg_tcnt - tcnt) : (tcnt - avg_tcnt);

        /* Check that this bit is within 12.5% of the duration of the average */
        int32_t threshold = (avg_tcnt >> 3U);
        has_error = delta > threshold;
    }

    return has_error;
}

#endif

/*******************************************************************************************************************//**
 * Handle error interrupt
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 **********************************************************************************************************************/
static lin_event_t r_sci_b_lin_eri_handler (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;
    uint32_t        ccr0  = p_reg->CCR0;

    /* If we are outputting break field, stop */
    p_reg->XCR1_b.TCST = 0;

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Reset bit rate measurement hardware state in preparation to receive next header (slave only) */
    r_sci_b_lin_aed_reset(p_ctrl);
#endif

    /* Suspend transmission and transmit interrupts, and reception interrupts */
    p_reg->CCR0 = ccr0 &
                  (uint32_t) ~(R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_TIE_Msk | R_SCI_B0_CCR0_TEIE_Msk |
                               R_SCI_B0_CCR0_RIE_Msk);

    /* Determine cause of error. */
    uint32_t    xsr    = p_ctrl->p_reg->XSR0;
    uint32_t    csr    = p_ctrl->p_reg->CSR;
    lin_event_t events = (lin_event_t) ((csr & SCI_B_LIN_ERI_CSR_EVENTS_MASK) | (xsr & SCI_B_LIN_ERI_XSR_EVENTS_MASK));

    /* Clear error conditions and discard RDR data. */
    r_sci_b_lin_flags_clear(p_ctrl->p_reg, SCI_B_LIN_ERROR_CSR_EVENTS_CLEAR_MASK,
                            SCI_B_LIN_ERROR_XSR_EVENTS_CLEAR_MASK);

    return events;
}

/*******************************************************************************************************************//**
 * Process received data byte and return an event if the user should be notified via callback. 0 is returned
 * if no event of user interest is detected.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @return     0 if no event present (rx still in progress), otherwise the lin_event_t to pass to the user callback
 **********************************************************************************************************************/
lin_event_t r_sci_b_lin_rxi_handler (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    lin_event_t     event = LIN_EVENT_NONE;
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;
    uint32_t        xsr0  = p_reg->XSR0;

    /* Check if control field 0 was received*/
    if (xsr0 & R_SCI_B0_XSR0_CF0MF_Msk)
    {
        /* Discard received data and clear the CF0 received flag to advance header reception state */
        r_sci_b_lin_flags_clear(p_reg, R_SCI_B0_CFCLR_RDRFC_Msk, R_SCI_B0_XFCLR_CF0MC_Msk);

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

        /* Disable bit rate measurement once CF0 is received. It will have been disabled already in the
         * AED handler if bit rate measurement completed successfully. But it is possible for bit rate
         * measurement to fail and the frame to still be received as long as the baud rates of sender
         * and receiver are close enough. */
        p_reg->XCR1_b.BMEN = 0;
#endif
    }
    /* Check if control field 1 was received */
    else if (xsr0 & (R_SCI_B0_XSR0_CF1MF_Msk | R_SCI_B0_XSR0_PIBDF_Msk))
    {
        /* Advance header reception state */
        p_reg->XFCLR = R_SCI_B0_XFCLR_CF1MC_Msk | R_SCI_B0_XFCLR_PIBDC_Msk;

        /* Read the received data */
        uint8_t pid = p_reg->RDR_BY;

        /* Set the event to notify the application (slave node only). */
        event = LIN_EVENT_RX_HEADER_COMPLETE;

        /* Check parity */
        if (r_sci_b_lin_pid_calculate(pid) != pid)
        {
            event = LIN_EVENT_ERR_PARITY;
        }
        else
        {
            /* Save received PID (Control Field 1) */
            p_ctrl->last_pid = pid;
        }
    }
    /* Data frame byte */
    else if (p_ctrl->rx_bytes_expected > p_ctrl->rx_bytes_received)
    {
        uint8_t bytes_remaining = p_ctrl->rx_bytes_expected - p_ctrl->rx_bytes_received;

        /* Read data byte from RDR */
        uint8_t rx_byte = p_reg->RDR_BY;

        /* Check if this is the last byte in the transfer */
        if (1 == bytes_remaining)
        {
            event = LIN_EVENT_RX_DATA_COMPLETE;

#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE

            /* Perform checksum validation if requested */
            if (p_ctrl->validate_checksum)
            {
                /* Validate checksum. At this point, p_ctrl->checksum contains the checksum over the data bytes. */
                if (((p_ctrl->checksum + rx_byte)) != SCI_B_LIN_CHECKSUM_OK)
                {
                    event = LIN_EVENT_ERR_INVALID_CHECKSUM;
                }

                /* Save the received checksum byte */
                p_ctrl->checksum = rx_byte;
            }
            else
#endif
            {
                /* Checksum validation skipped (nonstandard checksum or checksum not present).
                 * Store the received byte as data. */
                *p_ctrl->p_data++ = rx_byte;
                p_ctrl->rx_bytes_received++;
            }

            /* Data reception complete. Reset receive state and stop reception interrupts. */
            p_ctrl->rx_bytes_expected = 0;
            p_ctrl->p_data            = NULL;
            p_reg->CCR0_b.RIE         = 0;

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

            /* Reset bit rate measurement hardware state in preparation to receive next header (slave only) */
            r_sci_b_lin_aed_reset(p_ctrl);
#endif
        }
        /* Received a byte which is not the last byte */
        else
        {
#if SCI_B_LIN_CHECKSUM_SUPPORT_ENABLE

            /* Add the received byte to the running checksum */
            if (p_ctrl->validate_checksum)
            {
                p_ctrl->checksum = r_sci_b_lin_checksum_add_byte_to_sum(rx_byte, p_ctrl->checksum);
            }
#endif

            /* Store the received byte */
            *p_ctrl->p_data++ = rx_byte;
            p_ctrl->rx_bytes_received++;
        }
    }
    else
    {
        /* Byte received out of sequence or frame is ignored due to filering (no CF1 match). */

        /* Discard the byte */
        p_reg->CFCLR = R_SCI_B0_CFCLR_RDRFC_Msk;

        /* Stop reception interrupts. */
        p_reg->CCR0_b.RIE = 0;

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

        /* Reset bit rate measurement hardware state in preparation to receive next header (slave only) */
        r_sci_b_lin_aed_reset(p_ctrl);
#endif
    }

    return event;
}

/*******************************************************************************************************************//**
 * Transmit next data byte
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 **********************************************************************************************************************/
static void r_sci_b_lin_txi_handler (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

    /* Check for break field output completion flag */
    if (p_reg->XSR0 & R_SCI_B0_XSR0_BFOF_Msk)
    {
        /* Clear break field transmission complete. Currently the break delimeter is still being
         * transmitted. But we can still write the next byte to TDR. If transmit data is written
         * while the Break Delimiter length is being counted, transmission  does not start until
         * the Break Delimiter length counting is completed.*/
        p_reg->XFCLR = R_SCI_B0_XFCLR_BFOC_Msk;

        /* Clear framing error flag, as by definition, break field is a UART framing error */
        r_sci_b_lin_flags_clear(p_reg, R_SCI_B0_CFCLR_FERC_Msk, 0);
    }

    if (p_ctrl->tx_header_bytes || p_ctrl->tx_src_bytes)
    {
        /* Dummy read of RDR to prevent overrun errors during transmission. Although RIE is disabled
         * and ERI will not fire for reception errors, if a bus collision error occurs, ERI will fire
         * if BCDIE is set, and all current  errors will be reported (in addition to the bus collision).
         * In this case, any reception flags caused by not servicing RDR are not meaningful, so read RDR
         * to prevent these flags from getting set. */
        (void) p_reg->RDR;

        if (p_ctrl->tx_header_bytes)
        {
            /* Write the sync word if this is the first header byte. Otherwise, this is the second header byte (the PID). */
            p_reg->TDR = (SCI_B_LIN_HEADER_NUM_BYTES == p_ctrl->tx_header_bytes) ?
                         SCI_B_LIN_SYNC : p_ctrl->last_pid;

            p_ctrl->event = LIN_EVENT_TX_HEADER_COMPLETE;
            p_ctrl->tx_header_bytes--;
        }
        else if (1 < p_ctrl->tx_src_bytes)
        {
            /* Write next data byte */
            p_reg->TDR = *p_ctrl->p_data++;
            p_ctrl->tx_src_bytes--;
        }
        else
        {
            /* Write checksum byte when there is only 1 data byte remaining to transmit */
            p_reg->TDR           = p_ctrl->checksum;
            p_ctrl->event        = LIN_EVENT_TX_DATA_COMPLETE;
            p_ctrl->tx_src_bytes = 0;
        }

        if ((0 == p_ctrl->tx_header_bytes) && (0 == p_ctrl->tx_src_bytes))
        {
            /* After all data has been transmitted, disable transmit interrupts and enable the transmit end interrupt. */
            uint32_t ccr0_temp = p_reg->CCR0;
            ccr0_temp     |= R_SCI_B0_CCR0_TEIE_Msk;
            ccr0_temp     &= (uint32_t) ~(R_SCI_B0_CCR0_TIE_Msk);
            p_reg->CCR0    = ccr0_temp;
            p_ctrl->p_data = NULL;
        }
    }
}

/*******************************************************************************************************************//**
 * Handle break field detected
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 **********************************************************************************************************************/
static void r_sci_b_lin_bfd_handler (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI_B0_Type * const p_reg = p_ctrl->p_reg;

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Reset auto synchronization state */
    p_ctrl->sync_bits_received = 0;
    p_ctrl->sync_bits_sum      = 0;
#endif

    /* Clear flags that may have occurred while reception interrupts were disabled */
    r_sci_b_lin_flags_clear(p_reg, SCI_B_LIN_ERROR_CSR_EVENTS_CLEAR_MASK, SCI_B_LIN_ERROR_XSR_EVENTS_CLEAR_MASK);

    /* Enable reception interrupts to receive incoming data following the break field */
    p_reg->CCR0_b.RIE = 1;
}

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Resets bit rate measurement for the next frame by clearing SDST and BMEN, then resetting them at the same time.
 * 2 writes to XCR1 is required.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 **********************************************************************************************************************/
static void r_sci_b_lin_aed_reset (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    sci_b_lin_extended_cfg_t const * const p_extend = (sci_b_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    if (p_extend->sci_b_settings_b.auto_synchronization)
    {
        R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

        uint32_t xcr1            = p_reg->XCR1;
        uint32_t xcr1_aed_stop   = xcr1 & (uint32_t) ~(R_SCI_B0_XCR1_SDST_Msk | R_SCI_B0_XCR1_BMEN_Msk);
        uint32_t xcr1_aed_resume = xcr1 | (R_SCI_B0_XCR1_SDST_Msk | R_SCI_B0_XCR1_BMEN_Msk);

        /* Stop bit rate measurement and header reception */
        p_reg->XCR1 = xcr1_aed_stop;

        /* Reset bit rate measurement for next frame */
        p_reg->XCR1 = xcr1_aed_resume;
    }
}

/*******************************************************************************************************************//**
 * Handles active edge detection when auto synchronization is enabled.
 *
 * The AED interrupt triggers on the rising edge of the first data bit of control field 0, and on each subsequent
 * edge (rising or falling) of control field 0.
 *
 * @par Measurement Synchronization
 *
 * XSR1.TCNT contains the duration, in LIN timer ticks, since the previous detected edge. Since the value of control
 * field 0 is 0x55 (alternating ones and zeros), it can be used to measure the duration of each bit and update the
 * baud rate and break field width register settings. The LIN timer divider (TCSS) must not be updated during bit
 * rate measurement, because it is the timer used to measure the duration between the bits, and this would corrupt
 * the measurement.
 *
 * Every time a control field 0 edge is received, its duration is added to an accumulated sum.
 * On reception of each edge, if no error occurred, the bit duration is added to a running sum. Once
 * SCI_B_LIN_SYNC_EDGES are received, the average bit duration is calculated, and used
 * to estimate the baud rate and adjust the baud rate and break field threshold register settings.
 *
 * @par Measurement Error Avoidance
 *
 * On each edge (rising and falling) of control field 0, TCNT is read and compared to the previous TCNT capture.
 * If they differ by more than 12.5%, it is assumed that an error occurred, and the running sum is reset. If
 * SCI_B_LIN_SYNC_EDGES are received without error subsequent to the error, the bit rate can still be estimated.
 * Otherwise, the bit rate will not be updated.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 **********************************************************************************************************************/
static void r_sci_b_lin_aed_handler (sci_b_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI_B0_Type * p_reg = p_ctrl->p_reg;

    /* Get the bit duration (in LIN timer ticks) of the most recently received bit of
     * control field 0. XSR0.AEDF is cleared automatically upon reading. For the most
     * accurate measurement, read this register as early as possible in the ISR. */
    uint16_t tcnt = p_reg->XSR1_b.TCNT;

    /* Check for bit errors  */
    if (!r_sci_b_lin_aed_latest_bit_has_error(p_ctrl, tcnt))
    {
        p_ctrl->sync_bits_received++;
        p_ctrl->sync_bits_sum += tcnt;

        if (SCI_B_LIN_SYNC_EDGES == p_ctrl->sync_bits_received)
        {
            /* Perform synchronization. */
            r_sci_b_lin_aed_synchronize(p_ctrl);

            /* Once all sync edges are successfully received, disable bit rate measurement */
            p_reg->XCR1_b.BMEN = 0;
        }
    }
    else
    {
        /* Measurement error occurred, reset counters.
         *
         * Do not report an error (yet). The frame can stil be received, even if there was a
         * measurement error. If there is a reception error, it will be caught and handled in
         * the ERI handler.
         *
         * We do not set BMEN=0 here in case the measurement error is due to a new header
         * started during the previous CF0 reception. The SCI supports detection of a new break
         * field at any timing, including during reception of another header. Leaving BMEN
         * enabled allows us to synchronize again with the new header in this scenario. In
         * all other scenarios, BMEN will be set to 0 either in ERI (in case of error) or in RXI
         * (when CF0 is received) */
        p_ctrl->sync_bits_received = 0;
        p_ctrl->sync_bits_sum      = 0;
    }
}

#endif

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to LIN instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_sci_b_lin_call_callback (sci_b_lin_instance_ctrl_t * p_ctrl, lin_event_t event)
{
    lin_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    lin_callback_args_t * p_args = p_ctrl->p_callback_memory;
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

    p_args->channel        = p_ctrl->p_cfg->channel;
    p_args->event          = event;
    p_args->pid            = p_ctrl->last_pid;
    p_args->p_context      = p_ctrl->p_context;
    p_args->bytes_received = p_ctrl->rx_bytes_received;
    p_args->checksum       = p_ctrl->checksum;

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
        sci_b_lin_prv_ns_callback p_callback = (sci_b_lin_prv_ns_callback) (p_ctrl->p_callback);
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

/*******************************************************************************************************************//**
 * TXI interrupt processing for Simple LIN mode. TXI interrupt fires when the data in the data register has
 * been transferred to the data shift register, and the next data can be written.
 *
 * @retval    none
 **********************************************************************************************************************/
void sci_b_lin_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Transmit the next byte */
    r_sci_b_lin_txi_handler(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * RXI interrupt processing for Simple LIN mode. RXI interrupt fires when data arrives to the data register.
 *
 * @retval    none
 **********************************************************************************************************************/
void sci_b_lin_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Process the received data and determine whether there is a callback event present */
    lin_event_t event = r_sci_b_lin_rxi_handler(p_ctrl);

    /* If callback event occurred, call the callback */
    if (event)
    {
        r_sci_b_lin_call_callback(p_ctrl, event);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * TEI interrupt processing for Simple LIN mode. The TEI interrupt fires after the last byte is transmitted on the TX pin.
 *
 * @retval    none
 **********************************************************************************************************************/
void sci_b_lin_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disable transmission and transmit interrupts */
    p_ctrl->p_reg->CCR0 &= (uint32_t) ~(R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_TIE_Msk | R_SCI_B0_CCR0_TEIE_Msk);

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

    /* Reset bit rate measurement hardware state in preparation to receive next header (slave only) */
    r_sci_b_lin_aed_reset(p_ctrl);
#endif

    /* Call user callback */
    if (p_ctrl->event)
    {
        r_sci_b_lin_call_callback(p_ctrl, p_ctrl->event);
    }

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ERI interrupt processing for Simple LIN mode. The ERI interrupt fires when an error that is detectable by the SCI
 * hardware occurs.
 *
 * @retval    none
 **********************************************************************************************************************/
void sci_b_lin_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Determine the error event */
    lin_event_t event = r_sci_b_lin_eri_handler(p_ctrl);

    /* Call user callback */
    r_sci_b_lin_call_callback(p_ctrl, event);

    /* Stop any in progress transmission/reception */
    p_ctrl->rx_bytes_expected = 0;
    p_ctrl->rx_bytes_received = 0;
    p_ctrl->tx_src_bytes      = 0;
    p_ctrl->tx_header_bytes   = 0;
    p_ctrl->p_data            = NULL;
    p_ctrl->event             = LIN_EVENT_NONE;

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * BFD interrupt processing for Simple LIN mode. The BFD interrupt fires when a break field is detected by the hardware,
 * signaling the start of a LIN frame (slave only).
 *
 * A break field detection may occur at any time, even interrupting the reception of data.
 *
 * @retval    none
 **********************************************************************************************************************/
void sci_b_lin_bfd_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Check if break field was detected. XSR0.BFDF must be confirmed according to Figure 26.105
     * "Example of Start Frame Reception Flowchart" of the RA6T2 manual R01UH0951EJ0130  */
    if (p_ctrl->p_reg->XSR0 & R_SCI_B0_XSR0_BFDF_Msk)
    {
        r_sci_b_lin_bfd_handler(p_ctrl);
    }

    /* Clearing the IR bit must be done after clearing the interrupt source in the the peripheral for level interrupts */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if SCI_B_LIN_AUTO_SYNC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Active edge detection interrupt processing for Simple LIN mode auto synchronization during control field 0 reception
 * (slave only).
 *
 * @retval    none
 **********************************************************************************************************************/
void sci_b_lin_aed_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_b_lin_instance_ctrl_t * p_ctrl = (sci_b_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Process the edge detect event */
    r_sci_b_lin_aed_handler(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif
