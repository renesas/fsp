/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "rm_rrh62000.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_RRH62000_OPEN                          (('R' << 24U) | ('H' << 16U) | ('6' << 8U) | ('2' << 0U)) // Open state, R"RH62"000

/* Definitions of Timeout */
#define RM_RRH62000_TIMEOUT                       (100)

/* Definitions of Wait Time */
#define RM_RRH62000_WAIT_TIME_1000                (1000)

/* Definitions of Retry max counts */
#define RM_RRH62000_RETRY_MAX_COUNTS              (5)
#define RM_RRH62000_RETRY_ZMOD_CLEANING_COUNTS    (60 + 10) // ZMOD cleaning time (60s) + buffer (10s)

/* Definitions of Command */
#define RM_RRH62000_COMMAND_READ                  (0x00)
#define RM_RRH62000_COMMAND_DATA                  (0x40)
#define RM_RRH62000_COMMAND_RESET                 (0x52)
#define RM_RRH62000_COMMAND_MAVE                  (0x53)
#define RM_RRH62000_COMMAND_SPEEDFAN              (0x63)
#define RM_RRH62000_COMMAND_ARGVER                (0x73)
#define RM_RRH62000_COMMAND_CSTATUS               (0x74)
#define RM_RRH62000_COMMAND_FWVAR                 (0x75)

/* Definitions of Reset */
#define RM_RRH62000_RESET_VALUE                   (0x81)

/* Definitions of Cleaning Status */
#define RM_RRH62000_ZMOD_CLEAN_NOT_COMPLETE       (0x00)
#define RM_RRH62000_ZMOD_CLEAN_COMPLETE           (0x01)

/* Definitions of data size */
#define RM_RRH62000_LEN_MEASUREMENT_DATA          (37)

/* Definitions of Mask */
#define RM_RRH62000_STATUS_MASK                   (0x01)
#define RM_RRH62000_HIGH_CONCENTRATION_MASK       (0x01)
#define RM_RRH62000_DUST_ACCUMULATION_MASK        (0x02)
#define RM_RRH62000_FAN_SPEED_MASK                (0x04)
#define RM_RRH62000_FAN_MASK                      (0x08)

/* Definitions of Position */
#define RM_RRH62000_POSITION_STATUS               (0)
#define RM_RRH62000_POSITION_NC_0P3               (2)
#define RM_RRH62000_POSITION_TEMPERATURE          (24)
#define RM_RRH62000_POSITION_ECO2                 (30)
#define RM_RRH62000_POSITION_IAQ                  (32)

/* Definitions of Calculation */
#define RM_RRH62000_CALC_CRC_INITIAL_VALUE        (0xFF)
#define RM_RRH62000_CALC_CRC_DATA_LENGTH          (36)
#define RM_RRH62000_CALC_DATA_STEP                (2)
#define RM_RRH62000_CALC_CRC_8BITS_LENGTH         (8)
#define RM_RRH62000_CALC_CRC_0X80                 (0x80)
#define RM_RRH62000_CALC_CRC_MASK_MSB             (0x80)
#define RM_RRH62000_CALC_CRC_POLYNOMIAL           (0x31)
#define RM_RRH62000_CALC_CRC_FINAL_XOR            (0x00)
#define RM_RRH62000_CALC_DECIMAL_VALUE_100        (100)
#define RM_RRH62000_CALC_DECIMAL_VALUE_10         (10)
#define RM_RRH62000_CALC_MASK_MINUS_VALUE         (0x8000)
#define RM_RRH62000_CALC_MINUS_VALUE              (0x8000)

/* Definitions of Shift */
#define RM_RRH62000_SHIFT_24                      (24)
#define RM_RRH62000_SHIFT_16                      (16)
#define RM_RRH62000_SHIFT_8                       (8)

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_air_sensor_api_t const g_air_sensor_on_rrh62000 =
{
    .open                = RM_RRH62000_Open,
    .close               = RM_RRH62000_Close,
    .read                = RM_RRH62000_Read,
    .dataCalculate       = RM_RRH62000_DataCalculate,
    .statusCheck         = RM_RRH62000_StatusCheck,
    .firmwareVersionGet  = RM_RRH62000_FirmwareVersionGet,
    .algorithmVersionGet = RM_RRH62000_AlgorithmVersionGet,
};

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
extern fsp_err_t rm_rrh62000_delay_ms(rm_air_sensor_ctrl_t * const p_ctrl, uint32_t const delay_ms);
void             rm_rrh62000_comms_i2c_callback(rm_comms_callback_args_t * p_args);

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

static fsp_err_t rm_rrh62000_i2c_read(rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                      rm_comms_write_read_params_t const  params);
static fsp_err_t rm_rrh62000_i2c_write(rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                       uint8_t * const                     p_src,
                                       uint32_t const                      bytes);
static fsp_err_t rm_rrh62000_zmod_cleaning_check(rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                 uint8_t * const                     p_cleaning_status);
static fsp_err_t rm_rrh62000_reset(rm_rrh62000_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_rrh62000_read_measurement_results(rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                      uint8_t * const                     p_raw_data);
static fsp_err_t rm_rrh62000_read_status(rm_rrh62000_instance_ctrl_t * const p_ctrl, uint8_t * const p_status);
static fsp_err_t rm_rrh62000_set_moving_average(rm_rrh62000_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_rrh62000_set_fan_speed_control(rm_rrh62000_instance_ctrl_t * const p_ctrl);
static fsp_err_t rm_rrh62000_read_firmware_version(rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                   uint8_t * const                     p_version);
static fsp_err_t rm_rrh62000_read_algorithm_version(rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                    uint8_t * const                     p_version);
static fsp_err_t rm_rrh62000_crc_execute(const uint8_t * const p_raw_data);
static void      rm_rrh62000_process_in_callback(rm_air_sensor_ctrl_t * const          p_api_ctrl,
                                                 rm_air_sensor_callback_args_t * const p_args);

/*******************************************************************************************************************//**
 * @addtogroup RM_RRH62000
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the RRH62000 sensor module.
 * If ZMOD cleaning is not complete, this function will take at least 1 minute.
 * Implements @ref rm_air_sensor_api_t::open.
 *
 * @retval FSP_SUCCESS              RRH62000 successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_NOT_INITIALIZED  ZMOD cleaning is not complete.
 **********************************************************************************************************************/
fsp_err_t RM_RRH62000_Open (rm_air_sensor_ctrl_t * const p_api_ctrl, rm_air_sensor_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;
    uint32_t counts;

#if RM_RRH62000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms_instance);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_RRH62000_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Set instances */
    p_ctrl->p_cfg                = p_cfg;
    p_ctrl->p_comms_i2c_instance = p_cfg->p_comms_instance;

    /* Set parameters */
    p_ctrl->p_context        = p_cfg->p_context;
    p_ctrl->p_comms_callback = p_cfg->p_comms_callback;
    p_ctrl->status.flag      = false;
    p_ctrl->event            = RM_AIR_SENSOR_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check if ZMOD cleaning is complete.
     * If not complete, it will take 1 minute. Please do not cut power to the sensor module during this period.
     */
    p_ctrl->cleaning_status.value = RM_RRH62000_ZMOD_CLEAN_NOT_COMPLETE;
    counts = RM_RRH62000_RETRY_ZMOD_CLEANING_COUNTS;
    do
    {
        err = rm_rrh62000_zmod_cleaning_check(p_ctrl, &p_ctrl->cleaning_status.value);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        if (RM_RRH62000_ZMOD_CLEAN_NOT_COMPLETE == p_ctrl->cleaning_status.value)
        {
            /* Delay 1s */
            rm_rrh62000_delay_ms(p_ctrl, RM_RRH62000_WAIT_TIME_1000);
            counts--;
        }
    } while ((RM_RRH62000_ZMOD_CLEAN_NOT_COMPLETE == p_ctrl->cleaning_status.value) && (0 < counts));

    FSP_ERROR_RETURN(RM_RRH62000_ZMOD_CLEAN_NOT_COMPLETE != p_ctrl->cleaning_status.value, FSP_ERR_NOT_INITIALIZED);

    /* Reset */
    err = rm_rrh62000_reset(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Delay 1s after sending a reset command */
    rm_rrh62000_delay_ms(p_ctrl, RM_RRH62000_WAIT_TIME_1000);

    /* Set the number of moving average */
    err = rm_rrh62000_set_moving_average(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set the fan speed control */
    err = rm_rrh62000_set_fan_speed_control(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check if everything is okay */
    p_ctrl->open = RM_RRH62000_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when close the sensor module. Implements @ref rm_air_sensor_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_RRH62000_Close (rm_air_sensor_ctrl_t * const p_api_ctrl)
{
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH62000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_RRH62000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when polling is used. It reads the status of sensor.
 * Implements @ref rm_air_sensor_api_t::statusCheck.
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH62000_StatusCheck (rm_air_sensor_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH62000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_RRH62000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear event */
    p_ctrl->event = RM_AIR_SENSOR_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Set flag */
    p_ctrl->status.flag = true;

    /* Read status from RRH62000 */
    err = rm_rrh62000_read_status(p_ctrl, &p_ctrl->status.value);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called to get measurement results after measurement finishes.
 * To check measurement status either polling or busy/interrupt pin can be used.
 * Implements @ref rm_air_sensor_api_t::read
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH62000_Read (rm_air_sensor_ctrl_t * const p_api_ctrl, rm_air_sensor_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH62000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_RRH62000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check if measurement is complete. */
    FSP_ERROR_RETURN(RM_AIR_SENSOR_EVENT_MEASUREMENT_COMPLETE == p_ctrl->event,
                     FSP_ERR_SENSOR_MEASUREMENT_NOT_FINISHED);

    /* Clear event */
    p_ctrl->event = RM_AIR_SENSOR_EVENT_MEASUREMENT_NOT_COMPLETE;

    /* Read measurement results */
    err = rm_rrh62000_read_measurement_results(p_ctrl, (uint8_t *) p_raw_data);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called when calculating gas data from measurement results.
 * Implements @ref rm_air_sensor_api_t::dataCalculate
 *
 * @retval FSP_SUCCESS                             Successfully gas data is calculated.
 * @retval FSP_ERR_ASSERTION                       Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                        Module is not opened configured.
 **********************************************************************************************************************/
fsp_err_t RM_RRH62000_DataCalculate (rm_air_sensor_ctrl_t * const           p_api_ctrl,
                                     const rm_air_sensor_raw_data_t * const p_raw_data,
                                     rm_air_sensor_data_t * const           p_rrh62000_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;
    uint16_t tmp_u16;
    int16_t  tmp_16;
    rm_air_sensor_single_data_t * p_sensor_data;
    uint32_t position;

#if RM_RRH62000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_rrh62000_data);
    FSP_ERROR_RETURN(RM_RRH62000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Execute CRC */
    err = rm_rrh62000_crc_execute(&p_raw_data->results[0]);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set status data */
    p_rrh62000_data->status =
        (uint32_t) (((uint32_t) p_raw_data->results[1] << RM_RRH62000_SHIFT_8) | (uint32_t) p_raw_data->results[0]);

    /* Set measurement results */
    p_sensor_data = &p_rrh62000_data->nc_0p3;
    for (position = RM_RRH62000_POSITION_NC_0P3;
         position < (RM_RRH62000_LEN_MEASUREMENT_DATA - 1);
         position += RM_RRH62000_CALC_DATA_STEP)
    {
        /* Calculate sensor data from measurement results (big-endian). */
        tmp_u16 = (uint16_t) (((uint16_t) p_raw_data->results[position] << RM_RRH62000_SHIFT_8) |
                              (uint16_t) p_raw_data->results[position + 1]);
        p_sensor_data->sign = RM_AIR_SENSOR_SIGN_PLUS;
        if (RM_RRH62000_POSITION_TEMPERATURE > position)
        {
            /* NC_x and PMx_x data. One decimal place. */
            p_sensor_data->integer_part = (uint32_t) (tmp_u16 / RM_RRH62000_CALC_DECIMAL_VALUE_10);
            p_sensor_data->decimal_part = (uint32_t) (tmp_u16 % RM_RRH62000_CALC_DECIMAL_VALUE_10);
        }
        else if (RM_RRH62000_POSITION_TEMPERATURE == position)
        {
            /* Temperature. This data is signed integer type. Two decimal places. */
            if (RM_RRH62000_CALC_MINUS_VALUE == (tmp_u16 & RM_RRH62000_CALC_MASK_MINUS_VALUE))
            {
                p_sensor_data->sign = RM_AIR_SENSOR_SIGN_MINUS;
                tmp_16              = (*((int16_t *) &tmp_u16)) * RM_AIR_SENSOR_SIGN_MINUS;
            }
            else
            {
                tmp_16 = (int16_t) tmp_u16;
            }

            p_sensor_data->integer_part = (uint32_t) (tmp_16 / RM_RRH62000_CALC_DECIMAL_VALUE_100);
            p_sensor_data->decimal_part = (uint32_t) (tmp_16 % RM_RRH62000_CALC_DECIMAL_VALUE_100);
        }
        else if ((RM_RRH62000_POSITION_ECO2 > position) || (RM_RRH62000_POSITION_IAQ == position))
        {
            /* Humidity, TVOC and IAQ data. Two decimal places. */
            p_sensor_data->integer_part = (uint32_t) (tmp_u16 / RM_RRH62000_CALC_DECIMAL_VALUE_100);
            p_sensor_data->decimal_part = (uint32_t) (tmp_u16 % RM_RRH62000_CALC_DECIMAL_VALUE_100);
        }
        else
        {
            /* eCO2 and Relative IAQ data. These data does not have a decimal part. */
            p_sensor_data->integer_part = (uint32_t) tmp_u16;
            p_sensor_data->decimal_part = 0;
        }

        p_sensor_data++;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called to get firmware version. Firmware version does not use "patch" of p_version.
 * Implements @ref rm_air_sensor_api_t::firmwareVersionGet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH62000_FirmwareVersionGet (rm_air_sensor_ctrl_t * const    p_api_ctrl,
                                          rm_air_sensor_version_t * const p_version)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH62000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_version);
    FSP_ERROR_RETURN(RM_RRH62000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read firmware version */
    err = rm_rrh62000_read_firmware_version(p_ctrl, (uint8_t *) p_version);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called to get algorithm version.
 * Implements @ref rm_air_sensor_api_t::algorithmVersionGet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH62000_AlgorithmVersionGet (rm_air_sensor_ctrl_t * const    p_api_ctrl,
                                           rm_air_sensor_version_t * const p_version)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH62000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_version);
    FSP_ERROR_RETURN(RM_RRH62000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read algorithm version */
    err = rm_rrh62000_read_algorithm_version(p_ctrl, (uint8_t *) p_version);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_RRH62000)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief RM_RRH62000 callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_rrh62000_comms_i2c_callback (rm_comms_callback_args_t * p_args)
{
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_args->p_context;
    rm_air_sensor_callback_args_t rrh62000_callback_args;

    /* Set context */
    rrh62000_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_ERROR;
            break;
        }
    }

    if (RM_RRH62000_OPEN != p_ctrl->open)
    {
        /* Set flag */
        p_ctrl->init_process_params.communication_finished = true;

        /* Set event */
        p_ctrl->init_process_params.event = rrh62000_callback_args.event;
    }
    else
    {
        if (RM_AIR_SENSOR_EVENT_SUCCESS == rrh62000_callback_args.event)
        {
            if (true == p_ctrl->status.flag)
            {
                if (p_ctrl->status.value & RM_RRH62000_STATUS_MASK)
                {
                    /* Set event */
                    rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_MEASUREMENT_COMPLETE;
                    p_ctrl->event                = RM_AIR_SENSOR_EVENT_MEASUREMENT_COMPLETE;
                }
                else
                {
                    /* Set event */
                    rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_MEASUREMENT_NOT_COMPLETE;
                }

                /* Clear flag */
                p_ctrl->status.flag = false;

                /* Call user callback function */
                rm_rrh62000_process_in_callback(p_ctrl, &rrh62000_callback_args);
            }
            else if ((NULL != p_ctrl->p_read_data) && (RM_RRH62000_LEN_MEASUREMENT_DATA == p_ctrl->read_bytes))
            {
                if (p_ctrl->p_read_data[RM_RRH62000_POSITION_STATUS] & RM_RRH62000_HIGH_CONCENTRATION_MASK)
                {
                    /* Set event */
                    rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_NOT_MEASURABLE; // Dust concentration is extremely high (not measurable).
                }
                else if (p_ctrl->p_read_data[RM_RRH62000_POSITION_STATUS] & RM_RRH62000_DUST_ACCUMULATION_MASK)
                {
                    /* Set event */
                    rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_NOT_MEASURABLE; // Dust accumulated inside the sensor (not measurable).
                }
                else if (p_ctrl->p_read_data[RM_RRH62000_POSITION_STATUS] & RM_RRH62000_FAN_SPEED_MASK)
                {
                    /* Set event */
                    rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_FAN_SPEED_OUT_OF_RANGE; // Fan speed is out of the set range.
                }
                else if (p_ctrl->p_read_data[RM_RRH62000_POSITION_STATUS] & RM_RRH62000_FAN_MASK)
                {
                    /* Set event */
                    rrh62000_callback_args.event = RM_AIR_SENSOR_EVENT_FAN_BROKEN; // Fan malfunctioned or broken down.
                }
                else
                {
                }

                /* Call user callback function */
                rm_rrh62000_process_in_callback(p_ctrl, &rrh62000_callback_args);
            }
            else
            {
                /* Call user callback function */
                rm_rrh62000_process_in_callback(p_ctrl, &rrh62000_callback_args);
            }
        }
        else
        {
            /* Call user callback function */
            rm_rrh62000_process_in_callback(p_ctrl, &rrh62000_callback_args);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief Process in callback function. Call user callback.
 **********************************************************************************************************************/
static void rm_rrh62000_process_in_callback (rm_air_sensor_ctrl_t * const          p_api_ctrl,
                                             rm_air_sensor_callback_args_t * const p_args)
{
    rm_rrh62000_instance_ctrl_t * p_ctrl = (rm_rrh62000_instance_ctrl_t *) p_api_ctrl;

    if (NULL != p_ctrl->p_comms_callback)
    {
        /* Call callback function */
        p_ctrl->p_comms_callback(p_args);
    }
}

/*******************************************************************************************************************//**
 * @brief I2C wrapper function to read from rrh62000 sensor.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_i2c_read (rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                       rm_comms_write_read_params_t const  params)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint16_t  counter      = 0;
    uint16_t  retry_counts = RM_RRH62000_RETRY_MAX_COUNTS;

    do
    {
        if (RM_RRH62000_OPEN != p_ctrl->open)
        {
            /* Clear flag */
            p_ctrl->init_process_params.communication_finished = false;
        }

        /* WriteRead data */
        err = p_ctrl->p_comms_i2c_instance->p_api->writeRead(p_ctrl->p_comms_i2c_instance->p_ctrl, params);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (RM_RRH62000_OPEN != p_ctrl->open)
        {
            /* Wait callback */
            while (false == p_ctrl->init_process_params.communication_finished)
            {
                rm_rrh62000_delay_ms(p_ctrl, 1);
                counter++;
                FSP_ERROR_RETURN(RM_RRH62000_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
            }

            /* Retry counts decrement */
            retry_counts--;
        }
    } while ((RM_RRH62000_OPEN != p_ctrl->open) && (RM_AIR_SENSOR_EVENT_SUCCESS != p_ctrl->init_process_params.event) &&
             (0 < retry_counts));

    /* Check callback event */
    FSP_ERROR_RETURN(RM_AIR_SENSOR_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief I2C wrapper function to write from rrh62000 sensor.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_i2c_write (rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                        uint8_t * const                     p_src,
                                        uint32_t const                      bytes)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint16_t  counter      = 0;
    uint16_t  retry_counts = RM_RRH62000_RETRY_MAX_COUNTS;

    do
    {
        if (RM_RRH62000_OPEN != p_ctrl->open)
        {
            /* Clear flag */
            p_ctrl->init_process_params.communication_finished = false;
        }

        /* Write data */
        err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, p_src, bytes);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (RM_RRH62000_OPEN != p_ctrl->open)
        {
            /* Wait callback */
            while (false == p_ctrl->init_process_params.communication_finished)
            {
                rm_rrh62000_delay_ms(p_ctrl, 1);
                counter++;
                FSP_ERROR_RETURN(RM_RRH62000_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
            }

            /* Decrease retry counts */
            retry_counts--;
        }
    } while ((RM_RRH62000_OPEN != p_ctrl->open) && (RM_AIR_SENSOR_EVENT_SUCCESS != p_ctrl->init_process_params.event) &&
             (0 < retry_counts));

    /* Check callback event */
    FSP_ERROR_RETURN(RM_AIR_SENSOR_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Check if ZMOD cleaning is complete.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_zmod_cleaning_check (rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                  uint8_t * const                     p_cleaning_status)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_CSTATUS;

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = p_cleaning_status;
    p_ctrl->read_bytes  = 1;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh62000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Reset the sensor module.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_reset (rm_rrh62000_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_RESET;
    p_ctrl->write_buf[1] = RM_RRH62000_RESET_VALUE;

    /* Send the command and a value */
    err = rm_rrh62000_i2c_write(p_ctrl, &p_ctrl->write_buf[0], 2);
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
static fsp_err_t rm_rrh62000_read_measurement_results (rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                       uint8_t * const                     p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_READ;

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = p_raw_data;
    p_ctrl->read_bytes  = RM_RRH62000_LEN_MEASUREMENT_DATA;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh62000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read status.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_read_status (rm_rrh62000_instance_ctrl_t * const p_ctrl, uint8_t * const p_status)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_DATA;

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = p_status;
    p_ctrl->read_bytes  = 1;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh62000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set the number of moving average.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_set_moving_average (rm_rrh62000_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_extended_cfg_t * p_extend = (rm_rrh62000_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_MAVE;
    p_ctrl->write_buf[1] = p_extend->moving_average;

    /* Send the command and a value */
    err = rm_rrh62000_i2c_write(p_ctrl, &p_ctrl->write_buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set the fan speed control.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_set_fan_speed_control (rm_rrh62000_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh62000_extended_cfg_t * p_extend = (rm_rrh62000_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_SPEEDFAN;
    p_ctrl->write_buf[1] = p_extend->fan_speed;

    /* Send the command and a value */
    err = rm_rrh62000_i2c_write(p_ctrl, &p_ctrl->write_buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read firmware version from the sensor.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_read_firmware_version (rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                    uint8_t * const                     p_version)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_FWVAR;

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = p_version;
    p_ctrl->read_bytes  = 2;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh62000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read algorithm version from the sensor.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_read_algorithm_version (rm_rrh62000_instance_ctrl_t * const p_ctrl,
                                                     uint8_t * const                     p_version)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH62000_COMMAND_ARGVER;

    /* Set pointer and read bytes */
    p_ctrl->p_read_data = p_version;
    p_ctrl->read_bytes  = 3;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh62000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculate checksum.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh62000_crc_execute (const uint8_t * const p_raw_data)
{
    uint8_t         crc;
    const uint8_t * p_input_data;
    uint8_t         i;
    uint8_t         j;

    /* Set pointer to input data */
    p_input_data = &p_raw_data[0];

    /* Set initial value */
    crc = RM_RRH62000_CALC_CRC_INITIAL_VALUE;

    /* Execute CRC */
    for (i = 0; i < RM_RRH62000_CALC_CRC_DATA_LENGTH; i++)
    {
        /* Calculate XOR with input value */
        crc ^= *p_input_data;

        for (j = 0; j < RM_RRH62000_CALC_CRC_8BITS_LENGTH; j++)
        {
            if (RM_RRH62000_CALC_CRC_0X80 == (crc & RM_RRH62000_CALC_CRC_MASK_MSB))
            {
                /* If MSB is 1, calculate XOR with the polynomial. */
                crc = (uint8_t) (crc << 1) ^ RM_RRH62000_CALC_CRC_POLYNOMIAL;
            }
            else
            {
                crc <<= 1;
            }
        }

        p_input_data++;
    }

    /* Final XOR */
    crc ^= RM_RRH62000_CALC_CRC_FINAL_XOR;
    FSP_ERROR_RETURN(p_raw_data[RM_RRH62000_CALC_CRC_DATA_LENGTH] == crc, FSP_ERR_SENSOR_INVALID_DATA);

    return FSP_SUCCESS;
}
