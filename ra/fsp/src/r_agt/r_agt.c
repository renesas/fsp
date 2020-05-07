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
#include "r_agt.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "AGT" in ASCII, used to determine if channel is open. */
#define AGT_OPEN                                (0x00414754ULL)

#define AGT_PRV_VALID_CHANNEL_MASK              (0x3U)

#define AGT_COMPARE_MATCH_A_OUTPUT              (0x03U) ///< Enabling AGTOAn pin
#define AGT_COMPARE_MATCH_B_OUTPUT              (0x30U) ///< Enabling AGTOBn pin

#define AGT_SOURCE_CLOCK_PCLKB_BITS             (0x3U)

#define FSUB_FREQUENCY_HZ                       (32768U)

#define AGT_PRV_CLOCK_PCLKB_DIV_8               (1U)
#define AGT_PRV_CLOCK_PCLKB_DIV_2               (3U)

#define AGT_PRV_AGTMR1_TMOD_EVENT_COUNTER       (2U)
#define AGT_PRV_AGTMR1_TMOD_PULSE_WIDTH         (3U)

#define AGT_PRV_AGTCR_FORCE_STOP                (0xF4U)
#define AGT_PRV_AGTCR_FORCE_STOP_CLEAR_FLAGS    (0x4U)
#define AGT_PRV_AGTCR_STATUS_FLAGS              (0xF0U)
#define AGT_PRV_AGTCR_STOP_TIMER                (0xF0U)
#define AGT_PRV_AGTCR_START_TIMER               (0xF1U)

#define AGT_PRV_AGTCMSR_PIN_B_OFFSET            (4U)
#define AGT_PRV_AGTCMSR_VALID_BITS              (0x77U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_agt_period_register_set(agt_instance_ctrl_t * p_instance_ctrl, uint32_t period_counts);

static void r_agt_hardware_cfg(agt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg);

static uint32_t r_agt_clock_frequency_get(R_AGT0_Type * p_agt_regs);

static fsp_err_t r_agt_common_preamble(agt_instance_ctrl_t * p_instance_ctrl);

#if AGT_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_agt_open_param_checking(agt_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg);

#endif

/* ISRs. */
void agt_int_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure. */
static const fsp_version_t s_agt_version =
{
    .api_version_minor  = TIMER_API_VERSION_MINOR,
    .api_version_major  = TIMER_API_VERSION_MAJOR,
    .code_version_minor = AGT_CODE_VERSION_MINOR,
    .code_version_major = AGT_CODE_VERSION_MAJOR,
};

/* The period for channel 0 must be known to calculate the frequency of channel 1 if the count source is AGT0
 * underflow. */
static uint32_t gp_prv_agt_periods[2];

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** AGT Implementation of General Timer Driver  */
const timer_api_t g_timer_on_agt =
{
    .open         = R_AGT_Open,
    .stop         = R_AGT_Stop,
    .start        = R_AGT_Start,
    .reset        = R_AGT_Reset,
    .enable       = R_AGT_Enable,
    .disable      = R_AGT_Disable,
    .periodSet    = R_AGT_PeriodSet,
    .dutyCycleSet = R_AGT_DutyCycleSet,
    .infoGet      = R_AGT_InfoGet,
    .statusGet    = R_AGT_StatusGet,
    .close        = R_AGT_Close,
    .versionGet   = R_AGT_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup AGT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the AGT module instance. Implements @ref timer_api_t::open.
 *
 * The AGT hardware does not support one-shot functionality natively.  The one-shot feature is therefore implemented in
 * the AGT HAL layer. For a timer configured as a one-shot timer, the timer is stopped upon the first timer expiration.
 *
 * The AGT implementation of the general timer can accept an optional agt_extended_cfg_t extension parameter.  For
 * AGT, the extension specifies the clock to be used as timer source and the output pin configurations.  If the
 * extension parameter is not specified (NULL), the default clock PCLKB is used and the output pins are disabled.
 *
 * Example:
 * @snippet r_agt_example.c R_AGT_Open
 *
 * @retval FSP_SUCCESS                 Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION           A required input pointer is NULL or the period is not in the valid range of
 *                                     1 to 0xFFFF.
 * @retval FSP_ERR_ALREADY_OPEN        R_AGT_Open has already been called for this p_ctrl.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    A required interrupt has not been enabled in the vector table.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel number is not available on AGT.
 **********************************************************************************************************************/
fsp_err_t R_AGT_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;

#if AGT_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_agt_open_param_checking(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    uint32_t base_address = (uint32_t) R_AGT0 + (p_cfg->channel * ((uint32_t) R_AGT1 - (uint32_t) R_AGT0));
    p_instance_ctrl->p_reg = (R_AGT0_Type *) base_address;
    p_instance_ctrl->p_cfg = p_cfg;

    /* Power on the AGT channel. */
    R_BSP_MODULE_START(FSP_IP_AGT, p_cfg->channel);

    /* Forcibly stop timer and clear flags. */
    p_instance_ctrl->p_reg->AGTCR = AGT_PRV_AGTCR_FORCE_STOP_CLEAR_FLAGS;

    /* Clear AGTMR2 before AGTMR1 is set. Reference Note 3 in section 25.2.6 "AGT Mode Register 2 (AGTMR2)"
     * of the RA6M3 manual R01UH0886EJ0100. */
    p_instance_ctrl->p_reg->AGTMR2 = 0U;

    /* Set count source and divider and configure pins. */
    r_agt_hardware_cfg(p_instance_ctrl, p_cfg);

    /* Set period register and update duty cycle if output mode is used for one-shot or periodic mode. */
    r_agt_period_register_set(p_instance_ctrl, p_cfg->period_counts);

    if (p_cfg->cycle_end_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);
    }

    p_instance_ctrl->open = AGT_OPEN;

    /* All done.  */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer. Implements @ref timer_api_t::start.
 *
 * Example:
 * @snippet r_agt_example.c R_AGT_Start
 *
 * @retval FSP_SUCCESS                 Timer started.
 * @retval FSP_ERR_ASSERTION           p_ctrl is null.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_Start (timer_ctrl_t * const p_ctrl)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Start timer */
    p_instance_ctrl->p_reg->AGTCR = AGT_PRV_AGTCR_START_TIMER;

#if AGT_CFG_OUTPUT_SUPPORT_ENABLE

    /* If using output compare in one-shot mode, update the compare match registers after starting the timer. This
     * ensures the output pin will not toggle again right after the period ends. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        /* Verify the timer is started before modifying any other AGT registers. Reference section 25.4.1 "Count
         * Operation Start and Stop Control" in the RA6M3 manual R01UH0886EJ0100. */
        FSP_HARDWARE_REGISTER_WAIT(1U, p_instance_ctrl->p_reg->AGTCR_b.TCSTF);
        p_instance_ctrl->p_reg->AGTCMA = UINT16_MAX;
        p_instance_ctrl->p_reg->AGTCMB = UINT16_MAX;
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops the timer.  Implements @ref timer_api_t::stop.
 *
 * Example:
 * @snippet r_agt_example.c R_AGT_Stop
 *
 * @retval FSP_SUCCESS                 Timer stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_Stop (timer_ctrl_t * const p_ctrl)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Stop timer */
    p_instance_ctrl->p_reg->AGTCR = AGT_PRV_AGTCR_STOP_TIMER;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to the period minus one. Implements @ref timer_api_t::reset.
 *
 * @retval FSP_SUCCESS                 Counter reset.
 * @retval FSP_ERR_ASSERTION           p_ctrl is NULL
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_Reset (timer_ctrl_t * const p_ctrl)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Reset counter to period minus one. */
    p_instance_ctrl->p_reg->AGT = (uint16_t) (p_instance_ctrl->period - 1U);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::enable.
 *
 * Example:
 * @snippet r_agt_example.c R_AGT_Enable
 *
 * @retval FSP_SUCCESS                 External events successfully enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_Enable (timer_ctrl_t * const p_ctrl)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;
#if AGT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(AGT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Reset counter to period minus one. */
    p_instance_ctrl->p_reg->AGT = (uint16_t) (p_instance_ctrl->period - 1U);

    /* Enable captures. */
    p_instance_ctrl->p_reg->AGTCR = AGT_PRV_AGTCR_START_TIMER;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::disable.
 *
 * Example:
 * @snippet r_agt_example.c R_AGT_Disable
 *
 * @retval FSP_SUCCESS                 External events successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_Disable (timer_ctrl_t * const p_ctrl)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;
#if AGT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(AGT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable captures. */
    p_instance_ctrl->p_reg->AGTCR = AGT_PRV_AGTCR_STOP_TIMER;

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
 * @snippet r_agt_example.c R_AGT_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value updated.
 * @retval FSP_ERR_ASSERTION           A required pointer was NULL, or the period was not in the valid range of
 *                                     1 to 0xFFFF.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;
#if AGT_CFG_PARAM_CHECKING_ENABLE

    /* Validate period parameter. */
    FSP_ASSERT(0U != period_counts);
    FSP_ASSERT(period_counts <= AGT_MAX_PERIOD);
#endif

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set period. */
    r_agt_period_register_set(p_instance_ctrl, period_counts);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates duty cycle. If the timer is counting, the new duty cycle is reflected after the next counter underflow.
 * Implements @ref timer_api_t::dutyCycleSet.
 *
 * Example:
 * @snippet r_agt_example.c R_AGT_DutyCycleSet
 *
 * @retval FSP_SUCCESS                 Duty cycle updated.
 * @retval FSP_ERR_ASSERTION           A required pointer was NULL, or the pin was not AGT_AGTO_AGTOA or AGT_AGTO_AGTOB.
 * @retval FSP_ERR_INVALID_ARGUMENT    Duty cycle was not in the valid range of 0 to period (counts) - 1
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 * @retval FSP_ERR_UNSUPPORTED         AGT_CFG_OUTPUT_SUPPORT_ENABLE is 0.
 **********************************************************************************************************************/
fsp_err_t R_AGT_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
#if AGT_CFG_OUTPUT_SUPPORT_ENABLE
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;
 #if AGT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT((pin == AGT_OUTPUT_PIN_AGTOA) || (pin == AGT_OUTPUT_PIN_AGTOB));
 #endif

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if AGT_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(duty_cycle_counts < (p_instance_ctrl->period), FSP_ERR_INVALID_ARGUMENT);
 #endif

    uint32_t temp_duty_cycle_counts         = duty_cycle_counts;
    uint32_t agtcmsr_agtoab_start_level_bit = 1U << 2 << (4 * pin);
    agt_extended_cfg_t const * p_extend     = (agt_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    if (p_extend->agtoab_settings & agtcmsr_agtoab_start_level_bit)
    {
        /* Invert duty cycle if this pin starts high since the high portion is at the beginning of the cycle. */
        temp_duty_cycle_counts = p_instance_ctrl->period - temp_duty_cycle_counts;
    }

    /* Set duty cycle. */
    volatile uint16_t * const p_agtcm = &p_instance_ctrl->p_reg->AGTCMA;
    p_agtcm[pin] = (uint16_t) temp_duty_cycle_counts;

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
 * @snippet r_agt_example.c R_AGT_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, and frequency stored in p_info.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;
#if AGT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_info);
#endif

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Get and store period */
    p_info->period_counts = p_instance_ctrl->period;

    /* Get and store clock frequency */
    agt_extended_cfg_t const * p_extend = (agt_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    if (AGT_CLOCK_AGT0_UNDERFLOW == p_extend->count_source)
    {
        /* Clock frequency is the AGT0 clock frequency divided by the period of AGT0. */
        p_info->clock_frequency = r_agt_clock_frequency_get(R_AGT0) / gp_prv_agt_periods[0];
    }
    else
    {
        p_info->clock_frequency = r_agt_clock_frequency_get(p_instance_ctrl->p_reg);
    }

    /* AGT supports only counting down direction */
    p_info->count_direction = TIMER_DIRECTION_DOWN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Retrieves the current state and counter value stores them in p_status. Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_agt_example.c R_AGT_StatusGet
 *
 * @retval FSP_SUCCESS                 Current status and counter value provided in p_status.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
fsp_err_t R_AGT_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;

#if AGT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_status);
#endif

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Read the state. */
    p_status->state = (timer_state_t) p_instance_ctrl->p_reg->AGTCR_b.TCSTF;

    /* Read counter value */
    p_status->counter = p_instance_ctrl->p_reg->AGT;

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
fsp_err_t R_AGT_Close (timer_ctrl_t * const p_ctrl)
{
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = r_agt_common_preamble(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Cleanup the device: Stop counter, disable interrupts, and power down if no other channels are in use. */

    /* Stop timer */
    p_instance_ctrl->p_reg->AGTCR = AGT_PRV_AGTCR_FORCE_STOP;

    /* Clear AGT output. */
    p_instance_ctrl->p_reg->AGTIOC = 0U;

    if (FSP_INVALID_VECTOR != p_instance_ctrl->p_cfg->cycle_end_irq)
    {
        NVIC_DisableIRQ(p_instance_ctrl->p_cfg->cycle_end_irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->cycle_end_irq, p_instance_ctrl);
    }

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets driver version based on compile time macros.  Implements @ref timer_api_t::versionGet.
 *
 * @retval     FSP_SUCCESS          Version in p_version.
 * @retval     FSP_ERR_ASSERTION    The parameter p_version is NULL.
 **********************************************************************************************************************/
fsp_err_t R_AGT_VersionGet (fsp_version_t * const p_version)
{
#if AGT_CFG_PARAM_CHECKING_ENABLE

    /* Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = s_agt_version.version_id;

    return FSP_SUCCESS;
}

/** @} (end addtogroup AGT) */

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if AGT_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking for R_AGT_Open.
 *
 * @param[in] p_instance_ctrl          Pointer to instance control structure.
 * @param[in]  p_cfg              Configuration structure for this instance
 *
 * @retval FSP_SUCCESS                 Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION           A required input pointer is NULL or the period is not in the valid range of
 *                                     1 to 0xFFFF.
 * @retval FSP_ERR_ALREADY_OPEN        R_AGT_Open has already been called for this p_ctrl.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    A required interrupt has not been enabled in the vector table.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel number is not available on AGT.
 **********************************************************************************************************************/
static fsp_err_t r_agt_open_param_checking (agt_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(AGT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Enable IRQ if user supplied a callback function,
     *  or if the timer is a one-shot timer (so the driver is able to
     *  turn off the timer after one period. */
    if ((NULL != p_cfg->p_callback) || (TIMER_MODE_ONE_SHOT == p_cfg->mode))
    {
        /* Return error if IRQ is required and not in the vector table. */
        FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    FSP_ASSERT(0U != p_cfg->period_counts);

    /* Validate period parameter. */
    FSP_ASSERT(p_cfg->period_counts <= AGT_MAX_PERIOD);

    /* Validate channel number. */
    FSP_ERROR_RETURN(((1U << p_cfg->channel) & AGT_PRV_VALID_CHANNEL_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* AGT_CLOCK_AGT0_UNDERFLOW is not allowed on AGT channel 0. */
    agt_extended_cfg_t const * p_extend = (agt_extended_cfg_t const *) p_cfg->p_extend;
    FSP_ASSERT((AGT_CLOCK_AGT0_UNDERFLOW != p_extend->count_source) || (1U == p_cfg->channel));

    /* Validate divider. */
    if (AGT_CLOCK_PCLKB == p_extend->count_source)
    {
        /* Allowed dividers for PCLKB are 1, 2, and 8. */
        FSP_ASSERT(p_cfg->source_div <= TIMER_SOURCE_DIV_8);
        FSP_ASSERT(p_cfg->source_div != TIMER_SOURCE_DIV_4);
    }
    else if (AGT_CLOCK_AGT0_UNDERFLOW == p_extend->count_source)
    {
        /* Divider not used if AGT0 underflow is selected as count source. */
        FSP_ASSERT(p_cfg->source_div == TIMER_SOURCE_DIV_1);
    }
    else
    {
        /* Allowed dividers for LOCO and SUBCLOCK are 1, 2, 4, 8, 16, 32, 64, and 128. */
        FSP_ASSERT(p_cfg->source_div <= TIMER_SOURCE_DIV_128);
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Common code at the beginning of all AGT functions except open.
 *
 * @param[in] p_instance_ctrl          Pointer to instance control structure.
 *
 * @retval FSP_SUCCESS                 No invalid conditions detected, timer state matches expected state.
 * @retval FSP_ERR_ASSERTION           p_ctrl is null.
 * @retval FSP_ERR_NOT_OPEN            The instance control structure is not opened.
 **********************************************************************************************************************/
static fsp_err_t r_agt_common_preamble (agt_instance_ctrl_t * p_instance_ctrl)
{
#if AGT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(AGT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Ensure timer state reflects expected status. Reference section 25.4.1 "Count Operation Start and Stop Control"
     * in the RA6M3 manual R01UH0886EJ0100. */
    uint32_t agtcr_tstart = p_instance_ctrl->p_reg->AGTCR_b.TSTART;
    FSP_HARDWARE_REGISTER_WAIT(agtcr_tstart, p_instance_ctrl->p_reg->AGTCR_b.TCSTF);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets count source and divider.
 *
 * @note Counter must be stopped before entering this function.
 *
 * @param[in]  p_instance_ctrl    Control block for this instance
 * @param[in]  p_cfg              Configuration structure for this instance
 **********************************************************************************************************************/
static void r_agt_hardware_cfg (agt_instance_ctrl_t * const p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    /* Update the divider for PCLKB. */
    agt_extended_cfg_t const * p_extend = (agt_extended_cfg_t const *) p_cfg->p_extend;
    uint32_t count_source_int           = (uint32_t) p_extend->count_source;
    uint32_t agtmr2  = 0U;
    uint32_t agtcmsr = 0U;
    uint32_t tedgsel = 0U;
    uint32_t agtioc  = p_extend->agtio_filter;
    uint32_t mode    = p_extend->measurement_mode & R_AGT0_AGTMR1_TMOD_Msk;
    uint32_t edge    = 0U;
    if (AGT_CLOCK_PCLKB == p_extend->count_source)
    {
        if (TIMER_SOURCE_DIV_1 != p_cfg->source_div)
        {
            /* Toggle the second bit if the count_source_int is not 0 to map PCLKB / 8 to 1 and PCLKB / 2 to 3. */
            count_source_int   = p_cfg->source_div ^ 2U;
            count_source_int <<= R_AGT0_AGTMR1_TCK_Pos;
        }
    }

#if AGT_CFG_INPUT_SUPPORT_ENABLE
    else if (AGT_CLOCK_AGTIO & p_extend->count_source)
    {
        /* If the count source is external, configure the AGT for event counter mode. */
        mode                             = AGT_PRV_AGTMR1_TMOD_EVENT_COUNTER;
        count_source_int                 = 0U;
        edge                            |= (p_extend->trigger_edge & R_AGT0_AGTMR1_TEDGPL_Msk);
        agtioc                          |= (p_extend->enable_pin & R_AGT0_AGTIOC_TIOGT_Msk);
        p_instance_ctrl->p_reg->AGTISR   = (p_extend->enable_pin & R_AGT0_AGTISR_EEPS_Msk);
        p_instance_ctrl->p_reg->AGTIOSEL = (uint8_t) (p_extend->count_source & (uint8_t) ~AGT_CLOCK_AGTIO);
    }
#endif
    else if (AGT_CLOCK_AGT0_UNDERFLOW != p_extend->count_source)
    {
        /* Update the divider for LOCO/subclock. */
        agtmr2 = p_cfg->source_div;
    }
    else
    {
        /* No divider can be used when count source is AGT_CLOCK_AGT0_UNDERFLOW. */
    }

    uint32_t agtmr1 = (count_source_int | edge) | mode;

    /* Configure output settings. */

#if AGT_CFG_OUTPUT_SUPPORT_ENABLE

    /* Set output if requested */
    agtcmsr = p_extend->agtoab_settings & AGT_PRV_AGTCMSR_VALID_BITS;

    /* Set initial duty cycle for PWM mode in open.  Duty cycle is set for other modes in r_agt_period_register_set. */
    if (TIMER_MODE_PWM == p_instance_ctrl->p_cfg->mode)
    {
        uint32_t inverted_duty_cycle = p_instance_ctrl->p_cfg->period_counts -
                                       p_instance_ctrl->p_cfg->duty_cycle_counts;
        uint32_t agtcma = p_instance_ctrl->p_cfg->duty_cycle_counts;
        uint32_t agtcmb = p_instance_ctrl->p_cfg->duty_cycle_counts;
        if (AGT_PIN_CFG_START_LEVEL_HIGH == p_extend->agtoa)
        {
            agtcma = inverted_duty_cycle;
        }

        if (AGT_PIN_CFG_START_LEVEL_HIGH == p_extend->agtob)
        {
            agtcmb = inverted_duty_cycle;
        }

        p_instance_ctrl->p_reg->AGTCMA = (uint16_t) agtcma;
        p_instance_ctrl->p_reg->AGTCMB = (uint16_t) agtcmb;
    }

    /* Configure TEDGSEL bit based on user input. */
    if (AGT_PIN_CFG_DISABLED != p_extend->agto)
    {
        /* Set the TOE bit if AGTO is enabled.  AGTO can be enabled in any mode. */
        agtioc |= (1U << R_AGT0_AGTIOC_TOE_Pos);

        if (AGT_PIN_CFG_START_LEVEL_LOW == p_extend->agto)
        {
            /* Configure the start level of AGTO. */
            tedgsel |= (1U << R_AGT0_AGTIOC_TEDGSEL_Pos);
        }
    }
#endif
#if AGT_CFG_INPUT_SUPPORT_ENABLE && AGT_CFG_OUTPUT_SUPPORT_ENABLE
    else
#endif
#if AGT_CFG_INPUT_SUPPORT_ENABLE
    {
        /* This if statement applies when p_extend->measurement_mode is AGT_MEASURE_PULSE_WIDTH_LOW_LEVEL or
         * AGT_MEASURE_PULSE_WIDTH_HIGH_LEVEL because the high level bit is in bit 4 and was masked off of mode. */
        if (AGT_PRV_AGTMR1_TMOD_PULSE_WIDTH == mode)
        {
            /* Level is stored with measurement mode for pulse width mode. */
            tedgsel = p_extend->measurement_mode >> 4U;
        }
        else
        {
            /* Use the trigger edge for pulse period or event counting modes. */
            tedgsel = (p_extend->trigger_edge & R_AGT0_AGTIOC_TEDGSEL_Msk);
        }
    }
#endif

    agtioc |= tedgsel;

    p_instance_ctrl->p_reg->AGTIOC  = (uint8_t) agtioc;
    p_instance_ctrl->p_reg->AGTCMSR = (uint8_t) agtcmsr;
    p_instance_ctrl->p_reg->AGTMR1  = (uint8_t) agtmr1;
    p_instance_ctrl->p_reg->AGTMR2  = (uint8_t) agtmr2;
}

/*******************************************************************************************************************//**
 * Sets period register and updates compare match registers in one-shot and periodic mode.
 *
 * @param[in]  p_instance_ctrl    Control block for this instance
 * @param[in]  period_counts      AGT period in counts
 **********************************************************************************************************************/
static void r_agt_period_register_set (agt_instance_ctrl_t * p_instance_ctrl, uint32_t period_counts)
{
    /* Store the period value so it can be retrieved later. */
    p_instance_ctrl->period = period_counts;
    gp_prv_agt_periods[p_instance_ctrl->p_cfg->channel] = period_counts;

    uint16_t period_reg = (uint16_t) (period_counts - 1U);

#if AGT_CFG_OUTPUT_SUPPORT_ENABLE
    uint16_t duty_cycle_counts = 0U;
    if (TIMER_MODE_PERIODIC == p_instance_ctrl->p_cfg->mode)
    {
        duty_cycle_counts = (uint16_t) (period_counts >> 1);
    }
    else if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        duty_cycle_counts = period_reg;
    }
    else
    {
        /* Do nothing, duty cycle should not be updated in R_AGT_PeriodSet. */
    }

    if (TIMER_MODE_PWM != p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->AGTCMA = duty_cycle_counts;
        p_instance_ctrl->p_reg->AGTCMB = duty_cycle_counts;
    }
#endif

    /* Set counter to period minus one. */
    p_instance_ctrl->p_reg->AGT = period_reg;
}

/*******************************************************************************************************************//**
 * Obtains the clock frequency of AGT for all clock sources except AGT0 underflow, with divisor applied.
 *
 * @param[in]  p_agt_regs         Registers of AGT channel used
 *
 * @return Source clock frequency of AGT in Hz, divider applied.
 **********************************************************************************************************************/
static uint32_t r_agt_clock_frequency_get (R_AGT0_Type * p_agt_regs)
{
    uint32_t           clock_freq_hz    = 0U;
    uint8_t            count_source_int = p_agt_regs->AGTMR1_b.TCK;
    timer_source_div_t divider          = TIMER_SOURCE_DIV_1;
    if (0U == (count_source_int & (~AGT_SOURCE_CLOCK_PCLKB_BITS)))
    {
        /* Call CGC function to obtain current PCLKB clock frequency. */
        clock_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);

        /* If Clock source is PCLKB or derived from PCLKB */
        divider = (timer_source_div_t) count_source_int;
        if (0U != divider)
        {
            /* Set divider to 3 to divide by 8 when AGTMR1.TCK is 1 (PCLKB / 8). Set divider to 1 to divide by 2 when
             * AGTMR1.TCK is 3 (PCLKB / 2). XOR with 2 to convert 1 to 3 and 3 to 1. */
            divider ^= 2U;
        }
    }
    else
    {
        /* Else either fSUB clock or LOCO clock is used. The frequency is set to 32Khz (32768). This function does not
         * support AGT0 underflow as count source.  */
        clock_freq_hz = FSUB_FREQUENCY_HZ;

        divider = (timer_source_div_t) p_agt_regs->AGTMR2_b.CKS;
    }

    clock_freq_hz >>= divider;

    return clock_freq_hz;
}

/*********************************************************************************************************************
 * AGT counter underflow interrupt.
 **********************************************************************************************************************/
void agt_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    agt_instance_ctrl_t * p_instance_ctrl = (agt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Save AGTCR to determine the source of the interrupt. */
    uint32_t agtcr = p_instance_ctrl->p_reg->AGTCR;

    /* If the channel is configured to be one-shot mode, stop the timer. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
#if AGT_CFG_OUTPUT_SUPPORT_ENABLE

        /* Forcibly stopping the timer resets AGTCMSR, AGTCMA, and AGTCMB. AGTCMA and AGTCMB are based on the
         * timer period, but AGTCMSR must be saved so it can be restored. */
        uint8_t agtcmsr = p_instance_ctrl->p_reg->AGTCMSR;
#endif

        /* Stop timer */
        p_instance_ctrl->p_reg->AGTCR = AGT_PRV_AGTCR_FORCE_STOP;
        agtcr &= AGT_PRV_AGTCR_STATUS_FLAGS;

        /* Set counter to period minus one. */
        r_agt_period_register_set(p_instance_ctrl, p_instance_ctrl->period);

#if AGT_CFG_OUTPUT_SUPPORT_ENABLE

        /* Restore AGTCMSR. */
        p_instance_ctrl->p_reg->AGTCMSR = agtcmsr;
#endif
    }

    /* Invoke the callback function if it is set. */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        /* Setup parameters for the user-supplied callback function. */
        timer_callback_args_t callback_args;
        if (agtcr & R_AGT0_AGTCR_TUNDF_Msk)
        {
            callback_args.event = TIMER_EVENT_CYCLE_END;
        }

#if AGT_CFG_INPUT_SUPPORT_ENABLE
        else
        {
            callback_args.event = TIMER_EVENT_CAPTURE_A;
            uint32_t reload_value = p_instance_ctrl->period - 1U;
            callback_args.capture = reload_value - p_instance_ctrl->p_reg->AGT;

            /* The AGT counter is not reset in pulse width measurement mode. Reset it by software. Note that this
             * will restart the counter if a new capture has already started. Application writers must ensure that
             * this interrupt processing completes before the next capture begins. */
            if (AGT_PRV_AGTMR1_TMOD_PULSE_WIDTH == p_instance_ctrl->p_reg->AGTMR1_b.TMOD)
            {
                p_instance_ctrl->p_reg->AGT = (uint16_t) reload_value;
            }
            else
            {
                /* Period of input pulse = (initial value of counter [AGT register] - reading value of the read-out buffer) + 1
                 * Reference section 25.4.5 of the RA6M3 manual R01UH0886EJ0100. */
                callback_args.capture++;
            }
        }
#endif

        callback_args.p_context = p_instance_ctrl->p_cfg->p_context;
        p_instance_ctrl->p_cfg->p_callback(&callback_args);
    }

    /* Clear flags in AGTCR. */
    p_instance_ctrl->p_reg->AGTCR = (uint8_t) (agtcr & ~AGT_PRV_AGTCR_STATUS_FLAGS);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
