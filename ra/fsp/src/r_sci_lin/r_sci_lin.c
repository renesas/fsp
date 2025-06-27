/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sci_lin.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

#define SCI_LIN_FRAME_ID_MASK                   (0x3FU)

/* "LIN" in ASCII.  Used to determine if the control block is open. */
#define SCI_LIN_OPEN                            (0x4C494EU)

/* Max/Min value of break field length */
#define SCI_LIN_MAX_TIMER_INTERVAL              (0x10000)

/* Range of LIN timer supported TCSS values */
#define SCI_LIN_TCSS_MIN                        (SCI_LIN_TIMER_DIV_1)
#define SCI_LIN_TCSS_MAX                        (SCI_LIN_TIMER_DIV_128)
#define SCI_LIN_TCSS_MASK                       (0x07U)

/* Max value of CKS for setting baud rate */
#define SCI_LIN_CKS_MAX                         (3U)

#define SCI_LIN_MIN_BAUD_DIVISOR_SHIFT          (5)

/* Used to validate the checksum of received data */
#define SCI_LIN_CHECKSUM_OK                     (0xFFU)

/* LIN Sync Word (Control Field 0) */
#define SCI_LIN_SYNC                            (0x55U)

/* Header data length */
#define SCI_LIN_HEADER_NUM_BYTES                (2U)

/* SCI SCR register initial value */
#define SCI_LIN_SCR_INITIAL_VALUE               (0U)

/* SCI CR1 register masks */
#define SCI_LIN_CR1_MASK_SLAVE                  (R_SCI0_CR1_BFE_Msk | R_SCI0_CR1_CF0RE_Msk)

/* SCI CR3 register masks */
#define SCI_LIN_CR3_MASK_SLAVE                  (R_SCI0_CR3_SDST_Msk)

/* SCI CF0DR register masks */
#define SCI_LIN_CF0DR_MASK_SLAVE                (SCI_LIN_SYNC)

/* SCI CF0CR register masks */
#define SCI_LIN_CF0CR_MASK_SLAVE                (0xFFU)

/* SCI SCMR register masks */
#define SCI_LIN_SCMR_DEFAULT_VALUE              (0xF2U)

/* SCI PCR register masks */
#define SCI_LIN_PCR_DEFAULT_VALUE               (0U)

/* SCI STCR register masks */
#define SCI_LIN_STCR_CLEAR_MASK                 (R_SCI0_STCR_BFDCL_Msk | R_SCI0_STCR_CF0MCL_Msk |  \
                                                 R_SCI0_STCR_CF1MCL_Msk | R_SCI0_STCR_PIBDCL_Msk | \
                                                 R_SCI0_STCR_BCDCL_Msk | R_SCI0_STCR_AEDCL_Msk)
#define SCI_LIN_ERROR_STCR_EVENTS_CLEAR_MASK    (R_SCI0_STCR_BFDCL_Msk | R_SCI0_STCR_BCDCL_Msk | \
                                                 R_SCI0_STCR_AEDCL_Msk)

/* SCI SSR register masks */
#define SCI_LIN_SSR_CLEAR_MASK                  (R_SCI0_SSR_PER_Msk | R_SCI0_SSR_FER_Msk | \
                                                 R_SCI0_SSR_ORER_Msk | R_SCI0_SSR_RDRF_Msk)
#define SCI_LIN_ERROR_SSR_EVENTS_CLEAR_MASK     (SCI_LIN_SSR_CLEAR_MASK)

/* SCI ICR register masks for Slave */
#define SCI_LIN_ICR_CONTROL_FIELD_MASK          (R_SCI0_ICR_CF0MIE_Msk | R_SCI0_ICR_CF1MIE_Msk)

/* SCI TMR register masks */
#define SCI_LIN_TIMER_MODE                      (0U)
#define SCI_LIN_BREAK_FIELD_OUTPUT_MODE         (2U)
#define SCI_LIN_TIMER_DETERMINATION_MASK        (1U << R_SCI0_TMR_TOMS_Pos)
#define SCI_LIN_TIMER_OUTPUT_MASK               (2U << R_SCI0_TMR_TOMS_Pos)

/* SCI FCR register default value */
#define SCI_LIN_FCR_DEFAULT_VALUE               (0xF800U)

/* SCI SIMR1 register default value */
#define SCI_LIN_SIMR1_DEFAULT_VALUE             (0U)

/* SCI SPMR register default value */
#define SCI_LIN_SPMR_DEFAULT_VALUE              (0U)

/* SCI MDDR register default value */
#define SCI_LIN_MDDR_DEFAULT_VALUE              (0xFFU)

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * sci_lin_prv_ns_callback)(lin_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile sci_lin_prv_ns_callback)(lin_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 * Private function prototypes
 *********************************************************************************************************************/

/* PID and checksum helper functions */
static uint8_t r_sci_lin_pid_calculate(uint8_t id);

#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE
static uint8_t r_sci_lin_checksum_calculate(uint8_t               id,
                                            uint8_t const * const p_data,
                                            uint8_t               num_bytes,
                                            lin_checksum_type_t   checksum_type);
static uint8_t r_sci_lin_checksum_initialize(uint8_t id, lin_checksum_type_t checksum_type);
static uint8_t r_sci_lin_checksum_add_byte_to_sum(uint8_t byte, uint8_t current_sum);

#endif

/* Initialization helper functions */
static void        r_sci_lin_hw_configure(sci_lin_instance_ctrl_t * const p_ctrl);
static void        r_sci_lin_irq_cfg(IRQn_Type const irq);
static void        r_sci_lin_irqs_cfg(sci_lin_instance_ctrl_t * const p_ctrl);
static void        r_sci_lin_irq_enable(IRQn_Type irq, uint8_t ipl, void * p_context);
static void        r_sci_lin_irq_disable(IRQn_Type irq, uint8_t ipl, void * p_context);
static inline void r_sci_lin_irqs_enable_disable(sci_lin_instance_ctrl_t * const p_ctrl,
                                                 void (                        * irqEnableDisableFunc)(
                                                     IRQn_Type                   irq,
                                                     uint8_t                     ipl,
                                                     void                      * p_context));

#if (SCI_LIN_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t r_sci_lin_common_parameter_checking(sci_lin_instance_ctrl_t const * const p_ctrl);
static fsp_err_t r_sci_lin_read_write_parameter_checking(sci_lin_instance_ctrl_t const * const p_ctrl,
                                                         lin_transfer_params_t const * const   p_transfer_params);

#endif

/* Transmission/reception helper functions */
static fsp_err_t r_sci_lin_write(sci_lin_instance_ctrl_t * const     p_ctrl,
                                 const lin_transfer_params_t * const p_transfer_params,
                                 uint8_t const                       send_header);

static void        r_sci_lin_call_callback(sci_lin_instance_ctrl_t * p_ctrl, lin_event_t event);
static lin_event_t r_sci_lin_rxi_handler(sci_lin_instance_ctrl_t * const p_ctrl);
static void        r_sci_lin_txi_handler(sci_lin_instance_ctrl_t * const p_ctrl);
static lin_event_t r_sci_lin_eri_handler(sci_lin_instance_ctrl_t * const p_ctrl);
static void        r_sci_lin_scix0_handler(sci_lin_instance_ctrl_t * const p_ctrl);
static lin_event_t r_sci_lin_scix1_handler(sci_lin_instance_ctrl_t * const p_ctrl);

#if SCI_LIN_BUS_CONFLICT_DETECTION_SUPPORT_ENABLE
static lin_event_t r_sci_lin_scix2_handler(sci_lin_instance_ctrl_t * const p_ctrl);

#endif

/* Baud and timing helper functions */
static fsp_err_t r_sci_lin_baud_setting_calculate(sci_lin_baud_params_t const * const p_baud_params,
                                                  sci_lin_baud_setting_t * const      p_baud_setting);
static fsp_err_t r_sci_lin_timer_setting_calculate(sci_lin_baud_params_t const * const p_baud_params,
                                                   sci_lin_timer_setting_t * const     p_timer_setting);

static void r_sci_lin_flags_clear(R_SCI0_Type * const p_reg, uint8_t ssr, uint8_t stcr);
static void r_sci_lin_break_field_detection_reset(sci_lin_instance_ctrl_t * const p_ctrl);
static void r_sci_lin_transfer_state_reset(sci_lin_instance_ctrl_t * const p_ctrl);

/**********************************************************************************************************************
 * ISR prototypes
 *********************************************************************************************************************/
void sci_lin_rxi_isr(void);
void sci_lin_tei_isr(void);
void sci_lin_txi_isr(void);
void sci_lin_eri_isr(void);
void sci_lin_scix0_isr(void);
void sci_lin_scix1_isr(void);
void sci_lin_scix2_isr(void);

/**********************************************************************************************************************
 * Global variables
 *********************************************************************************************************************/

/* LIN on SCI HAL API mapping for LIN interface */
const lin_api_t g_lin_on_sci =
{
    .open                  = R_SCI_LIN_Open,
    .write                 = R_SCI_LIN_Write,
    .read                  = R_SCI_LIN_Read,
    .communicationAbort    = R_SCI_LIN_CommunicationAbort,
    .callbackSet           = R_SCI_LIN_CallbackSet,
    .close                 = R_SCI_LIN_Close,
    .sleepEnter            = R_SCI_LIN_SleepEnter,
    .sleepExit             = R_SCI_LIN_SleepExit,
    .wakeupSend            = R_SCI_LIN_WakeupSend,
    .informationFrameRead  = R_SCI_LIN_InformationFrameRead,  // [DEPRECATED]
    .startFrameWrite       = R_SCI_LIN_StartFrameWrite,       // [DEPRECATED]
    .informationFrameWrite = R_SCI_LIN_InformationFrameWrite, // [DEPRECATED]
};

/******************************************************************************************************************//**
 * @addtogroup SCI_LIN
 * @{
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Functions
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * Configures the LIN driver channel based on the input configuration.
 *
 * Implements @ref lin_api_t::open.
 *
 * Example:
 * @snippet r_sci_lin_example.c R_SCI_LIN_Open
 *
 * @retval  FSP_SUCCESS                    Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to LIN control block or configuration structure is NULL.
 * @retval  FSP_ERR_INVALID_CHANNEL        The requested channel does not exist on this MCU or the channel does not
 *                                         support LIN mode.
 * @retval  FSP_ERR_ALREADY_OPEN           Control block has already been opened or channel is being used by another
 *                                         instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_MODE           Setting not supported for selected mode
 *
 * @return                                 See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                         possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_Open (lin_ctrl_t * const p_api_ctrl, lin_cfg_t const * const p_cfg)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_cfg->p_callback);

    /* Check control block isn't already open */
    FSP_ERROR_RETURN(p_ctrl->open != SCI_LIN_OPEN, FSP_ERR_ALREADY_OPEN);

    /* Make sure this channel supports LIN Mode (some MCUs do not support it on all SCI channels) */
    FSP_ERROR_RETURN(BSP_FEATURE_SCI_LIN_CHANNELS & (1U << p_cfg->channel), FSP_ERR_INVALID_CHANNEL);

    sci_lin_extended_cfg_t const * const p_extend = (sci_lin_extended_cfg_t *) p_cfg->p_extend;

    /* Check for required IRQs */
    FSP_ASSERT(p_extend->rxi_irq >= 0);
    FSP_ASSERT(p_extend->txi_irq >= 0);
    FSP_ASSERT(p_extend->tei_irq >= 0);
    FSP_ASSERT(p_extend->eri_irq >= 0);
    FSP_ASSERT(p_extend->scix0_irq >= 0);
    if (LIN_MODE_SLAVE == p_cfg->mode)
    {
        FSP_ASSERT(p_extend->scix1_irq >= 0);
    }
#endif

    /* Initialize control block */
    p_ctrl->p_reg =
        (R_SCI0_Type *) (R_SCI0_BASE + ((R_SCI1_BASE - R_SCI0_BASE) * p_cfg->channel));
    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

    /* Initialize variables preparing for transmission/reception */
    r_sci_lin_transfer_state_reset(p_ctrl);

    /* Configure, but do not enable the interrupts in the NVIC */
    r_sci_lin_irqs_cfg(p_ctrl);

    /* Initialize the SCI in LIN mode. */
    r_sci_lin_hw_configure(p_ctrl);

    /* Mark the control block as open */
    p_ctrl->open = SCI_LIN_OPEN;

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
 * @snippet r_sci_lin_example.c R_SCI_LIN_Write
 *
 * @retval  FSP_SUCCESS              Data transmission started successfully.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0
 *                                   bytes length provided
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call
 *                                   R_SCI_LIN_CommunicationAbort to cancel it if desired, or wait for the current
 *                                   transfer operation to complete before starting a new one.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                   possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_Write (lin_ctrl_t * const p_api_ctrl, const lin_transfer_params_t * const p_transfer_params)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_transfer_params);
    fsp_err_t err = r_sci_lin_read_write_parameter_checking(p_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Send the header before the data in master mode only */
    uint8_t send_header = LIN_MODE_MASTER == p_ctrl->p_cfg->mode;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE

    /* Check ID is at most 6 bits (only for master header transmission) */
    FSP_ERROR_RETURN((0 == (p_transfer_params->id & 0xC0)) || !send_header, FSP_ERR_INVALID_ARGUMENT);

    /* Check p_data is not null in slave mode */
    FSP_ASSERT(NULL != p_transfer_params->p_data || send_header);
#endif

    return r_sci_lin_write(p_ctrl, p_transfer_params, send_header);
}

/******************************************************************************************************************//**
 * Begins non-blocking data reception to receive user specified number of bytes into destination
 * buffer pointer.
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
 * On successful data reception completion, the callback is called with event
 * @ref lin_event_t::LIN_EVENT_RX_DATA_COMPLETE.
 *
 * Implements @ref lin_api_t::read.
 *
 * Example:
 * @snippet r_sci_lin_example.c R_SCI_LIN_Read
 *
 * @retval  FSP_SUCCESS              Data reception started successfully.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0
 *                                   bytes length provided
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call
 *                                   R_SCI_LIN_CommunicationAbort to cancel it if desired, or wait for the current
 *                                   transfer operation to complete before starting a new one.
 * @retval  FSP_ERR_INVALID_CALL     Data reception is not possible because a header frame has not been received yet
 *                                   (slave mode only).
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                   possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_Read (lin_ctrl_t * const p_api_ctrl, lin_transfer_params_t * const p_transfer_params)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_lin_read_write_parameter_checking(p_api_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    FSP_ASSERT(NULL != p_transfer_params->p_data);
#endif

    R_SCI0_Type * p_reg = p_ctrl->p_reg;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE

    /* In slave mode, check that data reception is possible (due to successful header reception) */
    FSP_ERROR_RETURN((LIN_MODE_MASTER == p_ctrl->p_cfg->mode) || (0 == (R_SCI0_CR0_SFSF_Msk & p_reg->CR0)),
                     FSP_ERR_INVALID_CALL);
#endif

    /* Disable reception interrupts */
    uint8_t scr = p_reg->SCR;
    p_reg->SCR = scr & (uint8_t) ~R_SCI0_SCR_RIE_Msk;

    /* Prepare receive state */
    p_ctrl->p_data            = p_transfer_params->p_data;
    p_ctrl->rx_bytes_expected = p_transfer_params->num_bytes;
    p_ctrl->rx_bytes_received = 0;
    p_ctrl->checksum          = 0;

#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE
    p_ctrl->validate_checksum = p_transfer_params->checksum_type != LIN_CHECKSUM_TYPE_NONE;

    /* Initialize checksum tracking fields */
    if (p_ctrl->validate_checksum)
    {
        p_ctrl->rx_bytes_expected++;
        p_ctrl->checksum = r_sci_lin_checksum_initialize(p_transfer_params->id, p_transfer_params->checksum_type);
    }
#endif

    /* Enable reception interrupts */
    p_reg->SSR &= (uint8_t) (~SCI_LIN_ERROR_SSR_EVENTS_CLEAR_MASK);
    p_reg->SCR  = scr | R_SCI0_SCR_RIE_Msk;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Cancels in progress frame data read or write, or header read or write. Break field reception cannot be
 * cancelled. For slave nodes, reception of a new header is still enabled after a call to this function.
 *
 * Implements @ref lin_api_t::communicationAbort.
 *
 * @retval  FSP_SUCCESS              Data transfer aborted successfully or no transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block is NULL.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                   possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_CommunicationAbort (lin_ctrl_t * const p_api_ctrl)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    /* Disable transmit interrupts, transmission, and reception interrupts */
    p_reg->SCR &=
        (uint8_t) ~(R_SCI0_SCR_TIE_Msk | R_SCI0_SCR_TEIE_Msk | R_SCI0_SCR_RIE_Msk | R_SCI0_SCR_TE_Msk);

    /* Reset any in progress transmission/reception */
    r_sci_lin_transfer_state_reset(p_ctrl);

    /* Reset break field detection in slave mode */
    r_sci_lin_break_field_detection_reset(p_ctrl);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 *
 * Implements @ref lin_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to LIN control block or callback is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 *
 * @return                               See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                       possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_CallbackSet (lin_ctrl_t * const          p_api_ctrl,
                                 void (                    * p_callback)(lin_callback_args_t *),
                                 void * const                p_context,
                                 lin_callback_args_t * const p_callback_memory)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_callback);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SCI_LIN_CFG_PARAM_CHECKING_ENABLE

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

/******************************************************************************************************************//**
 * Calculates baud rate and LIN timer (TCNT, TPRE and TCSS) register settings. This function evaluates and determines
 * the most accurate settings for the baud rate and timer related registers.
 *
 * The LIN timer setting is used for break field transmission/detection. Because the timer setting is specified in
 * terms of bits, and the duration of a bit varies depending on baud rate, the baud rate register settings and timer
 * register settings are related. The smallest possible LIN timer divider which can achieve the desired break field
 * bits setting at the configured baud rate is selected to provide the highest measurement accuracy.
 *
 * The baud rate cannot be updated at runtime with this function. This function is provided to ease configuration of
 * the initial baud settings.
 *
 * @param[in]  p_baud_params          Parameters required to calculate the baud rate
 * @param[out] p_baud_setting         If calculation succeeds, contains computed values to achieve requested baud rate.
 *                                    If calculation fails, the input structure is not modified.
 *
 * @retval  FSP_SUCCESS               Register settings updated in provided p_baud_setting
 * @retval  FSP_ERR_ASSERTION         p_baud_setting was NULL
 * @retval  FSP_ERR_INVALID_ARGUMENT  Cannot achieve combination of break field bits and baudrate with provided
 *                                    settings or p_baud_params->baudrate was 0 or p_baud_params->break_bits was 0
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_BaudCalculate (sci_lin_baud_params_t const * const p_baud_params,
                                   sci_lin_baud_setting_t * const      p_baud_setting)
{
#if (SCI_LIN_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_baud_params);
    FSP_ASSERT(p_baud_setting);
    FSP_ERROR_RETURN((0U != p_baud_params->break_bits), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0U != p_baud_params->baudrate), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((1U <= p_baud_params->delimiter_bits), FSP_ERR_INVALID_ARGUMENT);
#endif

    fsp_err_t err;

    /* Use temp variable in order to not update output arg unless both baud and timer calculations succeed */
    sci_lin_baud_setting_t tmp_baud_setting;

    err = r_sci_lin_baud_setting_calculate(p_baud_params, &tmp_baud_setting);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = r_sci_lin_timer_setting_calculate(p_baud_params, &tmp_baud_setting.timer_setting);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    *p_baud_setting = tmp_baud_setting;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Set the the ID filter settings for filtering control field 1 (PID byte).
 *
 * NOTE: Setting the ID filter will abort any in-progress LIN header reception, as the ID filter
 * settings cannot be changed during reception of the header. The next header will be received with the
 * new settings.
 *
 * @snippet r_sci_lin_example.c R_SCI_LIN_IdFilterSet
 *
 * @param[in]  p_api_ctrl           Pointer to the LIN control block.
 * @param[in]  p_config             The ID filter settings to apply
 *
 * @retval  FSP_SUCCESS              ID filter updated successfully.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block or p_config is NULL.
 * @retval  FSP_ERR_INVALID_MODE     Function called by master node (not supported for master nodes)
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                   possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_IdFilterSet (lin_ctrl_t * const p_api_ctrl, sci_lin_id_filter_setting_t const * const p_config)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_config);

    /* Function only supported for slave mode */
    FSP_ERROR_RETURN(LIN_MODE_SLAVE == p_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
#endif

    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    uint8_t cr1 = p_reg->CR1;
    uint8_t icr = p_reg->ICR;

    /* Clear CR3.SDST and ESMER.ESME will initialize the HW and allow to set a new filter. */
    p_reg->CR3   = 0;
    p_reg->ESMER = 0;

    /* Clear current CR1 filter settings and apply new setting for CR1 */
    cr1 &= (uint8_t) ~(R_SCI0_CR1_PIBS_Msk | R_SCI0_CR1_PIBE_Msk | R_SCI0_CR1_CF1DS_Msk);
    cr1 |= (p_config->priority_interrupt_bit_select << R_SCI0_CR1_PIBS_Pos) |
           (p_config->priority_interrupt_enable << R_SCI0_CR1_PIBE_Pos) |
           (p_config->compare_data_select << R_SCI0_CR1_CF1DS_Pos);

    /* Apply new setting for all related register */
    p_reg->CR1    = cr1;
    p_reg->CF1CR  = p_config->compare_data_mask;
    p_reg->PCF1DR = p_config->primary_compare_data;
    p_reg->SCF1DR = p_config->secondary_compare_data;

    p_reg->ICR = (icr & (uint8_t) ~((uint8_t) R_SCI0_ICR_PIBDIE_Msk)) |
                 (uint8_t) (p_config->priority_interrupt_enable << R_SCI0_ICR_PIBDIE_Pos);

    /* After setting new filter, enable CR3.SDST and ESMER.ESME */
    p_reg->ESMER = R_SCI0_ESMER_ESME_Msk;
    p_reg->CR3   = SCI_LIN_CR3_MASK_SLAVE;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
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
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                   possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_IdFilterGet (lin_ctrl_t * const p_api_ctrl, sci_lin_id_filter_setting_t * const p_config)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_config);

    /* Function only supported for slave mode */
    FSP_ERROR_RETURN(LIN_MODE_SLAVE == p_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
#endif

    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    uint16_t cr1    = p_reg->CR1;
    uint8_t  cf1cr  = p_reg->CF1CR;
    uint8_t  pcf1dr = p_reg->PCF1DR;
    uint8_t  scf1dr = p_reg->SCF1DR;

    p_config->compare_data_mask             = cf1cr;
    p_config->primary_compare_data          = pcf1dr;
    p_config->secondary_compare_data        = scf1dr;
    p_config->priority_interrupt_bit_select = (uint8_t) ((cr1 & R_SCI0_CR1_PIBS_Msk) >> R_SCI0_CR1_PIBS_Pos);
    p_config->priority_interrupt_enable     = (uint8_t) ((cr1 & R_SCI0_CR1_PIBE_Msk) >> R_SCI0_CR1_PIBE_Pos);
    p_config->compare_data_select           = (uint8_t) ((cr1 & R_SCI0_CR1_CF1DS_Msk) >> R_SCI0_CR1_CF1DS_Pos);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Closes the LIN driver.
 *
 * Implements @ref lin_api_t::close.
 *
 * Example:
 * @snippet r_sci_lin_example.c R_SCI_LIN_Close
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                   possible return codes.
 *********************************************************************************************************************/
fsp_err_t R_SCI_LIN_Close (lin_ctrl_t * const p_api_ctrl)
{
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_sci_lin_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    /* Disable transmission and reception */
    p_reg->SCR   = SCI_LIN_SCR_INITIAL_VALUE;
    p_reg->ESMER = 0;
    p_reg->CR3   = 0;
    p_reg->TCR   = 0;

    /* Disable irqs */
    r_sci_lin_irqs_enable_disable(p_ctrl, r_sci_lin_irq_disable);

    /* Disable the clock to the SCI channel. */
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_ctrl->p_cfg->channel);

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Send wakeup is not supported on the SCI LIN driver.
 *
 * Implements @ref lin_api_t::wakeupSend.
 *
 * @retval FSP_ERR_UNSUPPORTED       Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SCI_LIN_WakeupSend (lin_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Sleep is not supported on the SCI LIN driver.
 *
 * Implements @ref lin_api_t::sleepEnter.
 *
 * @retval FSP_ERR_UNSUPPORTED       Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SCI_LIN_SleepEnter (lin_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Sleep is not supported on the SCI LIN driver.
 *
 * Implements @ref lin_api_t::sleepExit.
 *
 * @retval FSP_ERR_UNSUPPORTED       Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SCI_LIN_SleepExit (lin_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SCI_LIN_Read.
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_LIN_InformationFrameRead (lin_ctrl_t * const            p_api_ctrl,
                                          lin_transfer_params_t * const p_transfer_params)
{
    return R_SCI_LIN_Read(p_api_ctrl, p_transfer_params);
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SCI_LIN_Write
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_LIN_StartFrameWrite (lin_ctrl_t * const p_api_ctrl, uint8_t const id)
{
    lin_transfer_params_t params =
    {
        .id            = id,
        .p_data        = NULL,
        .num_bytes     = 0,
        .checksum_type = LIN_CHECKSUM_TYPE_NONE
    };

#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = r_sci_lin_read_write_parameter_checking(p_ctrl, &params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check ID is at most 6 bits */
    FSP_ERROR_RETURN(0 == (id & 0xC0), FSP_ERR_INVALID_ARGUMENT);

    /* Function only supported for master mode */
    FSP_ERROR_RETURN(LIN_MODE_MASTER == p_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
#endif

    return r_sci_lin_write(p_api_ctrl, &params, true);
}

/*******************************************************************************************************************//**
 * [DEPRECATED] Use @ref R_SCI_LIN_Write
 *
 * @return      See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SCI_LIN_InformationFrameWrite (lin_ctrl_t * const                  p_api_ctrl,
                                           const lin_transfer_params_t * const p_transfer_params)
{
#if SCI_LIN_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err =
        r_sci_lin_read_write_parameter_checking((sci_lin_instance_ctrl_t *) p_api_ctrl, p_transfer_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    FSP_ASSERT(NULL != p_transfer_params->p_data);
#endif

    return r_sci_lin_write(p_api_ctrl, p_transfer_params, false);
}

/******************************************************************************************************************//**
 * @} (end addtogroup SCI_LIN)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private Functions
 *********************************************************************************************************************/

#if (SCI_LIN_CFG_PARAM_CHECKING_ENABLE)

/******************************************************************************************************************//**
 * Verifies the control structure is not NULL and the module is open. This reduces code size when parameter checking is
 * enabled.
 *
 * @param[in] p_ctrl                    Pointer to the control block for the channel
 *
 * @retval FSP_SUCCESS                  No error detected.
 * @retval FSP_ERR_ASSERTION            NULL input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 *********************************************************************************************************************/
static fsp_err_t r_sci_lin_common_parameter_checking (sci_lin_instance_ctrl_t const * const p_ctrl)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SCI_LIN_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Parameter error check function for R_SCI_LIN_Write and R_SCI_LIN_Read
 *
 * @param[in] p_ctrl             Pointer to the control block for the channel
 * @param[in] p_transfer_params  Pointer to the transfer parameters for the transfer
 *
 * @retval  FSP_SUCCESS              No parameter error found
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened
 * @retval  FSP_ERR_IN_USE           A transmission or reception is currently in progress. Call
 *                                   R_SCI_LIN_CommunicationAbort to cancel it if desired, or wait for the current
 *                                   transfer operation to complete before starting a new one.
 * @retval  FSP_ERR_ASSERTION        Pointer to LIN control block, transfer parameters, or tx/rx buffer is NULL, or 0
 *                                   bytes length provided
 *********************************************************************************************************************/
static fsp_err_t r_sci_lin_read_write_parameter_checking (sci_lin_instance_ctrl_t const * const p_ctrl,
                                                          lin_transfer_params_t const * const   p_transfer_params)
{
    fsp_err_t err = r_sci_lin_common_parameter_checking(p_ctrl);
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

/******************************************************************************************************************//**
 * Calculates the baud rate register settings
 *
 * @param[in] p_baud_params    Function inputs required to calculate the baud rate
 * @param[out] p_baud_setting  Baud rate calculation result
 *
 * @retval  FSP_SUCCESS                 Calculation succeeded
 * @retval  FSP_ERR_INVALID_ARGUMENT    Calculation failed/register settings not possible
 *********************************************************************************************************************/
static fsp_err_t r_sci_lin_baud_setting_calculate (sci_lin_baud_params_t const * const p_baud_params,
                                                   sci_lin_baud_setting_t * const      p_baud_setting)
{
    uint32_t freq_hz = R_FSP_SystemClockHzGet(BSP_FEATURE_SCI_CLOCK);
    uint32_t divisor = 0;
    uint32_t brr     = 0;
    int8_t   cks     = -1;
    uint32_t divisor_shift;

    /* Get ABCS value from user's setting */
    uint8_t abcs = (uint8_t) p_baud_params->base_clock_cycles_per_bit;

    /* BRR is calculated by testing whether each possible divisor produces a valid BRR setting.
     * Note ABCS is set in the user configuration and BGDM is fixed to 0.
     * The divisors are checked in order, from smallest to largest. Since the smallest divisor always produces the lowest
     * error, we can break out of the loop as soon as a valid BRR setting is found, since no other setting can have
     * a smaller error. */
    for (uint8_t i = 0; i <= SCI_LIN_CKS_MAX; i++)
    {
        cks++;
        divisor_shift = SCI_LIN_MIN_BAUD_DIVISOR_SHIFT + ((uint32_t) cks << 1U) - (uint32_t) (abcs);
        divisor       = (1U << divisor_shift) * p_baud_params->baudrate;
        brr           = (freq_hz / divisor) - 1U;
        if (brr <= UINT8_MAX)
        {
            /* Save the baud settings. */
            p_baud_setting->semr_baudrate_bits = (uint8_t) (abcs << R_SCI0_SEMR_ABCS_Pos);
            p_baud_setting->cks                = (uint8_t) ((uint32_t) cks & R_SCI0_SMR_CKS_Msk);
            p_baud_setting->brr                = (uint8_t) brr;

            return FSP_SUCCESS;
        }
    }

    /* No valid setting found */
    return FSP_ERR_INVALID_ARGUMENT;
}

/******************************************************************************************************************//**
 * Calculates the lin timer register settings
 *
 * @param[in] p_baud_params     Function inputs required to calculate the baud rate
 * @param[out] p_timer_setting  Timer setting calculation result
 *
 * @retval  FSP_SUCCESS                 Calculation succeeded
 * @retval  FSP_ERR_INVALID_ARGUMENT    Calculation failed/register settings not possible
 *********************************************************************************************************************/
static fsp_err_t r_sci_lin_timer_setting_calculate (sci_lin_baud_params_t const * const p_baud_params,
                                                    sci_lin_timer_setting_t * const     p_timer_setting)
{
    sci_lin_timer_divider_t tcss;
    uint32_t                break_field = SCI_LIN_MAX_TIMER_INTERVAL;
    uint32_t                lin_timer_freq_hz;

    /* TCSS is calculated so that the smallest divider that produces a valid value for Break field is selected */
    for (tcss = SCI_LIN_TCSS_MIN; tcss <= SCI_LIN_TCSS_MAX; tcss++)
    {
        lin_timer_freq_hz = (R_FSP_SystemClockHzGet(BSP_FEATURE_SCI_CLOCK) / (1U << tcss));
        break_field       =
            (uint32_t) (((uint64_t) lin_timer_freq_hz * p_baud_params->break_bits) / p_baud_params->baudrate);

        if (break_field <= SCI_LIN_MAX_TIMER_INTERVAL)
        {
            break;
        }
    }

    FSP_ERROR_RETURN(break_field <= SCI_LIN_MAX_TIMER_INTERVAL, FSP_ERR_INVALID_ARGUMENT);

    /* Calculate break delimiter */
    uint32_t break_delimiter =
        (uint32_t) (((uint64_t) lin_timer_freq_hz * p_baud_params->delimiter_bits) / p_baud_params->baudrate);

    FSP_ERROR_RETURN(break_delimiter <= SCI_LIN_MAX_TIMER_INTERVAL, FSP_ERR_INVALID_ARGUMENT);

    /* Save the clock divider setting and counter setting for break field output */
    p_timer_setting->tcss = (uint8_t) (tcss & SCI_LIN_TCSS_MASK);

    /* (TCNT+1) x (TPRE+1) = ticks
     * Let TCNT = ticks/256
     * => TPRE = (ticks/(TCNT+1)) -1 */
    p_timer_setting->break_field_tcnt = (uint8_t) (break_field >> 8U);
    p_timer_setting->break_field_tpre =
        (uint8_t) (((break_field + p_timer_setting->break_field_tcnt) / (p_timer_setting->break_field_tcnt + 1)) - 1);

    /* Save counter setting for break delimiter */
    p_timer_setting->delimiter_tcnt = (uint8_t) (break_delimiter >> 8U);
    p_timer_setting->delimiter_tpre =
        (uint8_t) (((break_delimiter + p_timer_setting->delimiter_tcnt) / (p_timer_setting->delimiter_tcnt + 1)) - 1);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
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
 *********************************************************************************************************************/
static uint8_t r_sci_lin_pid_calculate (uint8_t id)
{
    /* ID is 6 bits */
    uint8_t pid = id & SCI_LIN_FRAME_ID_MASK;

    /* P0 = id0 ^ id1 ^ id2 ^ id4*/
    uint8_t tmp = (((id >> 0) ^ (id >> 1) ^ (id >> 2) ^ (id >> 4)) & 0x01);
    pid |= (uint8_t) (tmp << 6U);

    /* P1 = ~(id1 ^ id3 ^ id4 ^ id5) */
    tmp  = (uint8_t) ~(((id >> 1) ^ (id >> 3) ^ (id >> 4) ^ (id >> 5)) & 0x01);
    pid |= (uint8_t) (tmp << 7U);

    return pid;
}

#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE

/******************************************************************************************************************//**
 * Add byte to checksum
 *
 * @param[in] byte         Byte to add to current sum
 * @param[in] current_sum  Current checksum (intermediate sum)
 *
 * @retval       New checksum result (after adding byte)
 *********************************************************************************************************************/
static uint8_t r_sci_lin_checksum_add_byte_to_sum (uint8_t byte, uint8_t current_sum)
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

#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE

/******************************************************************************************************************//**
 * Initialize the checksum based on the checksum type
 *
 * @param[in] id                LIN unprotected frame identifier
 * @param[in] checksum_type     Checksum type (classic or enhanced)
 *
 * @retval   Initial checksum value for the provided checksum type
 *********************************************************************************************************************/
static uint8_t r_sci_lin_checksum_initialize (uint8_t id, lin_checksum_type_t checksum_type)
{
    uint8_t checksum = 0;

    if (LIN_CHECKSUM_TYPE_ENHANCED == checksum_type)
    {
        /* Compute PID and add to checksum. Enhanced checksum includes data and PID. Standard is data only. */
        checksum = r_sci_lin_pid_calculate(id);
    }

    return checksum;
}

#endif

#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE

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
static uint8_t r_sci_lin_checksum_calculate (uint8_t               id,
                                             uint8_t const * const p_data,
                                             uint8_t               num_bytes,
                                             lin_checksum_type_t   checksum_type)
{
    uint8_t checksum = r_sci_lin_checksum_initialize(id, checksum_type);

    for (uint8_t i = 0; i < num_bytes; i++)
    {
        checksum = r_sci_lin_checksum_add_byte_to_sum(p_data[i], checksum);
    }

    return (uint8_t) ~checksum;
}

#endif

/******************************************************************************************************************//**
 * Initializes the SCI common and LIN register settings and enable LIN interrupts.
 *
 * Initial settings are based on Figure 27.103 "Example of Start Frame transmission" and Figure 27.107 "Sample
 * flowchart for reception of a Start Frame" of the RA4M2 manual R01UH0892EJ0130 and related Table 27.28 "Example flow
 * of SCI initialization in asynchronous mode with non-FIFO selected".
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *********************************************************************************************************************/
static void r_sci_lin_hw_configure (sci_lin_instance_ctrl_t * const p_ctrl)
{
    lin_cfg_t const * p_cfg = p_ctrl->p_cfg;
    sci_lin_extended_cfg_t const * const p_extend = (sci_lin_extended_cfg_t *) p_cfg->p_extend;
    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    uint8_t cr2 = 0;
    uint8_t icr = R_SCI0_ICR_BFDIE_Msk;
    uint8_t tmr;

    /* Enable the SCI channel */
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);

    /* Ensure transmission and reception are disabled during initialization. */
    p_reg->SCR = SCI_LIN_SCR_INITIAL_VALUE;

    /* Make node-specific settings */
    if (LIN_MODE_SLAVE == p_cfg->mode)
    {
        p_reg->CR1 = (uint8_t) ((uint8_t) SCI_LIN_CR1_MASK_SLAVE |
                                (p_extend->filter_setting.priority_interrupt_bit_select << R_SCI0_CR1_PIBS_Pos) |
                                (p_extend->filter_setting.priority_interrupt_enable << R_SCI0_CR1_PIBE_Pos) |
                                (p_extend->filter_setting.compare_data_select << R_SCI0_CR1_CF1DS_Pos));
        p_reg->CF1CR  = p_extend->filter_setting.compare_data_mask;
        p_reg->PCF1DR = p_extend->filter_setting.primary_compare_data;
        p_reg->SCF1DR = p_extend->filter_setting.secondary_compare_data;
        p_reg->CF0CR  = SCI_LIN_CF0CR_MASK_SLAVE;
        p_reg->CF0DR  = SCI_LIN_CF0DR_MASK_SLAVE;
        tmr           = SCI_LIN_TIMER_DETERMINATION_MASK;
        icr          |= SCI_LIN_ICR_CONTROL_FIELD_MASK;
        icr          |= p_extend->filter_setting.priority_interrupt_enable << R_SCI0_ICR_PIBDIE_Pos;
    }
    else
    {
        tmr = SCI_LIN_TIMER_OUTPUT_MASK;
    }

    /* Configure LIN timer divider */
    tmr |= (p_extend->baud_setting.timer_setting.tcss << R_SCI0_TMR_TCSS_Pos);

#if SCI_LIN_BUS_CONFLICT_DETECTION_SUPPORT_ENABLE

    /* Configure bus conflict detection clock */
    cr2 |= (uint8_t) (p_extend->bus_conflict_clock << R_SCI0_CR2_BCCS_Pos);

    /* Enable LIN bus collision interrupt if bus conflict detection support is enabled */
    icr |= (p_extend->scix2_irq >= 0) << (uint8_t) R_SCI0_ICR_BCDIE_Pos;
#endif

    /* Configure digital filter clock */
    cr2 |= (uint8_t) (p_extend->digital_filter_clock << R_SCI0_CR2_DFCS_Pos);

    /* Set required LIN settings. */
    p_reg->CR2  = cr2;
    p_reg->PCR  = SCI_LIN_PCR_DEFAULT_VALUE;
    p_reg->TMR  = tmr;
    p_reg->TPRE = p_extend->baud_setting.timer_setting.break_field_tpre;
    p_reg->TCNT = p_extend->baud_setting.timer_setting.break_field_tcnt;

    /* Write the settings to the SCI control registers in the order specified by the initialization flow. */
    p_reg->FCR   = SCI_LIN_FCR_DEFAULT_VALUE;
    p_reg->SIMR1 = SCI_LIN_SIMR1_DEFAULT_VALUE;
    p_reg->SPMR  = SCI_LIN_SPMR_DEFAULT_VALUE;
    p_reg->SMR   = (uint8_t) (p_extend->baud_setting.cks << R_SCI0_SMR_CKS_Pos);
    p_reg->SCMR  = SCI_LIN_SCMR_DEFAULT_VALUE;
    p_reg->SEMR  = (uint8_t) (R_SCI0_SEMR_RXDESEL_Msk | p_extend->baud_setting.semr_baudrate_bits);
    p_reg->BRR   = p_extend->baud_setting.brr;
    p_reg->MDDR  = SCI_LIN_MDDR_DEFAULT_VALUE;

    /* Enable reception */
    p_reg->SCR = SCI_LIN_SCR_INITIAL_VALUE | R_SCI0_SCR_RE_Msk;

    /* Clear all flags BFDF, CF0MF, CF1MF, PIBDF, BCDF, AEDF */
    p_reg->STCR = SCI_LIN_STCR_CLEAR_MASK;

    /* Set LIN interrupt enable bits */
    p_reg->ICR = icr;

    /* Enable the LIN mode control. */
    p_reg->ESMER = R_SCI0_ESMER_ESME_Msk;

    /* Enable break field detection in slave mode */
    r_sci_lin_break_field_detection_reset(p_ctrl);

    /* Enable interrupt handlers in the NVIC */
    r_sci_lin_irqs_enable_disable(p_ctrl, r_sci_lin_irq_enable);
}

/******************************************************************************************************************//**
 * Clear LIN status flags (STCR and SSR)
 *
 * @param[in]  p_reg      SCI register pointer
 * @param[in]  ssr        SSR flags to clear
 * @param[in]  stcr       STCR flags to clear
 *
 *********************************************************************************************************************/
static void r_sci_lin_flags_clear (R_SCI0_Type * const p_reg, uint8_t ssr, uint8_t stcr)
{
    p_reg->SSR &= (~ssr);
    p_reg->STCR = stcr;
}

/******************************************************************************************************************//**
 * Enables the requested IRQ and sets the interrupt context
 *
 * @param[in]  irq        IRQ to enable
 * @param[in]  ipl        Interrupt priority
 * @param[in]  p_context  Pointer to interrupt context
 *********************************************************************************************************************/
static void r_sci_lin_irq_enable (IRQn_Type irq, uint8_t ipl, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, ipl, p_context);
    }
}

/******************************************************************************************************************//**
 * Disables the requested IRQ.
 *
 * @param[in]  irq        IRQ to disable
 * @param[in]  ipl        Interrupt priority
 * @param[in]  p_context  Pointer to interrupt context
 *********************************************************************************************************************/
static void r_sci_lin_irq_disable (IRQn_Type irq, uint8_t ipl, void * p_context)
{
    /* Parameters unused to allow using same function signature in r_sci_lin_irqs_enable_disable which reduces
     * codes size */
    FSP_PARAMETER_NOT_USED(ipl);
    FSP_PARAMETER_NOT_USED(p_context);

    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
    }
}

/******************************************************************************************************************//**
 * Disables interrupt and clears pending status
 *
 * @param[in]  irq                       IRQ number for this interrupt
 *********************************************************************************************************************/
static void r_sci_lin_irq_cfg (IRQn_Type const irq)
{
    r_sci_lin_irq_disable(irq, 0, 0);

    if (irq >= 0)
    {
        R_BSP_IrqStatusClear(irq);
    }
}

/******************************************************************************************************************//**
 * Intializes interrupts in the NVIC, but does not enable them
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *********************************************************************************************************************/
static void r_sci_lin_irqs_cfg (sci_lin_instance_ctrl_t * const p_ctrl)
{
    lin_cfg_t const * p_cfg = p_ctrl->p_cfg;
    sci_lin_extended_cfg_t const * const p_extend = (sci_lin_extended_cfg_t *) p_cfg->p_extend;

    /* Required */
    r_sci_lin_irq_cfg(p_extend->rxi_irq);
    r_sci_lin_irq_cfg(p_extend->txi_irq);
    r_sci_lin_irq_cfg(p_extend->tei_irq);
    r_sci_lin_irq_cfg(p_extend->eri_irq);
    r_sci_lin_irq_cfg(p_extend->scix0_irq);
    if (LIN_MODE_SLAVE == p_cfg->mode)
    {
        r_sci_lin_irq_cfg(p_extend->scix1_irq);
    }

#if SCI_LIN_BUS_CONFLICT_DETECTION_SUPPORT_ENABLE
    r_sci_lin_irq_cfg(p_extend->scix2_irq);
#endif
}

/******************************************************************************************************************//**
 * Enables or disables all LIN interrupts in the NVIC. Enable does not necessarily enable them in the SCI.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  irqEnableDisableFunc      r_sci_lin_irq_enable to enable interrupts. r_sci_lin_irq_disable to
 *                                       disable interrupts.
 *********************************************************************************************************************/
static inline void r_sci_lin_irqs_enable_disable (sci_lin_instance_ctrl_t * const p_ctrl,
                                                  void (                        * irqEnableDisableFunc)(
                                                      IRQn_Type                   irq,
                                                      uint8_t                     ipl,
                                                      void                      * p_context))
{
    lin_cfg_t const * p_cfg = p_ctrl->p_cfg;
    sci_lin_extended_cfg_t const * const p_extend = (sci_lin_extended_cfg_t *) p_cfg->p_extend;

    irqEnableDisableFunc(p_extend->rxi_irq, p_extend->rxi_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->txi_irq, p_extend->txi_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->tei_irq, p_extend->tei_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->eri_irq, p_extend->eri_ipl, p_ctrl);
    irqEnableDisableFunc(p_extend->scix0_irq, p_extend->scix0_ipl, p_ctrl);
    if (LIN_MODE_SLAVE == p_cfg->mode)
    {
        irqEnableDisableFunc(p_extend->scix1_irq, p_extend->scix1_ipl, p_ctrl);
    }

#if SCI_LIN_BUS_CONFLICT_DETECTION_SUPPORT_ENABLE
    irqEnableDisableFunc(p_extend->scix2_irq, p_extend->scix2_ipl, p_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * Transmit the LIN frame
 *
 *  Header transmission is based on flow chart process in Figure 27.103
 * "Example of Start Frame transmission" in RA4M2 manual R01UH0892EJ0130.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @param[in]  p_transfer_params         Pointer to the transfer parameters for the transfer
 * @param[in]  send_header               Set to true if the LIN header should be transmitted before the frame data (master mode only)
 *
 * @retval     FSP_SUCCESS               Transmission started successfully
 **********************************************************************************************************************/
static fsp_err_t r_sci_lin_write (sci_lin_instance_ctrl_t * const     p_ctrl,
                                  const lin_transfer_params_t * const p_transfer_params,
                                  uint8_t const                       send_header)
{
    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    /* Stop any in-progress break field transmission */
    p_reg->TCR = 0;

    /* Disable transmit interrupts, transmission, and reception interrupts */
    p_reg->SCR &=
        (uint8_t) ~(R_SCI0_SCR_TIE_Msk | R_SCI0_SCR_TEIE_Msk | R_SCI0_SCR_RIE_Msk | R_SCI0_SCR_TE_Msk);

    /* Prepare the data transmission state. */
    p_ctrl->p_data       = p_transfer_params->p_data;
    p_ctrl->tx_src_bytes = 0;
    p_ctrl->event        = LIN_EVENT_NONE;
    p_ctrl->checksum     = 0;

    if (p_transfer_params->p_data)
    {
        p_ctrl->tx_src_bytes = p_transfer_params->num_bytes;

#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE
        if (p_transfer_params->checksum_type != LIN_CHECKSUM_TYPE_NONE)
        {
            /* If checksum generation is enabled, calculate the checksum */
            p_ctrl->checksum = r_sci_lin_checksum_calculate(p_transfer_params->id,
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
        p_ctrl->tx_header_bytes = SCI_LIN_HEADER_NUM_BYTES;

        /* Save the PID of the last attempted transmit */
        p_ctrl->last_pid = r_sci_lin_pid_calculate(p_transfer_params->id);

        /* Ensure transmission is enabled. Do not set SCR.TE and TIE to 1 at the same time to
         * avoid SCIn_TXI output before the Break Field */
        p_reg->SCR |= (uint8_t) (R_SCI0_SCR_TE_Msk);

        /* Clear flags */
        r_sci_lin_flags_clear(p_reg, SCI_LIN_SSR_CLEAR_MASK, SCI_LIN_STCR_CLEAR_MASK);

        /* Start outputting break field. */
        p_reg->TCR = R_SCI0_TCR_TCST_Msk;
    }
    else
    {
        /* Clear flags */
        r_sci_lin_flags_clear(p_ctrl->p_reg, SCI_LIN_SSR_CLEAR_MASK, SCI_LIN_STCR_CLEAR_MASK);

        /* Enable transmit interrupt to start transmission. Setting TE and TIE together causes a
         * TXI interrupt which will kick of transmission of the first byte. */
        p_reg->SCR |= (uint8_t) (R_SCI0_SCR_TE_Msk | R_SCI0_SCR_TIE_Msk);
    }

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Handle error interrupt
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *********************************************************************************************************************/
static lin_event_t r_sci_lin_eri_handler (sci_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI0_Type * p_reg = p_ctrl->p_reg;
    lin_event_t   event = LIN_EVENT_NONE;
    uint8_t       scr   = p_reg->SCR;
    uint8_t       ssr   = p_reg->SSR;

    /* Begin error handling according to flow chart process in Figure 27.125
     * "Example of Flowchart for Receive Error Handling (during Reception of the Start Frame)"
     * in RA4M2 manual R01UH0892EJ0130. */

    /* Stop counting by the timer */
    p_reg->TCR = 0;

    /* Disable LIN mode. The state of the LIN mode control section is initialized. */
    p_reg->ESMER = 0;

    /* Enable LIN mode. */
    p_reg->ESMER = R_SCI0_ESMER_ESME_Msk;

    /* Suspend transmission and transmit interrupts, and reception interrupts */
    p_reg->SCR = scr &
                 (uint8_t) ~(R_SCI0_SCR_TE_Msk | R_SCI0_SCR_TIE_Msk | R_SCI0_SCR_TEIE_Msk | R_SCI0_SCR_RIE_Msk);

    /* Determine cause of error. */
    if (ssr & R_SCI0_SSR_FER_Msk)
    {
        event = LIN_EVENT_ERR_FRAMING;
    }
    else if (ssr & R_SCI0_SSR_ORER_Msk)
    {
        event = LIN_EVENT_ERR_OVERRUN;
    }
    else
    {
        /* Do nothing */
    }

    /* Clear error conditions and discard RDR data. */
    r_sci_lin_flags_clear(p_ctrl->p_reg, SCI_LIN_ERROR_SSR_EVENTS_CLEAR_MASK, SCI_LIN_ERROR_STCR_EVENTS_CLEAR_MASK);

    /* Reset break field detection in slave mode */
    r_sci_lin_break_field_detection_reset(p_ctrl);

    return event;
}

/**********************************************************************************************************************
 * Process received data byte and return an event if the user should be notified via callback. 0 is returned
 * if no event of user interest is detected.
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 * @return     0 if no event present (rx still in progress), otherwise the lin_event_t to pass to the user callback
 *********************************************************************************************************************/
lin_event_t r_sci_lin_rxi_handler (sci_lin_instance_ctrl_t * const p_ctrl)
{
    lin_event_t   event = LIN_EVENT_NONE;
    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    /* Data byte */
    if (p_ctrl->rx_bytes_expected > p_ctrl->rx_bytes_received)
    {
        uint8_t bytes_remaining = p_ctrl->rx_bytes_expected - p_ctrl->rx_bytes_received;

        /* Read data byte from RDR */
        uint8_t rx_byte = p_reg->RDR;

        /* Check if this is the last byte in the transfer */
        if (1 == bytes_remaining)
        {
            event = LIN_EVENT_RX_DATA_COMPLETE;

#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE

            /* Perform checksum validation if requested */
            if (p_ctrl->validate_checksum)
            {
                /* Validate checksum. At this point, p_ctrl->checksum contains the checksum over the data bytes. */
                if (((p_ctrl->checksum + rx_byte)) != SCI_LIN_CHECKSUM_OK)
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
            p_reg->SCR_b.RIE          = 0;

            /* Reset break field detection in slave mode */
            r_sci_lin_break_field_detection_reset(p_ctrl);
        }
        /* Received a byte which is not the last byte */
        else
        {
#if SCI_LIN_CHECKSUM_SUPPORT_ENABLE

            /* Add the received byte to the running checksum */
            if (p_ctrl->validate_checksum)
            {
                p_ctrl->checksum = r_sci_lin_checksum_add_byte_to_sum(rx_byte, p_ctrl->checksum);
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
        p_reg->SSR_b.RDRF = 0;

        /* Stop reception interrupts. */
        p_reg->SCR_b.RIE = 0;

        /* Reset break field detection in slave mode */
        r_sci_lin_break_field_detection_reset(p_ctrl);
    }

    return event;
}

/******************************************************************************************************************//**
 * Transmit next data byte
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *********************************************************************************************************************/
static void r_sci_lin_txi_handler (sci_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI0_Type * p_reg = p_ctrl->p_reg;

    if (p_ctrl->tx_header_bytes || p_ctrl->tx_src_bytes)
    {
        if (p_ctrl->tx_header_bytes)
        {
            /* Write the sync word if this is the first header byte. Otherwise, this is the second header byte (the PID). */
            p_reg->TDR = (SCI_LIN_HEADER_NUM_BYTES == p_ctrl->tx_header_bytes) ?
                         SCI_LIN_SYNC : p_ctrl->last_pid;

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
            uint8_t scr_temp = p_reg->SCR;
            scr_temp      |= R_SCI0_SCR_TEIE_Msk;
            scr_temp      &= (uint8_t) ~(R_SCI0_SCR_TIE_Msk);
            p_reg->SCR     = scr_temp;
            p_ctrl->p_data = NULL;
        }
    }
}

/**********************************************************************************************************************
 * Handle break field detected
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *********************************************************************************************************************/
static void r_sci_lin_scix0_handler (sci_lin_instance_ctrl_t * const p_ctrl)
{
    lin_cfg_t const   * p_cfg = p_ctrl->p_cfg;
    R_SCI0_Type * const p_reg = p_ctrl->p_reg;
    sci_lin_extended_cfg_t const * const p_extend = (sci_lin_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Clear the BFDF flag */
    p_reg->STCR = R_SCI0_STCR_BFDCL_Msk;

    if (LIN_MODE_MASTER == p_cfg->mode)
    {
        /* Stop the timer counting after Break Field low width, before the next underflow of time occurs */
        p_reg->TCR = 0;

        if (SCI_LIN_BREAK_FIELD_OUTPUT_MODE == p_reg->TMR_b.TOMS)
        {
            /* Switch to timer mode to time the break delimiter */
            p_reg->TMR_b.TOMS = SCI_LIN_TIMER_MODE;

            /* Setting counter for break delimiter */
            p_reg->TPRE = p_extend->baud_setting.timer_setting.delimiter_tpre;
            p_reg->TCNT = p_extend->baud_setting.timer_setting.delimiter_tcnt;

            /* Start the counter */
            p_reg->TCR = 1;
        }
        else
        {
            /* Switch to break field low width output mode */
            p_reg->TMR_b.TOMS = SCI_LIN_BREAK_FIELD_OUTPUT_MODE;

            /* Setting the counter as the original value for the next break field length */
            p_reg->TPRE = p_extend->baud_setting.timer_setting.break_field_tpre;
            p_reg->TCNT = p_extend->baud_setting.timer_setting.break_field_tcnt;

            /* Disable transmit function, then re-enable it with TIE to generate a TXI interrupt request.
             * Refer to Figure 27.104 "Example of Start Frame Transmission (2/2)" of the RA4M2 manual R01UH0892EJ0130 */
            p_reg->SCR &= (uint8_t) (~R_SCI0_SCR_TE_Msk);
            p_reg->SCR |= (uint8_t) (R_SCI0_SCR_TE_Msk | R_SCI0_SCR_TIE_Msk);
        }
    }
    else
    {
        /* Clear flags that may have occurred during previous frames to prepare for reception */
        r_sci_lin_flags_clear(p_reg, SCI_LIN_ERROR_SSR_EVENTS_CLEAR_MASK, SCI_LIN_ERROR_STCR_EVENTS_CLEAR_MASK);
    }
}

/**********************************************************************************************************************
 * Handle control field 0/1 match and priority interrupt bit detected
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *********************************************************************************************************************/
lin_event_t r_sci_lin_scix1_handler (sci_lin_instance_ctrl_t * const p_ctrl)
{
    lin_event_t   event = LIN_EVENT_NONE;
    R_SCI0_Type * p_reg = p_ctrl->p_reg;
    uint8_t       str   = p_reg->STR;

    /* Check if control field 0 was received*/
    if (str & R_SCI0_STR_CF0MF_Msk)
    {
        /* Discard received data and clear the CF0 received flag to advance header reception state */
        r_sci_lin_flags_clear(p_reg, R_SCI0_SSR_RDRF_Msk, R_SCI0_STCR_CF0MCL_Msk);
    }
    else if (str & (R_SCI0_STR_PIBDF_Msk | R_SCI0_STR_CF1MF_Msk))
    {
        /*  Clear CF1MF flag in the STR register */
        p_reg->STCR = R_SCI0_STCR_PIBDCL_Msk | R_SCI0_STCR_CF1MCL_Msk;

        /* Read the received data */
        uint8_t pid = p_reg->RDR;

        /* Set the event to notify the application (slave node only). */
        event = LIN_EVENT_RX_HEADER_COMPLETE;

        /* Check parity */
        if (r_sci_lin_pid_calculate(pid) != pid)
        {
            event = LIN_EVENT_ERR_PARITY;

            /* Reset break field detection in slave mode */
            r_sci_lin_break_field_detection_reset(p_ctrl);
        }
        else
        {
            /* Save received PID (Control Field 1) */
            p_ctrl->last_pid = pid;
        }

        /* Enable reception interrupts to receive the data frame */
        p_reg->SCR |= R_SCI0_SCR_RIE_Msk;
    }
    else
    {
        /* Do nothing */
    }

    return event;
}

#if SCI_LIN_BUS_CONFLICT_DETECTION_SUPPORT_ENABLE

/**********************************************************************************************************************
 * Handle bus collision detected
 *
 * @param[in]  p_ctrl                    Pointer to driver control block
 *********************************************************************************************************************/
static lin_event_t r_sci_lin_scix2_handler (sci_lin_instance_ctrl_t * const p_ctrl)
{
    R_SCI0_Type * p_reg = p_ctrl->p_reg;
    uint8_t       scr   = p_reg->SCR;

    /* Suspend transmission and transmit interrupts, and reception interrupts */
    p_reg->SCR = scr &
                 (uint8_t) ~(R_SCI0_SCR_TE_Msk | R_SCI0_SCR_TIE_Msk | R_SCI0_SCR_TEIE_Msk |
                             R_SCI0_SCR_RIE_Msk);

    /* Clear error conditions and discard RDR data. */
    r_sci_lin_flags_clear(p_reg, SCI_LIN_ERROR_SSR_EVENTS_CLEAR_MASK, SCI_LIN_ERROR_STCR_EVENTS_CLEAR_MASK);

    /* Reset break field detection in slave mode */
    r_sci_lin_break_field_detection_reset(p_ctrl);

    return LIN_EVENT_ERR_BUS_COLLISION_DETECTED;
}

#endif

/******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to LIN instance control block
 * @param[in]     event      Event code
 *********************************************************************************************************************/
static void r_sci_lin_call_callback (sci_lin_instance_ctrl_t * p_ctrl, lin_event_t event)
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
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the
         * callback. */
        sci_lin_prv_ns_callback p_callback = (sci_lin_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the
     * callback. */
    p_ctrl->p_callback(p_args);
#endif
    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/******************************************************************************************************************//**
 * Reset break field detection
 *
 * @param[in]     p_ctrl     Pointer to LIN instance control block
 *********************************************************************************************************************/
static void r_sci_lin_break_field_detection_reset (sci_lin_instance_ctrl_t * const p_ctrl)
{
    if (LIN_MODE_SLAVE == p_ctrl->p_cfg->mode)
    {
        R_SCI0_Type * p_reg = p_ctrl->p_reg;

        /* Enable timer in preparation to receive next header */
        p_reg->TCR = R_SCI0_TCR_TCST_Msk;

        /* Slave Start Frame Detection Start */
        p_reg->CR3 = SCI_LIN_CR3_MASK_SLAVE;
    }
}

/******************************************************************************************************************//**
 * Reset any in progress transmission/reception
 *
 * @param[in]     p_ctrl     Pointer to LIN instance control block
 *********************************************************************************************************************/
static void r_sci_lin_transfer_state_reset (sci_lin_instance_ctrl_t * const p_ctrl)
{
    /* Reset any in progress transmission/reception */
    p_ctrl->rx_bytes_expected = 0;
    p_ctrl->rx_bytes_received = 0;
    p_ctrl->tx_src_bytes      = 0;
    p_ctrl->tx_header_bytes   = 0U;
    p_ctrl->p_data            = NULL;
    p_ctrl->p_callback_memory = NULL;
    p_ctrl->event             = LIN_EVENT_NONE;
}

/**********************************************************************************************************************
 * Interrupt service routines
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * TXI interrupt processing for LIN mode. TXI interrupt fires when the data in the data register has
 * been transferred to the data shift register, and the next data can be written.
 *
 * @retval    none
 *********************************************************************************************************************/
void sci_lin_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear Interrupt Status Flag IR */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Transmit the next byte */
    r_sci_lin_txi_handler(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * RXI interrupt processing for LIN mode. RXI interrupt fires when data arrives to the data register.
 *
 * @retval    none
 *********************************************************************************************************************/
void sci_lin_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Process the received data and determine whether there is a callback event present */
    lin_event_t event = r_sci_lin_rxi_handler(p_ctrl);

    /* If callback event occurred, call the callback */
    if (event)
    {
        r_sci_lin_call_callback(p_ctrl, event);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * TEI interrupt processing for LIN mode. The TEI interrupt fires after the last byte is transmitted on the
 * TX pin.
 *
 * @retval    none
 *********************************************************************************************************************/
void sci_lin_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Disable transmission and transmit interrupts */
    p_ctrl->p_reg->SCR &= (uint8_t) ~(R_SCI0_SCR_TE_Msk | R_SCI0_SCR_TIE_Msk | R_SCI0_SCR_TEIE_Msk);

    /* Call user callback */
    if (p_ctrl->event)
    {
        r_sci_lin_call_callback(p_ctrl, p_ctrl->event);
    }

    /* Reset break field detection in slave mode */
    r_sci_lin_break_field_detection_reset(p_ctrl);

    /* Clear Interrupt Status Flag IR */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * ERI interrupt processing for LIN mode. The ERI interrupt fires when an error that is detectable by the SCI
 * hardware occurs.
 *
 * @retval    none
 *********************************************************************************************************************/
void sci_lin_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Determine the error event */
    lin_event_t event = r_sci_lin_eri_handler(p_ctrl);

    /* Call user callback */
    r_sci_lin_call_callback(p_ctrl, event);

    /* Reset any in progress transmission/reception */
    r_sci_lin_transfer_state_reset(p_ctrl);

    /* Clear Interrupt Status Flag IR */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * SCIX0 interrupt processing for LIN mode. The SCIX0 interrupt fires when a break field is detected by the
 * hardware, signaling the start of a LIN frame.
 *
 * @retval    none
 *********************************************************************************************************************/
void sci_lin_scix0_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Process the break field */
    r_sci_lin_scix0_handler(p_ctrl);

    /* Clear Interrupt Status Flag IR */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * SCIX1 interrupt processing for LIN mode. The SCIX1 interrupt fires when a control field 0/1 is matched or
 * priority interrupt bit deteced by the hardware
 *
 * @retval    none
 *********************************************************************************************************************/
void sci_lin_scix1_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Process the Control field event */
    lin_event_t event = r_sci_lin_scix1_handler(p_ctrl);

    /* If callback event occurred, call the callback */
    if (event)
    {
        r_sci_lin_call_callback(p_ctrl, event);
    }

    /* Clear Interrupt Status Flag IR */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if SCI_LIN_BUS_CONFLICT_DETECTION_SUPPORT_ENABLE

/******************************************************************************************************************//**
 * SCIX2 interrupt processing for LIN mode. The SCIX2 interrupt fires when a bus collision detected by the
 * hardware
 * @retval    none
 *********************************************************************************************************************/
void sci_lin_scix2_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    sci_lin_instance_ctrl_t * p_ctrl = (sci_lin_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Process the bus collisions event */
    lin_event_t event = r_sci_lin_scix2_handler(p_ctrl);

    /* Call user callback */
    r_sci_lin_call_callback(p_ctrl, event);

    /* Reset any in progress transmission/reception */
    r_sci_lin_transfer_state_reset(p_ctrl);

    /* Clear Interrupt Status Flag IR */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif
