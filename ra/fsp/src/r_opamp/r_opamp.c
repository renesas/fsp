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
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_opamp_api.h"
#include "bsp_cfg.h"

/* Configuration for this package. */
#include "r_opamp_cfg.h"

/* Private header file for this package. */
#include "r_opamp.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup OPAMP
 * @{
 **********************************************************************************************************************/
#define OPAMP_OPEN                       (0x4f414d50U)

#define OPAMP_PRIV_AMPMC_LOW_POWER       (0U)
#define OPAMP_PRIV_AMPMC_MIDDLE_SPEED    (0x40U)
#if 2U == BSP_FEATURE_OPAMP_BASE_ADDRESS
 #define OPAMP_PRIV_AMPMC_HIGH_SPEED     (0xC0U)
#else
 #define OPAMP_PRIV_AMPMC_HIGH_SPEED     (0x80U)
#endif
#define OPAMP_CHARGE_PUMP_DELAY_US       (100U)
#define OPAMP_MAX_SWITCH_CHANNELS        (2)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

static void r_opamp_hardware_init(opamp_instance_ctrl_t * const p_instance_ctrl);

/** Lookup table to select the minimum stabilization wait time for respective power mode based on OPAMP Characteristics
 *  Chapter 47 of RA2A1 hardware manual R01UM0008EU0130 and
 *  Chapter 48 of RA4M1 hardware manual R01UM0007EU0110
 */

static const uint32_t g_opamp_stabilization_lookup[] =
{
    [OPAMP_PRIV_AMPMC_LOW_POWER]    = BSP_FEATURE_OPAMP_MIN_WAIT_TIME_LP_US,
    [OPAMP_PRIV_AMPMC_MIDDLE_SPEED] = BSP_FEATURE_OPAMP_MIN_WAIT_TIME_MS_US,
    [OPAMP_PRIV_AMPMC_HIGH_SPEED]   = BSP_FEATURE_OPAMP_MIN_WAIT_TIME_HS_US,
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** OPAMP Implementation of OPAMP interface. */
const opamp_api_t g_opamp_on_opamp =
{
    .open      = R_OPAMP_Open,
    .start     = R_OPAMP_Start,
    .stop      = R_OPAMP_Stop,
    .trim      = R_OPAMP_Trim,
    .infoGet   = R_OPAMP_InfoGet,
    .statusGet = R_OPAMP_StatusGet,
    .close     = R_OPAMP_Close,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Applies power to the OPAMP and initializes the hardware based on the user configuration. Implements
 * @ref opamp_api_t::open.
 *
 * The op-amp is not operational until the @ref opamp_api_t::start is called. If the op-amp is configured to start after
 * AGT compare match, the op-amp is not operational until @ref opamp_api_t::start and the associated AGT compare match
 * event occurs.
 *
 * Some MCUs have switches that must be set before starting the op-amp.  These switches must be set in the application
 * code after @ref opamp_api_t::open and before @ref opamp_api_t::start.
 *
 * Example:
 * @snippet r_opamp_example.c R_OPAMP_Open
 *
 * @retval  FSP_SUCCESS                Configuration successful.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN       Control block is already opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT   An attempt to configure OPAMP in middle speed mode on MCU that does not
 *                                     support middle speed mode.
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_Open (opamp_ctrl_t * const p_api_ctrl, opamp_cfg_t const * const p_cfg)
{
    opamp_instance_ctrl_t * p_ctrl = (opamp_instance_ctrl_t *) p_api_ctrl;

#if OPAMP_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(OPAMP_OPEN != p_ctrl->opened, FSP_ERR_ALREADY_OPEN);

/* If the MCU does not have middle speed */
 #if (!BSP_FEATURE_OPAMP_HAS_MIDDLE_SPEED)

    /* This variant does not support middle speed mode. */
    FSP_ERROR_RETURN(OPAMP_MODE_MIDDLE_SPEED != ((opamp_extended_cfg_t *) p_cfg->p_extend)->mode,
                     FSP_ERR_INVALID_ARGUMENT);
 #endif
#endif

    /* Save pointers for later use */
    p_ctrl->p_cfg = p_cfg;
    opamp_extended_cfg_t * p_cfg_extend = (opamp_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    uint8_t amptrm_val = 0U;
    uint8_t ampmc_val  = 0U;

    /* Appropriately set the available channel based on the MCU */
    amptrm_val |= (uint8_t) p_cfg_extend->trigger_channel_0;
    amptrm_val |= (uint8_t) (p_cfg_extend->trigger_channel_1 << 2U);
    amptrm_val |= (uint8_t) (p_cfg_extend->trigger_channel_2 << 4U);
    amptrm_val |= (uint8_t) (p_cfg_extend->trigger_channel_3 << 6U);

#if (BSP_FEATURE_OPAMP_HAS_MIDDLE_SPEED)
    ampmc_val = (uint8_t) (p_cfg_extend->mode << 6U);
#else

    /* This variant only uses bit 7 for power mode. Clear 6th bit. */
    ampmc_val = (uint8_t) (p_cfg_extend->mode << 6U) & R_OPAMP_AMPMC_AMPSP_Msk;
#endif

    p_ctrl->trim_state = OPAMP_PRIV_TRIM_STATE_INVALID;

    /* Initialize the hardware based on the configuration. */

    R_BSP_MODULE_START(FSP_IP_OPAMP, 0);

    /* Stop operation of all op-amps. */
    R_OPAMP->AMPC = 0U;

    /* Initialize trim registers to factory trim values. */
#if (BSP_FEATURE_OPAMP_TRIM_CAPABLE)
    R_OPAMP->AMPUOTE = 0U;
#endif
    R_OPAMP->AMPMC  = ampmc_val;
    R_OPAMP->AMPTRS = (uint8_t) (p_cfg_extend->agt_link);
    R_OPAMP->AMPTRM = amptrm_val;

    /* Initialize to user defined switches and connection settings if the OPAMP as switches */

    r_opamp_hardware_init(p_ctrl);

    p_ctrl->opened = OPAMP_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the minimum stabilization wait time in microseconds. Implements @ref opamp_api_t::infoGet.
 *
 * * Example:
 * @snippet r_opamp_example.c R_OPAMP_InfoGet
 *
 * @retval  FSP_SUCCESS                information on opamp_power_mode stored in p_info.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_InfoGet (opamp_ctrl_t * const p_api_ctrl, opamp_info_t * const p_info)
{
    opamp_instance_ctrl_t * p_ctrl = (opamp_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Perform parameter checking  */
#if (1 == OPAMP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the OPAMP is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(OPAMP_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    uint8_t power_mode = R_OPAMP->AMPMC;

    p_info->min_stabilization_wait_us = g_opamp_stabilization_lookup[power_mode];

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * If the OPAMP is configured for hardware triggers, enables hardware triggers.  Otherwise, starts the op-amp.
 * Implements @ref opamp_api_t::start.
 *
 * Some MCUs have switches that must be set before starting the op-amp.  These switches must be set in the application
 * code after @ref opamp_api_t::open and before @ref opamp_api_t::start.
 *
 * Example:
 * @snippet r_opamp_example.c R_OPAMP_Start
 *
 * @retval  FSP_SUCCESS                Op-amp started or hardware triggers enabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_INVALID_ARGUMENT   channel_mask includes a channel that does not exist on this MCU.
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_Start (opamp_ctrl_t * const p_api_ctrl, uint32_t const channel_mask)
{
    opamp_instance_ctrl_t * p_ctrl = (opamp_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t               err    = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(p_ctrl);
#if (1 == OPAMP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the OPAMP is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OPAMP_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Make sure all channels in the mask exist. */
    FSP_ERROR_RETURN(BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK == (BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK | channel_mask),
                     FSP_ERR_INVALID_ARGUMENT);
#endif

    /* Enable AGT start and ADC conversion end triggers or start the op-amp channel(s). */

    R_OPAMP->AMPC |= (uint8_t) channel_mask;

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * Stops the op-amp. If the OPAMP is configured for hardware triggers, disables hardware triggers. Implements
 * @ref opamp_api_t::stop.
 *
 *
 * @retval  FSP_SUCCESS                Op-amp stopped or hardware triggers disabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_INVALID_ARGUMENT   channel_mask includes a channel that does not exist on this MCU.
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_Stop (opamp_ctrl_t * const p_api_ctrl, uint32_t const channel_mask)
{
    opamp_instance_ctrl_t * p_ctrl = (opamp_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);
#if (1 == OPAMP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the OPAMP is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OPAMP_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Make sure all channels in the mask exist. */
    FSP_ERROR_RETURN(BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK == (BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK | channel_mask),
                     FSP_ERR_INVALID_ARGUMENT);
#endif

    /* Disable AGT start and ADC conversion end triggers and stop the op-amp channel(s). */

    R_OPAMP->AMPC &= (uint8_t) (~channel_mask);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the operating status for each op-amp in a bitmask. This bit is set when operation begins, before the
 * stabilization wait time has elapsed. Implements @ref opamp_api_t::statusGet.
 *
 *
 * @retval  FSP_SUCCESS                Operating status of each op-amp provided in p_status.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_StatusGet (opamp_ctrl_t * const p_api_ctrl, opamp_status_t * const p_status)
{
    opamp_instance_ctrl_t * p_ctrl = (opamp_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_ctrl);
#if (1 == OPAMP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the OPAMP is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(OPAMP_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Read the operating status of the op-amps. */
    p_status->operating_channel_mask = R_OPAMP->AMPMON;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * On MCUs that support trimming, the op-amp trim register is set to the factory default after open(). This function
 * allows the application to trim the operational amplifier to a user setting, which overwrites the factory default
 * factory trim values.
 *
 * Not supported on all MCUs. See hardware manual for details. Not supported if configured for low power mode
 * (OPAMP_MODE_LOW_POWER).
 *
 * This function is not reentrant.  Only one side of one op-amp can be trimmed at a time. Complete the procedure for
 * one side of one channel before calling trim() with command OPAMP_TRIM_CMD_START again.
 *
 * Implements @ref opamp_api_t::trim.
 *
 * Reference: Section 37.9 "User Offset Trimming" RA2A1 hardware manual R01UM0008EU0130.
 * The trim procedure works as follows:
 *  - Call trim() for the Pch (+) side input with command OPAMP_TRIM_CMD_START.
 *  - Connect a fixed voltage to the Pch (+) input.
 *  - Connect the Nch (-) input to the op-amp output to create a voltage follower.
 *  - Ensure the op-amp is operating and stabilized.
 *  - Call trim() for the Pch (+) side input with command OPAMP_TRIM_CMD_START.
 *  - Measure the fixed voltage connected to the Pch (+) input using the SAR ADC and save the value (referred to as A
 *    later in this procedure).
 *  - Iterate over the following loop 5 times:
 *     - Call trim() for the Pch (+) side input with command OPAMP_TRIM_CMD_NEXT_STEP.
 *     - Measure the op-amp output using the SAR ADC (referred to as B in the next step).
 *     - If A <= B, call trim() for the Pch (+) side input with command OPAMP_TRIM_CMD_CLEAR_BIT.
 *  - Call trim() for the Nch (-) side input with command OPAMP_TRIM_CMD_START.
 *  - Measure the fixed voltage connected to the Pch (+) input using the SAR ADC and save the value (referred to as A
 *    later in this procedure).
 *  - Iterate over the following loop 5 times:
 *     - Call trim() for the Nch (-) side input with command OPAMP_TRIM_CMD_NEXT_STEP.
 *     - Measure the op-amp output using the SAR ADC (referred to as B in the next step).
 *     - If A <= B, call trim() for the Nch (-) side input with command OPAMP_TRIM_CMD_CLEAR_BIT.
 *
 * @retval  FSP_SUCCESS                Conversion result in p_data.
 * @retval  FSP_ERR_UNSUPPORTED        Trimming is not supported on this MCU.
 * @retval  FSP_ERR_INVALID_STATE      The command is not valid in the current state of the trim state machine.
 * @retval  FSP_ERR_INVALID_ARGUMENT   The requested channel is not operating or the trim procedure is not in progress
 *                                     for this channel/input combination.
 * @retval  FSP_ERR_INVALID_MODE       Trim is not allowed in low power mode.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_Trim (opamp_ctrl_t * const            p_api_ctrl,
                        opamp_trim_cmd_t const          cmd,
                        opamp_trim_args_t const * const p_args)
{
    opamp_instance_ctrl_t * p_ctrl = (opamp_instance_ctrl_t *) p_api_ctrl;

#if (1 == OPAMP_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_args);

    /* Verify the pointers are not NULL and ensure the OPAMP is already open. */
    FSP_ERROR_RETURN(OPAMP_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_OPAMP_TRIM_CAPABLE, FSP_ERR_UNSUPPORTED);

    /* Trim not supported in low power mode. */
    FSP_ERROR_RETURN(OPAMP_PRIV_AMPMC_LOW_POWER != R_OPAMP->AMPMC, FSP_ERR_INVALID_MODE);

    /* Make sure the channel exists. */
    FSP_ERROR_RETURN(BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK ==
                     (BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK | (1U << p_args->channel)),
                     FSP_ERR_INVALID_ARGUMENT);
    if (OPAMP_TRIM_CMD_START != cmd)
    {
        /* Make sure the channel is operating. */
        uint8_t operating_channels = R_OPAMP->AMPMON;
        FSP_ERROR_RETURN(operating_channels == (operating_channels | (1U << (uint8_t) p_args->channel)),
                         FSP_ERR_INVALID_ARGUMENT);

        /* Make sure the trim procedure was most recently started for this channel and input. */
        FSP_ERROR_RETURN(p_ctrl->trim_channel == p_args->channel, FSP_ERR_INVALID_ARGUMENT);
        FSP_ERROR_RETURN(p_ctrl->trim_input == p_args->input, FSP_ERR_INVALID_ARGUMENT);
    }
#endif

    /* Enable trimming. */

    R_OPAMP->AMPUOTE |= (uint8_t) (1U << p_args->channel);

    /* Get the trim register for the requested channel and input. */
    uint8_t volatile * p_trim_reg = (uint8_t *) &R_OPAMP->AMPOT + (2 * p_args->channel);
    p_trim_reg += p_args->input;

    if (OPAMP_TRIM_CMD_START == cmd)
    {
        /* OPAMP_PRIV_TRIM_STATE_BEGIN resets the trim procedure and can be called at any time. */
        p_ctrl->trim_state   = OPAMP_PRIV_TRIM_STATE_BEGIN;
        p_ctrl->trim_channel = p_args->channel;
        p_ctrl->trim_input   = p_args->input;

        /* Initialize the trim register to 0 during OPAMP_TRIM_CMD_START. */
        *p_trim_reg = 0U;
    }
    else
    {
        FSP_ERROR_RETURN(OPAMP_PRIV_TRIM_STATE_INVALID != p_ctrl->trim_state, FSP_ERR_INVALID_STATE);
        if (OPAMP_TRIM_CMD_NEXT_STEP == cmd)
        {
            /* OPAMP_TRIM_CMD_NEXT_STEP can only be called 5 times (one for each trim bit). */
            FSP_ERROR_RETURN(OPAMP_PRIV_TRIM_STATE_END != p_ctrl->trim_state, FSP_ERR_INVALID_STATE);
            p_ctrl->trim_state--;

            /* Set the next trim bit during OPAMP_TRIM_CMD_NEXT_STEP. */
            uint8_t mask = (uint8_t) (1U << p_ctrl->trim_state);
            *p_trim_reg |= mask;
        }
        else                           /* (OPAMP_TRIM_CMD_CLEAR_BIT == cmd) */
        {
            /* OPAMP_TRIM_CMD_CLEAR_BIT cannot be used until OPAMP_TRIM_CMD_NEXT_STEP is used at least once. */
            FSP_ERROR_RETURN(OPAMP_PRIV_TRIM_STATE_BEGIN != p_ctrl->trim_state, FSP_ERR_INVALID_STATE);

            /* If the current trim bit is already cleared, return an error. */
            uint8_t mask = (uint8_t) (1U << p_ctrl->trim_state);
            FSP_ERROR_RETURN(0U != (*p_trim_reg & mask), FSP_ERR_INVALID_STATE);

            /* Clear the current trim bit during OPAMP_TRIM_CMD_CLEAR_BIT. */
            *p_trim_reg &= (uint8_t) (~mask);
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops the op-amps. Implements @ref opamp_api_t::close.
 *
 *
 * @retval  FSP_SUCCESS                Instance control block closed successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_OPAMP_Close (opamp_ctrl_t * const p_api_ctrl)
{
    opamp_instance_ctrl_t * p_ctrl = (opamp_instance_ctrl_t *) p_api_ctrl;

    /* Perform parameter checking*/
#if (1 == OPAMP_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the OPAMP is already open. */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OPAMP_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Set all OPAMP units and the reference current generator to be stopped. */
    R_OPAMP->AMPC = 0U;

    /* Mark driver as closed   */
    p_ctrl->opened = 0U;

    /* Enter the module-stop state. */

    R_BSP_MODULE_STOP(FSP_IP_OPAMP, 0);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup OPAMP)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

static void r_opamp_hardware_init (opamp_instance_ctrl_t * const p_instance_ctrl)
{
#if BSP_FEATURE_OPAMP_HAS_SWITCHES

    /* Switches and pin connections are supported through user configurations, configure the respective OPAMP channel,pin and charge pump with respect to configuration settings selected */
    opamp_extended_cfg_t * p_extend = ((opamp_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend);

    /* Clear AMPnMS, AMPnPS, and AMP0OS before setting AMPCPC */
    for (int i = 0; i <= OPAMP_MAX_SWITCH_CHANNELS; i++)
    {
        R_OPAMP->AMP[i].MS = 0x00;
        R_OPAMP->AMP[i].PS = 0x00;
    }

    R_OPAMP->AMP[0].OS = 0x00;

    /* Set PUMPnEN bit while the AMPnMS and AMPnPS registers are 00h (no connection).
     * Additionally, set the PUMP0EN bit when the AMP0OS register is 00h (no connection).
     * Reference: Section 37.2.13 of the RA2A1 hardware manual R01UM0008EU0130. */

    /* AVCC0 = VCC, enable charge pump for respective channel if AVCC0 < 2.7 V
     * Reference: Section 37.2.13 and RA2A1 "Electrical characteristics"- section 47 of RA2A1 hardware manual R01UM0008EU0130 */

 #if BSP_CFG_MCU_VCC_MV < 2700
    uint8_t pump0_enable = 0U;
    uint8_t pump1_enable = 0U;
    uint8_t pump2_enable = 0U;

    (0U == p_extend->minus_input_select_opamp0 && 0U == p_extend->plus_input_select_opamp0 &&
     0U == p_extend->output_select_opamp0) ? (pump0_enable = 0U) : (pump0_enable = 1U);

    (0U == p_extend->minus_input_select_opamp1 &&
     0U == p_extend->plus_input_select_opamp1) ? (pump1_enable = 0U) : (pump1_enable = 1U);

    (0U == p_extend->minus_input_select_opamp2 &&
     0U == p_extend->plus_input_select_opamp2) ? (pump2_enable = 0U) : (pump2_enable = 1U);

    R_OPAMP->AMPCPC = (uint8_t) (pump0_enable | (pump1_enable << 1U) | (pump2_enable << 2U));

    R_BSP_SoftwareDelay(OPAMP_CHARGE_PUMP_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
 #endif

    R_OPAMP->AMP[0].MS = (uint8_t) (p_extend->minus_input_select_opamp0);
    R_OPAMP->AMP[0].PS = (uint8_t) (p_extend->plus_input_select_opamp0);
    R_OPAMP->AMP[0].OS = (uint8_t) (p_extend->output_select_opamp0);
    R_OPAMP->AMP[1].MS = (uint8_t) (p_extend->minus_input_select_opamp1);
    R_OPAMP->AMP[1].PS = (uint8_t) (p_extend->plus_input_select_opamp1);
    R_OPAMP->AMP[2].MS = (uint8_t) (p_extend->minus_input_select_opamp2);
    R_OPAMP->AMP[2].PS = (uint8_t) (p_extend->plus_input_select_opamp2);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
}
