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
#include "r_adc_api.h"

/* Configuration for this package. */
#include "r_sdadc_cfg.h"

/* Private header file for this package. */
#include "r_sdadc.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if BSP_CFG_SDADCCLK_DIV == 8
 #define SDADC_PRIV_CLK_DIV                 (16U)
#elif BSP_CFG_SDADCCLK_DIV == 7
 #define SDADC_PRIV_CLK_DIV                 (12U)
#elif BSP_CFG_SDADCCLK_DIV == 6
 #define SDADC_PRIV_CLK_DIV                 (8U)
#else
 #define SDADC_PRIV_CLK_DIV                 (BSP_CFG_SDADCCLK_DIV + 1U)
#endif

#if BSP_CFG_SDADC_CLOCK_SOURCE == 0
 #define SDADC_PRIV_CLK_INPUT               (BSP_HOCO_HZ)
#else
 #define SDADC_PRIV_CLK_INPUT               (BSP_CFG_XTAL_HZ)
#endif

#define SDADC_PRIV_CLK_HZ                   (SDADC_PRIV_CLK_INPUT / SDADC_PRIV_CLK_DIV)
#define SDADC_PRIV_NORMAL_MODE_CLK_HZ       (4000000U)
#define SDADC_PRIV_LOW_POWER_MODE_CLK_HZ    (500000U)

#if (SDADC_PRIV_CLK_HZ != SDADC_PRIV_NORMAL_MODE_CLK_HZ) && (SDADC_PRIV_CLK_HZ != SDADC_PRIV_LOW_POWER_MODE_CLK_HZ)
 #error "SDADC clock must be 4 MHz"
#endif

#define SDADC_PRIV_VSBIAS_STABILIZATION_US    (80U)

#define SDADC_PRIV_PGAC_DEFAULT               (0x00010040U)
#define SDADC_PRIV_PGAC_PGACVE_SHIFT          (30)
#define SDADC_PRIV_PGAC_PGAOFS_MASK           (0x1F00U)

/* Calibration was measured to take 3.4 ms per channel.  A 10% buffer is added.  So the timeout is 3.4 ms * 5 * 1.10 = 19 ms. */
#define SDADC_PRIV_CALIBRATION_TIMEOUT_US     (19000U)

#define SDADC_PRIV_8_BITS                     (8U)
#define SDADC_PRIV_16_BITS                    (16U)

#define SDADC_OPEN                            (0x53444144U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** SDADC power mode. */
typedef enum e_sdadc_power_mode
{
    SDADC_POWER_MODE_NORMAL    = 0,    ///< Normal mode (reference clock 4 MHz, oversampling clock 1 MHz)
    SDADC_POWER_MODE_LOW_POWER = 1,    ///< Low power mode (reference clock 500 kHz, oversampling clock 125 kHz)
} sdadc_power_mode_t;

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

static fsp_err_t r_sdadc_open_param_check(sdadc_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg);

static fsp_err_t r_sdadc_open_param_check_2(adc_cfg_t const * const p_cfg);

static fsp_err_t r_sdadc_calibrate_param_check(sdadc_instance_ctrl_t * const p_instance_ctrl,
                                               sdadc_calibrate_args_t      * p_calibrate);

#endif

static fsp_err_t r_sdadc_open_irq_cfg(sdadc_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg);

static void r_sdadc_scan_configure(uint32_t scan_mask, adc_mode_t mode, adc_trigger_t trigger);

static void r_sdadc_calibrate_end_restore(sdadc_instance_ctrl_t * const p_instance_ctrl);

static void r_sdadc_disable_irq(IRQn_Type irq);

void sdadc_adi_isr(void);
void sdadc_scanend_isr(void);
void sdadc_caliend_isr(void);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** SDADC Implementation of ADC interface. */
const adc_api_t g_adc_on_sdadc =
{
    .open           = R_SDADC_Open,
    .scanCfg        = R_SDADC_ScanCfg,
    .infoGet        = R_SDADC_InfoGet,
    .scanStart      = R_SDADC_ScanStart,
    .scanGroupStart = R_SDADC_ScanGroupStart,
    .scanStop       = R_SDADC_ScanStop,
    .scanStatusGet  = R_SDADC_StatusGet,
    .offsetSet      = R_SDADC_OffsetSet,
    .read           = R_SDADC_Read,
    .read32         = R_SDADC_Read32,
    .calibrate      = R_SDADC_Calibrate,
    .close          = R_SDADC_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup SDADC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Applies power to the SDADC and initializes the hardware based on the user configuration. As part of this
 * initialization, the SDADC clock is configured and enabled.  If an interrupt priority is non-zero, enables an
 * interrupt which will call a callback to notify the user when a conversion, scan, or calibration is complete.
 * R_SDADC_Calibrate() must be called after this function before using the SDADC if any channels are used in
 * differential mode. Implements @ref adc_api_t::open().
 *
 * @note This function delays at least 2 ms as required by the SDADC power on procedure.
 *
 * @retval  FSP_SUCCESS                Configuration successful.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_ALREADY_OPEN       Control block is already open.
 * @retval  FSP_ERR_IRQ_BSP_DISABLED   A required interrupt is disabled
 **********************************************************************************************************************/
fsp_err_t R_SDADC_Open (adc_ctrl_t * p_ctrl, adc_cfg_t const * const p_cfg)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)
    err = r_sdadc_open_param_check(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set all p_instance_ctrl fields prior to using it in any functions. */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Configure and enable interrupts. */
    err = r_sdadc_open_irq_cfg(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* SDADC clock must be disabled to begin power supply activation. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
#if BSP_CFG_SDADC_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_HOCO
    uint8_t sdadcckcr = 1U;
#else
    uint8_t sdadcckcr = 0U;
#endif
    p_instance_ctrl->calib_status = false;
    R_SYSTEM->SDADCCKCR           = sdadcckcr;

    /* Initialize the hardware based on the configuration. */

    /* Start the SDADC. */
    R_BSP_MODULE_START(FSP_IP_SDADC, 0U);

    /* Apply default settings to unused registers. */

    /* All bits in STC1, ADC1, and PGACn are set during initialization. ADCR, ADAR, and CLBSSR are read-only. STC2 needs to
     * be initialized to ensure all the power is not applied during initialization. */
    R_SDADC0->ADC2   = 0U;
    R_SDADC0->CLBC   = 0U;
    R_SDADC0->CLBSTR = 0U;
    R_SDADC0->STC2   = 0U;

    /* Configure the SDADC clock source and divisor to the clock source selected in the clock configuration. This must be
     * done before the analog power supply is activated (reference Note 1 in section 33.2.1 "Startup Control Register 1
     * (STC1)" of the RA2A1 manual R01UH0888EJ0100. */

    /* Set the A/D conversion operation mode (normal mode). */
    /* Set the reference voltage for sensors (internal or external VREF mode). */
    /* After discussions with the hardware design team, we do not need to step through changes to VSBIAS when BGRPON is 0. */
    sdadc_extended_cfg_t const * p_cfg_extend = p_cfg->p_extend;
    uint32_t stc1 = BSP_CFG_SDADCCLK_DIV | (uint32_t) (SDADC_POWER_MODE_NORMAL << R_SDADC0_STC1_SDADLPM_Pos) |
                    (uint32_t) (p_cfg_extend->vref_src << R_SDADC0_STC1_VREFSEL_Pos) |
                    (uint32_t) (p_cfg_extend->vref_voltage << R_SDADC0_STC1_VSBIAS_Pos);
    R_SDADC0->STC1 = (uint16_t) stc1;

    /* Activate the analog power supply as described in Figure 33.23 "Analog power supply activation flow" of the RA2A1
     * manual R01UH0888EJ0100. */

    /* Supply the 24-bit sigma-delta A/D converter clock (SDADCCLK). */
    R_SYSTEM->SDADCCKCR = sdadcckcr | R_SYSTEM_SDADCCKCR_SDADCCKEN_Msk;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    /* Turn on the power of ADBGR, SBIAS, and ADREG. */
    R_SDADC0->STC2 = R_SDADC0_STC2_BGRPON_Msk;

    /* Stabilization wait time of 2 ms is required between power on of ADBGR/SBIAS/ADREG and VBIAS/channel/SDADC. */
    R_BSP_SoftwareDelay(2U, BSP_DELAY_UNITS_MILLISECONDS);

    /* Turn on the power of VBIAS, channel, and sigma-delta A/D converter. */
    R_SDADC0->STC2 = R_SDADC0_STC2_ADCPON_Msk | R_SDADC0_STC2_BGRPON_Msk;

    /* For each channel: */
    uint32_t scan_mask = 0U;
    for (uint32_t i = 0U; i < SDADC_MAX_NUM_CHANNELS; i++)
    {
        p_instance_ctrl->results.results_32[i] = 0U;
        if (NULL != p_cfg_extend->p_channel_cfgs[i])
        {
            /* Set the oversampling ratio. */
            uint32_t pgac_register_value = p_cfg_extend->p_channel_cfgs[i]->pgac_setting;

            /* If differential mode is used and calibration during open is not skipped, enable calibration on this channel. */
            if (SDADC_CHANNEL_INPUT_DIFFERENTIAL == p_cfg_extend->p_channel_cfgs[i]->pgac_setting_b.input)
            {
                pgac_register_value |= 1U << SDADC_PRIV_PGAC_PGACVE_SHIFT;
            }

            R_SDADC0->PGAC[(adc_channel_t) i] = pgac_register_value;

            /* Enable conversion for the channel. */
            scan_mask |= (1U << i);
        }
        else
        {
            R_SDADC0->PGAC[(adc_channel_t) i] = SDADC_PRIV_PGAC_DEFAULT;
        }
    }

    p_instance_ctrl->scan_mask     = scan_mask;
    p_instance_ctrl->scan_cfg_mask = scan_mask;

    /* Configure enabled channels and autoscan mode. */

    /* If the A/D conversion trigger is ELC hardware events, the hardware events are enabled in
     *  @ref adc_api_t::scanStart(). */
    r_sdadc_scan_configure(p_instance_ctrl->scan_mask, p_cfg->mode, ADC_TRIGGER_SOFTWARE);

    /* Mark driver as open by initializing it to "SDAD" - its ASCII equivalent. */
    p_instance_ctrl->opened = SDADC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the enabled channels of the ADC. Pass a pointer to @ref sdadc_scan_cfg_t to p_extend. Implements
 * @ref adc_api_t::scanCfg().
 *
 * @retval  FSP_SUCCESS                Information stored in p_adc_info.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_ScanCfg (adc_ctrl_t * p_ctrl, void const * const p_extend)
{
    sdadc_scan_cfg_t const * p_scan_cfg      = (sdadc_scan_cfg_t const *) p_extend;
    sdadc_instance_ctrl_t  * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_scan_cfg);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Verify all channels to enable are configured. */
    FSP_ASSERT(p_instance_ctrl->scan_cfg_mask == (p_scan_cfg->scan_mask | p_instance_ctrl->scan_cfg_mask));
#endif

    /* Update the enabled channels. */
    p_instance_ctrl->scan_mask = p_scan_cfg->scan_mask;
    r_sdadc_scan_configure(p_instance_ctrl->scan_mask, p_instance_ctrl->p_cfg->mode, p_instance_ctrl->p_cfg->trigger);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the address of the lowest number configured channel, the total number of results to be read in order to
 * read the results of all configured channels, the size of each result, and the ELC event enumerations. Implements
 * @ref adc_api_t::infoGet().
 *
 * @retval  FSP_SUCCESS                Information stored in p_adc_info.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_InfoGet (adc_ctrl_t * p_ctrl, adc_info_t * p_adc_info)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_adc_info);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Retrieve the scan mask of active channels from the control block */
    uint32_t scan_mask = p_instance_ctrl->scan_mask;

    if (0U == scan_mask)
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
            temp_mask = (uint32_t) (scan_mask & (1U << lowest_channel));
        }

        /* Determine the highest channel that is configured. */
        int32_t highest_channel = SDADC_MAX_NUM_CHANNELS;
        temp_mask = 0U;
        while (0U == temp_mask)
        {
            highest_channel--;
            temp_mask = (uint32_t) (scan_mask & (1U << highest_channel));
        }

        /* Determine the size of data that must be read to read all the channels between and including the
         * highest and lowest channels. */
        p_adc_info->length = (uint32_t) ((highest_channel - lowest_channel) + 1);

        /* Determine the base address and transfer size. */
        p_adc_info->p_address     = (__I uint16_t *) &R_SDADC0->ADCR;
        p_adc_info->transfer_size = TRANSFER_SIZE_4_BYTE;
    }

    /* Specify the peripheral name in the ELC list */
    p_adc_info->elc_event      = ELC_EVENT_SDADC0_ADI;
    p_adc_info->elc_peripheral = ELC_PERIPHERAL_SDADC0;

    /* Set sensor information to invalid value */
    p_adc_info->calibration_data = UINT32_MAX;
    p_adc_info->slope_microvolts = 0U;

    return err;
}

/*******************************************************************************************************************//**
 * If the SDADC is configured for hardware triggers, enables hardware triggers.  Otherwise, starts a scan.
 * Implements @ref adc_api_t::scanStart().
 *
 * @retval  FSP_SUCCESS                Scan started or hardware triggers enabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 * @retval  FSP_ERR_IN_USE             A conversion or calibration is in progress.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_ScanStart (adc_ctrl_t * p_ctrl)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* Conversion cannot be performed if conversion or calibration is already in progress. */
    FSP_ERROR_RETURN(0U == p_instance_ctrl->calib_status, FSP_ERR_IN_USE);
    FSP_ERROR_RETURN(0U == R_SDADC0->ADC2, FSP_ERR_IN_USE);
#endif

    /* If the unit is configured for software triggering, trigger a scan. */
    if (ADC_TRIGGER_SOFTWARE == p_instance_ctrl->p_cfg->trigger)
    {
        R_SDADC0->ADC2 = 1U;
    }
    else
    {
        /* Otherwise, enable hardware triggers. */
        R_SDADC0->ADC1_b.SDADTMD = 1U;
    }

    /* Return the error code */
    return err;
}

/*******************************************************************************************************************//**
 * @ref adc_api_t::scanStart is not supported on the SDADC. Use scanStart instead.
 *
 * @retval FSP_ERR_UNSUPPORTED         Function not supported in this implementation.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_ScanGroupStart (adc_ctrl_t * p_ctrl, adc_group_mask_t group_id)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(group_id);

    /* Return the unsupported error. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * If the SDADC is configured for hardware triggers, disables hardware triggers.  Otherwise, stops any in-progress scan
 * started by software. Implements @ref adc_api_t::scanStop().
 *
 * @retval  FSP_SUCCESS                Scan stopped or hardware triggers disabled successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_ScanStop (adc_ctrl_t * p_ctrl)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* If the unit is configured for software triggering, stop the scan. */
    if (ADC_TRIGGER_SOFTWARE == p_instance_ctrl->p_cfg->trigger)
    {
        R_SDADC0->ADC2 = 0U;
    }
    else
    {
        /* Otherwise, disable hardware triggers. */
        R_SDADC0->ADC1_b.SDADTMD = 0U;
    }

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the status of a scan started by software, including calibration scans.  It is not possible to determine the
 * status of a scan started by a hardware trigger. Implements @ref adc_api_t::scanStatusGet().
 *
 * @retval  FSP_SUCCESS                No software scan or calibration is in progress.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_StatusGet (adc_ctrl_t * p_ctrl, adc_status_t * p_status)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* If calibration is in progress or a scan was triggered by software, scan is in progress. */
    bool calib_status = p_instance_ctrl->calib_status; // non-volatile copy
    p_status->state = (adc_state_t) (calib_status | R_SDADC0->ADC2);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the most recent conversion result from a channel.  Truncates 24-bit results to the upper 16 bits.  Implements
 * @ref adc_api_t::read().
 *
 * @note The result stored in p_data is signed when the SDADC channel is configured in differential mode.
 *
 * @note Do not use this API if the conversion end interrupt (SDADC0_ADI) is used to trigger the DTC unless the
 * interrupt mode is set to TRANSFER_IRQ_EACH.
 *
 * @retval  FSP_SUCCESS                Conversion result in p_data.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_Read (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint16_t * const p_data)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0U != ((1U << (uint32_t) reg_id) & p_instance_ctrl->scan_mask));
#endif

    /* Read the most recent conversion value into a 16-bit result. */
    if (ADC_RESOLUTION_24_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        if (ADC_ALIGNMENT_LEFT == p_instance_ctrl->p_cfg->alignment)
        {
            *p_data = (uint16_t) (p_instance_ctrl->results.results_32[reg_id] >> SDADC_PRIV_16_BITS);
        }
        else
        {
            *p_data = (uint16_t) (p_instance_ctrl->results.results_32[reg_id] >> SDADC_PRIV_8_BITS);
        }
    }
    else
    {
        *p_data = p_instance_ctrl->results.results_16[reg_id];
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the most recent conversion result from a channel. Implements @ref adc_api_t::read32().
 *
 * @note The result stored in p_data is signed when the SDADC channel is configured in differential mode. When the
 * SDADC is configured for 24-bit resolution and right alignment, the sign bit is bit 23, and the upper 8 bits are 0.
 * When the SDADC is configured for 16-bit resolution and right alignment, the sign bit is bit 15, and the upper 16
 * bits are 0.
 *
 * @note Do not use this API if the conversion end interrupt (SDADC0_ADI) is used to trigger the DTC unless the
 * interrupt mode is set to TRANSFER_IRQ_EACH.
 *
 * @retval  FSP_SUCCESS                Conversion result in p_data.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_Read32 (adc_ctrl_t * p_ctrl, adc_channel_t const reg_id, uint32_t * const p_data)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_data);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0U != ((1U << (uint32_t) reg_id) & p_instance_ctrl->scan_mask));
#endif

    /* Read the most recent conversion value into a 32-bit result. */
    uint32_t result = 0U;
    if (ADC_RESOLUTION_24_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        result = p_instance_ctrl->results.results_32[reg_id];
    }
    else
    {
        result = (uint32_t) p_instance_ctrl->results.results_16[reg_id];
        if (ADC_ALIGNMENT_LEFT == p_instance_ctrl->p_cfg->alignment)
        {
            result <<= SDADC_PRIV_16_BITS;
        }
    }

    *p_data = result;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the offset.  Offset is applied after stage 1 of the input channel.  Offset can only be applied when the channel
 * is configured for differential input.  Implements @ref adc_api_t::offsetSet().
 *
 * Note: The offset is cleared if @ref adc_api_t::calibrate() is called.  The offset can be re-applied if necessary
 * after the the callback with event ADC_EVENT_CALIBRATION_COMPLETE is called.
 *
 * @param[in]  p_ctrl      See p_instance_ctrl in @ref adc_api_t::offsetSet().
 * @param[in]  reg_id      See reg_id in @ref adc_api_t::offsetSet().
 * @param[in]  offset      Must be between -15 and 15, offset (mV) = 10.9376 mV * offset_steps / stage 1 gain.
 *
 * @retval  FSP_SUCCESS                Offset updated successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL or an input parameter was invalid.
 * @retval  FSP_ERR_IN_USE             A conversion or calibration is in progress.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_OffsetSet (adc_ctrl_t * const p_ctrl, adc_channel_t const reg_id, int32_t const offset)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT((offset >= -15) && (offset <= 15));
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(0U != ((1U << (uint32_t) reg_id) & p_instance_ctrl->scan_cfg_mask));

    /* The channel must be configured for differential input. */
    FSP_ASSERT(SDADC_CHANNEL_INPUT_DIFFERENTIAL == (sdadc_channel_input_t) R_SDADC0->PGAC_b[reg_id].PGASEL);
#endif

    /* Offset cannot be updated if conversion or calibration is in progress. */
    FSP_ERROR_RETURN(0U == p_instance_ctrl->calib_status, FSP_ERR_IN_USE);
    FSP_ERROR_RETURN(0U == R_SDADC0->ADC2, FSP_ERR_IN_USE);

    /* Set the offset. */
    R_SDADC0->PGAC_b[reg_id].PGAOFS = (uint32_t) offset & 0x1FU;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Requires ::sdadc_calibrate_args_t passed to p_extend. Calibrates the specified channel. Calibration is not required
 * or supported for single-ended mode. Calibration must be completed for differential mode before using the SDADC. A
 * callback with the event ADC_EVENT_CALIBRATION_COMPLETE is called when calibration completes. Implements @ref
 * adc_api_t::calibrate().
 *
 * During external offset calibration, apply a differential voltage of 0 to ANSDnP - ANSDnN, where n is the input
 * channel and ANSDnP is OPAMP0 for channel 4 and ANSDnN is OPAMP1 for channel 4.  Complete external offset calibration
 * before external gain calibration.
 *
 * During external gain calibration apply a voltage between 0.4 V / total_gain and 0.8 V / total_gain.  The
 * differential voltage applied during calibration is corrected to a conversion result of 0x7FFFFF, which is the
 * maximum possible positive differential measurement.
 *
 * This function clears the offset value. If offset is required after calibration, it must be reapplied after
 * calibration is complete using @ref adc_api_t::offsetSet.
 *
 * @retval  FSP_SUCCESS                Calibration began successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_IN_USE             A conversion or calibration is in progress.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_Calibrate (adc_ctrl_t * const p_ctrl, void const * p_extend)
{
    sdadc_instance_ctrl_t  * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;
    sdadc_calibrate_args_t * p_calibrate     = (sdadc_calibrate_args_t *) p_extend;

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)
    fsp_err_t err = r_sdadc_calibrate_param_check(p_instance_ctrl, p_calibrate);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Calibration cannot be performed if conversion or calibration is already in progress. */
    FSP_ERROR_RETURN(0U == p_instance_ctrl->calib_status, FSP_ERR_IN_USE);
    FSP_ERROR_RETURN(0U == R_SDADC0->ADC2, FSP_ERR_IN_USE);
#endif

    p_instance_ctrl->calib_status = 1U;

    /* Calibrate the SDADC as described in Figure 33.27 "Internal calibration flow" and Figure 33.28 "External
     * calibration flow" of the RA2A1 manual R01UH0888EJ0100. */

    /* Select software trigger. */
    /* Select single scan mode. */
    r_sdadc_scan_configure(0U, ADC_MODE_SINGLE_SCAN, ADC_TRIGGER_SOFTWARE);

    /* Enable calibration and clear offset to 0 mV. */
    uint32_t pgac = R_SDADC0->PGAC[p_calibrate->channel];
    pgac &= ~SDADC_PRIV_PGAC_PGAOFS_MASK;
    pgac |= 1U << SDADC_PRIV_PGAC_PGACVE_SHIFT;
    R_SDADC0->PGAC[p_calibrate->channel] = pgac;

    /* Set the calibration mode. */
    R_SDADC0->CLBC = (uint8_t) p_calibrate->mode;

    /* Start calibration. */
    R_SDADC0->CLBSTR = 1U;

    /* Not verifying calibration started by checking CLBSSR because a context switch could cause the setting of CLBSSR
     * to be missed since it clears itself when calibration completes. This could be avoided with a critical section,
     * but CLBSSR is set after 2 PCLKB + 3 SDADCCLK, which could block interrupts for longer than desired depending
     * on the divider of PCLKB. *//* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops any scan in progress, disables interrupts, and powers down the SDADC peripheral. Implements
 * @ref adc_api_t::close().
 *
 * @note This function delays at least 3 us as required by the SDADC24 stop procedure.
 *
 * @retval  FSP_SUCCESS                Instance control block closed successfully.
 * @retval  FSP_ERR_ASSERTION          An input pointer was NULL.
 * @retval  FSP_ERR_NOT_OPEN           Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SDADC_Close (adc_ctrl_t * p_ctrl)
{
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking*/
#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Mark driver as closed   */
    p_instance_ctrl->opened = 0U;

    /* Follow the procedure in Figure 33.30 "SDADC24 stop setting flow" in the RA2A1 manual R01UH0888EJ0100. */

    /* Stop A/D conversion. */
    R_SDADC0->ADC1 = R_SDADC0_ADC1_SDADBMP_Msk;
    R_SDADC0->ADC2 = 0U;

    /* Disable interrupts. */
    sdadc_extended_cfg_t const * p_cfg_extend = (sdadc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    r_sdadc_disable_irq(p_cfg_extend->conv_end_irq);
    r_sdadc_disable_irq(p_instance_ctrl->p_cfg->scan_end_irq);
    r_sdadc_disable_irq(p_instance_ctrl->p_cfg->scan_end_b_irq);

    /* Wait 3 us in normal mode. */
    R_BSP_SoftwareDelay(3U, BSP_DELAY_UNITS_MICROSECONDS);

    /* Turn off the power of VBIAS, channel, and sigma-delta A/D converter. */
    R_SDADC0->STC2 = R_SDADC0_STC2_BGRPON_Msk;

    /* Turn off the power of ADBGR, SBIAS, and ADREG. This must be done after clearing ADCPON according to
     * Figure 33.30 "SDADC24 stop setting flow" in the RA2A1 manual R01UH0888EJ0100. */
    R_SDADC0->STC2 = 0U;

    /* Stop the input clock for the 24-bit sigma-delta A/D converter (SDADCCLK). */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    R_SYSTEM->SDADCCKCR = 0U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    /* Enter the module-stop state. */
    R_BSP_MODULE_STOP(FSP_IP_SDADC, 0U);

    /* Return the error code */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SDADC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Validates the input parameters to open().
 *
 * @param[in]  p_cfg   Pointer to configuration structure
 *
 * @retval  FSP_SUCCESS                No invalid configurations identified.
 * @retval  FSP_ERR_ASSERTION          An input parameter was invalid.
 **********************************************************************************************************************/
static fsp_err_t r_sdadc_open_param_check_2 (adc_cfg_t const * const p_cfg)
{
    /* When single-ended input is selected, oversampling must be 256 and gain at each stage must be 1. */
    sdadc_extended_cfg_t const * p_cfg_extend = (sdadc_extended_cfg_t *) p_cfg->p_extend;
    uint32_t channels_configured              = 0U;
    for (uint32_t i = 0U; i < SDADC_MAX_NUM_CHANNELS; i++)
    {
        if (NULL != p_cfg_extend->p_channel_cfgs[i])
        {
            channels_configured++;
            if (SDADC_CHANNEL_INPUT_SINGLE_ENDED == p_cfg_extend->p_channel_cfgs[i]->pgac_setting_b.input)
            {
                FSP_ASSERT(
                    SDADC_CHANNEL_OVERSAMPLING_256 == p_cfg_extend->p_channel_cfgs[i]->pgac_setting_b.oversampling);
                FSP_ASSERT(SDADC_CHANNEL_STAGE_1_GAIN_1 ==
                           p_cfg_extend->p_channel_cfgs[i]->pgac_setting_b.stage_1_gain);
                FSP_ASSERT(SDADC_CHANNEL_STAGE_2_GAIN_1 ==
                           p_cfg_extend->p_channel_cfgs[i]->pgac_setting_b.stage_2_gain);
            }
        }
    }

    /* At least one channel must be configured */
    FSP_ASSERT(channels_configured > 0U);

    /* Conversion end interrupt is required. */
    FSP_ASSERT(p_cfg_extend->conv_end_irq >= 0);

    /* Callback is required if scan end interrupt is enabled. */
    if (p_cfg->scan_end_irq >= 0)
    {
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }

    return FSP_SUCCESS;
}

#endif

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Validates the input parameters to open().
 *
 * @param[in]  p_instance_ctrl  Pointer to instance control block
 * @param[in]  p_cfg   Pointer to configuration structure
 *
 * @retval  FSP_SUCCESS                No invalid configurations identified.
 * @retval  FSP_ERR_ALREADY_OPEN       Control block is already open.
 * @retval  FSP_ERR_ASSERTION          An input pointer is NULL or an input parameter is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_sdadc_open_param_check (sdadc_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg)
{
    /* Verify the pointers are not NULL. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    /* Verify the control block has not already been initialized. */
    FSP_ERROR_RETURN(SDADC_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);

    /* Resolution must be 24-bit or 16-bit. */
    FSP_ASSERT((ADC_RESOLUTION_24_BIT == p_cfg->resolution) || (ADC_RESOLUTION_16_BIT == p_cfg->resolution));

    /* Group scan mode is not supported. */
    FSP_ASSERT(ADC_MODE_GROUP_SCAN != p_cfg->mode);

    /* External trigger mode is not supported. */
    FSP_ASSERT(ADC_TRIGGER_ASYNC_EXTERNAL != p_cfg->trigger);

    /* If hardware trigger is selected, the product always operates in single scan mode. Reference SDADTMD documentation
     * in section 33.2.4 "Sigma-Delta A/D Converter Control Register 1 (ADC1)" of the RA2A1 manual R01UH0888EJ0100. */
    if (ADC_TRIGGER_SYNC_ELC == p_cfg->trigger)
    {
        FSP_ASSERT(ADC_MODE_SINGLE_SCAN == p_cfg->mode);
    }

    fsp_err_t err = r_sdadc_open_param_check_2(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

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
 * @retval  FSP_ERR_IRQ_BSP_DISABLED   A required interrupt is disabled
 **********************************************************************************************************************/
static fsp_err_t r_sdadc_open_irq_cfg (sdadc_instance_ctrl_t * const p_instance_ctrl, adc_cfg_t const * const p_cfg)
{
    sdadc_extended_cfg_t const * p_cfg_extend = (sdadc_extended_cfg_t *) p_cfg->p_extend;

#if SDADC_CFG_PARAM_CHECKING_ENABLE

    /* Calibration interrupt is required if any channel is configured for differential mode. */
    for (uint32_t i = 0U; i < SDADC_MAX_NUM_CHANNELS; i++)
    {
        if (NULL != p_cfg_extend->p_channel_cfgs[i])
        {
            if (SDADC_CHANNEL_INPUT_DIFFERENTIAL == p_cfg_extend->p_channel_cfgs[i]->pgac_setting_b.input)
            {
                FSP_ERROR_RETURN(FSP_INVALID_VECTOR != p_cfg->scan_end_b_irq, FSP_ERR_IRQ_BSP_DISABLED);
            }
        }
    }
#endif

    /* Set the interrupt priorities. */
    /* scan_end_b_irq is used for the calibration end interrupt for SDADC. */
    if (p_cfg->scan_end_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->scan_end_irq, p_cfg->scan_end_ipl, p_instance_ctrl);
    }

    if (p_cfg->scan_end_b_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->scan_end_b_irq, p_cfg->scan_end_b_ipl, p_instance_ctrl);
    }

    if (p_cfg_extend->conv_end_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg_extend->conv_end_irq, p_cfg_extend->conv_end_ipl, p_instance_ctrl);
    }

    return FSP_SUCCESS;
}

#if (1 == SDADC_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Validates the input parameters to calibrate().
 *
 * @param[in]  p_instance_ctrl        Pointer to instance control block
 * @param[in]  p_calibrate   Pointer to calibration configuration structure
 *
 * @retval  FSP_SUCCESS                No invalid configurations identified.
 * @retval  FSP_ERR_ASSERTION          A required input pointer is NULL or an input parameter is invalid.
 * @retval  FSP_ERR_NOT_OPEN           The instance control block has not been opened.
 **********************************************************************************************************************/
static fsp_err_t r_sdadc_calibrate_param_check (sdadc_instance_ctrl_t * const p_instance_ctrl,
                                                sdadc_calibrate_args_t      * p_calibrate)
{
    /* Verify the pointers are not NULL and ensure the ADC unit is already open. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_calibrate);
    FSP_ERROR_RETURN(SDADC_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);

    /* The channel must be enabled during open. */
    uint32_t channel = (uint32_t) p_calibrate->channel;
    uint32_t mask    = 1U << channel;
    FSP_ASSERT(0U != (mask & p_instance_ctrl->scan_cfg_mask));

    /* The channel must be configured for differential input. */
    FSP_ASSERT(SDADC_CHANNEL_INPUT_DIFFERENTIAL ==
               (sdadc_channel_input_t) R_SDADC0->PGAC_b[p_calibrate->channel].PGASEL);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Sets the scan mask, scan mode, and trigger.
 *
 * @param[in]  scan_mask  Bitmask of enabled channels
 * @param[in]  mode       Single scan or continuous scan mode.
 * @param[in]  trigger    ELC or software trigger.
 **********************************************************************************************************************/
static void r_sdadc_scan_configure (uint32_t scan_mask, adc_mode_t mode, adc_trigger_t trigger)
{
    /* Select which channels to enable conversion on. */
    uint32_t adc1_setting = (~scan_mask & 0x1FU) << R_SDADC0_ADC1_SDADBMP_Pos;

    /* Select AUTOSCAN mode (single scan or continuous scan). */
    uint32_t adc1_mode_bit = !((uint32_t) mode);
    adc1_setting |= adc1_mode_bit;

    /* Select software or hardware (ELC event) trigger. */
    uint32_t adc1_trigger_bit = (uint32_t) trigger & 0x1U;
    adc1_trigger_bit <<= R_SDADC0_ADC1_SDADTMD_Pos;
    adc1_setting      |= adc1_trigger_bit;

    R_SDADC0->ADC1 = adc1_setting;
}

/*******************************************************************************************************************//**
 * Restores settings after calibration.
 *
 * @param[in]  p_instance_ctrl     Pointer to instance control block
 **********************************************************************************************************************/
static void r_sdadc_calibrate_end_restore (sdadc_instance_ctrl_t * const p_instance_ctrl)
{
    /* Disable calibration for all channels. */
    for (uint32_t i = 0U; i < SDADC_MAX_NUM_CHANNELS; i++)
    {
        R_SDADC0->PGAC_b[i].PGACVE = 0U;
    }

    /* Restore scan mask, mode, and trigger. */
    r_sdadc_scan_configure(p_instance_ctrl->scan_mask, p_instance_ctrl->p_cfg->mode, p_instance_ctrl->p_cfg->trigger);

    /* Clear the calibration in progress software flag only after restoring scan mask, mode, and trigger settings. */
    p_instance_ctrl->calib_status = 0U;
}

/*******************************************************************************************************************//**
 * Disables an interrupt.
 *
 * @param[in]  irq     Interrupt to disable
 **********************************************************************************************************************/
static void r_sdadc_disable_irq (IRQn_Type irq)
{
    if (irq >= 0)
    {
        R_BSP_IrqDisable(irq);
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Scan complete interrupt.
 **********************************************************************************************************************/
void sdadc_scanend_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the BSP IRQ Flag. */
    R_BSP_IrqStatusClear(irq);

    /* If a callback was provided, call it with the argument */
    adc_callback_args_t args;
    args.unit = 0U;

    /* Store the event into the callback argument */
    args.event = ADC_EVENT_SCAN_COMPLETE;

    args.p_context = p_instance_ctrl->p_cfg->p_context;
    p_instance_ctrl->p_cfg->p_callback(&args);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Conversion complete interrupt.
 **********************************************************************************************************************/
void sdadc_adi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the BSP IRQ Flag. */
    R_BSP_IrqStatusClear(irq);

    /* Read the converted result. */
    uint32_t      result  = R_SDADC0->ADCR;
    adc_channel_t channel = (adc_channel_t) ((result >> 25) - 1U);
    if (3U == R_SDADC0->PGAC_b[channel].PGAAVE)
    {
        /* If averaging is enabled, read the averaged result. The regular result register is read first to determine
         * the channel number. ADCR contains the last sample in the average if averaging is enabled. */
        result  = R_SDADC0->ADAR;
        channel = (adc_channel_t) ((result >> 25) - 1U);
    }

    /* Mask off the upper 8 bits, which are not part of the result. */
    result = result & R_SDADC0_ADCR_SDADCRD_Msk;

    /* Store the result according to the configured resolution. */
    if (ADC_RESOLUTION_24_BIT == p_instance_ctrl->p_cfg->resolution)
    {
        if (ADC_ALIGNMENT_LEFT == p_instance_ctrl->p_cfg->alignment)
        {
            result <<= SDADC_PRIV_8_BITS;
        }

        p_instance_ctrl->results.results_32[channel] = result;
    }
    else
    {
        result = result >> SDADC_PRIV_8_BITS;
        p_instance_ctrl->results.results_16[channel] = (uint16_t) result;
    }

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        /* Store the event into the callback argument */
        adc_callback_args_t args;
        args.unit  = 0U;
        args.event = ADC_EVENT_CONVERSION_COMPLETE;

        args.channel   = channel;
        args.p_context = p_instance_ctrl->p_cfg->p_context;
        p_instance_ctrl->p_cfg->p_callback(&args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Calibration complete interrupt.
 **********************************************************************************************************************/
void sdadc_caliend_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    sdadc_instance_ctrl_t * p_instance_ctrl = (sdadc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the BSP IRQ Flag. */
    R_BSP_IrqStatusClear(irq);

    /* Restore settings to their pre-calibration values. */
    r_sdadc_calibrate_end_restore(p_instance_ctrl);

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        /* Store the event into the callback argument */
        adc_callback_args_t args;
        args.unit      = 0U;
        args.event     = ADC_EVENT_CALIBRATION_COMPLETE;
        args.p_context = p_instance_ctrl->p_cfg->p_context;
        p_instance_ctrl->p_cfg->p_callback(&args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
