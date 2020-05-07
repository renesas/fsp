/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "r_icu.h"
#include "r_icu_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "ICU" in ASCII, used to determine if channel is open. */
#define ICU_OPEN              (0x00494355U)

#define ICU_IRQMD_OFFSET      (0)
#define ICU_FCLKSEL_OFFSET    (4)
#define ICU_FLTEN_OFFSET      (7)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void r_icu_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure used by error logger macro. */
static const fsp_version_t g_icu_version =
{
    .api_version_minor  = EXTERNAL_IRQ_API_VERSION_MINOR,
    .api_version_major  = EXTERNAL_IRQ_API_VERSION_MAJOR,
    .code_version_major = ICU_CODE_VERSION_MAJOR,
    .code_version_minor = ICU_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* ICU implementation of External IRQ API. */
const external_irq_api_t g_external_irq_on_icu =
{
    .open       = R_ICU_ExternalIrqOpen,
    .enable     = R_ICU_ExternalIrqEnable,
    .disable    = R_ICU_ExternalIrqDisable,
    .close      = R_ICU_ExternalIrqClose,
    .versionGet = R_ICU_ExternalIrqVersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup ICU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure an IRQ input pin for use with the external interrupt interface.  Implements @ref external_irq_api_t::open.
 *
 * The Open function is responsible for preparing an external IRQ pin for operation.
 *
 * @retval FSP_SUCCESS                    Open successful.
 * @retval FSP_ERR_ASSERTION              One of the following is invalid:
 *                                          - p_ctrl or p_cfg is NULL
 * @retval FSP_ERR_ALREADY_OPEN           The channel specified has already been opened. No configurations were changed.
 *                                        Call the associated Close function to reconfigure the channel.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in p_cfg is not available on the device selected in
 *                                        r_bsp_cfg.h.
 * @retval FSP_ERR_INVALID_ARGUMENT       p_cfg->p_callback is not NULL, but ISR is not enabled. ISR must be enabled to
 *                                        use callback function.
 *
 * @note This function is reentrant for different channels.  It is not reentrant for the same channel.
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqOpen (external_irq_ctrl_t * const p_api_ctrl, external_irq_cfg_t const * const p_cfg)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(0 != ((1U << p_cfg->channel) & BSP_FEATURE_ICU_IRQ_CHANNELS_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Callback must be used with a valid interrupt priority otherwise it will never be called. */
    if (p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(BSP_IRQ_DISABLED != p_cfg->ipl, FSP_ERR_INVALID_ARGUMENT);
    }
#endif

    p_ctrl->irq = p_cfg->irq;

    /* IELSR Must be zero when modifying the IRQCR bits.
     * (See ICU Section 14.2.1 of the RA6M3 manual R01UH0886EJ0100). */
    uint32_t ielsr = R_ICU->IELSR[p_ctrl->irq];
    R_ICU->IELSR[p_ctrl->irq] = 0;

    /* Initialize control block. */
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;
    p_ctrl->channel    = p_cfg->channel;

    /* Disable digital filter */
    R_ICU->IRQCR[p_ctrl->channel] = 0U;

    /* Set the digital filter divider. */
    uint8_t irqcr = (uint8_t) (p_cfg->pclk_div << ICU_FCLKSEL_OFFSET);

    /* Enable/Disable digital filter. */
    irqcr |= (uint8_t) (p_cfg->filter_enable << ICU_FLTEN_OFFSET);

    /* Set the IRQ trigger. */
    irqcr |= (uint8_t) (p_cfg->trigger << ICU_IRQMD_OFFSET);

    /* Write IRQCR */
    R_ICU->IRQCR[p_ctrl->channel] = irqcr;

    /* Restore IELSR. */
    R_ICU->IELSR[p_ctrl->irq] = ielsr;

    /* NOTE: User can have the driver opened when the IRQ is not in the vector table. This is for use cases
     * where the external IRQ driver is used to generate ELC events only (without CPU interrupts).
     * In such cases we will not set the IRQ priority but will continue with the processing.
     */
    if (p_ctrl->irq >= 0)
    {
        R_BSP_IrqCfg(p_ctrl->irq, p_cfg->ipl, p_ctrl);
    }

    /* Mark the control block as open */
    p_ctrl->open = ICU_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable external interrupt for specified channel at NVIC. Implements @ref external_irq_api_t::enable.
 *
 * @retval FSP_SUCCESS                 Interrupt Enabled successfully.
 * @retval FSP_ERR_ASSERTION           The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    Requested IRQ is not defined in this system
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqEnable (external_irq_ctrl_t * const p_api_ctrl)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_ctrl->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
#endif

    /* Clear the interrupt status and Pending bits, before the interrupt is enabled. */
    R_BSP_IrqEnable(p_ctrl->irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable external interrupt for specified channel at NVIC. Implements @ref external_irq_api_t::disable.
 *
 * @retval FSP_SUCCESS                 Interrupt disabled successfully.
 * @retval FSP_ERR_ASSERTION           The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 * @retval FSP_ERR_IRQ_BSP_DISABLED    Requested IRQ is not defined in this system
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqDisable (external_irq_ctrl_t * const p_api_ctrl)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_ctrl->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
#endif

    /* Disable the interrupt, and then clear the interrupt pending bits and interrupt status. */
    R_BSP_IrqDisable(p_ctrl->irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close the external interrupt channel. Implements @ref external_irq_api_t::close.
 *
 * @retval     FSP_SUCCESS          Successfully closed.
 * @retval     FSP_ERR_ASSERTION    The parameter p_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN     The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqClose (external_irq_ctrl_t * const p_api_ctrl)
{
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) p_api_ctrl;

#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(ICU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Cleanup. Disable interrupt */
    if (p_ctrl->irq >= 0)
    {
        /* Disable the interrupt, and then clear the interrupt pending bits and interrupt status. */
        R_BSP_IrqDisable(p_ctrl->irq);
        R_FSP_IsrContextSet(p_ctrl->irq, NULL);
    }

    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set driver version based on compile time macros.  Implements @ref external_irq_api_t::versionGet.
 *
 * @retval     FSP_SUCCESS        Successful close.
 * @retval     FSP_ERR_ASSERTION  The parameter p_version is NULL.
 **********************************************************************************************************************/
fsp_err_t R_ICU_ExternalIrqVersionGet (fsp_version_t * const p_version)
{
#if ICU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_icu_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ICU)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * ICU External Interrupt ISR.
 **********************************************************************************************************************/
void r_icu_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    bool level_irq = false;
    if (EXTERNAL_IRQ_TRIG_LEVEL_LOW == R_ICU->IRQCR_b[p_ctrl->channel].IRQMD)
    {
        level_irq = true;
    }
    else
    {
        /* Clear the IR bit before calling the user callback so that if an edge is detected while the ISR is active
         * it will not be missed. */
        R_BSP_IrqStatusClear(irq);
    }

    if ((NULL != p_ctrl) && (NULL != p_ctrl->p_callback))
    {
        /* Set data to identify callback to user, then call user callback. */
        external_irq_callback_args_t args;
        args.channel   = p_ctrl->channel;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args);
    }

    if (level_irq)
    {
        /* Clear the IR bit after calling the user callback so that if the condition is cleared the ISR will not
         * be called again. */
        R_BSP_IrqStatusClear(irq);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
