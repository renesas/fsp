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

/*******************************************************************************************************************//**
 * @addtogroup RM_ZMOD4XXX
 * @{
 **********************************************************************************************************************/

#ifndef RM_ZMOD4XXX_H
#define RM_ZMOD4XXX_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_zmod4xxx_api.h"
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else
 #include "rm_zmod4xxx_cfg.h"
#endif

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Buffer Size */
#define RM_ZMOD4XXX_MAX_I2C_BUF_SIZE    (64) // Maximum I2C buffer size

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** ZMOD4XXX Library type */
typedef enum e_rm_zmod4xxx_lib_type
{
    RM_ZMOD4410_LIB_TYPE_IAQ_1ST_GEN_CONTINUOUS = 1,
    RM_ZMOD4410_LIB_TYPE_IAQ_1ST_GEN_LOW_POWER,
    RM_ZMOD4410_LIB_TYPE_IAQ_2ND_GEN,
    RM_ZMOD4410_LIB_TYPE_IAQ_2ND_GEN_ULP,
    RM_ZMOD4410_LIB_TYPE_ODOR,
    RM_ZMOD4410_LIB_TYPE_SULFUR_ODOR,
    RM_ZMOD4510_LIB_TYPE_OAQ_1ST_GEN,
    RM_ZMOD4510_LIB_TYPE_OAQ_2ND_GEN,
    RM_ZMOD4450_LIB_TYPE_RAQ,
} rm_zmod4xxx_lib_type_t;

/** ZMOD4XXX initialization process block */
typedef struct st_rm_zmod4xxx_init_process_params
{
    volatile uint32_t            delay_ms;               ///< Delay milliseconds.
    volatile bool                communication_finished; ///< Communication flag for blocking.
    volatile bool                measurement_finished;   ///< IRQ flag
    volatile rm_zmod4xxx_event_t event;                  ///< Callback event
} rm_zmod4xxx_init_process_params_t;

typedef struct st_rm_zmod4xxx_status_params
{
    uint8_t       value;
    volatile bool flag;
} rm_zmod4xxx_status_params_t;

/* ZMOD4XXX lib configuration */
typedef struct st_rm_zmod4xxx_lib_extended_cfg
{
    rm_zmod4xxx_lib_type_t const lib_type;    ///< Library type.
    float const               sample_period;  ///< Time between samples.
    uint16_t const            product_id;     ///< ZMOD4XXX product ID.
    rm_zmod4xxx_api_t const * p_api;          ///< Pointer to APIs.
    void const              * p_data_set;     ///< Pointer to ZMOD4XXX sensor data set.
    uint8_t const           * p_product_data; ///< Pointer to ZMOD4XXX product data
    void const              * p_device;       ///< Pointer to ZMOD4XXX device structure.
    void const              * p_handle;       ///< Pointer to ZMOD4XXX library handler.
    void const              * p_results;      ///< Pointer to ZMOD4XXX library results.
    float temperature;                        ///< Temperature for OAQ 2nd
    float humidity;                           ///< Humidity for OAQ 2nd
} rm_zmod4xxx_lib_extended_cfg_t;

/** ZMOD4XXX control block */
typedef struct st_rm_zmod4xxx_instance_ctrl
{
    uint32_t open;                                                   ///< Open flag
    uint8_t  buf[RM_ZMOD4XXX_MAX_I2C_BUF_SIZE];                      ///< Buffer for I2C communications
    uint8_t  register_address;                                       ///< Register address to access
    rm_zmod4xxx_status_params_t       status;                        ///< Status parameter
    volatile bool                     dev_err_check;                 ///< Flag for checking device error
    volatile rm_zmod4xxx_event_t      event;                         ///< Callback event
    rm_zmod4xxx_init_process_params_t init_process_params;           ///< For the initialization process.
    rm_zmod4xxx_cfg_t const         * p_cfg;                         ///< Pointer of configuration block
    rm_comms_instance_t const       * p_comms_i2c_instance;          ///< Pointer of I2C Communications Middleware instance structure
    rm_zmod4xxx_lib_extended_cfg_t  * p_zmod4xxx_lib;                ///< Pointer of ZMOD4XXX Lib extended configuration
    void const * p_irq_instance;                                     ///< Pointer to IRQ instance.
    void const * p_context;                                          ///< Pointer to the user-provided context

    /* Pointer to callback and optional working memory */
    void (* p_comms_callback)(rm_zmod4xxx_callback_args_t * p_args); ///< I2C Communications callback
    void (* p_irq_callback)(rm_zmod4xxx_callback_args_t * p_args);   ///< IRQ callback
} rm_zmod4xxx_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_zmod4xxx_api_t const g_zmod4xxx_on_zmod4xxx;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_ZMOD4XXX_Open(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_cfg_t const * const p_cfg);
fsp_err_t RM_ZMOD4XXX_MeasurementStart(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t RM_ZMOD4XXX_MeasurementStop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t RM_ZMOD4XXX_StatusCheck(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t RM_ZMOD4XXX_Read(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_raw_data_t * const p_raw_data);
fsp_err_t RM_ZMOD4XXX_TemperatureAndHumiditySet(rm_zmod4xxx_ctrl_t * const p_api_ctrl, float temperature,
                                                float humidity);
fsp_err_t RM_ZMOD4XXX_DeviceErrorCheck(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t RM_ZMOD4XXX_Iaq1stGenDataCalculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                             rm_zmod4xxx_iaq_1st_data_t * const p_zmod4xxx_data);
fsp_err_t RM_ZMOD4XXX_Iaq2ndGenDataCalculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                             rm_zmod4xxx_iaq_2nd_data_t * const p_zmod4xxx_data);
fsp_err_t RM_ZMOD4XXX_OdorDataCalculate(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                        rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                        rm_zmod4xxx_odor_data_t * const p_zmod4xxx_data);
fsp_err_t RM_ZMOD4XXX_SulfurOdorDataCalculate(rm_zmod4xxx_ctrl_t * const             p_api_ctrl,
                                              rm_zmod4xxx_raw_data_t * const         p_raw_data,
                                              rm_zmod4xxx_sulfur_odor_data_t * const p_zmod4xxx_data);
fsp_err_t RM_ZMOD4XXX_Oaq1stGenDataCalculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                             rm_zmod4xxx_oaq_1st_data_t * const p_zmod4xxx_data);
fsp_err_t RM_ZMOD4XXX_Oaq2ndGenDataCalculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                             rm_zmod4xxx_oaq_2nd_data_t * const p_zmod4xxx_data);
fsp_err_t RM_ZMOD4XXX_RaqDataCalculate(rm_zmod4xxx_ctrl_t * const     p_api_ctrl,
                                       rm_zmod4xxx_raw_data_t * const p_raw_data,
                                       rm_zmod4xxx_raq_data_t * const p_zmod4xxx_data);
fsp_err_t RM_ZMOD4XXX_Close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_ZMOD4XXX_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_ZMOD4XXX)
 **********************************************************************************************************************/
