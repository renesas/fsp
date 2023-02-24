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
#include "rm_ob1203.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_OB1203_OPEN                         (0x632A5721UL) // Open state

/* Definitions of Timeout */
#define RM_OB1203_TIMEOUT                      (100)
#define RM_OB1203_10MS                         (10)

/* Definitions of Register data */
#define RM_OB1203_REG_DATA_PPG_PS_GAIN         (0x09)

/* Definitions of Commands */
#define RM_OB1203_COMMAND_SOFTWARE_RESET       (0x80)

/* Definitions of Register address */
#define RM_OB1203_REG_ADDR_STATUS_0            (0x00) // Power-on status, LS interrupt, and LS data status
#define RM_OB1203_REG_ADDR_STATUS_1            (0x01) // PPG/PS data status, PS/PPG interrupt status
#define RM_OB1203_REG_ADDR_MAIN_CTRL_0         (0x15) // LS operation mode control, software (SW) reset
#define RM_OB1203_REG_ADDR_MAIN_CTRL_1         (0x16) // PPG/PS operation mode control
#define RM_OB1203_REG_ADDR_INT_CFG_0           (0x2B) // LS interrupt configuration
#define RM_OB1203_REG_ADDR_INT_CFG_1           (0x2C) // PS/PPG interrupt configuration
#define RM_OB1203_REG_ADDR_PPG_PS_GAIN         (0x2E) // PPG/PS gain setting
#define RM_OB1203_REG_ADDR_PPG_PS_CFG          (0x2F) // PPG power save and LED flip setting
#define RM_OB1203_REG_ADDR_FIFO_WR_PTR         (0x38) // FIFO write pointer

/* Definitions of Mask */
#define RM_OB1203_MASK_POWER_ON_RESET          (0x80)
#define RM_OB1203_MASK_LIGHT_INTERRUPT         (0x02)
#define RM_OB1203_MASK_LIGHT_DATA_STATUS       (0x01)
#define RM_OB1203_MASK_TS_DATA                 (0x80)
#define RM_OB1203_MASK_PPG_DATA_STATUS         (0x10)
#define RM_OB1203_MASK_FIFO_AFULL_INTERRUPT    (0x20)
#define RM_OB1203_MASK_LOGIC_SIGNAL            (0x04)
#define RM_OB1203_MASK_PROX_INTERRUPT          (0x02)
#define RM_OB1203_MASK_PROX_DATA_STATUS        (0x01)

/* Definitions of FIFO */
#define RM_OB1203_FIFO_MAX_SAMPLES_32          (32)
#define RM_OB1203_FIFO_MASK_PPG2_0XFE          (0xFE)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global function prototypes
 **********************************************************************************************************************/
void      rm_ob1203_comms_i2c_callback(rm_comms_callback_args_t * p_args);
fsp_err_t rm_ob1203_read(rm_ob1203_ctrl_t * const p_api_ctrl, rm_comms_write_read_params_t write_read_params);
fsp_err_t rm_ob1203_write(rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint8_t const bytes);
fsp_err_t rm_ob1203_main_ctrl_register_write(rm_ob1203_ctrl_t * const p_api_ctrl,
                                             uint8_t const            main_ctrl_0,
                                             uint8_t const            main_ctrl_1);
fsp_err_t rm_ob1203_int_cfg_register_write(rm_ob1203_ctrl_t * const p_api_ctrl,
                                           uint8_t const            int_cfg_0,
                                           uint8_t const            int_cfg_1,
                                           uint8_t const            int_pst);
fsp_err_t        rm_ob1203_ppg_ps_gain_register_write(rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t const ppg_ps_gain);
fsp_err_t        rm_ob1203_ppg_ps_cfg_register_write(rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t const ppg_ps_cfg);
fsp_err_t        rm_ob1203_fifo_info_reset(rm_ob1203_ctrl_t * const p_api_ctrl);
fsp_err_t        rm_ob1203_all_interrupt_bits_clear(rm_ob1203_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_ob1203_delay_ms(rm_ob1203_ctrl_t * const p_ctrl, uint32_t const delay_ms);
extern fsp_err_t rm_ob1203_irq_open(rm_ob1203_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_ob1203_irq_close(rm_ob1203_ctrl_t * const p_api_ctrl);

#if BSP_CFG_RTOS
extern fsp_err_t rm_ob1203_os_semaphore_create(rm_ob1203_semaphore_t const * p_semaphore);
extern fsp_err_t rm_ob1203_os_semaphore_delete(rm_ob1203_semaphore_t const * p_semaphore);
extern fsp_err_t rm_ob1203_os_semaphore_acquire(rm_ob1203_semaphore_t const * p_semaphore, uint32_t const timeout);
extern fsp_err_t rm_ob1203_os_semaphore_release_from_ISR(rm_ob1203_semaphore_t const * p_semaphore);

#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void rm_ob1203_process_in_callback(rm_ob1203_ctrl_t * const          p_api_ctrl,
                                          rm_ob1203_callback_args_t * const p_args);
static void      rm_ob1203_device_status_check(rm_ob1203_ctrl_t * const p_api_ctrl);
static void      rm_ob1203_unread_samples_calculate(rm_ob1203_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_ob1203_software_reset(rm_ob1203_ctrl_t * const p_api_ctrl);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_ob1203_api_t const g_ob1203_on_ob1203 =
{
    .open                  = RM_OB1203_Open,
    .close                 = RM_OB1203_Close,
    .measurementStart      = RM_OB1203_MeasurementStart,
    .measurementStop       = RM_OB1203_MeasurementStop,
    .lightRead             = RM_OB1203_LightRead,
    .lightDataCalculate    = RM_OB1203_LightDataCalculate,
    .proxRead              = RM_OB1203_ProxRead,
    .proxDataCalculate     = RM_OB1203_ProxDataCalculate,
    .ppgRead               = RM_OB1203_PpgRead,
    .ppgDataCalculate      = RM_OB1203_PpgDataCalculate,
    .gainSet               = RM_OB1203_GainSet,
    .ledCurrentSet         = RM_OB1203_LedCurrentSet,
    .deviceInterruptCfgSet = RM_OB1203_DeviceInterruptCfgSet,
    .fifoInfoGet           = RM_OB1203_FifoInfoGet,
    .deviceStatusGet       = RM_OB1203_DeviceStatusGet,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_OB1203
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the OB1203 Middle module. Implements @ref rm_ob1203_api_t::open.
 *
 * Example:
 * @snippet rm_ob1203_example.c RM_OB1203_Open
 *
 * @retval FSP_SUCCESS              OB1203 successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_Open (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t     * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    rm_ob1203_mode_extended_cfg_t * p_mode;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms_instance);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_OB1203_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg = p_cfg;
    p_mode        = (rm_ob1203_mode_extended_cfg_t *) p_cfg->p_extend;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_mode->p_api);
 #if BSP_CFG_RTOS
    FSP_ASSERT(NULL != p_ctrl->p_cfg->p_semaphore);
 #endif
#endif

    /* Set instances */
    p_ctrl->p_comms_i2c_instance = p_cfg->p_comms_instance;
    p_ctrl->p_irq_instance       = p_cfg->p_irq_instance;

    /* Set operation mode */
    p_ctrl->p_mode = p_mode;

    /* Set parameters */
    p_ctrl->p_context            = p_cfg->p_context;
    p_ctrl->p_comms_callback     = p_cfg->p_comms_callback;
    p_ctrl->p_irq_callback       = p_cfg->p_irq_callback;
    p_ctrl->p_device_status      = NULL;
    p_ctrl->p_fifo_info          = NULL;
    p_ctrl->fifo_reset           = false;
    p_ctrl->prox_gain_update     = false;
    p_ctrl->interrupt_bits_clear = false;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Open IRQ */
    if (NULL != p_ctrl->p_irq_instance)
    {
        err = rm_ob1203_irq_open(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

#if BSP_CFG_RTOS

    /* Set semaphore */
    p_ctrl->p_semaphore = p_ctrl->p_cfg->p_semaphore;

    /* Create semaphore */
    err = rm_ob1203_os_semaphore_create(p_ctrl->p_semaphore);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Stop previous measurements */
    err = rm_ob1203_main_ctrl_register_write(p_ctrl, 0x00, 0x00);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Software reset */
    err = rm_ob1203_software_reset(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Delay 10ms */
    err = rm_ob1203_delay_ms(p_ctrl, RM_OB1203_10MS);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear all interrupt bits */
    err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Open operation mode */
    err = p_mode->p_api->open(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set open flag */
    p_ctrl->open = RM_OB1203_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified OB1203 control block. Implements @ref rm_ob1203_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_Close (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Close IRQ */
    if (NULL != p_ctrl->p_irq_instance)
    {
        rm_ob1203_irq_close(p_ctrl);
    }

#if BSP_CFG_RTOS

    /* delete a semaphore */
    rm_ob1203_os_semaphore_delete(p_ctrl->p_semaphore);
#endif

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Start measurement.
 * Implements @ref rm_ob1203_api_t::measurementStart
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_MeasurementStart (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Start measurement */
    err = p_ctrl->p_mode->p_api->measurementStart(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Stop measurement.
 * If device interrupt is enabled, interrupt bits are cleared after measurement stop.
 * If PPG mode, FIFO information is also reset after measurement stop.
 * In RTOS and Light/Proximity/Light Proximity mode, if device interrupt is enabled, blocks 2 bytes on the I2C bus.
 * In RTOS and PPG mode, if device interrupt is enabled, blocks 6 bytes on the I2C bus. If device interrupt is disabled,
 * blocks 4 bytes on the I2C bus.
 * Implements @ref rm_ob1203_api_t::measurementStop
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_MeasurementStop (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop measurement */
    err = p_ctrl->p_mode->p_api->measurementStop(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Reads Light ADC data from OB1203 device.
 * If device interrupt is enabled, interrupt bits are cleared after data read.
 * In RTOS and Light mode, if device interrupt is enabled, blocks 2 bytes on the I2C bus.
 * Implements @ref rm_ob1203_api_t::lightRead
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_LightRead (rm_ob1203_ctrl_t * const     p_api_ctrl,
                               rm_ob1203_raw_data_t * const p_raw_data,
                               rm_ob1203_light_data_type_t  type)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read Light raw data */
    err = p_ctrl->p_mode->p_api->lightRead(p_ctrl, p_raw_data, type);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate light data from raw data.
 * Implements @ref rm_ob1203_api_t::lightDataCalculate
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_LightDataCalculate (rm_ob1203_ctrl_t * const       p_api_ctrl,
                                        rm_ob1203_raw_data_t * const   p_raw_data,
                                        rm_ob1203_light_data_t * const p_ob1203_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_ob1203_data);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Calculate Light data from raw data */
    err = p_ctrl->p_mode->p_api->lightDataCalculate(p_ctrl, p_raw_data, p_ob1203_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Reads Proximity ADC data from OB1203 device.
 * If device interrupt is enabled, interrupt bits are cleared after data read.
 * In RTOS and Proximity mode, if device interrupt is enabled, blocks 2 bytes on the I2C bus.
 * Implements @ref rm_ob1203_api_t::proxRead
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_ProxRead (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read Proximity raw data */
    err = p_ctrl->p_mode->p_api->proxRead(p_ctrl, p_raw_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate proximity data from raw data.
 * Implements @ref rm_ob1203_api_t::proxDataCalculate
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_ProxDataCalculate (rm_ob1203_ctrl_t * const      p_api_ctrl,
                                       rm_ob1203_raw_data_t * const  p_raw_data,
                                       rm_ob1203_prox_data_t * const p_ob1203_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_ob1203_data);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Calculate Proximity data from raw data */
    err = p_ctrl->p_mode->p_api->proxDataCalculate(p_ctrl, p_raw_data, p_ob1203_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Reads PPG ADC data from OB1203 device. One sample requires three bytes. 0 cannot set to the number of samples.
 * Implements @ref rm_ob1203_api_t::ppgRead
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_PpgRead (rm_ob1203_ctrl_t * const     p_api_ctrl,
                             rm_ob1203_raw_data_t * const p_raw_data,
                             uint8_t const                number_of_samples)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read PPG raw data */
    err = p_ctrl->p_mode->p_api->ppgRead(p_ctrl, p_raw_data, number_of_samples);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate PPG data from raw data.
 * Implements @ref rm_ob1203_api_t::ppgDataCalculate
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_PpgDataCalculate (rm_ob1203_ctrl_t * const     p_api_ctrl,
                                      rm_ob1203_raw_data_t * const p_raw_data,
                                      rm_ob1203_ppg_data_t * const p_ob1203_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_ob1203_data);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Calculate PPG data from raw data */
    err = p_ctrl->p_mode->p_api->ppgDataCalculate(p_ctrl, p_raw_data, p_ob1203_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Set gain. This function should be called after calling RM_OB1203_MeasurementStop().
 * In RTOS and Light Proximity mode, blocks 2 bytes on the I2C bus.
 * Implements @ref rm_ob1203_api_t::gainSet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_GainSet (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_gain_t const gain)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set PPG and Proximity gain */
    err = p_ctrl->p_mode->p_api->gainSet(p_ctrl, gain);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Set currents. This function should be called after calling RM_OB1203_MeasurementStop().
 * Implements @ref rm_ob1203_api_t::ledCurrentSet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_LedCurrentSet (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_led_current_t const led_current)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set LED currents */
    err = p_ctrl->p_mode->p_api->ledCurrentSet(p_ctrl, led_current);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Set device interrupt configurations. This function should be called after calling RM_OB1203_MeasurementStop().
 * Implements @ref rm_ob1203_api_t::deviceInterruptCfgSet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_DeviceInterruptCfgSet (rm_ob1203_ctrl_t * const               p_api_ctrl,
                                           rm_ob1203_device_interrupt_cfg_t const interrupt_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set PPG device interrupt configuration */
    err = p_ctrl->p_mode->p_api->deviceInterruptCfgSet(p_ctrl, interrupt_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Get FIFO information from OB1203 device.
 * Implements @ref rm_ob1203_api_t::fifoInfoGet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_FifoInfoGet (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_fifo_info_t * const p_fifo_info)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_fifo_info);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Get PPG FIFO information */
    err = p_ctrl->p_mode->p_api->fifoInfoGet(p_ctrl, p_fifo_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Get device status from OB1203 device. Clear all interrupt bits.
 * Implements @ref rm_ob1203_api_t::deviceStatusGet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_OB1203_DeviceStatusGet (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_device_status_t * const p_status)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t  * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    rm_comms_write_read_params_t write_read_params;

#if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(RM_OB1203_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set pointer */
    p_ctrl->p_device_status = p_status;

    /* Get status */
    p_ctrl->register_address     = RM_OB1203_REG_ADDR_STATUS_0;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = &p_ctrl->buf[0];
    write_read_params.dest_bytes = 2;
    err = rm_ob1203_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_OB1203)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief OB1203 callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_ob1203_comms_i2c_callback (rm_comms_callback_args_t * p_args)
{
#if BSP_CFG_RTOS == 0
    fsp_err_t err = FSP_SUCCESS;
#endif
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_args->p_context;
    rm_ob1203_callback_args_t   ob1203_callback_args;

    /* Set context */
    ob1203_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            ob1203_callback_args.event = RM_OB1203_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            ob1203_callback_args.event = RM_OB1203_EVENT_ERROR;
            break;
        }
    }

    if (RM_OB1203_OPEN != p_ctrl->open)
    {
        /* Set flag */
        p_ctrl->init_process_params.communication_finished = true;

        /* Set event */
        p_ctrl->init_process_params.event = ob1203_callback_args.event;
    }
    else
    {
        if (RM_OB1203_EVENT_SUCCESS == ob1203_callback_args.event)
        {
            if (NULL != p_ctrl->p_device_status)
            {
                /* Check device status */
                rm_ob1203_device_status_check(p_ctrl);

                /* Clear pointer */
                p_ctrl->p_device_status = NULL;

                /* Call user callback function */
                rm_ob1203_process_in_callback(p_ctrl, &ob1203_callback_args);
            }
            else if (NULL != p_ctrl->p_fifo_info)
            {
                /* Calculate the number of unread FIFO samples */
                rm_ob1203_unread_samples_calculate(p_ctrl);

                /* Clear pointer */
                p_ctrl->p_fifo_info = NULL;

                /* Call user callback function */
                rm_ob1203_process_in_callback(p_ctrl, &ob1203_callback_args);
            }
            else if (false != p_ctrl->fifo_reset)
            {
                /* Clear flag */
                p_ctrl->fifo_reset = false;

#if BSP_CFG_RTOS

                /* Release a semaphore */
                rm_ob1203_os_semaphore_release_from_ISR(p_ctrl->p_semaphore);
#else

                /* Reset FIFO info. */
                err = rm_ob1203_fifo_info_reset(p_ctrl);
                if (FSP_SUCCESS != err)
                {
                    /* Set event */
                    ob1203_callback_args.event = RM_OB1203_EVENT_ERROR;

                    /* Call user callback function */
                    rm_ob1203_process_in_callback(p_ctrl, &ob1203_callback_args);
                }
#endif
            }
            else if (false != p_ctrl->prox_gain_update)
            {
                /* Clear flag */
                p_ctrl->prox_gain_update = false;

#if BSP_CFG_RTOS

                /* Release a semaphore */
                rm_ob1203_os_semaphore_release_from_ISR(p_ctrl->p_semaphore);
#else

                /* Set Proximity mode gain */
                err = rm_ob1203_ppg_ps_gain_register_write(p_ctrl, (uint8_t) p_ctrl->p_mode->ppg_prox_gain);
                if (FSP_SUCCESS != err)
                {
                    /* Set event */
                    ob1203_callback_args.event = RM_OB1203_EVENT_ERROR;

                    /* Call user callback function */
                    rm_ob1203_process_in_callback(p_ctrl, &ob1203_callback_args);
                }
#endif
            }
            else if (false != p_ctrl->interrupt_bits_clear)
            {
                /* Clear flag */
                p_ctrl->interrupt_bits_clear = false;

#if BSP_CFG_RTOS

                /* Release a semaphore */
                rm_ob1203_os_semaphore_release_from_ISR(p_ctrl->p_semaphore);
#else

                /* Clear all interrupt bits */
                err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
                if (FSP_SUCCESS != err)
                {
                    /* Set event */
                    ob1203_callback_args.event = RM_OB1203_EVENT_ERROR;

                    /* Call user callback function */
                    rm_ob1203_process_in_callback(p_ctrl, &ob1203_callback_args);
                }
#endif
            }
            else
            {
                /* Call user callback function */
                rm_ob1203_process_in_callback(p_ctrl, &ob1203_callback_args);
            }
        }
        else
        {
            /* Call user callback function */
            rm_ob1203_process_in_callback(p_ctrl, &ob1203_callback_args);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief Read data from OB1203 device.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_read (rm_ob1203_ctrl_t * const p_api_ctrl, rm_comms_write_read_params_t write_read_params)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint16_t counter = 0;

    if (RM_OB1203_OPEN != p_ctrl->open)
    {
        /* Clear flag */
        p_ctrl->init_process_params.communication_finished = false;
    }

    /* WriteRead data */
    err = p_ctrl->p_comms_i2c_instance->p_api->writeRead(p_ctrl->p_comms_i2c_instance->p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_OB1203_OPEN != p_ctrl->open)
    {
        /* Wait callback */
        while (false == p_ctrl->init_process_params.communication_finished)
        {
            rm_ob1203_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_OB1203_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN(RM_OB1203_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write data to OB1203 device.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_write (rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint8_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint16_t counter = 0;

    if (RM_OB1203_OPEN != p_ctrl->open)
    {
        /* Clear flag */
        p_ctrl->init_process_params.communication_finished = false;
    }

    /* Write data */
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, p_src, (uint32_t) bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_OB1203_OPEN != p_ctrl->open)
    {
        /* Wait callback */
        while (false == p_ctrl->init_process_params.communication_finished)
        {
            rm_ob1203_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_OB1203_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN(RM_OB1203_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write data to the MAIN_CTRL_0 and MAIN_CTRL_1 registers.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_main_ctrl_register_write (rm_ob1203_ctrl_t * const p_api_ctrl,
                                              uint8_t const            main_ctrl_0,
                                              uint8_t const            main_ctrl_1)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    /* Set the data */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_MAIN_CTRL_0;
    p_ctrl->buf[1] = main_ctrl_0;
    p_ctrl->buf[2] = main_ctrl_1;

    /* Write data */
    err = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write data to the INT_CFG and INT_PST registers.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_int_cfg_register_write (rm_ob1203_ctrl_t * const p_api_ctrl,
                                            uint8_t const            int_cfg_0,
                                            uint8_t const            int_cfg_1,
                                            uint8_t const            int_pst)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    /* Set the data */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_INT_CFG_0;
    p_ctrl->buf[1] = int_cfg_0;
    p_ctrl->buf[2] = int_cfg_1;
    p_ctrl->buf[3] = int_pst;

    /* Write data */
    err = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 4);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write data to the PPG_PS_GAIN register.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_ppg_ps_gain_register_write (rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t const ppg_ps_gain)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    /* Set the data */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PPG_PS_GAIN;
    p_ctrl->buf[1] = ppg_ps_gain | RM_OB1203_REG_DATA_PPG_PS_GAIN;

    /* Write data */
    err = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write data to the PPG_PS_CFG register.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_ppg_ps_cfg_register_write (rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t const ppg_ps_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    /* Set the data */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PPG_PS_CFG;
    p_ctrl->buf[1] = ppg_ps_cfg;

    /* Write data */
    err = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Clear all interrupt bits.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_all_interrupt_bits_clear (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t  * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    rm_comms_write_read_params_t write_read_params;

    /* Clear all interrupt bits */
    p_ctrl->register_address     = RM_OB1203_REG_ADDR_STATUS_0;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = &p_ctrl->buf[0];
    write_read_params.dest_bytes = 2;
    err = rm_ob1203_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset FIFO information.
 * If device interrupt is enabled, interrupt bits are cleared after measurement stop.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t rm_ob1203_fifo_info_reset (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    if (RM_OB1203_OPERATION_MODE_PPG == p_ctrl->p_mode->mode_irq)
    {
        /* Clear interrupt bits after FIFO reset */
        p_ctrl->interrupt_bits_clear = true;
    }

    /* Reset FIFO information */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_FIFO_WR_PTR;
    p_ctrl->buf[1] = 0x00;
    p_ctrl->buf[2] = 0x00;
    p_ctrl->buf[3] = 0x00;
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 4);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if BSP_CFG_RTOS
    if (RM_OB1203_OPERATION_MODE_PPG == p_ctrl->p_mode->mode_irq)
    {
        /* Acquire a semaphore */
        err = rm_ob1203_os_semaphore_acquire(p_ctrl->p_semaphore, p_ctrl->p_cfg->semaphore_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Clear all interrupt bits */
        err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal ob1203 private function.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Process in callback function. Call user callback.
 **********************************************************************************************************************/
static void rm_ob1203_process_in_callback (rm_ob1203_ctrl_t * const          p_api_ctrl,
                                           rm_ob1203_callback_args_t * const p_args)
{
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    if (NULL != p_ctrl->p_comms_callback)
    {
        /* Call callback function */
        p_ctrl->p_comms_callback(p_args);
    }
}

/*******************************************************************************************************************//**
 * @brief Check device status and set callback event.
 **********************************************************************************************************************/
static void rm_ob1203_device_status_check (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    /* Check if power-on-reset occurs */
    if (0x00 != (p_ctrl->buf[0] & RM_OB1203_MASK_POWER_ON_RESET))
    {
        p_ctrl->p_device_status->power_on_reset_occur = true;
    }
    else
    {
        p_ctrl->p_device_status->power_on_reset_occur = false;
    }

    /* Check if Light mode interrupt condition occurs */
    if (0x00 != (p_ctrl->buf[0] & RM_OB1203_MASK_LIGHT_INTERRUPT))
    {
        p_ctrl->p_device_status->light_interrupt_occur = true;
    }
    else
    {
        p_ctrl->p_device_status->light_interrupt_occur = false;
    }

    /* Check if Light mode measurement is complete */
    if (0x00 != (p_ctrl->buf[0] & RM_OB1203_MASK_LIGHT_DATA_STATUS))
    {
        p_ctrl->p_device_status->light_measurement_complete = true;
    }
    else
    {
        p_ctrl->p_device_status->light_measurement_complete = false;
    }

    /* Check if TS data measurement is complete */
    if (0x00 != (p_ctrl->buf[1] & RM_OB1203_MASK_TS_DATA))
    {
        p_ctrl->p_device_status->ts_measurement_complete = true;
    }
    else
    {
        p_ctrl->p_device_status->ts_measurement_complete = false;
    }

    /* Check if PPG FIFO almost full interrupt condition occurs */
    if (0x00 != (p_ctrl->buf[1] & RM_OB1203_MASK_FIFO_AFULL_INTERRUPT))
    {
        p_ctrl->p_device_status->fifo_afull_interrupt_occur = true;
    }
    else
    {
        p_ctrl->p_device_status->fifo_afull_interrupt_occur = false;
    }

    /* Check if PPG mode measurement is complete */
    if (0x00 != (p_ctrl->buf[1] & RM_OB1203_MASK_PPG_DATA_STATUS))
    {
        p_ctrl->p_device_status->ppg_measurement_complete = true;
    }
    else
    {
        p_ctrl->p_device_status->ppg_measurement_complete = false;
    }

    /* Check if object is near */
    if (0x00 != (p_ctrl->buf[1] & RM_OB1203_MASK_LOGIC_SIGNAL))
    {
        p_ctrl->p_device_status->object_near = true;
    }
    else
    {
        p_ctrl->p_device_status->object_near = false;
    }

    /* Check if Proximity mode interrupt condition occurs */
    if (0x00 != (p_ctrl->buf[1] & RM_OB1203_MASK_PROX_INTERRUPT))
    {
        p_ctrl->p_device_status->prox_interrupt_occur = true;
    }
    else
    {
        p_ctrl->p_device_status->prox_interrupt_occur = false;
    }

    /* Check if Proximity mode measurement is complete */
    if (0x00 != (p_ctrl->buf[1] & RM_OB1203_MASK_PROX_DATA_STATUS))
    {
        p_ctrl->p_device_status->prox_measurement_complete = true;
    }
    else
    {
        p_ctrl->p_device_status->prox_measurement_complete = false;
    }
}

/*******************************************************************************************************************//**
 * @brief Calculate the number of unread FIFO samples.
 **********************************************************************************************************************/
static void rm_ob1203_unread_samples_calculate (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint8_t unread_samples             = 0;

    /* Calculate the number of unread FIFO samples */
    unread_samples = p_ctrl->buf[0];
    if (p_ctrl->buf[0] < p_ctrl->buf[1])
    {
        unread_samples += RM_OB1203_FIFO_MAX_SAMPLES_32; // Number of samples is up to 32.
    }

    unread_samples -= p_ctrl->buf[1];

    if (RM_OB1203_PPG_SENSOR_MODE_PPG2 == p_ctrl->p_mode->ppg_sensor_mode)
    {
        /* In PPG2 mode, Two samples is one pair. */
        unread_samples &= RM_OB1203_FIFO_MASK_PPG2_0XFE;
    }

    /* Set data */
    p_ctrl->p_fifo_info->write_index      = p_ctrl->buf[0];
    p_ctrl->p_fifo_info->read_index       = p_ctrl->buf[1];
    p_ctrl->p_fifo_info->overflow_counter = p_ctrl->buf[2];
    p_ctrl->p_fifo_info->unread_samples   = unread_samples;
}

/*******************************************************************************************************************//**
 * @brief Software reset.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_software_reset (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;

    /* Set the data */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_MAIN_CTRL_0;
    p_ctrl->buf[1] = RM_OB1203_COMMAND_SOFTWARE_RESET;

    /* Software reset */
    err = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}
