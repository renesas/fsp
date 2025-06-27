/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_MIPI_CSI_H
#define R_MIPI_CSI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_mipi_csi_cfg.h"
#include "r_mipi_csi_contract_types.h"
#include "r_mipi_csi_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup MIPI_CSI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** MIPI CSI instance control block. */
typedef struct st_mipi_csi_instance_ctrl
{
    uint32_t               open;                     ///< Interface is open
    mipi_csi_cfg_t const * p_cfg;                    ///< Pointer to configuration structure used to open the interface
    void (* p_callback)(mipi_csi_callback_args_t *); ///< Pointer to callback that is called when an adc_event_t occurs.
    void * p_context;                                ///< Pointer to context to be passed into callback function
    mipi_csi_callback_args_t * p_callback_memory;    ///< Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
} mipi_csi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const mipi_csi_api_t g_mipi_csi;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_MIPI_CSI_Open(mipi_csi_ctrl_t * const p_api_ctrl, mipi_csi_cfg_t const * const p_cfg);
fsp_err_t R_MIPI_CSI_Close(mipi_csi_ctrl_t * const p_api_ctrl);
fsp_err_t R_MIPI_CSI_Start(mipi_csi_ctrl_t * const p_api_ctrl);
fsp_err_t R_MIPI_CSI_Stop(mipi_csi_ctrl_t * const p_api_ctrl);
fsp_err_t R_MIPI_CSI_StatusGet(mipi_csi_ctrl_t * const p_api_ctrl, mipi_csi_status_t * p_status);
fsp_err_t R_MIPI_CSI_Read(mipi_csi_ctrl_t * const p_api_ctrl, mipi_csi_short_packet_t * p_data);

/*******************************************************************************************************************//**
 * @} (end defgroup MIPI_CSI)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_MIPI_CSI_H
