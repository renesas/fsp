/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup MIPI_CSI
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_MIPI_CSI_CONTRACT_TYPES_H
#define R_MIPI_CSI_CONTRACT_TYPES_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_mipi_csi_device_types.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

typedef struct st_mipi_csi_event_data
{
    union
    {
        mipi_csi_receive_status_t           receive_status;
        mipi_csi_data_lane_status_t         data_lane_status;
        mipi_csi_virtual_channel_status_t   virtual_channel_status;
        mipi_csi_power_status_t             power_status;
        mipi_csi_short_packet_fifo_status_t fifo_status;
    };
} mipi_csi_event_data_t;

/* @} (end addtogroup MIPI_CSI) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
