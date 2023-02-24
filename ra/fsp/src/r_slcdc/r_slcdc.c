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
#include "r_slcdc.h"
#include "r_slcdc_cfg.h"
#include "r_slcdc_api.h"
#include "string.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "SLCD" in ASCII, used to determine if the module is open */
#define SLCDC_OPEN                          (0x534C4344U)
#define SLCDC_CLOSED                        (0x00000000U)

#define SLCDC_PRV_LCDM1_LCDSEL_BLON         (0x18)
#define SLCDC_PRV_LCDM1_SCOC_LCDON          (0xC0)
#define SLCDC_PRV_LCDM1_LCDVLM_THRESHOLD    (3300)
#define SLCDC_PRV_VLCD_CONTRAST_OFFSET      (4)
#define SLCDC_PRV_CONTRAST_MAX_4BIAS        (SLCDC_CONTRAST_6)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

#if SLCDC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_slcdc_check_display_mode(slcdc_cfg_t const * const p_cfg);

#endif

static fsp_err_t r_slcdc_clock_operation(slcdc_cfg_t const * const p_cfg);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** SLCDC HAL module API function pointer list */
const slcdc_api_t g_slcdc_on_slcdc =
{
    .open           = R_SLCDC_Open,
    .write          = R_SLCDC_Write,
    .modify         = R_SLCDC_Modify,
    .start          = R_SLCDC_Start,
    .stop           = R_SLCDC_Stop,
    .setContrast    = R_SLCDC_SetContrast,
    .setDisplayArea = R_SLCDC_SetDisplayArea,
    .close          = R_SLCDC_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup SLCDC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the SLCDC driver. Implements slcdc_api_t::open.
 *
 * @retval  FSP_SUCCESS                    Device was opened successfully.
 * @retval  FSP_ERR_ASSERTION              Pointer to the control block or the configuration structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval  FSP_ERR_UNSUPPORTED            Invalid display mode.
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_Open (slcdc_ctrl_t * const p_ctrl, slcdc_cfg_t const * const p_cfg)
{
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (SLCDC_CFG_PARAM_CHECKING_ENABLE)

    /** Check parameters */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ERROR_RETURN(SLCDC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Check combination of display mode */
    err = r_slcdc_check_display_mode(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Start the SLCDC module */
    R_BSP_MODULE_START(FSP_IP_SLCDC, 0);

    /* Set Mode, waveform, timeslice and bias method */
    R_SLCDC->LCDM0 = (uint8_t) ((p_cfg->drive_volt_gen << R_SLCDC_LCDM0_MDSET_Pos) +
                                (p_cfg->waveform << R_SLCDC_LCDM0_LWAVE_Pos) +
                                (p_cfg->time_slice << R_SLCDC_LCDM0_LDTY_Pos) +
                                p_cfg->bias_method);

#if BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN

    /* Clear LCDM1 and set LCDVLM (if applicable) */
    R_SLCDC->LCDM1 = (BSP_CFG_MCU_VCC_MV > SLCDC_PRV_LCDM1_LCDVLM_THRESHOLD) ? 0U : 1U;
#else

    /* Clear LCDM1 */
    R_SLCDC->LCDM1 = 0U;
#endif

    /* Do clock operations required for SLCDC */
    err = r_slcdc_clock_operation(p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

#if BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN

    /* Set default contrast */
    if (SLCDC_VOLT_INTERNAL == p_cfg->drive_volt_gen)
    {
        /* Set boost (contrast) setting */
        R_SLCDC->VLCD = (uint8_t) (p_cfg->contrast + SLCDC_PRV_VLCD_CONTRAST_OFFSET);
    }
    else
    {
        /* Non-boost modes must use the default setting for VLCD */
        R_SLCDC->VLCD = (uint8_t) SLCDC_PRV_VLCD_CONTRAST_OFFSET;
    }
#endif

    /* Save a pointer to the config block */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Set module state to open */
    p_instance_ctrl->open = SLCDC_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Writes a sequence of display data to the segment data registers. Implements slcdc_api_t::write.
 *
 * @retval  FSP_SUCCESS                      Data was written successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block or data is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT         Segment index is (or will be) out of range.
 * @retval  FSP_ERR_NOT_OPEN                 Device is not opened or initialized.
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_Write (slcdc_ctrl_t * const p_ctrl,
                         uint8_t const        start_segment,
                         uint8_t const      * p_data,
                         uint8_t const        segment_count)
{
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (SLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_data);
    FSP_ERROR_RETURN(SLCDC_CLOSED != p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    if ((BSP_FEATURE_SLCDC_MAX_NUM_SEG <= start_segment) ||
        (((uint8_t) (BSP_FEATURE_SLCDC_MAX_NUM_SEG)) < (start_segment + segment_count)))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Display data is stored in the LCD segment data register array */
    for (uint8_t seg = start_segment; (seg - start_segment) < segment_count; seg++)
    {
        R_SLCDC->SEG[seg] = *p_data;
        p_data++;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Modifies a single segment register based on a mask and the desired data. Implements slcdc_api_t::modify.
 *
 * @retval  FSP_SUCCESS                      Device was opened successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block structure is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT         Invalid parameter in the argument.
 * @retval  FSP_ERR_NOT_OPEN                 Device is not opened or initialized
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_Modify (slcdc_ctrl_t * const p_ctrl,
                          uint8_t const        segment,
                          uint8_t const        data,
                          uint8_t const        data_mask)
{
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

#if (SLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SLCDC_CLOSED != p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    if (BSP_FEATURE_SLCDC_MAX_NUM_SEG <= segment)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Mask and write data to segment */
    R_SLCDC->SEG[segment] = (R_SLCDC->SEG[segment] & (uint8_t) (~(data_mask))) | data;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Starts output of LCD signals. Implements slcdc_api_t::start.
 *
 * @retval  FSP_SUCCESS                      Device was opened successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN                 Device is not opened or initialized
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_Start (slcdc_ctrl_t * const p_ctrl)
{
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

#if (SLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SLCDC_CLOSED != p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN

    /* Enable the voltage boost or capacitor split circuit. */
    if (SLCDC_VOLT_EXTERNAL != p_instance_ctrl->p_cfg->drive_volt_gen)
    {
        R_SLCDC->LCDM1_b.VLCON = 1;
    }

#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Start SLCDC output */
    R_SLCDC->LCDM1 = R_SLCDC->LCDM1 | SLCDC_PRV_LCDM1_SCOC_LCDON;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops output of LCD signals. Implements slcdc_api_t::stop.
 *
 * @retval  FSP_SUCCESS                      Device was opened successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN                 Device is not opened or initialized
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_Stop (slcdc_ctrl_t * const p_ctrl)
{
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

#if (SLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SLCDC_CLOSED != p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Stop SLCDC output */
    R_SLCDC->LCDM1 = (uint8_t) (R_SLCDC->LCDM1 & (~(SLCDC_PRV_LCDM1_SCOC_LCDON)));

#if BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN

    /* Disable voltage circuit */
    R_SLCDC->LCDM1_b.VLCON = 0;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets contrast to the specified level. Implements slcdc_api_t::setContrast.
 *
 * @note Contrast can be adjusted when the SLCDC is operating in internal boost mode only. The range of values is 0-5
 *       when 1/4 bias setting is used and 0-15 otherwise. See RA4M1 User's Manual (R01UH0887EJ0100) section 45.2.4 "LCD
 *       Boost Level Control Register (VLCD)" for voltage levels at each setting.
 *
 * @retval  FSP_SUCCESS                      Device was opened successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN                 Device is not opened or initialized
 * @retval  FSP_ERR_UNSUPPORTED              Unsupported operation
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_SetContrast (slcdc_ctrl_t * const p_ctrl, slcdc_contrast_t const contrast)
{
#if !BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(contrast);

    /* Internal voltage generation is not supported on this MCU */
    return FSP_ERR_UNSUPPORTED;
#else
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

 #if (SLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SLCDC_CLOSED != p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    slcdc_cfg_t const * p_cfg = p_instance_ctrl->p_cfg;

    /* The VLCD setting is valid only when the voltage boost circuit is operating */
    if (SLCDC_VOLT_INTERNAL != p_cfg->drive_volt_gen)
    {
        return FSP_ERR_UNSUPPORTED;
    }

    /* Verify the new setting is within the range. */
    if ((SLCDC_BIAS_4 == p_cfg->bias_method) && (SLCDC_PRV_CONTRAST_MAX_4BIAS < contrast))
    {
        return FSP_ERR_UNSUPPORTED;
    }

 #else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
 #endif

    /* Stop the internal voltage boost circuit. */
    R_SLCDC->LCDM1_b.VLCON = 0;

    /* Set new voltage value. */
    R_SLCDC->VLCD = (uint8_t) (contrast + SLCDC_PRV_VLCD_CONTRAST_OFFSET);

    /* Enable the voltage boost circuit */
    R_SLCDC->LCDM1_b.VLCON = 1;

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 * Sets output to Waveform A, Waveform B or blinking output. Implements slcdc_api_t::setDisplayArea.
 *
 * @retval  FSP_SUCCESS                      Device was opened successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block structure is NULL.
 * @retval  FSP_ERR_UNSUPPORTED              Pattern selection has no effect in 8-time-slice mode.
 * @retval  FSP_ERR_NOT_OPEN                 Device is not opened or initialized.
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_SetDisplayArea (slcdc_ctrl_t * const p_ctrl, slcdc_display_area_t const display_area)
{
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

#if (SLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SLCDC_CLOSED != p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* When the number of time slices is eight, LCD display data registers
     * (A-pattern, B-pattern, or blinking display) cannot be selected. */
    if (SLCDC_SLICE_8 == p_instance_ctrl->p_cfg->time_slice)
    {
        return FSP_ERR_UNSUPPORTED;
    }

#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Clear blink mode and set selected display area */
    R_SLCDC->LCDM1 = (uint8_t) ((uint8_t) (R_SLCDC->LCDM1 & (~(SLCDC_PRV_LCDM1_LCDSEL_BLON))) |
                                (display_area << R_SLCDC_LCDM1_LCDSEL_Pos));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the SLCDC driver. Implements slcdc_api_t::close.
 *
 * @retval  FSP_SUCCESS                      Device was closed successfully.
 * @retval  FSP_ERR_ASSERTION                Pointer to the control block structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN                 Device is not opened or initialized
 **********************************************************************************************************************/
fsp_err_t R_SLCDC_Close (slcdc_ctrl_t * const p_ctrl)
{
    slcdc_instance_ctrl_t * p_instance_ctrl = (slcdc_instance_ctrl_t *) p_ctrl;

#if (SLCDC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(SLCDC_CLOSED != p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop SLCDC output */
    R_SLCDC->LCDM1 = (uint8_t) (R_SLCDC->LCDM1 & (~(SLCDC_PRV_LCDM1_SCOC_LCDON)));

#if BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN

    /* Disable voltage circuit */
    R_SLCDC->LCDM1_b.VLCON = 0;
#endif

    /* Switch to external resistance method to reduce idle power consumption (per RA4M1 User's Manual (R01UH0887EJ0100)
     * section 45.2.2 "LCD Mode Register 1 (LCDM1)" Note 2) */
    R_SLCDC->LCDM0_b.MDSET = 0;

    /* Disable CGC register protection */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);

    /* Disable LCD clock */
    R_SYSTEM->SLCDSCKCR_b.LCDSCKEN = 0;

    /* Re-enable CGC register protection */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    /* Enter module-stop state for the SLCDC */
    R_BSP_MODULE_STOP(FSP_IP_SLCDC, 0);

    /* Set driver to closed */
    p_instance_ctrl->open = SLCDC_CLOSED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup R_SLCDC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if SLCDC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * This function checks the display mode against the list of valid modes given in given in Table 45.6 of the RA4M1
 * User's Manual (R01UH0887EJ0100).
 *
 * @param[in]     p_cfg   Pointer to the configuration structure for slcdc interface
 *
 * @retval  FSP_SUCCESS                      Display mode is valid.
 * @retval  FSP_ERR_UNSUPPORTED              Display mode is invalid.
 **********************************************************************************************************************/
static fsp_err_t r_slcdc_check_display_mode (slcdc_cfg_t const * const p_cfg)
{
    /* Get waveform (LCDM0) configuration parameters */
    slcdc_time_slice_t     time_slice     = p_cfg->time_slice;
    slcdc_bias_method_t    bias_method    = p_cfg->bias_method;
    slcdc_drive_volt_gen_t drive_volt_gen = p_cfg->drive_volt_gen;
    slcdc_waveform_t       waveform       = p_cfg->waveform;

    /* Pre-run a few boolean operations */
    bool drive_is_external = (SLCDC_VOLT_EXTERNAL == drive_volt_gen);
 #if BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN
    bool drive_is_internal = (SLCDC_VOLT_INTERNAL == drive_volt_gen);
 #endif
    bool bias_is_3  = (SLCDC_BIAS_3 == bias_method);
    bool bias_is_2  = (SLCDC_BIAS_2 == bias_method);
    bool slice_is_3 = (SLCDC_SLICE_3 == time_slice);

    /* The below checks the configuration against the list of valid modes
     * given in Table 45.6 of the RA4M1 User's Manual (R01UH0887EJ0100) */

 #if !BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN
    if (!drive_is_external)
    {
        return FSP_ERR_UNSUPPORTED;
    }
 #endif

    /* Check common compatibility modes */
 #if BSP_FEATURE_SLCDC_HAS_8_TIME_SLICE
    if (((SLCDC_SLICE_8 == time_slice) && (SLCDC_BIAS_4 == bias_method) && (drive_is_external || drive_is_internal)) ||
        ((SLCDC_SLICE_4 == time_slice) && bias_is_3))
 #else
    if ((SLCDC_SLICE_4 == time_slice) && bias_is_3)
 #endif
    {
        /* Do nothing (valid configuration) */
    }
    else if (waveform == SLCDC_WAVE_A)
    {
        /* Check further compatibility with Waveform A */
        if ((slice_is_3 && bias_is_3) ||
            (drive_is_external && (bias_is_2 && (time_slice < SLCDC_SLICE_4))))
        {
            /* Do nothing (valid configuration)*/
        }
        else
        {
            return FSP_ERR_UNSUPPORTED;
        }
    }
    else
    {

        /* All other modes are unsupported for Waveform B */
        return FSP_ERR_UNSUPPORTED;
    }

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Starts the HOCO clock when SLCDC clock source is selected as HOCO. Configures clock registers for SLCDC.
 *
 * @retval  FSP_SUCCESS                Clocks configured successfully.
 **********************************************************************************************************************/
static fsp_err_t r_slcdc_clock_operation (slcdc_cfg_t const * const p_cfg)
{
    /* Unprotect CGC registers */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);

    /* Disable LCD clock */
    R_SYSTEM->SLCDSCKCR_b.LCDSCKEN = 0;

    /* Set Division of LCDC clock source. */
    R_SLCDC->LCDC0 = (uint8_t) p_cfg->slcdc_clock_setting;

    /* Set clock source for LCDC. */
    R_SYSTEM->SLCDSCKCR = (uint8_t) p_cfg->slcdc_clock;

    /* Read SLCDSCKCR to ensure clock source is set */
    (void) (R_SYSTEM->SLCDSCKCR);

    /* Enable LCD clock */
    R_SYSTEM->SLCDSCKCR_b.LCDSCKEN = 1;

    /* Protect CGC registers */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    return FSP_SUCCESS;
}
