/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_adc_api.h"

/* Configuration for this package. */
#include "r_sdadc_b_cfg.h"

/* Private header file for this package. */
#include "r_sdadc_b.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SDADC_B_PRIV_8_BITS                 (8U)
#define SDADC_B_OPEN                        (0x53444144U)
#define SDADC_B_REG_ADDRESS(base, idx)    ((uint16_t *) ((uint32_t *) ((uint32_t *) &base + idx)))

#define SDADC_B_INTERNAL_SETUP_TIME         (80)

/* Mask to clear channel bits */
#define SDADC_B_SDADMR_CE_BIT_CLEAR_MASK    (0xFFFF0000U)

/* Mask to get active channels in case of Hybrid sampling mode */
#define SDADC_B_HYBRID_MODE_CHANNEL_MASK    (0x0FU)
#define SDADC_B_MAX_HYBRID_CHANNELS         (SDADC_B_MAX_NUM_CHANNELS / 2)
#define SDADC_B_MAX_CHANNEL_MASK            (0xFFU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

static fsp_err_t r_sdadc_b_open_param_check(sdadc_b_instance_ctrl_t * const p_instance_ctrl,
                                            adc_cfg_t const * const         p_cfg);

#endif

static void r_sdadc_b_open_irq_cfg(sdadc_b_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg);
static void r_sdadc_b_disable_irq(IRQn_Type irq);
static void r_sdadc_scan_configure(sdadc_b_instance_ctrl_t * p_instance_ctrl, sdadc_b_scan_cfg_t const * p_scan_cfg);

void sdadc_b_adi_isr(void);            /* End of SD A/D conversion type 1  */
void sdadc_b_adi2_isr(void);           /* End of SD A/D conversion type 2  */
void sdadc_b_adzc0_isr(void);          /* Zero-cross detection interrupt 0, ch1, ch2 */
void sdadc_b_adzc1_isr(void);          /* Zero-cross detection interrupt 1, ch0, ch3 */

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Keep the FSP ADC interface template, customed function hasn't interface */
/** SDADC_B Implementation of ADC interface. */
const adc_api_t g_adc_on_sdadc_b =
{
    .open           = R_SDADC_B_Open,
    .scanCfg        = R_SDADC_B_ScanCfg,
    .infoGet        = R_SDADC_B_InfoGet,
    .scanStart      = R_SDADC_B_ScanStart,
    .scanGroupStart = R_SDADC_B_ScanGroupStart,
    .scanStop       = R_SDADC_B_ScanStop,
    .scanStatusGet  = R_SDADC_B_StatusGet,
    .offsetSet      = R_SDADC_B_OffsetSet,
    .read           = R_SDADC_B_Read,
    .read32         = R_SDADC_B_Read32,
    .calibrate      = R_SDADC_B_Calibrate,
    .close          = R_SDADC_B_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup SDADC_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Applies power to the SDADC_B and initializes the hardware based on the user configuration. Enabling interrupts which will call a callback to notify the user when a conversion is completed or a zero-cross is detected.
 * Implements @ref adc_api_t::open().
 *
 * @retval  FSP_SUCCESS                Configuration successful.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_ALREADY_OPEN       Control block is already open.
 * @retval  FSP_ERR_INVALID_CHANNEL    Invalid channel configuration
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = FSP_SUCCESS;
    err = r_sdadc_b_open_param_check(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set all p_instance_ctrl fields prior to using it in any functions. */
    p_instance_ctrl->p_cfg = p_cfg;
    sdadc_b_extended_cfg_t const * p_cfg_extend = p_cfg->p_extend;

    /* Start the SDADC. */
    R_BSP_MODULE_START(FSP_IP_SDADC, 0U);

    /* Initialize the hardware based on the configuration. */
    /* Select the operating clock of the digital block */
    R_SDADC_B->SDADCCR = (uint8_t) p_cfg_extend->oper_clk;

    /* Set sampling mode */
    uint32_t sdadmr = (uint32_t) (p_cfg_extend->sampling_mode << R_SDADC_B_SDADMR_FR_Pos);

    /* Set resolution of A/D conversion result */
    sdadmr |= (uint32_t) (ADC_RESOLUTION_16_BIT == p_cfg->resolution) << R_SDADC_B_SDADMR_TYP_Pos;

    R_SDADC_B->SDADMR = sdadmr;

    /* Other hardware configurations: Preamplifier gain, HPF bypass, Phase adjustment */
    r_sdadc_scan_configure(p_instance_ctrl, p_cfg_extend->p_channel_cfg);

    /* Set zero-cross detection configuration */
    R_SDADC_B->SDADICR = p_cfg_extend->zc_detection_setting;

    /* Configure and enable interrupts. */
    r_sdadc_b_open_irq_cfg(p_instance_ctrl, p_cfg);

    /* Mark driver as open by initializing it to "SDAD" - its ASCII equivalent. */
    p_instance_ctrl->opened = SDADC_B_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the enabled channels of the ADC. Implements @ref adc_api_t::scanCfg().
 *
 * @note This function is not compatible with Hybrid Mode operation.
 *
 * @retval  FSP_SUCCESS                Information stored in p_adc_info.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_INVALID_MODE       Hybrid mode channel configuration is invalid
 * @retval  FSP_ERR_INVALID_CHANNEL    Invalid channel configuration
 * @retval  FSP_ERR_INVALID_STATE      Converter operation must be stopped before reconfiguring
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_ScanCfg (adc_ctrl_t * p_ctrl, void const * const p_extend)
{
    sdadc_b_scan_cfg_t const * p_scan_cfg      = (sdadc_b_scan_cfg_t const *) p_extend;
    sdadc_b_instance_ctrl_t  * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_scan_cfg);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    FSP_ERROR_RETURN((SDADC_B_MAX_CHANNEL_MASK >= p_scan_cfg->scan_cfg_mask) && (0U != p_scan_cfg->scan_cfg_mask),
                     FSP_ERR_INVALID_CHANNEL);

    sdadc_b_extended_cfg_t * p_cfg_extend = (sdadc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    bool hybrid_mode = (SDADC_B_HYBRID_SAMPLING_MODE == p_cfg_extend->sampling_mode);

    /* At least two channels are enabled */
    uint32_t channels_match = 0U;
    for (uint8_t i = 0; (i < SDADC_B_MAX_HYBRID_CHANNELS) && hybrid_mode; i++)
    {
        uint32_t channel_mask = (1U << i) | (1U << (i + 4));
        channels_match |= (channel_mask == (p_scan_cfg->scan_cfg_mask & channel_mask));
    }
    FSP_ERROR_RETURN(!hybrid_mode || channels_match, FSP_ERR_INVALID_MODE);
#endif

    /* Verify conversion is stopped */
    FSP_ERROR_RETURN(0U == (R_SDADC_B->SDADMR & (~SDADC_B_SDADMR_CE_BIT_CLEAR_MASK)), FSP_ERR_INVALID_STATE);

    r_sdadc_scan_configure(p_instance_ctrl, p_scan_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the address of the lowest number configured channel, the total number of results to be read in order to
 * read the results of all configured channels, the size of each result, and the ELC event enumerations. Implements
 * @ref adc_api_t::infoGet().
 *
 * @retval  FSP_SUCCESS                Conversion is started successfully.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_InfoGet (adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;
    fsp_err_t                 err             = FSP_SUCCESS;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_info);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Retrieve the scan mask of active channels from the control block */
    uint32_t channel_mask = p_instance_ctrl->channel_mask;

    if (0U == channel_mask)
    {
        p_adc_info->length        = 0U;
        p_adc_info->p_address     = NULL;
        p_adc_info->transfer_size = TRANSFER_SIZE_2_BYTE;
    }
    else
    {
        /* Determine the lowest channel that is configured. */
        uint32_t temp_mask      = 0U;
        int32_t  lowest_channel = -1;
        while (0U == temp_mask)
        {
            lowest_channel++;
            temp_mask = (uint32_t) (channel_mask & (1U << lowest_channel));
        }

        /* Determine the highest channel that is configured. */
        int32_t highest_channel = SDADC_B_MAX_NUM_CHANNELS;
        temp_mask = 0U;
        while (0U == temp_mask)
        {
            highest_channel--;
            temp_mask = (uint32_t) (channel_mask & (1U << highest_channel));
        }

        /* Determine the size of data that must be read to read all the channels between and including the
         * highest and lowest channels. */
        p_adc_info->length = (uint32_t) ((highest_channel - lowest_channel) + 1);

        /* Determine the base address and transfer size. */
        p_adc_info->p_address     = (uint32_t *) &R_SDADC_B->SDADCR0;
        p_adc_info->transfer_size = TRANSFER_SIZE_4_BYTE;
    }

    /* Specify the peripheral name in the ELC list */
    p_adc_info->elc_event      = ELC_EVENT_SDADC0_ADI;
    p_adc_info->elc_peripheral = (elc_peripheral_t) UINT32_MAX;

    /* Set sensor information to invalid value */
    p_adc_info->calibration_data = UINT32_MAX;
    p_adc_info->slope_microvolts = 0U;

    return err;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanStart().
 *
 * @retval  FSP_SUCCESS                Conversion is started successfully.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_ScanStart (adc_ctrl_t * p_ctrl)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;
    fsp_err_t                 err             = FSP_SUCCESS;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    sdadc_b_extended_cfg_t const * p_cfg_extend = (sdadc_b_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
    uint32_t channel_mask = p_instance_ctrl->channel_mask;

    if (SDADC_B_HYBRID_SAMPLING_MODE == p_cfg_extend->sampling_mode)
    {
        channel_mask = channel_mask & SDADC_B_HYBRID_MODE_CHANNEL_MASK;
    }

    /* Set CEn bit to 1 to start conversion */
    R_SDADC_B->SDADMR |= channel_mask;

    /* Set scan status to false, this status flag shall be true after 80 interrupts. */
    p_instance_ctrl->calibration_complete = false;

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanGroupStart is not supported on the SDADC_B. Use scanStart instead.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_ScanGroupStart (adc_ctrl_t * p_ctrl, adc_group_mask_t group_id)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(group_id);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanStop().
 *
 * @note According to Hardware specification, after stopping the conversion, it is necessary to wait at least 1.4us before performing conversion again.
 *
 * @retval  FSP_SUCCESS                Conversion is started successfully.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_ScanStop (adc_ctrl_t * p_ctrl)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->setup_time_cnt = SDADC_B_INTERNAL_SETUP_TIME;

    /* To stop conversion, clear all CEn */
    R_SDADC_B->SDADMR &= SDADC_B_SDADMR_CE_BIT_CLEAR_MASK;

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the status of a scan including calibration scans.
 * Implements @ref adc_api_t::scanStatusGet().
 *
 * @retval FSP_SUCCESS                 Module status stored in the provided pointer p_status
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_StatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the SDADC_B unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Check if converter operation is not started. */
    bool idle_state = (0U == (R_SDADC_B->SDADMR & (~SDADC_B_SDADMR_CE_BIT_CLEAR_MASK)));

    /* Check if calibration is completed. */
    bool scan_state = (p_instance_ctrl->calibration_complete && (0U == p_instance_ctrl->setup_time_cnt));

    p_status->state = (idle_state ? ADC_STATE_IDLE :
                       scan_state ? ADC_STATE_SCAN_IN_PROGRESS : ADC_STATE_CALIBRATION_IN_PROGRESS);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the most recent conversion result from a channel. Truncates 24-bit results to the upper 16 bits. When the SDADC_B is configured for 16-bit resolution, the sign bit is bit 15 and the upper 16 bits are 0.
 * Implements @ref adc_api_t::read().
 *
 * @note The result stored in p_data is signed.
 *
 * @retval  FSP_SUCCESS                Conversion result in p_data.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_INVALID_DATA       Result buffer has not been updated with valid data.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_Read (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(SDADC_B_MAX_NUM_CHANNELS > (uint32_t) reg_id);

    sdadc_b_extended_cfg_t const * p_cfg_extend = (sdadc_b_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;

    /* Read conversion result on CHANNEL_7 only when Hybrid mode is enabled */
    FSP_ASSERT((ADC_CHANNEL_7 != reg_id) || (SDADC_B_HYBRID_SAMPLING_MODE == p_cfg_extend->sampling_mode));
#endif

    /* Check if conversion result has been updated with valid data */
    FSP_ERROR_RETURN(p_instance_ctrl->calibration_complete, FSP_ERR_INVALID_DATA);

    /* Read the most recent conversion value */
    uint16_t result;
    if (ADC_RESOLUTION_24_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        result = (uint16_t) (p_instance_ctrl->results.result[reg_id] >> SDADC_B_PRIV_8_BITS);
    }
    else
    {
        result = (uint16_t) p_instance_ctrl->results.result[reg_id];
    }

    *p_data = result;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the most recent conversion result from a channel. Implements @ref adc_api_t::read32().
 *
 * @note The result stored in p_data is signed.
 * @note When the SDADC is configured for 24-bit resolution,  the upper 8 bits are sign extended.
 *
 * @retval  FSP_SUCCESS                Conversion result in p_data.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_INVALID_DATA       Result buffer has not been updated with valid data.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_Read32 (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(SDADC_B_MAX_NUM_CHANNELS > (uint32_t) reg_id);

    sdadc_b_extended_cfg_t const * p_cfg_extend = (sdadc_b_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;

    /* Read conversion result on CHANNEL_7 only when Hybrid mode is enabled */
    FSP_ASSERT((ADC_CHANNEL_7 != reg_id) || (SDADC_B_HYBRID_SAMPLING_MODE == p_cfg_extend->sampling_mode));
#endif

    /* Check if conversion result has been updated with valid data */
    FSP_ERROR_RETURN(p_instance_ctrl->calibration_complete, FSP_ERR_INVALID_DATA);

    /* Read the most recent conversion value into a 32-bit result. */
    uint32_t result = p_instance_ctrl->results.result[reg_id];

    *p_data = result;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::offsetSet is not supported on the SDADC_B.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_OffsetSet (adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t const offset)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(reg_id);
    FSP_PARAMETER_NOT_USED(offset);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Calibration is performed automatically each time a scan is started.
 * @ref adc_api_t::calibrate is not supported on the SDADC_B.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_Calibrate (adc_ctrl_t * const p_ctrl, void const * p_extend)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_extend);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Stops any scan in progress, disables interrupts, and powers down the SDADC_B peripheral. Implements
 * @ref adc_api_t::close().
 *
 * @retval  FSP_SUCCESS                Instance control block closed successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_B_Close (adc_ctrl_t * p_ctrl)
{
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking*/
#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SDADC_B_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Mark driver as closed   */
    p_instance_ctrl->opened = 0U;

    /* Stop A/D conversion by clear all CEn and PONn bit */
    R_SDADC_B->SDADMR &= (R_SDADC_B_SDADMR_FR_Msk | R_SDADC_B_SDADMR_TYP_Msk);

    /* Disable interrupts. */
    sdadc_b_extended_cfg_t const * p_cfg_extend = (sdadc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    r_sdadc_b_disable_irq(p_cfg_extend->conv_end_irq);
    r_sdadc_b_disable_irq(p_cfg_extend->conv_end_irq2);
    r_sdadc_b_disable_irq(p_cfg_extend->zc_irq);
    r_sdadc_b_disable_irq(p_cfg_extend->zc_irq2);

    /* Stop the input clock for the 24-bit sigma-delta A/D converter (SDADCCLK). */
    R_SDADC_B->SDADCCR = 0x00;

    /* Enter the module-stop state. */
    R_BSP_MODULE_STOP(FSP_IP_SDADC, 0U);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SDADC_B)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if SDADC_B_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Validates the input parameters to open().
 *
 * @param[in]  p_instance_ctrl  Pointer to instance control block
 * @param[in]  p_cfg   Pointer to configuration structure
 *
 * @retval  FSP_SUCCESS                No invalid configurations identified.
 * @retval  FSP_ERR_ALREADY_OPEN       Control block is already open.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_INVALID_CHANNEL    Invalid channel configuration
 **********************************************************************************************************************/
static fsp_err_t r_sdadc_b_open_param_check (sdadc_b_instance_ctrl_t * const p_instance_ctrl,
                                             adc_cfg_t const * const         p_cfg)
{
    /* Verify the pointers are not NULL. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(SDADC_B_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);

    sdadc_b_extended_cfg_t * p_cfg_extend = (sdadc_b_extended_cfg_t *) p_cfg->p_extend;

    /* Verify if at least one channel is enabled */
    FSP_ERROR_RETURN((SDADC_B_MAX_CHANNEL_MASK >= p_cfg_extend->p_channel_cfg->scan_cfg_mask) &&
                     (0U != p_cfg_extend->p_channel_cfg->scan_cfg_mask),
                     FSP_ERR_INVALID_CHANNEL);

    /* SDADC_B only support 16 bit and 24 bit resolution */
    FSP_ASSERT((ADC_RESOLUTION_24_BIT == p_cfg->resolution) || (ADC_RESOLUTION_16_BIT == p_cfg->resolution));

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Configures interrupts and ensures required interrupts are enabled.
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 * @param[in]  p_cfg      Pointer to configuration structure
 *
 * @retval  FSP_SUCCESS                All required interrupts enabled.
 **********************************************************************************************************************/
static void r_sdadc_b_open_irq_cfg (sdadc_b_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg)
{
    sdadc_b_extended_cfg_t const * p_cfg_extend = (sdadc_b_extended_cfg_t *) p_cfg->p_extend;

    /* Set the interrupt priorities. */
    R_BSP_IrqCfgEnable(p_cfg_extend->conv_end_irq, p_cfg_extend->conv_end_ipl, p_instance_ctrl);

    R_BSP_IrqCfgEnable(p_cfg_extend->conv_end_irq2, p_cfg_extend->conv_end_ipl, p_instance_ctrl);

    if (p_cfg_extend->zc_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg_extend->zc_irq, p_cfg_extend->zc_ipl, p_instance_ctrl);
    }

    if (p_cfg_extend->zc_irq2 >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg_extend->zc_irq2, p_cfg_extend->zc_ipl2, p_instance_ctrl);
    }
}

/*******************************************************************************************************************//**
 * Disables an interrupt.
 *
 * @param[in]  irq     Interrupt to disable
 **********************************************************************************************************************/
static void r_sdadc_b_disable_irq (IRQn_Type irq)
{
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Sets the target channels to be converted and hardware configuration for these channels.
 *
 * @param[in]  p_instance_ctrl       Pointer to instance control block
 * @param[in]  p_scan_cfg            New scan configuration
 **********************************************************************************************************************/
static void r_sdadc_scan_configure (sdadc_b_instance_ctrl_t * p_instance_ctrl, sdadc_b_scan_cfg_t const * p_scan_cfg)
{
    sdadc_b_extended_cfg_t * p_cfg_extend = (sdadc_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    uint32_t                 gain_setting = 0U;

    /* Store COF value setting */
    uint32_t hpf_setting =
        (R_SDADC_B_SDADHPFCR_COF_Msk &
         (uint32_t) (p_cfg_extend->p_channel_cfg->hpf_cutoff << R_SDADC_B_SDADHPFCR_COF_Pos));

    /* Set Phase, HPF, and Gain settings for all channels.
     *  - Configuration for disabled channels should be ignored.
     *  - Disregard virtual channel 7, since doesn't have these settings */
    uint8_t max_channel_id = (SDADC_B_MAX_NUM_CHANNELS - 1);
    for (uint8_t i = 0; i < max_channel_id; i++)
    {
        /* Reset cached conversion results */
        p_instance_ctrl->results.result[i] = 0U;

        /* Specify the phase adjustment steps for each channel */
        *SDADC_B_REG_ADDRESS(R_SDADC_B->SDADPHCR0, i) = p_cfg_extend->p_channel_cfg->phase_adjustment[i];

        /* Update HPF bypass setting for each hybrid channel (Type 1) */
        hpf_setting |= (uint32_t) (p_cfg_extend->p_channel_cfg->hpf_setting[i] << i);

        /* Update preamplifier gain for each channel */
        gain_setting |= (uint32_t) (p_cfg_extend->p_channel_cfg->gain_setting[i] << (i * 4U));
    }

    /* Set the preamplifier gain for each channel */
    R_SDADC_B->SDADGCR = gain_setting;

    /* Set phase adjustment for channel 7 - (only effects hybrid mode) */
    if (SDADC_B_HYBRID_SAMPLING_MODE == p_cfg_extend->sampling_mode)
    {
        *SDADC_B_REG_ADDRESS(R_SDADC_B->SDADPHCR0,
                             max_channel_id) = p_cfg_extend->p_channel_cfg->phase_adjustment[max_channel_id];

        /* Enable or disable HPF bypass for each hybrid channel (Type 2) - (only affects hybrid mode) */
        hpf_setting |= (hpf_setting & 0xF) << R_SDADC_B_SDADHPFCR_DIST2_Pos;
    }

    /* Specify whether to use the high-pass filter (HPF) for each channel */
    R_SDADC_B->SDADHPFCR = hpf_setting;

    /* Reset virtual channel 7 - (4KHz hybrid mode channel 3) */
    p_instance_ctrl->results.result[max_channel_id] = 0U;

    /* Set enabled channel mask - Channels are configured twice internally when hybrid mode is enabled
     * SDADMR.PONs should be set after SDADMR.FR
     * (see Section 31.4.2 SFR Access (5) of the manual R01UH1005EJ0051) */
    uint32_t channel_mask = p_scan_cfg->scan_cfg_mask;
    p_instance_ctrl->channel_mask = channel_mask;

    bool hybrid_mode = (SDADC_B_HYBRID_SAMPLING_MODE == p_cfg_extend->sampling_mode);
    channel_mask = (hybrid_mode ? (channel_mask & SDADC_B_HYBRID_MODE_CHANNEL_MASK) : channel_mask);
    uint32_t sdadmr = (R_SDADC_B_SDADMR_TYP_Msk | R_SDADC_B_SDADMR_FR_Msk) & R_SDADC_B->SDADMR;
    sdadmr           |= channel_mask << R_SDADC_B_SDADMR_PON_Pos;
    R_SDADC_B->SDADMR = sdadmr;

    /* r01uh1005ej0050.pdf user manual, 31.4.2. SFR Access: after powering on the Sigma-Delta A/D converter (SDADMR.PONn = 1),
     * internal setup time is necessary. Consequently, the data of the first 80 conversions is invalid. */
    p_instance_ctrl->setup_time_cnt = SDADC_B_INTERNAL_SETUP_TIME;

    /* Set calibration status to false */
    p_instance_ctrl->calibration_complete = false;

    /* Reset SDADC_B and apply new settings */
    R_SDADC_B->SDADRR = 1;
    FSP_REGISTER_READ(R_SDADC_B->SDADRR); // Read register to prevent optimization from removing reset
    R_SDADC_B->SDADRR = 0;
}

/*******************************************************************************************************************//**
 * Conversion type 1 complete interrupt.
 **********************************************************************************************************************/
void sdadc_b_adi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type                 irq             = R_FSP_CurrentIrqGet();
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the BSP IRQ Flag. */
    R_BSP_IrqStatusClear(irq);

    /* Check if internal setup time (first 80 conversions) has been expired */
    if (p_instance_ctrl->setup_time_cnt > 0U)
    {
        p_instance_ctrl->setup_time_cnt--;
    }
    else
    {
        /* Set calibration status to be completed */
        p_instance_ctrl->calibration_complete = true;
        sdadc_b_extended_cfg_t const * p_cfg_extend = (sdadc_b_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;
        uint8_t num_channels =
            (SDADC_B_HYBRID_SAMPLING_MODE !=
             p_cfg_extend->sampling_mode) ? (SDADC_B_MAX_NUM_CHANNELS - 1) : (SDADC_B_MAX_NUM_CHANNELS / 2);

        /* Read the converted result. */
        uint32_t * p_temp_addr = (uint32_t *) &R_SDADC_B->SDADCR0;
        for (uint8_t i = 0U; i < num_channels; i++)
        {
            p_instance_ctrl->results.result[i] = *p_temp_addr;
            p_temp_addr++;
        }

        uint8_t channel_mask = (uint8_t) p_instance_ctrl->channel_mask;
        channel_mask =
            (SDADC_B_HYBRID_SAMPLING_MODE !=
             p_cfg_extend->sampling_mode) ? channel_mask : (channel_mask & SDADC_B_HYBRID_MODE_CHANNEL_MASK);

        /* If a callback was provided, call it with the argument */
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            /* Store the event into the callback argument */
            adc_callback_args_t args = {0};
            args.event        = ADC_EVENT_CONVERSION_COMPLETE;
            args.p_context    = p_instance_ctrl->p_cfg->p_context;
            args.channel_mask = channel_mask;
            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Conversion type 2 complete interrupt.
 **********************************************************************************************************************/
void sdadc_b_adi2_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type                 irq             = R_FSP_CurrentIrqGet();
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the BSP IRQ Flag. */
    R_BSP_IrqStatusClear(irq);

    /* Check if internal setup time (first 80 conversions) has been expired */
    if (0U == p_instance_ctrl->setup_time_cnt)
    {
        sdadc_b_extended_cfg_t const * p_cfg_extend = (sdadc_b_extended_cfg_t const *) p_instance_ctrl->p_cfg->p_extend;

        /* Read type 2 result if using hybrid mode */
        if (SDADC_B_HYBRID_SAMPLING_MODE == p_cfg_extend->sampling_mode)
        {
            uint32_t * p_temp_addr = (uint32_t *) &R_SDADC_B->SDADCR0T2;
            for (uint8_t i = 4U; i < SDADC_B_MAX_NUM_CHANNELS; i++)
            {
                p_instance_ctrl->results.result[i] = *p_temp_addr;
                p_temp_addr++;
            }
        }

        /* If a callback was provided, call it with the argument */
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            /* Store the event into the callback argument */
            adc_callback_args_t args = {0};
            args.event     = ADC_EVENT_CONVERSION_COMPLETE;
            args.p_context = p_instance_ctrl->p_cfg->p_context;
            uint8_t channel_mask = (uint8_t) p_instance_ctrl->channel_mask;

            /* Get enabled channels which are converted in 4kHz Hybrid mode */
            args.channel_mask = channel_mask & (~SDADC_B_HYBRID_MODE_CHANNEL_MASK);
            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Zero-cross detection interrupt 0, ch1, ch2
 **********************************************************************************************************************/
void sdadc_b_adzc0_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type                 irq             = R_FSP_CurrentIrqGet();
    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the BSP IRQ Flag. */
    R_BSP_IrqStatusClear(irq);

    /* Clear the zero-detection interrupt 0 */
    R_SDADC_B->SDADICLR_b.ICL0 = 1U;

    /* Check if internal setup time (first 80 conversions) has been expired */
    if (0U == p_instance_ctrl->setup_time_cnt)
    {
        /* If a callback was provided, call it with the argument */
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            /* Store the event into the callback argument */
            adc_callback_args_t args = {0};
            args.event     = ADC_EVENT_ZERO_CROSS_DETECTION;
            args.p_context = p_instance_ctrl->p_cfg->p_context;
            if (R_SDADC_B->SDADICR_b.ZCCTL0)
            {
                args.channel = ADC_CHANNEL_1;
            }
            else
            {
                args.channel = ADC_CHANNEL_2;
            }

            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * Zero-cross detection interrupt 1, ch0, ch3
 **********************************************************************************************************************/
void sdadc_b_adzc1_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear the BSP IRQ Flag. */
    R_BSP_IrqStatusClear(irq);

    sdadc_b_instance_ctrl_t * p_instance_ctrl = (sdadc_b_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the zero-detection interrupt 1*/
    R_SDADC_B->SDADICLR_b.ICL1 = 1U;

    /* Check if internal setup time (first 80 conversions) has been expired */
    if (0U == p_instance_ctrl->setup_time_cnt)
    {
        /* If a callback was provided, call it with the argument */
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            /* Store the event into the callback argument */
            adc_callback_args_t args = {0};
            args.event     = ADC_EVENT_ZERO_CROSS_DETECTION;
            args.p_context = p_instance_ctrl->p_cfg->p_context;
            if (R_SDADC_B->SDADICR_b.ZCCTL1)
            {
                args.channel = ADC_CHANNEL_0;
            }
            else
            {
                args.channel = ADC_CHANNEL_3;
            }

            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
