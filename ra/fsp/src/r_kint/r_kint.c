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
#include "r_kint_cfg.h"
#include "r_kint.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define KINT_OPEN    (0x4B494E54)

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

void key_int_isr(void);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* KeyMatrix Implementation of Key Interrupt  */
const keymatrix_api_t g_keymatrix_on_kint =
{
    .open    = R_KINT_Open,
    .enable  = R_KINT_Enable,
    .disable = R_KINT_Disable,
    .close   = R_KINT_Close,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup KINT
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure all the Key Input (KINT) channels and provides a handle for use with the rest of the KINT API functions.
 * Implements @ref keymatrix_api_t::open.
 *
 * @retval     FSP_SUCCESS                     Initialization was successful.
 * @retval     FSP_ERR_ASSERTION               One of the following parameters may be NULL: p_cfg, or p_ctrl or the
 *                                             callback.
 * @retval     FSP_ERR_ALREADY_OPEN            The module has already been opened.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  The channel mask is invalid.
 **********************************************************************************************************************/
fsp_err_t R_KINT_Open (keymatrix_ctrl_t * const p_api_ctrl, keymatrix_cfg_t const * const p_cfg)
{
    kint_instance_ctrl_t * p_ctrl = (kint_instance_ctrl_t *) p_api_ctrl;

    /* Check to see that the arguments passed are not null pointers */
#if KINT_CFG_PARAM_CHECKING_ENABLE

    /* Check NULL pointers */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);

    /* Check that the interrupt is valid. */
    FSP_ASSERT(p_cfg->irq >= 0);

    /* Check that the Open function has been called else return FSP_ERR_NOT_OPEN */
    FSP_ERROR_RETURN(0 == p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Check  that the selected channels are valid. */
    FSP_ERROR_RETURN(p_cfg->channel_mask <= UINT8_MAX, FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

#if BSP_FEATURE_KINT_HAS_MSTP

    /* Clear the Module Stop bit. */
    R_BSP_MODULE_START(FSP_IP_KEY, 0);
#endif

    p_ctrl->p_cfg = p_cfg;

    /* Configure the trigger edge. */
    R_KINT->KRCTL = (uint8_t) p_cfg->trigger | R_KINT_KRCTL_KRMD_Msk;

    /* Enable interrupt for the selected channels after casting since KRM is an 8 bit register */
    R_KINT->KRM = 0;

    /* Configure the interrupt priority. */
    R_BSP_IrqCfg(p_cfg->irq, p_cfg->ipl, p_ctrl);

    /* Mark KINT as initialized */
    p_ctrl->open = KINT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Clear the KINT configuration and disable the KINT IRQ. Implements @ref keymatrix_api_t::close.
 *
 * @retval FSP_SUCCESS        Successful close.
 * @retval FSP_ERR_ASSERTION  The parameter p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN   The module is not opened.
 **********************************************************************************************************************/
fsp_err_t R_KINT_Close (keymatrix_ctrl_t * const p_api_ctrl)
{
    kint_instance_ctrl_t * p_ctrl = (kint_instance_ctrl_t *) p_api_ctrl;

#if KINT_CFG_PARAM_CHECKING_ENABLE

    /* Check for null pointers */
    FSP_ASSERT(NULL != p_ctrl);

    /* Check that the Open function has been called else return FSP_ERR_NOT_OPEN */
    FSP_ERROR_RETURN(p_ctrl->open == KINT_OPEN, FSP_ERR_NOT_OPEN);
#endif

    /** Disable interrupt in NVIC. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->irq);

    /** Disable interrupts in the KINT peripheral*/
    R_KINT->KRM = 0U;

#if BSP_FEATURE_KINT_HAS_MSTP

    /* Set the Module Stop bit. */
    R_BSP_MODULE_STOP(FSP_IP_KEY, 0);
#endif

    /* Mark KINT as un-initialized */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function enables interrupts for the KINT peripheral after clearing any pending requests.
 * Implements @ref keymatrix_api_t::enable.
 *
 * @retval FSP_SUCCESS        Interrupt enabled successfully.
 * @retval FSP_ERR_ASSERTION  The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN   The peripheral is not opened.
 **********************************************************************************************************************/
fsp_err_t R_KINT_Enable (keymatrix_ctrl_t * const p_api_ctrl)
{
    kint_instance_ctrl_t * p_ctrl = (kint_instance_ctrl_t *) p_api_ctrl;

#if KINT_CFG_PARAM_CHECKING_ENABLE

    /* Check for null pointer. */
    FSP_ASSERT(NULL != p_ctrl);

    /* Check that the Open function has been called else return FSP_ERR_NOT_OPEN */
    FSP_ERROR_RETURN(p_ctrl->open == KINT_OPEN, FSP_ERR_NOT_OPEN);
#endif

    /* Enable interrupt for the selected channels after casting since KRM is an 8 bit register */
    R_KINT->KRM = (uint8_t) p_ctrl->p_cfg->channel_mask;

    /* Clear any pending interrupt requests in the KINT peripheral */
    R_KINT->KRF = 0;

    /* Enable interrupt */
    R_BSP_IrqEnable(p_ctrl->p_cfg->irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function disables interrupts for the KINT peripheral. Implements @ref keymatrix_api_t::disable.
 *
 * @retval FSP_SUCCESS        Interrupt disabled successfully.
 * @retval FSP_ERR_ASSERTION  The p_ctrl parameter was null.
 * @retval FSP_ERR_NOT_OPEN   The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_KINT_Disable (keymatrix_ctrl_t * const p_api_ctrl)
{
    kint_instance_ctrl_t * p_ctrl = (kint_instance_ctrl_t *) p_api_ctrl;

#if KINT_CFG_PARAM_CHECKING_ENABLE

    /* Check for null pointers */
    FSP_ASSERT(NULL != p_ctrl);

    /* Check that the Open function has been called else return FSP_ERR_NOT_OPEN */
    FSP_ERROR_RETURN(p_ctrl->open == KINT_OPEN, FSP_ERR_NOT_OPEN);
#endif

    /* Disable interrupt in the ICU */
    R_BSP_IrqDisable(p_ctrl->p_cfg->irq);

    /* Disable interrupts in the KINT peripheral */
    R_KINT->KRM = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup KINT)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * ISR for handling key interrupts. It calls p_callback with a mask of channels that caused the interrupt.
 **********************************************************************************************************************/
void key_int_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type              irq    = R_FSP_CurrentIrqGet();
    kint_instance_ctrl_t * p_ctrl = (kint_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Read the state of the Key Input pins/ */
    uint8_t status = R_KINT->KRF;

    /* The IRQ status must be cleared after reading the KRF register and before writing to the KRF register.
     * If the IRQ status is cleared and an edge is detected before KRF is read, then a second interrupt will be
     * generated with KRF equal to 0. If the IRQ status is cleared after writing to KRF, then an interrupt could be
     * missed. */
    R_BSP_IrqStatusClear(irq);

    /* Only clear the serviced channels in the KINT peripheral.
     * Note:
     * - Writing 0 to a KRF register bit clears the KRF bit. Writing 1 has no effect on a KRF register bit value.
     * - Clearing a subset of KRFn bits has the effect of generating an additional interrupt request (See section
     *   21.3.2 Operation when using the key interrupt flags in the RA6M3 manual R01UH0886EJ0100). */
    R_KINT->KRF = (uint8_t) ~status;

    /* Set data to identify callback to user. */
    keymatrix_callback_args_t cb_data =
    {
        .channel_mask = status,
        .p_context    = p_ctrl->p_cfg->p_context
    };

    /* Call the callback function. */
    p_ctrl->p_cfg->p_callback(&cb_data);

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}
