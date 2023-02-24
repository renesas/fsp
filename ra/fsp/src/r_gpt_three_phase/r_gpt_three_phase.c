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
#include "r_gpt_three_phase.h"
#include "r_gpt_three_phase_cfg.h"

#include "r_gpt.h"
#include "r_gpt_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "GPT3" in ASCII, used to determine if channel is open. */
#define GPT_THREE_PHASE_OPEN                       (0x47505433ULL)

#define GPT_THREE_PHASE_PRV_GTWP_RESET_VALUE       (0xA500U)
#define GPT_THREE_PHASE_PRV_GTWP_WRITE_PROTECT     (0xA501U)

#define GPT_THREE_PHASE_PRV_GTBER_SINGLE_BUFFER    (0x50000U)
#define GPT_THREE_PHASE_PRV_GTBER_DOUBLE_BUFFER    (0xA0000U)

#define GPT_THREE_PHASE_PRV_GTWP_RESET_VALUE       (0xA500U)
#define GPT_THREE_PHASE_PRV_GTWP_WRITE_PROTECT     (0xA501U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
enum e_gpt_three_phase_prv_gtccr
{
    GPT_THREE_PHASE_PRV_GTCCRA = 0U,
    GPT_THREE_PHASE_PRV_GTCCRB,
    GPT_THREE_PHASE_PRV_GTCCRC,
    GPT_THREE_PHASE_PRV_GTCCRE,
    GPT_THREE_PHASE_PRV_GTCCRD,
    GPT_THREE_PHASE_PRV_GTCCRF
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_enable_all(gpt_three_phase_instance_ctrl_t * const p_instance_ctrl);
static inline void r_gpt_write_protect_disable_all(gpt_three_phase_instance_ctrl_t * const p_instance_ctrl);

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Implementation of GPT_THREE_PHASE interface  */
const three_phase_api_t g_gpt_three_phase_on_gpt_three_phase =
{
    .open         = R_GPT_THREE_PHASE_Open,
    .stop         = R_GPT_THREE_PHASE_Stop,
    .start        = R_GPT_THREE_PHASE_Start,
    .reset        = R_GPT_THREE_PHASE_Reset,
    .dutyCycleSet = R_GPT_THREE_PHASE_DutyCycleSet,
    .callbackSet  = R_GPT_THREE_PHASE_CallbackSet,
    .close        = R_GPT_THREE_PHASE_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup GPT_THREE_PHASE
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the 3-phase timer module (and associated timers) and applies configurations. Implements
 * @ref three_phase_api_t::open.
 *
 * Example:
 * @snippet r_gpt_three_phase_example.c R_GPT_THREE_PHASE_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_Open (three_phase_ctrl_t * const p_ctrl, three_phase_cfg_t const * const p_cfg)
{
    gpt_three_phase_instance_ctrl_t * p_instance_ctrl = (gpt_three_phase_instance_ctrl_t *) p_ctrl;
#if GPT_THREE_PHASE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_THREE_PHASE_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    fsp_err_t err;

    /* Open all three GPT submodules */
    for (three_phase_channel_t ch = THREE_PHASE_CHANNEL_U; ch <= THREE_PHASE_CHANNEL_W; ch++)
    {
        err = R_GPT_Open(p_cfg->p_timer_instance[ch]->p_ctrl, p_cfg->p_timer_instance[ch]->p_cfg);
#if GPT_CFG_PARAM_CHECKING_ENABLE
        if (err)
        {
            /* In case of an error on GPT open, close all opened instances and return the error */
            for (three_phase_channel_t close_ch = THREE_PHASE_CHANNEL_U; close_ch < ch; close_ch++)
            {
                R_GPT_Close(p_cfg->p_timer_instance[close_ch]->p_ctrl);
            }

            return err;
        }

#else
        FSP_PARAMETER_NOT_USED(err);
#endif

        /* Save a pointer to the GPT registers for this channel */
        p_instance_ctrl->p_reg[ch] = ((gpt_instance_ctrl_t *) (p_cfg->p_timer_instance[ch]->p_ctrl))->p_reg;

#if GPT_CFG_WRITE_PROTECT_ENABLE

        /* Disable write protection on the current GPT channel */
        p_instance_ctrl->p_reg[ch]->GTWP = GPT_THREE_PHASE_PRV_GTWP_RESET_VALUE;
#endif

        /* Set the buffer mode */
        if (THREE_PHASE_BUFFER_MODE_DOUBLE == p_cfg->buffer_mode)
        {
            p_instance_ctrl->p_reg[ch]->GTBER |= GPT_THREE_PHASE_PRV_GTBER_DOUBLE_BUFFER;
        }

#if GPT_CFG_WRITE_PROTECT_ENABLE

        /* Re-enable write protection */
        p_instance_ctrl->p_reg[ch]->GTWP = GPT_THREE_PHASE_PRV_GTWP_WRITE_PROTECT;
#endif
    }

    /* Get copy of GPT channel mask and buffer mode */
    p_instance_ctrl->channel_mask = p_cfg->channel_mask;
    p_instance_ctrl->buffer_mode  = p_cfg->buffer_mode;

    /* Save pointer to config struct */
    p_instance_ctrl->p_cfg = p_cfg;

    p_instance_ctrl->open = GPT_THREE_PHASE_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops all timers synchronously. Implements @ref three_phase_api_t::stop.
 *
 * @retval FSP_SUCCESS                 Timers successfully stopped.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_Stop (three_phase_ctrl_t * const p_ctrl)
{
    gpt_three_phase_instance_ctrl_t * p_instance_ctrl = (gpt_three_phase_instance_ctrl_t *) p_ctrl;
#if GPT_THREE_PHASE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_THREE_PHASE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop timer */
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_U]->GTSTP = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts all timers synchronously. Implements @ref three_phase_api_t::start.
 *
 * Example:
 * @snippet r_gpt_three_phase_example.c R_GPT_THREE_PHASE_Start
 *
 * @retval FSP_SUCCESS                 Timers successfully started.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_Start (three_phase_ctrl_t * const p_ctrl)
{
    gpt_three_phase_instance_ctrl_t * p_instance_ctrl = (gpt_three_phase_instance_ctrl_t *) p_ctrl;
#if GPT_THREE_PHASE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_THREE_PHASE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start timer */
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_U]->GTSTR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets the counter values to 0. Implements @ref three_phase_api_t::reset.
 *
 * @retval FSP_SUCCESS                 Counters were reset successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_Reset (three_phase_ctrl_t * const p_ctrl)
{
    gpt_three_phase_instance_ctrl_t * p_instance_ctrl = (gpt_three_phase_instance_ctrl_t *) p_ctrl;
#if GPT_THREE_PHASE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_THREE_PHASE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear timer counter. */
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_U]->GTCLR = p_instance_ctrl->channel_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets duty cycle for all three timers. Implements @ref three_phase_api_t::dutyCycleSet.
 *
 * In symmetric PWM mode duty cycle values are reflected after the next trough. In asymmetric PWM mode values are
 * reflected at the next trough OR crest, whichever comes first.
 *
 * When double-buffering is enabled the values in @ref three_phase_duty_cycle_t::duty_buffer are set to the
 * double-buffer registers. When values are reflected the first time the single buffer values
 * (@ref three_phase_duty_cycle_t::duty) are used. On the second reflection the duty_buffer values are used.
 * In asymmetric PWM mode this enables both count-up and count-down PWM values to be set at trough (or crest)
 * exclusively.
 *
 * @note It is recommended to call this function in a high-priority callback to ensure that it is not interrupted and
 * that no GPT events occur during setting that would result in a duty cycle buffer load operation.
 *
 * Example:
 * @snippet r_gpt_three_phase_example.c R_GPT_THREE_PHASE_DutyCycleSet
 *
 * @retval FSP_SUCCESS                 Duty cycle updated successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT    One or more duty cycle count values was outside the range 0..(period - 1).
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_DutyCycleSet (three_phase_ctrl_t * const       p_ctrl,
                                          three_phase_duty_cycle_t * const p_duty_cycle)
{
    gpt_three_phase_instance_ctrl_t * p_instance_ctrl = (gpt_three_phase_instance_ctrl_t *) p_ctrl;
#if GPT_THREE_PHASE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_duty_cycle);
    FSP_ERROR_RETURN(GPT_THREE_PHASE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check that duty cycle values are in-range (less than period) */
    for (three_phase_channel_t ch = THREE_PHASE_CHANNEL_U; ch <= THREE_PHASE_CHANNEL_W; ch++)
    {
        uint32_t gtpr = p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_U]->GTPR;
        FSP_ERROR_RETURN((p_duty_cycle->duty[ch] < gtpr) && (p_duty_cycle->duty[ch] > 0), FSP_ERR_INVALID_ARGUMENT);

        /* In double-buffer mode also check double buffer */
        if (THREE_PHASE_BUFFER_MODE_DOUBLE == p_instance_ctrl->buffer_mode)
        {
            FSP_ERROR_RETURN((p_duty_cycle->duty_buffer[ch] < gtpr) && (p_duty_cycle->duty_buffer[ch] > 0),
                             FSP_ERR_INVALID_ARGUMENT);
        }
    }
#endif

    r_gpt_write_protect_disable_all(p_instance_ctrl);

    /* Set all duty cycle registers */
    for (three_phase_channel_t ch = THREE_PHASE_CHANNEL_U; ch <= THREE_PHASE_CHANNEL_W; ch++)
    {
        p_instance_ctrl->p_reg[ch]->GTCCR[GPT_THREE_PHASE_PRV_GTCCRC] = p_duty_cycle->duty[ch];
        p_instance_ctrl->p_reg[ch]->GTCCR[GPT_THREE_PHASE_PRV_GTCCRE] = p_duty_cycle->duty[ch];

        /* Set double-buffer registers (if applicable) */
        if ((THREE_PHASE_BUFFER_MODE_DOUBLE == p_instance_ctrl->buffer_mode) ||
            (TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3 == p_instance_ctrl->p_cfg->p_timer_instance[0]->p_cfg->mode))
        {
            p_instance_ctrl->p_reg[ch]->GTCCR[GPT_THREE_PHASE_PRV_GTCCRD] = p_duty_cycle->duty_buffer[ch];
            p_instance_ctrl->p_reg[ch]->GTCCR[GPT_THREE_PHASE_PRV_GTCCRF] = p_duty_cycle->duty_buffer[ch];
        }
    }

    r_gpt_write_protect_enable_all(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback for the GPT U-channel with the option to provide memory for the callback argument
 * structure.
 * Implements @ref three_phase_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_CallbackSet (three_phase_ctrl_t * const    p_ctrl,
                                         void (                      * p_callback)(timer_callback_args_t *),
                                         void const * const            p_context,
                                         timer_callback_args_t * const p_callback_memory)
{
    gpt_three_phase_instance_ctrl_t * p_instance_ctrl = (gpt_three_phase_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if GPT_THREE_PHASE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(GPT_THREE_PHASE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    err = R_GPT_CallbackSet(p_instance_ctrl->p_cfg->p_timer_instance[p_instance_ctrl->p_cfg->callback_ch]->p_ctrl,
                            p_callback,
                            p_context,
                            p_callback_memory);

    return err;
}

/*******************************************************************************************************************//**
 * Stops counters, disables output pins, and clears internal driver data. Implements @ref three_phase_api_t::close.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_GPT_THREE_PHASE_Close (three_phase_ctrl_t * const p_ctrl)
{
    gpt_three_phase_instance_ctrl_t * p_instance_ctrl = (gpt_three_phase_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if GPT_THREE_PHASE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(GPT_THREE_PHASE_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    /* Stop counter. */
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_U]->GTSTP = p_instance_ctrl->channel_mask;

    /* Close all GPT modules */
    for (three_phase_channel_t ch = THREE_PHASE_CHANNEL_U; ch <= THREE_PHASE_CHANNEL_W; ch++)
    {
        R_GPT_Close(p_instance_ctrl->p_cfg->p_timer_instance[ch]->p_ctrl);
    }

    return err;
}

/** @} (end addtogroup GPT_THREE_PHASE) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enables write protection for all relevant GPT registers (if enabled).
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_enable_all (gpt_three_phase_instance_ctrl_t * const p_instance_ctrl)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_U]->GTWP = GPT_THREE_PHASE_PRV_GTWP_WRITE_PROTECT;
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_V]->GTWP = GPT_THREE_PHASE_PRV_GTWP_WRITE_PROTECT;
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_W]->GTWP = GPT_THREE_PHASE_PRV_GTWP_WRITE_PROTECT;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * Disables write protection for all relevant GPT registers (if enabled).
 *
 * @param[in]  p_instance_ctrl         Instance control block.
 **********************************************************************************************************************/
static inline void r_gpt_write_protect_disable_all (gpt_three_phase_instance_ctrl_t * const p_instance_ctrl)
{
#if GPT_CFG_WRITE_PROTECT_ENABLE
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_U]->GTWP = GPT_THREE_PHASE_PRV_GTWP_RESET_VALUE;
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_V]->GTWP = GPT_THREE_PHASE_PRV_GTWP_RESET_VALUE;
    p_instance_ctrl->p_reg[THREE_PHASE_CHANNEL_W]->GTWP = GPT_THREE_PHASE_PRV_GTWP_RESET_VALUE;
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
}
