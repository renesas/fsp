/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include "r_iica_slave.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* "I2CS" in ASCII, used to determine if channel is open. */
#define IICA_SLAVE_OPEN                       (0x49324353ULL)

#define IICA_SLAVE_IICS0_EXC_ACKD_MASK        ((1 << R_IICA0_IICS0_EXC_Pos) | (1 << R_IICA0_IICS0_ACKD_Pos))

#define IICA_SLAVE_IICA0_HIGH_BITS_MASK       (0xFE)
#define I2C_CODE_10BIT                        (0xF0U)

#define IICA_SLAVE_IICF0_STCEN_IICRSV_MASK    ((1 << R_IICA0_IICF0_IICRSV_Pos) | (1 << R_IICA0_IICF0_STCEN_Pos))

#define IICA_SLAVE_IICCTL00_INIT              ((1 << R_IICA0_IICCTL00_IICE_Pos) | (1 << R_IICA0_IICCTL00_LREL_Pos) | \
                                               (1 << R_IICA0_IICCTL00_WTIM_Pos) | (1 << R_IICA0_IICCTL00_ACKE_Pos))
#define IICA_SLAVE_IICCTL00_SPIE_WREL_MASK    ((1 << R_IICA0_IICCTL00_WREL_Pos) | (1 << R_IICA0_IICCTL00_SPIE_Pos))
#if (IICA_SLAVE_CFG_SINGLE_CHANNEL == 1)
 #define IICA_REG                             R_IICA1
#elif (IICA_SLAVE_CFG_SINGLE_CHANNEL == 0)
 #define IICA_REG                             R_IICA0
#else
 #define IICA_REG                             p_ctrl->p_reg
#endif

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private function prototypes
 *********************************************************************************************************************/
void iica_slave_txrxi_isr(void);

/* Internal helper functions */
static fsp_err_t r_iica_slave_read_write(i2c_slave_ctrl_t * const p_api_ctrl,
                                         uint8_t * const          p_buffer,
                                         uint32_t const           bytes);
static void r_iica_slave_call_callback(iica_slave_instance_ctrl_t * p_ctrl, i2c_slave_event_t event);

/* Functions that manipulate hardware */
static void r_iica_open_hw_slave(iica_slave_instance_ctrl_t * const p_ctrl);

/* Interrupt handler */
static void r_iica_txrxi_slave(iica_slave_instance_ctrl_t * p_ctrl);

/**********************************************************************************************************************
 * Private global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Global variables
 *********************************************************************************************************************/

/* IICA Implementation of IICA device slave interface */
i2c_slave_api_t const g_iica_slave_on_iica =
{
    .open        = R_IICA_SLAVE_Open,
    .read        = R_IICA_SLAVE_Read,
    .write       = R_IICA_SLAVE_Write,
    .close       = R_IICA_SLAVE_Close,
    .callbackSet = R_IICA_SLAVE_CallbackSet
};

/*******************************************************************************************************************/ /**
 * @addtogroup IICA_SLAVE
 * @{
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Functions
 *********************************************************************************************************************/

/******************************************************************************************************************/ /**
 * Opens the IICA slave device.
 *
 * @retval  FSP_SUCCESS                       IICA slave device opened successfully.
 * @retval  FSP_ERR_ALREADY_OPEN              Module is already open.
 * @retval  FSP_ERR_IP_CHANNEL_NOT_PRESENT    Channel is not available on this MCU.
 * @retval  FSP_ERR_ASSERTION                 Parameter check failure due to one or more reasons below:
 *                                            1. p_api_ctrl or p_cfg is NULL.
 *                                            2. extended parameter is NULL.
 *                                            3. Callback parameter is NULL.
 *                                            4. Invalid IRQ number assigned
 *********************************************************************************************************************/
fsp_err_t R_IICA_SLAVE_Open (i2c_slave_ctrl_t * const p_api_ctrl, i2c_slave_cfg_t const * const p_cfg)
{
    iica_slave_instance_ctrl_t * p_ctrl = (iica_slave_instance_ctrl_t *) p_api_ctrl;

#if IICA_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_cfg != NULL);
    FSP_ASSERT(p_cfg->p_extend != NULL);
    FSP_ASSERT(p_cfg->tei_irq >= (IRQn_Type) 0);

    FSP_ERROR_RETURN(IICA_SLAVE_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_IIC_VALID_CHANNEL_MASK & (1 << p_cfg->channel), FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif
#if IICA_SLAVE_CFG_SINGLE_CHANNEL == -1
    p_ctrl->p_reg =
        (R_IICA0_Type *) ((uint32_t) R_IICA0 + (p_cfg->channel * ((uint32_t) R_IICA1 - (uint32_t) R_IICA0)));
#endif

    /* Record the configuration on the device for use later */
    p_ctrl->p_cfg      = p_cfg;
    p_ctrl->p_callback = p_cfg->p_callback;
    p_ctrl->p_context  = p_cfg->p_context;
    p_ctrl->addr_mode  = p_cfg->addr_mode;

    p_ctrl->p_buff = NULL;
    p_ctrl->total  = 0U;
    p_ctrl->loaded = 0U;

    R_BSP_MODULE_START(FSP_IP_IICA, p_cfg->channel);

    /* Open the hardware in slave mode. Performs IICA initialization as described in hardware manual (see Section 22.4.16
     * Initial Settings for slave mode of the manual). */
    r_iica_open_hw_slave(p_ctrl);

    p_ctrl->open = IICA_SLAVE_OPEN;

    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->tei_irq, p_ctrl->p_cfg->ipl, p_ctrl);

    return FSP_SUCCESS;
}

/******************************************************************************************************************/ /**
 * Performs a read from the IICA Master device.
 *
 * This function will fail if there is already an in-progress IICA transfer on the associated channel. Otherwise, the
 * IICA slave read operation will begin. The caller will be notified when the operation has finished by an
 * I2C_SLAVE_EVENT_RX_COMPLETE in the callback.
 * In case the master continues to write more data, an I2C_SLAVE_EVENT_RX_MORE_REQUEST will be issued via callback.
 * In case of errors, an I2C_SLAVE_EVENT_ABORTED will be issued via callback.
 *
 * @retval  FSP_SUCCESS        Function executed without issue
 * @retval  FSP_ERR_ASSERTION  p_api_ctrl, bytes or p_dest is NULL.
 * @retval  FSP_ERR_IN_USE     Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN   Device is not open.
 *********************************************************************************************************************/
fsp_err_t R_IICA_SLAVE_Read (i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
#if IICA_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif

    fsp_err_t err = FSP_SUCCESS;

    err = r_iica_slave_read_write(p_api_ctrl, p_dest, bytes);

    return err;
}

/******************************************************************************************************************/ /**
 * Performs a write to the IICA Master device.
 *
 * This function will fail if there is already an in-progress IICA transfer on the associated channel. Otherwise, the
 * IICA slave write operation will begin. The caller will be notified when the operation has finished by an
 * I2C_SLAVE_EVENT_TX_COMPLETE in the callback.
 * In case the master continues to read more data, an I2C_SLAVE_EVENT_TX_MORE_REQUEST will be issued via callback.
 * In case of errors, an I2C_SLAVE_EVENT_ABORTED will be issued via callback.
 *
 * @retval  FSP_SUCCESS        Function executed without issue.
 * @retval  FSP_ERR_ASSERTION  p_api_ctrl or p_src is NULL.
 * @retval  FSP_ERR_IN_USE     Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN   Device is not open.
 *********************************************************************************************************************/
fsp_err_t R_IICA_SLAVE_Write (i2c_slave_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
#if IICA_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_api_ctrl != NULL);
#endif

    fsp_err_t err = FSP_SUCCESS;

    err = r_iica_slave_read_write(p_api_ctrl, p_src, bytes);

    return err;
}

/*******************************************************************************************************************/ /**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements i2c_slave_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 **********************************************************************************************************************/
fsp_err_t R_IICA_SLAVE_CallbackSet (i2c_slave_ctrl_t * const          p_api_ctrl,
                                    void (                          * p_callback)(i2c_slave_callback_args_t *),
                                    void * const                      p_context,
                                    i2c_slave_callback_args_t * const p_callback_memory)
{
    iica_slave_instance_ctrl_t * p_ctrl = (iica_slave_instance_ctrl_t *) p_api_ctrl;

#if (IICA_SLAVE_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ASSERT(p_callback_memory == NULL);
    FSP_ERROR_RETURN(IICA_SLAVE_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    /* Store callback and context */
    p_ctrl->p_callback = p_callback;
    p_ctrl->p_context  = p_context;

    return FSP_SUCCESS;
}

/******************************************************************************************************************/ /**
 * Closes the IICA device.
 *
 * @retval  FSP_SUCCESS         Device closed successfully.
 * @retval  FSP_ERR_NOT_OPEN    Device not opened.
 * @retval  FSP_ERR_ASSERTION   p_api_ctrl is NULL.
 *********************************************************************************************************************/
fsp_err_t R_IICA_SLAVE_Close (i2c_slave_ctrl_t * const p_api_ctrl)
{
    iica_slave_instance_ctrl_t * p_ctrl = (iica_slave_instance_ctrl_t *) p_api_ctrl;

#if IICA_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);

    /* Check if the device is even open, return an error if not */
    FSP_ERROR_RETURN(IICA_SLAVE_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* The device is now considered closed */
    p_ctrl->open = 0U;

    /* Disable all interrupts in NVIC */
    R_BSP_IrqDisable(p_ctrl->p_cfg->tei_irq);

    R_BSP_MODULE_STOP(FSP_IP_IICA, p_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/******************************************************************************************************************/ /**
 * @} (end addtogroup IICA_SLAVE)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private Functions
 *********************************************************************************************************************/

/*******************************************************************************************************************/ /**
 * Helper function for handling IICA Slave Read or Write.
 *
 * @param      p_api_ctrl         Pointer to the control structure.
 * @param      p_buffer           Pointer to the buffer to store read/write data.
 * @param[in]  bytes              Number of bytes to be read/written.
 *
 * @retval  FSP_SUCCESS           Function executed successfully.
 * @retval  FSP_ERR_ASSERTION     p_api_ctrl or p_buffer is NULL.
 *
 * @retval  FSP_ERR_IN_USE        Another transfer was in progress.
 * @retval  FSP_ERR_NOT_OPEN      Handle is not initialized. Call R_IICA_SLAVE_Open to initialize the control block.
 **********************************************************************************************************************/
static fsp_err_t r_iica_slave_read_write (i2c_slave_ctrl_t * const p_api_ctrl,
                                          uint8_t * const          p_buffer,
                                          uint32_t const           bytes)
{
    iica_slave_instance_ctrl_t * p_ctrl = (iica_slave_instance_ctrl_t *) p_api_ctrl;

#if IICA_SLAVE_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl != NULL);
    FSP_ASSERT(p_buffer != NULL);

    /* Check if the device is even open, return an error if not */
    FSP_ERROR_RETURN(IICA_SLAVE_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Fail if there is already a transfer in progress */
    FSP_ERROR_RETURN(0 == p_ctrl->total, FSP_ERR_IN_USE);

    FSP_ASSERT(((iica_slave_instance_ctrl_t *) p_api_ctrl)->p_callback != NULL);
#endif

    /* Record the new information about this transfer */
    p_ctrl->p_buff = p_buffer;
    p_ctrl->total  = bytes;
    p_ctrl->loaded = 0U;

    return FSP_SUCCESS;
}

/******************************************************************************************************************/ /**
 * Performs the hardware initialization sequence when operating as a slave (see Section 22.4.16
 * Initial setting for slave mode of the manual).
 *
 * @param[in]       p_ctrl     Pointer to the control structure.
 *********************************************************************************************************************/
static void r_iica_open_hw_slave (iica_slave_instance_ctrl_t * const p_ctrl)
{
    iica_slave_extended_cfg_t * pextend = (iica_slave_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    uint8_t iicctl01 = 0;

    /* Select a transfer clock */
    IICA_REG->IICWL0 = pextend->clock_settings.iicwl_value;
    IICA_REG->IICWH0 = pextend->clock_settings.iicwh_value;

    if (p_ctrl->addr_mode == I2C_SLAVE_ADDR_MODE_7BIT)
    {
        IICA_REG->SVA0 = (uint8_t) (p_ctrl->p_cfg->slave << 1U);
    }

#if IICA_SLAVE_CFG_ADDR_MODE_10_BIT_ENABLE
    else
    {
        /* 10 bit mode selected */
        p_ctrl->tenbitaddr_matched = false;
        IICA_REG->SVA0             =
            (uint8_t) ((((uint32_t) ((p_ctrl->p_cfg->slave >> 8U)) << 1U)) | I2C_CODE_10BIT);
    }
#endif

    /* Enable communication reservation */
    IICA_REG->IICF0 = IICA_SLAVE_IICF0_STCEN_IICRSV_MASK;

    /* IICCTL01 Register Settings */
    /* Set IICA operation clock and digital filter */
    /* Set operation mode */
    if (p_ctrl->p_cfg->rate == I2C_SLAVE_RATE_STANDARD)
    {
        iicctl01 =
            (uint8_t) ((pextend->clock_settings.operation_clock) | (pextend->clock_settings.digital_filter << 2));
    }
    else
    {
        iicctl01 =
            (uint8_t) ((pextend->clock_settings.operation_clock) | (pextend->clock_settings.digital_filter << 2) |
                       (uint8_t) R_IICA0_IICCTL01_SMC_Msk);
    }

    IICA_REG->IICCTL01 = iicctl01;

    /* IICCTL00 Register Settings:
     * 1. ACKE = 1：Enable acknowledgment. During the 9th clock period, the SDAA0 line is set to low level.
     * 2. WTIM = 1：An interrupt request is generated on the falling edge of the 9th clock cycle.
     * 3. SPIE = 0：Disable and disable generation of interrupt request when stop condition is detected
     * 4. IICE = 1：Enable IICA operation.
     * 5. LREL = 1：Exit from Communications.
     */
    IICA_REG->IICCTL00 = IICA_SLAVE_IICCTL00_INIT;

    /* Configure Pin settings */
    R_BSP_PinAccessEnable();
    R_BSP_PinCfg(pextend->scl_pin_settings.pin, pextend->scl_pin_settings.cfg);
    R_BSP_PinCfg(pextend->sda_pin_settings.pin, pextend->sda_pin_settings.cfg);
    R_BSP_PinAccessDisable();
}

/*******************************************************************************************************************/ /**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to iic slave instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_iica_slave_call_callback (iica_slave_instance_ctrl_t * p_ctrl, i2c_slave_event_t event)
{
    i2c_slave_callback_args_t args;

    args.bytes     = p_ctrl->total_loaded;
    args.event     = event;
    args.p_context = p_ctrl->p_context;

    /* p_ctrl->total is used to check whether I2C is busy or not. */
    p_ctrl->total = 0;

    p_ctrl->p_callback(&args);
}

/******************************************************************************************************************/ /**
 * Handles the transmit interrupt when operating as a slave.
 *
 * @param[in]       p_ctrl     The target IICA block's control block.
 *********************************************************************************************************************/
static void r_iica_txrxi_slave (iica_slave_instance_ctrl_t * p_ctrl)
{
    uint8_t iics0_val = IICA_REG->IICS0;

    /* Stop condition detected */
    if (iics0_val & R_IICA0_IICS0_SPD_Msk)
    {
        if (p_ctrl->communication_mode)
        {
            p_ctrl->communication_mode = 0U;
            IICA_REG->IICCTL00_b.SPIE  = 0U;

            i2c_slave_event_t i2c_event = p_ctrl->communication_dir ==
                                          0 ? I2C_SLAVE_EVENT_RX_COMPLETE : I2C_SLAVE_EVENT_TX_COMPLETE;

            r_iica_slave_call_callback(p_ctrl, i2c_event);
        }

        return;
    }

    if (iics0_val & R_IICA0_IICS0_STD_Msk)
    {
#if IICA_SLAVE_CFG_ADDR_MODE_GENERAL_CALL_ENABLE
        if ((iics0_val & R_IICA0_IICS0_EXC_Msk) && (IICA_REG->IICA0 == 0))
        {
            r_iica_slave_call_callback(p_ctrl, I2C_SLAVE_EVENT_GENERAL_CALL);
            p_ctrl->communication_mode = 1U;
            IICA_REG->IICCTL00        |= IICA_SLAVE_IICCTL00_SPIE_WREL_MASK;

            return;
        }
#endif

        if (iics0_val & R_IICA0_IICS0_COI_Msk)
        {
            p_ctrl->total_loaded      = 0;
            p_ctrl->communication_dir = iics0_val & R_IICA0_IICS0_TRC_Msk;
            if (0U == p_ctrl->communication_dir)
            {
                /* Avoid enter callback again after detection of extension code */
#if IICA_SLAVE_CFG_ADDR_MODE_10_BIT_ENABLE
                if (p_ctrl->addr_mode == I2C_SLAVE_ADDR_MODE_10BIT)
                {
                    p_ctrl->tenbitaddr_matched = false;
                }
                else
#endif
                {
                    r_iica_slave_call_callback(p_ctrl, I2C_SLAVE_EVENT_RX_REQUEST);
                }

                p_ctrl->communication_mode = 1U;
                IICA_REG->IICCTL00        |= IICA_SLAVE_IICCTL00_SPIE_WREL_MASK;

                return;
            }

#if IICA_SLAVE_CFG_ADDR_MODE_10_BIT_ENABLE
            if ((p_ctrl->addr_mode == I2C_SLAVE_ADDR_MODE_10BIT) && !p_ctrl->tenbitaddr_matched)
            {
                IICA_REG->IICCTL00_b.LREL = 1;

                return;
            }
#endif

            /* Avoid enter callback again after detection of extension code */
            if (!((iics0_val & IICA_SLAVE_IICS0_EXC_ACKD_MASK) == IICA_SLAVE_IICS0_EXC_ACKD_MASK))
            {
                r_iica_slave_call_callback(p_ctrl, I2C_SLAVE_EVENT_TX_REQUEST);
                p_ctrl->communication_mode = 1U;
            }
        }
        else
        {
            IICA_REG->IICCTL00_b.LREL = 1;

            return;
        }
    }

    if (p_ctrl->communication_mode)
    {
        if (p_ctrl->communication_dir && !(iics0_val & R_IICA0_IICS0_ACKD_Msk))
        {
            // Release clock stretch and enable interrupt when generate a stop condition
            IICA_REG->IICCTL00 |= IICA_SLAVE_IICCTL00_SPIE_WREL_MASK;

            return;
        }

#if IICA_SLAVE_CFG_ADDR_MODE_10_BIT_ENABLE
        if (p_ctrl->addr_mode == I2C_SLAVE_ADDR_MODE_10BIT)
        {
            if (!p_ctrl->tenbitaddr_matched)
            {
                if (IICA_REG->IICA0 == (uint8_t) (p_ctrl->p_cfg->slave))
                {
                    p_ctrl->tenbitaddr_matched = true;
                    IICA_REG->IICCTL00_b.WREL  = 1;
                }
                else
                {
                    p_ctrl->communication_mode = 0U;
                    IICA_REG->IICCTL00_b.LREL  = 1;
                }

                return;
            }

            if (!p_ctrl->communication_dir && (0 == p_ctrl->total_loaded))
            {
                r_iica_slave_call_callback(p_ctrl, I2C_SLAVE_EVENT_RX_REQUEST);
            }
        }
#endif

        /* Notify application when buffer is full/no more data to send */
        if (p_ctrl->loaded == p_ctrl->total)
        {
            i2c_slave_event_t i2c_event =
                (0 == p_ctrl->communication_dir) ? I2C_SLAVE_EVENT_RX_MORE_REQUEST : I2C_SLAVE_EVENT_TX_MORE_REQUEST;
            r_iica_slave_call_callback(p_ctrl, i2c_event);
        }

        /* User wants to abort by setting total to 0. There will be no more callback as user knows the communication is aborted. */
        if (0U == p_ctrl->total)
        {
            IICA_REG->IICCTL00 = IICA_SLAVE_IICCTL00_INIT;

            return;
        }

        if (p_ctrl->communication_dir)
        {
            IICA_REG->IICA0 = p_ctrl->p_buff[p_ctrl->loaded];
        }
        else
        {
            /* Read data */
            p_ctrl->p_buff[p_ctrl->loaded] = IICA_REG->IICA0;
            IICA_REG->IICCTL00_b.WREL      = 1;
        }

        p_ctrl->loaded++;
        p_ctrl->total_loaded++;
    }
}

/*******************************************************************************************************************/ /**
 * Transmit end interrupt routine.
 *
 * This function implements the IIC Transmission End ISR routine.
 *
 ***********************************************************************************************************************/

void iica_slave_txrxi_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    iica_slave_instance_ctrl_t * p_ctrl = (iica_slave_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    r_iica_txrxi_slave(p_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
