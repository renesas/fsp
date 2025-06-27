/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_RAI_DATA_COLLECTOR_API_H
#define RM_RAI_DATA_COLLECTOR_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_AI_INTERFACES
 * @defgroup RM_RAI_DATA_COLLECTOR_API Data Collector Interface
 * @brief Interface for RAI Data Collector
 *
 * @section RM_RAI_DATA_COLLECTOR_API_SUMMARY Summary
 * The rai data collector interface provides functionality to collect data from differnet channels using snapshot mode,
 * data feed mode or mixed mode.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"
#include "r_timer_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Data types */
typedef enum e_rai_data_collector_data_type
{
    RAI_DATA_COLLECTOR_DATA_TYPE_INT8_T   = 0x01, ///< Signed 8-bit
    RAI_DATA_COLLECTOR_DATA_TYPE_UINT8_T  = 0x11, ///< Unsigned 8-bit
    RAI_DATA_COLLECTOR_DATA_TYPE_INT16_T  = 0x22, ///< Signed 16-bit
    RAI_DATA_COLLECTOR_DATA_TYPE_UINT16_T = 0x32, ///< Unsigned 16-bit
    RAI_DATA_COLLECTOR_DATA_TYPE_INT32_T  = 0x44, ///< Signed 32-bit
    RAI_DATA_COLLECTOR_DATA_TYPE_UINT32_T = 0x54, ///< Unsigned 32-bit
    RAI_DATA_COLLECTOR_DATA_TYPE_FLOAT    = 0x64, ///< Float
    RAI_DATA_COLLECTOR_DATA_TYPE_DOUBLE   = 0x78, ///< Double
} rai_data_collector_data_type_t;

#define RAI_DATA_COLLECTOR_DATA_TYPE_SIZE_MASK    (0x0F)

/** Data Collector module error events */
typedef enum e_rai_data_collector_error_event_type
{
    RAI_DATA_COLLECTOR_ERROR_TYPE_NONE = 0x00,

    /* E.g PING buf is not released while PONG buf is filled up */
    RAI_DATA_COLLECTOR_ERROR_TYPE_BUF_OVERRUN = 0x01,

    /* E.g PONG buf is filled up but PING buf not submitted yet (e.g some channel failed to keep pace) */
    RAI_DATA_COLLECTOR_ERROR_TYPE_BUF_OUT_OF_SYNC = 0x02,
} rai_data_collector_error_event_t;

/** Error callback function parameter */
typedef struct st_rai_data_collector_error_callback_args
{
    uint8_t instance_id;                    ///< Instance ID
    rai_data_collector_error_event_t event; ///< Error event
} rai_data_collector_error_callback_args_t;

/** Frame buffer structure */
typedef struct st_rai_data_collector_frame_buffer_type
{
    void * p_buf;                             ///< Pointer to data buffer
    rai_data_collector_data_type_t data_type; ///< Data samples in the buffer
} rai_data_collector_frame_buffer_t;

/** Data ready callback function parameter */
typedef struct st_rai_data_collector_callback_args
{
    uint8_t  frames;                                       ///< Number of frame buffers
    uint8_t  instance_id;                                  ///< Instance id
    uint32_t frame_buf_len;                                ///< Frame buffers shall have the same amount of data sample
    rai_data_collector_frame_buffer_t const * p_frame_buf; ///< Array of frame buffers
    void * p_context;                                      ///< Pointer to the user-provided context
} rai_data_collector_callback_args_t;

/** Snapshot mode configuration  */
typedef struct st_rai_data_collector_snapshot_cfg
{
    uint8_t                     channels;     ///< Total snapshot mode channels
    uint16_t                    transfer_len; ///< DTC transfer length
    timer_instance_t const    * p_timer;      ///< Pointer to timer instance
    transfer_instance_t const * p_transfer;   ///< Pointer to DTC instance
} rai_data_collector_snapshot_cfg_t;

/** Data feed mode configuration  */
typedef struct st_rai_data_collector_data_feed_cfg
{
    uint8_t channels;                  ///< Total data feed mode channels
} rai_data_collector_data_feed_cfg_t;

/** RAI Data Collector general configuration  */
typedef struct st_rai_data_collector_cfg
{
    uint32_t channels      : 8;                                                         ///< Total number of channels
    uint32_t instance_id   : 8;                                                         ///< Instance id
    uint32_t virt_channels : 8;                                                         ///< Virtual channels
    uint32_t reserved      : 8;                                                         ///< Reserved

    uint32_t channel_ready_mask;                                                        ///< Bitmask of configured channels
    uint32_t required_frame_len;                                                        ///< Length of each frame buffer
    rai_data_collector_snapshot_cfg_t const  * p_snapshot_cfg;                          ///< Pointer to snapshot mode configuration structure
    rai_data_collector_data_feed_cfg_t const * p_data_feed_cfg;                         ///< Pointer to data feed mode configuration structure
    void * p_extend;                                                                    ///< Pointer to extended configuration structure

    void (* p_callback)(rai_data_collector_callback_args_t const * p_args);             ///< Pointer to the callback function when data is collected
    void (* p_error_callback)(rai_data_collector_error_callback_args_t const * p_args); ///< Pointer to the callback function when there is an error
    void * p_context;                                                                   ///< Pointer to the user-provided context
} rai_data_collector_cfg_t;

/** Data Collector control block.  Allocate an instance specific control block to pass into the Data Collector API calls.
 */
typedef void rai_data_collector_ctrl_t;

/** RAI Data Collector interface API. */
typedef struct st_rai_data_collector_api
{
    /** Initialize Data Collector module instance.
     *
     * @note To reopen after calling this function, call @ref rai_data_collector_api_t::close first.
     * @param[in]  p_ctrl  Pointer to control handle structure
     * @param[in]  p_cfg   Pointer to configuration structure
     */
    fsp_err_t (* open)(rai_data_collector_ctrl_t * const p_ctrl, rai_data_collector_cfg_t const * const p_cfg);

    /** Config transfer source address for snapshot mode channel
     *
     * @param[in]  p_ctrl      Pointer to control handle structure
     * @param[in]  p_src       Pointer to transfer source address
     *
     */

    fsp_err_t (* snapshotChannelRegister)(rai_data_collector_ctrl_t * const p_ctrl, uint8_t channel,
                                          void const * p_src);

    /** Release frame buffers by upper modules
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     * @param[in]  channel  Which snapshot mode channel
     * @param[in]  p_src    Chanenl source buffer address
     */
    fsp_err_t (* bufferRelease)(rai_data_collector_ctrl_t * const p_ctrl);

    /** Reset internal buffers
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* bufferReset)(rai_data_collector_ctrl_t * const p_ctrl);

    /** Starts snapshot mode.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     *
     */
    fsp_err_t (* snapshotStart)(rai_data_collector_ctrl_t * const p_ctrl);

    /** Stops snapshot mode.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     *
     */
    fsp_err_t (* snapshotStop)(rai_data_collector_ctrl_t * const p_ctrl);

    /** Get the PING or PONG buffer address for data transfer. For data feed mode only.
     *
     * @param[in]  p_ctrl      Pointer to control handle structure
     * @param[in]  channel     Which data feed mode channel
     * @param[out] pp_buf      Returned buffer address
     *
     */
    fsp_err_t (* channelBufferGet)(rai_data_collector_ctrl_t * const p_ctrl, uint8_t channel, void ** pp_buf);

    /** Write data to frame buffer using CPU copy. For data feed mode only.
     *
     * @param[in]  p_ctrl      Pointer to control handle structure
     * @param[in]  channel     Which data feed mode channel
     * @param[in]  p_buf       Data buffer
     * @param[in]  len         Length of data buffer in data samples
     *
     */
    fsp_err_t (* channelWrite)(rai_data_collector_ctrl_t * const p_ctrl, uint8_t channel, const void * p_buf,
                               uint32_t len);

    /** Close the specified Data Collector module instance.
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* close)(rai_data_collector_ctrl_t * const p_ctrl);
} rai_data_collector_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rai_data_collector_instance
{
    rai_data_collector_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rai_data_collector_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rai_data_collector_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rai_data_collector_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_RAI_DATA_COLLECTOR_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
