/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_SMBUS
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_SMBUS_H
#define RM_COMMS_SMBUS_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_comms_api.h"
#include "r_i2c_master_api.h"
#include "r_elc_api.h"
#include "r_elc.h"
#include "r_timer_api.h"
#include "r_gpt.h"
#include "rm_comms_smbus_cfg.h"
#include "rm_comms_i2c.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* This macro contains 32 data bytes + 1 command code byte + 2 count bytes + 1 PEC byte + 1 address byte */
#define RM_COMMS_SMBUS_TRANSMISSION_MAX_BYTES    (37U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** SMBus specific event */
typedef enum e_rm_comms_smbus_event
{
    RM_COMMS_SMBUS_NO_ERROR = 0,       ///< SMBus transmission complete without any error.
    RM_COMMS_SMBUS_MISC_ERROR,         ///< Dependency modules failed.
    RM_COMMS_SMBUS_DATA_CORRUPT,       ///< PEC byte is incorrect.
    RM_COMMS_SMBUS_SEXT_TIMEOUT,       ///< Total transmission time exceeded 25 ms.
    RM_COMMS_SMBUS_MEXT_TIMEOUT,       ///< Transmission time between each event exceeded 10 ms.
} rm_comms_smbus_event_t;

/** SMBus error structure */
typedef struct rm_comms_smbus_error_t
{
    rm_comms_smbus_event_t smbus_event;
} rm_comms_smbus_error_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_comms_api_t const g_comms_on_comms_smbus;

/** @endcond */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Extend configuration of SMBus **/
typedef struct st_rm_comms_smbus_extended_cfg
{
    bool pec_enable;                                          ///< Calculate PEC byte for SMBus transmission.
    rm_comms_i2c_bus_extended_cfg_t * p_comms_i2c_extend_cfg; ///< Pointer to extend configuration block of rm_comms_i2c
    rm_comms_i2c_instance_ctrl_t    * p_comms_i2c_ctrl;       ///< Control block of rm_comms_i2c
} rm_comms_smbus_extended_cfg_t;

/** SMBus middleware control block **/
typedef struct st_rm_comms_smbus_instance_ctrl
{
    bool     timer_is_enabled;                                  ///< Validate that external event triggers stop the timer is enabled
    uint8_t  write_buff[RM_COMMS_SMBUS_TRANSMISSION_MAX_BYTES]; ///< Intermediate buffer
    uint8_t  receive_crc_seed;                                  ///< CRC seed value
    uint32_t open;                                              ///< Open flag.

    rm_comms_i2c_instance_ctrl_t * p_comms_i2c_ctrl;            ///< Control block of rm_comms_i2c
    rm_comms_smbus_error_t       * p_smbus_error;               ///< SMBus specific error code

    void * p_context;
} rm_comms_smbus_instance_ctrl_t;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_SMBUS_Open(rm_comms_ctrl_t * const p_api_ctrl, rm_comms_cfg_t const * const p_cfg);

fsp_err_t RM_COMMS_SMBUS_Close(rm_comms_ctrl_t * const p_api_ctrl);

fsp_err_t RM_COMMS_SMBUS_Read(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);

fsp_err_t RM_COMMS_SMBUS_Write(rm_comms_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);

fsp_err_t RM_COMMS_SMBUS_WriteRead(rm_comms_ctrl_t * const            p_api_ctrl,
                                   rm_comms_write_read_params_t const write_read_params);

fsp_err_t RM_COMMS_SMBUS_CallbackSet(rm_comms_ctrl_t * const p_api_ctrl,
                                     void (                * p_callback)(rm_comms_callback_args_t *),
                                     void * const            p_context);

void rm_comms_smbus_transmission_callback(i2c_master_callback_args_t * p_args);

void rm_comms_smbus_timeout_callback(timer_callback_args_t * p_args);

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif                                 /* RM_COMMS_SMBUS_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMM_SMBUS)
 **********************************************************************************************************************/
