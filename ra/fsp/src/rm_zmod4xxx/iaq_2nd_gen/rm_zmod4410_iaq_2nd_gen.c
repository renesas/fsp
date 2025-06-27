/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_zmod4xxx_if.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include "r_zmod4xxx_if.h"
#else
 #define RM_ZMOD4410_IAQ_2ND_GEN_CFG_LIB_ENABLE    (1)
#endif

#if RM_ZMOD4410_IAQ_2ND_GEN_CFG_LIB_ENABLE
 #include "rm_zmod4xxx.h"
 #include "../zmod4xxx_types.h"
 #include "iaq_2nd_gen.h"
 #include "zmod4410_config_iaq2.h"
 #include "rm_zmod4xxx_iaq_2nd_cfg.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* Definitions of IAQ 2nd gen Parameter */
 #define RM_ZMOD4410_IAQ_2ND_GEN_DEFAULT_HUMIDITY       (50.0F)
 #define RM_ZMOD4410_IAQ_2ND_GEN_DEFAULT_TEMPERATURE    (20.0F)
 #define RM_ZMOD4410_IAQ_2ND_GEN_RMOX3_OFFSET           (15 * 2)

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_open(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                              rm_zmod4xxx_cfg_t const * const p_cfg);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_measurement_start(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_measurement_stop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_status_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_read(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const p_raw_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_temperature_and_humidity_set(rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                                      float                      temperature,
                                                                      float                      humidity);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_iaq_1st_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                        rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                        rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_sulfur_odor_data_calculate(rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                                                    rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_oaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_raq_data_calculate(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                                            rm_zmod4xxx_raw_data_t * const p_raw_data,
                                                            rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_rel_iaq_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                rm_zmod4xxx_rel_iaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_pbaq_data_calculate(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                             rm_zmod4xxx_pbaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_no2_o3_data_calculate(rm_zmod4xxx_ctrl_t * const        p_api_ctrl,
                                                               rm_zmod4xxx_raw_data_t * const    p_raw_data,
                                                               rm_zmod4xxx_no2_o3_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4410_iaq_2nd_gen_device_error_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_zmod4xxx_api_t const g_zmod4xxx_on_zmod4410_iaq_2nd_gen =
{
    .open                      = rm_zmod4410_iaq_2nd_gen_open,
    .close                     = rm_zmod4410_iaq_2nd_gen_close,
    .measurementStart          = rm_zmod4410_iaq_2nd_gen_measurement_start,
    .measurementStop           = rm_zmod4410_iaq_2nd_gen_measurement_stop,
    .statusCheck               = rm_zmod4410_iaq_2nd_gen_status_check,
    .read                      = rm_zmod4410_iaq_2nd_gen_read,
    .iaq1stGenDataCalculate    = rm_zmod4410_iaq_2nd_gen_iaq_1st_gen_data_calculate,
    .iaq2ndGenDataCalculate    = rm_zmod4410_iaq_2nd_gen_data_calculate,
    .sulfurOdorDataCalculate   = rm_zmod4410_iaq_2nd_gen_sulfur_odor_data_calculate,
    .oaq2ndGenDataCalculate    = rm_zmod4410_iaq_2nd_gen_oaq_2nd_gen_data_calculate,
    .raqDataCalculate          = rm_zmod4410_iaq_2nd_gen_raq_data_calculate,
    .relIaqDataCalculate       = rm_zmod4410_iaq_2nd_gen_rel_iaq_data_calculate,
    .pbaqDataCalculate         = rm_zmod4410_iaq_2nd_gen_pbaq_data_calculate,
    .no2O3DataCalculate        = rm_zmod4410_iaq_2nd_gen_no2_o3_data_calculate,
    .temperatureAndHumiditySet = rm_zmod4410_iaq_2nd_gen_temperature_and_humidity_set,
    .deviceErrorCheck          = rm_zmod4410_iaq_2nd_gen_device_error_check,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Initialize the IAQ 2nd Gen. library
 *
 * @retval FSP_SUCCESS              Successfully started.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_open (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                               rm_zmod4xxx_cfg_t const * const p_cfg)
{
    rm_zmod4xxx_instance_ctrl_t * p_ctrl = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    int8_t lib_err = 0;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib    = p_ctrl->p_zmod4xxx_lib;
    iaq_2nd_gen_handle_t           * p_handle = (iaq_2nd_gen_handle_t *) p_lib->p_handle;

    FSP_PARAMETER_NOT_USED(p_cfg);

    /* Set default temperature and humidity */
    p_lib->temperature = RM_ZMOD4410_IAQ_2ND_GEN_DEFAULT_TEMPERATURE;
    p_lib->humidity    = RM_ZMOD4410_IAQ_2ND_GEN_DEFAULT_HUMIDITY;

    /* Initialize the library */
    lib_err = init_iaq_2nd_gen(p_handle);
    FSP_ERROR_RETURN(0 == lib_err, FSP_ERR_ASSERTION);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate the IAQ 2nd Gen. data with the library API.
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_ASSERTION                      Null pointer passed as a parameter.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 * @retval FSP_ERR_SENSOR_INVALID_DATA            Sensor probably damaged. Algorithm results may be incorrect.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                         rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                         rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data)
{
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl    = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib     = p_ctrl->p_zmod4xxx_lib;
    iaq_2nd_gen_handle_t           * p_handle  = (iaq_2nd_gen_handle_t *) p_lib->p_handle;
    iaq_2nd_gen_results_t          * p_results = (iaq_2nd_gen_results_t *) p_lib->p_results;
    zmod4xxx_dev_t                 * p_device  = (zmod4xxx_dev_t *) p_lib->p_device;

 #if RM_ZMOD4XXX_CFG_OXIDIZING_GAS_CORRECTION_IAQ_2ND_ENABLE
    zmod4xxx_dev_t         * p_device_4510   = (zmod4xxx_dev_t *) p_ctrl->p_zmod4510_device;
    rm_zmod4xxx_raw_data_t * p_raw_data_4510 = p_ctrl->p_zmod4510_raw_data;

  #if RM_ZMOD4XXX_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_device_4510);
    FSP_ASSERT(NULL != p_raw_data_4510);
  #endif
 #else
    zmod4xxx_dev_t * p_device_4510 = NULL;
 #endif

    uint16_t             i;
    int8_t               lib_err = 0;
    iaq_2nd_gen_inputs_t algorithm_input;

    /* Calculate IAQ 2nd Gen. data form ADC data */
 #if RM_ZMOD4XXX_CFG_OXIDIZING_GAS_CORRECTION_IAQ_2ND_ENABLE
    algorithm_input.adc_rmox3_4510 = p_raw_data_4510->adc_data + RM_ZMOD4410_IAQ_2ND_GEN_RMOX3_OFFSET;
 #endif
    algorithm_input.adc_result       = &p_raw_data->adc_data[0];
    algorithm_input.humidity_pct     = p_lib->humidity;
    algorithm_input.temperature_degc = p_lib->temperature;
    lib_err = calc_iaq_2nd_gen(p_handle, p_device, p_device_4510, &algorithm_input, p_results);

    FSP_ERROR_RETURN(0 <= lib_err, FSP_ERR_ASSERTION);

    /* Set Data */
    for (i = 0; i < 13; i++)
    {
        p_zmod4xxx_data->rmox[i] = p_results->rmox[i];
    }

 #if RM_ZMOD4XXX_CFG_OXIDIZING_GAS_CORRECTION_IAQ_2ND_ENABLE
    p_zmod4xxx_data->compensation_rmox = p_results->zmod4510_rmox3;
 #endif
    p_zmod4xxx_data->log_rcda = p_results->log_rcda;
    p_zmod4xxx_data->iaq      = p_results->iaq;
    p_zmod4xxx_data->tvoc     = p_results->tvoc;
    p_zmod4xxx_data->etoh     = p_results->etoh;
    p_zmod4xxx_data->eco2     = p_results->eco2;
    p_zmod4xxx_data->rel_iaq  = p_results->rel_iaq;

    FSP_ERROR_RETURN(IAQ_2ND_GEN_STABILIZATION != lib_err, FSP_ERR_SENSOR_IN_STABILIZATION);
    FSP_ERROR_RETURN(IAQ_2ND_GEN_DAMAGE != lib_err, FSP_ERR_SENSOR_INVALID_DATA);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_measurement_start (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_measurement_stop (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_status_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_read (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                               rm_zmod4xxx_raw_data_t * const p_raw_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_temperature_and_humidity_set (rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                                       float                      temperature,
                                                                       float                      humidity)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(temperature);
    FSP_PARAMETER_NOT_USED(humidity);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_iaq_1st_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                     rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                     rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_sulfur_odor_data_calculate (rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                                                     rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                                                     rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_oaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                     rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                     rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_raq_data_calculate (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const p_raw_data,
                                                             rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_rel_iaq_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                 rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                 rm_zmod4xxx_rel_iaq_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_pbaq_data_calculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                              rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                              rm_zmod4xxx_pbaq_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_no2_o3_data_calculate (rm_zmod4xxx_ctrl_t * const        p_api_ctrl,
                                                                rm_zmod4xxx_raw_data_t * const    p_raw_data,
                                                                rm_zmod4xxx_no2_o3_data_t * const p_zmod4xxx_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_zmod4xxx_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4410_iaq_2nd_gen_device_error_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

#endif
