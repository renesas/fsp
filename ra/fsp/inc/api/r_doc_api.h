/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MONITORING_INTERFACES
 * @defgroup DOC_API DOC Interface
 *
 * @brief Interface for the Data Operation Circuit.
 *
 * Defines the API and data structures for the DOC implementation of the Data Operation Circuit (DOC) interface.
 *
 * @section DOC_API_SUMMARY Summary
 * @brief This module implements the DOC_API using the Data Operation Circuit (DOC).
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_DOC_API_H
#define R_DOC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Event that can trigger a callback function. */
typedef enum e_doc_event
{
    DOC_EVENT_COMPARISON_MISMATCH       = 0x00, ///< The data is not equal to the reference data setting.
    DOC_EVENT_ADDITION                  = 0x01, ///< Addition resulted in a value greater than the max for the configured bit width.
    DOC_EVENT_SUBTRACTION               = 0x02, ///< Subtraction resulted in a value less than 0.
    DOC_EVENT_COMPARISON_MATCH          = 0x04, ///< The data is equal to the reference data settting.
    DOC_EVENT_COMPARISON_LOWER          = 0x08, ///< The data is less than the reference data setting.
    DOC_EVENT_COMPARISON_UPPER          = 0x0C, ///< The data is greater than the reference data setting.
    DOC_EVENT_COMPARISON_INSIDE_WINDOW  = 0x10, ///< The data is between the two reference data settings.
    DOC_EVENT_COMPARISON_OUTSIDE_WINDOW = 0x14, ///< The data is outside the two reference data setttings.
} doc_event_t;

/** The bit width used during operations. */
typedef enum e_doc_bit_width
{
    DOC_BIT_WIDTH_16,                  ///< Operations are 16-bit.
    DOC_BIT_WIDTH_32                   ///< Operations are 32-bit.
} doc_bit_width_t;

/** Callback function parameter data. */
typedef struct st_doc_callback_args
{
    void const * p_context;            ///< Placeholder for user data.
    ///< Set in @ref doc_api_t::open function in @ref doc_cfg_t.
} doc_callback_args_t;

/** DOC control block.  Allocate an instance specific control block to pass into the DOC API calls.
 */
typedef void doc_ctrl_t;

/** User configuration structure, used in the open function. */
typedef struct st_doc_cfg
{
    doc_event_t     event;             ///< Select enumerated value from @ref doc_event_t.
    doc_bit_width_t bit_width;         ///< The bit width of operations.

    /**
     * Initial/Reference data for addition, subtraction, and comparison operations.
     * - In Addition and Subtraction mode, this value sets the initial value of the operations.
     * - In Comparison match, mismatch, lower, and upper modes, this value is compared with data that is written.
     * - In Comparison inside window and outside window modes, this value is used as the lower bound for comparisons.
     */
    uint32_t doc_data;

    /**
     * Additional reference data for use in Window Comparison operations.
     * - In Comparison inside window and outside window modes, this value is used as the upper bound for comparisons.
     */
    uint32_t doc_data_extra;

    uint8_t   ipl;                     ///< DOC interrupt priority
    IRQn_Type irq;                     ///< Interrupt number assigned to this instance

    /** Callback provided when a DOC ISR occurs. */
    void (* p_callback)(doc_callback_args_t * p_args);

    /** Placeholder for user data. Passed to the user callback in @ref doc_callback_args_t. */
    void const * p_context;
} doc_cfg_t;

/** Data Operation Circuit (DOC) API structure. DOC functions implemented at the HAL layer will follow this API. */
typedef struct st_doc_api
{
    /** Initial configuration.
     * @param[in]   p_ctrl      Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg       Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(doc_ctrl_t * const p_ctrl, doc_cfg_t const * const p_cfg);

    /**Allow the driver to be reconfigured. Will reduce power consumption.
     * @param[in]   p_ctrl      Control block set in @ref doc_api_t::open call.
     */
    fsp_err_t (* close)(doc_ctrl_t * const p_ctrl);

    /** Gets the result of addition/subtraction operations and stores it in the provided pointer p_result.
     *
     * @param[in]   p_ctrl      Control block set in @ref doc_api_t::open call.
     * @param[in]   p_result    The result of the DOC operation.
     */
    fsp_err_t (* read)(doc_ctrl_t * const p_ctrl, uint32_t * p_result);

    /** Write to the DODIR register.
     *
     * @param[in]   p_ctrl      Control block set in @ref doc_api_t::open call.
     * @param[in]   data        data to be written to DOC DODIR register.
     */
    fsp_err_t (* write)(doc_ctrl_t * const p_ctrl, uint32_t data);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the DOC control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(doc_ctrl_t * const p_ctrl, void (* p_callback)(doc_callback_args_t *),
                              void const * const p_context, doc_callback_args_t * const p_callback_memory);
} doc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_doc_instance
{
    doc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    doc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    doc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} doc_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup DOC_API)
 **********************************************************************************************************************/
