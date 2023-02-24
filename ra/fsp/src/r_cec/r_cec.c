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
#include "bsp_api.h"
#include "r_cec.h"
#include "r_cec_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CEC_OPEN                 (0x52434543U) /* "RCEC" in ascii */

/* CADR and Local Address Macros */
#define CEC_CADR_UNREGISTERED    (0U)
#define CEC_CADR_TO_LOCAL_ADDRESS(cadr)    (cadr != 0U ? p_instance_ctrl->local_address : CEC_ADDR_UNREGISTERED)
#define CEC_LOCAL_ADDR_TO_CADR(a)          ((uint16_t) (0x01 << p_instance_ctrl->local_address))

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * cec_prv_ns_callback_t)(cec_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile cec_prv_ns_callback_t)(cec_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * ISR prototypes
 **********************************************************************************************************************/

static void r_cec_call_callback(cec_instance_ctrl_t * p_ctrl, cec_callback_args_t * p_args);

void cec_data_isr(void);
void cec_error_isr(void);
void cec_message_isr(void);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* CEC function pointers   */
const cec_api_t g_cec_on_cec =
{
    .open        = R_CEC_Open,
    .mediaInit   = R_CEC_MediaInit,
    .close       = R_CEC_Close,
    .write       = R_CEC_Write,
    .statusGet   = R_CEC_StatusGet,
    .callbackSet = R_CEC_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup CEC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***************************************************************************************************************//**
 * Open and configure the CEC module for operation.
 *
 * Example:
 * @snippet r_cec_example.c R_CEC_Open
 *
 * @retval FSP_SUCCESS                      CEC Module opened successfully.
 * @retval FSP_ERR_ALREADY_OPEN             Driver already open.
 * @retval FSP_ERR_ASSERTION                An input argument is invalid.
 * @retval FSP_ERR_IRQ_BSP_DISABLED         Interrupts are not enabled.
 *****************************************************************************************************************/
fsp_err_t R_CEC_Open (cec_ctrl_t * const p_ctrl, cec_cfg_t const * const p_cfg)
{
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) p_ctrl;

#if CEC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN((IRQn_Type) 0 <= p_cfg->data_irq, FSP_ERR_IRQ_BSP_DISABLED);
    FSP_ERROR_RETURN((IRQn_Type) 0 <= p_cfg->msg_irq, FSP_ERR_IRQ_BSP_DISABLED);
    FSP_ERROR_RETURN((IRQn_Type) 0 <= p_cfg->error_irq, FSP_ERR_IRQ_BSP_DISABLED);
    FSP_ERROR_RETURN(CEC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif
    cec_extended_cfg_t * p_extend = p_cfg->p_extend;
    p_instance_ctrl->p_cfg = p_cfg;

    /* Set callback and context pointers, if configured */
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    R_BSP_MODULE_START(FSP_IP_CEC, 0);

    /* Initialize Local Address to unregistered */
    R_CEC->CADR = CEC_CADR_UNREGISTERED;

    /* Set bit-width registers.
     * These are only rewritable when the CEC module is stopped (CECCTL0.CECE == 0), which is ensured by parameter checking above.
     * Configured width for these settings can be calculated: (Register_Value + 1) * CEC_Clock_Cycle */
    R_CEC->STATL  = p_cfg->bit_timing_cfg->bit_width_tx_start_low;
    R_CEC->STATB  = p_cfg->bit_timing_cfg->bit_width_tx_start_high;
    R_CEC->LGC0L  = p_cfg->bit_timing_cfg->bit_width_tx_zero_low;
    R_CEC->LGC1L  = p_cfg->bit_timing_cfg->bit_width_tx_one_low;
    R_CEC->DATB   = p_cfg->bit_timing_cfg->bit_width_tx_bit_overall;
    R_CEC->STATLL = p_cfg->bit_timing_cfg->bit_width_rx_start_low_min;
    R_CEC->STATLH = p_cfg->bit_timing_cfg->bit_width_rx_start_low_max;
    R_CEC->STATBL = p_cfg->bit_timing_cfg->bit_width_rx_start_overall_min;
    R_CEC->STATBH = p_cfg->bit_timing_cfg->bit_width_rx_start_overall_max;
    R_CEC->LGC0LL = p_cfg->bit_timing_cfg->bit_width_rx_zero_low_min;
    R_CEC->LGC0LH = p_cfg->bit_timing_cfg->bit_width_rx_zero_low_max;
    R_CEC->LGC1LL = p_cfg->bit_timing_cfg->bit_width_rx_one_low_min;
    R_CEC->LGC1LH = p_cfg->bit_timing_cfg->bit_width_rx_one_low_max;
    R_CEC->DATBL  = p_cfg->bit_timing_cfg->bit_width_rx_bit_overall_min;
    R_CEC->DATBH  = p_cfg->bit_timing_cfg->bit_width_rx_bit_overall_max;

    /* CEC Data sampling time */
    R_CEC->NOMT = p_cfg->rx_data_sample_time;

    /* CEC Data Bit Reference Width Setting
     * This 1-data bit width is used when counting the number of bits for errors handling, signal-free time, and bus locking
     * detection. This register is only rewritable when the CEC module is stopped (CECCTL0.CECE == 0), which is ensured by parameter
     * checking above. */
    R_CEC->NOMP = p_cfg->rx_data_bit_reference_width;

    /* CEC Extension Mode Register
     * This register is only rewritable when the CEC module is stopped (CECCTL0.CECE == 0), which is ensured by parameter checking above. */
    R_CEC->CECEXMD = (uint8_t) ((p_extend->err_detect_lerplen) |
                                (p_extend->err_detect_rercven) |
                                (p_extend->intda_timing_select));

    /* CEC Control Register One
     * 37.2.5 CEC Control Register 1 (CECCTL1) of the RA6M5 User Manual. Rewrite SFT bits only after confirming
     * that the Signal-Free Time Rewrite Disable Report Flag (CECS.SFTST) is 0. */
    FSP_HARDWARE_REGISTER_WAIT(R_CEC->CECS_b.SFTST, 0x0);
    R_CEC->CECCTL1 = p_extend->ctl1;

    /* Ensure the module starts without pending errors */
    R_CEC->CECFC = CEC_CECFC_MASK_ALL;

    /* CEC Control Register Zero */
    p_instance_ctrl->cecctl0 = (uint8_t) ((p_extend->ctl0_clock_select) |
                                          (p_extend->ctl0_ackten) |
                                          (1U << R_CEC_CECCTL0_CECE_Pos));
    R_CEC->CECCTL0 = p_instance_ctrl->cecctl0;

    /* Enable Interrupts */
    cec_instance_ctrl_t * p_isr_context = p_instance_ctrl;
    R_BSP_IrqCfgEnable(p_cfg->data_irq, p_instance_ctrl->p_cfg->ipl, p_isr_context);
    R_BSP_IrqCfgEnable(p_cfg->msg_irq, p_instance_ctrl->p_cfg->ipl, p_isr_context);
    R_BSP_IrqCfgEnable(p_cfg->error_irq, p_instance_ctrl->p_cfg->ipl, p_isr_context);

    /* Mark the control block as open and status to uninitialized */
    p_instance_ctrl->state = CEC_STATE_UNINIT;
    p_instance_ctrl->open  = CEC_OPEN;

    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Allocate provided CEC Local Address and Initialize the CEC module for operation.
 *
 * @note After calling R_CEC_Open this function may return FSP_ERR_IN_USE for up to 45 milliseconds.
 *
 * Example:
 * @snippet r_cec_example.c R_CEC_MediaInit
 *
 * @retval FSP_SUCCESS                 CEC Module Initialized successfully.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid or callback has not been set.
 * @retval FSP_ERR_NOT_OPEN            Control block not open.
 * @retval FSP_ERR_IN_USE              HDMI CEC Bus is currently in use. Try again later.
 *****************************************************************************************************************/
fsp_err_t R_CEC_MediaInit (cec_ctrl_t * const p_ctrl, cec_addr_t local_address)
{
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) p_ctrl;

#if CEC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(CEC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(local_address <= CEC_ADDR_UNREGISTERED);
    FSP_ASSERT(NULL != p_instance_ctrl->p_callback);
#endif
    FSP_ERROR_RETURN(0U == R_CEC->CECS_b.BUSST, FSP_ERR_IN_USE);

    /* Set local address register to zero for now - the actual value is set by MediaInit */
    p_instance_ctrl->local_address = local_address;

    /* Disable reception and reset the CEC address to 'unregistered' */
    p_instance_ctrl->cecctl0 &= (uint8_t) ~R_CEC_CECCTL0_CECRXEN_Msk;
    R_CEC->CECCTL0            = p_instance_ctrl->cecctl0;
    R_CEC->CADR               = CEC_CADR_UNREGISTERED;

    /* Set EOM and load address into CTXD as both initiator and follower */
    p_instance_ctrl->state = CEC_STATE_UNINIT;
    R_CEC->CECCTL0         = p_instance_ctrl->cecctl0 | R_CEC_CECCTL0_EOM_Msk;
    R_CEC->CTXD            = (uint8_t) ((p_instance_ctrl->local_address) | (p_instance_ctrl->local_address << 4U));

    /* Start Transmission */
    R_CEC->CECCTL0 = p_instance_ctrl->cecctl0 | R_CEC_CECCTL0_EOM_Msk | R_CEC_CECCTL0_TXTRG_Msk;

    /* Message transmitted successfully. Use callback to determine address allocation success/failure */
    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Close the CEC module.
 *
 * @retval FSP_SUCCESS          CEC Module closed successfully.
 * @retval FSP_ERR_ASSERTION    An input argument is invalid.
 *****************************************************************************************************************/
fsp_err_t R_CEC_Close (cec_ctrl_t * const p_ctrl)
{
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) p_ctrl;

#if CEC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
#endif

    /* Mark the module as closed */
    p_instance_ctrl->open  = 0U;
    p_instance_ctrl->state = CEC_STATE_UNINIT;

    /* Disable CEC Interrupts */
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->data_irq);
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->msg_irq);
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->error_irq);

    /* Clear the CEC address and Disable Operation */
    R_CEC->CADR    = CEC_CADR_UNREGISTERED;
    R_CEC->CECCTL0 = (uint8_t) (p_instance_ctrl->cecctl0 & ~R_CEC_CECCTL0_CECE_Msk);

    /* Turn off the peripheral to save power */
    R_BSP_MODULE_STOP(FSP_IP_CEC, 0);

    return FSP_SUCCESS;
}

/***************************************************************************************************************//**
 * Write data to the CEC bus. Data transmission is asynchronous. Provided message buffer should not be modified
 * until transmission is complete.
 *
 * Data Transmission follows the pattern defined be the HDMI CEC Specification:
 *
 *   | Data         | Description                     | Size                           |
 *   |--------------|---------------------------------|--------------------------------|
 *   | Start Bit    | Managed by Hardware, per config | N/A                            |
 *   | Header Block | Source/Destination Identifier   | 1 Byte                         |
 *   | Data Block 1 | Opcode Value (Optional)         | 1 Byte                         |
 *   | Data Block 2 | Operands (Optional)             | Variable (0-14 Bytes Typical)  |
 *
 * Example:
 * @snippet r_cec_example.c R_CEC_Write
 *
 * @retval FSP_SUCCESS                      Operation succeeded.
 * @retval FSP_ERR_NOT_OPEN                 Control block not open.
 * @retval FSP_ERR_NOT_INITIALIZED          Module has not been successfully initialized.
 * @retval FSP_ERR_ASSERTION                An input argument is invalid.
 * @retval FSP_ERR_INVALID_SIZE             Invalid message size.
 * @retval FSP_ERR_IN_USE                   HDMI CEC Bus is currently in use. Try again later.
 *****************************************************************************************************************/
fsp_err_t R_CEC_Write (cec_ctrl_t * const p_ctrl, cec_message_t const * const p_message, uint32_t message_size)
{
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) p_ctrl;

#if CEC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_message);
    FSP_ERROR_RETURN(CEC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(CEC_STATE_UNINIT != p_instance_ctrl->state, FSP_ERR_NOT_INITIALIZED);
    FSP_ERROR_RETURN(CEC_STATE_READY == p_instance_ctrl->state, FSP_ERR_IN_USE);
    FSP_ERROR_RETURN(0 < message_size, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN(sizeof(cec_message_t) >= message_size, FSP_ERR_INVALID_SIZE);
#endif
    FSP_ERROR_RETURN(0U == R_CEC->CECS_b.BUSST, FSP_ERR_IN_USE);

    /* Set control block state to transmitting */
    p_instance_ctrl->state = CEC_STATE_TX_ACTIVE;

    /* Prepare internal state for transmission - will continue via ISR */
    p_instance_ctrl->p_tx_buf = p_message->raw_data + 1;
    p_instance_ctrl->tx_bytes = message_size - 1;

    /* Set EOM Bit if needed */
    R_CEC->CECCTL0 = (uint8_t) (p_instance_ctrl->cecctl0 | (p_instance_ctrl->tx_bytes ? 0 : R_CEC_CECCTL0_EOM_Msk));

    /* Load header block - always transmitted first */
    R_CEC->CTXD = (uint8_t) (p_instance_ctrl->local_address << 4U | p_message->destination);

    /* Start transmission */
    R_CEC->CECCTL0 = p_instance_ctrl->cecctl0 | R_CEC_CECCTL0_TXTRG_Msk;

    return FSP_SUCCESS;
};

/***************************************************************************************************************//**
 * Provides the state and status information according to the provided CEC control instance.
 * @retval  FSP_SUCCESS                  Operation succeeded.
 * @retval  FSP_ERR_NOT_OPEN             Control block not open.
 * @retval  FSP_ERR_ASSERTION            An input argument is invalid.
 *****************************************************************************************************************/
fsp_err_t R_CEC_StatusGet (cec_ctrl_t * const p_ctrl, cec_status_t * const p_status)
{
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) p_ctrl;

#if CEC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);

    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(CEC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_status->local_address = (cec_addr_t) CEC_CADR_TO_LOCAL_ADDRESS(R_CEC->CADR);
    p_status->state         = p_instance_ctrl->state;
    if (CEC_STATE_READY == p_instance_ctrl->state)
    {
        p_status->state = R_CEC->CECS_b.BUSST ? CEC_STATE_BUSY : p_instance_ctrl->state;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref cec_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            An input argument is invalid.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_CEC_CallbackSet (cec_ctrl_t * const          p_ctrl,
                             void (                    * p_callback)(cec_callback_args_t *),
                             void const * const          p_context,
                             cec_callback_args_t * const p_callback_memory)
{
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) p_ctrl;

#if CEC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(CEC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if CEC_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    cec_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(cec_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup CEC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to CEC instance control block
 * @param[in]     p_args     Pointer to arguments on stack
 **********************************************************************************************************************/
static void r_cec_call_callback (cec_instance_ctrl_t * p_ctrl, cec_callback_args_t * p_args)
{
    cec_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    cec_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = p_args;
    }
    else
    {
        /* Save previous arguments on the stack in case this is a nested interrupt. */
        args = *p_args_memory;

        /* Copy the current stack args to callback memory */
        *p_args_memory = *p_args;
    }

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args_memory);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        cec_prv_ns_callback_t p_callback = (cec_prv_ns_callback_t) (p_ctrl->p_callback);
        p_callback(p_args_memory);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args_memory);
#endif

    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Data ISR - Invoked after start bit of all tx data and after data for all rx data
 **********************************************************************************************************************/
void cec_data_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Clear interrupt */
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (CEC_STATE_UNINIT != p_instance_ctrl->state) /* Do nothing if not initialized */
    {
        uint8_t cecs_b = R_CEC->CECS;

        /* Tx Processing - Tx flag can deassert quickly, so we check module state also to catch certain possible error cases */
        if ((cecs_b & R_CEC_CECS_TXST_Msk) || (CEC_STATE_TX_ACTIVE == p_instance_ctrl->state))
        {
            if (p_instance_ctrl->tx_bytes > 0)
            {
                /* Indicate EOM if this is the last byte to be transmitted */
                if (--p_instance_ctrl->tx_bytes == 0)
                {
                    R_CEC->CECCTL0 = p_instance_ctrl->cecctl0 | (uint8_t) R_CEC_CECCTL0_EOM_Msk;
                }

                /* Load next data before current transmission ends */
                R_CEC->CTXD = *p_instance_ctrl->p_tx_buf++;
            }
        }
        /* Rx Processing */
        else
        {
            cec_callback_args_t cb_args;
            cb_args.event                = CEC_EVENT_RX_DATA;
            cb_args.p_context            = p_instance_ctrl->p_context;
            cb_args.addr_match           = cecs_b & R_CEC_CECS_ADRF_Msk;
            cb_args.data_byte            = R_CEC->CRXD;
            cb_args.status.local_address = (cec_addr_t) CEC_CADR_TO_LOCAL_ADDRESS(R_CEC->CADR);
            cb_args.errors               = CEC_ERROR_NONE;

            p_instance_ctrl->state = CEC_STATE_RX_ACTIVE;

            /* Rx data maintained and processed by application*/
            r_cec_call_callback(p_instance_ctrl, &cb_args);
        }
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Message Complete ISR - Invoked after EOM message has been sent or received
 **********************************************************************************************************************/
void cec_message_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Clear interrupt */
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    bool tx_actv = (R_CEC->CECS & R_CEC_CECS_TXST_Msk) || (p_instance_ctrl->state == CEC_STATE_TX_ACTIVE);
    bool rx_actv = p_instance_ctrl->state == CEC_STATE_RX_ACTIVE;

    /* Notify application that message processing is complete */
    cec_callback_args_t cb_args;
    cb_args.event        = tx_actv ? CEC_EVENT_TX_COMPLETE : CEC_EVENT_RX_COMPLETE;
    cb_args.p_context    = p_instance_ctrl->p_context;
    cb_args.addr_match   = false;
    cb_args.data_byte    = 0U;
    cb_args.status.state = p_instance_ctrl->state;
    cb_args.errors       = CEC_ERROR_NONE; /* Errors will be sent by error ISR */

    /* Assign local address if allocation successful */
    if ((CEC_STATE_UNINIT == p_instance_ctrl->state) &&
        ((CEC_ADDR_UNREGISTERED == p_instance_ctrl->local_address) || R_CEC->CECEXMON_b.ACKF))
    {
        /* 37.2.4 CEC Control Register 0 (CECCTL0) of the RA6M5 User Manual. Setting the CECRXEN bit to 1 enables
         * reception. Set this bit to 1 after determining the local address (setting the CADR register). */
        R_CEC->CADR               = CEC_LOCAL_ADDR_TO_CADR(p_instance_ctrl->local_address);
        p_instance_ctrl->cecctl0 |= (uint8_t) R_CEC_CECCTL0_CECRXEN_Msk;
        R_CEC->CECCTL0            = p_instance_ctrl->cecctl0;

        /* Clear ack error */
        R_CEC->CECFC |= R_CEC_CECFC_ACKCTRG_Msk;

        /* Mark module as ready and update callback args */
        p_instance_ctrl->state       = CEC_STATE_READY;
        cb_args.event                = CEC_EVENT_READY;
        cb_args.status.local_address = p_instance_ctrl->local_address;
        cb_args.status.state         = p_instance_ctrl->state;
    }

    if ((p_instance_ctrl->state != CEC_STATE_UNINIT))
    {
        cb_args.event = tx_actv ? CEC_EVENT_TX_COMPLETE : (rx_actv ? CEC_EVENT_RX_COMPLETE : CEC_EVENT_READY);
        r_cec_call_callback(p_instance_ctrl, &cb_args);

        /* Tx/Rx complete. Module is now idle */
        p_instance_ctrl->state = CEC_STATE_READY;
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Error ISR - Invoked after error detected.
 **********************************************************************************************************************/
void cec_error_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    /* Clear interrupt */
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
    cec_instance_ctrl_t * p_instance_ctrl = (cec_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Capture error and send to application via callback */
    cec_callback_args_t cb_args;
    cb_args.event                = CEC_EVENT_ERR;
    cb_args.p_context            = p_instance_ctrl->p_context;
    cb_args.status.local_address = (cec_addr_t) CEC_CADR_TO_LOCAL_ADDRESS(R_CEC->CADR);
    cb_args.status.state         = p_instance_ctrl->state;
    cb_args.errors               = (cec_error_t) R_CEC->CECES;

    /* Ignore ACKERR if address is not yet allocated (ackerr indicates address allocation success)*/
    if ((CEC_STATE_UNINIT != p_instance_ctrl->state) || (cb_args.errors & ~R_CEC_CECES_ACKERR_Msk))
    {
        r_cec_call_callback(p_instance_ctrl, &cb_args);

        /* Mark module as idle if tx and rx inactive and mediaInit has succeeded */
        if (CEC_STATE_UNINIT != p_instance_ctrl->state)
        {
            p_instance_ctrl->state = CEC_STATE_READY;
        }

        /* Clear errors after application processing */
        R_CEC->CECFC = CEC_CECFC_MASK_ALL;
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
