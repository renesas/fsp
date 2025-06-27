/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_ETHOSU
 * @{
 **********************************************************************************************************************/

#ifndef RM_ETHOSU_H
#define RM_ETHOSU_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "rm_ethosu_cfg.h"
#include "rm_ethosu_api.h"
#include "ethosu_driver.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Instance control block.  This is private to the FSP and should not be used or modified by the application. */
typedef struct st_rm_ethosu_instance_ctrl
{
    uint32_t                     open;                // Open flag
    rm_ethosu_cfg_t const      * p_cfg;               // Pointer to configuration structure
    struct ethosu_driver * const p_dev;               // Pointer to ethosu driver instance
    void (* p_callback)(rm_ethosu_callback_args_t *); // Pointer to callback
    rm_ethosu_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void * p_context;                                 // Pointer to context to be passed into callback function
} rm_ethosu_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_ethosu_api_t g_rm_ethosu_on_npu;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_ETHOSU_Open(rm_ethosu_ctrl_t * const p_api_ctrl, rm_ethosu_cfg_t const * const p_cfg);
fsp_err_t RM_ETHOSU_CallbackSet(rm_ethosu_ctrl_t * const          p_api_ctrl,
                                void (                          * p_callback)(rm_ethosu_callback_args_t *),
                                void * const                      p_context,
                                rm_ethosu_callback_args_t * const p_callback_memory);
fsp_err_t RM_ETHOSU_Close(rm_ethosu_ctrl_t * const p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_ETHOSU_H

/*******************************************************************************************************************//**
 * @} (end defgroup RM_ETHOSU)
 **********************************************************************************************************************/
