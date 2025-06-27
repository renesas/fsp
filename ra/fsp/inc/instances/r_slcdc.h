/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup SLCDC
 * @{
 **********************************************************************************************************************/

#ifndef R_SLCDC_H
#define R_SLCDC_H

#include "bsp_api.h"
#include "r_slcdc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** SLCDC control block. DO NOT INITIALIZE.  Initialization occurs when @ref slcdc_api_t::open is called */
typedef struct st_slcdc_instance_ctrl
{
    uint32_t            open;          // Status of SLCD module
    slcdc_cfg_t const * p_cfg;         // Pointer to SLCDC configuration
    void              * p_context;     // Pointer to the higher level device context
} slcdc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
extern const slcdc_api_t g_slcdc_on_slcdc;

/** @endcond */

/**********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_SLCDC_Open(slcdc_ctrl_t * const p_ctrl, slcdc_cfg_t const * const p_cfg);
fsp_err_t R_SLCDC_Write(slcdc_ctrl_t * const p_ctrl,
                        uint8_t const        start_segment,
                        uint8_t const      * p_data,
                        uint8_t const        segment_count);
fsp_err_t R_SLCDC_Modify(slcdc_ctrl_t * const p_ctrl,
                         uint8_t const        segment_number,
                         uint8_t const        data_mask,
                         uint8_t const        data);
fsp_err_t R_SLCDC_Start(slcdc_ctrl_t * const p_ctrl);
fsp_err_t R_SLCDC_Stop(slcdc_ctrl_t * const p_ctrl);
fsp_err_t R_SLCDC_SetContrast(slcdc_ctrl_t * const p_ctrl, slcdc_contrast_t const contrast);
fsp_err_t R_SLCDC_SetDisplayArea(slcdc_ctrl_t * const p_ctrl, slcdc_display_area_t const display_area);
fsp_err_t R_SLCDC_Close(slcdc_ctrl_t * const p_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_SLCDC_H

/*******************************************************************************************************************//**
 * @} (end addtogroup SLCDC)
 **********************************************************************************************************************/
