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
#include "r_cac.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "CAC" in ASCII, used to determine if channel is open. */
#define CAC_OPEN                        (0x00434143ULL)

/* CAC Control Register 0 Bit Field Definitions */
#define CAC_PRV_CACR0_CFME_OFFSET       (0U)
#define CAC_PRV_CACR0_CFME_MASK         (1U << CAC_PRV_CACR0_CFME_OFFSET)

/* CAC Control Register 1 Bit Field Definitions */
#define CAC_PRV_CACR1_CACREFE_OFFSET    (0U)
#define CAC_PRV_CACR1_CACREFE_MASK      (1U << CAC_PRV_CACR1_CACREFE_OFFSET)
#define CAC_PRV_CACR1_FMCS_OFFSET       (1U)
#define CAC_PRV_CACR1_FMCS_MASK         (0x07U << CAC_PRV_CACR1_FMCS_OFFSET)
#define CAC_PRV_CACR1_TCSS_OFFSET       (4U)
#define CAC_PRV_CACR1_TCSS_MASK         (0x03U << CAC_PRV_CACR1_TCSS_OFFSET)
#define CAC_PRV_CACR1_EDGES_OFFSET      (6U)
#define CAC_PRV_CACR1_EDGES_MASK        (0x03U << CAC_PRV_CACR1_EDGES_OFFSET)

/* CAC Control Register 2 Bit Field Definitions */
#define CAC_PRV_CACR2_RPS_OFFSET        (0U)
#define CAC_PRV_CACR2_RPS_MASK          (1U << CAC_PRV_CACR2_RPS_OFFSET)
#define CAC_PRV_CACR2_RSCS_OFFSET       (1U)
#define CAC_PRV_CACR2_RCSC_MASK         (0x07U << CAC_PRV_CACR2_RSCS_OFFSET)
#define CAC_PRV_CACR2_RCDS_OFFSET       (4U)
#define CAC_PRV_CACR2_RCDS_MASK         (0x03U << CAC_PRV_CACR2_RCDS_OFFSET)
#define CAC_PRV_CACR2_DFS_OFFSET        (6U)
#define CAC_PRV_CACR2_DFS_MASK          (0x03U << CAC_PRV_CACR2_DFS_OFFSET)

/* CAC Interrupt Control Register Bit Field Definitions */
#define CAC_PRV_CAICR_FERRIE_OFFSET     (0U)
#define CAC_PRV_CAICR_FERRIE_MASK       (1U << CAC_PRV_CAICR_FERRIE_OFFSET)
#define CAC_PRV_CAICR_MENDIE_OFFSET     (1U)
#define CAC_PRV_CAICR_MENDIE_MASK       (1U << CAC_PRV_CAICR_MENDIE_OFFSET)
#define CAC_PRV_CAICR_OVFIE_OFFSET      (2U)
#define CAC_PRV_CAICR_OVFIE_MASK        (1U << CAC_PRV_CAICR_OVFIE_OFFSET)
#define CAC_PRV_CAICR_FERRFCL_OFFSET    (4U)
#define CAC_PRV_CAICR_FERRFCL_MASK      (1U << CAC_PRV_CAICR_FERRFCL_OFFSET)
#define CAC_PRV_CAICR_MENDFCL_OFFSET    (5U)
#define CAC_PRV_CAICR_MENDFCL_MASK      (1U << CAC_PRV_CAICR_MENDFCL_OFFSET)
#define CAC_PRV_CAICR_OVFFCL_OFFSET     (6U)
#define CAC_PRV_CAICR_OVFFCL_MASK       (1U << CAC_PRV_CAICR_OVFFCL_OFFSET)

/* CAC Status Register Bit Field Definitions */
#define CAC_PRV_CASTR_FERRF_OFFSET      (0U)
#define CAC_PRV_CASTR_FERRF_MASK        (1U << CAC_PRV_CASTR_FERRF_OFFSET)
#define CAC_PRV_CASTR_MENDF_OFFSET      (1U)
#define CAC_PRV_CASTR_MENDF_MASK        (1U << CAC_PRV_CASTR_MENDF_OFFSET)
#define CAC_PRV_CASTR_OVFF_OFFSET       (2U)
#define CAC_PRV_CASTR_OVFF_MASK         (1U << CAC_PRV_CASTR_OVFF_OFFSET)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
void cac_ferri_isr(void);
void cac_mendi_isr(void);
void cac_ovfi_isr(void);

static void r_cac_hw_configure(cac_instance_ctrl_t * const p_instance_ctrl);
static void r_cac_isr_handler(cac_event_t event, uint32_t clear_mask);

/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char g_module_name[] = "cac";
#endif

/** Version data structure used by error logger macro. */
static const fsp_version_t g_cac_version =
{
    .api_version_minor  = CAC_API_VERSION_MINOR,
    .api_version_major  = CAC_API_VERSION_MAJOR,
    .code_version_major = CAC_CODE_VERSION_MAJOR,
    .code_version_minor = CAC_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* CAC Implementation. */
const cac_api_t g_cac_on_cac =
{
    .open             = R_CAC_Open,
    .startMeasurement = R_CAC_StartMeasurement,
    .stopMeasurement  = R_CAC_StopMeasurement,
    .read             = R_CAC_Read,
    .close            = R_CAC_Close,
    .versionGet       = R_CAC_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup CAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * The Open function configures the CAC based on the provided user configuration settings.
 *
 * @retval     FSP_SUCCESS               CAC is available and available for measurement(s).
 * @retval     FSP_ERR_ASSERTION         An argument is invalid.
 * @retval     FSP_ERR_ALREADY_OPEN      The CAC has already been opened.
 *
 * @note       There is only a single CAC peripheral.
 **********************************************************************************************************************/
fsp_err_t R_CAC_Open (cac_ctrl_t * const p_ctrl, cac_cfg_t const * const p_cfg)
{
    cac_instance_ctrl_t * p_instance_ctrl = (cac_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if (CAC_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(CAC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);

    /* Ensure that upper limit is not less than the lower limit. If they are both the same (ie. 0) we will allow
     * measurement to proceed. */
    FSP_ASSERT(p_cfg->cac_upper_limit >= p_cfg->cac_lower_limit);
#endif

    p_instance_ctrl->p_cfg = p_cfg;

    /* Configure the CAC per the configuration. */
    r_cac_hw_configure(p_instance_ctrl);

    /* Mark driver as open by initializing it to "CAC" - its ASCII equivalent. */
    p_instance_ctrl->open = CAC_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Start the CAC measurement process.
 *
 * @retval     FSP_SUCCESS        CAC measurement started.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_instance_ctrl or p_cfg.
 * @retval     FSP_ERR_NOT_OPEN   R_CAC_Open() has not been successfully called.
 **********************************************************************************************************************/
fsp_err_t R_CAC_StartMeasurement (cac_ctrl_t * const p_ctrl)
{
#if (CAC_CFG_PARAM_CHECKING_ENABLE == 1)
    cac_instance_ctrl_t * p_instance_ctrl = (cac_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN((CAC_OPEN == p_instance_ctrl->open), FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Start CAC measurement. */
    R_CAC->CACR0 = 1U;

    /* Read CFME bit to confirm the bit value has changed. See section 10.2.1 CAC Control Register 0 of the RA6M3
     * manual R01UH0886EJ0100. */
    FSP_HARDWARE_REGISTER_WAIT(R_CAC->CACR0, 1U);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stop the CAC measurement process.
 *
 * @retval     FSP_SUCCESS        CAC measuring has been stopped.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_instance_ctrl or p_cfg.
 * @retval     FSP_ERR_NOT_OPEN   R_CAC_Open() has not been successfully called.
 **********************************************************************************************************************/
fsp_err_t R_CAC_StopMeasurement (cac_ctrl_t * const p_ctrl)
{
#if (CAC_CFG_PARAM_CHECKING_ENABLE == 1)
    cac_instance_ctrl_t * p_instance_ctrl = (cac_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN((CAC_OPEN == p_instance_ctrl->open), FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Disable measurements. */
    R_CAC->CACR0 = 0U;

    /* Read CFME bit to confirm the bit value has changed. See section 10.2.1 CAC Control Register 0 of the RA6M3
     * manual R01UH0886EJ0100. */
    FSP_HARDWARE_REGISTER_WAIT(R_CAC->CACR0, 0);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read and return the CAC status and counter registers.
 *
 * @retval     FSP_SUCCESS        CAC read successful.
 * @retval     FSP_ERR_ASSERTION  An argument is NULL.
 * @retval     FSP_ERR_NOT_OPEN   R_CAC_Open() has not been successfully called.
 **********************************************************************************************************************/
fsp_err_t R_CAC_Read (cac_ctrl_t * const p_ctrl, uint16_t * const p_counter)
{
#if (CAC_CFG_PARAM_CHECKING_ENABLE == 1)
    cac_instance_ctrl_t * p_instance_ctrl = (cac_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_counter);
    FSP_ERROR_RETURN((CAC_OPEN == p_instance_ctrl->open), FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Read the CAC count buffer. */
    *p_counter = R_CAC->CACNTBR;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Release any resources that were allocated by the Open() or any subsequent CAC operations.
 *
 * @retval     FSP_SUCCESS        Successful close.
 * @retval     FSP_ERR_ASSERTION  NULL provided for p_instance_ctrl or p_cfg.
 * @retval     FSP_ERR_NOT_OPEN   R_CAC_Open() has not been successfully called.
 **********************************************************************************************************************/
fsp_err_t R_CAC_Close (cac_ctrl_t * const p_ctrl)
{
    cac_instance_ctrl_t * p_instance_ctrl = (cac_instance_ctrl_t *) p_ctrl;
#if (CAC_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN((CAC_OPEN == p_instance_ctrl->open), FSP_ERR_NOT_OPEN);
#endif

    /* Disable measurements. */
    R_CAC->CACR0 = 0U;

    /* Disable interrupts in NVIC. */
    NVIC_DisableIRQ(p_instance_ctrl->p_cfg->ferri_irq);
    NVIC_DisableIRQ(p_instance_ctrl->p_cfg->mendi_irq);
    NVIC_DisableIRQ(p_instance_ctrl->p_cfg->ovfi_irq);

    /* Read CFME bit to confirm the bit value has changed. See section 10.2.1 CAC Control Register 0 of the RA6M3
     * manual R01UH0886EJ0100. */
    FSP_HARDWARE_REGISTER_WAIT(R_CAC->CACR0, 0);

    /* Power down peripheral. */
    R_BSP_MODULE_STOP(FSP_IP_CAC, 0);

    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the API and code version information.
 *
 * @retval FSP_SUCCESS              Version info returned.
 * @retval FSP_ERR_ASSERTION        An argument is NULL.
 **********************************************************************************************************************/
fsp_err_t R_CAC_VersionGet (fsp_version_t * const p_version)
{
#if CAC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_cac_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup CAC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Write the configuration to CAC registers.
 * @param[in]  p_instance_ctrl  A pointer to the instance control structure.
 **********************************************************************************************************************/
static void r_cac_hw_configure (cac_instance_ctrl_t * const p_instance_ctrl)
{
    cac_cfg_t const * p_cfg = p_instance_ctrl->p_cfg;

    uint32_t cacr1 = 0;
    uint32_t cacr2 = 0;
    uint32_t caicr = 0;

    /* Apply power to the peripheral */
    R_BSP_MODULE_START(FSP_IP_CAC, 0);

    /* Disable measurements. */
    R_CAC->CACR0 = 0U;

    /* Read CFME bit to confirm the bit value has changed. See section 10.2.1 CAC Control Register 0 of the RA6M3
     * manual R01UH0886EJ0100. */
    FSP_HARDWARE_REGISTER_WAIT(R_CAC->CACR0, 0);

    /* Clear interrupt status flags. */
    R_CAC->CAICR = CAC_PRV_CAICR_FERRFCL_MASK | CAC_PRV_CAICR_MENDFCL_MASK | CAC_PRV_CAICR_OVFFCL_MASK;

    /* Configure measurement clock divider. */
    cacr1 |= (uint32_t) (p_instance_ctrl->p_cfg->cac_meas_clock.divider << CAC_PRV_CACR1_TCSS_OFFSET);

    if (p_cfg->cac_ref_clock.clock == CAC_CLOCK_SOURCE_EXTERNAL)
    {
        /* Enable CACREF. */
        cacr1 |= CAC_PRV_CACR1_CACREFE_MASK;
    }
    else
    {
        /* Configure the CAC reference clock. */
        cacr2 |= (uint32_t) (p_cfg->cac_ref_clock.clock << CAC_PRV_CACR2_RSCS_OFFSET) |
                 CAC_PRV_CACR2_RPS_MASK;
    }

    /* Configure edge detection. */
    cacr1 |= (uint32_t) (p_cfg->cac_ref_clock.edge << CAC_PRV_CACR1_EDGES_OFFSET);

    /* Configure the digital filter. */
    cacr2 |= (uint32_t) (p_cfg->cac_ref_clock.digfilter << CAC_PRV_CACR2_DFS_OFFSET);

    /* Configure reference clock divider. */
    cacr2 |= (uint32_t) (p_cfg->cac_ref_clock.divider << CAC_PRV_CACR2_RCDS_OFFSET);

    /* Configure the measurement clock. */
    cacr1 |= (uint32_t) (p_cfg->cac_meas_clock.clock << CAC_PRV_CACR1_FMCS_OFFSET);

    if (p_cfg->mendi_irq >= 0)
    {
        /* Enable the measurement end interrupt. */
        R_BSP_IrqCfgEnable(p_cfg->mendi_irq, p_cfg->mendi_ipl, p_instance_ctrl);
        caicr |= CAC_PRV_CAICR_MENDIE_MASK;
    }

    if (p_instance_ctrl->p_cfg->ovfi_irq >= 0)
    {
        /* Enable the measurement overflow interrupt. */
        R_BSP_IrqCfgEnable(p_cfg->ovfi_irq, p_cfg->ovfi_ipl, p_instance_ctrl);
        caicr |= CAC_PRV_CAICR_OVFIE_MASK;
    }

    if (p_cfg->ferri_irq >= 0)
    {
        /* Enable the frequency error interrupt. */
        R_BSP_IrqCfgEnable(p_cfg->ferri_irq, p_cfg->ferri_ipl, p_instance_ctrl);
        caicr |= CAC_PRV_CAICR_FERRIE_MASK;
    }

    /* Write settings to registers. */
    R_CAC->CACR1  = (uint8_t) cacr1;
    R_CAC->CACR2  = (uint8_t) cacr2;
    R_CAC->CAICR  = (uint8_t) caicr;
    R_CAC->CAULVR = p_cfg->cac_upper_limit;
    R_CAC->CALLVR = p_cfg->cac_lower_limit;
}

/*******************************************************************************************************************//**
 * Generic routine for handling all of the CAC interrupts.
 *
 * @param[in]  event           The event to pass into the callback args.
 * @param[in]  clear_mask      The status bit to clear.
 **********************************************************************************************************************/
static void r_cac_isr_handler (cac_event_t event, uint32_t clear_mask)
{
    IRQn_Type             irq             = R_FSP_CurrentIrqGet();
    cac_instance_ctrl_t * p_instance_ctrl = (cac_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        /* Call the user defined callback. */
        cac_callback_args_t cb_data;
        cb_data.event     = event;
        cb_data.p_context = p_instance_ctrl->p_cfg->p_context;
        p_instance_ctrl->p_cfg->p_callback(&cb_data);
    }

    /* Clear the status flag. */
    R_CAC->CAICR |= (uint8_t) clear_mask;
    R_BSP_IrqStatusClear(irq);
}

/*******************************************************************************************************************//**
 * CAC Frequency error ISR.
 **********************************************************************************************************************/
void cac_ferri_isr (void)
{
    FSP_CONTEXT_SAVE;

    r_cac_isr_handler(CAC_EVENT_FREQUENCY_ERROR, CAC_PRV_CAICR_FERRFCL_MASK);

    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * CAC Overflow ISR.
 **********************************************************************************************************************/
void cac_ovfi_isr (void)
{
    FSP_CONTEXT_SAVE;

    r_cac_isr_handler(CAC_EVENT_COUNTER_OVERFLOW, CAC_PRV_CAICR_OVFFCL_MASK);

    FSP_CONTEXT_RESTORE;
}

/*******************************************************************************************************************//**
 * CAC Measurement Complete ISR.
 **********************************************************************************************************************/
void cac_mendi_isr (void)
{
    FSP_CONTEXT_SAVE;

    r_cac_isr_handler(CAC_EVENT_MEASUREMENT_COMPLETE, CAC_PRV_CAICR_MENDFCL_MASK);

    FSP_CONTEXT_RESTORE;
}
