/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include <string.h>
#include "bsp_api.h"
#include "r_ioport.h"
#include "renesashw.h"

extern ethercat_ssc_port_instance_t const * gp_ethercat_ssc_port;

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/** "ECAT" in ASCII, used to determine if channel is open. */
#define ETHERCAT_SSC_PORT_OPEN                      (('E' << 24U) | ('C' << 16U) | ('A' << 8U) | ('T' << 0U))

/** Detect type of the interrupt  */
#define ETHERCAT_SSC_PORT_IRQ_TYPE_EDGE_RISE        (0U)     /* rising edge-triggerd */

/* ESC EEPROM status */
#define ETHERCAT_SSC_PORT_EEPROM_MASK_STATE         (0x2800) /* error check mask */
#define ETHERCAT_SSC_PORT_EEPROM_ERROR_BLANK        (0x0800) /* active-HIGH level */
#define ETHERCAT_SSC_PORT_EEPROM_ERROR_I2CBUS       (0x2800) /* rising edge-triggerd */

/* ESC reset */
#define ETHERCAT_SSC_PORT_RESET                     (0U)
#define ETHERCAT_SSC_PORT_RESET_RELEASE             (1U)

/* Initial value of down counter for timeout detection */
#define ETHERCAT_SSC_PORT_EEPROMLOADING_TIMEOUT     (1000000000)

/* Max value of system timer */
#define ETHERCAT_SSC_PORT_MAX_VALUE_SYSTEM_TIMER    (0xFFFF)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (ETHERCAT_SSC_PORT_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t ethercat_ssc_port_open_param_check(ethercat_ssc_port_instance_ctrl_t const * const p_instance_ctrl,
                                                    ethercat_ssc_port_cfg_t const * const           p_cfg);

#endif

static void ethercat_ssc_port_close_phy(ethercat_ssc_port_ctrl_t * const p_ctrl);
static void ethercat_ssc_port_close_timer(ethercat_ssc_port_ctrl_t * const p_ctrl);
static void ethercat_ssc_port_enable_icu(ethercat_ssc_port_ctrl_t * const p_ctrl);
static void ethercat_ssc_port_disable_icu(ethercat_ssc_port_ctrl_t * const p_ctrl);

static fsp_err_t ethercat_ssc_port_loading_eeprom(void * const p_reg_base);

void ethercat_ssc_port_isr_esc_cat(void);
void ethercat_ssc_port_isr_esc_sync0(void);
void ethercat_ssc_port_isr_esc_sync1(void);

__attribute__((weak)) void PDI_Isr(void);

__attribute__((weak)) void Sync0_Isr(void);

__attribute__((weak)) void Sync1_Isr(void);

void ethercat_ssc_port_timer_callback(timer_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** ETHERCAT SSC PORT API mapping for ETHECAT SSC PORT interface */
const ethercat_ssc_port_api_t g_ethercat_ssc_port_on_ethercat_ssc_port =
{
    .open  = RM_ETHERCAT_SSC_PORT_Open,
    .close = RM_ETHERCAT_SSC_PORT_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_ETHERCAT_SSC_PORT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * @brief EtherCAT Slave Controller is initialized with this function.
 * This function includes PHY initialization and ESC EEPROM loading.
 * Afterwards, EtherCAT communication begins.
 * Also EtherCAT interrupts are permitted if the interrupts are used.
 * In order to receive the EtherCAT, EtherCAT Sync0, EtherCAT Sync1 interrupt event,
 * it's necessary to register a callback function.
 * Implements @ref ethercat_ssc_port_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Opened successfully
 * @retval  FSP_ERR_ASSERTION                       A required input pointer is NULL
 * @retval  FSP_ERR_ALREADY_OPEN                    Control block has already been opened
 * @retval  FSP_ERR_INVALID_ARGUMENT                Irq number lower then 0.
 * @retval  FSP_ERR_INVALID_HW_CONDITION            ESC EEPROM loading error
 * @retval  FSP_ERR_TIMEOUT                         ESC EEPROM loading timeout error
 ***********************************************************************************************************************/
fsp_err_t RM_ETHERCAT_SSC_PORT_Open (ethercat_ssc_port_ctrl_t * const      p_ctrl,
                                     ethercat_ssc_port_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    ethercat_ssc_port_extend_cfg_t    * p_extend;

    R_ESC_INI_Type * p_reg_esc_ini = (R_ESC_INI_Type *) R_ESC_INI_BASE;
    R_ESC_Type     * p_reg_esc     = (R_ESC_Type *) R_ESC_BASE;

    uint32_t               i;
    uint32_t               ecatdbgc;
    bool                   opened_phy[BSP_FEATURE_ESC_NUM_PORTS] = {false};
    bool                   opened_timer = false;
    ether_phy_instance_t * p_ether_phy_instance;
    timer_instance_t     * p_timer_instance;

#if (ETHERCAT_SSC_PORT_CFG_PARAM_CHECKING_ENABLE)

    /** Check parameters. */
    err = ethercat_ssc_port_open_param_check(p_instance_ctrl, p_cfg); /** check arguments */
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);
#endif

    p_instance_ctrl->p_reg_esc_ini = (void *) p_reg_esc_ini;
    p_instance_ctrl->p_reg_esc     = (void *) p_reg_esc;

    p_instance_ctrl->p_cfg = p_cfg;
    p_extend               = (ethercat_ssc_port_extend_cfg_t *) p_cfg->p_extend;

    /* Power on ESC  */
    R_MSTP->MSTPCRC_b.MSTPC29 = 0;

    /* Power on Ether PHY Clock */
    R_MSTP->MSTPCRC_b.MSTPC28 = 0;

    /* Set PHY address offset */
    p_reg_esc_ini->ECATOFFADR = p_instance_ctrl->p_cfg->address_offset;

    /* Set EEPROM size */
    p_reg_esc_ini->ECATOPMOD = (uint32_t) p_extend->eeprom_size;

    /* Set TX signal delay time */
    ecatdbgc =
        (uint32_t) ((p_extend->tx_signal_delay_port1 << 2) | (p_extend->tx_signal_delay_port0 << 0));
    p_reg_esc_ini->ECATDBGC = ecatdbgc;

    /* Set PHY link polarity */
    p_reg_esc_ini->PHYLINK_b.LINKPOL0 = ETHERCAT_SSC_PORT_CFG_CAT0_LINKSTA_POL;
    p_reg_esc_ini->PHYLINK_b.LINKPOL1 = ETHERCAT_SSC_PORT_CFG_CAT1_LINKSTA_POL;

    /* ESC Reset */
    p_reg_esc_ini->ESCRST_b.PHYRST = ETHERCAT_SSC_PORT_RESET;
    p_reg_esc_ini->ESCRST_b.ESCRST = ETHERCAT_SSC_PORT_RESET;

    /* Reset hold time */
    R_BSP_SoftwareDelay(p_instance_ctrl->p_cfg->reset_hold_time, BSP_DELAY_UNITS_MILLISECONDS);

    /* ESC Reset release*/
    p_reg_esc_ini->ESCRST_b.ESCRST = ETHERCAT_SSC_PORT_RESET_RELEASE;

    /* Wait for 4 cycles to access next register */
    __asm volatile (
        "nop \n"
        "nop \n"
        "nop \n"
        "nop \n"
        );

    /* Write High-output to ESC_RESETOUT# as release */
    p_reg_esc_ini->ESCRST_b.PHYRST = ETHERCAT_SSC_PORT_RESET_RELEASE;

    /* Wait Loading ESC EEPROM */
    err = ethercat_ssc_port_loading_eeprom(p_reg_esc);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);

    /* Wait after reset */
    R_BSP_SoftwareDelay(p_instance_ctrl->p_cfg->reset_wait_time, BSP_DELAY_UNITS_MICROSECONDS);

    /* Open EtherCAT-Phy Driver */
    for (i = 0; BSP_FEATURE_ESC_NUM_PORTS > i; i++)
    {
        p_ether_phy_instance = (ether_phy_instance_t *) p_extend->p_ether_phy_instance[i];
        if (NULL != p_ether_phy_instance)
        {
            p_ether_phy_instance->p_api->open(p_ether_phy_instance->p_ctrl, p_ether_phy_instance->p_cfg);
            err = p_ether_phy_instance->p_api->chipInit(p_ether_phy_instance->p_ctrl, p_ether_phy_instance->p_cfg);
            if (FSP_SUCCESS == err)
            {
                opened_phy[i] = true;
            }
            else
            {
                opened_phy[i] = false;
                break;
            }
        }
    }

    /* Open Timer driver */
    if (FSP_SUCCESS == err)
    {
        p_timer_instance = (timer_instance_t *) p_cfg->p_timer_instance;
        err              = p_timer_instance->p_api->open(p_timer_instance->p_ctrl, p_timer_instance->p_cfg);
        if (FSP_SUCCESS == err)
        {
            opened_timer = true;
            err          = p_timer_instance->p_api->callbackSet(p_timer_instance->p_ctrl,
                                                                ethercat_ssc_port_timer_callback,
                                                                p_instance_ctrl,
                                                                NULL);
            if (FSP_SUCCESS == err)
            {
                p_instance_ctrl->sys_time = 0;
                err = p_timer_instance->p_api->start(p_timer_instance->p_ctrl);
            }
        }
    }

    if (FSP_SUCCESS == err)
    {
        /** Enable EtherCAT interrupts */
        ethercat_ssc_port_enable_icu(p_instance_ctrl);
        p_instance_ctrl->open = ETHERCAT_SSC_PORT_OPEN;
    }
    else
    {
        /* Close Timer driver */
        if (true == opened_timer)
        {
            ethercat_ssc_port_close_timer(p_instance_ctrl);
        }

        /* Close PHY driver */
        if (true == opened_phy[0])
        {
            ethercat_ssc_port_close_phy(p_instance_ctrl);
        }
    }

    return err;
}                                      /* End of function RM_ETHERCAT_SSC_PORT_Open() */

/********************************************************************************************************************//**
 * Disables interrupts. Removes power and releases hardware lock. Implements @ref ethercat_ssc_port_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to the control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t RM_ETHERCAT_SSC_PORT_Close (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;

#if (ETHERCAT_SSC_PORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(ETHERCAT_SSC_PORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable EtherCAT interrupt. */
    ethercat_ssc_port_disable_icu(p_instance_ctrl);

    /* Close Timer driver */
    ethercat_ssc_port_close_timer(p_instance_ctrl);

    /* Close PHY driver */
    ethercat_ssc_port_close_phy(p_instance_ctrl);

    /** Clear configure block parameters. */
    p_instance_ctrl->p_cfg = NULL;

    /** Reset base time of EtherCAT. */
    p_instance_ctrl->sys_time = 0;

    /** Mark the channel not open so other APIs cannot use it. */
    p_instance_ctrl->open = 0U;

    return err;
}                                      /* End of function RM_ETHERCAT_SSC_PORT_Close() */

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHERCAT_SSC_PORT)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if (ETHERCAT_SSC_PORT_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * @brief Parameter error check function for open.
 *
 * @param[in] p_instance_ctrl   Pointer to the control block
 * @param[in] p_cfg             Pointer to the configuration structure
 *
 * @retval  FSP_SUCCESS                  No parameter error found
 * @retval  FSP_ERR_ASSERTION            A required input pointer is NULL
 * @retval  FSP_ERR_ALREADY_OPEN         Control block has already been opened
 * @retval  FSP_ERR_INVALID_ARGUMENT     Irq number lower then 0.
 **********************************************************************************************************************/
static fsp_err_t ethercat_ssc_port_open_param_check (ethercat_ssc_port_instance_ctrl_t const * const p_instance_ctrl,
                                                     ethercat_ssc_port_cfg_t const * const           p_cfg)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);

    /* Check timer driver instance */
    FSP_ASSERT(NULL != p_cfg->p_timer_instance);

    /* Check IRQ number */
    FSP_ERROR_RETURN((0 <= p_cfg->common_irq), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0 <= p_cfg->sync0_irq), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((0 <= p_cfg->sync1_irq), FSP_ERR_INVALID_ARGUMENT);

    FSP_ERROR_RETURN((ETHERCAT_SSC_PORT_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Function Name: ethercat_ssc_port_isr_esc_cat
 * Description  : Interrupt handler for EtherCAT interrupts.
 * Arguments    : none
 * Return Value : none
 **********************************************************************************************************************/
void ethercat_ssc_port_isr_esc_cat (void)
{
    ethercat_ssc_port_callback_args_t callback_arg;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl =
        (ethercat_ssc_port_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
    R_BSP_IrqClearPending(irq);

    /* SSC ESC CAT Interrupt handler */
    PDI_Isr();

    /* Callback : Interrupt handler */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        callback_arg.event     = ETHERCAT_SSC_PORT_EVENT_ESC_CAT_INTERRUPT;
        callback_arg.p_context = p_instance_ctrl->p_cfg->p_context;

        (*p_instance_ctrl->p_cfg->p_callback)((void *) &callback_arg);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}                                      /* End of function ethercat_ssc_port_isr_esc_cat() */

/*******************************************************************************************************************//**
 * Function Name: ethercat_ssc_port_isr_esc_sync0
 * Description  : Interrupt handler for EtherCAT Sync0 interrupts.
 * Arguments    : none
 * Return Value : none
 **********************************************************************************************************************/
void ethercat_ssc_port_isr_esc_sync0 (void)
{
    ethercat_ssc_port_callback_args_t callback_arg;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl =
        (ethercat_ssc_port_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
    R_BSP_IrqClearPending(irq);

    /* SSC ESC SYNC0 Interrupt handler */
    Sync0_Isr();

    /* Callback : Interrupt handler */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        callback_arg.event     = ETHERCAT_SSC_PORT_EVENT_ESC_SYNC0_INTERRUPT;
        callback_arg.p_context = p_instance_ctrl->p_cfg->p_context;

        (*p_instance_ctrl->p_cfg->p_callback)((void *) &callback_arg);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}                                      /* End of function ethercat_ssc_port_isr_esc_sync0() */

/*******************************************************************************************************************//**
 * Function Name: ethercat_ssc_port_isr_esc_sync1
 * Description  : Interrupt handler for EtherCAT Sync1 interrupts.
 * Arguments    : none
 * Return Value : none
 **********************************************************************************************************************/
void ethercat_ssc_port_isr_esc_sync1 (void)
{
    ethercat_ssc_port_callback_args_t callback_arg;

    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl =
        (ethercat_ssc_port_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
    R_BSP_IrqClearPending(irq);

    /* SSC ESC SYNC1 Interrupt handler */
    Sync1_Isr();

    /* Callback : Interrupt handler */
    if (NULL != p_instance_ctrl->p_cfg->p_callback)
    {
        callback_arg.event     = ETHERCAT_SSC_PORT_EVENT_ESC_SYNC1_INTERRUPT;
        callback_arg.p_context = p_instance_ctrl->p_cfg->p_context;

        (*p_instance_ctrl->p_cfg->p_callback)((void *) &callback_arg);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}                                      /* End of function ethercat_ssc_port_isr_esc_sync1() */

/*******************************************************************************************************************//**
 * Close all Ethernet PHY driver
 *
 * @param[in] p_ctrl   Pointer to the control block for the Ethernet PHY driver
 *
 * @retval      none
 **********************************************************************************************************************/
static void ethercat_ssc_port_close_phy (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    uint8_t                             i;
    ether_phy_instance_t              * p_ether_phy_instance;
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    ethercat_ssc_port_cfg_t           * p_cfg           = (ethercat_ssc_port_cfg_t *) p_instance_ctrl->p_cfg;
    ethercat_ssc_port_extend_cfg_t    * p_extend        = (ethercat_ssc_port_extend_cfg_t *) p_cfg->p_extend;

    for (i = 0; BSP_FEATURE_ESC_NUM_PORTS > i; i++)
    {
        p_ether_phy_instance = (ether_phy_instance_t *) p_extend->p_ether_phy_instance[i];
        if (NULL != p_ether_phy_instance)
        {
            p_ether_phy_instance->p_api->close(p_ether_phy_instance->p_ctrl);
        }
    }
}                                      /* End of function ethercat_ssc_port_close_phy() */

/*******************************************************************************************************************//**
 * Close timer driver
 *
 * @param[in] p_ctrl   Pointer to the control block for the timer driver
 *
 * @retval      none
 **********************************************************************************************************************/
static void ethercat_ssc_port_close_timer (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    timer_instance_t * p_timer_instance;
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    ethercat_ssc_port_cfg_t           * p_cfg           = (ethercat_ssc_port_cfg_t *) p_instance_ctrl->p_cfg;

    p_timer_instance = (timer_instance_t *) p_cfg->p_timer_instance;
    p_timer_instance->p_api->stop(p_timer_instance->p_ctrl);
    p_timer_instance->p_api->close(p_timer_instance->p_ctrl);
}                                      /* End of function ethercat_ssc_port_close_timer() */

/*******************************************************************************************************************//**
 * Enable ICU
 *
 * @param[in] p_ctrl   Pointer to the control block for the channel
 *
 * @retval      none
 **********************************************************************************************************************/
static void ethercat_ssc_port_enable_icu (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    R_ESC_INI_Type * p_reg_esc_ini = p_instance_ctrl->p_reg_esc_ini;

    /* Configure the EtherCAT interrupt. */
    R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->common_irq, p_instance_ctrl->p_cfg->common_ipl, p_instance_ctrl);

    /* Set Detect type */
    p_reg_esc_ini->ESCICR_b.SYNC0C = ETHERCAT_SSC_PORT_IRQ_TYPE_EDGE_RISE;

    /* Configure the EtherCAT SYNC0 interrupt. */
    R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->sync0_irq, p_instance_ctrl->p_cfg->sync0_ipl, p_instance_ctrl);

    /* Set Detect type */
    p_reg_esc_ini->ESCICR_b.SYNC1C = ETHERCAT_SSC_PORT_IRQ_TYPE_EDGE_RISE;

    /* Configure the EtherCAT SYNC1 interrupt. */
    R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->sync1_irq, p_instance_ctrl->p_cfg->sync1_ipl, p_instance_ctrl);
}                                      /* End of function ethercat_ssc_port_enable_icu() */

/*******************************************************************************************************************//**
 * Disable ICU
 *
 * @param[in] p_ctrl   Pointer to the control block for the channel
 *
 * @retval      none
 **********************************************************************************************************************/
static void ethercat_ssc_port_disable_icu (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;

    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->common_irq);
    R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->common_irq, NULL);

    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->sync0_irq);
    R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->sync0_irq, NULL);

    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->sync1_irq);
    R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->sync1_irq, NULL);
}                                      /* End of function ethercat_ssc_port_disable_icu() */

/*******************************************************************************************************************//**
 * Loading ESC EEPROM
 * EtherCAT communication is possible even if the EEPROM is blank, so no error code is returned.
 *
 * @param[in] p_reg_base   Pointer to the ESC register base address
 *
 * @retval  FSP_SUCCESS                             EEPROM loading successfully or Invalid data in EEPROM including blank
 * @retval  FSP_ERR_INVALID_HW_CONDITION            The error of I2C bus which connectors to EEPROM
 * @retval  FSP_ERR_TIMEOUT                         EEPROM loading timeout error
 **********************************************************************************************************************/
static fsp_err_t ethercat_ssc_port_loading_eeprom (void * const p_reg_base)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  timeout;
    uint16_t  eeprom_error_status;

    R_ESC_Type * p_reg_esc = (R_ESC_Type *) p_reg_base;

    timeout = ETHERCAT_SSC_PORT_EEPROMLOADING_TIMEOUT;

    while (1)
    {
        if (1 == p_reg_esc->ESC_DL_STATUS_b.PDIOPE)
        {
            err = FSP_SUCCESS;
            break;                                                        /* Loading successful, PDI operations */
        }

        eeprom_error_status = p_reg_esc->EEP_CONT_STAT & ETHERCAT_SSC_PORT_EEPROM_MASK_STATE;
        if (ETHERCAT_SSC_PORT_EEPROM_ERROR_BLANK == eeprom_error_status)  /* ACMDERR,CKSUMERR = 01 */
        {
            err = FSP_SUCCESS;
            break;                                                        /* EEPROM is loaded, but it is blank */
        }

        if (ETHERCAT_SSC_PORT_EEPROM_ERROR_I2CBUS == eeprom_error_status) /* ACMDERR,CKSUMERR = 11 */
        {
            err = FSP_ERR_INVALID_HW_CONDITION;
            break;                                                        /* I2C bus error */
        }

        if (0 == timeout)                                                 /* Timeout */
        {
            err = FSP_ERR_TIMEOUT;
            break;                                                        /* Timeout error */
        }

        timeout--;
    }

    return err;
}                                      /* End of function ethercat_ssc_port_loading_eeprom() */

/*******************************************************************************************************************//**
 * Timer ISR
 *
 * @param[in]     p_args      Pointer to timer callback arguments
 *
 * @note    This is a weak function. It can be overridden by an application specific implementation if desired.
 **********************************************************************************************************************/
void ethercat_ssc_port_timer_callback (timer_callback_args_t * p_args)
{
    if (TIMER_EVENT_CYCLE_END == p_args->event)
    {
        ethercat_ssc_port_increment_timer((ethercat_ssc_port_instance_ctrl_t *) p_args->p_context);
    }
}

/*******************************************************************************************************************//**
 * PDI ISR
 *
 * @note    This is a weak function. It can be overridden by the SSC.
 **********************************************************************************************************************/
__attribute__((weak)) void PDI_Isr (void)
{
}

/*******************************************************************************************************************//**
 * Sync0 ISR
 *
 * @note    This is a weak function. It can be overridden by the SSC.
 **********************************************************************************************************************/
__attribute__((weak)) void Sync0_Isr (void)
{
}

/*******************************************************************************************************************//**
 * Sync1 ISR
 *
 * @note    This is a weak function. It can be overridden by the SSC.
 **********************************************************************************************************************/
__attribute__((weak)) void Sync1_Isr (void)
{
}

/*******************************************************************************************************************//**
 * Enable EtherCAT interrupts
 *
 * @param[in] p_ctrl   Pointer to the control block for the channel
 *
 * @note    This function is the Hardware Access Interface function could be called from the SSC.
 **********************************************************************************************************************/
void ethercat_ssc_port_enable_interrupt (ethercat_ssc_port_ctrl_t const * p_ctrl)
{
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    ethercat_ssc_port_cfg_t           * p_cfg           = (ethercat_ssc_port_cfg_t *) p_instance_ctrl->p_cfg;

    R_BSP_IrqEnableNoClear(p_cfg->sync0_irq);
    R_BSP_IrqEnableNoClear(p_cfg->sync1_irq);
    R_BSP_IrqEnableNoClear(p_cfg->common_irq);
}

/*******************************************************************************************************************//**
 * Disable EtherCAT interrupts
 *
 * @param[in] p_ctrl   Pointer to the control block for the channel
 *
 * @note    This function is the Hardware Access Interface function could be called from the SSC.
 **********************************************************************************************************************/
void ethercat_ssc_port_disable_interrupt (ethercat_ssc_port_ctrl_t const * p_ctrl)
{
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    ethercat_ssc_port_cfg_t           * p_cfg           = (ethercat_ssc_port_cfg_t *) p_instance_ctrl->p_cfg;

    R_BSP_IrqDisable(p_cfg->sync0_irq);
    R_BSP_IrqDisable(p_cfg->sync1_irq);
    R_BSP_IrqDisable(p_cfg->common_irq);
}

/*******************************************************************************************************************//**
 * Clear the timer value
 *
 * @param[out] p_ctrl           Pointer to the control block for the channel
 *
 * @note    This function is the Hardware Access Interface function could be called from the SSC.
 **********************************************************************************************************************/
void ethercat_ssc_port_clear_timer (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    p_instance_ctrl->sys_time = 0;
}

/*******************************************************************************************************************//**
 * Get the value of the timer.
 *  This function gets the value of the timer.
 *  The timer ticks per ms shall be set in "ECAT_TIMER_INC_P_MS"
 *
 * @param[in] p_ctrl              Pointer to the control block for the channel
 * @retval  Current timer value
 *
 * @note    This function is the Hardware Access Interface function could be called from the SSC.
 **********************************************************************************************************************/
uint16_t ethercat_ssc_port_get_timer (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;

    return p_instance_ctrl->sys_time;
}

/*******************************************************************************************************************//**
 * Increment the timer value
 *
 * @param[in, out] p_ctrl           Pointer to the control block for the channel
 *
 * @note    This function is the Hardware Access Interface function could be called from the SSC.
 **********************************************************************************************************************/
void ethercat_ssc_port_increment_timer (ethercat_ssc_port_ctrl_t * const p_ctrl)
{
    ethercat_ssc_port_instance_ctrl_t * p_instance_ctrl = (ethercat_ssc_port_instance_ctrl_t *) p_ctrl;
    uint32_t increment_time = p_instance_ctrl->sys_time + ECAT_TIMER_INC_P_MS;

    if (ETHERCAT_SSC_PORT_MAX_VALUE_SYSTEM_TIMER >= increment_time)
    {
        p_instance_ctrl->sys_time = (uint16_t) increment_time;
    }
    else
    {
        p_instance_ctrl->sys_time = ETHERCAT_SSC_PORT_MAX_VALUE_SYSTEM_TIMER;
    }
}

/*******************************************************************************************************************//**
 * RUN and ERR LED control
 *
 * @param[out] run_led_address            Run LED address
 * @param[out] err_led_address            Error LED address
 * @param[in] run_led_status              This parameter is not used
 * @param[in] err_led_status              Error LED status is on or off
 *
 * @note    This function is the Hardware Access Interface function could be called from the SSC.
 **********************************************************************************************************************/
void ethercat_ssc_port_run_led (uint8_t * run_led_address,
                                uint8_t * err_led_address,
                                uint8_t   run_led_status,
                                uint8_t   err_led_status)
{
    if (NULL != run_led_address)
    {
        *run_led_address = run_led_status;
    }

    FSP_PARAMETER_NOT_USED(run_led_status);

    if (NULL != err_led_address)
    {
        *err_led_address = err_led_status;
    }
}
