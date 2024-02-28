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
#include "r_tau.h"
#include "r_tau_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "TAU" in ASCII, used to determine if channel is open. */
#define TAU_OPEN                                            (0x00544155ULL)
#define TAU_CLOSE                                           (0U)

/* TAU Channel */
#define TAU_CH0                                             (0)
#define TAU_CH1                                             (1)
#define TAU_CH3                                             (3)
#define TAU_CH5                                             (5)
#define TAU_CH7                                             (7)

/* Delay cycles */
#define TAU_DELAY_2_CYCLE_FMCK                              (2U)

/* Shift to higher 8-bit mode channels */
#define TAU_BIT_MODE_HIGHER_8BIT_SHIFT                      (8U)

/* Mask 9 bit for lower mode timer 8-bit */
#define TAU_8BIT_MODE_MASK                                  (0x00FFU)

/* Mask 9 bit for higher mode timer 8-bit */
#define TAU_BIT_MODE_HIGHER_8BIT_MASK                       (0xFF00U)

/* These bitfield defines indicate which channels support a certain function */
#define TAU_DIVIDER_MODE_CAPABLE_CHANNEL_MASK               (1 << TAU_CH0)
#define TAU_8BIT_MODE_SUPPORT_CAPABLE_CHANNEL_MASK          ((1 << TAU_CH1) | (1 << TAU_CH3))
#define TAU_CK02_CK03_CAPABLE_CHANNELS_MASK                 ((1 << TAU_CH1) | (1 << TAU_CH3))
#define TAU_INPUT_RXD2_CAPABLE_CHANNEL_MASK                 (1 << TAU_CH7)
#define TAU_INPUT_CLOCK_CAPABLE_CHANNEL_MASK                (1 << TAU_CH5)
#define TAU_ELC_CAPABLE_CHANNELS_MASK                       ((1 << TAU_CH0) | (1 << TAU_CH1))

/* These bit fields are for the TS0 and TT0 registers. */
#define TAU_TS0_TT0_16BIT_MODE_MASK                         (0x0001)
#define TAU_TS0_TT0_HIGHER_8BIT_MODE_MASK                   (0x0100)
#define TAU_TS0_TT0_LOWER_8BIT_MODE_MASK                    (0x0001)
#define TAU_TS0_TT0_HIGHER_LOWER_8BIT_MODE_MASK             (0x0101)

/* Setting low level measurement and high level measurement */
#define TAU_INPUT_LOW_LEVEL_MEASUREMENT_SETTING             (0x02)
#define TAU_INPUT_HIGH_LEVEL_MEASUREMENT_SETTING            (0x03)

/* Used for checking maximum period count in 16-bit mode (1 to 65536) */
#define TAU_MAXIMUM_16BIT_TIMER_MODE                        (65536)

/* Used for checking maximum period count in 8-bit mode (1 to 256) */
#define TAU_MAXIMUM_8BIT_TIMER_MODE                         (256)

/* Used for checking maximum divider value with both edge (1 to 65536) */
#define TAU_MAXIMUM_BOTH_EDGE_DIVIDER_FUNCTION              (65536)

/* Used for checking maximum divider value with falling or rising edge (2 to 131072) */
#define TAU_MAXIMUM_FALLING_RISING_EDGE_DIVIDER_FUNCTION    (131072)

/* Convert to micro second */
#define TAU_CONVERT_TO_MICRO_SECOND                         (1000000U)

/* Timer TDR overflow value */
#define TAU_TDR_OVF_VALUE                                   (0x10000UL)

/* Operation clock CK00, CK01 Mask */
#define TAU_OPERATION_CLOCK_CK00_CK01_MASK                  (0x0FU)

/* Operation clock CK02, CK03 Mask */
#define TAU_OPERATION_CLOCK_CK02_CK03_MASK                  (0x03U)

/* The number of available functions. */
#define TAU_FUNCTIONS_COUNT                                 (8)

#define TAU_TDR_WRITE_MSK_BY_TIMER_MODE                     (0x8FU)
#define TAU_SUPPORT_8BIT_MSK_BY_TIMER_MODE                  (0x87U)
#define TAU_TDR_MASK                                        (0xFFFFU)

/* Use for functions which support output pin */
#define TAU_FUNCTION_SUPPORTED_OUTPUT_MASK                  (0x0AU)

/* Use for functions which support input pin */
#define TAU_FUNCTION_SUPPORTED_INPUT_MASK                   (0xFCU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Timer Mode */
typedef enum e_tau_timer_mode
{
    TAU_TIMER_MODE_INTERVAL              = 0, ///< Interval timer mode
    TAU_TIMER_MODE_CAPTURE               = 2, ///< Capture timer mode
    TAU_TIMER_MODE_EVENT_COUNTER         = 3, ///< Event counter timer mode
    TAU_TIMER_MODE_ONE_COUNT             = 4, ///< One count timer mode
    TAU_TIMER_MODE_CAPTURE_AND_ONE_COUNT = 6, ///< Capture and one-count mode
} tau_timer_mode_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static fsp_err_t r_tau_config_set(tau_instance_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);
static fsp_err_t r_tau_cnt_set(tau_instance_ctrl_t * const p_ctrl, uint32_t period_counts, uint32_t period_8bit_counts);

#if TAU_CFG_INPUT_SUPPORT_ENABLE
static void r_tau_wait_time(tau_instance_ctrl_t * const p_ctrl, uint32_t delay_cycles);
static void r_tau_config_input_set(tau_instance_ctrl_t * const p_ctrl);

#endif

#if TAU_CFG_OUTPUT_SUPPORT_ENABLE
static void r_tau_config_output_set(tau_instance_ctrl_t * const p_ctrl);

#endif

static uint32_t r_tau_clock_frequency_get(tau_instance_ctrl_t * const p_instance_ctrl);

#if TAU_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_tau_open_param_checking(tau_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg);
static fsp_err_t r_tau_cnt_check(tau_instance_ctrl_t * const p_ctrl, uint32_t period_counts,
                                 uint32_t period_8bit_counts);

#endif

static void r_tau_disable_irq(IRQn_Type irq);

static void r_tau_enable_irq(IRQn_Type const irq, uint32_t priority, void * p_context);

static void r_tau_operation_clock_set(tau_operation_ck_t operation_clock, timer_source_div_t source_div);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void tau_tmi_isr(void);
void tau_tmih_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Look-up table for mapping timer function and timer mode, index to this table is defined
 * by the tau_function_t enum */
static const uint16_t tau_func_setting_lut[TAU_FUNCTIONS_COUNT] =
{
    /* This setting supports to interval timer function */
    [TAU_FUNCTION_INTERVAL] =
        (TAU_TIMER_MODE_INTERVAL << R_TAU_TMR0_MD_Pos) |              ///< Setting interval timer mode.
        (0 << R_TAU_TMR0_STS_Pos) |                                   ///< Only software start.
        (0 << R_TAU_TMR0_CCS_Pos),                                    ///< Operation clock (fMCK).

    /* This setting supports to square wave output function */
    [TAU_FUNCTION_SQUARE_WAVE] =
        (TAU_TIMER_MODE_INTERVAL << R_TAU_TMR0_MD_Pos) |              ///< Setting interval timer mode.
        (0 << R_TAU_TMR0_STS_Pos) |                                   ///< Only software start.
        (0 << R_TAU_TMR0_CCS_Pos),                                    ///< Operation clock (fMCK).

    /* This setting supports to external event count function */
    [TAU_FUNCTION_EXTERNAL_EVENT_COUNT] =
        (TAU_TIMER_MODE_EVENT_COUNTER << R_TAU_TMR0_MD_Pos) |         ///< Setting event count mode.
        (0 << R_TAU_TMR0_STS_Pos) |                                   ///< Only software start.
        (1 << R_TAU_TMR0_CCS_Pos),                                    ///< The TI0n pin input valid edge.

    /* This setting supports to divider function */
    [TAU_FUNCTION_DIVIDER] =
        (TAU_TIMER_MODE_INTERVAL << R_TAU_TMR0_MD_Pos) |              ///< Setting interval timer mode.
        (0 << R_TAU_TMR0_STS_Pos) |                                   ///< Only software start.
        (1 << R_TAU_TMR0_CCS_Pos),                                    ///< The TI0n pin input valid edge.

    /* This setting supports to input pulse measurement function */
    [TAU_FUNCTION_INPUT_PULSE_INTERVAL_MEASUREMENT] =
        (TAU_TIMER_MODE_CAPTURE << R_TAU_TMR0_MD_Pos) |               ///< Setting capture mode.
        (1 << R_TAU_TMR0_STS_Pos) |                                   ///< The TI0n pin input valid edge.
        (0 << R_TAU_TMR0_CCS_Pos),                                    ///< Operation clock (fMCK).

    /* This setting supports to low level width measurement function */
    [TAU_FUNCTION_LOW_LEVEL_WIDTH_MEASUREMENT] =
        (TAU_TIMER_MODE_CAPTURE_AND_ONE_COUNT << R_TAU_TMR0_MD_Pos) | ///< Setting capture & one-count mode.
        (2 << R_TAU_TMR0_STS_Pos) |                                   ///< The TI0n pin input valid edges.
        (0 << R_TAU_TMR0_CCS_Pos),                                    ///< Operation clock (fMCK).

    /* This setting supports to high level width measurement function */
    [TAU_FUNCTION_HIGH_LEVEL_WIDTH_MEASUREMENT] =
        (TAU_TIMER_MODE_CAPTURE_AND_ONE_COUNT << R_TAU_TMR0_MD_Pos) | ///< Setting capture & one-count mode.
        (2 << R_TAU_TMR0_STS_Pos) |                                   ///< The TI0n pin input valid edges.
        (0 << R_TAU_TMR0_CCS_Pos),                                    ///< Operation clock (fMCK).

    /* This setting supports to delay count function */
    [TAU_FUNCTION_DELAY_COUNT] =
        (TAU_TIMER_MODE_ONE_COUNT << R_TAU_TMR0_MD_Pos) |             ///< Setting one-count mode.
        (1 << R_TAU_TMR0_STS_Pos) |                                   ///< The TI0n pin input valid edge.
        (0 << R_TAU_TMR0_CCS_Pos)                                     ///< Operation clock (fMCK).
};

/* Look-up table for bit mode channel  */
static const uint16_t channel_bitmode_lut[] =
{
    [TAU_BIT_MODE_16BIT]             = TAU_TS0_TT0_16BIT_MODE_MASK,
    [TAU_BIT_MODE_HIGHER_8BIT]       = TAU_TS0_TT0_HIGHER_8BIT_MODE_MASK,
    [TAU_BIT_MODE_LOWER_8BIT]        = TAU_TS0_TT0_LOWER_8BIT_MODE_MASK,
    [TAU_BIT_MODE_HIGHER_LOWER_8BIT] = TAU_TS0_TT0_HIGHER_LOWER_8BIT_MODE_MASK
};

/* Look-up table for operation clock CK02, CK03 */
static const uint8_t operation_clock_ck02_ck03_lut[] =
{
    [TIMER_SOURCE_DIV_2]     = 0,
    [TIMER_SOURCE_DIV_4]     = 1,
    [TIMER_SOURCE_DIV_16]    = 2,
    [TIMER_SOURCE_DIV_64]    = 3,
    [TIMER_SOURCE_DIV_256]   = 0,
    [TIMER_SOURCE_DIV_1024]  = 1,
    [TIMER_SOURCE_DIV_4096]  = 2,
    [TIMER_SOURCE_DIV_16384] = 3
};

static const uint8_t prs0_offset_lut[] =
{
    [TAU_OPERATION_CK00] = 0,
    [TAU_OPERATION_CK01] = 4,
    [TAU_OPERATION_CK02] = 8,
    [TAU_OPERATION_CK03] = 12,
};

/* TAU implementation of timer interface  */
const timer_api_t g_timer_on_tau =
{
    .open         = R_TAU_Open,
    .stop         = R_TAU_Stop,
    .start        = R_TAU_Start,
    .reset        = R_TAU_Reset,
    .enable       = R_TAU_Enable,
    .disable      = R_TAU_Disable,
    .periodSet    = R_TAU_PeriodSet,
    .dutyCycleSet = R_TAU_DutyCycleSet,
    .infoGet      = R_TAU_InfoGet,
    .statusGet    = R_TAU_StatusGet,
    .callbackSet  = R_TAU_CallbackSet,
    .close        = R_TAU_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup TAU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the timer module and applies configurations. Implements @ref timer_api_t::open.
 *
 * The TAU implementation of the general timer can accept a tau_extended_cfg_t extension parameter.
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL or the period is not in the valid range
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_INVALID_CHANNEL        The channel does not support this feature.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       Timer_cfg_t::p_callback is not NULL, but ISR is not enabled.
 *                                        ISR must be enabled to use callback
 * @retval FSP_ERR_INVALID_MODE           Invalid configuration for p_extend.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_TAU_Open (timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = FSP_SUCCESS;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ASSERT(NULL != p_instance_ctrl);
#endif

    p_instance_ctrl->channel_mask = (uint16_t) (1U << p_cfg->channel);

#if TAU_CFG_PARAM_CHECKING_ENABLE
    err = r_tau_open_param_checking(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    p_instance_ctrl->p_cfg      = p_cfg;
    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->p_context  = p_cfg->p_context;

    /* Enable the TAU channel and reset the registers to their initial state. */
    R_BSP_MODULE_START(FSP_IP_TAU, p_cfg->channel);

    /* Set the TAU configuration settings provided in ::tau_cfg_t and :: tau_extended_cfg_t. */
    err = r_tau_config_set(p_ctrl, p_cfg);

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    r_tau_enable_irq(p_cfg->cycle_end_irq, p_cfg->cycle_end_ipl, p_instance_ctrl);

    r_tau_enable_irq(((tau_extended_cfg_t *) p_cfg->p_extend)->higher_8bit_cycle_end_irq,
                     ((tau_extended_cfg_t *) p_cfg->p_extend)->higher_8bit_cycle_end_ipl, p_instance_ctrl);

    p_instance_ctrl->open = TAU_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Stops timer. Implements @ref timer_api_t::stop.
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_Stop
 *
 * @retval FSP_SUCCESS                 Timer successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_Stop (timer_ctrl_t * const p_ctrl)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    R_TAU->TT0 = (uint16_t) (channel_bitmode_lut[p_extend->bit_mode] << p_instance_ctrl->p_cfg->channel);

#if TAU_CFG_OUTPUT_SUPPORT_ENABLE
    if (TAU_PIN_OUTPUT_CFG_DISABLED != p_extend->initial_output)
    {
        R_TAU->TOE0 &= (uint16_t) (~(p_instance_ctrl->channel_mask));
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts timer. Implements @ref timer_api_t::start.
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_Start
 *
 * @retval FSP_SUCCESS                 Timer successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_Start (timer_ctrl_t * const p_ctrl)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t              channel  = p_instance_ctrl->p_cfg->channel;

#if TAU_CFG_OUTPUT_SUPPORT_ENABLE
    if (TAU_PIN_OUTPUT_CFG_DISABLED != p_extend->initial_output)
    {
        R_TAU->TOE0 |= p_instance_ctrl->channel_mask;
    }
#endif

    /* Start timer */
    R_TAU->TS0 =
        (uint16_t) ((channel_bitmode_lut[p_extend->bit_mode] << channel));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter value to the period minus one. Input Pulse Function is reset counter value to 0.
 * Implements @ref timer_api_t::reset.
 *
 * @note This function can not reset the counter when counter is stopped,
 * and function High/Low Measurement Function is used.
 *
 * @retval FSP_SUCCESS                 The counter value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_Reset (timer_ctrl_t * const p_ctrl)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend      = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint16_t             timer_channel =
        (uint16_t) (channel_bitmode_lut[p_extend->bit_mode] << p_instance_ctrl->p_cfg->channel);

    if (0 < (timer_channel & R_TAU->TE0))
    {
        /* Stop counting. */
        R_TAU->TT0 = timer_channel;

        /* Start counting again. */
        R_TAU->TS0 = timer_channel;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables external event triggers that start, stop, clear, or capture the counter. Implements @ref timer_api_t::enable.
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_Enable
 *
 * @retval FSP_SUCCESS                 External events successfully enabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_Enable (timer_ctrl_t * const p_ctrl)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Start counting. */
    R_TAU->TS0 =
        (uint16_t) ((channel_bitmode_lut[p_extend->bit_mode] << p_instance_ctrl->p_cfg->channel));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables external event triggers that start, stop, clear, or capture the counter.
 * Implements @ref timer_api_t::disable.
 * @note The timer could be running after R_TAU_Disable(). To ensure it is stopped, call R_TAU_Stop().
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_Disable
 *
 * @retval FSP_SUCCESS                 External events successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_Disable (timer_ctrl_t * const p_ctrl)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Stop counting. */
    R_TAU->TT0 =
        (uint16_t) ((channel_bitmode_lut[p_extend->bit_mode] << p_instance_ctrl->p_cfg->channel));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets period value provided. If the timer is running, the period will be updated after the next counter underflow.
 * If the timer is stopped, this function resets the counter and updates the period.
 * This Function is not supported for Input pulse Function, High-Low Measurement Function.
 * Implements @ref timer_api_t::periodSet.
 *
 * @note if timer mode is Lower and Higher 8-bit Timer Mode, the last 9 bits are the lower 8-bits of the timer,
 * and the subsequent 9 bits are the higher 8-bits of the timer
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_PeriodSet
 *
 * @retval FSP_SUCCESS                 Period value written successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL or period is invalid range.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_UNSUPPORTED         Unsupported for Input pulse Function, High-Low Measurement Function
 **********************************************************************************************************************/
fsp_err_t R_TAU_PeriodSet (timer_ctrl_t * const p_ctrl, uint32_t const period_counts)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    if ((1U << p_extend->tau_func) & TAU_TDR_WRITE_MSK_BY_TIMER_MODE)
    {
        uint32_t period_higher = period_counts;
        uint32_t period        = period_counts;

        if (TAU_BIT_MODE_HIGHER_LOWER_8BIT == p_extend->bit_mode)
        {
            uint32_t tdr = period_counts - 1;
            period        = (uint32_t) ((tdr & TAU_8BIT_MODE_MASK) + 1);
            period_higher = (uint32_t)
                            (((tdr >> TAU_BIT_MODE_HIGHER_8BIT_SHIFT) & TAU_8BIT_MODE_MASK) + 1);
        }

        r_tau_cnt_set(p_instance_ctrl, period, period_higher);
    }
    else
    {

        /* Input Pulse Function and High-Low Measurement Function are not supported for this function */
        return FSP_ERR_UNSUPPORTED;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref timer_api_t::dutyCycleSet is not supported on the R_TAU Independent channels.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_TAU_DutyCycleSet (timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(duty_cycle_counts);
    FSP_PARAMETER_NOT_USED(pin);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Get timer information and store it in provided pointer p_info. Implements @ref timer_api_t::infoGet.
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_InfoGet
 *
 * @retval FSP_SUCCESS                 Period, count direction, frequency, and ELC event written to caller's
 *                                     structure successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_info was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_InfoGet (timer_ctrl_t * const p_ctrl, timer_info_t * const p_info)
{
    tau_instance_ctrl_t   * p_instance_ctrl      = (tau_instance_ctrl_t *) p_ctrl;
    const timer_direction_t function_direction[] =
    {
        TIMER_DIRECTION_DOWN, TIMER_DIRECTION_DOWN, TIMER_DIRECTION_DOWN,
        TIMER_DIRECTION_DOWN, TIMER_DIRECTION_UP,   TIMER_DIRECTION_UP,  TIMER_DIRECTION_UP,
        TIMER_DIRECTION_DOWN
    };
#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get and store period */
    p_info->period_counts = (uint32_t) (R_TAU->TDR0[p_instance_ctrl->p_cfg->channel].TDR0n) + 1;

    /* Get and store clock counting direction. Read count direction setting */
    p_info->count_direction =
        function_direction[((tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->tau_func];

    /* Get and store clock frequency */
    p_info->clock_frequency = r_tau_clock_frequency_get(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current timer status and store it in provided pointer p_status. Implements @ref timer_api_t::statusGet.
 *
 * Example:
 * @snippet r_tau_example.c R_TAU_StatusGet
 *
 * @retval FSP_SUCCESS                 Current timer state and counter value set successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_StatusGet (timer_ctrl_t * const p_ctrl, timer_status_t * const p_status)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    p_status->state = TIMER_STATE_STOPPED;
    uint8_t channel = p_instance_ctrl->p_cfg->channel;

    /* Get counter state for higher 8-bit mode, lower 8-bit mode, higher-lower 8-bit mode or 16-bit mode. */
    p_status->state = (((channel_bitmode_lut[p_extend->bit_mode] << channel) &
                        R_TAU->TE0) > 0 ? TIMER_STATE_COUNTING : TIMER_STATE_STOPPED);

    /* Get counter value */
    p_status->counter = R_TAU->TCR0[channel];

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
fsp_err_t R_TAU_CallbackSet (timer_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(timer_callback_args_t *),
                             void const * const            p_context,
                             timer_callback_args_t * const p_callback_memory)
{
    tau_instance_ctrl_t * p_ctrl = (tau_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_callback_memory);

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(TAU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops counter, disables output pins, and clears internal driver data. Implements @ref timer_api_t::close.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_TAU_Close (timer_ctrl_t * const p_ctrl)
{
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) p_ctrl;

#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(TAU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Mark driver as closed */
    p_instance_ctrl->open = TAU_CLOSE;
    uint8_t channel = p_instance_ctrl->p_cfg->channel;

    R_TAU->TT0 =
        (uint16_t) ((channel_bitmode_lut[p_extend->bit_mode] << channel));

#if TAU_CFG_OUTPUT_SUPPORT_ENABLE
    if (TAU_PIN_OUTPUT_CFG_DISABLED != p_extend->initial_output)
    {
        R_TAU->TOE0 &= (uint16_t) (~(p_instance_ctrl->channel_mask));
    }
#endif

    /* Disable interrupts. */
    r_tau_disable_irq(p_instance_ctrl->p_cfg->cycle_end_irq);
    r_tau_disable_irq(p_extend->higher_8bit_cycle_end_irq);

    /* Return the error code */
    return FSP_SUCCESS;
}

/** @} (end addtogroup TAU) */

#if TAU_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking for R_TAU_Open.
 *
 * @param[in]  p_instance_ctrl         Pointer to instance control structure.
 * @param[in]  p_cfg                   Configuration structure for this instance
 *
 * @retval FSP_SUCCESS                 Initialization was successful and timer has started.
 * @retval FSP_ERR_ALREADY_OPEN        R_TAU_Open has already been called for this p_ctrl.
 * @retval FSP_ERR_INVALID_CHANNEL     The channel does not support this feature.
 * @retval FSP_ERR_INVALID_MODE        Invalid configuration for p_extend.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    Timer_cfg_t::p_callback is not NULL, but ISR is not enabled.
 *                                     ISR must be enabled to use callback
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel number is not available on TAU.
 **********************************************************************************************************************/
static fsp_err_t r_tau_open_param_checking (tau_instance_ctrl_t * p_instance_ctrl, timer_cfg_t const * const p_cfg)
{
    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_cfg->p_extend;

    FSP_ERROR_RETURN(TAU_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Enable IRQ if user supplied a callback function */
    if (NULL != p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(p_cfg->cycle_end_irq >= 0 ||
                         (TAU_BIT_MODE_HIGHER_8BIT == p_extend->bit_mode),
                         FSP_ERR_IRQ_BSP_DISABLED);

        FSP_ERROR_RETURN(p_extend->higher_8bit_cycle_end_irq >= 0 ||
                         (TAU_BIT_MODE_16BIT == p_extend->bit_mode) ||
                         ((TAU_BIT_MODE_LOWER_8BIT == p_extend->bit_mode)),
                         FSP_ERR_IRQ_BSP_DISABLED);
    }

    FSP_ERROR_RETURN((p_instance_ctrl->channel_mask & BSP_FEATURE_TAU_VALID_CHANNEL_MASK),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Divider Function is only available in channel 0 */
    FSP_ERROR_RETURN((TAU_FUNCTION_DIVIDER != p_extend->tau_func) ||
                     (p_instance_ctrl->channel_mask & TAU_DIVIDER_MODE_CAPABLE_CHANNEL_MASK),
                     FSP_ERR_INVALID_CHANNEL);

    /* Higher 8-bit timer, lower 8-bit timer, Higher and lower 8-bit timer are available in channel 1 and 3 */
    FSP_ERROR_RETURN((TAU_BIT_MODE_16BIT == p_extend->bit_mode) ||
                     (p_instance_ctrl->channel_mask & TAU_8BIT_MODE_SUPPORT_CAPABLE_CHANNEL_MASK),
                     FSP_ERR_INVALID_CHANNEL);

    if ((TAU_OPERATION_CK02 == p_extend->operation_clock) || (TAU_OPERATION_CK03 == p_extend->operation_clock))
    {
        /* CK02, CK03 are only available in channels 1 and 3 */
        FSP_ERROR_RETURN(p_instance_ctrl->channel_mask & TAU_CK02_CK03_CAPABLE_CHANNELS_MASK, FSP_ERR_INVALID_CHANNEL);

        /* Checking invalid clock source for operation clock CK02 */
        FSP_ERROR_RETURN((TAU_OPERATION_CK02 != p_extend->operation_clock) ||
                         (TIMER_SOURCE_DIV_2 == p_cfg->source_div) ||
                         (TIMER_SOURCE_DIV_4 == p_cfg->source_div) ||
                         (TIMER_SOURCE_DIV_16 == p_cfg->source_div) ||
                         (TIMER_SOURCE_DIV_64 == p_cfg->source_div),
                         FSP_ERR_INVALID_MODE);

        /* Checking invalid clock source for operation clock CK03 */
        FSP_ERROR_RETURN((TAU_OPERATION_CK03 != p_extend->operation_clock) ||
                         (TIMER_SOURCE_DIV_256 == p_cfg->source_div) ||
                         (TIMER_SOURCE_DIV_1024 == p_cfg->source_div) ||
                         (TIMER_SOURCE_DIV_4096 == p_cfg->source_div) ||
                         (TIMER_SOURCE_DIV_16384 == p_cfg->source_div),
                         FSP_ERR_INVALID_MODE);
    }
    else
    {
        /* Higher 8-bit timer, lower 8-bit timer, Higher and lower 8-bit timer are available when
         * the "Operation Clock" is set to CK02 or CK03 */
        FSP_ERROR_RETURN(TAU_BIT_MODE_16BIT == p_extend->bit_mode, FSP_ERR_INVALID_MODE);
    }

 #if TAU_CFG_INPUT_SUPPORT_ENABLE
    if ((1 << p_extend->tau_func) & TAU_FUNCTION_SUPPORTED_INPUT_MASK)
    {
        /* Input source is different to No input signal When this function used input pin */
        FSP_ERROR_RETURN((TAU_INPUT_SOURCE_NONE != p_extend->input_source), FSP_ERR_INVALID_MODE)

        /* Input signal of RXD2 is only available in channels 7 */
        FSP_ERROR_RETURN((TAU_INPUT_SOURCE_RXD2_PIN != p_extend->input_source) ||
                         (p_instance_ctrl->channel_mask & TAU_INPUT_RXD2_CAPABLE_CHANNEL_MASK),
                         FSP_ERR_INVALID_CHANNEL);

        /* Input signal of the RXD2 pin is only available in Input Pulse and
         * High-Low Level Pulse Width Measure Function */
        FSP_ERROR_RETURN((TAU_INPUT_SOURCE_RXD2_PIN != p_extend->input_source) ||
                         (TAU_FUNCTION_INPUT_PULSE_INTERVAL_MEASUREMENT == p_extend->tau_func) ||
                         (TAU_FUNCTION_LOW_LEVEL_WIDTH_MEASUREMENT == p_extend->tau_func) ||
                         (TAU_FUNCTION_HIGH_LEVEL_WIDTH_MEASUREMENT == p_extend->tau_func),
                         FSP_ERR_INVALID_MODE);

        /* Input signal of MOCO, LOCO, FSUB are only available in channels 5 */
        FSP_ERROR_RETURN((TAU_INPUT_SOURCE_MOCO > p_extend->input_source) ||
                         (TAU_INPUT_SOURCE_FSUB < p_extend->input_source) ||
                         (p_instance_ctrl->channel_mask & TAU_INPUT_CLOCK_CAPABLE_CHANNEL_MASK),
                         FSP_ERR_INVALID_CHANNEL);

        /* ELC input source is only available in channels 0 and 1 */
        FSP_ERROR_RETURN((TAU_INPUT_SOURCE_ELC != p_extend->input_source) ||
                         (p_instance_ctrl->channel_mask & TAU_ELC_CAPABLE_CHANNELS_MASK),
                         FSP_ERR_INVALID_CHANNEL);

        /* The noise filter should be disabled when ELC signal is selected as an input signal */
        FSP_ERROR_RETURN((TAU_INPUT_SOURCE_ELC != p_extend->input_source) ||
                         (TAU_INPUT_NOISE_FILTER_DISABLE == p_extend->tau_filter),
                         FSP_ERR_INVALID_MODE);

        /* ELC input source is only available External Event Counter, Input Pulse, and Delay Counter Function */
        FSP_ERROR_RETURN((TAU_INPUT_SOURCE_ELC != p_extend->input_source) ||
                         (TAU_FUNCTION_EXTERNAL_EVENT_COUNT == p_extend->tau_func) ||
                         (TAU_FUNCTION_INPUT_PULSE_INTERVAL_MEASUREMENT == p_extend->tau_func) ||
                         (TAU_FUNCTION_DELAY_COUNT == p_extend->tau_func),
                         FSP_ERR_INVALID_MODE);
    }
 #endif

 #if TAU_CFG_OUTPUT_SUPPORT_ENABLE
    if ((1 << p_extend->tau_func) & TAU_FUNCTION_SUPPORTED_OUTPUT_MASK)
    {
        /* Initial Output should not be disabled when function uses output pin */
        FSP_ERROR_RETURN(TAU_PIN_OUTPUT_CFG_DISABLED != p_extend->initial_output, FSP_ERR_INVALID_MODE);
    }
 #endif

    if ((1U << p_extend->tau_func) & TAU_SUPPORT_8BIT_MSK_BY_TIMER_MODE)
    {
        /* Higher-Lower 8 and higher 8-bit timer are available in Interval Timer function */
        FSP_ERROR_RETURN(((TAU_BIT_MODE_HIGHER_LOWER_8BIT != p_extend->bit_mode) &&
                          (TAU_BIT_MODE_HIGHER_8BIT != p_extend->bit_mode)) ||
                         (TAU_FUNCTION_INTERVAL == p_extend->tau_func),
                         FSP_ERR_INVALID_MODE);
    }
    else
    {
        /* This function is not supported for 8-bit mode */
        FSP_ERROR_RETURN(TAU_BIT_MODE_16BIT == p_extend->bit_mode, FSP_ERR_INVALID_MODE);
    }

    tau_timer_mode_t mode_timer =
        (tau_timer_mode_t) ((tau_func_setting_lut[p_extend->tau_func] & R_TAU_TMR0_MD_Msk) >> R_TAU_TMR0_MD_Pos);

    if ((TAU_TIMER_MODE_CAPTURE_AND_ONE_COUNT == mode_timer) || (TAU_TIMER_MODE_EVENT_COUNTER == mode_timer))
    {
        /* Bit opirq should be 0 when Event counter mode or Capture & one-count mode is selected */
        FSP_ERROR_RETURN(TAU_INTERRUPT_OPIRQ_BIT_RESET == p_extend->opirq, FSP_ERR_INVALID_MODE);

        /* Trigger Edge Both is supported Measure Low Level Pulse Width and Measure High Level Pulse Width */
        if (TAU_TIMER_MODE_CAPTURE_AND_ONE_COUNT == mode_timer)
        {
            FSP_ERROR_RETURN(TAU_TRIGGER_EDGE_BOTH == p_extend->trigger_edge, FSP_ERR_INVALID_MODE);
        }
    }

    return FSP_SUCCESS;
}

#endif

#if TAU_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking valid range of period.
 *
 * @param[in]  p_ctrl                Pointer to TAU control structure
 * @param[in]  period_counts         Current timer period
 * @param[in]  period_8bit_counts     Current higher 8-bit timer period
 *
 * @retval FSP_SUCCESS                 Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION           The period is not in the valid range
 **********************************************************************************************************************/
static fsp_err_t r_tau_cnt_check (tau_instance_ctrl_t * const p_ctrl,
                                  uint32_t                    period_counts,
                                  uint32_t                    period_8bit_counts)
{
    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint32_t min_timer = 1;
    uint32_t max_timer = TAU_MAXIMUM_16BIT_TIMER_MODE;

    /* Checking range of each function */
    switch (p_extend->tau_func)
    {
        case TAU_FUNCTION_INTERVAL:
        case TAU_FUNCTION_SQUARE_WAVE:
        {
            if (TIMER_SOURCE_DIV_1 == p_ctrl->p_cfg->source_div)
            {
                min_timer = 2;
            }

            if (TAU_BIT_MODE_16BIT != p_extend->bit_mode)
            {
                max_timer = TAU_MAXIMUM_8BIT_TIMER_MODE;
            }

            break;
        }

        case TAU_FUNCTION_DIVIDER:
        {
            if (TAU_TRIGGER_EDGE_BOTH == p_extend->trigger_edge)
            {
                max_timer = TAU_MAXIMUM_BOTH_EDGE_DIVIDER_FUNCTION;
            }
            else
            {
                max_timer = TAU_MAXIMUM_FALLING_RISING_EDGE_DIVIDER_FUNCTION;
                min_timer = 2;
            }

            break;
        }

        case TAU_FUNCTION_EXTERNAL_EVENT_COUNT:
        case TAU_FUNCTION_DELAY_COUNT:
        {
            if (TAU_BIT_MODE_16BIT != p_extend->bit_mode)
            {
                max_timer = TAU_MAXIMUM_8BIT_TIMER_MODE;
            }

            break;
        }

        default:
        {
            break;
        }
    }

    if ((1U << p_extend->tau_func) & TAU_TDR_WRITE_MSK_BY_TIMER_MODE)
    {
        if (TAU_BIT_MODE_HIGHER_8BIT != p_extend->bit_mode)
        {
            FSP_ASSERT(max_timer >= period_counts);
            FSP_ASSERT(min_timer <= period_counts);
        }

        if ((TAU_BIT_MODE_HIGHER_8BIT == p_extend->bit_mode) ||
            (TAU_BIT_MODE_HIGHER_LOWER_8BIT == p_extend->bit_mode))
        {
            FSP_ASSERT(max_timer >= period_8bit_counts);
            FSP_ASSERT(min_timer <= period_8bit_counts);
        }
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Configures TAU related registers based on user configurations.
 *
 * @param[in]     p_ctrl               Pointer to TAU control structure
 * @param[in]     p_cfg                Pointer to TAU specific configuration structure
 *
 * @retval FSP_SUCCESS                 Initialization was successful and timer has started.
 * @retval FSP_ERR_ASSERTION           The period is not in the valid range.
 **********************************************************************************************************************/
static fsp_err_t r_tau_config_set (tau_instance_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg)
{
    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_cfg->p_extend;

    uint16_t tmr_split = (uint16_t) ((p_extend->bit_mode == TAU_BIT_MODE_16BIT) ? 0U : R_TAU_TMR0_MASTER_SPLIT_Msk);

    /* Setting Function timer */
    uint16_t tmr = ((uint16_t) (p_extend->operation_clock << R_TAU_TMR0_CKS_Pos) |
                    (uint16_t) (p_extend->opirq << R_TAU_TMR0_OPIRQ_Pos) |
                    tmr_split | tau_func_setting_lut[p_extend->tau_func]);

#if TAU_CFG_INPUT_SUPPORT_ENABLE

    /* Setting trigger edge */
    if ((1 << p_extend->tau_func) & TAU_FUNCTION_SUPPORTED_INPUT_MASK)
    {
        if (TAU_FUNCTION_LOW_LEVEL_WIDTH_MEASUREMENT == p_extend->tau_func)
        {
            tmr |= (uint16_t) (TAU_INPUT_LOW_LEVEL_MEASUREMENT_SETTING << R_TAU_TMR0_CIS_Pos);
        }
        else if (TAU_FUNCTION_HIGH_LEVEL_WIDTH_MEASUREMENT == p_extend->tau_func)
        {
            tmr |= (uint16_t) (TAU_INPUT_HIGH_LEVEL_MEASUREMENT_SETTING << R_TAU_TMR0_CIS_Pos);
        }
        else
        {
            tmr |= (uint16_t) (p_extend->trigger_edge << R_TAU_TMR0_CIS_Pos);
        }

        r_tau_config_input_set(p_ctrl);
    }
#endif

    r_tau_operation_clock_set(p_extend->operation_clock, p_cfg->source_div);

    /* Setting Timer Mode register */
    R_TAU->TMR0[p_ctrl->p_cfg->channel] = tmr;

    fsp_err_t err = r_tau_cnt_set(p_ctrl, p_cfg->period_counts, p_extend->period_higher_8bit_counts);

#if TAU_CFG_OUTPUT_SUPPORT_ENABLE
    r_tau_config_output_set(p_ctrl);
#endif

    return err;
}

/*******************************************************************************************************************//**
 * Configures operation clock for TAU based on user configurations.
 *
 * @param[in]     operation_clock  Operation clock
 * @param[in]     source_div       Clock Divier
 **********************************************************************************************************************/
static void r_tau_operation_clock_set (tau_operation_ck_t operation_clock, timer_source_div_t source_div)
{
    uint8_t prs_offset = prs0_offset_lut[operation_clock];
    uint8_t prs_mask   = TAU_OPERATION_CLOCK_CK00_CK01_MASK;
    uint8_t prs_value  = (uint8_t) source_div;

    if ((operation_clock == TAU_OPERATION_CK02) || (operation_clock == TAU_OPERATION_CK03))
    {
        prs_mask  = TAU_OPERATION_CLOCK_CK02_CK03_MASK;
        prs_value = operation_clock_ck02_ck03_lut[source_div];
    }

    uint16_t tps0_value = R_TAU->TPS0;

    tps0_value &= (uint16_t) ~(prs_mask << prs_offset);
    tps0_value |= (prs_value << prs_offset);

    R_TAU->TPS0 = tps0_value;
}

#if TAU_CFG_INPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Configures input source of TAU related registers based on user configurations.
 *
 * @param[in]     p_ctrl               Pointer to TAU control structure
 **********************************************************************************************************************/
static void r_tau_config_input_set (tau_instance_ctrl_t * const p_ctrl)
{
    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    uint8_t              tnfen    = R_PORGA->TNFEN;
    tnfen         &= (uint8_t) (~p_ctrl->channel_mask);
    tnfen         |= (uint8_t) (p_extend->tau_filter << p_ctrl->p_cfg->channel);
    R_PORGA->TNFEN = tnfen;

    if (p_ctrl->channel_mask & TAU_INPUT_RXD2_CAPABLE_CHANNEL_MASK)
    {
        uint8_t isc_value = R_PORGA->ISC;
        isc_value &= (uint8_t) (~R_PORGA_ISC_ISC1_Msk);

        if (TAU_INPUT_SOURCE_RXD2_PIN == p_extend->input_source)
        {
            isc_value |= R_PORGA_ISC_ISC1_Msk;
        }

        R_PORGA->ISC = isc_value;
    }

    if (p_ctrl->channel_mask & TAU_ELC_CAPABLE_CHANNELS_MASK)
    {
        uint8_t tis1_value = R_PORGA->TIS1;
        tis1_value &= (uint8_t) (~p_ctrl->channel_mask);

        if (TAU_INPUT_SOURCE_ELC == p_extend->input_source)
        {
            tis1_value |= (1 << p_ctrl->p_cfg->channel);
        }

        R_PORGA->TIS1 = tis1_value;
    }

    if (p_ctrl->channel_mask & TAU_INPUT_CLOCK_CAPABLE_CHANNEL_MASK)
    {
        uint8_t tis0_value = (p_extend->input_source & R_PORGA_TIS0_TIS_Msk);
        R_PORGA->TIS0 = tis0_value;
    }

    /* When bits 12 (CCS), 9 and 8 (STS[1:0]) in the timer mode register mn (TMRmn) are 0 and then one of them is
     * set to 1, wait for at least two or four(if noise filter is enabled) cycles of the operating clock (fMCK),
     * and then set the operation
     * enable trigger bit in the timer channel start register (TSm). */
    if (TAU_FUNCTION_EXTERNAL_EVENT_COUNT < p_extend->tau_func)
    {
        r_tau_wait_time(p_ctrl, TAU_DELAY_2_CYCLE_FMCK * (p_extend->tau_filter + 1));
    }
}

#endif

#if TAU_CFG_OUTPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Configures output of TAU related registers based on user configurations.
 *
 * @param[in]     p_ctrl               Pointer to TAU control structure
 **********************************************************************************************************************/
static void r_tau_config_output_set (tau_instance_ctrl_t * const p_ctrl)
{
    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Sets master channel output mode. Note: r_tau does not support slave functionality.*/
    uint8_t inverted_channel_mask = (uint8_t) (~p_ctrl->channel_mask);

    if (p_ctrl->channel_mask > 0x01U)
    {
        R_TAU->TOM0 &= inverted_channel_mask;
        R_TAU->TOL0 &= inverted_channel_mask;
    }

    uint16_t to0_value  = R_TAU->TO0 & inverted_channel_mask;
    uint16_t toe0_value = R_TAU->TOE0 & inverted_channel_mask;

    if ((1 << p_extend->tau_func) & TAU_FUNCTION_SUPPORTED_OUTPUT_MASK)
    {
        if (TAU_PIN_OUTPUT_CFG_START_LEVEL_HIGH == p_extend->initial_output)
        {
            to0_value |= p_ctrl->channel_mask;
        }

        toe0_value |= p_ctrl->channel_mask;
    }

    R_TAU->TO0  = to0_value;
    R_TAU->TOE0 = toe0_value;
}

#endif

/*******************************************************************************************************************//**
 * Set TAU counter registers based on user configurations.
 *
 * @param[in]  p_ctrl                Pointer to TAU control structure
 * @param[in]  period_counts         Current timer period (lower 8-bit or 16-bit timer)
 * @param[in]  period_8bit_counts    Current higher 8-bit timer period
 *
 * @retval FSP_SUCCESS               The counter was successful updated.
 * @retval FSP_ERR_ASSERTION         The period is not in the valid range
 **********************************************************************************************************************/
static fsp_err_t r_tau_cnt_set (tau_instance_ctrl_t * const p_ctrl, uint32_t period_counts, uint32_t period_8bit_counts)
{
    tau_extended_cfg_t * p_extend = (tau_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
#if TAU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(FSP_ERR_ASSERTION != r_tau_cnt_check(p_ctrl, period_counts, period_8bit_counts));
#endif

    uint8_t  channel  = p_ctrl->p_cfg->channel;
    uint16_t tdr      = (uint16_t) (period_counts - 1);
    uint8_t  tdr_8bit = ((uint8_t) period_8bit_counts - 1);

    if ((TAU_FUNCTION_DIVIDER == p_extend->tau_func) && (TAU_TRIGGER_EDGE_BOTH != p_extend->trigger_edge))
    {
        tdr = (uint16_t) ((period_counts >> 1) - 1);
    }

    uint16_t tdr_mask = 0;

    if ((1U << p_extend->tau_func) & TAU_TDR_WRITE_MSK_BY_TIMER_MODE)
    {
        tdr_mask = TAU_TDR_MASK;
    }

    R_TAU->TDR0[channel].TDR0n = (tdr & tdr_mask);

    if ((TAU_BIT_MODE_HIGHER_8BIT == p_extend->bit_mode) || (TAU_BIT_MODE_HIGHER_LOWER_8BIT == p_extend->bit_mode))
    {
        R_TAU->TDR0[channel].TDR0nH = tdr_8bit & ((uint8_t) tdr_mask);
    }

    return FSP_SUCCESS;
}

#if TAU_CFG_INPUT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * This function implements waiting for at least 4 cycles of CPU clock.
 * @param[in] p_ctrl          Pointer to instance control block.
 * @param[in] delay_cycles    Delay cycles value of the operating clock (fMCK).
 **********************************************************************************************************************/
static void r_tau_wait_time (tau_instance_ctrl_t * const p_ctrl, uint32_t delay_cycles)
{
    /* Calculate frequency TAU operation clock */
    uint32_t fmck = r_tau_clock_frequency_get(p_ctrl);

    uint32_t cpu_count = (uint32_t) (SystemCoreClock / fmck);

    if (cpu_count > 4)
    {
        uint32_t count = (cpu_count * delay_cycles);

        /* Waiting for the period */
        bsp_prv_software_delay_loop(count / 4);
    }
}

#endif

/*******************************************************************************************************************//**
 * Calculates clock frequency of TAU counter.
 *
 * @param[in]  p_instance_ctrl           Instance control block
 *
 * @return     Clock frequency of the TAU counter.
 **********************************************************************************************************************/
static uint32_t r_tau_clock_frequency_get (tau_instance_ctrl_t * const p_instance_ctrl)
{
    /* Look-up table for operation clock CK02 */
    const uint8_t convert_to_ck02_clockdiv_lut[] =
    {
        [0] = TIMER_SOURCE_DIV_2,
        [1] = TIMER_SOURCE_DIV_4,
        [2] = TIMER_SOURCE_DIV_16,
        [3] = TIMER_SOURCE_DIV_64,
    };

    /* Look-up table for operation clock CK03 */
    const uint8_t convert_to_ck03_clockdiv_lut[] =
    {
        [0] = TIMER_SOURCE_DIV_8,
        [1] = TIMER_SOURCE_DIV_1024,
        [2] = TIMER_SOURCE_DIV_4096,
        [3] = TIMER_SOURCE_DIV_16384,
    };

    /* This table is indexed by tau_operation_ck_t. */
    const uint8_t operation_clock_table[] =
    {
        R_TAU->TPS0_b.PRS0,
        convert_to_ck02_clockdiv_lut[R_TAU->TPS0_b.PRS2],
        R_TAU->TPS0_b.PRS1,
        convert_to_ck03_clockdiv_lut[R_TAU->TPS0_b.PRS3]
    };

    /* Get TAU clock divider */
    timer_source_div_t divisor = (timer_source_div_t) operation_clock_table[((tau_extended_cfg_t *)
                                                                             (p_instance_ctrl->p_cfg->p_extend))->
                                                                            operation_clock];

    uint32_t freq_hz = R_FSP_SystemClockHzGet(BSP_FEATURE_TAU_CLOCK_SOURCE);

    return freq_hz >> divisor;
}

/*******************************************************************************************************************//**
 * Disables interrupt if it is a valid vector number.
 *
 * @param[in]  irq                     Interrupt number
 **********************************************************************************************************************/
static void r_tau_disable_irq (IRQn_Type irq)
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
static void r_tau_enable_irq (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, priority, p_context);
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to TAU instance control block
 * @param[in]     event      Event code
 * @param[in]     capture    Event capture counts (if applicable)
 **********************************************************************************************************************/
static void r_tau_call_callback (tau_instance_ctrl_t * p_ctrl, timer_event_t event, uint32_t capture)
{
    timer_callback_args_t args;

    args.event     = event;
    args.capture   = capture;
    args.p_context = p_ctrl->p_context;

    if (TIMER_EVENT_CAPTURE_EDGE == event)
    {
        if (0 != (R_TAU->TSR0[p_ctrl->p_cfg->channel] & 0x01))
        {
            args.capture = (capture + 1UL) + TAU_TDR_OVF_VALUE;
        }
        else
        {
            args.capture = (capture + 1UL);
        }
    }

    /* If the project is not Trustzone Secure,
     * then it will never need to change security state in order to call the callback.
     */
    p_ctrl->p_callback(&args);
}

/*******************************************************************************************************************//**
 * Stops the timer if one-shot mode, clears interrupts, and calls callback if one was provided in the open function.
 **********************************************************************************************************************/
void tau_tmi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    timer_event_t event = TIMER_EVENT_CYCLE_END;

    tau_function_t func    = ((tau_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->tau_func;
    uint32_t       counter = 0;

    if ((TAU_FUNCTION_INPUT_PULSE_INTERVAL_MEASUREMENT == func) || (TAU_FUNCTION_LOW_LEVEL_WIDTH_MEASUREMENT == func) ||
        (TAU_FUNCTION_HIGH_LEVEL_WIDTH_MEASUREMENT == func))
    {
        event = TIMER_EVENT_CAPTURE_EDGE;

        /* Get captured value. */
        counter = (uint32_t) (R_TAU->TDR0[p_instance_ctrl->p_cfg->channel].TDR0n);
    }

    if (NULL != p_instance_ctrl->p_callback)
    {
        r_tau_call_callback(p_instance_ctrl, event, counter);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Only supported for higher 8-bit timer mode. Notifies application of trough event.
 **********************************************************************************************************************/
void tau_tmih_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    tau_instance_ctrl_t * p_instance_ctrl = (tau_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    timer_event_t event = TIMER_EVENT_HIGHER_8BIT_CYCLE_END;

    if (NULL != p_instance_ctrl->p_callback)
    {
        r_tau_call_callback(p_instance_ctrl, event, 0);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
