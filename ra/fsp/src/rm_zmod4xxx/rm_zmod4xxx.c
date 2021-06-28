/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "rm_zmod4xxx_lib_specific_configuration.h"
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
#define RM_ZMOD4XXX_B7                                 (0xB7)
#define RM_ZMOD4XXX_1E_3                               (1e-3)
#define RM_ZMOD4XXX_10E9                               (10e9)
#define RM_ZMOD4XXX_1E3                                (1e3)
#define RM_ZMOD4XXX_100F                               (100.0F)

#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4)

/* Definitions of Odor Parameter */
 #define RM_ZMOD4XXX_ODOR_PARAM_ALPHA                  (0.8F)
 #define RM_ZMOD4XXX_ODOR_PARAM_STOP_DELAY             (60)
 #define RM_ZMOD4XXX_ODOR_PARAM_THRESHOLD              (1.3F)
 #define RM_ZMOD4XXX_ODOR_PARAM_TAU                    (1800)
 #define RM_ZMOD4XXX_ODOR_PARAM_STAB_SAMPLES           (15)
#endif

#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7)

/* Definitions of OAQ 2nd gen Parameter */
 #define RM_ZMOD4XXX_DEFAULT_HUMIDITY       (50.0F)
 #define RM_ZMOD4XXX_DEFAULT_TEMPERATURE    (20.0F)
#endif

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
    .temperatureAndHumiditySet = RM_ZMOD4XXX_TemperatureAndHumiditySet,
};

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
extern fsp_err_t rm_zmod4xxx_timer_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_zmod4xxx_timer_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_zmod4xxx_timer_start(rm_zmod4xxx_ctrl_t * const p_api_ctrl, uint32_t const delay_ms);
extern fsp_err_t rm_zmod4xxx_timer_stop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_zmod4xxx_irq_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_zmod4xxx_irq_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/
uint8_t g_zmod4xxx_prod_data[RM_ZMOD4XXX_PROD_DATA_LEN];

static fsp_err_t rm_zmod4xxx_i2c_read(rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                      rm_comms_write_read_params_t const  params);
static fsp_err_t rm_zmod4xxx_i2c_write(rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                       uint8_t * const                     p_src,
                                       uint32_t const                      bytes);
static fsp_err_t rm_zmod4xxx_delay_ms(rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint32_t const delay_ms);
static fsp_err_t rm_zmod4xxx_read_status(rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * status);
static fsp_err_t rm_zmod4xxx_read_sensor_info(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_calc_factor(zmod4xxx_conf * conf, uint8_t * hsp, uint8_t * config);
static fsp_err_t rm_zmod4xxx_init_sensor(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_init_measurement(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_start_measurement(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_read_adc_result(rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * adc_result);
static fsp_err_t rm_zmod4xxx_stop_measurement(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_configuration(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_zmod4xxx_init_library(rm_zmod4xxx_instance_ctrl_t * const p_ctrl);

#if ((RM_ZMOD4XXX_CFG_OPERATION_MODE == 4) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6))
static fsp_err_t rm_zmod4xxx_calc_rmox(rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * adc_result, float * rmox);

#endif

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
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms_instance);
    FSP_ASSERT(NULL != p_cfg->p_timer_instance);
    FSP_ASSERT(NULL != p_cfg->p_zmod4xxx_device);
    FSP_ASSERT(NULL != p_cfg->p_zmod4xxx_handle);
    FSP_ASSERT(NULL != p_cfg->p_zmod4xxx_results);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg = p_cfg;

    /* Set instances */
    p_ctrl->p_comms_i2c_instance = p_cfg->p_comms_instance;
    p_ctrl->p_timer_instance     = p_cfg->p_timer_instance;
    p_ctrl->p_irq_instance       = p_cfg->p_irq_instance;

    /* Set ZMOD4XXX library specific */
    p_ctrl->p_zmod4xxx_device  = (void *) p_cfg->p_zmod4xxx_device;
    p_ctrl->p_zmod4xxx_handle  = (void *) p_cfg->p_zmod4xxx_handle;
    p_ctrl->p_zmod4xxx_results = (void *) p_cfg->p_zmod4xxx_results;

    /* Set parameters */
    p_ctrl->p_context        = p_cfg->p_context;
    p_ctrl->p_comms_callback = p_cfg->p_comms_callback;
    p_ctrl->p_irq_callback   = p_cfg->p_irq_callback;
    p_ctrl->status.flag      = false;
    p_ctrl->event            = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;

#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7)

    /* Set default temperature and humidity */
    p_ctrl->temperature = RM_ZMOD4XXX_DEFAULT_TEMPERATURE;
    p_ctrl->humidity    = RM_ZMOD4XXX_DEFAULT_HUMIDITY;
#endif

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Open timer */
    err = rm_zmod4xxx_timer_open(p_ctrl);
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
    err = rm_zmod4xxx_init_library(p_ctrl);
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

    /* Close timer */
    rm_zmod4xxx_timer_close(p_ctrl);

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
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Iaq1stGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data)
{
#if ((RM_ZMOD4XXX_CFG_OPERATION_MODE == 1) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 2))
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

 #if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    iaq_1st_gen_handle_t  * p_handle  = (iaq_1st_gen_handle_t *) p_ctrl->p_zmod4xxx_handle;
    iaq_1st_gen_results_t * p_results = (iaq_1st_gen_results_t *) p_ctrl->p_zmod4xxx_results;
    zmod4xxx_dev_t        * p_device  = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    int8_t lib_err = 0;

    /* Calculate IAQ 1st Gen. data form ADC data */
    lib_err = calc_iaq_1st_gen(p_handle,
                               p_device,
                               &p_raw_data->adc_data[0],
                               p_results);
    FSP_ERROR_RETURN(0 <= lib_err, FSP_ERR_ASSERTION);

    /* Set Data */
    p_zmod4xxx_data->rmox = p_results->rmox;
    p_zmod4xxx_data->rcda = p_results->rcda;
    p_zmod4xxx_data->iaq  = p_results->iaq;
    p_zmod4xxx_data->tvoc = p_results->tvoc;
    p_zmod4xxx_data->etoh = p_results->etoh;
    p_zmod4xxx_data->eco2 = p_results->eco2;
    FSP_ERROR_RETURN(IAQ_1ST_GEN_STABILIZATION != lib_err, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::iaq2ndGenDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Iaq2ndGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data)
{
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 3)
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

 #if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    iaq_2nd_gen_handle_t  * p_handle  = (iaq_2nd_gen_handle_t *) p_ctrl->p_zmod4xxx_handle;
    iaq_2nd_gen_results_t * p_results = (iaq_2nd_gen_results_t *) p_ctrl->p_zmod4xxx_results;
    zmod4xxx_dev_t        * p_device  = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    uint16_t                i;
    int8_t lib_err = 0;

    /* Calculate IAQ 2nd Gen. data form ADC data */
    lib_err = calc_iaq_2nd_gen(p_handle,
                               p_device,
                               &p_raw_data->adc_data[0],
                               p_results);
    FSP_ERROR_RETURN(0 <= lib_err, FSP_ERR_ASSERTION);

    /* Set Data */
    for (i = 0; i < 13; i++)
    {
        p_zmod4xxx_data->rmox[i] = p_results->rmox[i];
    }

    p_zmod4xxx_data->log_rcda = p_results->log_rcda;
    p_zmod4xxx_data->iaq      = p_results->iaq;
    p_zmod4xxx_data->tvoc     = p_results->tvoc;
    p_zmod4xxx_data->etoh     = p_results->etoh;
    p_zmod4xxx_data->eco2     = p_results->eco2;
    FSP_ERROR_RETURN(IAQ_2ND_GEN_STABILIZATION != lib_err, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::odorDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_OdorDataCalculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                         rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                         rm_zmod4xxx_odor_data_t * const p_zmod4xxx_data)
{
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4)
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

 #if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    float            rmox      = 0.0F;
    odor_params    * p_handle  = (odor_params *) p_ctrl->p_zmod4xxx_handle;
    odor_results_t * p_results = (odor_results_t *) p_ctrl->p_zmod4xxx_results;
    int8_t           lib_err   = 0;

    /* Calculate Odor data form ADC data */
    rm_zmod4xxx_calc_rmox(p_ctrl, &p_raw_data->adc_data[0], &rmox);
    lib_err = calc_odor(rmox, p_handle, p_results);
    FSP_ERROR_RETURN(0 <= lib_err, FSP_ERR_ASSERTION);

    /* Set Data */
    p_zmod4xxx_data->odor = p_results->conc_ratio;
    if (ON == p_results->cs_state)
    {
        p_zmod4xxx_data->control_signal = true;
    }
    else
    {
        p_zmod4xxx_data->control_signal = false;
    }

    FSP_ERROR_RETURN(ODOR_STABILIZATION != lib_err, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::sulfurOdorDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_SulfurOdorDataCalculate (rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                               rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                               rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data)
{
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 5)
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

 #if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    sulfur_odor_handle_t  * p_handle  = (sulfur_odor_handle_t *) p_ctrl->p_zmod4xxx_handle;
    sulfur_odor_results_t * p_results = (sulfur_odor_results_t *) p_ctrl->p_zmod4xxx_results;
    zmod4xxx_dev_t        * p_device  = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    uint16_t                i;
    int8_t lib_err = 0;

    /* Calculate Sulfur odor data form ADC data */
    lib_err = calc_sulfur_odor(p_handle,
                               p_device,
                               &p_raw_data->adc_data[0],
                               p_results);
    FSP_ERROR_RETURN(0 <= lib_err, FSP_ERR_ASSERTION);

    /* Set Data */
    for (i = 0; i < 9; i++)
    {
        p_zmod4xxx_data->rmox[i] = p_results->rmox[i];
    }

    p_zmod4xxx_data->intensity = p_results->intensity;
    if (SULFUR_ODOR_ACCEPTABLE == p_results->odor)
    {
        p_zmod4xxx_data->odor = RM_ZMOD4XXX_SULFUR_ODOR_ACCEPTABLE;
    }
    else
    {
        p_zmod4xxx_data->odor = RM_ZMOD4XXX_SULFUR_ODOR_UNACCEPTABLE;
    }

    FSP_ERROR_RETURN(SULFUR_ODOR_WARMUP != lib_err, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::oaq1stGenDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Oaq1stGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_oaq_1st_data_t * const p_zmod4xxx_data)
{
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6)
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

 #if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    oaq_base_handle_t * p_handle = (oaq_base_handle_t *) p_ctrl->p_zmod4xxx_handle;

    /* Calculate OAQ 1st Gen. data form ADC data */
    rm_zmod4xxx_calc_rmox(p_ctrl, &p_raw_data->adc_data[0], p_zmod4xxx_data->rmox);

    /* Calculation of results */
    p_zmod4xxx_data->aiq = calc_oaq_1st_gen(p_handle,
                                            p_zmod4xxx_data->rmox,
                                            RCDA_STRATEGY_ADJ,
                                            GAS_DETECTION_STRATEGY_AUTO,
                                            (float) D_RISING_M1,
                                            (float) D_FALLING_M1,
                                            (float) D_CLASS_M1);
    FSP_ERROR_RETURN(0 == p_handle->stabilization_sample, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when measurement finishes. To check measurement status either polling or
 * busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::oaq2ndGenDataCalculate
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Oaq2ndGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data)
{
#if (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7)
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

 #if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_zmod4xxx_data);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    oaq_2nd_gen_handle_t  * p_handle  = (oaq_2nd_gen_handle_t *) p_ctrl->p_zmod4xxx_handle;
    oaq_2nd_gen_results_t * p_results = (oaq_2nd_gen_results_t *) p_ctrl->p_zmod4xxx_results;
    zmod4xxx_dev_t        * p_device  = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    uint16_t                i;
    int8_t lib_err = 0;

    /* Calculate OAQ 1st Gen. data form ADC data */
    lib_err = calc_oaq_2nd_gen(p_handle,
                               p_device,
                               &p_raw_data->adc_data[0],
                               p_ctrl->humidity,
                               p_ctrl->temperature,
                               p_results);
    FSP_ERROR_RETURN(0 <= lib_err, FSP_ERR_ASSERTION);

    /* Set Data */
    for (i = 0; i < 8; i++)
    {
        p_zmod4xxx_data->rmox[i] = p_results->rmox[i];
    }

    p_zmod4xxx_data->ozone_concentration = p_results->O3_conc_ppb;
    p_zmod4xxx_data->fast_aqi            = p_results->FAST_AQI;
    p_zmod4xxx_data->epa_aqi             = p_results->EPA_AQI;
    FSP_ERROR_RETURN(OAQ_2ND_GEN_STABILIZATION != lib_err, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function is valid only for OAQ_2nd_Gen. This function should be called before DataCalculate.
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
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;

#if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_ZMOD4XXX_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->temperature = temperature;
    p_ctrl->humidity    = humidity;

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
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_args->p_context;
    rm_zmod4xxx_callback_args_t   zmod4xxx_callback_args;
    uint8_t status;

#if ((RM_ZMOD4XXX_CFG_OPERATION_MODE == 1) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4))
    zmod4xxx_dev_t * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
#endif

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
#if ((RM_ZMOD4XXX_CFG_OPERATION_MODE == 1) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4))
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

#else
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
#endif

            /* Clear flag */
            p_ctrl->status.flag = false;

            if (NULL != p_ctrl->p_comms_callback)
            {
                /* Call callback function */
                p_ctrl->p_comms_callback(&zmod4xxx_callback_args);
            }
        }
        else
        {
            if (NULL != p_ctrl->p_comms_callback)
            {
                /* Call callback function */
                p_ctrl->p_comms_callback(&zmod4xxx_callback_args);
            }
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
            rm_zmod4xxx_timer_stop(p_ctrl);
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
            rm_zmod4xxx_timer_stop(p_ctrl);
            FSP_ERROR_RETURN(RM_ZMOD4XXX_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN(RM_ZMOD4XXX_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Delay some milliseconds.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_delay_ms (rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint32_t const delay_ms)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Start timer */
    err = rm_zmod4xxx_timer_start(p_ctrl, delay_ms);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_ZMOD4XXX_OPEN != p_ctrl->open)
    {
        /* Wait timer callback */
        while (0 < p_ctrl->init_process_params.delay_ms)
        {
        }
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
    fsp_err_t                    err               = FSP_SUCCESS;
    zmod4xxx_dev_t             * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    rm_comms_write_read_params_t write_read_params;

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
    fsp_err_t                    err                          = FSP_SUCCESS;
    zmod4xxx_dev_t             * p_zmod4xxx_device            = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    uint8_t                      hsp[RM_ZMOD4XXX_HSP_MAX * 2] = {0};
    rm_comms_write_read_params_t write_read_params;
    uint8_t                      i;
    uint8_t                      bytes;
    uint8_t                    * p_src_tmp;
    uint8_t                      status;

    /* Read address 0xB7 */
    p_ctrl->register_address     = RM_ZMOD4XXX_B7;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = &p_ctrl->buf[0];
    write_read_params.dest_bytes = 1;
    err = rm_zmod4xxx_i2c_read(p_ctrl, write_read_params);
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
    fsp_err_t        err                          = FSP_SUCCESS;
    zmod4xxx_dev_t * p_zmod4xxx_device            = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    uint8_t          hsp[RM_ZMOD4XXX_HSP_MAX * 2] = {0};
    uint8_t          i;
    uint8_t          bytes;
    uint8_t        * p_src_tmp;

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
    fsp_err_t        err               = FSP_SUCCESS;
    zmod4xxx_dev_t * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;

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
    fsp_err_t                    err               = FSP_SUCCESS;
    zmod4xxx_dev_t             * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    rm_comms_write_read_params_t write_read_params;

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

#if ((RM_ZMOD4XXX_CFG_OPERATION_MODE == 4) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6))

/*******************************************************************************************************************//**
 * @brief Calculate mox resistance.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_calc_rmox (rm_zmod4xxx_instance_ctrl_t * const p_ctrl, uint8_t * adc_result, float * rmox)
{
    zmod4xxx_dev_t * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    uint8_t          i;
    uint16_t         adc_value  = 0;
    float          * p          = rmox;
    float            rmox_local = 0;

    i = 0;
    while (i < p_zmod4xxx_device->meas_conf->r.len)
    {
        adc_value = (uint16_t) ((((uint16_t) adc_result[i]) << 8) | adc_result[i + 1]);
        if (0.0 > (adc_value - p_zmod4xxx_device->mox_lr))
        {
            *p = (float) RM_ZMOD4XXX_1E_3;
            p++;
        }
        else if (0.0 >= (p_zmod4xxx_device->mox_er - adc_value))
        {
            *p = (float) RM_ZMOD4XXX_10E9;
            p++;
        }
        else
        {
            rmox_local = (float) p_zmod4xxx_device->config[0] * (float) RM_ZMOD4XXX_1E3 *
                         (float) (adc_value - p_zmod4xxx_device->mox_lr) /
                         (float) (p_zmod4xxx_device->mox_er - adc_value);
            *p = rmox_local;
            p++;
        }

        i = (uint8_t) (i + 2);
    }

    return FSP_SUCCESS;
}

#endif

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
    fsp_err_t        err               = FSP_SUCCESS;
    zmod4xxx_dev_t * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;

    /* Set ZMOD4XXX specific configurations */
    p_zmod4xxx_device->prod_data = g_zmod4xxx_prod_data;
    p_zmod4xxx_device->init_conf = &gs_zmod4xxx_sensor_type[0];
    p_zmod4xxx_device->meas_conf = &gs_zmod4xxx_sensor_type[1];
    p_zmod4xxx_device->pid       = RM_ZMOD4XXX_PID;

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
 * @brief Initialize the library of the ZMOD4XXX.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_ASSERTION        Error in library.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4xxx_init_library (rm_zmod4xxx_instance_ctrl_t * const p_ctrl)
{
    int8_t lib_err = 0;

#if ((RM_ZMOD4XXX_CFG_OPERATION_MODE == 1) || (RM_ZMOD4XXX_CFG_OPERATION_MODE == 2))
    iaq_1st_gen_handle_t * p_handle          = (iaq_1st_gen_handle_t *) p_ctrl->p_zmod4xxx_handle;
    zmod4xxx_dev_t       * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    lib_err = init_iaq_1st_gen(p_handle, p_zmod4xxx_device, RM_ZMOD4XXX_SAMPLE_PERIOD);
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 3)
    iaq_2nd_gen_handle_t * p_handle = (iaq_2nd_gen_handle_t *) p_ctrl->p_zmod4xxx_handle;
    lib_err = init_iaq_2nd_gen(p_handle);
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 5)
    sulfur_odor_handle_t * p_handle          = (sulfur_odor_handle_t *) p_ctrl->p_zmod4xxx_handle;
    zmod4xxx_dev_t       * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    lib_err = init_sulfur_odor(p_handle, p_zmod4xxx_device);
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 4)
    odor_params * p_handle = (odor_params *) p_ctrl->p_zmod4xxx_handle;
    p_handle->alpha                 = RM_ZMOD4XXX_ODOR_PARAM_ALPHA;
    p_handle->stop_delay            = RM_ZMOD4XXX_ODOR_PARAM_STOP_DELAY;
    p_handle->threshold             = RM_ZMOD4XXX_ODOR_PARAM_THRESHOLD;
    p_handle->tau                   = RM_ZMOD4XXX_ODOR_PARAM_TAU;
    p_handle->stabilization_samples = RM_ZMOD4XXX_ODOR_PARAM_STAB_SAMPLES;
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 6)
    oaq_base_handle_t * p_handle          = (oaq_base_handle_t *) p_ctrl->p_zmod4xxx_handle;
    zmod4xxx_dev_t    * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    init_oaq_1st_gen(p_handle, p_zmod4xxx_device->prod_data, STABILIZATION_SAMPLES);
#elif (RM_ZMOD4XXX_CFG_OPERATION_MODE == 7)
    oaq_2nd_gen_handle_t * p_handle          = (oaq_2nd_gen_handle_t *) p_ctrl->p_zmod4xxx_handle;
    zmod4xxx_dev_t       * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_ctrl->p_zmod4xxx_device;
    lib_err = init_oaq_2nd_gen(p_handle, p_zmod4xxx_device);
#else
#endif
    FSP_ERROR_RETURN(0 == lib_err, FSP_ERR_ASSERTION);

    return FSP_SUCCESS;
}
