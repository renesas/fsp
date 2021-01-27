/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * lvd_prv_ns_callback)(lvd_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile lvd_prv_ns_callback)(lvd_callback_args_t * p_args);
#endif

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
static uint8_t volatile * const g_lvdncr0_lut[] = {&(R_SYSTEM->LVD1CR0), &(R_SYSTEM->LVD2CR0)};
static uint8_t volatile * const g_lvdncr1_lut[] = {&(R_SYSTEM->LVD1CR1), &(R_SYSTEM->LVD2CR1)};
static uint8_t volatile * const g_lvdnsr_lut[]  = {&(R_SYSTEM->LVD1SR), &(R_SYSTEM->LVD2SR)};
#if (BSP_FEATURE_LVD_HAS_LVDLVLR == 1)
static uint32_t const g_lvdlvlr_offset_lut[] =
{
    LVD_PRV_LVDLVLR_LVD1LVL_OFFSET, LVD_PRV_LVDLVLR_LVD2LVL_OFFSET
};
static uint32_t const g_lvdlvlr_mask_lut[] = {LVD_PRV_LVDLVLR_LVD1LVL_MASK, LVD_PRV_LVDLVLR_LVD2LVL_MASK};
#else
static uint8_t volatile * const g_lvdncmpcr_lut[]    = {&(R_SYSTEM->LVD1CMPCR), &(R_SYSTEM->LVD2CMPCR)};
static uint32_t const           g_lvdnlvl_mask_lut[] = {R_SYSTEM_LVD1CMPCR_LVD1LVL_Msk, R_SYSTEM_LVD2CMPCR_LVD2LVL_Msk};
#endif

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
    .callbackSet = R_LVD_CallbackSet
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
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

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
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements lvd_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_LVD_CallbackSet (lvd_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(lvd_callback_args_t *),
                             void const * const          p_context,
                             lvd_callback_args_t * const p_callback_memory)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(LVD_OPENED == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if LVD_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    lvd_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(lvd_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

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

#if BSP_FEATURE_LVD_HAS_LVDLVLR == 1
    FSP_CRITICAL_SECTION_DEFINE;
#endif

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

#if BSP_FEATURE_LVD_HAS_LVDLVLR == 1

    /* Critical section required because LVCMPCR register is shared with other instances. */
    FSP_CRITICAL_SECTION_ENTER;

    /* Disable voltage detection circuit. */
    R_SYSTEM->LVCMPCR &= (uint8_t) ~(p_ctrl->p_cfg->monitor_number << LVD_PRV_LVCMPCR_LVD1E_OFFSET);

    FSP_CRITICAL_SECTION_EXIT;
#else
    *(g_lvdncmpcr_lut[monitor_index]) &= (uint8_t) ~R_SYSTEM_LVD1CMPCR_LVD1E_Msk;
#endif

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);

    gp_ctrls[monitor_index] = NULL;
    p_ctrl->open            = 0;

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * DEPRECATED Returns the LVD driver version based on compile time macros.
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

#if (BSP_FEATURE_LVD_HAS_LVDLVLR == 1)
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
#else
    uint8_t lvdne[LVD_PRV_NUMBER_OF_MONITORS];
    uint8_t i;

    /* Critical section required because LVCMPCR and LVDLVLR registers are shared with other instances. */
    FSP_CRITICAL_SECTION_ENTER;

    /* To change a LVDNLVL register both voltage detection circuits must be disabled.
     * Disable the voltage detection circuit for all monitors before writing the LVDLVLR register.
     * See section 7.2.2 "LVD1CMPCR : Voltage Monitoring 1 Comparator Control Register" in the RA6M4 manual R01HUM0890EJ0050.*/
    for (i = 0; i < LVD_PRV_NUMBER_OF_MONITORS; i++)
    {
        lvdne[i]               = *(g_lvdncmpcr_lut[i]) & R_SYSTEM_LVD1CMPCR_LVD1E_Msk; // Preserve enable values for other monitors
        *(g_lvdncmpcr_lut[i]) &= (uint8_t) ~R_SYSTEM_LVD1CMPCR_LVD1E_Msk;
    }

    /* Configure the voltage threshold setting. */
    uint8_t lvdncmpcr = *(g_lvdncmpcr_lut[monitor_index]);
    lvdncmpcr &= (uint8_t) ~(g_lvdnlvl_mask_lut[monitor_index]);
    lvdncmpcr |= p_ctrl->p_cfg->voltage_threshold;

    /* Write the voltage level setting. */
    *(g_lvdncmpcr_lut[monitor_index]) = lvdncmpcr;

    /* Enable the voltage detection circuits. */
    for (i = 0; i < LVD_PRV_NUMBER_OF_MONITORS; i++)
    {
        if (monitor_index == i)
        {
            *(g_lvdncmpcr_lut[monitor_index]) |= R_SYSTEM_LVD1CMPCR_LVD1E_Msk;
        }
        else
        {
            *(g_lvdncmpcr_lut[i]) |= lvdne[i];
        }
    }
    FSP_CRITICAL_SECTION_EXIT;
#endif

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

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    lvd_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &callback_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        callback_args = *p_args;
    }

    p_args->current_state =
        (lvd_current_state_t) ((*(g_lvdnsr_lut[monitor_index]) & LVD_PRV_LVDNSR_MON_MASK) > 0);
    p_args->monitor_number = p_ctrl->p_cfg->monitor_number;
    p_args->p_context      = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        lvd_prv_ns_callback p_callback = (lvd_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = callback_args;
    }

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
