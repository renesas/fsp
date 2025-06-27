/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_ipc.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "RIPC" in ASCII.  Used to determine if the control block is open. */
#define IPC_OPEN                      (0x52495043U)

/* IPC0 is Core1 -> Core0, IPC1 is Core0 -> Core1 */
#if (BSP_CFG_CPU_CORE == 0)
 #define IPC_PRV_SEND_UNIT            IPC1
 #define IPC_PRV_RECEIVE_UNIT         IPC0
#else
 #define IPC_PRV_SEND_UNIT            IPC0
 #define IPC_PRV_RECEIVE_UNIT         IPC1
#endif

/* Mask for IPC event bits to pass into callback */
#define IPC_PRV_EVENT_MASK            (~(R_IPC_IPC_CH_STA_RDY_Msk | R_IPC_IPC_CH_STA_FULL_Msk))

#define IPC_PRV_VALID_CHANNEL_MASK    (3U) // Mask is per IPC unit

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * ipc_prv_ns_callback)(ipc_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile ipc_prv_ns_callback)(ipc_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const ipc_api_t g_ipc_on_ipc =
{
    .open          = R_IPC_Open,
    .messageSend   = R_IPC_MessageSend,
    .eventGenerate = R_IPC_EventGenerate,
    .callbackSet   = R_IPC_CallbackSet,
    .close         = R_IPC_Close,
};

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* Interrupt service routines */
void ipc_isr(void);

#if (IPC_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t r_ipc_common_parameter_checking(ipc_instance_ctrl_t const * const p_ctrl);

#endif

static void r_ipc_call_callback(ipc_instance_ctrl_t * p_ctrl, ipc_event_t event);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup IPC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures the IPC driver channel based on the input configuration.
 *
 * Implements @ref ipc_api_t::open.
 *
 *
 * @retval  FSP_SUCCESS                     Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION               Pointer to IPC control block or configuration structure is NULL.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT  The requested channel does not exist on this MCU.
 * @retval  FSP_ERR_ALREADY_OPEN            Control block has already been opened or channel is being used by another
 *                                          instance. Call close() then open() to reconfigure.
 *
 * @return                                  See @ref RENESAS_ERROR_CODES or functions called by this function for
 *                                          other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_IPC_Open (ipc_ctrl_t * const p_api_ctrl, ipc_cfg_t const * const p_cfg)
{
    ipc_instance_ctrl_t * p_ctrl = (ipc_instance_ctrl_t *) p_api_ctrl;

#if IPC_CFG_PARAM_CHECKING_ENABLE

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);

    /* Check control block isn't already open */
    FSP_ERROR_RETURN(p_ctrl->open != IPC_OPEN, FSP_ERR_ALREADY_OPEN);

    FSP_ERROR_RETURN(IPC_PRV_VALID_CHANNEL_MASK & (1U << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Callback should not be NULL when interrupt is configured */
    if (p_cfg->irq >= 0)
    {
        FSP_ERROR_RETURN(BSP_IRQ_DISABLED != p_cfg->ipl, FSP_ERR_INVALID_ARGUMENT);
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }
#endif

    /* Initialize control block */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Set instance IPC registers based on channel and current core */
    p_ctrl->p_send_reg = (R_IPC_IPC_CH_Type *) &(R_IPC->IPC_PRV_SEND_UNIT.CH[p_cfg->channel]);
    p_ctrl->p_recv_reg = (R_IPC_IPC_CH_Type *) &(R_IPC->IPC_PRV_RECEIVE_UNIT.CH[p_cfg->channel]);

    /* Enable IRQ if it is set */
    if (p_cfg->irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->irq, p_cfg->ipl, p_ctrl);
    }

    /* Mark the control block as open */
    p_ctrl->open = IPC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sends a message over the configured IPC channel.
 *
 * Implements @ref ipc_api_t::messageSend.
 *
 *
 * @retval  FSP_SUCCESS                  Message written to FIFO successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INSUFFICIENT_SPACE   IPC channel FIFO is full
 *
 * @return                               See @ref RENESAS_ERROR_CODES or functions called by this function for
 *                                       other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_IPC_MessageSend (ipc_ctrl_t * const p_api_ctrl, uint32_t message)
{
    ipc_instance_ctrl_t * p_ctrl = (ipc_instance_ctrl_t *) p_api_ctrl;

#if IPC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_ipc_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Return an error if the FIFO is full */
    FSP_ERROR_RETURN(0 == p_ctrl->p_send_reg->STA_b.FULL, FSP_ERR_OVERFLOW);

    /* Write message to FIFO */
    p_ctrl->p_send_reg->TXD = message;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Triggers an interrupt with the specified event bit set over the configured IPC channel.
 *
 * Implements @ref ipc_api_t::eventGenerate.
 *
 * @retval  FSP_SUCCESS                  Event request set successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 *
 * @return                               See @ref RENESAS_ERROR_CODES or functions called by this function for
 *                                       other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_IPC_EventGenerate (ipc_ctrl_t * const p_api_ctrl, ipc_generate_event_t event)
{
    ipc_instance_ctrl_t * p_ctrl = (ipc_instance_ctrl_t *) p_api_ctrl;

#if IPC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_ipc_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Write to IRQ Request Set Register to generate event */
    p_ctrl->p_send_reg->SET = event;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 *
 * Implements @ref ipc_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to IPC control block or callback is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 *
 * @return                               See @ref RENESAS_ERROR_CODES or functions called by this function for
 *                                       other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_IPC_CallbackSet (ipc_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(ipc_callback_args_t *),
                             void * const                p_context,
                             ipc_callback_args_t * const p_callback_memory)
{
    ipc_instance_ctrl_t * p_ctrl = (ipc_instance_ctrl_t *) p_api_ctrl;

#if IPC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_ipc_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for null parameters */
    FSP_ASSERT(NULL != p_callback);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if IPC_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    ipc_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(ipc_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the IPC driver.
 *
 * Implements @ref ipc_api_t::close.
 *
 * @retval  FSP_SUCCESS              Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION        Pointer to IPC control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN         The control block has not been opened.
 *
 * @return                           See @ref RENESAS_ERROR_CODES or functions called by this function for other possible
 *                                   return codes.
 **********************************************************************************************************************/
fsp_err_t R_IPC_Close (ipc_ctrl_t * const p_api_ctrl)
{
    ipc_instance_ctrl_t * p_ctrl = (ipc_instance_ctrl_t *) p_api_ctrl;

#if IPC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_ipc_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    if (p_ctrl->p_cfg->irq >= 0)
    {
        /* Disable interrupt if configured */
        R_BSP_IrqDisable(p_ctrl->p_cfg->irq);
    }

    /* Mark the channel not open so other APIs cannot use it. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IPC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (IPC_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Verifies the control structure is not NULL and the module is open. This reduces code size when parameter checking is
 * enabled.
 *
 * @param[in] p_ctrl                    Pointer to the control block for the channel
 *
 * @retval FSP_SUCCESS                  No error detected.
 * @retval FSP_ERR_ASSERTION            NULL input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 **********************************************************************************************************************/
static fsp_err_t r_ipc_common_parameter_checking (ipc_instance_ctrl_t const * const p_ctrl)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(IPC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to IPC instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_ipc_call_callback (ipc_instance_ctrl_t * p_ctrl, ipc_event_t event)
{
    ipc_callback_args_t args;

    /* Store callback arguments in memory provided by user if available. This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    ipc_callback_args_t * p_args = p_ctrl->p_callback_memory;
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

    p_args->channel   = p_ctrl->p_cfg->channel;
    p_args->event     = event;
    p_args->p_context = p_ctrl->p_context;

    if (IPC_EVENT_MESSAGE_RECEIVED == event)
    {
        /* Pull message from FIFO */
        p_args->message = p_ctrl->p_recv_reg->RXD;
    }
    else
    {
        p_args->message = 0;
    }

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
        ipc_prv_ns_callback p_callback = (ipc_prv_ns_callback) (p_ctrl->p_callback);
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
 * IPC general ISR.
 *
 * @retval    none
 **********************************************************************************************************************/
void ipc_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Clear pending IRQ to make sure it doesn't fire again after exiting */
    R_BSP_IrqStatusClear(irq);

    /* Recover ISR context saved in open. */
    ipc_instance_ctrl_t * p_ctrl = (ipc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    uint32_t ipc_status_temp = p_ctrl->p_recv_reg->STA;

    /* Handle Received Messages */
    if (ipc_status_temp & R_IPC_IPC_CH_STA_RDY_Msk)
    {
        /* Ready bit is set which means FIFO isn't empty read message and call callback */
        r_ipc_call_callback(p_ctrl, IPC_EVENT_MESSAGE_RECEIVED);
    }

    /* Check for other errors and generated events */
    ipc_event_t event = (ipc_event_t) (ipc_status_temp & IPC_PRV_EVENT_MASK);

    /* Handle events */
    if (event)
    {
        /* Call callback */
        r_ipc_call_callback(p_ctrl, event);

        /* Clear out set events */
        p_ctrl->p_recv_reg->CLR = (uint32_t) event;
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
