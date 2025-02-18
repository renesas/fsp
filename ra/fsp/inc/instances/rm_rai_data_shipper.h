/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_RAI_DATA_SHIPPER_H
#define RM_RAI_DATA_SHIPPER_H

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
#include "rm_rai_data_shipper_cfg.h"
#include "rm_rai_data_shipper_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_RAI_DATA_SHIPPER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Header buffer structure */
typedef __PACKED_STRUCT st_rai_data_shipper_header_buffer_type
{
    uint8_t  rssn[4];                                                     // "RSSN" for synchronization
    uint8_t  version;                                                     // Version
    uint8_t  crc_enable;                                                  // CRC enabled or not
    uint8_t  instance_id;                                                 // Data collector instance id
    uint8_t  reserved;                                                    // Reserved
    uint16_t events;                                                      // Events e.g buffer overflow
    uint16_t diagnostic_data_len;                                         // Diagnostic data length in bytes
    uint32_t frame_buf_len;                                               // Frame buffer length in data samples
    uint8_t  channels;                                                    // Total number of sensors
    uint8_t  data_type[(RM_RAI_DATA_COLLECTOR_CFG_MAX_CHANNELS + 1) / 2]; // Channel data type. 4-bit for each channel.
} rai_data_shipper_header_buffer_t;

typedef struct st_rai_data_shipper_data_buffer_type
{
    void   * p_buf;                    // Pointer to data buffer
    uint32_t len;                      // Data buffer length in bytes
} rai_data_shipper_data_buffer_t;

typedef struct st_rai_data_shipper_tx_info_type
{
    /** CRC's address is 4-byte aligned for USB PCDC (HS/FS) could transmit by DMA transfer */
    uint16_t crc BSP_ALIGN_VARIABLE(4);                                                // 16-bit CRC value

    uint8_t current;                                                                   // Current channel being sent
    uint8_t channels;                                                                  // Total number of channels
    rai_data_shipper_data_buffer_t   data[RM_RAI_DATA_COLLECTOR_CFG_MAX_CHANNELS + 2]; // Array of sensor buffers + Debug data + CRC
    rai_data_shipper_header_buffer_t header;
    uint8_t write_requests;                                                            // Skipped write request counter
} rai_data_shipper_tx_info_t;

/** RAI_DATA_SHIPPER instance control block. Initialization occurs when RM_RAI_DATA_SHIPPER_Open() is called. */
typedef struct st_rai_data_shipper_instance_ctrl
{
    uint32_t opened;                                                                        // Flag to determine if the module is open or not
    rai_data_shipper_cfg_t const * p_cfg;                                                   // Pointer to configuration structure
    rai_data_shipper_tx_info_t     tx_info[RM_RAI_DATA_SHIPPER_MAX_NUMBER_OF_DC_INSTANCES]; // Cached tx info. Data collector instance will be indexed by its ID.
    volatile uint8_t               data_ready_mask;                                         // Bit mask of data collector instances that have data ready to be sent.
    uint8_t index;                                                                          // Instance being sent
} rai_data_shipper_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const rai_data_shipper_api_t g_ds_on_rai_data_shipper;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t RM_RAI_DATA_SHIPPER_Open(rai_data_shipper_ctrl_t * const      p_api_ctrl,
                                   rai_data_shipper_cfg_t const * const p_cfg);
fsp_err_t RM_RAI_DATA_SHIPPER_Read(rai_data_shipper_ctrl_t * const p_api_ctrl,
                                   void * const                    p_buf,
                                   uint32_t * const                buf_len);
fsp_err_t RM_RAI_DATA_SHIPPER_Write(rai_data_shipper_ctrl_t * const         p_api_ctrl,
                                    rai_data_shipper_write_params_t const * p_write_params);
fsp_err_t RM_RAI_DATA_SHIPPER_Close(rai_data_shipper_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end addgroup RM_RAI_DATA_SHIPPER)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
