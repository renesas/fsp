/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "r_gpt.h"
#include "r_gpt_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "GPT" in ASCII, used to determine if channel is open. */
#define GPT_OPEN                                         (0x00475054ULL)

#define GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK               (BSP_FEATURE_GPTEH_CHANNEL_MASK | \
                                                          BSP_FEATURE_GPTE_CHANNEL_MASK)

#define GPT_PRV_GTWP_RESET_VALUE                         (0xA500U)
#define GPT_PRV_GTWP_WRITE_PROTECT                       (0xA501U)

#define GPT_PRV_GTIOR_STOP_LEVEL_BIT                     (6)
#define GPT_PRV_GTIOR_INITIAL_LEVEL_BIT                  (4)

#define GPT_PRV_GTIO_HIGH_COMPARE_MATCH_LOW_CYCLE_END    (0x6U)
#define GPT_PRV_GTIO_LOW_COMPARE_MATCH_HIGH_CYCLE_END    (0x9U)

#define GPT_PRV_GTIO_TOGGLE_COMPARE_MATCH                (0x3U)

#define GPT_PRV_GTBER_BUFFER_ENABLE_FORCE_TRANSFER       (0x550000U)

#define GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE             (0x80000000U)

#define GPT_PRV_GTCCRA                                   (0U)
#define GPT_PRV_GTCCRB                                   (1U)
#define GPT_PRV_GTCCRC                                   (2U)
#define GPT_PRV_GTCCRD                                   (3U)

/* GPT_CFG_OUTPUT_SUPPORT_ENABLE is set to 2 to enable extra features. */
#define GPT_PRV_EXTRA_FEATURES_ENABLED                   (2U)

#define R_GPT0_GTINTAD_ADTRAUEN_Pos                      (16U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Duty cycle mode. */
typedef enum e_gpt_duty_cycle_mode
{
    GPT_DUTY_CYCLE_MODE_REGISTER    = 0, // Duty cycle depends on compare match
    GPT_DUTY_CYCLE_MODE_0_PERCENT   = 2, // Output low
    GPT_DUTY_CYCLE_MODE_100_PERCENT = 3, // Output high
} gpt_duty_cycle_mode_t;

/* Count direction */
typedef enum e_gpt_dir
{
    GPT_DIR_COUNT_DOWN = 0,
    GPT_DIR_COUNT_UP   = 1
} gpt_dir_t;

typedef struct st_gpt_prv_duty_registers
{
    uint32_t gtccr_buffer;
    uint32_t omdty;
} gpt_prv_duty_registers_t;

typedef enum e_gpt_prv_capture_event
{
    GPT_PRV_CAPTURE_EVENT_A,
    GPT_PRV_CAPTURE_EVENT_B,
} gpt_prv_capture_event_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void gpt_hardware_initialize(gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);

static void gpt_common_open(gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);

static uint32_t gpt_clock_frequency_get(gpt_instance_ctrl_t * const p_instance_ctrl);

static void gpt_hardware_events_disable(gpt_instance_ctrl_t * p_instance_ctrl);

static void r_gpt_disable_irq(IRQn_Type irq);

static inline void r_gpt_write_protect_enable(gpt_instance_ctrl_t * const p_instance_ctrl);
static inline void r_gpt_write_protect_disable(gpt_instance_ctrl_t * const p_instance_ctrl);

/* Noinline attribute added to reduce code size for CM23 GCC build. */
static void r_gpt_enable_irq(IRQn_Type const irq, uint32_t priority, void * p_context) __attribute__((noinline));

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

static void gpt_calculate_duty_cycle(gpt_instance_ctrl_t * const p_instance_ctrl,
                                     uint32_t const              duty_cycle_counts,
                                     gpt_prv_duty_registers_t  * p_duty_reg);

static uint32_t gpt_gtior_calculate(timer_cfg_t const * const p_cfg, gpt_pin_level_t const stop_level);

#endif

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void gpt_counter_overflow_isr(void);
void gpt_counter_underflow_isr(void);
void gpt_capture_a_isr(void);
void gpt_capture_b_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro. */
static const fsp_version_t g_gpt_version =
{
    .api_version_minor  = TIMER_API_VERSION_MINOR,
    .api_version_major  = TIMER_API_VERSION_MAJOR,
    .code_version_major = GPT_CODE_VERSION_MAJOR,
    .code_version_minor = GPT_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* GPT implementation of timer interface  */
const timer_api_t g_timer_on_gpt =
{
    .open         = R_GPT_Open,
    .stop         = R_GPT_Stop,
    .start        = R_GPT_Start,
    .reset        = R_GPT_Reset,
    .enable       = R_GPT_Enable,
    .disable      = R_GPT_Disable,
    .periodSet    = R_GPT_PeriodSet,
    .dutyCycleSet = R_GPT_DutyCycleSet,
    .infoGet      = R_GPT_InfoGet,
    .statusGet    = R_GPT_StatusGet,
    .close        = R_GPT_Close,
    .versionGet   = R_GPT_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup GPT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the timer module and applies configurations. Implements @ref timer_api_t::open.
 *
 * GPT hardware does not support one-shot functionality natively.  When using one-shot mode, the timer will be stopped
 * in an ISR after the requested period has elapsed.
 *
 * The GPT implementation of the general timer can accept a gpt_extended_cfg_t extension parameter.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL or the source divider is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       timer_cfg_t::mode is ::TIMER_MODE_ONE_SHOT or timer_cfg_t::p_callback is not
 *                                        NULL, but ISR is not enabled.  ISR must be enabled to use one-shot mode or
 *                                        callback.
 * @retval FSP_ERR_INVALID_MODE           Triangle wave PWM is only supported if GPT_CFG_OUTPUT_SUPPORT_ENABLE is 2.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(0U == (p_cfg->source_div % 2U));
 #if GPT_PRV_EXTRA_FEATURES_ENABLED != GPT_CFG_OUTPUT_SUPPORT_ENABLE
    FSP_ERROR_RETURN(p_cfg->mode <= TIMER_MODE_PWM, FSP_ERR_INVALID_MODE);
 #endif
    FSP_ERROR_RETURN(GPT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_instance_ctrl->channel_mask = 1U << p_cfg->channel;

#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN((p_instance_ctrl->channel_mask & BSP_FEATURE_GPT_VALID_CHANNEL_MASK),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    if ((p_cfg->p_callback) || (TIMER_MODE_ONE_SHOT == p_cfg->mode))
    {
        FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

 #if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Callback is required if underflow interrupt is enabled. */
    gpt_extended_cfg_t           * p_extend  = (gpt_extended_cfg_t *) p_cfg->p_extend;
    gpt_extended_pwm_cfg_t const * p_pwm_cfg = p_extend->p_pwm_cfg;
    if (NULL != p_pwm_cfg)
    {
        if (p_pwm_cfg->trough_irq >= 0)
        {
            FSP_ASSERT(NULL != p_cfg->p_callback);
        }
    }
 #endif
#endif

    /* Initialize control structure based on configurations. */
    gpt_common_open(p_instance_ctrl, p_cfg);

    gpt_hardware_initialize(p_instance_ctrl, p_cfg);

    p_instance_ctrl->open = GPT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops timer. Implements @ref timer_api_t::stop.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Stop
 *
 * @retval FSP_SUCCESS                 Timer successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Stop (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer. Implements @ref timer_api_t::start.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Start
 *
 * @retval FSP_SUCCESS                 Timer successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Start (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start timer */
    p_instance_ctrl->p_reg->GTSTR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to 0. Implements @ref timer_api_t::reset.
 *
 * @note This function also updates to the new period if no counter overflow has occurred since the last call to
 * R_GPT_PeriodSet().
 *
 * @retval FSP_SUCCESS                 Counter value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Reset (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear timer counter. */
    p_instance_ctrl->p_reg->GTCLR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::enable.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Enable
 *
 * @retval FSP_SUCCESS                 External events successfully enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Enable (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Enable use of GTSTR, GTSTP, and GTCLR for this channel. */
    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint32_t             gtssr    = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    uint32_t             gtpsr    = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    uint32_t             gtcsr    = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;

    /* OR with user settings. */
    gtssr |= p_extend->start_source;
    gtpsr |= p_extend->stop_source;
    gtcsr |= p_extend->clear_source;

    r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set the count sources. Ensure stop and clear sources are set before start source, and capture sources are set
     * after start source. */
    p_instance_ctrl->p_reg->GTPSR   = gtpsr;
    p_instance_ctrl->p_reg->GTCSR   = gtcsr;
    p_instance_ctrl->p_reg->GTSSR   = gtssr;
    p_instance_ctrl->p_reg->GTICASR = p_extend->capture_a_source;
    p_instance_ctrl->p_reg->GTICBSR = p_extend->capture_b_source;

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::disable.
 *
 * @note The timer could be running after R_GPT_Disable(). To ensure it is stopped, call R_GPT_Stop().
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_Disable
 *
 * @retval FSP_SUCCESS                 External events successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Disable (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_gpt_write_protect_disable(p_instance_ctrl);

    gpt_hardware_events_disable(p_instance_ctrl);

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets period value provided. If the timer is running, the period will be updated after the next counter overflow.
 * If the timer is stopped, this function resets the counter and updates the period.
 * Implements @ref timer_api_t::periodSet.
 *
 * @warning If periodic output is used, the duty cycle buffer registers are updated after the period buffer register.
 * If this function is called while the timer is running and a GPT overflow occurs during processing, the duty cycle
 * will not be the desired 50% duty cycle until the counter overflow after processing completes.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_gpt_write_protect_disable(p_instance_ctrl);

    /* Update period buffer register. The actual period is one cycle longer than the register value for saw waves
     * and twice the register value for triangle waves. Reference section 23.2.21 "General PWM Timer Cycle Setting
     * Register (GTPR)". The setting passed to the configuration is expected to be half the desired period for
     * triangle waves. */
    uint32_t new_gtpr = period_counts - 1U;
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (p_instance_ctrl->p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        new_gtpr = period_counts;
    }
#endif

    p_instance_ctrl->p_reg->GTPBR = new_gtpr;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Set a 50% duty cycle so the period of the waveform on the output pin matches the requested period. */
    if (TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode)
    {
        /* The  GTIOCA/GTIOCB pins transition 1 cycle after compare match when buffer operation is used. Reference
         * Figure 23.34 "Example setting for saw-wave PWM mode" in the RA6M3 manual R01UH0886EJ0100. To get a duty cycle
         * as close to 50% as possible, duty cycle (register) = (period (counts) / 2) - 1. */
        uint32_t duty_cycle_50_percent = (period_counts >> 1) - 1U;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRC] = duty_cycle_50_percent;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRD] = duty_cycle_50_percent;
    }
#endif

    /* If the counter is not counting, update period register and reset counter. */
    if (0U == p_instance_ctrl->p_reg->GTCR_b.CST)
    {
        p_instance_ctrl->p_reg->GTPR = new_gtpr;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE
        p_instance_ctrl->p_reg->GTBER = GPT_PRV_GTBER_BUFFER_ENABLE_FORCE_TRANSFER;
#endif

        p_instance_ctrl->p_reg->GTCLR = p_instance_ctrl->channel_mask;
    }

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets duty cycle on requested pin. Implements @ref timer_api_t::dutyCycleSet.
 *
 * Duty cycle is updated in the buffer register. The updated duty cycle is reflected after the next cycle end (counter
 * overflow).
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_DutyCycleSet
 *
 * @param[in] p_ctrl                   Pointer to instance control block.
 * @param[in] duty_cycle_counts        Duty cycle to set in counts.
 * @param[in] pin                      Use gpt_io_pin_t to select GPT_IO_PIN_GTIOCA or GPT_IO_PIN_GTIOCB
 *
 * @retval FSP_SUCCESS                 Duty cycle updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL or the pin is not one of gpt_io_pin_t
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    Duty cycle is larger than period.
 * @retval FSP_ERR_UNSUPPORTED         GPT_CFG_OUTPUT_SUPPORT_ENABLE is 0.
 **********************************************************************************************************************/
fsp_err_t R_GPT_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
#if GPT_CFG_OUTPUT_SUPPORT_ENABLE
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
 #if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(pin <= GPT_IO_PIN_GTIOCA_AND_GTIOCB);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(duty_cycle_counts <= (p_instance_ctrl->p_reg->GTPR + 1), FSP_ERR_INVALID_ARGUMENT);
 #endif

    /* Set duty cycle. */
    gpt_prv_duty_registers_t duty_regs = {UINT32_MAX, 0};
    gpt_calculate_duty_cycle(p_instance_ctrl, duty_cycle_counts, &duty_regs);

    r_gpt_write_protect_disable(p_instance_ctrl);

    p_instance_ctrl->p_reg->GTCCR[pin + 2] = duty_regs.gtccr_buffer;

    /* Read modify write bitfield access is used to update GTUDDTYC to make sure we don't clobber settings for the
     * other pin. */

    uint32_t gtuddtyc = p_instance_ctrl->p_reg->GTUDDTYC;
    if (GPT_IO_PIN_GTIOCB != pin)
    {
        /* GTIOCA or both GTIOCA and GTIOCB. */
        gtuddtyc &= ~R_GPT0_GTUDDTYC_OADTY_Msk;
        gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OADTY_Pos;
    }

    if (GPT_IO_PIN_GTIOCA != pin)
    {
        /* GTIOCB or both GTIOCA and GTIOCB. */
        gtuddtyc &= ~R_GPT0_GTUDDTYC_OBDTY_Msk;
        gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OBDTY_Pos;
    }

    p_instance_ctrl->p_reg->GTUDDTYC = gtuddtyc;

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(duty_cycle_counts);
    FSP_PARAMETER_NOT_USED(pin);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif
}

/*******************************************************************************************************************//**
 * Get timer information and store it in provided pointer p_info. Implements @ref timer_api_t::infoGet.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, frequency, and ELC event written to caller's
 *                                     structure successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_info was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get and store period */
    uint32_t gtpr          = p_instance_ctrl->p_reg->GTPR;
    uint32_t period_counts = gtpr + 1;
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (p_instance_ctrl->p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        period_counts = gtpr;
    }
#endif
    p_info->period_counts = period_counts;

    /* Get and store clock frequency */
    p_info->clock_frequency = gpt_clock_frequency_get(p_instance_ctrl);

    /* Get and store clock counting direction. Read count direction setting */
    p_info->count_direction = TIMER_DIRECTION_UP;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current timer status and store it in provided pointer p_status. Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_gpt_example.c R_GPT_StatusGet
 *
 * @retval FSP_SUCCESS                 Current timer state and counter value set successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get counter state. */
    p_status->state = (timer_state_t) p_instance_ctrl->p_reg->GTCR_b.CST;

    /* Get counter value */
    p_status->counter = p_instance_ctrl->p_reg->GTCNT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set counter value.
 *
 * @note Do not call this API while the counter is counting.  The counter value can only be updated while the counter
 * is stopped.
 *
 * @retval FSP_SUCCESS                 Counter value updated.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_IN_USE              The timer is running.  Stop the timer before calling this function.
 **********************************************************************************************************************/
fsp_err_t R_GPT_CounterSet (timer_ctrl_t * const p_ctrl, uint32_t counter)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(0U == p_instance_ctrl->p_reg->GTCR_b.CST, FSP_ERR_IN_USE);
#endif

    r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set counter value */
    p_instance_ctrl->p_reg->GTCNT = counter;

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable output for GTIOCA and/or GTIOCB.
 *
 * @retval FSP_SUCCESS                 Output is enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_OutputEnable (timer_ctrl_t * const p_ctrl, gpt_io_pin_t pin)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_gpt_write_protect_disable(p_instance_ctrl);

    uint32_t gtior = p_instance_ctrl->p_reg->GTIOR;
    if (GPT_IO_PIN_GTIOCB != pin)
    {
        /* GTIOCA or both GTIOCA and GTIOCB. */
        gtior |= R_GPT0_GTIOR_OAE_Msk;
    }

    if (GPT_IO_PIN_GTIOCA != pin)
    {
        /* GTIOCB or both GTIOCA and GTIOCB. */
        gtior |= R_GPT0_GTIOR_OBE_Msk;
    }

    p_instance_ctrl->p_reg->GTIOR = gtior;

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable output for GTIOCA and/or GTIOCB.
 *
 * @retval FSP_SUCCESS                 Output is disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_OutputDisable (timer_ctrl_t * const p_ctrl, gpt_io_pin_t pin)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_gpt_write_protect_disable(p_instance_ctrl);

    uint32_t gtior = p_instance_ctrl->p_reg->GTIOR;
    if (GPT_IO_PIN_GTIOCB != pin)
    {
        /* GTIOCA or both GTIOCA and GTIOCB. */
        gtior &= ~R_GPT0_GTIOR_OAE_Msk;
    }

    if (GPT_IO_PIN_GTIOCA != pin)
    {
        /* GTIOCB or both GTIOCA and GTIOCB. */
        gtior &= ~R_GPT0_GTIOR_OBE_Msk;
    }

    p_instance_ctrl->p_reg->GTIOR = gtior;

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set A/D converter start request compare match value.
 *
 * @retval FSP_SUCCESS                 Counter value updated.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_AdcTriggerSet (timer_ctrl_t * const    p_ctrl,
                               gpt_adc_compare_match_t which_compare_match,
                               uint32_t                compare_match_value)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_gpt_write_protect_disable(p_instance_ctrl);

    /* Set A/D converter start request compare match value. */
    volatile uint32_t * p_gtadtr = &p_instance_ctrl->p_reg->GTADTRA;
    p_gtadtr[which_compare_match] = compare_match_value;

    r_gpt_write_protect_enable(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops counter, disables output pins, and clears internal driver data. Implements @ref timer_api_t::close.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_Close (timer_ctrl_t * const p_ctrl)
{
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;

#if GPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    r_gpt_write_protect_disable(p_instance_ctrl);

    /* Stop counter. */
    p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

    /* Disable output. */
    p_instance_ctrl->p_reg->GTIOR = 0U;

    r_gpt_write_protect_enable(p_instance_ctrl);

    /* Disable interrupts. */
    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    r_gpt_disable_irq(p_instance_ctrl->p_cfg->cycle_end_irq);
    r_gpt_disable_irq(p_extend->capture_a_irq);
    r_gpt_disable_irq(p_extend->capture_b_irq);
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    gpt_extended_pwm_cfg_t const * p_pwm_cfg = p_extend->p_pwm_cfg;
    if (NULL != p_pwm_cfg)
    {
        r_gpt_disable_irq(p_pwm_cfg->trough_irq);
    }
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Sets driver version based on compile time macros. Implements @ref timer_api_t::versionGet.
 *
 * @retval FSP_SUCCESS                 Version stored in p_version.
 * @retval FSP_ERR_ASSERTION           p_version was NULL.
 **********************************************************************************************************************/
fsp_err_t R_GPT_VersionGet (fsp_version_t * const p_version)
{
#if GPT_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_gpt_version.version_id;

    return FSP_SUCCESS;
}

/** @} (end addtogroup GPT) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enables write protection.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_enable (gpt_instance_ctrl_t * const p_instance_ctrl)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    p_instance_ctrl->p_reg->GTWP = GPT_PRV_GTWP_WRITE_PROTECT;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * Disables write protection.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_disable (gpt_instance_ctrl_t * const p_instance_ctrl)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    p_instance_ctrl->p_reg->GTWP = GPT_PRV_GTWP_RESET_VALUE;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * Initializes control structure based on configuration.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 * @param[in]  p_cfg                   Pointer to timer configuration.
 **********************************************************************************************************************/
static void gpt_common_open (gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Initialize control structure.  */
    p_instance_ctrl->p_cfg = p_cfg;

    /* If callback is not null or timer mode is one shot, make sure the IRQ is enabled and store callback in the
     *  control block.
     *  @note The GPT hardware does not support one-shot mode natively.  To support one-shot mode, the timer will be
     *  stopped and cleared using software in the ISR. *//* Determine if this is a 32-bit or a 16-bit timer. */
    p_instance_ctrl->variant = TIMER_VARIANT_16_BIT;
    if (0U != (p_instance_ctrl->channel_mask & BSP_FEATURE_GPT_32BIT_CHANNEL_MASK))
    {
        p_instance_ctrl->variant = TIMER_VARIANT_32_BIT;
    }

    /* Save register base address. */
    uint32_t base_address = (uint32_t) R_GPT0 + (p_cfg->channel * ((uint32_t) R_GPT1 - (uint32_t) R_GPT0));
    p_instance_ctrl->p_reg = (R_GPT0_Type *) base_address;
}

/*******************************************************************************************************************//**
 * Performs hardware initialization of the GPT.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void gpt_hardware_initialize (gpt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Save pointer to extended configuration structure. */
    gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_cfg->p_extend;

    /* Power on GPT before setting any hardware registers. Make sure the counter is stopped before setting mode
     * register, PCLK divisor register, and counter register. */
    R_BSP_MODULE_START(FSP_IP_GPT, p_cfg->channel);

    /* Initialize all registers that may affect operation of this driver to reset values.  Skip these since they
     * affect all channels, and are initialized in GTCR and GTCNT: GTSTR, GTSTP, GTCLR. GTCR is set immediately after
     * clearing the module stop bit to ensure the timer is stopped before proceeding with configuration. */
    p_instance_ctrl->p_reg->GTWP  = GPT_PRV_GTWP_RESET_VALUE;
    p_instance_ctrl->p_reg->GTCR  = 0U;
    p_instance_ctrl->p_reg->GTST  = 0U;
    p_instance_ctrl->p_reg->GTCNT = 0U;

    /* GTPR, GTCCRn, GTIOR, GTSSR, GTPSR, GTCSR, GTUPSR, GTDNSR, GTPBR, and GTUDDTYC are set by this driver. */

    /* Initialization sets all register required for up counting as described in hardware manual (Figure 23.4 in the
     * RA6M3 manual R01UH0886EJ0100) and other registers required by the driver. */

    /* Dividers for GPT are half the enum value. */
    uint32_t gtcr_tpcs = p_cfg->source_div >> 1;
    uint32_t gtcr      = gtcr_tpcs << R_GPT0_GTCR_TPCS_Pos;

    /* Store period register setting. The actual period and is one cycle longer than the register value for saw waves
     * and twice the register value for triangle waves. Reference section 23.2.21 "General PWM Timer Cycle Setting
     * Register (GTPR)". The setting passed to the configuration is expected to be half the desired period for
     * triangle waves. */
    uint32_t gtpr = p_cfg->period_counts - 1U;
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Saw-wave PWM mode is set in GTCR.MD for all modes except TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM and
     * TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM. */
    if (p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        gtcr |= ((uint32_t) p_cfg->mode << R_GPT0_GTCR_MD_Pos);
        gtpr  = p_cfg->period_counts;
    }
#endif

    /* Counter must be stopped to update TPCS. Reference section 23.2.12 "General PWM Timer Control Register (GTCR)"
     * in the RA6M3 manual R01UH0886EJ0100. */
    p_instance_ctrl->p_reg->GTCR = gtcr;

    gpt_hardware_events_disable(p_instance_ctrl);

    /* Configure the up/down count sources. These are not affected by enable/disable. */
    p_instance_ctrl->p_reg->GTUPSR = p_extend->count_up_source;
    p_instance_ctrl->p_reg->GTDNSR = p_extend->count_down_source;

    /* Set period. The actual period is one cycle longer than the register value. Reference section 23.2.21
     * "General PWM Timer Cycle Setting Register (GTPR)". */
    p_instance_ctrl->p_reg->GTPBR = gtpr;
    p_instance_ctrl->p_reg->GTPR  = gtpr;

    uint32_t gtuddtyc = 0U;
    uint32_t gtior    = 0U;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* For one shot mode, the compare match buffer register must be loaded with a value that exceeds the timer
     * cycle end value so that second compare match event would never occur and hence there will be only a
     * single pulse.  Writing to the upper bits is ignored for 16-bit timers. */
    gpt_prv_duty_registers_t duty_regs = {UINT32_MAX, 0};

    if (TIMER_MODE_PERIODIC == p_cfg->mode)
    {
        /* The  GTIOCA/GTIOCB pins transition 1 cycle after compare match when buffer operation is used. Reference
         * Figure 23.34 "Example setting for saw-wave PWM mode" in the RA6M3 manual R01UH0886EJ0100. To get a duty cycle
         * as close to 50% as possible, duty cycle (register) = (period (counts) / 2) - 1. */
        uint32_t duty_cycle_50_percent = (p_cfg->period_counts >> 1) - 1U;
        duty_regs.gtccr_buffer = duty_cycle_50_percent;
    }

    if (p_cfg->mode >= TIMER_MODE_PWM)
    {
        gpt_calculate_duty_cycle(p_instance_ctrl, p_cfg->duty_cycle_counts, &duty_regs);
    }

    /* Set the compare match and compare match buffer registers based on previously calculated values. */
    p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRC] = duty_regs.gtccr_buffer;
    p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRD] = duty_regs.gtccr_buffer;

    /* If the requested duty cycle is 0% or 100%, set this in the registers. */
    gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OADTY_Pos;
    gtuddtyc |= duty_regs.omdty << R_GPT0_GTUDDTYC_OBDTY_Pos;

    /* Calculate GTIOR. */
    if (p_extend->gtioca.output_enabled)
    {
        uint32_t gtioca_gtior = gpt_gtior_calculate(p_cfg, p_extend->gtioca.stop_level);
        gtior |= gtioca_gtior << R_GPT0_GTIOR_GTIOA_Pos;
    }

    if (p_extend->gtiocb.output_enabled)
    {
        uint32_t gtiocb_gtior = gpt_gtior_calculate(p_cfg, p_extend->gtiocb.stop_level);
        gtior |= gtiocb_gtior << R_GPT0_GTIOR_GTIOB_Pos;
    }
#endif

#if GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK
    if ((1U << p_cfg->channel) & GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK)
    {
        /* This register is available on GPTE and GPTEH only. It must be cleared before setting. When modifying the
         * IVTT[2:0] bits, first set the IVTC[1:0] bits to 00b.  Reference section 23.2.18 "General PWM Timer Interrupt
         * and A/D Converter Start Request Skipping Setting Register (GTITC)"" of the RA6M3 manual R01UH0886EJ0100. */
        p_instance_ctrl->p_reg->GTITC = 0U;
    }
#endif

#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    gpt_extended_pwm_cfg_t const * p_pwm_cfg = p_extend->p_pwm_cfg;
    if (NULL != p_pwm_cfg)
    {
        p_instance_ctrl->p_reg->GTINTAD = ((uint32_t) p_pwm_cfg->output_disable << R_GPT0_GTINTAD_GRPDTE_Pos) |
                                          ((uint32_t) p_pwm_cfg->poeg_link << R_GPT0_GTINTAD_GRP_Pos) |
                                          ((uint32_t) p_pwm_cfg->adc_trigger << R_GPT0_GTINTAD_ADTRAUEN_Pos);
        p_instance_ctrl->p_reg->GTDVU = p_pwm_cfg->dead_time_count_up;

        /* Set GTDTCR.TDE only if one of the dead time values is non-zero. */
        uint32_t gtdtcr = ((p_pwm_cfg->dead_time_count_up > 0) || (p_pwm_cfg->dead_time_count_down > 0));

 #if GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK
        if ((1U << p_cfg->channel) & GPT_PRV_GPTE_OR_GPTEH_CHANNEL_MASK)
        {
            /* These registers are only available on GPTE and GPTEH. */
            p_instance_ctrl->p_reg->GTITC = ((uint32_t) p_pwm_cfg->interrupt_skip_source << R_GPT0_GTITC_IVTC_Pos) |
                                            ((uint32_t) p_pwm_cfg->interrupt_skip_count << R_GPT0_GTITC_IVTT_Pos) |
                                            ((uint32_t) p_pwm_cfg->interrupt_skip_adc << R_GPT0_GTITC_ADTAL_Pos);
            p_instance_ctrl->p_reg->GTDVD   = p_pwm_cfg->dead_time_count_down;
            p_instance_ctrl->p_reg->GTADTRA = p_pwm_cfg->adc_a_compare_match;
            p_instance_ctrl->p_reg->GTADTRB = p_pwm_cfg->adc_b_compare_match;
        }
 #endif

        gtior |= (uint32_t) (p_pwm_cfg->gtioca_disable_setting << R_GPT0_GTIOR_OADF_Pos);
        gtior |= (uint32_t) (p_pwm_cfg->gtiocb_disable_setting << R_GPT0_GTIOR_OBDF_Pos);

        p_instance_ctrl->p_reg->GTDTCR = gtdtcr;
    }
    else
#endif
    {
        /* GTADTR* registers are unused if GTINTAD is cleared. */
        p_instance_ctrl->p_reg->GTINTAD = 0U;
        p_instance_ctrl->p_reg->GTDTCR  = 0U;

        /* GTDVU, GTDVD, GTDBU, GTDBD, and GTSOTR are not used if GTDTCR is cleared. */
    }

    /* Configure the noise filter for the GTIOC pins. */
    gtior |= (uint32_t) (p_extend->capture_filter_gtioca << R_GPT0_GTIOR_NFAEN_Pos);
    gtior |= (uint32_t) (p_extend->capture_filter_gtiocb << R_GPT0_GTIOR_NFBEN_Pos);

    /* Enable the compare match buffer. */
    p_instance_ctrl->p_reg->GTBER = GPT_PRV_GTBER_BUFFER_ENABLE_FORCE_TRANSFER;

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (TIMER_MODE_ONE_SHOT == p_cfg->mode)
    {
        /* In one shot mode, the output pin toggles when counting starts, then again when the period expires.
         * The buffer is enabled to set the compare match to UINT32_MAX after the one shot pulse is output
         * so that the pin level will not change if the period expires again before the timer is stopped in
         * the interrupt.*/
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRA] = 0U;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRB] = 0U;
    }
#endif

    /* Reset counter to 0. */
    p_instance_ctrl->p_reg->GTCLR = p_instance_ctrl->channel_mask;

    /* Set the I/O control register. */
    p_instance_ctrl->p_reg->GTIOR = gtior;

    /* Configure duty cycle and force timer to count up. GTUDDTYC must be set, then cleared to force the count
     * direction to be reflected when counting starts. Reference section 23.2.13 "General PWM Timer Count Direction
     * and Duty Setting Register (GTUDDTYC)" in the RA6M3 manual R01UH0886EJ0100. */
    p_instance_ctrl->p_reg->GTUDDTYC = gtuddtyc | 3U;
    p_instance_ctrl->p_reg->GTUDDTYC = gtuddtyc | 1U;

    r_gpt_write_protect_enable(p_instance_ctrl);

    /* Enable CPU interrupts if callback is not null.  Also enable interrupts for one shot mode.
     *  @note The GPT hardware does not support one-shot mode natively. To support one-shot mode, the timer will be
     *  stopped and cleared using software in the ISR. */
    r_gpt_enable_irq(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);
    r_gpt_enable_irq(p_extend->capture_a_irq, p_extend->capture_a_ipl, p_instance_ctrl);
    r_gpt_enable_irq(p_extend->capture_b_irq, p_extend->capture_b_ipl, p_instance_ctrl);
#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    if (NULL != p_pwm_cfg)
    {
        r_gpt_enable_irq(p_pwm_cfg->trough_irq, p_pwm_cfg->trough_ipl, p_instance_ctrl);
    }
#endif
}

/*******************************************************************************************************************//**
 * Disables hardware events that would cause the timer to start, stop, clear, or capture.
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 **********************************************************************************************************************/
static void gpt_hardware_events_disable (gpt_instance_ctrl_t * p_instance_ctrl)
{
    /* Enable use of GTSTR, GTSTP, and GTCLR for this channel. */
    p_instance_ctrl->p_reg->GTSSR   = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    p_instance_ctrl->p_reg->GTPSR   = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    p_instance_ctrl->p_reg->GTCSR   = GPT_PRV_ENABLE_GROUP_SOFTWARE_UPDATE;
    p_instance_ctrl->p_reg->GTICASR = GPT_SOURCE_NONE;
    p_instance_ctrl->p_reg->GTICBSR = GPT_SOURCE_NONE;
}

/*******************************************************************************************************************//**
 * Disables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 **********************************************************************************************************************/
static void r_gpt_disable_irq (IRQn_Type irq)
{
    /* Disable interrupts. */
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Configures and enables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 * @param[in]  priority                NVIC priority of the interrupt
 * @param[in]  p_context               The interrupt context is a pointer to data required in the ISR.
 **********************************************************************************************************************/
static void r_gpt_enable_irq (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, priority, p_context);
    }
}

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Calculates duty cycle register values.  GTPR must be set before entering this function.
 *
 * @param[in]  p_instance_ctrl         Instance control structure
 * @param[in]  duty_cycle_counts       Duty cycle to set
 * @param[out] p_duty_reg              Duty cycle register values
 **********************************************************************************************************************/
static void gpt_calculate_duty_cycle (gpt_instance_ctrl_t * const p_instance_ctrl,
                                      uint32_t const              duty_cycle_counts,
                                      gpt_prv_duty_registers_t  * p_duty_reg)
{
    /* 0% and 100% duty cycle are supported in OADTY/OBDTY. */
    uint32_t current_period = p_instance_ctrl->p_reg->GTPR;
    if (0U == duty_cycle_counts)
    {
        p_duty_reg->omdty = GPT_DUTY_CYCLE_MODE_0_PERCENT;
    }
    else if (duty_cycle_counts >= current_period)
    {
        p_duty_reg->omdty = GPT_DUTY_CYCLE_MODE_100_PERCENT;
    }
    else
    {
        uint32_t temp_duty_cycle = duty_cycle_counts;

        /* When the GPT_SHORTEST_LEVEL_ON is set, the high part of the PWM wave is at the end of the cycle. */
        gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
        if (GPT_SHORTEST_LEVEL_ON == p_extend->shortest_pwm_signal)
        {
            temp_duty_cycle = current_period - temp_duty_cycle;
        }

 #if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
        if (p_instance_ctrl->p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
        {
            p_duty_reg->gtccr_buffer = temp_duty_cycle;
        }
        else
 #endif
        {
            /* The GTIOCA/GTIOCB pins transition 1 cycle after compare match when buffer operation is used. Reference
             * Figure 23.34 "Example setting for saw-wave PWM mode" in the RA6M3 manual R01UH0886EJ0100. */
            temp_duty_cycle--;
            p_duty_reg->gtccr_buffer = temp_duty_cycle;
        }
    }
}

#endif

/*******************************************************************************************************************//**
 * Calculates clock frequency of GPT counter.  Divides GPT clock by GPT clock divisor.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 *
 * @return     Clock frequency of the GPT counter.
 **********************************************************************************************************************/
static uint32_t gpt_clock_frequency_get (gpt_instance_ctrl_t * const p_instance_ctrl)
{
    /* Look up PCLKD frequency and divide it by GPT PCLKD divider. */
    timer_source_div_t pclk_divisor = (timer_source_div_t) (p_instance_ctrl->p_reg->GTCR_b.TPCS << 1);
    uint32_t           pclk_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD);

    return pclk_freq_hz >> pclk_divisor;
}

#if GPT_CFG_OUTPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Calculates GTIOR settings for given mode and stop level.
 *
 * @param[in]  p_instance_ctrl         Instance control block
 * @param[in]  p_cfg                   Timer configuration
 * @param[in]  level                   Output level after timer stops
 **********************************************************************************************************************/
static uint32_t gpt_gtior_calculate (timer_cfg_t const * const p_cfg, gpt_pin_level_t const stop_level)
{
    /* The stop level is used as both the initial level and the stop level. */
    uint32_t gtior = R_GPT0_GTIOR_OAE_Msk | ((uint32_t) stop_level << GPT_PRV_GTIOR_STOP_LEVEL_BIT) |
                     ((uint32_t) stop_level << GPT_PRV_GTIOR_INITIAL_LEVEL_BIT);

    uint32_t        gtion         = GPT_PRV_GTIO_LOW_COMPARE_MATCH_HIGH_CYCLE_END;
    gpt_pin_level_t compare_match = GPT_PIN_LEVEL_LOW;

    if (TIMER_MODE_PWM == p_cfg->mode)
    {
        gpt_extended_cfg_t * p_extend = (gpt_extended_cfg_t *) p_cfg->p_extend;
        if (GPT_SHORTEST_LEVEL_ON == p_extend->shortest_pwm_signal)
        {
            /* Output high after compare match when GPT_SHORTEST_LEVEL_ON is used to generate the shortest PWM duty cycle. */
            compare_match = GPT_PIN_LEVEL_HIGH;
        }
    }

 #if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE
    else if (p_cfg->mode >= TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM)
    {
        gtion = GPT_PRV_GTIO_TOGGLE_COMPARE_MATCH;
    }
 #endif
    else
    {
        /* In one-shot mode, the output pin goes high after the first compare match (one cycle after the timer starts counting). */
        if (GPT_PIN_LEVEL_LOW == stop_level)
        {
            compare_match = GPT_PIN_LEVEL_HIGH;
        }
    }

    if (compare_match == GPT_PIN_LEVEL_HIGH)
    {
        gtion = GPT_PRV_GTIO_HIGH_COMPARE_MATCH_LOW_CYCLE_END;
    }

    gtior |= gtion;

    return gtior;
}

#endif

/*******************************************************************************************************************//**
 * Common processing for input capture interrupt.
 *
 * @param[in]  event  Which input capture event occurred
 **********************************************************************************************************************/
static void r_gpt_capture_common_isr (gpt_prv_capture_event_t event)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Get captured value. */
    uint32_t counter = p_instance_ctrl->p_reg->GTCCR[event];

    /* If we captured a one-shot pulse, then disable future captures. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        /* Disable captures. */
        gpt_hardware_events_disable(p_instance_ctrl);

        /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
        R_BSP_IrqClearPending(irq);
    }

    /* If a callback is provided, then call it with the captured counter value. */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        timer_callback_args_t callback_args;
        callback_args.event     = (timer_event_t) ((uint32_t) TIMER_EVENT_CAPTURE_A + (uint32_t) event);
        callback_args.capture   = counter;
        callback_args.p_context = p_instance_ctrl->p_cfg->p_context;
        p_instance_ctrl->p_cfg->p_callback(&callback_args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Stops the timer if one-shot mode, clears interrupts, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void gpt_counter_overflow_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* If one-shot mode is selected, stop the timer since period has expired. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        r_gpt_write_protect_disable(p_instance_ctrl);

        p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

        /* Clear the GPT counter and the overflow flag after the one shot pulse has being generated */
        p_instance_ctrl->p_reg->GTCNT                 = 0;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRA] = 0;
        p_instance_ctrl->p_reg->GTCCR[GPT_PRV_GTCCRB] = 0;

        r_gpt_write_protect_enable(p_instance_ctrl);

        /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
        R_BSP_IrqClearPending(irq);
    }

    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        /* Set data to identify callback to user, then call user callback. */
        timer_callback_args_t callback_args;
        callback_args.p_context = p_instance_ctrl->p_cfg->p_context;
        callback_args.event     = TIMER_EVENT_CYCLE_END;
        p_instance_ctrl->p_cfg->p_callback(&callback_args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#if GPT_PRV_EXTRA_FEATURES_ENABLED == GPT_CFG_OUTPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Only supported for asymmetric triangle-wave PWM. Notifies application of trough event.
 **********************************************************************************************************************/
void gpt_counter_underflow_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    gpt_instance_ctrl_t * p_instance_ctrl = (gpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Set data to identify callback to user, then call user callback. */
    timer_callback_args_t callback_args;
    callback_args.p_context = p_instance_ctrl->p_cfg->p_context;
    callback_args.event     = TIMER_EVENT_TROUGH;
    p_instance_ctrl->p_cfg->p_callback(&callback_args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture A source.
 *
 * Clears interrupt, disables captures if one-shot mode, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void gpt_capture_a_isr (void)
{
    r_gpt_capture_common_isr(GPT_PRV_CAPTURE_EVENT_A);
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a capture B source.
 *
 * Clears interrupt, disables captures if one-shot mode, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void gpt_capture_b_isr (void)
{
    r_gpt_capture_common_isr(GPT_PRV_CAPTURE_EVENT_B);
}
