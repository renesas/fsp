/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_IPC_H
#define R_IPC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ipc_cfg.h"
#include "r_ipc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup IPC
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* IPC Instance Control Block. DO NOT INITIALIZE.  */
typedef struct st_ipc_instance_ctrl
{
    uint32_t            open;                   // Used to determine if the channel is configured
    ipc_cfg_t const   * p_cfg;                  // Pointer to the configuration block
    R_IPC_IPC_CH_Type * p_send_reg;             // Base register for sending
    R_IPC_IPC_CH_Type * p_recv_reg;             // Base register for receiving
    void (* p_callback)(ipc_callback_args_t *); // Pointer to callback
    ipc_callback_args_t * p_callback_memory;    // Pointer to optional working memory
    void                * p_context;            // Pointer to context to be passed into callback function
} ipc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const ipc_api_t g_ipc_on_ipc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_IPC_Open(ipc_ctrl_t * const p_api_ctrl, ipc_cfg_t const * const p_cfg);
fsp_err_t R_IPC_MessageSend(ipc_ctrl_t * const p_api_ctrl, uint32_t message);
fsp_err_t R_IPC_EventGenerate(ipc_ctrl_t * const p_api_ctrl, ipc_generate_event_t event);
fsp_err_t R_IPC_CallbackSet(ipc_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(ipc_callback_args_t *),
                            void * const                p_context,
                            ipc_callback_args_t * const p_callback_memory);
fsp_err_t R_IPC_Close(ipc_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end addtogroup IPC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
