/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_lvd.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define LVD_OPENED                            (0x4C5644U)

#define LVD_MONITOR_LVD1                      (1U)
#define LVD_MONITOR_LVD2                      (2U)
#define LVD_MONITOR_LVD_VBAT                  (3U)
#define LVD_MONITOR_LVD_VRTC                  (4U)
#define LVD_MONITOR_EXLVD                     (5U)

#define LVD_PRV_FIRST_MONITOR_NUMBER          (1U)

#if    (1U == BSP_FEATURE_LVD_VERSION)
 #define LVD_PRV_NUMBER_OF_NMI                (2U)
 #define LVD_PRV_NUMBER_OF_VCC_MONITOR        (2U)
#elif  (2U == BSP_FEATURE_LVD_VERSION)
 #define LVD_PRV_NUMBER_OF_NMI                (1U)
 #define LVD_PRV_NUMBER_OF_VCC_MONITOR        (1U)
#elif  (3U == BSP_FEATURE_LVD_VERSION)
 #define LVD_PRV_NUMBER_OF_NMI                (2U)
 #define LVD_PRV_NUMBER_OF_VCC_MONITOR        (5U)
#endif

#define LVD_PRV_EXT_LVDICR_IE_ENABLE          (1U << R_SYSTEM_VBTLVDICR_IE_Pos)

#define LVD_PRV_EXT_LVDCR_LVDE_ENABLE         (1 << R_SYSTEM_VBTLVDCR_LVDE_Pos)

#define LVD_PRV_LVD1MKR_MK_ENABLE             (1U)
#define LVD_PRV_LVD1MKR_MK_DISABLE            (0U)
#define LVD_PRV_LVDCR0_BIT3_MASK              (0x8U)

#define LVD_PRV_LVD1CR_IRQSEL_NON_MASKABLE    (0U)
#define LVD_PRV_LVD1CR_IRQSEL_MASKABLE        (1U)
#define LVD_PRV_LVD1CR_LVD1SEL_INTERRUPT      (0U)
#define LVD_PRV_LVD1CR_LVD1SEL_RESET          (1U)
#define LVD_PRV_LVD1CR_LVD1EN_DISABLE         (0U)
#define LVD_PRV_LVD1CR_LVD1EN_ENABLE          (1U)

#define LVD_PRV_SECONDS_TO_MICROSECONDS       (1000000U)

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

#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
static void r_lvd_ext_hw_configure(lvd_instance_ctrl_t * p_ctrl);

#endif

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

#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
static void lvd_ext_common_isr_handler(lvd_instance_ctrl_t * p_ctrl);
void        lvd_ext_isr(void);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Stored context for NMI handler. */
static lvd_instance_ctrl_t * gp_ctrls[LVD_PRV_NUMBER_OF_VCC_MONITOR] = {NULL};

#if (1U == BSP_FEATURE_LVD_VERSION)

/* Look-up tables for writing to monitor 1 and monitor 2 registers. */
static uint8_t volatile * const g_lvdncr0_lut[] = {&(R_SYSTEM->LVD1CR0), &(R_SYSTEM->LVD2CR0)};
static uint8_t volatile * const g_lvdncr1_lut[] = {&(R_SYSTEM->LVD1CR1), &(R_SYSTEM->LVD2CR1)};
static uint8_t volatile * const g_lvdnsr_lut[]  = {&(R_SYSTEM->LVD1SR), &(R_SYSTEM->LVD2SR)};

#elif (2U == BSP_FEATURE_LVD_VERSION)
static uint8_t volatile * const g_lvdnsr_lut[] = {&(R_SYSTEM->LVD1SR)};

#elif (3U == BSP_FEATURE_LVD_VERSION)

/* Look-up tables for writing to monitor 1, monitor 2, monitor 4, monitor 5, registers. monitor 3 registers are dummy variables. */
static uint8_t volatile * const g_lvdncr0_lut[] =
{
    &(R_SYSTEM->LVD1CR0), &(R_SYSTEM->LVD2CR0), &(R_SYSTEM->LVD3CR0), &(R_SYSTEM->LVD4CR0), &(R_SYSTEM->LVD5CR0)
};
static uint8_t volatile * const g_lvdncr1_lut[] =
{
    &(R_SYSTEM->LVD1CR1), &(R_SYSTEM->LVD2CR1), &(R_SYSTEM->LVD3CR1), &(R_SYSTEM->LVD4CR1), &(R_SYSTEM->LVD5CR1)
};
static uint8_t volatile * const g_lvdnsr_lut[] = {&(R_SYSTEM->LVD1SR), &(R_SYSTEM->LVD2SR)};
#endif

#if BSP_FEATURE_LVD_SUPPORT_RESET_ON_RISING_EDGE
 #if (3U == BSP_FEATURE_LVD_VERSION)
static uint8_t volatile * const g_lvdnfcr_lut[] =
{
    &(R_SYSTEM->LVD1FCR), &(R_SYSTEM->LVD2FCR), &(R_SYSTEM->LVD3FCR), &(R_SYSTEM->LVD4FCR), &(R_SYSTEM->LVD5FCR)
};
 #else
static uint8_t volatile * const g_lvdnfcr_lut[] = {&(R_SYSTEM->LVD1FCR), &(R_SYSTEM->LVD2FCR)};
 #endif
#endif

#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1

/* Look-up table for writing to VBAT, RTC, EX register. */
/* Index: VBAT - 0, RTC - 1, EX - 2. */
static uint8_t volatile * const g_ext_lvdcr_lut[] =
{&(R_SYSTEM->VBTLVDCR), &(R_SYSTEM->VRTLVDCR), &(R_SYSTEM->EXLVDCR)};

static uint8_t volatile * const g_ext_lvdsr_lut[] =
{&(R_SYSTEM->VBTLVDSR), &(R_SYSTEM->VRTSR), &(R_SYSTEM->EXLVDSR)};

static uint8_t volatile * const g_ext_lvdicr_lut[] =
{&(R_SYSTEM->VBTLVDICR), &(R_SYSTEM->VRTLVDICR), &(R_SYSTEM->EXLVDICR)};

static uint8_t volatile * const g_ext_lvdcmpcr_lut[] =
{&(R_SYSTEM->VBTCMPCR), &(R_SYSTEM->VRTCMPCR), &(R_SYSTEM->EXLVDCMPCR)};
#endif

#if (BSP_FEATURE_LVD_HAS_LVDLVLR == 1)
static uint32_t const g_lvdlvlr_offset_lut[] =
{
    R_SYSTEM_LVDLVLR_LVD1LVL_Pos, R_SYSTEM_LVDLVLR_LVD2LVL_Pos
};
static uint32_t const g_lvdlvlr_mask_lut[] = {R_SYSTEM_LVDLVLR_LVD1LVL_Msk, R_SYSTEM_LVDLVLR_LVD2LVL_Msk};
#elif (1U == BSP_FEATURE_LVD_VERSION)
static uint8_t volatile * const g_lvdncmpcr_lut[]    = {&(R_SYSTEM->LVD1CMPCR), &(R_SYSTEM->LVD2CMPCR)};
static uint32_t const           g_lvdnlvl_mask_lut[] = {R_SYSTEM_LVD1CMPCR_LVDLVL_Msk, R_SYSTEM_LVD2CMPCR_LVDLVL_Msk};
#elif (3U == BSP_FEATURE_LVD_VERSION)
static uint8_t volatile * const g_lvdncmpcr_lut[] =
{
    &(R_SYSTEM->LVD1CMPCR), &(R_SYSTEM->LVD2CMPCR), &(R_SYSTEM->LVD3CMPCR), &(R_SYSTEM->LVD4CMPCR),
    &(R_SYSTEM->LVD5CMPCR)
};
static uint32_t const g_lvdnlvl_mask_lut[] =
{
    R_SYSTEM_LVD1CMPCR_LVDLVL_Msk, R_SYSTEM_LVD2CMPCR_LVDLVL_Msk, R_SYSTEM_LVD3CMPCR_LVDLVL_Msk,
    R_SYSTEM_LVD4CMPCR_LVDLVL_Msk, R_SYSTEM_LVD5CMPCR_LVDLVL_Msk
};
#endif

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* Instance of low voltage detection peripheral driver interface. */
const lvd_api_t g_lvd_on_lvd =
{
    .open        = R_LVD_Open,
    .statusGet   = R_LVD_StatusGet,
    .statusClear = R_LVD_StatusClear,
    .close       = R_LVD_Close,
    .callbackSet = R_LVD_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup LVD-PVD
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

    if (p_ctrl->p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_VCC_MONITOR)
    {
        /* Store control structure so it can be accessed from NMI handler. */
        gp_ctrls[p_ctrl->p_cfg->monitor_number - 1] = p_ctrl;

        /* Configure the hardware based on the user settings. */
        r_lvd_hw_configure(p_ctrl);
    }

#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
    else
    {
        /* Configure the hardware based on the user settings. */
        r_lvd_ext_hw_configure(p_ctrl);
    }
#endif

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
 * @retval          FSP_ERR_UNSUPPORTED This monitor does not support status feature
 *
 **********************************************************************************************************************/
fsp_err_t R_LVD_StatusGet (lvd_ctrl_t * const p_api_ctrl, lvd_status_t * p_lvd_status)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (0 != LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_lvd_status);
 #if (3U == BSP_FEATURE_LVD_VERSION)
    FSP_ERROR_RETURN(!((4 == p_ctrl->p_cfg->monitor_number) || (5 == p_ctrl->p_cfg->monitor_number)),
                     FSP_ERR_UNSUPPORTED);
 #endif
    FSP_ERROR_RETURN((LVD_OPENED == p_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    uint8_t lvdnsr = 0;

    if (p_ctrl->p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_NMI)
    {
        lvdnsr = *(g_lvdnsr_lut[p_ctrl->p_cfg->monitor_number - 1]);
        p_lvd_status->crossing_detected = (lvd_threshold_crossing_t) ((lvdnsr & R_SYSTEM_LVD1SR_DET_Msk) != 0);
        p_lvd_status->current_state     = (lvd_current_state_t) ((lvdnsr & R_SYSTEM_LVD1SR_MON_Msk) != 0);
    }

#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
    else
    {
        lvdnsr = *(g_ext_lvdsr_lut[p_ctrl->p_cfg->monitor_number - 3]);
        p_lvd_status->crossing_detected = (lvd_threshold_crossing_t) ((lvdnsr & R_SYSTEM_VBTLVDSR_DET_Msk) != 0);
        p_lvd_status->current_state     = (lvd_current_state_t) ((lvdnsr & R_SYSTEM_VBTLVDSR_MON_Msk) != 0);
    }
#endif

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
 * @retval      FSP_ERR_UNSUPPORTED This monitor does not support status feature
 *
 **********************************************************************************************************************/
fsp_err_t R_LVD_StatusClear (lvd_ctrl_t * const p_api_ctrl)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (0 != LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ERROR_RETURN((NULL != p_ctrl), FSP_ERR_ASSERTION);
 #if (3U == BSP_FEATURE_LVD_VERSION)
    FSP_ERROR_RETURN(!((4 == p_ctrl->p_cfg->monitor_number) || (5 == p_ctrl->p_cfg->monitor_number)),
                     FSP_ERR_UNSUPPORTED);
 #endif
    FSP_ERROR_RETURN((LVD_OPENED == p_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    /* Clear the status register. */
    if (p_ctrl->p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_NMI)
    {
        *(g_lvdnsr_lut[p_ctrl->p_cfg->monitor_number - 1]) = 0;
    }

#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
    else
    {
        *(g_ext_lvdsr_lut[p_ctrl->p_cfg->monitor_number - 3]) = 0;
    }
#endif

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
                             void * const                p_context,
                             lvd_callback_args_t * const p_callback_memory)
{
    lvd_instance_ctrl_t * p_ctrl = (lvd_instance_ctrl_t *) p_api_ctrl;

#if (LVD_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(LVD_OPENED == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback. */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if LVD_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure. */
    lvd_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context. */
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

    if (FSP_INVALID_VECTOR != p_ctrl->p_cfg->irq)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->irq);
    }

    if (p_ctrl->p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_VCC_MONITOR)
    {
        uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 1;

        if (p_ctrl->p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_NMI)
        {
            /* Setting for NMI. */
            R_BSP_GroupIrqWrite((bsp_grp_irq_t) (BSP_GRP_IRQ_LVD1 + monitor_index), NULL);
        }

        /* Shutdown procedure from Table 8.5 in the RA6M3 Hardware Manual R01UH0886EJ0100. */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

#if 2U == BSP_FEATURE_LVD_VERSION

        /* Enable writing to the LVD1CR register. */
        R_SYSTEM->LVD1MKR_b.MK = LVD_PRV_LVD1MKR_MK_ENABLE;

        /* Disable LVD1 operation. */
        R_SYSTEM->LVD1CR_b.LVD1EN = LVD_PRV_LVD1CR_LVD1EN_DISABLE;

        /* Disable writing to the LVD1CR register. */
        R_SYSTEM->LVD1MKR_b.MK = LVD_PRV_LVD1MKR_MK_DISABLE;
#else

        /* Disable output of comparison results by voltage monitor. Write value to lvdncr0.bit3 should be 1. */
        *(g_lvdncr0_lut[monitor_index]) = (*(g_lvdncr0_lut[monitor_index]) | (uint8_t) LVD_PRV_LVDCR0_BIT3_MASK) &
                                          ((uint8_t) ~(R_SYSTEM_LVD1CR0_CMPE_Msk));

 #if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1
        if (LVD_SAMPLE_CLOCK_DISABLED != p_ctrl->p_cfg->sample_clock_divisor)
        {
            /* Wait for at least 2n + 3 LOCO cycles, where n = [2,4,8,16]. */
            R_BSP_SoftwareDelay(r_lvd_filter_delay(p_ctrl->p_cfg->sample_clock_divisor), BSP_DELAY_UNITS_MICROSECONDS);
        }
 #endif
        uint8_t lvdncr0 = *(g_lvdncr0_lut[monitor_index]);

        /* Disable voltage monitor interrupt or reset. */
        lvdncr0 &= (uint8_t) ~R_SYSTEM_LVD1CR0_RIE_Msk;

 #if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1

        /* Disable digital filter. */
        lvdncr0 |= (uint8_t) R_SYSTEM_LVD1CR0_DFDIS_Msk;
 #endif

        /* Write value to lvdncr0.bit3 should be 1. */
        *(g_lvdncr0_lut[monitor_index]) = (lvdncr0 | (uint8_t) LVD_PRV_LVDCR0_BIT3_MASK);
 #if BSP_FEATURE_LVD_HAS_LVDLVLR == 1

        /* Critical section required because LVCMPCR register is shared with other instances. */
        FSP_CRITICAL_SECTION_ENTER;

        /* Disable voltage detection circuit. */
        R_SYSTEM->LVCMPCR &= (uint8_t) ~(p_ctrl->p_cfg->monitor_number << R_SYSTEM_LVCMPCR_LVD1E_Pos);

        FSP_CRITICAL_SECTION_EXIT;
 #else
        *(g_lvdncmpcr_lut[monitor_index]) &= (uint8_t) ~R_SYSTEM_LVD1CMPCR_LVDE_Msk;
 #endif
#endif

        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);
        gp_ctrls[monitor_index] = NULL;
    }

#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
    else
    {
        uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 3;

        /* Enable access to LVD registers. */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

        /* Disable voltage monitor interrupt. */
        *g_ext_lvdicr_lut[monitor_index] &= (uint8_t) ~(LVD_PRV_EXT_LVDICR_IE_ENABLE);

        /* Disable voltage detection circuit. */
        *g_ext_lvdcmpcr_lut[monitor_index] &= (uint8_t) ~(R_SYSTEM_VBTCMPCR_CMPE_Msk);

        /* Disable pin LVD output. */
        *g_ext_lvdcr_lut[monitor_index] &= (uint8_t) ~(LVD_PRV_EXT_LVDCR_LVDE_ENABLE);

        /* Disable access to LVD registers. */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);
    }
#endif

    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup LVD-PVD)
 **********************************************************************************************************************/

/***********************************************************************************************************************
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
#if 2U == BSP_FEATURE_LVD_VERSION
    uint32_t lvd1cr = 0;

    /* Configure the voltage threshold setting. */
    lvd1cr &= (uint8_t) ~(R_SYSTEM_LVD1CR_LVD1V_Msk);
    lvd1cr |= (uint32_t) (p_ctrl->p_cfg->voltage_threshold << R_SYSTEM_LVD1CR_LVD1V_Pos);

    if (LVD_RESPONSE_NONE != p_ctrl->p_cfg->detection_response)
    {
        if (LVD_RESPONSE_INTERRUPT == p_ctrl->p_cfg->detection_response)
        {
            /* Configure the voltage monitor as interrupt mode. */
            lvd1cr |= LVD_PRV_LVD1CR_LVD1SEL_INTERRUPT << R_SYSTEM_LVD1CR_LVD1SEL_Pos;

            /* Configure the voltage monitor interrupt type as maskable. */
            lvd1cr |= LVD_PRV_LVD1CR_IRQSEL_MASKABLE << R_SYSTEM_LVD1CR_IRQSEL_Pos;

            /* Enable interrupt in NVIC. */
            R_BSP_IrqCfgEnable(p_ctrl->p_cfg->irq, p_ctrl->p_cfg->monitor_ipl, p_ctrl);
        }
        else if (LVD_RESPONSE_NMI == p_ctrl->p_cfg->detection_response)
        {
            /* Enable the NMI handler. */
            R_BSP_GroupIrqWrite((bsp_grp_irq_t) (BSP_GRP_IRQ_LVD1), lvd_nmi_handler);

            /* Configure the voltage monitor as interrupt mode. */
            lvd1cr |= LVD_PRV_LVD1CR_LVD1SEL_INTERRUPT << R_SYSTEM_LVD1CR_LVD1SEL_Pos;

            /* Configure the voltage monitor interrupt type as non-maskable. */
            lvd1cr |= LVD_PRV_LVD1CR_IRQSEL_NON_MASKABLE << R_SYSTEM_LVD1CR_IRQSEL_Pos;

            /* Enable NMI for this LVD monitor. NMIER bits can only be set. They cannot be cleared. */
            R_ICU->NMIER = (uint16_t) (R_ICU_NMIER_LVD1EN_Msk);
        }
        else                           /* LVD_RESPONSE_RESET */
        {
            /* Enable voltage monitor reset when the voltage falls to below threshold. */
            lvd1cr |= LVD_PRV_LVD1CR_LVD1SEL_RESET << R_SYSTEM_LVD1CR_LVD1SEL_Pos;
        }
    }

    /* Enable LVD1 operation. */
    lvd1cr |= LVD_PRV_LVD1CR_LVD1EN_ENABLE << R_SYSTEM_LVD1CR_LVD1EN_Pos;

    /* Enable access to LVD registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    /* Enable writing to the LVD1CR register. */
    R_SYSTEM->LVD1MKR_b.MK = LVD_PRV_LVD1MKR_MK_ENABLE;

    /* Writing to the LVD1CR register. */
    R_SYSTEM->LVD1CR = (uint8_t) lvd1cr;

    /* Disable writing to the LVD1CR register. */
    R_SYSTEM->LVD1MKR_b.MK = LVD_PRV_LVD1MKR_MK_DISABLE;

    /* Wait for LVD1 stabilization. */
    R_BSP_SoftwareDelay(BSP_FEATURE_LVD_MONITOR_1_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
#else
    FSP_CRITICAL_SECTION_DEFINE;

    uint32_t lvdncr0 = 0;
    uint32_t lvdncr1 = 0;

    /* Calculate index used to get monitor registers from look-up tables and perform other calculations. */
    uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 1;

    if (p_ctrl->p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_NMI)
    {
        /* Configure the voltage monitor interrupt condition. */
        lvdncr1 |= (uint32_t) (p_ctrl->p_cfg->voltage_slope << R_SYSTEM_LVD1CR1_IDTSEL_Pos);

        if (LVD_RESPONSE_NONE != p_ctrl->p_cfg->detection_response)
        {
            if (LVD_RESPONSE_INTERRUPT == p_ctrl->p_cfg->detection_response)
            {
                /* Configure the voltage monitor interrupt type as maskable. */
                lvdncr1 |= R_SYSTEM_LVD1CR1_IRQSEL_Msk;

                /* Enable interrupt in NVIC. */
                R_BSP_IrqCfgEnable(p_ctrl->p_cfg->irq, p_ctrl->p_cfg->monitor_ipl, p_ctrl);
            }
            else if (LVD_RESPONSE_NMI == p_ctrl->p_cfg->detection_response)
            {
                /* Enable the NMI handler. */
                R_BSP_GroupIrqWrite((bsp_grp_irq_t) (BSP_GRP_IRQ_LVD1 + monitor_index), lvd_nmi_handler);

                /* Enable NMI for this LVD monitor. NMIER bits can only be set. They cannot be cleared. */
                R_ICU->NMIER = (uint16_t) (1U << (2U + monitor_index));
            }
            else
            {
                /* LVD_RESPONSE_RESET or LVD_RESPONSE_RESET_ON_RISING. */

                /* Voltage monitor reset enabled. */
                lvdncr0 |= R_SYSTEM_LVD1CR0_RI_Msk;

                /* Configure the voltage monitor reset negation mode. */
                lvdncr0 |= (uint32_t) (p_ctrl->p_cfg->negation_delay << R_SYSTEM_LVD1CR0_RN_Pos);
            }
        }
    }

    /* Amount of time to wait before enabling output of voltage monitor comparison results. */
    uint32_t delay;
    if (LVD_MONITOR_LVD1 == p_ctrl->p_cfg->monitor_number)
    {
        /* LVD monitor is LVD1. */
        delay = BSP_FEATURE_LVD_MONITOR_1_STABILIZATION_TIME_US;
    }
    else
    {
        /* LVD monitor is LVD2. */
        delay = BSP_FEATURE_LVD_MONITOR_2_STABILIZATION_TIME_US;
    }

 #if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 1
    if (LVD_SAMPLE_CLOCK_DISABLED != p_ctrl->p_cfg->sample_clock_divisor)
    {
        /* Configure the digital filter clock divider. */
        lvdncr0 |= (uint32_t) (p_ctrl->p_cfg->sample_clock_divisor << R_SYSTEM_LVD1CR0_FSAMP_Pos);

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
        lvdncr0 |= R_SYSTEM_LVD1CR0_DFDIS_Msk;
    }
 #endif

    /* Setup procedure from Table 8.4 in the RA6M3 Hardware Manual R01UH0886EJ0100. */

    /* Enable access to LVD registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

 #if (BSP_FEATURE_LVD_HAS_LVDLVLR == 1)
    uint32_t lvdne_mask    = p_ctrl->p_cfg->monitor_number << R_SYSTEM_LVCMPCR_LVD1E_Pos;
    uint32_t lvdlvr_offset = g_lvdlvlr_offset_lut[monitor_index];

    /* Critical section required because LVCMPCR and LVDLVLR registers are shared with other instances. */
    FSP_CRITICAL_SECTION_ENTER;

    /* Disable the voltage detection circuit before writing the LVDLVLR register. */
    R_SYSTEM->LVCMPCR &= (uint8_t) ~lvdne_mask;

    /* Configure the voltage threshold setting. */
    uint32_t lvdlvlr = R_SYSTEM->LVDLVLR;
    lvdlvlr &= ~(g_lvdlvlr_mask_lut[monitor_index]);
    lvdlvlr |= (uint32_t) (p_ctrl->p_cfg->voltage_threshold << lvdlvr_offset);

    /* Write the voltage level setting. */
    R_SYSTEM->LVDLVLR = (uint8_t) lvdlvlr;

    /* Enable the voltage detection circuit. */
    R_SYSTEM->LVCMPCR |= (uint8_t) lvdne_mask;

    FSP_CRITICAL_SECTION_EXIT;
 #else

    /* Unlock control registers for PVD4 and PVD5.
     * Any additional write to PVDLR will lock it to 1 until the next POR, Reset pin toggle, or PVD0 reset. */
  #if (3U == BSP_FEATURE_LVD_VERSION)
    if (R_SYSTEM->PVDLR != 0)
    {
        R_SYSTEM->PVDLR = 0;
    }

    /* Write value to bit 6 in LVD4CR0 and LVD5CR0 should be 1. */
    if ((p_ctrl->p_cfg->monitor_number == 4) || (p_ctrl->p_cfg->monitor_number == 5))
    {
        lvdncr0 |= (uint8_t) (1 << R_SYSTEM_LVD4CR0_RI_Pos);
    }
  #endif
    uint8_t lvdne[LVD_PRV_NUMBER_OF_VCC_MONITOR];
    uint8_t i;

    /* Critical section required because LVCMPCR and LVDLVLR registers are shared with other instances. */
    FSP_CRITICAL_SECTION_ENTER;

    /* To change a LVDNLVL register both voltage detection circuits must be disabled.
     * Disable the voltage detection circuit for all monitors before writing the LVDLVLR register.
     * See section 7.2.2 "LVD1CMPCR : Voltage Monitoring 1 Comparator Control Register" in the RA6M4 manual R01HUM0890EJ0050. */

    for (i = 0; i < LVD_PRV_NUMBER_OF_VCC_MONITOR; i++)
    {
        if (0 != ((1 << i) & BSP_FEATURE_LVD_MONITOR_MASK))
        {
            /* Preserve enable values for other monitors. */
            lvdne[i] = *(g_lvdncmpcr_lut[i]) & R_SYSTEM_LVD1CMPCR_LVDE_Msk;

            /* Disable the monitor. */
            *(g_lvdncmpcr_lut[i]) &= (uint8_t) ~R_SYSTEM_LVD1CMPCR_LVDE_Msk;
        }
    }

    /* Configure the voltage threshold setting. */
    uint8_t lvdncmpcr = *(g_lvdncmpcr_lut[monitor_index]);
    lvdncmpcr &= (uint8_t) ~(g_lvdnlvl_mask_lut[monitor_index]);
    lvdncmpcr |= p_ctrl->p_cfg->voltage_threshold;

    /* Write the voltage level setting. */
    *(g_lvdncmpcr_lut[monitor_index]) = lvdncmpcr;

  #if BSP_FEATURE_LVD_SUPPORT_RESET_ON_RISING_EDGE
    if (LVD_RESPONSE_RESET_ON_RISING == p_ctrl->p_cfg->detection_response)
    {
        /* When LVD reset generated by the VCC-rise detection is required, RHSEL must be set to 1. */
        *(g_lvdnfcr_lut[monitor_index]) = 1;
    }
    else
    {
        *(g_lvdnfcr_lut[monitor_index]) = 0;
    }
  #endif

    /* Enable the voltage detection circuits. */
    for (i = 0; i < LVD_PRV_NUMBER_OF_VCC_MONITOR; i++)
    {
        if (0 != ((1 << i) & BSP_FEATURE_LVD_MONITOR_MASK))
        {
            if (monitor_index == i)
            {
                *(g_lvdncmpcr_lut[monitor_index]) |= R_SYSTEM_LVD1CMPCR_LVDE_Msk;
            }
            else
            {
                *(g_lvdncmpcr_lut[i]) |= lvdne[i];
            }
        }
    }
    FSP_CRITICAL_SECTION_EXIT;
 #endif

    /* Write settings to control registers. Write value to lvdncr0.bit3 should be 1. */
    *(g_lvdncr0_lut[monitor_index]) = (uint8_t) (lvdncr0 | LVD_PRV_LVDCR0_BIT3_MASK);
    *(g_lvdncr1_lut[monitor_index]) = (uint8_t) lvdncr1;

    if (p_ctrl->p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_NMI)
    {
        /* Clear DET before setting RIE. */
        *(g_lvdnsr_lut[monitor_index]) = 0;
    }

    if (LVD_RESPONSE_NONE != p_ctrl->p_cfg->detection_response)
    {
        /* Reset/Interrupt enable bit set after clearing DET bit. Write value to lvdncr0.bit3 should be 1. */
        *(g_lvdncr0_lut[monitor_index]) |= (R_SYSTEM_LVD1CR0_RIE_Msk | LVD_PRV_LVDCR0_BIT3_MASK);
    }

    /* Wait for LVD and filter stabilization. */
    R_BSP_SoftwareDelay(delay, BSP_DELAY_UNITS_MICROSECONDS);

    /* Enable output of comparison results by voltage monitor. Write value to lvdncr0.bit3 should be 1. */
    *(g_lvdncr0_lut[monitor_index]) |= (R_SYSTEM_LVD1CR0_CMPE_Msk | LVD_PRV_LVDCR0_BIT3_MASK);
#endif

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
    FSP_ERROR_RETURN(LVD_THRESHOLD_NOT_AVAILABLE != p_cfg->voltage_threshold, FSP_ERR_INVALID_ARGUMENT);
 #if (BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1)
    FSP_ASSERT(1U <= p_cfg->monitor_number && 5U >= p_cfg->monitor_number);
 #else
    FSP_ASSERT(0 != ((1 << (p_cfg->monitor_number - 1)) & BSP_FEATURE_LVD_MONITOR_MASK));
 #endif
 #if (3U == BSP_FEATURE_LVD_VERSION)
    if (p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_VCC_MONITOR)
    {
        FSP_ERROR_RETURN(NULL == gp_ctrls[p_cfg->monitor_number - 1], FSP_ERR_IN_USE);
    }

 #else
    if (p_cfg->monitor_number <= LVD_PRV_NUMBER_OF_NMI)
    {
        FSP_ERROR_RETURN(NULL == gp_ctrls[p_cfg->monitor_number - 1], FSP_ERR_IN_USE);
    }
 #endif

    int32_t threshold = (int32_t) p_cfg->voltage_threshold;

    /* Verify that the threshold is valid for voltage monitor. */
    switch (p_cfg->monitor_number)
    {
        case 1:
        {
            /* High voltage thresholds correspond to low register settings. */
            FSP_ASSERT(threshold >= (int32_t) BSP_FEATURE_LVD_MONITOR_1_HI_THRESHOLD &&
                       threshold <= (int32_t) BSP_FEATURE_LVD_MONITOR_1_LOW_THRESHOLD);
            break;
        }

        case 2:
 #if (3U == BSP_FEATURE_LVD_VERSION)
        case 4:
        case 5:
 #endif
            {
                /* High voltage thresholds correspond to low register settings. */
                FSP_ASSERT(threshold >= (int32_t) BSP_FEATURE_LVD_MONITOR_2_HI_THRESHOLD &&
                           threshold <= (int32_t) BSP_FEATURE_LVD_MONITOR_2_LOW_THRESHOLD);
                break;
            }

            /* If the device does not support an external monitor, the check below will be skipped. */
 #if (BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1)
        case 3:
        {
            /* High voltage thresholds correspond to low register settings. */
            FSP_ASSERT(threshold <= (int32_t) BSP_FEATURE_LVD_EXLVDVBAT_HI_THRESHOLD &&
                       threshold >= (int32_t) BSP_FEATURE_LVD_EXLVDVBAT_LOW_THRESHOLD);
            break;
        }

        case 4:
        {
            /* High voltage thresholds correspond to low register settings. */
            FSP_ASSERT(threshold <= (int32_t) BSP_FEATURE_LVD_EXLVDVRTC_HI_THRESHOLD &&
                       threshold >= (int32_t) BSP_FEATURE_LVD_EXLVDVRTC_LOW_THRESHOLD);
            break;
        }

        case 5:
        {
            /* Checking for EXLVD will be skipped because it doesn't have threshold configuration. */
            break;
        }
 #endif
        default:
        {
            break;
        }
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

 #if 3U == BSP_FEATURE_LVD_VERSION
    if ((p_cfg->monitor_number == 4) || (p_cfg->monitor_number == 5))
    {
        if (LVD_RESPONSE_RESET == p_cfg->detection_response)
        {
            /* Negation shall only follow a stabilization time (tPVDm) after VCC > Vdetm is detected on VCC-falling reset and VCC-rising reset. */
            FSP_ASSERT(LVD_NEGATION_DELAY_FROM_VOLTAGE == p_cfg->negation_delay);
        }
    }
 #endif
    if (LVD_RESPONSE_RESET_ON_RISING == p_cfg->detection_response)
    {
        /* Negation shall only follow a stabilization time (tPVDm) after VCC < Vdetm is detected on VCC-rising reset. */
        FSP_ASSERT(LVD_NEGATION_DELAY_FROM_VOLTAGE == p_cfg->negation_delay);
    }

 #if BSP_FEATURE_LVD_HAS_DIGITAL_FILTER == 0
    FSP_ERROR_RETURN(LVD_SAMPLE_CLOCK_DISABLED == p_cfg->sample_clock_divisor, FSP_ERR_UNSUPPORTED);
 #endif

    return FSP_SUCCESS;
}

#endif

/***********************************************************************************************************************
 * Private funtions configure LVD of VBAT, RTC, EX
 *
 * @param[in] p_ctrl            Pointer to the control block structure for the driver instance
 *
 **********************************************************************************************************************/
#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
static void r_lvd_ext_hw_configure (lvd_instance_ctrl_t * p_ctrl)
{
    /* Calculate index used to get monitor registers from look-up tables and perform other calculations. */
    uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 3;
 #if (0UL != BSP_FEATURE_LVD_VRTC_LVL_STABILIZATION_TIME_US)
    uint8_t current_rtclvl = 0;
    uint8_t new_rtclvl     = 0;
 #endif

    /* Enable access to LVD registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    /* Specify the detection voltage by setting the nLVDCR.LVL bits */
    switch (monitor_index)
    {
        case 0:
        {
            /* Configure voltage threshold for LVD of VBAT */
            *g_ext_lvdcr_lut[monitor_index] =
                (uint8_t) (p_ctrl->p_cfg->voltage_threshold << R_SYSTEM_VBTLVDCR_LVL_Pos);
            break;
        }

        case 1:
        {
 #if (0UL == BSP_FEATURE_LVD_VRTC_LVL_STABILIZATION_TIME_US)

            /* Configure voltage threshold for LVD of VRTC. */
            *g_ext_lvdcr_lut[monitor_index] =
                (uint8_t) (p_ctrl->p_cfg->voltage_threshold << R_SYSTEM_VRTLVDCR_LVL_Pos);
            break;
 #elif (0UL != BSP_FEATURE_LVD_VRTC_LVL_STABILIZATION_TIME_US)

            /* Check the current state and new desire state of LVL field. */
            new_rtclvl = (uint8_t) (p_ctrl->p_cfg->voltage_threshold) < LVD_THRESHOLD_LVDVRTC_LEVEL_1_99V ? 0 : 1;

            current_rtclvl = (uint8_t) (*g_ext_lvdcr_lut[monitor_index] >> R_SYSTEM_VRTLVDCR_LVL_Pos) <=
                             LVD_THRESHOLD_LVDVRTC_LEVEL_1_99V ? 0 : 1;

            /* If change from voltage_threshold > 2 back to voltage_threshold < 2 a intermediate stage and 300us is required. */
            if (new_rtclvl >= current_rtclvl)
            {
                /* Direct change */
                *g_ext_lvdcr_lut[monitor_index] =
                    (uint8_t) (p_ctrl->p_cfg->voltage_threshold << R_SYSTEM_VRTLVDCR_LVL_Pos);
            }
            else
            {
                /* Change to (intermediate stage) and wait 300us before change to desired voltage_threshold */
                *g_ext_lvdcr_lut[monitor_index] =
                    (uint8_t) (LVD_THRESHOLD_LVDVRTC_LEVEL_1_99V << R_SYSTEM_VRTLVDCR_LVL_Pos);
                R_BSP_SoftwareDelay((uint32_t) BSP_FEATURE_LVD_VRTC_LVL_STABILIZATION_TIME_US,
                                    BSP_DELAY_UNITS_MICROSECONDS);
                *g_ext_lvdcr_lut[monitor_index] =
                    (uint8_t) (p_ctrl->p_cfg->voltage_threshold << R_SYSTEM_VRTLVDCR_LVL_Pos);
            }
            break;
 #endif
        }

        case 2:
        {
            /* EXLVD doesn't have threshold configuration */
            break;
        }

        default:
        {
            break;
        }
    }

    /* Select the interrupt request timing in the nLVDICR.IDTSEL bits */
    *g_ext_lvdicr_lut[monitor_index] = (uint8_t) (p_ctrl->p_cfg->voltage_slope << R_SYSTEM_VBTLVDICR_IDTSEL_Pos);

    /* Set the nLVDCR.LVDE bit to 1 to enable pin low voltage detection */
    *g_ext_lvdcr_lut[monitor_index] |= (uint8_t) LVD_PRV_EXT_LVDCR_LVDE_ENABLE;

    /* Waiting for the comparator operation stabilization time */
    if (LVD_MONITOR_LVD_VBAT == p_ctrl->p_cfg->monitor_number)
    {
        /* LVD monitor is LVD VBAT. */
        R_BSP_SoftwareDelay((uint32_t) BSP_FEATURE_LVD_VBAT_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
    }
    else if (LVD_MONITOR_LVD_VRTC == p_ctrl->p_cfg->monitor_number)
    {
        /* LVD monitor is LVD VRTC. */
        R_BSP_SoftwareDelay((uint32_t) BSP_FEATURE_LVD_VRTC_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
    }
    else
    {
        /* LVD monitor is EXLVD. */
        R_BSP_SoftwareDelay((uint32_t) BSP_FEATURE_LVD_EXLVD_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
    }

    /* Set the nCMPCR.CMPE bit to 1 to enable pin voltage detect circuit. */
    *g_ext_lvdcmpcr_lut[monitor_index] = (uint8_t) R_SYSTEM_VBTCMPCR_CMPE_Msk;

    if (LVD_RESPONSE_NONE != p_ctrl->p_cfg->detection_response)
    {
        /* Make sure that the nSR.DET flag is 0. */
        *g_ext_lvdsr_lut[monitor_index] &= (uint8_t) (~R_SYSTEM_VBTLVDSR_DET_Msk);

        /* Set the nLVDICR.IE bit to 1 to enable pin low voltage detection interrupt output. */
        *g_ext_lvdicr_lut[monitor_index] |= (uint8_t) (LVD_PRV_EXT_LVDICR_IE_ENABLE);

        /* Enable interrupt in NVIC. */
        R_BSP_IrqCfgEnable(p_ctrl->p_cfg->irq, p_ctrl->p_cfg->monitor_ipl, p_ctrl);
    }
    else
    {
        /* Disable interrupt. */
        *g_ext_lvdicr_lut[monitor_index] &= (uint8_t) (~LVD_PRV_EXT_LVDICR_IE_ENABLE);
    }

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);
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
        /* Store on stack. */
        p_args = &callback_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        callback_args = *p_args;
    }

    p_args->current_state =
        (lvd_current_state_t) ((*(g_lvdnsr_lut[monitor_index]) & R_SYSTEM_LVD1SR_MON_Msk) > 0);
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
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

#if BSP_FEATURE_ICU_HAS_IELSR

    /* Clear the Interrupt Request. */
    R_BSP_IrqStatusClear(irq);
#endif

    /* Call common isr handler. */
    lvd_common_isr_handler((lvd_instance_ctrl_t *) R_FSP_IsrContextGet(irq));

    /* Restore context if RTOS is used. */
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
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE
    /* Call common isr handler. */
    lvd_common_isr_handler(gp_ctrls[irq - BSP_GRP_IRQ_LVD1]);

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * ISR for maskable interrupts LVD of VBAT, RTC, EX
 *
 **********************************************************************************************************************/
#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
void lvd_ext_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear the Interrupt Request. */
    R_BSP_IrqStatusClear(irq);

    /* Call common isr handler. */
    lvd_ext_common_isr_handler((lvd_instance_ctrl_t *) R_FSP_IsrContextGet(irq));

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}

#endif

/***********************************************************************************************************************
 * ISR handle for LVD interrupts of VBAT, RTC, EX
 *
 * @param[in] irq       BSP group IRQ indenttifier
 *
 **********************************************************************************************************************/
#if BSP_FEATURE_LVD_HAS_EXT_MONITOR == 1
static void lvd_ext_common_isr_handler (lvd_instance_ctrl_t * p_ctrl)
{
    /* Calculate index used to get monitor registers from look-up tables and perform other calculations. */
    uint32_t monitor_index = p_ctrl->p_cfg->monitor_number - 3;

    lvd_callback_args_t callback_args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be stored in
     * non-secure memory so they can be accessed by a non-secure callback function. */
    lvd_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack. */
        p_args = &callback_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        callback_args = *p_args;
    }

    p_args->current_state =
        (lvd_current_state_t) ((*(g_ext_lvdsr_lut[monitor_index]) & R_SYSTEM_VBTLVDSR_MON_Msk) > 0);
    p_args->monitor_number = p_ctrl->p_cfg->monitor_number;
    p_args->p_context      = p_ctrl->p_context;

    uint8_t det_flag = *g_ext_lvdsr_lut[monitor_index] & (uint8_t) (R_SYSTEM_VBTLVDSR_DET_Msk);

 #if BSP_TZ_SECURE_BUILD

    /* Make sure if nLVDSR.DET bit is 1. */
    if (det_flag != 0)
    {
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
    }

 #else

    /* Make sure if nLVDSR.DET bit is 1. */
    if (det_flag != 0)
    {
        /* If the project is not Trustzone Secure, then it will never need to change security state in order to call
         * the callback. */
        p_ctrl->p_callback(p_args);
    }
 #endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = callback_args;
    }

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LVD);

    /* Clear the status register. */
    *g_ext_lvdsr_lut[monitor_index] = 0;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LVD);
}

#endif
