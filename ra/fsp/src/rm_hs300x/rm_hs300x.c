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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_hs300x.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Open flag */
#define RM_HS300X_OPEN                           (0x433E4432UL) // Open state

/* Definitions of HS300X data size */
#if RM_HS300X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE
 #define RM_HS300X_DATA_SIZE                     (4)            // Both humidity and temperature
#else
 #define RM_HS300X_DATA_SIZE                     (2)            // Humidity only
#endif

/* Definitions of Mask Data for A/D data */
#define RM_HS300X_MASK_HUMIDITY_UPPER_0X3F       (0x3F)
#define RM_HS300X_MASK_TEMPERATURE_LOWER_0XFC    (0xFC)
#define RM_HS300X_MASK_STATUS_0XC0               (0xC0)

/* Definitions for Status Bits of A/D Data */
#define RM_HS300X_DATA_STATUS_VALID              (0x00) // Status-bit: Valid data

/* Definitions for Calculation */
#define RM_HS300X_CALC_STATIC_VALUE              (16383.0F)
#define RM_HS300X_CALC_HUMD_VALUE_100            (100.0F)
#define RM_HS300X_CALC_TEMP_C_VALUE_165          (165.0F)
#define RM_HS300X_CALC_TEMP_C_VALUE_40           (40.0F)
#define RM_HS300X_CALC_DECIMAL_VALUE_100         (100.0F)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
rm_hs300x_api_t const g_hs300x_on_hs300x =
{
    .open             = RM_HS300X_Open,
    .close            = RM_HS300X_Close,
    .measurementStart = RM_HS300X_MeasurementStart,
    .read             = RM_HS300X_Read,
    .dataCalculate    = RM_HS300X_DataCalculate,
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

    p_ctrl->p_cfg                = p_cfg;
    p_ctrl->open                 = RM_HS300X_OPEN;
    p_ctrl->p_comms_i2c_instance = p_cfg->p_instance;
    p_ctrl->p_context            = p_cfg->p_context;
    p_ctrl->p_callback           = p_cfg->p_callback;

    /* Open Communications middleware */
    err = p_ctrl->p_comms_i2c_instance->p_api->open(p_ctrl->p_comms_i2c_instance->p_ctrl,
                                                    p_ctrl->p_comms_i2c_instance->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* May need to add resolution */

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
    uint8_t write_data                 = 0;

#if RM_HS300X_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_HS300X_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Write */
    err = p_ctrl->p_comms_i2c_instance->p_api->write(p_ctrl->p_comms_i2c_instance->p_ctrl, &write_data, 0);
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
    float    tmp_f   = 0.0;
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
    tmp_f = (float) (tmp_u16 | (uint16_t) (p_raw_data->humidity[1]));
    tmp_f = (tmp_f * RM_HS300X_CALC_HUMD_VALUE_100) / RM_HS300X_CALC_STATIC_VALUE;
    p_hs300x_data->humidity.integer_part = (int16_t) tmp_f;
    p_hs300x_data->humidity.decimal_part =
        (int16_t) ((tmp_f - (float) p_hs300x_data->humidity.integer_part) * RM_HS300X_CALC_DECIMAL_VALUE_100);

#if RM_HS300X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE
    /* Temperature [Celsius] */
    tmp_u16 = (uint16_t) ((uint16_t) (p_raw_data->temperature[0]) << 8);
    tmp_f   =
        (float) ((tmp_u16 | (uint16_t) (p_raw_data->temperature[1] & RM_HS300X_MASK_TEMPERATURE_LOWER_0XFC)) >> 2);
    tmp_f = ((tmp_f * RM_HS300X_CALC_TEMP_C_VALUE_165) / RM_HS300X_CALC_STATIC_VALUE) - RM_HS300X_CALC_TEMP_C_VALUE_40;
    p_hs300x_data->temperature.integer_part = (int16_t) tmp_f;
    p_hs300x_data->temperature.decimal_part =
        (int16_t) ((tmp_f - (float) p_hs300x_data->temperature.integer_part) * RM_HS300X_CALC_DECIMAL_VALUE_100);
#endif

    return FSP_SUCCESS;
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

    if (NULL != p_ctrl->p_callback)
    {
        /* Call callback function */
        p_ctrl->p_callback(&hs300x_callback_args);
    }
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal hs300x private function.
 **********************************************************************************************************************/
