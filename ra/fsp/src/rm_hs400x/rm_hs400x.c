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
#include "rm_hs400x.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_HS400X_OPEN                                   (0x561AB59CUL) // Open state

/* Definitions of HS400X measurement type */
#define RM_HS400X_HOLD_MEASUREMENT                       (1)
#define RM_HS400X_NO_HOLD_MEASUREMENT                    (2)
#define RM_HS400X_PERIODIC_MEASUREMENT                   (3)

/* Definitions of HS400X data size */
#if RM_HS400X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE
 #define RM_HS400X_DATA_SIZE                             (5) // Both humidity and temperature
#else
 #define RM_HS400X_DATA_SIZE                             (3) // Temperature only
#endif
#if RM_HS400X_PERIODIC_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
 #define RM_HS400X_THRESHOLDS_DATA_SIZE                  (18)
#endif

/* Definitions of HS400X register address */
#define RM_HS400X_REG_ADDR_RESOLUTION                    (0x00)
#if RM_HS400X_PERIODIC_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
 #define RM_HS400X_REG_ADDR_PERIODIC_MEASUREMENT         (0x02)
 #define RM_HS400X_REG_ADDR_RESET_THRESHOLD_TEMP_HIGH    (0x05)
#endif

/* Definitions of Mask Data for A/D data */
#define RM_HS400X_MASK_DATA_0X3F                         (0x3F)
#define RM_HS400X_MASK_RESOLUTION                        (0xF0)
#define RM_HS400X_MASK_PERIODIC_MEASUREMENT              (0x0E)
#define RM_HS400X_MASK_ALERT_ENABLE_SETTINGS             (0xF0)
#define RM_HS400X_MASK_THRESHOLD_UPPER                   (0x3F)
#define RM_HS400X_MASK_THRESHOLD_LOWER                   (0xFF)
#define RM_HS400X_MASK_TEMP_HIGH_ALERT                   (0x08)
#define RM_HS400X_MASK_TEMP_LOW_ALERT                    (0x04)
#define RM_HS400X_MASK_HUMI_HIGH_ALERT                   (0x02)
#define RM_HS400X_MASK_HUMI_LOW_ALERT                    (0x01)

/* Definitions for Calculation */
#define RM_HS400X_CALC_STATIC_VALUE                      (16383.0F)
#define RM_HS400X_CALC_HUMD_VALUE_100                    (100.0F)
#define RM_HS400X_CALC_TEMP_C_VALUE_165                  (165.0F)
#define RM_HS400X_CALC_TEMP_C_VALUE_40                   (40.0F)
#define RM_HS400X_CALC_DECIMAL_VALUE_100                 (100.0F)
#define RM_HS400X_CALC_CRC_ADC_DATA_LENGTH               (4)
#define RM_HS400X_CALC_CRC_8BITS_LENGTH                  (8)
#define RM_HS400X_CALC_CRC_POLYNOMIAL                    (0x1D)
#define RM_HS400X_CALC_CRC_INITIAL_VALUE                 (0xFF)
#define RM_HS400X_CALC_CRC_FINAL_XOR                     (0x00)
#define RM_HS400X_CACL_CRC_0X80                          (0x80)
#define RM_HS400X_CACL_CRC_MASK_MSB                      (0x80)

/* Definitions for Commands */
#if RM_HS400X_HOLD_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
 #if RM_HS400X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE
  #define RM_HS400X_COMMAND_MEASUREMENT                  (0xE5)
 #else
  #define RM_HS400X_COMMAND_MEASUREMENT                  (0xE3)
 #endif
#elif RM_HS400X_NO_HOLD_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
 #if RM_HS400X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE
  #define RM_HS400X_COMMAND_MEASUREMENT                  (0xF5)
 #else
  #define RM_HS400X_COMMAND_MEASUREMENT                  (0xF3)
 #endif
#elif RM_HS400X_PERIODIC_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
 #define RM_HS400X_COMMAND_START_PERIODIC_MEASUREMENT    (0x80)
#else
#endif
#define RM_HS400X_COMMAND_READ_REGISTER                  (0xA7)
#define RM_HS400X_COMMAND_WRITE_REGISTER                 (0xA6)
#define RM_HS400X_COMMAND_STOP_PERIODIC_MEASUREMENT      (0x30)
#define RM_HS400X_COMMAND_READ_SENSOR_ID                 (0xD7)

/* Definitions of Timeout */
#define RM_HS400X_TIMEOUT                                (1000)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global function prototypes
 **********************************************************************************************************************/
void rm_hs400x_comms_i2c_callback(rm_comms_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
extern fsp_err_t rm_hs400x_delay_ms(rm_hs400x_ctrl_t * const p_ctrl, uint32_t const delay_ms);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_write(rm_hs400x_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
static fsp_err_t rm_hs400x_read(rm_hs400x_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
static fsp_err_t rm_hs400x_write_read(rm_hs400x_ctrl_t * const p_api_ctrl, rm_comms_write_read_params_t const params);
static fsp_err_t rm_hs400x_all_measurements_stop(rm_hs400x_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_hs400x_periodic_measurement_stop(rm_hs400x_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_hs400x_resolution_set(rm_hs400x_ctrl_t * const                 p_api_ctrl,
                                          rm_hs400x_temperature_resolution_t const temperature,
                                          rm_hs400x_humidity_resolution_t const    humidity);
static fsp_err_t rm_hs400x_crc_execute(rm_hs400x_raw_data_t * const p_raw_data);

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_hs400x_api_t const g_hs400x_on_hs400x =
{
    .open             = RM_HS400X_Open,
    .close            = RM_HS400X_Close,
    .measurementStart = RM_HS400X_MeasurementStart,
    .measurementStop  = RM_HS400X_MeasurementStop,
    .read             = RM_HS400X_Read,
    .dataCalculate    = RM_HS400X_DataCalculate,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_HS400X
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the HS400X middleware module. Implements @ref rm_hs400x_api_t::open.
 *
 * Example:
 * @snippet rm_hs400x_example.c RM_HS400X_Open
 *
 * @retval FSP_SUCCESS              HS400X successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_HS400X_Open (rm_hs400x_ctrl_t * const p_api_ctrl, rm_hs400x_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
#if RM_HS400X_PERIODIC_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
    rm_comms_write_read_params_t write_read_params;
#endif

#if RM_HS400X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms_instance);
    FSP_ERROR_RETURN(RM_HS400X_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg                     = p_cfg;
    p_ctrl->p_comms_i2c_instance      = p_cfg->p_comms_instance;
    p_ctrl->p_context                 = p_cfg->p_context;
    p_ctrl->p_comms_callback          = p_cfg->p_comms_callback;
    p_ctrl->periodic_measurement_stop = false;
    p_ctrl->no_hold_measurement_read  = false;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Stop previous measurements */
    err = rm_hs400x_all_measurements_stop(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set Temperature and humidity resolution */
    err = rm_hs400x_resolution_set(p_ctrl, p_ctrl->p_cfg->temperature_resolution, p_ctrl->p_cfg->humidity_resolution);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if RM_HS400X_PERIODIC_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE

    /* Read default register data for periodic measurement */
    p_ctrl->write_buf[0]         = RM_HS400X_COMMAND_READ_REGISTER;
    p_ctrl->write_buf[1]         = RM_HS400X_REG_ADDR_PERIODIC_MEASUREMENT;
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 2;
    write_read_params.p_dest     = &p_ctrl->periodic_measurement_register[0];
    write_read_params.dest_bytes = 1;
    err = rm_hs400x_write_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set open flag */
    p_ctrl->open = RM_HS400X_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified HS400X control block. Implements @ref rm_hs400x_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_HS400X_Close (rm_hs400x_ctrl_t * const p_api_ctrl)
{
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;

#if RM_HS400X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS400X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when start one shot measurement.
 * Sends the command of measurement to HS400X and start a measurement.
 * This function supports No-Hold measurement and Periodic measurement only.
 * If Hold measurement is enabled, please call RM_HS400X_Read() without calling this function.
 * In Periodic measurement, if the periodic measurement has already run, RM_HS400X_EVENT_ERROR is received in callback
 * because HS400x device replies with NACK.
 * Implements @ref rm_hs400x_api_t::measurementStart.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 * @retval FSP_ERR_UNSUPPORTED      Hold measurement is unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_HS400X_MeasurementStart (rm_hs400x_ctrl_t * const p_api_ctrl)
{
#if RM_HS400X_HOLD_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
#else
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;

 #if RM_HS400X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS400X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Write the measurement start command */
 #if RM_HS400X_NO_HOLD_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
    p_ctrl->write_buf[0] = RM_HS400X_COMMAND_MEASUREMENT;
    err = rm_hs400x_write(p_ctrl, &p_ctrl->write_buf[0], 1);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #else

    /* Settings for periodic measurement */
    p_ctrl->periodic_measurement_register[0] &= RM_HS400X_MASK_PERIODIC_MEASUREMENT;
    p_ctrl->periodic_measurement_register[0] |=
        ((uint8_t) p_ctrl->p_cfg->frequency | RM_HS400X_COMMAND_START_PERIODIC_MEASUREMENT);

    /* Start measurement and read ADC data */
    p_ctrl->write_buf[0] = RM_HS400X_COMMAND_WRITE_REGISTER;
    p_ctrl->write_buf[1] = RM_HS400X_REG_ADDR_PERIODIC_MEASUREMENT;
    p_ctrl->write_buf[2] = p_ctrl->periodic_measurement_register[0];
    err = rm_hs400x_write(p_ctrl, &p_ctrl->write_buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 * @brief Stop a periodic measurement.
 * Sends the command of stopping periodic measurement to HS400X.
 * This function supports periodic measurement only.
 * If a periodic measurement is not running, RM_HS400X_EVENT_ERROR is received in callback because HS400x device
 * replies with NACK.
 * Implements @ref rm_hs400x_api_t::measurementStop.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 * @retval FSP_ERR_UNSUPPORTED      Hold and No-Hold measurement are unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_HS400X_MeasurementStop (rm_hs400x_ctrl_t * const p_api_ctrl)
{
#if RM_HS400X_PERIODIC_MEASUREMENT != RM_HS400X_CFG_MEASUREMENT_TYPE
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
#else
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;

 #if RM_HS400X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS400X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Stop a periodic measurement */
    err = rm_hs400x_periodic_measurement_stop(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 * @brief Reads ADC data from HS400X.
 * If Hold measurement is enabled, HS400X holds the SCL line low during the measurement and releases the SCL line
 * when the measurement is complete.
 * If No-Hold measurement is enabled and the measurement result is not ready, RM_HS400X_EVENT_MEASUREMENT_NOT_COMPLETE
 * is received in callback.
 * Implements @ref rm_hs400x_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_HS400X_Read (rm_hs400x_ctrl_t * const p_api_ctrl, rm_hs400x_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
    uint8_t * p_adc_data;
#if RM_HS400X_HOLD_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE
    rm_comms_write_read_params_t write_read_params;
#endif

#if RM_HS400X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_HS400X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if RM_HS400X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE

    /* Set the pointer to adc data */
    p_adc_data = &p_raw_data->humidity[0];
#else

    /* Set the pointer to adc data */
    p_adc_data = &p_raw_data->temperature[0];

    /* Set 0's because humidity data is not measured and CRC uses humidity values */
    p_raw_data->humidity[0] = 0;
    p_raw_data->humidity[1] = 0;
#endif

#if RM_HS400X_HOLD_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE

    /* Start measurement and read ADC data */
    p_ctrl->write_buf[0]         = RM_HS400X_COMMAND_MEASUREMENT;
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_adc_data;
    write_read_params.dest_bytes = RM_HS400X_DATA_SIZE;
    err = rm_hs400x_write_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#elif RM_HS400X_NO_HOLD_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE

    /* Set flag */
    p_ctrl->no_hold_measurement_read = true;

    /* Read data */
    err = rm_hs400x_read(p_ctrl, p_adc_data, RM_HS400X_DATA_SIZE);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else                                  // RM_HS400X_PERIODIC_MEASUREMENT == RM_HS400X_CFG_MEASUREMENT_TYPE

    /* Read data */
    err = rm_hs400x_read(p_ctrl, p_adc_data, RM_HS400X_DATA_SIZE);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculates temperature [Celsius] and humidity [%RH] from ADC data.
 * Implements @ref rm_hs400x_api_t::dataCalculate.
 *
 * @retval FSP_SUCCESS                  Successfully data decoded.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_SENSOR_INVALID_DATA  Data is invalid.
 **********************************************************************************************************************/
fsp_err_t RM_HS400X_DataCalculate (rm_hs400x_ctrl_t * const     p_api_ctrl,
                                   rm_hs400x_raw_data_t * const p_raw_data,
                                   rm_hs400x_data_t * const     p_hs400x_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
    float    tmp_f   = 0.0;
    uint16_t tmp_u16 = 0x0000U;

#if RM_HS400X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_hs400x_data);
    FSP_ERROR_RETURN(RM_HS400X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Execute CRC */
    err = rm_hs400x_crc_execute(p_raw_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if RM_HS400X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE

    /* Relative Humidity [%RH] */
    tmp_u16 =
        (uint16_t) ((uint16_t) (p_raw_data->humidity[0] & RM_HS400X_MASK_DATA_0X3F) << 8);
    tmp_f = (float) (tmp_u16 | (uint16_t) (p_raw_data->humidity[1]));
    tmp_f = (tmp_f * RM_HS400X_CALC_HUMD_VALUE_100) / RM_HS400X_CALC_STATIC_VALUE;
    p_hs400x_data->humidity.integer_part = (int16_t) tmp_f;
    p_hs400x_data->humidity.decimal_part =
        (int16_t) ((tmp_f - (float) p_hs400x_data->humidity.integer_part) * RM_HS400X_CALC_DECIMAL_VALUE_100);
#endif

    /* Temperature [Celsius] */
    tmp_u16 =
        (uint16_t) ((uint16_t) (p_raw_data->temperature[0] & RM_HS400X_MASK_DATA_0X3F) << 8);
    tmp_f = (float) (tmp_u16 | (uint16_t) (p_raw_data->temperature[1]));
    tmp_f = ((tmp_f * RM_HS400X_CALC_TEMP_C_VALUE_165) / RM_HS400X_CALC_STATIC_VALUE) -
            RM_HS400X_CALC_TEMP_C_VALUE_40;
    p_hs400x_data->temperature.integer_part = (int16_t) tmp_f;
    p_hs400x_data->temperature.decimal_part =
        (int16_t) ((tmp_f - (float) p_hs400x_data->temperature.integer_part) * RM_HS400X_CALC_DECIMAL_VALUE_100);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup HS400X)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief HS400X callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_hs400x_comms_i2c_callback (rm_comms_callback_args_t * p_args)
{
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_args->p_context;
    rm_hs400x_callback_args_t   hs400x_callback_args;

    /* Set context */
    hs400x_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            hs400x_callback_args.event = RM_HS400X_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            hs400x_callback_args.event = RM_HS400X_EVENT_ERROR;
            break;
        }
    }

    if (false != p_ctrl->periodic_measurement_stop)
    {
        /* Clear flag */
        p_ctrl->periodic_measurement_stop = false;

        if (RM_HS400X_EVENT_ERROR == hs400x_callback_args.event)
        {
            /* If a periodic measurement is not running, HS400x device replies with NACK */
            hs400x_callback_args.event = RM_HS400X_EVENT_MEASUREMENT_NOT_RUNNING;
        }
    }
    else if (false != p_ctrl->no_hold_measurement_read)
    {
        /* Clear flag */
        p_ctrl->no_hold_measurement_read = false;

        if (RM_HS400X_EVENT_ERROR == hs400x_callback_args.event)
        {
            /* If a measurement is not complete, HS400x device replies with NACK */
            hs400x_callback_args.event = RM_HS400X_EVENT_MEASUREMENT_NOT_COMPLETE;
        }
    }
    else
    {
    }

    if (RM_HS400X_OPEN != p_ctrl->open)
    {
        /* Set flag */
        p_ctrl->init_process_params.communication_finished = true;

        /* Set event */
        p_ctrl->init_process_params.event = hs400x_callback_args.event;
    }
    else
    {
        if (NULL != p_ctrl->p_comms_callback)
        {
            /* Call callback function */
            p_ctrl->p_comms_callback(&hs400x_callback_args);
        }
    }
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Write data to HS400x sensor.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_write (rm_hs400x_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
    uint16_t counter = 0;

    if (RM_HS400X_OPEN != p_ctrl->open)
    {
        /* Clear flag */
        p_ctrl->init_process_params.communication_finished = false;
    }

    /* Write data */
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_HS400X_OPEN != p_ctrl->open)
    {
        /* Wait callback */
        while (false == p_ctrl->init_process_params.communication_finished)
        {
            rm_hs400x_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_HS400X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN((RM_HS400X_EVENT_SUCCESS == p_ctrl->init_process_params.event) ||
                         (RM_HS400X_EVENT_MEASUREMENT_NOT_RUNNING == p_ctrl->init_process_params.event),
                         FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read data from HS400x sensor.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_read (rm_hs400x_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
    uint16_t counter = 0;

    if (RM_HS400X_OPEN != p_ctrl->open)
    {
        /* Clear flag */
        p_ctrl->init_process_params.communication_finished = false;
    }

    /* Read data */
    err = p_ctrl->p_comms_i2c_instance->p_api->read(p_ctrl->p_comms_i2c_instance->p_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_HS400X_OPEN != p_ctrl->open)
    {
        /* Wait callback */
        while (false == p_ctrl->init_process_params.communication_finished)
        {
            rm_hs400x_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_HS400X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN((RM_HS400X_EVENT_SUCCESS == p_ctrl->init_process_params.event) ||
                         (RM_HS400X_EVENT_MEASUREMENT_NOT_COMPLETE == p_ctrl->init_process_params.event),
                         FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Write data to and then read from HS400x.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_write_read (rm_hs400x_ctrl_t * const p_api_ctrl, rm_comms_write_read_params_t const params)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
    uint16_t counter = 0;

    if (RM_HS400X_OPEN != p_ctrl->open)
    {
        /* Clear flag */
        p_ctrl->init_process_params.communication_finished = false;
    }

    /* WriteRead data */
    err = p_ctrl->p_comms_i2c_instance->p_api->writeRead(p_ctrl->p_comms_i2c_instance->p_ctrl, params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (RM_HS400X_OPEN != p_ctrl->open)
    {
        /* Wait callback */
        while (false == p_ctrl->init_process_params.communication_finished)
        {
            rm_hs400x_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_HS400X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Check callback event */
        FSP_ERROR_RETURN(RM_HS400X_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop all measurements.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_all_measurements_stop (rm_hs400x_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
    uint8_t dummy[2];

    /* Stop previous periodic measurement */
    p_ctrl->periodic_measurement_stop = true;
    err = rm_hs400x_periodic_measurement_stop(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear previous no-hold measurement flag */
    p_ctrl->no_hold_measurement_read = true;
    err = rm_hs400x_read(p_ctrl, &dummy[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Stop a periodic measurement.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_periodic_measurement_stop (rm_hs400x_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;

    /* Write the measurement stop command */
    p_ctrl->write_buf[0] = RM_HS400X_COMMAND_STOP_PERIODIC_MEASUREMENT;
    err = rm_hs400x_write(p_ctrl, &p_ctrl->write_buf[0], 1);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set resolutions to HS400x.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_resolution_set (rm_hs400x_ctrl_t * const                 p_api_ctrl,
                                           rm_hs400x_temperature_resolution_t const temperature,
                                           rm_hs400x_humidity_resolution_t const    humidity)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs400x_instance_ctrl_t  * p_ctrl = (rm_hs400x_instance_ctrl_t *) p_api_ctrl;
    rm_comms_write_read_params_t write_read_params;

    /* Read default register data for resolution */
    p_ctrl->write_buf[0]         = RM_HS400X_COMMAND_READ_REGISTER;
    p_ctrl->write_buf[1]         = RM_HS400X_REG_ADDR_RESOLUTION;
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 2;
    write_read_params.p_dest     = &p_ctrl->resolution_register;
    write_read_params.dest_bytes = 1;
    err = rm_hs400x_write_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set resolutions for temperature and humidity */
    p_ctrl->resolution_register &= RM_HS400X_MASK_RESOLUTION;
    p_ctrl->resolution_register |= (uint8_t) ((uint8_t) temperature | (uint8_t) humidity);

    /* Start measurement and read ADC data */
    p_ctrl->write_buf[0] = RM_HS400X_COMMAND_WRITE_REGISTER;
    p_ctrl->write_buf[1] = RM_HS400X_REG_ADDR_RESOLUTION;
    p_ctrl->write_buf[2] = p_ctrl->resolution_register;
    err = rm_hs400x_write(p_ctrl, &p_ctrl->write_buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Execute CRC using ADC data.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_SENSOR_INVALID_DATA  Data is invalid.
 **********************************************************************************************************************/
static fsp_err_t rm_hs400x_crc_execute (rm_hs400x_raw_data_t * const p_raw_data)
{
    uint8_t   crc;
    uint8_t * p_input_data;
    uint8_t   i;
    uint8_t   j;

    /* Set pointer to input data */
    p_input_data = &p_raw_data->humidity[0];

    /* Set initial value */
    crc = RM_HS400X_CALC_CRC_INITIAL_VALUE;

    /* Execute CRC */
    for (i = 0; i < RM_HS400X_CALC_CRC_ADC_DATA_LENGTH; i++)
    {
        /* Calculate XOR with input value */
        crc ^= *p_input_data;

        for (j = 0; j < RM_HS400X_CALC_CRC_8BITS_LENGTH; j++)
        {
            if (RM_HS400X_CACL_CRC_0X80 == (crc & RM_HS400X_CACL_CRC_MASK_MSB))
            {
                // If MSB is 1, calculate XOR with the polynomial.
                crc = (uint8_t) (crc << 1) ^ RM_HS400X_CALC_CRC_POLYNOMIAL;
            }
            else
            {
                crc <<= 1;
            }
        }

        p_input_data++;
    }

    /* Final XOR */
    crc ^= RM_HS400X_CALC_CRC_FINAL_XOR;
    FSP_ERROR_RETURN(p_raw_data->checksum == crc, FSP_ERR_SENSOR_INVALID_DATA);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Internal hs400x private function.
 **********************************************************************************************************************/
