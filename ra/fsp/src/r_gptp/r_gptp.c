/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "r_gptp.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/** "GPTP" in ASCII.  Used to determine if the control block is open. */
#define GPTP_OPEN                         (('G' << 24U) | ('P' << 16U) | ('T' << 8U) | ('P' << 0U))

#define GPTP_GPTP_TIMER_OFFSET            (0x40)
#define GPTP_PULSE_OUTPUT_TIMER_OFFSET    (0x30)
#define GPTP_SEC_LOWER_OFFSET             (0x100000000L)

#define GPTP_CLOCK_PERIOD_MASK            (0x1F)
#define GPTP_OFFSET_MASK                  (0xFFFFFFFF)
#define GPTP_OFFSET_NANO_SEC_MASK         (0x3FFFFFFF)
#define GPTP_SEC_UPPER_MASK               (0xFFFF)

#define GPTP_NANO_SEC_POSITION            (27)
#define GPTP_SEC_UPPER_POSITION           (32)

#define GPTP_NANO_COUNT_FOR_1SEC          (1000000000L)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** GPTP API mapping for gptp module. */
const gptp_api_t g_gptp_on_gptp =
{
    .open           = R_GPTP_Open,
    .close          = R_GPTP_Close,
    .timerCfg       = R_GPTP_TimerCfg,
    .start          = R_GPTP_Start,
    .stop           = R_GPTP_Stop,
    .timerValueGet  = R_GPTP_TimerValueGet,
    .timerOffsetSet = R_GPTP_TimerOffsetSet,
    .timerRateSet   = R_GPTP_TimerRateSet,
    .callbackSet    = R_GPTP_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup GPTP
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * Initializes the gptp module and applies configurations.
 *
 * @retval  FSP_SUCCESS                 Module opened successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to GPTP control block or configuration structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN        Control block has already been opened or channel is being used by another
 *                                      instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 ***********************************************************************************************************************/
fsp_err_t R_GPTP_Open (gptp_ctrl_t * const p_ctrl, gptp_cfg_t const * const p_cfg)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN((NULL != p_cfg), FSP_ERR_INVALID_POINTER);

    FSP_ERROR_RETURN((GPTP_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);
#endif

    /* Initialize configuration of gptp module. */
    p_instance_ctrl->p_reg_gptp        = (void *) R_GPTP;
    p_instance_ctrl->p_cfg             = p_cfg;
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    p_instance_ctrl->open = GPTP_OPEN;

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_Open() */

/********************************************************************************************************************//**
 * Close the gptp module.
 *
 * @retval  FSP_SUCCESS                                 Successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to GPTP control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t R_GPTP_Close (gptp_ctrl_t * const p_ctrl)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear configure block parameters. */
    p_instance_ctrl->p_cfg = NULL;

    /* Mark the channel not open so other APIs cannot use it. */
    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_Close() */

/*******************************************************************************************************************//**
 * Configures the gptp timer parameters.
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid timer id.
 * @retval  FSP_ERR_INVALID_POINTER     Invalid poiter to the timer cfg.
 **********************************************************************************************************************/
fsp_err_t R_GPTP_TimerCfg (gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_timer_cfg_t const * const p_timer_cfg)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;
    volatile uint32_t    * p_ptpvic_reg;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((BSP_FEATURE_ESWM_GPTP_TIMER_NUM > timer), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(NULL != p_timer_cfg, FSP_ERR_INVALID_POINTER);
#endif

    p_ptpvic_reg = (volatile uint32_t *) ((uint8_t *) &p_instance_ctrl->p_reg_gptp->PTPTIVC0 + \
                                          (GPTP_GPTP_TIMER_OFFSET * timer));
    *p_ptpvic_reg =
        (uint32_t) ((p_timer_cfg->clock_period & GPTP_CLOCK_PERIOD_MASK) << GPTP_NANO_SEC_POSITION);

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_TimerCfg() */

/*******************************************************************************************************************//**
 * Starts gptp timer.
 *
 * @retval  FSP_SUCCESS                 Timer started..
 * @retval  FSP_ERR_ASSERTION           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid timer id.
 **********************************************************************************************************************/
fsp_err_t R_GPTP_Start (gptp_ctrl_t * const p_ctrl, uint8_t timer)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;
    R_GPTP_Type          * p_gptp_reg;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((BSP_FEATURE_ESWM_GPTP_TIMER_NUM > timer), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_gptp_reg                = p_instance_ctrl->p_reg_gptp;
    p_gptp_reg->PTPTMEC_b.TE |= (1U << timer);

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_Start() */

/*******************************************************************************************************************//**
 * Stops gptp timer.
 *
 * @retval  FSP_SUCCESS                 Timer stopped.
 * @retval  FSP_ERR_ASSERTION           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid timer id.
 **********************************************************************************************************************/
fsp_err_t R_GPTP_Stop (gptp_ctrl_t * const p_ctrl, uint8_t timer)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;
    R_GPTP_Type          * p_gptp_reg;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((BSP_FEATURE_ESWM_GPTP_TIMER_NUM > timer), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_gptp_reg                = p_instance_ctrl->p_reg_gptp;
    p_gptp_reg->PTPTMDC_b.TD |= (1U << timer);

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_Stop() */

/*******************************************************************************************************************//**
 * Gets the current time value to the timer with the specified gptp timer number.
 *
 * @retval  FSP_SUCCESS                 Sec upper, sec lower, and nano sec srored in p_timestamp.
 * @retval  FSP_ERR_ASSERTION           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 **********************************************************************************************************************/
fsp_err_t R_GPTP_TimerValueGet (gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_timer_value_t * const p_timer_value)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;
    R_GPTP_Type          * p_gptp_reg;
    volatile uint32_t    * p_ptpgptptml_reg;
    volatile uint32_t    * p_ptpgptptmm_reg;
    volatile uint32_t    * p_ptpgptptmu_reg;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    FSP_ERROR_RETURN((NULL != p_timer_value), FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BSP_FEATURE_ESWM_GPTP_TIMER_NUM > timer, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_gptp_reg = p_instance_ctrl->p_reg_gptp;

    p_ptpgptptml_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->PTPGPTPTML0 + \
                                              (GPTP_GPTP_TIMER_OFFSET * timer));
    p_timer_value->time_nsec = *p_ptpgptptml_reg;

    p_ptpgptptmm_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->PTPGPTPTMM0 + \
                                              (GPTP_GPTP_TIMER_OFFSET * timer));
    p_timer_value->time_sec_lower = *p_ptpgptptmm_reg;

    p_ptpgptptmu_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->PTPGPTPTMU0 + \
                                              (GPTP_GPTP_TIMER_OFFSET * timer));
    p_timer_value->time_sec_upper = (uint16_t) (*p_ptpgptptmu_reg);

    return FSP_SUCCESS;
}                                      /* End of R_GPTP_GptpTimeValueGet() */

/********************************************************************************************************************//**
 * Sets the offset correction for the specified gptp timer number.
 *
 * @retval  FSP_SUCCESS                 Time offset set successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 ***********************************************************************************************************************/
fsp_err_t R_GPTP_TimerOffsetSet (gptp_ctrl_t * const p_ctrl, uint8_t timer, int64_t offset)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;
    R_GPTP_Type          * p_gptp_reg;

    int64_t offset_abs;
    int64_t offset_nsec;
    int64_t offset_sec_lower;
    int64_t offset_sec_upper;

    volatile uint32_t * p_ptptovcl_reg;
    volatile uint32_t * p_ptptovcm_reg;
    volatile uint32_t * p_ptptovcu_reg;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_ESWM_GPTP_TIMER_NUM > timer, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_gptp_reg = p_instance_ctrl->p_reg_gptp;

    /* Obtains the offset value currently applied to the gPTP timer and adds the set offset. */
    p_ptptovcl_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->PTPTOVCL0 + \
                                            (GPTP_GPTP_TIMER_OFFSET * timer));
    p_ptptovcm_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->PTPTOVCM0 + \
                                            (GPTP_GPTP_TIMER_OFFSET * timer));
    p_ptptovcu_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->PTPTOVCU0 + \
                                            (GPTP_GPTP_TIMER_OFFSET * timer));

    if (0 <= offset)
    {
        /* When advancing a gPTP timer, add an offset value. */
        offset_abs = offset;

        /* Check for carryover during nanosecond addition. */
        offset_nsec = (int64_t) (*p_ptptovcl_reg) + (offset_abs % GPTP_NANO_COUNT_FOR_1SEC);
        if (GPTP_NANO_COUNT_FOR_1SEC <= offset_nsec)
        {
            offset_nsec     -= GPTP_NANO_COUNT_FOR_1SEC;
            offset_sec_lower = (int64_t) (*p_ptptovcm_reg) + \
                               ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) & GPTP_OFFSET_MASK) + 1;
        }
        else
        {
            offset_sec_lower = (int64_t) (*p_ptptovcm_reg) + \
                               ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) & GPTP_OFFSET_MASK);
        }

        /* Check for carryover during lower second addition. */
        if ((int64_t) GPTP_OFFSET_MASK < offset_sec_lower)
        {
            offset_sec_lower -= (int64_t) GPTP_SEC_LOWER_OFFSET;
            offset_sec_upper  = (int64_t) (*p_ptptovcu_reg) + \
                                ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) >> GPTP_SEC_UPPER_POSITION) + 1;
        }
        else
        {
            offset_sec_upper = (int64_t) (*p_ptptovcu_reg) + \
                               ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) >> GPTP_SEC_UPPER_POSITION);
        }
    }
    else
    {
        /* To set the gPTP timer back, subtract the offset value. */
        offset_abs = offset * -1;

        /* When subtracting nanoseconds, check for borrowing. */
        offset_nsec = (int64_t) (*p_ptptovcl_reg) - (offset_abs % GPTP_NANO_COUNT_FOR_1SEC);
        if (0 > offset_nsec)
        {
            offset_nsec     += GPTP_NANO_COUNT_FOR_1SEC;
            offset_sec_lower = (int64_t) (*p_ptptovcm_reg) - \
                               ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) & GPTP_OFFSET_MASK) - 1;
        }
        else
        {
            offset_sec_lower = (int64_t) (*p_ptptovcm_reg) - \
                               ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) & GPTP_OFFSET_MASK);
        }

        /* When subtracting lower second, check for borrowing. */
        if (0 > offset_sec_lower)
        {
            offset_sec_lower += (int64_t) GPTP_SEC_LOWER_OFFSET;
            offset_sec_upper  = (int64_t) (*p_ptptovcu_reg) - \
                                ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) >> GPTP_SEC_UPPER_POSITION) - 1;
        }
        else
        {
            offset_sec_upper = (int64_t) (*p_ptptovcu_reg) - \
                               ((offset_abs / GPTP_NANO_COUNT_FOR_1SEC) >> GPTP_SEC_UPPER_POSITION);
        }
    }

    *p_ptptovcu_reg = (uint16_t) offset_sec_upper;
    *p_ptptovcm_reg = (uint32_t) offset_sec_lower;
    *p_ptptovcl_reg = (uint32_t) offset_nsec & GPTP_OFFSET_NANO_SEC_MASK;

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_TimeOffsetSet() */

/********************************************************************************************************************//**
 * Sets clock rate correction for the specified timer.
 *
 * @retval  FSP_SUCCESS                 Time rate set successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 ***********************************************************************************************************************/
fsp_err_t R_GPTP_TimerRateSet (gptp_ctrl_t * const p_ctrl, uint8_t timer, uint32_t rate)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;
    R_GPTP_Type          * p_gptp_reg;
    volatile uint32_t    * p_ptpvic_reg;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_ESWM_GPTP_TIMER_NUM > timer, FSP_ERR_INVALID_ARGUMENT);
#endif

    p_gptp_reg = p_instance_ctrl->p_reg_gptp;

    p_ptpvic_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->PTPTIVC0 + \
                                          (GPTP_GPTP_TIMER_OFFSET * timer));
    *p_ptpvic_reg = rate;

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_TimeRateSet() */

/********************************************************************************************************************//**
 * Sets pulse generator.
 *
 * @retval  FSP_SUCCESS                 Pulse generator set successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 ***********************************************************************************************************************/
fsp_err_t R_GPTP_PulseGeneratorSet (gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_pulse_generator_t * p_pulse)
{
    gptp_instance_ctrl_t     * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;
    gptp_pulsed_output_cfg_t * p_pulsed_output_cfg;
    R_GPTP_Type              * p_gptp_reg;

    volatile uint32_t * p_potcr_reg;
    volatile uint32_t * p_potstru_reg;
    volatile uint32_t * p_potstrm_reg;
    volatile uint32_t * p_potstrl_reg;
    volatile uint32_t * p_potperu_reg;
    volatile uint32_t * p_potperm_reg;
    volatile uint32_t * p_potperl_reg;
    volatile uint32_t * p_potpwr_reg;

#if (GPTP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    FSP_ERROR_RETURN((NULL != p_pulse), FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(BSP_FEATURE_ESWM_GPTP_TIMER_NUM > timer, FSP_ERR_INVALID_ARGUMENT);

    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM; i++)
    {
        FSP_ERROR_RETURN(BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM > p_pulse->p_pulsed_output_cfg_list[i]->pulse_num,
                         FSP_ERR_INVALID_ARGUMENT);
        FSP_ERROR_RETURN(GPTP_NANO_COUNT_FOR_1SEC > p_pulse->p_pulsed_output_cfg_list[i]->period_ns,
                         FSP_ERR_INVALID_ARGUMENT);
        FSP_ERROR_RETURN(GPTP_NANO_COUNT_FOR_1SEC > p_pulse->p_pulsed_output_cfg_list[i]->start_ns,
                         FSP_ERR_INVALID_ARGUMENT);
    }
#endif

    p_gptp_reg = p_instance_ctrl->p_reg_gptp;

    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM; i++)
    {
        p_pulsed_output_cfg = p_pulse->p_pulsed_output_cfg_list[i];
        p_potcr_reg         = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTCR0 +
                                                     (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));

        /* Stop pulse output for modification POTCFGR register. */
        *p_potcr_reg = 0U;

        p_gptp_reg->POTCFGR_b.REFSEL = (uint32_t) (timer & 0x1);

        /* Modification Pulse output generation registers. */
        p_potstru_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTSTRU0 + \
                                               (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));
        *p_potstru_reg = (p_pulsed_output_cfg->start_sec_upper & GPTP_SEC_UPPER_MASK);

        p_potstrm_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTSTRM0 + \
                                               (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));
        *p_potstrm_reg = p_pulsed_output_cfg->start_sec_lower;

        p_potstrl_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTSTRL0 + \
                                               (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));
        *p_potstrl_reg = (p_pulsed_output_cfg->start_ns & GPTP_OFFSET_NANO_SEC_MASK);

        p_potperu_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTPERU0 + \
                                               (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));
        *p_potperu_reg = (p_pulsed_output_cfg->period_sec_upper & GPTP_SEC_UPPER_MASK);

        p_potperm_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTPERM0 + \
                                               (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));
        *p_potperm_reg = p_pulsed_output_cfg->period_sec_lower;

        p_potperl_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTPERL0 + \
                                               (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));
        *p_potperl_reg = (p_pulsed_output_cfg->period_ns & GPTP_OFFSET_NANO_SEC_MASK);

        p_potpwr_reg = (volatile uint32_t *) ((uint8_t *) &p_gptp_reg->POTPWR0 + \
                                              (GPTP_PULSE_OUTPUT_TIMER_OFFSET * p_pulsed_output_cfg->pulse_num));
        *p_potpwr_reg = (p_pulsed_output_cfg->wide & GPTP_SEC_UPPER_MASK);

        /* Apply generate pulse setting. */
        *p_potcr_reg = 1U;
    }

    return FSP_SUCCESS;
}                                      /* End of function R_GPTP_PulseGeneratorSet() */

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref gptp_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_GPTP_CallbackSet (gptp_ctrl_t * const          p_ctrl,
                              void (                     * p_callback)(gptp_callback_args_t *),
                              void * const                 p_context,
                              gptp_callback_args_t * const p_callback_memory)
{
    gptp_instance_ctrl_t * p_instance_ctrl = (gptp_instance_ctrl_t *) p_ctrl;

#if GPTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(GPTP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if GPTP_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    gptp_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                       CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(gptp_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup GPTP)
 **********************************************************************************************************************/
