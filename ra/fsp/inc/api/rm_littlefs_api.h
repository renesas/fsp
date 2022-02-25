/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef RM_LITTLEFS_API_H
#define RM_LITTLEFS_API_H

/*******************************************************************************************************************//**
 * @defgroup RM_LITTLEFS_API LittleFS Interface
 * @ingroup RENESAS_INTERFACES
 * @brief Interface for LittleFS access
 *
 * @section RM_LITTLEFS_API_SUMMARY Summary
 * The LittleFS Port configures a fail-safe filesystem designed for microcontrollers on top of a lower level storage
 * device.
 *
 * Implemented by:
 * @ref RM_LITTLEFS_FLASH
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
 * @par Implemented as
 * - @ref rm_littlefs_flash_instance_ctrl_t
 */
typedef void rm_littlefs_ctrl_t;

/** LittleFS Port interface API. */
typedef struct st_rm_littlefs_api
{
    /** Initialize The lower level storage device.
     * @par Implemented as
     * - @ref RM_LITTLEFS_FLASH_Open
     *
     * @param[in]   p_ctrl              Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg               Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(rm_littlefs_ctrl_t * const p_ctrl, rm_littlefs_cfg_t const * const p_cfg);

    /** Closes the module and lower level storage device.
     * @par Implemented as
     * - @ref RM_LITTLEFS_FLASH_Close
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

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end defgroup RM_LITTLEFS_API)
 **********************************************************************************************************************/

#endif                                 /* RM_LITTLEFS_API_H */
