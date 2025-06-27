/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_DOC_H
#define R_DOC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_doc_api.h"
#include "r_doc_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DOC instance control block. Do not initialize. Initialization occurs when the @ref doc_api_t::open function is called. */
typedef struct st_doc_instance_ctrl
{
    doc_cfg_t const * p_cfg;           // Pointer to the configuration structure
    uint32_t          open;            ///< Used by driver to check if the control structure is valid

    /* Pointer to callback and optional working memory */
    void (* p_callback)(doc_callback_args_t *);
    doc_callback_args_t * p_callback_memory;
    void                * p_context;   ///< User defined context passed into callback function
} doc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const doc_api_t g_doc_on_doc;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_DOC_Open(doc_ctrl_t * const p_api_ctrl, doc_cfg_t const * const p_cfg);
fsp_err_t R_DOC_Close(doc_ctrl_t * const p_api_ctrl);
fsp_err_t R_DOC_Read(doc_ctrl_t * const p_api_ctrl, uint32_t * p_result);
fsp_err_t R_DOC_Write(doc_ctrl_t * const p_api_ctrl, uint32_t data);
fsp_err_t R_DOC_CallbackSet(doc_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(doc_callback_args_t *),
                            void * const                p_context,
                            doc_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_DOC_H

/*******************************************************************************************************************//**
 * @} (end defgroup DOC)
 **********************************************************************************************************************/
