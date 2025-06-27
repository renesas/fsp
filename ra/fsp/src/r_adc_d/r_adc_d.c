/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "r_adc_d_cfg.h"
#include "r_adc_d.h"
#include <stdint.h>

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define ADC_D_OPEN                                (0x41444344) /* ADC_D in ascii */

#define ADC_D_POSITIVE_DISCHARGE_MASK             (R_ADC_D_ADM2_ADREFP_Msk)
#define ADC_D_POSITIVE_CLEAR_MASK                 (~R_ADC_D_ADM2_ADREFP_Msk)

#define ADC_D_ICLK_FREQ_4_TO_32_MHZ               (0U)
#define ADC_D_ICLK_FREQ_1_TO_4_MHZ                (1U)
#define ADC_D_FREQ_4_MHZ                          (4000000U)

#define ADC_D_CONVERT_TO_MICRO_SECOND             (1000000U)
#define ADC_D_FAD_MIN_FREQ_HZ                     (1000000U)
#define ADC_D_IVREF_INPUT_LOW2_MAX_FAD_FREQ_HZ    (16000000U)
#define ADC_D_LOW12_MAX_FAD_FREQ_HZ               (24000000U)

#define ADC_D_ADREFP1_IVREF_MIN_FAD_FREQ_HZ       (1000000U)
#define ADC_D_ADREFP1_IVREF_MAX_FAD_FREQ_HZ       (2000000U)

#define ADC_D_MASK_RESOLUTION_12_BIT_VALUE        (0x0FFFU)

#define ADC_D_SELECT_MODE_DATA_LENGTH             (1U)
#define ADC_D_SCAN_MODE_DATA_LENGTH               (4U)

#define ADC_D_START_HW_TRIGGER                    (7U)

#define R_ADC_D_STATE_ICLK_FREQUENCY()                                           \
    ((R_FSP_SystemClockHzGet(BSP_FEATURE_ADC_CLOCK_SOURCE) > ADC_D_FREQ_4_MHZ) ? \
     ADC_D_ICLK_FREQ_4_TO_32_MHZ : ADC_D_ICLK_FREQ_1_TO_4_MHZ)

#if ADC_D_CFG_INTERNAL_REF_VOLT_ENABLE
 #define ADC_D_STABILIZATION_DELAY_US             (5U)
 #define ADC_D_DISCHARGE_DELAY_US                 (1U)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
#if ADC_D_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_adc_d_scan_cfg_check(adc_d_instance_ctrl_t * const     p_ctrl,
                                        adc_d_channel_cfg_t const * const p_channel_cfg);
static fsp_err_t r_adc_d_open_cfg_check(adc_cfg_t const * const p_cfg);

#endif
static void     r_adc_d_open_sub(adc_d_instance_ctrl_t * const p_ctrl);
static uint32_t r_adc_d_get_adc_frequency(adc_d_clock_div_t div);

#if ADC_D_CFG_INTERRUPT_SUPPORT_ENABLE
void adc_d_scan_end_isr(void);

#endif

/* Select test input channels */
typedef enum e_adc_d_test_channel
{
    ADC_D_TEST_CHANNEL_NORMAL_INPUT = 0, ///< Select normal input
    ADC_D_TEST_CHANNEL_ADVREFM      = 2, ///< Select the (-) side reference voltage as the target for conversion.
    ADC_D_TEST_CHANNEL_ADVREFP      = 3  ///< Select the (+) side reference voltage as the target for conversion.
} adc_d_test_channel_t;

/* The ADCRn register contains the conversion results for all resolutions. This is a 16-bit register but the
 * conversion result begins at different bit positions depending on resolutions and needs to be shifted accordingly  */
uint8_t resolution_read_shift_lut[] =
{
    [ADC_RESOLUTION_8_BIT]  = 8,       ///< Shift read value right 8 bits
    [ADC_RESOLUTION_10_BIT] = 6,       ///< Shift read value right 6 bits
    [ADC_RESOLUTION_12_BIT] = 0,       ///< Shift read value right 0 bits
};

/***********************************************************************************************************************
 * Interrupt Service Routines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* ADC_D Implementation of ADC. */
const adc_api_t g_adc_on_adc_d =
{
    .open           = R_ADC_D_Open,
    .scanCfg        = R_ADC_D_ScanCfg,
    .infoGet        = R_ADC_D_InfoGet,
    .scanStart      = R_ADC_D_ScanStart,
    .scanGroupStart = R_ADC_D_ScanGroupStart,
    .scanStop       = R_ADC_D_ScanStop,
    .scanStatusGet  = R_ADC_D_StatusGet,
    .read           = R_ADC_D_Read,
    .read32         = R_ADC_D_Read32,
    .close          = R_ADC_D_Close,
    .calibrate      = R_ADC_D_Calibrate,
    .offsetSet      = R_ADC_D_OffsetSet,
    .callbackSet    = R_ADC_D_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup ADC_D
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the ADC_D peripheral.
 * If interrupt is enabled, the function registers a callback function for notifying the user when a scan
 * has completed.
 * Implements @ref adc_api_t::open.
 *
 * @retval FSP_SUCCESS                    Module is ready for use.
 * @retval FSP_ERR_ASSERTION              An input argument is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           The instance control structure has already been opened.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       A callback is provided, but the interrupt is not enabled.
 * @retval FSP_ERR_INVALID_HW_CONDITION   Invalid configuration corresponds to condition HardWare UM.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;
#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);

    /* Verify the configuration parameters are valid   */
    fsp_err_t err = r_adc_d_open_cfg_check(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Verify this unit has not already been initialized   */
    FSP_ERROR_RETURN(ADC_D_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);

    /* If a callback is used, then make sure an interrupt is enabled */
    if (NULL != p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(p_cfg->scan_end_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    /* Mark driver as opened by initializing it to "ADC_D" in its ASCII equivalent for this unit. */
    p_instance_ctrl->opened = ADC_D_OPEN;
#endif

    /* Save configurations. */
    p_instance_ctrl->p_cfg      = p_cfg;
    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->p_context  = p_cfg->p_context;

    /* Initialize the hardware based on the configuration. */
    r_adc_d_open_sub(p_instance_ctrl);

#if ADC_D_CFG_INTERRUPT_SUPPORT_ENABLE

    /* Enable interrupts */
    R_BSP_IrqCfgEnable(p_cfg->scan_end_irq, p_cfg->scan_end_ipl, p_instance_ctrl);
#endif

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the ADC_D scan parameters. Channel specific settings are set in this function. Pass a pointer to
 * @ref adc_d_channel_cfg_t to p_channel_cfg.
 *
 * @retval FSP_SUCCESS                    Channel specific settings applied.
 * @retval FSP_ERR_ASSERTION              An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN               Unit is not open.
 * @retval FSP_ERR_INVALID_HW_CONDITION   Invalid configuration corresponds to condition HardWare UM.
 * @retval FSP_ERR_INVALID_STATE          Invalid Scan Configuration.
 * @retval FSP_ERR_INVALID_CHANNEL        Channel is invalid.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_ScanCfg (adc_ctrl_t * p_ctrl, void const * const p_channel_cfg)
{
    adc_d_channel_cfg_t const * p_adc_channel_cfg = (adc_d_channel_cfg_t const *) p_channel_cfg;

#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_channel_cfg);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    fsp_err_t err = r_adc_d_scan_cfg_check(p_instance_ctrl, p_adc_channel_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    uint8_t ads   = ADC_CHANNEL_0;
    uint8_t adtes = ADC_D_TEST_CHANNEL_NORMAL_INPUT;

    if (ADC_CHANNEL_POSITIVE_SIDE_VREF == p_adc_channel_cfg->channel_input)
    {
        adtes = ADC_D_TEST_CHANNEL_ADVREFP;
    }
    else if (ADC_CHANNEL_NEGATIVE_SIDE_VREF == p_adc_channel_cfg->channel_input)
    {
        adtes = ADC_D_TEST_CHANNEL_ADVREFM;
    }
    else
    {
        ads = (uint8_t) p_adc_channel_cfg->channel_input;
    }

    /* Configure input channels mode */
    R_ADC_D->ADS   = ads;
    R_ADC_D->ADTES = adtes;

#if ADC_D_CFG_PARAM_CHECKING_ENABLE

    /* Mark driver as initialized */
    p_instance_ctrl->initialized = ADC_D_OPEN;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements adc_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_NOT_OPEN             Unit is not open.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_CallbackSet (adc_ctrl_t * const          p_api_ctrl,
                               void (                    * p_callback)(adc_callback_args_t *),
                               void * const                p_context,
                               adc_callback_args_t * const p_callback_memory)
{
    adc_d_instance_ctrl_t * p_ctrl = (adc_d_instance_ctrl_t *) p_api_ctrl;
    FSP_PARAMETER_NOT_USED(p_callback_memory);

#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts a software trigger scan or enables the hardware trigger mode for a scan depending on how the triggers were
 * configured in the R_ADC_D_Open call. If the unit was configured for ELC or interrupt hardware triggering, then
 * this function allows the trigger signal to get to the ADC_D. The function is not able to control the generation
 * of the trigger itself.
 *
 * @pre Call R_ADC_D_ScanCfg after R_ADC_D_Open before starting a scan.
 *
 * @retval FSP_SUCCESS                 Scan started (software trigger) or hardware trigger mode enabled.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_D is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     ADC_D is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_ScanStart (adc_ctrl_t * p_ctrl)
{
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking  */
#if ADC_D_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    adc_d_extended_cfg_t * p_extend = (adc_d_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    uint8_t adm0_mask = R_ADC_D_ADM0_ADCE_Msk;
    if (ADC_D_TRIGGER_MODE_NO_WAIT == p_extend->operation_trigger)
    {
        /* Software/Hardware no-wait mode sets ADCE then ADCS. */
        R_ADC_D->ADM0 |= adm0_mask;

        /* In Software/Hardware no-wait mode, it takes 1 us + 2 cycles of the conversion clock (fAD)
         * from the start of operation for the operation to stabilize. */
        uint32_t freq_adc       = r_adc_d_get_adc_frequency(p_extend->conversion_clockdiv);
        uint32_t delay_us_cycle = (uint32_t) (ADC_D_CONVERT_TO_MICRO_SECOND / freq_adc);
        R_BSP_SoftwareDelay((2 * delay_us_cycle) + 1, BSP_DELAY_UNITS_MICROSECONDS);

        adm0_mask |= R_ADC_D_ADM0_ADCS_Msk;
    }
    else if (ADC_D_TRIGGER_SOURCE_SOFTWARE == p_extend->trigger_source)
    {
        /* Software wait mode does not set ADCE, only set ADCS */
        adm0_mask = R_ADC_D_ADM0_ADCS_Msk;
    }
    else
    {
        /* Hardware wait mode does not set ADCS, only set ADCE */
    }

    R_ADC_D->ADM0 |= adm0_mask;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanStart is not supported on the ADC_D. Use scanStart instead.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_ScanGroupStart (adc_ctrl_t * p_ctrl, adc_group_mask_t group_id)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(group_id);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Disables the hardware trigger for a scan or select mode and immediately stops converters.
 * This function will abort conversions.
 *
 * @retval FSP_SUCCESS                 Scan stopped (software trigger) or hardware triggers disabled.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_ScanStop (adc_ctrl_t * p_ctrl)
{
    /* Perform parameter checking */
#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Stops conversion operation */
    /* Stops A/D operation */
    R_ADC_D->ADM0 &= ((uint8_t) ~(R_ADC_D_ADM0_ADCS_Msk | R_ADC_D_ADM0_ADCE_Msk));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides the status of any scan process that was started, including scans started by ELC or interrupts triggers.
 *
 * @note In Hardware no-wait mode, ADCS retains the value 1 after conversion end.
 *
 * @retval FSP_SUCCESS                 Module status stored in the provided pointer p_status.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_D is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_StatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Read the status of the ADCS bit. ADCS is set when a scan is in progress */
    p_status->state = (R_ADC_D->ADM0_b.ADCS ? ADC_STATE_SCAN_IN_PROGRESS : ADC_STATE_IDLE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a channel or sensor.
 *
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     Unit is not initialized.
 * @retval FSP_ERR_INVALID_MODE        Invalid configuration for channel_mode.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_Read (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data)
{
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;
    uint8_t                 adsreg          = R_ADC_D->ADS;
    uint8_t                 adsbit          = adsreg & R_ADC_D_ADS_ADS_Msk;

    /* Perform parameter checking. */
#if ADC_D_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are valid */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);

    /* Verify that the channel is valid */
    if ((reg_id >= ADC_CHANNEL_0) && ((uint32_t) reg_id <= 31U))
    {
        uint32_t requested_channel_mask = (1U << (uint32_t) reg_id);
        FSP_ASSERT(0 != (requested_channel_mask & BSP_FEATURE_ADC_D_CHANNELS));
        if (ADC_D_CHANNEL_MODE_SELECT == ((adc_d_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->channel_mode)
        {
            FSP_ASSERT(reg_id == adsbit);
        }
        else
        {
            FSP_ASSERT(((adsbit + 3) >= reg_id) && (adsbit <= reg_id));
        }
    }
    else
    {
        FSP_ASSERT((((ADC_CHANNEL_TEMPERATURE == reg_id) || (ADC_CHANNEL_VOLT == reg_id)) && (adsreg == reg_id)) ||
                   (ADC_CHANNEL_POSITIVE_SIDE_VREF == reg_id) || (ADC_CHANNEL_NEGATIVE_SIDE_VREF == reg_id));
        FSP_ERROR_RETURN(
            ADC_D_CHANNEL_MODE_SELECT == ((adc_d_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->channel_mode,
            FSP_ERR_INVALID_MODE);
    }
#endif

    adc_d_extended_cfg_t * p_extend         = (adc_d_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint8_t                scan_mode_offset = 0;

    if (ADC_D_CHANNEL_MODE_SCAN == p_extend->channel_mode)
    {
        scan_mode_offset = (uint8_t) ((reg_id - adsbit) % 4);
    }

    *p_data =
        ((R_ADC_D->ADCR[scan_mode_offset]) >>
         resolution_read_shift_lut[p_instance_ctrl->p_cfg->resolution]) &
        ADC_D_MASK_RESOLUTION_12_BIT_VALUE;

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads conversion results from a select/scan channel or sensor register into a 32-bit result.
 *
 *
 * @retval FSP_SUCCESS                 Data read into provided p_data.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_D is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     ADC_D is not initialized.
 * @retval FSP_ERR_INVALID_MODE        Invalid configuration for channel_mode.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_Read32 (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data)
{
    uint16_t result = 0U;

#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_data);
#endif

    fsp_err_t err = R_ADC_D_Read(p_ctrl, reg_id, &result);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    *p_data = result;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get information of address ADCR to reading the data, determine the size of data that must be read,
 * size data of each transfer, name of the ELC event for the peripheral, name of the peripheral in the ELC list
 *
 *
 * @retval FSP_SUCCESS                 Information stored in p_adc_info.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_D is not open.
 * @retval FSP_ERR_NOT_INITIALIZED     ADC_D is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_InfoGet (adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info)
{
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;

#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_info);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->initialized, FSP_ERR_NOT_INITIALIZED);
#endif

    adc_d_extended_cfg_t * p_extend = (adc_d_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* The total number of transfers to read depend on channel mode */
    if (ADC_D_CHANNEL_MODE_SELECT == p_extend->channel_mode)
    {
        p_adc_info->length = ADC_D_SELECT_MODE_DATA_LENGTH;
    }
    else
    {
        p_adc_info->length = ADC_D_SCAN_MODE_DATA_LENGTH;
    }

    /* The size transfer byte after conversion end depend on resolution mode */
    if (ADC_RESOLUTION_8_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        p_adc_info->p_address     = ((uint8_t *) &R_ADC_D->ADCR[0]) + 1;
        p_adc_info->transfer_size = TRANSFER_SIZE_1_BYTE;
    }
    else
    {
        p_adc_info->p_address     = &R_ADC_D->ADCR[0];
        p_adc_info->transfer_size = TRANSFER_SIZE_2_BYTE;
    }

    p_adc_info->elc_peripheral = ELC_PERIPHERAL_AD;
    p_adc_info->elc_event      = ELC_EVENT_ADC0_SCAN_END;

    /* Preset data to invalid value */
    p_adc_info->calibration_data = UINT32_MAX;

    /* Provide the previously retrieved slope information */
    p_adc_info->slope_microvolts = BSP_FEATURE_TSN_SLOPE;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function ends any scan or select mode in progress, disables interrupts, and removes power to the A/D peripheral.
 *
 * @retval FSP_SUCCESS                 Module closed.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            ADC_D is not open.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_Close (adc_ctrl_t * p_ctrl)
{
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;

#if ADC_D_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Mark driver as closed */
    p_instance_ctrl->opened      = 0U;
    p_instance_ctrl->initialized = 0U;
#endif
#if ADC_D_CFG_INTERRUPT_SUPPORT_ENABLE

    /* Disable interrupts. */
    if (p_instance_ctrl->p_cfg->scan_end_irq > 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->scan_end_irq);
    }
#endif
#if !ADC_D_CFG_INTERRUPT_SUPPORT_ENABLE && !ADC_D_CFG_PARAM_CHECKING_ENABLE
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Stops conversion operation */
    /* Stops A/D operation */
    R_ADC_D->ADM0 &= ((uint8_t) ~(R_ADC_D_ADM0_ADCS_Msk | R_ADC_D_ADM0_ADCE_Msk));

    R_BSP_MODULE_STOP(FSP_IP_ADC, 0);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::calibrate is not supported on the ADC_D.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_Calibrate (adc_ctrl_t * const p_ctrl, void const * p_extend)
{
    FSP_PARAMETER_NOT_USED(p_extend);
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_ERROR_LOG(FSP_ERR_UNSUPPORTED);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::offsetSet is not supported on the ADC_D.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_OffsetSet (adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t offset)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(reg_id);
    FSP_PARAMETER_NOT_USED(offset);
    FSP_ERROR_LOG(FSP_ERR_UNSUPPORTED);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Prepare ADC_D to enter snooze mode via a hardware trigger.
 * This function must be called immediately before entering software standby mode in order to allow the configured
 * hardware trigger to transition the MCU from software standby mode to snooze mode and perform an ADC conversion.
 *
 * Supported modes for requesting snooze mode via hardware trigger:
 * - channel_mode = ADC_D_CHANNEL_MODE_SELECT, conversion_operation = ADC_D_CONVERSION_MODE_ONESHOT
 * - channel_mode = ADC_D_CHANNEL_MODE_SCAN,   conversion_operation = ADC_D_CONVERSION_MODE_ONESHOT
 *
 * @param[in] p_ctrl              Pointer to the ADC control block
 *
 * @pre The R_ADC_D_ScanStart must be called in advance.
 *
 * @retval FSP_SUCCESS            ADC is configured to request Snooze mode.
 * @retval FSP_ERR_ASSERTION      An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN       ADC_D is not open.
 * @retval FSP_ERR_INVALID_MODE   ADC is in an invalid mode for requesting Snooze mode.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_SnoozeModePrepare (adc_ctrl_t * const p_ctrl)
{
#if ADC_D_CFG_SNOOZE_SUPPORT_ENABLE
 #if ADC_D_CFG_PARAM_CHECKING_ENABLE
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Verify that the ADC instance is in the correct mode for requesting snooze mode via hardware trigger. */
    adc_d_extended_cfg_t const * p_extend = (adc_d_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    FSP_ERROR_RETURN(ADC_D_TRIGGER_SOURCE_SOFTWARE != p_extend->trigger_source, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(ADC_D_CONVERSION_MODE_ONESHOT == p_extend->conversion_operation, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(ADC_D_TRIGGER_MODE_WAIT == p_extend->operation_trigger, FSP_ERR_INVALID_MODE);

    /* The peripheral clock source must be set to HOCO or MOCO. */
    FSP_ERROR_RETURN(0 == R_SYSTEM->ICLKSCR_b.CKST, FSP_ERR_INVALID_MODE);
    FSP_ERROR_RETURN(0 == R_SYSTEM->FMAINSCR_b.CKST, FSP_ERR_INVALID_MODE);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Set AWC prior to entering software standby mode.
     * See in hardware manual: ADC12 > Snooze Mode Function > A/D Conversion by Inputting a Hardware Trigger */
    R_ADC_D->ADM2_b.AWC = 1;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * After exiting snooze mode, if the ADC_D module was in snooze mode, then this function must be called in order to
 * restore ADC operation to normal mode.
 *
 * @param[in] p_ctrl              Pointer to the ADC control block
 *
 * @retval FSP_SUCCESS            ADC is configured to request Snooze mode.
 * @retval FSP_ERR_INVALID_MODE   ADC is in an invalid mode for requesting Snooze mode.
 **********************************************************************************************************************/
fsp_err_t R_ADC_D_SnoozeModeExit (adc_ctrl_t * const p_ctrl)
{
#if ADC_D_CFG_SNOOZE_SUPPORT_ENABLE
 #if ADC_D_CFG_PARAM_CHECKING_ENABLE
    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ADC_D_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(1 == R_ADC_D->ADM2_b.AWC, FSP_ERR_INVALID_MODE);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Clear AWC after exiting software standby mode.
     * See in hardware manual: ADC12 > Snooze Mode Function > A/D Conversion by Inputting a Hardware Trigger */
    R_ADC_D->ADM2_b.AWC = 0;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ADC_D)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if ADC_D_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Validate the configuration when ADC_D channel is configured
 *
 * @param[in]  p_ctrl                     Pointer to instance control block
 * @param[in]  p_channel_cfg              Pointer to channel configuration
 *
 * @retval FSP_SUCCESS                    No configuration errors detected.
 * @retval FSP_ERR_INVALID_CHANNEL        Channel is invalid.
 * @retval FSP_ERR_INVALID_HW_CONDITION   Invalid configuration corresponds to condition HardWare UM.
 * @retval FSP_ERR_INVALID_STATE          Invalid Scan Configuration.
 **********************************************************************************************************************/
static fsp_err_t r_adc_d_scan_cfg_check (adc_d_instance_ctrl_t * const     p_ctrl,
                                         adc_d_channel_cfg_t const * const p_channel_cfg)
{
    adc_d_instance_ctrl_t * p_instance_ctrl = p_ctrl;
    adc_d_extended_cfg_t  * p_extend        = (adc_d_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    adc_channel_t           channel         = p_channel_cfg->channel_input;

    /* Check if the channel input is valid. */
    if (ADC_D_CHANNEL_MODE_SELECT == p_extend->channel_mode)
    {
        FSP_ERROR_RETURN((BSP_FEATURE_ADC_D_CHANNELS & (1U << (uint32_t) channel)) ||
                         (ADC_CHANNEL_TEMPERATURE == channel) ||
                         (ADC_CHANNEL_VOLT == channel) ||
                         (ADC_CHANNEL_POSITIVE_SIDE_VREF == channel) ||
                         (ADC_CHANNEL_NEGATIVE_SIDE_VREF == channel),
                         FSP_ERR_INVALID_CHANNEL);

        /* Ensure to rewrite the value of the ADISS bit while conversion is stopped. */
        if (1 == R_ADC_D->ADM0_b.ADCE)
        {
            FSP_ERROR_RETURN((ADC_CHANNEL_TEMPERATURE != channel) &&
                             (ADC_CHANNEL_VOLT != channel) &&
                             (ADC_CHANNEL_TEMPERATURE > R_ADC_D->ADS),
                             FSP_ERR_INVALID_STATE);
        }
    }
    else
    {
        FSP_ERROR_RETURN(((1U << (uint32_t) channel) & BSP_FEATURE_ADC_D_SCAN_MODE_CHANNELS), FSP_ERR_INVALID_CHANNEL);
    }

    /* Check invalid configuration when the channel input is internal reference voltage or temperature sensor. */
    if ((ADC_D_CHANNEL_MODE_SELECT == p_extend->channel_mode) &&
        ((ADC_CHANNEL_TEMPERATURE == channel) ||
         (ADC_CHANNEL_VOLT == channel)))
    {
        /* Use normal mode 2 when the internal reference voltage or temperature sensor output voltage is selected
         * as the target for A/D conversion. */
        FSP_ERROR_RETURN((ADC_D_VOLTAGE_MODE_NORMAL_2 == p_extend->operation_voltage) ||
                         (ADC_D_VOLTAGE_MODE_LOW_2 == p_extend->operation_voltage),
                         FSP_ERR_INVALID_HW_CONDITION);

        /* If using operation voltage is low-voltage mode 2, use a conversion clock (fAD)
         * with a frequency no greater than 16 MHz. */
        FSP_ERROR_RETURN((ADC_D_IVREF_INPUT_LOW2_MAX_FAD_FREQ_HZ >=
                          r_adc_d_get_adc_frequency(p_extend->conversion_clockdiv)) ||
                         (ADC_D_VOLTAGE_MODE_LOW_2 != p_extend->operation_voltage),
                         FSP_ERR_INVALID_HW_CONDITION);

        /* The internal reference voltage cannot be used for the positive side reference voltage. */
        FSP_ERROR_RETURN(ADC_D_POSITIVE_VREF_IVREF > p_extend->positive_vref, FSP_ERR_INVALID_HW_CONDITION);

        /* The hardware/software trigger wait mode and one-shot conversion mode cannot be used at the same time. */
        FSP_ERROR_RETURN((ADC_D_CONVERSION_MODE_SEQUENTIAL == p_extend->conversion_operation) ||
                         (ADC_D_TRIGGER_MODE_NO_WAIT == p_extend->operation_trigger),
                         FSP_ERR_INVALID_HW_CONDITION);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validates the configuration arguments for illegal combinations or options.
 *
 * @param[in]  p_cfg                       Pointer to configuration structure.
 *
 * @retval FSP_SUCCESS                     No configuration errors detected.
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 * @retval FSP_ERR_INVALID_HW_CONDITION    Invalid configuration corresponds to condition HardWare UM.
 **********************************************************************************************************************/
static fsp_err_t r_adc_d_open_cfg_check (adc_cfg_t const * const p_cfg)
{
    /* Check if p_cfg is NULL. */
    FSP_ASSERT(NULL != p_cfg);

    adc_d_extended_cfg_t const * p_cfg_extend = (adc_d_extended_cfg_t const *) p_cfg->p_extend;

    /* Get conversion clock (fAD) */
    uint32_t freq_ad_hz = r_adc_d_get_adc_frequency(p_cfg_extend->conversion_clockdiv);

    /* Frequency of the conversion clock (fAD) cannot be lower than 1 MHz. */
    FSP_ERROR_RETURN(freq_ad_hz >= ADC_D_FAD_MIN_FREQ_HZ, FSP_ERR_INVALID_HW_CONDITION);

    /* Checking maximum frequency of the conversion clock (fAD) when operation voltage is Low voltage 1, 2 */
    if ((ADC_D_VOLTAGE_MODE_LOW_1 == p_cfg_extend->operation_voltage) ||
        (ADC_D_VOLTAGE_MODE_LOW_2 == p_cfg_extend->operation_voltage))
    {
        FSP_ERROR_RETURN((ADC_D_LOW12_MAX_FAD_FREQ_HZ >= freq_ad_hz), FSP_ERR_INVALID_HW_CONDITION);
    }

    /* The setting of the ADUL must be greater than that of the ADLL.*/
    FSP_ERROR_RETURN(p_cfg_extend->lower_bound_limit < p_cfg_extend->upper_bound_limit, FSP_ERR_INVALID_HW_CONDITION);

 #if ADC_D_CFG_INTERNAL_REF_VOLT_ENABLE

    /* Check invalid configuration when the internal reference voltage is used for the positive side reference voltage. */
    if (ADC_D_POSITIVE_VREF_IVREF == p_cfg_extend->positive_vref)
    {
        /* Check operation voltage is low-voltage mode 1 or 2. */
        FSP_ERROR_RETURN((ADC_D_VOLTAGE_MODE_LOW_1 == p_cfg_extend->operation_voltage) ||
                         (ADC_D_VOLTAGE_MODE_LOW_2 == p_cfg_extend->operation_voltage),
                         FSP_ERR_INVALID_HW_CONDITION);

        /* Check the conversion clock (fAD) must be in the range from 1 to 2 MHz.*/
        FSP_ERROR_RETURN((ADC_D_ADREFP1_IVREF_MAX_FAD_FREQ_HZ >= freq_ad_hz) &&
                         (ADC_D_ADREFP1_IVREF_MIN_FAD_FREQ_HZ <= freq_ad_hz),
                         FSP_ERR_INVALID_HW_CONDITION);
    }
 #endif

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * The Open function applies power to the A/D peripheral, sets channel selection, operation voltage, divider clock,
 * trigger mode, trigger signal, one-shot and sequent mode, resolution,
 * upper limit and lower limit conversion result values, and reference voltage source.
 *
 * @param[in]  p_ctrl         Pointer to instance control block
 **********************************************************************************************************************/
static void r_adc_d_open_sub (adc_d_instance_ctrl_t * const p_ctrl)
{
    adc_d_instance_ctrl_t * p_instance_ctrl = p_ctrl;
    adc_d_extended_cfg_t  * p_extend        = (adc_d_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Setting the A/D conversion channel selection mode */
    /* Setting the A/D Operation voltage mode */
    /* Setting the A/D divider clock */
    uint8_t adcadm0 =
        (uint8_t) ((p_extend->channel_mode << R_ADC_D_ADM0_ADMD_Pos) |
                   (p_extend->operation_voltage << R_ADC_D_ADM0_LV_Pos) |
                   (p_extend->conversion_clockdiv << R_ADC_D_ADM0_FR_Pos));

    /* Setting trigger mode*/
    /* Setting sequential and one-shot mode */
    /* Setting ICLK input frequency */
    uint8_t adcadm1 =
        (uint8_t) ((uint8_t) (p_extend->operation_trigger << R_ADC_D_ADM1_ADTMD_Pos) |
                   (uint8_t) (p_extend->conversion_operation << R_ADC_D_ADM1_ADSCM_Pos) |
                   (R_ADC_D_STATE_ICLK_FREQUENCY() << R_ADC_D_ADM1_ADLSP_Pos));

    if (ADC_D_TRIGGER_SOURCE_SOFTWARE != p_extend->trigger_source)
    {
        /* Setting Hardware trigger signal */
        adcadm1 |= (uint8_t) ((1 << ADC_D_START_HW_TRIGGER) | (p_extend->trigger_source << R_ADC_D_ADM1_ADTRS_Pos));
    }

    /* Setting resolution */
    /* The upper limit and lower limit conversion result values */
    /* Setting negative side reference voltage */
    uint8_t adcadm2 =
        (uint8_t) ((p_instance_ctrl->p_cfg->resolution << R_ADC_D_ADM2_ADTYP_Pos) |
                   (p_extend->upper_lower_bound << R_ADC_D_ADM2_ADRCK_Pos) |
                   (p_extend->negative_vref << R_ADC_D_ADM2_ADREFM_Pos));

    R_BSP_MODULE_START(FSP_IP_ADC, 0);

    /* Wait 1 μs or longer to start A/D conversion after release from the module-stop state.*/
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);

    /* Setting comparison upper limit */
    R_ADC_D->ADUL = (p_extend->upper_bound_limit);

    /* Setting comparison lower limit */
    R_ADC_D->ADLL = (p_extend->lower_bound_limit);

    /* Set the predetermined values for ADM0, ADM1, ADM2. */
    R_ADC_D->ADM0 = adcadm0;
    R_ADC_D->ADM1 = adcadm1;

#if ADC_D_CFG_INTERNAL_REF_VOLT_ENABLE
    R_ADC_D->ADM2 = adcadm2;

    /* Setting reference voltage source. See in hardware manual: ADC12 > Registers to Control the A/D Converter >
     * Table "Register settings for ADREFP[1:0] rewrite" */
    if (ADC_D_POSITIVE_VREF_IVREF == p_extend->positive_vref)
    {
        /* Discharge */
        R_ADC_D->ADM2 = (adcadm2 | (uint8_t) ADC_D_POSITIVE_DISCHARGE_MASK);

        /* Reference voltage discharge time: 1us */
        R_BSP_SoftwareDelay(ADC_D_DISCHARGE_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
    }
#endif

    /* Setting reference voltage source */
    R_ADC_D->ADM2 = (adcadm2 & (uint8_t) ADC_D_POSITIVE_CLEAR_MASK) |
                    ((uint8_t) (p_extend->positive_vref << R_ADC_D_ADM2_ADREFP_Pos));

#if ADC_D_CFG_INTERNAL_REF_VOLT_ENABLE

    /* Internal reference voltage is selected, Reference voltage stability wait time(A): 5us */
    R_BSP_SoftwareDelay(ADC_D_STABILIZATION_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
#endif
}

/*******************************************************************************************************************//**
 * This function implements calculation frequency of conversion clock (fAD).
 *
 * @param[in] div         Conversion Clock Divider value
 *
 * @return frequency of conversion clock (fAD).
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t r_adc_d_get_adc_frequency (adc_d_clock_div_t div)
{
    /* Remap the divider value fromm the register value to a value that can be shifted for the equivalent divide. This uses less space than a LUT.
     * Example: `div` of value 0 becomes a `shift` of 5 and `div` of value 5 becomes a `shift` of 0. */
    uint8_t shift = (uint8_t) (-(div - ADC_D_CLOCK_DIV_1));

    return SystemCoreClock >> shift;
}

#if ADC_D_CFG_INTERRUPT_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * This function implements the interrupt handler for trigger scan complete.
 **********************************************************************************************************************/
void adc_d_scan_end_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    adc_d_instance_ctrl_t * p_instance_ctrl = (adc_d_instance_ctrl_t *) R_FSP_IsrContextGet(R_FSP_CurrentIrqGet());

    /* Clear NVC_ICPR0 before the A/D conversion operation is resumed */
    R_BSP_IrqClearPending(p_instance_ctrl->p_cfg->scan_end_irq);

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_callback)
    {
        adc_callback_args_t args;
        args.event = ADC_EVENT_SCAN_COMPLETE;

        /* Store the unit number into the callback argument */
        args.unit = p_instance_ctrl->p_cfg->unit;

        /* Initialize the channel to 0.  It is not used in this implementation. */
        args.channel = ADC_CHANNEL_0;

        /* Populate the context field. */
        args.p_context = p_instance_ctrl->p_context;

        /* Call the callback. */
        p_instance_ctrl->p_callback(&args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

#endif
