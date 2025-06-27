/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_VIN_H
#define R_VIN_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_vin_cfg.h"
#include "r_vin_device_types.h"
#include "r_capture_api.h"
#include "r_mipi_csi.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup VIN
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** VIN instance control block. Implements  */
typedef enum e_vin_event
{
    VIN_EVENT_NONE,                    ///< No Event
    VIN_EVENT_NOTIFY,                  ///< Notification Event
    VIN_EVENT_ERROR                    ///< Error Event
} vin_event_t;

/** VIN instance control block. */
typedef struct st_vin_instance_ctrl
{
    uint32_t              open;                     ///< Interface is open
    capture_cfg_t const * p_cfg;                    // Pointer to the configuration structure
    void (* p_callback)(capture_callback_args_t *); ///< Pointer to callback that is called when an adc_event_t occurs.

    void * p_context;                               ///< Pointer to context to be passed into callback function
    capture_callback_args_t * p_callback_memory;    ///< Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
} vin_instance_ctrl_t;

/** Extended configuration structure for VIN. */
typedef struct st_vin_extended_cfg
{
    mipi_csi_instance_t const * p_mipi_csi_instance; ///< Pointer to mipi physical layer instance

    vin_input_ctrl_t      input_ctrl;
    vin_output_ctrl_t     output_ctrl;
    vin_conversion_ctrl_t conversion_ctrl;
    vin_conversion_data_t conversion_data;
    vin_interrupt_cfg_t   interrupt_cfg;
} vin_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const capture_api_t g_capture_on_vin;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_VIN_Open(capture_ctrl_t * const p_api_ctrl, capture_cfg_t const * const p_cfg);
fsp_err_t R_VIN_Close(capture_ctrl_t * const p_api_ctrl);
fsp_err_t R_VIN_CaptureStart(capture_ctrl_t * const p_api_ctrl, uint8_t * const p_buffer);
fsp_err_t R_VIN_StatusGet(capture_ctrl_t * const p_api_ctrl, capture_status_t * p_status);

/*******************************************************************************************************************//**
 * @} (end defgroup VIN)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_VIN_H
