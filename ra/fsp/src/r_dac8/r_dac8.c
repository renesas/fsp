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
#include "r_dac8.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "DAC8" in ASCII, used to determine if channel is open. */
#define DAC8_OPEN         (0x44414338)
#define DAC8_DACS_MASK    (0xFFU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const dac_api_t g_dac_on_dac8 =
{
    .open  = R_DAC8_Open,
    .close = R_DAC8_Close,
    .write = R_DAC8_Write,
    .start = R_DAC8_Start,
    .stop  = R_DAC8_Stop,
};

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup DAC8
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Perform required initialization described in hardware manual.
 *
 * Implements @ref dac_api_t::open.
 *
 * Configures a single DAC channel.  Must be called once prior to calling any other DAC API
 * functions.  After a channel is opened, Open should not be called again for the same channel
 * without calling Close first.
 *
 * @retval FSP_SUCCESS                      The channel was successfully opened.
 * @retval FSP_ERR_ASSERTION                One or both of the following parameters may be NULL: p_ctrl or p_cfg
 * @retval FSP_ERR_ALREADY_OPEN             The instance control structure has already been opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT   An invalid channel was requested.
 * @retval FSP_ERR_NOT_ENABLED              Setting DACADSCR is not enabled when ADCSR.ADST = 0.
 *
 * @note This function is reentrant for different channels.  It is not reentrant for the same channel.
 **********************************************************************************************************************/
fsp_err_t R_DAC8_Open (dac_ctrl_t * const p_ctrl, dac_cfg_t const * const p_cfg)
{
    dac8_instance_ctrl_t * p_instance_ctrl = (dac8_instance_ctrl_t *) p_ctrl;

    /* Validate the input parameters. */
#if DAC8_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(p_cfg->channel < (uint8_t) BSP_FEATURE_DAC8_MAX_CHANNELS, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    FSP_ERROR_RETURN(false == p_instance_ctrl->channel_opened, FSP_ERR_ALREADY_OPEN);
    if ((1U == BSP_FEATURE_DAC8_HAS_DA_AD_SYNCHRONIZE) && (p_cfg->ad_da_synchronized))
    {
        /* Only set this bit while the ADC16 is halted (ADCSR.ADST = 0) and the software trigger is selected as the
         * ADC16 trigger. Refer 35.2.3 D/A A/D Synchronous Start Control Register (DACADSCR) of the RA2A1 manual
         * R01UH0888EJ0100*/
        FSP_ERROR_RETURN(R_ADC0->ADCSR_b.ADST == 0, FSP_ERR_NOT_ENABLED);
    }

    if (1U == BSP_FEATURE_DAC8_HAS_CHARGEPUMP)
    {
        FSP_ASSERT(NULL != p_cfg->p_extend)
    }
#endif

    /* Power on the DAC8 device. */
    R_BSP_MODULE_START(FSP_IP_DAC8, 0U);

    /* Added this to a separate block to avoid redeclaration of
     * critical section variable under module stop macro. */
    {
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        /* Stop the channel. */
        (0U == p_instance_ctrl->channel) ? (R_DAC8->DAM_b.DACE0 = 0U) : (R_DAC8->DAM_b.DACE1 = 0U);

        FSP_CRITICAL_SECTION_EXIT;
    }

    /* Configure the charge pump. */
#if (1U == BSP_FEATURE_DAC8_HAS_CHARGEPUMP)
    R_DAC8->DACPC = (uint8_t) ((dac8_extended_cfg_t *) p_cfg->p_extend)->enable_charge_pump;
#endif

    /* Set DAC8 mode to normal */
    dac8_mode_t dac_mode = DAC8_MODE_NORMAL;

    /* Configure the DAC mode. */
#if (1U == BSP_FEATURE_DAC8_HAS_REALTIME_MODE)
    dac_mode = ((dac8_extended_cfg_t *) p_cfg->p_extend)->dac_mode;
#endif
    if (0U == p_cfg->channel)
    {
        R_DAC8->DAM_b.DAMD0 = (uint8_t) dac_mode & 1U;
    }
    else
    {
        R_DAC8->DAM_b.DAMD1 = (uint8_t) dac_mode & 1U;
    }

    /* Configure the D/A A/D Synchronous Conversion bit. */
#if (1U == BSP_FEATURE_DAC8_HAS_DA_AD_SYNCHRONIZE)
    {
        /* Start ADC unit. Hardcoded to unit 0 as D/A A/D Synchronous support only available on Selected MCU's having
         * single ADC unit */
        R_BSP_MODULE_START(FSP_IP_ADC, 0);

        /* Only set this bit while the ADC16 is halted (ADCSR.ADST = 0) and the software trigger is selected as the
         * ADC16 trigger. Refer 35.2.3 D/A A/D Synchronous Start Control Register (DACADSCR) of the RA2A1 manual
         * R01UH0888EJ0100*/
        R_DAC8->DACADSCR = (uint8_t) p_cfg->ad_da_synchronized;
    }
#endif

    /* Initialize the channel state information. */
    p_instance_ctrl->channel         = p_cfg->channel;
    p_instance_ctrl->channel_started = false;
    p_instance_ctrl->channel_opened  = DAC8_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Write data to the D/A converter.
 *
 * @retval   FSP_SUCCESS           Data is successfully written to the D/A Converter.
 * @retval   FSP_ERR_ASSERTION     p_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Channel associated with p_instance_ctrl has not been opened.
 * @retval   FSP_ERR_OVERFLOW      Data overflow when data value exceeds 8-bit limit.
 **********************************************************************************************************************/
fsp_err_t R_DAC8_Write (dac_ctrl_t * const p_ctrl, uint16_t value)
{
    dac8_instance_ctrl_t * p_instance_ctrl = (dac8_instance_ctrl_t *) p_ctrl;

#if DAC8_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(DAC8_OPEN == p_instance_ctrl->channel_opened, FSP_ERR_NOT_OPEN);

    /* Validate the DAC8 value to be 8 bits */
    FSP_ERROR_RETURN(value <= 0xFFU, FSP_ERR_OVERFLOW);
#endif

    /* Convert to 8 bits. */
    uint8_t dac_value = (uint8_t) value & DAC8_DACS_MASK;

    /* Write the value to D/A converter. */
    R_DAC8->DACS[p_instance_ctrl->channel] = dac_value;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Start the D/A conversion output.
 *
 * @retval   FSP_SUCCESS           The channel is started successfully.
 * @retval   FSP_ERR_ASSERTION     p_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Channel associated with p_instance_ctrl has not been opened.
 * @retval   FSP_ERR_IN_USE        Attempt to re-start a channel.
 **********************************************************************************************************************/
fsp_err_t R_DAC8_Start (dac_ctrl_t * const p_ctrl)
{
    dac8_instance_ctrl_t * p_instance_ctrl = (dac8_instance_ctrl_t *) p_ctrl;

#if DAC8_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(DAC8_OPEN == p_instance_ctrl->channel_opened, FSP_ERR_NOT_OPEN);

    /* Check if the channel is not already started */
    bool channel_started = false;

    channel_started = ((0U == p_instance_ctrl->channel) ? ((bool) R_DAC8->DAM_b.DACE0) : (bool) (R_DAC8->DAM_b.DACE1));
    FSP_ERROR_RETURN(!channel_started, FSP_ERR_IN_USE);
#endif

    /* Enable the output. */
    (0U == p_instance_ctrl->channel) ? (R_DAC8->DAM_b.DACE0 = 1U) : (R_DAC8->DAM_b.DACE1 = 1U);

    /* Update the internal state. */
    p_instance_ctrl->channel_started = true;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Stop the D/A conversion and disable the output signal.
 *
 * @retval  FSP_SUCCESS           The control is successfully stopped.
 * @retval  FSP_ERR_ASSERTION     p_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN      Channel associated with p_instance_ctrl has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_DAC8_Stop (dac_ctrl_t * const p_ctrl)
{
    dac8_instance_ctrl_t * p_instance_ctrl = (dac8_instance_ctrl_t *) p_ctrl;

#if DAC8_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(DAC8_OPEN == p_instance_ctrl->channel_opened, FSP_ERR_NOT_OPEN);
#endif

    /* Disable the output. */
    (0U == p_instance_ctrl->channel) ? (R_DAC8->DAM_b.DACE0 = 0U) : (R_DAC8->DAM_b.DACE1 = 0U);

    /* Mark the internal state. */
    p_instance_ctrl->channel_started = false;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Stop the D/A conversion, stop output, and close the DAC channel.
 *
 * @retval   FSP_SUCCESS           The channel is successfully closed.
 * @retval   FSP_ERR_ASSERTION     p_ctrl is NULL.
 * @retval   FSP_ERR_NOT_OPEN      Channel associated with p_instance_ctrl has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_DAC8_Close (dac_ctrl_t * const p_ctrl)
{
    dac8_instance_ctrl_t * p_instance_ctrl = (dac8_instance_ctrl_t *) p_ctrl;

#if DAC8_CFG_PARAM_CHECKING_ENABLE

    /* Validate the handle parameter */
    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Validate that the channel is opened. */
    FSP_ERROR_RETURN(DAC8_OPEN == p_instance_ctrl->channel_opened, FSP_ERR_NOT_OPEN);
#endif

    /* Stop the channel */
    (0U == p_instance_ctrl->channel) ? (R_DAC8->DAM_b.DACE0 = 0U) : (R_DAC8->DAM_b.DACE1 = 0U);

    /* Update the channel state information. */
    p_instance_ctrl->channel_opened  = 0U;
    p_instance_ctrl->channel_started = false;

    /* All done, return success. */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DAC8)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
