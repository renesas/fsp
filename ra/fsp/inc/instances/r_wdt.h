/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @addtogroup WDT WDT
 * @{
 **********************************************************************************************************************/

#ifndef R_WDT_H
#define R_WDT_H

#include "bsp_api.h"

#include "r_wdt_cfg.h"
#include "r_wdt_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** WDT private control block. DO NOT MODIFY. Initialization occurs when R_WDT_Open() is called. */
typedef struct st_wdt_instance_ctrl
{
    uint32_t wdt_open;                                 // Indicates whether the open() API has been successfully
                                                       // called.
    void const * p_context;                            // Placeholder for user data.  Passed to the user callback in
                                                       // wdt_callback_args_t.
    void (* p_callback)(wdt_callback_args_t * p_args); // Callback provided when a WDT NMI ISR occurs.
    wdt_callback_args_t * p_callback_memory;           // Pointer to non-secure memory that can be used to pass arguments to a callback in non-secure memory.
} wdt_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const wdt_api_t g_wdt_on_wdt;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_WDT_Refresh(wdt_ctrl_t * const p_ctrl);

fsp_err_t R_WDT_Open(wdt_ctrl_t * const p_ctrl, wdt_cfg_t const * const p_cfg);

fsp_err_t R_WDT_StatusClear(wdt_ctrl_t * const p_ctrl, const wdt_status_t status);

fsp_err_t R_WDT_StatusGet(wdt_ctrl_t * const p_ctrl, wdt_status_t * const p_status);

fsp_err_t R_WDT_CounterGet(wdt_ctrl_t * const p_ctrl, uint32_t * const p_count);

fsp_err_t R_WDT_TimeoutGet(wdt_ctrl_t * const p_ctrl, wdt_timeout_values_t * const p_timeout);

fsp_err_t R_WDT_CallbackSet(wdt_ctrl_t * const          p_ctrl,
                            void (                    * p_callback)(wdt_callback_args_t *),
                            void const * const          p_context,
                            wdt_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_WDT_H

/*******************************************************************************************************************//**
 * @} (end addtogroup WDT)
 **********************************************************************************************************************/
