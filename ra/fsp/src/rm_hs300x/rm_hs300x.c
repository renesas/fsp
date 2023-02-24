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
#include "rm_hs300x.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_HS300X_OPEN                               (0x433E4432UL) // Open state

/* Definitions of HS300X data size */
#if RM_HS300X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE
 #define RM_HS300X_DATA_SIZE                         (4)            // Both humidity and temperature
#else
 #define RM_HS300X_DATA_SIZE                         (2)            // Humidity only
#endif

/* Definitions of Mask Data for A/D data */
#define RM_HS300X_MASK_HUMIDITY_UPPER_0X3F           (0x3F)
#define RM_HS300X_MASK_TEMPERATURE_LOWER_0XFC        (0xFC)
#define RM_HS300X_MASK_STATUS_0XC0                   (0xC0)

/* Definitions for Status Bits of A/D Data */
#define RM_HS300X_DATA_STATUS_VALID                  (0x00) // Status-bit: Valid data

/* Definitions for Calculation */
#define RM_HS300X_CALC_STATIC_VALUE                  (16383)
#define RM_HS300X_CALC_HUMD_VALUE_100                (100)
#define RM_HS300X_CALC_TEMP_C_VALUE_165              (165)
#define RM_HS300X_CALC_TEMP_C_VALUE_40               (40)
#define RM_HS300X_CALC_DECIMAL_VALUE_100             (100)

/* Definitions for Programming mode */
#define RM_HS300X_PROGRAMMING_MODE_ENTER             (0xA0)
#define RM_HS300X_PROGRAMMING_MODE_EXIT              (0x80)
#define RM_HS300X_PROGRAMMING_MODE_SUCCESS_STATUS    (0x81)
#define RM_HS300X_HUMIDITY_RESOLUTION_READ           (0x06)
#define RM_HS300X_HUMIDITY_RESOLUTION_WRITE          (0x46)
#define RM_HS300X_TEMPERATURE_RESOLUTION_READ        (0x11)
#define RM_HS300X_TEMPERATURE_RESOLUTION_WRITE       (0x51)
#define RM_HS300X_SENSOR_ID_UPPER                    (0x1E)
#define RM_HS300X_SENSOR_ID_LOWER                    (0x1F)
#define RM_HS300X_RESOLUTION_CLEAR                   (0xF3)

/* Definitions of Timeout */
#define RM_HS300X_TIMEOUT                            (1000)

/* Definitions of Wait Time */
#define RM_HS300X_WAIT_TIME_100                      (100)
#define RM_HS300X_WAIT_TIME_120                      (120)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global function prototypes
 **********************************************************************************************************************/
void rm_hs300x_callback(rm_comms_callback_args_t * p_args);

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
extern fsp_err_t rm_hs300x_delay_us(rm_hs300x_instance_ctrl_t * const p_ctrl, uint32_t const delay_us);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_hs300x_api_t const g_hs300x_on_hs300x =
{
    .open                 = RM_HS300X_Open,
    .close                = RM_HS300X_Close,
    .measurementStart     = RM_HS300X_MeasurementStart,
    .read                 = RM_HS300X_Read,
    .dataCalculate        = RM_HS300X_DataCalculate,
    .programmingModeEnter = RM_HS300X_ProgrammingModeEnter,
    .resolutionChange     = RM_HS300X_ResolutionChange,
    .sensorIdGet          = RM_HS300X_SensorIdGet,
    .programmingModeExit  = RM_HS300X_ProgrammingModeExit,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_HS300X
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the HS300X Middle module. Implements @ref rm_hs300x_api_t::open.
 *
 * Example:
 * @snippet rm_hs300x_example.c RM_HS300X_Open
 *
 * @retval FSP_SUCCESS              HS300X successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_Open (rm_hs300x_ctrl_t * const p_api_ctrl, rm_hs300x_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;

#if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_instance);
    FSP_ERROR_RETURN(RM_HS300X_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg                  = p_cfg;
    p_ctrl->p_comms_i2c_instance   = p_cfg->p_instance;
    p_ctrl->p_context              = p_cfg->p_context;
    p_ctrl->p_callback             = p_cfg->p_callback;
    p_ctrl->programming_mode.enter = false;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set open flag */
    p_ctrl->open = RM_HS300X_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified HS300X control block. Implements @ref rm_hs300x_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_Close (rm_hs300x_ctrl_t * const p_api_ctrl)
{
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;

#if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when start a measurement and when measurement data is stale data.
 * Sends the slave address to the hs300x and start a measurement.
 * Implements @ref rm_hs300x_api_t::measurementStart.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_MeasurementStart (rm_hs300x_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;

#if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Write */
    p_ctrl->buf[0] = 0;
    err            =
        p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 0);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reads ADC data from HS300X.
 * Implements @ref rm_hs300x_api_t::read.
 *
 * @retval FSP_SUCCESS              Successfully data decoded.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_Read (rm_hs300x_ctrl_t * const p_api_ctrl, rm_hs300x_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;

#if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read HS300x ADC data */
    err =
        p_ctrl->p_comms_i2c_instance->p_api->read(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                  (uint8_t *) p_raw_data,
                                                  RM_HS300X_DATA_SIZE);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculates humidity [%RH] and temperature [Celsius] from ADC data.
 * Implements @ref rm_hs300x_api_t::dataCalculate.
 *
 * @retval FSP_SUCCESS                  Successfully data decoded.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_SENSOR_INVALID_DATA  Data is invalid.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_DataCalculate (rm_hs300x_ctrl_t * const     p_api_ctrl,
                                   rm_hs300x_raw_data_t * const p_raw_data,
                                   rm_hs300x_data_t * const     p_hs300x_data)
{
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;
    uint8_t  status;
    int32_t  tmp_32  = 0;
    uint16_t tmp_u16 = 0x0000U;

#if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_hs300x_data);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Check data status */
    status = p_raw_data->humidity[0] & RM_HS300X_MASK_STATUS_0XC0;
    FSP_ERROR_RETURN(RM_HS300X_DATA_STATUS_VALID == status, FSP_ERR_SENSOR_INVALID_DATA);

    /* Relative Humidity [%RH] */
    tmp_u16 =
        (uint16_t) ((uint16_t) (p_raw_data->humidity[0] & RM_HS300X_MASK_HUMIDITY_UPPER_0X3F) << 8);
    tmp_u16 = (uint16_t) (tmp_u16 | (uint16_t) (p_raw_data->humidity[1]));
    tmp_32  = (int32_t) (((int32_t) tmp_u16 * RM_HS300X_CALC_HUMD_VALUE_100 * RM_HS300X_CALC_DECIMAL_VALUE_100) /
                         RM_HS300X_CALC_STATIC_VALUE);
    p_hs300x_data->humidity.integer_part = (int16_t) (tmp_32 / RM_HS300X_CALC_DECIMAL_VALUE_100);
    p_hs300x_data->humidity.decimal_part = (int16_t) (tmp_32 % RM_HS300X_CALC_DECIMAL_VALUE_100);

#if RM_HS300X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE

    /* Temperature [Celsius] */
    tmp_u16 = (uint16_t) ((uint16_t) (p_raw_data->temperature[0]) << 8);
    tmp_u16 =
        (uint16_t) ((tmp_u16 | (uint16_t) (p_raw_data->temperature[1] & RM_HS300X_MASK_TEMPERATURE_LOWER_0XFC)) >> 2);
    tmp_32 =
        (int32_t) ((((int32_t) tmp_u16 * RM_HS300X_CALC_TEMP_C_VALUE_165 * RM_HS300X_CALC_DECIMAL_VALUE_100) /
                    RM_HS300X_CALC_STATIC_VALUE) -
                   (RM_HS300X_CALC_TEMP_C_VALUE_40 * RM_HS300X_CALC_DECIMAL_VALUE_100));
    p_hs300x_data->temperature.integer_part = (int16_t) (tmp_32 / RM_HS300X_CALC_DECIMAL_VALUE_100);
    p_hs300x_data->temperature.decimal_part = (int16_t) (tmp_32 % RM_HS300X_CALC_DECIMAL_VALUE_100);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function must be called within 10ms after applying power to the sensor.
 * Sends the commands to enter the programming mode.
 * After calling this function, please wait 120us.
 * Implements @ref rm_hs300x_api_t::programmingModeEnter.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_UNSUPPORTED      Programming mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_ProgrammingModeEnter (rm_hs300x_ctrl_t * const p_api_ctrl)
{
    /* The procedure in this function is based on section 6.8 "Accessing the Non-volatile Memory" of the HS300x Datasheet R36DS0010EU0701. */

#if RM_HS300X_CFG_PROGRAMMING_MODE
    fsp_err_t err = FSP_SUCCESS;
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;

 #if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Set the flag */
    p_ctrl->programming_mode.enter = true;

    /* Write the commands */
    p_ctrl->buf[0] = RM_HS300X_PROGRAMMING_MODE_ENTER;
    p_ctrl->buf[1] = 0x00;
    p_ctrl->buf[2] = 0x00;
    err            =
        p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief This function must be called after calling the RM_HS300X_ProgrammingModeEnter function.
 * Changes the sensor resolution.
 * This function blocks for 120 us software delay plus 9 bytes on the I2C bus.
 * After calling this function, 14ms must be waited.
 * Failure to comply with these times may result in data corruption and introduce errors in sensor measurements.
 * Implements @ref rm_hs300x_api_t::resolutionChange.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_MODE     Module is not entering the programming mode.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_UNSUPPORTED      Programming mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_ResolutionChange (rm_hs300x_ctrl_t * const     p_api_ctrl,
                                      rm_hs300x_data_type_t const  data_type,
                                      rm_hs300x_resolution_t const resolution)
{
    /* The procedure in this function is based on section 6.9 "Setting the Measurement Resolution" of the HS300x Datasheet R36DS0010EU0701. */

#if RM_HS300X_CFG_PROGRAMMING_MODE
    fsp_err_t err = FSP_SUCCESS;
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;
    uint16_t counter = 0;

 #if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(true == p_ctrl->programming_mode.enter, FSP_ERR_INVALID_MODE);
 #endif

    /* Set the register address */
    if (RM_HS300X_HUMIDITY_DATA == data_type)
    {
        p_ctrl->buf[0] = RM_HS300X_HUMIDITY_RESOLUTION_READ;
    }
    else
    {
        p_ctrl->buf[0] = RM_HS300X_TEMPERATURE_RESOLUTION_READ;
    }

    p_ctrl->buf[1] = 0x00;
    p_ctrl->buf[2] = 0x00;

    /* Set the blocking flag */
    p_ctrl->programming_mode.blocking = true;

    /* Write the register address */
    p_ctrl->programming_mode.communication_finished = false;
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait the callback */
    while (false == p_ctrl->programming_mode.communication_finished)
    {
        rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_100);
        counter++;
        FSP_ERROR_RETURN(RM_HS300X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
    }

    /* Check the error */
    FSP_ERROR_RETURN(RM_HS300X_EVENT_SUCCESS == p_ctrl->programming_mode.event, FSP_ERR_ABORTED);

    /* Delay 120us */
    err = rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_120);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Read the current resolution */
    p_ctrl->programming_mode.communication_finished = false;
    err = p_ctrl->p_comms_i2c_instance->p_api->read(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait the callback */
    while (false == p_ctrl->programming_mode.communication_finished)
    {
        rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_100);
        counter++;
        FSP_ERROR_RETURN(RM_HS300X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
    }

    /* Check the errors */
    FSP_ERROR_RETURN(RM_HS300X_EVENT_SUCCESS == p_ctrl->programming_mode.event, FSP_ERR_ABORTED);
    FSP_ERROR_RETURN(RM_HS300X_PROGRAMMING_MODE_SUCCESS_STATUS == p_ctrl->buf[0], FSP_ERR_INVALID_MODE);

    /* Set the register address */
    if (RM_HS300X_HUMIDITY_DATA == data_type)
    {
        p_ctrl->buf[0] = RM_HS300X_HUMIDITY_RESOLUTION_WRITE;
    }
    else
    {
        p_ctrl->buf[0] = RM_HS300X_TEMPERATURE_RESOLUTION_WRITE;
    }

    /* set the next resolution */
    p_ctrl->buf[1] &= RM_HS300X_RESOLUTION_CLEAR; // Clear the current resolution
    p_ctrl->buf[1] |= resolution;                 // Set the new resolution

    /* Clear the blocking flag */
    p_ctrl->programming_mode.blocking = false;

    /* Write the next resolution */
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(data_type);
    FSP_PARAMETER_NOT_USED(resolution);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief This function must be called after calling the RM_HS300X_ProgrammingModeEnter function.
 * Gets the sensor ID.
 * This function blocks for 240 us software delay plus 12 bytes on the I2C bus.
 * Implements @ref rm_hs300x_api_t::sensorIdGet.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_MODE     Module is not entering the programming mode.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_UNSUPPORTED      Programming mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_SensorIdGet (rm_hs300x_ctrl_t * const p_api_ctrl, uint32_t * const p_sensor_id)
{
    /* The procedure in this function is based on section 6.10 "Reading the HS300x ID Number" of the HS300x Datasheet R36DS0010EU0701. */

#if RM_HS300X_CFG_PROGRAMMING_MODE
    fsp_err_t err = FSP_SUCCESS;
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;
    uint16_t counter = 0;

 #if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_sensor_id);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(true == p_ctrl->programming_mode.enter, FSP_ERR_INVALID_MODE);
 #endif

    /* Set the register address of upper value */
    p_ctrl->buf[0] = RM_HS300X_SENSOR_ID_UPPER;
    p_ctrl->buf[1] = 0x00;
    p_ctrl->buf[2] = 0x00;

    /* Set the blocking flag */
    p_ctrl->programming_mode.blocking = true;

    /* Write the register address */
    p_ctrl->programming_mode.communication_finished = false;
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait the callback */
    while (false == p_ctrl->programming_mode.communication_finished)
    {
        rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_100);
        counter++;
        FSP_ERROR_RETURN(RM_HS300X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
    }

    /* Check the error */
    FSP_ERROR_RETURN(RM_HS300X_EVENT_SUCCESS == p_ctrl->programming_mode.event, FSP_ERR_ABORTED);

    /* Delay 120us */
    err = rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_120);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Read the upper value of the sensor ID */
    p_ctrl->programming_mode.communication_finished = false;
    err = p_ctrl->p_comms_i2c_instance->p_api->read(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait the callback */
    while (false == p_ctrl->programming_mode.communication_finished)
    {
        rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_100);
        counter++;
        FSP_ERROR_RETURN(RM_HS300X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
    }

    /* Check the errors */
    FSP_ERROR_RETURN(RM_HS300X_EVENT_SUCCESS == p_ctrl->programming_mode.event, FSP_ERR_ABORTED);
    FSP_ERROR_RETURN(RM_HS300X_PROGRAMMING_MODE_SUCCESS_STATUS == p_ctrl->buf[0], FSP_ERR_INVALID_MODE);

    /* set the upper value of sensor ID */
    *p_sensor_id = (uint32_t) ((p_ctrl->buf[1] << 8) + p_ctrl->buf[2]) << 16;

    /* Set the register address of lower value */
    p_ctrl->buf[0] = RM_HS300X_SENSOR_ID_LOWER;
    p_ctrl->buf[1] = 0x00;
    p_ctrl->buf[2] = 0x00;

    /* Write the register address */
    p_ctrl->programming_mode.communication_finished = false;
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait the callback */
    while (false == p_ctrl->programming_mode.communication_finished)
    {
        rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_100);
        counter++;
        FSP_ERROR_RETURN(RM_HS300X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
    }

    /* Check the error */
    FSP_ERROR_RETURN(RM_HS300X_EVENT_SUCCESS == p_ctrl->programming_mode.event, FSP_ERR_ABORTED);

    /* Delay 120us */
    err = rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_120);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Read the lower value of the sensor ID */
    p_ctrl->programming_mode.communication_finished = false;
    err = p_ctrl->p_comms_i2c_instance->p_api->read(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait the callback */
    while (false == p_ctrl->programming_mode.communication_finished)
    {
        rm_hs300x_delay_us(p_ctrl, RM_HS300X_WAIT_TIME_100);
        counter++;
        FSP_ERROR_RETURN(RM_HS300X_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
    }

    /* Check the errors */
    FSP_ERROR_RETURN(RM_HS300X_EVENT_SUCCESS == p_ctrl->programming_mode.event, FSP_ERR_ABORTED);
    FSP_ERROR_RETURN(RM_HS300X_PROGRAMMING_MODE_SUCCESS_STATUS == p_ctrl->buf[0], FSP_ERR_INVALID_MODE);

    /* set the upper value of sensor ID */
    *p_sensor_id = *p_sensor_id + (uint32_t) ((p_ctrl->buf[1] << 8) + p_ctrl->buf[2]);

    /* Clear the blocking flag */
    p_ctrl->programming_mode.blocking = false;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_sensor_id);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @brief This function must be called after calling the RM_HS300X_ProgrammingModeEnter function.
 * This function must be called to return to normal sensor operation and perform measurements.
 * Sends the commands to exit the programming mode.
 * Implements @ref rm_hs300x_api_t::programmingModeExit.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_MODE     Module is not entering the programming mode.
 * @retval FSP_ERR_UNSUPPORTED      Programming mode is not supported.
 **********************************************************************************************************************/
fsp_err_t RM_HS300X_ProgrammingModeExit (rm_hs300x_ctrl_t * const p_api_ctrl)
{
    /* The procedure in this function is based on section 6.8 "Accessing the Non-volatile Memory" of the HS300x Datasheet R36DS0010EU0701. */

#if RM_HS300X_CFG_PROGRAMMING_MODE
    fsp_err_t err = FSP_SUCCESS;
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_api_ctrl;

 #if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(true == p_ctrl->programming_mode.enter, FSP_ERR_INVALID_MODE);
 #endif

    /* Write the commands */
    p_ctrl->buf[0] = RM_HS300X_PROGRAMMING_MODE_EXIT;
    p_ctrl->buf[1] = 0x00;
    p_ctrl->buf[2] = 0x00;
    err            =
        p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Clear the flag */
    p_ctrl->programming_mode.enter = false;

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @} (end addtogroup HS300X)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief HS300X callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_hs300x_callback (rm_comms_callback_args_t * p_args)
{
    rm_hs300x_instance_ctrl_t * p_ctrl = (rm_hs300x_instance_ctrl_t *) p_args->p_context;
    rm_hs300x_callback_args_t   hs300x_callback_args;

    /* Set context */
    hs300x_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            hs300x_callback_args.event = RM_HS300X_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            hs300x_callback_args.event = RM_HS300X_EVENT_ERROR;
            break;
        }
    }

    if (true == p_ctrl->programming_mode.blocking)
    {
        /* Set flag */
        p_ctrl->programming_mode.communication_finished = true;

        /* Set event */
        p_ctrl->programming_mode.event = hs300x_callback_args.event;
    }
    else
    {
        if (NULL != p_ctrl->p_callback)
        {
            /* Call callback function */
            p_ctrl->p_callback(&hs300x_callback_args);
        }
    }
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal hs300x private function.
 **********************************************************************************************************************/
