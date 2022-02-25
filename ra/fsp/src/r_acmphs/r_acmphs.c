/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_acmphs_cfg.h"
#include "r_acmphs.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ACMPHS_OPEN                        (0x434d5048U)

/* ACMPHS base register access macro.  */
#define ACMPHS_REG(channel)    ((R_ACMPHS0_Type *) ((uint32_t) R_ACMPHS0 +                          \
                                                    ((uint32_t) R_ACMPHS1 - (uint32_t) R_ACMPHS0) * \
                                                    (channel)))

#define ACMPHS_PRIV_MAX_STATUS_RETRIES     (1024U)

#define ACMPHS_PRIV_US_PER_S               (1000000U)
#define ACMPHS_PRIV_FILTER_WAIT_CLOCKS     (4U)
#define ACMPHS_PRIV_FILTER_DIVISOR_BASE    (4U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
void        comp_hs_int_isr(void);
static void acmphs_hardware_initialize(acmphs_instance_ctrl_t * const p_instance_ctrl);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* ACMPHS Implementation of comparator interface. */
const comparator_api_t g_comparator_on_acmphs =
{
    .open         = R_ACMPHS_Open,
    .outputEnable = R_ACMPHS_OutputEnable,
    .infoGet      = R_ACMPHS_InfoGet,
    .statusGet    = R_ACMPHS_StatusGet,
    .close        = R_ACMPHS_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup ACMPHS
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the comparator and starts operation. Callbacks and pin output are not active until outputEnable() is
 * called. @ref comparator_api_t::outputEnable() should be called after the output has stabilized. Implements
 * @ref comparator_api_t::open().
 *
 * Comparator inputs must be configured in the application code prior to calling this function.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              An input pointer is NULL
 * @retval FSP_ERR_INVALID_ARGUMENT       An argument is invalid. Window mode (COMPARATOR_MODE_WINDOW) and filter of 1
 *                                        (COMPARATOR_FILTER_1) are not supported in this implementation.
 * @retval FSP_ERR_ALREADY_OPEN           The control block is already open or the hardware lock is taken.
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_Open (comparator_ctrl_t * const p_ctrl, comparator_cfg_t const * const p_cfg)
{
    acmphs_instance_ctrl_t * p_instance_ctrl = (acmphs_instance_ctrl_t *) p_ctrl;

#if ACMPHS_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);

    /* COMPARATOR_FILTER_1 and COMPARATOR_MODE_WINDOW are not supported in this implementation. */
    FSP_ERROR_RETURN(COMPARATOR_FILTER_1 != p_cfg->filter, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(COMPARATOR_MODE_WINDOW != p_cfg->mode, FSP_ERR_INVALID_ARGUMENT);

    /* Callback should not be NULL when interrupt is configured */
    if (p_cfg->irq >= 0)
    {
        FSP_ERROR_RETURN(BSP_IRQ_DISABLED != p_cfg->ipl, FSP_ERR_INVALID_ARGUMENT);
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(ACMPHS_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Save the configuration  */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Initialize control block. */
    p_instance_ctrl->p_reg = ACMPHS_REG(p_instance_ctrl->p_cfg->channel);

    /* Configure interrupt priority. The interrupt is disabled until @ref comparator_api_t::outputEnable() is called. */
    if (p_instance_ctrl->p_cfg->irq >= 0)
    {
        R_BSP_IrqCfg(p_instance_ctrl->p_cfg->irq, p_instance_ctrl->p_cfg->ipl, p_instance_ctrl);
    }

    /* Enable clocks to the ACMPHS hardware. */
    R_BSP_MODULE_START(FSP_IP_ACMPHS, p_cfg->channel);

    acmphs_hardware_initialize(p_instance_ctrl);

    /* Mark the control block as open */
    p_instance_ctrl->open = ACMPHS_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the minimum stabilization wait time in microseconds. Implements @ref comparator_api_t::infoGet().
 *
 * @retval  FSP_SUCCESS                Information stored in p_info.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_InfoGet (comparator_ctrl_t * const p_ctrl, comparator_info_t * const p_info)
{
    acmphs_instance_ctrl_t * p_instance_ctrl = (acmphs_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking  */
#if (1 == ACMPHS_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ACMPHS is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(ACMPHS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get the base stabilization time. */
    uint32_t            filter_stabilization_us = 0U;
    comparator_filter_t filter = (comparator_filter_t) p_instance_ctrl->p_reg->CMPCTL_b.CDFS;
    if (COMPARATOR_FILTER_OFF != filter)
    {
        uint32_t pclk_freq_hz = 0;
        pclk_freq_hz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);

        /* Add 4 filter clocks if the filter is enabled. */
        uint32_t divisor;
        divisor                 = ACMPHS_PRIV_FILTER_DIVISOR_BASE << (uint32_t) filter;
        filter_stabilization_us = (ACMPHS_PRIV_FILTER_WAIT_CLOCKS * ACMPHS_PRIV_US_PER_S * divisor) / pclk_freq_hz;

        /* Round up. */
        filter_stabilization_us += 1U;
    }

    p_info->min_stabilization_wait_us = BSP_FEATURE_ACMPHS_MIN_WAIT_TIME_US + filter_stabilization_us;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables the comparator output, which can be polled using @ref comparator_api_t::statusGet(). Also enables pin output and
 * interrupts as configured during @ref comparator_api_t::open(). Implements @ref comparator_api_t::outputEnable().
 *
 * @retval  FSP_SUCCESS                Comparator output is enabled.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_OutputEnable (comparator_ctrl_t * const p_ctrl)
{
    acmphs_instance_ctrl_t * p_instance_ctrl = (acmphs_instance_ctrl_t *) p_ctrl;

#if (1 == ACMPHS_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ACMPHS is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ACMPHS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* NOTE: All write instructions to registers with bits for more than one channel must be
     * in critical sections to ensure the driver is reentrant for different channels. */

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Enable the ACMPHS output. */
    p_instance_ctrl->p_reg->CMPCTL_b.COE = 1U;

    /* Set the VCOUT output setting for this channel (enabled or disabled). */
    p_instance_ctrl->p_reg->CPIOC_b.CPOE = (uint8_t) (p_instance_ctrl->p_cfg->pin_output & 1);

    FSP_CRITICAL_SECTION_EXIT;

    /* Enable interrupts for this channel. */

    if (p_instance_ctrl->p_cfg->irq >= 0)
    {
        R_BSP_IrqEnable(p_instance_ctrl->p_cfg->irq);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the operating status of the comparator. Implements @ref comparator_api_t::statusGet().
 *
 * @retval  FSP_SUCCESS                Operating status of the comparator is provided in p_status.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_TIMEOUT            The debounce filter is off and 2 consecutive matching values were not read within
 *                                     1024 attempts.
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_StatusGet (comparator_ctrl_t * const p_ctrl, comparator_status_t * const p_status)
{
    acmphs_instance_ctrl_t * p_instance_ctrl = (acmphs_instance_ctrl_t *) p_ctrl;

#if (1 == ACMPHS_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ACMPHS is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(ACMPHS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read the operating status of the comparator. */
    if (0U == p_instance_ctrl->p_reg->CMPCTL_b.COE)
    {
        p_status->state = COMPARATOR_STATE_OUTPUT_DISABLED;
    }
    else
    {
        uint8_t state = p_instance_ctrl->p_reg->CMPMON;
        if (COMPARATOR_FILTER_OFF == (comparator_filter_t) p_instance_ctrl->p_reg->CMPCTL_b.CDFS)
        {
            /* Software debounce of 2 consecutive reads is required by the hardware manual if the hardware debounce filter is off. */
            /* See section "50.2.4 Comparator Output Monitor Register (CMPMON)" of the RA6M3 manual R01UH0886EJ0100) */
            uint8_t state2 = p_instance_ctrl->p_reg->CMPMON;

            r_acmphs_extended_cfg_t * p_extend = ((r_acmphs_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend);
            uint32_t retries = p_extend->maximum_status_retries;

            while ((state2 != state) && (retries > 0U))
            {
                state  = state2;
                state2 = p_instance_ctrl->p_reg->CMPMON;
                retries--;
            }

            FSP_ERROR_RETURN(0U != retries, FSP_ERR_TIMEOUT);
        }

        if (1U == state)
        {
            p_status->state = COMPARATOR_STATE_OUTPUT_HIGH;
        }
        else
        {
            p_status->state = COMPARATOR_STATE_OUTPUT_LOW;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops the comparator. Implements @ref comparator_api_t::close().
 *
 * @retval  FSP_SUCCESS                Instance control block closed successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_Close (comparator_ctrl_t * p_ctrl)
{
    acmphs_instance_ctrl_t * p_instance_ctrl = (acmphs_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking*/
#if (1 == ACMPHS_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ACMPHS is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ACMPHS_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Mark driver as closed   */
    p_instance_ctrl->open = 0U;

    /* Disable interrupts. */
    if (p_instance_ctrl->p_cfg->irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->irq, NULL);
    }

    /* Added this to a separate block to avoid redeclaration of
     * critical section variable under module stop macro. */
    {
        /* Stop the comparator and disable output to VCOUT. */
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        p_instance_ctrl->p_reg->CMPCTL       = 0U;
        p_instance_ctrl->p_reg->CPIOC_b.CPOE = 0U;

        FSP_CRITICAL_SECTION_EXIT;
    }

    /* Enter the module-stop state. */
    R_BSP_MODULE_STOP(FSP_IP_ACMPHS, p_instance_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ACMPHS)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Performs hardware initialization of the ACMPLP.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 **********************************************************************************************************************/
static void acmphs_hardware_initialize (acmphs_instance_ctrl_t * const p_instance_ctrl)
{
    /* Set registers controlled by this driver to their default values. */
    p_instance_ctrl->p_reg->CMPCTL       = 0U;
    p_instance_ctrl->p_reg->CPIOC_b.CPOE = 0U;
    p_instance_ctrl->p_reg->CMPSEL0      = 0U;
    p_instance_ctrl->p_reg->CMPSEL1      = 0U;

    uint8_t cmpctl = 0;

    /* Configure the output polarity. */
    cmpctl = (uint8_t) p_instance_ctrl->p_cfg->invert;

    /* Configure the trigger edge. */
    cmpctl |= (uint8_t) (p_instance_ctrl->p_cfg->trigger << R_ACMPHS0_CMPCTL_CEG_Pos);

    /* Configure the hardware debounce filter. */
    cmpctl |= (uint8_t) (p_instance_ctrl->p_cfg->filter << R_ACMPHS0_CMPCTL_CDFS_Pos);

    /* Enable the comparator. */
    cmpctl |= 1 << R_ACMPHS0_CMPCTL_HCMPON_Pos;

    r_acmphs_extended_cfg_t * p_extend = ((r_acmphs_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend);

    /* Configure the internal reference voltage enable */

    /* For ACMPHS modules 0 to 5, VREFEN exists only in ACMPHS0.CPIOC. When using the internal Vref in COMP0 to COMP5,
     * set the VREFEN bit in ACMPHS0.CPIOC to 1. Bit [7] in ACMPHS1.CPIOC to ACMPHS5.CPIOC should be 0 regardless of
     * whether or not the internal Vref is used
     * See section "50.2.5 Comparator Output Control Register (CPIOC)" of the RA6M3 manual R01UH0886EJ0100) */
    if (BSP_FEATURE_ACMPHS_VREF == p_extend->reference_voltage)
    {
        R_MSTP->MSTPCRD_b.MSTPD28 = 0;

        /*Writes to VREFEN bit must be in critical sections to ensure the driver is reentrant for different channels.*/
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        R_ACMPHS0->CPIOC_b.VREFEN = 1;

        FSP_CRITICAL_SECTION_EXIT;
    }

    /* Configure the input and reference voltage for comparator*/
    p_instance_ctrl->p_reg->CMPSEL0 = (uint8_t) p_extend->input_voltage;
    p_instance_ctrl->p_reg->CMPSEL1 = (uint8_t) p_extend->reference_voltage;

    p_instance_ctrl->p_reg->CMPCTL = cmpctl;
}

/*******************************************************************************************************************//**
 * Comparator interrupt
 **********************************************************************************************************************/
void comp_hs_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type                irq    = R_FSP_CurrentIrqGet();
    acmphs_instance_ctrl_t * p_ctrl = (acmphs_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the IRQ flag. */
    R_BSP_IrqStatusClear(irq);

    /* Call user callback if one was provided. */
    comparator_callback_args_t args;
    args.channel   = p_ctrl->p_cfg->channel;
    args.p_context = p_ctrl->p_cfg->p_context;
    p_ctrl->p_cfg->p_callback(&args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
