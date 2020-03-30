/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#define DOC_CODE_VERSION_MAJOR    (1U)
#define DOC_CODE_VERSION_MINOR    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DOC instance control block. Do not initialize. Initialization occurs when the @ref doc_api_t::open function is called. */
typedef struct st_doc_instance_ctrl
{
    doc_cfg_t const * p_cfg;           // Pointer to the configuration structure
    uint32_t          open;            ///< Used by driver to check if the control structure is valid
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
fsp_err_t R_DOC_StatusGet(doc_ctrl_t * const p_api_ctrl, doc_status_t * p_status);
fsp_err_t R_DOC_Write(doc_ctrl_t * const p_api_ctrl, uint16_t data);
fsp_err_t R_DOC_VersionGet(fsp_version_t * const p_version);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_DOC_H

/*******************************************************************************************************************//**
 * @} (end defgroup DOC)
 **********************************************************************************************************************/
