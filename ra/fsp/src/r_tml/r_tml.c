/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_tml.h"
#include "r_tml_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "TML" in ASCII, used to determine if channel is open. */
#define TML_OPEN                                (0x00544D4CULL)

/* ITLCMP0n bit field definitions. */
#define TML_PRV_ITLCMP0_UPPER_16_BIT_POS        (16)
#define TML_PRV_ITLCMP0_UPPER_16_BIT_CLEARED    (0x0000FFFFU)

#define CHANNEL0_MASK                           (1U << 0)
#define CHANNEL2_MASK                           (1U << 2)
#define VALID_16_BIT_COUNTER_CHANNEL_MASK       (CHANNEL0_MASK | CHANNEL2_MASK)
#define VALID_16_BIT_CAPTURE_CHANNEL_MASK       (CHANNEL0_MASK)
#define VALID_32_BIT_COUNTER_CHANNEL_MASK       (CHANNEL0_MASK)

/* Counter clock selection (ISEL) */
#if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_TML_FITL0_SOURCE
 #define TML_PRV_ITLCSEL0_ISEL_VALUE            (TML_CLOCK_HOCO)
#elif BSP_CLOCKS_SOURCE_CLOCK_MOCO == BSP_CFG_TML_FITL0_SOURCE
 #define TML_PRV_ITLCSEL0_ISEL_VALUE            (TML_CLOCK_MOCO)
#elif BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_TML_FITL0_SOURCE
 #define TML_PRV_ITLCSEL0_ISEL_VALUE            (TML_CLOCK_MOSC)
#elif BSP_CFG_FSXP_SOURCE == BSP_CFG_TML_FITL0_SOURCE
 #define TML_PRV_ITLCSEL0_ISEL_VALUE            (TML_CLOCK_LOCO_SOSC)
#else
 #define TML_PRV_ITLCSEL0_ISEL_VALUE            (TML_CLOCK_ELC_EVENT)
#endif

/* Capture clock selection (CSEL) */
#if BSP_CLOCKS_SOURCE_CLOCK_HOCO == BSP_CFG_TML_FITL1_SOURCE
 #define TML_PRV_ITLCSEL0_CSEL_VALUE            (TML_CLOCK_HOCO)
#elif BSP_CLOCKS_SOURCE_CLOCK_MOCO == BSP_CFG_TML_FITL1_SOURCE
 #define TML_PRV_ITLCSEL0_CSEL_VALUE            (TML_CLOCK_MOCO)
#elif BSP_CLOCKS_SOURCE_CLOCK_MAIN_OSC == BSP_CFG_TML_FITL1_SOURCE
 #define TML_PRV_ITLCSEL0_CSEL_VALUE            (TML_CLOCK_MOSC)
#elif BSP_CFG_FSXP_SOURCE == BSP_CFG_TML_FITL1_SOURCE
 #define TML_PRV_ITLCSEL0_CSEL_VALUE            (TML_CLOCK_LOCO_SOSC)
#else
 #define TML_PRV_ITLCSEL0_CSEL_VALUE            (TML_CLOCK_ELC_EVENT)
#endif

#if TML_CFG_CRITICAL_SECTION_ENABLE
 #define TML_PRV_CRITICAL_SECTION_ENTER()    {FSP_CRITICAL_SECTION_DEFINE; FSP_CRITICAL_SECTION_ENTER
 #define TML_PRV_CRITICAL_SECTION_EXIT()     FSP_CRITICAL_SECTION_EXIT;}
#else
 #define TML_PRV_CRITICAL_SECTION_ENTER()
 #define TML_PRV_CRITICAL_SECTION_EXIT()
#endif

#if TML_CFG_SINGLE_CHANNEL_ENABLE
 #define TML_PRV_CHANNEL            (0U)
 #define TML_PRV_CHANNEL_MASK       (0x1U)
 #define TML_PRV_ITLFDIV_ADDRESS    (&(R_TML->ITLFDIV00))
 #define TML_PRV_ITLFDIV_POS        (R_TML_ITLFDIV00_FDIV0_Pos)
 #define TML_PRV_ITLFDIV_MASK       (uint8_t) (R_TML_ITLFDIV00_FDIV0_Msk)
#else
 #define TML_PRV_CHANNEL            (p_instance_ctrl->p_cfg->channel)
 #define TML_PRV_CHANNEL_MASK       (p_instance_ctrl->channel_mask)
 #define TML_PRV_ITLFDIV_ADDRESS    (&(R_TML->ITLFDIV00) + TML_PRV_CHANNEL / 2)
 #define TML_PRV_ITLFDIV_POS        ((TML_PRV_CHANNEL & 0x01) * R_TML_ITLFDIV00_FDIV1_Pos)
 #define TML_PRV_ITLFDIV_MASK       (uint8_t) (R_TML_ITLFDIV00_FDIV0_Msk << TML_PRV_ITLFDIV_POS)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* TML channels. */
typedef enum e_tml_channel
{
    TML_CHANNEL_0 = 0,                 // channel 0
    TML_CHANNEL_1 = 1,                 // channel 1
    TML_CHANNEL_2 = 2,                 // channel 2
    TML_CHANNEL_3 = 3,                 // channel 3
} tml_channel_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static fsp_err_t r_tml_hardware_initialize(tml_instance_ctrl_t * const p_instance_ctrl,
                                           timer_cfg_t const * const   p_cfg);

static void r_tml_period_counts_set(tml_instance_ctrl_t * const p_instance_ctrl, uint32_t const period_counts);

static uint32_t r_tml_period_counts_get(tml_instance_ctrl_t * const p_instance_ctrl);

#if TML_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_tml_open_param_checking(tml_instance_ctrl_t * const p_instance_ctrl,
                                           timer_cfg_t const * const   p_cfg);

#endif

#if TML_CFG_INTERRUPT_SUPPORT_ENABLE
static fsp_err_t r_tml_enable_helper(timer_ctrl_t * const p_ctrl, bool enable);

#endif

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
#if TML_CFG_INTERRUPT_SUPPORT_ENABLE
void tml_itl_or_isr(void);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
#if TML_CFG_INTERRUPT_SUPPORT_ENABLE && (!TML_CFG_SINGLE_CHANNEL_ENABLE)

/** Stored context for isr handler. */
static tml_instance_ctrl_t * gp_tml_ctrls[BSP_FEATURE_TML_NUM_CHANNELS] = {NULL};
#endif

#if !TML_CFG_SINGLE_CHANNEL_ENABLE

/** g_modeset is to track whether the mode has been set by an active channel. Incremented when a channel is opened,
 * decremented when a channel is closed. This is done because the mode ITLCTL0_b.MD register doesn't have an
 * "inactive" selection and we need to make sure the mode of a channel matches the modes of currently active
 * channels. We can only set the mode on the first channel open.*/
static uint8_t g_modeset = 0;
#endif

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* TML implementation of timer interface  */
const timer_api_t g_timer_on_tml =
{
    .open            = R_TML_Open,
    .stop            = R_TML_Stop,
    .start           = R_TML_Start,
    .reset           = R_TML_Reset,
    .enable          = R_TML_Enable,
    .disable         = R_TML_Disable,
    .periodSet       = R_TML_PeriodSet,
    .dutyCycleSet    = R_TML_DutyCycleSet,
    .compareMatchSet = R_TML_CompareMatchSet,
    .infoGet         = R_TML_InfoGet,
    .statusGet       = R_TML_StatusGet,
    .callbackSet     = R_TML_CallbackSet,
    .close           = R_TML_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup TML
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the timer module and applies configurations. Implements @ref timer_api_t::open.
 *
 * TML hardware does not support one-shot functionality natively. If one shot mode is desired, the user code should
 * stop the timer after the timer expires the first time in an ISR after the requested period has elapsed.
 *
 * The TML implementation of the general timer can accept a tml_extended_cfg_t extension parameter.
 *
 * Example:
 * @snippet r_tml_example.c R_TML_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL or the source divider is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       timer_cfg_t::p_callback is not NULL, but ISR is not enabled.
 *                                        ISR must be enabled to use one-shot mode or callback.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 * @retval FSP_ERR_INVALID_CHANNEL        Selected channel is invalid
 * @retval FSP_ERR_INVALID_MODE           The mode requested in the p_cfg parameter is incorrect.
 *                                        It must be the same for all instances.
 * @retval FSP_ERR_IN_USE                 Channel is running
 **********************************************************************************************************************/
fsp_err_t R_TML_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;

#if TML_CFG_PARAM_CHECKING_ENABLE
    err = r_tml_open_param_checking(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Initialize control structure.  */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->p_context  = p_cfg->p_context;

    err = r_tml_hardware_initialize(p_instance_ctrl, p_cfg);
#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_instance_ctrl->open = TML_OPEN;
#endif

#if TML_CFG_INTERRUPT_SUPPORT_ENABLE && (!TML_CFG_SINGLE_CHANNEL_ENABLE)
    gp_tml_ctrls[TML_PRV_CHANNEL] = p_instance_ctrl;
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Stops the counter and disable the capture. Implements @ref timer_api_t::stop.
 *
 * Example:
 * @snippet r_tml_example.c R_TML_Stop
 *
 * @retval FSP_SUCCESS                    Timer successfully stopped.
 * @retval FSP_ERR_ASSERTION              p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN               The instance is not opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TML_Stop (timer_ctrl_t * const p_ctrl)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TML_PRV_CHANNEL_MASK & BSP_FEATURE_TML_VALID_CHANNEL_MASK, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

#if TML_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Critical section required because ITLCTL0 register is shared with other instances. */
    TML_PRV_CRITICAL_SECTION_ENTER();

    uint8_t itlctl0 = R_TML->ITLCTL0;

    /* Stop timer */
    itlctl0 &= (uint8_t) ~(TML_PRV_CHANNEL_MASK);

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE

    /* Save pointer to extended configuration structure. */
    tml_extended_cfg_t * p_tml_cfg = (tml_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (TIMER_MODE_16_BIT_CAPTURE == p_instance_ctrl->p_cfg->mode)
    {
        if (TML_CAPTURE_TRIGGER_ITLCMP01 == p_tml_cfg->capture_trigger)
        {
            /* Stop timer channel 2 + 3 */
            itlctl0 &= (uint8_t) ~(R_TML_ITLCTL0_EN2_Msk);
        }
    }
#endif

    /* Write to registers */
    R_TML->ITLCTL0 = itlctl0;

    TML_PRV_CRITICAL_SECTION_EXIT();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts the counter and enable the capture. Implements @ref timer_api_t::start.
 *
 * Example:
 * @snippet r_tml_example.c R_TML_Start
 *
 * @retval FSP_SUCCESS                    Timer successfully started.
 * @retval FSP_ERR_ASSERTION              p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN               The instance is not opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TML_Start (timer_ctrl_t * const p_ctrl)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TML_PRV_CHANNEL_MASK & BSP_FEATURE_TML_VALID_CHANNEL_MASK, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

#if TML_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Critical section required because ITLCTL0 register is shared with other instances. */
    TML_PRV_CRITICAL_SECTION_ENTER();

    uint8_t itlctl0 = R_TML->ITLCTL0;
    uint8_t itls0   = R_TML->ITLS0;
    uint8_t itlmkf0 = R_TML->ITLMKF0;

    /* Clear the ITF0i interrupt status flags for channel used. */
    itls0 &= (uint8_t) ~(TML_PRV_CHANNEL_MASK);

    /* Start timer */
    itlctl0 |= TML_PRV_CHANNEL_MASK;

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE

    /* Save pointer to extended configuration structure. */
    tml_extended_cfg_t * p_tml_cfg = (tml_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if (TIMER_MODE_16_BIT_CAPTURE == p_instance_ctrl->p_cfg->mode)
    {
        /* Clear the ITF0C interrupt status flags. */
        itls0 &= (uint8_t) ~(R_TML_ITLS0_ITF0C_Msk);

        if (TML_CAPTURE_TRIGGER_ITLCMP01 == p_tml_cfg->capture_trigger)
        {
            /* Enable the MKF02 masks of the ITF02 status flags. */
            itlmkf0 |= R_TML_ITLMKF0_MKF02_Msk;

            /* Clear the ITF02 interrupt status flags. */
            itls0 &= (uint8_t) ~(R_TML_ITLS0_ITF02_Msk);

            /* Start timer channel 2 + 3 */
            itlctl0 |= R_TML_ITLCTL0_EN2_Msk;
        }
    }
#endif

    /* Write to registers */
    R_TML->ITLMKF0 = itlmkf0;
    R_TML->ITLS0   = itls0;
    R_TML->ITLCTL0 = itlctl0;

    TML_PRV_CRITICAL_SECTION_EXIT();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to 0. Implements @ref timer_api_t::reset.
 *
 * @retval FSP_SUCCESS                    Counter value written successfully.
 * @retval FSP_ERR_ASSERTION              p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN               The instance is not opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TML_Reset (timer_ctrl_t * const p_ctrl)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TML_PRV_CHANNEL_MASK & BSP_FEATURE_TML_VALID_CHANNEL_MASK, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

#if TML_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Critical section required because ITLCTL0 register is shared with other instances. */
    TML_PRV_CRITICAL_SECTION_ENTER();

    uint8_t channel_in_use = R_TML->ITLCTL0 & TML_PRV_CHANNEL_MASK;

    /* Modifying ITLCTL0:ENi from 1 to 0 clears the counter without synchronization with the count clock */
    R_TML->ITLCTL0 &= ~(channel_in_use);

    /* Restart the timer */
    R_TML->ITLCTL0 |= channel_in_use;

    TML_PRV_CRITICAL_SECTION_EXIT();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable the interrupt generation from the selected channel @ref timer_api_t::enable.
 *
 * Example:
 * @snippet r_tml_example.c R_TML_Enable
 *
 * @retval FSP_SUCCESS                    External events successfully enabled.
 * @retval FSP_ERR_ASSERTION              p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN               The instance is not opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TML_Enable (timer_ctrl_t * const p_ctrl)
{
#if TML_CFG_INTERRUPT_SUPPORT_ENABLE

    return r_tml_enable_helper(p_ctrl, true);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Disable the interrupt generation for this timer. Implements @ref timer_api_t::disable.
 *
 * @note The timer could be stop after R_TML_Disable().
 *
 * Example:
 * @snippet r_tml_example.c R_TML_Disable
 *
 * @retval FSP_SUCCESS                    External events successfully disabled.
 * @retval FSP_ERR_ASSERTION              p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN               The instance is not opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TML_Disable (timer_ctrl_t * const p_ctrl)
{
#if TML_CFG_INTERRUPT_SUPPORT_ENABLE

    return r_tml_enable_helper(p_ctrl, false);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Sets period value provided. Only set this value when all timers are stop.
 * Implements @ref timer_api_t::periodSet.
 *
 * Example:
 * @snippet r_tml_example.c R_TML_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_IN_USE              Channel is running
 **********************************************************************************************************************/
fsp_err_t R_TML_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    uint8_t channel_status = R_TML->ITLCTL0 & TML_PRV_CHANNEL_MASK;
    FSP_ERROR_RETURN(0U == channel_status, FSP_ERR_IN_USE);
#endif

    /* Specify a period value. */
    r_tml_period_counts_set(p_instance_ctrl, (period_counts - 1));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref timer_api_t::dutyCycleSet is not supported on the TML.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_TML_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
    /* Prevent warnings */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(duty_cycle_counts);
    FSP_PARAMETER_NOT_USED(pin);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * @ref timer_api_t::compareMatchSet is not supported on the TML.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_TML_CompareMatchSet (timer_ctrl_t * const        p_ctrl,
                                 uint32_t const              compare_match_value,
                                 timer_compare_match_t const match_channel)
{
    /* Prevent warnings */
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(compare_match_value);
    FSP_PARAMETER_NOT_USED(match_channel);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Get timer configuration information and store it in provided pointer p_info. Implements @ref timer_api_t::infoGet.
 *
 * Example:
 * @snippet r_tml_example.c R_TML_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, frequency, and ELC event written to caller's
 *                                     structure successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_info was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TML_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get and store period */
    p_info->period_counts = r_tml_period_counts_get(p_instance_ctrl) + 1;

    /* Get and store counter clock frequency */
#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
    if (R_TML->ITLCC0_b.CAPEN &&
        (TIMER_MODE_16_BIT_COUNTER == p_instance_ctrl->p_cfg->mode) &&
        (BSP_CLOCKS_CLOCK_DISABLED != BSP_CFG_TML_FITL1_SOURCE))
    {
        p_info->clock_frequency = R_BSP_SourceClockHzGet((fsp_priv_source_clock_t) BSP_CFG_TML_FITL1_SOURCE);
    }
    else
#endif
    {
        if (BSP_CLOCKS_CLOCK_DISABLED != BSP_CFG_TML_FITL0_SOURCE)
        {
            uint32_t clock_frequency = R_BSP_SourceClockHzGet((fsp_priv_source_clock_t) BSP_CFG_TML_FITL0_SOURCE);
            p_info->clock_frequency = clock_frequency >> p_instance_ctrl->p_cfg->source_div;
        }
    }

    /* Get and store clock count direction as up. */
    p_info->count_direction = TIMER_DIRECTION_UP;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current timer status and store it in provided pointer p_status. Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_tml_example.c R_TML_StatusGet
 *
 * @retval FSP_SUCCESS                    Current timer state and counter value set successfully.
 * @retval FSP_ERR_ASSERTION              p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN               The instance is not opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TML_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TML_PRV_CHANNEL_MASK & BSP_FEATURE_TML_VALID_CHANNEL_MASK, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

#if TML_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Store 0 to current counter since cannot read the counter value. */
    p_status->counter = 0;

    /* Get counter state. */
    p_status->state = (timer_state_t) ((R_TML->ITLCTL0 & TML_PRV_CHANNEL_MASK) > 0);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref timer_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_TML_CallbackSet (timer_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(timer_callback_args_t *),
                             void * const                  p_context,
                             timer_callback_args_t * const p_callback_memory)
{
    FSP_PARAMETER_NOT_USED(p_callback_memory);

#if TML_CFG_INTERRUPT_SUPPORT_ENABLE
    tml_instance_ctrl_t * p_ctrl = (tml_instance_ctrl_t *) p_api_ctrl;

 #if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(TML_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);
    FSP_PARAMETER_NOT_USED(p_context);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Stops counter, disables output pins, and clears internal driver data. Implements @ref timer_api_t::close.
 *
 * @retval FSP_SUCCESS                    Successful close.
 * @retval FSP_ERR_ASSERTION              p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN               The instance is not opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 * @retval FSP_ERR_IN_USE                 Channel is running
 **********************************************************************************************************************/
fsp_err_t R_TML_Close (timer_ctrl_t * const p_ctrl)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;

#if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TML_PRV_CHANNEL_MASK & BSP_FEATURE_TML_VALID_CHANNEL_MASK, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

#if TML_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Critical section required because ITLMKF0, ITLS0, ITLCTL0, ITLFDIV00, ITLFDIV01 registers are shared
     * with other instances. */
    TML_PRV_CRITICAL_SECTION_ENTER();

#if TML_CFG_INTERRUPT_SUPPORT_ENABLE

    /* Disable interrupts. */
    if (0 <= p_instance_ctrl->p_cfg->cycle_end_irq)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->cycle_end_irq);
    }
#endif

    uint8_t itlmkf0 = R_TML->ITLMKF0;
    uint8_t itls0   = R_TML->ITLS0;
    uint8_t itlctl0 = R_TML->ITLCTL0;

    /* Enable the interrupt generation from the selected channel by clearing the mask bits . */
    itlmkf0 &= (uint8_t) ~(TML_PRV_CHANNEL_MASK);

    /* Clear the ITF0i interrupt status flags. */
    itls0 &= (uint8_t) ~(TML_PRV_CHANNEL_MASK);

    /* Stop counter channel. */
    itlctl0 &= (uint8_t) ~(TML_PRV_CHANNEL_MASK);

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
    if (TIMER_MODE_16_BIT_CAPTURE == p_instance_ctrl->p_cfg->mode)
    {
        /* Disable the MKF0C masks of the ITF0C status flags. */
        itlmkf0 &= (uint8_t) ~(R_TML_ITLMKF0_MKF0C_Msk);

        /* Clear the ITF0C interrupt status flags. */
        itls0 &= (uint8_t) ~(R_TML_ITLS0_ITF0C_Msk);

        /* Save pointer to extended configuration structure. */
        tml_extended_cfg_t * p_tml_cfg = (tml_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

        if (TML_CAPTURE_TRIGGER_ITLCMP01 == p_tml_cfg->capture_trigger)
        {
            /* Disable the MKF02 masks of the ITF02 status flags. */
            itlmkf0 &= (uint8_t) ~(R_TML_ITLMKF0_MKF02_Msk);

            /* Stop channels 2 + 3. */
            itlctl0 &= (uint8_t) ~(R_TML_ITLCTL0_EN2_Msk);
        }
    }
#endif

    /* Write to registers. */
    R_TML->ITLMKF0 = itlmkf0;
    R_TML->ITLS0   = itls0;
    R_TML->ITLCTL0 = itlctl0;

    /* Clear the frequency division ratio for the count source. */
    *(TML_PRV_ITLFDIV_ADDRESS) &= (uint8_t) ~(TML_PRV_ITLFDIV_MASK);

    TML_PRV_CRITICAL_SECTION_EXIT();

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
    if (TIMER_MODE_16_BIT_CAPTURE == p_instance_ctrl->p_cfg->mode)
    {
        /* Only set the ITLCC0.CAPEN and ITLCSEL0.CSEL when all timer channels are stopped. */
        FSP_ERROR_RETURN(0U == (BSP_FEATURE_TML_VALID_CHANNEL_MASK & R_TML->ITLCTL0), FSP_ERR_IN_USE);

        /* Disable capturing. */
        R_TML->ITLCC0 &= (uint8_t) ~(R_TML_ITLCC0_CAPEN_Msk);

        /* Clear the capture clock setting. */
        R_TML->ITLCSEL0 &= (uint8_t) ~(R_TML_ITLCSEL0_CSEL_Msk);
    }
#endif
#if !TML_CFG_SINGLE_CHANNEL_ENABLE
 #if TML_CFG_INTERRUPT_SUPPORT_ENABLE

    /* Clear instance. */
    gp_tml_ctrls[TML_PRV_CHANNEL] = NULL;
 #endif
    if (0U < g_modeset)
    {
        g_modeset--;
    }
#endif

#if TML_CFG_PARAM_CHECKING_ENABLE

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;
#endif

    return err;
}

/** @} (end addtogroup TML) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Performs hardware initialization of the TML.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 *
 * @retval FSP_SUCCESS                Successful initialize.
 * @retval FSP_ERR_IN_USE             Channel is running
 **********************************************************************************************************************/
fsp_err_t r_tml_hardware_initialize (tml_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    uint8_t channel = p_cfg->channel;
    p_instance_ctrl->channel_mask = (uint8_t) (1U << channel);
    uint8_t itlctl0;
    uint8_t itlcsel0;

    /* Enable the TML channel and take module out of stop state. */
    R_BSP_MODULE_START(FSP_IP_TML, channel);

    /* Critical section required because ITLCTL0, ITLFDIV00, ITLFDIV01, ITLCSEL0  registers is shared with other instances. */
    TML_PRV_CRITICAL_SECTION_ENTER();

    uint8_t timer_status = R_TML->ITLCTL0 & BSP_FEATURE_TML_VALID_CHANNEL_MASK;

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE

    /* Save pointer to extended configuration structure. */
    tml_extended_cfg_t * p_tml_cfg = (tml_extended_cfg_t *) p_cfg->p_extend;

    if (TIMER_MODE_16_BIT_CAPTURE == p_cfg->mode)
    {
        /* Only set the ITLCC0.CTRS, ITLCC0.CAPCCR and ITLCC0.CAPEN when all timer channels are stopped. */
        FSP_ERROR_RETURN(0U == timer_status, FSP_ERR_IN_USE);

        /* Select the capture trigger */
        uint8_t itlcc0 = R_TML_ITLCC0_CTRS_Msk & (uint8_t) (p_tml_cfg->capture_trigger << R_TML_ITLCC0_CTRS_Pos);

        /* Specify the clearing of the counter values in channels 0 and 1 after completion of capturing. */
        itlcc0 |= R_TML_ITLCC0_CAPCCR_Msk & (uint8_t) (p_tml_cfg->counter_status << R_TML_ITLCC0_CAPCCR_Pos);

        /* Enable capturing. */
        itlcc0 |= R_TML_ITLCC0_CAPEN_Msk;

        /* Write to ITLCC0 register */
        R_TML->ITLCC0 = itlcc0;

        /* Select the capture mode. */
        itlctl0 = R_TML_ITLCTL0_MD_Msk & (uint8_t) (TIMER_MODE_16_BIT_COUNTER << R_TML_ITLCTL0_MD_Pos);
    }
    else
#endif
    {
        /* Select the operation mode. */
        itlctl0 = R_TML_ITLCTL0_MD_Msk & (uint8_t) (p_cfg->mode << R_TML_ITLCTL0_MD_Pos);
    }

    /* Select the count clock for the counter timer */
    itlcsel0 = R_TML_ITLCSEL0_ISEL_Msk & (uint8_t) (TML_PRV_ITLCSEL0_ISEL_VALUE << R_TML_ITLCSEL0_ISEL_Pos);

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE

    /* Select the count clock for the capture timer */
    if (R_TML->ITLCC0_b.CAPEN)
    {
        itlcsel0 |= (R_TML_ITLCSEL0_CSEL_Msk & (uint8_t) (TML_PRV_ITLCSEL0_CSEL_VALUE << R_TML_ITLCSEL0_CSEL_Pos));
    }
#endif

    /* Write to registers to setting mode/clock. */
#if !TML_CFG_SINGLE_CHANNEL_ENABLE
    if (0U == g_modeset++)
#endif
    {
        R_TML->ITLCTL0 = itlctl0 | timer_status;
    }

    R_TML->ITLCSEL0 = itlcsel0;

    /* Select the frequency division ratio for the count source. */
    *(TML_PRV_ITLFDIV_ADDRESS) |= TML_PRV_ITLFDIV_MASK &
                                  ((uint8_t) p_cfg->source_div << (TML_PRV_ITLFDIV_POS));

    TML_PRV_CRITICAL_SECTION_EXIT();

    /* Specify a period value for timer channel. */
    r_tml_period_counts_set(p_instance_ctrl, (p_cfg->period_counts - 1));

#if TML_CFG_INTERRUPT_SUPPORT_ENABLE

    /* Enable CPU interrupts if callback is not null. */
    if (0 <= p_cfg->cycle_end_irq)
    {
        R_BSP_IrqCfgEnable(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the period value for counter channel.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  period_counts          Time until timer should expire.
 **********************************************************************************************************************/
void r_tml_period_counts_set (tml_instance_ctrl_t * const p_instance_ctrl, uint32_t const period_counts)
{
    /* Specify a period value. */
    switch (p_instance_ctrl->p_cfg->mode)
    {
        case TIMER_MODE_8_BIT_COUNTER:
        {
            /* The ITLCMP00_L for channel 0
             * The ITLCMP00_H for channel 1
             * The ITLCMP01_L for channel 2
             * The ITLCMP01_H for channel 3
             */
            *(&(R_TML->ITLCMP00_L) + TML_PRV_CHANNEL) = (uint8_t) (period_counts);
            break;
        }

        case TIMER_MODE_16_BIT_COUNTER:
        {
            /* Set the ITLCMP0n register (n: 0, 1) */
            *(&(R_TML->ITLCMP00) + TML_PRV_CHANNEL / 2) = (uint16_t) (period_counts);
            break;
        }

        case TIMER_MODE_32_BIT_COUNTER:
        {
            /* Set the upper 16-bit period value in the ITLCMP01 register and the lower 16-bit period value
             * in the ITLCMP00 register. */
            R_TML->ITLCMP01 = (uint16_t) (period_counts >> TML_PRV_ITLCMP0_UPPER_16_BIT_POS);
            R_TML->ITLCMP00 = (uint16_t) (period_counts & TML_PRV_ITLCMP0_UPPER_16_BIT_CLEARED);
            break;
        }

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
        case TIMER_MODE_16_BIT_CAPTURE:
        {
            /* Save pointer to extended configuration structure. */
            tml_extended_cfg_t * p_tml_cfg = (tml_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

            if (TML_CAPTURE_TRIGGER_ITLCMP01 == p_tml_cfg->capture_trigger)
            {
                /* Set the period value into ITLCMP01 register for channel 2 + 3 */
                R_TML->ITLCMP01 = (uint16_t) (period_counts);
            }

            break;
        }
#endif

        default:
        {
            break;
        }
    }
}

#if TML_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking for R_TML_Open.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 * @param[in]  p_cfg                  Pointer to timer configuration.
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL or the source divider is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       timer_cfg_t::p_callback is not NULL, but ISR is not enabled.
 *                                        ISR must be enabled to use one-shot mode or callback.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 * @retval FSP_ERR_INVALID_CHANNEL        Selected channel is invalid
 * @retval FSP_ERR_INVALID_MODE           The mode requested in the p_cfg parameter is incorrect.
 *                                        It must be the same for all instances.
 * @retval FSP_ERR_IN_USE                 Channel is running
 **********************************************************************************************************************/
fsp_err_t r_tml_open_param_checking (tml_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Check NULL pointer. */
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_instance_ctrl);

    timer_mode_t mode         = p_cfg->mode;
    uint8_t      channel_mask = (uint8_t) (1U << p_cfg->channel);

    /* Check the status of channel selected. */
    FSP_ERROR_RETURN(TML_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Selected channel must be disabled (ITLCTL0.ENx is 0U). */
    FSP_ERROR_RETURN(0U == (R_TML->ITLCTL0 & channel_mask), FSP_ERR_IN_USE);

 #if !TML_CFG_SINGLE_CHANNEL_ENABLE

    /* Selected mode must be the same for all instance. */
    if (0U != g_modeset)
    {
  #if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
        tml_extended_cfg_t * p_cfg_ext = (tml_extended_cfg_t *) p_cfg->p_extend;

        /* Channels 2 and 3 can only be used in 16-bit counter mode when an interrupt on compare match with
         * ITLCMP01 is not to be used as a capture trigger. */
        if (!(((TIMER_MODE_16_BIT_COUNTER == R_TML->ITLCTL0_b.MD) &&
               (TIMER_MODE_16_BIT_CAPTURE == mode) &&
               (TML_CAPTURE_TRIGGER_ITLCMP01 != p_cfg_ext->capture_trigger)) ||
              (R_TML->ITLCC0_b.CAPEN &&
               (TML_CAPTURE_TRIGGER_ITLCMP01 != R_TML->ITLCC0_b.CTRS) &&
               (TIMER_MODE_16_BIT_COUNTER == mode))))
  #endif
        {
            /* Selected mode must be the same for all instance. */
            FSP_ERROR_RETURN(mode == R_TML->ITLCTL0_b.MD, FSP_ERR_INVALID_MODE);
        }
    }
 #endif

    /* Channel selected must be in range 0:3. */
    FSP_ERROR_RETURN((channel_mask & BSP_FEATURE_TML_VALID_CHANNEL_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Check the maximum range of counter clock source division. */
    FSP_ASSERT(p_cfg->source_div <= BSP_FEATURE_TML_MAX_CLOCK_DIVIDER);
 #if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE

    /* The clock source division must be 0 if 16-bit counter channel use CSEL as clock source. */
    if (R_TML->ITLCC0_b.CAPEN && (TIMER_MODE_16_BIT_COUNTER == mode))
    {
        FSP_ASSERT(TIMER_SOURCE_DIV_1 == p_cfg->source_div);
    }
 #endif

    /* Validate period must be configured in correct range and channel must be selected according to each mode. */
    FSP_ASSERT(1 < p_cfg->period_counts);

 #if TML_CFG_SINGLE_CHANNEL_ENABLE

    /* Selected channel must match the channel selected by TML_CFG_SINGLE_CHANNEL_ENABLE */
    FSP_ERROR_RETURN(0U == p_cfg->channel, FSP_ERR_INVALID_CHANNEL);
 #endif

    if (TIMER_MODE_8_BIT_COUNTER == mode)
    {
        FSP_ASSERT(1 < p_cfg->period_counts);
        FSP_ASSERT(p_cfg->period_counts <= (UINT8_MAX + 1));
    }
    else if ((TIMER_MODE_16_BIT_COUNTER == mode) || (TIMER_MODE_16_BIT_CAPTURE == mode))
    {
        FSP_ASSERT(1 < p_cfg->period_counts);
        FSP_ASSERT(p_cfg->period_counts <= (UINT16_MAX + 1));
        if (TIMER_MODE_16_BIT_COUNTER == mode)
        {
            FSP_ERROR_RETURN((channel_mask & VALID_16_BIT_COUNTER_CHANNEL_MASK), FSP_ERR_INVALID_CHANNEL);
        }

 #if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
        else
        {
            FSP_ERROR_RETURN((channel_mask & VALID_16_BIT_CAPTURE_CHANNEL_MASK), FSP_ERR_INVALID_CHANNEL);
        }
 #endif
    }
    else                               // TIMER_MODE_32_BIT_COUNTER == mode
    {
        FSP_ERROR_RETURN((channel_mask & VALID_32_BIT_COUNTER_CHANNEL_MASK), FSP_ERR_INVALID_CHANNEL);
    }

    /* Enable IRQ if user supplied a callback function. */
    if (p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Get the period value for counter channel.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 **********************************************************************************************************************/
uint32_t r_tml_period_counts_get (tml_instance_ctrl_t * const p_instance_ctrl)
{
    uint32_t period_counts = 0;

    /* Get a period value. */
    switch (p_instance_ctrl->p_cfg->mode)
    {
        case TIMER_MODE_8_BIT_COUNTER:
        {
            /* The ITLCMP00_L for channel 0
             * The ITLCMP00_H for channel 1
             * The ITLCMP01_L for channel 2
             * The ITLCMP01_H for channel 3
             */
            period_counts = *(&(R_TML->ITLCMP00_L) + TML_PRV_CHANNEL);
            break;
        }

        case TIMER_MODE_16_BIT_COUNTER:
        {
            /* Set the ITLCMP0n register (n: 0, 1) */
            period_counts = *(&(R_TML->ITLCMP00) + TML_PRV_CHANNEL / 2);
            break;
        }

        case TIMER_MODE_32_BIT_COUNTER:
        {
            /* Get the upper 16-bit period value in the ITLCMP01 register and the lower 16-bit period value
             * in the ITLCMP00 register. */
            period_counts  = (uint32_t) R_TML->ITLCMP01 << 16;
            period_counts |= R_TML->ITLCMP00;
            break;
        }

#if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
        case TIMER_MODE_16_BIT_CAPTURE:
        {
            /* Save pointer to extended configuration structure. */
            tml_extended_cfg_t * p_tml_cfg = (tml_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

            if (TML_CAPTURE_TRIGGER_ITLCMP01 == p_tml_cfg->capture_trigger)
            {
                /* Get the period value into ITLCMP01 register for channel 2 + 3 */
                period_counts = R_TML->ITLCMP01;
            }

            break;
        }
#endif

        default:
        {
            break;
        }
    }

    return period_counts;
}

#if TML_CFG_INTERRUPT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Helper for enabling or disabling interrupts
 *
 * @param[in]  p_ctrl        Instance control block.
 * @param[in]  enable        Whether or not to enable disable interrupts.
 **********************************************************************************************************************/
static fsp_err_t r_tml_enable_helper (timer_ctrl_t * const p_ctrl, bool enable)
{
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) p_ctrl;
 #if TML_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TML_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(TML_PRV_CHANNEL_MASK & BSP_FEATURE_TML_VALID_CHANNEL_MASK, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
 #endif

 #if TML_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
 #endif

    /* Critical section required because ITLMKF0, ITLS0, ITLCTL0 register is shared with other instances. */
    TML_PRV_CRITICAL_SECTION_ENTER();

    uint8_t itls0   = R_TML->ITLS0;
    uint8_t itlmkf0 = R_TML->ITLMKF0;

    /* Clear the ITF0i interrupt status flags for channel used. */
    itls0 &= (uint8_t) ~(TML_PRV_CHANNEL_MASK);

    if (enable)
    {
        /* Enable the interrupt generation from the selected channel by clearing the mask bits . */
        itlmkf0 &= (uint8_t) ~(TML_PRV_CHANNEL_MASK);
    }
    else
    {
        /* Disable the interrupt generation from the selected channel by setting the mask bits . */
        itlmkf0 |= TML_PRV_CHANNEL_MASK;
    }

 #if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
    if (TIMER_MODE_16_BIT_CAPTURE == p_instance_ctrl->p_cfg->mode)
    {
        /* Clear the ITF0C interrupt status flags. */
        itls0 &= (uint8_t) ~(R_TML_ITLS0_ITF0C_Msk);

        if (enable)
        {
            /* Disable the MKF0C masks of the ITF0C status flags. */
            itlmkf0 &= (uint8_t) ~(R_TML_ITLMKF0_MKF0C_Msk);
        }
        else
        {
            /* Enable the MKF0C masks of the ITF0C status flags. */
            itlmkf0 |= R_TML_ITLMKF0_MKF0C_Msk;
        }
    }
 #endif

    /* Write to registers */
    R_TML->ITLS0   = itls0;
    R_TML->ITLMKF0 = itlmkf0;

    TML_PRV_CRITICAL_SECTION_EXIT();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Interrupt triggered by a compare match or capture.
 *
 * Clears interrupt, disables captures and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void tml_itl_or_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

 #if TML_CFG_SINGLE_CHANNEL_ENABLE
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    tml_instance_ctrl_t * p_instance_ctrl = (tml_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
 #else
    tml_instance_ctrl_t * p_instance_ctrl = gp_tml_ctrls[TML_CHANNEL_0];
 #endif
    uint8_t       itls0   = R_TML->ITLS0;
    uint32_t      capture = 0;
    timer_event_t event   = TIMER_EVENT_CYCLE_END;

 #if TML_CFG_16_BIT_CAPTURE_MODE_ENABLE
    if (itls0 & R_TML_ITLS0_ITF0C_Msk)
    {
        /* Clear the interrupt flag. */
        R_TML->ITLS0 = itls0 & ((uint8_t) ~R_TML_ITLS0_ITF0C_Msk);

        event = TIMER_EVENT_CAPTURE_EDGE;

        /* Get captured value */
        capture = R_TML->ITLCAP00;
    }
    else
 #endif
    {
 #if !TML_CFG_SINGLE_CHANNEL_ENABLE

        /* Due to the shared IRQ for all of the TML we need to find the stored context from the channel instance. */
        for (tml_channel_t channel = TML_CHANNEL_0; channel < BSP_FEATURE_TML_NUM_CHANNELS; channel++)
        {
            if (itls0 & (1U << channel))
            {
                p_instance_ctrl = gp_tml_ctrls[channel];
                break;
            }
        }
 #endif

        /* Clear the interrupt flag. */
        R_TML->ITLS0 = itls0 & (uint8_t) ~(TML_PRV_CHANNEL_MASK);
    }

    /* If a callback is provided, then call it with the captured counter value. */
    if (NULL != p_instance_ctrl->p_callback)
    {
        timer_callback_args_t args =
        {
            .p_context = p_instance_ctrl->p_context,
            .event     = event,
            .capture   = capture,
        };

        /* Call the callback. */
        p_instance_ctrl->p_callback(&args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif
