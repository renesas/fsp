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
 **********************************************************************************************************************/
#include "r_sci_b_i2c.h"

#if SCI_B_I2C_CFG_DTC_ENABLE
 #include "r_dtc.h"
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "I2CB" in ASCII, used to determine if channel is open. */
#define SCI_B_I2C_OPEN                                      ('I' << 0U | '2' << 1U | 'C' << 2U | 'B' << 3U)

#define SCI_B_I2C_PRV_CODE_READ                             (0x01U)
#define SCI_B_I2C_PRV_CODE_10BIT                            (0xF0U)

#define SCI_B_I2C_PRV_SLAVE_10_BIT_ADDR_LEN_ADJUST          (2U)

#define SCI_B_I2C_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL <<            \
                                                              TRANSFER_SETTINGS_MODE_BITS) |     \
                                                             (TRANSFER_SIZE_1_BYTE <<            \
                                                              TRANSFER_SETTINGS_SIZE_BITS) |     \
                                                             (TRANSFER_ADDR_MODE_FIXED <<        \
                                                              TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                                             (TRANSFER_IRQ_END <<                \
                                                              TRANSFER_SETTINGS_IRQ_BITS) |      \
                                                             (TRANSFER_ADDR_MODE_INCREMENTED <<  \
                                                              TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define SCI_B_I2C_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL <<            \
                                                              TRANSFER_SETTINGS_MODE_BITS) |     \
                                                             (TRANSFER_SIZE_1_BYTE <<            \
                                                              TRANSFER_SETTINGS_SIZE_BITS) |     \
                                                             (TRANSFER_ADDR_MODE_FIXED <<        \
                                                              TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                                             (TRANSFER_IRQ_END <<                \
                                                              TRANSFER_SETTINGS_IRQ_BITS) |      \
                                                             (TRANSFER_ADDR_MODE_FIXED <<        \
                                                              TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define SCI_B_I2C_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL <<            \
                                                              TRANSFER_SETTINGS_MODE_BITS) |     \
                                                             (TRANSFER_SIZE_1_BYTE <<            \
                                                              TRANSFER_SETTINGS_SIZE_BITS) |     \
                                                             (TRANSFER_ADDR_MODE_INCREMENTED <<  \
                                                              TRANSFER_SETTINGS_SRC_ADDR_BITS) | \
                                                             (TRANSFER_IRQ_END <<                \
                                                              TRANSFER_SETTINGS_IRQ_BITS) |      \
                                                             (TRANSFER_ADDR_MODE_FIXED <<        \
                                                              TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define SCI_B_I2C_PRV_MDDR_REG_MIN                          (0x80)
#define SCI_B_I2C_PRV_DUMMY_WRITE_DATA_FOR_READ_OP          (0xFFU)
#define SCI_B_I2C_PRV_DATA_REG_MASK                         (0xFFFFFF00)
#define SCI_B_I2C_PRV_GENERATE_REQUEST(R, X)    ((R & ~(R_SCI_B0_ICR_IICSDAS_Msk | R_SCI_B0_ICR_IICSCLS_Msk))          \
                                                 | (1U << R_SCI_B0_ICR_IICSDAS_Pos) | (1U << R_SCI_B0_ICR_IICSCLS_Pos) \
                                                 | X)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* I2C read/write enumeration */
typedef enum e_sci_b_i2c_transfer_dir_option
{
    SCI_B_I2C_TRANSFER_DIR_WRITE = 0x0,
    SCI_B_I2C_TRANSFER_DIR_READ  = 0x1
} sci_b_i2c_transfer_dir_t;

/* DTC TXI/RXI enumeration */
typedef enum e_sci_b_i2c_dtc_interrupt_trigger
{
    SCI_B_I2C_DTC_INTERRUPT_TRIGGER_TXI = 0x0,
    SCI_B_I2C_DTC_INTERRUPT_TRIGGER_RXI = 0x1
} sci_b_i2c_dtc_interrupt_trigger_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * sci_b_i2c_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile sci_b_i2c_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* Internal helper functions */
void        sci_b_i2c_notify(sci_b_i2c_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event);
static void sci_b_i2c_abort_seq_master(sci_b_i2c_instance_ctrl_t * const p_ctrl);

static fsp_err_t sci_b_i2c_read_write(i2c_master_ctrl_t * const p_api_ctrl,
                                      uint8_t * const           p_buffer,
                                      uint32_t const            bytes,
                                      sci_b_i2c_transfer_dir_t  direction);

/* Functions that manipulate hardware */
static void sci_b_i2c_open_hw_master(sci_b_i2c_instance_ctrl_t * const p_ctrl, i2c_master_cfg_t const * const p_cfg);
static void sci_b_i2c_run_hw_master(sci_b_i2c_instance_ctrl_t * const p_ctrl);

void sci_b_i2c_txi_isr(void);
void sci_b_i2c_tei_isr(void);

static void sci_b_i2c_txi_send_data(sci_b_i2c_instance_ctrl_t * const p_ctrl);
static void sci_b_i2c_tei_send_address(sci_b_i2c_instance_ctrl_t * const p_ctrl);

static void sci_b_i2c_tei_handler(sci_b_i2c_instance_ctrl_t * const p_ctrl);
static void sci_b_i2c_txi_handler(sci_b_i2c_instance_ctrl_t * const p_ctrl);
static void sci_b_i2c_txi_process_nack(sci_b_i2c_instance_ctrl_t * const p_ctrl);
static void sci_b_i2c_issue_restart_or_stop(sci_b_i2c_instance_ctrl_t * const p_ctrl);

#if SCI_B_I2C_CFG_DTC_ENABLE
void             sci_b_i2c_rxi_isr(void);
static fsp_err_t sci_b_i2c_transfer_open(sci_b_i2c_instance_ctrl_t * p_ctrl, i2c_master_cfg_t const * const p_cfg);
static fsp_err_t sci_b_i2c_transfer_configure(sci_b_i2c_instance_ctrl_t       * p_ctrl,
                                              transfer_instance_t const       * p_transfer,
                                              sci_b_i2c_dtc_interrupt_trigger_t trigger);
static void sci_b_i2c_reconfigure_interrupts_for_transfer(sci_b_i2c_instance_ctrl_t * const p_ctrl);
static void sci_b_i2c_enable_transfer_support_tx(sci_b_i2c_instance_ctrl_t * const p_ctrl);

#endif

/**********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* constant used as the source location for the DTC dummy write  */
static const uint8_t g_dummy_write_data_for_read_op = SCI_B_I2C_PRV_DUMMY_WRITE_DATA_FOR_READ_OP;

/**********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* Simple I2C on SCI HAL API mapping for I2C Master interface */
i2c_master_api_t const g_i2c_master_on_sci_b =
{
    .open            = R_SCI_B_I2C_Open,
    .read            = R_SCI_B_I2C_Read,
    .write           = R_SCI_B_I2C_Write,
    .abort           = R_SCI_B_I2C_Abort,
    .slaveAddressSet = R_SCI_B_I2C_SlaveAddressSet,
    .close           = R_SCI_B_I2C_Close,
    .callbackSet     = R_SCI_B_I2C_CallbackSet,
    .statusGet       = R_SCI_B_I2C_StatusGet
};

/*******************************************************************************************************************//**
 * @addtogroup SCI_B_I2C
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Opens the I2C device.
 *
 * @retval  FSP_SUCCESS                       Requested clock rate was set exactly.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT    Channel is not available on this MCU.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 *                                            4. Clock rate requested is greater than 400KHz
 *                                            5. Invalid IRQ number assigned
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_Open (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) p_api_ctrl;
#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT((p_cfg->rate == I2C_MASTER_RATE_STANDARD) || (p_cfg->rate == I2C_MASTER_RATE_FAST));
    FSP_ASSERT(p_cfg->txi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);
    FSP_ERROR_RETURN(SCI_B_I2C_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN((p_cfg->channel < 8 * sizeof(unsigned int)) && (BSP_FEATURE_SCI_CHANNELS & (1U << p_cfg->channel)),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
    sci_b_i2c_extended_cfg_t * pextend = (sci_b_i2c_extended_cfg_t *) p_cfg->p_extend;
    if (true == pextend->clock_settings.bitrate_modulation)
    {
        FSP_ASSERT(pextend->clock_settings.mddr_value >= SCI_B_I2C_PRV_MDDR_REG_MIN);
    }

 #if SCI_B_I2C_CFG_DTC_ENABLE
    if (NULL != p_cfg->p_transfer_rx)
    {
        FSP_ASSERT(p_cfg->rxi_irq >= (IRQn_Type) 0);
        FSP_ASSERT(p_cfg->p_transfer_tx != NULL);
    }
 #endif
#endif
#if SCI_B_I2C_CFG_DTC_ENABLE
    fsp_err_t err = FSP_SUCCESS;
#endif

    p_ctrl->p_reg = (R_SCI_B0_Type *) ((uint32_t) R_SCI0 + (p_cfg->channel * ((uint32_t) R_SCI1 - (uint32_t) R_SCI0)));;

    /* Record the configuration on the device for use later */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->slave             = p_cfg->slave;
    p_ctrl->addr_mode         = p_cfg->addr_mode;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

#if SCI_B_I2C_CFG_DTC_ENABLE

    /* Open transfer interfaces if available
     * In case of Read operations both p_transfer_tx and p_transfer_rx are used.
     * p_transfer_tx writes 0xFF to the TDR and p_transfer_rx reads from the RDR.
     * If p_transfer_tx is set to NULL, 0xFF would be written to TDR using the CPU
     * and the p_transfer_rx will be used to read the RDR.
     * Such a configuration will make the read operation CPU dependent and there would be
     * no benefit to use DRC on p_transfer_rx only.
     *
     * In case of Write operation p_transfer_tx is used to write to the TDR.
     */
    err = sci_b_i2c_transfer_open(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);

    /* Open the hardware in master mode */
    sci_b_i2c_open_hw_master(p_ctrl, p_cfg);

    p_ctrl->p_buff    = NULL;
    p_ctrl->total     = 0U;
    p_ctrl->remain    = 0U;
    p_ctrl->loaded    = 0U;
    p_ctrl->read      = false;
    p_ctrl->restart   = false;
    p_ctrl->err       = false;
    p_ctrl->restarted = false;
    p_ctrl->open      = SCI_B_I2C_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Performs a read from the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_RX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS                 Function executed without issue.
 * @retval  FSP_ERR_ASSERTION           The parameter p_ctrl, p_dest is NULL, bytes is 0.
 * @retval  FSP_ERR_INVALID_SIZE        Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                      for data transfer.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_Read (i2c_master_ctrl_t * const p_api_ctrl,
                            uint8_t * const           p_dest,
                            uint32_t const            bytes,
                            bool const                restart)
{
#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(bytes != 0U);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_master_read_write to 4. */
    ((sci_b_i2c_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Read operation.*/
    err = sci_b_i2c_read_write(p_api_ctrl, p_dest, bytes, SCI_B_I2C_TRANSFER_DIR_READ);

    return err;
}

/******************************************************************************************************************//**
 * Performs a write to the I2C device.
 *
 *  This function will fail if there is already an in-progress I2C transfer on the associated channel. Otherwise, the
 *  I2C write operation will begin. When no callback is provided by the user, this function performs a blocking write.
 *  Otherwise, the write operation is non-blocking and the caller will be notified when the operation has finished by
 *  an I2C_EVENT_TX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS                 Function executed without issue.
 * @retval  FSP_ERR_ASSERTION           p_ctrl, p_src is NULL.
 * @retval  FSP_ERR_INVALID_SIZE        Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                      for data transfer.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_Write (i2c_master_ctrl_t * const p_api_ctrl,
                             uint8_t * const           p_src,
                             uint32_t const            bytes,
                             bool const                restart)
{
#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_master_read_write to 4. */
    ((sci_b_i2c_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Write operation.*/
    err = sci_b_i2c_read_write(p_api_ctrl, p_src, bytes, SCI_B_I2C_TRANSFER_DIR_WRITE);

    return err;
}

/******************************************************************************************************************//**
 * Aborts any in-progress transfer and forces the I2C peripheral into a ready state.
 *
 *  This function will safely terminate any in-progress I2C transfer with the device. If a transfer is aborted, the user
 *  will be notified via callback with an abort event. Since the callback is optional, this function will also return
 *  a specific error code in this situation.
 *
 * @retval  FSP_SUCCESS                 Transaction was aborted without issue.
 * @retval  FSP_ERR_ASSERTION           p_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_Abort (i2c_master_ctrl_t * const p_api_ctrl)
{
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) p_api_ctrl;
#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(SCI_B_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort any transfer happening on the channel */
    sci_b_i2c_abort_seq_master(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets address and addressing mode of the slave device.
 *
 * This function is used to set the device address and addressing mode of the slave without reconfiguring the entire bus.
 *
 * @retval  FSP_SUCCESS                 Address of the slave is set correctly.
 * @retval  FSP_ERR_ASSERTION           p_ctrl or address is NULL.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 * @retval  FSP_ERR_IN_USE              An I2C Transaction is in progress.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_SlaveAddressSet (i2c_master_ctrl_t * const    p_api_ctrl,
                                       uint32_t const               slave,
                                       i2c_master_addr_mode_t const addr_mode)
{
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(SCI_B_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN(((0 == p_ctrl->remain) && (false == p_ctrl->restarted)), FSP_ERR_IN_USE);
#endif

    /* Sets the address of the slave device */
    p_ctrl->slave = slave;

    /* Sets the mode of addressing */
    p_ctrl->addr_mode = addr_mode;

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements i2c_master_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_CallbackSet (i2c_master_ctrl_t * const          p_api_ctrl,
                                   void (                           * p_callback)(i2c_master_callback_args_t *),
                                   void const * const                 p_context,
                                   i2c_master_callback_args_t * const p_callback_memory)
{
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) p_api_ctrl;

#if (SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SCI_B_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    i2c_master_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                             CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(i2c_master_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides driver status.
 *
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_StatusGet (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status)
{
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_status != NULL);
#endif

    p_status->open = (SCI_B_I2C_OPEN == p_ctrl->open);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Closes the I2C device. Power down I2C peripheral.
 *
 *  This function will safely terminate any in-progress I2C transfer with the device. If a transfer is aborted, the user
 *  will be notified via callback with an abort event. Since the callback is optional, this function will also return
 *  a specific error code in this situation.
 *
 * @retval  FSP_SUCCESS                 Device closed without issue.
 * @retval  FSP_ERR_ASSERTION           The parameter p_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 **********************************************************************************************************************/
fsp_err_t R_SCI_B_I2C_Close (i2c_master_ctrl_t * const p_api_ctrl)
{
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(SCI_B_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort an in-progress transfer with this device only */
    sci_b_i2c_abort_seq_master(p_ctrl);

    /* The device is now considered closed */
    p_ctrl->open = 0U;

#if SCI_B_I2C_CFG_DTC_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif
    R_BSP_MODULE_STOP(FSP_IP_SCI, p_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @} (end defgroup SCI_B_I2C)
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Helper function for handling I2C Read or Write.
 *
 * @param      p_api_ctrl      Pointer to control block
 * @param      p_buffer        Pointer to the buffer to store read/write data.
 * @param[in]  bytes           Number of bytes to be read/written.
 * @param[in]  direction       Read or Write
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_buffer is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than UINT16_MAX(= 65535) while DTC is used
 *                                for data transfer.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized. Call R_IIC_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
static fsp_err_t sci_b_i2c_read_write (i2c_master_ctrl_t * const p_api_ctrl,
                                       uint8_t * const           p_buffer,
                                       uint32_t const            bytes,
                                       sci_b_i2c_transfer_dir_t  direction)
{
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) p_api_ctrl;

#if SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_buffer != NULL);
    FSP_ERROR_RETURN((p_ctrl->open == SCI_B_I2C_OPEN), FSP_ERR_NOT_OPEN);
    FSP_ASSERT(((sci_b_i2c_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);

 #if SCI_B_I2C_CFG_DTC_ENABLE

    /* DTC on RX could actually receive 65535+3 = 65538 bytes as 3 bytes are handled separately.
     * Forcing to 65535 to keep TX and RX uniform with respect to max transaction length via DTC.
     */
    FSP_ERROR_RETURN((bytes <= UINT16_MAX), FSP_ERR_INVALID_SIZE);
 #endif
#endif

    p_ctrl->p_buff = p_buffer;
    p_ctrl->total  = bytes;

    /* Handle the (different) addressing mode(s) */
    if (p_ctrl->addr_mode == I2C_MASTER_ADDR_MODE_7BIT)
    {
        /* Set the address bytes according to a 7-bit slave read command */
        p_ctrl->addr_high  = 0U;
        p_ctrl->addr_low   = (uint8_t) ((p_ctrl->slave << 1U) | (uint8_t) direction);
        p_ctrl->addr_total = 1U;
    }

#if SCI_B_I2C_CFG_ADDR_MODE_10_BIT_ENABLE
    else
    {
        /* Set the address bytes according to a 10-bit slave read command */
        p_ctrl->addr_high =
            (uint8_t) (((p_ctrl->slave >> 7U) | SCI_B_I2C_PRV_CODE_10BIT) & (uint8_t) ~(SCI_B_I2C_PRV_CODE_READ));
        p_ctrl->addr_low = (uint8_t) p_ctrl->slave;

        /* Addr total = 3 for Read and 2 for Write (See section 27.3.1.3.1 "Communication Data Format" in the RA6T2 manual R01UH0951EJ0100). */
        p_ctrl->addr_total = (uint8_t) ((uint8_t) direction + SCI_B_I2C_PRV_SLAVE_10_BIT_ADDR_LEN_ADJUST);
    }
#endif

    p_ctrl->read = (bool) direction;

    /* Kickoff the read operation as a master */
    sci_b_i2c_run_hw_master(p_ctrl);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl      Pointer to transfer that is ending.
 * @param[in]       event       The event code to pass to the callback.
 **********************************************************************************************************************/
void sci_b_i2c_notify (sci_b_i2c_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event)
{
    i2c_master_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    i2c_master_callback_args_t * p_args = p_ctrl->p_callback_memory;
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
    p_args->event     = event;

#if SCI_B_I2C_CFG_DTC_ENABLE

    /* Stop any DTC assisted transfer for tx */
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
    if ((NULL != p_transfer_tx) && (!p_ctrl->read))
    {
        p_transfer_tx->p_api->disable(p_transfer_tx->p_ctrl);
    }

    /* Stop any DTC assisted transfer for rx */
    const transfer_instance_t * p_transfer_rx = p_ctrl->p_cfg->p_transfer_rx;
    if ((NULL != p_transfer_rx) && (p_ctrl->read))
    {
        p_transfer_rx->p_api->disable(p_transfer_rx->p_ctrl);
    }
#endif

    /* Now do the callback here */
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
        sci_b_i2c_prv_ns_callback p_callback = (sci_b_i2c_prv_ns_callback) (p_ctrl->p_callback);
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
 * Single point for managing the logic around aborting a transfer when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to control struct of specific device
 **********************************************************************************************************************/
static void sci_b_i2c_abort_seq_master (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    /* Safely stop the hardware from operating
     * - Disable Serial Reception and Transmission.
     * - Disable channel interrupts.
     */
    p_ctrl->p_reg->CCR0 = 0U;

    /* If TCLK is slower than the bus clock, then wait for the internal state to be updated (See Section 26.20.15 in the RA6T2 user manual). */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CESR, 0U);

    /* Set SDA and SCL to high impedance state. */
    p_ctrl->p_reg->ICR |= R_SCI_B0_ICR_IICSCLS_Msk | R_SCI_B0_ICR_IICSDAS_Msk;

    /* Update the transfer descriptor to show no longer in-progress and an error */
    p_ctrl->remain    = 0U;
    p_ctrl->restarted = false;
    p_ctrl->restart   = false;

    /* Update the transfer descriptor to make sure interrupts no longer process */
    p_ctrl->addr_loaded = p_ctrl->addr_total;
    p_ctrl->loaded      = p_ctrl->total;
}

/******************************************************************************************************************//**
 * Performs the hardware initialization sequence when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to control structure
 * @param[in]       p_cfg   Pointer to configuration structure
 *
 * @retval  FSP_SUCCESS                 Hardware initialized with proper configurations
 * @retval  FSP_ERR_INVALID_RATE        The requested rate cannot be set.
 **********************************************************************************************************************/
static void sci_b_i2c_open_hw_master (sci_b_i2c_instance_ctrl_t * const p_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    /* SCI Initialization in Simple IIC Mode (See Section 26.8.4 in RA6T2 manual R01UH0951EJ0100). */

    sci_b_i2c_extended_cfg_t * pextend = (sci_b_i2c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Set TEIE, TIE, RIE, TE, and RE to 0. */
    p_ctrl->p_reg->CCR0 = 0U;

    /* If TCLK is slower than the bus clock, then wait for the internal state to be updated (See Section 26.20.15 in the RA6T2 user manual). */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CESR, 0U);

    /* Write settings to ICR:
     * - Drive SDAn and SCLn pin to high-impedance state
     * - IICDL configuration settings.
     * - Configure IIC Interrupt mode to use Rx and Tx interrupts.
     * - Enable synchronization with the clock signal.
     * - Enable NACK transmission and reception of ACK/NACK.
     */
    uint32_t icr = R_SCI_B0_ICR_IICSCLS_Msk | R_SCI_B0_ICR_IICSDAS_Msk;
    icr |= (uint32_t) (pextend->clock_settings.cycles_value & R_SCI_B0_ICR_IICDL_Msk) <<
           R_SCI_B0_ICR_IICDL_Pos;
    icr               |= R_SCI_B0_ICR_IICINTM_Msk | R_SCI_B0_ICR_IICCSC_Msk | R_SCI_B0_ICR_IICACKT_Msk;
    p_ctrl->p_reg->ICR = icr;

    /* Write settings to CCR3:
     * - Set clock source.
     * - Set Character Length to 8-Bit.
     * - Set MSB first.
     * - Set Simple IIC Mode.
     */
    uint32_t ccr3 = 2U << R_SCI_B0_CCR3_CHR_Pos;
    ccr3               |= (uint32_t) pextend->clock_settings.clock_source << R_SCI_B0_CCR3_BPEN_Pos;
    ccr3               |= 4U << R_SCI_B0_CCR3_MOD_Pos;
    p_ctrl->p_reg->CCR3 = ccr3;

    /* Write settings to CCR2:
     * - Write the BRR setting.
     * - Write the MDDR enable setting.
     * - Write the clock divider setting.
     * - Write the MDDR setting.
     */
    uint32_t ccr2 = 4U << R_SCI_B0_CCR2_BCP_Pos;
    ccr2               |= (uint32_t) pextend->clock_settings.brr_value << R_SCI_B0_CCR2_BRR_Pos;
    ccr2               |= (uint32_t) pextend->clock_settings.bitrate_modulation << R_SCI_B0_CCR2_BRME_Pos;
    ccr2               |= (uint32_t) pextend->clock_settings.clk_divisor_value << R_SCI_B0_CCR2_CKS_Pos;
    ccr2               |= (uint32_t) pextend->clock_settings.mddr_value << R_SCI_B0_CCR2_MDDR_Pos;
    p_ctrl->p_reg->CCR2 = ccr2;

    /* Write settings to CCR1:
     * - Write the Noise filter setting.
     * - Enable the Noise filter.
     */
    p_ctrl->p_reg->CCR1 = (uint32_t) (pextend->clock_settings.snfr_value << R_SCI_B0_CCR1_NFCS_Pos) |
                          R_SCI_B0_CCR1_NFEN_Msk;

    /* Clear status flags. */
    p_ctrl->p_reg->CFCLR = (R_SCI_B0_CFCLR_RDRFC_Msk |
                            R_SCI_B0_CFCLR_FERC_Msk |
                            R_SCI_B0_CFCLR_PERC_Msk |
                            R_SCI_B0_CFCLR_MFFC_Msk |
                            R_SCI_B0_CFCLR_ORERC_Msk |
                            R_SCI_B0_CFCLR_DPERC_Msk |
                            R_SCI_B0_CFCLR_DCMFC_Msk |
                            R_SCI_B0_CFCLR_ERSC_Msk);

    p_ctrl->p_reg->ICFCLR = R_SCI_B0_ICFCLR_IICSTIFC_Msk;

    /* Enable interrupts (Note that when DTC is not used, data is read in the Transmit IRQ). */
    R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->ipl, p_ctrl);
#if SCI_B_I2C_CFG_DTC_ENABLE
    if (p_cfg->rxi_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->ipl, p_ctrl);
    }
#endif

    /* Step #9 of writing to CCR0 is done under helper function sci_b_i2c_run_hw_master */
}

/******************************************************************************************************************//**
 * Performs the data transfer described by the parameters when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to Control structure of specific device.
 *
 * @retval   FSP_SUCCESS                     Data transferred when operating as a master.
 * @retval   FSP_ERR_ABORTED                 If there is an in-progress transfer.
 **********************************************************************************************************************/
static void sci_b_i2c_run_hw_master (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    /* Initialize fields used during transfer */
    p_ctrl->addr_loaded       = 0U;
    p_ctrl->loaded            = 0U;
    p_ctrl->remain            = p_ctrl->total;
    p_ctrl->addr_remain       = p_ctrl->addr_total;
    p_ctrl->err               = false;
    p_ctrl->do_dummy_read     = false;
    p_ctrl->activation_on_txi = false;

    /* In case of read operation the first ACK detected on the bus is from the slave after the address is sent.
     * Since we are reading on every ACK detection on the bus [in this case from this driver],
     * we skip the first read corresponding to the address.
     */
    if (true == p_ctrl->read)
    {
        p_ctrl->do_dummy_read = true;
    }

    /* Enable TE, RE, TXI and TEIE. */
    p_ctrl->p_reg->CCR0 =
        (R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_RE_Msk | R_SCI_B0_CCR0_TEIE_Msk | R_SCI_B0_CCR0_TIE_Msk);

    /* If TCLK is slower than the bus clock, then wait for the internal state to be updated (See Section 26.20.15 in the RA6T2 user manual). */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CESR, (R_SCI_B0_CESR_TIST_Msk | R_SCI_B0_CESR_RIST_Msk));

#if SCI_B_I2C_CFG_DTC_ENABLE
    sci_b_i2c_reconfigure_interrupts_for_transfer(p_ctrl);
#endif

    /* Check if this is a new transaction or a continuation */
    if (!p_ctrl->restarted)
    {
        /* Initiate a start condition.
         * - The IICSTARREQ, IICSDAS, IICSCLS bits must be set simultaneously.
         * - IICDL, IICINTM, IICCSC, and IICACKT settings must be preserved.
         */
        p_ctrl->p_reg->ICR = SCI_B_I2C_PRV_GENERATE_REQUEST(p_ctrl->p_reg->ICR, R_SCI_B0_ICR_IICSTAREQ_Msk);
    }
    else
    {
        /* Clear for next transfer */
        p_ctrl->restarted = false;

#if SCI_B_I2C_CFG_DTC_ENABLE

        /* Enable transfer support for tx if this is the last address byte */
        if (1U == p_ctrl->addr_total)
        {
            sci_b_i2c_enable_transfer_support_tx(p_ctrl);
        }
#endif

        /* Send MSB or LSB based on the addressing mode.
         * - Write 1 byte data to the LSB byte in the data register.
         * - Write the initial value to the remaining bits in TDR.
         */
        uint32_t data_w = (1U == p_ctrl->addr_total) ? (p_ctrl->addr_low) : (p_ctrl->addr_high);
        data_w            |= SCI_B_I2C_PRV_DATA_REG_MASK;
        p_ctrl->p_reg->TDR = data_w;

        /* Update the trackers */
        p_ctrl->addr_remain--;
        p_ctrl->addr_loaded++;
    }
}

/******************************************************************************************************************//**
 * ISR for ACK/RXI interrupt
 *
 **********************************************************************************************************************/
#if SCI_B_I2C_CFG_DTC_ENABLE
void sci_b_i2c_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* This interrupt is invoked once DTC supported Read transfer is completed. Nothing to be done here. */

    /* Clear pending IRQ */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif

/******************************************************************************************************************//**
 * ISR for NACK/TXI interrupt
 *
 **********************************************************************************************************************/
void sci_b_i2c_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear pending IRQ */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Call the handler */
    sci_b_i2c_txi_handler(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * Handles the STI interrupt
 *
 *********************************************************************************************************************/
void sci_b_i2c_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    sci_b_i2c_instance_ctrl_t * p_ctrl = (sci_b_i2c_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Call the handler */
    sci_b_i2c_tei_handler(p_ctrl);

    /* Clear pending IRQ */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/******************************************************************************************************************//**
 * Handles the NACK/TXI interrupt .
 *
 * @param[in]       p_ctrl     pointer to the I2C control block.
 **********************************************************************************************************************/

static void sci_b_i2c_txi_handler (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    /* Check if ACK is detected  */
    if (0U == (p_ctrl->p_reg->ISR & R_SCI_B0_ISR_IICACKR_Msk))
    {
        /* 10 bit address, transfer the remaining address or generate RESTART */
        if (p_ctrl->addr_total != p_ctrl->addr_loaded)
        {
            /* Issue a RESTART as this is 10 bit address read and we have already transmitted the LSB */
            if ((p_ctrl->read) && (2U == p_ctrl->addr_loaded))
            {
                /* Initiate a restart condition.
                 * - The IICRSTARREQ, IICSDAS, IICSCLS bits must be set simultaneously.
                 * - IICDL, IICINTM, IICCSC, and IICACKT settings must be preserved.
                 */
                p_ctrl->p_reg->ICR = SCI_B_I2C_PRV_GENERATE_REQUEST(p_ctrl->p_reg->ICR, R_SCI_B0_ICR_IICRSTAREQ_Msk);
            }
            /* Transmit the LSB of the address */
            else
            {
#if SCI_B_I2C_CFG_DTC_ENABLE
                sci_b_i2c_enable_transfer_support_tx(p_ctrl);
#endif

                /* Write 1byte p_ctrl->addr_low to p_ctrl->addr_low register */
                p_ctrl->p_reg->TDR = SCI_B_I2C_PRV_DATA_REG_MASK | p_ctrl->addr_low;

                /* Update tracker that we have completed an address byte */
                p_ctrl->addr_remain--;
                p_ctrl->addr_loaded++;
            }
        }

#if SCI_B_I2C_CFG_DTC_ENABLE

        /* This is the first interrupt after the completion of DTC operation, ignore it */
        else if (true == p_ctrl->activation_on_txi)
        {
            p_ctrl->activation_on_txi = false;
        }
#endif

        /* Transmit/Receive data */
        else if (0U < p_ctrl->remain)
        {
            sci_b_i2c_txi_send_data(p_ctrl);
        }
        /* All transfers complete, send the required bus condition */
        else
        {
            sci_b_i2c_issue_restart_or_stop(p_ctrl);
        }
    }
    /* NACK detected: Either a NACK interrupt or TXI interrupt with NACK flag set */
    else
    {
        sci_b_i2c_txi_process_nack(p_ctrl);
    }
}

/******************************************************************************************************************//**
 * Handles the START/STOP interrupt .
 *
 * @param[in]       p_ctrl     pointer to the I2C control block.
 **********************************************************************************************************************/
static void sci_b_i2c_tei_handler (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    /* Clear the interrupt STI flag */
    p_ctrl->p_reg->ICFCLR = R_SCI_B0_ICFCLR_IICSTIFC_Msk;

    if (p_ctrl->err)
    {
        /* Set SDA and SCL to high impedance state. */
        p_ctrl->p_reg->ICR |= R_SCI_B0_ICR_IICSCLS_Msk | R_SCI_B0_ICR_IICSDAS_Msk;

        /* Notify the user of the error */
        sci_b_i2c_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);
    }
    /* Address transmission is not complete, this could be the START condition prior to the transmission
     *  of first address byte or RESTART condition in between a 10 bit address read */
    else if (p_ctrl->addr_total != p_ctrl->addr_loaded)
    {
        /* Check to send address */
        sci_b_i2c_tei_send_address(p_ctrl);
    }
    /*This a STOP or RESTART after completion of the read/write operation */
    else if (0U == p_ctrl->remain)
    {
        i2c_master_event_t event = p_ctrl->read ? I2C_MASTER_EVENT_RX_COMPLETE : I2C_MASTER_EVENT_TX_COMPLETE;

        /* Set the SCL/SDA lines to the required state */
        if (p_ctrl->restarted)
        {
            /* Configure SDA and SCL for serial output. */
            p_ctrl->p_reg->ICR &= ~(R_SCI_B0_ICR_IICSDAS_Msk | R_SCI_B0_ICR_IICSCLS_Msk);
        }
        else
        {
            /* Set SDA and SCL to high impedance state. */
            p_ctrl->p_reg->ICR |= R_SCI_B0_ICR_IICSCLS_Msk | R_SCI_B0_ICR_IICSDAS_Msk;

            /* Disable the transmitter and receiver */
            p_ctrl->p_reg->CCR0 &= ~(R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_RE_Msk);

            /* If TCLK is slower than the bus clock, then wait for the internal state to be updated (See Section 26.20.15 in the RA6T2 user manual). */
            FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CESR, 0U);
        }

        /* Notify anyone waiting that the transfer is finished */
        sci_b_i2c_notify(p_ctrl, event);
    }
    else
    {
        /*Do nothing*/
    }
}

#if SCI_B_I2C_CFG_DTC_ENABLE

/*******************************************************************************************************************//**
 * Configures SCI I2C related transfer drivers (if enabled).
 *
 * @param[in]     p_ctrl   Pointer to SCI I2C specific control structure
 * @param[in]     p_cfg    Pointer to SCI I2C specific configuration structure
 *
 * @retval FSP_SUCCESS                 If configures SCI I2C related transfer drivers
 * @retval FSP_ERR_ASSERTION           Transfer configuration for tx/rx not proper.
 **********************************************************************************************************************/
static fsp_err_t sci_b_i2c_transfer_open (sci_b_i2c_instance_ctrl_t * const p_ctrl,
                                          i2c_master_cfg_t const * const    p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    if (NULL != p_cfg->p_transfer_rx)
    {
        err = sci_b_i2c_transfer_configure(p_ctrl, p_cfg->p_transfer_rx, SCI_B_I2C_DTC_INTERRUPT_TRIGGER_RXI);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        err = sci_b_i2c_transfer_configure(p_ctrl, p_cfg->p_transfer_tx, SCI_B_I2C_DTC_INTERRUPT_TRIGGER_TXI);
        if (FSP_SUCCESS != err)
        {
            if (NULL != p_cfg->p_transfer_rx)
            {
                err = p_cfg->p_transfer_rx->p_api->close(p_cfg->p_transfer_rx->p_ctrl);
            }

            return err;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures  DTC
 * @param[in]     p_ctrl                     Pointer to I2C specific control structure
 * @param[in]     p_transfer                 Pointer to DTC instance structure
 * @param[in]     trigger                    TXI or RXI to be set as trigger
 *
 * @retval        FSP_SUCCESS                Transfer interface is configured with valid parameters.
 * @retval        FSP_ERR_ASSERTION          Pointer to transfer instance for I2C receive in p_cfg is NULL.
 **********************************************************************************************************************/
static fsp_err_t sci_b_i2c_transfer_configure (sci_b_i2c_instance_ctrl_t       * p_ctrl,
                                               transfer_instance_t const       * p_transfer,
                                               sci_b_i2c_dtc_interrupt_trigger_t trigger)
{
    fsp_err_t err;

    /* Set default transfer info and open receive transfer module, if enabled. */
 #if (SCI_B_I2C_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_transfer->p_api);
    FSP_ASSERT(NULL != p_transfer->p_ctrl);
    FSP_ASSERT(NULL != p_transfer->p_cfg);
    FSP_ASSERT(NULL != p_transfer->p_cfg->p_info);
 #endif
    transfer_info_t * p_cfg = p_transfer->p_cfg->p_info;
    if (SCI_B_I2C_DTC_INTERRUPT_TRIGGER_RXI == trigger)
    {
        p_cfg->transfer_settings_word = SCI_B_I2C_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS;
        p_cfg->p_src = (void *) (&(p_ctrl->p_reg->RDR));
    }
    else
    {
        /* In case of read operation using DTC, the TXI interrupt will trigger the DTC to write 0xFF into TDR (See Figure 26.94 in the RA6T2 manual R01UH0951EJ0100). */
        /* In case of Write operation this will be reconfigured */
        p_cfg->transfer_settings_word = SCI_B_I2C_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS;
        p_cfg->p_dest                 = (void *) (&(p_ctrl->p_reg->TDR));
    }

    err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Reconfigure the address mode for transfer interface
 *
 * @param[in]  p_ctrl     transfer control block
 *
 * @retval FSP_SUCCESS                       Address mode for transfer interface reconfigured.
 **********************************************************************************************************************/
static void sci_b_i2c_reconfigure_interrupts_for_transfer (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    if (NULL != p_transfer_tx)
    {
        transfer_info_t * p_info = p_transfer_tx->p_cfg->p_info;

        /* Disable the transmitter and receiver for reconfiguring interrupt source */
        p_ctrl->p_reg->CCR0 = 0;

        /* If TCLK is slower than the bus clock, then wait for the internal state to be updated (See Section 26.20.15 in the RA6T2 user manual). */
        FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CESR, 0U);

        if (p_ctrl->read)
        {
            /* Re-adjust address modes */
            p_info->transfer_settings_word = SCI_B_I2C_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS;
            p_info->p_src = (void *) &g_dummy_write_data_for_read_op;
        }
        else                           /* This is a write operation */
        {
            /* Re-adjust address modes */
            p_info->transfer_settings_word = SCI_B_I2C_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;
        }

        /* Set the interrupt source to RXI/TXI */
        p_ctrl->p_reg->CCR0 =
            (R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_RE_Msk | R_SCI_B0_CCR0_TEIE_Msk | R_SCI_B0_CCR0_TIE_Msk);

        /* If TCLK is slower than the bus clock, then wait for the internal state to be updated (See Section 26.20.15 in the RA6T2 user manual). */
        FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->CESR, (R_SCI_B0_CESR_TIST_Msk | R_SCI_B0_CESR_RIST_Msk));
    }
}

/*******************************************************************************************************************//**
 * Enables the dtc transfer interface for the transmit operation
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void sci_b_i2c_enable_transfer_support_tx (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    if ((NULL != p_transfer_tx) && (!p_ctrl->read))
    {
        /* Enable transfer interface to write to TDR
         * Re-configures the source buffer to the user buffer as this is a Write operation.
         */
        p_transfer_tx->p_api->reset(p_transfer_tx->p_ctrl, (void *) (p_ctrl->p_buff), NULL,
                                    (uint16_t) (p_ctrl->remain));

        p_ctrl->remain = 0U;
        p_ctrl->loaded = p_ctrl->total;

        p_ctrl->activation_on_txi = true;
    }
}

#endif

/*******************************************************************************************************************//**
 * Check for the receive condition.
 *
 * @param[in]  p_ctrl     Pointer to transfer control block
 **********************************************************************************************************************/
static void sci_b_i2c_txi_send_data (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    /* As per the hardware manual, a byte should be written to TDR to generate SCL.
     * If we are doing an I2C read, we will write 0xFF to the TDR  */
    uint8_t data = g_dummy_write_data_for_read_op;

    /* This is a write operation, update the data byte from user buffer */
    if (!p_ctrl->read)
    {
        data = p_ctrl->p_buff[p_ctrl->loaded];

        /* Update trackers */
        p_ctrl->remain--;
        p_ctrl->loaded++;
    }
    /* This is a read operation, move data from RDR and do dummy write to TDR. */
    else
    {
        /* Skip updating the buffer on first interrupt as it is the ACK of address */
        if (true == p_ctrl->do_dummy_read)
        {
            p_ctrl->do_dummy_read = false;
#if SCI_B_I2C_CFG_DTC_ENABLE

            /* If transfer interface is available, use it.
             * Enable the transfer interfaces if the number of bytes to be read is greater than 2.
             * The last two bytes will be read through interrupt, this is for support NACK before STOP.
             */
            if ((NULL != p_ctrl->p_cfg->p_transfer_tx) && (NULL != p_ctrl->p_cfg->p_transfer_rx) &&
                (p_ctrl->total > 2U))
            {
                /* Enable RXI  interrupt */
                p_ctrl->p_reg->CCR0 =
                    (R_SCI_B0_CCR0_TE_Msk | R_SCI_B0_CCR0_RE_Msk | R_SCI_B0_CCR0_TEIE_Msk | R_SCI_B0_CCR0_TIE_Msk |
                     R_SCI_B0_CCR0_RIE_Msk);

                /* Enable transfer interface for reading data from RDR */
                p_ctrl->p_cfg->p_transfer_rx->p_api->reset(p_ctrl->p_cfg->p_transfer_rx->p_ctrl, NULL,
                                                           (void *) (p_ctrl->p_buff), (uint16_t) (p_ctrl->total - 2U));

                /* Enable transfer interface to do dummy write into TDR */
                p_ctrl->p_cfg->p_transfer_tx->p_api->reset(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                           NULL,
                                                           NULL,
                                                           (uint16_t) (p_ctrl->total - 2U));

                /* Update the tracker variables */
                p_ctrl->remain = 2U;
                p_ctrl->loaded = p_ctrl->total - 2U;

                /* Mark DTC activation for TXI */
                p_ctrl->activation_on_txi = true;
            }
#endif

            /* If number of bytes to be received is greater than one, set ACK transmission
             * NACK transmission will be set before the last byte is read.
             */
            if (1U < p_ctrl->remain)
            {
                p_ctrl->p_reg->ICR_b.IICACKT = 0;
            }
        }
        /* Read data into the buffer */
        else
        {
            p_ctrl->p_buff[p_ctrl->loaded] = (uint8_t) (p_ctrl->p_reg->RDR & UINT8_MAX);

            /* Update trackers */
            p_ctrl->remain--;
            p_ctrl->loaded++;
        }

        /* Enable NACK transmission prior to the reception of the last byte */
        if (1U == p_ctrl->remain)
        {
            p_ctrl->p_reg->ICR_b.IICACKT = 1;
        }
    }

    /* Write 1 byte data to data register (see Figure 26.91 and Figure 26.94 in the RA6T2 manual R01UH0951EJ0100).
     * - In case of write operation this will be data from user buffer.
     * - In case of read operation this will be 0xFF as required by HW.
     */
    p_ctrl->p_reg->TDR = SCI_B_I2C_PRV_DATA_REG_MASK | data;
}

/*******************************************************************************************************************//**
 * Enables transfer support while handling the tei interrupt
 *
 * @param[in] p_ctrl     Pointer to transfer control block
 **********************************************************************************************************************/
static void sci_b_i2c_tei_send_address (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    uint8_t data = 0U;

    /* This is the first address byte */
    if (0U == p_ctrl->addr_loaded)
    {
#if SCI_B_I2C_CFG_DTC_ENABLE

        /* Enable transfer support for tx if this is the last address byte */
        if (1U == p_ctrl->addr_total)
        {
            sci_b_i2c_enable_transfer_support_tx(p_ctrl);
        }
#endif

        /* if 7 bit addressing, send LSB else send MSB of address word */
        data = (1U == p_ctrl->addr_total) ? p_ctrl->addr_low : p_ctrl->addr_high;
    }
    /* This is a 10 bit read operation, issue the address as per the protocol */
    else if ((p_ctrl->read) && (p_ctrl->addr_loaded == 2U))
    {
        /* Write address MSB with R/W bit set to read */
        data = p_ctrl->addr_high | (uint8_t) SCI_B_I2C_PRV_CODE_READ;
    }
    /* Shouldn't have come here, do nothing */
    else
    {
        /* Do Nothing */
    }

    /* Configure SDA and SCL for serial output. */
    p_ctrl->p_reg->ICR &= ~(R_SCI_B0_ICR_IICSDAS_Msk | R_SCI_B0_ICR_IICSCLS_Msk);

    /* Write 1 byte data to data LSB byte in TDR. */
    p_ctrl->p_reg->TDR = SCI_B_I2C_PRV_DATA_REG_MASK | data;

    /* Update the number of address bytes remain for next pass */
    p_ctrl->addr_remain--;
    p_ctrl->addr_loaded++;
}

/*******************************************************************************************************************//**
 * Process NACK reception within TXI interrupt
 *
 * @param[in] p_ctrl     Pointer to transfer control block
 **********************************************************************************************************************/
static void sci_b_i2c_txi_process_nack (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    /* If we are doing master write, or address is NACKed during read operation, this is an error condition, set error and send stop  */
    if ((!p_ctrl->read) || (true == p_ctrl->do_dummy_read))
    {
        p_ctrl->remain = 0U;
        p_ctrl->err    = true;

        /* Initiate a stop condition.
         * - The IICSTPREQ, IICSDAS, IICSCLS bits must be set simultaneously.
         * - IICDL, IICINTM, IICCSC, and IICACKT settings must be preserved.
         */
        p_ctrl->p_reg->ICR = SCI_B_I2C_PRV_GENERATE_REQUEST(p_ctrl->p_reg->ICR, R_SCI_B0_ICR_IICSTPREQ_Msk);
    }
    /* If we are doing master read, this marks the end of transaction, read the last byte from RDR  before
     * generating the required bus condition */
    else
    {
        /* Load the RDR into user buffer */
        p_ctrl->p_buff[p_ctrl->loaded] = (uint8_t) (p_ctrl->p_reg->RDR & UINT8_MAX);

        /* Update trackers */
        p_ctrl->remain--;
        p_ctrl->loaded++;

        sci_b_i2c_issue_restart_or_stop(p_ctrl);
    }
}

/*******************************************************************************************************************//**
 * This helper function issues a Restart or a Stop condition on the channel.
 *
 * @param[in]  p_ctrl         Instance control structure.
 **********************************************************************************************************************/
static void sci_b_i2c_issue_restart_or_stop (sci_b_i2c_instance_ctrl_t * const p_ctrl)
{
    /* Initiate a stop or restart condition.
     * - IICDL, IICINTM, IICCSC, and IICACKT settings must be preserved.
     */
    uint32_t icr = p_ctrl->p_reg->ICR;
    icr &= ~(R_SCI_B0_ICR_IICSDAS_Msk | R_SCI_B0_ICR_IICSCLS_Msk);
    icr |= (1U << R_SCI_B0_ICR_IICSDAS_Pos) | (1U << R_SCI_B0_ICR_IICSCLS_Pos);

    if (true == p_ctrl->restart)
    {
        /* The IICRSTARREQ, IICSDAS, IICSCLS bits must be set simultaneously. */
        p_ctrl->p_reg->ICR = (R_SCI_B0_ICR_IICRSTAREQ_Msk | icr);
        p_ctrl->restarted  = true;
    }
    else
    {
        /* The IICRSTPREQ, IICSDAS, IICSCLS bits must be set simultaneously. */
        p_ctrl->p_reg->ICR = (R_SCI_B0_ICR_IICSTPREQ_Msk | icr);
    }
}
