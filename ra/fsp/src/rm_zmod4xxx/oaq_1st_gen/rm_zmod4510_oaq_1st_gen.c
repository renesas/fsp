/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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
 #define RM_ZMOD4510_OAQ_1ST_GEN_CFG_LIB_ENABLE    (1)
#endif

#if RM_ZMOD4510_OAQ_1ST_GEN_CFG_LIB_ENABLE
 #include "rm_zmod4xxx.h"
 #include "../zmod4xxx_types.h"
 #include "oaq_1st_gen.h"
 #include "zmod4510_config_oaq1.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
 #define RM_ZMOD4510_OAQ_1ST_GEN_1E_3    (1e-3)
 #define RM_ZMOD4510_OAQ_1ST_GEN_10E9    (10e9)
 #define RM_ZMOD4510_OAQ_1ST_GEN_1E3     (1e3)

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

static fsp_err_t rm_zmod4510_oaq_1st_gen_open(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                              rm_zmod4xxx_cfg_t const * const p_cfg);
static fsp_err_t rm_zmod4510_oaq_1st_gen_measurement_start(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_oaq_1st_gen_measurement_stop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_oaq_1st_gen_status_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_oaq_1st_gen_read(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const p_raw_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_temperature_and_humidity_set(rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                                      float                      temperature,
                                                                      float                      humidity);
static fsp_err_t rm_zmod4510_oaq_1st_gen_iaq_1st_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_iaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_odor_data_calculate(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                             rm_zmod4xxx_odor_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_sulfur_odor_data_calculate(rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                                                    rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                        rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                        rm_zmod4xxx_oaq_1st_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_oaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                    rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                    rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_raq_data_calculate(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                                            rm_zmod4xxx_raw_data_t * const p_raw_data,
                                                            rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_rel_iaq_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                rm_zmod4xxx_rel_iaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_pbaq_data_calculate(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                             rm_zmod4xxx_pbaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_oaq_1st_gen_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_oaq_1st_gen_device_error_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_oaq_1st_gen_calc_rmox(rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                                   uint8_t                           * adc_result,
                                                   float                             * rmox);

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_zmod4xxx_api_t const g_zmod4xxx_on_zmod4510_oaq_1st_gen =
{
    .open                      = rm_zmod4510_oaq_1st_gen_open,
    .close                     = rm_zmod4510_oaq_1st_gen_close,
    .measurementStart          = rm_zmod4510_oaq_1st_gen_measurement_start,
    .measurementStop           = rm_zmod4510_oaq_1st_gen_measurement_stop,
    .statusCheck               = rm_zmod4510_oaq_1st_gen_status_check,
    .read                      = rm_zmod4510_oaq_1st_gen_read,
    .iaq1stGenDataCalculate    = rm_zmod4510_oaq_1st_gen_iaq_1st_gen_data_calculate,
    .iaq2ndGenDataCalculate    = rm_zmod4510_oaq_1st_gen_iaq_2nd_gen_data_calculate,
    .odorDataCalculate         = rm_zmod4510_oaq_1st_gen_odor_data_calculate,
    .sulfurOdorDataCalculate   = rm_zmod4510_oaq_1st_gen_sulfur_odor_data_calculate,
    .oaq1stGenDataCalculate    = rm_zmod4510_oaq_1st_gen_data_calculate,
    .oaq2ndGenDataCalculate    = rm_zmod4510_oaq_1st_gen_oaq_2nd_gen_data_calculate,
    .raqDataCalculate          = rm_zmod4510_oaq_1st_gen_raq_data_calculate,
    .relIaqDataCalculate       = rm_zmod4510_oaq_1st_gen_rel_iaq_data_calculate,
    .pbaqDataCalculate         = rm_zmod4510_oaq_1st_gen_pbaq_data_calculate,
    .temperatureAndHumiditySet = rm_zmod4510_oaq_1st_gen_temperature_and_humidity_set,
    .deviceErrorCheck          = rm_zmod4510_oaq_1st_gen_device_error_check,
};

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Initialize the OAQ 1st Gen. library
 *
 * @retval FSP_SUCCESS              Successfully started.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_open (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                               rm_zmod4xxx_cfg_t const * const p_cfg)
{
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl            = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    oaq_base_handle_t              * p_handle          = (oaq_base_handle_t *) p_lib->p_handle;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;

    FSP_PARAMETER_NOT_USED(p_cfg);

    /* Initialize the library */
    init_oaq_1st_gen(p_handle, p_zmod4xxx_device->prod_data, STABILIZATION_SAMPLES);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate the OAQ 1st Gen. data with the library API.
 *
 * @retval FSP_SUCCESS                            Successfully results are read.
 * @retval FSP_ERR_SENSOR_IN_STABILIZATION        Module is stabilizing.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                         rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                         rm_zmod4xxx_oaq_1st_data_t * const p_zmod4xxx_data)
{
    rm_zmod4xxx_instance_ctrl_t    * p_ctrl   = (rm_zmod4xxx_instance_ctrl_t *) p_api_ctrl;
    rm_zmod4xxx_lib_extended_cfg_t * p_lib    = p_ctrl->p_zmod4xxx_lib;
    oaq_base_handle_t              * p_handle = (oaq_base_handle_t *) p_lib->p_handle;

    /* Calculate OAQ 1st Gen. data form ADC data */
    rm_zmod4510_oaq_1st_gen_calc_rmox(p_ctrl, &p_raw_data->adc_data[0], p_zmod4xxx_data->rmox);

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
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_measurement_start (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_measurement_stop (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_status_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_read (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_temperature_and_humidity_set (rm_zmod4xxx_ctrl_t * const p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_iaq_1st_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_iaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                                     rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                                     rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data)
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_odor_data_calculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                              rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                              rm_zmod4xxx_odor_data_t * const p_zmod4xxx_data)
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_sulfur_odor_data_calculate (rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_oaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_raq_data_calculate (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_rel_iaq_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_pbaq_data_calculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
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
static fsp_err_t rm_zmod4510_oaq_1st_gen_device_error_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Calculate mox resistance.
 *
 * @retval FSP_SUCCESS              successfully configured.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_oaq_1st_gen_calc_rmox (rm_zmod4xxx_instance_ctrl_t * const p_ctrl,
                                                    uint8_t                           * adc_result,
                                                    float                             * rmox)
{
    rm_zmod4xxx_lib_extended_cfg_t * p_lib             = p_ctrl->p_zmod4xxx_lib;
    zmod4xxx_dev_t                 * p_zmod4xxx_device = (zmod4xxx_dev_t *) p_lib->p_device;
    uint8_t  i;
    uint16_t adc_value  = 0;
    float  * p          = rmox;
    float    rmox_local = 0;

    i = 0;
    while (i < p_zmod4xxx_device->meas_conf->r.len)
    {
        adc_value = (uint16_t) ((((uint16_t) adc_result[i]) << 8) | adc_result[i + 1]);
        if (0.0 > (adc_value - p_zmod4xxx_device->mox_lr))
        {
            *p = (float) RM_ZMOD4510_OAQ_1ST_GEN_1E_3;
            p++;
        }
        else if (0.0 >= (p_zmod4xxx_device->mox_er - adc_value))
        {
            *p = (float) RM_ZMOD4510_OAQ_1ST_GEN_10E9;
            p++;
        }
        else
        {
            rmox_local = (float) p_zmod4xxx_device->config[0] * (float) RM_ZMOD4510_OAQ_1ST_GEN_1E3 *
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
