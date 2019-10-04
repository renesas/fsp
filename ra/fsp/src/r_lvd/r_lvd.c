/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_lvd.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define LVD_OPENED                         0x4C5644U

#define LVD_PRV_NUMBER_OF_MONITORS         2

#define LVD_PRV_FIRST_MONITOR_NUMBER       (1U)

/* LVDNCR1 Bit Field Definitions */
#define LVD_PRV_LVDNCR1_IDTSEL_OFFSET      (0U)
#define LVD_PRV_LVDNCR1_IDTSEL_MASK        (3U << LVD_PRV_LVDNCR1_IDTSEL_OFFSET)
#define LVD_PRV_LVDNCR1_IRQSEL_OFFSET      (2U)
#define LVD_PRV_LVDNCR1_IRQSEL_MASK        (1U << LVD_PRV_LVDNCR1_IRQSEL_OFFSET)

/* LVDNSR Bit Field Definitions */
#define LVD_PRV_LVDNSR_DET_OFFSET          (0U)
#define LVD_PRV_LVDNSR_DET_MASK            (1U << LVD_PRV_LVDNSR_DET_OFFSET)
#define LVD_PRV_LVDNSR_MON_OFFSET          (1U)
#define LVD_PRV_LVDNSR_MON_MASK            (1U << LVD_PRV_LVDNSR_MON_OFFSET)

/* LVCMPCR Bit Field Definitions */
#define LVD_PRV_LVCMPCR_LVD1E_OFFSET       (5U)
#define LVD_PRV_LVCMPCR_LVD1E_MASK         (1U << LVD_PRV_LVCMPCR_LVD1E_OFFSET)
#define LVD_PRV_LVCMPCR_LVD2E_OFFSET       (6U)
#define LVD_PRV_LVCMPCR_LVD2E_MASK         (1U << LVD_PRV_LVCMPCR_LVD2E_OFFSET)

/* LVDLVLR Bit Field Definitions */
#define LVD_PRV_LVDLVLR_LVD1LVL_OFFSET     (0U)
#define LVD_PRV_LVDLVLR_LVD1LVL_MASK       (0x1FU << LVD_PRV_LVDLVLR_LVD1LVL_OFFSET)
#define LVD_PRV_LVDLVLR_LVD2LVL_OFFSET     (5U)
#define LVD_PRV_LVDLVLR_LVD2LVL_MASK       (0x07U << LVD_PRV_LVDLVLR_LVD2LVL_OFFSET)

/* LVDNCR0 Bit Field Definitions */
#define LVD_PRV_LVDNCR0_RIE_OFFSET         (0U)
#define LVD_PRV_LVDNCR0_RIE_MASK           (1U << LVD_PRV_LVDNCR0_RIE_OFFSET)
#define LVD_PRV_LVDNCR0_DFDIS_OFFSET       (1U)
#define LVD_PRV_LVDNCR0_DFDIS_MASK         (1U << LVD_PRV_LVDNCR0_DFDIS_OFFSET)
#define LVD_PRV_LVDNCR0_CMPE_OFFSET        (2U)
#define LVD_PRV_LVDNCR0_CMPE_MASK          (1U << LVD_PRV_LVDNCR0_CMPE_OFFSET)
#define LVD_PRV_LVDNCR0_FSAMP_OFFSET       (4U)
#define LVD_PRV_LVDNCR0_FSAMP_MASK         (3U << LVD_PRV_LVDNCR0_FSAMP_OFFSET)
#define LVD_PRV_LVDNCR0_RI_OFFSET          (6U)
#define LVD_PRV_LVDNCR0_RI_MASK            (1U << LVD_PRV_LVDNCR0_RI_OFFSET)
#define LVD_PRV_LVDNCR0_RN_OFFSET          (7U)
#define LVD_PRV_LVDNCR0_RN_MASK            (1U << LVD_PRV_LVDNCR0_RN_OFFSET)

#define LVD_PRV_SECONDS_TO_MICROSECONDS    (1000000U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_lvd_hw_configure(lvd_instance_ctrl_t * p_ctrl);

#if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1
static uint32_t r_lvd_filter_delay(lvd_sample_clock_t sample_clock_divisor);

#endif
#if (LVD_CFG_PARAM_CHECKING_ENABLE == 1)
static fsp_err_t lvd_open_parameter_check(lvd_instance_ctrl_t * p_ctrl, lvd_cfg_t const * const p_cfg);

#endif

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
static void lvd_common_isr_handler(lvd_instance_ctrl_t * p_ctrl);
static void lvd_nmi_handler(bsp_grp_irq_t irq);
void        lvd_lvd_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Stored context for NMI handler. */
static lvd_instance_ctrl_t * gp_ctrls[LVD_PRV_NUMBER_OF_MONITORS] = {NULL};

/** Version data structure used by error logger macro. */
static const fsp_version_t g_lvd_version =
{
    .api_version_minor  = LVD_API_VERSION_MINOR,
    .api_version_major  = LVD_API_VERSION_MAJOR,
    .code_version_major = LVD_CODE_VERSION_MAJOR,
    .code_version_minor = LVD_CODE_VERSION_MINOR
};

/* Look-up tables for writing to monitor 1 and monitor 2 registers. */
static uint8_t volatile * const g_lvdncr0_lut[]        = {&(R_SYSTEM->LVD1CR0), &(R_SYSTEM->LVD2CR0)};
static uint8_t volatile * const g_lvdncr1_lut[]        = {&(R_SYSTEM->LVD1CR1), &(R_SYSTEM->LVD2CR1)};
static uint8_t volatile * const g_lvdnsr_lut[]         = {&(R_SYSTEM->LVD1SR), &(R_SYSTEM->LVD2SR)};
static uint32_t const           g_lvdlvlr_offset_lut[] =
{
    LVD_PRV_LVDLVLR_LVD1LVL_OFFSET, LVD_PRV_LVDLVLR_LVD2LVL_OFFSET
};
static uint32_t const g_lvdlvlr_mask_lut[] = {LVD_PRV_LVDLVLR_LVD1LVL_MASK, LVD_PRV_LVDLVLR_LVD2LVL_MASK};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** Instance of low voltage detection peripheral driver interface */
const lvd_api_t g_lvd_on_lvd =
{
    .open        = R_LVD_Open,
    .statusGet   = R_LVD_StatusGet,
    .statusClear = R_LVD_StatusClear,
    .close       = R_LVD_Close,
    .versionGet  = R_LVD_VersionGet,
};

/*******************************************************************************************************************//**
 * @addtogroup LVD
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes a voltage monitor and detector according to the passed-in configuration structure.
 *
 * @param[in]   p_api_ctrl              Pointer to the control structure for the driver instance
 * @param[in]   p_cfg                   Pointer to the configuration structure for the driver instance
 *
 * @note Digital filter is not to be used with standby modes.
 * @note Startup time can take on the order of milliseconds for some configurations.
 *
 * Example:
 * @snippet r_lvd_example.c R_LVD_Open
 *
 * @retval      FSP_SUCCESS             Successful
 * @retval      FSP_ERR_ASSERTION       Requested configuration was invalid
 * @retval      FSP_ERR_ALREADY_OPEN    The instance was already opened
 * @retval      FSP_ERR_IN_USE          Another instance is already using the desired monitor
 * @retval      FSP_ERR_UNSUPPORTED     Digital filter was enabled on a device that does not support it
 **********************************************************************************************************************/
fsp_err_t R_LVD_Open (lvd_ctrl_t * const p_api_ctrl, lvd_cfg_t const * const p_cfg)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (LVD_CFG_PARAM_CHECKING_ENABLE == 1)
    fsp_err_t err = FSP_SUCCESS;
    err = lvd_open_parameter_check(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err)
#endif

    /* Store the user configuration. */
    p_ctrl->p_cfg = p_cfg;

    /* Store control structure so it can be accessed from NMI handler. */
    gp_ctrls[p_ctrl->p_cfg->monitor_number - 1] = p_ctrl;

    /* Configure the hardware based on the user settings. */
    r_lvd_hw_configure(p_ctrl);

    /* Mark driver as opened by initializing it to "LVD" in its ASCII equivalent. */
    p_ctrl->open = LVD_OPENED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the current state of the monitor (threshold crossing detected, voltage currently above or below threshold).
 *
 * @param[in]   p_api_ctrl              Pointer to the control structure for the driver instance
 * @param[out]  p_lvd_status            Pointer to status structure
 *
 * Example:
 * @snippet r_lvd_example.c R_LVD_StatusGet
 *
 * @retval          FSP_SUCCESS         Successful
 * @retval          FSP_ERR_ASSERTION   An argument was NULL
 * @retval          FSP_ERR_NOT_OPEN    Driver is not open
 *
 **********************************************************************************************************************/
fsp_err_t R_LVD_StatusGet (lvd_ctrl_t * const p_api_ctrl, lvd_status_t * p_lvd_status)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (0 != LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_lvd_status);
    FSP_ERROR_RETURN((LVD_OPENED == p_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    uint8_t lvdnsr = 0;

    if (1U == p_ctrl->p_cfg->monitor_number)
    {
        lvdnsr = R_SYSTEM->LVD1SR;
    }
    else
    {
        lvdnsr = R_SYSTEM->LVD2SR;
    }

    p_lvd_status->crossing_detected = (lvd_threshold_crossing_t) ((lvdnsr & LVD_PRV_LVDNSR_DET_MASK) != 0);
    p_lvd_status->current_state     = (lvd_current_state_t) ((lvdnsr & LVD_PRV_LVDNSR_MON_MASK) != 0);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Clears the latched status of the monitor.
 *
 * @param[in]   p_api_ctrl          Pointer to the control structure for the driver instance
 *
 * @retval      FSP_SUCCESS         Successful
 * @retval      FSP_ERR_ASSERTION   An argument was NULL
 * @retval      FSP_ERR_NOT_OPEN    Driver is not open
 *
 **********************************************************************************************************************/
fsp_err_t R_LVD_StatusClear (lvd_ctrl_t * const p_api_ctrl)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (0 != LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN((NULL != p_ctrl), FSP_ERR_ASSERTION);
    FSP_ERROR_RETURN((LVD_OPENED == p_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    /* Clear the status register. */
    *(g_lvdnsr_lut[p_ctrl->p_cfg->monitor_number - 1]) = 0;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables the LVD peripheral. Closes the driver instance.
 *
 * @param[in]   p_api_ctrl          Pointer to the control block structure for the driver instance
 *
 * @retval      FSP_SUCCESS         Successful
 * @retval      FSP_ERR_ASSERTION   An argument was NULL
 * @retval      FSP_ERR_NOT_OPEN    Driver is not open
 *
 **********************************************************************************************************************/
fsp_err_t R_LVD_Close (lvd_ctrl_t * const p_api_ctrl)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (0 != LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN((NULL != p_ctrl), FSP_ERR_ASSERTION);
    FSP_ERROR_RETURN(LVD_OPENED == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_CRITICAL_SECTION_DEFINE;

    uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 1;

    R_BSP_GroupIrqWrite((bsp_grp_irq_t) (BSP_GRP_IRQ_LVD1 + monitor_index), NULL);

    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->irq)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->irq);
    }

    /* Shutdown procedure from Table 8.5 in the RA6M3 Hardware Manual R01UH0886EJ0100. */

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    /* Disable output of comparison results by voltage monitor. */
    *(g_lvdncr0_lut[monitor_index]) &= (uint8_t) ~(LVD_PRV_LVDNCR0_CMPE_MASK);

#if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1
    if (LVD_SAMPLE_CLOCK_DISABLED != p_ctrl->p_cfg->sample_clock_divisor)
    {
        /* Wait for at least 2n + 3 LOCO cycles, where n = [2,4,8,16]. */
        R_BSP_SoftwareDelay(r_lvd_filter_delay(p_ctrl->p_cfg->sample_clock_divisor), BSP_DELAY_UNITS_MICROSECONDS);
    }
#endif

    uint8_t lvdncr0 = *(g_lvdncr0_lut[monitor_index]);

    /* Disable voltage monitor interrupt or reset. */
    lvdncr0 &= (uint8_t) ~LVD_PRV_LVDNCR0_RIE_MASK;

#if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1

    /* Disable digital filter. */
    lvdncr0 |= (uint8_t) LVD_PRV_LVDNCR0_DFDIS_MASK;
#endif

    *(g_lvdncr0_lut[monitor_index]) = lvdncr0;

    /* Critical section required because LVCMPCR register is shared with other instances. */
    FSP_CRITICAL_SECTION_ENTER;

    /* Disable voltage detection circuit. */
    R_SYSTEM->LVCMPCR &= (uint8_t) ~(p_ctrl->p_cfg->monitor_number << LVD_PRV_LVCMPCR_LVD1E_OFFSET);

    FSP_CRITICAL_SECTION_EXIT;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);

    gp_ctrls[monitor_index] = NULL;
    p_ctrl->open            = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the LVD driver version based on compile time macros.
 *
 * @param[in]       p_version           Pointer to the version structure
 *
 * @retval          FSP_SUCCESS         Successful
 * @retval          FSP_ERR_ASSERTION   p_version was NULL
 *
 **********************************************************************************************************************/
fsp_err_t R_LVD_VersionGet (fsp_version_t * const p_version)
{
#if (0 != LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN((NULL != p_version), FSP_ERR_ASSERTION);
#endif

    p_version->version_id = g_lvd_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup LVD)
 **********************************************************************************************************************/

/*********************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the hardware based on the user defined configuration settings.
 *
 * @param[in]   p_ctrl                  Pointer to the control structure for the driver instance
 *
 **********************************************************************************************************************/
static void r_lvd_hw_configure (lvd_instance_ctrl_t * p_ctrl)
{
    FSP_CRITICAL_SECTION_DEFINE;

    uint32_t lvdncr0 = 0;
    uint32_t lvdncr1 = 0;

    /* Calculate index used to get monitor registers from look-up tables and perform other calculations. */
    uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 1;

    /* Configure the voltage monitor interrupt condition. */
    lvdncr1 |= (uint32_t) (p_ctrl->p_cfg->voltage_slope << LVD_PRV_LVDNCR1_IDTSEL_OFFSET);

    if (LVD_RESPONSE_NONE != p_ctrl->p_cfg->detection_response)
    {
        if (LVD_RESPONSE_INTERRUPT == p_ctrl->p_cfg->detection_response)
        {
            /* Configure the voltage monitor interrupt type as maskable. */
            lvdncr1 |= LVD_PRV_LVDNCR1_IRQSEL_MASK;

            /* Enable interrupt in NVIC */
            R_BSP_IrqCfgEnable(p_ctrl->p_cfg->irq, p_ctrl->p_cfg->monitor_ipl, p_ctrl);
        }
        else if (LVD_RESPONSE_NMI == p_ctrl->p_cfg->detection_response)
        {
            /* Enable the NMI handler. */
            R_BSP_GroupIrqWrite((bsp_grp_irq_t) (BSP_GRP_IRQ_LVD1 + monitor_index), lvd_nmi_handler);

            /* Enable NMI for this LVD monitor. NMIER bits can only be set. They cannot be cleared. */
            R_ICU->NMIER = (uint16_t) (1U << (2U + monitor_index));
        }
        else                           /* LVD_RESPONSE_RESET */
        {
            /* Enable voltage monitor reset when the voltage falls to below threshold. */
            lvdncr0 |= LVD_PRV_LVDNCR0_RI_MASK;

            /* Configure the voltage monitor reset negation mode. */
            lvdncr0 |= (uint32_t) (p_ctrl->p_cfg->negation_delay << LVD_PRV_LVDNCR0_RN_OFFSET);
        }
    }

    /* Amount of time to wait before enabling output of voltage monitor comparison results. */
    uint32_t delay = BSP_FEATURE_LVD_STABILIZATION_TIME_US;

#if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1
    if (LVD_SAMPLE_CLOCK_DISABLED != p_ctrl->p_cfg->sample_clock_divisor)
    {
        /* Configure the digital filter clock divider. */
        lvdncr0 |= (uint32_t) (p_ctrl->p_cfg->sample_clock_divisor << LVD_PRV_LVDNCR0_FSAMP_OFFSET);

        /* Wait for at least 2n + 3 LOCO cycles, where n = [2,4,8,16]. */
        uint32_t filter_delay = r_lvd_filter_delay(p_ctrl->p_cfg->sample_clock_divisor);

        /* If filter delay is greater than the stabilization delay, wait for filter delay. */
        if (filter_delay > delay)
        {
            delay = filter_delay;
        }
    }
    else
    {
        /* Disable the digital filter. */
        lvdncr0 |= LVD_PRV_LVDNCR0_DFDIS_MASK;
    }
#endif

    /* Setup procedure from Table 8.4 in the RA6M3 Hardware Manual R01UH0886EJ0100. */

    /* Enable access to LVD registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    uint32_t lvdne_mask    = p_ctrl->p_cfg->monitor_number << LVD_PRV_LVCMPCR_LVD1E_OFFSET;
    uint32_t lvdlvr_offset = g_lvdlvlr_offset_lut[monitor_index];

    /* Critical section required because LVCMPCR and LVDLVLR registers are shared with other instances. */
    FSP_CRITICAL_SECTION_ENTER;

    /* Disable the voltage detection circuit before writing the LVDLVLR register. */
    R_SYSTEM->LVCMPCR &= (uint8_t) ~lvdne_mask;

    /* Configure the voltage threshold setting. */
    uint32_t lvdlvlr = R_SYSTEM->LVDLVLR;
    lvdlvlr &= ~(g_lvdlvlr_mask_lut[monitor_index]);
    lvdlvlr |= (uint32_t) (p_ctrl->p_cfg->voltage_threshold << lvdlvr_offset);

    /*Write the voltage level setting. */
    R_SYSTEM->LVDLVLR = (uint8_t) lvdlvlr;

    /* Enable the voltage detection circuit. */
    R_SYSTEM->LVCMPCR |= (uint8_t) lvdne_mask;

    FSP_CRITICAL_SECTION_EXIT;

    /* Write settings to control registers. */
    *(g_lvdncr0_lut[monitor_index]) = (uint8_t) lvdncr0;
    *(g_lvdncr1_lut[monitor_index]) = (uint8_t) lvdncr1;

    /* Clear DET before setting RIE. */
    *(g_lvdnsr_lut[monitor_index]) = 0;

    if (LVD_RESPONSE_NONE != p_ctrl->p_cfg->detection_response)
    {
        /* Reset/Interrupt enable bit set after clearing DET bit. */
        *(g_lvdncr0_lut[monitor_index]) |= LVD_PRV_LVDNCR0_RIE_MASK;
    }

    /* Wait for LVD and filter stabilization. */
    R_BSP_SoftwareDelay(delay, BSP_DELAY_UNITS_MICROSECONDS);

    /* Enable output of comparison results by voltage monitor 2. */
    *(g_lvdncr0_lut[monitor_index]) |= (LVD_PRV_LVDNCR0_CMPE_MASK);

    /* Disable access to LVD registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);
}

#if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1

/*******************************************************************************************************************//**
 * Calculates the microseconds to delay after enabling the digital filter.
 *
 * @param[in]   sample_clock_divisor     The configured sample clock divisor for the digital filter
 *
 * @retval      microseconds             Number of microseconds to delay
 **********************************************************************************************************************/
static uint32_t r_lvd_filter_delay (lvd_sample_clock_t sample_clock_divisor)
{
    uint32_t loco_cycles = (uint32_t) (1 << (sample_clock_divisor + 1)) * 2 + 3;

    return (loco_cycles * LVD_PRV_SECONDS_TO_MICROSECONDS) / BSP_LOCO_HZ + 1U;
}

#endif

#if (LVD_CFG_PARAM_CHECKING_ENABLE == 1)

/*******************************************************************************************************************//**
 * Helper function to do parameter checking for R_LVD_Open.
 *
 * @param[in]   p_ctrl                  Pointer to the control block structure for the driver instance
 * @param[in]   p_cfg                   Pointer to the configuration structure for the driver instance
 *
 * @retval      FSP_SUCCESS             Successful
 * @retval      FSP_ERR_ASSERTION       Requested configuration was invalid
 * @retval      FSP_ERR_ALREADY_OPEN    The instance was already opened
 * @retval      FSP_ERR_IN_USE          Another instance is already using the desired monitor
 * @retval      FSP_ERR_UNSUPPORTED     Digital filter was enabled on a device that does not support it
 **********************************************************************************************************************/
static fsp_err_t lvd_open_parameter_check (lvd_instance_ctrl_t * p_ctrl, lvd_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(LVD_OPENED != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(1U == p_cfg->monitor_number || 2U == p_cfg->monitor_number);
    FSP_ERROR_RETURN(NULL == gp_ctrls[p_cfg->monitor_number - 1], FSP_ERR_IN_USE);

    int32_t threshold = (int32_t) p_cfg->voltage_threshold;

    /* Verify that the threshold is valid for voltage monitor. */
    if (1U == p_cfg->monitor_number)
    {
        /* High voltage thresholds correspond to low register settings. */
        FSP_ASSERT(threshold >= (int32_t) BSP_FEATURE_LVD_MONITOR_1_HI_THRESHOLD &&
                   threshold <= (int32_t) BSP_FEATURE_LVD_MONITOR_1_LOW_THRESHOLD);
    }
    else
    {
        /* High voltage thresholds correspond to low register settings. */
        FSP_ASSERT(threshold >= (int32_t) BSP_FEATURE_LVD_MONITOR_2_HI_THRESHOLD &&
                   threshold <= (int32_t) BSP_FEATURE_LVD_MONITOR_2_LOW_THRESHOLD);
    }

    /* If the response is an interrupt then IRQ setting must be a valid interrupt number. */
    if (LVD_RESPONSE_INTERRUPT == p_cfg->detection_response)
    {
        FSP_ASSERT(p_cfg->irq >= 0);
    }

    /* If the response is a maskable or non-maskable interrupt then a callback must be provided. */
    if ((LVD_RESPONSE_INTERRUPT == p_cfg->detection_response) || (LVD_RESPONSE_NMI == p_cfg->detection_response))
    {
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }

    /* Only LVD_VOLTAGE_SLOP_FALLING is possible when the detection response is LVD_RESPONSE_RESET. */
    if (LVD_RESPONSE_RESET == p_cfg->detection_response)
    {
        FSP_ASSERT(LVD_VOLTAGE_SLOPE_FALLING == p_cfg->voltage_slope);
    }

 #if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 0
    FSP_ERROR_RETURN(LVD_SAMPLE_CLOCK_DISABLED == p_cfg->sample_clock_divisor, FSP_ERR_UNSUPPORTED);
 #endif

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Common code needed for all LVD ISRs.
 *
 * @param[in] p_ctrl            Pointer to the control block structure for the driver instance
 *
 **********************************************************************************************************************/
static void lvd_common_isr_handler (lvd_instance_ctrl_t * p_ctrl)
{
    /* Calculate index used to get monitor registers from look-up tables and perform other calculations. */
    uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 1;

    lvd_callback_args_t callback_args;
    callback_args.current_state =
        (lvd_current_state_t) ((*(g_lvdnsr_lut[monitor_index]) & LVD_PRV_LVDNSR_MON_MASK) > 0);
    callback_args.monitor_number = p_ctrl->p_cfg->monitor_number;
    p_ctrl->p_cfg->p_callback(&callback_args);

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    /* Clear the status register. */
    *(g_lvdnsr_lut[monitor_index]) = 0;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);
}

/*******************************************************************************************************************//**
 * ISR for maskable LVD interrupts
 *
 **********************************************************************************************************************/
void lvd_lvd_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear the Interrupt Request */
    R_BSP_IrqStatusClear(irq);

    /* Call common isr handler. */
    lvd_common_isr_handler((lvd_instance_ctrl_t *) R_FSP_IsrContextGet(irq));

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ISR handler for non-maskable interrupts
 *
 * @param[in] irq         BSP group IRQ identifier
 *
 **********************************************************************************************************************/
static void lvd_nmi_handler (bsp_grp_irq_t irq)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Call common isr handler. */
    lvd_common_isr_handler(gp_ctrls[irq - BSP_GRP_IRQ_LVD1]);

    /* Restore context if RTOS is used  */
    FSP_CONTEXT_RESTORE
}
