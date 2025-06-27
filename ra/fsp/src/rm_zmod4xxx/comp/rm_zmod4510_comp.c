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
 #define RM_ZMOD4510_COMP_GEN_CFG_LIB_ENABLE    (1)
#endif

#if RM_ZMOD4510_COMP_GEN_CFG_LIB_ENABLE
 #include "rm_zmod4xxx.h"
 #include "../zmod4xxx_types.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
 #define INIT                                   0
 #define MEASUREMENT                            1

/**********************************/
/* < Define product data length > */
 #define ZMOD4510_PROD_DATA_LEN                 10

// Sequencer adresses
 #define ZMOD4XXX_H_ADDR                        0x40
 #define ZMOD4XXX_D_ADDR                        0x50
 #define ZMOD4XXX_M_ADDR                        0x60
 #define ZMOD4XXX_S_ADDR                        0x68

 #define ZMOD4XXX_0X00                          0x00
 #define ZMOD4XXX_0X50                          0x50
 #define ZMOD4XXX_0X28                          0x28
 #define ZMOD4XXX_0XC3                          0xC3
 #define ZMOD4XXX_0XE3                          0xE3
 #define ZMOD4XXX_0X80                          0x80
 #define ZMOD4XXX_0X40                          0x40
 #define ZMOD4XXX_0XFF                          0xFF
 #define ZMOD4XXX_0X06                          0x06
 #define ZMOD4XXX_0XFE                          0xFE
 #define ZMOD4XXX_0XA2                          0xA2
 #define ZMOD4XXX_0X3E                          0x3E
 #define ZMOD4XXX_0X10                          0x10
 #define ZMOD4XXX_0X52                          0x52
 #define ZMOD4XXX_0X3F                          0x3F
 #define ZMOD4XXX_0X66                          0x66
 #define ZMOD4XXX_0X42                          0x42
 #define ZMOD4XXX_0X23                          0x23
 #define ZMOD4XXX_0X03                          0x03
 #define ZMOD4XXX_0X02                          0x02
 #define ZMOD4XXX_0X41                          0x41
 #define ZMOD4XXX_0X49                          0x49
 #define ZMOD4XXX_0X4A                          0x4A
 #define ZMOD4XXX_0X43                          0x43
 #define ZMOD4XXX_0X5B                          0x5B
 #define ZMOD4XXX_0X97                          0x97

 #define ZMOD4XXX_DATASET_INIT_HEATER           ZMOD4XXX_0X00, ZMOD4XXX_0X50
 #define ZMOD4XXX_DATASET_INIT_DELAY            ZMOD4XXX_0X00, ZMOD4XXX_0X28
 #define ZMOD4XXX_DATASET_INIT_MESUREMENT       ZMOD4XXX_0XC3, ZMOD4XXX_0XE3
 #define ZMOD4XXX_DATASET_INIT_SEQUENCER        ZMOD4XXX_0X00, ZMOD4XXX_0X00, ZMOD4XXX_0X80, ZMOD4XXX_0X40
 #define ZMOD4XXX_DATASET_NO2_O3_HEATER_1       ZMOD4XXX_0X00, ZMOD4XXX_0X50, ZMOD4XXX_0XFF, ZMOD4XXX_0X06
 #define ZMOD4XXX_DATASET_NO2_O3_HEATER_2       ZMOD4XXX_0XFE, ZMOD4XXX_0XA2, ZMOD4XXX_0XFE, ZMOD4XXX_0X3E
 #define ZMOD4XXX_DATASET_NO2_O3_DELAY_1        ZMOD4XXX_0X00, ZMOD4XXX_0X10, ZMOD4XXX_0X00, ZMOD4XXX_0X52
 #define ZMOD4XXX_DATASET_NO2_O3_DELAY_2        ZMOD4XXX_0X3F, ZMOD4XXX_0X66, ZMOD4XXX_0X00, ZMOD4XXX_0X42
 #define ZMOD4XXX_DATASET_NO2_O3_MEASUREMENT    ZMOD4XXX_0X23, ZMOD4XXX_0X03
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_1    ZMOD4XXX_0X00, ZMOD4XXX_0X00, ZMOD4XXX_0X02, ZMOD4XXX_0X41
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_2    ZMOD4XXX_0X00, ZMOD4XXX_0X41, ZMOD4XXX_0X00, ZMOD4XXX_0X41
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_3    ZMOD4XXX_0X00, ZMOD4XXX_0X49, ZMOD4XXX_0X00, ZMOD4XXX_0X50
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_4    ZMOD4XXX_0X02, ZMOD4XXX_0X42, ZMOD4XXX_0X00, ZMOD4XXX_0X42
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_5    ZMOD4XXX_0X00, ZMOD4XXX_0X42, ZMOD4XXX_0X00, ZMOD4XXX_0X4A
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_6    ZMOD4XXX_0X00, ZMOD4XXX_0X50, ZMOD4XXX_0X02, ZMOD4XXX_0X43
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_7    ZMOD4XXX_0X00, ZMOD4XXX_0X43, ZMOD4XXX_0X00, ZMOD4XXX_0X43
 #define ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_8    ZMOD4XXX_0X00, ZMOD4XXX_0X43, ZMOD4XXX_0X80, ZMOD4XXX_0X5B

 #define ZMOD4XXX_LEN_32                        32

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/
static uint8_t data_set_4510_init[] =
{
    // heater
    ZMOD4XXX_DATASET_INIT_HEATER,

    // delay     , measurement
    ZMOD4XXX_DATASET_INIT_DELAY, ZMOD4XXX_DATASET_INIT_MESUREMENT,

    // sequencer
    ZMOD4XXX_DATASET_INIT_SEQUENCER
};

static uint8_t data_set_4510_no2_o3[] =
{
    // this implements the ULP_NN_16ext.xml sequence
    // heater
    ZMOD4XXX_DATASET_NO2_O3_HEATER_1,    ZMOD4XXX_DATASET_NO2_O3_HEATER_2,

    // delay
    ZMOD4XXX_DATASET_NO2_O3_DELAY_1,     ZMOD4XXX_DATASET_NO2_O3_DELAY_2,

    // measurement
    ZMOD4XXX_DATASET_NO2_O3_MEASUREMENT,

    // sequencer
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_1,
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_2,
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_3,
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_4,
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_5,
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_6,
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_7,
    ZMOD4XXX_DATASET_NO2_O3_SEQUENCER_8,
};

// Export to hal_data.h
zmod4xxx_conf g_zmod4510_comp_sensor_type[] =
{
    [INIT] =
        {
        .start = ZMOD4XXX_0X80,
        .h     =
        {.addr    = ZMOD4XXX_H_ADDR,
        .len      = 2,
        .data_buf = &data_set_4510_init[0]},
        .d               =
        {.addr    = ZMOD4XXX_D_ADDR,
        .len      = 2,
        .data_buf = &data_set_4510_init[2]},
        .m               =
        {.addr           = ZMOD4XXX_M_ADDR,
        .len             =
            2, .data_buf = &data_set_4510_init[4]},
        .s               =
        {.addr           = ZMOD4XXX_S_ADDR,
        .len             =
            4, .data_buf = &data_set_4510_init[6]},
        .r               =
        {.addr = ZMOD4XXX_0X97,
        .len   =
            4},
        },

    [MEASUREMENT] =
        {
        .start = ZMOD4XXX_0X80,
        .h     =
        {.addr           = ZMOD4XXX_H_ADDR,
        .len             =
            8, .data_buf = &data_set_4510_no2_o3[0]},
        .d               =
        {.addr           = ZMOD4XXX_D_ADDR,
        .len             =
            8, .data_buf = &data_set_4510_no2_o3[8]},
        .m               =
        {.addr           = ZMOD4XXX_M_ADDR,
        .len             =
            2, .data_buf = &data_set_4510_no2_o3[16]},
        .s               =
        {.addr = ZMOD4XXX_S_ADDR,
        .len   =
            ZMOD4XXX_LEN_32, .data_buf= &data_set_4510_no2_o3[18]},
        .r               =
        {.addr = ZMOD4XXX_0X97,
        .len   =
            ZMOD4XXX_LEN_32},
        .prod_data_len   = ZMOD4510_PROD_DATA_LEN,
        },
};

static fsp_err_t rm_zmod4510_comp_open(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_cfg_t const * const p_cfg);
static fsp_err_t rm_zmod4510_comp_measurement_start(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_comp_measurement_stop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_comp_status_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_comp_read(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                       rm_zmod4xxx_raw_data_t * const p_raw_data);
static fsp_err_t rm_zmod4510_comp_temperature_and_humidity_set(rm_zmod4xxx_ctrl_t * const p_api_ctrl,
                                                               float                      temperature,
                                                               float                      humidity);
static fsp_err_t rm_zmod4510_comp_iaq_1st_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                             rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_iaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                             rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_sulfur_odor_data_calculate(rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                                             rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_oaq_2nd_gen_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                             rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_raq_data_calculate(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                                     rm_zmod4xxx_raw_data_t * const p_raw_data,
                                                     rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_rel_iaq_data_calculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                                         rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                                         rm_zmod4xxx_rel_iaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_pbaq_data_calculate(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                                      rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                                      rm_zmod4xxx_pbaq_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_no2_o3_data_calculate(rm_zmod4xxx_ctrl_t * const        p_api_ctrl,
                                                        rm_zmod4xxx_raw_data_t * const    p_raw_data,
                                                        rm_zmod4xxx_no2_o3_data_t * const p_zmod4xxx_data);
static fsp_err_t rm_zmod4510_comp_close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_zmod4510_comp_device_error_check(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_zmod4xxx_api_t const g_zmod4xxx_on_zmod4510_comp =
{
    .open                      = rm_zmod4510_comp_open,
    .close                     = rm_zmod4510_comp_close,
    .measurementStart          = rm_zmod4510_comp_measurement_start,
    .measurementStop           = rm_zmod4510_comp_measurement_stop,
    .statusCheck               = rm_zmod4510_comp_status_check,
    .read                      = rm_zmod4510_comp_read,
    .iaq1stGenDataCalculate    = rm_zmod4510_comp_iaq_1st_gen_data_calculate,
    .iaq2ndGenDataCalculate    = rm_zmod4510_comp_iaq_2nd_gen_data_calculate,
    .sulfurOdorDataCalculate   = rm_zmod4510_comp_sulfur_odor_data_calculate,
    .oaq2ndGenDataCalculate    = rm_zmod4510_comp_oaq_2nd_gen_data_calculate,
    .raqDataCalculate          = rm_zmod4510_comp_raq_data_calculate,
    .relIaqDataCalculate       = rm_zmod4510_comp_rel_iaq_data_calculate,
    .pbaqDataCalculate         = rm_zmod4510_comp_pbaq_data_calculate,
    .no2O3DataCalculate        = rm_zmod4510_comp_no2_o3_data_calculate,
    .temperatureAndHumiditySet = rm_zmod4510_comp_temperature_and_humidity_set,
    .deviceErrorCheck          = rm_zmod4510_comp_device_error_check,
};

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Initialize the Compensation library
 *
 * @retval FSP_SUCCESS              Successfully started.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_comp_open (rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_cfg_t const * const p_cfg)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_comp_no2_o3_data_calculate (rm_zmod4xxx_ctrl_t * const        p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_close (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_comp_measurement_start (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_comp_measurement_stop (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_comp_status_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_zmod4510_comp_read (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_temperature_and_humidity_set (rm_zmod4xxx_ctrl_t * const p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_iaq_1st_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_iaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_sulfur_odor_data_calculate (rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_oaq_2nd_gen_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_raq_data_calculate (rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_rel_iaq_data_calculate (rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_pbaq_data_calculate (rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
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
static fsp_err_t rm_zmod4510_comp_device_error_check (rm_zmod4xxx_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

#endif
