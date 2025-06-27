/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_iica_master.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "IICA" in ASCII, used to determine if channel is open. */
#define IICA_MASTER_OPEN                       (0x52494943U)

#define I2C_CODE_READ                          (0x01U)
#define I2C_CODE_10BIT                         (0xF0U)

#define IICA_MASTER_IICCTL00_INIT              (R_IICA0_IICCTL00_ACKE_Msk | R_IICA0_IICCTL00_WTIM_Msk | \
                                                R_IICA0_IICCTL00_SPIE_Msk)
#define IICA_MASTER_IICCTL00_WREL_ACKE_MASK    ((1 << R_IICA0_IICCTL00_WREL_Pos) | \
                                                (1 << R_IICA0_IICCTL00_ACKE_Pos))
#define IICA_MASTER_IICCTL00_WREL_WTIM_MASK    ((1 << R_IICA0_IICCTL00_WREL_Pos) | \
                                                (1 << R_IICA0_IICCTL00_WTIM_Pos))
#if (IICA_MASTER_CFG_SINGLE_CHANNEL == 1)
 #define IICA_REG                              R_IICA1
#elif (IICA_MASTER_CFG_SINGLE_CHANNEL == 0)
 #define IICA_REG                              R_IICA0
#else
 #define IICA_REG                              p_ctrl->p_reg
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* IICA read/write enumeration */
typedef enum e_iica_master_transfer_dir_option
{
    IICA_MASTER_TRANSFER_DIR_WRITE = 0x0,
    IICA_MASTER_TRANSFER_DIR_READ  = 0x1
} iica_master_transfer_dir_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

void iica_master_txrxi_isr(void);

/* Internal helper functions */
static void      r_iica_master_abort_seq_master(iica_master_instance_ctrl_t * const p_ctrl, bool iica_reset);
static fsp_err_t r_iica_master_read_write(i2c_master_ctrl_t * const  p_api_ctrl,
                                          uint8_t * const            p_buffer,
                                          uint32_t const             bytes,
                                          iica_master_transfer_dir_t direction);
static void r_iica_master_notify(iica_master_instance_ctrl_t * const p_ctrl, bool error);
static void r_iica_master_do_tx_rx(iica_master_instance_ctrl_t * p_ctrl);

/* Interrupt handlers */
static void r_iica_master_txrxi_master(iica_master_instance_ctrl_t * p_ctrl);

/* Functions that manipulate hardware */
static void r_iica_master_open_hw_master(iica_master_instance_ctrl_t * const p_ctrl,
                                         i2c_master_cfg_t const * const      p_cfg);
static fsp_err_t r_iica_master_run_hw_master(iica_master_instance_ctrl_t * const p_ctrl);
static void      r_iica_master_send_address(iica_master_instance_ctrl_t * const p_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* IICA Implementation of IICA device master interface */
i2c_master_api_t const g_iica_master_on_iica =
{
    .open            = R_IICA_MASTER_Open,
    .read            = R_IICA_MASTER_Read,
    .write           = R_IICA_MASTER_Write,
    .abort           = R_IICA_MASTER_Abort,
    .slaveAddressSet = R_IICA_MASTER_SlaveAddressSet,
    .close           = R_IICA_MASTER_Close,
    .statusGet       = R_IICA_MASTER_StatusGet,
    .callbackSet     = R_IICA_MASTER_CallbackSet
};

/*******************************************************************************************************************//**
 * @addtogroup IICA_MASTER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the IICA device.
 *
 * @retval  FSP_SUCCESS                       Requested clock rate was set exactly.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT    Channel is not available on this MCU.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 *                                            4. Invalid IRQ number assigned
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_Open (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_cfg_t const * const p_cfg)
{
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;
#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);

    FSP_ERROR_RETURN(IICA_MASTER_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_IIC_VALID_CHANNEL_MASK & (1 << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

    /* Record the pointer to the configuration structure for later use */
    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->slave      = p_cfg->slave;
    p_ctrl->addr_mode  = p_cfg->addr_mode;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;

    R_BSP_MODULE_START(FSP_IP_IICA, p_cfg->channel);

#if (IICA_MASTER_CFG_SINGLE_CHANNEL == -1)
    p_ctrl->p_reg =
        (R_IICA0_Type *) ((uint32_t) R_IICA0 + (p_cfg->channel * ((uint32_t) R_IICA1 - (uint32_t) R_IICA0)));
#endif

    /* Open the hardware in master mode. Performs IICA initialization as described in hardware manual (see Section 22.4.16
     * Initial Settings for master mode of the manual). */
    r_iica_master_open_hw_master(p_ctrl, p_cfg);
    p_ctrl->p_buff    = NULL;
    p_ctrl->total     = 0U;
    p_ctrl->loaded    = 0U;
    p_ctrl->read      = false;
    p_ctrl->err       = false;
    p_ctrl->restarted = false;
    p_ctrl->open      = IICA_MASTER_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Performs a read from the IICA device.
 * The caller will be notified when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_RX_COMPLETE in the callback.
 *
 * @retval  FSP_SUCCESS             Function executed without issue.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl, p_dest or bytes is NULL.
 * @retval  FSP_ERR_INVALID_SIZE    Provided number of bytes more than uint16_t size (65535) for data transfer.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IICA_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_Read (i2c_master_ctrl_t * const p_api_ctrl,
                              uint8_t * const           p_dest,
                              uint32_t const            bytes,
                              bool const                restart)
{
#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
    FSP_ASSERT(bytes != 0U);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of r_iica_master_read_write to 4. */
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;
    p_ctrl->restart = restart;

    /* Call the common helper function to perform IICA Read operation.*/
    err = r_iica_master_read_write(p_api_ctrl, p_dest, bytes, IICA_MASTER_TRANSFER_DIR_READ);

    return err;
}

/*******************************************************************************************************************//**
 * Performs a write to the IICA device.
 * The caller will be notifieEd when the operation has completed (successfully) by an
 * I2C_MASTER_EVENT_TX_COMPLET in the callback.
 *
 * @retval  FSP_SUCCESS           Function executed without issue.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_src is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than uint16_t size (65535) for data transfer.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized.  Call R_IICA_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_Write (i2c_master_ctrl_t * const p_api_ctrl,
                               uint8_t * const           p_src,
                               uint32_t const            bytes,
                               bool const                restart)
{
#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif
    fsp_err_t err = FSP_SUCCESS;

    /* Record the restart information about this transfer.
     * This is done here to keep the parameter (argument) list of r_iica_master_read_write to 4. */
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;
    p_ctrl->restart = restart;

    /* Call the common helper function to perform IICA Write operation.*/
    err = r_iica_master_read_write(p_api_ctrl, p_src, bytes, IICA_MASTER_TRANSFER_DIR_WRITE);

    return err;
}

/*******************************************************************************************************************//**
 * Safely aborts any in-progress transfer and forces the IICA peripheral into ready state.
 *
 *
 * @retval  FSP_SUCCESS             Channel was reset successfully.
 * @retval  FSP_ERR_ASSERTION       p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IICA_MASTER_Open to initialize the control block.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_Abort (i2c_master_ctrl_t * const p_api_ctrl)
{
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;

#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IICA_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort any transfer happening on the channel */
    r_iica_master_abort_seq_master(p_ctrl, false);

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
 * @retval  FSP_ERR_NOT_OPEN        Handle is not initialized.  Call R_IICA_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_SlaveAddressSet (i2c_master_ctrl_t * const    p_api_ctrl,
                                         uint32_t const               slave,
                                         i2c_master_addr_mode_t const addr_mode)
{
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;

#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IICA_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN(!IICA_REG->IICS0_b.MSTS, FSP_ERR_IN_USE);
 #if !IICA_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
    FSP_ERROR_RETURN(p_ctrl->addr_mode != I2C_MASTER_ADDR_MODE_10BIT, FSP_ERR_INVALID_MODE);
 #endif
#endif

    /* Sets the address of the slave device */
    p_ctrl->slave = slave;

    p_ctrl->addr_mode = addr_mode;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements i2c_master_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_CallbackSet (i2c_master_ctrl_t * const          p_api_ctrl,
                                     void (                           * p_callback)(i2c_master_callback_args_t *),
                                     void * const                       p_context,
                                     i2c_master_callback_args_t * const p_callback_memory)
{
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;

#if (IICA_MASTER_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ASSERT(p_callback_memory == NULL);
    FSP_ERROR_RETURN(IICA_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
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
fsp_err_t R_IICA_MASTER_StatusGet (i2c_master_ctrl_t * const p_api_ctrl, i2c_master_status_t * p_status)
{
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;

#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_status != NULL);
#endif

    p_status->open = (IICA_MASTER_OPEN == p_ctrl->open);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the IICA device. May power down IICA peripheral.
 * This function will safely terminate any in-progress IICA transfers.
 *
 * @retval  FSP_SUCCESS         Device closed without issue.
 * @retval  FSP_ERR_ASSERTION   p_api_ctrl is NULL.
 * @retval  FSP_ERR_NOT_OPEN    Handle is not initialized.  Call R_IICA_MASTER_Open to initialize the control block.
 *
 * @note A callback will not be invoked in case an in-progress transfer gets aborted by calling this API.
 **********************************************************************************************************************/
fsp_err_t R_IICA_MASTER_Close (i2c_master_ctrl_t * const p_api_ctrl)
{
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;

#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ERROR_RETURN(IICA_MASTER_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Abort an in-progress transfer with this device only */
    r_iica_master_abort_seq_master(p_ctrl, true);

    /* The device is now considered closed */
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);
    R_BSP_MODULE_STOP(FSP_IP_IICA, p_ctrl->p_cfg->channel);

    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IICA_MASTER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Helper function for handling IICA Read or Write.
 *
 * @param      p_api_ctrl      Pointer to control block
 * @param      p_buffer        Pointer to the buffer to store read/write data.
 * @param[in]  bytes           Number of bytes to be read/written.
 * @param[in]  direction       Read or Write
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_buffer is NULL.
 * @retval  FSP_ERR_INVALID_SIZE  Provided number of bytes more than UINT16_MAX(= 65535).
 * @retval  FSP_ERR_IN_USE        Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized. Call R_IICA_MASTER_Open to initialize the control block.
 **********************************************************************************************************************/
static fsp_err_t r_iica_master_read_write (i2c_master_ctrl_t * const  p_api_ctrl,
                                           uint8_t * const            p_buffer,
                                           uint32_t const             bytes,
                                           iica_master_transfer_dir_t direction)
{
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) p_api_ctrl;

#if IICA_MASTER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_buffer != NULL);
    FSP_ERROR_RETURN((IICA_MASTER_OPEN == p_ctrl->open), FSP_ERR_NOT_OPEN);
    FSP_ASSERT(((iica_master_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);
#endif

    p_ctrl->p_buff = p_buffer;
    p_ctrl->total  = bytes;
    p_ctrl->loaded = 0U;

    /* Handle the (different) addressing mode(s) */
    if (p_ctrl->addr_mode == I2C_MASTER_ADDR_MODE_7BIT)
    {
        /* Set the address bytes according to a 7-bit slave read command */
        p_ctrl->addr_high  = (uint8_t) ((p_ctrl->slave << 1U) | (uint8_t) direction);
        p_ctrl->addr_total = 1U;
    }

#if IICA_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
    else
    {
        /* Set the address bytes according to a 10-bit slave read command */
        p_ctrl->addr_high = (uint8_t) (((p_ctrl->slave >> 8U) << 1U) | I2C_CODE_10BIT);
        p_ctrl->addr_low  = (uint8_t) p_ctrl->slave;

        /* Addr total = 3 for Read and 2 for Write. */
        p_ctrl->addr_total = (uint8_t) ((uint8_t) direction + I2C_MASTER_ADDR_MODE_10BIT);
    }
#endif

    p_ctrl->read = (bool) direction;

    /* Kickoff the read operation as a master */
    return r_iica_master_run_hw_master(p_ctrl);
}

/*******************************************************************************************************************//**
 * Single point for managing the logic around notifying a transfer has finished.
 *
 * @param[in]       p_ctrl      Pointer to transfer that is ending.
 * @param[in]       error       There are errors in transmitting data.
 **********************************************************************************************************************/
static void r_iica_master_notify (iica_master_instance_ctrl_t * const p_ctrl, bool error)
{
    i2c_master_callback_args_t args;
    i2c_master_event_t         event;

    if (error)
    {
        event = I2C_MASTER_EVENT_ABORTED;
    }
    else if (p_ctrl->read)
    {
        event = I2C_MASTER_EVENT_RX_COMPLETE;
    }
    else
    {
        event = I2C_MASTER_EVENT_TX_COMPLETE;
    }

    args.p_context = p_ctrl->p_context;
    args.event     = event;

    /* Now do the callback here */
    p_ctrl->p_callback(&args);
}

/*******************************************************************************************************************//**
 * Single point for managing the logic around aborting a transfer when operating as a master.
 *
 * @param[in]       p_ctrl  Pointer to control structure of specific device.
 * @param[in]       iica_reset  Flag to enable IICA reset
 **********************************************************************************************************************/
static void r_iica_master_abort_seq_master (iica_master_instance_ctrl_t * const p_ctrl, bool iica_reset)
{
    iica_master_extended_cfg_t * pextend = (iica_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Abort communication */
    IICA_REG->IICCTL00_b.IICE = 0U;

    /* Reset the peripheral */
    if (false == iica_reset)
    {
        /* Enable generation of a start condition without detecting a stop condition */
        IICA_REG->IICF0 = R_IICA0_IICF0_STCEN_Msk;

        /* IICCTL00 Register Settings:
         * 1. ACKE = 1：Enable acknowledgment. During the 9th clock period, the SDAA0 line is set to low level.
         * 2. WTIM = 1：An interrupt request is generated on the falling edge of the 9th clock cycle.
         * 3. SPIE = 1：Enable and disable generation of interrupt request when stop condition is detected
         * 4. IICE = 1：Enable IICA operation.
         */
        IICA_REG->IICCTL00 |= R_IICA0_IICCTL00_IICE_Msk | IICA_MASTER_IICCTL00_INIT;
    }
    else
    {
        /* Disable Pin settings */
        R_BSP_PinAccessEnable();
        R_BSP_PinCfg(pextend->scl_pin_settings.pin, IOPORT_CFG_PORT_DIRECTION_INPUT);
        R_BSP_PinCfg(pextend->sda_pin_settings.pin, IOPORT_CFG_PORT_DIRECTION_INPUT);
        R_BSP_PinAccessDisable();
    }

    /* Update the transfer descriptor to show no longer in-progress and an error */
    p_ctrl->restarted = false;
    p_ctrl->total     = 0;
}

/*******************************************************************************************************************//**
 * Performs the hardware initialization sequence when operating as a master (see Section 22.4.16
 * Initial setting for master mode of the manual).
 *
 * @param[in]  p_ctrl                Pointer to IIC specific control structure
 * @param[in]  p_cfg                 Pointer to IIC specific configuration structure.
 **********************************************************************************************************************/
static void r_iica_master_open_hw_master (iica_master_instance_ctrl_t * const p_ctrl,
                                          i2c_master_cfg_t const * const      p_cfg)
{
    iica_master_extended_cfg_t * pextend = (iica_master_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    uint8_t iicctl01 = 0;

    /* Set a transfer clock */
    IICA_REG->IICWL0 = pextend->clock_settings.iicwl_value;
    IICA_REG->IICWH0 = pextend->clock_settings.iicwh_value;

    /* IICCTL01 Register Settings */
    /* Set IICA operation clock and digital filter */
    /* Set operation mode */
    if (p_ctrl->p_cfg->rate == I2C_MASTER_RATE_STANDARD)
    {
        iicctl01 =
            (uint8_t) ((pextend->clock_settings.cks_value) |
                       (pextend->clock_settings.digital_filter << R_IICA0_IICCTL01_DFC_Pos));
    }
    else
    {
        iicctl01 =
            (uint8_t) ((pextend->clock_settings.cks_value) |
                       (pextend->clock_settings.digital_filter << R_IICA0_IICCTL01_DFC_Pos) |
                       (uint8_t) R_IICA0_IICCTL01_SMC_Msk);
    }

    IICA_REG->IICCTL01 = iicctl01;

    R_BSP_IrqCfgEnable(p_cfg->tei_irq, p_cfg->ipl, p_ctrl);

    IICA_REG->IICCTL00_b.IICE = 0U;

    /* Enable generation of a start condition without detecting a stop condition */
    IICA_REG->IICF0 = R_IICA0_IICF0_STCEN_Msk;

    /* IICCTL00 Register Settings:
     * 1. ACKE = 1：Enable acknowledgment. During the 9th clock period, the SDAA0 line is set to low level.
     * 2. WTIM = 1：An interrupt request is generated on the falling edge of the 9th clock cycle.
     * 3. SPIE = 1：Enable and disable generation of interrupt request when stop condition is detected
     * 4. IICE = 1：Enable IICA operation.
     */
    IICA_REG->IICCTL00 |= R_IICA0_IICCTL00_IICE_Msk | IICA_MASTER_IICCTL00_INIT;

    /* Configure Pin settings */
    R_BSP_PinAccessEnable();
    R_BSP_PinCfg(pextend->scl_pin_settings.pin, pextend->scl_pin_settings.cfg);
    R_BSP_PinCfg(pextend->sda_pin_settings.pin, pextend->sda_pin_settings.cfg);
    R_BSP_PinAccessDisable();
}

/*******************************************************************************************************************//**
 * Performs the data transfer described by the parameters when operating as a master.
 * See 22.4.16 Communication processing for master mode of the manual.
 *
 * @param[in]       p_ctrl  Pointer to control structure of specific device.
 *
 * @retval  FSP_SUCCESS       Data transfer success.
 * @retval  FSP_ERR_IN_USE    If data transfer is in progress.
 **********************************************************************************************************************/
static fsp_err_t r_iica_master_run_hw_master (iica_master_instance_ctrl_t * const p_ctrl)
{
    /* Initialize fields used during transfer */
    p_ctrl->addr_loaded          = 0U;
    p_ctrl->err                  = false;
    p_ctrl->dummy_read_completed = false;

    if (!p_ctrl->restarted)
    {
        IICA_REG->IICCTL00 |= R_IICA0_IICCTL00_STT_Msk;
        r_iica_master_send_address(p_ctrl);
    }
    else
    {
        p_ctrl->restarted = false;
        r_iica_master_send_address(p_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Handles the transmit interrupt when operating as a master.
 *
 * @param[in]       p_ctrl     The target IICA block's control block.
 **********************************************************************************************************************/
static void r_iica_master_txrxi_master (iica_master_instance_ctrl_t * p_ctrl)
{
    /* If the event was an error event, then handle it */
    uint8_t reg_iics0 = IICA_REG->IICS0;
    if (reg_iics0 & R_IICA0_IICS0_SPD_Msk)
    {
        r_iica_master_notify(p_ctrl, p_ctrl->err);
    }
    else if (((!(reg_iics0 & R_IICA0_IICS0_ACKD_Msk) && !(p_ctrl->dummy_read_completed)) ||
              !(reg_iics0 & R_IICA0_IICS0_MSTS_Msk) || ((reg_iics0 & R_IICA0_IICS0_ALD_Msk))))
    {
        p_ctrl->err = true;

        /* Conditions to get here:
         * 1. This is arbitration loss error during an ongoing transaction
         * 2. This is a NACK error and this device is no longer the active master on the bus.
         *    The MSTS bit here can get cleared:
         *     a. In case of an arbitration loss error.also occurs.
         *//* Request IICA to issue the stop condition */
        IICA_REG->IICCTL00 |= (uint8_t) R_IICA0_IICCTL00_SPT_Msk; /* It is safe to write 0's to other bits. */
    }

#if IICA_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
    else if (p_ctrl->addr_loaded < p_ctrl->addr_total)
    {
        r_iica_master_send_address(p_ctrl);
    }
#endif
    else if (p_ctrl->loaded < p_ctrl->total)
    {
        r_iica_master_do_tx_rx(p_ctrl);
    }
    else
    {
        if (!p_ctrl->restart)
        {
            IICA_REG->IICCTL00_b.SPT = 1U;
        }
        else
        {
            IICA_REG->IICCTL00_b.STT = 1U;
            p_ctrl->restarted        = true;

            r_iica_master_notify(p_ctrl, p_ctrl->err);
        }
    }
}

/*******************************************************************************************************************//**
 * Handles the transmit and recevie data when operating as a master.
 * @param[in]       p_ctrl     The target IICA block's control block.
 **********************************************************************************************************************/
static void r_iica_master_do_tx_rx (iica_master_instance_ctrl_t * p_ctrl)
{
    if (!p_ctrl->read)
    {
        /* Write the data to IICA0 register */
        IICA_REG->IICA0 = p_ctrl->p_buff[p_ctrl->loaded];

        /* Update the number of bytes remaining for next pass */
        p_ctrl->loaded++;
    }
    else if (false == p_ctrl->dummy_read_completed)
    {
        /* Do a dummy read to clock the data into the IICA0 */
        IICA_REG->IICA0;

        /* Update the counter */
        p_ctrl->dummy_read_completed = true;
        IICA_REG->IICCTL00           = (IICA_REG->IICCTL00 & ((uint8_t) ~(1U << R_IICA0_IICCTL00_WTIM_Pos))) |
                                       IICA_MASTER_IICCTL00_WREL_ACKE_MASK;
    }
    else
    {
        p_ctrl->p_buff[p_ctrl->loaded] = IICA_REG->IICA0;

        /* Update the counter values */
        p_ctrl->loaded++;

        if (p_ctrl->loaded == p_ctrl->total)
        {
            IICA_REG->IICCTL00 = (IICA_REG->IICCTL00 & ((uint8_t) ~(1U << R_IICA0_IICCTL00_ACKE_Pos))) |
                                 IICA_MASTER_IICCTL00_WREL_WTIM_MASK;
        }
        else
        {
            IICA_REG->IICCTL00 |= R_IICA0_IICCTL00_WREL_Msk;
        }
    }
}

/*******************************************************************************************************************//**
 * Write the address byte to the IICA
 *
 * @param[in]       p_ctrl  Pointer to transfer control block
 **********************************************************************************************************************/
static void r_iica_master_send_address (iica_master_instance_ctrl_t * const p_ctrl)
{
    /* Address first byte, this could either be a 7 bit address or first byte of 10 bit address */
    uint8_t address_byte = p_ctrl->addr_high;
#if IICA_MASTER_CFG_ADDR_MODE_10_BIT_ENABLE
    if (p_ctrl->addr_loaded == 1)
    {
        address_byte = p_ctrl->addr_low;
    }
    else if (p_ctrl->addr_loaded == 2)
    {
        IICA_REG->IICCTL00_b.STT = 1U;
        address_byte             = p_ctrl->addr_high | I2C_CODE_READ;
    }
    else
    {
        // Do nothing
    }
#endif

    /* Update the number of address bytes loaded for next pass */
    p_ctrl->addr_loaded++;

    /* Write the address byte */
    IICA_REG->IICA0 = address_byte;
}

/*******************************************************************************************************************//**
 * Transmit interrupt routine.
 *
 * This function implements the IIC Transmission ISR routine.
 *
 **********************************************************************************************************************/
void iica_master_txrxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iica_master_instance_ctrl_t * p_ctrl = (iica_master_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    r_iica_master_txrxi_master(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
