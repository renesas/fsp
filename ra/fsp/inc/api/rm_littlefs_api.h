/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_LITTLEFS_API_H
#define RM_LITTLEFS_API_H

/*******************************************************************************************************************//**
 * @defgroup RM_LITTLEFS_API LittleFS Interface
 * @ingroup RENESAS_STORAGE_INTERFACES
 * @brief Interface for LittleFS access
 *
 * @section RM_LITTLEFS_API_SUMMARY Summary
 * The LittleFS Port configures a fail-safe filesystem designed for microcontrollers on top of a lower level storage
 * device.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_flash_api.h"
#include "lfs.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** User configuration structure, used in open function */
typedef struct st_rm_littlefs_cfg
{
    struct lfs_config const * p_lfs_cfg; ///< Pointer LittleFS configuration structure
    void const              * p_extend;  ///< Pointer to hardware dependent configuration
} rm_littlefs_cfg_t;

/** LittleFS Port API control block.  Allocate an instance specific control block to pass into the LittleFS Port API calls.
 */
typedef void rm_littlefs_ctrl_t;

/** LittleFS Port interface API. */
typedef struct st_rm_littlefs_api
{
    /** Initialize The lower level storage device.
     *
     * @param[in]   p_ctrl              Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg               Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(rm_littlefs_ctrl_t * const p_ctrl, rm_littlefs_cfg_t const * const p_cfg);

    /** Closes the module and lower level storage device.
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_littlefs_api_t::open call.
     */
    fsp_err_t (* close)(rm_littlefs_ctrl_t * const p_ctrl);
} rm_littlefs_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_littlefs_instance
{
    rm_littlefs_ctrl_t      * p_ctrl;  ///< Pointer to the control structure for this instance
    rm_littlefs_cfg_t const * p_cfg;   ///< Pointer to the configuration structure for this instance
    rm_littlefs_api_t const * p_api;   ///< Pointer to the API structure for this instance
} rm_littlefs_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end defgroup RM_LITTLEFS_API)
 **********************************************************************************************************************/

#endif                                 /* RM_LITTLEFS_API_H */
