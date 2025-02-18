/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_FILEX_BLOCK_MEDIA_H
#define RM_FILEX_BLOCK_MEDIA_H

/*******************************************************************************************************************//**
 * @addtogroup RM_FILEX_BLOCK_MEDIA
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "bsp_api.h"
#include "fx_api.h"
#include "rm_filex_block_media_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** FileX block media private control block. DO NOT MODIFY.  Initialization occurs when RM_FILEX_BLOCK_MEDIA_Open is called. */
typedef struct
{
    uint32_t open;
    rm_filex_block_media_cfg_t const * p_cfg;
    volatile rm_block_media_event_t    last_event;
    volatile bool event_ready;
} rm_filex_block_media_instance_ctrl_t;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_FILEX_BLOCK_MEDIA_Open(rm_filex_block_media_ctrl_t * const      p_ctrl,
                                    rm_filex_block_media_cfg_t const * const p_cfg);
fsp_err_t RM_FILEX_BLOCK_MEDIA_Close(rm_filex_block_media_ctrl_t * const p_ctrl);
void      RM_FILEX_BLOCK_MEDIA_BlockDriver(FX_MEDIA * p_fx_media);

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rm_filex_block_media_api_t g_filex_on_block_media;

/** @endcond */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_FILEX_BLOCK_MEDIA)
 **********************************************************************************************************************/

#endif
