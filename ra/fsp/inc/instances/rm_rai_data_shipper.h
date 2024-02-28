/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
    uint8_t current;                                                                   // Current channel being sent
    uint8_t channels;                                                                  // Total number of channels
    uint8_t write_requests;                                                            // Skipped write request counter
    uint8_t crc;                                                                       // 8-bit CRC value

    rai_data_shipper_data_buffer_t   data[RM_RAI_DATA_COLLECTOR_CFG_MAX_CHANNELS + 2]; // Array of sensor buffers + Debug data + CRC
    rai_data_shipper_header_buffer_t header;                                           // Header buffer
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
