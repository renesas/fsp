/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_RAI_DATA_COLLECTOR_H
#define RM_RAI_DATA_COLLECTOR_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>

/* Fixed width integer support. */
#include <stdint.h>

/* bool support */
#include <stdbool.h>

#include "bsp_api.h"
#include "rm_rai_data_collector_cfg.h"
#include "rm_rai_data_collector_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_RAI_DATA_COLLECTOR
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* PING PONG buffer is required */
#define RAI_DATA_COLLECTOR_PING_PONG_BUFFER_SIZE    (2)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Buffer status */
typedef enum e_rai_data_collector_buffer_status_type
{
    RAI_DATA_COLLECTOR_BUFFER_STATUS_IDLE    = 0x00, // PING(or PONG) buffer is idle
    RAI_DATA_COLLECTOR_BUFFER_STATUS_BUSY    = 0x01, // PING(or PONG) buffer is being used
    RAI_DATA_COLLECTOR_BUFFER_STATUS_OVERRUN = 0x02, // PING(or PONG) buffer is overrun
} rai_data_collector_buffer_status_t;

/* Frame buffer (PING PONG buffer) handle */
typedef struct st_rai_data_collector_frame_buffer_handle_type
{
    uint32_t buf_idx;                  // Which buffer (PING or PONG) is being used
    uint32_t accumulated_len;          // Data samples accumulated in each frame buffer
} rai_data_collector_frame_buffer_handle_t;

/* RAI_DATA_COLLECTOR extended configuration */
typedef struct st_rai_data_collector_extended_cfg
{
    transfer_info_t * p_transfer_info;                              // Array of DTC transfer information
    rai_data_collector_frame_buffer_t        * p_ping_pong_buf;     // Array of PING-PONG buffers
    rai_data_collector_frame_buffer_handle_t * p_ping_pong_buf_hnd; // Array of buffer handles
} rai_data_collector_extended_cfg_t;

/** RAI_DATA_COLLECTOR instance control block. Initialization occurs when RM_RAI_DATA_COLLECTOR_Open() is called. */
typedef struct st_rai_data_collector_instance_ctrl
{
    uint32_t opened;                                        // Flag to determine if the module is open or not

    volatile uint32_t channel_ready;                        // Bit mask of channels that have frame buffers ready to submit
    volatile rai_data_collector_buffer_status_t buf_status; // PING-PONG buffer status

    rai_data_collector_cfg_t const    * p_cfg;              // Pointer to configuration structure
    rai_data_collector_extended_cfg_t * p_extend;           // Pointer to extended configuration structure
} rai_data_collector_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const rai_data_collector_api_t g_dc_on_rai_data_collector;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_RAI_DATA_COLLECTOR_Open(rai_data_collector_ctrl_t * const      p_api_ctrl,
                                     rai_data_collector_cfg_t const * const p_cfg);
fsp_err_t RM_RAI_DATA_COLLECTOR_SnapshotChannelRegister(rai_data_collector_ctrl_t * const p_api_ctrl,
                                                        uint8_t                           channel,
                                                        void const                      * p_src);
fsp_err_t RM_RAI_DATA_COLLECTOR_BufferReset(rai_data_collector_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RAI_DATA_COLLECTOR_BufferRelease(rai_data_collector_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RAI_DATA_COLLECTOR_ChannelBufferGet(rai_data_collector_ctrl_t * const p_api_ctrl,
                                                 uint8_t                           channel,
                                                 void                           ** pp_buf);
fsp_err_t RM_RAI_DATA_COLLECTOR_ChannelWrite(rai_data_collector_ctrl_t * const p_api_ctrl,
                                             uint8_t                           channel,
                                             const void                      * p_buf,
                                             uint32_t                          len);
fsp_err_t RM_RAI_DATA_COLLECTOR_SnapshotStart(rai_data_collector_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RAI_DATA_COLLECTOR_SnapshotStop(rai_data_collector_ctrl_t * const p_api_ctrl);
fsp_err_t RM_RAI_DATA_COLLECTOR_Close(rai_data_collector_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_RAI_DATA_COLLECTOR)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
