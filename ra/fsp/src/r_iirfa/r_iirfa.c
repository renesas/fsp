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
#include <string.h>
#include "r_iirfa.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define IIRFA_OPEN                (0x52494952)
#define IIRFA_PRV_NUM_CHANNELS    (16)

#define IIRFA_FILTER_STAGES(stage_base, stage_num) \
    (UINT32_MAX << (32 - (stage_num))) >> (32 - (stage_num) - (stage_base))

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* Filter stages in use */
static uint32_t g_iirfa_filter_stages = 0U;

const iir_api_t g_iir_on_iirfa =
{
    .open      = R_IIRFA_Open,
    .close     = R_IIRFA_Close,
    .configure = R_IIRFA_Configure,
    .filter    = R_IIRFA_Filter,
    .statusGet = R_IIRFA_StatusGet,
};

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup IIRFA
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Prepare an IIR channel for filtering.
 *
 * @retval FSP_SUCCESS                     The channel was successfully opened.
 * @retval FSP_ERR_ASSERTION               One or both of the parameters was NULL.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  An invalid channel was selected.
 * @retval FSP_ERR_ALREADY_OPEN            The instance is already opened.
 **********************************************************************************************************************/
fsp_err_t R_IIRFA_Open (iir_ctrl_t * const p_api_ctrl, iir_cfg_t const * const p_cfg)
{
    iirfa_instance_ctrl_t * p_ctrl = (iirfa_instance_ctrl_t *) p_api_ctrl;

#if IIRFA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_cfg->channel < IIRFA_PRV_NUM_CHANNELS, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN(!p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Start clocks to IIRFA */
    R_BSP_MODULE_START(FSP_IP_IIRFA, 0);

#if (IIRFA_CFG_ECC_SUPPORT > 0)

    /* Set global ECC setting */
    R_IIRFA->IIRECCCNT = IIRFA_CFG_ECC_SUPPORT;
#endif

#if (IIRFA_CFG_ROUNDING_MODE > 0)

    /* Set global rounding setting */
    R_IIRFA->IIROPCNT = IIRFA_CFG_ROUNDING_MODE;
#endif

    /* Set channel in control struct */
    p_ctrl->channel = p_cfg->channel;

    /* Initialize filter_stages */
    p_ctrl->filter_stages = 0;

    /* Mark control block as opened */
    p_ctrl->open = IIRFA_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Start a filter operation on the specified data.
 *
 * @retval   FSP_SUCCESS                Data has been successfully filtered.
 * @retval   FSP_ERR_ASSERTION          One of the provided pointers is NULL.
 * @retval   FSP_ERR_NOT_OPEN           Instance is not open.
 * @retval   FSP_ERR_INVALID_ARGUMENT   num_samples is zero.
 * @retval   FSP_ERR_INVALID_RESULT     The result of one or more calculations was +/- infinity.
 * @retval   FSP_ERR_NOT_INITIALIZED    The filter is not configured.
 * @retval   FSP_ERR_IIRFA_ECC_1BIT     A 1-bit ECC error was detected.
 * @retval   FSP_ERR_IIRFA_ECC_2BIT     A 2-bit ECC error was detected.
 **********************************************************************************************************************/
fsp_err_t R_IIRFA_Filter (iir_ctrl_t * const p_api_ctrl,
                          float const      * p_data_in,
                          float            * p_data_out,
                          uint16_t const     num_samples)
{
    iirfa_instance_ctrl_t * p_ctrl = (iirfa_instance_ctrl_t *) p_api_ctrl;

#if IIRFA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_data_in);
    FSP_ASSERT(p_data_out);
    FSP_ERROR_RETURN(IIRFA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(num_samples > 0, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_ctrl->filter_stages != 0, FSP_ERR_NOT_INITIALIZED);
#endif

    /* Get pointers for data and registers */
    volatile float * const p_reg_in  = (volatile float *) &R_IIRFA->IIRCH[p_ctrl->channel].INP;
    volatile float * const p_reg_out = (volatile float *) &R_IIRFA->IIRCH[p_ctrl->channel].OUT;

    /* Define temporary macro to clean up loop unrolling */
#if IIRFA_CFG_LOOP_USE_POLLING
    volatile uint8_t * const p_reg_status = (volatile uint8_t *) &R_IIRFA->IIRCH[p_ctrl->channel].STS;
 #define IIRFA_PRV_PROCESS_SAMPLE                               \
    * p_reg_in = *p_data_in++;                                  \
    while (!(*p_reg_status & R_IIRFA_IIRCH_STS_CPRCFF_Msk)) {;} \
    *p_data_out++ = *p_reg_out;
#else
 #define IIRFA_PRV_PROCESS_SAMPLE \
    * p_reg_in    = *p_data_in++; \
    *p_data_out++ = *p_reg_out;
#endif

    /* Perform filter operation */
    for (uint32_t sample = 0; sample < num_samples / IIRFA_CFG_LOOP_UNROLL_DEPTH; sample++)
    {
        /* Reading an IIRCHnOUT register will cause the bus to wait until data is ready. While the bus is waiting
         * no interrupts will be handled. For this reason, the IIRCHnSTS register is polled for the CPRCFF flag first.
         * See RA6T2 User's Manual (R01UH0951EJ0100) section 33.3.5.2 "Procedure for Channel Processing Execution" for
         * further details. */
        IIRFA_PRV_PROCESS_SAMPLE;
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 2)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 3)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 4)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 5)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 6)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 7)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 8)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 9)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 10)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 11)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 12)
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 16)
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 20)
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 24)
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
#if (IIRFA_CFG_LOOP_UNROLL_DEPTH >= 32)
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;

        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
        IIRFA_PRV_PROCESS_SAMPLE;
#endif
    }

#if (IIRFA_CFG_LOOP_UNROLL_DEPTH > 1)

    /* Handle any remaining samples that don't fit into a multiple of the unroll depth */
    for (uint32_t sample = 0; sample < (num_samples % IIRFA_CFG_LOOP_UNROLL_DEPTH); sample++)
    {
        IIRFA_PRV_PROCESS_SAMPLE;
    }
#endif

    /* Undefine temporary macro */
#undef IIRFA_PRV_PROCESS_SAMPLE

    /* Check to ensure there were no errors in processing */
#if IIRFA_CFG_ECC_SUPPORT
    uint32_t iireccef = R_IIRFA->IIRECCEF;
    if ((R_IIRFA->IIRCERRF & (1 << p_ctrl->channel)) || (iireccef > 0))
    {
        /* Clear channel error status bits */
        R_IIRFA->IIRCH[p_ctrl->channel].FCLR_b.CERRFCLR = 1;
        R_IIRFA->IIRECCEFCLR = iireccef;

        /* Determine if a 1- or 2-bit ECC error has occurred */
        fsp_err_t err = FSP_ERR_INVALID_RESULT;
        if (iireccef > 0)
        {
            err = (iireccef & R_IIRFA_IIRECCEF_EDEF_Msk) ? FSP_ERR_IIRFA_ECC_2BIT : FSP_ERR_IIRFA_ECC_1BIT;
        }

        return err;
    }

#else

    /* Check to ensure there were no errors in processing */
    if (R_IIRFA->IIRCERRF & (1 << p_ctrl->channel))
    {
        /* Clear channel error status bit */
        R_IIRFA->IIRCH[p_ctrl->channel].FCLR_b.CERRFCLR = 1;

        return FSP_ERR_INVALID_RESULT;
    }
#endif

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Configure filter coefficients and state values.
 *
 * @retval   FSP_SUCCESS               Configuration successful.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 * @retval   FSP_ERR_INVALID_ARGUMENT  Invalid filter stage selection.
 * @retval   FSP_ERR_IN_USE            One or more requested filter stages are currently in use.
 **********************************************************************************************************************/
fsp_err_t R_IIRFA_Configure (iir_ctrl_t * const p_api_ctrl, iir_filter_cfg_t const * const p_filter_cfg)
{
    iirfa_instance_ctrl_t * p_ctrl = (iirfa_instance_ctrl_t *) p_api_ctrl;

#if IIRFA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_filter_cfg);
    FSP_ERROR_RETURN(IIRFA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_filter_cfg->stage_base < 32, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_filter_cfg->stage_num && (p_filter_cfg->stage_num <= (32 - p_filter_cfg->stage_base)),
                     FSP_ERR_INVALID_ARGUMENT);
#endif

    /* Calculate requested filter stage mask by shifting all 1s left then right */
    uint32_t filter_stages = IIRFA_FILTER_STAGES(p_filter_cfg->stage_base, p_filter_cfg->stage_num);
#if IIRFA_CFG_PARAM_CHECKING_ENABLE

    /* Ensure the requested stages are not in use */
    FSP_ERROR_RETURN(!(filter_stages & (g_iirfa_filter_stages & ~p_ctrl->filter_stages)), FSP_ERR_IN_USE);
#endif

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Keep track of what stages are used globally */
    g_iirfa_filter_stages = (g_iirfa_filter_stages & ~p_ctrl->filter_stages) | filter_stages;

    FSP_CRITICAL_SECTION_EXIT;

    p_ctrl->filter_stages = filter_stages;

    /* Set selected stages */
    R_IIRFA->IIRCH[p_ctrl->channel].CNT = filter_stages;

    uint32_t stage_base = p_filter_cfg->stage_base;
    uint32_t stage_num  = p_filter_cfg->stage_num;

    for (uint32_t stage = stage_base; stage < (stage_base + stage_num); stage++)
    {
        *(iir_filter_coeffs_t *) &R_IIRFA->IIRSTG[stage].B0 = p_filter_cfg->p_filter_coeffs[stage - stage_base];
        *(iir_filter_state_t *) &R_IIRFA->IIRSTG[stage].D0  = p_filter_cfg->p_filter_state[stage - stage_base];
    }

    p_ctrl->stage_base = (uint8_t) stage_base;
    p_ctrl->stage_num  = (uint8_t) stage_num;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Read the current filter state variables.
 *
 * @retval   FSP_SUCCESS               Information read successfully.
 * @retval   FSP_ERR_ASSERTION         p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN          Instance is not open.
 **********************************************************************************************************************/
fsp_err_t R_IIRFA_StatusGet (iir_ctrl_t * const p_api_ctrl, iir_status_t * const p_status)
{
    iirfa_instance_ctrl_t * p_ctrl = (iirfa_instance_ctrl_t *) p_api_ctrl;

#if IIRFA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(IIRFA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Only fill in state array if present */
    iir_filter_state_t * p_filter_state = p_status->p_filter_state;
    if (p_filter_state != NULL)
    {
        uint32_t stage_base = p_ctrl->stage_base;
        uint32_t stage_num  = p_ctrl->stage_num;

        /* Write current state variables to provided filter config */
        for (uint32_t stage = stage_base; stage < (stage_base + stage_num); stage++)
        {
            p_filter_state[stage - stage_base].d0 = *((float *) &R_IIRFA->IIRSTG[stage].D0);
            p_filter_state[stage - stage_base].d1 = *((float *) &R_IIRFA->IIRSTG[stage].D1);
        }
    }

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Stop filter operations and close the channel instance.
 *
 * @retval   FSP_SUCCESS           The channel is successfully closed.
 * @retval   FSP_ERR_ASSERTION     p_api_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Instance is not open.
 **********************************************************************************************************************/
fsp_err_t R_IIRFA_Close (iir_ctrl_t * const p_api_ctrl)
{
    iirfa_instance_ctrl_t * p_ctrl = (iirfa_instance_ctrl_t *) p_api_ctrl;

#if IIRFA_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(IIRFA_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear channel stages in case another channel needs to use them */
    R_IIRFA->IIRCH[p_ctrl->channel].CNT = 0U;

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Release stages in g_iirfa_filter_stages */
    g_iirfa_filter_stages &= ~p_ctrl->filter_stages;

    FSP_CRITICAL_SECTION_EXIT;

    /* Set control block to closed */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IIRFA)
 **********************************************************************************************************************/
