/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_MRAM_H
#define R_MRAM_H

/*******************************************************************************************************************//**
 * @addtogroup MRAM
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_flash_api.h"
#include "r_mram_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* If Code Flash programming is enabled, then all API functions must execute out of RAM. */
#if defined(__ICCARM__)
 #pragma section=".ram_from_flash"
#endif
#if defined(__ARMCC_VERSION) || defined(__GNUC__)
 #define PLACE_IN_RAM_SECTION    __attribute__((noinline)) BSP_PLACE_IN_SECTION(".ram_from_flash")
#else
 #define PLACE_IN_RAM_SECTION    BSP_PLACE_IN_SECTION(".ram_from_flash")
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** MRAM instance control block. DO NOT INITIALIZE. */
typedef struct st_mram_instance_ctrl
{
    uint32_t            opened;        // To check whether api has been opened or not.
    flash_cfg_t const * p_cfg;

    uint32_t timeout_mram_write;
    uint32_t timeout_arc_increment;
    uint32_t timeout_arc_read;
    uint32_t timeout_configuration_set;
    uint32_t timeout_maci_command;
} mram_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const flash_api_t g_flash_on_mram;

/** @endcond */

fsp_err_t R_MRAM_Open(flash_ctrl_t * const p_api_ctrl, flash_cfg_t const * const p_cfg);

fsp_err_t R_MRAM_Write(flash_ctrl_t * const p_api_ctrl,
                       uint32_t const       src_address,
                       uint32_t             mram_address,
                       uint32_t const       num_bytes) PLACE_IN_RAM_SECTION;

fsp_err_t R_MRAM_Erase(flash_ctrl_t * const p_api_ctrl, uint32_t const address, uint32_t const num_blocks);

fsp_err_t R_MRAM_BlankCheck(flash_ctrl_t * const p_api_ctrl,
                            uint32_t const       address,
                            uint32_t             num_bytes,
                            flash_result_t     * blank_check_result);

fsp_err_t R_MRAM_Close(flash_ctrl_t * const p_api_ctrl);

fsp_err_t R_MRAM_StatusGet(flash_ctrl_t * const p_api_ctrl, flash_status_t * const p_status);

fsp_err_t R_MRAM_AccessWindowSet(flash_ctrl_t * const p_api_ctrl, uint32_t const start_addr, uint32_t const end_addr);

fsp_err_t R_MRAM_AccessWindowClear(flash_ctrl_t * const p_api_ctrl);

fsp_err_t R_MRAM_IdCodeSet(flash_ctrl_t * const p_api_ctrl, uint8_t const * const p_id_code, flash_id_code_mode_t mode);

fsp_err_t R_MRAM_Reset(flash_ctrl_t * const p_api_ctrl);

fsp_err_t R_MRAM_UpdateFlashClockFreq(flash_ctrl_t * const p_api_ctrl);

fsp_err_t R_MRAM_StartUpAreaSelect(flash_ctrl_t * const      p_api_ctrl,
                                   flash_startup_area_swap_t swap_type,
                                   bool                      is_temporary);
fsp_err_t R_MRAM_CallbackSet(flash_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(flash_callback_args_t *),
                             void * const                  p_context,
                             flash_callback_args_t * const p_callback_memory);
fsp_err_t R_MRAM_BankSwap(flash_ctrl_t * const p_api_ctrl);
fsp_err_t R_MRAM_InfoGet(flash_ctrl_t * const p_api_ctrl, flash_info_t * const p_info);
fsp_err_t R_MRAM_AntiRollbackCounterIncrement(flash_ctrl_t * const p_api_ctrl, flash_arc_t counter);
fsp_err_t R_MRAM_AntiRollbackCounterRefresh(flash_ctrl_t * const p_api_ctrl, flash_arc_t counter);
fsp_err_t R_MRAM_AntiRollbackCounterRead(flash_ctrl_t * const p_api_ctrl, flash_arc_t counter,
                                         uint32_t * const p_count);
fsp_err_t R_MRAM_UserLockableAreaWrite(flash_ctrl_t * const p_api_ctrl,
                                       uint32_t const       src_address,
                                       uint32_t             mram_address,
                                       uint32_t const       num_bytes);

/*******************************************************************************************************************//**
 * @} (end defgroup MRAM)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
