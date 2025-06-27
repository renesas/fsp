/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_RRH47000
 * @{
 **********************************************************************************************************************/

#ifndef RM_RRH47000_H
#define RM_RRH47000_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_rrh47000_cfg.h"
#include "rm_air_sensor_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RRH47000 Automatic Baseline Correction (ABC) setting. */
typedef enum e_rm_rrh47000_abc
{
    RM_RRH47000_ABC_ENABLE_ALL           = (0x00), ///< Enable all
    RM_RRH47000_ABC_ENABLE_ONLY_ABC      = (0x01), ///< Enable only ABC (automatic baseline correction)
    RM_RRH47000_ABC_ENABLE_ONLY_FAST_ABC = (0x02), ///< Enable only fast ABC (fast automatic baseline correction)
    RM_RRH47000_ABC_DISABLE_ALL          = (0x03), ///< Disable all
} rm_rrh47000_abc_t;

/** RRH47000 initialization process block */
typedef struct st_rm_rrh47000_init_process_params
{
    volatile bool communication_finished; ///< Communication flag for blocking.
    volatile rm_air_sensor_event_t event; ///< Callback event
} rm_rrh47000_init_process_params_t;

/* RRH47000 configuration */
typedef struct st_rm_rrh47000_extended_cfg
{
    rm_rrh47000_abc_t const abc;                     ///< ABC setting.
    uint8_t const           correction_cycle_period; ///< Correction cycle period [days].
    uint32_t const          co2_baseline_value;      ///< CO2 baseline value [ppm].
} rm_rrh47000_extended_cfg_t;

/** RRH47000 control block */
typedef struct st_rm_rrh47000_instance_ctrl
{
    uint32_t                          open;                            ///< Open flag
    uint8_t                           write_buf[7];                    ///< Write buffer for I2C communications
    uint8_t                           read_buf[13];                    ///< Read buffer for I2C communications
    uint8_t                         * p_read_data;                     ///< Pointer to read data. This is used for checksum in callback
    uint8_t                           read_bytes;                      ///< Read bytes. This is used for checksum in callback
    rm_air_sensor_version_t         * p_version;                       ///< Pointer to firmware version
    volatile rm_air_sensor_event_t    event;                           ///< Callback event
    rm_rrh47000_init_process_params_t init_process_params;             ///< For the initialization process.
    rm_air_sensor_cfg_t const       * p_cfg;                           ///< Pointer of configuration block
    rm_comms_instance_t const       * p_comms_i2c_instance;            ///< Pointer of I2C Communications Middleware instance structure
    void * p_context;                                                  ///< Pointer to the user-provided context

    /* Pointer to callback and optional working memory */
    void (* p_comms_callback)(rm_air_sensor_callback_args_t * p_args); ///< I2C Communications callback
} rm_rrh47000_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_air_sensor_api_t const g_air_sensor_on_rrh47000;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_RRH47000_Open(rm_air_sensor_ctrl_t * const p_api_ctrl, rm_air_sensor_cfg_t const * const p_cfg);
fsp_err_t RM_RRH47000_Read(rm_air_sensor_ctrl_t * const p_api_ctrl, rm_air_sensor_raw_data_t * const p_raw_data);
fsp_err_t RM_RRH47000_DataCalculate(rm_air_sensor_ctrl_t * const           p_api_ctrl,
                                    const rm_air_sensor_raw_data_t * const p_raw_data,
                                    rm_air_sensor_data_t * const           p_rrh47000_data);
fsp_err_t RM_RRH47000_FirmwareVersionGet(rm_air_sensor_ctrl_t * const    p_api_ctrl,
                                         rm_air_sensor_version_t * const p_version);
fsp_err_t RM_RRH47000_Close(rm_air_sensor_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RRH47000_StatusCheck(rm_air_sensor_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RRH47000_AlgorithmVersionGet(rm_air_sensor_ctrl_t * const    p_api_ctrl,
                                          rm_air_sensor_version_t * const p_version);

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER

#endif                                 /* RM_RRH47000_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_RRH47000)
 **********************************************************************************************************************/
