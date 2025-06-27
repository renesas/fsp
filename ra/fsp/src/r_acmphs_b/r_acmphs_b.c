/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_acmphs_b_cfg.h"
#include "r_acmphs_b.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ACMPHS_B_OPEN                       (0x434D5042U) /* CMPB in ascii */

/* Number of channels. */
#define ACMPHS_B_CHANNELS                   (2U)

/* ACMPHS_B registers that are shared between channels are laid out by 1 nibble per channel
 * so 1 byte register is c1 c1 c1 c1 c0 c0 c0 c0 */
#define ACMPHS_B_CHANNEL0_BIT_RESET_MASK    0xF0
#define ACMPHS_B_CHANNEL1_BIT_RESET_MASK    0x0F

#define ACMPHS_B_TRIGGER_TRANSLATE(trigger)    (trigger - 1)

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static void acmphs_b_hardware_initialize(acmphs_b_instance_ctrl_t * const p_instance_ctrl);

/* Maps valid enums to register values. */
static const uint8_t acmphs_b_filter_map[] =
{
    [COMPARATOR_FILTER_OFF] = 0U,
    [COMPARATOR_FILTER_1]   = 1U,
    [COMPARATOR_FILTER_8]   = 2U,
};

/* Used to keep track of opened channels. */
static acmphs_b_instance_ctrl_t * gp_acmphs_b_ctrl[ACMPHS_B_CHANNELS];

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void comp_hs_b_int_isr(void);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* ACMPHS_B Implementation of comparator interface. */
const comparator_api_t g_comparator_on_acmphs_b =
{
    .open         = R_ACMPHS_B_Open,
    .outputEnable = R_ACMPHS_B_OutputEnable,
    .infoGet      = R_ACMPHS_B_InfoGet,
    .statusGet    = R_ACMPHS_B_StatusGet,
    .close        = R_ACMPHS_B_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup ACMPHS_B
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
 * @retval FSP_ERR_INVALID_ARGUMENT       An argument is invalid.  Filter of 16 (COMPARATOR_FILTER_16),
 *                                        filter of 32 (COMPARATOR_FILTER_32) are not supported in this implementation.
 * @retval FSP_ERR_ALREADY_OPEN           The control block is already open or the hardware lock is taken.
 * @retval FSP_ERR_IN_USE                 The channel is already in use.
 * @retval FSP_ERR_INVALID_CHANNEL        Selected channel does not exist.
 * @retval FSP_ERR_UNSUPPORTED            Selected mode not supported by this API
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_B_Open (comparator_ctrl_t * const p_ctrl, comparator_cfg_t const * const p_cfg)
{
    acmphs_b_instance_ctrl_t * p_instance_ctrl = (acmphs_b_instance_ctrl_t *) p_ctrl;

#if ACMPHS_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_ctrl);

    /* COMPARATOR_MODE_WINDOW, COMPARATOR_FILTER_16, COMPARATOR_FILTER_32 are not supported in this implementation. */
    FSP_ERROR_RETURN(COMPARATOR_FILTER_16 != p_cfg->filter, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(COMPARATOR_FILTER_32 != p_cfg->filter, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(COMPARATOR_MODE_WINDOW != p_cfg->mode, FSP_ERR_UNSUPPORTED);

    /* Callback should not be NULL when interrupt is configured */
    if (p_cfg->irq >= 0)
    {
        FSP_ERROR_RETURN(BSP_IRQ_DISABLED != p_cfg->ipl, FSP_ERR_INVALID_ARGUMENT);
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(ACMPHS_B_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN((p_cfg->channel < ACMPHS_B_CHANNELS), FSP_ERR_INVALID_CHANNEL);
    FSP_ERROR_RETURN(NULL == gp_acmphs_b_ctrl[p_cfg->channel], FSP_ERR_IN_USE);
#endif

    /* Save ctrl instance. */
    gp_acmphs_b_ctrl[p_cfg->channel] = p_instance_ctrl;

    /* Save the configuration  */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Configure interrupt priority. The interrupt is disabled until @ref comparator_api_t::outputEnable() is called. */
    if (p_cfg->irq >= 0)
    {
        R_BSP_IrqCfg(p_cfg->irq, p_cfg->ipl, p_ctrl);
    }

    /* Enable clocks to the ACMPHS hardware. Bit MSTPD28*/
    R_BSP_MODULE_START(FSP_IP_ACMPHS, 0);

    acmphs_b_hardware_initialize(p_instance_ctrl);

#if ACMPHS_B_CFG_PARAM_CHECKING_ENABLE

    /* Mark the control block as open */
    p_instance_ctrl->open = ACMPHS_B_OPEN;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the minimum stabilization wait time in microseconds. Implements @ref comparator_api_t::infoGet().
 *
 * @retval  FSP_SUCCESS                Information stored in p_info.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_B_InfoGet (comparator_ctrl_t * const p_ctrl, comparator_info_t * const p_info)
{
    /* Perform parameter checking  */
#if ACMPHS_B_CFG_PARAM_CHECKING_ENABLE
    acmphs_b_instance_ctrl_t * p_instance_ctrl = (acmphs_b_instance_ctrl_t *) p_ctrl;

    /* Verify the pointers are not NULL and ensure the ACMPHS_B is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(ACMPHS_B_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* ACMPHS_B switching delay setting as described in the Step 7 of "Procedure for setting the ACMPHS to Control the Comparators"
     * as seen in Table 28.3 of the R01UH1089EJ0040 Hardware User Manual. */
    p_info->min_stabilization_wait_us = BSP_FEATURE_ACMPHS_MIN_WAIT_TIME_US;

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
fsp_err_t R_ACMPHS_B_OutputEnable (comparator_ctrl_t * const p_ctrl)
{
    acmphs_b_instance_ctrl_t * p_instance_ctrl = (acmphs_b_instance_ctrl_t *) p_ctrl;

#if ACMPHS_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ACMPHS_B is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ACMPHS_B_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* NOTE: All write instructions to registers with bits for more than one channel must be
     * in critical sections to ensure the driver is reentrant for different channels. */

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    if (0U == p_instance_ctrl->p_cfg->channel)
    {
        /* Enable output. */
        R_ACMPHS_B->COMPOCR0_b.C0OE = 1;

        /* Set the VCOUT output setting for this channel (enabled or disabled). */
        R_ACMPHS_B->COMPMDR0_b.C0POE = (uint8_t) (p_instance_ctrl->p_cfg->pin_output & 1U);
    }
    else
    {
        /* Enable output. */
        R_ACMPHS_B->COMPOCR0_b.C1OE = 1;

        /* Set the VCOUT output setting for this channel (enabled or disabled). */
        R_ACMPHS_B->COMPMDR0_b.C1POE = (uint8_t) (p_instance_ctrl->p_cfg->pin_output & 1U);
    }

    FSP_CRITICAL_SECTION_EXIT;

    /* Enable interrupts for this channel. */

    if (p_instance_ctrl->p_cfg->irq >= 0)
    {
        /* Clear pending interrupt before enabling IRQ */
        R_BSP_IrqClearPending(p_instance_ctrl->p_cfg->irq);
        R_BSP_IrqEnable(p_instance_ctrl->p_cfg->irq);
    }

    p_instance_ctrl->output_enabled = 1U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the operating status of the comparator. Implements @ref comparator_api_t::statusGet().
 *
 * @retval  FSP_SUCCESS                Operating status of the comparator is provided in p_status.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_ACMPHS_B_StatusGet (comparator_ctrl_t * const p_ctrl, comparator_status_t * const p_status)
{
    acmphs_b_instance_ctrl_t * p_instance_ctrl = (acmphs_b_instance_ctrl_t *) p_ctrl;

#if ACMPHS_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ACMPHS_B is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(ACMPHS_B_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    uint8_t state = 0;

    if (!p_instance_ctrl->output_enabled)
    {
        p_status->state = COMPARATOR_STATE_OUTPUT_DISABLED;
    }
    else
    {
        /* Read the operating status of the comparator. */
        if (0U == p_instance_ctrl->p_cfg->channel)
        {
            state = R_ACMPHS_B->COMPMDR0_b.C0MON;
        }
        else
        {
            state = R_ACMPHS_B->COMPMDR0_b.C1MON;
        }

        /* Check for Output Polarity Selection */
        if (COMPARATOR_POLARITY_INVERT_ON == p_instance_ctrl->p_cfg->invert)
        {
            state = !state;
        }

        p_status->state = (comparator_state_t) state;
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
fsp_err_t R_ACMPHS_B_Close (comparator_ctrl_t * p_ctrl)
{
    acmphs_b_instance_ctrl_t * p_instance_ctrl = (acmphs_b_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking*/
#if ACMPHS_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ACMPHS is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ACMPHS_B_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable interrupts. */
    if (p_instance_ctrl->p_cfg->irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->irq, NULL);
    }

    uint8_t channelShift = R_ACMPHS_B_COMPMDR0_C1ENB_Pos * p_instance_ctrl->p_cfg->channel;

    /* Added this to a separate block to avoid redeclaration of
     * critical section variable under module stop macro. */
    {
        /* Stop the comparator and disable output to VCOUT. */
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        uint8_t compmdr0 = R_ACMPHS_B->COMPMDR0;
        uint8_t compocr0 = R_ACMPHS_B->COMPOCR0;

        /* Stop the comparator and disable output to VCOUT. */
        R_ACMPHS_B->COMPMDR0 = compmdr0 & ~(uint8_t) ((R_ACMPHS_B_COMPMDR0_C0ENB_Msk | \
                                                       R_ACMPHS_B_COMPMDR0_C0POE_Msk) << channelShift);

        R_ACMPHS_B->COMPOCR0 = compocr0 & ~(uint8_t) ((R_ACMPHS_B_COMPOCR0_C0OE_Msk) << channelShift);

        FSP_CRITICAL_SECTION_EXIT;
    }

    /* Mark output as disabled   */
    p_instance_ctrl->output_enabled = 0U;

    /* Disable interrupt. */
    if (p_instance_ctrl->p_cfg->irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->irq, NULL);
    }

    /* Check if the other channel is in use. */
    acmphs_b_instance_ctrl_t * alt_channel = gp_acmphs_b_ctrl[!p_instance_ctrl->p_cfg->channel];
    if (NULL == alt_channel)
    {
        /* No other channels open. Enter the module-stop state. Bit MSTPD28 */
        R_BSP_MODULE_STOP(FSP_IP_ACMPHS, 0);
    }

#if ACMPHS_B_CFG_PARAM_CHECKING_ENABLE

    /* Mark driver as closed   */
    p_instance_ctrl->open = 0U;
#endif

    gp_acmphs_b_ctrl[p_instance_ctrl->p_cfg->channel] = NULL;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ACMPHS_B)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Performs hardware initialization of the ACMPHS_B.
 *
 * @param[in]  p_instance_ctrl        Instance control block.
 **********************************************************************************************************************/
static void acmphs_b_hardware_initialize (acmphs_b_instance_ctrl_t * const p_instance_ctrl)
{
    r_acmphs_b_extended_cfg_t * p_extend = ((r_acmphs_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend);

    uint8_t channelShift = R_ACMPHS_B_COMPMDR0_C1ENB_Pos * p_instance_ctrl->p_cfg->channel;

    /* Input signal selection*/
    if (0U == p_instance_ctrl->p_cfg->channel)
    {
        /* Set registers controlled by this driver to their default values - channel 0 */
        R_ACMPHS_B->CMP0SEL = 0;

        R_ACMPHS_B->CMP0SEL |= (uint8_t) ((p_extend->input_voltage << R_ACMPHS_B_CMP0SEL_C0INS_Pos) | \
                                          (p_extend->reference_voltage << R_ACMPHS_B_CMP0SEL_C0REFS_Pos));
    }
    else
    {
        /* Set registers controlled by this driver to their default values - channel 1 */
        R_ACMPHS_B->CMP1SEL = 0;

        R_ACMPHS_B->CMP1SEL |= (uint8_t) (p_extend->reference_voltage << R_ACMPHS_B_CMP1SEL_C1REFS_Pos);;
    }

    /* NOTE: All read-modify-write instructions to registers with bits for more than one channel must be
     * in critical sections to ensure the driver is reentrant for different channels. */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Clear all the appropriate bits of the channel we are configuring, 0 is default/disabled */
    R_ACMPHS_B->COMPMDR0 &= (channelShift ? ACMPHS_B_CHANNEL1_BIT_RESET_MASK : ACMPHS_B_CHANNEL0_BIT_RESET_MASK);
    R_ACMPHS_B->COMPOCR0 &= (channelShift ? ACMPHS_B_CHANNEL1_BIT_RESET_MASK : ACMPHS_B_CHANNEL0_BIT_RESET_MASK);
    R_ACMPHS_B->COMPFIR0 &= (channelShift ? ACMPHS_B_CHANNEL1_BIT_RESET_MASK : ACMPHS_B_CHANNEL0_BIT_RESET_MASK);

    uint8_t compmdr0 = R_ACMPHS_B->COMPMDR0;
    uint8_t compocr0 = R_ACMPHS_B->COMPOCR0;
    uint8_t compfir0 = R_ACMPHS_B->COMPFIR0;

    compmdr0 |= (1U << channelShift);

    /* Select whether the digital filter is to be used or not and the sampling clock.
     * Select the edge detection condition for an interrupt request (rising edge, falling edge, or both edges).*/
    compfir0 |= (uint8_t) ((acmphs_b_filter_map[p_instance_ctrl->p_cfg->filter]) |           \
                           ((ACMPHS_B_TRIGGER_TRANSLATE(p_instance_ctrl->p_cfg->trigger)) << \
                            R_ACMPHS_B_COMPFIR0_C0EPO_Pos)) << channelShift;

    /* Set the output of comparator (selecting the logical sense). */
    compocr0 |= (uint8_t) (p_instance_ctrl->p_cfg->invert) << (channelShift + R_ACMPHS_B_COMPOCR0_C0OP_Pos);

    R_ACMPHS_B->COMPOCR0 |= compocr0;
    R_ACMPHS_B->COMPFIR0 |= compfir0;

    /* Enable the comparator. */
    R_ACMPHS_B->COMPMDR0 |= (compmdr0 | (1U << channelShift));

    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 * Comparator interrupt
 **********************************************************************************************************************/
void comp_hs_b_int_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    acmphs_b_instance_ctrl_t * p_ctrl = (acmphs_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

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
