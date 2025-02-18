/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "rm_rrh46410.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_RRH46410_OPEN                                 (('R' << 24U) | ('H' << 16U) | ('4' << 8U) | ('6' << 0U)) // Open state, R"RH46"410

/* Definitions of Timeout */
#define RM_RRH46410_TIMEOUT                              (100)

/* Definitions of Wait Time */
#define RM_RRH46410_WAIT_TIME_20                         (20)
#define RM_RRH46410_WAIT_TIME_50                         (50)
#define RM_RRH46410_WAIT_TIME_200                        (200)

/* Definitions of Retry max counts */
#define RM_RRH46410_RETRY_MAX_COUNTS                     (5)

/* Definitions of Command */
#define RM_RRH46410_COMMAND_SET_OPERATION_MODE           (0x11)
#define RM_RRH46410_COMMAND_SET_HUMIDITY                 (0x12)
#define RM_RRH46410_COMMAND_GET_MEASUREMENT_RESULTS      (0x18)

/* Definitions of operation mode */
#define RM_RRH46410_OPERATION_MODE_SUSPEND               (0x00)
#define RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN           (0x01)
#define RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN_ULP       (0x02)
#define RM_RRH46410_OPERATION_MODE_PBAQ                  (0x05)

/* Definitions of data size */
#define RM_RRH46410_LEN_COMMAND                          (1)
#define RM_RRH46410_LEN_ERROR_CODE                       (1)
#define RM_RRH46410_LEN_CHECKSUM                         (1)
#define RM_RRH46410_LEN_SET_OPERATION_MODE_WRITE         (1 + RM_RRH46410_LEN_COMMAND + RM_RRH46410_LEN_CHECKSUM)    // Request 1-bytes
#define RM_RRH46410_LEN_SET_OPERATION_MODE_READ          (0 + RM_RRH46410_LEN_ERROR_CODE + RM_RRH46410_LEN_CHECKSUM) // Response 0-bytes
#define RM_RRH46410_LEN_SET_HIMIDITY_WRITE               (1 + RM_RRH46410_LEN_COMMAND + RM_RRH46410_LEN_CHECKSUM)    // Request 1-bytes
#define RM_RRH46410_LEN_SET_HIMIDITY_READ                (0 + RM_RRH46410_LEN_ERROR_CODE + RM_RRH46410_LEN_CHECKSUM) // Response 0-bytes
#define RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_WRITE    (RM_RRH46410_LEN_COMMAND + RM_RRH46410_LEN_CHECKSUM)        // Request 0-bytes
#if (RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN == RM_RRH46410_CFG_OPERATION_MODE) || \
    (RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN_ULP == RM_RRH46410_CFG_OPERATION_MODE)                                   // IAQ 2nd gen and IAQ 2nd gen ULP
 #define RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_READ    (9 + RM_RRH46410_LEN_ERROR_CODE + RM_RRH46410_LEN_CHECKSUM) // Response 9-bytes
#elif (RM_RRH46410_OPERATION_MODE_PBAQ == RM_RRH46410_CFG_OPERATION_MODE)                                            // PBAQ
 #define RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_READ    (5 + RM_RRH46410_LEN_ERROR_CODE + RM_RRH46410_LEN_CHECKSUM) // Response 5-bytes
#else
 #define RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_READ    (0)
#endif

/* Definitions of data position */
#define RM_RRH46410_POSITION_ERROR_CODE                  (0)
#define RM_RRH46410_POSITION_SAMPLE_ID                   (1)

/* Definitions of warm up */
#if (RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN == RM_RRH46410_CFG_OPERATION_MODE)       // IAQ 2nd gen
 #define RM_RRH46410_WARMUP_COUNTS                       (100)
#elif (RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN_ULP == RM_RRH46410_CFG_OPERATION_MODE) // IAQ 2nd gen ULP
 #define RM_RRH46410_WARMUP_COUNTS                       (10)
#elif (RM_RRH46410_OPERATION_MODE_PBAQ == RM_RRH46410_CFG_OPERATION_MODE)            // PBAQ
 #define RM_RRH46410_WARMUP_COUNTS                       (60)
#else
 #define RM_RRH46410_WARMUP_COUNTS                       (0)
#endif

/* Definitions of Mask */
#define RM_RRH46410_MASK_INVALID_CMMAND                  (0x80)                                        // Invalid command is sent
#define RM_RRH46410_MASK_SENDING_WRONG_CHECKSUM          (0x40)                                        // Wrong checksum is sent
#define RM_RRH46410_MASK_INTERNAL_ERROR                  (0x20)                                        // Internal error occurs.
#define RM_RRH46410_MASK_DATA_NOT_READY                  (0x10)                                        // Data requested before data is available.
#define RM_RRH46410_MASK_OPERATION_MODE                  (0x0F)                                        // Error code for operation mode

/* Definitions of error codes */
#define RM_RRH46410_ERROR_CODE_INVALID_CMMAND            (0x80)                                        // Invalid command is sent
#define RM_RRH46410_ERROR_CODE_SENDING_WRONG_CHECKSUM    (0x40)                                        // Wrong checksum is sent
#define RM_RRH46410_ERROR_CODE_INTERNAL_ERROR            (0x20)                                        // Internal error occurs.
#define RM_RRH46410_ERROR_CODE_DATA_NOT_READY            (0x10)                                        // Data requested before data is available.
#define RM_RRH46410_ERROR_CODE_DAMAGE                    (0x0A)                                        // Gas sensor may be damaged
#define RM_RRH46410_ERROR_CODE_POWR_ON_RESET             (0x09)                                        // Power-on reset event

/* Definitions of encoded humidity */
#define RM_RRH46410_ENCODED_HUMIDITY(humidity_float)    (uint8_t) ((humidity_float / 100.0F) * 255.0F) // float -> uint8_t

/* Definitions of Calculation */
#define RM_RRH46410_1000F      (1000.0F)
#define RM_RRH46410_100F       (100.0F)
#define RM_RRH46410_10F        (10.0F)

/* Definitions of Shift */
#define RM_RRH46410_SHIFT_8    (8)

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_zmod4xxx_api_t const g_zmod4xxx_on_rrh46410 =
{
    .open                      = RM_RRH46410_Open,
    .close                     = RM_RRH46410_Close,
    .measurementStart          = RM_RRH46410_MeasurementStart,
    .measurementStop           = RM_RRH46410_MeasurementStop,
    .read                      = RM_RRH46410_Read,
    .iaq2ndGenDataCalculate    = RM_RRH46410_Iaq2ndGenDataCalculate,
    .pbaqDataCalculate         = RM_RRH46410_PbaqDataCalculate,
    .temperatureAndHumiditySet = RM_RRH46410_TemperatureAndHumiditySet,
};

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
extern fsp_err_t rm_rrh46410_delay_ms(rm_zmod4xxx_ctrl_t * const p_ctrl, uint32_t const delay_ms);
extern fsp_err_t rm_rrh46410_irq_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_rrh46410_irq_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
void             rm_rrh46410_comms_i2c_callback(rm_comms_callback_args_t * p_args);

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

static fsp_err_t rm_rrh46410_i2c_read(rm_rrh46410_instance_ctrl_t * const p_ctrl,
                                      rm_comms_write_read_params_t const  params);
static fsp_err_t rm_rrh46410_start_measurement(rm_rrh46410_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_rrh46410_stop_measurement(rm_rrh46410_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_rrh46410_read_measurement_result(rm_rrh46410_instance_ctrl_t * const p_ctrl,
                                                     uint8_t * const                     p_raw_data);
static fsp_err_t           rm_rrh46410_humidty_set(rm_rrh46410_instance_ctrl_t * const p_ctrl, float const humidity);
static uint8_t             rm_rrh46410_checksum_calculate(uint8_t * const p_buf, uint32_t length);
static rm_zmod4xxx_event_t rm_rrh46410_error_code_check(uint8_t const error_code);
static fsp_err_t           rm_rrh46410_stabilizaiton_check(rm_rrh46410_instance_ctrl_t * const p_ctrl,
                                                           uint8_t const                       sample_id);

/*******************************************************************************************************************//**
 * @addtogroup RM_RRH46410
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the RRH46410 sensor module.
 * Implements @ref rm_zmod4xxx_api_t::open.
 *
 * @retval FSP_SUCCESS              RRH46410 successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_Open (rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms_instance);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Set instances */
    p_ctrl->p_cfg                = p_cfg;
    p_ctrl->p_comms_i2c_instance = p_cfg->p_comms_instance;
    p_ctrl->p_irq_instance       = p_cfg->p_irq_instance;

    /* Set parameters */
    p_ctrl->p_context        = p_cfg->p_context;
    p_ctrl->p_comms_callback = p_cfg->p_comms_callback;
    p_ctrl->p_irq_callback   = p_cfg->p_irq_callback;
    p_ctrl->prev_sample_id   = 0;
    p_ctrl->warmup_counts    = RM_RRH46410_WARMUP_COUNTS;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Open IRQ */
    if (NULL != p_ctrl->p_irq_instance)
    {
        err = rm_rrh46410_irq_open(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* Stop a previous measurement */
    err = rm_rrh46410_stop_measurement(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check if everything is okay */
    p_ctrl->open = RM_RRH46410_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when close the sensor module. Implements @ref rm_zmod4xxx_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_Close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Close IRQ */
    if (NULL != p_ctrl->p_irq_instance)
    {
        rm_rrh46410_irq_close(p_ctrl);
    }

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when start a measurement.
 * Implements @ref rm_zmod4xxx_api_t::measurementStart.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_MeasurementStart (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear parameters */
    p_ctrl->prev_sample_id = 0;
    p_ctrl->warmup_counts  = RM_RRH46410_WARMUP_COUNTS;
    p_ctrl->event          = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Start the measurement */
    err = rm_rrh46410_start_measurement(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when stop a measurement.
 * Implements @ref rm_zmod4xxx_api_t::measurementStop.
 *
 * @retval FSP_SUCCESS              Successfully stopped.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_MeasurementStop (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop the measurement */
    err = rm_rrh46410_stop_measurement(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called to get measurement results after measurement finishes.
 * To check measurement status either polling or busy/interrupt pin can be used.
 * Implements @ref rm_zmod4xxx_api_t::read
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_Read (rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read measurement results */
    err = rm_rrh46410_read_measurement_result(p_ctrl, (uint8_t *) p_raw_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when calculating gas data from measurement results.
 * Implements @ref rm_zmod4xxx_api_t::iaq2ndGenDataCalculate
 *
 * @retval FSP_SUCCESS                             Successfully gas data is calculated.
 * @retval FSP_ERR_ASSERTION                       Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                        Module is not opened configured.
 * @retval FSP_ERR_UNSUPPORTED                     Unsupported operation mode.
 * @retval FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED Measurement is not finished.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_Iaq2ndGenDataCalculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                              rm_zmod4xxx_iaq_2nd_data_t * const p_rrh46410_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_rrh46410_data);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Calculate IAQ 2nd Gen. data */
#if (RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN == RM_RRH46410_CFG_OPERATION_MODE) || \
    (RM_RRH46410_OPERATION_MODE_IAQ_2ND_GEN_ULP == RM_RRH46410_CFG_OPERATION_MODE) // IAQ 2nd gen and IAQ 2nd gen ULP

    /* Check if measurement is complete. */
    FSP_ERROR_RETURN(RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE == p_ctrl->event, FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED);
    p_ctrl->event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Calculate Data from measurement results */
    p_rrh46410_data->sample_id = p_raw_data->adc_data[1];
    p_rrh46410_data->iaq       = (float) p_raw_data->adc_data[2] / RM_RRH46410_10F;
    p_rrh46410_data->tvoc      = (float) (p_raw_data->adc_data[3] + (p_raw_data->adc_data[4] << RM_RRH46410_SHIFT_8)) /
                                 RM_RRH46410_100F;
    p_rrh46410_data->etoh = (float) (p_raw_data->adc_data[5] + (p_raw_data->adc_data[6] << RM_RRH46410_SHIFT_8)) /
                            RM_RRH46410_100F;
    p_rrh46410_data->eco2    = (float) (p_raw_data->adc_data[7] + (p_raw_data->adc_data[8] << RM_RRH46410_SHIFT_8));
    p_rrh46410_data->rel_iaq = (float) p_raw_data->adc_data[9] * RM_RRH46410_10F;

    /* Check if sensor is in stabilization phase */
    err =
        rm_rrh46410_stabilizaiton_check(p_ctrl, p_rrh46410_data->sample_id);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(err);
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_rrh46410_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when calculating gas data from measurement results.
 * Implements @ref rm_zmod4xxx_api_t::pbaqDataCalculate
 *
 * @retval FSP_SUCCESS                             Successfully gas data is calculated.
 * @retval FSP_ERR_ASSERTION                       Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                        Module is not opened configured.
 * @retval FSP_ERR_UNSUPPORTED                     Unsupported operation mode.
 * @retval FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED Measurement is not finished.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_PbaqDataCalculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                         rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                         rm_zmod4xxx_pbaq_data_t * const p_rrh46410_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_rrh46410_data);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Calculate PBAQ data */
#if (RM_RRH46410_OPERATION_MODE_PBAQ == RM_RRH46410_CFG_OPERATION_MODE) // PBAQ

    /* Check if measurement is complete. */
    FSP_ERROR_RETURN(RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE == p_ctrl->event, FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED);
    p_ctrl->event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Calculate Data from measurement results */
    p_rrh46410_data->sample_id = p_raw_data->adc_data[1];
    p_rrh46410_data->tvoc      = (float) (p_raw_data->adc_data[2] + (p_raw_data->adc_data[3] << RM_RRH46410_SHIFT_8)) /
                                 RM_RRH46410_1000F;
    p_rrh46410_data->etoh = (float) (p_raw_data->adc_data[4] + (p_raw_data->adc_data[5] << RM_RRH46410_SHIFT_8)) /
                            RM_RRH46410_1000F;

    /* Check if sensor is in stabilization phase */
    err =
        rm_rrh46410_stabilizaiton_check(p_ctrl, p_rrh46410_data->sample_id);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(err);
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_rrh46410_data);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief  This function should be called before Read. Humidity measurements are needed for ambient compensation.
 * temperature is not supported.
 * Implements @ref rm_zmod4xxx_api_t::temperatureAndHumiditySet
 *
 * @retval FSP_SUCCESS                            Successfully humidity is set.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                       Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_TemperatureAndHumiditySet (rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                 float                      temperature,
                                                 float                      humidity)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_api_ctrl;

    FSP_PARAMETER_NOT_USED(temperature);

#if RM_RRH46410_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_RRH46410_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set humidity */
    err = rm_rrh46410_humidty_set(p_ctrl, humidity);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_RRH46410)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief RM_RRH46410 callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_rrh46410_comms_i2c_callback (rm_comms_callback_args_t * p_args)
{
    rm_rrh46410_instance_ctrl_t * p_ctrl = (rm_rrh46410_instance_ctrl_t *) p_args->p_context;
    rm_zmod4xxx_callback_args_t   rrh46410_callback_args;
    uint8_t checksum = 0;

    /* Set context */
    rrh46410_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            rrh46410_callback_args.event = RM_ZMOD4XXX_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            rrh46410_callback_args.event = RM_ZMOD4XXX_EVENT_ERROR;
            break;
        }
    }

    if (RM_RRH46410_OPEN != p_ctrl->open)
    {
        /* Set flag */
        p_ctrl->init_process_params.communication_finished = true;

        /* Set event */
        p_ctrl->init_process_params.event = rrh46410_callback_args.event;
    }
    else
    {
        if (NULL != p_ctrl->p_read_data)
        {
            /* Check error codes and set callback event */
            rrh46410_callback_args.event =
                rm_rrh46410_error_code_check(p_ctrl->p_read_data[RM_RRH46410_POSITION_ERROR_CODE]);
            if (RM_ZMOD4XXX_EVENT_SUCCESS == rrh46410_callback_args.event)
            {
                /* Check checksum */
                checksum = rm_rrh46410_checksum_calculate(&p_ctrl->p_read_data[0],
                                                          p_ctrl->read_bytes - RM_RRH46410_LEN_CHECKSUM);
                if (p_ctrl->p_read_data[p_ctrl->read_bytes - RM_RRH46410_LEN_CHECKSUM] != checksum)
                {
                    /* Checksum error */
                    rrh46410_callback_args.event = RM_ZMOD4XXX_EVENT_ERROR;
                }

                /* When sending Get Measurement Results command. */
                if ((RM_ZMOD4XXX_EVENT_SUCCESS == rrh46410_callback_args.event) &&
                    (RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_READ == p_ctrl->read_bytes))
                {
                    if (NULL == p_ctrl->p_irq_instance)
                    {
                        /* Set event after reading measurement results */
                        if (p_ctrl->prev_sample_id != p_ctrl->p_read_data[RM_RRH46410_POSITION_SAMPLE_ID])
                        {
                            rrh46410_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
                            p_ctrl->event                = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
                        }
                        else
                        {
                            rrh46410_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;
                            p_ctrl->event                = RM_ZMOD4XXX_EVENT_MEASUREMENT_NOT_COMPLETE;
                        }
                    }
                    else
                    {
                        /* IRQ signal already received */
                        rrh46410_callback_args.event = RM_ZMOD4XXX_EVENT_MEASUREMENT_COMPLETE;
                    }
                }
            }
        }
        else
        {
            rrh46410_callback_args.event = RM_ZMOD4XXX_EVENT_ERROR;
        }

        if (NULL != p_ctrl->p_comms_callback)
        {
            /* Call callback function */
            p_ctrl->p_comms_callback(&rrh46410_callback_args);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief Set callback event from error code.
 **********************************************************************************************************************/
static rm_zmod4xxx_event_t rm_rrh46410_error_code_check (uint8_t const error_code)
{
    if ((RM_RRH46410_ERROR_CODE_INVALID_CMMAND == (error_code & RM_RRH46410_MASK_INVALID_CMMAND)) ||
        (RM_RRH46410_ERROR_CODE_SENDING_WRONG_CHECKSUM == (error_code & RM_RRH46410_MASK_SENDING_WRONG_CHECKSUM)) ||
        (RM_RRH46410_ERROR_CODE_INTERNAL_ERROR == (error_code & RM_RRH46410_MASK_INTERNAL_ERROR)) ||
        (RM_RRH46410_ERROR_CODE_DATA_NOT_READY == (error_code & RM_RRH46410_MASK_DATA_NOT_READY)))
    {
        return RM_ZMOD4XXX_EVENT_ERROR;
    }

    if (RM_RRH46410_ERROR_CODE_DAMAGE == (error_code & RM_RRH46410_MASK_OPERATION_MODE))
    {
        return RM_ZMOD4XXX_EVENT_DEV_ERR_DAMAGE;
    }

    if (RM_RRH46410_ERROR_CODE_POWR_ON_RESET == (error_code & RM_RRH46410_MASK_OPERATION_MODE))
    {
        return RM_ZMOD4XXX_EVENT_DEV_ERR_POWER_ON_RESET;
    }

    return RM_ZMOD4XXX_EVENT_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Check if sensor is in stabilization phase.
 * @retval FSP_SUCCESS                             Data is ready.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION         Module is in stabilization phase.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh46410_stabilizaiton_check (rm_rrh46410_instance_ctrl_t * const p_ctrl, uint8_t const sample_id)
{
    int16_t sample_id_diff = 0;

    if (p_ctrl->warmup_counts)
    {
        sample_id_diff         = (int16_t) (sample_id - p_ctrl->prev_sample_id);
        p_ctrl->prev_sample_id = sample_id;
        if ((0 < sample_id_diff) && (sample_id_diff <= p_ctrl->warmup_counts))
        {
            /* Sensor is in stabilization phase */
            p_ctrl->warmup_counts -= sample_id_diff;
        }
        else
        {
            /* Sensor is ready. */
            p_ctrl->warmup_counts = 0;
        }
    }

    FSP_ERROR_RETURN(0 == p_ctrl->warmup_counts, FSP_ERR_SENSOR_IN_STABILIZATION);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief I2C wrapper function to read from rrh46410 sensor.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh46410_i2c_read (rm_rrh46410_instance_ctrl_t * const p_ctrl,
                                       rm_comms_write_read_params_t const  params)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint16_t  counter      = 0;
    uint16_t  retry_counts = RM_RRH46410_RETRY_MAX_COUNTS;

    do
    {
        if (RM_RRH46410_OPEN != p_ctrl->open)
        {
            /* Clear flag */
            p_ctrl->init_process_params.communication_finished = false;
        }

        /* WriteRead data */
        err = p_ctrl->p_comms_i2c_instance->p_api->writeRead(p_ctrl->p_comms_i2c_instance->p_ctrl, params);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (RM_RRH46410_OPEN != p_ctrl->open)
        {
            /* Wait callback */
            while (false == p_ctrl->init_process_params.communication_finished)
            {
                rm_rrh46410_delay_ms(p_ctrl, 1);
                counter++;
                FSP_ERROR_RETURN(RM_RRH46410_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
            }

            /* Retry counts decrement */
            retry_counts--;
        }
    } while ((RM_RRH46410_OPEN != p_ctrl->open) && (RM_ZMOD4XXX_EVENT_SUCCESS != p_ctrl->init_process_params.event) &&
             (0 < retry_counts));

    /* Check callback event */
    FSP_ERROR_RETURN(RM_ZMOD4XXX_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Start the measurement.
 *
 * @retval FSP_SUCCESS              Successfully start.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh46410_start_measurement (rm_rrh46410_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Set write data */
    p_ctrl->write_buf[0] = RM_RRH46410_COMMAND_SET_OPERATION_MODE;
    p_ctrl->write_buf[1] = RM_RRH46410_CFG_OPERATION_MODE;
    p_ctrl->write_buf[2] = rm_rrh46410_checksum_calculate(&p_ctrl->write_buf[0],
                                                          RM_RRH46410_LEN_SET_OPERATION_MODE_WRITE -
                                                          RM_RRH46410_LEN_CHECKSUM);

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = &p_ctrl->read_buf[0];
    p_ctrl->read_bytes  = RM_RRH46410_LEN_SET_OPERATION_MODE_READ;

    /* Send the start command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = RM_RRH46410_LEN_SET_OPERATION_MODE_WRITE;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh46410_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop the measurement.
 *
 * @retval FSP_SUCCESS              Successfully stop.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh46410_stop_measurement (rm_rrh46410_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the stop signal */
    p_ctrl->write_buf[0] = RM_RRH46410_COMMAND_SET_OPERATION_MODE;
    p_ctrl->write_buf[1] = RM_RRH46410_OPERATION_MODE_SUSPEND;
    p_ctrl->write_buf[2] = rm_rrh46410_checksum_calculate(&p_ctrl->write_buf[0],
                                                          RM_RRH46410_LEN_SET_OPERATION_MODE_WRITE -
                                                          RM_RRH46410_LEN_CHECKSUM);

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = &p_ctrl->read_buf[0];
    p_ctrl->read_bytes  = RM_RRH46410_LEN_SET_OPERATION_MODE_READ;

    /* Send the stop command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = RM_RRH46410_LEN_SET_OPERATION_MODE_WRITE;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh46410_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read measurement results from the sensor.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh46410_read_measurement_result (rm_rrh46410_instance_ctrl_t * const p_ctrl,
                                                      uint8_t * const                     p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the commands */
    p_ctrl->write_buf[0] = RM_RRH46410_COMMAND_GET_MEASUREMENT_RESULTS;
    p_ctrl->write_buf[1] = rm_rrh46410_checksum_calculate(&p_ctrl->write_buf[0],
                                                          RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_WRITE -
                                                          RM_RRH46410_LEN_CHECKSUM);

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = p_raw_data;
    p_ctrl->read_bytes  = RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_READ;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = RM_RRH46410_LEN_GET_MEASUREMENT_RESULTS_WRITE;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh46410_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write current humidity to the sensor.
 *
 * @retval FSP_SUCCESS              Successfully set.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh46410_humidty_set (rm_rrh46410_instance_ctrl_t * const p_ctrl, float const humidity)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the commands */
    p_ctrl->write_buf[0] = RM_RRH46410_COMMAND_SET_HUMIDITY;
    p_ctrl->write_buf[1] = RM_RRH46410_ENCODED_HUMIDITY(humidity);
    p_ctrl->write_buf[2] = rm_rrh46410_checksum_calculate(&p_ctrl->write_buf[0],
                                                          RM_RRH46410_LEN_SET_HIMIDITY_WRITE -
                                                          RM_RRH46410_LEN_CHECKSUM);

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = &p_ctrl->read_buf[0];
    p_ctrl->read_bytes  = RM_RRH46410_LEN_SET_HIMIDITY_READ;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = RM_RRH46410_LEN_SET_HIMIDITY_WRITE;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh46410_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculate checksum.
 **********************************************************************************************************************/
static uint8_t rm_rrh46410_checksum_calculate (uint8_t * const p_buf, uint32_t length)
{
    uint8_t   checksum = 0;
    uint32_t  i;
    uint8_t * p_data = p_buf;

    for (i = 0; i < length; i++)
    {
        checksum += *p_data;
        p_data++;
    }

    return ~checksum;
}
