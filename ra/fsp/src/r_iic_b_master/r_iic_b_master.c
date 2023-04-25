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
#include "r_iic_b_master.h"
#if IIC_B_MASTER_CFG_DTC_ENABLE
 #include "r_dtc.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "IICB" in ASCII, used to determine if channel is open. */
#define IIC_B_MASTER_OPEN                             (0x49494342U)
#define I2C_CODE_READ                                 (0x01U)
#define I2C_CODE_10BIT                                (0xF0U)
#define IIC_B_MASTER_BUS_RATE_REG_RESERVED_BITS       (0xE0U)
#define IIC_B_MASTER_INTERNAL_REF_CLOCK_SELECT_MAX    (0x07U)

#define IIC_B_MASTER_SLAVE_10_BIT_ADDR_LEN_ADJUST     (2U)

#define IIC_B_MASTER_DTC_RX_TRANSFER_SETTINGS         ((TRANSFER_MODE_NORMAL <<                           \
                                                        TRANSFER_SETTINGS_MODE_BITS) |                    \
                                                       (TRANSFER_SIZE_1_BYTE <<                           \
                                                        TRANSFER_SETTINGS_SIZE_BITS) |                    \
                                                       (TRANSFER_ADDR_MODE_FIXED <<                       \
                                                        TRANSFER_SETTINGS_SRC_ADDR_BITS) |                \
                                                       (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) | \
                                                       (TRANSFER_ADDR_MODE_INCREMENTED <<                 \
                                                        TRANSFER_SETTINGS_DEST_ADDR_BITS))
#define IIC_B_MASTER_DTC_TX_TRANSFER_SETTINGS         ((TRANSFER_MODE_NORMAL <<                           \
                                                        TRANSFER_SETTINGS_MODE_BITS) |                    \
                                                       (TRANSFER_SIZE_1_BYTE <<                           \
                                                        TRANSFER_SETTINGS_SIZE_BITS) |                    \
                                                       (TRANSFER_ADDR_MODE_INCREMENTED <<                 \
                                                        TRANSFER_SETTINGS_SRC_ADDR_BITS) |                \
                                                       (TRANSFER_IRQ_END << TRANSFER_SETTINGS_IRQ_BITS) | \
                                                       (TRANSFER_ADDR_MODE_FIXED <<                       \
                                                        TRANSFER_SETTINGS_DEST_ADDR_BITS))

#define IIC_B_MASTER_PRV_BIE_INIT_MASK                (R_I3C0_BIE_NACKDIE_Msk | R_I3C0_BIE_ALIE_Msk | \
                                                       R_I3C0_BIE_TODIE_Msk)
#define IIC_B_MASTER_PRV_BSTE_INIT_MASK               (R_I3C0_BSTE_NACKDE_Msk | R_I3C0_BSTE_TENDE_Msk | \
                                                       R_I3C0_BSTE_ALE_Msk |                            \
                                                       R_I3C0_BSTE_TODE_Msk)
#define IIC_B_MASTER_PRV_NTIE_INIT_MASK               (R_I3C0_NTIE_TDBEIE0_Msk | R_I3C0_NTIE_RDBFIE0_Msk)
#define IIC_B_MASTER_PRV_NTSTE_INIT_MASK              (R_I3C0_NTSTE_TDBEE0_Msk | R_I3C0_NTSTE_RDBFE0_Msk)

#define IIC_B_MASTER_PRV_BST_ERR_STATUS_MASK          (R_I3C0_BST_STCNDDF_Msk | R_I3C0_BST_SPCNDDF_Msk | \
                                                       R_I3C0_BST_NACKDF_Msk |                           \
                                                       R_I3C0_BST_ALF_Msk | R_I3C0_BST_TODF_Msk)

#define IIC_B_MASTER_BFRECDT_FASTPLUS_DELAY_CONST     (120U)
#define IIC_B_MASTER_BFRECDT_DELAY_CONST              (300U)
#define IIC_B_MASTER_BILLION                          (1000000000U)
#define IIC_B_MASTER_ROUNDING_OFF_COMP                (1U)

/* Worst case ratio of ICLK/PCLKB (RA2E2) or ICLK/PCLKA (RA6T2) = 64 approximately.
 * 3 PCLKB cycles is the number of cycles to wait for IICn.
 * Refer "Table 3.2 Access cycles for non-GPT modules (1 of 2)" of the RA2E2 manual R01UH0919EJ0050)
 */
#define IIC_B_MASTER_PERIPHERAL_REG_MAX_WAIT          (0x40U * 0x03U)

#define IIC_B_MASTER_HARDWARE_REGISTER_WAIT(reg, required_value, timeout) \
    while ((timeout))                                                     \
    {                                                                     \
        if ((required_value) == (reg))                                    \
        {                                                                 \
            break;                                                        \
        }                                                                 \
        (timeout)--;                                                      \
    }

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* IIC read/write enumeration */
typedef enum e_iic_b_master_transfer_dir_option
{
    IIC_B_MASTER_TRANSFER_DIR_WRITE = 0x0,
    IIC_B_MASTER_TRANSFER_DIR_READ  = 0x1
} iic_b_master_transfer_dir_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * iic_b_master_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile iic_b_master_prv_ns_callback)(i2c_master_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

void iic_b_master_rxi_isr(void);
void iic_b_master_txi_isr(void);
void iic_b_master_tei_isr(void);
void iic_b_master_eri_isr(void);

/* Internal helper functions */
static void      iic_b_master_abort_seq_master(iic_b_master_instance_ctrl_t * const p_ctrl, bool iic_reset);
static fsp_err_t iic_b_master_read_write(i2c_master_ctrl_t * const   p_api_ctrl,
                                         uint8_t * const             p_buffer,
                                         uint32_t const              bytes,
                                         iic_b_master_transfer_dir_t direction);
static void iic_b_master_notify(iic_b_master_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event);

#if IIC_B_MASTER_CFG_DTC_ENABLE
static fsp_err_t iic_b_master_transfer_open(i2c_master_cfg_t const * const p_cfg);
static fsp_err_t iic_b_master_transfer_configure(transfer_instance_t const * p_transfer,
                                                 iic_b_master_transfer_dir_t direction);

#endif

/* Interrupt handlers */
static void iic_b_master_rxi_master(iic_b_master_instance_ctrl_t * p_ctrl);
static void iic_b_master_txi_master(iic_b_master_instance_ctrl_t * p_ctrl);
static void iic_b_master_tei_master(iic_b_master_instance_ctrl_t * p_ctrl);
static void iic_b_master_err_master(iic_b_master_instance_ctrl_t * p_ctrl);

/* Functions that manipulate hardware */
static void iic_b_master_open_hw_master(iic_b_master_instance_ctrl_t * const p_ctrl,
                                        i2c_master_cfg_t const * const       p_cfg);
static fsp_err_t iic_b_master_run_hw_master(iic_b_master_instance_ctrl_t * const p_ctrl);
static void      iic_b_master_rxi_read_data(iic_b_master_instance_ctrl_t * const p_ctrl);
static void      iic_b_master_txi_send_address(iic_b_master_instance_ctrl_t * const p_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* IIC Implementation of I2C device master interface */
i2c_master_api_t const g_i2c_master_on_iic_b =
{
    .open            = R_IIC_B_MASTER_Open,
    .read            = R_IIC_B_MASTER_Read,
    .write           = R_IIC_B_MASTER_Write,
    .abort           = R_IIC_B_MASTER_Abort,
    .slaveAddressSet = R_IIC_B_MASTER_SlaveAddressSet,
    .close           = R_IIC_B_MASTER_Close,
    .statusGet       = R_IIC_B_MASTER_StatusGet,
    .callbackSet     = R_IIC_B_MASTER_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup IIC_B_MASTER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the I2C device.
 *
 * @retval  FSP_SUCCESS                       Requested clock rate was set exactly.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT    Channel is not available on this MCU.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 *                                            4. Set the rate to fast mode plus on a channel which does not support it.
 *                                            5. Invalid IRQ number assigned
 **********************************************************************************************************************/
fsp_err_t R_IIC_B_MASTER_Open (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) p_api_ctrl;
#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT(p_cfg->rxi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->txi_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);
    FSP_ASSERT(p_cfg->eri_irq >= (IRQn_Type) 0);
    FSP_ERROR_RETURN(IIC_B_MASTER_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    FSP_ERROR_RETURN(BSP_FEATURE_IIC_B_VALID_CHANNEL_MASK & (1 << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* If rate is configured as Fast mode plus, check whether the channel supports it */
    if (I2C_MASTER_RATE_FASTPLUS == p_cfg->rate)
    {
        FSP_ASSERT((BSP_FEATURE_IIC_B_FAST_MODE_PLUS & (1U << p_cfg->channel)));
    }
#endif
#if IIC_B_MASTER_CFG_DTC_ENABLE
    fsp_err_t err = FSP_SUCCESS;
#endif

#if (BSP_FEATURE_IIC_B_VALID_CHANNEL_MASK > 1U)
    p_ctrl->p_reg =
        (R_I3C0_Type *) ((uint32_t) R_I3C0 + (p_cfg->channel * ((uint32_t) R_I3C1 - (uint32_t) R_I3C0)));
#else
    p_ctrl->p_reg = R_I3C0;
#endif

    /* Record the pointer to the configuration structure for later use */
    p_ctrl->p_cfg             = p_cfg;
    p_ctrl->slave             = p_cfg->slave;
    p_ctrl->addr_mode         = p_cfg->addr_mode;
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

#if (1 == BSP_FEATURE_BSP_HAS_I3C_CLOCK)
    R_BSP_MODULE_START(FSP_IP_I3C, p_cfg->channel);
#else
    R_BSP_MODULE_START(FSP_IP_IIC, p_cfg->channel);
#endif

    /* Open the hardware in master mode. Performs IIC initialization as described in hardware manual (see Section 27.3.2.1
     * 'Initial Settings' of the RA6T2 manual R01UH0951EJ0050). */
    iic_b_master_open_hw_master(p_ctrl, p_cfg);

#if IIC_B_MASTER_CFG_DTC_ENABLE

    /* Open the IIC transfer interface if available */
    err = iic_b_master_transfer_open(p_cfg);
    if (FSP_SUCCESS != err)
    {
        R_BSP_MODULE_STOP(FSP_IP_IIC, p_cfg->channel);

        return err;
    }
#endif

    p_ctrl->p_buff    = NULL;
    p_ctrl->total     = 0U;
    p_ctrl->remain    = 0U;
    p_ctrl->loaded    = 0U;
    p_ctrl->read      = false;
    p_ctrl->restart   = false;
    p_ctrl->err       = false;
    p_ctrl->restarted = false;
    p_ctrl->open      = IIC_B_MASTER_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Performs a read from the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_RX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS             Function executed without issue.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl, p_dest or bytes is NULL.
 * @retval  FSP_ERR_INVALID_SIZE    Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                  for data transfer.
 * @retval  FSP_ERR_IN_USE          Bus busy condition. Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IIC_B_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IIC_B_MASTER_Read (i2c_master_ctrl_t * const p_api_ctrl,
                               uint8_t * const           p_dest,
                               uint32_t const            bytes,
                               bool const                restart)
{
#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(bytes != 0U);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_b_master_read_write to 4. */
    ((iic_b_master_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Read operation.*/
    err = iic_b_master_read_write(p_api_ctrl, p_dest, bytes, IIC_B_MASTER_TRANSFER_DIR_READ);

    return err;
}

/*******************************************************************************************************************//**
 * Performs a write to the I2C device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_TX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS           Function executed without issue.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_src is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than uint16_t size (65535) while DTC is used
 *                                for data transfer.
 * @retval  FSP_ERR_IN_USE        Bus busy condition. Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_IIC_B_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IIC_B_MASTER_Write (i2c_master_ctrl_t * const p_api_ctrl,
                                uint8_t * const           p_src,
                                uint32_t const            bytes,
                                bool const                restart)
{
#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of iic_b_master_read_write to 4. */
    ((iic_b_master_instance_ctrl_t *) p_api_ctrl)->restart = restart;

    /* Call the common helper function to perform I2C Write operation.*/
    err = iic_b_master_read_write(p_api_ctrl, p_src, bytes, IIC_B_MASTER_TRANSFER_DIR_WRITE);

    return err;
}

/*******************************************************************************************************************//**
 * Safely aborts any in-progress transfer and forces the IIC peripheral into ready state.
 *
 *
 * @retval  FSP_SUCCESS             Channel was reset successfully.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IIC_B_MASTER_Open to initialize the control block.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 **********************************************************************************************************************/
fsp_err_t R_IIC_B_MASTER_Abort (i2c_master_ctrl_t * const p_api_ctrl)
{
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IIC_B_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort any transfer happening on the channel */
    iic_b_master_abort_seq_master(p_ctrl, true);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets address and addressing mode of the slave device.
 * This function is used to set the device address and addressing mode of the slave
 * without reconfiguring the entire bus.
 *
 * @retval  FSP_SUCCESS             Address of the slave is set correctly.
 * @retval  FSP_ERR_ASSERTION       Pointer to control structure is NULL.
 * @retval  FSP_ERR_IN_USE          Another transfer was in-progress.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IIC_B_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IIC_B_MASTER_SlaveAddressSet (i2c_master_ctrl_t * const    p_api_ctrl,
                                          uint32_t const               slave,
                                          i2c_master_addr_mode_t const addr_mode)
{
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IIC_B_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN(((0 == p_ctrl->remain) && (false == p_ctrl->restart)), FSP_ERR_IN_USE);
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
fsp_err_t R_IIC_B_MASTER_CallbackSet (i2c_master_ctrl_t * const          p_api_ctrl,
                                      void (                           * p_callback)(i2c_master_callback_args_t *),
                                      void const * const                 p_context,
                                      i2c_master_callback_args_t * const p_callback_memory)
{
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) p_api_ctrl;

#if (IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(IIC_B_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE

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
fsp_err_t R_IIC_B_MASTER_StatusGet (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status)
{
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_status != NULL);
#endif

    p_status->open = (IIC_B_MASTER_OPEN == p_ctrl->open);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the I2C device. May power down IIC peripheral.
 * This function will safely terminate any in-progress I2C transfers.
 *
 * @retval  FSP_SUCCESS         Device closed without issue.
 * @retval  FSP_ERR_ASSERTION   p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN    Handle is not initialized.  Call R_IIC_B_MASTER_Open to initialize the control block.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 **********************************************************************************************************************/
fsp_err_t R_IIC_B_MASTER_Close (i2c_master_ctrl_t * const p_api_ctrl)
{
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IIC_B_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable I2C interrupts. */
    p_ctrl->p_reg->BIE  = 0x00;
    p_ctrl->p_reg->NTIE = 0x00;

    /* Clear BCTL.BUSE to 0: SCL, SDA pins not driven */
    p_ctrl->p_reg->BCTL = 0;

    /* Abort an in-progress transfer with this device only
     * Set RSTCTL.RI2CRST to 1: Reset all registers and internal state; RSTCTL.INTLRST is already 0.
     */
    p_ctrl->p_reg->RSTCTL = (uint32_t) (R_I3C0_RSTCTL_RI3CRST_Msk);

    /* Waiting for reset completion RSTCTL.RI2CRST = 0;  RSTCTL.INTLRST is already 0. */
    FSP_HARDWARE_REGISTER_WAIT(0U, p_ctrl->p_reg->RSTCTL);

    /* The device is now considered closed */
    p_ctrl->open = 0U;

#if IIC_B_MASTER_CFG_DTC_ENABLE

    /* Close the handles for the transfer interfaces */
    if (NULL != p_ctrl->p_cfg->p_transfer_rx)
    {
        p_ctrl->p_cfg->p_transfer_rx->p_api->close(p_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_ctrl->p_cfg->p_transfer_tx)
    {
        p_ctrl->p_cfg->p_transfer_tx->p_api->close(p_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif

    R_BSP_IrqDisable(p_ctrl->p_cfg->eri_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->rxi_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);
    R_BSP_IrqDisable(p_ctrl->p_cfg->txi_irq);

#if (1 == BSP_FEATURE_BSP_HAS_I3C_CLOCK)
    R_BSP_MODULE_STOP(FSP_IP_I3C, p_ctrl->p_cfg->channel);
#else
    R_BSP_MODULE_STOP(FSP_IP_IIC, p_ctrl->p_cfg->channel);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IIC_B_MASTER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
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
 * @retval  FSP_ERR_IN_USE        Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized. Call R_IIC_B_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
static fsp_err_t iic_b_master_read_write (i2c_master_ctrl_t * const   p_api_ctrl,
                                          uint8_t * const             p_buffer,
                                          uint32_t const              bytes,
                                          iic_b_master_transfer_dir_t direction)
{
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) p_api_ctrl;

#if IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_buffer != NULL);
    FSP_ERROR_RETURN((p_ctrl->open == IIC_B_MASTER_OPEN), FSP_ERR_NOT_OPEN);
    FSP_ASSERT(((iic_b_master_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);
 #if IIC_B_MASTER_CFG_DTC_ENABLE

    /* DTC on RX could actually receive 65535+3 = 65538 bytes as 3 bytes are handled separately.
     * Forcing to 65535 to keep TX and RX uniform with respect to max transaction length via DTC.
     */
    FSP_ERROR_RETURN((bytes <= UINT16_MAX), FSP_ERR_INVALID_SIZE);
 #endif
#endif

    fsp_err_t err = FSP_SUCCESS;

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

#if IIC_B_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
    else
    {
        /* Set the address bytes according to a 10-bit slave read command */
        p_ctrl->addr_high = (uint8_t) (((p_ctrl->slave >> 7U) | I2C_CODE_10BIT) & (uint8_t) ~(I2C_CODE_READ));
        p_ctrl->addr_low  = (uint8_t) p_ctrl->slave;

        /* Addr total = 3 for Read and 2 for Write.
         * See Section 27.3.1.3.1 "Communication Data Format" of the RA6T2 manual R01UH0951EJ0050
         */
        p_ctrl->addr_total = (uint8_t) ((uint8_t) direction + IIC_B_MASTER_SLAVE_10_BIT_ADDR_LEN_ADJUST);
    }
#endif

    p_ctrl->read = (bool) direction;

    /* Kickoff the read operation as a master */
    err = iic_b_master_run_hw_master(p_ctrl);

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl      Pointer to transfer that is ending.
 * @param[in]       event       The event code to pass to the callback.
 **********************************************************************************************************************/
static void iic_b_master_notify (iic_b_master_instance_ctrl_t * const p_ctrl, i2c_master_event_t const event)
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

#if IIC_B_MASTER_CFG_DTC_ENABLE

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
        iic_b_master_prv_ns_callback p_callback = (iic_b_master_prv_ns_callback) (p_ctrl->p_callback);
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

    /* Clear the err flags */
    p_ctrl->err = false;
}

/*******************************************************************************************************************//**
 * Single point for managing the logic around aborting a transfer when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to control structure of specific device.
 * @param[in]       iic_reset  Flag to enable IIC reset
 **********************************************************************************************************************/
static void iic_b_master_abort_seq_master (iic_b_master_instance_ctrl_t * const p_ctrl, bool iic_reset)
{
    /* Safely stop the hardware from operating. */

    /* Reset the peripheral */
    if (true == iic_reset)
    {
        /* Disable channel interrupts */
        p_ctrl->p_reg->BIE  = 0x00;
        p_ctrl->p_reg->NTIE = 0x00;

        /* This helper function would do a full IIC reset
         * followed by re-initializing the required peripheral registers. */
        iic_b_master_open_hw_master(p_ctrl, p_ctrl->p_cfg);
    }

    /* Update the transfer descriptor to show no longer in-progress and an error */
    p_ctrl->remain = 0U;

    /* Update the transfer descriptor to make sure interrupts no longer process */
    p_ctrl->addr_loaded = p_ctrl->addr_total;
    p_ctrl->loaded      = p_ctrl->total;
    p_ctrl->restarted   = false;
    p_ctrl->restart     = false;

    /* Enable Interrupts: TMOIE, ALIE, NAKIE, RIE, TIE.
     * Disable Interrupt: TEIE, STIE, SPIE
     */
    p_ctrl->p_reg->BIE  = IIC_B_MASTER_PRV_BIE_INIT_MASK;
    p_ctrl->p_reg->NTIE = IIC_B_MASTER_PRV_NTIE_INIT_MASK;
}

/*******************************************************************************************************************//**
 * Performs the hardware initialization sequence when operating as a master (see Section 27.3.2.1
 * 'Initial Settings' of the RA6T2 manual R01UH0951EJ0050).
 *
 * @param[in]  p_ctrl                Pointer to IIC specific control structure
 * @param[in]  p_cfg                 Pointer to IIC specific configuration structure.
 **********************************************************************************************************************/
static void iic_b_master_open_hw_master (iic_b_master_instance_ctrl_t * const p_ctrl,
                                         i2c_master_cfg_t const * const       p_cfg)
{
#if (1 == BSP_FEATURE_BSP_HAS_I3C_CLOCK)

    /* Enable I3CCLK. (Not a part of init sequence in the HW manual, but RA8 must enable it to reset the module ) */
    p_ctrl->p_reg->CECTL = (uint32_t) R_I3C0_CECTL_CLKE_Msk;
#endif

    /* Clear BCTL.BUSE to 0: SCL, SDA pins not driven */
    p_ctrl->p_reg->BCTL = 0;

    /* Set RSTCTL.RI2CRST to 1: Reset all registers and internal state; RSTCTL.INTLRST is already 0.*/
    p_ctrl->p_reg->RSTCTL = (uint32_t) (R_I3C0_RSTCTL_RI3CRST_Msk);

    /* Waiting for reset completion RSTCTL.RI2CRST = 0;  RSTCTL.INTLRST is already 0. */
    FSP_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->RSTCTL_b.RI3CRST, 0U);

    /* In case of RA2E2, PRTS.PRTMD = 1 and BFCFG.FIFOE = 0 after the above reset.
     * Refer 25.2.2 'PRTS : Protocol Selection Register' and
     * 'BFCFG : Buffer Configuration Selection Register' of the RA2E2 manual R01UH0919EJ0050
     *
     * Default value of SVCTL register is 0.
     * Default/Reset value is set after IIC reset above. Refer Table 27.9 of the RA6T2 manual R01UH0951EJ0050
     * This ensures the HW is in master mode and does not behave as a slave to another master on the same channel.
     * Skip setting slave address length and slave address.
     */
    iic_b_master_extended_cfg_t * p_extend = (iic_b_master_extended_cfg_t *) (p_ctrl->p_cfg->p_extend);

    /* Clock settings - Set REFCKCTL, STDBR and EXTBR registers: Set transfer bit rate.
     * The values for these are set in the configuration structure by the tooling.
     */
    p_ctrl->p_reg->REFCKCTL = (uint32_t) (p_extend->clock_settings.cks_value & R_I3C0_REFCKCTL_IREFCKS_Msk);
    p_ctrl->p_reg->STDBR    = (uint32_t) ((p_extend->clock_settings.brl_value << R_I3C0_STDBR_SBRLO_Pos) |
                                          (p_extend->clock_settings.brh_value << R_I3C0_STDBR_SBRHO_Pos));

    /* Set OUTCTL, INCTL, TMOCTL, ACKCTL and SCSTRCTL registers.
     * (Default/Reset value is set after IIC reset above. Refer Table 27.9 of the RA6T2 manual R01UH0951EJ0050)
     * 1. OUTCTL: Keep default settings in Open.
     *
     * 2. SCSTRCTL: Keep default settings in Open.
     *
     * 3. ACKCTL: Keep default settings in Open.
     *
     * 4. INCTL: Keep default settings in Open:
     * Digital noise filter circuit is enabled by default after IIC reset.
     * Upon IIC reset, 'DNFS[3:0] Digital Noise Filter Stage Selection' will be set to 0x00
     * This would imply  'Noise of up to one IICφ cycle is filtered out (singlestage filter).'
     * (see Section 27.2.12 'INCTL : Input Control Register' of the RA6T2 manual R01UH0951EJ0050)
     *
     *  Set TOHCTL to enable timeouts when SCLn is high. (Non configurable)
     * Set TOLCTL based on user settings.
     * Set TODTS based on user settings. Only 14 (SHORT) and 16 (LONG) bit counters are allowed.
     * (see Section 27.2.13 'TMOCTL : Timeout Control Register' of the RA6T2 manual R01UH0951EJ0050).
     */
    p_ctrl->p_reg->TMOCTL = (uint32_t) ((uint32_t) R_I3C0_TMOCTL_TOHCTL_Msk |
                                        (uint32_t) (IIC_B_MASTER_TIMEOUT_MODE_SHORT ==
                                                    ((iic_b_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                                    timeout_mode) |
                                        (uint32_t) (((iic_b_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                                    timeout_scl_low << R_I3C0_TMOCTL_TOLCTL_Pos));

    /* 1. Enable FM+ slope circuit if fast mode plus is enabled.
     * 2. Set Master Arbitration-Lost Detection Enable
     * 3. Set NACK Transmission Arbitration-Lost Detection Enable
     */
    p_ctrl->p_reg->BFCTL = (((uint32_t) ((I2C_MASTER_RATE_FASTPLUS == p_ctrl->p_cfg->rate) << R_I3C0_BFCTL_FMPE_Pos)) |
                            R_I3C0_BFCTL_NALE_Msk | R_I3C0_BFCTL_MALE_Msk | R_I3C0_BFCTL_SCSYNE_Msk);

    /* Enable status for Timeout Detection, Arbitration Loss, NACK Detection, Transmit End
     * Disable status for Wake-up Condition Detection (Feature not supported by driver),
     * STOP and START condition Detection
     */
    p_ctrl->p_reg->BSTE = (uint32_t) IIC_B_MASTER_PRV_BSTE_INIT_MASK;

    /* Enable Interrupts: Timeout Detection, Arbitration Loss, NACK Detection.
     * Disable Interrupt: Transmit End, Start, Stop
     */
    p_ctrl->p_reg->BIE = (uint32_t) IIC_B_MASTER_PRV_BIE_INIT_MASK;

    /* Enable status for Transmit Data Buffer Empty and Receive Data Buffer Full */
    p_ctrl->p_reg->NTSTE = (uint32_t) IIC_B_MASTER_PRV_NTSTE_INIT_MASK;

    /* Enable Interrupts: Transmit Data Buffer Empty and Receive Data Buffer Full */
    p_ctrl->p_reg->NTIE = (uint32_t) IIC_B_MASTER_PRV_NTIE_INIT_MASK;

    /* Set valid interrupt contexts and user provided priority. Enable the interrupts at the NVIC  */
    R_BSP_IrqCfgEnable(p_cfg->eri_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->ipl, p_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->ipl, p_ctrl);

    /* Set BCTL.BUSE to 1: SCL, SDA pins in active state */
    p_ctrl->p_reg->BCTL = (uint32_t) R_I3C0_BCTL_BUSE_Msk;

    /* Set FRECYC based on IIC reference clock.
     * (Not a part of init sequence in the HW manual)
     * See section 46.3.11. IIC Timing of the RA6T2 manual R01UH0951EJ0050:
     * 1. tBUF (Standard Mode) = 5 × tIICcyc + 300 ns
     * 2. tBUF (Fast Mode) = 5 × tIICcyc + 300 ns
     * 3. tBUF (Fast Plus Mode) = 5 × tIICcyc + 120 ns
     *
     * See section 36.3.10 I3C Timing of the RA2E2 manual R01UH0919EJ0100:
     * 1. tBUF (Standard Mode) = 3 × tIICcyc + 300 ns
     * 2. tBUF (Fast Mode) = 3 × tIICcyc + 300 ns
     * 3. tBUF (Fast Plus Mode) = 3 × tIICcyc + 120 ns
     */
    uint32_t extra_ns =
        (I2C_MASTER_RATE_FASTPLUS ==
         p_ctrl->p_cfg->rate) ? IIC_B_MASTER_BFRECDT_FASTPLUS_DELAY_CONST : IIC_B_MASTER_BFRECDT_DELAY_CONST;
    uint32_t iic_clock_ns = (uint32_t) IIC_B_MASTER_BILLION / p_extend->iic_clock_freq;
    p_ctrl->p_reg->BFRECDT = (uint32_t) (BSP_FEATURE_IIC_BUS_FREE_TIME_MULTIPLIER + IIC_B_MASTER_ROUNDING_OFF_COMP +
                                         extra_ns / iic_clock_ns);
}

/*******************************************************************************************************************//**
 * Performs the data transfer described by the parameters when operating as a master.
 * See 36.3.3 "Master Transmit Operation" and section 36.3.4 "Master Receive Operation"
 * of the RA2E2 manual R01UH0886EJ0100
 *
 * @param[in]       p_ctrl  Pointer to control structure of specific device.
 *
 * @retval  FSP_SUCCESS       Data transfer success.
 * @retval  FSP_ERR_IN_USE    If data transfer is in progress.
 **********************************************************************************************************************/
static fsp_err_t iic_b_master_run_hw_master (iic_b_master_instance_ctrl_t * const p_ctrl)
{
    /* Check if this is a new transaction or a continuation */
    if (!p_ctrl->restarted)
    {
        /* If bus is busy, return error */
        FSP_ERROR_RETURN((R_I3C0_BCST_BFREF_Msk == (p_ctrl->p_reg->BCST & R_I3C0_BCST_BFREF_Msk)), FSP_ERR_IN_USE);

        /* This is not a restarted transaction. Enable TXI for the next transfer.
         * This had been disabled at the end of TXI interrupt.
         */
        p_ctrl->p_reg->NTIE = IIC_B_MASTER_PRV_NTIE_INIT_MASK;
    }

    /* Initialize fields used during transfer */
    p_ctrl->addr_loaded          = 0U;
    p_ctrl->loaded               = 0U;
    p_ctrl->remain               = p_ctrl->total;
    p_ctrl->addr_remain          = p_ctrl->addr_total;
    p_ctrl->err                  = false;
    p_ctrl->dummy_read_completed = false;
    p_ctrl->activation_on_rxi    = false;
    p_ctrl->activation_on_txi    = false;
    p_ctrl->address_restarted    = false;

    /* This gets disabled in case the previous transaction issues a restart.
     * Set TOHCTL to enable timeouts when SCLn is high. (Non configurable)
     * Set TOLCTL based on user settings.
     * Set TODTS based on user settings. Only 14 (SHORT) and 16 (LONG) bit counters are allowed.
     * (see Section 27.2.13 'TMOCTL : Timeout Control Register' of the RA6T2 manual R01UH0951EJ0050).
     */
    p_ctrl->p_reg->TMOCTL = (uint32_t) (R_I3C0_TMOCTL_TOHCTL_Msk |
                                        (uint32_t) (IIC_B_MASTER_TIMEOUT_MODE_SHORT ==
                                                    ((iic_b_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                                    timeout_mode) |
                                        (uint32_t) (((iic_b_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                                    timeout_scl_low << R_I3C0_TMOCTL_TOLCTL_Pos));

    /* Enable START condition and timeout detection
     * Enable SPCNDDIE to detect unexpected STOP condition. This is disabled between communication events as it can lead
     * to undesired interrupts in multi-master setups.
     */
    p_ctrl->p_reg->BSTE = IIC_B_MASTER_PRV_BSTE_INIT_MASK | R_I3C0_BSTE_STCNDDE_Msk | R_I3C0_BSTE_SPCNDDE_Msk |
                          R_I3C0_BSTE_TODE_Msk;
    p_ctrl->p_reg->BIE = IIC_B_MASTER_PRV_BIE_INIT_MASK | R_I3C0_BIE_STCNDDIE_Msk | R_I3C0_BIE_SPCNDDIE_Msk |
                         R_I3C0_BIE_TODIE_Msk;

    /* If previous transaction did not end with restart, send a start condition */
    if (!p_ctrl->restarted)
    {
        /* Request IIC to issue the start condition */
        p_ctrl->p_reg->CNDCTL = (uint32_t) R_I3C0_CNDCTL_STCND_Msk;
    }
    else
    {
        p_ctrl->restarted = false;

        /* Enable NTSTE.TDBEE0. This is treated differently to support restart functionality.
         * The TXI status interrupt logging (NTSTE.TDBEE0) had been disabled
         * before setting the RS bit by the previous restart enabled transaction
         * (As a part of TEI interrupt handling).
         *
         * In case the previous IIC master transaction enabled restart,
         * PRSST.CRMS = 1 and PRSST.TRMD = 1 at this point.
         * With the above condition, Once NTSTE.TDBEE0 is set, NTST.TDBEF0 will get set enabling the
         * pulse triggered IICn_TXI interrupt.
         * See Section 27.3.1.1.1 'Master Mode Operation', '(1) I2C Master Operation',
         * '(a) Data Write Transfer (Single Buffer transfer)' point #2.
         * AND
         * Table 27.8 'Interrupt Generation' of the RA6T2 manual R01UH0951EJ0050.
         *
         */
        p_ctrl->p_reg->NTSTE = (uint32_t) IIC_B_MASTER_PRV_NTSTE_INIT_MASK;
    }

    /*
     * The Flowchart under 27.3.2.2 "Master Mode Communication Flow"
     * of the RA6T2 manual R01UH0951EJ0050 is covered in the interrupts:
     *
     * 1. NACKF processing is handled in the ERI interrupt.
     *    For receive, dummy reading NTDTBP0 is not required because the NACK processing in this driver resets the IIC peripheral.
     * 2. Data is written to NTDTBP0 in the transmit interrupt (TDRE is set when a transmit interrupt fires).
     * 3. For transmit, stop is issued in the transmit end interrupt (TEND is set when a transmit end interrupt fires).
     * 4. For transmit, ICSR2 is cleared in the transmit end interrupt.
     * 5. For receive, remaining processing including reading NTDTBP0 happens in the receive interrupt (ACKTWE is set when a receive interrupt fires).
     */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Handles the receive data full interrupt when operating as a master.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 **********************************************************************************************************************/
static void iic_b_master_rxi_master (iic_b_master_instance_ctrl_t * p_ctrl)
{
    volatile uint32_t dummy_read;

    /* First receive interrupt: Handle the special case of 1 or 2 byte read here */
    if (false == p_ctrl->dummy_read_completed)
    {
        /* Enable RWE for 1 or 2 byte read */
        if (2U >= p_ctrl->total)
        {
            p_ctrl->p_reg->SCSTRCTL = R_I3C0_SCSTRCTL_RWE_Msk;
        }

        /* Enable NACK for 1 byte read */
        if (1U == p_ctrl->remain)
        {
            /* Writes to be done together with write protect bit.
             * See Note 1 in Section 27.2.15 'ACKCTL : Acknowledge Control Register'
             * of the RA6T2 manual R01UH0951EJ0050
             */
            p_ctrl->p_reg->ACKCTL = (uint32_t) (R_I3C0_ACKCTL_ACKTWP_Msk | R_I3C0_ACKCTL_ACKT_Msk);
        }

#if IIC_B_MASTER_CFG_DTC_ENABLE
        uint32_t volatile const * p_iic_b_master_rx_buffer = &(p_ctrl->p_reg->NTDTBP0);

        /* Enable transfer support if possible */
        if ((NULL != p_ctrl->p_cfg->p_transfer_rx) && (p_ctrl->read) && (p_ctrl->total > 3U))
        {
            p_ctrl->p_cfg->p_transfer_rx->p_api->reset(p_ctrl->p_cfg->p_transfer_rx->p_ctrl,
                                                       (uint8_t *) (p_iic_b_master_rx_buffer),
                                                       (void *) (p_ctrl->p_buff),
                                                       (uint16_t) (p_ctrl->total - 3U));

            p_ctrl->remain            = 3U;
            p_ctrl->loaded            = p_ctrl->total - 3U;
            p_ctrl->activation_on_rxi = true;
        }
#endif

        /* Do a dummy read to clock the data into the NTDTBP0. */
        dummy_read = p_ctrl->p_reg->NTDTBP0;
        FSP_PARAMETER_NOT_USED(dummy_read);

        p_ctrl->dummy_read_completed = true;
    }

#if IIC_B_MASTER_CFG_DTC_ENABLE

    /* If this is the interrupt that got fired after DTC transfer,
     * ignore it as the DTC has already taken care of the data transfer */
    else if (true == p_ctrl->activation_on_rxi)
    {
        p_ctrl->activation_on_rxi = false;
    }
#endif

    /* NTDTBP0 contains valid received data */
    else if (0U < p_ctrl->remain)
    {
        iic_b_master_rxi_read_data(p_ctrl);
    }
    else
    {
        /* Do nothing */
    }
}

/*******************************************************************************************************************//**
 * Handles the transmit data empty interrupt when operating as a master.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 **********************************************************************************************************************/
static void iic_b_master_txi_master (iic_b_master_instance_ctrl_t * p_ctrl)
{
    uint32_t timeout_count = IIC_B_MASTER_PERIPHERAL_REG_MAX_WAIT;

    /* Check if we are issuing the slave address */
    if (0U < p_ctrl->addr_remain)
    {
        iic_b_master_txi_send_address(p_ctrl);
    }
    else if (!p_ctrl->read)
    {
#if IIC_B_MASTER_CFG_DTC_ENABLE

        /* If this is the interrupt that got fired after DTC transfer,
         * ignore it as the DTC has already taken care of the data transfer */
        if (true == p_ctrl->activation_on_txi)
        {
            p_ctrl->activation_on_txi = false;
        }
        else if (p_ctrl->remain > 0U)
#else
        if (p_ctrl->remain > 0U)
#endif
        {
            /* Write the data to NTDTBP0 register */
            p_ctrl->p_reg->NTDTBP0 = p_ctrl->p_buff[p_ctrl->loaded];

            /* Update the number of bytes remaining for next pass */
            p_ctrl->loaded++;
            p_ctrl->remain--;
        }
        else
        {
            /* Do nothing */
        }

        /* We are done loading NTDTBP0, wait for TEND to send a stop/restart */
        if (0U == p_ctrl->remain)
        {
            /* Disable Normal Transmit Data Buffer Empty Interrupt keeping other settings unchanged. */
            p_ctrl->p_reg->NTIE = (uint32_t) R_I3C0_NTIE_RDBFIE0_Msk;

            /* Wait for the value to reflect at the peripheral.
             * See 'Note' under Table 1.138 "Interrupt sources" of the RA2E2 manual: I2C I3C unified IP (R-I3C v2) */
            IIC_B_MASTER_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->NTIE_b.TDBEIE0, 0U, timeout_count);

            /* Enable the transmit end IRQ, to issue a STOP or RESTART */
            /* Clear any pending TEND interrupts */
            R_BSP_IrqClearPending(p_ctrl->p_cfg->tei_irq);

            /* Enable the TXEND interrupt */
            p_ctrl->p_reg->BIE_b.TENDIE = 1U;

            /* No need to wait to check TENDIE has actually become 1U; because if that's not the case,
             * no other operation can occur at this point */
        }
    }
    else
    {
        /* Do nothing */
    }
}

/*******************************************************************************************************************//**
 * Handles the transmit end interrupt when operating as a master.
 * @note This interrupt is configured to be generated at the end of last byte of the requested transfer.
 *
 * @param[in]       p_ctrl     The target IIC block's control block.
 **********************************************************************************************************************/
static void iic_b_master_tei_master (iic_b_master_instance_ctrl_t * p_ctrl)
{
    uint32_t timeout_count = IIC_B_MASTER_PERIPHERAL_REG_MAX_WAIT;

    /* This is a 10 bit address read, issue a restart prior to the last address byte transmission  */
    if ((p_ctrl->read) && (p_ctrl->addr_remain == 1U) && (false == p_ctrl->address_restarted))
    {
#if IIC_B_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE

        /* Disable TXI interrupt logging to fire it from eri after restart is detected on the bus. */
        p_ctrl->p_reg->NTSTE = (uint32_t) R_I3C0_NTSTE_RDBFE0_Msk;

        /* Request IIC to issue the restart condition */
        p_ctrl->p_reg->CNDCTL     = (uint32_t) R_I3C0_CNDCTL_SRCND_Msk;
        p_ctrl->address_restarted = true;
#endif
    }
    /* We are done with the transfer, send STOP or RESTART */
    else if (0U == p_ctrl->remain)
    {
        /* Send RESTART */
        if (p_ctrl->restart)
        {
            /* NTIE.TDBEIE0 would be disabled at this point from the previous TXI. Enable it */
            p_ctrl->p_reg->NTIE = IIC_B_MASTER_PRV_NTIE_INIT_MASK;

            /* Disable NTSTE.TDBEE0
             * This diables the functionality of NTST.TDBEF0.
             * Once 'SR' is detected on the bus, PRSST.CRMS and PRSST.TRMD will get set leaving NTST.TDBEF0 cleared.
             * Upon the next Read/Write API call, NTSTE.TDBEE0 will be enabled setting the NTST.TDBEF0 bit.
             * This will allow IICn_TXI to fire where the slave address will be sent.
             */
            p_ctrl->p_reg->NTSTE = (uint32_t) R_I3C0_NTSTE_RDBFE0_Msk;

            /* Request IIC to issue the restart condition.
             * This will only fire ERI interrupt invoking a user callback
             * which informs that this transaction is completed.
             */
            p_ctrl->p_reg->CNDCTL = (uint32_t) R_I3C0_CNDCTL_SRCND_Msk;

            /* Disable timeout function. This will get re-enabled by the next read/write API */
            p_ctrl->p_reg->BSTE_b.TODE = 0U;

            /* Remember that we issued a restart for the next transfer */
            p_ctrl->restarted = true;
        }
        /* Send STOP */
        else
        {
            /* Clear STOP flag and set SP */
            p_ctrl->p_reg->BST_b.SPCNDDF = 0U;

            /* Request IIC to issue the stop condition */
            p_ctrl->p_reg->CNDCTL = (uint32_t) R_I3C0_CNDCTL_SPCND_Msk;
        }
    }
    else
    {
        /* Do nothing */
    }

    /* Disable the interrupt as we are done with the transfer */
    p_ctrl->p_reg->BST_b.TENDF  = 0U;
    p_ctrl->p_reg->BIE_b.TENDIE = 0U;

    /* Wait for the value to reflect at the peripheral.
     * See 'Note' under Table 1.138 "Interrupt sources" of the RA2E2 manual: I2C I3C unified IP (R-I3C v2) */
    IIC_B_MASTER_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->BIE_b.TENDIE, 0U, timeout_count);
}

/*******************************************************************************************************************//**
 * Handles the error interrupts when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void iic_b_master_err_master (iic_b_master_instance_ctrl_t * p_ctrl)
{
    /* Clear all the event flags except the receive data full, transmit end and transmit data empty flags*/
    uint32_t errs_events = IIC_B_MASTER_PRV_BST_ERR_STATUS_MASK & p_ctrl->p_reg->BST;
    p_ctrl->p_reg->BST &= (uint32_t) ~IIC_B_MASTER_PRV_BST_ERR_STATUS_MASK;

    /* If the event was an error event, then handle it */
    if ((errs_events &
         (uint32_t) ((uint32_t) (R_I3C0_BST_TODF_Msk) | (uint32_t) (R_I3C0_BST_ALF_Msk))) |
        ((errs_events & (uint32_t) (R_I3C0_BST_NACKDF_Msk)) && (1U != p_ctrl->p_reg->PRSST_b.CRMS)))
    {
        /* Set the error flag when an error event occurred:
         * Conditions to get here:
         * 1. This is Timeout and/or arbitration loss error during an ongoing transaction
         * 2. This is a NACK error and this device is no longer the active master on the bus.
         *    The MST bit here can get cleared:
         *     a. In case of an arbitration loss error.also occurs.
         *     b. If the slave timeout is lesser than master timeout and the slave releases
         *        the bus by performing an internal reset.
         *        Refer Section "27.2.4 PRSST : Present State Register - Clearing conditions for CRMS"
         *        of the RA6T2 manual R01UH0951EJ0050
         * 3. This is a Timeout error after attempting to issue a stop after detecting a NACK previously.
         */
        p_ctrl->err = true;

        /* Abort an in-progress transfer with the current device */
        iic_b_master_abort_seq_master(p_ctrl, true); /* This will reset the IIC Master driver */
        /* Notify anyone waiting that the transfer is Aborted due to error. */
        iic_b_master_notify(p_ctrl, I2C_MASTER_EVENT_ABORTED);
    }
    else if ((errs_events & (uint32_t) (R_I3C0_BST_NACKDF_Msk)) && (1U == p_ctrl->p_reg->PRSST_b.CRMS))
    {
        /* CRMS bit must be set to issue a stop condition.
         * Refer Section "1.8.3.3 Issuing a Stop Condition" of the RA2E2 manual: I2C I3C unified IP (R-I3C v2)
         */

        /* Set the error flag when an error event occurred
         * This will be checked after the stop condition is detected from the request below. */
        p_ctrl->err = true;

        /* The sequence below is to handle a NACK received from slave in the middle of a write.
         * See item '[4]' under 'Figure 27.47 Example of I2C master transmission flowchart' of
         * the RA6T2 manual R01UH0951EJ0050 */

        /* Request IIC to issue the stop condition */
        p_ctrl->p_reg->BST_b.SPCNDDF = 0U;

        p_ctrl->p_reg->CNDCTL = (uint32_t) R_I3C0_CNDCTL_SPCND_Msk; /* It is safe to write 0's to other bits. */
        /* Allow timeouts to be generated on the low value of SCL using either long or short mode */

        p_ctrl->p_reg->TMOCTL = (uint32_t) (R_I3C0_TMOCTL_TOHCTL_Msk |
                                            (uint32_t) (IIC_B_MASTER_TIMEOUT_MODE_SHORT ==
                                                        ((iic_b_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend)->
                                                        timeout_mode)
                                            |
                                            (uint32_t) (1U << R_I3C0_TMOCTL_TOLCTL_Pos));

        p_ctrl->p_reg->BIE_b.TODIE = 1U;

        /* This interrupt will be fired again when wither stop condition is sent
         * or the hardware detects the line is stuck low causing a timeout */
    }
    /* This is a STOP, START or RESTART event. We need to process these events only at the
     * end of the requisite transfers.
     * NOTE: Do not use p_transfer->loaded or p_transfer->remain to check whether the transfer is
     * completed, since using them would lead to a race condition between txi and eri interrupts in case
     * of one byte transfer which will result in BUS arbitration loss error */
    else if ((errs_events & (uint8_t) R_I3C0_BST_SPCNDDF_Msk) ||
             ((p_ctrl->restarted) && (errs_events & (uint8_t) R_I3C0_BST_STCNDDF_Msk)))
    {
        i2c_master_event_t event = I2C_MASTER_EVENT_ABORTED;
        if (false == p_ctrl->err)      /* Successful transaction */
        {
            /* Get the correct event to notify the user */
            event = (p_ctrl->read) ? I2C_MASTER_EVENT_RX_COMPLETE : I2C_MASTER_EVENT_TX_COMPLETE;

            /* Disable STIE/SPIE to prevent errant interrupts in multi-master scenarios */
            p_ctrl->p_reg->BIE = IIC_B_MASTER_PRV_BIE_INIT_MASK;
        }
        else if ((errs_events & (uint8_t) R_I3C0_BST_SPCNDDF_Msk))
        {
            /* This is the STOP condition requested due to a NACK error earlier.
             * Since the stop condition is successfully issued there is no need to reset the driver.
             */
            iic_b_master_abort_seq_master(p_ctrl, false); /* Clear the transaction flags only */
        }
        else
        {
            /* Do nothing */
        }

        /* Notify anyone waiting */
        iic_b_master_notify(p_ctrl, event);
    }
    else if ((p_ctrl->read) && (p_ctrl->addr_remain == 1U) && (true == p_ctrl->address_restarted))
    {
        /* NTIE.TDBEIE0 would be disabled at this point from the previous TXI
         * (Which happened just before the TEI that caused the restart condition).
         * Enable it */
        p_ctrl->p_reg->NTIE = IIC_B_MASTER_PRV_NTIE_INIT_MASK;

        /* Restart has been detected (after first 2 address bytes of 10-bit slave address format are sent).
         * This is a request to read, send 3rd byte of 10-bit slave address. */
        p_ctrl->p_reg->NTSTE = (uint32_t) IIC_B_MASTER_PRV_NTSTE_INIT_MASK;
    }
    else
    {
        /* Do nothing */
    }
}

/*******************************************************************************************************************//**
 * Check valid receive data and set RWE, NACK and STOP/RESTART bit in RXI handler.
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void iic_b_master_rxi_read_data (iic_b_master_instance_ctrl_t * const p_ctrl)
{
    /* If next data = (final byte - 2), enable RWE */
    if (3U == p_ctrl->remain)
    {
        p_ctrl->p_reg->SCSTRCTL = R_I3C0_SCSTRCTL_RWE_Msk;
    }
    /* If next data = (final byte - 1), enable NACK  */
    else if (2U == p_ctrl->remain)
    {
        /* Writes to be done together with write protect bit.
         * See Note 1 in Section 27.2.15 'ACKCTL : Acknowledge Control Register'
         * of the RA6T2 manual R01UH0951EJ0050
         */
        p_ctrl->p_reg->ACKCTL = (uint32_t) (R_I3C0_ACKCTL_ACKTWP_Msk | R_I3C0_ACKCTL_ACKT_Msk);
    }
    /* If next data = final byte, send STOP or RESTART */
    else if (1U == p_ctrl->remain)
    {
        if (p_ctrl->restart)
        {
            /* NOTE: Only disable NTSTE.TDBEE0 (leaving NTIE.TDBEIE0 enabled).
             * This will allow the interrupt to fire in the "restarted" (next)
             * transaction when NTSTE.TDBEE0 is re-enabled.
             * NTIE.TDBEIE0 should be already enabled as this is a read transfer.
             */
            p_ctrl->p_reg->NTSTE = (uint32_t) R_I3C0_NTSTE_RDBFE0_Msk;

            /* This bit clears to 0 automatically by issuing stop condition.
             * For restart condition, clear bit by software.
             */
            p_ctrl->p_reg->ACKCTL = (uint32_t) (R_I3C0_ACKCTL_ACKTWP_Msk);

            /* Request IIC to issue the restart condition */
            p_ctrl->p_reg->CNDCTL = (uint32_t) R_I3C0_CNDCTL_SRCND_Msk;

            /* Disable timeout function */
            p_ctrl->p_reg->BIE_b.TODIE = 0U;

            /* Remember that we issued a restart when doing the next transfer */
            p_ctrl->restarted = true;
        }
        else
        {
            /* Clear STOP flag and set SP.
             * It is ok to clear other status' as this transaction is over.
             */
            p_ctrl->p_reg->BST_b.SPCNDDF = 0U;

            /* Request IIC to issue the stop condition */

            p_ctrl->p_reg->CNDCTL = (uint32_t) R_I3C0_CNDCTL_SPCND_Msk; /* It is safe to write 0's to other bits. */

            /* STOP flag will not be set just yet. STOP will be set only after reading the
             * last byte from NTDTBP0 and clearing the RWE.
             * See Point #7 under '27.3.1.1.1 Master Mode Operation, (1) I2C Master Operation,
             * (b) Data Read Transfer (Single Buffer transfer)' of the RA6T2 manual R01UH0951EJ0050.
             */
        }
    }
    else
    {
        /* Do nothing */
    }

    volatile uint32_t read_data = p_ctrl->p_reg->NTDTBP0;
    p_ctrl->p_buff[p_ctrl->loaded] = (uint8_t) read_data;

    /* Update the counter values */
    p_ctrl->loaded++;
    p_ctrl->remain--;

    /* If we are done with the reception, clear the RWE bit */
    if (0U == p_ctrl->remain)
    {
        p_ctrl->p_reg->SCSTRCTL = 0;

        /* If this transaction does not have the restart flag set to true,
         * last byte has been read and RWE has been cleared.
         * Callback will be issued by the ERI once the stop condition is detected
         * In case of restart flag set to true a callback will be issued by the ERI once the start
         * (from restart) condition is detected
         */
    }
}

/*******************************************************************************************************************//**
 * Write the address byte to the iic bus
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void iic_b_master_txi_send_address (iic_b_master_instance_ctrl_t * const p_ctrl)
{
    /* This is a 10 bit read and we have transmitted the low byte, next is restart */
    if ((3U == p_ctrl->addr_total) && (2U == p_ctrl->addr_loaded) && (false == p_ctrl->address_restarted))
    {
#if IIC_B_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
        uint32_t timeout_count = IIC_B_MASTER_PERIPHERAL_REG_MAX_WAIT;

        /* For Read operation an extra address byte needs to be sent after issuing restart.
         * At this point we have sent the first 2 address bytes. Disable TXI.
         */
        p_ctrl->p_reg->NTIE = (uint32_t) R_I3C0_NTIE_RDBFIE0_Msk;

        /* Wait for the value to reflect at the peripheral.
         * See 'Note' under Table 1.138 "Interrupt sources" of the RA2E2 manual: I2C I3C unified IP (R-I3C v2) */
        IIC_B_MASTER_HARDWARE_REGISTER_WAIT(p_ctrl->p_reg->NTIE_b.TDBEIE0, 0U, timeout_count);

        /* Enable the transmit end IRQ, so that we can generate a RESTART condition */
        /* Clear any pending TEND interrupts */
        R_BSP_IrqClearPending(p_ctrl->p_cfg->tei_irq);

        /* Enable the TXEND interrupt */
        p_ctrl->p_reg->BIE_b.TENDIE = 1U;

        /* No need to wait to check TEIE has actually become 1U; because if that's not the case,
         * no other operation can occur at this point */
#endif
    }
    else
    {
        /* Address low byte, this could either be a 7 bit address or low byte of 10 bit address */
        uint8_t address_byte = p_ctrl->addr_low;
#if IIC_B_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE

        /* 10 bit address, handle accordingly */
        if (p_ctrl->addr_total > 1U)
        {
            /* MSB transfer, send address high byte with with R/W set to 0 */
            if (0U == p_ctrl->addr_loaded)
            {
                address_byte = p_ctrl->addr_high;
            }
            /* MSB transfer after restart of 10 bit read, send high byte with R/W set to 1 */
            else if ((2U == p_ctrl->addr_loaded) && (3U == p_ctrl->addr_total))
            {
                address_byte = p_ctrl->addr_high | (uint8_t) I2C_CODE_READ;
            }
            /* Low byte transfer */
            else
            {
                address_byte = p_ctrl->addr_low;
            }
        }
#endif

#if IIC_B_MASTER_CFG_DTC_ENABLE
        uint32_t volatile const * p_iic_b_master_tx_buffer = &(p_ctrl->p_reg->NTDTBP0);

        /* If this is the last address byte, enable transfer */
        if (1U == p_ctrl->addr_remain)
        {
            if ((NULL != p_ctrl->p_cfg->p_transfer_tx) && !(p_ctrl->read) && (p_ctrl->total > 0U))
            {
                p_ctrl->p_cfg->p_transfer_tx->p_api->reset(p_ctrl->p_cfg->p_transfer_tx->p_ctrl,
                                                           (void *) (p_ctrl->p_buff),
                                                           (uint8_t *) (p_iic_b_master_tx_buffer),
                                                           (uint16_t) (p_ctrl->remain));
                p_ctrl->remain            = 0U;
                p_ctrl->loaded            = p_ctrl->total;
                p_ctrl->activation_on_txi = true;
            }
        }
#endif

        /* Write the address byte */
        p_ctrl->p_reg->NTDTBP0 = address_byte;

        /* Update the number of address bytes loaded for next pass */
        p_ctrl->addr_loaded++;
        p_ctrl->addr_remain--;
    }
}

#if IIC_B_MASTER_CFG_DTC_ENABLE

/*******************************************************************************************************************//**
 * Configures IIC related transfer drivers (if enabled).
 *
 * @param[in]   p_ctrl    Pointer to IIC specific control structure
 * @param[in]   p_cfg     Pointer to IIC specific configuration structure
 *
 * @retval      FSP_SUCCESS                Transfer interface initialized successfully.
 * @retval      FSP_ERR_ASSERTION          Pointer to transfer instance for I2C receive in p_cfg is NULL.
 **********************************************************************************************************************/
static fsp_err_t iic_b_master_transfer_open (i2c_master_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    if (NULL != p_cfg->p_transfer_rx)
    {
        err = iic_b_master_transfer_configure(p_cfg->p_transfer_rx, IIC_B_MASTER_TRANSFER_DIR_READ);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        err = iic_b_master_transfer_configure(p_cfg->p_transfer_tx, IIC_B_MASTER_TRANSFER_DIR_WRITE);
        if (FSP_SUCCESS != err)
        {
            if (NULL != p_cfg->p_transfer_rx)
            {
                p_cfg->p_transfer_rx->p_api->close(p_cfg->p_transfer_rx->p_ctrl);
            }

            return err;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures  IIC RX related transfer.
 * @param[in]     p_ctrl                     Pointer to IIC specific control structure
 * @param[in]     p_cfg                      Pointer to IIC specific configuration structure
 *
 * @retval        FSP_SUCCESS                Transfer interface is configured with valid parameters.
 * @retval        FSP_ERR_ASSERTION          Pointer to transfer instance for I2C receive in p_cfg is NULL.
 **********************************************************************************************************************/
static fsp_err_t iic_b_master_transfer_configure (transfer_instance_t const * p_transfer,
                                                  iic_b_master_transfer_dir_t direction)
{
    fsp_err_t err;

    /* Set default transfer info and open receive transfer module, if enabled. */
 #if (IIC_B_MASTER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_transfer->p_api);
    FSP_ASSERT(NULL != p_transfer->p_cfg);
    FSP_ASSERT(NULL != p_transfer->p_cfg->p_info);
 #endif
    transfer_info_t * p_cfg = p_transfer->p_cfg->p_info;
    if (IIC_B_MASTER_TRANSFER_DIR_READ == direction)
    {
        p_cfg->transfer_settings_word = IIC_B_MASTER_DTC_RX_TRANSFER_SETTINGS;
    }
    else
    {
        p_cfg->transfer_settings_word = IIC_B_MASTER_DTC_TX_TRANSFER_SETTINGS;
    }

    err = p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    return FSP_SUCCESS;
}

#endif

/***********************************************************************************************************************
 * Interrupt Vectors
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Receive data full interrupt routine.
 *
 * This function implements the IIC Receive buffer full ISR routine.
 *
 **********************************************************************************************************************/
void iic_b_master_rxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_b_master_rxi_master(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Transmit data empty interrupt routine.
 *
 * This function implements the Transmit buffer empty ISR routine.
 *
 **********************************************************************************************************************/
void iic_b_master_txi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_b_master_txi_master(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Transmit end interrupt routine.
 *
 * This function implements the IIC Transmission End ISR routine.
 *
 **********************************************************************************************************************/
void iic_b_master_tei_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_b_master_tei_master(p_ctrl);

    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Error and event interrupt routine.
 *
 * This function implements the IIC Event/Error.
 *
 **********************************************************************************************************************/
void iic_b_master_eri_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iic_b_master_instance_ctrl_t * p_ctrl = (iic_b_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    iic_b_master_err_master(p_ctrl);

    /* Clear the IR flag */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
