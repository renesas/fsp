/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_ETHOSU_API_H
#define RM_ETHOSU_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_AI_INTERFACES
 * @defgroup RM_ETHOSU_API Ethos-U Interface
 * @brief Interface for Ethos-U
 *
 * @section RM_ETHOSU_API_SUMMARY Summary
 * The Ethos-U NPU interface provides the ability to initialize Arm Ethos-U55 NPU.
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** User configuration structure, used in open function */
typedef struct st_rm_ethosu_callback_args
{
    void * p_context;                  ///< Placeholder for user data. Set in @ref rm_ethosu_api_t::open function in::rm_ethosu_cfg_t.
} rm_ethosu_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_rm_ethosu_cfg
{
    void (* p_callback)(rm_ethosu_callback_args_t * p_args); ///< Callback provided for NPU IRQ
    void    * p_context;                                     ///< Placeholder for user data
    uint32_t  ipl;                                           ///< Interrupt priority level
    IRQn_Type irq;                                           ///< NPU IRQ number
    bool      secure_enable;                                 ///< Configure NPU in secure or non-secure mode
    bool      privilege_enable;                              ///< Configure NPU in privileged or non-privileged mode
} rm_ethosu_cfg_t;

/** Ethos-U NPU API control block.  Allocate an instance specific control block to pass into the Ethos-U NPU API calls.
 */
typedef void rm_ethosu_ctrl_t;

/** Ethos-U NPU interface API. */
typedef struct st_rm_ethosu_api
{
    /** Enables Ethos-U NPU module and initialize driver.
     *
     * @param[in]   p_ctrl              Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg               Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(rm_ethosu_ctrl_t * const p_ctrl, rm_ethosu_cfg_t const * const p_cfg);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Control block set in @ref rm_ethosu_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_callback_memory        Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(rm_ethosu_ctrl_t * const p_ctrl, void (* p_callback)(rm_ethosu_callback_args_t *),
                              void * const p_context, rm_ethosu_callback_args_t * const p_callback_memory);

    /** Closes the module and deinitializes Ethos-U driver.
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_ethosu_api_t::open call.
     */
    fsp_err_t (* close)(rm_ethosu_ctrl_t * const p_ctrl);
} rm_ethosu_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_ethosu_instance
{
    rm_ethosu_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    rm_ethosu_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    rm_ethosu_api_t const * p_api;     ///< Pointer to the API structure for this instance
} rm_ethosu_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end defgroup RM_ETHOSU_API)
 **********************************************************************************************************************/

#endif                                 /* RM_ETHOSU_API_H */
