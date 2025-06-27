/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_RAI_DATA_SHIPPER_API_H
#define RM_RAI_DATA_SHIPPER_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_AI_INTERFACES
 * @defgroup RM_RAI_DATA_SHIPPER_API Data Shipper Interface
 * @brief Interface for RAI Data Shipper
 *
 * @section RM_RAI_DATA_SHIPPER_API_SUMMARY Summary
 * The rai data shipper interface provides multiple communication methods.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_crc_api.h"
#include "rm_comms_api.h"
#include "rm_rai_data_collector_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Callback function parameter structure */
typedef struct st_rai_data_shipper_callback_args
{
    rm_comms_event_t result;           ///< Whether data is sent successfully or not
    void           * p_context;        ///< Pointer to the user-provided context
    uint8_t          instance;         ///< Data collector instance ID
} rai_data_shipper_callback_args_t;

/** Data Shipper write function parameter structure */
typedef struct st_rai_data_shipper_write_params
{
    uint16_t  events;                                   ///< Events
    uint16_t  diagnostic_data_len;                      ///< Diagnostic data length
    uint8_t * p_diagnostic_data;                        ///< Pointer to diagnostic data
    rai_data_collector_callback_args_t * p_sensor_data; ///< Pointer to sensor data info
} rai_data_shipper_write_params_t;

/** RAI Data Shipper general configuration  */
typedef struct st_rai_data_shipper_cfg
{
    uint8_t divider;                                                ///< Send data on every (divider + 1) requests in case the interface bandwidth is not sufficient

    crc_instance_t const      * p_crc;                              ///< Pointer to CRC instance
    rm_comms_instance_t const * p_comms;                            ///< Pointer to COMMS API instance

    void * p_context;                                               ///< Pointer to the user-provided context
    void (* p_callback)(rai_data_shipper_callback_args_t * p_args); ///< Pointer to the callback function on data sent or error
} rai_data_shipper_cfg_t;

/** Data Shipper control block.  Allocate an instance specific control block to pass into the Data Shipper API calls.
 */
typedef void rai_data_shipper_ctrl_t;

/** RAI Data Shipper interface API. */
typedef struct st_rai_data_shipper_api
{
    /** Initialize Data Shipper module instance.
     *
     * @note To reopen after calling this function, call @ref rai_data_shipper_api_t::close first.
     * @param[in]  p_ctrl  Pointer to control handle structure
     * @param[in]  p_cfg   Pointer to configuration structure
     */
    fsp_err_t (* open)(rai_data_shipper_ctrl_t * const p_ctrl, rai_data_shipper_cfg_t const * const p_cfg);

    /** Read data.
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  p_buf    Pointer to the location to store read data.
     * @param[in]  buf_len  Number of bytes to read.
     */
    fsp_err_t (* read)(rai_data_shipper_ctrl_t * const p_ctrl, void * const p_buf, uint32_t * const buf_len);

    /** Write data.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  write_params     Pointer to write parameters structure
     */
    fsp_err_t (* write)(rai_data_shipper_ctrl_t * const p_ctrl, rai_data_shipper_write_params_t const * p_write_params);

    /** Close the specified Data Shipper module instance.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* close)(rai_data_shipper_ctrl_t * const p_ctrl);
} rai_data_shipper_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rai_data_shipper_instance
{
    rai_data_shipper_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rai_data_shipper_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rai_data_shipper_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rai_data_shipper_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_RAI_DATA_SHIPPER_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
