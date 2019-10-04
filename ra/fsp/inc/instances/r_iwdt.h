/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

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
#define IWDT_CODE_VERSION_MAJOR    (1U)
#define IWDT_CODE_VERSION_MINOR    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** WDT control block. DO NOT INITIALIZE.  Initialization occurs when wdt_api_t::open is called. */
typedef struct st_iwdt_instance_ctrl
{
    uint32_t wdt_open;                                 ///< Indicates whether the open() API has been successfully called.
    void const * p_context;                            ///< Placeholder for user data.  Passed to the user callback in wdt_callback_args_t.
    R_IWDT_Type * p_reg;                               ///< Pointer to register base address.
    void (* p_callback)(wdt_callback_args_t * p_args); ///< Callback provided when a WDT NMI ISR occurs.
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

fsp_err_t R_IWDT_VersionGet(fsp_version_t * const p_data);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IWDT_H

/*******************************************************************************************************************//**
 * @} (end addtogroup IWDT)
 **********************************************************************************************************************/
