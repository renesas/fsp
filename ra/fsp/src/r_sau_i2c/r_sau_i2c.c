/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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

/* DTC transfer settings for TX descriptor when reading data (for dummy write)*/
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

/* DTC transfer settings for TX descriptor when writing data */
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
#define SAU_I2C_PRV_SAU0_SPS_REG_INIT                     ((BSP_CFG_SAU_CK01_DIV << R_SAU0_SPS_PRS1_Pos) | \
                                                           BSP_CFG_SAU_CK00_DIV)
#define SAU_I2C_PRV_SAU1_SPS_REG_INIT                     ((BSP_CFG_SAU_CK11_DIV << R_SAU0_SPS_PRS1_Pos) | \
                                                           BSP_CFG_SAU_CK10_DIV)
#define SAU_I2C_PRV_SCR_TE_MASK                           (0x8000U)
#define SAU_I2C_PRV_SCR_RE_MASK                           (0x4000U)

#define SAU_I2C_SO_SCL_HIGH                               (1 << R_SAU0_SO_CKO_Pos)
#define SAU_I2C_SO_SDA_HIGH                               (1 << R_SAU0_SO_SO_Pos)

#define SAU_I2C_PRV_SIR_MASK                              (R_SAU0_SIR_OVCT_Msk | R_SAU0_SIR_PECT_Msk | \
                                                           R_SAU0_SIR_FECT_Msk)

#if 0 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE /* Only IIC00 used (Unit 0 Channel 0) */
 #define SAU_I2C_PRV_CHANNEL                              (0)
 #define SAU_I2C_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_I2C_PRV_SPS_REG_INIT                         (SAU_I2C_PRV_SAU0_SPS_REG_INIT)
#elif 1 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE /* Only IIC01 used (Unit 0 Channel 1) */
 #define SAU_I2C_PRV_CHANNEL                              (1)
 #define SAU_I2C_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_I2C_PRV_SPS_REG_INIT                         (SAU_I2C_PRV_SAU0_SPS_REG_INIT)
#elif 10 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE /* Only IIC10 used (Unit 0 Channel 2) */
 #define SAU_I2C_PRV_CHANNEL                              (2)
 #define SAU_I2C_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_I2C_PRV_SPS_REG_INIT                         (SAU_I2C_PRV_SAU0_SPS_REG_INIT)
#elif 11 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE /* Only IIC11 used (Unit 0 Channel 3) */
 #define SAU_I2C_PRV_CHANNEL                              (3)
 #define SAU_I2C_PRV_UNIT                                 (0)
 #define SAU_REG                                          (R_SAU0)
 #define SAU_I2C_PRV_SPS_REG_INIT                         (SAU_I2C_PRV_SAU0_SPS_REG_INIT)
#elif 20 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE /* Only IIC20 used (Unit 1 Channel 0) */
 #define SAU_I2C_PRV_CHANNEL                              (0)
 #define SAU_I2C_PRV_UNIT                                 (1)
 #define SAU_REG                                          (R_SAU1)
 #define SAU_I2C_PRV_SPS_REG_INIT                         (SAU_I2C_PRV_SAU1_SPS_REG_INIT)
#elif 21 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE /* Only IIC21 used (Unit 1 Channel 1) */
 #define SAU_I2C_PRV_CHANNEL                              (1)
 #define SAU_I2C_PRV_UNIT                                 (1)
 #define SAU_REG                                          (R_SAU1)
 #define SAU_I2C_PRV_SPS_REG_INIT                         (SAU_I2C_PRV_SAU1_SPS_REG_INIT)
#endif

#if -1 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE /* Multiple IICxx instances used */
 #define SAU_REG                                          (p_ctrl->p_reg)
 #define SAU_I2C_PRV_UNIT                                 (p_extend->i2c_unit)
 #define SAU_I2C_PRV_CHANNEL_DECLARATION                  uint8_t i2c_channel = p_ctrl->p_cfg->channel
 #define SAU_I2C_PRV_CHANNEL                              (i2c_channel)
 #define SAU_I2C_PRV_SPS_REG_INIT                         (SAU_I2C_PRV_UNIT ? \
                                                           SAU_I2C_PRV_SAU1_SPS_REG_INIT : SAU_I2C_PRV_SAU0_SPS_REG_INIT)
#else
 #define SAU_I2C_PRV_CHANNEL_DECLARATION
#endif

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
 #define SAU_I2C_CRITICAL_SECTION_ENTER()    FSP_CRITICAL_SECTION_DEFINE; FSP_CRITICAL_SECTION_ENTER
 #define SAU_I2C_CRITICAL_SECTION_EXIT()     FSP_CRITICAL_SECTION_EXIT;
#else
 #define SAU_I2C_CRITICAL_SECTION_ENTER()
 #define SAU_I2C_CRITICAL_SECTION_EXIT()
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* I2C read/write enumeration */
typedef enum e_sau_i2c_transfer_dir
{
    SAU_I2C_TRANSFER_DIR_WRITE = 0x0,
    SAU_I2C_TRANSFER_DIR_READ  = 0x1
} sau_i2c_transfer_dir_t;

/**********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* Internal helper functions */
static void r_sau_i2c_transfer_complete(sau_i2c_instance_ctrl_t * const p_ctrl,
                                        bool                            is_nack,
                                        i2c_master_event_t const        event);
static void r_sau_i2c_abort_seq_master(sau_i2c_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sau_i2c_read_write(i2c_master_ctrl_t * const p_api_ctrl,
                                      uint8_t * const           p_buffer,
                                      uint32_t const            bytes,
                                      sau_i2c_transfer_dir_t    direction);

/* Functions that manipulate hardware */
static void r_sau_i2c_open_hw_master(sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_cfg_t const * const p_cfg);
static void r_sau_i2c_hw_stop(sau_i2c_instance_ctrl_t * const p_ctrl);

void sau_i2c_tei_isr(void);

static void r_sau_i2c_tei_handler(sau_i2c_instance_ctrl_t * const p_ctrl);
static bool r_sau_i2c_do_tx_rx(sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_event_t * const p_event);

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE
static fsp_err_t r_sau_i2c_transfer_open(sau_i2c_instance_ctrl_t * p_ctrl, i2c_master_cfg_t const * const p_cfg);
static fsp_err_t r_sau_i2c_transfer_configure(sau_i2c_instance_ctrl_t * p_ctrl, transfer_instance_t const * p_transfer);
static void      r_sau_i2c_reconfigure_dtc_for_transfer(sau_i2c_instance_ctrl_t * const p_ctrl);
static void      r_sau_i2c_dtc_transfer_enable(sau_i2c_instance_ctrl_t * const p_ctrl,
                                               transfer_info_t * const         p_info,
                                               uint16_t                        bytes_to_transfer);

#endif

/**********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

/* constant used as the source location for the DTC dummy write */
static const uint8_t g_dummy_write_data_for_read_op = SAU_I2C_PRV_DUMMY_WRITE_DATA_FOR_READ_OP;
#endif

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

#if -1 == SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE
    sau_i2c_extended_cfg_t const * const p_extend = (sau_i2c_extended_cfg_t *) p_cfg->p_extend;
    SAU_REG =
        (R_SAU0_Type *) ((uint32_t) R_SAU0_BASE +
                         (SAU_I2C_PRV_UNIT * ((uint32_t) R_SAU1_BASE - (uint32_t) R_SAU0_BASE)));
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
    fsp_err_t err = r_sau_i2c_transfer_open(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    R_BSP_MODULE_START(FSP_IP_SAU, SAU_I2C_PRV_UNIT);

    /* Open the hardware in master mode */
    r_sau_i2c_open_hw_master(p_ctrl, p_cfg);

    /* Exact value is don't-care, but loaded and total must have same initial value
     * to indicate that a transfer is not currently in progress */
    p_ctrl->loaded = p_ctrl->total;

#if SAU_I2C_CFG_RESTART_ENABLE
    p_ctrl->restarted = false;
    p_ctrl->restart   = false;
#endif
    p_ctrl->open = SAU_I2C_OPEN;

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
 * @retval  FSP_ERR_NOT_OPEN            Instance control block is not open.
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
#if SAU_I2C_CFG_RESTART_ENABLE

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of r_sau_i2c_read_write to 4. */
    ((sau_i2c_instance_ctrl_t *) p_api_ctrl)->restart = restart;
#else
    FSP_PARAMETER_NOT_USED(restart);
#endif

    /* Call the common helper function to perform I2C Read operation.*/
    fsp_err_t err = r_sau_i2c_read_write(p_api_ctrl, p_dest, bytes, SAU_I2C_TRANSFER_DIR_READ);

    return err;
}

/******************************************************************************************************************//**
 * Performs a write to the I2C device.
 *
 *  This function will fail if there is already an in-progress I2C transfer on the associated channel. Otherwise, the
 *  I2C write operation will begin.
 *  The write operation is non-blocking and the caller will be notified when the operation has finished by
 *  an I2C_EVENT_TX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS                 Function executed without issue.
 * @retval  FSP_ERR_ASSERTION           p_api_ctrl, p_src is NULL.
 * @retval  FSP_ERR_INVALID_SIZE        Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                      for data transfer.
 * @retval  FSP_ERR_NOT_OPEN            Instance control block is not open.
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_Write (i2c_master_ctrl_t * const p_api_ctrl,
                           uint8_t * const           p_src,
                           uint32_t const            bytes,
                           bool const                restart)
{
#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif
#if SAU_I2C_CFG_RESTART_ENABLE

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of r_sau_i2c_read_write to 4. */
    ((sau_i2c_instance_ctrl_t *) p_api_ctrl)->restart = restart;
#else
    FSP_PARAMETER_NOT_USED(restart);
#endif

    /* Call the common helper function to perform I2C Write operation.*/
    fsp_err_t err = r_sau_i2c_read_write(p_api_ctrl, p_src, bytes, SAU_I2C_TRANSFER_DIR_WRITE);

    return err;
}

/******************************************************************************************************************//**
 * Aborts any in-progress transfer and forces the I2C peripheral into a ready state.
 *
 *  This function will safely terminate any in-progress I2C transfer with the device. If a transfer is aborted, the user
 *  will be notified via callback with an abort event.
 *
 * @retval  FSP_SUCCESS                 Transaction was aborted without issue.
 * @retval  FSP_ERR_ASSERTION           p_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN            Instance control block is not open.
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
 * @retval  FSP_ERR_NOT_OPEN            Instance control block is not open.
 * @retval  FSP_ERR_IN_USE              An I2C Transaction is in progress.
 *
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_SlaveAddressSet (i2c_master_ctrl_t * const    p_api_ctrl,
                                     uint32_t const               slave,
                                     i2c_master_addr_mode_t const addr_mode)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if SAU_I2C_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(SAU_I2C_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN((p_ctrl->loaded == p_ctrl->total) && (false == p_ctrl->restart), FSP_ERR_IN_USE);

    /* Fail if the addr_mode is not 7-bit mode */
    FSP_ASSERT(I2C_MASTER_ADDR_MODE_7BIT == addr_mode);
#else
    FSP_PARAMETER_NOT_USED(addr_mode);
#endif

    /* Sets the address of the slave device */
    p_ctrl->slave = (uint8_t) slave;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback.
 *
 * @note p_callback_memory is not used in this implementation and can be set to NULL.
 *
 * Implements i2c_master_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_CallbackSet (i2c_master_ctrl_t * const          p_api_ctrl,
                                 void (                           * p_callback)(i2c_master_callback_args_t *),
                                 void * const                       p_context,
                                 i2c_master_callback_args_t * const p_callback_memory)
{
    sau_i2c_instance_ctrl_t * p_ctrl = (sau_i2c_instance_ctrl_t *) p_api_ctrl;

#if (SAU_I2C_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
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
 *  will be notified via callback with an abort event.
 *
 * @retval  FSP_SUCCESS                 Device closed without issue.
 * @retval  FSP_ERR_ASSERTION           The parameter p_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN            Instance control block is not open.
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
    i2c_master_cfg_t const * const p_cfg = p_ctrl->p_cfg;
    R_BSP_IrqDisable(p_cfg->tei_irq);

    /* The device is now considered closed */
    p_ctrl->open = 0U;

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE
    if (NULL != p_cfg->p_transfer_tx)
    {
        p_cfg->p_transfer_tx->p_api->close(p_cfg->p_transfer_tx->p_ctrl);
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

    /* Initialize fields used during transfer */
    p_ctrl->p_buff = p_buffer;
    p_ctrl->total  = bytes;
    p_ctrl->loaded = 0U;
    p_ctrl->read   = (bool) direction;

    /* In case of read operation the first ACK detected on the bus is from the slave after the address is sent.
     * Since we are reading on every ACK detection on the bus [in this case from this driver],
     * we skip the first read corresponding to the address. */
    p_ctrl->do_dummy_read = (bool) direction;

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE
    r_sau_i2c_reconfigure_dtc_for_transfer(p_ctrl);
#endif

    /* Clear error flag */
    R_SAU0_Type * p_reg = SAU_REG;
    SAU_I2C_PRV_CHANNEL_DECLARATION;
    p_reg->SIR[SAU_I2C_PRV_CHANNEL] = SAU_I2C_PRV_SIR_MASK;

    /* Set operation mode to transmission */
    uint16_t scr = p_reg->SCR[SAU_I2C_PRV_CHANNEL];
    p_reg->SCR[SAU_I2C_PRV_CHANNEL] = (scr & (uint16_t) (~R_SAU0_SCR_TRXE_Msk)) | SAU_I2C_PRV_SCR_TE_MASK;

#if !SAU_I2C_CFG_MANUAL_START_STOP_ENABLE
    (void) R_SAU_I2C_Start(p_ctrl);
#endif

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl      Pointer to transfer that is ending.
 * @param[in]       is_nack     True if the transmission completed due to NACK, false otherwise
 * @param[in]       event       The event code to pass to the callback.
 **********************************************************************************************************************/
static void r_sau_i2c_transfer_complete (sau_i2c_instance_ctrl_t * const p_ctrl,
                                         bool                            is_nack,
                                         i2c_master_event_t const        event)
{
#if SAU_I2C_CFG_RESTART_ENABLE

    /* Suppress stop if restart was requested, unless NACK response was received */
    if (p_ctrl->restart && !is_nack)
    {
        p_ctrl->restarted = true;
    }
    else
#else
    FSP_PARAMETER_NOT_USED(is_nack);
#endif
    {
        r_sau_i2c_hw_stop(p_ctrl);
    }

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
    r_sau_i2c_hw_stop(p_ctrl);

#if SAU_I2C_CFG_RESTART_ENABLE
    p_ctrl->restarted = false;
    p_ctrl->restart   = false;
#endif

    /* Update state to make sure interrupts no longer progress */
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
    R_SAU0_Type * p_reg = SAU_REG;
    sau_i2c_extended_cfg_t const * const   p_extend         = (sau_i2c_extended_cfg_t *) p_cfg->p_extend;
    sau_i2c_clock_settings_t const * const p_clock_settings = &p_extend->clock_settings;

    /* See in hardware manual: SAU > Table "Initial Setting Procedure for Simplified I2C Address Field Transmission" */

    /* Configure the operation clock divisor based on BSP settings */
    p_reg->SPS = SAU_I2C_PRV_SPS_REG_INIT;

    /* Configure the SAU channel in Simple I2C mode */
    SAU_I2C_PRV_CHANNEL_DECLARATION;
    p_reg->SMR[SAU_I2C_PRV_CHANNEL] =
        ((uint16_t) (p_clock_settings->operation_clock << R_SAU0_SMR_CKS_Pos) | SAU_I2C_PRV_SMR_INIT);

    /* Set a communication format */
    p_reg->SCR[SAU_I2C_PRV_CHANNEL] = SAU_I2C_PRV_SCR_REG_INIT;

    /* Set the bit rate register SDRmn(setting the transfer clock by dividing the operating clock (fMCK)) in the hardware */
    p_reg->SDR[SAU_I2C_PRV_CHANNEL] = (uint16_t) (p_clock_settings->stclk << R_SAU0_SDR_STCLK_Pos);

    SAU_I2C_CRITICAL_SECTION_ENTER();

    /* Set the initial output level (1) of the serial data (SOmn) and serial clock (CKOmn). */
    p_reg->SO |= (uint16_t) (SAU_I2C_PRV_SO0_REG_INIT << SAU_I2C_PRV_CHANNEL);

    SAU_I2C_CRITICAL_SECTION_EXIT();

    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->ipl, p_ctrl);
}

/******************************************************************************************************************//**
 * Handles the STI interrupt
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
 * Handles transmission or reception of the I2C data
 *
 * @note Called from ISR context
 *
 * @param[in]       p_ctrl   Pointer to transfer control block
 * @param[in]       p_event  Pointer to transfer completion event code. Valid only if return value from this function is 1,
 *                           indicating transfer completed successfully.
 *
 * @returns        1 if the transfer has completed, 0 otherwise
 *********************************************************************************************************************/
static bool r_sau_i2c_do_tx_rx (sau_i2c_instance_ctrl_t * const p_ctrl, i2c_master_event_t * const p_event)
{
    R_SAU0_Type * p_reg = SAU_REG;
    SAU_I2C_PRV_CHANNEL_DECLARATION;
    uint8_t   data  = SAU_I2C_PRV_DUMMY_WRITE_DATA_FOR_READ_OP;
    bool      is_rx = p_ctrl->read;
    bool      transfer_complete;
    uint8_t * p_buff = &p_ctrl->p_buff[p_ctrl->loaded];

    if (!is_rx && (p_ctrl->loaded < p_ctrl->total))
    {
        /* Write the next data to SDR */
        data = *p_buff;
        p_ctrl->loaded++;
        transfer_complete = false;
    }
    else if (is_rx)
    {
        if (p_ctrl->do_dummy_read)
        {
            p_ctrl->do_dummy_read = false;

            /* Set operation mode to reception. It is not necessary to actually read SDR to do a dummy
             * read because we were previously in transmission mode to send the slave address. */
            uint16_t scr = p_reg->SCR[SAU_I2C_PRV_CHANNEL];
            p_reg->SCR[SAU_I2C_PRV_CHANNEL] = (scr & (uint16_t) ~R_SAU0_SCR_TRXE_Msk) | SAU_I2C_PRV_SCR_RE_MASK;

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

            /* If transfer interface is available, use it.
             * Enable the transfer interfaces if the number of bytes to be read is greater than 2.
             * The last two bytes will be read through interrupt, this is for support NACK before STOP.
             */
            const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
            if ((NULL != p_transfer_tx) && (p_ctrl->total > 2U))
            {
                r_sau_i2c_dtc_transfer_enable(p_ctrl, p_transfer_tx->p_cfg->p_info, (uint16_t) (p_ctrl->total - 2U));
            }
#endif
        }
        else
        {
            /* Read the received data into the buffer */
            *p_buff = (uint8_t) (p_reg->SDR_b[SAU_I2C_PRV_CHANNEL].DAT);
            p_ctrl->loaded++;
        }

        /* Check if the next byte will be the last byte */
        if ((p_ctrl->loaded + 1) == p_ctrl->total)
        {
            SAU_I2C_CRITICAL_SECTION_ENTER();

            /* During a receive  operation, the SOE[n] bit of serial output enable register m (SOEm) is cleared to 0
             * before receiving the last data. Refer to hardware manual: SAU > Operation of Simplified I2C >
             * Figure "Timing of stop condition generation" */
            p_reg->SOE &= (uint16_t) ~(1 << SAU_I2C_PRV_CHANNEL);

            SAU_I2C_CRITICAL_SECTION_EXIT();
        }

        /* Update transfer complete after updating state since a read is complete
         * after the last byte is loaded into the buffer (unlike a write, which
         * is not complete until the ISR after the last byte is written to ISR) */
        transfer_complete = p_ctrl->loaded == p_ctrl->total;
        *p_event          = I2C_MASTER_EVENT_RX_COMPLETE;
    }
    else
    {
        /* TX completion event */
        transfer_complete = true;
        *p_event          = I2C_MASTER_EVENT_TX_COMPLETE;
    }

    if (!transfer_complete)
    {
        /* A dummy byte should be written to SDR to generate SCL during reception.
         * Refer to hardware manual: SAU > Operation of Simplified I2C > Table "Procedure for data reception" */
        p_reg->SDR_b[SAU_I2C_PRV_CHANNEL].DAT = data;
    }

    return transfer_complete;
}

/******************************************************************************************************************//**
 * Handles the interrupt.
 *
 * @param[in]       p_ctrl     pointer to the I2C control block.
 **********************************************************************************************************************/
static void r_sau_i2c_tei_handler (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    R_SAU0_Type * p_reg = SAU_REG;
    SAU_I2C_PRV_CHANNEL_DECLARATION;
    i2c_master_event_t event;
    bool               is_nack = false;

    uint16_t status = p_reg->SSR[SAU_I2C_PRV_CHANNEL];

    /* Check if NACK was detected */
    if (R_SAU0_SSR_PEF_Msk & status)
    {
        /* Handle NACK */
        p_reg->SIR[SAU_I2C_PRV_CHANNEL] &= (uint16_t) ~SAU_I2C_PRV_SIR_MASK;

        event   = I2C_MASTER_EVENT_ABORTED;
        is_nack = true;

        /* Update internal state to reflect transfer complete */
        p_ctrl->loaded = p_ctrl->total;
    }

#if SAU_I2C_CFG_DTC_SUPPORT_ENABLE

    /* This is the first interrupt after the completion of DTC operation, ignore it */
    else if (p_ctrl->activation_on_txi)
    {
        p_ctrl->activation_on_txi = false;

        return;
    }
#endif
    else
    {
        bool transfer_complete = r_sau_i2c_do_tx_rx(p_ctrl, &event);

        if (!transfer_complete)
        {

            /* Transfer still in-progress */
            return;
        }
    }

    /* If we didn't return early (due to transfer still in progress), finish
     * the transfer and notify the user of transfer completion */
    r_sau_i2c_transfer_complete(p_ctrl, is_nack, event);
}

/*******************************************************************************************************************//**
 * This function starts/restarts the IIC condition.
 *
 * @param[in]  p_ctrl         Instance control structure.
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_Start (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    SAU_I2C_CRITICAL_SECTION_ENTER();
    R_SAU0_Type * p_reg = SAU_REG;
    SAU_I2C_PRV_CHANNEL_DECLARATION;

#if SAU_I2C_CFG_RESTART_ENABLE
    if (p_ctrl->restarted)
    {
        /* Writing 1 to the STmn bit to stop operation */
        p_reg->ST = (uint16_t) (1 << SAU_I2C_PRV_CHANNEL);

        /* Disable IIC output */
        p_reg->SOE &= (uint16_t) ~(1 << SAU_I2C_PRV_CHANNEL);

        /* Set IIC SCL */
        p_reg->SO |= (uint16_t) (SAU_I2C_SO_SCL_HIGH << SAU_I2C_PRV_CHANNEL);

        p_ctrl->restarted = false;
    }
#endif

    /* Clear IIC SDA */
    p_reg->SO &= (uint16_t) ~(SAU_I2C_SO_SDA_HIGH << SAU_I2C_PRV_CHANNEL);

    SAU_I2C_CRITICAL_SECTION_EXIT();

    /* Set delay time before setting SCL. Refer to hardware manual: SAU > Operation of Simplified I2C >
     * Table "Procedure for simplified I2C address field transmission" */
    sau_i2c_extended_cfg_t const * const p_extend = (sau_i2c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    R_BSP_SoftwareDelay(p_extend->delay_time, BSP_DELAY_UNITS_MICROSECONDS);

#if SAU_I2C_CFG_CRITICAL_SECTION_ENABLE
    FSP_CRITICAL_SECTION_ENTER;
#endif

    /* Clear IIC SCL */
    p_reg->SO &= (uint16_t) ~(SAU_I2C_SO_SCL_HIGH << SAU_I2C_PRV_CHANNEL);

    /* Enable IIC output */
    p_reg->SOE |= (1 << SAU_I2C_PRV_CHANNEL);

    /* Enable IIC */
    p_reg->SS |= (1 << SAU_I2C_PRV_CHANNEL);

    SAU_I2C_CRITICAL_SECTION_EXIT();

    /* Set the address byte according to a 7-bit slave address */
    uint8_t slave_address = (uint8_t) ((p_ctrl->slave << 1U) | (uint8_t) p_ctrl->read);

    /* Write slave address to data register to start the transfer */
    p_reg->SDR_b[SAU_I2C_PRV_CHANNEL].DAT = slave_address;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function generates the I2C stop condition
 *
 * @param[in]  p_ctrl         Instance control structure.
 **********************************************************************************************************************/
static void r_sau_i2c_hw_stop (sau_i2c_instance_ctrl_t * const p_ctrl)
{
#if -1 != SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    R_SAU0_Type * p_reg = SAU_REG;
    SAU_I2C_PRV_CHANNEL_DECLARATION;

    SAU_I2C_CRITICAL_SECTION_ENTER();

    /* See in hardware manual:  SAU > Operation of Simplified I2C > Table "Procedure for stop condition generation" */

    /* Writing 1 to the STmn bit to stop operation */
    p_reg->ST = (uint16_t) (1 << SAU_I2C_PRV_CHANNEL);

    /* Disable IIC output */
    p_reg->SOE &= (uint16_t) ~(1 << SAU_I2C_PRV_CHANNEL);

    /* Clear SDA and set SCL */
    p_reg->SO &= (uint16_t) ~(SAU_I2C_SO_SDA_HIGH << SAU_I2C_PRV_CHANNEL);

    p_reg->SO |= (uint16_t) (SAU_I2C_SO_SCL_HIGH << SAU_I2C_PRV_CHANNEL);

    SAU_I2C_CRITICAL_SECTION_EXIT();

#if !SAU_I2C_CFG_MANUAL_START_STOP_ENABLE

    /* Delay the required wait time, then release SDA to send the I2C
     * stop condition, unless manual start/stop is enabled. */
    (void) R_SAU_I2C_Stop(p_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * This function stops the IIC condition.
 *
 * @param[in]  p_ctrl         Instance control structure.
 **********************************************************************************************************************/
fsp_err_t R_SAU_I2C_Stop (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    /* Set delay time before setting SCL
     * See in hardware manual:  SAU > Operation of Simplified I2C > Table "Procedure for stop condition generation" */
    sau_i2c_extended_cfg_t const * const p_extend = (sau_i2c_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    R_BSP_SoftwareDelay(p_extend->delay_time, BSP_DELAY_UNITS_MICROSECONDS);

    R_SAU0_Type * p_reg = SAU_REG;
    SAU_I2C_PRV_CHANNEL_DECLARATION;

    SAU_I2C_CRITICAL_SECTION_ENTER();

    /* Set IIC SDA */
    p_reg->SO |= (uint16_t) (SAU_I2C_SO_SDA_HIGH << SAU_I2C_PRV_CHANNEL);

    SAU_I2C_CRITICAL_SECTION_EXIT();

    return FSP_SUCCESS;
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
    if (NULL != p_cfg->p_transfer_tx)
    {
        fsp_err_t err = r_sau_i2c_transfer_configure(p_ctrl, p_cfg->p_transfer_tx);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures  DTC
 * @param[in]     p_ctrl                     Pointer to I2C specific control structure
 * @param[in]     p_transfer                 Pointer to DTC instance structure
 *
 * @retval        FSP_SUCCESS                Transfer interface opened successfully
 * @retval        FSP_ERR_ASSERTION          Transfer instance not correctly initialized (NULL pointer)
 **********************************************************************************************************************/
static fsp_err_t r_sau_i2c_transfer_configure (sau_i2c_instance_ctrl_t * p_ctrl, transfer_instance_t const * p_transfer)
{
 #if -1 != SAU_I2C_CFG_SINGLE_CHANNEL_ENABLE
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Set default transfer info and open receive transfer module, if enabled. */
 #if (SAU_I2C_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_transfer->p_api);
    FSP_ASSERT(NULL != p_transfer->p_ctrl);
    FSP_ASSERT(NULL != p_transfer->p_cfg);
 #endif
    R_SAU0_Type * p_reg = SAU_REG;
    SAU_I2C_PRV_CHANNEL_DECLARATION;
    void * sdr = (void *) &p_reg->SDR[SAU_I2C_PRV_CHANNEL];

    /* Runtime initialization for the first transfer info in the chain transfer info list */
    transfer_info_t * p_info_rx = p_transfer->p_cfg->p_info;
    p_info_rx->p_src = sdr;

    /* Runtime initialization for the second transfer info in the chain transfer info list */
    transfer_info_t * p_info_tx = p_info_rx + 1;
    p_info_tx->p_dest = sdr;

    fsp_err_t err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Starts the DTC transfer
 *
 * @param[in]  p_ctrl     Transfer control block
 * @param[in]  p_info     Pointer to transfer info to start
 * @param      loaded     Count of data bytes already transferred
 **********************************************************************************************************************/
static void r_sau_i2c_dtc_transfer_enable (sau_i2c_instance_ctrl_t * const p_ctrl,
                                           transfer_info_t * const         p_info,
                                           uint16_t                        bytes_to_transfer)
{
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;

    /* Update the tracker variables */
    p_ctrl->loaded = bytes_to_transfer;

    /* Start the transfer (reconfigure can be used to enable transfers since p_info is valid) */
    p_transfer_tx->p_api->reconfigure(p_transfer_tx->p_ctrl, p_info);

    /* Mark DTC activation for TXI */
    p_ctrl->activation_on_txi = true;
}

/******************************************************************************************************************//**
 * Reconfigures the DTC for the current transfer (read or write)
 *
 * @param[in]  p_ctrl     transfer control block
 **********************************************************************************************************************/
static void r_sau_i2c_reconfigure_dtc_for_transfer (sau_i2c_instance_ctrl_t * const p_ctrl)
{
    const transfer_instance_t * p_transfer_tx = p_ctrl->p_cfg->p_transfer_tx;
    if (NULL != p_transfer_tx)
    {
        transfer_info_t * p_info_tx       = &(p_transfer_tx->p_cfg->p_info[1]);
        uint16_t          transfer_length = (uint16_t) p_ctrl->total;

        if (p_ctrl->read)
        {
            transfer_info_t * p_info_rx = &(p_transfer_tx->p_cfg->p_info[0]);
            transfer_length -= 2;      // Last 2B received handled in ISR

            /* Update the rx transfer descriptor for reading data from SDR into the buffer
             * The transfer will be enabled from interrupt context after sending the address. */
            p_info_rx->p_dest = (void *) (p_ctrl->p_buff);
            p_info_rx->length = transfer_length;

            /* Update the tx transfer descriptor for the dummy write */
            p_info_tx->p_src                  = (void *) &g_dummy_write_data_for_read_op;
            p_info_tx->length                 = transfer_length;
            p_info_tx->transfer_settings_word = SAU_I2C_PRV_DTC_TX_FOR_READ_TRANSFER_SETTINGS;
        }
        else
        {
            /* Update the tx transfer descriptor for writing data from the buffer to SDR */
            p_info_tx->p_src                  = (void *) (p_ctrl->p_buff);
            p_info_tx->length                 = transfer_length;
            p_info_tx->transfer_settings_word = SAU_I2C_PRV_DTC_TX_FOR_WRITE_TRANSFER_SETTINGS;

            /* Enable the write transfer */
            r_sau_i2c_dtc_transfer_enable(p_ctrl, p_info_tx, transfer_length);
        }
    }
}

#endif
