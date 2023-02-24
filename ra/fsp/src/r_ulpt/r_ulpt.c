/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "r_ulpt.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "ULPT" in ASCII, used to determine if channel is open. */
#define ULPT_OPEN                           (0x554C5054ULL)

#define ULPT_PRV_ULPTCR_STATUS_FLAGS        (0xE0U)
#define ULPT_PRV_ULPTCMSR_VALID_BITS        (0x77U)

#define ULPT_PRV_ULPTCR_START_TIMER         (0xE1U)
#define ULPT_PRV_ULPTCR_STOP_TIMER          (0xE0U)
#define ULPT_PRV_ULPTCR_FORCE_STOP_TIMER    (0xE4U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * ulpt_prv_ns_callback)(timer_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile ulpt_prv_ns_callback)(timer_callback_args_t * p_args);
#endif
/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t r_ulpt_common_preamble(ulpt_instance_ctrl_t * p_instance_ctrl);

static void r_ulpt_hardware_cfg(ulpt_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg);

static void r_ulpt_period_register_set(ulpt_instance_ctrl_t * p_instance_ctrl, uint32_t period_counts);
static uint32_t r_ulpt_clock_frequency_get (R_ULPT0_Type * p_ulpt_regs);

#if ULPT_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_ulpt_open_param_checking(ulpt_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg);

#endif

/* ISRs. */
void ulpt_int_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** ULPT implementation of General Timer Driver. */
const timer_api_t g_timer_on_ulpt =
{
    .open         = R_ULPT_Open,
    .stop         = R_ULPT_Stop,
    .start        = R_ULPT_Start,
    .reset        = R_ULPT_Reset,
    .enable       = R_ULPT_Enable,
    .disable      = R_ULPT_Disable,
    .periodSet    = R_ULPT_PeriodSet,
    .dutyCycleSet = R_ULPT_DutyCycleSet,
    .infoGet      = R_ULPT_InfoGet,
    .statusGet    = R_ULPT_StatusGet,
    .callbackSet  = R_ULPT_CallbackSet,
    .close        = R_ULPT_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup ULPT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the ULPT module instance. Implements @ref timer_api_t::open.
 *
 * The ULPT implementation of the general timer can accept an optional ulpt_extended_cfg_t extension parameter.  For
 * ULPT, the extension specifies the clock to be used as timer source and the output pin configurations.  If the
 * extension parameter is not specified (NULL), the default clock LOCO is used and the output pins are disabled.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_Open
 *
 * @retval FSP_SUCCESS                 Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION           A required input pointer is NULL or the period is not in the valid range of
 *                                     1 to 0xFFFF.
 * @retval FSP_ERR_ALREADY_OPEN        R_ULPT_Open has already been called for this p_ctrl.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    A required interrupt has not been enabled in the vector table.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel number is not available on ULPT.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;

#if ULPT_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_ulpt_open_param_checking(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    uint32_t base_address =  (uint32_t) R_ULPT0_BASE + (p_cfg->channel * ((uint32_t)R_ULPT1_BASE - (uint32_t)R_ULPT0_BASE));
    p_instance_ctrl->p_reg = (R_ULPT0_Type *) base_address;

    p_instance_ctrl->p_cfg = p_cfg;

    /* Power on the ULPT channel. */
    R_BSP_MODULE_START(FSP_IP_ULPT, p_cfg->channel);

    /* Clear ULPTCR. This stops the timer if it is running and clears the flags. */
    p_instance_ctrl->p_reg->ULPTCR = 0U;

    /* The timer is stopped in sync with the count source. */
    FSP_HARDWARE_REGISTER_WAIT(0U, p_instance_ctrl->p_reg->ULPTCR_b.TCSTF);

    /* Clear ULPTMR2 before ULPTMR1 to prevent clock destablization if the mode is changed. */
    p_instance_ctrl->p_reg->ULPTMR2 = 0U;

    /* Set count source and divider and configure pins. */
    r_ulpt_hardware_cfg(p_instance_ctrl, p_cfg);

    /* Set period register and update duty cycle if output mode is used. */
    r_ulpt_period_register_set(p_instance_ctrl, p_cfg->period_counts);

    if (p_cfg->cycle_end_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);
    }

    /* Set callback and context pointers */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    p_instance_ctrl->open = ULPT_OPEN;

    /* All done.  */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer. Implements @ref timer_api_t::start.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_Start
 *
 * @retval FSP_SUCCESS                 Timer started.
 * @retval FSP_ERR_ASSERTION           p_ctrl is null.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_Start (timer_ctrl_t * const p_ctrl)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Start timer */
    p_instance_ctrl->p_reg->ULPTCR = ULPT_PRV_ULPTCR_START_TIMER;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops the timer.  Implements @ref timer_api_t::stop.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_Stop
 *
 * @retval FSP_SUCCESS                 Timer stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_Stop (timer_ctrl_t * const p_ctrl)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Stop timer */
    p_instance_ctrl->p_reg->ULPTCR = ULPT_PRV_ULPTCR_STOP_TIMER;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to the period minus one. Implements @ref timer_api_t::reset.
 *
 * @retval FSP_SUCCESS                 Counter reset.
 * @retval FSP_ERR_ASSERTION           p_ctrl is NULL
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_Reset (timer_ctrl_t * const p_ctrl)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Reset counter to period minus one. */
    p_instance_ctrl->p_reg->ULPTCNT = p_instance_ctrl->period - 1U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::enable.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_Enable
 *
 * @retval FSP_SUCCESS                 External events successfully enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_Enable (timer_ctrl_t * const p_ctrl)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;
#if ULPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ULPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Reset counter to period minus one. */
    p_instance_ctrl->p_reg->ULPTCNT = p_instance_ctrl->period - 1U;

    /* Enable captures. */
    p_instance_ctrl->p_reg->ULPTCR = ULPT_PRV_ULPTCR_START_TIMER;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::disable.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_Disable
 *
 * @retval FSP_SUCCESS                 External events successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_Disable (timer_ctrl_t * const p_ctrl)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;
#if ULPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ULPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable captures. */
    p_instance_ctrl->p_reg->ULPTCR = ULPT_PRV_ULPTCR_STOP_TIMER;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates period. The new period is updated immediately and the counter is reset to the maximum value. Implements
 * @ref timer_api_t::periodSet.
 *
 * @warning If periodic output is used, the duty cycle buffer registers are updated after the period buffer register.
 * If this function is called while the timer is running and an AGT underflow occurs during processing, the duty cycle
 * will not be the desired 50% duty cycle until the counter underflow after processing completes.
 *
 * @warning Stop the timer before calling this function if one-shot output is used.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value updated.
 * @retval FSP_ERR_ASSERTION           A required pointer was NULL, or the period was not in the valid range of
 *                                     1 to 0xFFFF.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;
#if ULPT_CFG_PARAM_CHECKING_ENABLE

    /* Validate period parameter. */
    FSP_ASSERT(0U != period_counts);
#endif

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set period. */
    r_ulpt_period_register_set(p_instance_ctrl, period_counts);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates duty cycle. If the timer is counting, the new duty cycle is reflected after the next counter underflow.
 * Implements @ref timer_api_t::dutyCycleSet.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_DutyCycleSet
 *
 * @retval FSP_SUCCESS                 Duty cycle updated.
 * @retval FSP_ERR_ASSERTION           A required pointer was NULL, or the pin was not ULPT_ULPTO_ULPTOA or ULPT_ULPTO_ULPTOB.
 * @retval FSP_ERR_INVALID_ARGUMENT    Duty cycle was not in the valid range of 0 to period (counts) - 1
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 * @retval FSP_ERR_UNSUPPORTED         ULPT_CFG_OUTPUT_SUPPORT_ENABLE is 0.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
#if ULPT_CFG_OUTPUT_SUPPORT_ENABLE
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;
 #if ULPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT((pin == ULPT_OUTPUT_PIN_ULPTOA) || (pin == ULPT_OUTPUT_PIN_ULPTOB));
 #endif

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if ULPT_CFG_PARAM_CHECKING_ENABLE
    if (0U != p_instance_ctrl->period)
    {
        FSP_ERROR_RETURN(duty_cycle_counts < (p_instance_ctrl->period), FSP_ERR_INVALID_ARGUMENT);
    }
 #endif

    uint32_t temp_duty_cycle_counts           = duty_cycle_counts;
    uint32_t ulptcmsr_ulptoab_start_level_bit = 1U << 2 << (4 * pin); /* polarity set*/
    ulpt_extended_cfg_t const * p_extend      = (ulpt_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    if (p_extend->ulptoab_settings & ulptcmsr_ulptoab_start_level_bit)
    {
        /* Invert duty cycle if this pin starts high since the high portion is at the beginning of the cycle. */
        temp_duty_cycle_counts = p_instance_ctrl->period - temp_duty_cycle_counts - 1;
    }

    /* Set duty cycle. */
    volatile uint32_t * const p_ulptcm = &p_instance_ctrl->p_reg->ULPTCMA;
    p_ulptcm[pin] = temp_duty_cycle_counts;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(duty_cycle_counts);
    FSP_PARAMETER_NOT_USED(pin);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif
}

/*******************************************************************************************************************//**
 * Gets timer information and store it in provided pointer p_info. Implements @ref timer_api_t::infoGet.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, and frequency stored in p_info.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;
#if ULPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_info);
#endif

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Get and store period */
    p_info->period_counts = p_instance_ctrl->period;

    /* Get and store clock frequency */
    /* ulpt_extended_cfg_t const * p_extend = (ulpt_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;*/
    p_info->clock_frequency = r_ulpt_clock_frequency_get(p_instance_ctrl->p_reg);

    /* ULPT supports only counting down direction */
    p_info->count_direction = TIMER_DIRECTION_DOWN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Retrieves the current state and counter value stores them in p_status. Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_ulpt_example.c R_ULPT_StatusGet
 *
 * @retval FSP_SUCCESS                 Current status and counter value provided in p_status.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;

#if ULPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_status);
#endif

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Read the state. */
    p_status->state = (timer_state_t) p_instance_ctrl->p_reg->ULPTCR_b.TCSTF;

    /* Read counter value */
    p_status->counter = p_instance_ctrl->p_reg->ULPTCNT;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref timer_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_CallbackSet (timer_ctrl_t * const          p_api_ctrl,
                              void (                      * p_callback)(timer_callback_args_t *),
                              void const * const            p_context,
                              timer_callback_args_t * const p_callback_memory)
{
    ulpt_instance_ctrl_t * p_ctrl = (ulpt_instance_ctrl_t *) p_api_ctrl;

#if ULPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(ULPT_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if ULPT_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    timer_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                        CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(timer_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops counter, disables interrupts, disables output pins, and clears internal driver data.  Implements
 * @ref timer_api_t::close.
 *
 *
 *
 * @retval FSP_SUCCESS                 Timer closed.
 * @retval FSP_ERR_ASSERTION           p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ULPT_Close (timer_ctrl_t * const p_ctrl)
{
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_ulpt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Cleanup the device: Stop counter, disable interrupts, and power down if no other channels are in use. */

    /* Stop timer */
    p_instance_ctrl->p_reg->ULPTCR = ULPT_PRV_ULPTCR_FORCE_STOP_TIMER;

    /* Clear ULPT output. */
    p_instance_ctrl->p_reg->ULPTIOC = 0U;

    if (FSP_INVALID_VECTOR != p_instance_ctrl->p_cfg->cycle_end_irq)
    {
        NVIC_DisableIRQ(p_instance_ctrl->p_cfg->cycle_end_irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->cycle_end_irq, p_instance_ctrl);
    }

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/** @} (end addtogroup ULPT) */

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if ULPT_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking for R_ULPT_Open.
 *
 * @param[in] p_instance_ctrl              Pointer to instance control structure.
 * @param[in] p_cfg                        Configuration structure for this instance
 *
 * @retval FSP_SUCCESS                     Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION               A required input pointer is NULL or an invalid parameter exists.
 * @retval FSP_ERR_ALREADY_OPEN            R_ULPT_Open has already been called for this p_ctrl.
 * @retval FSP_ERR_IRQ_BSP_DISABLED        A required interrupt has not been enabled in the vector table.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel number is not available on ULPT.
 **********************************************************************************************************************/
static fsp_err_t r_ulpt_open_param_checking (ulpt_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(ULPT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Validate channel number. */
    FSP_ERROR_RETURN(((1U << p_cfg->channel) & BSP_FEATURE_ULPT_VALID_CHANNEL_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Enable IRQ if user supplied a callback function,
     *  or if the timer is a one-shot timer (so the driver is able to
     *  turn off the timer after one period. */
    if ((NULL != p_cfg->p_callback) || (TIMER_MODE_ONE_SHOT == p_cfg->mode))
    {
        /* Return error if IRQ is required and not in the vector table. */
        FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

     ulpt_extended_cfg_t const * p_extend = (ulpt_extended_cfg_t const *) p_cfg->p_extend;
    /* Validate mode specific settings. */
    if ((ULPT_CLOCK_LOCO == p_extend->count_source) || (ULPT_CLOCK_SUBCLOCK == p_extend->count_source))
    {
        /* Timer mode */

        /* Validate the divider. */
        FSP_ASSERT(p_cfg->source_div <= TIMER_SOURCE_DIV_128);

        /* Count enable,start,amd restart functions are not allowed in timer mode. */
        FSP_ASSERT(p_extend->enable_function != ULPT_ENABLE_FUNCTION_ENABLE_LOW);
        FSP_ASSERT(p_extend->enable_function != ULPT_ENABLE_FUNCTION_ENABLE_HIGH);
        FSP_ASSERT(p_extend->enable_function != ULPT_ENABLE_FUNCTION_START);
        FSP_ASSERT(p_extend->enable_function != ULPT_ENABLE_FUNCTION_RESTART);
    }
    else
    {
        /* Event counter mode */
        /* No Divider allowed. */
        FSP_ASSERT(p_cfg->source_div <= TIMER_SOURCE_DIV_1);
    }
    return (FSP_SUCCESS);
}

#endif

/*******************************************************************************************************************//**
 * Common code at the beginning of all ULPT functions except open.
 *
 * @param[in] p_instance_ctrl          Pointer to instance control structure.
 *
 * @retval FSP_SUCCESS                 No invalid conditions detected, timer state matches expected state.
 * @retval FSP_ERR_ASSERTION           p_ctrl is null.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
static fsp_err_t r_ulpt_common_preamble (ulpt_instance_ctrl_t * p_instance_ctrl)
{
#if ULPT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ULPT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Ensure timer state reflects expected status. */
    uint32_t ulptcr_tstart = p_instance_ctrl->p_reg->ULPTCR_b.TSTART;
    FSP_HARDWARE_REGISTER_WAIT(ulptcr_tstart, p_instance_ctrl->p_reg->ULPTCR_b.TCSTF);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets count source, divider, and other hardware registers.
 *
 * @note Counter must be stopped before entering this function.
 *
 * @param[in]  p_instance_ctrl    Control block for this instance
 * @param[in]  p_cfg              Configuration structure for this instance
 **********************************************************************************************************************/

static void r_ulpt_hardware_cfg (ulpt_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    ulpt_extended_cfg_t const * p_extend = (ulpt_extended_cfg_t const *) p_cfg->p_extend;

    /* ULPT register locals */
    uint32_t ulptmr1  = 0U;
    uint32_t ulptmr2  = 0U;
    uint32_t ulptmr3  = 0U;
    uint32_t ulptioc  = 0U;
    uint32_t ulptisr  = 0U;
    uint32_t ulptcmsr = 0U;

    /* Configure the count source(LOCO or SCK) and mode(event or Timer). */
    ulptmr1 |= p_extend->count_source & (R_ULPT0_ULPTMR1_TMOD1_Msk | R_ULPT0_ULPTMR1_TCK1_Msk);
    
    if (TIMER_MODE_ONE_SHOT == p_cfg->mode)
    {
        ulptmr3 |= R_ULPT0_ULPTMR3_TCNTCTL_Msk;
    }
    if (p_extend->count_source != ULPT_CLOCK_ULPTEVI)
    {
        /* Timer mode */
        ulptmr1 &= ~R_ULPT0_ULPTMR1_TMOD1_Msk;

        /* The divider is only used for normal timer operation. */
        ulptmr2 |= p_cfg->source_div & R_ULPT0_ULPTMR2_CKS_Msk;
    }
#if ULPT_CFG_INPUT_SUPPORT_ENABLE
    else // (p_extend->count_source == ULPT_CLOCK_ULPTEVI)
    {
        /* Event counter mode */
        ulptmr1 |= R_ULPT0_ULPTMR1_TMOD1_Msk;

        /* Set the edge selection for for event pin. */
        /*  For Falling we set it for rising edge and flip the polarity */
        ulptmr1 |= p_extend->event_pin & R_ULPT0_ULPTMR1_TEDGPL_Msk;
        ulptmr3 |= p_extend->event_pin & R_ULPT0_ULPTMR3_TEVPOL_Msk;
        /* Configure input filtering */
        ulptioc |= p_extend->ulptevi_filter & R_ULPT0_ULPTIOC_TIPF_Msk;

        /* Select if the ULPTEE pin should be ignored. */
        ulptioc |= p_extend->enable_function & R_ULPT0_ULPTIOC_TIOGT0_Msk;

        /* Set the active polarity for ULPTEE. This is only set for count enable function. */
        ulptisr |= p_extend->enable_function & R_ULPT0_ULPTISR_RCCPSEL2_Msk;
    }
#endif    



    /* ULPTEE can be used in either timer or event mode. */
    /* Configure ULPTEE pin function and edge polarity for start or restart functions. */
    ulptmr3 |= p_extend->enable_function & R_ULPT0_ULPTMR3_TEECTL_Msk;
    ulptmr3 |= p_extend->trigger_edge & R_ULPT0_ULPTMR3_TEEPOL_Msk;

    
#if ULPT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Set output if requested. */
    if ( p_extend->ulpto != ULPT_PULSE_PIN_CFG_DISABLED)
    {
        ulptioc |= R_ULPT0_ULPTIOC_TOE_Msk;
        /* Now set the polarity*/ 
        if (p_extend->ulpto == ULPT_PULSE_PIN_CFG_ENABLED_START_LEVEL_HIGH)
        {
            ulptmr3 |=  R_ULPT0_ULPTMR3_TOPOL_Msk;
        }
        else
        {
            ulptmr3 &=  ~R_ULPT0_ULPTMR3_TOPOL_Msk;
        }
    }
    /* set enable match, output, and polarity of both match outputs*/
    ulptcmsr = p_extend->ulptoab_settings & ULPT_PRV_ULPTCMSR_VALID_BITS;

    /* Set initial duty cycle for PWM mode in open.  Duty cycle is set for other modes in r_agt_period_register_set. */
    if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        uint32_t inverted_duty_cycle = p_instance_ctrl->p_cfg->period_counts -
                                       p_instance_ctrl->p_cfg->duty_cycle_counts - 1;
        /*In this driver match A and match b have the same duty cycle*/
        uint32_t ulptcma = p_instance_ctrl->p_cfg->duty_cycle_counts;
        uint32_t ulptcmb = p_instance_ctrl->p_cfg->duty_cycle_counts;
        if (ULPT_MATCH_PIN_CFG_DISABLED != p_extend->ulptoab_settings_b.ulptoa)
        {
            if (ULPT_MATCH_PIN_CFG_START_LEVEL_HIGH == p_extend->ulptoab_settings_b.ulptoa)
            {
                ulptcma = inverted_duty_cycle;
            }
            p_instance_ctrl->p_reg->ULPTCMA = ulptcma;
        }
        if (ULPT_MATCH_PIN_CFG_DISABLED != p_extend->ulptoab_settings_b.ulptob)
        {
            if (ULPT_MATCH_PIN_CFG_START_LEVEL_HIGH == p_extend->ulptoab_settings_b.ulptob)
            {
                ulptcmb = inverted_duty_cycle;
            }
            p_instance_ctrl->p_reg->ULPTCMB = ulptcmb;

        }
    }
#endif

    p_instance_ctrl->p_reg->ULPTMR1  = (uint8_t)ulptmr1;
    p_instance_ctrl->p_reg->ULPTMR2  = (uint8_t)ulptmr2;
    p_instance_ctrl->p_reg->ULPTMR3  = (uint8_t)ulptmr3;
    p_instance_ctrl->p_reg->ULPTIOC  = (uint8_t)ulptioc;
    p_instance_ctrl->p_reg->ULPTISR  = (uint8_t)ulptisr;
    p_instance_ctrl->p_reg->ULPTCMSR = (uint8_t)ulptcmsr;
}

/*******************************************************************************************************************//**
 * Sets period register and updates compare match registers in one-shot and periodic mode.
 *
 * @param[in]  p_instance_ctrl    Control block for this instance
 * @param[in]  period_counts      ULPT period in counts
 **********************************************************************************************************************/
static void r_ulpt_period_register_set (ulpt_instance_ctrl_t * p_instance_ctrl, uint32_t period_counts)
{
    /* Store the period value so it can be retrieved later. */
    p_instance_ctrl->period = period_counts;

    uint32_t period_reg = period_counts - 1U;

#if ULPT_CFG_OUTPUT_SUPPORT_ENABLE
    uint32_t duty_cycle_counts = 0U;
    if (TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode)
    {
        duty_cycle_counts = (period_counts >> 1);
    }
    else if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        duty_cycle_counts = period_reg;
    }
    else
    {
        /* Do nothing, duty cycle should not be updated in R_ULPT_PeriodSet. */
    }

    if (TIMER_MODE_PWM != p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->ULPTCMA = duty_cycle_counts;
        p_instance_ctrl->p_reg->ULPTCMB = duty_cycle_counts;
    }
#endif

    /* Set counter to period minus one. */
    p_instance_ctrl->p_reg->ULPTCNT = period_reg;
}

/*******************************************************************************************************************//**
 * Obtains the clock frequency of ULPT for all clock sources 
 *
 * @param[in]  p_ulpt_regs         Registers of ULPT channel used
 *
 * @return Source clock frequency of ULPT in Hz with prescaler divider applied
 **********************************************************************************************************************/
static uint32_t r_ulpt_clock_frequency_get (R_ULPT0_Type * p_ulpt_regs)
{
    uint32_t clock_freq_hz    = 0U;
    uint8_t  count_source_int = p_ulpt_regs->ULPTMR1_b.TCK1;
    uint8_t  divider          = p_ulpt_regs->ULPTMR2_b.CKS;

    if (ULPT_CLOCK_SUBCLOCK == (count_source_int & R_ULPT0_ULPTMR1_TCK1_Msk))
    {
        clock_freq_hz = BSP_SUBCLOCK_FREQ_HZ;
    }
    else
    {
        clock_freq_hz = BSP_LOCO_FREQ_HZ;
    }

    clock_freq_hz >>= divider;

    return clock_freq_hz;
}

/*********************************************************************************************************************
 * AGT counter underflow interrupt.
 **********************************************************************************************************************/
void ulpt_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    uint32_t statusMask;
    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    ulpt_instance_ctrl_t * p_instance_ctrl = (ulpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Save ULPTCR to determine the source of the interrupt. */
    uint32_t ulptcr = p_instance_ctrl->p_reg->ULPTCR;

    /* Invoke the callback function if it is set. */
    if (NULL != p_instance_ctrl->p_callback)
    {
        /* Setup parameters for the user-supplied callback function. */
        timer_callback_args_t callback_args;

        /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
         * stored in non-secure memory so they can be accessed by a non-secure callback function. */
        timer_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
        if (NULL == p_args)
        {
            /* Store on stack */
            p_args = &callback_args;
        }
        else
        {
            /* Save current arguments on the stack in case this is a nested interrupt. */
            callback_args = *p_args;
        }

        if (ulptcr & R_ULPT0_ULPTCR_TUNDF_Msk)
        {
            p_args->event = TIMER_EVENT_CYCLE_END;
        }
        else if (ulptcr & R_ULPT0_ULPTCR_TCMAF_Msk)
        {
            p_args->event = TIMER_EVENT_CAPTURE_A;
        }
        else if (ulptcr & R_ULPT0_ULPTCR_TCMBF_Msk)
        {
            p_args->event = TIMER_EVENT_CAPTURE_B;
        }
        else 
        {

        }

        p_args->p_context = p_instance_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

        /* p_callback can point to a secure function or a non-secure function. */
        if (!cmse_is_nsfptr(p_instance_ctrl->p_callback))
        {
            /* If p_callback is secure, then the project does not need to change security state. */
            p_instance_ctrl->p_callback(p_args);
        }
        else
        {
            /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
            ulpt_prv_ns_callback p_callback = (ulpt_prv_ns_callback) (p_instance_ctrl->p_callback);
            p_callback(p_args);
        }

#else

        /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
        p_instance_ctrl->p_callback(p_args);
#endif

        if (NULL != p_instance_ctrl->p_callback_memory)
        {
            /* Restore callback memory in case this is a nested interrupt. */
            *p_instance_ctrl->p_callback_memory = callback_args;
        }

        /* Retreive AGTCR in case it was modified in the callback. */
        ulptcr = p_instance_ctrl->p_reg->ULPTCR;
    }

    /* Clear flags in AGTCR. */
    /* In one shot mode we need to stop the timer*/
    statusMask = ULPT_PRV_ULPTCR_STATUS_FLAGS;
    if (p_instance_ctrl->p_reg->ULPTMR3 &  R_ULPT0_ULPTMR3_TCNTCTL_Msk)
    {
        statusMask |= R_ULPT0_ULPTCR_TSTART_Msk;
    }

    p_instance_ctrl->p_reg->ULPTCR = (uint8_t) (ulptcr & ~statusMask);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
