/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "rm_rrh47000.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_RRH47000_OPEN                                     (('R' << 24U) | ('H' << 16U) | ('4' << 8U) | ('7' << 0U)) // Open state, R"RH47"000

/* Definitions of Timeout */
#define RM_RRH47000_TIMEOUT                                  (100)

/* Definitions of Retry max counts */
#define RM_RRH47000_RETRY_MAX_COUNTS                         (5)
#define RM_RRH47000_RETRY_GET_ABC_PARAMETERS_COUNTS          (1000) // 1000 * 1ms = 1000ms

/* Definitions of Command */
#define RM_RRH47000_COMMAND_GET_MEASUREMENT_RESULTS          (0x31)
#define RM_RRH47000_COMMAND_SET_ABC_PARAMETERS               (0x10)
#define RM_RRH47000_COMMAND_GET_FIRMWARE_VERSION             (0x1E)

/* Definitions of data size */
#define RM_RRH47000_LEN_GET_MEASUREMENT_RESULTS_RES_BYTES    (10)
#define RM_RRH47000_LEN_SET_ABC_PARAMETERS_REQ_BYTES         (7)
#define RM_RRH47000_LEN_SET_ABC_PARAMETERS_RES_BYTES         (8)
#define RM_RRH47000_LEN_GET_FIRMWARE_VERSION_RES_BYTES       (13)

/* Definitions of Mask */
#define RM_RRH47000_MASK_CHECKSUM_0XFF                       (0xFF)

/* Definitions of Position */
#define RM_RRH47000_POSITION_CO2                             (1)
#define RM_RRH47000_POSITION_TEMPERATURE                     (5)
#define RM_RRH47000_POSITION_HUMIDITY                        (7)

/* Definitions of Calculation */
#define RM_RRH47000_CALC_0X100                               (0x100)
#define RM_RRH47000_CALC_DECIMAL_VALUE_100                   (100)
#define RM_RRH47000_CALC_MASK_MINUS_VALUE                    (0x8000)
#define RM_RRH47000_CALC_MINUS_VALUE                         (0x8000)

/* Definitions of Shift */
#define RM_RRH47000_SHIFT_8                                  (8)

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_air_sensor_api_t const g_air_sensor_on_rrh47000 =
{
    .open                = RM_RRH47000_Open,
    .close               = RM_RRH47000_Close,
    .read                = RM_RRH47000_Read,
    .dataCalculate       = RM_RRH47000_DataCalculate,
    .statusCheck         = RM_RRH47000_StatusCheck,
    .firmwareVersionGet  = RM_RRH47000_FirmwareVersionGet,
    .algorithmVersionGet = RM_RRH47000_AlgorithmVersionGet,
};

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
extern fsp_err_t rm_rrh47000_delay_ms(rm_air_sensor_ctrl_t * const p_ctrl, uint32_t const delay_ms);
void             rm_rrh47000_comms_i2c_callback(rm_comms_callback_args_t * p_args);

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

static fsp_err_t rm_rrh47000_i2c_read(rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                      rm_comms_write_read_params_t const  params);
static fsp_err_t rm_rrh47000_i2c_write(rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                       uint8_t * const                     p_src,
                                       uint32_t const                      bytes);
static fsp_err_t rm_rrh47000_read_measurement_results(rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                                      uint8_t * const                     p_raw_data);
static fsp_err_t rm_rrh47000_get_abc(rm_rrh47000_instance_ctrl_t * const p_ctrl, uint8_t * const p_setting_data);
static fsp_err_t rm_rrh47000_set_abc(rm_rrh47000_instance_ctrl_t * const p_ctrl, uint8_t * const p_setting_data);
static fsp_err_t rm_rrh47000_read_firmware_version(rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                                   rm_air_sensor_version_t * const     p_version);
static uint32_t rm_rrh47000_calculate_checksum(uint8_t * const p_data, uint8_t const bytes);
static void     rm_rrh47000_process_in_callback(rm_air_sensor_ctrl_t * const          p_api_ctrl,
                                                rm_air_sensor_callback_args_t * const p_args);

/*******************************************************************************************************************//**
 * @addtogroup RM_RRH47000
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the RRH47000 sensor module.
 * Implements @ref rm_air_sensor_api_t::open.
 *
 * @retval FSP_SUCCESS                  RRH47000 successfully configured.
 * @retval FSP_ERR_ASSERTION            Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_DATA         Checksum error occurs.
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_Open (rm_air_sensor_ctrl_t * const p_api_ctrl, rm_air_sensor_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh47000_instance_ctrl_t * p_ctrl = (rm_rrh47000_instance_ctrl_t *) p_api_ctrl;
    uint32_t checksum;
    bool     is_valid;
    uint8_t  set_abc_data[RM_RRH47000_LEN_SET_ABC_PARAMETERS_RES_BYTES];
    uint32_t counts;

#if RM_RRH47000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_comms_instance);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(RM_RRH47000_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Set instances */
    p_ctrl->p_cfg                = p_cfg;
    p_ctrl->p_comms_i2c_instance = p_cfg->p_comms_instance;

    /* Set parameters */
    p_ctrl->p_version        = NULL;
    p_ctrl->p_context        = p_cfg->p_context;
    p_ctrl->p_comms_callback = p_cfg->p_comms_callback;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    counts = RM_RRH47000_RETRY_GET_ABC_PARAMETERS_COUNTS;
    do
    {
        /* Clear the flag */
        is_valid = false;

        /* Get current auto zero configuration */
        err = rm_rrh47000_get_abc(p_ctrl, &set_abc_data[0]);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Checksum calculation */
        checksum = rm_rrh47000_calculate_checksum(&set_abc_data[0], RM_RRH47000_LEN_SET_ABC_PARAMETERS_RES_BYTES);
        if ((uint32_t) set_abc_data[RM_RRH47000_LEN_SET_ABC_PARAMETERS_RES_BYTES - 1] == checksum)
        {
            /* Set the flag */
            is_valid = true;
        }
        else
        {
            /* Delay 1ms */
            rm_rrh47000_delay_ms(p_ctrl, 1);
            counts--;
        }
    } while ((false == is_valid) && (0 < counts));

    FSP_ERROR_RETURN(false != is_valid, FSP_ERR_INVALID_DATA);

    /* Set auto zero configuration */
    err = rm_rrh47000_set_abc(p_ctrl, &set_abc_data[0]);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check if everything is okay */
    p_ctrl->open = RM_RRH47000_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function should be called when close the sensor module. Implements @ref rm_air_sensor_api_t::close.
 *
 * @retval FSP_SUCCESS              Successfully closed.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_Close (rm_air_sensor_ctrl_t * const p_api_ctrl)
{
    rm_rrh47000_instance_ctrl_t * p_ctrl = (rm_rrh47000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH47000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_RRH47000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Close Communications Middleware */
    p_ctrl->p_comms_i2c_instance->p_api->close(p_ctrl->p_comms_i2c_instance->p_ctrl);

    /* Clear Open flag */
    p_ctrl->open = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called to get measurement results after measurement finishes.
 * Implements @ref rm_air_sensor_api_t::read
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_Read (rm_air_sensor_ctrl_t * const p_api_ctrl, rm_air_sensor_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh47000_instance_ctrl_t * p_ctrl = (rm_rrh47000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH47000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ERROR_RETURN(RM_RRH47000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Clear the event */
    p_ctrl->event = RM_AIR_SENSOR_EVENT_ERROR;

    /* Read measurement results */
    err = rm_rrh47000_read_measurement_results(p_ctrl, (uint8_t *) p_raw_data);
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
 * @retval FSP_ERR_SENSOR_INVALID_DATA             Checksum error occurs.
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_DataCalculate (rm_air_sensor_ctrl_t * const           p_api_ctrl,
                                     const rm_air_sensor_raw_data_t * const p_raw_data,
                                     rm_air_sensor_data_t * const           p_rrh47000_data)
{
    rm_rrh47000_instance_ctrl_t * p_ctrl = (rm_rrh47000_instance_ctrl_t *) p_api_ctrl;
    uint16_t tmp_u16;
    int16_t  tmp_16;

#if RM_RRH47000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_raw_data);
    FSP_ASSERT(NULL != p_rrh47000_data);
    FSP_ERROR_RETURN(RM_RRH47000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check if checksum error occurs. */
    FSP_ERROR_RETURN(RM_AIR_SENSOR_EVENT_SUCCESS == p_ctrl->event, FSP_ERR_SENSOR_INVALID_DATA);

    /* Set CO2 data [ppm] */
    tmp_u16 =
        (uint16_t) (((uint16_t) p_raw_data->results[RM_RRH47000_POSITION_CO2] << RM_RRH47000_SHIFT_8) |
                    (uint16_t) p_raw_data->results[RM_RRH47000_POSITION_CO2 + 1]);
    p_rrh47000_data->eco2.sign         = RM_AIR_SENSOR_SIGN_PLUS;
    p_rrh47000_data->eco2.integer_part = (uint32_t) tmp_u16;
    p_rrh47000_data->eco2.decimal_part = 0;

    /* Set temperature [Celsius] */
    tmp_u16 =
        (uint16_t) (((uint16_t) p_raw_data->results[RM_RRH47000_POSITION_TEMPERATURE] << RM_RRH47000_SHIFT_8) |
                    (uint16_t) p_raw_data->results[RM_RRH47000_POSITION_TEMPERATURE + 1]);
    if (RM_RRH47000_CALC_MINUS_VALUE == (tmp_u16 & RM_RRH47000_CALC_MASK_MINUS_VALUE))
    {
        p_rrh47000_data->temperature.sign = RM_AIR_SENSOR_SIGN_MINUS;
        tmp_16 = (*((int16_t *) &tmp_u16)) * RM_AIR_SENSOR_SIGN_MINUS;
    }
    else
    {
        p_rrh47000_data->temperature.sign = RM_AIR_SENSOR_SIGN_PLUS;
        tmp_16 = (int16_t) tmp_u16;
    }

    p_rrh47000_data->temperature.integer_part = (uint32_t) (tmp_16 / RM_RRH47000_CALC_DECIMAL_VALUE_100);
    p_rrh47000_data->temperature.decimal_part = (uint32_t) (tmp_16 % RM_RRH47000_CALC_DECIMAL_VALUE_100);

    /* Set humidity [%RH] */
    tmp_u16 =
        (uint16_t) (((uint16_t) p_raw_data->results[RM_RRH47000_POSITION_HUMIDITY] << RM_RRH47000_SHIFT_8) |
                    (uint16_t) p_raw_data->results[RM_RRH47000_POSITION_HUMIDITY + 1]);
    p_rrh47000_data->humidity.sign         = RM_AIR_SENSOR_SIGN_PLUS;
    p_rrh47000_data->humidity.integer_part = (uint32_t) (tmp_u16 / RM_RRH47000_CALC_DECIMAL_VALUE_100);
    p_rrh47000_data->humidity.decimal_part = (uint32_t) (tmp_u16 % RM_RRH47000_CALC_DECIMAL_VALUE_100);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  This function should be called to get firmware version.
 * Firmware version will be set "ascii_code" of p_version.
 * Implements @ref rm_air_sensor_api_t::firmwareVersionGet
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not opened configured.
 * @retval FSP_ERR_INVALID_POINTER  Pointer is NULL.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_FirmwareVersionGet (rm_air_sensor_ctrl_t * const    p_api_ctrl,
                                          rm_air_sensor_version_t * const p_version)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh47000_instance_ctrl_t * p_ctrl = (rm_rrh47000_instance_ctrl_t *) p_api_ctrl;

#if RM_RRH47000_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(NULL != p_version, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(RM_RRH47000_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read firmware version */
    err = rm_rrh47000_read_firmware_version(p_ctrl, p_version);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  StatusCheck API is unsupported.
 * Implements @ref rm_air_sensor_api_t::statusCheck
 *
 * @retval FSP_ERR_UNSUPPORTED              Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_StatusCheck (rm_air_sensor_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  AlgorithmVersionGet API is unsupported.
 * Implements @ref rm_air_sensor_api_t::statusCheck
 *
 * @retval FSP_ERR_UNSUPPORTED              Unsupported.
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_AlgorithmVersionGet (rm_air_sensor_ctrl_t * const    p_api_ctrl,
                                           rm_air_sensor_version_t * const p_version)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_version);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_RRH47000)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief RM_RRH47000 callback function called in the I2C Communications Middleware callback function.
 **********************************************************************************************************************/
void rm_rrh47000_comms_i2c_callback (rm_comms_callback_args_t * p_args)
{
    rm_rrh47000_instance_ctrl_t * p_ctrl = (rm_rrh47000_instance_ctrl_t *) p_args->p_context;
    rm_air_sensor_callback_args_t rrh47000_callback_args;
    uint8_t  i;
    uint32_t checksum;

    /* Set context */
    rrh47000_callback_args.p_context = p_ctrl->p_context;

    /* Set event */
    switch (p_args->event)
    {
        case RM_COMMS_EVENT_OPERATION_COMPLETE:
        {
            rrh47000_callback_args.event = RM_AIR_SENSOR_EVENT_SUCCESS;
            break;
        }

        case RM_COMMS_EVENT_ERROR:
        default:
        {
            rrh47000_callback_args.event = RM_AIR_SENSOR_EVENT_ERROR;
            break;
        }
    }

    if (RM_RRH47000_OPEN != p_ctrl->open)
    {
        /* Set flag */
        p_ctrl->init_process_params.communication_finished = true;

        /* Set event */
        p_ctrl->init_process_params.event = rrh47000_callback_args.event;
    }
    else
    {
        if (RM_AIR_SENSOR_EVENT_SUCCESS == rrh47000_callback_args.event)
        {
            /* Checksum calculation */
            checksum = rm_rrh47000_calculate_checksum(p_ctrl->p_read_data, p_ctrl->read_bytes);

            /* Set the event */
            if ((uint32_t) p_ctrl->p_read_data[p_ctrl->read_bytes - 1] != checksum)
            {
                rrh47000_callback_args.event = RM_AIR_SENSOR_EVENT_CHECKSUM_ERROR;
                p_ctrl->event                = RM_AIR_SENSOR_EVENT_CHECKSUM_ERROR;
            }
            else
            {
                rrh47000_callback_args.event = RM_AIR_SENSOR_EVENT_SUCCESS;
                p_ctrl->event                = RM_AIR_SENSOR_EVENT_SUCCESS;
            }

            if (RM_AIR_SENSOR_EVENT_SUCCESS == rrh47000_callback_args.event)
            {
                if (NULL != p_ctrl->p_version)
                {
                    /* Set ASCII code of firmware version */
                    for (i = 1; i < (p_ctrl->read_bytes - 1); i++)
                    {
                        p_ctrl->p_version->ascii_code[i - 1] = p_ctrl->p_read_data[i];
                    }

                    /* clear the pointer */
                    p_ctrl->p_version = NULL;
                }
            }
        }

        /* Call user callback function */
        rm_rrh47000_process_in_callback(p_ctrl, &rrh47000_callback_args);
    }
}

/*******************************************************************************************************************//**
 * @brief Process in callback function. Call user callback.
 **********************************************************************************************************************/
static void rm_rrh47000_process_in_callback (rm_air_sensor_ctrl_t * const          p_api_ctrl,
                                             rm_air_sensor_callback_args_t * const p_args)
{
    rm_rrh47000_instance_ctrl_t * p_ctrl = (rm_rrh47000_instance_ctrl_t *) p_api_ctrl;

    if (NULL != p_ctrl->p_comms_callback)
    {
        /* Call callback function */
        p_ctrl->p_comms_callback(p_args);
    }
}

/*******************************************************************************************************************//**
 * @brief I2C wrapper function to read from rrh47000 sensor.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh47000_i2c_read (rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                       rm_comms_write_read_params_t const  params)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint16_t  counter      = 0;
    uint16_t  retry_counts = RM_RRH47000_RETRY_MAX_COUNTS;

    do
    {
        if (RM_RRH47000_OPEN != p_ctrl->open)
        {
            /* Clear flag */
            p_ctrl->init_process_params.communication_finished = false;
        }

        /* WriteRead data */
        err = p_ctrl->p_comms_i2c_instance->p_api->writeRead(p_ctrl->p_comms_i2c_instance->p_ctrl, params);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (RM_RRH47000_OPEN != p_ctrl->open)
        {
            /* Wait callback */
            while (false == p_ctrl->init_process_params.communication_finished)
            {
                rm_rrh47000_delay_ms(p_ctrl, 1);
                counter++;
                FSP_ERROR_RETURN(RM_RRH47000_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
            }

            /* Retry counts decrement */
            retry_counts--;
        }
    } while ((RM_RRH47000_OPEN != p_ctrl->open) && (RM_AIR_SENSOR_EVENT_SUCCESS != p_ctrl->init_process_params.event) &&
             (0 < retry_counts));

    /* Check callback event */
    FSP_ERROR_RETURN(RM_AIR_SENSOR_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief I2C wrapper function to write from rrh47000 sensor.
 *
 * @retval FSP_SUCCESS              successfully configured.
 * @retval FSP_ERR_TIMEOUT          communication is timeout.
 * @retval FSP_ERR_ABORTED          communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh47000_i2c_write (rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                        uint8_t * const                     p_src,
                                        uint32_t const                      bytes)
{
    fsp_err_t err          = FSP_SUCCESS;
    uint16_t  counter      = 0;
    uint16_t  retry_counts = RM_RRH47000_RETRY_MAX_COUNTS;

    do
    {
        if (RM_RRH47000_OPEN != p_ctrl->open)
        {
            /* Clear flag */
            p_ctrl->init_process_params.communication_finished = false;
        }

        /* Write data */
        err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, p_src, bytes);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        if (RM_RRH47000_OPEN != p_ctrl->open)
        {
            /* Wait callback */
            while (false == p_ctrl->init_process_params.communication_finished)
            {
                rm_rrh47000_delay_ms(p_ctrl, 1);
                counter++;
                FSP_ERROR_RETURN(RM_RRH47000_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
            }

            /* Decrease retry counts */
            retry_counts--;
        }
    } while ((RM_RRH47000_OPEN != p_ctrl->open) && (RM_AIR_SENSOR_EVENT_SUCCESS != p_ctrl->init_process_params.event) &&
             (0 < retry_counts));

    /* Check callback event */
    FSP_ERROR_RETURN(RM_AIR_SENSOR_EVENT_SUCCESS == p_ctrl->init_process_params.event, FSP_ERR_ABORTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Read measurement results from the sensor.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh47000_read_measurement_results (rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                                       uint8_t * const                     p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH47000_COMMAND_GET_MEASUREMENT_RESULTS;

    /* Set the parameters */
    p_ctrl->p_read_data = p_raw_data;
    p_ctrl->read_bytes  = RM_RRH47000_LEN_GET_MEASUREMENT_RESULTS_RES_BYTES;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh47000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Get current auto zero settings.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh47000_get_abc (rm_rrh47000_instance_ctrl_t * const p_ctrl, uint8_t * const p_setting_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH47000_COMMAND_SET_ABC_PARAMETERS;

    /* Set the parameters */
    p_ctrl->p_read_data = p_setting_data;
    p_ctrl->read_bytes  = RM_RRH47000_LEN_SET_ABC_PARAMETERS_RES_BYTES;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh47000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Set new auto zero settings.
 *
 * @retval FSP_SUCCESS              Successfully read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_rrh47000_set_abc (rm_rrh47000_instance_ctrl_t * const p_ctrl, uint8_t * const p_setting_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_rrh47000_extended_cfg_t * p_extend = (rm_rrh47000_extended_cfg_t *) p_ctrl->p_cfg->p_extend;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH47000_COMMAND_SET_ABC_PARAMETERS;
    p_ctrl->write_buf[1] = p_setting_data[1];
    p_ctrl->write_buf[2] = (uint8_t) p_extend->abc;
    p_ctrl->write_buf[3] = p_extend->correction_cycle_period;
    p_ctrl->write_buf[4] = (uint8_t) (p_extend->co2_baseline_value >> RM_RRH47000_SHIFT_8);
    p_ctrl->write_buf[5] = (uint8_t) (p_extend->co2_baseline_value & RM_RRH47000_MASK_CHECKSUM_0XFF);
    p_ctrl->write_buf[6] = p_setting_data[6];

    /* Send the command and a value */
    err = rm_rrh47000_i2c_write(p_ctrl, &p_ctrl->write_buf[0], RM_RRH47000_LEN_SET_ABC_PARAMETERS_REQ_BYTES);
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
static fsp_err_t rm_rrh47000_read_firmware_version (rm_rrh47000_instance_ctrl_t * const p_ctrl,
                                                    rm_air_sensor_version_t * const     p_version)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_comms_write_read_params_t write_read_params;

    /* Write the command */
    p_ctrl->write_buf[0] = RM_RRH47000_COMMAND_GET_FIRMWARE_VERSION;

    /* Set the parameters */
    p_ctrl->p_version   = p_version;
    p_ctrl->p_read_data = &p_ctrl->read_buf[0];
    p_ctrl->read_bytes  = RM_RRH47000_LEN_GET_FIRMWARE_VERSION_RES_BYTES;

    /* Send the command and receive the error codes and checksum */
    write_read_params.p_src      = &p_ctrl->write_buf[0];
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = p_ctrl->p_read_data;
    write_read_params.dest_bytes = p_ctrl->read_bytes;
    err = rm_rrh47000_i2c_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Calculate checksum.
 **********************************************************************************************************************/
static uint32_t rm_rrh47000_calculate_checksum (uint8_t * const p_data, uint8_t const bytes)
{
    uint8_t  i;
    uint32_t sum;

    /* Checksum calculation */
    sum = 0;
    for (i = 0; i < (bytes - 1); i++)
    {
        sum = (uint32_t) (sum + (uint32_t) p_data[i]);
    }

    return RM_RRH47000_CALC_0X100 - (sum & RM_RRH47000_MASK_CHECKSUM_0XFF);
}
