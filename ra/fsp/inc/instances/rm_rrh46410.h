/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_RRH46410
 * @{
 **********************************************************************************************************************/

#ifndef RM_RRH46410_H
#define RM_RRH46410_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_rrh46410_cfg.h"
#include "rm_zmod4xxx_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Definitions of Buffer Size */
#define RM_RRH46410_MAX_I2C_BUF_SIZE    (11) // Maximum I2C buffer size

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RRH46410 initialization process block */
typedef struct st_rm_rrh46410_init_process_params
{
    volatile bool                communication_finished; ///< Communication flag for blocking.
    volatile rm_zmod4xxx_event_t event;                  ///< Callback event
} rm_rrh46410_init_process_params_t;

/** RRH46410 control block */
typedef struct st_rm_rrh46410_instance_ctrl
{
    uint32_t                          open;                                    ///< Open flag
    uint8_t                           write_buf[RM_RRH46410_MAX_I2C_BUF_SIZE]; ///< Write buffer for I2C communications
    uint8_t                           read_buf[RM_RRH46410_MAX_I2C_BUF_SIZE];  ///< Read buffer for I2C communications
    uint8_t                         * p_read_data;                             ///< Pointer to read data. This is used for checking error code and checksum in callback
    uint8_t                           read_bytes;                              ///< Read bytes. This is used for checking error code and checksum in callback
    volatile uint8_t                  prev_sample_id;                          ///< Previous sample ID. This is used for checking if sensor is in stabilization
    volatile int16_t                  warmup_counts;                           ///< Counts for warning up. This is used for checking if sensor is in stabilization
    volatile rm_zmod4xxx_event_t      event;                                   ///< Callback event
    rm_rrh46410_init_process_params_t init_process_params;                     ///< For the initialization process.
    rm_zmod4xxx_cfg_t const         * p_cfg;                                   ///< Pointer of configuration block
    rm_comms_instance_t const       * p_comms_i2c_instance;                    ///< Pointer of I2C Communications Middleware instance structure
    void const                      * p_irq_instance;                          ///< Pointer to IRQ instance.
    void * p_context;                                                          ///< Pointer to the user-provided context

    /* Pointer to callback and optional working memory */
    void (* p_comms_callback)(rm_zmod4xxx_callback_args_t * p_args);           ///< I2C Communications callback
    void (* p_irq_callback)(rm_zmod4xxx_callback_args_t * p_args);             ///< IRQ callback
} rm_rrh46410_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_zmod4xxx_api_t const g_zmod4xxx_on_rrh46410;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_RRH46410_Open(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_cfg_t const * const p_cfg);
fsp_err_t RM_RRH46410_MeasurementStart(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RRH46410_MeasurementStop(rm_zmod4xxx_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RRH46410_Read(rm_zmod4xxx_ctrl_t * const p_api_ctrl, rm_zmod4xxx_raw_data_t * const p_raw_data);
fsp_err_t RM_RRH46410_TemperatureAndHumiditySet(rm_zmod4xxx_ctrl_t * const p_api_ctrl, float temperature,
                                                float humidity);
fsp_err_t RM_RRH46410_Iaq2ndGenDataCalculate(rm_zmod4xxx_ctrl_t * const         p_api_ctrl,
                                             rm_zmod4xxx_raw_data_t * const     p_raw_data,
                                             rm_zmod4xxx_iaq_2nd_data_t * const p_rrh46410_data);
fsp_err_t RM_RRH46410_PbaqDataCalculate(rm_zmod4xxx_ctrl_t * const      p_api_ctrl,
                                        rm_zmod4xxx_raw_data_t * const  p_raw_data,
                                        rm_zmod4xxx_pbaq_data_t * const p_rrh46410_data);
fsp_err_t RM_RRH46410_Close(rm_zmod4xxx_ctrl_t * const p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER

#endif                                 /* RM_RRH46410_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_RRH46410)
 **********************************************************************************************************************/
