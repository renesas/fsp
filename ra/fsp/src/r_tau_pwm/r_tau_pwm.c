/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_tau_pwm.h"
#include "r_tau_pwm_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "TAUP" in ASCII, used to determine if channel is open. */
#define TAU_PWM_OPEN                            (0x54415550ULL)

#define TAU_PWM_PRV_TMR0_MD_INTERVAL_TIMER      (0U)
#define TAU_PWM_PRV_TMR0_MD_ONE_COUNT           (4U)
#define TAU_PWM_PRV_TMR0_STS_TI0n_VALID_EDGE    (1U)
#define TAU_PWM_PRV_TMR0_STS_TAU0_TMI0n         (4U)

#define TAU_PWM_PRV_PERIOD_MAX                  (0x10001U)
#define TAU_PWM_PRV_PERIOD_MIN                  (0x00002U)

/* Shifted mask for TPS0.PRS2 and .PRS3 bitfields */
#define TAU_PRV_PRS2_PRS3_MASK                  (0x3U)

/* Divisor settings for CK02 and CK03 */
#define TAU_PRV_TPS0_PRS3_SETTING               ((BSP_CFG_TAU_CK03 >> 1) & TAU_PRV_PRS2_PRS3_MASK)
#define TAU_PRV_TPS0_PRS2_SETTING               ((BSP_CFG_TAU_CK02 >> 1) & TAU_PRV_PRS2_PRS3_MASK)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_tau_pwm_hardware_initialize(tau_pwm_instance_ctrl_t * const p_instance_ctrl,
                                          timer_cfg_t const * const       p_cfg);

static void r_tau_pwm_master_channel_initialize(tau_pwm_instance_ctrl_t * p_instance_ctrl,
                                                timer_cfg_t const * const p_cfg);

static void r_tau_pwm_slave_channels_initialize(tau_pwm_instance_ctrl_t * p_instance_ctrl,
                                                timer_cfg_t const * const p_cfg);

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_tau_pwm_parameter_checking(tau_pwm_instance_ctrl_t * const p_instance_ctrl,
                                              timer_cfg_t const * const       p_cfg);

#endif

static void r_tau_pwm_disable_irq(IRQn_Type irq);

static void r_tau_pwm_enable_irq(IRQn_Type const irq, uint32_t priority, void * p_context);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void tau_pwm_common_tmi_isr(timer_event_t event);
void tau_pwm_master_tmi_isr(void);
void tau_pwm_slave_tmi_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* TAU_PWM implementation of timer interface  */
const timer_api_t g_timer_on_tau_pwm =
{
    .open            = R_TAU_PWM_Open,
    .stop            = R_TAU_PWM_Stop,
    .start           = R_TAU_PWM_Start,
    .reset           = R_TAU_PWM_Reset,
    .enable          = R_TAU_PWM_Enable,
    .disable         = R_TAU_PWM_Stop,
    .periodSet       = R_TAU_PWM_PeriodSet,
    .compareMatchSet = R_TAU_PWM_CompareMatchSet,
    .dutyCycleSet    = R_TAU_PWM_DutyCycleSet,
    .infoGet         = R_TAU_PWM_InfoGet,
    .statusGet       = R_TAU_PWM_StatusGet,
    .callbackSet     = R_TAU_PWM_CallbackSet,
    .close           = R_TAU_PWM_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup TAU_PWM
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the timer module and applies configurations. Implements @ref timer_api_t::open.
 *
 * The TAU_PWM implementation of the timer requires a tau_pwm_extended_cfg_t extension parameter.
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL, the source divider/period/duty cycle counts
 *                                        or number of slave channels is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       ISR of master channel must be enabled
 * @retval FSP_ERR_INVALID_MODE           Invalid configuration option provided for selected timer mode
 * @retval FSP_ERR_INVALID_CHANNEL        The master/slave channel selected is not available on this device,
 *                                        slave channel number must be greater than master channel number.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;
    fsp_err_t                 err             = FSP_SUCCESS;

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    err = r_tau_pwm_parameter_checking(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set configuration */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->p_context  = p_cfg->p_context;

    r_tau_pwm_hardware_initialize(p_instance_ctrl, p_cfg);

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    p_instance_ctrl->open = TAU_PWM_OPEN;
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Stops timer. Implements @ref timer_api_t::stop.
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_Stop
 *
 * @retval FSP_SUCCESS                 Timer successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_Stop (timer_ctrl_t * const p_ctrl)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;
#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    R_TAU->TT0 = p_instance_ctrl->channels_mask;

    /* Disable the output */
    R_TAU->TOE0 &= (uint16_t) ~(p_instance_ctrl->slave_channels_mask);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer (pwm mode) or triggers the one-shot pulse output by software (one-shot mode).
 * Implements @ref timer_api_t::start.
 *
 * @note In one-shot mode, this function is supported only after the timer has been placed into the start trigger
 * detection wait state by calling @ref timer_api_t::enable
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_Start
 *
 * @retval FSP_SUCCESS                 Timer successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_NOT_ENABLED         In One-shot mode, timer must be enabled first.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_Start (timer_ctrl_t * const p_ctrl)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;
#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

 #if TAU_PWM_CFG_ONE_SHOT_MODE_ENABLE
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        /* Get the channel status */
        bool channel_in_use = R_TAU->TE0 & (1U << p_instance_ctrl->p_cfg->channel);
        FSP_ERROR_RETURN(channel_in_use, FSP_ERR_NOT_ENABLED);
    }
 #endif
#endif

    uint16_t ts0 = 0;
#if TAU_PWM_CFG_PWM_MODE_ENABLE
    if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        /* Enable the output */
        R_TAU->TOE0 |= (uint16_t) (p_instance_ctrl->slave_channels_mask);

        /* Start timer */
        ts0 = p_instance_ctrl->channels_mask;
    }

 #if TAU_PWM_CFG_ONE_SHOT_MODE_ENABLE
    else
 #endif
#endif
#if TAU_PWM_CFG_ONE_SHOT_MODE_ENABLE
    {
        /* Start trigger the one-shot pulse output by software */
        ts0 = (uint16_t) (p_instance_ctrl->master_channel_mask);
    }
#endif

    R_TAU->TS0 = ts0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to the current period and duty cycle. Implements @ref timer_api_t::reset.
 *
 * @note If the timer is stopped when calling this function, the timer counter is not reset. The counter will be
 * reset one cycle after the timer is next started (or restarted), since it takes one cycle to reload the initial count
 * when starting the timer.
 *
 * @retval FSP_SUCCESS                 Counter value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_Reset (timer_ctrl_t * const p_ctrl)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;
#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get the channel status */
    bool channel_in_use = R_TAU->TE0 & (1U << p_instance_ctrl->p_cfg->channel);
    if (channel_in_use)
    {
        /* Stop timer */
        R_TAU->TT0 = p_instance_ctrl->channels_mask;

        /* Restart timer */
        R_TAU->TS0 = p_instance_ctrl->channels_mask;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables external event inputs that can start the counter and enables the software trigger.
 * After a successful call to this function, the timer is placed into the trigger detection wait state.
 * Implements @ref timer_api_t::enable.
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_Enable
 *
 * @retval FSP_SUCCESS                 External events successfully enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_MODE        The mode is invalid, only called in TIMER_MODE_ONE_SHOT mode.
 * @retval FSP_ERR_UNSUPPORTED         Unsupported when one shot mode support is disabled
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_Enable (timer_ctrl_t * const p_ctrl)
{
#if TAU_PWM_CFG_ONE_SHOT_MODE_ENABLE
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;
 #if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Only called in one-shot mode */
    FSP_ERROR_RETURN(TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode, FSP_ERR_INVALID_MODE);
 #endif

    /* Enable the output */
    R_TAU->TOE0 |= (uint16_t) (p_instance_ctrl->slave_channels_mask);

    /* Start timer and wait for trigger source to start count */
    R_TAU->TS0 = p_instance_ctrl->channels_mask;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_RETURN(FSP_ERR_UNSUPPORTED);
#endif
}

/*******************************************************************************************************************//**
 * Sets period value provided. If the timer is running, the period will be updated after the next counter underflow.
 * If the timer is stopped, this function resets the counter and updates the period.
 * Implements @ref timer_api_t::periodSet.
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    Period counts is out of range.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(period_counts <= (UINT16_MAX + 1), FSP_ERR_INVALID_ARGUMENT);
#endif

    /* Sets the TDR register to the period minus 1 or 2 based on the timer mode */
    uint32_t tdr0 = period_counts - 2U;
#if TAU_PWM_CFG_PWM_MODE_ENABLE
    if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        tdr0 = tdr0 + 1U;
    }
#endif
    R_TAU->TDR0[p_instance_ctrl->p_cfg->channel].TDR0n = (uint16_t) tdr0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Placeholder for unsupported compareMatch function. Implements @ref timer_api_t::compareMatchSet.
 *
 * @retval FSP_ERR_UNSUPPORTED      TAU PWM compare match is not supported.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_CompareMatchSet (timer_ctrl_t * const        p_ctrl,
                                     uint32_t const              compare_match_value,
                                     timer_compare_match_t const match_channel)
{
    /* This function isn't supported. It is defined only to implement a required function of timer_api_t.
     * Mark the input parameter as unused since this function isn't supported. */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(compare_match_value);
    FSP_PARAMETER_NOT_USED(match_channel);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Sets duty cycle on requested pin. Implements @ref timer_api_t::dutyCycleSet.
 *
 * Duty cycle is updated in the timer data register. The updated duty cycle is reflected after the next cycle end
 * (counter underflow).
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_DutyCycleSet
 *
 * @param[in] p_ctrl                   Pointer to instance control block.
 * @param[in] duty_cycle_counts        Duty cycle to set in counts.
 * @param[in] pin                      Use tau_pwm_io_pin_t to select the target slave channel
 *
 * @retval FSP_SUCCESS                 Duty cycle updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL or the pin is not one of tau_pwm_io_pin_t.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    Duty cycle is out of range or larger than period.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Duty cycle counts must be in valid range. */
    if (TIMER_SOURCE_DIV_1 == p_instance_ctrl->p_cfg->source_div)
    {
        FSP_ERROR_RETURN(1 <= duty_cycle_counts, FSP_ERR_INVALID_ARGUMENT);
    }

    FSP_ERROR_RETURN(duty_cycle_counts <= UINT16_MAX, FSP_ERR_INVALID_ARGUMENT);

    /* Duty cycle must be <= period. */
    FSP_ERROR_RETURN(duty_cycle_counts <= p_instance_ctrl->p_cfg->period_counts, FSP_ERR_INVALID_ARGUMENT);

    /* Do not select the pin of master channel. */
    FSP_ASSERT(pin != p_instance_ctrl->p_cfg->channel);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Sets the TDR register for slave channels */
    R_TAU->TDR0[pin].TDR0n = (uint16_t) duty_cycle_counts;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get timer information and store it in provided pointer p_info. Implements @ref timer_api_t::infoGet.
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, frequency written to caller's structure successfully
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_info was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;
    uint8_t specific_divider;

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    timer_cfg_t const * p_cfg = p_instance_ctrl->p_cfg;

    tau_pwm_extended_cfg_t * p_extend = (tau_pwm_extended_cfg_t *) p_cfg->p_extend;

    /* Get and store period */
    p_info->period_counts = R_TAU->TDR0[p_instance_ctrl->p_cfg->channel].TDR0n + 2U;
#if TAU_PWM_CFG_PWM_MODE_ENABLE
    if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        p_info->period_counts = p_info->period_counts - 1U;
    }
#endif

    /* Get and store clock frequency */
    /* figure out which clock and associated divider is driving this channel */
    uint32_t bsp_ck0n_div = BSP_CFG_TAU_CK01 << 8 | BSP_CFG_TAU_CK00;
    specific_divider = (uint8_t) (bsp_ck0n_div >> (p_extend->operation_clock << 2));

    p_info->clock_frequency = SystemCoreClock >> specific_divider;

    /* Get and store clock count direction as down. */
    p_info->count_direction = TIMER_DIRECTION_DOWN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Retrieves the current timer state and master channel counter value and stores them in provided pointer p_status.
 * Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_tau_pwm_example.c R_TAU_PWM_StatusGet
 *
 * @retval FSP_SUCCESS                 Current timer state and counter value retrieved successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;
#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint8_t channel = p_instance_ctrl->p_cfg->channel;

    /* Get counter state. */
    p_status->state = (timer_state_t) ((R_TAU->TE0 >> channel) & 1U);

    /* Get counter value */
    p_status->counter = R_TAU->TCR0[channel];

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref timer_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            p_ctrl or p_callback was NULL.
 * @retval  FSP_ERR_NOT_OPEN             The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_CallbackSet (timer_ctrl_t * const          p_api_ctrl,
                                 void (                      * p_callback)(timer_callback_args_t *),
                                 void * const                  p_context,
                                 timer_callback_args_t * const p_callback_memory)
{
    tau_pwm_instance_ctrl_t * p_ctrl = (tau_pwm_instance_ctrl_t *) p_api_ctrl;

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    FSP_PARAMETER_NOT_USED(p_callback_memory);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops counter, disables output pins, and clears internal driver data. Implements @ref timer_api_t::close.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_PWM_Close (timer_ctrl_t * const p_ctrl)
{
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) p_ctrl;

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_PWM_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    R_TAU->TT0 = p_instance_ctrl->channels_mask;

    /* Disable the output */
    R_TAU->TOE0 &= (uint16_t) ~(p_instance_ctrl->slave_channels_mask);

    /* Disable interrupts. */
    const tau_pwm_extended_cfg_t * p_extend = (tau_pwm_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    r_tau_pwm_disable_irq(p_instance_ctrl->p_cfg->cycle_end_irq);
#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;
#endif

#if (1 == TAU_PWM_CFG_MULTI_SLAVE_ENABLE)

    /* Save the active slave mask; shift right because channel 0 cant be a slave */
    uint8_t slave_channels_mask = (p_instance_ctrl->slave_channels_mask >> 1);

    uint8_t index = 0;
    do
    {
        if (slave_channels_mask & 0x01)
        {
            r_tau_pwm_disable_irq(p_extend->p_slave_channel_cfgs[index]->cycle_end_irq);
            index++;
        }

        slave_channels_mask >>= 1;
    } while (slave_channels_mask > 0);

    p_instance_ctrl->slave_channels_mask = 0;
#else

    /* Single slave mode always uses index 0 */
    if ((0 != p_instance_ctrl->slave_channels_mask) && (NULL != p_extend->p_slave_channel_cfgs[0]))
    {
        r_tau_pwm_disable_irq(p_extend->p_slave_channel_cfgs[0]->cycle_end_irq);
        p_instance_ctrl->slave_channels_mask = 0;
    }
#endif

    return FSP_SUCCESS;
}

/** @} (end addtogroup TAU_PWM) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

#if TAU_PWM_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking.
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 * @param[in]  p_cfg                   Pointer to timer configuration.
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL, the source divider/period/duty cycle counts
 *                                        or number of slave channels is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       ISR of master channel must be enabled
 * @retval FSP_ERR_INVALID_MODE           Simultaneous Channel Operation Function of TAU only support
 *                                        TIMER_MODE_ONE_SHOT and TIMER_MODE_PWM and event trigger source only
 *                                        supported in TIMER_MODE_ONE_SHOT mode
 * @retval FSP_ERR_INVALID_CHANNEL        The master/slave channel selected is not available on this device,
 *                                        slave channel number must be greater than master channel number.
 **********************************************************************************************************************/
static fsp_err_t r_tau_pwm_parameter_checking (tau_pwm_instance_ctrl_t * const p_instance_ctrl,
                                               timer_cfg_t const * const       p_cfg)
{
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TIMER_MODE_PWM == p_cfg->mode || TIMER_MODE_ONE_SHOT == p_cfg->mode, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(TAU_PWM_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Master channel must available on the device and must be even */
    FSP_ERROR_RETURN(((1 << p_cfg->channel) & BSP_FEATURE_TAU_VALID_CHANNEL_MASK) && !(p_cfg->channel & 0x01),
                     FSP_ERR_INVALID_CHANNEL);

    /* Master channel's interrupt must be enabled */
    FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);

    tau_pwm_extended_cfg_t * p_extend = (tau_pwm_extended_cfg_t *) p_cfg->p_extend;
    uint32_t                 slave_channels_configured = 0U;

    if (TAU_PWM_SOURCE_ELC_EVENT == p_extend->trigger_source)
    {
        /* ELC event trigger source only supported in TIMER_MODE_ONE_SHOT mode. */
        FSP_ERROR_RETURN(TIMER_MODE_ONE_SHOT == p_cfg->mode, FSP_ERR_INVALID_MODE);

        /* Master channel must be 0 when ELC is used as the trigger source. */
        FSP_ERROR_RETURN(0 == p_cfg->channel, FSP_ERR_INVALID_CHANNEL);

        /* PCLK (undivided) must be selected when ELC is used as the trigger source. */
        FSP_ASSERT(TIMER_SOURCE_DIV_1 == p_cfg->source_div);
    }

 #if (0 == TAU_PWM_CFG_MULTI_SLAVE_ENABLE)
    const uint8_t index = 0;
 #else
    for (uint8_t index = 0; index < TAU_PWM_MAX_NUM_SLAVE_CHANNELS; index++)
 #endif
    {
        if (NULL != p_extend->p_slave_channel_cfgs[index])
        {
            uint8_t slaveChannel = p_extend->p_slave_channel_cfgs[index]->channel;
            slave_channels_configured++;

            /* Slave channel must be valid in range 1 to 7 and greater than master channel number */

            FSP_ERROR_RETURN((slaveChannel > TAU_PWM_SLAVE_CHANNEL_UNUSED) &&
                             (slaveChannel <= TAU_PWM_MAX_CHANNEL_NUM) && /*This is TAU_PWM_MAX_CHANNEL_NUM
                                                                           * because even with a single slave it could be any slave
                                                                           * from 1-7 */
                             (p_extend->p_slave_channel_cfgs[index]->channel > p_cfg->channel),
                             FSP_ERR_INVALID_CHANNEL);

            /* Pulse width/duty cycle counts of slave channels must be in valid range */
            if (TIMER_SOURCE_DIV_1 == p_cfg->source_div)
            {
                FSP_ASSERT(1 <= p_extend->p_slave_channel_cfgs[index]->duty_cycle_counts);
            }
        }
    }

    uint32_t master_counter_max = TAU_PWM_PRV_PERIOD_MAX;
    uint32_t master_counter_min = TAU_PWM_PRV_PERIOD_MIN;

    if (TIMER_SOURCE_DIV_1 == p_cfg->source_div)
    {
        master_counter_min++;
    }

 #if TAU_PWM_CFG_PWM_MODE_ENABLE

    /* decrement counters if mode is PWM */
    master_counter_min = master_counter_min - (TIMER_MODE_PWM == p_cfg->mode);
    master_counter_max = master_counter_max - (TIMER_MODE_PWM == p_cfg->mode);
 #endif

    /* Pulse period/delay time of master channel must be in valid range */
    FSP_ASSERT(master_counter_min <= p_cfg->period_counts);
    FSP_ASSERT(p_cfg->period_counts <= master_counter_max);

    /* At least one slave channel must be configured */
    FSP_ASSERT(slave_channels_configured > 0U);

 #if TAU_PWM_CFG_ONE_SHOT_MODE_ENABLE

    /* Only one slave channel must be configured in TIMER_MODE_ONE_SHOT mode */
    if (TIMER_MODE_ONE_SHOT == p_cfg->mode)
    {
        FSP_ASSERT(1U == slave_channels_configured);
    }
 #endif

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Performs hardware initialization of the TAU_PWM.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void r_tau_pwm_hardware_initialize (tau_pwm_instance_ctrl_t * const p_instance_ctrl,
                                           timer_cfg_t const * const       p_cfg)
{
    /* Set TAU divisors based on BSP settings */
    R_TAU->TPS0 = (uint16_t) ((TAU_PRV_TPS0_PRS3_SETTING << R_TAU_TPS0_PRS3_Pos) |
                              (TAU_PRV_TPS0_PRS2_SETTING << R_TAU_TPS0_PRS2_Pos) |
                              (BSP_CFG_TAU_CK01 << R_TAU_TPS0_PRS1_Pos) | BSP_CFG_TAU_CK00);

    /* Setting for master channel */
    r_tau_pwm_master_channel_initialize(p_instance_ctrl, p_cfg);

    /* Setting for slave channels */
    r_tau_pwm_slave_channels_initialize(p_instance_ctrl, p_cfg);
}

/*******************************************************************************************************************//**
 * Performs hardware initialization of the master channel.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void r_tau_pwm_master_channel_initialize (tau_pwm_instance_ctrl_t * p_instance_ctrl,
                                                 timer_cfg_t const * const p_cfg)
{
    /* Save pointer to extended configuration structure. */
    tau_pwm_extended_cfg_t * p_extend = (tau_pwm_extended_cfg_t *) p_cfg->p_extend;
    p_instance_ctrl->master_channel_mask = (uint8_t) (1U << (p_cfg->channel));

    /* Power on TAU to start module. */
    R_BSP_MODULE_START(FSP_IP_TAU, p_cfg->channel);

    /* Calculate TMR0 register for master channel */
    uint16_t tmr0 = 0;
#if TAU_PWM_CFG_ONE_SHOT_MODE_ENABLE
    if (TIMER_MODE_ONE_SHOT == p_cfg->mode)
    {
        if (0U == p_cfg->channel)
        {
            /* Sets the trigger source in case master channel is 0 */
            uint8_t tis1 = R_PORGA->TIS1;
            tis1         &= (uint8_t) ~(p_instance_ctrl->master_channel_mask);
            tis1         |= (uint8_t) p_extend->trigger_source;
            R_PORGA->TIS1 = tis1;
        }

        /* Clear the noise filter */
        uint8_t tnfen = R_PORGA->TNFEN & (uint8_t) ~(p_instance_ctrl->master_channel_mask);
        if ((TAU_PWM_SOURCE_PIN_INPUT == p_extend->trigger_source))
        {
            /* Enables the noise filter for input pin */
            tnfen |= p_instance_ctrl->master_channel_mask;
        }

        R_PORGA->TNFEN = tnfen;

        /* Sets the operation mode to one count */
        tmr0 = TAU_PWM_PRV_TMR0_MD_ONE_COUNT << R_TAU_TMR0_MD_Pos;

        /* Sets the detection edge of input */
        tmr0 |= (uint32_t) (p_extend->detect_edge << R_TAU_TMR0_CIS_Pos);

        /* Sets the start trigger or capture trigger by valid edge of TI0n pin input*/
        tmr0 |= TAU_PWM_PRV_TMR0_STS_TI0n_VALID_EDGE << R_TAU_TMR0_STS_Pos;
    }

 #if TAU_PWM_CFG_PWM_MODE_ENABLE
    else
 #endif
#endif
#if TAU_PWM_CFG_PWM_MODE_ENABLE
    {
        /* Sets the operation mode to interval timer */
        tmr0 = TAU_PWM_PRV_TMR0_MD_INTERVAL_TIMER << R_TAU_TMR0_MD_Pos;

        /* Generates TAU0_TMI0n when counting is started */
        tmr0 |= R_TAU_TMR0_OPIRQ_Msk;
    }
#endif

    /* Sets the channel as master channel */
    tmr0 |= R_TAU_TMR0_MASTER_SPLIT_Msk;

    /* Sets the operation clock */
    tmr0 |= (uint16_t) (p_extend->operation_clock << R_TAU_TMR0_CKS_Pos);

    /* Set the TMR0 register to determines operation mode of master channel */
    R_TAU->TMR0[p_cfg->channel] = tmr0;

    /* Sets the TDR register to specify the counter data of master channel */
    uint32_t tdr0 = p_cfg->period_counts - 2U;
#if TAU_PWM_CFG_PWM_MODE_ENABLE
    tdr0 += (TIMER_MODE_PWM == p_cfg->mode);
#endif
    R_TAU->TDR0[p_cfg->channel].TDR0n = (uint16_t) tdr0;

    /* Sets output setting to default setting for master channel */
    if (0 < p_cfg->channel)
    {
        R_TAU->TOM0 &= (uint16_t) ~(p_instance_ctrl->master_channel_mask);
        R_TAU->TOL0 &= (uint16_t) ~(p_instance_ctrl->master_channel_mask);
    }

    R_TAU->TO0  &= (uint16_t) ~(p_instance_ctrl->master_channel_mask);
    R_TAU->TOE0 &= (uint16_t) ~(p_instance_ctrl->master_channel_mask);

    /* Enables interrupt */
    r_tau_pwm_enable_irq(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);
}

/*******************************************************************************************************************//**
 * Performs hardware initialization of the slave channels.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 **********************************************************************************************************************/
static void r_tau_pwm_slave_channels_initialize (tau_pwm_instance_ctrl_t * p_instance_ctrl,
                                                 timer_cfg_t const * const p_cfg)
{
    /* Save pointer to extended configuration structure. */
    tau_pwm_extended_cfg_t * p_extend = (tau_pwm_extended_cfg_t *) p_cfg->p_extend;

    /* Calculate TMR0 register for slave channels */
    uint16_t tmr0;

#if (0 == TAU_PWM_CFG_MULTI_SLAVE_ENABLE)
    const uint8_t index = 0;
#else
    for (uint8_t index = 0; index < TAU_PWM_MAX_NUM_SLAVE_CHANNELS; index++)
#endif
    {
        if (NULL != p_extend->p_slave_channel_cfgs[index])
        {
            const tau_pwm_channel_cfg_t * slave_channel_cfg = p_extend->p_slave_channel_cfgs[index];
            uint8_t slave_channel      = slave_channel_cfg->channel;
            uint8_t slave_channel_mask = (uint8_t) (1U << slave_channel);

            /* Sets the operation mode */
            tmr0 = TAU_PWM_PRV_TMR0_MD_ONE_COUNT << R_TAU_TMR0_MD_Pos;
#if TAU_PWM_CFG_PWM_MODE_ENABLE
            if (TIMER_MODE_PWM == p_cfg->mode)
            {
                /* Trigger input is valid */
                tmr0 |= R_TAU_TMR0_OPIRQ_Msk;
            }
#endif

            /* Sets the start trigger or capture trigger */
            tmr0 |= TAU_PWM_PRV_TMR0_STS_TAU0_TMI0n << R_TAU_TMR0_STS_Pos;

            /* Sets the operation clock */
            tmr0 |= (uint16_t) (p_extend->operation_clock << R_TAU_TMR0_CKS_Pos);

            /* Set the TMR0 register to determines operation mode of slave channel */
            R_TAU->TMR0[slave_channel] = tmr0;

            /* Sets the TDR register to specify the counter data of slave channel */
            R_TAU->TDR0[slave_channel].TDR0n =
                slave_channel_cfg->duty_cycle_counts;

            /* Sets output setting for slave channel */
            R_TAU->TOM0 |= (uint16_t) (slave_channel_mask);

            uint16_t tol0 = R_TAU->TOL0;
            tol0       &= (uint16_t) ~(slave_channel_mask);
            tol0       |= (uint16_t) (slave_channel_cfg->output_polarity << slave_channel);
            R_TAU->TOL0 = tol0;

            uint16_t to0 = R_TAU->TO0;
            to0       &= (uint16_t) ~(slave_channel_mask);
            to0       |= (uint16_t) (slave_channel_cfg->output_level << slave_channel);
            R_TAU->TO0 = to0;

            p_instance_ctrl->slave_channels_mask |= slave_channel_mask;

            /* Enables interrupt */
            r_tau_pwm_enable_irq(slave_channel_cfg->cycle_end_irq, slave_channel_cfg->cycle_end_ipl, p_instance_ctrl);
        }
    }

    p_instance_ctrl->channels_mask = p_instance_ctrl->master_channel_mask | p_instance_ctrl->slave_channels_mask;
}

/*******************************************************************************************************************//**
 * Disables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 **********************************************************************************************************************/
static void r_tau_pwm_disable_irq (IRQn_Type irq)
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
static void r_tau_pwm_enable_irq (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, priority, p_context);
    }
}

/*******************************************************************************************************************//**
 * Common ISR.
 *
 * Clears interrupt and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void tau_pwm_common_tmi_isr (timer_event_t event)
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    tau_pwm_instance_ctrl_t * p_instance_ctrl = (tau_pwm_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* If a callback is provided, then call it with the event and context. */
    if (NULL != p_instance_ctrl->p_callback)
    {
        timer_callback_args_t args = {0};
        args.event     = event;
        args.p_context = p_instance_ctrl->p_context;

        /* Call the callback. */
        p_instance_ctrl->p_callback(&args);
    }
}

/*******************************************************************************************************************//**
 * Master channel ISR.
 **********************************************************************************************************************/
void tau_pwm_master_tmi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Call the common isr function */
    tau_pwm_common_tmi_isr(TIMER_EVENT_MASTER_CYCLE_END);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Slave channel ISR.
 **********************************************************************************************************************/
void tau_pwm_slave_tmi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Call the common isr function */
    tau_pwm_common_tmi_isr(TIMER_EVENT_SLAVE_CYCLE_END);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
