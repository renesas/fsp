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
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "rm_zmod4xxx.h"
#include "zmod4xxx_types.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_ZMOD4XXX_OPEN                               (0x5A4D4F44UL) // Open state

/* Definitions of Command Size */
#define RM_ZMOD4XXX_DF_SIZE                            (4)            // Size of DF command

/* Definitions of Timeout */
#define RM_ZMOD4XXX_TIMEOUT                            (100)

/* Definitions of Wait Time */
#define RM_ZMOD4XXX_WAIT_TIME_50                       (50)
#define RM_ZMOD4XXX_WAIT_TIME_200                      (200)

/* Definitions of Register address */
#define RM_ZMOD4XXX_ADDR_PID                           (0x00)
#define RM_ZMOD4XXX_ADDR_CONF                          (0x20)
#define RM_ZMOD4XXX_ADDR_PROD_DATA                     (0x26)
#define RM_ZMOD4XXX_ADDR_CMD                           (0x93)
#define RM_ZMOD4XXX_ADDR_STATUS                        (0x94)
#define RM_ZMOD4XXX_ADDR_TRACKING                      (0x3A)
#define RM_ZMOD4XXX_ADDR_DEV_ERR                       (0xB7)

/* Definitions of data size */
#define RM_ZMOD4XXX_LEN_PID                            (2)
#define RM_ZMOD4XXX_LEN_CONF                           (6)
#define RM_ZMOD45XX_LEN_TRACKING                       (6)
#define RM_ZMOD45XX_LEN_GENERAL_PURPOSE                (9)
#define RM_ZMOD4XXX_HSP_MAX                            (8)

/* Definitions of data mask */
#define RM_ZMOD4XXX_STATUS_SEQUENCER_RUNNING_MASK      (0x80) // Sequencer is running
#define RM_ZMOD4XXX_STATUS_SLEEP_TIMER_ENABLED_MASK    (0x40) // SleepTimer_enabled */
#define RM_ZMOD4XXX_STATUS_ALARM_MASK                  (0x20) // Alarm
#define RM_ZMOD4XXX_STATUS_LAST_SEQ_STEP_MASK          (0x1F) // Last executed sequencer step
#define RM_ZMOD4XXX_STATUS_POR_EVENT_MASK              (0x80) // POR_event
#define RM_ZMOD4XXX_STATUS_ACCESS_CONFLICT_MASK        (0x40) // AccessConflict

/* Definitions of Calculation */
#define RM_ZMOD4XXX_80H                                (0x80)
#define RM_ZMOD4XXX_1000                               (1000)
#define RM_ZMOD4XXX_256                                (256)
#define RM_ZMOD4XXX_256F                               (256.0F)
#define RM_ZMOD4XXX_640F                               (640.0F)
#define RM_ZMOD4XXX_512000F                            (512000.0F)
#define RM_ZMOD4XXX_12288000F                          (12288000.0F)
#define RM_ZMOD4XXX_FF                                 (0x00FF)
#define RM_ZMOD4XXX_1E_3                               (1e-3)
#define RM_ZMOD4XXX_10E9                               (10e9)
#define RM_ZMOD4XXX_1E3                                (1e3)
#define RM_ZMOD4XXX_100F                               (100.0F)

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_zmod4xxx_api_t const g_zmod4xxx_on_zmod4xxx =
{
    .open                      = RM_ZMOD4XXX_Open,
    .close                     = RM_ZMOD4XXX_Close,
    .measurementStart          = RM_ZMOD4XXX_MeasurementStart,
    .measurementStop           = RM_ZMOD4XXX_MeasurementStop,
    .statusCheck               = RM_ZMOD4XXX_StatusCheck,
    .read                      = RM_ZMOD4XXX_Read,
    .iaq1stGenDataCalculate    = RM_ZMOD4XXX_Iaq1stGenDataCalculate,
    .iaq2ndGenDataCalculate    = RM_ZMOD4XXX_Iaq2ndGenDataCalculate,
    .odorDataCalculate         = RM_ZMOD4XXX_OdorDataCalculate,
    .sulfurOdorDataCalculate   = RM_ZMOD4XXX_SulfurOdorDataCalculate,
    .oaq1stGenDataCalculate    = RM_ZMOD4XXX_Oaq1stGenDataCalculate,
    .oaq2ndGenDataCalculate    = RM_ZMOD4XXX_Oaq2ndGenDataCalculate,
    .raqDataCalculate          = RM_ZMOD4XXX_RaqDataCalculate,
    .temperatureAndHumiditySet = RM_ZMOD4XXX_TemperatureAndHumiditySet,
    .deviceErrorCheck          = RM_ZMOD4XXX_DeviceErrorCheck,
};

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
extern fsp_err_t rm_zmod4xxx_delay_ms(rm_zmod4xxx_ctrl_t * const p_ctrl, uint32_t const delay_ms);
extern fsp_err_t rm_zmod4xxx_irq_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_zmod4xxx_irq_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
void             rm_zmod4xxx_comms_i2c_callback(rm_comms_callback_args_t * p_args);

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

static fsp_err_t rm_zmod4xxx_i2c_read(rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                      rm_comms_write_read_params_t const  params);
static fsp_err_t rm_zmod4xxx_i2c_write(rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                       uint8_t * const                     p_src,
                                       uint32_t const                      bytes);
static fsp_err_t rm_zmod4xxx_read_status(rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * status);
static fsp_err_t rm_zmod4xxx_read_sensor_info(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_calc_factor(zmod4xxx_conf * conf, uint8_t * hsp, uint8_t * config);
static fsp_err_t rm_zmod4xxx_init_sensor(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_init_measurement(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_start_measurement(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_read_adc_result(rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * adc_result);
static fsp_err_t rm_zmod4xxx_stop_measurement(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_configuration(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_device_error_event_check(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @addtogroup RM_ZMOD4XXX
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief This function should be called when start a measurement and when measurement data is stale data.
 * Sends the slave address to the zmod4xxx and start a measurement.
 * Implements @ref rm_zmod4xxx_api_t::open.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.
 * @retval FSP_ERR_UNSUPPORTED      Unsupport product ID.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Open (rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms_instance);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg = p_cfg;
    p_lib         = (rm_zmod4xxx_lib_extended_cfg_t *) p_cfg->p_extend;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_lib->p_api);
    FSP_ASSERT(NULL != p_lib->p_data_set);
    FSP_ASSERT(NULL != p_lib->p_product_data);
    FSP_ASSERT(NULL != p_lib->p_device);
    FSP_ASSERT(NULL != p_lib->p_handle);
    FSP_ASSERT(NULL != p_lib->p_results);
#endif

    /* Set instances */
    p_ctrl->p_comms_i2c_instance = p_cfg->p_comms_instance;
    p_ctrl->p_irq_instance       = p_cfg->p_irq_instance;

    /* Set ZMOD4XXX library specific */
    p_ctrl->p_zmod4xxx_lib = p_lib;

    /* Set parameters */
    p_ctrl->p_context        = p_cfg->p_context;
    p_ctrl->p_comms_callback = p_cfg->p_comms_callback;
    p_ctrl->p_irq_callback   = p_cfg->p_irq_callback;
    p_ctrl->status.flag      = false;
    p_ctrl->event            = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;
    p_ctrl->dev_err_check    = false;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Open IRQ */
    if (NULL != p_ctrl->p_irq_instance)
    {
        err = rm_zmod4xxx_irq_open(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* Initialize the device */
    err = rm_zmod4xxx_configuration(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Initialize Library */
    err = p_lib->p_api->open(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check if everything is okay */
    p_ctrl->open = RM_ZMOD4XXX_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when close the sensor. Implements @ref rm_zmod4xxx_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Close IRQ */
    if (NULL != p_ctrl->p_irq_instance)
    {
        rm_zmod4xxx_irq_close(p_ctrl);
    }

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when start a measurement.
 * Implements @ref rm_zmod4xxx_api_t::measurementStart.
 *
 * @retval FSP_SUCCESS                    Successfully started.
 * @retval FSP_ERR_ASSERTION              Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN               Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_MeasurementStart (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear event */
    p_ctrl->event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Start the measurement */
    err = rm_zmod4xxx_start_measurement(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when stop a measurement.
 * Implements @ref rm_zmod4xxx_api_t::measurementStop.
 *
 * @retval FSP_SUCCESS                    Successfully started.
 * @retval FSP_ERR_ASSERTION              Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN               Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_MeasurementStop (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop the measurement */
    err = rm_zmod4xxx_stop_measurement(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when polling is used. It reads the status of sensor.
 * Implements @ref rm_zmod4xxx_api_t::statusCheck.
 *
 * @retval FSP_SUCCESS                    Successfully started.
 * @retval FSP_ERR_ASSERTION              Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN               Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_StatusCheck (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear event */
    p_ctrl->event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Set flag */
    p_ctrl->status.flag = true;

    /* Read status from ZMOD4XXX */
    err = rm_zmod4xxx_read_status(p_ctrl, &p_ctrl->status.value);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::read
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 * @retval FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED          Measurement is not finished.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Read (rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check if measurement is complete. */
    FSP_ERROR_RETURN(RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE == p_ctrl->event, FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED);

    /* Clear event */
    p_ctrl->event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Read ADC data */
    err = rm_zmod4xxx_read_adc_result(p_ctrl, (uint8_t *) p_raw_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::iaq1stGenDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Iaq1stGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    /* Calculate IAQ 1st Gen. data */
    err = p_lib->p_api->iaq1stGenDataCalculate(p_ctrl, p_raw_data, p_zmod4xxx_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::iaq2ndGenDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Iaq2ndGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    /* Calculate IAQ 2nd Gen. data */
    err = p_lib->p_api->iaq2ndGenDataCalculate(p_ctrl, p_raw_data, p_zmod4xxx_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::odorDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_OdorDataCalculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                         rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                         rm_zmod4xxx_odor_data_t * const p_zmod4xxx_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    /* Calculate Odor data */
    err = p_lib->p_api->odorDataCalculate(p_ctrl, p_raw_data, p_zmod4xxx_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::sulfurOdorDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_SulfurOdorDataCalculate (rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                               rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                               rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    /* Calculate Sulfur Odor data */
    err = p_lib->p_api->sulfurOdorDataCalculate(p_ctrl, p_raw_data, p_zmod4xxx_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::oaq1stGenDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Oaq1stGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_oaq_1st_data_t * const p_zmod4xxx_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    /* Calculate OAQ 1st Gen. data */
    err = p_lib->p_api->oaq1stGenDataCalculate(p_ctrl, p_raw_data, p_zmod4xxx_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::oaq2ndGenDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Oaq2ndGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    /* Calculate OAQ 2nd Gen. data */
    err = p_lib->p_api->oaq2ndGenDataCalculate(p_ctrl, p_raw_data, p_zmod4xxx_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::raqDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_RaqDataCalculate (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                        rm_zmod4xxx_raw_data_t * const p_raw_data,
                                        rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    /* Calculate RAQ data */
    err = p_lib->p_api->raqDataCalculate(p_ctrl, p_raw_data, p_zmod4xxx_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function is valid only for OAQ_2nd_Gen and IAQ_2nd_Gen_ULP. This function should be called before DataCalculate.
 * Humidity and temperature measurements are needed for ambient compensation.
 * Implements @ref rm_zmod4xxx_api_t::temperatureAndHumiditySet
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_TemperatureAndHumiditySet (rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                 float                      temperature,
                                                 float                      humidity)
{
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set ZMOD4XXX library specific */
    p_lib = p_ctrl->p_zmod4xxx_lib;

    p_lib->temperature = temperature;
    p_lib->humidity    = humidity;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function is valid only for IAQ_2nd_Gen and IAQ_2nd_Gen_ULP. This function should be called before Read and DataCalculate.
 * Check for unexpected reset occurs or getting unvalid ADC data.
 * Implements @ref rm_zmod4xxx_api_t::deviceErrorCheck
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_DeviceErrorCheck (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set flag */
    p_ctrl->dev_err_check = true;

    /* Check device error event */
    err = rm_zmod4xxx_device_error_event_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup ZMOD4XXX)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief ZMOD4XXX callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_zmod4xxx_comms_i2c_callback (rm_comms_callback_args_t * p_args)
{
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_args->p_context;
    rm_zmod4xxx_callback_args_t      zmod4xxx_callback_args;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;
    uint8_t status;

    /* Set context */
    zmod4xxx_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_ERROR;
            break;
        }
    }

    if (RM_ZMOD4XXX_OPEN != p_ctrl->open)
    {
        /* Set flag */
        p_ctrl->init_process_params.communication_finished = true;

        /* Set event */
        p_ctrl->init_process_params.event = zmod4xxx_callback_args.event;
    }
    else
    {
        if ((true == p_ctrl->status.flag) && (RM_ZMOD4XXX_EVENT_SUCCESS == zmod4xxx_callback_args.event))
        {
            if ((RM_ZMOD4410_LIB_TYPE_IAQ_1ST_GEN_CONTINUOUS == p_lib->lib_type) ||
                (RM_ZMOD4410_LIB_TYPE_ODOR == p_lib->lib_type) ||
                (RM_ZMOD4450_LIB_TYPE_RAQ == p_lib->lib_type))
            {
                status = (p_ctrl->status.value & RM_ZMOD4XXX_STATUS_LAST_SEQ_STEP_MASK);
                if (((p_zmod4xxx_device->meas_conf->s.len / 2) - 1) != status)
                {
                    /* Set event */
                    zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;
                }
                else
                {
                    /* Set event */
                    zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
                    p_ctrl->event                = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
                }
            }
            else
            {
                status = p_ctrl->status.value & RM_ZMOD4XXX_STATUS_SEQUENCER_RUNNING_MASK;
                if (0 != status)
                {
                    /* Set event */
                    zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;
                }
                else
                {
                    /* Set event */
                    zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
                    p_ctrl->event                = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
                }
            }

            /* Clear flag */
            p_ctrl->status.flag = false;
        }
        else if ((true == p_ctrl->dev_err_check) && (RM_ZMOD4XXX_EVENT_SUCCESS == zmod4xxx_callback_args.event))
        {
            /* Set event */
            if (RM_ZMOD4XXX_STATUS_ACCESS_CONFLICT_MASK & p_ctrl->buf[0])
            {
                zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_DEV_ERR_ACCESS_CONFLICT;
            }
            else if (RM_ZMOD4XXX_STATUS_POR_EVENT_MASK & p_ctrl->buf[0])
            {
                zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_DEV_ERR_POWER_ON_RESET;
            }
            else
            {
                zmod4xxx_callback_args.event = RM_ZMOD4XXX_EVENT_SUCCESS;
            }

            /* Clear flag */
            p_ctrl->dev_err_check = false;
        }
        else
        {
        }

        if (NULL != p_ctrl->p_comms_callback)
        {
            /* Call callback function */
            p_ctrl->p_comms_callback(&zmod4xxx_callback_args);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief I2C wrapper function to read from zmod4xxx sensor.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_i2c_read (rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                       rm_comms_write_read_params_t const  params)
{
    fsp_err_t err     = FSP_SUCCESS;
    uint16_t  counter = 0;

    if (RM_ZMOD4XXX_OPEN != p_ctrl->open)
    {
        /* Clear flag */
        p_ctrl->init_process_params.communication_finished = false;
    }

    /* WriteRead data */
    err = p_ctrl->p_comms_i2c_instance->p_api->writeRead(p_ctrl->p_comms_i2c_instance->p_ctrl, params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_ZMOD4XXX_OPEN != p_ctrl->open)
    {
        /* Wait callback */
        while (false == p_ctrl->init_process_params.communication_finished)
        {
            rm_zmod4xxx_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_ZMOD4XXX_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN(RM_ZMOD4XXX_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief I2C wrapper function to write from zmod4xxx sensor.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_i2c_write (rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                        uint8_t * const                     p_src,
                                        uint32_t const                      bytes)
{
    fsp_err_t err     = FSP_SUCCESS;
    uint16_t  counter = 0;

    if (RM_ZMOD4XXX_OPEN != p_ctrl->open)
    {
        /* Clear flag */
        p_ctrl->init_process_params.communication_finished = false;
    }

    /* Write data */
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_ZMOD4XXX_OPEN != p_ctrl->open)
    {
        /* Wait callback */
        while (false == p_ctrl->init_process_params.communication_finished)
        {
            rm_zmod4xxx_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_ZMOD4XXX_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN(RM_ZMOD4XXX_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read status from the ZMOD4XXX.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_read_status (rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * p_status)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Read status data */
    p_ctrl->register_address     = RM_ZMOD4XXX_ADDR_STATUS;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_status;
    write_read_params.dest_bytes = 1;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read sensor parameter from the ZMOD4XXX.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_UNSUPPORTED      Unsupport product ID.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_read_sensor_info (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;
    rm_comms_write_read_params_t     write_read_params;

    uint8_t  status;
    uint16_t product_id;
    uint32_t timeout_count = 0;

    do
    {
        /* Stop the previous measurement */
        err = rm_zmod4xxx_stop_measurement(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Read the status */
        err = rm_zmod4xxx_read_status(p_ctrl, &status);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Delay 200ms */
        err = rm_zmod4xxx_delay_ms(p_ctrl, RM_ZMOD4XXX_WAIT_TIME_200);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Increase the count */
        timeout_count++;
    } while ((0x00 != (status & RM_ZMOD4XXX_80H)) && (RM_ZMOD4XXX_1000 > timeout_count));

    FSP_ERROR_RETURN(RM_ZMOD4XXX_1000 > timeout_count, FSP_ERR_TIMEOUT);

    /* Read PID */
    p_ctrl->register_address     = RM_ZMOD4XXX_ADDR_PID;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = &p_ctrl->buf[0];
    write_read_params.dest_bytes = RM_ZMOD4XXX_LEN_PID;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check PID */
    product_id = (uint16_t) ((p_ctrl->buf[0] << 8) | p_ctrl->buf[1]);
    FSP_ERROR_RETURN(p_zmod4xxx_device->pid == product_id, FSP_ERR_UNSUPPORTED);

    /* Read the sensor configuration */
    p_ctrl->register_address     = RM_ZMOD4XXX_ADDR_CONF;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_zmod4xxx_device->config;
    write_read_params.dest_bytes = RM_ZMOD4XXX_LEN_CONF;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Read product data */
    p_ctrl->register_address     = RM_ZMOD4XXX_ADDR_PROD_DATA;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_zmod4xxx_device->prod_data;
    write_read_params.dest_bytes = p_zmod4xxx_device->meas_conf->prod_data_len;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculate measurement settings.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_calc_factor (zmod4xxx_conf * const conf, uint8_t * const hsp, uint8_t * const config)
{
    int16_t hsp_temp[RM_ZMOD4XXX_HSP_MAX];
    float   hspf;
    uint8_t i;

    i = 0;
    while (i < conf->h.len)
    {
        hsp_temp[i / 2] = (int16_t) (((uint16_t) conf->h.data_buf[i] << 8) + conf->h.data_buf[i + 1]);
        hspf            = (-((float) config[2] * RM_ZMOD4XXX_256F + config[3]) *
                           ((config[4] + RM_ZMOD4XXX_640F) * (float) (config[5] + hsp_temp[i / 2]) -
                            RM_ZMOD4XXX_512000F)) /
                          RM_ZMOD4XXX_12288000F;

        hsp[i]     = (uint8_t) ((uint16_t) hspf >> 8);
        hsp[i + 1] = (uint8_t) ((uint16_t) hspf & RM_ZMOD4XXX_FF);

        i = (uint8_t) (i + 2);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Initialize the sensor after power on.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_init_sensor (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;
    uint8_t hsp[RM_ZMOD4XXX_HSP_MAX * 2]               = {0};
    rm_comms_write_read_params_t write_read_params;
    uint8_t   i;
    uint8_t   bytes;
    uint8_t * p_src_tmp;
    uint8_t   status;

    /* Read address 0xB7 */
    err = rm_zmod4xxx_device_error_event_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Calculate the factor */
    err = rm_zmod4xxx_calc_factor(p_zmod4xxx_device->init_conf, hsp, p_zmod4xxx_device->config);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write H data */
    p_ctrl->buf[0] = p_zmod4xxx_device->init_conf->h.addr;
    bytes          = p_zmod4xxx_device->init_conf->h.len;
    p_src_tmp      = hsp;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write D data */
    p_ctrl->buf[0] = p_zmod4xxx_device->init_conf->d.addr;
    bytes          = p_zmod4xxx_device->init_conf->d.len;
    p_src_tmp      = p_zmod4xxx_device->init_conf->d.data_buf;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write M data */
    p_ctrl->buf[0] = p_zmod4xxx_device->init_conf->m.addr;
    bytes          = p_zmod4xxx_device->init_conf->m.len;
    p_src_tmp      = p_zmod4xxx_device->init_conf->m.data_buf;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write S data */
    p_ctrl->buf[0] = p_zmod4xxx_device->init_conf->s.addr;
    bytes          = p_zmod4xxx_device->init_conf->s.len;
    p_src_tmp      = p_zmod4xxx_device->init_conf->s.data_buf;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear IRQ pin */
    if (NULL != p_ctrl->p_irq_instance)
    {
        p_ctrl->init_process_params.measurement_finished = false;
    }

    /* Write the start signal */
    p_ctrl->buf[0] = RM_ZMOD4XXX_ADDR_CMD;
    p_ctrl->buf[1] = p_zmod4xxx_device->init_conf->start;
    err            = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (NULL != p_ctrl->p_irq_instance)
    {
        /* Wait IRQ interrupt */
        while (false == p_ctrl->init_process_params.measurement_finished)
        {
        }

        p_ctrl->init_process_params.measurement_finished = false;
    }
    else
    {
        do
        {
            /* Read the status */
            err = rm_zmod4xxx_read_status(p_ctrl, &status);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            /* Delay 50ms */
            err = rm_zmod4xxx_delay_ms(p_ctrl, RM_ZMOD4XXX_WAIT_TIME_50);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        } while (status & RM_ZMOD4XXX_STATUS_SEQUENCER_RUNNING_MASK);
    }

    /* Read R data */
    p_ctrl->register_address     = p_zmod4xxx_device->init_conf->r.addr;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = &p_ctrl->buf[0];
    write_read_params.dest_bytes = p_zmod4xxx_device->init_conf->r.len;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set specific parameters */
    p_zmod4xxx_device->mox_lr = (uint16_t) ((uint16_t) (p_ctrl->buf[0] << 8) | p_ctrl->buf[1]);
    p_zmod4xxx_device->mox_er = (uint16_t) ((uint16_t) (p_ctrl->buf[2] << 8) | p_ctrl->buf[3]);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Initialize the sensor for corresponding measurement.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_init_measurement (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;
    uint8_t   hsp[RM_ZMOD4XXX_HSP_MAX * 2]             = {0};
    uint8_t   i;
    uint8_t   bytes;
    uint8_t * p_src_tmp;

    /* Calculate the factor */
    err = rm_zmod4xxx_calc_factor(p_zmod4xxx_device->meas_conf, hsp, p_zmod4xxx_device->config);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write H data */
    p_ctrl->buf[0] = p_zmod4xxx_device->meas_conf->h.addr;
    bytes          = p_zmod4xxx_device->meas_conf->h.len;
    p_src_tmp      = hsp;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write D data */
    p_ctrl->buf[0] = p_zmod4xxx_device->meas_conf->d.addr;
    bytes          = p_zmod4xxx_device->meas_conf->d.len;
    p_src_tmp      = p_zmod4xxx_device->meas_conf->d.data_buf;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write M data */
    p_ctrl->buf[0] = p_zmod4xxx_device->meas_conf->m.addr;
    bytes          = p_zmod4xxx_device->meas_conf->m.len;
    p_src_tmp      = p_zmod4xxx_device->meas_conf->m.data_buf;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Write S data */
    p_ctrl->buf[0] = p_zmod4xxx_device->meas_conf->s.addr;
    bytes          = p_zmod4xxx_device->meas_conf->s.len;
    p_src_tmp      = p_zmod4xxx_device->meas_conf->s.data_buf;
    for (i = 1; i <= bytes; i++)
    {
        p_ctrl->buf[i] = *p_src_tmp;
        p_src_tmp++;
    }

    err = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], (uint32_t) (bytes + 1));
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Start the measurement.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_start_measurement (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;

    /* Write the start signal */
    p_ctrl->buf[0] = RM_ZMOD4XXX_ADDR_CMD;
    p_ctrl->buf[1] = p_zmod4xxx_device->meas_conf->start;
    err            = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop the measurement.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_stop_measurement (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Write the stop signal */
    p_ctrl->buf[0] = RM_ZMOD4XXX_ADDR_CMD;
    p_ctrl->buf[1] = 0;
    err            = rm_zmod4xxx_i2c_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read ADC values from the sensor.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_read_adc_result (rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * const adc_result)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;
    rm_comms_write_read_params_t     write_read_params;

    /* Read R data */
    p_ctrl->register_address     = p_zmod4xxx_device->meas_conf->r.addr;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = adc_result;
    write_read_params.dest_bytes = p_zmod4xxx_device->meas_conf->r.len;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Initialization processes of the ZMOD4XXX.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_UNSUPPORTED      Unsupport product ID.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_configuration (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;
    zmod4xxx_conf * p_data_set = (zmod4xxx_conf *) p_lib->p_data_set;

    /* Set ZMOD4XXX specific configurations */
    p_zmod4xxx_device->prod_data = (uint8_t *) p_lib->p_product_data;
    p_zmod4xxx_device->pid       = p_lib->product_id;
    p_zmod4xxx_device->init_conf = &p_data_set[0];
    if (RM_ZMOD4410_LIB_TYPE_IAQ_1ST_GEN_LOW_POWER != p_lib->lib_type)
    {
        p_zmod4xxx_device->meas_conf = &p_data_set[1];
    }
    else
    {
        p_zmod4xxx_device->meas_conf = &p_data_set[2];
    }

    /* Read sensor information */
    err = rm_zmod4xxx_read_sensor_info(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Initialize the sensor */
    err = rm_zmod4xxx_init_sensor(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Initialize the sensor for corresponding measurement */
    err = rm_zmod4xxx_init_measurement(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Check device error event.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_device_error_event_check (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Read device error event */
    p_ctrl->register_address     = RM_ZMOD4XXX_ADDR_DEV_ERR;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = &p_ctrl->buf[0];
    write_read_params.dest_bytes = 1;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}
