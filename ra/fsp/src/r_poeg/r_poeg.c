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
#include "r_poeg.h"
#include "r_poeg_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "POEG" in ASCII, used to determine if channel is open. */
#define POEG_OPEN                (0x00475054ULL)

#define POEG_PRV_STATUS_FLAGS    (R_GPT_POEG0_POEGG_ST_Msk | R_GPT_POEG0_POEGG_SSF_Msk | R_GPT_POEG0_POEGG_OSTPF_Msk | \
                                  R_GPT_POEG0_POEGG_IOCF_Msk | R_GPT_POEG0_POEGG_PIDF_Msk)

#define POEG_PRV_FLAG_CLEAR      (R_GPT_POEG0_POEGG_SSF_Msk | R_GPT_POEG0_POEGG_OSTPF_Msk | R_GPT_POEG0_POEGG_IOCF_Msk | \
                                  R_GPT_POEG0_POEGG_PIDF_Msk)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/
void poeg_event_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Version data structure used by error logger macro. */
static const fsp_version_t g_poeg_version =
{
    .api_version_minor  = POEG_API_VERSION_MINOR,
    .api_version_major  = POEG_API_VERSION_MAJOR,
    .code_version_major = POEG_CODE_VERSION_MAJOR,
    .code_version_minor = POEG_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* POEG implementation of POEG interface  */
const poeg_api_t g_poeg_on_poeg =
{
    .open          = R_POEG_Open,
    .reset         = R_POEG_Reset,
    .outputDisable = R_POEG_OutputDisable,
    .statusGet     = R_POEG_StatusGet,
    .close         = R_POEG_Close,
    .versionGet    = R_POEG_VersionGet
};

/*******************************************************************************************************************//**
 * @addtogroup POEG
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes the POEG module and applies configurations. Implements @ref poeg_api_t::open.
 *
 * @note The @ref poeg_cfg_t::trigger setting can only be configured once after reset. Reopening with a different trigger
 * configuration is not possible.
 *
 * Example:
 * @snippet r_poeg_example.c R_POEG_Open
 *
 * @retval FSP_SUCCESS                    Initialization was successful.
 * @retval FSP_ERR_ASSERTION              A required input pointer is NULL or the source divider is invalid.
 * @retval FSP_ERR_ALREADY_OPEN           Module is already open.
 * @retval FSP_ERR_IRQ_BSP_DISABLED       poeg_cfg_t::p_callback is not NULL, but ISR is not enabled.  ISR must be
 *                                        enabled to use callback.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT The channel requested in the p_cfg parameter is not available on this device.
 **********************************************************************************************************************/
fsp_err_t R_POEG_Open (poeg_ctrl_t * const p_ctrl, poeg_cfg_t const * const p_cfg)
{
    poeg_instance_ctrl_t * p_instance_ctrl = (poeg_instance_ctrl_t *) p_ctrl;
#if POEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POEG_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(((1U << p_cfg->channel) & BSP_FEATURE_POEG_CHANNEL_MASK), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    if (p_cfg->p_callback)
    {
        FSP_ERROR_RETURN(p_cfg->irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);
    }

    if (p_cfg->irq >= 0)
    {
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }
#endif

    /* Save register base address. */
    uint32_t base_address = (uint32_t) R_GPT_POEG0 +
                            (p_cfg->channel * ((uint32_t) R_GPT_POEG1 - (uint32_t) R_GPT_POEG0));
    p_instance_ctrl->p_reg = (R_GPT_POEG0_Type *) base_address;
    p_instance_ctrl->p_cfg = p_cfg;

    /* Power on POEG before setting any hardware registers. */
    R_BSP_MODULE_START(FSP_IP_POEG, p_cfg->channel);

    /* Configure the POEGG register. */
    p_instance_ctrl->p_reg->POEGG = ((uint32_t) p_cfg->trigger << R_GPT_POEG0_POEGG_PIDE_Pos) |
                                    ((uint32_t) p_cfg->polarity << R_GPT_POEG0_POEGG_INV_Pos) |
                                    ((uint32_t) p_cfg->noise_filter << R_GPT_POEG0_POEGG_NFEN_Pos);

    /* Make sure the module is marked open before enabling the interrupt since the interrupt could fire immediately. */
    p_instance_ctrl->open = POEG_OPEN;

    /* Configure interrupt. */
    if (p_cfg->irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->irq, p_cfg->ipl, p_instance_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables GPT output pins. Implements @ref poeg_api_t::outputDisable.
 *
 * @retval FSP_SUCCESS                 GPT output pins successfully disabled.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POEG_OutputDisable (poeg_ctrl_t * const p_ctrl)
{
    poeg_instance_ctrl_t * p_instance_ctrl = (poeg_instance_ctrl_t *) p_ctrl;
#if POEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POEG_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable GPT output pins. */
    p_instance_ctrl->p_reg->POEGG_b.SSF = 1U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets status flags. Implements @ref poeg_api_t::reset.
 *
 * @note Status flags are only reset if the original POEG trigger is resolved. Check the status using
 * @ref R_POEG_StatusGet after calling this function to verify the status is cleared.
 *
 * Example:
 * @snippet r_poeg_example.c R_POEG_Reset
 *
 * @retval FSP_SUCCESS                 Function attempted to clear status flags.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POEG_Reset (poeg_ctrl_t * const p_ctrl)
{
    poeg_instance_ctrl_t * p_instance_ctrl = (poeg_instance_ctrl_t *) p_ctrl;
#if POEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POEG_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Reset POEG status flags. */
    p_instance_ctrl->p_reg->POEGG &= ~POEG_PRV_STATUS_FLAGS;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get current POEG status and store it in provided pointer p_status. Implements @ref poeg_api_t::statusGet.
 *
 * Example:
 * @snippet r_poeg_example.c R_POEG_StatusGet
 *
 * @retval FSP_SUCCESS                 Current POEG state stored successfully.
 * @retval FSP_ERR_ASSERTION           p_ctrl or p_status was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POEG_StatusGet (poeg_ctrl_t * const p_ctrl, poeg_status_t * const p_status)
{
    poeg_instance_ctrl_t * p_instance_ctrl = (poeg_instance_ctrl_t *) p_ctrl;
#if POEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(POEG_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get POEG state. */
    p_status->state = (poeg_state_t) (p_instance_ctrl->p_reg->POEGG & POEG_PRV_STATUS_FLAGS);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables POEG interrupt. Implements @ref poeg_api_t::close.
 *
 * @note This function does not disable the POEG.
 *
 * @retval FSP_SUCCESS                 Successful close.
 * @retval FSP_ERR_ASSERTION           p_ctrl was NULL.
 * @retval FSP_ERR_NOT_OPEN            The instance is not opened.
 **********************************************************************************************************************/
fsp_err_t R_POEG_Close (poeg_ctrl_t * const p_ctrl)
{
    poeg_instance_ctrl_t * p_instance_ctrl = (poeg_instance_ctrl_t *) p_ctrl;

#if POEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(POEG_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable interrupts. */
    if (p_instance_ctrl->p_cfg->irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->irq);
        R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->irq, NULL);
    }

    /* Clear open flag. */
    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets driver version based on compile time macros. Implements @ref poeg_api_t::versionGet.
 *
 * @retval FSP_SUCCESS                 Version stored in p_version.
 * @retval FSP_ERR_ASSERTION           p_version was NULL.
 **********************************************************************************************************************/
fsp_err_t R_POEG_VersionGet (fsp_version_t * const p_version)
{
#if POEG_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_poeg_version.version_id;

    return FSP_SUCCESS;
}

/** @} (end addtogroup POEG) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Notifies user of POEG event.
 **********************************************************************************************************************/
void poeg_event_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    poeg_instance_ctrl_t * p_instance_ctrl = (poeg_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Set data to identify callback to user, then call user callback. */
    poeg_callback_args_t callback_args;
    callback_args.p_context = p_instance_ctrl->p_cfg->p_context;
    p_instance_ctrl->p_cfg->p_callback(&callback_args);

    /* Clear pending IRQ to make sure it doesn't fire again after exiting.  This is a level interrupt, so it must be
     * cleared at the end of the ISR. */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
