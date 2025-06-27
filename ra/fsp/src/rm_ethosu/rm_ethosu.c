/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ethosu.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_ETHOS_OPEN    (0x524D4554UL) // "RMET"

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function declarations.
 **********************************************************************************************************************/
static void rm_ethosu_call_callback(rm_ethosu_instance_ctrl_t * p_ctrl);

void rm_ethosu_isr(void);

/*******************************************************************************************************************//**
 * @addtogroup RM_ETHOSU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_ethosu_api_t const g_rm_ethosu_on_npu =
{
    .open        = RM_ETHOSU_Open,
    .close       = RM_ETHOSU_Close,
    .callbackSet = RM_ETHOSU_CallbackSet,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enable Ethos-U NPU and initialize driver. Implements @ref rm_ethosu_api_t::open.
 *
 * This function performs the following tasks:
 *   - Performs parameter checking and processes error conditions.
 *   - Enables NPU module
 *   - Initializes Ethos-U NPU driver.
 *   - Provides the handle for use with other API functions.
 *
 * @param      p_api_ctrl                      Pointer to the control structure.
 * @param      p_cfg                           Pointer to a configuration structure.
 *
 * @retval     FSP_SUCCESS                     NPU initialized successfully.
 * @retval     FSP_ERR_ASSERTION               An input parameter is invalid or NULL.
 * @retval     FSP_ERR_ALREADY_OPEN            The instance has already been opened.
 * @retval     FSP_ERR_INVALID_ARGUMENT        Failed to initialize ethosu driver
 **********************************************************************************************************************/
fsp_err_t RM_ETHOSU_Open (rm_ethosu_ctrl_t * p_api_ctrl, rm_ethosu_cfg_t const * const p_cfg)
{
    rm_ethosu_instance_ctrl_t * p_ctrl = (rm_ethosu_instance_ctrl_t *) p_api_ctrl;

#if RM_ETHOSU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(p_cfg->irq >= 0);
    FSP_ERROR_RETURN(RM_ETHOS_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    R_BSP_MODULE_START(FSP_IP_NPU, 0);

    if (0 != ethosu_init(p_ctrl->p_dev, (void *) R_NPU_BASE, NULL, 0, p_cfg->secure_enable, p_cfg->privilege_enable))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    R_BSP_IrqCfgEnable(p_cfg->irq, p_cfg->ipl, p_ctrl);

    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    p_ctrl->open = RM_ETHOS_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements rm_ethosu_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t RM_ETHOSU_CallbackSet (rm_ethosu_ctrl_t * const          p_api_ctrl,
                                 void (                          * p_callback)(rm_ethosu_callback_args_t *),
                                 void * const                      p_context,
                                 rm_ethosu_callback_args_t * const p_callback_memory)
{
    rm_ethosu_instance_ctrl_t * p_ctrl = (rm_ethosu_instance_ctrl_t *) p_api_ctrl;

#if (RM_ETHOSU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ETHOS_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if RM_ETHOSU_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    uart_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                       CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(uart_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif

    /* Store callback and context */
    p_ctrl->p_callback        = p_callback;
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable NPU and set the instance as not open. Implements @ref rm_ethosu_api_t::close.
 *
 * @param      p_api_ctrl         Pointer to an opened instance.
 *
 * @retval     FSP_SUCCESS        Channel successfully closed.
 * @retval     FSP_ERR_ASSERTION  The parameter p_api_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN   The channel has not been opened. Open the channel first.
 **********************************************************************************************************************/
fsp_err_t RM_ETHOSU_Close (rm_ethosu_ctrl_t * p_api_ctrl)
{
    rm_ethosu_instance_ctrl_t * p_ctrl = (rm_ethosu_instance_ctrl_t *) p_api_ctrl;
#if RM_ETHOSU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ETHOS_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    R_BSP_IrqDisable(p_ctrl->p_cfg->irq);

    ethosu_deinit((struct ethosu_driver *) p_ctrl->p_dev);

    R_BSP_MODULE_STOP(FSP_IP_NPU, 0);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_ETHOSU)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to Ethos-U instance control block
 **********************************************************************************************************************/
static void rm_ethosu_call_callback (rm_ethosu_instance_ctrl_t * p_ctrl)
{
    rm_ethosu_callback_args_t args;

    /* Store callback arguments in memory provided by user if available. This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    rm_ethosu_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->p_context = p_ctrl->p_context;

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
        ethosu_prv_ns_callback p_callback = (ethosu_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif
    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * ISR for NPU IRQ
 *
 **********************************************************************************************************************/
void rm_ethosu_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    rm_ethosu_instance_ctrl_t * p_ctrl = (rm_ethosu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    ethosu_irq_handler(p_ctrl->p_dev);

    if (p_ctrl->p_callback)
    {
        rm_ethosu_call_callback(p_ctrl);
    }

    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
