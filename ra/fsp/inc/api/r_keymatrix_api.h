/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @defgroup KEYMATRIX_API Key Matrix Interface
 * @ingroup RENESAS_INPUT_INTERFACES
 * @brief Interface for key matrix functions.
 *
 * @section KEYMATRIX_API_SUMMARY Summary
 * The KEYMATRIX interface provides standard Key Matrix functionality including event generation on a rising or falling
 * edge for one or more channels at the same time. The generated event indicates all channels that are active in
 * that instant via a bit mask. This allows the interface to be used with a matrix configuration or a one-to-one
 * hardware implementation that is triggered on either a rising or a falling edge.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_KEYMATRIX_API_H
#define R_KEYMATRIX_API_H

/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Key matrix control block.  Allocate an instance specific control block to pass into the key matrix API calls.
 */
typedef void keymatrix_ctrl_t;

/** Trigger type: rising edge, falling edge */
typedef enum e_keymatrix_trigger
{
    KEYMATRIX_TRIG_FALLING = 0,        ///< Falling edge trigger
    KEYMATRIX_TRIG_RISING  = 1,        ///< Rising edge trigger
} keymatrix_trigger_t;

/** Callback function parameter data */
typedef struct st_keymatrix_callback_args
{
    void * p_context;                  ///< Holder for user data. Set in @ref keymatrix_api_t::open function in @ref keymatrix_cfg_t.

    /** Bit vector representing the physical hardware channel(s) that caused the interrupt. */
    uint32_t channel_mask;
} keymatrix_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_keymatrix_cfg
{
    uint32_t            channel_mask;                        ///< Key Input channel(s). Bit mask of channels to open.
    keymatrix_trigger_t trigger;                             ///< Key Input trigger setting.
    uint8_t             ipl;                                 ///< Interrupt priority level
    IRQn_Type           irq;                                 ///< NVIC IRQ number

    void (* p_callback)(keymatrix_callback_args_t * p_args); ///< Callback for key interrupt ISR.
    void       * p_context;                                  ///< Holder for user data. Passed to callback in keymatrix_user_cb_data_t.
    void const * p_extend;                                   ///< Extension parameter for hardware specific settings.
} keymatrix_cfg_t;

/** Key Matrix driver structure. Key Matrix functions implemented at the HAL layer will use this API. */
typedef struct st_keymatrix_api
{
    /** Initial configuration.
     *
     * @param[out]  p_ctrl   Pointer to control block. Must be declared by user. Value set in this function.
     * @param[in]   p_cfg    Pointer to configuration structure. All elements of the structure must be set by user.
     */
    fsp_err_t (* open)(keymatrix_ctrl_t * const p_ctrl, keymatrix_cfg_t const * const p_cfg);

    /** Enable Key interrupt
     *
     * @param[in]     p_ctrl      Control block pointer set in Open call for this Key interrupt.
     */
    fsp_err_t (* enable)(keymatrix_ctrl_t * const p_ctrl);

    /** Disable Key interrupt.
     *
     * @param[in]     p_ctrl      Control block pointer set in Open call for this Key interrupt.
     */
    fsp_err_t (* disable)(keymatrix_ctrl_t * const p_ctrl);

    /** Allow driver to be reconfigured. May reduce power consumption.
     *
     * @param[in]  p_ctrl      Control block pointer set in Open call for this Key interrupt.
     */
    fsp_err_t (* close)(keymatrix_ctrl_t * const p_ctrl);
} keymatrix_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_keymatrix_instance
{
    keymatrix_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    keymatrix_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    keymatrix_api_t const * p_api;     ///< Pointer to the API structure for this instance
} keymatrix_instance_t;

/******************************************************************************************************************//**
 * @} (end addtogroup KEYMATRIX_API)
 *********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
