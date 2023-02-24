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

/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include "r_iic_b_slave.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* "I2CS" in ASCII, used to determine if channel is open. */
#define IIC_B_SLAVE_OPEN                       (0x49324353ULL)
#define IIC_B_SLAVE_PRV_NTDTBP0_SIZE           (0xFFU)
#define IIC_B_SLAVE_CODE_10BIT                 (0xF0U)
#define IIC_B_SLAVE_PRV_BIE_INIT_MASK          (R_I3C0_BIE_NACKDIE_Msk | R_I3C0_BIE_ALIE_Msk | R_I3C0_BIE_TODIE_Msk)
#define IIC_B_SLAVE_PRV_BSTE_INIT_MASK         (R_I3C0_BSTE_NACKDE_Msk | R_I3C0_BSTE_ALE_Msk | R_I3C0_BSTE_TODE_Msk | \
                                                R_I3C0_BSTE_TENDE_Msk)
#define IIC_B_SLAVE_PRV_NTIE_INIT_MASK         (R_I3C0_NTIE_TDBEIE0_Msk | R_I3C0_NTIE_RDBFIE0_Msk)
#define IIC_B_SLAVE_PRV_NTSTE_INIT_MASK        (R_I3C0_NTSTE_TDBEE0_Msk | R_I3C0_NTSTE_RDBFE0_Msk)
#define IIC_B_SLAVE_PRV_BST_ERR_STATUS_MASK    (R_I3C0_BST_STCNDDF_Msk | R_I3C0_BST_SPCNDDF_Msk | \
                                                R_I3C0_BST_NACKDF_Msk |                           \
                                                R_I3C0_BST_ALF_Msk | R_I3C0_BST_TODF_Msk)

/* Worst case ratio of ICLK/PCLKB (RA2E2) or ICLK/PCLKA (RA6T2) = 64 approximately.
 * 3 PCLKB cycles is the number of cycles to wait for IICn.
 * Refer "Table 3.2 Access cycles for non-GPT modules (1 of 2)" of the RA2E2 manual R01UH0919EJ0050)
 */
#define IIC_B_SLAVE_PERIPHERAL_REG_MAX_WAIT    (0x40U * 0x03U)

#define IIC_B_SLAVE_HARDWARE_REGISTER_WAIT(reg, required_value, timeout) \
    while ((timeout))                                                    \
    {                                                                    \
        if ((required_value) == (reg))                                   \
        {                                                                \
            break;                                                       \
        }                                                                \
        (timeout)--;                                                     \
    }

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * iic_b_slave_prv_ns_callback)(i2c_slave_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile iic_b_slave_prv_ns_callback)(i2c_slave_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 * Private function prototypes
 *********************************************************************************************************************/

/* Internal helper functions */
static void iic_b_slave_notify(iic_b_slave_instance_ctrl_t * const p_ctrl, i2c_slave_event_t const slave_event);
static void iic_b_slave_callback_request(iic_b_slave_instance_ctrl_t * const p_ctrl,
                                         i2c_slave_event_t                   slave_event);
static void      iic_b_slave_initiate_transaction(iic_b_slave_instance_ctrl_t * p_ctrl, i2c_slave_event_t slave_event);
static fsp_err_t iic_b_slave_read_write(i2c_slave_ctrl_t * const   p_api_ctrl,
                                        uint8_t * const            p_buffer,
                                        uint32_t const             bytes,
                                        iic_b_slave_transfer_dir_t direction);
static void iic_b_slave_call_callback(iic_b_slave_instance_ctrl_t * p_ctrl,
                                      i2c_slave_event_t             event,
                                      uint32_t                      transaction_count);

/* Functions that manipulate hardware */
static void iic_b_open_hw_slave(iic_b_slave_instance_ctrl_t * const p_ctrl);

/* Interrupt handlers */
static void iic_b_rxi_slave(iic_b_slave_instance_ctrl_t * p_ctrl);
static void iic_b_txi_slave(iic_b_slave_instance_ctrl_t * p_ctrl);
static void iic_b_tei_slave(iic_b_slave_instance_ctrl_t * p_ctrl);
static void iic_b_err_slave(iic_b_slave_instance_ctrl_t * p_ctrl);

/**********************************************************************************************************************
 * Private global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Global variables
 *********************************************************************************************************************/

/* IIC Implementation of I2C device slave interface */
i2c_slave_api_t const g_i2c_slave_on_iic_b =
{
    .open        = R_IIC_B_SLAVE_Open,
    .read        = R_IIC_B_SLAVE_Read,
    .write       = R_IIC_B_SLAVE_Write,
    .close       = R_IIC_B_SLAVE_Close,
    .callbackSet = R_IIC_B_SLAVE_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup IIC_B_SLAVE
 * @{
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Functions
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * Opens the I2C slave device.
 *
 * @retval  FSP_SUCCESS                       I2C slave device opened successfully.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT    Channel is not available on this MCU.
 * @retval  FSP_ERR_INVALID_ARGUMENT          Error interrupt priority is lower than
 *                                            Transmit, Receive and Transmit End interrupt priority
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 *                                            4. Set the rate to fast mode plus on a channel which does not support it.
 *                                            5. Invalid IRQ number assigned
 *********************************************************************************************************************/
fsp_err_t R_IIC_B_SLAVE_Open (i2c_slave_ctrl_t * const p_api_ctrl, i2c_slave_cfg_t const * const p_cfg)
{
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) p_api_ctrl;

#if IIC_B_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT(p_cfg->rxi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->txi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->eri_irq >= (IRQn_Type) 0);

    FSP_ERROR_RETURN(BSP_FEATURE_IIC_B_VALID_CHANNEL_MASK & (1 << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    FSP_ERROR_RETURN(IIC_B_SLAVE_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(p_cfg->eri_ipl <= p_cfg->ipl, FSP_ERR_INVALID_ARGUMENT);

    /* If rate is configured as Fast mode plus, check whether the channel supports it */
    if (I2C_SLAVE_RATE_FASTPLUS == p_cfg->rate)
    {
        FSP_ASSERT((BSP_FEATURE_IIC_B_FAST_MODE_PLUS & (1U << p_cfg->channel)));
    }
#endif

#if (BSP_FEATURE_IIC_B_VALID_CHANNEL_MASK > 1U)
    p_ctrl->p_reg =
        (R_I3C0_Type *) ((uint32_t) R_I3C0 + (p_cfg->channel * ((uint32_t) R_I3C1 - (uint32_t) R_I3C0)));
#else
    p_ctrl->p_reg = R_I3C0;
#endif

    /* Record the configuration on the device for use later */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

#if (1 == BSP_FEATURE_BSP_HAS_I3C_CLOCK)
    R_BSP_MODULE_START(FSP_IP_I3C, p_cfg->channel);
#else
    R_BSP_MODULE_START(FSP_IP_IIC, p_cfg->channel);
#endif

    /* Open the hardware in slave mode. Performs IIC initialization as described in hardware manual (see Section 27.3.2.1
     * 'Initial Settings' of the RA6T2 manual R01UH0951EJ0050). */
    iic_b_open_hw_slave(p_ctrl);

    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->eri_irq, p_ctrl->p_cfg->eri_ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->txi_irq, p_ctrl->p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->tei_irq, p_ctrl->p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->rxi_irq, p_ctrl->p_cfg->ipl, p_ctrl);

    /* Finally, we can consider the device opened */
    p_ctrl->p_buff                = NULL;
    p_ctrl->total                 = 0U;
    p_ctrl->remain                = 0U;
    p_ctrl->loaded                = 0U;
    p_ctrl->transaction_completed = false;
    p_ctrl->open              = IIC_B_SLAVE_OPEN;
    p_ctrl->direction         = IIC_B_SLAVE_TRANSFER_DIR_NOT_ESTABLISHED;
    p_ctrl->do_dummy_read     = false;
    p_ctrl->notify_request    = false;
    p_ctrl->transaction_count = 0U;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Performs a read from the I2C Master device.
 *
 * This function will fail if there is already an in-progress I2C transfer on the associated channel. Otherwise, the
 * I2C slave read operation will begin. The caller will be notified when the operation has finished by an
 * I2C_SLAVE_EVENT_RX_COMPLETE in the callback.
 * In case the master continues to write more data, an I2C_SLAVE_EVENT_RX_MORE_REQUEST will be issued via callback.
 * In case of errors, an I2C_SLAVE_EVENT_ABORTED will be issued via callback.
 *
 * @retval  FSP_SUCCESS        Function executed without issue
 * @retval  FSP_ERR_ASSERTION  p_api_ctrl, bytes or p_dest is NULL.
 * @retval  FSP_ERR_IN_USE     Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN   Device is not open.
 *********************************************************************************************************************/
fsp_err_t R_IIC_B_SLAVE_Read (i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;

    err = iic_b_slave_read_write(p_api_ctrl, p_dest, bytes, IIC_B_SLAVE_TRANSFER_DIR_MASTER_WRITE_SLAVE_READ);

    return err;
}

/******************************************************************************************************************//**
 * Performs a write to the I2C Master device.
 *
 * This function will fail if there is already an in-progress I2C transfer on the associated channel. Otherwise, the
 * I2C slave write operation will begin. The caller will be notified when the operation has finished by an
 * I2C_SLAVE_EVENT_TX_COMPLETE in the callback.
 * In case the master continues to read more data, an I2C_SLAVE_EVENT_TX_MORE_REQUEST will be issued via callback.
 * In case of errors, an I2C_SLAVE_EVENT_ABORTED will be issued via callback.
 *
 * @retval  FSP_SUCCESS        Function executed without issue.
 * @retval  FSP_ERR_ASSERTION  p_api_ctrl or p_src is NULL.
 * @retval  FSP_ERR_IN_USE     Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN   Device is not open.
 *********************************************************************************************************************/
fsp_err_t R_IIC_B_SLAVE_Write (i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;

    err = iic_b_slave_read_write(p_api_ctrl, p_src, bytes, IIC_B_SLAVE_TRANSFER_DIR_MASTER_READ_SLAVE_WRITE);

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements i2c_slave_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_IIC_B_SLAVE_CallbackSet (i2c_slave_ctrl_t * const          p_api_ctrl,
                                     void (                          * p_callback)(i2c_slave_callback_args_t *),
                                     void const * const                p_context,
                                     i2c_slave_callback_args_t * const p_callback_memory)
{
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) p_api_ctrl;

#if (IIC_B_SLAVE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(IIC_B_SLAVE_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if IIC_B_SLAVE_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    i2c_slave_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                            CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(i2c_slave_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Closes the I2C device.
 *
 * @retval  FSP_SUCCESS         Device closed successfully.
 * @retval  FSP_ERR_NOT_OPEN    Device not opened.
 * @retval  FSP_ERR_ASSERTION   p_api_ctrl is NULL.
 *********************************************************************************************************************/
fsp_err_t R_IIC_B_SLAVE_Close (i2c_slave_ctrl_t * const p_api_ctrl)
{
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) p_api_ctrl;

#if IIC_B_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);

    /* Check if the device is even open, return an error if not */
    FSP_ERROR_RETURN(IIC_B_SLAVE_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* The device is now considered closed */
    p_ctrl->open = 0U;

    /* Clear all interrupt bits */
    p_ctrl->p_reg->BIE  = 0x00;
    p_ctrl->p_reg->NTIE = 0x00;

    /* Disable all interrupts in NVIC */
    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    /* Set RSTCTL.RI2CRST to 1: Reset all registers and internal state; RSTCTL.INTLRST is already 0. */
    p_ctrl->p_reg->RSTCTL = (uint32_t) (R_I3C0_RSTCTL_RI3CRST_Msk);

    /* Waiting for reset completion RSTCTL.RI2CRST = 0;  RSTCTL.INTLRST is already 0. */
    FSP_HARDWARE_REGISTER_WAIT(0U, p_ctrl->p_reg->RSTCTL);

#if (1 == BSP_FEATURE_BSP_HAS_I3C_CLOCK)
    R_BSP_MODULE_STOP(FSP_IP_I3C, p_ctrl->p_cfg->channel);
#else
    R_BSP_MODULE_STOP(FSP_IP_IIC, p_ctrl->p_cfg->channel);
#endif

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @} (end addtogroup IIC_B_SLAVE)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private Functions
 *********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Helper function for handling I2C Slave Read or Write.
 *
 * @param      p_api_ctrl      Pointer to the control structure.
 * @param      p_buffer        Pointer to the buffer to store read/write data.
 * @param[in]  bytes           Number of bytes to be read/written.
 * @param[in]  direction       Slave Read or Slave Write
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_buffer is NULL.
 *
 * @retval  FSP_ERR_IN_USE        Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized. Call R_IIC_B_SLAVE_Open to initialize the control block.
 **********************************************************************************************************************/
static fsp_err_t iic_b_slave_read_write (i2c_slave_ctrl_t * const   p_api_ctrl,
                                         uint8_t * const            p_buffer,
                                         uint32_t const             bytes,
                                         iic_b_slave_transfer_dir_t direction)
{
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) p_api_ctrl;

#if IIC_B_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_buffer != NULL);

    /* Check if the device is even open, return an error if not */
    FSP_ERROR_RETURN(IIC_B_SLAVE_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN(IIC_B_SLAVE_TRANSFER_DIR_NOT_ESTABLISHED == p_ctrl->direction, FSP_ERR_IN_USE);

    FSP_ASSERT(((iic_b_slave_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);
#endif

    /* Record the new information about this transfer */
    p_ctrl->p_buff    = p_buffer;
    p_ctrl->total     = bytes;
    p_ctrl->remain    = bytes;
    p_ctrl->direction = direction;

    /* Initialize fields used during transfer */
    p_ctrl->loaded = 0U;

    /* Set the response as ACK */
    p_ctrl->p_reg->ACKCTL = R_I3C0_ACKCTL_ACKTWP_Msk;

    /* Timeouts are enabled by the driver code at the end of an IIC Slave callback.
     * Do not enable them here to prevent time restricting the application code.
     */
    p_ctrl->transaction_completed = false;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl            Pointer to the control structure.
 * @param[in]       slave_event       The slave event code to pass to the callback.
 *********************************************************************************************************************/
static void iic_b_slave_notify (iic_b_slave_instance_ctrl_t * const p_ctrl, i2c_slave_event_t const slave_event)
{
    /* Clear all interrupt bits,
     * Only enable TXI and RXI interrupts for the next transaction.
     * Disable start and stop detection.
     * Disable timeout function.
     */
    p_ctrl->p_reg->BSTE = IIC_B_SLAVE_PRV_BSTE_INIT_MASK & ~R_I3C0_BSTE_TODE_Msk;
    p_ctrl->p_reg->NTIE = IIC_B_SLAVE_PRV_NTIE_INIT_MASK;

    /* Reset the status flags */
    p_ctrl->notify_request = false;
    p_ctrl->do_dummy_read  = false;

    /* Disable timeout interrupt */
    p_ctrl->p_reg->BIE_b.TODIE = 0U;

    /* Check if the transaction ended with a stop (or restart) */
    if (p_ctrl->transaction_completed)
    {
        /* Clear all status flags */
        uint32_t bst_status = p_ctrl->p_reg->BST;
        bst_status        &= ~bst_status;
        p_ctrl->p_reg->BST = bst_status;
    }
    /*
     * Since the transaction resulted in an error or is not completed at the master (this is a bus hang situation)
     * the slave must do an internal reset to release the bus.
     * Restore initial settings.
     */
    else
    {
        iic_b_open_hw_slave(p_ctrl);
    }

    /* Save transaction count */
    uint32_t transaction_count = p_ctrl->transaction_count;

    /* Reset the transaction count here */
    p_ctrl->transaction_count = 0U;

    p_ctrl->direction = IIC_B_SLAVE_TRANSFER_DIR_NOT_ESTABLISHED;

    /* Invoke the callback */
    iic_b_slave_call_callback(p_ctrl, slave_event, transaction_count);
}

/*******************************************************************************************************************//**
 * Deliver callback. Timeouts are disabled causing clock to stretch.
 *
 * @param      p_ctrl          Pointer to the control structure.
 * @param[in]  slave_event     Slave event to be reported via callback.
 **********************************************************************************************************************/
static void iic_b_slave_callback_request (iic_b_slave_instance_ctrl_t * const p_ctrl, i2c_slave_event_t slave_event)
{
    p_ctrl->direction = IIC_B_SLAVE_TRANSFER_DIR_NOT_ESTABLISHED;

    /* Disable timeout function */
    p_ctrl->p_reg->BSTE_b.TODE = 0U;
    p_ctrl->p_reg->BIE_b.TODIE = 0U;

    /* Invoke the callback to notify the read request.
     * The application must call MasterWriteSlaveRead API in the callback.*/
    iic_b_slave_call_callback(p_ctrl, slave_event, p_ctrl->transaction_count);

    /* Allow timeouts to be generated on the low value of SCL using long count mode */
    p_ctrl->p_reg->TMOCTL = R_I3C0_TMOCTL_TOLCTL_Msk;

    /* Enable timeout function */
    p_ctrl->p_reg->BSTE_b.TODE = 1U;
    p_ctrl->p_reg->BIE_b.TODIE = 1U;
}

/******************************************************************************************************************//**
 * Performs the hardware initialization sequence when operating as a slave (see Section 27.3.2.1
 * 'Initial Settings' of the RA6T2 manual R01UH0951EJ0050).
 *
 * @param[in]       p_ctrl     Pointer to the control structure.
 *********************************************************************************************************************/
static void iic_b_open_hw_slave (iic_b_slave_instance_ctrl_t * const p_ctrl)
{
#if (1 == BSP_FEATURE_BSP_HAS_I3C_CLOCK || 1 == BSP_FEATURE_BSP_HAS_IIC_CLOCK)

    /* Enable I3CCLK. (Not a part of init sequence in the HW manual, but RA8 must enable it to reset the module ) */
    p_ctrl->p_reg->CECTL = (uint32_t) R_I3C0_CECTL_CLKE_Msk;
#endif

    /* Clear BCTL.BUSE to 0: SCL, SDA pins not driven */
    p_ctrl->p_reg->BCTL_b.BUSE = 0;

    /* Set RSTCTL.RI2CRST to 1: Reset all registers and internal state; RSTCTL.INTLRST is already 0.*/
    p_ctrl->p_reg->RSTCTL = R_I3C0_RSTCTL_RI3CRST_Msk;

    /* Waiting for reset completion RSTCTL.RI2CRST = 0;  RSTCTL.INTLRST is already 0. */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->RSTCTL_b.RI3CRST, 0U);

    /* Set Slave address in SDATBAS0 and set SVCTL */
    p_ctrl->p_reg->SDATBAS0 = (uint32_t) (p_ctrl->p_cfg->slave) |
                              (((uint32_t) ((p_ctrl->p_cfg->addr_mode) ==
                                            I2C_SLAVE_ADDR_MODE_10BIT)) << R_I3C0_SDATBAS0_SDADLS_Pos);

    /* Enable the slave address and general call based on user config */
    p_ctrl->p_reg->SVCTL = (uint32_t) (R_I3C0_SVCTL_SVAEn_Msk |
                                       ((uint32_t) p_ctrl->p_cfg->general_call_enable << R_I3C0_SVCTL_GCAE_Pos));

    /* Allow timeouts to be generated on the low value of SCL using long count mode */
    p_ctrl->p_reg->TMOCTL = R_I3C0_TMOCTL_TOLCTL_Msk;

    /* Setup digital noise filter circuit. */
    uint8_t digital_filter_stages =
        (((iic_b_slave_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clock_settings.digital_filter_stages);
    p_ctrl->p_reg->INCTL =
        ((uint32_t) (digital_filter_stages >
                     0U ? ((digital_filter_stages - 1U) & R_I3C0_INCTL_DNFS_Msk) : 0U) << R_I3C0_INCTL_DNFS_Pos) |
        R_I3C0_INCTL_DNFE_Msk;

    /* 1. Enable FM+ slope circuit if fast mode plus is enabled.
     * 2. Set Master Arbitration-Lost Detection Enable
     * 3. Set NACK Transmission Arbitration-Lost Detection Enable
     * 4. Set Slave Arbitration-Lost Detection Enable
     * 5. Use the SCL synchronous circuit.
     */
    p_ctrl->p_reg->BFCTL = (((uint32_t) ((I2C_SLAVE_RATE_FASTPLUS == p_ctrl->p_cfg->rate) << R_I3C0_BFCTL_FMPE_Pos)) |
                            R_I3C0_BFCTL_MALE_Msk | R_I3C0_BFCTL_NALE_Msk | R_I3C0_BFCTL_SALE_Msk |
                            R_I3C0_BFCTL_SCSYNE_Msk);

    /* Set the clock and slope circuits to match the data setup time specified by the I2C standard */
    /* This is set in the configuration structure by the tooling. */

    /* Clock settings - Set REFCKCTL, STDBR and EXTBR registers: Set transfer bit rate.
     * The values for these are set in the configuration structure by the tooling.
     */
    p_ctrl->p_reg->REFCKCTL =
        (uint32_t) (((iic_b_slave_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clock_settings.cks_value &
                    R_I3C0_REFCKCTL_IREFCKS_Msk);

    /* SBRHO need not be updated. */
    p_ctrl->p_reg->STDBR =
        (uint32_t) (((iic_b_slave_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->clock_settings.brl_value <<
                    R_I3C0_STDBR_SBRLO_Pos);

    /* 1. ACKCTL: ACKBT should be set to 0 after reset to send out an ACK upon slave address match. */

    /* Set RWE bit based on user config.
     * Refer Section 27.2.16 SCSTRCTL : SCL Stretch Control Register :
     * 'RWE bit (RWE)' and 'ACKTWE bit (RDBFF0 Flag Set Timing Select)'
     * of the RA6T2 manual R01UH0951EJ0050.
     * Since ACKTWE = 0:
     * - SCLn line will *not* be held low at the falling edge of the 8th clock cycle.
     * - RDRF flag will be set at the rising edge of the 9th clock cycle. (Cause of iic_b_rxi_slave)
     * This means that iic_b_rxi_slave will be invoked during the 9th clock cycle (High) if there is no preemption.
     * Set the RWE = 1 so that the SCLn line is held low from the falling edge of the 9th clock cycle.
     * This is done to support clock stretching during the 'iic_b_slave_initiate_transaction'/user event callback (more often)
     * and if iic_b_rxi_slave can get preempted.
     *
     * Note 1: If the preemption happens after the Read API is called in the user event callback,
     *         RWE = 1 will be able to handle that scenario,
     *         however if the preemption happens before, the slave will timeout if the Read API
     *         is not called within 'Long Timeout Mode' duration.
     *
     * Note 2: When RWE = 1, this driver no longer supports data reception utilizing the double buffer HW setup.
     *
     * Note 3: RWE bit is dont-care during transmission.
     */
    p_ctrl->p_reg->SCSTRCTL = (uint32_t) (p_ctrl->p_cfg->clock_stretching_enable << R_I3C0_SCSTRCTL_RWE_Pos);

    /* Enable status for Timeout Detection, Arbitration Loss, NACK Detection, Transmit End detection.
     * Disable status for Wake-up Condition Detection (Feature not supported by driver),
     * STOP and START condition Detection.
     */
    p_ctrl->p_reg->BSTE = IIC_B_SLAVE_PRV_BSTE_INIT_MASK;

    /* Enable status for Transmit Data Buffer Empty and Receive Data Buffer Full */
    p_ctrl->p_reg->NTSTE = IIC_B_SLAVE_PRV_NTSTE_INIT_MASK;

    /* Enable Interrupts: Transmit Data Buffer Empty and Receive Data Buffer Full */
    p_ctrl->p_reg->NTIE = IIC_B_SLAVE_PRV_NTIE_INIT_MASK;

    /* Set BCTL.BUSE to 1: SCL, SDA pins in active state */
    p_ctrl->p_reg->BCTL = (uint32_t) R_I3C0_BCTL_BUSE_Msk;
}

/*******************************************************************************************************************//**
 * Setup the Slave Read/Write transaction by issuing RX Request or TX request to the application via callback.
 *
 * @param      p_ctrl          Pointer to the control structure.
 * @param[in]  slave_event     Slave event to be reported via callback.
 **********************************************************************************************************************/
static void iic_b_slave_initiate_transaction (iic_b_slave_instance_ctrl_t * p_ctrl, i2c_slave_event_t slave_event)
{
    /* Set the status flag to ensure this conditional clause execution only once */
    p_ctrl->notify_request = true;

    /* Enable Interrupts: Timeout Detection, Arbitration Loss, NACK Detection.
     * Disable Interrupt: Transmit End, Start, Stop
     */
    p_ctrl->p_reg->BIE = IIC_B_SLAVE_PRV_BIE_INIT_MASK;

    /* Enable Interrupts: Transmit Data Buffer Empty and Receive Data Buffer Full */
    p_ctrl->p_reg->NTIE = IIC_B_SLAVE_PRV_NTIE_INIT_MASK;

    /* Invoke callback for the user to call a valid API. */
    iic_b_slave_callback_request(p_ctrl, slave_event);

    /* Check if correct API is called here  Check direction (API called) against slave event requested (ISR invoked) */
    if (!(((IIC_B_SLAVE_TRANSFER_DIR_MASTER_WRITE_SLAVE_READ ==
            p_ctrl->direction) &&
           ((I2C_SLAVE_EVENT_RX_REQUEST == slave_event) || (I2C_SLAVE_EVENT_GENERAL_CALL == slave_event))) ||
          ((IIC_B_SLAVE_TRANSFER_DIR_MASTER_READ_SLAVE_WRITE ==
            p_ctrl->direction) && (I2C_SLAVE_EVENT_TX_REQUEST == slave_event))))
    {
        /* In case MasterWriteSlaveRead API is NOT called to service Master write operation a NACK is
         * issued from the RXI ISR (which is fired once) and the bus is released.
         *
         * In case MasterWriteSlaveRead API is NOT called to service Master General Call operation a NACK is
         * issued from the RXI ISR (which is fired once) and the bus is released.
         *
         * In case MasterReadSlaveWrite API is NOT called to service Master read operation the TXI will fire once,
         * no data will be written to ICDRT and the master will read oxFF for every byte it tries to read.
         *
         * For both the cases above the slave callback is invoked with I2C_SLAVE_EVENT_ABORTED
         * event to notify the user application.
         *
         */
    }
    else
    {
        /* Enable the Start condition detection to trigger ERI ISR */

        /* Since address match is detected, enable STOP and RESTART detection for Master Read Slave Write.
         * This must be done conditionally only for Master Read Slave Write to prevent clearing the start bit
         * in case a restart occurred (and got captured) while we were in the user callback.
         * This capturing is made possible in the 'iic_b_rxi_slave' after the dummy read.
         * In case of Master Write Slave Read for 10-bit, this is done here as the address issues a
         * restart which we don't want to detect.
         */
        if ((IIC_B_SLAVE_TRANSFER_DIR_MASTER_READ_SLAVE_WRITE == p_ctrl->direction) ||
            ((IIC_B_SLAVE_TRANSFER_DIR_MASTER_WRITE_SLAVE_READ == p_ctrl->direction) &&
             (p_ctrl->p_cfg->addr_mode == I2C_SLAVE_ADDR_MODE_10BIT)))
        {
            /* Clear the Start and Stop condition flag for Slave Read/Write operation */
            p_ctrl->p_reg->BST &= ((uint32_t) ~(R_I3C0_BST_STCNDDF_Msk | R_I3C0_BST_SPCNDDF_Msk));
        }

        /* Enable the Start and Stop condition detection interrupt */

        /* Enable Interrupts: Timeout Detection, Arbitration Loss, NACK, Start, Stop Detection.
         * Disable Interrupt: Transmit End
         */
        p_ctrl->p_reg->BSTE = IIC_B_SLAVE_PRV_BSTE_INIT_MASK | R_I3C0_BIE_STCNDDIE_Msk | R_I3C0_BIE_SPCNDDIE_Msk;
        p_ctrl->p_reg->BIE  = IIC_B_SLAVE_PRV_BIE_INIT_MASK | R_I3C0_BIE_STCNDDIE_Msk | R_I3C0_BIE_SPCNDDIE_Msk;

        /* Enable Interrupts: Transmit Data Buffer Empty and Receive Data Buffer Full */
        p_ctrl->p_reg->NTIE = IIC_B_SLAVE_PRV_NTIE_INIT_MASK;
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to iic slave instance control block
 * @param[in]     event      Event code
 * @param[in]     transaction_count      Transaction count for iic slave
 **********************************************************************************************************************/
static void iic_b_slave_call_callback (iic_b_slave_instance_ctrl_t * p_ctrl,
                                       i2c_slave_event_t             event,
                                       uint32_t                      transaction_count)
{
    i2c_slave_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    i2c_slave_callback_args_t * p_args = p_ctrl->p_callback_memory;
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

    p_args->bytes     = transaction_count;
    p_args->event     = event;
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
        iic_b_slave_prv_ns_callback p_callback = (iic_b_slave_prv_ns_callback) (p_ctrl->p_callback);
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

/******************************************************************************************************************//**
 * Handles the receive data full interrupt when operating as a slave.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 *********************************************************************************************************************/
static void iic_b_rxi_slave (iic_b_slave_instance_ctrl_t * p_ctrl)
{
    /* Perform dummy read after an address match detection. */
    if (!p_ctrl->do_dummy_read)
    {
        p_ctrl->do_dummy_read = true;
        volatile uint8_t dummy_read = (uint8_t) (p_ctrl->p_reg->NTDTBP0 & IIC_B_SLAVE_PRV_NTDTBP0_SIZE);
        FSP_PARAMETER_NOT_USED(dummy_read);

        /* The below code enables/services 0 byte writes from Master by enabling stop detection.*/

        /* Since address match detected, enable STOP and START (RESTART) detection in case of Master Write Slave Read Operation.
         * This is done here (before the user API handling callback) so that RESTART handling is not missed if the
         * callback takes long and the Master issues the restart on the bus.
         * For 10-bit slave address this interrupt will be fired for both master read slave write and master write slave read operations,
         * Skip the start bit enable for 10-bit addresses. This is later done conditionally under iic_b_slave_initiate_transaction.
         *
         */
        if (p_ctrl->p_cfg->addr_mode == I2C_SLAVE_ADDR_MODE_7BIT)
        {
            p_ctrl->p_reg->BSTE = IIC_B_SLAVE_PRV_BSTE_INIT_MASK | R_I3C0_BIE_STCNDDIE_Msk | R_I3C0_BIE_SPCNDDIE_Msk;
            p_ctrl->p_reg->BST &= ((uint32_t) ~(R_I3C0_BST_STCNDDF_Msk | R_I3C0_BST_SPCNDDF_Msk));
        }
        else
        {
            p_ctrl->p_reg->BSTE = IIC_B_SLAVE_PRV_BSTE_INIT_MASK | R_I3C0_BIE_SPCNDDIE_Msk;
            p_ctrl->p_reg->BST &= ((uint32_t) ~(R_I3C0_BST_SPCNDDF_Msk));
        }

        /* Enable the Stop condition detection interrupt.
         * In case this is a greater than 0 byte write from Master and MasterWriteSlaveRead API is called
         * in the callback with valid parameters, this flag will be appropriately updated by helper function -
         * iic_b_slave_initiate_transaction.
         * Start condition is enabled here for Master Write Slave Read case to trigger an interrupt on detecting
         * a restart on the bus when slave is processing a long user callback.
         *
         * Enable Interrupts: Start, Stop Detection.
         * Disable Interrupt: Transmit End, Timeout Detection, Arbitration Loss, NACK
         */
        p_ctrl->p_reg->BIE = R_I3C0_BIE_STCNDDIE_Msk | R_I3C0_BIE_SPCNDDIE_Msk;

        /* Enable Interrupts: Transmit Data Buffer Empty and Receive Data Buffer Full */
        p_ctrl->p_reg->NTIE = IIC_B_SLAVE_PRV_NTIE_INIT_MASK;
    }
    else
    {
        /* Check if the read request event has been notified through callback, if not provide the callback */
        if (!p_ctrl->notify_request)
        {
            /* Check if this is a General Call by Master */
            i2c_slave_event_t receive_callback_event =
                (R_I3C0_SVST_GCAF_Msk ==
                 (p_ctrl->p_reg->SVST &
                  R_I3C0_SVST_GCAF_Msk)) ? I2C_SLAVE_EVENT_GENERAL_CALL : I2C_SLAVE_EVENT_RX_REQUEST;
            iic_b_slave_initiate_transaction(p_ctrl, receive_callback_event);
        }

#if IIC_B_SLAVE_CFG_PARAM_CHECKING_ENABLE

        /* Proceed reading data */
        if (IIC_B_SLAVE_TRANSFER_DIR_MASTER_WRITE_SLAVE_READ != p_ctrl->direction)
        {
            /* If the user application incorrectly handles Master Write, send a NACK to exit the transaction. */
            /* Do not dummy read here to allow slave to timeout */

            /* Writes to be done together with write protect bit.
             * See Note 1 in Section 27.2.15 'ACKCTL : Acknowledge Control Register'
             * of the RA6T2 manual R01UH0951EJ0050
             */
            p_ctrl->p_reg->ACKCTL = R_I3C0_ACKCTL_ACKTWP_Msk | R_I3C0_ACKCTL_ACKT_Msk;
        }
        else
#endif
        {
            if (0U == p_ctrl->total)   /* Send NACK */
            {
                /* Slave is sending a NACK. */
                /* Do dummy read to release SCL */
                volatile uint32_t dummy_read = p_ctrl->p_reg->NTDTBP0;
                FSP_PARAMETER_NOT_USED(dummy_read);

                /* Set the response as NACK, since slave is not setup for reading any data from master at this time.
                 * This is an intentional way to let master know that the slave receiver cannot
                 * accept any data and hence should eventually result in I2C_SLAVE_EVENT_RX_COMPLETE.
                 *
                 * Writes to be done together with write protect bit.
                 * See Note 1 in Section 27.2.15 'ACKCTL : Acknowledge Control Register'
                 * of the RA6T2 manual R01UH0951EJ0050
                 */
                p_ctrl->p_reg->ACKCTL = R_I3C0_ACKCTL_ACKTWP_Msk | R_I3C0_ACKCTL_ACKT_Msk;
            }
            /* If master is requesting still more data than configured to be read, notify
             * with a read more event in callback */
            else if (p_ctrl->total == p_ctrl->loaded)
            {
                iic_b_slave_callback_request(p_ctrl, I2C_SLAVE_EVENT_RX_MORE_REQUEST);
#if IIC_B_SLAVE_CFG_PARAM_CHECKING_ENABLE
                if (IIC_B_SLAVE_TRANSFER_DIR_MASTER_WRITE_SLAVE_READ != p_ctrl->direction)
                {
                    /* If the user application incorrectly handles Master Write, send a NACK to exit the transaction. */
                    /* Do not dummy read here to allow slave to timeout */
                    p_ctrl->p_reg->ACKCTL = R_I3C0_ACKCTL_ACKTWP_Msk | R_I3C0_ACKCTL_ACKT_Msk;
                }
                else
#endif
                {
                    if (0 == p_ctrl->total) /* Send NACK */
                    {
                        /* Do dummy read to release SCL */
                        volatile uint32_t dummy_read = p_ctrl->p_reg->NTDTBP0;
                        FSP_PARAMETER_NOT_USED(dummy_read);

                        /* Set the response as NACK, since slave is not setup for reading more data from master at this time.
                         * This is an intentional way to let master know that the slave receiver cannot
                         * accept any more data and hence should eventually result in I2C_SLAVE_EVENT_RX_COMPLETE.
                         */
                        p_ctrl->p_reg->ACKCTL = R_I3C0_ACKCTL_ACKTWP_Msk | R_I3C0_ACKCTL_ACKT_Msk;
                    }
                    else
                    {
                        /* Read data */
                        p_ctrl->p_buff[p_ctrl->loaded++] =
                            (uint8_t) (p_ctrl->p_reg->NTDTBP0 & IIC_B_SLAVE_PRV_NTDTBP0_SIZE);

                        /* Keep track of the the actual number of transactions */
                        p_ctrl->transaction_count++;
                    }
                }
            }
            else
            {
                /* Read data */
                p_ctrl->p_buff[p_ctrl->loaded++] = (uint8_t) (p_ctrl->p_reg->NTDTBP0 & IIC_B_SLAVE_PRV_NTDTBP0_SIZE);

                /* Keep track of the the actual number of transactions */
                p_ctrl->transaction_count++;
            }
        }
    }
}

/******************************************************************************************************************//**
 * Handles the transmit data empty interrupt when operating as a slave.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 *********************************************************************************************************************/
static void iic_b_txi_slave (iic_b_slave_instance_ctrl_t * p_ctrl)
{
    /* Check if the write request event has been notified through callback, if not provide the callback */
    if (!p_ctrl->notify_request)
    {
        iic_b_slave_initiate_transaction(p_ctrl, I2C_SLAVE_EVENT_TX_REQUEST);
    }

    /* If MasterReadSlaveWrite API is invoked, proceed writing data */
    if (IIC_B_SLAVE_TRANSFER_DIR_MASTER_READ_SLAVE_WRITE != p_ctrl->direction)
    {
        /* MasterReadSlaveWrite API was not called in the callback.
         * Master will read 0xFF for all the byte(s) for this transaction.
         */
    }
    else
    {
        /* If slave has exhausted the buffer length from application, wait for slave to transmit last byte on the bus
         * and check for master is sending ACK or NACK. If master ACKs this last byte, it is expecting more data
         * from slave. Slave has to notify this event to application via callback */
        if (p_ctrl->total == p_ctrl->loaded)
        {
            /* Clear the pending interrupts for TEI */
            R_BSP_IrqClearPending(p_ctrl->p_cfg->tei_irq);

            /* Enable the TEI interrupt source */
            p_ctrl->p_reg->BIE_b.TENDIE = 1U;
        }
        else
        {
            /* Write the data byte, this will also release SCL */
            p_ctrl->p_reg->NTDTBP0 = (uint32_t) p_ctrl->p_buff[p_ctrl->loaded];
            p_ctrl->loaded++;

            /* Keep track of the the actual number of transactions */
            p_ctrl->transaction_count++;
        }
    }
}

/******************************************************************************************************************//**
 * Handles the transmission end interrupt when operating as a slave.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 *********************************************************************************************************************/
static void iic_b_tei_slave (iic_b_slave_instance_ctrl_t * p_ctrl)
{
    uint32_t timeout_count = IIC_B_SLAVE_PERIPHERAL_REG_MAX_WAIT;

    /* Check if ACK has been detected from master expecting further data */
    if (0 == p_ctrl->p_reg->ACKCTL_b.ACKR)
    {
        iic_b_slave_callback_request(p_ctrl, I2C_SLAVE_EVENT_TX_MORE_REQUEST);

        if (IIC_B_SLAVE_TRANSFER_DIR_MASTER_READ_SLAVE_WRITE != p_ctrl->direction)
        {
            /* MasterReadSlaveWrite API was not called in the callback.
             * Master will read 0xFF for the remaining byte(s) for this transaction.
             */
        }
        else
        {
            p_ctrl->p_reg->NTDTBP0 = (uint32_t) p_ctrl->p_buff[p_ctrl->loaded];
            p_ctrl->loaded++;
            p_ctrl->transaction_count++;
        }
    }

    /* Disable the interrupt as we are done with the transfer */
    p_ctrl->p_reg->BIE_b.TENDIE = 0U;

    /* Wait for the value to reflect at the peripheral.
     * See 'Note' under Table 1.138 "Interrupt sources" of the RA2E2 manual: I2C I3C unified IP (R-I3C v2) */
    IIC_B_SLAVE_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->BIE_b.TENDIE, 0U, timeout_count);
}

/******************************************************************************************************************//**
 * Handles the error interrupts when operating as a slave.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 *********************************************************************************************************************/
static void iic_b_err_slave (iic_b_slave_instance_ctrl_t * p_ctrl)
{
    uint32_t error_events = IIC_B_SLAVE_PRV_BST_ERR_STATUS_MASK & p_ctrl->p_reg->BST;

    /* Timeout or Arbitration loss detected */
    if ((error_events & R_I3C0_BST_TODF_Msk) || (error_events & R_I3C0_BST_ALF_Msk))
    {
        /* Clear the stop flag. This indicates an error. */
        p_ctrl->transaction_completed = false;

        iic_b_slave_notify(p_ctrl, I2C_SLAVE_EVENT_ABORTED);
    }
    /* Stop or restart condition detected, a valid end of transaction.
     * Ensure callback is not fired for 10-bit Master-Read Slave-Write
     * transactions at the time of restart during address transmission. */
    else if ((error_events & R_I3C0_BST_STCNDDF_Msk) || (error_events & R_I3C0_BST_SPCNDDF_Msk))
    {
        i2c_slave_event_t i2c_event = I2C_SLAVE_EVENT_ABORTED;

        /* In case of stop (or restart), set the transaction_completed flag */
        p_ctrl->transaction_completed = true;

        /* Set the I2C event */
        if (IIC_B_SLAVE_TRANSFER_DIR_MASTER_WRITE_SLAVE_READ == p_ctrl->direction)
        {
            i2c_event = I2C_SLAVE_EVENT_RX_COMPLETE;
        }
        else
        {
            i2c_event = I2C_SLAVE_EVENT_TX_COMPLETE;

            /* Decrement the transaction count when slave configured to write more data than master requested.
             * Addresses the exception raised from double buffer hardware implementation */
            if (p_ctrl->total > p_ctrl->loaded)
            {
                p_ctrl->transaction_count -= 1U;
            }
        }

        /* Notify the user */
        iic_b_slave_notify(p_ctrl, i2c_event);
    }
    /* NACK detected */
    else if (error_events & R_I3C0_BST_NACKDF_Msk)
    {
        /* NACK interrupt will be triggered on MasterReadSlaveWrite operation.
         * Do dummy read to release SCL
         * Refer point number 5 under Section "27.3.1.1.2 Slave Mode Operation", "(1) I2C Slave Operation",
         * "(b) Data Read Transfer (Single Buffer transfer)" of the RA6T2 manual R01UH0951EJ0050
         */
        volatile uint32_t dummy_read = p_ctrl->p_reg->NTDTBP0;
        FSP_PARAMETER_NOT_USED(dummy_read);

        /* Disable NACK interrupt, this is required since we will clear NACK flag only on detection of STOP bit or
         * when a timeout occurs. Not clearing the flag will cause error interrupt to get triggered again.
         */
        p_ctrl->p_reg->BIE &= (uint32_t) ~R_I3C0_BIE_NACKDIE_Msk;
    }
    else
    {
        /* No processing, should not come here */
    }
}

/**********************************************************************************************************************
 * Interrupt Vectors
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * Receive data full interrupt routine.
 *
 * This function implements the IIC Receive buffer full ISR routine.
 *
 *********************************************************************************************************************/
void iic_b_slave_rxi_isr(void);

void iic_b_slave_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    iic_b_rxi_slave(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * Transmit data empty interrupt routine.
 *
 * This function implements the Transmit buffer empty ISR routine.
 *
 *********************************************************************************************************************/
void iic_b_slave_txi_isr(void);

void iic_b_slave_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    iic_b_txi_slave(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Transmit end interrupt routine.
 *
 * This function implements the IIC Transmission End ISR routine.
 *
 ***********************************************************************************************************************/
void iic_b_slave_tei_isr(void);

void iic_b_slave_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    iic_b_tei_slave(p_ctrl);

    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * Error and event interrupt routine.
 *
 * This function implements the IIC Event/Error.
 *
 *********************************************************************************************************************/
void iic_b_slave_eri_isr(void);

void iic_b_slave_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_slave_instance_ctrl_t * p_ctrl = (iic_b_slave_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    iic_b_err_slave(p_ctrl);

    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
