/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "r_sau_i2c.h"

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE
 #include "r_dtc.h"
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "SI2C" in ASCII, used to determine if channel is open. */
#define SAU_I2C_OPEN                                      (0x53493243ULL)

#define SAU_I2C_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL <<              \
                                                            TRANSFER_SETTINGS_MODE_BITS) |       \
                                                           (TRANSFER_CHAIN_MODE_EACH <<          \
                                                            TRANSFER_SETTINGS_CHAIN_MODE_BITS) | \
                                                           (TRANSFER_SIZE_1_BYTE <<              \
                                                            TRANSFER_SETTINGS_SIZE_BITS) |       \
                                                           (TRANSFER_ADDR_MODE_FIXED <<          \
                                                            TRANSFER_SETTINGS_SRC_ADDR_BITS) |   \
                                                           (TRANSFER_IRQ_END <<                  \
                                                            TRANSFER_SETTINGS_IRQ_BITS) |        \
                                                           (TRANSFER_ADDR_MODE_INCREMENTED <<    \
                                                            TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define SAU_I2C_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS     ((TRANSFER_MODE_NORMAL <<              \
                                                            TRANSFER_SETTINGS_MODE_BITS) |       \
                                                           (TRANSFER_CHAIN_MODE_DISABLED <<      \
                                                            TRANSFER_SETTINGS_CHAIN_MODE_BITS) | \
                                                           (TRANSFER_SIZE_1_BYTE <<              \
                                                            TRANSFER_SETTINGS_SIZE_BITS) |       \
                                                           (TRANSFER_ADDR_MODE_FIXED <<          \
                                                            TRANSFER_SETTINGS_SRC_ADDR_BITS) |   \
                                                           (TRANSFER_IRQ_END <<                  \
                                                            TRANSFER_SETTINGS_IRQ_BITS) |        \
                                                           (TRANSFER_ADDR_MODE_FIXED <<          \
                                                            TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define SAU_I2C_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS    ((TRANSFER_MODE_NORMAL <<              \
                                                            TRANSFER_SETTINGS_MODE_BITS) |       \
                                                           (TRANSFER_CHAIN_MODE_DISABLED <<      \
                                                            TRANSFER_SETTINGS_CHAIN_MODE_BITS) | \
                                                           (TRANSFER_SIZE_1_BYTE <<              \
                                                            TRANSFER_SETTINGS_SIZE_BITS) |       \
                                                           (TRANSFER_ADDR_MODE_INCREMENTED <<    \
                                                            TRANSFER_SETTINGS_SRC_ADDR_BITS) |   \
                                                           (TRANSFER_IRQ_END <<                  \
                                                            TRANSFER_SETTINGS_IRQ_BITS) |        \
                                                           (TRANSFER_ADDR_MODE_FIXED <<          \
                                                            TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define SAU_I2C_PRV_DUMMY_WRITE_DATA_FOR_READ_OP          (0xFFU)

#define SAU_I2C_PRV_SMR_INIT                              (0x0024U)
#define SAU_I2C_PRV_SCR_REG_INIT                          (0x8017U)
#define SAU_I2C_PRV_SO0_REG_INIT                          (0x0101U)
#define SAU_I2C_PRV_SCR_TE_MASK                           (0x8000U)
#define SAU_I2C_PRV_SCR_RE_MASK                           (0x4000U)

#define SAU_I2C_SO_SCL_HIGH                               (1 << R_SAU0_SO_CKO_Pos)
#define SAU_I2C_SO_SDA_HIGH                               (1 << R_SAU0_SO_SO_Pos)

#define SAU_I2C_PRV_SIR_MASK                              (R_SAU0_SIR_OVCT_Msk | R_SAU0_SIR_PECT_Msk | \
                                                           R_SAU0_SIR_FECT_Msk)

#if SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE == 1
 #define SAU_REG                                          (R_SAU0)
#elif SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE == 2
 #define SAU_REG                                          (R_SAU1)
#else
 #define SAU_REG                                          (p_ctrl->p_reg)
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* I2C read/write enumeration */
typedef enum e_sau_i2c_transfer_dir_option
{
    SAU_I2C_TRANSFER_DIR_WRITE = 0x0,
    SAU_I2C_TRANSFER_DIR_READ  = 0x1
} sau_i2c_transfer_dir_t;

/**********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* Internal helper functions */
static void r_sau_i2c_notify(sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event);
static void r_sau_i2c_abort_seq_master(sau_i2c_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sau_i2c_read_write(i2c_master_ctrl_t * const p_api_ctrl,
                                      uint8_t * const           p_buffer,
                                      uint32_t const            bytes,
                                      sau_i2c_transfer_dir_t    direction);

/* Functions that manipulate hardware */
static void r_sau_i2c_open_hw_master(sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_cfg_t const * const p_cfg);
static void r_sau_i2c_run_hw_master(sau_i2c_instance_ctrl_t * const p_ctrl);
static void r_sau_i2c_stop_prepare(sau_i2c_instance_ctrl_t * const p_ctrl);

void sau_i2c_tei_isr(void);

static void r_sau_i2c_tei_handler(sau_i2c_instance_ctrl_t * const p_ctrl);

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE
static fsp_err_t r_sau_i2c_transfer_open(sau_i2c_instance_ctrl_t * p_ctrl, i2c_master_cfg_t const * const p_cfg);
static fsp_err_t r_sau_i2c_transfer_configure(sau_i2c_instance_ctrl_t * p_ctrl, transfer_instance_t const * p_transfer);
static void      r_sau_i2c_reconfigure_interrupts_for_transfer(sau_i2c_instance_ctrl_t * const p_ctrl);

#endif

/**********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* constant used as the source location for the DTC dummy write */
static const uint8_t g_dummy_write_data_for_read_op = SAU_I2C_PRV_DUMMY_WRITE_DATA_FOR_READ_OP;

/**********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* Simple I2C on SAU HAL API mapping for I2C Master interface */
i2c_master_api_t const g_i2c_master_on_sau =
{
    .open            = R_SAU_I2C_Open,
    .read            = R_SAU_I2C_Read,
    .write           = R_SAU_I2C_Write,
    .abort           = R_SAU_I2C_Abort,
    .slaveAddressSet = R_SAU_I2C_SlaveAddressSet,
    .close           = R_SAU_I2C_Close,
    .callbackSet     = R_SAU_I2C_CallbackSet,
    .statusGet       = R_SAU_I2C_StatusGet
};

/*******************************************************************************************************************//**
 * @addtogroup SAU_I2C
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/******************************************************************************************************************//**
 * Opens the SAU device.
 *
 * @retval  FSP_SUCCESS                       Requested clock rate was set exactly.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 *                                            4. Clock rate requested is greater than 400KHz
 *                                            5. Invalid IRQ number assigned
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_Open (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT((I2C_MASTER_RATE_STANDARD == p_cfg->rate) || (I2C_MASTER_RATE_FAST == p_cfg->rate) ||
               (I2C_MASTER_RATE_FASTPLUS == p_cfg->rate));
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);
    FSP_ERROR_RETURN(SAU_I2C_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

#if !SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE
    SAU_REG =
        (R_SAU0_Type *) ((uint32_t) R_SAU0_BASE +
                         (p_ctrl->i2c_unit * ((uint32_t) R_SAU1_BASE - (uint32_t) R_SAU0_BASE)));
#endif

    /* Record the configuration on the device for use later */
    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->slave      = (uint8_t) p_cfg->slave;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

    /* When DTC is enabled, data read and write will be done using DTC.
     * There is only 1 IRQ for SAU I2C, so chain transfer mode will be used.
     * p_transfer_tx points to an array of two transfer info descriptors.
     * The first one is for reading data from SDR,
     * and the second one is for writing data to SDR.
     * For write operation, only the second transfer descriptor will be used.
     */
    fsp_err_t err = FSP_SUCCESS;
    err = r_sau_i2c_transfer_open(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    R_BSP_MODULE_START(FSP_IP_SAU, p_ctrl->i2c_unit);

    /* Open the hardware in master mode */
    r_sau_i2c_open_hw_master(p_ctrl, p_cfg);

    p_ctrl->p_buff    = NULL;
    p_ctrl->total     = 0U;
    p_ctrl->remain    = 0U;
    p_ctrl->loaded    = 0U;
    p_ctrl->read      = false;
    p_ctrl->restarted = false;
    p_ctrl->restart   = false;
    p_ctrl->open      = SAU_I2C_OPEN;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Performs a read from the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_RX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS                 Function executed without issue.
 * @retval  FSP_ERR_ASSERTION           The parameter p_api_ctrl, p_dest is NULL, bytes is 0.
 * @retval  FSP_ERR_INVALID_SIZE        Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                      for data transfer.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_Read (i2c_master_ctrl_t * const p_api_ctrl,
                          uint8_t * const           p_dest,
                          uint32_t const            bytes,
                          bool const                restart)
{
#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(bytes != 0U);
#endif

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_master_read_write to 4. */
    ((sau_i2c_instance_ctrl_t *) p_api_ctrl)->restart = restart;
    fsp_err_t err = FSP_SUCCESS;

    /* Call the common helper function to perform I2C Read operation.*/
    err = r_sau_i2c_read_write(p_api_ctrl, p_dest, bytes, SAU_I2C_TRANSFER_DIR_READ);

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
 * @retval  FSP_ERR_ASSERTION           p_api_ctrl, p_src is NULL.
 * @retval  FSP_ERR_INVALID_SIZE        Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                      for data transfer.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_Write (i2c_master_ctrl_t * const p_api_ctrl,
                           uint8_t * const           p_src,
                           uint32_t const            bytes,
                           bool const                restart)
{
#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_master_read_write to 4. */
    ((sau_i2c_instance_ctrl_t *) p_api_ctrl)->restart = restart;
    fsp_err_t err = FSP_SUCCESS;

    /* Call the common helper function to perform I2C Write operation.*/
    err = r_sau_i2c_read_write(p_api_ctrl, p_src, bytes, SAU_I2C_TRANSFER_DIR_WRITE);

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
fsp_err_t R_SAU_I2C_Abort (i2c_master_ctrl_t * const p_api_ctrl)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(SAU_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort any transfer happening on the channel */
    r_sau_i2c_abort_seq_master(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets address of the slave device.
 *
 * This function is used to set the device address of the slave without reconfiguring the entire bus.
 *
 * @retval  FSP_SUCCESS                 Address of the slave is set correctly.
 * @retval  FSP_ERR_ASSERTION           p_ctrl or address is NULL.
 * @retval  FSP_ERR_NOT_OPEN            Device was not even opened.
 * @retval  FSP_ERR_IN_USE              An I2C Transaction is in progress.
 *
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_SlaveAddressSet (i2c_master_ctrl_t * const    p_api_ctrl,
                                     uint32_t const               slave,
                                     i2c_master_addr_mode_t const addr_mode)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(SAU_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN((0 == p_ctrl->remain), FSP_ERR_IN_USE);

    /* Fail if the addr_mode is not 7-bit mode */
    FSP_ASSERT(I2C_MASTER_ADDR_MODE_7BIT == addr_mode);
#endif

    /* Sets the address of the slave device */
    p_ctrl->slave = (uint8_t) slave;

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
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_CallbackSet (i2c_master_ctrl_t * const          p_api_ctrl,
                                 void (                           * p_callback)(i2c_master_callback_args_t *),
                                 void const * const                 p_context,
                                 i2c_master_callback_args_t * const p_callback_memory)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if (SAU_I2C_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ASSERT(p_callback_memory == NULL);
    FSP_ERROR_RETURN(SAU_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides driver status.
 *
 * @retval     FSP_SUCCESS                   Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_StatusGet (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_status != NULL);
#endif

    p_status->open = (SAU_I2C_OPEN == p_ctrl->open);

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
fsp_err_t R_SAU_I2C_Close (i2c_master_ctrl_t * const p_api_ctrl)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(SAU_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort an in-progress transfer with this device only */
    r_sau_i2c_abort_seq_master(p_ctrl);

    /* Disable interrupts */
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    /* The device is now considered closed */
    p_ctrl->open = 0U;

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE
    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * @} (end defgroup SAU_I2C)
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
static fsp_err_t r_sau_i2c_read_write (i2c_master_ctrl_t * const p_api_ctrl,
                                       uint8_t * const           p_buffer,
                                       uint32_t const            bytes,
                                       sau_i2c_transfer_dir_t    direction)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_buffer != NULL);
    FSP_ERROR_RETURN((SAU_I2C_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
    FSP_ASSERT(((sau_i2c_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);
 #if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

    /* DTC on RX could actually receive 65535+3 = 65538 bytes as 3 bytes are handled separately.
     * Forcing to 65535 to keep TX and RX uniform with respect to max transaction length via DTC.
     */
    FSP_ERROR_RETURN((bytes <= UINT16_MAX), FSP_ERR_INVALID_SIZE);
 #endif
#endif

    p_ctrl->p_buff = p_buffer;
    p_ctrl->total  = bytes;

    /* Set the address bytes according to a 7-bit slave read command */
    p_ctrl->addr_low = (uint8_t) ((p_ctrl->slave << 1U) | (uint8_t) direction);

    p_ctrl->read = (bool) direction;

    /* Kickoff the read operation as a master */
    r_sau_i2c_run_hw_master(p_ctrl);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl      Pointer to transfer that is ending.
 * @param[in]       event       The event code to pass to the callback.
 **********************************************************************************************************************/
static void r_sau_i2c_notify (sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event)
{
    i2c_master_callback_args_t   args;
    i2c_master_callback_args_t * p_args = &args;

    p_args->p_context = p_ctrl->p_context;
    p_args->event     = event;

    /* Now do the callback here */
    p_ctrl->p_callback(p_args);
}

/******************************************************************************************************************//**
 * Single point for managing the logic around aborting a transfer when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to control struct of specific device
 **********************************************************************************************************************/
static void r_sau_i2c_abort_seq_master (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    r_sau_i2c_stop_prepare(p_ctrl);
#if !SAU_I2C_CFG_MANUAL_START_STOP_ENABLE

    /* Safely stop the hardware from operating */
    R_SAU_I2C_Stop(p_ctrl);
#endif

    /* Update the transfer descriptor to show no longer in-progress and an error */
    p_ctrl->remain    = 0U;
    p_ctrl->restarted = false;
    p_ctrl->restart   = false;

    /* Update the transfer descriptor to make sure interrupts no longer process */
    p_ctrl->loaded = p_ctrl->total;
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
static void r_sau_i2c_open_hw_master (sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    sau_i2c_extended_cfg_t * pextend = (sau_i2c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Refer flow diagram of master I2C initialization as described in hardware manual (see Figure 13 - 104
     * Initial Setting Procedure for Simplified I2C Address Field Transmission */

    /* Set this SAU channel to operate in simple I2C mode and selection of operation clock*/
    if (SAU_I2C_MASTER_OPERATION_CLOCK_CK0 == pextend->clock_settings.operation_clock)
    {
        SAU_REG->SPS &= R_SAU0_SPS_PRS1_Msk;
        SAU_REG->SPS |= pextend->clock_settings.clk_divisor_value;

        SAU_REG->SMR[p_ctrl->i2c_channel] = (0 << R_SAU0_SMR_CKS_Pos) | SAU_I2C_PRV_SMR_INIT;
    }
    else
    {
        SAU_REG->SPS &= R_SAU0_SPS_PRS0_Msk;
        SAU_REG->SPS |= (uint16_t) ((pextend->clock_settings.clk_divisor_value) << 4);

        SAU_REG->SMR[p_ctrl->i2c_channel] = (1 << R_SAU0_SMR_CKS_Pos) | SAU_I2C_PRV_SMR_INIT;
    }

    /* Set a communication format */
    SAU_REG->SCR[p_ctrl->i2c_channel] = SAU_I2C_PRV_SCR_REG_INIT;

    /* Set the bit rate register SDRmn(setting the transfer clock by dividing the operating clock (fMCK)) in the hardware */
    SAU_REG->SDR[p_ctrl->i2c_channel] = (uint16_t) (pextend->clock_settings.sdr_value << R_SAU0_SDR_STCLK_Pos);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif

    /* Set the initial output level (1) of the serial data (SOmn) and serial clock (CKOmn). */
    SAU_REG->SO |= (uint16_t) (SAU_I2C_PRV_SO0_REG_INIT << p_ctrl->i2c_channel);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif

    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->ipl, p_ctrl);
}

/******************************************************************************************************************//**
 * Performs the data transfer described by the parameters when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to Control structure of specific device.
 *
 * @retval   FSP_SUCCESS                     Data transferred when operating as a master.
 * @retval   FSP_ERR_ABORTED                 If there is an in-progress transfer.
 **********************************************************************************************************************/
static void r_sau_i2c_run_hw_master (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    uint16_t scr = SAU_REG->SCR[p_ctrl->i2c_channel];

    /* Initialize fields used during transfer */
    p_ctrl->loaded        = 0U;
    p_ctrl->remain        = p_ctrl->total;
    p_ctrl->do_dummy_read = false;

    /* In case of read operation the first ACK detected on the bus is from the slave after the address is sent.
     * Since we are reading on every ACK detection on the bus [in this case from this driver],
     * we skip the first read corresponding to the address.
     */
    if (true == p_ctrl->read)
    {
        p_ctrl->do_dummy_read = true;
    }

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE
    r_sau_i2c_reconfigure_interrupts_for_transfer(p_ctrl);
#endif

    /* Clear error flag */
    SAU_REG->SIR[p_ctrl->i2c_channel] = SAU_I2C_PRV_SIR_MASK;

    scr &= (uint8_t) (~R_SAU0_SCR_TRXE_Msk);
    scr |= SAU_I2C_PRV_SCR_TE_MASK;
    SAU_REG->SCR[p_ctrl->i2c_channel] = scr;
#if !SAU_I2C_CFG_MANUAL_START_STOP_ENABLE
    R_SAU_I2C_Start(p_ctrl);
#endif
}

/******************************************************************************************************************//**
 * Handles the STI interrupt8
 *
 *********************************************************************************************************************/
void sau_i2c_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type                 irq    = R_FSP_CurrentIrqGet();
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Call the handler */
    r_sau_i2c_tei_handler(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}

/******************************************************************************************************************//**
 * Handles the interrupt.
 *
 * @param[in]       p_ctrl     pointer to the I2C control block.
 **********************************************************************************************************************/
static void r_sau_i2c_tei_handler (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    /* As per the hardware manual, a byte should be written to SDR to generate SCL. */
    uint8_t  data   = g_dummy_write_data_for_read_op;
    uint16_t status = SAU_REG->SSR[p_ctrl->i2c_channel];

    /* NACK detected: process NACK reception */
    if (R_SAU0_SSR_PEF_Msk & status)
    {
        SAU_REG->SIR[p_ctrl->i2c_channel] &= (uint16_t) ~SAU_I2C_PRV_SIR_MASK;
        r_sau_i2c_stop_prepare(p_ctrl);
#if !SAU_I2C_CFG_MANUAL_START_STOP_ENABLE
        R_SAU_I2C_Stop(p_ctrl);
#endif
        r_sau_i2c_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);
        p_ctrl->remain = 0U;
    }

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

    /* This is the first interrupt after the completion of DTC operation, ignore it */
    else if (true == p_ctrl->activation_on_txi)
    {
        p_ctrl->activation_on_txi = false;

        return;
    }
#endif
    else if (!p_ctrl->read)
    {
        if (p_ctrl->remain > 0U)
        {
            data = p_ctrl->p_buff[p_ctrl->loaded];
            p_ctrl->remain--;
            p_ctrl->loaded++;
        }
        else
        {
            if (p_ctrl->restart)
            {
                p_ctrl->restarted = true;
            }
            else
            {
                r_sau_i2c_stop_prepare(p_ctrl);
#if !SAU_I2C_CFG_MANUAL_START_STOP_ENABLE
                R_SAU_I2C_Stop(p_ctrl);
#endif
            }

            r_sau_i2c_notify(p_ctrl, I2C_MASTER_EVENT_TX_COMPLETE);

            return;
        }
    }
    else
    {
        /* Skip updating the buffer on first interrupt as it is the ACK of address */
        if (true == p_ctrl->do_dummy_read)
        {
            p_ctrl->do_dummy_read = false;
            SAU_REG->SDR[p_ctrl->i2c_channel];
            SAU_REG->SCR[p_ctrl->i2c_channel] &= (uint16_t) ~R_SAU0_SCR_TRXE_Msk;
            SAU_REG->SCR[p_ctrl->i2c_channel] |= SAU_I2C_PRV_SCR_RE_MASK;
#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

            /* If transfer interface is available, use it.
             * Enable the transfer interfaces if the number of bytes to be read is greater than 2.
             * The last two bytes will be read through interrupt, this is for support NACK before STOP.
             */
            if ((NULL != p_ctrl->p_cfg->p_transfer_tx) && (p_ctrl->total > 2U))
            {
                const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
                p_transfer_tx->p_api->reconfigure(p_transfer_tx->p_ctrl, p_transfer_tx->p_cfg->p_info);

                /* Update the tracker variables */
                p_ctrl->remain = 2U;
                p_ctrl->loaded = p_ctrl->total - 2U;

                /* Mark DTC activation for TXI */
                p_ctrl->activation_on_txi = true;
            }
#endif
        }
        /* Read data into the buffer */
        else
        {
            if (p_ctrl->activation_on_txi == false)
            {
                p_ctrl->p_buff[p_ctrl->loaded] = (uint8_t) (SAU_REG->SDR_b[p_ctrl->i2c_channel].DAT);

                /* Update trackers */
                p_ctrl->remain--;
                p_ctrl->loaded++;
            }
        }

        if (p_ctrl->remain == 1)
        {
#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
            FSP_CRITICAL_SECTION_DEFINE;
            FSP_CRITICAL_SECTION_ENTER;
#endif

            SAU_REG->SOE &= (uint16_t) (~(1 << p_ctrl->i2c_channel));

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
            FSP_CRITICAL_SECTION_EXIT;
#endif
        }
        else if (p_ctrl->remain == 0)
        {
            if (p_ctrl->restart)
            {
                p_ctrl->restarted = true;
            }
            else
            {
                r_sau_i2c_stop_prepare(p_ctrl);
#if !SAU_I2C_CFG_MANUAL_START_STOP_ENABLE
                R_SAU_I2C_Stop(p_ctrl);
#endif
            }

            r_sau_i2c_notify(p_ctrl, I2C_MASTER_EVENT_RX_COMPLETE);

            return;
        }
        else
        {
            // do nothing
        }
    }

    SAU_REG->SDR_b[p_ctrl->i2c_channel].DAT = data;
}

/*******************************************************************************************************************//**
 * This function starts/restarts the IIC condition.
 *
 * @param[in]  p_ctrl         Instance control structure.
 **********************************************************************************************************************/
void R_SAU_I2C_Start (sau_i2c_instance_ctrl_t * const p_ctrl)
{
#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif

    if (p_ctrl->restarted)
    {
        /* Writing 1 to the STmn bit to stop operation */
        SAU_REG->ST |= (uint16_t) (1 << p_ctrl->i2c_channel);

        FSP_HARDWARE_REGISTER_WAIT(SAU_REG->SE_b.SE, 0);

        /* Disable IIC output */
        SAU_REG->SOE &= (uint16_t) ~(1 << p_ctrl->i2c_channel);

        /* Set IIC SCL */
        SAU_REG->SO |= (uint16_t) (SAU_I2C_SO_SCL_HIGH << p_ctrl->i2c_channel);

        p_ctrl->restarted = false;
    }

    /* Clear IIC SDA */
    SAU_REG->SO &= (uint16_t) ~(SAU_I2C_SO_SDA_HIGH << p_ctrl->i2c_channel);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif

    /* Set delay time before setting SCL, see to UM Table 20.109 */
    R_BSP_SoftwareDelay(p_ctrl->delay_time, BSP_DELAY_UNITS_MICROSECONDS);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_ENTER;
#endif

    /* Clear IIC SCL */
    SAU_REG->SO &= (uint16_t) ~(SAU_I2C_SO_SCL_HIGH << p_ctrl->i2c_channel);

    /* Enable IIC output */
    SAU_REG->SOE |= (uint16_t) (1 << p_ctrl->i2c_channel);

    /* Enable IIC */
    SAU_REG->SS |= (uint16_t) (1 << p_ctrl->i2c_channel);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif

    /* Write 1 byte data to data register */
    SAU_REG->SDR_b[p_ctrl->i2c_channel].DAT = p_ctrl->addr_low;
}

/*******************************************************************************************************************//**
 * This function prepares to stop the IIC condition.
 *
 * @param[in]  p_ctrl         Instance control structure.
 **********************************************************************************************************************/
static void r_sau_i2c_stop_prepare (sau_i2c_instance_ctrl_t * const p_ctrl)
{
#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif

    /* Writing 1 to the STmn bit to stop operation */
    SAU_REG->ST |= (uint16_t) (1 << p_ctrl->i2c_channel);

    FSP_HARDWARE_REGISTER_WAIT(SAU_REG->SE_b.SE, 0);

    /* Disable IIC output */
    SAU_REG->SOE &= (uint16_t) ~(1 << p_ctrl->i2c_channel);

    /* Clear IIC SDA */
    SAU_REG->SO &= (uint16_t) ~(SAU_I2C_SO_SDA_HIGH << p_ctrl->i2c_channel);

    /* Set IIC SCL */
    SAU_REG->SO |= (uint16_t) (SAU_I2C_SO_SCL_HIGH << p_ctrl->i2c_channel);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

/*******************************************************************************************************************//**
 * This function stops the IIC condition.
 *
 * @param[in]  p_ctrl         Instance control structure.
 **********************************************************************************************************************/
void R_SAU_I2C_Stop (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    /* Set delay time before setting SCL, see to UM Table 20.109 */
    R_BSP_SoftwareDelay(p_ctrl->delay_time, BSP_DELAY_UNITS_MICROSECONDS);
#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
#endif

    /* Set IIC SDA */
    SAU_REG->SO |= (uint16_t) (SAU_I2C_SO_SDA_HIGH << p_ctrl->i2c_channel);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Configures SAU I2C related transfer drivers (if enabled).
 *
 * @param[in]     p_ctrl   Pointer to SAU I2C specific control structure
 * @param[in]     p_cfg    Pointer to SAU I2C specific configuration structure
 *
 * @retval FSP_SUCCESS                 If configures SAU I2C related transfer drivers
 * @retval FSP_ERR_ASSERTION           Transfer configuration for tx/rx not proper.
 **********************************************************************************************************************/
static fsp_err_t r_sau_i2c_transfer_open (sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    if (NULL != p_cfg->p_transfer_tx)
    {
        err = r_sau_i2c_transfer_configure(p_ctrl, p_cfg->p_transfer_tx);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
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
static fsp_err_t r_sau_i2c_transfer_configure (sau_i2c_instance_ctrl_t * p_ctrl, transfer_instance_t const * p_transfer)
{
    fsp_err_t err;

    /* Set default transfer info and open receive transfer module, if enabled. */
 #if (SAU_I2C_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_transfer->p_api);
    FSP_ASSERT(NULL != p_transfer->p_ctrl);
    FSP_ASSERT(NULL != p_transfer->p_cfg);
 #endif
    transfer_info_t * p_info_rx = &(p_transfer->p_cfg->p_info[0]);
    transfer_info_t * p_info_tx = &(p_transfer->p_cfg->p_info[1]);
    p_info_rx->transfer_settings_word = SAU_I2C_PRV_DTC_RX_FOR_READ_TRANSFER_SETTINGS;
    p_info_rx->p_src = (void *) (&(SAU_REG->SDR[p_ctrl->i2c_channel]));
    p_info_tx->transfer_settings_word = SAU_I2C_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS;
    p_info_tx->p_dest                 = (void *) (&(SAU_REG->SDR[p_ctrl->i2c_channel]));
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
static void r_sau_i2c_reconfigure_interrupts_for_transfer (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    transfer_info_t * p_info    = &(p_transfer_tx->p_cfg->p_info[1]);
    transfer_info_t * p_info_rx = &(p_transfer_tx->p_cfg->p_info[0]);
    if (p_ctrl->read)
    {
        p_info_rx->p_dest              = (void *) (p_ctrl->p_buff);
        p_info_rx->length              = (uint16_t) (p_ctrl->total - 2);
        p_info->transfer_settings_word = SAU_I2C_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS;
        p_info->p_src  = (void *) &g_dummy_write_data_for_read_op;
        p_info->p_dest = (void *) (&(SAU_REG->SDR[p_ctrl->i2c_channel]));
        p_info->length = (uint16_t) (p_ctrl->total - 2);
    }
    else
    {
        p_info->p_src                  = (void *) (p_ctrl->p_buff);
        p_info->length                 = (uint16_t) (p_ctrl->remain);
        p_info->transfer_settings_word = SAU_I2C_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;
        p_ctrl->remain                 = 0U;
        p_ctrl->loaded                 = p_ctrl->total;
        p_transfer_tx->p_api->reconfigure(p_transfer_tx->p_ctrl, p_info);
        p_ctrl->activation_on_txi = true;
    }
}

#endif
