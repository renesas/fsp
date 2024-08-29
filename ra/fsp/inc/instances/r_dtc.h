/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup DTC
 * @{
 **********************************************************************************************************************/

#ifndef R_DTC_H
#define R_DTC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_transfer_api.h"
#include "r_dtc_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Max configurable number of transfers in NORMAL MODE */
#define DTC_MAX_NORMAL_TRANSFER_LENGTH    (0x10000)

/** Max number of transfers per repeat for REPEAT MODE */
#define DTC_MAX_REPEAT_TRANSFER_LENGTH    (0x100)

/** Max number of transfers per block in BLOCK MODE */
#define DTC_MAX_BLOCK_TRANSFER_LENGTH     (0x100)

/** Max configurable number of blocks to transfer in BLOCK MODE */
#define DTC_MAX_BLOCK_COUNT               (0x10000)

/** Alignment required for transfer_info_t structures. */
#define DTC_TRANSFER_INFO_ALIGNMENT       BSP_ALIGN_VARIABLE(BSP_FEATURE_DTC_TRANSFER_INFO_ALIGNMENT)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DTC transfer configuration extension. This extension is required. */
typedef struct st_dtc_extended_cfg
{
    /** Select which IRQ will trigger the transfer. */
    IRQn_Type activation_source;
} dtc_extended_cfg_t;

/** Control block used by driver. DO NOT INITIALIZE - this structure will be initialized in @ref transfer_api_t::open. */
typedef struct st_dtc_instance_ctrl
{
    uint32_t  open;                    // Driver ID
    IRQn_Type irq;                     // Transfer activation IRQ number.
} dtc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const transfer_api_t g_transfer_on_dtc;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_DTC_Open(transfer_ctrl_t * const p_api_ctrl, transfer_cfg_t const * const p_cfg);
fsp_err_t R_DTC_Reconfigure(transfer_ctrl_t * const p_api_ctrl, transfer_info_t * p_info);
fsp_err_t R_DTC_Reset(transfer_ctrl_t * const p_api_ctrl,
                      void const * volatile   p_src,
                      void * volatile         p_dest,
                      uint16_t const          num_transfers);
fsp_err_t R_DTC_SoftwareStart(transfer_ctrl_t * const p_api_ctrl, transfer_start_mode_t mode);
fsp_err_t R_DTC_SoftwareStop(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DTC_Enable(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DTC_Disable(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DTC_InfoGet(transfer_ctrl_t * const p_api_ctrl, transfer_properties_t * const p_properties);
fsp_err_t R_DTC_Reload(transfer_ctrl_t * const p_api_ctrl,
                       void const            * p_src,
                       void                  * p_dest,
                       uint32_t const          num_transfers);
fsp_err_t R_DTC_CallbackSet(transfer_ctrl_t * const          p_api_ctrl,
                            void (                         * p_callback)(transfer_callback_args_t *),
                            void const * const               p_context,
                            transfer_callback_args_t * const p_callback_memory);
fsp_err_t R_DTC_Close(transfer_ctrl_t * const p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup DTC)
 **********************************************************************************************************************/
