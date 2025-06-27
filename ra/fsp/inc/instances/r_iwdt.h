/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup IWDT
 * @{
 **********************************************************************************************************************/

#ifndef R_IWDT_H
#define R_IWDT_H

#include "bsp_api.h"

#include "r_iwdt_cfg.h"
#include "r_wdt_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IWDT control block. DO NOT INITIALIZE.  Initialization occurs when @ref wdt_api_t::open is called. */
typedef struct st_iwdt_instance_ctrl
{
    uint32_t wdt_open;                                 ///< Indicates whether the open() API has been successfully called.
    void   * p_context;                                ///< Placeholder for user data.  Passed to the user callback in wdt_callback_args_t.

    void (* p_callback)(wdt_callback_args_t * p_args); ///< Callback provided when a WDT NMI ISR occurs.
    wdt_callback_args_t * p_callback_memory;           // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
} iwdt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const wdt_api_t g_wdt_on_iwdt;

/** @endcond */
fsp_err_t R_IWDT_Refresh(wdt_ctrl_t * const p_api_ctrl);

fsp_err_t R_IWDT_Open(wdt_ctrl_t * const p_api_ctrl, wdt_cfg_t const * const p_cfg);

fsp_err_t R_IWDT_StatusClear(wdt_ctrl_t * const p_api_ctrl, const wdt_status_t status);

fsp_err_t R_IWDT_StatusGet(wdt_ctrl_t * const p_api_ctrl, wdt_status_t * const p_status);

fsp_err_t R_IWDT_CounterGet(wdt_ctrl_t * const p_api_ctrl, uint32_t * const p_count);

fsp_err_t R_IWDT_TimeoutGet(wdt_ctrl_t * const p_api_ctrl, wdt_timeout_values_t * const p_timeout);

fsp_err_t R_IWDT_CallbackSet(wdt_ctrl_t * const          p_ctrl,
                             void (                    * p_callback)(wdt_callback_args_t *),
                             void * const                p_context,
                             wdt_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IWDT_H

/*******************************************************************************************************************//**
 * @} (end addtogroup IWDT)
 **********************************************************************************************************************/
